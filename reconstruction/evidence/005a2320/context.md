# Reconstruction context 0x005a2320

- Status: `partial`
- Content SHA-256: `5fd2d67c30f187c2e265084e8f4a3e78e4f10438f68fb5e9b21b0e5b6717c6d3`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x005a2320",
  "phase": "reconstruction",
  "target": "0x005a2320"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueEditorCamera",
  "name": "Editors::EditorCamera::func54h",
  "package": "PKG-CAMERA-WAVE8",
  "subsystem": "Camera",
  "va": "0x005a2320"
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
  "content_sha256": "f046c26f7cc694261b9e92b0fd006fbaf077e7ad262c4feec2a577364f479f71",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x005a2320 failed: Decompilation did not complete. Reason: ",
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
      "name": "deleting_destructor_flag",
      "type": "uint32_t",
      "width_bytes": 4
    }
  ],
  "ret_form": "JMP to 0x005a2ed0, which ends in RET 4",
  "return_note": "primary EditorCamera pointer",
  "return_register": "EAX",
  "stack_cleanup_bytes": 4
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "FUN_005a2ed0",
      "reconstructed": false,
      "va": "0x005a2ed0"
    }
  ],
  "callers": [],
  "edge_rows": [
    {
      "callsite": "0x005a2323",
      "direction": "out",
      "other": "0x005a2ed0",
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
    "primary EditorCamera pointer",
    "uint32_t"
  ],
  "vtables": [
    "vtable:0x013f69b4",
    "vtable:0x013f69b8"
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
      "No original Wine deletion trace was captured for this object, property list or virtual destructor callback.",
      "No original Wine deletion trace was captured for this object, property list or virtual destructor callback.; The exact runtime owner of the 0x013f69b8 secondary vtable requires indirect-dispatch confirmation before promotion.; The imported func54h semantic name remains unresolved because the exact entry is a deleting-destructor thunk.",
      "The exact runtime owner of the 0x013f69b8 secondary vtable requires indirect-dispatch confirmation before promotion.",
      "The imported func54h semantic name remains unresolved because the exact entry is a deleting-destructor thunk."
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
      "name": "FUN_005a2ed0",
      "reconstructed": false,
      "va": "0x005a2ed0"
    }
  ],
  "callees_truncated": false,
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x005a2323",
      "direction": "out",
      "other": "0x005a2ed0",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 0,
  "fan_out": 1,
  "manifest_callees": [],
  "manifest_callers": [],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0101",
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
      "shared_types:OpaqueEditorCamera",
      "shared_vtable:vtable:0x013f69b4",
      "same_calling_convention"
    ],
    "package": "PKG-CAMERA-WAVE8",
    "score": 28,
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
    "symbol": "editor_camera_on_exit_00c2e640",
    "va": "0x00c2e640"
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
      "shared_vtable:vtable:0x013f69b4",
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
    "pac
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Editors__EditorCamera__func54h.c",
  "file": "src/reconstruction/pkg_camera_wave8/camera_wave8.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Editors__EditorCamera__func54h.c",
    "src/reconstruction/pkg_camera_wave8/camera_wave8.cpp",
    "src/reconstruction/pkg_camera_wave8/camera_wave8_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave8/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-camera-wave8/005a2320.json"
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
    "No original Wine deletion trace was captured for this object, property list or virtual destructor callback.",
    "No original Wine deletion trace was captured for this object, property list or virtual destructor callback.; The exact runtime owner of the 0x013f69b8 secondary vtable requires indirect-dispatch confirmation before promotion.; The imported func54h semantic name remains unresolved because the exact entry is a deleting-destructor thunk.",
    "The exact runtime owner of the 0x013f69b8 secondary vtable requires indirect-dispatch confirmation before promotion.",
    "The imported func54h semantic name remains unresolved because the exact entry is a deleting-destructor thunk.",
    "concrete runtime owners and values remain unresolved"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/Editors__EditorCamera__func54h.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave8/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-camera-wave8/005a2320.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_camera_wave8/camera_wave8.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_camera_wave8/camera_wave8_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/Editors__EditorCamera__func54h.c",
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
      "ref": "reconstruction/metadata/pkg-camera-wave8/005a2320.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_camera_wave8/camera_wave8.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_came
[TRUNCATED]
```
