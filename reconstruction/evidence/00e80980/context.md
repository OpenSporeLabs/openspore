# Reconstruction context 0x00e80980

- Status: `partial`
- Content SHA-256: `2b103318114c0b660e1c6ee412867876c6f062be3d3791ca40e9b443322e65c4`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00e80980",
  "phase": "reconstruction",
  "target": "0x00e80980"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueFrameRuntime",
  "name": "App::cCellModeStrategy::Update",
  "package": "PKG-FRAME-RUNTIME-WAVE7",
  "subsystem": "Runtime.Frame",
  "va": "0x00e80980"
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
  "content_sha256": "4a1aa3aff07212923b935a8d2a8b6a7556cff8cfb015c245ed084729b579616e",
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
  "calling_convention": "thiscall with callee stack cleanup",
  "ordinary_stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "machine_type": "float",
      "normalized_name": "first_word",
      "position": 1,
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x08",
      "machine_type": "float",
      "normalized_name": "second_word",
      "position": 2,
      "width_bytes": 4
    }
  ],
  "receiver_register": "ECX",
  "ret_form": "RET 0x8",
  "return_register": "EAX",
  "return_width_bytes": 0,
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
      "name": "cell_update_body_00e806b0",
      "reconstructed": true,
      "va": "0x00e806b0"
    }
  ],
  "callers": [],
  "edge_rows": [
    {
      "callsite": "0x00e80992",
      "direction": "out",
      "other": "0x00e806b0",
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
    "OpaqueCellMode*",
    "OpaqueFrameRuntime"
  ],
  "vtables": [
    "vtable:0x01485550"
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
      "name": "cell_update_body_00e806b0",
      "reconstructed": true,
      "va": "0x00e806b0"
    }
  ],
  "callees_truncated": false,
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00e80992",
      "direction": "out",
      "other": "0x00e806b0",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 0,
  "fan_out": 1,
  "manifest_callees": [
    {
      "address": "0x00e806b0",
      "callee_cleanup_bytes": 0,
      "native_call": "caller-cleaned two-float stack call",
      "receiver": "unchanged ECX value",
      "role": "Cell-mode orchestration body",
      "stack_words": [
        "first float word",
        "second float word"
      ],
      "wrapper_cleanup_bytes": 8
    }
  ],
  "manifest_callers": [],
  "nearby_reconstructed": [
    "0x00e806b0"
  ],
  "scc": {
    "id": "scc-0559",
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
      "shared_types:OpaqueFrameRuntime"
    ],
    "package": "PKG-FRAME-RUNTIME-WAVE7",
    "score": 22,
    "symbol": "app_frame_update_00f47930",
    "va": "0x00f47930"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_types:DATA"
    ],
    "package": "PKG-FRAME-RUNTIME-WAVE8",
    "score": 9,
    "symbol": "timing_update_body_00b31cc0",
    "va": "0x00b31cc0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "direct_xref_neighbor"
    ],
    "package": "PKG-FRAME-RUNTIME-WAVE8",
    "score": 9,
    "symbol": "cell_update_body_00e806b0",
    "va": "0x00e806b0"
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
    "symbol": "cell_mode_str
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__cCellModeStrategy__Update.c",
  "file": "src/reconstruction/pkg_frame_runtime_wave7/frame_runtime_wave7.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__cCellModeStrategy__Update.c",
    "src/reconstruction/pkg_frame_runtime_wave7/frame_runtime_wave7.cpp",
    "src/reconstruction/pkg_frame_runtime_wave7/frame_runtime_wave7.hpp",
    "src/reconstruction/pkg_frame_runtime_wave7/frame_runtime_wave7_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave7/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-frame-runtime-wave7/00e80980.json"
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
        "0x00e80980",
        "0x00e818f0",
        "0x00e81cf0",
        "0x00e81f30",
        "0x00e552f0",
        "0x00e7fc00",
        "0x00e616c0",
        "0x00e80d8b",
        "0x01485550",
        "0x013f57f8",
        "0x01485550",
        "0x01485558",
        "0x01485550",
        "0x01485550",
        "0x01485558",
        "0x01485550"
      ],
      "conflict_id": "VT-002",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "RESOLVED_OBSERVED",
      "resolution_status": "RESOLVED_OBSERVED",
      "source": "knowledgegraph/research/conflicts/track-a-type-signature.json",
      "subject": "0x01485550/0x01485558 cCellModeStrategy vtable owner and base",
      "unresolved_reason": "The exact source-level name of the secondary subobject and the language-level interface declaration remain unproven, but the disputed table owner/base is resolved."
    },
    {
      "anchors": [
        "0x00aeb160",
        "0x00aebe90",
        "0x00aeb160",
        "0x00aebe90",
        "0x00f47b10",
        "0x00e552f0",
        "0x00e552f0",
        "0x00e7fc00",
        "0x00e7fc00",
        "0x00e80980",
        "0x00e80980",
        "0x00e81cf0",
        "0x00e81cf0",
        "0x00e81f30",
        "0x00e81f30",
        "0x00f47930"
      ],
      "conflict_id": "unresolved:knowledgegraph/research/state-machines/temporal-semantics.json:4",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "Deferred trigger and owner/order semantics are not recovered; no immediate dispatch equivalence i
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/App__cCellModeStrategy__Update.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave7/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-frame-runtime-wave7/00e80980.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_frame_runtime_wave7/frame_runtime_wave7.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_frame_runtime_wave7/frame_runtime_wave7.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_frame_runtime_wave7/frame_runtime_wave7_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/App__cCellModeStrategy__Update.c",
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
      "ref": "reconstruction/metadata/pkg-frame-runtime-wave7/00e80980.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_frame_runtime_wave7/frame_runtime_wave7.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/re
[TRUNCATED]
```
