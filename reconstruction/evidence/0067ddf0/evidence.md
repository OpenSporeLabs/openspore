# Evidence 0x0067ddf0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `7d5425f51a827789fd53012dc15d43e6604a10c87128f1be534b9477233606bd`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__cdecl",
  "ordinary_stack_argument_slots": 0,
  "return_note": "opaque pointer word",
  "return_register": "EAX",
  "return_width_bytes": 4,
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
    "receiver": false,
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "pointer_like_in_EAX",
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "no_discriminator: no stack-argument read and no positive receiver evidence"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "9209878cda50e63bbc55bddd7c3ae94d409472a7a2e6c6c885265e022bd3a1f5",
  "conventions": {
    "ambiguities": [],
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
    "ghidra_parameter_count": 0,
    "persisted": "no_information",
    "persisted_calling_convention": "__cdecl"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0002"
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
      "claim": "ECX is never read in any form, so there is no register receiver",
      "confidence": "OBSERVED",
      "id": "R2",
      "value": {
        "present": false
      }
    },
    {
      "based_on": [
        "obs-0002"
      ],
      "claim": "the function is byte-identical under all four conventions",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0002"
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
        "obs-0002"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0002"
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
      "at": "0x0067ddf0",
      "definite": true,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,[0x015fd8f0]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x0067ddf5",
      "form": "RET",
      "id": "obs-0002",
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
    "va": "0x0067ddf0"
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

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": null,
    "reconstructed": false,
    "va": "0x006f24a0"
  }
]
```

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
      "address": "0067ddf0",
      "instruction": "MOV EAX,[0x015fd8f0]"
    },
    {
      "address": "0067ddf5",
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
    "calling_convention": "__cdecl",
    "ordinary_stack_argument_slots": 0,
    "return_note": "opaque pointer word",
    "return_register": "EAX",
    "return_width_bytes": 4,
    "stack_cleanup_bytes": 0
  },
  "analogues": [
    {
      "match_basis": [
        "same_package",
        "same_subsystem",
        "shared_types:READ,WRITE,Wave6ServiceRoots,opaque pointer word",
        "same_calling_convention"
      ],
      "package": "PKG-06-WAVE6-APP-MANAGERS",
      "score": 25,
      "symbol": "App_IStateManager_Get_0067dce0",
      "va": "0x0067dce0"
    },
    {
      "match_basis": [
        "same_subsystem",
        "same_calling_convention"
      ],
      "package": "WAVE6-ENGINE-RUNTIME",
      "score": 8,
      "symbol": "app_config_manager_get_0067dcf0",
      "va": "0x0067dcf0"
    },
    {
      "match_basis": [
        "same_package"
      ],
      "package": "PKG-06-WAVE6-APP-MANAGERS",
      "score": 8,
      "symbol": "MessageManagerCleanupStorageWalker_008841f0",
      "va": "0x008841f0"
    },
    {
      "match_basis": [
        "same_subsystem"
      ],
      "package": "PKG-APP-SERVICES-SAFE-WAVE11",
      "score": 6,
      "symbol": "service_005f9230",
      "va": "0x005f9230"
    },
    {
      "match_basis": [
        "same_subsystem"
      ],
      "package": "PKG-APP-SERVICES-SAFE-WAVE11",
      "score": 6,
      "symbol": "service_005f9310",
      "va": "0x005f9310"
    },
    {
      "match_basis": [
        "same_subsystem"
      ],
      "package": "PKG-APP-SERVICES-SAFE-WAVE11",
      "score": 6,
      "symbol": "service_005fa8d0",
      "va": "0x005fa8d0"
    },
    {
      "match_basis": [
        "same_subsystem"
      ],
      "package": "PKG-APP-SERVICES-SAFE-WAVE11",
      "score": 6,
      "symbol": "service_005fc330",
      "va": "0x005fc330"
    },
    {
      "match_basis": [
        "same_subsystem"
      ],
      "package": "PKG-APP-SERVICES-SAFE-WAVE11",
      "score": 6,
      "symbol": "service_0060ee90",
      "va": "0x0060ee90"
    }
  ],
  "audit_evidence_boundary": "The distinct absolute slot read and unchanged pointer return are exact; the imported subtype, publisher, ownership, and runtime publication remain unresolved.",
  "audit_findings": [],
  "audit_status": "pass_after_repair",
  "blocked": false,
  "blockers": [],
  "body_status": "integrated",
  "class_type": "OpaquePropManager",
  "cluster": null,
  "confidence": 0.96,
  "dependencies": {
    "callees": [],
    "callees_truncated": false,
    "callers": [
      {
        "name": null,
        "reconstructed": false,
        "va": "0x006f24a0"
      }
    ],
    "callers_truncated": false,
    "data_reference_count": 0,
    "edges": [
      {
        "callsite": "0x006f24c0",
        "direction": "in",
        "other": "0x006f24a0",
        "reference_type": "direct-call"
      }
    ],
    "edges_truncated": false,
    "external_callees": [],
    "fan_in": 1,
    "fan_out": 0,
    "manifest_callees": [],
    "manifest_callers": [
      "direct_caller_functions_1",
      "function_xrefs_3"
    ],
    "nearby_reconstructed": [],
    "scc": {
      "id": "scc-0186",
      "size": 1
    },
    "vtable_reference_count": 0
  },
  "evidence_level": "OBSERVED",
  "globals": [
    "global:0x015fd8f0",
    "global:g_wave6_service_roots.prop_manager_015fd8f0"
  ],
  "integration_status": "integrated",
  "name": "App_IPropManager_Get_0067ddf0",
  "normalized_symbol": "App_IPropManager_Get_0067ddf0",
  "observed_mechanics": [
    "cdecl zero-argument frame",
    "read absolute slot 0x015fd8f0",
    "return EAX unchanged",
    "no alias to the state-manager slot",
    "no guard, fallback, mutation, or reference operation"
  ],
  "ownership": {
    "claimability": "do_not_claim",
    "handoff_packages": [
      "PKG-06-WAVE6-APP-MANAGERS"
    ],
    "manifest": {
      "record": null,
      "worker_ownership": null
    },
    "package": "PKG-06-WAVE6-APP-MANAGERS",
    "queue_state": null
  },
  "package": "PKG-06-WAVE6-APP-MANAGERS",
  "reconstructed": true,
  "review_status": "approved",
  "runtime": {
    "blocking_reason": null,
    "gates": [
      "gate-property-manager-slot-publication"
    ],
    "validated": 0
  },
  "runtime_gated": true,
  "runtime_validated": 0,
  "semantic": null,
  "semantic_status": "static_property_manager_slot_accessor_runtime_publication_unknown",
  "services": [],
  "source": {
    "decomp": null,
    "file": "src/reconstruction/wave6_app_managers/service_accessors_cleanup.cpp",
    "files": [
      "reconstruction/staging/wave6-app-managers/service_accessors_cleanup_model_test.cpp",
      "src/reconstruction/wave6_app_managers/service_accessors_cleanup.cpp"
    ],
    "handoffs": [
      "reconstruction/integrated/batch-2026-09-25-wave6/handoff.json"
    ],
    "metadata": [
      "reconstruction/metadata/wave6-app-managers/0067ddf0.json"
    ],
    "provenance": [
      "reconstruction/metadata/wave6-app-managers/0067ddf0.json"
    ]
  },
  "status": "reconstructed",
  "subsystem": "App.Services",
  "triage": null,
  "types": [
    "OpaquePropManager",
    "OpaquePropManager*",
    "READ",
    "WRITE",
    "Wave6ServiceRoots",
    "opaque pointer word",
    "undefined4"
  ],
  "unresolved_questions": [
    "How does the property manager relate to the App service and state-manager slot?",
    "Is the returned manager borrowed, retained, or invalidated during lifecycle transitions?",
    "What concrete IPropManager subtype and vtable are stored in the slot?",
    "Which startup path publishes or replaces DAT_015fd8f0?",
    "concrete IPropManager subtype",
    "returned manager lifetime",
    "slot publisher and replacement order"
  ],
  "va": "0x0067ddf0",
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
  "body_end": "0067ddf5",
  "body_span_bytes": 6,
  "body_start": "0067ddf0",
  "callees": [],
  "callers": [
    "FUN_006f24a0"
  ],
  "classification": "stub",
  "dispatch": null,
  "entry_point": "0067ddf0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "App::IPropManager::Get",
  "namespace": "App",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "IPropManager *",
  "return_type_resolved": true,
  "rva": "0x27ddf0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "IPropManager * App::IPropManager::Get(void)",
  "size_bytes": 6,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x0067ddf0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 3,
  "xrefs": [
    {
      "from": "006f24c0"
    },
    {
      "from": "006e746e"
    },
    {
      "from": "007eacf2"
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
  "global:0x015fd8f0",
  "global:g_wave6_service_roots.prop_manager_015fd8f0"
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/wave6_app_managers/service_accessors_cleanup.cpp",
  "files": [
    "reconstruction/staging/wave6-app-managers/service_accessors_cleanup_model_test.cpp",
    "src/reconstruction/wave6_app_managers/service_accessors_cleanup.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/wave6-app-managers/0067ddf0.json"
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
    "gate-property-manager-slot-publication"
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
  "OpaquePropManager",
  "OpaquePropManager*",
  "READ",
  "WRITE",
  "Wave6ServiceRoots",
  "opaque pointer word",
  "undefined4"
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
