# Evidence 0x00e81f30

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `db728df432ccaae919132b8ff8e2f623cbda29f99da0157fb317b884797ca59e`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_receiver": "ECX OpaqueCellModeStrategy*",
  "ordinary_stack_argument_slots": 0,
  "ret_form": "plain RET",
  "return_register": "AL",
  "return_type": "bool"
}
```

## abi_derived

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function, tools/reconstruction_tooling/vftables.py@25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e`

```json
{
  "abi": {
    "architecture": "x86-32",
    "calling_convention": "__thiscall",
    "ret_form": "RET",
    "return_register": "XMM0",
    "return_semantics": "float_or_x87_in_XMM0",
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
    "flow_not_modelled: the linear ESP walk ends at +76, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
    "receiver_not_determinable: ecx_read_without_deref"
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
  "content_sha256": "78894e8fed095144d6548409d3ae80719a76d7917bfcc027c951df765c69a5bf",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall",
      "__fastcall"
    ],
    "confidence": "SUPPORTED",
    "corroboration": "persisted_agrees"
  },
  "cross_validation": {
    "agreement": true,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 1,
    "persisted": "agrees",
    "persisted_calling_convention": "__thiscall"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 6,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0050"
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
        "obs-0006",
        "obs-0007",
        "obs-0015"
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
        "obs-0050"
      ],
      "claim": "calling convention is __thiscall: 0x00e81f30 is slot 7 of the vptr-backed vftable at 0x01485550, so it is a virtual member of some class; the callee pops nothing and no stack word is read as an argument, so the receiver is in a register, and ECX is the only one that carries one",
      "confidence": "INFERRED",
      "id": "V1-VFT",
      "value": {
        "cleanup_side": "caller",
        "membership_count": 1,
        "receiver_provenance": "vftable_slot",
        "receiver_register": "ECX",
        "slot_index": 7,
        "table": "0x01485550"
      }
    },
    {
      "based_on": [
        "obs-0050"
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
        "obs-0004"
      ],
      "claim": "the return value is carried in XMM0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "XMM0"
    }
  ],
  "observations": [
    {
      "at": "0x00e81f30",
      "definite": true,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,[0x016b3c04]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00e81f35",
      "count": 21,
      "first_use": 1,
      "first_write_index": 0,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "CMP byte ptr [EAX + 0x4121],0x0",
      "reg": "EAX"
    },
    {
      "at": "0x00e81f3c",
      "count": 4,
      "first_use": 2,
      "first_write_index": 4,
      "id": "obs-0003",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH EBP",
      "reg": "EBP"
    },
    {
      "and_esp": null,
      "at": "0x00e81f3c",
      "ebp_is_general_register": true,
      "fp": false,
      "id": "obs-0004",
      "index": 2,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": true,
      "push_ebp_at": 2,
      "raw": "PUSH EBP",
      "sub": null
    },
    {
      "at": "0x00e81f3d",
      "count": 19,
      "first_use": 3,
      "first_write_index": 11,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00e81f3e",
      "count": 6,
      "first_use": 4,
      "first_write_index": 17,
      "id": "obs-0006",
      "index": 4,
      "kind": "REG_READ",
      "raw": "MOV EBP,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00e81f3e",
      "definite": true,
      "id": "obs-0007",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV EBP,ECX",
      "reg": "EBP",
      "write_kind": "reg"
    },
    {
      "at": "0x00e81f42",
      "id": "obs-0008",
      "index": 6,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00e81ba0",
      "target": "0x00e81ba0"
    },
    {
      "at": "0x00e81f47",
      "count": 3,
      "first_use": 7,
      "first_write_index": 10,
      "id": "obs-0009",
      "index": 7,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00e81f48",
      "count": 6,
      "first_use": 8,
      "first_write_index": 9,
      "id": "obs-0010",
      "index": 8,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00e81f49",
      "definite": true,
      "id": "obs-0011",
      "index": 9,
      "kind": "REG_WRITE",
      "raw": "MOV ED
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
    "va": "0x0067dcc0"
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
      "0x00e4ace0",
      "0x00e4cde0",
      "0x00e823a0",
      "0x00e80ba0",
      "0x00e7fc00",
      "0x00e81f30",
      "0x00e4cde0",
      "0x00e4cde0",
      "0x00e4ace0",
      "0x00e4ace0",
      "0x00e80ba0",
      "0x00005190",
      "0x00e80ba0",
      "0x00e80d45",
      "0x00e80f9f",
      "0x00e7fc00"
    ],
    "conflict_id": "TD-DATA-005",
    "kind": "conflict_ledger",
    "rejected": [
      {
        "path": "competing_hypotheses.0.claim",
        "status": "rejected_for_recovered_record_families     ",
        "text": "Direct Cell records are generic CellSerializer name/ID envelopes containing a shared field descriptor table."
      },
      {
        "path": "competing_hypotheses.2.claim",
        "status": "rejected_structural_pointer_is_not_wire_envelope     ",
        "text": "Because cCellResource stores a CellSerializer pointer, every direct Cell record necessarily carries a CellSerializer wire envelope."
      }
    ],
    "resolution": null,
    "resolution_status": null,
    "source": "knowledgegraph/research/conflicts/track-d-data-serialization.json",
    "subject": "Direct Cell records, CellSerializer metadata, cCellDataReference, cCellGame, and cCellSerializableData",
    "unresolved_reason": [
      "Actual cCellSerializableData field emission order and class/object pointer remapping are not recovered.",
      "No original-process save/load trace or byte-level .spo oracle is available."
    ]
  },
  {
    "anchors": [
      "0x00005190",
      "0x00e61550",
      "0x00e61630",
      "0x00e80ba0",
      "0x00e7fc00",
      "0x00e81f30",
      "0x01485598",
      "0x00e61550",
      "0x00e61550",
      "0x00e80ba0",
      "0x00005190",
      "0x00e80ba0",
      "0x00e80d45",
      "0x00e80e17",
      "0x00e81f30",
      "0x00e81f30"
    ],
    "conflict_id": "TD-DATA-008",
    "kind": "conflict_ledger",
    "rejected": [
      {
        "path": "competing_hypotheses.0.claim",
        "status": "rejected_by_layer_and_lifecycle_evidence     ",
        "text": "Every cCellSerializableData field and every cCellGame field is persistent save state because the serializable object is attached to cCellGame+0x5190."
      }
    ],
    "resolution": null,
    "resolution_status": null,
    "source": "knowledgegraph/research/conflicts/track-d-data-serialization.json",
    "subject": "cCellSerializableData persistence candidates versus cCellGame and cache transient state",
    "unresolved_reason": [
      "The actual cCellSerializableData Read/Write vtable targets and field order are not identified.",
      "Cross-stage handoff, reset semantics, telemetry persistence, and synchronization with creature/space progression remain unresolved."
    ]
  },
  {
    "anchors": [
      "0x00e81cf0",
      "0x00e81f30",
      "0x00e81cf0",
      "0x00e81cf0",
      "0x00e81f30",
      "0x00e81cf0",
      "0x00e81f30",
      "0x00e81cf0",
      "0x00e81f30",
      "0x00e81cf0",
      "0x00e81f30"
    ],
    "conflict_id": "U09",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
    "resolution_status": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
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
  },
  {
    "anchors": [
      "0x00e81cf0",
      "0x00e81cf0",
      "0x00e552f0",
      "0x00e552f0",
      "0x00e7fc00",
      "0x00e7fc00",
      "0x00e80980",
      "0x00e80980",
      "0x00e81cf0",
      "0x00e81cf0",
      "0x00e81f30",
      "0x00e81f30"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/temporal-semantics.json:6",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "A positive hash-pinned original-process trace is required; static naming or conceptual state names are not promoted to 
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
  "count": 144,
  "instructions": [
    {
      "address": "00e81f30",
      "instruction": "MOV EAX,[0x016b3c04]"
    },
    {
      "address": "00e81f35",
      "instruction": "CMP byte ptr [EAX + 0x4121],0x0"
    },
    {
      "address": "00e81f3c",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00e81f3d",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00e81f3e",
      "instruction": "MOV EBP,ECX"
    },
    {
      "address": "00e81f40",
      "instruction": "JZ 0x00e81f47"
    },
    {
      "address": "00e81f42",
      "instruction": "CALL 0x00e81ba0"
    },
    {
      "address": "00e81f47",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00e81f48",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00e81f49",
      "instruction": "MOV EDI,dword ptr [0x016b3c04]"
    },
    {
      "address": "00e81f4f",
      "instruction": "MOV EBX,dword ptr [EDI + 0x519c]"
    },
    {
      "address": "00e81f55",
      "instruction": "MOV ESI,dword ptr [EDI + 0x51a0]"
    },
    {
      "address": "00e81f5b",
      "instruction": "ADD EDI,0x519c"
    },
    {
      "address": "00e81f61",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00e81f62",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00e81f63",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00e81f64",
      "instruction": "CALL 0x005f4e10"
    },
    {
      "address": "00e81f69",
      "instruction": "MOV ECX,dword ptr [EDI + 0x4]"
    },
    {
      "address": "00e81f6c",
      "instruction": "ADD ESP,0xc"
    },
    {
      "address": "00e81f6f",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00e81f70",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00e81f71",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00e81f73",
      "instruction": "CALL 0x005f3680"
    },
    {
      "address": "00e81f78",
      "instruction": "SUB ESI,EBX"
    },
    {
      "address": "00e81f7a",
      "instruction": "SAR ESI,0x2"
    },
    {
      "address": "00e81f7d",
      "instruction": "NEG ESI"
    },
    {
      "address": "00e81f7f",
      "instruction": "ADD ESI,ESI"
    },
    {
      "address": "00e81f81",
      "instruction": "ADD ESI,ESI"
    },
    {
      "address": "00e81f83",
      "instruction": "ADD dword ptr [EDI + 0x4],ESI"
    },
    {
      "address": "00e81f86",
      "instruction": "CALL 0x00e4cd50"
    },
    {
      "address": "00e81f8b",
      "instruction": "CALL 0x00e4c9e0"
    },
    {
      "address": "00e81f90",
      "instruction": "MOVSS XMM0,dword ptr [0x016b3bf0]"
    },
    {
      "address": "00e81f98",
      "instruction": "MOV EDX,dword ptr [0x016b3bfc]"
    },
    {
      "address": "00e81f9e",
      "instruction": "MOV EAX,[0x016b3bf8]"
    },
    {
      "address": "00e81fa3",
      "instruction": "MOV ECX,dword ptr [0x016b3bf4]"
    },
    {
      "address": "00e81fa9",
      "instruction": "MOVSS dword ptr [0x01550adc],XMM0"
    },
    {
      "address": "00e81fb1",
      "instruction": "MOVSS XMM0,dword ptr [0x016b3bec]"
    },
    {
      "address": "00e81fb9",
      "instruction": "MOVSS dword ptr [0x01550af0],XMM0"
    },
    {
      "address": "00e81fc1",
      "instruction": "MOVSS XMM0,dword ptr [0x016b3be8]"
    },
    {
      "address": "00e81fc9",
      "instruction": "MOV dword ptr [0x0166c004],EDX"
    },
    {
      "address": "00e81fcf",
      "instruction": "MOV EDX,dword ptr [0x016b3c08]"
    },
    {
      "address": "00e81fd5",
      "instruction": "MOVSS dword ptr [0x01550aec],XMM0"
    },
    {
      "address": "00e81fdd",
      "instruction": "MOVSS XMM0,dword ptr [0x016b3be4]"
    },
    {
      "address": "00e81fe5",
      "instruction": "ADD EDX,0x40"
    },
    {
      "address": "00e81fe8",
      "instruction": "MOVSS dword ptr [0x01550ae0],XMM0"
    },
    {
      "address": "00e81ff0",
      "instruction": "MOVSS XMM0,dword ptr [0x016b3be0]"
    },
    {
      "address": "00e81ff8",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00e81ff9",
      "instruction": "MOV [0x01550a84],EAX"
    },
    {
      "address": "00e81ffe",
      "instruction": "MOV dword ptr [0x01550ad8],ECX"
    },
    {
      "address": "00e82004",
      "instruction": "MOVSS dword ptr [0x01550ae4],XMM0"
    },
    {
      "address": "00e8200c",
      "instruction": "CALL 0x00e83590"
    },
    {
      "address": "00e82011",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "00e82014",
      "instruction": "CALL 0x0067ddd0"
    },
    {
      "address": "00e82019",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00e8201b",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00e8201d",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00e8201f",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00e82021",
      "instruction": "MOV EAX,dword ptr [EDX + 0x88]"
    },
    {
      "address": "00e82027",
      "instruction": "PUSH 0x1010003"
    },
    {
      "address": "00e8202c",
      "instruction": "CALL EAX"
    },
    {
      "address": "00e8202e",
      "instruction": "CALL 0x0067ddd0"
    },
    {
      "address": "00e82033",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00e82035",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00e82037",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00e82039",
      "instruction": "MOV EAX,dword ptr [EDX + 0x98]"
    },
    {
      "address": "00e8203f",
      "instruction": "PUSH 0x7"
    },
    {
      "address": "00e82041",
      "instruction": "CALL EAX"
    },
    {
      "address": "00e82043",
      "instruction": "CALL 0x0067dcc0"
    },
    {
      "address": "00e82048",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00e8204a",
      "instruction": "PUSH 0xffffd8f1"
    },
    {
      "address": "00e8204f",
      "
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
  "original_bytes": 10404,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_receiver\": \"ECX OpaqueCellModeStrategy*\",\n    \"ordinary_stack_argument_slots\": 0,\n    \"ret_form\": \"plain RET\",\n    \"return_register\": \"AL\",\n    \"return_type\": \"bool\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:DATA,OpaqueCellModeStrategy\",\n        \"shared_vtable:vtable:0x01485550\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE8\",\n      \"score\": 15,\n      \"symbol\": \"cell_mode_strategy_on_mouse_up_00e5c0f0\",\n      \"va\": \"0x00e5c0f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:DATA,OpaqueCellModeStrategy\",\n        \"shared_vtable:vtable:0x01485550\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE8\",\n      \"score\": 15,\n      \"symbol\": \"cell_mode_strategy_on_mouse_down_00e6c860\",\n      \"va\": \"0x00e6c860\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:DATA,OpaqueCellModeStrategy\",\n        \"shared_vtable:vtable:0x01485550\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE8\",\n      \"score\": 15,\n      \"symbol\": \"cell_mode_strategy_on_mouse_wheel_00e7d660\",\n      \"va\": \"0x00e7d660\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_types:DATA\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"WAVE6-ENGINE-RUNTIME\",\n      \"score\": 11,\n      \"symbol\": \"app_system_service_gate_dispatch_007e5f30\",\n      \"va\": \"0x007e5f30\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_types:DATA\"\n      ],\n      \"package\": \"PKG-APP-LIFECYCLE-WAVE7\",\n      \"score\": 9,\n      \"symbol\": \"app_capp_system_hook_windows_007e6080\",\n      \"va\": \"0x007e6080\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_types:DATA\"\n      ],\n      \"package\": \"PKG-APP-LIFECYCLE-WAVE7\",\n      \"score\": 9,\n      \"symbol\": \"app_capp_system_set_effect_collection_ids_007e6100\",\n      \"va\": \"0x007e6100\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_types:DATA\"\n      ],\n      \"package\": \"PKG-APP-LIFECYCLE-WAVE7\",\n      \"score\": 9,\n      \"symbol\": \"app_capp_system_func88h_00a6c940\",\n      \"va\": \"0x00a6c940\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DATA\",\n        \"shared_vtable:vtable:0x01485550\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-08-CELL-MODE\",\n      \"score\": 9,\n      \"symbol\": \"cell_mode_on_exit_00e7fc00\",\n      \"va\": \"0x00e7fc00\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Static mechanics and x86-32 ABI reviewed from live Ghidra; runtime values, concrete owners, and unresolved ports remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueCellModeStrategy\",\n  \"cluster\": \"app-lifecycle\",\n  \"confidence\": 0.7,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0067dcc0\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00e81f73\",\n        \"direction\": \"out\",\n        \"other\": \"0x005f3680\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e81f64\",\n        \"direction\": \"out\",\n        \"other\": \"0x005f4e10\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e82043\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067dcc0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e820bb\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067dcc0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e820df\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067dcc0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e82103\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067dcc0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e82014\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067ddd0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e8202e\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067ddd0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e81f8b\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e4c9e0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e81f86\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e4cd50\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e820a2\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e61b00\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e8206e\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e63f90\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e82088\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e64090\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e81f42\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e81ba0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n     
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
  "body_end": "00e82120",
  "body_span_bytes": 497,
  "body_start": "00e81f30",
  "callees": [
    "FUN_00f47380",
    "FUN_00e4cd50",
    "FUN_005f3680",
    "FUN_00e4c9e0",
    "FUN_0067ddd0",
    "FUN_00e83590",
    "FUN_00e63f90",
    "FUN_00e61b00",
    "FUN_00e64090",
    "FUN_005f4e10",
    "App::IAppSystem::Get",
    "FUN_00e81ba0"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00e81f30",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "App::cCellModeStrategy::Dispose",
  "namespace": "App",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 1,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "cCellModeStrategy *"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "bool",
  "return_type_resolved": true,
  "rva": "0xa81f30",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "bool App::cCellModeStrategy::Dispose(cCellModeStrategy * this)",
  "size_bytes": 497,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00e81f30",
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
      "from": "0148556c"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__cCellModeStrategy__Dispose.c",
  "file": "src/reconstruction/pkg_app_lifecycle_wave8/app_lifecycle_wave8.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__cCellModeStrategy__Dispose.c",
    "src/reconstruction/pkg_app_lifecycle_wave8/app_lifecycle_wave8.cpp",
    "src/reconstruction/pkg_app_lifecycle_wave8/app_lifecycle_wave8.hpp",
    "src/reconstruction/pkg_app_lifecycle_wave8/app_lifecycle_wave8_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave8/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-app-lifecycle-wave8/00e81f30.json"
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
  "DATA",
  "OpaqueCellModeStrategy",
  "bool"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x01485550",
  "vtable:0x0148556c"
]
```

