# Reconstruction context 0x0059b2f0

- Status: `partial`
- Content SHA-256: `f09aaffff07a7a378390ad84b65bff991b44da26065e46de4c2f8c535d512353`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x0059b2f0",
  "phase": "reconstruction",
  "target": "0x0059b2f0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueCreatureWalkController",
  "name": "Editor_CreatureWalkController_SetTargetAngle",
  "package": "PKG-EDITOR-RUNTIME-WAVE8",
  "subsystem": "Editor.Runtime",
  "va": "0x0059b2f0"
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
  "content_sha256": "986f014f9791d0271d74cdb29e04688acd50d24b0bd93b02b2a2ceec31a3f151",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x0059b2f0 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "thiscall with callee stack cleanup",
  "receiver_register": "ECX",
  "ret_form": "RET 0x8",
  "return_register": null,
  "return_width_bytes": 0,
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "machine_type": "float",
      "normalized_name": "angle",
      "position": 1,
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x08",
      "machine_type": "bool",
      "native_test": "low byte at ESP+0x08",
      "normalized_name": "apply_now",
      "position": 2,
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 8
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
      "name": "EditorAnimWorld_SetTargetAngle_0059cea0",
      "reconstructed": true,
      "va": "0x0059cea0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0062cc20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00638810"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x0059ceed",
      "direction": "in",
      "other": "0x0059cea0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0062cd14",
      "direction": "in",
      "other": "0x0062cc20",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0063886a",
      "direction": "in",
      "other": "0x00638810",
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
    "OpaqueCreatureWalkController",
    "OpaqueCreatureWalkController*"
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
      "required"
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
      "name": "EditorAnimWorld_SetTargetAngle_0059cea0",
      "reconstructed": true,
      "va": "0x0059cea0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0062cc20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00638810"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x0059ceed",
      "direction": "in",
      "other": "0x0059cea0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0062cd14",
      "direction": "in",
      "other": "0x0062cc20",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0063886a",
      "direction": "in",
      "other": "0x00638810",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 3,
  "fan_out": 0,
  "manifest_callees": [],
  "manifest_callers": [
    {
      "call_site": "0x0059ceed",
      "function": "Editors::cEditorAnimWorld::SetTargetAngle",
      "va": "0x0059cea0"
    },
    {
      "call_site": "0x0062cd14",
      "function": "FUN_0062cc20",
      "va": "0x0062cc20"
    },
    {
      "call_site": "0x0063886a",
      "function": "FUN_00638810",
      "va": "0x00638810"
    }
  ],
  "nearby_reconstructed": [
    "0x0059cea0"
  ],
  "scc": {
    "id": "scc-0087",
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
      "same_subsystem",
      "direct_xref_neighbor"
    ],
    "package": "PKG-EDITOR-RUNTIME-WAVE7",
    "score": 9,
    "symbol": "EditorAnimWorld_SetTargetAngle_0059cea0",
    "va": "0x0059cea0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-EDITOR-RUNTIME-WAVE7",
    "score": 6,
    "symbol": "EditorCreatureController_SetTargetPosition_0059b0f0",
    "va": "0x0059b0f0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-EDITOR-RUNTIME-WAVE7",
    "score": 6,
    "symbol": "EditorCreatureController_Update_0059b4b0",
    "va": "0x0059b4b0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-EDITOR-RUNTIME-WAVE7",
    "score": 6,
    "symbol": "EditorAnimWorld_GetCreatureController_0059cac0",
    "va": "0x0059cac0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-EDITOR-RUNTIME-WAVE7",
    "score": 6,
    "symbol": "EditorAnimWorld_PlayAnimation_0059cb10",
    "va": "0x0059cb10"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-EDITOR-RUNTIME-WAVE7",
    "score": 6,
    "symbol": "EditorAnimWorld_SetTargetPosition_0059cf00",
    "va": "0x0059cf00"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-APP-SAFE-WAVE10",
    "score": 2,
    "symbol": "cursor_buffer_emit_0041e8b0",
    "va": "0x0041e8b0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-SKINNER-SAFE-WAVE10",
    "score": 2,
    "symbol": "skin_painter_state_setup
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg_editor_runtime_wave8/editor_runtime_wave8.cpp",
  "files": [
    "src/reconstruction/pkg_editor_runtime_wave8/editor_runtime_wave8.cpp",
    "src/reconstruction/pkg_editor_runtime_wave8/editor_runtime_wave8.hpp",
    "src/reconstruction/pkg_editor_runtime_wave8/editor_runtime_wave8_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave8/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-editor-runtime-wave8/0059b2f0.json"
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
    "concrete runtime owners and values remain unresolved",
    "required"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave8/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-editor-runtime-wave8/0059b2f0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_editor_runtime_wave8/editor_runtime_wave8.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_editor_runtime_wave8/editor_runtime_wave8.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_editor_runtime_wave8/editor_runtime_wave8_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/integrated/batch-2026-09-25-wave8/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg-editor-runtime-wave8/0059b2f0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_editor_runtime_wave8/editor_runtime_wave8.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_editor_runtime_wave8/editor_runtime_wave8.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstru
[TRUNCATED]
```
