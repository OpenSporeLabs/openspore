# Evidence 0x00b63980

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `0b5eb717d5e43482f006c21d081e7db8c1d7065b06d0355137094ec9c7491d42`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "thiscall with one hidden ECX receiver and one ordinary stack word",
  "hidden_receiver": "ECX points to the destructible object",
  "ordinary_stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "role": "MSVC scalar deleting-destructor flag",
      "type": "uint32_t",
      "width_bytes": 4
    }
  ],
  "ret_form": "RET 0x4",
  "return_note": "opaque receiver pointer",
  "return_register": "EAX",
  "return_width_bytes": 4,
  "stack_cleanup_bytes": 4
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
          1
        ],
        "written": false
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x4",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
    "saved_registers": [
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
          1
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
  "content_sha256": "782b73c5285c05ec25f1a0f2da0ebba876e99371349fb0fe6cd7432007398b57",
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
    "persisted_calling_convention": "thiscall with one hidden ECX receiver and one ordinary stack word"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0011"
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
        "obs-0006"
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
        "obs-0002",
        "obs-0003"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          0
        ],
        "register": "ECX",
        "written_through": 1
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0011"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0011"
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
        "obs-0011"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0011"
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
      "at": "0x00b63980",
      "count": 4,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00b63981",
      "count": 1,
      "first_use": 1,
      "first_write_index": null,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00b63981",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00b63989",
      "id": "obs-0004",
      "index": 3,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x005725a0",
      "target": "0x005725a0"
    },
    {
      "at": "0x00b6398e",
      "count": 1,
      "first_use": 4,
      "first_write_index": 8,
      "id": "obs-0005",
      "index": 4,
      "kind": "REG_READ",
      "raw": "TEST byte ptr [ESP + 0x8],0x1",
      "reg": "ESP"
    },
    {
      "at": "0x00b6398e",
      "base": "ESP",
      "disp": 8,
      "id": "obs-0006",
      "index": 4,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "TEST byte ptr [ESP + 0x8],0x1",
      "resolved": true,
      "size": 1
    },
    {
      "at": "0x00b63996",
      "id": "obs-0007",
      "index": 7,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00f47380",
      "target": "0x00f47380"
    },
    {
      "at": "0x00b6399b",
      "definite": true,
      "id": "obs-0008",
      "index": 8,
      "kind": "REG_WRITE",
      "raw": "ADD ESP,0x4",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00b6399e",
      "definite": true,
      "id": "obs-0009",
      "index": 9,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,ESI",
      "reg": "EAX",
      "write_kind": "reg"
    },
    {
      "at": "0x00b639a0",
      "id": "obs-0010",
      "index": 10,
      "kind": "REG_RESTORE",
      "raw": "POP ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00b639a1",
      "form": "RET 0x4",
      "
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
      "0x00b3d480",
      "0x00b3d480",
      "0x00b31da0",
      "0x00b321e0",
      "0x005c7d00",
      "0x005c7cb0",
      "0x005c7f10",
      "0x005c7f70",
      "0x00b32330",
      "0x00b32560",
      "0x00b63980",
      "0x00b32390",
      "0x00b32330",
      "0x00b32560",
      "0x00e63560",
      "0x005c7d00"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/additional-domains.json:2",
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
      "0x00587270",
      "0x0059d840",
      "0x0059d8b0",
      "0x00587270",
      "0x0059d8b0",
      "0x0059d840",
      "0x0067cae0",
      "0x00b31da0",
      "0x0059ca70",
      "0x0059cac0",
      "0x00b321e0",
      "0x00b32330",
      "0x00b32560",
      "0x0059cea0",
      "0x0059cf00",
      "0x00b63980"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/additional-domains.json:3",
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
      "0x00676e90",
      "0x00676e90",
      "0x00676e50",
      "0x00b31da0",
      "0x006766d0",
      "0x006766b0",
      "0x00676620",
      "0x00b321e0",
      "0x00676c40",
      "0x00b32330",
      "0x00676e90",
      "0x00b32560",
      "0x0067dd90",
      "0x00b63980",
      "0x00b32390",
      "0x00e66280"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/additional-domains.json:6",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The cited stream or file boundary is retained, but the complete wire/transaction/round-trip contract is not reconstructed.",
    "resolution_status": "The cited stream or file boundary is retained, but the complete wire/transaction/round-trip contract is not reconstructed.",
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
  "count": 12,
  "instructions": [
    {
      "address": "00b63980",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00b63981",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00b63983",
      "instruction": "MOV dword ptr [ESI],0x1464450"
    },
    {
      "address": "00b63989",
      "instruction": "CALL 0x005725a0"
    },
    {
      "address": "00b6398e",
      "instruction": "TEST byte ptr [ESP + 0x8],0x1"
    },
    {
      "address": "00b63993",
      "instruction": "JZ 0x00b6399e"
    },
    {
      "address": "00b63995",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00b63996",
      "instruction": "CALL 0x00f47380"
    },
    {
      "address": "00b6399b",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "00b6399e",
      "instruction": "MOV EAX,ESI"
    },
    {
      "address": "00b639a0",
      "instruction": "POP ESI"
    },
    {
      "address": "00b639a1",
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
    "calling_convention": "thiscall with one hidden ECX receiver and one ordinary stack word",
    "hidden_receiver": "ECX points to the destructible object",
    "ordinary_stack_arguments": [
      {
        "entry_offset": "ESP+0x04",
        "role": "MSVC scalar deleting-destructor flag",
        "type": "uint32_t",
        "width_bytes": 4
      }
    ],
    "ret_form": "RET 0x4",
    "return_note": "opaque receiver pointer",
    "return_register": "EAX",
    "return_width_bytes": 4,
    "stack_cleanup_bytes": 4
  },
  "analogues": [
    {
      "match_basis": [
        "same_package"
      ],
      "package": "PKG-WAVE6-MISC-ENGINE",
      "score": 8,
      "symbol": "message_manager_get_queue_0098f4d0",
      "va": "0x0098f4d0"
    },
    {
      "match_basis": [
        "same_package"
      ],
      "package": "PKG-WAVE6-MISC-ENGINE",
      "score": 8,
      "symbol": "game_time_manager_get_00b3d480",
      "va": "0x00b3d480"
    },
    {
      "match_basis": [
        "shared_types:opaque receiver pointer"
      ],
      "package": "PKG-20-PERSISTENCE-BOUNDARY",
      "score": 3,
      "symbol": "ProfilePersistenceBoundary_run_candidate_00b28ec0",
      "va": "0x00b28ec0"
    }
  ],
  "audit_evidence_boundary": "The vtable writes, base-call order, bit-zero-only delete, global-delete boundary, receiver return, and RET 4 are exact; the imported TimeAtStartOfFrame label and concrete class are rejected or unresolved.",
  "audit_findings": [],
  "audit_status": "pass_after_repair",
  "blocked": false,
  "blockers": [],
  "body_status": "integrated",
  "class_type": "OpaqueDestructible",
  "cluster": null,
  "confidence": 0.91,
  "dependencies": {
    "callees": [],
    "callees_truncated": false,
    "callers": [],
    "callers_truncated": false,
    "data_reference_count": 0,
    "edges": [
      {
        "callsite": "0x00b63989",
        "direction": "out",
        "other": "0x005725a0",
        "reference_type": "direct-call"
      },
      {
        "callsite": "0x00b63996",
        "direction": "out",
        "other": "0x00f47380",
        "reference_type": "direct-call"
      }
    ],
    "edges_truncated": false,
    "external_callees": [],
    "fan_in": 0,
    "fan_out": 0,
    "manifest_callees": [
      "0x005725a0",
      "0x00f47380"
    ],
    "manifest_callers": [
      "data_xref_01464450"
    ],
    "nearby_reconstructed": [],
    "scc": {
      "id": "scc-0400",
      "size": 1
    },
    "vtable_reference_count": 0
  },
  "evidence_level": "OBSERVED",
  "globals": [],
  "integration_status": "integrated",
  "name": "destructible_lifecycle_thunk_00b63980",
  "normalized_symbol": "destructible_lifecycle_thunk_00b63980",
  "observed_mechanics": [
    "thiscall receiver and one stack word",
    "store vtable 0x01464450 first",
    "call base destructor 0x005725a0",
    "test only bit zero of deleting flag",
    "call global delete 0x00f47380 when set",
    "return the original receiver in EAX",
    "RET 4"
  ],
  "ownership": {
    "claimability": "do_not_claim",
    "handoff_packages": [
      "PKG-WAVE6-MISC-ENGINE"
    ],
    "manifest": {
      "record": null,
      "worker_ownership": null
    },
    "package": "PKG-WAVE6-MISC-ENGINE",
    "queue_state": null
  },
  "package": "PKG-WAVE6-MISC-ENGINE",
  "reconstructed": true,
  "review_status": "approved",
  "runtime": {
    "blocking_reason": null,
    "gates": [
      "gate-deleting-destructor-vtable-and-global-delete"
    ],
    "validated": 0
  },
  "runtime_gated": true,
  "runtime_validated": 0,
  "semantic": null,
  "semantic_status": "static_deleting_destructor_vtable_and_delete_order_runtime_class_ownership_unknown",
  "services": [],
  "source": {
    "decomp": null,
    "file": "src/reconstruction/wave6_misc_engine/misc_engine.cpp",
    "files": [
      "reconstruction/staging/wave6-misc-engine/misc_engine.cpp",
      "reconstruction/staging/wave6-misc-engine/misc_engine.hpp",
      "reconstruction/staging/wave6-misc-engine/misc_engine_model_test.cpp",
      "src/reconstruction/wave6_misc_engine/misc_engine.cpp"
    ],
    "handoffs": [
      "reconstruction/integrated/batch-2026-09-25-wave6/handoff.json"
    ],
    "metadata": [
      "reconstruction/metadata/wave6-misc-engine/00b63980.json"
    ],
    "provenance": [
      "reconstruction/metadata/wave6-misc-engine/00b63980.json"
    ]
  },
  "status": "reconstructed",
  "subsystem": "Core.Lifecycle",
  "triage": null,
  "types": [
    "DeletingDestructorPorts",
    "OpaqueDestructible",
    "opaque receiver pointer",
    "uint32_t"
  ],
  "unresolved_questions": [
    "Is the function a scalar deleting destructor, a generated adapter, or a differently named lifecycle thunk?",
    "What allocator, reference-count, and destruction behavior is hidden in 0x00f47380 and 0x009276c0?",
    "What object state does 0x005725a0 destroy beyond its vtable write?",
    "What runtime vtable path reaches the function despite zero direct callers?",
    "Which concrete class owns the vtable at 0x01464450?",
    "base and global-delete effects",
    "concrete vtable owner",
    "runtime vtable reachability",
    "whether the entry is a scalar deleting destructor or generated lifecycle thunk"
  ],
  "va": "0x00b63980",
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
  "body_end": "00b639a3",
  "body_span_bytes": 36,
  "body_start": "00b63980",
  "callees": [
    "FUN_00f47380",
    "FUN_005725a0"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00b63980",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "Simulator::TimeAtStartOfFrame",
  "namespace": "Simulator",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "LARGE_INTEGER",
  "return_type_resolved": true,
  "rva": "0x763980",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "LARGE_INTEGER Simulator::TimeAtStartOfFrame(void)",
  "size_bytes": 36,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00b63980",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "01464450"
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
  "file": "src/reconstruction/wave6_misc_engine/misc_engine.cpp",
  "files": [
    "reconstruction/staging/wave6-misc-engine/misc_engine.cpp",
    "reconstruction/staging/wave6-misc-engine/misc_engine.hpp",
    "reconstruction/staging/wave6-misc-engine/misc_engine_model_test.cpp",
    "src/reconstruction/wave6_misc_engine/misc_engine.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/wave6-misc-engine/00b63980.json"
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
    "gate-deleting-destructor-vtable-and-global-delete"
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
  "DeletingDestructorPorts",
  "OpaqueDestructible",
  "opaque receiver pointer",
  "uint32_t"
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
      "0x00b3d480",
      "0x00b3d480",
      "0x00b31da0",
      "0x00b321e0",
      "0x005c7d00",
      "0x005c7cb0",
      "0x005c7f10",
      "0x005c7f70",
      "0x00b32330",
      "0x00b32560",
      "0x00b63980",
      "0x00b32390",
      "0x00b32330",
      "0x00b32560",
      "0x00e63560",
      "0x005c7d00"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/additional-domains.json:2",
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
      "0x00587270",
      "0x0059d840",
      "0x0059d8b0",
      "0x00587270",
      "0x0059d8b0",
      "0x0059d840",
      "0x0067cae0",
      "0x00b31da0",
      "0x0059ca70",
      "0x0059cac0",
      "0x00b321e0",
      "0x00b32330",
      "0x00b32560",
      "0x0059cea0",
      "0x0059cf00",
      "0x00b63980"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/additional-domains.json:3",
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
      "0x00676e90",
      "0x00676e90",
      "0x00676e50",
      "0x00b31da0",
      "0x006766d0",
      "0x006766b0",
      "0x00676620",
      "0x00b321e0",
      "0x00676c40",
      "0x00b32330",
      "0x00676e90",
      "0x00b32560",
      "0x0067dd90",
      "0x00b63980",
      "0x00b32390",
      "0x00e66280"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/additional-domains.json:6",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The cited stream or file boundary is retained, but the complete wire/transaction/round-trip contract is not reconstructed.",
    "resolution_status": "The cited stream or file boundary is retained, but the complete wire/transaction/round-trip contract is not reconstructed.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  }
]
```
