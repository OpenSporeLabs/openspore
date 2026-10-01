# Reconstruction context 0x00c2e640

- Status: `partial`
- Content SHA-256: `cf0dc35f4aed00c326629786f8b6ab75acdfbc410bd135568d5086fdc82e7e8b`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00c2e640",
  "phase": "reconstruction",
  "target": "0x00c2e640"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueEditorCamera",
  "name": "Editors::EditorCamera::OnExit",
  "package": "PKG-CAMERA-WAVE8",
  "subsystem": "Camera",
  "va": "0x00c2e640"
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
  "content_sha256": "5a9d3c5909d51b71e429a8f28488b793de1d4423540abfefabe2ea3b967c7e69",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00c2e640 failed: Decompilation did not complete. Reason: ",
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
      "name": "type",
      "type": "uint32_t",
      "width_bytes": 4
    }
  ],
  "ret_form": "RET 4",
  "return_note": "object pointer",
  "return_register": "EAX",
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
      "callsite": "0x00c2e656",
      "direction": "out",
      "other": "0x00c44990",
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
    "OpaqueEditorCamera",
    "object pointer",
    "uint32_t"
  ],
  "vtables": [
    "vtable:0x0146b420"
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
      "No original runtime invocation or indirect caller trace was captured for this imported-name entry.",
      "No original runtime invocation or indirect caller trace was captured for this imported-name entry.; The 0x0146b420 family association is static xref evidence and requires runtime dispatch confirmation before promotion.",
      "The 0x0146b420 family association is static xref evidence and requires runtime dispatch confirmation before promotion."
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
      "callsite": "0x00c2e656",
      "direction": "out",
      "other": "0x00c44990",
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
    "id": "scc-0448",
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
      "shared_types:OpaqueEditorCamera,object pointer",
      "same_calling_convention"
    ],
    "package": "PKG-CAMERA-WAVE8",
    "score": 27,
    "symbol": "editor_camera_func24h_005a2050",
    "va": "0x005a2050"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "same_class",
      "shared_types:OpaqueEditorCamera",
      "same_calling_convention"
    ],
    "package": "PKG-CAMERA-WAVE8",
    "score": 24,
    "symbol": "editor_camera_func54h_005a2320",
    "va": "0x005a2320"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "PKG-CAMERA-WAVE7",
    "score": 8,
    "symbol": "camera_light_origin_helper_007c4900",
    "va": "0x007c4900"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "PKG-CAMERA-WAVE7",
    "score": 8,
    "symbol": "camera_manager_set_active_007c64c0",
    "va": "0x007c64c0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "PKG-CAMERA-WAVE7",
    "score": 8,
    "symbol": "camera_manager_dispose_007c6e50",
    "va": "0x007c6e50"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x0146b420",
      "same_calling_convention"
    ],
    "package": "pkg-sporepedia-nop-slot",
    "score": 6,
    "symbol": "sporepedia_nop_slot_FUN_00c2e4e0",
    "va": "0x00c2e4e0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-CAMERA-WAVE7",
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Editors__EditorCamera__OnExit.c",
  "file": "src/reconstruction/pkg_camera_wave8/camera_wave8.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Editors__EditorCamera__OnExit.c",
    "src/reconstruction/pkg_camera_wave8/camera_wave8.cpp",
    "src/reconstruction/pkg_camera_wave8/camera_wave8_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave8/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-camera-wave8/00c2e640.json"
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
    "No original runtime invocation or indirect caller trace was captured for this imported-name entry.",
    "No original runtime invocation or indirect caller trace was captured for this imported-name entry.; The 0x0146b420 family association is static xref evidence and requires runtime dispatch confirmation before promotion.",
    "The 0x0146b420 family association is static xref evidence and requires runtime dispatch confirmation before promotion.",
    "concrete runtime owners and values remain unresolved"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/Editors__EditorCamera__OnExit.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave8/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-camera-wave8/00c2e640.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_camera_wave8/camera_wave8.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_camera_wave8/camera_wave8_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/Editors__EditorCamera__OnExit.c",
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
      "ref": "reconstruction/integrated/batch-2026-09-25-wave8/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg-camera-wave8/00c2e640.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_camera_wave8/camera_wave8.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_camer
[TRUNCATED]
```
