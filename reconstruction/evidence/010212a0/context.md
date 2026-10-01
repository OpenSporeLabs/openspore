# Reconstruction context 0x010212a0

- Status: `partial`
- Content SHA-256: `047c46c398c8391b87cebd35fd6e7e334a7d726c56140b7752af1739f755f5af`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x010212a0",
  "phase": "reconstruction",
  "target": "0x010212a0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueActivePlanetField13c",
  "name": "FUN_010212a0",
  "package": "PKG-01-SHARED-STATE-ROOTS",
  "subsystem": "Simulator.SpacePlayerState",
  "va": "0x010212a0"
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
  "content_sha256": "f950a1005174188b52abe700fb27ab0672da1c5b9ba29809bd339516192a2dee",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x010212a0 failed: Decompilation did not complete. Reason: ",
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
  "return_note": "opaque 32-bit word loaded from active-planet+0x13c",
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
      "va": "0x00ae5840"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aeb3e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba0770"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba5650"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba57f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba58f3"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba5a60"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bbc670"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bbc6a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bbc870"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bbc950"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bbcda0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bbce00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bbce40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bbe370"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bbe5f0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00ae5874",
      "direction": "in",
      "other": "0x00ae5840",
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
    "ActivePlanetAccessWindow",
    "OpaqueActivePlanetField13c",
    "SpacePlayerDataAccessPrefix",
    "opaque 32-bit word loaded from active-planet+0x13c"
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
      "The concrete +0x13c pointee, reference policy, and lifetime remain unresolved.",
      "The planet can be replaced or released by separate static lifecycle paths; validity of the two-level read and returned pointee remains runtime-gated.",
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
      "va": "0x00ae5840"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aeb3e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba0770"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba5650"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba57f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba58f3"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba5a60"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bbc670"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bbc6a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bbc870"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bbc950"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bbcda0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bbce00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bbce40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bbe370"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bbe5f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bbe850"
    },
    {
      "name": null,
      "reconst
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
    "reconstruction/metadata/pkg01-roots/010212a0.json"
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
    "+0x13c pointee type",
    "Is the +0x13c word always a pointer, and what ownership or lifetime applies to it?",
    "No trace establishes when the published global is valid during initialization or teardown.",
    "The concrete +0x13c pointee, reference policy, and lifetime remain unresolved.",
    "The planet can be replaced or released by separate static lifecycle paths; validity of the two-level read and returned pointee remains runtime-gated.",
    "What concrete type, vtable, and semantic role does active_planet+0x13c represent?",
    "What runtime ordering guarantees publication of the global, planet, and +0x13c pointee?",
    "borrowed-pointer lifetime",
    "gate-space-player-data-publication",
    "runtime publication"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-pkg01-roots/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg01-roots/010212a0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg01_roots/space_player_data_accessors.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg01_roots/space_player_data_accessors.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg01_roots/space_player_data_accessors_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg01-roots/010212a0.json",
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
