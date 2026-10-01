# Reconstruction context 0x00e57460

- Status: `partial`
- Content SHA-256: `e0bcd103ac69ebc6eaf01b1d40e27ed538c4b1eff70af42745bb63d3acc089d5`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00e57460",
  "phase": "reconstruction",
  "target": "0x00e57460"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "Simulator::Cell::ShouldNotAttack",
  "package": null,
  "subsystem": "Simulator",
  "va": "0x00e57460"
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
  "content_sha256": "2744d459c73112c09f42fb3bbc29b3ae404f621ce05012fd78c66453e3a52a2f",
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
      "name": "Simulator::Cell::GetScaleDifferenceWithPlayer",
      "reconstructed": false,
      "va": "0x00e57340"
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e68870"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e68910"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e70b20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e71ce0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e72360"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e725c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e727e0"
    },
    {
      "name": "FUN_00e7a7c0",
      "reconstructed": true,
      "va": "0x00e7a7c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e7b470"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e7e020"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e7e7f0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00e68889",
      "direction": "in",
      "other": "0x00e68870",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e6891c",
      "direction": "in",
      "other": "0x00e68910",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e70b39"
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
      "va": "0x00e68870"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e68910"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e70b20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e71ce0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e72360"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e725c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e727e0"
    },
    {
      "name": "FUN_00e7a7c0",
      "reconstructed": true,
      "va": "0x00e7a7c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e7b470"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e7e020"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e7e7f0"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00e68889",
      "direction": "in",
      "other": "0x00e68870",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e6891c",
      "direction": "in",
      "other": "0x00e6891
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__ShouldNotAttack.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__ShouldNotAttack.c"
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
    },
    {
      "anchors": [
        "0x00d2e490",
        "0x00d2e4a0",
        "0x0169e394",
        "0x00d2e490",
        "0x00e7a4a0",
        "0x00e7a7c0",
        "0x0169e394",
        "0x00d2e490",
        "0x00d2e490",
        "0x00d2e490",
        "0x00d2e4a0",
        "0x00d2e4a0",
        "0x00d2e4a0",
        "0x00e57460",
        "0x00e57460",
        "0x00e7a7c0"
      ],
      "conflict_id": "ability_mode_calle
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__ShouldNotAttack.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__ShouldNotAttack.c",
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
    ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__ShouldNotAttack.c"
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
