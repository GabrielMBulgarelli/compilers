# Project 0 review walkthrough

This guide is a 5-8 minute route through the complete Micro compiler. Use it
during the live review. The [README](README.md) remains the full reference for
the language, build, diagnostics, tests, and submission archive.

## Before the review

Run these commands from the `project0` directory before the reviewer arrives:

```sh
make verify
make package
```

`make verify` runs the ordinary and sanitizer regression suites. Each suite
prints `all regression tests passed`. `make package` creates
`../proyecto0.tgz`, extracts it into a temporary directory, and verifies the
extracted copy. Leave the terminal in the `project0` directory for the live
commands below.

## 1. State the goal and constraints (0:00-0:40)

Say:

> This is a compiler for the Micro language, written in C17. It accepts one
> source file, translates it directly to GNU x86-64 assembly, asks GCC to build
> the generated program, and runs that program. The scanner and parser are
> handwritten. There is no parser generator, AST, or intermediate
> representation.

Show the project root and point out that the submitted implementation consists
of C sources and headers, the Makefile, tests, the example, and documentation.

## 2. Explain the T-diagram and pipeline (0:40-1:20)

The T-diagram identifies the compiler's source language, target language, and
implementation language:

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

Connect that diagram to the actual execution path:

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

`main.c` owns the outer workflow: paths, files, compilation, GCC, execution,
exit status, and cleanup. The parser calls semantic actions as it recognizes
the program, so code generation happens without building an AST or IR.

## 3. Tour the implementation (1:20-2:10)

Use this order rather than reading every file line by line:

| File | What to explain | Useful review anchor |
|---|---|---|
| `micro.h` | Shared tokens and expression records | `token`, `expr_rec` |
| `scanner.c` | Character lookahead, tokens, comments, identifier and integer checks | `scanner_next` |
| `parser.c` | One-token lookahead and grammar procedures | `primary`, `expression`, `statement`, `system_goal` |
| `semantic.c` | Symbols, constant folding, temporaries, and conditional labels | `gen_infix`, `conditional_begin` |
| `codegen.c` | Direct x86-64 emission, libc I/O, and separate assembler namespaces | `codegen_binary`, `codegen_read`, `codegen_finish` |
| `main.c` | Output paths, GCC invocation, execution, status decoding, and cleanup | `derive_output_paths`, `link_generated_program`, `cleanup_outputs` |
| `Makefile` | Builds, regression tests, sanitizers, and archive verification | `verify`, `package` |

Tie the parser functions back to the grammar in the README. `primary` handles
identifiers, literals, parenthesized expressions, and conditional expressions.
`expression` implements left-associative addition and subtraction. `statement`
selects assignment, `read`, or `write`.

## 4. Run one complete example (2:10-3:30)

Show the input program:

```sh
sed -n '1,80p' examples/example.micro
```

Then compile and run it through the Micro compiler:

```sh
printf '2 3\n' | ./micro examples/example.micro
```

Expected output:

```text
5
```

Point out the two generated artifacts:

```sh
ls -l examples/example.s examples/example
grep -nE 'main:|call (scanf|printf)|micro_var_|\.Lmicro_' examples/example.s
```

Explain the evidence in the assembly:

- `micro_var_` prefixes keep user identifiers separate from runtime symbols.
- RIP-relative operands support normal PIE linking.
- `scanf@PLT` and `printf@PLT` implement Micro `read` and `write`.
- `.Lmicro_false_` and `.Lmicro_end_` labels implement the selected conditional
  branch at runtime.

## 5. Explain the important internals (3:30-4:50)

Keep this section focused on design decisions that are easy to verify in the
source:

1. `scanner.c` retains one character of lookahead. A single `-` becomes
   subtraction, while `--` starts a comment. Identifiers are limited to 32
   characters, and integer literals must fit in `int32_t`.
2. `parser.c` retains one token of lookahead. Each function matches one grammar
   level and calls semantic actions immediately.
3. `semantic.c::gen_infix` folds an operation when both operands are literals.
   It performs the calculation in `int64_t` and rejects results outside the
   signed 32-bit range. Nonconstant expressions receive compiler temporaries.
4. Conditional expressions allocate false and end labels. The emitted jump
   skips the unselected branch, so only the chosen branch executes.
5. `codegen.c` emits a complete `main`, observes the x86-64 calling convention,
   returns zero, and marks the stack as non-executable.

If the review must fit in five minutes, finish this section after explaining
constant folding and conditionals, then move to the failure case.

## 6. Show a controlled failure (4:50-5:30)

Run a source file containing the unsupported `*` character:

```sh
./micro tests/bad_char.micro; printf 'exit=%s\n' "$?"
test ! -e tests/bad_char.s && echo 'incomplete assembly removed'
```

Expected observations:

- The compiler reports a lexical error with the source path, line, and column.
- The exit status is nonzero.
- GCC and the generated program do not run.
- The incomplete assembly file is removed.

Use this case to summarize the error contract: lexical, syntax, semantic, file,
allocation, GCC, and generated-program failures all return a nonzero status.

## 7. Close with verification and packaging (5:30-6:30)

Show the Makefile targets already run during preparation:

```text
make test           ordinary regression suite
make test-sanitize  AddressSanitizer and UndefinedBehaviorSanitizer suite
make verify         both suites
make package        verified submission archive
```

Confirm the archive has one top-level directory:

```sh
tar -tzf ../proyecto0.tgz | cut -d/ -f1 | sort -u
```

Expected output:

```text
project0
```

Close with this requirement check:

| Requirement | Evidence |
|---|---|
| Handwritten scanner | `scanner.c` |
| One-token recursive-descent parser | `parser.c` |
| Direct assembly generation, without AST or IR | Parser calls into `semantic.c` and `codegen.c` |
| Signed 32-bit rules and constant folding | `micro.h`, `scanner.c`, `semantic.c` |
| Conditional expressions | Parser, semantic actions, emitted branch labels |
| GCC build and generated-program execution | `main.c` |
| Ordinary and sanitizer regressions | `make verify` |
| Required archive layout and clean rebuild | `make package` |

## Reviewer question index

| If the reviewer asks about... | Open... |
|---|---|
| Token boundaries, comments, or bad characters | `scanner.c`, `tests/comments.micro`, `tests/bad_char.micro` |
| Grammar and lookahead | `parser.c`, the grammar in `README.md` |
| Constant folding or overflow | `semantic.c`, `tests/constant.micro`, `tests/fold_overflow.micro` |
| Conditional evaluation and branch order | `parser.c`, `semantic.c`, `codegen.c`, `tests/arithmetic.micro` |
| User names colliding with runtime names | `codegen.c`, `tests/symbols.micro` |
| x86-64 ABI, PIE, or libc calls | `codegen.c`, generated `examples/example.s` |
| Output names, shell-safe paths, or cleanup | `main.c`, the `run-tests` target |
| Test coverage and submission contents | `Makefile`, `tests/`, `make package` |

After the review, remove the generated example files if needed:

```sh
make clean
```
