# Reconstruction context 0x00d2e490

- Status: `partial`
- Content SHA-256: `a6177c738a7dbe4c395017ab2c4263193ecb757b9222641e9ae42be01a1ccb6b`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00d2e490",
  "phase": "reconstruction",
  "target": "0x00d2e490"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "None",
  "name": "Simulator_cCreatureGameData_GetAbilityMode",
  "package": "PKG-13-SIM-CREATURE-TRIBECIV",
  "subsystem": "Simulator.CreatureProgression",
  "va": "0x00d2e490"
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
  "content_sha256": "836fce75650f1efa4865507b608cdd406c83109e527723036f45f84a965809f0",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00d2e490 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "cdecl-compatible thisless static accessor from RET",
  "hidden_this": false,
  "return_register": "EAX",
  "return_semantics": "Exact full 32-bit word loaded from global 0x0169e394. The staged source keeps the raw word because this function does not normalize it to an enum or boolean.",
  "return_width_bytes": 4,
  "stack_arguments": [],
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
      "va": "0x00d2dd20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d2ffd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d35190"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d491b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d495b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d49820"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d4a4a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d4a930"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00f10bd0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00d2dff1",
      "direction": "in",
      "other": "0x00d2dd20",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d300e2",
      "direction": "in",
      "other": "0x00d2ffd0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d3028d",
      "direction": "in",
      "other": "0x00d2ffd0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d30388",
      "direction": "in",
      "other": "0x00d2ffd0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d304ca",
      "direction": "in",
      "other": "0x00d2ffd0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d30715",
      "direction": "in",
     
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [
    "global:DAT_0169e394",
    "global:raw 32-bit ability-mode word",
    "global:unknown"
  ],
  "types": [
    "None"
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
      "creature_ability_mode_global_observation"
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
      "va": "0x00d2dd20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d2ffd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d35190"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d491b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d495b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d49820"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d4a4a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d4a930"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00f10bd0"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00d2dff1",
      "direction": "in",
      "other": "0x00d2dd20",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d300e2",
      "direction": "in",
      "other": "0x00d2ffd0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d3028d",
      "direction": "in",
      "other": "0x00d2ffd0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d30388",
      "direction": "in",
      "other": "0x00d2ffd0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d304ca",
      "direction": "in",
      "other": "0x00d2ffd0",
      "reference_type": "dir
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
      "shared_types:None",
      "same_calling_convention"
    ],
    "package": "PKG-13-SIM-CREATURE-TRIBECIV",
    "score": 24,
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
    "symbol": "Simulator_cCreatureGameData_GetEvoPointsToNextBrainLevel",
    "va": "0x00d2e380"
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
    "reconstruction/metadata/pkg13-b0-creature-state/00d2e490.json"
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
        "0x00d2e490",
        "0x00d2e4a0",
        "0x0169e394",
        "0x00d2e490",
        "0x00e7a4a0",
        "0x00e7a7c0",
        "0x0169e394",
        "0x00d2e490",
        "0x00d2e490",
        "0x00d2e490",
        "0x00d2e4a0",
        "0x00d2e4a0",
        "0x00d2e4a0",
        "0x00e57460",
        "0x00e57460",
        "0x00e7a7c0"
      ],
      "conflict_id": "ability_mode_callers_and_domain",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
      "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
      "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
      "subject": null,
      "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
    }
  ],
  "unresolved_questions": [
    "No original-process mode transition has been observed.",
    "The complete authoritative AbilityMode value set and invalid-value policy are not proven by this accessor.",
    "The owner and initialization writer of global 0x0169e394 remain unresolved.",
    "ability-mode enum values",
    "creature_ability_mode_global_observation",
    "global owner",
    "runtime mode value"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg13-b0-creature-state/00d2e490.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg13-b0-creature-state/creature_state.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg13-b0-creature-state/creature_state.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg13-b0-creature-state/creature_state_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg13_creature_state/creature_state.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg13-b0-creature-state/00d2e490.json",
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
