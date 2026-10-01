# Reconstruction context 0x00b63510

- Status: `partial`
- Content SHA-256: `6ff51473c3fc2284fe7abbae6ae9ef6a9064c7037bc24bfbd3b0ba43592898d0`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00b63510",
  "phase": "reconstruction",
  "target": "0x00b63510"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueGameModeState",
  "name": "app_simulator_mode_bridge_00b63510",
  "package": "PKG-GAME-MODE-WAVE7",
  "subsystem": "App.GameMode",
  "va": "0x00b63510"
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
  "content_sha256": "036541804307665cd5cfc2a435f0b206e2dfff9c15c5848196b97a6e693fd68a",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00b63510 failed: Decompilation did not complete. Reason: ",
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
    "uint32 message_id",
    "void* payload"
  ],
  "receiver": "bridge object in ECX",
  "ret_form": "RET 0x8",
  "return": "AL boolean"
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0067dcc0"
    },
    {
      "name": "FUN_00b5b800",
      "reconstructed": false,
      "va": "0x00b5b800"
    },
    {
      "name": "simulator_strategy_transition_00b5dbb0",
      "reconstructed": true,
      "va": "0x00b5dbb0"
    },
    {
      "name": "simulator_strategy_transition_00b5f040",
      "reconstructed": true,
      "va": "0x00b5f040"
    },
    {
      "name": "FUN_01021080",
      "reconstructed": true,
      "va": "0x01021080"
    }
  ],
  "callers": [],
  "edge_rows": [
    {
      "callsite": "0x00b63822",
      "direction": "out",
      "other": "0x0067cb40",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00b636c2",
      "direction": "out",
      "other": "0x0067dcc0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00b63710",
      "direction": "out",
      "other": "0x0067dcc0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00b6377d",
      "direction": "out",
      "other": "0x0067dcc0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00b63794",
      "direction": "out",
      "other": "0x0067dd20",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00b635a2",
      "direction": "out",
      "other": "0x00b108b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00b635d8",
      "direction": "out",
      "other": "0x00b108b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00b63700",
      "direc
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [
    "global:0x3e9a620 writes the package-owned synthetic 0x01686af1 flag to 1; 0x3e9a625 writes it to 0."
  ],
  "types": [
    "OpaqueGameModeState"
  ],
  "vtables": [
    "vtable:0x00b63510"
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
      "Observe receiver validity, all message-id reachability, service identities, mode-object fields, payload validity, and all unresolved native port results; runtime validation is not run."
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
      "name": null,
      "reconstructed": false,
      "va": "0x0067dcc0"
    },
    {
      "name": "FUN_00b5b800",
      "reconstructed": false,
      "va": "0x00b5b800"
    },
    {
      "name": "simulator_strategy_transition_00b5dbb0",
      "reconstructed": true,
      "va": "0x00b5dbb0"
    },
    {
      "name": "simulator_strategy_transition_00b5f040",
      "reconstructed": true,
      "va": "0x00b5f040"
    },
    {
      "name": "FUN_01021080",
      "reconstructed": true,
      "va": "0x01021080"
    }
  ],
  "callees_truncated": false,
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00b63822",
      "direction": "out",
      "other": "0x0067cb40",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00b636c2",
      "direction": "out",
      "other": "0x0067dcc0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00b63710",
      "direction": "out",
      "other": "0x0067dcc0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00b6377d",
      "direction": "out",
      "other": "0x0067dcc0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00b63794",
      "direction": "out",
      "other": "0x0067dd20",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00b635a2",
      "direction": "out",
      "other": "0x00b108b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00b635d8",
      "direction": "out",
      "other": "0x00b108b0",
      "ref
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
    "symbol": "app_mode_activate_007d85b0",
    "va": "0x007d85b0"
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
      "s
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
    "reconstruction/metadata/pkg-game-mode-wave7/00b63510.json"
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
        "0x007d85b0",
        "0x007d8c80",
        "0x01412598",
        "0x01412598",
        "0x007d8c80",
        "0x007d8c80",
        "0x007d85b0",
        "0x0212d3e7",
        "0x022d1adc",
        "0x00b63510",
        "0x00b63510",
        "0x007d8060",
        "0x007d8060",
        "0x007d8230",
        "0x007d8230",
        "0x007d8360"
      ],
      "conflict_id": "U-MODE-TRANSITION-RUNTIME",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "Static call order is fixed: old OnExit, active-index write, mode-exit send, new OnEnter, mode-enter send. Runtime reachability and listener completion order are not verified.",
      "resolution_status": "Static call order is fixed: old OnExit, active-index write, mode-exit send, new OnEnter, mode-enter send. Runtime reachability and listener completion order are not verified.",
      "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
      "subject": null,
      "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
    },
    {
      "anchors": [
        "0x00e11333",
        "0x01412598",
        "0x01412598",
        "0x00e11333",
        "0x00e11333",
        "0x00e11333",
        "0x00b63510",
        "0x007d9120",
        "0x00e11333"
      ],
      "conflict_id": "U06",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The cited producer, consumer, or registration surface is retained, but the complete event-to-message mapping, timing, and payloa
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave7/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-game-mode-wave7/00b63510.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_game_mode_wave7/game_mode_wave7.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-game-mode-wave7/00b63510.json",
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
