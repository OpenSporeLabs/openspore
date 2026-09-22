# Contract for tools/observatory/menu_walk.sh (docs/analysis/GUI-BOUNDARY.md
# §6, docs/RE-AUTOMATION-ARCHITECTURE.md §8): dry-run enumerates every step
# while issuing nothing; key allowlist enforced; shot manifest line shape;
# approval gate fail-closed. Stdlib unittest; `sh` required (always present).
import json
import os
import shutil
import subprocess
import tempfile
import unittest

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SCRIPT = os.path.join(ROOT, "tools", "observatory", "menu_walk.sh")
WALK_TMP = "/tmp/openspore-walk"
SHOTS_DIR = os.path.join(ROOT, "tools", "observatory", "out", "shots")


def run(args, env=None):
    return subprocess.run(["sh", SCRIPT] + list(args),
                          capture_output=True, text=True,
                          env=env if env is not None else dict(os.environ),
                          timeout=60)


def dir_listing(path):
    if not os.path.isdir(path):
        return set()
    out = set()
    for base, dirs, files in os.walk(path):
        for d in dirs + files:
            out.add(os.path.relpath(os.path.join(base, d), path))
    return out


@unittest.skipUnless(os.path.exists(SCRIPT), "menu_walk.sh absent")
class MenuWalkDryRunTest(unittest.TestCase):
    def test_dry_run_lists_every_step_and_safety_item(self):
        r = run(["--dry-run"])
        self.assertEqual(r.returncode, 0, r.stderr)
        for token in ("pin", "maximize", "Return", "Down", "shot",
                      "no-op", "ladder", "stop-state", "geometry",
                      "machine.lock", "input", "approval", "maim",
                      "Ctrl+Alt+Backspace", "wineserver -k"):
            self.assertIn(token, r.stdout)

    def test_dry_run_issues_nothing(self):
        shim = tempfile.TemporaryDirectory()
        markers = os.path.join(shim.name, "markers")
        os.makedirs(markers)
        for tool in ("xdotool", "wine", "wineserver", "maim", "xwininfo",
                     "xrandr", "xprop", "python3", "sleep"):
            with open(os.path.join(shim.name, tool), "w") as f:
                f.write('#!/bin/sh\necho x >> "%s/%s"\nexit 0\n'
                        % (markers, tool))
            os.chmod(os.path.join(shim.name, tool), 0o755)
        env = dict(os.environ)
        env["PATH"] = shim.name + os.pathsep + env.get("PATH", "")
        before_walk = dir_listing(WALK_TMP)
        before_shots = dir_listing(SHOTS_DIR)
        r = run(["--dry-run"], env=env)
        self.assertEqual(r.returncode, 0, r.stderr)
        self.assertEqual(os.listdir(markers), [])
        self.assertEqual(dir_listing(WALK_TMP), before_walk)
        self.assertEqual(dir_listing(SHOTS_DIR), before_shots)
        shim.cleanup()


@unittest.skipUnless(os.path.exists(SCRIPT), "menu_walk.sh absent")
class MenuWalkGateTest(unittest.TestCase):
    def _clean_env(self):
        env = dict(os.environ)
        env.pop("OPENSPORE_MCP_TRUSTED", None)
        env.pop("OPENSPORE_WALK_LOCKED", None)
        return env

    def test_missing_approve_flag_is_approval_required(self):
        r = run([], env=self._clean_env())
        self.assertEqual(r.returncode, 3)
        self.assertIn("approval_required", r.stdout)

    def test_missing_trusted_env_is_approval_required(self):
        r = run(["--approve"], env=self._clean_env())
        self.assertEqual(r.returncode, 3)
        self.assertIn("approval_required", r.stdout)

    def test_validate_key_allowed(self):
        for key in ("Return", "Escape", "Up", "Down", "Left", "Right"):
            r = run(["--validate-key", key])
            self.assertEqual(r.returncode, 0, key + ": " + r.stderr)

    def test_validate_key_rejected(self):
        r = run(["--validate-key", "F13"])
        self.assertEqual(r.returncode, 2)
        self.assertIn("rejected", r.stderr)

    def test_shot_line_shape(self):
        r = run(["--shot-line", "1", "/tmp/a.png", "abc123", "1790000000",
                 "1790000000", "Return", "2560x1440+0+0", ""])
        self.assertEqual(r.returncode, 0, r.stderr)
        line = json.loads(r.stdout)
        self.assertEqual(set(line), {"seq", "path", "sha256", "wall_clock",
                                     "trace_t_nearest", "input_event",
                                     "window_geom", "delta_vs_prev_sha"})
        self.assertEqual(line["seq"], 1)
        self.assertIs(line["delta_vs_prev_sha"], True)
        r2 = run(["--shot-line", "2", "/tmp/b.png", "abc123", "1790000001",
                  "1790000001", "Down", "2560x1440+0+0", "abc123"])
        self.assertIs(json.loads(r2.stdout)["delta_vs_prev_sha"], False)


if __name__ == "__main__":
    unittest.main()
