# Evidence 0x00e7a7c0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `b172a87585df2590f47d5112a03c1d58f2e1bbe76d9f79fd2f88f70573039f82`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "stack_cleanup_bytes": 24
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
      "entry_ESP+0x10",
      "entry_ESP+0x1c",
      "entry_ESP+0x20",
      "entry_ESP+0x34",
      "entry_ESP+0x3c",
      "entry_ESP+0x40",
      "entry_ESP+0x44",
      "entry_ESP+0x4c",
      "entry_ESP+0x54"
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
        "entry_offset": "entry_ESP+0x1c",
        "observed": true,
        "ordinal": 7,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x20",
        "observed": true,
        "ordinal": 8,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "confidence": "UNKNOWN",
        "entry_offset": "entry_ESP+0x34",
        "observed": true,
        "ordinal": 13,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1,
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x3c",
        "observed": true,
        "ordinal": 15,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x40",
        "observed": true,
        "ordinal": 16,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x44",
        "observed": true,
        "ordinal": 17,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x4c",
        "observed": true,
        "ordinal": 19,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x54",
        "observed": true,
        "ordinal": 21,
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
        "entry_offset": "entry_ESP+0x1c",
        "observed": true,
        "ordinal": 7,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x20",
        "observed": true,
        "ordinal": 8,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "confidence": "UNKNOWN",
        "entry_offset": "entry_ESP+0x34",
        "observed": true,
        "ordinal": 13,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1,
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x3c",
        "observed": true,
        "ordinal": 15,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x40",
        "observed": true,
        "ordinal": 16,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x44",
        "observed": true,
        "ordinal": 17,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x4c",
        "observed": true,
        "ordinal": 19,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x54",
        "observed": true,
        "ordinal": 21,
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
    "flow_not_modelled: the linear ESP walk ends at -40, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no
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
  },
  {
    "name": "Simulator::Cell::ShouldNotAttack",
    "reconstructed": false,
    "va": "0x00e57460"
  },
  {
    "name": "Simulator::Cell::GetDamageAmount",
    "reconstructed": false,
    "va": "0x00e58980"
  },
  {
    "name": "Simulator::Cell::cCellUI::ShowHealthRollover",
    "reconstructed": false,
    "va": "0x00e62340"
  },
  {
    "name": "Simulator::Cell::PlayAnimation",
    "reconstructed": false,
    "va": "0x00e6d200"
  },
  {
    "name": "FUN_00e7a4a0",
    "reconstructed": true,
    "va": "0x00e7a4a0"
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
    "va": "0x00e7b0a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e7e7f0"
  }
]
```

## contradictions

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "original_bytes": 12235,
  "preview": "[\n  {\n    \"anchors\": [\n      \"0x00e62340\",\n      \"0x00e780a0\",\n      \"0x00e7a7c0\",\n      \"0x00e806b0\",\n      \"0x00e7a7c0\",\n      \"0x00e62340\",\n      \"0x00e780a0\",\n      \"0x00e806b0\",\n      \"0x00e7fd00\",\n      \"0x00e74a20\",\n      \"0x00e780a0\",\n      \"0x00e74a20\",\n      \"0x00e74a20\",\n      \"0x00e4ce20\",\n      \"0x00e5b790\",\n      \"0x00e665c0\"\n    ],\n    \"conflict_id\": \"U-003-cell-respawn-policy\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"Damage/death branches, despawn cleanup, optional scale replacement, and deferred stage rebuild are concrete. Caller-specific respawn policy and replacement ordering are unresolved.\",\n    \"resolution_status\": \"Damage/death branches, despawn cleanup, optional scale replacement, and deferred stage rebuild are concrete. Caller-specific respawn policy and replacement ordering are unresolved.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00e62340\",\n      \"0x00e780a0\",\n      \"0x00e7a7c0\",\n      \"0x00e806b0\",\n      \"0x00e7a7c0\",\n      \"0x00e62340\",\n      \"0x00e780a0\",\n      \"0x00e806b0\",\n      \"0x00e62200\",\n      \"0x00e62200\",\n      \"0x00e62340\",\n      \"0x00e62340\",\n      \"0x007d8c80\"\n    ],\n    \"conflict_id\": \"U-CELL-ROLLOVER\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"Rollover creation is guarded by GFX presence, receives a health-derived value, and receives mDisappearTime=0.5. Expiry, hide, reuse, and release order are unresolved.\",\n    \"resolution_status\": \"Rollover creation is guarded by GFX presence, receives a health-derived value, and receives mDisappearTime=0.5. Expiry, hide, reuse, and release order are unresolved.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x0000411c\",\n      \"0x00e62340\",\n      \"0x00e780a0\",\n      \"0x00e7a7c0\",\n      \"0x00e806b0\",\n      \"0x00e7a7c0\",\n      \"0x00e62340\",\n      \"0x00e780a0\",\n      \"0x00e806b0\",\n      \"0x00e74a20\",\n      \"0x000051d8\",\n      \"0x00e780a0\",\n      \"0x00b721d0\",\n      \"0x00b72260\",\n      \"0x00e771d0\",\n      \"0x00e7d370\"\n    ],\n    \"conflict_id\": \"U2\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The cited direct body establishes a bounded state mutation or call anchor, but the full transition policy, consumer order, and runtime reachability remain unresolved.\",\n    \"resolution_status\": \"The cited direct body establishes a bounded state mutation or call anchor, but the full transition policy, consumer order, and runtime reachability remain unresolved.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00e62340\",\n      \"0x00e780a0\",\n      \"0x00e7a7c0\",\n      \"0x00e806b0\",\n      \"0x00e7a7c0\",\n      \"0x00e62340\",\n      \"0x00e780a0\",\n      \"0x00e806b0\",\n      \"0x00e7e130\"\n    ],\n    \"conflict_id\": \"U4\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The cited direct body establishes a bounded state mutation or call anchor, but the full transition policy, consumer order, and runtime reachability remain unresolved.\",\n    \"resolution_status\": \"The cited direct body establishes a bounded state mutation or call anchor, but the full transition policy, consumer order, and runtime reachability remain unresolved.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00e62340\",\n      \"0x00e780a0\",\n      \"0x00e7a7c0\",\n      \"0x00e806b0\",\n      \"0x00e7a7c0\",\n      \"0x00e62340\",\n      \"0x00e780a0\",\n      \"0x00e806b0\",\n      \"0x00e74a20\",\n      \"0x00e780a0\",\n      \"0x00b721d0\",\n      \"0x00b72260\",\n      \"0x00e771d0\",\n      \"0x00e7d370\",\n      \"0x00e7a4a0\"\n    ],\n    \"conflict_id\": \"U6\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The cited direct body establishes a bounded state mutation or call anchor, but the full transition policy, consumer order, and runtime reachability remain unresolved.\",\n    \"resolution_status\": \"The cited direct body establishes a bounded state mutation or call anchor, but the full transition policy, consumer order, and runtime reachability remain unresolved.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00d2e490\",\n      \"0x00d2e4a0\",\n      \"0x0169e394\",\n      \"0x00d2e490\",\n      \"0x00e7a4a0\",\n      \"0x00e7a7c0\",\n      \"0x0169e394\",\n      \"0x00d2e490\",\n      \"0x00d2e490\",\n      \"0x00d2e490\",\n      \"0x00d2e4a0\",\n      \"0x00d2e4a0\",\n      \"0x00d2e4a0\",\n      \"0x00e57460\",\n      \"0x00e57460\",\n      \"0x00e7a7c0\"\n    ],\n    \"conflict_id\": \"ability_mode_callers_and_domain\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The committed evidence does not establ
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
  "count": 203,
  "instructions": [
    {
      "address": "00e7a7c0",
      "instruction": "SUB ESP,0xc"
    },
    {
      "address": "00e7a7c3",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00e7a7c4",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00e7a7c5",
      "instruction": "MOV EDI,dword ptr [ESP + 0x18]"
    },
    {
      "address": "00e7a7c9",
      "instruction": "MOV ESI,EDI"
    },
    {
      "address": "00e7a7cb",
      "instruction": "CALL 0x00e52960"
    },
    {
      "address": "00e7a7d0",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00e7a7d2",
      "instruction": "JNZ 0x00e7a7da"
    },
    {
      "address": "00e7a7d4",
      "instruction": "POP EDI"
    },
    {
      "address": "00e7a7d5",
      "instruction": "POP ESI"
    },
    {
      "address": "00e7a7d6",
      "instruction": "ADD ESP,0xc"
    },
    {
      "address": "00e7a7d9",
      "instruction": "RET"
    },
    {
      "address": "00e7a7da",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00e7a7db",
      "instruction": "MOV EBP,dword ptr [ESP + 0x20]"
    },
    {
      "address": "00e7a7df",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00e7a7e0",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00e7a7e1",
      "instruction": "CALL 0x00e57460"
    },
    {
      "address": "00e7a7e6",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "00e7a7e9",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00e7a7eb",
      "instruction": "JNZ 0x00e7a7fd"
    },
    {
      "address": "00e7a7ed",
      "instruction": "CMP byte ptr [EDI + 0x17c],AL"
    },
    {
      "address": "00e7a7f3",
      "instruction": "JNZ 0x00e7a7fd"
    },
    {
      "address": "00e7a7f5",
      "instruction": "CMP byte ptr [EDI + 0x111],AL"
    },
    {
      "address": "00e7a7fb",
      "instruction": "JZ 0x00e7a806"
    },
    {
      "address": "00e7a7fd",
      "instruction": "POP EBP"
    },
    {
      "address": "00e7a7fe",
      "instruction": "POP EDI"
    },
    {
      "address": "00e7a7ff",
      "instruction": "XOR AL,AL"
    },
    {
      "address": "00e7a801",
      "instruction": "POP ESI"
    },
    {
      "address": "00e7a802",
      "instruction": "ADD ESP,0xc"
    },
    {
      "address": "00e7a805",
      "instruction": "RET"
    },
    {
      "address": "00e7a806",
      "instruction": "MOV EAX,dword ptr [EBP]"
    },
    {
      "address": "00e7a809",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00e7a80a",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00e7a80b",
      "instruction": "CALL 0x00e71ce0"
    },
    {
      "address": "00e7a810",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00e7a811",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00e7a812",
      "instruction": "CALL 0x00e58980"
    },
    {
      "address": "00e7a817",
      "instruction": "MOV ESI,EAX"
    },
    {
      "address": "00e7a819",
      "instruction": "ADD ESP,0x10"
    },
    {
      "address": "00e7a81c",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "00e7a81e",
      "instruction": "JLE 0x00e7a88a"
    },
    {
      "address": "00e7a820",
      "instruction": "MOV ECX,dword ptr [0x016b3c04]"
    },
    {
      "address": "00e7a826",
      "instruction": "MOV EAX,dword ptr [ECX + 0x411c]"
    },
    {
      "address": "00e7a82c",
      "instruction": "CMP EAX,dword ptr [EDI]"
    },
    {
      "address": "00e7a82e",
      "instruction": "JZ 0x00e7a83e"
    },
    {
      "address": "00e7a830",
      "instruction": "CMP EAX,dword ptr [EBP]"
    },
    {
      "address": "00e7a833",
      "instruction": "JZ 0x00e7a83e"
    },
    {
      "address": "00e7a835",
      "instruction": "CMP byte ptr [EBP + 0x110],0x0"
    },
    {
      "address": "00e7a83c",
      "instruction": "JZ 0x00e7a84e"
    },
    {
      "address": "00e7a83e",
      "instruction": "MOV EDX,dword ptr [EDI + 0x244]"
    },
    {
      "address": "00e7a844",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00e7a845",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00e7a846",
      "instruction": "CALL 0x00e62340"
    },
    {
      "address": "00e7a84b",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "00e7a84e",
      "instruction": "SUB dword ptr [EDI + 0x244],ESI"
    },
    {
      "address": "00e7a854",
      "instruction": "CMP dword ptr [EDI + 0x244],0x0"
    },
    {
      "address": "00e7a85b",
      "instruction": "LEA EAX,[EDI + 0x244]"
    },
    {
      "address": "00e7a861",
      "instruction": "MOV dword ptr [ESP + 0xc],0x0"
    },
    {
      "address": "00e7a869",
      "instruction": "LEA ECX,[ESP + 0xc]"
    },
    {
      "address": "00e7a86d",
      "instruction": "JL 0x00e7a871"
    },
    {
      "address": "00e7a86f",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00e7a871",
      "instruction": "MOV ECX,dword ptr [ECX]"
    },
    {
      "address": "00e7a873",
      "instruction": "MOV ESI,EBP"
    },
    {
      "address": "00e7a875",
      "instruction": "MOV dword ptr [EAX],ECX"
    },
    {
      "address": "00e7a877",
      "instruction": "CALL 0x00e57910"
    },
    {
      "address": "00e7a87c",
      "instruction": "MOV EDX,dword ptr [EBP]"
    },
    {
      "address": "00e7a87f",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00e7a880",
      "instruction": "MOV ESI,EDI"
    },
    {
      "address": "00e7a882",
      "instruction": "CALL 0x00e576f0"
    },
    {
      "address": "00e7a887",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "00e7a88a",
      "instruction": "CVTSI2SS XMM0,dword ptr [EDI + 0x244]"
    },
    {
      "address": "00e7a892",
      "instruction": "UCOMISS XMM0,dword ptr [0x01485378]"
    },
    {
      "address": "00e7a899",
      "instruction": "LAHF"
    },
    {
      "address"
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
  "original_bytes": 20166,
  "preview": "{\n  \"abi\": {\n    \"stack_cleanup_bytes\": 24\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:CellObjectData,CellObjectData*,CellResourceRef\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-06-CELL-STATE\",\n      \"score\": 31,\n      \"symbol\": \"FUN_00e7a4a0\",\n      \"va\": \"0x00e7a4a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:CellObjectData,CellResourceRef\"\n      ],\n      \"package\": \"PKG-06-CELL-STATE\",\n      \"score\": 25,\n      \"symbol\": \"FUN_00e780a0\",\n      \"va\": \"0x00e780a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:CellObjectData,CellResourceRef\"\n      ],\n      \"package\": \"PKG-06-CELL-STATE\",\n      \"score\": 20,\n      \"symbol\": \"FUN_00e7fd00\",\n      \"va\": \"0x00e7fd00\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-06A-CELL-AI-SELECTION\",\n      \"score\": 6,\n      \"symbol\": \"cell_ai_select_profile_00e52910\",\n      \"va\": \"0x00e52910\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-11-H3-HELPER-WAVE2\",\n      \"score\": 3,\n      \"symbol\": \"embedded_object_first_word_init_00743b50\",\n      \"va\": \"0x00743b50\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Static damage/death mechanics accepted; field meanings and actual runtime damage, health, resource, effect, and global state remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"CellObjectData\",\n  \"cluster\": null,\n  \"confidence\": 0.65,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"embedded_object_first_word_init_00743b50\",\n        \"reconstructed\": true,\n        \"va\": \"0x00743b50\"\n      },\n      {\n        \"name\": \"Simulator::Cell::ShouldNotAttack\",\n        \"reconstructed\": false,\n        \"va\": \"0x00e57460\"\n      },\n      {\n        \"name\": \"Simulator::Cell::GetDamageAmount\",\n        \"reconstructed\": false,\n        \"va\": \"0x00e58980\"\n      },\n      {\n        \"name\": \"Simulator::Cell::cCellUI::ShowHealthRollover\",\n        \"reconstructed\": false,\n        \"va\": \"0x00e62340\"\n      },\n      {\n        \"name\": \"Simulator::Cell::PlayAnimation\",\n        \"reconstructed\": false,\n        \"va\": \"0x00e6d200\"\n      },\n      {\n        \"name\": \"FUN_00e7a4a0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00e7a4a0\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e7b0a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e7e7f0\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00e7b15a\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e7b0a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7b20a\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e7b0a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7f096\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e7e7f0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7a8ec\",\n        \"direction\": \"out\",\n        \"other\": \"0x00743b50\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7a93c\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b72210\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7a8fd\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e4cc40\",\n        \"reference_type\": \"thunk\"\n      },\n      {\n        \"callsite\": \"0x00e7a9bf\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e51ee0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7a7cb\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e52960\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7a7e1\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e57460\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7a882\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e576f0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7a877\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e57910\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7a812\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e58980\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7a9d8\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e59010\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7a846\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e62340\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7a94c\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e6d200\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7a80b\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e71ce0\",\n        \"reference_type\": \"direct-
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
  "body_end": "00e7aa0a",
  "body_span_bytes": 587,
  "body_start": "00e7a7c0",
  "callees": [
    "Simulator::Cell::ShouldNotAttack",
    "FUN_00e57910",
    "Simulator::Cell::GetDamageAmount",
    "FUN_00e71ce0",
    "FUN_00e7a770",
    "thunk_FUN_00e823a0",
    "FUN_00e82130",
    "Simulator::Cell::cCellUI::ShowHealthRollover",
    "FUN_00e576f0",
    "FUN_00b72210",
    "FUN_00e7a4a0",
    "FUN_00e51ee0",
    "FUN_00e52960",
    "FUN_00743b50",
    "Simulator::Cell::PlayAnimation",
    "FUN_00e59010"
  ],
  "callers": [
    "FUN_00e7b0a0",
    "FUN_00e7e7f0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00e7a7c0",
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
      "storage": "Stack[-0x8]:1",
      "type": "undefined"
    },
    {
      "name": "local_c",
      "storage": "Stack[-0xc]:4",
      "type": "undefined4"
    },
    {
      "name": "local_1c",
      "storage": "Stack[-0x1c]:4",
      "type": "undefined4"
    },
    {
      "name": "local_20",
      "storage": "Stack[-0x20]:4",
      "type": "undefined4"
    },
    {
      "name": "local_24",
      "storage": "Stack[-0x24]:4",
      "type": "undefined4"
    },
    {
      "name": "local_38",
      "storage": "Stack[-0x38]:4",
      "type": "undefined4"
    },
    {
      "name": "local_3c",
      "storage": "Stack[-0x3c]:4",
      "type": "undefined4"
    },
    {
      "name": "local_58",
      "storage": "Stack[-0x58]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 9,
  "mode": "live",
  "name": "FUN_00e7a7c0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xa7a7c0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00e7a7c0(void)",
  "size_bytes": 587,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00e7a7c0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 5,
  "xrefs": [
    {
      "from": "00e7f096"
    },
    {
      "from": "00e7b15a"
    },
    {
      "from": "00e7b20a"
    },
    {
      "from": "00e7b335"
    },
    {
      "from": "00e7b3d7"
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
  "file": "src/reconstruction/pkg06_cell_state/cell_state.cpp",
  "files": [
    "src/reconstruction/pkg06_cell_state/cell_state.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg06-cell-state/00e7a7c0.json"
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
    "cell_damage_transition_observation"
  ],
  "validated": 0
}
```

