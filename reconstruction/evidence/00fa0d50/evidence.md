# Evidence 0x00fa0d50

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `fc6cc7d4b34417a3093d4e988b49b490814f2a795216c189468577d30e6f438e`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "__thiscall",
  "ordinary_stack_argument_slots": 0,
  "receiver": {
    "provenance": "vftable_slot",
    "register": "ECX",
    "width_bytes": 4
  },
  "return_observation": "XADD.LOCK leaves the pre-increment value in EAX; INC EAX makes the returned word the post-increment value.",
  "return_register": "EAX",
  "return_semantics": "integral_in_EAX",
  "return_type": "std::uint32_t",
  "return_width_bytes": 4,
  "stack_arguments": [],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "RET"
}
```

## abi_derived

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function, tools/reconstruction_tooling/vftables.py@25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e`

```json
{
  "abi": {
    "architecture": "x86-32",
    "calling_convention": "__thiscall",
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "receiver_not_determinable: ecx_reassigned_before_deref"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "d17caf1cbcc8a8c570558ba75c48912622dd296c16937217e0f143c4836ef10d",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall",
      "__fastcall"
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
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0006"
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
        "obs-0001",
        "obs-0003",
        "obs-0004",
        "obs-0005"
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
        "obs-0006"
      ],
      "claim": "calling convention is __thiscall: 0x00fa0d50 is slot 1 of the vptr-backed vftable at 0x0140a028, so it is a virtual member of some class; the callee pops nothing and no stack word is read as an argument, so the receiver is in a register, and ECX is the only one that carries one",
      "confidence": "INFERRED",
      "id": "V1-VFT",
      "value": {
        "cleanup_side": "caller",
        "membership_count": 2,
        "receiver_provenance": "vftable_slot",
        "receiver_register": "ECX",
        "slot_index": 1,
        "table": "0x0140a028"
      }
    },
    {
      "based_on": [
        "obs-0006"
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
        "obs-0006"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0006"
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
      "at": "0x00fa0d50",
      "definite": true,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "ADD ECX,0x14",
      "reg": "ECX",
      "write_kind": "arith"
    },
    {
      "at": "0x00fa0d53",
      "definite": true,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,0x1",
      "reg": "EAX",
      "write_kind": "imm"
    },
    {
      "at": "0x00fa0d58",
      "count": 1,
      "first_use": 2,
      "first_write_index": 0,
      "id": "obs-0003",
      "index": 2,
      "kind": "REG_READ",
      "raw": "XADD.LOCK dword ptr [ECX],EAX",
      "reg": "ECX"
    },
    {
      "at": "0x00fa0d58",
      "count": 1,
      "first_use": 2,
      "first_write_index": 1,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "XADD.LOCK dword ptr [ECX],EAX",
      "reg": "EAX"
    },
    {
      "at": "0x00fa0d58",
      "clobbers": [
        "EAX",
        "ECX"
      ],
      "form": "XADD.LOCK",
      "id": "obs-0005",
      "index": 2,
      "kind": "STRING_OP",
      "raw": "XADD.LOCK dword ptr [ECX],EAX",
      "rep": false,
      "string_base": false
    },
    {
      "at": "0x00fa0d5d",
      "form": "RET",
      "id": "obs-0006",
      "imm": null,
      "index": 4,
      "kind": "RET",
      "raw": "RET"
    }
  ],
  "parse": {
    "declared_count": 5,
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
    "confidence": "UNKNOWN",
    "distinct_offsets": 0,
    "max_offset": null,
    "offsets": [],
    "present": null,
    "provenance": "vftable_slot",
    "reason": "ecx_reassigned_before_deref",
    "register": "ECX",
    "shape": null,
    "written_through": 0
  },
  "return": {
    "aggregate_evidence": {
      "bulk_write": false
    },
    "confidence": "INFERRED",
    "register": "EAX",
    "register_class": "integral",
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
    "hypothesis_confide
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

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

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
  "count": 5,
  "instructions": [
    {
      "address": "00fa0d50",
      "instruction": "ADD ECX,0x14"
    },
    {
      "address": "00fa0d53",
      "instruction": "MOV EAX,0x1"
    },
    {
      "address": "00fa0d58",
      "instruction": "XADD.LOCK dword ptr [ECX],EAX"
    },
    {
      "address": "00fa0d5c",
      "instruction": "INC EAX"
    },
    {
      "address": "00fa0d5d",
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
    "calling_convention": "__thiscall",
    "ordinary_stack_argument_slots": 0,
    "receiver": {
      "provenance": "vftable_slot",
      "register": "ECX",
      "width_bytes": 4
    },
    "return_observation": "XADD.LOCK leaves the pre-increment value in EAX; INC EAX makes the returned word the post-increment value.",
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
    "return_type": "std::uint32_t",
    "return_width_bytes": 4,
    "stack_arguments": [],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "analogues": [
    {
      "match_basis": [
        "shared_vtable:vtable:0x01490be8"
      ],
      "package": "PKG-16-SPOREPEDIA-ONLINE",
      "score": 4,
      "symbol": "Sporepedia_cSPAssetDataOTDB_HasName_raw_00641770",
      "va": "0x00641770"
    },
    {
      "match_basis": [
        "same_calling_convention"
      ],
      "package": "PKG-APP-SAFE-WAVE11",
      "score": 2,
      "symbol": "property_record_assign_pair_004279d0",
      "va": "0x004279d0"
    },
    {
      "match_basis": [
        "same_calling_convention"
      ],
      "package": "PKG-APP-SAFE-WAVE11",
      "score": 2,
      "symbol": "property_record_assign_scalar_00428060",
      "va": "0x00428060"
    },
    {
      "match_basis": [
        "same_calling_convention"
      ],
      "package": "PKG-EDITOR-SAFE-WAVE11",
      "score": 2,
      "symbol": "editor_paint_commit_0043ac40",
      "va": "0x0043ac40"
    },
    {
      "match_basis": [
        "same_calling_convention"
      ],
      "package": "PKG-APP-SAFE-WAVE11",
      "score": 2,
      "symbol": "model_parts_apply_properties_00447150",
      "va": "0x00447150"
    },
    {
      "match_basis": [
        "same_calling_convention"
      ],
      "package": "PKG-APP-SAFE-WAVE11",
      "score": 2,
      "symbol": "pair_vector_insert_004786e0",
      "va": "0x004786e0"
    },
    {
      "match_basis": [
        "same_calling_convention"
      ],
      "package": "PKG-EDITOR-SAFE-WAVE11",
      "score": 2,
      "symbol": "editor_entry_expand_004ad6f0",
      "va": "0x004ad6f0"
    },
    {
      "match_basis": [
        "same_calling_convention"
      ],
      "package": "PKG-10-EDITOR-DISPATCH",
      "score": 2,
      "symbol": "Editors_EditorModel_SetColor_raw_004ae250",
      "va": "0x004ae250"
    }
  ],
  "audit_evidence_boundary": null,
  "audit_findings": [],
  "audit_status": null,
  "blocked": false,
  "blockers": [
    "Runtime validation against the original process is an open capability gate: nothing was attempted and nothing failed."
  ],
  "body_status": null,
  "class_type": null,
  "cluster": "sporepedia-online",
  "confidence": null,
  "dependencies": {
    "callees": [],
    "callees_truncated": false,
    "callers": [],
    "callers_truncated": false,
    "data_reference_count": 0,
    "edges": [],
    "edges_truncated": false,
    "external_callees": [],
    "fan_in": 0,
    "fan_out": 0,
    "manifest_callees": [],
    "manifest_callers": [],
    "nearby_reconstructed": [],
    "scc": {
      "id": "scc-0576",
      "size": 1
    },
    "vtable_reference_count": 0
  },
  "evidence_level": "INFERRED",
  "globals": [],
  "integration_status": null,
  "name": "FUN_00fa0d50",
  "normalized_symbol": "FUN_00fa0d50",
  "observed_mechanics": [],
  "ownership": {
    "claimability": "queue_candidate",
    "handoff_packages": [],
    "manifest": {
      "record": null,
      "worker_ownership": null
    },
    "package": null,
    "queue_state": "candidate"
  },
  "package": null,
  "reconstructed": false,
  "review_status": null,
  "runtime": {
    "blocking_reason": null,
    "gates": [],
    "validated": 0
  },
  "runtime_gated": false,
  "runtime_validated": 0,
  "semantic": null,
  "semantic_status": null,
  "services": [],
  "source": {
    "decomp": null,
    "file": null,
    "files": [
      "reconstruction/staging/pkg-fa0d50-atomic-inc/atomic_inc.cpp",
      "reconstruction/staging/pkg-fa0d50-atomic-inc/atomic_inc.hpp",
      "reconstruction/staging/pkg-fa0d50-atomic-inc/atomic_inc_model_test.cpp"
    ],
    "handoffs": [],
    "metadata": [
      "reconstruction/metadata/pkg-fa0d50-atomic-inc/00fa0d50.json"
    ],
    "provenance": []
  },
  "status": "candidate",
  "subsystem": "Sporepedia",
  "triage": {
    "category": "GAMEPLAY_LOGIC",
    "cluster": "sporepedia-online",
    "db_triage_status": "candidate",
    "decomp_path": null,
    "dependencies": [],
    "evidence": "INFERRED",
    "kg_node_id": "fun:00fa0d50",
    "name": "FUN_00fa0d50",
    "priority": "P1",
    "provenance": {
      "classifier": "triage-v5",
      "sdk_name": null,
      "snapshot": "f0e310e0",
      "snapshot_sha256": "f0e310e0c83fc960ed38d490ff6d2a78d53925969206b4c4db7a012ddbf8b54b",
      "vtable_addrs": [
        "0140a028",
        "01490be8"
      ]
    },
    "queue_state": "candidate",
    "rank": 282
  },
  "types": [
    "std::uint32_t"
  ],
  "unresolved_questions": [
    "The runtime role of the counter at receiver +0x14 (reference count, ownership flag, or other): the body fixes its location, width, and atomic increment, not its meaning.",
    "Whether the two memberships (0x0140a028 slot 1, 0x01490be8 slot 0) are one class seen through two bases or two distinct classes.",
    "Which class this virtual member belongs to: vftable slot membership yields 'virtual member of some class' and no class name is inferred."
  ],
  "va": "0x00fa0d50",
  "vtables": [
    "vtable:0x0140a028",
    "vtable:0x01490be8"
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
  "body_end": "00fa0d5d",
  "body_span_bytes": 14,
  "body_start": "00fa0d50",
  "callees": [],
  "callers": [],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "00fa0d50",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00fa0d50",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xba0d50",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00fa0d50(void)",
  "size_bytes": 14,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00fa0d50",
  "vtables": {
    "referenced_by_vtables": [
      "0x01490be8",
      "0x0140a028"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 5,
  "xrefs": [
    {
      "from": "01490be8"
    },
    {
      "from": "00fa0ea3"
    },
    {
      "from": "00fa0eb3"
    },
    {
      "from": "00fa0ee3"
    },
    {
      "from": "00fa0ef3"
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
  "files": [
    "reconstruction/staging/pkg-fa0d50-atomic-inc/atomic_inc.cpp",
    "reconstruction/staging/pkg-fa0d50-atomic-inc/atomic_inc.hpp",
    "reconstruction/staging/pkg-fa0d50-atomic-inc/atomic_inc_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-fa0d50-atomic-inc/00fa0d50.json"
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
  "status": "candidate"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "std::uint32_t"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x0140a028",
  "vtable:0x01490be8"
]
```

## Conflicts

```json
[]
```
