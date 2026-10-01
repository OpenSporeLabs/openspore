# Reconstruction context 0x00e6c860

- Status: `partial`
- Content SHA-256: `13c50ae6fe19781648c9d7d58b2b3fa7dca84c52d9c2443ff380ac1605b6d2fb`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00e6c860",
  "phase": "reconstruction",
  "target": "0x00e6c860"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueCellModeStrategy",
  "name": "App::cCellModeStrategy::OnMouseDown",
  "package": "PKG-GAME-INPUT-WAVE8",
  "subsystem": "Input",
  "va": "0x00e6c860"
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
  "content_sha256": "4c764ff4b0e545a70979653362ca5d64f9e67024eb570684b88473c699913e5c",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00e6c860 failed: Decompilation did not complete. Reason: ",
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
  "hidden_receiver": "ECX App::cCellModeStrategy*",
  "ordinary_stack_arguments": [
    {
      "evidence": "captured into EBP by MOV EBP,[ESP+0x828] at 0x00e6c879 and compared in full 32-bit width against 0x3e8 and 0x3ea",
      "name": "mouseButton",
      "offset": "ESP+4",
      "slot": 0,
      "type": "int32"
    },
    {
      "evidence": "loaded by FLD float ptr [ESP+0x838] at 0x00e6c888 and stored into the outgoing word forwarded to GameInput::OnMouseDown",
      "name": "mouseX",
      "offset": "ESP+8",
      "slot": 1,
      "type": "raw float dword"
    },
    {
      "evidence": "loaded by FLD float ptr [ESP+0xc] at 0x00e6c860 and stored into the outgoing word forwarded to GameInput::OnMouseDown",
      "name": "mouseY",
      "offset": "ESP+0xc",
      "slot": 2,
      "type": "raw float dword"
    },
    {
      "evidence": "captured into EBX by MOV EBX,[ESP+0x830] at 0x00e6c871 and tested with TEST BL,0x3 at 0x00e6c898",
      "name": "mouseState",
      "offset": "ESP+0x10",
      "slot": 3,
      "type": "uint32",
      "width_bytes": 4
    }
  ],
  "ret_form": "RET 0x10 on all four return sites",
  "return_register": "AL, set by MOV AL,0x1 or XOR AL,AL",
  "stack_cleanup_bytes": 16
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "embedded_object_first_word_init_00743b50",
      "reconstructed": true,
      "va": "0x00743b50"
    }
  ],
  "callers": [],
  "edge_rows": [
    {
      "callsite": "0x00e6c962",
      "direction": "out",
      "other": "0x0067dd10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e6c893",
      "direction": "out",
      "other": "0x00697ab0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e6c8c3",
      "direction": "out",
      "other": "0x00743b50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e6c994",
      "direction": "out",
      "other": "0x007c4730",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e6c8cd",
      "direction": "out",
      "other": "0x00e4ce40",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e6c8b6",
      "direction": "out",
      "other": "0x00e643e0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e6c8a2",
      "direction": "out",
      "other": "0x00e6c780",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e6c8df",
      "direction": "out",
      "other": "0x00e82130",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e6c9c4",
      "direction": "out",
      "other": "0x00e87200",
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
    "OpaqueCellModeStrategy",
    "bool in AL",
    "int32",
    "raw float dword",
    "uint32"
  ],
  "vtables": [
    "vtable:0x01485550",
    "vtable:0x01485584"
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
      "Observe the concrete vtable call shape, the global Cell game and Cell state pointer validity, the 0x00e6c780 pick result, the sub-object mode word at offset 0xd4, and both publication words in the original Cell mode."
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
      "name": "embedded_object_first_word_init_00743b50",
      "reconstructed": true,
      "va": "0x00743b50"
    }
  ],
  "callees_truncated": false,
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00e6c962",
      "direction": "out",
      "other": "0x0067dd10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e6c893",
      "direction": "out",
      "other": "0x00697ab0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e6c8c3",
      "direction": "out",
      "other": "0x00743b50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e6c994",
      "direction": "out",
      "other": "0x007c4730",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e6c8cd",
      "direction": "out",
      "other": "0x00e4ce40",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e6c8b6",
      "direction": "out",
      "other": "0x00e643e0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e6c8a2",
      "direction": "out",
      "other": "0x00e6c780",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e6c8df",
      "direction": "out",
      "other": "0x00e82130",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e6c9c4",
      "direction": "out",
      "other": "0x00e87200",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 0,
  "fan_out": 1,
  "m
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
      "shared_types:DATA,OpaqueCellModeStrategy,int32,raw float dword",
      "shared_vtable:vtable:0x01485550",
      "same_calling_convention"
    ],
    "package": "PKG-GAME-INPUT-WAVE8",
    "score": 34,
    "symbol": "cell_mode_strategy_on_mouse_up_00e5c0f0",
    "va": "0x00e5c0f0"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "same_class",
      "shared_types:DATA,OpaqueCellModeStrategy,int32,raw float dword",
      "shared_vtable:vtable:0x01485550",
      "same_calling_convention"
    ],
    "package": "PKG-GAME-INPUT-WAVE8",
    "score": 34,
    "symbol": "cell_mode_strategy_on_mouse_wheel_00e7d660",
    "va": "0x00e7d660"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_types:DATA,bool in AL,raw float dword",
      "shared_vtable:vtable:0x01485550",
      "same_calling_convention"
    ],
    "package": "PKG-GAME-INPUT-WAVE7",
    "score": 21,
    "symbol": "cell_mode_strategy_on_mouse_move_00e51010",
    "va": "0x00e51010"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_types:DATA,bool in AL,int32",
      "shared_vtable:vtable:0x01485550",
      "same_calling_convention"
    ],
    "package": "PKG-GAME-INPUT-WAVE7",
    "score": 21,
    "symbol": "cell_mode_strategy_on_key_down_00e818f0",
    "va": "0x00e818f0"
  },
  {
    "match_basis": [
      "same_class",
      "shared_types:DATA,OpaqueCellModeStrategy",
      "shared_vtable:vtable:0x01485550"
    ],
    "package": "PKG-APP-LIFECYCLE-WAVE8",
   
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__cCellModeStrategy__OnMouseDown.c",
  "file": "src/reconstruction/pkg_game_input_wave8/game_input_wave8.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__cCellModeStrategy__OnMouseDown.c",
    "src/reconstruction/pkg_game_input_wave8/game_input_wave8.cpp",
    "src/reconstruction/pkg_game_input_wave8/game_input_wave8.hpp",
    "src/reconstruction/pkg_game_input_wave8/game_input_wave8_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave8/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-game-input-wave8/00e6c860.json"
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
        "0x00e7c8c0",
        "0x00e7c8c0",
        "0x00e5c0f0",
        "0x00e7c8c0",
        "0x00e6c860"
      ],
      "conflict_id": "U7",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The cited direct body establishes a bounded state mutation or call anchor, but the full transition policy, consumer order, and runtime reachability remain unresolved.",
      "resolution_status": "The cited direct body establishes a bounded state mutation or call anchor, but the full transition policy, consumer order, and runtime reachability remain unresolved.",
      "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
      "subject": null,
      "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
    },
    {
      "anchors": [
        "0x00e5c0f0",
        "0x00e6c860",
        "0x00e7d660"
      ],
      "conflict_id": "U9",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
      "resolution_status": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
      "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
      "subject": null,
      "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
    }
  ],
  "unresolved_questions": [
    "Observe the concre
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/App__cCellModeStrategy__OnMouseDown.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave8/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-game-input-wave8/00e6c860.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_game_input_wave8/game_input_wave8.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_game_input_wave8/game_input_wave8.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_game_input_wave8/game_input_wave8_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/App__cCellModeStrategy__OnMouseDown.c",
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
      "ref": "reconstruction/integrated/batch-2026-09-25-wave8/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg-game-input-wave8/00e6c860.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_game_input_wave8/game_input_wave8.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/recons
[TRUNCATED]
```
