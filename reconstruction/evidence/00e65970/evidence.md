# Evidence 0x00e65970

- Evidence state: `PERSISTED`
- Live requested: `False`
- Content SHA-256: `12c8e990341a29eb44452271d10e9f8bc269b8132611435acf60dc038309ad40`

## abi

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## abi_derived

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: ``

## callees_dependencies

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## callers_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "Simulator::Cell::cCellGFX::AddPreloadedEffect",
    "reconstructed": false,
    "va": "0x00e66280"
  }
]
```

## contradictions

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## decompilation

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: ``

## disassembly

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: ``

## external_callees

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## function_identity

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "abi": {},
  "analogues": [
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
  ],
  "audit_evidence_boundary": null,
  "audit_findings": [],
  "audit_status": null,
  "blocked": false,
  "blockers": [],
  "body_status": null,
  "class_type": null,
  "cluster": "sim-cell",
  "confidence": null,
  "dependencies": {
    "callees": [],
    "callees_truncated": false,
    "callers": [
      {
        "name": "Simulator::Cell::cCellGFX::AddPreloadedEffect",
        "reconstructed": false,
        "va": "0x00e66280"
      }
    ],
    "callers_truncated": false,
    "data_reference_count": 0,
    "edges": [
      {
        "callsite": "0x00e66318",
        "direction": "in",
        "other": "0x00e66280",
        "reference_type": "direct-call"
      },
      {
        "callsite": "0x00e659b8",
        "direction": "out",
        "other": "0x00425a80",
        "reference_type": "direct-call"
      }
    ],
    "edges_truncated": false,
    "external_callees": [],
    "fan_in": 1,
    "fan_out": 0,
    "manifest_callees": [],
    "manifest_callers": [],
    "nearby_reconstructed": [],
    "scc": {
      "id": "scc-0539",
      "size": 1
    },
    "vtable_reference_count": 0
  },
  "evidence_level": "CONFIRMED",
  "globals": [],
  "integration_status": null,
  "name": "Simulator::Cell::cCellGFX::AddPreloadedTexture",
  "normalized_symbol": "Simulator::Cell::cCellGFX::AddPreloadedTexture",
  "observed_mechanics": [],
  "ownership": {
    "claimability": "queue_candidate",
    "handoff_packages": [],
    "manifest": {
      "record": null,
      "worker_ownership": null
    },
    "package": null,
    "queue_state": "implemented"
  },
  "package": null,
  "reconstructed": false,
  "review_status": null,
  "runtime": {
    "blocking_reason": null,
    "gates": [],
    "validated": 0
  },
  "runtime_gated": false,
  "runtime_validated": 0,
  "semantic": null,
  "semantic_status": null,
  "services": [],
  "source": {
    "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__cCellGFX__AddPreloadedTexture.c",
    "file": null,
    "files": [
      ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__cCellGFX__AddPreloadedTexture.c"
    ],
    "handoffs": [],
    "metadata": [],
    "provenance": []
  },
  "status": "implemented",
  "subsystem": "Simulator",
  "triage": {
    "category": "GAMEPLAY_LOGIC",
    "cluster": "sim-cell",
    "db_triage_status": "DONE",
    "decomp_path": ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__cCellGFX__AddPreloadedTexture.c",
    "dependencies": [
      "resource-io",
      "app-lifecycle",
      "utfwin-framework",
      "graphics-render"
    ],
    "evidence": "CONFIRMED",
    "kg_node_id": "fun:00e65970",
    "name": "Simulator::Cell::cCellGFX::AddPreloadedTexture",
    "priority": "P3",
    "provenance": {
      "classifier": "triage-v4",
      "generated_at": "2026-09-23T10:12:09Z",
      "generator": "subagent-7-sequential-triage",
      "sdk_name": "Simulator::Cell::cCellGFX::AddPreloadedTexture",
      "snapshot": "2540f2ca",
      "snapshot_sha256": "2540f2ca7cd361a72b559448fa5cf247eff3cee20d375b14ed0dd256c45229c8",
      "vtable_addrs": []
    },
    "queue_state": "implemented",
    "rank": 192
  },
  "types": [],
  "unresolved_questions": [],
  "va": "0x00e65970",
  "vtables": []
}
```

## ghidra_function

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: ``

## globals

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__cCellGFX__AddPreloadedTexture.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__cCellGFX__AddPreloadedTexture.c"
  ],
  "handoffs": [],
  "metadata": []
}
```

## runtime

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## runtime_metadata

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "blocking_reason": null,
  "gates": [],
  "validated": 0
}
```

## semantic_hypotheses

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

## status

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "runtime_gated": false,
  "runtime_validated": 0,
  "status": "implemented"
}
```

## types

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## vtables

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## Conflicts

```json
[]
```
