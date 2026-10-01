# Evidence 0x00aeb160

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `4c669a4a5458e4d0d1b10af269112b78c3bfb2d5813718513a490ef691e9e241`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "__thiscall",
  "receiver": {
    "register": "ECX",
    "type": "cCommManager*",
    "width_bytes": 4
  },
  "return_register": "EAX",
  "return_type": "cCommEvent*",
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "payload0",
      "position": 1,
      "type": "OpaqueWord"
    },
    {
      "entry_offset": "ESP+0x08",
      "name": "payload1",
      "position": 2,
      "type": "OpaqueWord"
    },
    {
      "entry_offset": "ESP+0x0c",
      "name": "payload2",
      "position": 3,
      "type": "OpaqueWord"
    },
    {
      "entry_offset": "ESP+0x10",
      "name": "payload3",
      "position": 4,
      "type": "OpaqueWord"
    },
    {
      "entry_offset": "ESP+0x14",
      "name": "payload4",
      "position": 5,
      "type": "OpaqueWord"
    },
    {
      "entry_offset": "ESP+0x18",
      "name": "payload5",
      "position": 6,
      "type": "OpaqueWord"
    },
    {
      "entry_offset": "ESP+0x1c",
      "name": "payload6",
      "position": 7,
      "type": "OpaqueWord"
    }
  ],
  "stack_cleanup_bytes": 28,
  "termination": "RET 0x1c"
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
    "calling_convention": "__thiscall",
    "hidden_this": true,
    "hidden_this_register": "ECX",
    "ordinary_stack_argument_slots": [
      "entry_ESP+0x4",
      "entry_ESP+0x8",
      "entry_ESP+0xc",
      "entry_ESP+0x10",
      "entry_ESP+0x14",
      "entry_ESP+0x18",
      "entry_ESP+0x1c"
    ],
    "ordinary_stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": true,
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
        "entry_offset": "entry_ESP+0x14",
        "observed": true,
        "ordinal": 5,
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
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x1c",
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
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
        "size_inferred": true,
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
        "entry_offset": "entry_ESP+0x14",
        "observed": true,
        "ordinal": 5,
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
    "stack_cleanup_bytes": 28,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x1c"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +8, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
    "sret_vs_out_param: entry slot 0 is written through a pointer"
  ],
  "cleanup": {
    "bytes": 28,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x1c",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "b4d36d505c528781aea3761c7e6c3ef7b51092c595ae843faad09dcd366b475b",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall"
    ],
    "confidence": "SUPPORTED",
    "corroboration": "persisted_agrees"
  },
  "cross_validation": {
    "agreement": true,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 0,
    "persisted": "agrees",
    "persisted_calling_convention": "__thiscall"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 5,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0043"
      ],
      "claim": "the callee pops 28 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 28,
        "side": "callee"
      }
    },
    {
      "based_on": [
        "obs-0015",
        "obs-0017",
        "obs-0018",
        "obs-0020",
        "obs-0022",
        "obs-0027",
        "obs-0028",
        "obs-0029",
        "obs-0035"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 7,
        "total_bytes": 28
      }
    },
    {
      "based_on": [
      
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "FUN_00aea250",
    "reconstructed": true,
    "va": "0x00aea250"
  },
  {
    "name": "FUN_00aea5d0",
    "reconstructed": true,
    "va": "0x00aea5d0"
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
    "va": "0x00aeb3e0"
  },
  {
    "name": "Simulator_cCommManager_CreateAndDispatchEvent_00aeb720",
    "reconstructed": true,
    "va": "0x00aeb720"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00aeb7b0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00aebc10"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00aed2c0"
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
      "0x00aeb160",
      "0x00aebe90",
      "0x00aed2c0",
      "0x00c75520",
      "0x00dd5160",
      "0x0102c9e0",
      "0x0102caa0",
      "0x0102cae0",
      "0x0102cc30",
      "0x0102cd90",
      "0x0102ce30",
      "0x0102cf10",
      "0x0102d1b0",
      "0x0102df20",
      "0x01072d40",
      "0x00aeb730"
    ],
    "conflict_id": "LC-006",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "RESOLVED_SUPPORTED",
    "resolution_status": "RESOLVED_SUPPORTED",
    "source": "knowledgegraph/research/conflicts/track-a-type-signature.json",
    "subject": "0x00AEB720 communication wrapper",
    "unresolved_reason": "The exact private wrapper name and the full parameter types are not recoverable from static naming alone; the create-and-dispatch contract is resolved."
  },
  {
    "anchors": [
      "0x00aeb160",
      "0x00aeb7b0",
      "0x00aebe90",
      "0x00aeb160",
      "0x00aebe90",
      "0x00aeb7b0"
    ],
    "conflict_id": "Q-COMM-CODEC",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "cCommEvent allocation, list append, and current-event publication are concrete. Versioned codec/defaulting/vector round-trip semantics remain unresolved.",
    "resolution_status": "cCommEvent allocation, list append, and current-event publication are concrete. Versioned codec/defaulting/vector round-trip semantics remain unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00aeb160",
      "0x00aebe90",
      "0x00aeb160",
      "0x00aebe90",
      "0x00aeb0e0",
      "0x00aeb0e0",
      "0x00aeb1c0",
      "0x00aeb1c0",
      "0x00aebe10",
      "0x00aebe10",
      "0x00e62340",
      "0x00e62340"
    ],
    "conflict_id": "Q-DEFERRED-OWNER",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The record shape and trigger-time surface are not enough to identify the owner or epoch/ordering rules. No deferred-to-immediate equivalence is claimed.",
    "resolution_status": "The record shape and trigger-time surface are not enough to identify the owner or epoch/ordering rules. No deferred-to-immediate equivalence is claimed.",
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
      "0x00aeb160",
      "0x00aeb7b0",
      "0x00aebe90",
      "0x00aeb160",
      "0x00aebe90",
      "0x00aeb7b0",
      "0x00aeb7b0",
      "0x005737d0",
      "0x005737d0",
      "0x00576c50",
      "0x00576c50",
      "0x00582fe0",
      "0x00582fe0",
      "0x00584300",
      "0x00584300",
      "0x00585d10"
    ],
    "conflict_id": "U-007-communication-completion",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "Creation appends to cCommManager+0x20 and ShowCommEvent stores +0x1c before processing. Removal/clear and completion ordering are unresolved.",
    "resolution_status": "Creation appends to cCommManager+0x20 and ShowCommEvent stores +0x1c before processing. Removal/clear and completion ordering are unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00aeb160",
      "0x00aebe90",
      "0x00aeb160",
      "0x00aebe90",
      "0x00f47b10",
      "0x00e552f0",
      "0x00e552f0",
      "0x00e7fc00",
      "0x00e7fc00",
      "0x00e80980",
      "0x00e80980",
      "0x00e81cf0",
      "0x00e81cf0",
      "0x00e81f30",
      "0x00e81f30",
      "0x00f47930"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/temporal-semantics.json:4",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "Deferred trigger and owner/order semantics are not recovered; no immediate dispatch equivalence is claimed.",
    "resolution_status": "Deferred trigger and owner/order semantics are not recovered; no immediate dispatch equivalence is claimed.",
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
  "count": 87,
  "instructions": [
    {
      "address": "00aeb160",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00aeb161",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00aeb162",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00aeb163",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00aeb164",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00aeb166",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00aeb168",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00aeb16a",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00aeb16c",
      "instruction": "PUSH 0x13f09b4"
    },
    {
      "address": "00aeb171",
      "instruction": "PUSH 0xa0"
    },
    {
      "address": "00aeb176",
      "instruction": "MOV EBP,ECX"
    },
    {
      "address": "00aeb178",
      "instruction": "CALL 0x00f473a0"
    },
    {
      "address": "00aeb17d",
      "instruction": "ADD ESP,0x18"
    },
    {
      "address": "00aeb180",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00aeb182",
      "instruction": "JZ 0x00aeb18f"
    },
    {
      "address": "00aeb184",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00aeb186",
      "instruction": "CALL 0x00aea250"
    },
    {
      "address": "00aeb18b",
      "instruction": "MOV ESI,EAX"
    },
    {
      "address": "00aeb18d",
      "instruction": "JMP 0x00aeb191"
    },
    {
      "address": "00aeb18f",
      "instruction": "XOR ESI,ESI"
    },
    {
      "address": "00aeb191",
      "instruction": "MOV EAX,dword ptr [ESP + 0x14]"
    },
    {
      "address": "00aeb195",
      "instruction": "MOV ECX,dword ptr [ESP + 0x18]"
    },
    {
      "address": "00aeb199",
      "instruction": "MOV EDX,dword ptr [ESP + 0x1c]"
    },
    {
      "address": "00aeb19d",
      "instruction": "MOV EBX,dword ptr [ESP + 0x24]"
    },
    {
      "address": "00aeb1a1",
      "instruction": "MOV dword ptr [ESI + 0x18],EAX"
    },
    {
      "address": "00aeb1a4",
      "instruction": "MOV EAX,dword ptr [ESP + 0x20]"
    },
    {
      "address": "00aeb1a8",
      "instruction": "MOV dword ptr [ESI + 0xc],0x0"
    },
    {
      "address": "00aeb1af",
      "instruction": "MOV dword ptr [ESI + 0x34],ECX"
    },
    {
      "address": "00aeb1b2",
      "instruction": "MOV dword ptr [ESI + 0x38],EDX"
    },
    {
      "address": "00aeb1b5",
      "instruction": "MOV dword ptr [ESI + 0x3c],EAX"
    },
    {
      "address": "00aeb1b8",
      "instruction": "MOV EDI,dword ptr [ESI + 0x40]"
    },
    {
      "address": "00aeb1bb",
      "instruction": "CMP EBX,EDI"
    },
    {
      "address": "00aeb1bd",
      "instruction": "JZ 0x00aeb1db"
    },
    {
      "address": "00aeb1bf",
      "instruction": "TEST EBX,EBX"
    },
    {
      "address": "00aeb1c1",
      "instruction": "JZ 0x00aeb1cb"
    },
    {
      "address": "00aeb1c3",
      "instruction": "MOV EDX,dword ptr [EBX]"
    },
    {
      "address": "00aeb1c5",
      "instruction": "MOV EAX,dword ptr [EDX]"
    },
    {
      "address": "00aeb1c7",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "00aeb1c9",
      "instruction": "CALL EAX"
    },
    {
      "address": "00aeb1cb",
      "instruction": "MOV dword ptr [ESI + 0x40],EBX"
    },
    {
      "address": "00aeb1ce",
      "instruction": "TEST EDI,EDI"
    },
    {
      "address": "00aeb1d0",
      "instruction": "JZ 0x00aeb1db"
    },
    {
      "address": "00aeb1d2",
      "instruction": "MOV EDX,dword ptr [EDI]"
    },
    {
      "address": "00aeb1d4",
      "instruction": "MOV EAX,dword ptr [EDX + 0x4]"
    },
    {
      "address": "00aeb1d7",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00aeb1d9",
      "instruction": "CALL EAX"
    },
    {
      "address": "00aeb1db",
      "instruction": "MOV ECX,dword ptr [ESP + 0x28]"
    },
    {
      "address": "00aeb1df",
      "instruction": "MOV EDX,dword ptr [ESP + 0x2c]"
    },
    {
      "address": "00aeb1e3",
      "instruction": "MOV dword ptr [ESI + 0x44],ECX"
    },
    {
      "address": "00aeb1e6",
      "instruction": "MOV dword ptr [ESI + 0x48],EDX"
    },
    {
      "address": "00aeb1e9",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "00aeb1eb",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00aeb1ed",
      "instruction": "MOV EDI,ESI"
    },
    {
      "address": "00aeb1ef",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00aeb1f1",
      "instruction": "MOV dword ptr [ESP + 0x14],EDI"
    },
    {
      "address": "00aeb1f5",
      "instruction": "CALL EDX"
    },
    {
      "address": "00aeb1f7",
      "instruction": "MOV EAX,dword ptr [EBP + 0x28]"
    },
    {
      "address": "00aeb1fa",
      "instruction": "CMP EAX,dword ptr [EBP + 0x2c]"
    },
    {
      "address": "00aeb1fd",
      "instruction": "LEA ECX,[EBP + 0x24]"
    },
    {
      "address": "00aeb200",
      "instruction": "JNC 0x00aeb218"
    },
    {
      "address": "00aeb202",
      "instruction": "LEA EDX,[EAX + 0x4]"
    },
    {
      "address": "00aeb205",
      "instruction": "MOV dword ptr [ECX + 0x4],EDX"
    },
    {
      "address": "00aeb208",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00aeb20a",
      "instruction": "JZ 0x00aeb227"
    },
    {
      "address": "00aeb20c",
      "instruction": "MOV dword ptr [EAX],ESI"
    },
    {
      "address": "00aeb20e",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "00aeb210",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00aeb212",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00aeb214",
      "instruction": "CALL EDX"
    },
    {
      "address": "00aeb216",
      "instruction": "JMP 0x00aeb227"
    },
    {
      "address": "00aeb218",
      "instruction": "LEA EDX,[E
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
  "original_bytes": 9156,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"__thiscall\",\n    \"receiver\": {\n      \"register\": \"ECX\",\n      \"type\": \"cCommManager*\",\n      \"width_bytes\": 4\n    },\n    \"return_register\": \"EAX\",\n    \"return_type\": \"cCommEvent*\",\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"name\": \"payload0\",\n        \"position\": 1,\n        \"type\": \"OpaqueWord\"\n      },\n      {\n        \"entry_offset\": \"ESP+0x08\",\n        \"name\": \"payload1\",\n        \"position\": 2,\n        \"type\": \"OpaqueWord\"\n      },\n      {\n        \"entry_offset\": \"ESP+0x0c\",\n        \"name\": \"payload2\",\n        \"position\": 3,\n        \"type\": \"OpaqueWord\"\n      },\n      {\n        \"entry_offset\": \"ESP+0x10\",\n        \"name\": \"payload3\",\n        \"position\": 4,\n        \"type\": \"OpaqueWord\"\n      },\n      {\n        \"entry_offset\": \"ESP+0x14\",\n        \"name\": \"payload4\",\n        \"position\": 5,\n        \"type\": \"OpaqueWord\"\n      },\n      {\n        \"entry_offset\": \"ESP+0x18\",\n        \"name\": \"payload5\",\n        \"position\": 6,\n        \"type\": \"OpaqueWord\"\n      },\n      {\n        \"entry_offset\": \"ESP+0x1c\",\n        \"name\": \"payload6\",\n        \"position\": 7,\n        \"type\": \"OpaqueWord\"\n      }\n    ],\n    \"stack_cleanup_bytes\": 28,\n    \"termination\": \"RET 0x1c\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaquePayloadWord,cCommEvent,cCommManager,cCommManager*\",\n        \"same_calling_convention\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 33,\n      \"symbol\": \"Simulator_cCommManager_CreateAndDispatchEvent_00aeb720\",\n      \"va\": \"0x00aeb720\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:cCommManager,cCommManager*\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 27,\n      \"symbol\": \"FUN_00aea230\",\n      \"va\": \"0x00aea230\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:cCommEvent,cCommVector\",\n        \"same_calling_convention\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 25,\n      \"symbol\": \"FUN_00aea5d0\",\n      \"va\": \"0x00aea5d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:cCommEvent,cCommEvent*\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 23,\n      \"symbol\": \"FUN_00aea250\",\n      \"va\": \"0x00aea250\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 10,\n      \"symbol\": \"cSpaceInventoryItem_ctor_00c877f0\",\n      \"va\": \"0x00c877f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 8,\n      \"symbol\": \"pkg12_space_00de9fc0\",\n      \"va\": \"0x00de9fc0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 8,\n      \"symbol\": \"pkg12_space_01021300\",\n      \"va\": \"0x01021300\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 8,\n      \"symbol\": \"FUN_0102d1b0\",\n      \"va\": \"0x0102d1b0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [\n    \"The original allocation-failure path is a null dereference rather than a null-return contract.\",\n    \"The target vtable implementations are not reconstructed; refcount calls are staged as opaque hooks.\"\n  ],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"cCommManager\",\n  \"cluster\": null,\n  \"confidence\": 0.94,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"FUN_00aea250\",\n        \"reconstructed\": true,\n        \"va\": \"0x00aea250\"\n      },\n      {\n        \"name\": \"FUN_00aea5d0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00aea5d0\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00aeb3e0\"\n      },\n      {\n        \"name\": \"Simulator_cCommManager_CreateAndDispatchEvent_00aeb720\",\n        \"reconstructed\": true,\n        \"va\": \"0x00aeb720\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00aeb7b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00aebc10\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00aed2c0\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00aeb405\",\n        \"direction\": \"in\",\n        \"other\": \"0x00aeb3e0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00aeb745\",\n        \"direction\": \"in\",\n        \"other\": \"0x00aeb720\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00aeb83d\",\n        \"direction\": \"in\",\n        \"other\": \"0x00aeb7b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00aebc80\",\n        \
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
  "body_end": "00aeb23c",
  "body_span_bytes": 221,
  "body_start": "00aeb160",
  "callees": [
    "FUN_00aea5d0",
    "FUN_00f473a0",
    "FUN_00aea250"
  ],
  "callers": [
    "FUN_00aeb3e0",
    "FUN_00aebc10",
    "FUN_00aeb7b0",
    "FUN_00aed2c0",
    "j_Sim_cCommManager_CreateSpaceCommEvent"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00aeb160",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00aeb160",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x6eb160",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00aeb160(void)",
  "size_bytes": 221,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00aeb160",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 6,
  "xrefs": [
    {
      "from": "00aeb405"
    },
    {
      "from": "00aeb83d"
    },
    {
      "from": "00aeb745"
    },
    {
      "from": "00aeb7a0"
    },
    {
      "from": "00aebc80"
    },
    {
      "from": "00aed30f"
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
  "file": "src/reconstruction/pkg12_space/space_comm_event_lifecycle.cpp",
  "files": [
    "reconstruction/staging/pkg12-space/space_comm_event_lifecycle.cpp",
    "reconstruction/staging/pkg12-space/space_comm_event_lifecycle.hpp",
    "reconstruction/staging/pkg12-space/space_comm_event_lifecycle_model_test.cpp",
    "src/reconstruction/pkg12_space/space_comm_event_lifecycle.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-source-wave3/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg12-space/00aeb160.json"
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
    "gate-space-comm-event-lifecycle"
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
  "OpaquePayloadWord",
  "OpaqueWord",
  "cCommEvent",
  "cCommEvent*",
  "cCommManager",
  "cCommManager*",
  "cCommVector"
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
      "0x00aeb160",
      "0x00aebe90",
      "0x00aed2c0",
      "0x00c75520",
      "0x00dd5160",
      "0x0102c9e0",
      "0x0102caa0",
      "0x0102cae0",
      "0x0102cc30",
      "0x0102cd90",
      "0x0102ce30",
      "0x0102cf10",
      "0x0102d1b0",
      "0x0102df20",
      "0x01072d40",
      "0x00aeb730"
    ],
    "conflict_id": "LC-006",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "RESOLVED_SUPPORTED",
    "resolution_status": "RESOLVED_SUPPORTED",
    "source": "knowledgegraph/research/conflicts/track-a-type-signature.json",
    "subject": "0x00AEB720 communication wrapper",
    "unresolved_reason": "The exact private wrapper name and the full parameter types are not recoverable from static naming alone; the create-and-dispatch contract is resolved."
  },
  {
    "anchors": [
      "0x00aeb160",
      "0x00aeb7b0",
      "0x00aebe90",
      "0x00aeb160",
      "0x00aebe90",
      "0x00aeb7b0"
    ],
    "conflict_id": "Q-COMM-CODEC",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "cCommEvent allocation, list append, and current-event publication are concrete. Versioned codec/defaulting/vector round-trip semantics remain unresolved.",
    "resolution_status": "cCommEvent allocation, list append, and current-event publication are concrete. Versioned codec/defaulting/vector round-trip semantics remain unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00aeb160",
      "0x00aebe90",
      "0x00aeb160",
      "0x00aebe90",
      "0x00aeb0e0",
      "0x00aeb0e0",
      "0x00aeb1c0",
      "0x00aeb1c0",
      "0x00aebe10",
      "0x00aebe10",
      "0x00e62340",
      "0x00e62340"
    ],
    "conflict_id": "Q-DEFERRED-OWNER",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The record shape and trigger-time surface are not enough to identify the owner or epoch/ordering rules. No deferred-to-immediate equivalence is claimed.",
    "resolution_status": "The record shape and trigger-time surface are not enough to identify the owner or epoch/ordering rules. No deferred-to-immediate equivalence is claimed.",
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
      "0x00aeb160",
      "0x00aeb7b0",
      "0x00aebe90",
      "0x00aeb160",
      "0x00aebe90",
      "0x00aeb7b0",
      "0x00aeb7b0",
      "0x005737d0",
      "0x005737d0",
      "0x00576c50",
      "0x00576c50",
      "0x00582fe0",
      "0x00582fe0",
      "0x00584300",
      "0x00584300",
      "0x00585d10"
    ],
    "conflict_id": "U-007-communication-completion",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "Creation appends to cCommManager+0x20 and ShowCommEvent stores +0x1c before processing. Removal/clear and completion ordering are unresolved.",
    "resolution_status": "Creation appends to cCommManager+0x20 and ShowCommEvent stores +0x1c before processing. Removal/clear and completion ordering are unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00aeb160",
      "0x00aebe90",
      "0x00aeb160",
      "0x00aebe90",
      "0x00f47b10",
      "0x00e552f0",
      "0x00e552f0",
      "0x00e7fc00",
      "0x00e7fc00",
      "0x00e80980",
      "0x00e80980",
      "0x00e81cf0",
      "0x00e81cf0",
      "0x00e81f30",
      "0x00e81f30",
      "0x00f47930"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/temporal-semantics.json:4",
    "kind": "conflict_ledge
[TRUNCATED]
```
