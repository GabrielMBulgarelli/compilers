#!/usr/bin/env python3
"""Byte-exact comparison of original PR0 archive with committed Git blobs."""
import argparse
from datetime import datetime, timezone
import gzip
import hashlib
from io import BytesIO
import json
from pathlib import Path, PurePosixPath
import subprocess
import sys
import tarfile

PROJECT = "projects/project0"
CLOUD_ONLY = {"CLOUD.md", "run-cloud-tests.sh", "verify_submission.py"}
LIMIT = 256 * 1024 * 1024


def sha(blob):
    return hashlib.sha256(blob).hexdigest()


def git(repo, *args):
    p = subprocess.run(["git", "-C", str(repo), *args],
                       capture_output=True, check=False)
    if p.returncode:
        raise ValueError(p.stderr.decode(errors="replace"))
    return p.stdout


def unpack(filename):
    if filename.stat().st_size > 100 * 1024 * 1024:
        raise ValueError("Compressed file exceeds 100 MiB safety limit")
    data = filename.read_bytes()
    for _ in range(3):
        if not data.startswith(b"\x1f\x8b"):
            break
        with gzip.GzipFile(fileobj=BytesIO(data)) as f:
            data = f.read(LIMIT + 1)
        if len(data) > LIMIT:
            raise ValueError("Decompressed archive exceeds 256 MiB")
    if data.startswith(b"\x1f\x8b"):
        raise ValueError("Unsupported gzip nesting (>3 layers)")
    files = {}
    total = 0
    with tarfile.open(fileobj=BytesIO(data), mode="r:") as tf:
        members = tf.getmembers()
        rooted = any("project0" in PurePosixPath(m.name).parts
                     for m in members if m.isfile())
        for member in members:
            if member.isdir():
                continue
            if not member.isfile():
                raise ValueError("Non-regular archive member: " + member.name)
            if member.name.startswith("/"):
                raise ValueError("Absolute path: " + member.name)
            parts = [p for p in PurePosixPath(member.name).parts if p != "."]
            if not parts or ".." in parts:
                raise ValueError("Unsafe path: " + member.name)
            if rooted:
                if "project0" not in parts:
                    raise ValueError("Outside project0/: " + member.name)
                parts = parts[parts.index("project0") + 1:]
            if not parts:
                continue
            path = "/".join(parts)
            if path in files:
                raise ValueError("Duplicate archive member: " + path)
            if member.size > 25 * 1024 * 1024:
                raise ValueError("Oversized member: " + path)
            content = tf.extractfile(member).read(25 * 1024 * 1024 + 1)
            if len(content) != member.size:
                raise ValueError("Truncated archive member: " + path)
            total += len(content)
            if total > LIMIT:
                raise ValueError("Archive files exceed 256 MiB in total")
            files[path] = content
    if not files:
        raise ValueError("Archive has no regular files")
    return files


def git_files(repo, commit):
    listing = git(repo, "ls-tree", "-r", "-z", "--name-only", commit, "--", PROJECT)
    prefix = PROJECT + "/"
    paths = [p.decode() for p in listing.split(b"\0") if p]
    return {p[len(prefix):]: git(repo, "show", commit + ":" + p)
            for p in paths if p.startswith(prefix)}


