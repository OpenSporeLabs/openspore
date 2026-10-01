# Evidence 0x00d2e8a0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `d6fa7e4a804ce3784d0155053a2f2e88cbb5933e0d27998f427770e52aeffb0c`

## abi

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
    "flow_not_modelled: the linear ESP walk ends at +12, so the listing is not one path",
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
  "content_sha256": "6d9899e46ce4c4cfc717c2c7dd5ee9ce75052b027e05f283e887f0d7654253a8",
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
        "obs-0034"
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
        "obs-0002",
        "obs-0016",
        "obs-0021"
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
        "obs-0014",
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
        "obs-0014",
        "obs-0022"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_read_without_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0034"
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
        "obs-0004"
      ],
      "claim": "the return value is carried in ST0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "ST0"
    }
  ],
  "observations": [
    {
      "at": "0x00d2e8a0",
      "count": 11,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOVSS XMM1,dword ptr [ESP + 0x4]",
      "reg": "ESP"
    },
    {
      "at": "0x00d2e8a0",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0002",
      "index": 0,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOVSS XMM1,dword ptr [ESP + 0x4]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00d2e8a0",
      "definite": true,
      "id": "obs-0003",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOVSS XMM1,dword ptr [ESP + 0x4]",
      "reg": "XMM1",
      "write_kind": "unknown"
    },
    {
      "and_esp": null,
      "at": "0x00d2e8a6",
      "ebp_is_general_register": false,
      "fp": false,
      "id": "obs-0004",
      "index": 1,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": false,
      "push_ebp_at": null,
      "raw": "SUB ESP,0x1c",
      "sub": 28
    },
    {
      "at": "0x00d2e8a6",
      "definite": true,
      "id": "obs-0005",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x1c",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00d2e8a9",
      "count": 3,
      "first_use": 2,
      "first_write_index": 0,
      "id": "obs-0006",
      "index": 2,
      "kind": "REG_READ",
      "raw": "UCOMISS XMM1,dword ptr [0x01485378]",
      "reg": "XMM1"
    },
    {
      "at": "0x00d2e8ba",
      "definite": true,
      "id": "obs-0007",
      "index": 6,
      "kind": "REG_WRITE",
      "raw": "MOVSS XMM0,dword ptr [0x0169e398]",
      "reg": "XMM0",
      "write_kind": "unknown"
    },
    {
      "at": "0x00d2e8ce",
      "count": 5,
      "first_use": 9,
      "first_write_index": 6,
      "id": "obs-0008",
      "index": 9,
      "kind": "REG_READ",
      "raw": "COMISS XMM1,XMM0",
      "reg": "XMM0"
    },
    {
      "at": "0x00d2e8d1",
      "base": "ESP",
      "disp": 0,
      "id": "obs-0009",
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
    "ret_form": "RET",
    "return_register": "ST0",
    "return_semantics": "float_or_x87_in_ST0",
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
    "flow_not_modelled: the linear ESP walk ends at +12, so the listing is not one path",
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
  "content_sha256": "6d9899e46ce4c4cfc717c2c7dd5ee9ce75052b027e05f283e887f0d7654253a8",
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
        "obs-0034"
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
        "obs-0002",
        "obs-0016",
        "obs-0021"
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
        "obs-0014",
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
        "obs-0014",
        "obs-0022"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_read_without_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0034"
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
        "obs-0004"
      ],
      "claim": "the return value is carried in ST0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "ST0"
    }
  ],
  "observations": [
    {
      "at": "0x00d2e8a0",
      "count": 11,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOVSS XMM1,dword ptr [ESP + 0x4]",
      "reg": "ESP"
    },
    {
      "at": "0x00d2e8a0",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0002",
      "index": 0,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOVSS XMM1,dword ptr [ESP + 0x4]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00d2e8a0",
      "definite": true,
      "id": "obs-0003",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOVSS XMM1,dword ptr [ESP + 0x4]",
      "reg": "XMM1",
      "write_kind": "unknown"
    },
    {
      "and_esp": null,
      "at": "0x00d2e8a6",
      "ebp_is_general_register": false,
      "fp": false,
      "id": "obs-0004",
      "index": 1,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": false,
      "push_ebp_at": null,
      "raw": "SUB ESP,0x1c",
      "sub": 28
    },
    {
      "at": "0x00d2e8a6",
      "definite": true,
      "id": "obs-0005",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x1c",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00d2e8a9",
      "count": 3,
      "first_use": 2,
      "first_write_index": 0,
      "id": "obs-0006",
      "index": 2,
      "kind": "REG_READ",
      "raw": "UCOMISS XMM1,dword ptr [0x01485378]",
      "reg": "XMM1"
    },
    {
      "at": "0x00d2e8ba",
      "definite": true,
      "id": "obs-0007",
      "index": 6,
      "kind": "REG_WRITE",
      "raw": "MOVSS XMM0,dword ptr [0x0169e398]",
      "reg": "XMM0",
      "write_kind": "unknown"
    },
    {
      "at": "0x00d2e8ce",
      "count": 5,
      "first_use": 9,
      "first_write_index": 6,
      "id": "obs-0008",
      "index": 9,
      "kind": "REG_READ",
      "raw": "COMISS XMM1,XMM0",
      "reg": "XMM0"
    },
    {
      "at": "0x00d2e8d1",
      "base": "ESP",
      "disp": 0,
      "id": "obs-0009",
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
  },
  {
    "name": "FUN_00b5b800",
    "reconstructed": false,
    "va": "0x00b5b800"
  },
  {
    "name": "FUN_00d38840",
    "reconstructed": false,
    "va": "0x00d38840"
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
    "va": "0x00c07480"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c2ed20"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d35190"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d46c30"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d71060"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d71780"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d85ad0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d87620"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d9bc70"
  }
]
```

## contradictions

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "original_bytes": 9562,
  "preview": "[\n  {\n    \"anchors\": [\n      \"0x00d2e380\",\n      \"0x00d2e480\",\n      \"0x00d2e8a0\",\n      \"0x00d39360\",\n      \"0x045ab96e\",\n      \"0x00d2e480\",\n      \"0x00aebe90\",\n      \"0x045ab96e\",\n      \"0x0067dcd0\",\n      \"0x0067dcd0\",\n      \"0x007d8420\",\n      \"0x007d8420\",\n      \"0x007d8cf0\",\n      \"0x007d8cf0\",\n      \"0x007d8d40\",\n      \"0x007d8d40\"\n    ],\n    \"conflict_id\": \"U-005-evolution-level-promotion\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"0x45ab96e is a concrete action/message value with a guarded dispatch, but its consumer and brain-level/ability promotion are not identified.\",\n    \"resolution_status\": \"0x45ab96e is a concrete action/message value with a guarded dispatch, but its consumer and brain-level/ability promotion are not identified.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x01037d30\",\n      \"0x01037d30\",\n      \"0x01037d30\",\n      \"0x01037d30\",\n      \"0x0103a480\",\n      \"0x0103a480\",\n      \"0x0103e8e0\",\n      \"0x0103e8e0\",\n      \"0x0103fc10\",\n      \"0x0103fc10\",\n      \"0x00c877f0\",\n      \"0x00c877f0\",\n      \"0x00596da0\",\n      \"0x01037d30\",\n      \"0x00d2e8a0\",\n      \"0x0103e8e0\"\n    ],\n    \"conflict_id\": \"U-E004\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.\",\n    \"resolution_status\": \"The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00596da0\",\n      \"0x01037d30\",\n      \"0x00d2e8a0\"\n    ],\n    \"conflict_id\": \"U-E012\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.\",\n    \"resolution_status\": \"The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00fe52c0\",\n      \"0x00fe52c0\",\n      \"0x00d2e350\",\n      \"0x00d2e350\",\n      \"0x00d2e380\",\n      \"0x00d2e380\",\n      \"0x00d2e480\",\n      \"0x00d2e480\",\n      \"0x00d2e8a0\",\n      \"0x00d2e8a0\",\n      \"0x00d3fcf0\",\n      \"0x00d3fcf0\",\n      \"0x00fe52c0\",\n      \"0x00fe52c0\",\n      \"0x00fe52c0\",\n      \"0x00fe52c0\"\n    ],\n    \"conflict_id\": \"badge_state_domain\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.\",\n    \"resolution_status\": \"The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00d2e380\",\n      \"0x00d2e8a0\",\n      \"0x045ab96e\",\n      \"0x00d2e8a0\",\n      \"0x045ab96e\",\n      \"0x00594b10\",\n      \"0x00594b10\",\n      \"0x00596da0\",\n      \"0x00596da0\",\n      \"0x00597390\",\n      \"0x00597390\",\n      \"0x00597400\",\n      \"0x00597400\",\n      \"0x00598db0\",\n      \"0x00598db0\",\n      \"0x00598e90\"\n    ],\n    \"conflict_id\": \"brain_level_transition_writer\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.\",\n    \"resolution_status\": \"The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00001278\",\n      \"0x0000127c\",\n      \"0x000010fc\",\n      \"0x0000110c\",\n      \"0x00001278\",\n      \"0x0000127c\",\n      \"0x00d2e350\",\n      \"0x00d2e350\",\n      \"0x00d2e380\",\n      \"0x00d2e380\",\n      \"0x00d2e480\",\n      \"0x00d2e480\",\n      \"0x00d2e8a0\",\n      \"0x00d2e8a0\",\n      \"0x00d3fcf0\",\n      \"0x00d3fcf0\"\n    ],\n    \"conflict_id\": \"consequence_trait_rules\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.\",\n    \"resolution_status\": \"The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-st
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
  "count": 51,
  "instructions": [
    {
      "address": "00d2e8a0",
      "instruction": "MOVSS XMM1,dword ptr [ESP + 0x4]"
    },
    {
      "address": "00d2e8a6",
      "instruction": "SUB ESP,0x1c"
    },
    {
      "address": "00d2e8a9",
      "instruction": "UCOMISS XMM1,dword ptr [0x01485378]"
    },
    {
      "address": "00d2e8b0",
      "instruction": "LAHF"
    },
    {
      "address": "00d2e8b1",
      "instruction": "TEST AH,0x44"
    },
    {
      "address": "00d2e8b4",
      "instruction": "JNP 0x00d2e96d"
    },
    {
      "address": "00d2e8ba",
      "instruction": "MOVSS XMM0,dword ptr [0x0169e398]"
    },
    {
      "address": "00d2e8c2",
      "instruction": "ADDSS XMM0,XMM1"
    },
    {
      "address": "00d2e8c6",
      "instruction": "MOVSS XMM1,dword ptr [0x01582e54]"
    },
    {
      "address": "00d2e8ce",
      "instruction": "COMISS XMM1,XMM0"
    },
    {
      "address": "00d2e8d1",
      "instruction": "MOVSS dword ptr [ESP],XMM0"
    },
    {
      "address": "00d2e8d6",
      "instruction": "LEA EAX,[ESP]"
    },
    {
      "address": "00d2e8d9",
      "instruction": "JA 0x00d2e8e0"
    },
    {
      "address": "00d2e8db",
      "instruction": "MOV EAX,0x1582e54"
    },
    {
      "address": "00d2e8e0",
      "instruction": "MOVSS XMM0,dword ptr [EAX]"
    },
    {
      "address": "00d2e8e4",
      "instruction": "MOVSS dword ptr [0x0169e398],XMM0"
    },
    {
      "address": "00d2e8ec",
      "instruction": "CALL 0x00b3d300"
    },
    {
      "address": "00d2e8f1",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00d2e8f3",
      "instruction": "CALL 0x00f67d90"
    },
    {
      "address": "00d2e8f8",
      "instruction": "MOVSS XMM0,dword ptr [EAX + 0x10f0]"
    },
    {
      "address": "00d2e900",
      "instruction": "ADDSS XMM0,dword ptr [ESP + 0x20]"
    },
    {
      "address": "00d2e906",
      "instruction": "ADD EAX,0x10f0"
    },
    {
      "address": "00d2e90b",
      "instruction": "MOVSS dword ptr [EAX],XMM0"
    },
    {
      "address": "00d2e90f",
      "instruction": "CALL 0x00b5b800"
    },
    {
      "address": "00d2e914",
      "instruction": "CMP EAX,0x1654c10"
    },
    {
      "address": "00d2e919",
      "instruction": "JZ 0x00d2e96d"
    },
    {
      "address": "00d2e91b",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00d2e91c",
      "instruction": "CALL 0x00d38840"
    },
    {
      "address": "00d2e921",
      "instruction": "MOV ESI,EAX"
    },
    {
      "address": "00d2e923",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "00d2e925",
      "instruction": "JZ 0x00d2e96c"
    },
    {
      "address": "00d2e927",
      "instruction": "FLD float ptr [ESP + 0x24]"
    },
    {
      "address": "00d2e92b",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00d2e92c",
      "instruction": "MOV ECX,dword ptr [ESI + 0x68]"
    },
    {
      "address": "00d2e92f",
      "instruction": "FSTP float ptr [ESP]"
    },
    {
      "address": "00d2e932",
      "instruction": "CALL 0x00d2e2e0"
    },
    {
      "address": "00d2e937",
      "instruction": "CALL 0x00b3d300"
    },
    {
      "address": "00d2e93c",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00d2e93e",
      "instruction": "CALL 0x00b1fdb0"
    },
    {
      "address": "00d2e943",
      "instruction": "MOVSS XMM0,dword ptr [ESP + 0x24]"
    },
    {
      "address": "00d2e949",
      "instruction": "MOV dword ptr [ESP + 0x8],EAX"
    },
    {
      "address": "00d2e94d",
      "instruction": "LEA EAX,[ESP + 0x8]"
    },
    {
      "address": "00d2e951",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00d2e952",
      "instruction": "PUSH 0x45ab96e"
    },
    {
      "address": "00d2e957",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00d2e959",
      "instruction": "MOV dword ptr [ESP + 0x14],0x0"
    },
    {
      "address": "00d2e961",
      "instruction": "MOVSS dword ptr [ESP + 0x18],XMM0"
    },
    {
      "address": "00d2e967",
      "instruction": "CALL 0x00d39360"
    },
    {
      "address": "00d2e96c",
      "instruction": "POP ESI"
    },
    {
      "address": "00d2e96d",
      "instruction": "ADD ESP,0x1c"
    },
    {
      "address": "00d2e970",
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
  "original_bytes": 11152,
  "preview": "{\n  \"abi\": {},\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:None,UNCONDITIONAL_CALL\"\n      ],\n      \"package\": \"PKG-13-C3-CREATURE-PROGRESSION-WAVE2\",\n      \"score\": 25,\n      \"symbol\": \"Simulator_cCreatureGameData_Get_00d2e340\",\n      \"va\": \"0x00d2e340\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-13-SIM-CREATURE-TRIBECIV\",\n      \"score\": 14,\n      \"symbol\": \"Simulator_cCreatureGameData_GetEvolutionPoints\",\n      \"va\": \"0x00d2e350\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-13-SIM-CREATURE-TRIBECIV\",\n      \"score\": 14,\n      \"symbol\": \"Simulator_cCreatureGameData_GetEvoPointsToNextBrainLevel\",\n      \"va\": \"0x00d2e380\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-13-SIM-CREATURE-TRIBECIV\",\n      \"score\": 14,\n      \"symbol\": \"Simulator_cCreatureGameData_GetAbilityMode\",\n      \"va\": \"0x00d2e490\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-11-H2-ROOT-ACCESSORS\",\n      \"score\": 8,\n      \"symbol\": \"root_accessor_00b3d3b0\",\n      \"va\": \"0x00b3d3b0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-11-H2-ROOT-ACCESSORS\",\n      \"score\": 8,\n      \"symbol\": \"root_accessor_00b3d3e0\",\n      \"va\": \"0x00b3d3e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-11-H2-ROOT-ACCESSORS\",\n      \"score\": 8,\n      \"symbol\": \"root_accessor_00b3d3f0\",\n      \"va\": \"0x00b3d3f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-11-H2-ROOT-ACCESSORS\",\n      \"score\": 8,\n      \"symbol\": \"root_accessor_00b3d430\",\n      \"va\": \"0x00b3d430\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Reviewed static mechanics and ABI are canonical; runtime values, ownership, concrete types, and opaque port behavior remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [\n    \"Runtime object validity, global ownership, and unresolved event/action behavior remain gated.\"\n  ],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"None\",\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"pkg13_creature_accessor_00b1fdb0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b1fdb0\"\n      },\n      {\n        \"name\": \"FUN_00b3d300\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b3d300\"\n      },\n      {\n        \"name\": \"FUN_00b5b800\",\n        \"reconstructed\": false,\n        \"va\": \"0x00b5b800\"\n      },\n      {\n        \"name\": \"FUN_00d38840\",\n        \"reconstructed\": false,\n        \"va\": \"0x00d38840\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c07480\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c2ed20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d35190\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d46c30\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d71060\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d71780\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d85ad0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d87620\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d9bc70\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00c07a8c\",\n        \"direction\": \"in\",\n        \"other\": \"0x00c07480\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c2ee69\",\n        \"direction\": \"in\",\n        \"other\": \"0x00c2ed20\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c2ef72\",\n        \"direction\": \"in\",\n        \"other\": \"0x00c2ed20\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00d35533\",\n        \"direction\": \"in\",\n        \"other\": \"0x00d35190\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00d363f6\",\n        \"direction\": \"in\",\n        \"other\": \"0x00d35190\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00d46d1e\",\n        \"direction\": \"in\",\n        \"other\": \"0x00d46c30\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00d7143d\",\n        \"direction\": \"in\",\n        \"other\": \"0x00d71060\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00d71cc5\",\n        \"direction\": \"in\",\n        \"other\": \"0x00d71780\",\n        \"reference_type\": \"direct-call\"\n      },
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
  "body_end": "00d2e970",
  "body_span_bytes": 209,
  "body_start": "00d2e8a0",
  "callees": [
    "FUN_00b5b800",
    "FUN_00f67d90",
    "FUN_00b1fdb0",
    "App::cCreatureModeStrategy::ExecuteAction",
    "FUN_00d2e2e0",
    "FUN_00d38840",
    "FUN_00b3d300"
  ],
  "callers": [
    "FUN_00d46c30",
    "FUN_00c2ed20",
    "FUN_00d85ad0",
    "FUN_00d71060",
    "FUN_00d9bc70",
    "FUN_00d35190",
    "FUN_00d87620",
    "FUN_00d71780",
    "FUN_00c07480"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00d2e8a0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_10",
      "storage": "Stack[-0x10]:4",
      "type": "undefined4"
    },
    {
      "name": "local_14",
      "storage": "Stack[-0x14]:4",
      "type": "undefined4"
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
      "name": "local_24",
      "storage": "Stack[-0x24]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 5,
  "mode": "live",
  "name": "Simulator::cCreatureGameData::AddEvolutionPoints",
  "namespace": "Simulator",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 1,
  "parameters": [
    {
      "name": "points",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "float"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "void",
  "return_type_resolved": true,
  "rva": "0x92e8a0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "void Simulator::cCreatureGameData::AddEvolutionPoints(float points)",
  "size_bytes": 209,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00d2e8a0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 12,
  "xrefs": [
    {
      "from": "00c07a8c"
    },
    {
      "from": "00c2ee69"
    },
    {
      "from": "00c2ef72"
    },
    {
      "from": "00d85be6"
    },
    {
      "from": "00d9bdb6"
    },
    {
      "from": "00d35533"
    },
    {
      "from": "00d363f6"
    },
    {
      "from": "00d7143d"
    },
    {
      "from": "00d883ff"
    },
    {
      "from": "00d71cc5"
    },
    {
      "from": "00c2e98e"
    },
    {
      "from": "00d46d1e"
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
  "global:0x0169e398",
  "global:DAT_01582e54",
  "global:DAT_0169e398",
  "global:float"
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg13_c3_creature_progression_wave2/creature_progression_wave2.cpp",
  "files": [
    "reconstruction/staging/pkg13-c3-creature-progression-wave2/creature_progression_wave2.cpp",
    "reconstruction/staging/pkg13-c3-creature-progression-wave2/creature_progression_wave2.hpp",
    "reconstruction/staging/pkg13-c3-creature-progression-wave2/creature_progression_wave2_model_test.cpp",
    "src/reconstruction/pkg13_c3_creature_progression_wave2/creature_progression_wave2.cpp",
    "src/reconstruction/pkg13_c3_creature_progression_wave2/creature_progression_wave2.hpp",
    "src/reconstruction/pkg13_c3_creature_progression_wave2/creature_progression_wave2_model_test.cpp",
    "src/reconstruction/pkg13_c3_creature_progression_wave2/metadata_package_validation.py"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-sim-social-world-wave2/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg13-c3-creature-progression-wave2/00d2e8a0.json"
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
    "No original-process event trace or runtime validation has been run.",
    "Observe 0x0169e398, 0x01582e54, 0x01654c10, the returned player, the strategy +0x68 receiver, and the +0x54 avatar word in an original process.",
    "Resolve concrete manager, player, avatar, strategy, event, and action ownership before assigning semantic names beyond the raw offsets.",
    "gate-add-evolution-points-00d2e8a0",
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
  "DAT_01582e54",
  "DAT_01654c10",
  "DAT_0169e398",
  "None",
  "UNCONDITIONAL_CALL",
  "float",
  "float points",
  "opaque avatar pointer",
  "zero sentinel at 0x01485378",
  "zero word"
]
```

