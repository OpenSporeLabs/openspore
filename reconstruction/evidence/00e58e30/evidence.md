# Evidence 0x00e58e30

- Evidence state: `PERSISTED`
- Live requested: `False`
- Content SHA-256: `55ef0da1d14f8556e8f7dfa824202e7d53d7ae16d26a1cbdc5a9973f3b9b6027`

## abi

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## abi_derived

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: ``

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "embedded_object_first_word_init_00743b50",
    "reconstructed": true,
    "va": "0x00743b50"
  }
]
```

## callers_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e5f360"
  }
]
```

## contradictions

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
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
      "scope_note": "The preferred claim concerns observed mechanics, not the persistence field contract or value-range proof.",
      "status": "preferred_claim_with_limit",
      "taxonomy": "preferred_claim_with_limit"
    },
    "resolution_status": "preferred_claim_with_limit",
    "source": "knowledgegraph/research/conflicts/track-b-vtable-fields.json",
    "subject": "cAdvectEntry strength, variance, and period integer versus float32 fields",
    "unresolved_reason": "The cited static evidence leaves the competing owner, slot, layout, or lifecycle interpretation unresolved; no positive original runtime or MSVC RTTI evidence is available."
  }
]
```

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
        "callsite": "0x00e5f383",
        "direction": "in",
        "other": "0x00e5f360",
        "reference_type": "direct-call"
      },
      {
        "callsite": "0x00e58e3a",
        "direction": "out",
        "other": "0x00743b50",
        "reference_type": "direct-call"
      },
      {
        "callsite": "0x00e58e51",
        "direction": "out",
        "other": "0x00e4cc40",
        "reference_type": "thunk"
      },
      {
        "callsite": "0x00e58ecb",
        "direction": "out",
        "other": "0x00e82130",
        "reference_type": "direct-call"
      },
      {
        "callsite": "0x00e58ede",
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
      "id": "scc-0525",
      "size": 1
    },
    "vtable_reference_count": 0
  },
  "evidence_level": "CONFIRMED",
  "globals": [],
  "integration_status": null,
  "name": "Simulator::Cell::GetNextAdvectID",
  "normalized_symbol": "Simulator::Cell::GetNextAdvectID",
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
    "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__GetNextAdvectID.c",
    "file": null,
    "files": [
      ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__GetNextAdvectID.c"
    ],
    "handoffs": [],
    "metadata": [],
    "provenance": []
  },
  "status": "implemented",
  "subsystem": "Simulator",
  "triage": {
    "category": "GAMEPLAY_SUPPORT",
    "cluster": "sim-cell",
    "db_triage_status": "DONE",
    "decomp_path": ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__GetNextAdvectID.c",
    "dependencies": [
      "resource-io",
      "app-lifecycle",
      "utfwin-framework",
      "graphics-render"
    ],
    "evidence": "CONFIRMED",
    "kg_node_id": "fun:00e58e30",
    "name": "Simulator::Cell::GetNextAdvectID",
    "priority": "P3",
    "provenance": {
      "classifier": "triage-v4",
      "generated_at": "2026-09-23T10:12:09Z",
      "generator": "subagent-7-sequential-triage",
      "sdk_name": "Simulator::Cell::GetNextAdvectID",
      "snapshot": "2540f2ca",
      "snapshot_sha256": "2540f2ca7cd361a72b559448fa5cf247eff3cee20d375b14ed0dd256c45229c8",
      "vtable_addrs": []
    },
    "queue_state": "implemented",
    "rank": 181
  },
  "types": [],
  "unresolved_questions": [],
  "va": "0x00e58e30",
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__GetNextAdvectID.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__GetNextAdvectID.c"
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
[
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
      "scope_note": "The preferred claim concerns observed mechanics, not the persistence field contract or value-range proof.",
      "status": "preferred_claim_with_limit",
      "taxonomy": "preferred_claim_with_limit"
    },
    "resolution_status": "preferred_claim_with_limit",
    "source": "knowledgegraph/research/conflicts/track-b-vtable-fields.json",
    "subject": "cAdvectEntry strength, variance, and period integer versus float32 fields",
    "unresolved_reason": "The cited static evidence leaves the competing owner, slot, layout, or lifecycle interpretation unresolved; no positive original runtime or MSVC RTTI evidence is available."
  }
]
```
