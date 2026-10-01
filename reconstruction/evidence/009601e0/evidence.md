# Evidence 0x009601e0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `596769c7dbcbf4a50bc18c72ffb65f5a945a87d113b0ab5f625639a26d7bc4c2`

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
  "stack_cleanup_bytes": 8,
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
    "ordinary_stack_argument_slots": [
      "entry_ESP+0x4",
      "entry_ESP+0x8"
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
      },
      {
        "entry_offset": "entry_ESP+0x8",
        "observed": true,
        "ordinal": 2,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "ret_form": "RET 0x8",
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
      },
      {
        "entry_offset": "entry_ESP+0x8",
        "observed": true,
        "ordinal": 2,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "stack_cleanup_bytes": 8,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x8"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +4, so the listing is not one path",
    "receiver_not_determinable: ecx_reassigned_before_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_reassigned_before_deref), and the convention rule that would apply discriminates on receiver absence",
    "sret_vs_out_param: entry slot 0 is written through a pointer"
  ],
  "cleanup": {
    "bytes": 8,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x8",
    "side": "callee"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "7501ab2a4ae4961e116e295aabc944e833a5b7a61e4df4bf236d5e5524b0f0fc",
  "conventions": {
    "ambiguities": [
      "receiver_undetermined"
    ],
    "calling_convention": null,
    "candidate_conventions": [
      "__stdcall",
      "__thiscall"
    ],
    "confidence": "UNKNOWN",
    "corroboration": "not_available"
  },
  "cross_validation": {
    "agreement": false,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 1,
    "persisted": "no_information",
    "persisted_calling_convention": "x86-32 thiscall with first explicit cast receiver in ECX and caller cleanup"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0011",
        "obs-0015"
      ],
      "claim": "the callee pops 8 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 8,
        "side": "callee"
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0007",
        "obs-0008",
        "obs-0010",
        "obs-0012"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 2,
        "total_bytes": 8
      }
    },
    {
      "based_on": [
        "obs-0005",
        "obs-0006",
        "obs-0009"
      ],
      "claim": "the register receiver is undetermined: ecx_reassigned_before_deref",
      "confidence": "UNKNOWN",
      "id": "R0",
      "value": {
        "reason": "ecx_reassigned_before_deref",
        "register": null
      }
    },
    {
      "based_on": [
        "obs-0005",
        "obs-0006",
        "obs-0009"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_reassigned_before_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0010"
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
        "obs-0011",
        "obs-0015"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0011",
        "obs-0015"
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
      "at": "0x009601e0",
      "count": 6,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x8]",
      "reg": "ESP"
    },
    {
      "at": "0x009601e0",
      "base": "ESP",
      "disp": 8,
      "id": "obs-0002",
      "index": 0,
      "key": 8,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x8]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x009601e0",
      "definite": true,
      "id": "obs-0003",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESP + 0x8]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x009601ed",
      "count": 10,
      "first_use": 5,
      "first_write_index": 0,
      "id": "obs-0004",
      "index": 5,
      "kind": "REG_READ",
      "raw": "XOR EAX,EAX",
      "reg": "EAX"
    },
    {
      "at": "0x009601ef",
      "count": 3,
      "first_use": 6,
      "first_write_index": null,
      "id": "obs-0005",
      "index": 6,
      "kind": "REG_READ",
      "raw": "LEA EDX,[ECX + -0x4]",
      "reg": "
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
  "count": 25,
  "instructions": [
    {
      "address": "009601e0",
      "instruction": "MOV EAX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "009601e4",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "009601e6",
      "instruction": "JZ 0x009601ed"
    },
    {
      "address": "009601e8",
      "instruction": "ADD EAX,-0x4"
    },
    {
      "address": "009601eb",
      "instruction": "JMP 0x009601ef"
    },
    {
      "address": "009601ed",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "009601ef",
      "instruction": "LEA EDX,[ECX + -0x4]"
    },
    {
      "address": "009601f2",
      "instruction": "CMP dword ptr [EAX + 0x38],EDX"
    },
    {
      "address": "009601f5",
      "instruction": "JNZ 0x0096020d"
    },
    {
      "address": "009601f7",
      "instruction": "ADD EAX,0x8"
    },
    {
      "address": "009601fa",
      "instruction": "MOV dword ptr [ESP + 0x8],EAX"
    },
    {
      "address": "009601fe",
      "instruction": "LEA EAX,[ESP + 0x8]"
    },
    {
      "address": "00960202",
      "instruction": "MOV ECX,dword ptr [EAX]"
    },
    {
      "address": "00960204",
      "instruction": "MOV EAX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "00960208",
      "instruction": "MOV dword ptr [EAX],ECX"
    },
    {
      "address": "0096020a",
      "instruction": "RET 0x8"
    },
    {
      "address": "0096020d",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "0096020f",
      "instruction": "MOV EAX,dword ptr [EAX + 0xd0]"
    },
    {
      "address": "00960215",
      "instruction": "LEA EDX,[ESP + 0x8]"
    },
    {
      "address": "00960219",
      "instruction": "PUSH EDX"
    },
    {
      "address": "0096021a",
      "instruction": "CALL EAX"
    },
    {
      "address": "0096021c",
      "instruction": "MOV ECX,dword ptr [EAX]"
    },
    {
      "address": "0096021e",
      "instruction": "MOV EAX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "00960222",
      "instruction": "MOV dword ptr [EAX],ECX"
    },
    {
      "address": "00960224",
      "instruction": "RET 0x8"
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
  "original_bytes": 10982,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"x86-32 thiscall with first explicit cast receiver in ECX and caller cleanup\",\n    \"return_semantics\": \"void\",\n    \"return_type\": \"void\",\n    \"stack_cleanup_bytes\": 8,\n    \"stack_cleanup_owner\": \"caller\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutManager,openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutWindow,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueCastObject,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueImageCarrier\",\n        \"shared_vtable:vtable:0x013fdb6c,vtable:0x013fdbe4\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-UTFWIN-LAYOUT-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"pkg_utfwin_layout_wave6_00961260\",\n      \"va\": \"0x00961260\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutManager,openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutWindow,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueCastObject,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueImageCarrier\",\n        \"shared_vtable:vtable:0x013fdb6c,vtable:0x013fdbe4\"\n      ],\n      \"package\": \"PKG-UTFWIN-LAYOUT-WAVE6\",\n      \"score\": 27,\n      \"symbol\": \"pkg_utfwin_layout_wave6_00961300\",\n      \"va\": \"0x00961300\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutManager,openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutWindow,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueCastObject,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueImageCarrier\"\n      ],\n      \"package\": \"PKG-UTFWIN-LAYOUT-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"pkg_utfwin_layout_wave6_00962830\",\n      \"va\": \"0x00962830\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutManager,openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutWindow,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueCastObject,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueImageCarrier\"\n      ],\n      \"package\": \"PKG-UTFWIN-LAYOUT-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"pkg_utfwin_layout_wave6_009646d0\",\n      \"va\": \"0x009646d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutManager,openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutWindow,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueCastObject,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueImageCarrier\"\n      ],\n      \"package\": \"PKG-UTFWIN-LAYOUT-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"pkg_utfwin_layout_wave6_00967e20\",\n      \"va\": \"0x00967e20\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutManager,openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutWindow,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueCastObject,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueImageCarrier\"\n      ],\n      \"package\": \"PKG-UTFWIN-LAYOUT-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"pkg_utfwin_layout_wave6_00967e60\",\n      \"va\": \"0x00967e60\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutManager,openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutWindow,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueCastObject,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueImageCarrier\"\n      ],\n      \"package\": \"PKG-UTFWIN-LAYOUT-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"pkg_utfwin_layout_wave6_00967e80\",\n      \"va\": \"0x00967e80\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutManager,openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutWindow,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueCastObject,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueImageCarrier\"\n      ],\n      \"package\": \"PKG-UTFWIN-LAYOUT-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"pkg_utfwin_layout_wave6_0096feb0\",\n      \"va\": \"0x0096feb0\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Reviewed static mechanics and x86-32 ABI are preserved; opaque runtime ports and ownership remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": null,\n  \"cluster\": \"utfwin-framework\",\n  \"confidence\": 0.9,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0300\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"SUPPORTED\",\n  \"globals\": [],\n  \"
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
  "body_end": "00960226",
  "body_span_bytes": 71,
  "body_start": "009601e0",
  "callees": [],
  "callers": [],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "009601e0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "UTFWin::Window::DisposeAllWindowFamilies",
  "namespace": "UTFWin",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 1,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "IWindow *"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "void",
  "return_type_resolved": true,
  "rva": "0x5601e0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "void UTFWin::Window::DisposeAllWindowFamilies(IWindow * this)",
  "size_bytes": 71,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x009601e0",
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
      "from": "013fdbec"
    },
    {
      "from": "01414c94"
    },
    {
      "from": "01414f84"
    },
    {
      "from": "0141524c"
    },
    {
      "from": "014432cc"
    },
    {
      "from": "014187ec"
    },
    {
      "from": "01419184"
    },
    {
      "from": "014193bc"
    },
    {
      "from": "0141965c"
    },
    {
      "from": "014199f4"
    },
    {
      "from": "01419c24"
    },
    {
      "from": "0141ac44"
    },
    {
      "from": "014411f4"
    },
    {
      "from": "01441844"
    },
    {
      "from": "01441bcc"
    },
    {
      "from": "01441f8c"
    },
    {
      "from": "01442ec4"
    },
    {
      "from": "01443b9c"
    },
    {
      "from": "014446a4"
    },
    {
      "from": "01444b1c"
    },
    {
      "from": "01445014"
    },
    {
      "from": "014454e4"
    },
    {
      "from": "01445974"
    },
    {
      "from": "01445e14"
    },
    {
      "from": "0144602c"
    },
    {
      "from": "01446264"
    },
    {
      "from": "01446544"
    },
    {
      "from": "0145d70c"
    },
    {
      "from": "01479394"
    },
    {
      "from": "0147f9e4"
    },
    {
      "from": "0147fc94"
    },
    {
      "from": "0147f81c"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__Window__DisposeAllWindowFamilies.c",
  "file": "src/reconstruction/pkg_utfwin_layout_wave6/utfwin_layout_wave6.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__Window__DisposeAllWindowFamilies.c",
    "src/reconstruction/pkg_utfwin_layout_wave6/utfwin_layout_wave6.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-utfwin-layout-wave6/009601e0.json"
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
    "cast object layout, candidate validity, and vtable return ownership remain gated",
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
