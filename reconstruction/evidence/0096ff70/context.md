# Reconstruction context 0x0096ff70

- Status: `partial`
- Content SHA-256: `39a51dc2a33be475a00127e2d7f39bb06687850c4266ea484e2bc0171a755e16`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x0096ff70",
  "phase": "reconstruction",
  "target": "0x0096ff70"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "UTFWin::GlideEffect::func88h",
  "package": "pkg-dfw-0096ff70",
  "subsystem": "UTFWin",
  "va": "0x0096ff70"
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
  "content_sha256": "85a52ad47b3ffcd7a156e021601b1687080f15327093211646d4878565cdc8fa",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x0096ff70 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "thiscall adjustor thunk with one forwarded stack word",
  "hidden_receiver": "ECX GlideEffectBiStateSubobject* (a pointer 0x0C bytes ABOVE the object the tail target operates on)",
  "ordinary_stack_arguments": [
    {
      "entry_offset": "ESP+0x08 (as observed inside the tail target 0x0096FFD0)",
      "name": "deleting_flag",
      "position": 1,
      "type": "uint32",
      "usage": "only bit 0 is read, by TEST byte [ESP+0x8],0x1 at 0x0096fff3"
    }
  ],
  "ret_form": "RET 0x4 at 0x00970006, inside the tail target; the thunk itself has no RET",
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
  "edge_rows": [
    {
      "callsite": "0x0096ff73",
      "direction": "out",
      "other": "0x0096ffd0",
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
  "globals": [
    "global:PASS"
  ],
  "types": [
    "DATA",
    "GlideEffect (UTFWin::GlideEffect, SDK SIZE 0x70, 32-bit)",
    "GlideEffectVTableRun (pointer run based at 0x01442584, 4 transcribed slots)",
    "OpaqueVtable (4 opaque slots, used for all four documented vptr words)",
    "uint32",
    "void"
  ],
  "vtables": [
    "vtable:0x01442584"
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
      "No runtime validation has been run; every claim here is static.",
      "The concrete caller that dispatches through the vftable entry at 0x0144258c is unknown, so the values of the deleting flag in real use are unknown.",
      "Whether the -0x0C receiver is a GlideEffect IBiStateEffect subobject or the analogous subobject of a sibling class (the same two-instruction shape is shared by UTFWin::InflateEffect::func88h at 0x0097e550 and by 0x0096ff80 with -0x04) is not settled by the static image."
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
      "callsite": "0x0096ff73",
      "direction": "out",
      "other": "0x0096ffd0",
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
    "id": "scc-0312",
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
      "shared_types:DATA,uint32"
    ],
    "package": "pkg-dfw-00980c50",
    "score": 12,
    "symbol": "dfw_00980c50_func88h",
    "va": "0x00980c50"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_types:DATA"
    ],
    "package": "pkg-0095fa30-utfwin-isancestorof",
    "score": 9,
    "symbol": "is_ancestor_of_0095fa30",
    "va": "0x0095fa30"
  },
  {
    "match_basis": [
      "shared_types:DATA,uint32"
    ],
    "package": "PKG-18-UI-SCRIPTING",
    "score": 6,
    "symbol": "FUN_005bf9d0",
    "va": "0x005bf9d0"
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
    "package": "pkg-dfw-00980510",
    "score": 6,
    "symbol": "dfw_get_proxy_id_00980510",
    "va": "0x00980510"
  },
  {
    "match_basis": [
      "shared_types:DATA,uint32"
    ],
    "package": "PKG-GAME-INPUT-WAVE8",
    "score": 6,
    "symbol": "cell_mode_strategy_on_mouse_up_00e5c0f0",
    "va": "0x00e5c0f0"
  },
  {
    "match_basis": [
      "shared_types:DATA,uint32"
    ],
    "package": "PKG-GAME-INPUT-WAVE8",
    "score": 6,
    "symbol": "cell_mode_strategy_on_mouse_down_00e6c860",
    "va": "0x00e6c860"
  },
  {
    "match_basis": [
      "shared_types:DATA,uint32"
    ],
    "package": "PKG-GAME-INPUT-WAVE8",
    "score": 6,
    "symbol": "cell_mode_strategy_on_mouse_wheel_00e7d660",
    "va": "0x00e7d660"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__GlideEffect__func88h.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__GlideEffect__func88h.c",
    "reconstruction/staging/pkg-dfw-0096ff70/dfw_0096ff70.cpp",
    "reconstruction/staging/pkg-dfw-0096ff70/dfw_0096ff70_model_test.cpp",
    "reconstruction/staging/pkg-dfw-0096ff70/dfw_0096ff70_types.hpp",
    "reconstruction/staging/pkg-utfwin-glideeffect-func88h/utfwin_glideeffect_func88h.cpp",
    "reconstruction/staging/pkg-utfwin-glideeffect-func88h/utfwin_glideeffect_func88h.hpp",
    "reconstruction/staging/pkg-utfwin-glideeffect-func88h/utfwin_glideeffect_func88h_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-dfw-0096ff70/0096ff70.json",
    "reconstruction/metadata/pkg-utfwin-glideeffect-func88h/0096ff70.json"
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
    "Is the -0x0C receiver the subobject the vptr was reached through, or an unrelated pointer the caller happened to hold? Deciding it needs a runtime trace of the value in ECX at 0x0096ff70, which this repository has never run.",
    "Is the receiver a UTFWin::GlideEffect IBiStateEffect subobject, or the same-offset subobject of a sibling effect class? The SDK places IBiStateEffect at +0x0c and the adjustment is 0x0C, but the byte-for-byte identical shape at 0x0097e550 (UTFWin::InflateEffect::func88h) and the -0x04 shape at 0x0096ff80 make the two-instruction form non-distinguishing, and the static image does not settle it. The model therefore names no class at all.",
    "Is the receiver of 0x0096ff70 a UTFWin::GlideEffect IBiStateEffect subobject, or the same-offset subobject of a sibling effect class? The identical SUB ECX,0x0C/JMP shape at 0x0097e550 (UTFWin::InflateEffect::func88h) makes the shapes non-distinguishing.",
    "No runtime validation has been run; every claim here is static.",
    "The calling convention is an inference, not a record. The machine-derived ABI record abstains outright (verdict ABI_UNKNOWN, confidence UNKNOWN) because the body has no terminal RET, and the live decompilation carries 'WARNING: Unknown calling convention'. thiscall is the best-supported reading -- the tail target's own RET 0x4 pops the one forwarded word, and the receiver travels in ECX -- and it is what the model declares, but nothing in the target's own two instructions proves it. This is the sole reason the ABI check is a WAR
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__GlideEffect__func88h.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-dfw-0096ff70/0096ff70.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-utfwin-glideeffect-func88h/0096ff70.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-dfw-0096ff70/dfw_0096ff70.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-dfw-0096ff70/dfw_0096ff70_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-dfw-0096ff70/dfw_0096ff70_types.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-utfwin-glideeffect-func88h/utfwin_glideeffect_func88h.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-utfwin-glideeffect-func88h/utfwin_glideeffect_func88h.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-utfwin-glideeffect-func88h/utfwin_glideeffect_func88h_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__GlideEffect__func88h.c",
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
      "ref": "reconstruction/metadata/pkg-dfw-0096ff70/0096ff70.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg-utfwin-glideeffect-func88h/0096ff70.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-dfw-0096ff70/dfw_0096ff70.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/sta
[TRUNCATED]
```
