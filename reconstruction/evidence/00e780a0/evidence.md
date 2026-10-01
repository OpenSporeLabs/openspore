# Evidence 0x00e780a0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `c672d410d7e98cbb27e832f2f1060ffbf0a13aa5bc79fcb973c8c51bbb487b66`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "stack_cleanup_bytes": 16
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
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +12, so the listing is not one path",
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
  "conflicts": [
    {
      "field": "stack_cleanup_bytes",
      "inferred": 0,
      "kind": "inferred_vs_persisted",
      "persisted": 16,
      "resolution_status": "unresolved"
    }
  ],
  "content_sha256": "3905d1446b3c5e2c1ef294b2ee2d0d22fc3f6e88ae87f7690dd781a9e2edbb24",
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
        "obs-0022",
        "obs-0040"
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
        "obs-0001",
        "obs-0012",
        "obs-0022",
        "obs-0028",
        "obs-0044"
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
        "obs-0001",
        "obs-0012",
        "obs-0022",
        "obs-0028",
        "obs-0044"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_reassigned_before_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
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
        "obs-0002"
      ],
      "claim": "the return value is carried in ST0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "ST0"
    }
  ],
  "observations": [
    {
      "at": "0x00e780a0",
      "definite": true,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [0x016b3c04]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "and_esp": null,
      "at": "0x00e780a6",
      "ebp_is_general_register": false,
      "fp": false,
      "id": "obs-0002",
      "index": 1,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": true,
      "push_ebp_at": 2,
      "raw": "SUB ESP,0x10",
      "sub": 16
    },
    {
      "at": "0x00e780a6",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x10",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00e780a9",
      "count": 5,
      "first_use": 2,
      "first_write_index": 3,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH EBP",
      "reg": "EBP"
    },
    {
      "at": "0x00e780aa",
      "count": 15,
      "first_use": 3,
      "first_write_index": 1,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV EBP,dword ptr [ESP + 0x18]",
      "reg": "ESP"
    },
    {
    
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
    "va": "0x00e771d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e78b20"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e78b80"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e78c00"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e78fc0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e791a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e79460"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e794f0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e79720"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e7a0d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e7a160"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e7aa20"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e7add0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e7b410"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e7b5d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e7b630"
  }
]
```

## contradictions

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "original_bytes": 9017,
  "preview": "[\n  {\n    \"anchors\": [\n      \"0x00e74a20\",\n      \"0x00e57460\",\n      \"0x00e6d200\",\n      \"0x00e57340\",\n      \"0x00e780a0\",\n      \"0x00000108\",\n      \"0x00e74a20\",\n      \"0x00000108\"\n    ],\n    \"conflict_id\": \"TB-FL-012\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": {\n      \"merge_decision\": \"separate_entities\",\n      \"preferred_claim\": \"Use the original direct field/body evidence as the ABI anchor.\",\n      \"preserved_alternatives\": true,\n      \"scope_note\": \"The current padding is a replacement limitation and cannot define the original structure.\",\n      \"status\": \"preferred_claim_with_limit\",\n      \"taxonomy\": \"preferred_claim_with_limit\"\n    },\n    \"resolution_status\": \"preferred_claim_with_limit\",\n    \"source\": \"knowledgegraph/research/conflicts/track-b-vtable-fields.json\",\n    \"subject\": \"cCellObjectData original middle fields versus current opaque padding\",\n    \"unresolved_reason\": \"The cited static evidence leaves the competing owner, slot, layout, or lifecycle interpretation unresolved; no positive original runtime or MSVC RTTI evidence is available.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00e62340\",\n      \"0x00e780a0\",\n      \"0x00e7a7c0\",\n      \"0x00e806b0\",\n      \"0x00e7a7c0\",\n      \"0x00e62340\",\n      \"0x00e780a0\",\n      \"0x00e806b0\",\n      \"0x00e7fd00\",\n      \"0x00e74a20\",\n      \"0x00e780a0\",\n      \"0x00e74a20\",\n      \"0x00e74a20\",\n      \"0x00e4ce20\",\n      \"0x00e5b790\",\n      \"0x00e665c0\"\n    ],\n    \"conflict_id\": \"U-003-cell-respawn-policy\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"Damage/death branches, despawn cleanup, optional scale replacement, and deferred stage rebuild are concrete. Caller-specific respawn policy and replacement ordering are unresolved.\",\n    \"resolution_status\": \"Damage/death branches, despawn cleanup, optional scale replacement, and deferred stage rebuild are concrete. Caller-specific respawn policy and replacement ordering are unresolved.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00eedd40\",\n      \"0x00e7fd00\",\n      \"0x00e74a20\",\n      \"0x00e74a20\",\n      \"0x00e5b790\",\n      \"0x00e80ba0\",\n      \"0x00b72370\",\n      \"0x00b72320\",\n      \"0x00e780a0\",\n      \"0x00b72160\",\n      \"0x00b72260\",\n      \"0x00b72270\",\n      \"0x00b72370\",\n      \"0x00bb4100\",\n      \"0x00bb42a0\"\n    ],\n    \"conflict_id\": \"U-008-scenario-respawner\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The cited direct body establishes a bounded state mutation or call anchor, but the full transition policy, consumer order, and runtime reachability remain unresolved.\",\n    \"resolution_status\": \"The cited direct body establishes a bounded state mutation or call anchor, but the full transition policy, consumer order, and runtime reachability remain unresolved.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00e62340\",\n      \"0x00e780a0\",\n      \"0x00e7a7c0\",\n      \"0x00e806b0\",\n      \"0x00e7a7c0\",\n      \"0x00e62340\",\n      \"0x00e780a0\",\n      \"0x00e806b0\",\n      \"0x00e62200\",\n      \"0x00e62200\",\n      \"0x00e62340\",\n      \"0x00e62340\",\n      \"0x007d8c80\"\n    ],\n    \"conflict_id\": \"U-CELL-ROLLOVER\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"Rollover creation is guarded by GFX presence, receives a health-derived value, and receives mDisappearTime=0.5. Expiry, hide, reuse, and release order are unresolved.\",\n    \"resolution_status\": \"Rollover creation is guarded by GFX presence, receives a health-derived value, and receives mDisappearTime=0.5. Expiry, hide, reuse, and release order are unresolved.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00e80ba0\",\n      \"0xffffffff\",\n      \"0x00e80ba0\",\n      \"0x00e74a20\",\n      \"0x00e780a0\",\n      \"0x00b721d0\",\n      \"0x00b72260\",\n      \"0x00e771d0\",\n      \"0x00e7d370\",\n      \"0xffffffff\",\n      \"0xffffffff\",\n      \"0xffffffff\"\n    ],\n    \"conflict_id\": \"U1\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [\n      {\n        \"path\": \"evidence.0.claim\",\n        \"status\": \"     \",\n        \"text\": \"Original lookup helper rejects index 0; current CellPool starts at 0 and uses 0xffffffff as invalid\"\n      }\n    ],\n    \"resolution\": \"The cited direct body establishes a bounded state mutation or call anchor, but the full transition policy, consumer order, and runtime reachability remain unresolved.\",\n    \"resolution_status\": \"The cited direct body establishes a bounded state mutation or call anchor, but the full transition policy, consumer order, and runtime reachability remain unresolved.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x0000411c\",\n      \"0x00e62340\",\n      \"0x00e780a0\",\n      \"0x00e7a7c0\",\n      \"0x00e806b0\",\n      \"0x00e7a7c0\",\n      \"0x00e62340\",
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
  "count": 116,
  "instructions": [
    {
      "address": "00e780a0",
      "instruction": "MOV ECX,dword ptr [0x016b3c04]"
    },
    {
      "address": "00e780a6",
      "instruction": "SUB ESP,0x10"
    },
    {
      "address": "00e780a9",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00e780aa",
      "instruction": "MOV EBP,dword ptr [ESP + 0x18]"
    },
    {
      "address": "00e780ae",
      "instruction": "ADD ECX,0x1c"
    },
    {
      "address": "00e780b1",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00e780b2",
      "instruction": "CALL 0x00b721d0"
    },
    {
      "address": "00e780b7",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00e780b9",
      "instruction": "JZ 0x00e78222"
    },
    {
      "address": "00e780bf",
      "instruction": "MOV EAX,[0x016b3c04]"
    },
    {
      "address": "00e780c4",
      "instruction": "CMP EBP,dword ptr [EAX + 0x411c]"
    },
    {
      "address": "00e780ca",
      "instruction": "JNZ 0x00e780db"
    },
    {
      "address": "00e780cc",
      "instruction": "MOV dword ptr [EAX + 0x411c],0x0"
    },
    {
      "address": "00e780d6",
      "instruction": "MOV EAX,[0x016b3c04]"
    },
    {
      "address": "00e780db",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00e780dc",
      "instruction": "LEA ECX,[EAX + 0x1c]"
    },
    {
      "address": "00e780df",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00e780e0",
      "instruction": "CALL 0x00b72210"
    },
    {
      "address": "00e780e5",
      "instruction": "MOV ESI,EAX"
    },
    {
      "address": "00e780e7",
      "instruction": "MOV EAX,dword ptr [ESI + 0x360]"
    },
    {
      "address": "00e780ed",
      "instruction": "MOV ECX,dword ptr [ESI + 0x35c]"
    },
    {
      "address": "00e780f3",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00e780f4",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00e780f5",
      "instruction": "CALL 0x00e86980"
    },
    {
      "address": "00e780fa",
      "instruction": "MOV EAX,dword ptr [ESI + 0x364]"
    },
    {
      "address": "00e78100",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "00e78103",
      "instruction": "CMP EAX,-0x1"
    },
    {
      "address": "00e78106",
      "instruction": "JZ 0x00e7811e"
    },
    {
      "address": "00e78108",
      "instruction": "MOV EDX,dword ptr [0x016b3c04]"
    },
    {
      "address": "00e7810e",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00e7810f",
      "instruction": "MOV EAX,dword ptr [EDX + 0x4104]"
    },
    {
      "address": "00e78115",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00e78116",
      "instruction": "CALL 0x00bbbde0"
    },
    {
      "address": "00e7811b",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "00e7811e",
      "instruction": "CMP dword ptr [ESI + 0x248],0x0"
    },
    {
      "address": "00e78125",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00e78126",
      "instruction": "MOV BL,byte ptr [ESP + 0x24]"
    },
    {
      "address": "00e7812a",
      "instruction": "JZ 0x00e78148"
    },
    {
      "address": "00e7812c",
      "instruction": "MOV ECX,dword ptr [ESP + 0x2c]"
    },
    {
      "address": "00e78130",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00e78131",
      "instruction": "MOV EAX,EBP"
    },
    {
      "address": "00e78133",
      "instruction": "CALL 0x00e66010"
    },
    {
      "address": "00e78138",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "00e7813b",
      "instruction": "TEST BL,BL"
    },
    {
      "address": "00e7813d",
      "instruction": "JZ 0x00e78148"
    },
    {
      "address": "00e7813f",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00e78140",
      "instruction": "CALL 0x00e67890"
    },
    {
      "address": "00e78145",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "00e78148",
      "instruction": "MOV EAX,dword ptr [ESI + 0x370]"
    },
    {
      "address": "00e7814e",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00e78150",
      "instruction": "JZ 0x00e7815b"
    },
    {
      "address": "00e78152",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00e78153",
      "instruction": "CALL 0x00e59200"
    },
    {
      "address": "00e78158",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "00e7815b",
      "instruction": "TEST BL,BL"
    },
    {
      "address": "00e7815d",
      "instruction": "POP EBX"
    },
    {
      "address": "00e7815e",
      "instruction": "JZ 0x00e78212"
    },
    {
      "address": "00e78164",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00e78165",
      "instruction": "LEA ECX,[ESP + 0xc]"
    },
    {
      "address": "00e78169",
      "instruction": "CALL 0x00743b50"
    },
    {
      "address": "00e7816e",
      "instruction": "MOV EAX,dword ptr [ESI + 0x108]"
    },
    {
      "address": "00e78174",
      "instruction": "LEA EDX,[ESP + 0xc]"
    },
    {
      "address": "00e78178",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00e78179",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00e7817a",
      "instruction": "CALL 0x00e4cc40"
    },
    {
      "address": "00e7817f",
      "instruction": "MOV ECX,dword ptr [0x016b3c04]"
    },
    {
      "address": "00e78185",
      "instruction": "MOV EDX,dword ptr [ECX + 0x5190]"
    },
    {
      "address": "00e7818b",
      "instruction": "MOV EDX,dword ptr [EDX + 0x1c]"
    },
    {
      "address": "00e7818e",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "00e78191",
      "instruction": "MOV EDI,EAX"
    },
    {
      "address": "00e78193",
      "instruction": "CALL 0x00e4ee60"
    },
    {
      "address": "00e78198",
      "instruction": "SUB EAX,0x1"
    },
    {
      "address": "00e7819
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
  "original_bytes": 25012,
  "preview": "{\n  \"abi\": {\n    \"stack_cleanup_bytes\": 16\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:CellObjectData,CellResourceRef,OpaqueResourceScope\"\n      ],\n      \"package\": \"PKG-06-CELL-STATE\",\n      \"score\": 28,\n      \"symbol\": \"FUN_00e7a4a0\",\n      \"va\": \"0x00e7a4a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:CellObjectData,CellResourceRef\"\n      ],\n      \"package\": \"PKG-06-CELL-STATE\",\n      \"score\": 25,\n      \"symbol\": \"FUN_00e7a7c0\",\n      \"va\": \"0x00e7a7c0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:CellObjectData,CellResourceRef,ObservedObjectPool,OpaqueResourceScope\"\n      ],\n      \"package\": \"PKG-06-CELL-STATE\",\n      \"score\": 23,\n      \"symbol\": \"FUN_00e7fd00\",\n      \"va\": \"0x00e7fd00\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-06A-CELL-AI-SELECTION\",\n      \"score\": 6,\n      \"symbol\": \"cell_ai_select_profile_00e52910\",\n      \"va\": \"0x00e52910\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-11-H3-HELPER-WAVE2\",\n      \"score\": 3,\n      \"symbol\": \"embedded_object_first_word_init_00743b50\",\n      \"va\": \"0x00743b50\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Cell identity and old-identity release are preserved and are not merged with Cell GFX ordering; pool, callback, registry timing, and resource state remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"CellObjectData\",\n  \"cluster\": \"unknown-fun-mass\",\n  \"confidence\": 0.62,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"embedded_object_first_word_init_00743b50\",\n        \"reconstructed\": true,\n        \"va\": \"0x00743b50\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e771d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e78b20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e78b80\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e78c00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e78fc0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e791a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e79460\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e794f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e79720\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e7a0d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e7a160\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e7aa20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e7add0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e7b410\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e7b5d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e7b630\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e7b7c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e7b9b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e7bfb0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e7c080\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e7cd10\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e7d880\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e7df40\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00e775cf\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e771d0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e78b69\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e78b20\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e78bdd\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e78b80\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e78c32\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e78c00\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e78c90\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e78c00\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e78cc1\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e78c00\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsi
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
  "body_end": "00e78226",
  "body_span_bytes": 391,
  "body_start": "00e780a0",
  "callees": [
    "FUN_00e771d0",
    "thunk_FUN_00e823a0",
    "FUN_00e82130",
    "FUN_00e86980",
    "FUN_00e59200",
    "FUN_00e4ee60",
    "FUN_00e66010",
    "FUN_00b72260",
    "FUN_00b72210",
    "FUN_00b721d0",
    "FUN_00e67890",
    "thunk_FUN_00bbb210",
    "FUN_00743b50"
  ],
  "callers": [
    "FUN_00e771d0",
    "FUN_00e7b5d0",
    "FUN_00e78fc0",
    "FUN_00e7bfb0",
    "FUN_00e7a0d0",
    "FUN_00e78c00",
    "FUN_00e7df40",
    "FUN_00e7d880",
    "FUN_00e7b9b0",
    "FUN_00e7add0",
    "FUN_00e7b410",
    "FUN_00e7cd10",
    "FUN_00e7b630",
    "FUN_00e78b80",
    "FUN_00e7a160",
    "FUN_00e7c080",
    "FUN_00e79460",
    "FUN_00e78b20",
    "FUN_00e7aa20",
    "FUN_00e794f0",
    "FUN_00e79720",
    "FUN_00e7b7c0",
    "FUN_00e791a0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00e780a0",
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
      "storage": "Stack[-0x10]:1",
      "type": "undefined"
    },
    {
      "name": "local_28",
      "storage": "Stack[-0x28]:4",
      "type": "undefined4"
    },
    {
      "name": "local_34",
      "storage": "Stack[-0x34]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 6,
  "mode": "live",
  "name": "FUN_00e780a0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xa780a0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00e780a0(void)",
  "size_bytes": 391,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00e780a0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 27,
  "xrefs": [
    {
      "from": "00e775cf"
    },
    {
      "from": "00e7b793"
    },
    {
      "from": "00e7c3e1"
    },
    {
      "from": "00e78c32"
    },
    {
      "from": "00e78c90"
    },
    {
      "from": "00e78cc1"
    },
    {
      "from": "00e7c037"
    },
    {
      "from": "00e78b69"
    },
    {
      "from": "00e78bdd"
    },
    {
      "from": "00e7aa58"
    },
    {
      "from": "00e79783"
    },
    {
      "from": "00e7cd9c"
    },
    {
      "from": "00e7b88d"
    },
    {
      "from": "00e7b615"
    },
    {
      "from": "00e791d9"
    },
    {
      "from": "00e7b463"
    },
    {
      "from": "00e7aebe"
    },
    {
      "from": "00e7dfcf"
    },
    {
      "from": "00e7b9c2"
    },
    {
      "from": "00e795db"
    },
    {
      "from": "00e794d8"
    },
    {
      "from": "00e7a183"
    },
    {
      "from": "00e790d7"
    },
    {
      "from": "00e7a131"
    },
    {
      "from": "00e7a149"
    },
    {
      "from": "00e7d919"
    },
    {
      "from": "00e7da29"
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
    "reconstruction/metadata/pkg06-cell-state/00e780a0.json"
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
    "cell_object_lifetime_observation"
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
  "original_bytes": 12527,
  "preview": "{\n  \"category\": null,\n  \"classification\": \"NEEDS_RUNTIME\",\n  \"confidence\": {\n    \"overall\": \"SUPPORTED\"\n  },\n  \"contradictions\": [],\n  \"downstream_unlock_count\": 36,\n  \"evidence\": [\n    {\n      \"independent_limit\": \"Parameter names and replacement semantics are inferred.\",\n      \"kind\": \"direct_decompilation\",\n      \"source\": \"Ghidra MCP:SporeApp.exe@0x00e780a0\",\n      \"supports\": [\n        \"validity guard\",\n        \"avatar clear\",\n        \"query/GFX/child cleanup\",\n        \"scale replacement\",\n        \"unconditional old release\"\n      ]\n    },\n    {\n      \"independent_limit\": \"Same binary source; assembly cross-check only.\",\n      \"kind\": \"disassembly\",\n      \"source\": \"Ghidra MCP:SporeApp.exe@0x00e780a0\",\n      \"supports\": [\n        \"+0x248 detach branch\",\n        \"+0x370 child branch\",\n        \"mScale comparison\",\n        \"tail FUN_00b72260 release\",\n        \"stack/register behavior\"\n      ]\n    },\n    {\n      \"independent_limit\": \"Static callers do not identify runtime reason per call.\",\n      \"kind\": \"callgraph_xrefs\",\n      \"source\": \"Ghidra MCP:SporeApp.exe@xrefs@0x00e780a0\",\n      \"supports\": [\n        \"23 direct callers spanning lifecycle/interaction/frame/population/rebuild\",\n        \"13 direct callees\"\n      ]\n    },\n    {\n      \"independent_limit\": \"Child/field names are generic.\",\n      \"kind\": \"structure_layout\",\n      \"source\": \"Ghidra MCP:SporeApp.exe@structure:cCellObjectData\",\n      \"supports\": [\n        \"920-byte Cell\",\n        \"+0x108 resource, +0x248 GFX, +0x358 scale, +0x35c query, +0x370 child relation\"\n      ]\n    },\n    {\n      \"independent_limit\": \"Does not prove every runtime sequence.\",\n      \"kind\": \"sibling_lifecycle_evidence\",\n      \"source\": \"Ghidra MCP:SporeApp.exe@0x00e66010 and @0x00e6d8f0\",\n      \"supports\": [\n        \"detach-only versus same-cell GFX rebuild distinction\",\n        \"GFX record is not Cell identity\"\n      ]\n    },\n    {\n      \"independent_limit\": \"Secondary static artifact.\",\n      \"kind\": \"committed_architecture_artifact\",\n      \"source\": \"knowledgegraph/research/architecture-resolution/followup-04-cell-boundary.json:162-187\",\n      \"supports\": [\n        \"23 callers\",\n        \"identity-destructive despawn\",\n        \"replacement is not old identity\"\n      ]\n    }\n  ],\n  \"family\": \"cell_despawn_and_scale_aware_replacement\",\n  \"interfaces\": {\n    \"boundaries\": {\n      \"boundary_rule\": \"The helper is identity-destructive for old Cells; a replacement is new even when content fields are reused.\",\n      \"classification\": \"cross_boundary\",\n      \"inbound\": \"Death, interaction, population, query, scale, and frame cleanup callers\",\n      \"outbound\": [\n        \"simulation pool release\",\n        \"query unlink\",\n        \"GFX detach\",\n        \"child release\",\n        \"scale-aware replacement/child population\",\n        \"visual effect\"\n      ]\n    },\n    \"direct_callees\": [\n      {\n        \"role\": \"validity lookup\",\n        \"va\": \"0x00b721d0\"\n      },\n      {\n        \"role\": \"Cell lookup\",\n        \"va\": \"0x00b72210\"\n      },\n      {\n        \"role\": \"query/linked-state cleanup\",\n        \"va\": \"0x00e86980\"\n      },\n      {\n        \"role\": \"linked object/pool cleanup\",\n        \"va\": \"0x00bbb210\"\n      },\n      {\n        \"role\": \"per-cell GFX detach\",\n        \"va\": \"0x00e66010\"\n      },\n      {\n        \"role\": \"scale-dependent effect\",\n        \"va\": \"0x00e67890\"\n      },\n      {\n        \"role\": \"related child release\",\n        \"va\": \"0x00e59200\"\n      },\n      {\n        \"role\": \"scale-aware replacement/child population\",\n        \"va\": \"0x00e771d0\"\n      },\n      {\n        \"role\": \"current player scale lookup\",\n        \"va\": \"0x00e4ee60\"\n      },\n      {\n        \"role\": \"resource context guard\",\n        \"va\": \"0x00743b50\"\n      },\n      {\n        \"role\": \"resource/reference cleanup\",\n        \"va\": \"0x00e82130\"\n      },\n      {\n        \"role\": \"old Cell pool release\",\n        \"va\": \"0x00b72260\"\n      }\n    ],\n    \"direct_callers\": [\n      \"0x00e78c00 FUN_00e78c00\",\n      \"0x00e78b20 FUN_00e78b20\",\n      \"0x00e78b80 FUN_00e78b80\",\n      \"0x00e78fc0 FUN_00e78fc0\",\n      \"0x00e791a0 FUN_00e791a0\",\n      \"0x00e79460 FUN_00e79460\",\n      \"0x00e794f0 FUN_00e794f0\",\n      \"0x00e79720 FUN_00e79720\",\n      \"0x00e7a0d0 FUN_00e7a0d0\",\n      \"0x00e7a160 FUN_00e7a160\",\n      \"0x00e7aa20 FUN_00e7aa20\",\n      \"0x00e7add0 FUN_00e7add0\"\n    ],\n    \"globals\": [],\n    \"structures\": [],\n    \"vtables\": [],\n    \"worker_contract_surface\": {\n      \"failure_behavior\": {\n        \"invalid_index\": \"Returns without mutation when pool lookup is null.\",\n        \"missing_child\": \"Skips FUN_00e59200 when field_370 is zero.\",\n        \"missing_gfx\": \"Skips GFX detach when mGFXObjectIndex is zero and still releases the Cell.\",\n        \"replacement_failure\": \"No status is returned from FUN_00e771d0; old Cell release still occurs.\",\n        \"resource_failure\": \"No explicit null check exists for resource/model before optional scale-aware work.\"\n      },\n      \"identity_boundary\": \"not_reported\",\n      \"inputs\": [],\n      \"ordering\": [],\n      \"outputs\": [],\n      \"postconditions\": [\n        \"Matching avatar index is cleared to zero.\",\n        \"Cell is unlinked from query/linked state through FUN_00e86980 and related helpers.\",\n        \"If mGFXObjectIndex is nonzero, GFX association is detached through FUN_00e66010.\",\n        \"If replaceIfScaled is nonzero, FUN_00e67890 may play a scale-dependent Cell effect.\",\n        \"If field_370 references a 
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
  "CellResourceRef",
  "ObservedObjectPool",
  "OpaqueResourceScope",
  "float",
  "std::int32_t",
  "std::uint32_t",
  "std::uint8_t",
  "void"
]
```

