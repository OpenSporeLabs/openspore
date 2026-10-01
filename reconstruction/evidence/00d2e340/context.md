# Reconstruction context 0x00d2e340

- Status: `partial`
- Content SHA-256: `30964359037450d4d58fcc1e73a3bbe0a2eb624d4b8eca5fea7e499aca09eda7`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00d2e340",
  "phase": "reconstruction",
  "target": "0x00d2e340"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "None",
  "name": "Simulator_cCreatureGameData_Get_00d2e340",
  "package": "PKG-13-C3-CREATURE-PROGRESSION-WAVE2",
  "subsystem": "Simulator.CreatureProgression",
  "va": "0x00d2e340"
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
  "content_sha256": "7c5bc4f83d208f93e4cee918dab39bc98eea9a6e54d5e821024136f72ef9d76a",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00d2e340 failed: Decompilation did not complete. Reason: ",
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
  "original_bytes": 5048,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"receiver\": false,\n    \"ret_form\": \"RET\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"pointer_like_in_EAX\",\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"RET\"\n  },\n  \"abstained_because\": [\n    \"no_discriminator: no stack-argument read and no positive receiver evidence\"\n  ],\n  \"cleanup\": {\n    \"bytes\": 0,\n    \"confidence\": \"INFERRED\",\n    \"corroboration\": \"not_available\",\n    \"evidence\": \"ret with no immediate, no stack reads\",\n    \"side\": \"caller\"\n  },\n  \"completeness\": \"PARTIAL\",\n  \"conflicts\": [],\n  \"content_sha256\": \"08cdcf75fde5d0ce024a60d54c0abfdbbaedd3ab68a5b98d1d057167b61ee4b5\",\n  \"conventions\": {\n    \"ambiguities\": [],\n    \"calling_convention\": null,\n    \"candidate_conventions\": [\n      \"__cdecl\",\n      \"__stdcall\",\n      \"__thiscall\",\n      \"__fastcall\"\n    ],\n    \"confidence\": \"UNKNOWN\",\n    \"corroboration\": \"not_available\"\n  },\n  \"cross_validation\": {\n    \"agreement\": false,\n    \"ghidra\": \"no_information\",\n    \"ghidra_calling_convention\": null,\n    \"ghidra_parameter_count\": 0,\n    \"persisted\": \"no_information\",\n    \"persisted_calling_convention\": null\n  },\n  \"dispatch\": {\n    \"call_offsets\": [],\n    \"indirect_calls\": 0,\n    \"vtable_shaped_loads\": 0\n  },\n  \"inferences\": [\n    {\n      \"based_on\": [\n        \"obs-0002\"\n      ],\n      \"claim\": \"the caller 
[TRUNCATED]
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
      "va": "0x00c0c630"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d1e930"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d1f650"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d239a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d24070"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e07e70"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00c0c983",
      "direction": "in",
      "other": "0x00c0c630",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d1ec3a",
      "direction": "in",
      "other": "0x00d1e930",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d1ec78",
      "direction": "in",
      "other": "0x00d1e930",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d1f795",
      "direction": "in",
      "other": "0x00d1f650",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d1f7e3",
      "direction": "in",
      "other": "0x00d1f650",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d23cb6",
      "direction": "in",
      "other": "0x00d239a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d23cd2",
      "direction": "in",
      "other": "0x00d239a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d23e37",
      "direction": "
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "None",
    "UNCONDITIONAL_CALL",
    "static storage at 0x0169e370"
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
      "No original-process accessor trace or runtime validation has been run.",
      "Observe the object at 0x0169e370 and its concrete initialization in an original process.",
      "Resolve the concrete caller-side type and lifetime contract before promoting the opaque object model.",
      "gate-creature-game-data-get-00d2e340",
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
      "va": "0x00c0c630"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d1e930"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d1f650"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d239a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d24070"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e07e70"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00c0c983",
      "direction": "in",
      "other": "0x00c0c630",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d1ec3a",
      "direction": "in",
      "other": "0x00d1e930",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d1ec78",
      "direction": "in",
      "other": "0x00d1e930",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d1f795",
      "direction": "in",
      "other": "0x00d1f650",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d1f7e3",
      "direction": "in",
      "other": "0x00d1f650",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d23cb6",
      "direction": "in",
      "other": "0x00d239a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d23cd2",
      "direction": "in",
      "other": "0x00d239a0",
      "reference_t
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
    "symbol": "Simulator_cCreatureGameData_AddEvolutionPoints_raw_00d2e8a0",
    "va": "0x00d2e8a0"
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
    "packa
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
    "reconstruction/metadata/pkg13-c3-creature-progression-wave2/00d2e340.json"
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
    "No original-process accessor trace or runtime validation has been run.",
    "Observe the object at 0x0169e370 and its concrete initialization in an original process.",
    "Resolve the concrete caller-side type and lifetime contract before promoting the opaque object model.",
    "gate-creature-game-data-get-00d2e340",
    "runtime validation not run"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'derived'}, {'mode': 'derived', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'derived'}, {'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-sim-social-world-wave2/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg13-c3-creature-progression-wave2/00d2e340.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg13-c3-creature-progression-wave2/creature_progression_wave2.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg13-c3-creature-progression-wave2/creature_progression_wave2.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg13-c3-creature-progression-wave2/creature_progression_wave2_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg13_c3_creature_progression_wave2/creature_progression_wave2.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg13_c3_creature_progression_wave2/creature_progression_wave2.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg13_c3_creature_progression_wave2/creature_progression_wave2_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg13_c3_creature_progression_wave2/metadata_package_validation.py', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg13-c3-creature-progression-wave2/00d2e340.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/p
[TRUNCATED]
```
