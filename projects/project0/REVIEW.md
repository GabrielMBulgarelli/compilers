# Project 0: implementation review

Project 0 is a compiler for the Micro language described in Chapter 2 of
Fischer-LeBlanc. It is written in C17 and runs on native x86-64 Linux. Given a
Micro source file, it scans and parses the program, emits GNU x86-64 assembly,
uses GCC to build the generated program, and finally runs that program.

The compiler is intentionally small and direct. Its scanner and
recursive-descent parser are handwritten, and code generation takes place as
the parser recognizes each construct. There is no parser generator, abstract
syntax tree, or intermediate representation between the source program and the
assembly output.

The [README](README.md) documents the complete grammar and command-line usage.
This document explains how the implementation fits together and points to the
parts of the source that are most useful when reviewing it.

## Compilation model

The T-diagram for the project identifies Micro as the source language, GNU
x86-64 assembly as the target language, and C17 as the implementation language:

```text
                source language        target language
             +--------------------+------------------------+
             |       Micro        | GNU x86-64 assembly    |
             +--------------------+------------------------+
                              |       |
                              |  C17  |
                              |       |
                              +-------+

Host: native x86-64 Linux
GCC assembles and links the emitted target program.
```

In practice, a source file passes through the following stages:

```text
program.micro
    |
    v
scanner -> recursive-descent parser -> semantic actions -> code generator
                                                              |
                                                              v
                                                          program.s
                                                              |
                                                             GCC
                                                              |
                                                              v
                                                        executable -> run
```

`main.c` controls this outer process. It derives the output paths, opens the
files, invokes the compiler, asks GCC to assemble and link the result, runs the
executable, and reports the final status. The parser handles the language
itself and calls semantic and code-generation functions while it consumes the
input.

## Source organization

The implementation is divided by responsibility:

| File | Responsibility | Useful entry points |
|---|---|---|
| `micro.h` | Shared token definitions and expression records | `token`, `expr_rec` |
| `scanner.c` | Character input, comments, tokens, identifiers, and integer checks | `scanner_next` |
| `parser.c` | Grammar procedures and one-token lookahead | `primary`, `expression`, `statement`, `system_goal` |
| `semantic.c` | Symbols, constant folding, temporaries, and conditional labels | `gen_infix`, `conditional_begin` |
| `codegen.c` | GNU x86-64 output and calls to the C library | `codegen_binary`, `codegen_read`, `codegen_finish` |
| `main.c` | Files, GCC execution, output names, exit status, and cleanup | `derive_output_paths`, `link_generated_program`, `cleanup_outputs` |
| `Makefile` | Builds, regression tests, sanitizer runs, and packaging | `test`, `verify`, `package` |

This separation keeps the parser close to the grammar without making it
responsible for platform details such as process creation or generated-file
cleanup.

## Scanning and parsing

The scanner keeps one character of lookahead. Once it recognizes a token, it
leaves the first unrelated character ready for the next call. That distinction
is especially important for `-`: a single character is subtraction, while
`--` begins a comment.

Identifiers start with a letter and may continue with letters, digits, or
underscores. They are limited to 32 characters. Decimal integer literals must
fit in `int32_t`, so an out-of-range literal is rejected before it reaches code
generation. The scanner also records the source location used in diagnostics.

The parser keeps one token of lookahead and follows the grammar one procedure
at a time. `primary` recognizes identifiers, literals, parenthesized
expressions, and conditional expressions. `expression` handles left-associative
addition and subtraction. `statement` selects among assignment, `read`, and
`write`, while `system_goal` verifies that the whole input has been consumed.

Because the parser calls semantic actions immediately, it does not need to
store a separate syntax tree. The structure of the recursive calls supplies
the ordering needed to emit the target program.

## Values, symbols, and generated code

All Micro values are signed 32-bit integers. When both operands of an addition
or subtraction are literals, `semantic.c::gen_infix` evaluates the operation
during compilation. It calculates in `int64_t` first and rejects a result that
does not fit in the signed 32-bit range. Expressions that cannot be folded are
assigned compiler-generated temporaries.

