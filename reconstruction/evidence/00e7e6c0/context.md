# Reconstruction context 0x00e7e6c0

- Status: `partial`
- Content SHA-256: `4479715cb49c7647e6f397200764ab954cf3493bfe3cb4b6e968e4cee41e41b0`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00e7e6c0",
  "phase": "reconstruction",
  "target": "0x00e7e6c0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueBehaviorTimerRecord",
  "name": "cell_behavior_timer_update_00e7e6c0",
  "package": "PKG-06D-CELL-BEHAVIOR-TIMER",
  "subsystem": "Simulator.Cell.BehaviorTimer",
  "va": "0x00e7e6c0"
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
  "content_sha256": "1fa5b50641a86a390d9a6a58e37ed1c884051850dbe0b73cbdec2360cf604d0a",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00e7e6c0 failed: Decompilation did not complete. Reason: ",
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
  "convention": "custom EAX record plus ECX residue plus one caller-cleaned float stack argument",
  "return": "void-like; all exits are plain RET and no EAX return contract is defined"
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
      "va": "0x00e7e7a0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00e7e7d0",
      "direction": "in",
      "other": "0x00e7e7a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7e6dc",
      "direction": "out",
      "other": "0x00e59c10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7e738",
      "direction": "out",
      "other": "0x00e7b540",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7e776",
      "direction": "out",
      "other": "0x00e7ba30",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7e6f4",
      "direction": "out",
      "other": "0x00e7e130",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7e78e",
      "direction": "out",
      "other": "0x00e7e130",
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
    "global:0x00005198",
    "global:0x016b3c04",
    "global:g_cell_game_016b3c04"
  ],
  "types": [
    "AdvanceCallContext",
    "ExpireCallContext",
    "FallbackCallContext",
    "GateCallContext",
    "NativePorts&",
    "OpaqueBehaviorTimerEntryEcx",
    "OpaqueBehaviorTimerRecord",
    "OpaqueBehaviorTimerRecord*",
    "PKG-06D-CELL-BEHAVIOR-TIMER::NativePorts",
    "float",
    "opaque caller residue"
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
      "gate-cell-behavior-timer"
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
      "va": "0x00e7e7a0"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00e7e7d0",
      "direction": "in",
      "other": "0x00e7e7a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7e6dc",
      "direction": "out",
      "other": "0x00e59c10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7e738",
      "direction": "out",
      "other": "0x00e7b540",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7e776",
      "direction": "out",
      "other": "0x00e7ba30",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7e6f4",
      "direction": "out",
      "other": "0x00e7e130",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7e78e",
      "direction": "out",
      "other": "0x00e7e130",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 1,
  "fan_out": 0,
  "manifest_callees": [
    "0x00e59c10",
    "0x00e7b540",
    "0x00e7ba30",
    "0x00e7e130"
  ],
  "manifest_callers": [
    "0x00e7e7a0"
  ],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0555",
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
      "shared_types:NativePorts&"
    ],
    "package": "PKG-06C-CELL-BEHAVIOR-DISPATCH",
    "score": 3,
    "symbol": "cell_behavior_dispatch_00e7a190",
    "va": "0x00e7a190"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg06d_cell_behavior_timer/cell_behavior_timer.cpp",
  "files": [
    "reconstruction/staging/pkg06d-cell-behavior-timer/cell_behavior_timer.cpp",
    "reconstruction/staging/pkg06d-cell-behavior-timer/cell_behavior_timer.hpp",
    "reconstruction/staging/pkg06d-cell-behavior-timer/cell_behavior_timer_model_test.cpp",
    "src/reconstruction/pkg06d_cell_behavior_timer/cell_behavior_timer.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-pkg06d-cell-behavior-timer/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg06d-cell-behavior-timer/00e7e6c0.json"
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
        "0x00e7a4a0",
        "0x00e7a7c0",
        "0x00e7a7c0",
        "0x00e7e6c0",
        "0x00e7a4a0",
        "0x00e7a4a0",
        "0x00e62340",
        "0x00e52910",
        "0x00e7a7c0",
        "0x00e7a7c0",
        "0x00bfc460",
        "0x00bfc460",
        "0x00bfc490",
        "0x00bfc490",
        "0x00bfc4a0",
        "0x00bfc4a0"
      ],
      "conflict_id": "cell_field_112_semantics",
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
        "0x00e52910",
        "0x00e575f0",
        "0x00e52910",
        "0x00e7e6c0",
        "0x00e7a7c0",
        "0x00e7a4a0",
        "0x00e52910",
        "0x00e7a7c0",
        "0x00e72060",
        "0x00e52910",
        "0x00e52910",
        "0x00e52910",
        "0x00e575f0",
        "0x00e575f0",
        "0x00e575f0",
        "0x00e7a4a0"
      ],
      "conflict_id": "cell_target_selector_domain",
      "kind": "conflict_ledger",
      "rej
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-pkg06d-cell-behavior-timer/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg06d-cell-behavior-timer/00e7e6c0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg06d-cell-behavior-timer/cell_behavior_timer.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg06d-cell-behavior-timer/cell_behavior_timer.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg06d-cell-behavior-timer/cell_behavior_timer_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg06d_cell_behavior_timer/cell_behavior_timer.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/integrated/batch-2026-09-25-pkg06d-cell-behavior-timer/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg06d-cell-behavior-timer/00e7e6c0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg06d-cell-behavior-timer/cell_behavior_timer.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg06d-cell-behavior-timer/cell_behavior_timer.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persis
[TRUNCATED]
```
