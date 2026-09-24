#!/usr/bin/env python3
import argparse
import hashlib
import json
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
EXE = ROOT / "SPORE/SporeBin/SporeApp.exe"
CELL_MANIFEST = ROOT / "tools/observatory/probes/cell_movement.json"
MAIN_MANIFEST = ROOT / "tools/observatory/probes/main_menu.json"
EXPECTED_SIZE = 20454960
EXPECTED_SHA256 = "25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e"
EXPECTED_CELL_SHA256 = "1c379af6d28c8bd9651473cfb7c5762a96345824a98ae6c94c8004c7af6199b3"
EXPECTED_MAIN_SHA256 = "aa99f627f995e5e0c2bf53f139d8fc9d2c30c0acf688a6ef239f76b66082a286"
IMAGE_BASE = 0x00400000
TARGET_VA = 0x00E5B790
TARGET_RVA = 0x00A5B790
TARGET_OFFSET = 0x00A5AB90
TARGET_BYTES = bytes.fromhex("a1 04 3c 6b 01")
CALL_VA = 0x00E8083B
CALL_RVA = 0x00A8083B
CALL_OFFSET = 0x00A7FC3B
CALL_BYTES = bytes.fromhex("e8 50 af fd ff")
CONTINUATION_VA = 0x00E80840
GLOBAL_OPERAND = 0x016B3C04
STALE_GLOBAL_OPERAND = 0x116B3C04
CAMERA_MODE_OPERAND = 0x015A758C
STALE_CAMERA_MODE_OPERAND = 0x115A758C

MAIN_PROBES = {
    "entry": 0x011E11A0,
    "App::Bootstrap::local_main": 0x00DE13D0,
    "App::Bootstrap::stateMachine": 0x00E20860,
    "App::cAppSystem::Init": 0x007E8BA0,
    "App::cAppSystem::Startup": 0x007E67A0,
    "App::cAppSystem::InitPlugins": 0x007E93D0,
    "App::IAppSystem::Get": 0x0067DCC0,
}

CELL_PROBES = {
    "App::cCellModeStrategy::Update": 0x00E80980,
    "cell_update_body_FUN_00e806b0": 0x00E806B0,
    "App::cCellModeStrategy::OnKeyDown": 0x00E818F0,
    "App::cCellModeStrategy::OnMouseMove": 0x00E51010,
    "App::cCellModeStrategy::OnMouseWheel": 0x00E7D660,
    "Simulator::Cell::MovePlayerToMousePosition": 0x00E5B790,
    "cell_per_frame_FUN_00e5b2e0": 0x00E5B2E0,
    "cam_light_origin_FUN_007c4900": 0x007C4900,
    "player_getter_FUN_00b721d0": 0x00B721D0,
    "cam_mode_getter_FUN_00e4ce40": 0x00E4CE40,
    "face_travel_orient_FUN_0069b600": 0x0069B600,
    "entry (bootstrap control)": 0x011E11A0,
}


class PreflightError(ValueError):
    def __init__(self, code, message, expected=None, observed=None):
        super().__init__(message)
        self.code = code
        self.expected = expected
        self.observed = observed

    def as_record(self, source):
        return {
            "id": self.code,
            "status": "FAIL",
            "evidence_level": "STATIC_CONTRACT",
            "source": source,
            "expected": self.expected,
            "observed": self.observed,
            "detail": str(self),
        }


def record(name, status, evidence_level, source, expected, observed, detail):
    return {
        "id": name,
        "name": name,
        "status": status,
        "evidence_level": evidence_level,
        "source": source,
        "expected": expected,
        "observed": observed,
        "detail": detail,
    }


def canonical_hex(value, label):
    if not isinstance(value, str) or not value.startswith("0x"):
        raise PreflightError("non_canonical_hex", "%s is not a 0x string" % label, observed=value)
    digits = value[2:]
    if not digits or any(char not in "0123456789abcdef" for char in digits):
        raise PreflightError("non_canonical_hex", "%s is not lowercase canonical hex" % label, observed=value)
    return int(digits, 16)


