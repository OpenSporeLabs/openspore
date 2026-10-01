# Evidence 0x00e7a4a0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `1294c5007bcda6db51370023f17c431e764cd8b59a9b46985e45e114d7743867`

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
        "size_inferred": true,
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
          1
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
        "size_inferred": true,
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
          1
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
    "receiver_not_determinable: ecx_read_without_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_read_without_deref), and the convention rule that would apply discriminates on receiver absence",
    "sret_vs_out_param: entry slot 0 is written through a pointer"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate",
    "side": "caller"
  },
  "completeness": "PARTIAL",
  "conflicts": [
    {
      "field": "stack_cleanup_bytes",
      "inferred": 0,
      "kind": "inferred_vs_persisted",
      "persisted": 24,
      "resolution_status": "unresolved"
    }
  ],
  "content_sha256": "bc9ee1f07107e721ac81684a5e123f3603fd19dfb045dec3ec517f65efc1fad5",
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
    "persisted_calling_convention": null
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0021",
        "obs-0062",
        "obs-0065"
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
        "obs-0004",
        "obs-0010",
        "obs-0011",
        "obs-0013",
        "obs-0028",
        "obs-0030",
        "obs-0033",
        "obs-0035",
        "obs-0039",
        "obs-0044",
        "obs-0056"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 0,
        
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
    "name": "Simulator::Cell::GetScaleDifferenceWithPlayer",
    "reconstructed": false,
    "va": "0x00e57340"
  },
  {
    "name": "Simulator::Cell::cCellGFX::InstanceEffectOnCell",
    "reconstructed": false,
    "va": "0x00e66840"
  },
  {
    "name": "Simulator::Cell::PlayAnimation",
    "reconstructed": false,
    "va": "0x00e6d200"
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
    "va": "0x00e7a770"
  },
  {
    "name": "FUN_00e7a7c0",
    "reconstructed": true,
    "va": "0x00e7a7c0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e7b240"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e81120"
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
  },
  {
    "anchors": [
      "0x00d2e490",
      "0x00d2e4a0",
      "0x0169e394",
      "0x00d2e490",
      "0x00e7a4a0",
      "0x00e7a7c0",
      "0x0169e394",
      "0x00d2e490",
      "0x00d2e490",
      "0x00d2e490",
      "0x00d2e4a0",
      "0x00d2e4a0",
      "0x00d2e4a0",
      "0x00e57460",
      "0x00e57460",
      "0x00e7a7c0"
    ],
    "conflict_id": "ability_mode_callers_and_domain",
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
      "0x00e7a4a0",
      "0x00e7a7c0",
      "0x00e7a7c0",
      "0x00e7e6c0",
      "0x00e7a4a0",
      "0x00e7a4a0",
      "0x00e62340",
      "0x00e52910",
      "0x00e7a7c0",
      "0x00e7a7c0",
      "0x00bfc460",
      "0x00bfc460",
      "0x00bfc490",
      "0x00bfc490",
      "0x00bfc4a0",
      "0x00bfc4a0"
    ],
    "conflict_id": "cell_field_112_semantics",
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
      "0x00e52910",
      "0x00e575f0",
      "0x00e52910",
      "0x00e7e6c0",
      "0x00e7a7c0",
      "0x00e7a4a0",
      "0x00e52910",
      "0x00e7a7c0",
      "0x00e72060",
      "0x00e52910",
      "0x00e52910",
      "0x00e52910",
      "0x00e575f0",
      "0x00e575f0",
      "0x00e575f0",
      "0x00e7a4a0"
    ],
    "conflict_id": "cell_target_selector_domain",
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
      "0x00c0bc20",
      "0x00c14aa0",
      "0x00c1f8d0",
      "0x00c1f8d0",
      "0x00e7a7c0",
      "0x00e7a4a0",
      "0x00c0bc20",
      "0x00c0bc20",
      "0x00c0bc20",
      "0x00c0e660",
      "0x00c0e660",
      "0x00c0e680",
      "0x00c0e680",
      "0x00c14aa0",
      "0x00c14aa0",
      "0x00c14aa0"
    ],
    "conflict_id": "creature_ability_bitset_mapping",
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
      "0x00bfc460",
      "0x00bfc540",
      "0x00bfc460",
      "0x00e7e6c0",
      "0x00e7a4a0",
      "0x00e52910",
      "0x00e7a7c0",
      "0x00bfc460",
      "0x00bfc460",
      "0x00bfc490",
      "0x00bfc490",
      "0x00bfc4a0",
      "0x00bfc4a0",
      "0x00bfc540",
      "0x00bfc540",
      "0x00bfc540"
    ],
    "conflict_id": "creature_death_publication",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The cited producer, consumer, or registration surface is retained, but the complete event-to-message mapping, timing, and payload contract remain unresolved.",
    "resolution_status": "The cited producer, consumer, or registration surface is retained, but the complete event-to-message mapping, timing, and payload contract remain unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "
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
  "count": 209,
  "instructions": [
    {
      "address": "00e7a4a0",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00e7a4a1",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00e7a4a2",
      "instruction": "MOV EDI,dword ptr [ESP + 0xc]"
    },
    {
      "address": "00e7a4a6",
      "instruction": "XOR EBX,EBX"
    },
    {
      "address": "00e7a4a8",
      "instruction": "CMP byte ptr [EDI + 0x112],BL"
    },
    {
      "address": "00e7a4ae",
      "instruction": "JNZ 0x00e7a75d"
    },
    {
      "address": "00e7a4b4",
      "instruction": "CMP byte ptr [EDI + 0x113],BL"
    },
    {
      "address": "00e7a4ba",
      "instruction": "JNZ 0x00e7a75d"
    },
    {
      "address": "00e7a4c0",
      "instruction": "MOV EAX,[0x016b3c04]"
    },
    {
      "address": "00e7a4c5",
      "instruction": "MOV ECX,dword ptr [EAX + 0x411c]"
    },
    {
      "address": "00e7a4cb",
      "instruction": "CMP ECX,dword ptr [EDI]"
    },
    {
      "address": "00e7a4cd",
      "instruction": "JNZ 0x00e7a511"
    },
    {
      "address": "00e7a4cf",
      "instruction": "CMP byte ptr [EAX + 0x5169],BL"
    },
    {
      "address": "00e7a4d5",
      "instruction": "JNZ 0x00e7a75d"
    },
    {
      "address": "00e7a4db",
      "instruction": "MOV EAX,dword ptr [EAX + 0x5158]"
    },
    {
      "address": "00e7a4e1",
      "instruction": "CMP EAX,0x5"
    },
    {
      "address": "00e7a4e4",
      "instruction": "JZ 0x00e7a75d"
    },
    {
      "address": "00e7a4ea",
      "instruction": "CMP EAX,0x3"
    },
    {
      "address": "00e7a4ed",
      "instruction": "JZ 0x00e7a75d"
    },
    {
      "address": "00e7a4f3",
      "instruction": "FLD float ptr [ESP + 0x20]"
    },
    {
      "address": "00e7a4f7",
      "instruction": "MOV EDX,dword ptr [ESP + 0x14]"
    },
    {
      "address": "00e7a4fb",
      "instruction": "MOV EAX,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00e7a4ff",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00e7a500",
      "instruction": "FSTP float ptr [ESP]"
    },
    {
      "address": "00e7a503",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00e7a504",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00e7a505",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00e7a506",
      "instruction": "CALL 0x00e72060"
    },
    {
      "address": "00e7a50b",
      "instruction": "ADD ESP,0x10"
    },
    {
      "address": "00e7a50e",
      "instruction": "POP EDI"
    },
    {
      "address": "00e7a50f",
      "instruction": "POP EBX"
    },
    {
      "address": "00e7a510",
      "instruction": "RET"
    },
    {
      "address": "00e7a511",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00e7a512",
      "instruction": "MOV byte ptr [EDI + 0x113],0x1"
    },
    {
      "address": "00e7a519",
      "instruction": "CALL 0x00e57340"
    },
    {
      "address": "00e7a51e",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "00e7a521",
      "instruction": "CMP EAX,0x1"
    },
    {
      "address": "00e7a524",
      "instruction": "JG 0x00e7a543"
    },
    {
      "address": "00e7a526",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "00e7a528",
      "instruction": "PUSH 0x811c9dc5"
    },
    {
      "address": "00e7a52d",
      "instruction": "PUSH 0x14857f0"
    },
    {
      "address": "00e7a532",
      "instruction": "CALL 0x00932e80"
    },
    {
      "address": "00e7a537",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00e7a538",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00e7a539",
      "instruction": "CALL 0x00e66840"
    },
    {
      "address": "00e7a53e",
      "instruction": "ADD ESP,0x14"
    },
    {
      "address": "00e7a541",
      "instruction": "JMP 0x00e7a56c"
    },
    {
      "address": "00e7a543",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00e7a544",
      "instruction": "CALL 0x00e57340"
    },
    {
      "address": "00e7a549",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "00e7a54c",
      "instruction": "CMP EAX,0x3"
    },
    {
      "address": "00e7a54f",
      "instruction": "JL 0x00e7a558"
    },
    {
      "address": "00e7a551",
      "instruction": "PUSH 0x14857d4"
    },
    {
      "address": "00e7a556",
      "instruction": "JMP 0x00e7a55d"
    },
    {
      "address": "00e7a558",
      "instruction": "PUSH 0x14857c0"
    },
    {
      "address": "00e7a55d",
      "instruction": "CALL 0x00571cf0"
    },
    {
      "address": "00e7a562",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00e7a563",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00e7a564",
      "instruction": "CALL 0x00e66840"
    },
    {
      "address": "00e7a569",
      "instruction": "ADD ESP,0xc"
    },
    {
      "address": "00e7a56c",
      "instruction": "MOV ECX,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00e7a570",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00e7a571",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00e7a572",
      "instruction": "CALL 0x00e71f00"
    },
    {
      "address": "00e7a577",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "00e7a57a",
      "instruction": "CMP byte ptr [ESP + 0x18],BL"
    },
    {
      "address": "00e7a57e",
      "instruction": "JZ 0x00e7a594"
    },
    {
      "address": "00e7a580",
      "instruction": "CALL 0x00e514c0"
    },
    {
      "address": "00e7a585",
      "instruction": "MOV EDX,dword ptr [0x016b3c04]"
    },
    {
      "address": "00e7a58b",
      "instruction": "MOV EAX,dword ptr [EDX + 0x5190]"
    },
    {
      "address": "00e7a591",
      "instruction": "INC dword ptr [EAX + 0x6c]"
    },
    {
      "address": "00e7a594",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00e7a595",
      "instruction": "CMP dword ptr [EDI + 0x358],EBX"
    }
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
  "original_bytes": 22453,
  "preview": "{\n  \"abi\": {\n    \"stack_cleanup_bytes\": 24\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:CellObjectData,CellObjectData*,CellResourceRef\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-06-CELL-STATE\",\n      \"score\": 31,\n      \"symbol\": \"FUN_00e7a7c0\",\n      \"va\": \"0x00e7a7c0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:CellObjectData,CellResourceRef,OpaqueResourceScope\"\n      ],\n      \"package\": \"PKG-06-CELL-STATE\",\n      \"score\": 28,\n      \"symbol\": \"FUN_00e780a0\",\n      \"va\": \"0x00e780a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:CellObjectData,CellResourceRef,OpaqueResourceScope\"\n      ],\n      \"package\": \"PKG-06-CELL-STATE\",\n      \"score\": 23,\n      \"symbol\": \"FUN_00e7fd00\",\n      \"va\": \"0x00e7fd00\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-06A-CELL-AI-SELECTION\",\n      \"score\": 6,\n      \"symbol\": \"cell_ai_select_profile_00e52910\",\n      \"va\": \"0x00e52910\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-11-H3-HELPER-WAVE2\",\n      \"score\": 3,\n      \"symbol\": \"embedded_object_first_word_init_00743b50\",\n      \"va\": \"0x00743b50\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Static removal/death mechanics accepted; five-argument meaning, scale inputs, resources, effects, and vtable subtypes remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"CellObjectData\",\n  \"cluster\": null,\n  \"confidence\": 0.62,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"embedded_object_first_word_init_00743b50\",\n        \"reconstructed\": true,\n        \"va\": \"0x00743b50\"\n      },\n      {\n        \"name\": \"Simulator::Cell::GetScaleDifferenceWithPlayer\",\n        \"reconstructed\": false,\n        \"va\": \"0x00e57340\"\n      },\n      {\n        \"name\": \"Simulator::Cell::cCellGFX::InstanceEffectOnCell\",\n        \"reconstructed\": false,\n        \"va\": \"0x00e66840\"\n      },\n      {\n        \"name\": \"Simulator::Cell::PlayAnimation\",\n        \"reconstructed\": false,\n        \"va\": \"0x00e6d200\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e7a770\"\n      },\n      {\n        \"name\": \"FUN_00e7a7c0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00e7a7c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e7b240\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e81120\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00e7a7ad\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e7a770\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7a8d8\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e7a7c0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7b268\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e7b240\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e81559\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e81120\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7a55d\",\n        \"direction\": \"out\",\n        \"other\": \"0x00571cf0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7a5a5\",\n        \"direction\": \"out\",\n        \"other\": \"0x00743b50\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7a532\",\n        \"direction\": \"out\",\n        \"other\": \"0x00932e80\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7a68f\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b72160\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7a642\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b72210\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7a668\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b72210\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7a69e\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b72210\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7a5b6\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e4cc40\",\n        \"reference_type\": \"thunk\"\n      },\n      {\n        \"callsite\": \"0x00e7a5cf\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e4ee60\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7a580\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e514c0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7a5fc\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e52a40\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7a519\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e57340\",\n        \"reference_t
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
  "body_end": "00e7a761",
  "body_span_bytes": 706,
  "body_start": "00e7a4a0",
  "callees": [
    "FUN_00e771d0",
    "FUN_00e52a40",
    "FUN_00e72060",
    "thunk_FUN_00e823a0",
    "FUN_00e82130",
    "FUN_00571cf0",
    "FUN_00e4ee60",
    "FUN_00932e80",
    "FUN_00b72160",
    "FUN_00b72210",
    "FUN_00e59170",
    "Simulator::Cell::GetScaleDifferenceWithPlayer",
    "FUN_00e514c0",
    "FUN_00e71f00",
    "FUN_00743b50",
    "Simulator::Cell::cCellGFX::InstanceEffectOnCell",
    "Simulator::Cell::PlayAnimation"
  ],
  "callers": [
    "FUN_00e7a770",
    "FUN_00e7a7c0",
    "FUN_00e7b240",
    "FUN_00e81120"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00e7a4a0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
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
      "name": "local_18",
      "storage": "Stack[-0x18]:4",
      "type": "undefined4"
    },
    {
      "name": "local_24",
      "storage": "Stack[-0x24]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 4,
  "mode": "live",
  "name": "FUN_00e7a4a0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xa7a4a0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00e7a4a0(void)",
  "size_bytes": 706,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00e7a4a0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 4,
  "xrefs": [
    {
      "from": "00e7a8d8"
    },
    {
      "from": "00e7a7ad"
    },
    {
      "from": "00e7b268"
    },
    {
      "from": "00e81559"
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
    "reconstruction/metadata/pkg06-cell-state/00e7a4a0.json"
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
    "cell_effect_and_scale_observation"
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
  "original_bytes": 12516,
  "preview": "{\n  \"category\": null,\n  \"classification\": \"NEEDS_RUNTIME\",\n  \"confidence\": {\n    \"overall\": \"SUPPORTED\"\n  },\n  \"contradictions\": [],\n  \"downstream_unlock_count\": 21,\n  \"evidence\": [\n    {\n      \"independent_limit\": \"Killer/resource/flag types are decompiler-inferred.\",\n      \"kind\": \"direct_decompilation\",\n      \"source\": \"Ghidra MCP:SporeApp.exe@0x00e7a4a0\",\n      \"supports\": [\n        \"guards\",\n        \"field_113 write\",\n        \"three death effect names\",\n        \"kill counter increment\",\n        \"type 6 record\",\n        \"animations\",\n        \"scale-aware call\"\n      ]\n    },\n    {\n      \"independent_limit\": \"Same binary source; assembly cross-check only.\",\n      \"kind\": \"disassembly\",\n      \"source\": \"Ghidra MCP:SporeApp.exe@0x00e7a4a0\",\n      \"supports\": [\n        \"player branch at +0x411c\",\n        \"field_112/113 checks\",\n        \"type 6 at record+0x24\",\n        \"mKillCount offset +0x6c\",\n        \"animation immediates 10 and 7\"\n      ]\n    },\n    {\n      \"independent_limit\": \"Static xrefs do not prove event frequency.\",\n      \"kind\": \"callgraph_xrefs\",\n      \"source\": \"Ghidra MCP:SporeApp.exe@xrefs@0x00e7a4a0\",\n      \"supports\": [\n        \"4 direct callers\",\n        \"17 direct callees\",\n        \"death/effect/animation/event fan-out\"\n      ]\n    },\n    {\n      \"independent_limit\": \"Does not prove disk encoding or transaction.\",\n      \"kind\": \"structure_layout\",\n      \"source\": \"Ghidra MCP:SporeApp.exe@structure:cCellSerializableData\",\n      \"supports\": [\n        \"+0x6c is mKillCount\",\n        \"+0x70 is mDeathCount\",\n        \"separate 236-byte object\"\n      ]\n    },\n    {\n      \"independent_limit\": \"Raw type names and payloads remain unresolved.\",\n      \"kind\": \"sibling_event_dispatch\",\n      \"source\": \"Ghidra MCP:SporeApp.exe@0x00e7e130\",\n      \"supports\": [\n        \"type 6 dispatch and release-after-dispatch\",\n        \"type 0x1d separate branch\"\n      ]\n    },\n    {\n      \"independent_limit\": \"Secondary static artifact.\",\n      \"kind\": \"committed_state_machine_artifact\",\n      \"source\": \"knowledgegraph/research/state-machines/cell-stage.json:200-220\",\n      \"supports\": [\n        \"non-player death, player delegation, queued duration record\"\n      ]\n    }\n  ],\n  \"family\": \"cell_death_and_terminal_transition\",\n  \"interfaces\": {\n    \"boundaries\": {\n      \"boundary_rule\": \"The pooled record and render effect are downstream projections; Cell state is authoritative and the kill counter is a separate candidate.\",\n      \"classification\": \"cross_boundary\",\n      \"inbound\": \"Lethal Cell damage or mode action\",\n      \"outbound\": [\n        \"Cell terminal state\",\n        \"AI reaction\",\n        \"serializable kill counter\",\n        \"GFX death effect\",\n        \"animation intent\",\n        \"pooled interaction record\",\n        \"player-death delegate\"\n      ]\n    },\n    \"direct_callees\": [\n      {\n        \"name\": \"Simulator::Cell::GetScaleDifferenceWithPlayer\",\n        \"role\": \"effect/scale classification\",\n        \"va\": \"0x00e57340\"\n      },\n      {\n        \"name\": \"Simulator::Cell::cCellGFX::InstanceEffectOnCell\",\n        \"role\": \"scale-dependent death effect\",\n        \"va\": \"0x00e66840\"\n      },\n      {\n        \"role\": \"nearby same-resource reaction\",\n        \"va\": \"0x00e71f00\"\n      },\n      {\n        \"role\": \"kill/player-progress side effect\",\n        \"va\": \"0x00e514c0\"\n      },\n      {\n        \"role\": \"player death delegate\",\n        \"va\": \"0x00e72060\"\n      },\n      {\n        \"role\": \"scale-aware child/effect population\",\n        \"va\": \"0x00e771d0\"\n      },\n      {\n        \"name\": \"Simulator::Cell::PlayAnimation\",\n        \"role\": \"death animation intent\",\n        \"va\": \"0x00e6d200\"\n      },\n      {\n        \"role\": \"sets death/terminal flags and state word\",\n        \"va\": \"0x00e59170\"\n      },\n      {\n        \"role\": \"allocates interaction record\",\n        \"va\": \"0x00b72160\"\n      },\n      {\n        \"role\": \"pool lookups\",\n        \"va\": \"0x00b72210\"\n      },\n      {\n        \"role\": \"resource context guard\",\n        \"va\": \"0x00743b50\"\n      },\n      {\n        \"role\": \"current player scale lookup\",\n        \"va\": \"0x00e4ee60\"\n      }\n    ],\n    \"direct_callers\": [\n      {\n        \"role\": \"lethal damage resolver\",\n        \"va\": \"0x00e7a7c0\"\n      },\n      {\n        \"role\": \"health-zero guard\",\n        \"va\": \"0x00e7a770\"\n      },\n      {\n        \"role\": \"event/attack death wrapper\",\n        \"va\": \"0x00e7b240\"\n      },\n      {\n        \"role\": \"mode action that can kill avatar\",\n        \"va\": \"0x00e81120\"\n      }\n    ],\n    \"globals\": [],\n    \"structures\": [],\n    \"vtables\": [],\n    \"worker_contract_surface\": {\n      \"failure_behavior\": {\n        \"already_terminal\": \"Returns 0 when field_112 or field_113 is set.\",\n        \"null_or_invalid_cell\": \"No explicit null check before cell field access; invalid pool indices are caller-precondition failures.\",\n        \"player_lock_or_mode\": \"Returns 0 for avatar when +0x5169 or +0x5158 guards block the path.\",\n        \"resource_or_replacement_failure\": \"No normalization of effect, child/effect, or animation helper failures; FUN_00e771d0 has internal checks but caller does not surface status.\"\n      },\n      \"identity_boundary\": \"not_reported\",\n      \"inputs\": [],\n      \"ordering\": [],\n      \"outputs\": [],\n      \"postconditions\": [\n        \"Non-player path sets cell->field_113=1.\",\n        \"Death effect is cell_death_oneshot_small, cell_death_oneshot, or cell_death_oneshot_large based on sca
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
  "CellPoolIndex",
  "CellResourceRef",
  "CellResourceRef*",
  "E52a40Stack6",
  "OpaqueResourceScope",
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
  },
  {
    "anchors": [
      "0x00d2e490",
      "0x00d2e4a0",
      "0x0169e394",
      "0x00d2e490",
      "0x00e7a4a0",
      "0x00e7a7c0",
      "0x0169e394",
      "0x00d2e490",
      "0x00d2e490",
      "0x00d2e490",
      "0x00d2e4a0",
      "0x00d2e4a0",
      "0x00d2e4a0",
      "0x00e57460",
      "0x00e57460",
      "0x00e7a7c0"
    ],
    "conflict_id": "ability_mode_callers_and_domain",
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
      "0x00e7a4a0",
      "0x00e7a7c0",
      "0x00e7a7c0",
      "0x00e7e6c0",
      "0x00e7a4a0",
      "0x00e7a4a0",
      "0x00e62340",
      "0x00e52910",
      "0x00e7a7c0",
      "0x00e7a7c0",
      "0x00bfc460",
      "0x00bfc460",
      "0x00bfc490",
      "0x00bfc490",
      "0x00bfc4a0",
      "0x00bfc4a0"
    ],
    "conflict_id": "cell_field_112_semantics",
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
      "0x00e52910",
      "0x00e575f0",
      "0x00e52910",
      "0x00e7e6c0",
      "0x00e7a7c0",
      "0x00e7a4a0",
      "0x00e52910",
      "0x00e7a7c0",
      "0x00e72060",
      "0x00e52910",
      "0x00e52910",
      "0x00e52910",
      "0x00e575f0",
      "0x00e575f0",
      "0x00e575f0",
      "0x00e7a4a0"
    ],
    "conflict_id": "cell_target_selector_domain",
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
      "0x00c0bc20",
      "0x00c14aa0",
      "0x00c1f8d0",
      "0x00c1f8d0",
      "0x00e7a7c0",
      "0x00e7a4a0",
      "0x00c0bc20",
      "0x00c0bc20",
      "0x00c0bc20",
      "0x00c0e660",
      "0x00c0e660",
      "0x00c0e680",
      "0x00c0e680",
      "0x00c14aa0",
      "0x00c14aa0",
      "0x00c14aa0"
    ],
    "conflict_id": "creature_ability_bitset_mapping",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolv
[TRUNCATED]
```
