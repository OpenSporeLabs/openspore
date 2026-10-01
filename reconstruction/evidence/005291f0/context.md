# Reconstruction context 0x005291f0

- Status: `partial`
- Content SHA-256: `0963b369791e7830afeac79f9e89614e43910085f41abb28fb1a6b04227d31b9`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x005291f0",
  "phase": "reconstruction",
  "target": "0x005291f0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "Matrix4",
  "name": "graphics_global_state_set_transform_005291f0",
  "package": "WAVE6-PRESENTATION",
  "subsystem": "Graphics.Transform",
  "va": "0x005291f0"
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
  "content_sha256": "1f3d8d089a050416243b0c9a8fb9e9a1a8aad84967334c1b7ef4c4f192e512e1",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x005291f0 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "__cdecl observed",
  "hidden_this_register": null,
  "return_register": null,
  "return_type": "void",
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "matrix",
      "observed_use": "Copies 64 bytes from matrix into the fixed global Matrix4 storage.",
      "position": 1,
      "type": "const Matrix4*",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x08",
      "name": "type",
      "observed_use": "Writes the global transform type before the matrix copy.",
      "position": 2,
      "type": "MatrixType",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 0
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
      "va": "0x00528e90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006eae40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006ee6f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007a8a50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b80ea0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x005291da",
      "direction": "in",
      "other": "0x00528e90",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006eb1ac",
      "direction": "in",
      "other": "0x006eae40",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006eb477",
      "direction": "in",
      "other": "0x006eae40",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006eb641",
      "direction": "in",
      "other": "0x006eae40",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006ee8b8",
      "direction": "in",
      "other": "0x006ee6f0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x007a8b90",
      "direction": "in",
      "other": "0x007a8a50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00b80f54",
      "direction": "in",
      "other": "0x00b80ea0",
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
  "globals": [
    "global:0x016f9528",
    "global:The body directly references 0x016f9528, 0x016f96a0, 0x016fa380, and 0x016fa4f0."
  ],
  "types": [
    "Matrix4",
    "MatrixType",
    "const Matrix4*",
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
      "gate-graphics-transform-global-publication"
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
      "va": "0x00528e90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006eae40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006ee6f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007a8a50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b80ea0"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x005291da",
      "direction": "in",
      "other": "0x00528e90",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006eb1ac",
      "direction": "in",
      "other": "0x006eae40",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006eb477",
      "direction": "in",
      "other": "0x006eae40",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006eb641",
      "direction": "in",
      "other": "0x006eae40",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006ee8b8",
      "direction": "in",
      "other": "0x006ee6f0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x007a8b90",
      "direction": "in",
      "other": "0x007a8a50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00b80f54",
      "direction": "in",
      "other": "0x00b80ea0",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "
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
      "same_subsystem"
    ],
    "package": "WAVE6-PRESENTATION",
    "score": 14,
    "symbol": "transform_pre_transform_by_0040ccb0",
    "va": "0x0040ccb0"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "WAVE6-PRESENTATION",
    "score": 8,
    "symbol": "renderware_mesh_set_indices_count_011f96e0",
    "va": "0x011f96e0"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "WAVE6-PRESENTATION",
    "score": 8,
    "symbol": "renderware_mesh_set_index_buffer_011f9710",
    "va": "0x011f9710"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/wave6_presentation/presentation_boundary.cpp",
  "files": [
    "src/reconstruction/wave6_presentation/presentation_boundary.cpp",
    "src/reconstruction/wave6_presentation/presentation_boundary.hpp",
    "src/reconstruction/wave6_presentation/presentation_boundary_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/wave6-presentation/005291f0.json"
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
    "What concrete MatrixType values are valid at runtime?",
    "When are the graphics globals initialized and published?",
    "Which runtime object owns the fixed global transform state?",
    "concrete graphics-state owner",
    "gate-graphics-transform-global-publication",
    "global initialization and lifetime",
    "valid MatrixType values"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave6/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave6-presentation/005291f0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/wave6_presentation/presentation_boundary.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/wave6_presentation/presentation_boundary.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/wave6_presentation/presentation_boundary_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave6-presentation/005291f0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/wave6_presentation/presentation_boundary.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/wave6_presentation/presentation_boundary.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/wave6_pres
[TRUNCATED]
```
