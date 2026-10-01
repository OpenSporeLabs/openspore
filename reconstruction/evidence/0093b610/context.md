# Reconstruction context 0x0093b610

- Status: `partial`
- Content SHA-256: `1c6bbe7babbabe78b6bc2a67ea4bd59b3a09ae1b76919743a5e271ad84e445c4`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x0093b610",
  "phase": "reconstruction",
  "target": "0x0093b610"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "StreamChild",
  "name": "StreamChild_Close",
  "package": "wave6-serialization-persistence",
  "subsystem": "IO.StreamChild",
  "va": "0x0093b610"
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
  "content_sha256": "d714dfd2e50c0cc078fd24f3968986641bb81c860e183cb02461f67385c80c0f",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x0093b610 failed: Decompilation did not complete. Reason: ",
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
  "return_register": "EAX",
  "return_type": "StreamChild*",
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "delete_flags",
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
  "callees": [
    {
      "name": "stream_child_teardown_0093b5a0",
      "reconstructed": true,
      "va": "0x0093b5a0"
    }
  ],
  "callers": [],
  "edge_rows": [
    {
      "callsite": "0x0093b613",
      "direction": "out",
      "other": "0x0093b5a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0093b620",
      "direction": "out",
      "other": "0x00f47380",
      "reference_type": "direct-call"
    }
  ],
  "external_callees": []
}
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "StreamChild",
    "StreamChild*",
    "StreamChildLifecycleServices",
    "uint32_t"
  ],
  "vtables": [
    "vtable:0x0093b610",
    "vtable:0x0143eaac"
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
      "gate-stream-child-virtual-teardown-and-delete"
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
  "callees": [
    {
      "name": "stream_child_teardown_0093b5a0",
      "reconstructed": true,
      "va": "0x0093b5a0"
    }
  ],
  "callees_truncated": false,
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x0093b613",
      "direction": "out",
      "other": "0x0093b5a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0093b620",
      "direction": "out",
      "other": "0x00f47380",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 0,
  "fan_out": 1,
  "manifest_callees": [
    "0x0093b5a0",
    "0x00f47380"
  ],
  "manifest_callers": [
    "vtable_xref_0143eaac"
  ],
  "nearby_reconstructed": [
    "0x0093b5a0"
  ],
  "scc": {
    "id": "scc-0285",
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
      "shared_types:StreamChild,StreamChild*,StreamChildLifecycleServices",
      "same_calling_convention",
      "direct_xref_neighbor"
    ],
    "package": "wave6-serialization-persistence",
    "score": 33,
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
      "shared_vtable:vtable:0x0143eaac"
    ],
    "package": "PKG-FILE-STREAM-WAVE6",
    "score": 4,
    "symbol": "pkg_file_stream_wave6_stream_buffer_delegate_0093ae60",
    "va": "0x0093ae60"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x0143eaac"
    ],
    "package": "PKG-FILE-STREAM-WAVE6",
    "score": 4,
    "symbol": "pkg_file_stream_wave6_stream_child_delegate_0093b6d0",
    "va": "0x0093b6d0"
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
    "package": "PKG-APP-SAFE-WAVE11"
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
    "reconstruction/metadata/wave6-serialization-persistence/0093b610.json"
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
    "active vtable owner",
    "delete-wrapper pairing",
    "gate-stream-child-virtual-teardown-and-delete",
    "meaning of delete bits 1 through 31"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave6/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave6-serialization-persistence/0093b610.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/wave6_serialization_persistence/stream_lifecycle.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/wave6_serialization_persistence/stream_lifecycle.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/wave6_serialization_persistence/stream_lifecycle_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave6-serialization-persistence/0093b610.json",
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
