# Evidence 0x00ba5e10

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `25428a60e4926e6cc7235bea372d876544a5b12ba7695b1049c2de043eb196f4`

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
      "entry_ESP+0xc"
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
      }
    ],
    "ret_form": "RET",
    "return_register": "ST0",
    "return_semantics": "float_or_x87_in_ST0",
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
      }
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -28, so the listing is not one path",
    "slot_gaps_present: argument ordinal(s) below the highest read slot are never touched",
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
  "content_sha256": "ac44eb0b24b43e01c52ee8244352720ad38285127790c0dc54e71d3a71550ba8",
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
    "indirect_calls": 4,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0008",
        "obs-0029",
        "obs-0036",
        "obs-0041"
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
        "obs-0003",
        "obs-0009"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 1,
        "observed_slots": 2,
        "total_bytes": 12
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
        "obs-0021",
        "obs-0024",
        "obs-0031"
      ],
      "claim": "the calling convention is not decidable from the listing",
      "confidence": "UNKNOWN",
      "id": "C12"
    },
    {
      "based_on": [
        "obs-0008",
        "obs-0029",
        "obs-0036",
        "obs-0041"
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
        "obs-0041"
      ],
      "claim": "the return value is carried in ST0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "ST0"
    }
  ],
  "observations": [
    {
      "at": "0x00ba5e10",
      "count": 12,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00ba5e11",
      "count": 2,
      "first_use": 1,
      "first_write_index": 15,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ESI,dword ptr [ESP + 0x8]",
      "reg": "ESP"
    },
    {
      "at": "0x00ba5e11",
      "base": "ESP",
      "disp": 8,
      "id": "obs-0003",
      "index": 1,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV ESI,dword ptr [ESP + 0x8]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00ba5e11",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,dword ptr [ESP + 0x8]",
      "reg": "ESI",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00ba5e19",
      "count": 9,
      "first_use": 4,
      "first_write_index": 4,
      "id": "obs-0005",
      "index": 4,
      "kind": "REG_READ",
      "raw": "XOR EAX,EAX",
      "reg": "EAX"
    },
    {
      "at": "0x00ba5e19",
      "definite": true,
      "id": "obs-0006",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "XOR EAX,EAX",
      "reg": "EAX",
      "write_kind": "zero"
    },
    {
      "at": "0x00ba5e1b",
      "id": "obs-0007",
      "index": 5,
      "kind": "REG_RESTORE",

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
"\nint FUN_00ba5e10(int *param_1,undefined4 param_2)\n\n{\n  char cVar1;\n  undefined4 uVar2;\n  int iVar3;\n  float10 fVar4;\n  \n  if (param_1 == (int *)0x0) {\n    return 0;\n  }\n  uVar2 = FUN_00c0bc00(param_2);\n  iVar3 = FUN_00ba5650(uVar2);\n  if (iVar3 != 0) {\n    uVar2 = (**(code **)(*param_1 + 0x4c))();\n    *(undefined4 *)(*(int *)(iVar3 + 0xc) + 0x24) = uVar2;\n    cVar1 = FUN_00c0c0e0();\n    if (cVar1 != '\\0') {\n      fVar4 = (float10)(**(code **)(param_1[0x16a] + 0x58))();\n      *(float *)(*(int *)(iVar3 + 0xc) + 0x2c) = (float)fVar4;\n      *(undefined4 *)(*(int *)(iVar3 + 0xc) + 0x1c) = 2;\n      return iVar3;\n    }\n    cVar1 = FUN_00c0c100();\n    if (cVar1 != '\\0') {\n      fVar4 = (float10)(**(code **)(param_1[0x16a] + 0x58))();\n      *(float *)(*(int *)(iVar3 + 0xc) + 0x2c) = (float)fVar4;\n      *(undefined4 *)(*(int *)(iVar3 + 0xc) + 0x1c) = 3;\n      return iVar3;\n    }\n    fVar4 = (float10)(**(code **)(*param_1 + 0x7c))();\n    *(float *)(*(int *)(iVar3 + 0xc) + 0x2c) = (float)fVar4;\n    *(undefined4 *)(*(int *)(iVar3 + 0xc) + 0x1c) = 1;\n  }\n  return iVar3;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 75,
  "instructions": [
    {
      "address": "00ba5e10",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00ba5e11",
      "instruction": "MOV ESI,dword ptr [ESP + 0x8]"
    },
    {
      "address": "00ba5e15",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "00ba5e17",
      "instruction": "JNZ 0x00ba5e1d"
    },
    {
      "address": "00ba5e19",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "00ba5e1b",
      "instruction": "POP ESI"
    },
    {
      "address": "00ba5e1c",
      "instruction": "RET"
    },
    {
      "address": "00ba5e1d",
      "instruction": "MOV EAX,dword ptr [ESP + 0xc]"
    },
    {
      "address": "00ba5e21",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00ba5e22",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00ba5e23",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00ba5e25",
      "instruction": "CALL 0x00c0bc00"
    },
    {
      "address": "00ba5e2a",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00ba5e2b",
      "instruction": "CALL 0x00ba5650"
    },
    {
      "address": "00ba5e30",
      "instruction": "MOV EDI,EAX"
    },
    {
      "address": "00ba5e32",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "00ba5e35",
      "instruction": "TEST EDI,EDI"
    },
    {
      "address": "00ba5e37",
      "instruction": "JZ 0x00ba5ece"
    },
    {
      "address": "00ba5e3d",
      "instruction": "MOV EDX,dword ptr [ESI]"
    },
    {
      "address": "00ba5e3f",
      "instruction": "MOV EAX,dword ptr [EDX + 0x4c]"
    },
    {
      "address": "00ba5e42",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00ba5e43",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00ba5e45",
      "instruction": "CALL EAX"
    },
    {
      "address": "00ba5e47",
      "instruction": "MOV ECX,dword ptr [EDI + 0xc]"
    },
    {
      "address": "00ba5e4a",
      "instruction": "MOV dword ptr [ECX + 0x24],EAX"
    },
    {
      "address": "00ba5e4d",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00ba5e4f",
      "instruction": "MOV EBX,0x1"
    },
    {
      "address": "00ba5e54",
      "instruction": "CALL 0x00c0c0e0"
    },
    {
      "address": "00ba5e59",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00ba5e5b",
      "instruction": "JZ 0x00ba5e85"
    },
    {
      "address": "00ba5e5d",
      "instruction": "MOV EDX,dword ptr [ESI + 0x5a8]"
    },
    {
      "address": "00ba5e63",
      "instruction": "MOV EAX,dword ptr [EDX + 0x58]"
    },
    {
      "address": "00ba5e66",
      "instruction": "LEA ECX,[ESI + 0x5a8]"
    },
    {
      "address": "00ba5e6c",
      "instruction": "MOV EBX,0x2"
    },
    {
      "address": "00ba5e71",
      "instruction": "CALL EAX"
    },
    {
      "address": "00ba5e73",
      "instruction": "MOV ECX,dword ptr [EDI + 0xc]"
    },
    {
      "address": "00ba5e76",
      "instruction": "FSTP float ptr [ECX + 0x2c]"
    },
    {
      "address": "00ba5e79",
      "instruction": "MOV EDX,dword ptr [EDI + 0xc]"
    },
    {
      "address": "00ba5e7c",
      "instruction": "MOV dword ptr [EDX + 0x1c],EBX"
    },
    {
      "address": "00ba5e7f",
      "instruction": "POP EBX"
    },
    {
      "address": "00ba5e80",
      "instruction": "MOV EAX,EDI"
    },
    {
      "address": "00ba5e82",
      "instruction": "POP EDI"
    },
    {
      "address": "00ba5e83",
      "instruction": "POP ESI"
    },
    {
      "address": "00ba5e84",
      "instruction": "RET"
    },
    {
      "address": "00ba5e85",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00ba5e87",
      "instruction": "CALL 0x00c0c100"
    },
    {
      "address": "00ba5e8c",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00ba5e8e",
      "instruction": "JZ 0x00ba5eb8"
    },
    {
      "address": "00ba5e90",
      "instruction": "MOV EDX,dword ptr [ESI + 0x5a8]"
    },
    {
      "address": "00ba5e96",
      "instruction": "MOV EAX,dword ptr [EDX + 0x58]"
    },
    {
      "address": "00ba5e99",
      "instruction": "LEA ECX,[ESI + 0x5a8]"
    },
    {
      "address": "00ba5e9f",
      "instruction": "MOV EBX,0x3"
    },
    {
      "address": "00ba5ea4",
      "instruction": "CALL EAX"
    },
    {
      "address": "00ba5ea6",
      "instruction": "MOV ECX,dword ptr [EDI + 0xc]"
    },
    {
      "address": "00ba5ea9",
      "instruction": "FSTP float ptr [ECX + 0x2c]"
    },
    {
      "address": "00ba5eac",
      "instruction": "MOV EDX,dword ptr [EDI + 0xc]"
    },
    {
      "address": "00ba5eaf",
      "instruction": "MOV dword ptr [EDX + 0x1c],EBX"
    },
    {
      "address": "00ba5eb2",
      "instruction": "POP EBX"
    },
    {
      "address": "00ba5eb3",
      "instruction": "MOV EAX,EDI"
    },
    {
      "address": "00ba5eb5",
      "instruction": "POP EDI"
    },
    {
      "address": "00ba5eb6",
      "instruction": "POP ESI"
    },
    {
      "address": "00ba5eb7",
      "instruction": "RET"
    },
    {
      "address": "00ba5eb8",
      "instruction": "MOV EDX,dword ptr [ESI]"
    },
    {
      "address": "00ba5eba",
      "instruction": "MOV EAX,dword ptr [EDX + 0x7c]"
    },
    {
      "address": "00ba5ebd",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00ba5ebf",
      "instruction": "CALL EAX"
    },
    {
      "address": "00ba5ec1",
      "instruction": "MOV ECX,dword ptr [EDI + 0xc]"
    },
    {
      "address": "00ba5ec4",
      "instruction": "FSTP float ptr [ECX + 0x2c]"
    },
    {
      "address": "00ba5ec7",
      "instruction": "MOV EDX,dword ptr [EDI + 0xc]"
    },
    {
      "address": "00ba5eca",
      "instruction": "MOV dword ptr [EDX + 0x1c],EBX"
    },
    {
      "address": "00ba5ecd",
      "instruction": "POP EBX"
    },
    {
      "address": "00ba5ece",
      "instruction": "MOV EAX,EDI"
    },
    {
      "address": "00ba5ed
[TRUNCATED]
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
  "body_end": "00ba5ed2",
  "body_span_bytes": 195,
  "body_start": "00ba5e10",
  "callees": [
    "FUN_00ba5650",
    "FUN_00c0c100",
    "FUN_00c0bc00",
    "FUN_00c0c0e0"
  ],
  "callers": [
    "FUN_00ba4f30",
    "FUN_00ba48b0",
    "FUN_00ba4600",
    "FUN_00cf50e0",
    "FUN_00d3fcf0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00ba5e10",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "uVar2",
      "storage": "register:00000000:4",
      "type": "undefined4"
    },
    {
      "name": "cVar1",
      "storage": "register:00000000:1",
      "type": "char"
    },
    {
      "name": "param_2",
      "storage": "Stack[0x8]:4",
      "type": "undefined4"
    },
    {
      "name": "param_1",
      "storage": "Stack[0x4]:4",
      "type": "int *"
    },
    {
      "name": "fVar4",
      "storage": "register:00001100:10",
      "type": "float10"
    },
    {
      "name": "iVar3",
      "storage": "register:00000000:4",
      "type": "int"
    }
  ],
  "locals_count": 6,
  "mode": "live",
  "name": "FUN_00ba5e10",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x7a5e10",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00ba5e10(void)",
  "size_bytes": 195,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00ba5e10",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 8,
  "xrefs": [
    {
      "from": "00ba504b"
    },
    {
      "from": "00ba50a0"
    },
    {
      "from": "00ba50e6"
    },
    {
      "from": "00ba498d"
    },
    {
      "from": "00cf51d0"
    },
    {
      "from": "00d40032"
    },
    {
      "from": "00ba4bf8"
    },
    {
      "from": "00ba463e"
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
