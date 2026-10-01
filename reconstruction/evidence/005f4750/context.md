# Reconstruction context 0x005f4750

- Status: `partial`
- Content SHA-256: `9ce45e4f815b975e5bd70ed537938a2680a6265a858ae4600da5472630010176`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x005f4750",
  "phase": "reconstruction",
  "target": "0x005f4750"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "Palettes::AdvancedItemViewer::func40h",
  "package": null,
  "subsystem": "Palettes",
  "va": "0x005f4750"
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
  "status": "queued"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "f388feca6fdacee6dce40da5ef2b613cdbdabc140eae7fc2f208ce7706eea125",
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
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ecdcc0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00ecdcc4",
      "direction": "in",
      "other": "0x00ecdcc0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005f47e4",
      "direction": "out",
      "other": "0x00401020",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005f4889",
      "direction": "out",
      "other": "0x0059f030",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005f48c6",
      "direction": "out",
      "other": "0x005ed320",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005f48b0",
      "direction": "out",
      "other": "0x005ee480",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005f48cb",
      "direction": "out",
      "other": "0x0067caa0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005f4944",
      "direction": "out",
      "other": "0x0067cad0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005f495f",
      "direction": "out",
      "other": "0x0067cad0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005f4977",
      "direction": "out",
      "other": "0x0067dcc0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005f494b",
      "direction": "out",
      "other": "0x0080d710",
      "reference_type": "direct-c
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [],
  "vtables": [
    "vtable:0x013f9eb8",
    "vtable:0x01489aa0"
  ]
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
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ecdcc0"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00ecdcc4",
      "direction": "in",
      "other": "0x00ecdcc0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005f47e4",
      "direction": "out",
      "other": "0x00401020",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005f4889",
      "direction": "out",
      "other": "0x0059f030",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005f48c6",
      "direction": "out",
      "other": "0x005ed320",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005f48b0",
      "direction": "out",
      "other": "0x005ee480",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005f48cb",
      "direction": "out",
      "other": "0x0067caa0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005f4944",
      "direction": "out",
      "other": "0x0067cad0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005f495f",
      "direction": "out",
      "other": "0x0067cad0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005f4977",
      "direction": "out",
      "other": "0x0067dcc0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005f494b",
   
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
    "package": "PKG-15-EDITOR-SUPPORT",
    "score": 6,
    "symbol": "palette_application_setup_005c53c0",
    "va": "0x005c53c0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "pkg-dfw-005c8bc0",
    "score": 6,
    "symbol": "dfw_005c8bc0_load",
    "va": "0x005c8bc0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-15-EDITOR-SUPPORT",
    "score": 6,
    "symbol": "palette_page_construct_005c9230",
    "va": "0x005c9230"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-15-EDITOR-SUPPORT",
    "score": 6,
    "symbol": "palette_select_category_005cb240",
    "va": "0x005cb240"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-15-EDITOR-SUPPORT",
    "score": 6,
    "symbol": "palette_editor_construct_loop_005cb5a0",
    "va": "0x005cb5a0"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x013f9eb8,vtable:0x01489aa0"
    ],
    "package": "pkg-sporepedia-nop-slot",
    "score": 4,
    "symbol": "sporepedia_nop_slot_FUN_00c2e4e0",
    "va": "0x00c2e4e0"
  }
]
```

## 12_existing_reconstruction

- State: `present`
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

## 13_semantic_hypotheses

- State: `missing`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

## 14_conflicts_questions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json, knowledgegraph/research/semantic-decomp.json`

```json
{
  "conflicts": [],
  "unresolved_questions": []
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/Palettes__AdvancedItemViewer__func40h.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/Palettes__AdvancedItemViewer__func40h.c",
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
    ".spore-analysis/ghidra-exports/decompiled_sdk/Palettes__AdvancedItemViewer__func40h.c"
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
