#!/usr/bin/env bash
set -euo pipefail

cd "$(dirname "$0")"

printf '\n=== MICRO: Linux environment ===\n'
uname -srm
gcc --version | head -n 1
clang --version | head -n 1

printf '\n=== MICRO: compiler and regression tests ===\n'
make verify

printf '\n=== MICRO: end-to-end example ===\n'
output="$(printf '2 3\n' | ./micro examples/example.micro)"
printf 'Input: 2 3\nOutput: %s\n' "$output"
if [[ "$output" != 5 ]]; then
  printf 'FAIL: expected result 5\n' >&2
  exit 1
fi

printf '\n=== MICRO: generated Linux executable ===\n'
file examples/example
file examples/example.s

printf '\nPASS: MICRO compiled, its regression/sanitizer checks passed, and the example ran successfully.\n'
