# Evidence 0x00676e90

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `aba72127c2dd78dfa3996c568ea802a4a883bdee35fc70071429beb1c5d435c9`

## abi

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
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
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
      }
    ],
    "stack_cleanup_bytes": 8,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x8"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +12, so the listing is not one path"
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
  "content_sha256": "f593aa4a2917637eb0f3a6206d65d2c3100ee03b695e1d5617c8a404c8e4ce9d",
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
    "ghidra_parameter_count": 4,
    "persisted": "no_information",
    "persisted_calling_convention": null
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0016"
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
        "obs-0006",
        "obs-0009"
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
        "obs-0002",
        "obs-0003",
        "obs-0009",
        "obs-0010",
        "obs-0011"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          36
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0009",
        "obs-0010",
        "obs-0011",
        "obs-0016"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0016"
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
        "obs-0016"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0016"
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
      "at": "0x00676e90",
      "count": 4,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00676e91",
      "count": 2,
      "first_use": 1,
      "first_write_index": 8,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00676e91",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00676e99",
      "count": 3,
      "first_use": 4,
      "first_write_index": 5,
      "id": "obs-0004",
      "index": 4,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00676e9a",
      "count": 2,
      "first_use": 5,
      "first_write_index": null,
      "id": "obs-0005",
      "index": 5,
      "kind": "REG_READ",
      "raw": "MOV EDI,dword ptr [ESP + 0xc]",
      "reg": "ESP"
    },
    {
      "at": "0x00676e9a",
      "base": "ESP",
      "disp": 12,
      "id": "obs-0006",
      "index": 5,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EDI,dword ptr [ESP + 0xc]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00676e9a",
      "definite": true,
      "id": "obs-0007",
      "index": 5,
      "kind": "REG_WRITE",
      "raw": "MOV EDI,dword ptr [ESP + 0xc]",
      "reg": "EDI",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00676e9f",
      "id": "obs-0008",
      "index": 7,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00676660",
      "target": "0x00676660"
    },
    {
      "at": "0x00676ea4",
      "base": "ESP",
      "disp": 16,
      "id": "obs-0009",
      "index": 8,
      "key": 4,
      "kind": "STACK_SLOT_READ",
  
[TRUNCATED]
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
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
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
      }
    ],
    "stack_cleanup_bytes": 8,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x8"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +12, so the listing is not one path"
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
  "content_sha256": "f593aa4a2917637eb0f3a6206d65d2c3100ee03b695e1d5617c8a404c8e4ce9d",
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
    "ghidra_parameter_count": 4,
    "persisted": "no_information",
    "persisted_calling_convention": null
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0016"
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
        "obs-0006",
        "obs-0009"
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
        "obs-0002",
        "obs-0003",
        "obs-0009",
        "obs-0010",
        "obs-0011"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          36
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0009",
        "obs-0010",
        "obs-0011",
        "obs-0016"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0016"
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
        "obs-0016"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0016"
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
      "at": "0x00676e90",
      "count": 4,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00676e91",
      "count": 2,
      "first_use": 1,
      "first_write_index": 8,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00676e91",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00676e99",
      "count": 3,
      "first_use": 4,
      "first_write_index": 5,
      "id": "obs-0004",
      "index": 4,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00676e9a",
      "count": 2,
      "first_use": 5,
      "first_write_index": null,
      "id": "obs-0005",
      "index": 5,
      "kind": "REG_READ",
      "raw": "MOV EDI,dword ptr [ESP + 0xc]",
      "reg": "ESP"
    },
    {
      "at": "0x00676e9a",
      "base": "ESP",
      "disp": 12,
      "id": "obs-0006",
      "index": 5,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EDI,dword ptr [ESP + 0xc]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00676e9a",
      "definite": true,
      "id": "obs-0007",
      "index": 5,
      "kind": "REG_WRITE",
      "raw": "MOV EDI,dword ptr [ESP + 0xc]",
      "reg": "EDI",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00676e9f",
      "id": "obs-0008",
      "index": 7,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00676660",
      "target": "0x00676660"
    },
    {
      "at": "0x00676ea4",
      "base": "ESP",
      "disp": 16,
      "id": "obs-0009",
      "index": 8,
      "key": 4,
      "kind": "STACK_SLOT_READ",
  
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "achievement_completion_boundary_00676710",
    "reconstructed": true,
    "va": "0x00676710"
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
    "va": "0x005802f0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0060cf30"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0063d2f0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0063fd20"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0064bcd0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b5ce70"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ba4600"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ba46f0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ba48b0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ba4f30"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c267e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c46b80"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c4b310"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c4da10"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00cdab10"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00cdbd20"
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
      "0x00676e90",
      "0x00676e90",
      "0x00676e50",
      "0x00b31da0",
      "0x006766d0",
      "0x006766b0",
      "0x00676620",
      "0x00b321e0",
      "0x00676c40",
      "0x00b32330",
      "0x00676e90",
      "0x00b32560",
      "0x0067dd90",
      "0x00b63980",
      "0x00b32390",
      "0x00e66280"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/additional-domains.json:6",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The cited stream or file boundary is retained, but the complete wire/transaction/round-trip contract is not reconstructed.",
    "resolution_status": "The cited stream or file boundary is retained, but the complete wire/transaction/round-trip contract is not reconstructed.",
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
  "count": 23,
  "instructions": [
    {
      "address": "00676e90",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00676e91",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00676e93",
      "instruction": "CMP byte ptr [ESI + 0x24],0x0"
    },
    {
      "address": "00676e97",
      "instruction": "JNZ 0x00676ec5"
    },
    {
      "address": "00676e99",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00676e9a",
      "instruction": "MOV EDI,dword ptr [ESP + 0xc]"
    },
    {
      "address": "00676e9e",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00676e9f",
      "instruction": "CALL 0x00676660"
    },
    {
      "address": "00676ea4",
      "instruction": "MOV ECX,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00676ea8",
      "instruction": "ADD dword ptr [EAX + 0x4],ECX"
    },
    {
      "address": "00676eab",
      "instruction": "TEST byte ptr [EAX],0x1"
    },
    {
      "address": "00676eae",
      "instruction": "JZ 0x00676ec4"
    },
    {
      "address": "00676eb0",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00676eb1",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00676eb3",
      "instruction": "CALL 0x006751c0"
    },
    {
      "address": "00676eb8",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00676eba",
      "instruction": "JZ 0x00676ec4"
    },
    {
      "address": "00676ebc",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00676ebd",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00676ebf",
      "instruction": "CALL 0x00676710"
    },
    {
      "address": "00676ec4",
      "instruction": "POP EDI"
    },
    {
      "address": "00676ec5",
      "instruction": "POP ESI"
    },
    {
      "address": "00676ec6",
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
  "original_bytes": 13000,
  "preview": "{\n  \"abi\": {},\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:AchievementManagerWire\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-11-A3-ACHIEVEMENT-MISSION-WAVE2\",\n      \"score\": 17,\n      \"symbol\": \"achievement_completion_boundary_00676710\",\n      \"va\": \"0x00676710\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:AchievementManagerWire\"\n      ],\n      \"package\": \"PKG-11-A3-ACHIEVEMENT-MISSION-WAVE2\",\n      \"score\": 14,\n      \"symbol\": \"achievement_progress_flag_transition_00676ed0\",\n      \"va\": \"0x00676ed0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-11-A2-PROGRESSION-ALTERNATIVE\",\n      \"score\": 8,\n      \"symbol\": \"mission_track_predicate_00febc90\",\n      \"va\": \"0x00febc90\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-11-A2-PROGRESSION-ALTERNATIVE\",\n      \"score\": 8,\n      \"symbol\": \"mission_manager_operation_00fee310\",\n      \"va\": \"0x00fee310\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 3,\n      \"symbol\": \"FUN_0102d1b0\",\n      \"va\": \"0x0102d1b0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": \"clean\",\n  \"blocked\": false,\n  \"blockers\": [\n    \"No original-process achievement update trace was run.\",\n    \"Record ownership and downstream 0x00676710 effects remain opaque.\"\n  ],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"AchievementManagerWire\",\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"achievement_completion_boundary_00676710\",\n        \"reconstructed\": true,\n        \"va\": \"0x00676710\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005802f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0060cf30\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0063d2f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0063fd20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0064bcd0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b5ce70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ba4600\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ba46f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ba48b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ba4f30\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c267e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c46b80\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c4b310\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c4da10\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00cdab10\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00cdbd20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00cf7630\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d2b5f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d3cdc0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d43e30\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d71060\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ea267c\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ec5160\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ed7060\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00f15890\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00f19940\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00f1b590\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00f1f3b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00fdd5a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00fdeac0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00fe5a20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x01004e50\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x01021ab0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0102cae0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": 
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
  "body_end": "00676ec8",
  "body_span_bytes": 57,
  "body_start": "00676e90",
  "callees": [
    "FUN_00676660",
    "FUN_00676710",
    "FUN_006751c0"
  ],
  "callers": [
    "FUN_00f15890",
    "FUN_0064bcd0",
    "FUN_01021ab0",
    "FUN_00ba48b0",
    "FUN_00c46b80",
    "FUN_00ba4600",
    "FUN_0060cf30",
    "FUN_00cf7630",
    "FUN_0102df20",
    "FUN_00ba4f30",
    "FUN_00f1b590",
    "FUN_00d3cdc0",
    "FUN_01004e50",
    "FUN_00c267e0",
    "FUN_0102d1b0",
    "FUN_00c4da10",
    "FUN_00d2b5f0",
    "FUN_00fe5a20",
    "FUN_00c4b310",
    "FUN_00cdbd20",
    "FUN_00ea267c",
    "FUN_005802f0",
    "FUN_0105b350",
    "FUN_0063d2f0",
    "FUN_00ed7060",
    "FUN_0063fd20",
    "FUN_00f19940",
    "FUN_00d71060",
    "FUN_0103fe90",
    "FUN_00b5ce70",
    "FUN_0102cae0",
    "FUN_0102cf10",
    "FUN_00ba46f0",
    "FUN_00f1f3b0",
    "FUN_00fdd5a0",
    "FUN_00cdab10",
    "FUN_00ec5160",
    "FUN_00d43e30",
    "FUN_00fdeac0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00676e90",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "Pollinator::cAchievementsManager::SetProgressFlags",
  "namespace": "Pollinator",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 4,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "cAchievementsManager *"
    },
    {
      "name": "achievementID",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "uint32_t"
    },
    {
      "name": "progressFlags",
      "ordinal": 2,
      "storage": "Stack[0xc]:4",
      "type": "int"
    },
    {
      "name": "value",
      "ordinal": 3,
      "storage": "Stack[0x10]:1",
      "type": "bool"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "void",
  "return_type_resolved": true,
  "rva": "0x276e90",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "void Pollinator::cAchievementsManager::SetProgressFlags(cAchievementsManager * this, uint32_t achievementID, int progressFlags, bool value)",
  "size_bytes": 57,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00676e90",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 75,
  "xrefs": [
    {
      "from": "0060cf66"
    },
    {
      "from": "0060cf85"
    },
    {
      "from": "0060cf94"
    },
    {
      "from": "01021b45"
    },
    {
      "from": "0063d79f"
    },
    {
      "from": "0063fd8c"
    },
    {
      "from": "00f19a59"
    },
    {
      "from": "00f19a75"
    },
    {
      "from": "00f19a91"
    },
    {
      "from": "00f19aad"
    },
    {
      "from": "00cf765a"
    },
    {
      "from": "00cf7672"
    },
    {
      "from": "00cf768a"
    },
    {
      "from": "00cf7698"
    },
    {
      "from": "0102e6fc"
    },
    {
      "from": "0102cb73"
    },
    {
      "from": "0102cff2"
    },
    {
      "from": "0102d5b8"
    },
    {
      "from": "00b5cee8"
    },
    {
      "from": "00b5cefa"
    },
    {
      "from": "00ba51b8"
    },
    {
      "from": "00d3d2c6"
    },
    {
      "from": "00f16121"
    },
    {
      "from": "00c2694d"
    },
    {
      "from": "00cdac28"
    },
    {
      "from": "00cdad04"
    },
    {
      "from": "00fdd8e6"
    },
    {
      "from": "00c4b397"
    },
    {
      "from": "00c46db8"
    },
    {
      "from": "00c4dad4"
    },
    {
      "from": "00cdc3a2"
    },
    {
      "from": "00cdc3c9"
    },
    {
      "from": "00f1b632"
    },
    {
      "from": "00ea26ce"
    },
    {
      "from": "00ec518f"
    },
    {
      "from": "00ed7079"
    },
    {
      "from": "00ed708c"
    },
    {
      "from": "00ed709f"
    },
    {
      "from": "00ed72e1"
    },
    {
      "from": "00ed72fb"
    },
    {
      "from": "00ed7311"
    },
    {
      "from": "00ed732b"
    },
    {
      "from": "00ed7345"
    },
    {
      "from": "00ed736a"
    },
    {
      "from": "00ed7384"
    },
    {
      "from": "00ed739e"
    },
    {
      "from": "00ed73cd"
    },
    {
      "from": "00ed73fc"
    },
    {
      "from": "00ed7422"
    },
    {
      "from": "00ed744a"
    },
    {
      "from": "00ed746f"
    },
    {
      "from": "00f1f43f"
    },
    {
      "from": "00fded71"
    },
    {
      "from": "00fe5fb9"
    },
    {
      "from": "01004ea7"
    },
    {
      "from": "01004ed6"
    },
    {
      "from": "0104000a"
    },
    {
      "from": "0105b3f7"
    },
    {
      "from": "00580595"
    },
    {
      "from": "00ba4736"
    },
    {
      "from": "00ba4a9a"
    },
    {
      "from": "00ba4636"
    },
    {
      "from": "00d4425b"
    },
    {
      "from": "00d445e7"
    },
    {
      "from": "0064be44"
    },
    {
      "from": "0064bee0"
    },
    {
      "from": "0064bf53"
    },
    {
      "from": "00d714cc"
    },
    {
      "from": "0067712f"
    },
    {
      "from": "00c3d9d6"
    },
    {
      "from": "00d2b67d"
    },
    {
      "from": "00d45893"
    },
    {
      "from": "00d537ff"
    },
    {
      "from": "0100bfff"
    },
    {
      "from": "0100c4c6"
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
  "file": "src/reconstruction/pkg11_a2_progression_alt/progression_alt.cpp",
  "files": [
    "reconstruction/staging/pkg11-a2-progression-alt/progression_alt.cpp",
    "reconstruction/staging/pkg11-a2-progression-alt/progression_alt.hpp",
    "src/reconstruction/pkg11_a2_progression_alt/progression_alt.cpp",
    "src/reconstruction/pkg11_a2_progression_alt/progression_alt.hpp",
    "src/reconstruction/pkg11_a2_progression_alt/progression_alt_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-sim-social-world-wave1/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg11-a2-progression-alt/00676e90.json"
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
    "gate-achievement-progress-update",
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
  "AchievementManagerWire",
  "AchievementRecordWire",
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
      "0x00676e90",
      "0x00676e90",
      "0x00676e50",
      "0x00b31da0",
      "0x006766d0",
      "0x006766b0",
      "0x00676620",
      "0x00b321e0",
      "0x00676c40",
      "0x00b32330",
      "0x00676e90",
      "0x00b32560",
      "0x0067dd90",
      "0x00b63980",
      "0x00b32390",
      "0x00e66280"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/additional-domains.json:6",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The cited stream or file boundary is retained, but the complete wire/transaction/round-trip contract is not reconstructed.",
    "resolution_status": "The cited stream or file boundary is retained, but the complete wire/transaction/round-trip contract is not reconstructed.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  }
]
```
