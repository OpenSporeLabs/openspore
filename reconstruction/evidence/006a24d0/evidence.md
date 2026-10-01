# Evidence 0x006a24d0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `d564388736e129d972b595b20418e7f337bb0e5c11ecf8f7048be2ca5107e1e9`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "__thiscall observed",
  "hidden_this_register": "ECX",
  "hidden_this_type": "PropertyList*",
  "return_register": "EAX",
  "return_type": "Property*",
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "property_id",
      "position": 1,
      "type": "uint32_t",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 4,
  "termination": "RET 0x4 at 0x006a250c, 0x006a252a, and the parent tail path"
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
    "hidden_this": true,
    "hidden_this_register": "ECX",
    "ordinary_stack_argument_slots": [
      "entry_ESP+0x4",
      "entry_ESP+0xc"
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
      },
      {
        "entry_offset": "entry_ESP+0xc",
        "observed": true,
        "ordinal": 3,
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
    "return_semantics": "pointer_like_in_EAX",
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
      },
      {
        "entry_offset": "entry_ESP+0xc",
        "observed": true,
        "ordinal": 3,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "termination": "RET 0x4"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -16, so the listing is not one path",
    "ret_imm_below_highest_slot: ret 0x4 pops less than the highest read slot 0xc; everything above it belongs to the caller's frame",
    "slot_gaps_present: argument ordinal(s) below the highest read slot are never touched",
    "no_discriminator: the callee pop of 0x4 is not a whole number of dword stack arguments, so no convention follows from it"
  ],
  "cleanup": {
    "bytes": 4,
    "confidence": "UNKNOWN",
    "corroboration": "not_available",
    "evidence": "ret 0x4 but entry slot 0xc is read",
    "side": null
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "fbf7eaaeee63d1823708cad9027a39857edee2c9179db4a33fccff93460a01c6",
  "conventions": {
    "ambiguities": [],
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
    "ghidra_parameter_count": 2,
    "persisted": "no_information",
    "persisted_calling_convention": "__thiscall observed"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0017",
        "obs-0025"
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
        "obs-0017",
        "obs-0025"
      ],
      "claim": "cleanup side is undetermined: a slot above the popped area is read",
      "confidence": "UNKNOWN",
      "id": "C4",
      "value": {
        "bytes": 4,
        "side": null
      }
    },
    {
      "based_on": [
        "obs-0009",
        "obs-0012",
        "obs-0021"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 1,
        "observed_slots": 2,
        "total_bytes": 12
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0008",
        "obs-0009",
        "obs-0018"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          24,
          28,
          44,
          48
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0025"
      ],
      "claim": "the calling convention is unknown: the terminal pop is not a whole number of dword arguments",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0017",
        "obs-0025"
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
        "obs-0017",
        "obs-0025"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0017",
        "obs-0025"
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
      "at": "0x006a24d0",
      "count": 5,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x006a24d1",
      "count": 5,
      "first_use": 1,
      "first_write_index": 28,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x006a24d1",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x006a24d3",
      "count": 5,
      "first_use": 2,
      "first_write_index": 21,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOVZX EAX,byte ptr [ESI + 0x2c]",
      "reg": "EAX"
   
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
    "name": "opaque_list_get_property_object_006a2800",
    "reconstructed": true,
    "va": "0x006a2800"
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
  "count": 41,
  "instructions": [
    {
      "address": "006a24d0",
      "instruction": "PUSH ESI"
    },
    {
      "address": "006a24d1",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "006a24d3",
      "instruction": "MOVZX EAX,byte ptr [ESI + 0x2c]"
    },
    {
      "address": "006a24d7",
      "instruction": "MOV EDX,dword ptr [ESI + 0x18]"
    },
    {
      "address": "006a24da",
      "instruction": "PUSH EDI"
    },
    {
      "address": "006a24db",
      "instruction": "MOV EDI,dword ptr [ESI + 0x1c]"
    },
    {
      "address": "006a24de",
      "instruction": "PUSH EAX"
    },
    {
      "address": "006a24df",
      "instruction": "LEA ECX,[ESP + 0x10]"
    },
    {
      "address": "006a24e3",
      "instruction": "PUSH ECX"
    },
    {
      "address": "006a24e4",
      "instruction": "PUSH EDI"
    },
    {
      "address": "006a24e5",
      "instruction": "PUSH EDX"
    },
    {
      "address": "006a24e6",
      "instruction": "CALL 0x00612db0"
    },
    {
      "address": "006a24eb",
      "instruction": "MOV EDX,dword ptr [ESP + 0x1c]"
    },
    {
      "address": "006a24ef",
      "instruction": "ADD ESP,0x10"
    },
    {
      "address": "006a24f2",
      "instruction": "CMP EAX,EDI"
    },
    {
      "address": "006a24f4",
      "instruction": "JZ 0x006a2501"
    },
    {
      "address": "006a24f6",
      "instruction": "CMP EDX,dword ptr [EAX]"
    },
    {
      "address": "006a24f8",
      "instruction": "JC 0x006a2501"
    },
    {
      "address": "006a24fa",
      "instruction": "LEA ECX,[EAX + 0x18]"
    },
    {
      "address": "006a24fd",
      "instruction": "CMP EAX,ECX"
    },
    {
      "address": "006a24ff",
      "instruction": "JNZ 0x006a2503"
    },
    {
      "address": "006a2501",
      "instruction": "MOV EAX,EDI"
    },
    {
      "address": "006a2503",
      "instruction": "CMP EAX,EDI"
    },
    {
      "address": "006a2505",
      "instruction": "JZ 0x006a250f"
    },
    {
      "address": "006a2507",
      "instruction": "POP EDI"
    },
    {
      "address": "006a2508",
      "instruction": "ADD EAX,0x4"
    },
    {
      "address": "006a250b",
      "instruction": "POP ESI"
    },
    {
      "address": "006a250c",
      "instruction": "RET 0x4"
    },
    {
      "address": "006a250f",
      "instruction": "MOV ECX,dword ptr [ESI + 0x30]"
    },
    {
      "address": "006a2512",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "006a2514",
      "instruction": "JZ 0x006a2523"
    },
    {
      "address": "006a2516",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "006a2518",
      "instruction": "POP EDI"
    },
    {
      "address": "006a2519",
      "instruction": "POP ESI"
    },
    {
      "address": "006a251a",
      "instruction": "MOV dword ptr [ESP + 0x4],EDX"
    },
    {
      "address": "006a251e",
      "instruction": "MOV EDX,dword ptr [EAX + 0x28]"
    },
    {
      "address": "006a2521",
      "instruction": "JMP EDX"
    },
    {
      "address": "006a2523",
      "instruction": "POP EDI"
    },
    {
      "address": "006a2524",
      "instruction": "MOV EAX,0x16027d0"
    },
    {
      "address": "006a2529",
      "instruction": "POP ESI"
    },
    {
      "address": "006a252a",
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
  "original_bytes": 7872,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"__thiscall observed\",\n    \"hidden_this_register\": \"ECX\",\n    \"hidden_this_type\": \"PropertyList*\",\n    \"return_register\": \"EAX\",\n    \"return_type\": \"Property*\",\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"name\": \"property_id\",\n        \"position\": 1,\n        \"type\": \"uint32_t\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 4,\n    \"termination\": \"RET 0x4 at 0x006a250c, 0x006a252a, and the parent tail path\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:DATA,PropertyList,PropertyList*,PropertyMap\",\n        \"shared_vtable:vtable:0x01408820\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"wave6-resources\",\n      \"score\": 34,\n      \"symbol\": \"property_list_has_property_006a2470\",\n      \"va\": \"0x006a2470\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:PropertyList\",\n        \"shared_vtable:vtable:0x01408820\"\n      ],\n      \"package\": \"PKG-PROPERTY-SAFE-WAVE9\",\n      \"score\": 12,\n      \"symbol\": \"property_list_copy_from_006a2a40\",\n      \"va\": \"0x006a2a40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:PropertyList\",\n        \"shared_vtable:vtable:0x01408820\"\n      ],\n      \"package\": \"PKG-PROPERTY-SAFE-WAVE9\",\n      \"score\": 12,\n      \"symbol\": \"property_list_get_property_ids_006a3070\",\n      \"va\": \"0x006a3070\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:PropertyList\",\n        \"shared_vtable:vtable:0x01408820\"\n      ],\n      \"package\": \"pkg-property-clear-wave13\",\n      \"score\": 7,\n      \"symbol\": \"property_list_clear_006a2a80\",\n      \"va\": \"0x006a2a80\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DATA,UNCONDITIONAL_CALL\"\n      ],\n      \"package\": \"PKG-18-UI-SCRIPTING\",\n      \"score\": 6,\n      \"symbol\": \"FUN_005bf9d0\",\n      \"va\": \"0x005bf9d0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DATA,UNCONDITIONAL_CALL\"\n      ],\n      \"package\": \"PKG-18-UI-SCRIPTING\",\n      \"score\": 6,\n      \"symbol\": \"FUN_005c0100\",\n      \"va\": \"0x005c0100\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DATA,UNCONDITIONAL_CALL\"\n      ],\n      \"package\": \"PKG-18-UI-SCRIPTING\",\n      \"score\": 6,\n      \"symbol\": \"FUN_005c0380\",\n      \"va\": \"0x005c0380\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:Property,PropertyMapEntry\"\n      ],\n      \"package\": \"PKG-20-PROPERTY-ADAPTER\",\n      \"score\": 6,\n      \"symbol\": \"app_direct_property_list_get_direct_bool_006a25a0\",\n      \"va\": \"0x006a25a0\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"The lower-bound, entry+0x04 return, parent slot, and no-parent sentinel address are exact; sentinel contents, parent subtype, and returned property lifetime remain unresolved.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"pass_after_repair\",\n  \"blocked\": false,\n  \"blockers\": [\n    \"No original runtime trace validates returned property lifetime or sentinel use.\",\n    \"The parent virtual dispatch and sentinel object contents are outside the selected body.\"\n  ],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"PropertyList\",\n  \"cluster\": \"app-lifecycle\",\n  \"confidence\": 0.94,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": \"opaque_list_get_property_object_006a2800\",\n        \"reconstructed\": true,\n        \"va\": \"0x006a2800\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x006a28ab\",\n        \"direction\": \"in\",\n        \"other\": \"0x006a2800\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006a24e6\",\n        \"direction\": \"out\",\n        \"other\": \"0x00612db0\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 1,\n    \"fan_out\": 0,\n    \"manifest_callees\": [\n      \"0x00612db0\",\n      \"parent vtable +0x28\"\n    ],\n    \"manifest_callers\": [\n      \"0x006a2800\"\n    ],\n    \"nearby_reconstructed\": [\n      \"0x006a2800\"\n    ],\n    \"scc\": {\n      \"id\": \"scc-0205\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"OBSERVED\",\n  \"globals\": [],\n  \"integration_status\": \"integrated\",\n  \"name\": \"App::PropertyList::GetPropertyObject\",\n  \"normalized_symbol\": \"property_list_get_property_object_006a24d0\",\n  \"observed_mechanics\": [\n    \"read map at receiver+0x18 and mode at +0x2c\",\n    \"call lower-bound helper 0x00612db0\",\n    \"return entry+0x04 on exact key\",\n    \"dispatch parent vtable+0x28 on miss\",\n    \"return address 0x016027d0 when no parent exists\"\n  ],\n  \"ownership\": {\n    \"claimability\": \"do_not_claim\",\n    \"handoff_packages\": [\n      \"wave6-resources\"\n    ],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": \"wave6-resources\",\n    \"queue_state\": \"queued\"\n  },\n  \"package\": \"wave6-resources\",\n  \"reconstructed\": true,\n  \"review_status\": \"approved\",\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"gate-property-list-parent-dispatch-sentinel-and-lifetime\"\n    ],\n    \"validated\": 0\n  },\n  \"runtime_gated\": true,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": \"static_property_lookup_parent_dispatch_and_sentinel_ru
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
  "body_end": "006a252c",
  "body_span_bytes": 93,
  "body_start": "006a24d0",
  "callees": [
    "FUN_00612db0"
  ],
  "callers": [
    "App::DirectPropertyList::GetPropertyObject"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "006a24d0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "App::PropertyList::GetPropertyObject",
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
      "name": "propertyID",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "uint32_t"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "Property *",
  "return_type_resolved": true,
  "rva": "0x2a24d0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "Property * App::PropertyList::GetPropertyObject(PropertyList * this, uint32_t propertyID)",
  "size_bytes": 93,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x006a24d0",
  "vtables": {
    "referenced_by_vtables": [
      "0x01408820"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 2,
  "xrefs": [
    {
      "from": "01408848"
    },
    {
      "from": "006a28ab"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__GetPropertyObject.c",
  "file": "src/reconstruction/wave6_resources/property_list_variants.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__GetPropertyObject.c",
    "reconstruction/staging/wave6-resources/property_list_variants.cpp",
    "reconstruction/staging/wave6-resources/property_list_variants.hpp",
    "reconstruction/staging/wave6-resources/property_list_variants_model_test.cpp",
    "src/reconstruction/wave6_resources/property_list_variants.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/wave6-resources/006a24d0.json"
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
    "gate-property-list-parent-dispatch-sentinel-and-lifetime"
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
  "ObjectParentVtable",
  "Property",
  "Property*",
  "PropertyList",
  "PropertyList*",
  "PropertyMap",
  "PropertyMapEntry",
  "UNCONDITIONAL_CALL",
  "uint32_t"
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
