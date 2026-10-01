# Evidence 0x0095f990

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `b2200349fb438eeaec75ad3c6e9e56e9324b541ad0b87753ebcf9882ccba03b2`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "x86-32 thiscall with first explicit window receiver in ECX and caller cleanup",
  "return_semantics": "new signed 32-bit reference count in EAX",
  "return_type": "std::int32_t",
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller"
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
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "receiver_not_determinable: ecx_reassigned_before_deref"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "b06110cb4a9fa69e8767e9199a71c57703d8efea18524614c2790fe613033259",
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
    "persisted_calling_convention": "x86-32 thiscall with first explicit window receiver in ECX and caller cleanup"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0006"
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
        "obs-0003",
        "obs-0004",
        "obs-0005"
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
        "obs-0006"
      ],
      "claim": "calling convention is __thiscall: 0x0095f990 is slot 0 of the vptr-backed vftable at 0x01414b10, so it is a virtual member of some class; the callee pops nothing and no stack word is read as an argument, so the receiver is in a register, and ECX is the only one that carries one",
      "confidence": "INFERRED",
      "id": "V1-VFT",
      "value": {
        "cleanup_side": "caller",
        "membership_count": 11,
        "receiver_provenance": "vftable_slot",
        "receiver_register": "ECX",
        "slot_index": 0,
        "table": "0x01414b10"
      }
    },
    {
      "based_on": [
        "obs-0006"
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
        "obs-0006"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0006"
      ],
      "claim": "the last value written to EAX classifies as integral",
      "confidence": "INFERRED",
      "id": "RT2",
      "value": {
        "register_class": "integral"
      }
    }
  ],
  "observations": [
    {
      "at": "0x0095f990",
      "definite": true,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "ADD ECX,0x28",
      "reg": "ECX",
      "write_kind": "arith"
    },
    {
      "at": "0x0095f993",
      "definite": true,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,0x1",
      "reg": "EAX",
      "write_kind": "imm"
    },
    {
      "at": "0x0095f998",
      "count": 1,
      "first_use": 2,
      "first_write_index": 0,
      "id": "obs-0003",
      "index": 2,
      "kind": "REG_READ",
      "raw": "XADD.LOCK dword ptr [ECX],EAX",
      "reg": "ECX"
    },
    {
      "at": "0x0095f998",
      "count": 1,
      "first_use": 2,
      "first_write_index": 1,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "XADD.LOCK dword ptr [ECX],EAX",
      "reg": "EAX"
    },
    {
      "at": "0x0095f998",
      "clobbers": [
        "EAX",
        "ECX"
      ],
      "form": "XADD.LOCK",
      "id": "obs-0005",
      "index": 2,
      "kind": "STRING_OP",
      "raw": "XADD.LOCK dword ptr [ECX],EAX",
      "rep": false,
      "string_base": false
    },
    {
      "at": "0x0095f99d",
      "form": "RET",
      "id": "obs-0006",
      "imm": null,
      "index": 4,
      "kind": "RET",
      "raw": "RET"
    }
  ],
  "parse": {
    "declared_count": 5,
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
    "confidence": "UNKNOWN",
    "distinct_offsets": 0,
    "max_offset": null,
    "offsets": [],
    "present": null,
    "provenance": "vftable_slot",
    "reason": "ecx_reassigned_before_deref",
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
    "register_class": "integral",
    "type": null,
    "void_possible": false
  },
  "schema": "openspore-abi-inference-1",
  "seh_or_cookie_frame": false,
  "sret": {
    "ambiguity": null,
    "basis": "entry slot 0 is not written through a pointer; DERIVED absence is weak, a struct filled through another alias would be missed",
    "candidates": null,
    "confidence": "AP
[TRUNCATED]
```

## callees_dependencies

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## callers_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": null,
    "reconstructed": false,
    "va": "0x007f31d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00952860"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x009568c0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00963f10"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b1dc60"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d0a760"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e0eab0"
  }
]
```

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
  "count": 5,
  "instructions": [
    {
      "address": "0095f990",
      "instruction": "ADD ECX,0x28"
    },
    {
      "address": "0095f993",
      "instruction": "MOV EAX,0x1"
    },
    {
      "address": "0095f998",
      "instruction": "XADD.LOCK dword ptr [ECX],EAX"
    },
    {
      "address": "0095f99c",
      "instruction": "INC EAX"
    },
    {
      "address": "0095f99d",
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
  "original_bytes": 11241,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"x86-32 thiscall with first explicit window receiver in ECX and caller cleanup\",\n    \"return_semantics\": \"new signed 32-bit reference count in EAX\",\n    \"return_type\": \"std::int32_t\",\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_core_wave6::CursorManager,openspore::reconstruction::pkg_utfwin_core_wave6::Drawable,openspore::reconstruction::pkg_utfwin_core_wave6::DropIconObject,openspore::reconstruction::pkg_utfwin_core_wave6::ResourceFactory\",\n        \"shared_vtable:vtable:0x01414b10,vtable:0x01440b1c\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"re_0095f960\",\n      \"va\": \"0x0095f960\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_core_wave6::CursorManager,openspore::reconstruction::pkg_utfwin_core_wave6::Drawable,openspore::reconstruction::pkg_utfwin_core_wave6::DropIconObject,openspore::reconstruction::pkg_utfwin_core_wave6::ResourceFactory\",\n        \"shared_vtable:vtable:0x01414b10,vtable:0x01414ce0\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"re_0095f9a0\",\n      \"va\": \"0x0095f9a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_core_wave6::CursorManager,openspore::reconstruction::pkg_utfwin_core_wave6::Drawable,openspore::reconstruction::pkg_utfwin_core_wave6::DropIconObject,openspore::reconstruction::pkg_utfwin_core_wave6::ResourceFactory\",\n        \"shared_vtable:vtable:0x01414b10,vtable:0x01414ce0\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 27,\n      \"symbol\": \"re_00951230\",\n      \"va\": \"0x00951230\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_core_wave6::CursorManager,openspore::reconstruction::pkg_utfwin_core_wave6::Drawable,openspore::reconstruction::pkg_utfwin_core_wave6::DropIconObject,openspore::reconstruction::pkg_utfwin_core_wave6::ResourceFactory\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 25,\n      \"symbol\": \"re_00575ea0\",\n      \"va\": \"0x00575ea0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_core_wave6::CursorManager,openspore::reconstruction::pkg_utfwin_core_wave6::Drawable,openspore::reconstruction::pkg_utfwin_core_wave6::DropIconObject,openspore::reconstruction::pkg_utfwin_core_wave6::ResourceFactory\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 25,\n      \"symbol\": \"re_00960050\",\n      \"va\": \"0x00960050\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_core_wave6::CursorManager,openspore::reconstruction::pkg_utfwin_core_wave6::Drawable,openspore::reconstruction::pkg_utfwin_core_wave6::DropIconObject,openspore::reconstruction::pkg_utfwin_core_wave6::ResourceFactory\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"re_00801ac0\",\n      \"va\": \"0x00801ac0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_core_wave6::CursorManager,openspore::reconstruction::pkg_utfwin_core_wave6::Drawable,openspore::reconstruction::pkg_utfwin_core_wave6::DropIconObject,openspore::reconstruction::pkg_utfwin_core_wave6::ResourceFactory\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"re_00835380\",\n      \"va\": \"0x00835380\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_core_wave6::CursorManager,openspore::reconstruction::pkg_utfwin_core_wave6::Drawable,openspore::reconstruction::pkg_utfwin_core_wave6::DropIconObject,openspore::reconstruction::pkg_utfwin_core_wave6::ResourceFactory\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"re_00951220\",\n      \"va\": \"0x00951220\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Reviewed static mechanics and x86-32 ABI are preserved; opaque runtime ports and ownership remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": null,\n  \"cluster\": \"utfwin-framework\",\n  \"confidence\": 0.9,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007f31d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00952860\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x009568c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00963f10\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b1dc60\"\n      },\n      {\n
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
  "body_end": "0095f99d",
  "body_span_bytes": 14,
  "body_start": "0095f990",
  "callees": [],
  "callers": [
    "FUN_00952860",
    "FUN_007f31d0",
    "FUN_00e0eab0",
    "UTFWin::Window::SetCommandID",
    "FUN_00d0a760",
    "FUN_009568c0",
    "FUN_00b1dc60"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "0095f990",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "UTFWin::Window::SetCommandID",
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
      "name": "commandID",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "uint32_t"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "void",
  "return_type_resolved": true,
  "rva": "0x55f990",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "void UTFWin::Window::SetCommandID(IWindow * this, uint32_t commandID)",
  "size_bytes": 14,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x0095f990",
  "vtables": {
    "referenced_by_vtables": [
      "0x01441c18",
      "0x01443318",
      "0x014793e0",
      "0x01414b10",
      "0x01414ce0",
      "0x01446078",
      "0x014462b0",
      "0x0145d758",
      "0x0147fa30",
      "0x01440b1c",
      "0x01440448",
      "0x0144064c"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 20,
  "xrefs": [
    {
      "from": "00956992"
    },
    {
      "from": "00b1de02"
    },
    {
      "from": "009528b4"
    },
    {
      "from": "00d0a8b9"
    },
    {
      "from": "00e0ee4a"
    },
    {
      "from": "00e0eebe"
    },
    {
      "from": "007f31d3"
    },
    {
      "from": "01414b10"
    },
    {
      "from": "01414ce0"
    },
    {
      "from": "014404ac"
    },
    {
      "from": "0144064c"
    },
    {
      "from": "01440b44"
    },
    {
      "from": "01441c18"
    },
    {
      "from": "01443318"
    },
    {
      "from": "01446078"
    },
    {
      "from": "014462b0"
    },
    {
      "from": "0145d758"
    },
    {
      "from": "014793e0"
    },
    {
      "from": "0147fa30"
    },
    {
      "from": "00963f10"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__Window__SetCommandID.c",
  "file": "src/reconstruction/pkg_utfwin_core_wave6/utfwin_core_wave6.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__Window__SetCommandID.c",
    "src/reconstruction/pkg_utfwin_core_wave6/utfwin_core_wave6.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-utfwin-core-wave6/0095f990.json"
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
    "runtime validation not run",
    "window lifetime and reference-count synchronization remain gated"
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
  "openspore::reconstruction::pkg_utfwin_core_wave6::CursorManager",
  "openspore::reconstruction::pkg_utfwin_core_wave6::Drawable",
  "openspore::reconstruction::pkg_utfwin_core_wave6::DropIconObject",
  "openspore::reconstruction::pkg_utfwin_core_wave6::ResourceFactory",
  "openspore::reconstruction::pkg_utfwin_core_wave6::TooltipCore",
  "openspore::reconstruction::pkg_utfwin_core_wave6::WindowCore",
  "std::int32_t"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x01414b10",
  "vtable:0x01414ce0",
  "vtable:0x01440448",
  "vtable:0x0144064c",
  "vtable:0x01440b1c",
  "vtable:0x01441c18",
  "vtable:0x01443318",
  "vtable:0x01446078",
  "vtable:0x014462b0",
  "vtable:0x0145d758",
  "vtable:0x014793e0",
  "vtable:0x0147fa30"
]
```

## Conflicts

```json
[]
```
