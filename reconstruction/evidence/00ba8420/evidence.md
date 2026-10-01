# Evidence 0x00ba8420

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `2126112eeefb7cc2fcf6a3fcd0803c174ffb39e8fe4c80ec990230af16a13d9c`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "__thiscall observed",
  "hidden_this_register": "ECX",
  "hidden_this_type": "OrderedMap*",
  "return_register": "EAX",
  "return_type": "MapInsertResult*",
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "output",
      "observed_use": "Receives the existing or newly inserted entry and the one-byte insertion result.",
      "position": 1,
      "type": "MapInsertResult*",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x08",
      "name": "handoff",
      "observed_use": "No semantic use is established by the target body; preserved to retain the three-word caller boundary.",
      "position": 2,
      "type": "opaque 32-bit handoff word",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x0C",
      "name": "pair",
      "observed_use": "The first word is read as the unsigned query key and the pair is forwarded to node allocation.",
      "position": 3,
      "type": "const MapInsertPair*",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 12
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
      "entry_ESP+0x8"
    ],
    "ordinary_stack_arguments": [
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
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0xc",
    "return_register": "EAX",
    "return_semantics": "pointer_like_in_EAX",
    "saved_registers": [
      "EBP",
      "EDI",
      "ESI"
    ],
    "stack_arguments": [
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
    "stack_cleanup_bytes": 12,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0xc"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +16, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register"
  ],
  "cleanup": {
    "bytes": 12,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0xc",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "39fb435c5ef87bef5f9c5a8c62e38ba5c154467f92b8d9573bffd68624fb4f67",
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
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0026",
        "obs-0031"
      ],
      "claim": "the callee pops 12 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 12,
        "side": "callee"
      }
    },
    {
      "based_on": [
        "obs-0004"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 1,
        "observed_slots": 1,
        "total_bytes": 8
      }
    },
    {
      "based_on": [
        "obs-0007",
        "obs-0008",
        "obs-0009",
        "obs-0015",
        "obs-0022",
        "obs-0027"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          8,
          12
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0007",
        "obs-0008",
        "obs-0009",
        "obs-0015",
        "obs-0022",
        "obs-0026",
        "obs-0027",
        "obs-0031"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0026",
        "obs-0031"
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
        "obs-0026",
        "obs-0031"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0026",
        "obs-0031"
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
      "at": "0x00ba8420",
      "count": 5,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH EBP",
      "reg": "EBP"
    },
    {
      "and_esp": null,
      "at": "0x00ba8420",
      "ebp_is_general_register": true,
      "fp": false,
      "id": "obs-0002",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": true,
      "push_ebp_at": 0,
      "raw": "PUSH EBP",
      "sub": null
    },
    {
      "at": "0x00ba8421",
      "count": 5,
      "first_use": 1,
      "first_write_index": 28,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EBP,dword ptr [ESP + 0xc]",
      "reg": "ESP"
    },
    {
      "at": "0x00ba8421",
      "base": "ESP",
      "disp": 12,
      "id": "obs-0004",
      "index": 1,
      "key": 8,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EBP,dword ptr [ESP + 0xc]",
      "resolved": true,
      "size": 4,
      "trust": "untrusted_frame"
    },
    {
      "at": "0x00ba8421",
      "definite": true,
      "id": "obs-0005",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EBP,dword ptr [ESP + 0xc]",
      "reg": "EBP",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00ba8425",
      "count": 5,
      "first_use": 2,
      "first_write_index": 3,
      "id": "obs-0006",
      "index": 2,
      
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "pkg20_gameglobal_00ba83a0",
    "reconstructed": true,
    "va": "0x00ba83a0"
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
    "name": "pkg11_sim_core_00b21340",
    "reconstructed": true,
    "va": "0x00b21340"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b2ede0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00baa660"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d02440"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d33c30"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00fe4d60"
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
  "count": 59,
  "instructions": [
    {
      "address": "00ba8420",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00ba8421",
      "instruction": "MOV EBP,dword ptr [ESP + 0xc]"
    },
    {
      "address": "00ba8425",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00ba8426",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00ba8428",
      "instruction": "MOV ECX,dword ptr [ESI + 0xc]"
    },
    {
      "address": "00ba842b",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00ba842c",
      "instruction": "LEA EAX,[ESI + 0x4]"
    },
    {
      "address": "00ba842f",
      "instruction": "MOV DL,0x1"
    },
    {
      "address": "00ba8431",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00ba8433",
      "instruction": "JZ 0x00ba844f"
    },
    {
      "address": "00ba8435",
      "instruction": "MOV EDI,dword ptr [EBP]"
    },
    {
      "address": "00ba8438",
      "instruction": "CMP EDI,dword ptr [ECX + 0x10]"
    },
    {
      "address": "00ba843b",
      "instruction": "MOV EAX,ECX"
    },
    {
      "address": "00ba843d",
      "instruction": "SETC DL"
    },
    {
      "address": "00ba8440",
      "instruction": "TEST DL,DL"
    },
    {
      "address": "00ba8442",
      "instruction": "JZ 0x00ba8449"
    },
    {
      "address": "00ba8444",
      "instruction": "MOV ECX,dword ptr [ECX + 0x4]"
    },
    {
      "address": "00ba8447",
      "instruction": "JMP 0x00ba844b"
    },
    {
      "address": "00ba8449",
      "instruction": "MOV ECX,dword ptr [ECX]"
    },
    {
      "address": "00ba844b",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00ba844d",
      "instruction": "JNZ 0x00ba8438"
    },
    {
      "address": "00ba844f",
      "instruction": "MOV EDI,EAX"
    },
    {
      "address": "00ba8451",
      "instruction": "TEST DL,DL"
    },
    {
      "address": "00ba8453",
      "instruction": "JZ 0x00ba8463"
    },
    {
      "address": "00ba8455",
      "instruction": "CMP EAX,dword ptr [ESI + 0x8]"
    },
    {
      "address": "00ba8458",
      "instruction": "JZ 0x00ba8471"
    },
    {
      "address": "00ba845a",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00ba845b",
      "instruction": "CALL 0x009215c0"
    },
    {
      "address": "00ba8460",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "00ba8463",
      "instruction": "MOV EDX,dword ptr [EAX + 0x10]"
    },
    {
      "address": "00ba8466",
      "instruction": "CMP EDX,dword ptr [EBP]"
    },
    {
      "address": "00ba8469",
      "instruction": "JNC 0x00ba8495"
    },
    {
      "address": "00ba846b",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00ba846d",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00ba846e",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00ba846f",
      "instruction": "JMP 0x00ba8475"
    },
    {
      "address": "00ba8471",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00ba8473",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00ba8474",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00ba8475",
      "instruction": "LEA EAX,[ESP + 0x20]"
    },
    {
      "address": "00ba8479",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00ba847a",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00ba847c",
      "instruction": "CALL 0x00ba83a0"
    },
    {
      "address": "00ba8481",
      "instruction": "MOV EAX,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00ba8485",
      "instruction": "MOV ECX,dword ptr [ESP + 0x14]"
    },
    {
      "address": "00ba8489",
      "instruction": "POP EDI"
    },
    {
      "address": "00ba848a",
      "instruction": "POP ESI"
    },
    {
      "address": "00ba848b",
      "instruction": "MOV dword ptr [EAX],ECX"
    },
    {
      "address": "00ba848d",
      "instruction": "MOV byte ptr [EAX + 0x4],0x1"
    },
    {
      "address": "00ba8491",
      "instruction": "POP EBP"
    },
    {
      "address": "00ba8492",
      "instruction": "RET 0xc"
    },
    {
      "address": "00ba8495",
      "instruction": "MOV ECX,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00ba8499",
      "instruction": "POP EDI"
    },
    {
      "address": "00ba849a",
      "instruction": "POP ESI"
    },
    {
      "address": "00ba849b",
      "instruction": "MOV dword ptr [ECX],EAX"
    },
    {
      "address": "00ba849d",
      "instruction": "MOV byte ptr [ECX + 0x4],0x0"
    },
    {
      "address": "00ba84a1",
      "instruction": "MOV EAX,ECX"
    },
    {
      "address": "00ba84a3",
      "instruction": "POP EBP"
    },
    {
      "address": "00ba84a4",
      "instruction": "RET 0xc"
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
  "original_bytes": 9068,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"__thiscall observed\",\n    \"hidden_this_register\": \"ECX\",\n    \"hidden_this_type\": \"OrderedMap*\",\n    \"return_register\": \"EAX\",\n    \"return_type\": \"MapInsertResult*\",\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"name\": \"output\",\n        \"observed_use\": \"Receives the existing or newly inserted entry and the one-byte insertion result.\",\n        \"position\": 1,\n        \"type\": \"MapInsertResult*\",\n        \"width_bytes\": 4\n      },\n      {\n        \"entry_offset\": \"ESP+0x08\",\n        \"name\": \"handoff\",\n        \"observed_use\": \"No semantic use is established by the target body; preserved to retain the three-word caller boundary.\",\n        \"position\": 2,\n        \"type\": \"opaque 32-bit handoff word\",\n        \"width_bytes\": 4\n      },\n      {\n        \"entry_offset\": \"ESP+0x0C\",\n        \"name\": \"pair\",\n        \"observed_use\": \"The first word is read as the unsigned query key and the pair is forwarded to node allocation.\",\n        \"position\": 3,\n        \"type\": \"const MapInsertPair*\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 12\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:MapInsertPair,MapInsertResult,MapInsertResult*,OrderedMap\",\n        \"same_calling_convention\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-20-GAMEGLOBAL\",\n      \"score\": 33,\n      \"symbol\": \"pkg20_gameglobal_00ba83a0\",\n      \"va\": \"0x00ba83a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_class\",\n        \"shared_types:OrderedMap,OrderedMapEntry,TargetWord\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-20-GAMEGLOBAL\",\n      \"score\": 24,\n      \"symbol\": \"map_int_whatever_find\",\n      \"va\": \"0x00e5c780\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:OrderedMap,OrderedMapEntry\",\n        \"same_calling_convention\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-11-SIM-CORE\",\n      \"score\": 11,\n      \"symbol\": \"pkg11_sim_core_00b21340\",\n      \"va\": \"0x00b21340\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:OrderedMapEntry,TargetWord\"\n      ],\n      \"package\": \"PKG-11-SIM-CORE\",\n      \"score\": 6,\n      \"symbol\": \"Simulator_LookupEmpireByPoliticalId\",\n      \"va\": \"0x00ba9370\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:TargetWord\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 3,\n      \"symbol\": \"pair_vector_insert_004786e0\",\n      \"va\": \"0x004786e0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:TargetWord\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 3,\n      \"symbol\": \"stream_probe_dispatch_004bc540\",\n      \"va\": \"0x004bc540\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:TargetWord\"\n      ],\n      \"package\": \"PKG-SKINNER-SAFE-WAVE11\",\n      \"score\": 3,\n      \"symbol\": \"skin_job_setup_0051a9a0\",\n      \"va\": \"0x0051a9a0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:TargetWord\"\n      ],\n      \"package\": \"PKG-RUNTIME-SERVICES-WAVE7\",\n      \"score\": 3,\n      \"symbol\": \"editor_anim_event_message_post_0059d840\",\n      \"va\": \"0x0059d840\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [\n    \"No runtime trace is available for malformed-tree or allocator-failure paths.\",\n    \"The pair value and second handoff word remain semantically opaque.\",\n    \"The predecessor and red-black helpers remain external staging boundaries.\"\n  ],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OrderedMap\",\n  \"cluster\": null,\n  \"confidence\": 0.94,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"pkg20_gameglobal_00ba83a0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00ba83a0\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": \"pkg11_sim_core_00b21340\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b21340\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b2ede0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00baa660\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d02440\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d33c30\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00fe4d60\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00b21395\",\n        \"direction\": \"in\",\n        \"other\": \"0x00b21340\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b2f0db\",\n        \"direction\": \"in\",\n        \"other\": \"0x00b2ede0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00baa70c\",\n        \"direction\": \"in\",\n        \"other\": \"0x00baa660\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00d02526\",\n        \"direction\": \"in\",\n        \"other\": \"0x00d02440\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00d33c81\",\n        \"direction\": \"in\",\n        \"other\": \"0x00d33c30\",\n        \"reference_type\": \"di
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
  "body_end": "00ba84a6",
  "body_span_bytes": 135,
  "body_start": "00ba8420",
  "callees": [
    "FUN_009215c0",
    "FUN_00ba83a0"
  ],
  "callers": [
    "FUN_00baa660",
    "FUN_00b21340",
    "FUN_00d33c30",
    "FUN_00fe4d60",
    "FUN_00b2ede0",
    "FUN_00d02440"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00ba8420",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00ba8420",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x7a8420",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00ba8420(void)",
  "size_bytes": 135,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00ba8420",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 7,
  "xrefs": [
    {
      "from": "00b21395"
    },
    {
      "from": "00baa70c"
    },
    {
      "from": "00b2f0db"
    },
    {
      "from": "00d02526"
    },
    {
      "from": "00d33c81"
    },
    {
      "from": "00d33cce"
    },
    {
      "from": "00fe4e42"
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
  "file": "src/reconstruction/pkg20_gameglobal/map_insert.cpp",
  "files": [
    "reconstruction/staging/pkg20-gameglobal/map_insert.cpp",
    "reconstruction/staging/pkg20-gameglobal/map_insert.hpp",
    "reconstruction/staging/pkg20-gameglobal/map_insert_model_test.cpp",
    "src/reconstruction/pkg20_gameglobal/map_insert.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-source-wave3/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg20-gameglobal/00ba8420.json"
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
    "gate-map-insertion"
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
  "MapInsertPair",
  "MapInsertResult",
  "MapInsertResult*",
  "OrderedMap",
  "OrderedMap*",
  "OrderedMapEntry",
  "TargetWord",
  "const MapInsertPair*",
  "opaque 32-bit handoff word"
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
