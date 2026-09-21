"""Cell Stage manifest determinism oracle (Obj16).

Runs the built `cell_stage` binary twice against the real package and
asserts the stdout manifest is identical. Skips cleanly when SPORE/ is
absent or the binary is not built, so CI without the game passes.

Run from the repo root:

    python3 -m unittest discover -s tests -t . -v
"""
import os
import subprocess
import tempfile
import unittest

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PKG = os.path.join(ROOT, 'SPORE', 'Data', 'Spore_Content.package')
BIN = os.path.join(ROOT, 'build', 'src', 'cell_stage')

HAVE_PKG = os.path.exists(PKG)


class TestCellStageManifest(unittest.TestCase):

    @unittest.skipUnless(HAVE_PKG, 'SPORE/ absent')
    def test_manifest_deterministic(self):
        if not os.path.exists(BIN):
            self.skipTest('cell_stage not built (run cmake --build build)')
        outs = []
        for _ in range(2):
            workdir = tempfile.mkdtemp(prefix='cellstage-', dir='/tmp')
            proc = subprocess.run([BIN, PKG], capture_output=True, text=True,
                                  cwd=workdir, timeout=300)
            self.assertEqual(proc.returncode, 0, proc.stdout + proc.stderr)
            outs.append(proc.stdout)
        self.assertIn('CELLSTAGE-MANIFEST v1', outs[0])
        for line in outs[0].splitlines():
            if line.startswith('entity role='):
                self.assertIn('group=0x', line)
                self.assertIn('verts=', line)
        self.assertEqual(outs[0], outs[1],
                         'cell_stage manifest not deterministic')


if __name__ == '__main__':
    unittest.main()
