import hashlib
import importlib.util
import json
import tempfile
import unittest
from pathlib import Path
from struct import pack_into as struct_pack_into
from struct import unpack_from as struct_unpack_from


ROOT = Path(__file__).resolve().parents[1]
MODULE_PATH = ROOT / "tools" / "observatory" / "pkg07_preflight.py"
SPEC = importlib.util.spec_from_file_location("pkg07_preflight", MODULE_PATH)
PREFLIGHT = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(PREFLIGHT)


def make_pe(target_bytes=PREFLIGHT.TARGET_BYTES, call_bytes=PREFLIGHT.CALL_BYTES):
    raw_size = 0x30000
    section_rva = PREFLIGHT.TARGET_RVA - 0x790
    section_offset = PREFLIGHT.TARGET_OFFSET - 0x790
    data = bytearray(section_offset + raw_size)
    data[0:2] = b"MZ"
    pe_offset = 0x80
    struct_pack_into("<I", data, 0x3C, pe_offset)
    data[pe_offset:pe_offset + 4] = b"PE\0\0"
    struct_pack_into("<HHIIIHH", data, pe_offset + 4, 0x014C, 1, 0, 0, 0, 0xE0, 0x0103)
    optional = pe_offset + 24
    struct_pack_into("<H", data, optional, 0x10B)
    struct_pack_into("<I", data, optional + 4, raw_size)
    struct_pack_into("<I", data, optional + 16, PREFLIGHT.TARGET_RVA)
    struct_pack_into("<I", data, optional + 20, section_rva)
    struct_pack_into("<I", data, optional + 28, PREFLIGHT.IMAGE_BASE)
    struct_pack_into("<II", data, optional + 32, 0x1000, 0x200)
    struct_pack_into("<HHHHHH", data, optional + 40, 4, 0, 0, 0, 4, 0)
    struct_pack_into("<III", data, optional + 52, 0, 0xA8C000, 0x1000)
    struct_pack_into("<IHH", data, optional + 64, 0, 2, 0x0040)
    struct_pack_into("<IIII", data, optional + 72, 0x100000, 0x1000, 0x100000, 0x1000)
    struct_pack_into("<II", data, optional + 88, 0, 16)
    section = optional + 0xE0
    data[section:section + 8] = b".text\0\0\0"
    struct_pack_into("<IIII", data, section + 8, raw_size, section_rva, raw_size, section_offset)
    struct_pack_into("<I", data, section + 36, 0x60000020)
    data[PREFLIGHT.TARGET_OFFSET:PREFLIGHT.TARGET_OFFSET + len(target_bytes)] = target_bytes
    data[PREFLIGHT.CALL_OFFSET:PREFLIGHT.CALL_OFFSET + len(call_bytes)] = call_bytes
    return bytes(data)


def write_manifest(path, value):
    raw = json.dumps(value, sort_keys=True).encode("utf-8")
    path.write_bytes(raw)
    return hashlib.sha256(raw).hexdigest()


def make_manifest(path, probes, image_base="0x400000"):
    return write_manifest(path, {"image_base": image_base, "probes": probes})


def probes_for(mapping, cell=False):
    probes = []
    for name, value in mapping.items():
        note = "static probe"
        if cell and name == "Simulator::Cell::MovePlayerToMousePosition":
            note = "current operand 0x016b3c04"
        if cell and name == "cam_mode_getter_FUN_00e4ce40":
            note = "current operand 0x015a758c"
        probes.append({"name": name, "rva": "0x%x" % value, "note": note})
    return probes


