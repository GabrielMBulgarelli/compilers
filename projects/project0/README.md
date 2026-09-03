# Project 0: Micro Compiler

This repository contains a compiler for the Micro language described in
Chapter 2 of Fischer-LeBlanc. It is written in C and includes the constant
evaluation from Exercise 8 and the conditional expression from Exercise 10.
Given one Micro source file, the compiler produces x86-64 assembly, asks GCC
to build it, and runs the resulting program.

Both the scanner and the recursive-descent parser are handwritten. The parser
keeps one token of lookahead and emits code as it recognizes the input, so
there is no AST or intermediate representation. The implementation does not
depend on `lex`, `flex`, `yacc`, or another parser generator.

## Requirements

The regular build needs a native 64-bit Linux system, GCC, and GNU Make.
Running the sanitizer checks also requires Clang with the AddressSanitizer and
UndefinedBehaviorSanitizer runtimes installed.

## Build

Run `make` from the `project0` directory:

```sh
make
```

The command builds an executable named `micro`. To remove it, along with the
files generated under `examples/`, use:

```sh
make clean
```

## Compiler input

`micro` expects one argument: the path of the source program.

```sh
./micro path/to/program.micro
```

There is no menu or filename prompt. The file must contain a complete Micro
program and at least one statement. This is the smallest valid example:

```text
begin
x := 0;
end
```

For that reason, `begin end` by itself is rejected.

An identifier starts with a letter and may contain letters, digits, or
underscores after that. Its maximum length is 32 characters. The words
`begin`, `end`, `read`, and `write` are reserved. Integer literals are decimal
and must fit in a signed 32-bit value. Spaces and line breaks are ignored. A
comment begins with `--` and ends at the next newline or at the end of the
file.

## Compiler output and execution

When the input is valid, `micro` carries out the complete process:

1. It writes GNU x86-64 assembly next to the source file.
2. It calls GCC to assemble and link that file.
3. It runs the executable produced by GCC.

The compiler stays quiet when those steps succeed. Anything printed in the
terminal comes from the compiled Micro program. `write` prints each value as a
signed decimal integer followed by a newline, while `read` takes signed decimal
integers from standard input.

For example, if `examples/example.micro` contains:

```text
begin
read(first, second);
sum := first + second;
choice := (sum | sum | 0);
write(choice);
end
```

it can be compiled and run with:

```sh
printf '2 3\n' | ./micro examples/example.micro
```

The program prints:

```text
5
```

The same command leaves `examples/example.s` and `examples/example` beside
the original source. Output filenames follow these rules:

| Source path | Assembly file | Executable |
|---|---|---|
| `foo.micro` | `foo.s` | `foo` |
| `.micro` | `.micro.s` | `.micro.out` |
| `x` | `x.s` | `x.out` |

Once assembly generation finishes, the `.s` file is kept even if GCC or the
compiled program fails afterward. If an assembly file or executable is left
incomplete, the compiler removes it when possible.

## Errors and exit status

The compiler returns a nonzero status for lexical, syntax, semantic, file, or
memory errors. It does the same if GCC cannot build the generated assembly or
if the compiled program cannot be started. Diagnostics go to standard error
when there is useful information to report.

Invalid Micro input is never linked. Likewise, an executable is not run when
linking fails. Truncated and malformed files are handled as errors instead of
causing a segmentation fault.

A successful compile, link, and run returns zero. The generated `main`
function also returns zero explicitly.

## Micro language

The compiler recognizes this grammar:

```text
system_goal    -> program SCANEOF
program        -> BEGIN statement_list END
statement_list -> statement { statement }
statement      -> ID := expression ;
                | READ ( id_list ) ;
                | WRITE ( expr_list ) ;
id_list        -> ID { , ID }
expr_list      -> expression { , expression }
expression     -> primary { ( + | - ) primary }
primary        -> ID
                | INTLITERAL
                | ( expression )
                | ( expression | expression | expression )
```

In `(E1 | E2 | E3)`, a nonzero `E1` selects `E2`; zero selects `E3`. Only the
selected branch runs. Addition and subtraction associate from left to right.

All Micro values use signed 32-bit integers. The compiler rejects literals
outside that range, as well as constant expressions whose result does not fit.
Addition and subtraction performed while the generated program is running use
regular 32-bit x86 arithmetic and do not check for overflow.

## Implementation overview

Compilation happens in one pass through the parser:

```text
scanner -> recursive-descent parser -> semantic actions -> x86-64 assembly
        -> GCC -> generated executable -> execution
```

Variables written by the user and temporaries created by the compiler have
separate assembler namespaces. A Micro variable named `main`, `printf`, or
`scanf` therefore cannot collide with the runtime symbols. Data references are
RIP-relative, which allows the output to link as a PIE. Calls to `read` and
`write` use the C library functions `scanf` and `printf`.

The scanner keeps one character of lookahead. After recognizing a token, it
leaves the first unrelated character ready for the next scan. This matters for
a single minus sign and for the character immediately following an identifier
or integer literal.

## Verification

The normal regression checks run with:

```sh
make test
```

The sanitizer version builds the compiler with AddressSanitizer and
UndefinedBehaviorSanitizer before running the same checks:

```sh
make test-sanitize
```

To run both modes in sequence:

```sh
make verify
```

The cases exercise tokenization, grammar rules, invalid input, arithmetic,
constant evaluation, input and output order, conditional expressions, symbol
names, output paths, assembly order, the x86-64 calling convention, and the
handling of generated files. The Makefile contains the test orchestration, so
the submission does not need a separate shell script for it.

## Submission archive

The release archive is built and checked with:

```sh
make package
```

It is written to:

```text
/home/gabriel/Code/Compilers/projects/proyecto0.tgz
```

The archive has `project0/` at its root. It contains the C sources, headers,
Makefile, README, test fixtures, and example program. As a final check, the
`package` target extracts a clean copy and runs the verification commands from
that copy.

The course demonstration must be run on native Linux. A virtual machine, an
external boot device, or a computer shared between groups does not meet that
requirement.
