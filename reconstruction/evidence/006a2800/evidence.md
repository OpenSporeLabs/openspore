# Evidence 0x006a2800

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `5b5b3c79c7e60689091af18188e9f606a3b11a224ceb2124ac4ef40345e150f3`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "x86-32 thiscall with first explicit list receiver in ECX and caller cleanup",
  "return_semantics": "OpaqueProperty* in EAX",
  "return_type": "OpaqueProperty*",
  "stack_cleanup_bytes": 4,
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
    "return_register": "XMM0",
    "return_semantics": "float_or_x87_in_XMM0",
    "saved_registers": [
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
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "termination": "RET 0x4"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -8, so the listing is not one path",
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
  "content_sha256": "5ca170654b7262fdc528b3515f3a0694f28a5c6e853c613570c8e9064762c66b",
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
        "obs-0023",
        "obs-0030",
        "obs-0039",
        "obs-0043"
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
        "obs-0023",
        "obs-0030",
        "obs-0039",
        "obs-0043"
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
        "obs-0003",
        "obs-0024",
        "obs-0025",
        "obs-0032",
        "obs-0034"
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
        "obs-0006",
        "obs-0007",
        "obs-0012",
        "obs-0031"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          56,
          60,
          80,
          82
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0043"
      ],
      "claim": "the calling convention is unknown: the terminal pop is not a whole number of dword arguments",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0023",
        "obs-0030",
        "obs-0039",
        "obs-0043"
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
        "obs-0043"
      ],
      "claim": "the return value is carried in XMM0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "XMM0"
    }
  ],
  "observations": [
    {
      "at": "0x006a2800",
      "count": 6,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x006a2801",
      "count": 7,
      "first_use": 1,
      "first_write_index": null,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EBX,dword ptr [ESP + 0x8]",
      "reg": "ESP"
    },
    {
      "at": "0x006a2801",
      "base": "ESP",
      "disp": 8,
      "id": "obs-0003",
      "index": 1,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EBX,dword ptr [ESP + 0x8]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x006a2801",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EBX,dword ptr [ESP + 0x8]",
      "reg": "EBX",
      "write_
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "property_record_assign_scalar_00428060",
    "reconstructed": true,
    "va": "0x00428060"
  },
  {
    "name": "property_list_get_property_object_006a24d0",
    "reconstructed": true,
    "va": "0x006a24d0"
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
  "count": 68,
  "instructions": [
    {
      "address": "006a2800",
      "instruction": "PUSH EBX"
    },
    {
      "address": "006a2801",
      "instruction": "MOV EBX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "006a2805",
      "instruction": "PUSH ESI"
    },
    {
      "address": "006a2806",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "006a2808",
      "instruction": "CMP EBX,dword ptr [ESI + 0x38]"
    },
    {
      "address": "006a280b",
      "instruction": "JNC 0x006a28aa"
    },
    {
      "address": "006a2811",
      "instruction": "PUSH EDI"
    },
    {
      "address": "006a2812",
      "instruction": "CALL 0x0067de30"
    },
    {
      "address": "006a2817",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "006a2819",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "006a281b",
      "instruction": "MOV EAX,dword ptr [EDX + 0x50]"
    },
    {
      "address": "006a281e",
      "instruction": "PUSH EBX"
    },
    {
      "address": "006a281f",
      "instruction": "LEA EDI,[ESI + 0x40]"
    },
    {
      "address": "006a2822",
      "instruction": "CALL EAX"
    },
    {
      "address": "006a2824",
      "instruction": "PUSH EAX"
    },
    {
      "address": "006a2825",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "006a2827",
      "instruction": "CALL 0x00542b80"
    },
    {
      "address": "006a282c",
      "instruction": "TEST byte ptr [ESI + 0x50],0x10"
    },
    {
      "address": "006a2830",
      "instruction": "JNZ 0x006a28a2"
    },
    {
      "address": "006a2832",
      "instruction": "MOVZX EAX,word ptr [ESI + 0x52]"
    },
    {
      "address": "006a2836",
      "instruction": "CMP AX,0x1"
    },
    {
      "address": "006a283a",
      "instruction": "JNZ 0x006a285e"
    },
    {
      "address": "006a283c",
      "instruction": "MOV ECX,dword ptr [ESI + 0x3c]"
    },
    {
      "address": "006a283f",
      "instruction": "CMP dword ptr [ECX + EBX*0x4],0x0"
    },
    {
      "address": "006a2843",
      "instruction": "LEA EAX,[ESP + 0x10]"
    },
    {
      "address": "006a2847",
      "instruction": "SETNZ DL"
    },
    {
      "address": "006a284a",
      "instruction": "PUSH EAX"
    },
    {
      "address": "006a284b",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "006a284d",
      "instruction": "MOV byte ptr [ESP + 0x14],DL"
    },
    {
      "address": "006a2851",
      "instruction": "CALL 0x00422e20"
    },
    {
      "address": "006a2856",
      "instruction": "MOV EAX,EDI"
    },
    {
      "address": "006a2858",
      "instruction": "POP EDI"
    },
    {
      "address": "006a2859",
      "instruction": "POP ESI"
    },
    {
      "address": "006a285a",
      "instruction": "POP EBX"
    },
    {
      "address": "006a285b",
      "instruction": "RET 0x4"
    },
    {
      "address": "006a285e",
      "instruction": "CMP AX,0x9"
    },
    {
      "address": "006a2862",
      "instruction": "JNZ 0x006a2882"
    },
    {
      "address": "006a2864",
      "instruction": "MOV ECX,dword ptr [ESI + 0x3c]"
    },
    {
      "address": "006a2867",
      "instruction": "MOV EDX,dword ptr [ECX + EBX*0x4]"
    },
    {
      "address": "006a286a",
      "instruction": "LEA EAX,[ESP + 0x10]"
    },
    {
      "address": "006a286e",
      "instruction": "PUSH EAX"
    },
    {
      "address": "006a286f",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "006a2871",
      "instruction": "MOV dword ptr [ESP + 0x14],EDX"
    },
    {
      "address": "006a2875",
      "instruction": "CALL 0x00422eb0"
    },
    {
      "address": "006a287a",
      "instruction": "MOV EAX,EDI"
    },
    {
      "address": "006a287c",
      "instruction": "POP EDI"
    },
    {
      "address": "006a287d",
      "instruction": "POP ESI"
    },
    {
      "address": "006a287e",
      "instruction": "POP EBX"
    },
    {
      "address": "006a287f",
      "instruction": "RET 0x4"
    },
    {
      "address": "006a2882",
      "instruction": "CMP AX,0xd"
    },
    {
      "address": "006a2886",
      "instruction": "JNZ 0x006a28a2"
    },
    {
      "address": "006a2888",
      "instruction": "MOV ECX,dword ptr [ESI + 0x3c]"
    },
    {
      "address": "006a288b",
      "instruction": "MOVSS XMM0,dword ptr [ECX + EBX*0x4]"
    },
    {
      "address": "006a2890",
      "instruction": "LEA EDX,[ESP + 0x10]"
    },
    {
      "address": "006a2894",
      "instruction": "PUSH EDX"
    },
    {
      "address": "006a2895",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "006a2897",
      "instruction": "MOVSS dword ptr [ESP + 0x14],XMM0"
    },
    {
      "address": "006a289d",
      "instruction": "CALL 0x00428060"
    },
    {
      "address": "006a28a2",
      "instruction": "MOV EAX,EDI"
    },
    {
      "address": "006a28a4",
      "instruction": "POP EDI"
    },
    {
      "address": "006a28a5",
      "instruction": "POP ESI"
    },
    {
      "address": "006a28a6",
      "instruction": "POP EBX"
    },
    {
      "address": "006a28a7",
      "instruction": "RET 0x4"
    },
    {
      "address": "006a28aa",
      "instruction": "PUSH EBX"
    },
    {
      "address": "006a28ab",
      "instruction": "CALL 0x006a24d0"
    },
    {
      "address": "006a28b0",
      "instruction": "POP ESI"
    },
    {
      "address": "006a28b1",
      "instruction": "POP EBX"
    },
    {
      "address": "006a28b2",
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
  "original_bytes": 9735,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"x86-32 thiscall with first explicit list receiver in ECX and caller cleanup\",\n    \"return_semantics\": \"OpaqueProperty* in EAX\",\n    \"return_type\": \"OpaqueProperty*\",\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"caller\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_direct_property_wave6::OpaqueBaseObject,openspore::reconstruction::pkg_direct_property_wave6::OpaqueList,openspore::reconstruction::pkg_direct_property_wave6::OpaqueMap,openspore::reconstruction::pkg_direct_property_wave6::OpaqueMapEntry\",\n        \"shared_vtable:vtable:0x01408870\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-DIRECT-PROPERTY-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"opaque_list_has_property_006a27d0\",\n      \"va\": \"0x006a27d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_direct_property_wave6::OpaqueBaseObject,openspore::reconstruction::pkg_direct_property_wave6::OpaqueList,openspore::reconstruction::pkg_direct_property_wave6::OpaqueMap,openspore::reconstruction::pkg_direct_property_wave6::OpaqueMapEntry\",\n        \"shared_vtable:vtable:0x01408870\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-DIRECT-PROPERTY-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"opaque_list_get_property_006a28c0\",\n      \"va\": \"0x006a28c0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_direct_property_wave6::OpaqueBaseObject,openspore::reconstruction::pkg_direct_property_wave6::OpaqueList,openspore::reconstruction::pkg_direct_property_wave6::OpaqueMap,openspore::reconstruction::pkg_direct_property_wave6::OpaqueMapEntry\",\n        \"shared_vtable:vtable:0x01408870\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-DIRECT-PROPERTY-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"opaque_list_set_property_006a30c0\",\n      \"va\": \"0x006a30c0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_direct_property_wave6::OpaqueBaseObject,openspore::reconstruction::pkg_direct_property_wave6::OpaqueList,openspore::reconstruction::pkg_direct_property_wave6::OpaqueMap,openspore::reconstruction::pkg_direct_property_wave6::OpaqueMapEntry\",\n        \"shared_vtable:vtable:0x01408870\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-DIRECT-PROPERTY-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"opaque_list_get_property_ids_006a3180\",\n      \"va\": \"0x006a3180\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01408870\"\n      ],\n      \"package\": \"pkg-app-proplist-copyall-wave16\",\n      \"score\": 4,\n      \"symbol\": \"all_copy_from_properties_006a14d0\",\n      \"va\": \"0x006a14d0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01408870\"\n      ],\n      \"package\": \"PKG-PROPERTY-SAFE-WAVE9\",\n      \"score\": 4,\n      \"symbol\": \"direct_property_list_add_properties_from_006a1600\",\n      \"va\": \"0x006a1600\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01408870\"\n      ],\n      \"package\": \"PKG-PROPERTY-SAFE-WAVE9\",\n      \"score\": 4,\n      \"symbol\": \"direct_property_list_get_property_alt_006a1e50\",\n      \"va\": \"0x006a1e50\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01408870\"\n      ],\n      \"package\": \"pkg-direct-property-clear-wave14\",\n      \"score\": 4,\n      \"symbol\": \"direct_property_list_clear_006a2b20\",\n      \"va\": \"0x006a2b20\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Reviewed static mechanics and x86-32 ABI are preserved; opaque runtime ports and ownership remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": null,\n  \"cluster\": \"app-lifecycle\",\n  \"confidence\": 0.9,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"property_record_assign_scalar_00428060\",\n        \"reconstructed\": true,\n        \"va\": \"0x00428060\"\n      },\n      {\n        \"name\": \"property_list_get_property_object_006a24d0\",\n        \"reconstructed\": true,\n        \"va\": \"0x006a24d0\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x006a2851\",\n        \"direction\": \"out\",\n        \"other\": \"0x00422e20\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006a2875\",\n        \"direction\": \"out\",\n        \"other\": \"0x00422eb0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006a289d\",\n        \"direction\": \"out\",\n        \"other\": \"0x00428060\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006a2827\",\n        \"direction\": \"out\",\n        \"other\": \"0x00542b80\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006a2812\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067de30\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006a28ab\",\n        \"direction\": \"out\",\n        \"other\": \"0x006a24d0\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_trun
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
  "body_end": "006a28b4",
  "body_span_bytes": 181,
  "body_start": "006a2800",
  "callees": [
    "App::Property::SetValueInt32",
    "App::Property::SetValueBool",
    "FUN_00542b80",
    "FUN_00428060",
    "App::PropertyList::GetPropertyObject",
    "FUN_0067de30"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "006a2800",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "App::DirectPropertyList::GetPropertyObject",
  "namespace": "App",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 2,
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
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "Property *",
  "return_type_resolved": true,
  "rva": "0x2a2800",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "Property * App::DirectPropertyList::GetPropertyObject(DirectPropertyList * this, uint32_t propertyID)",
  "size_bytes": 181,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x006a2800",
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
      "from": "01408898"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__DirectPropertyList__GetPropertyObject.c",
  "file": "src/reconstruction/pkg_direct_property_wave6/direct_property_wave6.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__DirectPropertyList__GetPropertyObject.c",
    "src/reconstruction/pkg_direct_property_wave6/direct_property_wave6.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-direct-property-wave6/006a2800.json"
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
    "property service resolver, type conversion, map lifetime, and sentinel contents remain gated",
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
  "OpaqueProperty*",
  "openspore::reconstruction::pkg_direct_property_wave6::OpaqueBaseObject",
  "openspore::reconstruction::pkg_direct_property_wave6::OpaqueList",
  "openspore::reconstruction::pkg_direct_property_wave6::OpaqueMap",
  "openspore::reconstruction::pkg_direct_property_wave6::OpaqueMapEntry",
  "openspore::reconstruction::pkg_direct_property_wave6::OpaqueProperty",
  "openspore::reconstruction::pkg_direct_property_wave6::OpaquePropertyService",
  "openspore::reconstruction::pkg_direct_property_wave6::OpaqueWordVector"
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