def main():
    cli = argparse.ArgumentParser(description=__doc__)
    cli.add_argument("archive", type=Path)
    cli.add_argument("--revision", default="HEAD")
    cli.add_argument("--output-dir", type=Path,
                     default=Path("evidence/micro-submission"))
    args = cli.parse_args()
    repo = Path(__file__).resolve().parents[2]

    try:
        commit = git(repo, "rev-parse", "--verify",
                     args.revision + "^{commit}").decode().strip()
        file_archive = args.archive.expanduser().resolve()
        archive_hash = sha(file_archive.read_bytes())
        submitted = unpack(file_archive)
        github = git_files(repo, commit)
        if not github:
            raise ValueError("No matching Git project files")
        rows = []
        for path in sorted(set(submitted) | set(github)):
            a, b = submitted.get(path), github.get(path)
            if a is None:
                status = "CLOUD_ONLY" if path in CLOUD_ONLY else "GITHUB_ONLY"
            elif b is None:
                status = "MISSING_FROM_GITHUB"
            else:
                status = "IDENTICAL" if a == b else "DIFFERENT"
            rows.append(dict(path=path, status=status,
                             archive_sha256=sha(a) if a is not None else None,
                             github_sha256=sha(b) if b is not None else None))
        num = lambda status: sum(r["status"] == status for r in rows)
        compiler_paths = {r["path"] for r in rows
                          if PurePosixPath(r["path"]).suffix in {".c", ".h"}}
        code_matches = sum(r["status"] == "IDENTICAL"
                           and r["path"] in compiler_paths for r in rows)
        summary = {
            "original_files": len(submitted),
            "identical": num("IDENTICAL"),
            "different": num("DIFFERENT"),
            "missing_from_github": num("MISSING_FROM_GITHUB"),
            "unexpected_github_only": num("GITHUB_ONLY"),
            "cloud_only": num("CLOUD_ONLY"),
            "compiler_code_files": len(compiler_paths),
            "compiler_code_identical": code_matches,
        }
        passed = (summary["original_files"] > 0
                  and len(compiler_paths) > 0
                  and code_matches == len(compiler_paths)
                  and num("IDENTICAL") == len(submitted)
                  and num("GITHUB_ONLY") == 0)
        outcome = "PASS" if passed else "FAIL"
        report = {
            "schema": "micro-pr0-byte-identity-v1",
            "generated_at_utc": datetime.now(timezone.utc).isoformat(),
            "result": outcome,
            "archive": {"filename": file_archive.name,
                        "bytes": file_archive.stat().st_size,
                        "sha256": archive_hash},
            "git": {"repository": "GabrielMBulgarelli/compilers",
                    "commit": commit, "directory": PROJECT},
            "summary": summary, "files": rows,
        }
        args.output_dir.mkdir(parents=True, exist_ok=True)
        json_file = args.output_dir / "verification.json"
        md_file = args.output_dir / "verification.md"
        json_file.write_text(json.dumps(report, indent=2, ensure_ascii=False) + "\n")
        tick = chr(96)
        lines = [
            "# Proyecto 0 — Verificación SHA-256 de identidad",
            "",
            "**Resultado:** " + outcome,
            "",
            "- Archivo original: " + tick + file_archive.name + tick,
            "- SHA-256 del archivo recibido: " + tick + archive_hash + tick,
            "- Commit Git comparado: " + tick + commit + tick,
            "- Código C/H idéntico: **{}/{}**".format(
                code_matches, len(compiler_paths)),
            "- Todos los archivos del envío idénticos: **{}/{}**".format(
                num("IDENTICAL"), len(submitted)),
            "- Diferentes: {}; ausentes en GitHub: {}; extras inesperados: {}".format(
                num("DIFFERENT"), num("MISSING_FROM_GITHUB"), num("GITHUB_ONLY")),
            "",
            "## Archivos y hashes",
            "",
            "| Archivo | Resultado | SHA-256 envío | SHA-256 Git |",
            "|---|---|---|---|",
        ]
        for r in rows:
            lines.append("| {}{}{} | {} | {} | {} |".format(
                tick, r["path"].replace("|", r"\|"), tick, r["status"],
                r["archive_sha256"] or "—", r["github_sha256"] or "—"))
        lines.extend([
            "",
            "## Interpretación",
            "",
            "Los archivos comparados son los bytes originales del archivo comprimido",
            "y los objetos inmutables del commit de Git indicado, NO el árbol editable.",
            "Las adiciones CLOUD_ONLY son utilidades de ejecución/verificación en nube.",
            "La coincidencia de hashes prueba identidad entre los objetos comparados;",
            "no prueba por sí sola que el archivo suministrado sea el mismo enviado",
            "al profesor. Conservar también el correo/recibo de entrega y obtener",
            "el archivo directamente de esa fuente.",
            "Los metadatos de empaquetado pueden cambiar sin cambiar el código.",
            "",
        ])
        md_file.write_text("\n".join(lines), encoding="utf-8")
        print("Verification: " + outcome)
        print("Original archive SHA-256: " + archive_hash)
        print("Compared Git commit: " + commit)
        print("Identical C/H code files: {}/{}".format(
            code_matches, len(compiler_paths)))
        print("Identical original files: {}/{}".format(
            num("IDENTICAL"), len(submitted)))
        print("Evidence: " + str(md_file) + " and " + str(json_file))
        return 0 if passed else 1
    except (OSError, ValueError, tarfile.TarError) as e:
        print("Verification error: " + str(e), file=sys.stderr)
        return 2


if __name__ == "__main__":
    sys.exit(main())
