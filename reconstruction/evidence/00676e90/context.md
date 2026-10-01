# Reconstruction context 0x00676e90

- Status: `partial`
- Content SHA-256: `d50e0dda9ae676dd628740260199cb7302139c21863da4a2d7ac1cecca118732`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00676e90",
  "phase": "reconstruction",
  "target": "0x00676e90"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "AchievementManagerWire",
  "name": "achievement_progress_update_00676e90",
  "package": "PKG-11-A2-PROGRESSION-ALTERNATIVE",
  "subsystem": "Simulator.Achievements",
  "va": "0x00676e90"
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
  "content_sha256": "aba72127c2dd78dfa3996c568ea802a4a883bdee35fc70071429beb1c5d435c9",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00676e90 failed: Decompilation did not complete. Reason: ",
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
  "original_bytes": 9550,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": [\n      \"entry_ESP+0x4\"\n    ],\n    \"ordinary_stack_arguments\": [\n      {\n        \"entry_offset\": \"entry_ESP+0x4\",\n        \"observed\": true,\n        \"ordinal\": 1,\n        \"read\": false,\n        \"size_inferred\": false,\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      }\n    ],\n    \"receiver\": true,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET 0x8\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"unclassified_in_EAX\",\n    \"saved_registers\": [\n      \"EDI\",\n      \"ESI\"\n    ],\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"entry_ESP+0x4\",\n        \"observed\": true,\n        \"ordinal\": 1,\n        \"read\": false,\n        \"size_inferred\": false,\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      }\n    ],\n    \"stack_cleanup_bytes\": 8,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"RET 0x8\"\n  },\n  \"abstained_because\": [\n    \"flow_not_modelled: the linear ESP walk ends at +12, so the listing is not one path\"\n  ],\n  \"cleanup\": {\n    \"bytes\": 8,\n    \"confidence\": \"OBSERVED\",\n    \"corroboration\": \"not_available\",\n    \"evidence\": \"ret 0x8\",\n    \"side\": \"callee\"\n  },\n  \"completeness\": \"CORE_RESOLVED\",\n  \"conflicts\": [],\
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
      "va": "0x005802f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0060cf30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0063d2f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0063fd20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0064bcd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b5ce70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba4600"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba46f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba48b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba4f30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c267e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c46b80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4b310"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4da10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cdab10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cdbd20"
    }
  ],
  "edge_rows": [
    {
    
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
    "AchievementRecordWire",
    "std::uint32_t"
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
      "gate-achievement-progress-update",
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
      "va": "0x005802f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0060cf30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0063d2f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0063fd20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0064bcd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b5ce70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba4600"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba46f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba48b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba4f30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c267e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c46b80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4b310"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4da10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cdab10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cdbd20"
    },
 
[TRUNCATED]
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "same_subsystem",
      "same_class",
      "shared_types:AchievementManagerWire",
      "direct_xref_neighbor"
    ],
    "package": "PKG-11-A3-ACHIEVEMENT-MISSION-WAVE2",
    "score": 17,
    "symbol": "achievement_completion_boundary_00676710",
    "va": "0x00676710"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_class",
      "shared_types:AchievementManagerWire"
    ],
    "package": "PKG-11-A3-ACHIEVEMENT-MISSION-WAVE2",
    "score": 14,
    "symbol": "achievement_progress_flag_transition_00676ed0",
    "va": "0x00676ed0"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "PKG-11-A2-PROGRESSION-ALTERNATIVE",
    "score": 8,
    "symbol": "mission_track_predicate_00febc90",
    "va": "0x00febc90"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "PKG-11-A2-PROGRESSION-ALTERNATIVE",
    "score": 8,
    "symbol": "mission_manager_operation_00fee310",
    "va": "0x00fee310"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-12-SIM-SPACE",
    "score": 3,
    "symbol": "FUN_0102d1b0",
    "va": "0x0102d1b0"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg11_a2_progression_alt/progression_alt.cpp",
  "files": [
    "reconstruction/staging/pkg11-a2-progression-alt/progression_alt.cpp",
    "reconstruction/staging/pkg11-a2-progression-alt/progression_alt.hpp",
    "src/reconstruction/pkg11_a2_progression_alt/progression_alt.cpp",
    "src/reconstruction/pkg11_a2_progression_alt/progression_alt.hpp",
    "src/reconstruction/pkg11_a2_progression_alt/progression_alt_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-sim-social-world-wave1/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg11-a2-progression-alt/00676e90.json"
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
        "0x00676e90",
        "0x00676e90",
        "0x00676e50",
        "0x00b31da0",
        "0x006766d0",
        "0x006766b0",
        "0x00676620",
        "0x00b321e0",
        "0x00676c40",
        "0x00b32330",
        "0x00676e90",
        "0x00b32560",
        "0x0067dd90",
        "0x00b63980",
        "0x00b32390",
        "0x00e66280"
      ],
      "conflict_id": "unresolved:knowledgegraph/research/state-machines/additional-domains.json:6",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The cited stream or file boundary is retained, but the complete wire/transaction/round-trip contract is not reconstructed.",
      "resolution_status": "The cited stream or file boundary is retained, but the complete wire/transaction/round-trip contract is not reconstructed.",
      "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
      "subject": null,
      "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
    }
  ],
  "unresolved_questions": [
    "gate-achievement-progress-update",
    "runtime validation not run"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'derived'}, {'mode': 'derived', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'derived'}, {'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-sim-social-world-wave1/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg11-a2-progression-alt/00676e90.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg11-a2-progression-alt/progression_alt.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg11-a2-progression-alt/progression_alt.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg11_a2_progression_alt/progression_alt.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg11_a2_progression_alt/progression_alt.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg11_a2_progression_alt/progression_alt_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/integrated/batch-2026-09-25-sim-social-world-wave1/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg11-a2-progression-alt/00676e90.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg11-a2-pro
[TRUNCATED]
```
