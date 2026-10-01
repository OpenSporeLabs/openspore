# Evidence 0x00b1e4d0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `2e6130f4a992f7c26cd5346756b787af486a9192adec976ff1569c980dc64265`

## abi

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function, tools/reconstruction_tooling/vftables.py@25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e`

```json
{
  "abi": {
    "architecture": "x86-32",
    "calling_convention": "__thiscall",
    "receiver": false,
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "874551e0d330478a64eb55a48b9f8997b6099abf95600c5df319021161bc256b",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall",
      "__fastcall"
    ],
    "confidence": "INFERRED",
    "corroboration": "not_available"
  },
  "cross_validation": {
    "agreement": false,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 0,
    "persisted": "no_information",
    "persisted_calling_convention": null
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0003"
      ],
      "claim": "the caller cleans up the stack: a bare RET is compatible with caller cleanup and, for a zero-parameter __stdcall, with zero bytes of callee cleanup",
      "confidence": "INFERRED",
      "id": "C5",
      "value": {
        "bytes": 0,
        "side": "caller"
      }
    },
    {
      "based_on": [
        "obs-0003"
      ],
      "claim": "ECX is never read in any form, so there is no register receiver",
      "confidence": "OBSERVED",
      "id": "R2",
      "value": {
        "present": false
      }
    },
    {
      "based_on": [
        "obs-0003"
      ],
      "claim": "calling convention is __thiscall: 0x00b1e4d0 is slot 10 of the vptr-backed vftable at 0x013f69b4, so it is a virtual member of some class; the callee pops nothing and no stack word is read as an argument, so the receiver is in a register, and ECX is the only one that carries one",
      "confidence": "INFERRED",
      "id": "V1-VFT",
      "value": {
        "cleanup_side": "caller",
        "membership_count": 286,
        "receiver_provenance": "vftable_slot",
        "receiver_register": "ECX",
        "slot_index": 10,
        "table": "0x013f69b4"
      }
    },
    {
      "based_on": [
        "obs-0003"
      ],
      "claim": "entry slot 0 is not written through a pointer",
      "confidence": "APPROXIMATION",
      "id": "S2",
      "value": {
        "present": false
      }
    },
    {
      "based_on": [
        "obs-0003"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0003"
      ],
      "claim": "the last value written to EAX classifies as integral",
      "confidence": "INFERRED",
      "id": "RT2",
      "value": {
        "register_class": "integral"
      }
    }
  ],
  "observations": [
    {
      "at": "0x00b1e4d0",
      "count": 1,
      "first_use": 0,
      "first_write_index": 0,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "XOR AL,AL",
      "reg": "EAX"
    },
    {
      "at": "0x00b1e4d0",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "XOR AL,AL",
      "reg": "EAX",
      "write_kind": "zero"
    },
    {
      "at": "0x00b1e4d2",
      "form": "RET",
      "id": "obs-0003",
      "imm": null,
      "index": 1,
      "kind": "RET",
      "raw": "RET"
    }
  ],
  "parse": {
    "declared_count": 2,
    "degraded": false,
    "esp_unresolved": false,
    "flow_complete": true,
    "frame": {
      "and_esp": null,
      "ebp_is_general_register": false,
      "fp": false,
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": false,
      "push_ebp_at": null,
      "sub": null
    },
    "layout": "json_instruction_list",
    "local_extent": 0,
    "unparsed": 0
  },
  "receiver": {
    "bounds_only": true,
    "confidence": "OBSERVED",
    "distinct_offsets": 0,
    "max_offset": null,
    "offsets": [],
    "present": false,
    "provenance": "vftable_slot",
    "register": "ECX",
    "shape": null,
    "written_through": 0
  },
  "return": {
    "aggregate_evidence": {
      "bulk_write": false
    },
    "confidence": "INFERRED",
    "register": "EAX",
    "register_class": "integral",
    "type": null,
    "void_possible": false
  },
  "schema": "openspore-abi-inference-1",
  "seh_or_cookie_frame": false,
  "sret": {
    "ambiguity": null,
    "basis": "entry slot 0 is not written through a pointer; DERIVED absence is weak, a struct filled through another alias would be missed",
    "candidates": null,
    "confidence": "APPROXIMATION",
    "eax_holds_slot0_at_ret": null,
    "hypothesis_confidence": null,
    "present": false,
    "slot": null,
    "this_interaction": null
  },
  "stack_arguments": {
    "confidence": "APPROXIMATION",
    "derived_slots": 0,
    "gaps": 0,
    "not_complete": false,
    "observed_slots": 0,
    "slots": [],
    "total_bytes": 0,
    "widths_ambiguous": false
  },
  "tail_call": {
    "after_frame_setup": false,
    "form": null,
    "present": false,
    "target": null
  },
  "target": {
    "address_available": true,
    "image_base": "0x00400000",
    "instructions": 2,
    "syntax": "intel",
    "va": "0x00b1e4d0"
  },
  "variadic": "UNKNOWN",
  "verdict": "ABI_INFERRED"
}
```

## abi_derived

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function, tools/reconstruction_tooling/vftables.py@25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e`

