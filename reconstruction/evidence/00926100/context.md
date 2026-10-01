# Reconstruction context 0x00926100

- Status: `partial`
- Content SHA-256: `584b2333ad03a28842abe281431ca90a3bb4a2e9d79259b8cf567303bb4b7f32`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00926100",
  "phase": "reconstruction",
  "target": "0x00926100"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "Wave6FixedPoolAllocator",
  "name": "wave6_fixed_pool_allocator_alloc_00926100",
  "package": "PKG-WAVE6-CONTAINERS-MEMORY",
  "subsystem": "Core.Memory",
  "va": "0x00926100"
}
```

## 03_current_status

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "blocked": false,
  "reconstructed": true,
  "runtime_gated": true,
  "runtime_validated": 0,
  "status": "reconstructed"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "fef16f4cca7b71b1e34edb4d0e1c6b91b8243b9726871d7361e28f830677ac18",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00926100 failed: Decompilation did not complete. Reason: ",
      "mode": "LIVE",
      "status": "unavailable"
    }
  ],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `missing`
- Provenance: ``

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "cdecl observed from direct caller",
  "receiver_register": null,
  "return_register": "EAX",
  "return_type": "void*",
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

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x009274d0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x009274f1",
      "direction": "in",
      "other": "0x009274d0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00926111",
      "direction": "out",
      "other": "EXT:KERNEL32.DLL::InitializeCriticalSectionAndSpinCount",
      "reference_type": "external"
    }
  ],
  "external_callees": [
    "EXT:KERNEL32.DLL::InitializeCriticalSectionAndSpinCount"
  ]
}
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "FixedPoolAllocator",
    "Wave6FixedPoolAllocator",
    "Wave6FixedPoolAllocator*",
    "Wave6InitializeCriticalSectionPort",
    "void*"
  ],
  "vtables": []
}
```

## 09_state_event_relationships

- State: `present`
- Provenance: `knowledgegraph/research/semantic-decomp.json, reconstruction/knowledge/index.json`

```json
{
  "runtime": {
    "blocking_reason": null,
    "gates": [
      "gate-fixed-pool-allocator-critical-section-initialization"
    ],
    "validated": 0
  },
  "semantic": {}
}
```

## 10_dependencies

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x009274d0"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x009274f1",
      "direction": "in",
      "other": "0x009274d0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00926111",
      "direction": "out",
      "other": "EXT:KERNEL32.DLL::InitializeCriticalSectionAndSpinCount",
      "reference_type": "external"
    }
  ],
  "edges_truncated": false,
  "external_callees": [
    "EXT:KERNEL32.DLL::InitializeCriticalSectionAndSpinCount"
  ],
  "fan_in": 1,
  "fan_out": 0,
  "manifest_callees": [
    "InitializeCriticalSectionAndSpinCount"
  ],
  "manifest_callers": [
    "0x009274d0"
  ],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0278",
    "size": 1
  },
  "vtable_reference_count": 0
}
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
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
    "symbol": "wave6_fixed_pool_allocator_free_00926140",
    "va": "0x00926140"
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
  },
  {
    "match_basis": [
      "shared_types:void*"
    ],
    "package": "PKG-APP-SAFE-WAVE11",
    "score": 3,
    "symbol": "property_record_assign_pair_004279d0",
    "va": "0x004279d0"
  },
  {
    "match_basis": [
      "shared_types:void*"
    ],
    "package": "PKG-PALETTE-SAFE-WAVE11",
    "score": 3,
    "symbol": "palette_safe_wave11_fill_node_array_005c7ff0",
    "va": "0x005c7ff0"
  },
  {
    "match_basis": [
      "shared_types:void*"
    ],
    "package": "PKG-APP-SERVICES-SAFE-WAVE11",
    "score": 3,
    "symbol": "service_005fa8d0",
    "va": "0x005fa8d0"
  },
  {
    "match_basis": [
      "shared_types:void*"
    ],
    "package": "PKG-APP-SERVICES-SAFE-WAVE11",
    "score": 3,
    "symbol": "service_0060ee90",
    "va": "0x0060ee90"
  },
  {
    "match_basis": [
      "shared_types:void*"
    ],
    "package": "pkg-swarm-w1-00641fd0",
    "score": 3,
    "symbol": "sporepedia_cached_handle_00641fd0",
    "va": "0x00641fd0"
  },
  {
    "match_basis": [
      "shared_types:void*"
   
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
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
    "reconstruction/metadata/wave6-containers-memory/00926100.json"
  ]
}
```

## 13_semantic_hypotheses

- State: `missing`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

## 14_conflicts_questions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json, knowledgegraph/research/semantic-decomp.json`

```json
{
  "conflicts": [],
  "unresolved_questions": [
    "The caller's later EnterCriticalSection and active-count increment are separate operations and are not folded into this function.",
    "The concrete FixedPoolAllocator owner and the runtime critical-section state remain outside the local body.",
    "The imported Alloc label may not be the source-level method name.",
    "concrete allocator owner",
    "gate-fixed-pool-allocator-critical-section-initialization",
    "imported Alloc label identity",
    "runtime critical-section state"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave6/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave6-containers-memory/00926100.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave6-containers-memory/containers_memory.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave6-containers-memory/containers_memory.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave6-containers-memory/containers_memory_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/wave6_containers_memory/containers_memory.cpp', 'source_class': 'committed_artifact'}`

```json
{
  "provenance": [
    {
      "mode": "derived",
      "ref": "ephemeral reconstruction_knowledge.build_index",
      "source_class": "generated_index"
    },
    {
      "mode": "derived",
      "ref": "tools/reconstruction_tooling/abi_infer.py",
      "source_class": "derived"
    },
    {
      "mode": "live",
      "ref": "GhidraMCP /disassemble_function",
      "source_class": "ghidra"
    },
    {
      "mode": "live",
      "ref": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
      "source_class": "ghidra"
    },
    {
      "mode": "persisted",
      "ref": "knowledgegraph/research/source-reconstruction-manifest.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "knowledgegraph/triage/queue-f0e310e0-v6.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/integrated/batch-2026-09-25-wave6/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/wave6-containers-memory/00926100.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave6-containers-memory/containers_memory.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave6-containers-memory/containers_memory.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction
[TRUNCATED]
```
