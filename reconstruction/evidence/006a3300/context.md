# Reconstruction context 0x006a3300

- Status: `partial`
- Content SHA-256: `56c00d77f360cdc71297f43d2126dba0b3ab46d9166d1251ae259116bcaf37f2`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x006a3300",
  "phase": "reconstruction",
  "target": "0x006a3300"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "cPropManager",
  "name": "App::cPropManager::SetDevMode",
  "package": "PKG-PROP-RESOURCE-SAFE-WAVE9",
  "subsystem": "App.Property",
  "va": "0x006a3300"
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
  "content_sha256": "355375a89401e3ab812322e4010465e8e5e89764d93d05ed80641f5b6be9283e",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x006a3300 failed: Decompilation did not complete. Reason: ",
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
      "entry_offset": "ESP+0x04 (low byte only)",
      "name": "value",
      "type": "bool",
      "width_bytes": 1,
      "width_note": "One byte is written by the caller; the callee pops the full four-byte slot."
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
    "bool",
    "cPropManager",
    "void"
  ],
  "vtables": [
    "vtable:0x014091e8"
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
      "The consumer of the +0x15 byte is not identified statically; its runtime effect is unresolved.",
      "The imported signature declares bool; only the low byte is observable and the upper argument bytes are ignored.",
      "gate-prop-manager-dev-mode-consumer-behavior"
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
  "edges": [],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 0,
  "fan_out": 0,
  "manifest_callees": [],
  "manifest_callers": [],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0222",
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
      "same_calling_convention"
    ],
    "package": "PKG-PROP-RESOURCE-SAFE-WAVE9",
    "score": 10,
    "symbol": "record_write_flush_006c0550",
    "va": "0x006c0550"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "PKG-APP-SAFE-WAVE11",
    "score": 8,
    "symbol": "property_record_assign_pair_004279d0",
    "va": "0x004279d0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "PKG-APP-SAFE-WAVE11",
    "score": 8,
    "symbol": "property_record_assign_scalar_00428060",
    "va": "0x00428060"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "PKG-PROPERTY-SAFE-WAVE9",
    "score": 8,
    "symbol": "direct_property_list_add_properties_from_006a1600",
    "va": "0x006a1600"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "PKG-PROPERTY-SAFE-WAVE9",
    "score": 8,
    "symbol": "direct_property_list_get_property_alt_006a1e50",
    "va": "0x006a1e50"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "PKG-PROPERTY-SAFE-WAVE9",
    "score": 8,
    "symbol": "property_list_copy_from_006a2a40",
    "va": "0x006a2a40"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "PKG-PROPERTY-SAFE-WAVE9",
    "score": 8,
    "symbol": "property_list_get_property_ids_006a3070",
    "va": "0x006a30
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__cPropManager__SetDevMode.c",
  "file": "src/reconstruction/pkg_prop_resource_safe_wave9/prop_resource_safe_wave9.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__cPropManager__SetDevMode.c",
    "src/reconstruction/pkg_prop_resource_safe_wave9/prop_resource_safe_wave9.cpp",
    "src/reconstruction/pkg_prop_resource_safe_wave9/prop_resource_safe_wave9.hpp",
    "src/reconstruction/pkg_prop_resource_safe_wave9/prop_resource_safe_wave9_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave9-safe-core/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-prop-resource-safe-wave9/006a3300.json"
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
    "No original-process invocation or indirect-caller trace was captured.",
    "The consumer of the +0x15 byte is not identified statically; its runtime effect is unresolved.",
    "The imported signature declares bool; only the low byte is observable and the upper argument bytes are ignored.",
    "Whether callers pass a canonical 0/1 value",
    "Whether the byte is a tri-state rather than a boolean",
    "Which manager consumers read the +0x15 byte and what they change",
    "gate-prop-manager-dev-mode-consumer-behavior"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/App__cPropManager__SetDevMode.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave9-safe-core/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-prop-resource-safe-wave9/006a3300.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_prop_resource_safe_wave9/prop_resource_safe_wave9.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_prop_resource_safe_wave9/prop_resource_safe_wave9.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_prop_resource_safe_wave9/prop_resource_safe_wave9_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/App__cPropManager__SetDevMode.c",
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
      "ref": "reconstruction/metadata/pkg-prop-resource-safe-wave9/006a3300.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_prop_resource_safe_wave9/prop_resource_safe_wave9.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persiste
[TRUNCATED]
```
