# Reconstruction context 0x00d2e380

- Status: `partial`
- Content SHA-256: `a1b8160791ce64a6a61dcc3a3b8eed38b6e599d7ac8aae483cdb9815ebd3d680`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00d2e380",
  "phase": "reconstruction",
  "target": "0x00d2e380"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "None",
  "name": "Simulator_cCreatureGameData_GetEvoPointsToNextBrainLevel",
  "package": "PKG-13-SIM-CREATURE-TRIBECIV",
  "subsystem": "Simulator.CreatureProgression",
  "va": "0x00d2e380"
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
  "content_sha256": "aaf6cb642045b7646cd3292f1ce6befb6438c671093d92ab0ad3985364b58c80",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00d2e380 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "cdecl-compatible from one stack argument and RET",
  "hidden_this": false,
  "return_register": "ST0",
  "return_semantics": "Returns the selected mutable global float exactly; all levels outside 0 through 3 return positive 0.0F.",
  "return_width_bytes": 4,
  "stack_arguments": [
    {
      "after_push_ecx_offset": "ESP+0x08",
      "entry_offset": "ESP+0x04",
      "observed_use": "Signed comparison with -1, followed by unsigned CMP EAX,3 / JA table bounds check",
      "position": 1,
      "type": "std::int32_t",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 0
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "pkg13_creature_accessor_00b1fdb0",
      "reconstructed": true,
      "va": "0x00b1fdb0"
    },
    {
      "name": "FUN_00b3d300",
      "reconstructed": true,
      "va": "0x00b3d300"
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d2d0b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d2e830"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d3fcf0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00d2d182",
      "direction": "in",
      "other": "0x00d2d0b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d2e861",
      "direction": "in",
      "other": "0x00d2e830",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d3fd13",
      "direction": "in",
      "other": "0x00d3fcf0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d2e399",
      "direction": "out",
      "other": "0x00b1fdb0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d2e392",
      "direction": "out",
      "other": "0x00b3d300",
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
    "BrainLevelVirtualTable",
    "None",
    "OpaqueCreatureGameDataObject",
    "OpaqueNounManager",
    "std::int32_t"
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
      "creature_brain_level_dispatch_observation"
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
      "name": "pkg13_creature_accessor_00b1fdb0",
      "reconstructed": true,
      "va": "0x00b1fdb0"
    },
    {
      "name": "FUN_00b3d300",
      "reconstructed": true,
      "va": "0x00b3d300"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d2d0b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d2e830"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d3fcf0"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00d2d182",
      "direction": "in",
      "other": "0x00d2d0b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d2e861",
      "direction": "in",
      "other": "0x00d2e830",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d3fd13",
      "direction": "in",
      "other": "0x00d3fcf0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d2e399",
      "direction": "out",
      "other": "0x00b1fdb0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d2e392",
      "direction": "out",
      "other": "0x00b3d300",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 3,
  "fan_out": 2,
  "manifest_callees": [
    "0x00b3d300",
    "0x00b1fdb0",
    "vtable+0xd8"
  ],
  "manifest_callers": [
    "0x00d2d0b0",
    "0x00d2e830",
    "0x00d3fcf0"
  ],
  "nearby_reconstructed": [
    "0x00b1
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
      "shared_types:None"
    ],
    "package": "PKG-13-SIM-CREATURE-TRIBECIV",
    "score": 22,
    "symbol": "Simulator_cCreatureGameData_GetEvolutionPoints",
    "va": "0x00d2e350"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "same_class",
      "shared_types:None"
    ],
    "package": "PKG-13-SIM-CREATURE-TRIBECIV",
    "score": 22,
    "symbol": "Simulator_cCreatureGameData_GetAbilityMode",
    "va": "0x00d2e490"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_class",
      "shared_types:None"
    ],
    "package": "PKG-13-C3-CREATURE-PROGRESSION-WAVE2",
    "score": 14,
    "symbol": "Simulator_cCreatureGameData_Get_00d2e340",
    "va": "0x00d2e340"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_class",
      "shared_types:None"
    ],
    "package": "PKG-13-C3-CREATURE-PROGRESSION-WAVE2",
    "score": 14,
    "symbol": "Simulator_cCreatureGameData_AddEvolutionPoints_raw_00d2e8a0",
    "va": "0x00d2e8a0"
  },
  {
    "match_basis": [
      "same_class",
      "shared_types:None"
    ],
    "package": "PKG-11-H2-ROOT-ACCESSORS",
    "score": 8,
    "symbol": "root_accessor_00b3d3b0",
    "va": "0x00b3d3b0"
  },
  {
    "match_basis": [
      "same_class",
      "shared_types:None"
    ],
    "package": "PKG-11-H2-ROOT-ACCESSORS",
    "score": 8,
    "symbol": "root_accessor_00b3d3e0",
    "va": "0x00b3d3e0"
  },
  {
    "match_basis": [
      "same_class",
      "shared_types:None"
    ],
    "package": 
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg13_creature_state/creature_state.cpp",
  "files": [
    "reconstruction/staging/pkg13-b0-creature-state/creature_state.cpp",
    "reconstruction/staging/pkg13-b0-creature-state/creature_state.hpp",
    "reconstruction/staging/pkg13-b0-creature-state/creature_state_test.cpp",
    "src/reconstruction/pkg13_creature_state/creature_state.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg13-b0-creature-state/00d2e380.json"
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
        "0x00d2e380",
        "0x00d2e480",
        "0x00d2e8a0",
        "0x00d39360",
        "0x045ab96e",
        "0x00d2e480",
        "0x00aebe90",
        "0x045ab96e",
        "0x0067dcd0",
        "0x0067dcd0",
        "0x007d8420",
        "0x007d8420",
        "0x007d8cf0",
        "0x007d8cf0",
        "0x007d8d40",
        "0x007d8d40"
      ],
      "conflict_id": "U-005-evolution-level-promotion",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "0x45ab96e is a concrete action/message value with a guarded dispatch, but its consumer and brain-level/ability promotion are not identified.",
      "resolution_status": "0x45ab96e is a concrete action/message value with a guarded dispatch, but its consumer and brain-level/ability promotion are not identified.",
      "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
      "subject": null,
      "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
    },
    {
      "anchors": [
        "0x00fe52c0",
        "0x00fe52c0",
        "0x00d2e350",
        "0x00d2e350",
        "0x00d2e380",
        "0x00d2e380",
        "0x00d2e480",
        "0x00d2e480",
        "0x00d2e8a0",
        "0x00d2e8a0",
        "0x00d3fcf0",
        "0x00d3fcf0",
        "0x00fe52c0",
        "0x00fe52c0",
        "0x00fe52c0",
        "0x00fe52c0"
      ],
      "conflict_id": "badge_state_domain",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The declared state su
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg13-b0-creature-state/00d2e380.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg13-b0-creature-state/creature_state.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg13-b0-creature-state/creature_state.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg13-b0-creature-state/creature_state_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg13_creature_state/creature_state.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/integrated/batch-2026-09-25/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg13-b0-creature-state/00d2e380.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg13-b0-creature-state/creature_state.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg13-b0-creature-state/creature_state.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg
[TRUNCATED]
```
