# Reconstruction context 0x00e74a20

- Status: `partial`
- Content SHA-256: `28615830ba2cf823b5aa964647125d66824efeba4961f5bc2ed6cee93251c0a1`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00e74a20",
  "phase": "reconstruction",
  "target": "0x00e74a20"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "Simulator::Cell::CreateCellObject",
  "package": null,
  "subsystem": "Simulator",
  "va": "0x00e74a20"
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
  "content_sha256": "49c32e3dea6502a97a885461bd872ac78e75762f788afde5f6b78211fabba748",
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
      "name": "QuaternionToMatrix",
      "reconstructed": false,
      "va": "0x0059c190"
    },
    {
      "name": "embedded_object_first_word_init_00743b50",
      "reconstructed": true,
      "va": "0x00743b50"
    },
    {
      "name": "Simulator::Cell::GetModelKeyForCellResource",
      "reconstructed": false,
      "va": "0x00e65640"
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e750c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e75350"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e75900"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e760f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e76360"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e76af0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e76d70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e78230"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e783d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e78570"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e786b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e78fc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e79720"
    },
    {
      "name": null,
      "reconstructed": false,
      
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
      "name": "QuaternionToMatrix",
      "reconstructed": false,
      "va": "0x0059c190"
    },
    {
      "name": "embedded_object_first_word_init_00743b50",
      "reconstructed": true,
      "va": "0x00743b50"
    },
    {
      "name": "Simulator::Cell::GetModelKeyForCellResource",
      "reconstructed": false,
      "va": "0x00e65640"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e750c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e75350"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e75900"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e760f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e76360"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e76af0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e76d70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e78230"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e783d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e78570"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e786b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e78fc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e79720"
    },
    {
      "name": null,
      
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__CreateCellObject.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__CreateCellObject.c"
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
    "original_bytes": 15343,
    "preview": "[\n  {\n    \"anchors\": [\n      \"0x011e073e\",\n      \"0x00b72190\",\n      \"0x00b72270\",\n      \"0x00b72160\",\n      \"0x00b72260\",\n      \"0x00b72190\",\n      \"0x00b72260\",\n      \"0x00b72190\",\n      \"0x00b72160\",\n      \"0x00b72270\",\n      \"0x00b72260\",\n      \"0x00b72190\",\n      \"0x00b72270\",\n      \"0x00b72160\",\n      \"0x00b72260\",\n      \"0x00e74a20\"\n    ],\n    \"conflict_id\": \"LC-002\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"RESOLVED_OBSERVED\",\n    \"resolution_status\": \"RESOLVED_OBSERVED\",\n    \"source\": \"knowledgegraph/research/conflicts/track-a-type-signature.json\",\n    \"subject\": \"0x00B72160/0x00B72190 and 0x00B72260/0x00B72270 pool entry identities\",\n    \"unresolved_reason\": \"The original private source-level method names are unknown; the disputed entry boundaries and observed acquire/release contracts are resolved.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00e74a20\",\n      \"0x00e57460\",\n      \"0x00e6d200\",\n      \"0x00e57340\",\n      \"0x00e780a0\",\n      \"0x00000108\",\n      \"0x00e74a20\",\n      \"0x00000108\"\n    ],\n    \"conflict_id\": \"TB-FL-012\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": {\n      \"merge_decision\": \"separate_entities\",\n      \"preferred_claim\": \"Use the original direct field/body evidence as the ABI anchor.\",\n      \"preserved_alternatives\": true,\n      \"scope_note\": \"The current padding is a replacement limi
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__CreateCellObject.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__CreateCellObject.c",
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
    ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__CreateCellObject.c"
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
