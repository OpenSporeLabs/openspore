# Evidence 0x00596da0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `dde1cf71171b76e28a50bda34b88c949677e35ef2d3bfe2bfb13efc458e49971`

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
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0xc",
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
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
    "stack_cleanup_bytes": 12,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0xc"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +12, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 12,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0xc",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "7670dc5fc8ccbde13481608159f82b86186ae7a91ee263b1b9391e945d5fa6aa",
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
    "ghidra_parameter_count": 0,
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
        "obs-0018",
        "obs-0020"
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
        "obs-0002",
        "obs-0007",
        "obs-0011"
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
        "obs-0005",
        "obs-0006",
        "obs-0007",
        "obs-0008",
        "obs-0011"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          28016
        ],
        "register": "ECX",
        "written_through": 1
      }
    },
    {
      "based_on": [
        "obs-0005",
        "obs-0006",
        "obs-0007",
        "obs-0008",
        "obs-0011",
        "obs-0018",
        "obs-0020"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0018",
        "obs-0020"
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
        "obs-0018",
        "obs-0020"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0018",
        "obs-0020"
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
      "at": "0x00596da0",
      "count": 5,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x8]",
      "reg": "ESP"
    },
    {
      "at": "0x00596da0",
      "base": "ESP",
      "disp": 8,
      "id": "obs-0002",
      "index": 0,
      "key": 8,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x8]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00596da0",
      "definite": true,
      "id": "obs-0003",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESP + 0x8]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00596da4",
      "count": 6,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00596da5",
      "count": 5,
      "first_use": 2,
      "first_write_index": 3,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00596da5",
      "definite": true,
      "id": "obs-0006",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind":
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
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0xc",
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
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
    "stack_cleanup_bytes": 12,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0xc"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +12, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 12,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0xc",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "7670dc5fc8ccbde13481608159f82b86186ae7a91ee263b1b9391e945d5fa6aa",
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
    "ghidra_parameter_count": 0,
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
        "obs-0018",
        "obs-0020"
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
        "obs-0002",
        "obs-0007",
        "obs-0011"
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
        "obs-0005",
        "obs-0006",
        "obs-0007",
        "obs-0008",
        "obs-0011"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          28016
        ],
        "register": "ECX",
        "written_through": 1
      }
    },
    {
      "based_on": [
        "obs-0005",
        "obs-0006",
        "obs-0007",
        "obs-0008",
        "obs-0011",
        "obs-0018",
        "obs-0020"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0018",
        "obs-0020"
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
        "obs-0018",
        "obs-0020"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0018",
        "obs-0020"
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
      "at": "0x00596da0",
      "count": 5,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x8]",
      "reg": "ESP"
    },
    {
      "at": "0x00596da0",
      "base": "ESP",
      "disp": 8,
      "id": "obs-0002",
      "index": 0,
      "key": 8,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x8]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00596da0",
      "definite": true,
      "id": "obs-0003",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESP + 0x8]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00596da4",
      "count": 6,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00596da5",
      "count": 5,
      "first_use": 2,
      "first_write_index": 3,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00596da5",
      "definite": true,
      "id": "obs-0006",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind":
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
    "va": "0x005973a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005bf1e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005ef470"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bb8b20"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c7a1f0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00de4f50"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e4fac0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e83430"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e83910"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00f12fc0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x01058460"
  }
]
```

## contradictions

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "original_bytes": 11277,
  "preview": "[\n  {\n    \"anchors\": [\n      \"0x00d01e30\",\n      \"0x00d01e30\",\n      \"0x00d038e0\",\n      \"0x00d038e0\",\n      \"0x00d05830\",\n      \"0x00d05830\",\n      \"0x00d06270\",\n      \"0x00d06270\",\n      \"0x00d065a0\",\n      \"0x00d065a0\",\n      \"0x00d06920\",\n      \"0x00d06920\",\n      \"0x00596da0\"\n    ],\n    \"conflict_id\": \"U-E001\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.\",\n    \"resolution_status\": \"The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x01037d30\",\n      \"0x01037d30\",\n      \"0x01037d30\",\n      \"0x01037d30\",\n      \"0x0103a480\",\n      \"0x0103a480\",\n      \"0x0103e8e0\",\n      \"0x0103e8e0\",\n      \"0x0103fc10\",\n      \"0x0103fc10\",\n      \"0x00c877f0\",\n      \"0x00c877f0\",\n      \"0x00596da0\",\n      \"0x01037d30\",\n      \"0x00d2e8a0\",\n      \"0x0103e8e0\"\n    ],\n    \"conflict_id\": \"U-E004\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.\",\n    \"resolution_status\": \"The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x010535e0\",\n      \"0x010535e0\",\n      \"0x005942e0\",\n      \"0x005942e0\",\n      \"0x00596da0\",\n      \"0x00596da0\",\n      \"0x00596e10\",\n      \"0x00596e10\",\n      \"0x005973a0\",\n      \"0x005973a0\",\n      \"0x00598db0\",\n      \"0x00598db0\",\n      \"0x00598e90\",\n      \"0x00598e90\",\n      \"0x00be2590\",\n      \"0x00be2590\"\n    ],\n    \"conflict_id\": \"U-E007\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The resource seam and cited call boundary are retained, but original ownership, priority, cache, failure, and load-order semantics are unresolved.\",\n    \"resolution_status\": \"The resource seam and cited call boundary are retained, but original ownership, priority, cache, failure, and load-order semantics are unresolved.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x010535e0\",\n      \"0x010535e0\",\n      \"0x005942e0\",\n      \"0x005942e0\",\n      \"0x00596da0\",\n      \"0x00596da0\",\n      \"0x00596e10\",\n      \"0x00596e10\",\n      \"0x005973a0\",\n      \"0x005973a0\",\n      \"0x00598db0\",\n      \"0x00598db0\",\n      \"0x00598e90\",\n      \"0x00598e90\",\n      \"0x00be2590\",\n      \"0x00be2590\"\n    ],\n    \"conflict_id\": \"U-E008\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.\",\n    \"resolution_status\": \"The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00c3a5a0\",\n      \"0x00c3b630\",\n      \"0x00c15e50\",\n      \"0x00c15e50\",\n      \"0x00c38b10\",\n      \"0x00c38b10\",\n      \"0x00596da0\",\n      \"0x00c15e50\",\n      \"0x00c15f20\",\n      \"0x00c38b10\",\n      \"0x00c38b50\"\n    ],\n    \"conflict_id\": \"U-E011\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.\",\n    \"resolution_status\": \"The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00596da0\",\n      \"0x01037d30\",\n      \"0x00d2e8a0\"\n    ],\n    \"conflict_id\": \"U-E012\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.\",\n    \"resolution_status\": \"The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00596da0\",\n      \"0x00596da0\",\n      \"
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
  "count": 33,
  "instructions": [
    {
      "address": "00596da0",
      "instruction": "MOV EAX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "00596da4",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00596da5",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00596da7",
      "instruction": "MOV ECX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "00596dab",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00596dac",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00596dad",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00596daf",
      "instruction": "CALL 0x00595110"
    },
    {
      "address": "00596db4",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00596db6",
      "instruction": "JNZ 0x00596dfb"
    },
    {
      "address": "00596db8",
      "instruction": "MOV ECX,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00596dbc",
      "instruction": "MOV EAX,dword ptr [ESI + 0x6d70]"
    },
    {
      "address": "00596dc2",
      "instruction": "SUB EAX,ECX"
    },
    {
      "address": "00596dc4",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00596dc6",
      "instruction": "JZ 0x00596dcc"
    },
    {
      "address": "00596dc8",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00596dca",
      "instruction": "JL 0x00596dfb"
    },
    {
      "address": "00596dcc",
      "instruction": "LEA EDX,[ESP + 0x8]"
    },
    {
      "address": "00596dd0",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00596dd1",
      "instruction": "LEA ECX,[ESI + 0x4d00]"
    },
    {
      "address": "00596dd7",
      "instruction": "MOV dword ptr [ESI + 0x6d70],EAX"
    },
    {
      "address": "00596ddd",
      "instruction": "CALL 0x00595eb0"
    },
    {
      "address": "00596de2",
      "instruction": "OR byte ptr [EAX],0x3"
    },
    {
      "address": "00596de5",
      "instruction": "LEA EAX,[ESP + 0x8]"
    },
    {
      "address": "00596de9",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00596dea",
      "instruction": "LEA ECX,[ESI + 0x6d80]"
    },
    {
      "address": "00596df0",
      "instruction": "CALL 0x00594b10"
    },
    {
      "address": "00596df5",
      "instruction": "MOV AL,0x1"
    },
    {
      "address": "00596df7",
      "instruction": "POP ESI"
    },
    {
      "address": "00596df8",
      "instruction": "RET 0xc"
    },
    {
      "address": "00596dfb",
      "instruction": "XOR AL,AL"
    },
    {
      "address": "00596dfd",
      "instruction": "POP ESI"
    },
    {
      "address": "00596dfe",
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
  "original_bytes": 7598,
  "preview": "{\n  \"abi\": {},\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-11-A4-PROGRESSION-WAVE3\",\n      \"score\": 8,\n      \"symbol\": \"collectable_lock_00596e10\",\n      \"va\": \"0x00596e10\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [\n    \"Container node allocation, hash layout, and the concrete mUnlockableItems/status map implementations remain opaque ports.\",\n    \"No original-process collectable unlock trace was run.\",\n    \"The SDK documents additional level, random-find, and effect eligibility outside the called 0x00595110 helper; those rules are not claimed here.\"\n  ],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005973a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005bf1e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005ef470\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bb8b20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c7a1f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00de4f50\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e4fac0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e83430\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e83910\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00f12fc0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x01058460\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x005973f0\",\n        \"direction\": \"in\",\n        \"other\": \"0x005973a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005bf2be\",\n        \"direction\": \"in\",\n        \"other\": \"0x005bf1e0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005bf2fa\",\n        \"direction\": \"in\",\n        \"other\": \"0x005bf1e0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005ef574\",\n        \"direction\": \"in\",\n        \"other\": \"0x005ef470\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00bb96b0\",\n        \"direction\": \"in\",\n        \"other\": \"0x00bb8b20\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00bb96d5\",\n        \"direction\": \"in\",\n        \"other\": \"0x00bb8b20\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00bb96fa\",\n        \"direction\": \"in\",\n        \"other\": \"0x00bb8b20\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00bb971e\",\n        \"direction\": \"in\",\n        \"other\": \"0x00bb8b20\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00bb9743\",\n        \"direction\": \"in\",\n        \"other\": \"0x00bb8b20\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c7a4dd\",\n        \"direction\": \"in\",\n        \"other\": \"0x00c7a1f0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c7a51d\",\n        \"direction\": \"in\",\n        \"other\": \"0x00c7a1f0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00de4f9c\",\n        \"direction\": \"in\",\n        \"other\": \"0x00de4f50\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e4fb29\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e4fac0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e4fb92\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e4fac0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e8345f\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e83430\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e83a4e\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e83910\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00f1307c\",\n        \"direction\": \"in\",\n        \"other\": \"0x00f12fc0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x010585b4\",\n        \"direction\": \"in\",\n        \"other\": \"0x01058460\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x01058617\",\n        \"direction\": \"in\",\n        \"other\": \"0x01058460\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00596df0\",\n        \"direction\": \"out\",\n        \"other\": \"0x00594b10\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00596daf\",\n        \"direction\": \"out\",\n        \"other\": \"0x00595110\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00596ddd\",\n        \"direction\": \"out\",\n       
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
  "body_end": "00596e00",
  "body_span_bytes": 97,
  "body_start": "00596da0",
  "callees": [
    "FUN_00595110",
    "FUN_00595eb0",
    "FUN_00594b10"
  ],
  "callers": [
    "FUN_00bb8b20",
    "FUN_005bf1e0",
    "FUN_01058460",
    "FUN_00de4f50",
    "FUN_00f12fc0",
    "FUN_005973a0",
    "FUN_00e4fac0",
    "FUN_00e83910",
    "FUN_00c7a1f0",
    "FUN_005ef470",
    "FUN_00e83430"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00596da0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00596da0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x196da0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00596da0(void)",
  "size_bytes": 97,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00596da0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 19,
  "xrefs": [
    {
      "from": "00bb96b0"
    },
    {
      "from": "00bb96d5"
    },
    {
      "from": "00bb96fa"
    },
    {
      "from": "00bb971e"
    },
    {
      "from": "00bb9743"
    },
    {
      "from": "005973f0"
    },
    {
      "from": "005bf2be"
    },
    {
      "from": "005bf2fa"
    },
    {
      "from": "005ef574"
    },
    {
      "from": "010585b4"
    },
    {
      "from": "01058617"
    },
    {
      "from": "00de4f9c"
    },
    {
      "from": "00c7a4dd"
    },
    {
      "from": "00c7a51d"
    },
    {
      "from": "00e83a4e"
    },
    {
      "from": "00e4fb29"
    },
    {
      "from": "00e4fb92"
    },
    {
      "from": "00e8345f"
    },
    {
      "from": "00f1307c"
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
    "reconstruction/staging/pkg11-a4-progression-wave3/progression_wave3.cpp",
    "reconstruction/staging/pkg11-a4-progression-wave3/progression_wave3.hpp",
    "src/reconstruction/pkg11_a4_progression_wave3/progression_wave3.cpp",
    "src/reconstruction/pkg11_a4_progression_wave3/progression_wave3.hpp",
    "src/reconstruction/pkg11_a4_progression_wave3/progression_wave3_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-sim-social-world-wave3/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg11-a4-progression-wave3/00596da0.json"
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
  "std::int32_t",
  "std::uint32_t"
]
```

