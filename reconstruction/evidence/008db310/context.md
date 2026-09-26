# Reconstruction context 0x008db310

- Status: `partial`
- Content SHA-256: `c395f44308dca99a46c4db06a1e687ce9a8d6a9775c6881e2b62b47cb976a8aa`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x008db310",
  "phase": "reconstruction",
  "target": "0x008db310"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "Resource::PFIndexModifiable::Write",
  "package": null,
  "subsystem": "Resource",
  "va": "0x008db310"
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
  "content_sha256": "ad44d0300541c6af575c53c7dbcb775f72d89f458543d8f7c1d40851f3c55fb4",
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
  "calling_convention": "__thiscall observed",
  "hidden_this_register": "ECX",
  "hidden_this_type": "PFIndexModifiableWriteCarrier*",
  "return_register": "AL",
  "return_type": "bool",
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "destination",
      "position": 1,
      "type": "void*",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x08",
      "name": "destination_size",
      "position": 2,
      "type": "uint32_t",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 8,
  "termination": "RET 0x8 at 0x008db384 and 0x008db38d"
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [],
  "callers": [],
  "edge_rows": [],
  "external_callees": []
}
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "DATA",
    "ItemsMap",
    "PFIndexModifiableWriteCarrier*",
    "bool",
    "uint32_t",
    "void*"
  ],
  "vtables": [
    "vtable:0x01436878"
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
  "callees": [],
  "callees_truncated": false,
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 0,
  "fan_out": 0,
  "manifest_callees": [],
  "manifest_callers": [],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0197",
    "size": 1
  },
  "vtable_reference_count": 0
}
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "shared_types:DATA",
      "same_calling_convention"
    ],
    "package": "wave6-resources",
    "score": 5,
    "symbol": "property_list_has_property_006a2470",
    "va": "0x006a2470"
  },
  {
    "match_basis": [
      "shared_types:DATA",
      "same_calling_convention"
    ],
    "package": "wave6-resources",
    "score": 5,
    "symbol": "property_list_get_property_object_006a24d0",
    "va": "0x006a24d0"
  },
  {
    "match_basis": [
      "shared_types:DATA"
    ],
    "package": "PKG-18-UI-SCRIPTING",
    "score": 3,
    "symbol": "FUN_005bf9d0",
    "va": "0x005bf9d0"
  },
  {
    "match_basis": [
      "shared_types:DATA"
    ],
    "package": "PKG-18-UI-SCRIPTING",
    "score": 3,
    "symbol": "FUN_005c0100",
    "va": "0x005c0100"
  },
  {
    "match_basis": [
      "shared_types:DATA"
    ],
    "package": "PKG-18-UI-SCRIPTING",
    "score": 3,
    "symbol": "FUN_005c0380",
    "va": "0x005c0380"
  },
  {
    "match_basis": [
      "shared_types:DATA"
    ],
    "package": "WAVE6-ENGINE-RUNTIME",
    "score": 3,
    "symbol": "app_system_service_gate_dispatch_007e5f30",
    "va": "0x007e5f30"
  },
  {
    "match_basis": [
      "shared_types:DATA"
    ],
    "package": "PKG-APP-LIFECYCLE-WAVE7",
    "score": 3,
    "symbol": "app_capp_system_hook_windows_007e6080",
    "va": "0x007e6080"
  },
  {
    "match_basis": [
      "shared_types:DATA"
    ],
    "package": "PKG-APP-LIFECYCLE-WAVE7",
    "score": 3,
    "symbol": "app_capp_system_set_effect_collection_ids_007e6100",
    "va": "0x007e6100"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Resource__PFIndexModifiable__Write.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Resource__PFIndexModifiable__Write.c",
    "reconstruction/staging/wave6-resources/pf_index_write.cpp",
    "reconstruction/staging/wave6-resources/pf_index_write.hpp",
    "reconstruction/staging/wave6-resources/property_list_variants_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave6-resources/008db310.json"
  ]
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
  "unresolved_questions": [
    "Concrete ItemsMap node and bucket ownership semantics",
    "The vtable/data-table owner that reaches this otherwise uncalled function",
    "Whether destination_size is a byte count or a target index extent in all callers"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'ref': 'ephemeral reconstruction_knowledge.build_index', 'mode': 'derived', 'source_class': 'generated_index'}, {'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/Resource__PFIndexModifiable__Write.c', 'mode': 'persisted', 'source_class': 'committed_artifact'}, {'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'mode': 'persisted', 'source_class': 'committed_artifact'}, {'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'mode': 'persisted', 'source_class': 'committed_artifact'}, {'ref': 'reconstruction/metadata/wave6-resources/008db310.json', 'mode': 'persisted', 'source_class': 'committed_artifact'}, {'ref': 'reconstruction/staging/wave6-resources/pf_index_write.cpp', 'mode': 'persisted', 'source_class': 'committed_artifact'}, {'ref': 'reconstruction/staging/wave6-resources/pf_index_write.hpp', 'mode': 'persisted', 'source_class': 'committed_artifact'}, {'ref': 'reconstruction/staging/wave6-resources/property_list_variants_model_test.cpp', 'mode': 'persisted', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/Resource__PFIndexModifiable__Write.c",
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
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/wave6-resources/008db310.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave6-resources/pf_index_write.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave6-resources/pf_index_write.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave6-resources/property_list_variants_model_test.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.json",
    ".spore-analysis/ghidra-exports/decompiled_sdk/Resource__PFIndexModifiable__Write.c"
  ],
  "required_categories": [
    "ABI",
    "CALLS",
    "GLOBALS",
    "FIELDS/OFFSETS",
    "CONSTANTS",
    "CONTROL FLOW",
    "VIRTUAL DISPATCH",
   
[TRUNCATED]
```
