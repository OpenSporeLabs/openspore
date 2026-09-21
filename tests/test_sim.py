"""Cell Stage sim replay determinism oracle (Obj17 part A).

Runs the built `cell_stage` binary in --input sim mode with scripted
JSON-lines inputs and asserts:

  - forward thrust moves the player along its heading; zero input does not
  - a script that drives the player onto food_a emits an `eat` event with
    growMeter=1, and the final PPM differs from a no-eat baseline
    (culled food + moved player change the render)
  - two runs of the same script print byte-identical manifests (and
    byte-identical PPMS)

Skips cleanly when SPORE/ is absent or the binary is not built, so CI
without the game passes.

Run from the repo root:

    python3 -m unittest discover -s tests -t . -v
"""
import json
import os
import subprocess
import tempfile
import unittest

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PKG = os.path.join(ROOT, 'SPORE', 'Data', 'Spore_Content.package')
BIN = os.path.join(ROOT, 'build', 'src', 'cell_stage')

HAVE_PKG = os.path.exists(PKG)


def write_script(path, rows):
    with open(path, 'w') as f:
        for row in rows:
            f.write(json.dumps(row) + '\n')


def read_bytes(path):
    with open(path, 'rb') as f:
        return f.read()


def run_sim(script):
    """Runs cell_stage in sim mode; returns (stdout, ppm path)."""
    workdir = tempfile.mkdtemp(prefix='cellsim-', dir='/tmp')
    proc = subprocess.run([BIN, PKG, '--input', script],
                          capture_output=True, text=True, cwd=workdir,
                          timeout=300)
    assert proc.returncode == 0, proc.stdout + proc.stderr
    return proc.stdout, os.path.join(workdir, 'cell_stage.ppm')


def parse_pos(manifest):
    for line in manifest.splitlines():
        if line.startswith('player pos='):
            vals = line.split('pos=', 1)[1].split(' heading', 1)[0].split()
            return tuple(float(x) for x in vals)
    raise AssertionError('manifest has no player pos= line')


def parse_grow(manifest):
    for line in manifest.splitlines():
        if 'growMeter=' in line:
            return int(line.split('growMeter=')[1].strip())
    raise AssertionError('manifest has no growMeter field')


@unittest.skipUnless(HAVE_PKG, 'SPORE/ absent')
class TestSimReplay(unittest.TestCase):

    def setUp(self):
        if not os.path.exists(BIN):
            self.skipTest('cell_stage not built (run cmake --build build)')
        self.tmp = tempfile.mkdtemp(prefix='cellsim-scripts-', dir='/tmp')

    def _script(self, name, rows):
        path = os.path.join(self.tmp, name)
        write_script(path, rows)
        return path

    def test_move_deterministic(self):
        script = self._script('move.jsonl',
                              [{'frame': i, 'keys': ['forward']}
                               for i in range(60)])
        out1, ppm1 = run_sim(script)
        out2, ppm2 = run_sim(script)
        self.assertIn('CELLSTAGE-SIMMANIFEST v1', out1)
        self.assertEqual(out1, out2, 'sim manifest not deterministic')
        self.assertEqual(read_bytes(ppm1), read_bytes(ppm2),
                         'sim render not deterministic')
        pos = parse_pos(out1)
        self.assertGreater(pos[2], 1.0,
                           'forward thrust should move the player +Z: %r' % (pos,))
        self.assertLess(abs(pos[0]), 0.5,
                        'forward thrust should not drift sideways: %r' % (pos,))

    def test_zero_input_no_movement(self):
        script = self._script('zero.jsonl',
                              [{'frame': i, 'keys': []} for i in range(30)])
        out, _ = run_sim(script)
        pos = parse_pos(out)
        self.assertEqual(pos, (0.0, 0.0, 0.0),
                         'zero input must not move the player: %r' % (pos,))

    def test_eat_deterministic(self):
        # Turn toward food_a (+X/+Z quadrant), then swim into it.
        rows = [{'frame': i, 'keys': ['right']} for i in range(20)]
        rows += [{'frame': 20 + i, 'keys': ['forward']}
                 for i in range(100)]
        script = self._script('eat.jsonl', rows)
        out1, ppm1 = run_sim(script)
        out2, ppm2 = run_sim(script)
        self.assertEqual(out1, out2, 'sim manifest not deterministic')
        self.assertIn('type=eat entity=food_a', out1)
        self.assertEqual(parse_grow(out1), 1,
                         'eating food_a must set growMeter=1')
        baseline = self._script('zero.jsonl',
                                [{'frame': i, 'keys': []}
                                 for i in range(30)])
        _, ppm0 = run_sim(baseline)
        self.assertNotEqual(read_bytes(ppm1), read_bytes(ppm0),
                            'culled food / moved player must change pixels')


if __name__ == '__main__':
    unittest.main()
