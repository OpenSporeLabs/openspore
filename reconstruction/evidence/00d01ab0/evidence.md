# Evidence 0x00d01ab0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `d5cc11b7f3f6526b09cc74d4060614aad30a9b5592e5cea6d38b14adbae5f2fe`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "thiscall",
  "hidden_this": "ECX OpaqueRelationshipManager* receiver",
  "return_register": "EAX",
  "return_semantics": "Returns receiver+0x24 fallback or selected record+0x04 map pointer; normal failure is a non-null fallback address.",
  "return_width_bytes": 4,
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "position": 1,
      "type": "std::uint32_t",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x08",
      "position": 2,
      "type": "std::uint32_t",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 8
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
      "entry_ESP+0x4",
      "entry_ESP+0x8"
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
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x8",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
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
      }
    ],
    "stack_cleanup_bytes": 8,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x8"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -8, so the listing is not one path"
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
  "content_sha256": "b52b3eabe3e8231617e4599e2c34afa8aaae76937ecd0e052463b265cf8795c9",
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
    "persisted_calling_convention": "thiscall"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0030",
        "obs-0033"
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
        "obs-0005",
        "obs-0008",
        "obs-0013",
        "obs-0017",
        "obs-0023",
        "obs-0025"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 2,
        "total_bytes": 8
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007",
        "obs-0008",
        "obs-0021"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          156,
          160,
          176
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007",
        "obs-0008",
        "obs-0021",
        "obs-0030",
        "obs-0033"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0030",
        "obs-0033"
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
        "obs-0030",
        "obs-0033"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0030",
        "obs-0033"
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
      "at": "0x00d01ab0",
      "count": 5,
      "first_use": 0,
      "first_write_index": 3,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00d01ab1",
      "count": 4,
      "first_use": 1,
      "first_write_index": 10,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00d01ab2",
      "count": 9,
      "first_use": 2,
      "first_write_index": 19,
      "id": "obs-0003",
      "index": 2,
      "kind": "REG_READ",
      "raw": "LEA EAX,[ESP + 0x10]",
      "reg": "EAX"
    },
    {
      "at": "0x00d01ab2",
      "count": 6,
      "first_use": 2,
      "first_write_index": 8,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "LEA EAX,[ESP + 0x10]",
      "reg": "ESP"
    },
    {
      "at": "0x00d01ab2",
      "base": "ESP",
      "disp": 16,
      "id": "obs-0005",
      "index": 2,
      "key": 8,
      "kind": "STACK_SLOT_READ",
      "raw": "LEA EAX,[ESP + 0x10]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00d01ab6",
      "count": 6,
      "first_use": 3,
      "first_write_index": 26,
      "id": "obs-0
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "context_word_read_00ce6950",
    "reconstructed": true,
    "va": "0x00ce6950"
  },
  {
    "name": "FUN_010212a0",
    "reconstructed": true,
    "va": "0x010212a0"
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
    "va": "0x00d01b50"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d01b80"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d01bb0"
  },
  {
    "name": "DiplomacyTransition_00d01e30",
    "reconstructed": true,
    "va": "0x00d01e30"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d01f20"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d01f50"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d01fb0"
  },
  {
    "name": "RelationshipManager_IsAllied2_00d01ff0",
    "reconstructed": true,
    "va": "0x00d01ff0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d02050"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d03860"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d038a0"
  },
  {
    "name": "DiplomacyTransition_00d038e0",
    "reconstructed": true,
    "va": "0x00d038e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d03d70"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d05830"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d05a20"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d06240"
  }
]
```

## contradictions

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "anchors": [
      "0x00d2e480",
      "0x00d2e480",
      "0x00d01410",
      "0x00d01410",
      "0x00d01ab0",
      "0x00d01ab0",
      "0x00d01e30",
      "0x00d01e30",
      "0x00d01f50",
      "0x00d01f50",
      "0x00d01ff0",
      "0x00d01ff0",
      "0x00d038e0",
      "0x00d038e0",
      "0x00d065a0",
      "0x00d065a0"
    ],
    "conflict_id": "U-003-civilization-progression",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The technology-level surface is recorded, but the binary writer/callback chain from one level to the next is not recovered.",
    "resolution_status": "The technology-level surface is recorded, but the binary writer/callback chain from one level to the next is not recovered.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00be34a0",
      "0x00d2e480",
      "0x00d2e480",
      "0x00aeb7b0",
      "0x00aeb160",
      "0x00aeb160",
      "0x00aeb7b0",
      "0x00aeb7b0",
      "0x00aebe90",
      "0x00aebe90",
      "0x00be34a0",
      "0x00d01410",
      "0x00d01410",
      "0x00d01ab0",
      "0x00d01ab0",
      "0x00d01e30"
    ],
    "conflict_id": "U-004-city-buildings",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
    "resolution_status": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  }
]
```

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
      "address": "00d01ab0",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00d01ab1",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00d01ab2",
      "instruction": "LEA EAX,[ESP + 0x10]"
    },
    {
      "address": "00d01ab6",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00d01ab8",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00d01ab9",
      "instruction": "LEA ECX,[ESP + 0x10]"
    },
    {
      "address": "00d01abd",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00d01abe",
      "instruction": "CALL 0x00d009a0"
    },
    {
      "address": "00d01ac3",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "00d01ac6",
      "instruction": "CALL 0x010212a0"
    },
    {
      "address": "00d01acb",
      "instruction": "MOV EDI,EAX"
    },
    {
      "address": "00d01acd",
      "instruction": "TEST EDI,EDI"
    },
    {
      "address": "00d01acf",
      "instruction": "JZ 0x00d01b42"
    },
    {
      "address": "00d01ad1",
      "instruction": "MOV EDX,dword ptr [ESP + 0xc]"
    },
    {
      "address": "00d01ad5",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00d01ad6",
      "instruction": "CALL 0x00ba6650"
    },
    {
      "address": "00d01adb",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "00d01ade",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00d01ae0",
      "instruction": "JZ 0x00d01af3"
    },
    {
      "address": "00d01ae2",
      "instruction": "MOV EAX,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00d01ae6",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00d01ae7",
      "instruction": "CALL 0x00ba6650"
    },
    {
      "address": "00d01aec",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "00d01aef",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00d01af1",
      "instruction": "JNZ 0x00d01b42"
    },
    {
      "address": "00d01af3",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00d01af4",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00d01af6",
      "instruction": "CALL 0x00ce6950"
    },
    {
      "address": "00d01afb",
      "instruction": "MOVZX ECX,byte ptr [ESI + 0xb0]"
    },
    {
      "address": "00d01b02",
      "instruction": "MOV EDI,dword ptr [ESI + 0xa0]"
    },
    {
      "address": "00d01b08",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00d01b09",
      "instruction": "LEA EDX,[ESP + 0x14]"
    },
    {
      "address": "00d01b0d",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00d01b0e",
      "instruction": "MOV EBX,EAX"
    },
    {
      "address": "00d01b10",
      "instruction": "MOV EAX,dword ptr [ESI + 0x9c]"
    },
    {
      "address": "00d01b16",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00d01b17",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00d01b18",
      "instruction": "MOV dword ptr [ESP + 0x20],EBX"
    },
    {
      "address": "00d01b1c",
      "instruction": "CALL 0x00d01210"
    },
    {
      "address": "00d01b21",
      "instruction": "ADD ESP,0x10"
    },
    {
      "address": "00d01b24",
      "instruction": "CMP EAX,EDI"
    },
    {
      "address": "00d01b26",
      "instruction": "JZ 0x00d01b33"
    },
    {
      "address": "00d01b28",
      "instruction": "CMP EBX,dword ptr [EAX]"
    },
    {
      "address": "00d01b2a",
      "instruction": "JC 0x00d01b33"
    },
    {
      "address": "00d01b2c",
      "instruction": "LEA ECX,[EAX + 0x20]"
    },
    {
      "address": "00d01b2f",
      "instruction": "CMP EAX,ECX"
    },
    {
      "address": "00d01b31",
      "instruction": "JNZ 0x00d01b35"
    },
    {
      "address": "00d01b33",
      "instruction": "MOV EAX,EDI"
    },
    {
      "address": "00d01b35",
      "instruction": "POP EBX"
    },
    {
      "address": "00d01b36",
      "instruction": "CMP EAX,EDI"
    },
    {
      "address": "00d01b38",
      "instruction": "JZ 0x00d01b42"
    },
    {
      "address": "00d01b3a",
      "instruction": "POP EDI"
    },
    {
      "address": "00d01b3b",
      "instruction": "ADD EAX,0x4"
    },
    {
      "address": "00d01b3e",
      "instruction": "POP ESI"
    },
    {
      "address": "00d01b3f",
      "instruction": "RET 0x8"
    },
    {
      "address": "00d01b42",
      "instruction": "POP EDI"
    },
    {
      "address": "00d01b43",
      "instruction": "LEA EAX,[ESI + 0x24]"
    },
    {
      "address": "00d01b46",
      "instruction": "POP ESI"
    },
    {
      "address": "00d01b47",
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
  "original_bytes": 14416,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"thiscall\",\n    \"hidden_this\": \"ECX OpaqueRelationshipManager* receiver\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"Returns receiver+0x24 fallback or selected record+0x04 map pointer; normal failure is a non-null fallback address.\",\n    \"return_width_bytes\": 4,\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"position\": 1,\n        \"type\": \"std::uint32_t\",\n        \"width_bytes\": 4\n      },\n      {\n        \"entry_offset\": \"ESP+0x08\",\n        \"position\": 2,\n        \"type\": \"std::uint32_t\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 8\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueRelationshipManager,OpaqueRelationshipMap\",\n        \"same_calling_convention\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-13-SIM-DIPLOMACY-PREDICATE\",\n      \"score\": 22,\n      \"symbol\": \"RelationshipManager_IsAllied2_00d01ff0\",\n      \"va\": \"0x00d01ff0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:OpaqueRelationshipMap\"\n      ],\n      \"package\": \"PKG-13-SIM-DIPLOMACY-PRIMITIVES\",\n      \"score\": 17,\n      \"symbol\": \"RelationshipLookup_00d01410\",\n      \"va\": \"0x00d01410\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:OpaqueRelationshipManager,OpaqueRelationshipMap\",\n        \"same_calling_convention\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-13-SIM-DIPLOMACY-TRANSITIONS\",\n      \"score\": 16,\n      \"symbol\": \"DiplomacyTransition_00d01e30\",\n      \"va\": \"0x00d01e30\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:OpaqueRelationshipManager,OpaqueRelationshipMap\",\n        \"same_calling_convention\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-13-SIM-DIPLOMACY-TRANSITIONS\",\n      \"score\": 16,\n      \"symbol\": \"DiplomacyTransition_00d038e0\",\n      \"va\": \"0x00d038e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:OpaqueRelationshipManager,OpaqueRelationshipMap\",\n        \"same_calling_convention\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-13-SIM-DIPLOMACY-TRANSITIONS\",\n      \"score\": 16,\n      \"symbol\": \"DiplomacyTransition_00d065a0\",\n      \"va\": \"0x00d065a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:OpaqueRelationshipManager,OpaqueRelationshipMap\",\n        \"same_calling_convention\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-13-SIM-DIPLOMACY-TRANSITIONS\",\n      \"score\": 16,\n      \"symbol\": \"DiplomacyTransition_00d06920\",\n      \"va\": \"0x00d06920\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-13-E2-DIPLOMACY-ALT\",\n      \"score\": 8,\n      \"symbol\": \"RelationshipScoreObjects_00d00d60\",\n      \"va\": \"0x00d00d60\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-13-E2-DIPLOMACY-ALT\",\n      \"score\": 6,\n      \"symbol\": \"RelationshipScoreBand_00d00d00\",\n      \"va\": \"0x00d00d00\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Manager offsets, context/key order, high-bit short-circuit, 0x20 candidate stride, candidate+0x04 selection, receiver+0x24 fallback, and RET 0x8 are exact; helper search/context behavior remains delegated.\",\n  \"audit_findings\": [\n    \"PKG13-DIP2-SEM-001\",\n    \"PKG13-DIP2-META-002\"\n  ],\n  \"audit_status\": \"clean_after_repair\",\n  \"blocked\": false,\n  \"blockers\": [\n    \"Selector and context helper bodies are intentionally unresolved; runtime relationship records remain gated.\"\n  ],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueRelationshipManager\",\n  \"cluster\": null,\n  \"confidence\": 0.86,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"context_word_read_00ce6950\",\n        \"reconstructed\": true,\n        \"va\": \"0x00ce6950\"\n      },\n      {\n        \"name\": \"FUN_010212a0\",\n        \"reconstructed\": true,\n        \"va\": \"0x010212a0\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d01b50\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d01b80\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d01bb0\"\n      },\n      {\n        \"name\": \"DiplomacyTransition_00d01e30\",\n        \"reconstructed\": true,\n        \"va\": \"0x00d01e30\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d01f20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d01f50\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d01fb0\"\n      },\n      {\n        \"name\": \"RelationshipManager_IsAllied2_00d01ff0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00d01ff0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d02050\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d03860\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d038a0\"\n      },\n      {\n        \"name\": \"DiplomacyTransition_00d038e0\",\n        \"reconstructed\": true,\n   
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
  "body_end": "00d01b49",
  "body_span_bytes": 154,
  "body_start": "00d01ab0",
  "callees": [
    "FUN_00ce6950",
    "FUN_00d01210",
    "FUN_00d009a0",
    "FUN_010212a0",
    "FUN_00ba6650"
  ],
  "callers": [
    "FUN_00d06240",
    "FUN_00d01bb0",
    "Simulator::cRelationshipManager::IsAllied2",
    "FUN_00d01fb0",
    "FUN_00d03860",
    "FUN_00d038a0",
    "FUN_00d02050",
    "FUN_00d038e0",
    "FUN_00d01f20",
    "FUN_00d01b80",
    "FUN_00d064b0",
    "FUN_00d03d70",
    "FUN_00d05830",
    "FUN_00d06270",
    "FUN_00d065a0",
    "FUN_00d06920",
    "FUN_00d01e30",
    "FUN_00d01f50",
    "FUN_00d05a20",
    "FUN_00d01b50"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00d01ab0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00d01ab0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x901ab0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00d01ab0(void)",
  "size_bytes": 154,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00d01ab0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 32,
  "xrefs": [
    {
      "from": "00d01f31"
    },
    {
      "from": "00d01f84"
    },
    {
      "from": "00d01fc1"
    },
    {
      "from": "00d05a67"
    },
    {
      "from": "00d020a9"
    },
    {
      "from": "00d020c9"
    },
    {
      "from": "00d0625e"
    },
    {
      "from": "00d065e0"
    },
    {
      "from": "00d065fb"
    },
    {
      "from": "00d0661c"
    },
    {
      "from": "00d06637"
    },
    {
      "from": "00d066a3"
    },
    {
      "from": "00d066eb"
    },
    {
      "from": "00d0695a"
    },
    {
      "from": "00d0697b"
    },
    {
      "from": "00d0391c"
    },
    {
      "from": "00d0393d"
    },
    {
      "from": "00d0656c"
    },
    {
      "from": "00d01b61"
    },
    {
      "from": "00d01b96"
    },
    {
      "from": "00d05854"
    },
    {
      "from": "00d01e61"
    },
    {
      "from": "00d01e82"
    },
    {
      "from": "00d01c0b"
    },
    {
      "from": "00d01cd5"
    },
    {
      "from": "00d03de1"
    },
    {
      "from": "00d02024"
    },
    {
      "from": "00d03871"
    },
    {
      "from": "00d038b1"
    },
    {
      "from": "00d0637d"
    },
    {
      "from": "00d063c4"
    },
    {
      "from": "00d063e6"
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
  "file": "src/reconstruction/pkg13_diplomacy_primitives/diplomacy_primitives.cpp",
  "files": [
    "reconstruction/staging/pkg13-diplomacy-primitives/diplomacy_primitives.cpp",
    "reconstruction/staging/pkg13-diplomacy-primitives/diplomacy_primitives.hpp",
    "reconstruction/staging/pkg13-diplomacy-primitives/diplomacy_primitives_test.cpp",
    "src/reconstruction/pkg13_diplomacy_primitives/diplomacy_primitives.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-diplomacy-primitives/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg13-diplomacy-primitives/00d01ab0.json"
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
    "gate-diplomacy-map-selector"
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
  "OpaqueRelationshipManager",
  "OpaqueRelationshipMap",
  "OpaqueRelationshipRecord",
  "OpaqueSpaceContext",
  "std::uint32_t"
]
```

## vtables

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## Conflicts

```json
[
  {
    "anchors": [
      "0x00d2e480",
      "0x00d2e480",
      "0x00d01410",
      "0x00d01410",
      "0x00d01ab0",
      "0x00d01ab0",
      "0x00d01e30",
      "0x00d01e30",
      "0x00d01f50",
      "0x00d01f50",
      "0x00d01ff0",
      "0x00d01ff0",
      "0x00d038e0",
      "0x00d038e0",
      "0x00d065a0",
      "0x00d065a0"
    ],
    "conflict_id": "U-003-civilization-progression",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The technology-level surface is recorded, but the binary writer/callback chain from one level to the next is not recovered.",
    "resolution_status": "The technology-level surface is recorded, but the binary writer/callback chain from one level to the next is not recovered.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00be34a0",
      "0x00d2e480",
      "0x00d2e480",
      "0x00aeb7b0",
      "0x00aeb160",
      "0x00aeb160",
      "0x00aeb7b0",
      "0x00aeb7b0",
      "0x00aebe90",
      "0x00aebe90",
      "0x00be34a0",
      "0x00d01410",
      "0x00d01410",
      "0x00d01ab0",
      "0x00d01ab0",
      "0x00d01e30"
    ],
    "conflict_id": "U-004-city-buildings",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
    "resolution_status": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  }
]
```
