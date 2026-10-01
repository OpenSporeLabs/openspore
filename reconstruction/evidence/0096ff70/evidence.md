# Evidence 0x0096ff70

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `85a52ad47b3ffcd7a156e021601b1687080f15327093211646d4878565cdc8fa`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
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

## abi_derived

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function, tools/reconstruction_tooling/abi_infer.py#tail_target=0x0096ffd0`

```json
{
  "abi": {
    "architecture": "x86-32",
    "calling_convention": "__thiscall",
    "receiver": false,
    "stack_cleanup_bytes": 4,
    "stack_cleanup_owner": "callee"
  },
  "abstained_because": [
    "no_terminal_ret: the only exit observed is a tail jump"
  ],
  "cleanup": {
    "bytes": 4,
    "confidence": "OBSERVED",
    "corroboration": "forwarded_from_tail_target",
    "evidence": "forwarded from the tail target 0x0096ffd0: ret 0x4",
    "side": "callee"
  },
  "completeness": "EMPTY",
  "conflicts": [],
  "content_sha256": "3454c90a0224bec621c16b4ce1591b860eb03e757f9034a3cd4a89f51128d5a7",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall"
    ],
    "confidence": "INFERRED",
    "corroboration": "forwarded_from_tail_target"
  },
  "cross_validation": {
    "agreement": false,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 4,
    "persisted": "no_information",
    "persisted_calling_convention": "thiscall adjustor thunk with one forwarded stack word"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0002"
      ],
      "claim": "no terminal return is present in the listing",
      "confidence": "UNKNOWN",
      "id": "C2"
    },
    {
      "based_on": [
        "obs-0002"
      ],
      "claim": "ECX is never read in any form, so there is no register receiver",
      "confidence": "OBSERVED",
      "id": "R2",
      "value": {
        "present": false
      }
    },
    {
      "based_on": [
        "obs-0002"
      ],
      "claim": "entry slot 0 is not written through a pointer",
      "confidence": "APPROXIMATION",
      "id": "S2",
      "value": {
        "present": false
      }
    },
    {
      "based_on": [
        "obs-0002"
      ],
      "claim": "this listing is a tail transfer: it inherits its caller's frame and never runs its own RET",
      "confidence": "UNKNOWN",
      "id": "T1",
      "value": {
        "form": "jmp"
      }
    },
    {
      "based_on": [
        "obs-0002"
      ],
      "claim": "calling convention is __thiscall, forwarded from the tail target 0x0096ffd0: this listing is a single ESP-neutral direct jump, inherits its caller's frame and never runs its own RET, so the two calls are one call (resolved from live listing for 0x0096ffd0)",
      "confidence": "INFERRED",
      "id": "T1-FWD",
      "value": "__thiscall"
    }
  ],
  "observations": [
    {
      "at": "0x0096ff70",
      "definite": true,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ECX,0xc",
      "reg": "ECX",
      "write_kind": "arith"
    },
    {
      "at": "0x0096ff73",
      "id": "obs-0002",
      "index": 1,
      "kind": "UNCOND_TRANSFER_OUT",
      "raw": "JMP 0x0096ffd0",
      "target": "0x0096ffd0"
    }
  ],
  "parse": {
    "declared_count": 2,
    "degraded": false,
    "esp_unresolved": false,
    "flow_complete": true,
    "frame": {
      "and_esp": null,
      "ebp_is_general_register": false,
      "fp": false,
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": false,
      "push_ebp_at": null,
      "sub": null
    },
    "layout": "json_instruction_list",
    "local_extent": 0,
    "unparsed": 0
  },
  "receiver": {
    "adjustor_delta": -12,
    "bounds_only": true,
    "confidence": "OBSERVED",
    "distinct_offsets": 0,
    "max_offset": null,
    "offsets": [],
    "present": false,
    "register": null,
    "shape": null,
    "written_through": 0
  },
  "return": {
    "aggregate_evidence": {
      "bulk_write": false
    },
    "confidence": "UNKNOWN",
    "register": null,
    "register_class": "unknown",
    "type": null,
    "void_possible": false
  },
  "schema": "openspore-abi-inference-1",
  "seh_or_cookie_frame": false,
  "sret": {
    "ambiguity": null,
    "basis": "entry slot 0 is not written through a pointer; DERIVED absence is weak, a struct filled through another alias would be missed",
    "candidates": null,
    "confidence": "APPROXIMATION",
    "eax_holds_slot0_at_ret": null,
    "hypothesis_confidence": null,
    "present": false,
    "slot": null,
    "this_interaction": null
  },
  "stack_arguments": {
    "confidence": "APPROXIMATION",
    "derived_slots": 0,
    "gaps": 0,
    "not_complete": false,
    "observed_slots": 0,
    "slots": [],
    "total_bytes": 0,
    "widths_ambiguous": false
  },
  "tail_call": {
    "after_frame_setup": false,
    "form": "jmp",
    "present": true,
    "target": "0x0096ffd0"
  },
  "target": {
    "address_available": true,
    "image_base": "0x00400000",
    "instructions": 2,
    "syntax": "intel",
    "va": "0x0096ff70"
  },
  "variadic": "UNKNOWN",
  "verdict": "ABI_UNKNOWN"
}
```

