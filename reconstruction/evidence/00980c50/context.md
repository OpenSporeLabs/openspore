# Reconstruction context 0x00980c50

- Status: `partial`
- Content SHA-256: `2707ffaa1723459733618d411e71f76efe393b118edf2705d998ebde6e68715b`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00980c50",
  "phase": "reconstruction",
  "target": "0x00980c50"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "UTFWin::RotateEffect::func88h",
  "package": "pkg-dfw-00980c50",
  "subsystem": "UTFWin",
  "va": "0x00980c50"
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
  "content_sha256": "488b8329a85997cd80d79a0d2d4701e1d424535feec10d344df159390c6d31ce",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00980c50 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": [
    "__thiscall (persisted record; derived record abstained)",
    "thiscall receiver in ECX (per the SDK method header) with caller stack cleanup; the receiver and every argument are ignored"
  ],
  "hidden_receiver": "ECX, typed as the RotateEffect receiver by the SDK method header. The frame never reads ECX, so the receiver cannot influence the result and no subobject offset can be recovered from this address.",
  "hidden_this": true,
  "hidden_this_register": "ECX",
  "ordinary_stack_arguments": [
    "{'entry_offset': 'ESP+0x08 on entry', 'name': 'param_2', 'position': 1, 'type': 'uint32', 'usage': 'never read; the frame executes no memory load at all'}",
    "{'entry_offset': 'ESP+0x0C on entry', 'name': 'param_3', 'position': 2, 'type': 'uint32', 'usage': 'never read'}",
    "{'entry_offset': 'ESP+0x10 on entry', 'name': 'param_4', 'position': 3, 'type': 'uint32', 'usage': 'never read'}"
  ],
  "receiver_register": "ECX",
  "ret_form": [
    "RET",
    "bare RET at 0x00980c55; the caller pops, which the staged model test exercises by pushing three words and removing them with 'addl $12, %esp' after the call"
  ],
  "return_register": "EAX",
  "return_type": "std::uint32_t",
  "saved_registers": [],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "RET"
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
  "globals": [
    "global:PASS"
  ],
  "types": [
    "DATA",
    "Opaque = std::uint32_t (opaque 32-bit word)",
    "RotateEffectTokenWord (the receiver's leading 32-bit word, the only word any observed code touches)",
    "RotateEffectVTableRun (pointer run based at 0x01444364, 12 transcribed slots)",
    "std::uint32_t",
    "uint32"
  ],
  "vtables": [
    "vtable:0x01444314",
    "vtable:0x01444364"
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
      "The dispatching caller of the run's slot +0x00 is unknown, so the circumstances under which this getter is invoked -- and whether its result is compared against anything -- are unknown.",
      "Whether slot +0x00 of the run is genuinely a getter of the word the block at 0x00980c80 stores is unproven; the adjacency is a byte-level argument only."
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
    "id": "scc-0326",
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
    "package": "pkg-dfw-0096ff70",
    "score": 12,
    "symbol": "dfw_func88h_0096ff70",
    "va": "0x0096ff70"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__RotateEffect__func88h.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__RotateEffect__func88h.c",
    "reconstruction/metadata/pkg-utfwin-rotateeffect-func88h/00980c50.json",
    "reconstruction/staging/pkg-dfw-00980c50/dfw_00980c50.cpp",
    "reconstruction/staging/pkg-dfw-00980c50/dfw_00980c50_model_test.cpp",
    "reconstruction/staging/pkg-dfw-00980c50/dfw_00980c50_types.hpp",
    "reconstruction/staging/pkg-utfwin-rotateeffect-func88h/utfwin_rotateeffect_func88h_00980c50.cpp",
    "reconstruction/staging/pkg-utfwin-rotateeffect-func88h/utfwin_rotateeffect_func88h_00980c50.hpp",
    "reconstruction/staging/pkg-utfwin-rotateeffect-func88h/utfwin_rotateeffect_func88h_00980c50_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-dfw-00980c50/00980c50.json",
    "reconstruction/metadata/pkg-utfwin-rotateeffect-func88h/00980c50.json"
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
    "Is the SDK return type void or is it a 32-bit value? The machine writes EAX with an immediate, but a void-returning SDK placeholder is equally consistent with the vtable generator's naming. The span is modelled as returning std::uint32_t; a human reviewer with vftable context may prefer void.",
    "Is the SDK return type void, or is it a 32-bit value? The machine writes EAX with an immediate; the SDK header, the Ghidra import and the live decompilation all say void. The span is modelled as returning std::uint32_t because that is what the two instructions do, and the void reading is left open rather than refuted. Carried forward unchanged from the pack.",
    "No runtime validation has been run; every claim here is static.",
    "Nothing else was investigated and nothing else is claimed. The adjustor thunks at 0x00980c60 and 0x00980c70, the INT3 padding their jumps target at 0x00980cb0, the four identical 0x006f2f20 entries at slots +0x20..+0x2c of the run, and the 0x0096ff70 sibling are all outside this six-byte span; they are named here only to record that they were left alone.",
    "The dispatching caller of the run's slot +0x00 is unknown, so the circumstances under which this getter is invoked -- and whether its result is compared against anything -- are unknown.",
    "What conventions is the frame compatible with? The derived record lists [__cdecl, __stdcall, __thiscall, __fastcall] with confidence UNKNOWN, and its own inference C10 notes the function is byte-identical under all four. This package picks __thiscal
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__RotateEffect__func88h.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-dfw-00980c50/00980c50.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-utfwin-rotateeffect-func88h/00980c50.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-dfw-00980c50/dfw_00980c50.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-dfw-00980c50/dfw_00980c50_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-dfw-00980c50/dfw_00980c50_types.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-utfwin-rotateeffect-func88h/utfwin_rotateeffect_func88h_00980c50.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-utfwin-rotateeffect-func88h/utfwin_rotateeffect_func88h_00980c50.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-utfwin-rotateeffect-func88h/utfwin_rotateeffect_func88h_00980c50_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__RotateEffect__func88h.c",
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
      "ref": "reconstruction/metadata/pkg-dfw-00980c50/00980c50.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg-utfwin-rotateeffect-func88h/00980c50.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-dfw-00980c50/dfw_00980c50.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/s
[TRUNCATED]
```