```json
{
  "abi": {
    "architecture": "x86-32",
    "calling_convention": "__thiscall",
    "receiver": false,
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "874551e0d330478a64eb55a48b9f8997b6099abf95600c5df319021161bc256b",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall",
      "__fastcall"
    ],
    "confidence": "INFERRED",
    "corroboration": "not_available"
  },
  "cross_validation": {
    "agreement": false,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 0,
    "persisted": "no_information",
    "persisted_calling_convention": null
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0003"
      ],
      "claim": "the caller cleans up the stack: a bare RET is compatible with caller cleanup and, for a zero-parameter __stdcall, with zero bytes of callee cleanup",
      "confidence": "INFERRED",
      "id": "C5",
      "value": {
        "bytes": 0,
        "side": "caller"
      }
    },
    {
      "based_on": [
        "obs-0003"
      ],
      "claim": "ECX is never read in any form, so there is no register receiver",
      "confidence": "OBSERVED",
      "id": "R2",
      "value": {
        "present": false
      }
    },
    {
      "based_on": [
        "obs-0003"
      ],
      "claim": "calling convention is __thiscall: 0x00b1e4d0 is slot 10 of the vptr-backed vftable at 0x013f69b4, so it is a virtual member of some class; the callee pops nothing and no stack word is read as an argument, so the receiver is in a register, and ECX is the only one that carries one",
      "confidence": "INFERRED",
      "id": "V1-VFT",
      "value": {
        "cleanup_side": "caller",
        "membership_count": 286,
        "receiver_provenance": "vftable_slot",
        "receiver_register": "ECX",
        "slot_index": 10,
        "table": "0x013f69b4"
      }
    },
    {
      "based_on": [
        "obs-0003"
      ],
      "claim": "entry slot 0 is not written through a pointer",
      "confidence": "APPROXIMATION",
      "id": "S2",
      "value": {
        "present": false
      }
    },
    {
      "based_on": [
        "obs-0003"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0003"
      ],
      "claim": "the last value written to EAX classifies as integral",
      "confidence": "INFERRED",
      "id": "RT2",
      "value": {
        "register_class": "integral"
      }
    }
  ],
  "observations": [
    {
      "at": "0x00b1e4d0",
      "count": 1,
      "first_use": 0,
      "first_write_index": 0,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "XOR AL,AL",
      "reg": "EAX"
    },
    {
      "at": "0x00b1e4d0",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "XOR AL,AL",
      "reg": "EAX",
      "write_kind": "zero"
    },
    {
      "at": "0x00b1e4d2",
      "form": "RET",
      "id": "obs-0003",
      "imm": null,
      "index": 1,
      "kind": "RET",
      "raw": "RET"
    }
  ],
  "parse": {
    "declared_count": 2,
    "degraded": false,
    "esp_unresolved": false,
    "flow_complete": true,
    "frame": {
      "and_esp": null,
      "ebp_is_general_register": false,
      "fp": false,
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": false,
      "push_ebp_at": null,
      "sub": null
    },
    "layout": "json_instruction_list",
    "local_extent": 0,
    "unparsed": 0
  },
  "receiver": {
    "bounds_only": true,
    "confidence": "OBSERVED",
    "distinct_offsets": 0,
    "max_offset": null,
    "offsets": [],
    "present": false,
    "provenance": "vftable_slot",
    "register": "ECX",
    "shape": null,
    "written_through": 0
  },
  "return": {
    "aggregate_evidence": {
      "bulk_write": false
    },
    "confidence": "INFERRED",
    "register": "EAX",
    "register_class": "integral",
    "type": null,
    "void_possible": false
  },
  "schema": "openspore-abi-inference-1",
  "seh_or_cookie_frame": false,
  "sret": {
    "ambiguity": null,
    "basis": "entry slot 0 is not written through a pointer; DERIVED absence is weak, a struct filled through another alias would be missed",
    "candidates": null,
    "confidence": "APPROXIMATION",
    "eax_holds_slot0_at_ret": null,
    "hypothesis_confidence": null,
    "present": false,
    "slot": null,
    "this_interaction": null
  },
  "stack_arguments": {
    "confidence": "APPROXIMATION",
    "derived_slots": 0,
    "gaps": 0,
    "not_complete": false,
    "observed_slots": 0,
    "slots": [],
    "total_bytes": 0,
    "widths_ambiguous": false
  },
  "tail_call": {
    "after_frame_setup": false,
    "form": null,
    "present": false,
    "target": null
  },
  "target": {
    "address_available": true,
    "image_base": "0x00400000",
    "instructions": 2,
    "syntax": "intel",
    "va": "0x00b1e4d0"
  },
  "variadic": "UNKNOWN",
  "verdict": "ABI_INFERRED"
}
```

