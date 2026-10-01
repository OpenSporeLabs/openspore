# Evidence 0x006a14d0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `079aa8b946650f4a7be5b12687a97d21cc959ed74ca450248b88de489e415a6f`

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
    "{'entry_offset': 'entry_ESP+0x4', 'observed': True, 'ordinal': 1, 'read': True, 'read_at': '0x006a14d2 MOV EDI,dword ptr [ESP + 0xc]', 'read_offset_note': 'the +0xc operand is entry_ESP+0x4 plus the 8 bytes pushed by 0x006a14d0 PUSH ESI and 0x006a14d1 PUSH EDI', 'role': 'the source property list, held in EDI and forwarded as the single stack word of the slot +0x38 dispatch at 0x006a14ff', 'sizes': [4], 'written': False}",
    "{'entry_offset': 'entry_ESP+0x4', 'observed': True, 'ordinal': 1, 'read': True, 'read_at': '0x006a14d2 MOV EDI,dword ptr [ESP + 0xc]', 'read_offset_note': 'the +0xc operand is entry_ESP+0x4 plus the 8 bytes pushed by 0x006a14d0 PUSH ESI and 0x006a14d1 PUSH EDI. Both citations are taken from the persisted abi record and were re-derived from the live listing, which agrees.', 'role': 'the source object. It is held in EDI, compared against the receiver at 0x006a14d8, and forwarded unchanged as the single stack word of the slot +0x38 dispatch at 0x006a14ff.', 'sizes': [4], 'written': False}"
  ],
  "receiver_register": "ECX",
  "ret_form": "RET 0x4",
  "return_register": "EAX",
  "return_type": "void",
  "saved_registers": [
    "EDI",
    "ESI"
  ],
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
  "content_sha256": "a743379230f7dda4c50612e1fbc313a886da3f0379566e2ef6633de5f4ac27a1",
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
    "indirect_calls": 3,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0018"
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
        "obs-0006",
        "obs-0007",
        "obs-0008",
        "obs-0009"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          0,
          48
        ],
        "register": "ECX",
        "written_through": 1
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007",
        "obs-0008",
        "obs-0009",
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
      "at": "0x006a14d0",
      "count": 7,
      "first_use": 0,
      "first_write_index": 3,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x006a14d1",
      "count": 2,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x006a14d2",
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
      "at": "0x006a14d2",
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
      "at": "0x006a14d2",
      "definite": true,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV EDI,dword ptr [ESP + 0xc]",
      "reg": "EDI",
      "write_kind": "mem_load"
    },
    {
      "at": "0x006a14d6",
      "count": 2,
      "first_use": 3,
      "first_write_index": 6,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x006a14d6",
      "definite": true,
      "id": "obs-0007",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x006a14dc",
      "definite": true,
      "id": "obs-0008",
      "index": 6,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [ESI + 0x30]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x006a14ea",
      "definite": true,
      "id": "obs-0009",
      "index": 10,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dw
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
  "count": 25,
  "instructions": [
    {
      "address": "006a14d0",
      "instruction": "PUSH ESI"
    },
    {
      "address": "006a14d1",
      "instruction": "PUSH EDI"
    },
    {
      "address": "006a14d2",
      "instruction": "MOV EDI,dword ptr [ESP + 0xc]"
    },
    {
      "address": "006a14d6",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "006a14d8",
      "instruction": "CMP ESI,EDI"
    },
    {
      "address": "006a14da",
      "instruction": "JZ 0x006a1504"
    },
    {
      "address": "006a14dc",
      "instruction": "MOV ECX,dword ptr [ESI + 0x30]"
    },
    {
      "address": "006a14df",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "006a14e1",
      "instruction": "JZ 0x006a14f1"
    },
    {
      "address": "006a14e3",
      "instruction": "MOV dword ptr [ESI + 0x30],0x0"
    },
    {
      "address": "006a14ea",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "006a14ec",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "006a14ef",
      "instruction": "CALL EDX"
    },
    {
      "address": "006a14f1",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "006a14f3",
      "instruction": "MOV EDX,dword ptr [EAX + 0x48]"
    },
    {
      "address": "006a14f6",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "006a14f8",
      "instruction": "CALL EDX"
    },
    {
      "address": "006a14fa",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "006a14fc",
      "instruction": "MOV EDX,dword ptr [EAX + 0x38]"
    },
    {
      "address": "006a14ff",
      "instruction": "PUSH EDI"
    },
    {
      "address": "006a1500",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "006a1502",
      "instruction": "CALL EDX"
    },
    {
      "address": "006a1504",
      "instruction": "POP EDI"
    },
    {
      "address": "006a1505",
      "instruction": "POP ESI"
    },
    {
      "address": "006a1506",
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
  "original_bytes": 13612,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": 1,\n    \"ordinary_stack_arguments\": [\n      \"{'entry_offset': 'entry_ESP+0x4', 'observed': True, 'ordinal': 1, 'read': True, 'read_at': '0x006a14d2 MOV EDI,dword ptr [ESP + 0xc]', 'read_offset_note': 'the +0xc operand is entry_ESP+0x4 plus the 8 bytes pushed by 0x006a14d0 PUSH ESI and 0x006a14d1 PUSH EDI', 'role': 'the source property list, held in EDI and forwarded as the single stack word of the slot +0x38 dispatch at 0x006a14ff', 'sizes': [4], 'written': False}\",\n      \"{'entry_offset': 'entry_ESP+0x4', 'observed': True, 'ordinal': 1, 'read': True, 'read_at': '0x006a14d2 MOV EDI,dword ptr [ESP + 0xc]', 'read_offset_note': 'the +0xc operand is entry_ESP+0x4 plus the 8 bytes pushed by 0x006a14d0 PUSH ESI and 0x006a14d1 PUSH EDI. Both citations are taken from the persisted abi record and were re-derived from the live listing, which agrees.', 'role': 'the source object. It is held in EDI, compared against the receiver at 0x006a14d8, and forwarded unchanged as the single stack word of the slot +0x38 dispatch at 0x006a14ff.', 'sizes': [4], 'written': False}\"\n    ],\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET 0x4\",\n    \"return_register\": \"EAX\",\n    \"return_type\": \"void\",\n    \"saved_registers\": [\n      \"EDI\",\n      \"ESI\"\n    ],\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"callee\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x01408820\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-dfw-006a1540\",\n      \"score\": 12,\n      \"symbol\": \"proplist_write_006a1540\",\n      \"va\": \"0x006a1540\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x01408820\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-property-clear-wave13\",\n      \"score\": 12,\n      \"symbol\": \"property_list_clear_006a2a80\",\n      \"va\": \"0x006a2a80\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x01408870\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-direct-property-clear-wave14\",\n      \"score\": 12,\n      \"symbol\": \"direct_property_list_clear_006a2b20\",\n      \"va\": \"0x006a2b20\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x01408820,vtable:0x01408870\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-property-remove-006a2ef0\",\n      \"score\": 12,\n      \"symbol\": \"property_list_remove_property_006a2ef0\",\n      \"va\": \"0x006a2ef0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01408870\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-PROPERTY-SAFE-WAVE9\",\n      \"score\": 6,\n      \"symbol\": \"direct_property_list_add_properties_from_006a1600\",\n      \"va\": \"0x006a1600\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01408870\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-PROPERTY-SAFE-WAVE9\",\n      \"score\": 6,\n      \"symbol\": \"direct_property_list_get_property_alt_006a1e50\",\n      \"va\": \"0x006a1e50\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01408820\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-PROPERTY-SAFE-WAVE9\",\n      \"score\": 6,\n      \"symbol\": \"property_list_copy_from_006a2a40\",\n      \"va\": \"0x006a2a40\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01408820\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-PROPERTY-SAFE-WAVE9\",\n      \"score\": 6,\n      \"symbol\": \"property_list_get_property_ids_006a3070\",\n      \"va\": \"0x006a3070\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": null,\n  \"cluster\": \"app-lifecycle\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0198\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"CONFIRMED\",\n  \"globals\": [\n    \"global:PASS\"\n  ],\n  \"integration_status\": \"integrated\",\n  \"name\": \"App::PropertyList::CopyAllPropertiesFrom\",\n  \"normalized_symbol\": \"all_copy_from_properties_006a14d0\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"do_not_claim\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": \"pkg-app-proplist-copyall-wave16\",\n    \"queue_state\": \"queued\"\n  },\n  \"package\": \"pkg-app-proplist-copyall-wave16\",\n  \"reconstructed\": true,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [],\n    \"validated\": 0\n  },\n  \"runtime_gated\": false,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": null,\n  \"services\": [],\n  \"source\": {\n    \"decomp\": \".spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__CopyAllPropertiesFrom.c\",\n    \"file\": \"src/reconstruction/pkg_app_proplist_copyall_wa
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
  "body_end": "006a1508",
  "body_span_bytes": 57,
  "body_start": "006a14d0",
  "callees": [],
  "callers": [],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "006a14d0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "App::PropertyList::CopyAllPropertiesFrom",
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
  "rva": "0x2a14d0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "void App::PropertyList::CopyAllPropertiesFrom(PropertyList * this, PropertyList * pOther)",
  "size_bytes": 57,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x006a14d0",
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
      "from": "01408854"
    },
    {
      "from": "014088a4"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__CopyAllPropertiesFrom.c",
  "file": "src/reconstruction/pkg_app_proplist_copyall_wave16/all_copy_from_properties_006a14d0.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__CopyAllPropertiesFrom.c",
    "reconstruction/staging/pkg-app-proplist-copyall-wave16/all_copy_from_properties_006a14d0.cpp",
    "reconstruction/staging/pkg-app-proplist-copyall-wave16/all_copy_from_properties_006a14d0.hpp",
    "reconstruction/staging/pkg-app-proplist-copyall-wave16/all_copy_from_properties_006a14d0_model_test.cpp",
    "reconstruction/staging/pkg-dfw-006a14d0/dfw_006a14d0.cpp",
    "reconstruction/staging/pkg-dfw-006a14d0/dfw_006a14d0_model_test.cpp",
    "reconstruction/staging/pkg-dfw-006a14d0/dfw_006a14d0_types.hpp",
    "src/reconstruction/pkg_app_proplist_copyall_wave16/all_copy_from_properties_006a14d0.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-app-proplist-copyall-wave16/006a14d0.json",
    "reconstruction/metadata/pkg-dfw-006a14d0/006a14d0.json"
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
  "status": "reconstructed"
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
  "vtable:0x00432b50",
  "vtable:0x006a14d0",
  "vtable:0x01408820",
  "vtable:0x01408870",
  "vtable:0x014088bc"
]
```

## Conflicts

```json
[]
```
