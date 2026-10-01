# Evidence 0x00576c50

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `2d78ec642798159502ce7b7d22f8846f206e7640f36ec8e073b6db9ebb62f7c8`

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
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
    "saved_registers": [
      "EBP",
      "EBX",
      "EDI",
      "ESI"
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +152, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "728fedf7374522eec9c99164129891a40d06b0f11cf83c3731deb8d50059ca9c",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall",
      "__fastcall"
    ],
    "confidence": "INFERRED",
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
    "indirect_calls": 32,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0097"
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
        "obs-0001",
        "obs-0004",
        "obs-0013",
        "obs-0082",
        "obs-0085",
        "obs-0088",
        "obs-0090",
        "obs-0096"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "SUPPORTED",
      "id": "R1",
      "value": {
        "offsets": [
          0,
          32,
          132,
          136,
          140,
          144,
          148,
          152,
          156,
          160,
          168,
          172,
          348,
          688,
          972,
          976,
          980,
          984,
          988,
          1472,
          1476,
          1480,
          1484,
          1488
        ],
        "register": "ECX",
        "written_through": 18
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0004",
        "obs-0013",
        "obs-0082",
        "obs-0085",
        "obs-0088",
        "obs-0090",
        "obs-0096",
        "obs-0097"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0097"
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
        "obs-0097"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0097"
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
      "at": "0x00576c50",
      "count": 35,
      "first_use": 0,
      "first_write_index": 13,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "reg": "ECX"
    },
    {
      "at": "0x00576c51",
      "count": 29,
      "first_use": 1,
      "first_write_index": 4,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "reg": "EBX"
    },
    {
      "at": "0x00576c52",
      "count": 53,
      "first_use": 2,
      "first_write_index": 3,
      "id": "obs-0003",
      "index": 2,
      "kind": "REG_READ",
      "reg": "ESI"
    },
    {
      "at": "0x00576c53",
      "definite": true,
      "id": "obs-0004",
      "index": 3,
      "kind": "REG_WRITE",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00576c55",
      "definite": true,
      "id": "obs-0005",
      "index": 4,
      "kind": "REG_WRITE",
      "reg": "EBX",
      "write_kind": "zero"
    },
    {
      "at": "0x00576c5f",
      "definite": true,
      "id": "obs-0006",
      "index": 7,
      "kind": "REG_WRITE",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00576c61",
      "count": 72,
      "first_use": 8,
      "first_write_index": 7,
      "id": "obs-0007",
      "index": 8,
      "kind": "REG_READ",
      "reg": "EAX"
    },
    {
      "at": "0x00576c61",
      "definite": true,
      "id": "obs-0008",
      "index": 8,
      "kind": "REG_WRITE",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00576c64",
      "count": 35,
      "first_use": 9,
      "first_write_index": 8,
      "id": "obs-0009",
      "index": 9,
      "kind": "REG_READ",
      "reg": "EDX"
    },
    {
      "at": "0x00576c64",
      "base": "EDX",
      "disp": null,
      "id": "obs-0010",
      "index": 9,
      "kind": "CALL_INDIRECT",
      "via": "register"
    },
    {
      "at": "0x00576c66",
      "count": 31,
      "first_use": 10,
      "first_write_index": 31,
      "id": "obs-0011",
      "index": 10,
      "kind": "REG_READ",
      "reg": "EDI"
    },
    {
      "at": "0x00576c67",
      "id": "obs-0012",
      "index": 11,
      "kind": "CALL_DIRECT",
      "target": "0x0067de20"
    },
    {
      
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
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
    "saved_registers": [
      "EBP",
      "EBX",
      "EDI",
      "ESI"
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +152, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "728fedf7374522eec9c99164129891a40d06b0f11cf83c3731deb8d50059ca9c",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall",
      "__fastcall"
    ],
    "confidence": "INFERRED",
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
    "indirect_calls": 32,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0097"
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
        "obs-0001",
        "obs-0004",
        "obs-0013",
        "obs-0082",
        "obs-0085",
        "obs-0088",
        "obs-0090",
        "obs-0096"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "SUPPORTED",
      "id": "R1",
      "value": {
        "offsets": [
          0,
          32,
          132,
          136,
          140,
          144,
          148,
          152,
          156,
          160,
          168,
          172,
          348,
          688,
          972,
          976,
          980,
          984,
          988,
          1472,
          1476,
          1480,
          1484,
          1488
        ],
        "register": "ECX",
        "written_through": 18
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0004",
        "obs-0013",
        "obs-0082",
        "obs-0085",
        "obs-0088",
        "obs-0090",
        "obs-0096",
        "obs-0097"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0097"
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
        "obs-0097"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0097"
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
      "at": "0x00576c50",
      "count": 35,
      "first_use": 0,
      "first_write_index": 13,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "reg": "ECX"
    },
    {
      "at": "0x00576c51",
      "count": 29,
      "first_use": 1,
      "first_write_index": 4,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "reg": "EBX"
    },
    {
      "at": "0x00576c52",
      "count": 53,
      "first_use": 2,
      "first_write_index": 3,
      "id": "obs-0003",
      "index": 2,
      "kind": "REG_READ",
      "reg": "ESI"
    },
    {
      "at": "0x00576c53",
      "definite": true,
      "id": "obs-0004",
      "index": 3,
      "kind": "REG_WRITE",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00576c55",
      "definite": true,
      "id": "obs-0005",
      "index": 4,
      "kind": "REG_WRITE",
      "reg": "EBX",
      "write_kind": "zero"
    },
    {
      "at": "0x00576c5f",
      "definite": true,
      "id": "obs-0006",
      "index": 7,
      "kind": "REG_WRITE",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00576c61",
      "count": 72,
      "first_use": 8,
      "first_write_index": 7,
      "id": "obs-0007",
      "index": 8,
      "kind": "REG_READ",
      "reg": "EAX"
    },
    {
      "at": "0x00576c61",
      "definite": true,
      "id": "obs-0008",
      "index": 8,
      "kind": "REG_WRITE",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00576c64",
      "count": 35,
      "first_use": 9,
      "first_write_index": 8,
      "id": "obs-0009",
      "index": 9,
      "kind": "REG_READ",
      "reg": "EDX"
    },
    {
      "at": "0x00576c64",
      "base": "EDX",
      "disp": null,
      "id": "obs-0010",
      "index": 9,
      "kind": "CALL_INDIRECT",
      "via": "register"
    },
    {
      "at": "0x00576c66",
      "count": 31,
      "first_use": 10,
      "first_write_index": 31,
      "id": "obs-0011",
      "index": 10,
      "kind": "REG_READ",
      "reg": "EDI"
    },
    {
      "at": "0x00576c67",
      "id": "obs-0012",
      "index": 11,
      "kind": "CALL_DIRECT",
      "target": "0x0067de20"
    },
    {
      
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": null,
    "reconstructed": false,
    "va": "0x004ad330"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0067dcc0"
  },
  {
    "name": "FUN_007c3ba0",
    "reconstructed": false,
    "va": "0x007c3ba0"
  },
  {
    "name": "FUN_007c4000",
    "reconstructed": false,
    "va": "0x007c4000"
  }
]
```

## callers_dependencies

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## contradictions

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "original_bytes": 10839,
  "preview": "[\n  {\n    \"anchors\": [\n      \"0x00584300\",\n      \"0x00584300\",\n      \"0x005737d0\",\n      \"0x005737d0\",\n      \"0x00576c50\",\n      \"0x00576c50\",\n      \"0x00584300\",\n      \"0x00584300\",\n      \"0x00585d10\",\n      \"0x00585d10\",\n      \"0x00586410\",\n      \"0x00586410\",\n      \"0x00586b00\",\n      \"0x00586b00\",\n      \"0x00587270\",\n      \"0x00587270\"\n    ],\n    \"conflict_id\": \"U-001-mission-transitions\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"Mission enum/field surface is known, but no complete direct writer and callback body establishes each transition. SDK contract is not promoted to native order.\",\n    \"resolution_status\": \"Mission enum/field surface is known, but no complete direct writer and callback body establishes each transition. SDK contract is not promoted to native order.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00582fe0\",\n      \"0x00587270\",\n      \"0x0059c830\",\n      \"0x0059c830\",\n      \"0x00576c50\",\n      \"0x00576c50\",\n      \"0x00582fe0\",\n      \"0x00582fe0\",\n      \"0x00582fe0\",\n      \"0x00584300\",\n      \"0x00584300\",\n      \"0x00586410\",\n      \"0x00586410\",\n      \"0x00586b00\",\n      \"0x00586b00\",\n      \"0x00587270\"\n    ],\n    \"conflict_id\": \"U-006-editor-world-slot-conflict\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The +0x360/+0x364 alternatives are preserved; no pointer-pair versus pointer-plus-ID choice is made without a typed body.\",\n    \"resolution_status\": \"The +0x360/+0x364 alternatives are preserved; no pointer-pair versus pointer-plus-ID choice is made without a typed body.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00aeb160\",\n      \"0x00aeb7b0\",\n      \"0x00aebe90\",\n      \"0x00aeb160\",\n      \"0x00aebe90\",\n      \"0x00aeb7b0\",\n      \"0x00aeb7b0\",\n      \"0x005737d0\",\n      \"0x005737d0\",\n      \"0x00576c50\",\n      \"0x00576c50\",\n      \"0x00582fe0\",\n      \"0x00582fe0\",\n      \"0x00584300\",\n      \"0x00584300\",\n      \"0x00585d10\"\n    ],\n    \"conflict_id\": \"U-007-communication-completion\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"Creation appends to cCommManager+0x20 and ShowCommEvent stores +0x1c before processing. Removal/clear and completion ordering are unresolved.\",\n    \"resolution_status\": \"Creation appends to cCommManager+0x20 and ShowCommEvent stores +0x1c before processing. Removal/clear and completion ordering are unresolved.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x005737d0\",\n      \"0x005737d0\",\n      \"0x00576c50\",\n      \"0x00576c50\",\n      \"0x00582fe0\",\n      \"0x00582fe0\",\n      \"0x00584300\",\n      \"0x00584300\",\n      \"0x00585d10\",\n      \"0x00585d10\",\n      \"0x00586410\",\n      \"0x00586410\",\n      \"0x00586b00\",\n      \"0x00586b00\",\n      \"0x00587270\",\n      \"0x00587270\"\n    ],\n    \"conflict_id\": \"U-008-runtime-validation\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.\",\n    \"resolution_status\": \"The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00587270\",\n      \"0x0058b650\",\n      \"0x013f57f8\",\n      \"0x0058b650\",\n      \"0x0057f3e0\",\n      \"0x013f57f8\",\n      \"0x005737d0\",\n      \"0x005737d0\",\n      \"0x00576c50\",\n      \"0x00576c50\",\n      \"0x0057ce80\",\n      \"0x0057ce80\",\n      \"0x00584300\",\n      \"0x00584300\",\n      \"0x00587270\",\n      \"0x00587270\"\n    ],\n    \"conflict_id\": \"ceditor_vtable_tail\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.\",\n    \"resolution_status\": \"The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x005737d0\",\n      \"0x00588570\",\n      \"0x0058ac10\",\n      \"0x00b3d350\",\n      \"0x00e818f0\",\n      \"0x00b3d350\",\n      \"0x00e818f0\",\n      \"0x00b3d350\",\n      \"0x005737d0\",\n      \"0x00576c50\",\n      \"0x00576c50\",\n      \"0x0057ce80\",\n      \"0x0057ce80\",\n      \"0x00584300\",\n      \"0x00584300\",\n      \"0x00587a20\"\n    ],\n    \"conflict_id\": \"editor_input_routing\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The input/UI surface is structurally p
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
  "count": 402,
  "instructions": [
    {
      "address": "00576c50",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00576c51",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00576c52",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00576c53",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00576c55",
      "instruction": "XOR EBX,EBX"
    },
    {
      "address": "00576c57",
      "instruction": "CMP byte ptr [ESI + 0x2b0],BL"
    },
    {
      "address": "00576c5d",
      "instruction": "JZ 0x00576c66"
    },
    {
      "address": "00576c5f",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "00576c61",
      "instruction": "MOV EDX,dword ptr [EAX + 0x1c]"
    },
    {
      "address": "00576c64",
      "instruction": "CALL EDX"
    },
    {
      "address": "00576c66",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00576c67",
      "instruction": "CALL 0x0067de20"
    },
    {
      "address": "00576c6c",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00576c6e",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00576c70",
      "instruction": "MOV EAX,dword ptr [EDX + 0x1c]"
    },
    {
      "address": "00576c73",
      "instruction": "PUSH 0x13f5688"
    },
    {
      "address": "00576c78",
      "instruction": "CALL EAX"
    },
    {
      "address": "00576c7a",
      "instruction": "CALL 0x0067de20"
    },
    {
      "address": "00576c7f",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00576c81",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00576c83",
      "instruction": "MOV EAX,dword ptr [EDX + 0x1c]"
    },
    {
      "address": "00576c86",
      "instruction": "PUSH 0x13f5670"
    },
    {
      "address": "00576c8b",
      "instruction": "CALL EAX"
    },
    {
      "address": "00576c8d",
      "instruction": "CALL 0x0067de20"
    },
    {
      "address": "00576c92",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00576c94",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00576c96",
      "instruction": "MOV EAX,dword ptr [EDX + 0x1c]"
    },
    {
      "address": "00576c99",
      "instruction": "PUSH 0x13f5660"
    },
    {
      "address": "00576c9e",
      "instruction": "CALL EAX"
    },
    {
      "address": "00576ca0",
      "instruction": "MOV dword ptr [ESI + 0x20],EBX"
    },
    {
      "address": "00576ca3",
      "instruction": "CALL 0x0067dcc0"
    },
    {
      "address": "00576ca8",
      "instruction": "MOV EDI,EAX"
    },
    {
      "address": "00576caa",
      "instruction": "CMP EDI,EBX"
    },
    {
      "address": "00576cac",
      "instruction": "JZ 0x00576d24"
    },
    {
      "address": "00576cae",
      "instruction": "MOV EAX,dword ptr [ESI + 0x5c0]"
    },
    {
      "address": "00576cb4",
      "instruction": "CMP EAX,EBX"
    },
    {
      "address": "00576cb6",
      "instruction": "JZ 0x00576ce3"
    },
    {
      "address": "00576cb8",
      "instruction": "MOV ECX,dword ptr [ESI + 0x5d0]"
    },
    {
      "address": "00576cbe",
      "instruction": "MOV EDX,dword ptr [ESI + 0x5cc]"
    },
    {
      "address": "00576cc4",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00576cc5",
      "instruction": "MOV ECX,dword ptr [ESI + 0x5c8]"
    },
    {
      "address": "00576ccb",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00576ccc",
      "instruction": "MOV EDX,dword ptr [ESI + 0x5c4]"
    },
    {
      "address": "00576cd2",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00576cd3",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00576cd4",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00576cd5",
      "instruction": "MOV dword ptr [ESI + 0x5c0],EBX"
    },
    {
      "address": "00576cdb",
      "instruction": "CALL 0x00571db0"
    },
    {
      "address": "00576ce0",
      "instruction": "ADD ESP,0x14"
    },
    {
      "address": "00576ce3",
      "instruction": "MOV EAX,dword ptr [EDI]"
    },
    {
      "address": "00576ce5",
      "instruction": "MOV EDX,dword ptr [EAX + 0x2c]"
    },
    {
      "address": "00576ce8",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00576ce9",
      "instruction": "PUSH 0xffffd8f1"
    },
    {
      "address": "00576cee",
      "instruction": "PUSH 0x29d57f4"
    },
    {
      "address": "00576cf3",
      "instruction": "LEA EBP,[ESI + 0x10]"
    },
    {
      "address": "00576cf6",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00576cf7",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00576cf9",
      "instruction": "CALL EDX"
    },
    {
      "address": "00576cfb",
      "instruction": "MOV EAX,dword ptr [EDI]"
    },
    {
      "address": "00576cfd",
      "instruction": "MOV EDX,dword ptr [EAX + 0x2c]"
    },
    {
      "address": "00576d00",
      "instruction": "PUSH 0xffffd8f1"
    },
    {
      "address": "00576d05",
      "instruction": "PUSH 0x3fc3f13"
    },
    {
      "address": "00576d0a",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00576d0b",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00576d0d",
      "instruction": "CALL EDX"
    },
    {
      "address": "00576d0f",
      "instruction": "MOV EAX,dword ptr [EDI]"
    },
    {
      "address": "00576d11",
      "instruction": "MOV EDX,dword ptr [EAX + 0x2c]"
    },
    {
      "address": "00576d14",
      "instruction": "PUSH 0xffffd8f1"
    },
    {
      "address": "00576d19",
      "instruction": "PUSH 0x62628f0"
    },
    {
      "address": "00576d1e",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00576d1f",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00576d21",
      "instruction": "CALL EDX"
    },
    {
      "address": "00576d23",
   
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
  "original_bytes": 8925,
  "preview": "{\n  \"abi\": {},\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013f57f8\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"editor_input_005737d0\",\n      \"va\": \"0x005737d0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013f57f8\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"editor_input_00585890\",\n      \"va\": \"0x00585890\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013f57f8\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"editor_input_00585d10\",\n      \"va\": \"0x00585d10\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013f57f8\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"editor_input_00588570\",\n      \"va\": \"0x00588570\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013f57f8\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"editor_input_0058ac10\",\n      \"va\": \"0x0058ac10\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013f57f8\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"editor_input_0058b650\",\n      \"va\": \"0x0058b650\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"editor-core\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004ad330\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0067dcc0\"\n      },\n      {\n        \"name\": \"FUN_007c3ba0\",\n        \"reconstructed\": false,\n        \"va\": \"0x007c3ba0\"\n      },\n      {\n        \"name\": \"FUN_007c4000\",\n        \"reconstructed\": false,\n        \"va\": \"0x007c4000\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00576d38\",\n        \"direction\": \"out\",\n        \"other\": \"0x004ad330\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00576d74\",\n        \"direction\": \"out\",\n        \"other\": \"0x004ad330\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00576f37\",\n        \"direction\": \"out\",\n        \"other\": \"0x004b9140\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00576d24\",\n        \"direction\": \"out\",\n        \"other\": \"0x00563de0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00576d29\",\n        \"direction\": \"out\",\n        \"other\": \"0x00563de0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00576cdb\",\n        \"direction\": \"out\",\n        \"other\": \"0x00571db0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00577101\",\n        \"direction\": \"out\",\n        \"other\": \"0x005a98f0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00576ca3\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067dcc0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00576eab\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067dd80\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00576ebe\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067dd80\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00576ed1\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067dd80\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00576efb\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067ddd0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00576c67\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067de20\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00576c7a\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067de20\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00576c8d\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067de20\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0057709b\",\n        \"direction\": \"out\",\n        \"other\": \"0x006b1f90\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00576f70\",\n        \"direction\": \"out\",\n        \"other\": \"0x007c3ba0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00576f9f\",\n        \"direction\": \"out\",\n        \"other\": \"0x007c3ba0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00576fce\",\n        \"direction\": \"out\",\n        \"other\": \"0x007c3ba0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00576ffd\",\n        \"direction\": \"out\",\n        \"other\": \"0x007c3ba0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0057702c\",\n        \"direction\": \"out\",\n        \"other\": \"0x007c3ba0\",\n    
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
  "body_end": "00577122",
  "body_span_bytes": 1235,
  "body_start": "00576c50",
  "callees": [
    "FUN_00f47380",
    "FUN_007c3ba0",
    "FUN_005a98f0",
    "FUN_00571db0",
    "FUN_006b1f90",
    "FUN_00563de0",
    "FUN_004b9140",
    "Graphics::IShadowWorld::Get",
    "App::cIDGenerator::Get",
    "App::IAppSystem::Get",
    "FUN_00a206f0",
    "FUN_004ad330",
    "FUN_007c4000",
    "FUN_0067ddd0"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00576c50",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "Editors::cEditor::Dispose",
  "namespace": "Editors",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 1,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "cEditor *"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "bool",
  "return_type_resolved": true,
  "rva": "0x176c50",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "bool Editors::cEditor::Dispose(cEditor * this)",
  "size_bytes": 1235,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00576c50",
  "vtables": {
    "referenced_by_vtables": [
      "0x013f57f8"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "013f580c"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditor__Dispose.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditor__Dispose.c"
  ],
  "handoffs": [],
  "metadata": []
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
  "gates": [],
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
  "runtime_gated": false,
  "runtime_validated": 0,
  "status": "queued"
}
```

