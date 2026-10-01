# Evidence 0x00e818f0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `0a8d72d420db71c1333ea0920fe9592211f6387c48cfc65ece20dade55e72636`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "thiscall",
  "hidden_receiver": "ECX OpaqueCellModeStrategy*",
  "ordinary_stack_arguments": [
    {
      "name": "virtualKey",
      "offset": "ESP+4",
      "slot": 0,
      "type": "int32"
    },
    {
      "offset": "ESP+8",
      "slot": 1,
      "type": "KeyModifiers",
      "width_bytes": 4
    }
  ],
  "ret_form": "RET 8",
  "return_register": "AL",
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
    "calling_convention": "__stdcall",
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
    "receiver": false,
    "ret_form": "RET 0x8",
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
    "saved_registers": [
      "EBX",
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
    "stack_cleanup_bytes": 8,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x8"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -16, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 8,
    "confidence": "SUPPORTED",
    "corroboration": "not_available",
    "evidence": "ret 0x8",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [
    {
      "field": "calling_convention",
      "inferred": "__stdcall",
      "kind": "inferred_vs_persisted",
      "persisted": "__thiscall",
      "resolution_status": "unresolved"
    }
  ],
  "content_sha256": "5d8b1811effb3859b54eed5d2b79a8001a17ef0b637dc5d9e0d3a6f33c95ea6b",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__stdcall",
    "candidate_conventions": [
      "__stdcall"
    ],
    "confidence": "INFERRED",
    "corroboration": "not_available"
  },
  "cross_validation": {
    "agreement": false,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 3,
    "persisted": "disagrees",
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
        "obs-0022",
        "obs-0027",
        "obs-0030"
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
        "obs-0003",
        "obs-0006"
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
        "obs-0030"
      ],
      "claim": "ECX is never read in any form, so there is no register receiver",
      "confidence": "OBSERVED",
      "id": "R2",
      "value": {
        "present": false
      }
    },
    {
      "based_on": [
        "obs-0022",
        "obs-0027",
        "obs-0030"
      ],
      "claim": "calling convention is __stdcall: a callee that pops stack arguments with no register receiver",
      "confidence": "INFERRED",
      "id": "C6",
      "value": "__stdcall"
    },
    {
      "based_on": [
        "obs-0022",
        "obs-0027",
        "obs-0030"
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
        "obs-0022",
        "obs-0027",
        "obs-0030"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0022",
        "obs-0027",
        "obs-0030"
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
      "at": "0x00e818f0",
      "count": 6,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00e818f1",
      "count": 5,
      "first_use": 1,
      "first_write_index": 7,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EBX,dword ptr [ESP + 0xc]",
      "reg": "ESP"
    },
    {
      "at": "0x00e818f1",
      "base": "ESP",
      "disp": 12,
      "id": "obs-0003",
      "index": 1,
      "key": 8,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EBX,dword ptr [ESP + 0xc]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00e818f1",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EBX,dword ptr [ESP + 0xc]",
      "reg": "EBX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00e818f5",
      "count": 6,
      "first_use": 2,
      "first_write_index": 3,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00e818f6",
      "base": "ESP",
      "disp": 12,
      "id": "obs-0006",
      "index": 3,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV ESI,dword ptr [ESP + 0xc]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00e818f6",
      "definite": true,
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
    "name": "game_input_on_key_down_00697a50",
    "reconstructed": true,
    "va": "0x00697a50"
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
[
  {
    "anchors": [
      "0x00b3d350",
      "0x00e818f0",
      "0x00b3d350",
      "0x00e818f0",
      "0x00b3d350",
      "0x007d8060",
      "0x007d8060",
      "0x007d8360",
      "0x007d8360",
      "0x007d85b0",
      "0x007d85b0",
      "0x007d8c30",
      "0x007d8c30",
      "0x007d8c80",
      "0x007d8c80",
      "0x007d8d40"
    ],
    "conflict_id": "Q-INPUT-ROUTING",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "resolution_status": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00b3d350",
      "0x00e818f0",
      "0x00b3d350",
      "0x00e818f0",
      "0x00b3d350",
      "0x007d8060",
      "0x007d8060",
      "0x007d8230",
      "0x007d8230",
      "0x007d8360",
      "0x007d8360",
      "0x007d8470",
      "0x007d8470",
      "0x007d85b0",
      "0x007d85b0",
      "0x007d8c30"
    ],
    "conflict_id": "U-GAME-INPUT-ROUTER",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "resolution_status": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00e80980",
      "0x00e818f0",
      "0x00e81cf0",
      "0x00e81f30",
      "0x00e552f0",
      "0x00e7fc00",
      "0x00e616c0",
      "0x00e80d8b",
      "0x01485550",
      "0x013f57f8",
      "0x01485550",
      "0x01485558",
      "0x01485550",
      "0x01485550",
      "0x01485558",
      "0x01485550"
    ],
    "conflict_id": "VT-002",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "RESOLVED_OBSERVED",
    "resolution_status": "RESOLVED_OBSERVED",
    "source": "knowledgegraph/research/conflicts/track-a-type-signature.json",
    "subject": "0x01485550/0x01485558 cCellModeStrategy vtable owner and base",
    "unresolved_reason": "The exact source-level name of the secondary subobject and the language-level interface declaration remain unproven, but the disputed table owner/base is resolved."
  },
  {
    "anchors": [
      "0x005737d0",
      "0x00588570",
      "0x0058ac10",
      "0x00b3d350",
      "0x00e818f0",
      "0x00b3d350",
      "0x00e818f0",
      "0x00b3d350",
      "0x005737d0",
      "0x00576c50",
      "0x00576c50",
      "0x0057ce80",
      "0x0057ce80",
      "0x00584300",
      "0x00584300",
      "0x00587a20"
    ],
    "conflict_id": "editor_input_routing",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "resolution_status": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
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
  "count": 68,
  "instructions": [
    {
      "address": "00e818f0",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00e818f1",
      "instruction": "MOV EBX,dword ptr [ESP + 0xc]"
    },
    {
      "address": "00e818f5",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00e818f6",
      "instruction": "MOV ESI,dword ptr [ESP + 0xc]"
    },
    {
      "address": "00e818fa",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00e818fb",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00e818fc",
      "instruction": "CALL 0x00e82900"
    },
    {
      "address": "00e81901",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "00e81904",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00e81906",
      "instruction": "JNZ 0x00e81979"
    },
    {
      "address": "00e81908",
      "instruction": "CMP EBX,0x2"
    },
    {
      "address": "00e8190b",
      "instruction": "JNZ 0x00e81927"
    },
    {
      "address": "00e8190d",
      "instruction": "CMP ESI,0x48"
    },
    {
      "address": "00e81910",
      "instruction": "JNZ 0x00e81927"
    },
    {
      "address": "00e81912",
      "instruction": "MOV EAX,[0x016b3c0c]"
    },
    {
      "address": "00e81917",
      "instruction": "CMP byte ptr [EAX + 0x937],0x0"
    },
    {
      "address": "00e8191e",
      "instruction": "SETZ CL"
    },
    {
      "address": "00e81921",
      "instruction": "MOV byte ptr [EAX + 0x937],CL"
    },
    {
      "address": "00e81927",
      "instruction": "MOV ECX,dword ptr [0x016b3c0c]"
    },
    {
      "address": "00e8192d",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00e8192e",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00e8192f",
      "instruction": "CALL 0x00697a50"
    },
    {
      "address": "00e81934",
      "instruction": "TEST BL,0x2"
    },
    {
      "address": "00e81937",
      "instruction": "JZ 0x00e81943"
    },
    {
      "address": "00e81939",
      "instruction": "MOV byte ptr [ESP + 0x10],0x1"
    },
    {
      "address": "00e8193e",
      "instruction": "TEST BL,0x4"
    },
    {
      "address": "00e81941",
      "instruction": "JNZ 0x00e81948"
    },
    {
      "address": "00e81943",
      "instruction": "MOV byte ptr [ESP + 0x10],0x0"
    },
    {
      "address": "00e81948",
      "instruction": "CALL 0x00e82cc0"
    },
    {
      "address": "00e8194d",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00e8194f",
      "instruction": "JZ 0x00e81956"
    },
    {
      "address": "00e81951",
      "instruction": "CMP ESI,0x42"
    },
    {
      "address": "00e81954",
      "instruction": "JNZ 0x00e8199f"
    },
    {
      "address": "00e81956",
      "instruction": "CMP byte ptr [ESP + 0x10],0x0"
    },
    {
      "address": "00e8195b",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00e8195c",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00e8195d",
      "instruction": "JZ 0x00e81980"
    },
    {
      "address": "00e8195f",
      "instruction": "CALL 0x00e81120"
    },
    {
      "address": "00e81964",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "00e81967",
      "instruction": "CMP AL,0x1"
    },
    {
      "address": "00e81969",
      "instruction": "JZ 0x00e81979"
    },
    {
      "address": "00e8196b",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00e8196c",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00e8196d",
      "instruction": "CALL 0x00e7f630"
    },
    {
      "address": "00e81972",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "00e81975",
      "instruction": "CMP AL,0x1"
    },
    {
      "address": "00e81977",
      "instruction": "JNZ 0x00e8199f"
    },
    {
      "address": "00e81979",
      "instruction": "POP ESI"
    },
    {
      "address": "00e8197a",
      "instruction": "MOV AL,0x1"
    },
    {
      "address": "00e8197c",
      "instruction": "POP EBX"
    },
    {
      "address": "00e8197d",
      "instruction": "RET 0x8"
    },
    {
      "address": "00e81980",
      "instruction": "CALL 0x00e7f630"
    },
    {
      "address": "00e81985",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "00e81988",
      "instruction": "CMP AL,0x1"
    },
    {
      "address": "00e8198a",
      "instruction": "JZ 0x00e81979"
    },
    {
      "address": "00e8198c",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00e8198d",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00e8198e",
      "instruction": "CALL 0x00e81120"
    },
    {
      "address": "00e81993",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "00e81996",
      "instruction": "CMP AL,0x1"
    },
    {
      "address": "00e81998",
      "instruction": "JNZ 0x00e8199f"
    },
    {
      "address": "00e8199a",
      "instruction": "POP ESI"
    },
    {
      "address": "00e8199b",
      "instruction": "POP EBX"
    },
    {
      "address": "00e8199c",
      "instruction": "RET 0x8"
    },
    {
      "address": "00e8199f",
      "instruction": "POP ESI"
    },
    {
      "address": "00e819a0",
      "instruction": "XOR AL,AL"
    },
    {
      "address": "00e819a2",
      "instruction": "POP EBX"
    },
    {
      "address": "00e819a3",
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
  "original_bytes": 8936,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"thiscall\",\n    \"hidden_receiver\": \"ECX OpaqueCellModeStrategy*\",\n    \"ordinary_stack_arguments\": [\n      {\n        \"name\": \"virtualKey\",\n        \"offset\": \"ESP+4\",\n        \"slot\": 0,\n        \"type\": \"int32\"\n      },\n      {\n        \"offset\": \"ESP+8\",\n        \"slot\": 1,\n        \"type\": \"KeyModifiers\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"ret_form\": \"RET 8\",\n    \"return_register\": \"AL\",\n    \"stack_cleanup_bytes\": 8\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:DATA,OpaqueGameInput,bool in AL\",\n        \"shared_vtable:vtable:0x01485550\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE7\",\n      \"score\": 34,\n      \"symbol\": \"cell_mode_strategy_on_mouse_move_00e51010\",\n      \"va\": \"0x00e51010\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:KeyModifiers,OpaqueGameInput,int32\",\n        \"same_calling_convention\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE7\",\n      \"score\": 33,\n      \"symbol\": \"game_input_on_key_down_00697a50\",\n      \"va\": \"0x00697a50\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:KeyModifiers,OpaqueGameInput,int32\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE7\",\n      \"score\": 30,\n      \"symbol\": \"game_input_on_key_up_00697a80\",\n      \"va\": \"0x00697a80\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueGameInput,int32\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE7\",\n      \"score\": 27,\n      \"symbol\": \"game_input_mouse_up_00697af0\",\n      \"va\": \"0x00697af0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueGameInput\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE7\",\n      \"score\": 22,\n      \"symbol\": \"simulator_game_input_manager_get_00b3d350\",\n      \"va\": \"0x00b3d350\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_types:DATA,bool in AL,int32\",\n        \"shared_vtable:vtable:0x01485550\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE8\",\n      \"score\": 21,\n      \"symbol\": \"cell_mode_strategy_on_mouse_down_00e6c860\",\n      \"va\": \"0x00e6c860\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_types:DATA,int32\",\n        \"shared_vtable:vtable:0x01485550\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE8\",\n      \"score\": 18,\n      \"symbol\": \"cell_mode_strategy_on_mouse_up_00e5c0f0\",\n      \"va\": \"0x00e5c0f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_types:DATA,int32\",\n        \"shared_vtable:vtable:0x01485550\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE8\",\n      \"score\": 18,\n      \"symbol\": \"cell_mode_strategy_on_mouse_wheel_00e7d660\",\n      \"va\": \"0x00e7d660\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Static mechanics and x86-32 ABI reviewed from live Ghidra; runtime values, concrete owners, and unresolved ports remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueGameInput\",\n  \"cluster\": \"app-lifecycle\",\n  \"confidence\": 0.7,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"game_input_on_key_down_00697a50\",\n        \"reconstructed\": true,\n        \"va\": \"0x00697a50\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00e8192f\",\n        \"direction\": \"out\",\n        \"other\": \"0x00697a50\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e8196d\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e7f630\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e81980\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e7f630\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e8195f\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e81120\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e8198e\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e81120\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e818fc\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e82900\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e81948\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e82cc0\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 1,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [\n      \"0x00697a50\"\n    ],\n    \"scc\": {\n      \"id\": \"scc-0560\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 
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
  "body_end": "00e819a5",
  "body_span_bytes": 182,
  "body_start": "00e818f0",
  "callees": [
    "GameInput::OnKeyDown",
    "FUN_00e82cc0",
    "FUN_00e7f630",
    "FUN_00e82900",
    "FUN_00e81120"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00e818f0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "App::cCellModeStrategy::OnKeyDown",
  "namespace": "App",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 3,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "cCellModeStrategy *"
    },
    {
      "name": "virtualKey",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "int"
    },
    {
      "name": "modifiers",
      "ordinal": 2,
      "storage": "Stack[0xc]:4",
      "type": "KeyModifiers"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "bool",
  "return_type_resolved": true,
  "rva": "0xa818f0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "bool App::cCellModeStrategy::OnKeyDown(cCellModeStrategy * this, int virtualKey, KeyModifiers modifiers)",
  "size_bytes": 182,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00e818f0",
  "vtables": {
    "referenced_by_vtables": [
      "0x01485550"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "0148557c"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__cCellModeStrategy__OnKeyDown.c",
  "file": "src/reconstruction/pkg_game_input_wave7/game_input_wave7.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__cCellModeStrategy__OnKeyDown.c",
    "src/reconstruction/pkg_game_input_wave7/game_input_wave7.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave7/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-game-input-wave7/00e818f0.json"
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
    "Observe Cell-mode vtable reachability, global receiver validity, route/UI/action return values, and all action side effects in the original process."
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
  "DATA",
  "KeyModifiers",
  "OpaqueGameInput",
  "bool in AL",
  "int32"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x01485550",
  "vtable:0x0148557c"
]
```

## Conflicts

```json
[
  {
    "anchors": [
      "0x00b3d350",
      "0x00e818f0",
      "0x00b3d350",
      "0x00e818f0",
      "0x00b3d350",
      "0x007d8060",
      "0x007d8060",
      "0x007d8360",
      "0x007d8360",
      "0x007d85b0",
      "0x007d85b0",
      "0x007d8c30",
      "0x007d8c30",
      "0x007d8c80",
      "0x007d8c80",
      "0x007d8d40"
    ],
    "conflict_id": "Q-INPUT-ROUTING",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "resolution_status": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00b3d350",
      "0x00e818f0",
      "0x00b3d350",
      "0x00e818f0",
      "0x00b3d350",
      "0x007d8060",
      "0x007d8060",
      "0x007d8230",
      "0x007d8230",
      "0x007d8360",
      "0x007d8360",
      "0x007d8470",
      "0x007d8470",
      "0x007d85b0",
      "0x007d85b0",
      "0x007d8c30"
    ],
    "conflict_id": "U-GAME-INPUT-ROUTER",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "resolution_status": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00e80980",
      "0x00e818f0",
      "0x00e81cf0",
      "0x00e81f30",
      "0x00e552f0",
      "0x00e7fc00",
      "0x00e616c0",
      "0x00e80d8b",
      "0x01485550",
      "0x013f57f8",
      "0x01485550",
      "0x01485558",
      "0x01485550",
      "0x01485550",
      "0x01485558",
      "0x01485550"
    ],
    "conflict_id": "VT-002",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "RESOLVED_OBSERVED",
    "resolution_status": "RESOLVED_OBSERVED",
    "source": "knowledgegraph/research/conflicts/track-a-type-signature.json",
    "subject": "0x01485550/0x01485558 cCellModeStrategy vtable owner and base",
    "unresolved_reason": "The exact source-level name of the secondary subobject and the language-level interface declaration remain unproven, but the disputed table owner/base is resolved."
  },
  {
    "anchors": [
      "0x005737d0",
      "0x00588570",
      "0x0058ac10",
      "0x00b3d350",
      "0x00e818f0",
      "0x00b3d350",
      "0x00e818f0",
      "0x00b3d350",
      "0x005737d0",
      "0x00576c50",
      "0x00576c50",
      "0x0057ce80",
      "0x0057ce80",
      "0x00584300",
      "0x00584300",
      "0x00587a20"
    ],
    "conflict_id": "editor_input_routing",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "resolution_status": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "derived": "__stdcall",
    "field": "calling_convention",
    "kind": "derived_vs_persisted",
    "persisted": "thiscall",
    "resolution_status": "unresolved"
  }
]
```
