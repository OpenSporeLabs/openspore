# Evidence 0x00d01410

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `1fd34867d1056ece6fd2dfe4ab15ab9db734a619e31eb128403a5e420bad055e`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "stdcall-equivalent callee cleanup",
  "hidden_this": false,
  "return_register": "EAX",
  "return_semantics": "Returns null for the map+0x04 sentinel; otherwise returns the lower-bound node+0x18 relationship payload pointer.",
  "return_width_bytes": 4,
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "position": 1,
      "type": "OpaqueRelationshipMap*",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x08",
      "position": 2,
      "type": "std::uint32_t",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x0c",
      "position": 3,
      "type": "std::uint32_t",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 12
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
      "entry_ESP+0x4",
      "entry_ESP+0x8",
      "entry_ESP+0xc"
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
    "ret_form": "RET 0xc",
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
        "size_inferred": false,
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
    "stack_cleanup_bytes": 12,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0xc"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -8, so the listing is not one path",
    "receiver_not_determinable: ecx_read_without_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_read_without_deref), and the convention rule that would apply discriminates on receiver absence"
  ],
  "cleanup": {
    "bytes": 12,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0xc",
    "side": "callee"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "3c5307ab63cc0556ced0fecd450285af54db5ad641dea299fd8feb2e10df692f",
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
    "persisted_calling_convention": "stdcall-equivalent callee cleanup"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0028",
        "obs-0031"
      ],
      "claim": "the callee pops 12 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 12,
        "side": "callee"
      }
    },
    {
      "based_on": [
        "obs-0007",
        "obs-0009",
        "obs-0012",
        "obs-0014",
        "obs-0016",
        "obs-0021"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 3,
        "total_bytes": 12
      }
    },
    {
      "based_on": [
        "obs-0008",
        "obs-0009",
        "obs-0018",
        "obs-0022"
      ],
      "claim": "the register receiver is undetermined: ecx_read_without_deref",
      "confidence": "UNKNOWN",
      "id": "R0",
      "value": {
        "reason": "ecx_read_without_deref",
        "register": null
      }
    },
    {
      "based_on": [
        "obs-0008",
        "obs-0009",
        "obs-0018",
        "obs-0022"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_read_without_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0028",
        "obs-0031"
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
        "obs-0028",
        "obs-0031"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0028",
        "obs-0031"
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
      "and_esp": null,
      "at": "0x00d01410",
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
      "raw": "SUB ESP,0x8",
      "sub": 8
    },
    {
      "at": "0x00d01410",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x8",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00d01413",
      "count": 2,
      "first_use": 1,
      "first_write_index": 11,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at":
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
    "va": "0x00d01470"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d015d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d01b50"
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
    "va": "0x00d05d90"
  },
  {
    "name": "DiplomacyTransition_00d065a0",
    "reconstructed": true,
    "va": "0x00d065a0"
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
  "count": 35,
  "instructions": [
    {
      "address": "00d01410",
      "instruction": "SUB ESP,0x8"
    },
    {
      "address": "00d01413",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00d01414",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00d01415",
      "instruction": "LEA EAX,[ESP + 0x1c]"
    },
    {
      "address": "00d01419",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00d0141a",
      "instruction": "LEA ECX,[ESP + 0x1c]"
    },
    {
      "address": "00d0141e",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00d0141f",
      "instruction": "XOR EDI,EDI"
    },
    {
      "address": "00d01421",
      "instruction": "CALL 0x00d009a0"
    },
    {
      "address": "00d01426",
      "instruction": "MOV EDX,dword ptr [ESP + 0x20]"
    },
    {
      "address": "00d0142a",
      "instruction": "MOV EAX,dword ptr [ESP + 0x24]"
    },
    {
      "address": "00d0142e",
      "instruction": "MOV ESI,dword ptr [ESP + 0x1c]"
    },
    {
      "address": "00d01432",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "00d01435",
      "instruction": "LEA ECX,[ESP + 0x8]"
    },
    {
      "address": "00d01439",
      "instruction": "MOV dword ptr [ESP + 0x8],EDX"
    },
    {
      "address": "00d0143d",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00d0143e",
      "instruction": "LEA EDX,[ESP + 0x1c]"
    },
    {
      "address": "00d01442",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00d01443",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00d01445",
      "instruction": "MOV dword ptr [ESP + 0x14],EAX"
    },
    {
      "address": "00d01449",
      "instruction": "CALL 0x00d00f80"
    },
    {
      "address": "00d0144e",
      "instruction": "MOV EAX,dword ptr [ESP + 0x18]"
    },
    {
      "address": "00d01452",
      "instruction": "ADD ESI,0x4"
    },
    {
      "address": "00d01455",
      "instruction": "CMP EAX,ESI"
    },
    {
      "address": "00d01457",
      "instruction": "JZ 0x00d01464"
    },
    {
      "address": "00d01459",
      "instruction": "POP EDI"
    },
    {
      "address": "00d0145a",
      "instruction": "ADD EAX,0x18"
    },
    {
      "address": "00d0145d",
      "instruction": "POP ESI"
    },
    {
      "address": "00d0145e",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "00d01461",
      "instruction": "RET 0xc"
    },
    {
      "address": "00d01464",
      "instruction": "MOV EAX,EDI"
    },
    {
      "address": "00d01466",
      "instruction": "POP EDI"
    },
    {
      "address": "00d01467",
      "instruction": "POP ESI"
    },
    {
      "address": "00d01468",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "00d0146b",
      "instruction": "RET 0xc"
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
  "original_bytes": 12717,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"stdcall-equivalent callee cleanup\",\n    \"hidden_this\": false,\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"Returns null for the map+0x04 sentinel; otherwise returns the lower-bound node+0x18 relationship payload pointer.\",\n    \"return_width_bytes\": 4,\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"position\": 1,\n        \"type\": \"OpaqueRelationshipMap*\",\n        \"width_bytes\": 4\n      },\n      {\n        \"entry_offset\": \"ESP+0x08\",\n        \"position\": 2,\n        \"type\": \"std::uint32_t\",\n        \"width_bytes\": 4\n      },\n      {\n        \"entry_offset\": \"ESP+0x0c\",\n        \"position\": 3,\n        \"type\": \"std::uint32_t\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 12\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:OpaqueRelationshipMap\"\n      ],\n      \"package\": \"PKG-13-SIM-DIPLOMACY-PRIMITIVES\",\n      \"score\": 17,\n      \"symbol\": \"RelationshipMapSelect_00d01ab0\",\n      \"va\": \"0x00d01ab0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_types:OpaqueRelationshipEntry,OpaqueRelationshipMap\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-13-SIM-DIPLOMACY-PREDICATE\",\n      \"score\": 15,\n      \"symbol\": \"RelationshipManager_IsAllied2_00d01ff0\",\n      \"va\": \"0x00d01ff0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:OpaqueRelationshipEntry,OpaqueRelationshipMap\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-13-SIM-DIPLOMACY-TRANSITIONS\",\n      \"score\": 9,\n      \"symbol\": \"DiplomacyTransition_00d01e30\",\n      \"va\": \"0x00d01e30\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:OpaqueRelationshipEntry,OpaqueRelationshipMap\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-13-SIM-DIPLOMACY-TRANSITIONS\",\n      \"score\": 9,\n      \"symbol\": \"DiplomacyTransition_00d038e0\",\n      \"va\": \"0x00d038e0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:OpaqueRelationshipEntry,OpaqueRelationshipMap\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-13-SIM-DIPLOMACY-TRANSITIONS\",\n      \"score\": 9,\n      \"symbol\": \"DiplomacyTransition_00d065a0\",\n      \"va\": \"0x00d065a0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:OpaqueRelationshipEntry,OpaqueRelationshipMap\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-13-SIM-DIPLOMACY-TRANSITIONS\",\n      \"score\": 9,\n      \"symbol\": \"DiplomacyTransition_00d06920\",\n      \"va\": \"0x00d06920\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-13-E2-DIPLOMACY-ALT\",\n      \"score\": 6,\n      \"symbol\": \"RelationshipScoreBand_00d00d00\",\n      \"va\": \"0x00d00d00\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-13-E2-DIPLOMACY-ALT\",\n      \"score\": 6,\n      \"symbol\": \"RelationshipScoreObjects_00d00d60\",\n      \"va\": \"0x00d00d60\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Key normalization, d00f80 output contract, map+0x04 sentinel conversion, node+0x18 payload conversion, and RET 0x0c are exact; lower-bound tree behavior remains delegated.\",\n  \"audit_findings\": [\n    \"PKG13-DIP2-META-001\"\n  ],\n  \"audit_status\": \"clean_after_repair\",\n  \"blocked\": false,\n  \"blockers\": [\n    \"Lower-bound helper body is intentionally unresolved; runtime records remain gated.\"\n  ],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueRelationshipMap\",\n  \"cluster\": null,\n  \"confidence\": 0.88,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d01470\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d015d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d01b50\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d01bb0\"\n      },\n      {\n        \"name\": \"DiplomacyTransition_00d01e30\",\n        \"reconstructed\": true,\n        \"va\": \"0x00d01e30\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d01f20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d01f50\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d01fb0\"\n      },\n      {\n        \"name\": \"RelationshipManager_IsAllied2_00d01ff0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00d01ff0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d03860\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d038a0\"\n      },\n      {\n        \"name\": \"DiplomacyTransition_00d038e0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00d038e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d05830\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d05a20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d05d90\"\n      },\n      {\n        \"name\": \"DiplomacyTransition_00d065a0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00d065a0\"\n      },\n      {\n        \"name\": \"DiplomacyTransition_00d06920\",\
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
  "body_end": "00d0146d",
  "body_span_bytes": 94,
  "body_start": "00d01410",
  "callees": [
    "FUN_00d009a0",
    "FUN_00d00f80"
  ],
  "callers": [
    "FUN_00d01bb0",
    "Simulator::cRelationshipManager::IsAllied2",
    "FUN_00d01fb0",
    "FUN_00d03860",
    "FUN_00d038a0",
    "FUN_00d05d90",
    "FUN_00d038e0",
    "FUN_00d01f20",
    "FUN_00d01470",
    "FUN_00d05830",
    "FUN_00d015d0",
    "FUN_00d065a0",
    "FUN_00d06920",
    "FUN_00d01e30",
    "FUN_00d01f50",
    "FUN_00d05a20",
    "FUN_00d01b50"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00d01410",
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
    },
    {
      "name": "local_8",
      "storage": "Stack[-0x8]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 2,
  "mode": "live",
  "name": "FUN_00d01410",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x901410",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00d01410(void)",
  "size_bytes": 94,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00d01410",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 24,
  "xrefs": [
    {
      "from": "00d01f39"
    },
    {
      "from": "00d01f8c"
    },
    {
      "from": "00d01fc9"
    },
    {
      "from": "00d05a75"
    },
    {
      "from": "00d015e5"
    },
    {
      "from": "00d0148a"
    },
    {
      "from": "00d05dcb"
    },
    {
      "from": "00d065e8"
    },
    {
      "from": "00d06603"
    },
    {
      "from": "00d06624"
    },
    {
      "from": "00d0663f"
    },
    {
      "from": "00d06962"
    },
    {
      "from": "00d06983"
    },
    {
      "from": "00d03924"
    },
    {
      "from": "00d03945"
    },
    {
      "from": "00d01b69"
    },
    {
      "from": "00d05860"
    },
    {
      "from": "00d01e69"
    },
    {
      "from": "00d01e8a"
    },
    {
      "from": "00d01c13"
    },
    {
      "from": "00d01cdd"
    },
    {
      "from": "00d0202c"
    },
    {
      "from": "00d03879"
    },
    {
      "from": "00d038b9"
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
    "reconstruction/metadata/pkg13-diplomacy-primitives/00d01410.json"
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
    "gate-diplomacy-map-lower-bound"
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
  "OpaqueRelationshipEntry",
  "OpaqueRelationshipMap",
  "OpaqueRelationshipMap*",
  "OpaqueRelationshipNode",
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
