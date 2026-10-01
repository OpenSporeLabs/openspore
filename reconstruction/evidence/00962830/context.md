# Reconstruction context 0x00962830

- Status: `partial`
- Content SHA-256: `7c785f02ea6954520a13ca490b0ce76d66dc4fa784100100be24be137fafc89a`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00962830",
  "phase": "reconstruction",
  "target": "0x00962830"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "UTFWin::Window::RemoveWindow",
  "package": "PKG-UTFWIN-LAYOUT-WAVE6",
  "subsystem": "UTFWin.Layout",
  "va": "0x00962830"
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
  "content_sha256": "86d2ec512fd9a5f60862f79abb15d895f8d50adc479bf11edb1e3f0442481c78",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00962830 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "x86-32 thiscall with first explicit object pointer in ECX and caller cleanup",
  "return_semantics": "delegated pointer in EAX",
  "return_type": "Opaque*",
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
      "callsite": "0x00962833",
      "direction": "out",
      "other": "0x00962bc0",
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
    "Opaque*",
    "openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutManager",
    "openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutWindow",
    "openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueCastObject",
    "openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueImageCarrier",
    "openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueIndexCarrier"
  ],
  "vtables": [
    "vtable:0x014431f8"
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
      "adjusted object layout and delegated return ownership remain gated",
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
  "edges": [
    {
      "callsite": "0x00962833",
      "direction": "out",
      "other": "0x00962bc0",
      "reference_type": "direct-call"
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
    "id": "scc-0303",
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
      "shared_types:openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutManager,openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutWindow,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueCastObject,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueImageCarrier",
      "same_calling_convention"
    ],
    "package": "PKG-UTFWIN-LAYOUT-WAVE6",
    "score": 25,
    "symbol": "pkg_utfwin_layout_wave6_00967e80",
    "va": "0x00967e80"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "shared_types:Opaque*,openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutManager,openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutWindow,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueCastObject",
      "same_calling_convention"
    ],
    "package": "PKG-UTFWIN-LAYOUT-WAVE6",
    "score": 25,
    "symbol": "pkg_utfwin_layout_wave6_0096feb0",
    "va": "0x0096feb0"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "shared_types:openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutManager,openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutWindow,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueCastObject,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueImageCarrier"
    ],
    "package": "PKG-UTFWIN-LAYOUT-WAVE6",
    "score": 23,
    "symbol": "pkg_utfwin_layout_wave6_009601e0",
    "va": "0x009601e0"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
   
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__Window__RemoveWindow.c",
  "file": "src/reconstruction/pkg_utfwin_layout_wave6/utfwin_layout_wave6.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__Window__RemoveWindow.c",
    "src/reconstruction/pkg_utfwin_layout_wave6/utfwin_layout_wave6.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-utfwin-layout-wave6/00962830.json"
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
    "adjusted object layout and delegated return ownership remain gated",
    "runtime validation not run"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__Window__RemoveWindow.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-utfwin-layout-wave6/00962830.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_utfwin_layout_wave6/utfwin_layout_wave6.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__Window__RemoveWindow.c",
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
      "ref": "reconstruction/metadata/pkg-utfwin-layout-wave6/00962830.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_utfwin_layout_wave6/utfwin_layout_wave6.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruct
[TRUNCATED]
```
