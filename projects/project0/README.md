# Project 0: Micro Compiler

Implement a small compiler in C for the Micro language presented in Chapter 2
of Fischer–LeBlanc. The compiler must include compile-time constant evaluation
from Exercise 8 and conditional expressions from Exercise 10.

The program accepts one Micro source file, translates it directly to x86-64
assembly, invokes GCC to build the generated program, and runs that program.
The scanner and recursive-descent parser must be handwritten. Do not use
`lex`, `flex`, `yacc`, another parser generator, an AST, or an intermediate
representation.

## Language

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

The conditional expression `(E1 | E2 | E3)` evaluates to `E2` when `E1` is
nonzero and to `E3` otherwise. Addition and subtraction associate from left to
right. Values and decimal integer literals use signed 32-bit integers.

Identifiers begin with a letter, may continue with letters, digits, or
underscores, and are limited to 32 characters. The reserved words are `begin`,
`end`, `read`, and `write`. Whitespace is ignored, and a `--` comment continues
through the next newline or the end of the file.

## Deliverables

Submit the C sources and headers, Makefile, documentation, test fixtures, and
an example Micro program. The project must build and run on native 64-bit
Linux.
