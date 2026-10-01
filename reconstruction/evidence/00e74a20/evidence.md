# Evidence 0x00e74a20

- Evidence state: `PERSISTED`
- Live requested: `False`
- Content SHA-256: `49c32e3dea6502a97a885461bd872ac78e75762f788afde5f6b78211fabba748`

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
    "va": "0x00e81120"
  }
]
```

## contradictions

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "original_bytes": 15343,
  "preview": "[\n  {\n    \"anchors\": [\n      \"0x011e073e\",\n      \"0x00b72190\",\n      \"0x00b72270\",\n      \"0x00b72160\",\n      \"0x00b72260\",\n      \"0x00b72190\",\n      \"0x00b72260\",\n      \"0x00b72190\",\n      \"0x00b72160\",\n      \"0x00b72270\",\n      \"0x00b72260\",\n      \"0x00b72190\",\n      \"0x00b72270\",\n      \"0x00b72160\",\n      \"0x00b72260\",\n      \"0x00e74a20\"\n    ],\n    \"conflict_id\": \"LC-002\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"RESOLVED_OBSERVED\",\n    \"resolution_status\": \"RESOLVED_OBSERVED\",\n    \"source\": \"knowledgegraph/research/conflicts/track-a-type-signature.json\",\n    \"subject\": \"0x00B72160/0x00B72190 and 0x00B72260/0x00B72270 pool entry identities\",\n    \"unresolved_reason\": \"The original private source-level method names are unknown; the disputed entry boundaries and observed acquire/release contracts are resolved.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00e74a20\",\n      \"0x00e57460\",\n      \"0x00e6d200\",\n      \"0x00e57340\",\n      \"0x00e780a0\",\n      \"0x00000108\",\n      \"0x00e74a20\",\n      \"0x00000108\"\n    ],\n    \"conflict_id\": \"TB-FL-012\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": {\n      \"merge_decision\": \"separate_entities\",\n      \"preferred_claim\": \"Use the original direct field/body evidence as the ABI anchor.\",\n      \"preserved_alternatives\": true,\n      \"scope_note\": \"The current padding is a replacement limitation and cannot define the original structure.\",\n      \"status\": \"preferred_claim_with_limit\",\n      \"taxonomy\": \"preferred_claim_with_limit\"\n    },\n    \"resolution_status\": \"preferred_claim_with_limit\",\n    \"source\": \"knowledgegraph/research/conflicts/track-b-vtable-fields.json\",\n    \"subject\": \"cCellObjectData original middle fields versus current opaque padding\",\n    \"unresolved_reason\": \"The cited static evidence leaves the competing owner, slot, layout, or lifecycle interpretation unresolved; no positive original runtime or MSVC RTTI evidence is available.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00e80ba0\",\n      \"0x00e74a20\",\n      \"0x00e5b790\",\n      \"0x00e80ba0\",\n      \"0x00e5b790\",\n      \"0x00000000\"\n    ],\n    \"conflict_id\": \"TB-INH-003\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": {\n      \"merge_decision\": \"separate_entities\",\n      \"preferred_claim\": \"Use coordination/composition, not inheritance.\",\n      \"preserved_alternatives\": true,\n      \"scope_note\": \"Current source ownership is non-equivalent and remains a comparison boundary.\",\n      \"status\": \"preserved_alternatives\",\n      \"taxonomy\": \"preserved_alternatives\"\n    },\n    \"resolution_status\": \"preserved_alternatives\",\n    \"source\": \"knowledgegraph/research/conflicts/track-b-vtable-fields.json\",\n    \"subject\": \"CellGame, CellGFX, and CellUI coordination versus inheritance\",\n    \"unresolved_reason\": \"The cited static evidence leaves the competing owner, slot, layout, or lifecycle interpretation unresolved; no positive original runtime or MSVC RTTI evidence is available.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00e80ba0\",\n      \"0x00e74a20\",\n      \"0x00e74a20\",\n      \"0x00e80ba0\",\n      \"0x00000014\"\n    ],\n    \"conflict_id\": \"TB-INH-004\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": {\n      \"merge_decision\": \"structural_only\",\n      \"preferred_claim\": \"Use an arena/ownership relation between separate structures.\",\n      \"preserved_alternatives\": true,\n      \"scope_note\": \"The original pointer-linked and current index-based representations remain distinct.\",\n      \"status\": \"preserved_alternatives\",\n      \"taxonomy\": \"preserved_alternatives\"\n    },\n    \"resolution_status\": \"preserved_alternatives\",\n    \"source\": \"knowledgegraph/research/conflicts/track-b-vtable-fields.json\",\n    \"subject\": \"cCellQueryEntry versus linked-pool data/header records\",\n    \"unresolved_reason\": \"The cited static evidence leaves the competing owner, slot, layout, or lifecycle interpretation unresolved; no positive original runtime or MSVC RTTI evidence is available.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00b72160\",\n      \"0x00b72260\",\n      \"0x00b72270\",\n      \"0x00e665c0\",\n      \"0x00e74a20\",\n      \"0x00e80ba0\",\n      \"0x00e80ba0\",\n      \"0x00e74a20\",\n      \"0x00b72160\",\n      \"0x00b72260\",\n      \"0x00e665c0\",\n      \"0x00e7fd00\",\n      \"0x00e74a20\",\n      \"0x00b72160\",\n      \"0x00b72260\",\n      \"0x00b72270\"\n    ],\n    \"conflict_id\": \"U-001-pool-contract\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The 4096 capacity, 920-byte Cell record, allocation/release path, and first-word free/self-index mechanics are bounded. Original sentinel, index-zero validity, and exact generic entry mapping remain unresolved.\",\n    \"resolution_status\": \"The 4096 capacity, 920-byte Cell record, allocation/release path, and first-word free/self-index mechanics are bounded. Original sentinel, index-zero validity, and exact generic entry mapping remain unresolved.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00004114\",\n      \"0x00004118\",\n      \"0x00b72160\",\n      \"0x00b72260\",\n      \"0x00e665c0\",\n      \"0x00e74a20\",\n      \"0x00e80ba0\",\n      \"0x00e80ba0\",\n      \"0x00e74a20\",\n      \"0x00b72160\",\n      \"0x00b72260\",\n      \"0x00e665c0\",\n      \"0x00004114\",\n      \"0x00004118\",\n      \"0x00bb42a0\",\n      \"0x00bb4c90\"\n  
[TRUNCATED]
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
  "original_bytes": 10607,
  "preview": "{\n  \"abi\": {},\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-11-H4-HELPER-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"address_window_offset_005c65e0\",\n      \"va\": \"0x005c65e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"dispatch_key_00628450\",\n      \"va\": \"0x00628450\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"cycle_key_006286a0\",\n      \"va\": \"0x006286a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"release_child_0062c910\",\n      \"va\": \"0x0062c910\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d2a0\",\n      \"va\": \"0x00b3d2a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d300\",\n      \"va\": \"0x00b3d300\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"Simulator_GetUIMissionLogManager\",\n      \"va\": \"0x00b3d4f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-13-E4-EMPIRE-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"EmpirePoliticalColor_00c32cd0\",\n      \"va\": \"0x00c32cd0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"sim-cell\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"QuaternionToMatrix\",\n        \"reconstructed\": false,\n        \"va\": \"0x0059c190\"\n      },\n      {\n        \"name\": \"embedded_object_first_word_init_00743b50\",\n        \"reconstructed\": true,\n        \"va\": \"0x00743b50\"\n      },\n      {\n        \"name\": \"Simulator::Cell::GetModelKeyForCellResource\",\n        \"reconstructed\": false,\n        \"va\": \"0x00e65640\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e750c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e75350\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e75900\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e760f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e76360\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e76af0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e76d70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e78230\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e783d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e78570\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e786b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e78fc0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e79720\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e81120\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00e75190\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e750c0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e75871\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e75350\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e75b3c\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e75900\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e761ee\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e760f0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e763b2\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e76360\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e76d25\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e76af0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e77077\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e76d70\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e782c9\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e78230\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e78469\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e783d0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e785f5\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e78570\",\n        \"re
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__CreateCellObject.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__CreateCellObject.c"
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
{
  "original_bytes": 15343,
  "preview": "[\n  {\n    \"anchors\": [\n      \"0x011e073e\",\n      \"0x00b72190\",\n      \"0x00b72270\",\n      \"0x00b72160\",\n      \"0x00b72260\",\n      \"0x00b72190\",\n      \"0x00b72260\",\n      \"0x00b72190\",\n      \"0x00b72160\",\n      \"0x00b72270\",\n      \"0x00b72260\",\n      \"0x00b72190\",\n      \"0x00b72270\",\n      \"0x00b72160\",\n      \"0x00b72260\",\n      \"0x00e74a20\"\n    ],\n    \"conflict_id\": \"LC-002\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"RESOLVED_OBSERVED\",\n    \"resolution_status\": \"RESOLVED_OBSERVED\",\n    \"source\": \"knowledgegraph/research/conflicts/track-a-type-signature.json\",\n    \"subject\": \"0x00B72160/0x00B72190 and 0x00B72260/0x00B72270 pool entry identities\",\n    \"unresolved_reason\": \"The original private source-level method names are unknown; the disputed entry boundaries and observed acquire/release contracts are resolved.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00e74a20\",\n      \"0x00e57460\",\n      \"0x00e6d200\",\n      \"0x00e57340\",\n      \"0x00e780a0\",\n      \"0x00000108\",\n      \"0x00e74a20\",\n      \"0x00000108\"\n    ],\n    \"conflict_id\": \"TB-FL-012\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": {\n      \"merge_decision\": \"separate_entities\",\n      \"preferred_claim\": \"Use the original direct field/body evidence as the ABI anchor.\",\n      \"preserved_alternatives\": true,\n      \"scope_note\": \"The current padding is a replacement limitation and cannot define the original structure.\",\n      \"status\": \"preferred_claim_with_limit\",\n      \"taxonomy\": \"preferred_claim_with_limit\"\n    },\n    \"resolution_status\": \"preferred_claim_with_limit\",\n    \"source\": \"knowledgegraph/research/conflicts/track-b-vtable-fields.json\",\n    \"subject\": \"cCellObjectData original middle fields versus current opaque padding\",\n    \"unresolved_reason\": \"The cited static evidence leaves the competing owner, slot, layout, or lifecycle interpretation unresolved; no positive original runtime or MSVC RTTI evidence is available.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00e80ba0\",\n      \"0x00e74a20\",\n      \"0x00e5b790\",\n      \"0x00e80ba0\",\n      \"0x00e5b790\",\n      \"0x00000000\"\n    ],\n    \"conflict_id\": \"TB-INH-003\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": {\n      \"merge_decision\": \"separate_entities\",\n      \"preferred_claim\": \"Use coordination/composition, not inheritance.\",\n      \"preserved_alternatives\": true,\n      \"scope_note\": \"Current source ownership is non-equivalent and remains a comparison boundary.\",\n      \"status\": \"preserved_alternatives\",\n      \"taxonomy\": \"preserved_alternatives\"\n    },\n    \"resolution_status\": \"preserved_alternatives\",\n    \"source\": \"knowledgegraph/research/conflicts/track-b-vtable-fields.json\",\n    \"subject\": \"CellGame, CellGFX, and CellUI coordination versus inheritance\",\n    \"unresolved_reason\": \"The cited static evidence leaves the competing owner, slot, layout, or lifecycle interpretation unresolved; no positive original runtime or MSVC RTTI evidence is available.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00e80ba0\",\n      \"0x00e74a20\",\n      \"0x00e74a20\",\n      \"0x00e80ba0\",\n      \"0x00000014\"\n    ],\n    \"conflict_id\": \"TB-INH-004\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": {\n      \"merge_decision\": \"structural_only\",\n      \"preferred_claim\": \"Use an arena/ownership relation between separate structures.\",\n      \"preserved_alternatives\": true,\n      \"scope_note\": \"The original pointer-linked and current index-based representations remain distinct.\",\n      \"status\": \"preserved_alternatives\",\n      \"taxonomy\": \"preserved_alternatives\"\n    },\n    \"resolution_status\": \"preserved_alternatives\",\n    \"source\": \"knowledgegraph/research/conflicts/track-b-vtable-fields.json\",\n    \"subject\": \"cCellQueryEntry versus linked-pool data/header records\",\n    \"unresolved_reason\": \"The cited static evidence leaves the competing owner, slot, layout, or lifecycle interpretation unresolved; no positive original runtime or MSVC RTTI evidence is available.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00b72160\",\n      \"0x00b72260\",\n      \"0x00b72270\",\n      \"0x00e665c0\",\n      \"0x00e74a20\",\n      \"0x00e80ba0\",\n      \"0x00e80ba0\",\n      \"0x00e74a20\",\n      \"0x00b72160\",\n      \"0x00b72260\",\n      \"0x00e665c0\",\n      \"0x00e7fd00\",\n      \"0x00e74a20\",\n      \"0x00b72160\",\n      \"0x00b72260\",\n      \"0x00b72270\"\n    ],\n    \"conflict_id\": \"U-001-pool-contract\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The 4096 capacity, 920-byte Cell record, allocation/release path, and first-word fre
[TRUNCATED]
```