## callees_dependencies

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## callers_dependencies

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## contradictions

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## decompilation

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: ``

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 2,
  "instructions": [
    {
      "address": "0096ff70",
      "instruction": "SUB ECX,0xc"
    },
    {
      "address": "0096ff73",
      "instruction": "JMP 0x0096ffd0"
    }
  ]
}
```

## external_callees

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## function_identity

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "original_bytes": 10291,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"thiscall adjustor thunk with one forwarded stack word\",\n    \"hidden_receiver\": \"ECX GlideEffectBiStateSubobject* (a pointer 0x0C bytes ABOVE the object the tail target operates on)\",\n    \"ordinary_stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x08 (as observed inside the tail target 0x0096FFD0)\",\n        \"name\": \"deleting_flag\",\n        \"position\": 1,\n        \"type\": \"uint32\",\n        \"usage\": \"only bit 0 is read, by TEST byte [ESP+0x8],0x1 at 0x0096fff3\"\n      }\n    ],\n    \"ret_form\": \"RET 0x4 at 0x00970006, inside the tail target; the thunk itself has no RET\",\n    \"return_type\": \"void\",\n    \"stack_cleanup_bytes\": 4\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"shared_types:DATA,uint32\"\n      ],\n      \"package\": \"PKG-18-UI-SCRIPTING\",\n      \"score\": 6,\n      \"symbol\": \"FUN_005bf9d0\",\n      \"va\": \"0x005bf9d0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DATA,uint32\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE8\",\n      \"score\": 6,\n      \"symbol\": \"cell_mode_strategy_on_mouse_up_00e5c0f0\",\n      \"va\": \"0x00e5c0f0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DATA,uint32\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE8\",\n      \"score\": 6,\n      \"symbol\": \"cell_mode_strategy_on_mouse_down_00e6c860\",\n      \"va\": \"0x00e6c860\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DATA,uint32\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE8\",\n      \"score\": 6,\n      \"symbol\": \"cell_mode_strategy_on_mouse_wheel_00e7d660\",\n      \"va\": \"0x00e7d660\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01442584\"\n      ],\n      \"package\": \"PKG-16-SPOREPEDIA-ONLINE\",\n      \"score\": 4,\n      \"symbol\": \"Sporepedia_cSPAssetDataOTDB_HasName_raw_00641770\",\n      \"va\": \"0x00641770\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01442584\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"re_00951220\",\n      \"va\": \"0x00951220\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01442584\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"re_00951230\",\n      \"va\": \"0x00951230\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DATA\"\n      ],\n      \"package\": \"PKG-SKINNER-SAFE-WAVE10\",\n      \"score\": 3,\n      \"symbol\": \"skin_painter_job_brush_pass_005182f0\",\n      \"va\": \"0x005182f0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [\n    \"Ghidra's vtable detection never ran on this program, so the 0x01442584 label is an unverified pointer run and the destructor-slot reading stays a hypothesis.\",\n    \"The SDK placeholder signature for func88h (three int parameters) disagrees with the machine (one stack word); the true caller contract is runtime-gated.\"\n  ],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"utfwin-framework\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x0096ff73\",\n        \"direction\": \"out\",\n        \"other\": \"0x0096ffd0\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0312\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"CONFIRMED\",\n  \"globals\": [\n    \"global:PASS\"\n  ],\n  \"integration_status\": null,\n  \"name\": \"UTFWin::GlideEffect::func88h\",\n  \"normalized_symbol\": \"UTFWin::GlideEffect::func88h\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"runtime_gated_requires_explicit_gate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"queued\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"No runtime validation has been run; every claim here is static.\",\n      \"The concrete caller that dispatches through the vftable entry at 0x0144258c is unknown, so the values of the deleting flag in real use are unknown.\",\n      \"Whether the -0x0C receiver is a GlideEffect IBiStateEffect subobject or the analogous subobject of a sibling class (the same two-instruction shape is shared by UTFWin::InflateEffect::func88h at 0x0097e550 and by 0x0096ff80 with -0x04) is not settled by the static image.\"\n    ],\n    \"validated\": 0\n  },\n  \"runtime_gated\": true,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": null,\n  \"services\": [],\n  \"source\": {\n    \"decomp\": \".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__GlideEffect__func88h.c\",\n    \"file\": null,\n    \"files\": [\n      \".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__GlideEffect__func88h.c\",\n      \"reconstruction/staging/pkg-dfw-0096ff70/dfw_0096ff70.cpp\",\n      \"reconstruction/staging/pkg-dfw-0096ff70/dfw_0096ff70_model_test.cpp\",\n      \"reconstruction/staging/pkg-dfw-0096ff70/dfw_0096ff70_types.hpp\",\n      \"reconstruction/staging/pkg-utfwin-glideeffect-func88h/utfwin_glideeffect_func88h.cpp\",\n      \"reconstruction/s
[TRUNCATED]
```

