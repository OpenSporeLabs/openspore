# Evidence 0x00980c50

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `488b8329a85997cd80d79a0d2d4701e1d424535feec10d344df159390c6d31ce`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
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

## abi_derived

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function, tools/reconstruction_tooling/vftables.py@25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e`

```json
{
  "abi": {
    "architecture": "x86-32",
    "calling_convention": "__thiscall",
    "receiver": false,
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "3249c9fc2b71e75192e32889e13d5864e136319e3908c378ccd4c0832450c321",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall",
      "__fastcall"
    ],
    "confidence": "INFERRED",
    "corroboration": "not_available"
  },
  "cross_validation": {
    "agreement": false,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 4,
    "persisted": "no_information",
    "persisted_calling_convention": "['__thiscall (persisted record; derived record abstained)', 'thiscall receiver in ECX (per the SDK method header) with caller stack cleanup; the receiver and every argument are ignored']"
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
      "claim": "the caller cleans up the stack: a bare RET is compatible with caller cleanup and, for a zero-parameter __stdcall, with zero bytes of callee cleanup",
      "confidence": "INFERRED",
      "id": "C5",
      "value": {
        "bytes": 0,
        "side": "caller"
      }
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
      "claim": "calling convention is __thiscall: 0x00980c50 is slot 20 of the vptr-backed vftable at 0x01444314, so it is a virtual member of some class; the callee pops nothing and no stack word is read as an argument, so the receiver is in a register, and ECX is the only one that carries one",
      "confidence": "INFERRED",
      "id": "V1-VFT",
      "value": {
        "cleanup_side": "caller",
        "membership_count": 1,
        "receiver_provenance": "vftable_slot",
        "receiver_register": "ECX",
        "slot_index": 20,
        "table": "0x01444314"
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
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0002"
      ],
      "claim": "the last value written to EAX classifies as aggregate_unknown",
      "confidence": "INFERRED",
      "id": "RT2",
      "value": {
        "register_class": "aggregate_unknown"
      }
    }
  ],
  "observations": [
    {
      "at": "0x00980c50",
      "definite": true,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,0xcf2b2ad5",
      "reg": "EAX",
      "write_kind": "imm"
    },
    {
      "at": "0x00980c55",
      "form": "RET",
      "id": "obs-0002",
      "imm": null,
      "index": 1,
      "kind": "RET",
      "raw": "RET"
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
    "bounds_only": true,
    "confidence": "OBSERVED",
    "distinct_offsets": 0,
    "max_offset": null,
    "offsets": [],
    "present": false,
    "provenance": "vftable_slot",
    "register": "ECX",
    "shape": null,
    "written_through": 0
  },
  "return": {
    "aggregate_evidence": {
      "bulk_write": false
    },
    "confidence": "INFERRED",
    "register": "EAX",
    "register_class": "aggregate_unknown",
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
    "form": null,
    "present": false,
    "target": null
  },
  "target": {
    "address_available": true,
    "image_base": "0x00400000",
    "instructions": 2,
    "syntax": "intel",
    "va": "0x00980c50"
  },
  "variadic": "UNKNOWN",
  "verdict": "ABI_INFERRED"
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
      "address": "00980c50",
      "instruction": "MOV EAX,0xcf2b2ad5"
    },
    {
      "address": "00980c55",
      "instruction": "RET"
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
  "original_bytes": 12138,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": [\n      \"__thiscall (persisted record; derived record abstained)\",\n      \"thiscall receiver in ECX (per the SDK method header) with caller stack cleanup; the receiver and every argument are ignored\"\n    ],\n    \"hidden_receiver\": \"ECX, typed as the RotateEffect receiver by the SDK method header. The frame never reads ECX, so the receiver cannot influence the result and no subobject offset can be recovered from this address.\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_arguments\": [\n      \"{'entry_offset': 'ESP+0x08 on entry', 'name': 'param_2', 'position': 1, 'type': 'uint32', 'usage': 'never read; the frame executes no memory load at all'}\",\n      \"{'entry_offset': 'ESP+0x0C on entry', 'name': 'param_3', 'position': 2, 'type': 'uint32', 'usage': 'never read'}\",\n      \"{'entry_offset': 'ESP+0x10 on entry', 'name': 'param_4', 'position': 3, 'type': 'uint32', 'usage': 'never read'}\"\n    ],\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": [\n      \"RET\",\n      \"bare RET at 0x00980c55; the caller pops, which the staged model test exercises by pushing three words and removing them with 'addl $12, %esp' after the call\"\n    ],\n    \"return_register\": \"EAX\",\n    \"return_type\": \"std::uint32_t\",\n    \"saved_registers\": [],\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"RET\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"shared_types:DATA,uint32\"\n      ],\n      \"package\": \"PKG-18-UI-SCRIPTING\",\n      \"score\": 6,\n      \"symbol\": \"FUN_005bf9d0\",\n      \"va\": \"0x005bf9d0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DATA,uint32\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE8\",\n      \"score\": 6,\n      \"symbol\": \"cell_mode_strategy_on_mouse_up_00e5c0f0\",\n      \"va\": \"0x00e5c0f0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DATA,uint32\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE8\",\n      \"score\": 6,\n      \"symbol\": \"cell_mode_strategy_on_mouse_down_00e6c860\",\n      \"va\": \"0x00e6c860\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DATA,uint32\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE8\",\n      \"score\": 6,\n      \"symbol\": \"cell_mode_strategy_on_mouse_wheel_00e7d660\",\n      \"va\": \"0x00e7d660\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01444314\"\n      ],\n      \"package\": \"PKG-16-SPOREPEDIA-ONLINE\",\n      \"score\": 4,\n      \"symbol\": \"Sporepedia_cSPAssetDataOTDB_HasName_raw_00641770\",\n      \"va\": \"0x00641770\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01444314,vtable:0x01444364\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"re_00951220\",\n      \"va\": \"0x00951220\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01444314,vtable:0x01444364\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"re_00951230\",\n      \"va\": \"0x00951230\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DATA\"\n      ],\n      \"package\": \"PKG-SKINNER-SAFE-WAVE10\",\n      \"score\": 3,\n      \"symbol\": \"skin_painter_job_brush_pass_005182f0\",\n      \"va\": \"0x005182f0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [\n    \"0xCF2B2AD5 is undocumented in the SDK, so no semantic name for the returned word is recoverable from the available evidence.\",\n    \"Ghidra's vtable detection never ran on this program, so 'vtable:0x01444364' is an unverified pointer run and every slot attribution derived from it is a heuristic.\",\n    \"The SDK's ObjectTYPE enum is not injective (0xEF2B293B is shared by IGlideEffect, IPerspectiveEffect and IRotateEffect), so no constant in this family can identify a class on its own.\"\n  ],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"utfwin-framework\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0326\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"CONFIRMED\",\n  \"globals\": [\n    \"global:PASS\"\n  ],\n  \"integration_status\": null,\n  \"name\": \"UTFWin::RotateEffect::func88h\",\n  \"normalized_symbol\": \"UTFWin::RotateEffect::func88h\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"runtime_gated_requires_explicit_gate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"queued\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"No runtime validation has been run; every claim here is static.\",\n      \"The dispatching caller of the run's slot +0x00 is unknown, so the circumstances under which this getter is invoked -- and whether its result is compared against anything -- are unknown.\",\n      \"Whether slot +0x00 of the run is genuinely a getter of the word the block at 0x00980c80 stores is unproven; the adjacency is a byte-level argument only.\"\n    ],\n    \"validated\": 0\n  },\n  \"runtime_gated\": t
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
  "body_end": "00980c55",
  "body_span_bytes": 6,
  "body_start": "00980c50",
  "callees": [],
  "callers": [],
  "classification": "stub",
  "dispatch": null,
  "entry_point": "00980c50",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "UTFWin::RotateEffect::func88h",
  "namespace": "UTFWin",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 4,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "RotateEffect *"
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
  "rva": "0x580c50",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "void UTFWin::RotateEffect::func88h(RotateEffect * this, int param_2, int param_3, int param_4)",
  "size_bytes": 6,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00980c50",
  "vtables": {
    "referenced_by_vtables": [
      "0x01444314",
      "0x01444364"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "01444364"
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
    "The dispatching caller of the run's slot +0x00 is unknown, so the circumstances under which this getter is invoked -- and whether its result is compared against anything -- are unknown.",
    "Whether slot +0x00 of the run is genuinely a getter of the word the block at 0x00980c80 stores is unproven; the adjacency is a byte-level argument only."
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
  "Opaque = std::uint32_t (opaque 32-bit word)",
  "RotateEffectTokenWord (the receiver's leading 32-bit word, the only word any observed code touches)",
  "RotateEffectVTableRun (pointer run based at 0x01444364, 12 transcribed slots)",
  "std::uint32_t",
  "uint32"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x01444314",
  "vtable:0x01444364"
]
```

## Conflicts

```json
[]
```
