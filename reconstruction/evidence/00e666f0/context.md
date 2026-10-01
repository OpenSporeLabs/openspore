# Reconstruction context 0x00e666f0

- Status: `partial`
- Content SHA-256: `af5e47118dc00b554db29b782775ebe73f83189c7060f77f60f295c4b1f31f37`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00e666f0",
  "phase": "reconstruction",
  "target": "0x00e666f0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "Simulator::Cell::cCellGFX::PreloadResources",
  "package": null,
  "subsystem": "Simulator",
  "va": "0x00e666f0"
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
  "content_sha256": "d30d5f3bf878ad17000f9f7334a21249a0aad379db40d8df5307ff69574fb7af",
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
      "name": "Simulator::Cell::cCellGFX::PreloadCellResource",
      "reconstructed": false,
      "va": "0x00e663b0"
    },
    {
      "name": "Simulator::Cell::cCellGFX::PreloadPopulateResource",
      "reconstructed": false,
      "va": "0x00e665c0"
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e819b0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00e81acb",
      "direction": "in",
      "other": "0x00e819b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e66727",
      "direction": "out",
      "other": "0x00743b50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e66758",
      "direction": "out",
      "other": "0x00743b50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e6681b",
      "direction": "out",
      "other": "0x009a9600",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e66765",
      "direction": "out",
      "other": "0x00e4cc40",
      "reference_type": "thunk"
    },
    {
      "callsite": "0x00e667a8",
      "direction": "out",
      "other": "0x00e4cce0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e667ba",
      "direction": "out",
      "other": "0x00e4cce0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e667cc",
      "direction": "out",
      "other": "0x00e4cce0",
      "ref
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
      "name": "Simulator::Cell::cCellGFX::PreloadCellResource",
      "reconstructed": false,
      "va": "0x00e663b0"
    },
    {
      "name": "Simulator::Cell::cCellGFX::PreloadPopulateResource",
      "reconstructed": false,
      "va": "0x00e665c0"
    }
  ],
  "callees_truncated": false,
  "callers": [
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
      "callsite": "0x00e81acb",
      "direction": "in",
      "other": "0x00e819b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e66727",
      "direction": "out",
      "other": "0x00743b50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e66758",
      "direction": "out",
      "other": "0x00743b50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e6681b",
      "direction": "out",
      "other": "0x009a9600",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e66765",
      "direction": "out",
      "other": "0x00e4cc40",
      "reference_type": "thunk"
    },
    {
      "callsite": "0x00e667a8",
      "direction": "out",
      "other": "0x00e4cce0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e667ba",
      "direction": "out",
      "other": "0x00e4cce0",
      "reference_type": "direct-call"
    },
    {
      "calls
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__cCellGFX__PreloadResources.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__cCellGFX__PreloadResources.c"
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
        "0x00c932f0",
        "0x00b237c0",
        "0x00c983c0",
        "0x00e74a20",
        "0x00e4ce20",
        "0x00e665c0",
        "0x00e666f0",
        "0x00b237c0",
        "0x00c983c0",
        "0x00c932f0"
      ],
      "conflict_id": "U-006-herd-respawn-evolution",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
      "resolution_status": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
      "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
      "subject": null,
      "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
    },
    {
      "anchors": [
        "0x00c932f0",
        "0x00c983c0",
        "0x00e74a20",
        "0x00e4ce20",
        "0x00e665c0",
        "0x00e666f0",
        "0x00be34a0",
        "0x00bddef0",
        "0x00bdde70",
        "0x00ca6630",
        "0x00ca6630"
      ],
      "conflict_id": "U-007-city-population-vehicle",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
      "resolution_status": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__cCellGFX__PreloadResources.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__cCellGFX__PreloadResources.c",
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
    ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__cCellGFX__PreloadResources.c"
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
