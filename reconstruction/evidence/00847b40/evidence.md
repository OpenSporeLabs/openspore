# Evidence 0x00847b40

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `97e28dee779f7ffde47667b9df97e854134e2949a26954e64e42d9ade6844c5b`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "x86-32 thiscall with first explicit canvas receiver in ECX and caller cleanup",
  "return_semantics": "unsigned 16-bit word in AX",
  "return_type": "std::uint16_t",
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller"
}
```

## abi_derived

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "abi": {
    "architecture": "x86-32",
    "calling_convention": "__thiscall",
    "hidden_this": true,
    "hidden_this_register": "ECX",
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "pointer_like_in_EAX",
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
  "content_sha256": "9100e228be82d7da1dbb7f4f08955e76830aacba659db53acee43aebf936b3d8",
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
    "ghidra_parameter_count": 1,
    "persisted": "no_information",
    "persisted_calling_convention": "x86-32 thiscall with first explicit canvas receiver in ECX and caller cleanup"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0003"
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
        "obs-0001",
        "obs-0002"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          112
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0002",
        "obs-0003"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0003"
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
        "obs-0003"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0003"
      ],
      "claim": "the last value written to EAX classifies as pointer_like",
      "confidence": "INFERRED",
      "id": "RT2",
      "value": {
        "register_class": "pointer_like"
      }
    }
  ],
  "observations": [
    {
      "at": "0x00847b40",
      "count": 1,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV AX,word ptr [ECX + 0x70]",
      "reg": "ECX"
    },
    {
      "at": "0x00847b40",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV AX,word ptr [ECX + 0x70]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00847b44",
      "form": "RET",
      "id": "obs-0003",
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
    "confidence": "INFERRED",
    "distinct_offsets": 1,
    "max_offset": 112,
    "offsets": [
      112
    ],
    "present": true,
    "register": "ECX",
    "shape": "R-DIRECT",
    "written_through": 0
  },
  "return": {
    "aggregate_evidence": {
      "bulk_write": false
    },
    "confidence": "INFERRED",
    "register": "EAX",
    "register_class": "pointer_like",
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
    "va": "0x00847b40"
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
      "address": "00847b40",
      "instruction": "MOV AX,word ptr [ECX + 0x70]"
    },
    {
      "address": "00847b44",
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
  "original_bytes": 7508,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"x86-32 thiscall with first explicit canvas receiver in ECX and caller cleanup\",\n    \"return_semantics\": \"unsigned 16-bit word in AX\",\n    \"return_type\": \"std::uint16_t\",\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_app_canvas_wave6::OpaqueCanvas,openspore::reconstruction::pkg_app_canvas_wave6::OpaqueCanvasSystems,openspore::reconstruction::pkg_app_canvas_wave6::OpaqueDispatchRecord,openspore::reconstruction::pkg_app_canvas_wave6::OpaqueMessageManager\",\n        \"shared_vtable:vtable:0x0141ca70\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-CANVAS-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"app_canvas_00847a40\",\n      \"va\": \"0x00847a40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_app_canvas_wave6::OpaqueCanvas,openspore::reconstruction::pkg_app_canvas_wave6::OpaqueCanvasSystems,openspore::reconstruction::pkg_app_canvas_wave6::OpaqueDispatchRecord,openspore::reconstruction::pkg_app_canvas_wave6::OpaqueMessageManager\",\n        \"shared_vtable:vtable:0x0141ca70,vtable:0x0141cab8\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-CANVAS-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"app_canvas_00847a90\",\n      \"va\": \"0x00847a90\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_app_canvas_wave6::OpaqueCanvas,openspore::reconstruction::pkg_app_canvas_wave6::OpaqueCanvasSystems,openspore::reconstruction::pkg_app_canvas_wave6::OpaqueDispatchRecord,openspore::reconstruction::pkg_app_canvas_wave6::OpaqueMessageManager\",\n        \"shared_vtable:vtable:0x0141ca70,vtable:0x0141cab8\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-CANVAS-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"app_canvas_00847b10\",\n      \"va\": \"0x00847b10\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_app_canvas_wave6::OpaqueCanvas,openspore::reconstruction::pkg_app_canvas_wave6::OpaqueCanvasSystems,openspore::reconstruction::pkg_app_canvas_wave6::OpaqueDispatchRecord,openspore::reconstruction::pkg_app_canvas_wave6::OpaqueMessageManager\",\n        \"shared_vtable:vtable:0x0141ca70\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-CANVAS-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"app_canvas_00848020\",\n      \"va\": \"0x00848020\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_app_canvas_wave6::OpaqueCanvas,openspore::reconstruction::pkg_app_canvas_wave6::OpaqueCanvasSystems,openspore::reconstruction::pkg_app_canvas_wave6::OpaqueDispatchRecord,openspore::reconstruction::pkg_app_canvas_wave6::OpaqueMessageManager\",\n        \"shared_vtable:vtable:0x0141ca70\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-CANVAS-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"app_canvas_00848100\",\n      \"va\": \"0x00848100\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Reviewed static mechanics and x86-32 ABI are preserved; opaque runtime ports and ownership remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": null,\n  \"cluster\": \"app-lifecycle\",\n  \"confidence\": 0.9,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0267\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"SUPPORTED\",\n  \"globals\": [],\n  \"integration_status\": \"integrated\",\n  \"name\": \"App::Canvas::IsActive\",\n  \"normalized_symbol\": \"app_canvas_00847b40\",\n  \"observed_mechanics\": [\n    \"Loads and returns canvas+0x70 without mutation.\"\n  ],\n  \"ownership\": {\n    \"claimability\": \"do_not_claim\",\n    \"handoff_packages\": [\n      \"PKG-APP-CANVAS-WAVE6\"\n    ],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": \"PKG-APP-CANVAS-WAVE6\",\n    \"queue_state\": \"queued\"\n  },\n  \"package\": \"PKG-APP-CANVAS-WAVE6\",\n  \"reconstructed\": true,\n  \"review_status\": \"approved\",\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"class/window word semantics and runtime owner remain gated\",\n      \"runtime validation not run\"\n    ],\n    \"validated\": 0\n  },\n  \"runtime_gated\": true,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": \"static_reconstruction_triage_runtime_gated\",\n  \"services\": [],\n  \"source\": {\n    \"decomp\": \".spore-analysis/ghidra-exports/decompiled_sdk/App__Canvas__IsActive.c\",\n    \"file\": \"src/reconstruction/pkg_app_canvas_wave6/app_canvas_wave6.cpp\",\n    \"files\": [\n      \".spore-analysis/ghidra-exports/decompiled_sdk/App__Canvas__IsActive.c\",\n      \"src/reconstruction/pkg_app_canvas_wave6/app_canvas_wave6.cpp\"\n    ],\n    \"handoffs\": [\n      \"reconstruction/integrated/batch-2
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
  "body_end": "00847b44",
  "body_span_bytes": 5,
  "body_start": "00847b40",
  "callees": [],
  "callers": [],
  "classification": "stub",
  "dispatch": null,
  "entry_point": "00847b40",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "App::Canvas::IsActive",
  "namespace": "App",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 1,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "Canvas *"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "bool",
  "return_type_resolved": true,
  "rva": "0x447b40",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "bool App::Canvas::IsActive(Canvas * this)",
  "size_bytes": 5,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00847b40",
  "vtables": {
    "referenced_by_vtables": [
      "0x0141ca70",
      "0x0141cab8",
      "0x0141cb08"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "0141cb08"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__Canvas__IsActive.c",
  "file": "src/reconstruction/pkg_app_canvas_wave6/app_canvas_wave6.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__Canvas__IsActive.c",
    "src/reconstruction/pkg_app_canvas_wave6/app_canvas_wave6.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-app-canvas-wave6/00847b40.json"
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
    "class/window word semantics and runtime owner remain gated",
    "runtime validation not run"
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
  "openspore::reconstruction::pkg_app_canvas_wave6::OpaqueCanvas",
  "openspore::reconstruction::pkg_app_canvas_wave6::OpaqueCanvasSystems",
  "openspore::reconstruction::pkg_app_canvas_wave6::OpaqueDispatchRecord",
  "openspore::reconstruction::pkg_app_canvas_wave6::OpaqueMessageManager",
  "openspore::reconstruction::pkg_app_canvas_wave6::OpaqueOwnerManager",
  "std::uint16_t"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x0141ca70",
  "vtable:0x0141cab8",
  "vtable:0x0141cb08"
]
```

## Conflicts

```json
[]
```
