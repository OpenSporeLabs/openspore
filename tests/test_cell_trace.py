# Contract for tools/observatory/cell_trace.sh (S5 real Cell runtime evidence):
# dry-run enumerates every step + exact focused-window commands while issuing
# nothing; the fixed key allowlist is enforced; the registration gate records a
# registration_blocked negative and never emits a letter/digit; the manifest
# builder parses per-probe counts from the trace; the input path is the
# FOCUSED-window one (windowactivate --sync + key --clearmodifiers, no --window).
# Stdlib unittest; `sh` required (always present).
import json
import os
import shutil
import subprocess
import tempfile
import unittest

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SCRIPT = os.path.join(ROOT, "tools", "observatory", "cell_trace.sh")
WALK_TMP = "/tmp/openspore-walk"
CELL_OUT = os.path.join(ROOT, "tools", "observatory", "out", "cell")
ALLOWED_KEYS = {"Return", "Escape", "Up", "Down", "Left", "Right"}


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


@unittest.skipUnless(os.path.exists(SCRIPT), "cell_trace.sh absent")
class CellTraceDryRunTest(unittest.TestCase):
    def test_dry_run_is_deterministic(self):
        r1 = run(["--dry-run"])
        r2 = run(["--dry-run"])
        self.assertEqual(r1.returncode, 0, r1.stderr)
        self.assertEqual(r2.returncode, 0, r2.stderr)
        self.assertEqual(r1.stdout, r2.stdout,
                         "dry-run plan is not byte-identical across runs")

    def test_dry_run_lists_every_step_and_safety_item(self):
        r = run(["--dry-run"])
        self.assertEqual(r.returncode, 0, r.stderr)
        for token in ("boot", "pin", "dismiss", "registration", "play",
                      "enter_play", "new_game", "start", "settle",
                      "windowactivate --sync", "key --clearmodifiers",
                      "no-op", "ladder", "stop-state", "geometry",
                      "machine_locked", "approval", "maim", "swapchain_resize_buffers",
                      "Ctrl+Alt+Backspace", "wineserver -k", "probe_tracer"):
            self.assertIn(token, r.stdout)

    def test_dry_run_focused_window_path_only(self):
        # The emitted per-keystep command is windowactivate --sync +
        # key --clearmodifiers; the XSendEvent --window form must be absent.
        r = run(["--dry-run"])
        self.assertEqual(r.returncode, 0, r.stderr)
        self.assertIn("xdotool windowactivate --sync", r.stdout)
        self.assertIn("xdotool key --clearmodifiers", r.stdout)
        self.assertNotIn("--window", r.stdout,
                         "dry-run must not emit the XSendEvent --window form")

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
        before_out = dir_listing(CELL_OUT)
        r = run(["--dry-run"], env=env)
        self.assertEqual(r.returncode, 0, r.stderr)
        self.assertEqual(os.listdir(markers), [],
                         "dry-run invoked a real/PATH tool")
        self.assertEqual(dir_listing(WALK_TMP), before_walk)
        self.assertEqual(dir_listing(CELL_OUT), before_out)
        shim.cleanup()


@unittest.skipUnless(os.path.exists(SCRIPT), "cell_trace.sh absent")
class CellTraceGateTest(unittest.TestCase):
    def _clean_env(self):
        env = dict(os.environ)
        env.pop("OPENSPORE_MCP_TRUSTED", None)
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
        for key in sorted(ALLOWED_KEYS):
            r = run(["--validate-key", key])
            self.assertEqual(r.returncode, 0, key + ": " + r.stderr)
            self.assertIn("allowed", r.stdout)

    def test_validate_key_rejected(self):
        for bad in ("F13", "a", "5", "Tab", "space"):
            r = run(["--validate-key", bad])
            self.assertEqual(r.returncode, 2, bad)
            self.assertIn("rejected", r.stderr)


