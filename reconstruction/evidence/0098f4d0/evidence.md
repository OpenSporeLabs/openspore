# Evidence 0x0098f4d0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `98ba9d62bbb65e2aa21fb03cb8ae1534b777064f562606390c6823eb7e3109c3`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "thiscall with one hidden ECX receiver and two ordinary stack words",
  "hidden_receiver": "ECX points to the cMessageManager object",
  "ordinary_stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "role": "queue index",
      "type": "uint32_t",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x08",
      "role": "queue pointer",
      "type": "opaque pointer word",
      "width_bytes": 4
    }
  ],
  "ret_form": "RET 0x8",
  "return_note": "result of service vtable slot +0x90",
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
    "saved_registers": [
      "ESI"
    ],
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
    "flow_not_modelled: the linear ESP walk ends at +8, so the listing is not one path"
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
  "content_sha256": "5b9effc815e81cf061b9b06cdbf09f36389067ea49636e6fd02ee2e4fbd6bbff",
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
    "persisted_calling_convention": "thiscall with one hidden ECX receiver and two ordinary stack words"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 3,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0018"
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
        "obs-0006",
        "obs-0008",
        "obs-0011",
        "obs-0012"
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
        "obs-0007",
        "obs-0010",
        "obs-0014"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          -520,
          -396,
          172,
          176,
          180,
          184
        ],
        "register": "ECX",
        "written_through": 4
      }
    },
    {
      "based_on": [
        "obs-0007",
        "obs-0010",
        "obs-0014",
        "obs-0018"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0018"
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
        "obs-0018"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0018"
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
      "at": "0x0098f4d0",
      "count": 5,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "ESP"
    },
    {
      "at": "0x0098f4d0",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0002",
      "index": 0,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x0098f4d0",
      "definite": true,
      "id": "obs-0003",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x0098f4d9",
      "count": 5,
      "first_use": 3,
      "first_write_index": 0,
      "id": "obs-0004",
      "index": 3,
      "kind": "REG_READ",
      "raw": "JMP dword ptr [EAX*0x4 + 0x98f538]",
      "reg": "EAX"
    },
    {
      "at": "0x0098f4d9",
      "base": null,
      "disp": 10024248,
      "id": "obs-0005",
      "index": 3,
      "kind": "JMP_INDIRECT",
      "raw": "JMP dword ptr [EAX*0x4 + 0x98f538]",
      "via": "memory"
    },
    {
      "at": "0x0098f4e0",
      "base": "ESP",
      "disp": 8,
      "id": "obs-0006",
      "index": 4,
      "key": 8,
      "kind": "STA
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
  "count": 29,
  "instructions": [
    {
      "address": "0098f4d0",
      "instruction": "MOV EAX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "0098f4d4",
      "instruction": "CMP EAX,0x3"
    },
    {
      "address": "0098f4d7",
      "instruction": "JA 0x0098f50e"
    },
    {
      "address": "0098f4d9",
      "instruction": "JMP dword ptr [EAX*0x4 + 0x98f538]"
    },
    {
      "address": "0098f4e0",
      "instruction": "MOV EAX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "0098f4e4",
      "instruction": "MOV dword ptr [ECX + 0xac],EAX"
    },
    {
      "address": "0098f4ea",
      "instruction": "JMP 0x0098f50e"
    },
    {
      "address": "0098f4ec",
      "instruction": "MOV EDX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "0098f4f0",
      "instruction": "MOV dword ptr [ECX + 0xb0],EDX"
    },
    {
      "address": "0098f4f6",
      "instruction": "JMP 0x0098f50e"
    },
    {
      "address": "0098f4f8",
      "instruction": "MOV EAX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "0098f4fc",
      "instruction": "MOV dword ptr [ECX + 0xb4],EAX"
    },
    {
      "address": "0098f502",
      "instruction": "JMP 0x0098f50e"
    },
    {
      "address": "0098f504",
      "instruction": "MOV EDX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "0098f508",
      "instruction": "MOV dword ptr [ECX + 0xb8],EDX"
    },
    {
      "address": "0098f50e",
      "instruction": "MOV EAX,dword ptr [ECX + 0xfffffdf8]"
    },
    {
      "address": "0098f514",
      "instruction": "MOV EDX,dword ptr [EAX + 0x7c]"
    },
    {
      "address": "0098f517",
      "instruction": "PUSH ESI"
    },
    {
      "address": "0098f518",
      "instruction": "LEA ESI,[ECX + 0xfffffdf8]"
    },
    {
      "address": "0098f51e",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "0098f520",
      "instruction": "PUSH 0x8"
    },
    {
      "address": "0098f522",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "0098f524",
      "instruction": "CALL EDX"
    },
    {
      "address": "0098f526",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "0098f528",
      "instruction": "MOV EDX,dword ptr [EAX + 0x90]"
    },
    {
      "address": "0098f52e",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "0098f530",
      "instruction": "CALL EDX"
    },
    {
      "address": "0098f532",
      "instruction": "POP ESI"
    },
    {
      "address": "0098f533",
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
  "original_bytes": 6900,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"thiscall with one hidden ECX receiver and two ordinary stack words\",\n    \"hidden_receiver\": \"ECX points to the cMessageManager object\",\n    \"ordinary_stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"role\": \"queue index\",\n        \"type\": \"uint32_t\",\n        \"width_bytes\": 4\n      },\n      {\n        \"entry_offset\": \"ESP+0x08\",\n        \"role\": \"queue pointer\",\n        \"type\": \"opaque pointer word\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"ret_form\": \"RET 0x8\",\n    \"return_note\": \"result of service vtable slot +0x90\",\n    \"return_register\": \"EAX\",\n    \"return_width_bytes\": 4,\n    \"stack_cleanup_bytes\": 8\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-WAVE6-MISC-ENGINE\",\n      \"score\": 8,\n      \"symbol\": \"game_time_manager_get_00b3d480\",\n      \"va\": \"0x00b3d480\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-WAVE6-MISC-ENGINE\",\n      \"score\": 8,\n      \"symbol\": \"destructible_lifecycle_thunk_00b63980\",\n      \"va\": \"0x00b63980\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01445cb8\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"re_00575ea0\",\n      \"va\": \"0x00575ea0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:opaque pointer word\"\n      ],\n      \"package\": \"PKG-06-WAVE6-APP-MANAGERS\",\n      \"score\": 3,\n      \"symbol\": \"App_IStateManager_Get_0067dce0\",\n      \"va\": \"0x0067dce0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:opaque pointer word\"\n      ],\n      \"package\": \"PKG-06-WAVE6-APP-MANAGERS\",\n      \"score\": 3,\n      \"symbol\": \"App_IPropManager_Get_0067ddf0\",\n      \"va\": \"0x0067ddf0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:OpaqueMessageManager\"\n      ],\n      \"package\": \"PKG-06-WAVE6-APP-MANAGERS\",\n      \"score\": 3,\n      \"symbol\": \"MessageManagerCleanupStorageWalker_008841f0\",\n      \"va\": \"0x008841f0\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"The unsigned four-slot write guard, field offsets, manager-0x208 service read, callback order, and returned EAX are exact; queue and service ownership remain unresolved.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"pass_after_repair\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueMessageManager\",\n  \"cluster\": \"app-lifecycle\",\n  \"confidence\": 0.93,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [\n      \"service vtable +0x7c\",\n      \"service vtable +0x90\"\n    ],\n    \"manifest_callers\": [\n      \"data_xref_01445cec\"\n    ],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0331\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"OBSERVED\",\n  \"globals\": [],\n  \"integration_status\": \"integrated\",\n  \"name\": \"App::cMessageManager::GetMessageQueue\",\n  \"normalized_symbol\": \"message_manager_get_queue_0098f4d0\",\n  \"observed_mechanics\": [\n    \"thiscall receiver, index, and queue pointer\",\n    \"write queue pointer at +0xac through +0xb8 only for indexes 0 through 3\",\n    \"out-of-range index skips the write\",\n    \"read service from manager-0x208\",\n    \"call service vtable+0x7c with logical arguments 8 then 1\",\n    \"call service vtable+0x90 without stack arguments\",\n    \"return the +0x90 EAX result\",\n    \"RET 8\"\n  ],\n  \"ownership\": {\n    \"claimability\": \"do_not_claim\",\n    \"handoff_packages\": [\n      \"PKG-WAVE6-MISC-ENGINE\"\n    ],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": \"PKG-WAVE6-MISC-ENGINE\",\n    \"queue_state\": \"queued\"\n  },\n  \"package\": \"PKG-WAVE6-MISC-ENGINE\",\n  \"reconstructed\": true,\n  \"review_status\": \"approved\",\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"gate-message-queue-service-vtable-and-ownership\"\n    ],\n    \"validated\": 0\n  },\n  \"runtime_gated\": true,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": \"static_message_queue_write_and_callback_order_runtime_service_unknown\",\n  \"services\": [],\n  \"source\": {\n    \"decomp\": \".spore-analysis/ghidra-exports/decompiled_sdk/App__cMessageManager__GetMessageQueue.c\",\n    \"file\": \"src/reconstruction/wave6_misc_engine/misc_engine.cpp\",\n    \"files\": [\n      \".spore-analysis/ghidra-exports/decompiled_sdk/App__cMessageManager__GetMessageQueue.c\",\n      \"reconstruction/staging/wave6-misc-engine/misc_engine.cpp\",\n      \"reconstruction/staging/wave6-misc-engine/misc_engine.hpp\",\n      \"reconstruction/staging/wave6-misc-engine/misc_engine_model_test.cpp\",\n      \"src/reconstruction/wave6_misc_engine/misc_engine.cpp\"\n    ],\n    \"handoffs\": [\n      \"reconstruction/integrated/batch-2026-09-25-wave6/handoff.json\"\n    ],\n    \"metadata\": [\n      \"reconstruction/metadata/wave6-misc-engine/0098f4d0.json\"\n    ],\n    \"provenance\": [\n      \"reconstruction/metadata/wave6-misc-engine/0098f4d0.json\"\n    ]\n  },\n  \"status\": \"reconstructed\",\n  \"subsystem\": \"App.MessageQueue\",\n  \"triage\": {\n    \"category\": \"ENGINE_INTERFACE\",\n    \"cluster\": \"app-lifecycle\",\n    \"db_triage_status\": \"QUEUED\",\n    \"decomp_path\": \".spore-analysis/ghidr
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
  "body_end": "0098f535",
  "body_span_bytes": 102,
  "body_start": "0098f4d0",
  "callees": [],
  "callers": [],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "0098f4d0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "App::cMessageManager::GetMessageQueue",
  "namespace": "App",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 1,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "cMessageManager *"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "int",
  "return_type_resolved": true,
  "rva": "0x58f4d0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "int App::cMessageManager::GetMessageQueue(cMessageManager * this)",
  "size_bytes": 102,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x0098f4d0",
  "vtables": {
    "referenced_by_vtables": [
      "0x01445cb8"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "01445cec"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__cMessageManager__GetMessageQueue.c",
  "file": "src/reconstruction/wave6_misc_engine/misc_engine.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__cMessageManager__GetMessageQueue.c",
    "reconstruction/staging/wave6-misc-engine/misc_engine.cpp",
    "reconstruction/staging/wave6-misc-engine/misc_engine.hpp",
    "reconstruction/staging/wave6-misc-engine/misc_engine_model_test.cpp",
    "src/reconstruction/wave6_misc_engine/misc_engine.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/wave6-misc-engine/0098f4d0.json"
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
    "gate-message-queue-service-vtable-and-ownership"
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
  "MessageQueuePorts",
  "OpaqueMessageManager",
  "OpaqueMessageService",
  "opaque pointer word",
  "result of service vtable slot +0x90",
  "uint32_t"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x01445cb8"
]
```

## Conflicts

```json
[]
```
