# Reconstruction context 0x006a30c0

- Status: `partial`
- Content SHA-256: `3510a722d3296d85c18a77a25a0545ecc97e05db77bea835a630a5dec451ab04`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x006a30c0",
  "phase": "reconstruction",
  "target": "0x006a30c0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "App::DirectPropertyList::SetProperty",
  "package": "PKG-DIRECT-PROPERTY-WAVE6",
  "subsystem": "App.Property.Direct",
  "va": "0x006a30c0"
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
  "content_sha256": "5cddd069bb3c575ea72ab7a343190aa0f7adca391f70f6509f2a5701462e6dae",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x006a30c0 failed: Decompilation did not complete. Reason: ",
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
  "architecture": "x86-32",
  "calling_convention": "x86-32 thiscall with first explicit list receiver in ECX and caller cleanup",
  "return_semantics": "void",
  "return_type": "void",
  "stack_cleanup_bytes": 8,
  "stack_cleanup_owner": "caller"
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "property_value_resolve_0041e920",
      "reconstructed": true,
      "va": "0x0041e920"
    },
    {
      "name": "dfw_property_set_006a2e20",
      "reconstructed": true,
      "va": "0x006a2e20"
    }
  ],
  "callers": [],
  "edge_rows": [
    {
      "callsite": "0x006a30f2",
      "direction": "out",
      "other": "0x0041e920",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a311a",
      "direction": "out",
      "other": "0x0041e990",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a3141",
      "direction": "out",
      "other": "0x0041ea70",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a30ce",
      "direction": "out",
      "other": "0x0067de30",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a3102",
      "direction": "out",
      "other": "0x006a17e0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a3129",
      "direction": "out",
      "other": "0x006a1880",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a3153",
      "direction": "out",
      "other": "0x006a1910",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a3162",
      "direction": "out",
      "other": "0x006a2e20",
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
    "openspore::reconstruction::pkg_direct_property_wave6::OpaqueBaseObject",
    "openspore::reconstruction::pkg_direct_property_wave6::OpaqueList",
    "openspore::reconstruction::pkg_direct_property_wave6::OpaqueMap",
    "openspore::reconstruction::pkg_direct_property_wave6::OpaqueMapEntry",
    "openspore::reconstruction::pkg_direct_property_wave6::OpaqueProperty",
    "openspore::reconstruction::pkg_direct_property_wave6::OpaquePropertyService",
    "openspore::reconstruction::pkg_direct_property_wave6::OpaqueWordVector",
    "void"
  ],
  "vtables": [
    "vtable:0x01408870"
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
      "property service, type conversion, base insertion, and fast-list runtime ownership remain gated",
      "runtime validation not run"
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
  "callees": [
    {
      "name": "property_value_resolve_0041e920",
      "reconstructed": true,
      "va": "0x0041e920"
    },
    {
      "name": "dfw_property_set_006a2e20",
      "reconstructed": true,
      "va": "0x006a2e20"
    }
  ],
  "callees_truncated": false,
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x006a30f2",
      "direction": "out",
      "other": "0x0041e920",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a311a",
      "direction": "out",
      "other": "0x0041e990",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a3141",
      "direction": "out",
      "other": "0x0041ea70",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a30ce",
      "direction": "out",
      "other": "0x0067de30",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a3102",
      "direction": "out",
      "other": "0x006a17e0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a3129",
      "direction": "out",
      "other": "0x006a1880",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a3153",
      "direction": "out",
      "other": "0x006a1910",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a3162",
      "direction": "out",
      "other": "0x006a2e20",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 0,
  "fan_out": 2,
  "manifest_callees": [],
  "manifest_cal
[TRUNCATED]
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
      "shared_types:openspore::reconstruction::pkg_direct_property_wave6::OpaqueBaseObject,openspore::reconstruction::pkg_direct_property_wave6::OpaqueList,openspore::reconstruction::pkg_direct_property_wave6::OpaqueMap,openspore::reconstruction::pkg_direct_property_wave6::OpaqueMapEntry",
      "shared_vtable:vtable:0x01408870",
      "same_calling_convention"
    ],
    "package": "PKG-DIRECT-PROPERTY-WAVE6",
    "score": 29,
    "symbol": "opaque_list_has_property_006a27d0",
    "va": "0x006a27d0"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "shared_types:openspore::reconstruction::pkg_direct_property_wave6::OpaqueBaseObject,openspore::reconstruction::pkg_direct_property_wave6::OpaqueList,openspore::reconstruction::pkg_direct_property_wave6::OpaqueMap,openspore::reconstruction::pkg_direct_property_wave6::OpaqueMapEntry",
      "shared_vtable:vtable:0x01408870",
      "same_calling_convention"
    ],
    "package": "PKG-DIRECT-PROPERTY-WAVE6",
    "score": 29,
    "symbol": "opaque_list_get_property_object_006a2800",
    "va": "0x006a2800"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "shared_types:openspore::reconstruction::pkg_direct_property_wave6::OpaqueBaseObject,openspore::reconstruction::pkg_direct_property_wave6::OpaqueList,openspore::reconstruction::pkg_direct_property_wave6::OpaqueMap,openspore::reconstruction::pkg_direct_property_wave6::OpaqueMapEntry",
      "shared_vtable:vtable:0x01408870",
      "same_calling_conv
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__DirectPropertyList__SetProperty.c",
  "file": "src/reconstruction/pkg_direct_property_wave6/direct_property_wave6.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__DirectPropertyList__SetProperty.c",
    "src/reconstruction/pkg_direct_property_wave6/direct_property_wave6.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-direct-property-wave6/006a30c0.json"
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
    "property service, type conversion, base insertion, and fast-list runtime ownership remain gated",
    "runtime validation not run"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/App__DirectPropertyList__SetProperty.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-direct-property-wave6/006a30c0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_direct_property_wave6/direct_property_wave6.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/App__DirectPropertyList__SetProperty.c",
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
      "ref": "reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg-direct-property-wave6/006a30c0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_direct_property_wave6/direct_property_wave6.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
  
[TRUNCATED]
```
