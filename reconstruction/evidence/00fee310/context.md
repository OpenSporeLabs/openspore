# Reconstruction context 0x00fee310

- Status: `partial`
- Content SHA-256: `3e0a0ef28a3892508311f9a29059dfc934ec648f842dcda8bacb25ec6a5cb275`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00fee310",
  "phase": "reconstruction",
  "target": "0x00fee310"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "MissionManagerWire",
  "name": "mission_manager_operation_00fee310",
  "package": "PKG-11-A2-PROGRESSION-ALTERNATIVE",
  "subsystem": "Simulator.MissionManagement",
  "va": "0x00fee310"
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
  "content_sha256": "3ff50ccfb64a2a935560e3e28bf050e642bc836eca806665528f25b2c33d7a29",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00fee310 failed: Decompilation did not complete. Reason: ",
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
  "original_bytes": 11231,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"ret_form\": \"RET\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"unclassified_in_EAX\",\n    \"saved_registers\": [\n      \"EDI\",\n      \"ESI\"\n    ],\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"RET\"\n  },\n  \"abstained_because\": [\n    \"receiver_not_determinable: ecx_reassigned_before_deref\",\n    \"esp_alignment_unknown: the entry-relative ESP offset is unknown and there is no frame pointer to fall back on\"\n  ],\n  \"cleanup\": {\n    \"bytes\": 0,\n    \"confidence\": \"INFERRED\",\n    \"corroboration\": \"not_available\",\n    \"evidence\": \"ret with no immediate, no stack reads\",\n    \"side\": \"caller\"\n  },\n  \"completeness\": \"PARTIAL\",\n  \"conflicts\": [],\n  \"content_sha256\": \"d8a7213cf46784e56ced847f88f9e43d1b630168565985331739a979d5c7e513\",\n  \"conventions\": {\n    \"ambiguities\": [\n      \"esp_alignment_unknown\"\n    ],\n    \"calling_convention\": null,\n    \"candidate_conventions\": [\n      \"__cdecl\",\n      \"__stdcall\",\n      \"__thiscall\",\n      \"__fastcall\"\n    ],\n    \"confidence\": \"UNKNOWN\",\n    \"corroboration\": \"not_available\"\n  },\n  \"cross_validation\": {\n    \"agreement\": false,\n    \"ghidra\": \"no_information\",\n    \"ghidra_calling_convention\": null,\n    \"ghidra_parameter_count\": 2,\n    \"persisted\": \"no_information\",\n    \"persisted_calling_convention\": null\n  },\n  \"dispatch\": {\n    \"call_offsets\": [],
