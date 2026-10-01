# Reconstruction context 0x00e5dba0

- Status: `partial`
- Content SHA-256: `96c994a35b74cda973a6bab48fb0396cf3c4b740f3e1a70f6a39d2a563a072db`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00e5dba0",
  "phase": "reconstruction",
  "target": "0x00e5dba0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "Simulator::Cell::cCellGFX::Initialize",
  "package": null,
  "subsystem": "Simulator",
  "va": "0x00e5dba0"
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
  "content_sha256": "0a3a25dcc2da5baa8124083b1a04ffb5fe0b58a9d029a5df27b655cbfe3fa859",
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
  "callees": [
    {
      "name": "dispatch_key_00628450",
      "reconstructed": true,
      "va": "0x00628450"
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e81120"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e819b0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00e81690",
      "direction": "in",
      "other": "0x00e81120",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e819c9",
      "direction": "in",
      "other": "0x00e819b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e5e2a2",
      "direction": "out",
      "other": "0x00628450",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e5de93",
      "direction": "out",
      "other": "0x0067cb20",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e5e0fe",
      "direction": "out",
      "other": "0x0067cb20",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e5dc5c",
      "direction": "out",
      "other": "0x0067dd10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e5dc6e",
      "direction": "out",
      "other": "0x0067dd10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e5de06",
      "direction": "out",
      "other": "0x0067dd80",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e5df60",
      "direction": "out",
      "other": "0x0067dd80",
      "reference_type": "direct-call"
    },
    {
      "callsite
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
  "callees": [
    {
      "name": "dispatch_key_00628450",
      "reconstructed": true,
      "va": "0x00628450"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e81120"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e819b0"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00e81690",
      "direction": "in",
      "other": "0x00e81120",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e819c9",
      "direction": "in",
      "other": "0x00e819b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e5e2a2",
      "direction": "out",
      "other": "0x00628450",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e5de93",
      "direction": "out",
      "other": "0x0067cb20",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e5e0fe",
      "direction": "out",
      "other": "0x0067cb20",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e5dc5c",
      "direction": "out",
      "other": "0x0067dd10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e5dc6e",
      "direction": "out",
      "other": "0x0067dd10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e5de06",
      "direction": "out",
      "other": "0x0067dd80",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e5df60",
      "direction": "out",
      "oth
[TRUNCATED]
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "same_subsystem",
      "direct_xref_neighbor"
    ],
    "package": "PKG-SIMULATOR-SAFE-WAVE11",
    "score": 9,
    "symbol": "dispatch_key_00628450",
    "va": "0x00628450"
  },
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__cCellGFX__Initialize.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__cCellGFX__Initialize.c"
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
    },
    {
      "anchors": [
        "0x00e5dba0",
        "0x00e5dba0",
        "0x00e666f0"
      ],
      "conflict_id": "teardown-order",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The cited direct body establishes a bounded state mutation or call anchor, but the full transition policy, consumer order, and runtime reachability remain unresolved.",
      "resolution_status": "The cited direct body establishes a bounded state mutation or call anchor, but the full transition policy, consumer order, and runtime reachability remain unresolved.",
      "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
      "subject": null,
      "unresolved_reason": "Runtime reachability is absent or the required direct bod
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__cCellGFX__Initialize.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__cCellGFX__Initialize.c",
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
    ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__cCellGFX__Initialize.c"
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
