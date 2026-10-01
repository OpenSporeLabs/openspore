# Evidence 0x00b8dec0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `d39399214c42e3dc282b008eb528b7335d500cf3f9d44c76470f31d06dcbaa50`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_receiver": "owner of the element block at +0x15c",
  "hidden_this_register": "ECX, read at 0x00b8dec0",
  "ordinary_stack_argument_slots": 1,
  "receiver": true,
  "ret_form": "RET 0x4",
  "return_observation": "0x00b8dedd MOV EAX,dword ptr [ECX + EAX*0x4] loads the element into EAX; 0x00b8dee3 XOR EAX,EAX is the only other write, so the return is never a pointer.",
  "return_register": "EAX",
  "return_semantics": "the 4-byte element itself (by value in EAX), or 0 when the index is at or past the element count",
  "return_type": "std::int32_t",
  "return_width_bytes": 4,
  "saved_registers": [],
  "stack_arguments": [
    {
      "read_at": "0x00b8decc",
      "role": "signed 32-bit element index",
      "slot": "entry ESP+4"
    }
  ],
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "callee",
  "termination": "0x00b8dee0 RET 0x4 and 0x00b8dee5 RET 0x4"
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
  "content_sha256": "5f19b43ee05d9e9079a30960243ee5c358ef6e286821d0a24708f4135e572e19",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall"
    ],
    "confidence": "SUPPORTED",
    "corroboration": "persisted_agrees"
  },
  "cross_validation": {
    "agreement": true,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 0,
    "persisted": "agrees",
    "persisted_calling_convention": "__thiscall"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0009",
        "obs-0010"
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
        "obs-0007",
        "obs-0008"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          348,
          352
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0002",
        "obs-0007",
        "obs-0008",
        "obs-0009",
        "obs-0010"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0009",
        "obs-0010"
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
        "obs-0009",
        "obs-0010"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0009",
        "obs-0010"
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
      "at": "0x00b8dec0",
      "count": 4,
      "first_use": 0,
      "first_write_index": 6,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EDX,dword ptr [ECX + 0x160]",
      "reg": "ECX"
    },
    {
      "at": "0x00b8dec0",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [ECX + 0x160]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00b8decc",
      "count": 1,
      "first_use": 2,
      "first_write_index": null,
      "id": "obs-0003",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "ESP"
    },
    {
      "at": "0x00b8decc",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0004",
      "index": 2,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00b8decc",
      "definite": true,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00b8ded0",
      "count": 1,
      "first_use": 3,
      "first_write_index": 0,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_READ",
      "raw": "SAR EDX,0x2",
      "reg": "EDX"
    },
    {
      "at": "0x00b8ded7",
      "definite": true,
      "id": "obs-0007",
      "index": 6,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [ECX + 0x15c]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00b8dedd",
      "count": 2,
      "first_use": 7,
      "first_write_index": 2,
      "id": "obs-0008",
      "index": 7,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ECX + EAX*0x4]",
      "reg": "EAX"
    },
    {
      "at": "0x00b8dee0",
      "form": "RET 0x4",
      "id": "obs-0009",
      "imm": 4,
      "index": 8,
      "kind": "RET",
      "raw": 
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
    "va": "0x00c5c860"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c70260"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c704a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c705c0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c71030"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c71040"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c711e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c72030"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c72190"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c737a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c8b820"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c8b920"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c8ba00"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c8bb00"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c8c5d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c8c7f0"
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
  "count": 11,
  "instructions": [
    {
      "address": "00b8dec0",
      "instruction": "MOV EDX,dword ptr [ECX + 0x160]"
    },
    {
      "address": "00b8dec6",
      "instruction": "SUB EDX,dword ptr [ECX + 0x15c]"
    },
    {
      "address": "00b8decc",
      "instruction": "MOV EAX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "00b8ded0",
      "instruction": "SAR EDX,0x2"
    },
    {
      "address": "00b8ded3",
      "instruction": "CMP EAX,EDX"
    },
    {
      "address": "00b8ded5",
      "instruction": "JGE 0x00b8dee3"
    },
    {
      "address": "00b8ded7",
      "instruction": "MOV ECX,dword ptr [ECX + 0x15c]"
    },
    {
      "address": "00b8dedd",
      "instruction": "MOV EAX,dword ptr [ECX + EAX*0x4]"
    },
    {
      "address": "00b8dee0",
      "instruction": "RET 0x4"
    },
    {
      "address": "00b8dee3",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "00b8dee5",
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
  "original_bytes": 12095,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_receiver\": \"owner of the element block at +0x15c\",\n    \"hidden_this_register\": \"ECX, read at 0x00b8dec0\",\n    \"ordinary_stack_argument_slots\": 1,\n    \"receiver\": true,\n    \"ret_form\": \"RET 0x4\",\n    \"return_observation\": \"0x00b8dedd MOV EAX,dword ptr [ECX + EAX*0x4] loads the element into EAX; 0x00b8dee3 XOR EAX,EAX is the only other write, so the return is never a pointer.\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"the 4-byte element itself (by value in EAX), or 0 when the index is at or past the element count\",\n    \"return_type\": \"std::int32_t\",\n    \"return_width_bytes\": 4,\n    \"saved_registers\": [],\n    \"stack_arguments\": [\n      {\n        \"read_at\": \"0x00b8decc\",\n        \"role\": \"signed 32-bit element index\",\n        \"slot\": \"entry ESP+4\"\n      }\n    ],\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"0x00b8dee0 RET 0x4 and 0x00b8dee5 RET 0x4\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"model_parts_apply_properties_00447150\",\n      \"va\": \"0x00447150\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_insert_004786e0\",\n      \"va\": \"0x004786e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_entry_expand_004ad6f0\",\n      \"va\": \"0x004ad6f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 2,\n      \"symbol\": \"Editors_EditorModel_SetColor_raw_004ae250\",\n      \"va\": \"0x004ae250\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_construct_004b62a0\",\n      \"va\": \"0x004b62a0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c5c860\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c70260\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c704a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c705c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c71030\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c71040\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c711e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c72030\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c72190\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c737a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c8b820\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c8b920\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c8ba00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c8bb00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c8c5d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c8c7f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c8c9d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c8cb20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00fe0570\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0100a160\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0100a960\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x010103f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0103ad50\"\n 
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
  "body_end": "00b8dee7",
  "body_span_bytes": 40,
  "body_start": "00b8dec0",
  "callees": [],
  "callers": [
    "FUN_00c705c0",
    "FUN_00c711e0",
    "FUN_00c72030",
    "FUN_00c704a0",
    "FUN_00c8ba00",
    "FUN_00c8cb20",
    "FUN_0103af90",
    "FUN_00c71040",
    "FUN_0100a160",
    "FUN_00c737a0",
    "FUN_00c5c860",
    "FUN_0103ad50",
    "FUN_00c8c7f0",
    "FUN_00c8bb00",
    "FUN_0100a960",
    "FUN_00c8b920",
    "FUN_00fe0570",
    "FUN_00c8c5d0",
    "FUN_010103f0",
    "FUN_00c71030",
    "FUN_00c8b820",
    "FUN_00c8c9d0",
    "FUN_00c72190",
    "FUN_00c70260"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "00b8dec0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00b8dec0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x78dec0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00b8dec0(void)",
  "size_bytes": 40,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00b8dec0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 27,
  "xrefs": [
    {
      "from": "00c7380e"
    },
    {
      "from": "00c8b983"
    },
    {
      "from": "00c71077"
    },
    {
      "from": "00c8bb8a"
    },
    {
      "from": "00c8c687"
    },
    {
      "from": "00c8cabd"
    },
    {
      "from": "00c8cd29"
    },
    {
      "from": "00c70625"
    },
    {
      "from": "0100aa29"
    },
    {
      "from": "00c8b8a7"
    },
    {
      "from": "00c8c875"
    },
    {
      "from": "00c71218"
    },
    {
      "from": "00c5cb9d"
    },
    {
      "from": "00c70507"
    },
    {
      "from": "00c7211f"
    },
    {
      "from": "00c722c0"
    },
    {
      "from": "0103ad7a"
    },
    {
      "from": "0100a3de"
    },
    {
      "from": "0100a41d"
    },
    {
      "from": "0103aff3"
    },
    {
      "from": "0103b03d"
    },
    {
      "from": "01010437"
    },
    {
      "from": "00c71036"
    },
    {
      "from": "00fe07c7"
    },
    {
      "from": "00c70295"
    },
    {
      "from": "00cfffcf"
    },
    {
      "from": "00c8ba66"
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
  "files": [
    "reconstruction/staging/wave13-w1-core-b07/00b8dec0_indexed_element_accessor.cpp",
    "reconstruction/staging/wave13-w1-core-b07/b07_model_test.cpp",
    "reconstruction/staging/wave13-w1-core-b07/b07_opaque_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-core-b07/00b8dec0.json"
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
    "No original-process trace exists for this address.",
    "The element type and the owning class can only be settled with a receiver trace or by inspecting the 22 remaining call sites."
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
  "status": "unresolved"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "std::int32_t"
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
