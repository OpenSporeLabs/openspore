# Reconstruction context 0x00e55120

- Status: `partial`
- Content SHA-256: `436e74ff7560b19a2137630b2f06d99723a8ec79109e207b1eaf9c3cd9092182`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00e55120",
  "phase": "reconstruction",
  "target": "0x00e55120"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "Simulator::Cell::cCellGFX::StartDisplay",
  "package": null,
  "subsystem": "Simulator",
  "va": "0x00e55120"
}
```

## 03_current_status

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "blocked": false,
  "reconstructed": false,
  "runtime_gated": false,
  "runtime_validated": 0,
  "status": "implemented"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "6b03ba14e812538b856f213340128b4010fbd41429be41be1efda583590afa5b",
  "live_attempts": [],
  "live_requested": false,
  "overall": "PERSISTED"
}
```

## 05_decompilation

- State: `missing`
- Provenance: ``

## 06_abi

- State: `missing`
- Provenance: `reconstruction/knowledge/index.json`

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [],
  "callers": [
    {
      "name": "App::cCellModeStrategy::OnEnter",
      "reconstructed": false,
      "va": "0x00e552f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e81120"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00e5531c",
      "direction": "in",
      "other": "0x00e552f0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e8169a",
      "direction": "in",
      "other": "0x00e81120",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e55120",
      "direction": "out",
      "other": "0x0067dd50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e55137",
      "direction": "out",
      "other": "0x0067dd50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e5514e",
      "direction": "out",
      "other": "0x0067dd50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e55165",
      "direction": "out",
      "other": "0x0067dd50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e5522d",
      "direction": "out",
      "other": "0x0067dd80",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e55248",
      "direction": "out",
      "other": "0x0067ddd0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e5528f",
      "direction": "out",
      "other": "0x00810590",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e55279",
      "direction": "out",
      "other": "0x00e82500",
      "
[TRUNCATED]
```

## 08_types_fields_globals

- State: `missing`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [],
  "vtables": []
}
```

## 09_state_event_relationships

- State: `missing`
- Provenance: `knowledgegraph/research/semantic-decomp.json, reconstruction/knowledge/index.json`

```json
{
  "runtime": {
    "blocking_reason": null,
    "gates": [],
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
      "name": "App::cCellModeStrategy::OnEnter",
      "reconstructed": false,
      "va": "0x00e552f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e81120"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00e5531c",
      "direction": "in",
      "other": "0x00e552f0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e8169a",
      "direction": "in",
      "other": "0x00e81120",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e55120",
      "direction": "out",
      "other": "0x0067dd50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e55137",
      "direction": "out",
      "other": "0x0067dd50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e5514e",
      "direction": "out",
      "other": "0x0067dd50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e55165",
      "direction": "out",
      "other": "0x0067dd50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e5522d",
      "direction": "out",
      "other": "0x0067dd80",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e55248",
      "direction": "out",
      "other": "0x0067ddd0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e5528f",
      "direction": "out",
      "other": "0x00810590",
      "reference_type": "direct-call"
    },
    {
      "ca
[TRUNCATED]
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-11-H4-HELPER-WAVE3",
    "score": 6,
    "symbol": "address_window_offset_005c65e0",
    "va": "0x005c65e0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-SIMULATOR-SAFE-WAVE11",
    "score": 6,
    "symbol": "dispatch_key_00628450",
    "va": "0x00628450"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-SIMULATOR-SAFE-WAVE11",
    "score": 6,
    "symbol": "cycle_key_006286a0",
    "va": "0x006286a0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-SIMULATOR-SAFE-WAVE11",
    "score": 6,
    "symbol": "release_child_0062c910",
    "va": "0x0062c910"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 6,
    "symbol": "FUN_00b3d2a0",
    "va": "0x00b3d2a0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 6,
    "symbol": "FUN_00b3d300",
    "va": "0x00b3d300"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 6,
    "symbol": "Simulator_GetUIMissionLogManager",
    "va": "0x00b3d4f0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-13-E4-EMPIRE-WAVE3",
    "score": 6,
    "symbol": "EmpirePoliticalColor_00c32cd0",
    "va": "0x00c32cd0"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__cCellGFX__StartDisplay.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__cCellGFX__StartDisplay.c"
  ],
  "handoffs": [],
  "metadata": []
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
        "0x00e5dba0",
        "0x00e5dba0",
        "0x008df730",
        "0x00e666f0",
        "0x00e55120"
      ],
      "conflict_id": "preload-readiness",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "Preload traversal and display-start boundaries are concrete. Completion barrier, waitUntilLoaded behavior, and fatal-child behavior are unresolved.",
      "resolution_status": "Preload traversal and display-start boundaries are concrete. Completion barrier, waitUntilLoaded behavior, and fatal-child behavior are unresolved.",
      "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
      "subject": null,
      "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
    }
  ],
  "unresolved_questions": []
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__cCellGFX__StartDisplay.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__cCellGFX__StartDisplay.c",
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
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.json",
    ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__cCellGFX__StartDisplay.c"
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
