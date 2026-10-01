# Reconstruction context 0x00985ce0

- Status: `partial`
- Content SHA-256: `4540691ea697a06a5c8dde68e417608a629bb5344af312885dd5baa5c2fe6318`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00985ce0",
  "phase": "reconstruction",
  "target": "0x00985ce0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "ImageDrawable",
  "name": "UTFWin::ImageDrawable::SetAlignmentHorizontal",
  "package": "PKG-UTFWIN-DRAWABLE-WAVE9",
  "subsystem": "UTFWin.Drawable",
  "va": "0x00985ce0"
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
  "content_sha256": "49bcdc5435689b5de6c33728d16ae78bc18d65c4ef6ac7a12505d5d27409213e",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00985ce0 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "__thiscall (no stack arguments, no cleanup)",
  "hidden_this_register": "ECX (read but unused)",
  "ordinary_stack_arguments": [],
  "ret_form": "plain RET",
  "return_register": "EAX",
  "return_type": "uint32_t",
  "stack_cleanup_bytes": 0
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
    "ImageDrawable",
    "uint32_t"
  ],
  "vtables": [
    "vtable:0x01445060"
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
      "No original-process invocation or indirect-caller trace was captured.",
      "The constant 0x4f063bb3 is not decoded; whether it is a real alignment value, a sentinel, or a placeholder is unresolved.",
      "The imported name SetAlignmentHorizontal is a candidate label only; the body performs no alignment write.",
      "gate-utfwin-stub-constant-decoding"
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
    "id": "scc-0329",
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
      "same_subsystem"
    ],
    "package": "PKG-UTFWIN-DRAWABLE-WAVE9",
    "score": 14,
    "symbol": "re_009849a0",
    "va": "0x009849a0"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem"
    ],
    "package": "PKG-UTFWIN-DRAWABLE-WAVE9",
    "score": 14,
    "symbol": "re_00987ae0",
    "va": "0x00987ae0"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "PKG-UTFWIN-DRAWABLE-WAVE9",
    "score": 8,
    "symbol": "re_00b267d0",
    "va": "0x00b267d0"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x01445060"
    ],
    "package": "PKG-UTFWIN-CORE-WAVE6",
    "score": 4,
    "symbol": "re_00951230",
    "va": "0x00951230"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x01445060"
    ],
    "package": "pkg-sporepedia-nop-slot",
    "score": 4,
    "symbol": "sporepedia_nop_slot_FUN_00c2e4e0",
    "va": "0x00c2e4e0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-ARGSCRIPT-WAVE9",
    "score": 2,
    "symbol": "pkg_argscript_get_current_scope_00d1dcd0",
    "va": "0x00d1dcd0"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__ImageDrawable__SetAlignmentHorizontal.c",
  "file": "src/reconstruction/pkg_utfwin_drawable_wave9/utfwin_drawable_wave9.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__ImageDrawable__SetAlignmentHorizontal.c",
    "src/reconstruction/pkg_utfwin_drawable_wave9/utfwin_drawable_wave9.cpp",
    "src/reconstruction/pkg_utfwin_drawable_wave9/utfwin_drawable_wave9.hpp",
    "src/reconstruction/pkg_utfwin_drawable_wave9/utfwin_drawable_wave9_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave9-safe-core/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-utfwin-drawable-wave9/00985ce0.json"
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
    "Decoded meaning of the 0x4f063bb3 constant",
    "No original-process invocation or indirect-caller trace was captured.",
    "The constant 0x4f063bb3 is not decoded; whether it is a real alignment value, a sentinel, or a placeholder is unresolved.",
    "The imported name SetAlignmentHorizontal is a candidate label only; the body performs no alignment write.",
    "Whether callers ignore the EAX result",
    "Why the stub is present in place of the imported setter behavior",
    "gate-utfwin-stub-constant-decoding"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__ImageDrawable__SetAlignmentHorizontal.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave9-safe-core/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-utfwin-drawable-wave9/00985ce0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_utfwin_drawable_wave9/utfwin_drawable_wave9.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_utfwin_drawable_wave9/utfwin_drawable_wave9.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_utfwin_drawable_wave9/utfwin_drawable_wave9_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__ImageDrawable__SetAlignmentHorizontal.c",
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
      "ref": "reconstruction/integrated/batch-2026-09-25-wave9-safe-core/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg-utfwin-drawable-wave9/00985ce0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_utfwin_drawable_wave9/utfwin_drawable_wave9.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "p
[TRUNCATED]
```