## semantic_hypotheses

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

```json
{
  "original_bytes": 11417,
  "preview": "{\n  \"category\": null,\n  \"classification\": \"NEEDS_RUNTIME\",\n  \"confidence\": {\n    \"overall\": \"SUPPORTED\"\n  },\n  \"contradictions\": [],\n  \"downstream_unlock_count\": 18,\n  \"evidence\": [\n    {\n      \"independent_limit\": \"Decompiler parameter types and unnamed helper semantics are not authoritative.\",\n      \"kind\": \"direct_decompilation\",\n      \"source\": \"Ghidra MCP:SporeApp.exe@0x00e7a7c0\",\n      \"supports\": [\n        \"six-argument body\",\n        \"attack gates\",\n        \"health clamp\",\n        \"animation mapping\",\n        \"death dispatch\"\n      ]\n    },\n    {\n      \"independent_limit\": \"Same binary source; used as an assembly cross-check, not a separate runtime source.\",\n      \"kind\": \"disassembly\",\n      \"source\": \"Ghidra MCP:SporeApp.exe@0x00e7a7c0\",\n      \"supports\": [\n        \"stack argument flow\",\n        \"field offsets +0x17c/+0x244\",\n        \"conditional return paths\"\n      ]\n    },\n    {\n      \"independent_limit\": \"Static call graph does not prove runtime frequency or reachability.\",\n      \"kind\": \"callgraph_xrefs\",\n      \"source\": \"Ghidra MCP:SporeApp.exe@xrefs@0x00e7a7c0\",\n      \"supports\": [\n        \"2 direct callers\",\n        \"16 direct callees\",\n        \"death/effect/UI fan-out\"\n      ]\n    },\n    {\n      \"independent_limit\": \"Several fields remain unnamed.\",\n      \"kind\": \"structure_layout\",\n      \"source\": \"Ghidra MCP:SporeApp.exe@structure:cCellObjectData\",\n      \"supports\": [\n        \"920-byte record\",\n        \"health/resource/scale/query/GFX offsets\"\n      ]\n    },\n    {\n      \"independent_limit\": \"Secondary artifact; no runtime proof.\",\n      \"kind\": \"committed_research_artifact\",\n      \"source\": \"docs/analysis/event-message-map.md:102-105\",\n      \"supports\": [\n        \"cell_damage_resolved and cell_death_started\"\n      ]\n    }\n  ],\n  \"family\": \"combat_damage_and_terminal_transition\",\n  \"interfaces\": {\n    \"boundaries\": {\n      \"boundary_rule\": \"Do not treat UI/effect calls as proof that the renderer owns health, damage, or identity.\",\n      \"classification\": \"cross_boundary\",\n      \"inbound\": \"Cell simulation damage event\",\n      \"outbound\": [\n        \"Cell health and AI reaction\",\n        \"UI health rollover\",\n        \"animation/effect presentation\",\n        \"death/event transition\"\n      ]\n    },\n    \"direct_callees\": [\n      {\n        \"role\": \"global damage/attack gate\",\n        \"va\": \"0x00e52960\"\n      },\n      {\n        \"name\": \"Simulator::Cell::ShouldNotAttack\",\n        \"role\": \"attack eligibility\",\n        \"va\": \"0x00e57460\"\n      },\n      {\n        \"role\": \"nearby flee/chase reaction\",\n        \"va\": \"0x00e71ce0\"\n      },\n      {\n        \"name\": \"Simulator::Cell::GetDamageAmount\",\n        \"role\": \"damage table\",\n        \"va\": \"0x00e58980\"\n      },\n      {\n        \"name\": \"Simulator::Cell::cCellUI::ShowHealthRollover\",\n        \"role\": \"health UI\",\n        \"va\": \"0x00e62340\"\n      },\n      {\n        \"role\": \"non-player death\",\n        \"va\": \"0x00e7a4a0\"\n      },\n      {\n        \"role\": \"health-zero death guard\",\n        \"va\": \"0x00e7a770\"\n      },\n      {\n        \"name\": \"Simulator::Cell::PlayAnimation\",\n        \"role\": \"damage animation intent\",\n        \"va\": \"0x00e6d200\"\n      },\n      {\n        \"role\": \"effect/impact dispatch; exact name unresolved\",\n        \"va\": \"0x00e51ee0\"\n      },\n      {\n        \"role\": \"contact/attack update; exact name unresolved\",\n        \"va\": \"0x00e59010\"\n      },\n      {\n        \"role\": \"post-damage helper; exact name unresolved\",\n        \"va\": \"0x00e57910\"\n      },\n      {\n        \"role\": \"post-damage helper; exact name unresolved\",\n        \"va\": \"0x00e576f0\"\n      }\n    ],\n    \"direct_callers\": [\n      {\n        \"name\": \"FUN_00e7b0a0\",\n        \"role\": \"contact/attack wrapper\",\n        \"va\": \"0x00e7b0a0\"\n      },\n      {\n        \"name\": \"FUN_00e7e7f0\",\n        \"role\": \"event-dispatch damage/eat branch\",\n        \"va\": \"0x00e7e7f0\"\n      }\n    ],\n    \"globals\": [],\n    \"structures\": [],\n    \"vtables\": [],\n    \"worker_contract_surface\": {\n      \"failure_behavior\": {\n        \"lethal_death\": \"The function returns the death helper's result and does not locally normalize it to 1.\",\n        \"null_or_invalid_cell\": \"No explicit null check exists before dereferencing victim/attacker; invalid pool entries are caller-precondition failures.\",\n        \"rejected_attack\": \"Returns 0 when the global gate, ShouldNotAttack, field_17C, or invulnerability rejects the interaction.\",\n        \"zero_damage\": \"The accepted path can still select/play the default damage animation and return 1; exact runtime intent is unresolved.\"\n      },\n      \"identity_boundary\": \"not_reported\",\n      \"inputs\": [],\n      \"ordering\": [],\n      \"outputs\": [],\n      \"postconditions\": [\n        \"Accepted damage subtracts GetDamageAmount(attacker, victim) from victim->mHealthPoints.\",\n        \"mHealthPoints is clamped to zero and never becomes negative.\",\n        \"A health rollover is requested when victim or attacker is avatar-related or attacker->field_110 is true.\",\n        \"If health reaches zero, the selected player/non-player death path is called and its result is returned.\",\n        \"If health remains positive, a damage animation/effect path is dispatched and the function returns 1.\",\n        \"Rejected damage returns 0 without the accepted health write.\"\n      ],\n      \"preconditions\": [\n        \"FUN_00e52960 returns nonzero.\",\n        \"ShouldNotAttack(victim, attacker) returns false.\",\n        \"victim->field_17C is zero and victim->mIsI
[TRUNCATED]
```

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
  "CellObjectData",
  "CellObjectData*",
  "CellResourceRef",
  "OpaqueCellDirectionPayload",
  "const CellDirectionVector*",
  "float",
  "std::uint32_t",
  "std::uint8_t"
]
```

## vtables

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## Conflicts

```json
{
  "original_bytes": 12235,
  "preview": "[\n  {\n    \"anchors\": [\n      \"0x00e62340\",\n      \"0x00e780a0\",\n      \"0x00e7a7c0\",\n      \"0x00e806b0\",\n      \"0x00e7a7c0\",\n      \"0x00e62340\",\n      \"0x00e780a0\",\n      \"0x00e806b0\",\n      \"0x00e7fd00\",\n      \"0x00e74a20\",\n      \"0x00e780a0\",\n      \"0x00e74a20\",\n      \"0x00e74a20\",\n      \"0x00e4ce20\",\n      \"0x00e5b790\",\n      \"0x00e665c0\"\n    ],\n    \"conflict_id\": \"U-003-cell-respawn-policy\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"Damage/death branches, despawn cleanup, optional scale replacement, and deferred stage rebuild are concrete. Caller-specific respawn policy and replacement ordering are unresolved.\",\n    \"resolution_status\": \"Damage/death branches, despawn cleanup, optional scale replacement, and deferred stage rebuild are concrete. Caller-specific respawn policy and replacement ordering are unresolved.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00e62340\",\n      \"0x00e780a0\",\n      \"0x00e7a7c0\",\n      \"0x00e806b0\",\n      \"0x00e7a7c0\",\n      \"0x00e62340\",\n      \"0x00e780a0\",\n      \"0x00e806b0\",\n      \"0x00e62200\",\n      \"0x00e62200\",\n      \"0x00e62340\",\n      \"0x00e62340\",\n      \"0x007d8c80\"\n    ],\n    \"conflict_id\": \"U-CELL-ROLLOVER\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"Rollover creation is guarded by GFX presence, receives a health-derived value, and receives mDisappearTime=0.5. Expiry, hide, reuse, and release order are unresolved.\",\n    \"resolution_status\": \"Rollover creation is guarded by GFX presence, receives a health-derived value, and receives mDisappearTime=0.5. Expiry, hide, reuse, and release order are unresolved.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x0000411c\",\n      \"0x00e62340\",\n      \"0x00e780a0\",\n      \"0x00e7a7c0\",\n      \"0x00e806b0\",\n      \"0x00e7a7c0\",\n      \"0x00e62340\",\n      \"0x00e780a0\",\n      \"0x00e806b0\",\n      \"0x00e74a20\",\n      \"0x000051d8\",\n      \"0x00e780a0\",\n      \"0x00b721d0\",\n      \"0x00b72260\",\n      \"0x00e771d0\",\n      \"0x00e7d370\"\n    ],\n    \"conflict_id\": \"U2\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The cited direct body establishes a bounded state mutation or call anchor, but the full transition policy, consumer order, and runtime reachability remain unresolved.\",\n    \"resolution_status\": \"The cited direct body establishes a bounded state mutation or call anchor, but the full transition policy, consumer order, and runtime reachability remain unresolved.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00e62340\",\n      \"0x00e780a0\",\n      \"0x00e7a7c0\",\n      \"0x00e806b0\",\n      \"0x00e7a7c0\",\n      \"0x00e62340\",\n      \"0x00e780a0\",\n      \"0x00e806b0\",\n      \"0x00e7e130\"\n    ],\n    \"conflict_id\": \"U4\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The cited direct body establishes a bounded state mutation or call anchor, but the full transition policy, consumer order, and runtime reachability remain unresolved.\",\n    \"resolution_status\": \"The cited direct body establishes a bounded state mutation or call anchor, but the full transition policy, consumer order, and runtime reachability remain unresolved.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00e62340\",\n      \"0x00e780a0\",\n      \"0x00e7a7c0\",\n      \"0x00e806b0\",\n      \"0x00e7a7c0\",\n      \"0x00e62340\",\n      \"0x00e780a0\",\n      \"0x00e806b0\",\n      \"0x00e74a20\",\n      \"0x00e780a0\",\n      \"0x00b721d0\",\n      \"0x00b72260\",\n      \"0x00e771d0\",\n      \"0x00e7d370\",\n      \"0x00e7a4a0\"\n    ],\n    \"conflict_id\": \"U6\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The cited direct body establishes a bounded state mutation or call anchor, but the full transition policy, consumer order, and runtime reachability remain unresolved.\",\n    \"res
[TRUNCATED]
```
