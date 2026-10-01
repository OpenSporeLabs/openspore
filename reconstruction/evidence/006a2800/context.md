# Reconstruction context 0x006a2800

- Status: `partial`
- Content SHA-256: `b7bcab672e3fa83905b53b3c27a2374c5a7a5b5fb48ac12fc7c75e70ceedb639`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x006a2800",
  "phase": "reconstruction",
  "target": "0x006a2800"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "App::DirectPropertyList::GetPropertyObject",
  "package": "PKG-DIRECT-PROPERTY-WAVE6",
  "subsystem": "App.Property.Direct",
  "va": "0x006a2800"
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
  "content_sha256": "5b5b3c79c7e60689091af18188e9f606a3b11a224ceb2124ac4ef40345e150f3",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x006a2800 failed: Decompilation did not complete. Reason: ",
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
  "return_semantics": "OpaqueProperty* in EAX",
  "return_type": "OpaqueProperty*",
  "stack_cleanup_bytes": 4,
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
      "name": "property_record_assign_scalar_00428060",
      "reconstructed": true,
      "va": "0x00428060"
    },
    {
      "name": "property_list_get_property_object_006a24d0",
      "reconstructed": true,
      "va": "0x006a24d0"
    }
  ],
  "callers": [],
  "edge_rows": [
    {
      "callsite": "0x006a2851",
      "direction": "out",
      "other": "0x00422e20",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a2875",
      "direction": "out",
      "other": "0x00422eb0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a289d",
      "direction": "out",
      "other": "0x00428060",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a2827",
      "direction": "out",
      "other": "0x00542b80",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a2812",
      "direction": "out",
      "other": "0x0067de30",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a28ab",
      "direction": "out",
      "other": "0x006a24d0",
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
    "OpaqueProperty*",
    "openspore::reconstruction::pkg_direct_property_wave6::OpaqueBaseObject",
    "openspore::reconstruction::pkg_direct_property_wave6::OpaqueList",
    "openspore::reconstruction::pkg_direct_property_wave6::OpaqueMap",
    "openspore::reconstruction::pkg_direct_property_wave6::OpaqueMapEntry",
    "openspore::reconstruction::pkg_direct_property_wave6::OpaqueProperty",
    "openspore::reconstruction::pkg_direct_property_wave6::OpaquePropertyService",
    "openspore::reconstruction::pkg_direct_property_wave6::OpaqueWordVector"
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
      "property service resolver, type conversion, map lifetime, and sentinel contents remain gated",
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
      "name": "property_record_assign_scalar_00428060",
      "reconstructed": true,
      "va": "0x00428060"
    },
    {
      "name": "property_list_get_property_object_006a24d0",
      "reconstructed": true,
      "va": "0x006a24d0"
    }
  ],
  "callees_truncated": false,
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x006a2851",
      "direction": "out",
      "other": "0x00422e20",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a2875",
      "direction": "out",
      "other": "0x00422eb0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a289d",
      "direction": "out",
      "other": "0x00428060",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a2827",
      "direction": "out",
      "other": "0x00542b80",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a2812",
      "direction": "out",
      "other": "0x0067de30",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a28ab",
      "direction": "out",
      "other": "0x006a24d0",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 0,
  "fan_out": 2,
  "manifest_callees": [],
  "manifest_callers": [],
  "nearby_reconstructed": [
    "0x00428060",
    "0x006a24d0"
  ],
  "scc": {
    "id": "scc-0209",
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
    "symbol": "opaque_list_get_property_006a28c0",
    "va": "0x006a28c0"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "shared_types:openspore::reconstruction::pkg_direct_property_wave6::OpaqueBaseObject,openspore::reconstruction::pkg_direct_property_wave6::OpaqueList,openspore::reconstruction::pkg_direct_property_wave6::OpaqueMap,openspore::reconstruction::pkg_direct_property_wave6::OpaqueMapEntry",
      "shared_vtable:vtable:0x01408870",
      "same_calling_convention"
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__DirectPropertyList__GetPropertyObject.c",
  "file": "src/reconstruction/pkg_direct_property_wave6/direct_property_wave6.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__DirectPropertyList__GetPropertyObject.c",
    "src/reconstruction/pkg_direct_property_wave6/direct_property_wave6.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-direct-property-wave6/006a2800.json"
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
    "property service resolver, type conversion, map lifetime, and sentinel contents remain gated",
    "runtime validation not run"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/App__DirectPropertyList__GetPropertyObject.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-direct-property-wave6/006a2800.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_direct_property_wave6/direct_property_wave6.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/App__DirectPropertyList__GetPropertyObject.c",
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
      "ref": "reconstruction/metadata/pkg-direct-property-wave6/006a2800.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_direct_property_wave6/direct_property_wave6.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first"
[TRUNCATED]
```
