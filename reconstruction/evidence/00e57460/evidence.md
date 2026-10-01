# Evidence 0x00e57460

- Evidence state: `PERSISTED`
- Live requested: `False`
- Content SHA-256: `2744d459c73112c09f42fb3bbc29b3ae404f621ce05012fd78c66453e3a52a2f`

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
  },
  {
    "name": "Simulator::Cell::GetScaleDifferenceWithPlayer",
    "reconstructed": false,
    "va": "0x00e57340"
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
    "conflict_id": "ability_mode_callers_and_domain",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
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
  "original_bytes": 9176,
  "preview": "{\n  \"abi\": {},\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-11-H4-HELPER-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"address_window_offset_005c65e0\",\n      \"va\": \"0x005c65e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"dispatch_key_00628450\",\n      \"va\": \"0x00628450\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"cycle_key_006286a0\",\n      \"va\": \"0x006286a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"release_child_0062c910\",\n      \"va\": \"0x0062c910\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d2a0\",\n      \"va\": \"0x00b3d2a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d300\",\n      \"va\": \"0x00b3d300\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"Simulator_GetUIMissionLogManager\",\n      \"va\": \"0x00b3d4f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-13-E4-EMPIRE-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"EmpirePoliticalColor_00c32cd0\",\n      \"va\": \"0x00c32cd0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"sim-cell\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"embedded_object_first_word_init_00743b50\",\n        \"reconstructed\": true,\n        \"va\": \"0x00743b50\"\n      },\n      {\n        \"name\": \"Simulator::Cell::GetScaleDifferenceWithPlayer\",\n        \"reconstructed\": false,\n        \"va\": \"0x00e57340\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e68870\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e68910\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e70b20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e71ce0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e72360\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e725c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e727e0\"\n      },\n      {\n        \"name\": \"FUN_00e7a7c0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00e7a7c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e7b470\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e7e020\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e7e7f0\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00e68889\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e68870\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e6891c\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e68910\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e70b39\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e70b20\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e71e17\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e71ce0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e72379\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e72360\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e725eb\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e725c0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e72829\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e727e0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7a7e1\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e7a7c0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7b4b3\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e7b470\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7e05b\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e7e020\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7eab0\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e7e7f0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7eb66\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e7e7f0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7ec03\",\n        \"directi
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__ShouldNotAttack.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__ShouldNotAttack.c"
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
    "conflict_id": "ability_mode_callers_and_domain",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  }
]
```
