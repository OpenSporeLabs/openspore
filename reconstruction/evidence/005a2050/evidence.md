# Evidence 0x005a2050

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `18e9ffed267217e927b47e6812b93053a941bcbff18c107cc8d2102e2a108506`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_this_register": "ECX",
  "ordinary_stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "type",
      "type": "uint32_t",
      "width_bytes": 4
    }
  ],
  "ret_form": "RET 4",
  "return_note": "object pointer",
  "return_register": "EAX",
  "stack_cleanup_bytes": 4
}
```

## abi_derived

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "abi": {
    "architecture": "x86-32",
    "calling_convention": "__thiscall",
    "hidden_this": true,
    "hidden_this_register": "ECX",
    "ordinary_stack_argument_slots": [
      "entry_ESP+0x4"
    ],
    "ordinary_stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x4",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
    "stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "stack_cleanup_bytes": 4,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x4"
  },
  "abstained_because": [],
  "cleanup": {
    "bytes": 4,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x4",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "9ffbd85f84c9c6cf70f745f1437e30ec5ef82b3bf0f382939df6d1c185e005e3",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall"
    ],
    "confidence": "SUPPORTED",
    "corroboration": "persisted_agrees"
  },
  "cross_validation": {
    "agreement": true,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 2,
    "persisted": "agrees",
    "persisted_calling_convention": "__thiscall"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0006"
      ],
      "claim": "the callee pops 4 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 4,
        "side": "callee"
      }
    },
    {
      "based_on": [
        "obs-0004"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "INFERRED",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 1,
        "total_bytes": 4
      }
    },
    {
      "based_on": [
        "obs-0005"
      ],
      "claim": "ECX carries the receiver: 0x005a2050 is slot 8 of the vptr-backed vftable at 0x013f69b4, so it is a virtual member of some class and every virtual call that reaches it indexes the vptr through the object address; the body reads its incoming ECX before writing it, and a body that reads a register the vtable dispatch delivered uses the object, so the receiver is in ECX. The callee pops its own stack arguments, which is the COM / __stdcall interface form, and that is the one shape in which a virtual member takes its receiver from the first popped stack word instead -- a body in that form never reads its incoming ECX, which is why this body reading it is what decides the two apart",
      "confidence": "INFERRED",
      "id": "R1-VFT",
      "value": {
        "cleanup_side": "callee",
        "incoming_ecx_reads": 1,
        "membership_count": 2,
        "receiver_provenance": "vftable_slot_dispatch",
        "receiver_register": "ECX",
        "slot_index": 8,
        "table": "0x013f69b4"
      }
    },
    {
      "based_on": [
        "obs-0005",
        "obs-0006"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0006"
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
        "obs-0006"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0006"
      ],
      "claim": "the last value written to EAX classifies as aggregate_unknown",
      "confidence": "INFERRED",
      "id": "RT2",
      "value": {
        "register_class": "aggregate_unknown"
      }
    }
  ],
  "observations": [
    {
      "at": "0x005a2050",
      "count": 1,
      "first_use": 0,
      "first_write_index": 0,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "XOR EAX,EAX",
      "reg": "EAX"
    },
    {
      "at": "0x005a2050",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "XOR EAX,EAX",
      "reg": "EAX",
      "write_kind": "zero"
    },
    {
      "at": "0x005a2052",
      "count": 1,
      "first_use": 1,
      "first_write_index": null,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "CMP dword ptr [ESP + 0x4],0x29da727",
      "reg": "ESP"
    },
    {
      "at": "0x005a2052",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0004",
      "index": 1,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "CMP dword ptr [ESP + 0x4],0x29da727",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x005a205e",
      "count": 1,
      "first_use": 4,
      "first_write_index": null,
      "id": "obs-0005",
      "index": 4,
      "kind": "REG_READ",
      "raw": "AND EAX,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x005a2060",
      "form": "RET 0x4",
      "id": "obs-0006",
      "imm": 4,
      "index": 5,
      "kind": "RET",
      "raw": "RET 0x4"
    }
  ],
  "parse": {
    "declared_count": 6,
    "degraded": false,
    "esp_unresolved": false,
    "flow_complete": true,
    "frame": {
      "and_esp": null,
      "ebp_is_
[TRUNCATED]
```

