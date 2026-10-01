# Evidence 0x00e7fc00

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `d90d4adef673eb28ade9d201483c5df42c2a00531862549fe196bf36ebe3daba`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_receiver": "ECX OpaqueMode* mode",
  "hidden_this_register": "ECX",
  "hidden_this_type": "App::cCellModeStrategy*",
  "ordinary_stack_argument_slots": 0,
  "ret_form": "plain RET",
  "return_type": "void",
  "stack_cleanup_bytes": 0
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
    "return_register": "ST0",
    "return_semantics": "float_or_x87_in_ST0",
    "saved_registers": [
      "EDI"
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +16, so the listing is not one path",
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
  "content_sha256": "c04a43b811788c03c50b9d6e64082717f152f52a0aeac430e6efbf488f1a2231",
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
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0029"
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
        "obs-0028"
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
        "obs-0029"
      ],
      "claim": "calling convention is __thiscall: 0x00e7fc00 is slot 9 of the vptr-backed vftable at 0x01485550, so it is a virtual member of some class; the callee pops nothing and no stack word is read as an argument, so the receiver is in a register, and ECX is the only one that carries one",
      "confidence": "INFERRED",
      "id": "V1-VFT",
      "value": {
        "cleanup_side": "caller",
        "membership_count": 1,
        "receiver_provenance": "vftable_slot",
        "receiver_register": "ECX",
        "slot_index": 9,
        "table": "0x01485550"
      }
    },
    {
      "based_on": [
        "obs-0029"
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
        "obs-0029"
      ],
      "claim": "the return value is carried in ST0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "ST0"
    }
  ],
  "observations": [
    {
      "at": "0x00e7fc00",
      "count": 3,
      "first_use": 0,
      "first_write_index": 3,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00e7fc01",
      "id": "obs-0002",
      "index": 1,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00e53580",
      "target": "0x00e53580"
    },
    {
      "at": "0x00e7fc06",
      "definite": true,
      "id": "obs-0003",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOVSS XMM0,dword ptr [0x016b3bf0]",
      "reg": "XMM0",
      "write_kind": "unknown"
    },
    {
      "at": "0x00e7fc0e",
      "definite": true,
      "id": "obs-0004",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [0x016b3bf8]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00e7fc14",
      "definite": true,
      "id": "obs-0005",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,[0x016b3bfc]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00e7fc19",
      "definite": true,
      "id": "obs-0006",
      "index": 5,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [0x016b3bf4]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00e7fc1f",
      "count": 5,
      "first_use": 6,
      "first_write_index": 2,
      "id": "obs-0007",
      "index": 6,
      "kind": "REG_READ",
      "raw": "MOVSS dword ptr [0x01550adc],XMM0",
      "reg": "XMM0"
    },
    {
      "at": "0x00e7fc6e",
      "count": 8,
      "first_use": 17,
      "first_write_index": 4,
      "id": "obs-0008",
      "index": 17,
      "kind": "REG_READ",
      "raw": "MOV [0x0166c004],EAX",
      "reg": "EAX"
    },
    {
      "at": "0x00e7fc73",
      "count": 4,
      "first_use": 18,
      "first_write_index": 5,
      "id": "obs-0009",
      "index": 18,
      "kind": "REG_READ",
      "raw": "MOV dword ptr [0x01550ad8],EDX",
      "reg": "EDX"
    },
    {
      "at": "0x00e7fc81",
      "id": "obs-0010",
      "index": 20,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00e31100",
      "target": "0x00e31100"
    },
    {
      "at": "0x00e7fc8c",
      "count": 4,
      "first_use": 22,
      "first_write_index": 38,
      "id": "obs-0011",
      "index": 22,
      "kind": "REG_READ",
      "raw": "MOV dword ptr [ESP],EAX",
      "reg": "ESP"
    },
    {
      "at": "0x00e7fc8c",
      "base": "ESP",
      "disp": 0,
      "id": "obs-0012",
      "index": 22,
      "key": null,
      "kind": "STACK_SLOT_WRITE",
      "raw": "MOV dword ptr [ESP],EAX",
      "reason": "local",
      "resolved": false,
      "size": 4,
      "via": "direct"
    },
    {
      "at": "0x00e7fc8f",
      "base"
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "FUN_00e31100",
    "reconstructed": false,
    "va": "0x00e31100"
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
      "0x00e20860",
      "0x00e20860",
      "0x00e20860",
      "0x00e20860",
      "0x00e20860",
      "0x0067dcc0",
      "0x00b3d330",
      "0x00e7fc00",
      "0x00e20860"
    ],
    "conflict_id": "U01",
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
    "resolution": "A positive hash-pinned original-process trace is required; static naming or conceptual state names are not promoted to runtime behavior.",
    "resolution_stat
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
  "count": 60,
  "instructions": [
    {
      "address": "00e7fc00",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00e7fc01",
      "instruction": "CALL 0x00e53580"
    },
    {
      "address": "00e7fc06",
      "instruction": "MOVSS XMM0,dword ptr [0x016b3bf0]"
    },
    {
      "address": "00e7fc0e",
      "instruction": "MOV ECX,dword ptr [0x016b3bf8]"
    },
    {
      "address": "00e7fc14",
      "instruction": "MOV EAX,[0x016b3bfc]"
    },
    {
      "address": "00e7fc19",
      "instruction": "MOV EDX,dword ptr [0x016b3bf4]"
    },
    {
      "address": "00e7fc1f",
      "instruction": "MOVSS dword ptr [0x01550adc],XMM0"
    },
    {
      "address": "00e7fc27",
      "instruction": "MOVSS XMM0,dword ptr [0x016b3bec]"
    },
    {
      "address": "00e7fc2f",
      "instruction": "MOVSS dword ptr [0x01550af0],XMM0"
    },
    {
      "address": "00e7fc37",
      "instruction": "MOVSS XMM0,dword ptr [0x016b3be8]"
    },
    {
      "address": "00e7fc3f",
      "instruction": "MOV dword ptr [0x01550a84],ECX"
    },
    {
      "address": "00e7fc45",
      "instruction": "MOV ECX,dword ptr [0x016b3c04]"
    },
    {
      "address": "00e7fc4b",
      "instruction": "MOVSS dword ptr [0x01550aec],XMM0"
    },
    {
      "address": "00e7fc53",
      "instruction": "MOVSS XMM0,dword ptr [0x016b3be4]"
    },
    {
      "address": "00e7fc5b",
      "instruction": "MOVSS dword ptr [0x01550ae0],XMM0"
    },
    {
      "address": "00e7fc63",
      "instruction": "MOVSS XMM0,dword ptr [0x016b3be0]"
    },
    {
      "address": "00e7fc6b",
      "instruction": "ADD ECX,0x54"
    },
    {
      "address": "00e7fc6e",
      "instruction": "MOV [0x0166c004],EAX"
    },
    {
      "address": "00e7fc73",
      "instruction": "MOV dword ptr [0x01550ad8],EDX"
    },
    {
      "address": "00e7fc79",
      "instruction": "MOVSS dword ptr [0x01550ae4],XMM0"
    },
    {
      "address": "00e7fc81",
      "instruction": "CALL 0x00e31100"
    },
    {
      "address": "00e7fc86",
      "instruction": "MOV ECX,dword ptr [0x016b3c04]"
    },
    {
      "address": "00e7fc8c",
      "instruction": "MOV dword ptr [ESP],EAX"
    },
    {
      "address": "00e7fc8f",
      "instruction": "LEA EAX,[ESP]"
    },
    {
      "address": "00e7fc92",
      "instruction": "ADD ECX,0x54"
    },
    {
      "address": "00e7fc95",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00e7fc96",
      "instruction": "CALL 0x00b72230"
    },
    {
      "address": "00e7fc9b",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00e7fc9d",
      "instruction": "JZ 0x00e7fccc"
    },
    {
      "address": "00e7fc9f",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00e7fca0",
      "instruction": "FLDZ"
    },
    {
      "address": "00e7fca2",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "00e7fca4",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00e7fca6",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00e7fca7",
      "instruction": "MOV EDI,EAX"
    },
    {
      "address": "00e7fca9",
      "instruction": "FSTP float ptr [ESP]"
    },
    {
      "address": "00e7fcac",
      "instruction": "CALL 0x00e7e130"
    },
    {
      "address": "00e7fcb1",
      "instruction": "MOV ECX,dword ptr [0x016b3c04]"
    },
    {
      "address": "00e7fcb7",
      "instruction": "ADD ESP,0xc"
    },
    {
      "address": "00e7fcba",
      "instruction": "LEA EDX,[ESP + 0x4]"
    },
    {
      "address": "00e7fcbe",
      "instruction": "ADD ECX,0x54"
    },
    {
      "address": "00e7fcc1",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00e7fcc2",
      "instruction": "CALL 0x00b72230"
    },
    {
      "address": "00e7fcc7",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00e7fcc9",
      "instruction": "JNZ 0x00e7fca0"
    },
    {
      "address": "00e7fccb",
      "instruction": "POP EDI"
    },
    {
      "address": "00e7fccc",
      "instruction": "MOV ECX,dword ptr [0x016b3c04]"
    },
    {
      "address": "00e7fcd2",
      "instruction": "ADD ECX,0x54"
    },
    {
      "address": "00e7fcd5",
      "instruction": "CALL 0x00b72110"
    },
    {
      "address": "00e7fcda",
      "instruction": "CALL 0x0067ddd0"
    },
    {
      "address": "00e7fcdf",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00e7fce1",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00e7fce3",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00e7fce5",
      "instruction": "MOV EAX,dword ptr [EDX + 0x98]"
    },
    {
      "address": "00e7fceb",
      "instruction": "PUSH 0x7"
    },
    {
      "address": "00e7fced",
      "instruction": "CALL EAX"
    },
    {
      "address": "00e7fcef",
      "instruction": "CALL 0x00e64a00"
    },
    {
      "address": "00e7fcf4",
      "instruction": "CALL 0x00e82d40"
    },
    {
      "address": "00e7fcf9",
      "instruction": "POP ECX"
    },
    {
      "address": "00e7fcfa",
      "instruction": "RET"
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
  "original_bytes": 9629,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_receiver\": \"ECX OpaqueMode* mode\",\n    \"hidden_this_register\": \"ECX\",\n    \"hidden_this_type\": \"App::cCellModeStrategy*\",\n    \"ordinary_stack_argument_slots\": 0,\n    \"ret_form\": \"plain RET\",\n    \"return_type\": \"void\",\n    \"stack_cleanup_bytes\": 0\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"shared_types:DATA\",\n        \"shared_vtable:vtable:0x01485550\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-LIFECYCLE-WAVE8\",\n      \"score\": 9,\n      \"symbol\": \"app_c_cell_mode_strategy_dispose_00e81f30\",\n      \"va\": \"0x00e81f30\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DATA\",\n        \"shared_vtable:vtable:0x01485550\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE7\",\n      \"score\": 7,\n      \"symbol\": \"cell_mode_strategy_on_mouse_move_00e51010\",\n      \"va\": \"0x00e51010\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DATA\",\n        \"shared_vtable:vtable:0x01485550\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE8\",\n      \"score\": 7,\n      \"symbol\": \"cell_mode_strategy_on_mouse_up_00e5c0f0\",\n      \"va\": \"0x00e5c0f0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DATA\",\n        \"shared_vtable:vtable:0x01485550\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE8\",\n      \"score\": 7,\n      \"symbol\": \"cell_mode_strategy_on_mouse_down_00e6c860\",\n      \"va\": \"0x00e6c860\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DATA\",\n        \"shared_vtable:vtable:0x01485550\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE8\",\n      \"score\": 7,\n      \"symbol\": \"cell_mode_strategy_on_mouse_wheel_00e7d660\",\n      \"va\": \"0x00e7d660\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DATA\",\n        \"shared_vtable:vtable:0x01485550\"\n      ],\n      \"package\": \"PKG-FRAME-RUNTIME-WAVE7\",\n      \"score\": 7,\n      \"symbol\": \"cell_mode_update_00e80980\",\n      \"va\": \"0x00e80980\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DATA\",\n        \"shared_vtable:vtable:0x01485550\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE7\",\n      \"score\": 7,\n      \"symbol\": \"cell_mode_strategy_on_key_down_00e818f0\",\n      \"va\": \"0x00e818f0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:OpaqueRecord\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 5,\n      \"symbol\": \"editor_entry_expand_004ad6f0\",\n      \"va\": \"0x004ad6f0\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"The x86-32 thiscall/no-stack/void frame, zero direct callers, one vtable data xref, eight direct callees, exact global copies, iterator lifecycle, service vtable +0x98(7,0), and no direct serializer boundary are observed; runtime reachability, ownership, semantics, and nested helper effects remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_semantic_abi_type_lifecycle_review\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueMode\",\n  \"cluster\": \"app-lifecycle\",\n  \"confidence\": 0.95,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"FUN_00e31100\",\n        \"reconstructed\": false,\n        \"va\": \"0x00e31100\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00e7fcda\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067ddd0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7fcd5\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b72110\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7fc96\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b72230\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7fcc2\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b72230\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7fc81\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e31100\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7fc01\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e53580\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7fcef\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e64a00\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7fcac\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e7e130\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7fcf4\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e82d40\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 1,\n    \"manifest_callees\": [\n      \"0x0067ddd0\",\n      \"0x00b72110\",\n      \"0x00b72230\",\n      \"0x00e31100\",\n      \"0x00e53580\",\n      \"0x00e64a00\",\n      \"0x00e7e130\",\n      \"0x00e82d40\"\n    ],\n    \"manifest_callers\": [\n      \"direct_callers_0\"\n    ],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0555\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"OBSERVED\",\n  \"globals\": [\n    \"global:0x015fd8e8\",\n    \"global:0x016b3be0\",\n    \"global:g_mode_on_exit_globals\"\n  ],\n  \"integration
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
  "body_end": "00e7fcfa",
  "body_span_bytes": 251,
  "body_start": "00e7fc00",
  "callees": [
    "FUN_0067ddd0",
    "FUN_00e53580",
    "FUN_00e64a00",
    "FUN_00e31100",
    "FUN_00b72230",
    "FUN_00e82d40",
    "FUN_00e7e130",
    "FUN_00b72110"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00e7fc00",
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
      "name": "local_14",
      "storage": "Stack[-0x14]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 2,
  "mode": "live",
  "name": "App::cCellModeStrategy::OnExit",
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
  "return_type": "void",
  "return_type_resolved": true,
  "rva": "0xa7fc00",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "void App::cCellModeStrategy::OnExit(cCellModeStrategy * this)",
  "size_bytes": 251,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00e7fc00",
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
      "from": "01485574"
    }
  ]
}
```

## globals

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "global:0x015fd8e8",
  "global:0x016b3be0",
  "global:g_mode_on_exit_globals"
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__cCellModeStrategy__OnExit.c",
  "file": "src/reconstruction/pkg08_cell_mode/mode_on_exit.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__cCellModeStrategy__OnExit.c",
    "reconstruction/staging/pkg08-cell-mode/mode_on_exit.cpp",
    "reconstruction/staging/pkg08-cell-mode/mode_on_exit.hpp",
    "reconstruction/staging/pkg08-cell-mode/mode_on_exit_model_test.cpp",
    "src/reconstruction/pkg08_cell_mode/mode_on_exit.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-pkg08-cell-mode/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg08-cell-mode/00e7fc00.json"
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
    "gate-cell-mode-on-exit"
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
  "App::cCellModeStrategy*",
  "DATA",
  "NativePorts",
  "OpaqueGlobalViews",
  "OpaqueMode",
  "OpaqueRecord",
  "OpaqueService",
  "void"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x00000098",
  "vtable:0x01485550",
  "vtable:0x01485574"
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
      "0x00e20860",
      "0x00e20860",
      "0x00e20860",
      "0x00e20860",
      "0x00e20860",
      "0x0067dcc0",
      "0x00b3d330",
      "0x00e7fc00",
      "0x00e20860"
    ],
    "conflict_id": "U01",
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
    "resolution": "Deferred trigger and owner/order semantics are not recove
[TRUNCATED]
```
