# Reconstruction context 0x00d2e8a0

- Status: `partial`
- Content SHA-256: `5998734d43aed60947e790995275a88d4ac0f0db9d35c44e983c263f9fbfc4ab`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00d2e8a0",
  "phase": "reconstruction",
  "target": "0x00d2e8a0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "None",
  "name": "Simulator_cCreatureGameData_AddEvolutionPoints_raw_00d2e8a0",
  "package": "PKG-13-C3-CREATURE-PROGRESSION-WAVE2",
  "subsystem": "Simulator.CreatureProgression",
  "va": "0x00d2e8a0"
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
  "content_sha256": "d6fa7e4a804ce3784d0155053a2f2e88cbb5933e0d27998f427770e52aeffb0c",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00d2e8a0 failed: Decompilation did not complete. Reason: ",
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
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "original_bytes": 13941,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"ordinary_stack_argument_slots\": [\n      \"entry_ESP+0x4\"\n    ],\n    \"ordinary_stack_arguments\": [\n      {\n        \"entry_offset\": \"entry_ESP+0x4\",\n        \"observed\": true,\n        \"ordinal\": 1,\n        \"read\": false,\n        \"size_inferred\": false,\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      }\n    ],\n    \"ret_form\": \"RET\",\n    \"return_register\": \"ST0\",\n    \"return_semantics\": \"float_or_x87_in_ST0\",\n    \"saved_registers\": [\n      \"ESI\"\n    ],\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"entry_ESP+0x4\",\n        \"observed\": true,\n        \"ordinal\": 1,\n        \"read\": false,\n        \"size_inferred\": false,\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      }\n    ],\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"RET\"\n  },\n  \"abstained_because\": [\n    \"flow_not_modelled: the linear ESP walk ends at +12, so the listing is not one path\",\n    \"receiver_not_determinable: ecx_read_without_deref\",\n    \"receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_read_without_deref), and the convention rule that would apply discriminates on receiver absence\"\n  ],\n  \"cleanup\": {\n    \"bytes\": 0,\n    \"confidence\": \"INFERRED\",\n    \"corroboration\": \"not_available\",\n    \"evidence\": \"ret with no immediate\",\n    \"side\": \"caller\"\n 
[TRUNCATED]
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
    },
    {
      "name": "FUN_00b5b800",
      "reconstructed": false,
      "va": "0x00b5b800"
    },
    {
      "name": "FUN_00d38840",
      "reconstructed": false,
      "va": "0x00d38840"
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c07480"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c2ed20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d35190"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d46c30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d71060"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d71780"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d85ad0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d87620"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d9bc70"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00c07a8c",
      "direction": "in",
      "other": "0x00c07480",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c2ee69",
      "direction": "in",
      "other": "0x00c2ed20",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c2ef72",
      "direction": "in",
    
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [
    "global:0x0169e398",
    "global:DAT_01582e54",
    "global:DAT_0169e398",
    "global:float"
  ],
  "types": [
    "DAT_01582e54",
    "DAT_01654c10",
    "DAT_0169e398",
    "None",
    "UNCONDITIONAL_CALL",
    "float",
    "float points",
    "opaque avatar pointer",
    "zero sentinel at 0x01485378",
    "zero word"
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
      "No original-process event trace or runtime validation has been run.",
      "Observe 0x0169e398, 0x01582e54, 0x01654c10, the returned player, the strategy +0x68 receiver, and the +0x54 avatar word in an original process.",
      "Resolve concrete manager, player, avatar, strategy, event, and action ownership before assigning semantic names beyond the raw offsets.",
      "gate-add-evolution-points-00d2e8a0",
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
      "name": "pkg13_creature_accessor_00b1fdb0",
      "reconstructed": true,
      "va": "0x00b1fdb0"
    },
    {
      "name": "FUN_00b3d300",
      "reconstructed": true,
      "va": "0x00b3d300"
    },
    {
      "name": "FUN_00b5b800",
      "reconstructed": false,
      "va": "0x00b5b800"
    },
    {
      "name": "FUN_00d38840",
      "reconstructed": false,
      "va": "0x00d38840"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c07480"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c2ed20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d35190"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d46c30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d71060"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d71780"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d85ad0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d87620"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d9bc70"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00c07a8c",
      "direction": "in",
      "other": "0x00c07480",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c2ee69",
      "direction": "in",
      "other": "0x00c2ed20",
      "reference_type": "di
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
      "shared_types:None,UNCONDITIONAL_CALL"
    ],
    "package": "PKG-13-C3-CREATURE-PROGRESSION-WAVE2",
    "score": 25,
    "symbol": "Simulator_cCreatureGameData_Get_00d2e340",
    "va": "0x00d2e340"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_class",
      "shared_types:None"
    ],
    "package": "PKG-13-SIM-CREATURE-TRIBECIV",
    "score": 14,
    "symbol": "Simulator_cCreatureGameData_GetEvolutionPoints",
    "va": "0x00d2e350"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_class",
      "shared_types:None"
    ],
    "package": "PKG-13-SIM-CREATURE-TRIBECIV",
    "score": 14,
    "symbol": "Simulator_cCreatureGameData_GetEvoPointsToNextBrainLevel",
    "va": "0x00d2e380"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_class",
      "shared_types:None"
    ],
    "package": "PKG-13-SIM-CREATURE-TRIBECIV",
    "score": 14,
    "symbol": "Simulator_cCreatureGameData_GetAbilityMode",
    "va": "0x00d2e490"
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
    "package": "PKG-11-H2-ROO
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg13_c3_creature_progression_wave2/creature_progression_wave2.cpp",
  "files": [
    "reconstruction/staging/pkg13-c3-creature-progression-wave2/creature_progression_wave2.cpp",
    "reconstruction/staging/pkg13-c3-creature-progression-wave2/creature_progression_wave2.hpp",
    "reconstruction/staging/pkg13-c3-creature-progression-wave2/creature_progression_wave2_model_test.cpp",
    "src/reconstruction/pkg13_c3_creature_progression_wave2/creature_progression_wave2.cpp",
    "src/reconstruction/pkg13_c3_creature_progression_wave2/creature_progression_wave2.hpp",
    "src/reconstruction/pkg13_c3_creature_progression_wave2/creature_progression_wave2_model_test.cpp",
    "src/reconstruction/pkg13_c3_creature_progression_wave2/metadata_package_validation.py"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-sim-social-world-wave2/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg13-c3-creature-progression-wave2/00d2e8a0.json"
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
  "original_bytes": 9391,
  "preview": "{\n  \"conflicts\": {\n    \"original_bytes\": 9562,\n    \"preview\": \"[\\n  {\\n    \\\"anchors\\\": [\\n      \\\"0x00d2e380\\\",\\n      \\\"0x00d2e480\\\",\\n      \\\"0x00d2e8a0\\\",\\n      \\\"0x00d39360\\\",\\n      \\\"0x045ab96e\\\",\\n      \\\"0x00d2e480\\\",\\n      \\\"0x00aebe90\\\",\\n      \\\"0x045ab96e\\\",\\n      \\\"0x0067dcd0\\\",\\n      \\\"0x0067dcd0\\\",\\n      \\\"0x007d8420\\\",\\n      \\\"0x007d8420\\\",\\n      \\\"0x007d8cf0\\\",\\n      \\\"0x007d8cf0\\\",\\n      \\\"0x007d8d40\\\",\\n      \\\"0x007d8d40\\\"\\n    ],\\n    \\\"conflict_id\\\": \\\"U-005-evolution-level-promotion\\\",\\n    \\\"kind\\\": \\\"conflict_ledger\\\",\\n    \\\"rejected\\\": [],\\n    \\\"resolution\\\": \\\"0x45ab96e is a concrete action/message value with a guarded dispatch, but its consumer and brain-level/ability promotion are not identified.\\\",\\n    \\\"resolution_status\\\": \\\"0x45ab96e is a concrete action/message value with a guarded dispatch, but its consumer and brain-level/ability promotion are not identified.\\\",\\n    \\\"source\\\": \\\"knowledgegraph/research/conflicts/track-c-state-events.json\\\",\\n    \\\"subject\\\": null,\\n    \\\"unresolved_reason\\\": \\\"Runtime reachability is absent or the required direct body/call path is not recovered.\\\"\\n  },\\n  {\\n    \\\"anchors\\\": [\\n      \\\"0x01037d30\\\",\\n      \\\"0x01037d30\\\",\\n      \\\"0x01037d30\\\",\\n      \\\"0x01037d30\\\",\\n      \\\"0x0103a480\\\",\\n      \\\"0x0103a480\\\",\\n      \\\"0x0103e8e0\\\",\\n      \\\"0x
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'derived'}, {'mode': 'derived', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'derived'}, {'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-sim-social-world-wave2/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg13-c3-creature-progression-wave2/00d2e8a0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg13-c3-creature-progression-wave2/creature_progression_wave2.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg13-c3-creature-progression-wave2/creature_progression_wave2.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg13-c3-creature-progression-wave2/creature_progression_wave2_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg13_c3_creature_progression_wave2/creature_progression_wave2.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg13_c3_creature_progression_wave2/creature_progression_wave2.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg13_c3_creature_progression_wave2/creature_progression_wave2_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg13_c3_creature_progression_wave2/metadata_package_validation.py', 'source_class': 'committed_artifact'}`

```json
{
  "provenance": [
    {
      "mode": "derived",
      "ref": "GhidraMCP /disassemble_function",
      "source_class": "derived"
    },
    {
      "mode": "derived",
      "ref": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
      "source_class": "derived"
    },
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
      "ref": "reconstruction/metadata/pkg13-c3-creature-progression-wave2/00d2e8a0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/p
[TRUNCATED]
```
