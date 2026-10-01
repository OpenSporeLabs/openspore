# Reconstruction context 0x007c64c0

- Status: `partial`
- Content SHA-256: `31812f2dddda669bb260b81e700a99bec34e0cff68f06f4d574e63d05f8572e8`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x007c64c0",
  "phase": "reconstruction",
  "target": "0x007c64c0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueCameraState",
  "name": "camera_manager_set_active_007c64c0",
  "package": "PKG-CAMERA-WAVE7",
  "subsystem": "Camera",
  "va": "0x007c64c0"
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
  "content_sha256": "54aa20de44e99399b936ac2cfbf8269ebc189d809088b2a246c6ecd34a2b1d0c",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x007c64c0 failed: Decompilation did not complete. Reason: ",
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
  "ordinary_stack_argument_slots": 1,
  "ordinary_stack_arguments": [
    "dword key at [ESP+4] after entry"
  ],
  "ret_form": "RET 0x4",
  "return_note": "machine value",
  "return_type": "OpaqueCamera*",
  "stack_cleanup_bytes": 4
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [],
  "callers": [],
  "edge_rows": [],
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
    "OpaqueCamera* machine value",
    "OpaqueCameraState"
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
      "Wine/original Cell or application camera-manager trace is not available; no runtime promotion is claimed.",
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
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 0,
  "fan_out": 0,
  "manifest_callees": [],
  "manifest_callers": [],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0238",
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
      "shared_types:OpaqueCameraState",
      "same_calling_convention"
    ],
    "package": "PKG-CAMERA-WAVE7",
    "score": 24,
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
      "same_package",
      "same_subsystem",
      "same_class",
      "shared_types:OpaqueCameraState"
    ],
    "package": "PKG-CAMERA-WAVE7",
    "score": 22,
    "symbol": "cell_move_player_to_mouse_position_00e5b790",
    "va": "0x00e5b790"
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
  },
  {
    "match_basis": 
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
    "reconstruction/metadata/pkg-camera-wave7/007c64c0.json"
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
        "0x007d85b0",
        "0x007d8d40",
        "0x01412598",
        "0x01412598",
        "0x007d8c80",
        "0x007d8d40",
        "0x007d85b0",
        "0x007d8d40",
        "0x01412598",
        "0x007d8c80",
        "0x007c61a0",
        "0x007c61a0",
        "0x007c64c0",
        "0x007c64c0",
        "0x007c6750",
        "0x007c6750"
      ],
      "conflict_id": "app_mode_setter_boundary",
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
        "0x007c61a0",
        "0x007c64c0",
        "0x007c6750",
        "0x007c6eb0",
        "0x007c61a0",
        "0x007c61a0",
        "0x007c61a0",
        "0x007c61a0",
        "0x007c64c0",
        "0x007c64c0",
        "0x007c64c0",
        "0x007c6750",
        "0x007c6750",
        "0x007c6750",
        "0x007c6eb0",
        "0x007c6eb0"
      ],
      "conflict_id": "camera_address_conflicts",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The committed evid
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave7/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-camera-wave7/007c64c0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_camera_wave7/camera_wave7.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_camera_wave7/camera_wave7_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-camera-wave7/007c64c0.json",
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
