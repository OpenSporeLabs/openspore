# Reconstruction context 0x006a3180

- Status: `partial`
- Content SHA-256: `d89af0dfe24cbd5c79a2daf39fb7deadd55cb1addd953bcdcfd9cdee0dd08726`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x006a3180",
  "phase": "reconstruction",
  "target": "0x006a3180"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "App::DirectPropertyList::GetPropertyIDs",
  "package": "PKG-DIRECT-PROPERTY-WAVE6",
  "subsystem": "App.Property.Direct",
  "va": "0x006a3180"
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
  "content_sha256": "537b615e936c5d4851871ffb6bc25c4d86411513912a5c41af7413f49e547dd7",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x006a3180 failed: Decompilation did not complete. Reason: ",
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
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "caller"
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [],
  "callers": [],
  "edge_rows": [
    {
      "callsite": "0x006a31f0",
      "direction": "out",
      "other": "0x004558a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a323f",
      "direction": "out",
      "other": "0x004cea40",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a31ac",
      "direction": "out",
      "other": "0x0067de30",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a3196",
      "direction": "out",
      "other": "0x011e0744",
      "reference_type": "thunk"
    },
    {
      "callsite": "0x006a3254",
      "direction": "out",
      "other": "0x011e0744",
      "reference_type": "thunk"
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
      "runtime validation not run",
      "vector allocation, service metadata, map lifetime, and destination ownership remain gated"
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
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x006a31f0",
      "direction": "out",
      "other": "0x004558a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a323f",
      "direction": "out",
      "other": "0x004cea40",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a31ac",
      "direction": "out",
      "other": "0x0067de30",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a3196",
      "direction": "out",
      "other": "0x011e0744",
      "reference_type": "thunk"
    },
    {
      "callsite": "0x006a3254",
      "direction": "out",
      "other": "0x011e0744",
      "reference_type": "thunk"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 0,
  "fan_out": 0,
  "manifest_callees": [],
  "manifest_callers": [],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0221",
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__DirectPropertyList__GetPropertyIDs.c",
  "file": "src/reconstruction/pkg_direct_property_wave6/direct_property_wave6.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__DirectPropertyList__GetPropertyIDs.c",
    "src/reconstruction/pkg_direct_property_wave6/direct_property_wave6.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-direct-property-wave6/006a3180.json"
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
    "runtime validation not run",
    "vector allocation, service metadata, map lifetime, and destination ownership remain gated"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/App__DirectPropertyList__GetPropertyIDs.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-direct-property-wave6/006a3180.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_direct_property_wave6/direct_property_wave6.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/App__DirectPropertyList__GetPropertyIDs.c",
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
      "ref": "reconstruction/metadata/pkg-direct-property-wave6/006a3180.json",
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
