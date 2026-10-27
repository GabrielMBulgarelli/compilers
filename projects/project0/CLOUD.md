# Run Project 0 online: Linux x86-64

**[Open the executable Linux environment (GitHub Codespaces)](https://codespaces.new/GabrielMBulgarelli/compilers/tree/feat/project0-cloud-codespaces?quickstart=1)**

This is a browser-based Linux x86-64 development environment for the original MICRO compiler. It contains Ubuntu 24.04, GCC, GNU Make, Clang sanitizers, GNU Binutils, and GDB. You do not need to install anything on your local machine.

## Reviewer instructions

1. Sign in to GitHub, open the link above, and choose **Create codespace** (or resume one).
2. When the VS Code web editor opens, choose **Terminal > New Terminal**.
3. Run the complete verification:

```sh
bash projects/project0/run-cloud-tests.sh
```

Alternatively, in the web editor open **Terminal > Run Task** and choose **MICRO: Run all tests (Linux)**. The complete check runs `make verify` (regression checks and AddressSanitizer/UndefinedBehaviorSanitizer) and compiles/executes the sample input `2 3`.

Expected result at the end:

```text
Input: 2 3
Output: 5
PASS: MICRO compiled, its regression/sanitizer checks passed, and the example ran successfully.
```

## Try the compiler manually

```sh
cd projects/project0
make
printf '2 3\n' | ./micro examples/example.micro
```

Expected output: `5`. The compiler leaves these generated files:

- `examples/example.s`: GNU x86-64 assembly.
- `examples/example`: Linux ELF executable.

Use `make test` for regular regression checks, `make test-sanitize` for sanitizer checks, or `make verify` for both.

## Execution validation

[Open the CI workflow](https://github.com/GabrielMBulgarelli/compilers/actions/workflows/project0-linux.yml). It runs `make verify` on Ubuntu and independently builds the exact `.devcontainer/Dockerfile` image used for the browser environment and runs the same tests inside it.

The Codespaces link uses a feature branch until [the configuration pull request](https://github.com/GabrielMBulgarelli/compilers/pull/1) is merged.

**Access note:** Each user needs a GitHub account, permission to access the repository, and Codespaces availability. Each user starts their own environment; GitHub usage allowances/billing may apply. This is not anonymous public code execution.

**Course requirement:** The project README separately specifies native Linux for an in-person demonstration; cloud Codespaces does not automatically fulfill that requirement.
