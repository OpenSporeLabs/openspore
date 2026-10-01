# Reconstruction context 0x00e81cf0

- Status: `partial`
- Content SHA-256: `c4a7acab768e7a66083e8cdf276292f7ac0e2dc5703c920c0915096ff357688b`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00e81cf0",
  "phase": "reconstruction",
  "target": "0x00e81cf0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "App::cCellModeStrategy::Initialize",
  "package": null,
  "subsystem": "App",
  "va": "0x00e81cf0"
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
  "content_sha256": "d128df7ee6084b3089caabd8e9dd7c89d69a957250181eac4e649bc4ef6e4cb0",
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
      "name": "property_value_resolve_0041e920",
      "reconstructed": true,
      "va": "0x0041e920"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0067dcc0"
    }
  ],
  "callers": [],
  "edge_rows": [
    {
      "callsite": "0x00e81f0c",
      "direction": "out",
      "other": "0x0041e920",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e81def",
      "direction": "out",
      "other": "0x0067dcc0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e81e52",
      "direction": "out",
      "other": "0x0067dcc0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e81e71",
      "direction": "out",
      "other": "0x0067dcc0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e81e90",
      "direction": "out",
      "other": "0x0067dcc0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e81eaf",
      "direction": "out",
      "other": "0x0067dcc0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e81ece",
      "direction": "out",
      "other": "0x0067dcc0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e81e0b",
      "direction": "out",
      "other": "0x0067ddd0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e81d3d",
      "direction": "out",
      "other": "0x00692850",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e81d0e",
      "direction": "out",
      "other": "0x00692f60",
      
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
      "name": "property_value_resolve_0041e920",
      "reconstructed": true,
      "va": "0x0041e920"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0067dcc0"
    }
  ],
  "callees_truncated": false,
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 1,
  "edges": [
    {
      "callsite": "0x00e81f0c",
      "direction": "out",
      "other": "0x0041e920",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e81def",
      "direction": "out",
      "other": "0x0067dcc0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e81e52",
      "direction": "out",
      "other": "0x0067dcc0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e81e71",
      "direction": "out",
      "other": "0x0067dcc0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e81e90",
      "direction": "out",
      "other": "0x0067dcc0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e81eaf",
      "direction": "out",
      "other": "0x0067dcc0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e81ece",
      "direction": "out",
      "other": "0x0067dcc0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e81e0b",
      "direction": "out",
      "other": "0x0067ddd0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e81d3d",
      "direction": "out",
      "other": "0x00692850",
      "reference_type": "direct-call"
    },
    {
      "c
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__cCellModeStrategy__Initialize.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__cCellModeStrategy__Initialize.c"
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
        "0x00e81cf0",
        "0x00e81f30",
        "0x00e81cf0",
        "0x00e81cf0",
        "0x00e81f30",
        "0x00e81cf0",
        "0x00e81f30",
        "0x00e81cf0",
        "0x00e81f30",
        "0x00e81cf0",
        "0x00e81f30"
      ],
      "conflict_id": "U09",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
      "resolution_status": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
      "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
      "subject": null,
      "u
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/App__cCellModeStrategy__Initialize.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/App__cCellModeStrategy__Initialize.c",
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
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__cCellModeStrategy__Initialize.c"
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
