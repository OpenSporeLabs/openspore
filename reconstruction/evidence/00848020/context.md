# Reconstruction context 0x00848020

- Status: `partial`
- Content SHA-256: `5b1d053619cfe1df782050c1594686ad96ea96cbf0033349dd2cd283dd1136cc`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00848020",
  "phase": "reconstruction",
  "target": "0x00848020"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "App::Canvas::func80h",
  "package": "PKG-APP-CANVAS-WAVE6",
  "subsystem": "App.Canvas",
  "va": "0x00848020"
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
  "content_sha256": "1f437f003f5d77997de52764091e0112f1be70397e53d297fe62fc2581f1369f",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00848020 failed: Decompilation did not complete. Reason: ",
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
  "return_semantics": "bool in AL; true on reviewed cleanup paths",
  "return_type": "bool",
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller"
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
      "name": null,
      "reconstructed": false,
      "va": "0x00849da0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00849da9",
      "direction": "in",
      "other": "0x00849da0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00848047",
      "direction": "out",
      "other": "0x00847e70",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0084809b",
      "direction": "out",
      "other": "EXT:GDI32.DLL::DeleteObject",
      "reference_type": "external"
    },
    {
      "callsite": "0x00848078",
      "direction": "out",
      "other": "EXT:KERNEL32.DLL::GetModuleHandleA",
      "reference_type": "external"
    },
    {
      "callsite": "0x00848068",
      "direction": "out",
      "other": "EXT:USER32.DLL::DestroyWindow",
      "reference_type": "external"
    },
    {
      "callsite": "0x00848055",
      "direction": "out",
      "other": "EXT:USER32.DLL::KillTimer",
      "reference_type": "external"
    },
    {
      "callsite": "0x008480c1",
      "direction": "out",
      "other": "EXT:USER32.DLL::SystemParametersInfoA",
      "reference_type": "external"
    },
    {
      "callsite": "0x008480d3",
      "direction": "out",
      "other": "EXT:USER32.DLL::SystemParametersInfoA",
      "reference_type": "external"
    },
    {
      "callsite": "0x008480e8",
      "direction": "out",
      "other": "EXT:USER32.DLL::SystemParametersInfoA",
      "reference_type": "external"
    },
    {
      "callsite": "0x00848084",
      "direction": "out",
      "other": "E
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "bool",
    "openspore::reconstruction::pkg_app_canvas_wave6::OpaqueCanvas",
    "openspore::reconstruction::pkg_app_canvas_wave6::OpaqueCanvasSystems",
    "openspore::reconstruction::pkg_app_canvas_wave6::OpaqueDispatchRecord",
    "openspore::reconstruction::pkg_app_canvas_wave6::OpaqueMessageManager",
    "openspore::reconstruction::pkg_app_canvas_wave6::OpaqueOwnerManager"
  ],
  "vtables": [
    "vtable:0x0141ca70"
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
      "platform handles, dispatch records, global state, and teardown ownership remain gated",
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
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00849da0"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00849da9",
      "direction": "in",
      "other": "0x00849da0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00848047",
      "direction": "out",
      "other": "0x00847e70",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0084809b",
      "direction": "out",
      "other": "EXT:GDI32.DLL::DeleteObject",
      "reference_type": "external"
    },
    {
      "callsite": "0x00848078",
      "direction": "out",
      "other": "EXT:KERNEL32.DLL::GetModuleHandleA",
      "reference_type": "external"
    },
    {
      "callsite": "0x00848068",
      "direction": "out",
      "other": "EXT:USER32.DLL::DestroyWindow",
      "reference_type": "external"
    },
    {
      "callsite": "0x00848055",
      "direction": "out",
      "other": "EXT:USER32.DLL::KillTimer",
      "reference_type": "external"
    },
    {
      "callsite": "0x008480c1",
      "direction": "out",
      "other": "EXT:USER32.DLL::SystemParametersInfoA",
      "reference_type": "external"
    },
    {
      "callsite": "0x008480d3",
      "direction": "out",
      "other": "EXT:USER32.DLL::SystemParametersInfoA",
      "reference_type": "external"
    },
    {
      "callsite": "0x008480e8",
      "direction": "out",
      "other": "EXT:USER32.DLL::SystemParametersInfoA",
      "reference_type": "external"
   
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
      "shared_vtable:vtable:0x0141ca70",
      "same_calling_convention"
    ],
    "package": "PKG-APP-CANVAS-WAVE6",
    "score": 29,
    "symbol": "app_canvas_00847a90",
    "va": "0x00847a90"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "shared_types:openspore::reconstruction::pkg_app_canvas_wave6::OpaqueCanvas,openspore::reconstruction::pkg_app_canvas_wave6::OpaqueCanvasSystems,openspore::reconstruction::pkg_app_canvas_wave6::OpaqueDispatchRecord,openspore::reconstruction::pkg_app_canvas_wave6::OpaqueMessageManager",
      "shared_vtable:vtable:0x0141ca70",
      "same_calling_convention"
    ],
    "package": "PKG-APP-
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__Canvas__func80h.c",
  "file": "src/reconstruction/pkg_app_canvas_wave6/app_canvas_wave6.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__Canvas__func80h.c",
    "src/reconstruction/pkg_app_canvas_wave6/app_canvas_wave6.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-app-canvas-wave6/00848020.json"
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
    "platform handles, dispatch records, global state, and teardown ownership remain gated",
    "runtime validation not run"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/App__Canvas__func80h.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-app-canvas-wave6/00848020.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_app_canvas_wave6/app_canvas_wave6.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/App__Canvas__func80h.c",
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
      "ref": "reconstruction/metadata/pkg-app-canvas-wave6/00848020.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_app_canvas_wave6/app_canvas_wave6.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/ind
[TRUNCATED]
```
