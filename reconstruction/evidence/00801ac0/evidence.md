# Evidence 0x00801ac0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `a036bd6816656180538bd70738ea634232fe18fd7f996631dfac36439487e38b`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "x86-32 thiscall with first explicit cursor-manager receiver in ECX and caller cleanup",
  "return_semantics": "byte in AL; one only after accepted dispatch",
  "return_type": "std::uint8_t",
  "stack_cleanup_bytes": 16,
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
      "entry_ESP+0x4",
      "entry_ESP+0xc",
      "entry_ESP+0x10"
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
        "entry_offset": "entry_ESP+0xc",
        "observed": true,
        "ordinal": 3,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x10",
        "observed": true,
        "ordinal": 4,
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
    "ret_form": "RET 0x10",
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
    "saved_registers": [
      "EBX",
      "EDI",
      "ESI"
    ],
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
        "entry_offset": "entry_ESP+0xc",
        "observed": true,
        "ordinal": 3,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x10",
        "observed": true,
        "ordinal": 4,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "stack_cleanup_bytes": 16,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x10"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +8, so the listing is not one path",
    "slot_gaps_present: argument ordinal(s) below the highest read slot are never touched",
    "ecx_and_edx_indistinguishable: EDX is dereferenced before any write to it (C8-E) and the callee pops its own stack arguments (C6B); a fastcall callee does not pop and a popping thiscall has no incoming register argument"
  ],
  "cleanup": {
    "bytes": 16,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x10",
    "side": "callee"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "e812622c9dbd39538dfc5422e306ec8889803478619eab90ef3d8a5e8ed7e538",
  "conventions": {
    "ambiguities": [
      "ecx_and_edx_indistinguishable"
    ],
    "calling_convention": null,
    "candidate_conventions": [
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
    "persisted_calling_convention": "x86-32 thiscall with first explicit cursor-manager receiver in ECX and caller cleanup"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 3,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0026",
        "obs-0029"
      ],
      "claim": "the callee pops 16 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 16,
        "side": "callee"
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0014",
        "obs-0019"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 1,
        "observed_slots": 3,
        "total_bytes": 16
      }
    },
    {
      "based_on": [
        "obs-0005",
        "obs-0006",
        "obs-0011"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          0
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0012",
        "obs-0017",
        "obs-0018",
        "obs-0020"
      ],
      "claim": "EDX is a memory base before any definite write to it",
      "confidence": "OBSERVED",
      "id": "C8-E",
      "value": {
        "register": "EDX"
      }
    },
    {
      "based_on": [
        "obs-0005",
        "obs-0006",
        "obs-0011",
        "obs-0026",
        "obs-0029"
      ],
      "claim": "the reading that this is a __thiscall member which pops its own stack arguments is present and undecided: it excludes __fastcall, while C8-E asserts an incoming EDX that only __fastcall guarantees",
      "confidence": "UNKNOWN",
      "id": "C6B"
    },
    {
      "based_on": [
        "obs-0026",
        "obs-0029"
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
        "obs-0026",
        "obs-0029"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0026",
        "obs-0029"
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
      "at": "0x00801ac0",
      "count": 4,
      "first_use": 0,
      "first_write_index": 13,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "CMP dword ptr [ESP +
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "wave6_reference_00432a50",
    "reconstructed": true,
    "va": "0x00432a50"
  }
]
```

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
  "count": 63,
  "instructions": [
    {
      "address": "00801ac0",
      "instruction": "CMP dword ptr [ESP + 0x10],0x2393756"
    },
    {
      "address": "00801ac8",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00801ac9",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00801aca",
      "instruction": "MOV EBX,ECX"
    },
    {
      "address": "00801acc",
      "instruction": "JNZ 0x00801b57"
    },
    {
      "address": "00801ad2",
      "instruction": "XOR ESI,ESI"
    },
    {
      "address": "00801ad4",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00801ad5",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00801ad6",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00801ad7",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00801ad8",
      "instruction": "PUSH 0x1416fbc"
    },
    {
      "address": "00801add",
      "instruction": "PUSH 0x18"
    },
    {
      "address": "00801adf",
      "instruction": "CALL 0x00f473a0"
    },
    {
      "address": "00801ae4",
      "instruction": "ADD ESP,0x18"
    },
    {
      "address": "00801ae7",
      "instruction": "CMP EAX,ESI"
    },
    {
      "address": "00801ae9",
      "instruction": "JZ 0x00801b09"
    },
    {
      "address": "00801aeb",
      "instruction": "MOV dword ptr [EAX],0x13ebcdc"
    },
    {
      "address": "00801af1",
      "instruction": "XOR ECX,ECX"
    },
    {
      "address": "00801af3",
      "instruction": "LEA EDX,[EAX + 0x4]"
    },
    {
      "address": "00801af6",
      "instruction": "XCHG dword ptr [EDX],ECX"
    },
    {
      "address": "00801af8",
      "instruction": "MOV dword ptr [EAX + 0x8],ESI"
    },
    {
      "address": "00801afb",
      "instruction": "MOV dword ptr [EAX + 0xc],ESI"
    },
    {
      "address": "00801afe",
      "instruction": "MOV dword ptr [EAX + 0x10],ESI"
    },
    {
      "address": "00801b01",
      "instruction": "MOV dword ptr [EAX],0x1416fa8"
    },
    {
      "address": "00801b07",
      "instruction": "MOV ESI,EAX"
    },
    {
      "address": "00801b09",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00801b0a",
      "instruction": "MOV EDI,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00801b0e",
      "instruction": "MOV EAX,dword ptr [EDI]"
    },
    {
      "address": "00801b10",
      "instruction": "MOV EDX,dword ptr [EAX + 0x10]"
    },
    {
      "address": "00801b13",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00801b15",
      "instruction": "CALL EDX"
    },
    {
      "address": "00801b17",
      "instruction": "MOV ECX,dword ptr [EAX]"
    },
    {
      "address": "00801b19",
      "instruction": "MOV dword ptr [ESI + 0x8],ECX"
    },
    {
      "address": "00801b1c",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "00801b1f",
      "instruction": "MOV dword ptr [ESI + 0xc],EDX"
    },
    {
      "address": "00801b22",
      "instruction": "MOV EAX,dword ptr [EAX + 0x8]"
    },
    {
      "address": "00801b25",
      "instruction": "MOV dword ptr [ESI + 0x10],EAX"
    },
    {
      "address": "00801b28",
      "instruction": "MOV EAX,dword ptr [ESP + 0x18]"
    },
    {
      "address": "00801b2c",
      "instruction": "MOV EDX,dword ptr [EBX]"
    },
    {
      "address": "00801b2e",
      "instruction": "MOV EDX,dword ptr [EDX + 0x24]"
    },
    {
      "address": "00801b31",
      "instruction": "PUSH 0x2393756"
    },
    {
      "address": "00801b36",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00801b37",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00801b38",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00801b39",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "00801b3b",
      "instruction": "CALL EDX"
    },
    {
      "address": "00801b3d",
      "instruction": "POP EDI"
    },
    {
      "address": "00801b3e",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00801b40",
      "instruction": "JZ 0x00801b57"
    },
    {
      "address": "00801b42",
      "instruction": "MOV EAX,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00801b46",
      "instruction": "MOV dword ptr [EAX],ESI"
    },
    {
      "address": "00801b48",
      "instruction": "MOV EDX,dword ptr [ESI]"
    },
    {
      "address": "00801b4a",
      "instruction": "MOV EAX,dword ptr [EDX]"
    },
    {
      "address": "00801b4c",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00801b4e",
      "instruction": "CALL EAX"
    },
    {
      "address": "00801b50",
      "instruction": "POP ESI"
    },
    {
      "address": "00801b51",
      "instruction": "MOV AL,0x1"
    },
    {
      "address": "00801b53",
      "instruction": "POP EBX"
    },
    {
      "address": "00801b54",
      "instruction": "RET 0x10"
    },
    {
      "address": "00801b57",
      "instruction": "POP ESI"
    },
    {
      "address": "00801b58",
      "instruction": "XOR AL,AL"
    },
    {
      "address": "00801b5a",
      "instruction": "POP EBX"
    },
    {
      "address": "00801b5b",
      "instruction": "RET 0x10"
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
  "original_bytes": 9347,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"x86-32 thiscall with first explicit cursor-manager receiver in ECX and caller cleanup\",\n    \"return_semantics\": \"byte in AL; one only after accepted dispatch\",\n    \"return_type\": \"std::uint8_t\",\n    \"stack_cleanup_bytes\": 16,\n    \"stack_cleanup_owner\": \"caller\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_core_wave6::CursorManager,openspore::reconstruction::pkg_utfwin_core_wave6::Drawable,openspore::reconstruction::pkg_utfwin_core_wave6::DropIconObject,openspore::reconstruction::pkg_utfwin_core_wave6::ResourceFactory\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"re_00575ea0\",\n      \"va\": \"0x00575ea0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_core_wave6::CursorManager,openspore::reconstruction::pkg_utfwin_core_wave6::Drawable,openspore::reconstruction::pkg_utfwin_core_wave6::DropIconObject,openspore::reconstruction::pkg_utfwin_core_wave6::ResourceFactory\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"re_00835380\",\n      \"va\": \"0x00835380\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_core_wave6::CursorManager,openspore::reconstruction::pkg_utfwin_core_wave6::Drawable,openspore::reconstruction::pkg_utfwin_core_wave6::DropIconObject,openspore::reconstruction::pkg_utfwin_core_wave6::ResourceFactory\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"re_00951220\",\n      \"va\": \"0x00951220\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_core_wave6::CursorManager,openspore::reconstruction::pkg_utfwin_core_wave6::Drawable,openspore::reconstruction::pkg_utfwin_core_wave6::DropIconObject,openspore::reconstruction::pkg_utfwin_core_wave6::ResourceFactory\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"re_00951230\",\n      \"va\": \"0x00951230\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_core_wave6::CursorManager,openspore::reconstruction::pkg_utfwin_core_wave6::Drawable,openspore::reconstruction::pkg_utfwin_core_wave6::DropIconObject,openspore::reconstruction::pkg_utfwin_core_wave6::ResourceFactory\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"re_00957510\",\n      \"va\": \"0x00957510\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_core_wave6::CursorManager,openspore::reconstruction::pkg_utfwin_core_wave6::Drawable,openspore::reconstruction::pkg_utfwin_core_wave6::DropIconObject,openspore::reconstruction::pkg_utfwin_core_wave6::ResourceFactory\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"re_0095f960\",\n      \"va\": \"0x0095f960\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_core_wave6::CursorManager,openspore::reconstruction::pkg_utfwin_core_wave6::Drawable,openspore::reconstruction::pkg_utfwin_core_wave6::DropIconObject,openspore::reconstruction::pkg_utfwin_core_wave6::ResourceFactory\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"re_0095f990\",\n      \"va\": \"0x0095f990\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_core_wave6::CursorManager,openspore::reconstruction::pkg_utfwin_core_wave6::Drawable,openspore::reconstruction::pkg_utfwin_core_wave6::DropIconObject,openspore::reconstruction::pkg_utfwin_core_wave6::ResourceFactory\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"re_0095f9a0\",\n      \"va\": \"0x0095f9a0\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Reviewed static mechanics and x86-32 ABI are preserved; opaque runtime ports and ownership remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": null,\n  \"cluster\": \"utfwin-framework\",\n  \"confidence\": 0.9,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"wave6_reference_00432a50\",\n        \"reconstructed\": true,\n        \"va\": \"0x00432a50\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00801b4e\",\n        \"direction\": \"out\",\n        \"other\": \"0x00432a50\",\n        \"reference_type\": \"computed-call\"\n      },\n      {\n        \"callsite\": \"0x00801adf\",\n        \"direction\": \"out\",\n        \"other\": \"0x00f473a0\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 1,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [\n      \"0x00432a50\"\n    ],\n    \"scc\": {\n      \"id\": \"scc-0256\",\n      \"size\": 1\n    },\n    \"vtable_
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
  "body_end": "00801b5d",
  "body_span_bytes": 158,
  "body_start": "00801ac0",
  "callees": [
    "FUN_00f473a0",
    "Reference"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00801ac0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "UTFWin::cCursorManager::ShowDropCursorIcon",
  "namespace": "UTFWin",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 2,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "cCursorManager *"
    },
    {
      "name": "visible",
      "ordinal": 1,
      "storage": "Stack[0x8]:1",
      "type": "bool"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "void",
  "return_type_resolved": true,
  "rva": "0x401ac0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "void UTFWin::cCursorManager::ShowDropCursorIcon(cCursorManager * this, bool visible)",
  "size_bytes": 158,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00801ac0",
  "vtables": {
    "referenced_by_vtables": [
      "0x01416fd4"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "01417004"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__cCursorManager__ShowDropCursorIcon.c",
  "file": "src/reconstruction/pkg_utfwin_core_wave6/utfwin_core_wave6.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__cCursorManager__ShowDropCursorIcon.c",
    "src/reconstruction/pkg_utfwin_core_wave6/utfwin_core_wave6.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-utfwin-core-wave6/00801ac0.json"
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
    "cursor allocator, resource factory, cursor vtable, icon dispatch, and output ownership remain gated",
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
  "openspore::reconstruction::pkg_utfwin_core_wave6::CursorManager",
  "openspore::reconstruction::pkg_utfwin_core_wave6::Drawable",
  "openspore::reconstruction::pkg_utfwin_core_wave6::DropIconObject",
  "openspore::reconstruction::pkg_utfwin_core_wave6::ResourceFactory",
  "openspore::reconstruction::pkg_utfwin_core_wave6::TooltipCore",
  "openspore::reconstruction::pkg_utfwin_core_wave6::WindowCore",
  "std::uint8_t"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x01416fd4"
]
```

## Conflicts

```json
[]
```
