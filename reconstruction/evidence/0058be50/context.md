# Reconstruction context 0x0058be50

- Status: `partial`
- Content SHA-256: `11dbd48aa5c940f97e162288f190623987b2709fff308ee0610f9e436dec802c`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x0058be50",
  "phase": "reconstruction",
  "target": "0x0058be50"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "Editors::cEditor::Update",
  "package": null,
  "subsystem": "Editor",
  "va": "0x0058be50"
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
  "status": "queued"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "0c05259336d481db5c21aacdd57e4f529945d8a0055d2b9c05a35d470c618e7a",
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
      "name": "FUN_0044ae00",
      "reconstructed": false,
      "va": "0x0044ae00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0045b150"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0045b210"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004c49e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059d110"
    },
    {
      "name": "editor_row_publish_005a2010",
      "reconstructed": true,
      "va": "0x005a2010"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005dc310"
    },
    {
      "name": "anim_manager_get_0067cae0",
      "reconstructed": true,
      "va": "0x0067cae0"
    },
    {
      "name": "app_direct_property_list_get_direct_bool_006a25a0",
      "reconstructed": true,
      "va": "0x006a25a0"
    },
    {
      "name": "sporepedia_nop_slot_FUN_00c2e4e0",
      "reconstructed": true,
      "va": "0x00c2e4e0"
    },
    {
      "name": "map_int_whatever_find",
      "reconstructed": true,
      "va": "0x00e5c780"
    }
  ],
  "callers": [],
  "edge_rows": [
    {
      "callsite": "0x0058bf3e",
      "direction": "out",
      "other": "0x00401050",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0058bf6b",
      "direction": "out",
      "other": "0x00401050",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0058c3d3",
      "direction": "out",
      "other": "0x00401050",
      "reference_type": "direct-call"
    },
    {
      "c
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
    "vtable:0x013f57f8"
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
      "name": "FUN_0044ae00",
      "reconstructed": false,
      "va": "0x0044ae00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0045b150"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0045b210"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004c49e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059d110"
    },
    {
      "name": "editor_row_publish_005a2010",
      "reconstructed": true,
      "va": "0x005a2010"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005dc310"
    },
    {
      "name": "anim_manager_get_0067cae0",
      "reconstructed": true,
      "va": "0x0067cae0"
    },
    {
      "name": "app_direct_property_list_get_direct_bool_006a25a0",
      "reconstructed": true,
      "va": "0x006a25a0"
    },
    {
      "name": "sporepedia_nop_slot_FUN_00c2e4e0",
      "reconstructed": true,
      "va": "0x00c2e4e0"
    },
    {
      "name": "map_int_whatever_find",
      "reconstructed": true,
      "va": "0x00e5c780"
    }
  ],
  "callees_truncated": false,
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x0058bf3e",
      "direction": "out",
      "other": "0x00401050",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0058bf6b",
      "direction": "out",
      "other": "0x00401050",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0058c3d3",
      "direction": "out",
   
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
      "shared_vtable:vtable:0x013f57f8"
    ],
    "package": "pkg-editor-w1-0057d6f0",
    "score": 10,
    "symbol": "re_0057d6f0",
    "va": "0x0057d6f0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013f57f8"
    ],
    "package": "pkg-swarm-w2-00586700",
    "score": 10,
    "symbol": "re_00586700",
    "va": "0x00586700"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013f57f8"
    ],
    "package": "pkg-swarm-w1-005b2490",
    "score": 10,
    "symbol": "re_005b2490",
    "va": "0x005b2490"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013f57f8"
    ],
    "package": "pkg-swarm-w1-005ba0d0",
    "score": 10,
    "symbol": "re_005ba0d0",
    "va": "0x005ba0d0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013f57f8"
    ],
    "package": "pkg-editor-child-007f30d0",
    "score": 10,
    "symbol": "FUN_007f30d0",
    "va": "0x007f30d0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013f57f8"
    ],
    "package": "pkg-shared-default-true-wave12",
    "score": 10,
    "symbol": "pkg_shared_default_true_00b1fbf0",
    "va": "0x00b1fbf0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013f57f8"
    ],
    "package": "pkg-w2-00e5cac0",
    "score": 10,
    "symbol": "FUN_00e5cac0",
    "va": "0x00e5cac0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "pkg-vft-preinc-0051e340",

[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditor__Update.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditor__Update.c"
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
        "0x007d85b0",
        "0x007d8c80",
        "0x007d8cf0",
        "0x007d8d40",
        "0x01412598",
        "0x01412598",
        "0x007d8c80",
        "0x007d8c80",
        "0x007d85b0",
        "0x0212d3e7",
        "0x022d1adc",
        "0x00582fe0",
        "0x00582fe0",
        "0x00587270",
        "0x00587270",
        "0x0058be50"
      ],
      "conflict_id": "game_mode_transition_branches",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The cited producer, consumer, or registration surface is retained, but the complete event-to-message mapping, timing, and payload contract remain unresolved.",
      "resolution_status": "The cited producer, consumer, or registration surface is retained, but the complete event-to-message mapping, timing, and payload contract remain unresolved.",
      "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
      "subject": null,
      "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
    },
    {
      "anchors": [
        "0x00574080",
        "0x00586410",
        "0x0058ac10",
        "0x0058ac10",
        "0x004af260",
        "0x00574080",
        "0x00576c50",
        "0x00576c50",
        "0x0057ce80",
        "0x0057ce80",
        "0x00584300",
        "0x00584300",
        "0x00586410",
        "0x00587a20",
        "0x00587a20",
        "0x0058be50"
      ],
      "conflict_id": "history_budget_semantics",
      "kind": "conflict_ledger",
      "rejected": [],
    
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditor__Update.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditor__Update.c",
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
    ".spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditor__Update.c"
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