## Conflicts

```json
[
  {
    "anchors": [
      "0x00e4ace0",
      "0x00e4cde0",
      "0x00e823a0",
      "0x00e80ba0",
      "0x00e7fc00",
      "0x00e81f30",
      "0x00e4cde0",
      "0x00e4cde0",
      "0x00e4ace0",
      "0x00e4ace0",
      "0x00e80ba0",
      "0x00005190",
      "0x00e80ba0",
      "0x00e80d45",
      "0x00e80f9f",
      "0x00e7fc00"
    ],
    "conflict_id": "TD-DATA-005",
    "kind": "conflict_ledger",
    "rejected": [
      {
        "path": "competing_hypotheses.0.claim",
        "status": "rejected_for_recovered_record_families     ",
        "text": "Direct Cell records are generic CellSerializer name/ID envelopes containing a shared field descriptor table."
      },
      {
        "path": "competing_hypotheses.2.claim",
        "status": "rejected_structural_pointer_is_not_wire_envelope     ",
        "text": "Because cCellResource stores a CellSerializer pointer, every direct Cell record necessarily carries a CellSerializer wire envelope."
      }
    ],
    "resolution": null,
    "resolution_status": null,
    "source": "knowledgegraph/research/conflicts/track-d-data-serialization.json",
    "subject": "Direct Cell records, CellSerializer metadata, cCellDataReference, cCellGame, and cCellSerializableData",
    "unresolved_reason": [
      "Actual cCellSerializableData field emission order and class/object pointer remapping are not recovered.",
      "No original-process save/load trace or byte-level .spo oracle is available."
    ]
  },
  {
    "anchors": [
      "0x00005190",
      "0x00e61550",
      "0x00e61630",
      "0x00e80ba0",
      "0x00e7fc00",
      "0x00e81f30",
      "0x01485598",
      "0x00e61550",
      "0x00e61550",
      "0x00e80ba0",
      "0x00005190",
      "0x00e80ba0",
      "0x00e80d45",
      "0x00e80e17",
      "0x00e81f30",
      "0x00e81f30"
    ],
    "conflict_id": "TD-DATA-008",
    "kind": "conflict_ledger",
    "rejected": [
      {
        "path": "competing_hypotheses.0.claim",
        "status": "rejected_by_layer_and_lifecycle_evidence     ",
        "text": "Every cCellSerializableData field and every cCellGame field is persistent save state because the serializable object is attached to cCellGame+0x5190."
      }
    ],
    "resolution": null,
    "resolution_status": null,
    "source": "knowledgegraph/research/conflicts/track-d-data-serialization.json",
    "subject": "cCellSerializableData persistence candidates versus cCellGame and cache transient state",
    "unresolved_reason": [
      "The actual cCellSerializableData Read/Write vtable targets and field order are not identified.",
      "Cross-stage handoff, reset semantics, telemetry persistence, and synchronization with creature/space progression remain unresolved."
    ]
  },
  {
    "anchors": [
      "0x00e81cf0",
      "0x00e81f30",
      "0x00e81cf0",
      "0x00e81cf0",
      "0x00e81f30",
      "0x00e81cf0",
      "0x00e81f30",
      "0x00e81cf0",
      "0x00e81f30",
      "0x00e81cf0",
      "0x00e81f30"
    ],
    "conflict_id": "U09",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
    "resolution_status": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
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
    "resolution": "Deferred trigger 
[TRUNCATED]
```
