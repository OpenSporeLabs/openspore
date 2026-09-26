# Evidence 0x00e5b790

- Evidence state: `PERSISTED`
- Live requested: `False`
- Content SHA-256: `c8042f569a5c3287d845a86e7f3b3cf2cd7bcd1f36cd2f969a8bd374035ca435`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
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

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
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
]
```

## callers_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e806b0"
  }
]
```

## contradictions

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
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
    "resolution": "Damage/death branches, despawn cleanup, optional scale replacement, and deferred stage rebuild are concrete. Caller-specific respawn policy and replacement ordering are unresolved.",
    "resolution_status": "Damage/death branches, despawn cleanup, optional scale replacement, and deferred stage rebuild are concrete. Caller-specific respawn policy and replacement ordering are unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00eedd40",
      "0x00e7fd00",
      "0x00e74a20",
      "0x00e74a20",
      "0x00e5b790",
      "0x00e80ba0",
      "0x00b72370",
      "0x00b72320",
      "0x00e780a0",
      "0x00b72160",
      "0x00b72260",
      "0x00b72270",
      "0x00b72370",
      "0x00bb4100",
      "0x00bb42a0"
    ],
    "conflict_id": "U-008-scenario-respawner",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The cited direct body establishes a bounded state mutation or call anchor, but the full transition policy, consumer order, and runtime reachability remain unresolved.",
    "resolution_status": "The cited direct body establishes a bounded state mutation or call anchor, but the full transition policy, consumer order, and runtime reachability remain unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00e7fd00",
      "0x00e74a20",
      "0x00bb42a0",
      "0x00bb4c90",
      "0x00b237c0",
      "0x00e74a20",
      "0x00e74a20",
      "0x00e4ce20",
      "0x00e5b790",
      "0x00e665c0",
      "0x00e666f0",
      "0x00e80ba0",
      "0x00be34a0",
      "0x00bddef0",
      "0x00bdde70",
      "0x00bb5b50"
    ],
    "conflict_id": "U-009-runtime-validation",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "A positive hash-pinned original-process trace is required; static naming or conceptual state names are not promoted to runtime behavior.",
    "resolution_status": "A positive hash-pinned original-process trace is required; static naming or conceptual state names are not promoted to runtime behavior.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "No positive original-process trace reaches this transition in the committed corpus."
  }
]
```

## decompilation

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: ``

## disassembly

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: ``

## external_callees

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## function_identity

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "original_bytes": 8427,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__cdecl\",\n    \"hidden_this_register\": \"none\",\n    \"ordinary_stack_argument_slots\": 1,\n    \"ordinary_stack_arguments\": [\n      \"float delta_time\"\n    ],\n    \"ret_form\": \"plain RET\",\n    \"return_type\": \"void\",\n    \"stack_cleanup_bytes\": 4\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueCameraState\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-CAMERA-WAVE7\",\n      \"score\": 25,\n      \"symbol\": \"camera_light_origin_helper_007c4900\",\n      \"va\": \"0x007c4900\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueCameraState\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-CAMERA-WAVE7\",\n      \"score\": 24,\n      \"symbol\": \"cell_get_globals_data_00e4ce20\",\n      \"va\": \"0x00e4ce20\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueCameraState\"\n      ],\n      \"package\": \"PKG-CAMERA-WAVE7\",\n      \"score\": 22,\n      \"symbol\": \"camera_manager_set_active_007c64c0\",\n      \"va\": \"0x007c64c0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueCameraState\"\n      ],\n      \"package\": \"PKG-CAMERA-WAVE7\",\n      \"score\": 22,\n      \"symbol\": \"camera_manager_dispose_007c6e50\",\n      \"va\": \"0x007c6e50\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-11-H3-HELPER-WAVE2\",\n      \"score\": 3,\n      \"symbol\": \"embedded_object_first_word_init_00743b50\",\n      \"va\": \"0x00743b50\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-06-WAVE6-APP-MANAGERS\",\n      \"score\": 2,\n      \"symbol\": \"App_IStateManager_Get_0067dce0\",\n      \"va\": \"0x0067dce0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"WAVE6-ENGINE-RUNTIME\",\n      \"score\": 2,\n      \"symbol\": \"app_config_manager_get_0067dcf0\",\n      \"va\": \"0x0067dcf0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-06-WAVE6-APP-MANAGERS\",\n      \"score\": 2,\n      \"symbol\": \"App_IPropManager_Get_0067ddf0\",\n      \"va\": \"0x0067ddf0\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Static mechanics and x86-32 ABI reviewed from live Ghidra; runtime values, concrete owners, and unresolved ports remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueCameraState\",\n  \"cluster\": \"sim-cell\",\n  \"confidence\": 0.7,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"embedded_object_first_word_init_00743b50\",\n        \"reconstructed\": true,\n        \"va\": \"0x00743b50\"\n      },\n      {\n        \"name\": \"camera_light_origin_helper_007c4900\",\n        \"reconstructed\": true,\n        \"va\": \"0x007c4900\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e806b0\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00e8083b\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e806b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e5b835\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067dd10\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e5b9dd\",\n        \"direction\": \"out\",\n        \"other\": \"0x0069b600\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e5b7d4\",\n        \"direction\": \"out\",\n        \"other\": \"0x00743b50\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e5b84f\",\n        \"direction\": \"out\",\n        \"other\": \"0x007c4900\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e5b7b0\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b721d0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e5b7de\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e4ce40\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e5b803\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e50730\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e5b817\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e50730\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e5b7c8\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e5b2e0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e5b7f0\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e82130\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 1,\n    \"fan_out\": 2,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [\n      \"0x00743b50\",\n      \"0x007c4900\"\n    ],\n    \"scc\": {\n      \"id\": \"scc-04
[TRUNCATED]
```