def display_path(path):
    try:
        return str(path.relative_to(ROOT))
    except ValueError:
        return str(path)


def u16(data, offset):
    if offset < 0 or offset + 2 > len(data):
        raise PreflightError("truncated_pe", "u16 is outside the file", observed=offset)
    return struct.unpack_from("<H", data, offset)[0]


def u32(data, offset):
    if offset < 0 or offset + 4 > len(data):
        raise PreflightError("truncated_pe", "u32 is outside the file", observed=offset)
    return struct.unpack_from("<I", data, offset)[0]


def parse_pe(data):
    if len(data) < 64 or data[:2] != b"MZ":
        raise PreflightError("invalid_mz", "missing MZ header", observed=data[:2].hex())
    pe_offset = u32(data, 0x3C)
    if pe_offset + 24 > len(data) or data[pe_offset:pe_offset + 4] != b"PE\0\0":
        raise PreflightError("invalid_pe_signature", "missing PE signature", observed=pe_offset)
    coff = pe_offset + 4
    machine = u16(data, coff)
    section_count = u16(data, coff + 2)
    optional_size = u16(data, coff + 16)
    optional = coff + 20
    if optional + optional_size > len(data):
        raise PreflightError("truncated_pe", "optional header is outside the file", observed=optional + optional_size)
    magic = u16(data, optional)
    if magic != 0x10B:
        raise PreflightError("invalid_optional_header", "expected PE32 optional header, got 0x%x" % magic, observed="0x%04x" % magic)
    if optional + 32 > len(data):
        raise PreflightError("truncated_pe", "PE32 image base is outside the file", observed=optional + 32)
    image_base = u32(data, optional + 28)
    section_table = optional + optional_size
    if section_count > (len(data) - section_table) // 40:
        raise PreflightError("truncated_pe", "section table is outside the file", observed=section_count)
    sections = []
    for index in range(section_count):
        row = section_table + index * 40
        name = data[row:row + 8].split(b"\0", 1)[0].decode("ascii", "replace")
        virtual_size = u32(data, row + 8)
        virtual_address = u32(data, row + 12)
        raw_size = u32(data, row + 16)
        raw_offset = u32(data, row + 20)
        if raw_offset + raw_size > len(data):
            raise PreflightError("invalid_section_range", "section raw range is outside the file", observed={"name": name, "raw_offset": raw_offset, "raw_size": raw_size})
        sections.append({
            "name": name,
            "virtual_size": virtual_size,
            "virtual_address": virtual_address,
            "raw_size": raw_size,
            "raw_offset": raw_offset,
        })
    return {"machine": machine, "image_base": image_base, "sections": sections}


def rva_to_offset(pe, rva):
    for section in pe["sections"]:
        start = section["virtual_address"]
        end = start + max(section["virtual_size"], section["raw_size"])
        if start <= rva < end:
            offset = section["raw_offset"] + rva - start
            if offset < 0 or offset >= section["raw_offset"] + section["raw_size"]:
                raise PreflightError("invalid_section_range", "RVA maps outside raw data", observed=rva)
            return offset
    raise PreflightError("unmapped_rva", "RVA 0x%08x is not mapped by a PE section" % rva, observed="0x%08x" % rva)