## callees_dependencies

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## callers_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00404660"
  },
  {
    "name": "FUN_005dda30",
    "reconstructed": true,
    "va": "0x005dda30"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x006a8610"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d77400"
  }
]
```

## contradictions

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## decompilation

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: ``

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 2,
  "instructions": [
    {
      "address": "00b1e4d0",
      "instruction": "XOR AL,AL"
    },
    {
      "address": "00b1e4d2",
      "instruction": "RET"
    }
  ]
}
```

## external_callees

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## function_identity

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "original_bytes": 9723,
  "preview": "{\n  \"abi\": {},\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013f69b4,vtable:0x014105ac\"\n      ],\n      \"package\": \"PKG-CAMERA-WAVE8\",\n      \"score\": 4,\n      \"symbol\": \"editor_camera_func24h_005a2050\",\n      \"va\": \"0x005a2050\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013f69b4\"\n      ],\n      \"package\": \"PKG-CAMERA-WAVE8\",\n      \"score\": 4,\n      \"symbol\": \"editor_camera_func54h_005a2320\",\n      \"va\": \"0x005a2320\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x013ff6ac\"\n      ],\n      \"package\": \"PKG-16-SPOREPEDIA-ONLINE\",\n      \"score\": 4,\n      \"symbol\": \"Sporepedia_cSPAssetDataOTDB_IsEditable_00641400\",\n      \"va\": \"0x00641400\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x013ff6ac\"\n      ],\n      \"package\": \"PKG-SPOREPEDIA-ACCESSORS-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"sporepedia_func7ch_00641460\",\n      \"va\": \"0x00641460\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x01462764\"\n      ],\n      \"package\": \"PKG-16-SPOREPEDIA-ONLINE\",\n      \"score\": 4,\n      \"symbol\": \"Sporepedia_cSPAssetDataOTDB_HasName_raw_00641770\",\n      \"va\": \"0x00641770\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x01462764\"\n      ],\n      \"package\": \"PKG-SPOREPEDIA-ACCESSORS-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"sporepedia_func3ch_006417b0\",\n      \"va\": \"0x006417b0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x01462764\"\n      ],\n      \"package\": \"PKG-16-SPOREPEDIA-ONLINE\",\n      \"score\": 4,\n      \"symbol\": \"Sporepedia_cSPAssetDataOTDB_GetAssetID_address_006417c0\",\n      \"va\": \"0x006417c0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x01462764\"\n      ],\n      \"package\": \"PKG-SPOREPEDIA-ACCESSORS-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"sporepedia_get_author_name_00641810\",\n      \"va\": \"0x00641810\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"sporepedia-online\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00404660\"\n      },\n      {\n        \"name\": \"FUN_005dda30\",\n        \"reconstructed\": true,\n        \"va\": \"0x005dda30\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x006a8610\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d77400\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00404a53\",\n        \"direction\": \"in\",\n        \"other\": \"0x00404660\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005ddb21\",\n        \"direction\": \"in\",\n        \"other\": \"0x005dda30\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006a89ef\",\n        \"direction\": \"in\",\n        \"other\": \"0x006a8610\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006a8fe7\",\n        \"direction\": \"in\",\n        \"other\": \"0x006a8610\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00d77433\",\n        \"direction\": \"in\",\n        \"other\": \"0x00d77400\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 4,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [\n      \"0x005dda30\"\n    ],\n    \"scc\": {\n      \"id\": \"scc-0349\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"INFERRED\",\n  \"globals\": [],\n  \"integration_status\": null,\n  \"name\": \"FUN_00b1e4d0\",\n  \"normalized_symbol\": \"FUN_00b1e4d0\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"queue_candidate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"candidate\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [],\n    \"validated\": 0\n  },\n  \"runtime_gated\": false,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": null,\n  \"services\": [],\n  \"source\": {\n    \"decomp\": null,\n    \"file\": null,\n    \"files\": [],\n    \"handoffs\": [],\n    \"metadata\": [],\n    \"provenance\": []\n  },\n  \"status\": \"candidate\",\n  \"subsystem\": \"Sporepedia\",\n  \"triage\": {\n    \"category\": \"GAMEPLAY_LOGIC\",\n    \"cluster\": \"sporepedia-online\",\n    \"db_triage_status\": \"candidate\",\n    \"decomp_path\": null,\n    \"dependencies\": [],\n    \"evidence\": \"INFERRED\",\n    \"kg_node_id\": \"fun:00b1e4d0\",\n    \"name\": \"FUN_00b1e4d0\",\n    \"priority\": \"P1\",\n    \"provenance\": {\n      \"classifier\": \"triage-v5\",\n      \"sdk_name\": null,\n      \"snapshot\": \"f0e310e0\",\n      \"snapshot_sha256\": \"f0e310e0c83fc960ed38d490ff6d2a78d53925969206b4c4db7a012ddbf8b54b\",\n      \"vtable_addrs\": [\n        \"013f69b4\",\n        \"013f9e20\",\n        \"0
