# Evidence 0x006a30c0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `5cddd069bb3c575ea72ab7a343190aa0f7adca391f70f6509f2a5701462e6dae`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "x86-32 thiscall with first explicit list receiver in ECX and caller cleanup",
  "return_semantics": "void",
  "return_type": "void",
  "stack_cleanup_bytes": 8,
  "stack_cleanup_owner": "caller"
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
    "ret_form": "RET 0x8",
    "return_register": "ST0",
    "return_semantics": "float_or_x87_in_ST0",
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
    "stack_cleanup_bytes": 8,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x8"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +24, so the listing is not one path"
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
  "content_sha256": "c39aa0784ec147811b387407b67aa3466e07eb2ef6f83ce303efd09cae156460",
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
    "ghidra_parameter_count": 3,
    "persisted": "no_information",
    "persisted_calling_convention": "x86-32 thiscall with first explicit list receiver in ECX and caller cleanup"
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
        "obs-0022",
        "obs-0028",
        "obs-0032"
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
        "obs-0003",
        "obs-0013"
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
        "obs-0009",
        "obs-0013",
        "obs-0018",
        "obs-0023"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          56
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0005",
        "obs-0009",
        "obs-0013",
        "obs-0017",
        "obs-0018",
        "obs-0022",
        "obs-0023",
        "obs-0028",
        "obs-0032"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0017",
        "obs-0022",
        "obs-0028",
        "obs-0032"
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
        "obs-0032"
      ],
      "claim": "the return value is carried in ST0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "ST0"
    }
  ],
  "observations": [
    {
      "at": "0x006a30c0",
      "count": 6,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x006a30c1",
      "count": 6,
      "first_use": 1,
      "first_write_index": null,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ESI,dword ptr [ESP + 0x8]",
      "reg": "ESP"
    },
    {
      "at": "0x006a30c1",
      "base": "ESP",
      "disp": 8,
      "id": "obs-0003",
      "index": 1,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV ESI,dword ptr [ESP + 0x8]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x006a30c1",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,dword ptr [ESP + 0x8]",
      "reg": "ESI",
      "write_kind": "mem_load"
    },
    {
      "at": "0x006a30c5",
      "count": 5,
      "first_use": 2,
      "first_write_index": 6,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_READ",
      "raw": "CMP ESI,dword ptr [ECX + 0x38]",
      "reg": "ECX"
    },
    {
      "at": "0x006a30ce",
      "id": "obs-0006",
      "index": 4,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x0067de30",
      "target": "0x0067de30"
    },
    {
      "at": "0x006a30d3",
      "count": 11,
      "first_use": 5,
      "first_write_index": 7,
      "id": "obs-0007",
      "index": 5,
      "kind": "REG_READ",
      "raw": "MOV EDX,dword ptr [EAX]",
      "reg": "EAX"
    },
    {
      "at": "0x006a30d3",
      "definite": true,
      "id": "obs-0008",
      "index": 5,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [EAX]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x006a30d5",
      "definite": true,
      "id": "obs-0009",
    
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "property_value_resolve_0041e920",
    "reconstructed": true,
    "va": "0x0041e920"
  },
  {
    "name": "App::PropertyList::SetProperty",
    "reconstructed": false,
    "va": "0x006a2e20"
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
  "count": 58,
  "instructions": [
    {
      "address": "006a30c0",
      "instruction": "PUSH ESI"
    },
    {
      "address": "006a30c1",
      "instruction": "MOV ESI,dword ptr [ESP + 0x8]"
    },
    {
      "address": "006a30c5",
      "instruction": "CMP ESI,dword ptr [ECX + 0x38]"
    },
    {
      "address": "006a30c8",
      "instruction": "JNC 0x006a315c"
    },
    {
      "address": "006a30ce",
      "instruction": "CALL 0x0067de30"
    },
    {
      "address": "006a30d3",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "006a30d5",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "006a30d7",
      "instruction": "MOV EAX,dword ptr [EDX + 0x50]"
    },
    {
      "address": "006a30da",
      "instruction": "PUSH ESI"
    },
    {
      "address": "006a30db",
      "instruction": "CALL EAX"
    },
    {
      "address": "006a30dd",
      "instruction": "MOVZX ECX,word ptr [EAX + 0x12]"
    },
    {
      "address": "006a30e1",
      "instruction": "MOV DL,0x10"
    },
    {
      "address": "006a30e3",
      "instruction": "CMP CX,0x1"
    },
    {
      "address": "006a30e7",
      "instruction": "JNZ 0x006a310b"
    },
    {
      "address": "006a30e9",
      "instruction": "TEST byte ptr [EAX + 0x10],DL"
    },
    {
      "address": "006a30ec",
      "instruction": "JNZ 0x006a310b"
    },
    {
      "address": "006a30ee",
      "instruction": "MOV ECX,dword ptr [ESP + 0xc]"
    },
    {
      "address": "006a30f2",
      "instruction": "CALL 0x0041e920"
    },
    {
      "address": "006a30f7",
      "instruction": "MOVZX ECX,byte ptr [EAX]"
    },
    {
      "address": "006a30fa",
      "instruction": "PUSH ECX"
    },
    {
      "address": "006a30fb",
      "instruction": "MOV ECX,dword ptr [0x015fd918]"
    },
    {
      "address": "006a3101",
      "instruction": "PUSH ESI"
    },
    {
      "address": "006a3102",
      "instruction": "CALL 0x006a17e0"
    },
    {
      "address": "006a3107",
      "instruction": "POP ESI"
    },
    {
      "address": "006a3108",
      "instruction": "RET 0x8"
    },
    {
      "address": "006a310b",
      "instruction": "CMP CX,0x9"
    },
    {
      "address": "006a310f",
      "instruction": "JNZ 0x006a3132"
    },
    {
      "address": "006a3111",
      "instruction": "TEST byte ptr [EAX + 0x10],DL"
    },
    {
      "address": "006a3114",
      "instruction": "JNZ 0x006a3132"
    },
    {
      "address": "006a3116",
      "instruction": "MOV ECX,dword ptr [ESP + 0xc]"
    },
    {
      "address": "006a311a",
      "instruction": "CALL 0x0041e990"
    },
    {
      "address": "006a311f",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "006a3121",
      "instruction": "MOV ECX,dword ptr [0x015fd918]"
    },
    {
      "address": "006a3127",
      "instruction": "PUSH EDX"
    },
    {
      "address": "006a3128",
      "instruction": "PUSH ESI"
    },
    {
      "address": "006a3129",
      "instruction": "CALL 0x006a1880"
    },
    {
      "address": "006a312e",
      "instruction": "POP ESI"
    },
    {
      "address": "006a312f",
      "instruction": "RET 0x8"
    },
    {
      "address": "006a3132",
      "instruction": "CMP CX,0xd"
    },
    {
      "address": "006a3136",
      "instruction": "JNZ 0x006a3167"
    },
    {
      "address": "006a3138",
      "instruction": "TEST byte ptr [EAX + 0x10],DL"
    },
    {
      "address": "006a313b",
      "instruction": "JNZ 0x006a3167"
    },
    {
      "address": "006a313d",
      "instruction": "MOV ECX,dword ptr [ESP + 0xc]"
    },
    {
      "address": "006a3141",
      "instruction": "CALL 0x0041ea70"
    },
    {
      "address": "006a3146",
      "instruction": "FLD float ptr [EAX]"
    },
    {
      "address": "006a3148",
      "instruction": "PUSH ECX"
    },
    {
      "address": "006a3149",
      "instruction": "MOV ECX,dword ptr [0x015fd918]"
    },
    {
      "address": "006a314f",
      "instruction": "FSTP float ptr [ESP]"
    },
    {
      "address": "006a3152",
      "instruction": "PUSH ESI"
    },
    {
      "address": "006a3153",
      "instruction": "CALL 0x006a1910"
    },
    {
      "address": "006a3158",
      "instruction": "POP ESI"
    },
    {
      "address": "006a3159",
      "instruction": "RET 0x8"
    },
    {
      "address": "006a315c",
      "instruction": "MOV EAX,dword ptr [ESP + 0xc]"
    },
    {
      "address": "006a3160",
      "instruction": "PUSH EAX"
    },
    {
      "address": "006a3161",
      "instruction": "PUSH ESI"
    },
    {
      "address": "006a3162",
      "instruction": "CALL 0x006a2e20"
    },
    {
      "address": "006a3167",
      "instruction": "POP ESI"
    },
    {
      "address": "006a3168",
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
  "original_bytes": 9855,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"x86-32 thiscall with first explicit list receiver in ECX and caller cleanup\",\n    \"return_semantics\": \"void\",\n    \"return_type\": \"void\",\n    \"stack_cleanup_bytes\": 8,\n    \"stack_cleanup_owner\": \"caller\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_direct_property_wave6::OpaqueBaseObject,openspore::reconstruction::pkg_direct_property_wave6::OpaqueList,openspore::reconstruction::pkg_direct_property_wave6::OpaqueMap,openspore::reconstruction::pkg_direct_property_wave6::OpaqueMapEntry\",\n        \"shared_vtable:vtable:0x01408870\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-DIRECT-PROPERTY-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"opaque_list_has_property_006a27d0\",\n      \"va\": \"0x006a27d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_direct_property_wave6::OpaqueBaseObject,openspore::reconstruction::pkg_direct_property_wave6::OpaqueList,openspore::reconstruction::pkg_direct_property_wave6::OpaqueMap,openspore::reconstruction::pkg_direct_property_wave6::OpaqueMapEntry\",\n        \"shared_vtable:vtable:0x01408870\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-DIRECT-PROPERTY-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"opaque_list_get_property_object_006a2800\",\n      \"va\": \"0x006a2800\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_direct_property_wave6::OpaqueBaseObject,openspore::reconstruction::pkg_direct_property_wave6::OpaqueList,openspore::reconstruction::pkg_direct_property_wave6::OpaqueMap,openspore::reconstruction::pkg_direct_property_wave6::OpaqueMapEntry\",\n        \"shared_vtable:vtable:0x01408870\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-DIRECT-PROPERTY-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"opaque_list_get_property_006a28c0\",\n      \"va\": \"0x006a28c0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_direct_property_wave6::OpaqueBaseObject,openspore::reconstruction::pkg_direct_property_wave6::OpaqueList,openspore::reconstruction::pkg_direct_property_wave6::OpaqueMap,openspore::reconstruction::pkg_direct_property_wave6::OpaqueMapEntry\",\n        \"shared_vtable:vtable:0x01408870\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-DIRECT-PROPERTY-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"opaque_list_get_property_ids_006a3180\",\n      \"va\": \"0x006a3180\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01408870\"\n      ],\n      \"package\": \"pkg-app-proplist-copyall-wave16\",\n      \"score\": 4,\n      \"symbol\": \"all_copy_from_properties_006a14d0\",\n      \"va\": \"0x006a14d0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01408870\"\n      ],\n      \"package\": \"PKG-PROPERTY-SAFE-WAVE9\",\n      \"score\": 4,\n      \"symbol\": \"direct_property_list_add_properties_from_006a1600\",\n      \"va\": \"0x006a1600\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01408870\"\n      ],\n      \"package\": \"PKG-PROPERTY-SAFE-WAVE9\",\n      \"score\": 4,\n      \"symbol\": \"direct_property_list_get_property_alt_006a1e50\",\n      \"va\": \"0x006a1e50\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01408870\"\n      ],\n      \"package\": \"pkg-direct-property-clear-wave14\",\n      \"score\": 4,\n      \"symbol\": \"direct_property_list_clear_006a2b20\",\n      \"va\": \"0x006a2b20\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Reviewed static mechanics and x86-32 ABI are preserved; opaque runtime ports and ownership remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": null,\n  \"cluster\": \"app-lifecycle\",\n  \"confidence\": 0.9,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"property_value_resolve_0041e920\",\n        \"reconstructed\": true,\n        \"va\": \"0x0041e920\"\n      },\n      {\n        \"name\": \"App::PropertyList::SetProperty\",\n        \"reconstructed\": false,\n        \"va\": \"0x006a2e20\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x006a30f2\",\n        \"direction\": \"out\",\n        \"other\": \"0x0041e920\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006a311a\",\n        \"direction\": \"out\",\n        \"other\": \"0x0041e990\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006a3141\",\n        \"direction\": \"out\",\n        \"other\": \"0x0041ea70\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006a30ce\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067de30\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006a3102\",\n        \"direction\": \"out\",\n        \"other\": \"0x006a17e0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006a3129\",\n        \"direction\": \"out\",\n        \"other\": \"0x006a1880\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006a3153\",\n        \"direc
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
  "body_end": "006a316a",
  "body_span_bytes": 171,
  "body_start": "006a30c0",
  "callees": [
    "FUN_0041e990",
    "App::PropertyList::SetProperty",
    "App::DirectPropertyList::SetFloat",
    "App::DirectPropertyList::SetBool",
    "FUN_0041ea70",
    "FUN_0041e920",
    "FUN_0067de30",
    "App::DirectPropertyList::SetInt"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "006a30c0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "App::DirectPropertyList::SetProperty",
  "namespace": "App",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 3,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "DirectPropertyList *"
    },
    {
      "name": "propertyID",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "uint32_t"
    },
    {
      "name": "pValue",
      "ordinal": 2,
      "storage": "Stack[0xc]:4",
      "type": "Property *"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "void",
  "return_type_resolved": true,
  "rva": "0x2a30c0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "void App::DirectPropertyList::SetProperty(DirectPropertyList * this, uint32_t propertyID, Property * pValue)",
  "size_bytes": 171,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x006a30c0",
  "vtables": {
    "referenced_by_vtables": [
      "0x01408870"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "01408884"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__DirectPropertyList__SetProperty.c",
  "file": "src/reconstruction/pkg_direct_property_wave6/direct_property_wave6.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__DirectPropertyList__SetProperty.c",
    "src/reconstruction/pkg_direct_property_wave6/direct_property_wave6.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-direct-property-wave6/006a30c0.json"
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
    "property service, type conversion, base insertion, and fast-list runtime ownership remain gated",
    "runtime validation not run"
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
  "openspore::reconstruction::pkg_direct_property_wave6::OpaqueBaseObject",
  "openspore::reconstruction::pkg_direct_property_wave6::OpaqueList",
  "openspore::reconstruction::pkg_direct_property_wave6::OpaqueMap",
  "openspore::reconstruction::pkg_direct_property_wave6::OpaqueMapEntry",
  "openspore::reconstruction::pkg_direct_property_wave6::OpaqueProperty",
  "openspore::reconstruction::pkg_direct_property_wave6::OpaquePropertyService",
  "openspore::reconstruction::pkg_direct_property_wave6::OpaqueWordVector",
  "void"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x01408870"
]
```

## Conflicts

```json
[]
```