[TRUNCATED]
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "pkg11_sim_core_00b21340",
      "reconstructed": true,
      "va": "0x00b21340"
    },
    {
      "name": "FUN_00b3d300",
      "reconstructed": true,
      "va": "0x00b3d300"
    },
    {
      "name": "sporepedia_nop_slot_FUN_00c2e4e0",
      "reconstructed": true,
      "va": "0x00c2e4e0"
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01007430"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x0100751f",
      "direction": "in",
      "other": "0x01007430",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00fee39a",
      "direction": "out",
      "other": "0x00b21340",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00fee37a",
      "direction": "out",
      "other": "0x00b3d300",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00fee314",
      "direction": "out",
      "other": "0x00b3d330",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00fee331",
      "direction": "out",
      "other": "0x00c2e4e0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00fee375",
      "direction": "out",
      "other": "0x00c44f50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00fee325",
      "direction": "out",
      "other": "0x00fed0b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00fee32a",
      "direction": "out",
      "other": "0x00fef670",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "MissionManagerWire",
    "MissionProjectionVectorWire"
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
      "gate-mission-manager-initialization-00fee310",
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
      "name": "pkg11_sim_core_00b21340",
      "reconstructed": true,
      "va": "0x00b21340"
    },
    {
      "name": "FUN_00b3d300",
      "reconstructed": true,
      "va": "0x00b3d300"
    },
    {
      "name": "sporepedia_nop_slot_FUN_00c2e4e0",
      "reconstructed": true,
      "va": "0x00c2e4e0"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01007430"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x0100751f",
      "direction": "in",
      "other": "0x01007430",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00fee39a",
      "direction": "out",
      "other": "0x00b21340",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00fee37a",
      "direction": "out",
      "other": "0x00b3d300",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00fee314",
      "direction": "out",
      "other": "0x00b3d330",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00fee331",
      "direction": "out",
      "other": "0x00c2e4e0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00fee375",
      "direction": "out",
      "other": "0x00c44f50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00fee325",
      "direction": "out",
      "other": "0x00fed0b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00fee32a",
      "direction": "out",
      "other": "0x0
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
      "shared_types:MissionManagerWire"
    ],
    "package": "PKG-11-A2-PROGRESSION-ALTERNATIVE",
    "score": 16,
    "symbol": "mission_track_predicate_00febc90",
    "va": "0x00febc90"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "PKG-11-A2-PROGRESSION-ALTERNATIVE",
    "score": 8,
    "symbol": "achievement_progress_update_00676e90",
    "va": "0x00676e90"
  },
  {
    "match_basis": [
      "same_class",
      "shared_types:MissionManagerWire"
    ],
    "package": "PKG-11-A3-ACHIEVEMENT-MISSION-WAVE2",
    "score": 8,
    "symbol": "mission_manager_record_init_00fec3c0",
    "va": "0x00fec3c0"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-11-SIM-CORE",
    "score": 3,
    "symbol": "pkg11_sim_core_00b21340",
    "va": "0x00b21340"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 3,
    "symbol": "FUN_00b3d300",
    "va": "0x00b3d300"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "pkg-sporepedia-nop-slot",
    "score": 3,
    "symbol": "sporepedia_nop_slot_FUN_00c2e4e0",
    "va": "0x00c2e4e0"
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
    "reconstruction/metadata/pkg11-a2-progression-alt/00fee310.json"
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
        "0x00cc8c90",
        "0x00cc8c90",
        "0x00feb880",
        "0x00feb880",
        "0x00febce0",
        "0x00febce0",
        "0x00fec420",
        "0x00fec420",
        "0x00fee020",
        "0x00fee020",
        "0x00fee260",
        "0x00fee260",
        "0x00fee310",
        "0x00fee310",
        "0x00feebc0",
        "0x00feebc0"
      ],
      "conflict_id": "herd_evolution_transition",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The cited stream or file boundary is retained, but the complete wire/transaction/round-trip contract is not reconstructed.",
      "resolution_status": "The cited stream or file boundary is retained, but the complete wire/transaction/round-trip contract is not reconstructed.",
      "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
      "subject": null,
      "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
    },
    {
      "anchors": [
        "0x00ff3bf0",
        "0x00feb880",
        "0x00feb880",
        "0x00febce0",
        "0x00febce0",
        "0x00fec420",
        "0x00fec420",
        "0x00fee020",
        "0x00fee020",
        "0x00fee260",
        "0x00fee260",
        "0x00fee310",
        "0x00fee310",
        "0x00feebc0",
        "0x00feebc0",
        "0x00ff3bf0"
      ],
      "conflict_id": "mission_reward_payout",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The declared state surface is retained, but the complete wri
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'derived'}, {'mode': 'derived', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'derived'}, {'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-sim-social-world-wave1/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg11-a2-progression-alt/00fee310.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg11-a2-progression-alt/progression_alt.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg11-a2-progression-alt/progression_alt.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg11_a2_progression_alt/progression_alt.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg11_a2_progression_alt/progression_alt.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg11_a2_progression_alt/progression_alt_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg11-a2-progression-alt/00fee310.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg11-a2-pro
[TRUNCATED]
```
