# Reconstruction context 0x00e552f0

- Status: `partial`
- Content SHA-256: `b6cd266862a8e95b368eca2a2c36f16ac1a500919851c6d0b13280e1881fa1b7`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00e552f0",
  "phase": "reconstruction",
  "target": "0x00e552f0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "App::cCellModeStrategy::OnEnter",
  "package": null,
  "subsystem": "App",
  "va": "0x00e552f0"
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
  "content_sha256": "a131d95e75f2de49eb8f74ac244e73cc19bc76d0e7f97b24dfb430e527927234",
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
      "name": "FUN_00b3d400",
      "reconstructed": true,
      "va": "0x00b3d400"
    },
    {
      "name": "Simulator::Cell::cCellGFX::StartDisplay",
      "reconstructed": false,
      "va": "0x00e55120"
    }
  ],
  "callers": [],
  "edge_rows": [
    {
      "callsite": "0x00e55326",
      "direction": "out",
      "other": "0x0067ddd0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e55317",
      "direction": "out",
      "other": "0x00697980",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e5535c",
      "direction": "out",
      "other": "0x00805070",
      "reference_type": "thunk"
    },
    {
      "callsite": "0x00e5537b",
      "direction": "out",
      "other": "0x00810660",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e5536a",
      "direction": "out",
      "other": "0x00810760",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e55380",
      "direction": "out",
      "other": "0x00b3d400",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e5538b",
      "direction": "out",
      "other": "0x00b3d400",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e55350",
      "direction": "out",
      "other": "0x00b3d410",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e55392",
      "direction": "out",
      "other": "0x00e17df0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e55357",
      "direction": "out",
      "other": "0x00e3e
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [],
  "vtables": [
    "vtable:0x01485550"
  ]
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
      "name": "FUN_00b3d400",
      "reconstructed": true,
      "va": "0x00b3d400"
    },
    {
      "name": "Simulator::Cell::cCellGFX::StartDisplay",
      "reconstructed": false,
      "va": "0x00e55120"
    }
  ],
  "callees_truncated": false,
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00e55326",
      "direction": "out",
      "other": "0x0067ddd0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e55317",
      "direction": "out",
      "other": "0x00697980",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e5535c",
      "direction": "out",
      "other": "0x00805070",
      "reference_type": "thunk"
    },
    {
      "callsite": "0x00e5537b",
      "direction": "out",
      "other": "0x00810660",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e5536a",
      "direction": "out",
      "other": "0x00810760",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e55380",
      "direction": "out",
      "other": "0x00b3d400",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e5538b",
      "direction": "out",
      "other": "0x00b3d400",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e55350",
      "direction": "out",
      "other": "0x00b3d410",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e55392",
      "direction": "out",
      "other": "0x00e17df0",
      "reference_type": "direct-call"
    },
  
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
    "package": "pkg-app-imessage-manager-dtor",
    "score": 6,
    "symbol": "get_0067dc80",
    "va": "0x0067dc80"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "pkg-cheat-func3ch-0067e6b0",
    "score": 6,
    "symbol": "func3_ch_0067e6b0",
    "va": "0x0067e6b0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "pkg-cheat-dispatch-0067e6f0",
    "score": 6,
    "symbol": "cCheatManager_func40h_0067e6f0",
    "va": "0x0067e6f0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "cheat-func44h-0067e730",
    "score": 6,
    "symbol": "func44h_0067e730",
    "va": "0x0067e730"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "pkg-app-proplist-copyall-wave16",
    "score": 6,
    "symbol": "all_copy_from_properties_006a14d0",
    "va": "0x006a14d0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "pkg-proplist-dispatch-wave14",
    "score": 6,
    "symbol": "app_property_list_add_all_properties_from_006a1510",
    "va": "0x006a1510"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "pkg-dfw-006a1540",
    "score": 6,
    "symbol": "proplist_write_006a1540",
    "va": "0x006a1540"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "pkg-property-clear-wave13",
    "score": 6,
    "symbol": "property_list_clear_006a2a80",
    "va": "0x006a2a80"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__cCellModeStrategy__OnEnter.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__cCellModeStrategy__OnEnter.c"
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
        "0x00e81cf0",
        "0x00e81cf0",
        "0x0067dcc0",
        "0x00b3d330",
        "0x00e552f0"
      ],
      "conflict_id": "U04",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
      "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
      "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
      "subject": null,
      "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
    },
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
      "unresolved_reason": "The exact source-level name of the secon
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/App__cCellModeStrategy__OnEnter.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/App__cCellModeStrategy__OnEnter.c",
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
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__cCellModeStrategy__OnEnter.c"
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