## ghidra_function

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `tools/re/data/ghidra_snapshot_cell_movement.json`

```json
{
  "address": "0x00e5b790",
  "body": [
    15054736,
    15055361
  ],
  "callees": [
    "FUN_00e5b2e0",
    "FUN_00743b50",
    "FUN_00e4ce40",
    "FUN_00e82130",
    "FUN_00e50730",
    "Graphics::IRenderer::Get",
    "FUN_007c4900",
    "FUN_0069b600"
  ],
  "callers": [
    "FUN_00e806b0"
  ],
  "decompiled_evidence": "Guard: return if sCellGame+20824 != 0 (a lock/paused flag). Player = FUN_00b721d0(* (sCellGame+16668)) (container-getter-by-index); if 0 return. FUN_00e5b2e0(dt) (per-frame update). Camera mode = FUN_00e4ce40()[+212]. Camera origin+dir fetched (FUN_007c4900 fills origin via ILightingWorld; direction is the view ray). Compute t = dot(dir, planeNormal) inverse; if valid and t>=0 set player pos (player+8/12/16) = origin + dir*t (RAY-PLANE INTERSECTION on the movement plane). Then targetDelta = -(newPos - curPos) using curPos at player+76/80/84; FUN_0069b600(...) computes orientation (rotation) to face travel; stored at player+20..32. Sets sCellGame+20880+224 = 1 ('moving' flag).",
  "evidence_level": "VERIFIED (SDK name + ray-plane intersection structure OBSERVED in decompilation); plane-normal/point constants = OBSERVED addresses, values INFERRED (need runtime to read)",
  "globals_referenced": [
    "Simulator::Cell::sCellGame (+20824 lock flag, +16668 player-ref, +20880)",
    "Simulator::Cell::sCellUI (+36, +38)"
  ],
  "key_constants": {
    "DAT_015a7c40": "plane normal X (movement plane)",
    "DAT_015a7c44": "plane normal Y",
    "DAT_015a7c48": "plane normal Z",
    "DAT_016b3c28/2c/30": "plane point (origin offset) X/Y/Z"
  },
  "name": "Simulator::Cell::MovePlayerToMousePosition",
  "rva": "0xa5b790",
  "signature": "void Simulator::Cell::MovePlayerToMousePosition(float deltaTime)",
  "size_bytes": 625
}
```

## globals

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
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

## runtime

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## runtime_metadata

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "blocking_reason": null,
  "gates": [
    "Original Cell-mode Wine trace and live movement-plane values are not available; no runtime promotion is claimed.",
    "runtime observation required"
  ],
  "validated": 0
}
```

## semantic_hypotheses

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

## status

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "runtime_gated": true,
  "runtime_validated": 0,
  "status": "reconstructed"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "OpaqueCameraState",
  "void"
]
```

## vtables

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## Conflicts

```json
[
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
    "resolution": "Damage/death branches, despawn cleanup, optional scale replacement, and deferred stage rebuild are concrete. Caller-specific respawn policy and replacement ordering are unresolved.",
    "resolution_status": "Damage/death branches, despawn cleanup, optional scale replacement, and deferred stage rebuild are concrete. Caller-specific respawn policy and replacement ordering are unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00eedd40",
      "0x00e7fd00",
      "0x00e74a20",
      "0x00e74a20",
      "0x00e5b790",
      "0x00e80ba0",
      "0x00b72370",
      "0x00b72320",
      "0x00e780a0",
      "0x00b72160",
      "0x00b72260",
      "0x00b72270",
      "0x00b72370",
      "0x00bb4100",
      "0x00bb42a0"
    ],
    "conflict_id": "U-008-scenario-respawner",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The cited direct body establishes a bounded state mutation or call anchor, but the full transition policy, consumer order, and runtime reachability remain unresolved.",
    "resolution_status": "The cited direct body establishes a bounded state mutation or call anchor, but the full transition policy, consumer order, and runtime reachability remain unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00e7fd00",
      "0x00e74a20",
      "0x00bb42a0",
      "0x00bb4c90",
      "0x00b237c0",
      "0x00e74a20",
      "0x00e74a20",
      "0x00e4ce20",
      "0x00e5b790",
      "0x00e665c0",
      "0x00e666f0",
      "0x00e80ba0",
      "0x00be34a0",
      "0x00bddef0",
      "0x00bdde70",
      "0x00bb5b50"
    ],
    "conflict_id": "U-009-runtime-validation",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "A positive hash-pinned original-process trace is required; static naming or conceptual state names are not promoted to runtime behavior.",
    "resolution_status": "A positive hash-pinned original-process trace is required; static naming or conceptual state names are not promoted to runtime behavior.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "No positive original-process trace reaches this transition in the committed corpus."
  }
]
```
