# Reconstruction context 0x0093b5a0

- Status: `partial`
- Content SHA-256: `ad3aadf202c4a0de699a0e2f8444b248de36c3c665cc5db048066999e1f003b3`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x0093b5a0",
  "phase": "reconstruction",
  "target": "0x0093b5a0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "StreamChild",
  "name": "stream_child_teardown_0093b5a0",
  "package": "wave6-serialization-persistence",
  "subsystem": "IO.StreamChild",
  "va": "0x0093b5a0"
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
  "content_sha256": "658c6d7c25aa7cbef2372d1d4e225664fd057501d9425dfd7a566ff44a77fca3",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x0093b5a0 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "__thiscall",
  "receiver_register": "ECX",
  "return_type": "void",
  "stack_arguments": [],
  "termination": "plain RET"
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
      "va": "0x006ab120"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x008d6ed0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0091c640"
    },
    {
      "name": "stream_child_close_and_maybe_delete_0093b610",
      "reconstructed": true,
      "va": "0x0093b610"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e4c130"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0120ddd8"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x006ab2f5",
      "direction": "in",
      "other": "0x006ab120",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x008d71d5",
      "direction": "in",
      "other": "0x008d6ed0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0091c85d",
      "direction": "in",
      "other": "0x0091c640",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0093b613",
      "direction": "in",
      "other": "0x0093b610",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e4c1ff",
      "direction": "in",
      "other": "0x00e4c130",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e4c2f7",
      "direction": "in",
      "other": "0x00e4c130",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0120dddb",
      "direction": "in",
      "other": "0x0120ddd8",
      "reference_type": "direct-call"
    },
    {
      "call
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "IStream",
    "StreamChild",
    "StreamChild*",
    "StreamChildLifecycleServices",
    "StreamChildTeardownWindow",
    "void"
  ],
  "vtables": [
    "vtable:0x013f3a68"
  ]
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
      "gate-stream-child-parent-block-and-allocator-lifecycle"
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
      "va": "0x006ab120"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x008d6ed0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0091c640"
    },
    {
      "name": "stream_child_close_and_maybe_delete_0093b610",
      "reconstructed": true,
      "va": "0x0093b610"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e4c130"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0120ddd8"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x006ab2f5",
      "direction": "in",
      "other": "0x006ab120",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x008d71d5",
      "direction": "in",
      "other": "0x008d6ed0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0091c85d",
      "direction": "in",
      "other": "0x0091c640",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0093b613",
      "direction": "in",
      "other": "0x0093b610",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e4c1ff",
      "direction": "in",
      "other": "0x00e4c130",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e4c2f7",
      "direction": "in",
      "other": "0x00e4c130",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0120dddb",
      "direction": "in",
      
[TRUNCATED]
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
      "shared_types:StreamChild,StreamChild*,StreamChildLifecycleServices",
      "same_calling_convention",
      "direct_xref_neighbor"
    ],
    "package": "wave6-serialization-persistence",
    "score": 33,
    "symbol": "stream_child_close_and_maybe_delete_0093b610",
    "va": "0x0093b610"
  },
  {
    "match_basis": [
      "same_package",
      "same_calling_convention"
    ],
    "package": "wave6-serialization-persistence",
    "score": 10,
    "symbol": "memory_stream_initialize_0093bd50",
    "va": "0x0093bd50"
  },
  {
    "match_basis": [
      "same_package",
      "same_calling_convention"
    ],
    "package": "wave6-serialization-persistence",
    "score": 10,
    "symbol": "memory_stream_set_position_0093c0c0",
    "va": "0x0093c0c0"
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
    "symbol": "model_par
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/wave6_serialization_persistence/stream_lifecycle.cpp",
  "files": [
    "src/reconstruction/wave6_serialization_persistence/stream_lifecycle.cpp",
    "src/reconstruction/wave6_serialization_persistence/stream_lifecycle.hpp",
    "src/reconstruction/wave6_serialization_persistence/stream_lifecycle_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/wave6-serialization-persistence/0093b5a0.json"
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
    "allocator implementation and thread safety",
    "concrete StreamChild subtype",
    "flush failure effects",
    "gate-stream-child-parent-block-and-allocator-lifecycle",
    "parent and block ownership"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave6/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave6-serialization-persistence/0093b5a0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/wave6_serialization_persistence/stream_lifecycle.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/wave6_serialization_persistence/stream_lifecycle.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/wave6_serialization_persistence/stream_lifecycle_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave6-serialization-persistence/0093b5a0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/wave6_serialization_persistence/stream_lifecycle.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/wave6_serialization_persistence/stream_lifecycle.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "
[TRUNCATED]
```
