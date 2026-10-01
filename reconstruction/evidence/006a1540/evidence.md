# Evidence 0x006a1540

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `a4a98ff51009a9a178b1301b963669b2e81fa90ef221dcfc2473ff7c070ed541`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_this": true,
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": 1,
  "ordinary_stack_arguments": [
    "{'entry_offset': 'entry_ESP+0x4', 'observed': True, 'ordinal': 1, 'read': True, 'read_at': '0x006a1543 MOV EBP,dword ptr [ESP + 0x10] (three pushes precede it, so [ESP+0x10] is entry_ESP+0x4)', 'role': 'an IStream-shaped sink. The body never dereferences it; it is only ever pushed as the first argument of the three direct calls (0x006a156a, 0x006a15b3, 0x006a15cf).', 'sizes': [4], 'written': False}"
  ],
  "receiver_register": "ECX",
  "ret_form": "RET 0x4",
  "return_register": "EAX",
  "saved_registers": [
    "ESI",
    "EBP",
    "EBX",
    "EDI"
  ],
  "stack_arguments": [
    {
      "entry_offset": "entry_ESP+0x4",
      "ordinal": 1,
      "read": true,
      "read_at": "0x006a1543 MOV EBP,dword ptr [ESP + 0x10]",
      "role": "an IStream-shaped sink. Never dereferenced by this body; pushed only as the first argument of the three direct calls (0x006a156a, 0x006a15b3, 0x006a15cf). The live Ghidra signature types it IStream *, which is recorded here and not adopted: no record for this target establishes that class.",
      "written": false
    }
  ],
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "callee",
  "termination": "RET 0x4"
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
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x4",
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
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "stack_cleanup_bytes": 4,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x4"
  },
  "abstained_because": [],
  "cleanup": {
    "bytes": 4,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x4",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "4886d887cf1cbc0056e752bb3f6477c32b6d9cf5913daf131ddc3999de20631c",
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
    "ghidra_parameter_count": 2,
    "persisted": "agrees",
    "persisted_calling_convention": "__thiscall"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0033"
      ],
      "claim": "the callee pops 4 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 4,
        "side": "callee"
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0021",
        "obs-0027"
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
        "obs-0001",
        "obs-0009",
        "obs-0010",
        "obs-0013",
        "obs-0023",
        "obs-0032"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          24,
          28
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0009",
        "obs-0010",
        "obs-0013",
        "obs-0023",
        "obs-0032",
        "obs-0033"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0033"
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
        "obs-0033"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0033"
      ],
      "claim": "the last value written to EAX classifies as integral",
      "confidence": "INFERRED",
      "id": "RT2",
      "value": {
        "register_class": "integral"
      }
    }
  ],
  "observations": [
    {
      "at": "0x006a1540",
      "count": 6,
      "first_use": 0,
      "first_write_index": 6,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ECX",
      "reg": "ECX"
    },
    {
      "at": "0x006a1541",
      "count": 1,
      "first_use": 1,
      "first_write_index": 23,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x006a1542",
      "count": 4,
      "first_use": 2,
      "first_write_index": 3,
      "id": "obs-0003",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH EBP",
      "reg": "EBP"
    },
    {
      "and_esp": null,
      "at": "0x006a1542",
      "ebp_is_general_register": false,
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
      "at": "0x006a1543",
      "count": 7,
      "first_use": 3,
      "first_write_index": 30,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV EBP,dword ptr [ESP + 0x10]",
      "reg": "ESP"
    },
    {
      "at": "0x006a1543",
      "base": "ESP",
      "disp": 16,
      "id": "obs-0006",
      "index": 3,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EBP,dword ptr [ESP + 0x10]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x006a1543",
      "definite": true,
      "id": "obs-0007",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV EBP,dword ptr [ESP + 0x10]",
      "reg": "EBP",
      "write_kind": "mem_load"
    },
    {
      "at": "0x006a1547",
      "count": 7,
      "first_use": 4,
      "first_write_index": 5,
      "id": "obs-0008",
      "index": 4,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
     
[TRUNCATED]
```

## callees_dependencies

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## callers_dependencies

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## contradictions

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "original_bytes": 12946,
  "preview": "[\n  {\n    \"anchors\": [\n      \"0x006a2f60\",\n      \"0x006a1540\",\n      \"0x00000000\",\n      \"0x006a2f60\",\n      \"0x00000018\",\n      \"0x006a2f60\",\n      \"0x006a1540\"\n    ],\n    \"conflict_id\": \"TB-FL-006\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": {\n      \"merge_decision\": \"do_not_collapse\",\n      \"preferred_claim\": null,\n      \"preserved_alternatives\": true,\n      \"scope_note\": \"No 4-byte or 0x14-byte layout is a wire contract until the direct reader/writer and stride are observed.\",\n      \"status\": \"preserved_alternatives\",\n      \"taxonomy\": \"preserved_alternatives\"\n    },\n    \"resolution_status\": \"preserved_alternatives\",\n    \"source\": \"knowledgegraph/research/conflicts/track-b-vtable-fields.json\",\n    \"subject\": \"App::Property 4-byte versus 0x14-byte layout\",\n    \"unresolved_reason\": \"The cited static evidence leaves the competing owner, slot, layout, or lifecycle interpretation unresolved; no positive original runtime or MSVC RTTI evidence is available.\"\n  },\n  {\n    \"anchors\": [\n      \"0x006a1540\",\n      \"0x006a2f60\",\n      \"0x00693390\",\n      \"0x00694440\",\n      \"0x00422e20\",\n      \"0x00422eb0\",\n      \"0x00422f40\",\n      \"0x006a3890\",\n      \"0x006a0f70\",\n      \"0x006a3510\",\n      \"0x006a1540\",\n      \"0x006a1540\",\n      \"0x006a15a4\",\n      \"0x006a15d5\",\n      \"0x00422eb0\",\n      \"0x00422eb0\"\n    ],\n    \"conflict_id\": \"TD-DATA-002\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [\n      {\n        \"path\": \"competing_hypotheses.1.claim\",\n        \"status\": \"rejected_by_inline_control_flow     \",\n        \"text\": \"The runtime Property is only 4 bytes and the SDK 0x14-byte record is a declaration defect or unrelated wrapper.\"\n      }\n    ],\n    \"resolution\": null,\n    \"resolution_status\": null,\n    \"source\": \"knowledgegraph/research/conflicts/track-d-data-serialization.json\",\n    \"subject\": \"Property 4-byte versus 20-byte layout and typed value codec\",\n    \"unresolved_reason\": [\n      \"Unknown Property type payloads and array/pointer encodings are not all directly recovered.\",\n      \"The outer PROP record and migration behavior remain separate unresolved questions.\"\n    ]\n  },\n  {\n    \"anchors\": [\n      \"0x006a1540\",\n      \"0x006a2f60\",\n      \"0x006a2e20\",\n      \"0x006a2530\",\n      \"0x006a2b80\",\n      \"0x006a2c50\",\n      \"0x00694440\",\n      \"0x006a1540\",\n      \"0x006a1540\",\n      \"0x006a154a\",\n      \"0x006a15f3\",\n      \"0x006a2f60\",\n      \"0x006a2f60\",\n      \"0x006a2f78\",\n      \"0x006a2fe9\",\n      \"0x006a2f60\"\n    ],\n    \"conflict_id\": \"TD-DATA-003\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [\n      {\n        \"path\": \"competing_hypotheses.1.claim\",\n        \"status\": \"rejected_for_current_read_write_bodies     \",\n        \"text\": \"PropertyList Write serializes the entire recursive parent graph as ordinary local entries.\"\n      }\n    ],\n    \"resolution\": null,\n    \"resolution_status\": null,\n    \"source\": \"knowledgegraph/research/conflicts/track-d-data-serialization.json\",\n    \"subject\": \"PropertyList local transfer, parent reference, and PROP framing\",\n    \"unresolved_reason\": [\n      \"The exact three-word parent identity and its manager-side construction are not fully identified.\",\n      \"Outer record envelope, version negotiation, compression, and atomic rollback are not established by the selected bodies.\"\n    ]\n  },\n  {\n    \"anchors\": [\n      \"0x00e63d10\",\n      \"0x00e80ba0\",\n      \"0x00e819b0\",\n      \"0x00e63d10\",\n      \"0x00e819b0\",\n      \"0x00e80ba0\",\n      \"0x013c7d90\",\n      \"0x013c7d90\",\n      \"0x00693900\",\n      \"0x00693900\",\n      \"0x00693d60\",\n      \"0x00693d60\",\n      \"0x006a1540\",\n      \"0x006a2f60\",\n      \"0x006a1540\",\n      \"0x006a2f60\"\n    ],\n    \"conflict_id\": \"cell_cross_stage_handoff\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The global serializable-data handoff is concrete around Cell reset/reinitialization. Cross-mode/stage handoff is not established.\",\n    \"resolution_status\": \"The global serializable-data handoff is concrete around Cell reset/reinitialization. Cross-mode/stage handoff is not established.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00b28ec0\",\n      \"0x00b294c0\",\n      \"0x00bb4ba0\",\n      \"0x00bb4ba0\",\n      \"0x00693900\",\n      \"0x00693900\",\n      \"0x00693900\",\n      \"0x00693900\",\n      \"0x00693d60\",\n      \"0x00693d60\",\n      \"0x00693d60\",\n      \"0x00693d60\",\n      \"0x006a1540\",\n      \"0x006a2f60\",\n      \"0x006a1540\",\n      \"0x006a2f60\"\n    ],\n    \"conflict_id\": \"cross_file_atomicity\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"stars.db.tmp write and replacement are concrete. No transaction boundary is claimed for the full .spo/profile set.\",\n    \"resolution_status\": \"stars.db.tmp write and replacement are concrete. No transaction boundary is claimed for the full .spo/profile set.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00b282e0\",\n      \"0x00b28750\",\n      \"0x00bb8b20\",\n      \"0x00b282e0\",\n      \"0x00693900\",\n      \"0x00693900\",\n      \"0x00693900\",\n      \"0x00693900\",\n      \"0x00693d60\",\n      \"0x00693d60\",
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
  "count": 74,
  "instructions": [
    {
      "address": "006a1540",
      "instruction": "PUSH ECX"
    },
    {
      "address": "006a1541",
      "instruction": "PUSH EBX"
    },
    {
      "address": "006a1542",
      "instruction": "PUSH EBP"
    },
    {
      "address": "006a1543",
      "instruction": "MOV EBP,dword ptr [ESP + 0x10]"
    },
    {
      "address": "006a1547",
      "instruction": "PUSH ESI"
    },
    {
      "address": "006a1548",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "006a154a",
      "instruction": "MOV ECX,dword ptr [ESI + 0x1c]"
    },
    {
      "address": "006a154d",
      "instruction": "SUB ECX,dword ptr [ESI + 0x18]"
    },
    {
      "address": "006a1550",
      "instruction": "MOV EAX,0x2aaaaaab"
    },
    {
      "address": "006a1555",
      "instruction": "IMUL ECX"
    },
    {
      "address": "006a1557",
      "instruction": "SAR EDX,0x2"
    },
    {
      "address": "006a155a",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "006a155c",
      "instruction": "MOV EAX,EDX"
    },
    {
      "address": "006a155e",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "006a1560",
      "instruction": "LEA ECX,[ESP + 0x14]"
    },
    {
      "address": "006a1564",
      "instruction": "SHR EAX,0x1f"
    },
    {
      "address": "006a1567",
      "instruction": "PUSH ECX"
    },
    {
      "address": "006a1568",
      "instruction": "ADD EAX,EDX"
    },
    {
      "address": "006a156a",
      "instruction": "PUSH EBP"
    },
    {
      "address": "006a156b",
      "instruction": "MOV dword ptr [ESP + 0x1c],EAX"
    },
    {
      "address": "006a156f",
      "instruction": "CALL 0x0093aa70"
    },
    {
      "address": "006a1574",
      "instruction": "MOV ECX,dword ptr [ESI + 0x1c]"
    },
    {
      "address": "006a1577",
      "instruction": "SUB ECX,dword ptr [ESI + 0x18]"
    },
    {
      "address": "006a157a",
      "instruction": "MOV BL,AL"
    },
    {
      "address": "006a157c",
      "instruction": "MOV EAX,0x2aaaaaab"
    },
    {
      "address": "006a1581",
      "instruction": "IMUL ECX"
    },
    {
      "address": "006a1583",
      "instruction": "SAR EDX,0x2"
    },
    {
      "address": "006a1586",
      "instruction": "MOV EAX,EDX"
    },
    {
      "address": "006a1588",
      "instruction": "SHR EAX,0x1f"
    },
    {
      "address": "006a158b",
      "instruction": "ADD EAX,EDX"
    },
    {
      "address": "006a158d",
      "instruction": "ADD ESP,0x10"
    },
    {
      "address": "006a1590",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "006a1592",
      "instruction": "JLE 0x006a15ed"
    },
    {
      "address": "006a1594",
      "instruction": "PUSH EDI"
    },
    {
      "address": "006a1595",
      "instruction": "XOR EDI,EDI"
    },
    {
      "address": "006a1597",
      "instruction": "MOV dword ptr [ESP + 0x18],EAX"
    },
    {
      "address": "006a159b",
      "instruction": "JMP 0x006a15a0"
    },
    {
      "address": "006a15a0",
      "instruction": "TEST BL,BL"
    },
    {
      "address": "006a15a2",
      "instruction": "JZ 0x006a15e0"
    },
    {
      "address": "006a15a4",
      "instruction": "MOV EDX,dword ptr [ESI + 0x18]"
    },
    {
      "address": "006a15a7",
      "instruction": "MOV EAX,dword ptr [EDI + EDX*0x1]"
    },
    {
      "address": "006a15aa",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "006a15ac",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "006a15ae",
      "instruction": "LEA ECX,[ESP + 0x18]"
    },
    {
      "address": "006a15b2",
      "instruction": "PUSH ECX"
    },
    {
      "address": "006a15b3",
      "instruction": "PUSH EBP"
    },
    {
      "address": "006a15b4",
      "instruction": "MOV dword ptr [ESP + 0x20],EAX"
    },
    {
      "address": "006a15b8",
      "instruction": "CALL 0x0093aa70"
    },
    {
      "address": "006a15bd",
      "instruction": "ADD ESP,0x10"
    },
    {
      "address": "006a15c0",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "006a15c2",
      "instruction": "JZ 0x006a15e0"
    },
    {
      "address": "006a15c4",
      "instruction": "MOV EAX,dword ptr [ESI + 0x18]"
    },
    {
      "address": "006a15c7",
      "instruction": "ADD EAX,EDI"
    },
    {
      "address": "006a15c9",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "006a15cb",
      "instruction": "ADD EAX,0x4"
    },
    {
      "address": "006a15ce",
      "instruction": "PUSH EAX"
    },
    {
      "address": "006a15cf",
      "instruction": "PUSH EBP"
    },
    {
      "address": "006a15d0",
      "instruction": "CALL 0x00693390"
    },
    {
      "address": "006a15d5",
      "instruction": "ADD ESP,0xc"
    },
    {
      "address": "006a15d8",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "006a15da",
      "instruction": "JZ 0x006a15e0"
    },
    {
      "address": "006a15dc",
      "instruction": "MOV BL,0x1"
    },
    {
      "address": "006a15de",
      "instruction": "JMP 0x006a15e2"
    },
    {
      "address": "006a15e0",
      "instruction": "XOR BL,BL"
    },
    {
      "address": "006a15e2",
      "instruction": "ADD EDI,0x18"
    },
    {
      "address": "006a15e5",
      "instruction": "SUB dword ptr [ESP + 0x18],0x1"
    },
    {
      "address": "006a15ea",
      "instruction": "JNZ 0x006a15a0"
    },
    {
      "address": "006a15ec",
      "instruction": "POP EDI"
    },
    {
      "address": "006a15ed",
      "instruction": "POP ESI"
    },
    {
      "address": "006a15ee",
      "instruction": "POP EBP"
    },
    {
      "address": "006a15ef",
      "instruction": "MOV AL,BL"
    },
    {
      "address": "006a15f1",
      "instruction": "POP EBX"
    },
    {
      "address": "006a15f2",
      "instruction": "POP ECX"
    },
    {
      "address": "006a15f3",
      "instruction": "RET 0x4"
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
  "original_bytes": 14806,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": 1,\n    \"ordinary_stack_arguments\": [\n      \"{'entry_offset': 'entry_ESP+0x4', 'observed': True, 'ordinal': 1, 'read': True, 'read_at': '0x006a1543 MOV EBP,dword ptr [ESP + 0x10] (three pushes precede it, so [ESP+0x10] is entry_ESP+0x4)', 'role': 'an IStream-shaped sink. The body never dereferences it; it is only ever pushed as the first argument of the three direct calls (0x006a156a, 0x006a15b3, 0x006a15cf).', 'sizes': [4], 'written': False}\"\n    ],\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET 0x4\",\n    \"return_register\": \"EAX\",\n    \"saved_registers\": [\n      \"ESI\",\n      \"EBP\",\n      \"EBX\",\n      \"EDI\"\n    ],\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"entry_ESP+0x4\",\n        \"ordinal\": 1,\n        \"read\": true,\n        \"read_at\": \"0x006a1543 MOV EBP,dword ptr [ESP + 0x10]\",\n        \"role\": \"an IStream-shaped sink. Never dereferenced by this body; pushed only as the first argument of the three direct calls (0x006a156a, 0x006a15b3, 0x006a15cf). The live Ghidra signature types it IStream *, which is recorded here and not adopted: no record for this target establishes that class.\",\n        \"written\": false\n      }\n    ],\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"RET 0x4\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x01408820\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-app-proplist-copyall-wave16\",\n      \"score\": 12,\n      \"symbol\": \"all_copy_from_properties_006a14d0\",\n      \"va\": \"0x006a14d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x01408820\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-property-clear-wave13\",\n      \"score\": 12,\n      \"symbol\": \"property_list_clear_006a2a80\",\n      \"va\": \"0x006a2a80\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x01408820\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-property-remove-006a2ef0\",\n      \"score\": 12,\n      \"symbol\": \"property_list_remove_property_006a2ef0\",\n      \"va\": \"0x006a2ef0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-direct-property-clear-wave14\",\n      \"score\": 8,\n      \"symbol\": \"direct_property_list_clear_006a2b20\",\n      \"va\": \"0x006a2b20\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01408820\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-PROPERTY-SAFE-WAVE9\",\n      \"score\": 6,\n      \"symbol\": \"property_list_copy_from_006a2a40\",\n      \"va\": \"0x006a2a40\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01408820\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-PROPERTY-SAFE-WAVE9\",\n      \"score\": 6,\n      \"symbol\": \"property_list_get_property_ids_006a3070\",\n      \"va\": \"0x006a3070\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01408820\"\n      ],\n      \"package\": \"wave6-resources\",\n      \"score\": 4,\n      \"symbol\": \"property_list_has_property_006a2470\",\n      \"va\": \"0x006a2470\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01408820\"\n      ],\n      \"package\": \"wave6-resources\",\n      \"score\": 4,\n      \"symbol\": \"property_list_get_property_object_006a24d0\",\n      \"va\": \"0x006a24d0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": null,\n  \"cluster\": \"app-lifecycle\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x006a15d0\",\n        \"direction\": \"out\",\n        \"other\": \"0x00693390\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006a156f\",\n        \"direction\": \"out\",\n        \"other\": \"0x0093aa70\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006a15b8\",\n        \"direction\": \"out\",\n        \"other\": \"0x0093aa70\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0200\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"CONFIRMED\",\n  \"globals\": [\n    \"global:PASS\",\n    \"global:PASS. The complete listing names no data-segment address and the span names none.\",\n    \"global:none: the complete 74-instruction listing names no data-segment address.\"\n  ],\n  \"integration_status\": \"integrated\",\n  \"name\": \"App::PropertyList::Write\",\n  \"normalized_symbol\": \"proplist_write_006a1540\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"do_not_claim\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": \"pkg-dfw-006a1540\",\n    \"queue_state\": \"queued\"\n  },\n  \"package\": \"pkg-dfw-006a1540\",\n  
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
  "body_end": "006a15f5",
  "body_span_bytes": 182,
  "body_start": "006a1540",
  "callees": [
    "FUN_0093aa70",
    "FUN_00693390"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "006a1540",
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
    }
  ],
  "locals_count": 1,
  "mode": "live",
  "name": "App::PropertyList::Write",
  "namespace": "App",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 2,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "DirectPropertyList *"
    },
    {
      "name": "pOutputStream",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "IStream *"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "bool",
  "return_type_resolved": true,
  "rva": "0x2a1540",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "bool App::PropertyList::Write(DirectPropertyList * this, IStream * pOutputStream)",
  "size_bytes": 182,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x006a1540",
  "vtables": {
    "referenced_by_vtables": [
      "0x01408820"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 2,
  "xrefs": [
    {
      "from": "01408860"
    },
    {
      "from": "006a1640"
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
  "global:PASS",
  "global:PASS. The complete listing names no data-segment address and the span names none.",
  "global:none: the complete 74-instruction listing names no data-segment address."
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__Write.c",
  "file": "src/reconstruction/pkg_dfw_006a1540/dfw_006a1540.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__Write.c",
    "reconstruction/staging/pkg-dfw-006a1540/dfw_006a1540.cpp",
    "reconstruction/staging/pkg-dfw-006a1540/dfw_006a1540_types.hpp",
    "reconstruction/staging/pkg-proplist-write-wave16/proplist_write_006a1540.cpp",
    "reconstruction/staging/pkg-proplist-write-wave16/proplist_write_006a1540.hpp",
    "reconstruction/staging/pkg-proplist-write-wave16/proplist_write_006a1540_model_test.cpp",
    "src/reconstruction/pkg_dfw_006a1540/dfw_006a1540.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-dfw-006a1540/006a1540.json",
    "reconstruction/metadata/pkg-proplist-write-wave16/006a1540.json"
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
  "gates": [],
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
  "runtime_gated": false,
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
  "bool"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x01408820"
]
```

## Conflicts

```json
{
  "original_bytes": 12946,
  "preview": "[\n  {\n    \"anchors\": [\n      \"0x006a2f60\",\n      \"0x006a1540\",\n      \"0x00000000\",\n      \"0x006a2f60\",\n      \"0x00000018\",\n      \"0x006a2f60\",\n      \"0x006a1540\"\n    ],\n    \"conflict_id\": \"TB-FL-006\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": {\n      \"merge_decision\": \"do_not_collapse\",\n      \"preferred_claim\": null,\n      \"preserved_alternatives\": true,\n      \"scope_note\": \"No 4-byte or 0x14-byte layout is a wire contract until the direct reader/writer and stride are observed.\",\n      \"status\": \"preserved_alternatives\",\n      \"taxonomy\": \"preserved_alternatives\"\n    },\n    \"resolution_status\": \"preserved_alternatives\",\n    \"source\": \"knowledgegraph/research/conflicts/track-b-vtable-fields.json\",\n    \"subject\": \"App::Property 4-byte versus 0x14-byte layout\",\n    \"unresolved_reason\": \"The cited static evidence leaves the competing owner, slot, layout, or lifecycle interpretation unresolved; no positive original runtime or MSVC RTTI evidence is available.\"\n  },\n  {\n    \"anchors\": [\n      \"0x006a1540\",\n      \"0x006a2f60\",\n      \"0x00693390\",\n      \"0x00694440\",\n      \"0x00422e20\",\n      \"0x00422eb0\",\n      \"0x00422f40\",\n      \"0x006a3890\",\n      \"0x006a0f70\",\n      \"0x006a3510\",\n      \"0x006a1540\",\n      \"0x006a1540\",\n      \"0x006a15a4\",\n      \"0x006a15d5\",\n      \"0x00422eb0\",\n      \"0x00422eb0\"\n    ],\n    \"conflict_id\": \"TD-DATA-002\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [\n      {\n        \"path\": \"competing_hypotheses.1.claim\",\n        \"status\": \"rejected_by_inline_control_flow     \",\n        \"text\": \"The runtime Property is only 4 bytes and the SDK 0x14-byte record is a declaration defect or unrelated wrapper.\"\n      }\n    ],\n    \"resolution\": null,\n    \"resolution_status\": null,\n    \"source\": \"knowledgegraph/research/conflicts/track-d-data-serialization.json\",\n    \"subject\": \"Property 4-byte versus 20-byte layout and typed value codec\",\n    \"unresolved_reason\": [\n      \"Unknown Property type payloads and array/pointer encodings are not all directly recovered.\",\n      \"The outer PROP record and migration behavior remain separate unresolved questions.\"\n    ]\n  },\n  {\n    \"anchors\": [\n      \"0x006a1540\",\n      \"0x006a2f60\",\n      \"0x006a2e20\",\n      \"0x006a2530\",\n      \"0x006a2b80\",\n      \"0x006a2c50\",\n      \"0x00694440\",\n      \"0x006a1540\",\n      \"0x006a1540\",\n      \"0x006a154a\",\n      \"0x006a15f3\",\n      \"0x006a2f60\",\n      \"0x006a2f60\",\n      \"0x006a2f78\",\n      \"0x006a2fe9\",\n      \"0x006a2f60\"\n    ],\n    \"conflict_id\": \"TD-DATA-003\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [\n      {\n        \"path\": \"competing_hypotheses.1.claim\",\n        \"status\": \"rejected_for_current_read_write_bodies     \",\n        \"text\": \"PropertyList Write serializes the entire recursive parent graph as ordinary local entries.\"\n      }\n    ],\n    \"resolution\": null,\n    \"resolution_status\": null,\n    \"source\": \"knowledgegraph/research/conflicts/track-d-data-serialization.json\",\n    \"subject\": \"PropertyList local transfer, parent reference, and PROP framing\",\n    \"unresolved_reason\": [\n      \"The exact three-word parent identity and its manager-side construction are not fully identified.\",\n      \"Outer record envelope, version negotiation, compression, and atomic rollback are not established by the selected bodies.\"\n    ]\n  },\n  {\n    \"anchors\": [\n      \"0x00e63d10\",\n      \"0x00e80ba0\",\n      \"0x00e819b0\",\n      \"0x00e63d10\",\n      \"0x00e819b0\",\n      \"0x00e80ba0\",\n      \"0x013c7d90\",\n      \"0x013c7d90\",\n      \"0x00693900\",\n      \"0x00693900\",\n      \"0x00693d60\",\n      \"0x00693d60\",\n      \"0x006a1540\",\n      \"0x006a2f60\",\n      \"0x006a1540\",\n      \"0x006a2f60\"\n    ],\n    \"conflict_id\": \"cell_cross_stage_handoff\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The global serializable-data handoff is concrete around Cell reset/reinitialization. Cross-mode/stage handoff is not established.\",\n    \"resolution_status\": \"The global serializable-data handoff is concrete around Cell reset/reinitialization. Cross-mode/stage handoff is not established.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00b28ec0\",\n      \"0x00b294c0\",\n      \"0x00bb4ba0\",\n      \"0x00bb4ba0\",\n      \"0x00693900\",\n      \"0x00693900\",\n      \"0x00693900\",\n      \"0x00693900\",\n      \"0x00693d60\",\n      \"0x00693d60\",\n      \"0x00693d60\",\n  
[TRUNCATED]
```
