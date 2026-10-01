# Evidence 0x00c8d060

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `ff0d76380b911d8e1ce59d0acf3f58229f63d62e23d1c69a88e57c526a6eba1a`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "cdecl",
  "hidden_this_register": null,
  "return_type": "void",
  "saved_registers": [
    "EBX",
    "EBP",
    "ESI",
    "EDI"
  ],
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "record",
      "position": 1,
      "type": "OpaqueRecord*",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 0,
  "termination": "plain RET on every return path"
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
      }
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
    "receiver_not_determinable: ecx_read_without_deref",
    "esp_alignment_unknown: the entry-relative ESP offset is unknown and there is no frame pointer to fall back on"
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
  "content_sha256": "3663bda2634b8dc5469988e7aeaf44e3df3b52edeaa6d41ee3fff5b839a9c0bc",
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
    "ghidra_parameter_count": 0,
    "persisted": "no_information",
    "persisted_calling_convention": "cdecl"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 5,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0067",
        "obs-0086"
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
        "obs-0004"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "INFERRED",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 1,
        "total_bytes": 4
      }
    },
    {
      "based_on": [
        "obs-0003",
        "obs-0004",
        "obs-0005",
        "obs-0028",
        "obs-0029",
        "obs-0043"
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
        "obs-0001"
      ],
      "claim": "the entry-relative argument offsets are unknown, so the convention is unknown",
      "confidence": "UNKNOWN",
      "id": "C11"
    },
    {
      "based_on": [
        "obs-0067",
        "obs-0086"
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
        "obs-0001"
      ],
      "claim": "the return value is carried in ST0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "ST0"
    }
  ],
  "observations": [
    {
      "and_esp": null,
      "at": "0x00c8d060",
      "ebp_is_general_register": true,
      "fp": false,
      "id": "obs-0001",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": true,
      "push_ebp_at": 3,
      "sub": 28
    },
    {
      "at": "0x00c8d060",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00c8d063",
      "count": 23,
      "first_use": 1,
      "first_write_index": 0,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "reg": "ESP"
    },
    {
      "at": "0x00c8d063",
      "base": "ESP",
      "disp": 32,
      "id": "obs-0004",
      "index": 1,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "resolved": true,
      "size": 4,
      "trust": "untrusted_frame"
    },
    {
      "at": "0x00c8d063",
      "definite": true,
      "id": "obs-0005",
      "index": 1,
      "kind": "REG_WRITE",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00c8d067",
      "count": 7,
      "first_use": 2,
      "first_write_index": 9,
      "id": "obs-0006",
      "index": 2,
      "kind": "REG_READ",
      "reg": "EBX"
    },
    {
      "at": "0x00c8d068",
      "count": 8,
      "first_use": 3,
      "first_write_index": 6,
      "id": "obs-0007",
      "index": 3,
      "kind": "REG_READ",
      "reg": "EBP"
    },
    {
      "at": "0x00c8d069",
      "count": 17,
      "first_use": 4,
      "first_write_index": 7,
      "id": "obs-0008",
      "index": 4,
      "kind": "REG_READ",
      "reg": "ESI"
    },
    {
      "at": "0x00c8d06a",
      "id": "obs-0009",
      "index": 5,
      "kind": "CALL_DIRECT",
      "target": "0x00bba790"
    },
    {
      "at": "0x00c8d06f",
      "count": 25,
   
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
    "name": null,
    "reconstructed": false,
    "va": "0x00b8d970"
  },
  {
    "name": "FUN_00b8dab0",
    "reconstructed": false,
    "va": "0x00b8dab0"
  },
  {
    "name": "FUN_00b8de30",
    "reconstructed": false,
    "va": "0x00b8de30"
  },
  {
    "name": "FUN_00bba790",
    "reconstructed": false,
    "va": "0x00bba790"
  },
  {
    "name": "FUN_00c772c0",
    "reconstructed": false,
    "va": "0x00c772c0"
  },
  {
    "name": "FUN_00c77bf0",
    "reconstructed": false,
    "va": "0x00c77bf0"
  },
  {
    "name": "FUN_01021080",
    "reconstructed": true,
    "va": "0x01021080"
  },
  {
    "name": "FUN_01021090",
    "reconstructed": false,
    "va": "0x01021090"
  },
  {
    "name": "FUN_010212a0",
    "reconstructed": true,
    "va": "0x010212a0"
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
    "va": "0x00be9b20"
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
      "0x00c341a0",
      "0x00c34ee0",
      "0x00c35240",
      "0x00c8d060",
      "0x00c34ee0",
      "0x00c35240",
      "0x00c3ae70",
      "0x00c3dae0",
      "0x01001360",
      "0x01001360",
      "0x01021080",
      "0x01021080",
      "0x01021300",
      "0x01021300",
      "0x01021960",
      "0x01021960"
    ],
    "conflict_id": "ownership_field_write_order",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The resource seam and cited call boundary are retained, but original ownership, priority, cache, failure, and load-order semantics are unresolved.",
    "resolution_status": "The resource seam and cited call boundary are retained, but original ownership, priority, cache, failure, and load-order semantics are unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x006a1540",
      "0x006a1540",
      "0x00c35240",
      "0x006a1540",
      "0x006a1540",
      "0x006a2f60",
      "0x006a2f60",
      "0x00b3d440",
      "0x00b3d440",
      "0x00c341a0",
      "0x00c341a0",
      "0x00c34ee0",
      "0x00c34ee0",
      "0x00c35240",
      "0x00c35240",
      "0x00c8d060"
    ],
    "conflict_id": "save_schema_and_migration",
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
  "count": 196,
  "instructions": [
    {
      "address": "00c8d060",
      "instruction": "SUB ESP,0x1c"
    },
    {
      "address": "00c8d063",
      "instruction": "MOV ECX,dword ptr [ESP + 0x20]"
    },
    {
      "address": "00c8d067",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00c8d068",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00c8d069",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00c8d06a",
      "instruction": "CALL 0x00bba790"
    },
    {
      "address": "00c8d06f",
      "instruction": "MOV EBP,EAX"
    },
    {
      "address": "00c8d071",
      "instruction": "MOV ESI,dword ptr [EBP + 0x4]"
    },
    {
      "address": "00c8d074",
      "instruction": "SUB ESI,dword ptr [EBP]"
    },
    {
      "address": "00c8d077",
      "instruction": "XOR EBX,EBX"
    },
    {
      "address": "00c8d079",
      "instruction": "SAR ESI,0x2"
    },
    {
      "address": "00c8d07c",
      "instruction": "MOV dword ptr [ESP + 0x24],EBP"
    },
    {
      "address": "00c8d080",
      "instruction": "MOV dword ptr [ESP + 0xc],0xffffffff"
    },
    {
      "address": "00c8d088",
      "instruction": "MOV dword ptr [ESP + 0x20],ESI"
    },
    {
      "address": "00c8d08c",
      "instruction": "MOV dword ptr [ESP + 0x14],EBX"
    },
    {
      "address": "00c8d090",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "00c8d092",
      "instruction": "JLE 0x00c8d2db"
    },
    {
      "address": "00c8d098",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00c8d099",
      "instruction": "LEA ESP,[ESP]"
    },
    {
      "address": "00c8d0a0",
      "instruction": "MOV EAX,dword ptr [EBP]"
    },
    {
      "address": "00c8d0a3",
      "instruction": "MOV EDI,dword ptr [EAX + EBX*0x4]"
    },
    {
      "address": "00c8d0a6",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00c8d0a8",
      "instruction": "MOV dword ptr [ESP + 0x1c],EDI"
    },
    {
      "address": "00c8d0ac",
      "instruction": "CALL 0x00b8dab0"
    },
    {
      "address": "00c8d0b1",
      "instruction": "CMP EAX,0x5"
    },
    {
      "address": "00c8d0b4",
      "instruction": "JNZ 0x00c8d196"
    },
    {
      "address": "00c8d0ba",
      "instruction": "MOV EAX,dword ptr [EDI + 0x28]"
    },
    {
      "address": "00c8d0bd",
      "instruction": "CMP EAX,0x1"
    },
    {
      "address": "00c8d0c0",
      "instruction": "JZ 0x00c8d196"
    },
    {
      "address": "00c8d0c6",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00c8d0c8",
      "instruction": "JZ 0x00c8d196"
    },
    {
      "address": "00c8d0ce",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00c8d0d0",
      "instruction": "CALL 0x00b8d970"
    },
    {
      "address": "00c8d0d5",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00c8d0d7",
      "instruction": "JNZ 0x00c8d196"
    },
    {
      "address": "00c8d0dd",
      "instruction": "MOV ECX,dword ptr [EDI + 0x160]"
    },
    {
      "address": "00c8d0e3",
      "instruction": "SUB ECX,dword ptr [EDI + 0x15c]"
    },
    {
      "address": "00c8d0e9",
      "instruction": "SAR ECX,0x2"
    },
    {
      "address": "00c8d0ec",
      "instruction": "MOV dword ptr [ESP + 0x20],ECX"
    },
    {
      "address": "00c8d0f0",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00c8d0f2",
      "instruction": "JZ 0x00c8d2da"
    },
    {
      "address": "00c8d0f8",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "00c8d0fa",
      "instruction": "MOV dword ptr [ESP + 0x14],EAX"
    },
    {
      "address": "00c8d0fe",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00c8d100",
      "instruction": "JLE 0x00c8d196"
    },
    {
      "address": "00c8d106",
      "instruction": "JMP 0x00c8d110"
    },
    {
      "address": "00c8d110",
      "instruction": "MOV EDX,dword ptr [EDI + 0x15c]"
    },
    {
      "address": "00c8d116",
      "instruction": "MOV EBP,dword ptr [EDX + EAX*0x4]"
    },
    {
      "address": "00c8d119",
      "instruction": "MOV ESI,dword ptr [EBP + 0x40]"
    },
    {
      "address": "00c8d11c",
      "instruction": "SUB ESI,dword ptr [EBP + 0x3c]"
    },
    {
      "address": "00c8d11f",
      "instruction": "SAR ESI,0x2"
    },
    {
      "address": "00c8d122",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "00c8d124",
      "instruction": "JZ 0x00c8d2da"
    },
    {
      "address": "00c8d12a",
      "instruction": "XOR EBX,EBX"
    },
    {
      "address": "00c8d12c",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "00c8d12e",
      "instruction": "JLE 0x00c8d181"
    },
    {
      "address": "00c8d130",
      "instruction": "MOV EAX,dword ptr [EBP + 0x3c]"
    },
    {
      "address": "00c8d133",
      "instruction": "MOV EDI,dword ptr [EAX + EBX*0x4]"
    },
    {
      "address": "00c8d136",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00c8d138",
      "instruction": "CALL 0x00b7e0a0"
    },
    {
      "address": "00c8d13d",
      "instruction": "FLD float ptr [0x013ec4d0]"
    },
    {
      "address": "00c8d143",
      "instruction": "FCOMIP ST0,ST1"
    },
    {
      "address": "00c8d145",
      "instruction": "FSTP ST0"
    },
    {
      "address": "00c8d147",
      "instruction": "JA 0x00c8d2da"
    },
    {
      "address": "00c8d14d",
      "instruction": "CMP dword ptr [ESP + 0x10],-0x1"
    },
    {
      "address": "00c8d152",
      "instruction": "JNZ 0x00c8d15f"
    },
    {
      "address": "00c8d154",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00c8d156",
      "instruction": "CALL 0x00a1ad10"
    },
    {
      "address": "00c8d15b",
      "instruction": "MOV dword ptr [ESP + 0x10],EAX"
    },
    {
      "address": "00c8d15f",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00c8d161",
      "instruction": "CALL 0x00a1a
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
  "original_bytes": 10445,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"cdecl\",\n    \"hidden_this_register\": null,\n    \"return_type\": \"void\",\n    \"saved_registers\": [\n      \"EBX\",\n      \"EBP\",\n      \"ESI\",\n      \"EDI\"\n    ],\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"name\": \"record\",\n        \"position\": 1,\n        \"type\": \"OpaqueRecord*\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 0,\n    \"termination\": \"plain RET on every return path\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"shared_types:OpaqueRecord*\"\n      ],\n      \"package\": \"PKG-13-E4-EMPIRE-WAVE3\",\n      \"score\": 11,\n      \"symbol\": \"EmpirePoliticalColor_00c32cd0\",\n      \"va\": \"0x00c32cd0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:OpaqueRecord*\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 3,\n      \"symbol\": \"editor_entry_expand_004ad6f0\",\n      \"va\": \"0x004ad6f0\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-13-CREATURE-ACCESSOR\",\n      \"score\": 3,\n      \"symbol\": \"pkg13_creature_accessor_00b1fdb0\",\n      \"va\": \"0x00b1fdb0\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 3,\n      \"symbol\": \"FUN_00b3d300\",\n      \"va\": \"0x00b3d300\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 3,\n      \"symbol\": \"FUN_01021080\",\n      \"va\": \"0x01021080\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 3,\n      \"symbol\": \"FUN_010212a0\",\n      \"va\": \"0x010212a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE7\",\n      \"score\": 2,\n      \"symbol\": \"simulator_game_input_manager_get_00b3d350\",\n      \"va\": \"0x00b3d350\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-14-A3-WORLD-WAVE3\",\n      \"score\": 2,\n      \"symbol\": \"sphere_draw_direction_00b7e560\",\n      \"va\": \"0x00b7e560\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"pkg13_creature_accessor_00b1fdb0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b1fdb0\"\n      },\n      {\n        \"name\": \"FUN_00b3d300\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b3d300\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b8d970\"\n      },\n      {\n        \"name\": \"FUN_00b8dab0\",\n        \"reconstructed\": false,\n        \"va\": \"0x00b8dab0\"\n      },\n      {\n        \"name\": \"FUN_00b8de30\",\n        \"reconstructed\": false,\n        \"va\": \"0x00b8de30\"\n      },\n      {\n        \"name\": \"FUN_00bba790\",\n        \"reconstructed\": false,\n        \"va\": \"0x00bba790\"\n      },\n      {\n        \"name\": \"FUN_00c772c0\",\n        \"reconstructed\": false,\n        \"va\": \"0x00c772c0\"\n      },\n      {\n        \"name\": \"FUN_00c77bf0\",\n        \"reconstructed\": false,\n        \"va\": \"0x00c77bf0\"\n      },\n      {\n        \"name\": \"FUN_01021080\",\n        \"reconstructed\": true,\n        \"va\": \"0x01021080\"\n      },\n      {\n        \"name\": \"FUN_01021090\",\n        \"reconstructed\": false,\n        \"va\": \"0x01021090\"\n      },\n      {\n        \"name\": \"FUN_010212a0\",\n        \"reconstructed\": true,\n        \"va\": \"0x010212a0\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00be9b20\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00be9c90\",\n        \"direction\": \"in\",\n        \"other\": \"0x00be9b20\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c8d156\",\n        \"direction\": \"out\",\n        \"other\": \"0x00a1ad10\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c8d161\",\n        \"direction\": \"out\",\n        \"other\": \"0x00a1ad10\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c8d23f\",\n        \"direction\": \"out\",\n        \"other\": \"0x00a206f0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c8d257\",\n        \"direction\": \"out\",\n        \"other\": \"0x00a206f0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c8d219\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b1fdb0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c8d29b\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b3d300\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c8d138\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b7e0a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c8d0d0\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b8d970\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"call
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
  "body_end": "00c8d2e1",
  "body_span_bytes": 642,
  "body_start": "00c8d060",
  "callees": [
    "FUN_00c8d000",
    "FUN_00b8d970",
    "FUN_00c77bf0",
    "FUN_00bba790",
    "FUN_00b8dab0",
    "FUN_01021080",
    "FUN_00b7e0a0",
    "FUN_010212a0",
    "FUN_01002bd0",
    "FUN_00a206f0",
    "FUN_00b8de30",
    "FUN_00b3d300",
    "FUN_00a1ad10",
    "FUN_00c772c0",
    "FUN_01021090",
    "FUN_0106dcd0",
    "FUN_00ff5930",
    "FUN_00b1fdb0",
    "FUN_00f67d90",
    "FUN_010666a0",
    "FUN_00ffa780"
  ],
  "callers": [
    "FUN_00be9b20"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00c8d060",
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
    },
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
      "name": "local_2c",
      "storage": "Stack[-0x2c]:1",
      "type": "undefined"
    }
  ],
  "locals_count": 8,
  "mode": "live",
  "name": "FUN_00c8d060",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x88d060",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00c8d060(void)",
  "size_bytes": 642,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00c8d060",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "00be9c90"
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
    "reconstruction/staging/pkg13-e4-empire-wave3/empire_wave3.cpp",
    "reconstruction/staging/pkg13-e4-empire-wave3/empire_wave3.hpp",
    "reconstruction/staging/pkg13-e4-empire-wave3/empire_wave3_boundary_test.sh",
    "reconstruction/staging/pkg13-e4-empire-wave3/empire_wave3_model_test.cpp",
    "src/reconstruction/pkg13_e4_empire_wave3/empire_wave3.cpp",
    "src/reconstruction/pkg13_e4_empire_wave3/empire_wave3.hpp",
    "src/reconstruction/pkg13_e4_empire_wave3/empire_wave3_boundary_test.sh",
    "src/reconstruction/pkg13_e4_empire_wave3/empire_wave3_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-sim-social-world-wave3/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg13-e4-empire-wave3/00c8d060.json"
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
  "OpaqueRecord*",
  "void"
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
      "0x00c341a0",
      "0x00c34ee0",
      "0x00c35240",
      "0x00c8d060",
      "0x00c34ee0",
      "0x00c35240",
      "0x00c3ae70",
      "0x00c3dae0",
      "0x01001360",
      "0x01001360",
      "0x01021080",
      "0x01021080",
      "0x01021300",
      "0x01021300",
      "0x01021960",
      "0x01021960"
    ],
    "conflict_id": "ownership_field_write_order",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The resource seam and cited call boundary are retained, but original ownership, priority, cache, failure, and load-order semantics are unresolved.",
    "resolution_status": "The resource seam and cited call boundary are retained, but original ownership, priority, cache, failure, and load-order semantics are unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x006a1540",
      "0x006a1540",
      "0x00c35240",
      "0x006a1540",
      "0x006a1540",
      "0x006a2f60",
      "0x006a2f60",
      "0x00b3d440",
      "0x00b3d440",
      "0x00c341a0",
      "0x00c341a0",
      "0x00c34ee0",
      "0x00c34ee0",
      "0x00c35240",
      "0x00c35240",
      "0x00c8d060"
    ],
    "conflict_id": "save_schema_and_migration",
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
