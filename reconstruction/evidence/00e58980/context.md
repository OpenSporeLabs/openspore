# Reconstruction context 0x00e58980

- Status: `partial`
- Content SHA-256: `5cf6ff91c31fec900eeb6f5251563237b1b772983e52315369b424586e839f1d`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00e58980",
  "phase": "reconstruction",
  "target": "0x00e58980"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "Simulator::Cell::GetDamageAmount",
  "package": null,
  "subsystem": "Simulator",
  "va": "0x00e58980"
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
  "content_sha256": "74bfd8a1009f0981f5ad6822747cdd3101bd418976ee049829ba129c983adb4e",
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
      "name": "Simulator::Cell::GetScaleDifferenceWithPlayer",
      "reconstructed": false,
      "va": "0x00e57340"
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e71520"
    },
    {
      "name": "FUN_00e7a7c0",
      "reconstructed": true,
      "va": "0x00e7a7c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e7b0a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e7dbd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e7dd90"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00e71910",
      "direction": "in",
      "other": "0x00e71520",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7a812",
      "direction": "in",
      "other": "0x00e7a7c0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7b1af",
      "direction": "in",
      "other": "0x00e7b0a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7dcc6",
      "direction": "in",
      "other": "0x00e7dbd0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7de6e",
      "direction": "in",
      "other": "0x00e7dd90",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e5899e",
      "direction": "out",
      "other": "0x00e57340",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e589e1",
      "direction": "out",
      "other": "0x00e57340",
      "reference_type": "direct-call"
    },
  
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
      "name": "Simulator::Cell::GetScaleDifferenceWithPlayer",
      "reconstructed": false,
      "va": "0x00e57340"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e71520"
    },
    {
      "name": "FUN_00e7a7c0",
      "reconstructed": true,
      "va": "0x00e7a7c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e7b0a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e7dbd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e7dd90"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00e71910",
      "direction": "in",
      "other": "0x00e71520",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7a812",
      "direction": "in",
      "other": "0x00e7a7c0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7b1af",
      "direction": "in",
      "other": "0x00e7b0a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7dcc6",
      "direction": "in",
      "other": "0x00e7dbd0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7de6e",
      "direction": "in",
      "other": "0x00e7dd90",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e5899e",
      "direction": "out",
      "other": "0x00e57340",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e589e1",
      "direction"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__GetDamageAmount.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__GetDamageAmount.c"
  ],
  "handoffs": [],
  "metadata": []
}
```

## 13_semantic_hypotheses

- State: `missing`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

## 14_conflicts_questions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json, knowledgegraph/research/semantic-decomp.json`

```json
{
  "conflicts": [],
  "unresolved_questions": []
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__GetDamageAmount.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__GetDamageAmount.c",
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
    ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__GetDamageAmount.c"
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
