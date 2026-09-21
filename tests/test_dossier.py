# Obj 31: dossier generator contract (tools/re/dossier.py,
# docs/RE-DOSSIER-SCHEMA.md). CI-safe: needs neither SPORE/ nor a live
# Ghidra server; runs under `python3 -m unittest discover -s tests -t .`.
import json
import os
import subprocess
import sys
import unittest

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
TOOL = os.path.join(ROOT, "tools", "re", "dossier.py")
OUT = os.path.join(ROOT, "docs", "analysis", "dossiers")
VOCAB = ["OBSERVED", "VERIFIED", "CONFIRMED", "SUPPORTED",
         "INFERRED", "APPROXIMATION", "UNKNOWN"]


class TestDossier(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.proc = subprocess.run(
            [sys.executable, TOOL, "cell-movement"],
            capture_output=True, text=True, timeout=300)

    def _dossier(self):
        with open(os.path.join(OUT, "cell-movement.json")) as f:
            return json.load(f)

    def _md(self):
        with open(os.path.join(OUT, "cell-movement.md")) as f:
            return f.read()

    def test_exit_zero(self):
        self.assertEqual(self.proc.returncode, 0,
                         self.proc.stdout + self.proc.stderr)

    def test_outputs_written(self):
        self.assertTrue(os.path.exists(os.path.join(OUT, "cell-movement.md")))
        self.assertTrue(os.path.exists(os.path.join(OUT, "cell-movement.json")))

    def test_schema_keys(self):
        d = self._dossier()
        for key in ("topic", "evidence_summary", "functions", "callers",
                    "callees", "constants", "runtime", "resource_refs",
                    "asset_relationships", "hypotheses", "known_unknowns",
                    "openspore_counterpart", "replacement_readiness"):
            self.assertIn(key, d, "missing schema key: %s" % key)
        self.assertEqual(d["topic"], "cell-movement")

    def test_key_functions_and_rvas(self):
        d = self._dossier()
        by = {f["name"]: f for f in d["functions"]}
        self.assertIn("Simulator::Cell::MovePlayerToMousePosition", by)
        self.assertEqual(by["Simulator::Cell::MovePlayerToMousePosition"]["rva"],
                         "0xd5b790")
        self.assertIn("App::cCellModeStrategy::Update", by)
        self.assertEqual(by["App::cCellModeStrategy::Update"]["rva"],
                         "0xd80980")

    def test_ray_plane_finding(self):
        md = self._md().lower()
        self.assertIn("plane", md)
        self.assertIn("ray", md)
        self.assertIn("mouse", md)

    def test_evidence_labels_and_not_truth(self):
        text = json.dumps(self._dossier()).upper()
        self.assertTrue(any(v in text for v in VOCAB),
                        "no evidence vocabulary label found")
        md = self._md().upper()
        self.assertIn("EVIDENCE", md)
        self.assertIn("NOT TRUTH", md)

    def test_runtime_recorded_not_fabricated(self):
        d = self._dossier()
        self.assertFalse(d["runtime"]["obtained"])
        self.assertTrue(d["runtime"]["reason"])
        self.assertEqual(d["runtime"]["matched_events"], [])


if __name__ == "__main__":
    unittest.main()
