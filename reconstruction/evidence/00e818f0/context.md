# Reconstruction context 0x00e818f0

- Status: `partial`
- Content SHA-256: `6c9411b045309839d20c5afad6c20ef31f4ec18ad565be5328a73f64c618361a`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00e818f0",
  "phase": "reconstruction",
  "target": "0x00e818f0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueGameInput",
  "name": "App::cCellModeStrategy::OnKeyDown",
  "package": "PKG-GAME-INPUT-WAVE7",
  "subsystem": "Input",
  "va": "0x00e818f0"
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
  "content_sha256": "0a8d72d420db71c1333ea0920fe9592211f6387c48cfc65ece20dade55e72636",
  "live_attempts": [
    {
      "code": "live_unavailable",
      "kind": "decompilation",
      "message": "Ghidra returned snapshot instead of live evidence",
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
  "calling_convention": "thiscall",
  "hidden_receiver": "ECX OpaqueCellModeStrategy*",
  "ordinary_stack_arguments": [
    {
      "name": "virtualKey",
      "offset": "ESP+4",
      "slot": 0,
      "type": "int32"
    },
    {
      "offset": "ESP+8",
      "slot": 1,
      "type": "KeyModifiers",
      "width_bytes": 4
    }
  ],
  "ret_form": "RET 8",
  "return_register": "AL",
  "stack_cleanup_bytes": 8
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "game_input_on_key_down_00697a50",
      "reconstructed": true,
      "va": "0x00697a50"
    }
  ],
  "callers": [],
  "edge_rows": [
    {
      "callsite": "0x00e8192f",
      "direction": "out",
      "other": "0x00697a50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e8196d",
      "direction": "out",
      "other": "0x00e7f630",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e81980",
      "direction": "out",
      "other": "0x00e7f630",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e8195f",
      "direction": "out",
      "other": "0x00e81120",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e8198e",
      "direction": "out",
      "other": "0x00e81120",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e818fc",
      "direction": "out",
      "other": "0x00e82900",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e81948",
      "direction": "out",
      "other": "0x00e82cc0",
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
    "DATA",
    "KeyModifiers",
    "OpaqueGameInput",
    "bool in AL",
    "int32"
  ],
  "vtables": [
    "vtable:0x01485550",
    "vtable:0x0148557c"
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
      "Observe Cell-mode vtable reachability, global receiver validity, route/UI/action return values, and all action side effects in the original process."
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
      "name": "game_input_on_key_down_00697a50",
      "reconstructed": true,
      "va": "0x00697a50"
    }
  ],
  "callees_truncated": false,
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00e8192f",
      "direction": "out",
      "other": "0x00697a50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e8196d",
      "direction": "out",
      "other": "0x00e7f630",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e81980",
      "direction": "out",
      "other": "0x00e7f630",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e8195f",
      "direction": "out",
      "other": "0x00e81120",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e8198e",
      "direction": "out",
      "other": "0x00e81120",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e818fc",
      "direction": "out",
      "other": "0x00e82900",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e81948",
      "direction": "out",
      "other": "0x00e82cc0",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 0,
  "fan_out": 1,
  "manifest_callees": [],
  "manifest_callers": [],
  "nearby_reconstructed": [
    "0x00697a50"
  ],
  "scc": {
    "id": "scc-0561",
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
      "shared_types:DATA,OpaqueGameInput,bool in AL",
      "shared_vtable:vtable:0x01485550",
      "same_calling_convention"
    ],
    "package": "PKG-GAME-INPUT-WAVE7",
    "score": 34,
    "symbol": "cell_mode_strategy_on_mouse_move_00e51010",
    "va": "0x00e51010"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "same_class",
      "shared_types:KeyModifiers,OpaqueGameInput,int32",
      "same_calling_convention",
      "direct_xref_neighbor"
    ],
    "package": "PKG-GAME-INPUT-WAVE7",
    "score": 33,
    "symbol": "game_input_on_key_down_00697a50",
    "va": "0x00697a50"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "same_class",
      "shared_types:KeyModifiers,OpaqueGameInput,int32",
      "same_calling_convention"
    ],
    "package": "PKG-GAME-INPUT-WAVE7",
    "score": 30,
    "symbol": "game_input_on_key_up_00697a80",
    "va": "0x00697a80"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "same_class",
      "shared_types:OpaqueGameInput,int32",
      "same_calling_convention"
    ],
    "package": "PKG-GAME-INPUT-WAVE7",
    "score": 27,
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
    "symbol": "simulator_game_input_manager_get_00b3d350",
    "va"
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__cCellModeStrategy__OnKeyDown.c",
  "file": "src/reconstruction/pkg_game_input_wave7/game_input_wave7.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__cCellModeStrategy__OnKeyDown.c",
    "src/reconstruction/pkg_game_input_wave7/game_input_wave7.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave7/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-game-input-wave7/00e818f0.json"
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
        "0x00e818f0",
        "0x00b3d350",
        "0x00e818f0",
        "0x00b3d350",
        "0x007d8060",
        "0x007d8060",
        "0x007d8230",
        "0x007d8230",
        "0x007d8360",
        "0x007d8360",
        "0x007d8470",
        "0x007d8470",
        "0x007d85b0",
        "0x007d85b0",
        "0x007d8c30"
      ],
      "conflict_id": "U-GAME-INPUT-ROUTER",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The input/UI surface is structurally present, but partition, focus, priority, and consum
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/App__cCellModeStrategy__OnKeyDown.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave7/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-game-input-wave7/00e818f0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_game_input_wave7/game_input_wave7.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/App__cCellModeStrategy__OnKeyDown.c",
      "source_class": "committed_artifact"
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
      "ref": "reconstruction/metadata/pkg-game-input-wave7/00e818f0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_game_input_wave7/game_input_wave7.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.j
[TRUNCATED]
```
