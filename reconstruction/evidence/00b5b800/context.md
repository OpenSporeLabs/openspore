# Reconstruction context 0x00b5b800

- Status: `partial`
- Content SHA-256: `10dd99dd8dfcd84053bae1c53c75f06410f807480ad7013d7405d92d2a7a4019`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00b5b800",
  "phase": "reconstruction",
  "target": "0x00b5b800"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00b5b800",
  "package": null,
  "subsystem": "Simulator",
  "va": "0x00b5b800"
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
  "status": "candidate"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "0ae1461f14c73fa9b348ea046737c01b057d24f5ec543cac06ad2569a2f3780f",
  "live_attempts": [],
  "live_requested": false,
  "overall": "PERSISTED"
}
```

## 05_decompilation

- State: `missing`
- Provenance: ``

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": null,
  "hidden_this_register": null,
  "hidden_this_type": null,
  "return_register": "EAX",
  "return_type": "std::uint32_t",
  "return_width_bytes": 4,
  "stack_arguments": [],
  "termination": "RET (bare)"
}
```

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
      "va": "0x00aca360"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00acc800"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00acd790"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ace5a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00acf4c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ad12a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ad20e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ad2200"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ad25e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ad7b90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae5840"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae6240"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae73e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aebe90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aee290"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b01db0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00aca38e",
      "direction": "in",
      "other": "0x00aca360",
      "reference_type": "direct-call"
    },

[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "std::uint32_t"
  ],
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
      "va": "0x00aca360"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00acc800"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00acd790"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ace5a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00acf4c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ad12a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ad20e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ad2200"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ad25e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ad7b90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae5840"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae6240"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae73e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aebe90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aee290"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b01db0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b0a6f0"
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
  "files": [],
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
        "0x00b3d300",
        "0x00b3d400",
        "0x00b3d2a0",
        "0x00b3d3a0",
        "0x00b5b800",
        "0xffffffff",
        "0x00b3d300",
        "0x00b3d2a0",
        "0x00b3d400",
        "0x00b3d3a0",
        "0x00b5b800"
      ],
      "conflict_id": "CF-002",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": null,
      "resolution_status": null,
      "source": "knowledgegraph/research/conflicts/track-f-cross-domain-impact.json",
      "subject": null,
      "unresolved_reason": {
        "missing_evidence": [
          "Direct or indirect publisher and teardown evidence for both alternate/canonical manager slot pairs.",
          "Pointer-equality checks across mode and service lifecycle boundaries.",
          "The concrete receiver class and physical storage type behind DAT_0167eaec and forwarded_object+0x20."
        ],
        "status": "blocked"
      }
    },
    {
      "anchors": [
        "0x00b3d2a0",
        "0x00b3d300",
        "0x00b5b800",
        "0x01021300",
        "0x01021300",
        "0x00ad23c0",
        "0x00adbca0",
        "0x00ae73e0",
        "0x00ae9590",
        "0x00ae9930",
        "0x00ae9c90",
        "0x00ae9f50",
        "0x00aeb3e0",
        "0x00aeb3e0",
        "0x00aebe90",
        "0x00b25fb0"
      ],
      "conflict_id": "global_root_identities",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or const
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}`

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
    "reconstruction/knowledge/index.json"
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
