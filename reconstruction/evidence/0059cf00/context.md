# Reconstruction context 0x0059cf00

- Status: `partial`
- Content SHA-256: `29db93066400ccb4673b9a61f340cea69e5533bf84b5525e47cc48b7e29bba58`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x0059cf00",
  "phase": "reconstruction",
  "target": "0x0059cf00"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueEditorRuntime",
  "name": "EditorAnimWorld_SetTargetPosition_0059cf00",
  "package": "PKG-EDITOR-RUNTIME-WAVE7",
  "subsystem": "Editor.Runtime",
  "va": "0x0059cf00"
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
  "content_sha256": "7f981d398e91fe5185b1e14be40a9e46bc0bd758fdb049ea911cec2a8f46fc7b",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x0059cf00 failed: Decompilation did not complete. Reason: ",
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
      "name": "position",
      "position": 2,
      "type": "Vector3 (12 bytes, by value, occupies three argument slots)",
      "width_bytes": 12
    },
    {
      "entry_offset": "ESP+0x14",
      "name": "applyNow",
      "position": 3,
      "type": "bool",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x18",
      "name": "ignoreZ",
      "position": 4,
      "type": "bool",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 24,
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
      "name": "EditorCreatureController_SetTargetPosition_0059b0f0",
      "reconstructed": true,
      "va": "0x0059b0f0"
    },
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
      "va": "0x00582fe0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00587270"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059d240"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00639350"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x0058362e",
      "direction": "in",
      "other": "0x00582fe0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00583831",
      "direction": "in",
      "other": "0x00582fe0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005838b4",
      "direction": "in",
      "other": "0x00582fe0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005873cc",
      "direction": "in",
      "other": "0x00587270",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0059d2c2",
      "direction": "in",
      "other": "0x0059d240",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00639541",
      "direction": "in",
      "other": "0x00639350",
      "reference_type": "direct-call"
    },
 
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
    "Vector3 (12 bytes, by value, occupies three argument slots)",
    "bool",
    "std::int32_t",
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
      "Coordinate space and units of the forwarded Vector3",
      "Coordinate space and units of the forwarded Vector3; Whether ignoreZ is ever set in practice by editor input paths; Interaction between applyNow and the ground-follow raycast in the target",
      "Interaction between applyNow and the ground-follow raycast in the target",
      "Whether ignoreZ is ever set in practice by editor input paths"
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
      "name": "EditorCreatureController_SetTargetPosition_0059b0f0",
      "reconstructed": true,
      "va": "0x0059b0f0"
    },
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
      "va": "0x00582fe0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00587270"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059d240"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00639350"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x0058362e",
      "direction": "in",
      "other": "0x00582fe0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00583831",
      "direction": "in",
      "other": "0x00582fe0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005838b4",
      "direction": "in",
      "other": "0x00582fe0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005873cc",
      "direction": "in",
      "other": "0x00587270",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0059d2c2",
      "direction": "in",
      "other": "0x0059d240",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00639541",
      "directio
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
    "symbol": "EditorAnimWorld_SetTargetAngle_005
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
    "reconstruction/metadata/pkg-editor-runtime-wave7/0059cf00.json"
  ]
}
```

## 13_semantic_hypotheses

- State: `missing`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

## 14_conflicts_questions

- State: `conflicted`
- Provenance: `reconstruction/knowledge/index.json, knowledgegraph/research/semantic-decomp.json`

```json
{
  "conflicts": [
    {
      "anchors": [
        "0x00587270",
        "0x0059d840",
        "0x0059d8b0",
        "0x00587270",
        "0x0059d8b0",
        "0x0059d840",
        "0x0067cae0",
        "0x00b31da0",
        "0x0059ca70",
        "0x0059cac0",
        "0x00b321e0",
        "0x00b32330",
        "0x00b32560",
        "0x0059cea0",
        "0x0059cf00",
        "0x00b63980"
      ],
      "conflict_id": "unresolved:knowledgegraph/research/state-machines/additional-domains.json:3",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
      "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
      "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
      "subject": null,
      "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
    },
    {
      "anchors": [
        "0x00571f80",
        "0x00571f80",
        "0x0067cae0",
        "0x00a20670",
        "0x00571f80",
        "0x00572070",
        "0x00572020",
        "0x0059ca70",
        "0x0059cac0",
        "0x0059cea0",
        "0x0059cf00",
        "0x0067dd90",
        "0x00e66280",
        "0x00e66840",
        "0x00e63560",
        "0x0059c6e0"
      ],
      "conflict_id": "unresolved:knowledgegraph/research/state-machines/additional-domains.j
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave7/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-editor-runtime-wave7/0059cf00.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_editor_runtime_wave7/editor_runtime_wave7.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_editor_runtime_wave7/editor_runtime_wave7.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_editor_runtime_wave7/editor_runtime_wave7_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-editor-runtime-wave7/0059cf00.json",
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
