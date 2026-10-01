# Evidence 0x007e6080

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `212fb23380f69db34f35e883b4edfa432fd9cfe8b3a448f779724c00bc1bc6f2`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "thiscall-shaped tail wrapper",
  "hidden_receiver": "ECX OpaqueAppSystem*",
  "ordinary_stack_arguments": [],
  "return_note": "at the imported method boundary",
  "return_type": "void",
  "stack_cleanup_bytes": 0,
  "termination": "JMP 0x00929bd0"
}
```

## abi_derived

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function, tools/reconstruction_tooling/abi_infer.py#tail_target=0x00929bd0`

```json
{
  "abi": {
    "architecture": "x86-32",
    "receiver": false,
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller"
  },
  "abstained_because": [
    "no_terminal_ret: the only exit observed is a tail jump"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "forwarded_from_tail_target",
    "evidence": "forwarded from the tail target 0x00929bd0: ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "EMPTY",
  "conflicts": [],
  "content_sha256": "39359ed0ba58e7d893646f7b5ac8e09216cf36b29f1461b0262749359c824a56",
  "conventions": {
    "ambiguities": [
      "tail_call"
    ],
    "calling_convention": null,
    "candidate_conventions": [
      "__cdecl",
      "__stdcall",
      "__thiscall",
      "__fastcall"
    ],
    "confidence": "UNKNOWN",
    "corroboration": "not_available"
  },
  "cross_validation": {
    "agreement": false,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 1,
    "persisted": "no_information",
    "persisted_calling_convention": "thiscall-shaped tail wrapper"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0001"
      ],
      "claim": "no terminal return is present in the listing",
      "confidence": "UNKNOWN",
      "id": "C2"
    },
    {
      "based_on": [
        "obs-0001"
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
        "obs-0001"
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
        "obs-0001"
      ],
      "claim": "this listing is a tail transfer: it inherits its caller's frame and never runs its own RET",
      "confidence": "UNKNOWN",
      "id": "T1",
      "value": {
        "form": "jmp"
      }
    },
    {
      "based_on": [
        "obs-0001"
      ],
      "claim": "the stack cleanup is caller with 0 byte(s), forwarded from the tail target 0x00929bd0; the target's own calling convention is not decided, so none is forwarded (resolved from live listing for 0x00929bd0)",
      "confidence": "INFERRED",
      "id": "T1-FWD",
      "value": {
        "target": "0x00929bd0",
        "target_calling_convention": null,
        "target_cleanup_side": "caller",
        "target_source": "live listing for 0x00929bd0",
        "target_stack_bytes": 0
      }
    }
  ],
  "observations": [
    {
      "at": "0x007e6080",
      "id": "obs-0001",
      "index": 0,
      "kind": "UNCOND_TRANSFER_OUT",
      "raw": "JMP 0x00929bd0",
      "target": "0x00929bd0"
    }
  ],
  "parse": {
    "declared_count": 1,
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
    "confidence": "UNKNOWN",
    "register": null,
    "register_class": "unknown",
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
    "form": "jmp",
    "present": true,
    "target": "0x00929bd0"
  },
  "target": {
    "address_available": true,
    "image_base": "0x00400000",
    "instructions": 1,
    "syntax": "intel",
    "va": "0x007e6080"
  },
  "variadic": "UNKNOWN",
  "verdict": "ABI_UNKNOWN"
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
  "count": 1,
  "instructions": [
    {
      "address": "007e6080",
      "instruction": "JMP 0x00929bd0"
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
    "calling_convention": "thiscall-shaped tail wrapper",
    "hidden_receiver": "ECX OpaqueAppSystem*",
    "ordinary_stack_arguments": [],
    "return_note": "at the imported method boundary",
    "return_type": "void",
    "stack_cleanup_bytes": 0,
    "termination": "JMP 0x00929bd0"
  },
  "analogues": [
    {
      "match_basis": [
        "same_package",
        "same_subsystem",
        "same_class",
        "shared_types:DATA,OpaqueAppSystem"
      ],
      "package": "PKG-APP-LIFECYCLE-WAVE7",
      "score": 25,
      "symbol": "app_capp_system_set_effect_collection_ids_007e6100",
      "va": "0x007e6100"
    },
    {
      "match_basis": [
        "same_package",
        "same_subsystem",
        "same_class",
        "shared_types:DATA,OpaqueAppSystem"
      ],
      "package": "PKG-APP-LIFECYCLE-WAVE7",
      "score": 25,
      "symbol": "app_capp_system_func88h_00a6c940",
      "va": "0x00a6c940"
    },
    {
      "match_basis": [
        "same_subsystem",
        "shared_types:DATA"
      ],
      "package": "WAVE6-ENGINE-RUNTIME",
      "score": 9,
      "symbol": "app_system_service_gate_dispatch_007e5f30",
      "va": "0x007e5f30"
    },
    {
      "match_basis": [
        "same_subsystem",
        "shared_types:DATA"
      ],
      "package": "PKG-APP-LIFECYCLE-WAVE8",
      "score": 9,
      "symbol": "app_c_cell_mode_strategy_dispose_00e81f30",
      "va": "0x00e81f30"
    },
    {
      "match_basis": [
        "shared_types:DATA"
      ],
      "package": "PKG-SKINNER-SAFE-WAVE10",
      "score": 3,
      "symbol": "skin_painter_job_brush_pass_005182f0",
      "va": "0x005182f0"
    },
    {
      "match_basis": [
        "shared_types:DATA"
      ],
      "package": "PKG-18-UI-SCRIPTING",
      "score": 3,
      "symbol": "FUN_005bf9d0",
      "va": "0x005bf9d0"
    },
    {
      "match_basis": [
        "shared_types:DATA"
      ],
      "package": "PKG-18-UI-SCRIPTING",
      "score": 3,
      "symbol": "FUN_005c0100",
      "va": "0x005c0100"
    },
    {
      "match_basis": [
        "shared_types:DATA"
      ],
      "package": "PKG-18-UI-SCRIPTING",
      "score": 3,
      "symbol": "FUN_005c0380",
      "va": "0x005c0380"
    }
  ],
  "audit_evidence_boundary": "Static mechanics and x86-32 ABI reviewed from live Ghidra; runtime values, concrete owners, and unresolved ports remain gated.",
  "audit_findings": [],
  "audit_status": "clean_after_reviewed_repairs",
  "blocked": false,
  "blockers": [
    "Original-process hook dispatch and receiver state remain runtime-gated."
  ],
  "body_status": "integrated",
  "class_type": "OpaqueAppSystem",
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
        "callsite": "0x007e6080",
        "direction": "out",
        "other": "0x00929bd0",
        "reference_type": "direct-call"
      }
    ],
    "edges_truncated": false,
    "external_callees": [],
    "fan_in": 0,
    "fan_out": 0,
    "manifest_callees": [
      "0x00929bd0"
    ],
    "manifest_callers": [],
    "nearby_reconstructed": [],
    "scc": {
      "id": "scc-0250",
      "size": 1
    },
    "vtable_reference_count": 0
  },
  "evidence_level": "SUPPORTED",
  "globals": [],
  "integration_status": "integrated",
  "name": "app_capp_system_hook_windows_007e6080",
  "normalized_symbol": "app_capp_system_hook_windows_007e6080",
  "observed_mechanics": [
    "{\"allocation_cleanup\": \"No allocation, release, or local cleanup occurs in the assigned body.\", \"call_order\": \"No local call or mutation precedes the tail transfer.\", \"receiver_use\": \"The wrapper passes the incoming ECX receiver to the opaque tail target.\"}"
  ],
  "ownership": {
    "claimability": "do_not_claim",
    "handoff_packages": [
      "PKG-APP-LIFECYCLE-WAVE7"
    ],
    "manifest": {
      "record": null,
      "worker_ownership": null
    },
    "package": "PKG-APP-LIFECYCLE-WAVE7",
    "queue_state": null
  },
  "package": "PKG-APP-LIFECYCLE-WAVE7",
  "reconstructed": true,
  "review_status": "approved_after_parallel_review",
  "runtime": {
    "blocking_reason": null,
    "gates": [
      "Observe the original global object at 0x01668eec, its vtable +0x04 implementation, and the concrete hook receiver before promoting ownership or platform semantics."
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
    "file": "src/reconstruction/pkg_app_lifecycle_wave7/app_lifecycle_wave7.cpp",
    "files": [
      "src/reconstruction/pkg_app_lifecycle_wave7",
      "src/reconstruction/pkg_app_lifecycle_wave7/app_lifecycle_wave7.cpp",
      "src/reconstruction/pkg_app_lifecycle_wave7/app_lifecycle_wave7.hpp",
      "src/reconstruction/pkg_app_lifecycle_wave7/app_lifecycle_wave7_model_test.cpp"
    ],
    "handoffs": [
      "reconstruction/integrated/batch-2026-09-25-wave7/handoff.json"
    ],
    "metadata": [
      "reconstruction/metadata/pkg-app-lifecycle-wave7/007e6080.json"
    ],
    "provenance": [
      "ghidra:decompile_function",
      "ghidra:disassemble_function",
      "ghidra:get_function_callees",
      "ghidra:get_function_callers",
      "reconstruction/metadata/pkg-app-lifecycle-wave7/007e6080.json"
    ]
  },
  "status": "reconstructed",
  "subsystem": "App.Lifecycle",
  "triage": null,
  "types": [
    "DATA",
    "OpaqueAppSystem",
    "void",
    "void at the imported method boundary"
  ],
  "unresolved_questions": [
    "Concrete global object and vtable owner at 0x01668eec",
    "Concrete implementation selected by the vtable +0x04 slot",
    "Runtime receiver and call reachability"
  ],
  "va": "0x007e6080",
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
  "body_end": "007e6084",
  "body_span_bytes": 5,
  "body_start": "007e6080",
  "callees": [
    "FUN_00929bd0"
  ],
  "callers": [],
  "classification": "thunk",
  "dispatch": null,
  "entry_point": "007e6080",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "App::cAppSystem::HookWindows",
  "namespace": "App",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 1,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "cAppSystem *"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "void",
  "return_type_resolved": true,
  "rva": "0x3e6080",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "void App::cAppSystem::HookWindows(cAppSystem * this)",
  "size_bytes": 5,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x007e6080",
  "vtables": {
    "referenced_by_vtables": [
      "0x01413acc",
      "0x01413b48"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "01413b5c"
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
  "file": "src/reconstruction/pkg_app_lifecycle_wave7/app_lifecycle_wave7.cpp",
  "files": [
    "src/reconstruction/pkg_app_lifecycle_wave7/app_lifecycle_wave7.cpp",
    "src/reconstruction/pkg_app_lifecycle_wave7/app_lifecycle_wave7.hpp",
    "src/reconstruction/pkg_app_lifecycle_wave7/app_lifecycle_wave7_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave7/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-app-lifecycle-wave7/007e6080.json"
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
    "Observe the original global object at 0x01668eec, its vtable +0x04 implementation, and the concrete hook receiver before promoting ownership or platform semantics."
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
  "DATA",
  "OpaqueAppSystem",
  "void",
  "void at the imported method boundary"
]
```

## vtables

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## Conflicts

```json
[]
```
