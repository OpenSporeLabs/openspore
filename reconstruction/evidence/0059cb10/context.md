# Reconstruction context 0x0059cb10

- Status: `partial`
- Content SHA-256: `4a2b97a233623d56cc18748842eb7db83bdd87343ea79cb8f887cd5d696c98ae`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x0059cb10",
  "phase": "reconstruction",
  "target": "0x0059cb10"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueEditorRuntime",
  "name": "EditorAnimWorld_PlayAnimation",
  "package": "PKG-EDITOR-RUNTIME-WAVE7",
  "subsystem": "Editor.Runtime",
  "va": "0x0059cb10"
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
  "content_sha256": "14353a02e653f2cf6b74fb93e92b34bf2c92466a9c9c5323caf3fc6d59730894",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x0059cb10 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "thiscall",
  "hidden_this": "OpaqueAnimWorld * in ECX",
  "return_register": null,
  "return_type": "void",
  "return_width_bytes": 0,
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "creatureID",
      "position": 1,
      "type": "std::int32_t",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x08",
      "name": "animationID",
      "position": 2,
      "type": "std::uint32_t",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 8,
  "stack_cleanup_owner": "caller"
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "map_int_EditorCreatureControllerPtr__get",
      "reconstructed": false,
      "va": "0x0059c740"
    },
    {
      "name": "map_int_whatever_find",
      "reconstructed": true,
      "va": "0x00e5c780"
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00577e10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00582fe0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00579309",
      "direction": "in",
      "other": "0x00577e10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0057932f",
      "direction": "in",
      "other": "0x00577e10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0057934e",
      "direction": "in",
      "other": "0x00577e10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0057936d",
      "direction": "in",
      "other": "0x00577e10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00583734",
      "direction": "in",
      "other": "0x00582fe0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0059cb45",
      "direction": "out",
      "other": "0x0059c740",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0059cb72",
      "direction": "out",
      "other": "0x007cd950",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0059cb32",
      "direction": "out",
      "other": "0x00e5c780",
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
    "OpaqueEditorRuntime",
    "std::int32_t",
    "std::uint32_t",
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
      "Interaction with the 0x38 and 0x3c gates at runtime",
      "The concrete creature vtable at controller+0x08 and the meaning of slot +4",
      "The concrete creature vtable at controller+0x08 and the meaning of slot +4; Whether controller+0x1c is a clip index, hash or resource id, and who reads it; Interaction with the 0x38 and 0x3c gates at runtime; The concrete implementation behind the 0x007cd950 publication port",
      "The concrete implementation behind the 0x007cd950 publication port",
      "Whether controller+0x1c is a clip index, hash or resource id, and who reads it"
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
      "name": "map_int_EditorCreatureControllerPtr__get",
      "reconstructed": false,
      "va": "0x0059c740"
    },
    {
      "name": "map_int_whatever_find",
      "reconstructed": true,
      "va": "0x00e5c780"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00577e10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00582fe0"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00579309",
      "direction": "in",
      "other": "0x00577e10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0057932f",
      "direction": "in",
      "other": "0x00577e10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0057934e",
      "direction": "in",
      "other": "0x00577e10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0057936d",
      "direction": "in",
      "other": "0x00577e10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00583734",
      "direction": "in",
      "other": "0x00582fe0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0059cb45",
      "direction": "out",
      "other": "0x0059c740",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0059cb72",
      "direction": "out",
      "other": "0x007cd950",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0059cb32",
      "direction": "out",
      "other": "0x00e5c78
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
      "shared_types:OpaqueEditorRuntime",
      "same_calling_convention"
    ],
    "package": "PKG-EDITOR-RUNTIME-WAVE7",
    "score": 24,
    "symbol": "EditorCreatureController_SetTargetPosition_0059b0f0",
    "va": "0x0059b0f0"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "same_class",
      "shared_types:OpaqueEditorRuntime",
      "same_calling_convention"
    ],
    "package": "PKG-EDITOR-RUNTIME-WAVE7",
    "score": 24,
    "symbol": "EditorCreatureController_Update_0059b4b0",
    "va": "0x0059b4b0"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "same_class",
      "shared_types:OpaqueEditorRuntime",
      "same_calling_convention"
    ],
    "package": "PKG-EDITOR-RUNTIME-WAVE7",
    "score": 24,
    "symbol": "EditorAnimWorld_GetCreatureController_0059cac0",
    "va": "0x0059cac0"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "same_class",
      "shared_types:OpaqueEditorRuntime",
      "same_calling_convention"
    ],
    "package": "PKG-EDITOR-RUNTIME-WAVE7",
    "score": 24,
    "symbol": "EditorAnimWorld_SetTargetAngle_0059cea0",
    "va": "0x0059cea0"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "same_class",
      "shared_types:OpaqueEditorRuntime",
      "same_calling_convention"
    ],
    "package": "PKG-EDITOR-RUNTIME-WAVE7",
    "score": 24,
    "symbol": "EditorAnimWorld_SetTargetPosition_0059cf00",
    "va": "0x0059c
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg_editor_runtime_wave7/editor_runtime_wave7.cpp",
  "files": [
    "src/reconstruction/pkg_editor_runtime_wave7/editor_runtime_wave7.cpp",
    "src/reconstruction/pkg_editor_runtime_wave7/editor_runtime_wave7.hpp",
    "src/reconstruction/pkg_editor_runtime_wave7/editor_runtime_wave7_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave7/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-editor-runtime-wave7/0059cb10.json"
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
    "Interaction with the 0x38 and 0x3c gates at runtime",
    "The concrete creature vtable at controller+0x08 and the meaning of slot +4",
    "The concrete creature vtable at controller+0x08 and the meaning of slot +4; Whether controller+0x1c is a clip index, hash or resource id, and who reads it; Interaction with the 0x38 and 0x3c gates at runtime; The concrete implementation behind the 0x007cd950 publication port",
    "The concrete implementation behind the 0x007cd950 publication port",
    "Whether controller+0x1c is a clip index, hash or resource id, and who reads it",
    "concrete runtime owners and values remain unresolved"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave7/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-editor-runtime-wave7/0059cb10.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_editor_runtime_wave7/editor_runtime_wave7.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_editor_runtime_wave7/editor_runtime_wave7.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_editor_runtime_wave7/editor_runtime_wave7_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/integrated/batch-2026-09-25-wave7/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg-editor-runtime-wave7/0059cb10.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_editor_runtime_wave7/editor_runtime_wave7.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_editor_runtime_wave7/editor_runtime_wave7.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstru
[TRUNCATED]
```
