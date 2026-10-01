# Reconstruction context 0x00fec3c0

- Status: `partial`
- Content SHA-256: `5c965c1f243bf4522c84cd940635fa1e9ce84c0e7647fd06e36a77db1608b563`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00fec3c0",
  "phase": "reconstruction",
  "target": "0x00fec3c0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "MissionManagerWire",
  "name": "mission_manager_record_init_00fec3c0",
  "package": "PKG-11-A3-ACHIEVEMENT-MISSION-WAVE2",
  "subsystem": "Simulator.MissionPersistence",
  "va": "0x00fec3c0"
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
  "content_sha256": "fe5fc2027b46ac41c7909963d09d57313b0ab8cc8ad47465e85815d556468299",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00fec3c0 failed: Decompilation did not complete. Reason: ",
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
  "original_bytes": 13371,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"ordinary_stack_argument_slots\": [\n      \"entry_ESP+0x4\",\n      \"entry_ESP+0x8\"\n    ],\n    \"ordinary_stack_arguments\": [\n      {\n        \"confidence\": \"UNKNOWN\",\n        \"entry_offset\": \"entry_ESP+0x4\",\n        \"observed\": true,\n        \"ordinal\": 1,\n        \"read\": false,\n        \"size_inferred\": true,\n        \"sizes\": [\n          1,\n          4\n        ],\n        \"written\": false\n      },\n      {\n        \"entry_offset\": \"entry_ESP+0x8\",\n        \"observed\": true,\n        \"ordinal\": 2,\n        \"read\": false,\n        \"size_inferred\": false,\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      }\n    ],\n    \"ret_form\": \"RET\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"pointer_like_in_EAX\",\n    \"saved_registers\": [\n      \"EBX\",\n      \"ESI\"\n    ],\n    \"stack_arguments\": [\n      {\n        \"confidence\": \"UNKNOWN\",\n        \"entry_offset\": \"entry_ESP+0x4\",\n        \"observed\": true,\n        \"ordinal\": 1,\n        \"read\": false,\n        \"size_inferred\": true,\n        \"sizes\": [\n          1,\n          4\n        ],\n        \"written\": false\n      },\n      {\n        \"entry_offset\": \"entry_ESP+0x8\",\n        \"observed\": true,\n        \"ordinal\": 2,\n        \"read\": false,\n        \"size_inferred\": false,\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      }\n    ],\n    \"stack_cleanup_b
[TRUNCATED]
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [],
  "callers": [],
  "edge_rows": [
    {
      "callsite": "0x00fec41e",
      "direction": "out",
      "other": "0x0093a9a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00fec3ea",
      "direction": "out",
      "other": "0x0093aa70",
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
    "MissionManagerWire",
    "Opaque",
    "const std::uint8_t*",
    "const void* vftable"
  ],
  "vtables": [
    "vtable:0x00000018",
    "vtable:0x00000020"
  ]
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
      "gate-mission-record-init-00fec3c0",
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
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00fec41e",
      "direction": "out",
      "other": "0x0093a9a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00fec3ea",
      "direction": "out",
      "other": "0x0093aa70",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 0,
  "fan_out": 0,
  "manifest_callees": [
    "0x0093aa70",
    "0x0093a9a0"
  ],
  "manifest_callers": [],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0586",
    "size": 1
  },
  "vtable_reference_count": 0
}
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "same_class",
      "shared_types:MissionManagerWire,Opaque"
    ],
    "package": "PKG-11-A2-PROGRESSION-ALTERNATIVE",
    "score": 11,
    "symbol": "mission_track_predicate_00febc90",
    "va": "0x00febc90"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "PKG-11-A3-ACHIEVEMENT-MISSION-WAVE2",
    "score": 8,
    "symbol": "achievement_completion_boundary_00676710",
    "va": "0x00676710"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "PKG-11-A3-ACHIEVEMENT-MISSION-WAVE2",
    "score": 8,
    "symbol": "achievement_progress_flag_transition_00676ed0",
    "va": "0x00676ed0"
  },
  {
    "match_basis": [
      "same_class",
      "shared_types:MissionManagerWire"
    ],
    "package": "PKG-11-A2-PROGRESSION-ALTERNATIVE",
    "score": 8,
    "symbol": "mission_manager_operation_00fee310",
    "va": "0x00fee310"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x00000018"
    ],
    "package": "WAVE6-ENGINE-RUNTIME",
    "score": 4,
    "symbol": "app_system_service_gate_dispatch_007e5f30",
    "va": "0x007e5f30"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x00000020"
    ],
    "package": "PKG-RUNTIME-SERVICES-WAVE7",
    "score": 4,
    "symbol": "app_canvas_get_message_server_00c871d0",
    "va": "0x00c871d0"
  },
  {
    "match_basis": [
      "shared_types:Opaque"
    ],
    "package": "PKG-18-UI-SPACE",
    "score": 3,
    "symbol": "pkg18_text_zoom_rebind_00834fa0",
    "va": "0x00834fa0"
  },
  {
    "match_basis": [
      "shared_types:Opaque"
    ],
    "packag
[TRUNCATED]
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
    "reconstruction/metadata/pkg11-a3-achievement-mission-wave2/00fec3c0.json"
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
    "gate-mission-record-init-00fec3c0",
    "runtime validation not run"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'derived'}, {'mode': 'derived', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'derived'}, {'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-sim-social-world-wave2/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg11-a3-achievement-mission-wave2/00fec3c0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg11-a3-achievement-mission-wave2/achievement_mission_wave2.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg11-a3-achievement-mission-wave2/achievement_mission_wave2.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg11_a3_achievement_mission_wave2/achievement_mission_wave2.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg11_a3_achievement_mission_wave2/achievement_mission_wave2.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg11_a3_achievement_mission_wave2/achievement_mission_wave2_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg11-a3-achievement-mission-wave2/00fec3c0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pk
[TRUNCATED]
```
