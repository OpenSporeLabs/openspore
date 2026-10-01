# Reconstruction context 0x00e663b0

- Status: `partial`
- Content SHA-256: `89e23976a7787705c409f571f191e02b5cc5cd597eda39dfae92f716c6d922c6`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00e663b0",
  "phase": "reconstruction",
  "target": "0x00e663b0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "Simulator::Cell::cCellGFX::PreloadCellResource",
  "package": null,
  "subsystem": "Simulator",
  "va": "0x00e663b0"
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
  "content_sha256": "598f57f23ec90dcf712ae32b866050662817e8b41ce7100ad530b0869e687014",
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
    },
    {
      "name": "map_int_whatever_find",
      "reconstructed": true,
      "va": "0x00e5c780"
    },
    {
      "name": "Simulator::Cell::cCellGFX::PreloadCreature",
      "reconstructed": false,
      "va": "0x00e64980"
    },
    {
      "name": "Simulator::Cell::cCellGFX::AddPreloadedModel2",
      "reconstructed": false,
      "va": "0x00e653a0"
    },
    {
      "name": "Simulator::Cell::cCellGFX::AddPreloadedEffect",
      "reconstructed": false,
      "va": "0x00e66280"
    },
    {
      "name": "Simulator::Cell::cCellGFX::PreloadCellResource",
      "reconstructed": false,
      "va": "0x00e663b0"
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e4fc20"
    },
    {
      "name": "Simulator::Cell::cCellGFX::PreloadCellResource",
      "reconstructed": false,
      "va": "0x00e663b0"
    },
    {
      "name": "Simulator::Cell::cCellGFX::PreloadPopulateResource",
      "reconstructed": false,
      "va": "0x00e665c0"
    },
    {
      "name": "Simulator::Cell::cCellGFX::PreloadResources",
      "reconstructed": false,
      "va": "0x00e666f0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00e4fc74",
      "direction": "in",
      "other": "0x00e4fc20",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e66500",
      "direction": "in",
      "other": "0x00e663b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e6
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
      "name": "embedded_object_first_word_init_00743b50",
      "reconstructed": true,
      "va": "0x00743b50"
    },
    {
      "name": "map_int_whatever_find",
      "reconstructed": true,
      "va": "0x00e5c780"
    },
    {
      "name": "Simulator::Cell::cCellGFX::PreloadCreature",
      "reconstructed": false,
      "va": "0x00e64980"
    },
    {
      "name": "Simulator::Cell::cCellGFX::AddPreloadedModel2",
      "reconstructed": false,
      "va": "0x00e653a0"
    },
    {
      "name": "Simulator::Cell::cCellGFX::AddPreloadedEffect",
      "reconstructed": false,
      "va": "0x00e66280"
    },
    {
      "name": "Simulator::Cell::cCellGFX::PreloadCellResource",
      "reconstructed": false,
      "va": "0x00e663b0"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e4fc20"
    },
    {
      "name": "Simulator::Cell::cCellGFX::PreloadCellResource",
      "reconstructed": false,
      "va": "0x00e663b0"
    },
    {
      "name": "Simulator::Cell::cCellGFX::PreloadPopulateResource",
      "reconstructed": false,
      "va": "0x00e665c0"
    },
    {
      "name": "Simulator::Cell::cCellGFX::PreloadResources",
      "reconstructed": false,
      "va": "0x00e666f0"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00e4fc74",
      "direction": "in",
      "other": "0x00e4fc20",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e66500",
      "direction": "in",
      "other": "0x00
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__cCellGFX__PreloadCellResource.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__cCellGFX__PreloadCellResource.c"
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
        "0x00e663b0",
        "0x00e663b0",
        "0x00e666f0"
      ],
      "conflict_id": "effect-failure",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "cCellGFX effect synchronization contains direct Stop/Release versus Create/Start branches. Whether each failure is optional or stage-fatal is unresolved.",
      "resolution_status": "cCellGFX effect synchronization contains direct Stop/Release versus Create/Start branches. Whether each failure is optional or stage-fatal is unresolved.",
      "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
      "subject": null,
      "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
    },
    {
      "anchors": [
        "0x00e663b0",
        "0x00e663b0",
        "0x008da6f0"
      ],
      "conflict_id": "resource-manager-error-taxonomy",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
      "resolution_status": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
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
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__cCellGFX__PreloadCellResource.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__cCellGFX__PreloadCellResource.c",
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
    ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__cCellGFX__PreloadCellResource.c"
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
