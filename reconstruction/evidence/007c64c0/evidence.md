# Evidence 0x007c64c0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `54aa20de44e99399b936ac2cfbf8269ebc189d809088b2a246c6ecd34a2b1d0c`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": 1,
  "ordinary_stack_arguments": [
    "dword key at [ESP+4] after entry"
  ],
  "ret_form": "RET 0x4",
  "return_note": "machine value",
  "return_type": "OpaqueCamera*",
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
    "ordinary_stack_argument_slots": [
      "entry_ESP+0x4"
    ],
    "ordinary_stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x4",
        "observed": false,
        "ordinal": 1,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "source": "ret_immediate",
        "written": false
      }
    ],
    "receiver": false,
    "ret_form": "RET 0x4",
    "return_register": "EAX",
    "return_semantics": "pointer_like_in_EAX",
    "stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x4",
        "observed": false,
        "ordinal": 1,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "source": "ret_immediate",
        "written": false
      }
    ],
    "stack_cleanup_bytes": 4,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x4"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -8, so the listing is not one path",
    "ecx_and_edx_indistinguishable: EDX is dereferenced before any write to it (C8-E) and the callee pops its own stack arguments (C6B); a fastcall callee does not pop and a popping thiscall has no incoming register argument"
  ],
  "cleanup": {
    "bytes": 4,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x4",
    "side": "callee"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "06f2cc82f541d6b0387b5f346e5f07cfe7e4fea21f311c365b0d7023c5277486",
  "conventions": {
    "ambiguities": [
      "ecx_and_edx_indistinguishable"
    ],
    "calling_convention": null,
    "candidate_conventions": [
      "__thiscall",
      "__fastcall"
    ],
    "confidence": "UNKNOWN",
    "corroboration": "not_available"
  },
  "cross_validation": {
    "agreement": false,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 2,
    "persisted": "no_information",
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
        "obs-0006",
        "obs-0008"
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
        "obs-0006",
        "obs-0008"
      ],
      "claim": "argument slots derived from the terminal immediate alone; no argument read was observed, so this is the popped area and not a parameter count",
      "confidence": "APPROXIMATION",
      "id": "A1-IMM",
      "value": {
        "derived_slots": 1,
        "total_bytes": 4
      }
    },
    {
      "based_on": [
        "obs-0008"
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
        "obs-0001",
        "obs-0002",
        "obs-0003"
      ],
      "claim": "EDX is a memory base before any definite write to it",
      "confidence": "OBSERVED",
      "id": "C8-E",
      "value": {
        "register": "EDX"
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0008"
      ],
      "claim": "the reading that this is a __thiscall member which pops its own stack arguments is present and undecided: it excludes __fastcall, while C8-E asserts an incoming EDX that only __fastcall guarantees",
      "confidence": "UNKNOWN",
      "id": "C6B"
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0008"
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
        "obs-0006",
        "obs-0008"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0008"
      ],
      "claim": "the last value written to EAX classifies as pointer_like",
      "confidence": "INFERRED",
      "id": "RT2",
      "value": {
        "register_class": "pointer_like"
      }
    }
  ],
  "observations": [
    {
      "at": "0x007c64c0",
      "count": 1,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [EDX + 0x4]",
      "reg": "EDX"
    },
    {
      "at": "0x007c64c0",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [EDX + 0x4]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x007c64c3",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "ADD EDX,0x4",
      "reg": "EDX",
      "write_kind": "arith"
    },
    {
      "at": "0x007c64ce",
      "count": 2,
      "first_use": 6,
      "first_write_index": 0,
      "id": "obs-0004",
      "index": 6,
      "kind": "REG_READ",
      "raw": "XOR EAX,EAX",
      "reg": "EAX"
    },
    {
      "at": "0x007c64d0",
      "id": "obs-0005",
      "index": 7,
      "kind": "REG_RESTORE",
      "raw": "POP ESI",
      "reg": "ESI"
    },
    {
      "at": "0x007c64d1",
      "form": "RET 0x4",
      "id": "obs-0006",
      "imm": 4,
      "index": 8,
      "kind": "RET",
      "raw": "RET 0x4"
    },
    {
      "at": "0x007c64d6",
      "id": "obs-0007",
      "index": 10,
      "kind": "REG_RESTORE",
      "raw": "POP ESI",
      "reg": "ESI"
    },
    {
      "at": "0x007c64d7",
      "form": "RET 0x4",
      "id": "obs-0008",
      "imm": 4,
      "index": 11,
      "kind": "RET",
      "raw": "RET 0x4"
    }
  ],
 
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

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "anchors": [
      "0x007d85b0",
      "0x007d8d40",
      "0x01412598",
      "0x01412598",
      "0x007d8c80",
      "0x007d8d40",
      "0x007d85b0",
      "0x007d8d40",
      "0x01412598",
      "0x007d8c80",
      "0x007c61a0",
      "0x007c61a0",
      "0x007c64c0",
      "0x007c64c0",
      "0x007c6750",
      "0x007c6750"
    ],
    "conflict_id": "app_mode_setter_boundary",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x007c61a0",
      "0x007c64c0",
      "0x007c6750",
      "0x007c6eb0",
      "0x007c61a0",
      "0x007c61a0",
      "0x007c61a0",
      "0x007c61a0",
      "0x007c64c0",
      "0x007c64c0",
      "0x007c64c0",
      "0x007c6750",
      "0x007c6750",
      "0x007c6750",
      "0x007c6eb0",
      "0x007c6eb0"
    ],
    "conflict_id": "camera_address_conflicts",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  }
]
```

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
  "count": 12,
  "instructions": [
    {
      "address": "007c64c0",
      "instruction": "MOV EAX,dword ptr [EDX + 0x4]"
    },
    {
      "address": "007c64c3",
      "instruction": "ADD EDX,0x4"
    },
    {
      "address": "007c64c6",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "007c64c8",
      "instruction": "JZ 0x007c64c0"
    },
    {
      "address": "007c64ca",
      "instruction": "CMP EAX,ECX"
    },
    {
      "address": "007c64cc",
      "instruction": "JNZ 0x007c64b0"
    },
    {
      "address": "007c64ce",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "007c64d0",
      "instruction": "POP ESI"
    },
    {
      "address": "007c64d1",
      "instruction": "RET 0x4"
    },
    {
      "address": "007c64d4",
      "instruction": "MOV EAX,dword ptr [EAX]"
    },
    {
      "address": "007c64d6",
      "instruction": "POP ESI"
    },
    {
      "address": "007c64d7",
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
  "original_bytes": 6031,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": 1,\n    \"ordinary_stack_arguments\": [\n      \"dword key at [ESP+4] after entry\"\n    ],\n    \"ret_form\": \"RET 0x4\",\n    \"return_note\": \"machine value\",\n    \"return_type\": \"OpaqueCamera*\",\n    \"stack_cleanup_bytes\": 4\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueCameraState\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-CAMERA-WAVE7\",\n      \"score\": 24,\n      \"symbol\": \"camera_light_origin_helper_007c4900\",\n      \"va\": \"0x007c4900\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueCameraState\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-CAMERA-WAVE7\",\n      \"score\": 24,\n      \"symbol\": \"camera_manager_dispose_007c6e50\",\n      \"va\": \"0x007c6e50\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueCameraState\"\n      ],\n      \"package\": \"PKG-CAMERA-WAVE7\",\n      \"score\": 22,\n      \"symbol\": \"cell_get_globals_data_00e4ce20\",\n      \"va\": \"0x00e4ce20\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueCameraState\"\n      ],\n      \"package\": \"PKG-CAMERA-WAVE7\",\n      \"score\": 22,\n      \"symbol\": \"cell_move_player_to_mouse_position_00e5b790\",\n      \"va\": \"0x00e5b790\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-CAMERA-WAVE8\",\n      \"score\": 8,\n      \"symbol\": \"editor_camera_func24h_005a2050\",\n      \"va\": \"0x005a2050\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-CAMERA-WAVE8\",\n      \"score\": 8,\n      \"symbol\": \"editor_camera_func54h_005a2320\",\n      \"va\": \"0x005a2320\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-CAMERA-WAVE8\",\n      \"score\": 8,\n      \"symbol\": \"editor_camera_on_exit_00c2e640\",\n      \"va\": \"0x00c2e640\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Static mechanics and x86-32 ABI reviewed from live Ghidra; runtime values, concrete owners, and unresolved ports remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueCameraState\",\n  \"cluster\": null,\n  \"confidence\": 0.7,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0238\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"SUPPORTED\",\n  \"globals\": [],\n  \"integration_status\": \"integrated\",\n  \"name\": \"camera_manager_set_active_007c64c0\",\n  \"normalized_symbol\": \"camera_manager_set_active_007c64c0\",\n  \"observed_mechanics\": [\n    \"{\\\"active_index_guard\\\": \\\"The active_index_0a8 field is not read or written by this observed body; only the sentinel and key guards control the return.\\\", \\\"node_offsets\\\": {\\\"key\\\": \\\"+0x04\\\", \\\"next\\\": \\\"+0x08\\\", \\\"value\\\": \\\"+0x00\\\"}, \\\"receiver_offsets\\\": {\\\"active_index\\\": \\\"+0xa8\\\", \\\"message_bucket_count\\\": \\\"+0x68\\\", \\\"message_buckets\\\": \\\"+0x64\\\", \\\"message_registry\\\": \\\"+0x60\\\"}, \\\"search_order\\\": [\\\"scan forward from bucket zero until a non-null bucket entry\\\", \\\"compare the first entry with the bucket-count sentinel\\\", \\\"for each node compare node key with the requested dword\\\", \\\"on a miss follow node next, then advance ...\"\n  ],\n  \"ownership\": {\n    \"claimability\": \"do_not_claim\",\n    \"handoff_packages\": [\n      \"PKG-CAMERA-WAVE7\"\n    ],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": \"PKG-CAMERA-WAVE7\",\n    \"queue_state\": null\n  },\n  \"package\": \"PKG-CAMERA-WAVE7\",\n  \"reconstructed\": true,\n  \"review_status\": \"approved_after_parallel_review\",\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"Wine/original Cell or application camera-manager trace is not available; no runtime promotion is claimed.\",\n      \"runtime observation required\"\n    ],\n    \"validated\": 0\n  },\n  \"runtime_gated\": true,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": \"static_reconstruction_runtime_gated\",\n  \"services\": [],\n  \"source\": {\n    \"decomp\": null,\n    \"file\": \"src/reconstruction/pkg_camera_wave7/camera_wave7.cpp\",\n    \"files\": [\n      \"src/reconstruction/pkg_camera_wave7\",\n      \"src/reconstruction/pkg_camera_wave7/camera_wave7.cpp\",\n      \"src/reconstruction/pkg_camera_wave7/camera_wave7_model_test.cpp\"\
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
  "body_end": "007c64d9",
  "body_span_bytes": 42,
  "body_start": "007c64b0",
  "callees": [],
  "callers": [],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "007c64c0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_res0",
      "storage": "Stack[0x0]:1",
      "type": "undefined"
    }
  ],
  "locals_count": 1,
  "mode": "live",
  "name": "App::cCameraManager::SetActiveCamera",
  "namespace": "App",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 2,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "cCameraManager *"
    },
    {
      "name": "nIndex",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "int"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "bool",
  "return_type_resolved": true,
  "rva": "0x3c64c0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "bool App::cCameraManager::SetActiveCamera(cCameraManager * this, int nIndex)",
  "size_bytes": 42,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x007c64c0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "007c64c8"
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
  "file": "src/reconstruction/pkg_camera_wave7/camera_wave7.cpp",
  "files": [
    "src/reconstruction/pkg_camera_wave7/camera_wave7.cpp",
    "src/reconstruction/pkg_camera_wave7/camera_wave7_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave7/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-camera-wave7/007c64c0.json"
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
    "Wine/original Cell or application camera-manager trace is not available; no runtime promotion is claimed.",
    "runtime observation required"
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
  "OpaqueCamera* machine value",
  "OpaqueCameraState"
]
```

## vtables

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## Conflicts

```json
[
  {
    "anchors": [
      "0x007d85b0",
      "0x007d8d40",
      "0x01412598",
      "0x01412598",
      "0x007d8c80",
      "0x007d8d40",
      "0x007d85b0",
      "0x007d8d40",
      "0x01412598",
      "0x007d8c80",
      "0x007c61a0",
      "0x007c61a0",
      "0x007c64c0",
      "0x007c64c0",
      "0x007c6750",
      "0x007c6750"
    ],
    "conflict_id": "app_mode_setter_boundary",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x007c61a0",
      "0x007c64c0",
      "0x007c6750",
      "0x007c6eb0",
      "0x007c61a0",
      "0x007c61a0",
      "0x007c61a0",
      "0x007c61a0",
      "0x007c64c0",
      "0x007c64c0",
      "0x007c64c0",
      "0x007c6750",
      "0x007c6750",
      "0x007c6750",
      "0x007c6eb0",
      "0x007c6eb0"
    ],
    "conflict_id": "camera_address_conflicts",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  }
]
```
