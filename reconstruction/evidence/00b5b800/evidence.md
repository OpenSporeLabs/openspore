# Evidence 0x00b5b800

- Evidence state: `PERSISTED`
- Live requested: `False`
- Content SHA-256: `0ae1461f14c73fa9b348ea046737c01b057d24f5ec543cac06ad2569a2f3780f`

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
    "resolution": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
    "resolution_status": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
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
  "original_bytes": 13476,
  "preview": "{\n  \"abi\": {},\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-11-H4-HELPER-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"address_window_offset_005c65e0\",\n      \"va\": \"0x005c65e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"dispatch_key_00628450\",\n      \"va\": \"0x00628450\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"cycle_key_006286a0\",\n      \"va\": \"0x006286a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"release_child_0062c910\",\n      \"va\": \"0x0062c910\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d2a0\",\n      \"va\": \"0x00b3d2a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d300\",\n      \"va\": \"0x00b3d300\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"Simulator_GetUIMissionLogManager\",\n      \"va\": \"0x00b3d4f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-13-E4-EMPIRE-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"EmpirePoliticalColor_00c32cd0\",\n      \"va\": \"0x00c32cd0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"unknown-fun-mass\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00aca360\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00acc800\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00acd790\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ace5a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00acf4c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ad12a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ad20e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ad2200\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ad25e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ad7b90\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ae5840\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ae6240\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ae73e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00aebe90\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00aee290\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b01db0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b0a6f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b148c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b19290\"\n      },\n      {\n        \"name\": \"FUN_00b1f9d0\",\n        \"reconstructed\": false,\n        \"va\": \"0x00b1f9d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b23940\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b28990\"\n      },\n      {\n        \"name\": \"ProfilePersistenceBoundary_run_candidate_00b28ec0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b28ec0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b294c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b2dac0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b2f740\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b3c1a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b3ce80\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b3cec0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b3cf00\"\n      },\n      {\n        \"name\": \"FUN_00b3d2c0\",\n        \"reconstructed\": false,\n        \"va\": \"0x00b3d2c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b41ee0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b48920\"\n      },\n      {\n 
[TRUNCATED]
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
  "files": [],
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
  "status": "candidate"
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
    "resolution": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
    "resolution_status": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  }
]
```
