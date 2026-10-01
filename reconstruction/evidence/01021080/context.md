# Reconstruction context 0x01021080

- Status: `partial`
- Content SHA-256: `2e93e1379158cc0d7dcfa8b97018e1115a447c6ce9b1522a04519f9e42b05573`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x01021080",
  "phase": "reconstruction",
  "target": "0x01021080"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "SpacePlayerDataAccessPrefix",
  "name": "FUN_01021080",
  "package": "PKG-01-SHARED-STATE-ROOTS",
  "subsystem": "Simulator.SpacePlayerState",
  "va": "0x01021080"
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
  "content_sha256": "cd807ab82663773ee934b4b22df61a47984db79e5bf92bd037155122db62c5b7",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x01021080 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "cdecl-compatible no-argument accessor",
  "return_note": "enum word",
  "return_register": "EAX",
  "return_type": "SpaceContext",
  "return_width_bytes": 4,
  "stack_cleanup_bytes": 0
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
      "va": "0x00ad23c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00adbca0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae73e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae9c90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aeb3e0"
    },
    {
      "name": "ProfilePersistenceBoundary_run_candidate_00b28ec0",
      "reconstructed": true,
      "va": "0x00b28ec0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b33130"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b35300"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b444c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b4a720"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b4c270"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b5ba30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b5ce70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b5e3f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b60110"
    },
    {
      "name": "app_simulator_mode_bridge_00b63510",
      "reconstructed": true,
      "va": "0x00b63510"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00ad2484",
      "direction": "in
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [
    "global:Simulator::sSpacePlayerData at 0x016dda8c"
  ],
  "types": [
    "SpaceContext enum word",
    "SpaceContextValue",
    "SpacePlayerDataAccessPrefix"
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
      "No trace establishes when the published global is valid during initialization or teardown.",
      "Static evidence does not establish runtime context-transition ordering.",
      "Whole-object finalization for Simulator::sSpacePlayerData remains unresolved; this accessor does not establish ownership.",
      "gate-space-player-data-publication"
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
      "va": "0x00ad23c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00adbca0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae73e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae9c90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aeb3e0"
    },
    {
      "name": "ProfilePersistenceBoundary_run_candidate_00b28ec0",
      "reconstructed": true,
      "va": "0x00b28ec0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b33130"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b35300"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b444c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b4a720"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b4c270"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b5ba30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b5ce70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b5e3f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b60110"
    },
    {
      "name": "app_simulator_mode_bridge_00b63510",
      "reconstructed": true,
      "va": "0x00b63510"
    },
    {
      "name": null,
      "reconstructed": fa
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
      "shared_types:SpacePlayerDataAccessPrefix",
      "same_calling_convention"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 24,
    "symbol": "FUN_01021230",
    "va": "0x01021230"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "shared_types:SpacePlayerDataAccessPrefix",
      "same_calling_convention"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 19,
    "symbol": "FUN_01021260",
    "va": "0x01021260"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "shared_types:SpacePlayerDataAccessPrefix",
      "same_calling_convention"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 19,
    "symbol": "FUN_010212a0",
    "va": "0x010212a0"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 8,
    "symbol": "FUN_00b3d2a0",
    "va": "0x00b3d2a0"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 8,
    "symbol": "FUN_00b3d300",
    "va": "0x00b3d300"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 8,
    "symbol": "FUN_00b3d3a0",
    "va": "0x00b3d3a0"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 8,
    "symbol": "FUN_00b3d400",
    "va": "0x00b3d400"
  },
  {
    "match_basis": [
      "same_package"
    ],
    
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg01_roots/space_player_data_accessors.cpp",
  "files": [
    "src/reconstruction/pkg01_roots/space_player_data_accessors.cpp",
    "src/reconstruction/pkg01_roots/space_player_data_accessors.hpp",
    "src/reconstruction/pkg01_roots/space_player_data_accessors_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-pkg01-roots/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg01-roots/01021080.json"
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
        "0x00c341a0",
        "0x00c34ee0",
        "0x00c35240",
        "0x00c8d060",
        "0x00c34ee0",
        "0x00c35240",
        "0x00c3ae70",
        "0x00c3dae0",
        "0x01001360",
        "0x01001360",
        "0x01021080",
        "0x01021080",
        "0x01021300",
        "0x01021300",
        "0x01021960",
        "0x01021960"
      ],
      "conflict_id": "ownership_field_write_order",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The resource seam and cited call boundary are retained, but original ownership, priority, cache, failure, and load-order semantics are unresolved.",
      "resolution_status": "The resource seam and cited call boundary are retained, but original ownership, priority, cache, failure, and load-order semantics are unresolved.",
      "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
      "subject": null,
      "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
    },
    {
      "anchors": [
        "0x00c34ee0",
        "0x00c34ee0",
        "0x00c35240",
        "0x00c3ae70",
        "0x00c3dae0",
        "0x01001360",
        "0x01001360",
        "0x01021080",
        "0x01021080",
        "0x01021300",
        "0x01021300",
        "0x01021960",
        "0x01021960",
        "0x01021d40",
        "0x01021d40",
        "0x01021d40"
      ],
      "conflict_id": "planet_ownership_projection",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The 
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-pkg01-roots/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg01-roots/01021080.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg01_roots/space_player_data_accessors.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg01_roots/space_player_data_accessors.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg01_roots/space_player_data_accessors_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/integrated/batch-2026-09-25-pkg01-roots/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg01-roots/01021080.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg01_roots/space_player_data_accessors.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg01_roots/space_player_data_accessors.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg01_roots/s
[TRUNCATED]
```
