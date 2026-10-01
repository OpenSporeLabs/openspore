#!/usr/bin/env python3
"""Capture the real SporeApp.exe listings the vftable rules are regressed against.

The committed bytes are the provenance, exactly as for the live ABI goldens: the
capture is a verbatim ``/disassemble_function`` response body and nothing about it
is asserted here. Re-capture with ``--record``; verify with no argument.

    python3 tests/capture_vftable_corpus.py            # verify
    python3 tests/capture_vftable_corpus.py --record   # re-record from live

Deliberately not named ``test_*.py``: this needs the live bridge, and the
discovered suite must stay hermetic.
"""
import json
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
if ROOT not in sys.path:
    sys.path.insert(0, ROOT)

from tests.capture_abi_golden import fetch, write_if_identical  # noqa: E402
from tests.vftable_corpus import CORPUS, corpus_path  # noqa: E402


def main():
    record = "--record" in sys.argv
    drift = 0
    written = 0
    for entry in CORPUS:
        va8 = entry["va8"]
        status, body, detail = fetch(va8)
        if status != 200:
            print("  0x%s: SKIP (%s)" % (va8, detail))
            continue
        try:
            payload = json.loads(body.decode("utf-8", "replace"))
        except ValueError:
            print("  0x%s: SKIP (bridge body is not JSON)" % va8)
            continue
        if not isinstance(payload.get("instructions"), list) or not payload["instructions"]:
            print("  0x%s: SKIP (no instruction listing)" % va8)
            continue
        outcome = write_if_identical(corpus_path(entry), body, force=record)
        if outcome == "drift":
            drift += 1
        elif outcome == "written":
            written += 1
    print("vftable corpus: %d written, %d drifted, %d entries"
          % (written, drift, len(CORPUS)))
    return 1 if (record and drift) or (not record and drift) else 0


if __name__ == "__main__":
    sys.exit(main())
