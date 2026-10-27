FROM mcr.microsoft.com/devcontainers/base:ubuntu-24.04

# Native Linux x86-64 C toolchain for MICRO, including sanitizer runtimes.
RUN apt-get update \
    && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
       build-essential \
       clang \
       libclang-rt-dev \
       binutils \
       gdb \
       file \
    && rm -rf /var/lib/apt/lists/*
