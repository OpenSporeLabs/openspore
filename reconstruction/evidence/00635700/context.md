# Reconstruction context 0x00635700

- Status: `partial`
- Content SHA-256: `8531454be8616768a7bdd3e4fbec3c5255684aed9f753d7af4204a8d4715ffc6`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00635700",
  "phase": "reconstruction",
  "target": "0x00635700"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueImageArchive",
  "name": "image_archive_scalar_deleting_destructor_00635700",
  "package": "PKG-UI-SAFE-WAVE10",
  "subsystem": "UI.ImageArchive",
  "va": "0x00635700"
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
  "content_sha256": "0bf85f649bb9c5499d46d15919b0825218111799d0eaee89d3866ac4af5c6951",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00635700 failed: Decompilation did not complete. Reason: ",
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
      "machine_type": "std::uint32_t",
      "native_reads": [
        "TEST byte ptr [ESP + 0x8],0x1"
      ],
      "normalized_name": "deleting",
      "note": "the slot is one word wide but only its low byte is read; after PUSH ESI it is observed at ESP+0x8",
      "position": 1,
      "width_bytes": 4
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
      "callsite": "0x0063572f",
      "direction": "out",
      "other": "0x00811fe0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00635737",
      "direction": "out",
      "other": "0x00811fe0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00635751",
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
    "ImageArchivePorts",
    "OpaqueImageArchive",
    "OpaqueImageArchive*",
    "OpaqueService24",
    "OpaqueSlot",
    "unsigned int"
  ],
  "vtables": []
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
      "The deallocation port 0x00f47380 is shared with other campaign packages and is not promoted here.",
      "The four vtable words are literal image addresses with no class attribution in the live database.",
      "The handle release slot at +0x04 and the service destructor 0x00811fe0 are opaque seams and are not promoted.",
      "The higher bits of the deleting flag are not interpreted; only its low byte is read.",
      "gate-image-archive-destructor-runtime-vtable-owners",
      "runtime validation not performed; static decompilation and disassembly only",
      "the deallocation port 0x00f47380 is shared with other campaign packages and is not promoted here",
      "the deleting flag is a one word formal whose low byte is the only bit read; the higher bits are not interpreted",
      "the four vtable words 0x013fe728, 0x013fe718, 0x013ec458 and 0x013eb938 are literal image addresses with no class attribution in the live database",
      "the two handle release slots at handle+0x04 and the service destructor 0x00811fe0 are opaque seams and are not promoted"
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
      "callsite": "0x0063572f",
      "direction": "out",
      "other": "0x00811fe0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00635737",
      "direction": "out",
      "other": "0x00811fe0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00635751",
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
    "0x00811fe0",
    "0x00f47380"
  ],
  "manifest_callers": [],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0148",
    "size": 1
  },
  "vtable_reference_count": 4
}
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "shared_types:unsigned int",
      "same_calling_convention"
    ],
    "package": "PKG-APP-SAFE-WAVE10",
    "score": 5,
    "symbol": "cursor_buffer_emit_0041e8b0",
    "va": "0x0041e8b0"
  },
  {
    "match_basis": [
      "shared_types:unsigned int",
      "same_calling_convention"
    ],
    "package": "PKG-SKINNER-SAFE-WAVE10",
    "score": 5,
    "symbol": "skin_painter_state_setup_00506590",
    "va": "0x00506590"
  },
  {
    "match_basis": [
      "shared_types:unsigned int",
      "same_calling_convention"
    ],
    "package": "PKG-EDITOR-SAFE-WAVE10",
    "score": 5,
    "symbol": "editor_row_publish_005a2010",
    "va": "0x005a2010"
  },
  {
    "match_basis": [
      "shared_types:unsigned int",
      "same_calling_convention"
    ],
    "package": "PKG-PALETTE-SAFE-WAVE10",
    "score": 5,
    "symbol": "page_visible_slots_refresh_005c0a60",
    "va": "0x005c0a60"
  },
  {
    "match_basis": [
      "shared_types:unsigned int"
    ],
    "package": "PKG-APP-SAFE-WAVE11",
    "score": 3,
    "symbol": "property_record_assign_pair_004279d0",
    "va": "0x004279d0"
  },
  {
    "match_basis": [
      "shared_types:unsigned int"
    ],
    "package": "PKG-APP-SAFE-WAVE11",
    "score": 3,
    "symbol": "property_record_assign_scalar_00428060",
    "va": "0x00428060"
  },
  {
    "match_basis": [
      "shared_types:unsigned int"
    ],
    "package": "PKG-APP-SAFE-WAVE11",
    "score": 3,
    "symbol": "pair_vector_construct_004b62a0",
    "va": "0x004b62a0"
  },
  {
    "match_basis": [
      "shared_types:unsigned int"
    ],
 
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg_ui_safe_wave10/ui_safe_wave10.cpp",
  "files": [
    "src/reconstruction/pkg_ui_safe_wave10/ui_safe_wave10.cpp",
    "src/reconstruction/pkg_ui_safe_wave10/ui_safe_wave10.hpp",
    "src/reconstruction/pkg_ui_safe_wave10/ui_safe_wave10_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave10-safe-core/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-ui-safe-wave10/00635700.json"
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
    "The deallocation port 0x00f47380 is shared with other campaign packages and is not promoted here.",
    "The four vtable words are literal image addresses with no class attribution in the live database.",
    "The handle release slot at +0x04 and the service destructor 0x00811fe0 are opaque seams and are not promoted.",
    "The higher bits of the deleting flag are not interpreted; only its low byte is read.",
    "What the service subobjects at +0x14 and +0x2c own and what 0x00811fe0 destroys in them",
    "What the two handles at +0x64 and +0x68 reference",
    "What the upper bytes of the deleting flag mean, since only the low byte is read",
    "Which classes the vtables at 0x013fe728, 0x013fe718, 0x013ec458 and 0x013eb938 belong to",
    "Who supplies the deallocation in 0x00f47380 and whether it matches the module allocator",
    "gate-image-archive-destructor-runtime-vtable-owners",
    "runtime validation not performed; static decompilation and disassembly only",
    "the deallocation port 0x00f47380 is shared with other campaign packages and is not promoted here",
    "the deleting flag is a one word formal whose low byte is the only bit read; the higher bits are not interpreted",
    "the four vtable words 0x013fe728, 0x013fe718, 0x013ec458 and 0x013eb938 are literal image addresses with no class attribution in the live database",
    "the two handle release slots at handle+0x04 and the service destructor 0x00811fe0 are opaque seams and are not promoted"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave10-safe-core/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-ui-safe-wave10/00635700.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_ui_safe_wave10/ui_safe_wave10.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_ui_safe_wave10/ui_safe_wave10.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_ui_safe_wave10/ui_safe_wave10_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-ui-safe-wave10/00635700.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_ui_safe_wave10/ui_safe_wave10.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_ui_safe_wave10/ui_safe_wave10.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_ui_safe_w
[TRUNCATED]
```
