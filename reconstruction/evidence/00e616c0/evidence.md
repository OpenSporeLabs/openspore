# Evidence 0x00e616c0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `9b7e24b7046f9d9cc79e816926d2954522e67bb2ee6308fff18b9513eba3de25`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "cdecl",
  "ordinary_stack_arguments": [
    "CellModeOwner* owner"
  ],
  "receiver": "none; owner is loaded from [ESP+4]",
  "ret_form": "plain RET; caller removes the four-byte owner argument",
  "return": "void"
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
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
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
  "conflicts": [],
  "content_sha256": "e25a9a991a85c833be5921553fa0a30544c029bf053fa4717a825831a7db8095",
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
    "persisted_calling_convention": "cdecl"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0012"
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
        "obs-0006"
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
        "obs-0005",
        "obs-0006",
        "obs-0007",
        "obs-0008",
        "obs-0009"
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
        "obs-0005",
        "obs-0006",
        "obs-0007",
        "obs-0008",
        "obs-0009"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_reassigned_before_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0012"
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
        "obs-0012"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0012"
      ],
      "claim": "the last value written to EAX classifies as aggregate_unknown",
      "confidence": "INFERRED",
      "id": "RT2",
      "value": {
        "register_class": "aggregate_unknown"
      }
    }
  ],
  "observations": [
    {
      "at": "0x00e616cf",
      "id": "obs-0001",
      "index": 6,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00f473a0",
      "target": "0x00f473a0"
    },
    {
      "at": "0x00e616d4",
      "definite": true,
      "id": "obs-0002",
      "index": 7,
      "kind": "REG_WRITE",
      "raw": "ADD ESP,0x18",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00e616db",
      "count": 6,
      "first_use": 10,
      "first_write_index": 14,
      "id": "obs-0003",
      "index": 10,
      "kind": "REG_READ",
      "raw": "MOV dword ptr [EAX + 0x4],0x13eb394",
      "reg": "EAX"
    },
    {
      "at": "0x00e616f1",
      "definite": true,
      "id": "obs-0004",
      "index": 14,
      "kind": "REG_WRITE",
      "raw": "XOR EAX,EAX",
      "reg": "EAX",
      "write_kind": "zero"
    },
    {
      "at": "0x00e616f3",
      "count": 1,
      "first_use": 15,
      "first_write_index": 7,
      "id": "obs-0005",
      "index": 15,
      "kind": "REG_READ",
      "raw": "MOV ECX,dword ptr [ESP + 0x4]",
      "reg": "ESP"
    },
    {
      "at": "0x00e616f3",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0006",
      "index": 15,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV ECX,dword ptr [ESP + 0x4]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00e616f3",
      "definite": true,
      "id": "obs-0007",
      "index": 15,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [ESP + 0x4]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00e616f7",
      "count": 1,
      "first_use": 16,
      "first_write_index": 15,
      "id": "obs-0008",
      "index": 16,
      "kind": "REG_READ",
      "raw": "MOV EDX,dword ptr [ECX]",
      "reg": "ECX"
    },
    {
      "at": "0x00e616f7",
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
      "0x00e61550",
      "0x00e616c0",
      "0x01485550",
      "0x01485550",
      "0x01485550"
    ],
    "conflict_id": "TB-INH-006",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": {
      "merge_decision": "structural_only",
      "preferred_claim": "Record interface implementation as structural interface evidence only.",
      "preserved_alternatives": true,
      "scope_note": "The current source is comparison-only and cannot backfill the original ABI.",
      "status": "preserved_alternatives",
      "taxonomy": "preserved_alternatives"
    },
    "resolution_status": "preserved_alternatives",
    "source": "knowledgegraph/research/conflicts/track-b-vtable-fields.json",
    "subject": "IGameMode implementation and cCellModeStrategy concrete table",
    "unresolved_reason": "The cited static evidence leaves the competing owner, slot, layout, or lifecycle interpretation unresolved; no positive original runtime or MSVC RTTI evidence is available."
  },
  {
    "anchors": [
      "0x01485550",
      "0x01485550",
      "0x01485550",
      "0x00e61550",
      "0x00e616c0",
      "0x01485550",
      "0x01485550",
      "0x00e61550",
      "0x01485550",
      "0x00e61550",
      "0x00e616c0",
      "0x0057ce80",
      "0x01485550",
      "0x01485550"
    ],
    "conflict_id": "TB-VT-002",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": {
      "merge_decision": "preferred_claim_with_limit",
      "preferred_claim": "App::cCellModeStrategy remains the preferred static identity for 0x01485550, with the cEditor projection explicitly retained.",
      "preserved_alternatives": true,
      "scope_note": "Preferred means stronger static evidence, not a resolved C++ owner or universal IGameMode ABI.",
      "status": "preferred_claim_with_limit",
      "taxonomy": "preferred_claim_with_limit"
    },
    "resolution_status": "preferred_claim_with_limit",
    "source": "knowledgegraph/research/conflicts/track-b-vtable-fields.json",
    "subject": "Vtable candidate 0x01485550 ownership and slot identity",
    "unresolved_reason": "The cited static evidence leaves the competing owner, slot, layout, or lifecycle interpretation unresolved; no positive original runtime or MSVC RTTI evidence is available."
  },
  {
    "anchors": [
      "0x00e80980",
      "0x00e818f0",
      "0x00e81cf0",
      "0x00e81f30",
      "0x00e552f0",
      "0x00e7fc00",
      "0x00e616c0",
      "0x00e80d8b",
      "0x01485550",
      "0x013f57f8",
      "0x01485550",
      "0x01485558",
      "0x01485550",
      "0x01485550",
      "0x01485558",
      "0x01485550"
    ],
    "conflict_id": "VT-002",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "RESOLVED_OBSERVED",
    "resolution_status": "RESOLVED_OBSERVED",
    "source": "knowledgegraph/research/conflicts/track-a-type-signature.json",
    "subject": "0x01485550/0x01485558 cCellModeStrategy vtable owner and base",
    "unresolved_reason": "The exact source-level name of the secondary subobject and the language-level interface declaration remain unproven, but the disputed table owner/base is resolved."
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
  "count": 23,
  "instructions": [
    {
      "address": "00e616c0",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00e616c2",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00e616c4",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00e616c6",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00e616c8",
      "instruction": "PUSH 0x13ebc58"
    },
    {
      "address": "00e616cd",
      "instruction": "PUSH 0xc"
    },
    {
      "address": "00e616cf",
      "instruction": "CALL 0x00f473a0"
    },
    {
      "address": "00e616d4",
      "instruction": "ADD ESP,0x18"
    },
    {
      "address": "00e616d7",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00e616d9",
      "instruction": "JZ 0x00e616f1"
    },
    {
      "address": "00e616db",
      "instruction": "MOV dword ptr [EAX + 0x4],0x13eb394"
    },
    {
      "address": "00e616e2",
      "instruction": "MOV dword ptr [EAX],0x1485558"
    },
    {
      "address": "00e616e8",
      "instruction": "MOV dword ptr [EAX + 0x4],0x1485550"
    },
    {
      "address": "00e616ef",
      "instruction": "JMP 0x00e616f3"
    },
    {
      "address": "00e616f1",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "00e616f3",
      "instruction": "MOV ECX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "00e616f7",
      "instruction": "MOV EDX,dword ptr [ECX]"
    },
    {
      "address": "00e616f9",
      "instruction": "PUSH 0x14856d8"
    },
    {
      "address": "00e616fe",
      "instruction": "PUSH 0x1654c00"
    },
    {
      "address": "00e61703",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00e61704",
      "instruction": "MOV EAX,dword ptr [EDX + 0x20]"
    },
    {
      "address": "00e61707",
      "instruction": "CALL EAX"
    },
    {
      "address": "00e61709",
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
  "abi": {
    "architecture": "x86-32",
    "calling_convention": "cdecl",
    "ordinary_stack_arguments": [
      "CellModeOwner* owner"
    ],
    "receiver": "none; owner is loaded from [ESP+4]",
    "ret_form": "plain RET; caller removes the four-byte owner argument",
    "return": "void"
  },
  "analogues": [
    {
      "match_basis": [
        "same_package",
        "same_subsystem",
        "same_class",
        "shared_types:OpaqueGameModeState"
      ],
      "package": "PKG-GAME-MODE-WAVE7",
      "score": 22,
      "symbol": "app_mode_activate_by_name_007d8360",
      "va": "0x007d8360"
    },
    {
      "match_basis": [
        "same_package",
        "same_subsystem",
        "same_class",
        "shared_types:OpaqueGameModeState"
      ],
      "package": "PKG-GAME-MODE-WAVE7",
      "score": 22,
      "symbol": "app_mode_activate_007d85b0",
      "va": "0x007d85b0"
    },
    {
      "match_basis": [
        "same_package",
        "same_subsystem",
        "same_class",
        "shared_types:OpaqueGameModeState"
      ],
      "package": "PKG-GAME-MODE-WAVE7",
      "score": 22,
      "symbol": "app_mode_activate_index_007d8c80",
      "va": "0x007d8c80"
    },
    {
      "match_basis": [
        "same_package",
        "same_subsystem",
        "same_class",
        "shared_types:OpaqueGameModeState"
      ],
      "package": "PKG-GAME-MODE-WAVE7",
      "score": 22,
      "symbol": "strategy_request_ready_00b5b840",
      "va": "0x00b5b840"
    },
    {
      "match_basis": [
        "same_package",
        "same_subsystem",
        "same_class",
        "shared_types:OpaqueGameModeState"
      ],
      "package": "PKG-GAME-MODE-WAVE7",
      "score": 22,
      "symbol": "strategy_queue_primary_00b5b880",
      "va": "0x00b5b880"
    },
    {
      "match_basis": [
        "same_package",
        "same_subsystem",
        "same_class",
        "shared_types:OpaqueGameModeState"
      ],
      "package": "PKG-GAME-MODE-WAVE7",
      "score": 22,
      "symbol": "strategy_queue_secondary_00b5b8a0",
      "va": "0x00b5b8a0"
    },
    {
      "match_basis": [
        "same_package",
        "same_subsystem",
        "same_class",
        "shared_types:OpaqueGameModeState"
      ],
      "package": "PKG-GAME-MODE-WAVE7",
      "score": 22,
      "symbol": "strategy_commit_primary_00b5b8c0",
      "va": "0x00b5b8c0"
    },
    {
      "match_basis": [
        "same_package",
        "same_subsystem",
        "same_class",
        "shared_types:OpaqueGameModeState"
      ],
      "package": "PKG-GAME-MODE-WAVE7",
      "score": 22,
      "symbol": "strategy_commit_secondary_00b5b8e0",
      "va": "0x00b5b8e0"
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
        "callsite": "0x00e616cf",
        "direction": "out",
        "other": "0x00f473a0",
        "reference_type": "direct-call"
      }
    ],
    "edges_truncated": false,
    "external_callees": [],
    "fan_in": 0,
    "fan_out": 0,
    "manifest_callees": [],
    "manifest_callers": [],
    "nearby_reconstructed": [],
    "scc": {
      "id": "scc-0531",
      "size": 1
    },
    "vtable_reference_count": 3
  },
  "evidence_level": "SUPPORTED",
  "globals": [],
  "integration_status": "integrated",
  "name": "cell_mode_constructor_00e616c0",
  "normalized_symbol": "cell_mode_constructor_00e616c0",
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
      "Observe constructor reachability, allocator identity, object vtable publication, owner vtable +0x20 target, and null-allocation behavior; runtime validation is not run."
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
      "reconstruction/metadata/pkg-game-mode-wave7/00e616c0.json"
    ],
    "provenance": [
      "ghidra:decompile_function",
      "ghidra:disassemble_function",
      "ghidra:get_function_callees",
      "ghidra:get_function_callers",
      "reconstruction/metadata/pkg-game-mode-wave7/00e616c0.json"
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
  "va": "0x00e616c0",
  "vtables": [
    "vtable:0x01485558"
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
  "body_end": "00e61709",
  "body_span_bytes": 74,
  "body_start": "00e616c0",
  "callees": [
    "FUN_00f473a0"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00e616c0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00e616c0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xa616c0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00e616c0(void)",
  "size_bytes": 74,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00e616c0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "00b5c9b7"
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
    "reconstruction/metadata/pkg-game-mode-wave7/00e616c0.json"
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
    "Observe constructor reachability, allocator identity, object vtable publication, owner vtable +0x20 target, and null-allocation behavior; runtime validation is not run."
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
  "vtable:0x01485558"
]
```

## Conflicts

```json
[
  {
    "anchors": [
      "0x00e61550",
      "0x00e616c0",
      "0x01485550",
      "0x01485550",
      "0x01485550"
    ],
    "conflict_id": "TB-INH-006",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": {
      "merge_decision": "structural_only",
      "preferred_claim": "Record interface implementation as structural interface evidence only.",
      "preserved_alternatives": true,
      "scope_note": "The current source is comparison-only and cannot backfill the original ABI.",
      "status": "preserved_alternatives",
      "taxonomy": "preserved_alternatives"
    },
    "resolution_status": "preserved_alternatives",
    "source": "knowledgegraph/research/conflicts/track-b-vtable-fields.json",
    "subject": "IGameMode implementation and cCellModeStrategy concrete table",
    "unresolved_reason": "The cited static evidence leaves the competing owner, slot, layout, or lifecycle interpretation unresolved; no positive original runtime or MSVC RTTI evidence is available."
  },
  {
    "anchors": [
      "0x01485550",
      "0x01485550",
      "0x01485550",
      "0x00e61550",
      "0x00e616c0",
      "0x01485550",
      "0x01485550",
      "0x00e61550",
      "0x01485550",
      "0x00e61550",
      "0x00e616c0",
      "0x0057ce80",
      "0x01485550",
      "0x01485550"
    ],
    "conflict_id": "TB-VT-002",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": {
      "merge_decision": "preferred_claim_with_limit",
      "preferred_claim": "App::cCellModeStrategy remains the preferred static identity for 0x01485550, with the cEditor projection explicitly retained.",
      "preserved_alternatives": true,
      "scope_note": "Preferred means stronger static evidence, not a resolved C++ owner or universal IGameMode ABI.",
      "status": "preferred_claim_with_limit",
      "taxonomy": "preferred_claim_with_limit"
    },
    "resolution_status": "preferred_claim_with_limit",
    "source": "knowledgegraph/research/conflicts/track-b-vtable-fields.json",
    "subject": "Vtable candidate 0x01485550 ownership and slot identity",
    "unresolved_reason": "The cited static evidence leaves the competing owner, slot, layout, or lifecycle interpretation unresolved; no positive original runtime or MSVC RTTI evidence is available."
  },
  {
    "anchors": [
      "0x00e80980",
      "0x00e818f0",
      "0x00e81cf0",
      "0x00e81f30",
      "0x00e552f0",
      "0x00e7fc00",
      "0x00e616c0",
      "0x00e80d8b",
      "0x01485550",
      "0x013f57f8",
      "0x01485550",
      "0x01485558",
      "0x01485550",
      "0x01485550",
      "0x01485558",
      "0x01485550"
    ],
    "conflict_id": "VT-002",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "RESOLVED_OBSERVED",
    "resolution_status": "RESOLVED_OBSERVED",
    "source": "knowledgegraph/research/conflicts/track-a-type-signature.json",
    "subject": "0x01485550/0x01485558 cCellModeStrategy vtable owner and base",
    "unresolved_reason": "The exact source-level name of the secondary subobject and the language-level interface declaration remain unproven, but the disputed table owner/base is resolved."
  }
]
```