Conditional expressions have the form `(E1 | E2 | E3)`. A nonzero `E1`
selects `E2`; zero selects `E3`. The semantic layer allocates false and end
labels, and the code generator emits jumps around the branch that was not
selected. Only the selected expression is evaluated at runtime.

User variables and compiler temporaries occupy separate assembler namespaces.
A Micro variable named `main`, `printf`, or `scanf` therefore cannot replace a
runtime symbol. Data operands use RIP-relative addressing, which lets GCC link
the output normally as a PIE. Micro `read` and `write` are implemented with
`scanf@PLT` and `printf@PLT`.

The generated file contains a complete `main` function, follows the x86-64
calling convention, returns zero explicitly, and marks the stack as
non-executable.

## Running a complete example

The example program reads two integers, adds them, selects the sum through a
conditional expression, and writes the result. From the `project0` directory,
it can be inspected and run with:

```sh
sed -n '1,80p' examples/example.micro
printf '2 3\n' | ./micro examples/example.micro
```

For the input `2 3`, the program prints:

```text
5
```

The compiler leaves `examples/example.s` and `examples/example` next to the
source file. The relevant labels, variables, and library calls can be located
with:

```sh
grep -nE 'main:|call (scanf|printf)|micro_var_|\.Lmicro_' examples/example.s
```

Prefixes such as `micro_var_` identify user variables in the generated
assembly. Labels beginning with `.Lmicro_false_` and `.Lmicro_end_` implement
the conditional branches.

## Errors and cleanup

Lexical, syntax, semantic, file, allocation, GCC, and generated-program
failures all produce a nonzero exit status. Invalid Micro input is never sent
to GCC, and the generated executable is not started when linking fails.

For example, `tests/bad_char.micro` contains the unsupported `*` character:

```sh
./micro tests/bad_char.micro; printf 'exit=%s\n' "$?"
test ! -e tests/bad_char.s && echo 'incomplete assembly removed'
```

The compiler reports the source path, line, and column, returns a nonzero
status, and removes the incomplete assembly file. Truncated or malformed input
is handled as an error instead of causing a segmentation fault.

Once assembly generation has completed successfully, the `.s` file remains
available even if GCC or the generated program fails. Incomplete assembly and
executable files are removed when possible.

## Verification

The Makefile provides three levels of checking:

```text
make test           ordinary regression suite
make test-sanitize  AddressSanitizer and UndefinedBehaviorSanitizer suite
make verify         both suites
```

Each regression suite prints `all regression tests passed` when it completes.
The cases cover token boundaries, comments, invalid characters, grammar rules,
arithmetic, constant folding and overflow, conditional evaluation, input and
output order, symbol names, generated paths, assembly order, the x86-64 calling
convention, and cleanup.

The most relevant fixtures for a focused review are:

| Topic | Source and tests |
|---|---|
| Comments and invalid characters | `scanner.c`, `tests/comments.micro`, `tests/bad_char.micro` |
| Grammar and lookahead | `parser.c`, the grammar in `README.md` |
| Constant folding and overflow | `semantic.c`, `tests/constant.micro`, `tests/fold_overflow.micro` |
| Conditional branch order | `parser.c`, `semantic.c`, `codegen.c`, `tests/arithmetic.micro` |
| Runtime-name collisions | `codegen.c`, `tests/symbols.micro` |
| ABI, PIE, and C library calls | `codegen.c`, generated `examples/example.s` |
| Output names and cleanup | `main.c`, the `run-tests` target |

## Packaging

The submission archive is created with:

```sh
make package
```

This target writes `../proyecto0.tgz`, extracts it in a temporary directory,
and runs the verification commands from the extracted copy. The archive has a
single top-level `project0/` directory containing the sources, headers,
Makefile, documentation, example, and test fixtures.

The top-level layout can be checked with:

```sh
tar -tzf ../proyecto0.tgz | cut -d/ -f1 | sort -u
```

The expected output is `project0`. The course demonstration must run on native
Linux; a virtual machine, an external boot device, or a computer shared between
groups does not satisfy that requirement.

Generated example files can be removed afterward with `make clean`.
