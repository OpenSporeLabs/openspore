# Reconstruction context 0x00b5f040

- Status: `partial`
- Content SHA-256: `717bd18b4ad24d9210bdd0c25b285a365254a9335157d774452ce82d02789ea8`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00b5f040",
  "phase": "reconstruction",
  "target": "0x00b5f040"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueModeTransition",
  "name": "simulator_strategy_transition_00b5f040",
  "package": "PKG-GAME-MODE-WAVE8",
  "subsystem": "App.GameMode",
  "va": "0x00b5f040"
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
  "content_sha256": "32644721d7a80f20066724506eb79914cf19df062db9dad4acca07f8846f67a9",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00b5f040 failed: Decompilation did not complete. Reason: ",
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
    "uint32 first_mode at [ESP+0x14] after four register saves",
    "uint32 second_mode at [ESP+0x18] after four register saves"
  ],
  "receiver": "Simulator strategy/mode transition object in ECX",
  "ret_form": "RET 0x8",
  "return": "void"
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "FUN_00b3d380",
      "reconstructed": false,
      "va": "0x00b3d380"
    },
    {
      "name": "FUN_00d38840",
      "reconstructed": false,
      "va": "0x00d38840"
    }
  ],
  "callers": [
    {
      "name": "app_simulator_mode_bridge_00b63510",
      "reconstructed": true,
      "va": "0x00b63510"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00b63664",
      "direction": "in",
      "other": "0x00b63510",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00b5f0d5",
      "direction": "out",
      "other": "0x0067caa0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00b5f192",
      "direction": "out",
      "other": "0x0067cab0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00b5f199",
      "direction": "out",
      "other": "0x008017f0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00b5f0a6",
      "direction": "out",
      "other": "0x00805070",
      "reference_type": "thunk"
    },
    {
      "callsite": "0x00b5f0c6",
      "direction": "out",
      "other": "0x00810660",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00b5f0b4",
      "direction": "out",
      "other": "0x00810760",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00b5f0f9",
      "direction": "out",
      "other": "0x00812d60",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00b5f0f0",
      "direction": "out",
      "other": "0x008153e0",
      "reference_type": "direct-call"

[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "OpaqueModeTransition"
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
      "Bind the live receiver vtable, participant list, shared-state root, and service callbacks before runtime validation; the model test is not an original-process trace."
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
      "name": "FUN_00b3d380",
      "reconstructed": false,
      "va": "0x00b3d380"
    },
    {
      "name": "FUN_00d38840",
      "reconstructed": false,
      "va": "0x00d38840"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": "app_simulator_mode_bridge_00b63510",
      "reconstructed": true,
      "va": "0x00b63510"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00b63664",
      "direction": "in",
      "other": "0x00b63510",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00b5f0d5",
      "direction": "out",
      "other": "0x0067caa0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00b5f192",
      "direction": "out",
      "other": "0x0067cab0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00b5f199",
      "direction": "out",
      "other": "0x008017f0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00b5f0a6",
      "direction": "out",
      "other": "0x00805070",
      "reference_type": "thunk"
    },
    {
      "callsite": "0x00b5f0c6",
      "direction": "out",
      "other": "0x00810660",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00b5f0b4",
      "direction": "out",
      "other": "0x00810760",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00b5f0f9",
      "direction": "out",
      "other": "0x00812d60",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00b5f0f0",
      "d
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
      "shared_types:OpaqueModeTransition",
      "same_calling_convention"
    ],
    "package": "PKG-GAME-MODE-WAVE8",
    "score": 24,
    "symbol": "simulator_strategy_transition_00b5dbb0",
    "va": "0x00b5dbb0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention",
      "direct_xref_neighbor"
    ],
    "package": "PKG-GAME-MODE-WAVE7",
    "score": 11,
    "symbol": "app_simulator_mode_bridge_00b63510",
    "va": "0x00b63510"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "PKG-GAME-MODE-WAVE7",
    "score": 8,
    "symbol": "app_mode_activate_by_name_007d8360",
    "va": "0x007d8360"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "PKG-GAME-MODE-WAVE7",
    "score": 8,
    "symbol": "app_mode_activate_007d85b0",
    "va": "0x007d85b0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "PKG-GAME-MODE-WAVE7",
    "score": 8,
    "symbol": "app_mode_activate_index_007d8c80",
    "va": "0x007d8c80"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "PKG-GAME-MODE-WAVE7",
    "score": 8,
    "symbol": "strategy_request_ready_00b5b840",
    "va": "0x00b5b840"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "PKG-GAME-MODE-WAVE7",
    "score": 8,
    "symbol": "s
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg_game_mode_wave8/game_mode_wave8.cpp",
  "files": [
    "src/reconstruction/pkg_game_mode_wave8/game_mode_wave8.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave8/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-game-mode-wave8/00b5f040.json"
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
    "Bind the live receiver vtable, participant list, shared-state root, and service callbacks before runtime validation; the model test is not an original-process trace.",
    "concrete runtime owners and values remain unresolved"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave8/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-game-mode-wave8/00b5f040.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_game_mode_wave8/game_mode_wave8.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/integrated/batch-2026-09-25-wave8/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg-game-mode-wave8/00b5f040.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_game_mode_wave8/game_mode_wave8.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.json",
    "src/reconstruction/pkg_game_mode_wave8/game_mode_wave8.cpp"
  ],
  "required_categories": [
    "ABI",
    "CALLS",
    "GLOBALS",
    "FIELDS/OFFSETS",
    "CONSTANTS",
   
[TRUNCATED]
```
