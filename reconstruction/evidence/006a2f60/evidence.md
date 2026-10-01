# Evidence 0x006a2f60

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `a959d68ce42fdf9f07273dbcf65ddea911f22cfed223ac57504e2e63b4c5810b`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "__thiscall observed",
  "hidden_this_register": "ECX",
  "hidden_this_type": "DirectPropertyList*",
  "return_type": "bool",
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "load_site": "0x006a2f65 MOV EBP,dword ptr [ESP + 0x1c]",
      "name": "pInputStream",
      "position": 1,
      "type": "IStream*",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 4,
  "termination": "RET 0x4 at 0x006a306a"
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
        "size_inferred": true,
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
        "size_inferred": true,
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
  "abstained_because": [
    "esp_alignment_unknown: the entry-relative ESP offset is unknown and there is no frame pointer to fall back on"
  ],
  "cleanup": {
    "bytes": 4,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x4",
    "side": "callee"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "a612d8edd347d1064090d10dacdb52da041b163e045659576d49fe8cfd388c9f",
  "conventions": {
    "ambiguities": [
      "esp_alignment_unknown"
    ],
    "calling_convention": null,
    "candidate_conventions": [
      "__cdecl",
      "__stdcall",
      "__thiscall",
      "__fastcall"
    ],
    "confidence": "UNKNOWN",
    "corroboration": "not_available"
  },
  "cross_validation": {
    "agreement": false,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 2,
    "persisted": "no_information",
    "persisted_calling_convention": "__thiscall observed"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 2,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0045"
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
        "obs-0012",
        "obs-0017"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 1,
        "total_bytes": 4
      }
    },
    {
      "based_on": [
        "obs-0013",
        "obs-0014",
        "obs-0019",
        "obs-0025",
        "obs-0027",
        "obs-0031",
        "obs-0032"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          48
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0001"
      ],
      "claim": "the entry-relative argument offsets are unknown, so the convention is unknown",
      "confidence": "UNKNOWN",
      "id": "C11"
    },
    {
      "based_on": [
        "obs-0045"
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
        "obs-0045"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0045"
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
      "and_esp": null,
      "at": "0x006a2f60",
      "ebp_is_general_register": false,
      "fp": false,
      "id": "obs-0001",
      "index": 0,
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
      "at": "0x006a2f60",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x10",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x006a2f63",
      "count": 1,
      "first_use": 1,
      "first_write_index": 14,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x006a2f64",
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
      "at": "0x006a2f65",
      "count": 16,
      "first_use": 3,
      "first_write_index": 0,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV EBP,dword ptr [ESP + 0x1c]",
      "reg": "ESP"
    },
    {
      "at": "0x006a2f65",
      "base": "ESP",
      "disp": 28,
      "id": "obs-0006",
      "index": 3,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EBP,dword ptr [ESP + 0x1c]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x006a2f65",
      "definite": true,
      "id": "obs-0007",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV EBP,dword ptr [ESP + 0x1c]",
      "reg": "EBP",
      "write_kind": "mem_load"
    },
    {
      "at": "0x006a2f69",
      "count": 16,
      "first_use": 4,
      "first_write_index": 6,
      "id": "obs-0008",
      "index": 4,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x
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
    "va": "0x006866f0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x006a3170"
  }
]
```

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
  "count": 106,
  "instructions": [
    {
      "address": "006a2f60",
      "instruction": "SUB ESP,0x10"
    },
    {
      "address": "006a2f63",
      "instruction": "PUSH EBX"
    },
    {
      "address": "006a2f64",
      "instruction": "PUSH EBP"
    },
    {
      "address": "006a2f65",
      "instruction": "MOV EBP,dword ptr [ESP + 0x1c]"
    },
    {
      "address": "006a2f69",
      "instruction": "PUSH ESI"
    },
    {
      "address": "006a2f6a",
      "instruction": "PUSH EDI"
    },
    {
      "address": "006a2f6b",
      "instruction": "XOR ESI,ESI"
    },
    {
      "address": "006a2f6d",
      "instruction": "PUSH ESI"
    },
    {
      "address": "006a2f6e",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "006a2f70",
      "instruction": "LEA EAX,[ESP + 0x2c]"
    },
    {
      "address": "006a2f74",
      "instruction": "PUSH EAX"
    },
    {
      "address": "006a2f75",
      "instruction": "PUSH EBP"
    },
    {
      "address": "006a2f76",
      "instruction": "MOV EDI,ECX"
    },
    {
      "address": "006a2f78",
      "instruction": "CALL 0x0093a780"
    },
    {
      "address": "006a2f7d",
      "instruction": "MOV BL,AL"
    },
    {
      "address": "006a2f7f",
      "instruction": "MOV EAX,dword ptr [ESP + 0x34]"
    },
    {
      "address": "006a2f83",
      "instruction": "ADD ESP,0x10"
    },
    {
      "address": "006a2f86",
      "instruction": "TEST BL,BL"
    },
    {
      "address": "006a2f88",
      "instruction": "JZ 0x006a2fe9"
    },
    {
      "address": "006a2f8a",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "006a2f8c",
      "instruction": "JNS 0x006a2fe9"
    },
    {
      "address": "006a2f8e",
      "instruction": "PUSH ESI"
    },
    {
      "address": "006a2f8f",
      "instruction": "PUSH 0x3"
    },
    {
      "address": "006a2f91",
      "instruction": "LEA ECX,[ESP + 0x1c]"
    },
    {
      "address": "006a2f95",
      "instruction": "PUSH ECX"
    },
    {
      "address": "006a2f96",
      "instruction": "PUSH EBP"
    },
    {
      "address": "006a2f97",
      "instruction": "MOV dword ptr [ESP + 0x24],ESI"
    },
    {
      "address": "006a2f9b",
      "instruction": "MOV dword ptr [ESP + 0x28],ESI"
    },
    {
      "address": "006a2f9f",
      "instruction": "MOV dword ptr [ESP + 0x2c],ESI"
    },
    {
      "address": "006a2fa3",
      "instruction": "CALL 0x0093a780"
    },
    {
      "address": "006a2fa8",
      "instruction": "ADD ESP,0x10"
    },
    {
      "address": "006a2fab",
      "instruction": "MOV BL,AL"
    },
    {
      "address": "006a2fad",
      "instruction": "CALL 0x0067de30"
    },
    {
      "address": "006a2fb2",
      "instruction": "MOV ECX,dword ptr [EDI + 0x30]"
    },
    {
      "address": "006a2fb5",
      "instruction": "LEA ESI,[EDI + 0x30]"
    },
    {
      "address": "006a2fb8",
      "instruction": "MOV dword ptr [ESP + 0x10],EAX"
    },
    {
      "address": "006a2fbc",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "006a2fbe",
      "instruction": "JZ 0x006a2fd1"
    },
    {
      "address": "006a2fc0",
      "instruction": "MOV dword ptr [ESI],0x0"
    },
    {
      "address": "006a2fc6",
      "instruction": "MOV EDX,dword ptr [ECX]"
    },
    {
      "address": "006a2fc8",
      "instruction": "MOV EAX,dword ptr [EDX + 0x4]"
    },
    {
      "address": "006a2fcb",
      "instruction": "CALL EAX"
    },
    {
      "address": "006a2fcd",
      "instruction": "MOV EAX,dword ptr [ESP + 0x10]"
    },
    {
      "address": "006a2fd1",
      "instruction": "MOV ECX,dword ptr [ESP + 0x1c]"
    },
    {
      "address": "006a2fd5",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "006a2fd7",
      "instruction": "MOV EDX,dword ptr [EDX + 0x2c]"
    },
    {
      "address": "006a2fda",
      "instruction": "PUSH ESI"
    },
    {
      "address": "006a2fdb",
      "instruction": "PUSH ECX"
    },
    {
      "address": "006a2fdc",
      "instruction": "MOV ECX,dword ptr [ESP + 0x1c]"
    },
    {
      "address": "006a2fe0",
      "instruction": "PUSH ECX"
    },
    {
      "address": "006a2fe1",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "006a2fe3",
      "instruction": "CALL EDX"
    },
    {
      "address": "006a2fe5",
      "instruction": "MOV EAX,dword ptr [ESP + 0x24]"
    },
    {
      "address": "006a2fe9",
      "instruction": "AND EAX,0x7fffffff"
    },
    {
      "address": "006a2fee",
      "instruction": "LEA ESI,[EDI + 0x18]"
    },
    {
      "address": "006a2ff1",
      "instruction": "PUSH EAX"
    },
    {
      "address": "006a2ff2",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "006a2ff4",
      "instruction": "CALL 0x006a2b80"
    },
    {
      "address": "006a2ff9",
      "instruction": "MOV ECX,dword ptr [ESI + 0x4]"
    },
    {
      "address": "006a2ffc",
      "instruction": "SUB ECX,dword ptr [ESI]"
    },
    {
      "address": "006a2ffe",
      "instruction": "MOV EAX,0x2aaaaaab"
    },
    {
      "address": "006a3003",
      "instruction": "IMUL ECX"
    },
    {
      "address": "006a3005",
      "instruction": "SAR EDX,0x2"
    },
    {
      "address": "006a3008",
      "instruction": "MOV EAX,EDX"
    },
    {
      "address": "006a300a",
      "instruction": "SHR EAX,0x1f"
    },
    {
      "address": "006a300d",
      "instruction": "ADD EAX,EDX"
    },
    {
      "address": "006a300f",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "006a3011",
      "instruction": "JLE 0x006a3061"
    },
    {
      "address": "006a3013",
      "instruction": "XOR EDI,EDI"
    },
    {
      "address": "006a3015",
      "instruction": "MOV dword ptr [ESP + 0x10],EAX"
    },
    {
      "address": "006a3019",
      "instruction": "LEA ESP,[ESP]"
    },
    {
      "address": "006a3020",
      "instruction": "TEST BL,BL"
    },
    {
      "address": "006a3022",
      "instruction": "JZ 0x006
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
  "original_bytes": 8731,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"__thiscall observed\",\n    \"hidden_this_register\": \"ECX\",\n    \"hidden_this_type\": \"DirectPropertyList*\",\n    \"return_type\": \"bool\",\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"load_site\": \"0x006a2f65 MOV EBP,dword ptr [ESP + 0x1c]\",\n        \"name\": \"pInputStream\",\n        \"position\": 1,\n        \"type\": \"IStream*\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 4,\n    \"termination\": \"RET 0x4 at 0x006a306a\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x01408820\"\n      ],\n      \"package\": \"pkg-app-proplist-copyall-wave16\",\n      \"score\": 10,\n      \"symbol\": \"all_copy_from_properties_006a14d0\",\n      \"va\": \"0x006a14d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x01408820\"\n      ],\n      \"package\": \"pkg-dfw-006a1540\",\n      \"score\": 10,\n      \"symbol\": \"proplist_write_006a1540\",\n      \"va\": \"0x006a1540\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x01408820\"\n      ],\n      \"package\": \"pkg-property-clear-wave13\",\n      \"score\": 10,\n      \"symbol\": \"property_list_clear_006a2a80\",\n      \"va\": \"0x006a2a80\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x01408820\"\n      ],\n      \"package\": \"pkg-property-remove-006a2ef0\",\n      \"score\": 10,\n      \"symbol\": \"property_list_remove_property_006a2ef0\",\n      \"va\": \"0x006a2ef0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01408820\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"wave6-resources\",\n      \"score\": 6,\n      \"symbol\": \"property_list_has_property_006a2470\",\n      \"va\": \"0x006a2470\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01408820\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"wave6-resources\",\n      \"score\": 6,\n      \"symbol\": \"property_list_get_property_object_006a24d0\",\n      \"va\": \"0x006a24d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"pkg-direct-property-clear-wave14\",\n      \"score\": 6,\n      \"symbol\": \"direct_property_list_clear_006a2b20\",\n      \"va\": \"0x006a2b20\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01408820\"\n      ],\n      \"package\": \"PKG-PROPERTY-SAFE-WAVE9\",\n      \"score\": 4,\n      \"symbol\": \"property_list_copy_from_006a2a40\",\n      \"va\": \"0x006a2a40\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [\n    \"No original runtime trace validates the extended header path or the parent-swap side effect.\",\n    \"The DAT_015fd8a8 service port is an opaque runtime boundary in the staging model.\"\n  ],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"app-lifecycle\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x006866f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x006a3170\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00686ab5\",\n        \"direction\": \"in\",\n        \"other\": \"0x006866f0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006a3170\",\n        \"direction\": \"in\",\n        \"other\": \"0x006a3170\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006a2fad\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067de30\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006a3045\",\n        \"direction\": \"out\",\n        \"other\": \"0x00694440\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006a2ff4\",\n        \"direction\": \"out\",\n        \"other\": \"0x006a2b80\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006a2f78\",\n        \"direction\": \"out\",\n        \"other\": \"0x0093a780\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006a2fa3\",\n        \"direction\": \"out\",\n        \"other\": \"0x0093a780\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006a302e\",\n        \"direction\": \"out\",\n        \"other\": \"0x0093a780\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 2,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0218\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"CONFIRMED\",\n  \"globals\": [],\n  \"integration_status\": null,\n  \"name\": \"App::PropertyList::Read\",\n  \"normalized_symbol\": \"App::PropertyList::Read\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"queue_candidate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"queued\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": nul
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
  "body_end": "006a306c",
  "body_span_bytes": 269,
  "body_start": "006a2f60",
  "callees": [
    "FUN_006a2b80",
    "FUN_00694440",
    "FUN_0093a780",
    "FUN_0067de30"
  ],
  "callers": [
    "App::DirectPropertyList::Read",
    "FUN_006866f0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "006a2f60",
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
      "storage": "Stack[-0x10]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 4,
  "mode": "live",
  "name": "App::PropertyList::Read",
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
      "name": "pInputStream",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "IStream *"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "bool",
  "return_type_resolved": true,
  "rva": "0x2a2f60",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "bool App::PropertyList::Read(DirectPropertyList * this, IStream * pInputStream)",
  "size_bytes": 269,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x006a2f60",
  "vtables": {
    "referenced_by_vtables": [
      "0x01408820"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 3,
  "xrefs": [
    {
      "from": "00686ab5"
    },
    {
      "from": "0140885c"
    },
    {
      "from": "006a3170"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__Read.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__Read.c",
    "reconstruction/staging/pkg-app-proplist-read-wave17/property_list_read_006a2f60.cpp",
    "reconstruction/staging/pkg-app-proplist-read-wave17/property_list_read_006a2f60.hpp",
    "reconstruction/staging/pkg-app-proplist-read-wave17/property_list_read_006a2f60_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-app-proplist-read-wave17/006a2f60.json"
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
  "status": "queued"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "DirectPropertyList*",
  "IStream*",
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
