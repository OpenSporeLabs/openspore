# Evidence 0x0040ccb0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `9975a67935c1b350d88a3b1f6ec9eca8ecaed1ffc9a0921d34fe584f98d9a47f`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "__thiscall observed",
  "hidden_this_register": "ECX",
  "hidden_this_type": "Transform*",
  "return_register": "EAX",
  "return_type": "Transform*",
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "other",
      "observed_use": "Reads the other transform offset, scale, flags, and rotation.",
      "position": 1,
      "type": "Transform*",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 4
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
        "ebp_offset": "EBP+0x8",
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
    "return_register": "XMM0",
    "return_semantics": "float_or_x87_in_XMM0",
    "saved_registers": [
      "EBP",
      "EDI",
      "ESI"
    ],
    "stack_arguments": [
      {
        "ebp_offset": "EBP+0x8",
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
    "sret_vs_out_param: entry slot 0 is written through a pointer"
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
  "content_sha256": "4c9acc013b0ab5f4e7066f794a6b2bf642b02a2ec1c11d9620b9a1b453511d48",
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
    "ghidra_parameter_count": 2,
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
        "obs-0049"
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
        "obs-0025",
        "obs-0037",
        "obs-0041"
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
        "obs-0008",
        "obs-0009",
        "obs-0013",
        "obs-0014",
        "obs-0020",
        "obs-0025",
        "obs-0036",
        "obs-0038",
        "obs-0041"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          0,
          2,
          16
        ],
        "register": "ECX",
        "written_through": 3
      }
    },
    {
      "based_on": [
        "obs-0008",
        "obs-0009",
        "obs-0013",
        "obs-0014",
        "obs-0020",
        "obs-0025",
        "obs-0036",
        "obs-0038",
        "obs-0041",
        "obs-0049"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0015",
        "obs-0025",
        "obs-0037",
        "obs-0041"
      ],
      "claim": "a hidden struct-return pointer is a hypothesis only: entry slot 0 is written through a pointer",
      "confidence": "INFERRED",
      "id": "S1",
      "value": {
        "ambiguity": "sret_vs_out_param",
        "present": null,
        "slot": 4
      }
    },
    {
      "based_on": [
        "obs-0049"
      ],
      "claim": "in MSVC x86 a hidden struct-return pointer is always stack slot 0 while this is in ECX, so the two never contend",
      "confidence": "APPROXIMATION",
      "id": "S3",
      "value": {
        "ordering": "not_applicable"
      }
    },
    {
      "based_on": [
        "obs-0002"
      ],
      "claim": "the return value is carried in XMM0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "XMM0"
    }
  ],
  "observations": [
    {
      "at": "0x0040ccb0",
      "count": 25,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH EBP",
      "reg": "EBP"
    },
    {
      "and_esp": null,
      "at": "0x0040ccb0",
      "ebp_is_general_register": true,
      "fp": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": true,
      "mov_ebp_esp_at": 1,
      "push_ebp": true,
      "push_ebp_at": 0,
      "raw": "PUSH EBP",
      "sub": 72
    },
    {
      "at": "0x0040ccb1",
      "count": 1,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EBP,ESP",
      "reg": "ESP"
    },
    {
      "at": "0x0040ccb1",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EBP,ESP",
      "reg": "EBP",
      "write_kind": "reg"
    },
    {
      "at": "0x0040ccb3",
      "definite": true,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x48",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x0040ccb6",
      "count": 2,
      "first_use": 3,
      "first_write_index": 44,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_
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
    "va": "0x0040aeb0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x004363d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0043d240"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0043d420"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0043d690"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00441440"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005f6260"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x006271a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00748ad0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0074a290"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0074ac80"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x007507e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00752620"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b02b90"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b134a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bd2af0"
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
  "count": 71,
  "instructions": [
    {
      "address": "0040ccb0",
      "instruction": "PUSH EBP"
    },
    {
      "address": "0040ccb1",
      "instruction": "MOV EBP,ESP"
    },
    {
      "address": "0040ccb3",
      "instruction": "SUB ESP,0x48"
    },
    {
      "address": "0040ccb6",
      "instruction": "PUSH ESI"
    },
    {
      "address": "0040ccb7",
      "instruction": "PUSH EDI"
    },
    {
      "address": "0040ccb8",
      "instruction": "MOV dword ptr [EBP + -0x48],ECX"
    },
    {
      "address": "0040ccbb",
      "instruction": "MOV EAX,dword ptr [EBP + -0x48]"
    },
    {
      "address": "0040ccbe",
      "instruction": "ADD EAX,0x14"
    },
    {
      "address": "0040ccc1",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0040ccc2",
      "instruction": "MOV ECX,dword ptr [EBP + -0x48]"
    },
    {
      "address": "0040ccc5",
      "instruction": "ADD ECX,0x10"
    },
    {
      "address": "0040ccc8",
      "instruction": "PUSH ECX"
    },
    {
      "address": "0040ccc9",
      "instruction": "MOV EDX,dword ptr [EBP + 0x8]"
    },
    {
      "address": "0040cccc",
      "instruction": "ADD EDX,0x4"
    },
    {
      "address": "0040cccf",
      "instruction": "PUSH EDX"
    },
    {
      "address": "0040ccd0",
      "instruction": "LEA EAX,[EBP + -0xc]"
    },
    {
      "address": "0040ccd3",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0040ccd4",
      "instruction": "CALL 0x0041dca0"
    },
    {
      "address": "0040ccd9",
      "instruction": "ADD ESP,0xc"
    },
    {
      "address": "0040ccdc",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0040ccdd",
      "instruction": "LEA ECX,[EBP + -0x18]"
    },
    {
      "address": "0040cce0",
      "instruction": "PUSH ECX"
    },
    {
      "address": "0040cce1",
      "instruction": "CALL 0x0041daf0"
    },
    {
      "address": "0040cce6",
      "instruction": "ADD ESP,0xc"
    },
    {
      "address": "0040cce9",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0040ccea",
      "instruction": "MOV EDX,dword ptr [EBP + -0x48]"
    },
    {
      "address": "0040cced",
      "instruction": "ADD EDX,0x4"
    },
    {
      "address": "0040ccf0",
      "instruction": "PUSH EDX"
    },
    {
      "address": "0040ccf1",
      "instruction": "CALL 0x0041ddb0"
    },
    {
      "address": "0040ccf6",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "0040ccf9",
      "instruction": "MOV EAX,dword ptr [EBP + -0x48]"
    },
    {
      "address": "0040ccfc",
      "instruction": "ADD EAX,0x14"
    },
    {
      "address": "0040ccff",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0040cd00",
      "instruction": "MOV ECX,dword ptr [EBP + 0x8]"
    },
    {
      "address": "0040cd03",
      "instruction": "ADD ECX,0x14"
    },
    {
      "address": "0040cd06",
      "instruction": "PUSH ECX"
    },
    {
      "address": "0040cd07",
      "instruction": "LEA EDX,[EBP + -0x3c]"
    },
    {
      "address": "0040cd0a",
      "instruction": "PUSH EDX"
    },
    {
      "address": "0040cd0b",
      "instruction": "CALL 0x0041de20"
    },
    {
      "address": "0040cd10",
      "instruction": "ADD ESP,0xc"
    },
    {
      "address": "0040cd13",
      "instruction": "MOV dword ptr [EBP + -0x44],EAX"
    },
    {
      "address": "0040cd16",
      "instruction": "MOV EAX,dword ptr [EBP + -0x48]"
    },
    {
      "address": "0040cd19",
      "instruction": "ADD EAX,0x14"
    },
    {
      "address": "0040cd1c",
      "instruction": "MOV dword ptr [EBP + -0x40],EAX"
    },
    {
      "address": "0040cd1f",
      "instruction": "MOV ESI,dword ptr [EBP + -0x44]"
    },
    {
      "address": "0040cd22",
      "instruction": "MOV ECX,0x9"
    },
    {
      "address": "0040cd27",
      "instruction": "MOV EDI,dword ptr [EBP + -0x40]"
    },
    {
      "address": "0040cd2a",
      "instruction": "MOVSD.REP ES:EDI,ESI"
    },
    {
      "address": "0040cd2c",
      "instruction": "MOV ECX,dword ptr [EBP + -0x48]"
    },
    {
      "address": "0040cd2f",
      "instruction": "MOV EDX,dword ptr [EBP + 0x8]"
    },
    {
      "address": "0040cd32",
      "instruction": "MOVSS XMM0,dword ptr [ECX + 0x10]"
    },
    {
      "address": "0040cd37",
      "instruction": "MULSS XMM0,dword ptr [EDX + 0x10]"
    },
    {
      "address": "0040cd3c",
      "instruction": "MOV EAX,dword ptr [EBP + -0x48]"
    },
    {
      "address": "0040cd3f",
      "instruction": "MOVSS dword ptr [EAX + 0x10],XMM0"
    },
    {
      "address": "0040cd44",
      "instruction": "MOV ECX,dword ptr [EBP + 0x8]"
    },
    {
      "address": "0040cd47",
      "instruction": "MOVZX EDX,word ptr [ECX]"
    },
    {
      "address": "0040cd4a",
      "instruction": "MOV EAX,dword ptr [EBP + -0x48]"
    },
    {
      "address": "0040cd4d",
      "instruction": "MOVZX ECX,word ptr [EAX]"
    },
    {
      "address": "0040cd50",
      "instruction": "OR ECX,EDX"
    },
    {
      "address": "0040cd52",
      "instruction": "MOV EDX,dword ptr [EBP + -0x48]"
    },
    {
      "address": "0040cd55",
      "instruction": "MOV word ptr [EDX],CX"
    },
    {
      "address": "0040cd58",
      "instruction": "MOV EAX,dword ptr [EBP + -0x48]"
    },
    {
      "address": "0040cd5b",
      "instruction": "MOV CX,word ptr [EAX + 0x2]"
    },
    {
      "address": "0040cd5f",
      "instruction": "ADD CX,0x1"
    },
    {
      "address": "0040cd63",
      "instruction": "MOV EDX,dword ptr [EBP + -0x48]"
    },
    {
      "address": "0040cd66",
      "instruction": "MOV word ptr [EDX + 0x2],CX"
    },
    {
      "address": "0040cd6a",
      "instruction": "POP EDI"
    },
    {
      "address": "0040cd6b",
      "instruction": "POP ESI"
    },
    {
      "address": "0040cd6c",
      "instruction": "MOV ESP,EBP"
    },
    {
      "address": "0040cd6e",
      "instruction": "POP EBP"
    },
    {
      "address": "0040cd6f",
      "i
[TRUNCATED]
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
  "original_bytes": 13127,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"__thiscall observed\",\n    \"hidden_this_register\": \"ECX\",\n    \"hidden_this_type\": \"Transform*\",\n    \"return_register\": \"EAX\",\n    \"return_type\": \"Transform*\",\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"name\": \"other\",\n        \"observed_use\": \"Reads the other transform offset, scale, flags, and rotation.\",\n        \"position\": 1,\n        \"type\": \"Transform*\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 4\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\"\n      ],\n      \"package\": \"WAVE6-PRESENTATION\",\n      \"score\": 14,\n      \"symbol\": \"graphics_global_state_set_transform_005291f0\",\n      \"va\": \"0x005291f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"WAVE6-PRESENTATION\",\n      \"score\": 10,\n      \"symbol\": \"renderware_mesh_set_indices_count_011f96e0\",\n      \"va\": \"0x011f96e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"WAVE6-PRESENTATION\",\n      \"score\": 10,\n      \"symbol\": \"renderware_mesh_set_index_buffer_011f9710\",\n      \"va\": \"0x011f9710\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-WAVE6-CONTAINERS-MEMORY\",\n      \"score\": 2,\n      \"symbol\": \"wave6_reference_00432a50\",\n      \"va\": \"0x00432a50\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-20-RESOURCE-ADAPTER\",\n      \"score\": 2,\n      \"symbol\": \"TexturePtr_Set\",\n      \"va\": \"0x00576650\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 2,\n      \"symbol\": \"editor_query_reset_005dd750\",\n      \"va\": \"0x005dd750\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 2,\n      \"symbol\": \"editor_query_dispatch_005dfd00\",\n      \"va\": \"0x005dfd00\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"wave6-resources\",\n      \"score\": 2,\n      \"symbol\": \"property_list_has_property_006a2470\",\n      \"va\": \"0x006a2470\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Scaled-offset, helper argument order, offset accumulation, rotation copy, scale product, flag OR, count increment, and receiver return are exact; helper semantics and runtime inputs remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"pass_after_repair\",\n  \"blocked\": false,\n  \"blockers\": [\n    \"No runtime transform trace is available.\",\n    \"The two helper wrappers are decompiler-conflicted and are represented as package-local ports.\"\n  ],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"Transform\",\n  \"cluster\": null,\n  \"confidence\": 0.93,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0040aeb0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004363d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0043d240\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0043d420\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0043d690\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00441440\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005f6260\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x006271a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00748ad0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0074a290\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0074ac80\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007507e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00752620\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b02b90\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b134a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bd2af0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d265c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d266c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d26c90\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e62380\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e725c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e76af0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e76d70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\
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
  "body_end": "0040cd71",
  "body_span_bytes": 194,
  "body_start": "0040ccb0",
  "callees": [
    "FUN_0041ddb0",
    "FUN_0041dca0",
    "_Unchecked_idl0<>",
    "_Unchecked_idl0<>"
  ],
  "callers": [
    "FUN_00e62380",
    "FUN_0043d690",
    "FUN_004363d0",
    "FUN_0074ac80",
    "FUN_00b134a0",
    "FUN_00e725c0",
    "FUN_007507e0",
    "FUN_00e76d70",
    "FUN_00f523a0",
    "FUN_0043d240",
    "FUN_006271a0",
    "FUN_00e7aa20",
    "FUN_00bd2af0",
    "FUN_0043d420",
    "FUN_0074a290",
    "FUN_00d265c0",
    "FUN_00748ad0",
    "FUN_00752620",
    "FUN_00d266c0",
    "FUN_0040aeb0",
    "FUN_00441440",
    "FUN_00e76af0",
    "FUN_00b02b90",
    "FUN_005f6260",
    "FUN_00d26c90"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "0040ccb0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_10",
      "storage": "Stack[-0x10]:1",
      "type": "undefined"
    },
    {
      "name": "local_1c",
      "storage": "Stack[-0x1c]:1",
      "type": "undefined"
    },
    {
      "name": "local_40",
      "storage": "Stack[-0x40]:1",
      "type": "undefined"
    },
    {
      "name": "local_44",
      "storage": "Stack[-0x44]:4",
      "type": "undefined4"
    },
    {
      "name": "local_48",
      "storage": "Stack[-0x48]:4",
      "type": "undefined4"
    },
    {
      "name": "local_4c",
      "storage": "Stack[-0x4c]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 6,
  "mode": "live",
  "name": "Transform::PreTransformBy",
  "namespace": "Transform",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 2,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "Transform *"
    },
    {
      "name": "other",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "Transform *"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "Transform *",
  "return_type_resolved": true,
  "rva": "0xccb0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "Transform * Transform::PreTransformBy(Transform * this, Transform * other)",
  "size_bytes": 194,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x0040ccb0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 33,
  "xrefs": [
    {
      "from": "0043d5c0"
    },
    {
      "from": "0043da52"
    },
    {
      "from": "00446ded"
    },
    {
      "from": "00436474"
    },
    {
      "from": "0043d2e8"
    },
    {
      "from": "0040b1dc"
    },
    {
      "from": "0040c6e5"
    },
    {
      "from": "0040c815"
    },
    {
      "from": "0040c9e6"
    },
    {
      "from": "0040ca74"
    },
    {
      "from": "005f6433"
    },
    {
      "from": "00748b31"
    },
    {
      "from": "006271e2"
    },
    {
      "from": "0074a345"
    },
    {
      "from": "0074aefd"
    },
    {
      "from": "00751368"
    },
    {
      "from": "00b02c14"
    },
    {
      "from": "00b136a8"
    },
    {
      "from": "00bd31e4"
    },
    {
      "from": "00d266a9"
    },
    {
      "from": "00d26e83"
    },
    {
      "from": "00d26771"
    },
    {
      "from": "00e6240c"
    },
    {
      "from": "00e7278e"
    },
    {
      "from": "00e77198"
    },
    {
      "from": "00e7ab3c"
    },
    {
      "from": "00e76ccf"
    },
    {
      "from": "005f58cb"
    },
    {
      "from": "0074a5da"
    },
    {
      "from": "0075279a"
    },
    {
      "from": "00752b10"
    },
    {
      "from": "00e90acf"
    },
    {
      "from": "00f525a8"
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
  "global:No direct gameplay-global data references were identified in the target body."
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/wave6_presentation/presentation_boundary.cpp",
  "files": [
    "src/reconstruction/wave6_presentation/presentation_boundary.cpp",
    "src/reconstruction/wave6_presentation/presentation_boundary.hpp",
    "src/reconstruction/wave6_presentation/presentation_boundary_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/wave6-presentation/0040ccb0.json"
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
    "gate-transform-helper-semantics-and-runtime-inputs"
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
  "Matrix3",
  "Transform",
  "Transform*",
  "TransformBoundaryPorts",
  "Vector3"
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
