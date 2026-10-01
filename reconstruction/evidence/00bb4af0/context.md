# Reconstruction context 0x00bb4af0

- Status: `partial`
- Content SHA-256: `6e21f650f86c6a680c1ab6c16a45960489b5d1594ff3fa73eb08f7fd47a89bd2`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00bb4af0",
  "phase": "reconstruction",
  "target": "0x00bb4af0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueStarManager",
  "name": "FUN_00bb4af0",
  "package": "PKG-14-A2-WORLD-LIFECYCLE-WAVE2",
  "subsystem": "Simulator.StarRegeneration",
  "va": "0x00bb4af0"
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
  "content_sha256": "ebfb532da2d64b7488284e0d53f8be6abea5636cc32332fef07427cdf6c0c646",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00bb4af0 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "thiscall",
  "hidden_this_register": "ECX",
  "hidden_this_type": "OpaqueStarManager*",
  "receiver": "ECX",
  "return": "EAX",
  "return_type": "void",
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "star",
      "position": 1,
      "type": "OpaqueStarRegeneration*"
    },
    {
      "entry_offset": "ESP+0x08",
      "name": "dispatch_word",
      "position": 2,
      "type": "TargetWord"
    }
  ],
  "stack_cleanup_bytes": 8,
  "termination": "RET 0x8"
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "FUN_00b3d380",
      "reconstructed": false,
      "va": "0x00b3d380"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb9b00"
    }
  ],
  "callers": [
    {
      "name": "FUN_00bb57b0",
      "reconstructed": false,
      "va": "0x00bb57b0"
    },
    {
      "name": "FUN_00c31730",
      "reconstructed": false,
      "va": "0x00c31730"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c34ee0"
    },
    {
      "name": "FUN_00c47e20",
      "reconstructed": false,
      "va": "0x00c47e20"
    },
    {
      "name": "FUN_00c59240",
      "reconstructed": false,
      "va": "0x00c59240"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c59540"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c5f770"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01011120"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00bb57c6",
      "direction": "in",
      "other": "0x00bb57b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c31760",
      "direction": "in",
      "other": "0x00c31730",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c35119",
      "direction": "in",
      "other": "0x00c34ee0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c3518b",
      "direction": "in",
      "other": "0x00c34ee0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c4820b",
      "direction": "in",
  
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "OpaqueStarManager",
    "OpaqueStarManager*",
    "OpaqueStarRegeneration*",
    "TargetWord",
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
      "gate-star-regenerate-00bb4af0",
      "runtime validation not run"
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
      "name": "FUN_00b3d380",
      "reconstructed": false,
      "va": "0x00b3d380"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb9b00"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": "FUN_00bb57b0",
      "reconstructed": false,
      "va": "0x00bb57b0"
    },
    {
      "name": "FUN_00c31730",
      "reconstructed": false,
      "va": "0x00c31730"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c34ee0"
    },
    {
      "name": "FUN_00c47e20",
      "reconstructed": false,
      "va": "0x00c47e20"
    },
    {
      "name": "FUN_00c59240",
      "reconstructed": false,
      "va": "0x00c59240"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c59540"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c5f770"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01011120"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00bb57c6",
      "direction": "in",
      "other": "0x00bb57b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c31760",
      "direction": "in",
      "other": "0x00c31730",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c35119",
      "direction": "in",
      "other": "0x00c34ee0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c3518b",
      "direction": "in",
      "other": "0x00c34ee0",
      "reference_type": "
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
      "same_class",
      "shared_types:OpaqueStarManager,OpaqueStarManager*",
      "same_calling_convention"
    ],
    "package": "PKG-14-A2-WORLD-LIFECYCLE-WAVE2",
    "score": 21,
    "symbol": "star_manager_record_to_planet_00bb5b50",
    "va": "0x00bb5b50"
  },
  {
    "match_basis": [
      "same_class",
      "shared_types:OpaqueStarManager,OpaqueStarManager*,TargetWord"
    ],
    "package": "PKG-11-SIM-CORE",
    "score": 14,
    "symbol": "Simulator_LookupEmpireByPoliticalId",
    "va": "0x00ba9370"
  },
  {
    "match_basis": [
      "same_package",
      "same_calling_convention"
    ],
    "package": "PKG-14-A2-WORLD-LIFECYCLE-WAVE2",
    "score": 10,
    "symbol": "planet_record_copy_three_word_key_00b8da30",
    "va": "0x00b8da30"
  },
  {
    "match_basis": [
      "same_class",
      "shared_types:OpaqueStarManager"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 8,
    "symbol": "FUN_00b3d2a0",
    "va": "0x00b3d2a0"
  },
  {
    "match_basis": [
      "shared_types:TargetWord",
      "same_calling_convention"
    ],
    "package": "PKG-RUNTIME-SERVICES-WAVE7",
    "score": 5,
    "symbol": "editor_anim_event_message_post_0059d840",
    "va": "0x0059d840"
  },
  {
    "match_basis": [
      "shared_types:TargetWord",
      "same_calling_convention"
    ],
    "package": "PKG-RUNTIME-SERVICES-WAVE7",
    "score": 5,
    "symbol": "editor_anim_event_message_send_0059d8b0",
    "va": "0x0059d8b0"
  },
  {
    "match_basis": [
      "shared_types:TargetWord",
      "same_calling_convention"
   
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg14_a2_world_lifecycle_wave2/world_lifecycle.cpp",
  "files": [
    "reconstruction/staging/pkg14-a2-world-lifecycle-wave2/world_lifecycle.cpp",
    "reconstruction/staging/pkg14-a2-world-lifecycle-wave2/world_lifecycle.hpp",
    "reconstruction/staging/pkg14-a2-world-lifecycle-wave2/world_lifecycle_model_test.cpp",
    "src/reconstruction/pkg14_a2_world_lifecycle_wave2/world_lifecycle.cpp",
    "src/reconstruction/pkg14_a2_world_lifecycle_wave2/world_lifecycle.hpp",
    "src/reconstruction/pkg14_a2_world_lifecycle_wave2/world_lifecycle_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-sim-social-world-wave2/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg14-a2-world-lifecycle-wave2/00bb4af0.json"
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
        "0x00bb4100",
        "0x00bb42a0",
        "0x00bb4af0",
        "0x00bb4ba0",
        "0x00bb4c90",
        "0x00bb4af0",
        "0x00bb4100",
        "0x00bb42a0",
        "0x00bb4ba0",
        "0x00bb4c90",
        "0x00e7fd00",
        "0x00e74a20",
        "0x00bb42a0",
        "0x00bb4c90",
        "0x00e74a20",
        "0x00e74a20"
      ],
      "conflict_id": "U-004-star-generation-boundary",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "0x00bb4100 and 0x00bb4ba0 are coherent current bodies; SDK addresses 0x00bb42a0 and 0x00bb4c90 are retained as interior/alias candidates. mPlanetCount creation is visible, but append/materialization order is not.",
      "resolution_status": "0x00bb4100 and 0x00bb4ba0 are coherent current bodies; SDK addresses 0x00bb42a0 and 0x00bb4c90 are retained as interior/alias candidates. mPlanetCount creation is visible, but append/materialization order is not.",
      "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
      "subject": null,
      "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
    },
    {
      "anchors": [
        "0x00bb4100",
        "0x00bb42a0",
        "0x00bb4af0",
        "0x00bb4ba0",
        "0x00bb4c90",
        "0x00bba900",
        "0x00bb4af0",
        "0x00bb4100",
        "0x00bb42a0",
        "0x00bb4ba0",
        "0x00bb4c90",
        "0x00bba900",
        "0x00bba900",
        "0x00bba900",
        "0x00c86760",
        "0x00c8b700"
      
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-sim-social-world-wave2/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg14-a2-world-lifecycle-wave2/00bb4af0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg14-a2-world-lifecycle-wave2/world_lifecycle.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg14-a2-world-lifecycle-wave2/world_lifecycle.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg14-a2-world-lifecycle-wave2/world_lifecycle_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg14_a2_world_lifecycle_wave2/world_lifecycle.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg14_a2_world_lifecycle_wave2/world_lifecycle.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg14_a2_world_lifecycle_wave2/world_lifecycle_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/integrated/batch-2026-09-25-sim-social-world-wave2/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg14-a2-world-lifecycle-wave2/00bb4af0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg14-a2-world-lifecycle-wave2/world_lifecycle.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg14-a2-world-lifecycle-wave2/world_lifecycle.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persis
[TRUNCATED]
```
