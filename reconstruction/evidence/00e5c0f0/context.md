# Reconstruction context 0x00e5c0f0

- Status: `partial`
- Content SHA-256: `dc0e66d3e550d58f6e66e9e496cef59dc8d63aa3a7059c7827550ee2c2207a00`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00e5c0f0",
  "phase": "reconstruction",
  "target": "0x00e5c0f0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueCellModeStrategy",
  "name": "App::cCellModeStrategy::OnMouseUp",
  "package": "PKG-GAME-INPUT-WAVE8",
  "subsystem": "Input",
  "va": "0x00e5c0f0"
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
  "content_sha256": "dc0077aee1e717ae5bf027fbec17756fededd862b1839d74fb5a11ab6b5cfbc9",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00e5c0f0 failed: Decompilation did not complete. Reason: ",
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
      "evidence": "captured into ECX by MOV ECX,[ESP+0x4] at 0x00e5c0f8 and pushed as the first forwarded word; the body performs no further use of the word after the forward",
      "name": "mouseButton",
      "offset": "ESP+4",
      "slot": 0,
      "type": "int32"
    },
    {
      "evidence": "loaded by FLD float ptr [ESP+0x2c] at 0x00e5c107 into the forwarded word at 0x00e5c10b",
      "name": "mouseX",
      "offset": "ESP+8",
      "slot": 1,
      "type": "raw float dword"
    },
    {
      "evidence": "loaded by FLD float ptr [ESP+0xc] at 0x00e5c0f4 into the forwarded word at 0x00e5c103",
      "name": "mouseY",
      "offset": "ESP+0xc",
      "slot": 2,
      "type": "raw float dword"
    },
    {
      "evidence": "captured into EAX by MOV EAX,[ESP+0x10] at 0x00e5c0f0 and pushed as the fourth forwarded word at 0x00e5c0ff",
      "name": "mouseState",
      "offset": "ESP+0x10",
      "slot": 3,
      "type": "uint32",
      "width_bytes": 4
    }
  ],
  "ret_form": "RET 0x10",
  "return_register": "AL, set once by MOV AL,0x1 at 0x00e5c189",
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
      "name": "game_input_mouse_up_00697af0",
      "reconstructed": true,
      "va": "0x00697af0"
    },
    {
      "name": "camera_light_origin_helper_007c4900",
      "reconstructed": true,
      "va": "0x007c4900"
    }
  ],
  "callers": [],
  "edge_rows": [
    {
      "callsite": "0x00e5c11a",
      "direction": "out",
      "other": "0x0067dd10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e5c115",
      "direction": "out",
      "other": "0x00697af0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e5c133",
      "direction": "out",
      "other": "0x007c4900",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e5c168",
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
    "bool in AL, always one",
    "int32",
    "raw float dword",
    "uint32"
  ],
  "vtables": [
    "vtable:0x01485550",
    "vtable:0x01485588"
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
      "Observe the concrete vtable call shape, the validity of the Cell game and Cell state globals, the 0x00e87200 return value, and the resulting words at Cell state offsets 0x900 and 0x904 in the original Cell mode."
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
      "name": "game_input_mouse_up_00697af0",
      "reconstructed": true,
      "va": "0x00697af0"
    },
    {
      "name": "camera_light_origin_helper_007c4900",
      "reconstructed": true,
      "va": "0x007c4900"
    }
  ],
  "callees_truncated": false,
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00e5c11a",
      "direction": "out",
      "other": "0x0067dd10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e5c115",
      "direction": "out",
      "other": "0x00697af0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e5c133",
      "direction": "out",
      "other": "0x007c4900",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e5c168",
      "direction": "out",
      "other": "0x00e87200",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 0,
  "fan_out": 2,
  "manifest_callees": [],
  "manifest_callers": [],
  "nearby_reconstructed": [
    "0x00697af0",
    "0x007c4900"
  ],
  "scc": {
    "id": "scc-0528",
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
      "shared_types:DATA,OpaqueCellModeStrategy,int32,raw float dword",
      "shared_vtable:vtable:0x01485550",
      "same_calling_convention"
    ],
    "package": "PKG-GAME-INPUT-WAVE8",
    "score": 34,
    "symbol": "cell_mode_strategy_on_mouse_down_00e6c860",
    "va": "0x00e6c860"
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
      "shared_types:DATA,raw float dword",
      "shared_vtable:vtable:0x01485550",
      "same_calling_convention"
    ],
    "package": "PKG-GAME-INPUT-WAVE7",
    "score": 18,
    "symbol": "cell_mode_strategy_on_mouse_move_00e51010",
    "va": "0x00e51010"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_types:DATA,int32",
      "shared_vtable:vtable:0x01485550",
      "same_calling_convention"
    ],
    "package": "PKG-GAME-INPUT-WAVE7",
    "score": 18,
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
    "score": 15,
    "s
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__cCellModeStrategy__OnMouseUp.c",
  "file": "src/reconstruction/pkg_game_input_wave8/game_input_wave8.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__cCellModeStrategy__OnMouseUp.c",
    "src/reconstruction/pkg_game_input_wave8/game_input_wave8.cpp",
    "src/reconstruction/pkg_game_input_wave8/game_input_wave8.hpp",
    "src/reconstruction/pkg_game_input_wave8/game_input_wave8_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave8/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-game-input-wave8/00e5c0f0.json"
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
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/App__cCellModeStrategy__OnMouseUp.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave8/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-game-input-wave8/00e5c0f0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_game_input_wave8/game_input_wave8.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_game_input_wave8/game_input_wave8.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_game_input_wave8/game_input_wave8_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/App__cCellModeStrategy__OnMouseUp.c",
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
      "ref": "reconstruction/metadata/pkg-game-input-wave8/00e5c0f0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_game_input_wave8/game_input_wave8.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstr
[TRUNCATED]
```
