# Reconstruction context 0x00bb5b50

- Status: `partial`
- Content SHA-256: `d43331df17ee2e3fd097497f81e4f67c883f176976137f253edec2b81a6d236f`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00bb5b50",
  "phase": "reconstruction",
  "target": "0x00bb5b50"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueStarManager",
  "name": "star_manager_record_to_planet_00bb5b50",
  "package": "PKG-14-A2-WORLD-LIFECYCLE-WAVE2",
  "subsystem": "Simulator.StarRecordCache",
  "va": "0x00bb5b50"
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
  "content_sha256": "987cef83092a2d38e8d1fa72714152d473ae949ea1e93e7bb1f6dd3aafb6b359",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00bb5b50 failed: Decompilation did not complete. Reason: ",
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
  "return_register": "EAX",
  "return_type": "OpaqueRecordToPlanetOutput*",
  "stack_arguments": [
    "output",
    "pending_record"
  ],
  "stack_cleanup_bytes": 4,
  "termination": "RET 0x4"
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
      "va": "0x00bba2a0"
    },
    {
      "name": "ProfileSetter_00c33690",
      "reconstructed": true,
      "va": "0x00c33690"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00bba3be",
      "direction": "in",
      "other": "0x00bba2a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c336d9",
      "direction": "in",
      "other": "0x00c33690",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00bb5b63",
      "direction": "out",
      "other": "0x00bb1560",
      "reference_type": "direct-call"
    }
  ],
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
    "OpaqueRecordCache*",
    "OpaqueRecordToPlanetOutput*",
    "OpaqueStarManager",
    "OpaqueStarManager*",
    "OpaqueUninitializedRecordSlot"
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
      "gate-star-record-cache-00bb5b50",
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
  "callees": [],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bba2a0"
    },
    {
      "name": "ProfileSetter_00c33690",
      "reconstructed": true,
      "va": "0x00c33690"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00bba3be",
      "direction": "in",
      "other": "0x00bba2a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c336d9",
      "direction": "in",
      "other": "0x00c33690",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00bb5b63",
      "direction": "out",
      "other": "0x00bb1560",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 2,
  "fan_out": 0,
  "manifest_callees": [
    "0x00bb1560"
  ],
  "manifest_callers": [
    "0x00c33690",
    "0x00bba2a0 cStarRecord__ctor"
  ],
  "nearby_reconstructed": [
    "0x00c33690"
  ],
  "scc": {
    "id": "scc-0420",
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
      "same_class",
      "shared_types:OpaqueStarManager,OpaqueStarManager*",
      "same_calling_convention"
    ],
    "package": "PKG-14-A2-WORLD-LIFECYCLE-WAVE2",
    "score": 21,
    "symbol": "star_regenerate_00bb4af0",
    "va": "0x00bb4af0"
  },
  {
    "match_basis": [
      "same_class",
      "shared_types:OpaqueStarManager,OpaqueStarManager*"
    ],
    "package": "PKG-11-SIM-CORE",
    "score": 11,
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
      "same_calling_convention",
      "direct_xref_neighbor"
    ],
    "package": "PKG-13-E3-EMPIRE-STATE-WAVE2",
    "score": 5,
    "symbol": "ProfileSetter_00c33690",
    "va": "0x00c33690"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-EDITOR-RUNTIME-WAVE7",
    "score": 2,
    "symbol": "EditorCreatureController_SetTargetPosition_0059b0f0",
    "va": "0x0059b0f0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-EDITOR-RUNTIME-WAVE7",
    "score": 2,
    "symbol": "EditorCreatureControl
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
    "reconstruction/metadata/pkg14-a2-world-lifecycle-wave2/00bb5b50.json"
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
        "0x00bb42a0",
        "0x00bb4c90",
        "0x00c932f0",
        "0x00c983c0",
        "0x00bb5b50",
        "0x00bba900",
        "0x00c983c0",
        "0x00c932f0"
      ],
      "conflict_id": "U-005-tribe-population",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
      "resolution_status": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
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
      "resolution_status": "A positive hash-pinned original-process trace is required; st
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-sim-social-world-wave2/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg14-a2-world-lifecycle-wave2/00bb5b50.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg14-a2-world-lifecycle-wave2/world_lifecycle.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg14-a2-world-lifecycle-wave2/world_lifecycle.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg14-a2-world-lifecycle-wave2/world_lifecycle_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg14_a2_world_lifecycle_wave2/world_lifecycle.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg14_a2_world_lifecycle_wave2/world_lifecycle.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg14_a2_world_lifecycle_wave2/world_lifecycle_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg14-a2-world-lifecycle-wave2/00bb5b50.json",
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
