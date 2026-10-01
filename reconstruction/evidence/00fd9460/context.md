# Reconstruction context 0x00fd9460

- Status: `partial`
- Content SHA-256: `6c1154822dcbeb0e05e20cb413cc5e5acffb54a2634fbff97b8438e4913e6324`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00fd9460",
  "phase": "reconstruction",
  "target": "0x00fd9460"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "UTFWin::ImageDrawable::SetTiling",
  "package": "pkg-utfwin-settiling-wave13",
  "subsystem": "UTFWin",
  "va": "0x00fd9460"
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
  "content_sha256": "73b2fd93424fdb89127adbab0d76c3164aa400c17069cd5d009c9251ec56743b",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00fd9460 failed: Decompilation did not complete. Reason: ",
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
  "convention": "__thiscall",
  "hidden_this": true,
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": [
    "entry_ESP+0x4"
  ],
  "ordinary_stack_arguments": [
    {
      "entry_offset": "entry_ESP+0x4",
      "name": "tiling",
      "note": "The name and the SDK type come from the Spore-ModAPI import. The body stores the word verbatim with no mask, range check, comparison or conversion, so the declared C++ type is NOT established; the import label is a candidate label only.",
      "observed": true,
      "ordinal": 1,
      "sdk_label": "ImageTiling tiling",
      "size_inferred": false,
      "sizes": [
        4
      ],
      "type": "opaque 32-bit word"
    }
  ],
  "receiver": true,
  "receiver_register": "ECX",
  "ret_form": "RET 0x4",
  "return_register": "EAX",
  "return_semantics": "void; no value is produced for the caller",
  "return_type": "void",
  "return_width_bytes": 0,
  "saved_registers": "ESI is pushed at 0x00fd9464 and popped at 0x00fd9472, so the callee-save obligation is discharged. No other callee-saved register is written.",
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "callee",
  "termination": "RET 0x4"
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
      "callsite": "0x00fd946a",
      "direction": "out",
      "other": "0x011e58c0",
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
    "opaque 32-bit word",
    "void"
  ],
  "vtables": [
    "vtable:0x01493d00",
    "vtable:0x01493d20"
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
      "No original-process invocation or indirect-caller trace was captured, so no concrete caller is known and the tiling values a real caller passes cannot be observed.",
      "The C++ type, class name and role of the shared static object whose pointer is published at +0x08 are unestablished; its vtable 0x014f6f80 carries no names, and SporeApp.exe has no MSVC RTTI.",
      "The declared C++ types of receiver +0x04 and +0x08 are not established. +0x04 is stored verbatim with no validation, and the import label ImageTiling is a candidate label, not machine evidence.",
      "The interface identity of vtable slot +0x70 of 0x01493d00 is unresolved; the eighteen purecall entries show it is a wide interface but not which one.",
      "Which constructor initialises +0x04 and +0x08 is unresolved: 0x00fd95f0 installs only the vtable and writes no field beyond +0x00."
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
      "callsite": "0x00fd946a",
      "direction": "out",
      "other": "0x011e58c0",
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
    "id": "scc-0584",
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
      "same_subsystem",
      "shared_types:opaque 32-bit word",
      "same_calling_convention"
    ],
    "package": "pkg-utfwin-slot7-wave12",
    "score": 11,
    "symbol": "re_00fc7e10_UTFWin_ImageDrawable_GetTiling",
    "va": "0x00fc7e10"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "pkg-dfw-00980510",
    "score": 8,
    "symbol": "dfw_get_proxy_id_00980510",
    "va": "0x00980510"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "pkg-0095fa30-utfwin-isancestorof",
    "score": 6,
    "symbol": "is_ancestor_of_0095fa30",
    "va": "0x0095fa30"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "pkg-utfwin-func35-wave12",
    "score": 6,
    "symbol": "func35_0095fd60",
    "va": "0x0095fd60"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "pkg-dfw-0096ff70",
    "score": 6,
    "symbol": "dfw_func88h_0096ff70",
    "va": "0x0096ff70"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "pkg-dfw-00980c50",
    "score": 6,
    "symbol": "dfw_00980c50_func88h",
    "va": "0x00980c50"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x01493d20",
      "same_calling_convention"
    ],
    "package": "pkg-sporepedia-nop-slot",
    "score": 6,
    "symbol": "sporepedia_nop_slot_FUN_00c2e4e0",
    "va": "0x00c2e4e0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-APP-SAFE-WAVE11",
    "score": 2,
    "symbol": "property_record_assign_pair_
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__ImageDrawable__SetTiling.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__ImageDrawable__SetTiling.c",
    "reconstruction/staging/pkg-utfwin-settiling-wave13/.clang-format",
    "reconstruction/staging/pkg-utfwin-settiling-wave13/utfwin_settiling_wave13.cpp",
    "reconstruction/staging/pkg-utfwin-settiling-wave13/utfwin_settiling_wave13.hpp",
    "reconstruction/staging/pkg-utfwin-settiling-wave13/utfwin_settiling_wave13_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-utfwin-settiling-wave13/00fd9460.json"
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
    "Is the sibling SDK-named GetTiling at 0x00fc7e10 the matching accessor for this target's +0x04 word? It publishes two stack words at +0x08 and +0x10 of a receiver in the 0x01491730/0x01492140/0x01493990 family, which is a different class from this one, so the pairing is not established.",
    "No original-process invocation or indirect-caller trace was captured, so no concrete caller is known and the tiling values a real caller passes cannot be observed.",
    "The C++ type, class name and role of the shared static object whose pointer is published at +0x08 are unestablished; its vtable 0x014f6f80 carries no names, and SporeApp.exe has no MSVC RTTI.",
    "The declared C++ types of receiver +0x04 and +0x08 are not established. +0x04 is stored verbatim with no validation, and the import label ImageTiling is a candidate label, not machine evidence.",
    "The interface identity of vtable slot +0x70 of 0x01493d00 is unresolved; the eighteen purecall entries show it is a wide interface but not which one.",
    "What are the fifteen purecall slots at +0x2c..+0x64 of 0x01493d00? They are unresolved by definition, and the width of the interface constrains but does not identify it.",
    "What is the declared C++ type of the word at receiver +0x04? The Spore-ModAPI import calls the argument ImageTiling tiling, but the body stores it verbatim with no mask, comparison or conversion, so the import label is not machine-confirmed.",
    "What is the shared static object whose pointer is published at receiver +0x08? Its storage is 0x0
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__ImageDrawable__SetTiling.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-utfwin-settiling-wave13/00fd9460.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-utfwin-settiling-wave13/.clang-format', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-utfwin-settiling-wave13/utfwin_settiling_wave13.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-utfwin-settiling-wave13/utfwin_settiling_wave13.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-utfwin-settiling-wave13/utfwin_settiling_wave13_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__ImageDrawable__SetTiling.c",
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
      "ref": "reconstruction/metadata/pkg-utfwin-settiling-wave13/00fd9460.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-utfwin-settiling-wave13/.clang-format",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-utfwin-settiling-wave13/utfwin_settiling_wave13.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
[TRUNCATED]
```
