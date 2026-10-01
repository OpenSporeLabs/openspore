# Evidence 0x00e6c860

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `4c764ff4b0e545a70979653362ca5d64f9e67024eb570684b88473c699913e5c`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "thiscall",
  "hidden_receiver": "ECX App::cCellModeStrategy*",
  "ordinary_stack_arguments": [
    {
      "evidence": "captured into EBP by MOV EBP,[ESP+0x828] at 0x00e6c879 and compared in full 32-bit width against 0x3e8 and 0x3ea",
      "name": "mouseButton",
      "offset": "ESP+4",
      "slot": 0,
      "type": "int32"
    },
    {
      "evidence": "loaded by FLD float ptr [ESP+0x838] at 0x00e6c888 and stored into the outgoing word forwarded to GameInput::OnMouseDown",
      "name": "mouseX",
      "offset": "ESP+8",
      "slot": 1,
      "type": "raw float dword"
    },
    {
      "evidence": "loaded by FLD float ptr [ESP+0xc] at 0x00e6c860 and stored into the outgoing word forwarded to GameInput::OnMouseDown",
      "name": "mouseY",
      "offset": "ESP+0xc",
      "slot": 2,
      "type": "raw float dword"
    },
    {
      "evidence": "captured into EBX by MOV EBX,[ESP+0x830] at 0x00e6c871 and tested with TEST BL,0x3 at 0x00e6c898",
      "name": "mouseState",
      "offset": "ESP+0x10",
      "slot": 3,
      "type": "uint32",
      "width_bytes": 4
    }
  ],
  "ret_form": "RET 0x10 on all four return sites",
  "return_register": "AL, set by MOV AL,0x1 or XOR AL,AL",
  "stack_cleanup_bytes": 16
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
      "entry_ESP+0xc",
      "entry_ESP+0x10",
      "entry_ESP+0x102c",
      "entry_ESP+0x1030",
      "entry_ESP+0x1034",
      "entry_ESP+0x103c",
      "entry_ESP+0x1048",
      "entry_ESP+0x104c",
      "entry_ESP+0x1054",
      "entry_ESP+0x1058",
      "entry_ESP+0x186c",
      "entry_ESP+0x1870"
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
      },
      {
        "entry_offset": "entry_ESP+0xc",
        "observed": true,
        "ordinal": 3,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x10",
        "observed": true,
        "ordinal": 4,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x102c",
        "observed": true,
        "ordinal": 1035,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x1030",
        "observed": true,
        "ordinal": 1036,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x1034",
        "observed": true,
        "ordinal": 1037,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x103c",
        "observed": true,
        "ordinal": 1039,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x1048",
        "observed": true,
        "ordinal": 1042,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x104c",
        "observed": true,
        "ordinal": 1043,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x1054",
        "observed": true,
        "ordinal": 1045,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x1058",
        "observed": true,
        "ordinal": 1046,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x186c",
        "observed": true,
        "ordinal": 1563,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x1870",
        "observed": true,
        "ordinal": 1564,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "ret_form": "RET 0x10",
    "return_register": "ST0",
    "return_semantics": "float_or_x87_in_ST0",
    "saved_registers": [
      "EBP",
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
      },
      {
        "entry_offset": "entry_ESP+0xc",
        "observed": true,
        "ordinal": 3,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x10",
        "observed": true,
        "ordinal": 4,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x102c",
        "observed": true,
        "ordinal": 1035,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x1030",
        "observed": true,
        "ordinal": 1036,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x1034",
        "observed": true,
        "ordinal": 1037,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x103c",
        "observed": true,
        "ordinal": 1039,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x1048",
        "observed": true,
        "ordinal": 1042,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "wr
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "embedded_object_first_word_init_00743b50",
    "reconstructed": true,
    "va": "0x00743b50"
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
      "0x00e7c8c0",
      "0x00e7c8c0",
      "0x00e5c0f0",
      "0x00e7c8c0",
      "0x00e6c860"
    ],
    "conflict_id": "U7",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The cited direct body establishes a bounded state mutation or call anchor, but the full transition policy, consumer order, and runtime reachability remain unresolved.",
    "resolution_status": "The cited direct body establishes a bounded state mutation or call anchor, but the full transition policy, consumer order, and runtime reachability remain unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00e5c0f0",
      "0x00e6c860",
      "0x00e7d660"
    ],
    "conflict_id": "U9",
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
  "count": 117,
  "instructions": [
    {
      "address": "00e6c860",
      "instruction": "FLD float ptr [ESP + 0xc]"
    },
    {
      "address": "00e6c864",
      "instruction": "MOV ECX,dword ptr [0x016b3c0c]"
    },
    {
      "address": "00e6c86a",
      "instruction": "SUB ESP,0x81c"
    },
    {
      "address": "00e6c870",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00e6c871",
      "instruction": "MOV EBX,dword ptr [ESP + 0x830]"
    },
    {
      "address": "00e6c878",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00e6c879",
      "instruction": "MOV EBP,dword ptr [ESP + 0x828]"
    },
    {
      "address": "00e6c880",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00e6c881",
      "instruction": "SUB ESP,0x8"
    },
    {
      "address": "00e6c884",
      "instruction": "FSTP float ptr [ESP + 0x4]"
    },
    {
      "address": "00e6c888",
      "instruction": "FLD float ptr [ESP + 0x838]"
    },
    {
      "address": "00e6c88f",
      "instruction": "FSTP float ptr [ESP]"
    },
    {
      "address": "00e6c892",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00e6c893",
      "instruction": "CALL 0x00697ab0"
    },
    {
      "address": "00e6c898",
      "instruction": "TEST BL,0x3"
    },
    {
      "address": "00e6c89b",
      "instruction": "JNZ 0x00e6c962"
    },
    {
      "address": "00e6c8a1",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00e6c8a2",
      "instruction": "CALL 0x00e6c780"
    },
    {
      "address": "00e6c8a7",
      "instruction": "MOV ESI,EAX"
    },
    {
      "address": "00e6c8a9",
      "instruction": "CMP EBP,0x3e8"
    },
    {
      "address": "00e6c8af",
      "instruction": "JNZ 0x00e6c8be"
    },
    {
      "address": "00e6c8b1",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "00e6c8b3",
      "instruction": "JZ 0x00e6c8be"
    },
    {
      "address": "00e6c8b5",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00e6c8b6",
      "instruction": "CALL 0x00e643e0"
    },
    {
      "address": "00e6c8bb",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "00e6c8be",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00e6c8bf",
      "instruction": "LEA ECX,[ESP + 0x10]"
    },
    {
      "address": "00e6c8c3",
      "instruction": "CALL 0x00743b50"
    },
    {
      "address": "00e6c8c8",
      "instruction": "LEA EAX,[ESP + 0x10]"
    },
    {
      "address": "00e6c8cc",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00e6c8cd",
      "instruction": "CALL 0x00e4ce40"
    },
    {
      "address": "00e6c8d2",
      "instruction": "MOV EDI,dword ptr [EAX + 0xd4]"
    },
    {
      "address": "00e6c8d8",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "00e6c8db",
      "instruction": "LEA ECX,[ESP + 0x10]"
    },
    {
      "address": "00e6c8df",
      "instruction": "CALL 0x00e82130"
    },
    {
      "address": "00e6c8e4",
      "instruction": "MOV EAX,EDI"
    },
    {
      "address": "00e6c8e6",
      "instruction": "SUB EAX,0x1"
    },
    {
      "address": "00e6c8e9",
      "instruction": "POP EDI"
    },
    {
      "address": "00e6c8ea",
      "instruction": "JZ 0x00e6c917"
    },
    {
      "address": "00e6c8ec",
      "instruction": "SUB EAX,0x1"
    },
    {
      "address": "00e6c8ef",
      "instruction": "JNZ 0x00e6c945"
    },
    {
      "address": "00e6c8f1",
      "instruction": "CMP EBP,0x3e8"
    },
    {
      "address": "00e6c8f7",
      "instruction": "JNZ 0x00e6c945"
    },
    {
      "address": "00e6c8f9",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "00e6c8fb",
      "instruction": "JZ 0x00e6c945"
    },
    {
      "address": "00e6c8fd",
      "instruction": "MOV ECX,dword ptr [0x016b3c0c]"
    },
    {
      "address": "00e6c903",
      "instruction": "MOV dword ptr [ECX + 0xc4],ESI"
    },
    {
      "address": "00e6c909",
      "instruction": "POP ESI"
    },
    {
      "address": "00e6c90a",
      "instruction": "POP EBP"
    },
    {
      "address": "00e6c90b",
      "instruction": "MOV AL,0x1"
    },
    {
      "address": "00e6c90d",
      "instruction": "POP EBX"
    },
    {
      "address": "00e6c90e",
      "instruction": "ADD ESP,0x81c"
    },
    {
      "address": "00e6c914",
      "instruction": "RET 0x10"
    },
    {
      "address": "00e6c917",
      "instruction": "CMP EBP,0x3e8"
    },
    {
      "address": "00e6c91d",
      "instruction": "JZ 0x00e6c927"
    },
    {
      "address": "00e6c91f",
      "instruction": "CMP EBP,0x3ea"
    },
    {
      "address": "00e6c925",
      "instruction": "JNZ 0x00e6c945"
    },
    {
      "address": "00e6c927",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "00e6c929",
      "instruction": "JZ 0x00e6c945"
    },
    {
      "address": "00e6c92b",
      "instruction": "MOV EDX,dword ptr [0x016b3c0c]"
    },
    {
      "address": "00e6c931",
      "instruction": "MOV dword ptr [EDX + 0xc4],ESI"
    },
    {
      "address": "00e6c937",
      "instruction": "POP ESI"
    },
    {
      "address": "00e6c938",
      "instruction": "POP EBP"
    },
    {
      "address": "00e6c939",
      "instruction": "MOV AL,0x1"
    },
    {
      "address": "00e6c93b",
      "instruction": "POP EBX"
    },
    {
      "address": "00e6c93c",
      "instruction": "ADD ESP,0x81c"
    },
    {
      "address": "00e6c942",
      "instruction": "RET 0x10"
    },
    {
      "address": "00e6c945",
      "instruction": "MOV EAX,[0x016b3c0c]"
    },
    {
      "address": "00e6c94a",
      "instruction": "POP ESI"
    },
    {
      "address": "00e6c94b",
      "instruction": "POP EBP"
    },
    {
      "address": "00e6c94c",
      "instruction": "MOV dword ptr [EAX + 0xc4],0x0"
    },
    {
      "address": "00e6c956",
      "instruction": "XOR AL,AL"
    },
    {
      "address": "00e6c958",
      "instruction": "POP EBX"
    },
    {
   
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
  "original_bytes": 10843,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"thiscall\",\n    \"hidden_receiver\": \"ECX App::cCellModeStrategy*\",\n    \"ordinary_stack_arguments\": [\n      {\n        \"evidence\": \"captured into EBP by MOV EBP,[ESP+0x828] at 0x00e6c879 and compared in full 32-bit width against 0x3e8 and 0x3ea\",\n        \"name\": \"mouseButton\",\n        \"offset\": \"ESP+4\",\n        \"slot\": 0,\n        \"type\": \"int32\"\n      },\n      {\n        \"evidence\": \"loaded by FLD float ptr [ESP+0x838] at 0x00e6c888 and stored into the outgoing word forwarded to GameInput::OnMouseDown\",\n        \"name\": \"mouseX\",\n        \"offset\": \"ESP+8\",\n        \"slot\": 1,\n        \"type\": \"raw float dword\"\n      },\n      {\n        \"evidence\": \"loaded by FLD float ptr [ESP+0xc] at 0x00e6c860 and stored into the outgoing word forwarded to GameInput::OnMouseDown\",\n        \"name\": \"mouseY\",\n        \"offset\": \"ESP+0xc\",\n        \"slot\": 2,\n        \"type\": \"raw float dword\"\n      },\n      {\n        \"evidence\": \"captured into EBX by MOV EBX,[ESP+0x830] at 0x00e6c871 and tested with TEST BL,0x3 at 0x00e6c898\",\n        \"name\": \"mouseState\",\n        \"offset\": \"ESP+0x10\",\n        \"slot\": 3,\n        \"type\": \"uint32\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"ret_form\": \"RET 0x10 on all four return sites\",\n    \"return_register\": \"AL, set by MOV AL,0x1 or XOR AL,AL\",\n    \"stack_cleanup_bytes\": 16\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:DATA,OpaqueCellModeStrategy,int32,raw float dword\",\n        \"shared_vtable:vtable:0x01485550\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE8\",\n      \"score\": 34,\n      \"symbol\": \"cell_mode_strategy_on_mouse_up_00e5c0f0\",\n      \"va\": \"0x00e5c0f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:DATA,OpaqueCellModeStrategy,int32,raw float dword\",\n        \"shared_vtable:vtable:0x01485550\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE8\",\n      \"score\": 34,\n      \"symbol\": \"cell_mode_strategy_on_mouse_wheel_00e7d660\",\n      \"va\": \"0x00e7d660\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_types:DATA,bool in AL,raw float dword\",\n        \"shared_vtable:vtable:0x01485550\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE7\",\n      \"score\": 21,\n      \"symbol\": \"cell_mode_strategy_on_mouse_move_00e51010\",\n      \"va\": \"0x00e51010\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_types:DATA,bool in AL,int32\",\n        \"shared_vtable:vtable:0x01485550\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE7\",\n      \"score\": 21,\n      \"symbol\": \"cell_mode_strategy_on_key_down_00e818f0\",\n      \"va\": \"0x00e818f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:DATA,OpaqueCellModeStrategy\",\n        \"shared_vtable:vtable:0x01485550\"\n      ],\n      \"package\": \"PKG-APP-LIFECYCLE-WAVE8\",\n      \"score\": 15,\n      \"symbol\": \"app_c_cell_mode_strategy_dispose_00e81f30\",\n      \"va\": \"0x00e81f30\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_types:int32\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE7\",\n      \"score\": 11,\n      \"symbol\": \"game_input_on_key_down_00697a50\",\n      \"va\": \"0x00697a50\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_types:int32\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE7\",\n      \"score\": 11,\n      \"symbol\": \"game_input_on_key_up_00697a80\",\n      \"va\": \"0x00697a80\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_types:int32\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE7\",\n      \"score\": 11,\n      \"symbol\": \"game_input_mouse_up_00697af0\",\n      \"va\": \"0x00697af0\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Static mechanics and x86-32 ABI reviewed from live Ghidra; runtime values, concrete owners, and unresolved ports remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueCellModeStrategy\",\n  \"cluster\": \"app-lifecycle\",\n  \"confidence\": 0.7,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"embedded_object_first_word_init_00743b50\",\n        \"reconstructed\": true,\n        \"va\": \"0x00743b50\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00e6c962\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067dd10\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e6c893\",\n        \"direction\": \"out\",\n        \"other\": \"0x00697ab0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e6c8c3\",\n        \"direction\": \"out\",\n        \"other\": \"0x00743b50\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e6c994\",\n        \"direction\": \"out\",\n        \"other\": \"0x007c4730\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\":
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
  "body_end": "00e6c9ec",
  "body_span_bytes": 397,
  "body_start": "00e6c860",
  "callees": [
    "FUN_00e4ce40",
    "FUN_00e643e0",
    "FUN_00e87200",
    "FUN_00e82130",
    "FUN_007c4730",
    "Graphics::IRenderer::Get",
    "FUN_00697ab0",
    "FUN_00e6c780",
    "FUN_00743b50"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00e6c860",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_80c",
      "storage": "Stack[-0x80c]:1",
      "type": "undefined"
    },
    {
      "name": "local_818",
      "storage": "Stack[-0x818]:1",
      "type": "undefined"
    },
    {
      "name": "local_81c",
      "storage": "Stack[-0x81c]:1",
      "type": "undefined"
    },
    {
      "name": "local_82c",
      "storage": "Stack[-0x82c]:4",
      "type": "undefined4"
    },
    {
      "name": "local_830",
      "storage": "Stack[-0x830]:4",
      "type": "undefined4"
    },
    {
      "name": "local_834",
      "storage": "Stack[-0x834]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 6,
  "mode": "live",
  "name": "App::cCellModeStrategy::OnMouseDown",
  "namespace": "App",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 5,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "cCellModeStrategy *"
    },
    {
      "name": "mouseButton",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "MouseButton"
    },
    {
      "name": "mouseX",
      "ordinal": 2,
      "storage": "Stack[0xc]:4",
      "type": "float"
    },
    {
      "name": "mouseY",
      "ordinal": 3,
      "storage": "Stack[0x10]:4",
      "type": "float"
    },
    {
      "name": "mouseState",
      "ordinal": 4,
      "storage": "Stack[0x14]:4",
      "type": "MouseState"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "bool",
  "return_type_resolved": true,
  "rva": "0xa6c860",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "bool App::cCellModeStrategy::OnMouseDown(cCellModeStrategy * this, MouseButton mouseButton, float mouseX, float mouseY, MouseState mouseState)",
  "size_bytes": 397,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00e6c860",
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
      "from": "01485584"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__cCellModeStrategy__OnMouseDown.c",
  "file": "src/reconstruction/pkg_game_input_wave8/game_input_wave8.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__cCellModeStrategy__OnMouseDown.c",
    "src/reconstruction/pkg_game_input_wave8/game_input_wave8.cpp",
    "src/reconstruction/pkg_game_input_wave8/game_input_wave8.hpp",
    "src/reconstruction/pkg_game_input_wave8/game_input_wave8_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave8/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-game-input-wave8/00e6c860.json"
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
    "Observe the concrete vtable call shape, the global Cell game and Cell state pointer validity, the 0x00e6c780 pick result, the sub-object mode word at offset 0xd4, and both publication words in the original Cell mode."
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
  "OpaqueCellModeStrategy",
  "bool in AL",
  "int32",
  "raw float dword",
  "uint32"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x01485550",
  "vtable:0x01485584"
]
```

## Conflicts

```json
[
  {
    "anchors": [
      "0x00e7c8c0",
      "0x00e7c8c0",
      "0x00e5c0f0",
      "0x00e7c8c0",
      "0x00e6c860"
    ],
    "conflict_id": "U7",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The cited direct body establishes a bounded state mutation or call anchor, but the full transition policy, consumer order, and runtime reachability remain unresolved.",
    "resolution_status": "The cited direct body establishes a bounded state mutation or call anchor, but the full transition policy, consumer order, and runtime reachability remain unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00e5c0f0",
      "0x00e6c860",
      "0x00e7d660"
    ],
    "conflict_id": "U9",
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
