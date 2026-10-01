# Evidence 0x00d2e480

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `c190bbf2a6739b575aae92c4093d4c2f3b52a51e261890f7817719c5d8d979d7`

## abi

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "abi": {
    "architecture": "x86-32",
    "calling_convention": "__cdecl",
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
    "receiver": false,
    "ret_form": "RET",
    "return_register": "XMM0",
    "return_semantics": "float_or_x87_in_XMM0",
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
  "abstained_because": [],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate",
    "side": "caller"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "fb899eb38dae99db1fa379ca778c59d8f176442b143331c3e28bc4a4dfcf241a",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__cdecl",
    "candidate_conventions": [
      "__cdecl",
      "__thiscall"
    ],
    "confidence": "INFERRED",
    "corroboration": "not_available"
  },
  "cross_validation": {
    "agreement": false,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 1,
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
        "obs-0005"
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
        "obs-0002"
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
        "obs-0005"
      ],
      "claim": "ECX is never read in any form, so there is no register receiver",
      "confidence": "OBSERVED",
      "id": "R2",
      "value": {
        "present": false
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0005"
      ],
      "claim": "calling convention is __cdecl: the caller cleans the stack and at least one entry slot is read",
      "confidence": "INFERRED",
      "id": "C9",
      "value": "__cdecl"
    },
    {
      "based_on": [
        "obs-0005"
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
        "obs-0005"
      ],
      "claim": "the return value is carried in XMM0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "XMM0"
    }
  ],
  "observations": [
    {
      "at": "0x00d2e480",
      "count": 1,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOVSS XMM0,dword ptr [ESP + 0x4]",
      "reg": "ESP"
    },
    {
      "at": "0x00d2e480",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0002",
      "index": 0,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOVSS XMM0,dword ptr [ESP + 0x4]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00d2e480",
      "definite": true,
      "id": "obs-0003",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOVSS XMM0,dword ptr [ESP + 0x4]",
      "reg": "XMM0",
      "write_kind": "unknown"
    },
    {
      "at": "0x00d2e486",
      "count": 1,
      "first_use": 1,
      "first_write_index": 0,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOVSS dword ptr [0x0169e398],XMM0",
      "reg": "XMM0"
    },
    {
      "at": "0x00d2e48e",
      "form": "RET",
      "id": "obs-0005",
      "imm": null,
      "index": 2,
      "kind": "RET",
      "raw": "RET"
    }
  ],
  "parse": {
    "declared_count": 3,
    "degraded": false,
    "esp_unresolved": false,
    "flow_complete": true,
    "frame": {
      "and_esp": null,
      "ebp_is_general_register": false,
      "fp": false,
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": false,
      "push_ebp_at": null,
      "sub": null
    },
    "layout": "json_instruction_list",
    "local_extent": 0,
    "unparsed": 0
  },
  "receiver": {
    "bounds_only": true,
    "confidence": "OBSERVED",
    "distinct_offsets": 0,
    "max_offset": null,
    "offsets": [],
    "present": false,
    "register": null,
    "shape": null,
    "written_through": 0
  },
  "return": {
    "aggregate_evidence": {
      "bulk_write": false
    },
    "confidence": "APPROXIMATION",
    "register": "XMM0",
    "register_class": "float_or_x87",
    "type": null,
    "void_possible": false
  },
  "schema": "openspore-abi-inference-1",
  "seh_or_cookie_frame": false,
  "sret": {
    "ambiguity": null,
    "basis": "entry slot 0 is not written through a pointer; DERIVED absence is weak, a struct filled through another alias would be missed",
    "candidates": null,
    "confidence": "APPROXIMATION",
    "eax_holds_slot0_at_ret": null,
    "hypothesis_confidence": null,
    "present": false,
    "slot": null,
    "this_interaction": null
  },
  "stack_arguments": {
    "confidence": "INFERRED",
    "derived_s
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
    "calling_convention": "__cdecl",
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
    "receiver": false,
    "ret_form": "RET",
    "return_register": "XMM0",
    "return_semantics": "float_or_x87_in_XMM0",
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
  "abstained_because": [],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate",
    "side": "caller"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "fb899eb38dae99db1fa379ca778c59d8f176442b143331c3e28bc4a4dfcf241a",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__cdecl",
    "candidate_conventions": [
      "__cdecl",
      "__thiscall"
    ],
    "confidence": "INFERRED",
    "corroboration": "not_available"
  },
  "cross_validation": {
    "agreement": false,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 1,
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
        "obs-0005"
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
        "obs-0002"
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
        "obs-0005"
      ],
      "claim": "ECX is never read in any form, so there is no register receiver",
      "confidence": "OBSERVED",
      "id": "R2",
      "value": {
        "present": false
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0005"
      ],
      "claim": "calling convention is __cdecl: the caller cleans the stack and at least one entry slot is read",
      "confidence": "INFERRED",
      "id": "C9",
      "value": "__cdecl"
    },
    {
      "based_on": [
        "obs-0005"
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
        "obs-0005"
      ],
      "claim": "the return value is carried in XMM0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "XMM0"
    }
  ],
  "observations": [
    {
      "at": "0x00d2e480",
      "count": 1,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOVSS XMM0,dword ptr [ESP + 0x4]",
      "reg": "ESP"
    },
    {
      "at": "0x00d2e480",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0002",
      "index": 0,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOVSS XMM0,dword ptr [ESP + 0x4]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00d2e480",
      "definite": true,
      "id": "obs-0003",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOVSS XMM0,dword ptr [ESP + 0x4]",
      "reg": "XMM0",
      "write_kind": "unknown"
    },
    {
      "at": "0x00d2e486",
      "count": 1,
      "first_use": 1,
      "first_write_index": 0,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOVSS dword ptr [0x0169e398],XMM0",
      "reg": "XMM0"
    },
    {
      "at": "0x00d2e48e",
      "form": "RET",
      "id": "obs-0005",
      "imm": null,
      "index": 2,
      "kind": "RET",
      "raw": "RET"
    }
  ],
  "parse": {
    "declared_count": 3,
    "degraded": false,
    "esp_unresolved": false,
    "flow_complete": true,
    "frame": {
      "and_esp": null,
      "ebp_is_general_register": false,
      "fp": false,
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": false,
      "push_ebp_at": null,
      "sub": null
    },
    "layout": "json_instruction_list",
    "local_extent": 0,
    "unparsed": 0
  },
  "receiver": {
    "bounds_only": true,
    "confidence": "OBSERVED",
    "distinct_offsets": 0,
    "max_offset": null,
    "offsets": [],
    "present": false,
    "register": null,
    "shape": null,
    "written_through": 0
  },
  "return": {
    "aggregate_evidence": {
      "bulk_write": false
    },
    "confidence": "APPROXIMATION",
    "register": "XMM0",
    "register_class": "float_or_x87",
    "type": null,
    "void_possible": false
  },
  "schema": "openspore-abi-inference-1",
  "seh_or_cookie_frame": false,
  "sret": {
    "ambiguity": null,
    "basis": "entry slot 0 is not written through a pointer; DERIVED absence is weak, a struct filled through another alias would be missed",
    "candidates": null,
    "confidence": "APPROXIMATION",
    "eax_holds_slot0_at_ret": null,
    "hypothesis_confidence": null,
    "present": false,
    "slot": null,
    "this_interaction": null
  },
  "stack_arguments": {
    "confidence": "INFERRED",
    "derived_s
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
    "va": "0x00d40230"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d43e30"
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
      "0x00d2e480",
      "0x00d2e480",
      "0x00d01410",
      "0x00d01410",
      "0x00d01ab0",
      "0x00d01ab0",
      "0x00d01e30",
      "0x00d01e30",
      "0x00d01f50",
      "0x00d01f50",
      "0x00d01ff0",
      "0x00d01ff0",
      "0x00d038e0",
      "0x00d038e0",
      "0x00d065a0",
      "0x00d065a0"
    ],
    "conflict_id": "U-003-civilization-progression",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The technology-level surface is recorded, but the binary writer/callback chain from one level to the next is not recovered.",
    "resolution_status": "The technology-level surface is recorded, but the binary writer/callback chain from one level to the next is not recovered.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00be34a0",
      "0x00d2e480",
      "0x00d2e480",
      "0x00aeb7b0",
      "0x00aeb160",
      "0x00aeb160",
      "0x00aeb7b0",
      "0x00aeb7b0",
      "0x00aebe90",
      "0x00aebe90",
      "0x00be34a0",
      "0x00d01410",
      "0x00d01410",
      "0x00d01ab0",
      "0x00d01ab0",
      "0x00d01e30"
    ],
    "conflict_id": "U-004-city-buildings",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
    "resolution_status": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00d2e380",
      "0x00d2e480",
      "0x00d2e8a0",
      "0x00d39360",
      "0x045ab96e",
      "0x00d2e480",
      "0x00aebe90",
      "0x045ab96e",
      "0x0067dcd0",
      "0x0067dcd0",
      "0x007d8420",
      "0x007d8420",
      "0x007d8cf0",
      "0x007d8cf0",
      "0x007d8d40",
      "0x007d8d40"
    ],
    "conflict_id": "U-005-evolution-level-promotion",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "0x45ab96e is a concrete action/message value with a guarded dispatch, but its consumer and brain-level/ability promotion are not identified.",
    "resolution_status": "0x45ab96e is a concrete action/message value with a guarded dispatch, but its consumer and brain-level/ability promotion are not identified.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00fe52c0",
      "0x00fe52c0",
      "0x00d2e350",
      "0x00d2e350",
      "0x00d2e380",
      "0x00d2e380",
      "0x00d2e480",
      "0x00d2e480",
      "0x00d2e8a0",
      "0x00d2e8a0",
      "0x00d3fcf0",
      "0x00d3fcf0",
      "0x00fe52c0",
      "0x00fe52c0",
      "0x00fe52c0",
      "0x00fe52c0"
    ],
    "conflict_id": "badge_state_domain",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
    "resolution_status": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00001278",
      "0x0000127c",
      "0x000010fc",
      "0x0000110c",
      "0x00001278",
      "0x0000127c",
      "0x00d2e350",
      "0x00d2e350",
      "0x00d2e380",
      "0x00d2e380",
      "0x00d2e480",
      "0x00d2e480",
      "0x00d2e8a0",
      "0x00d2e8a0",
      "0x00d3fcf0",
      "0x00d3fcf0"
    ],
    "conflict_id": "consequence_trait_rules",
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
      "0x00d2e380",
      "0x00d2e8a0",
      "0x00d2e8a0",
      "0x00d2e350",
      "0x00d2e350",
      "0x00d2e380",
      "0x00d2e380",
      "0x00d2e380",
      "0x00d2e480",
      "0x00d2e480",
      "0x00d2e8a0",
      "0x00d2e8a0",
      "0x00d2e8a0",
      "0x00d3fcf0",
      "0x00d3fcf0",
      "0x00feb880"
    ],
    "conflict_id": "evolution_numeric_thresholds",
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
      "0x00598db0",
      "0x00598db0",
      "0x00cc8c90",
      "0x00cc8c90",
      "0x00d2e3
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
  "count": 3,
  "instructions": [
    {
      "address": "00d2e480",
      "instruction": "MOVSS XMM0,dword ptr [ESP + 0x4]"
    },
    {
      "address": "00d2e486",
      "instruction": "MOVSS dword ptr [0x0169e398],XMM0"
    },
    {
      "address": "00d2e48e",
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
  "abi": {},
  "analogues": [
    {
      "match_basis": [
        "shared_types:UNCONDITIONAL_CALL"
      ],
      "package": "PKG-18-UI-SCRIPTING",
      "score": 3,
      "symbol": "FUN_005bf9d0",
      "va": "0x005bf9d0"
    },
    {
      "match_basis": [
        "shared_types:UNCONDITIONAL_CALL"
      ],
      "package": "PKG-18-UI-SCRIPTING",
      "score": 3,
      "symbol": "FUN_005c0100",
      "va": "0x005c0100"
    },
    {
      "match_basis": [
        "shared_types:UNCONDITIONAL_CALL"
      ],
      "package": "PKG-18-UI-SCRIPTING",
      "score": 3,
      "symbol": "FUN_005c0380",
      "va": "0x005c0380"
    },
    {
      "match_basis": [
        "shared_types:UNCONDITIONAL_CALL"
      ],
      "package": "wave6-resources",
      "score": 3,
      "symbol": "property_list_has_property_006a2470",
      "va": "0x006a2470"
    },
    {
      "match_basis": [
        "shared_types:UNCONDITIONAL_CALL"
      ],
      "package": "wave6-resources",
      "score": 3,
      "symbol": "property_list_get_property_object_006a24d0",
      "va": "0x006a24d0"
    },
    {
      "match_basis": [
        "shared_types:UNCONDITIONAL_CALL"
      ],
      "package": "PKG-13-C4-CREATURE-WAVE3",
      "score": 3,
      "symbol": "Simulator_cCreatureBase_CreateAndStartPool2Effect_00c1d460",
      "va": "0x00c1d460"
    },
    {
      "match_basis": [
        "shared_types:UNCONDITIONAL_CALL"
      ],
      "package": "PKG-13-C3-CREATURE-PROGRESSION-WAVE2",
      "score": 3,
      "symbol": "Simulator_cCreatureGameData_Get_00d2e340",
      "va": "0x00d2e340"
    },
    {
      "match_basis": [
        "shared_types:UNCONDITIONAL_CALL"
      ],
      "package": "PKG-13-C3-CREATURE-PROGRESSION-WAVE2",
      "score": 3,
      "symbol": "Simulator_cCreatureGameData_AddEvolutionPoints_raw_00d2e8a0",
      "va": "0x00d2e8a0"
    }
  ],
  "audit_evidence_boundary": null,
  "audit_findings": [],
  "audit_status": null,
  "blocked": false,
  "blockers": [
    "Runtime global ownership and original-process caller behavior remain gated."
  ],
  "body_status": null,
  "class_type": null,
  "cluster": null,
  "confidence": null,
  "dependencies": {
    "callees": [],
    "callees_truncated": false,
    "callers": [
      {
        "name": null,
        "reconstructed": false,
        "va": "0x00d40230"
      },
      {
        "name": null,
        "reconstructed": false,
        "va": "0x00d43e30"
      }
    ],
    "callers_truncated": false,
    "data_reference_count": 0,
    "edges": [
      {
        "callsite": "0x00d4031b",
        "direction": "in",
        "other": "0x00d40230",
        "reference_type": "direct-call"
      },
      {
        "callsite": "0x00d44272",
        "direction": "in",
        "other": "0x00d43e30",
        "reference_type": "direct-call"
      },
      {
        "callsite": "0x00d445fa",
        "direction": "in",
        "other": "0x00d43e30",
        "reference_type": "direct-call"
      }
    ],
    "edges_truncated": false,
    "external_callees": [],
    "fan_in": 2,
    "fan_out": 0,
    "manifest_callees": [],
    "manifest_callers": [],
    "nearby_reconstructed": [],
    "scc": {
      "id": "scc-0500",
      "size": 1
    },
    "vtable_reference_count": 0
  },
  "evidence_level": null,
  "globals": [
    "global:0x0169e398",
    "global:DAT_0169e398",
    "global:float"
  ],
  "integration_status": null,
  "name": null,
  "normalized_symbol": null,
  "observed_mechanics": [],
  "ownership": {
    "claimability": "runtime_gated_requires_explicit_gate",
    "handoff_packages": [],
    "manifest": {
      "record": null,
      "worker_ownership": null
    },
    "package": null,
    "queue_state": null
  },
  "package": null,
  "reconstructed": false,
  "review_status": null,
  "runtime": {
    "blocking_reason": null,
    "gates": [
      "Actual runtime evolution-point values and caller save-restoration context remain unobserved.",
      "The owner and initialization of DAT_0169e398 remain outside this target."
    ],
    "validated": 0
  },
  "runtime_gated": true,
  "runtime_validated": 0,
  "semantic": null,
  "semantic_status": null,
  "services": [],
  "source": {
    "decomp": null,
    "file": null,
    "files": [
      "reconstruction/staging/pkg13-c1-creature-progression/creature_progression.cpp",
      "reconstruction/staging/pkg13-c1-creature-progression/creature_progression.hpp",
      "reconstruction/staging/pkg13-c1-creature-progression/creature_progression_model_test.cpp"
    ],
    "handoffs": [],
    "metadata": [
      "reconstruction/metadata/pkg13-c1-creature-progression/00d2e480.json"
    ],
    "provenance": []
  },
  "status": "unresolved",
  "subsystem": null,
  "triage": null,
  "types": [
    "UNCONDITIONAL_CALL",
    "float"
  ],
  "unresolved_questions": [
    "No original-process save restoration or caller context has been observed.",
    "Whether the SDK method name corresponds to a broader object API is not inferred from this receiverless body."
  ],
  "va": "0x00d2e480",
  "vtables": []
}
```

## ghidra_function

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089`

```json
{
  "binary_available": true,
  "binary_sha256": "25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e",
  "body_end": "00d2e48e",
  "body_span_bytes": 15,
  "body_start": "00d2e480",
  "callees": [],
  "callers": [
    "FUN_00d43e30",
    "FUN_00d40230"
  ],
  "classification": "stub",
  "dispatch": null,
  "entry_point": "00d2e480",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "Simulator::cCreatureGameData::SetEvolutionPoints",
  "namespace": "Simulator",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 1,
  "parameters": [
    {
      "name": "points",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "float"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "void",
  "return_type_resolved": true,
  "rva": "0x92e480",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "void Simulator::cCreatureGameData::SetEvolutionPoints(float points)",
  "size_bytes": 15,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00d2e480",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 3,
  "xrefs": [
    {
      "from": "00d4031b"
    },
    {
      "from": "00d44272"
    },
    {
      "from": "00d445fa"
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
  "global:0x0169e398",
  "global:DAT_0169e398",
  "global:float"
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg13-c1-creature-progression/creature_progression.cpp",
    "reconstruction/staging/pkg13-c1-creature-progression/creature_progression.hpp",
    "reconstruction/staging/pkg13-c1-creature-progression/creature_progression_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg13-c1-creature-progression/00d2e480.json"
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
    "Actual runtime evolution-point values and caller save-restoration context remain unobserved.",
    "The owner and initialization of DAT_0169e398 remain outside this target."
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
  "status": "unresolved"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "UNCONDITIONAL_CALL",
  "float"
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
      "0x00d2e480",
      "0x00d2e480",
      "0x00d01410",
      "0x00d01410",
      "0x00d01ab0",
      "0x00d01ab0",
      "0x00d01e30",
      "0x00d01e30",
      "0x00d01f50",
      "0x00d01f50",
      "0x00d01ff0",
      "0x00d01ff0",
      "0x00d038e0",
      "0x00d038e0",
      "0x00d065a0",
      "0x00d065a0"
    ],
    "conflict_id": "U-003-civilization-progression",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The technology-level surface is recorded, but the binary writer/callback chain from one level to the next is not recovered.",
    "resolution_status": "The technology-level surface is recorded, but the binary writer/callback chain from one level to the next is not recovered.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00be34a0",
      "0x00d2e480",
      "0x00d2e480",
      "0x00aeb7b0",
      "0x00aeb160",
      "0x00aeb160",
      "0x00aeb7b0",
      "0x00aeb7b0",
      "0x00aebe90",
      "0x00aebe90",
      "0x00be34a0",
      "0x00d01410",
      "0x00d01410",
      "0x00d01ab0",
      "0x00d01ab0",
      "0x00d01e30"
    ],
    "conflict_id": "U-004-city-buildings",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
    "resolution_status": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00d2e380",
      "0x00d2e480",
      "0x00d2e8a0",
      "0x00d39360",
      "0x045ab96e",
      "0x00d2e480",
      "0x00aebe90",
      "0x045ab96e",
      "0x0067dcd0",
      "0x0067dcd0",
      "0x007d8420",
      "0x007d8420",
      "0x007d8cf0",
      "0x007d8cf0",
      "0x007d8d40",
      "0x007d8d40"
    ],
    "conflict_id": "U-005-evolution-level-promotion",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "0x45ab96e is a concrete action/message value with a guarded dispatch, but its consumer and brain-level/ability promotion are not identified.",
    "resolution_status": "0x45ab96e is a concrete action/message value with a guarded dispatch, but its consumer and brain-level/ability promotion are not identified.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00fe52c0",
      "0x00fe52c0",
      "0x00d2e350",
      "0x00d2e350",
      "0x00d2e380",
      "0x00d2e380",
      "0x00d2e480",
      "0x00d2e480",
      "0x00d2e8a0",
      "0x00d2e8a0",
      "0x00d3fcf0",
      "0x00d3fcf0",
      "0x00fe52c0",
      "0x00fe52c0",
      "0x00fe52c0",
      "0x00fe52c0"
    ],
    "conflict_id": "badge_state_domain",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
    "resolution_status": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00001278",
      "0x0000127c",
      "0x000010fc",
      "0x0000110c",
      "0x00001278",
      "0x0000127c",
      "0x00d2e350",
      "0x00d2e350",
      "0x00d2e380",
      "0x00d2e380",
      "0x00d2e480",
      "0x00d2e480",
      "0x00d2e8a0",
      "0x00d2e8a0",
      "0x00d3fcf0",
      "0x00d3fcf0"
    ],
    "conflict_id": "consequence_trait_rules",
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
      "0x00d2e380",
      "0x00d2e8a0",
      "0x00d2e8a0",
      "0x00d2e350",
      "0x00d2e35
[TRUNCATED]
```
