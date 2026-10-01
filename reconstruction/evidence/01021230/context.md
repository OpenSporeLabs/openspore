# Reconstruction context 0x01021230

- Status: `partial`
- Content SHA-256: `3f16c3fe682c27c74ea93937475e640be1a3494c883e341f12106ccc83287ec1`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x01021230",
  "phase": "reconstruction",
  "target": "0x01021230"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "SpacePlayerDataAccessPrefix",
  "name": "FUN_01021230",
  "package": "PKG-01-SHARED-STATE-ROOTS",
  "subsystem": "Simulator.SpacePlayerState",
  "va": "0x01021230"
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
  "content_sha256": "5027f103e4bd679152b8253ec25165658614101c35cb23af29b042872ddd9ba6",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x01021230 failed: Decompilation did not complete. Reason: ",
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
  "return_note": "opaque 32-bit active-star pointer word",
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
      "name": "ProfilePersistenceBoundary_run_candidate_00b28ec0",
      "reconstructed": true,
      "va": "0x00b28ec0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bae130"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bba4b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bcece0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c474b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c5f530"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cd5f70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cfa410"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d43e30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e1a040"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ea5510"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fd9d30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fd9d90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fda5e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fda9f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fdc240"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00b28fa0",
      "direction": "in",
      "other": "0x00b28ec0",
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
    "OpaqueActiveStar",
    "SpacePlayerDataAccessPrefix",
    "opaque 32-bit active-star pointer word"
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
      "Separate static writers and cleanup routines can replace or release the +0x08 slot; use-after-clear or stale-pointer windows remain runtime questions.",
      "The concrete returned object and its lifetime are not established by this accessor.",
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
      "name": "ProfilePersistenceBoundary_run_candidate_00b28ec0",
      "reconstructed": true,
      "va": "0x00b28ec0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bae130"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bba4b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bcece0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c474b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c5f530"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cd5f70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cfa410"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d43e30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e1a040"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ea5510"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fd9d30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fd9d90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fda5e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fda9f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fdc240"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fdc710"
 
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
    "reconstruction/metadata/pkg01-roots/01021230.json"
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
    "Separate static writers and cleanup routines can replace or release the +0x08 slot; use-after-clear or stale-pointer windows remain runtime questions.",
    "The concrete returned object and its lifetime are not established by this accessor.",
    "What concrete star subtype and vtable can the +0x08 word contain?",
    "What lifetime guarantee accompanies use of the borrowed returned pointer?",
    "borrowed-pointer lifetime",
    "concrete star subtype",
    "gate-space-player-data-publication",
    "runtime publication"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-pkg01-roots/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg01-roots/01021230.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg01_roots/space_player_data_accessors.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg01_roots/space_player_data_accessors.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg01_roots/space_player_data_accessors_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg01-roots/01021230.json",
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
