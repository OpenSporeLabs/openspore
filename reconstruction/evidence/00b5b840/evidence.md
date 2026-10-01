# Evidence 0x00b5b840

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `305925ff46801ba8a214271896054f4f7afb9e2b805cbcb0bac6b4b28769cde4`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "ordinary_stack_arguments": [
    "uint32 requested_value"
  ],
  "receiver": "strategy state in ECX",
  "ret_form": "RET 0x4",
  "return": "EAX/AL boolean; 1 only when both axis reads equal requested and pending is 0xffffffff"
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
    "flow_not_modelled: the linear ESP walk ends at -8, so the listing is not one path"
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
  "content_sha256": "055e942e63694017280f1642ab6dce6c779c750605c0d926fe2ceb97b08d59b8",
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
        "obs-0017",
        "obs-0020"
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
        "obs-0011"
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
        "obs-0013"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          0,
          20
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0013",
        "obs-0017",
        "obs-0020"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0017",
        "obs-0020"
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
        "obs-0017",
        "obs-0020"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0017",
        "obs-0020"
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
      "at": "0x00b5b840",
      "count": 5,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00b5b841",
      "count": 1,
      "first_use": 1,
      "first_write_index": 11,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00b5b841",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00b5b843",
      "definite": true,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESI]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00b5b845",
      "count": 3,
      "first_use": 3,
      "first_write_index": 2,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV EDX,dword ptr [EAX + 0x1c]",
      "reg": "EAX"
    },
    {
      "at": "0x00b5b845",
      "definite": true,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [EAX + 0x1c]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00b5b848",
      "count": 1,
      "first_use": 4,
      "first_write_index": 6,
      "id": "obs-0007",
      "index": 4,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00b5b849",
      "count": 2,
      "first_use": 5,
      "first_write_index": 3,
      "id": "obs-0008",
      "index": 5,
      "kind": "REG_READ",
      "raw": "CALL EDX",
      "reg": "EDX"
    },
    {
      "at": "0x00b5b849",
      "base": "EDX",
      "disp": null,
      "id": "obs-0009",
      "index": 5,
      "kind": "CALL_INDIRECT",
      "
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
    "va": "0x00b1fbb0"
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
      "0x007d85b0",
      "0x007d8c80",
      "0x01412598",
      "0x01412598",
      "0x007d8c80",
      "0x007d8c80",
      "0x007d85b0",
      "0x0212d3e7",
      "0x022d1adc",
      "0x007d85b0",
      "0x00b1db60",
      "0x00b1db60",
      "0x00b1dbd0",
      "0x00b1dbd0",
      "0x00b5b840",
      "0x00b5b840"
    ],
    "conflict_id": "U-MODE-MESSAGE-PAYLOAD",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The two mode IDs and send sites are concrete. The formal parameter roles and remaining StandardMessage slots are not recovered.",
    "resolution_status": "The two mode IDs and send sites are concrete. The formal parameter roles and remaining StandardMessage slots are not recovered.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00e20860",
      "0x00e20860",
      "0x00de4c20",
      "0x00df5ac0",
      "0x00b1d870",
      "0x00b1d870",
      "0x00b1db60",
      "0x00b1db60",
      "0x00b1dbd0",
      "0x00b1dbd0",
      "0x00b267f0",
      "0x00b267f0",
      "0x00b5b840",
      "0x00b5b840",
      "0x00b5b880",
      "0x00b5b880"
    ],
    "conflict_id": "app_bootstrap_meanings",
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
      "0x00b5b8a0",
      "0x00b5b8c0",
      "0x00b5b8e0",
      "0x00b5b960",
      "0x00b5b960",
      "0x00b1d870",
      "0x00b1d870",
      "0x00b1db60",
      "0x00b1db60",
      "0x00b1dbd0",
      "0x00b1dbd0",
      "0x00b267f0",
      "0x00b267f0",
      "0x00b5b840",
      "0x00b5b840",
      "0x00b5b880"
    ],
    "conflict_id": "game_mode_identifier_domain",
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
  "count": 25,
  "instructions": [
    {
      "address": "00b5b840",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00b5b841",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00b5b843",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "00b5b845",
      "instruction": "MOV EDX,dword ptr [EAX + 0x1c]"
    },
    {
      "address": "00b5b848",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00b5b849",
      "instruction": "CALL EDX"
    },
    {
      "address": "00b5b84b",
      "instruction": "MOV EDI,dword ptr [ESP + 0xc]"
    },
    {
      "address": "00b5b84f",
      "instruction": "CMP EDI,EAX"
    },
    {
      "address": "00b5b851",
      "instruction": "JNZ 0x00b5b870"
    },
    {
      "address": "00b5b853",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "00b5b855",
      "instruction": "MOV EDX,dword ptr [EAX + 0x20]"
    },
    {
      "address": "00b5b858",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00b5b85a",
      "instruction": "CALL EDX"
    },
    {
      "address": "00b5b85c",
      "instruction": "CMP EDI,EAX"
    },
    {
      "address": "00b5b85e",
      "instruction": "JNZ 0x00b5b870"
    },
    {
      "address": "00b5b860",
      "instruction": "CMP dword ptr [ESI + 0x14],-0x1"
    },
    {
      "address": "00b5b864",
      "instruction": "JNZ 0x00b5b870"
    },
    {
      "address": "00b5b866",
      "instruction": "POP EDI"
    },
    {
      "address": "00b5b867",
      "instruction": "MOV EAX,0x1"
    },
    {
      "address": "00b5b86c",
      "instruction": "POP ESI"
    },
    {
      "address": "00b5b86d",
      "instruction": "RET 0x4"
    },
    {
      "address": "00b5b870",
      "instruction": "POP EDI"
    },
    {
      "address": "00b5b871",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "00b5b873",
      "instruction": "POP ESI"
    },
    {
      "address": "00b5b874",
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
  "abi": {
    "architecture": "x86-32",
    "calling_convention": "__thiscall",
    "ordinary_stack_arguments": [
      "uint32 requested_value"
    ],
    "receiver": "strategy state in ECX",
    "ret_form": "RET 0x4",
    "return": "EAX/AL boolean; 1 only when both axis reads equal requested and pending is 0xffffffff"
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
      "symbol": "app_mode_activate_by_name_007d8360",
      "va": "0x007d8360"
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
    "callers": [
      {
        "name": null,
        "reconstructed": false,
        "va": "0x00b1fbb0"
      }
    ],
    "callers_truncated": false,
    "data_reference_count": 0,
    "edges": [
      {
        "callsite": "0x00b1fbb9",
        "direction": "in",
        "other": "0x00b1fbb0",
        "reference_type": "direct-call"
      }
    ],
    "edges_truncated": false,
    "external_callees": [],
    "fan_in": 1,
    "fan_out": 0,
    "manifest_callees": [],
    "manifest_callers": [],
    "nearby_reconstructed": [],
    "scc": {
      "id": "scc-0391",
      "size": 1
    },
    "vtable_reference_count": 0
  },
  "evidence_level": "SUPPORTED",
  "globals": [],
  "integration_status": "integrated",
  "name": "strategy_request_ready_00b5b840",
  "normalized_symbol": "strategy_request_ready_00b5b840",
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
      "Observe the concrete strategy owner, axis virtual implementations, and pending sentinel state; runtime validation is not run."
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
      "reconstruction/metadata/pkg-game-mode-wave7/00b5b840.json"
    ],
    "provenance": [
      "ghidra:decompile_function",
      "ghidra:disassemble_function",
      "ghidra:get_function_callees",
      "ghidra:get_function_callers",
      "reconstruction/metadata/pkg-game-mode-wave7/00b5b840.json"
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
  "va": "0x00b5b840",
  "vtables": [
    "vtable:0x00b5b840"
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
  "body_end": "00b5b876",
  "body_span_bytes": 55,
  "body_start": "00b5b840",
  "callees": [],
  "callers": [
    "FUN_00b1fbb0"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "00b5b840",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00b5b840",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x75b840",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00b5b840(void)",
  "size_bytes": 55,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00b5b840",
  "vtables": {
    "referenced_by_vtables": [
      "0x0145f9c8",
      "0x01479ec0",
      "0x0147abac",
      "0x0147ce24",
      "0x0145cbc8",
      "0x0146098c",
      "0x01461580",
      "0x0146837c",
      "0x01481e2c",
      "0x01493f60",
      "0x014650e8",
      "0x01478c10",
      "0x014818d8",
      "0x01499b0c",
      "0x0149ade0",
      "0x01459d30",
      "0x01459fc8",
      "0x0145bde0",
      "0x0145bf14",
      "0x0145d7f0"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 35,
  "xrefs": [
    {
      "from": "01459d54"
    },
    {
      "from": "01459fec"
    },
    {
      "from": "0145be04"
    },
    {
      "from": "0145bf44"
    },
    {
      "from": "0145cbec"
    },
    {
      "from": "0145d814"
    },
    {
      "from": "0145f9ec"
    },
    {
      "from": "0145fdcc"
    },
    {
      "from": "014603b4"
    },
    {
      "from": "014609b4"
    },
    {
      "from": "01461204"
    },
    {
      "from": "014615a4"
    },
    {
      "from": "01462944"
    },
    {
      "from": "01461874"
    },
    {
      "from": "01464f3c"
    },
    {
      "from": "0146510c"
    },
    {
      "from": "01465c64"
    },
    {
      "from": "0146607c"
    },
    {
      "from": "014668bc"
    },
    {
      "from": "014683a4"
    },
    {
      "from": "01477614"
    },
    {
      "from": "01478c34"
    },
    {
      "from": "01479ee4"
    },
    {
      "from": "0147ac34"
    },
    {
      "from": "0147ce84"
    },
    {
      "from": "0148000c"
    },
    {
      "from": "01480134"
    },
    {
      "from": "014818fc"
    },
    {
      "from": "01481e6c"
    },
    {
      "from": "0148d19c"
    },
    {
      "from": "01493f84"
    },
    {
      "from": "01499b54"
    },
    {
      "from": "0149ae04"
    },
    {
      "from": "00b1fbb9"
    },
    {
      "from": "00ba2780"
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
    "reconstruction/metadata/pkg-game-mode-wave7/00b5b840.json"
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
    "Observe the concrete strategy owner, axis virtual implementations, and pending sentinel state; runtime validation is not run."
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
  "vtable:0x00b5b840"
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
      "0x007d85b0",
      "0x00b1db60",
      "0x00b1db60",
      "0x00b1dbd0",
      "0x00b1dbd0",
      "0x00b5b840",
      "0x00b5b840"
    ],
    "conflict_id": "U-MODE-MESSAGE-PAYLOAD",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The two mode IDs and send sites are concrete. The formal parameter roles and remaining StandardMessage slots are not recovered.",
    "resolution_status": "The two mode IDs and send sites are concrete. The formal parameter roles and remaining StandardMessage slots are not recovered.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00e20860",
      "0x00e20860",
      "0x00de4c20",
      "0x00df5ac0",
      "0x00b1d870",
      "0x00b1d870",
      "0x00b1db60",
      "0x00b1db60",
      "0x00b1dbd0",
      "0x00b1dbd0",
      "0x00b267f0",
      "0x00b267f0",
      "0x00b5b840",
      "0x00b5b840",
      "0x00b5b880",
      "0x00b5b880"
    ],
    "conflict_id": "app_bootstrap_meanings",
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
      "0x00b5b8a0",
      "0x00b5b8c0",
      "0x00b5b8e0",
      "0x00b5b960",
      "0x00b5b960",
      "0x00b1d870",
      "0x00b1d870",
      "0x00b1db60",
      "0x00b1db60",
      "0x00b1dbd0",
      "0x00b1dbd0",
      "0x00b267f0",
      "0x00b267f0",
      "0x00b5b840",
      "0x00b5b840",
      "0x00b5b880"
    ],
    "conflict_id": "game_mode_identifier_domain",
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
  }
]
```
