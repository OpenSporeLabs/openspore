# Evidence 0x00962830

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `86d2ec512fd9a5f60862f79abb15d895f8d50adc479bf11edb1e3f0442481c78`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "x86-32 thiscall with first explicit object pointer in ECX and caller cleanup",
  "return_semantics": "delegated pointer in EAX",
  "return_type": "Opaque*",
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "caller"
}
```

## abi_derived

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function, tools/reconstruction_tooling/abi_infer.py#tail_target=0x00962bc0`

```json
{
  "abi": {
    "architecture": "x86-32",
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
    "evidence": "forwarded from the tail target 0x00962bc0: ret 0x4",
    "side": "callee"
  },
  "completeness": "EMPTY",
  "conflicts": [],
  "content_sha256": "76f34d5943716709df6b2b2736e70b2a93057790b78e51f3358d2fbdfb7283b5",
  "conventions": {
    "ambiguities": [
      "tail_call"
    ],
    "calling_convention": null,
    "candidate_conventions": [
      "__cdecl",
      "__stdcall",
      "__thiscall",
      "__fastcall"
    ],
    "confidence": "UNKNOWN",
    "corroboration": "not_available"
  },
  "cross_validation": {
    "agreement": false,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 2,
    "persisted": "no_information",
    "persisted_calling_convention": "x86-32 thiscall with first explicit object pointer in ECX and caller cleanup"
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
      "claim": "the stack cleanup is callee with 4 byte(s), forwarded from the tail target 0x00962bc0; the target's own calling convention is not decided, so none is forwarded (resolved from live listing for 0x00962bc0)",
      "confidence": "OBSERVED",
      "id": "T1-FWD",
      "value": {
        "target": "0x00962bc0",
        "target_calling_convention": null,
        "target_cleanup_side": "callee",
        "target_source": "live listing for 0x00962bc0",
        "target_stack_bytes": 4,
        "this_adjustor_delta": -4
      }
    }
  ],
  "observations": [
    {
      "at": "0x00962830",
      "definite": true,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ECX,0x4",
      "reg": "ECX",
      "write_kind": "arith"
    },
    {
      "at": "0x00962833",
      "id": "obs-0002",
      "index": 1,
      "kind": "UNCOND_TRANSFER_OUT",
      "raw": "JMP 0x00962bc0",
      "target": "0x00962bc0"
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
    "adjustor_delta": -4,
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
    "target": "0x00962bc0"
  },
  "target": {
    "address_available": true,
    "image_base": "0x00400000",
    "instructions": 2,
    "syntax": "intel",
    "va": "0x00962830"
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
      "address": "00962830",
      "instruction": "SUB ECX,0x4"
    },
    {
      "address": "00962833",
      "instruction": "JMP 0x00962bc0"
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
  "original_bytes": 8856,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"x86-32 thiscall with first explicit object pointer in ECX and caller cleanup\",\n    \"return_semantics\": \"delegated pointer in EAX\",\n    \"return_type\": \"Opaque*\",\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"caller\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutManager,openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutWindow,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueCastObject,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueImageCarrier\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-UTFWIN-LAYOUT-WAVE6\",\n      \"score\": 25,\n      \"symbol\": \"pkg_utfwin_layout_wave6_00967e80\",\n      \"va\": \"0x00967e80\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:Opaque*,openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutManager,openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutWindow,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueCastObject\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-UTFWIN-LAYOUT-WAVE6\",\n      \"score\": 25,\n      \"symbol\": \"pkg_utfwin_layout_wave6_0096feb0\",\n      \"va\": \"0x0096feb0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutManager,openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutWindow,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueCastObject,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueImageCarrier\"\n      ],\n      \"package\": \"PKG-UTFWIN-LAYOUT-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"pkg_utfwin_layout_wave6_009601e0\",\n      \"va\": \"0x009601e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutManager,openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutWindow,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueCastObject,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueImageCarrier\"\n      ],\n      \"package\": \"PKG-UTFWIN-LAYOUT-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"pkg_utfwin_layout_wave6_00961260\",\n      \"va\": \"0x00961260\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutManager,openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutWindow,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueCastObject,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueImageCarrier\"\n      ],\n      \"package\": \"PKG-UTFWIN-LAYOUT-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"pkg_utfwin_layout_wave6_00961300\",\n      \"va\": \"0x00961300\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:Opaque*,openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutManager,openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutWindow,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueCastObject\"\n      ],\n      \"package\": \"PKG-UTFWIN-LAYOUT-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"pkg_utfwin_layout_wave6_009646d0\",\n      \"va\": \"0x009646d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutManager,openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutWindow,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueCastObject,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueImageCarrier\"\n      ],\n      \"package\": \"PKG-UTFWIN-LAYOUT-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"pkg_utfwin_layout_wave6_00967e20\",\n      \"va\": \"0x00967e20\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:Opaque*,openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutManager,openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutWindow,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueCastObject\"\n      ],\n      \"package\": \"PKG-UTFWIN-LAYOUT-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"pkg_utfwin_layout_wave6_00967e60\",\n      \"va\": \"0x00967e60\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Reviewed static mechanics and x86-32 ABI are preserved; opaque runtime ports and ownership remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": null,\n  \"cluster\": \"utfwin-framework\",\n  \"confidence\": 0.9,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00962833\",\n        \"direction\": \"out\",\n        \"other\": \"0x00962bc0\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0303\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"SUPPORTED\",\n  \"globals\": [],\n  \"integration_status\": \"integrated\",\n  \"name\": \"UTFWin::Window::RemoveWind
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
  "body_end": "00962837",
  "body_span_bytes": 8,
  "body_start": "00962830",
  "callees": [
    "FUN_00962bc0"
  ],
  "callers": [],
  "classification": "stub",
  "dispatch": null,
  "entry_point": "00962830",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "UTFWin::Window::RemoveWindow",
  "namespace": "UTFWin",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 2,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "IWindow *"
    },
    {
      "name": "pWindow",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "IWindow *"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "void",
  "return_type_resolved": true,
  "rva": "0x562830",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "void UTFWin::Window::RemoveWindow(IWindow * this, IWindow * pWindow)",
  "size_bytes": 8,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00962830",
  "vtables": {
    "referenced_by_vtables": [
      "0x014431f8"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "01443200"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__Window__RemoveWindow.c",
  "file": "src/reconstruction/pkg_utfwin_layout_wave6/utfwin_layout_wave6.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__Window__RemoveWindow.c",
    "src/reconstruction/pkg_utfwin_layout_wave6/utfwin_layout_wave6.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-utfwin-layout-wave6/00962830.json"
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
    "adjusted object layout and delegated return ownership remain gated",
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
  "Opaque*",
  "openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutManager",
  "openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutWindow",
  "openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueCastObject",
  "openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueImageCarrier",
  "openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueIndexCarrier"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x014431f8"
]
```

## Conflicts

```json
[]
```