## vtables

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## Conflicts

```json
{
  "original_bytes": 11277,
  "preview": "[\n  {\n    \"anchors\": [\n      \"0x00d01e30\",\n      \"0x00d01e30\",\n      \"0x00d038e0\",\n      \"0x00d038e0\",\n      \"0x00d05830\",\n      \"0x00d05830\",\n      \"0x00d06270\",\n      \"0x00d06270\",\n      \"0x00d065a0\",\n      \"0x00d065a0\",\n      \"0x00d06920\",\n      \"0x00d06920\",\n      \"0x00596da0\"\n    ],\n    \"conflict_id\": \"U-E001\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.\",\n    \"resolution_status\": \"The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x01037d30\",\n      \"0x01037d30\",\n      \"0x01037d30\",\n      \"0x01037d30\",\n      \"0x0103a480\",\n      \"0x0103a480\",\n      \"0x0103e8e0\",\n      \"0x0103e8e0\",\n      \"0x0103fc10\",\n      \"0x0103fc10\",\n      \"0x00c877f0\",\n      \"0x00c877f0\",\n      \"0x00596da0\",\n      \"0x01037d30\",\n      \"0x00d2e8a0\",\n      \"0x0103e8e0\"\n    ],\n    \"conflict_id\": \"U-E004\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.\",\n    \"resolution_status\": \"The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x010535e0\",\n      \"0x010535e0\",\n      \"0x005942e0\",\n      \"0x005942e0\",\n      \"0x00596da0\",\n      \"0x00596da0\",\n      \"0x00596e10\",\n      \"0x00596e10\",\n      \"0x005973a0\",\n      \"0x005973a0\",\n      \"0x00598db0\",\n      \"0x00598db0\",\n      \"0x00598e90\",\n      \"0x00598e90\",\n      \"0x00be2590\",\n      \"0x00be2590\"\n    ],\n    \"conflict_id\": \"U-E007\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The resource seam and cited call boundary are retained, but original ownership, priority, cache, failure, and load-order semantics are unresolved.\",\n    \"resolution_status\": \"The resource seam and cited call boundary are retained, but original ownership, priority, cache, failure, and load-order semantics are unresolved.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x010535e0\",\n      \"0x010535e0\",\n      \"0x005942e0\",\n      \"0x005942e0\",\n      \"0x00596da0\",\n      \"0x00596da0\",\n      \"0x00596e10\",\n      \"0x00596e10\",\n      \"0x005973a0\",\n      \"0x005973a0\",\n      \"0x00598db0\",\n      \"0x00598db0\",\n      \"0x00598e90\",\n      \"0x00598e90\",\n      \"0x00be2590\",\n      \"0x00be2590\"\n    ],\n    \"conflict_id\": \"U-E008\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.\",\n    \"resolution_status\": \"The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00c3a5a0\",\n      \"0x00c3b630\",\n      \"0x00c15e50\",\n      \"0x00c15e50\",\n      \"0x00c38b10\",\n      \"0x00c38b10\",\n      \"0x00596da0\",\n      \"0x00c15e50\",\n      \"0x00c15f20\",\n      \"0x00c38b10\",\n      \"0x00c38b50\"\n    ],\n    \"conflict_id\": \"U-E011\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.\",\n    \"resolution_status\": \"The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",
[TRUNCATED]
```
