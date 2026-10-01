# Evidence 0x007d8360

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `4ac238a2e428fca89b0b1897251343d0162edaeb6222eefdb493297a21400360`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "ordinary_stack_arguments": [
    "const char* requested_name"
  ],
  "receiver": "AppModeRegistry* in ECX",
  "ret_form": "RET 0x4",
  "return": "AL boolean"
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
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -12, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register"
  ],
  "cleanup": {
    "bytes": 4,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x4",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "17d302bdce173f04131b908c58af086584a45f97c7cae0f63d4d9bd857a0114f",
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
    "ghidra_parameter_count": 0,
    "persisted": "agrees",
    "persisted_calling_convention": "__thiscall"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 2,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0024",
        "obs-0030"
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
        "obs-0016"
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
        "obs-0002",
        "obs-0003",
        "obs-0004",
        "obs-0014"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          0,
          20,
          24
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0004",
        "obs-0014",
        "obs-0024",
        "obs-0030"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0024",
        "obs-0030"
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
        "obs-0024",
        "obs-0030"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0024",
        "obs-0030"
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
      "at": "0x007d8360",
      "count": 6,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x007d8361",
      "count": 2,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EBX,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x007d8361",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EBX,ECX",
      "reg": "EBX",
      "write_kind": "reg"
    },
    {
      "at": "0x007d8363",
      "definite": true,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [EBX + 0x18]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x007d8369",
      "definite": true,
      "id": "obs-0005",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,0x2aaaaaab",
      "reg": "EAX",
      "write_kind": "imm"
    },
    {
      "at": "0x007d8370",
      "count": 5,
      "first_use": 6,
      "first_write_index": 16,
      "id": "obs-0006",
      "index": 6,
      "kind": "REG_READ",
      "raw": "PUSH EBP",
      "reg": "EBP"
    },
    {
      "and_esp": null,
      "at": "0x007d8370",
      "ebp_is_general_register": true,
      "fp": false,
      "id": "obs-0007",
      "index": 6,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": nul
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
[
  {
    "anchors": [
      "0x007d85b0",
      "0x007d8c80",
      "0x01412598",
      "0x01412598",
      "0x007d8c80",
      "0x007d8c80",
      "0x007d85b0",
      "0x0212d3e7",
      "0x022d1adc",
      "0x007d8060",
      "0x007d8060",
      "0x007d8360",
      "0x007d8360",
      "0x007d85b0",
      "0x007d85b0",
      "0x007d8c30"
    ],
    "conflict_id": "Q-APP-ID-CATALOG",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "Registration operations, mode IDs, and several named event surfaces are concrete. The complete ID catalog, payload schema, and producer/consumer map are not recovered.",
    "resolution_status": "Registration operations, mode IDs, and several named event surfaces are concrete. The complete ID catalog, payload schema, and producer/consumer map are not recovered.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00b3d350",
      "0x00e818f0",
      "0x00b3d350",
      "0x00e818f0",
      "0x00b3d350",
      "0x007d8060",
      "0x007d8060",
      "0x007d8360",
      "0x007d8360",
      "0x007d85b0",
      "0x007d85b0",
      "0x007d8c30",
      "0x007d8c30",
      "0x007d8c80",
      "0x007d8c80",
      "0x007d8d40"
    ],
    "conflict_id": "Q-INPUT-ROUTING",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "resolution_status": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00960250",
      "0x00960250",
      "0x005bf9d0",
      "0x005bf9d0",
      "0x005bfd40",
      "0x005bfd40",
      "0x005c0100",
      "0x005c0100",
      "0x005c0380",
      "0x005c0380",
      "0x007d8060",
      "0x007d8060",
      "0x007d8230",
      "0x007d8230",
      "0x007d8360",
      "0x007d8360"
    ],
    "conflict_id": "U-DIALOG-BEHAVIOR",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "resolution_status": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00b3d350",
      "0x00e818f0",
      "0x00b3d350",
      "0x00e818f0",
      "0x00b3d350",
      "0x007d8060",
      "0x007d8060",
      "0x007d8230",
      "0x007d8230",
      "0x007d8360",
      "0x007d8360",
      "0x007d8470",
      "0x007d8470",
      "0x007d85b0",
      "0x007d85b0",
      "0x007d8c30"
    ],
    "conflict_id": "U-GAME-INPUT-ROUTER",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "resolution_status": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x007d85b0",
      "0x007d8c80",
      "0x01412598",
      "0x01412598",
      "0x007d8c80",
      "0x007d8c80",
      "0x007d85b0",
      "0x0212d3e7",
      "0x022d1adc",
      "0x00b63510",
      "0x00b63510",
      "0x007d8060",
      "0x007d8060",
      "0x007d8230",
      "0x007d8230",
      "0x007d8360"
    ],
    "conflict_id": "U-MODE-TRANSITION-RUNTIME",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "Static call order is fixed: old OnExit, active-index write, mode-exit send, new OnEnter, mode-enter send. Runtime reachability and listener completion order are not verified.",
    "resolution_status": "Static call order is fixed: old OnExit, active-index write, mode-exit send, new OnEnter, mode-enter send. Runtime reachability and listener completion order are not verified.",
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
  "count": 51,
  "instructions": [
    {
      "address": "007d8360",
      "instruction": "PUSH EBX"
    },
    {
      "address": "007d8361",
      "instruction": "MOV EBX,ECX"
    },
    {
      "address": "007d8363",
      "instruction": "MOV ECX,dword ptr [EBX + 0x18]"
    },
    {
      "address": "007d8366",
      "instruction": "SUB ECX,dword ptr [EBX + 0x14]"
    },
    {
      "address": "007d8369",
      "instruction": "MOV EAX,0x2aaaaaab"
    },
    {
      "address": "007d836e",
      "instruction": "IMUL ECX"
    },
    {
      "address": "007d8370",
      "instruction": "PUSH EBP"
    },
    {
      "address": "007d8371",
      "instruction": "PUSH ESI"
    },
    {
      "address": "007d8372",
      "instruction": "SAR EDX,0x2"
    },
    {
      "address": "007d8375",
      "instruction": "MOV ESI,EDX"
    },
    {
      "address": "007d8377",
      "instruction": "SHR ESI,0x1f"
    },
    {
      "address": "007d837a",
      "instruction": "PUSH EDI"
    },
    {
      "address": "007d837b",
      "instruction": "ADD ESI,EDX"
    },
    {
      "address": "007d837d",
      "instruction": "XOR EDI,EDI"
    },
    {
      "address": "007d837f",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "007d8381",
      "instruction": "JLE 0x007d83b3"
    },
    {
      "address": "007d8383",
      "instruction": "XOR EBP,EBP"
    },
    {
      "address": "007d8385",
      "instruction": "MOV EAX,dword ptr [EBX + 0x14]"
    },
    {
      "address": "007d8388",
      "instruction": "MOV ECX,dword ptr [EAX + EBP*0x1 + 0x8]"
    },
    {
      "address": "007d838c",
      "instruction": "CMP ECX,dword ptr [EAX + EBP*0x1 + 0xc]"
    },
    {
      "address": "007d8390",
      "instruction": "LEA EAX,[EAX + EBP*0x1 + 0x8]"
    },
    {
      "address": "007d8394",
      "instruction": "JZ 0x007d83ab"
    },
    {
      "address": "007d8396",
      "instruction": "MOV EDX,dword ptr [ESP + 0x14]"
    },
    {
      "address": "007d839a",
      "instruction": "MOV EAX,ECX"
    },
    {
      "address": "007d839c",
      "instruction": "PUSH EDX"
    },
    {
      "address": "007d839d",
      "instruction": "PUSH EAX"
    },
    {
      "address": "007d839e",
      "instruction": "CALL dword ptr [0x013cc4dc]"
    },
    {
      "address": "007d83a4",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "007d83a7",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "007d83a9",
      "instruction": "JZ 0x007d83bc"
    },
    {
      "address": "007d83ab",
      "instruction": "INC EDI"
    },
    {
      "address": "007d83ac",
      "instruction": "ADD EBP,0x18"
    },
    {
      "address": "007d83af",
      "instruction": "CMP EDI,ESI"
    },
    {
      "address": "007d83b1",
      "instruction": "JL 0x007d8385"
    },
    {
      "address": "007d83b3",
      "instruction": "POP EDI"
    },
    {
      "address": "007d83b4",
      "instruction": "POP ESI"
    },
    {
      "address": "007d83b5",
      "instruction": "POP EBP"
    },
    {
      "address": "007d83b6",
      "instruction": "XOR AL,AL"
    },
    {
      "address": "007d83b8",
      "instruction": "POP EBX"
    },
    {
      "address": "007d83b9",
      "instruction": "RET 0x4"
    },
    {
      "address": "007d83bc",
      "instruction": "MOV EAX,dword ptr [EBX]"
    },
    {
      "address": "007d83be",
      "instruction": "MOV EDX,dword ptr [EAX + 0x40]"
    },
    {
      "address": "007d83c1",
      "instruction": "PUSH EDI"
    },
    {
      "address": "007d83c2",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "007d83c4",
      "instruction": "CALL EDX"
    },
    {
      "address": "007d83c6",
      "instruction": "POP EDI"
    },
    {
      "address": "007d83c7",
      "instruction": "POP ESI"
    },
    {
      "address": "007d83c8",
      "instruction": "POP EBP"
    },
    {
      "address": "007d83c9",
      "instruction": "MOV AL,0x1"
    },
    {
      "address": "007d83cb",
      "instruction": "POP EBX"
    },
    {
      "address": "007d83cc",
      "instruction": "RET 0x4"
    }
  ]
}
```

## external_callees

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "EXT:MSVCR90.DLL::_stricmp"
]
```

