# Reconstruction context 0x00847a90

- Status: `partial`
- Content SHA-256: `ec6f0f8299d851c182d51c53ae21f499f48f17e0daa06556a5ce91c5017c8af2`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00847a90",
  "phase": "reconstruction",
  "target": "0x00847a90"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "App::Canvas::Update",
  "package": "PKG-APP-CANVAS-WAVE6",
  "subsystem": "App.Canvas",
  "va": "0x00847a90"
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
  "content_sha256": "de9ce066e7e6d9374c175aaf985fb8022d60c1514a720f3e9621a0496c0c1f2b",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00847a90 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "x86-32 thiscall with first explicit canvas receiver in ECX and caller cleanup",
  "return_semantics": "active-handle port result in EAX",
  "return_type": "OpaqueHandle",
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
    "OpaqueHandle",
    "openspore::reconstruction::pkg_app_canvas_wave6::OpaqueCanvas",
    "openspore::reconstruction::pkg_app_canvas_wave6::OpaqueCanvasSystems",
    "openspore::reconstruction::pkg_app_canvas_wave6::OpaqueDispatchRecord",
    "openspore::reconstruction::pkg_app_canvas_wave6::OpaqueMessageManager",
    "openspore::reconstruction::pkg_app_canvas_wave6::OpaqueOwnerManager"
  ],
  "vtables": [
    "vtable:0x0141ca70",
    "vtable:0x0141cab8"
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
      "platform active-handle and window lifetime remain gated",
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
    "id": "scc-0265",
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
      "shared_types:openspore::reconstruction::pkg_app_canvas_wave6::OpaqueCanvas,openspore::reconstruction::pkg_app_canvas_wave6::OpaqueCanvasSystems,openspore::reconstruction::pkg_app_canvas_wave6::OpaqueDispatchRecord,openspore::reconstruction::pkg_app_canvas_wave6::OpaqueMessageManager",
      "shared_vtable:vtable:0x0141ca70",
      "same_calling_convention"
    ],
    "package": "PKG-APP-CANVAS-WAVE6",
    "score": 29,
    "symbol": "app_canvas_00847a40",
    "va": "0x00847a40"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "shared_types:openspore::reconstruction::pkg_app_canvas_wave6::OpaqueCanvas,openspore::reconstruction::pkg_app_canvas_wave6::OpaqueCanvasSystems,openspore::reconstruction::pkg_app_canvas_wave6::OpaqueDispatchRecord,openspore::reconstruction::pkg_app_canvas_wave6::OpaqueMessageManager",
      "shared_vtable:vtable:0x0141ca70,vtable:0x0141cab8",
      "same_calling_convention"
    ],
    "package": "PKG-APP-CANVAS-WAVE6",
    "score": 29,
    "symbol": "app_canvas_00847b10",
    "va": "0x00847b10"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "shared_types:openspore::reconstruction::pkg_app_canvas_wave6::OpaqueCanvas,openspore::reconstruction::pkg_app_canvas_wave6::OpaqueCanvasSystems,openspore::reconstruction::pkg_app_canvas_wave6::OpaqueDispatchRecord,openspore::reconstruction::pkg_app_canvas_wave6::OpaqueMessageManager",
      "shared_vtable:vtable:0x0141ca70,vtable:0x0141cab8",
      "same_calling_convent
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__Canvas__Update.c",
  "file": "src/reconstruction/pkg_app_canvas_wave6/app_canvas_wave6.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__Canvas__Update.c",
    "src/reconstruction/pkg_app_canvas_wave6/app_canvas_wave6.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-app-canvas-wave6/00847a90.json"
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
    "platform active-handle and window lifetime remain gated",
    "runtime validation not run"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/App__Canvas__Update.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-app-canvas-wave6/00847a90.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_app_canvas_wave6/app_canvas_wave6.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/App__Canvas__Update.c",
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
      "ref": "reconstruction/metadata/pkg-app-canvas-wave6/00847a90.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_app_canvas_wave6/app_canvas_wave6.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/inde
[TRUNCATED]
```
