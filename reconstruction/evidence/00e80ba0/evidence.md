# Evidence 0x00e80ba0

- Evidence state: `PERSISTED`
- Live requested: `False`
- Content SHA-256: `c949f0cc3cb4929c2abd7ec0e8c54d8921595537ba529ce5e5196a88a618a28a`

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
    "va": "0x00e81120"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e819b0"
  }
]
```

## contradictions

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "original_bytes": 12414,
  "preview": "[\n  {\n    \"anchors\": [\n      \"0x00005168\",\n      \"0x00005168\",\n      \"0x0000516b\",\n      \"0x00005168\",\n      \"0x00005168\",\n      \"0x00005169\",\n      \"0x00005168\",\n      \"0x00005169\",\n      \"0x00e80ba0\",\n      \"0x00005168\",\n      \"0x00e80ba0\",\n      \"0x00005168\",\n      \"0x0000516b\",\n      \"0x00005168\",\n      \"0x00005169\",\n      \"0x00005168\"\n    ],\n    \"conflict_id\": \"TB-FL-009\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": {\n      \"merge_decision\": \"preferred_claim_with_limit\",\n      \"preferred_claim\": \"Treat +0x5168/+0x5169 as byte flags for the observed initialization path.\",\n      \"preserved_alternatives\": true,\n      \"scope_note\": \"The imported four-byte field remains a layout alternative until all adjacent reads/writes are bounded.\",\n      \"status\": \"preferred_claim_with_limit\",\n      \"taxonomy\": \"preferred_claim_with_limit\"\n    },\n    \"resolution_status\": \"preferred_claim_with_limit\",\n    \"source\": \"knowledgegraph/research/conflicts/track-b-vtable-fields.json\",\n    \"subject\": \"cCellGame +0x5168 integer versus adjacent byte flags\",\n    \"unresolved_reason\": \"The cited static evidence leaves the competing owner, slot, layout, or lifecycle interpretation unresolved; no positive original runtime or MSVC RTTI evidence is available.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00e80ba0\",\n      \"0x00e74a20\",\n      \"0x00e5b790\",\n      \"0x00e80ba0\",\n      \"0x00e5b790\",\n      \"0x00000000\"\n    ],\n    \"conflict_id\": \"TB-INH-003\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": {\n      \"merge_decision\": \"separate_entities\",\n      \"preferred_claim\": \"Use coordination/composition, not inheritance.\",\n      \"preserved_alternatives\": true,\n      \"scope_note\": \"Current source ownership is non-equivalent and remains a comparison boundary.\",\n      \"status\": \"preserved_alternatives\",\n      \"taxonomy\": \"preserved_alternatives\"\n    },\n    \"resolution_status\": \"preserved_alternatives\",\n    \"source\": \"knowledgegraph/research/conflicts/track-b-vtable-fields.json\",\n    \"subject\": \"CellGame, CellGFX, and CellUI coordination versus inheritance\",\n    \"unresolved_reason\": \"The cited static evidence leaves the competing owner, slot, layout, or lifecycle interpretation unresolved; no positive original runtime or MSVC RTTI evidence is available.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00e80ba0\",\n      \"0x00e74a20\",\n      \"0x00e74a20\",\n      \"0x00e80ba0\",\n      \"0x00000014\"\n    ],\n    \"conflict_id\": \"TB-INH-004\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": {\n      \"merge_decision\": \"structural_only\",\n      \"preferred_claim\": \"Use an arena/ownership relation between separate structures.\",\n      \"preserved_alternatives\": true,\n      \"scope_note\": \"The original pointer-linked and current index-based representations remain distinct.\",\n      \"status\": \"preserved_alternatives\",\n      \"taxonomy\": \"preserved_alternatives\"\n    },\n    \"resolution_status\": \"preserved_alternatives\",\n    \"source\": \"knowledgegraph/research/conflicts/track-b-vtable-fields.json\",\n    \"subject\": \"cCellQueryEntry versus linked-pool data/header records\",\n    \"unresolved_reason\": \"The cited static evidence leaves the competing owner, slot, layout, or lifecycle interpretation unresolved; no positive original runtime or MSVC RTTI evidence is available.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00e4ace0\",\n      \"0x00e4cde0\",\n      \"0x00e823a0\",\n      \"0x00e80ba0\",\n      \"0x00e7fc00\",\n      \"0x00e81f30\",\n      \"0x00e4cde0\",\n      \"0x00e4cde0\",\n      \"0x00e4ace0\",\n      \"0x00e4ace0\",\n      \"0x00e80ba0\",\n      \"0x00005190\",\n      \"0x00e80ba0\",\n      \"0x00e80d45\",\n      \"0x00e80f9f\",\n      \"0x00e7fc00\"\n    ],\n    \"conflict_id\": \"TD-DATA-005\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [\n      {\n        \"path\": \"competing_hypotheses.0.claim\",\n        \"status\": \"rejected_for_recovered_record_families     \",\n        \"text\": \"Direct Cell records are generic CellSerializer name/ID envelopes containing a shared field descriptor table.\"\n      },\n      {\n        \"path\": \"competing_hypotheses.2.claim\",\n        \"status\": \"rejected_structural_pointer_is_not_wire_envelope     \",\n        \"text\": \"Because cCellResource stores a CellSerializer pointer, every direct Cell record necessarily carries a CellSerializer wire envelope.\"\n      }\n    ],\n    \"resolution\": null,\n    \"resolution_status\": null,\n    \"source\": \"knowledgegraph/research/conflicts/track-d-data-serialization.json\",\n    \"subject\": \"Direct Cell records, CellSerializer metadata, cCellDataReference, cCellGame, and cCellSerializableData\",\n    \"unresolved_reason\": [\n      \"Actual cCellSerializableData field emission order and class/object pointer remapping are not recovered.\",\n      \"No original-process save/load trace or byte-level .spo oracle is available.\"\n    ]\n  },\n  {\n    \"anchors\": [\n      \"0x00005190\",\n      \"0x00e61550\",\n      \"0x00e61630\",\n      \"0x00e80ba0\",\n      \"0x00e7fc00\",\n      \"0x00e81f30\",\n      \"0x01485598\",\n      \"0x00e61550\",\n      \"0x00e61550\",\n      \"0x00e80ba0\",\n      \"0x00005190\",\n      \"0x00e80ba0\",\n      \"0x00e80d45\",\n      \"0x00e80e17\",\n      \"0x00e81f30\",\n      \"0x00e81f30\"\n    ],\n    \"conflict_id\": \"TD-DATA-008\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [\n      {\n        \"path\": \"competing_hypotheses.0.claim\",\n        \"status\": \"rejected_by_layer_and_lifecycle_evidence     \",\n        \"text\": \"Every cCellSerializableData field and every cCellGame field is persistent save state because the seria
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
  "original_bytes": 9584,
  "preview": "{\n  \"abi\": {},\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-11-H4-HELPER-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"address_window_offset_005c65e0\",\n      \"va\": \"0x005c65e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"dispatch_key_00628450\",\n      \"va\": \"0x00628450\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"cycle_key_006286a0\",\n      \"va\": \"0x006286a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"release_child_0062c910\",\n      \"va\": \"0x0062c910\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d2a0\",\n      \"va\": \"0x00b3d2a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d300\",\n      \"va\": \"0x00b3d300\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"Simulator_GetUIMissionLogManager\",\n      \"va\": \"0x00b3d4f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-13-E4-EMPIRE-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"EmpirePoliticalColor_00c32cd0\",\n      \"va\": \"0x00c32cd0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"sim-cell\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0067dcc0\"\n      },\n      {\n        \"name\": \"embedded_object_first_word_init_00743b50\",\n        \"reconstructed\": true,\n        \"va\": \"0x00743b50\"\n      },\n      {\n        \"name\": \"FUN_00b3d400\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b3d400\"\n      },\n      {\n        \"name\": \"FUN_00e7fd00\",\n        \"reconstructed\": true,\n        \"va\": \"0x00e7fd00\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e81120\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e819b0\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00e81695\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e81120\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e81b4e\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e819b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e80fcf\",\n        \"direction\": \"out\",\n        \"other\": \"0x00597e00\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e80fe5\",\n        \"direction\": \"out\",\n        \"other\": \"0x00599440\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e80ba7\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067dcc0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e80bb5\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067dcc0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e80e22\",\n        \"direction\": \"out\",\n        \"other\": \"0x00743b50\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e810eb\",\n        \"direction\": \"out\",\n        \"other\": \"0x00810590\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e810f0\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b3d400\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e810ff\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b3d400\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e80ccb\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b72080\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e80ce3\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b72080\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e80cfb\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b72080\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e80d10\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b72080\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e80d28\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b72080\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e80d40\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b72080\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e80c55\",\n        \"direction\": \"out\",\n        \"other\": \"0x00bbbe00\",\n        \"reference_type\": \"thunk\"\n      },\n      {\n   
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__cCellGame__Initialize.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__cCellGame__Initialize.c"
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
  "original_bytes": 12414,
  "preview": "[\n  {\n    \"anchors\": [\n      \"0x00005168\",\n      \"0x00005168\",\n      \"0x0000516b\",\n      \"0x00005168\",\n      \"0x00005168\",\n      \"0x00005169\",\n      \"0x00005168\",\n      \"0x00005169\",\n      \"0x00e80ba0\",\n      \"0x00005168\",\n      \"0x00e80ba0\",\n      \"0x00005168\",\n      \"0x0000516b\",\n      \"0x00005168\",\n      \"0x00005169\",\n      \"0x00005168\"\n    ],\n    \"conflict_id\": \"TB-FL-009\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": {\n      \"merge_decision\": \"preferred_claim_with_limit\",\n      \"preferred_claim\": \"Treat +0x5168/+0x5169 as byte flags for the observed initialization path.\",\n      \"preserved_alternatives\": true,\n      \"scope_note\": \"The imported four-byte field remains a layout alternative until all adjacent reads/writes are bounded.\",\n      \"status\": \"preferred_claim_with_limit\",\n      \"taxonomy\": \"preferred_claim_with_limit\"\n    },\n    \"resolution_status\": \"preferred_claim_with_limit\",\n    \"source\": \"knowledgegraph/research/conflicts/track-b-vtable-fields.json\",\n    \"subject\": \"cCellGame +0x5168 integer versus adjacent byte flags\",\n    \"unresolved_reason\": \"The cited static evidence leaves the competing owner, slot, layout, or lifecycle interpretation unresolved; no positive original runtime or MSVC RTTI evidence is available.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00e80ba0\",\n      \"0x00e74a20\",\n      \"0x00e5b790\",\n      \"0x00e80ba0\",\n      \"0x00e5b790\",\n      \"0x00000000\"\n    ],\n    \"conflict_id\": \"TB-INH-003\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": {\n      \"merge_decision\": \"separate_entities\",\n      \"preferred_claim\": \"Use coordination/composition, not inheritance.\",\n      \"preserved_alternatives\": true,\n      \"scope_note\": \"Current source ownership is non-equivalent and remains a comparison boundary.\",\n      \"status\": \"preserved_alternatives\",\n      \"taxonomy\": \"preserved_alternatives\"\n    },\n    \"resolution_status\": \"preserved_alternatives\",\n    \"source\": \"knowledgegraph/research/conflicts/track-b-vtable-fields.json\",\n    \"subject\": \"CellGame, CellGFX, and CellUI coordination versus inheritance\",\n    \"unresolved_reason\": \"The cited static evidence leaves the competing owner, slot, layout, or lifecycle interpretation unresolved; no positive original runtime or MSVC RTTI evidence is available.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00e80ba0\",\n      \"0x00e74a20\",\n      \"0x00e74a20\",\n      \"0x00e80ba0\",\n      \"0x00000014\"\n    ],\n    \"conflict_id\": \"TB-INH-004\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": {\n      \"merge_decision\": \"structural_only\",\n      \"preferred_claim\": \"Use an arena/ownership relation between separate structures.\",\n      \"preserved_alternatives\": true,\n      \"scope_note\": \"The original pointer-linked and current index-based representations remain distinct.\",\n      \"status\": \"preserved_alternatives\",\n      \"taxonomy\": \"preserved_alternatives\"\n    },\n    \"resolution_status\": \"preserved_alternatives\",\n    \"source\": \"knowledgegraph/research/conflicts/track-b-vtable-fields.json\",\n    \"subject\": \"cCellQueryEntry versus linked-pool data/header records\",\n    \"unresolved_reason\": \"The cited static evidence leaves the competing owner, slot, layout, or lifecycle interpretation unresolved; no positive original runtime or MSVC RTTI evidence is available.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00e4ace0\",\n      \"0x00e4cde0\",\n      \"0x00e823a0\",\n      \"0x00e80ba0\",\n      \"0x00e7fc00\",\n      \"0x00e81f30\",\n      \"0x00e4cde0\",\n      \"0x00e4cde0\",\n      \"0x00e4ace0\",\n      \"0x00e4ace0\",\n      \"0x00e80ba0\",\n      \"0x00005190\",\n      \"0x00e80ba0\",\n      \"0x00e80d45\",\n      \"0x00e80f9f\",\n      \"0x00e7fc00\"\n    ],\n    \"conflict_id\": \"TD-DATA-005\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [\n      {\n        \"path\": \"competing_hypotheses.0.claim\",\n        \"status\": \"rejected_for_recovered_record_families     \",\n        \"text\": \"Direct Cell records are generic CellSerializer name/ID envelopes containing a shared field descriptor table.\"\n      },\n      {\n        \"path\": \"competing_hypotheses.2.claim\",\n        \"status\": \"rejected_structural_pointer_is_not_wire_envelope     \",\n        \"text\": \"Because cCellResource stores a CellSerializer pointer, every direct Cell record necessarily carries a CellSerializer wire envelope.\"\n      }\n    ],\n    \"resolution\": null,\n    \"resolution_status\": null,\n    \"source\": \"knowledgegraph/research/conflicts/track-d-data-serialization.json\",\n    \"subject\": \"Direct Cell records, CellSerializer metadata, cCellDataReference, cCellGame, and cCellSerializableData\",
[TRUNCATED]
```
