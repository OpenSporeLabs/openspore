# Evidence 0x00e5c780

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `e4a7aaa5ce14ba7a8db8069f9188a30f5e4c5b4559b91687d6a658a19830c937`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "__thiscall observed",
  "return_observation": "The live function ends through void RET paths after writing the result pointer and cleans two stack words with RET 8.",
  "return_type": "void",
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "observed_use": "Receives the node pointer selected by the search.",
      "position": 1,
      "type": "OrderedMapEntry **",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x08",
      "observed_use": "The first stack word is dereferenced as the unsigned comparison key.",
      "position": 2,
      "type": "const std::uint32_t *",
      "width_bytes": 4
    }
  ]
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
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x8",
    "return_register": "EAX",
    "return_semantics": "pointer_like_in_EAX",
    "saved_registers": [
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
    "stack_cleanup_bytes": 8,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x8"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -4, so the listing is not one path",
    "sret_vs_out_param: entry slot 0 is written through a pointer"
  ],
  "cleanup": {
    "bytes": 8,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x8",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "4a8bc0e73dd1f16fe7bd121f8b9e27dd6d965d90071c73a9f49d2d4bc6994d99",
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
        "obs-0015",
        "obs-0018"
      ],
      "claim": "the callee pops 8 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 8,
        "side": "callee"
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0013",
        "obs-0016"
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
        "obs-0002",
        "obs-0003",
        "obs-0008"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          12,
          16,
          28
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0002",
        "obs-0003",
        "obs-0008",
        "obs-0015",
        "obs-0018"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0013"
      ],
      "claim": "a hidden struct-return pointer is a hypothesis only: entry slot 0 is written through a pointer",
      "confidence": "INFERRED",
      "id": "S1",
      "value": {
        "ambiguity": "sret_vs_out_param",
        "present": null,
        "slot": 4
      }
    },
    {
      "based_on": [
        "obs-0015",
        "obs-0018"
      ],
      "claim": "in MSVC x86 a hidden struct-return pointer is always stack slot 0 while this is in ECX, so the two never contend",
      "confidence": "APPROXIMATION",
      "id": "S3",
      "value": {
        "ordering": "not_applicable"
      }
    },
    {
      "based_on": [
        "obs-0015",
        "obs-0018"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0015",
        "obs-0018"
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
      "at": "0x00e5c780",
      "count": 4,
      "first_use": 0,
      "first_write_index": 4,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ECX + 0xc]",
      "reg": "ECX"
    },
    {
      "at": "0x00e5c780",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ECX + 0xc]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00e5c783",
      "count": 3,
      "first_use": 1,
      "first_write_index": null,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "LEA EDX,[ECX + 0x4]",
      "reg": "EDX"
    },
    {
      "at": "0x00e5c786",
      "count": 3,
      "first_use": 2,
      "first_write_index": 3,
      "id": "obs-0004",
      "index": 2,
      "kind"
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
    "name": "Editors::cEditor::Update",
    "reconstructed": false,
    "va": "0x0058be50"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0059c6e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0059ca70"
  },
  {
    "name": "EditorAnimWorld_GetCreatureController_0059cac0",
    "reconstructed": true,
    "va": "0x0059cac0"
  },
  {
    "name": "EditorAnimWorld_PlayAnimation_0059cb10",
    "reconstructed": true,
    "va": "0x0059cb10"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0059cbd0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0059cc40"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0059cd20"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0059cdb0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0059ce30"
  },
  {
    "name": "EditorAnimWorld_SetTargetAngle_0059cea0",
    "reconstructed": true,
    "va": "0x0059cea0"
  },
  {
    "name": "EditorAnimWorld_SetTargetPosition_0059cf00",
    "reconstructed": true,
    "va": "0x0059cf00"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0059cf60"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0059cfb0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0059d010"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0059d060"
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
      "0x00e63560",
      "0x00e63560",
      "0x00acd9a0",
      "0x00ace2c0",
      "0x00b25f40",
      "0x00ba0080",
      "0x00bf9820",
      "0x00e5c780",
      "0x00551240",
      "0x0067dd90",
      "0x00e66280",
      "0x00e66840",
      "0x00e63560",
      "0x00e5c780",
      "0x00e63560",
      "0x00571f80"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/additional-domains.json:4",
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
      "0x00845310",
      "0x00845310",
      "0x00acd9a0",
      "0x00ace2c0",
      "0x00b25f40",
      "0x00ba0080",
      "0x00bf9820",
      "0x00e5c780",
      "0x00844f70",
      "0x00841440",
      "0x00846e60",
      "0x00841d40",
      "0x00845790",
      "0x00842d10",
      "0x00844180",
      "0x00843000"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/additional-domains.json:8",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [],
    "kind": "semantic_decomp_contradiction",
    "path": "evidence.5",
    "source": "knowledgegraph/research/semantic-decomp/worker-01-gameglobal.json",
    "statement": {
      "kind": "repository_contradiction",
      "source": "docs/analysis/architecture-resolution.md:50-86",
      "statement": "The committed resolution claims lower_bound and rejects exact find; this conflicts with the target's final CMP/JC equality check and is retained as a contradiction."
    },
    "va": "0x00e5c780"
  },
  {
    "anchors": [
      "0x0059c740"
    ],
    "kind": "semantic_decomp_contradiction",
    "path": "evidence.6",
    "source": "knowledgegraph/research/semantic-decomp/worker-01-gameglobal.json",
    "statement": {
      "kind": "repository_contradiction",
      "source": "knowledgegraph/research/global-campaign-2026/conflicts/track-a-type-signature.json:602-779",
      "statement": "The conflict artifact calls the target an ordered lower-bound helper, while the live target body and sibling 0x0059c740 enforce exact-key selection."
    },
    "va": "0x00e5c780"
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
  "count": 31,
  "instructions": [
    {
      "address": "00e5c780",
      "instruction": "MOV EAX,dword ptr [ECX + 0xc]"
    },
    {
      "address": "00e5c783",
      "instruction": "LEA EDX,[ECX + 0x4]"
    },
    {
      "address": "00e5c786",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00e5c787",
      "instruction": "MOV EDI,dword ptr [ESP + 0xc]"
    },
    {
      "address": "00e5c78b",
      "instruction": "MOV ECX,EDX"
    },
    {
      "address": "00e5c78d",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00e5c78f",
      "instruction": "JZ 0x00e5c7a7"
    },
    {
      "address": "00e5c791",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00e5c792",
      "instruction": "MOV ESI,dword ptr [EDI]"
    },
    {
      "address": "00e5c794",
      "instruction": "CMP dword ptr [EAX + 0x10],ESI"
    },
    {
      "address": "00e5c797",
      "instruction": "JC 0x00e5c7a0"
    },
    {
      "address": "00e5c799",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00e5c79b",
      "instruction": "MOV EAX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "00e5c79e",
      "instruction": "JMP 0x00e5c7a2"
    },
    {
      "address": "00e5c7a0",
      "instruction": "MOV EAX,dword ptr [EAX]"
    },
    {
      "address": "00e5c7a2",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00e5c7a4",
      "instruction": "JNZ 0x00e5c794"
    },
    {
      "address": "00e5c7a6",
      "instruction": "POP ESI"
    },
    {
      "address": "00e5c7a7",
      "instruction": "CMP ECX,EDX"
    },
    {
      "address": "00e5c7a9",
      "instruction": "JZ 0x00e5c7bc"
    },
    {
      "address": "00e5c7ab",
      "instruction": "MOV EAX,dword ptr [EDI]"
    },
    {
      "address": "00e5c7ad",
      "instruction": "CMP EAX,dword ptr [ECX + 0x10]"
    },
    {
      "address": "00e5c7b0",
      "instruction": "JC 0x00e5c7bc"
    },
    {
      "address": "00e5c7b2",
      "instruction": "MOV EAX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "00e5c7b6",
      "instruction": "MOV dword ptr [EAX],ECX"
    },
    {
      "address": "00e5c7b8",
      "instruction": "POP EDI"
    },
    {
      "address": "00e5c7b9",
      "instruction": "RET 0x8"
    },
    {
      "address": "00e5c7bc",
      "instruction": "MOV EAX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "00e5c7c0",
      "instruction": "MOV dword ptr [EAX],EDX"
    },
    {
      "address": "00e5c7c2",
      "instruction": "POP EDI"
    },
    {
      "address": "00e5c7c3",
      "instruction": "RET 0x8"
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
  "original_bytes": 25335,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"__thiscall observed\",\n    \"return_observation\": \"The live function ends through void RET paths after writing the result pointer and cleans two stack words with RET 8.\",\n    \"return_type\": \"void\",\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"observed_use\": \"Receives the node pointer selected by the search.\",\n        \"position\": 1,\n        \"type\": \"OrderedMapEntry **\",\n        \"width_bytes\": 4\n      },\n      {\n        \"entry_offset\": \"ESP+0x08\",\n        \"observed_use\": \"The first stack word is dereferenced as the unsigned comparison key.\",\n        \"position\": 2,\n        \"type\": \"const std::uint32_t *\",\n        \"width_bytes\": 4\n      }\n    ]\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_class\",\n        \"shared_types:OrderedMap,OrderedMapEntry,TargetWord\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-20-GAMEGLOBAL\",\n      \"score\": 24,\n      \"symbol\": \"pkg20_gameglobal_00ba83a0\",\n      \"va\": \"0x00ba83a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_class\",\n        \"shared_types:OrderedMap,OrderedMapEntry,TargetWord\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-20-GAMEGLOBAL\",\n      \"score\": 24,\n      \"symbol\": \"pkg20_gameglobal_00ba8420\",\n      \"va\": \"0x00ba8420\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:OrderedMap,OrderedMapEntry,void *\",\n        \"same_calling_convention\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-11-SIM-CORE\",\n      \"score\": 14,\n      \"symbol\": \"pkg11_sim_core_00b21340\",\n      \"va\": \"0x00b21340\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:OrderedMapEntry,TargetWord\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-11-SIM-CORE\",\n      \"score\": 9,\n      \"symbol\": \"Simulator_LookupEmpireByPoliticalId\",\n      \"va\": \"0x00ba9370\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:TargetWord\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 3,\n      \"symbol\": \"pair_vector_insert_004786e0\",\n      \"va\": \"0x004786e0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:TargetWord\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 3,\n      \"symbol\": \"stream_probe_dispatch_004bc540\",\n      \"va\": \"0x004bc540\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:TargetWord\"\n      ],\n      \"package\": \"PKG-SKINNER-SAFE-WAVE11\",\n      \"score\": 3,\n      \"symbol\": \"skin_job_setup_0051a9a0\",\n      \"va\": \"0x0051a9a0\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 3,\n      \"symbol\": \"EditorAnimWorld_GetCreatureController_0059cac0\",\n      \"va\": \"0x0059cac0\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"The candidate walk and final exact-key guard are exact; runtime root publication, lifetime, and caller fault behavior remain separate from the resolved static contract.\",\n  \"audit_findings\": [\n    \"P0-001\"\n  ],\n  \"audit_status\": \"clean_after_static_resolution\",\n  \"blocked\": false,\n  \"blockers\": [\n    \"No differential runtime corpus is available for the 239 caller sites; runtime observation is not required for the static helper contract.\",\n    \"The live Ghidra prototype is undefined and does not name the generic map value type.\"\n  ],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OrderedMap\",\n  \"cluster\": \"gameglobal-misc\",\n  \"confidence\": 0.95,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": \"Editors::cEditor::Update\",\n        \"reconstructed\": false,\n        \"va\": \"0x0058be50\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0059c6e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0059ca70\"\n      },\n      {\n        \"name\": \"EditorAnimWorld_GetCreatureController_0059cac0\",\n        \"reconstructed\": true,\n        \"va\": \"0x0059cac0\"\n      },\n      {\n        \"name\": \"EditorAnimWorld_PlayAnimation_0059cb10\",\n        \"reconstructed\": true,\n        \"va\": \"0x0059cb10\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0059cbd0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0059cc40\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0059cd20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0059cdb0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0059ce30\"\n      },\n      {\n        \"name\": \"EditorAnimWorld_SetTargetAngle_0059cea0\",\n        \"reconstructed\": true,\n        \"va\": \"0x0059cea0\"\n      },\n      {\n        \"name\": \"EditorAnimWorld_SetTargetPosition_0059cf00\",\n        \"reconstructed\": true,\n        \"va\": \"0x0059cf00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0059cf60\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0059cfb0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0059d010\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0059d060\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\":
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
  "body_end": "00e5c7c5",
  "body_span_bytes": 70,
  "body_start": "00e5c780",
  "callees": [],
  "callers": [
    "FUN_00bb24d0",
    "FUN_00b21340",
    "FUN_0059cc40",
    "FUN_009fc310",
    "FUN_00dd67d0",
    "FUN_00a39620",
    "FUN_00dd6df0",
    "FUN_00e0f9c0",
    "FUN_00cc6910",
    "FUN_006aa130",
    "FUN_00ff9800",
    "FUN_00fe4150",
    "FUN_00b20750",
    "FUN_0059d300",
    "FUN_0059cd20",
    "FUN_00dd3810",
    "FUN_0069e9e0",
    "FUN_010021a0",
    "FUN_00de5cb0",
    "FUN_00e052d0",
    "FUN_00e063d0",
    "FUN_005f0a60",
    "FUN_009a37a0",
    "FUN_00b21410",
    "FUN_00e0d940",
    "FUN_0059d180",
    "FUN_01058c90",
    "FUN_00ccbb60",
    "FUN_00ba9f80",
    "Simulator::Cell::cCellGFX::PreloadCellResource",
    "FUN_00c76a30",
    "FUN_00b32190",
    "FUN_00c932a0",
    "FUN_0068abb0",
    "FUN_009fcb30",
    "FUN_005f05e0",
    "FUN_005a9050",
    "FUN_00b1c8d0",
    "FUN_00b23560",
    "FUN_00e2ab10",
    "FUN_00e18cb0",
    "FUN_00a25000",
    "FUN_00802160",
    "FUN_00a63860",
    "FUN_00fe4180",
    "FUN_006b2000",
    "FUN_008d68c0",
    "FUN_00810620",
    "FUN_00f1d430",
    "FUN_008024e0",
    "FUN_00b9d640",
    "Editors::cEditorAnimWorld::SetTargetAngle",
    "FUN_00a27e60",
    "FUN_00fe9580",
    "FUN_00c78450",
    "FUN_00de6e80",
    "FUN_00ba93b0",
    "FUN_00beb1c0",
    "FUN_0059d240",
    "FUN_00e19350",
    "FUN_00c769b0",
    "FUN_00643e70",
    "FUN_00633230",
    "FUN_0102daa0",
    "FUN_00e40010",
    "FUN_00a060a0",
    "FUN_00d30ee0",
    "FUN_00abea40",
    "FUN_0059ce30",
    "FUN_005d3300",
    "FUN_00dd6710",
    "FUN_006a0110",
    "FUN_00fe6210",
    "FUN_00bb99e0",
    "FUN_009e1850",
    "FUN_006b1f90",
    "FUN_00ff8300",
    "FUN_00e06630",
    "FUN_01013a70",
    "FUN_00e10220",
    "FUN_00baf790",
    "FUN_00fe4230",
    "FUN_00de6f20",
    "FUN_00e0df30",
    "FUN_0082b9c0",
    "FUN_00ccaff0",
    "FUN_00b20790",
    "Editors::cEditorAnimWorld::GetCreatureController",
    "Editors::cEditorAnimWorld::SetTargetPosition",
    "FUN_00fecbb0",
    "FUN_00ebc2f0",
    "FUN_009aba80",
    "FUN_00801b60",
    "FUN_00bb3750",
    "FUN_00ba92e0",
    "FUN_00cc5170",
    "FUN_00baa930",
    "FUN_00d06710",
    "FUN_00fe4710",
    "FUN_00fee930",
    "FUN_00cc5070",
    "FUN_00e9e2f0",
    "FUN_00dd6ac0",
    "FUN_00dd6d10",
    "FUN_00b033b0",
    "FUN_00ebcc80",
    "FUN_00e40080",
    "FUN_00e40670",
    "FUN_00fe45f0",
    "FUN_00b2b5b0",
    "FUN_009abe90",
    "FUN_00811110",
    "FUN_00fe41c0",
    "FUN_00b99ed0",
    "FUN_00d05d90",
    "FUN_00feed30",
    "FUN_00ceb430",
    "FUN_00ba9370",
    "Editors::cEditorAnimWorld::DestroyCreature",
    "FUN_00a63dd0",
    "FUN_00b02fa0",
    "FUN_00bf45f0",
    "FUN_009abd10",
    "FUN_00b201a0",
    "FUN_00fe4900",
    "FUN_00fe43c0",
    "FUN_00dd6930",
    "FUN_00bb1340",
    "FUN_00e18b10",
    "FUN_00fe47a0",
    "FUN_0059cbd0",
    "Editors::cEditor::Update",
    "FUN_0059d010",
    "FUN_00f1f600",
    "FUN_00810660",
    "FUN_00de7010",
    "FUN_00fe66f0",
    "FUN_00b2ede0",
    "FUN_00dd68e0",
    "FUN_0059cf60",
    "FUN_00c77450",
    "FUN_00e9f9c0",
    "FUN_00ccb0f0",
    "FUN_0059d110",
    "FUN_009aa820",
    "FUN_00fe6690",
    "FUN_00c76800",
    "FUN_00baf630",
    "FUN_00b73f30",
    "FUN_00ceae70",
    "FUN_00810760",
    "FUN_00a63680",
    "FUN_00801bb0",
    "FUN_00e3f2a0",
    "FUN_00a0d570",
    "FUN_006b2400",
    "FUN_006aa4c0",
    "FUN_00fe46a0",
    "FUN_00f1d500",
    "FUN_00e2c840",
    "FUN_00d01470",
    "FUN_006b2090",
    "FUN_00abea90",
    "FUN_00e3f010",
    "FUN_00661d10",
    "FUN_00dd69f0",
    "FUN_00dd35c0",
    "FUN_00e0df70",
    "FUN_0059d1e0",
    "FUN_00c76790",
    "FUN_0068aae0",
    "EditorAnimWorld_PlayAnimation",
    "FUN_00c7ae80",
    "FUN_00c7d7a0",
    "FUN_006111c0",
    "FUN_00bad7a0",
    "FUN_009ab710",
    "FUN_00c93160",
    "FUN_00c7d6d0",
    "FUN_0059cfb0",
    "FUN_00f20d20",
    "FUN_008117f0",
    "FUN_00e655c0",
    "FUN_00ccc400",
    "FUN_00dd6a70",
    "FUN_0059d060",
    "FUN_00cca5b0",
    "FUN_00b6baf0",
    "FUN_009fc0f0",
    "FUN_00dd6980",
    "FUN_00a05ee0",
    "FUN_00d03b80",
    "FUN_00dd6b70",
    "Editors::cEditorAnimWorld::GetAnimatedCreature",
    "FUN_00cfbc10",
    "FUN_009a4430",
    "FUN_00b998a0",
    "FUN_00ceab20",
    "FUN_0059cdb0",
    "FUN_00642c40",
    "FUN_00c33580",
    "FUN_009e5b40",
    "FUN_00dd6bc0",
    "FUN_00b6a6e0",
    "FUN_00baa110",
    "FUN_00b6e7b0",
    "FUN_00d015d0",
    "FUN_005d25c0",
    "FUN_0094f870",
    "FUN_0059d0b0",
    "FUN_00802050",
    "FUN_00fecbf0",
    "FUN_00dd6b20",
    "FUN_00642c10",
    "FUN_006a3f00",
    "FUN_00de74c0",
    "FUN_010107b0",
    "FUN_00a07fc0",
    "FUN_00fe4830",
    "FUN_00a0c270",
    "FUN_006886b0",
    "FUN_005d2480",
    "FUN_00c784c0",
    "FUN_005d4630",
    "FUN_00f243c0",
    "FUN_00a636b0",
    "FUN_00b320d0",
    "FUN_005d43d0",
    "FUN_00b76f10",
    "FUN_00baf700",
    "FUN_00dd6810",
    "FUN_00688830",
    "FUN_0102d820",
    "FUN_00b023d0",
    "FUN_00c99dc0",
    "FUN_00b71510",
    "FUN_0094f910",
    "FUN_00cca880",
    "FUN_00f3e6d0"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "00e5c780",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "map_int_whatever_find",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_res
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
  "file": "src/reconstruction/pkg20_gameglobal/map_search.cpp",
  "files": [
    "reconstruction/staging/pkg20-gameglobal/map_search.cpp",
    "reconstruction/staging/pkg20-gameglobal/map_search.hpp",
    "reconstruction/staging/pkg20-gameglobal/map_search_model_test.cpp",
    "src/reconstruction/pkg20_gameglobal/map_search.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-source-wave2/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg20-gameglobal/00e5c780.json"
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
    "gate-map-root-publication-and-caller-fault-paths"
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
  "original_bytes": 7924,
  "preview": "{\n  \"category\": \"GAMEPLAY_LOGIC\",\n  \"classification\": \"BOUNDED_SEMANTIC\",\n  \"confidence\": {\n    \"identity\": 0.86,\n    \"mechanics\": 0.99\n  },\n  \"contradictions\": [\n    {\n      \"path\": \"evidence.5\",\n      \"source\": \"knowledgegraph/research/semantic-decomp/worker-01-gameglobal.json\",\n      \"value\": {\n        \"kind\": \"repository_contradiction\",\n        \"source\": \"docs/analysis/architecture-resolution.md:50-86\",\n        \"statement\": \"The committed resolution claims lower_bound and rejects exact find; this conflicts with the target's final CMP/JC equality check and is retained as a contradiction.\"\n      }\n    },\n    {\n      \"path\": \"evidence.6\",\n      \"source\": \"knowledgegraph/research/semantic-decomp/worker-01-gameglobal.json\",\n      \"value\": {\n        \"kind\": \"repository_contradiction\",\n        \"source\": \"knowledgegraph/research/global-campaign-2026/conflicts/track-a-type-signature.json:602-779\",\n        \"statement\": \"The conflict artifact calls the target an ordered lower-bound helper, while the live target body and sibling 0x0059c740 enforce exact-key selection.\"\n      }\n    }\n  ],\n  \"downstream_unlock_count\": 239,\n  \"evidence\": [\n    {\n      \"kind\": \"disassembly\",\n      \"source\": \"ghidra://SporeApp.exe@0x00e5c780\",\n      \"statement\": \"The 31 instructions load map+0x0c, use map+0x04 as sentinel, compare node+0x10 unsigned against *key, reject a candidate whose key is greater than *key, write the exact candidate through the output pointer, and return with RET 0x8.\"\n    },\n    {\n      \"kind\": \"decompilation\",\n      \"source\": \"ghidra://SporeApp.exe@0x00e5c780\",\n      \"statement\": \"Targeted pseudocode exposes the same sentinel-backed tree traversal and output assignment.\"\n    },\n    {\n      \"kind\": \"direct_caller\",\n      \"source\": \"ghidra://SporeApp.exe@0x00b21340\",\n      \"statement\": \"The caller passes a noun-ID key and output local, compares to the owner map end sentinel, and invokes insertion on a miss.\"\n    },\n    {\n      \"kind\": \"direct_caller\",\n      \"source\": \"ghidra://SporeApp.exe@0x00ba9370\",\n      \"statement\": \"The caller passes cStarManager+0x150 and reads node payload +0x14.\"\n    },\n    {\n      \"kind\": \"repository\",\n      \"source\": \"docs/analysis/simulator-shared-state-interface.md:188-216\",\n      \"statement\": \"The committed interface freeze records mEmpires +0x150, map end +0x154, and payload +0x14.\"\n    },\n    {\n      \"kind\": \"repository_contradiction\",\n      \"source\": \"docs/analysis/architecture-resolution.md:50-86\",\n      \"statement\": \"The committed resolution claims lower_bound and rejects exact find; this conflicts with the target's final CMP/JC equality check and is retained as a contradiction.\"\n    },\n    {\n      \"kind\": \"repository_contradiction\",\n      \"source\": \"knowledgegraph/research/global-campaign-2026/conflicts/track-a-type-signature.json:602-779\",\n      \"statement\": \"The conflict artifact calls the target an ordered lower-bound helper, while the live target body and sibling 0x0059c740 enforce exact-key selection.\"\n    }\n  ],\n  \"family\": \"generic unsigned ordered-map exact-find primitive\",\n  \"interfaces\": {\n    \"boundaries\": {},\n    \"direct_callees\": {\n      \"count\": 0,\n      \"items\": [],\n      \"status\": \"leaf\"\n    },\n    \"direct_callers\": {\n      \"canonical\": {\n        \"direct_call_references\": 265,\n        \"fan_out_external\": 0,\n        \"fan_out_internal\": 0,\n        \"gameplay_fan_in\": 49,\n        \"unique_direct_caller_functions\": 239\n      },\n      \"read_only_ghidra\": {\n        \"direct_call_xrefs\": 308,\n        \"unique_direct_caller_functions\": 239\n      },\n      \"representative\": [\n        {\n          \"keys\": [\n            \"name\",\n            \"use\",\n            \"va\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"name\",\n            \"use\",\n            \"va\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"name\",\n            \"use\",\n            \"va\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"name\",\n            \"use\",\n            \"va\"\n          ]\n        }\n      ]\n    },\n    \"globals\": [],\n    \"structures\": [\n      {\n        \"fields\": [\n          \"map+0x04 end\",\n          \"map+0x0c root\",\n          \"node+0x00 left\",\n          \"node+0x04 right\",\n          \"node+0x10 uint32_t key\",\n          \"node+0x14 opaque payload\"\n        ],\n        \"name\": \"EASTL ordered map/node\",\n        \"status\": \"observed layout\"\n      },\n      {\n        \"field\": \"mNounMap at receiver+0x98; the helper receives the map beginning there.\",\n        \"name\": \"cGameNounManager\",\n        \"status\": \"representative owner\"\n      },\n      {\n        \"field\": \"mEmpires at receiver+0x150; end sentinel observed at receiver+0x154.\",\n        \"name\": \"cStarManager\",\n        \"status\": \"representative owner\"\n      }\n    ],\n    \"vtables\": [],\n    \"worker_contract_surface\": {\n      \"failure_behavior\": [],\n      \"identity_boundary\": \"not_reported\",\n      \"inputs\": [\n        {\n          \"keys\": [\n            \"meaning\",\n            \"name\",\n            \"ordinal\",\n            \"storage\",\n            \"type\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"direction\",\n            \"meaning\",\n            \"name\",\n            \"ordinal\",\n            \"storage\",\n            \"type\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"meaning\",\n            \"name\",\n            \"ordinal\",\n            \"storage\",\n            \"type\"\n          ]\n        }\n      ],\n      \"ordering\": [],\n      \"outputs\": [],\n      \"postc
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
  "OrderedMap",
  "OrderedMapEntry",
  "OrderedMapEntry **",
  "OrderedMapNode",
  "OrderedMapNode *",
  "TargetWord",
  "const std::uint32_t *",
  "map<unsigned int, int>",
  "rbtree_node_base",
  "std::uint32_t",
  "void",
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
      "0x00e63560",
      "0x00e63560",
      "0x00acd9a0",
      "0x00ace2c0",
      "0x00b25f40",
      "0x00ba0080",
      "0x00bf9820",
      "0x00e5c780",
      "0x00551240",
      "0x0067dd90",
      "0x00e66280",
      "0x00e66840",
      "0x00e63560",
      "0x00e5c780",
      "0x00e63560",
      "0x00571f80"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/additional-domains.json:4",
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
      "0x00845310",
      "0x00845310",
      "0x00acd9a0",
      "0x00ace2c0",
      "0x00b25f40",
      "0x00ba0080",
      "0x00bf9820",
      "0x00e5c780",
      "0x00844f70",
      "0x00841440",
      "0x00846e60",
      "0x00841d40",
      "0x00845790",
      "0x00842d10",
      "0x00844180",
      "0x00843000"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/additional-domains.json:8",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [],
    "kind": "semantic_decomp_contradiction",
    "path": "evidence.5",
    "source": "knowledgegraph/research/semantic-decomp/worker-01-gameglobal.json",
    "statement": {
      "kind": "repository_contradiction",
      "source": "docs/analysis/architecture-resolution.md:50-86",
      "statement": "The committed resolution claims lower_bound and rejects exact find; this conflicts with the target's final CMP/JC equality check and is retained as a contradiction."
    },
    "va": "0x00e5c780"
  },
  {
    "anchors": [
      "0x0059c740"
    ],
    "kind": "semantic_decomp_contradiction",
    "path": "evidence.6",
    "source": "knowledgegraph/research/semantic-decomp/worker-01-gameglobal.json",
    "statement": {
      "kind": "repository_contradiction",
      "source": "knowledgegraph/research/global-campaign-2026/conflicts/track-a-type
[TRUNCATED]
```
