# Evidence 0x00c12310

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `a1c3ed1e2327c204b81bdbab8ad9248f9764cd6e3b62b41f12ada458efb098f6`

## abi

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
      "entry_ESP+0x4",
      "entry_ESP+0x8"
    ],
    "ordinary_stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": true,
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
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0xc",
    "return_register": "ST0",
    "return_semantics": "float_or_x87_in_ST0",
    "saved_registers": [
      "EBP",
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
        "size_inferred": true,
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
    "stack_cleanup_bytes": 12,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0xc"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +32, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 12,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0xc",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "4ce389573b855bcbf4a24e8d06c5532a655dcc711c566e25aca310c0e5d6942e",
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
    "persisted_calling_convention": null
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 7,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0029",
        "obs-0044"
      ],
      "claim": "the callee pops 12 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 12,
        "side": "callee"
      }
    },
    {
      "based_on": [
        "obs-0010",
        "obs-0013",
        "obs-0014",
        "obs-0019",
        "obs-0032"
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
        "obs-0006",
        "obs-0007",
        "obs-0020",
        "obs-0038"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          2900,
          3720
        ],
        "register": "ECX",
        "written_through": 1
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007",
        "obs-0020",
        "obs-0029",
        "obs-0038",
        "obs-0044"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0029",
        "obs-0044"
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
        "obs-0003"
      ],
      "claim": "the return value is carried in ST0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "ST0"
    }
  ],
  "observations": [
    {
      "at": "0x00c12310",
      "count": 3,
      "first_use": 0,
      "first_write_index": 23,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00c12311",
      "count": 4,
      "first_use": 1,
      "first_write_index": 8,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EBP",
      "reg": "EBP"
    },
    {
      "and_esp": null,
      "at": "0x00c12311",
      "ebp_is_general_register": false,
      "fp": false,
      "id": "obs-0003",
      "index": 1,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": true,
      "push_ebp_at": 1,
      "raw": "PUSH EBP",
      "sub": null
    },
    {
      "at": "0x00c12312",
      "count": 11,
      "first_use": 2,
      "first_write_index": 4,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00c12313",
      "count": 12,
      "first_use": 3,
      "first_write_index": 5,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00c12314",
      "count": 9,
      "first_use": 4,
      "first_write_index": 19,
      "id": "obs-0006",
      "index": 4,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00c12314",
      "definite": true,
      "id": "obs
[TRUNCATED]
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
      "entry_ESP+0x4",
      "entry_ESP+0x8"
    ],
    "ordinary_stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": true,
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
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0xc",
    "return_register": "ST0",
    "return_semantics": "float_or_x87_in_ST0",
    "saved_registers": [
      "EBP",
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
        "size_inferred": true,
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
    "stack_cleanup_bytes": 12,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0xc"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +32, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 12,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0xc",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "4ce389573b855bcbf4a24e8d06c5532a655dcc711c566e25aca310c0e5d6942e",
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
    "persisted_calling_convention": null
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 7,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0029",
        "obs-0044"
      ],
      "claim": "the callee pops 12 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 12,
        "side": "callee"
      }
    },
    {
      "based_on": [
        "obs-0010",
        "obs-0013",
        "obs-0014",
        "obs-0019",
        "obs-0032"
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
        "obs-0006",
        "obs-0007",
        "obs-0020",
        "obs-0038"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          2900,
          3720
        ],
        "register": "ECX",
        "written_through": 1
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007",
        "obs-0020",
        "obs-0029",
        "obs-0038",
        "obs-0044"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0029",
        "obs-0044"
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
        "obs-0003"
      ],
      "claim": "the return value is carried in ST0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "ST0"
    }
  ],
  "observations": [
    {
      "at": "0x00c12310",
      "count": 3,
      "first_use": 0,
      "first_write_index": 23,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00c12311",
      "count": 4,
      "first_use": 1,
      "first_write_index": 8,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EBP",
      "reg": "EBP"
    },
    {
      "and_esp": null,
      "at": "0x00c12311",
      "ebp_is_general_register": false,
      "fp": false,
      "id": "obs-0003",
      "index": 1,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": true,
      "push_ebp_at": 1,
      "raw": "PUSH EBP",
      "sub": null
    },
    {
      "at": "0x00c12312",
      "count": 11,
      "first_use": 2,
      "first_write_index": 4,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00c12313",
      "count": 12,
      "first_use": 3,
      "first_write_index": 5,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00c12314",
      "count": 9,
      "first_use": 4,
      "first_write_index": 19,
      "id": "obs-0006",
      "index": 4,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00c12314",
      "definite": true,
      "id": "obs
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
    "va": "0x00c06f70"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c13650"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c13a30"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c14590"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c14990"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c149c0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c14cb0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c18370"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c18740"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c18b40"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c190e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c1b020"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c1c9f0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c1e460"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c20230"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c21bf0"
  }
]
```

## contradictions

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## decompilation

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json
"\nundefined4 __thiscall FUN_00c12310(int param_1,undefined4 param_2)\n\n{\n  undefined4 uVar1;\n  int *piVar2;\n  int iVar3;\n  char unaff_BP;\n  undefined4 uVar4;\n  undefined4 uVar5;\n  \n  uVar1 = param_2;\n  uVar4 = 0;\n  if (*(int *)(param_1 + 0xb54) != 0) {\n    FUN_00c0c5b0(param_1,param_2,&param_2);\n    piVar2 = (int *)FUN_0067cb20();\n    uVar4 = param_2;\n    iVar3 = (**(code **)(*piVar2 + 0x40))(param_2);\n    if (iVar3 == 0) {\n      return 0;\n    }\n    uVar4 = (**(code **)(**(int **)(param_1 + 0xb54) + 8))(uVar4,0);\n    uVar5 = 1;\n    (**(code **)(**(int **)(param_1 + 0xb54) + 0xc))(uVar4,1);\n    if (unaff_BP != '\\0') {\n      (**(code **)(**(int **)(param_1 + 0xb54) + 0x14))(uVar4,0);\n    }\n    (**(code **)(**(int **)(param_1 + 0xb54) + 0x18))(uVar4);\n    (**(code **)(**(int **)(param_1 + 0xb54) + 0x40))(uVar4,uVar1);\n    (**(code **)(**(int **)(param_1 + 0xb54) + 0x3c))(uVar4,0);\n    FUN_00c10250(param_1,uVar4,uVar5,iVar3);\n    if (*(char *)(iVar3 + 0x1c) != '\\x01') {\n      *(undefined4 *)(param_1 + 0xe88) = uVar4;\n    }\n  }\n  return uVar4;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 87,
  "instructions": [
    {
      "address": "00c12310",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00c12311",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00c12312",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00c12313",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00c12314",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00c12316",
      "instruction": "XOR EDI,EDI"
    },
    {
      "address": "00c12318",
      "instruction": "CMP dword ptr [ESI + 0xb54],EDI"
    },
    {
      "address": "00c1231e",
      "instruction": "JZ 0x00c123e1"
    },
    {
      "address": "00c12324",
      "instruction": "MOV EBP,dword ptr [ESP + 0x14]"
    },
    {
      "address": "00c12328",
      "instruction": "LEA EAX,[ESP + 0x14]"
    },
    {
      "address": "00c1232c",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00c1232d",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00c1232e",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00c1232f",
      "instruction": "MOV dword ptr [ESP + 0x20],EBP"
    },
    {
      "address": "00c12333",
      "instruction": "CALL 0x00c0c5b0"
    },
    {
      "address": "00c12338",
      "instruction": "ADD ESP,0xc"
    },
    {
      "address": "00c1233b",
      "instruction": "CALL 0x0067cb20"
    },
    {
      "address": "00c12340",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00c12342",
      "instruction": "MOV EDI,dword ptr [ESP + 0x14]"
    },
    {
      "address": "00c12346",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00c12348",
      "instruction": "MOV EAX,dword ptr [EDX + 0x40]"
    },
    {
      "address": "00c1234b",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00c1234c",
      "instruction": "CALL EAX"
    },
    {
      "address": "00c1234e",
      "instruction": "MOV EBX,EAX"
    },
    {
      "address": "00c12350",
      "instruction": "TEST EBX,EBX"
    },
    {
      "address": "00c12352",
      "instruction": "JNZ 0x00c1235b"
    },
    {
      "address": "00c12354",
      "instruction": "POP EDI"
    },
    {
      "address": "00c12355",
      "instruction": "POP ESI"
    },
    {
      "address": "00c12356",
      "instruction": "POP EBP"
    },
    {
      "address": "00c12357",
      "instruction": "POP EBX"
    },
    {
      "address": "00c12358",
      "instruction": "RET 0xc"
    },
    {
      "address": "00c1235b",
      "instruction": "MOV ECX,dword ptr [ESI + 0xb54]"
    },
    {
      "address": "00c12361",
      "instruction": "MOV EDX,dword ptr [ECX]"
    },
    {
      "address": "00c12363",
      "instruction": "MOV EAX,dword ptr [EDX + 0x8]"
    },
    {
      "address": "00c12366",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00c12368",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00c12369",
      "instruction": "CALL EAX"
    },
    {
      "address": "00c1236b",
      "instruction": "MOV ECX,dword ptr [ESI + 0xb54]"
    },
    {
      "address": "00c12371",
      "instruction": "MOV EDX,dword ptr [ECX]"
    },
    {
      "address": "00c12373",
      "instruction": "MOV EDI,EAX"
    },
    {
      "address": "00c12375",
      "instruction": "MOV EAX,dword ptr [EDX + 0xc]"
    },
    {
      "address": "00c12378",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "00c1237a",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00c1237b",
      "instruction": "CALL EAX"
    },
    {
      "address": "00c1237d",
      "instruction": "CMP byte ptr [ESP + 0x1c],0x0"
    },
    {
      "address": "00c12382",
      "instruction": "JZ 0x00c12398"
    },
    {
      "address": "00c12384",
      "instruction": "MOV ECX,dword ptr [ESI + 0xb54]"
    },
    {
      "address": "00c1238a",
      "instruction": "FLDZ"
    },
    {
      "address": "00c1238c",
      "instruction": "MOV EDX,dword ptr [ECX]"
    },
    {
      "address": "00c1238e",
      "instruction": "MOV EAX,dword ptr [EDX + 0x14]"
    },
    {
      "address": "00c12391",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00c12392",
      "instruction": "FSTP float ptr [ESP]"
    },
    {
      "address": "00c12395",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00c12396",
      "instruction": "CALL EAX"
    },
    {
      "address": "00c12398",
      "instruction": "MOV ECX,dword ptr [ESI + 0xb54]"
    },
    {
      "address": "00c1239e",
      "instruction": "MOV EDX,dword ptr [ECX]"
    },
    {
      "address": "00c123a0",
      "instruction": "MOV EAX,dword ptr [EDX + 0x18]"
    },
    {
      "address": "00c123a3",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00c123a4",
      "instruction": "CALL EAX"
    },
    {
      "address": "00c123a6",
      "instruction": "MOV ECX,dword ptr [ESI + 0xb54]"
    },
    {
      "address": "00c123ac",
      "instruction": "MOV EDX,dword ptr [ECX]"
    },
    {
      "address": "00c123ae",
      "instruction": "MOV EAX,dword ptr [EDX + 0x40]"
    },
    {
      "address": "00c123b1",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00c123b2",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00c123b3",
      "instruction": "CALL EAX"
    },
    {
      "address": "00c123b5",
      "instruction": "MOV ECX,dword ptr [ESI + 0xb54]"
    },
    {
      "address": "00c123bb",
      "instruction": "MOV EDX,dword ptr [ECX]"
    },
    {
      "address": "00c123bd",
      "instruction": "MOV EAX,dword ptr [EDX + 0x3c]"
    },
    {
      "address": "00c123c0",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00c123c2",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00c123c3",
      "instruction": "CALL EAX"
    },
    {
      "address": "00c123c5",
      "instruction": "MOV ECX,dword ptr [ESP + 0x18]"
    },
    {
      "address": "00c123c9",
      
[TRUNCATED]
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
  "original_bytes": 13228,
  "preview": "{\n  \"abi\": {},\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-11-H4-HELPER-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"address_window_offset_005c65e0\",\n      \"va\": \"0x005c65e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"dispatch_key_00628450\",\n      \"va\": \"0x00628450\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"cycle_key_006286a0\",\n      \"va\": \"0x006286a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"release_child_0062c910\",\n      \"va\": \"0x0062c910\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d2a0\",\n      \"va\": \"0x00b3d2a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d300\",\n      \"va\": \"0x00b3d300\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"Simulator_GetUIMissionLogManager\",\n      \"va\": \"0x00b3d4f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-13-E4-EMPIRE-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"EmpirePoliticalColor_00c32cd0\",\n      \"va\": \"0x00c32cd0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"unknown-fun-mass\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c06f70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c13650\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c13a30\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c14590\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c14990\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c149c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c14cb0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c18370\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c18740\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c18b40\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c190e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c1b020\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c1c9f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c1e460\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c20230\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c21bf0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c25480\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c26380\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00cd7320\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ce1510\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d57f80\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d5cfd0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d5f780\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d679e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d697a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d6aa30\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d6fa60\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d703a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d705f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d74060\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d7c3e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d7e6e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d7eab0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\
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
  "body_end": "00c123e9",
  "body_span_bytes": 218,
  "body_start": "00c12310",
  "callees": [
    "FUN_00c10250",
    "FUN_00c0c5b0",
    "FUN_0067cb20"
  ],
  "callers": [
    "FUN_00d8e8d0",
    "FUN_00d93880",
    "FUN_00d8a750",
    "FUN_00c14cb0",
    "FUN_00c20230",
    "FUN_00c1e460",
    "FUN_00d92cc0",
    "FUN_00d5f780",
    "FUN_00d679e0",
    "FUN_00d9d1e0",
    "FUN_00db1c10",
    "FUN_00cd7320",
    "FUN_00d5cfd0",
    "FUN_00d85e40",
    "FUN_00c26380",
    "FUN_00da01a0",
    "FUN_00d57f80",
    "FUN_00c18370",
    "FUN_00c18740",
    "FUN_010323d0",
    "FUN_00d930b0",
    "FUN_00d8a660",
    "FUN_00d92560",
    "FUN_00c13a30",
    "FUN_00ce1510",
    "FUN_00c149c0",
    "FUN_00d824a0",
    "FUN_00d705f0",
    "FUN_00d952e0",
    "FUN_00c1c9f0",
    "FUN_00d7e6e0",
    "FUN_00c18b40",
    "FUN_00d697a0",
    "FUN_00c14990",
    "FUN_00db2060",
    "FUN_00d74060",
    "FUN_00daf2e0",
    "FUN_00c21bf0",
    "FUN_00c06f70",
    "FUN_00d703a0",
    "FUN_00c25480",
    "FUN_00db4370",
    "FUN_00dad390",
    "FUN_00da7340",
    "FUN_00d8a8c0",
    "FUN_00d93670",
    "FUN_00d86240",
    "FUN_00d83370",
    "FUN_00d6fa60",
    "FUN_00c190e0",
    "FUN_00d7eab0",
    "FUN_00d932e0",
    "FUN_00d6aa30",
    "FUN_00d97d93",
    "FUN_00f235e0",
    "FUN_00daf620",
    "FUN_00c14590",
    "FUN_00db7190",
    "FUN_00da2fd0",
    "FUN_01034260",
    "FUN_00d92880",
    "FUN_00daf820",
    "FUN_00dbb840",
    "FUN_00d92660",
    "FUN_00c13650",
    "FUN_00c1b020",
    "FUN_00d92fb0",
    "FUN_00db33d0",
    "FUN_00d7c3e0",
    "FUN_00d8d300"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00c12310",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "param_2",
      "storage": "Stack[0x4]:4",
      "type": "undefined4"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int"
    },
    {
      "name": "uVar5",
      "storage": "Stack[-0x20]:4",
      "type": "undefined4"
    },
    {
      "name": "uVar4",
      "storage": "register:0000001c:4",
      "type": "undefined4"
    },
    {
      "name": "piVar2",
      "storage": "register:00000000:4",
      "type": "int *"
    },
    {
      "name": "uVar1",
      "storage": "unique:100000d0:4",
      "type": "undefined4"
    },
    {
      "name": "unaff_BP",
      "storage": "register:00000014:1",
      "type": "char"
    },
    {
      "name": "iVar3",
      "storage": "register:00000000:4",
      "type": "int"
    }
  ],
  "locals_count": 8,
  "mode": "live",
  "name": "FUN_00c12310",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x812310",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00c12310(void)",
  "size_bytes": 218,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00c12310",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 100,
  "xrefs": [
    {
      "from": "00d58014"
    },
    {
      "from": "00c21efd"
    },
    {
      "from": "00d5fb0d"
    },
    {
      "from": "00c1461e"
    },
    {
      "from": "00c07067"
    },
    {
      "from": "00c13998"
    },
    {
      "from": "00c13a10"
    },
    {
      "from": "00c13a21"
    },
    {
      "from": "00c13c1b"
    },
    {
      "from": "00c14d8d"
    },
    {
      "from": "00c186ef"
    },
    {
      "from": "00c1871d"
    },
    {
      "from": "00c1872f"
    },
    {
      "from": "00c1879e"
    },
    {
      "from": "00c18b32"
    },
    {
      "from": "00c20fd1"
    },
    {
      "from": "00c254b8"
    },
    {
      "from": "00c1cc53"
    },
    {
      "from": "00cd73fb"
    },
    {
      "from": "00ce1661"
    },
    {
      "from": "00d5d333"
    },
    {
      "from": "00d67b3e"
    },
    {
      "from": "00d67c14"
    },
    {
      "from": "00d67c5d"
    },
    {
      "from": "00d6999a"
    },
    {
      "from": "00d69e40"
    },
    {
      "from": "00d6aa1b"
    },
    {
      "from": "00c1e719"
    },
    {
      "from": "00c149d2"
    },
    {
      "from": "00d6fd21"
    },
    {
      "from": "00d704c8"
    },
    {
      "from": "00c263be"
    },
    {
      "from": "00d7c3fe"
    },
    {
      "from": "00d7e7f3"
    },
    {
      "from": "00d82e3c"
    },
    {
      "from": "00c19601"
    },
    {
      "from": "00c19643"
    },
    {
      "from": "00d83a3e"
    },
    {
      "from": "00d85f05"
    },
    {
      "from": "00d862bc"
    },
    {
      "from": "00d86312"
    },
    {
      "from": "00c149a2"
    },
    {
      "from": "00d8a678"
    },
    {
      "from": "00d8a7aa"
    },
    {
      "from": "00d8a912"
    },
    {
      "from": "00d8d366"
    },
    {
      "from": "00d8e969"
    },
    {
      "from": "00d9262d"
    },
    {
      "from": "00d92738"
    },
    {
      "from": "00d92957"
    },
    {
      "from": "00d92d1d"
    },
    {
      "from": "00d93081"
    },
    {
      "from": "00d9314f"
    },
    {
      "from": "00d93389"
    },
    {
      "from": "00d936c9"
    },
    {
      "from": "00d93cb9"
    },
    {
      "from": "00d93ce8"
    },
    {
      "from": "00d95500"
    },
    {
      "from": "00d97f3e"
    },
    {
      "from": "00d980c5"
    },
    {
      "from": "00da0236"
    },
    {
      "from": "00da024c"
    },
    {
      "from": "00da026
[TRUNCATED]
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
  "files": [],
  "handoffs": [],
  "metadata": []
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
  "gates": [],
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
  "runtime_gated": false,
  "runtime_validated": 0,
  "status": "candidate"
}
```

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
