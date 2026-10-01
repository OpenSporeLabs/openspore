# Reconstruction context 0x005c3000

- Status: `partial`
- Content SHA-256: `80a8c9c589329253230bf445a04efdd945c340211dd14eda50094b7d783f562b`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x005c3000",
  "phase": "reconstruction",
  "target": "0x005c3000"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaquePalette",
  "name": "palette_row_layout_005c3000",
  "package": "PKG-PALETTE-SAFE-WAVE10",
  "subsystem": "UI.PalettePage",
  "va": "0x005c3000"
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
  "content_sha256": "fdece4baec41dece08cea17948ba5a442d86e0651d35f5302c52754ec4b1bb81",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x005c3000 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "thiscall, receiver only, no stack arguments",
  "receiver_register": "ECX",
  "ret_form": "RET",
  "return_register": "EAX",
  "return_width_bytes": 0,
  "stack_arguments": [],
  "stack_cleanup_bytes": 0
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
      "va": "0x005c50b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005c51e0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x005c51c4",
      "direction": "in",
      "other": "0x005c50b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005c5220",
      "direction": "in",
      "other": "0x005c51e0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005c3061",
      "direction": "out",
      "other": "0x005c2aa0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005c3020",
      "direction": "out",
      "other": "0x008105b0",
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
    "OpaqueApp",
    "OpaqueAppProps",
    "OpaqueElement",
    "OpaquePalette",
    "OpaquePalette*",
    "OpaquePaletteGroup",
    "OpaqueRect",
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
      "The element vtable owner behind slot +0x38 and +0x6c is unattributed in the live database.",
      "The feature query port 0x008105b0 and the distinct row port 0x005c2aa0 are opaque seams and are not promoted.",
      "The group pointer at +0x6c is dereferenced without a null check, exactly as the native body does.",
      "The row gap global at 0x01486110 is modelled as a float whose runtime value is not established.",
      "The semantic identity of the feature id 0x05d3f56b is inferred from the call shape only.",
      "gate-palette-row-layout-runtime-group-and-feature-values",
      "runtime validation not performed; static decompilation and disassembly only",
      "the element vtable owner behind slot +0x38 and +0x6c is unattributed in the live database",
      "the feature query port 0x008105b0 and the distinct row port 0x005c2aa0 are opaque seams and are not promoted",
      "the group vector at group+0x0c/+0x10 is dereferenced without a null group check, exactly as the native body does",
      "the row gap global at 0x01486110 is modelled as a float whose runtime value is not established",
      "the semantic identity of the feature id 0x05d3f56b is inferred from the call shape only"
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
      "va": "0x005c50b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005c51e0"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x005c51c4",
      "direction": "in",
      "other": "0x005c50b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005c5220",
      "direction": "in",
      "other": "0x005c51e0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005c3061",
      "direction": "out",
      "other": "0x005c2aa0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005c3020",
      "direction": "out",
      "other": "0x008105b0",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 2,
  "fan_out": 0,
  "manifest_callees": [
    "0x008105b0",
    "0x005c2aa0"
  ],
  "manifest_callers": [],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0115",
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
      "shared_types:OpaqueRect"
    ],
    "package": "PKG-PALETTE-SAFE-WAVE10",
    "score": 17,
    "symbol": "page_visible_slots_refresh_005c0a60",
    "va": "0x005c0a60"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-APP-SAFE-WAVE10",
    "score": 2,
    "symbol": "property_value_resolve_0041e920",
    "va": "0x0041e920"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-SKINNER-SAFE-WAVE10",
    "score": 2,
    "symbol": "skin_painter_job_brush_pass_005182f0",
    "va": "0x005182f0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-SPOREPEDIA-SAFE-WAVE10",
    "score": 2,
    "symbol": "sporepedia_asset_destroy_00642190",
    "va": "0x00642190"
  }
]
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
    "reconstruction/metadata/pkg-palette-safe-wave10/005c3000.json"
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
    "The element vtable owner behind slot +0x38 and +0x6c is unattributed in the live database.",
    "The feature query port 0x008105b0 and the distinct row port 0x005c2aa0 are opaque seams and are not promoted.",
    "The group pointer at +0x6c is dereferenced without a null check, exactly as the native body does.",
    "The row gap global at 0x01486110 is modelled as a float whose runtime value is not established.",
    "The semantic identity of the feature id 0x05d3f56b is inferred from the call shape only.",
    "What the distinct row port 0x005c2aa0 counts",
    "What the feature id 0x05d3f56b identifies and which subsystem answers the query",
    "What the group byte at +0x70 means and how it relates to the group vector span",
    "Whether a null group at +0x6c is reachable in practice, since the native body does not check it",
    "Who owns the element vtable slots +0x38 and +0x6c",
    "gate-palette-row-layout-runtime-group-and-feature-values",
    "runtime validation not performed; static decompilation and disassembly only",
    "the element vtable owner behind slot +0x38 and +0x6c is unattributed in the live database",
    "the feature query port 0x008105b0 and the distinct row port 0x005c2aa0 are opaque seams and are not promoted",
    "the group vector at group+0x0c/+0x10 is dereferenced without a null group check, exactly as the native body does",
    "the row gap global at 0x01486110 is modelled as a float whose runtime value is not established",
    "the semantic identity of the feature id 0x05d3f56b is inferr
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave10-safe-core/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-palette-safe-wave10/005c3000.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_palette_safe_wave10/pkg_palette_safe_wave10.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_palette_safe_wave10/pkg_palette_safe_wave10.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_palette_safe_wave10/pkg_palette_safe_wave10_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-palette-safe-wave10/005c3000.json",
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
