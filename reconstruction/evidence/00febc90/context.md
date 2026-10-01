# Reconstruction context 0x00febc90

- Status: `partial`
- Content SHA-256: `e839672146d7b383d594d935138813998e60350481cd2f84a6087f0079c799f5`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00febc90",
  "phase": "reconstruction",
  "target": "0x00febc90"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "MissionManagerWire",
  "name": "mission_track_predicate_00febc90",
  "package": "PKG-11-A2-PROGRESSION-ALTERNATIVE",
  "subsystem": "Simulator.MissionTracking",
  "va": "0x00febc90"
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
  "content_sha256": "1a2018faa28fdd4050d79bf09cc5edf66862ef2f0ea99225aeecfa0c9bb66277",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00febc90 failed: Decompilation did not complete. Reason: ",
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
  "original_bytes": 9129,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": [\n      \"entry_ESP+0x8\"\n    ],\n    \"ordinary_stack_arguments\": [\n      {\n        \"entry_offset\": \"entry_ESP+0x8\",\n        \"observed\": true,\n        \"ordinal\": 2,\n        \"read\": false,\n        \"size_inferred\": false,\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      }\n    ],\n    \"receiver\": true,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET 0x8\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"pointer_like_in_EAX\",\n    \"saved_registers\": [\n      \"ESI\"\n    ],\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"entry_ESP+0x8\",\n        \"observed\": true,\n        \"ordinal\": 2,\n        \"read\": false,\n        \"size_inferred\": false,\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      }\n    ],\n    \"stack_cleanup_bytes\": 8,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"RET 0x8\"\n  },\n  \"abstained_because\": [\n    \"flow_not_modelled: the linear ESP walk ends at +8, so the listing is not one path\"\n  ],\n  \"cleanup\": {\n    \"bytes\": 8,\n    \"confidence\": \"OBSERVED\",\n    \"corroboration\": \"not_available\",\n    \"evidence\": \"ret 0x8\",\n    \"side\": \"callee\"\n  },\n  \"completeness\": \"CORE_RESOLVED\",\n  \"conflicts\": [],\n  \"content_sha2
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
      "va": "0x00feed30"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00feefc2",
      "direction": "in",
      "other": "0x00feed30",
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
    "MissionTrackRecordStorage",
    "Opaque",
    "opaque 32-bit identity/borrowed target",
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
      "gate-mission-track-decision-00febc90",
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
      "va": "0x00feed30"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00feefc2",
      "direction": "in",
      "other": "0x00feed30",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 1,
  "fan_out": 0,
  "manifest_callees": [
    "0x01002bd0",
    "0x00bfc5f0",
    "0x00fe4180",
    "0x01021300",
    "0x00c317a0"
  ],
  "manifest_callers": [
    "0x00feed30"
  ],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0585",
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
      "same_package",
      "same_class",
      "shared_types:MissionManagerWire"
    ],
    "package": "PKG-11-A2-PROGRESSION-ALTERNATIVE",
    "score": 16,
    "symbol": "mission_manager_operation_00fee310",
    "va": "0x00fee310"
  },
  {
    "match_basis": [
      "same_class",
      "shared_types:MissionManagerWire,Opaque"
    ],
    "package": "PKG-11-A3-ACHIEVEMENT-MISSION-WAVE2",
    "score": 11,
    "symbol": "mission_manager_record_init_00fec3c0",
    "va": "0x00fec3c0"
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
    "package": "PKG-UTFWIN-LAYOUT-WAVE6",
    "score": 3,
    "symbol": "pkg_utfwin_layout_wave6_00967e80",
    "va": "0x00967e80"
  },
  {
    "match_basis": [
      "shared_types:Opaque"
    ],
    "package": "PKG-UTFWIN-EFFECTS-WAVE6",
    "score": 3,
    "symbol": "utfwin_0096ffc0",
    "va": "0x0096ffc0"
  },
  {
    "match_basis": [
      "shared_types:Opaque"
    ],
    "package": "PKG-UTFWIN-EFFECTS-WAVE6",
    "score": 3,
    "symbol": "utfwin_0097e550",
    "va": "0x0097e550"
  },
  {
    "match_basis": [
      "shared_types:Opaque"
    ],
    "package": "PKG-UTFWIN-EFFECTS-WAVE6",
    "score": 3,
    "symbol": "utf
[TRUNCATED]
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
    "reconstruction/metadata/pkg11-a2-progression-alt/00febc90.json"
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
    "gate-mission-track-decision-00febc90",
    "runtime validation not run"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'derived'}, {'mode': 'derived', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'derived'}, {'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-sim-social-world-wave1/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg11-a2-progression-alt/00febc90.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg11-a2-progression-alt/progression_alt.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg11-a2-progression-alt/progression_alt.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg11_a2_progression_alt/progression_alt.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg11_a2_progression_alt/progression_alt.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg11_a2_progression_alt/progression_alt_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg11-a2-progression-alt/00febc90.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg11-a2-pro
[TRUNCATED]
```
