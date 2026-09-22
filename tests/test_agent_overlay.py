# Contract for tools/observatory/agent_overlay.py (visible AGENT DRIVING
# overlay + global Ctrl+Alt+Backspace stop grab;
# docs/analysis/GUI-BOUNDARY.md §6). --selftest maps a real override-redirect
# window on $DISPLAY, verifies it, and tears it down. Skipped without DISPLAY.
import os
import subprocess
import sys
import unittest

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
OVERLAY = os.path.join(ROOT, "tools", "observatory", "agent_overlay.py")


@unittest.skipUnless(os.environ.get("DISPLAY"), "no DISPLAY (X session required)")
class OverlaySelfTest(unittest.TestCase):
    def test_selftest_passes_on_display(self):
        r = subprocess.run([sys.executable, OVERLAY, "--selftest"],
                           capture_output=True, text=True, timeout=30)
        self.assertEqual(r.returncode, 0, r.stdout + r.stderr)
        self.assertIn("PASS", r.stdout)

    def test_stop_without_running_is_clean(self):
        r = subprocess.run([sys.executable, OVERLAY, "--stop"],
                           capture_output=True, text=True, timeout=10)
        self.assertEqual(r.returncode, 0)

    def test_usage_exit_2(self):
        r = subprocess.run([sys.executable, OVERLAY],
                           capture_output=True, text=True, timeout=10)
        self.assertEqual(r.returncode, 2)


if __name__ == "__main__":
    unittest.main()
