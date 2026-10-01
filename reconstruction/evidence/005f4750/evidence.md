# Evidence 0x005f4750

- Evidence state: `PERSISTED`
- Live requested: `False`
- Content SHA-256: `f388feca6fdacee6dce40da5ef2b613cdbdabc140eae7fc2f208ce7706eea125`

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
    "va": "0x00ecdcc0"
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
  "original_bytes": 6405,
  "preview": "{\n  \"abi\": {},\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-15-EDITOR-SUPPORT\",\n      \"score\": 6,\n      \"symbol\": \"palette_application_setup_005c53c0\",\n      \"va\": \"0x005c53c0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"pkg-dfw-005c8bc0\",\n      \"score\": 6,\n      \"symbol\": \"dfw_005c8bc0_load\",\n      \"va\": \"0x005c8bc0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-15-EDITOR-SUPPORT\",\n      \"score\": 6,\n      \"symbol\": \"palette_page_construct_005c9230\",\n      \"va\": \"0x005c9230\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-15-EDITOR-SUPPORT\",\n      \"score\": 6,\n      \"symbol\": \"palette_select_category_005cb240\",\n      \"va\": \"0x005cb240\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-15-EDITOR-SUPPORT\",\n      \"score\": 6,\n      \"symbol\": \"palette_editor_construct_loop_005cb5a0\",\n      \"va\": \"0x005cb5a0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013f9eb8,vtable:0x01489aa0\"\n      ],\n      \"package\": \"pkg-sporepedia-nop-slot\",\n      \"score\": 4,\n      \"symbol\": \"sporepedia_nop_slot_FUN_00c2e4e0\",\n      \"va\": \"0x00c2e4e0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"editor-support\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0067dcc0\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ecdcc0\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00ecdcc4\",\n        \"direction\": \"in\",\n        \"other\": \"0x00ecdcc0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005f47e4\",\n        \"direction\": \"out\",\n        \"other\": \"0x00401020\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005f4889\",\n        \"direction\": \"out\",\n        \"other\": \"0x0059f030\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005f48c6\",\n        \"direction\": \"out\",\n        \"other\": \"0x005ed320\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005f48b0\",\n        \"direction\": \"out\",\n        \"other\": \"0x005ee480\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005f48cb\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067caa0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005f4944\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067cad0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005f495f\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067cad0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005f4977\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067dcc0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005f494b\",\n        \"direction\": \"out\",\n        \"other\": \"0x0080d710\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005f4966\",\n        \"direction\": \"out\",\n        \"other\": \"0x0080d710\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005f4931\",\n        \"direction\": \"out\",\n        \"other\": \"0x008283a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005f4845\",\n        \"direction\": \"out\",\n        \"other\": \"0x00f473a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005f47eb\",\n        \"direction\": \"out\",\n        \"other\": \"0x0113ae10\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 1,\n    \"fan_out\": 1,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0137\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"CONFIRMED\",\n  \"globals\": [],\n  \"integration_status\": null,\n  \"name\": \"Palettes::AdvancedItemViewer::func40h\",\n  \"normalized_symbol\": \"Palettes::AdvancedItemViewer::func40h\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"queue_candidate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"queued\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [],\n    \"validated\": 0\n  },\n  \"runtime_gated\": false,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": null,\n  \"services\": [],\n  \"source\": {\n    \"decomp\": \".spore-analysis/ghidra-exports/decompiled_sdk/Palettes__AdvancedItemViewer__func40h.c\",\n    \"file\": null,\n    \"files\": [\n      \".spore-analysis/ghidra-exports/decompiled_sdk/Palettes__AdvancedItemViewer__func40h.c\"\n    ],\n    \"handoffs\":
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Palettes__AdvancedItemViewer__func40h.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Palettes__AdvancedItemViewer__func40h.c"
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
  "status": "queued"
}
```

## types

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x013f9eb8",
  "vtable:0x01489aa0"
]
```

## Conflicts

```json
[]
```
