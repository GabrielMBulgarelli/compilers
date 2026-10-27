# Run Project 0 in GitHub Codespaces

You can compile and run the MICRO compiler in a Linux x86-64 cloud environment directly from your browser. No local Linux installation is required.

[Open Project 0 in GitHub Codespaces](https://codespaces.new/GabrielMBulgarelli/compilers/tree/feat/project0-cloud-codespaces?quickstart=1)

Sign in to GitHub, create your codespace, and wait until the terminal appears. The repository's `.devcontainer` configuration installs GCC, Clang, Make, Binutils, and debugger tooling. The `postCreateCommand` builds `micro` automatically.

In the terminal:

```sh
cd projects/project0
make
printf '2 3\n' | ./micro examples/example.micro
```

Expected output:

```text
5
```

The command generates `examples/example.s` (GNU x86-64 assembly) and `examples/example` (ELF executable). To run automated checks:

```sh
make test
make test-sanitize
make verify
```

Each GitHub user gets an independent codespace. They need GitHub access to this repository and must be able to use Codespaces on their account. This is **not** a single public shared shell or an anonymous web app. Users can work collaboratively using VS Code Live Share if needed.

The original project README requires a native Linux demonstration for the course. A cloud codespace is hosted in a VM-based environment and should not be assumed to satisfy that specific demonstration requirement.

GitHub Codespaces usage is subject to each user's account allowance and billing settings.
