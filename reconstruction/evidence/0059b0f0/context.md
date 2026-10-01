# Reconstruction context 0x0059b0f0

- Status: `partial`
- Content SHA-256: `d24d0e32381d871ee9faba8e1b527bcd8105fb34f758f4d85706a37c18444014`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x0059b0f0",
  "phase": "reconstruction",
  "target": "0x0059b0f0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueEditorRuntime",
  "name": "EditorCreatureController_SetTargetPosition_0059b0f0",
  "package": "PKG-EDITOR-RUNTIME-WAVE7",
  "subsystem": "Editor.Runtime",
  "va": "0x0059b0f0"
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
  "content_sha256": "1f1ba798b05bfb2fbbec8a6a404e973d769a8d404724331740ecc61f1f4022c7",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x0059b0f0 failed: Decompilation did not complete. Reason: ",
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
  "hidden_this": "OpaqueController * in ECX",
  "return_register": null,
  "return_type": "void",
  "return_width_bytes": 0,
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "position",
      "position": 1,
      "type": "const Vector3 *",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x08",
      "name": "applyNow",
      "position": 2,
      "type": "bool",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x0c",
      "name": "ignoreZ",
      "position": 3,
      "type": "bool",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 12,
  "stack_cleanup_owner": "caller"
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
      "name": "EditorAnimWorld_SetTargetPosition_0059cf00",
      "reconstructed": true,
      "va": "0x0059cf00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00629de0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0062cc20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0062d0f0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x0059cf4f",
      "direction": "in",
      "other": "0x0059cf00",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00629fb2",
      "direction": "in",
      "other": "0x00629de0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00629fc2",
      "direction": "in",
      "other": "0x00629de0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0062a012",
      "direction": "in",
      "other": "0x00629de0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0062a022",
      "direction": "in",
      "other": "0x00629de0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0062a125",
      "direction": "in",
      "other": "0x00629de0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0062cc33",
      "direction": "in",
      "other": "0x0062cc20",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0062d556",
      "direction": "in",
      "other": "0x0062d0f0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0062d732",
      "direction": "
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "OpaqueEditorRuntime",
    "bool",
    "const Vector3 *",
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
      "Creature layout beyond 0x0c and the AnimatedCreature at controller+0x08",
      "The IShadowWorld raycast argument record at 0x0059b294..0x0059b2c0 (eight stack slots) is not owned by this package",
      "The picker world returned by 0x0067dd80 and the meaning of its vtable slot 0x28 return value",
      "The picker world returned by 0x0067dd80 and the meaning of its vtable slot 0x28 return value; The IShadowWorld raycast argument record at 0x0059b294..0x0059b2c0 (eight stack slots) is not owned by this package; Whether the hit x really is a ground height; Creature layout beyond 0x0c and the AnimatedCreature at controller+0x08",
      "Whether the hit x really is a ground height"
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
      "name": "EditorAnimWorld_SetTargetPosition_0059cf00",
      "reconstructed": true,
      "va": "0x0059cf00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00629de0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0062cc20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0062d0f0"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x0059cf4f",
      "direction": "in",
      "other": "0x0059cf00",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00629fb2",
      "direction": "in",
      "other": "0x00629de0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00629fc2",
      "direction": "in",
      "other": "0x00629de0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0062a012",
      "direction": "in",
      "other": "0x00629de0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0062a022",
      "direction": "in",
      "other": "0x00629de0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0062a125",
      "direction": "in",
      "other": "0x00629de0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0062cc33",
      "direction": "in",
      "other": "0x0062cc20",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0062d556",
      "direction": "in",
      "other": "0x0062d0f0",
      "reference_t
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
      "same_calling_convention",
      "direct_xref_neighbor"
    ],
    "package": "PKG-EDITOR-RUNTIME-WAVE7",
    "score": 27,
    "symbol": "EditorAnimWorld_SetTargetPosition_0059cf00",
    "va": "0x0059cf00"
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
    "symbol": "EditorAnimWorld_PlayAnimation_0059cb10",
    "va": "0x0059cb10"
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
    "reconstruction/metadata/pkg-editor-runtime-wave7/0059b0f0.json"
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
    "Creature layout beyond 0x0c and the AnimatedCreature at controller+0x08",
    "The IShadowWorld raycast argument record at 0x0059b294..0x0059b2c0 (eight stack slots) is not owned by this package",
    "The picker world returned by 0x0067dd80 and the meaning of its vtable slot 0x28 return value",
    "The picker world returned by 0x0067dd80 and the meaning of its vtable slot 0x28 return value; The IShadowWorld raycast argument record at 0x0059b294..0x0059b2c0 (eight stack slots) is not owned by this package; Whether the hit x really is a ground height; Creature layout beyond 0x0c and the AnimatedCreature at controller+0x08",
    "Whether the hit x really is a ground height",
    "concrete runtime owners and values remain unresolved"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave7/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-editor-runtime-wave7/0059b0f0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_editor_runtime_wave7/editor_runtime_wave7.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_editor_runtime_wave7/editor_runtime_wave7.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_editor_runtime_wave7/editor_runtime_wave7_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-editor-runtime-wave7/0059b0f0.json",
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
