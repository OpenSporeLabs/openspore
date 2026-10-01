# Evidence 0x006a25a0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `6454812b2e7824dd5387d3240989f2f687931319223f8fe0cc9bb4e57670bd15`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "__thiscall",
  "receiver": "DirectPropertyList *",
  "receiver_register": "ECX",
  "return_type": "bool",
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "property_id",
      "type": "uint32_t",
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
    "hidden_this": true,
    "hidden_this_register": "ECX",
    "ordinary_stack_argument_slots": [
      "entry_ESP+0x4",
      "entry_ESP+0x8",
      "entry_ESP+0x14",
      "entry_ESP+0x20"
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
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x14",
        "observed": true,
        "ordinal": 5,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x20",
        "observed": true,
        "ordinal": 8,
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
        "entry_offset": "entry_ESP+0x8",
        "observed": true,
        "ordinal": 2,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x14",
        "observed": true,
        "ordinal": 5,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x20",
        "observed": true,
        "ordinal": 8,
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
    "flow_not_modelled: the linear ESP walk ends at -48, so the listing is not one path",
    "ret_imm_below_highest_slot: ret 0x4 pops less than the highest read slot 0x20; everything above it belongs to the caller's frame",
    "slot_gaps_present: argument ordinal(s) below the highest read slot are never touched",
    "no_discriminator: the callee pop of 0x4 is not a whole number of dword stack arguments, so no convention follows from it"
  ],
  "cleanup": {
    "bytes": 4,
    "confidence": "UNKNOWN",
    "corroboration": "not_available",
    "evidence": "ret 0x4 but entry slot 0x20 is read",
    "side": null
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "f6c786398848302dbcff0d6de406d2b1e20280cbce6bdf22fc9b2a7158ddbc23",
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
    "ghidra_parameter_count": 0,
    "persisted": "no_information",
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
        "obs-0015",
        "obs-0029",
        "obs-0032"
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
        "obs-0015",
        "obs-0029",
        "obs-0032"
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
        "obs-0005",
        "obs-0019",
        "obs-0022",
        "obs-0024",
        "obs-0025"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 4,
        "observed_slots": 4,
        "total_bytes": 32
      }
    },
    {
      "based_on": [
        "obs-0008",
        "obs-0009",
        "obs-0011",
        "obs-0012",
        "obs-0022",
        "obs-0025"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          24,
          28,
          44,
          56,
          60
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0032"
      ],
      "claim": "the calling convention is unknown: the terminal pop is not a whole number of dword arguments",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0015",
        "obs-0029",
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
        "obs-0015",
        "obs-0029",
        "obs-0032"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0015",
        "obs-0029",
        
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "editor_query_clear_flags_0093db80",
    "reconstructed": true,
    "va": "0x0093db80"
  }
]
```

## callers_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0040a590"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0040f3f0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0040fe00"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x004157d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x004bafc0"
  },
  {
    "name": "PaintPersistenceBoundary_submit_004c5200",
    "reconstructed": true,
    "va": "0x004c5200"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x004f3de0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0051c6a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00522b40"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00573070"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005745c0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00575270"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0057aaa0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0057ac00"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005812b0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005855b0"
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
  "count": 73,
  "instructions": [
    {
      "address": "006a25a0",
      "instruction": "SUB ESP,0x14"
    },
    {
      "address": "006a25a3",
      "instruction": "PUSH EBX"
    },
    {
      "address": "006a25a4",
      "instruction": "MOV EBX,dword ptr [ESP + 0x1c]"
    },
    {
      "address": "006a25a8",
      "instruction": "PUSH ESI"
    },
    {
      "address": "006a25a9",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "006a25ab",
      "instruction": "CMP EBX,dword ptr [ESI + 0x38]"
    },
    {
      "address": "006a25ae",
      "instruction": "JNC 0x006a25c5"
    },
    {
      "address": "006a25b0",
      "instruction": "MOV EAX,dword ptr [ESI + 0x3c]"
    },
    {
      "address": "006a25b3",
      "instruction": "XOR ECX,ECX"
    },
    {
      "address": "006a25b5",
      "instruction": "CMP dword ptr [EAX + EBX*0x4],ECX"
    },
    {
      "address": "006a25b8",
      "instruction": "POP ESI"
    },
    {
      "address": "006a25b9",
      "instruction": "SETNZ CL"
    },
    {
      "address": "006a25bc",
      "instruction": "MOV AL,CL"
    },
    {
      "address": "006a25be",
      "instruction": "POP EBX"
    },
    {
      "address": "006a25bf",
      "instruction": "ADD ESP,0x14"
    },
    {
      "address": "006a25c2",
      "instruction": "RET 0x4"
    },
    {
      "address": "006a25c5",
      "instruction": "MOVZX EDX,byte ptr [ESI + 0x2c]"
    },
    {
      "address": "006a25c9",
      "instruction": "MOV ECX,dword ptr [ESI + 0x18]"
    },
    {
      "address": "006a25cc",
      "instruction": "PUSH EDI"
    },
    {
      "address": "006a25cd",
      "instruction": "MOV EDI,dword ptr [ESI + 0x1c]"
    },
    {
      "address": "006a25d0",
      "instruction": "PUSH EDX"
    },
    {
      "address": "006a25d1",
      "instruction": "LEA EAX,[ESP + 0x28]"
    },
    {
      "address": "006a25d5",
      "instruction": "PUSH EAX"
    },
    {
      "address": "006a25d6",
      "instruction": "PUSH EDI"
    },
    {
      "address": "006a25d7",
      "instruction": "PUSH ECX"
    },
    {
      "address": "006a25d8",
      "instruction": "CALL 0x00612db0"
    },
    {
      "address": "006a25dd",
      "instruction": "ADD ESP,0x10"
    },
    {
      "address": "006a25e0",
      "instruction": "CMP EAX,EDI"
    },
    {
      "address": "006a25e2",
      "instruction": "JZ 0x006a25ef"
    },
    {
      "address": "006a25e4",
      "instruction": "CMP EBX,dword ptr [EAX]"
    },
    {
      "address": "006a25e6",
      "instruction": "JC 0x006a25ef"
    },
    {
      "address": "006a25e8",
      "instruction": "LEA ECX,[EAX + 0x18]"
    },
    {
      "address": "006a25eb",
      "instruction": "CMP EAX,ECX"
    },
    {
      "address": "006a25ed",
      "instruction": "JNZ 0x006a25f1"
    },
    {
      "address": "006a25ef",
      "instruction": "MOV EAX,EDI"
    },
    {
      "address": "006a25f1",
      "instruction": "CMP EAX,EDI"
    },
    {
      "address": "006a25f3",
      "instruction": "POP EDI"
    },
    {
      "address": "006a25f4",
      "instruction": "JZ 0x006a264b"
    },
    {
      "address": "006a25f6",
      "instruction": "ADD EAX,0x4"
    },
    {
      "address": "006a25f9",
      "instruction": "PUSH EAX"
    },
    {
      "address": "006a25fa",
      "instruction": "LEA ECX,[ESP + 0xc]"
    },
    {
      "address": "006a25fe",
      "instruction": "CALL 0x006a19b0"
    },
    {
      "address": "006a2603",
      "instruction": "MOVZX ECX,word ptr [EAX + 0x12]"
    },
    {
      "address": "006a2607",
      "instruction": "CMP CX,0x1"
    },
    {
      "address": "006a260b",
      "instruction": "JZ 0x006a261a"
    },
    {
      "address": "006a260d",
      "instruction": "CMP CX,0x10"
    },
    {
      "address": "006a2611",
      "instruction": "JZ 0x006a261a"
    },
    {
      "address": "006a2613",
      "instruction": "MOV ECX,0x15d115d"
    },
    {
      "address": "006a2618",
      "instruction": "JMP 0x006a262d"
    },
    {
      "address": "006a261a",
      "instruction": "TEST byte ptr [EAX + 0x10],0x30"
    },
    {
      "address": "006a261e",
      "instruction": "JZ 0x006a2624"
    },
    {
      "address": "006a2620",
      "instruction": "MOV ECX,dword ptr [EAX]"
    },
    {
      "address": "006a2622",
      "instruction": "JMP 0x006a262d"
    },
    {
      "address": "006a2624",
      "instruction": "MOVZX ECX,CX"
    },
    {
      "address": "006a2627",
      "instruction": "NEG ECX"
    },
    {
      "address": "006a2629",
      "instruction": "SBB ECX,ECX"
    },
    {
      "address": "006a262b",
      "instruction": "AND ECX,EAX"
    },
    {
      "address": "006a262d",
      "instruction": "TEST byte ptr [ESP + 0x18],0x4"
    },
    {
      "address": "006a2632",
      "instruction": "MOV BL,byte ptr [ECX]"
    },
    {
      "address": "006a2634",
      "instruction": "JZ 0x006a2641"
    },
    {
      "address": "006a2636",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "006a2638",
      "instruction": "LEA ECX,[ESP + 0xc]"
    },
    {
      "address": "006a263c",
      "instruction": "CALL 0x0093db80"
    },
    {
      "address": "006a2641",
      "instruction": "POP ESI"
    },
    {
      "address": "006a2642",
      "instruction": "MOV AL,BL"
    },
    {
      "address": "006a2644",
      "instruction": "POP EBX"
    },
    {
      "address": "006a2645",
      "instruction": "ADD ESP,0x14"
    },
    {
      "address": "006a2648",
      "instruction": "RET 0x4"
    },
    {
      "address": "006a264b",
      "instruction": "POP ESI"
    },
    {
      "address": "006a264c",
      "instruction": "XOR AL,AL"
    },
    {
      "address": "006a264e",
      "instruction": "POP EBX"
    },
    {
      "address": "006a264f",
      "instruction": "ADD ESP,0x14"
    },
    {
      "address": "006a2652",
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
  "original_bytes": 24594,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"__thiscall\",\n    \"receiver\": \"DirectPropertyList *\",\n    \"receiver_register\": \"ECX\",\n    \"return_type\": \"bool\",\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"name\": \"property_id\",\n        \"type\": \"uint32_t\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 4,\n    \"termination\": \"RET 0x4\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:DirectPropertyList\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-PROPERTY-SAFE-WAVE9\",\n      \"score\": 10,\n      \"symbol\": \"direct_property_list_add_properties_from_006a1600\",\n      \"va\": \"0x006a1600\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:DirectPropertyList\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-PROPERTY-SAFE-WAVE9\",\n      \"score\": 10,\n      \"symbol\": \"direct_property_list_get_property_alt_006a1e50\",\n      \"va\": \"0x006a1e50\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:Property,PropertyMapEntry\"\n      ],\n      \"package\": \"wave6-resources\",\n      \"score\": 6,\n      \"symbol\": \"property_list_get_property_object_006a24d0\",\n      \"va\": \"0x006a24d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-20-PERSISTENCE-BOUNDARY\",\n      \"score\": 5,\n      \"symbol\": \"PaintPersistenceBoundary_submit_004c5200\",\n      \"va\": \"0x004c5200\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DirectPropertyList\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-direct-property-clear-wave14\",\n      \"score\": 5,\n      \"symbol\": \"direct_property_list_clear_006a2b20\",\n      \"va\": \"0x006a2b20\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:PropertyMapEntry\"\n      ],\n      \"package\": \"wave6-resources\",\n      \"score\": 3,\n      \"symbol\": \"property_list_has_property_006a2470\",\n      \"va\": \"0x006a2470\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 3,\n      \"symbol\": \"editor_query_clear_flags_0093db80\",\n      \"va\": \"0x0093db80\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"DirectPropertyList\",\n  \"cluster\": \"gameglobal-misc\",\n  \"confidence\": 0.9,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"editor_query_clear_flags_0093db80\",\n        \"reconstructed\": true,\n        \"va\": \"0x0093db80\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0040a590\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0040f3f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0040fe00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004157d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004bafc0\"\n      },\n      {\n        \"name\": \"PaintPersistenceBoundary_submit_004c5200\",\n        \"reconstructed\": true,\n        \"va\": \"0x004c5200\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004f3de0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0051c6a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00522b40\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00573070\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005745c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00575270\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0057aaa0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0057ac00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005812b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005855b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0058a1e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0058a5a0\"\n      },\n      {\n        \"name\": \"Editors::cEditor::Update\",\n        \"reconstructed\": false,\n        \"va\": \"0x0058be50\"\n      },\n      {\n        \"name\": \"Editors::cEditor::HandleMessage\",\n        \"reconstructed\": false,\n        \"va\": \"0x00591fa0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0059e580\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0059e8d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00600e80\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": fals
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
  "body_end": "006a2654",
  "body_span_bytes": 181,
  "body_start": "006a25a0",
  "callees": [
    "FUN_00612db0",
    "FUN_006a19b0",
    "FUN_0093db80"
  ],
  "callers": [
    "FUN_00b9caa0",
    "FUN_00522b40",
    "FUN_0075e900",
    "Editors::cEditor::HandleMessage",
    "FUN_00f99680",
    "FUN_007a5290",
    "FUN_00f97960",
    "FUN_00cf7ad0",
    "FUN_0075f030",
    "FUN_0102f4a0",
    "FUN_00fa5610",
    "FUN_01060150",
    "FUN_00f98530",
    "FUN_0066ee50",
    "FUN_007bedb0",
    "FUN_007cb590",
    "FUN_00fe0c60",
    "FUN_00b3c1a0",
    "FUN_007bd750",
    "FUN_00b783b0",
    "FUN_00b76f10",
    "FUN_00b18f70",
    "FUN_00e00c40",
    "FUN_00b328e0",
    "FUN_00741b10",
    "FUN_00fa0400",
    "FUN_0057ac00",
    "FUN_004bafc0",
    "FUN_0074c670",
    "FUN_00f8b2b0",
    "FUN_0059e580",
    "FUN_01003a50",
    "FUN_007bbf80",
    "FUN_0040fe00",
    "FUN_007e9db0",
    "FUN_0074c910",
    "FUN_01041cf0",
    "Editors::cEditor::Update",
    "FUN_004c5200",
    "FUN_00b308f0",
    "FUN_00fa3860",
    "FUN_00f9bd00",
    "FUN_005745c0",
    "FUN_00cd3e60",
    "FUN_00ccdd70",
    "FUN_005855b0",
    "FUN_004157d0",
    "FUN_0059e8d0",
    "FUN_00fdbc20",
    "Editors::cEditor::Undo",
    "FUN_00601fd0",
    "FUN_00fc5900",
    "FUN_004f3de0",
    "FUN_0065a070",
    "FUN_006b37d0",
    "FUN_0066daf0",
    "FUN_00f98020",
    "FUN_007be430",
    "FUN_0058a1e0",
    "FUN_00f9c470",
    "FUN_0063cd30",
    "FUN_007b7ac0",
    "FUN_00687610",
    "FUN_0040a590",
    "FUN_00dd1aa0",
    "FUN_005812b0",
    "FUN_0066d430",
    "FUN_00f94480",
    "FUN_00f9fef0",
    "FUN_00b84270",
    "FUN_00f05790",
    "FUN_00f97f50",
    "FUN_00780b70",
    "FUN_007bb670",
    "FUN_0057aaa0",
    "FUN_00e38240",
    "FUN_00fdeac0",
    "FUN_00fa5cc0",
    "FUN_0065a990",
    "FUN_00600e80",
    "FUN_00ee68b0",
    "FUN_00780ab0",
    "FUN_00cf6e30",
    "FUN_00fb0e00",
    "FUN_0051c6a0",
    "FUN_00573070",
    "FUN_00634640",
    "FUN_006e8810",
    "FUN_00d58c50",
    "FUN_0102f340",
    "FUN_00575270",
    "FUN_0040f3f0",
    "FUN_0075eca0",
    "FUN_0075a260",
    "FUN_00780270",
    "FUN_00b32a10",
    "FUN_00f47b10",
    "FUN_01041d10",
    "FUN_00e00d20"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "006a25a0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_4",
      "storage": "Stack[-0x4]:1",
      "type": "undefined1"
    },
    {
      "name": "local_14",
      "storage": "Stack[-0x14]:1",
      "type": "undefined"
    }
  ],
  "locals_count": 2,
  "mode": "live",
  "name": "Prop_GetPropValueBool",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x2a25a0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined Prop_GetPropValueBool(void)",
  "size_bytes": 181,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x006a25a0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 100,
  "xrefs": [
    {
      "from": "004bb3b7"
    },
    {
      "from": "00d58ce4"
    },
    {
      "from": "004f3e1f"
    },
    {
      "from": "005234b1"
    },
    {
      "from": "0040a837"
    },
    {
      "from": "004158d9"
    },
    {
      "from": "0040f417"
    },
    {
      "from": "0041015b"
    },
    {
      "from": "00741ff1"
    },
    {
      "from": "004c549c"
    },
    {
      "from": "0051cd08"
    },
    {
      "from": "0057aab1"
    },
    {
      "from": "005745df"
    },
    {
      "from": "00575282"
    },
    {
      "from": "0057ac14"
    },
    {
      "from": "0058135f"
    },
    {
      "from": "0058a306"
    },
    {
      "from": "0058a797"
    },
    {
      "from": "00585603"
    },
    {
      "from": "0059e594"
    },
    {
      "from": "0059ea01"
    },
    {
      "from": "00573248"
    },
    {
      "from": "00600f55"
    },
    {
      "from": "006024dd"
    },
    {
      "from": "0063464d"
    },
    {
      "from": "0063cd73"
    },
    {
      "from": "0065a809"
    },
    {
      "from": "0065ae8b"
    },
    {
      "from": "0066d557"
    },
    {
      "from": "0066eb56"
    },
    {
      "from": "0066efb9"
    },
    {
      "from": "006877f1"
    },
    {
      "from": "006b3eb2"
    },
    {
      "from": "006e8a7b"
    },
    {
      "from": "006e8a8f"
    },
    {
      "from": "0074c981"
    },
    {
      "from": "0074c696"
    },
    {
      "from": "0075a271"
    },
    {
      "from": "0075e97c"
    },
    {
      "from": "0075ecf8"
    },
    {
      "from": "0075f121"
    },
    {
      "from": "0075f1c4"
    },
    {
      "from": "0075f1d7"
    },
    {
      "from": "0075f1e7"
    },
    {
      "from": "0075f1f7"
    },
    {
      "from": "0075f205"
    },
    {
      "from": "0078039c"
    },
    {
      "from": "00780ae9"
    },
    {
      "from": "00780af9"
    },
    {
      "from": "00780b23"
    },
    {
      "from": "00780b35"
    },
    {
      "from": "00780b44"
    },
    {
      "from": "00780b8e"
    },
    {
      "from": "00780b9e"
    },
    {
      "from": "00780c6c"
    },
    {
      "from": "00780c7c"
    },
    {
      "from": "00780c8c"
    },
    {
      "from": "007a52cd"
    },
    {
      "from": "007b7db8"
    },
    {
      "from": "007b7dcf"
    },
    {
      "from": "007b7de6"
    },
    {
      "from": "
[TRUNCATED]
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
  "file": "src/reconstruction/pkg20_property_adapter/direct_property_list.cpp",
  "files": [
    "reconstruction/staging/pkg20-property-adapter/direct_property_list.cpp",
    "reconstruction/staging/pkg20-property-adapter/direct_property_list.hpp",
    "reconstruction/staging/pkg20-property-adapter/direct_property_list_model_test.cpp",
    "src/reconstruction/pkg20_property_adapter/direct_property_list.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-source-wave4/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg20-property-adapter/006a25a0.json"
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
    "gate-property-direct-bool"
  ],
  "validated": 0
}
```

