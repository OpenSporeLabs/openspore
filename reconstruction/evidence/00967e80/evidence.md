# Evidence 0x00967e80

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `b947378546fc1865a6395f09e160dd5f8d5add78de569e7178130ebdc19c166e`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "x86-32 thiscall with first explicit object pointer in ECX and caller cleanup",
  "return_semantics": "tail virtual result in EAX",
  "return_type": "Opaque",
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
    ]
  },
  "abstained_because": [
    "no_terminal_ret: function has no RET instruction"
  ],
  "cleanup": {
    "bytes": null,
    "confidence": "UNKNOWN",
    "corroboration": "not_available",
    "evidence": null,
    "side": null
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "b545c84e4caf5c3a410b5d307ae6774e47c4c573eab0c3de3b9602bf915f954a",
  "conventions": {
    "ambiguities": [],
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
    "ghidra_parameter_count": 3,
    "persisted": "no_information",
    "persisted_calling_convention": "x86-32 thiscall with first explicit object pointer in ECX and caller cleanup"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0010"
      ],
      "claim": "no terminal return is present in the listing",
      "confidence": "UNKNOWN",
      "id": "C2"
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0009"
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
        "obs-0004",
        "obs-0005",
        "obs-0006",
        "obs-0008"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "SUPPORTED",
      "id": "R1",
      "value": {
        "offsets": [
          -524,
          -384,
          52
        ],
        "register": "ECX",
        "written_through": 1
      }
    },
    {
      "based_on": [
        "obs-0010"
      ],
      "claim": "entry slot 0 is not written through a pointer",
      "confidence": "APPROXIMATION",
      "id": "S2",
      "value": {
        "present": false
      }
    }
  ],
  "observations": [
    {
      "at": "0x00967e80",
      "count": 2,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "ESP"
    },
    {
      "at": "0x00967e80",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0002",
      "index": 0,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00967e80",
      "definite": true,
      "id": "obs-0003",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00967e84",
      "count": 2,
      "first_use": 1,
      "first_write_index": 4,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EDX,dword ptr [ECX + 0xfffffdf4]",
      "reg": "ECX"
    },
    {
      "at": "0x00967e84",
      "definite": true,
      "id": "obs-0005",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [ECX + 0xfffffdf4]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00967e8a",
      "count": 2,
      "first_use": 2,
      "first_write_index": 0,
      "id": "obs-0006",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV dword ptr [ECX + 0x34],EAX",
      "reg": "EAX"
    },
    {
      "at": "0x00967e8d",
      "count": 1,
      "first_use": 3,
      "first_write_index": 1,
      "id": "obs-0007",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [EDX + 0x8c]",
      "reg": "EDX"
    },
    {
      "at": "0x00967e93",
      "definite": true,
      "id": "obs-0008",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "ADD ECX,0xfffffdf4",
      "reg": "ECX",
      "write_kind": "arith"
    },
    {
      "at": "0x00967e99",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0009",
      "index": 5,
      "key": 4,
      "kind": "STACK_SLOT_WRITE",
      "raw": "MOV dword ptr [ESP + 0x4],0x1",
      "resolved": true,
      "size": 4,
      "via": "direct"
    },
    {
      "at": "0x00967ea1",
      "base": "EAX",
      "disp": null,
      "id": "obs-0010",
      "index": 6,
      "kind": "JMP_INDIRECT",
      "raw": "JMP EAX",
      "via": "register"
    }
  ],
  "parse": {
    "declared_count": 7,
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
    "local_extent": 524,
    "unparsed": 0
  },
  "receiver": {
    "bounds_only": true,
    "confidence": "SUPPORTED",
    "distinct_offsets": 3,
    "max_offset": 52,
    "offsets": [

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
  "count": 7,
  "instructions": [
    {
      "address": "00967e80",
      "instruction": "MOV EAX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "00967e84",
      "instruction": "MOV EDX,dword ptr [ECX + 0xfffffdf4]"
    },
    {
      "address": "00967e8a",
      "instruction": "MOV dword ptr [ECX + 0x34],EAX"
    },
    {
      "address": "00967e8d",
      "instruction": "MOV EAX,dword ptr [EDX + 0x8c]"
    },
    {
      "address": "00967e93",
      "instruction": "ADD ECX,0xfffffdf4"
    },
    {
      "address": "00967e99",
      "instruction": "MOV dword ptr [ESP + 0x4],0x1"
    },
    {
      "address": "00967ea1",
      "instruction": "JMP EAX"
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
  "original_bytes": 9150,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"x86-32 thiscall with first explicit object pointer in ECX and caller cleanup\",\n    \"return_semantics\": \"tail virtual result in EAX\",\n    \"return_type\": \"Opaque\",\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"caller\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutManager,openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutWindow,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueCastObject,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueImageCarrier\",\n        \"shared_vtable:vtable:0x014416f0,vtable:0x01441748\"\n      ],\n      \"package\": \"PKG-UTFWIN-LAYOUT-WAVE6\",\n      \"score\": 27,\n      \"symbol\": \"pkg_utfwin_layout_wave6_00967e20\",\n      \"va\": \"0x00967e20\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutManager,openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutWindow,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueCastObject,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueImageCarrier\",\n        \"shared_vtable:vtable:0x014416f0,vtable:0x01441748\"\n      ],\n      \"package\": \"PKG-UTFWIN-LAYOUT-WAVE6\",\n      \"score\": 27,\n      \"symbol\": \"pkg_utfwin_layout_wave6_00967e60\",\n      \"va\": \"0x00967e60\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutManager,openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutWindow,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueCastObject,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueImageCarrier\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-UTFWIN-LAYOUT-WAVE6\",\n      \"score\": 25,\n      \"symbol\": \"pkg_utfwin_layout_wave6_00962830\",\n      \"va\": \"0x00962830\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutManager,openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutWindow,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueCastObject,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueImageCarrier\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-UTFWIN-LAYOUT-WAVE6\",\n      \"score\": 25,\n      \"symbol\": \"pkg_utfwin_layout_wave6_0096feb0\",\n      \"va\": \"0x0096feb0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutManager,openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutWindow,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueCastObject,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueImageCarrier\"\n      ],\n      \"package\": \"PKG-UTFWIN-LAYOUT-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"pkg_utfwin_layout_wave6_009601e0\",\n      \"va\": \"0x009601e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutManager,openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutWindow,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueCastObject,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueImageCarrier\"\n      ],\n      \"package\": \"PKG-UTFWIN-LAYOUT-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"pkg_utfwin_layout_wave6_00961260\",\n      \"va\": \"0x00961260\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutManager,openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutWindow,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueCastObject,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueImageCarrier\"\n      ],\n      \"package\": \"PKG-UTFWIN-LAYOUT-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"pkg_utfwin_layout_wave6_00961300\",\n      \"va\": \"0x00961300\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutManager,openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutWindow,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueCastObject,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueImageCarrier\"\n      ],\n      \"package\": \"PKG-UTFWIN-LAYOUT-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"pkg_utfwin_layout_wave6_009646d0\",\n      \"va\": \"0x009646d0\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Reviewed static mechanics and x86-32 ABI are preserved; opaque runtime ports and ownership remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": null,\n  \"cluster\": \"utfwin-framework\",\n  \"confidence\": 0.9,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0309\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n
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
  "body_end": "00967ea2",
  "body_span_bytes": 35,
  "body_start": "00967e80",
  "callees": [],
  "callers": [],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "00967e80",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "UTFWin::ComboBoxDrawable::SetImage",
  "namespace": "UTFWin",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 3,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "IComboBoxDrawable *"
    },
    {
      "name": "index",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "int"
    },
    {
      "name": "pImage",
      "ordinal": 2,
      "storage": "Stack[0xc]:4",
      "type": "Image *"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "void",
  "return_type_resolved": true,
  "rva": "0x567e80",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "void UTFWin::ComboBoxDrawable::SetImage(IComboBoxDrawable * this, int index, Image * pImage)",
  "size_bytes": 35,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00967e80",
  "vtables": {
    "referenced_by_vtables": [
      "0x01441748",
      "0x014416f0"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "01441758"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__ComboBoxDrawable__SetImage.c",
  "file": "src/reconstruction/pkg_utfwin_layout_wave6/utfwin_layout_wave6.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__ComboBoxDrawable__SetImage.c",
    "src/reconstruction/pkg_utfwin_layout_wave6/utfwin_layout_wave6.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-utfwin-layout-wave6/00967e80.json"
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
    "adjusted layout, tail vtable, and returned value ownership remain gated",
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
  "Opaque",
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
  "vtable:0x014416f0",
  "vtable:0x01441748"
]
```

## Conflicts

```json
[]
```
