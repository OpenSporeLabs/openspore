# Evidence 0x006a1de0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `f4946786c2443caabc9a07a9a0dbb76ece8e26ef2bde370f87d2abf6f01d20c1`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "convention": "thiscall with callee stack cleanup",
  "hidden_receiver": "ECX OpaquePropertyList*; copied to ESI at 0x006a1de1",
  "hidden_this_register": "ECX",
  "hidden_this_type": "OpaquePropertyList*",
  "ordinary_stack_argument_slots": 2,
  "ordinary_stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "evidence": "MOVZX-free 32-bit use; reloaded at 0x006a1dfb from [ESP+0x1c] with four callee arguments still pushed, which is the same slot as ESP+0x04 at function entry",
      "name": "property_id",
      "position": 1,
      "type": "uint32_t",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x08",
      "evidence": "reloaded from [ESP+0x10] at 0x006a1e17 and at 0x006a1e2e with ESP+8 adjusted, and pushed as the first callee-visible word of the +0x20 dispatch",
      "name": "result",
      "position": 2,
      "type": "Property **",
      "width_bytes": 4
    }
  ],
  "ret_form": "RET 0x8",
  "return_register": "AL",
  "return_type": "bool",
  "return_width_bytes": 1,
  "saved_registers": "ESI is saved at 0x006a1de0 and restored at 0x006a1e23/0x006a1e3c/0x006a1e43; EDI is pushed at 0x006a1dea and popped at 0x006a1e1e/0x006a1e3b/0x006a1e40; EAX and EDX are caller-saved scratch",
  "stack_cleanup_bytes": 8,
  "stack_cleanup_owner": "callee; all three exits are RET 0x8",
  "termination": "RET 0x8 at 0x006a1e24, 0x006a1e3d and 0x006a1e44"
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
      "entry_ESP+0x8",
      "entry_ESP+0x10"
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
        "entry_offset": "entry_ESP+0x8",
        "observed": true,
        "ordinal": 2,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x10",
        "observed": true,
        "ordinal": 4,
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
      },
      {
        "entry_offset": "entry_ESP+0x10",
        "observed": true,
        "ordinal": 4,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "termination": "RET 0x8"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -8, so the listing is not one path",
    "ret_imm_below_highest_slot: ret 0x8 pops less than the highest read slot 0x10; everything above it belongs to the caller's frame",
    "slot_gaps_present: argument ordinal(s) below the highest read slot are never touched",
    "no_discriminator: the callee pop of 0x8 is not a whole number of dword stack arguments, so no convention follows from it"
  ],
  "cleanup": {
    "bytes": 8,
    "confidence": "UNKNOWN",
    "corroboration": "not_available",
    "evidence": "ret 0x8 but entry slot 0x10 is read",
    "side": null
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "03f9be0f5467c5c9df34621d460b9db12c6aa7106cad6ab53e168be2da1c097a",
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
    "ghidra_parameter_count": 3,
    "persisted": "no_information",
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
        "obs-0019",
        "obs-0024",
        "obs-0027"
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
        "obs-0019",
        "obs-0024",
        "obs-0027"
      ],
      "claim": "cleanup side is undetermined: a slot above the popped area is read",
      "confidence": "UNKNOWN",
      "id": "C4",
      "value": {
        "bytes": 8,
        "side": null
      }
    },
    {
      "based_on": [
        "obs-0009",
        "obs-0012",
        "obs-0015",
        "obs-0020"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 1,
        "observed_slots": 3,
        "total_bytes": 16
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0008",
        "obs-0009",
        "obs-0015",
        "obs-0016"
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
        "obs-0027"
      ],
      "claim": "the calling convention is unknown: the terminal pop is not a whole number of dword arguments",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0019",
        "obs-0024",
        "obs-0027"
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
        "obs-0019",
        "obs-0024",
        "obs-0027"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0019",
        "obs-0024",
        "obs-0027"
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
      "at": "0x006a1de0",
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
      "at": "0x006a1de1",
      "count": 6,
      "first_use": 1
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
    "name": "direct_property_list_get_property_alt_006a1e50",
    "reconstructed": true,
    "va": "0x006a1e50"
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
  "count": 47,
  "instructions": [
    {
      "address": "006a1de0",
      "instruction": "PUSH ESI"
    },
    {
      "address": "006a1de1",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "006a1de3",
      "instruction": "MOVZX EAX,byte ptr [ESI + 0x2c]"
    },
    {
      "address": "006a1de7",
      "instruction": "MOV EDX,dword ptr [ESI + 0x18]"
    },
    {
      "address": "006a1dea",
      "instruction": "PUSH EDI"
    },
    {
      "address": "006a1deb",
      "instruction": "MOV EDI,dword ptr [ESI + 0x1c]"
    },
    {
      "address": "006a1dee",
      "instruction": "PUSH EAX"
    },
    {
      "address": "006a1def",
      "instruction": "LEA ECX,[ESP + 0x10]"
    },
    {
      "address": "006a1df3",
      "instruction": "PUSH ECX"
    },
    {
      "address": "006a1df4",
      "instruction": "PUSH EDI"
    },
    {
      "address": "006a1df5",
      "instruction": "PUSH EDX"
    },
    {
      "address": "006a1df6",
      "instruction": "CALL 0x00612db0"
    },
    {
      "address": "006a1dfb",
      "instruction": "MOV EDX,dword ptr [ESP + 0x1c]"
    },
    {
      "address": "006a1dff",
      "instruction": "ADD ESP,0x10"
    },
    {
      "address": "006a1e02",
      "instruction": "CMP EAX,EDI"
    },
    {
      "address": "006a1e04",
      "instruction": "JZ 0x006a1e11"
    },
    {
      "address": "006a1e06",
      "instruction": "CMP EDX,dword ptr [EAX]"
    },
    {
      "address": "006a1e08",
      "instruction": "JC 0x006a1e11"
    },
    {
      "address": "006a1e0a",
      "instruction": "LEA ECX,[EAX + 0x18]"
    },
    {
      "address": "006a1e0d",
      "instruction": "CMP EAX,ECX"
    },
    {
      "address": "006a1e0f",
      "instruction": "JNZ 0x006a1e13"
    },
    {
      "address": "006a1e11",
      "instruction": "MOV EAX,EDI"
    },
    {
      "address": "006a1e13",
      "instruction": "CMP EAX,EDI"
    },
    {
      "address": "006a1e15",
      "instruction": "JZ 0x006a1e27"
    },
    {
      "address": "006a1e17",
      "instruction": "MOV ECX,dword ptr [ESP + 0x10]"
    },
    {
      "address": "006a1e1b",
      "instruction": "ADD EAX,0x4"
    },
    {
      "address": "006a1e1e",
      "instruction": "POP EDI"
    },
    {
      "address": "006a1e1f",
      "instruction": "MOV dword ptr [ECX],EAX"
    },
    {
      "address": "006a1e21",
      "instruction": "MOV AL,0x1"
    },
    {
      "address": "006a1e23",
      "instruction": "POP ESI"
    },
    {
      "address": "006a1e24",
      "instruction": "RET 0x8"
    },
    {
      "address": "006a1e27",
      "instruction": "MOV ECX,dword ptr [ESI + 0x30]"
    },
    {
      "address": "006a1e2a",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "006a1e2c",
      "instruction": "JZ 0x006a1e40"
    },
    {
      "address": "006a1e2e",
      "instruction": "MOV ESI,dword ptr [ESP + 0x10]"
    },
    {
      "address": "006a1e32",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "006a1e34",
      "instruction": "PUSH ESI"
    },
    {
      "address": "006a1e35",
      "instruction": "PUSH EDX"
    },
    {
      "address": "006a1e36",
      "instruction": "MOV EDX,dword ptr [EAX + 0x20]"
    },
    {
      "address": "006a1e39",
      "instruction": "CALL EDX"
    },
    {
      "address": "006a1e3b",
      "instruction": "POP EDI"
    },
    {
      "address": "006a1e3c",
      "instruction": "POP ESI"
    },
    {
      "address": "006a1e3d",
      "instruction": "RET 0x8"
    },
    {
      "address": "006a1e40",
      "instruction": "POP EDI"
    },
    {
      "address": "006a1e41",
      "instruction": "XOR AL,AL"
    },
    {
      "address": "006a1e43",
      "instruction": "POP ESI"
    },
    {
      "address": "006a1e44",
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
  "original_bytes": 9748,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"convention\": \"thiscall with callee stack cleanup\",\n    \"hidden_receiver\": \"ECX OpaquePropertyList*; copied to ESI at 0x006a1de1\",\n    \"hidden_this_register\": \"ECX\",\n    \"hidden_this_type\": \"OpaquePropertyList*\",\n    \"ordinary_stack_argument_slots\": 2,\n    \"ordinary_stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"evidence\": \"MOVZX-free 32-bit use; reloaded at 0x006a1dfb from [ESP+0x1c] with four callee arguments still pushed, which is the same slot as ESP+0x04 at function entry\",\n        \"name\": \"property_id\",\n        \"position\": 1,\n        \"type\": \"uint32_t\",\n        \"width_bytes\": 4\n      },\n      {\n        \"entry_offset\": \"ESP+0x08\",\n        \"evidence\": \"reloaded from [ESP+0x10] at 0x006a1e17 and at 0x006a1e2e with ESP+8 adjusted, and pushed as the first callee-visible word of the +0x20 dispatch\",\n        \"name\": \"result\",\n        \"position\": 2,\n        \"type\": \"Property **\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"ret_form\": \"RET 0x8\",\n    \"return_register\": \"AL\",\n    \"return_type\": \"bool\",\n    \"return_width_bytes\": 1,\n    \"saved_registers\": \"ESI is saved at 0x006a1de0 and restored at 0x006a1e23/0x006a1e3c/0x006a1e43; EDI is pushed at 0x006a1dea and popped at 0x006a1e1e/0x006a1e3b/0x006a1e40; EAX and EDX are caller-saved scratch\",\n    \"stack_cleanup_bytes\": 8,\n    \"stack_cleanup_owner\": \"callee; all three exits are RET 0x8\",\n    \"termination\": \"RET 0x8 at 0x006a1e24, 0x006a1e3d and 0x006a1e44\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x01408820\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-app-proplist-copyall-wave16\",\n      \"score\": 12,\n      \"symbol\": \"all_copy_from_properties_006a14d0\",\n      \"va\": \"0x006a14d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x01408820\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-dfw-006a1540\",\n      \"score\": 12,\n      \"symbol\": \"proplist_write_006a1540\",\n      \"va\": \"0x006a1540\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x01408820\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-property-clear-wave13\",\n      \"score\": 12,\n      \"symbol\": \"property_list_clear_006a2a80\",\n      \"va\": \"0x006a2a80\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x01408820\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-property-remove-006a2ef0\",\n      \"score\": 12,\n      \"symbol\": \"property_list_remove_property_006a2ef0\",\n      \"va\": \"0x006a2ef0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DATA,UNCONDITIONAL_CALL\",\n        \"shared_vtable:vtable:0x01408820\"\n      ],\n      \"package\": \"wave6-resources\",\n      \"score\": 10,\n      \"symbol\": \"property_list_has_property_006a2470\",\n      \"va\": \"0x006a2470\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DATA,UNCONDITIONAL_CALL\",\n        \"shared_vtable:vtable:0x01408820\"\n      ],\n      \"package\": \"wave6-resources\",\n      \"score\": 10,\n      \"symbol\": \"property_list_get_property_object_006a24d0\",\n      \"va\": \"0x006a24d0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:Property **\",\n        \"same_calling_convention\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-PROPERTY-SAFE-WAVE9\",\n      \"score\": 8,\n      \"symbol\": \"direct_property_list_get_property_alt_006a1e50\",\n      \"va\": \"0x006a1e50\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-direct-property-clear-wave14\",\n      \"score\": 8,\n      \"symbol\": \"direct_property_list_clear_006a2b20\",\n      \"va\": \"0x006a2b20\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"app-lifecycle\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": \"direct_property_list_get_property_alt_006a1e50\",\n        \"reconstructed\": true,\n        \"va\": \"0x006a1e50\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x006a1e70\",\n        \"direction\": \"in\",\n        \"other\": \"0x006a1e50\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006a1df6\",\n        \"direction\": \"out\",\n        \"other\": \"0x00612db0\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 1,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [\n      \"0x006a1e50\"\n    ],\n    \"scc\": {\n      \"id\": \"scc-0202\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"CONFIRMED\",\n  \"globals\": [],\n  \"integration_status\": null,\n  \"name\": \"App::PropertyList::GetPropertyAlt\",\n  \"normalized_symbol\": \"App::PropertyList::GetPropertyAlt\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"runtime_gated_requires_explicit_gate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"packa
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
  "body_end": "006a1e46",
  "body_span_bytes": 103,
  "body_start": "006a1de0",
  "callees": [
    "FUN_00612db0"
  ],
  "callers": [
    "App::DirectPropertyList::GetPropertyAlt"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "006a1de0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "App::PropertyList::GetPropertyAlt",
  "namespace": "App",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 3,
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
    },
    {
      "name": "result",
      "ordinal": 2,
      "storage": "Stack[0xc]:4",
      "type": "Property * *"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "bool",
  "return_type_resolved": true,
  "rva": "0x2a1de0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "bool App::PropertyList::GetPropertyAlt(PropertyList * this, uint32_t propertyID, Property * * result)",
  "size_bytes": 103,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x006a1de0",
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
      "from": "01408840"
    },
    {
      "from": "006a1e70"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__GetPropertyAlt.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__GetPropertyAlt.c",
    "reconstruction/staging/pkg-orchestrate-dogfood-006a1de0/dogfood_006a1de0.cpp",
    "reconstruction/staging/pkg-orchestrate-dogfood-006a1de0/dogfood_006a1de0.hpp",
    "reconstruction/staging/pkg-orchestrate-dogfood-006a1de0/dogfood_006a1de0_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-orchestrate-dogfood-006a1de0/006a1de0.json"
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
    "No original-process invocation and no indirect-caller trace were captured for this record.",
    "The concrete implementation behind +0x20 (0x006a1de0 in the table read here, but the runtime table of the +0x30 object was not captured) is a runtime gate.",
    "The pointee type and ownership of the word at entry+0x04 are unresolved; no runtime observation of the returned address was captured.",
    "The runtime object that supplies the +0x30 word and its class identity are unobserved; the chain depth and its termination condition are data dependent.",
    "Whether the entry span is sorted at runtime, and therefore whether the unsigned lower bound is a valid search, is a runtime property of the data."
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
  "0x00612db0 cdecl port type OpaquePropertyListLowerBound00612db0",
  "DATA",
  "OpaqueProperty (forward declared only; size, layout and ownership unresolved)",
  "OpaquePropertyEntry",
  "OpaquePropertyEntry (package-local, stride 0x18, key at 0x00, address-only word at 0x04)",
  "OpaquePropertyEntry*",
  "OpaquePropertyList",
  "OpaquePropertyList (package-local, offsets 0x00, 0x18, 0x1c, 0x2c, 0x30)",
  "OpaquePropertyList*",
  "OpaquePropertyListVtable (package-local window 0x00-0x23, named slots +0x1c and +0x20)",
  "Property **",
  "UNCONDITIONAL_CALL",
  "bool",
  "const uint32_t*",
  "direct-call",
  "opaque 4-byte word",
  "uint32_t",
  "uint8_t"
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
