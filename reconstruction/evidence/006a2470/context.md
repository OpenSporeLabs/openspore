# Reconstruction context 0x006a2470

- Status: `partial`
- Content SHA-256: `e75ffe2f705512891e76c125f95f788e58d2decc1a83337c0b0462ba566222eb`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x006a2470",
  "phase": "reconstruction",
  "target": "0x006a2470"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "PropertyList",
  "name": "App::PropertyList::HasProperty",
  "package": "wave6-resources",
  "subsystem": "App.PropertyList",
  "va": "0x006a2470"
}
```

## 03_current_status

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "blocked": false,
  "reconstructed": true,
  "runtime_gated": true,
  "runtime_validated": 0,
  "status": "reconstructed"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "d926789302550dead793f2186b55ebb893c84468513d6a9a2b2340c640667b68",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x006a2470 failed: Decompilation did not complete. Reason: ",
      "mode": "LIVE",
      "status": "unavailable"
    }
  ],
  "live_requested": true,
  "overall": "LIVE"
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
  "hidden_this_type": "PropertyList*",
  "return_register": "AL",
  "return_type": "bool",
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "property_id",
      "position": 1,
      "type": "uint32_t",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 4,
  "termination": "RET 0x4 at 0x006a24ab and 0x006a24c6"
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [],
  "callers": [
    {
      "name": "opaque_list_has_property_006a27d0",
      "reconstructed": true,
      "va": "0x006a27d0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x006a27de",
      "direction": "in",
      "other": "0x006a27d0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a2486",
      "direction": "out",
      "other": "0x00612db0",
      "reference_type": "direct-call"
    }
  ],
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
    "HasParentVtable",
    "PropertyList",
    "PropertyList*",
    "PropertyMap",
    "PropertyMapEntry",
    "UNCONDITIONAL_CALL",
    "bool",
    "uint32_t"
  ],
  "vtables": [
    "vtable:0x01408820"
  ]
}
```

## 09_state_event_relationships

- State: `present`
- Provenance: `knowledgegraph/research/semantic-decomp.json, reconstruction/knowledge/index.json`

```json
{
  "runtime": {
    "blocking_reason": null,
    "gates": [
      "gate-property-list-parent-dispatch-and-inherited-property-runtime"
    ],
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
  "callers": [
    {
      "name": "opaque_list_has_property_006a27d0",
      "reconstructed": true,
      "va": "0x006a27d0"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x006a27de",
      "direction": "in",
      "other": "0x006a27d0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a2486",
      "direction": "out",
      "other": "0x00612db0",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 1,
  "fan_out": 0,
  "manifest_callees": [
    "0x00612db0",
    "parent vtable +0x1c"
  ],
  "manifest_callers": [
    "0x006a27d0"
  ],
  "nearby_reconstructed": [
    "0x006a27d0"
  ],
  "scc": {
    "id": "scc-0204",
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
      "same_package",
      "same_subsystem",
      "same_class",
      "shared_types:DATA,PropertyList,PropertyList*,PropertyMap",
      "shared_vtable:vtable:0x01408820",
      "same_calling_convention"
    ],
    "package": "wave6-resources",
    "score": 34,
    "symbol": "property_list_get_property_object_006a24d0",
    "va": "0x006a24d0"
  },
  {
    "match_basis": [
      "same_class",
      "shared_types:PropertyList",
      "shared_vtable:vtable:0x01408820"
    ],
    "package": "PKG-PROPERTY-SAFE-WAVE9",
    "score": 12,
    "symbol": "property_list_copy_from_006a2a40",
    "va": "0x006a2a40"
  },
  {
    "match_basis": [
      "same_class",
      "shared_types:PropertyList",
      "shared_vtable:vtable:0x01408820"
    ],
    "package": "PKG-PROPERTY-SAFE-WAVE9",
    "score": 12,
    "symbol": "property_list_get_property_ids_006a3070",
    "va": "0x006a3070"
  },
  {
    "match_basis": [
      "shared_types:PropertyList",
      "shared_vtable:vtable:0x01408820"
    ],
    "package": "pkg-property-clear-wave13",
    "score": 7,
    "symbol": "property_list_clear_006a2a80",
    "va": "0x006a2a80"
  },
  {
    "match_basis": [
      "shared_types:DATA,UNCONDITIONAL_CALL"
    ],
    "package": "PKG-18-UI-SCRIPTING",
    "score": 6,
    "symbol": "FUN_005bf9d0",
    "va": "0x005bf9d0"
  },
  {
    "match_basis": [
      "shared_types:DATA,UNCONDITIONAL_CALL"
    ],
    "package": "PKG-18-UI-SCRIPTING",
    "score": 6,
    "symbol": "FUN_005c0100",
    "va": "0x005c0100"
  },
  {
    "match_basis": [
      "shared_types:DATA,UNCONDITIONAL_CALL
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__HasProperty.c",
  "file": "src/reconstruction/wave6_resources/property_list_variants.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__HasProperty.c",
    "reconstruction/staging/wave6-resources/property_list_variants.cpp",
    "reconstruction/staging/wave6-resources/property_list_variants.hpp",
    "reconstruction/staging/wave6-resources/property_list_variants_model_test.cpp",
    "src/reconstruction/wave6_resources/property_list_variants.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/wave6-resources/006a2470.json"
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
    "Concrete parent PropertyList subtype and vtable +0x1c implementation",
    "Whether any callers depend on property map lookup_mode values not visible in the binary search helper",
    "gate-property-list-parent-dispatch-and-inherited-property-runtime",
    "lookup-mode policy",
    "parent subtype and slot +0x1c implementation",
    "runtime property records"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__HasProperty.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave6/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave6-resources/006a2470.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave6-resources/property_list_variants.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave6-resources/property_list_variants.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave6-resources/property_list_variants_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/wave6_resources/property_list_variants.cpp', 'source_class': 'committed_artifact'}`

```json
{
  "provenance": [
    {
      "mode": "derived",
      "ref": "ephemeral reconstruction_knowledge.build_index",
      "source_class": "generated_index"
    },
    {
      "mode": "derived",
      "ref": "tools/reconstruction_tooling/abi_infer.py",
      "source_class": "derived"
    },
    {
      "mode": "live",
      "ref": "GhidraMCP /disassemble_function",
      "source_class": "ghidra"
    },
    {
      "mode": "live",
      "ref": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
      "source_class": "ghidra"
    },
    {
      "mode": "persisted",
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__HasProperty.c",
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
      "ref": "reconstruction/integrated/batch-2026-09-25-wave6/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/wave6-resources/006a2470.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave6-resources/property_list_variants.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/
[TRUNCATED]
```
