# Reconstruction context 0x00e80ba0

- Status: `partial`
- Content SHA-256: `fdcf516c30b12fb07842d44471a92e9897acd5cf96b01bebe9a8601a94aef0a7`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00e80ba0",
  "phase": "reconstruction",
  "target": "0x00e80ba0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "Simulator::Cell::cCellGame::Initialize",
  "package": null,
  "subsystem": "Simulator",
  "va": "0x00e80ba0"
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
  "content_sha256": "c949f0cc3cb4929c2abd7ec0e8c54d8921595537ba529ce5e5196a88a618a28a",
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
      "name": null,
      "reconstructed": false,
      "va": "0x0067dcc0"
    },
    {
      "name": "embedded_object_first_word_init_00743b50",
      "reconstructed": true,
      "va": "0x00743b50"
    },
    {
      "name": "FUN_00b3d400",
      "reconstructed": true,
      "va": "0x00b3d400"
    },
    {
      "name": "FUN_00e7fd00",
      "reconstructed": true,
      "va": "0x00e7fd00"
    }
  ],
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
      "callsite": "0x00e81695",
      "direction": "in",
      "other": "0x00e81120",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e81b4e",
      "direction": "in",
      "other": "0x00e819b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e80fcf",
      "direction": "out",
      "other": "0x00597e00",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e80fe5",
      "direction": "out",
      "other": "0x00599440",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e80ba7",
      "direction": "out",
      "other": "0x0067dcc0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e80bb5",
      "direction": "out",
      "other": "0x0067dcc0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e80e22",
      "direction": "out",
      "other": "0x00743b50",
      "reference_type": "direct-call"
   
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
      "name": null,
      "reconstructed": false,
      "va": "0x0067dcc0"
    },
    {
      "name": "embedded_object_first_word_init_00743b50",
      "reconstructed": true,
      "va": "0x00743b50"
    },
    {
      "name": "FUN_00b3d400",
      "reconstructed": true,
      "va": "0x00b3d400"
    },
    {
      "name": "FUN_00e7fd00",
      "reconstructed": true,
      "va": "0x00e7fd00"
    }
  ],
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
      "callsite": "0x00e81695",
      "direction": "in",
      "other": "0x00e81120",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e81b4e",
      "direction": "in",
      "other": "0x00e819b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e80fcf",
      "direction": "out",
      "other": "0x00597e00",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e80fe5",
      "direction": "out",
      "other": "0x00599440",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e80ba7",
      "direction": "out",
      "other": "0x0067dcc0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e80bb5",
      "direction": "out",
      "other": "0x0067dcc0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e80e22",
      "dire
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__cCellGame__Initialize.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__cCellGame__Initialize.c"
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
  "conflicts": {
    "original_bytes": 12414,
    "preview": "[\n  {\n    \"anchors\": [\n      \"0x00005168\",\n      \"0x00005168\",\n      \"0x0000516b\",\n      \"0x00005168\",\n      \"0x00005168\",\n      \"0x00005169\",\n      \"0x00005168\",\n      \"0x00005169\",\n      \"0x00e80ba0\",\n      \"0x00005168\",\n      \"0x00e80ba0\",\n      \"0x00005168\",\n      \"0x0000516b\",\n      \"0x00005168\",\n      \"0x00005169\",\n      \"0x00005168\"\n    ],\n    \"conflict_id\": \"TB-FL-009\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": {\n      \"merge_decision\": \"preferred_claim_with_limit\",\n      \"preferred_claim\": \"Treat +0x5168/+0x5169 as byte flags for the observed initialization path.\",\n      \"preserved_alternatives\": true,\n      \"scope_note\": \"The imported four-byte field remains a layout alternative until all adjacent reads/writes are bounded.\",\n      \"status\": \"preferred_claim_with_limit\",\n      \"taxonomy\": \"preferred_claim_with_limit\"\n    },\n    \"resolution_status\": \"preferred_claim_with_limit\",\n    \"source\": \"knowledgegraph/research/conflicts/track-b-vtable-fields.json\",\n    \"subject\": \"cCellGame +0x5168 integer versus adjacent byte flags\",\n    \"unresolved_reason\": \"The cited static evidence leaves the competing owner, slot, layout, or lifecycle interpretation unresolved; no positive original runtime or MSVC RTTI evidence is available.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00e80ba0\",\n      \"0x00e74a20\",\n      \"0x00e5b790\",\n      \"0x00e80ba0\",\n      \"0x00e5b790
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__cCellGame__Initialize.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__cCellGame__Initialize.c",
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
    ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__cCellGame__Initialize.c"
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
