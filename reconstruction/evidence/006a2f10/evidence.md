# Evidence 0x006a2f10

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `f3f37d2d9217c01f9168687ccb1d0164b2081eae05f8b8577f4b56e45a77a0a0`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_this": true,
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": 1,
  "ordinary_stack_arguments": [
    {
      "entry_offset": "entry_ESP+0x4",
      "observed": true,
      "ordinal": 1,
      "read": true,
      "read_at": "0x006a2f10 MOV EAX,dword ptr [ESP + 0x4]",
      "role": "the source property list; its words at +0x18 and +0x1c are the iterated range",
      "sizes": [
        4
      ],
      "written": false
    }
  ],
  "ret_form": "RET 0x4",
  "return_register": "EAX",
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "callee"
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
      "EBP",
      "EBX",
      "EDI",
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
    "flow_not_modelled: the linear ESP walk ends at +8, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register"
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
  "content_sha256": "a2b96cb73e12e174a02f48ac057a3b5e0866e4eba3f50d9920d9acbb29625cc8",
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
        "obs-0006",
        "obs-0007",
        "obs-0015"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          52
        ],
        "register": "ECX",
        "written_through": 1
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007",
        "obs-0015",
        "obs-0023"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
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
        "obs-0023"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0023"
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
      "at": "0x006a2f10",
      "count": 1,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "ESP"
    },
    {
      "at": "0x006a2f10",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0002",
      "index": 0,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "resolved": true,
      "size": 4,
      "trust": "untrusted_frame"
    },
    {
      "at": "0x006a2f10",
      "definite": true,
      "id": "obs-0003",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x006a2f14",
      "count": 3,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EBP",
      "reg": "EBP"
    },
    {
      "and_esp": null,
      "at": "0x006a2f14",
      "ebp_is_general_register": true,
      "fp": false,
      "id": "obs-0005",
      "index": 1,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": true,
      "push_ebp_at": 1,
      "raw": "PUSH EBP",
      "sub": null
    },
    {
      "at": "0x006a2f15",
      "count": 1,
      "first_use": 2,
      "first_write_index": 17,
      "id": "obs-0006",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV EBP,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x006a2f15",
      "definite": true,
      "id": "obs-0007",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV EBP,ECX",

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
  "count": 30,
  "instructions": [
    {
      "address": "006a2f10",
      "instruction": "MOV EAX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "006a2f14",
      "instruction": "PUSH EBP"
    },
    {
      "address": "006a2f15",
      "instruction": "MOV EBP,ECX"
    },
    {
      "address": "006a2f17",
      "instruction": "CMP EBP,EAX"
    },
    {
      "address": "006a2f19",
      "instruction": "JZ 0x006a2f50"
    },
    {
      "address": "006a2f1b",
      "instruction": "PUSH ESI"
    },
    {
      "address": "006a2f1c",
      "instruction": "MOV ESI,dword ptr [EAX + 0x18]"
    },
    {
      "address": "006a2f1f",
      "instruction": "PUSH EDI"
    },
    {
      "address": "006a2f20",
      "instruction": "MOV EDI,dword ptr [EAX + 0x1c]"
    },
    {
      "address": "006a2f23",
      "instruction": "CMP ESI,EDI"
    },
    {
      "address": "006a2f25",
      "instruction": "JZ 0x006a2f4b"
    },
    {
      "address": "006a2f27",
      "instruction": "PUSH EBX"
    },
    {
      "address": "006a2f28",
      "instruction": "LEA EBX,[EBP + 0x18]"
    },
    {
      "address": "006a2f2b",
      "instruction": "JMP 0x006a2f30"
    },
    {
      "address": "006a2f30",
      "instruction": "LEA EAX,[ESI + 0x4]"
    },
    {
      "address": "006a2f33",
      "instruction": "PUSH EAX"
    },
    {
      "address": "006a2f34",
      "instruction": "PUSH ESI"
    },
    {
      "address": "006a2f35",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "006a2f37",
      "instruction": "CALL 0x006a2d30"
    },
    {
      "address": "006a2f3c",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "006a2f3e",
      "instruction": "CALL 0x00542b80"
    },
    {
      "address": "006a2f43",
      "instruction": "ADD ESI,0x18"
    },
    {
      "address": "006a2f46",
      "instruction": "CMP ESI,EDI"
    },
    {
      "address": "006a2f48",
      "instruction": "JNZ 0x006a2f30"
    },
    {
      "address": "006a2f4a",
      "instruction": "POP EBX"
    },
    {
      "address": "006a2f4b",
      "instruction": "INC dword ptr [EBP + 0x34]"
    },
    {
      "address": "006a2f4e",
      "instruction": "POP EDI"
    },
    {
      "address": "006a2f4f",
      "instruction": "POP ESI"
    },
    {
      "address": "006a2f50",
      "instruction": "POP EBP"
    },
    {
      "address": "006a2f51",
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
  "original_bytes": 9974,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": 1,\n    \"ordinary_stack_arguments\": [\n      {\n        \"entry_offset\": \"entry_ESP+0x4\",\n        \"observed\": true,\n        \"ordinal\": 1,\n        \"read\": true,\n        \"read_at\": \"0x006a2f10 MOV EAX,dword ptr [ESP + 0x4]\",\n        \"role\": \"the source property list; its words at +0x18 and +0x1c are the iterated range\",\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      }\n    ],\n    \"ret_form\": \"RET 0x4\",\n    \"return_register\": \"EAX\",\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"callee\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x01408820\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-app-proplist-copyall-wave16\",\n      \"score\": 12,\n      \"symbol\": \"all_copy_from_properties_006a14d0\",\n      \"va\": \"0x006a14d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x01408820\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-dfw-006a1540\",\n      \"score\": 12,\n      \"symbol\": \"proplist_write_006a1540\",\n      \"va\": \"0x006a1540\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x01408820\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-property-clear-wave13\",\n      \"score\": 12,\n      \"symbol\": \"property_list_clear_006a2a80\",\n      \"va\": \"0x006a2a80\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x01408820\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-property-remove-006a2ef0\",\n      \"score\": 12,\n      \"symbol\": \"property_list_remove_property_006a2ef0\",\n      \"va\": \"0x006a2ef0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-direct-property-clear-wave14\",\n      \"score\": 8,\n      \"symbol\": \"direct_property_list_clear_006a2b20\",\n      \"va\": \"0x006a2b20\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01408820\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-PROPERTY-SAFE-WAVE9\",\n      \"score\": 6,\n      \"symbol\": \"property_list_copy_from_006a2a40\",\n      \"va\": \"0x006a2a40\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01408820\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-PROPERTY-SAFE-WAVE9\",\n      \"score\": 6,\n      \"symbol\": \"property_list_get_property_ids_006a3070\",\n      \"va\": \"0x006a3070\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01408820\"\n      ],\n      \"package\": \"wave6-resources\",\n      \"score\": 4,\n      \"symbol\": \"property_list_has_property_006a2470\",\n      \"va\": \"0x006a2470\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"app-lifecycle\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x006a2f3e\",\n        \"direction\": \"out\",\n        \"other\": \"0x00542b80\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006a2f37\",\n        \"direction\": \"out\",\n        \"other\": \"0x006a2d30\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0217\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"CONFIRMED\",\n  \"globals\": [\n    \"global:PASS\"\n  ],\n  \"integration_status\": null,\n  \"name\": \"App::PropertyList::AddPropertiesFrom\",\n  \"normalized_symbol\": \"App::PropertyList::AddPropertiesFrom\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"queue_candidate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"queued\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [],\n    \"validated\": 0\n  },\n  \"runtime_gated\": false,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": null,\n  \"services\": [],\n  \"source\": {\n    \"decomp\": \".spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__AddPropertiesFrom.c\",\n    \"file\": null,\n    \"files\": [\n      \".spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__AddPropertiesFrom.c\",\n      \"reconstruction/staging/pkg-app-proplist-wave13/app_property_list_add_from_006a2f10.cpp\",\n      \"reconstruction/staging/pkg-app-proplist-wave13/app_property_list_add_from_006a2f10.hpp\",\n      \"reconstruction/staging/pkg-app-proplist-wave13/app_property_list_add_from_006a2f10_model_test.cpp\"\n    ],\n    \"handoffs\": [],\n    \"metadata\": [\n      \"reconstruction/metadata/pkg-app-proplist-wave13/006a2f10.json\"\n    ],\n    \"provenance\": []\n  },\n  \"status\": \"queued\",\n  \"subsystem\": \"App\",\n  \"triage\": {\n    \"ca
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
  "body_end": "006a2f53",
  "body_span_bytes": 68,
  "body_start": "006a2f10",
  "callees": [
    "FUN_00542b80",
    "FUN_006a2d30"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "006a2f10",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "App::PropertyList::AddPropertiesFrom",
  "namespace": "App",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 2,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "PropertyList *"
    },
    {
      "name": "pOther",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "PropertyList *"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "void",
  "return_type_resolved": true,
  "rva": "0x2a2f10",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "void App::PropertyList::AddPropertiesFrom(PropertyList * this, PropertyList * pOther)",
  "size_bytes": 68,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x006a2f10",
  "vtables": {
    "referenced_by_vtables": [
      "0x01408820"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "01408850"
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
  "global:PASS"
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__AddPropertiesFrom.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__AddPropertiesFrom.c",
    "reconstruction/staging/pkg-app-proplist-wave13/app_property_list_add_from_006a2f10.cpp",
    "reconstruction/staging/pkg-app-proplist-wave13/app_property_list_add_from_006a2f10.hpp",
    "reconstruction/staging/pkg-app-proplist-wave13/app_property_list_add_from_006a2f10_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-app-proplist-wave13/006a2f10.json"
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
  "status": "queued"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "void"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x01408820"
]
```

## Conflicts

```json
[]
```
