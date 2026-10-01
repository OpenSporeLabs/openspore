# Reconstruction context 0x007d85b0

- Status: `partial`
- Content SHA-256: `d11bff9fc486e7d2050818661cd612e94d5513e29ed7255e9f5056437c9f145f`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x007d85b0",
  "phase": "reconstruction",
  "target": "0x007d85b0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueGameModeState",
  "name": "app_mode_activate_007d85b0",
  "package": "PKG-GAME-MODE-WAVE7",
  "subsystem": "App.GameMode",
  "va": "0x007d85b0"
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
  "content_sha256": "a184ba502b2c5a1eaf1c82bcda16be6e2b61edf02a8293e348e045454f055326",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x007d85b0 failed: Decompilation did not complete. Reason: ",
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
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "ordinary_stack_arguments": [
    "int32 index"
  ],
  "receiver": "AppModeRegistry* in ECX",
  "ret_form": "RET 0x4",
  "return": "void"
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
      "name": "app_mode_activate_index_007d8c80",
      "reconstructed": true,
      "va": "0x007d8c80"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x007d8ca5",
      "direction": "in",
      "other": "0x007d8c80",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x007d8690",
      "direction": "out",
      "other": "0x00421cf0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x007d8715",
      "direction": "out",
      "other": "0x00421cf0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x007d8626",
      "direction": "out",
      "other": "0x00883860",
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
    "OpaqueGameModeState"
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
      "Observe concrete mode identities, notification manager publication, vtable targets, and runtime transition reachability; runtime validation is not run."
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
      "name": "app_mode_activate_index_007d8c80",
      "reconstructed": true,
      "va": "0x007d8c80"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x007d8ca5",
      "direction": "in",
      "other": "0x007d8c80",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x007d8690",
      "direction": "out",
      "other": "0x00421cf0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x007d8715",
      "direction": "out",
      "other": "0x00421cf0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x007d8626",
      "direction": "out",
      "other": "0x00883860",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 1,
  "fan_out": 0,
  "manifest_callees": [],
  "manifest_callers": [],
  "nearby_reconstructed": [
    "0x007d8c80"
  ],
  "scc": {
    "id": "scc-0244",
    "size": 1
  },
  "vtable_reference_count": 2
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
      "same_subsystem",
      "same_class",
      "shared_types:OpaqueGameModeState",
      "same_calling_convention",
      "direct_xref_neighbor"
    ],
    "package": "PKG-GAME-MODE-WAVE7",
    "score": 27,
    "symbol": "app_mode_activate_index_007d8c80",
    "va": "0x007d8c80"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "same_class",
      "shared_types:OpaqueGameModeState",
      "same_calling_convention"
    ],
    "package": "PKG-GAME-MODE-WAVE7",
    "score": 24,
    "symbol": "app_mode_activate_by_name_007d8360",
    "va": "0x007d8360"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "same_class",
      "shared_types:OpaqueGameModeState",
      "same_calling_convention"
    ],
    "package": "PKG-GAME-MODE-WAVE7",
    "score": 24,
    "symbol": "strategy_request_ready_00b5b840",
    "va": "0x00b5b840"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "same_class",
      "shared_types:OpaqueGameModeState",
      "same_calling_convention"
    ],
    "package": "PKG-GAME-MODE-WAVE7",
    "score": 24,
    "symbol": "strategy_queue_primary_00b5b880",
    "va": "0x00b5b880"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "same_class",
      "shared_types:OpaqueGameModeState",
      "same_calling_convention"
    ],
    "package": "PKG-GAME-MODE-WAVE7",
    "score": 24,
    "symbol": "strategy_queue_secondary_00b5b8a0",
    "va": "0x00b5b8a0"
  },
  {
    "match_basis": [
      "same_packa
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg_game_mode_wave7/game_mode_wave7.cpp",
  "files": [
    "src/reconstruction/pkg_game_mode_wave7/game_mode_wave7.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave7/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-game-mode-wave7/007d85b0.json"
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
  "original_bytes": 9160,
  "preview": "{\n  \"conflicts\": {\n    \"original_bytes\": 9653,\n    \"preview\": \"[\\n  {\\n    \\\"anchors\\\": [\\n      \\\"0x007d85b0\\\",\\n      \\\"0x007d8c80\\\",\\n      \\\"0x01412598\\\",\\n      \\\"0x01412598\\\",\\n      \\\"0x007d8c80\\\",\\n      \\\"0x007d8c80\\\",\\n      \\\"0x007d85b0\\\",\\n      \\\"0x0212d3e7\\\",\\n      \\\"0x022d1adc\\\",\\n      \\\"0x007d8060\\\",\\n      \\\"0x007d8060\\\",\\n      \\\"0x007d8360\\\",\\n      \\\"0x007d8360\\\",\\n      \\\"0x007d85b0\\\",\\n      \\\"0x007d85b0\\\",\\n      \\\"0x007d8c30\\\"\\n    ],\\n    \\\"conflict_id\\\": \\\"Q-APP-ID-CATALOG\\\",\\n    \\\"kind\\\": \\\"conflict_ledger\\\",\\n    \\\"rejected\\\": [],\\n    \\\"resolution\\\": \\\"Registration operations, mode IDs, and several named event surfaces are concrete. The complete ID catalog, payload schema, and producer/consumer map are not recovered.\\\",\\n    \\\"resolution_status\\\": \\\"Registration operations, mode IDs, and several named event surfaces are concrete. The complete ID catalog, payload schema, and producer/consumer map are not recovered.\\\",\\n    \\\"source\\\": \\\"knowledgegraph/research/conflicts/track-c-state-events.json\\\",\\n    \\\"subject\\\": null,\\n    \\\"unresolved_reason\\\": \\\"Runtime reachability is absent or the required direct body/call path is not recovered.\\\"\\n  },\\n  {\\n    \\\"anchors\\\": [\\n      \\\"0x00b3d350\\\",\\n      \\\"0x00e818f0\\\",\\n      \\\"0x00b3d350\\\",\\n      \\\"0x00e818f0\\\",\\n      \\\"0x00b3d350\\\",\\n      \\\"0x007d8060\\\",\\n 
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave7/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-game-mode-wave7/007d85b0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_game_mode_wave7/game_mode_wave7.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/integrated/batch-2026-09-25-wave7/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg-game-mode-wave7/007d85b0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_game_mode_wave7/game_mode_wave7.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.json",
    "src/reconstruction/pkg_game_mode_wave7/game_mode_wave7.cpp"
  ],
  "required_categories": [
    "ABI",
    "CALLS",
    "GLOBALS",
    "FIELDS/OFFSETS",
    "CONSTANTS",
   
[TRUNCATED]
```