def read_manifest(path, expected_map, expected_sha256, require_cell_notes=False):
    try:
        raw = path.read_bytes()
    except OSError as exc:
        raise PreflightError("manifest_unreadable", str(exc), observed=display_path(path)) from exc
    digest = hashlib.sha256(raw).hexdigest()
    if digest != expected_sha256:
        raise PreflightError("manifest_hash_mismatch", "SHA-256 does not match the approved manifest", expected=expected_sha256, observed=digest)
    try:
        data = json.loads(raw.decode("utf-8"))
    except (UnicodeDecodeError, json.JSONDecodeError) as exc:
        raise PreflightError("manifest_json_invalid", str(exc), observed=display_path(path)) from exc
    if not isinstance(data, dict):
        raise PreflightError("manifest_root_invalid", "manifest root is not an object", observed=type(data).__name__)
    image_base = canonical_hex(data.get("image_base"), "image_base")
    if image_base != IMAGE_BASE:
        raise PreflightError("manifest_image_base_mismatch", "image_base is not 0x400000", expected="0x400000", observed=data.get("image_base"))
    probes = data.get("probes")
    if not isinstance(probes, list):
        raise PreflightError("manifest_probes_invalid", "probes is not a list", observed=type(probes).__name__)
    if len(probes) != len(expected_map):
        raise PreflightError("manifest_probe_count", "unexpected probe count", expected=len(expected_map), observed=len(probes))
    values = {}
    notes = {}
    for probe in probes:
        if not isinstance(probe, dict):
            raise PreflightError("manifest_probe_invalid", "probe entry is not an object", observed=type(probe).__name__)
        name = probe.get("name")
        if not isinstance(name, str) or not name:
            raise PreflightError("manifest_name_invalid", "probe lacks a valid name", observed=name)
        if name in values:
            raise PreflightError("manifest_duplicate_name", "duplicate probe name", observed=name)
        if "rva" not in probe:
            raise PreflightError("manifest_rva_missing", "probe lacks rva", observed=name)
        rva = canonical_hex(probe["rva"], "%s.rva" % name)
        note = probe.get("note", "")
        if not isinstance(note, str):
            raise PreflightError("manifest_note_invalid", "probe note is not text", observed=name)
        values[name] = rva
        notes[name] = note
    if set(values) != set(expected_map):
        raise PreflightError("manifest_key_set", "probe names do not match the exact contract", expected=sorted(expected_map), observed=sorted(values))
    actual_map = {name: values[name] for name in expected_map}
    if len(set(values.values())) != len(values):
        raise PreflightError("manifest_duplicate_value", "probe linked VA values must be unique", observed=sorted(values.values()))
    if actual_map != expected_map:
        differences = {name: {"expected": "0x%08x" % expected_map[name], "observed": "0x%08x" % values[name]} for name in expected_map if values[name] != expected_map[name]}
        raise PreflightError("manifest_map_mismatch", "probe linked VA does not match the exact contract", expected=differences, observed=actual_map)
    text = raw.decode("utf-8").lower()
    for stale in (STALE_GLOBAL_OPERAND, STALE_CAMERA_MODE_OPERAND):
        stale_text = "0x%08x" % stale
        if stale_text in text:
            raise PreflightError("stale_operand", "stale operand is present in manifest notes", expected="rejected", observed=stale_text)
    if require_cell_notes:
        required_notes = {
            "Simulator::Cell::MovePlayerToMousePosition": "0x%08x" % GLOBAL_OPERAND,
            "cam_mode_getter_FUN_00e4ce40": "0x%08x" % CAMERA_MODE_OPERAND,
        }
        for name, operand in required_notes.items():
            if operand not in notes[name].lower():
                raise PreflightError("current_operand_note_missing", "required current operand is missing from probe note", expected=operand, observed=notes[name])
    return {
        "path": display_path(path),
        "sha256": digest,
        "probe_count": len(probes),
        "names": [probe["name"] for probe in probes],
        "values": {name: "0x%08x" % values[name] for name in expected_map},
        "normalized": [{"name": name, "linked_va": "0x%08x" % values[name]} for probe in probes for name in [probe["name"]]],
        "notes": notes,
        "note_contract": {
            "stale_sentinels": ["0x%08x" % STALE_GLOBAL_OPERAND, "0x%08x" % STALE_CAMERA_MODE_OPERAND],
            "current_operands": ["0x%08x" % GLOBAL_OPERAND, "0x%08x" % CAMERA_MODE_OPERAND],
        },
    }


def static_result(checks):
    if any(item["status"] == "FAIL" for item in checks):
        return "FAIL"
    if any(item["status"] == "BLOCKED" for item in checks):
        return "BLOCKED"
    return "PASS"


