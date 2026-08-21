#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "parser.h"
#include "scanner.h"
#include "semantic.h"

static char *assembly_path;
static char *executable_path;
static int assembly_owned;
static int assembly_complete;
static int executable_owned;
static int executable_complete;

static void cleanup_outputs(void)
{
    if (assembly_owned && !assembly_complete && assembly_path != NULL) {
        (void)unlink(assembly_path);
    }
    if (executable_owned && !executable_complete && executable_path != NULL) {
        (void)unlink(executable_path);
    }
    free(assembly_path);
    free(executable_path);
}

static int ends_with_micro(const char *basename)
{
    size_t length = strlen(basename);
    return length > 6 && strcmp(basename + length - 6, ".micro") == 0;
}

static char *replace_or_append(const char *source_path, size_t removed,
                               const char *suffix)
{
    size_t source_length = strlen(source_path);
    size_t suffix_length = strlen(suffix);
    size_t prefix_length = source_length - removed;
    char *result;

    if (prefix_length > SIZE_MAX - suffix_length - 1) {
        return NULL;
    }
    result = malloc(prefix_length + suffix_length + 1);
    if (result == NULL) {
        return NULL;
    }
    memcpy(result, source_path, prefix_length);
    memcpy(result + prefix_length, suffix, suffix_length + 1);
    return result;
}

static int derive_output_paths(const char *source_path)
{
    const char *slash = strrchr(source_path, '/');
    const char *basename = slash == NULL ? source_path : slash + 1;
    size_t removed = ends_with_micro(basename) ? 6U : 0U;

    assembly_path = replace_or_append(source_path, removed, ".s");
    executable_path = replace_or_append(source_path, removed,
                                        removed == 0 ? ".out" : "");
    return assembly_path != NULL && executable_path != NULL;
}

static char *prefix_current_directory(const char *path)
{
    size_t length = strlen(path);
    char *result;
    if (length > SIZE_MAX - 3) {
        return NULL;
    }
    result = malloc(length + 3);
    if (result == NULL) {
        return NULL;
    }
    memcpy(result, "./", 2);
    memcpy(result + 2, path, length + 1);
    return result;
}

static char *duplicate_string(const char *text)
{
    size_t length = strlen(text);
    char *result;
    if (length == SIZE_MAX) {
        return NULL;
    }
    result = malloc(length + 1);
    if (result != NULL) {
        memcpy(result, text, length + 1);
    }
    return result;
}

static char *normalized_assembly_operand(void)
{
    if (strchr(assembly_path, '/') == NULL && assembly_path[0] == '-') {
        return prefix_current_directory(assembly_path);
    }
    return duplicate_string(assembly_path);
}

static char *normalized_execution_path(void)
{
    if (strchr(executable_path, '/') == NULL) {
        return prefix_current_directory(executable_path);
    }
    return duplicate_string(executable_path);
}

static char *shell_quote(const char *text)
{
    size_t length = 3;
    const char *cursor;
    char *quoted;
    char *output;

    for (cursor = text; *cursor != '\0'; ++cursor) {
        size_t addition = *cursor == '\'' ? 4U : 1U;
        if (length > SIZE_MAX - addition) {
            return NULL;
        }
        length += addition;
    }
    quoted = malloc(length);
    if (quoted == NULL) {
        return NULL;
    }
    output = quoted;
    *output++ = '\'';
    for (cursor = text; *cursor != '\0'; ++cursor) {
        if (*cursor == '\'') {
            memcpy(output, "'\\''", 4);
            output += 4;
        } else {
            *output++ = *cursor;
        }
    }
    *output++ = '\'';
    *output = '\0';
    return quoted;
}

static int decoded_status(int status, const char *operation)
{
    if (status == -1) {
        fprintf(stderr, "%s failed: %s\n", operation, strerror(errno));
        return 1;
    }
    if (WIFEXITED(status)) {
        return WEXITSTATUS(status);
    }
    if (WIFSIGNALED(status)) {
        fprintf(stderr, "%s terminated by signal %d\n", operation,
                WTERMSIG(status));
        return 128 + WTERMSIG(status);
    }
    fprintf(stderr, "%s did not terminate normally\n", operation);
    return 1;
}

static int link_generated_program(void)
{
    char *operand = normalized_assembly_operand();
    char *quoted_operand;
    char *quoted_output;
    char *command;
    size_t command_size;
    int status;

    if (operand == NULL) {
        return 1;
    }
    quoted_operand = shell_quote(operand);
    quoted_output = shell_quote(executable_path);
    free(operand);
    if (quoted_operand == NULL || quoted_output == NULL) {
        free(quoted_operand);
        free(quoted_output);
        return 1;
    }
    command_size = strlen(quoted_operand) + strlen(quoted_output) + 16;
    command = malloc(command_size);
    if (command == NULL) {
        free(quoted_operand);
        free(quoted_output);
        return 1;
    }
    (void)snprintf(command, command_size, "gcc %s -o %s", quoted_operand,
                   quoted_output);
    executable_owned = 1;
    status = decoded_status(system(command), "gcc");
    free(command);
    free(quoted_operand);
    free(quoted_output);
    if (status == 0 && access(executable_path, X_OK) == 0) {
        executable_complete = 1;
        return 0;
    }
    return status == 0 ? 1 : status;
}

static int run_generated_program(void)
{
    char *execution_path = normalized_execution_path();
    char *command;
    int status;

    if (execution_path == NULL) {
        return 1;
    }
    command = shell_quote(execution_path);
    free(execution_path);
    if (command == NULL) {
        return 1;
    }
    status = decoded_status(system(command), "generated program");
    free(command);
    return status;
}

int main(int argc, char **argv)
{
    FILE *input;
    FILE *output;
    int compilation_ok;
    int input_close_ok;
    int output_close_ok;
    int status;

    if (argc != 2) {
        fprintf(stderr, "usage: %s source-file\n", argv[0]);
        return 2;
    }
    if (atexit(cleanup_outputs) != 0) {
        fprintf(stderr, "could not register output cleanup\n");
        return 1;
    }
    if (!derive_output_paths(argv[1])) {
        fprintf(stderr, "could not derive output paths\n");
        return 1;
    }

    input = fopen(argv[1], "r");
    if (input == NULL) {
        fprintf(stderr, "%s: %s\n", argv[1], strerror(errno));
        return 1;
    }
    output = fopen(assembly_path, "w");
    if (output == NULL) {
        fprintf(stderr, "%s: %s\n", assembly_path, strerror(errno));
        (void)fclose(input);
        return 1;
    }
    assembly_owned = 1;

    scanner_init(input, argv[1]);
    semantic_init(output);
    parser_init();
    compilation_ok = system_goal();
    semantic_destroy();

    input_close_ok = fclose(input) == 0;
    if (!input_close_ok) {
        fprintf(stderr, "%s: could not close input: %s\n", argv[1],
                strerror(errno));
    }
    output_close_ok = fclose(output) == 0;
    if (!output_close_ok) {
        fprintf(stderr, "%s: could not close assembly output: %s\n",
                assembly_path, strerror(errno));
    }
    if (compilation_ok && output_close_ok) {
        assembly_complete = 1;
    }
    if (!compilation_ok || !input_close_ok || !output_close_ok) {
        return 1;
    }

    status = link_generated_program();
    if (status != 0) {
        return status;
    }
    return run_generated_program();
}
