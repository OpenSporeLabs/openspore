# Reconstruction context 0x00e7fc00

- Status: `partial`
- Content SHA-256: `fc2e83669d73b89e917efb0aef52828c4ea16167ebeff45943104d4ec39918b4`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00e7fc00",
  "phase": "reconstruction",
  "target": "0x00e7fc00"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueMode",
  "name": "App::cCellModeStrategy::OnExit",
  "package": "PKG-08-CELL-MODE",
  "subsystem": "Simulator.Cell.Mode",
  "va": "0x00e7fc00"
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
  "content_sha256": "d90d4adef673eb28ade9d201483c5df42c2a00531862549fe196bf36ebe3daba",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00e7fc00 failed: Decompilation did not complete. Reason: ",
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
  "hidden_receiver": "ECX OpaqueMode* mode",
  "hidden_this_register": "ECX",
  "hidden_this_type": "App::cCellModeStrategy*",
  "ordinary_stack_argument_slots": 0,
  "ret_form": "plain RET",
  "return_type": "void",
  "stack_cleanup_bytes": 0
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "FUN_00e31100",
      "reconstructed": false,
      "va": "0x00e31100"
    }
  ],
  "callers": [],
  "edge_rows": [
    {
      "callsite": "0x00e7fcda",
      "direction": "out",
      "other": "0x0067ddd0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7fcd5",
      "direction": "out",
      "other": "0x00b72110",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7fc96",
      "direction": "out",
      "other": "0x00b72230",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7fcc2",
      "direction": "out",
      "other": "0x00b72230",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7fc81",
      "direction": "out",
      "other": "0x00e31100",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7fc01",
      "direction": "out",
      "other": "0x00e53580",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7fcef",
      "direction": "out",
      "other": "0x00e64a00",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7fcac",
      "direction": "out",
      "other": "0x00e7e130",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7fcf4",
      "direction": "out",
      "other": "0x00e82d40",
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
  "globals": [
    "global:0x015fd8e8",
    "global:0x016b3be0",
    "global:g_mode_on_exit_globals"
  ],
  "types": [
    "App::cCellModeStrategy*",
    "DATA",
    "NativePorts",
    "OpaqueGlobalViews",
    "OpaqueMode",
    "OpaqueRecord",
    "OpaqueService",
    "void"
  ],
  "vtables": [
    "vtable:0x00000098",
    "vtable:0x01485550",
    "vtable:0x01485574"
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
      "gate-cell-mode-on-exit"
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
      "name": "FUN_00e31100",
      "reconstructed": false,
      "va": "0x00e31100"
    }
  ],
  "callees_truncated": false,
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00e7fcda",
      "direction": "out",
      "other": "0x0067ddd0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7fcd5",
      "direction": "out",
      "other": "0x00b72110",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7fc96",
      "direction": "out",
      "other": "0x00b72230",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7fcc2",
      "direction": "out",
      "other": "0x00b72230",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7fc81",
      "direction": "out",
      "other": "0x00e31100",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7fc01",
      "direction": "out",
      "other": "0x00e53580",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7fcef",
      "direction": "out",
      "other": "0x00e64a00",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7fcac",
      "direction": "out",
      "other": "0x00e7e130",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7fcf4",
      "direction": "out",
      "other": "0x00e82d40",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 0,
  "fan_out": 1,
  "manifest_callees": [
    "0x
[TRUNCATED]
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "shared_types:DATA",
      "shared_vtable:vtable:0x01485550",
      "same_calling_convention"
    ],
    "package": "PKG-APP-LIFECYCLE-WAVE8",
    "score": 9,
    "symbol": "app_c_cell_mode_strategy_dispose_00e81f30",
    "va": "0x00e81f30"
  },
  {
    "match_basis": [
      "shared_types:DATA",
      "shared_vtable:vtable:0x01485550"
    ],
    "package": "PKG-GAME-INPUT-WAVE7",
    "score": 7,
    "symbol": "cell_mode_strategy_on_mouse_move_00e51010",
    "va": "0x00e51010"
  },
  {
    "match_basis": [
      "shared_types:DATA",
      "shared_vtable:vtable:0x01485550"
    ],
    "package": "PKG-GAME-INPUT-WAVE8",
    "score": 7,
    "symbol": "cell_mode_strategy_on_mouse_up_00e5c0f0",
    "va": "0x00e5c0f0"
  },
  {
    "match_basis": [
      "shared_types:DATA",
      "shared_vtable:vtable:0x01485550"
    ],
    "package": "PKG-GAME-INPUT-WAVE8",
    "score": 7,
    "symbol": "cell_mode_strategy_on_mouse_down_00e6c860",
    "va": "0x00e6c860"
  },
  {
    "match_basis": [
      "shared_types:DATA",
      "shared_vtable:vtable:0x01485550"
    ],
    "package": "PKG-GAME-INPUT-WAVE8",
    "score": 7,
    "symbol": "cell_mode_strategy_on_mouse_wheel_00e7d660",
    "va": "0x00e7d660"
  },
  {
    "match_basis": [
      "shared_types:DATA",
      "shared_vtable:vtable:0x01485550"
    ],
    "package": "PKG-FRAME-RUNTIME-WAVE7",
    "score": 7,
    "symbol": "cell_mode_update_00e80980",
    "va": "0x00e80980"
  },
  {
    "match_basis": [
      "shared_types:DATA",
      "shared_vtable:vtable:0x01485550"
    ],
    "package": "PKG-GAME-INPUT-
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__cCellModeStrategy__OnExit.c",
  "file": "src/reconstruction/pkg08_cell_mode/mode_on_exit.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__cCellModeStrategy__OnExit.c",
    "reconstruction/staging/pkg08-cell-mode/mode_on_exit.cpp",
    "reconstruction/staging/pkg08-cell-mode/mode_on_exit.hpp",
    "reconstruction/staging/pkg08-cell-mode/mode_on_exit_model_test.cpp",
    "src/reconstruction/pkg08_cell_mode/mode_on_exit.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-pkg08-cell-mode/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg08-cell-mode/00e7fc00.json"
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
        "0x00e4ace0",
        "0x00e4cde0",
        "0x00e823a0",
        "0x00e80ba0",
        "0x00e7fc00",
        "0x00e81f30",
        "0x00e4cde0",
        "0x00e4cde0",
        "0x00e4ace0",
        "0x00e4ace0",
        "0x00e80ba0",
        "0x00005190",
        "0x00e80ba0",
        "0x00e80d45",
        "0x00e80f9f",
        "0x00e7fc00"
      ],
      "conflict_id": "TD-DATA-005",
      "kind": "conflict_ledger",
      "rejected": [
        {
          "path": "competing_hypotheses.0.claim",
          "status": "rejected_for_recovered_record_families     ",
          "text": "Direct Cell records are generic CellSerializer name/ID envelopes containing a shared field descriptor table."
        },
        {
          "path": "competing_hypotheses.2.claim",
          "status": "rejected_structural_pointer_is_not_wire_envelope     ",
          "text": "Because cCellResource stores a CellSerializer pointer, every direct Cell record necessarily carries a CellSerializer wire envelope."
        }
      ],
      "resolution": null,
      "resolution_status": null,
      "source": "knowledgegraph/research/conflicts/track-d-data-serialization.json",
      "subject": "Direct Cell records, CellSerializer metadata, cCellDataReference, cCellGame, and cCellSerializableData",
      "unresolved_reason": [
        "Actual cCellSerializableData field emission order and class/object pointer remapping are not recovered.",
        "No original-process save/load trace or byte-level .spo oracle is available."
      ]
    },
    {
      "anchors
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/App__cCellModeStrategy__OnExit.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-pkg08-cell-mode/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg08-cell-mode/00e7fc00.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg08-cell-mode/mode_on_exit.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg08-cell-mode/mode_on_exit.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg08-cell-mode/mode_on_exit_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg08_cell_mode/mode_on_exit.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/App__cCellModeStrategy__OnExit.c",
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
      "ref": "reconstruction/integrated/batch-2026-09-25-pkg08-cell-mode/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg08-cell-mode/00e7fc00.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg08-cell-mode/mode_on_exit.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/
[TRUNCATED]
```
