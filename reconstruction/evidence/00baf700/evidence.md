# Evidence 0x00baf700

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `e96e497e24eb045efe28654cf90bbd01bd73d2a78b3f07bb4312a3418506f635`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__stdcall encoding (one callee-cleaned stack dword); the incoming ECX is preserved and never read, so the function is best modelled as a static member taking one argument",
  "hidden_receiver": "unread: the incoming ECX is pushed at 0x00baf700 and popped at 0x00baf734/0x00baf789 without ever being dereferenced or tested",
  "hidden_this_register": "ECX, saved and restored but never read; the reconstruction therefore does not consume it",
  "ordinary_stack_argument_slots": 1,
  "receiver": "present but unread",
  "ret_form": "RET 0x4 (at both 0x00baf735 and 0x00baf78a)",
  "return_observation": "0x00baf730: MOV EAX,[EAX + 0x14] returns the mapped value on a hit; 0x00baf784: MOV EAX,[EAX] returns the RE-READ slot content on a miss, not the earlier pointer. Both exits write the full dword.",
  "return_register": "EAX",
  "return_semantics": "the interned object registered for the hashed name: node->value on a hit, or the value the factory's +0x2C slot stored into the node on a miss",
  "return_type": "std::uint32_t",
  "return_width_bytes": 4,
  "saved_registers": [
    "EBX",
    "ECX",
    "ESI",
    "EDI"
  ],
  "stack_arguments": [
    {
      "instruction": "0x00baf701: MOV ECX,dword ptr [ESP + 0x8] after the PUSH ECX, i.e. the entry stack argument",
      "offset": "ESP+0x4 at entry",
      "role": "selector token, passed as the ECX receiver of the callee 0x00c30e80 and stored as the map key",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "callee",
  "termination": "two exits, 0x00baf735 on the hit path and 0x00baf78a on the miss path"
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
    "ordinary_stack_argument_slots": [
      "entry_ESP+0x4"
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
      }
    ],
    "ret_form": "RET 0x4",
    "return_register": "EAX",
    "return_semantics": "pointer_like_in_EAX",
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
      }
    ],
    "stack_cleanup_bytes": 4,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x4"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +20, so the listing is not one path",
    "receiver_not_determinable: ecx_reassigned_before_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_reassigned_before_deref), and the convention rule that would apply discriminates on receiver absence"
  ],
  "cleanup": {
    "bytes": 4,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x4",
    "side": "callee"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "6351f1139a409debca8a971d4f05799ef80d4906dea16b709496db9749cc6012",
  "conventions": {
    "ambiguities": [
      "receiver_undetermined"
    ],
    "calling_convention": null,
    "candidate_conventions": [
      "__stdcall",
      "__thiscall"
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
    "persisted_calling_convention": "__stdcall encoding (one callee-cleaned stack dword); the incoming ECX is preserved and never read, so the function is best modelled as a static member taking one argument"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 2,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0017",
        "obs-0035"
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
        "obs-0003",
        "obs-0009",
        "obs-0011",
        "obs-0022"
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
        "obs-0001",
        "obs-0002",
        "obs-0003",
        "obs-0004",
        "obs-0010",
        "obs-0016",
        "obs-0034"
      ],
      "claim": "the register receiver is undetermined: ecx_reassigned_before_deref",
      "confidence": "UNKNOWN",
      "id": "R0",
      "value": {
        "reason": "ecx_reassigned_before_deref",
        "register": null
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0002",
        "obs-0003",
        "obs-0004",
        "obs-0010",
        "obs-0016",
        "obs-0034"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_reassigned_before_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0017",
        "obs-0035"
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
        "obs-0035"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0017",
        "obs-0035"
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
      "at": "0x00baf700",
      "count": 4,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00baf701",
      "count": 7,
      "first_use": 1,
      "first_write_index": null,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ECX,dword ptr [ESP + 0x8]",
      "reg": "ESP"
    },
    {
      "at": "0x00baf701",
      "base": "ESP",
      "disp": 8,
      "id": "obs-0003",
      "index": 1,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV ECX,dword ptr [ESP + 0x8]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00baf701",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [ESP + 0x8]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00baf705",
      "count": 3,
      "first_use": 2,
      "first_write_index": 4,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00baf706",
      "id": "obs-0006",
      "index": 3,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00c30e80",
      "target": "0x00c30e80"
    },
    {
      "at": "0x00baf70b",
      "count": 11,
      "first_use": 4,
      "first_write_index": 12,
      "id": "obs-0007",
      "index": 4,
      "kind": "
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "map_int_whatever_find",
    "reconstructed": true,
    "va": "0x00e5c780"
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
    "va": "0x00bd9a80"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c322f0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c35320"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c75940"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c75d70"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c76800"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c784c0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00fed640"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ff5930"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x01030930"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x010309c0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x01030a30"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x01030aa0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x010407d0"
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
  "count": 52,
  "instructions": [
    {
      "address": "00baf700",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00baf701",
      "instruction": "MOV ECX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "00baf705",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00baf706",
      "instruction": "CALL 0x00c30e80"
    },
    {
      "address": "00baf70b",
      "instruction": "MOV EBX,EAX"
    },
    {
      "address": "00baf70d",
      "instruction": "LEA EAX,[ESP + 0xc]"
    },
    {
      "address": "00baf711",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00baf712",
      "instruction": "LEA ECX,[ESP + 0x8]"
    },
    {
      "address": "00baf716",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00baf717",
      "instruction": "MOV ECX,0x156c61c"
    },
    {
      "address": "00baf71c",
      "instruction": "MOV dword ptr [ESP + 0x14],EBX"
    },
    {
      "address": "00baf720",
      "instruction": "CALL 0x00e5c780"
    },
    {
      "address": "00baf725",
      "instruction": "MOV EAX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "00baf729",
      "instruction": "CMP EAX,0x156c620"
    },
    {
      "address": "00baf72e",
      "instruction": "JZ 0x00baf738"
    },
    {
      "address": "00baf730",
      "instruction": "MOV EAX,dword ptr [EAX + 0x14]"
    },
    {
      "address": "00baf733",
      "instruction": "POP EBX"
    },
    {
      "address": "00baf734",
      "instruction": "POP ECX"
    },
    {
      "address": "00baf735",
      "instruction": "RET 0x4"
    },
    {
      "address": "00baf738",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00baf739",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00baf73a",
      "instruction": "CALL 0x0067de30"
    },
    {
      "address": "00baf73f",
      "instruction": "LEA EDX,[ESP + 0x14]"
    },
    {
      "address": "00baf743",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00baf744",
      "instruction": "MOV ECX,0x156c61c"
    },
    {
      "address": "00baf749",
      "instruction": "MOV EDI,EAX"
    },
    {
      "address": "00baf74b",
      "instruction": "CALL 0x00dd85c0"
    },
    {
      "address": "00baf750",
      "instruction": "MOV ESI,EAX"
    },
    {
      "address": "00baf752",
      "instruction": "MOV ECX,dword ptr [ESI]"
    },
    {
      "address": "00baf754",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00baf756",
      "instruction": "JZ 0x00baf765"
    },
    {
      "address": "00baf758",
      "instruction": "MOV dword ptr [ESI],0x0"
    },
    {
      "address": "00baf75e",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "00baf760",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "00baf763",
      "instruction": "CALL EDX"
    },
    {
      "address": "00baf765",
      "instruction": "MOV EAX,dword ptr [EDI]"
    },
    {
      "address": "00baf767",
      "instruction": "MOV EDX,dword ptr [EAX + 0x2c]"
    },
    {
      "address": "00baf76a",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00baf76b",
      "instruction": "PUSH 0x568de14"
    },
    {
      "address": "00baf770",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00baf771",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00baf773",
      "instruction": "CALL EDX"
    },
    {
      "address": "00baf775",
      "instruction": "LEA EAX,[ESP + 0x14]"
    },
    {
      "address": "00baf779",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00baf77a",
      "instruction": "MOV ECX,0x156c61c"
    },
    {
      "address": "00baf77f",
      "instruction": "CALL 0x00dd85c0"
    },
    {
      "address": "00baf784",
      "instruction": "MOV EAX,dword ptr [EAX]"
    },
    {
      "address": "00baf786",
      "instruction": "POP EDI"
    },
    {
      "address": "00baf787",
      "instruction": "POP ESI"
    },
    {
      "address": "00baf788",
      "instruction": "POP EBX"
    },
    {
      "address": "00baf789",
      "instruction": "POP ECX"
    },
    {
      "address": "00baf78a",
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
  "original_bytes": 12477,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__stdcall encoding (one callee-cleaned stack dword); the incoming ECX is preserved and never read, so the function is best modelled as a static member taking one argument\",\n    \"hidden_receiver\": \"unread: the incoming ECX is pushed at 0x00baf700 and popped at 0x00baf734/0x00baf789 without ever being dereferenced or tested\",\n    \"hidden_this_register\": \"ECX, saved and restored but never read; the reconstruction therefore does not consume it\",\n    \"ordinary_stack_argument_slots\": 1,\n    \"receiver\": \"present but unread\",\n    \"ret_form\": \"RET 0x4 (at both 0x00baf735 and 0x00baf78a)\",\n    \"return_observation\": \"0x00baf730: MOV EAX,[EAX + 0x14] returns the mapped value on a hit; 0x00baf784: MOV EAX,[EAX] returns the RE-READ slot content on a miss, not the earlier pointer. Both exits write the full dword.\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"the interned object registered for the hashed name: node->value on a hit, or the value the factory's +0x2C slot stored into the node on a miss\",\n    \"return_type\": \"std::uint32_t\",\n    \"return_width_bytes\": 4,\n    \"saved_registers\": [\n      \"EBX\",\n      \"ECX\",\n      \"ESI\",\n      \"EDI\"\n    ],\n    \"stack_arguments\": [\n      {\n        \"instruction\": \"0x00baf701: MOV ECX,dword ptr [ESP + 0x8] after the PUSH ECX, i.e. the entry stack argument\",\n        \"offset\": \"ESP+0x4 at entry\",\n        \"role\": \"selector token, passed as the ECX receiver of the callee 0x00c30e80 and stored as the map key\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"two exits, 0x00baf735 on the hit path and 0x00baf78a on the miss path\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-20-GAMEGLOBAL\",\n      \"score\": 3,\n      \"symbol\": \"map_int_whatever_find\",\n      \"va\": \"0x00e5c780\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"map_int_whatever_find\",\n        \"reconstructed\": true,\n        \"va\": \"0x00e5c780\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bd9a80\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c322f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c35320\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c75940\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c75d70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c76800\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c784c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00fed640\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ff5930\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x01030930\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x010309c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x01030a30\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x01030aa0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x010407d0\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00bd9ad9\",\n        \"direction\": \"in\",\n        \"other\": \"0x00bd9a80\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c323f7\",\n        \"direction\": \"in\",\n        \"other\": \"0x00c322f0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c356b2\",\n        \"direction\": \"in\",\n        \"other\": \"0x00c35320\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c7594f\",\n        \"direction\": \"in\",\n        \"other\": \"0x00c75940\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c75d9f\",\n        \"direction\": \"in\",\n        \"other\": \"0x00c75d70\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c76977\",\n        \"direction\": \"in\",\n        \"other\": \"0x00c76800\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c78568\",\n        \"direction\": \"in\",\n        \"other\": \"0x00c784c0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c785cb\",\n        \"direction\": \"in\",\n        \"other\": \"0x00c784c0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00fed75b\",\n        \"direction\": \"in\",\n        \"other\": \"0x00fed640\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00ff5997\",\n        \"direction\": \"in\",\n        \"other\": \"0x00ff5930\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\":
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
  "body_end": "00baf78c",
  "body_span_bytes": 141,
  "body_start": "00baf700",
  "callees": [
    "FUN_0067de30",
    "FUN_00dd85c0",
    "FUN_00c30e80",
    "map_int_whatever_find"
  ],
  "callers": [
    "FUN_00c75940",
    "FUN_00c75d70",
    "FUN_01030930",
    "FUN_01030a30",
    "FUN_00c76800",
    "FUN_00c322f0",
    "FUN_010407d0",
    "FUN_00bd9a80",
    "FUN_00ff5930",
    "FUN_010309c0",
    "FUN_00c784c0",
    "FUN_01030aa0",
    "FUN_00c35320",
    "FUN_00fed640"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00baf700",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_4",
      "storage": "Stack[-0x4]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 1,
  "mode": "live",
  "name": "FUN_00baf700",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x7af700",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00baf700(void)",
  "size_bytes": 141,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00baf700",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 15,
  "xrefs": [
    {
      "from": "00c356b2"
    },
    {
      "from": "00c78568"
    },
    {
      "from": "00c785cb"
    },
    {
      "from": "00c75d9f"
    },
    {
      "from": "00c7594f"
    },
    {
      "from": "00fed75b"
    },
    {
      "from": "00c323f7"
    },
    {
      "from": "00c76977"
    },
    {
      "from": "01030966"
    },
    {
      "from": "01030a08"
    },
    {
      "from": "01030a78"
    },
    {
      "from": "01030ae8"
    },
    {
      "from": "010407df"
    },
    {
      "from": "00ff5997"
    },
    {
      "from": "00bd9ad9"
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
    "reconstruction/staging/wave13-w1-core-b06/baf700_interned_object_get_or_create.cpp",
    "reconstruction/staging/wave13-w1-core-b06/sim_core_b06_model_test.cpp",
    "reconstruction/staging/wave13-w1-core-b06/sim_core_b06_opaque.hpp",
    "reconstruction/staging/wave13-w1-core-b06/sim_core_b06_ports_model.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-core-b06/00baf700.json"
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
    "No original-process trace has ever been captured for this function; the original Cell stage has never been entered in any recorded run. Every claim here is static.",
    "The create path cannot execute before the factory host at 0x015FD8A8 is installed, and that host is zero in the shipping image. A differential test must first establish the host is live, then observe the first miss and the exact object the factory stores.",
    "The low-byte keying collision risk in 0x00dd85c0 can only be settled by enumerating the runtime hashed names 0x00c30cc0 can produce and checking for shared top 24 bits.",
    "The re-fetch after the factory call is a correctness claim about tree rebalancing. Confirming it needs a case where the factory inserts enough nodes to force a rebalance, which cannot be provoked statically.",
    "The zero-before-release ordering is a re-entrancy and observability claim. Confirming it needs a concurrent reader of 0x0156C61C during the release, which only a runtime harness can arrange."
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
  "std::uint32_t"
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