def run_checks(exe_path=EXE, cell_manifest_path=CELL_MANIFEST, main_manifest_path=MAIN_MANIFEST):
    checks = []
    try:
        data = exe_path.read_bytes()
    except OSError as exc:
        checks.append(record("canonical_executable", "FAIL", "FILE_READ", display_path(exe_path), {"path": str(exe_path)}, None, str(exc)))
        data = b""
    size = len(data)
    digest = hashlib.sha256(data).hexdigest() if data else None
    checks.append(record("canonical_executable", "PASS" if size == EXPECTED_SIZE else "FAIL", "FILE_IDENTITY", display_path(exe_path), {"size": EXPECTED_SIZE}, {"size": size}, "size=%d" % size))
    checks.append(record("binary_hash", "PASS" if digest == EXPECTED_SHA256 else "FAIL", "FILE_IDENTITY", display_path(exe_path), EXPECTED_SHA256, digest, "sha256=%s" % digest))
    if not data:
        return checks
    try:
        pe = parse_pe(data)
    except PreflightError as exc:
        checks.append(exc.as_record("canonical_executable"))
        return checks
    pe_ok = pe["machine"] == 0x014C and pe["image_base"] == IMAGE_BASE
    checks.append(record("pe_identity", "PASS" if pe_ok else "FAIL", "STATIC_PARSE", display_path(exe_path), {"machine": "0x014c", "image_base": "0x400000"}, {"machine": "0x%04x" % pe["machine"], "image_base": "0x%08x" % pe["image_base"]}, "PE32/i386 preferred image base"))
    if not pe_ok:
        return checks
    try:
        target_offset = rva_to_offset(pe, TARGET_RVA)
        call_offset = rva_to_offset(pe, CALL_RVA)
    except PreflightError as exc:
        checks.append(exc.as_record("pe_mapping"))
        return checks
    mapping_ok = target_offset == TARGET_OFFSET and call_offset == CALL_OFFSET
    checks.append(record("pe_mapping", "PASS" if mapping_ok else "FAIL", "STATIC_PARSE", display_path(exe_path), {"target_offset": "0x%x" % TARGET_OFFSET, "call_offset": "0x%x" % CALL_OFFSET}, {"target_offset": "0x%x" % target_offset, "call_offset": "0x%x" % call_offset}, "linked-VA to PE-RVA to file-offset mapping"))
    target_actual = data[target_offset:target_offset + len(TARGET_BYTES)]
    target_ok = target_actual == TARGET_BYTES
    checks.append(record("target_bytes", "PASS" if target_ok else "FAIL", "FILE_BYTES", display_path(exe_path), "a1 04 3c 6b 01", target_actual.hex(" "), "target entry bytes at linked VA 0x%08x" % TARGET_VA))
    call_actual = data[call_offset:call_offset + len(CALL_BYTES)]
    call_ok = call_actual == CALL_BYTES
    checks.append(record("call_bytes", "PASS" if call_ok else "FAIL", "FILE_BYTES", display_path(exe_path), "e8 50 af fd ff", call_actual.hex(" "), "direct call bytes at linked VA 0x%08x" % CALL_VA))
    if call_ok:
        displacement = struct.unpack_from("<i", call_actual, 1)[0]
        decoded_target = (CALL_VA + 5 + displacement) & 0xFFFFFFFF
        decode_ok = decoded_target == TARGET_VA
        checks.append(record("call_decode", "PASS" if decode_ok else "FAIL", "STATIC_DECODE", display_path(exe_path), "0x%08x" % TARGET_VA, "0x%08x" % decoded_target, "rel32 continuation=0x%08x" % CONTINUATION_VA))
    else:
        checks.append(record("call_decode", "FAIL", "STATIC_DECODE", display_path(exe_path), "0x%08x" % TARGET_VA, None, "not_checked_due_to_bad_bytes"))
    if target_ok:
        operand = struct.unpack_from("<I", target_actual, 1)[0]
        operand_ok = operand == GLOBAL_OPERAND and operand != STALE_GLOBAL_OPERAND
        checks.append(record("binary_interpretation", "PASS" if operand_ok else "FAIL", "STATIC_DECODE", display_path(exe_path), {"current": "0x%08x" % GLOBAL_OPERAND, "rejected_stale": "0x%08x" % STALE_GLOBAL_OPERAND}, {"operand": "0x%08x" % operand}, "mov eax,[sCellGame]; stale sentinel is not an alias"))
    else:
        checks.append(record("binary_interpretation", "FAIL", "STATIC_DECODE", display_path(exe_path), "0x%08x" % GLOBAL_OPERAND, None, "not_checked_due_to_bad_bytes"))
    checks.append(record("static_abi", "STATIC_ASSERTED", "STATIC_ASSERTION", "repository_static_record", {"calling_convention": "x86-32 cdecl", "return": "void", "argument": "float at [ESP+4]"}, None, "caller and ABI are not independently proven by this standalone file-only preflight"))
    checks.append(record("caller_continuation", "STATIC_ASSERTED", "STATIC_ASSERTION", "repository_static_record", {"caller": "FUN_00E806B0", "continuation": "0x%08x" % CONTINUATION_VA}, None, "direct-site arithmetic is checked; complete dynamic callers remain UNKNOWN"))
    for name, path, expected_map, expected_hash, cell_notes in (
        ("main_menu_probe_manifest", main_manifest_path, MAIN_PROBES, EXPECTED_MAIN_SHA256, False),
        ("cell_probe_manifest", cell_manifest_path, CELL_PROBES, EXPECTED_CELL_SHA256, True),
    ):
        try:
            manifest = read_manifest(path, expected_map, expected_hash, cell_notes)
            checks.append(record(name, "PASS", "MANIFEST_CONTRACT", manifest["path"], {"sha256": expected_hash, "probe_count": len(expected_map), "exact_keys": sorted(expected_map)}, {"sha256": manifest["sha256"], "probe_count": manifest["probe_count"], "normalized": manifest["normalized"]}, "exact name-to-linked-VA map; stale sentinels rejected; current operands recorded in notes"))
        except PreflightError as exc:
            checks.append(exc.as_record(display_path(path)))
    return checks


