# Reconstruction context 0x00e310c0

- Status: `partial`
- Content SHA-256: `5451c52394b2e27c010c36ed0e7afdb4a9b9a56e218d11436e37b2898b447bbb`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00e310c0",
  "phase": "reconstruction",
  "target": "0x00e310c0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "Resource::PFRecordWrite",
  "name": "Resource::PFRecordWrite::GetState",
  "package": "PKG-RESOURCE-STATE-SAFE-WAVE10",
  "subsystem": "Resource.PFRecordWrite",
  "va": "0x00e310c0"
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
  "content_sha256": "ad8f38df76f02321f542b432365608071bf88bbaa6048ac403f245a618fe5f32",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00e310c0 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "thiscall with callee stack cleanup",
  "receiver_register": "ECX",
  "ret_form": "RET 0x4",
  "return_register": "EAX",
  "return_width_bytes": 4,
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "machine_type": "unsigned char",
      "native_test": "TEST byte ptr [ESP + 0x8],0x1",
      "normalized_name": "state_release_flag",
      "note": "the stack slot is one word wide but only its low byte is read; after PUSH ESI the slot is observed at ESP+0x8",
      "position": 1,
      "width_bytes": 4,
      "width_read_bytes": 1
    }
  ],
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
      "callsite": "0x00e310c3",
      "direction": "out",
      "other": "0x00e30f90",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e310d0",
      "direction": "out",
      "other": "0x00f47380",
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
    "OpaqueRecordWrite",
    "OpaqueRecordWrite*",
    "Resource::PFRecordWrite",
    "ResourceStateSafePorts",
    "unsigned char"
  ],
  "vtables": [
    "vtable:0x01481940"
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
      "0x00e30f90 and 0x00f47380 remain dependency-only, so the release and untrack effects are unverified in this package.",
      "No original-process invocation was captured.",
      "The published entry is reached only through the 0x01481948 vtable slot and the 0x00e31020 thunk that rebases ECX by -0x8.",
      "The receiver class identity is unresolved; the target never dereferences the receiver so no field evidence exists.",
      "gate-record-write-get-state-runtime-receiver-identity"
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
      "callsite": "0x00e310c3",
      "direction": "out",
      "other": "0x00e30f90",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e310d0",
      "direction": "out",
      "other": "0x00f47380",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 0,
  "fan_out": 0,
  "manifest_callees": [
    "0x00e30f90",
    "0x00f47380"
  ],
  "manifest_callers": [],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0512",
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
      "shared_types:unsigned char"
    ],
    "package": "PKG-EDITOR-SAFE-WAVE11",
    "score": 3,
    "symbol": "editor_paint_commit_0043ac40",
    "va": "0x0043ac40"
  },
  {
    "match_basis": [
      "shared_types:unsigned char"
    ],
    "package": "PKG-APP-SAFE-WAVE11",
    "score": 3,
    "symbol": "stream_probe_dispatch_004bc540",
    "va": "0x004bc540"
  },
  {
    "match_basis": [
      "shared_types:unsigned char"
    ],
    "package": "PKG-EDITOR-SAFE-WAVE11",
    "score": 3,
    "symbol": "editor_bake_probe_004bf770",
    "va": "0x004bf770"
  },
  {
    "match_basis": [
      "shared_types:unsigned char"
    ],
    "package": "PKG-EDITOR-SAFE-WAVE11",
    "score": 3,
    "symbol": "editor_bake_select_004c4a30",
    "va": "0x004c4a30"
  },
  {
    "match_basis": [
      "shared_types:unsigned char"
    ],
    "package": "PKG-SKINNER-SAFE-WAVE11",
    "score": 3,
    "symbol": "skin_paint_slot_pass_005183c0",
    "va": "0x005183c0"
  },
  {
    "match_basis": [
      "shared_types:unsigned char"
    ],
    "package": "PKG-SKINNER-SAFE-WAVE11",
    "score": 3,
    "symbol": "skin_tex0_full_region_00518bf0",
    "va": "0x00518bf0"
  },
  {
    "match_basis": [
      "shared_types:unsigned char"
    ],
    "package": "PKG-SKINNER-SAFE-WAVE11",
    "score": 3,
    "symbol": "skin_tex2_uv_region_00518cf0",
    "va": "0x00518cf0"
  },
  {
    "match_basis": [
      "shared_types:unsigned char"
    ],
    "package": "PKG-SKINNER-SAFE-WAVE11",
    "score": 3,
    "symbol": "skin_rig_block_draw_00518f10",
    "va": "0x00518f10"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Resource__PFRecordWrite__GetState.c",
  "file": "src/reconstruction/pkg_resource_state_safe_wave10/resource_state_safe_wave10.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Resource__PFRecordWrite__GetState.c",
    "src/reconstruction/pkg_resource_state_safe_wave10/resource_state_safe_wave10.cpp",
    "src/reconstruction/pkg_resource_state_safe_wave10/resource_state_safe_wave10.hpp",
    "src/reconstruction/pkg_resource_state_safe_wave10/resource_state_safe_wave10_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave10-safe-core/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-resource-state-safe-wave10/00e310c0.json"
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
    "0x00e30f90 and 0x00f47380 remain dependency-only, so the release and untrack effects are unverified in this package.",
    "No original-process invocation was captured.",
    "The published entry is reached only through the 0x01481948 vtable slot and the 0x00e31020 thunk that rebases ECX by -0x8.",
    "The receiver class identity is unresolved; the target never dereferences the receiver so no field evidence exists.",
    "What 0x00e30f90 and 0x00f47380 actually release, and in what order relative to the untrack",
    "What class owns the receiver that the 0x01481948 vtable slot publishes",
    "Whether the -0x8 receiver rebase performed by the 0x00e31020 thunk changes what the caller observes",
    "Which caller supplies the release flag, given the only caller is the 0x00e31020 thunk",
    "gate-record-write-get-state-runtime-receiver-identity"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/Resource__PFRecordWrite__GetState.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave10-safe-core/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-resource-state-safe-wave10/00e310c0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_resource_state_safe_wave10/resource_state_safe_wave10.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_resource_state_safe_wave10/resource_state_safe_wave10.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_resource_state_safe_wave10/resource_state_safe_wave10_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/Resource__PFRecordWrite__GetState.c",
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
      "ref": "reconstruction/integrated/batch-2026-09-25-wave10-safe-core/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg-resource-state-safe-wave10/00e310c0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_resource_state_safe_wave10/resource_state_safe_wave10.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode"
[TRUNCATED]
```
