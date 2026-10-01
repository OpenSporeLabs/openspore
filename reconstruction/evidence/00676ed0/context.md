# Reconstruction context 0x00676ed0

- Status: `partial`
- Content SHA-256: `dca6949bb0efad3d6860d2cd501566af8416c4b50ae53ac0fd481651f10b90b6`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00676ed0",
  "phase": "reconstruction",
  "target": "0x00676ed0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "AchievementManagerWire",
  "name": "achievement_progress_flag_transition_00676ed0",
  "package": "PKG-11-A3-ACHIEVEMENT-MISSION-WAVE2",
  "subsystem": "Simulator.Achievements",
  "va": "0x00676ed0"
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
  "content_sha256": "771accbdc795a762add5ddc3490ae532197932d2238c4a333954a9130283fb9a",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00676ed0 failed: Decompilation did not complete. Reason: ",
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
  "original_bytes": 11294,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": [\n      \"entry_ESP+0x4\",\n      \"entry_ESP+0x8\"\n    ],\n    \"ordinary_stack_arguments\": [\n      {\n        \"entry_offset\": \"entry_ESP+0x4\",\n        \"observed\": true,\n        \"ordinal\": 1,\n        \"read\": false,\n        \"size_inferred\": false,\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      },\n      {\n        \"entry_offset\": \"entry_ESP+0x8\",\n        \"observed\": true,\n        \"ordinal\": 2,\n        \"read\": false,\n        \"size_inferred\": false,\n        \"sizes\": [\n          1\n        ],\n        \"written\": false\n      }\n    ],\n    \"receiver\": true,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET 0xc\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"unclassified_in_EAX\",\n    \"saved_registers\": [\n      \"EDI\",\n      \"ESI\"\n    ],\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"entry_ESP+0x4\",\n        \"observed\": true,\n        \"ordinal\": 1,\n        \"read\": false,\n        \"size_inferred\": false,\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      },\n      {\n        \"entry_offset\": \"entry_ESP+0x8\",\n        \"observed\": true,\n        \"ordinal\": 2,\n        \"read\": false,\n        \"size_inferred\": false,\n        \"sizes\": [\n          1\n 
[TRUNCATED]
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "achievement_completion_boundary_00676710",
      "reconstructed": true,
      "va": "0x00676710"
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005a9200"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c07480"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cd4280"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cfbc10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d43e30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e82cf0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fda750"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x005a9452",
      "direction": "in",
      "other": "0x005a9200",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c07bd6",
      "direction": "in",
      "other": "0x00c07480",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00cd43a6",
      "direction": "in",
      "other": "0x00cd4280",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00cfc029",
      "direction": "in",
      "other": "0x00cfbc10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d440f5",
      "direction": "in",
      "other": "0x00d43e30",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d453d0",
      "direction": "in",
      "other": "0x00d43e30",
      "reference_type": "
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "AchievementManagerWire",
    "std::uint32_t",
    "std::uint32_t flags",
    "std::uint32_t progress flags",
    "std::uint8_t",
    "std::uint8_t gate"
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
      "gate-achievement-progress-flags-00676ed0",
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
      "name": "achievement_completion_boundary_00676710",
      "reconstructed": true,
      "va": "0x00676710"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005a9200"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c07480"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cd4280"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cfbc10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d43e30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e82cf0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fda750"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x005a9452",
      "direction": "in",
      "other": "0x005a9200",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c07bd6",
      "direction": "in",
      "other": "0x00c07480",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00cd43a6",
      "direction": "in",
      "other": "0x00cd4280",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00cfc029",
      "direction": "in",
      "other": "0x00cfbc10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d440f5",
      "direction": "in",
      "other": "0x00d43e30",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d45
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
      "shared_types:AchievementManagerWire,std::uint8_t gate",
      "direct_xref_neighbor"
    ],
    "package": "PKG-11-A3-ACHIEVEMENT-MISSION-WAVE2",
    "score": 28,
    "symbol": "achievement_completion_boundary_00676710",
    "va": "0x00676710"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_class",
      "shared_types:AchievementManagerWire"
    ],
    "package": "PKG-11-A2-PROGRESSION-ALTERNATIVE",
    "score": 14,
    "symbol": "achievement_progress_update_00676e90",
    "va": "0x00676e90"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "PKG-11-A3-ACHIEVEMENT-MISSION-WAVE2",
    "score": 8,
    "symbol": "mission_manager_record_init_00fec3c0",
    "va": "0x00fec3c0"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg11_a3_achievement_mission_wave2/achievement_mission_wave2.cpp",
  "files": [
    "reconstruction/staging/pkg11-a3-achievement-mission-wave2/achievement_mission_wave2.cpp",
    "reconstruction/staging/pkg11-a3-achievement-mission-wave2/achievement_mission_wave2.hpp",
    "src/reconstruction/pkg11_a3_achievement_mission_wave2/achievement_mission_wave2.cpp",
    "src/reconstruction/pkg11_a3_achievement_mission_wave2/achievement_mission_wave2.hpp",
    "src/reconstruction/pkg11_a3_achievement_mission_wave2/achievement_mission_wave2_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-sim-social-world-wave2/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg11-a3-achievement-mission-wave2/00676ed0.json"
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
    "gate-achievement-progress-flags-00676ed0",
    "runtime validation not run"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'derived'}, {'mode': 'derived', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'derived'}, {'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-sim-social-world-wave2/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg11-a3-achievement-mission-wave2/00676ed0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg11-a3-achievement-mission-wave2/achievement_mission_wave2.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg11-a3-achievement-mission-wave2/achievement_mission_wave2.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg11_a3_achievement_mission_wave2/achievement_mission_wave2.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg11_a3_achievement_mission_wave2/achievement_mission_wave2.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg11_a3_achievement_mission_wave2/achievement_mission_wave2_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg11-a3-achievement-mission-wave2/00676ed0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pk
[TRUNCATED]
```
