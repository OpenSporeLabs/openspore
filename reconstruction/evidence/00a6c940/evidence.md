# Evidence 0x00a6c940

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `181c6c429237a3084dfd8c37ca6c6b57743f7911ea84ff6cb7252040d0babb90`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "thiscall with two stack words",
  "hidden_receiver": "ECX OpaqueAppSystem*",
  "ordinary_stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "index",
      "position": 1,
      "type": "int32"
    },
    {
      "entry_offset": "ESP+0x08",
      "name": "enabled",
      "position": 2,
      "type": "uint8"
    }
  ],
  "ret_form": "RET 0x8 on every path",
  "return_register": "EAX",
  "return_width_bytes": 4,
  "stack_cleanup_bytes": 8
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
      "entry_ESP+0x4",
      "entry_ESP+0x8"
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
      },
      {
        "entry_offset": "entry_ESP+0x8",
        "observed": true,
        "ordinal": 2,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x8",
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
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
      },
      {
        "entry_offset": "entry_ESP+0x8",
        "observed": true,
        "ordinal": 2,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      }
    ],
    "stack_cleanup_bytes": 8,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x8"
  },
  "abstained_because": [],
  "cleanup": {
    "bytes": 8,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x8",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "13931d07cbe6594cdb67b5ceefb971f235aa0661551ff55bda61824a0bb71928",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall"
    ],
    "confidence": "INFERRED",
    "corroboration": "not_available"
  },
  "cross_validation": {
    "agreement": false,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 1,
    "persisted": "no_information",
    "persisted_calling_convention": "thiscall with two stack words"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0010",
        "obs-0011"
      ],
      "claim": "the callee pops 8 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 8,
        "side": "callee"
      }
    },
    {
      "based_on": [
        "obs-0004",
        "obs-0008"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "INFERRED",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 2,
        "total_bytes": 8
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0002",
        "obs-0003",
        "obs-0004",
        "obs-0005"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          104
        ],
        "register": "ECX",
        "written_through": 2
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0002",
        "obs-0003",
        "obs-0004",
        "obs-0005",
        "obs-0010",
        "obs-0011"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0010",
        "obs-0011"
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
        "obs-0010",
        "obs-0011"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0010",
        "obs-0011"
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
      "at": "0x00a6c940",
      "count": 2,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EDX,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00a6c940",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,ECX",
      "reg": "EDX",
      "write_kind": "reg"
    },
    {
      "at": "0x00a6c942",
      "count": 2,
      "first_use": 1,
      "first_write_index": null,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ECX,dword ptr [ESP + 0x4]",
      "reg": "ESP"
    },
    {
      "at": "0x00a6c942",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0004",
      "index": 1,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV ECX,dword ptr [ESP + 0x4]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00a6c942",
      "definite": true,
      "id": "obs-0005",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [ESP + 0x4]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00a6c94b",
      "definite": true,
      "id": "obs-0006",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,0x1",
      "reg": "EAX",
      "write_kind": "imm"
    },
    {
      "at": "0x00a6c950",
      "count": 3,
      "first_use": 5,
      "first_write_index": 4,
      "id": "obs-0007",
      "index": 
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
  "count": 13,
  "instructions": [
    {
      "address": "00a6c940",
      "instruction": "MOV EDX,ECX"
    },
    {
      "address": "00a6c942",
      "instruction": "MOV ECX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "00a6c946",
      "instruction": "CMP ECX,0x20"
    },
    {
      "address": "00a6c949",
      "instruction": "JGE 0x00a6c964"
    },
    {
      "address": "00a6c94b",
      "instruction": "MOV EAX,0x1"
    },
    {
      "address": "00a6c950",
      "instruction": "SHL EAX,CL"
    },
    {
      "address": "00a6c952",
      "instruction": "CMP byte ptr [ESP + 0x8],0x0"
    },
    {
      "address": "00a6c957",
      "instruction": "JZ 0x00a6c95f"
    },
    {
      "address": "00a6c959",
      "instruction": "OR dword ptr [EDX + 0x68],EAX"
    },
    {
      "address": "00a6c95c",
      "instruction": "RET 0x8"
    },
    {
      "address": "00a6c95f",
      "instruction": "NOT EAX"
    },
    {
      "address": "00a6c961",
      "instruction": "AND dword ptr [EDX + 0x68],EAX"
    },
    {
      "address": "00a6c964",
      "instruction": "RET 0x8"
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
  "original_bytes": 7428,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"thiscall with two stack words\",\n    \"hidden_receiver\": \"ECX OpaqueAppSystem*\",\n    \"ordinary_stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"name\": \"index\",\n        \"position\": 1,\n        \"type\": \"int32\"\n      },\n      {\n        \"entry_offset\": \"ESP+0x08\",\n        \"name\": \"enabled\",\n        \"position\": 2,\n        \"type\": \"uint8\"\n      }\n    ],\n    \"ret_form\": \"RET 0x8 on every path\",\n    \"return_register\": \"EAX\",\n    \"return_width_bytes\": 4,\n    \"stack_cleanup_bytes\": 8\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:DATA,OpaqueAppSystem\"\n      ],\n      \"package\": \"PKG-APP-LIFECYCLE-WAVE7\",\n      \"score\": 25,\n      \"symbol\": \"app_capp_system_hook_windows_007e6080\",\n      \"va\": \"0x007e6080\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:DATA,OpaqueAppSystem\"\n      ],\n      \"package\": \"PKG-APP-LIFECYCLE-WAVE7\",\n      \"score\": 25,\n      \"symbol\": \"app_capp_system_set_effect_collection_ids_007e6100\",\n      \"va\": \"0x007e6100\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_types:DATA\"\n      ],\n      \"package\": \"WAVE6-ENGINE-RUNTIME\",\n      \"score\": 9,\n      \"symbol\": \"app_system_service_gate_dispatch_007e5f30\",\n      \"va\": \"0x007e5f30\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_types:DATA\"\n      ],\n      \"package\": \"PKG-APP-LIFECYCLE-WAVE8\",\n      \"score\": 9,\n      \"symbol\": \"app_c_cell_mode_strategy_dispose_00e81f30\",\n      \"va\": \"0x00e81f30\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DATA,uint8\"\n      ],\n      \"package\": \"PKG-18-UI-SCRIPTING\",\n      \"score\": 6,\n      \"symbol\": \"FUN_005c0380\",\n      \"va\": \"0x005c0380\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DATA,int32\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE8\",\n      \"score\": 6,\n      \"symbol\": \"cell_mode_strategy_on_mouse_up_00e5c0f0\",\n      \"va\": \"0x00e5c0f0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DATA,int32\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE8\",\n      \"score\": 6,\n      \"symbol\": \"cell_mode_strategy_on_mouse_down_00e6c860\",\n      \"va\": \"0x00e6c860\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DATA,int32\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE8\",\n      \"score\": 6,\n      \"symbol\": \"cell_mode_strategy_on_mouse_wheel_00e7d660\",\n      \"va\": \"0x00e7d660\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Static mechanics and x86-32 ABI reviewed from live Ghidra; runtime values, concrete owners, and unresolved ports remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [\n    \"Original-process index, flag, receiver, and field_68 state remain runtime-gated.\"\n  ],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueAppSystem\",\n  \"cluster\": \"app-lifecycle\",\n  \"confidence\": 0.7,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0333\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"SUPPORTED\",\n  \"globals\": [],\n  \"integration_status\": \"integrated\",\n  \"name\": \"App::cAppSystem::func88h\",\n  \"normalized_symbol\": \"app_capp_system_func88h_00a6c940\",\n  \"observed_mechanics\": [\n    \"{\\\"enable_nonzero\\\": \\\"OR the mask into receiver+0x68 and return the mask.\\\", \\\"enable_zero\\\": \\\"Negate the mask, AND it into receiver+0x68, and return the negated mask.\\\", \\\"invalid_index\\\": \\\"Skip the field update and RET 0x8 with the incoming EAX value unchanged.\\\", \\\"mask\\\": \\\"EAX receives 1 shifted by CL; x86 masks the shift count to five bits.\\\", \\\"null_behavior\\\": \\\"No receiver null guard exists; a null receiver faults on a valid-index field access.\\\", \\\"validity_test\\\": \\\"Signed CMP index,0x20 followed by JGE; values less than 32 continue, including negative signed indices.\\\"}\"\n  ],\n  \"ownership\": {\n    \"claimability\": \"do_not_claim\",\n    \"handoff_packages\": [\n      \"PKG-APP-LIFECYCLE-WAVE7\"\n    ],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": \"PKG-APP-LIFECYCLE-WAVE7\",\n    \"queue_state\": \"queued\"\n  },\n  \"package\": \"PKG-APP-LIFECYCLE-WAVE7\",\n  \"reconstructed\": true,\n  \"review_status\": \"approved_after_parallel_review\",\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"Observe the actual table caller, index producer, enabled flag producer, receiver validity, and field_68 lifetime before promoting bitfield ownership semantics.\"\n    ],\n    \"validated\": 0\n  },\n  \"runtime_gated\": true,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": \"static_reconstruction_runtime_gated\",\n  \"services\": [],\n  \"source\": {\n    \"decomp\": \".spore-analysis/ghidra-exports/decompiled_sdk/App__cAppSystem__func88h.c\",\n    \"file\": \"src/reconstruction/pkg_app_lifecycle_wave7/app_lifecycle_wave7.cpp\",\n    \"files\": [\n      \".spore-analysis/ghidra-exports/decom
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
  "body_end": "00a6c966",
  "body_span_bytes": 39,
  "body_start": "00a6c940",
  "callees": [],
  "callers": [],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "00a6c940",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "App::cAppSystem::func88h",
  "namespace": "App",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 1,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "cAppSystem *"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "int",
  "return_type_resolved": true,
  "rva": "0x66c940",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "int App::cAppSystem::func88h(cAppSystem * this)",
  "size_bytes": 39,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00a6c940",
  "vtables": {
    "referenced_by_vtables": [
      "0x01455b7c",
      "0x01455c18"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "01455c18"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__cAppSystem__func88h.c",
  "file": "src/reconstruction/pkg_app_lifecycle_wave7/app_lifecycle_wave7.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__cAppSystem__func88h.c",
    "src/reconstruction/pkg_app_lifecycle_wave7/app_lifecycle_wave7.cpp",
    "src/reconstruction/pkg_app_lifecycle_wave7/app_lifecycle_wave7.hpp",
    "src/reconstruction/pkg_app_lifecycle_wave7/app_lifecycle_wave7_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave7/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-app-lifecycle-wave7/00a6c940.json"
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
    "Observe the actual table caller, index producer, enabled flag producer, receiver validity, and field_68 lifetime before promoting bitfield ownership semantics."
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
  "DATA",
  "OpaqueAppSystem",
  "int32",
  "std::uint32_t in EAX",
  "uint8"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x01455b7c",
  "vtable:0x01455c18"
]
```

## Conflicts

```json
[]
```
