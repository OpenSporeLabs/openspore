# Reconstruction context 0x00e66280

- Status: `partial`
- Content SHA-256: `736ed9b09cb3dd3c26973038374654adb00abcd8187b161d0e2df8a3187d1c02`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00e66280",
  "phase": "reconstruction",
  "target": "0x00e66280"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "Simulator::Cell::cCellGFX::AddPreloadedEffect",
  "package": null,
  "subsystem": "Simulator",
  "va": "0x00e66280"
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
  "content_sha256": "b9b34538b566df3e6feccf03864a7c69ae839b6502d5343e700f76f3029992d0",
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
      "name": "Simulator::Cell::cCellGFX::AddPreloadedModel2",
      "reconstructed": false,
      "va": "0x00e653a0"
    },
    {
      "name": "Simulator::Cell::cCellGFX::AddPreloadedModel",
      "reconstructed": false,
      "va": "0x00e65410"
    },
    {
      "name": "Simulator::Cell::cCellGFX::AddPreloadedTexture",
      "reconstructed": false,
      "va": "0x00e65970"
    },
    {
      "name": "Simulator::Cell::cCellGFX::AddPreloadedEffect",
      "reconstructed": false,
      "va": "0x00e66280"
    }
  ],
  "callers": [
    {
      "name": "Simulator::Cell::cCellGFX::AddPreloadedEffect",
      "reconstructed": false,
      "va": "0x00e66280"
    },
    {
      "name": "Simulator::Cell::cCellGFX::PreloadCellResource",
      "reconstructed": false,
      "va": "0x00e663b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e67610"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e67670"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00e66326",
      "direction": "in",
      "other": "0x00e66280",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e6646d",
      "direction": "in",
      "other": "0x00e663b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e664e6",
      "direction": "in",
      "other": "0x00e663b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e67649",
      "direction": "in",
      "other": "0x00e67610",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e67
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
      "name": "Simulator::Cell::cCellGFX::AddPreloadedModel2",
      "reconstructed": false,
      "va": "0x00e653a0"
    },
    {
      "name": "Simulator::Cell::cCellGFX::AddPreloadedModel",
      "reconstructed": false,
      "va": "0x00e65410"
    },
    {
      "name": "Simulator::Cell::cCellGFX::AddPreloadedTexture",
      "reconstructed": false,
      "va": "0x00e65970"
    },
    {
      "name": "Simulator::Cell::cCellGFX::AddPreloadedEffect",
      "reconstructed": false,
      "va": "0x00e66280"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": "Simulator::Cell::cCellGFX::AddPreloadedEffect",
      "reconstructed": false,
      "va": "0x00e66280"
    },
    {
      "name": "Simulator::Cell::cCellGFX::PreloadCellResource",
      "reconstructed": false,
      "va": "0x00e663b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e67610"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e67670"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00e66326",
      "direction": "in",
      "other": "0x00e66280",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e6646d",
      "direction": "in",
      "other": "0x00e663b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e664e6",
      "direction": "in",
      "other": "0x00e663b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e67649",
      "direction": "in",
      "other": "0x00e
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__cCellGFX__AddPreloadedEffect.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__cCellGFX__AddPreloadedEffect.c"
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
        "0x00845310",
        "0x00b1fdb0",
        "0x00845310",
        "0x00b1fdb0",
        "0x00844f70",
        "0x00841440",
        "0x00846e60",
        "0x00841d40",
        "0x00845790",
        "0x00842d10",
        "0x00844180",
        "0x00843000",
        "0x00845310",
        "0x0067dd90",
        "0x00e66280",
        "0x00e66840"
      ],
      "conflict_id": "unresolved:knowledgegraph/research/state-machines/additional-domains.json:1",
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
        "0x00e63560",
        "0x00e63560",
        "0x00acd9a0",
        "0x00ace2c0",
        "0x00b25f40",
        "0x00ba0080",
        "0x00bf9820",
        "0x00e5c780",
        "0x00551240",
        "0x0067dd90",
        "0x00e66280",
        "0x00e66840",
        "0x00e63560",
        "0x00e5c780",
        "0x00e63560",
        "0x00571f80"
      ],
      "conflict_id": "unresolved:knowledgegraph/research/state-machines/additional-domains.j
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__cCellGFX__AddPreloadedEffect.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__cCellGFX__AddPreloadedEffect.c",
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
    ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__cCellGFX__AddPreloadedEffect.c"
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
