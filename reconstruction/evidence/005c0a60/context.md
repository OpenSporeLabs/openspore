# Reconstruction context 0x005c0a60

- Status: `partial`
- Content SHA-256: `757ecc63dcce24075cd0ffe71a0df4a8350e504de70a539025eed78c9da8f049`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x005c0a60",
  "phase": "reconstruction",
  "target": "0x005c0a60"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaquePage",
  "name": "page_visible_slots_refresh_005c0a60",
  "package": "PKG-PALETTE-SAFE-WAVE10",
  "subsystem": "UI.PalettePage",
  "va": "0x005c0a60"
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
  "content_sha256": "99c29edbdac9e03a785251f96fcff5748b09ce821d175af30e64b7dda836162d",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x005c0a60 failed: Decompilation did not complete. Reason: ",
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
  "return_width_bytes": 0,
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "machine_type": "std::uint32_t",
      "native_reads": [],
      "normalized_name": "argument",
      "note": "the entry accepts one stack word but never reads it; the body only tests byte ptr [ESP+0x8],0x1 against the deleting-destructor idiom position, so the argument is an unused formal",
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
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005c28b0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x005c28dc",
      "direction": "in",
      "other": "0x005c28b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005c0b2d",
      "direction": "out",
      "other": "0x0041e050",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005c0aa4",
      "direction": "out",
      "other": "0x005c29c0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005c0b64",
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
    "OpaquePage",
    "OpaquePage*",
    "OpaquePageCategory",
    "OpaqueRect",
    "OpaqueTextBuffer",
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
      "The decoded meaning of the format literal at 0x013f7c30 is inferred as '<n>/<total>' and is unconfirmed by any runtime render.",
      "The formatter 0x0041e050 and the release port 0x00f47380 remain dependency-only.",
      "The nav and text vtable owners are unattributed in the live database.",
      "The unused formal argument is kept only to preserve the RET 0x4 cleanup width.",
      "The visibility port 0x005c29c0 is an opaque bool seam and is not promoted.",
      "gate-page-visible-slots-runtime-visibility-and-format-literal",
      "runtime validation not performed; static decompilation and disassembly only",
      "the decoded meaning of the format literal at 0x013f7c30 is inferred as '<n>/<total>' and is not confirmed by a runtime render",
      "the nav and text vtable owners at slot +0x7c and +0x80 are unattributed in the live database",
      "the text formatter 0x0041e050 and the release port 0x00f47380 remain dependency-only",
      "the unused formal argument is retained in the signature to keep the RET 0x4 cleanup width exact",
      "the visibility port 0x005c29c0 is modelled as an opaque bool seam and is not promoted"
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
      "va": "0x005c28b0"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x005c28dc",
      "direction": "in",
      "other": "0x005c28b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005c0b2d",
      "direction": "out",
      "other": "0x0041e050",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005c0aa4",
      "direction": "out",
      "other": "0x005c29c0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005c0b64",
      "direction": "out",
      "other": "0x00f47380",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 1,
  "fan_out": 0,
  "manifest_callees": [
    "0x005c29c0",
    "0x0041e050",
    "0x00f47380"
  ],
  "manifest_callers": [],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0112",
    "size": 1
  },
  "vtable_reference_count": 1
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
      "shared_types:OpaqueRect"
    ],
    "package": "PKG-PALETTE-SAFE-WAVE10",
    "score": 17,
    "symbol": "palette_row_layout_005c3000",
    "va": "0x005c3000"
  },
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
    "mat
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg_palette_safe_wave10/pkg_palette_safe_wave10.cpp",
  "files": [
    "src/reconstruction/pkg_palette_safe_wave10/pkg_palette_safe_wave10.cpp",
    "src/reconstruction/pkg_palette_safe_wave10/pkg_palette_safe_wave10.hpp",
    "src/reconstruction/pkg_palette_safe_wave10/pkg_palette_safe_wave10_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave10-safe-core/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-palette-safe-wave10/005c0a60.json"
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
    "The decoded meaning of the format literal at 0x013f7c30 is inferred as '<n>/<total>' and is unconfirmed by any runtime render.",
    "The formatter 0x0041e050 and the release port 0x00f47380 remain dependency-only.",
    "The nav and text vtable owners are unattributed in the live database.",
    "The unused formal argument is kept only to preserve the RET 0x4 cleanup width.",
    "The visibility port 0x005c29c0 is an opaque bool seam and is not promoted.",
    "What the unused fourth formal was intended to select",
    "What the visibility port 0x005c29c0 actually tests to decide a slot is visible",
    "Whether the cached pair at +0x20 and +0x24 is ever invalidated by another path",
    "Whether the format literal at 0x013f7c30 really renders as '<n>/<total>'",
    "Who owns the nav vtable slot +0x7c and the text vtable slot +0x80",
    "gate-page-visible-slots-runtime-visibility-and-format-literal",
    "runtime validation not performed; static decompilation and disassembly only",
    "the decoded meaning of the format literal at 0x013f7c30 is inferred as '<n>/<total>' and is not confirmed by a runtime render",
    "the nav and text vtable owners at slot +0x7c and +0x80 are unattributed in the live database",
    "the text formatter 0x0041e050 and the release port 0x00f47380 remain dependency-only",
    "the unused formal argument is retained in the signature to keep the RET 0x4 cleanup width exact",
    "the visibility port 0x005c29c0 is modelled as an opaque bool seam and is not promoted"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave10-safe-core/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-palette-safe-wave10/005c0a60.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_palette_safe_wave10/pkg_palette_safe_wave10.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_palette_safe_wave10/pkg_palette_safe_wave10.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_palette_safe_wave10/pkg_palette_safe_wave10_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-palette-safe-wave10/005c0a60.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_palette_safe_wave10/pkg_palette_safe_wave10.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_palette_safe_wave10/pkg_palette_safe_wave10.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": 
[TRUNCATED]
```
