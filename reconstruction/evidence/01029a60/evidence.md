# Evidence 0x01029a60

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `60aeff00c881f004f538a1d0823839c79310a58c71520938a0b00b0bdd56234c`

## abi

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
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      }
    ],
    "ret_form": "RET",
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
        "entry_offset": "entry_ESP+0x8",
        "observed": true,
        "ordinal": 2,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      }
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +4, so the listing is not one path",
    "receiver_not_determinable: ecx_reassigned_before_deref",
    "variadic_not_decidable_from_listing: no caller-side va_list construction is visible",
    "variadic_caps_convention: variadic suspicion removes any guarantee about the stack-argument extent"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate",
    "side": "caller"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "3f0ce13564eb21136fed7f6bd9d025cbec620ccab39378efa9089c37a66a34fa",
  "conventions": {
    "ambiguities": [
      "variadic_suspected"
    ],
    "calling_convention": null,
    "candidate_conventions": [
      "__cdecl"
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
    "indirect_calls": 2,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0028",
        "obs-0031"
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
        "obs-0004",
        "obs-0006"
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
        "obs-0011",
        "obs-0020"
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
        "obs-0017"
      ],
      "claim": "the calling convention is not decidable from the listing",
      "confidence": "UNKNOWN",
      "id": "C12"
    },
    {
      "based_on": [
        "obs-0028",
        "obs-0031"
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
        "obs-0028",
        "obs-0031"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0028",
        "obs-0031"
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
      "at": "0x01029a60",
      "count": 1,
      "first_use": 0,
      "first_write_index": 5,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x01029a61",
      "count": 7,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x01029a62",
      "count": 2,
      "first_use": 2,
      "first_write_index": null,
      "id": "obs-0003",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV ESI,dword ptr [ESP + 0xc]",
      "reg": "ESP"
    },
    {
      "at": "0x01029a62",
      "base": "ESP",
      "disp": 12,
      "id": "obs-0004",
      "index": 2,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV ESI,dword ptr [ESP + 0xc]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x01029a62",
      "definite": true,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,dword ptr [ESP + 0xc]",
      "reg": "ESI",
      "write_kind": "mem_load"
    },
    {
      "at": "0x01029a6f",
      "base": "ESP",
      "disp": 16,
      "id": "obs-0006",
      "index": 5,
      "key": 8,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV BL,byte ptr [ESP + 0x10]",
      "resolved": true,
      "size": 1
    },
    {
      "at": "0x01029a6f",
      "def
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
"\nundefined1 FUN_01029a60(int *param_1,char param_2)\n\n{\n  int iVar1;\n  char cVar2;\n  undefined4 uVar3;\n  int iVar4;\n  undefined1 uVar5;\n  \n  if (param_1[0x1c5] != 6) {\n    uVar3 = (**(code **)(*param_1 + 0x4c))();\n    FUN_00b3d2a0(uVar3);\n    iVar4 = FUN_00ba9370(uVar3);\n    if ((iVar4 == 0) || (cVar2 = FUN_00c309e0(), cVar2 != '\\0')) {\n      param_2 = '\\x01';\n    }\n    else {\n      param_2 = '\\0';\n    }\n  }\n  FUN_00ffbe50();\n  iVar4 = FUN_00a1ad60();\n  if (param_2 == '\\0') {\n    iVar1 = param_1[0x151];\n    iVar4 = (**(code **)(*(int *)(iVar4 + 0x508) + 0x10))();\n    uVar5 = 0;\n    if (iVar1 != iVar4) goto LAB_01029acb;\n  }\n  uVar5 = 1;\nLAB_01029acb:\n  if (param_1[0x1b2] != 0) {\n    iVar4 = FUN_00bc96a0(0x10,0);\n    if (iVar4 != 0) {\n      return 0;\n    }\n  }\n  return uVar5;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 56,
  "instructions": [
    {
      "address": "01029a60",
      "instruction": "PUSH EBX"
    },
    {
      "address": "01029a61",
      "instruction": "PUSH ESI"
    },
    {
      "address": "01029a62",
      "instruction": "MOV ESI,dword ptr [ESP + 0xc]"
    },
    {
      "address": "01029a66",
      "instruction": "CMP dword ptr [ESI + 0x714],0x6"
    },
    {
      "address": "01029a6d",
      "instruction": "JNZ 0x01029a75"
    },
    {
      "address": "01029a6f",
      "instruction": "MOV BL,byte ptr [ESP + 0x10]"
    },
    {
      "address": "01029a73",
      "instruction": "JMP 0x01029aa0"
    },
    {
      "address": "01029a75",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "01029a77",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4c]"
    },
    {
      "address": "01029a7a",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "01029a7c",
      "instruction": "CALL EDX"
    },
    {
      "address": "01029a7e",
      "instruction": "PUSH EAX"
    },
    {
      "address": "01029a7f",
      "instruction": "CALL 0x00b3d2a0"
    },
    {
      "address": "01029a84",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "01029a86",
      "instruction": "CALL 0x00ba9370"
    },
    {
      "address": "01029a8b",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "01029a8d",
      "instruction": "JZ 0x01029a9e"
    },
    {
      "address": "01029a8f",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "01029a91",
      "instruction": "CALL 0x00c309e0"
    },
    {
      "address": "01029a96",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "01029a98",
      "instruction": "JNZ 0x01029a9e"
    },
    {
      "address": "01029a9a",
      "instruction": "XOR BL,BL"
    },
    {
      "address": "01029a9c",
      "instruction": "JMP 0x01029aa0"
    },
    {
      "address": "01029a9e",
      "instruction": "MOV BL,0x1"
    },
    {
      "address": "01029aa0",
      "instruction": "CALL 0x00ffbe50"
    },
    {
      "address": "01029aa5",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "01029aa7",
      "instruction": "CALL 0x00a1ad60"
    },
    {
      "address": "01029aac",
      "instruction": "TEST BL,BL"
    },
    {
      "address": "01029aae",
      "instruction": "JNZ 0x01029ac9"
    },
    {
      "address": "01029ab0",
      "instruction": "LEA ECX,[EAX + 0x508]"
    },
    {
      "address": "01029ab6",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "01029ab8",
      "instruction": "MOV EDX,dword ptr [EAX + 0x10]"
    },
    {
      "address": "01029abb",
      "instruction": "PUSH EDI"
    },
    {
      "address": "01029abc",
      "instruction": "MOV EDI,dword ptr [ESI + 0x544]"
    },
    {
      "address": "01029ac2",
      "instruction": "CALL EDX"
    },
    {
      "address": "01029ac4",
      "instruction": "CMP EDI,EAX"
    },
    {
      "address": "01029ac6",
      "instruction": "POP EDI"
    },
    {
      "address": "01029ac7",
      "instruction": "JNZ 0x01029acb"
    },
    {
      "address": "01029ac9",
      "instruction": "MOV BL,0x1"
    },
    {
      "address": "01029acb",
      "instruction": "MOV ESI,dword ptr [ESI + 0x6c8]"
    },
    {
      "address": "01029ad1",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "01029ad3",
      "instruction": "JZ 0x01029aea"
    },
    {
      "address": "01029ad5",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "01029ad7",
      "instruction": "PUSH 0x10"
    },
    {
      "address": "01029ad9",
      "instruction": "LEA ECX,[ESI + 0x8]"
    },
    {
      "address": "01029adc",
      "instruction": "CALL 0x00bc96a0"
    },
    {
      "address": "01029ae1",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "01029ae3",
      "instruction": "JZ 0x01029aea"
    },
    {
      "address": "01029ae5",
      "instruction": "POP ESI"
    },
    {
      "address": "01029ae6",
      "instruction": "XOR AL,AL"
    },
    {
      "address": "01029ae8",
      "instruction": "POP EBX"
    },
    {
      "address": "01029ae9",
      "instruction": "RET"
    },
    {
      "address": "01029aea",
      "instruction": "POP ESI"
    },
    {
      "address": "01029aeb",
      "instruction": "MOV AL,BL"
    },
    {
      "address": "01029aed",
      "instruction": "POP EBX"
    },
    {
      "address": "01029aee",
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
  "body_end": "01029aee",
  "body_span_bytes": 143,
  "body_start": "01029a60",
  "callees": [
    "FUN_00c309e0",
    "FUN_00ffbe50",
    "FUN_00ba9370",
    "FUN_00a1ad60",
    "FUN_00b3d2a0",
    "FUN_00bc96a0"
  ],
  "callers": [
    "FUN_0102aa50",
    "FUN_0102c720"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "01029a60",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "iVar1",
      "storage": "unique:00017200:4",
      "type": "int"
    },
    {
      "name": "cVar2",
      "storage": "register:00000000:1",
      "type": "char"
    },
    {
      "name": "param_1",
      "storage": "Stack[0x4]:4",
      "type": "int *"
    },
    {
      "name": "param_2",
      "storage": "Stack[0x8]:1",
      "type": "char"
    },
    {
      "name": "uVar5",
      "storage": "register:0000000c:1",
      "type": "undefined1"
    },
    {
      "name": "uVar3",
      "storage": "register:00000000:4",
      "type": "undefined4"
    },
    {
      "name": "iVar4",
      "storage": "register:00000000:4",
      "type": "int"
    }
  ],
  "locals_count": 7,
  "mode": "live",
  "name": "FUN_01029a60",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xc29a60",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_01029a60(void)",
  "size_bytes": 143,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x01029a60",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 4,
  "xrefs": [
    {
      "from": "0102c7b8"
    },
    {
      "from": "0102aad7"
    },
    {
      "from": "0102ab48"
    },
    {
      "from": "0102abbd"
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
