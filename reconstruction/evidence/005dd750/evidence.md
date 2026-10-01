# Evidence 0x005dd750

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `32c02597c57e676336ac50c993df0cf29fcaa878fb4e6c1d16613d514700e9c8`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "__thiscall observed",
  "hidden_this_register": "ECX",
  "return_register": "EAX",
  "return_type": "OpaquePreferenceQuery *",
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "observed_use": "Forwarded unchanged to the property-value callback",
      "position": 1,
      "type": "OpaquePropertyValue *",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 4,
  "termination": "RET 0x4"
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
      }
    ],
    "stack_cleanup_bytes": 4,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x4"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +4, so the listing is not one path"
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
  "content_sha256": "003bcbcbfeeadd203975bf6e8a4f15e51d3cb982894190689998ed2468545e7b",
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
    "ghidra_parameter_count": 0,
    "persisted": "no_information",
    "persisted_calling_convention": "__thiscall observed"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0013"
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
        "obs-0002"
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
        "obs-0007"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          16,
          18
        ],
        "register": "ECX",
        "written_through": 2
      }
    },
    {
      "based_on": [
        "obs-0005",
        "obs-0006",
        "obs-0007",
        "obs-0013"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0013"
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
        "obs-0013"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0013"
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
      "at": "0x005dd750",
      "count": 1,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EDX,dword ptr [ESP + 0x4]",
      "reg": "ESP"
    },
    {
      "at": "0x005dd750",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0002",
      "index": 0,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EDX,dword ptr [ESP + 0x4]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x005dd750",
      "definite": true,
      "id": "obs-0003",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [ESP + 0x4]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x005dd754",
      "count": 5,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x005dd755",
      "count": 3,
      "first_use": 2,
      "first_write_index": 3,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x005dd755",
      "definite": true,
      "id": "obs-0006",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x005dd757",
      "definite": true,
      "id": "obs-0007",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "XOR ECX,ECX",
      "reg": "ECX",
      "write_kind": "zero"
    },
    {
      "at": "0x005dd759",
      "count": 2,
      "first_use": 4,
      "first_write_index": 4,
      "id": "obs-0008",
      "index": 4,
      "kind": "REG_READ",
      "raw": "XOR EAX,EAX",
      "reg": "EAX"
    },
    {
      "at": "0x005dd759",
      "definite": true,
      "id": "obs-0009",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "XOR EAX,EAX",
      "reg": "EAX",
      "write_kind": "zero"
    },
  
[TRUNCATED]
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
    "name": "Editors_EditorUI_HandleMessage_005e0000",
    "reconstructed": true,
    "va": "0x005e0000"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b76160"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00de9a00"
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
  "count": 13,
  "instructions": [
    {
      "address": "005dd750",
      "instruction": "MOV EDX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "005dd754",
      "instruction": "PUSH ESI"
    },
    {
      "address": "005dd755",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "005dd757",
      "instruction": "XOR ECX,ECX"
    },
    {
      "address": "005dd759",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "005dd75b",
      "instruction": "MOV word ptr [ESI + 0x12],CX"
    },
    {
      "address": "005dd75f",
      "instruction": "PUSH EDX"
    },
    {
      "address": "005dd760",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "005dd762",
      "instruction": "MOV word ptr [ESI + 0x10],AX"
    },
    {
      "address": "005dd766",
      "instruction": "CALL 0x00422e20"
    },
    {
      "address": "005dd76b",
      "instruction": "MOV EAX,ESI"
    },
    {
      "address": "005dd76d",
      "instruction": "POP ESI"
    },
    {
      "address": "005dd76e",
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
  "original_bytes": 7011,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"__thiscall observed\",\n    \"hidden_this_register\": \"ECX\",\n    \"return_register\": \"EAX\",\n    \"return_type\": \"OpaquePreferenceQuery *\",\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"observed_use\": \"Forwarded unchanged to the property-value callback\",\n        \"position\": 1,\n        \"type\": \"OpaquePropertyValue *\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 4,\n    \"termination\": \"RET 0x4\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaquePreferenceQuery\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 24,\n      \"symbol\": \"editor_query_clear_flags_0093db80\",\n      \"va\": \"0x0093db80\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"shared_types:OpaquePreferenceQuery,OpaquePropertyValue\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 17,\n      \"symbol\": \"Editors_EditorUI_HandleMessage_005e0000\",\n      \"va\": \"0x005e0000\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 16,\n      \"symbol\": \"editor_query_dispatch_005dfd00\",\n      \"va\": \"0x005dfd00\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 14,\n      \"symbol\": \"editor_query_service_005ca960\",\n      \"va\": \"0x005ca960\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 8,\n      \"symbol\": \"Editors_EditorModel_SetColor_raw_004ae250\",\n      \"va\": \"0x004ae250\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 8,\n      \"symbol\": \"FUN_005dda30\",\n      \"va\": \"0x005dda30\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"WAVE6-PRESENTATION\",\n      \"score\": 2,\n      \"symbol\": \"transform_pre_transform_by_0040ccb0\",\n      \"va\": \"0x0040ccb0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-WAVE6-CONTAINERS-MEMORY\",\n      \"score\": 2,\n      \"symbol\": \"wave6_reference_00432a50\",\n      \"va\": \"0x00432a50\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [\n    \"The external property owner and its persistence behavior are not reconstructed here.\",\n    \"The stack value pointer is semantically opaque and is not assigned a message or preference meaning.\"\n  ],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaquePreferenceQuery\",\n  \"cluster\": null,\n  \"confidence\": 0.95,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": \"Editors_EditorUI_HandleMessage_005e0000\",\n        \"reconstructed\": true,\n        \"va\": \"0x005e0000\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b76160\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00de9a00\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x005e0205\",\n        \"direction\": \"in\",\n        \"other\": \"0x005e0000\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b763b0\",\n        \"direction\": \"in\",\n        \"other\": \"0x00b76160\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00de9d06\",\n        \"direction\": \"in\",\n        \"other\": \"0x00de9a00\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005dd766\",\n        \"direction\": \"out\",\n        \"other\": \"0x00422e20\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 3,\n    \"fan_out\": 0,\n    \"manifest_callees\": [\n      \"0x00422e20\"\n    ],\n    \"manifest_callers\": [\n      \"direct_caller_functions_3\",\n      \"function_xrefs_6\"\n    ],\n    \"nearby_reconstructed\": [\n      \"0x005e0000\"\n    ],\n    \"scc\": {\n      \"id\": \"scc-0132\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"OBSERVED\",\n  \"globals\": [],\n  \"integration_status\": \"integrated\",\n  \"name\": \"editor_query_reset_005dd750\",\n  \"normalized_symbol\": \"editor_query_reset_005dd750\",\n  \"observed_mechanics\": [\n    \"clears +0x12 then +0x10\",\n    \"calls 0x00422e20\",\n    \"returns query pointer\",\n    \"RET 4\"\n  ],\n  \"ownership\": {\n    \"claimability\": \"do_not_claim\",\n    \"handoff_packages\": [\n      \"PKG-10-EDITOR-DISPATCH\"\n    ],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": \"source-wave3/PKG-10-EDITOR-DISPATCH\"\n    },\n    \"package\": \"PKG-10-EDITOR-DISPATCH\",\n    \"queue_state\": null\n  },\n  \"package\": \"PKG-10-EDITOR-DISPATCH\",\n  \"reconstructed\": true,\n  \"review_status\": \"approved\",\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"gate-editor-query-property-callback\"\n    ],\n    \"validated\": 0\n  },\n  \"runtime_gated\": true,\n  \"runtime_validated\":
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
  "body_end": "005dd770",
  "body_span_bytes": 33,
  "body_start": "005dd750",
  "callees": [
    "App::Property::SetValueBool"
  ],
  "callers": [
    "FUN_00de9a00",
    "FUN_00b76160",
    "FUN_005e0000"
  ],
  "classification": "wrapper",
  "dispatch": null,
  "entry_point": "005dd750",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_005dd750",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x1dd750",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_005dd750(void)",
  "size_bytes": 33,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x005dd750",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 6,
  "xrefs": [
    {
      "from": "005e0205"
    },
    {
      "from": "00b763b0"
    },
    {
      "from": "00de9d06"
    },
    {
      "from": "0093e671"
    },
    {
      "from": "00de1c81"
    },
    {
      "from": "00de1d23"
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
  "file": "src/reconstruction/pkg10_editor_dispatch/editor_query_helpers.cpp",
  "files": [
    "reconstruction/staging/pkg10-editor-dispatch/editor_query_helpers.cpp",
    "reconstruction/staging/pkg10-editor-dispatch/editor_query_helpers.hpp",
    "reconstruction/staging/pkg10-editor-dispatch/editor_query_helpers_model_test.cpp",
    "src/reconstruction/pkg10_editor_dispatch/editor_query_helpers.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-source-wave3/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg10-editor-dispatch/005dd750.json"
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
    "gate-editor-query-property-callback"
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
  "OpaquePreferenceQuery",
  "OpaquePreferenceQuery *",
  "OpaquePropertyValue",
  "OpaquePropertyValue *"
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
