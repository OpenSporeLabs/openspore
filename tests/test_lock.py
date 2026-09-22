# Contract for tools/observatory/lock.py (machine lock: flock on
# /tmp/openspore-machine.lock; body {pid,label,ts,task_id}; fail-closed
# exit 5 machine_locked — docs/RE-AUTOMATION-ARCHITECTURE.md §8).
# Stdlib unittest. Runs under `python3 -m unittest discover -s tests -t .`.
import importlib.util
import json
import os
import subprocess
import sys
import tempfile
import time
import unittest

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
LOCKPY = os.path.join(ROOT, "tools", "observatory", "lock.py")


def load():
    spec = importlib.util.spec_from_file_location("openspore_lock", LOCKPY)
    mod = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(mod)
    return mod


class LockTest(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.path = os.path.join(self.tmp.name, "machine.lock")
        self._old = os.environ.get("OPENSPORE_MCP_LOCK")
        os.environ["OPENSPORE_MCP_LOCK"] = self.path
        self.mod = load()

    def tearDown(self):
        if self._old is None:
            os.environ.pop("OPENSPORE_MCP_LOCK", None)
        else:
            os.environ["OPENSPORE_MCP_LOCK"] = self._old
        self.tmp.cleanup()

    def test_probe_free(self):
        self.assertFalse(self.mod.lock_held(self.path))
        r = subprocess.run([sys.executable, LOCKPY, "probe"],
                           capture_output=True, text=True)
        self.assertEqual(r.returncode, 0)
        self.assertEqual(json.loads(r.stdout)["machine_locked"], False)

    def test_acquire_writes_body_and_releases(self):
        fh = self.mod.acquire("test-label", task_id="t1", path=self.path)
        try:
            self.assertTrue(self.mod.lock_held(self.path))
            with open(self.path) as f:
                body = json.load(f)
            self.assertEqual(body["pid"], os.getpid())
            self.assertEqual(body["label"], "test-label")
            self.assertEqual(body["task_id"], "t1")
            self.assertIsInstance(body["ts"], float)
        finally:
            self.mod.release(fh)
        self.assertFalse(self.mod.lock_held(self.path))

    def test_contention_machine_locked(self):
        fh = self.mod.acquire("holder", path=self.path)
        with self.assertRaises(self.mod.MachineLocked):
            self.mod.acquire("other", path=self.path)
        r = subprocess.run([sys.executable, LOCKPY, "probe"],
                           capture_output=True, text=True)
        self.assertEqual(r.returncode, 5)
        self.assertEqual(json.loads(r.stdout)["code"], "machine_locked")
        self.mod.release(fh)

    def test_acquire_execs_command_and_lock_dropped_after(self):
        marker = os.path.join(self.tmp.name, "ran")
        r = subprocess.run(
            [sys.executable, LOCKPY, "acquire", "t", "--",
             sys.executable, "-c",
             "import time; time.sleep(0.2); open(%r, 'w').write('x')" % marker],
            capture_output=True, text=True, timeout=30)
        self.assertEqual(r.returncode, 0)
        self.assertTrue(os.path.exists(marker))
        self.assertFalse(self.mod.lock_held(self.path))

    def test_command_path_holds_lock_during_execution(self):
        # Regression: CPython 3.4+ opens files with O_CLOEXEC by default, so
        # the flock'd fd was closed at os.execvpe and the kernel released the
        # lock at exec time — a concurrent acquire SUCCEEDED while a command
        # ran. The command path must keep the lock held for the whole child
        # lifetime, and the body's pid must be the child's pid (the exec'd
        # process).
        proc = subprocess.Popen(
            [sys.executable, LOCKPY, "acquire", "holder", "--",
             sys.executable, "-c", "import time; time.sleep(3)"],
            stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        try:
            deadline = time.time() + 15
            while time.time() < deadline and not self.mod.lock_held(self.path):
                time.sleep(0.2)
            self.assertTrue(self.mod.lock_held(self.path),
                            "lock not held while the command runs")
            with open(self.path) as f:
                body = json.load(f)
            self.assertEqual(body["pid"], proc.pid,
                             "body must record the exec'd command's pid")
            with self.assertRaises(self.mod.MachineLocked):
                self.mod.acquire("other", path=self.path)
            pr = subprocess.run([sys.executable, LOCKPY, "probe"],
                                capture_output=True, text=True)
            self.assertEqual(pr.returncode, 5)
            self.assertEqual(json.loads(pr.stdout)["code"], "machine_locked")
        finally:
            proc.wait(timeout=30)
            proc.stdout.close()
            proc.stderr.close()
        self.assertEqual(proc.returncode, 0)
        self.assertFalse(self.mod.lock_held(self.path))

    def test_acquire_contended_exit_5(self):
        fh = self.mod.acquire("holder", path=self.path)
        t0 = time.time()
        r = subprocess.run([sys.executable, LOCKPY, "acquire", "other"],
                           capture_output=True, text=True, timeout=30)
        dt = time.time() - t0
        self.mod.release(fh)
        self.assertEqual(r.returncode, 5)
        self.assertEqual(json.loads(r.stdout)["code"], "machine_locked")
        self.assertLess(dt, 10)

    def test_lock_path_default_prefix(self):
        os.environ.pop("OPENSPORE_MCP_LOCK", None)
        self.assertEqual(load().lock_path(), "/tmp/openspore-machine.lock")


if __name__ == "__main__":
    unittest.main()
