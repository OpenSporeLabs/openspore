# Reconstruction context 0x00e806b0

- Status: `partial`
- Content SHA-256: `05d50aff4e35a07c4a5acb5bbdc202ada6fd409aec84cd6ac7ad579558077da1`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00e806b0",
  "phase": "reconstruction",
  "target": "0x00e806b0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueCellUpdateBody",
  "name": "cell_update_body_00e806b0",
  "package": "PKG-FRAME-RUNTIME-WAVE8",
  "subsystem": "Runtime.Frame",
  "va": "0x00e806b0"
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
  "content_sha256": "2afe9e34c38e0266b262e35e748d749f31753be7964f14446d4e25992c2c0771",
  "live_attempts": [
    {
      "code": "live_unavailable",
      "kind": "decompilation",
      "message": "Ghidra returned snapshot instead of live evidence",
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
  "calling_convention": "cdecl body with caller-cleaned adapter subset",
  "ordinary_stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "machine_type": "float",
      "normalized_name": "first_stack_word",
      "position": 1,
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x08",
      "machine_type": "float",
      "normalized_name": "second_stack_word",
      "position": 2,
      "width_bytes": 4
    }
  ],
  "receiver_register": "ECX register residue is not normalized as a body parameter",
  "ret_form": "plain RET",
  "return_register": "EAX",
  "return_width_bytes": 0
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "root_accessor_00b3d3f0",
      "reconstructed": true,
      "va": "0x00b3d3f0"
    },
    {
      "name": "Simulator_cSpaceTrading_Get",
      "reconstructed": true,
      "va": "0x00b3d4d0"
    },
    {
      "name": "cell_move_player_to_mouse_position_00e5b790",
      "reconstructed": true,
      "va": "0x00e5b790"
    },
    {
      "name": "FUN_00e7fd00",
      "reconstructed": true,
      "va": "0x00e7fd00"
    }
  ],
  "callers": [
    {
      "name": "cell_mode_update_00e80980",
      "reconstructed": true,
      "va": "0x00e80980"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00e80992",
      "direction": "in",
      "other": "0x00e80980",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e80720",
      "direction": "out",
      "other": "0x0067dd20",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e806fc",
      "direction": "out",
      "other": "0x0067de20",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e80947",
      "direction": "out",
      "other": "0x006ffe00",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e807d9",
      "direction": "out",
      "other": "0x00b3d3f0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e8091a",
      "direction": "out",
      "other": "0x00b3d3f0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e807a2",
      "direction": "out",
      "other": "0x00b3d4d0",
      "reference_type": "direct-call"
    },
    {
      "callsite": 
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "OpaqueCellUpdateBody"
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
  "callees": [
    {
      "name": "root_accessor_00b3d3f0",
      "reconstructed": true,
      "va": "0x00b3d3f0"
    },
    {
      "name": "Simulator_cSpaceTrading_Get",
      "reconstructed": true,
      "va": "0x00b3d4d0"
    },
    {
      "name": "cell_move_player_to_mouse_position_00e5b790",
      "reconstructed": true,
      "va": "0x00e5b790"
    },
    {
      "name": "FUN_00e7fd00",
      "reconstructed": true,
      "va": "0x00e7fd00"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": "cell_mode_update_00e80980",
      "reconstructed": true,
      "va": "0x00e80980"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00e80992",
      "direction": "in",
      "other": "0x00e80980",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e80720",
      "direction": "out",
      "other": "0x0067dd20",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e806fc",
      "direction": "out",
      "other": "0x0067de20",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e80947",
      "direction": "out",
      "other": "0x006ffe00",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e807d9",
      "direction": "out",
      "other": "0x00b3d3f0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e8091a",
      "direction": "out",
      "other": "0x00b3d3f0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e807a2",
      "direction": "out",
      "other"
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
      "shared_types:OpaqueCellUpdateBody"
    ],
    "package": "PKG-FRAME-RUNTIME-WAVE8",
    "score": 22,
    "symbol": "timing_update_body_00b31cc0",
    "va": "0x00b31cc0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "direct_xref_neighbor"
    ],
    "package": "PKG-FRAME-RUNTIME-WAVE7",
    "score": 9,
    "symbol": "cell_mode_update_00e80980",
    "va": "0x00e80980"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-FRAME-RUNTIME-WAVE7",
    "score": 6,
    "symbol": "app_frame_update_00f47930",
    "va": "0x00f47930"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-11-H2-ROOT-ACCESSORS",
    "score": 3,
    "symbol": "root_accessor_00b3d3f0",
    "va": "0x00b3d3f0"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 3,
    "symbol": "Simulator_cSpaceTrading_Get",
    "va": "0x00b3d4d0"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-CAMERA-WAVE7",
    "score": 3,
    "symbol": "cell_move_player_to_mouse_position_00e5b790",
    "va": "0x00e5b790"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-06-CELL-STATE",
    "score": 3,
    "symbol": "FUN_00e7fd00",
    "va": "0x00e7fd00"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg_frame_runtime_wave8/frame_runtime_wave8.cpp",
  "files": [
    "src/reconstruction/pkg_frame_runtime_wave8/frame_runtime_wave8.cpp",
    "src/reconstruction/pkg_frame_runtime_wave8/frame_runtime_wave8.hpp",
    "src/reconstruction/pkg_frame_runtime_wave8/frame_runtime_wave8_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave8/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-frame-runtime-wave8/00e806b0.json"
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
      "resolution": "Damage/death branches, despawn cleanup, optional scale replacement, and deferred stage rebuild are concrete. Caller-specific respawn policy and replacement ordering are unresolved.",
      "resolution_status": "Damage/death branches, despawn cleanup, optional scale replacement, and deferred stage rebuild are concrete. Caller-specific respawn policy and replacement ordering are unresolved.",
      "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
      "subject": null,
      "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
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
        "0x00e62200",
        "0x00e62200",
        "0x00e62340",
        "0x00e62340",
        "0x007d8c80"
      ],
      "conflict_id": "U-CELL-ROLLOVER",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "Rollover creatio
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave8/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-frame-runtime-wave8/00e806b0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_frame_runtime_wave8/frame_runtime_wave8.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_frame_runtime_wave8/frame_runtime_wave8.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_frame_runtime_wave8/frame_runtime_wave8_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-frame-runtime-wave8/00e806b0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_frame_runtime_wave8/frame_runtime_wave8.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_frame_runtime_wave8/frame_runtime_wave8.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction
[TRUNCATED]
```