@unittest.skipUnless(os.path.exists(SCRIPT), "cell_trace.sh absent")
class CellTraceRegistrationGateTest(unittest.TestCase):
    def _decision(self, signal):
        r = run(["--registration-decision", signal])
        return r

    def test_persists_is_registration_blocked(self):
        r = self._decision("persists")
        self.assertEqual(r.returncode, 0, r.stderr)
        obj = json.loads(r.stdout)
        self.assertEqual(obj["decision"], "registration_blocked")

    def test_advanced_is_continue(self):
        r = self._decision("advanced")
        self.assertEqual(r.returncode, 0, r.stderr)
        self.assertEqual(json.loads(r.stdout)["decision"], "continue")

    def test_never_emits_letter_or_digit_key(self):
        # A "letter/digit key" is a typing key (e.g. 'a', '5', 'F13'). The
        # allowlist is pure navigation, so the driver never types: for both
        # signals every emitted key is in the allowlist and the JSON claim
        # letters_or_digits is False.
        for signal in ("persists", "advanced"):
            r = self._decision(signal)
            self.assertEqual(r.returncode, 0, r.stderr)
            obj = json.loads(r.stdout)
            self.assertFalse(obj["letters_or_digits"])
            for k in obj["keys"]:
                self.assertIn(k, ALLOWED_KEYS,
                              "%s emitted non-allowlisted (typing) key %s"
                              % (signal, k))

    def test_unknown_signal_refused(self):
        r = self._decision("bogus")
        self.assertEqual(r.returncode, 2, r.stderr)
        self.assertIn("unknown registration signal", r.stderr)


@unittest.skipUnless(os.path.exists(SCRIPT), "cell_trace.sh absent")
class CellTraceManifestTest(unittest.TestCase):
    def _synthetic(self, lines):
        d = tempfile.NamedTemporaryFile("w", suffix=".jsonl", delete=False)
        d.write("\n".join(lines) + "\n")
        d.close()
        return d.name

    def test_probe_event_counts_and_stage(self):
        p = self._synthetic([
            '{"t":1,"name":"entry (bootstrap control)","rva":"0x11e11a0"}',
            '{"t":2,"name":"entry (bootstrap control)","rva":"0x11e11a0"}',
            '{"t":3,"name":"App::cCellModeStrategy::Update","rva":"0xe80980"}',
            '{"t":4,"name":"Simulator::Cell::MovePlayerToMousePosition","rva":"0xe5b790"}',
        ])
        r = run(["--manifest", p, "menu_only", "S5-test", "150", "false"])
        self.assertEqual(r.returncode, 0, r.stderr)
        m = json.loads(r.stdout)
        self.assertEqual(m["run_id"], "S5-test")
        self.assertEqual(m["scenario"], "cell_movement")
        t = m["trace"]
        self.assertEqual(t["probe_set"], "cell_movement")
        self.assertEqual(t["jsonl"], "obs_cell_movement.jsonl")
        self.assertEqual(t["duration"], 150)
        self.assertEqual(t["cell_stage_reached"], "menu_only")
        self.assertEqual(t["probe_event_counts"], {
            "entry (bootstrap control)": 2,
            "App::cCellModeStrategy::Update": 1,
            "Simulator::Cell::MovePlayerToMousePosition": 1,
        })
        self.assertIs(m["lock_probe"]["machine_locked"], False)
        os.unlink(p)

    def test_stage_true_is_a_bool(self):
        p = self._synthetic([
            '{"name":"cell_update_body_FUN_00e806b0","rva":"0xe806b0"}',
        ])
        r = run(["--manifest", p, "true", "S5-test", "200", "false"])
        self.assertEqual(r.returncode, 0, r.stderr)
        m = json.loads(r.stdout)
        self.assertIs(m["trace"]["cell_stage_reached"], True)
        self.assertEqual(m["trace"]["duration"], 200)
        self.assertEqual(m["trace"]["probe_event_counts"],
                         {"cell_update_body_FUN_00e806b0": 1})
        os.unlink(p)

    def test_manifest_is_deterministic(self):
        p = self._synthetic([
            '{"name":"entry (bootstrap control)","rva":"0x11e11a0"}',
            '{"name":"App::cCellModeStrategy::Update","rva":"0xe80980"}',
        ])
        r1 = run(["--manifest", p, "menu_only", "S5-test", "150", "false"])
        r2 = run(["--manifest", p, "menu_only", "S5-test", "150", "false"])
        self.assertEqual(r1.returncode, 0, r1.stderr)
        self.assertEqual(r1.stdout, r2.stdout,
                         "manifest is not byte-identical across runs")
        os.unlink(p)


if __name__ == "__main__":
    unittest.main()
