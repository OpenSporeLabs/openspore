# Reconstruction context 0x0102df20

- Status: `partial`
- Content SHA-256: `8c1a55675fb8e78e3042582dd082b05967415daff13f7335a3bbc3fcdd0e7033`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x0102df20",
  "phase": "reconstruction",
  "target": "0x0102df20"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": null,
  "package": null,
  "subsystem": null,
  "va": "0x0102df20"
}
```

## 03_current_status

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "blocked": false,
  "reconstructed": false,
  "runtime_gated": false,
  "runtime_validated": 0,
  "status": "unresolved"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "2d9fcee7e5119f93521cf9e3d6962481c69c2e2562df624b52944b7167ddd47c",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x0102df20 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "cdecl observed; no implicit this parameter",
  "return_observation": "The function has void live decompilation and returns through ordinary RET paths.",
  "return_type": "void",
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "observed_use": "Loaded into ECX from the first stack slot and dereferenced at offset 0 to select a large event-code dispatch.",
      "position": 1,
      "type": "SpaceEvent *",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x08",
      "observed_use": "Loaded from the second stack slot and forwarded to branch helpers and FUN_0102d1b0.",
      "position": 2,
      "type": "Space *",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x0C",
      "observed_use": "Loaded from the third stack slot, null-checked in selected paths, and forwarded to event/cleanup helpers.",
      "position": 3,
      "type": "SpaceContext *",
      "width_bytes": 4
    }
  ]
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "address_window_offset_005c65e0",
      "reconstructed": true,
      "va": "0x005c65e0"
    },
    {
      "name": "achievement_progress_update_00676e90",
      "reconstructed": true,
      "va": "0x00676e90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0067dcc0"
    },
    {
      "name": "Simulator_cCommManager_CreateAndDispatchEvent_00aeb720",
      "reconstructed": true,
      "va": "0x00aeb720"
    },
    {
      "name": "pkg13_creature_accessor_00b1fdb0",
      "reconstructed": true,
      "va": "0x00b1fdb0"
    },
    {
      "name": "FUN_00b3d2a0",
      "reconstructed": true,
      "va": "0x00b3d2a0"
    },
    {
      "name": "FUN_00b3d2c0",
      "reconstructed": false,
      "va": "0x00b3d2c0"
    },
    {
      "name": "FUN_00b3d300",
      "reconstructed": true,
      "va": "0x00b3d300"
    },
    {
      "name": "Simulator_cSpaceTrading_Get",
      "reconstructed": true,
      "va": "0x00b3d4d0"
    },
    {
      "name": "FUN_00b8dab0",
      "reconstructed": false,
      "va": "0x00b8dab0"
    },
    {
      "name": "FUN_00b8de30",
      "reconstructed": false,
      "va": "0x00b8de30"
    },
    {
      "name": "Simulator_LookupEmpireByPoliticalId",
      "reconstructed": true,
      "va": "0x00ba9370"
    },
    {
      "name": "FUN_00bba790",
      "reconstructed": false,
      "va": "0x00bba790"
    },
    {
      "name": "FUN_00c31730",
      "reconstructed": false,
      "va": "0x00c31730"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c485b0"
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
    "GameSpace",
    "Space *",
    "SpaceContext",
    "SpaceContext *",
    "SpaceEvent *",
    "cCommEvent",
    "cCommManager",
    "void"
  ],
  "vtables": []
}
```

## 09_state_event_relationships

- State: `missing`
- Provenance: `knowledgegraph/research/semantic-decomp.json, reconstruction/knowledge/index.json`

