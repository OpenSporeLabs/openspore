# Contract for tools/observatory/observe.py machine-lock integration
# (fail-closed machine_locked when the shared display/GPU lock is held;
# docs/RE-AUTOMATION-ARCHITECTURE.md §8; same lock file/prefix as
# tools/mcp/runtime_tools.py). Stdlib unittest.
import importlib.util
import os
import subprocess
import sys
import tempfile
import time
import unittest

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
OBSERVE = os.path.join(ROOT, "tools", "observatory", "observe.py")
LOCKPY = os.path.join(ROOT, "tools", "observatory", "lock.py")
PROBES = os.path.join(ROOT, "tools", "observatory", "probes")


def load_lock():
    spec = importlib.util.spec_from_file_location("openspore_lock", LOCKPY)
    mod = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(mod)
    return mod


@unittest.skipUnless(os.path.exists(os.path.join(PROBES, "main_menu.json")),
                     "probe main_menu.json absent")
class ObserveLockTest(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.env = dict(os.environ)
        self.env["OPENSPORE_MCP_LOCK"] = os.path.join(self.tmp.name, "obs.lock")
        self.mod = load_lock()

    def tearDown(self):
        self.tmp.cleanup()

    def test_held_lock_parks_fail_closed(self):
        fh = self.mod.acquire("test", path=self.env["OPENSPORE_MCP_LOCK"])
        t0 = time.time()
        r = subprocess.run([sys.executable, OBSERVE, "main_menu"],
                           capture_output=True, text=True, env=self.env,
                           timeout=60)
        dt = time.time() - t0
        self.mod.release(fh)
        self.assertEqual(r.returncode, 5)
        self.assertIn("machine_locked", r.stderr)
        self.assertLess(dt, 15)

    def test_lock_free_passes_gate(self):
        # No lock held: observe.py must pass the lock gate. With the tracer
        # binary hidden it exits 1 ("tracer not built") right after the gate
        # — no wine, no display, no game process.
        tracer = os.path.join(ROOT, "tools", "observatory", "probe_tracer")
        hidden = tracer + ".hidden-by-test"
        if not os.path.exists(tracer):
            self.skipTest("probe_tracer not built; nothing to hide")
        os.rename(tracer, hidden)
        try:
            r = subprocess.run([sys.executable, OBSERVE, "main_menu"],
                               capture_output=True, text=True, env=self.env,
                               timeout=60)
            self.assertNotEqual(r.returncode, 5)
            self.assertNotIn("machine_locked", r.stderr)
            self.assertIn("tracer not built", r.stderr)
        finally:
            os.rename(hidden, tracer)


if __name__ == "__main__":
    unittest.main()
