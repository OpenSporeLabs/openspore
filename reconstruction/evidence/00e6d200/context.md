# Reconstruction context 0x00e6d200

- Status: `partial`
- Content SHA-256: `9a5e69313cd823e96a0af17c20784b4094fe56ae8845a10d7d45f417e5b5c139`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00e6d200",
  "phase": "reconstruction",
  "target": "0x00e6d200"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "Simulator::Cell::PlayAnimation",
  "package": null,
  "subsystem": "Simulator",
  "va": "0x00e6d200"
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
  "content_sha256": "b829551f9d00d344d9261f25d4c67d61e9c8d9360fa4da800cfa5dfed00f695a",
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
      "va": "0x00e6d340"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e6d8f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e6e8c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e6eb60"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e6ecb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e6ee10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e70950"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e70a90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e70b20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e70bc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e71520"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e72060"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e72200"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e72360"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e72430"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e72530"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00e6d456",
      "direction": "in",
      "other": "0x00e6d340",
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
  "callees": [],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e6d340"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e6d8f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e6e8c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e6eb60"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e6ecb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e6ee10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e70950"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e70a90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e70b20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e70bc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e71520"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e72060"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e72200"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e72360"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e72430"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e72530"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e725c0"
    },
    {
      "name": null,
      "reconst
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__PlayAnimation.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__PlayAnimation.c"
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
        "0x00e74a20",
        "0x00e57460",
        "0x00e6d200",
        "0x00e57340",
        "0x00e780a0",
        "0x00000108",
        "0x00e74a20",
        "0x00000108"
      ],
      "conflict_id": "TB-FL-012",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": {
        "merge_decision": "separate_entities",
        "preferred_claim": "Use the original direct field/body evidence as the ABI anchor.",
        "preserved_alternatives": true,
        "scope_note": "The current padding is a replacement limitation and cannot define the original structure.",
        "status": "preferred_claim_with_limit",
        "taxonomy": "preferred_claim_with_limit"
      },
      "resolution_status": "preferred_claim_with_limit",
      "source": "knowledgegraph/research/conflicts/track-b-vtable-fields.json",
      "subject": "cCellObjectData original middle fields versus current opaque padding",
      "unresolved_reason": "The cited static evidence leaves the competing owner, slot, layout, or lifecycle interpretation unresolved; no positive original runtime or MSVC RTTI evidence is available."
    }
  ],
  "unresolved_questions": []
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__PlayAnimation.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__PlayAnimation.c",
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
    ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__PlayAnimation.c"
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