## semantic_hypotheses

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

```json
{
  "original_bytes": 7313,
  "preview": "{\n  \"category\": \"GAMEPLAY_SUPPORT\",\n  \"classification\": \"STRONG_SEMANTIC\",\n  \"confidence\": {\n    \"identity\": 0.94,\n    \"mechanics\": 0.99\n  },\n  \"contradictions\": [],\n  \"downstream_unlock_count\": 102,\n  \"evidence\": [\n    {\n      \"kind\": \"disassembly\",\n      \"source\": \"ghidra://SporeApp.exe@0x006a25a0\",\n      \"statement\": \"The body compares propertyID to +0x38, reads +0x3c + id*4 on the fast path, calls 0x00612db0 on the map path, and returns a normalized byte.\"\n    },\n    {\n      \"kind\": \"decompilation\",\n      \"source\": \"ghidra://SporeApp.exe@0x006a25a0\",\n      \"statement\": \"Pseudocode shows exact-key rejection, Property type/flag selection, DAT_015d115d fallback, and cleanup call.\"\n    },\n    {\n      \"kind\": \"sibling\",\n      \"source\": \"ghidra://SporeApp.exe@0x006a2660\",\n      \"statement\": \"GetDirectInt repeats the same fast-array and vector_map branches.\"\n    },\n    {\n      \"kind\": \"sibling\",\n      \"source\": \"ghidra://SporeApp.exe@0x006a2710\",\n      \"statement\": \"GetDirectFloat repeats the same fast-array and vector_map branches.\"\n    },\n    {\n      \"kind\": \"SDK\",\n      \"source\": \"/home/juanr/apps/Spore-ModAPI/Spore ModAPI/Spore/App/DirectPropertyList.h:31-46,109-145\",\n      \"statement\": \"The SDK defines the 0x54-byte DirectPropertyList and GetDirectBool fast-access contract.\"\n    },\n    {\n      \"kind\": \"repository\",\n      \"source\": \"docs/analysis/reconstruction-research-queue.md:202\",\n      \"statement\": \"The committed queue records the target as a 99-fan-in GameGlobal support bridge with three callees.\"\n    }\n  ],\n  \"family\": \"App::DirectPropertyList::GetDirectBool\",\n  \"interfaces\": {\n    \"boundaries\": {},\n    \"direct_callees\": {\n      \"count\": 3,\n      \"fan_out_external\": 0,\n      \"fan_out_internal\": 3,\n      \"items\": [\n        {\n          \"keys\": [\n            \"callsite\",\n            \"name\",\n            \"role\",\n            \"va\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"callsite\",\n            \"name\",\n            \"role\",\n            \"va\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"callsite\",\n            \"name\",\n            \"role\",\n            \"va\"\n          ]\n        }\n      ]\n    },\n    \"direct_callers\": {\n      \"canonical\": {\n        \"direct_call_references\": 144,\n        \"fan_out_external\": 0,\n        \"fan_out_internal\": 3,\n        \"gameplay_fan_in\": 0,\n        \"global_fan_in\": 14,\n        \"unique_direct_caller_functions\": 99\n      },\n      \"read_only_ghidra\": {\n        \"direct_call_xrefs\": 162,\n        \"unique_direct_caller_functions\": 99\n      },\n      \"representative\": [\n        {\n          \"keys\": [\n            \"name\",\n            \"use\",\n            \"va\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"name\",\n            \"use\",\n            \"va\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"name\",\n            \"use\",\n            \"va\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"name\",\n            \"use\",\n            \"va\"\n          ]\n        }\n      ]\n    },\n    \"globals\": [\n      {\n        \"access\": \"read\",\n        \"address\": \"0x015d115d\",\n        \"meaning\": \"false default\",\n        \"name\": \"DAT_015d115d\",\n        \"observation\": \"Target reads this byte; targeted audit found 28 xrefs to the global and no target write.\"\n      }\n    ],\n    \"structures\": [\n      {\n        \"fields\": [\n          \"vtable +0x00\",\n          \"PropertyMap +0x18 size 0x18\",\n          \"parent +0x30\",\n          \"fast count +0x38\",\n          \"values +0x3c\",\n          \"temporary Property +0x40\"\n        ],\n        \"name\": \"App::DirectPropertyList\",\n        \"size\": \"0x54\"\n      },\n      {\n        \"meaning\": \"eastl::vector_map<uint32_t, Property>; begin/end observed at +0x18/+0x1c\",\n        \"name\": \"App::PropertyList::PropertyMap\",\n        \"size\": \"0x18\"\n      },\n      {\n        \"blocker\": \"Ghidra exposes a 4-byte imported Property stub while SDK source asserts 0x14 and the target accesses +0x10/+0x12.\",\n        \"fields\": [\n          \"value storage +0x00\",\n          \"flags +0x10\",\n          \"PropertyType +0x12\"\n        ],\n        \"name\": \"App::Property\",\n        \"status\": \"partially typed\"\n      }\n    ],\n    \"vtables\": [],\n    \"worker_contract_surface\": {\n      \"failure_behavior\": [],\n      \"identity_boundary\": \"not_reported\",\n      \"inputs\": [\n        {\n          \"keys\": [\n            \"meaning\",\n            \"name\",\n            \"ordinal\",\n            \"storage\",\n            \"type\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"meaning\",\n            \"name\",\n            \"ordinal\",\n            \"storage\",\n            \"type\"\n          ]\n        }\n      ],\n      \"ordering\": [],\n      \"outputs\": [],\n      \"postconditions\": [\n        \"Fast IDs read this+0x3c + propertyID*4 and normalize to bool.\",\n        \"Other IDs use the exact-key vector_map lookup at +0x18/+0x1c.\",\n        \"A found Property is materialized through 0x006a19b0 and only Bool or Void is accepted.\",\n        \"The scratch Property at this+0x40 is cleaned through 0x0093db80 when flagged.\"\n      ],\n      \"preconditions\": [\n        \"this is a valid DirectPropertyList or ABI-compatible receiver.\",\n        \"propertyID is indexed only when less than this+0x38.\",\n        \"SDK semantics expect fast-access IDs; non-fast IDs are undefined by the SDK even though a map branch exists.\"\n      ],\n      \"purpose\": \"App::DirectPropertyList::GetDirectBool\",\n      \"return\": {\n        \"fallback\"
[TRUNCATED]
```

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
  "0x01",
  "DirectPropertyList",
  "Property",
  "PropertyAdapterServices",
  "PropertyMapEntry",
  "bool",
  "uint32_t"
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
