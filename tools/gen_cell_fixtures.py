#!/usr/bin/env python3
"""Obj35: freeze the Cell simulation contract fixtures.

Runs the C++ emitter (`sim_test --emit-fixtures`) twice and requires the
outputs to be byte-identical before writing
tests/fixtures/cell/fixtures.json — the same write-if-identical discipline
as tests/fixtures/gen_fixtures.py.

Usage:
  python3 tools/gen_cell_fixtures.py [--rebuild]

Stdlib only. The emitter prints its contract version on success.
"""
import argparse
import hashlib
import os
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
OUT = os.path.join(ROOT, "tests", "fixtures", "cell", "fixtures.json")
SIM_TEST = os.path.join(ROOT, "build", "src", "sim", "sim_test")


def build() -> None:
    subprocess.run(["cmake", "-S", ".", "-B", "build"], cwd=ROOT, check=True)
    subprocess.run(
        ["cmake", "--build", "build", "--target", "sim_test"],
        cwd=ROOT,
        check=True,
    )


def emit() -> bytes:
    proc = subprocess.run(
        [SIM_TEST, "--emit-fixtures", OUT],
        cwd=ROOT,
        capture_output=True,
        text=True,
    )
    if proc.returncode != 0:
        sys.stderr.write(proc.stdout + proc.stderr)
        raise SystemExit("emitter failed")
    print(proc.stdout, end="")
    with open(OUT, "rb") as fh:
        return fh.read()


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--rebuild", action="store_true", help="cmake configure + build first"
    )
    args = parser.parse_args()

    if args.rebuild:
        build()
    elif not os.path.exists(SIM_TEST):
        print("sim_test not found — use --rebuild", file=sys.stderr)
        sys.exit(1)

    first = emit()
    second = emit()
    if hashlib.sha256(first).hexdigest() != hashlib.sha256(second).hexdigest():
        print("FAIL: emitter is not deterministic", file=sys.stderr)
        sys.exit(1)
    print(
        "fixtures frozen: {} ({} bytes, deterministic)".format(
            os.path.relpath(OUT, ROOT), len(first)
        )
    )


if __name__ == "__main__":
    main()