def build_report(checks):
    static_overall = static_result(checks)
    readiness = "READY" if static_overall == "PASS" else "BLOCKED" if static_overall == "BLOCKED" else "NOT_READY"
    gates = {}
    for gate in ("m0", "m1", "m2"):
        gates[gate] = {
            "static_preflight": static_overall,
            "static_artifact_readiness": readiness,
            "full_preflight": "BLOCKED",
            "runtime_evidence": "NOT_RUN",
        }
    return {
        "schema": "pkg07-preflight-2",
        "static_overall": static_overall,
        "runtime_status": "NOT_RUN",
        "preflight_enforcement": "ADVISORY_STANDALONE",
        "gates": gates,
        "notes": {
            "address_convention": "probe rva fields are linked VAs at image_base=0x00400000",
            "stale_sentinels": ["0x%08x" % STALE_GLOBAL_OPERAND, "0x%08x" % STALE_CAMERA_MODE_OPERAND],
            "current_operands": ["0x%08x" % GLOBAL_OPERAND, "0x%08x" % CAMERA_MODE_OPERAND],
            "dynamic_callers": "UNKNOWN",
        },
        "runtime_launched": False,
        "process_memory_read": False,
        "process_memory_written": False,
        "canonical_kg_written": False,
        "checks": checks,
    }


def main():
    parser = argparse.ArgumentParser(description="PKG-07 read-only static preflight")
    parser.add_argument("--json", action="store_true", help="emit machine-readable JSON")
    args = parser.parse_args()
    report = build_report(run_checks())
    static_overall = report["static_overall"]
    if args.json:
        print(json.dumps(report, indent=2, sort_keys=True))
    else:
        print("PKG-07 preflight: static=%s runtime=NOT_RUN" % static_overall)
        for item in report["checks"]:
            print("[%s] %s: %s" % (item["status"], item["id"], item["detail"]))
    return 1 if static_overall == "FAIL" else 2 if static_overall == "BLOCKED" else 0


if __name__ == "__main__":
    sys.exit(main())
