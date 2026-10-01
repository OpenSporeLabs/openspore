# Evidence 0x00d06920

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `3ad546e3ca88ff640d094238b378cbb245a35f887a42c6404542edf53a4d744a`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "thiscall",
  "hidden_this_register": "ECX",
  "hidden_this_type": "OpaqueRelationshipManager*",
  "receiver": "current_root",
  "receiver_register": "ECX",
  "return_type": "OpaqueCurrentRoot*",
  "stack_arguments": [
    {
      "name": "event_id",
      "position": 1,
      "type": "OpaqueWord"
    },
    {
      "name": "event_pointer",
      "position": 2,
      "type": "OpaqueEventRecord*"
    },
    {
      "name": "zero",
      "position": 3,
      "type": "OpaqueWord"
    }
  ],
  "stack_cleanup_bytes": 12,
  "termination": "RET 0x8"
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
    "ret_form": "RET 0x8",
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
      }
    ],
    "stack_cleanup_bytes": 8,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x8"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +80, so the listing is not one path",
    "unparsed_lines_present: 1 line(s) matched no grammar rule",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
    "receiver_not_determinable: ecx_reassigned_before_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_reassigned_before_deref), and the convention rule that would apply discriminates on receiver absence"
  ],
  "cleanup": {
    "bytes": 8,
    "confidence": "SUPPORTED",
    "corroboration": "not_available",
    "evidence": "ret 0x8",
    "side": "callee"
  },
  "completeness": "PARTIAL",
  "conflicts": [
    {
      "field": "stack_cleanup_bytes",
      "inferred": 8,
      "kind": "inferred_vs_persisted",
      "persisted": 12,
      "resolution_status": "unresolved"
    }
  ],
  "content_sha256": "79970bf2337c3e6e8d46145dbe765dff8f24f4d18ca4db09722e6e8385e595ee",
  "conventions": {
    "ambiguities": [
      "receiver_undetermined"
    ],
    "calling_convention": null,
    "candidate_conventions": [
      "__stdcall",
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
    "persisted_calling_convention": "thiscall"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0056"
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
        "obs-0009",
        "obs-0013"
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
        "obs-0016",
        "obs-0033",
        "obs-0041",
        "obs-0043"
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
        "obs-0005",
        "obs-0006",
        "obs-0016",
        "obs-0033",
        "obs-0041",
        "obs-0043"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_reassigned_before_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0056"
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
      "at": "0x00d06920",
      "ebp_is_general_register": true,
      "fp": false,
      "id": "obs-0001",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": true,
      "push_ebp_at": 1,
      "raw": "SUB ESP,0x44",
      "sub": 68
    },
    {
      "at": "0x00d06920",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x44",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00d06923",
      "count": 7,
      "first_use": 1,
      "first_write_index": 3,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EBP",
      "reg": "EBP"
    },
    {
      "at": "0x00d06924",
      "count": 7,
      "first_use": 2,
      "first_write_index": 5,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "E
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "FUN_00b3d2a0",
    "reconstructed": true,
    "va": "0x00b3d2a0"
  },
  {
    "name": "RelationshipLookup_00d01410",
    "reconstructed": true,
    "va": "0x00d01410"
  },
  {
    "name": "RelationshipMapSelect_00d01ab0",
    "reconstructed": true,
    "va": "0x00d01ab0"
  },
  {
    "name": "DiplomacyTransition_00d038e0",
    "reconstructed": true,
    "va": "0x00d038e0"
  },
  {
    "name": "pkg12_space_01021300",
    "reconstructed": true,
    "va": "0x01021300"
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
    "va": "0x00fe9580"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0102ce30"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0102df20"
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
      "0x00d01e30",
      "0x00d01e30",
      "0x00d038e0",
      "0x00d038e0",
      "0x00d05830",
      "0x00d05830",
      "0x00d06270",
      "0x00d06270",
      "0x00d065a0",
      "0x00d065a0",
      "0x00d06920",
      "0x00d06920",
      "0x00596da0"
    ],
    "conflict_id": "U-E001",
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
      "0x00be2590",
      "0x00be2590",
      "0x00d01e30",
      "0x00d01e30",
      "0x00d038e0",
      "0x00d038e0",
      "0x00d05830",
      "0x00d05830",
      "0x00d06270",
      "0x00d06270",
      "0x00d065a0",
      "0x00d065a0",
      "0x00d06920",
      "0x00d06920"
    ],
    "conflict_id": "U-E002",
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
      "0x00d01e30",
      "0x00d01e30",
      "0x00d038e0",
      "0x00d038e0",
      "0x00d05830",
      "0x00d05830",
      "0x00d06270",
      "0x00d06270",
      "0x00d065a0",
      "0x00d065a0",
      "0x00d06920",
      "0x00d06920",
      "0x01037d30",
      "0x010535e0",
      "0x010535f0"
    ],
    "conflict_id": "U-E003",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
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
  "count": 99,
  "instructions": [
    {
      "address": "00d06920",
      "instruction": "SUB ESP,0x44"
    },
    {
      "address": "00d06923",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00d06924",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00d06925",
      "instruction": "MOV EBP,ECX"
    },
    {
      "address": "00d06927",
      "instruction": "CALL 0x01021300"
    },
    {
      "address": "00d0692c",
      "instruction": "MOV ESI,dword ptr [ESP + 0x54]"
    },
    {
      "address": "00d06930",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00d06931",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00d06932",
      "instruction": "MOV EDI,dword ptr [ESP + 0x58]"
    },
    {
      "address": "00d06936",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "00d06938",
      "instruction": "CMOVZ ESI,EAX"
    },
    {
      "address": "00d0693b",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00d0693c",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00d0693d",
      "instruction": "MOV ECX,EBP"
    },
    {
      "address": "00d0693f",
      "instruction": "MOV dword ptr [ESP + 0x18],EAX"
    },
    {
      "address": "00d06943",
      "instruction": "CALL 0x00d038e0"
    },
    {
      "address": "00d06948",
      "instruction": "MOV EBX,dword ptr [ESI + 0x84]"
    },
    {
      "address": "00d0694e",
      "instruction": "MOV EDI,dword ptr [EDI + 0x84]"
    },
    {
      "address": "00d06954",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00d06955",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00d06956",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00d06957",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00d06958",
      "instruction": "MOV ECX,EBP"
    },
    {
      "address": "00d0695a",
      "instruction": "CALL 0x00d01ab0"
    },
    {
      "address": "00d0695f",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00d06960",
      "instruction": "MOV ECX,EBP"
    },
    {
      "address": "00d06962",
      "instruction": "CALL 0x00d01410"
    },
    {
      "address": "00d06967",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00d06969",
      "instruction": "JZ 0x00d0696f"
    },
    {
      "address": "00d0696b",
      "instruction": "OR dword ptr [EAX + 0x4],0x2"
    },
    {
      "address": "00d0696f",
      "instruction": "CMP ESI,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00d06973",
      "instruction": "JZ 0x00d06990"
    },
    {
      "address": "00d06975",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00d06976",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00d06977",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00d06978",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00d06979",
      "instruction": "MOV ECX,EBP"
    },
    {
      "address": "00d0697b",
      "instruction": "CALL 0x00d01ab0"
    },
    {
      "address": "00d06980",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00d06981",
      "instruction": "MOV ECX,EBP"
    },
    {
      "address": "00d06983",
      "instruction": "CALL 0x00d01410"
    },
    {
      "address": "00d06988",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00d0698a",
      "instruction": "JZ 0x00d06990"
    },
    {
      "address": "00d0698c",
      "instruction": "OR dword ptr [EAX + 0x4],0x2"
    },
    {
      "address": "00d06990",
      "instruction": "MOV EDI,dword ptr [ESP + 0x58]"
    },
    {
      "address": "00d06994",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00d06995",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00d06997",
      "instruction": "CALL 0x00c34680"
    },
    {
      "address": "00d0699c",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00d0699d",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00d0699f",
      "instruction": "CALL 0x00c34680"
    },
    {
      "address": "00d069a4",
      "instruction": "CMP ESI,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00d069a8",
      "instruction": "JNZ 0x00d069f6"
    },
    {
      "address": "00d069aa",
      "instruction": "XOR EBX,EBX"
    },
    {
      "address": "00d069ac",
      "instruction": "MOV dword ptr [ESP + 0x44],EBX"
    },
    {
      "address": "00d069b0",
      "instruction": "MOV dword ptr [ESP + 0x14],0x13eb90c"
    },
    {
      "address": "00d069b8",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "00d069ba",
      "instruction": "LEA ECX,[ESP + 0x18]"
    },
    {
      "address": "00d069be",
      "instruction": "XCHG dword ptr [ECX],EAX"
    },
    {
      "address": "00d069c0",
      "instruction": "MOV dword ptr [ESP + 0x14],0x13eb844"
    },
    {
      "address": "00d069c8",
      "instruction": "MOV dword ptr [ESP + 0x4c],EBX"
    },
    {
      "address": "00d069cc",
      "instruction": "MOV dword ptr [ESP + 0x1c],EDI"
    },
    {
      "address": "00d069d0",
      "instruction": "MOV dword ptr [ESP + 0x24],ESI"
    },
    {
      "address": "00d069d4",
      "instruction": "CALL 0x00883860"
    },
    {
      "address": "00d069d9",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00d069db",
      "instruction": "MOV EDX,dword ptr [EDX + 0x14]"
    },
    {
      "address": "00d069de",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00d069df",
      "instruction": "LEA ECX,[ESP + 0x18]"
    },
    {
      "address": "00d069e3",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00d069e4",
      "instruction": "PUSH 0x4445d43"
    },
    {
      "address": "00d069e9",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00d069eb",
      "instruction": "CALL EDX"
    },
    {
      "address": "00d069ed",
      "instruction"
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
  "original_bytes": 11519,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"thiscall\",\n    \"hidden_this_register\": \"ECX\",\n    \"hidden_this_type\": \"OpaqueRelationshipManager*\",\n    \"receiver\": \"current_root\",\n    \"receiver_register\": \"ECX\",\n    \"return_type\": \"OpaqueCurrentRoot*\",\n    \"stack_arguments\": [\n      {\n        \"name\": \"event_id\",\n        \"position\": 1,\n        \"type\": \"OpaqueWord\"\n      },\n      {\n        \"name\": \"event_pointer\",\n        \"position\": 2,\n        \"type\": \"OpaqueEventRecord*\"\n      },\n      {\n        \"name\": \"zero\",\n        \"position\": 3,\n        \"type\": \"OpaqueWord\"\n      }\n    ],\n    \"stack_cleanup_bytes\": 12,\n    \"termination\": \"RET 0x8\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:DiplomacyTransitionPorts,OpaqueEventFactory,OpaqueEventFactory*,OpaqueEventRecord\",\n        \"shared_vtable:vtable:0x00000000\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-13-SIM-DIPLOMACY-TRANSITIONS\",\n      \"score\": 34,\n      \"symbol\": \"DiplomacyTransition_00d01e30\",\n      \"va\": \"0x00d01e30\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:DiplomacyTransitionPorts,OpaqueRelationshipEntry,OpaqueRelationshipManager,OpaqueRelationshipManager*\",\n        \"same_calling_convention\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-13-SIM-DIPLOMACY-TRANSITIONS\",\n      \"score\": 33,\n      \"symbol\": \"DiplomacyTransition_00d038e0\",\n      \"va\": \"0x00d038e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:DiplomacyTransitionPorts,OpaqueRelationshipEntry,OpaqueRelationshipManager,OpaqueRelationshipManager*\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-13-SIM-DIPLOMACY-TRANSITIONS\",\n      \"score\": 30,\n      \"symbol\": \"DiplomacyTransition_00d065a0\",\n      \"va\": \"0x00d065a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:OpaqueRelationshipManager,OpaqueRelationshipMap\",\n        \"same_calling_convention\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-13-SIM-DIPLOMACY-PRIMITIVES\",\n      \"score\": 16,\n      \"symbol\": \"RelationshipMapSelect_00d01ab0\",\n      \"va\": \"0x00d01ab0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:OpaqueRelationshipEntry,OpaqueRelationshipManager,OpaqueRelationshipMap\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-13-SIM-DIPLOMACY-PREDICATE\",\n      \"score\": 16,\n      \"symbol\": \"RelationshipManager_IsAllied2_00d01ff0\",\n      \"va\": \"0x00d01ff0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:OpaqueRelationshipEntry,OpaqueRelationshipMap\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-13-SIM-DIPLOMACY-PRIMITIVES\",\n      \"score\": 9,\n      \"symbol\": \"RelationshipLookup_00d01410\",\n      \"va\": \"0x00d01410\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x00000000\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-13-E2-DIPLOMACY-ALT\",\n      \"score\": 6,\n      \"symbol\": \"RelationshipScoreObjects_00d00d60\",\n      \"va\": \"0x00d00d60\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:OpaqueWord\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 3,\n      \"symbol\": \"re_00575ea0\",\n      \"va\": \"0x00575ea0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [\n    \"All dependency ports remain opaque by design.\",\n    \"No original-process trace is available.\"\n  ],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueRelationshipManager\",\n  \"cluster\": null,\n  \"confidence\": 0.9,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"FUN_00b3d2a0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b3d2a0\"\n      },\n      {\n        \"name\": \"RelationshipLookup_00d01410\",\n        \"reconstructed\": true,\n        \"va\": \"0x00d01410\"\n      },\n      {\n        \"name\": \"RelationshipMapSelect_00d01ab0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00d01ab0\"\n      },\n      {\n        \"name\": \"DiplomacyTransition_00d038e0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00d038e0\"\n      },\n      {\n        \"name\": \"pkg12_space_01021300\",\n        \"reconstructed\": true,\n        \"va\": \"0x01021300\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00fe9580\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0102ce30\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0102df20\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00fe9fea\",\n        \"direction\": \"in\",\n        \"other\": \"0x00fe9580\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0102ceac\",\n        \"direction\": \"in\",\n        \"other\": \"0x0102ce30\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0102f03f\",\n        \"direction\": \"in\",\n        \"other\": \"0x0102df20\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00d069f1\",\n        \"direct
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
  "body_end": "00d06a40",
  "body_span_bytes": 289,
  "body_start": "00d06920",
  "callees": [
    "FUN_00883860",
    "FUN_00d01410",
    "FUN_01021300",
    "FUN_00d01ab0",
    "FUN_00d068c0",
    "FUN_00421cf0",
    "FUN_00c34680",
    "FUN_00c31c50",
    "FUN_00b3d2a0",
    "FUN_00885c90",
    "FUN_00d038e0"
  ],
  "callers": [
    "FUN_0102ce30",
    "FUN_00fe9580",
    "FUN_0102df20"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00d06920",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_8",
      "storage": "Stack[-0x8]:4",
      "type": "undefined4"
    },
    {
      "name": "local_10",
      "storage": "Stack[-0x10]:4",
      "type": "undefined4"
    },
    {
      "name": "local_30",
      "storage": "Stack[-0x30]:4",
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
      "name": "local_40",
      "storage": "Stack[-0x40]:4",
      "type": "undefined4"
    },
    {
      "name": "local_44",
      "storage": "Stack[-0x44]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 7,
  "mode": "live",
  "name": "FUN_00d06920",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x906920",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00d06920(void)",
  "size_bytes": 289,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00d06920",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 3,
  "xrefs": [
    {
      "from": "00fe9fea"
    },
    {
      "from": "0102f03f"
    },
    {
      "from": "0102ceac"
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
  "file": "src/reconstruction/pkg13_diplomacy_transitions/diplomacy_transitions.cpp",
  "files": [
    "reconstruction/staging/pkg13-diplomacy-transitions/diplomacy_transitions.cpp",
    "reconstruction/staging/pkg13-diplomacy-transitions/diplomacy_transitions.hpp",
    "reconstruction/staging/pkg13-diplomacy-transitions/diplomacy_transitions_model_test.cpp",
    "src/reconstruction/pkg13_diplomacy_transitions/diplomacy_transitions.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-source-wave5/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg13-diplomacy-transitions/00d06920.json"
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
    "gate-diplomacy-transition-00d06920"
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
  "DiplomacyTransitionPorts",
  "OpaqueCurrentRoot",
  "OpaqueCurrentRoot*",
  "OpaqueEventFactory",
  "OpaqueEventFactory*",
  "OpaqueEventRecord",
  "OpaqueEventRecord*",
  "OpaqueRelationshipEntry",
  "OpaqueRelationshipManager",
  "OpaqueRelationshipManager*",
  "OpaqueRelationshipMap",
  "OpaqueTransitionRecord",
  "OpaqueTransitionRecord*",
  "OpaqueWord",
  "void"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x00000000"
]
```

## Conflicts

```json
[
  {
    "anchors": [
      "0x00d01e30",
      "0x00d01e30",
      "0x00d038e0",
      "0x00d038e0",
      "0x00d05830",
      "0x00d05830",
      "0x00d06270",
      "0x00d06270",
      "0x00d065a0",
      "0x00d065a0",
      "0x00d06920",
      "0x00d06920",
      "0x00596da0"
    ],
    "conflict_id": "U-E001",
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
      "0x00be2590",
      "0x00be2590",
      "0x00d01e30",
      "0x00d01e30",
      "0x00d038e0",
      "0x00d038e0",
      "0x00d05830",
      "0x00d05830",
      "0x00d06270",
      "0x00d06270",
      "0x00d065a0",
      "0x00d065a0",
      "0x00d06920",
      "0x00d06920"
    ],
    "conflict_id": "U-E002",
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
      "0x00d01e30",
      "0x00d01e30",
      "0x00d038e0",
      "0x00d038e0",
      "0x00d05830",
      "0x00d05830",
      "0x00d06270",
      "0x00d06270",
      "0x00d065a0",
      "0x00d065a0",
      "0x00d06920",
      "0x00d06920",
      "0x01037d30",
      "0x010535e0",
      "0x010535f0"
    ],
    "conflict_id": "U-E003",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  }
]
```
