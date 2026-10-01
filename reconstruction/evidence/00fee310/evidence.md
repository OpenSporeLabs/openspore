# Evidence 0x00fee310

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `3ff50ccfb64a2a935560e3e28bf050e642bc836eca806665528f25b2c33d7a29`

## abi

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "abi": {
    "architecture": "x86-32",
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
    "saved_registers": [
      "EDI",
      "ESI"
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "receiver_not_determinable: ecx_reassigned_before_deref",
    "esp_alignment_unknown: the entry-relative ESP offset is unknown and there is no frame pointer to fall back on"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "d8a7213cf46784e56ced847f88f9e43d1b630168565985331739a979d5c7e513",
  "conventions": {
    "ambiguities": [
      "esp_alignment_unknown"
    ],
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
    "ghidra_parameter_count": 2,
    "persisted": "no_information",
    "persisted_calling_convention": null
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 2,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
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
        "obs-0004",
        "obs-0008"
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
        "obs-0027"
      ],
      "claim": "the entry-relative argument offsets are unknown, so the convention is unknown",
      "confidence": "UNKNOWN",
      "id": "C11"
    },
    {
      "based_on": [
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
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0031"
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
      "at": "0x00fee310",
      "count": 7,
      "first_use": 0,
      "first_write_index": 2,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00fee311",
      "count": 1,
      "first_use": 1,
      "first_write_index": 42,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00fee312",
      "count": 4,
      "first_use": 2,
      "first_write_index": 5,
      "id": "obs-0003",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00fee312",
      "definite": true,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00fee314",
      "id": "obs-0005",
      "index": 3,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00b3d330",
      "target": "0x00b3d330"
    },
    {
      "at": "0x00fee319",
      "count": 11,
      "first_use": 4,
      "first_write_index": 6,
      "id": "obs-0006",
      "index": 4,
      "kind": "REG_READ",
      "raw": "MOV EDX,dword ptr [EAX]",
      "reg": "EAX"
    },
    {
      "at": "0x00fee319",
      "definite": true,
      "id": "obs-0007",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [EAX]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00fee31b",
      "definite": true,
      "id": "obs-0008",
      "index": 5,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,EAX",
      "reg": "ECX",
      "write_kind": "reg"
    },
    {
      "at": "0x00fee31d",
      "count": 4,
      "first_use": 6,
      "first_write_index": 4,
      "id": "obs-0009",
      "index": 6,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [EDX + 0x50]",
      "reg": "EDX"
    },
    {
      "at": "0x00fee31d",
      "definite": true,
      "id": "obs-0010",
      "index": 6,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [EDX + 0x50]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00fee321",
      "base": "EAX",
      "disp": null,
      "id": "obs-0011",
      "index": 8,
      "kind": "CALL_INDIRECT",
      "raw": "CALL EAX",
      "via": "register"
    },
    {
      "at": "0x00fee325",
      "id": "obs-0012",
      "index": 10,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00fed0b0",
      "target": "0x00fed0b0"
    },
    {
      "at": "0x00fee32a",
      "id": "obs-0013",
      "index": 11,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00fef670",
      "target": "0x00fef670"
    },
    {
      "at": "0x00fee331",
      "id": "obs-0014",
      "index": 13,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00c2e4e0",
      "target": "0x00c2e4e0"
    },
    {
      "at": "0x00fee33f",
      "id":
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
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
    "saved_registers": [
      "EDI",
      "ESI"
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "receiver_not_determinable: ecx_reassigned_before_deref",
    "esp_alignment_unknown: the entry-relative ESP offset is unknown and there is no frame pointer to fall back on"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "d8a7213cf46784e56ced847f88f9e43d1b630168565985331739a979d5c7e513",
  "conventions": {
    "ambiguities": [
      "esp_alignment_unknown"
    ],
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
    "ghidra_parameter_count": 2,
    "persisted": "no_information",
    "persisted_calling_convention": null
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 2,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
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
        "obs-0004",
        "obs-0008"
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
        "obs-0027"
      ],
      "claim": "the entry-relative argument offsets are unknown, so the convention is unknown",
      "confidence": "UNKNOWN",
      "id": "C11"
    },
    {
      "based_on": [
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
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0031"
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
      "at": "0x00fee310",
      "count": 7,
      "first_use": 0,
      "first_write_index": 2,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00fee311",
      "count": 1,
      "first_use": 1,
      "first_write_index": 42,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00fee312",
      "count": 4,
      "first_use": 2,
      "first_write_index": 5,
      "id": "obs-0003",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00fee312",
      "definite": true,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00fee314",
      "id": "obs-0005",
      "index": 3,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00b3d330",
      "target": "0x00b3d330"
    },
    {
      "at": "0x00fee319",
      "count": 11,
      "first_use": 4,
      "first_write_index": 6,
      "id": "obs-0006",
      "index": 4,
      "kind": "REG_READ",
      "raw": "MOV EDX,dword ptr [EAX]",
      "reg": "EAX"
    },
    {
      "at": "0x00fee319",
      "definite": true,
      "id": "obs-0007",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [EAX]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00fee31b",
      "definite": true,
      "id": "obs-0008",
      "index": 5,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,EAX",
      "reg": "ECX",
      "write_kind": "reg"
    },
    {
      "at": "0x00fee31d",
      "count": 4,
      "first_use": 6,
      "first_write_index": 4,
      "id": "obs-0009",
      "index": 6,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [EDX + 0x50]",
      "reg": "EDX"
    },
    {
      "at": "0x00fee31d",
      "definite": true,
      "id": "obs-0010",
      "index": 6,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [EDX + 0x50]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00fee321",
      "base": "EAX",
      "disp": null,
      "id": "obs-0011",
      "index": 8,
      "kind": "CALL_INDIRECT",
      "raw": "CALL EAX",
      "via": "register"
    },
    {
      "at": "0x00fee325",
      "id": "obs-0012",
      "index": 10,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00fed0b0",
      "target": "0x00fed0b0"
    },
    {
      "at": "0x00fee32a",
      "id": "obs-0013",
      "index": 11,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00fef670",
      "target": "0x00fef670"
    },
    {
      "at": "0x00fee331",
      "id": "obs-0014",
      "index": 13,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00c2e4e0",
      "target": "0x00c2e4e0"
    },
    {
      "at": "0x00fee33f",
      "id":
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "pkg11_sim_core_00b21340",
    "reconstructed": true,
    "va": "0x00b21340"
  },
  {
    "name": "FUN_00b3d300",
    "reconstructed": true,
    "va": "0x00b3d300"
  },
  {
    "name": "FUN_00c2e4e0",
    "reconstructed": false,
    "va": "0x00c2e4e0"
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
    "va": "0x01007430"
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
      "0x00cc8c90",
      "0x00cc8c90",
      "0x00feb880",
      "0x00feb880",
      "0x00febce0",
      "0x00febce0",
      "0x00fec420",
      "0x00fec420",
      "0x00fee020",
      "0x00fee020",
      "0x00fee260",
      "0x00fee260",
      "0x00fee310",
      "0x00fee310",
      "0x00feebc0",
      "0x00feebc0"
    ],
    "conflict_id": "herd_evolution_transition",
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
      "0x00ff3bf0",
      "0x00feb880",
      "0x00feb880",
      "0x00febce0",
      "0x00febce0",
      "0x00fec420",
      "0x00fec420",
      "0x00fee020",
      "0x00fee020",
      "0x00fee260",
      "0x00fee260",
      "0x00fee310",
      "0x00fee310",
      "0x00feebc0",
      "0x00feebc0",
      "0x00ff3bf0"
    ],
    "conflict_id": "mission_reward_payout",
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
      "0x00fe52c0",
      "0x00fe52c0",
      "0x00feb880",
      "0x00feb880",
      "0x00febce0",
      "0x00febce0",
      "0x00fec420",
      "0x00fec420",
      "0x00fee020",
      "0x00fee020",
      "0x00fee260",
      "0x00fee260",
      "0x00fee310",
      "0x00fee310",
      "0x00feebc0",
      "0x00feebc0"
    ],
    "conflict_id": "progression_runtime_validation",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "A positive hash-pinned original-process trace is required; static naming or conceptual state names are not promoted to runtime behavior.",
    "resolution_status": "A positive hash-pinned original-process trace is required; static naming or conceptual state names are not promoted to runtime behavior.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "No positive original-process trace reaches this transition in the committed corpus."
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
      "address": "00fee310",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00fee311",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00fee312",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00fee314",
      "instruction": "CALL 0x00b3d330"
    },
    {
      "address": "00fee319",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00fee31b",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00fee31d",
      "instruction": "MOV EAX,dword ptr [EDX + 0x50]"
    },
    {
      "address": "00fee320",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00fee321",
      "instruction": "CALL EAX"
    },
    {
      "address": "00fee323",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00fee325",
      "instruction": "CALL 0x00fed0b0"
    },
    {
      "address": "00fee32a",
      "instruction": "CALL 0x00fef670"
    },
    {
      "address": "00fee32f",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00fee331",
      "instruction": "CALL 0x00c2e4e0"
    },
    {
      "address": "00fee336",
      "instruction": "LEA ECX,[ESI + 0x20]"
    },
    {
      "address": "00fee339",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00fee33a",
      "instruction": "PUSH 0x6b5005e"
    },
    {
      "address": "00fee33f",
      "instruction": "CALL 0x00fef670"
    },
    {
      "address": "00fee344",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00fee346",
      "instruction": "CALL 0x00fef9f0"
    },
    {
      "address": "00fee34b",
      "instruction": "LEA EDX,[ESI + 0x34]"
    },
    {
      "address": "00fee34e",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00fee34f",
      "instruction": "PUSH 0x994d1f83"
    },
    {
      "address": "00fee354",
      "instruction": "CALL 0x00fef670"
    },
    {
      "address": "00fee359",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00fee35b",
      "instruction": "CALL 0x00fef9f0"
    },
    {
      "address": "00fee360",
      "instruction": "ADD ESI,0x48"
    },
    {
      "address": "00fee363",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00fee364",
      "instruction": "PUSH 0xa07f6fd6"
    },
    {
      "address": "00fee369",
      "instruction": "CALL 0x00fef670"
    },
    {
      "address": "00fee36e",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00fee370",
      "instruction": "CALL 0x00fef9f0"
    },
    {
      "address": "00fee375",
      "instruction": "CALL 0x00c44f50"
    },
    {
      "address": "00fee37a",
      "instruction": "CALL 0x00b3d300"
    },
    {
      "address": "00fee37f",
      "instruction": "PUSH 0x2aa5ada"
    },
    {
      "address": "00fee384",
      "instruction": "PUSH 0xb1e520"
    },
    {
      "address": "00fee389",
      "instruction": "PUSH 0xfed010"
    },
    {
      "address": "00fee38e",
      "instruction": "PUSH 0xd3d420"
    },
    {
      "address": "00fee393",
      "instruction": "PUSH 0xcd7d10"
    },
    {
      "address": "00fee398",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00fee39a",
      "instruction": "CALL 0x00b21340"
    },
    {
      "address": "00fee39f",
      "instruction": "MOV ESI,dword ptr [EAX + 0x4]"
    },
    {
      "address": "00fee3a2",
      "instruction": "MOV EDI,dword ptr [EAX + 0x8]"
    },
    {
      "address": "00fee3a5",
      "instruction": "ADD EAX,0x4"
    },
    {
      "address": "00fee3a8",
      "instruction": "CMP ESI,EDI"
    },
    {
      "address": "00fee3aa",
      "instruction": "JZ 0x00fee3c7"
    },
    {
      "address": "00fee3ac",
      "instruction": "LEA ESP,[ESP]"
    },
    {
      "address": "00fee3b0",
      "instruction": "MOV ECX,dword ptr [ESI]"
    },
    {
      "address": "00fee3b2",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00fee3b4",
      "instruction": "JZ 0x00fee3c0"
    },
    {
      "address": "00fee3b6",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "00fee3b8",
      "instruction": "MOV EDX,dword ptr [EAX + 0x80]"
    },
    {
      "address": "00fee3be",
      "instruction": "CALL EDX"
    },
    {
      "address": "00fee3c0",
      "instruction": "ADD ESI,0x4"
    },
    {
      "address": "00fee3c3",
      "instruction": "CMP ESI,EDI"
    },
    {
      "address": "00fee3c5",
      "instruction": "JNZ 0x00fee3b0"
    },
    {
      "address": "00fee3c7",
      "instruction": "POP EDI"
    },
    {
      "address": "00fee3c8",
      "instruction": "POP ESI"
    },
    {
      "address": "00fee3c9",
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
  "original_bytes": 7329,
  "preview": "{\n  \"abi\": {},\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_class\",\n        \"shared_types:MissionManagerWire\"\n      ],\n      \"package\": \"PKG-11-A2-PROGRESSION-ALTERNATIVE\",\n      \"score\": 16,\n      \"symbol\": \"mission_track_predicate_00febc90\",\n      \"va\": \"0x00febc90\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-11-A2-PROGRESSION-ALTERNATIVE\",\n      \"score\": 8,\n      \"symbol\": \"achievement_progress_update_00676e90\",\n      \"va\": \"0x00676e90\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:MissionManagerWire\"\n      ],\n      \"package\": \"PKG-11-A3-ACHIEVEMENT-MISSION-WAVE2\",\n      \"score\": 8,\n      \"symbol\": \"mission_manager_record_init_00fec3c0\",\n      \"va\": \"0x00fec3c0\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-11-SIM-CORE\",\n      \"score\": 3,\n      \"symbol\": \"pkg11_sim_core_00b21340\",\n      \"va\": \"0x00b21340\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 3,\n      \"symbol\": \"FUN_00b3d300\",\n      \"va\": \"0x00b3d300\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": \"clean\",\n  \"blocked\": false,\n  \"blockers\": [\n    \"No original-process mission initialization trace was run.\",\n    \"Simulator vtable +0x50, registry builder, noun projection callback, and projection-entry concrete types remain opaque.\"\n  ],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"MissionManagerWire\",\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"pkg11_sim_core_00b21340\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b21340\"\n      },\n      {\n        \"name\": \"FUN_00b3d300\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b3d300\"\n      },\n      {\n        \"name\": \"FUN_00c2e4e0\",\n        \"reconstructed\": false,\n        \"va\": \"0x00c2e4e0\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x01007430\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x0100751f\",\n        \"direction\": \"in\",\n        \"other\": \"0x01007430\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00fee39a\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b21340\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00fee37a\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b3d300\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00fee314\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b3d330\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00fee331\",\n        \"direction\": \"out\",\n        \"other\": \"0x00c2e4e0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00fee375\",\n        \"direction\": \"out\",\n        \"other\": \"0x00c44f50\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00fee325\",\n        \"direction\": \"out\",\n        \"other\": \"0x00fed0b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00fee32a\",\n        \"direction\": \"out\",\n        \"other\": \"0x00fef670\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00fee33f\",\n        \"direction\": \"out\",\n        \"other\": \"0x00fef670\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00fee354\",\n        \"direction\": \"out\",\n        \"other\": \"0x00fef670\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00fee369\",\n        \"direction\": \"out\",\n        \"other\": \"0x00fef670\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00fee346\",\n        \"direction\": \"out\",\n        \"other\": \"0x00fef9f0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00fee35b\",\n        \"direction\": \"out\",\n        \"other\": \"0x00fef9f0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00fee370\",\n        \"direction\": \"out\",\n        \"other\": \"0x00fef9f0\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 1,\n    \"fan_out\": 3,\n    \"manifest_callees\": [\n      \"0x00b3d330\",\n      \"vtable+0x50\",\n      \"0x00fed0b0\",\n      \"0x00fef670\",\n      \"0x00c2e4e0\",\n      \"0x00fef9f0\",\n      \"0x00c44f50\",\n      \"0x00b3d300\",\n      \"0x00b21340\",\n      \"projection-vtable+0x80\"\n    ],\n    \"manifest_callers\": [\n      \"0x01007430\"\n    ],\n    \"nearby_reconstructed\": [\n      \"0x00b21340\",\n      \"0x00b3d300\"\n    ],\n    \"scc\": {\n      \"id\": \"scc-0586\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"SUPPORTED\",\n  \"globals\": [],\n  \"integration_status\": \"integrated\",\n  \"name\": \"mission_manager_operation_00fee310\",\n  \"normalized_symbol\": \"mission_manager_operation_00fee310\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"do_not_claim\",\n    \"handoff_packages\": [\n      \"PKG-11-A2-PROGRESSION-ALTERNATIVE\"\n    ],\n  
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
  "body_end": "00fee3c9",
  "body_span_bytes": 186,
  "body_start": "00fee310",
  "callees": [
    "FUN_00c2e4e0",
    "FUN_00b21340",
    "FUN_00fed0b0",
    "FUN_00fef670",
    "FUN_00fef9f0",
    "FUN_00c44f50",
    "FUN_00b3d300",
    "Simulator::cSimulatorSystem::Get"
  ],
  "callers": [
    "FUN_01007430"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00fee310",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "Simulator::cMissionManager::GetMissionByID",
  "namespace": "Simulator",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 2,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "cMissionManager *"
    },
    {
      "name": "missionID",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "uint32_t"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "cMission *",
  "return_type_resolved": true,
  "rva": "0xbee310",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "cMission * Simulator::cMissionManager::GetMissionByID(cMissionManager * this, uint32_t missionID)",
  "size_bytes": 186,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00fee310",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "0100751f"
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
    "reconstruction/metadata/pkg11-a2-progression-alt/00fee310.json"
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
    "gate-mission-manager-initialization-00fee310",
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
  "MissionManagerWire",
  "MissionProjectionVectorWire"
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
      "0x00cc8c90",
      "0x00cc8c90",
      "0x00feb880",
      "0x00feb880",
      "0x00febce0",
      "0x00febce0",
      "0x00fec420",
      "0x00fec420",
      "0x00fee020",
      "0x00fee020",
      "0x00fee260",
      "0x00fee260",
      "0x00fee310",
      "0x00fee310",
      "0x00feebc0",
      "0x00feebc0"
    ],
    "conflict_id": "herd_evolution_transition",
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
      "0x00ff3bf0",
      "0x00feb880",
      "0x00feb880",
      "0x00febce0",
      "0x00febce0",
      "0x00fec420",
      "0x00fec420",
      "0x00fee020",
      "0x00fee020",
      "0x00fee260",
      "0x00fee260",
      "0x00fee310",
      "0x00fee310",
      "0x00feebc0",
      "0x00feebc0",
      "0x00ff3bf0"
    ],
    "conflict_id": "mission_reward_payout",
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
      "0x00fe52c0",
      "0x00fe52c0",
      "0x00feb880",
      "0x00feb880",
      "0x00febce0",
      "0x00febce0",
      "0x00fec420",
      "0x00fec420",
      "0x00fee020",
      "0x00fee020",
      "0x00fee260",
      "0x00fee260",
      "0x00fee310",
      "0x00fee310",
      "0x00feebc0",
      "0x00feebc0"
    ],
    "conflict_id": "progression_runtime_validation",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "A positive hash-pinned original-process trace is required; static naming or conceptual state names are not promoted to runtime behavior.",
    "resolution_status": "A positive hash-pinned original-process trace is required; static naming or conceptual state names are not promoted to runtime behavior.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "No positive original-process trace reaches this transition in the committed corpus."
  }
]
```
