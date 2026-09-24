#!/usr/bin/env python3
"""CS-04 differential test: C++ RW4 walker vs the python oracle.

Runs the C++ `rw4_test --dump` over every 0x2F4E681B record in
SPORE/Data/Spore_Content.package and diffs the canonical section-walk lines
against the python oracle (`tools/spore/rw4/rw4.py::describe`). They must be
byte-identical for all 1,131 records. Skips gracefully when SPORE/ or the
build tree is absent.
"""
import os
import subprocess
import sys
import unittest

_HERE = os.path.dirname(os.path.abspath(__file__))
_REPO = os.path.join(_HERE, '..')
_TOOLS = os.path.join(_REPO, 'tools', 'spore')
sys.path.insert(0, os.path.join(_TOOLS, 'dbpf'))
sys.path.insert(0, os.path.join(_TOOLS, 'rw4'))

PKG = os.path.join(_REPO, 'SPORE', 'Data', 'Spore_Content.package')
BIN = os.path.join(_REPO, 'build', 'src', 'assets', 'rw4_test')


class TestRw4Differential(unittest.TestCase):
    def setUp(self):
        if not os.path.exists(PKG):
            self.skipTest("Spore_Content.package not available")
        if not os.path.exists(BIN):
            self.skipTest("rw4_test binary not built")

    def test_cpp_matches_oracle(self):
        import dbpf
        from rw4 import describe

        data, items = dbpf.read(PKG)
        py_lines = []
        for it in items:
            if it['type'] == 0x2F4E681B:
                py_lines.append(describe(dbpf.getdata(data, it)))

        r = subprocess.run([BIN, '--dump', PKG],
                           capture_output=True, text=True, timeout=120)
        self.assertEqual(r.returncode, 0, r.stdout + r.stderr)
        cpp_lines = [ln for ln in r.stdout.splitlines() if ' obj=' in ln]

        self.assertEqual(len(cpp_lines), len(py_lines),
                         "record count mismatch")
        self.assertEqual(len(py_lines), 1131, "expected 1131 rw4 records")
        for i, (c, p) in enumerate(zip(cpp_lines, py_lines)):
            self.assertEqual(c, p, "record %d walk differs" % i)


if __name__ == '__main__':
    unittest.main()