## vtables

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## Conflicts

```json
{
  "original_bytes": 9017,
  "preview": "[\n  {\n    \"anchors\": [\n      \"0x00e74a20\",\n      \"0x00e57460\",\n      \"0x00e6d200\",\n      \"0x00e57340\",\n      \"0x00e780a0\",\n      \"0x00000108\",\n      \"0x00e74a20\",\n      \"0x00000108\"\n    ],\n    \"conflict_id\": \"TB-FL-012\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": {\n      \"merge_decision\": \"separate_entities\",\n      \"preferred_claim\": \"Use the original direct field/body evidence as the ABI anchor.\",\n      \"preserved_alternatives\": true,\n      \"scope_note\": \"The current padding is a replacement limitation and cannot define the original structure.\",\n      \"status\": \"preferred_claim_with_limit\",\n      \"taxonomy\": \"preferred_claim_with_limit\"\n    },\n    \"resolution_status\": \"preferred_claim_with_limit\",\n    \"source\": \"knowledgegraph/research/conflicts/track-b-vtable-fields.json\",\n    \"subject\": \"cCellObjectData original middle fields versus current opaque padding\",\n    \"unresolved_reason\": \"The cited static evidence leaves the competing owner, slot, layout, or lifecycle interpretation unresolved; no positive original runtime or MSVC RTTI evidence is available.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00e62340\",\n      \"0x00e780a0\",\n      \"0x00e7a7c0\",\n      \"0x00e806b0\",\n      \"0x00e7a7c0\",\n      \"0x00e62340\",\n      \"0x00e780a0\",\n      \"0x00e806b0\",\n      \"0x00e7fd00\",\n      \"0x00e74a20\",\n      \"0x00e780a0\",\n      \"0x00e74a20\",\n      \"0x00e74a20\",\n      \"0x00e4ce20\",\n      \"0x00e5b790\",\n      \"0x00e665c0\"\n    ],\n    \"conflict_id\": \"U-003-cell-respawn-policy\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"Damage/death branches, despawn cleanup, optional scale replacement, and deferred stage rebuild are concrete. Caller-specific respawn policy and replacement ordering are unresolved.\",\n    \"resolution_status\": \"Damage/death branches, despawn cleanup, optional scale replacement, and deferred stage rebuild are concrete. Caller-specific respawn policy and replacement ordering are unresolved.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00eedd40\",\n      \"0x00e7fd00\",\n      \"0x00e74a20\",\n      \"0x00e74a20\",\n      \"0x00e5b790\",\n      \"0x00e80ba0\",\n      \"0x00b72370\",\n      \"0x00b72320\",\n      \"0x00e780a0\",\n      \"0x00b72160\",\n      \"0x00b72260\",\n      \"0x00b72270\",\n      \"0x00b72370\",\n      \"0x00bb4100\",\n      \"0x00bb42a0\"\n    ],\n    \"conflict_id\": \"U-008-scenario-respawner\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The cited direct body establishes a bounded state mutation or call anchor, but the full transition policy, consumer order, and runtime reachability remain unresolved.\",\n    \"resolution_status\": \"The cited direct body establishes a bounded state mutation or call anchor, but the full transition policy, consumer order, and runtime reachability remain unresolved.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00e62340\",\n      \"0x00e780a0\",\n      \"0x00e7a7c0\",\n      \"0x00e806b0\",\n      \"0x00e7a7c0\",\n      \"0x00e62340\",\n      \"0x00e780a0\",\n      \"0x00e806b0\",\n      \"0x00e62200\",\n      \"0x00e62200\",\n      \"0x00e62340\",\n      \"0x00e62340\",\n      \"0x007d8c80\"\n    ],\n    \"conflict_id\": \"U-CELL-ROLLOVER\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"Rollover creation is guarded by GFX presence, receives a health-derived value, and receives mDisappearTime=0.5. Expiry, hide, reuse, and release order are unresolved.\",\n    \"resolution_status\": \"Rollover creation is guarded by GFX presence, receives a health-derived value, and receives mDisappearTime=0.5. Expiry, hide, reuse, and release order are unresolved.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00e80ba0\",\n      \"0xffffffff\",\n      \"0x00e80ba0\",\n      \"0x00e74a20\",\n      \"0x00e780a0\",\n      \"0x00b721d0\",\n      \"0x00b72260\",\n      \"0x00e771d0\",\n      \"0x00e7d370\",\n      \"0xffffffff\",\n      \"0xffffffff\",\n      \"0xffffffff\"\n    ],\n    \"conflict_id\": \"U1\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [\n      {\n        \"path\": \"e
[TRUNCATED]
```