## callees_dependencies

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## callers_dependencies

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

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
  "count": 6,
  "instructions": [
    {
      "address": "005a2050",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "005a2052",
      "instruction": "CMP dword ptr [ESP + 0x4],0x29da727"
    },
    {
      "address": "005a205a",
      "instruction": "SETNZ AL"
    },
    {
      "address": "005a205d",
      "instruction": "DEC EAX"
    },
    {
      "address": "005a205e",
      "instruction": "AND EAX,ECX"
    },
    {
      "address": "005a2060",
      "instruction": "RET 0x4"
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
  "original_bytes": 7395,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"name\": \"type\",\n        \"type\": \"uint32_t\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"ret_form\": \"RET 4\",\n    \"return_note\": \"object pointer\",\n    \"return_register\": \"EAX\",\n    \"stack_cleanup_bytes\": 4\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueEditorCamera\",\n        \"shared_vtable:vtable:0x013f69b4\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-CAMERA-WAVE8\",\n      \"score\": 28,\n      \"symbol\": \"editor_camera_func54h_005a2320\",\n      \"va\": \"0x005a2320\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueEditorCamera,object pointer\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-CAMERA-WAVE8\",\n      \"score\": 27,\n      \"symbol\": \"editor_camera_on_exit_00c2e640\",\n      \"va\": \"0x00c2e640\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-CAMERA-WAVE7\",\n      \"score\": 8,\n      \"symbol\": \"camera_light_origin_helper_007c4900\",\n      \"va\": \"0x007c4900\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-CAMERA-WAVE7\",\n      \"score\": 8,\n      \"symbol\": \"camera_manager_set_active_007c64c0\",\n      \"va\": \"0x007c64c0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-CAMERA-WAVE7\",\n      \"score\": 8,\n      \"symbol\": \"camera_manager_dispose_007c6e50\",\n      \"va\": \"0x007c6e50\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013f69b4,vtable:0x014105ac\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-sporepedia-nop-slot\",\n      \"score\": 6,\n      \"symbol\": \"sporepedia_nop_slot_FUN_00c2e4e0\",\n      \"va\": \"0x00c2e4e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-CAMERA-WAVE7\",\n      \"score\": 6,\n      \"symbol\": \"cell_get_globals_data_00e4ce20\",\n      \"va\": \"0x00e4ce20\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-CAMERA-WAVE7\",\n      \"score\": 6,\n      \"symbol\": \"cell_move_player_to_mouse_position_00e5b790\",\n      \"va\": \"0x00e5b790\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Static mechanics and x86-32 ABI reviewed from live Ghidra; runtime values, concrete owners, and unresolved ports remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueEditorCamera\",\n  \"cluster\": \"editor-core\",\n  \"confidence\": 0.7,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0100\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"SUPPORTED\",\n  \"globals\": [],\n  \"integration_status\": \"integrated\",\n  \"name\": \"Editors::EditorCamera::func24h\",\n  \"normalized_symbol\": \"editor_camera_func24h_005a2050\",\n  \"observed_mechanics\": [\n    \"{\\\"accepted_result\\\": \\\"this\\\", \\\"accepted_type\\\": \\\"0x029da727\\\", \\\"active_camera_writes\\\": [], \\\"active_viewer_writes\\\": [], \\\"all_other_types\\\": \\\"null\\\", \\\"camera_state_writes\\\": [], \\\"coordinate_or_rotation_arithmetic\\\": \\\"none\\\", \\\"flow\\\": [\\\"Initialize EAX to zero.\\\", \\\"Compare the stack type word with 0x029da727 and SETNZ AL.\\\", \\\"DEC EAX produces zero for equality and all-bits-set otherwise.\\\", \\\"AND EAX,ECX returns this only for inequality and null for equality.\\\", \\\"Return with RET 4.\\\"]}\"\n  ],\n  \"ownership\": {\n    \"claimability\": \"do_not_claim\",\n    \"handoff_packages\": [\n      \"PKG-CAMERA-WAVE8\"\n    ],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": \"PKG-CAMERA-WAVE8\",\n    \"queue_state\": \"queued\"\n  },\n  \"package\": \"PKG-CAMERA-WAVE8\",\n  \"reconstructed\": true,\n  \"review_status\": \"approved_after_parallel_review\",\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"No original runtime indirect invocation was captured for this imported-name entry.\",\n      \"No original runtime indirect invocation was captured for this imported-name entry.; The exact semantic identity behind the imported func24h name remains gated because the machine body is a type-equality pointer result rather than an input reset.\",\n      \"The exact semantic identity behind the imported func24h name remains gated because the machine body is a type-equality pointer result rather than an input reset.\"\n    ],\n    \"validated\": 0\n  },\n  \"runtime_gated\": true,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": \"static_reconstruction_runtime_gated\",\n  \"services\": [],\n  \"source\": {\n    \"decomp\": \".spore-analysis/ghidra-exports/decompiled_sdk/Editors__EditorCamera__func24h.c
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
  "body_end": "005a2062",
  "body_span_bytes": 19,
  "body_start": "005a2050",
  "callees": [],
  "callers": [],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "005a2050",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "Editors::EditorCamera::func24h",
  "namespace": "Editors",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 2,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "EditorCamera *"
    },
    {
      "name": "param_2",
      "ordinal": 1,
      "storage": "Stack[0x8]:1",
      "type": "bool"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "void",
  "return_type_resolved": true,
  "rva": "0x1a2050",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "void Editors::EditorCamera::func24h(EditorCamera * this, bool param_2)",
  "size_bytes": 19,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x005a2050",
  "vtables": {
    "referenced_by_vtables": [
      "0x014105ac",
      "0x013f69b4"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 2,
  "xrefs": [
    {
      "from": "013f69d4"
    },
    {
      "from": "014105cc"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Editors__EditorCamera__func24h.c",
  "file": "src/reconstruction/pkg_camera_wave8/camera_wave8.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Editors__EditorCamera__func24h.c",
    "src/reconstruction/pkg_camera_wave8/camera_wave8.cpp",
    "src/reconstruction/pkg_camera_wave8/camera_wave8_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave8/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-camera-wave8/005a2050.json"
  ]
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
  "gates": [
    "No original runtime indirect invocation was captured for this imported-name entry.",
    "No original runtime indirect invocation was captured for this imported-name entry.; The exact semantic identity behind the imported func24h name remains gated because the machine body is a type-equality pointer result rather than an input reset.",
    "The exact semantic identity behind the imported func24h name remains gated because the machine body is a type-equality pointer result rather than an input reset."
  ],
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
  "runtime_gated": true,
  "runtime_validated": 0,
  "status": "reconstructed"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "OpaqueEditorCamera",
  "object pointer",
  "uint32_t"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x013f69b4",
  "vtable:0x013f69c8",
  "vtable:0x014105ac"
]
```

## Conflicts

```json
[]
```
