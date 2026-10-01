# Evidence 0x00b21340

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `d67bbd35c1ac11c6e108b9b9a9ce8635c578dfc9b9cfde2e150015dd3e83c01e`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "__thiscall observed",
  "hidden_this": true,
  "return_register": "EAX",
  "return_semantics": "The body returns the map value pointer without an AddRef, copy, or ownership transfer.",
  "return_width_bytes": 4,
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "observed_use": "Called with no source-level arguments on a map miss; its EAX result becomes the new value pointer.",
      "position": 1,
      "type": "NounCreateCallback",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x08",
      "observed_use": "Called with the selected value pointer when the value dirty byte is nonzero.",
      "position": 2,
      "type": "NounClearCallback",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x0C",
      "observed_use": "Called with value then list-node arguments when the filter callback returns nonzero.",
      "position": 3,
      "type": "NounAddCallback",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x10",
      "observed_use": "Called with list-node then noun-ID arguments; only a nonzero AL result invokes add.",
      "position": 4,
      "type": "NounFilterCallback",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x14",
      "observed_use": "Used as the map key and forwarded as the second filter argument.",
      "position": 5,
      "type": "std::uint32_t",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 0
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
      "entry_ESP+0xc",
      "entry_ESP+0x14"
    ],
    "ordinary_stack_arguments": [
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
        "entry_offset": "entry_ESP+0x14",
        "observed": true,
        "ordinal": 5,
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
    "ret_form": "RET 0x14",
    "return_register": "EAX",
    "return_semantics": "pointer_like_in_EAX",
    "saved_registers": [
      "EBP",
      "EBX",
      "EDI",
      "ESI"
    ],
    "stack_arguments": [
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
        "entry_offset": "entry_ESP+0x14",
        "observed": true,
        "ordinal": 5,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "stack_cleanup_bytes": 20,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x14"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +20, so the listing is not one path",
    "slot_gaps_present: argument ordinal(s) below the highest read slot are never touched"
  ],
  "cleanup": {
    "bytes": 20,
    "confidence": "SUPPORTED",
    "corroboration": "not_available",
    "evidence": "ret 0x14",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [
    {
      "field": "stack_cleanup_bytes",
      "inferred": 20,
      "kind": "inferred_vs_persisted",
      "persisted": 0,
      "resolution_status": "unresolved"
    }
  ],
  "content_sha256": "4c2dadbd34c750b662af75f706fda02fa473c7c80d973e3370dde3e60f66e409",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall"
    ],
    "confidence": "INFERRED",
    "corroboration": "not_available"
  },
  "cross_validation": {
    "agreement": false,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 0,
    "persisted": "no_information",
    "persisted_calling_convention": "__thiscall observed"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 4,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0042"
      ],
      "claim": "the callee pops 20 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 20,
        "side": "callee"
      }
    },
    {
      "based_on": [
        "obs-0010",
        "obs-0020"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 3,
        "observed_slots": 2,
        "total_bytes": 20
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007",
        "obs-0011",
        "obs-0012",
        "obs-0022",
        "obs-0034"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          120
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007",
        "obs-0011",
        "obs-0012",
        "obs-0022",
        "obs-0034",
        "obs-0042"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0042"
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
        "obs-0042"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0042"
      ],
      "claim": "the last value written to EAX classifies as pointer_like",
      "confidence": "INFERRED",
      "id": "RT2",
      "value": {
        "register_class": "pointer_like"
      }
    }
  ],
  "observations": [
    {
      "and_esp": null,
      "at": "0x00b21340",
      "ebp_is_general_register": false,
      "fp": false,
      "id": "obs-0001",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": true,
      "push_ebp_at": 51,
      "raw": "SUB ESP,0x10",
      "sub": 16
    },
    {
      "at": "0x00b21340",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x10",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00b21343",
      "count": 7,
      "first_use": 1,
      "first_write_index": 17,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00b21344",
      "count": 11,
      "first_use": 2,
      "first_write_index": 4,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00b21345",
      "count": 6,
      "first_use": 3,
      "first_write_
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "pkg20_gameglobal_00ba8420",
    "reconstructed": true,
    "va": "0x00ba8420"
  },
  {
    "name": "map_int_whatever_find",
    "reconstructed": true,
    "va": "0x00e5c780"
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
    "va": "0x00acd9a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00acd9d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00acda00"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ace2c0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ace2f0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ace4e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ace5a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ad12a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ad49b0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ad49e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ad4a10"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ae0dd0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ae0e00"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ae6030"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ae6240"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ae7200"
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
      "0x00b21340",
      "0x00b21340"
    ],
    "conflict_id": "CF-006",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": null,
    "resolution_status": null,
    "source": "knowledgegraph/research/conflicts/track-f-cross-domain-impact.json",
    "subject": null,
    "unresolved_reason": {
      "missing_evidence": [
        "Concrete noun create, owner, erase, rekey, invalidation, and failure paths.",
        "Subtype-by-subtype factory and destruction evidence for cGameData, cCivilization, cCreatureBase, cTribe, cEmpire, cStarRecord, and cMission.",
        "A cross-mode identity and persistence handoff contract."
      ],
      "status": "blocked"
    }
  },
  {
    "anchors": [
      "0x00ba8420",
      "0x00e5c780",
      "0x00b212d0",
      "0x00b21340",
      "0x00b21340",
      "0x00b21340",
      "0x00e9c9a0",
      "0x00b21340",
      "0x00b212d0",
      "0x00b21340",
      "0x00b21340",
      "0x00ba8420",
      "0x00e9c9a0",
      "0x00b21340",
      "0x00e9c9a0",
      "0x00e5c780"
    ],
    "conflict_id": "LC-011",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "RESOLVED_SUPPORTED",
    "resolution_status": "RESOLVED_SUPPORTED",
    "source": "knowledgegraph/research/conflicts/track-a-type-signature.json",
    "subject": "0x00B21340 semantic identity",
    "unresolved_reason": "The exact private source-level function name and complete parameter types are unknown; the noun-materialization semantics and rejection of the message-registration label are resolved."
  },
  {
    "anchors": [
      "0x00e5c780",
      "0x00b21340",
      "0x00ba8420",
      "0x00000004",
      "0x00b21340",
      "0x00e5c780",
      "0x00b21340",
      "0x00b21340"
    ],
    "conflict_id": "TB-LC-011",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": {
      "merge_decision": "preferred_claim_with_limit",
      "preferred_claim": "Use map/list callback or noun-materialization mechanics as the preferred behavior label for 0x00B21340.",
      "preserved_alternatives": true,
      "scope_note": "The message-handler label remains withdrawn or contested because the owner and key/value domain are unresolved.",
      "status": "preferred_claim_with_limit",
      "taxonomy": "preferred_claim_with_limit"
    },
    "resolution_status": "preferred_claim_with_limit",
    "source": "knowledgegraph/research/conflicts/track-b-vtable-fields.json",
    "subject": "FUN_00B21340 message-handler label versus map/list callback mechanics",
    "unresolved_reason": "The cited static evidence leaves the competing owner, slot, layout, or lifecycle interpretation unresolved; no positive original runtime or MSVC RTTI evidence is available."
  },
  {
    "anchors": [
      "0x00b21340",
      "0x00b21340",
      "0x00b1d870",
      "0x00b1d870",
      "0x00b1db60",
      "0x00b1db60",
      "0x00b1dbd0",
      "0x00b1dbd0",
      "0x00b21340",
      "0x00b267f0",
      "0x00b267f0",
      "0x00b5b840",
      "0x00b5b840",
      "0x00b5b880",
      "0x00b5b880",
      "0x00b5b8a0"
    ],
    "conflict_id": "noun_update_flag_writers",
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
      "0x00b21340",
      "0x00b21340",
      "0x00acd9a0",
      "0x00acd9a0",
      "0x00acd9a0",
      "0x00ace2c0",
      "0x00ace2c0",
      "0x00ace2c0",
      "0x00b25f40",
      "0x00b25f40",
      "0x00ba0080",
      "0x00ba0080",
      "0x00ba0080",
      "0x00bf9820",
      "0x00bf9820",
      "0x00ba8420"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/additional-domains.json:0",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
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
  "count": 80,
  "instructions": [
    {
      "address": "00b21340",
      "instruction": "SUB ESP,0x10"
    },
    {
      "address": "00b21343",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00b21344",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00b21345",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00b21346",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00b21348",
      "instruction": "LEA EAX,[ESP + 0x30]"
    },
    {
      "address": "00b2134c",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00b2134d",
      "instruction": "LEA ECX,[ESP + 0x10]"
    },
    {
      "address": "00b21351",
      "instruction": "LEA EDI,[ESI + 0x98]"
    },
    {
      "address": "00b21357",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00b21358",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00b2135a",
      "instruction": "CALL 0x00e5c780"
    },
    {
      "address": "00b2135f",
      "instruction": "MOV EAX,dword ptr [ESP + 0xc]"
    },
    {
      "address": "00b21363",
      "instruction": "LEA EDX,[ESI + 0x9c]"
    },
    {
      "address": "00b21369",
      "instruction": "CMP EAX,EDX"
    },
    {
      "address": "00b2136b",
      "instruction": "JNZ 0x00b2139c"
    },
    {
      "address": "00b2136d",
      "instruction": "CALL dword ptr [ESP + 0x20]"
    },
    {
      "address": "00b21371",
      "instruction": "MOV EBX,EAX"
    },
    {
      "address": "00b21373",
      "instruction": "MOV EAX,dword ptr [ESP + 0x30]"
    },
    {
      "address": "00b21377",
      "instruction": "MOV byte ptr [ESP + 0x20],0x0"
    },
    {
      "address": "00b2137c",
      "instruction": "MOV ECX,dword ptr [ESP + 0x20]"
    },
    {
      "address": "00b21380",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00b21381",
      "instruction": "LEA EDX,[ESP + 0x10]"
    },
    {
      "address": "00b21385",
      "instruction": "MOV dword ptr [ESP + 0x10],EAX"
    },
    {
      "address": "00b21389",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00b2138a",
      "instruction": "LEA EAX,[ESP + 0x1c]"
    },
    {
      "address": "00b2138e",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00b2138f",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00b21391",
      "instruction": "MOV dword ptr [ESP + 0x1c],EBX"
    },
    {
      "address": "00b21395",
      "instruction": "CALL 0x00ba8420"
    },
    {
      "address": "00b2139a",
      "instruction": "JMP 0x00b2139f"
    },
    {
      "address": "00b2139c",
      "instruction": "MOV EBX,dword ptr [EAX + 0x14]"
    },
    {
      "address": "00b2139f",
      "instruction": "CMP byte ptr [EBX],0x0"
    },
    {
      "address": "00b213a2",
      "instruction": "JZ 0x00b213ff"
    },
    {
      "address": "00b213a4",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00b213a5",
      "instruction": "CALL dword ptr [ESP + 0x28]"
    },
    {
      "address": "00b213a9",
      "instruction": "MOV ECX,dword ptr [ESI + 0x78]"
    },
    {
      "address": "00b213ac",
      "instruction": "LEA EAX,[ESI + 0x78]"
    },
    {
      "address": "00b213af",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "00b213b2",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00b213b4",
      "instruction": "JZ 0x00b213bb"
    },
    {
      "address": "00b213b6",
      "instruction": "LEA ESI,[ECX + -0xc]"
    },
    {
      "address": "00b213b9",
      "instruction": "JMP 0x00b213bd"
    },
    {
      "address": "00b213bb",
      "instruction": "XOR ESI,ESI"
    },
    {
      "address": "00b213bd",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00b213bf",
      "instruction": "JZ 0x00b213c6"
    },
    {
      "address": "00b213c1",
      "instruction": "LEA EDI,[EAX + -0xc]"
    },
    {
      "address": "00b213c4",
      "instruction": "JMP 0x00b213c8"
    },
    {
      "address": "00b213c6",
      "instruction": "XOR EDI,EDI"
    },
    {
      "address": "00b213c8",
      "instruction": "CMP ESI,EDI"
    },
    {
      "address": "00b213ca",
      "instruction": "JZ 0x00b213fc"
    },
    {
      "address": "00b213cc",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00b213cd",
      "instruction": "MOV EBP,dword ptr [ESP + 0x30]"
    },
    {
      "address": "00b213d1",
      "instruction": "MOV ECX,dword ptr [ESP + 0x34]"
    },
    {
      "address": "00b213d5",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00b213d6",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00b213d7",
      "instruction": "CALL EBP"
    },
    {
      "address": "00b213d9",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "00b213dc",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00b213de",
      "instruction": "JZ 0x00b213e9"
    },
    {
      "address": "00b213e0",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00b213e1",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00b213e2",
      "instruction": "CALL dword ptr [ESP + 0x34]"
    },
    {
      "address": "00b213e6",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "00b213e9",
      "instruction": "MOV ESI,dword ptr [ESI + 0xc]"
    },
    {
      "address": "00b213ec",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "00b213ee",
      "instruction": "JZ 0x00b213f5"
    },
    {
      "address": "00b213f0",
      "instruction": "ADD ESI,-0xc"
    },
    {
      "address": "00b213f3",
      "instruction": "JMP 0x00b213f7"
    },
    {
      "address": "00b213f5",
      "instruction": "XOR ESI,ESI"
    },
    {
      "address": "00b213f7",
      "instruction": "CMP ESI,EDI"
    },
    {
      "address": "00b213f9",
      "instruction": "JNZ 0x00b213d1"
    },
    {
      "address": "00b213fb",
      "instruction": "POP EBP"
    },
   
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
  "original_bytes": 28408,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"__thiscall observed\",\n    \"hidden_this\": true,\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"The body returns the map value pointer without an AddRef, copy, or ownership transfer.\",\n    \"return_width_bytes\": 4,\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"observed_use\": \"Called with no source-level arguments on a map miss; its EAX result becomes the new value pointer.\",\n        \"position\": 1,\n        \"type\": \"NounCreateCallback\",\n        \"width_bytes\": 4\n      },\n      {\n        \"entry_offset\": \"ESP+0x08\",\n        \"observed_use\": \"Called with the selected value pointer when the value dirty byte is nonzero.\",\n        \"position\": 2,\n        \"type\": \"NounClearCallback\",\n        \"width_bytes\": 4\n      },\n      {\n        \"entry_offset\": \"ESP+0x0C\",\n        \"observed_use\": \"Called with value then list-node arguments when the filter callback returns nonzero.\",\n        \"position\": 3,\n        \"type\": \"NounAddCallback\",\n        \"width_bytes\": 4\n      },\n      {\n        \"entry_offset\": \"ESP+0x10\",\n        \"observed_use\": \"Called with list-node then noun-ID arguments; only a nonzero AL result invokes add.\",\n        \"position\": 4,\n        \"type\": \"NounFilterCallback\",\n        \"width_bytes\": 4\n      },\n      {\n        \"entry_offset\": \"ESP+0x14\",\n        \"observed_use\": \"Used as the map key and forwarded as the second filter argument.\",\n        \"position\": 5,\n        \"type\": \"std::uint32_t\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 0\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"shared_types:OrderedMap,OrderedMapEntry,void *\",\n        \"same_calling_convention\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-20-GAMEGLOBAL\",\n      \"score\": 14,\n      \"symbol\": \"map_int_whatever_find\",\n      \"va\": \"0x00e5c780\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:OrderedMap,OrderedMapEntry\",\n        \"same_calling_convention\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-20-GAMEGLOBAL\",\n      \"score\": 11,\n      \"symbol\": \"pkg20_gameglobal_00ba8420\",\n      \"va\": \"0x00ba8420\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"shared_types:OrderedMapEntry\"\n      ],\n      \"package\": \"PKG-11-SIM-CORE\",\n      \"score\": 11,\n      \"symbol\": \"Simulator_LookupEmpireByPoliticalId\",\n      \"va\": \"0x00ba9370\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:OrderedMap,OrderedMapEntry\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-20-GAMEGLOBAL\",\n      \"score\": 8,\n      \"symbol\": \"pkg20_gameglobal_00ba83a0\",\n      \"va\": \"0x00ba83a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-11-SIM-CORE\",\n      \"score\": 8,\n      \"symbol\": \"Simulator_IsNotStarOrBinaryStar\",\n      \"va\": \"0x00c8b6b0\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-13-C4-CIV-WAVE3\",\n      \"score\": 3,\n      \"symbol\": \"culture_selection_00bf9820\",\n      \"va\": \"0x00bf9820\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-11-A2-PROGRESSION-ALTERNATIVE\",\n      \"score\": 3,\n      \"symbol\": \"mission_manager_operation_00fee310\",\n      \"va\": \"0x00fee310\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-18-UI-SPACE\",\n      \"score\": 3,\n      \"symbol\": \"pkg18_space_ui_initialize_01073700\",\n      \"va\": \"0x01073700\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [\n    \"No differential runtime corpus is available for the 254 callers.\",\n    \"The concrete callback implementations and noun vector payload subtype remain unresolved.\",\n    \"The live function is not named as cGameNounManager::GetData, so the adjacent helper's semantic relationship is not promoted.\"\n  ],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"NounProjection\",\n  \"cluster\": \"unknown-fun-mass\",\n  \"confidence\": 0.93,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"pkg20_gameglobal_00ba8420\",\n        \"reconstructed\": true,\n        \"va\": \"0x00ba8420\"\n      },\n      {\n        \"name\": \"map_int_whatever_find\",\n        \"reconstructed\": true,\n        \"va\": \"0x00e5c780\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00acd9a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00acd9d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00acda00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ace2c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ace2f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ace4e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ace5a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ad12a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ad49b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ad49e0\"\n      },\n      {\
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
  "body_end": "00b21409",
  "body_span_bytes": 202,
  "body_start": "00b21340",
  "callees": [
    "FUN_00ba8420",
    "map_int_whatever_find"
  ],
  "callers": [
    "FUN_00bd3280",
    "FUN_00b9caa0",
    "FUN_00ffa900",
    "FUN_00e10e30",
    "FUN_00ace4e0",
    "FUN_00ff9520",
    "FUN_00b175e0",
    "FUN_00fee110",
    "FUN_00fee820",
    "FUN_00ef2b20",
    "FUN_00d40b40",
    "FUN_00ae6030",
    "FUN_00b8bba0",
    "FUN_00b894a0",
    "FUN_00bf7150",
    "FUN_00fedd50",
    "FUN_00b1add0",
    "FUN_00b9d820",
    "FUN_00ccd8a0",
    "FUN_00d522c0",
    "FUN_00be4400",
    "FUN_00b25fe0",
    "FUN_00cc1890",
    "FUN_00c519a0",
    "FUN_00cdd9c0",
    "FUN_00fee8d0",
    "FUN_00fdf8e0",
    "FUN_00dcedb0",
    "FUN_00ba47b0",
    "FUN_01043fd0",
    "FUN_00fdfb10",
    "FUN_00fee6b0",
    "FUN_00b89a30",
    "FUN_00ace2c0",
    "FUN_00ffaa90",
    "FUN_00ad12a0",
    "FUN_00bf7d80",
    "FUN_00bf8170",
    "FUN_00ffab60",
    "FUN_00ad4a10",
    "FUN_00feddf0",
    "FUN_00fdf5f0",
    "FUN_0105b6a0",
    "FUN_00ffa780",
    "FUN_00cdd960",
    "FUN_00cfee00",
    "FUN_00bf5cb0",
    "FUN_00cdcb10",
    "FUN_00ae6240",
    "FUN_00d3fcf0",
    "FUN_00e9c6d0",
    "FUN_00b25f40",
    "FUN_00b2f350",
    "FUN_00e435c0",
    "FUN_00bbff40",
    "FUN_00c5fe00",
    "FUN_00fdf9f0",
    "FUN_00ad49b0",
    "FUN_00e43710",
    "FUN_00dc3e10",
    "FUN_00b992c0",
    "FUN_00b993c0",
    "FUN_00c737a0",
    "FUN_00cc22c0",
    "FUN_00cf44c0",
    "FUN_00c9b740",
    "FUN_00fedf20",
    "FUN_0102c0c0",
    "FUN_00d1cb00",
    "FUN_00fedfe0",
    "FUN_00ae7200",
    "FUN_00acd9d0",
    "FUN_00bc0180",
    "FUN_00b98f00",
    "FUN_00f316d0",
    "FUN_00cddcf0",
    "FUN_00ef2e90",
    "FUN_010251e0",
    "FUN_00b6d1d0",
    "FUN_00dceca0",
    "FUN_00cfb660",
    "FUN_00cec7a0",
    "FUN_01060df0",
    "FUN_00b25c30",
    "FUN_00ad49e0",
    "FUN_01001b60",
    "FUN_00c74280",
    "FUN_00d51c30",
    "FUN_00ff9070",
    "FUN_0105fbc0",
    "FUN_00ffa2c0",
    "FUN_00ba0080",
    "FUN_00cacf40",
    "FUN_00c51740",
    "FUN_00cc0700",
    "FUN_00cdb8b0",
    "FUN_00dc40a0",
    "FUN_00d38530",
    "FUN_00dc3f10",
    "FUN_00acd9a0",
    "FUN_00cc1c30",
    "FUN_00b17c10",
    "FUN_00f39f50",
    "FUN_00ae73b0",
    "FUN_01058c90",
    "FUN_00bd3550",
    "FUN_00ea8c30",
    "FUN_01044360",
    "FUN_00f24dc0",
    "FUN_00f315a0",
    "FUN_00c829e0",
    "FUN_00c5fd60",
    "FUN_00ffaf20",
    "FUN_00dd4950",
    "FUN_00ae7350",
    "FUN_00cdd500",
    "FUN_00fee190",
    "FUN_00aee830",
    "FUN_00be41b0",
    "FUN_0103fe90",
    "FUN_0102bc90",
    "FUN_00b9fa40",
    "FUN_00bfbbf0",
    "FUN_00ff95a0",
    "FUN_01072680",
    "FUN_00b99530",
    "FUN_00cc26a0",
    "FUN_00d43e30",
    "FUN_00ace2f0",
    "FUN_00beabb0",
    "FUN_01073700",
    "FUN_00af82e0",
    "FUN_00dcd720",
    "FUN_00c635c0",
    "FUN_00bbfeb0",
    "FUN_00bf5720",
    "FUN_01060150",
    "FUN_00be4000",
    "FUN_00d3f9b0",
    "FUN_00bf8710",
    "FUN_00cec6d0",
    "FUN_00b9a4d0",
    "FUN_00b3c1a0",
    "FUN_00ba1590",
    "FUN_00b99670",
    "FUN_00ffb830",
    "FUN_00c36ae0",
    "FUN_00cddda0",
    "FUN_00b294c0",
    "FUN_00cde2f0",
    "FUN_00c50600",
    "FUN_00c51900",
    "FUN_00bc08d0",
    "FUN_00cfbc10",
    "FUN_00c54e50",
    "FUN_01059170",
    "FUN_00e9c9a0",
    "FUN_0102c1a0",
    "FUN_00b4c7c0",
    "FUN_00c35740",
    "FUN_00ef2c70",
    "FUN_00c8cb20",
    "FUN_00f1e6a0",
    "FUN_00cc6910",
    "FUN_00fe0160",
    "FUN_00ff9100",
    "FUN_01071d70",
    "FUN_0100a080",
    "FUN_00bff2d0",
    "FUN_00b28da0",
    "FUN_0102c340",
    "FUN_00fdfbc0",
    "FUN_00fe0f40",
    "FUN_00ae0e00",
    "FUN_00fedea0",
    "FUN_00cac360",
    "FUN_00d425f0",
    "FUN_01044640",
    "FUN_00be45b0",
    "FUN_00bd5ea0",
    "FUN_00ae73e0",
    "FUN_00ff9800",
    "FUN_00b23a40",
    "FUN_01030b70",
    "FUN_00b4c730",
    "FUN_0102be20",
    "FUN_00c8c9d0",
    "FUN_0102c600",
    "FUN_00cc5f80",
    "FUN_00c830f0",
    "FUN_00cfb140",
    "FUN_00d90320",
    "FUN_00b990bb",
    "FUN_00cfb890",
    "FUN_00cac1a0",
    "FUN_00bf6fa0",
    "FUN_00c5d640",
    "FUN_00d40930",
    "FUN_00fedd80",
    "FUN_00bc0710",
    "FUN_00acda00",
    "FUN_00fee590",
    "FUN_00ba4600",
    "FUN_00bf9820",
    "FUN_0105ba00",
    "FUN_00feff80",
    "FUN_00ffa690",
    "FUN_00b9bed0",
    "FUN_00e434a0",
    "FUN_00d90640",
    "FUN_00c5da10",
    "FUN_00c73b60",
    "FUN_01000dc0",
    "FUN_00cfb610",
    "FUN_0100b0a0",
    "FUN_00b23690",
    "FUN_00ba46f0",
    "FUN_00b4c850",
    "FUN_00c61390",
    "FUN_00ff9390",
    "Simulator::cMissionManager::GetMissionByID",
    "FUN_00fef3b0",
    "FUN_00ffabc0",
    "FUN_00cdc8b0",
    "FUN_00b71ee0",
    "FUN_00fee0a0",
    "FUN_00c6fb80",
    "FUN_00bf70b0",
    "FUN_00ff5840",
    "FUN_00fef140",
    "FUN_00fee220",
    "FUN_00fee480",
    "FUN_01001700",
    "FUN_00ae0dd0",
    "FUN_00bc0000",
    "FUN_00b99420",
    "FUN_00ace5a0",
    "FUN_00d5de40",
    "FUN_00bcc010",
    "FUN_00bf6cb0",
    "FUN_010019a0",
    "FUN_00d04320",
    "FUN_00c5fd90",
    "FUN_00d1cdf0",
    "FUN_00b25ee0",
    "FUN_00fee4f0",
    "FUN_00d90950",
    "FUN_00bfa660",
    "FUN_00ba1280",
    "FUN_00b25ca0",
    "FUN_00cac740",
    "FUN_00cacc60",
    "FUN_00ffb270",
    "FUN_00dc4460"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00b21340",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_10",
      "storage": "Stack[-0x10]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 1,
  "mode": "live",
  "name": "FUN_00b21340",
  "namespace": null,
  "name
[TRUNCATED]
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
  "file": "src/reconstruction/pkg11_sim_core/noun_projection.cpp",
  "files": [
    "reconstruction/staging/pkg11-sim-core/noun_projection.cpp",
    "reconstruction/staging/pkg11-sim-core/noun_projection.hpp",
    "reconstruction/staging/pkg11-sim-core/noun_projection_model_test.cpp",
    "src/reconstruction/pkg11_sim_core/noun_projection.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-source-wave2/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg11-sim-core/00b21340.json"
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
    "gate-noun-projection-callbacks-and-map-ownership"
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
  "original_bytes": 9322,
  "preview": "{\n  \"category\": null,\n  \"classification\": \"STRONG_SEMANTIC\",\n  \"confidence\": {\n    \"mechanics\": 0.99\n  },\n  \"contradictions\": [],\n  \"downstream_unlock_count\": 256,\n  \"evidence\": [\n    {\n      \"independence\": \"same-binary disassembly corroborates decompilation\",\n      \"source\": \"Ghidra SporeApp.exe 0x00b21340: 80 instructions; RET 0x14; direct calls to 0x00e5c780 and 0x00ba8420\",\n      \"supports\": \"signature, calling convention, branches, direct callees\"\n    },\n    {\n      \"independence\": \"same-binary decompilation\",\n      \"source\": \"Ghidra SporeApp.exe FUN_00b21340\",\n      \"supports\": \"lower-bound selection, end-only insertion, dirty rebuild, borrowed return\"\n    },\n    {\n      \"independence\": \"independent same-binary consumer chain\",\n      \"source\": \"Ghidra SporeApp.exe 0x00bff2d0 and 0x00b25f40\",\n      \"supports\": \"receiver compatibility, callback ABI use, typed-vector consumer shape\"\n    },\n    {\n      \"independence\": \"same-binary helper decompilation\",\n      \"source\": \"Ghidra SporeApp.exe 0x00e5c780, 0x00ba8420, 0x00b201a0, 0x00b21410\",\n      \"supports\": \"lower_bound versus exact_find, insertion branch, invalidation and sibling erase boundary\"\n    },\n    {\n      \"independence\": \"independent repository static adjudication\",\n      \"source\": \"knowledgegraph/research/root-closure/followup-noun-boundary.md:7-13,38-80,84-103,176-183\",\n      \"supports\": \"actual GetData identity, callback roles, successor hazard, and preserved allocation/locking unknowns\"\n    },\n    {\n      \"independence\": \"independent repository closure synthesis\",\n      \"source\": \"docs/analysis/simulator-root-closure.md:14,33-39,141,154\",\n      \"supports\": \"subsystem boundary, structure offsets, borrowed ownership, downstream role\"\n    }\n  ],\n  \"family\": \"cGameNounManager typed game-data projection family\",\n  \"interfaces\": {\n    \"boundaries\": {},\n    \"direct_callees\": {\n      \"direct\": [\n        {\n          \"keys\": [\n            \"name\",\n            \"role\",\n            \"va\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"name\",\n            \"role\",\n            \"va\"\n          ]\n        }\n      ],\n      \"indirect_callbacks\": [\n        {\n          \"keys\": [\n            \"name\",\n            \"role\",\n            \"va\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"name\",\n            \"role\",\n            \"va\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"name\",\n            \"role\",\n            \"va\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"name\",\n            \"role\",\n            \"va\"\n          ]\n        }\n      ]\n    },\n    \"direct_callers\": {\n      \"direct_call_edges\": null,\n      \"direct_caller_count\": 254,\n      \"downstream_unlock_count\": 254,\n      \"gameplay_caller_count\": 50,\n      \"representative\": [\n        {\n          \"keys\": [\n            \"name\",\n            \"role\",\n            \"va\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"name\",\n            \"role\",\n            \"va\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"name\",\n            \"role\",\n            \"va\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"name\",\n            \"role\",\n            \"va\"\n          ]\n        }\n      ]\n    },\n    \"globals\": [\n      {\n        \"field\": \"mNouns\",\n        \"offset\": \"0x78\",\n        \"structure\": \"cGameNounManager\",\n        \"type\": \"intrusive_list<cGameData>\"\n      },\n      {\n        \"field\": \"mNounMap\",\n        \"offset\": \"0x98\",\n        \"structure\": \"cGameNounManager\",\n        \"type\": \"map<uint32_t, tGameDataVectorT<cGameData>>\"\n      },\n      {\n        \"field\": \"mNounMap end/anchor\",\n        \"offset\": \"0x9c\",\n        \"structure\": \"cGameNounManager\",\n        \"type\": \"map end storage\"\n      },\n      {\n        \"field\": \"needsUpdate/mpBegin/mpEnd/mpCapacity\",\n        \"offset\": \"0x00/0x04/0x08/0x0c\",\n        \"structure\": \"tGameDataVectorT<cGameData>\",\n        \"type\": \"bool and intrusive_ptr<cGameData> vector fields\"\n      }\n    ],\n    \"structures\": [\n      {\n        \"field\": \"mNouns\",\n        \"offset\": \"0x78\",\n        \"structure\": \"cGameNounManager\",\n        \"type\": \"intrusive_list<cGameData>\"\n      },\n      {\n        \"field\": \"mNounMap\",\n        \"offset\": \"0x98\",\n        \"structure\": \"cGameNounManager\",\n        \"type\": \"map<uint32_t, tGameDataVectorT<cGameData>>\"\n      },\n      {\n        \"field\": \"mNounMap end/anchor\",\n        \"offset\": \"0x9c\",\n        \"structure\": \"cGameNounManager\",\n        \"type\": \"map end storage\"\n      },\n      {\n        \"field\": \"needsUpdate/mpBegin/mpEnd/mpCapacity\",\n        \"offset\": \"0x00/0x04/0x08/0x0c\",\n        \"structure\": \"tGameDataVectorT<cGameData>\",\n        \"type\": \"bool and intrusive_ptr<cGameData> vector fields\"\n      }\n    ],\n    \"vtables\": [],\n    \"worker_contract_surface\": {\n      \"failure_behavior\": [],\n      \"identity_boundary\": \"not_reported\",\n      \"inputs\": [\n        {\n          \"keys\": [\n            \"meaning\",\n            \"name\",\n            \"offset\",\n            \"type\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"meaning\",\n            \"name\",\n            \"offset\",\n            \"type\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"meaning\",\n            \"name\",\n            \"offset\",\n            \"type\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"meaning\",\n            \"name\",\n            \"o
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
  "ContainerCreateCallback_t/ContainerClearCallback_t/ContainerAddCallback_t/ContainerFilterCallback_t",
  "NounAddCallback",
  "NounClearCallback",
  "NounCreateCallback",
  "NounCreateMap",
  "NounFilterCallback",
  "NounListNode",
  "NounMapEntry",
  "NounProjection",
  "NounProjectionVector",
  "NounProjectionVector *",
  "OrderedMap",
  "OrderedMapEntry",
  "cGameNounManager",
  "std::int32_t",
  "std::uint32_t",
  "std::uint8_t",
  "tGameDataVectorT<Simulator::cGameData>",
  "void *"
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
      "0x00b21340",
      "0x00b21340"
    ],
    "conflict_id": "CF-006",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": null,
    "resolution_status": null,
    "source": "knowledgegraph/research/conflicts/track-f-cross-domain-impact.json",
    "subject": null,
    "unresolved_reason": {
      "missing_evidence": [
        "Concrete noun create, owner, erase, rekey, invalidation, and failure paths.",
        "Subtype-by-subtype factory and destruction evidence for cGameData, cCivilization, cCreatureBase, cTribe, cEmpire, cStarRecord, and cMission.",
        "A cross-mode identity and persistence handoff contract."
      ],
      "status": "blocked"
    }
  },
  {
    "anchors": [
      "0x00ba8420",
      "0x00e5c780",
      "0x00b212d0",
      "0x00b21340",
      "0x00b21340",
      "0x00b21340",
      "0x00e9c9a0",
      "0x00b21340",
      "0x00b212d0",
      "0x00b21340",
      "0x00b21340",
      "0x00ba8420",
      "0x00e9c9a0",
      "0x00b21340",
      "0x00e9c9a0",
      "0x00e5c780"
    ],
    "conflict_id": "LC-011",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "RESOLVED_SUPPORTED",
    "resolution_status": "RESOLVED_SUPPORTED",
    "source": "knowledgegraph/research/conflicts/track-a-type-signature.json",
    "subject": "0x00B21340 semantic identity",
    "unresolved_reason": "The exact private source-level function name and complete parameter types are unknown; the noun-materialization semantics and rejection of the message-registration label are resolved."
  },
  {
    "anchors": [
      "0x00e5c780",
      "0x00b21340",
      "0x00ba8420",
      "0x00000004",
      "0x00b21340",
      "0x00e5c780",
      "0x00b21340",
      "0x00b21340"
    ],
    "conflict_id": "TB-LC-011",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": {
      "merge_decision": "preferred_claim_with_limit",
      "preferred_claim": "Use map/list callback or noun-materialization mechanics as the preferred behavior label for 0x00B21340.",
      "preserved_alternatives": true,
      "scope_note": "The message-handler label remains withdrawn or contested because the owner and key/value domain are unresolved.",
      "status": "preferred_claim_with_limit",
      "taxonomy": "preferred_claim_with_limit"
    },
    "resolution_status": "preferred_claim_with_limit",
    "source": "knowledgegraph/research/conflicts/track-b-vtable-fields.json",
    "subject": "FUN_00B21340 message-handler label versus map/list callback mechanics",
    "unresolved_reason": "The cited static evidence leaves the competing owner, slot, layout, or lifecycle interpretation unresolved; no positive original runtime or MSVC RTTI evidence is available."
  },
  {
    "anchors": [
      "0x00b21340",
      "0x00b21340",
      "0x00b1d870",
      "0x00b1d870",
      "0x00b1db60",
      "0x00b1db60",
      "0x00b1dbd0",
      "0x00b1dbd0",
      "0x00b21340",
      "0x00b267f0",
      "0x00b267f0",
      "0x00b5b840",
      "0x00b5b840",
      "0x00b5b880",
      "0x00b5b880",
      "0x00b5b8a0"
    ],
    "conflict_id": "noun_update_flag_writers",
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
      "0x00b21340",
      "0x00b21340",
      "0x00acd9a0",
      "0x00acd9a0",
      "0x00acd9a0",
      "0x00ace2c0",
      "0x00ace2c0",
      "0x00ace2c0",
      "0x00b25f40",
      "0x00b25f40",
      "0x00ba0080",
      "0x00ba0080",
      "0x00ba0080",
      "0x00bf9820",
      "0x00bf9820",
      "0x00ba8420"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/additional-domains.json:0",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  }
]
```
