# Evidence 0x00d01e30

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `9e0dfb5de2c7a72cd2abadcdd320d704142f3f0ce75b45e551cfcb59ce2f2ac3`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "thiscall",
  "hidden_this_register": "ECX",
  "hidden_this_type": "OpaqueRelationshipManager*",
  "receiver": "first record",
  "receiver_register": "ECX",
  "return_type": "void",
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
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
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
    "flow_not_modelled: the linear ESP walk ends at +60, so the listing is not one path",
    "unparsed_lines_present: 1 line(s) matched no grammar rule",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
    "receiver_not_determinable: ecx_read_without_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_read_without_deref), and the convention rule that would apply discriminates on receiver absence",
    "sret_vs_out_param: entry slot 0 is written through a pointer"
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
  "content_sha256": "e939d8641476357b02a6e6a4dd7a961aaecae84d8ff2ed14c0dfbf3c5c71c4a8",
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
        "obs-0051"
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
        "obs-0011",
        "obs-0018"
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
        "obs-0007",
        "obs-0008",
        "obs-0021",
        "obs-0041",
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
        "obs-0033",
        "obs-0034",
        "obs-0040",
        "obs-0042"
      ],
      "claim": "EDX is a memory base before any definite write to it",
      "confidence": "OBSERVED",
      "id": "C8-E",
      "value": {
        "register": "EDX"
      }
    },
    {
      "based_on": [
        "obs-0007",
        "obs-0008",
        "obs-0021",
        "obs-0041",
        "obs-0043"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_read_without_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0018"
      ],
      "claim": "a hidden struct-return pointer is a hypothesis only: entry slot 0 is written through a pointer",
      "confidence": "INFERRED",
      "id": "S1",
      "value": {
        "ambiguity": "sret_vs_out_param",
        "present": null,
        "slot": 4
      }
    },
    {
      "based_on": [
        "obs-0051"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0051"
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
      "and_esp": null,
      "at": "0x00d01e30",
      "ebp_is_general_register": true,
      "fp": false,
      "id": "obs-0001",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": true,
      "push_ebp_at": 2,
      "raw": "SUB ESP,0x44",
      "sub": 68
    },
    {
      "at": "0x00d01e
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
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
    "va": "0x010134d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0102cd90"
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
      "0x00d2e480",
      "0x00d2e480",
      "0x00d01410",
      "0x00d01410",
      "0x00d01ab0",
      "0x00d01ab0",
      "0x00d01e30",
      "0x00d01e30",
      "0x00d01f50",
      "0x00d01f50",
      "0x00d01ff0",
      "0x00d01ff0",
      "0x00d038e0",
      "0x00d038e0",
      "0x00d065a0",
      "0x00d065a0"
    ],
    "conflict_id": "U-003-civilization-progression",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The technology-level surface is recorded, but the binary writer/callback chain from one level to the next is not recovered.",
    "resolution_status": "The technology-level surface is recorded, but the binary writer/callback chain from one level to the next is not recovered.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00be34a0",
      "0x00d2e480",
      "0x00d2e480",
      "0x00aeb7b0",
      "0x00aeb160",
      "0x00aeb160",
      "0x00aeb7b0",
      "0x00aeb7b0",
      "0x00aebe90",
      "0x00aebe90",
      "0x00be34a0",
      "0x00d01410",
      "0x00d01410",
      "0x00d01ab0",
      "0x00d01ab0",
      "0x00d01e30"
    ],
    "conflict_id": "U-004-city-buildings",
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
  },
  {
    "anchors": [
      "0x00c3a5a0",
      "0x00c3b630",
      "0x010535e0",
      "0x010535e0",
      "0x00c15e50",
      "0x00c15e50",
      "0x00c38b10",
      "0x00c38b10",
      "0x00d01e30",
      "0x00d01e30",
      "0x00d038e0",
      "0x00d038e0",
      "0x00d05830",
      "0x00d05830",
      "0x00d06270",
      "0x00d06270"
    ],
    "conflict_id": "U-E010",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The cited producer, consumer, or registration surface is retained, but the complete event-to-message mapping, timing, and payload contract remain unresolved.",
    "resolution_status": "The cited producer, consumer, or registration surface is retained, but the complete event-to-message mapping, timing, and payload contract remain unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00d05830",
      "0x00d06270",
      "0x00d05830",
      "0x007d8530",
      "0x007d8530",
      "0x007d8cf0",
      "0x007d8cf0",
      "0x007d8d40",
      "0x007d8d40",
      "0x00b1db60",
      "0x00b1db60",
      "0x00b1dbd0",
      "0x00b1dbd0",
      "0x00d01e30",
      "0x
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
  "count": 80,
  "instructions": [
    {
      "address": "00d01e30",
      "instruction": "SUB ESP,0x44"
    },
    {
      "address": "00d01e33",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00d01e34",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00d01e35",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00d01e36",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00d01e37",
      "instruction": "MOV EBX,ECX"
    },
    {
      "address": "00d01e39",
      "instruction": "CALL 0x01021300"
    },
    {
      "address": "00d01e3e",
      "instruction": "MOV EBP,dword ptr [ESP + 0x5c]"
    },
    {
      "address": "00d01e42",
      "instruction": "TEST EBP,EBP"
    },
    {
      "address": "00d01e44",
      "instruction": "CMOVZ EBP,EAX"
    },
    {
      "address": "00d01e47",
      "instruction": "MOV EDI,dword ptr [EBP + 0x84]"
    },
    {
      "address": "00d01e4d",
      "instruction": "MOV dword ptr [ESP + 0x10],EAX"
    },
    {
      "address": "00d01e51",
      "instruction": "MOV EAX,dword ptr [ESP + 0x58]"
    },
    {
      "address": "00d01e55",
      "instruction": "MOV ESI,dword ptr [EAX + 0x84]"
    },
    {
      "address": "00d01e5b",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00d01e5c",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00d01e5d",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00d01e5e",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00d01e5f",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "00d01e61",
      "instruction": "CALL 0x00d01ab0"
    },
    {
      "address": "00d01e66",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00d01e67",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "00d01e69",
      "instruction": "CALL 0x00d01410"
    },
    {
      "address": "00d01e6e",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00d01e70",
      "instruction": "JZ 0x00d01e76"
    },
    {
      "address": "00d01e72",
      "instruction": "AND dword ptr [EAX + 0x4],0xfffffffd"
    },
    {
      "address": "00d01e76",
      "instruction": "CMP EBP,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00d01e7a",
      "instruction": "JZ 0x00d01e97"
    },
    {
      "address": "00d01e7c",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00d01e7d",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00d01e7e",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00d01e7f",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00d01e80",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "00d01e82",
      "instruction": "CALL 0x00d01ab0"
    },
    {
      "address": "00d01e87",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00d01e88",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "00d01e8a",
      "instruction": "CALL 0x00d01410"
    },
    {
      "address": "00d01e8f",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00d01e91",
      "instruction": "JZ 0x00d01e97"
    },
    {
      "address": "00d01e93",
      "instruction": "AND dword ptr [EAX + 0x4],0xfffffffd"
    },
    {
      "address": "00d01e97",
      "instruction": "MOV ESI,dword ptr [ESP + 0x58]"
    },
    {
      "address": "00d01e9b",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00d01e9c",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00d01e9e",
      "instruction": "CALL 0x00c32830"
    },
    {
      "address": "00d01ea3",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00d01ea4",
      "instruction": "MOV ECX,EBP"
    },
    {
      "address": "00d01ea6",
      "instruction": "CALL 0x00c32830"
    },
    {
      "address": "00d01eab",
      "instruction": "CMP EBP,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00d01eaf",
      "instruction": "JNZ 0x00d01efd"
    },
    {
      "address": "00d01eb1",
      "instruction": "XOR EDI,EDI"
    },
    {
      "address": "00d01eb3",
      "instruction": "MOV dword ptr [ESP + 0x44],EDI"
    },
    {
      "address": "00d01eb7",
      "instruction": "MOV dword ptr [ESP + 0x14],0x13eb90c"
    },
    {
      "address": "00d01ebf",
      "instruction": "XOR ECX,ECX"
    },
    {
      "address": "00d01ec1",
      "instruction": "LEA EDX,[ESP + 0x18]"
    },
    {
      "address": "00d01ec5",
      "instruction": "XCHG dword ptr [EDX],ECX"
    },
    {
      "address": "00d01ec7",
      "instruction": "MOV dword ptr [ESP + 0x14],0x13eb844"
    },
    {
      "address": "00d01ecf",
      "instruction": "MOV dword ptr [ESP + 0x4c],EDI"
    },
    {
      "address": "00d01ed3",
      "instruction": "MOV dword ptr [ESP + 0x1c],ESI"
    },
    {
      "address": "00d01ed7",
      "instruction": "MOV dword ptr [ESP + 0x24],EBP"
    },
    {
      "address": "00d01edb",
      "instruction": "CALL 0x00883860"
    },
    {
      "address": "00d01ee0",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00d01ee2",
      "instruction": "MOV EDX,dword ptr [EDX + 0x14]"
    },
    {
      "address": "00d01ee5",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00d01ee6",
      "instruction": "LEA ECX,[ESP + 0x18]"
    },
    {
      "address": "00d01eea",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00d01eeb",
      "instruction": "PUSH 0x4445d44"
    },
    {
      "address": "00d01ef0",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00d01ef2",
      "instruction": "CALL EDX"
    },
    {
      "address": "00d01ef4",
      "instruction": "LEA ECX,[ESP + 0x14]"
    },
    {
      "address": "00d01ef8",
      "instruction": "CALL 0x00421cf0"
    },
    {
      "address": "00d01efd",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00d01eff",
      "instruction": "CALL 0x00c31c50"
    },
    {
      "addres
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
  "original_bytes": 10144,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"thiscall\",\n    \"hidden_this_register\": \"ECX\",\n    \"hidden_this_type\": \"OpaqueRelationshipManager*\",\n    \"receiver\": \"first record\",\n    \"receiver_register\": \"ECX\",\n    \"return_type\": \"void\",\n    \"stack_arguments\": [\n      {\n        \"name\": \"event_id\",\n        \"position\": 1,\n        \"type\": \"OpaqueWord\"\n      },\n      {\n        \"name\": \"event_pointer\",\n        \"position\": 2,\n        \"type\": \"OpaqueEventRecord*\"\n      },\n      {\n        \"name\": \"zero\",\n        \"position\": 3,\n        \"type\": \"OpaqueWord\"\n      }\n    ],\n    \"stack_cleanup_bytes\": 12,\n    \"termination\": \"RET 0x8\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:DiplomacyTransitionPorts,OpaqueEventFactory,OpaqueEventFactory*,OpaqueEventRecord\",\n        \"shared_vtable:vtable:0x00000000\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-13-SIM-DIPLOMACY-TRANSITIONS\",\n      \"score\": 34,\n      \"symbol\": \"DiplomacyTransition_00d06920\",\n      \"va\": \"0x00d06920\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:DiplomacyTransitionPorts,OpaqueRelationshipEntry,OpaqueRelationshipManager,OpaqueRelationshipManager*\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-13-SIM-DIPLOMACY-TRANSITIONS\",\n      \"score\": 30,\n      \"symbol\": \"DiplomacyTransition_00d038e0\",\n      \"va\": \"0x00d038e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:DiplomacyTransitionPorts,OpaqueRelationshipEntry,OpaqueRelationshipManager,OpaqueRelationshipManager*\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-13-SIM-DIPLOMACY-TRANSITIONS\",\n      \"score\": 30,\n      \"symbol\": \"DiplomacyTransition_00d065a0\",\n      \"va\": \"0x00d065a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:OpaqueRelationshipManager,OpaqueRelationshipMap\",\n        \"same_calling_convention\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-13-SIM-DIPLOMACY-PRIMITIVES\",\n      \"score\": 16,\n      \"symbol\": \"RelationshipMapSelect_00d01ab0\",\n      \"va\": \"0x00d01ab0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:OpaqueRelationshipEntry,OpaqueRelationshipManager,OpaqueRelationshipMap\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-13-SIM-DIPLOMACY-PREDICATE\",\n      \"score\": 16,\n      \"symbol\": \"RelationshipManager_IsAllied2_00d01ff0\",\n      \"va\": \"0x00d01ff0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:OpaqueRelationshipEntry,OpaqueRelationshipMap\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-13-SIM-DIPLOMACY-PRIMITIVES\",\n      \"score\": 9,\n      \"symbol\": \"RelationshipLookup_00d01410\",\n      \"va\": \"0x00d01410\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x00000000\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-13-E2-DIPLOMACY-ALT\",\n      \"score\": 6,\n      \"symbol\": \"RelationshipScoreObjects_00d00d60\",\n      \"va\": \"0x00d00d60\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:OpaqueWord\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 3,\n      \"symbol\": \"re_00575ea0\",\n      \"va\": \"0x00575ea0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [\n    \"All helper, event, relationship, and current-player service types remain opaque.\",\n    \"No original-process trace is available.\"\n  ],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueRelationshipManager\",\n  \"cluster\": null,\n  \"confidence\": 0.92,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"RelationshipLookup_00d01410\",\n        \"reconstructed\": true,\n        \"va\": \"0x00d01410\"\n      },\n      {\n        \"name\": \"RelationshipMapSelect_00d01ab0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00d01ab0\"\n      },\n      {\n        \"name\": \"pkg12_space_01021300\",\n        \"reconstructed\": true,\n        \"va\": \"0x01021300\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x010134d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0102cd90\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x01013577\",\n        \"direction\": \"in\",\n        \"other\": \"0x010134d0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0102cdb6\",\n        \"direction\": \"in\",\n        \"other\": \"0x0102cd90\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00d01ef8\",\n        \"direction\": \"out\",\n        \"other\": \"0x00421cf0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00d01edb\",\n        \"direction\": \"out\",\n        \"other\": \"0x00883860\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00d01eff\",\n        \"direction\": \"out\",\n        \"other\": \"0x00c31c50\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00d01f06\",\n        \"direction\": \"out\",\n        \"other\": \"0
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
  "body_end": "00d01f14",
  "body_span_bytes": 229,
  "body_start": "00d01e30",
  "callees": [
    "FUN_00883860",
    "FUN_00d01410",
    "FUN_00c32830",
    "FUN_01021300",
    "FUN_00d01ab0",
    "FUN_00421cf0",
    "FUN_00c31c50"
  ],
  "callers": [
    "FUN_0102cd90",
    "FUN_010134d0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00d01e30",
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
  "name": "FUN_00d01e30",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x901e30",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00d01e30(void)",
  "size_bytes": 229,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00d01e30",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 2,
  "xrefs": [
    {
      "from": "0102cdb6"
    },
    {
      "from": "01013577"
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
    "reconstruction/metadata/pkg13-diplomacy-transitions/00d01e30.json"
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
    "gate-diplomacy-transition-00d01e30"
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
      "0x00d2e480",
      "0x00d2e480",
      "0x00d01410",
      "0x00d01410",
      "0x00d01ab0",
      "0x00d01ab0",
      "0x00d01e30",
      "0x00d01e30",
      "0x00d01f50",
      "0x00d01f50",
      "0x00d01ff0",
      "0x00d01ff0",
      "0x00d038e0",
      "0x00d038e0",
      "0x00d065a0",
      "0x00d065a0"
    ],
    "conflict_id": "U-003-civilization-progression",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The technology-level surface is recorded, but the binary writer/callback chain from one level to the next is not recovered.",
    "resolution_status": "The technology-level surface is recorded, but the binary writer/callback chain from one level to the next is not recovered.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00be34a0",
      "0x00d2e480",
      "0x00d2e480",
      "0x00aeb7b0",
      "0x00aeb160",
      "0x00aeb160",
      "0x00aeb7b0",
      "0x00aeb7b0",
      "0x00aebe90",
      "0x00aebe90",
      "0x00be34a0",
      "0x00d01410",
      "0x00d01410",
      "0x00d01ab0",
      "0x00d01ab0",
      "0x00d01e30"
    ],
    "conflict_id": "U-004-city-buildings",
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
  },
  {
    "anchors": [
      "0x00c3a5a0",
      "0x00c3b630",
      "0x010535e0",
      "0x010535e0",
      "0x00c15e50",
      "0x00c15e50",
      "0x00c38b10",
      "0x00c38b10",
      "0x00d01e30",
      "0x00d01e30",
      "0x00d038e0",
      "0x00d038e0",
      "0x00d05830",
      "0x00d05830",
      "0x00d06270"
[TRUNCATED]
```
