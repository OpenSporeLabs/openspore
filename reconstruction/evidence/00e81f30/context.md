# Reconstruction context 0x00e81f30

- Status: `partial`
- Content SHA-256: `66dbd8a3734e7bb81a97fbeaa351f3e45e320d45b987b1f665ecfe45fb82615b`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00e81f30",
  "phase": "reconstruction",
  "target": "0x00e81f30"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueCellModeStrategy",
  "name": "App::cCellModeStrategy::Dispose",
  "package": "PKG-APP-LIFECYCLE-WAVE8",
  "subsystem": "App.Lifecycle",
  "va": "0x00e81f30"
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
  "content_sha256": "db728df432ccaae919132b8ff8e2f623cbda29f99da0157fb317b884797ca59e",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00e81f30 failed: Decompilation did not complete. Reason: ",
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
  "hidden_receiver": "ECX OpaqueCellModeStrategy*",
  "ordinary_stack_argument_slots": 0,
  "ret_form": "plain RET",
  "return_register": "AL",
  "return_type": "bool"
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
    }
  ],
  "callers": [],
  "edge_rows": [
    {
      "callsite": "0x00e81f73",
      "direction": "out",
      "other": "0x005f3680",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e81f64",
      "direction": "out",
      "other": "0x005f4e10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e82043",
      "direction": "out",
      "other": "0x0067dcc0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e820bb",
      "direction": "out",
      "other": "0x0067dcc0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e820df",
      "direction": "out",
      "other": "0x0067dcc0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e82103",
      "direction": "out",
      "other": "0x0067dcc0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e82014",
      "direction": "out",
      "other": "0x0067ddd0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e8202e",
      "direction": "out",
      "other": "0x0067ddd0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e81f8b",
      "direction": "out",
      "other": "0x00e4c9e0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e81f86",
      "direction": "out",
      "other": "0x00e4cd50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e820a2",
      "direction": "out",
      "other"
[TRUNCATED]
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
    "bool"
  ],
  "vtables": [
    "vtable:0x01485550",
    "vtable:0x0148556c"
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
      "required"
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
    }
  ],
  "callees_truncated": false,
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00e81f73",
      "direction": "out",
      "other": "0x005f3680",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e81f64",
      "direction": "out",
      "other": "0x005f4e10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e82043",
      "direction": "out",
      "other": "0x0067dcc0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e820bb",
      "direction": "out",
      "other": "0x0067dcc0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e820df",
      "direction": "out",
      "other": "0x0067dcc0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e82103",
      "direction": "out",
      "other": "0x0067dcc0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e82014",
      "direction": "out",
      "other": "0x0067ddd0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e8202e",
      "direction": "out",
      "other": "0x0067ddd0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e81f8b",
      "direction": "out",
      "other": "0x00e4c9e0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e81f86",
      "direction": "out",
      "other": "0x00e4cd50",
      "reference_type": "direct-call"
[TRUNCATED]
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "same_class",
      "shared_types:DATA,OpaqueCellModeStrategy",
      "shared_vtable:vtable:0x01485550"
    ],
    "package": "PKG-GAME-INPUT-WAVE8",
    "score": 15,
    "symbol": "cell_mode_strategy_on_mouse_up_00e5c0f0",
    "va": "0x00e5c0f0"
  },
  {
    "match_basis": [
      "same_class",
      "shared_types:DATA,OpaqueCellModeStrategy",
      "shared_vtable:vtable:0x01485550"
    ],
    "package": "PKG-GAME-INPUT-WAVE8",
    "score": 15,
    "symbol": "cell_mode_strategy_on_mouse_down_00e6c860",
    "va": "0x00e6c860"
  },
  {
    "match_basis": [
      "same_class",
      "shared_types:DATA,OpaqueCellModeStrategy",
      "shared_vtable:vtable:0x01485550"
    ],
    "package": "PKG-GAME-INPUT-WAVE8",
    "score": 15,
    "symbol": "cell_mode_strategy_on_mouse_wheel_00e7d660",
    "va": "0x00e7d660"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_types:DATA",
      "same_calling_convention"
    ],
    "package": "WAVE6-ENGINE-RUNTIME",
    "score": 11,
    "symbol": "app_system_service_gate_dispatch_007e5f30",
    "va": "0x007e5f30"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_types:DATA"
    ],
    "package": "PKG-APP-LIFECYCLE-WAVE7",
    "score": 9,
    "symbol": "app_capp_system_hook_windows_007e6080",
    "va": "0x007e6080"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_types:DATA"
    ],
    "package": "PKG-APP-LIFECYCLE-WAVE7",
    "score": 9,
    "symbol": "app_capp_system_set_effect_collection_ids_007e6100",
    "va": "0x007e6100"
  },
  {
    "match_basis": [
  
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__cCellModeStrategy__Dispose.c",
  "file": "src/reconstruction/pkg_app_lifecycle_wave8/app_lifecycle_wave8.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__cCellModeStrategy__Dispose.c",
    "src/reconstruction/pkg_app_lifecycle_wave8/app_lifecycle_wave8.cpp",
    "src/reconstruction/pkg_app_lifecycle_wave8/app_lifecycle_wave8.hpp",
    "src/reconstruction/pkg_app_lifecycle_wave8/app_lifecycle_wave8_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave8/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-app-lifecycle-wave8/00e81f30.json"
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
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/App__cCellModeStrategy__Dispose.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave8/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-app-lifecycle-wave8/00e81f30.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_app_lifecycle_wave8/app_lifecycle_wave8.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_app_lifecycle_wave8/app_lifecycle_wave8.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_app_lifecycle_wave8/app_lifecycle_wave8_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/App__cCellModeStrategy__Dispose.c",
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
      "ref": "reconstruction/metadata/pkg-app-lifecycle-wave8/00e81f30.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_app_lifecycle_wave8/app_lifecycle_wave8.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/r
[TRUNCATED]
```
