# Evidence 0x00e52910

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `8b4b62e89e3f77b631f388ab51686195d9d54008d56edcf37157ee6da541a1b8`

## abi

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
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
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
  "content_sha256": "89e2ffa779f5e77b68d15fb5e577730dabe37edf0d7e1da3bcad5f9971ca6d59",
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
        "obs-0008",
        "obs-0010"
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
        "obs-0009"
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
        "obs-0002",
        "obs-0003",
        "obs-0004",
        "obs-0005",
        "obs-0006",
        "obs-0009"
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
        "obs-0002",
        "obs-0003",
        "obs-0004",
        "obs-0005",
        "obs-0006",
        "obs-0009"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_reassigned_before_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0008",
        "obs-0010"
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
        "obs-0008",
        "obs-0010"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0008",
        "obs-0010"
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
      "at": "0x00e52910",
      "definite": true,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,[0x016b3c04]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00e52915",
      "count": 5,
      "first_use": 1,
      "first_write_index": 0,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ECX,dword ptr [EAX + 0x5190]",
      "reg": "EAX"
    },
    {
      "at": "0x00e52915",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [EAX + 0x5190]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00e5291b",
      "count": 4,
      "first_use": 2,
      "first_write_index": 1,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ECX + 0x7c]",
      "reg": "ECX"
    },
    {
      "at": "0x00e5292d",
      "count": 3,
      "first_use": 9,
      "first_write_index": null,
      "id": "obs-0005",
      "index": 9,
      "kind": "REG_READ",
      "raw": "MOV ECX,dword ptr [ESP + 0x4]",
      "reg": "ESP"
    },
    {
      "at": "0x00e5292d",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0006",
      "index": 9,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV ECX,dword ptr [ESP + 0x4]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00e52939",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0007",
      "index": 12,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00e52942",
      "form": "RET",
      "id": "obs-0008",
     
[TRUNCATED]
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
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
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
  "content_sha256": "89e2ffa779f5e77b68d15fb5e577730dabe37edf0d7e1da3bcad5f9971ca6d59",
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
        "obs-0008",
        "obs-0010"
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
        "obs-0009"
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
        "obs-0002",
        "obs-0003",
        "obs-0004",
        "obs-0005",
        "obs-0006",
        "obs-0009"
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
        "obs-0002",
        "obs-0003",
        "obs-0004",
        "obs-0005",
        "obs-0006",
        "obs-0009"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_reassigned_before_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0008",
        "obs-0010"
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
        "obs-0008",
        "obs-0010"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0008",
        "obs-0010"
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
      "at": "0x00e52910",
      "definite": true,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,[0x016b3c04]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00e52915",
      "count": 5,
      "first_use": 1,
      "first_write_index": 0,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ECX,dword ptr [EAX + 0x5190]",
      "reg": "EAX"
    },
    {
      "at": "0x00e52915",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [EAX + 0x5190]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00e5291b",
      "count": 4,
      "first_use": 2,
      "first_write_index": 1,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ECX + 0x7c]",
      "reg": "ECX"
    },
    {
      "at": "0x00e5292d",
      "count": 3,
      "first_use": 9,
      "first_write_index": null,
      "id": "obs-0005",
      "index": 9,
      "kind": "REG_READ",
      "raw": "MOV ECX,dword ptr [ESP + 0x4]",
      "reg": "ESP"
    },
    {
      "at": "0x00e5292d",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0006",
      "index": 9,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV ECX,dword ptr [ESP + 0x4]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00e52939",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0007",
      "index": 12,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00e52942",
      "form": "RET",
      "id": "obs-0008",
     
[TRUNCATED]
```

## callees_dependencies

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## callers_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e575f0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e57890"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e67c40"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e686c0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e69480"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e695f0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e6cbd0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e6f990"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e6fbb0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e6fce0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e6fd70"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e70650"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e707d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e70cf0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e71300"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e71520"
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
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00e52910",
      "0x00e52910",
      "0x00e7e6c0",
      "0x00e7a4a0",
      "0x00e7a4a0",
      "0x00e52910",
      "0x00e7a7c0",
      "0x00e72060",
      "0x00e52910",
      "0x00e52910",
      "0x00e575f0",
      "0x00e575f0",
      "0x00e7a4a0",
      "0x00e7a4a0",
      "0x00e7e6c0",
      "0x00e7e6c0"
    ],
    "conflict_id": "live_ghidra_access",
    "kind": "conflict_ledger",
    "rejected": [
      {
        "path": "evidence.1.claim",
        "status": "     ",
        "text": "Ghidra headless open rejected SporeApp.exe"
      }
    ],
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
  "count": 21,
  "instructions": [
    {
      "address": "00e52910",
      "instruction": "MOV EAX,[0x016b3c04]"
    },
    {
      "address": "00e52915",
      "instruction": "MOV ECX,dword ptr [EAX + 0x5190]"
    },
    {
      "address": "00e5291b",
      "instruction": "MOV EAX,dword ptr [ECX + 0x7c]"
    },
    {
      "address": "00e5291e",
      "instruction": "SUB EAX,0x0"
    },
    {
      "address": "00e52921",
      "instruction": "JZ 0x00e52943"
    },
    {
      "address": "00e52923",
      "instruction": "SUB EAX,0x1"
    },
    {
      "address": "00e52926",
      "instruction": "JZ 0x00e52939"
    },
    {
      "address": "00e52928",
      "instruction": "SUB EAX,0x1"
    },
    {
      "address": "00e5292b",
      "instruction": "JNZ 0x00e52939"
    },
    {
      "address": "00e5292d",
      "instruction": "MOV ECX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "00e52931",
      "instruction": "LEA EAX,[ECX + 0x194]"
    },
    {
      "address": "00e52937",
      "instruction": "JMP 0x00e5294d"
    },
    {
      "address": "00e52939",
      "instruction": "MOV EAX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "00e5293d",
      "instruction": "ADD EAX,0xe0"
    },
    {
      "address": "00e52942",
      "instruction": "RET"
    },
    {
      "address": "00e52943",
      "instruction": "MOV ECX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "00e52947",
      "instruction": "LEA EAX,[ECX + 0x248]"
    },
    {
      "address": "00e5294d",
      "instruction": "CMP dword ptr [EAX],-0x1"
    },
    {
      "address": "00e52950",
      "instruction": "JNZ 0x00e52958"
    },
    {
      "address": "00e52952",
      "instruction": "LEA EAX,[ECX + 0xe0]"
    },
    {
      "address": "00e52958",
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
  "original_bytes": 12893,
  "preview": "{\n  \"abi\": {},\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None,ObservedCellCellResource\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-06C-CELL-BEHAVIOR-DISPATCH\",\n      \"score\": 14,\n      \"symbol\": \"cell_behavior_dispatch_00e7a190\",\n      \"va\": \"0x00e7a190\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-06-CELL-STATE\",\n      \"score\": 14,\n      \"symbol\": \"FUN_00e7fd00\",\n      \"va\": \"0x00e7fd00\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-11-H2-ROOT-ACCESSORS\",\n      \"score\": 8,\n      \"symbol\": \"root_accessor_00b3d3b0\",\n      \"va\": \"0x00b3d3b0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-11-H2-ROOT-ACCESSORS\",\n      \"score\": 8,\n      \"symbol\": \"root_accessor_00b3d3e0\",\n      \"va\": \"0x00b3d3e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-11-H2-ROOT-ACCESSORS\",\n      \"score\": 8,\n      \"symbol\": \"root_accessor_00b3d3f0\",\n      \"va\": \"0x00b3d3f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-11-H2-ROOT-ACCESSORS\",\n      \"score\": 8,\n      \"symbol\": \"root_accessor_00b3d430\",\n      \"va\": \"0x00b3d430\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-13-E3-EMPIRE-STATE-WAVE2\",\n      \"score\": 8,\n      \"symbol\": \"SpeciesProfileSelector_00c30cc0\",\n      \"va\": \"0x00c30cc0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-13-E3-EMPIRE-STATE-WAVE2\",\n      \"score\": 8,\n      \"symbol\": \"ArchetypeRelationshipsID_00c30e20\",\n      \"va\": \"0x00c30e20\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Static selection mapping and type -1 fallback are supported; original Cell reachability, runtime pointer chain, difficulty values, and profile ownership remain unresolved, and no runtime validation is claimed.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_semantic_abi_type_lifecycle_review\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"None\",\n  \"cluster\": null,\n  \"confidence\": 0.9,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e575f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e57890\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e67c40\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e686c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e69480\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e695f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e6cbd0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e6f990\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e6fbb0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e6fce0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e6fd70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e70650\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e707d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e70cf0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e71300\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e71520\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e71f00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e78fc0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e792b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e79320\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e79c30\"\n      },\n      {\n        \"name\": \"cell_behavior_dispatch_00e7a190\",\n        \"reconstructed\": true,\n        \"va\": \"0x00e7a190\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e7d760\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00e57657\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e575f0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e57682\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e575f0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e57694\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e575f0\",\n        \"reference
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
  "body_end": "00e52958",
  "body_span_bytes": 73,
  "body_start": "00e52910",
  "callees": [],
  "callers": [
    "FUN_00e695f0",
    "FUN_00e792b0",
    "FUN_00e78fc0",
    "FUN_00e6fce0",
    "FUN_00e7d760",
    "FUN_00e6fd70",
    "FUN_00e6fbb0",
    "FUN_00e70650",
    "FUN_00e67c40",
    "FUN_00e69480",
    "FUN_00e71520",
    "FUN_00e707d0",
    "FUN_00e575f0",
    "FUN_00e6cbd0",
    "FUN_00e6f990",
    "FUN_00e57890",
    "FUN_00e79320",
    "FUN_00e79c30",
    "FUN_00e686c0",
    "FUN_00e7a190",
    "FUN_00e71f00",
    "FUN_00e71300",
    "FUN_00e70cf0"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "00e52910",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00e52910",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xa52910",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00e52910(void)",
  "size_bytes": 73,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00e52910",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 90,
  "xrefs": [
    {
      "from": "00e68752"
    },
    {
      "from": "00e687bb"
    },
    {
      "from": "00e687d5"
    },
    {
      "from": "00e687f3"
    },
    {
      "from": "00e68813"
    },
    {
      "from": "00e6882a"
    },
    {
      "from": "00e68846"
    },
    {
      "from": "00e6cf14"
    },
    {
      "from": "00e6cfb2"
    },
    {
      "from": "00e6d03c"
    },
    {
      "from": "00e6fa4b"
    },
    {
      "from": "00e6fa58"
    },
    {
      "from": "00e6fa6e"
    },
    {
      "from": "00e6fb56"
    },
    {
      "from": "00e6fb71"
    },
    {
      "from": "00e6fb7d"
    },
    {
      "from": "00e67c5a"
    },
    {
      "from": "00e67c69"
    },
    {
      "from": "00e6fbef"
    },
    {
      "from": "00e6fbfb"
    },
    {
      "from": "00e6fc57"
    },
    {
      "from": "00e6fc81"
    },
    {
      "from": "00e6fc9c"
    },
    {
      "from": "00e6fca8"
    },
    {
      "from": "00e6fe64"
    },
    {
      "from": "00e6fe71"
    },
    {
      "from": "00e6fe87"
    },
    {
      "from": "00e6fee6"
    },
    {
      "from": "00e6ff01"
    },
    {
      "from": "00e6ff0d"
    },
    {
      "from": "00e706b1"
    },
    {
      "from": "00e7078c"
    },
    {
      "from": "00e70798"
    },
    {
      "from": "00e694db"
    },
    {
      "from": "00e694fc"
    },
    {
      "from": "00e6964a"
    },
    {
      "from": "00e7169d"
    },
    {
      "from": "00e716bb"
    },
    {
      "from": "00e7a252"
    },
    {
      "from": "00e7a283"
    },
    {
      "from": "00e7a29e"
    },
    {
      "from": "00e7a31b"
    },
    {
      "from": "00e71fa2"
    },
    {
      "from": "00e72027"
    },
    {
      "from": "00e578e7"
    },
    {
      "from": "00e7d7a1"
    },
    {
      "from": "00e792f0"
    },
    {
      "from": "00e57657"
    },
    {
      "from": "00e57682"
    },
    {
      "from": "00e57694"
    },
    {
      "from": "00e70dc3"
    },
    {
      "from": "00e70dff"
    },
    {
      "from": "00e79d93"
    },
    {
      "from": "00e79dae"
    },
    {
      "from": "00e79e42"
    },
    {
      "from": "00e79e85"
    },
    {
      "from": "00e79e9e"
    },
    {
      "from": "00e79ed2"
    },
    {
      "from": "00e79f2b"
    },
    {
      "from": "00e79f45"
    },
    {
      "from": "00e79fb0"
    },
    {
      "from": "00e79fd3"
    },
    {
      "from": "00e7a009"
    },
    {
      "from": "00e7a015"
    },
    {
      "from": "00e7a021"
    },
    {
      "from": "00e7a053"
    },
    {
      "from": "00e7a06f"
    },
    {
      "from": "00e79013"
    },
    {
      "from": "00e79026"
    },
    {
      "from": "00e79063"
    },
    {
      "from": "00e790a6"
    },
    {
      "from": "00e79128"
    },
    {
      "from": "00e7915f"
    },
    {
      "from": "00e79178"
    },
    {
      "from": "00e7081a"
    },
    {
      "from": "00e7085c"
    },
    {
      "from": "00e708bb"
    },
    {
      "from": "00e708f2"
    },
    {
      "from": "00e7090d"
    },
    {
      "from": "00e70919"
    },
    {
      "from": "00e6fd35"
    },
    {
      "from": "00e6fd41"
    },
    {
      "from": "00e71327"
    },
    {
      "from": "00e71365"
    },
    {
      "from": "00e714e1"
    },
    {
      "from": "00e714fa"
    },
    {
      "from": "00e79392"
    },
    {
      "from": "00e793ee"
    },
    {
      "from": "00e79405"
    },
    {
      "from": "00e79426"
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
  "global:std::byte* g_cell_game_016b3c04"
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg06a_cell_ai_selection/cell_ai_selection.cpp",
  "files": [
    "src/reconstruction/pkg06a_cell_ai_selection/cell_ai_selection.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-pkg06a-cell-ai-selection/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg06a-cell-ai-selection/00e52910.json"
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
    "gate-cell-ai-selection"
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
  "None",
  "ObservedCellAiData",
  "ObservedCellCellResource",
  "std::int32_t"
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
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00e52910",
      "0x00e52910",
      "0x00e7e6c0",
      "0x00e7a4a0",
      "0x00e7a4a0",
      "0x00e52910",
      "0x00e7a7c0",
      "0x00e72060",
      "0x00e52910",
      "0x00e52910",
      "0x00e575f0",
      "0x00e575f0",
      "0x00e7a4a0",
      "0x00e7a4a0",
      "0x00e7e6c0",
      "0x00e7e6c0"
    ],
    "conflict_id": "live_ghidra_access",
    "kind": "conflict_ledger",
    "rejected": [
      {
        "path": "evidence.1.claim",
        "status": "     ",
        "text": "Ghidra headless open rejected SporeApp.exe"
      }
    ],
    "resolution": "The cited stream or file boundary is retained, but the complete wire/transaction/round-trip contract is not reconstructed.",
    "resolution_status": "The cited stream or file boundary is retained, but the complete wire/transaction/round-trip contract is not reconstructed.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  }
]
```
