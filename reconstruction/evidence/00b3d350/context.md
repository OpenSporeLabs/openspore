# Reconstruction context 0x00b3d350

- Status: `partial`
- Content SHA-256: `c0b688355b40180a132ed74f53db9d97584cca08cfc0422a72c4aa018de07fce`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00b3d350",
  "phase": "reconstruction",
  "target": "0x00b3d350"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueGameInput",
  "name": "simulator_game_input_manager_get_00b3d350",
  "package": "PKG-GAME-INPUT-WAVE7",
  "subsystem": "Input",
  "va": "0x00b3d350"
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
  "content_sha256": "a4de232a1cafcde63adfef3e4aa2447c512bff9ea71ad9e73063ad4e67058170",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00b3d350 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "cdecl",
  "hidden_receiver": "none",
  "ordinary_stack_argument_slots": 0,
  "ret_form": "plain RET",
  "return_register": "EAX",
  "stack_cleanup_bytes": 0
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
      "name": null,
      "reconstructed": false,
      "va": "0x00ac1970"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ac1b30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ac1dc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ac2200"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ac2520"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ac2a20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ac2b40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ac2d00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ac2e20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ac3110"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ac3540"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ac38d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ac5590"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ac5c00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ac65d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ac68e0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00ac1974",
      "direction": "in",
      "other": "0x00ac1970",
      "reference_type": "direct-call"
    },

[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [
    "global:0x0167eaf8"
  ],
  "types": [
    "OpaqueGameInput",
    "OpaqueGameInputManager*",
    "READ"
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
      "Observe the original global slot and concrete manager lifetime before making ownership claims."
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
      "va": "0x00ac1970"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ac1b30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ac1dc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ac2200"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ac2520"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ac2a20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ac2b40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ac2d00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ac2e20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ac3110"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ac3540"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ac38d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ac5590"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ac5c00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ac65d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ac68e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ac6960"
    },
    {
      "name": null,
      "reconst
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
      "shared_types:OpaqueGameInput"
    ],
    "package": "PKG-GAME-INPUT-WAVE7",
    "score": 22,
    "symbol": "game_input_on_key_down_00697a50",
    "va": "0x00697a50"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "same_class",
      "shared_types:OpaqueGameInput"
    ],
    "package": "PKG-GAME-INPUT-WAVE7",
    "score": 22,
    "symbol": "game_input_on_key_up_00697a80",
    "va": "0x00697a80"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "same_class",
      "shared_types:OpaqueGameInput"
    ],
    "package": "PKG-GAME-INPUT-WAVE7",
    "score": 22,
    "symbol": "game_input_mouse_up_00697af0",
    "va": "0x00697af0"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "same_class",
      "shared_types:OpaqueGameInput"
    ],
    "package": "PKG-GAME-INPUT-WAVE7",
    "score": 22,
    "symbol": "cell_mode_strategy_on_mouse_move_00e51010",
    "va": "0x00e51010"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "same_class",
      "shared_types:OpaqueGameInput"
    ],
    "package": "PKG-GAME-INPUT-WAVE7",
    "score": 22,
    "symbol": "cell_mode_strategy_on_key_down_00e818f0",
    "va": "0x00e818f0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-GAME-INPUT-WAVE8",
    "score": 6,
    "symbol": "cell_mode_strategy_on_mouse_up_00e5c0f0",
    "va": "0x00e5c0f0"
  },
  {
    "match_basis": [
      "same_subsystem"
  
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg_game_input_wave7/game_input_wave7.cpp",
  "files": [
    "src/reconstruction/pkg_game_input_wave7/game_input_wave7.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave7/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-game-input-wave7/00b3d350.json"
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
        "0x00b3d350",
        "0x00e818f0",
        "0x00b3d350",
        "0x00e818f0",
        "0x00b3d350",
        "0x007d8060",
        "0x007d8060",
        "0x007d8360",
        "0x007d8360",
        "0x007d85b0",
        "0x007d85b0",
        "0x007d8c30",
        "0x007d8c30",
        "0x007d8c80",
        "0x007d8c80",
        "0x007d8d40"
      ],
      "conflict_id": "Q-INPUT-ROUTING",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
      "resolution_status": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
      "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
      "subject": null,
      "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
    },
    {
      "anchors": [
        "0x00b3d350",
        "0x00b3d400",
        "0x00b3d350",
        "0x00b3d350",
        "0x01485550"
      ],
      "conflict_id": "TB-VT-008",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": {
        "merge_decision": "separate_entities",
        "preferred_claim": null,
        "preserved_alternatives": true,
        "scope_note": "The interface and object layout are supported; the concrete vtable address is unresolved.",
        "status": "unresolved",
        "taxonomy": "unresolved"
      },
      "resolution_status": "un
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave7/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-game-input-wave7/00b3d350.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_game_input_wave7/game_input_wave7.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-game-input-wave7/00b3d350.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_game_input_wave7/game_input_wave7.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.json",
    "src/reconstruction/pkg_game_input_wave7/game_input_wave7.cpp"
  ],
  "required_categories": [
    "ABI",
    "CALLS",
    "GLOBALS",
    "FIELDS/OFFSETS",
    "CONSTANTS"
[TRUNCATED]
```
