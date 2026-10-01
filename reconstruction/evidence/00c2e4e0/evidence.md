# Evidence 0x00c2e4e0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `d955de24af726988f5e68d2e94d0642a50014dfa4e4eadd5f1e4a36a5c39fb53`

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
    "return_semantics": "unclassified_in_EAX;void_possible",
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
  "content_sha256": "fc27f70eebae14cd612b14c973aa2cc028a19fe6ad9a9c23077fa73cc26f8e0f",
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
        "obs-0001"
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
        "obs-0001"
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
        "obs-0001"
      ],
      "claim": "calling convention is __thiscall: 0x00c2e4e0 is slot 12 of the vptr-backed vftable at 0x013f69b4, so it is a virtual member of some class; the callee pops nothing and no stack word is read as an argument, so the receiver is in a register, and ECX is the only one that carries one",
      "confidence": "INFERRED",
      "id": "V1-VFT",
      "value": {
        "cleanup_side": "caller",
        "membership_count": 479,
        "receiver_provenance": "vftable_slot",
        "receiver_register": "ECX",
        "slot_index": 12,
        "table": "0x013f69b4"
      }
    },
    {
      "based_on": [
        "obs-0001"
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
        "obs-0001"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0001"
      ],
      "claim": "the last value written to EAX classifies as aggregate_unknown",
      "confidence": "INFERRED",
      "id": "RT2",
      "value": {
        "register_class": "aggregate_unknown"
      }
    },
    {
      "based_on": [
        "obs-0001"
      ],
      "claim": "EAX is never written and no call can clobber it, so a void return is possible; this is a flag, never a type",
      "confidence": "APPROXIMATION",
      "id": "RT3",
      "value": {
        "void_possible": true
      }
    }
  ],
  "observations": [
    {
      "at": "0x00c2e4e0",
      "form": "RET",
      "id": "obs-0001",
      "imm": null,
      "index": 0,
      "kind": "RET",
      "raw": "RET"
    }
  ],
  "parse": {
    "declared_count": 1,
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
    "register_class": "aggregate_unknown",
    "type": null,
    "void_possible": true
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
    "instructions": 1,
    "syntax": "intel",
    "va": "0x00c2e4e0"
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
    "return_semantics": "unclassified_in_EAX;void_possible",
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
  "content_sha256": "fc27f70eebae14cd612b14c973aa2cc028a19fe6ad9a9c23077fa73cc26f8e0f",
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
        "obs-0001"
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
        "obs-0001"
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
        "obs-0001"
      ],
      "claim": "calling convention is __thiscall: 0x00c2e4e0 is slot 12 of the vptr-backed vftable at 0x013f69b4, so it is a virtual member of some class; the callee pops nothing and no stack word is read as an argument, so the receiver is in a register, and ECX is the only one that carries one",
      "confidence": "INFERRED",
      "id": "V1-VFT",
      "value": {
        "cleanup_side": "caller",
        "membership_count": 479,
        "receiver_provenance": "vftable_slot",
        "receiver_register": "ECX",
        "slot_index": 12,
        "table": "0x013f69b4"
      }
    },
    {
      "based_on": [
        "obs-0001"
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
        "obs-0001"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0001"
      ],
      "claim": "the last value written to EAX classifies as aggregate_unknown",
      "confidence": "INFERRED",
      "id": "RT2",
      "value": {
        "register_class": "aggregate_unknown"
      }
    },
    {
      "based_on": [
        "obs-0001"
      ],
      "claim": "EAX is never written and no call can clobber it, so a void return is possible; this is a flag, never a type",
      "confidence": "APPROXIMATION",
      "id": "RT3",
      "value": {
        "void_possible": true
      }
    }
  ],
  "observations": [
    {
      "at": "0x00c2e4e0",
      "form": "RET",
      "id": "obs-0001",
      "imm": null,
      "index": 0,
      "kind": "RET",
      "raw": "RET"
    }
  ],
  "parse": {
    "declared_count": 1,
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
    "register_class": "aggregate_unknown",
    "type": null,
    "void_possible": true
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
    "instructions": 1,
    "syntax": "intel",
    "va": "0x00c2e4e0"
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
    "va": "0x00496d30"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x004b4470"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x004b4930"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x004b76c0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00577c40"
  },
  {
    "name": "editor_input_00588570",
    "reconstructed": true,
    "va": "0x00588570"
  },
  {
    "name": "Editors::cEditor::Update",
    "reconstructed": false,
    "va": "0x0058be50"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00599040"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0059c640"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0060ceb0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x006275d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x007e6470"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0082f020"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x008639f0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00987900"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00999110"
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
  "count": 1,
  "instructions": [
    {
      "address": "00c2e4e0",
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
  "original_bytes": 20120,
  "preview": "{\n  \"abi\": {},\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01452b00,vtable:0x0145c0b4\"\n      ],\n      \"package\": \"PKG-WAVE6-CONTAINERS-MEMORY\",\n      \"score\": 4,\n      \"symbol\": \"wave6_reference_00432a50\",\n      \"va\": \"0x00432a50\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013f69b4,vtable:0x014105ac\"\n      ],\n      \"package\": \"PKG-CAMERA-WAVE8\",\n      \"score\": 4,\n      \"symbol\": \"editor_camera_func24h_005a2050\",\n      \"va\": \"0x005a2050\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013f69b4\"\n      ],\n      \"package\": \"PKG-CAMERA-WAVE8\",\n      \"score\": 4,\n      \"symbol\": \"editor_camera_func54h_005a2320\",\n      \"va\": \"0x005a2320\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x0147c9e8\"\n      ],\n      \"package\": \"PKG-16-SPOREPEDIA-ONLINE\",\n      \"score\": 4,\n      \"symbol\": \"Sporepedia_cSPAssetDataOTDB_IsEditable_00641400\",\n      \"va\": \"0x00641400\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x0147c9e8\"\n      ],\n      \"package\": \"PKG-SPOREPEDIA-ACCESSORS-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"sporepedia_func7ch_00641460\",\n      \"va\": \"0x00641460\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x0147c9e8\"\n      ],\n      \"package\": \"PKG-16-SPOREPEDIA-ONLINE\",\n      \"score\": 4,\n      \"symbol\": \"Sporepedia_cSPAssetDataOTDB_HasName_raw_00641770\",\n      \"va\": \"0x00641770\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x0147c9e8\"\n      ],\n      \"package\": \"PKG-SPOREPEDIA-ACCESSORS-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"sporepedia_func3ch_006417b0\",\n      \"va\": \"0x006417b0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x0147c9e8\"\n      ],\n      \"package\": \"PKG-16-SPOREPEDIA-ONLINE\",\n      \"score\": 4,\n      \"symbol\": \"Sporepedia_cSPAssetDataOTDB_GetAssetID_address_006417c0\",\n      \"va\": \"0x006417c0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"sporepedia-online\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00496d30\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004b4470\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004b4930\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004b76c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00577c40\"\n      },\n      {\n        \"name\": \"editor_input_00588570\",\n        \"reconstructed\": true,\n        \"va\": \"0x00588570\"\n      },\n      {\n        \"name\": \"Editors::cEditor::Update\",\n        \"reconstructed\": false,\n        \"va\": \"0x0058be50\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00599040\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0059c640\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0060ceb0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x006275d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007e6470\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0082f020\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x008639f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00987900\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00999110\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0099ed90\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x009a1ee0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x009a9920\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x009ff4b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00a168c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00a4a320\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00a4a870\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00a4a9a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00a4b140\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00a4b1c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00a4b250\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00a4b2f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00a4b630\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00a4c170\"\n      },\
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
  "body_end": "00c2e4e0",
  "body_span_bytes": 1,
  "body_start": "00c2e4e0",
  "callees": [],
  "callers": [
    "Unwind@0120fa90",
    "FUN_00b5cc80",
    "FUN_00a514d0",
    "FUN_00a4f130",
    "FUN_00c5f360",
    "Unwind@01210751",
    "FUN_00b20e40",
    "FUN_00c5a0b0",
    "FUN_00a4b2f0",
    "FUN_0082f020",
    "Unwind@0120de80",
    "FUN_00a4b140",
    "FUN_00ef0ee0",
    "FUN_00c2cac0",
    "Unwind@0120f980",
    "Unwind@0120fb32",
    "FUN_00e61b00",
    "FUN_00d739c0",
    "FUN_009a1ee0",
    "Unwind@01210980",
    "FUN_004b4470",
    "Unwind@0120d24e",
    "FUN_00a4f0b0",
    "FUN_00a4f950",
    "FUN_010743a0",
    "FUN_00a4c940",
    "FUN_00a51e20",
    "FUN_01099690",
    "FUN_0060ceb0",
    "FUN_0108fba0",
    "FUN_00e4c9e0",
    "Unwind@012174ca",
    "FUN_00a4c740",
    "Unwind@01210d1c",
    "FUN_0112c880",
    "FUN_00a4d1d0",
    "FUN_00a4c860",
    "Unwind@012111b4",
    "FUN_00a4f0e0",
    "FUN_0059c640",
    "FUN_00a51cf0",
    "FUN_0112c9e0",
    "FUN_00bf8170",
    "FUN_00a4a320",
    "Unwind@012112cf",
    "Unwind@012111e1",
    "Unwind@01219c70",
    "FUN_00f18660",
    "Unwind@01210805",
    "FUN_010377f0",
    "Unwind@01219c84",
    "Unwind@01210832",
    "FUN_00b60d80",
    "FUN_00a4a9a0",
    "FUN_00fda390",
    "FUN_0099ed90",
    "FUN_00c51e40",
    "FUN_0108bba0",
    "FUN_00c4f210",
    "FUN_00b33350",
    "Unwind@01210d33",
    "FUN_0100a960",
    "FUN_00ebfad0",
    "FUN_011378e0",
    "Unwind@0120c33b",
    "FUN_00b22960",
    "FUN_00c62170",
    "FUN_00a4b250",
    "FUN_010f25f0",
    "FUN_00a168c0",
    "Unwind@0121115a",
    "FUN_00b1f960",
    "FUN_00dc8f30",
    "FUN_00a4f9e0",
    "FUN_00bd7640",
    "Unwind@01219b50",
    "FUN_00a4e9c0",
    "FUN_00fc8660",
    "Unwind@01211065",
    "FUN_00b20c60",
    "FUN_00b8df20",
    "Unwind@01211e58",
    "FUN_00c4db40",
    "Unwind@012106f7",
    "Unwind@012120ab",
    "FUN_00f97130",
    "Unwind@0120fad0",
    "FUN_00c97de0",
    "FUN_00fedb50",
    "FUN_00599040",
    "UTFWin::StdDrawable::SetScaleType",
    "FUN_00a4c470",
    "Unwind@01211100",
    "FUN_007e6470",
    "FUN_00b6d190",
    "FUN_00cadb00",
    "FUN_00f347e0",
    "Unwind@01211e71",
    "FUN_00e64090",
    "FUN_00d79000",
    "FUN_00a4e560",
    "FUN_00c4bd00",
    "FUN_00a4fd00",
    "Unwind@0120fb10",
    "FUN_00a4a870",
    "FUN_00c2c7d6",
    "Editors::cEditor::Update",
    "Resource::PFRecordRead::GetSize",
    "Unwind@012106ca",
    "FUN_00a4f080",
    "Unwind@0120c9e0",
    "FUN_00a4b1c0",
    "FUN_00a4dc60",
    "FUN_00fca0b0",
    "Unwind@0120fa67",
    "FUN_00fcb860",
    "FUN_00a51240",
    "FUN_00bf36f0",
    "Unwind@0121086a",
    "FUN_00d56c20",
    "FUN_01139410",
    "FUN_00d42570",
    "FUN_00a51450",
    "Unwind@0121077e",
    "FUN_00cb2770",
    "FUN_00a4c170",
    "Unwind@012107ab",
    "FUN_00cb0130",
    "Unwind@0120c368",
    "FUN_00f21040",
    "FUN_004b76c0",
    "Unwind@012108ae",
    "FUN_0109d9c0",
    "FUN_010938e0",
    "FUN_00ee9350",
    "FUN_00b5d870",
    "FUN_01139eb0",
    "FUN_00999110",
    "Unwind@0120fa50",
    "Unwind@0120faa7",
    "Unwind@01211187",
    "Unwind@01211d68",
    "Unwind@01215ef0",
    "Unwind@0120f710",
    "FUN_00a51c60",
    "FUN_00b5ce70",
    "Unwind@0121088c",
    "FUN_00c299e0",
    "FUN_00c4e230",
    "FUN_00c004a0",
    "Unwind@0121112d",
    "FUN_00c8c2a0",
    "FUN_013c8050",
    "FUN_00dddc30",
    "FUN_00c61ba0",
    "FUN_00fc1c70",
    "FUN_00f32030",
    "FUN_00a4e390",
    "FUN_00b8e860",
    "FUN_00cb24a6",
    "FUN_00f47ed0",
    "FUN_006275d0",
    "FUN_0113cbb0",
    "Editors::cEditor::OnMouseDown",
    "Unwind@0121124e",
    "Unwind@012107d8",
    "Unwind@0121120e",
    "FUN_00b45170",
    "FUN_0104cf20",
    "FUN_00a510e0",
    "FUN_009ff4b0",
    "FUN_00fef5d0",
    "FUN_0113ba00",
    "FUN_010f3a40",
    "Unwind@01213be0",
    "FUN_00496d30",
    "Unwind@0121a210",
    "FUN_010cbd40",
    "Simulator::cMissionManager::GetMissionByID",
    "FUN_008639f0",
    "FUN_00ef0a70",
    "Unwind@01210724",
    "FUN_00c63330",
    "FUN_01003690",
    "Unwind@012108c5",
    "Unwind@0121a2d0",
    "FUN_00a4c7e0",
    "FUN_004b4930",
    "FUN_009a9920",
    "FUN_011831e0",
    "Unwind@01210960",
    "FUN_00aebe90",
    "Unwind@0120fae9",
    "FUN_00de76b0",
    "FUN_00577c40",
    "FUN_00a4b630",
    "FUN_00e63f90",
    "FUN_00b8dfe0"
  ],
  "classification": "stub",
  "dispatch": null,
  "entry_point": "00c2e4e0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00c2e4e0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x82e4e0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00c2e4e0(void)",
  "size_bytes": 1,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00c2e4e0",
  "vtables": {
    "referenced_by_vtables": [
      "0x013fcc08",
      "0x01418838",
      "0x014191d0",
      "0x01441240",
      "0x01441c18",
      "0x01441fd8",
      "0x01443318",
      "0x01443be8",
      "0x014446f0",
      "0x01444b68",
      "0x01445060",
      "0x014793e0",
      "0x0147f868",
      "0x013fcc48",
      "0x013fdc38",
      "0x013ff648",
      "0x01414fd0",
      "0x01415298",
      "0x01419408",
      "0x01441890"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 100,
  "xrefs": [
    {
      "from": "0
[TRUNCATED]
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
  "vtable:0x013f7028",
  "vtable:0x013f70d4",
  "vtable:0x013f718c",
  "vtable:0x013f72ac",
  "vtable:0x013f74cc",
  "vtable:0x013f756c",
  "vtable:0x013f76c4",
  "vtable:0x013f7820",
  "vtable:0x013f78c0",
  "vtable:0x013f7cc0",
  "vtable:0x013f7de0",
  "vtable:0x013f8100",
  "vtable:0x013f8a38",
  "vtable:0x013f98cc",
  "vtable:0x013f99f0"
]
```

## Conflicts

```json
[]
```
