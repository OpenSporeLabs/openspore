# Evidence 0x006a1510

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `9338b2c1437f9092b37108d674b46c94054d34cbd8d671133903f1ad12d20f4c`

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
  "ordinary_stack_argument_slots": [
    "entry_ESP+0x4"
  ],
  "receiver_register": "ECX",
  "ret_form": "RET 0x4",
  "return_observation": "0x006a152f CALL EAX is the final EAX write; 0x006a1531 POP EDI, 0x006a1532 POP ESI and 0x006a1533 RET 0x4 follow without touching it. The reconstructed body returns the value of the second transfer, which is the only reading consistent with the listing. Ghidra's live record types the same function void (ghidra_function.return_type, return_type_resolved true); that is a decompiler judgement, not a machine ABI record, and the two are reported side by side rather than merged.",
  "return_register": "EAX",
  "return_semantics": "unclassified_in_EAX -- the machine-derived record classes the EAX left behind as aggregate_unknown with type null; the last write to EAX is the result of the register-indirect CALL at 0x006a152f and the body applies no further operation to it",
  "return_type": "unclassified_in_EAX",
  "return_width_bytes": 4,
  "saved_registers": [
    "EDI",
    "ESI"
  ],
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "callee",
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
    "flow_not_modelled: the linear ESP walk ends at +8, so the listing is not one path"
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
  "content_sha256": "afd0d4c4d01aa5108d5c8753939086ada0de0296552e1a43c848be38b9598c6c",
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
    "indirect_calls": 2,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0017"
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
        "obs-0007",
        "obs-0008",
        "obs-0013"
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
        "obs-0007",
        "obs-0008",
        "obs-0013",
        "obs-0017"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0017"
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
        "obs-0017"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0017"
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
      "at": "0x006a1510",
      "count": 4,
      "first_use": 0,
      "first_write_index": 4,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x006a1511",
      "count": 3,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x006a1512",
      "count": 1,
      "first_use": 2,
      "first_write_index": null,
      "id": "obs-0003",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV EDI,dword ptr [ESP + 0xc]",
      "reg": "ESP"
    },
    {
      "at": "0x006a1512",
      "base": "ESP",
      "disp": 12,
      "id": "obs-0004",
      "index": 2,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EDI,dword ptr [ESP + 0xc]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x006a1512",
      "definite": true,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV EDI,dword ptr [ESP + 0xc]",
      "reg": "EDI",
      "write_kind": "mem_load"
    },
    {
      "at": "0x006a1516",
      "definite": true,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [EDI + 0x30]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x006a1519",
      "count": 1,
      "first_use": 4,
      "first_write_index": 14,
      "id": "obs-0007",
      "index": 4,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x006a1519",
      "definite": true,
      "id": "obs-0008",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x006a151f",
      "definite": true,
      "id": "obs-0009",
      "index": 7,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [ESI]",
      "reg": "EDX",
      "write_kind"
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
      "address": "006a1510",
      "instruction": "PUSH ESI"
    },
    {
      "address": "006a1511",
      "instruction": "PUSH EDI"
    },
    {
      "address": "006a1512",
      "instruction": "MOV EDI,dword ptr [ESP + 0xc]"
    },
    {
      "address": "006a1516",
      "instruction": "MOV EAX,dword ptr [EDI + 0x30]"
    },
    {
      "address": "006a1519",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "006a151b",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "006a151d",
      "instruction": "JZ 0x006a1527"
    },
    {
      "address": "006a151f",
      "instruction": "MOV EDX,dword ptr [ESI]"
    },
    {
      "address": "006a1521",
      "instruction": "PUSH EAX"
    },
    {
      "address": "006a1522",
      "instruction": "MOV EAX,dword ptr [EDX + 0x38]"
    },
    {
      "address": "006a1525",
      "instruction": "CALL EAX"
    },
    {
      "address": "006a1527",
      "instruction": "MOV EDX,dword ptr [ESI]"
    },
    {
      "address": "006a1529",
      "instruction": "MOV EAX,dword ptr [EDX + 0x30]"
    },
    {
      "address": "006a152c",
      "instruction": "PUSH EDI"
    },
    {
      "address": "006a152d",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "006a152f",
      "instruction": "CALL EAX"
    },
    {
      "address": "006a1531",
      "instruction": "POP EDI"
    },
    {
      "address": "006a1532",
      "instruction": "POP ESI"
    },
    {
      "address": "006a1533",
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
  "original_bytes": 9087,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": [\n      \"entry_ESP+0x4\"\n    ],\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET 0x4\",\n    \"return_observation\": \"0x006a152f CALL EAX is the final EAX write; 0x006a1531 POP EDI, 0x006a1532 POP ESI and 0x006a1533 RET 0x4 follow without touching it. The reconstructed body returns the value of the second transfer, which is the only reading consistent with the listing. Ghidra's live record types the same function void (ghidra_function.return_type, return_type_resolved true); that is a decompiler judgement, not a machine ABI record, and the two are reported side by side rather than merged.\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"unclassified_in_EAX -- the machine-derived record classes the EAX left behind as aggregate_unknown with type null; the last write to EAX is the result of the register-indirect CALL at 0x006a152f and the body applies no further operation to it\",\n    \"return_type\": \"unclassified_in_EAX\",\n    \"return_width_bytes\": 4,\n    \"saved_registers\": [\n      \"EDI\",\n      \"ESI\"\n    ],\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"RET 0x4\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x01408820,vtable:0x01408870\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-app-proplist-copyall-wave16\",\n      \"score\": 12,\n      \"symbol\": \"all_copy_from_properties_006a14d0\",\n      \"va\": \"0x006a14d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x01408820\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-dfw-006a1540\",\n      \"score\": 12,\n      \"symbol\": \"proplist_write_006a1540\",\n      \"va\": \"0x006a1540\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x01408820\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-property-clear-wave13\",\n      \"score\": 12,\n      \"symbol\": \"property_list_clear_006a2a80\",\n      \"va\": \"0x006a2a80\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x01408870\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-direct-property-clear-wave14\",\n      \"score\": 12,\n      \"symbol\": \"direct_property_list_clear_006a2b20\",\n      \"va\": \"0x006a2b20\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x01408820,vtable:0x01408870\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-property-remove-006a2ef0\",\n      \"score\": 12,\n      \"symbol\": \"property_list_remove_property_006a2ef0\",\n      \"va\": \"0x006a2ef0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01408870\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-PROPERTY-SAFE-WAVE9\",\n      \"score\": 6,\n      \"symbol\": \"direct_property_list_add_properties_from_006a1600\",\n      \"va\": \"0x006a1600\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01408870\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-PROPERTY-SAFE-WAVE9\",\n      \"score\": 6,\n      \"symbol\": \"direct_property_list_get_property_alt_006a1e50\",\n      \"va\": \"0x006a1e50\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01408820\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-PROPERTY-SAFE-WAVE9\",\n      \"score\": 6,\n      \"symbol\": \"property_list_copy_from_006a2a40\",\n      \"va\": \"0x006a2a40\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"app-lifecycle\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0199\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"CONFIRMED\",\n  \"globals\": [],\n  \"integration_status\": null,\n  \"name\": \"App::PropertyList::AddAllPropertiesFrom\",\n  \"normalized_symbol\": \"App::PropertyList::AddAllPropertiesFrom\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"queue_candidate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"queued\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [],\n    \"validated\": 0\n  },\n  \"runtime_gated\": false,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": null,\n  \"services\": [],\n  \"source\": {\n    \"decomp\": \".spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__AddAllPropertiesFrom.c\",\n    \"file\": null,\n    \"files\": [\n      \".spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__AddAllPropertiesFrom.c\",\n      \"reconstruction/staging/pkg-proplist-dispatch-wave14/app_property_list_add_all_properties_from_006a1510.cpp\",\n      \"reconstruction/staging/pkg-pro
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
  "body_end": "006a1535",
  "body_span_bytes": 38,
  "body_start": "006a1510",
  "callees": [],
  "callers": [],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "006a1510",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "App::PropertyList::AddAllPropertiesFrom",
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
  "rva": "0x2a1510",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "void App::PropertyList::AddAllPropertiesFrom(PropertyList * this, PropertyList * pOther)",
  "size_bytes": 38,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x006a1510",
  "vtables": {
    "referenced_by_vtables": [
      "0x01408820",
      "0x01408870"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 2,
  "xrefs": [
    {
      "from": "01408858"
    },
    {
      "from": "014088a8"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__AddAllPropertiesFrom.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__AddAllPropertiesFrom.c",
    "reconstruction/staging/pkg-proplist-dispatch-wave14/app_property_list_add_all_properties_from_006a1510.cpp",
    "reconstruction/staging/pkg-proplist-dispatch-wave14/app_property_list_add_all_properties_from_006a1510.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-proplist-dispatch-wave14/006a1510.json"
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
  "unclassified_in_EAX"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x01408820",
  "vtable:0x01408870"
]
```

## Conflicts

```json
[]
```
