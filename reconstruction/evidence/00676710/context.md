# Reconstruction context 0x00676710

- Status: `partial`
- Content SHA-256: `ed87bf6d12136fb238544e50f2a1e03e2123d2ca1ca48714e5b387b02b5a40ea`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00676710",
  "phase": "reconstruction",
  "target": "0x00676710"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "AchievementManagerWire",
  "name": "achievement_completion_boundary_00676710",
  "package": "PKG-11-A3-ACHIEVEMENT-MISSION-WAVE2",
  "subsystem": "Simulator.Achievements",
  "va": "0x00676710"
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
  "content_sha256": "86efef20f7e58e70c8fa59e8ec9b21f278768864501dad70ed048672a0bad303",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00676710 failed: Decompilation did not complete. Reason: ",
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
  "original_bytes": 19248,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": [\n      \"entry_ESP+0x4\"\n    ],\n    \"ordinary_stack_arguments\": [\n      {\n        \"entry_offset\": \"entry_ESP+0x4\",\n        \"observed\": true,\n        \"ordinal\": 1,\n        \"read\": false,\n        \"size_inferred\": true,\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      }\n    ],\n    \"receiver\": true,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET 0x4\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"integral_in_EAX\",\n    \"saved_registers\": [\n      \"EBP\",\n      \"EBX\",\n      \"EDI\",\n      \"ESI\"\n    ],\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"entry_ESP+0x4\",\n        \"observed\": true,\n        \"ordinal\": 1,\n        \"read\": false,\n        \"size_inferred\": true,\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      }\n    ],\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"RET 0x4\"\n  },\n  \"abstained_because\": [\n    \"flow_not_modelled: the linear ESP walk ends at -12, so the listing is not one path\",\n    \"untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated\",\n    \"frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loa
[TRUNCATED]
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "editor_query_clear_flags_0093db80",
      "reconstructed": true,
      "va": "0x0093db80"
    }
  ],
  "callers": [
    {
      "name": "achievement_progress_update_00676e90",
      "reconstructed": true,
      "va": "0x00676e90"
    },
    {
      "name": "achievement_progress_flag_transition_00676ed0",
      "reconstructed": true,
      "va": "0x00676ed0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00676f20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00676f60"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be41b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bff2d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4b310"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cd8e70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cdbd20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cf7630"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d2b5f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d2e580"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d3cdc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d54330"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00db5e80"
    },
    {
      "name": null,
      "reconstructed": fa
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
    "Opaque sorted range begin",
    "Opaque sorted range end",
    "serializer pointer",
    "std::uint32_t",
    "std::uint8_t gate",
    "std::uint8_t tag"
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
      "gate-achievement-completion-00676710",
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
      "name": "editor_query_clear_flags_0093db80",
      "reconstructed": true,
      "va": "0x0093db80"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": "achievement_progress_update_00676e90",
      "reconstructed": true,
      "va": "0x00676e90"
    },
    {
      "name": "achievement_progress_flag_transition_00676ed0",
      "reconstructed": true,
      "va": "0x00676ed0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00676f20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00676f60"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be41b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bff2d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4b310"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cd8e70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cdbd20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cf7630"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d2b5f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d2e580"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d3cdc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d54330"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00db5e80"
    },
    {
      "name": n
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
    "symbol": "achievement_progress_flag_transition_00676ed0",
    "va": "0x00676ed0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_class",
      "shared_types:AchievementManagerWire",
      "direct_xref_neighbor"
    ],
    "package": "PKG-11-A2-PROGRESSION-ALTERNATIVE",
    "score": 17,
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
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-10-EDITOR-DISPATCH",
    "score": 3,
    "symbol": "editor_query_clear_flags_0093db80",
    "va": "0x0093db80"
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
    "reconstruction/metadata/pkg11-a3-achievement-mission-wave2/00676710.json"
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
        "0x00b28ec0",
        "0x00b294c0",
        "0x00b3d440",
        "0x00b28ec0",
        "0x00675d70",
        "0x00675d70",
        "0x00676710",
        "0x00676660",
        "0x00676710",
        "0x00676660",
        "0x00676c80",
        "0x00676c80",
        "0x00677140",
        "0x00677140",
        "0x00693900",
        "0x00693900"
      ],
      "conflict_id": "persistence_manager_vtable",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The cited producer, consumer, or registration surface is retained, but the complete event-to-message mapping, timing, and payload contract remain unresolved.",
      "resolution_status": "The cited producer, consumer, or registration surface is retained, but the complete event-to-message mapping, timing, and payload contract remain unresolved.",
      "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
      "subject": null,
      "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
    },
    {
      "anchors": [
        "0x00676c80",
        "0x00677140",
        "0x007e6470",
        "0x0212d3e7",
        "0x00676c80",
        "0x0212d3e7",
        "0x00675d70",
        "0x00675d70",
        "0x00676710",
        "0x00676660",
        "0x00676710",
        "0x00676660",
        "0x00676c80",
        "0x00676c80",
        "0x00676c80",
        "0x00677140"
      ],
      "conflict_id": "shutdown_message_semantics",
      "kind": "conflict_ledger",
      "rejected": [],
     
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'derived'}, {'mode': 'derived', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'derived'}, {'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-sim-social-world-wave2/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg11-a3-achievement-mission-wave2/00676710.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg11-a3-achievement-mission-wave2/achievement_mission_wave2.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg11-a3-achievement-mission-wave2/achievement_mission_wave2.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg11_a3_achievement_mission_wave2/achievement_mission_wave2.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg11_a3_achievement_mission_wave2/achievement_mission_wave2.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg11_a3_achievement_mission_wave2/achievement_mission_wave2_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg11-a3-achievement-mission-wave2/00676710.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pk
[TRUNCATED]
```
