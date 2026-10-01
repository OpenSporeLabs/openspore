# Evidence 0x0093db80

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `9bad94e2b73f1f3c5ca5f6640022cb9119b91c809eef0371149ac9011f98d8de`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "__thiscall observed",
  "hidden_this_register": "ECX",
  "return_type": "void",
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "observed_use": "Nonzero enables the conditional clear path",
      "position": 1,
      "type": "std::uint8_t",
      "width_bytes": 1
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
          1
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
          1
        ],
        "written": false
      }
    ],
    "stack_cleanup_bytes": 4,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x4"
  },
  "abstained_because": [],
  "cleanup": {
    "bytes": 4,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x4",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "d8e0cccdb528b4f1f381b2e2df3ce39270849bb11842ed11e7892bb8dd2384b7",
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
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0012"
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
        "obs-0007"
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
        "obs-0002",
        "obs-0003",
        "obs-0010"
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
        "obs-0002",
        "obs-0003",
        "obs-0010",
        "obs-0012"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0012"
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
        "obs-0012"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0012"
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
      "at": "0x0093db80",
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
      "at": "0x0093db81",
      "count": 3,
      "first_use": 1,
      "first_write_index": 17,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x0093db81",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x0093db94",
      "base": null,
      "disp": 22342472,
      "id": "obs-0004",
      "index": 10,
      "kind": "CALL_INDIRECT",
      "raw": "CALL dword ptr [0x0154eb48]",
      "via": "memory"
    },
    {
      "at": "0x0093db9a",
      "definite": true,
      "id": "obs-0005",
      "index": 11,
      "kind": "REG_WRITE",
      "raw": "ADD ESP,0x18",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x0093db9d",
      "count": 1,
      "first_use": 12,
      "first_write_index": 11,
      "id": "obs-0006",
      "index": 12,
      "kind": "REG_READ",
      "raw": "CMP byte ptr [ESP + 0x8],0x0",
      "reg": "ESP"
    },
    {
      "at": "0x0093db9d",
      "base": "ESP",
      "disp": 8,
      "id": "obs-0007",
      "index": 12,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "CMP byte ptr [ESP + 0x8],0x0",
      "resolved": true,
      "size": 1
    },
    {
      "at": "0x0093dbaa",
      "count": 2,
      "first_use": 16,
      "first_write_index": 16,
      "id": "obs-0008",
      "index": 16,
      "kind": "REG_READ",
      "raw": "XOR EAX,EAX",
      "reg": "EAX"
    },
    {
      "at": "0x0093dbaa",
      "definite": true,
      "id": "obs-0009",
      "index": 16,
      "kind": "REG_WRITE",
      "raw": "XOR EAX,EAX",
      "reg": "EAX",
      "write_kind": "zero"
    },
    {
      "at": "0x0093dbac",
      "definite": true,
      "id": "obs-0010",
      "index": 17,
      "kind": "REG_W
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
    "name": null,
    "reconstructed": false,
    "va": "0x00407280"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0040d2d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x004111e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00411e50"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00417600"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0041a0c0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00422e20"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00422eb0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00422f40"
  },
  {
    "name": "property_record_assign_pair_004279d0",
    "reconstructed": true,
    "va": "0x004279d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00427fd0"
  },
  {
    "name": "property_record_assign_scalar_00428060",
    "reconstructed": true,
    "va": "0x00428060"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x004284d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00430e70"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0046aac0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0046b460"
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
  "count": 22,
  "instructions": [
    {
      "address": "0093db80",
      "instruction": "PUSH ESI"
    },
    {
      "address": "0093db81",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "0093db83",
      "instruction": "TEST byte ptr [ESI + 0x10],0x4"
    },
    {
      "address": "0093db87",
      "instruction": "JZ 0x0093db9d"
    },
    {
      "address": "0093db89",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "0093db8b",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "0093db8d",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "0093db8f",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "0093db91",
      "instruction": "PUSH ESI"
    },
    {
      "address": "0093db92",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "0093db94",
      "instruction": "CALL dword ptr [0x0154eb48]"
    },
    {
      "address": "0093db9a",
      "instruction": "ADD ESP,0x18"
    },
    {
      "address": "0093db9d",
      "instruction": "CMP byte ptr [ESP + 0x8],0x0"
    },
    {
      "address": "0093dba2",
      "instruction": "JZ 0x0093dbb6"
    },
    {
      "address": "0093dba4",
      "instruction": "TEST byte ptr [ESI + 0x10],0x2"
    },
    {
      "address": "0093dba8",
      "instruction": "JNZ 0x0093dbb6"
    },
    {
      "address": "0093dbaa",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "0093dbac",
      "instruction": "XOR ECX,ECX"
    },
    {
      "address": "0093dbae",
      "instruction": "MOV word ptr [ESI + 0x12],AX"
    },
    {
      "address": "0093dbb2",
      "instruction": "MOV word ptr [ESI + 0x10],CX"
    },
    {
      "address": "0093dbb6",
      "instruction": "POP ESI"
    },
    {
      "address": "0093dbb7",
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
  "original_bytes": 15610,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"__thiscall observed\",\n    \"hidden_this_register\": \"ECX\",\n    \"return_type\": \"void\",\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"observed_use\": \"Nonzero enables the conditional clear path\",\n        \"position\": 1,\n        \"type\": \"std::uint8_t\",\n        \"width_bytes\": 1\n      }\n    ],\n    \"stack_cleanup_bytes\": 4,\n    \"termination\": \"RET 0x4\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaquePreferenceQuery\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 24,\n      \"symbol\": \"editor_query_reset_005dd750\",\n      \"va\": \"0x005dd750\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 16,\n      \"symbol\": \"editor_query_dispatch_005dfd00\",\n      \"va\": \"0x005dfd00\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 14,\n      \"symbol\": \"editor_query_service_005ca960\",\n      \"va\": \"0x005ca960\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"shared_types:OpaquePreferenceQuery\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 14,\n      \"symbol\": \"Editors_EditorUI_HandleMessage_005e0000\",\n      \"va\": \"0x005e0000\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 8,\n      \"symbol\": \"Editors_EditorModel_SetColor_raw_004ae250\",\n      \"va\": \"0x004ae250\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 8,\n      \"symbol\": \"FUN_005dda30\",\n      \"va\": \"0x005dda30\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 3,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 3,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [\n    \"The function has very broad property-system fan-in, so a typed implementation would overclaim without the owner.\",\n    \"The global callback owner and payload semantics are unresolved.\"\n  ],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaquePreferenceQuery\",\n  \"cluster\": null,\n  \"confidence\": 0.94,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00407280\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0040d2d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004111e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00411e50\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00417600\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0041a0c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00422e20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00422eb0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00422f40\"\n      },\n      {\n        \"name\": \"property_record_assign_pair_004279d0\",\n        \"reconstructed\": true,\n        \"va\": \"0x004279d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00427fd0\"\n      },\n      {\n        \"name\": \"property_record_assign_scalar_00428060\",\n        \"reconstructed\": true,\n        \"va\": \"0x00428060\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004284d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00430e70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0046aac0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0046b460\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00471000\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00478300\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004b5dd0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004ea920\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00542980\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00542b80\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005477a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n 
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
  "body_end": "0093dbb9",
  "body_span_bytes": 58,
  "body_start": "0093db80",
  "callees": [
    "FUN_009415a0"
  ],
  "callers": [
    "FUN_006a2b80",
    "FUN_00e47520",
    "FUN_013ca8f0",
    "FUN_00e24d10",
    "FUN_00828c30",
    "FUN_00804920",
    "FUN_0060f370",
    "FUN_0068a720",
    "FUN_0075f030",
    "FUN_0068a0f0",
    "FUN_007cce50",
    "FUN_0046b460",
    "FUN_0040d2d0",
    "FUN_005799a0",
    "FUN_007c9680",
    "FUN_00a18910",
    "FUN_00b199c0",
    "FUN_00804e70",
    "FUN_00f16580",
    "FUN_00754310",
    "FUN_006a9790",
    "FUN_00f47ed0",
    "FUN_005e6b40",
    "FUN_006a2d30",
    "FUN_00a17910",
    "FUN_0081fd70",
    "FUN_004279d0",
    "FUN_00658e80",
    "FUN_00411e50",
    "FUN_006a0e50",
    "App::Property::SetValueVector2",
    "FUN_008347f0",
    "FUN_00dfa930",
    "FUN_008219a0",
    "FUN_013c1760",
    "FUN_004284d0",
    "App::PropertyList::SetProperty",
    "FUN_013bed20",
    "App::Property::SetValueVector3",
    "FUN_00f93dd0",
    "FUN_006a0ca0",
    "FUN_00b1bb40",
    "FUN_00df6c40",
    "FUN_00ef7d90",
    "FUN_00eceab0",
    "FUN_00cdbd20",
    "FUN_00a412c0",
    "FUN_00a41410",
    "FUN_00677700",
    "FUN_00a415f0",
    "FUN_00828410",
    "FUN_00e28f40",
    "App::Property::SetValueInt32",
    "FUN_008048c0",
    "FUN_006a1bd0",
    "FUN_007ca1c0",
    "FUN_004b5dd0",
    "FUN_008220e0",
    "FUN_00417600",
    "FUN_00471000",
    "FUN_00bca120",
    "FUN_00f31f20",
    "FUN_0081d7a0",
    "FUN_00bcab00",
    "FUN_006a6340",
    "FUN_00430e70",
    "FUN_00ce3eb0",
    "FUN_00689c80",
    "FUN_0081dbf0",
    "FUN_00f368b0",
    "FUN_006aa640",
    "FUN_013bed00",
    "FUN_00d35190",
    "Prop_GetPropValueBool",
    "FUN_00b76160",
    "FUN_00571ee0",
    "FUN_0081f0e0",
    "App::DirectPropertyList::SetFloat",
    "FUN_00f055c0",
    "FUN_00478300",
    "FUN_00de9a00",
    "FUN_006a0d30",
    "FUN_00ce1390",
    "FUN_00f9b7f0",
    "FUN_00e21b30",
    "FUN_00ecc8b0",
    "FUN_0068b370",
    "FUN_00b279e0",
    "FUN_00bdde70",
    "App::DirectPropertyList::SetInt",
    "FUN_00f93790",
    "App::Property::SetValueKey",
    "FUN_00608cc0",
    "FUN_00bed920",
    "FUN_00f37690",
    "FUN_00e32250",
    "FUN_00820ec0",
    "FUN_00f32d10",
    "FUN_00428060",
    "FUN_007cccc0",
    "FUN_00f34660",
    "FUN_00407280",
    "FUN_004ea920",
    "FUN_00ce2140",
    "FUN_0081daa0",
    "FUN_00f35be0",
    "FUN_013c0570",
    "FUN_007e67a0",
    "FUN_0041a0c0",
    "FUN_006a4990",
    "FUN_00828350",
    "FUN_006a0ee0",
    "FUN_0060e600",
    "FUN_00828740",
    "FUN_006a0dc0",
    "FUN_0081d800",
    "FUN_005e0000",
    "FUN_00e9a940",
    "FUN_00eeda20",
    "FUN_00694440",
    "FUN_0081ed10",
    "FUN_0060cfa0",
    "FUN_0061e330",
    "FUN_00613e50",
    "FUN_00676710",
    "FUN_0081d9c0",
    "FUN_007c8d20",
    "FUN_0081d870",
    "FUN_0081da30",
    "FUN_006aa4c0",
    "App::Property::SetValueColorRGBA",
    "FUN_0061c880",
    "FUN_00e2c590",
    "FUN_00ef8dc0",
    "FUN_00f27d80",
    "FUN_00d1e930",
    "FUN_005477a0",
    "FUN_006a3fa0",
    "FUN_00f32bf0",
    "FUN_00754ca0",
    "FUN_004111e0",
    "FUN_005bf7c0",
    "FUN_00542980",
    "App::Property::SetValueVector4",
    "App::Property::SetValueBool",
    "FUN_00542b80",
    "FUN_005e4560",
    "FUN_00821d70",
    "FUN_006a36b0",
    "FUN_00d12910",
    "FUN_00821600",
    "FUN_006a2010",
    "FUN_005bf470",
    "FUN_00a41500",
    "FUN_00613d20",
    "FUN_0081d950",
    "FUN_0081db10",
    "FUN_00821260",
    "FUN_00b215a0",
    "FUN_00820680",
    "FUN_0068bf20",
    "FUN_0081dc60",
    "FUN_00427fd0",
    "FUN_0060d860",
    "FUN_0081f490",
    "App::Property::SetValueColorRGB",
    "FUN_0081d8e0",
    "FUN_00820210",
    "FUN_0080b4d0",
    "FUN_00f94480",
    "FUN_00612a70",
    "FUN_00676c80",
    "FUN_0081f900",
    "FUN_0063dc40",
    "FUN_00e2d6a0",
    "FUN_006aaa10",
    "FUN_0081db80",
    "App::DirectPropertyList::SetBool",
    "FUN_00612ba0",
    "FUN_0046aac0",
    "FUN_00a06310",
    "FUN_00685a30",
    "FUN_006a2660",
    "FUN_005bf860",
    "FUN_00bed460",
    "FUN_00612a90",
    "FUN_006a34a0",
    "FUN_00d0aa70",
    "FUN_005802f0",
    "FUN_006a2710",
    "FUN_006a2cb0",
    "App::PropertyList::SetParent",
    "FUN_00de5950",
    "FUN_00603de0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "0093db80",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_0093db80",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x53db80",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_0093db80(void)",
  "size_bytes": 58,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x0093db80",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 100,
  "xrefs": [
    {
      "from": "00685a4b"
    },
    {
      "from": "00571ee8"
    },
    {
      "from": "0068a118"
    },
    {
      "from": "00612a7b"
    },
    {
      "from": "00f48674"
    },
    {
      "from": "00f486d3"
    },
    {
      "from": "006a1859"
    },
    {
      "from": "00422e38"
    },
    {
      "from": "0069449d"
    },
    {
      "from": "00542b98"
    },
    {
      "from": "006a2c0f"
    },
    {
      "from": "006a2183"
    },
    {
      "from": "00612aae"
    },
    {

[TRUNCATED]
```

## globals

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "global:0x0154eb48"
]
```

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
    "reconstruction/metadata/pkg10-editor-dispatch/0093db80.json"
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
    "gate-editor-query-global-callback"
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
  "OpaqueQueryCallback",
  "std::uint8_t",
  "void"
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
