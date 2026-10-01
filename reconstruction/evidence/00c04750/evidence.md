# Evidence 0x00c04750

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `082f87eeaa83fa92eee8c71d27b6a4d13c2889ac48d1fe7cc1570c359566a855`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_receiver": "owner of the id at +0x1c, forwarded as ECX to 0x00b18530",
  "hidden_this_register": "ECX, saved to ESI at 0x00c04751",
  "ordinary_stack_argument_slots": 0,
  "receiver": true,
  "ret_form": "RET",
  "return_observation": "0x00c04779 IMUL EAX,EAX,0x4e0 and 0x00c0477f ADD EAX,dword ptr [ESI + 0x70] build the value; the only other exit is 0x00c04784 XOR EAX,EAX.",
  "return_register": "EAX",
  "return_semantics": "a pointer computed as index * 0x4e0 + the word at subObject + 0x70, or 0 when either guard fails",
  "return_type": "std::uint32_t",
  "return_width_bytes": 4,
  "saved_registers": [
    "ESI"
  ],
  "stack_arguments": [],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller (nothing is pushed at entry)",
  "termination": "0x00c04783 RET and 0x00c04787 RET"
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
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
    "saved_registers": [
      "ESI"
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -4, so the listing is not one path",
    "receiver_not_determinable: ecx_read_without_deref",
    "no_discriminator: no stack-argument read and no positive receiver evidence"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "8d57cd448d2a88d86d04607055ad038df54495e414c55212219d7078f7eee525",
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
    "ghidra_parameter_count": 0,
    "persisted": "no_information",
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
        "obs-0011",
        "obs-0013"
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
        "obs-0002",
        "obs-0003",
        "obs-0005"
      ],
      "claim": "the register receiver is undetermined: ecx_read_without_deref",
      "confidence": "UNKNOWN",
      "id": "R0",
      "value": {
        "reason": "ecx_read_without_deref",
        "register": null
      }
    },
    {
      "based_on": [
        "obs-0013"
      ],
      "claim": "the function is byte-identical under all four conventions",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0011",
        "obs-0013"
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
        "obs-0011",
        "obs-0013"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0011",
        "obs-0013"
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
      "at": "0x00c04750",
      "count": 3,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00c04751",
      "count": 1,
      "first_use": 1,
      "first_write_index": 5,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00c04751",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00c04753",
      "id": "obs-0004",
      "index": 2,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00b5b800",
      "target": "0x00b5b800"
    },
    {
      "at": "0x00c0475f",
      "definite": true,
      "id": "obs-0005",
      "index": 5,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,ESI",
      "reg": "ECX",
      "write_kind": "reg"
    },
    {
      "at": "0x00c04761",
      "id": "obs-0006",
      "index": 6,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00b18530",
      "target": "0x00b18530"
    },
    {
      "at": "0x00c04766",
      "count": 4,
      "first_use": 7,
      "first_write_index": 10,
      "id": "obs-0007",
      "index": 7,
      "kind": "REG_READ",
      "raw": "MOV ESI,EAX",
      "reg": "EAX"
    },
    {
      "at": "0x00c0476c",
      "definite": true,
      "id": "obs-0008",
      "index": 10,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,[0x016c7aa4]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00c04774",
      "id": "obs-0009",
      "index": 12,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00f3c0e0",
      "target": "0x00f3c0e0"
    },
    {
      "at": "0x00c04782",
      "id": "obs-0010",
      "index": 15,
      "kind": "REG_RESTORE",
      "raw": "POP ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00c04783",
      "form": "RET",
      "id": "obs-0011",
      "imm": null,
      "index": 16,
      "kind": "RET",
      "raw": "RET"
    },
    {
      "at": "0x00c04786",
      "id": "obs-0012",
      "index": 18,
      "kind": "REG_RESTORE",
      "raw": "POP ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00c04787",
      "form": "RET",
      "id": "obs-0013",
      "imm": null,
      "index": 19,
      "kind": "RET",
      "raw": "RET"
    }
  ],
  "parse": {
    "declared_count": 20,
    "degraded": false,
    "esp_unresolved": false,
    "flow_complete": false,
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

[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "FUN_00b5b800",
    "reconstructed": false,
    "va": "0x00b5b800"
  }
]
```

## callers_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b682a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c04790"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c0cdb0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c0e4f0"
  },
  {
    "name": "FUN_00c14750",
    "reconstructed": false,
    "va": "0x00c14750"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c20230"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d2ffd0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d85c00"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ec0530"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ec2a70"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ec2f30"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ec3880"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00f07e10"
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
  "count": 20,
  "instructions": [
    {
      "address": "00c04750",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00c04751",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00c04753",
      "instruction": "CALL 0x00b5b800"
    },
    {
      "address": "00c04758",
      "instruction": "CMP EAX,0x1654c10"
    },
    {
      "address": "00c0475d",
      "instruction": "JNZ 0x00c04784"
    },
    {
      "address": "00c0475f",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00c04761",
      "instruction": "CALL 0x00b18530"
    },
    {
      "address": "00c04766",
      "instruction": "MOV ESI,EAX"
    },
    {
      "address": "00c04768",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "00c0476a",
      "instruction": "JZ 0x00c04784"
    },
    {
      "address": "00c0476c",
      "instruction": "MOV EAX,[0x016c7aa4]"
    },
    {
      "address": "00c04771",
      "instruction": "MOV ECX,dword ptr [EAX + 0x74]"
    },
    {
      "address": "00c04774",
      "instruction": "CALL 0x00f3c0e0"
    },
    {
      "address": "00c04779",
      "instruction": "IMUL EAX,EAX,0x4e0"
    },
    {
      "address": "00c0477f",
      "instruction": "ADD EAX,dword ptr [ESI + 0x70]"
    },
    {
      "address": "00c04782",
      "instruction": "POP ESI"
    },
    {
      "address": "00c04783",
      "instruction": "RET"
    },
    {
      "address": "00c04784",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "00c04786",
      "instruction": "POP ESI"
    },
    {
      "address": "00c04787",
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
  "original_bytes": 10442,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_receiver\": \"owner of the id at +0x1c, forwarded as ECX to 0x00b18530\",\n    \"hidden_this_register\": \"ECX, saved to ESI at 0x00c04751\",\n    \"ordinary_stack_argument_slots\": 0,\n    \"receiver\": true,\n    \"ret_form\": \"RET\",\n    \"return_observation\": \"0x00c04779 IMUL EAX,EAX,0x4e0 and 0x00c0477f ADD EAX,dword ptr [ESI + 0x70] build the value; the only other exit is 0x00c04784 XOR EAX,EAX.\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"a pointer computed as index * 0x4e0 + the word at subObject + 0x70, or 0 when either guard fails\",\n    \"return_type\": \"std::uint32_t\",\n    \"return_width_bytes\": 4,\n    \"saved_registers\": [\n      \"ESI\"\n    ],\n    \"stack_arguments\": [],\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller (nothing is pushed at entry)\",\n    \"termination\": \"0x00c04783 RET and 0x00c04787 RET\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"model_parts_apply_properties_00447150\",\n      \"va\": \"0x00447150\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_insert_004786e0\",\n      \"va\": \"0x004786e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_entry_expand_004ad6f0\",\n      \"va\": \"0x004ad6f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 2,\n      \"symbol\": \"Editors_EditorModel_SetColor_raw_004ae250\",\n      \"va\": \"0x004ae250\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_construct_004b62a0\",\n      \"va\": \"0x004b62a0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"FUN_00b5b800\",\n        \"reconstructed\": false,\n        \"va\": \"0x00b5b800\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b682a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c04790\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c0cdb0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c0e4f0\"\n      },\n      {\n        \"name\": \"FUN_00c14750\",\n        \"reconstructed\": false,\n        \"va\": \"0x00c14750\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c20230\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d2ffd0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d85c00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ec0530\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ec2a70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ec2f30\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ec3880\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00f07e10\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00b68304\",\n        \"direction\": \"in\",\n        \"other\": \"0x00b682a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c047ac\",\n        \"direction\": \"in\",\n        \"other\": \"0x00c04790\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c047b7\",\n        \"direction\": \"in\",\n        \"other\": \"0x00c04790\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c0cddd\",\n        \"direction\": \"in\",\n        \"other\": \"0x00c0cdb0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c0e534\",\n        \"direction\": \"in\",\n        \"other\": \"0x00c0e4f0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c147b0\",\n        \"direction\": \"in\",\n        \"other\": \"0x00c147
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
  "body_end": "00c04787",
  "body_span_bytes": 56,
  "body_start": "00c04750",
  "callees": [
    "FUN_00f3c0e0",
    "FUN_00b5b800",
    "FUN_00b18530"
  ],
  "callers": [
    "FUN_00ec2f30",
    "FUN_00c20230",
    "FUN_00c14750",
    "FUN_00d85c00",
    "FUN_00c0e4f0",
    "FUN_00f07e10",
    "FUN_00ec0530",
    "FUN_00d2ffd0",
    "FUN_00c0cdb0",
    "FUN_00ec2a70",
    "FUN_00c04790",
    "FUN_00ec3880",
    "FUN_00b682a0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00c04750",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00c04750",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x804750",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00c04750(void)",
  "size_bytes": 56,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00c04750",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 19,
  "xrefs": [
    {
      "from": "00c0cddd"
    },
    {
      "from": "00c147b0"
    },
    {
      "from": "00b68304"
    },
    {
      "from": "00c0e534"
    },
    {
      "from": "00c047ac"
    },
    {
      "from": "00c047b7"
    },
    {
      "from": "00d30194"
    },
    {
      "from": "00d3019f"
    },
    {
      "from": "00c20525"
    },
    {
      "from": "00d85ce5"
    },
    {
      "from": "00ec053a"
    },
    {
      "from": "00ec2c91"
    },
    {
      "from": "00ec2ca1"
    },
    {
      "from": "00ec2cb1"
    },
    {
      "from": "00ec2f3a"
    },
    {
      "from": "00ec39a0"
    },
    {
      "from": "00ec39b0"
    },
    {
      "from": "00f07e54"
    },
    {
      "from": "00f07e5f"
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
    "reconstruction/staging/wave13-w1-core-b07/00c04750_record_pointer_by_index.cpp",
    "reconstruction/staging/wave13-w1-core-b07/b07_model_test.cpp",
    "reconstruction/staging/wave13-w1-core-b07/b07_opaque_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-core-b07/00c04750.json"
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
    "The record type, the index semantics and the mode guard's intent can only be settled with a runtime trace that exercises the accessor in its live mode."
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
  "std::uint32_t"
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
