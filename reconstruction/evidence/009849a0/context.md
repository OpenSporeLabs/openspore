# Reconstruction context 0x009849a0

- Status: `partial`
- Content SHA-256: `b469d749a079604314b5780b963b76af0d4ebe7d033c5a06cae44985930de72d`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x009849a0",
  "phase": "reconstruction",
  "target": "0x009849a0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "SpinnerDrawable",
  "name": "UTFWin::SpinnerDrawable::Paint",
  "package": "PKG-UTFWIN-DRAWABLE-WAVE9",
  "subsystem": "UTFWin.Drawable",
  "va": "0x009849a0"
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
  "content_sha256": "2692020e8d4eaeba1cc18bf06af36cf99bf6b6c4ba4849e12da5c8ff8dc15b17",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x009849a0 failed: Decompilation did not complete. Reason: ",
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
      "entry_offset": "ESP+0x04 (read after PUSH ESI, i.e. the incoming ESP+0x08 slot)",
      "name": "target",
      "type": "drawable header *",
      "width_bytes": 4
    }
  ],
  "ret_form": "RET 0x4",
  "return_register": "none",
  "return_type": "void",
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
    "SpinnerDrawable",
    "drawable header *",
    "void"
  ],
  "vtables": [
    "vtable:0x01444c60"
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
      "The 0x1444c24 tag is treated as an opaque published constant, not a decoded type id.",
      "The concrete vtable owner and meaning of slot +0x14 are unresolved; the result is only stored.",
      "gate-utfwin-drawable-slot-14-and-tag-decoding"
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
    "id": "scc-0328",
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
      "shared_types:drawable header *",
      "same_calling_convention"
    ],
    "package": "PKG-UTFWIN-DRAWABLE-WAVE9",
    "score": 19,
    "symbol": "re_00987ae0",
    "va": "0x00987ae0"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem"
    ],
    "package": "PKG-UTFWIN-DRAWABLE-WAVE9",
    "score": 14,
    "symbol": "re_00985ce0",
    "va": "0x00985ce0"
  },
  {
    "match_basis": [
      "same_package",
      "same_calling_convention"
    ],
    "package": "PKG-UTFWIN-DRAWABLE-WAVE9",
    "score": 10,
    "symbol": "re_00b267d0",
    "va": "0x00b267d0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-APP-SAFE-WAVE11",
    "score": 2,
    "symbol": "property_record_assign_pair_004279d0",
    "va": "0x004279d0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-APP-SAFE-WAVE11",
    "score": 2,
    "symbol": "property_record_assign_scalar_00428060",
    "va": "0x00428060"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-EDITOR-SAFE-WAVE11",
    "score": 2,
    "symbol": "editor_paint_commit_0043ac40",
    "va": "0x0043ac40"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-APP-SAFE-WAVE11",
    "score": 2,
    "symbol": "model_parts_apply_properties_00447150",
    "va": "0x00447150"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-APP-SAFE-WAVE11",
    "score": 2,
    "symbol": "
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__SpinnerDrawable__Paint.c",
  "file": "src/reconstruction/pkg_utfwin_drawable_wave9/utfwin_drawable_wave9.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__SpinnerDrawable__Paint.c",
    "src/reconstruction/pkg_utfwin_drawable_wave9/utfwin_drawable_wave9.cpp",
    "src/reconstruction/pkg_utfwin_drawable_wave9/utfwin_drawable_wave9.hpp",
    "src/reconstruction/pkg_utfwin_drawable_wave9/utfwin_drawable_wave9_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave9-safe-core/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-utfwin-drawable-wave9/009849a0.json"
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
    "Concrete owner and semantics of vtable slot +0x14",
    "Decoded meaning of the 0x1444c24 published tag",
    "No original-process invocation or indirect-caller trace was captured.",
    "The 0x1444c24 tag is treated as an opaque published constant, not a decoded type id.",
    "The concrete vtable owner and meaning of slot +0x14 are unresolved; the result is only stored.",
    "Whether the +0x8 word is a reference count, a live flag, or a paint counter",
    "Why the back-pointer is biased by four bytes",
    "gate-utfwin-drawable-slot-14-and-tag-decoding"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__SpinnerDrawable__Paint.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave9-safe-core/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-utfwin-drawable-wave9/009849a0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_utfwin_drawable_wave9/utfwin_drawable_wave9.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_utfwin_drawable_wave9/utfwin_drawable_wave9.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_utfwin_drawable_wave9/utfwin_drawable_wave9_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__SpinnerDrawable__Paint.c",
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
      "ref": "reconstruction/metadata/pkg-utfwin-drawable-wave9/009849a0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_utfwin_drawable_wave9/utfwin_drawable_wave9.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
    
[TRUNCATED]
```
