# Reconstruction context 0x01021260

- Status: `partial`
- Content SHA-256: `fc7405fcdb79a5a52b3dd4e504fc0348054ecaf5e58f966f1fc54261599c5ecb`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x01021260",
  "phase": "reconstruction",
  "target": "0x01021260"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "ActivePlanetAccessWindow",
  "name": "FUN_01021260",
  "package": "PKG-01-SHARED-STATE-ROOTS",
  "subsystem": "Simulator.SpacePlayerState",
  "va": "0x01021260"
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
  "content_sha256": "c1df758376726904da08ae8c22543e2448480a7fecb029c3810d9c8f425fd0e2",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x01021260 failed: Decompilation did not complete. Reason: ",
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
  "return_note": "opaque 32-bit active-planet pointer word",
  "return_register": "EAX",
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
      "va": "0x00acc390"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00acc800"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00acd790"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00acf3e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00acf4c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ad4a10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aeb240"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aeb890"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b2a110"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b2bbe0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b2bf10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b2ec80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b2f210"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b2f350"
    },
    {
      "name": "timing_update_body_00b31cc0",
      "reconstructed": true,
      "va": "0x00b31cc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b421b0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00acc39d",
      "direction": "in",
      "other": "0x00acc390",
      "reference_type
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
    "ActivePlanetAccessWindow",
    "SpacePlayerDataAccessPrefix",
    "opaque 32-bit active-planet pointer word"
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
      "Separate static writers and cleanup routines can replace or release the +0x04 slot; stale-pointer and lifetime windows remain runtime questions.",
      "The concrete active-planet object is not established by this accessor.",
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
      "va": "0x00acc390"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00acc800"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00acd790"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00acf3e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00acf4c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ad4a10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aeb240"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aeb890"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b2a110"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b2bbe0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b2bf10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b2ec80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b2f210"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b2f350"
    },
    {
      "name": "timing_update_body_00b31cc0",
      "reconstructed": true,
      "va": "0x00b31cc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b421b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b4c270"
    },
    {
      "nam
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
      "shared_types:ActivePlanetAccessWindow,SpacePlayerDataAccessPrefix",
      "same_calling_convention"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 22,
    "symbol": "FUN_010212a0",
    "va": "0x010212a0"
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
    "symbol": "FUN_01021080",
    "va": "0x01021080"
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
    "symbol": "FUN_01021230",
    "va": "0x01021230"
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
    "reconstruction/metadata/pkg01-roots/01021260.json"
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
    "No trace establishes when the published global is valid during initialization or teardown.",
    "Separate static writers and cleanup routines can replace or release the +0x04 slot; stale-pointer and lifetime windows remain runtime questions.",
    "The concrete active-planet object is not established by this accessor.",
    "What concrete planet subtype and vtable can the +0x04 word contain?",
    "What lifetime guarantee accompanies use of the borrowed returned pointer?",
    "borrowed-pointer lifetime",
    "concrete planet subtype",
    "gate-space-player-data-publication",
    "runtime publication"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-pkg01-roots/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg01-roots/01021260.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg01_roots/space_player_data_accessors.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg01_roots/space_player_data_accessors.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg01_roots/space_player_data_accessors_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg01-roots/01021260.json",
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