## ghidra_function

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089`

```json
{
  "binary_available": true,
  "binary_sha256": "25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e",
  "body_end": "0096ff77",
  "body_span_bytes": 8,
  "body_start": "0096ff70",
  "callees": [
    "FUN_0096ffd0"
  ],
  "callers": [],
  "classification": "stub",
  "dispatch": null,
  "entry_point": "0096ff70",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "UTFWin::GlideEffect::func88h",
  "namespace": "UTFWin",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 4,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "GlideEffect *"
    },
    {
      "name": "param_2",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "int"
    },
    {
      "name": "param_3",
      "ordinal": 2,
      "storage": "Stack[0xc]:4",
      "type": "int"
    },
    {
      "name": "param_4",
      "ordinal": 3,
      "storage": "Stack[0x10]:4",
      "type": "int"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "void",
  "return_type_resolved": true,
  "rva": "0x56ff70",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "void UTFWin::GlideEffect::func88h(GlideEffect * this, int param_2, int param_3, int param_4)",
  "size_bytes": 8,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x0096ff70",
  "vtables": {
    "referenced_by_vtables": [
      "0x01442584"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "0144258c"
    }
  ]
}
```

## globals

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "global:PASS"
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
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

## runtime

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## runtime_metadata

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "blocking_reason": null,
  "gates": [
    "No runtime validation has been run; every claim here is static.",
    "The concrete caller that dispatches through the vftable entry at 0x0144258c is unknown, so the values of the deleting flag in real use are unknown.",
    "Whether the -0x0C receiver is a GlideEffect IBiStateEffect subobject or the analogous subobject of a sibling class (the same two-instruction shape is shared by UTFWin::InflateEffect::func88h at 0x0097e550 and by 0x0096ff80 with -0x04) is not settled by the static image."
  ],
  "validated": 0
}
```

## semantic_hypotheses

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

## status

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "runtime_gated": true,
  "runtime_validated": 0,
  "status": "queued"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "DATA",
  "GlideEffect (UTFWin::GlideEffect, SDK SIZE 0x70, 32-bit)",
  "GlideEffectVTableRun (pointer run based at 0x01442584, 4 transcribed slots)",
  "OpaqueVtable (4 opaque slots, used for all four documented vptr words)",
  "uint32",
  "void"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x01442584"
]
```

## Conflicts

```json
[]
```
