# Evidence 0x00e66840

- Evidence state: `PERSISTED`
- Live requested: `False`
- Content SHA-256: `c32822e5775e5d6d6d1f5ad727323318350da9b3bdcddc5cc1daf075b085422f`

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
    "name": "dispatch_key_00628450",
    "reconstructed": true,
    "va": "0x00628450"
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
    "va": "0x00e67890"
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
    "name": "FUN_00e7a4a0",
    "reconstructed": true,
    "va": "0x00e7a4a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e7aee0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e7d880"
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
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/additional-domains.json:4",
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
      "0x00a20670",
      "0x00571f80",
      "0x00572070",
      "0x00572020",
      "0x0067dd90",
      "0x00e66280",
      "0x00e66840",
      "0x00e63560",
      "0x00c8ec00"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/additional-domains.json:5",
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
      "0x00571f80",
      "0x00571f80",
      "0x0067cae0",
      "0x00a20670",
      "0x00571f80",
      "0x00572070",
      "0x00572020",
      "0x0059ca70",
      "0x0059cac0",
      "0x0059cea0",
      "0x0059cf00",
      "0x0067dd90",
      "0x00e66280",
      "0x00e66840",
      "0x00e63560",
      "0x0059c6e0"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/additional-domains.json:9",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The cited stream or file boundary is retained, but the complete wire/transaction/round-trip contract is not reconstructed.",
    "resolution_status": "The cited stream or file boundary is retained, but the complete wire/transaction/round-trip contract is not reconstructed.",
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
  "original_bytes": 7031,
  "preview": "{\n  \"abi\": {},\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 9,\n      \"symbol\": \"dispatch_key_00628450\",\n      \"va\": \"0x00628450\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-11-H4-HELPER-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"address_window_offset_005c65e0\",\n      \"va\": \"0x005c65e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"cycle_key_006286a0\",\n      \"va\": \"0x006286a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"release_child_0062c910\",\n      \"va\": \"0x0062c910\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d2a0\",\n      \"va\": \"0x00b3d2a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d300\",\n      \"va\": \"0x00b3d300\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"Simulator_GetUIMissionLogManager\",\n      \"va\": \"0x00b3d4f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-13-E4-EMPIRE-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"EmpirePoliticalColor_00c32cd0\",\n      \"va\": \"0x00c32cd0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"sim-cell\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"dispatch_key_00628450\",\n        \"reconstructed\": true,\n        \"va\": \"0x00628450\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e67890\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e6eb60\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e6ecb0\"\n      },\n      {\n        \"name\": \"FUN_00e7a4a0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00e7a4a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e7aee0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e7d880\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00e67909\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e67890\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e6eb79\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e6eb60\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e6ecc9\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e6ecb0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7a539\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e7a4a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7a564\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e7a4a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7af28\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e7aee0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7da49\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e7d880\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e66883\",\n        \"direction\": \"out\",\n        \"other\": \"0x00537dc0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e668fd\",\n        \"direction\": \"out\",\n        \"other\": \"0x00628450\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e66929\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e61750\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e66876\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e619a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e66938\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e65200\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 6,\n    \"fan_out\": 1,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [\n      \"0x00628450\",\n      \"0x00e7a4a0\"\n    ],\n    \"scc\": {\n      \"id\": \"scc-0544\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"CONFIRMED\",\n  \"globals\": [],\n  \"integration_status\": null,\n  \"name\": \"Simulator::Cell::cCellGFX::InstanceEffectOnCell\",\n  \"normalized_symbol\": \"Simulator::Cell::cCellGFX::InstanceEffectOnCell\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"queue_candidate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__cCellGFX__InstanceEffectOnCell.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__cCellGFX__InstanceEffectOnCell.c"
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
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/additional-domains.json:4",
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
      "0x00a20670",
      "0x00571f80",
      "0x00572070",
      "0x00572020",
      "0x0067dd90",
      "0x00e66280",
      "0x00e66840",
      "0x00e63560",
      "0x00c8ec00"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/additional-domains.json:5",
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
      "0x00571f80",
      "0x00571f80",
      "0x0067cae0",
      "0x00a20670",
      "0x00571f80",
      "0x00572070",
      "0x00572020",
      "0x0059ca70",
      "0x0059cac0",
      "0x0059cea0",
      "0x0059cf00",
      "0x0067dd90",
      "0x00e66280",
      "0x00e66840",
      "0x00e63560",
      "0x0059c6e0"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/additional-domains.json:9",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The cited stream or file boundary is retained, but the complete wire/transaction/round-trip contract is not reconstructed.",
    "resolution_status": "The cited stream or file boundary is retained, but the complete wire/transaction/round-trip contract is not reconstructed.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  }
]
```
