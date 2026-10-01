# Evidence 0x00d2e380

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `aaf6cb642045b7646cd3292f1ce6befb6438c671093d92ab0ad3985364b58c80`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "cdecl-compatible from one stack argument and RET",
  "hidden_this": false,
  "return_register": "ST0",
  "return_semantics": "Returns the selected mutable global float exactly; all levels outside 0 through 3 return positive 0.0F.",
  "return_width_bytes": 4,
  "stack_arguments": [
    {
      "after_push_ecx_offset": "ESP+0x08",
      "entry_offset": "ESP+0x04",
      "observed_use": "Signed comparison with -1, followed by unsigned CMP EAX,3 / JA table bounds check",
      "position": 1,
      "type": "std::int32_t",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 0
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
      "entry_ESP+0x8"
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
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "ret_form": "RET",
    "return_register": "ST0",
    "return_semantics": "float_or_x87_in_ST0",
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
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -12, so the listing is not one path",
    "receiver_not_determinable: ecx_read_without_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_read_without_deref), and the convention rule that would apply discriminates on receiver absence"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate",
    "side": "caller"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "7bd66c55686b76bc7d667e3a55a9d330ca70e2e9cc08bbdea8fe488ba0575738",
  "conventions": {
    "ambiguities": [
      "receiver_undetermined"
    ],
    "calling_convention": null,
    "candidate_conventions": [
      "__cdecl",
      "__thiscall"
    ],
    "confidence": "UNKNOWN",
    "corroboration": "not_available"
  },
  "cross_validation": {
    "agreement": false,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 1,
    "persisted": "no_information",
    "persisted_calling_convention": "cdecl-compatible from one stack argument and RET"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 2,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0019",
        "obs-0023",
        "obs-0027",
        "obs-0031"
      ],
      "claim": "the caller cleans up the stack: a bare RET is compatible with caller cleanup and, for a zero-parameter __stdcall, with zero bytes of callee cleanup",
      "confidence": "INFERRED",
      "id": "C5",
      "value": {
        "bytes": 0,
        "side": "caller"
      }
    },
    {
      "based_on": [
        "obs-0003",
        "obs-0024",
        "obs-0025",
        "obs-0028",
        "obs-0029"
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
        "obs-0001",
        "obs-0009",
        "obs-0010",
        "obs-0018",
        "obs-0022",
        "obs-0026",
        "obs-0030"
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
        "obs-0001",
        "obs-0009",
        "obs-0010",
        "obs-0018",
        "obs-0022",
        "obs-0026",
        "obs-0030"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_read_without_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0019",
        "obs-0023",
        "obs-0027",
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
        "obs-0031"
      ],
      "claim": "the return value is carried in ST0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "ST0"
    }
  ],
  "observations": [
    {
      "at": "0x00d2e380",
      "count": 1,
      "first_use": 0,
      "first_write_index": 7,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00d2e381",
      "count": 10,
      "first_use": 1,
      "first_write_index": null,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x8]",
      "reg": "ESP"
    },
    {
      "at": "0x00d2e381",
      "base": "ESP",
      "disp": 8,
      "id": "obs-0003",
      "index": 1,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x8]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00d2e381",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESP + 0x8]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00d2e385",
      "count": 6,
      "first_use": 2,
      "first_write_index": 2,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_READ",
      "raw": "XORPS XMM0,XMM0",
      "reg": "XMM0"
    },
    {
      "at": "0x00d2e385",
      "definite": true,
      "id": "obs-0006",
      "index"
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "pkg13_creature_accessor_00b1fdb0",
    "reconstructed": true,
    "va": "0x00b1fdb0"
  },
  {
    "name": "FUN_00b3d300",
    "reconstructed": true,
    "va": "0x00b3d300"
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
    "va": "0x00d2d0b0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d2e830"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d3fcf0"
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
      "0x00d2e380",
      "0x00d2e480",
      "0x00d2e8a0",
      "0x00d39360",
      "0x045ab96e",
      "0x00d2e480",
      "0x00aebe90",
      "0x045ab96e",
      "0x0067dcd0",
      "0x0067dcd0",
      "0x007d8420",
      "0x007d8420",
      "0x007d8cf0",
      "0x007d8cf0",
      "0x007d8d40",
      "0x007d8d40"
    ],
    "conflict_id": "U-005-evolution-level-promotion",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "0x45ab96e is a concrete action/message value with a guarded dispatch, but its consumer and brain-level/ability promotion are not identified.",
    "resolution_status": "0x45ab96e is a concrete action/message value with a guarded dispatch, but its consumer and brain-level/ability promotion are not identified.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00fe52c0",
      "0x00fe52c0",
      "0x00d2e350",
      "0x00d2e350",
      "0x00d2e380",
      "0x00d2e380",
      "0x00d2e480",
      "0x00d2e480",
      "0x00d2e8a0",
      "0x00d2e8a0",
      "0x00d3fcf0",
      "0x00d3fcf0",
      "0x00fe52c0",
      "0x00fe52c0",
      "0x00fe52c0",
      "0x00fe52c0"
    ],
    "conflict_id": "badge_state_domain",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
    "resolution_status": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00d2e380",
      "0x00d2e8a0",
      "0x045ab96e",
      "0x00d2e8a0",
      "0x045ab96e",
      "0x00594b10",
      "0x00594b10",
      "0x00596da0",
      "0x00596da0",
      "0x00597390",
      "0x00597390",
      "0x00597400",
      "0x00597400",
      "0x00598db0",
      "0x00598db0",
      "0x00598e90"
    ],
    "conflict_id": "brain_level_transition_writer",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
    "resolution_status": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00001278",
      "0x0000127c",
      "0x000010fc",
      "0x0000110c",
      "0x00001278",
      "0x0000127c",
      "0x00d2e350",
      "0x00d2e350",
      "0x00d2e380",
      "0x00d2e380",
      "0x00d2e480",
      "0x00d2e480",
      "0x00d2e8a0",
      "0x00d2e8a0",
      "0x00d3fcf0",
      "0x00d3fcf0"
    ],
    "conflict_id": "consequence_trait_rules",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00d2e380",
      "0x00d2e8a0",
      "0x00d2e8a0",
      "0x00d2e350",
      "0x00d2e350",
      "0x00d2e380",
      "0x00d2e380",
      "0x00d2e380",
      "0x00d2e480",
      "0x00d2e480",
      "0x00d2e8a0",
      "0x00d2e8a0",
      "0x00d2e8a0",
      "0x00d3fcf0",
      "0x00d3fcf0",
      "0x00feb880"
    ],
    "conflict_id": "evolution_numeric_thresholds",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00598db0",
      "0x00598db0",
      "0x00cc8c90",
      "0x00cc8c90",
      "0x00d2e350",
      "0x00d2e350",
      "0x00d2e380",
      "0x00d2e380",
      "0x00d2e480",
      "0x00d2e480",
      "0x00d2e8a0",
      "0x00d2e8a0",
      "0x00d3fcf0",
      "0x00d3fcf0",
      "0x00d2e350",
      "0x00d2e380"
    ],
    "conflict_id": "live_ghidra_progression_access",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The cited stream or file boundary is retained, but the complete wire/transaction/round-trip contract is not reconstructed.",
    "resolution_status": "The cited stream or file boundary is retained, but the complete wire/transaction/round-trip contract is not reconstructed.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00d2e350",
      "0x00d2e350",
      "0x00d2e380",
      "0x00d2e380",
      "0
