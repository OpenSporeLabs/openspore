# Evidence 0x007e6100

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `a972ed663ab0f4520fcf30e021944ee9754ef6f68985e6b8190aeaadf570fcbc`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "cdecl-shaped two-argument body with an unused ECX receiver",
  "hidden_receiver": "ECX is overwritten from the global string-pointer slot and is not an ordinary machine parameter.",
  "ordinary_stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "instance_ids",
      "position": 1,
      "type": "const char*"
    },
    {
      "entry_offset": "ESP+0x08",
      "name": "group_ids",
      "position": 2,
      "type": "OpaqueWord*"
    }
  ],
  "return_note": "in AL",
  "return_type": "std::uint8_t",
  "stack_cleanup_bytes": 0,
  "termination": "plain RET after POP ESI"
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
      }
    ]
  },
  "abstained_because": [
    "no_terminal_ret: the only exit observed is a tail jump",
    "receiver_not_determinable: ecx_reassigned_before_deref"
  ],
  "cleanup": {
    "bytes": null,
    "confidence": "UNKNOWN",
    "corroboration": "not_available",
    "evidence": null,
    "side": null
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "9b71df6a9879fbbd6485c77f187aa5d401d69ce5238291b9e1b26a9f5cb691d4",
  "conventions": {
    "ambiguities": [
      "tail_call"
    ],
    "calling_convention": null,
    "candidate_conventions": [
      "__cdecl",
      "__stdcall",
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
    "ghidra_parameter_count": 3,
    "persisted": "no_information",
    "persisted_calling_convention": "cdecl-shaped two-argument body with an unused ECX receiver"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0010"
      ],
      "claim": "no terminal return is present in the listing",
      "confidence": "UNKNOWN",
      "id": "C2"
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
        "obs-0001",
        "obs-0007"
      ],
      "claim": "the register receiver is undetermined: ecx_reassigned_before_deref",
      "confidence": "UNKNOWN",
      "id": "R0",
      "value": {
        "reason": "ecx_reassigned_before_deref",
        "register": null
      }
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
      "claim": "this listing is a tail transfer: it inherits its caller's frame and never runs its own RET",
      "confidence": "UNKNOWN",
      "id": "T1",
      "value": {
        "form": "jmp"
      }
    }
  ],
  "observations": [
    {
      "at": "0x007e6100",
      "definite": true,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [0x0143e9b4]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x007e6106",
      "count": 2,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x007e6107",
      "count": 1,
      "first_use": 2,
      "first_write_index": null,
      "id": "obs-0003",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV ESI,dword ptr [ESP + 0x8]",
      "reg": "ESP"
    },
    {
      "at": "0x007e6107",
      "base": "ESP",
      "disp": 8,
      "id": "obs-0004",
      "index": 2,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV ESI,dword ptr [ESP + 0x8]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x007e6107",
      "definite": true,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,dword ptr [ESP + 0x8]",
      "reg": "ESI",
      "write_kind": "mem_load"
    },
    {
      "at": "0x007e610b",
      "definite": true,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,ESI",
      "reg": "EAX",
      "write_kind": "reg"
    },
    {
      "at": "0x007e610d",
      "count": 4,
      "first_use": 4,
      "first_write_index": 0,
      "id": "obs-0007",
      "index": 4,
      "kind": "REG_READ",
      "raw": "LEA ECX,[ECX]",
      "reg": "ECX"
    },
    {
      "at": "0x007e6110",
      "count": 3,
      "first_use": 5,
      "first_write_index": 3,
      "id": "obs-0008",
      "index": 5,
      "kind": "REG_READ",
      "raw": "MOV DL,byte ptr [EAX]",
      "reg": "EAX"
    },
    {
      "at": "0x007e6110",
      "definite": true,
      "id": "obs-0009",
      "index": 5,
      "kind": "REG_WRITE",
      "raw": "MOV DL,byte ptr [EAX]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x007e612e",
      "id": "obs-0010",
      "index": 18,
      "kind": "UNCOND_TRANSFER_OUT",
      "raw": "JMP 0x007e6135",
      "target": "0x007e6135"
    }
  ],
  "parse": {
    "declared_count": 19,
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
    "confidence": "UNKNOWN",
    "distinct_offsets": 0,
    "max_offset": null,
    "offsets": [],
    "present": null,
    "reason": "ecx_reassigned_be
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
  "count": 19,
  "instructions": [
    {
      "address": "007e6100",
      "instruction": "MOV ECX,dword ptr [0x0143e9b4]"
    },
    {
      "address": "007e6106",
      "instruction": "PUSH ESI"
    },
    {
      "address": "007e6107",
      "instruction": "MOV ESI,dword ptr [ESP + 0x8]"
    },
    {
      "address": "007e610b",
      "instruction": "MOV EAX,ESI"
    },
    {
      "address": "007e610d",
      "instruction": "LEA ECX,[ECX]"
    },
    {
      "address": "007e6110",
      "instruction": "MOV DL,byte ptr [EAX]"
    },
    {
      "address": "007e6112",
      "instruction": "CMP DL,byte ptr [ECX]"
    },
    {
      "address": "007e6114",
      "instruction": "JNZ 0x007e6130"
    },
    {
      "address": "007e6116",
      "instruction": "TEST DL,DL"
    },
    {
      "address": "007e6118",
      "instruction": "JZ 0x007e612c"
    },
    {
      "address": "007e611a",
      "instruction": "MOV DL,byte ptr [EAX + 0x1]"
    },
    {
      "address": "007e611d",
      "instruction": "CMP DL,byte ptr [ECX + 0x1]"
    },
    {
      "address": "007e6120",
      "instruction": "JNZ 0x007e6130"
    },
    {
      "address": "007e6122",
      "instruction": "ADD EAX,0x2"
    },
    {
      "address": "007e6125",
      "instruction": "ADD ECX,0x2"
    },
    {
      "address": "007e6128",
      "instruction": "TEST DL,DL"
    },
    {
      "address": "007e612a",
      "instruction": "JNZ 0x007e6110"
    },
    {
      "address": "007e612c",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "007e612e",
      "instruction": "JMP 0x007e6135"
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
  "original_bytes": 6602,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"cdecl-shaped two-argument body with an unused ECX receiver\",\n    \"hidden_receiver\": \"ECX is overwritten from the global string-pointer slot and is not an ordinary machine parameter.\",\n    \"ordinary_stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"name\": \"instance_ids\",\n        \"position\": 1,\n        \"type\": \"const char*\"\n      },\n      {\n        \"entry_offset\": \"ESP+0x08\",\n        \"name\": \"group_ids\",\n        \"position\": 2,\n        \"type\": \"OpaqueWord*\"\n      }\n    ],\n    \"return_note\": \"in AL\",\n    \"return_type\": \"std::uint8_t\",\n    \"stack_cleanup_bytes\": 0,\n    \"termination\": \"plain RET after POP ESI\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:DATA,OpaqueAppSystem\"\n      ],\n      \"package\": \"PKG-APP-LIFECYCLE-WAVE7\",\n      \"score\": 25,\n      \"symbol\": \"app_capp_system_hook_windows_007e6080\",\n      \"va\": \"0x007e6080\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:DATA,OpaqueAppSystem\"\n      ],\n      \"package\": \"PKG-APP-LIFECYCLE-WAVE7\",\n      \"score\": 25,\n      \"symbol\": \"app_capp_system_func88h_00a6c940\",\n      \"va\": \"0x00a6c940\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_types:DATA\"\n      ],\n      \"package\": \"WAVE6-ENGINE-RUNTIME\",\n      \"score\": 9,\n      \"symbol\": \"app_system_service_gate_dispatch_007e5f30\",\n      \"va\": \"0x007e5f30\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_types:DATA\"\n      ],\n      \"package\": \"PKG-APP-LIFECYCLE-WAVE8\",\n      \"score\": 9,\n      \"symbol\": \"app_c_cell_mode_strategy_dispose_00e81f30\",\n      \"va\": \"0x00e81f30\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DATA\"\n      ],\n      \"package\": \"PKG-SKINNER-SAFE-WAVE10\",\n      \"score\": 3,\n      \"symbol\": \"skin_painter_job_brush_pass_005182f0\",\n      \"va\": \"0x005182f0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DATA\"\n      ],\n      \"package\": \"PKG-18-UI-SCRIPTING\",\n      \"score\": 3,\n      \"symbol\": \"FUN_005bf9d0\",\n      \"va\": \"0x005bf9d0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DATA\"\n      ],\n      \"package\": \"PKG-18-UI-SCRIPTING\",\n      \"score\": 3,\n      \"symbol\": \"FUN_005c0100\",\n      \"va\": \"0x005c0100\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DATA\"\n      ],\n      \"package\": \"PKG-18-UI-SCRIPTING\",\n      \"score\": 3,\n      \"symbol\": \"FUN_005c0380\",\n      \"va\": \"0x005c0380\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Static mechanics and x86-32 ABI reviewed from live Ghidra; runtime values, concrete owners, and unresolved ports remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [\n    \"Original-process input strings, service results, and output lifetime remain runtime-gated.\"\n  ],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueAppSystem\",\n  \"cluster\": null,\n  \"confidence\": 0.7,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0251\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"SUPPORTED\",\n  \"globals\": [\n    \"global:0x0143e9b4 contains a pointer to the GetSharedLibraryVersion string at 0x0143e8e4.\"\n  ],\n  \"integration_status\": \"integrated\",\n  \"name\": \"app_capp_system_set_effect_collection_ids_007e6100\",\n  \"normalized_symbol\": \"app_capp_system_set_effect_collection_ids_007e6100\",\n  \"observed_mechanics\": [\n    \"{\\\"first_match\\\": \\\"Write the immediate 0x0153f864 to group_ids[0], set AL to 1, and return without helper calls.\\\", \\\"first_mismatch\\\": \\\"Continue at 0x007e6130 with the first argument in ESI, the first-comparison carry in flags, and the saved output pointer at the inherited ESP+0x10 continuation-relative slot.\\\", \\\"first_string\\\": \\\"GetSharedLibraryVersion\\\", \\\"null_behavior\\\": \\\"The byte comparison has no null guard; a null instance_ids faults. A null group_ids faults only on a matching path that writes it.\\\"}\"\n  ],\n  \"ownership\": {\n    \"claimability\": \"do_not_claim\",\n    \"handoff_packages\": [\n      \"PKG-APP-LIFECYCLE-WAVE7\"\n    ],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": \"PKG-APP-LIFECYCLE-WAVE7\",\n    \"queue_state\": null\n  },\n  \"package\": \"PKG-APP-LIFECYCLE-WAVE7\",\n  \"reconstructed\": true,\n  \"review_status\": \"approved_after_parallel_review\",\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"Observe the input string values, the output buffer lifetime, and the concrete helper objects at the 0x0067xxxx service addresses before promoting collection identity semantics.\"\n    ],\n    \"validated\": 0\n  },\n  \"runtime_gated\": true,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": \"static_reconstruction_runtime_gated\",\n  \"services\": [],\n  \"source\": {\n    \"decomp\": null,\n    \"file\": \"src/reconstruction/pkg_app_lifecycle_wave7/app_lifecycle_wave7.cpp\",\n    \"files\": [\n      \"src/reco
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
  "body_end": "007e612f",
  "body_span_bytes": 48,
  "body_start": "007e6100",
  "callees": [],
  "callers": [],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "007e6100",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "App::cAppSystem::SetEffectCollectionIDs",
  "namespace": "App",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 3,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "cAppSystem *"
    },
    {
      "name": "instanceIDs",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "uint32_t *"
    },
    {
      "name": "groupIDs",
      "ordinal": 2,
      "storage": "Stack[0xc]:4",
      "type": "uint32_t *"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "void",
  "return_type_resolved": true,
  "rva": "0x3e6100",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "void App::cAppSystem::SetEffectCollectionIDs(cAppSystem * this, uint32_t * instanceIDs, uint32_t * groupIDs)",
  "size_bytes": 48,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x007e6100",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "007e9129"
    }
  ]
}
```

## globals

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "global:0x0143e9b4 contains a pointer to the GetSharedLibraryVersion string at 0x0143e8e4."
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg_app_lifecycle_wave7/app_lifecycle_wave7.cpp",
  "files": [
    "src/reconstruction/pkg_app_lifecycle_wave7/app_lifecycle_wave7.cpp",
    "src/reconstruction/pkg_app_lifecycle_wave7/app_lifecycle_wave7.hpp",
    "src/reconstruction/pkg_app_lifecycle_wave7/app_lifecycle_wave7_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave7/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-app-lifecycle-wave7/007e6100.json"
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
    "Observe the input string values, the output buffer lifetime, and the concrete helper objects at the 0x0067xxxx service addresses before promoting collection identity semantics."
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
  "OpaqueWord*",
  "const char*",
  "std::uint8_t in AL"
]
```

## vtables

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## Conflicts

```json
[]
```
