# Evidence 0x0041e8b0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `5b9251a237bf07b467fa67e8e6edeed39154cef50cff2cb6e02fffb89b450ce4`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "thiscall with callee stack cleanup",
  "receiver_register": "ECX",
  "ret_form": "RET 0x4",
  "return_register": "EAX",
  "return_width_bytes": 0,
  "stack_arguments": [
    {
      "entry_offset": "EBP+0x08",
      "machine_type": "std::uint32_t",
      "native_reads": [
        "PUSH EAX at 0x0041e8ee for the copy port",
        "PUSH ECX at 0x0041e908 for the grow port"
      ],
      "normalized_name": "argument",
      "note": "the word is used as an opaque source pointer, not as a count",
      "position": 1,
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 4
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
        "ebp_offset": "EBP+0x8",
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
    "return_semantics": "unclassified_in_EAX",
    "saved_registers": [
      "EBP"
    ],
    "stack_arguments": [
      {
        "ebp_offset": "EBP+0x8",
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
  "content_sha256": "005e85225ac2a582ba4d7c7a3fc0fa5f31802dbff2b07a26c50fc0955a5b2acc",
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
    "ghidra_parameter_count": 0,
    "persisted": "no_information",
    "persisted_calling_convention": "thiscall with callee stack cleanup"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0032"
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
        "obs-0022",
        "obs-0027"
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
        "obs-0006",
        "obs-0007",
        "obs-0010",
        "obs-0011",
        "obs-0015",
        "obs-0018",
        "obs-0023",
        "obs-0027",
        "obs-0029"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          4
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007",
        "obs-0010",
        "obs-0011",
        "obs-0015",
        "obs-0018",
        "obs-0023",
        "obs-0027",
        "obs-0029",
        "obs-0032"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0032"
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
        "obs-0032"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0032"
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
      "at": "0x0041e8b0",
      "count": 19,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH EBP",
      "reg": "EBP"
    },
    {
      "and_esp": null,
      "at": "0x0041e8b0",
      "ebp_is_general_register": true,
      "fp": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": true,
      "mov_ebp_esp_at": 1,
      "push_ebp": true,
      "push_ebp_at": 0,
      "raw": "PUSH EBP",
      "sub": 24
    },
    {
      "at": "0x0041e8b1",
      "count": 1,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EBP,ESP",
      "reg": "ESP"
    },
    {
      "at": "0x0041e8b1",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EBP,ESP",
      "reg": "EBP",
      "write_kind": "reg"
    },
    {
      "at": "0x0041e8b3",
      "definite": true,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x18",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x0041e8b6",
      "count": 5,
      "first_use": 3,
      "first_write_index": 5,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV dword ptr [EBP + -0x14],ECX",
      "reg": "ECX"
    },
    {
      "at": "0x0041e8b6",
      "base": "EBP",
      "disp": -20,
      "id": "obs-0007",
      "index": 3,
      "key": null,
      "kind": "STACK_SLOT_WRITE",
      "raw": "MOV dword ptr [EBP + -0x14],ECX",
      "reason": "local",
      "resolved": false,
      "size": 4,
      "via": "direct"
    },
    {
      "at": "0x00
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
    "va": "0x00407280"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0041aaa0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0046aac0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00471000"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00471830"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00471b50"
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
  "count": 39,
  "instructions": [
    {
      "address": "0041e8b0",
      "instruction": "PUSH EBP"
    },
    {
      "address": "0041e8b1",
      "instruction": "MOV EBP,ESP"
    },
    {
      "address": "0041e8b3",
      "instruction": "SUB ESP,0x18"
    },
    {
      "address": "0041e8b6",
      "instruction": "MOV dword ptr [EBP + -0x14],ECX"
    },
    {
      "address": "0041e8b9",
      "instruction": "MOV EAX,dword ptr [EBP + -0x14]"
    },
    {
      "address": "0041e8bc",
      "instruction": "MOV ECX,dword ptr [EBP + -0x14]"
    },
    {
      "address": "0041e8bf",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "0041e8c2",
      "instruction": "CMP EDX,dword ptr [ECX + 0x8]"
    },
    {
      "address": "0041e8c5",
      "instruction": "JNC 0x0041e905"
    },
    {
      "address": "0041e8c7",
      "instruction": "MOV EAX,dword ptr [EBP + -0x14]"
    },
    {
      "address": "0041e8ca",
      "instruction": "MOV ECX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "0041e8cd",
      "instruction": "MOV dword ptr [EBP + -0x8],ECX"
    },
    {
      "address": "0041e8d0",
      "instruction": "MOV EDX,dword ptr [EBP + -0x14]"
    },
    {
      "address": "0041e8d3",
      "instruction": "MOV EAX,dword ptr [EDX + 0x4]"
    },
    {
      "address": "0041e8d6",
      "instruction": "ADD EAX,0x18"
    },
    {
      "address": "0041e8d9",
      "instruction": "MOV ECX,dword ptr [EBP + -0x14]"
    },
    {
      "address": "0041e8dc",
      "instruction": "MOV dword ptr [ECX + 0x4],EAX"
    },
    {
      "address": "0041e8df",
      "instruction": "MOV EDX,dword ptr [EBP + -0x8]"
    },
    {
      "address": "0041e8e2",
      "instruction": "MOV dword ptr [EBP + -0x4],EDX"
    },
    {
      "address": "0041e8e5",
      "instruction": "CMP dword ptr [EBP + -0x4],0x0"
    },
    {
      "address": "0041e8e9",
      "instruction": "JZ 0x0041e8fc"
    },
    {
      "address": "0041e8eb",
      "instruction": "MOV EAX,dword ptr [EBP + 0x8]"
    },
    {
      "address": "0041e8ee",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0041e8ef",
      "instruction": "MOV ECX,dword ptr [EBP + -0x4]"
    },
    {
      "address": "0041e8f2",
      "instruction": "CALL 0x00511140"
    },
    {
      "address": "0041e8f7",
      "instruction": "MOV dword ptr [EBP + -0x18],EAX"
    },
    {
      "address": "0041e8fa",
      "instruction": "JMP 0x0041e903"
    },
    {
      "address": "0041e8fc",
      "instruction": "MOV dword ptr [EBP + -0x18],0x0"
    },
    {
      "address": "0041e903",
      "instruction": "JMP 0x0041e918"
    },
    {
      "address": "0041e905",
      "instruction": "MOV ECX,dword ptr [EBP + 0x8]"
    },
    {
      "address": "0041e908",
      "instruction": "PUSH ECX"
    },
    {
      "address": "0041e909",
      "instruction": "MOV EDX,dword ptr [EBP + -0x14]"
    },
    {
      "address": "0041e90c",
      "instruction": "MOV EAX,dword ptr [EDX + 0x4]"
    },
    {
      "address": "0041e90f",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0041e910",
      "instruction": "MOV ECX,dword ptr [EBP + -0x14]"
    },
    {
      "address": "0041e913",
      "instruction": "CALL 0x00424010"
    },
    {
      "address": "0041e918",
      "instruction": "MOV ESP,EBP"
    },
    {
      "address": "0041e91a",
      "instruction": "POP EBP"
    },
    {
      "address": "0041e91b",
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
  "original_bytes": 9698,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"thiscall with callee stack cleanup\",\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET 0x4\",\n    \"return_register\": \"EAX\",\n    \"return_width_bytes\": 0,\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"EBP+0x08\",\n        \"machine_type\": \"std::uint32_t\",\n        \"native_reads\": [\n          \"PUSH EAX at 0x0041e8ee for the copy port\",\n          \"PUSH ECX at 0x0041e908 for the grow port\"\n        ],\n        \"normalized_name\": \"argument\",\n        \"note\": \"the word is used as an opaque source pointer, not as a count\",\n        \"position\": 1,\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 4\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE10\",\n      \"score\": 8,\n      \"symbol\": \"vector3_add_0041dc10\",\n      \"va\": \"0x0041dc10\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE10\",\n      \"score\": 8,\n      \"symbol\": \"property_value_resolve_0041e920\",\n      \"va\": \"0x0041e920\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:unsigned int\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-SKINNER-SAFE-WAVE10\",\n      \"score\": 5,\n      \"symbol\": \"skin_painter_state_setup_00506590\",\n      \"va\": \"0x00506590\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:unsigned int\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE10\",\n      \"score\": 5,\n      \"symbol\": \"editor_row_publish_005a2010\",\n      \"va\": \"0x005a2010\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:unsigned int\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-PALETTE-SAFE-WAVE10\",\n      \"score\": 5,\n      \"symbol\": \"page_visible_slots_refresh_005c0a60\",\n      \"va\": \"0x005c0a60\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:unsigned int\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-UI-SAFE-WAVE10\",\n      \"score\": 5,\n      \"symbol\": \"image_archive_scalar_deleting_destructor_00635700\",\n      \"va\": \"0x00635700\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:unsigned int\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 3,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:unsigned int\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 3,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Static x86-32 mechanics, register/stack argument contract, stack cleanup width, RET form, field offsets, constants, strides, vtable slot indices and the compiled terminator were read from the live Ghidra disassembly of SporeApp.exe and re-confirmed against the compiled reconstruction at -O0 and -O2 with and without NDEBUG. Imported SDK signatures are candidate labels only. Concrete vtable owners, port semantics, runtime values and ownership remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_semantic_abi_and_runtime_lifecycle_review\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueCursorBuffer\",\n  \"cluster\": null,\n  \"confidence\": 0.93,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00407280\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0041aaa0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0046aac0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00471000\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00471830\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00471b50\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00407b08\",\n        \"direction\": \"in\",\n        \"other\": \"0x00407280\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0041b1a4\",\n        \"direction\": \"in\",\n        \"other\": \"0x0041aaa0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0046adbd\",\n        \"direction\": \"in\",\n        \"other\": \"0x0046aac0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0047138a\",\n        \"direction\": \"in\",\n        \"other\": \"0x00471000\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00471a71\",\n        \"direction\": \"in\",\n        \"other\": \"0x00471830\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00471e13\",\n        \"direction\": \"in\",\n        \"other\": \"0x00471b50\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0041e913\",\n        \"direction\": \"out\",\n        \"other\": \"0x00424010\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0041e8f2\",\n        \"direction\": \"out\",\n        \"other\": \"0x00511140\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\"
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
  "body_end": "0041e91d",
  "body_span_bytes": 110,
  "body_start": "0041e8b0",
  "callees": [
    "FUN_00424010",
    "FUN_00511140"
  ],
  "callers": [
    "FUN_00471830",
    "FUN_00407280",
    "FUN_0046aac0",
    "FUN_00471000",
    "FUN_0041aaa0",
    "FUN_00471b50"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "0041e8b0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_8",
      "storage": "Stack[-0x8]:4",
      "type": "undefined4"
    },
    {
      "name": "local_c",
      "storage": "Stack[-0xc]:4",
      "type": "undefined4"
    },
    {
      "name": "local_18",
      "storage": "Stack[-0x18]:4",
      "type": "undefined4"
    },
    {
      "name": "local_1c",
      "storage": "Stack[-0x1c]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 4,
  "mode": "live",
  "name": "FUN_0041e8b0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x1e8b0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_0041e8b0(void)",
  "size_bytes": 110,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x0041e8b0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 6,
  "xrefs": [
    {
      "from": "0041b1a4"
    },
    {
      "from": "00407b08"
    },
    {
      "from": "0047138a"
    },
    {
      "from": "00471e13"
    },
    {
      "from": "00471a71"
    },
    {
      "from": "0046adbd"
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
  "file": "src/reconstruction/pkg_app_safe_wave10/app_safe_wave10.cpp",
  "files": [
    "src/reconstruction/pkg_app_safe_wave10/app_safe_wave10.cpp",
    "src/reconstruction/pkg_app_safe_wave10/app_safe_wave10.hpp",
    "src/reconstruction/pkg_app_safe_wave10/app_safe_wave10_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave10-safe-core/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-app-safe-wave10/0041e8b0.json"
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
    "The 0x18 element stride comes from the ADD EAX,0x18 immediate; the element size is not independently confirmed.",
    "The argument is modelled as an opaque source pointer; its declared type is unresolved.",
    "The cursor buffer base word at +0x00 is never read or written by this body.",
    "The element copy port 0x00511140 and the grow port 0x00424010 are opaque seams and are not promoted.",
    "gate-cursor-buffer-emit-runtime-port-semantics",
    "runtime validation not performed; static decompilation and disassembly only",
    "the 0x18 element stride is a static constant read from the ADD EAX,0x18 immediate; the element size is not independently confirmed",
    "the argument is modelled as an opaque source pointer; its declared type is unresolved",
    "the cursor buffer base word at +0x00 is never read or written by this body",
    "the element copy port 0x00511140 and the grow port 0x00424010 are opaque seams and are not promoted"
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
  "CursorRuntime",
  "OpaqueCursorBuffer",
  "OpaqueCursorBuffer*",
  "OpaqueCursorElement",
  "unsigned int",
  "void"
]
```

## vtables

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## Conflicts

```json
[]
```
