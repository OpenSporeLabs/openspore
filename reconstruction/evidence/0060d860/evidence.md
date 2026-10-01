# Evidence 0x0060d860

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `8e9fbfa49bf9600b0b9446638fd9e20a11c34e907f2405637c5c2ddc835efec5`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_receiver": "owner of the +0x58 gate",
  "hidden_this_register": "ECX, read at 0x0060d863",
  "ordinary_stack_argument_slots": 2,
  "receiver": true,
  "ret_form": "RET 0x8",
  "return_observation": "0x0060d915 ADD ESP,0x20 / 0x0060d918 RET 0x8 is the only exit and no EAX write is observable on any path.",
  "return_register": null,
  "return_semantics": "no value; the result of the work is observed through the resolved object, which is always released",
  "return_type": "void",
  "return_width_bytes": 0,
  "saved_registers": [
    "ESI"
  ],
  "stack_arguments": [
    {
      "read_at": "0x0060d8e2",
      "role": "argument forwarded to 0x0061fdb0",
      "slot": "entry ESP+4"
    },
    {
      "read_at": "0x0060d86d",
      "role": "mode descriptor pointer passed to 0x00552450",
      "slot": "entry ESP+8"
    }
  ],
  "stack_cleanup_bytes": 8,
  "stack_cleanup_owner": "callee",
  "termination": "0x0060d918 RET 0x8"
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
      "entry_ESP+0x8"
    ],
    "ordinary_stack_arguments": [
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
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x8",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
    "saved_registers": [
      "ESI"
    ],
    "stack_arguments": [
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
      }
    ],
    "stack_cleanup_bytes": 8,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x8"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +16, so the listing is not one path"
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
  "content_sha256": "f58fdb802d2a1603caaf6a80e35858c53c5526a798c4f30bbf205f66390f197b",
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
    "ghidra_parameter_count": 0,
    "persisted": "agrees",
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
        "obs-0039"
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
        "obs-0005"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 1,
        "observed_slots": 1,
        "total_bytes": 8
      }
    },
    {
      "based_on": [
        "obs-0003",
        "obs-0004",
        "obs-0005",
        "obs-0006",
        "obs-0015",
        "obs-0017",
        "obs-0021",
        "obs-0022",
        "obs-0027",
        "obs-0030",
        "obs-0034",
        "obs-0036"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          88
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0003",
        "obs-0004",
        "obs-0005",
        "obs-0006",
        "obs-0015",
        "obs-0017",
        "obs-0021",
        "obs-0022",
        "obs-0027",
        "obs-0030",
        "obs-0034",
        "obs-0036",
        "obs-0039"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0039"
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
        "obs-0039"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0039"
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
      "and_esp": null,
      "at": "0x0060d860",
      "ebp_is_general_register": false,
      "fp": false,
      "id": "obs-0001",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": false,
      "push_ebp_at": null,
      "raw": "SUB ESP,0x20",
      "sub": 32
    },
    {
      "at": "0x0060d860",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x20",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x0060d863",
      "count": 9,
      "first_use": 1,
      "first_write_index": 3,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "CMP dword ptr [ECX + 0x58],0x0",
      "reg": "ECX"
    },
    {
      "at": "0x0060d86d",
      "count": 19,
      "first_use": 3,
      "first_write_index": 0,
      "id": "obs-0004",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV ECX,dword ptr [ESP + 0x28]",
      "reg": "ESP"
    },
    {
      "at": "0x0060d86d",
      "base": "ESP",
      "disp": 40,
      "id": "obs-0005",
      "index": 3,
      "key": 8,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV ECX,dword ptr [ESP + 0x28]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x0060d86d",
      "definite": true,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [ESP + 0x28]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x0060d871",
      "count": 4,
      "first_use": 4,
      "first_write_index": 7,
      "id": "obs-0007",
      "index":
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
    "va": "0x00acf3e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ba4600"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c07480"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c099e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c2ed20"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c4f160"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00cdbd20"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00cf44c0"
  },
  {
    "name": "DiplomacyTransition_00d065a0",
    "reconstructed": true,
    "va": "0x00d065a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d54330"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00db5e80"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x010027b0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0102ce30"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0105b350"
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
  "count": 59,
  "instructions": [
    {
      "address": "0060d860",
      "instruction": "SUB ESP,0x20"
    },
    {
      "address": "0060d863",
      "instruction": "CMP dword ptr [ECX + 0x58],0x0"
    },
    {
      "address": "0060d867",
      "instruction": "JZ 0x0060d915"
    },
    {
      "address": "0060d86d",
      "instruction": "MOV ECX,dword ptr [ESP + 0x28]"
    },
    {
      "address": "0060d871",
      "instruction": "PUSH ESI"
    },
    {
      "address": "0060d872",
      "instruction": "LEA EAX,[ESP + 0x4]"
    },
    {
      "address": "0060d876",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0060d877",
      "instruction": "OR ESI,0xffffffff"
    },
    {
      "address": "0060d87a",
      "instruction": "PUSH ECX"
    },
    {
      "address": "0060d87b",
      "instruction": "MOV dword ptr [ESP + 0x10],ESI"
    },
    {
      "address": "0060d87f",
      "instruction": "MOV dword ptr [ESP + 0x14],ESI"
    },
    {
      "address": "0060d883",
      "instruction": "MOV dword ptr [ESP + 0xc],0x0"
    },
    {
      "address": "0060d88b",
      "instruction": "CALL 0x00552450"
    },
    {
      "address": "0060d890",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "0060d893",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "0060d895",
      "instruction": "JZ 0x0060d8af"
    },
    {
      "address": "0060d897",
      "instruction": "MOV ECX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "0060d89b",
      "instruction": "CALL 0x005507a0"
    },
    {
      "address": "0060d8a0",
      "instruction": "MOV ECX,dword ptr [EAX]"
    },
    {
      "address": "0060d8a2",
      "instruction": "MOV dword ptr [ESP + 0x8],ECX"
    },
    {
      "address": "0060d8a6",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "0060d8a9",
      "instruction": "MOV dword ptr [ESP + 0xc],EDX"
    },
    {
      "address": "0060d8ad",
      "instruction": "JMP 0x0060d8b3"
    },
    {
      "address": "0060d8af",
      "instruction": "MOV ECX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "0060d8b3",
      "instruction": "AND ECX,dword ptr [ESP + 0xc]"
    },
    {
      "address": "0060d8b7",
      "instruction": "CMP ECX,ESI"
    },
    {
      "address": "0060d8b9",
      "instruction": "JZ 0x0060d905"
    },
    {
      "address": "0060d8bb",
      "instruction": "CALL 0x0061df20"
    },
    {
      "address": "0060d8c0",
      "instruction": "MOV ESI,EAX"
    },
    {
      "address": "0060d8c2",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "0060d8c4",
      "instruction": "JZ 0x0060d905"
    },
    {
      "address": "0060d8c6",
      "instruction": "XOR ECX,ECX"
    },
    {
      "address": "0060d8c8",
      "instruction": "LEA EDX,[ESP + 0x8]"
    },
    {
      "address": "0060d8cc",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "0060d8ce",
      "instruction": "MOV word ptr [ESP + 0x22],CX"
    },
    {
      "address": "0060d8d3",
      "instruction": "PUSH EDX"
    },
    {
      "address": "0060d8d4",
      "instruction": "LEA ECX,[ESP + 0x14]"
    },
    {
      "address": "0060d8d8",
      "instruction": "MOV word ptr [ESP + 0x24],AX"
    },
    {
      "address": "0060d8dd",
      "instruction": "CALL 0x0060cfa0"
    },
    {
      "address": "0060d8e2",
      "instruction": "MOV ECX,dword ptr [ESP + 0x28]"
    },
    {
      "address": "0060d8e6",
      "instruction": "LEA EAX,[ESP + 0x10]"
    },
    {
      "address": "0060d8ea",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0060d8eb",
      "instruction": "PUSH ECX"
    },
    {
      "address": "0060d8ec",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "0060d8ee",
      "instruction": "CALL 0x0061fdb0"
    },
    {
      "address": "0060d8f3",
      "instruction": "TEST byte ptr [ESP + 0x20],0x4"
    },
    {
      "address": "0060d8f8",
      "instruction": "JZ 0x0060d905"
    },
    {
      "address": "0060d8fa",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "0060d8fc",
      "instruction": "LEA ECX,[ESP + 0x14]"
    },
    {
      "address": "0060d900",
      "instruction": "CALL 0x0093db80"
    },
    {
      "address": "0060d905",
      "instruction": "MOV ECX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "0060d909",
      "instruction": "POP ESI"
    },
    {
      "address": "0060d90a",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "0060d90c",
      "instruction": "JZ 0x0060d915"
    },
    {
      "address": "0060d90e",
      "instruction": "MOV EDX,dword ptr [ECX]"
    },
    {
      "address": "0060d910",
      "instruction": "MOV EAX,dword ptr [EDX + 0x4]"
    },
    {
      "address": "0060d913",
      "instruction": "CALL EAX"
    },
    {
      "address": "0060d915",
      "instruction": "ADD ESP,0x20"
    },
    {
      "address": "0060d918",
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
  "original_bytes": 11713,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_receiver\": \"owner of the +0x58 gate\",\n    \"hidden_this_register\": \"ECX, read at 0x0060d863\",\n    \"ordinary_stack_argument_slots\": 2,\n    \"receiver\": true,\n    \"ret_form\": \"RET 0x8\",\n    \"return_observation\": \"0x0060d915 ADD ESP,0x20 / 0x0060d918 RET 0x8 is the only exit and no EAX write is observable on any path.\",\n    \"return_register\": null,\n    \"return_semantics\": \"no value; the result of the work is observed through the resolved object, which is always released\",\n    \"return_type\": \"void\",\n    \"return_width_bytes\": 0,\n    \"saved_registers\": [\n      \"ESI\"\n    ],\n    \"stack_arguments\": [\n      {\n        \"read_at\": \"0x0060d8e2\",\n        \"role\": \"argument forwarded to 0x0061fdb0\",\n        \"slot\": \"entry ESP+4\"\n      },\n      {\n        \"read_at\": \"0x0060d86d\",\n        \"role\": \"mode descriptor pointer passed to 0x00552450\",\n        \"slot\": \"entry ESP+8\"\n      }\n    ],\n    \"stack_cleanup_bytes\": 8,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"0x0060d918 RET 0x8\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 3,\n      \"symbol\": \"editor_query_clear_flags_0093db80\",\n      \"va\": \"0x0093db80\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-13-SIM-DIPLOMACY-TRANSITIONS\",\n      \"score\": 3,\n      \"symbol\": \"DiplomacyTransition_00d065a0\",\n      \"va\": \"0x00d065a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"model_parts_apply_properties_00447150\",\n      \"va\": \"0x00447150\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_insert_004786e0\",\n      \"va\": \"0x004786e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_entry_expand_004ad6f0\",\n      \"va\": \"0x004ad6f0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"editor_query_clear_flags_0093db80\",\n        \"reconstructed\": true,\n        \"va\": \"0x0093db80\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00acf3e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ba4600\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c07480\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c099e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c2ed20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c4f160\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00cdbd20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00cf44c0\"\n      },\n      {\n        \"name\": \"DiplomacyTransition_00d065a0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00d065a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d54330\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00db5e80\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x010027b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0102ce30\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0105b350\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00acf4a9\",\n        \"direction\": \"in\",\n        \"other\": \"0x00acf3e0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00ba46e0\",\n        \"direction\": \"in\",\n        \"other\": \"0x00ba4600\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c0764c\",\n        \"direction\": \"in\",\n        \"other\": \"0x00c07480\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c07b52\",\n        \"direction\": \"in\",\n        \"other\": \"0x00c07480\",\n  
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
  "body_end": "0060d91a",
  "body_span_bytes": 187,
  "body_start": "0060d860",
  "callees": [
    "FUN_0060cfa0",
    "FUN_005507a0",
    "FUN_0061df20",
    "FUN_00552450",
    "FUN_0061fdb0",
    "FUN_0093db80"
  ],
  "callers": [
    "FUN_0105b350",
    "FUN_00d065a0",
    "FUN_00c2ed20",
    "FUN_00ba4600",
    "FUN_00cf44c0",
    "FUN_010027b0",
    "FUN_00cdbd20",
    "FUN_00c099e0",
    "FUN_00c07480",
    "FUN_00acf3e0",
    "FUN_00d54330",
    "FUN_00c4f160",
    "FUN_00db5e80",
    "FUN_0102ce30"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "0060d860",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_2",
      "storage": "Stack[-0x2]:2",
      "type": "undefined2"
    },
    {
      "name": "local_4",
      "storage": "Stack[-0x4]:2",
      "type": "undefined2"
    },
    {
      "name": "local_14",
      "storage": "Stack[-0x14]:1",
      "type": "undefined"
    },
    {
      "name": "local_18",
      "storage": "Stack[-0x18]:4",
      "type": "undefined4"
    },
    {
      "name": "local_1c",
      "storage": "Stack[-0x1c]:4",
      "type": "undefined4"
    },
    {
      "name": "local_20",
      "storage": "Stack[-0x20]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 6,
  "mode": "live",
  "name": "FUN_0060d860",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x20d860",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_0060d860(void)",
  "size_bytes": 187,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x0060d860",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 17,
  "xrefs": [
    {
      "from": "00d066d5"
    },
    {
      "from": "00c09b87"
    },
    {
      "from": "01002982"
    },
    {
      "from": "0102ceca"
    },
    {
      "from": "00c0764c"
    },
    {
      "from": "00c07b52"
    },
    {
      "from": "00c2ee9b"
    },
    {
      "from": "00acf4a9"
    },
    {
      "from": "00c4f1df"
    },
    {
      "from": "00c4f206"
    },
    {
      "from": "00cdc45f"
    },
    {
      "from": "00d545b3"
    },
    {
      "from": "00db60bc"
    },
    {
      "from": "0105b480"
    },
    {
      "from": "00ba46e0"
    },
    {
      "from": "00cf463a"
    },
    {
      "from": "00cfd5ab"
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
  "files": [
    "reconstruction/staging/wave13-w1-core-b07/0060d860_resolve_and_submit_keyed_work.cpp",
    "reconstruction/staging/wave13-w1-core-b07/b07_model_test.cpp",
    "reconstruction/staging/wave13-w1-core-b07/b07_opaque_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-core-b07/0060d860.json"
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
    "No original-process trace exists for this address.",
    "The domain meaning of the keyed work, and whether the AND-based emptiness test ever misfires on real data, need runtime observation.",
    "The virtual release at vtable slot +0x4 can only be resolved with a receiver trace that captures the concrete object's vtable."
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
  "status": "unresolved"
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

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## Conflicts

```json
[]
```