[TRUNCATED]
```

## ghidra_function

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089`

```json
{
  "binary_available": true,
  "binary_sha256": "25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e",
  "body_end": "00b1e4d2",
  "body_span_bytes": 3,
  "body_start": "00b1e4d0",
  "callees": [],
  "callers": [
    "FUN_006a8610",
    "FUN_00404660",
    "FUN_005dda30",
    "FUN_00d77400"
  ],
  "classification": "stub",
  "dispatch": null,
  "entry_point": "00b1e4d0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00b1e4d0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x71e4d0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00b1e4d0(void)",
  "size_bytes": 3,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00b1e4d0",
  "vtables": {
    "referenced_by_vtables": [
      "0x013fcc08",
      "0x01418838",
      "0x01441c18",
      "0x01443318",
      "0x014793e0",
      "0x013fcc48",
      "0x013fdc38",
      "0x013ff648",
      "0x014368c4",
      "0x01462764",
      "0x01479424",
      "0x0147c9e8",
      "0x0147ca30",
      "0x0147ca70",
      "0x0147caf8",
      "0x0147cbbc",
      "0x014807dc",
      "0x01480904",
      "0x01480a14",
      "0x01480b24"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 100,
  "xrefs": [
    {
      "from": "00404a53"
    },
    {
      "from": "005ddb21"
    },
    {
      "from": "00d77433"
    },
    {
      "from": "006a89ef"
    },
    {
      "from": "006a8fe7"
    },
    {
      "from": "00a31334"
    },
    {
      "from": "013f69dc"
    },
    {
      "from": "013f9e7c"
    },
    {
      "from": "013fc5dc"
    },
    {
      "from": "013fcc9c"
    },
    {
      "from": "013fdc90"
    },
    {
      "from": "013ff6a0"
    },
    {
      "from": "013ff6cc"
    },
    {
      "from": "014627b0"
    },
    {
      "from": "014627dc"
    },
    {
      "from": "0140051c"
    },
    {
      "from": "0140053c"
    },
    {
      "from": "0140055c"
    },
    {
      "from": "014005dc"
    },
    {
      "from": "014005fc"
    },
    {
      "from": "0140061c"
    },
    {
      "from": "014004fc"
    },
    {
      "from": "0140177c"
    },
    {
      "from": "0140a340"
    },
    {
      "from": "014105d4"
    },
    {
      "from": "014128bc"
    },
    {
      "from": "01412bc4"
    },
    {
      "from": "01413b30"
    },
    {
      "from": "01413b34"
    },
    {
      "from": "01413b38"
    },
    {
      "from": "01414b68"
    },
    {
      "from": "01414d38"
    },
    {
      "from": "01417e04"
    },
    {
      "from": "01417e24"
    },
    {
      "from": "01418890"
    },
    {
      "from": "01419a98"
    },
    {
      "from": "01419cc8"
    },
    {
      "from": "0141ace8"
    },
    {
      "from": "01436944"
    },
    {
      "from": "01436dc0"
    },
    {
      "from": "01436f74"
    },
    {
      "from": "01436f78"
    },
    {
      "from": "01436d74"
    },
    {
      "from": "01436d78"
    },
    {
      "from": "01441c70"
    },
    {
      "from": "01443370"
    },
    {
      "from": "01445588"
    },
    {
      "from": "01445c84"
    },
    {
      "from": "014465e8"
    },
    {
      "from": "01455958"
    },
    {
      "from": "01455988"
    },
    {
      "from": "0145766c"
    },
    {
      "from": "01459ce0"
    },
    {
      "from": "0145a630"
    },
    {
      "from": "0145c548"
    },
    {
      "from": "0145cf9c"
    },
    {
      "from": "01466804"
    },
    {
      "from": "0145d7b0"
    },
    {
      "from": "0145dccc"
    },
    {
      "from": "0145ff70"
    },
    {
      "from": "0145e9a8"
    },
    {
      "from": "014657e0"
    },
    {
      "from": "01466ac0"
    },
    {
      "from": "01466cc4"
    },
    {
      "from": "01466c74"
    },
    {
      "from": "01467130"
    },
    {
      "from": "01466f94"
    },
    {
      "from": "01467368"
    },
    {
      "from": "014671cc"
    },
    {
      "from": "01467178"
    },
    {
      "from": "014677e0"
    },
    {
      "from": "01467644"
    },
    {
      "from": "014675a0"
    },
    {
      "from": "01467404"
    },
    {
      "from": "01467a18"
    },
    {
      "from": "0146787c"
    },
    {
      "from": "01467ca8"
    },
    {
      "from": "01467b0c"
    },
    {
      "from": "01468038"
    },
    {
      "from": "014685dc"
    },
    {
      "from": "01468530"
    },
    {
      "from": "01468ee8"
    },
    {
      "from": "01469030"
    },
    {
      "from": "0146992c"
    },
    {
      "from": "01469a88"
    },
    {
      "from": "01469a04"
    },
    {
      "from": "01469ecc"
    },
    {
      "from": "0146a488"
    },
    {
      "from": "0146a3dc"
    },
    {
      "from": "0146ab4c"
    },
    {
      "from": "0146bbe4"
    },
    {
      "from": "0146c250"
    },
    {
      "from": "0146c1a4"
    },
    {
      "from": "0146c3e0"
    },
    {
      "from": "0146c5d4"
    },
    {
      "from": "0146c7cc"
    },
    {
      "from": "0146ca10"
    },
    {
      "from": "0146cc20"
    },
    {
      "from": "0146cb8c"
    },
    {
      "from": "0146cde8"
    }
  ]
}
```

## globals

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [],
  "handoffs": [],
  "metadata": []
}
```

## runtime

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## runtime_metadata

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "blocking_reason": null,
  "gates": [],
  "validated": 0
}
```

## semantic_hypotheses

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

## status

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "runtime_gated": false,
  "runtime_validated": 0,
  "status": "candidate"
}
```

## types

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x013f69b4",
  "vtable:0x013f9e20",
  "vtable:0x013fcc08",
  "vtable:0x013fcc48",
  "vtable:0x013fdc38",
  "vtable:0x013ff648",
  "vtable:0x013ff6ac",
  "vtable:0x014004e0",
  "vtable:0x01401748",
  "vtable:0x0140a328",
  "vtable:0x014105ac",
  "vtable:0x01410ea8",
  "vtable:0x014128a8",
  "vtable:0x01412b9c",
  "vtable:0x01413acc",
  "vtable:0x01414b10"
]
```

## Conflicts

```json
[]
```
