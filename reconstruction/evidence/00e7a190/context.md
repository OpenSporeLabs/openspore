# Reconstruction context 0x00e7a190

- Status: `partial`
- Content SHA-256: `28f1c998444751e996d9e3de7d83036affd4d91f27e9f9dc974939b45e1ff008`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00e7a190",
  "phase": "reconstruction",
  "target": "0x00e7a190"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "None",
  "name": "cell_behavior_dispatch_00e7a190",
  "package": "PKG-06C-CELL-BEHAVIOR-DISPATCH",
  "subsystem": "Simulator.Cell.BehaviorDispatch",
  "va": "0x00e7a190"
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
  "content_sha256": "571109c7c062cb6ffade3be590535c737bc318cbf1bf8ed96876192098e0796e",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00e7a190 failed: Decompilation did not complete. Reason: ",
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
  "architecture": "x86-32",
  "convention": "custom register-and-stack convention; no standard Ghidra prototype is assigned",
  "return": "void-like; all visible exits use RET without a target-specific return-value contract",
  "stack_cleanup_bytes": 4
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "cell_ai_select_profile_00e52910",
      "reconstructed": true,
      "va": "0x00e52910"
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e7c8c0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00e7ca47",
      "direction": "in",
      "other": "0x00e7c8c0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7a252",
      "direction": "out",
      "other": "0x00e52910",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7a283",
      "direction": "out",
      "other": "0x00e52910",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7a29e",
      "direction": "out",
      "other": "0x00e52910",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7a31b",
      "direction": "out",
      "other": "0x00e52910",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7a294",
      "direction": "out",
      "other": "0x00e67c40",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7a30b",
      "direction": "out",
      "other": "0x00e6f5b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7a2c9",
      "direction": "out",
      "other": "0x00e6f800",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7a3a7",
      "direction": "out",
      "other": "0x00e6f990",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7a3ef",
      "direction": "out",
      "other": "0x00e6fbb0",
     
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [
    "global:0x00e7a225",
    "global:0x00e7a2a6",
    "global:0x016b3c04"
  ],
  "types": [
    "NativeCallContext",
    "NativePorts&",
    "None",
    "ObservedCellCellResource",
    "ObservedCellCellResource*",
    "ObservedCellObjectData",
    "ObservedCellObjectData*",
    "PKG-06C-CELL-BEHAVIOR-DISPATCH::NativePorts",
    "float"
  ],
  "vtables": [
    "vtable:0x00e7a45c"
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
      "gate-cell-behavior-dispatch"
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
      "name": "cell_ai_select_profile_00e52910",
      "reconstructed": true,
      "va": "0x00e52910"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e7c8c0"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00e7ca47",
      "direction": "in",
      "other": "0x00e7c8c0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7a252",
      "direction": "out",
      "other": "0x00e52910",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7a283",
      "direction": "out",
      "other": "0x00e52910",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7a29e",
      "direction": "out",
      "other": "0x00e52910",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7a31b",
      "direction": "out",
      "other": "0x00e52910",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7a294",
      "direction": "out",
      "other": "0x00e67c40",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7a30b",
      "direction": "out",
      "other": "0x00e6f5b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7a2c9",
      "direction": "out",
      "other": "0x00e6f800",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7a3a7",
      "direction": "out",
      "other": "0x00e6f990",
      "reference_type": "direct-call"
    },
    {
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
      "same_class",
      "shared_types:None,ObservedCellCellResource",
      "direct_xref_neighbor"
    ],
    "package": "PKG-06A-CELL-AI-SELECTION",
    "score": 14,
    "symbol": "cell_ai_select_profile_00e52910",
    "va": "0x00e52910"
  },
  {
    "match_basis": [
      "same_class",
      "shared_types:None"
    ],
    "package": "PKG-11-H2-ROOT-ACCESSORS",
    "score": 8,
    "symbol": "root_accessor_00b3d3b0",
    "va": "0x00b3d3b0"
  },
  {
    "match_basis": [
      "same_class",
      "shared_types:None"
    ],
    "package": "PKG-11-H2-ROOT-ACCESSORS",
    "score": 8,
    "symbol": "root_accessor_00b3d3e0",
    "va": "0x00b3d3e0"
  },
  {
    "match_basis": [
      "same_class",
      "shared_types:None"
    ],
    "package": "PKG-11-H2-ROOT-ACCESSORS",
    "score": 8,
    "symbol": "root_accessor_00b3d3f0",
    "va": "0x00b3d3f0"
  },
  {
    "match_basis": [
      "same_class",
      "shared_types:None"
    ],
    "package": "PKG-11-H2-ROOT-ACCESSORS",
    "score": 8,
    "symbol": "root_accessor_00b3d430",
    "va": "0x00b3d430"
  },
  {
    "match_basis": [
      "same_class",
      "shared_types:None"
    ],
    "package": "PKG-13-E3-EMPIRE-STATE-WAVE2",
    "score": 8,
    "symbol": "SpeciesProfileSelector_00c30cc0",
    "va": "0x00c30cc0"
  },
  {
    "match_basis": [
      "same_class",
      "shared_types:None"
    ],
    "package": "PKG-13-E3-EMPIRE-STATE-WAVE2",
    "score": 8,
    "symbol": "ArchetypeRelationshipsID_00c30e20",
    "va": "0x00c30e20"
  },
  {
    "match_basis": [
      "same_class",
      "shared_types:None
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg06c_cell_behavior_dispatch/cell_behavior_dispatch.cpp",
  "files": [
    "reconstruction/staging/pkg06c-cell-behavior-dispatch/cell_behavior_dispatch.cpp",
    "reconstruction/staging/pkg06c-cell-behavior-dispatch/cell_behavior_dispatch.hpp",
    "reconstruction/staging/pkg06c-cell-behavior-dispatch/cell_behavior_dispatch_model_test.cpp",
    "src/reconstruction/pkg06c_cell_behavior_dispatch/cell_behavior_dispatch.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-pkg06c-cell-behavior-dispatch/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg06c-cell-behavior-dispatch/00e7a190.json"
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
    "Does any unresolved native callee invalidate the cell pointer or otherwise change later fields before the target returns?",
    "Should the incoming float remain an opaque update scalar, or can another package provide a stronger canonical type and name?",
    "What are the exact return, register, stack-cleanup, mutation, and failure contracts of the 17 unresolved native callees?",
    "What concrete canonical types and lifetime boundaries correspond to ObservedCellCellResource and CellObjectData?",
    "What exact machine arguments are consumed by 0x00e67c40 and 0x00e6f800 in the mode-3 special path?",
    "What runtime values reach each early gate, special branch, and dispatch selector?",
    "What stable meanings, if any, belong to difficulty, profile type, profile+0x18, profile+0x1c, profile+0x40, profile+0x44, and dispatch selector values?",
    "canonical meaning of the incoming four-byte float",
    "concrete canonical types and lifetime boundaries for ObservedCellCellResource and ObservedCellObjectData",
    "exact machine arguments consumed by 0x00e67c40 and 0x00e6f800 in the mode-3 special path",
    "exact return, register, stack-cleanup, mutation, and failure contracts of the 17 unresolved native callees",
    "gate-cell-behavior-dispatch",
    "runtime values reaching each early gate, special branch, and dispatch selector",
    "stable meanings for difficulty, profile type, profile offsets, and dispatch selectors",
    "whether any unresolved native callee invalidates the cell pointer or changes later fields"
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-pkg06c-cell-behavior-dispatch/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg06c-cell-behavior-dispatch/00e7a190.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg06c-cell-behavior-dispatch/cell_behavior_dispatch.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg06c-cell-behavior-dispatch/cell_behavior_dispatch.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg06c-cell-behavior-dispatch/cell_behavior_dispatch_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg06c_cell_behavior_dispatch/cell_behavior_dispatch.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/integrated/batch-2026-09-25-pkg06c-cell-behavior-dispatch/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg06c-cell-behavior-dispatch/00e7a190.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg06c-cell-behavior-dispatch/cell_behavior_dispatch.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg06c-cell-behavior-dispatch/cell_behavior_dispatch.hpp",
      "source_class": "committed_artifact"
    },
    {
   
[TRUNCATED]
```