## types

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x013f57f8"
]
```

## Conflicts

```json
{
  "original_bytes": 10839,
  "preview": "[\n  {\n    \"anchors\": [\n      \"0x00584300\",\n      \"0x00584300\",\n      \"0x005737d0\",\n      \"0x005737d0\",\n      \"0x00576c50\",\n      \"0x00576c50\",\n      \"0x00584300\",\n      \"0x00584300\",\n      \"0x00585d10\",\n      \"0x00585d10\",\n      \"0x00586410\",\n      \"0x00586410\",\n      \"0x00586b00\",\n      \"0x00586b00\",\n      \"0x00587270\",\n      \"0x00587270\"\n    ],\n    \"conflict_id\": \"U-001-mission-transitions\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"Mission enum/field surface is known, but no complete direct writer and callback body establishes each transition. SDK contract is not promoted to native order.\",\n    \"resolution_status\": \"Mission enum/field surface is known, but no complete direct writer and callback body establishes each transition. SDK contract is not promoted to native order.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00582fe0\",\n      \"0x00587270\",\n      \"0x0059c830\",\n      \"0x0059c830\",\n      \"0x00576c50\",\n      \"0x00576c50\",\n      \"0x00582fe0\",\n      \"0x00582fe0\",\n      \"0x00582fe0\",\n      \"0x00584300\",\n      \"0x00584300\",\n      \"0x00586410\",\n      \"0x00586410\",\n      \"0x00586b00\",\n      \"0x00586b00\",\n      \"0x00587270\"\n    ],\n    \"conflict_id\": \"U-006-editor-world-slot-conflict\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The +0x360/+0x364 alternatives are preserved; no pointer-pair versus pointer-plus-ID choice is made without a typed body.\",\n    \"resolution_status\": \"The +0x360/+0x364 alternatives are preserved; no pointer-pair versus pointer-plus-ID choice is made without a typed body.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00aeb160\",\n      \"0x00aeb7b0\",\n      \"0x00aebe90\",\n      \"0x00aeb160\",\n      \"0x00aebe90\",\n      \"0x00aeb7b0\",\n      \"0x00aeb7b0\",\n      \"0x005737d0\",\n      \"0x005737d0\",\n      \"0x00576c50\",\n      \"0x00576c50\",\n      \"0x00582fe0\",\n      \"0x00582fe0\",\n      \"0x00584300\",\n      \"0x00584300\",\n      \"0x00585d10\"\n    ],\n    \"conflict_id\": \"U-007-communication-completion\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"Creation appends to cCommManager+0x20 and ShowCommEvent stores +0x1c before processing. Removal/clear and completion ordering are unresolved.\",\n    \"resolution_status\": \"Creation appends to cCommManager+0x20 and ShowCommEvent stores +0x1c before processing. Removal/clear and completion ordering are unresolved.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x005737d0\",\n      \"0x005737d0\",\n      \"0x00576c50\",\n      \"0x00576c50\",\n      \"0x00582fe0\",\n      \"0x00582fe0\",\n      \"0x00584300\",\n      \"0x00584300\",\n      \"0x00585d10\",\n      \"0x00585d10\",\n      \"0x00586410\",\n      \"0x00586410\",\n      \"0x00586b00\",\n      \"0x00586b00\",\n      \"0x00587270\",\n      \"0x00587270\"\n    ],\n    \"conflict_id\": \"U-008-runtime-validation\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.\",\n    \"resolution_status\": \"The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00587270\",\n      \"0x0058b650\",\n      \"0x013f57f8\",\n      \"0x0058b650\",\n      \"0x0057f3e0\",\n      \"0x013f57f8\",\n      \"0x005737d0\",\n      \"0x005737d0\",\n      \"0x00576c50\",\n      \"0x00576c50\",\n      \"0x0057ce80\",\n      \"0x0057ce80\",\n      \"0x00584300\",\n      \"0x00584300\",\n      \"0x00587270\",\n      \"0x00587270\"\n    ],\n    \"conflict_id\": \"ceditor_vtable_tail\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The address/layout alternatives are preserved; no owner or exact binary identity is selected without a ty
[TRUNCATED]
```
