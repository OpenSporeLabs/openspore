# Reconstruction context 0x00c86760

- Status: `partial`
- Content SHA-256: `22f8657c284e5cadd9250a116cd2003b2b5857bab2bfd25ccc4b7d472f463c90`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00c86760",
  "phase": "reconstruction",
  "target": "0x00c86760"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "solar_system_load_00c86760",
  "package": "PKG-14-A3-WORLD-WAVE3",
  "subsystem": null,
  "va": "0x00c86760"
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
  "content_sha256": "245dcfc1b3111a730bc567bb5af96eb78560896780f50df7f192bb817c2115fa",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00c86760 failed: Decompilation did not complete. Reason: ",
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
  "hidden_this_type": "OpaqueSolarSystem*",
  "receiver": "ECX",
  "return": "void",
  "return_type": "void",
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "star",
      "position": 1,
      "type": "OpaqueStar*"
    }
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
  "callees": [
    {
      "name": "FUN_00aea5d0",
      "reconstructed": true,
      "va": "0x00aea5d0"
    },
    {
      "name": "FUN_00b3d2a0",
      "reconstructed": true,
      "va": "0x00b3d2a0"
    },
    {
      "name": "FUN_00bba790",
      "reconstructed": false,
      "va": "0x00bba790"
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c8b700"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00c8b75b",
      "direction": "in",
      "other": "0x00c8b700",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c8686d",
      "direction": "out",
      "other": "0x00423650",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c86809",
      "direction": "out",
      "other": "0x00aea5d0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c869c3",
      "direction": "out",
      "other": "0x00b3d2a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c86a16",
      "direction": "out",
      "other": "0x00bab900",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c869ca",
      "direction": "out",
      "other": "0x00bb59b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c8698a",
      "direction": "out",
      "other": "0x00bba790",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c867b6",
      "direction": "out",
      "other": "0x00bd6410",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c86a35",
      "direction": "ou
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [
    "global:0x01579d10"
  ],
  "types": [
    "OpaqueName*",
    "OpaquePlanetManager*",
    "OpaquePlanetVector*",
    "OpaqueSolarSystem*",
    "OpaqueStar*",
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
      "name": "FUN_00aea5d0",
      "reconstructed": true,
      "va": "0x00aea5d0"
    },
    {
      "name": "FUN_00b3d2a0",
      "reconstructed": true,
      "va": "0x00b3d2a0"
    },
    {
      "name": "FUN_00bba790",
      "reconstructed": false,
      "va": "0x00bba790"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c8b700"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00c8b75b",
      "direction": "in",
      "other": "0x00c8b700",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c8686d",
      "direction": "out",
      "other": "0x00423650",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c86809",
      "direction": "out",
      "other": "0x00aea5d0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c869c3",
      "direction": "out",
      "other": "0x00b3d2a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c86a16",
      "direction": "out",
      "other": "0x00bab900",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c869ca",
      "direction": "out",
      "other": "0x00bb59b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c8698a",
      "direction": "out",
      "other": "0x00bba790",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c867b6",
      "direction": "out",
      "other": "0x00bd6410",
      "reference_typ
[TRUNCATED]
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "same_package"
    ],
    "package": "PKG-14-A3-WORLD-WAVE3",
    "score": 8,
    "symbol": "sphere_draw_direction_00b7e560",
    "va": "0x00b7e560"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-12-SIM-SPACE",
    "score": 3,
    "symbol": "FUN_00aea5d0",
    "va": "0x00aea5d0"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 3,
    "symbol": "FUN_00b3d2a0",
    "va": "0x00b3d2a0"
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
    "symbol": "EditorCreatureController_Update_0059b4b0",
    "va": "0x0059b4b0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-EDITOR-RUNTIME-WAVE7",
    "score": 2,
    "symbol": "EditorAnimWorld_GetCreatureController_0059cac0",
    "va": "0x0059cac0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-EDITOR-RUNTIME-WAVE7",
    "score": 2,
    "symbol": "EditorAnimWorld_PlayAnimation_0059cb10",
    "va": "0x0059cb10"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-EDITOR-RUNTIME-WAVE7",
    "score": 2,
    "symbol": "EditorAnimWorld_SetTargetAngle_0059cea0",
    "va": "0x0059cea0"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg14-a3-world-wave3/world_wave3.cpp",
    "reconstruction/staging/pkg14-a3-world-wave3/world_wave3.hpp",
    "reconstruction/staging/pkg14-a3-world-wave3/world_wave3_model_test.cpp",
    "src/reconstruction/pkg14_a3_world_wave3/world_wave3.cpp",
    "src/reconstruction/pkg14_a3_world_wave3/world_wave3.hpp",
    "src/reconstruction/pkg14_a3_world_wave3/world_wave3_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-sim-social-world-wave3/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg14-a3-world-wave3/00c86760.json"
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
      ],
      "conflict_id": "planet_count_materialization",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The generation body increments mPlanetCount while creating cPlanetRecord objects. Lazy materialization and equality with final runtime cPlanets are unresolved.",
      "resolution_status": "The generation body increments mPlanetCount while creating cPlanetRecord objects. Lazy materialization and equality with final runtime cPlanets are unresolved.",
      "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
      "subject": null,
      "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
    }
  ],
  "unresolved_questions": [
    "Runtime population of the three transform words and indexed star-radius table remains outside this worker boundary.",
    "The binary-or-asteroid and asteroid-belt services are preserved as separate unresolved ports.",
    "The concrete owner and domain meaning of the system, star, planet, and materialization services remain opaque.",
    "runtime validation not run"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-sim-social-world-wave3/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg14-a3-world-wave3/00c86760.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg14-a3-world-wave3/world_wave3.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg14-a3-world-wave3/world_wave3.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg14-a3-world-wave3/world_wave3_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg14_a3_world_wave3/world_wave3.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg14_a3_world_wave3/world_wave3.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg14_a3_world_wave3/world_wave3_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/integrated/batch-2026-09-25-sim-social-world-wave3/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg14-a3-world-wave3/00c86760.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg14-a3-world-wave3/world_wave3.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg14-a3-world-wave3/world_wave3.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/sta
[TRUNCATED]
```