```json
{
  "runtime": {
    "blocking_reason": null,
    "gates": [],
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
      "name": "address_window_offset_005c65e0",
      "reconstructed": true,
      "va": "0x005c65e0"
    },
    {
      "name": "achievement_progress_update_00676e90",
      "reconstructed": true,
      "va": "0x00676e90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0067dcc0"
    },
    {
      "name": "Simulator_cCommManager_CreateAndDispatchEvent_00aeb720",
      "reconstructed": true,
      "va": "0x00aeb720"
    },
    {
      "name": "pkg13_creature_accessor_00b1fdb0",
      "reconstructed": true,
      "va": "0x00b1fdb0"
    },
    {
      "name": "FUN_00b3d2a0",
      "reconstructed": true,
      "va": "0x00b3d2a0"
    },
    {
      "name": "FUN_00b3d2c0",
      "reconstructed": false,
      "va": "0x00b3d2c0"
    },
    {
      "name": "FUN_00b3d300",
      "reconstructed": true,
      "va": "0x00b3d300"
    },
    {
      "name": "Simulator_cSpaceTrading_Get",
      "reconstructed": true,
      "va": "0x00b3d4d0"
    },
    {
      "name": "FUN_00b8dab0",
      "reconstructed": false,
      "va": "0x00b8dab0"
    },
    {
      "name": "FUN_00b8de30",
      "reconstructed": false,
      "va": "0x00b8de30"
    },
    {
      "name": "Simulator_LookupEmpireByPoliticalId",
      "reconstructed": true,
      "va": "0x00ba9370"
    },
    {
      "name": "FUN_00bba790",
      "reconstructed": false,
      "va": "0x00bba790"
    },
    {
      "name": "FUN_00c31730",
      "reconstructed": false,
      "va": "0x00c31730"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c485b0"
    },
[TRUNCATED]
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "shared_types:Space *,SpaceContext,SpaceContext *",
      "same_calling_convention",
      "direct_xref_neighbor"
    ],
    "package": "PKG-12-SIM-SPACE",
    "score": 14,
    "symbol": "FUN_0102d1b0",
    "va": "0x0102d1b0"
  },
  {
    "match_basis": [
      "shared_types:cCommEvent,cCommManager",
      "direct_xref_neighbor"
    ],
    "package": "PKG-12-SIM-SPACE",
    "score": 9,
    "symbol": "Simulator_cCommManager_CreateAndDispatchEvent_00aeb720",
    "va": "0x00aeb720"
  },
  {
    "match_basis": [
      "shared_types:cCommEvent,cCommManager"
    ],
    "package": "PKG-12-SIM-SPACE",
    "score": 6,
    "symbol": "FUN_00aeb160",
    "va": "0x00aeb160"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-11-H4-HELPER-WAVE3",
    "score": 3,
    "symbol": "address_window_offset_005c65e0",
    "va": "0x005c65e0"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-11-A2-PROGRESSION-ALTERNATIVE",
    "score": 3,
    "symbol": "achievement_progress_update_00676e90",
    "va": "0x00676e90"
  },
  {
    "match_basis": [
      "shared_types:cCommManager"
    ],
    "package": "PKG-12-SIM-SPACE",
    "score": 3,
    "symbol": "FUN_00aea230",
    "va": "0x00aea230"
  },
  {
    "match_basis": [
      "shared_types:cCommEvent"
    ],
    "package": "PKG-12-SIM-SPACE",
    "score": 3,
    "symbol": "FUN_00aea250",
    "va": "0x00aea250"
  },
  {
    "match_basis": [
      "shared_types:cCommEvent"
    ],
    "package": "PKG-12-SIM-SPACE",
    "score": 3,
    "symbol": "FUN_00aea
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg12-space/0102df20.json"
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
        "0x00aeb160",
        "0x00aebe90",
        "0x00aed2c0",
        "0x00c75520",
        "0x00dd5160",
        "0x0102c9e0",
        "0x0102caa0",
        "0x0102cae0",
        "0x0102cc30",
        "0x0102cd90",
        "0x0102ce30",
        "0x0102cf10",
        "0x0102d1b0",
        "0x0102df20",
        "0x01072d40",
        "0x00aeb730"
      ],
      "conflict_id": "LC-006",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "RESOLVED_SUPPORTED",
      "resolution_status": "RESOLVED_SUPPORTED",
      "source": "knowledgegraph/research/conflicts/track-a-type-signature.json",
      "subject": "0x00AEB720 communication wrapper",
      "unresolved_reason": "The exact private wrapper name and the full parameter types are not recoverable from static naming alone; the create-and-dispatch contract is resolved."
    }
  ],
  "unresolved_questions": []
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg12-space/0102df20.json', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg12-space/0102df20.json",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.json"
  ],
  "required_categories": [
    "ABI",
    "CALLS",
    "GLOBALS",
    "FIELDS/OFFSETS",
    "CONSTANTS",
    "CONTROL FLOW",
    "VIRTUAL DISPATCH",
    "RETURN SEMANTICS",
    "EVIDENCE COVERAGE"
  ]
}
```