## vtables

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## Conflicts

```json
{
  "original_bytes": 9562,
  "preview": "[\n  {\n    \"anchors\": [\n      \"0x00d2e380\",\n      \"0x00d2e480\",\n      \"0x00d2e8a0\",\n      \"0x00d39360\",\n      \"0x045ab96e\",\n      \"0x00d2e480\",\n      \"0x00aebe90\",\n      \"0x045ab96e\",\n      \"0x0067dcd0\",\n      \"0x0067dcd0\",\n      \"0x007d8420\",\n      \"0x007d8420\",\n      \"0x007d8cf0\",\n      \"0x007d8cf0\",\n      \"0x007d8d40\",\n      \"0x007d8d40\"\n    ],\n    \"conflict_id\": \"U-005-evolution-level-promotion\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"0x45ab96e is a concrete action/message value with a guarded dispatch, but its consumer and brain-level/ability promotion are not identified.\",\n    \"resolution_status\": \"0x45ab96e is a concrete action/message value with a guarded dispatch, but its consumer and brain-level/ability promotion are not identified.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x01037d30\",\n      \"0x01037d30\",\n      \"0x01037d30\",\n      \"0x01037d30\",\n      \"0x0103a480\",\n      \"0x0103a480\",\n      \"0x0103e8e0\",\n      \"0x0103e8e0\",\n      \"0x0103fc10\",\n      \"0x0103fc10\",\n      \"0x00c877f0\",\n      \"0x00c877f0\",\n      \"0x00596da0\",\n      \"0x01037d30\",\n      \"0x00d2e8a0\",\n      \"0x0103e8e0\"\n    ],\n    \"conflict_id\": \"U-E004\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.\",\n    \"resolution_status\": \"The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00596da0\",\n      \"0x01037d30\",\n      \"0x00d2e8a0\"\n    ],\n    \"conflict_id\": \"U-E012\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.\",\n    \"resolution_status\": \"The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00fe52c0\",\n      \"0x00fe52c0\",\n      \"0x00d2e350\",\n      \"0x00d2e350\",\n      \"0x00d2e380\",\n      \"0x00d2e380\",\n      \"0x00d2e480\",\n      \"0x00d2e480\",\n      \"0x00d2e8a0\",\n      \"0x00d2e8a0\",\n      \"0x00d3fcf0\",\n      \"0x00d3fcf0\",\n      \"0x00fe52c0\",\n      \"0x00fe52c0\",\n      \"0x00fe52c0\",\n      \"0x00fe52c0\"\n    ],\n    \"conflict_id\": \"badge_state_domain\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.\",\n    \"resolution_status\": \"The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00d2e380\",\n      \"0x00d2e8a0\",\n      \"0x045ab96e\",\n      \"0x00d2e8a0\",\n      \"0x045ab96e\",\n      \"0x00594b10\",\n      \"0x00594b10\",\n      \"0x00596da0\",\n      \"0x00596da0\",\n      \"0x00597390\",\n      \"0x00597390\",\n      \"0x00597400\",\n      \"0x00597400\",\n      \"0x00598db0\",\n      \"0x00598db0\",\n      \"0x00598e90\"\n    ],\n    \"conflict_id\": \"brain_level_transition_writer\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.\",\n    \"resolution_status\": \"The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reach
[TRUNCATED]
```
