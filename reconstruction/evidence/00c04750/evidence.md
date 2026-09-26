# Evidence 0x00c04750

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `c77a2f7bf5752a2cbf8dc40c369f13b93f1ea20278285aa1cd4924296d6f1d72`

## abi

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
  "content_sha256": "2bc8b905c10a603c86aa96fd59910252d641358efc3555bc5ea7d4d9327fcdcd",
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
    "persisted_calling_convention": null
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
  },
  "
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

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json
"\nint FUN_00c04750(void)\n\n{\n  undefined *puVar1;\n  int iVar2;\n  int iVar3;\n  \n  puVar1 = (undefined *)FUN_00b5b800();\n  if (puVar1 == &DAT_01654c10) {\n    iVar2 = FUN_00b18530();\n    if (iVar2 != 0) {\n      iVar3 = FUN_00f3c0e0();\n      return iVar3 * 0x4e0 + *(int *)(iVar2 + 0x70);\n    }\n  }\n  return 0;\n}\n\n"
```

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

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

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
    "FUN_00b18530",
    "FUN_00b5b800"
  ],
  "callers": [
    "FUN_00c0e4f0",
    "FUN_00ec3880",
    "FUN_00b682a0",
    "FUN_00d85c00",
    "FUN_00ec2a70",
    "FUN_00c04790",
    "FUN_00c0cdb0",
    "FUN_00d2ffd0",
    "FUN_00c20230",
    "FUN_00c14750",
    "FUN_00ec2f30",
    "FUN_00f07e10",
    "FUN_00ec0530"
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
  "locals": [
    {
      "name": "iVar3",
      "storage": "register:00000000:4",
      "type": "int"
    },
    {
      "name": "iVar2",
      "storage": "register:00000000:4",
      "type": "int"
    },
    {
      "name": "puVar1",
      "storage": "register:00000000:4",
      "type": "undefined *"
    }
  ],
  "locals_count": 3,
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

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## runtime

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## runtime_metadata

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## semantic_hypotheses

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

## status

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## types

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## vtables

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## Conflicts

```json
[]
```
