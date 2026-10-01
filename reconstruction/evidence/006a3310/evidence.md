# Evidence 0x006a3310

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `ef6106f7ed8ee4eb2adc6207bfd1abc812a1f999da2c35d208f58aaf526b7b09`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86:LE:32",
  "calling_convention": "thiscall",
  "hidden_receiver": "ECX = OpaquePropManager*",
  "ordinary_stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "instance_id",
      "position": 1,
      "type": "TargetWord",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x08",
      "name": "destination",
      "position": 2,
      "type": "OpaquePropertyListRef*",
      "width_bytes": 4
    }
  ],
  "return_note": "virtual dispatch result",
  "return_register": "AL",
  "return_width_bytes": 1,
  "stack_cleanup_bytes": 8,
  "termination": "RET 0x8"
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
          4
        ],
        "written": false
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x8",
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
      },
      {
        "entry_offset": "entry_ESP+0x8",
        "observed": true,
        "ordinal": 2,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "stack_cleanup_bytes": 8,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x8"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +12, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 8,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x8",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "622c6bb608139b86f8b0c0f9ebbc902e39af9a548a074dc6933b7f62a3a9e7cd",
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
    "ghidra_parameter_count": 3,
    "persisted": "agrees",
    "persisted_calling_convention": "thiscall"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0010"
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
        "obs-0002",
        "obs-0008"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 2,
        "total_bytes": 8
      }
    },
    {
      "based_on": [
        "obs-0004",
        "obs-0005"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          0,
          44
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0004",
        "obs-0005",
        "obs-0010"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0010"
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
        "obs-0010"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0010"
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
      "at": "0x006a3310",
      "count": 2,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EDX,dword ptr [ESP + 0x8]",
      "reg": "ESP"
    },
    {
      "at": "0x006a3310",
      "base": "ESP",
      "disp": 8,
      "id": "obs-0002",
      "index": 0,
      "key": 8,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EDX,dword ptr [ESP + 0x8]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x006a3310",
      "definite": true,
      "id": "obs-0003",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [ESP + 0x8]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x006a3314",
      "count": 1,
      "first_use": 1,
      "first_write_index": null,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ECX]",
      "reg": "ECX"
    },
    {
      "at": "0x006a3314",
      "definite": true,
      "id": "obs-0005",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ECX]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x006a3316",
      "count": 2,
      "first_use": 2,
      "first_write_index": 1,
      "id": "obs-0006",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [EAX + 0x2c]",
      "reg": "EAX"
    },
    {
      "at": "0x006a3319",
      "count": 2,
      "first_use": 3,
      "first_write_index": 0,
      "id": "obs-0007",
      "index": 3,
      "kind": "REG_READ",
      "raw": "PUS
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
  "count": 9,
  "instructions": [
    {
      "address": "006a3310",
      "instruction": "MOV EDX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "006a3314",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "006a3316",
      "instruction": "MOV EAX,dword ptr [EAX + 0x2c]"
    },
    {
      "address": "006a3319",
      "instruction": "PUSH EDX"
    },
    {
      "address": "006a331a",
      "instruction": "MOV EDX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "006a331e",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "006a3320",
      "instruction": "PUSH EDX"
    },
    {
      "address": "006a3321",
      "instruction": "CALL EAX"
    },
    {
      "address": "006a3323",
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
  "original_bytes": 7923,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86:LE:32\",\n    \"calling_convention\": \"thiscall\",\n    \"hidden_receiver\": \"ECX = OpaquePropManager*\",\n    \"ordinary_stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"name\": \"instance_id\",\n        \"position\": 1,\n        \"type\": \"TargetWord\",\n        \"width_bytes\": 4\n      },\n      {\n        \"entry_offset\": \"ESP+0x08\",\n        \"name\": \"destination\",\n        \"position\": 2,\n        \"type\": \"OpaquePropertyListRef*\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"return_note\": \"virtual dispatch result\",\n    \"return_register\": \"AL\",\n    \"return_width_bytes\": 1,\n    \"stack_cleanup_bytes\": 8,\n    \"termination\": \"RET 0x8\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueRuntimeService,TargetWord\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-RUNTIME-SERVICES-WAVE7\",\n      \"score\": 27,\n      \"symbol\": \"editor_anim_event_message_post_0059d840\",\n      \"va\": \"0x0059d840\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueRuntimeService,TargetWord\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-RUNTIME-SERVICES-WAVE7\",\n      \"score\": 27,\n      \"symbol\": \"editor_anim_event_message_send_0059d8b0\",\n      \"va\": \"0x0059d8b0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueRuntimeService\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-RUNTIME-SERVICES-WAVE7\",\n      \"score\": 24,\n      \"symbol\": \"app_prop_manager_get_supported_types_006a3400\",\n      \"va\": \"0x006a3400\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueRuntimeService\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-RUNTIME-SERVICES-WAVE7\",\n      \"score\": 24,\n      \"symbol\": \"app_canvas_get_message_server_00c871d0\",\n      \"va\": \"0x00c871d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueRuntimeService\"\n      ],\n      \"package\": \"PKG-RUNTIME-SERVICES-WAVE7\",\n      \"score\": 22,\n      \"symbol\": \"app_cheat_manager_get_0067dde0\",\n      \"va\": \"0x0067dde0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueRuntimeService\"\n      ],\n      \"package\": \"PKG-RUNTIME-SERVICES-WAVE7\",\n      \"score\": 22,\n      \"symbol\": \"app_id_generator_get_007c79e0\",\n      \"va\": \"0x007c79e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueRuntimeService\"\n      ],\n      \"package\": \"PKG-RUNTIME-SERVICES-WAVE8\",\n      \"score\": 14,\n      \"symbol\": \"ui_layer_manager_get_0067ca90\",\n      \"va\": \"0x0067ca90\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueRuntimeService\"\n      ],\n      \"package\": \"PKG-RUNTIME-SERVICES-WAVE8\",\n      \"score\": 14,\n      \"symbol\": \"anim_manager_get_0067cae0\",\n      \"va\": \"0x0067cae0\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Static mechanics and x86-32 ABI reviewed from live Ghidra; runtime values, concrete owners, and unresolved ports remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueRuntimeService\",\n  \"cluster\": \"app-lifecycle\",\n  \"confidence\": 0.7,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0223\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"SUPPORTED\",\n  \"globals\": [],\n  \"integration_status\": \"integrated\",\n  \"name\": \"App::cPropManager::GetGlobalPropertyList\",\n  \"normalized_symbol\": \"app_prop_manager_get_global_property_list_006a3310\",\n  \"observed_mechanics\": [\n    \"{\\\"body_end_inclusive\\\": \\\"0x006a3323\\\", \\\"entry\\\": \\\"0x006a3310\\\", \\\"instruction_count\\\": 9, \\\"mechanics\\\": [\\\"load the receiver vtable from ECX+0x00\\\", \\\"load the indirect function at vtable+0x2c\\\", \\\"push destination, then push zero, then push instance_id before the call\\\", \\\"pass the receiver in ECX and return the virtual result unchanged\\\"], \\\"raw_bytes_hex\\\": \\\"8b5424088b018b402c528b5424086a0052ffd0c208\\\", \\\"virtual_arguments_as_received\\\": [\\\"instance_id\\\", \\\"0\\\", \\\"destination\\\"], \\\"virtual_slot\\\": \\\"0x2c\\\"}\"\n  ],\n  \"ownership\": {\n    \"claimability\": \"do_not_claim\",\n    \"handoff_packages\": [\n      \"PKG-RUNTIME-SERVICES-WAVE7\"\n    ],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": \"PKG-RUNTIME-SERVICES-WAVE7\",\n    \"queue_state\": \"queued\"\n  },\n  \"package\": \"PKG-RUNTIME-SERVICES-WAVE7\",\n  \"reconstructed\": true,\n  \"review_status\": \"approved_after_parallel_review\",\n  \"runtime\": {\n    \"blocking_reason\":
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
  "body_end": "006a3325",
  "body_span_bytes": 22,
  "body_start": "006a3310",
  "callees": [],
  "callers": [],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "006a3310",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "App::cPropManager::GetGlobalPropertyList",
  "namespace": "App",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 3,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "cPropManager *"
    },
    {
      "name": "instanceID",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "uint32_t"
    },
    {
      "name": "pDst",
      "ordinal": 2,
      "storage": "Stack[0xc]:4",
      "type": "intrusive_ptr<App::PropertyList> *"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "bool",
  "return_type_resolved": true,
  "rva": "0x2a3310",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "bool App::cPropManager::GetGlobalPropertyList(cPropManager * this, uint32_t instanceID, intrusive_ptr<App::PropertyList> * pDst)",
  "size_bytes": 22,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x006a3310",
  "vtables": {
    "referenced_by_vtables": [
      "0x014091e8"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "01409218"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__cPropManager__GetGlobalPropertyList.c",
  "file": "src/reconstruction/pkg_runtime_services_wave7/runtime_services_wave7.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__cPropManager__GetGlobalPropertyList.c",
    "src/reconstruction/pkg_runtime_services_wave7/runtime_services_wave7.cpp",
    "src/reconstruction/pkg_runtime_services_wave7/runtime_services_wave7.hpp",
    "src/reconstruction/pkg_runtime_services_wave7/runtime_services_wave7_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave7/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-runtime-services-wave7/006a3310.json"
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
    "required"
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
  "OpaquePropertyListRef*",
  "OpaqueRuntimeService",
  "TargetWord",
  "virtual dispatch result"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x014091e8"
]
```

## Conflicts

```json
[]
```
