# Reconstruction context 0x005a2010

- Status: `partial`
- Content SHA-256: `5e4b88f6fc8d2e6aff6a86ced22022063a18ad867c45f51a3cd8e06134ece8b6`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x005a2010",
  "phase": "reconstruction",
  "target": "0x005a2010"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "Editors::cEditor",
  "name": "editor_row_publish_005a2010",
  "package": "PKG-EDITOR-SAFE-WAVE10",
  "subsystem": "Editors.RowPublisher",
  "va": "0x005a2010"
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
  "content_sha256": "77ccab6a0fae46120df0227dd11c03fdd29d341de61b18c2229d31b1dd4c6714",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x005a2010 failed: Decompilation did not complete. Reason: ",
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
  "ret_form": "RET 0x10",
  "stack_arguments": [
    {
      "destination_slot": "+0x80",
      "entry_offset": "ESP+0x04",
      "machine_type": "float",
      "normalized_name": "row_x",
      "position": 1,
      "width_bytes": 4
    },
    {
      "destination_slot": "+0x84",
      "entry_offset": "ESP+0x08",
      "machine_type": "float",
      "normalized_name": "row_y",
      "position": 2,
      "width_bytes": 4
    },
    {
      "destination_slot": "+0x88",
      "entry_offset": "ESP+0x0c",
      "machine_type": "float",
      "normalized_name": "row_z",
      "position": 3,
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x10",
      "gate_width": "low byte only",
      "machine_type": "unsigned int",
      "native_test": "CMP byte ptr [ESP + 0x10],0x0",
      "normalized_name": "also_previous",
      "position": 4,
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 16
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
      "name": "Editors::cEditor::Update",
      "reconstructed": false,
      "va": "0x0058be50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e34540"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x0058cbbf",
      "direction": "in",
      "other": "0x0058be50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0058cbf5",
      "direction": "in",
      "other": "0x0058be50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e34641",
      "direction": "in",
      "other": "0x00e34540",
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
    "Editors::cEditor",
    "OpaqueRowPublisher",
    "OpaqueRowPublisher*",
    "float",
    "unsigned int",
    "void"
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
      "A full-word gate test would be observably wrong; the low-byte read is fixed by the CMP at the entry.",
      "No Wine differential run against the original binary was performed.",
      "Receiver class identity unresolved; no vtable label exists for this receiver in the live database.",
      "The semantic role of the +0x74 mirrored row versus the +0x80 row is not established by static evidence.",
      "gate-editor-row-publish-receiver-identity-and-row-semantics"
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
      "name": "Editors::cEditor::Update",
      "reconstructed": false,
      "va": "0x0058be50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e34540"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x0058cbbf",
      "direction": "in",
      "other": "0x0058be50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0058cbf5",
      "direction": "in",
      "other": "0x0058be50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e34641",
      "direction": "in",
      "other": "0x00e34540",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 2,
  "fan_out": 0,
  "manifest_callees": [],
  "manifest_callers": [],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0099",
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
    "package": "PKG-PALETTE-SAFE-WAVE10",
    "score": 5,
    "symbol": "page_visible_slots_refresh_005c0a60",
    "va": "0x005c0a60"
  },
  {
    "match_basis": [
      "shared_types:unsigned int",
      "same_calling_convention"
    ],
    "package": "PKG-UI-SAFE-WAVE10",
    "score": 5,
    "symbol": "image_archive_scalar_deleting_destructor_00635700",
    "va": "0x00635700"
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
      "shared_types:unsi
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg_editor_safe_wave10/editor_safe_wave10.cpp",
  "files": [
    "src/reconstruction/pkg_editor_safe_wave10/editor_safe_wave10.cpp",
    "src/reconstruction/pkg_editor_safe_wave10/editor_safe_wave10.hpp",
    "src/reconstruction/pkg_editor_safe_wave10/editor_safe_wave10_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave10-safe-core/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-editor-safe-wave10/005a2010.json"
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
    "A full-word gate test would be observably wrong; the low-byte read is fixed by the CMP at the entry.",
    "No Wine differential run against the original binary was performed.",
    "Receiver class identity unresolved; no vtable label exists for this receiver in the live database.",
    "The semantic role of the +0x74 mirrored row versus the +0x80 row is not established by static evidence.",
    "What the also_previous formal means above its low byte, since only the low byte is read",
    "Whether any consumer reads +0x74 at all",
    "Whether the +0x74 mirrored row is a previous-row cache or a second live row",
    "Which class the row publisher receiver belongs to; no vtable label exists for it",
    "gate-editor-row-publish-receiver-identity-and-row-semantics"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave10-safe-core/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-editor-safe-wave10/005a2010.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_editor_safe_wave10/editor_safe_wave10.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_editor_safe_wave10/editor_safe_wave10.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_editor_safe_wave10/editor_safe_wave10_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-editor-safe-wave10/005a2010.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_editor_safe_wave10/editor_safe_wave10.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_editor_safe_wave10/editor_safe_wave10.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstr
[TRUNCATED]
```
