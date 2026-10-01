# Evidence 0x00985ce0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `49bcdc5435689b5de6c33728d16ae78bc18d65c4ef6ac7a12505d5d27409213e`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
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
  "content_sha256": "df8be83125e1929f63d9b98a8adb086d442171a2b88723bf23658fe280b92c62",
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
    "ghidra_parameter_count": 2,
    "persisted": "no_information",
    "persisted_calling_convention": "__thiscall (no stack arguments, no cleanup)"
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
      "claim": "calling convention is __thiscall: 0x00985ce0 is slot 5 of the vptr-backed vftable at 0x01445060, so it is a virtual member of some class; the callee pops nothing and no stack word is read as an argument, so the receiver is in a register, and ECX is the only one that carries one",
      "confidence": "INFERRED",
      "id": "V1-VFT",
      "value": {
        "cleanup_side": "caller",
        "membership_count": 1,
        "receiver_provenance": "vftable_slot",
        "receiver_register": "ECX",
        "slot_index": 5,
        "table": "0x01445060"
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
      "at": "0x00985ce0",
      "definite": true,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,0x4f063bb3",
      "reg": "EAX",
      "write_kind": "imm"
    },
    {
      "at": "0x00985ce5",
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
    "va": "0x00985ce0"
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
      "address": "00985ce0",
      "instruction": "MOV EAX,0x4f063bb3"
    },
    {
      "address": "00985ce5",
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
  "original_bytes": 6185,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall (no stack arguments, no cleanup)\",\n    \"hidden_this_register\": \"ECX (read but unused)\",\n    \"ordinary_stack_arguments\": [],\n    \"ret_form\": \"plain RET\",\n    \"return_register\": \"EAX\",\n    \"return_type\": \"uint32_t\",\n    \"stack_cleanup_bytes\": 0\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-UTFWIN-DRAWABLE-WAVE9\",\n      \"score\": 14,\n      \"symbol\": \"re_009849a0\",\n      \"va\": \"0x009849a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-UTFWIN-DRAWABLE-WAVE9\",\n      \"score\": 14,\n      \"symbol\": \"re_00987ae0\",\n      \"va\": \"0x00987ae0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-UTFWIN-DRAWABLE-WAVE9\",\n      \"score\": 8,\n      \"symbol\": \"re_00b267d0\",\n      \"va\": \"0x00b267d0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01445060\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"re_00951230\",\n      \"va\": \"0x00951230\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-ARGSCRIPT-WAVE9\",\n      \"score\": 2,\n      \"symbol\": \"pkg_argscript_get_current_scope_00d1dcd0\",\n      \"va\": \"0x00d1dcd0\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Static x86-32 mechanics, register/stack argument contract, stack cleanup width, RET form, offsets, constants, strides, and slot indices were read from the live Ghidra disassembly; imported signatures are candidate labels only. Concrete vtable and port owners, runtime values, and ownership remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_semantic_abi_and_lifecycle_review\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"ImageDrawable\",\n  \"cluster\": \"utfwin-framework\",\n  \"confidence\": 0.97,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0329\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"OBSERVED\",\n  \"globals\": [],\n  \"integration_status\": \"integrated\",\n  \"name\": \"UTFWin::ImageDrawable::SetAlignmentHorizontal\",\n  \"normalized_symbol\": \"re_00985ce0\",\n  \"observed_mechanics\": [\n    \"MOV EAX,0x4f063bb3.\",\n    \"RET.\"\n  ],\n  \"ownership\": {\n    \"claimability\": \"do_not_claim\",\n    \"handoff_packages\": [\n      \"PKG-UTFWIN-DRAWABLE-WAVE9\"\n    ],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": \"PKG-UTFWIN-DRAWABLE-WAVE9\",\n    \"queue_state\": \"queued\"\n  },\n  \"package\": \"PKG-UTFWIN-DRAWABLE-WAVE9\",\n  \"reconstructed\": true,\n  \"review_status\": \"approved\",\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"No original-process invocation or indirect-caller trace was captured.\",\n      \"The constant 0x4f063bb3 is not decoded; whether it is a real alignment value, a sentinel, or a placeholder is unresolved.\",\n      \"The imported name SetAlignmentHorizontal is a candidate label only; the body performs no alignment write.\",\n      \"gate-utfwin-stub-constant-decoding\"\n    ],\n    \"validated\": 0\n  },\n  \"runtime_gated\": true,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": \"static_constant_return_stub_with_no_state_effect_observed\",\n  \"services\": [],\n  \"source\": {\n    \"decomp\": \".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__ImageDrawable__SetAlignmentHorizontal.c\",\n    \"file\": \"src/reconstruction/pkg_utfwin_drawable_wave9/utfwin_drawable_wave9.cpp\",\n    \"files\": [\n      \".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__ImageDrawable__SetAlignmentHorizontal.c\",\n      \"src/reconstruction/pkg_utfwin_drawable_wave9\",\n      \"src/reconstruction/pkg_utfwin_drawable_wave9/utfwin_drawable_wave9.cpp\",\n      \"src/reconstruction/pkg_utfwin_drawable_wave9/utfwin_drawable_wave9.hpp\",\n      \"src/reconstruction/pkg_utfwin_drawable_wave9/utfwin_drawable_wave9_model_test.cpp\"\n    ],\n    \"handoffs\": [\n      \"reconstruction/integrated/batch-2026-09-25-wave9-safe-core/handoff.json\"\n    ],\n    \"metadata\": [\n      \"reconstruction/metadata/pkg-utfwin-drawable-wave9/00985ce0.json\"\n    ],\n    \"provenance\": [\n      \"ghidra:disassemble_function:0x00985ce0\",\n      \"ghidra:get_function_by_address:0x00985ce0\",\n      \"ghidra:get_function_callees:0x00985ce0\",\n      \"ghidra:get_function_callers:0x00985ce0\",\n      \"reconstruction/integrated/batch-2026-09-25-wave9-safe-core/handoff.json\",\n      \"reconstruction/metadata/pkg-utfwin-drawable-wave9/00985ce0.json\"\n    ]\n  },\n  \"status\": \"reconstructed\",\n  \"subsystem\": \"UTFWin.Drawable\",\n  \"triage\": {\n    \"category\": \"ENGINE_INTERFACE\",\n    \"cluster\": \"utfwin-framework\",\n    \"db_triage_status\": \"QUEUED\",\n    \"decomp_path\": \".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__ImageDrawable__SetAlignmentHorizontal.c\",\n    \"dependencies\": [\n      \"app-lifecycle\",\n      \"resource-io\"\n    ],\n    \"evidence\": \"CONFIRMED\",\n    \"kg_node_id\": \"fun:00985ce0\",\n    \"name\": \"UTFWin::ImageDrawable::SetAlignmentHorizontal\",\n    \"priority\": \"P0\",\n   
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
  "body_end": "00985ce5",
  "body_span_bytes": 6,
  "body_start": "00985ce0",
  "callees": [],
  "callers": [],
  "classification": "stub",
  "dispatch": null,
  "entry_point": "00985ce0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "UTFWin::ImageDrawable::SetAlignmentHorizontal",
  "namespace": "UTFWin",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 2,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "IImageDrawable *"
    },
    {
      "name": "alignment",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "AlignmentH"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "void",
  "return_type_resolved": true,
  "rva": "0x585ce0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "void UTFWin::ImageDrawable::SetAlignmentHorizontal(IImageDrawable * this, AlignmentH alignment)",
  "size_bytes": 6,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00985ce0",
  "vtables": {
    "referenced_by_vtables": [
      "0x01445060"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "01445074"
    }
  ]
}
```

## globals

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
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
    "No original-process invocation or indirect-caller trace was captured.",
    "The constant 0x4f063bb3 is not decoded; whether it is a real alignment value, a sentinel, or a placeholder is unresolved.",
    "The imported name SetAlignmentHorizontal is a candidate label only; the body performs no alignment write.",
    "gate-utfwin-stub-constant-decoding"
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
  "status": "reconstructed"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "ImageDrawable",
  "uint32_t"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x01445060"
]
```

## Conflicts

```json
[]
```
