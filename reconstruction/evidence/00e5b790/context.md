# Reconstruction context 0x00e5b790

- Status: `partial`
- Content SHA-256: `4aae9284789fba6a10273ca77d1e0613260a0f8ae1c8a7dfd98b9fb9768bb060`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00e5b790",
  "phase": "reconstruction",
  "target": "0x00e5b790"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueCameraState",
  "name": "Simulator::Cell::MovePlayerToMousePosition",
  "package": "PKG-CAMERA-WAVE7",
  "subsystem": "Camera",
  "va": "0x00e5b790"
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
  "content_sha256": "c8042f569a5c3287d845a86e7f3b3cf2cd7bcd1f36cd2f969a8bd374035ca435",
  "live_attempts": [],
  "live_requested": false,
  "overall": "PERSISTED"
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
  "calling_convention": "__cdecl",
  "hidden_this_register": "none",
  "ordinary_stack_argument_slots": 1,
  "ordinary_stack_arguments": [
    "float delta_time"
  ],
  "ret_form": "plain RET",
  "return_type": "void",
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
      "name": "embedded_object_first_word_init_00743b50",
      "reconstructed": true,
      "va": "0x00743b50"
    },
    {
      "name": "camera_light_origin_helper_007c4900",
      "reconstructed": true,
      "va": "0x007c4900"
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e806b0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00e8083b",
      "direction": "in",
      "other": "0x00e806b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e5b835",
      "direction": "out",
      "other": "0x0067dd10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e5b9dd",
      "direction": "out",
      "other": "0x0069b600",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e5b7d4",
      "direction": "out",
      "other": "0x00743b50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e5b84f",
      "direction": "out",
      "other": "0x007c4900",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e5b7b0",
      "direction": "out",
      "other": "0x00b721d0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e5b7de",
      "direction": "out",
      "other": "0x00e4ce40",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e5b803",
      "direction": "out",
      "other": "0x00e50730",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e5b817",
      "direction": "out",
      "other": "0x00e50730",
      "referen
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
      "Original Cell-mode Wine trace and live movement-plane values are not available; no runtime promotion is claimed.",
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
  "callees": [
    {
      "name": "embedded_object_first_word_init_00743b50",
      "reconstructed": true,
      "va": "0x00743b50"
    },
    {
      "name": "camera_light_origin_helper_007c4900",
      "reconstructed": true,
      "va": "0x007c4900"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e806b0"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00e8083b",
      "direction": "in",
      "other": "0x00e806b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e5b835",
      "direction": "out",
      "other": "0x0067dd10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e5b9dd",
      "direction": "out",
      "other": "0x0069b600",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e5b7d4",
      "direction": "out",
      "other": "0x00743b50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e5b84f",
      "direction": "out",
      "other": "0x007c4900",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e5b7b0",
      "direction": "out",
      "other": "0x00b721d0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e5b7de",
      "direction": "out",
      "other": "0x00e4ce40",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e5b803",
      "direction": "out",
      "other": "0x00e50730",
      "reference_type": "direct-call"
    },
    {
      "callsite"
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
    "symbol": "camera_light_origin_helper_007c4900",
    "va": "0x007c4900"
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
    "symbol": "cell_get_globals_data_00e4ce20",
    "va": "0x00e4ce20"
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
    "symbol": "camera_manager_set_active_007c64c0",
    "va": "0x007c64c0"
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
    "symbol": "camera_manager_dispose_007c6e50",
    "va": "0x007c6e50"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-11-H3-HELPER-WAVE2",
    "score": 3,
    "symbol": "embedded_object_first_word_init_00743b50",
    "va": "0x00743b50"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-06-WAVE6-APP-MANAGERS",
    "score": 2,
    "symbol": "App_IStateManager_Get_0067dce0",
    "va": "0x0067dce0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__MovePlayerToMousePosition.c",
  "file": "src/reconstruction/pkg_camera_wave7/camera_wave7.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__MovePlayerToMousePosition.c",
    "src/reconstruction/pkg_camera_wave7/camera_wave7.cpp",
    "src/reconstruction/pkg_camera_wave7/camera_wave7_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave7/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-camera-wave7/00e5b790.json"
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
        "0x00e80ba0",
        "0x00e74a20",
        "0x00e5b790",
        "0x00e80ba0",
        "0x00e5b790",
        "0x00000000"
      ],
      "conflict_id": "TB-INH-003",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": {
        "merge_decision": "separate_entities",
        "preferred_claim": "Use coordination/composition, not inheritance.",
        "preserved_alternatives": true,
        "scope_note": "Current source ownership is non-equivalent and remains a comparison boundary.",
        "status": "preserved_alternatives",
        "taxonomy": "preserved_alternatives"
      },
      "resolution_status": "preserved_alternatives",
      "source": "knowledgegraph/research/conflicts/track-b-vtable-fields.json",
      "subject": "CellGame, CellGFX, and CellUI coordination versus inheritance",
      "unresolved_reason": "The cited static evidence leaves the competing owner, slot, layout, or lifecycle interpretation unresolved; no positive original runtime or MSVC RTTI evidence is available."
    },
    {
      "anchors": [
        "0x00e62340",
        "0x00e780a0",
        "0x00e7a7c0",
        "0x00e806b0",
        "0x00e7a7c0",
        "0x00e62340",
        "0x00e780a0",
        "0x00e806b0",
        "0x00e7fd00",
        "0x00e74a20",
        "0x00e780a0",
        "0x00e74a20",
        "0x00e74a20",
        "0x00e4ce20",
        "0x00e5b790",
        "0x00e665c0"
      ],
      "conflict_id": "U-003-cell-respawn-policy",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "Dama
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'ref': 'ephemeral reconstruction_knowledge.build_index', 'mode': 'derived', 'source_class': 'generated_index'}, {'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__MovePlayerToMousePosition.c', 'mode': 'persisted', 'source_class': 'committed_artifact'}, {'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'mode': 'persisted', 'source_class': 'committed_artifact'}, {'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'mode': 'persisted', 'source_class': 'committed_artifact'}, {'ref': 'reconstruction/integrated/batch-2026-09-25-wave7/handoff.json', 'mode': 'persisted', 'source_class': 'committed_artifact'}, {'ref': 'reconstruction/metadata/pkg-camera-wave7/00e5b790.json', 'mode': 'persisted', 'source_class': 'committed_artifact'}, {'ref': 'src/reconstruction/pkg_camera_wave7/camera_wave7.cpp', 'mode': 'persisted', 'source_class': 'committed_artifact'}, {'ref': 'src/reconstruction/pkg_camera_wave7/camera_wave7_model_test.cpp', 'mode': 'persisted', 'source_class': 'committed_artifact'}, {'ref': 'tools/re/data/ghidra_snapshot_cell_movement.json', 'mode': 'snapshot', 'source_class': 'ghidra'}`

```json
{
  "provenance": [
    {
      "mode": "derived",
      "ref": "ephemeral reconstruction_knowledge.build_index",
      "source_class": "generated_index"
    },
    {
      "mode": "persisted",
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__MovePlayerToMousePosition.c",
      "source_class": "committed_artifact"
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
      "ref": "reconstruction/metadata/pkg-camera-wave7/00e5b790.json",
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
    },
    {
      "mode": "snapshot",
      "ref": "tools/re/data/ghidra_snapshot_cell_movement.json",
      "source_class": "ghidra"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.json",
    "src/reconstruction/pkg_camera_wave7/camera_wave7.cpp",
    ".spore-analysis/ghidra-exports/decompiled_sdk/Simul
[TRUNCATED]
```
