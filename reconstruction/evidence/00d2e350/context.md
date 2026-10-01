# Reconstruction context 0x00d2e350

- Status: `partial`
- Content SHA-256: `185dffb7abd8ccf635e90c6e1ab1975e82a7a63f2f89beeeb2bafff52e40b4bb`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00d2e350",
  "phase": "reconstruction",
  "target": "0x00d2e350"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "None",
  "name": "Simulator_cCreatureGameData_GetEvolutionPoints",
  "package": "PKG-13-SIM-CREATURE-TRIBECIV",
  "subsystem": "Simulator.CreatureProgression",
  "va": "0x00d2e350"
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
  "content_sha256": "590bf687c76a01328508477beffa522ada247bff8b0235a8e4afbb8126f4680c",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00d2e350 failed: Decompilation did not complete. Reason: ",
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
  "return_register": "ST0",
  "return_semantics": "Exact four-byte float value loaded from the global slot 0x0169e398; no conversion, clamp, sentinel, or default occurs.",
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
      "va": "0x00d35190"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d39670"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d40230"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d45530"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00d2ddcc",
      "direction": "in",
      "other": "0x00d2dd20",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d3551a",
      "direction": "in",
      "other": "0x00d35190",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d3973d",
      "direction": "in",
      "other": "0x00d39670",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d4030c",
      "direction": "in",
      "other": "0x00d40230",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d45654",
      "direction": "in",
      "other": "0x00d45530",
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
  "globals": [
    "global:DAT_0169e398",
    "global:float",
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
      "creature_evolution_points_global_observation"
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
      "va": "0x00d35190"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d39670"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d40230"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d45530"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00d2ddcc",
      "direction": "in",
      "other": "0x00d2dd20",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d3551a",
      "direction": "in",
      "other": "0x00d35190",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d3973d",
      "direction": "in",
      "other": "0x00d39670",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d4030c",
      "direction": "in",
      "other": "0x00d40230",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d45654",
      "direction": "in",
      "other": "0x00d45530",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 5,
  "fan_out": 0,
  "manifest_callees": [],
  "manifest_callers": [
    "0x00d2dd20",
    "0x00d35190",
    "0x00d39670",
    "0x00d40230",
    "0x00d45530"
  ],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0499",
    "size": 1
  },
  "vtable_reference_
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
    "symbol": "Simulator_cCreatureGameData_GetAbilityMode",
    "va": "0x00d2e490"
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
    "reconstruction/metadata/pkg13-b0-creature-state/00d2e350.json"
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
      "resolution": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
      "resolution_status": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
      "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
      "subject": null,
      "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
    },
    {
      "anchors": [
        "0x00594b10",
        "0x00594b10",
        "0x00596da0",
        "0x00596da0",
        "0x00597390",
        "0x00597390",
        "0x00597400",
        "0x00597400",
        "0x00598db0",
        "0x00598db0",
        "0x00598e90",
        "0x00598e90",
        "0x00599440",
        "0x00599440",
        "0x00d2e350",
        "0x00d2e350"
      ],
      "conflict_id": "cell_progression_semantics",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The declared state surface is retained, but the comple
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg13-b0-creature-state/00d2e350.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg13-b0-creature-state/creature_state.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg13-b0-creature-state/creature_state.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg13-b0-creature-state/creature_state_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg13_creature_state/creature_state.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg13-b0-creature-state/00d2e350.json",
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
