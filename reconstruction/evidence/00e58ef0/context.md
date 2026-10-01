# Reconstruction context 0x00e58ef0

- Status: `partial`
- Content SHA-256: `17cff5edaec38983d231ec3407e1ae8f208aa923c945dd0bad3da282a3eb39f9`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00e58ef0",
  "phase": "reconstruction",
  "target": "0x00e58ef0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "Simulator::Cell::GetCurrentAdvectInfo",
  "package": null,
  "subsystem": "Simulator",
  "va": "0x00e58ef0"
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
  "content_sha256": "6367787b90a5eb1e7aceb980d9582360181553385188da325b0cd167a8e178a0",
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
      "name": "embedded_object_first_word_init_00743b50",
      "reconstructed": true,
      "va": "0x00743b50"
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e5f360"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00e5f379",
      "direction": "in",
      "other": "0x00e5f360",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e58f01",
      "direction": "out",
      "other": "0x00743b50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e58f18",
      "direction": "out",
      "other": "0x00e4cc40",
      "reference_type": "thunk"
    },
    {
      "callsite": "0x00e58fc8",
      "direction": "out",
      "other": "0x00e82130",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e58fff",
      "direction": "out",
      "other": "0x00e82130",
      "reference_type": "direct-call"
    }
  ],
  "external_callees": []
}
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
      "name": "embedded_object_first_word_init_00743b50",
      "reconstructed": true,
      "va": "0x00743b50"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e5f360"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00e5f379",
      "direction": "in",
      "other": "0x00e5f360",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e58f01",
      "direction": "out",
      "other": "0x00743b50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e58f18",
      "direction": "out",
      "other": "0x00e4cc40",
      "reference_type": "thunk"
    },
    {
      "callsite": "0x00e58fc8",
      "direction": "out",
      "other": "0x00e82130",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e58fff",
      "direction": "out",
      "other": "0x00e82130",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 1,
  "fan_out": 1,
  "manifest_callees": [],
  "manifest_callers": [],
  "nearby_reconstructed": [
    "0x00743b50"
  ],
  "scc": {
    "id": "scc-0526",
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__GetCurrentAdvectInfo.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__GetCurrentAdvectInfo.c"
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
        "0x00e82340",
        "0x00e82420",
        "0x00e82420",
        "0x00e82340",
        "0x00e82340",
        "0x00e82420",
        "0x00e82420",
        "0x00e82340",
        "0x00e82340",
        "0x00e82420",
        "0x00e82340",
        "0x00e82420",
        "0x00e82340",
        "0x00e4ace0",
        "0x00e4cde0",
        "0x00e58ef0"
      ],
      "conflict_id": "LC-004",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "RESOLVED_OBSERVED",
      "resolution_status": "RESOLVED_OBSERVED",
      "source": "knowledgegraph/research/conflicts/track-a-type-signature.json",
      "subject": "0x00E82420 and 0x00E82340 cCellDataReference_::Create identity",
      "unresolved_reason": "Only the private helper's exact source-level name is unknown; its behavior, size, ownership role, and non-alias relationship are resolved."
    },
    {
      "anchors": [
        "0x00e58ef0",
        "0x00e58e30",
        "0x00000008",
        "0x00e58ef0",
        "0x00e58e30"
      ],
      "conflict_id": "TB-FL-005",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": {
        "merge_decision": "preferred_claim_with_limit",
        "preferred_claim": "Use float32 for the observed GetCurrentAdvectInfo arithmetic path, with the imported integer alternative retained until the writer and wire/raw-byte behavior are recovered.",
        "preserved_alternatives": true,
        "scope_note": "The preferred claim concerns observed mechanics, not the persistence field contract or value-range proof."
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__GetCurrentAdvectInfo.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__GetCurrentAdvectInfo.c",
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
    ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__GetCurrentAdvectInfo.c"
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
