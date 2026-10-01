# Evidence 0x00d1dcd0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `3f303f89f9923f4abd8f43be7a7e780fdcf61024536bd6be2df03e201a286fed`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall (no stack arguments, no cleanup)",
  "hidden_this_register": "ECX",
  "ordinary_stack_arguments": [],
  "ret_form": "plain RET",
  "return_register": "EAX",
  "return_type": "char *",
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
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "pointer_like_in_EAX",
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "3a76ddb0bcbb1547371105e7e48d5d937dc80012a6a0c5e5e63f2d7126d64973",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall",
      "__fastcall"
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
    "persisted_calling_convention": "__thiscall (no stack arguments, no cleanup)"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0003"
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
        "obs-0002"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          304
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0002",
        "obs-0003"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0003"
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
        "obs-0003"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0003"
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
      "at": "0x00d1dcd0",
      "count": 1,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ECX + 0x130]",
      "reg": "ECX"
    },
    {
      "at": "0x00d1dcd0",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ECX + 0x130]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00d1dcd6",
      "form": "RET",
      "id": "obs-0003",
      "imm": null,
      "index": 1,
      "kind": "RET",
      "raw": "RET"
    }
  ],
  "parse": {
    "declared_count": 2,
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
    "confidence": "INFERRED",
    "distinct_offsets": 1,
    "max_offset": 304,
    "offsets": [
      304
    ],
    "present": true,
    "register": "ECX",
    "shape": "R-DIRECT",
    "written_through": 0
  },
  "return": {
    "aggregate_evidence": {
      "bulk_write": false
    },
    "confidence": "INFERRED",
    "register": "EAX",
    "register_class": "pointer_like",
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
    "confidence": "APPROXIMATION",
    "derived_slots": 0,
    "gaps": 0,
    "not_complete": false,
    "observed_slots": 0,
    "slots": [],
    "total_bytes": 0,
    "widths_ambiguous": false
  },
  "tail_call": {
    "after_frame_setup": false,
    "form": null,
    "present": false,
    "target": null
  },
  "target": {
    "address_available": true,
    "image_base": "0x00400000",
    "instructions": 2,
    "syntax": "intel",
    "va": "0x00d1dcd0"
  },
  "variadic": "UNKNOWN",
  "verdict": "ABI_INFERRED"
}
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
  "count": 2,
  "instructions": [
    {
      "address": "00d1dcd0",
      "instruction": "MOV EAX,dword ptr [ECX + 0x130]"
    },
    {
      "address": "00d1dcd6",
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
    "calling_convention": "__thiscall (no stack arguments, no cleanup)",
    "hidden_this_register": "ECX",
    "ordinary_stack_arguments": [],
    "ret_form": "plain RET",
    "return_register": "EAX",
    "return_type": "char *",
    "stack_cleanup_bytes": 0
  },
  "analogues": [
    {
      "match_basis": [
        "same_calling_convention"
      ],
      "package": "PKG-UTFWIN-DRAWABLE-WAVE9",
      "score": 2,
      "symbol": "re_00985ce0",
      "va": "0x00985ce0"
    }
  ],
  "audit_evidence_boundary": "Static x86-32 mechanics, register/stack argument contract, stack cleanup width, RET form, offsets, constants, strides, and slot indices were read from the live Ghidra disassembly; imported signatures are candidate labels only. Concrete vtable and port owners, runtime values, and ownership remain gated.",
  "audit_findings": [],
  "audit_status": "clean_after_semantic_abi_and_lifecycle_review",
  "blocked": false,
  "blockers": [],
  "body_status": "integrated",
  "class_type": "FormatParser",
  "cluster": "scripting-content",
  "confidence": 0.98,
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
      "id": "scc-0495",
      "size": 1
    },
    "vtable_reference_count": 0
  },
  "evidence_level": "OBSERVED",
  "globals": [],
  "integration_status": "integrated",
  "name": "ArgScript::FormatParser::GetCurrentScope",
  "normalized_symbol": "pkg_argscript_get_current_scope_00d1dcd0",
  "observed_mechanics": [
    "MOV EAX,[ECX+0x130] (opcode 8b 81 with a 32-bit displacement).",
    "RET."
  ],
  "ownership": {
    "claimability": "do_not_claim",
    "handoff_packages": [
      "PKG-ARGSCRIPT-WAVE9"
    ],
    "manifest": {
      "record": null,
      "worker_ownership": null
    },
    "package": "PKG-ARGSCRIPT-WAVE9",
    "queue_state": "queued"
  },
  "package": "PKG-ARGSCRIPT-WAVE9",
  "reconstructed": true,
  "review_status": "approved",
  "runtime": {
    "blocking_reason": null,
    "gates": [
      "An empty scope returns a null begin word rather than a sentinel string; callers' null handling is unverified.",
      "No original-process invocation or indirect-caller trace was captured.",
      "Ownership and lifetime of the returned character pointer are unresolved; no reference count is taken or released.",
      "The +0x130 string header layout (begin, end, capacity, allocator) is inferred from adjacent fields and is unverified at runtime.",
      "gate-argscript-scope-string-header-layout"
    ],
    "validated": 0
  },
  "runtime_gated": true,
  "runtime_validated": 0,
  "semantic": null,
  "semantic_status": "static_single_load_scope_field_projection_observed",
  "services": [],
  "source": {
    "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/ArgScript__FormatParser__GetCurrentScope.c",
    "file": "src/reconstruction/pkg_argscript_wave9/argscript_get_current_scope.cpp",
    "files": [
      ".spore-analysis/ghidra-exports/decompiled_sdk/ArgScript__FormatParser__GetCurrentScope.c",
      "src/reconstruction/pkg_argscript_wave9",
      "src/reconstruction/pkg_argscript_wave9/argscript_get_current_scope.cpp",
      "src/reconstruction/pkg_argscript_wave9/argscript_get_current_scope.hpp",
      "src/reconstruction/pkg_argscript_wave9/argscript_get_current_scope_model_test.cpp"
    ],
    "handoffs": [
      "reconstruction/integrated/batch-2026-09-25-wave9-safe-core/handoff.json"
    ],
    "metadata": [
      "reconstruction/metadata/pkg-argscript-wave9/00d1dcd0.json"
    ],
    "provenance": [
      "ghidra:disassemble_function:0x00d1dcd0",
      "ghidra:get_function_by_address:0x00d1dcd0",
      "ghidra:get_function_callees:0x00d1dcd0",
      "ghidra:get_function_callers:0x00d1dcd0",
      "reconstruction/integrated/batch-2026-09-25-wave9-safe-core/handoff.json",
      "reconstruction/metadata/pkg-argscript-wave9/00d1dcd0.json"
    ]
  },
  "status": "reconstructed",
  "subsystem": "ArgScript",
  "triage": {
    "category": "ENGINE_INTERFACE",
    "cluster": "scripting-content",
    "db_triage_status": "QUEUED",
    "decomp_path": ".spore-analysis/ghidra-exports/decompiled_sdk/ArgScript__FormatParser__GetCurrentScope.c",
    "dependencies": [
      "resource-io"
    ],
    "evidence": "CONFIRMED",
    "kg_node_id": "fun:00d1dcd0",
    "name": "ArgScript::FormatParser::GetCurrentScope",
    "priority": "P0",
    "provenance": {
      "classifier": "triage-v4",
      "generated_at": "2026-09-23T10:12:09Z",
      "generator": "subagent-7-sequential-triage",
      "sdk_name": "ArgScript::FormatParser::GetCurrentScope",
      "snapshot": "2540f2ca",
      "snapshot_sha256": "2540f2ca7cd361a72b559448fa5cf247eff3cee20d375b14ed0dd256c45229c8",
      "vtable_addrs": [
        "0141c930",
        "0141c97c",
        "0147a200"
      ]
    },
    "queue_state": "queued",
    "rank": 88
  },
  "types": [
    "FormatParser",
    "char *"
  ],
  "unresolved_questions": [
    "Confirmed layout of the +0x130 string header and the +0x154 secondary string",
    "Ownership of the returned scope pointer",
    "Whether callers treat a null scope as valid",
    "Whether the +0x164/+0x168 state words gate scope validity"
  ],
  "va": "0x00d1dcd0",
  "vtables": [
    "vtable:0x0141c930",
    "vtable:0x0141c97c",
    "vtable:0x0147a200"
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
  "body_end": "00d1dcd6",
  "body_span_bytes": 7,
  "body_start": "00d1dcd0",
  "callees": [],
  "callers": [],
  "classification": "stub",
  "dispatch": null,
  "entry_point": "00d1dcd0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "ArgScript::FormatParser::GetCurrentScope",
  "namespace": "ArgScript",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 1,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "FormatParser *"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "char *",
  "return_type_resolved": true,
  "rva": "0x91dcd0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "char * ArgScript::FormatParser::GetCurrentScope(FormatParser * this)",
  "size_bytes": 7,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00d1dcd0",
  "vtables": {
    "referenced_by_vtables": [
      "0x0141c930",
      "0x0141c97c",
      "0x0147a200"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 2,
  "xrefs": [
    {
      "from": "0141c9b8"
    },
    {
      "from": "0147a270"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/ArgScript__FormatParser__GetCurrentScope.c",
  "file": "src/reconstruction/pkg_argscript_wave9/argscript_get_current_scope.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/ArgScript__FormatParser__GetCurrentScope.c",
    "src/reconstruction/pkg_argscript_wave9/argscript_get_current_scope.cpp",
    "src/reconstruction/pkg_argscript_wave9/argscript_get_current_scope.hpp",
    "src/reconstruction/pkg_argscript_wave9/argscript_get_current_scope_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave9-safe-core/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-argscript-wave9/00d1dcd0.json"
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
    "An empty scope returns a null begin word rather than a sentinel string; callers' null handling is unverified.",
    "No original-process invocation or indirect-caller trace was captured.",
    "Ownership and lifetime of the returned character pointer are unresolved; no reference count is taken or released.",
    "The +0x130 string header layout (begin, end, capacity, allocator) is inferred from adjacent fields and is unverified at runtime.",
    "gate-argscript-scope-string-header-layout"
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
  "FormatParser",
  "char *"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x0141c930",
  "vtable:0x0141c97c",
  "vtable:0x0147a200"
]
```

## Conflicts

```json
[]
```