## function_identity

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "abi": {
    "architecture": "x86-32",
    "calling_convention": "__thiscall",
    "ordinary_stack_arguments": [
      "const char* requested_name"
    ],
    "receiver": "AppModeRegistry* in ECX",
    "ret_form": "RET 0x4",
    "return": "AL boolean"
  },
  "analogues": [
    {
      "match_basis": [
        "same_package",
        "same_subsystem",
        "same_class",
        "shared_types:OpaqueGameModeState",
        "same_calling_convention"
      ],
      "package": "PKG-GAME-MODE-WAVE7",
      "score": 24,
      "symbol": "app_mode_activate_007d85b0",
      "va": "0x007d85b0"
    },
    {
      "match_basis": [
        "same_package",
        "same_subsystem",
        "same_class",
        "shared_types:OpaqueGameModeState",
        "same_calling_convention"
      ],
      "package": "PKG-GAME-MODE-WAVE7",
      "score": 24,
      "symbol": "app_mode_activate_index_007d8c80",
      "va": "0x007d8c80"
    },
    {
      "match_basis": [
        "same_package",
        "same_subsystem",
        "same_class",
        "shared_types:OpaqueGameModeState",
        "same_calling_convention"
      ],
      "package": "PKG-GAME-MODE-WAVE7",
      "score": 24,
      "symbol": "strategy_request_ready_00b5b840",
      "va": "0x00b5b840"
    },
    {
      "match_basis": [
        "same_package",
        "same_subsystem",
        "same_class",
        "shared_types:OpaqueGameModeState",
        "same_calling_convention"
      ],
      "package": "PKG-GAME-MODE-WAVE7",
      "score": 24,
      "symbol": "strategy_queue_primary_00b5b880",
      "va": "0x00b5b880"
    },
    {
      "match_basis": [
        "same_package",
        "same_subsystem",
        "same_class",
        "shared_types:OpaqueGameModeState",
        "same_calling_convention"
      ],
      "package": "PKG-GAME-MODE-WAVE7",
      "score": 24,
      "symbol": "strategy_queue_secondary_00b5b8a0",
      "va": "0x00b5b8a0"
    },
    {
      "match_basis": [
        "same_package",
        "same_subsystem",
        "same_class",
        "shared_types:OpaqueGameModeState",
        "same_calling_convention"
      ],
      "package": "PKG-GAME-MODE-WAVE7",
      "score": 24,
      "symbol": "strategy_commit_primary_00b5b8c0",
      "va": "0x00b5b8c0"
    },
    {
      "match_basis": [
        "same_package",
        "same_subsystem",
        "same_class",
        "shared_types:OpaqueGameModeState",
        "same_calling_convention"
      ],
      "package": "PKG-GAME-MODE-WAVE7",
      "score": 24,
      "symbol": "strategy_commit_secondary_00b5b8e0",
      "va": "0x00b5b8e0"
    },
    {
      "match_basis": [
        "same_package",
        "same_subsystem",
        "same_class",
        "shared_types:OpaqueGameModeState",
        "same_calling_convention"
      ],
      "package": "PKG-GAME-MODE-WAVE7",
      "score": 24,
      "symbol": "app_simulator_mode_bridge_00b63510",
      "va": "0x00b63510"
    }
  ],
  "audit_evidence_boundary": "Static mechanics and x86-32 ABI reviewed from live Ghidra; runtime values, concrete owners, and unresolved ports remain gated.",
  "audit_findings": [],
  "audit_status": "clean_after_reviewed_repairs",
  "blocked": false,
  "blockers": [],
  "body_status": "integrated",
  "class_type": "OpaqueGameModeState",
  "cluster": null,
  "confidence": 0.7,
  "dependencies": {
    "callees": [],
    "callees_truncated": false,
    "callers": [],
    "callers_truncated": false,
    "data_reference_count": 0,
    "edges": [
      {
        "callsite": "0x007d839e",
        "direction": "out",
        "other": "EXT:MSVCR90.DLL::_stricmp",
        "reference_type": "external"
      }
    ],
    "edges_truncated": false,
    "external_callees": [
      "EXT:MSVCR90.DLL::_stricmp"
    ],
    "fan_in": 0,
    "fan_out": 0,
    "manifest_callees": [],
    "manifest_callers": [],
    "nearby_reconstructed": [],
    "scc": {
      "id": "scc-0243",
      "size": 1
    },
    "vtable_reference_count": 0
  },
  "evidence_level": "SUPPORTED",
  "globals": [],
  "integration_status": "integrated",
  "name": "app_mode_activate_by_name_007d8360",
  "normalized_symbol": "app_mode_activate_by_name_007d8360",
  "observed_mechanics": [
    "{}"
  ],
  "ownership": {
    "claimability": "do_not_claim",
    "handoff_packages": [
      "PKG-GAME-MODE-WAVE7"
    ],
    "manifest": {
      "record": null,
      "worker_ownership": null
    },
    "package": "PKG-GAME-MODE-WAVE7",
    "queue_state": null
  },
  "package": "PKG-GAME-MODE-WAVE7",
  "reconstructed": true,
  "review_status": "approved_after_parallel_review",
  "runtime": {
    "blocking_reason": null,
    "gates": [
      "Observe entry name storage, registry vtable target, and runtime case-insensitive matching; runtime validation is not run."
    ],
    "validated": 0
  },
  "runtime_gated": true,
  "runtime_validated": 0,
  "semantic": null,
  "semantic_status": "static_reconstruction_runtime_gated",
  "services": [],
  "source": {
    "decomp": null,
    "file": "src/reconstruction/pkg_game_mode_wave7/game_mode_wave7.cpp",
    "files": [
      "src/reconstruction/pkg_game_mode_wave7/game_mode_wave7.cpp"
    ],
    "handoffs": [
      "reconstruction/integrated/batch-2026-09-25-wave7/handoff.json"
    ],
    "metadata": [
      "reconstruction/metadata/pkg-game-mode-wave7/007d8360.json"
    ],
    "provenance": [
      "ghidra:decompile_function",
      "ghidra:disassemble_function",
      "ghidra:get_function_callees",
      "ghidra:get_function_callers",
      "reconstruction/metadata/pkg-game-mode-wave7/007d8360.json"
    ]
  },
  "status": "reconstructed",
  "subsystem": "App.GameMode",
  "triage": null,
  "types": [
    "OpaqueGameModeState"
  ],
  "unresolved_questions": [
    "concrete runtime owners and values remain unresolved"
  ],
  "va": "0x007d8360",
  "vtables": [
    "vtable:0x007d8360"
  ]
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
  "body_end": "007d83ce",
  "body_span_bytes": 111,
  "body_start": "007d8360",
  "callees": [
    "_stricmp"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "007d8360",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_007d8360",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x3d8360",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_007d8360(void)",
  "size_bytes": 111,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x007d8360",
  "vtables": {
    "referenced_by_vtables": [
      "0x01412598"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "014125e4"
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
  "file": "src/reconstruction/pkg_game_mode_wave7/game_mode_wave7.cpp",
  "files": [
    "src/reconstruction/pkg_game_mode_wave7/game_mode_wave7.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave7/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-game-mode-wave7/007d8360.json"
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
    "Observe entry name storage, registry vtable target, and runtime case-insensitive matching; runtime validation is not run."
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
  "OpaqueGameModeState"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x007d8360"
]
```

## Conflicts

```json
[
  {
    "anchors": [
      "0x007d85b0",
      "0x007d8c80",
      "0x01412598",
      "0x01412598",
      "0x007d8c80",
      "0x007d8c80",
      "0x007d85b0",
      "0x0212d3e7",
      "0x022d1adc",
      "0x007d8060",
      "0x007d8060",
      "0x007d8360",
      "0x007d8360",
      "0x007d85b0",
      "0x007d85b0",
      "0x007d8c30"
    ],
    "conflict_id": "Q-APP-ID-CATALOG",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "Registration operations, mode IDs, and several named event surfaces are concrete. The complete ID catalog, payload schema, and producer/consumer map are not recovered.",
    "resolution_status": "Registration operations, mode IDs, and several named event surfaces are concrete. The complete ID catalog, payload schema, and producer/consumer map are not recovered.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00b3d350",
      "0x00e818f0",
      "0x00b3d350",
      "0x00e818f0",
      "0x00b3d350",
      "0x007d8060",
      "0x007d8060",
      "0x007d8360",
      "0x007d8360",
      "0x007d85b0",
      "0x007d85b0",
      "0x007d8c30",
      "0x007d8c30",
      "0x007d8c80",
      "0x007d8c80",
      "0x007d8d40"
    ],
    "conflict_id": "Q-INPUT-ROUTING",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "resolution_status": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00960250",
      "0x00960250",
      "0x005bf9d0",
      "0x005bf9d0",
      "0x005bfd40",
      "0x005bfd40",
      "0x005c0100",
      "0x005c0100",
      "0x005c0380",
      "0x005c0380",
      "0x007d8060",
      "0x007d8060",
      "0x007d8230",
      "0x007d8230",
      "0x007d8360",
      "0x007d8360"
    ],
    "conflict_id": "U-DIALOG-BEHAVIOR",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "resolution_status": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00b3d350",
      "0x00e818f0",
      "0x00b3d350",
      "0x00e818f0",
      "0x00b3d350",
      "0x007d8060",
      "0x007d8060",
      "0x007d8230",
      "0x007d8230",
      "0x007d8360",
      "0x007d8360",
      "0x007d8470",
      "0x007d8470",
      "0x007d85b0",
      "0x007d85b0",
      "0x007d8c30"
    ],
    "conflict_id": "U-GAME-INPUT-ROUTER",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "resolution_status": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x007d85b0",
      "0x007d8c80",
      "0x01412598",
      "0x01412598",
      "0x007d8c80",
      "0x007d8c80",
      "0x007d85b0",
      "0x0212d3e7",
      "0x022d1adc",
      "0x00b63510",
      "0x00b63510",
      "0x007d8060",
      "0x007d8060",
      "0x007d8230",
      "0x007d8230",
      "0x007d8360"
    ],
    "conflict_id": "U-MODE-TRANSITION-RUNTIME",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "Static call order is fixed: old OnExit, active-index write, mode-exit send, new OnEnter, mode-enter send. Runtime reachability and listener completion order are not verified.",
    "resolution_status": "Static call order is fixed: old OnExit, active-index write, mode-exit send, new OnEnter, mode-enter send. Runtime reachability and listener completion order are not verified.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  }
]
```