[TRUNCATED]
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
  "count": 36,
  "instructions": [
    {
      "address": "00d2e380",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00d2e381",
      "instruction": "MOV EAX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "00d2e385",
      "instruction": "XORPS XMM0,XMM0"
    },
    {
      "address": "00d2e388",
      "instruction": "MOVSS dword ptr [ESP],XMM0"
    },
    {
      "address": "00d2e38d",
      "instruction": "CMP EAX,-0x1"
    },
    {
      "address": "00d2e390",
      "instruction": "JNZ 0x00d2e3aa"
    },
    {
      "address": "00d2e392",
      "instruction": "CALL 0x00b3d300"
    },
    {
      "address": "00d2e397",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00d2e399",
      "instruction": "CALL 0x00b1fdb0"
    },
    {
      "address": "00d2e39e",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00d2e3a0",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00d2e3a2",
      "instruction": "MOV EAX,dword ptr [EDX + 0xd8]"
    },
    {
      "address": "00d2e3a8",
      "instruction": "CALL EAX"
    },
    {
      "address": "00d2e3aa",
      "instruction": "CMP EAX,0x3"
    },
    {
      "address": "00d2e3ad",
      "instruction": "JA 0x00d2e3f9"
    },
    {
      "address": "00d2e3af",
      "instruction": "JMP dword ptr [EAX*0x4 + 0xd2e400]"
    },
    {
      "address": "00d2e3b6",
      "instruction": "MOVSS XMM0,dword ptr [0x01582e38]"
    },
    {
      "address": "00d2e3be",
      "instruction": "MOVSS dword ptr [ESP],XMM0"
    },
    {
      "address": "00d2e3c3",
      "instruction": "FLD float ptr [ESP]"
    },
    {
      "address": "00d2e3c6",
      "instruction": "POP ECX"
    },
    {
      "address": "00d2e3c7",
      "instruction": "RET"
    },
    {
      "address": "00d2e3c8",
      "instruction": "MOVSS XMM0,dword ptr [0x01582e3c]"
    },
    {
      "address": "00d2e3d0",
      "instruction": "MOVSS dword ptr [ESP],XMM0"
    },
    {
      "address": "00d2e3d5",
      "instruction": "FLD float ptr [ESP]"
    },
    {
      "address": "00d2e3d8",
      "instruction": "POP ECX"
    },
    {
      "address": "00d2e3d9",
      "instruction": "RET"
    },
    {
      "address": "00d2e3da",
      "instruction": "MOVSS XMM0,dword ptr [0x01582e40]"
    },
    {
      "address": "00d2e3e2",
      "instruction": "MOVSS dword ptr [ESP],XMM0"
    },
    {
      "address": "00d2e3e7",
      "instruction": "FLD float ptr [ESP]"
    },
    {
      "address": "00d2e3ea",
      "instruction": "POP ECX"
    },
    {
      "address": "00d2e3eb",
      "instruction": "RET"
    },
    {
      "address": "00d2e3ec",
      "instruction": "MOVSS XMM0,dword ptr [0x01582e44]"
    },
    {
      "address": "00d2e3f4",
      "instruction": "MOVSS dword ptr [ESP],XMM0"
    },
    {
      "address": "00d2e3f9",
      "instruction": "FLD float ptr [ESP]"
    },
    {
      "address": "00d2e3fc",
      "instruction": "POP ECX"
    },
    {
      "address": "00d2e3fd",
      "instruction": "RET"
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
  "original_bytes": 8206,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"cdecl-compatible from one stack argument and RET\",\n    \"hidden_this\": false,\n    \"return_register\": \"ST0\",\n    \"return_semantics\": \"Returns the selected mutable global float exactly; all levels outside 0 through 3 return positive 0.0F.\",\n    \"return_width_bytes\": 4,\n    \"stack_arguments\": [\n      {\n        \"after_push_ecx_offset\": \"ESP+0x08\",\n        \"entry_offset\": \"ESP+0x04\",\n        \"observed_use\": \"Signed comparison with -1, followed by unsigned CMP EAX,3 / JA table bounds check\",\n        \"position\": 1,\n        \"type\": \"std::int32_t\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 0\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-13-SIM-CREATURE-TRIBECIV\",\n      \"score\": 22,\n      \"symbol\": \"Simulator_cCreatureGameData_GetEvolutionPoints\",\n      \"va\": \"0x00d2e350\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-13-SIM-CREATURE-TRIBECIV\",\n      \"score\": 22,\n      \"symbol\": \"Simulator_cCreatureGameData_GetAbilityMode\",\n      \"va\": \"0x00d2e490\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-13-C3-CREATURE-PROGRESSION-WAVE2\",\n      \"score\": 14,\n      \"symbol\": \"Simulator_cCreatureGameData_Get_00d2e340\",\n      \"va\": \"0x00d2e340\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-13-C3-CREATURE-PROGRESSION-WAVE2\",\n      \"score\": 14,\n      \"symbol\": \"Simulator_cCreatureGameData_AddEvolutionPoints_raw_00d2e8a0\",\n      \"va\": \"0x00d2e8a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-11-H2-ROOT-ACCESSORS\",\n      \"score\": 8,\n      \"symbol\": \"root_accessor_00b3d3b0\",\n      \"va\": \"0x00b3d3b0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-11-H2-ROOT-ACCESSORS\",\n      \"score\": 8,\n      \"symbol\": \"root_accessor_00b3d3e0\",\n      \"va\": \"0x00b3d3e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-11-H2-ROOT-ACCESSORS\",\n      \"score\": 8,\n      \"symbol\": \"root_accessor_00b3d3f0\",\n      \"va\": \"0x00b3d3f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-11-H2-ROOT-ACCESSORS\",\n      \"score\": 8,\n      \"symbol\": \"root_accessor_00b3d430\",\n      \"va\": \"0x00b3d430\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"The -1 sentinel, local stack slot, four mutable threshold globals, unsigned bounds check, and function-pointer vtable slot are exact; root/object availability and the virtual implementation remain gated.\",\n  \"audit_findings\": [\n    \"PKG13-ABI-001\"\n  ],\n  \"audit_status\": \"clean_after_repair\",\n  \"blocked\": false,\n  \"blockers\": [\n    \"Runtime noun-manager/object availability and actual vtable dispatch remain gated.\"\n  ],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"None\",\n  \"cluster\": null,\n  \"confidence\": 0.9,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"pkg13_creature_accessor_00b1fdb0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b1fdb0\"\n      },\n      {\n        \"name\": \"FUN_00b3d300\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b3d300\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d2d0b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d2e830\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d3fcf0\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00d2d182\",\n        \"direction\": \"in\",\n        \"other\": \"0x00d2d0b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00d2e861\",\n        \"direction\": \"in\",\n        \"other\": \"0x00d2e830\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00d3fd13\",\n        \"direction\": \"in\",\n        \"other\": \"0x00d3fcf0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00d2e399\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b1fdb0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00d2e392\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b3d300\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 3,\n    \"fan_out\": 2,\n    \"manifest_callees\": [\n      \"0x00b3d300\",\n      \"0x00b1fdb0\",\n      \"vtable+0xd8\"\n    ],\n    \"manifest_callers\": [\n      \"0x00d2d0b0\",\n      \"0x00d2e830\",\n      \"0x00d3fcf0\"\n    ],\n    \"nearby_reconstructed\": [\n      \"0x00b1fdb0\",\n      \"0x00b3d300\"\n    ],\n    \"scc\": {\n      \"id\": \"scc-0499\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"SUPPORTED\",\n  \"globals\": [],\n  \"integration_status\": \"integrated\",\n  
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
  "body_end": "00d2e3fd",
  "body_span_bytes": 126,
  "body_start": "00d2e380",
  "callees": [
    "FUN_00b1fdb0",
    "FUN_00b3d300"
  ],
  "callers": [
    "FUN_00d2d0b0",
    "FUN_00d2e830",
    "FUN_00d3fcf0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00d2e380",
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
  "name": "Simulator::cCreatureGameData::GetEvoPointsToNextBrainLevel",
  "namespace": "Simulator",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 1,
  "parameters": [
    {
      "name": "currentLevel",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "int"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "float",
  "return_type_resolved": true,
  "rva": "0x92e380",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "float Simulator::cCreatureGameData::GetEvoPointsToNextBrainLevel(int currentLevel)",
  "size_bytes": 126,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00d2e380",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 3,
  "xrefs": [
    {
      "from": "00d2d182"
    },
    {
      "from": "00d2e861"
    },
    {
      "from": "00d3fd13"
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
  "file": "src/reconstruction/pkg13_creature_state/creature_state.cpp",
  "files": [
    "reconstruction/staging/pkg13-b0-creature-state/creature_state.cpp",
    "reconstruction/staging/pkg13-b0-creature-state/creature_state.hpp",
    "reconstruction/staging/pkg13-b0-creature-state/creature_state_test.cpp",
    "src/reconstruction/pkg13_creature_state/creature_state.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg13-b0-creature-state/00d2e380.json"
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
    "creature_brain_level_dispatch_observation"
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
  "BrainLevelVirtualTable",
  "None",
  "OpaqueCreatureGameDataObject",
  "OpaqueNounManager",
  "std::int32_t"
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
      "0x00d2e380",
      "0x00d2e480",
      "0x00d2e8a0",
      "0x00d39360",
      "0x045ab96e",
      "0x00d2e480",
      "0x00aebe90",
      "0x045ab96e",
      "0x0067dcd0",
      "0x0067dcd0",
      "0x007d8420",
      "0x007d8420",
      "0x007d8cf0",
      "0x007d8cf0",
      "0x007d8d40",
      "0x007d8d40"
    ],
    "conflict_id": "U-005-evolution-level-promotion",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "0x45ab96e is a concrete action/message value with a guarded dispatch, but its consumer and brain-level/ability promotion are not identified.",
    "resolution_status": "0x45ab96e is a concrete action/message value with a guarded dispatch, but its consumer and brain-level/ability promotion are not identified.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00fe52c0",
      "0x00fe52c0",
      "0x00d2e350",
      "0x00d2e350",
      "0x00d2e380",
      "0x00d2e380",
      "0x00d2e480",
      "0x00d2e480",
      "0x00d2e8a0",
      "0x00d2e8a0",
      "0x00d3fcf0",
      "0x00d3fcf0",
      "0x00fe52c0",
      "0x00fe52c0",
      "0x00fe52c0",
      "0x00fe52c0"
    ],
    "conflict_id": "badge_state_domain",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
    "resolution_status": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00d2e380",
      "0x00d2e8a0",
      "0x045ab96e",
      "0x00d2e8a0",
      "0x045ab96e",
      "0x00594b10",
      "0x00594b10",
      "0x00596da0",
      "0x00596da0",
      "0x00597390",
      "0x00597390",
      "0x00597400",
      "0x00597400",
      "0x00598db0",
      "0x00598db0",
      "0x00598e90"
    ],
    "conflict_id": "brain_level_transition_writer",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
    "resolution_status": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00001278",
      "0x0000127c",
      "0x000010fc",
      "0x0000110c",
      "0x00001278",
      "0x0000127c",
      "0x00d2e350",
      "0x00d2e350",
      "0x00d2e380",
      "0x00d2e380",
      "0x00d2e480",
      "0x00d2e480",
      "0x00d2e8a0",
      "0x00d2e8a0",
      "0x00d3fcf0",
      "0x00d3fcf0"
    ],
    "conflict_id": "consequence_trait_rules",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00d2e380",
      "0x00d2e8a0",
      "0x00d2e8a0",
      "0x00d2e350",
      "0x00d2e350",
      "0x00d2e380",
      "0x00d2e380",
      "0x00d2e380",
      "0x00d2e480",
      "0x00d2e480",
      "0x00d2e8a0",
      "0x00d2e8a0",
      "0x00d2e8a0",
      "0x00d3fcf0",
      "0x00d3fcf0",
      "0x00feb880"
    ],
    "conflict_id": "evolution_numeric_thresholds",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00598db0",
      "0x00598db0",
      "0x00
[TRUNCATED]
```