class Pkg07PreflightTest(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.root = Path(self.tmp.name)
        self.main_path = self.root / "main.json"
        self.cell_path = self.root / "cell.json"
        self.exe_path = self.root / "synthetic.exe"
        self.main_hash = make_manifest(self.main_path, probes_for(PREFLIGHT.MAIN_PROBES))
        self.cell_hash = make_manifest(self.cell_path, probes_for(PREFLIGHT.CELL_PROBES, True))

    def tearDown(self):
        self.tmp.cleanup()

    def test_synthetic_pe_has_coherent_headers(self):
        data = make_pe()
        pe = PREFLIGHT.parse_pe(data)
        section = pe["sections"][0]
        optional = 0x98
        self.assertEqual(struct_unpack_from("<H", data, 0x96)[0], 0x0103)
        self.assertEqual(struct_unpack_from("<H", data, optional)[0], 0x10B)
        self.assertEqual(struct_unpack_from("<I", data, optional + 16)[0], PREFLIGHT.TARGET_RVA)
        self.assertEqual(struct_unpack_from("<II", data, optional + 32), (0x1000, 0x200))
        self.assertEqual(struct_unpack_from("<I", data, optional + 56)[0], 0xA8C000)
        self.assertEqual(struct_unpack_from("<I", data, optional + 60)[0], 0x1000)
        self.assertEqual(struct_unpack_from("<H", data, optional + 68)[0], 2)
        self.assertEqual(struct_unpack_from("<H", data, optional + 70)[0], 0x0040)
        self.assertEqual(struct_unpack_from("<I", data, optional + 92)[0], 16)
        self.assertEqual(section["virtual_address"] % 0x1000, 0)
        self.assertEqual(section["raw_offset"] % 0x200, 0)
        self.assertEqual(section["raw_size"] % 0x200, 0)
        self.assertEqual(len(data), section["raw_offset"] + section["raw_size"])
        self.assertEqual(struct_unpack_from("<I", data, 0x178 + 36)[0], 0x60000020)

    def test_parse_and_static_report_without_game_files(self):
        data = make_pe()
        self.exe_path.write_bytes(data)
        old_size = PREFLIGHT.EXPECTED_SIZE
        old_hash = PREFLIGHT.EXPECTED_SHA256
        old_cell_hash = PREFLIGHT.EXPECTED_CELL_SHA256
        old_main_hash = PREFLIGHT.EXPECTED_MAIN_SHA256
        try:
            PREFLIGHT.EXPECTED_SIZE = len(data)
            PREFLIGHT.EXPECTED_SHA256 = hashlib.sha256(data).hexdigest()
            PREFLIGHT.EXPECTED_CELL_SHA256 = self.cell_hash
            PREFLIGHT.EXPECTED_MAIN_SHA256 = self.main_hash
            checks = PREFLIGHT.run_checks(self.exe_path, self.cell_path, self.main_path)
            report = PREFLIGHT.build_report(checks)
        finally:
            PREFLIGHT.EXPECTED_SIZE = old_size
            PREFLIGHT.EXPECTED_SHA256 = old_hash
            PREFLIGHT.EXPECTED_CELL_SHA256 = old_cell_hash
            PREFLIGHT.EXPECTED_MAIN_SHA256 = old_main_hash
        self.assertEqual(report["static_overall"], "PASS")
        self.assertEqual(report["runtime_status"], "NOT_RUN")
        self.assertEqual(report["preflight_enforcement"], "ADVISORY_STANDALONE")
        self.assertTrue(all(not report[key] for key in ("runtime_launched", "process_memory_read", "process_memory_written", "canonical_kg_written")))
        self.assertTrue(all(gate["static_preflight"] == "PASS" for gate in report["gates"].values()))
        self.assertTrue(all(gate["static_artifact_readiness"] == "READY" for gate in report["gates"].values()))
        self.assertTrue(all(gate["full_preflight"] == "BLOCKED" for gate in report["gates"].values()))
        self.assertTrue(all(gate["runtime_evidence"] == "NOT_RUN" for gate in report["gates"].values()))
        self.assertIn("STATIC_ASSERTED", [item["status"] for item in report["checks"]])

    def test_exact_maps_and_same_bytes_hash(self):
        main = PREFLIGHT.read_manifest(self.main_path, PREFLIGHT.MAIN_PROBES, self.main_hash)
        cell = PREFLIGHT.read_manifest(self.cell_path, PREFLIGHT.CELL_PROBES, self.cell_hash, True)
        self.assertEqual(len(main["normalized"]), 7)
        self.assertEqual(len(cell["normalized"]), 12)
        self.assertEqual(main["sha256"], self.main_hash)
        self.assertEqual(cell["sha256"], self.cell_hash)
        self.assertEqual(main["normalized"][0], {"name": "entry", "linked_va": "0x011e11a0"})

    def test_manifest_malformed_inputs_are_structured(self):
        path = self.root / "malformed.json"
        cases = [
            ([], "manifest_root_invalid"),
            ({"image_base": "0x400000", "probes": {}}, "manifest_probes_invalid"),
        ]
        invalid_probe = probes_for(PREFLIGHT.MAIN_PROBES)
        invalid_probe[0] = None
        cases.append(({"image_base": "0x400000", "probes": invalid_probe}, "manifest_probe_invalid"))
        invalid_note = probes_for(PREFLIGHT.MAIN_PROBES)
        invalid_note[0]["note"] = 7
        cases.append(({"image_base": "0x400000", "probes": invalid_note}, "manifest_note_invalid"))
        for value, code in cases:
            digest = write_manifest(path, value)
            with self.assertRaises(PREFLIGHT.PreflightError) as raised:
                PREFLIGHT.read_manifest(path, PREFLIGHT.MAIN_PROBES, digest)
            self.assertEqual(raised.exception.code, code)
        raw = b"{"
        path.write_bytes(raw)
        digest = hashlib.sha256(raw).hexdigest()
        with self.assertRaises(PREFLIGHT.PreflightError) as raised:
            PREFLIGHT.read_manifest(path, PREFLIGHT.MAIN_PROBES, digest)
        self.assertEqual(raised.exception.code, "manifest_json_invalid")

    def test_manifest_rejects_wrong_approved_hash(self):
        with self.assertRaises(PREFLIGHT.PreflightError) as raised:
            PREFLIGHT.read_manifest(self.main_path, PREFLIGHT.MAIN_PROBES, "0" * 64)
        self.assertEqual(raised.exception.code, "manifest_hash_mismatch")
        self.assertEqual(raised.exception.expected, "0" * 64)
        self.assertEqual(raised.exception.observed, self.main_hash)

    def test_manifest_rejects_exact_key_and_hex_errors(self):
        bad = probes_for(PREFLIGHT.MAIN_PROBES)
        bad[0]["rva"] = "1234"
        path = self.root / "bad.json"
        digest = make_manifest(path, bad)
        with self.assertRaises(PREFLIGHT.PreflightError) as raised:
            PREFLIGHT.read_manifest(path, PREFLIGHT.MAIN_PROBES, digest)
        self.assertEqual(raised.exception.code, "non_canonical_hex")
        bad[0]["rva"] = "0x011e11a0"
        bad[1]["name"] = bad[0]["name"]
        digest = make_manifest(path, bad)
        with self.assertRaises(PREFLIGHT.PreflightError) as raised:
            PREFLIGHT.read_manifest(path, PREFLIGHT.MAIN_PROBES, digest)
        self.assertEqual(raised.exception.code, "manifest_duplicate_name")

    def test_manifest_rejects_wrong_map_and_duplicate_value(self):
        bad = probes_for(PREFLIGHT.MAIN_PROBES)
        bad[0]["rva"] = "0x011e11a1"
        path = self.root / "bad.json"
        digest = make_manifest(path, bad)
        with self.assertRaises(PREFLIGHT.PreflightError) as raised:
            PREFLIGHT.read_manifest(path, PREFLIGHT.MAIN_PROBES, digest)
        self.assertEqual(raised.exception.code, "manifest_map_mismatch")
        bad[0]["rva"] = "0x011e11a0"
        bad[1]["rva"] = "0x011e11a0"
        digest = make_manifest(path, bad)
        with self.assertRaises(PREFLIGHT.PreflightError) as raised:
            PREFLIGHT.read_manifest(path, PREFLIGHT.MAIN_PROBES, digest)
        self.assertEqual(raised.exception.code, "manifest_duplicate_value")

    def test_manifest_rejects_both_stale_sentinels(self):
        for stale in ("0x116b3c04", "0x115a758c"):
            probes = probes_for(PREFLIGHT.CELL_PROBES, True)
            probes[0]["note"] = "historical " + stale
            path = self.root / "stale.json"
            digest = make_manifest(path, probes)
            with self.assertRaises(PREFLIGHT.PreflightError) as raised:
                PREFLIGHT.read_manifest(path, PREFLIGHT.CELL_PROBES, digest, True)
            self.assertEqual(raised.exception.code, "stale_operand")

    def test_manifest_requires_current_operands_in_notes(self):
        probes = probes_for(PREFLIGHT.CELL_PROBES, True)
        probes[5]["note"] = "current address omitted"
        path = self.root / "notes.json"
        digest = make_manifest(path, probes)
        with self.assertRaises(PREFLIGHT.PreflightError) as raised:
            PREFLIGHT.read_manifest(path, PREFLIGHT.CELL_PROBES, digest, True)
        self.assertEqual(raised.exception.code, "current_operand_note_missing")

    def test_pe_errors_are_structured(self):
        for data, code in ((b"", "invalid_mz"), (b"MZ" + b"\0" * 62, "invalid_pe_signature")):
            with self.assertRaises(PREFLIGHT.PreflightError) as raised:
                PREFLIGHT.parse_pe(data)
            self.assertEqual(raised.exception.code, code)


if __name__ == "__main__":
    unittest.main()
