# Evidence 0x007c66b0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `c85a94e93a4bcf8990a6a9010a31a49dcc0501dcba2b9031c5cec4ab49cdf321`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": 2,
  "ordinary_stack_arguments": [
    "dword message id at [ESP+4] after entry; address taken at 0x007c66b7 LEA EAX,[ESP+0x14] and passed as the hash key",
    "dword message payload at [ESP+8] after entry; never read by any instruction in 0x007c66b0..0x007c66f8"
  ],
  "ret_form": "RET 0x4",
  "return_semantics": "true when the message id resolved in the receiver's registry at +0x60 and the payload was forwarded to virtual slot 0x54; false when the lookup returned the miss sentinel and nothing was dispatched",
  "return_type": "bool",
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
        "size_inferred": true,
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
    "return_semantics": "integral_in_EAX",
    "saved_registers": [
      "EDI",
      "ESI"
    ],
    "stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": true,
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
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -4, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 4,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x4",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "e202f2f6de4b2e85ab61cb6dcdf620b546bfa3f8bd2e61ff64019f308b83141f",
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
        "obs-0020",
        "obs-0023"
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
        "obs-0009"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 1,
        "total_bytes": 4
      }
    },
    {
      "based_on": [
        "obs-0005",
        "obs-0006",
        "obs-0010",
        "obs-0011",
        "obs-0016"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          0
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0005",
        "obs-0006",
        "obs-0010",
        "obs-0011",
        "obs-0016",
        "obs-0020",
        "obs-0023"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0020",
        "obs-0023"
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
        "obs-0020",
        "obs-0023"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0020",
        "obs-0023"
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
      "and_esp": null,
      "at": "0x007c66b0",
      "ebp_is_general_register": false,
      "fp": false,
      "id": "obs-0001",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": false,
      "push_ebp_at": null,
      "raw": "SUB ESP,0x8",
      "sub": 8
    },
    {
      "at": "0x007c66b0",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x8",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x007c66b3",
      "count": 5,
      "first_use": 1,
      "first_write_index": null,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x007c66b4",
      "count": 4,
      "first_use": 2,
      "first_write_index": 3,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x007c66b5",
      "count": 4,
      "first_use": 3,
      "first_write_index": 9,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV EDI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x007c66b5",
      "definite": true,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV EDI,ECX",
      "reg": "EDI",
      "write_kind": "reg"
    },
    {
      "at": "0x007c66b7",
      "count": 4,
      "first_use": 4,
      "first_write_index": 13,
      "id": "obs-0007",
      "index": 4,
      "kind": "REG_READ",
      "raw": "LEA EAX,[ESP + 0x14]",
      "reg": "EAX"
    },
    {
      "at": "0x007c66b7",
      "count": 3,
      "first_use": 4,
      "first_write_index": 0,
      "id": "obs-0008",
      "index": 4,
      "kind": "REG_READ",
      "raw": "LEA EAX,[ESP + 0
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
  "count": 32,
  "instructions": [
    {
      "address": "007c66b0",
      "instruction": "SUB ESP,0x8"
    },
    {
      "address": "007c66b3",
      "instruction": "PUSH ESI"
    },
    {
      "address": "007c66b4",
      "instruction": "PUSH EDI"
    },
    {
      "address": "007c66b5",
      "instruction": "MOV EDI,ECX"
    },
    {
      "address": "007c66b7",
      "instruction": "LEA EAX,[ESP + 0x14]"
    },
    {
      "address": "007c66bb",
      "instruction": "PUSH EAX"
    },
    {
      "address": "007c66bc",
      "instruction": "LEA ECX,[ESP + 0xc]"
    },
    {
      "address": "007c66c0",
      "instruction": "LEA ESI,[EDI + 0x60]"
    },
    {
      "address": "007c66c3",
      "instruction": "PUSH ECX"
    },
    {
      "address": "007c66c4",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "007c66c6",
      "instruction": "CALL 0x00645ed0"
    },
    {
      "address": "007c66cb",
      "instruction": "MOV EDX,dword ptr [ESI + 0x8]"
    },
    {
      "address": "007c66ce",
      "instruction": "MOV ECX,dword ptr [ESI + 0x4]"
    },
    {
      "address": "007c66d1",
      "instruction": "MOV EAX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "007c66d5",
      "instruction": "CMP EAX,dword ptr [ECX + EDX*0x4]"
    },
    {
      "address": "007c66d8",
      "instruction": "JZ 0x007c66f1"
    },
    {
      "address": "007c66da",
      "instruction": "MOV EDX,dword ptr [EDI]"
    },
    {
      "address": "007c66dc",
      "instruction": "MOV EAX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "007c66df",
      "instruction": "MOV EDX,dword ptr [EDX + 0x54]"
    },
    {
      "address": "007c66e2",
      "instruction": "PUSH EAX"
    },
    {
      "address": "007c66e3",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "007c66e5",
      "instruction": "CALL EDX"
    },
    {
      "address": "007c66e7",
      "instruction": "POP EDI"
    },
    {
      "address": "007c66e8",
      "instruction": "MOV AL,0x1"
    },
    {
      "address": "007c66ea",
      "instruction": "POP ESI"
    },
    {
      "address": "007c66eb",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "007c66ee",
      "instruction": "RET 0x4"
    },
    {
      "address": "007c66f1",
      "instruction": "POP EDI"
    },
    {
      "address": "007c66f2",
      "instruction": "XOR AL,AL"
    },
    {
      "address": "007c66f4",
      "instruction": "POP ESI"
    },
    {
      "address": "007c66f5",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "007c66f8",
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
  "original_bytes": 7069,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": 2,\n    \"ordinary_stack_arguments\": [\n      \"dword message id at [ESP+4] after entry; address taken at 0x007c66b7 LEA EAX,[ESP+0x14] and passed as the hash key\",\n      \"dword message payload at [ESP+8] after entry; never read by any instruction in 0x007c66b0..0x007c66f8\"\n    ],\n    \"ret_form\": \"RET 0x4\",\n    \"return_semantics\": \"true when the message id resolved in the receiver's registry at +0x60 and the payload was forwarded to virtual slot 0x54; false when the lookup returned the miss sentinel and nothing was dispatched\",\n    \"return_type\": \"bool\",\n    \"stack_cleanup_bytes\": 4\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-app-proplist-copyall-wave16\",\n      \"score\": 8,\n      \"symbol\": \"all_copy_from_properties_006a14d0\",\n      \"va\": \"0x006a14d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-dfw-006a1540\",\n      \"score\": 8,\n      \"symbol\": \"proplist_write_006a1540\",\n      \"va\": \"0x006a1540\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-property-clear-wave13\",\n      \"score\": 8,\n      \"symbol\": \"property_list_clear_006a2a80\",\n      \"va\": \"0x006a2a80\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-direct-property-clear-wave14\",\n      \"score\": 8,\n      \"symbol\": \"direct_property_list_clear_006a2b20\",\n      \"va\": \"0x006a2b20\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-property-remove-006a2ef0\",\n      \"score\": 8,\n      \"symbol\": \"property_list_remove_property_006a2ef0\",\n      \"va\": \"0x006a2ef0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"app-lifecycle\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x007c66c6\",\n        \"direction\": \"out\",\n        \"other\": \"0x00645ed0\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0239\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"CONFIRMED\",\n  \"globals\": [],\n  \"integration_status\": null,\n  \"name\": \"App::cCameraManager::HandleMessage\",\n  \"normalized_symbol\": \"App::cCameraManager::HandleMessage\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"runtime_gated_requires_explicit_gate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"queued\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"No Wine/original trace was run for this target; no runtime promotion is claimed.\"\n    ],\n    \"validated\": 0\n  },\n  \"runtime_gated\": true,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": null,\n  \"services\": [],\n  \"source\": {\n    \"decomp\": \".spore-analysis/ghidra-exports/decompiled_sdk/App__cCameraManager__HandleMessage.c\",\n    \"file\": null,\n    \"files\": [\n      \".spore-analysis/ghidra-exports/decompiled_sdk/App__cCameraManager__HandleMessage.c\",\n      \"reconstruction/staging/pkg-camera-msg-007c66b0/camera_msg_007c66b0.cpp\",\n      \"reconstruction/staging/pkg-camera-msg-007c66b0/camera_msg_007c66b0.hpp\",\n      \"reconstruction/staging/pkg-camera-msg-007c66b0/camera_msg_007c66b0_model_test.cpp\"\n    ],\n    \"handoffs\": [],\n    \"metadata\": [\n      \"reconstruction/metadata/pkg-camera-msg-007c66b0/007c66b0.json\"\n    ],\n    \"provenance\": []\n  },\n  \"status\": \"queued\",\n  \"subsystem\": \"App\",\n  \"triage\": {\n    \"category\": \"ENGINE_INTERFACE\",\n    \"cluster\": \"app-lifecycle\",\n    \"db_triage_status\": \"QUEUED\",\n    \"decomp_path\": \".spore-analysis/ghidra-exports/decompiled_sdk/App__cCameraManager__HandleMessage.c\",\n    \"dependencies\": [\n      \"resource-io\"\n    ],\n    \"evidence\": \"CONFIRMED\",\n    \"kg_node_id\": \"fun:007c66b0\",\n    \"name\": \"App::cCameraManager::HandleMessage\",\n    \"priority\"
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
  "body_end": "007c66fa",
  "body_span_bytes": 75,
  "body_start": "007c66b0",
  "callees": [
    "FUN_00645ed0"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "007c66b0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_8",
      "storage": "Stack[-0x8]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 1,
  "mode": "live",
  "name": "App::cCameraManager::HandleMessage",
  "namespace": "App",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 3,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "cCameraManager *"
    },
    {
      "name": "messageID",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "uint32_t"
    },
    {
      "name": "pMessage",
      "ordinal": 2,
      "storage": "Stack[0xc]:4",
      "type": "void *"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "bool",
  "return_type_resolved": true,
  "rva": "0x3c66b0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "bool App::cCameraManager::HandleMessage(cCameraManager * this, uint32_t messageID, void * pMessage)",
  "size_bytes": 75,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x007c66b0",
  "vtables": {
    "referenced_by_vtables": [
      "0x014106a4"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "014106dc"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__cCameraManager__HandleMessage.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__cCameraManager__HandleMessage.c",
    "reconstruction/staging/pkg-camera-msg-007c66b0/camera_msg_007c66b0.cpp",
    "reconstruction/staging/pkg-camera-msg-007c66b0/camera_msg_007c66b0.hpp",
    "reconstruction/staging/pkg-camera-msg-007c66b0/camera_msg_007c66b0_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-camera-msg-007c66b0/007c66b0.json"
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
    "No Wine/original trace was run for this target; no runtime promotion is claimed."
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
  "status": "queued"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "bool"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x014106a4"
]
```

## Conflicts

```json
[]
```
