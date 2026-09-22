# Contract for the canonical 7-level evidence scale (knowledgegraph/scale.py,
# docs/RE-AUTOMATION-ARCHITECTURE.md §3). Stdlib unittest; no temp files,
# no DB. Runs under `python3 -m unittest discover -s tests -t .`.
import json
import os
import sys
import unittest

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "knowledgegraph"))
import scale  # noqa: E402
sys.path.insert(0, os.path.join(ROOT, "tools", "re"))
import dossier  # noqa: E402


class TestScale(unittest.TestCase):
    def test_ev_exactly_seven_doc_values(self):
        self.assertEqual(scale.EV, {
            "UNKNOWN": 0.0,
            "APPROXIMATION": 0.3,
            "INFERRED": 0.5,
            "SUPPORTED": 0.75,
            "OBSERVED": 0.85,
            "CONFIRMED": 0.9,
            "VERIFIED": 1.0,
        })
        self.assertEqual(len(scale.EV), 7)

    def test_ev_order_strictly_ascending(self):
        self.assertEqual(set(scale.EV_ORDER), set(scale.EV))
        vals = [scale.EV[l] for l in scale.EV_ORDER]
        for a, b in zip(vals, vals[1:]):
            self.assertLess(a, b, f"not strictly ascending: {a} !< {b}")

    def test_all_documented_statuses_map(self):
        with open(os.path.join(ROOT, "docs", "replacement-status.json")) as f:
            doc = json.load(f)
        file_statuses = set(doc["vocabulary"])
        for s in doc["subsystems"]:
            file_statuses.add(s["status"])
        self.assertEqual(len(scale.STATUS2EV), 9)
        self.assertEqual(file_statuses, set(scale.STATUS2EV))
        for st in file_statuses:
            self.assertIn(scale.evidence_for_status(st), scale.EV,
                          f"status {st!r} maps to non-scale level")

    def test_map_b_exactly_five_legacy_values(self):
        self.assertEqual(scale.LEGACY_EV, {
            "UNKNOWN": "UNKNOWN",
            "HYPOTHESIS": "INFERRED",
            "INFERRED": "INFERRED",
            "SUPPORTED": "SUPPORTED",
            "VERIFIED": "VERIFIED",
        })
        for legacy, modern in scale.LEGACY_EV.items():
            self.assertEqual(scale.legacy_evidence(legacy), modern)
            self.assertIn(modern, scale.EV)

    def test_previously_missing_keys_resolve(self):
        # Regression guard for the stale 7-key dict: both keys that used to
        # KeyError on the current docs/replacement-status.json must resolve.
        self.assertEqual(scale.evidence_for_status("approximated"),
                         "APPROXIMATION")
        self.assertEqual(scale.evidence_for_status("replaced-approx"),
                         "APPROXIMATION")

    def test_unknown_status_raises_valueerror_not_keyerror(self):
        with self.assertRaises(ValueError) as ctx:
            scale.evidence_for_status("no-such-status")
        self.assertIn("approximated", str(ctx.exception))
        self.assertIn("replaced-verified", str(ctx.exception))
        with self.assertRaises(ValueError):
            scale.legacy_evidence("OBSERVED")  # 7-level value, not legacy

    def test_dossier_vocab_matches_scale(self):
        self.assertEqual(dossier.EVIDENCE_VOCAB,
                         ["OBSERVED", "VERIFIED", "CONFIRMED", "SUPPORTED",
                          "INFERRED", "APPROXIMATION", "UNKNOWN"])
        self.assertEqual(len(dossier.EVIDENCE_VOCAB), 7)
        self.assertEqual(set(dossier.EVIDENCE_VOCAB), set(scale.EV))


if __name__ == "__main__":
    unittest.main()
