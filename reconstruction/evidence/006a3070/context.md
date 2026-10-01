# Reconstruction context 0x006a3070

- Status: `partial`
- Content SHA-256: `d56a900bc8777fe9176a34ca1dd13aa4e1dc47e8ca1b7e8e99380961e15bb613`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x006a3070",
  "phase": "reconstruction",
  "target": "0x006a3070"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "PropertyList",
  "name": "App::PropertyList::GetPropertyIDs",
  "package": "PKG-PROPERTY-SAFE-WAVE9",
  "subsystem": "App.Property",
  "va": "0x006a3070"
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
  "content_sha256": "9ebeaa953b0abd3b6d7ea45930fb3640621c5cae0a824c96194a8779eaca1d5f",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x006a3070 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "__thiscall",
  "hidden_this_register": "ECX",
  "ordinary_stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "destination",
      "type": "uint32_t * (word vector)",
      "width_bytes": 4
    }
  ],
  "ret_form": "RET 0x4",
  "return_register": "none",
  "return_type": "void",
  "stack_cleanup_bytes": 4
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
      "callsite": "0x006a3092",
      "direction": "out",
      "other": "0x004cd3c0",
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
    "PropertyList",
    "uint32_t * (word vector)",
    "void"
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
      "No original-process invocation or indirect-caller trace was captured.",
      "The raw signed quotient is forwarded without a negative clamp; runtime behavior for a malformed span is unverified.",
      "The resize port's real allocator, capacity policy, and zero-fill are unresolved.",
      "gate-property-list-word-vector-resize-port-behavior"
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
      "callsite": "0x006a3092",
      "direction": "out",
      "other": "0x004cd3c0",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 0,
  "fan_out": 0,
  "manifest_callees": [
    "0x004cd3c0"
  ],
  "manifest_callers": [],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0219",
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
      "shared_types:PropertyList",
      "shared_vtable:vtable:0x01408820",
      "same_calling_convention"
    ],
    "package": "PKG-PROPERTY-SAFE-WAVE9",
    "score": 28,
    "symbol": "property_list_copy_from_006a2a40",
    "va": "0x006a2a40"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "PKG-PROPERTY-SAFE-WAVE9",
    "score": 16,
    "symbol": "direct_property_list_add_properties_from_006a1600",
    "va": "0x006a1600"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "PKG-PROPERTY-SAFE-WAVE9",
    "score": 16,
    "symbol": "direct_property_list_get_property_alt_006a1e50",
    "va": "0x006a1e50"
  },
  {
    "match_basis": [
      "same_class",
      "shared_types:PropertyList",
      "shared_vtable:vtable:0x01408820"
    ],
    "package": "wave6-resources",
    "score": 12,
    "symbol": "property_list_has_property_006a2470",
    "va": "0x006a2470"
  },
  {
    "match_basis": [
      "same_class",
      "shared_types:PropertyList",
      "shared_vtable:vtable:0x01408820"
    ],
    "package": "wave6-resources",
    "score": 12,
    "symbol": "property_list_get_property_object_006a24d0",
    "va": "0x006a24d0"
  },
  {
    "match_basis": [
      "shared_types:PropertyList",
      "shared_vtable:vtable:0x01408820",
      "same_calling_convention"
    ],
    "package": "pkg-property-clear-wave13",
    "score": 9,
    "
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__GetPropertyIDs.c",
  "file": "src/reconstruction/pkg_property_safe_wave9/property_safe_wave9.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__GetPropertyIDs.c",
    "src/reconstruction/pkg_property_safe_wave9/property_safe_wave9.cpp",
    "src/reconstruction/pkg_property_safe_wave9/property_safe_wave9.hpp",
    "src/reconstruction/pkg_property_safe_wave9/property_safe_wave9_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave9-safe-core/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-property-safe-wave9/006a3070.json"
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
    "Behavior when the map span is inconsistent (negative quotient)",
    "Caller expectation for the resulting vector capacity",
    "No original-process invocation or indirect-caller trace was captured.",
    "Real resize port allocator and capacity policy",
    "The raw signed quotient is forwarded without a negative clamp; runtime behavior for a malformed span is unverified.",
    "The resize port's real allocator, capacity policy, and zero-fill are unresolved.",
    "Whether the destination vector is required to be empty on entry",
    "gate-property-list-word-vector-resize-port-behavior"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__GetPropertyIDs.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave9-safe-core/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-property-safe-wave9/006a3070.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_property_safe_wave9/property_safe_wave9.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_property_safe_wave9/property_safe_wave9.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_property_safe_wave9/property_safe_wave9_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__GetPropertyIDs.c",
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
      "ref": "reconstruction/integrated/batch-2026-09-25-wave9-safe-core/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg-property-safe-wave9/006a3070.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_property_safe_wave9/property_safe_wave9.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "
[TRUNCATED]
```
