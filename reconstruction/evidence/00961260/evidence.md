# Evidence 0x00961260

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `71ef016b86442683bc34f767d24b61b8a989ad776ac81a42f9febfafd5a51a54`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "x86-32 thiscall with first explicit cast receiver in ECX and caller cleanup",
  "return_semantics": "void",
  "return_type": "void",
  "stack_cleanup_bytes": 4,
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
    "ordinary_stack_argument_slots": [
      "entry_ESP+0x4"
    ],
    "ordinary_stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x4",
    "return_register": "EAX",
    "return_semantics": "pointer_like_in_EAX",
    "stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "stack_cleanup_bytes": 4,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x4"
  },
  "abstained_because": [
    "sret_vs_out_param: entry slot 0 is written through a pointer"
  ],
  "cleanup": {
    "bytes": 4,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x4",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "297909cfed66bba7b2d19ebf8f984a2e38015b70c6d37678ee0543b45969edf8",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall"
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
    "persisted_calling_convention": "x86-32 thiscall with first explicit cast receiver in ECX and caller cleanup"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0007"
      ],
      "claim": "the callee pops 4 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 4,
        "side": "callee"
      }
    },
    {
      "based_on": [
        "obs-0004"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "INFERRED",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 1,
        "total_bytes": 4
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0002",
        "obs-0006"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          56
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0002",
        "obs-0006",
        "obs-0007"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0004"
      ],
      "claim": "a hidden struct-return pointer is a hypothesis only: entry slot 0 is written through a pointer",
      "confidence": "INFERRED",
      "id": "S1",
      "value": {
        "ambiguity": "sret_vs_out_param",
        "present": null,
        "slot": 4
      }
    },
    {
      "based_on": [
        "obs-0007"
      ],
      "claim": "in MSVC x86 a hidden struct-return pointer is always stack slot 0 while this is in ECX, so the two never contend",
      "confidence": "APPROXIMATION",
      "id": "S3",
      "value": {
        "ordering": "not_applicable"
      }
    },
    {
      "based_on": [
        "obs-0007"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0007"
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
      "at": "0x00961260",
      "count": 2,
      "first_use": 0,
      "first_write_index": 0,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV ECX,dword ptr [ECX + 0x38]",
      "reg": "ECX"
    },
    {
      "at": "0x00961260",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [ECX + 0x38]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00961263",
      "count": 1,
      "first_use": 1,
      "first_write_index": null,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "ESP"
    },
    {
      "at": "0x00961263",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0004",
      "index": 1,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00961263",
      "definite": true,
      "id": "obs-0005",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00961267",
      "count": 1,
      "first_use": 2,
      "first_write_index": 1,
      "id": "obs-0006",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV dword ptr [EAX],ECX",
      "reg": "EAX"
    },
    {
      "at": "0x00961269",
      "form": "RET 0x4",
      "id": "obs-0007",
      "imm": 4,
      "index": 3,
      "kind": "RET",
      "raw": "RET 0x4"
    }
  ],
  "parse": {
    "declared_count": 4,
[TRUNCATED]
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
  "count": 4,
  "instructions": [
    {
      "address": "00961260",
      "instruction": "MOV ECX,dword ptr [ECX + 0x38]"
    },
    {
      "address": "00961263",
      "instruction": "MOV EAX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "00961267",
      "instruction": "MOV dword ptr [EAX],ECX"
    },
    {
      "address": "00961269",
      "instruction": "RET 0x4"
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
  "original_bytes": 10698,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"x86-32 thiscall with first explicit cast receiver in ECX and caller cleanup\",\n    \"return_semantics\": \"void\",\n    \"return_type\": \"void\",\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"caller\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutManager,openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutWindow,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueCastObject,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueImageCarrier\",\n        \"shared_vtable:vtable:0x013fdb6c,vtable:0x013fdbe4\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-UTFWIN-LAYOUT-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"pkg_utfwin_layout_wave6_009601e0\",\n      \"va\": \"0x009601e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutManager,openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutWindow,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueCastObject,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueImageCarrier\",\n        \"shared_vtable:vtable:0x013fdb6c,vtable:0x013fdbe4\"\n      ],\n      \"package\": \"PKG-UTFWIN-LAYOUT-WAVE6\",\n      \"score\": 27,\n      \"symbol\": \"pkg_utfwin_layout_wave6_00961300\",\n      \"va\": \"0x00961300\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutManager,openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutWindow,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueCastObject,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueImageCarrier\"\n      ],\n      \"package\": \"PKG-UTFWIN-LAYOUT-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"pkg_utfwin_layout_wave6_00962830\",\n      \"va\": \"0x00962830\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutManager,openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutWindow,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueCastObject,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueImageCarrier\"\n      ],\n      \"package\": \"PKG-UTFWIN-LAYOUT-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"pkg_utfwin_layout_wave6_009646d0\",\n      \"va\": \"0x009646d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutManager,openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutWindow,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueCastObject,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueImageCarrier\"\n      ],\n      \"package\": \"PKG-UTFWIN-LAYOUT-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"pkg_utfwin_layout_wave6_00967e20\",\n      \"va\": \"0x00967e20\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutManager,openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutWindow,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueCastObject,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueImageCarrier\"\n      ],\n      \"package\": \"PKG-UTFWIN-LAYOUT-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"pkg_utfwin_layout_wave6_00967e60\",\n      \"va\": \"0x00967e60\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutManager,openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutWindow,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueCastObject,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueImageCarrier\"\n      ],\n      \"package\": \"PKG-UTFWIN-LAYOUT-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"pkg_utfwin_layout_wave6_00967e80\",\n      \"va\": \"0x00967e80\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutManager,openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutWindow,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueCastObject,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueImageCarrier\"\n      ],\n      \"package\": \"PKG-UTFWIN-LAYOUT-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"pkg_utfwin_layout_wave6_0096feb0\",\n      \"va\": \"0x0096feb0\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Reviewed static mechanics and x86-32 ABI are preserved; opaque runtime ports and ownership remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": null,\n  \"cluster\": \"utfwin-framework\",\n  \"confidence\": 0.9,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0301\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"SUPPORTED\",\n  \"globals\": [],\n  \"
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
  "body_end": "0096126b",
  "body_span_bytes": 12,
  "body_start": "00961260",
  "callees": [],
  "callers": [],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "00961260",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "UTFWin::Window::SendToBack",
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
  "rva": "0x561260",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "void UTFWin::Window::SendToBack(IWindow * this, IWindow * pWindow)",
  "size_bytes": 12,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00961260",
  "vtables": {
    "referenced_by_vtables": [
      "0x013fdb6c",
      "0x01414c14",
      "0x014151cc",
      "0x01419974",
      "0x01419ba4",
      "0x01441b4c",
      "0x01442e44",
      "0x0144324c",
      "0x01444624",
      "0x01444a9c",
      "0x01444f94",
      "0x01445464",
      "0x01445d94",
      "0x01445fac",
      "0x014461e4",
      "0x014464c4",
      "0x0145d68c",
      "0x01479314",
      "0x0147f964",
      "0x01414f38"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 32,
  "xrefs": [
    {
      "from": "013fdbe4"
    },
    {
      "from": "01414c8c"
    },
    {
      "from": "01414f7c"
    },
    {
      "from": "01415244"
    },
    {
      "from": "014432c4"
    },
    {
      "from": "014187e4"
    },
    {
      "from": "0141917c"
    },
    {
      "from": "014193b4"
    },
    {
      "from": "01419654"
    },
    {
      "from": "014199ec"
    },
    {
      "from": "01419c1c"
    },
    {
      "from": "0141ac3c"
    },
    {
      "from": "014411ec"
    },
    {
      "from": "0144183c"
    },
    {
      "from": "01441bc4"
    },
    {
      "from": "01441f84"
    },
    {
      "from": "01442ebc"
    },
    {
      "from": "01443b94"
    },
    {
      "from": "0144469c"
    },
    {
      "from": "01444b14"
    },
    {
      "from": "0144500c"
    },
    {
      "from": "014454dc"
    },
    {
      "from": "0144596c"
    },
    {
      "from": "01445e0c"
    },
    {
      "from": "01446024"
    },
    {
      "from": "0144625c"
    },
    {
      "from": "0144653c"
    },
    {
      "from": "0145d704"
    },
    {
      "from": "0147938c"
    },
    {
      "from": "0147f9dc"
    },
    {
      "from": "0147fc8c"
    },
    {
      "from": "0147f814"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__Window__SendToBack.c",
  "file": "src/reconstruction/pkg_utfwin_layout_wave6/utfwin_layout_wave6.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__Window__SendToBack.c",
    "src/reconstruction/pkg_utfwin_layout_wave6/utfwin_layout_wave6.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-utfwin-layout-wave6/00961260.json"
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
    "cast field semantics and output ownership remain gated",
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
  "openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutManager",
  "openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutWindow",
  "openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueCastObject",
  "openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueImageCarrier",
  "openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueIndexCarrier",
  "void"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x013fdb6c",
  "vtable:0x013fdbe4",
  "vtable:0x01414c14",
  "vtable:0x01414c8c",
  "vtable:0x01414f38",
  "vtable:0x01414f7c",
  "vtable:0x014151cc",
  "vtable:0x01415244",
  "vtable:0x014187a0",
  "vtable:0x014187e4",
  "vtable:0x01419138",
  "vtable:0x0141917c",
  "vtable:0x01419370",
  "vtable:0x014193b4",
  "vtable:0x01419610",
  "vtable:0x01419654"
]
```

## Conflicts

```json
[]
```
