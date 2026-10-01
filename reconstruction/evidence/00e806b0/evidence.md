# Evidence 0x00e806b0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `2afe9e34c38e0266b262e35e748d749f31753be7964f14446d4e25992c2c0771`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "cdecl body with caller-cleaned adapter subset",
  "ordinary_stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "machine_type": "float",
      "normalized_name": "first_stack_word",
      "position": 1,
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x08",
      "machine_type": "float",
      "normalized_name": "second_stack_word",
      "position": 2,
      "width_bytes": 4
    }
  ],
  "receiver_register": "ECX register residue is not normalized as a body parameter",
  "ret_form": "plain RET",
  "return_register": "EAX",
  "return_width_bytes": 0
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
      "entry_ESP+0x18",
      "entry_ESP+0x1c"
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
        "entry_offset": "entry_ESP+0x18",
        "observed": true,
        "ordinal": 6,
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
      }
    ],
    "ret_form": "RET",
    "return_register": "ST0",
    "return_semantics": "float_or_x87_in_ST0",
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
        "entry_offset": "entry_ESP+0x18",
        "observed": true,
        "ordinal": 6,
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
      }
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +4, so the listing is not one path",
    "slot_gaps_present: argument ordinal(s) below the highest read slot are never touched",
    "receiver_not_determinable: ecx_reassigned_before_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_reassigned_before_deref), and the convention rule that would apply discriminates on receiver absence"
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
  "content_sha256": "b2d96a23fd7684dada08ae262aa0e225f5a7b8b86beb3a0ed192ec52234ccb64",
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
    "ghidra_parameter_count": 0,
    "persisted": "no_information",
    "persisted_calling_convention": "cdecl body with caller-cleaned adapter subset"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 6,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0017",
        "obs-0078",
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
        "obs-0008",
        "obs-0021",
        "obs-0025",
        "obs-0026",
        "obs-0027",
        "obs-0028",
        "obs-0029",
        "obs-0030",
        "obs-0031",
        "obs-0034",
        "obs-0035",
        "obs-0036",
        "obs-0037",
        "obs-0038",
        "obs-0039",
        "obs-0043",
        "obs-0044",
        "obs-0045",
        "obs-0047",
        "obs-0048",
        "obs-0053",
        "obs-0056",
        "obs-0065",
        "obs-0069",
        "obs-0072",
        "obs-0075",
        "obs-0080",
        "obs-0081",
        "obs-0082",
        "obs-0083",
        "obs-0087",
        "obs-0088",
        "obs-0091",
        "obs-0094"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 1,
        "observed_slots": 6,
        "total_bytes":
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "root_accessor_00b3d3f0",
    "reconstructed": true,
    "va": "0x00b3d3f0"
  },
  {
    "name": "Simulator_cSpaceTrading_Get",
    "reconstructed": true,
    "va": "0x00b3d4d0"
  },
  {
    "name": "cell_move_player_to_mouse_position_00e5b790",
    "reconstructed": true,
    "va": "0x00e5b790"
  },
  {
    "name": "FUN_00e7fd00",
    "reconstructed": true,
    "va": "0x00e7fd00"
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
    "name": "cell_mode_update_00e80980",
    "reconstructed": true,
    "va": "0x00e80980"
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
      "0x00e62340",
      "0x00e780a0",
      "0x00e7a7c0",
      "0x00e806b0",
      "0x00e7a7c0",
      "0x00e62340",
      "0x00e780a0",
      "0x00e806b0",
      "0x00e7fd00",
      "0x00e74a20",
      "0x00e780a0",
      "0x00e74a20",
      "0x00e74a20",
      "0x00e4ce20",
      "0x00e5b790",
      "0x00e665c0"
    ],
    "conflict_id": "U-003-cell-respawn-policy",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "Damage/death branches, despawn cleanup, optional scale replacement, and deferred stage rebuild are concrete. Caller-specific respawn policy and replacement ordering are unresolved.",
    "resolution_status": "Damage/death branches, despawn cleanup, optional scale replacement, and deferred stage rebuild are concrete. Caller-specific respawn policy and replacement ordering are unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00e62340",
      "0x00e780a0",
      "0x00e7a7c0",
      "0x00e806b0",
      "0x00e7a7c0",
      "0x00e62340",
      "0x00e780a0",
      "0x00e806b0",
      "0x00e62200",
      "0x00e62200",
      "0x00e62340",
      "0x00e62340",
      "0x007d8c80"
    ],
    "conflict_id": "U-CELL-ROLLOVER",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "Rollover creation is guarded by GFX presence, receives a health-derived value, and receives mDisappearTime=0.5. Expiry, hide, reuse, and release order are unresolved.",
    "resolution_status": "Rollover creation is guarded by GFX presence, receives a health-derived value, and receives mDisappearTime=0.5. Expiry, hide, reuse, and release order are unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x0000411c",
      "0x00e62340",
      "0x00e780a0",
      "0x00e7a7c0",
      "0x00e806b0",
      "0x00e7a7c0",
      "0x00e62340",
      "0x00e780a0",
      "0x00e806b0",
      "0x00e74a20",
      "0x000051d8",
      "0x00e780a0",
      "0x00b721d0",
      "0x00b72260",
      "0x00e771d0",
      "0x00e7d370"
    ],
    "conflict_id": "U2",
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
      "0x000051e0",
      "0x000051e0",
      "0x000051e0",
      "0x000051e0",
      "0x000051e0",
      "0x00e806b0"
    ],
    "conflict_id": "U3",
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
      "0x00e62340",
      "0x00e780a0",
      "0x00e7a7c0",
      "0x00e806b0",
      "0x00e7a7c0",
      "0x00e62340",
      "0x00e780a0",
      "0x00e806b0",
      "0x00e7e130"
    ],
    "conflict_id": "U4",
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
      "0x00e62340",
      "0x00e780a0",
      "0x00e7a7c0",
      "0x00e806b0",
      "0x00e7a7c0",
      "0x00e62340",
      "0x00e780a0",
      "0x00e806b0",
      "0x00e74a20",
      "0x00e780a0",
      "0x00b721d0",
      "0x00b72260",
      "0x00e771d0",
      "0x00e7d370",
      "0x00e7a4a0"
    ],
    "conflict_id": "U6",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The cited direct body establishes a bounded state mutation or call anchor, but the full transition policy, consumer order, and runtime reachability remain unresolved.",
    "resolution_status": "The cited direct body establishes a bounded state mutation or call anchor, but the full transition policy, consumer order, and runtime reachability remain unresolved.",
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
  "count": 189,
  "instructions": [
    {
      "address": "00e806b0",
      "instruction": "SUB ESP,0xc"
    },
    {
      "address": "00e806b3",
      "instruction": "CALL 0x00e84bf0"
    },
    {
      "address": "00e806b8",
      "instruction": "MOV ECX,dword ptr [0x016b3c04]"
    },
    {
      "address": "00e806be",
      "instruction": "MOV EDX,dword ptr [ECX + 0x51e0]"
    },
    {
      "address": "00e806c4",
      "instruction": "TEST EDX,EDX"
    },
    {
      "address": "00e806c6",
      "instruction": "JZ 0x00e80731"
    },
    {
      "address": "00e806c8",
      "instruction": "MOVSS XMM0,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00e806ce",
      "instruction": "UCOMISS XMM0,dword ptr [0x01485378]"
    },
    {
      "address": "00e806d5",
      "instruction": "LAHF"
    },
    {
      "address": "00e806d6",
      "instruction": "TEST AH,0x44"
    },
    {
      "address": "00e806d9",
      "instruction": "JNP 0x00e8096d"
    },
    {
      "address": "00e806df",
      "instruction": "MOV EAX,EDX"
    },
    {
      "address": "00e806e1",
      "instruction": "SUB EAX,0x1"
    },
    {
      "address": "00e806e4",
      "instruction": "JZ 0x00e80713"
    },
    {
      "address": "00e806e6",
      "instruction": "SUB EAX,0x1"
    },
    {
      "address": "00e806e9",
      "instruction": "JNZ 0x00e8096d"
    },
    {
      "address": "00e806ef",
      "instruction": "CALL 0x00e82c70"
    },
    {
      "address": "00e806f4",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00e806f6",
      "instruction": "JZ 0x00e8096d"
    },
    {
      "address": "00e806fc",
      "instruction": "CALL 0x0067de20"
    },
    {
      "address": "00e80701",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00e80703",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00e80705",
      "instruction": "MOV EAX,dword ptr [EDX + 0x20]"
    },
    {
      "address": "00e80708",
      "instruction": "PUSH 0x14137f8"
    },
    {
      "address": "00e8070d",
      "instruction": "CALL EAX"
    },
    {
      "address": "00e8070f",
      "instruction": "ADD ESP,0xc"
    },
    {
      "address": "00e80712",
      "instruction": "RET"
    },
    {
      "address": "00e80713",
      "instruction": "CALL 0x00e82c70"
    },
    {
      "address": "00e80718",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00e8071a",
      "instruction": "JZ 0x00e8096d"
    },
    {
      "address": "00e80720",
      "instruction": "CALL 0x0067dd20"
    },
    {
      "address": "00e80725",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00e80727",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00e80729",
      "instruction": "MOV EAX,dword ptr [EDX + 0x40]"
    },
    {
      "address": "00e8072c",
      "instruction": "ADD ESP,0xc"
    },
    {
      "address": "00e8072f",
      "instruction": "JMP EAX"
    },
    {
      "address": "00e80731",
      "instruction": "CMP dword ptr [ECX + 0x515c],0x0"
    },
    {
      "address": "00e80738",
      "instruction": "JNZ 0x00e808e9"
    },
    {
      "address": "00e8073e",
      "instruction": "MOVSS XMM0,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00e80744",
      "instruction": "UCOMISS XMM0,dword ptr [0x01485378]"
    },
    {
      "address": "00e8074b",
      "instruction": "LAHF"
    },
    {
      "address": "00e8074c",
      "instruction": "TEST AH,0x44"
    },
    {
      "address": "00e8074f",
      "instruction": "JNP 0x00e808e9"
    },
    {
      "address": "00e80755",
      "instruction": "MOVSS XMM1,dword ptr [0x013ec5b4]"
    },
    {
      "address": "00e8075d",
      "instruction": "INC dword ptr [ECX + 0x5160]"
    },
    {
      "address": "00e80763",
      "instruction": "MULSS XMM0,XMM1"
    },
    {
      "address": "00e80767",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00e80768",
      "instruction": "MOVSS dword ptr [ESP + 0x8],XMM0"
    },
    {
      "address": "00e8076e",
      "instruction": "MOVSS dword ptr [ESP + 0x4],XMM0"
    },
    {
      "address": "00e80774",
      "instruction": "CVTSS2SI EAX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "00e8077a",
      "instruction": "MOVSS XMM0,dword ptr [ESP + 0x18]"
    },
    {
      "address": "00e80780",
      "instruction": "MULSS XMM0,XMM1"
    },
    {
      "address": "00e80784",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00e80786",
      "instruction": "MOVSS dword ptr [ESP + 0x4],XMM0"
    },
    {
      "address": "00e8078c",
      "instruction": "MOVSS dword ptr [ESP + 0xc],XMM0"
    },
    {
      "address": "00e80792",
      "instruction": "CVTSS2SI EAX,dword ptr [ESP + 0xc]"
    },
    {
      "address": "00e80798",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00e80799",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00e8079a",
      "instruction": "CALL 0x00e82de0"
    },
    {
      "address": "00e8079f",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "00e807a2",
      "instruction": "CALL 0x00b3d4d0"
    },
    {
      "address": "00e807a7",
      "instruction": "MOVSS XMM0,dword ptr [ESP + 0x8]"
    },
    {
      "address": "00e807ad",
      "instruction": "LEA ECX,[EAX + 0x4]"
    },
    {
      "address": "00e807b0",
      "instruction": "MOVSS dword ptr [ESP + 0xc],XMM0"
    },
    {
      "address": "00e807b6",
      "instruction": "CVTSS2SI EAX,dword ptr [ESP + 0xc]"
    },
    {
      "address": "00e807bc",
      "instruction": "MOVSS XMM0,dword ptr [ESP + 0x4]"
    },
    {
      "address": "00e807c2",
      "instruction": "MOV EDX,EAX"
    },
    {
      "address": "00e807c4",
      "instruction": "MOVSS dword ptr [ESP + 0xc],XMM0"
    },
    {
      "address": "00e807ca",
      "instruction": "CVTSS2SI EAX,dword ptr [ESP + 0xc]"
    },
    {
      "address": "00e807d0",
      "instruction": "MOV ESI,dword ptr [ECX]"
 
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
  "original_bytes": 9636,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"cdecl body with caller-cleaned adapter subset\",\n    \"ordinary_stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"machine_type\": \"float\",\n        \"normalized_name\": \"first_stack_word\",\n        \"position\": 1,\n        \"width_bytes\": 4\n      },\n      {\n        \"entry_offset\": \"ESP+0x08\",\n        \"machine_type\": \"float\",\n        \"normalized_name\": \"second_stack_word\",\n        \"position\": 2,\n        \"width_bytes\": 4\n      }\n    ],\n    \"receiver_register\": \"ECX register residue is not normalized as a body parameter\",\n    \"ret_form\": \"plain RET\",\n    \"return_register\": \"EAX\",\n    \"return_width_bytes\": 0\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueCellUpdateBody\"\n      ],\n      \"package\": \"PKG-FRAME-RUNTIME-WAVE8\",\n      \"score\": 22,\n      \"symbol\": \"timing_update_body_00b31cc0\",\n      \"va\": \"0x00b31cc0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-FRAME-RUNTIME-WAVE7\",\n      \"score\": 9,\n      \"symbol\": \"cell_mode_update_00e80980\",\n      \"va\": \"0x00e80980\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-FRAME-RUNTIME-WAVE7\",\n      \"score\": 6,\n      \"symbol\": \"app_frame_update_00f47930\",\n      \"va\": \"0x00f47930\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-11-H2-ROOT-ACCESSORS\",\n      \"score\": 3,\n      \"symbol\": \"root_accessor_00b3d3f0\",\n      \"va\": \"0x00b3d3f0\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 3,\n      \"symbol\": \"Simulator_cSpaceTrading_Get\",\n      \"va\": \"0x00b3d4d0\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-CAMERA-WAVE7\",\n      \"score\": 3,\n      \"symbol\": \"cell_move_player_to_mouse_position_00e5b790\",\n      \"va\": \"0x00e5b790\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-06-CELL-STATE\",\n      \"score\": 3,\n      \"symbol\": \"FUN_00e7fd00\",\n      \"va\": \"0x00e7fd00\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Static mechanics and x86-32 ABI reviewed from live Ghidra; runtime values, concrete owners, and unresolved ports remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueCellUpdateBody\",\n  \"cluster\": null,\n  \"confidence\": 0.7,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"root_accessor_00b3d3f0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b3d3f0\"\n      },\n      {\n        \"name\": \"Simulator_cSpaceTrading_Get\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b3d4d0\"\n      },\n      {\n        \"name\": \"cell_move_player_to_mouse_position_00e5b790\",\n        \"reconstructed\": true,\n        \"va\": \"0x00e5b790\"\n      },\n      {\n        \"name\": \"FUN_00e7fd00\",\n        \"reconstructed\": true,\n        \"va\": \"0x00e7fd00\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": \"cell_mode_update_00e80980\",\n        \"reconstructed\": true,\n        \"va\": \"0x00e80980\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00e80992\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e80980\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e80720\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067dd20\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e806fc\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067de20\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e80947\",\n        \"direction\": \"out\",\n        \"other\": \"0x006ffe00\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e807d9\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b3d3f0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e8091a\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b3d3f0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e807a2\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b3d4d0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e808e9\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b3d4d0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e808bc\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e53b00\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e8083b\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e5b790\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e808ce\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e600a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e80956\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e600a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"
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
  "body_end": "00e80970",
  "body_span_bytes": 705,
  "body_start": "00e806b0",
  "callees": [
    "Graphics::ITextureManager::Get",
    "FUN_00e73f60",
    "FUN_00e82de0",
    "FUN_00e7fd00",
    "FUN_00e84bf0",
    "FUN_00e7f3a0",
    "FUN_00e82c70",
    "FUN_006ffe00",
    "Simulator::cSpaceTrading::Get",
    "Simulator::Cell::MovePlayerToMousePosition",
    "App::cIDGenerator::Get",
    "FUN_00e7f550",
    "FUN_00e600a0",
    "FUN_00e6c9f0",
    "FUN_00b3d3f0",
    "FUN_00e53b00"
  ],
  "callers": [
    "App::cCellModeStrategy::Update"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00e806b0",
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
    },
    {
      "name": "local_c",
      "storage": "Stack[-0xc]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 3,
  "mode": "live",
  "name": "FUN_00e806b0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xa806b0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00e806b0(void)",
  "size_bytes": 705,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00e806b0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "00e80992"
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
  "file": "src/reconstruction/pkg_frame_runtime_wave8/frame_runtime_wave8.cpp",
  "files": [
    "src/reconstruction/pkg_frame_runtime_wave8/frame_runtime_wave8.cpp",
    "src/reconstruction/pkg_frame_runtime_wave8/frame_runtime_wave8.hpp",
    "src/reconstruction/pkg_frame_runtime_wave8/frame_runtime_wave8_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave8/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-frame-runtime-wave8/00e806b0.json"
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
    "required"
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
  "OpaqueCellUpdateBody"
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
      "0x00e62340",
      "0x00e780a0",
      "0x00e7a7c0",
      "0x00e806b0",
      "0x00e7a7c0",
      "0x00e62340",
      "0x00e780a0",
      "0x00e806b0",
      "0x00e7fd00",
      "0x00e74a20",
      "0x00e780a0",
      "0x00e74a20",
      "0x00e74a20",
      "0x00e4ce20",
      "0x00e5b790",
      "0x00e665c0"
    ],
    "conflict_id": "U-003-cell-respawn-policy",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "Damage/death branches, despawn cleanup, optional scale replacement, and deferred stage rebuild are concrete. Caller-specific respawn policy and replacement ordering are unresolved.",
    "resolution_status": "Damage/death branches, despawn cleanup, optional scale replacement, and deferred stage rebuild are concrete. Caller-specific respawn policy and replacement ordering are unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00e62340",
      "0x00e780a0",
      "0x00e7a7c0",
      "0x00e806b0",
      "0x00e7a7c0",
      "0x00e62340",
      "0x00e780a0",
      "0x00e806b0",
      "0x00e62200",
      "0x00e62200",
      "0x00e62340",
      "0x00e62340",
      "0x007d8c80"
    ],
    "conflict_id": "U-CELL-ROLLOVER",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "Rollover creation is guarded by GFX presence, receives a health-derived value, and receives mDisappearTime=0.5. Expiry, hide, reuse, and release order are unresolved.",
    "resolution_status": "Rollover creation is guarded by GFX presence, receives a health-derived value, and receives mDisappearTime=0.5. Expiry, hide, reuse, and release order are unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x0000411c",
      "0x00e62340",
      "0x00e780a0",
      "0x00e7a7c0",
      "0x00e806b0",
      "0x00e7a7c0",
      "0x00e62340",
      "0x00e780a0",
      "0x00e806b0",
      "0x00e74a20",
      "0x000051d8",
      "0x00e780a0",
      "0x00b721d0",
      "0x00b72260",
      "0x00e771d0",
      "0x00e7d370"
    ],
    "conflict_id": "U2",
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
      "0x000051e0",
      "0x000051e0",
      "0x000051e0",
      "0x000051e0",
      "0x000051e0",
      "0x00e806b0"
    ],
    "conflict_id": "U3",
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
      "0x00e62340",
      "0x00e780a0",
      "0x00e7a7c0",
      "0x00e806b0",
      "0x00e7a7c0",
      "0x00e62340",
      "0x00e780a0",
      "0x00e806b0",
      "0x00e7e130"
    ],
    "conflict_id": "U4",
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
      "0x00e62340",
      "0x00e780a0",
      "0x00e7a7c0",
      "0x00e806b0",
      "0x00e7a7c0",
      "0x00e62340",
      "0x00e780a0",
      "0x00e806b0",
      "0x00e74a20",
      "0x00e780a0"
[TRUNCATED]
```
