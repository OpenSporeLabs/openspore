# Evidence 0x0095f960

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `80caa3bff81590ad5b6955e74a36d74060b82ab8ab35747b0257fbb84077ee01`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "x86-32 thiscall with first explicit window receiver in ECX and caller cleanup",
  "return_semantics": "window+4 pointer or null in EAX",
  "return_type": "void*",
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
    "return_semantics": "integral_in_EAX",
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
  "abstained_because": [],
  "cleanup": {
    "bytes": 4,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x4",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "bac9461f4bd3806629ba05e8b57f76ee5184609a2cb5295bb22a58cb5e46ba11",
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
    "ghidra_parameter_count": 1,
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
        "obs-0006",
        "obs-0008"
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
        "obs-0001"
      ],
      "claim": "ECX carries the receiver: 0x0095f960 is slot 3 of the vptr-backed vftable at 0x01414b10, so it is a virtual member of some class and every virtual call that reaches it indexes the vptr through the object address; the body reads its incoming ECX before writing it, and a body that reads a register the vtable dispatch delivered uses the object, so the receiver is in ECX. The callee pops its own stack arguments, which is the COM / __stdcall interface form, and that is the one shape in which a virtual member takes its receiver from the first popped stack word instead -- a body in that form never reads its incoming ECX, which is why this body reading it is what decides the two apart",
      "confidence": "INFERRED",
      "id": "R1-VFT",
      "value": {
        "cleanup_side": "callee",
        "incoming_ecx_reads": 1,
        "membership_count": 7,
        "receiver_provenance": "vftable_slot_dispatch",
        "receiver_register": "ECX",
        "slot_index": 3,
        "table": "0x01414b10"
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0002",
        "obs-0003",
        "obs-0004",
        "obs-0005",
        "obs-0006",
        "obs-0008"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0008"
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
        "obs-0006",
        "obs-0008"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0008"
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
      "at": "0x0095f960",
      "count": 1,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x0095f960",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,ECX",
      "reg": "EAX",
      "write_kind": "reg"
    },
    {
      "at": "0x0095f962",
      "count": 1,
      "first_use": 1,
      "first_write_index": null,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ECX,dword ptr [ESP + 0x4]",
      "reg": "ESP"
    },
    {
      "at": "0x0095f962",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0004",
      "index": 1,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV ECX,dword ptr [ESP + 0x4]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x0095f962",
      "definite": true,
      "id": "obs-0005",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [ESP + 0x4]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x0095f985",
      "form": "RET 0x4",
      "id": "obs-0006",
      "imm": 4,
      "index": 11,
    
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
    "va": "0x007f31b0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x007f5410"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0081cf00"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00963f30"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00967a20"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0096b3d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00970270"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00980fc0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00983b40"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00985cb0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00988690"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00989210"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0098f370"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00991f40"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x009925b0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00992da0"
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
  "count": 14,
  "instructions": [
    {
      "address": "0095f960",
      "instruction": "MOV EAX,ECX"
    },
    {
      "address": "0095f962",
      "instruction": "MOV ECX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "0095f966",
      "instruction": "CMP ECX,0xee3f516e"
    },
    {
      "address": "0095f96c",
      "instruction": "JZ 0x0095f97e"
    },
    {
      "address": "0095f96e",
      "instruction": "CMP ECX,0xeec58382"
    },
    {
      "address": "0095f974",
      "instruction": "JZ 0x0095f98a"
    },
    {
      "address": "0095f976",
      "instruction": "CMP ECX,0xeeee8218"
    },
    {
      "address": "0095f97c",
      "instruction": "JNZ 0x0095f988"
    },
    {
      "address": "0095f97e",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "0095f980",
      "instruction": "JZ 0x0095f988"
    },
    {
      "address": "0095f982",
      "instruction": "ADD EAX,0x4"
    },
    {
      "address": "0095f985",
      "instruction": "RET 0x4"
    },
    {
      "address": "0095f988",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "0095f98a",
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
  "original_bytes": 13366,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"x86-32 thiscall with first explicit window receiver in ECX and caller cleanup\",\n    \"return_semantics\": \"window+4 pointer or null in EAX\",\n    \"return_type\": \"void*\",\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"caller\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_core_wave6::CursorManager,openspore::reconstruction::pkg_utfwin_core_wave6::Drawable,openspore::reconstruction::pkg_utfwin_core_wave6::DropIconObject,openspore::reconstruction::pkg_utfwin_core_wave6::ResourceFactory\",\n        \"shared_vtable:vtable:0x01414b10,vtable:0x01440b1c\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"re_0095f990\",\n      \"va\": \"0x0095f990\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_core_wave6::CursorManager,openspore::reconstruction::pkg_utfwin_core_wave6::Drawable,openspore::reconstruction::pkg_utfwin_core_wave6::DropIconObject,openspore::reconstruction::pkg_utfwin_core_wave6::ResourceFactory\",\n        \"shared_vtable:vtable:0x01414b10,vtable:0x01440b1c\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"re_0095f9a0\",\n      \"va\": \"0x0095f9a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_core_wave6::CursorManager,openspore::reconstruction::pkg_utfwin_core_wave6::Drawable,openspore::reconstruction::pkg_utfwin_core_wave6::DropIconObject,openspore::reconstruction::pkg_utfwin_core_wave6::ResourceFactory\",\n        \"shared_vtable:vtable:0x01414b10,vtable:0x01418838\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 27,\n      \"symbol\": \"re_00951230\",\n      \"va\": \"0x00951230\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_core_wave6::CursorManager,openspore::reconstruction::pkg_utfwin_core_wave6::Drawable,openspore::reconstruction::pkg_utfwin_core_wave6::DropIconObject,openspore::reconstruction::pkg_utfwin_core_wave6::ResourceFactory\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 25,\n      \"symbol\": \"re_00575ea0\",\n      \"va\": \"0x00575ea0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_core_wave6::CursorManager,openspore::reconstruction::pkg_utfwin_core_wave6::Drawable,openspore::reconstruction::pkg_utfwin_core_wave6::DropIconObject,openspore::reconstruction::pkg_utfwin_core_wave6::ResourceFactory\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 25,\n      \"symbol\": \"re_00960050\",\n      \"va\": \"0x00960050\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_core_wave6::CursorManager,openspore::reconstruction::pkg_utfwin_core_wave6::Drawable,openspore::reconstruction::pkg_utfwin_core_wave6::DropIconObject,openspore::reconstruction::pkg_utfwin_core_wave6::ResourceFactory\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"re_00801ac0\",\n      \"va\": \"0x00801ac0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_core_wave6::CursorManager,openspore::reconstruction::pkg_utfwin_core_wave6::Drawable,openspore::reconstruction::pkg_utfwin_core_wave6::DropIconObject,openspore::reconstruction::pkg_utfwin_core_wave6::ResourceFactory\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"re_00835380\",\n      \"va\": \"0x00835380\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_core_wave6::CursorManager,openspore::reconstruction::pkg_utfwin_core_wave6::Drawable,openspore::reconstruction::pkg_utfwin_core_wave6::DropIconObject,openspore::reconstruction::pkg_utfwin_core_wave6::ResourceFactory\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"re_00951220\",\n      \"va\": \"0x00951220\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Reviewed static mechanics and x86-32 ABI are preserved; opaque runtime ports and ownership remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": null,\n  \"cluster\": \"utfwin-framework\",\n  \"confidence\": 0.9,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007f31b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007f5410\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0081cf00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00963f30\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00967a20\"\n      },\n      {\n        \"name\"
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
  "body_end": "0095f98c",
  "body_span_bytes": 45,
  "body_start": "0095f960",
  "callees": [],
  "callers": [
    "FUN_00980fc0",
    "FUN_00963f30",
    "FUN_0096b3d0",
    "FUN_00970270",
    "FUN_0081cf00",
    "UTFWin::Window::GetRealArea",
    "FUN_00989210",
    "FUN_0098f370",
    "FUN_00985cb0",
    "FUN_00991f40",
    "FUN_00992da0",
    "FUN_00983b40",
    "FUN_007f5410",
    "FUN_00967a20",
    "FUN_007f31b0",
    "FUN_009925b0",
    "FUN_00988690"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "0095f960",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "UTFWin::Window::GetRealArea",
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
  "return_type": "Rectangle *",
  "return_type_resolved": true,
  "rva": "0x55f960",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "Rectangle * UTFWin::Window::GetRealArea(IWindow * this)",
  "size_bytes": 45,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x0095f960",
  "vtables": {
    "referenced_by_vtables": [
      "0x01418838",
      "0x01441c18",
      "0x01443318",
      "0x014793e0",
      "0x01414b10",
      "0x0145d758",
      "0x0147fa30",
      "0x01440b1c"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 26,
  "xrefs": [
    {
      "from": "01414b1c"
    },
    {
      "from": "01418844"
    },
    {
      "from": "01440b50"
    },
    {
      "from": "01441c24"
    },
    {
      "from": "01443324"
    },
    {
      "from": "0145d764"
    },
    {
      "from": "014793ec"
    },
    {
      "from": "0147fa3c"
    },
    {
      "from": "00992daf"
    },
    {
      "from": "007f31b3"
    },
    {
      "from": "007f3c84"
    },
    {
      "from": "0098921f"
    },
    {
      "from": "007f542d"
    },
    {
      "from": "00963f3f"
    },
    {
      "from": "0081cf0f"
    },
    {
      "from": "0098869f"
    },
    {
      "from": "00967a2f"
    },
    {
      "from": "0096b3df"
    },
    {
      "from": "0097027f"
    },
    {
      "from": "00980fcf"
    },
    {
      "from": "00983b4f"
    },
    {
      "from": "00985cbf"
    },
    {
      "from": "0098f37f"
    },
    {
      "from": "00991f54"
    },
    {
      "from": "009925c4"
    },
    {
      "from": "00e0ab20"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__Window__GetRealArea.c",
  "file": "src/reconstruction/pkg_utfwin_core_wave6/utfwin_core_wave6.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__Window__GetRealArea.c",
    "src/reconstruction/pkg_utfwin_core_wave6/utfwin_core_wave6.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-utfwin-core-wave6/0095f960.json"
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
    "window subobject layout and type domain remain gated"
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
  "void*"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x01414b10",
  "vtable:0x01418838",
  "vtable:0x01440b1c",
  "vtable:0x01441c18",
  "vtable:0x01443318",
  "vtable:0x0145d758",
  "vtable:0x014793e0",
  "vtable:0x0147fa30"
]
```

## Conflicts

```json
[]
```
