# GCC Constant Folding and Constant Propagation

This directory contains the C experiments, generated GCC assembly, Konsole
screenshots, and LaTeX report for Exercise 1.4.

## Prerequisites

- GCC 16.1.1 or a compatible GCC release
- GNU Make
- A LaTeX installation with `latexmk` and `pdflatex`

## Build

Run `make all` from this directory. The nine assembly files are written to
`asm/`, and the compiled report is written to `report.pdf`. Run `make package`
to create `../tareacorta1.tgz`. The archive has `tareacorta1/` as its sole
top-level directory and is automatically rebuilt from a fresh extraction as
part of the packaging check.

The retained screenshots were produced on Fedora Linux 44 (x86-64) with GCC
16.1.1 20260515 (Red Hat 16.1.1-2), targeting `x86_64-redhat-linux`.

The submission metadata is stored in `metadata.tex`. Confirm that the name,
student ID, and course remain correct before submitting.
