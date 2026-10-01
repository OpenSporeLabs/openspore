# Reconstruction context 0x007c4900

- Status: `partial`
- Content SHA-256: `c191269618e5e394120cd2cbe9d2bf4edc522c6ce8f949445ad686f6b8eeb106`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x007c4900",
  "phase": "reconstruction",
  "target": "0x007c4900"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueCameraState",
  "name": "camera_light_origin_helper_007c4900",
  "package": "PKG-CAMERA-WAVE7",
  "subsystem": "Camera",
  "va": "0x007c4900"
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
  "content_sha256": "d24494b1cb9f99f117e78a73e1e56d03926e3505f5b9c70d24ed63cc58107132",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x007c4900 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "__thiscall",
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": 2,
  "ordinary_stack_arguments": [
    "direction output pointer at [ESP+4]",
    "origin output pointer at [ESP+8]"
  ],
  "ret_form": "RET 0x8 after restoring ESI",
  "return_type": "void",
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
      "name": null,
      "reconstructed": false,
      "va": "0x00574850"
    },
    {
      "name": "Editors::cEditor::HandleMessage",
      "reconstructed": false,
      "va": "0x00591fa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ace4e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b34790"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b349b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c63dd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c66760"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c678f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d0a040"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d0ae50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d11730"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e5aae0"
    },
    {
      "name": "cell_move_player_to_mouse_position_00e5b790",
      "reconstructed": true,
      "va": "0x00e5b790"
    },
    {
      "name": "cell_mode_strategy_on_mouse_up_00e5c0f0",
      "reconstructed": true,
      "va": "0x00e5c0f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e62500"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e6c780"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00574
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "OpaqueCameraState",
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
      "Original application camera-frame trace is not available; no runtime promotion is claimed.",
      "runtime observation required"
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
      "va": "0x00574850"
    },
    {
      "name": "Editors::cEditor::HandleMessage",
      "reconstructed": false,
      "va": "0x00591fa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ace4e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b34790"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b349b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c63dd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c66760"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c678f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d0a040"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d0ae50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d11730"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e5aae0"
    },
    {
      "name": "cell_move_player_to_mouse_position_00e5b790",
      "reconstructed": true,
      "va": "0x00e5b790"
    },
    {
      "name": "cell_mode_strategy_on_mouse_up_00e5c0f0",
      "reconstructed": true,
      "va": "0x00e5c0f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e62500"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e6c780"
    },
    {
      "name": nul
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
      "shared_types:OpaqueCameraState",
      "direct_xref_neighbor"
    ],
    "package": "PKG-CAMERA-WAVE7",
    "score": 25,
    "symbol": "cell_move_player_to_mouse_position_00e5b790",
    "va": "0x00e5b790"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "same_class",
      "shared_types:OpaqueCameraState",
      "same_calling_convention"
    ],
    "package": "PKG-CAMERA-WAVE7",
    "score": 24,
    "symbol": "camera_manager_set_active_007c64c0",
    "va": "0x007c64c0"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "same_class",
      "shared_types:OpaqueCameraState",
      "same_calling_convention"
    ],
    "package": "PKG-CAMERA-WAVE7",
    "score": 24,
    "symbol": "camera_manager_dispose_007c6e50",
    "va": "0x007c6e50"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "same_class",
      "shared_types:OpaqueCameraState"
    ],
    "package": "PKG-CAMERA-WAVE7",
    "score": 22,
    "symbol": "cell_get_globals_data_00e4ce20",
    "va": "0x00e4ce20"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "PKG-CAMERA-WAVE8",
    "score": 8,
    "symbol": "editor_camera_func24h_005a2050",
    "va": "0x005a2050"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "PKG-CAMERA-WAVE8",
    "score": 8,
    "symbol": "editor_camera_func54h_005a2320",
    "va": "0x005a2320"
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg_camera_wave7/camera_wave7.cpp",
  "files": [
    "src/reconstruction/pkg_camera_wave7/camera_wave7.cpp",
    "src/reconstruction/pkg_camera_wave7/camera_wave7_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave7/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-camera-wave7/007c4900.json"
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
    "Original application camera-frame trace is not available; no runtime promotion is claimed.",
    "concrete runtime owners and values remain unresolved",
    "runtime observation required"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave7/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-camera-wave7/007c4900.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_camera_wave7/camera_wave7.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_camera_wave7/camera_wave7_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-camera-wave7/007c4900.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_camera_wave7/camera_wave7.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_camera_wave7/camera_wave7_model_test.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.json",
    "src/reconstruction/
[TRUNCATED]
```
