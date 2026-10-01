# Evidence 0x00926140

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `bed56068a18f2422d1d42c3db56c613c6daf00bb33352a7ccb161351f6191b1e`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "cdecl observed from direct caller",
  "receiver_register": null,
  "return_register": "EAX",
  "return_type": "std::int32_t",
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "allocator",
      "position": 1,
      "type": "Wave6FixedPoolAllocator*",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 4,
  "termination": "RET"
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
    "return_register": "EAX",
    "return_semantics": "pointer_like_in_EAX",
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
    "flow_not_modelled: the linear ESP walk ends at +4, so the listing is not one path",
    "sret_vs_out_param: entry slot 0 is written through a pointer"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate",
    "side": "caller"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [
    {
      "field": "stack_cleanup_bytes",
      "inferred": 0,
      "kind": "inferred_vs_persisted",
      "persisted": 4,
      "resolution_status": "unresolved"
    }
  ],
  "content_sha256": "fa7d1ab7474aa1eb706d1abcd71cc3c54411b19e7e78baa16d23f0d7e5144839",
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
    "ghidra_parameter_count": 3,
    "persisted": "no_information",
    "persisted_calling_convention": "cdecl observed from direct caller"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0009"
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
        "obs-0009"
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
        "obs-0009"
      ],
      "claim": "calling convention is __cdecl: the caller cleans the stack and at least one entry slot is read",
      "confidence": "INFERRED",
      "id": "C9",
      "value": "__cdecl"
    },
    {
      "based_on": [
        "obs-0002"
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
        "obs-0009"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0009"
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
      "at": "0x00926140",
      "count": 1,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "ESP"
    },
    {
      "at": "0x00926140",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0002",
      "index": 0,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00926140",
      "definite": true,
      "id": "obs-0003",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00926144",
      "count": 3,
      "first_use": 1,
      "first_write_index": 0,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_READ",
      "raw": "DEC dword ptr [EAX + 0x18]",
      "reg": "EAX"
    },
    {
      "at": "0x00926147",
      "count": 2,
      "first_use": 2,
      "first_write_index": 3,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00926148",
      "definite": true,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,dword ptr [EAX + 0x18]",
      "reg": "ESI",
      "write_kind": "mem_load"
    },
    {
      "at": "0x0092614c",
      "base": null,
      "disp": 20759260,
      "id": "obs-0007",
      "index": 5,
      "kind": "CALL_INDIRECT",
      "raw": "CALL dword ptr [0x013cc2dc]",
      "via": "memory"
    },
    {
      "at": "0x00926154",
      "id": "obs-0008",
      "index": 7,
      "kind": "REG_RESTORE",
      "raw": "POP ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00926155",
      "form": "RET",
      "id": "obs-0009"
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
    "va": "0x00927a50"
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
  "count": 9,
  "instructions": [
    {
      "address": "00926140",
      "instruction": "MOV EAX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "00926144",
      "instruction": "DEC dword ptr [EAX + 0x18]"
    },
    {
      "address": "00926147",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00926148",
      "instruction": "MOV ESI,dword ptr [EAX + 0x18]"
    },
    {
      "address": "0092614b",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0092614c",
      "instruction": "CALL dword ptr [0x013cc2dc]"
    },
    {
      "address": "00926152",
      "instruction": "MOV EAX,ESI"
    },
    {
      "address": "00926154",
      "instruction": "POP ESI"
    },
    {
      "address": "00926155",
      "instruction": "RET"
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
  "EXT:KERNEL32.DLL::LeaveCriticalSection"
]
```

## function_identity

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "abi": {
    "calling_convention": "cdecl observed from direct caller",
    "receiver_register": null,
    "return_register": "EAX",
    "return_type": "std::int32_t",
    "stack_arguments": [
      {
        "entry_offset": "ESP+0x04",
        "name": "allocator",
        "position": 1,
        "type": "Wave6FixedPoolAllocator*",
        "width_bytes": 4
      }
    ],
    "stack_cleanup_bytes": 4,
    "termination": "RET"
  },
  "analogues": [
    {
      "match_basis": [
        "same_package",
        "same_subsystem",
        "same_class",
        "shared_types:FixedPoolAllocator,Wave6FixedPoolAllocator,Wave6FixedPoolAllocator*",
        "same_calling_convention"
      ],
      "package": "PKG-WAVE6-CONTAINERS-MEMORY",
      "score": 30,
      "symbol": "wave6_fixed_pool_allocator_alloc_00926100",
      "va": "0x00926100"
    },
    {
      "match_basis": [
        "same_package",
        "same_subsystem"
      ],
      "package": "PKG-WAVE6-CONTAINERS-MEMORY",
      "score": 14,
      "symbol": "wave6_reference_00432a50",
      "va": "0x00432a50"
    }
  ],
  "audit_evidence_boundary": "The unchecked receiver, signed decrement, release call order, and post-decrement return are exact; imported Free meaning and runtime pairing remain unresolved.",
  "audit_findings": [],
  "audit_status": "pass_after_repair",
  "blocked": false,
  "blockers": [
    "No original-process runtime trace is available.",
    "The external release call is represented by a package-local port for focused model testing."
  ],
  "body_status": "integrated",
  "class_type": "Wave6FixedPoolAllocator",
  "cluster": null,
  "confidence": 0.95,
  "dependencies": {
    "callees": [],
    "callees_truncated": false,
    "callers": [
      {
        "name": null,
        "reconstructed": false,
        "va": "0x00927a50"
      }
    ],
    "callers_truncated": false,
    "data_reference_count": 0,
    "edges": [
      {
        "callsite": "0x00927bb7",
        "direction": "in",
        "other": "0x00927a50",
        "reference_type": "direct-call"
      },
      {
        "callsite": "0x0092614c",
        "direction": "out",
        "other": "EXT:KERNEL32.DLL::LeaveCriticalSection",
        "reference_type": "external"
      }
    ],
    "edges_truncated": false,
    "external_callees": [
      "EXT:KERNEL32.DLL::LeaveCriticalSection"
    ],
    "fan_in": 1,
    "fan_out": 0,
    "manifest_callees": [
      "LeaveCriticalSection"
    ],
    "manifest_callers": [
      "0x00927a50"
    ],
    "nearby_reconstructed": [],
    "scc": {
      "id": "scc-0279",
      "size": 1
    },
    "vtable_reference_count": 0
  },
  "evidence_level": "OBSERVED",
  "globals": [],
  "integration_status": "integrated",
  "name": "wave6_fixed_pool_allocator_free_00926140",
  "normalized_symbol": "wave6_fixed_pool_allocator_free_00926140",
  "observed_mechanics": [
    "one cdecl stack pointer",
    "no receiver null guard",
    "decrement signed word at receiver+0x18",
    "call LeaveCriticalSection after decrement",
    "return the post-decrement value in EAX"
  ],
  "ownership": {
    "claimability": "do_not_claim",
    "handoff_packages": [
      "PKG-WAVE6-CONTAINERS-MEMORY"
    ],
    "manifest": {
      "record": null,
      "worker_ownership": null
    },
    "package": "PKG-WAVE6-CONTAINERS-MEMORY",
    "queue_state": null
  },
  "package": "PKG-WAVE6-CONTAINERS-MEMORY",
  "reconstructed": true,
  "review_status": "approved",
  "runtime": {
    "blocking_reason": null,
    "gates": [
      "gate-fixed-pool-allocator-critical-section-release"
    ],
    "validated": 0
  },
  "runtime_gated": true,
  "runtime_validated": 0,
  "semantic": null,
  "semantic_status": "static_decrement_release_order_runtime_critical_section_unknown",
  "services": [],
  "source": {
    "decomp": null,
    "file": "src/reconstruction/wave6_containers_memory/containers_memory.cpp",
    "files": [
      "reconstruction/staging/wave6-containers-memory/containers_memory.cpp",
      "reconstruction/staging/wave6-containers-memory/containers_memory.hpp",
      "reconstruction/staging/wave6-containers-memory/containers_memory_model_test.cpp",
      "src/reconstruction/wave6_containers_memory/containers_memory.cpp"
    ],
    "handoffs": [
      "reconstruction/integrated/batch-2026-09-25-wave6/handoff.json"
    ],
    "metadata": [
      "reconstruction/metadata/wave6-containers-memory/00926140.json"
    ],
    "provenance": [
      "reconstruction/metadata/wave6-containers-memory/00926140.json"
    ]
  },
  "status": "reconstructed",
  "subsystem": "Core.Memory",
  "triage": null,
  "types": [
    "FixedPoolAllocator",
    "Wave6FixedPoolAllocator",
    "Wave6FixedPoolAllocator*",
    "Wave6LeaveCriticalSectionPort",
    "std::int32_t"
  ],
  "unresolved_questions": [
    "The concrete critical-section object and runtime caller pairing remain opaque.",
    "The imported Free label and source-level allocator ownership semantics are not independently established.",
    "The later 0x00926340 call in the teardown caller is outside this function.",
    "concrete allocator owner",
    "imported Free label identity",
    "runtime critical-section pairing"
  ],
  "va": "0x00926140",
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
  "body_end": "00926155",
  "body_span_bytes": 22,
  "body_start": "00926140",
  "callees": [
    "LeaveCriticalSection"
  ],
  "callers": [
    "FUN_00927a50"
  ],
  "classification": "wrapper",
  "dispatch": null,
  "entry_point": "00926140",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FixedPoolAllocator::Free",
  "namespace": "FixedPoolAllocator",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 3,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "FixedPoolAllocator *"
    },
    {
      "name": "block",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "void *"
    },
    {
      "name": "size",
      "ordinal": 2,
      "storage": "Stack[0xc]:4",
      "type": "size_t"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "void",
  "return_type_resolved": true,
  "rva": "0x526140",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "void FixedPoolAllocator::Free(FixedPoolAllocator * this, void * block, size_t size)",
  "size_bytes": 22,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00926140",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "00927bb7"
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
  "file": "src/reconstruction/wave6_containers_memory/containers_memory.cpp",
  "files": [
    "reconstruction/staging/wave6-containers-memory/containers_memory.cpp",
    "reconstruction/staging/wave6-containers-memory/containers_memory.hpp",
    "reconstruction/staging/wave6-containers-memory/containers_memory_model_test.cpp",
    "src/reconstruction/wave6_containers_memory/containers_memory.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/wave6-containers-memory/00926140.json"
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
    "gate-fixed-pool-allocator-critical-section-release"
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
  "FixedPoolAllocator",
  "Wave6FixedPoolAllocator",
  "Wave6FixedPoolAllocator*",
  "Wave6LeaveCriticalSectionPort",
  "std::int32_t"
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
