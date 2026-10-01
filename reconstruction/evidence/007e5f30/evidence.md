# Evidence 0x007e5f30

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `dd15dacd0f43b574187d15632a1abdf32481742991491678d01b852b7355a789`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "__thiscall",
  "ordinary_stack_arguments": [],
  "receiver_register": "ECX",
  "return_register": "EAX",
  "return_width_bytes": 4,
  "stack_cleanup_bytes": 0,
  "termination": "plain RET"
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
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +16, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "a7a36a59442beb8af319eadd80bdd8b19b0fb9ce13916699866287124246a32d",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall",
      "__fastcall"
    ],
    "confidence": "SUPPORTED",
    "corroboration": "persisted_agrees"
  },
  "cross_validation": {
    "agreement": true,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 1,
    "persisted": "agrees",
    "persisted_calling_convention": "__thiscall"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0009"
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
        "obs-0001",
        "obs-0005"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          364,
          370
        ],
        "register": "ECX",
        "written_through": 1
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0005",
        "obs-0009"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0009"
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
        "obs-0009"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0009"
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
      "at": "0x007e5f30",
      "count": 2,
      "first_use": 0,
      "first_write_index": 8,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "CMP dword ptr [ECX + 0x16c],0x0",
      "reg": "ECX"
    },
    {
      "at": "0x007e5f40",
      "id": "obs-0002",
      "index": 3,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x0067dcc0",
      "target": "0x0067dcc0"
    },
    {
      "at": "0x007e5f45",
      "count": 3,
      "first_use": 4,
      "first_write_index": 9,
      "id": "obs-0003",
      "index": 4,
      "kind": "REG_READ",
      "raw": "MOV EDX,dword ptr [EAX]",
      "reg": "EAX"
    },
    {
      "at": "0x007e5f45",
      "definite": true,
      "id": "obs-0004",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [EAX]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x007e5f4d",
      "definite": true,
      "id": "obs-0005",
      "index": 8,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,EAX",
      "reg": "ECX",
      "write_kind": "reg"
    },
    {
      "at": "0x007e5f4f",
      "count": 1,
      "first_use": 9,
      "first_write_index": 4,
      "id": "obs-0006",
      "index": 9,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [EDX + 0x18]",
      "reg": "EDX"
    },
    {
      "at": "0x007e5f4f",
      "definite": true,
      "id": "obs-0007",
      "index": 9,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [EDX + 0x18]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x007e5f57",
      "base": "EAX",
      "disp": null,
      "id": "obs-0008",
      "index": 11,
      "kind": "CALL_INDIRECT",
      "raw": "CALL EAX",
      "via": "register"
    },
    {
      "at": "0x007e5f59",
      "form": "RET",
      "id": "obs-0009",
      "imm": null,
      "index": 12,
      "kind": "RET",
      "raw": "RET"
    }
  ],
  "parse": {
    "declared_count": 13,
    "degraded": false,
    "esp_unresolved": false,
    "flow_complete": false,
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
    "confidence": "INFERRED",
    "distinct_offsets": 2,
    "max_offset": 370,
    "offsets": [
      364,
      370
    ],
    "present": true,
    "register": "ECX",
    "shape": "R-DIRECT",
    "written_through": 1
  },
  "return": {
    "aggregate_evidence": {
      "bulk_write": false
    },
    "confidence": "INFERRED",
    "register": "EAX",
    "register_class": "aggregate_unknown",
    "type": null,
    "void_possible": false
  },
  "sc
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0067dcc0"
  }
]
```

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
      "address": "007e5f30",
      "instruction": "CMP dword ptr [ECX + 0x16c],0x0"
    },
    {
      "address": "007e5f37",
      "instruction": "MOV byte ptr [ECX + 0x172],0x1"
    },
    {
      "address": "007e5f3e",
      "instruction": "JZ 0x007e5f59"
    },
    {
      "address": "007e5f40",
      "instruction": "CALL 0x0067dcc0"
    },
    {
      "address": "007e5f45",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "007e5f47",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "007e5f49",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "007e5f4b",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "007e5f4d",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "007e5f4f",
      "instruction": "MOV EAX,dword ptr [EDX + 0x18]"
    },
    {
      "address": "007e5f52",
      "instruction": "PUSH 0x462dde3"
    },
    {
      "address": "007e5f57",
      "instruction": "CALL EAX"
    },
    {
      "address": "007e5f59",
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
  "original_bytes": 7250,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"__thiscall\",\n    \"ordinary_stack_arguments\": [],\n    \"receiver_register\": \"ECX\",\n    \"return_register\": \"EAX\",\n    \"return_width_bytes\": 4,\n    \"stack_cleanup_bytes\": 0,\n    \"termination\": \"plain RET\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"shared_types:DATA\",\n        \"shared_vtable:vtable:0x01413acc\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"WAVE6-ENGINE-RUNTIME\",\n      \"score\": 17,\n      \"symbol\": \"app_system_initialize_plugins_007e93d0\",\n      \"va\": \"0x007e93d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_types:DATA\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-LIFECYCLE-WAVE8\",\n      \"score\": 11,\n      \"symbol\": \"app_c_cell_mode_strategy_dispose_00e81f30\",\n      \"va\": \"0x00e81f30\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_types:DATA\"\n      ],\n      \"package\": \"PKG-APP-LIFECYCLE-WAVE7\",\n      \"score\": 9,\n      \"symbol\": \"app_capp_system_hook_windows_007e6080\",\n      \"va\": \"0x007e6080\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_types:DATA\"\n      ],\n      \"package\": \"PKG-APP-LIFECYCLE-WAVE7\",\n      \"score\": 9,\n      \"symbol\": \"app_capp_system_set_effect_collection_ids_007e6100\",\n      \"va\": \"0x007e6100\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_types:DATA\"\n      ],\n      \"package\": \"PKG-APP-LIFECYCLE-WAVE7\",\n      \"score\": 9,\n      \"symbol\": \"app_capp_system_func88h_00a6c940\",\n      \"va\": \"0x00a6c940\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"WAVE6-ENGINE-RUNTIME\",\n      \"score\": 8,\n      \"symbol\": \"app_config_manager_get_0067dcf0\",\n      \"va\": \"0x0067dcf0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DATA\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-08-CELL-MODE\",\n      \"score\": 5,\n      \"symbol\": \"cell_mode_on_exit_00e7fc00\",\n      \"va\": \"0x00e7fc00\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x00000018\"\n      ],\n      \"package\": \"PKG-11-A3-ACHIEVEMENT-MISSION-WAVE2\",\n      \"score\": 4,\n      \"symbol\": \"mission_manager_record_init_00fec3c0\",\n      \"va\": \"0x00fec3c0\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"The gate, state publication order, zero-gate EAX preservation, service lookup, slot, and four forwarded words are exact; lifecycle meanings and the concrete slot target remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"pass_after_repair\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueWave6AppSystem\",\n  \"cluster\": \"app-lifecycle\",\n  \"confidence\": 0.9,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0067dcc0\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x007e5f40\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067dcc0\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 1,\n    \"manifest_callees\": [\n      \"0x0067dcc0\",\n      \"service vtable +0x18\"\n    ],\n    \"manifest_callers\": [\n      \"data_xref_01413b48\"\n    ],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0249\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"OBSERVED\",\n  \"globals\": [],\n  \"integration_status\": \"integrated\",\n  \"name\": \"App::cAppSystem::Unpause\",\n  \"normalized_symbol\": \"app_system_service_gate_dispatch_007e5f30\",\n  \"observed_mechanics\": [\n    \"read receiver+0x16c\",\n    \"store byte 1 at receiver+0x172 before branching\",\n    \"zero gate returns incoming EAX\",\n    \"nonzero gate calls 0x0067dcc0 and unchecked vtable+0x18\",\n    \"forward 0x0462dde3 and three zero words\",\n    \"return callback EAX unchanged\"\n  ],\n  \"ownership\": {\n    \"claimability\": \"do_not_claim\",\n    \"handoff_packages\": [\n      \"WAVE6-ENGINE-RUNTIME\"\n    ],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": \"WAVE6-ENGINE-RUNTIME\",\n    \"queue_state\": \"queued\"\n  },\n  \"package\": \"WAVE6-ENGINE-RUNTIME\",\n  \"reconstructed\": true,\n  \"review_status\": \"approved\",\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"gate-app-system-service-gate-and-vtable\"\n    ],\n    \"validated\": 0\n  },\n  \"runtime_gated\": true,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": \"static_service_gate_and_vtable_dispatch_runtime_state_unknown\",\n  \"services\": [],\n  \"source\": {\n    \"decomp\": \".spore-analysis/ghidra-exports/decompiled_sdk/App__cAppSystem__Unpause.c\",\n    \"file\": \"src/reconstruction/wave6_engine_runtime/engine_runtime.cpp\",\n    \"files\": [\n      \".spore-analysis/ghidra-exports/decompiled_sdk/App__cAppSystem__Unpause.c\",\n      \"reconstruction/staging/wave6-engine-runtime/engine_runtime.cpp\",\n      \"reconstruction/staging/wave6-engine-runtime/engine_runtime.hpp\",\n      \"reconstruction/staging/wave6-engine-runtime/engine_runtime_model_test.cpp\",\n      \"src/reconstruction/wave6_engine_runtime/engine_runtime.cpp\"\n    ],\n    \"handoffs\": [\n      \"reconstruction/integrated/batch-2026-09-25-wave6/handoff.json\"\n    ],\n    \"metadata\": [\n  
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
  "body_end": "007e5f59",
  "body_span_bytes": 42,
  "body_start": "007e5f30",
  "callees": [
    "App::IAppSystem::Get"
  ],
  "callers": [],
  "classification": "wrapper",
  "dispatch": null,
  "entry_point": "007e5f30",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "App::cAppSystem::Unpause",
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
  "rva": "0x3e5f30",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "int App::cAppSystem::Unpause(cAppSystem * this)",
  "size_bytes": 42,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x007e5f30",
  "vtables": {
    "referenced_by_vtables": [
      "0x01413acc",
      "0x01413b48"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "01413b48"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__cAppSystem__Unpause.c",
  "file": "src/reconstruction/wave6_engine_runtime/engine_runtime.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__cAppSystem__Unpause.c",
    "reconstruction/staging/wave6-engine-runtime/engine_runtime.cpp",
    "reconstruction/staging/wave6-engine-runtime/engine_runtime.hpp",
    "reconstruction/staging/wave6-engine-runtime/engine_runtime_model_test.cpp",
    "src/reconstruction/wave6_engine_runtime/engine_runtime.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/wave6-engine-runtime/007e5f30.json"
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
    "gate-app-system-service-gate-and-vtable"
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
  "OpaqueWave6AppService",
  "OpaqueWave6AppSystem",
  "OpaqueWave6AppSystem*",
  "Wave6AppLifecyclePorts"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x00000018",
  "vtable:0x01413acc",
  "vtable:0x01413b48"
]
```

## Conflicts

```json
[]
```
