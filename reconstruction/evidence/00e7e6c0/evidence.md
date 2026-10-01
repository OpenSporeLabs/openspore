# Evidence 0x00e7e6c0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `1fa5b50641a86a390d9a6a58e37ed1c884051850dbe0b73cbdec2360cf604d0a`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "convention": "custom EAX record plus ECX residue plus one caller-cleaned float stack argument",
  "return": "void-like; all exits are plain RET and no EAX return contract is defined"
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
    "flow_not_modelled: the linear ESP walk ends at -4, so the listing is not one path",
    "receiver_not_determinable: ecx_read_without_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_read_without_deref), and the convention rule that would apply discriminates on receiver absence"
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
  "content_sha256": "25eea11a9425540f7362c486be2dcfd5db350d2faaf20b74a54f8f8dbff7dfa0",
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
        "obs-0017",
        "obs-0040"
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
        "obs-0002",
        "obs-0007",
        "obs-0013",
        "obs-0023",
        "obs-0024",
        "obs-0031",
        "obs-0034"
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
        "obs-0008",
        "obs-0025"
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
        "obs-0008",
        "obs-0025"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_read_without_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0017",
        "obs-0040"
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
        "obs-0040"
      ],
      "claim": "the return value is carried in ST0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "ST0"
    }
  ],
  "observations": [
    {
      "at": "0x00e7e6c0",
      "count": 12,
      "first_use": 0,
      "first_write_index": 10,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "FLD float ptr [ESP + 0x4]",
      "reg": "ESP"
    },
    {
      "at": "0x00e7e6c0",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0002",
      "index": 0,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "FLD float ptr [ESP + 0x4]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00e7e6c4",
      "count": 10,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00e7e6c5",
      "count": 2,
      "first_use": 2,
      "first_write_index": 52,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV EDI,EAX",
      "reg": "EAX"
    },
    {
      "at": "0x00e7e6c5",
      "definite": true,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV EDI,EAX",
      "reg": "EDI",
      "write_kind": "reg"
    },
    {
      "at": "0x00e7e6c7",
      "definite": true,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOVSS XMM0,dword ptr [EDI + 0x1c]",
      "reg": "XMM0",
      "write_kind": "unknown"
    },
    {
      "at": "0x00e7e6cc",
      "base": "ESP",
      "disp": 8,
      "id": "obs-0007",
      "index": 4,
 
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
    "va": "0x00e7e7a0"
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
  "count": 77,
  "instructions": [
    {
      "address": "00e7e6c0",
      "instruction": "FLD float ptr [ESP + 0x4]"
    },
    {
      "address": "00e7e6c4",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00e7e6c5",
      "instruction": "MOV EDI,EAX"
    },
    {
      "address": "00e7e6c7",
      "instruction": "MOVSS XMM0,dword ptr [EDI + 0x1c]"
    },
    {
      "address": "00e7e6cc",
      "instruction": "SUBSS XMM0,dword ptr [ESP + 0x8]"
    },
    {
      "address": "00e7e6d2",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00e7e6d3",
      "instruction": "FSTP float ptr [ESP]"
    },
    {
      "address": "00e7e6d6",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00e7e6d7",
      "instruction": "MOVSS dword ptr [EDI + 0x1c],XMM0"
    },
    {
      "address": "00e7e6dc",
      "instruction": "CALL 0x00e59c10"
    },
    {
      "address": "00e7e6e1",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "00e7e6e4",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00e7e6e6",
      "instruction": "JNZ 0x00e7e6fe"
    },
    {
      "address": "00e7e6e8",
      "instruction": "FLD float ptr [ESP + 0x8]"
    },
    {
      "address": "00e7e6ec",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00e7e6ee",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00e7e6f0",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00e7e6f1",
      "instruction": "FSTP float ptr [ESP]"
    },
    {
      "address": "00e7e6f4",
      "instruction": "CALL 0x00e7e130"
    },
    {
      "address": "00e7e6f9",
      "instruction": "ADD ESP,0xc"
    },
    {
      "address": "00e7e6fc",
      "instruction": "POP EDI"
    },
    {
      "address": "00e7e6fd",
      "instruction": "RET"
    },
    {
      "address": "00e7e6fe",
      "instruction": "XORPS XMM1,XMM1"
    },
    {
      "address": "00e7e701",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00e7e702",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00e7e703",
      "instruction": "XOR ESI,ESI"
    },
    {
      "address": "00e7e705",
      "instruction": "LEA EBX,[EDI + 0xc]"
    },
    {
      "address": "00e7e708",
      "instruction": "JMP 0x00e7e710"
    },
    {
      "address": "00e7e710",
      "instruction": "MOVSS XMM0,dword ptr [EBX]"
    },
    {
      "address": "00e7e714",
      "instruction": "COMISS XMM0,XMM1"
    },
    {
      "address": "00e7e717",
      "instruction": "JBE 0x00e7e747"
    },
    {
      "address": "00e7e719",
      "instruction": "SUBSS XMM0,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00e7e71f",
      "instruction": "COMISS XMM1,XMM0"
    },
    {
      "address": "00e7e722",
      "instruction": "MOVSS dword ptr [EBX],XMM0"
    },
    {
      "address": "00e7e726",
      "instruction": "JBE 0x00e7e747"
    },
    {
      "address": "00e7e728",
      "instruction": "FLD float ptr [ESP + 0x10]"
    },
    {
      "address": "00e7e72c",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00e7e72d",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00e7e72f",
      "instruction": "FSTP float ptr [ESP]"
    },
    {
      "address": "00e7e732",
      "instruction": "MOV EDX,ESI"
    },
    {
      "address": "00e7e734",
      "instruction": "MOVSS dword ptr [EBX],XMM1"
    },
    {
      "address": "00e7e738",
      "instruction": "CALL 0x00e7b540"
    },
    {
      "address": "00e7e73d",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "00e7e740",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00e7e742",
      "instruction": "JZ 0x00e7e782"
    },
    {
      "address": "00e7e744",
      "instruction": "XORPS XMM1,XMM1"
    },
    {
      "address": "00e7e747",
      "instruction": "INC ESI"
    },
    {
      "address": "00e7e748",
      "instruction": "ADD EBX,0x4"
    },
    {
      "address": "00e7e74b",
      "instruction": "CMP ESI,0x4"
    },
    {
      "address": "00e7e74e",
      "instruction": "JL 0x00e7e710"
    },
    {
      "address": "00e7e750",
      "instruction": "COMISS XMM1,dword ptr [EDI + 0x1c]"
    },
    {
      "address": "00e7e754",
      "instruction": "JC 0x00e7e76c"
    },
    {
      "address": "00e7e756",
      "instruction": "MOV EAX,[0x016b3c04]"
    },
    {
      "address": "00e7e75b",
      "instruction": "MOV ECX,dword ptr [EAX + 0x5198]"
    },
    {
      "address": "00e7e761",
      "instruction": "CMP ECX,dword ptr [EDI]"
    },
    {
      "address": "00e7e763",
      "instruction": "JZ 0x00e7e76c"
    },
    {
      "address": "00e7e765",
      "instruction": "MOVSS dword ptr [EDI + 0x1c],XMM1"
    },
    {
      "address": "00e7e76a",
      "instruction": "JMP 0x00e7e782"
    },
    {
      "address": "00e7e76c",
      "instruction": "FLD float ptr [ESP + 0x10]"
    },
    {
      "address": "00e7e770",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00e7e771",
      "instruction": "MOV EAX,EDI"
    },
    {
      "address": "00e7e773",
      "instruction": "FSTP float ptr [ESP]"
    },
    {
      "address": "00e7e776",
      "instruction": "CALL 0x00e7ba30"
    },
    {
      "address": "00e7e77b",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "00e7e77e",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00e7e780",
      "instruction": "JNZ 0x00e7e796"
    },
    {
      "address": "00e7e782",
      "instruction": "FLD float ptr [ESP + 0x10]"
    },
    {
      "address": "00e7e786",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00e7e788",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00e7e78a",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00e7e78b",
      "instruction": "FSTP float ptr [ESP]"
    },
    {
      "address": "00e7e78e",
      "instruction": "CALL 0x00e7e130"
    },
    {
      "address": "00e7e793",
      "instruction": "ADD ESP,0xc
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
  "original_bytes": 6830,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"convention\": \"custom EAX record plus ECX residue plus one caller-cleaned float stack argument\",\n    \"return\": \"void-like; all exits are plain RET and no EAX return contract is defined\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"shared_types:NativePorts&\"\n      ],\n      \"package\": \"PKG-06C-CELL-BEHAVIOR-DISPATCH\",\n      \"score\": 3,\n      \"symbol\": \"cell_behavior_dispatch_00e7a190\",\n      \"va\": \"0x00e7a190\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"The custom EAX-record/ECX-residue/stack-float/RET boundary, ordered and unordered COMISS outcomes, four slot operations, selector branches, fallback order, and no target-local release are exact; live record stride, pointer validity, unresolved port effects, and runtime branch outcomes remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_semantic_abi_type_lifecycle_review\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueBehaviorTimerRecord\",\n  \"cluster\": null,\n  \"confidence\": 0.9,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e7e7a0\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00e7e7d0\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e7e7a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7e6dc\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e59c10\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7e738\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e7b540\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7e776\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e7ba30\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7e6f4\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e7e130\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7e78e\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e7e130\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 1,\n    \"fan_out\": 0,\n    \"manifest_callees\": [\n      \"0x00e59c10\",\n      \"0x00e7b540\",\n      \"0x00e7ba30\",\n      \"0x00e7e130\"\n    ],\n    \"manifest_callers\": [\n      \"0x00e7e7a0\"\n    ],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0554\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"OBSERVED\",\n  \"globals\": [\n    \"global:0x00005198\",\n    \"global:0x016b3c04\",\n    \"global:g_cell_game_016b3c04\"\n  ],\n  \"integration_status\": \"integrated\",\n  \"name\": \"cell_behavior_timer_update_00e7e6c0\",\n  \"normalized_symbol\": \"cell_behavior_timer_update_00e7e6c0\",\n  \"observed_mechanics\": [\n    \"EAX borrowed record and ECX opaque entry residue are normalized without treating ECX as a pool pointer\",\n    \"one caller-cleaned float stack argument and plain RET\",\n    \"record[0x1c] is decremented unconditionally before the initial gate\",\n    \"COMISS 0,main_timer sends ordered-positive and unordered NaN results to advance without reading the selector\",\n    \"four ordered-positive slot semantics at +0x0c, +0x10, +0x14, and +0x18 subtract delta; only ordered-negative remainders are zeroed and invoke expiry with slots 0 through 3\",\n    \"ordered non-positive main timer reads PKG-06A g_cell_game_016b3c04+0x5198; selector equality advances, while selector inequality zeros +0x1c before fallback\",\n    \"failed gate, failed expiry, selector inequality, or failed advance follows unresolved 0x00e7e130 fallback order\",\n    \"no target-local pool release\"\n  ],\n  \"ownership\": {\n    \"claimability\": \"do_not_claim\",\n    \"handoff_packages\": [\n      \"PKG-06D-CELL-BEHAVIOR-TIMER\"\n    ],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": \"PKG-06D-CELL-BEHAVIOR-TIMER\",\n    \"queue_state\": null\n  },\n  \"package\": \"PKG-06D-CELL-BEHAVIOR-TIMER\",\n  \"reconstructed\": true,\n  \"review_status\": \"approved\",\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"gate-cell-behavior-timer\"\n    ],\n    \"validated\": 0\n  },\n  \"runtime_gated\": true,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": \"static_timer_mutation_and_call_order_known_runtime_ports_and_record_lifetime_unknown\",\n  \"services\": [],\n  \"source\": {\n    \"decomp\": null,\n    \"file\": \"src/reconstruction/pkg06d_cell_behavior_timer/cell_behavior_timer.cpp\",\n    \"files\": [\n      \"reconstruction/staging/pkg06d-cell-behavior-timer/cell_behavior_timer.cpp\",\n      \"reconstruction/staging/pkg06d-cell-behavior-timer/cell_behavior_timer.hpp\",\n      \"reconstruction/staging/pkg06d-cell-behavior-timer/cell_behavior_timer_model_test.cpp\",\n      \"src/reconstruction/pkg06d_cell_behavior_timer/cell_behavior_timer.cpp\"\n    ],\n    \"handoffs\": [\n      \"reconstruction/integrated/batch-2026-09-25-pkg06d-cell-behavior-timer/handoff.json\"\n    ],\n    \"metadata\": [\n      \"reconstruction/metadata/pkg06d-cell-behavior-timer/00e7e6c0.json\"\n    ],\n    \"provenance\": [\n      \"ghidra:decompile_function\",\n      \"ghidra:disassemble_function\",\n      \"ghidra:get_function_callees\",\n      \"ghidra:get_function_callers\",\n      \"reconstruction/integrated/batch-2026-09-25-pkg06d-cell-behavior-timer/handoff.json\",\n   
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
  "body_end": "00e7e799",
  "body_span_bytes": 218,
  "body_start": "00e7e6c0",
  "callees": [
    "FUN_00e7b540",
    "FUN_00e7ba30",
    "FUN_00e59c10",
    "FUN_00e7e130"
  ],
  "callers": [
    "FUN_00e7e7a0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00e7e6c0",
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
      "name": "local_18",
      "storage": "Stack[-0x18]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 3,
  "mode": "live",
  "name": "FUN_00e7e6c0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xa7e6c0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00e7e6c0(void)",
  "size_bytes": 218,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00e7e6c0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "00e7e7d0"
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
  "global:0x00005198",
  "global:0x016b3c04",
  "global:g_cell_game_016b3c04"
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg06d_cell_behavior_timer/cell_behavior_timer.cpp",
  "files": [
    "reconstruction/staging/pkg06d-cell-behavior-timer/cell_behavior_timer.cpp",
    "reconstruction/staging/pkg06d-cell-behavior-timer/cell_behavior_timer.hpp",
    "reconstruction/staging/pkg06d-cell-behavior-timer/cell_behavior_timer_model_test.cpp",
    "src/reconstruction/pkg06d_cell_behavior_timer/cell_behavior_timer.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-pkg06d-cell-behavior-timer/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg06d-cell-behavior-timer/00e7e6c0.json"
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
    "gate-cell-behavior-timer"
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
  "AdvanceCallContext",
  "ExpireCallContext",
  "FallbackCallContext",
  "GateCallContext",
  "NativePorts&",
  "OpaqueBehaviorTimerEntryEcx",
  "OpaqueBehaviorTimerRecord",
  "OpaqueBehaviorTimerRecord*",
  "PKG-06D-CELL-BEHAVIOR-TIMER::NativePorts",
  "float",
  "opaque caller residue"
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
