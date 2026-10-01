# Reconstruction context 0x00e54270

- Status: `partial`
- Content SHA-256: `6faaa08d3d24dec9183ec30afae4a3ade2bd430e54e19870c6ca7364e589148b`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00e54270",
  "phase": "reconstruction",
  "target": "0x00e54270"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "Simulator::Cell::cCellUI::Load",
  "package": null,
  "subsystem": "Simulator",
  "va": "0x00e54270"
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
  "content_sha256": "51436358ad2dc3ba8a96f09347409c0be6a26f02ee2c47b4524271a118d522a0",
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
      "callsite": "0x00e81688",
      "direction": "in",
      "other": "0x00e81120",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e81b46",
      "direction": "in",
      "other": "0x00e819b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e5441c",
      "direction": "out",
      "other": "0x00697980",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e54801",
      "direction": "out",
      "other": "0x007b07e0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e54867",
      "direction": "out",
      "other": "0x007b1e90",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e545ee",
      "direction": "out",
      "other": "0x00806e40",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e544b8",
      "direction": "out",
      "other": "0x00810000",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e54526",
      "direction": "out",
      "other": "0x008105b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e5453f",
      "direction": "out",
      "other": "0x008105b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e54563",
      "direction": "out",
      "other": "0x008105b0",
      "reference_type": "direct-call
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
      "callsite": "0x00e81688",
      "direction": "in",
      "other": "0x00e81120",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e81b46",
      "direction": "in",
      "other": "0x00e819b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e5441c",
      "direction": "out",
      "other": "0x00697980",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e54801",
      "direction": "out",
      "other": "0x007b07e0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e54867",
      "direction": "out",
      "other": "0x007b1e90",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e545ee",
      "direction": "out",
      "other": "0x00806e40",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e544b8",
      "direction": "out",
      "other": "0x00810000",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e54526",
      "direction": "out",
      "other": "0x008105b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e5453f",
      "direction": "out",
      "other": "0x008105b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e54563",
      
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__cCellUI__Load.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__cCellUI__Load.c"
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
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__cCellUI__Load.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__cCellUI__Load.c",
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
    ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__cCellUI__Load.c"
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
