#!/usr/bin/env python3
"""Capture real SporeApp.exe disassembly into committed ABI-inference goldens.

Deliberately NOT named ``test_*.py``: this needs the live GhidraMCP headless
bridge, and the discovered suite must stay hermetic. Mirrors
``tests/diff_real.py`` in every respect that matters -- the ``--record`` /
verify split, the ``write_if_identical`` byte guard, the one-line summary and
the non-zero exit on drift.

    python3 tests/capture_abi_golden.py            # verify goldens against live
    python3 tests/capture_abi_golden.py --record   # re-record from live

What it does, per target in ``tests/abi_fixtures.LIVE_TARGETS``:

1. ``GET http://127.0.0.1:8089/disassemble_function?address=0x<va>`` and write
   the **verbatim** response body to
   ``tests/fixtures/abi/live/<va8>_<slug>.json``. The committed bytes *are* the
   provenance, so nothing about the capture is asserted by this script.
2. Feed the committed bytes to ``abi_infer.analyze`` and write the resulting
   record to ``tests/expected/abi/live/<va8>_<slug>.json``.

``tests/test_abi_inference.py`` then replays the committed captures with no
bridge at all, which is what makes the real-function assertions CI-safe.

The bridge command line is documented in AGENTS.md. If the bridge is down,
``--record`` fails loudly and plain verify mode is skipped with a clear message
rather than a traceback, so a fresh checkout is a no-op.
"""
import hashlib
import json
import os
import sys
import urllib.error
import urllib.request

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
if ROOT not in sys.path:
    sys.path.insert(0, ROOT)

from tests import abi_fixtures as fx  # noqa: E402
from tools.reconstruction_tooling import abi_infer  # noqa: E402
from tools.reconstruction_tooling.models import canonical_json  # noqa: E402

BRIDGE = os.environ.get("OPENSPORE_GHIDRA_BRIDGE", "http://127.0.0.1:8089")
TIMEOUT = float(os.environ.get("OPENSPORE_GHIDRA_TIMEOUT", "30"))


def write_if_identical(path, blob, force=False):
    """House byte guard, shared in spirit with tests/fixtures/gen_fixtures.py."""
    name = os.path.relpath(path, ROOT)
    if os.path.exists(path):
        with open(path, "rb") as handle:
            current = handle.read()
        if current == blob:
            print("  %s: identical (%d bytes)" % (name, len(blob)))
            return "identical"
        if not force:
            print("  %s: DRIFT (disk %d bytes, live %d bytes)" % (name, len(current), len(blob)))
            return "drift"
        with open(path, "wb") as handle:
            handle.write(blob)
        print("  %s: rewritten (%d bytes)" % (name, len(blob)))
        return "written"
    os.makedirs(os.path.dirname(path), exist_ok=True)
    with open(path, "wb") as handle:
        handle.write(blob)
    print("  %s: written (%d bytes)" % (name, len(blob)))
    return "written"


def fetch(va8):
    """GET /disassemble_function and return (status, body_bytes, detail)."""
    url = "%s/disassemble_function?address=0x%s" % (BRIDGE, va8)
    try:
        with urllib.request.urlopen(url, timeout=TIMEOUT) as response:
            return response.status, response.read(), url
    except urllib.error.URLError as error:
        return None, b"", "%s (%s)" % (url, error)
    except OSError as error:
        return None, b"", "%s (%s)" % (url, error)


def check_connection():
    url = "%s/check_connection" % BRIDGE
    try:
        with urllib.request.urlopen(url, timeout=TIMEOUT) as response:
            return True, response.read().decode("utf-8", "replace").strip()
    except (urllib.error.URLError, OSError) as error:
        return False, "%s (%s)" % (url, error)


def expected_record(document):
    return abi_infer.analyze(document)


def main(argv):
    record_mode = "--record" in argv
    unknown = [item for item in argv if item not in ("--record", "--verbose")]
    if unknown:
        sys.exit("FATAL: unknown argument(s): %s" % " ".join(unknown))
    verbose = "--verbose" in argv

    ok, detail = check_connection()
    if not ok:
        message = ("Ghidra bridge not reachable at %s -- live ABI capture skipped. "
                   "This is expected on a fresh checkout / CI; the hermetic suite in "
                   "tests/test_abi_inference.py replays the committed captures."
                   % BRIDGE)
        if record_mode:
            sys.exit("FATAL: --record needs the live bridge; %s" % detail)
        print(message)
        print("  checked: %s" % detail)
        return 0
    if verbose:
        print("bridge: %s" % detail)

    os.makedirs(fx.LIVE_DIR, exist_ok=True)
    os.makedirs(fx.LIVE_EXPECT_DIR, exist_ok=True)

    drift = []
    for va8, slug, _convention, _side, _bytes, _note in fx.LIVE_TARGETS:
        print("%s %s:" % (va8, slug))
        capture_path = fx.live_path(va8, slug)
        golden_path = fx.live_expected_path(va8, slug)

        if record_mode:
            status, body, where = fetch(va8)
            if status != 200:
                sys.exit("FATAL: %s returned %s" % (where, status))
            try:
                document = json.loads(body.decode("utf-8"))
            except ValueError as error:
                sys.exit("FATAL: %s did not return JSON: %s" % (where, error))
            if not isinstance(document.get("instructions"), list):
                sys.exit("FATAL: %s has no 'instructions' list: %r" % (where, document))
            outcome = write_if_identical(capture_path, body, force=True)
        else:
            if not os.path.isfile(capture_path):
                sys.exit("FATAL: missing committed capture %s; run with --record"
                         % os.path.relpath(capture_path, ROOT))
            status, body, where = fetch(va8)
            if status != 200:
                print("  live fetch failed (%s) -- comparing the committed capture "
                      "against its golden only" % where)
            outcome = "committed"

        with open(capture_path, "rb") as handle:
            committed = handle.read()
        try:
            document = json.loads(committed.decode("utf-8"))
        except (ValueError, UnicodeDecodeError) as error:
            sys.exit("FATAL: committed capture %s is not valid JSON (%s); re-record "
                     "with --record" % (os.path.relpath(capture_path, ROOT), error))
        if not isinstance(document.get("instructions"), list):
            sys.exit("FATAL: committed capture %s has no 'instructions' list; "
                     "re-record with --record" % os.path.relpath(capture_path, ROOT))
        if status == 200 and committed != body:
            print("  CAPTURE DRIFT: live response differs from the committed bytes")
            print("    live      sha256 %s" % hashlib.sha256(body).hexdigest())
            print("    committed sha256 %s" % hashlib.sha256(committed).hexdigest())
            drift.append(va8 + " capture")
        record = canonical_json(expected_record(document)).encode("utf-8")
        outcome = write_if_identical(golden_path, record, force=record_mode)
        if outcome == "drift":
            drift.append(va8 + " golden")
            if verbose:
                print("    " + "\n    ".join(
                    fx.semantic_diff(fx.read_json(golden_path), json.loads(record))))

    total = len(fx.LIVE_TARGETS)
    if drift:
        print("LIVE ABI GOLDEN DRIFT (%d): %s" % (len(drift), ", ".join(drift)))
        print("(re-record with: python3 tests/capture_abi_golden.py --record)")
        return 1
    verb = "RECORDED" if record_mode else "VERIFIED"
    print("%s %d fixtures (no drift)" % (verb, total))
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
