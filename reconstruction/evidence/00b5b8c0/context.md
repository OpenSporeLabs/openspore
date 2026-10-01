# Reconstruction context 0x00b5b8c0

- Status: `partial`
- Content SHA-256: `9ff291927cabdff4ef4801705d68417c981a110af87bfa8f6a0b097fdc0567f0`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00b5b8c0",
  "phase": "reconstruction",
  "target": "0x00b5b8c0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueGameModeState",
  "name": "strategy_commit_primary_00b5b8c0",
  "package": "PKG-GAME-MODE-WAVE7",
  "subsystem": "App.GameMode",
  "va": "0x00b5b8c0"
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
  "content_sha256": "22e51dc2341c77f0d1fd133d19c40dc9ba195ac5b3e897fabd2ec51b66975135",
  "live_attempts": [
    {
      "code": "ghidra_offline",
      "kind": "function",
      "message": "Ghidra unreachable and no committed snapshot covers '0x00b5b8c0'",
      "mode": "LIVE",
      "status": "unavailable"
    },
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00b5b8c0 failed: No function found for 0x00b5b8c0",
      "mode": "LIVE",
      "status": "unavailable"
    },
    {
      "code": "disassembly_unavailable",
      "kind": "disassembly",
      "message": "Ghidra disassembly unavailable",
      "mode": "LIVE",
      "status": "unavailable"
    }
  ],
  "live_requested": true,
  "overall": "PERSISTED"
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
  "ordinary_stack_arguments": [],
  "receiver": "strategy state in ECX",
  "ret_form": "plain RET",
  "return": "void"
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [],
  "callers": [],
  "edge_rows": [],
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
  "vtables": [
    "vtable:0x00b5b8c0"
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
      "Observe concrete strategy commit reachability and whether sentinel commits occur in the original process; runtime validation is not run."
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
  "edges": [],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 0,
  "fan_out": 0,
  "manifest_callees": [],
  "manifest_callers": [],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0394",
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
    "reconstruction/metadata/pkg-game-mode-wave7/00b5b8c0.json"
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
        "0x00b5b8a0",
        "0x00b5b8c0",
        "0x00b5b8e0",
        "0x00b5b960",
        "0x00b5b960",
        "0x00b1d870",
        "0x00b1d870",
        "0x00b1db60",
        "0x00b1db60",
        "0x00b1dbd0",
        "0x00b1dbd0",
        "0x00b267f0",
        "0x00b267f0",
        "0x00b5b840",
        "0x00b5b840",
        "0x00b5b880"
      ],
      "conflict_id": "game_mode_identifier_domain",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
      "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
      "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
      "subject": null,
      "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
    },
    {
      "anchors": [
        "0x00b1db60",
        "0x00b5b880",
        "0x00b5b8a0",
        "0x00b5b8c0",
        "0x00b5b8e0",
        "0x00b5b960",
        "0x00b1db60",
        "0x00c3ae70",
        "0x00c3dae0",
        "0x01001360",
        "0x01001360",
        "0x01021080",
        "0x01021080",
        "0x01021960",
        "0x01021960",
        "0x01021d40"
      ],
      "conflict_id": "simulator_mode_identifier_mapping",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The co
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave7/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-game-mode-wave7/00b5b8c0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_game_mode_wave7/game_mode_wave7.cpp', 'source_class': 'committed_artifact'}`

```json
{
  "provenance": [
    {
      "mode": "derived",
      "ref": "ephemeral reconstruction_knowledge.build_index",
      "source_class": "generated_index"
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
      "ref": "reconstruction/metadata/pkg-game-mode-wave7/00b5b8c0.json",
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
    "CONTROL FLOW",
    "VIRTUAL DISPATCH",
    "RETURN SEMANTICS",
    "EVIDENCE COVERAGE"
  ]
}
```
