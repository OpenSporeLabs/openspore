# Reconstruction context 0x0093bd50

- Status: `partial`
- Content SHA-256: `19c1c0c49a72800533bafeda401ef8120db3d6e5035178bba772e578acea88fb`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x0093bd50",
  "phase": "reconstruction",
  "target": "0x0093bd50"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "MemoryStream",
  "name": "memory_stream_initialize_0093bd50",
  "package": "wave6-serialization-persistence",
  "subsystem": "IO.MemoryStream",
  "va": "0x0093bd50"
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
  "content_sha256": "6e0c00c46c1c5a99455e48b33503ead59e20ef07efe14ee5ec04e77b45f3426b",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x0093bd50 failed: Decompilation did not complete. Reason: ",
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
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "ignored_word",
      "observed_use": "none",
      "type": "uint32_t",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 4,
  "termination": "RET 0x4"
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
      "va": "0x006b17a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006c09c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006c0b20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006c0c40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006c0db0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007ebce0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x008dcc80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x008dcdc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x008dcea0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x008dd0d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x008fdd10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00900990"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00946dc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00947d50"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x006b17e9",
      "direction": "in",
      "other": "0x006b17a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006c0a55",
      "direction": "in",
      "other": "0x006c09c0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006c0baf",
 
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "MemoryStream",
    "MemoryStream*",
    "MemoryStreamVtable",
    "uint32_t",
    "void"
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
      "gate-memory-stream-initialization-and-allocation-lifecycle"
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
      "va": "0x006b17a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006c09c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006c0b20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006c0c40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006c0db0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007ebce0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x008dcc80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x008dcdc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x008dcea0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x008dd0d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x008fdd10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00900990"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00946dc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00947d50"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x006b17e9",
      "direction": "in",
      "other": "0x006b17a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006c0a55",
      "direction": "in",
      "other": "0x006c09c0",
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
      "shared_types:MemoryStream,MemoryStream*",
      "same_calling_convention"
    ],
    "package": "wave6-serialization-persistence",
    "score": 27,
    "symbol": "memory_stream_set_position_0093c0c0",
    "va": "0x0093c0c0"
  },
  {
    "match_basis": [
      "same_package",
      "same_calling_convention"
    ],
    "package": "wave6-serialization-persistence",
    "score": 10,
    "symbol": "stream_child_teardown_0093b5a0",
    "va": "0x0093b5a0"
  },
  {
    "match_basis": [
      "same_package",
      "same_calling_convention"
    ],
    "package": "wave6-serialization-persistence",
    "score": 10,
    "symbol": "stream_child_close_and_maybe_delete_0093b610",
    "va": "0x0093b610"
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
    "reconstruction/metadata/wave6-serialization-persistence/0093bd50.json"
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
    "allocation and secondary-vtable caller behavior",
    "gate-memory-stream-initialization-and-allocation-lifecycle",
    "runtime resize-factor value",
    "shared-pointer owner"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave6/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave6-serialization-persistence/0093bd50.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/wave6_serialization_persistence/stream_lifecycle.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/wave6_serialization_persistence/stream_lifecycle.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/wave6_serialization_persistence/stream_lifecycle_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave6-serialization-persistence/0093bd50.json",
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
