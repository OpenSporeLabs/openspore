# Evidence 0x00828c30

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `ad41d4fa600c171c5653e4c718507628d0a55678aba13f4fbf798da739aab75d`

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
      }
    ],
    "stack_cleanup_bytes": 16,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x10"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +24, so the listing is not one path",
    "unparsed_lines_present: 1 line(s) matched no grammar rule"
  ],
  "cleanup": {
    "bytes": 16,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x10",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "03c2906e8b52d8a7027a6d85dfa80a9b6d5e09c0111f21a38b12ef05c00f3893",
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
    "indirect_calls": 4,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0054"
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
        "obs-0004"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 1,
        "total_bytes": 4
      }
    },
    {
      "based_on": [
        "obs-0008",
        "obs-0009",
        "obs-0010",
        "obs-0019",
        "obs-0030",
        "obs-0036",
        "obs-0038",
        "obs-0041",
        "obs-0043",
        "obs-0047"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          44,
          48,
          64
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0008",
        "obs-0009",
        "obs-0010",
        "obs-0019",
        "obs-0030",
        "obs-0036",
        "obs-0038",
        "obs-0041",
        "obs-0043",
        "obs-0047",
        "obs-0054"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0054"
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
        "obs-0054"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0054"
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
      "and_esp": null,
      "at": "0x00828c30",
      "ebp_is_general_register": false,
      "fp": false,
      "id": "obs-0001",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": false,
      "push_ebp_at": null,
      "raw": "SUB ESP,0x3c",
      "sub": 60
    },
    {
      "at": "0x00828c30",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x3c",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00828c33",
      "count": 24,
      "first_use": 1,
      "first_write_index": 0,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EDX,dword ptr [ESP + 0x40]",
      "reg": "ESP"
    },
    {
      "at": "0x00828c33",
      "base": "ESP",
      "disp": 64,
      "id": "obs-0004",
      "index": 1,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EDX,dword ptr [ESP + 0x40]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00828c33",
      "definite": true,
      "id": "obs-0005",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [ESP + 0x40]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00828c37",
      "count": 5,
      "first_use": 2,
      "first_write_index": 42,
      "id": "obs-0006",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00828c38",
      "count": 9,
      "first_use": 3,
      "first_write_index": 4,
      "id": "obs-0007",
      "index":
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
"\n/* WARNING: Removing unreachable block (ram,0x00828cef) */\n\nundefined4 __thiscall\nFUN_00828c30(int param_1,uint param_2,undefined4 param_3,uint param_4,int *param_5)\n\n{\n  uint *puVar1;\n  int *piVar2;\n  uint *puVar3;\n  undefined1 local_38 [16];\n  ushort local_28;\n  undefined2 local_26;\n  undefined4 local_24;\n  uint local_20;\n  int *local_1c;\n  ushort local_8;\n  undefined2 local_6;\n  undefined4 local_4;\n  \n  local_20 = param_2;\n  local_26 = 0;\n  local_6 = 0;\n  local_28 = 0;\n  local_1c = (int *)0x0;\n  local_8 = 0;\n  FUN_00542b80(local_38);\n  puVar1 = *(uint **)(param_1 + 0x30);\n  local_4 = local_24;\n  puVar3 = (uint *)FUN_00d01210(*(undefined4 *)(param_1 + 0x2c),puVar1,&local_20,\n                                *(undefined1 *)(param_1 + 0x40));\n  if ((puVar3 == puVar1) || (local_20 < *puVar3)) {\n    puVar3 = (uint *)FUN_00828b80(puVar3,&local_20);\n  }\n  if ((local_8 & 4) != 0) {\n    FUN_0093db80(0);\n  }\n  if (local_1c != (int *)0x0) {\n    (**(code **)(*local_1c + 4))();\n  }\n  if ((local_28 & 4) != 0) {\n    FUN_0093db80(0);\n  }\n  FUN_00542b80(param_3);\n  piVar2 = (int *)puVar3[1];\n  puVar3[7] = param_4 | 4;\n  if (param_5 != piVar2) {\n    if (param_5 != (int *)0x0) {\n      (**(code **)*param_5)();\n    }\n    puVar3[1] = (uint)param_5;\n    if (piVar2 != (int *)0x0) {\n      (**(code **)(*piVar2 + 4))();\n    }\n  }\n  return 1;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 96,
  "instructions": [
    {
      "address": "00828c30",
      "instruction": "SUB ESP,0x3c"
    },
    {
      "address": "00828c33",
      "instruction": "MOV EDX,dword ptr [ESP + 0x40]"
    },
    {
      "address": "00828c37",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00828c38",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00828c39",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00828c3b",
      "instruction": "XOR ECX,ECX"
    },
    {
      "address": "00828c3d",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "00828c3f",
      "instruction": "MOV dword ptr [ESP + 0x24],EDX"
    },
    {
      "address": "00828c43",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00828c44",
      "instruction": "LEA EDX,[ESP + 0x10]"
    },
    {
      "address": "00828c48",
      "instruction": "MOV word ptr [ESP + 0x22],CX"
    },
    {
      "address": "00828c4d",
      "instruction": "MOV word ptr [ESP + 0x42],CX"
    },
    {
      "address": "00828c52",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00828c53",
      "instruction": "LEA ECX,[ESP + 0x34]"
    },
    {
      "address": "00828c57",
      "instruction": "MOV dword ptr [ESP + 0x10],0x0"
    },
    {
      "address": "00828c5f",
      "instruction": "MOV word ptr [ESP + 0x24],AX"
    },
    {
      "address": "00828c64",
      "instruction": "MOV dword ptr [ESP + 0x30],EAX"
    },
    {
      "address": "00828c68",
      "instruction": "MOV word ptr [ESP + 0x44],AX"
    },
    {
      "address": "00828c6d",
      "instruction": "CALL 0x00542b80"
    },
    {
      "address": "00828c72",
      "instruction": "MOVZX ECX,byte ptr [ESI + 0x40]"
    },
    {
      "address": "00828c76",
      "instruction": "MOV EAX,dword ptr [ESP + 0x24]"
    },
    {
      "address": "00828c7a",
      "instruction": "MOV EDI,dword ptr [ESI + 0x30]"
    },
    {
      "address": "00828c7d",
      "instruction": "ADD ESI,0x2c"
    },
    {
      "address": "00828c80",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00828c81",
      "instruction": "LEA EDX,[ESP + 0x2c]"
    },
    {
      "address": "00828c85",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00828c86",
      "instruction": "MOV dword ptr [ESP + 0x4c],EAX"
    },
    {
      "address": "00828c8a",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "00828c8c",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00828c8d",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00828c8e",
      "instruction": "CALL 0x00d01210"
    },
    {
      "address": "00828c93",
      "instruction": "ADD ESP,0x10"
    },
    {
      "address": "00828c96",
      "instruction": "CMP EAX,EDI"
    },
    {
      "address": "00828c98",
      "instruction": "JZ 0x00828ca2"
    },
    {
      "address": "00828c9a",
      "instruction": "MOV ECX,dword ptr [ESP + 0x28]"
    },
    {
      "address": "00828c9e",
      "instruction": "CMP ECX,dword ptr [EAX]"
    },
    {
      "address": "00828ca0",
      "instruction": "JNC 0x00828caf"
    },
    {
      "address": "00828ca2",
      "instruction": "LEA EDX,[ESP + 0x28]"
    },
    {
      "address": "00828ca6",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00828ca7",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00828ca8",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00828caa",
      "instruction": "CALL 0x00828b80"
    },
    {
      "address": "00828caf",
      "instruction": "MOV EBX,0x4"
    },
    {
      "address": "00828cb4",
      "instruction": "MOV ESI,EAX"
    },
    {
      "address": "00828cb6",
      "instruction": "TEST byte ptr [ESP + 0x40],BL"
    },
    {
      "address": "00828cba",
      "instruction": "JZ 0x00828cc7"
    },
    {
      "address": "00828cbc",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00828cbe",
      "instruction": "LEA ECX,[ESP + 0x34]"
    },
    {
      "address": "00828cc2",
      "instruction": "CALL 0x0093db80"
    },
    {
      "address": "00828cc7",
      "instruction": "MOV ECX,dword ptr [ESP + 0x2c]"
    },
    {
      "address": "00828ccb",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00828ccd",
      "instruction": "JZ 0x00828cd6"
    },
    {
      "address": "00828ccf",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "00828cd1",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "00828cd4",
      "instruction": "CALL EDX"
    },
    {
      "address": "00828cd6",
      "instruction": "TEST byte ptr [ESP + 0x20],BL"
    },
    {
      "address": "00828cda",
      "instruction": "JZ 0x00828ce7"
    },
    {
      "address": "00828cdc",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00828cde",
      "instruction": "LEA ECX,[ESP + 0x14]"
    },
    {
      "address": "00828ce2",
      "instruction": "CALL 0x0093db80"
    },
    {
      "address": "00828ce7",
      "instruction": "MOV ECX,dword ptr [ESP + 0xc]"
    },
    {
      "address": "00828ceb",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00828ced",
      "instruction": "JZ 0x00828cf6"
    },
    {
      "address": "00828cef",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "00828cf1",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "00828cf4",
      "instruction": "CALL EDX"
    },
    {
      "address": "00828cf6",
      "instruction": "MOV EAX,dword ptr [ESP + 0x50]"
    },
    {
      "address": "00828cfa",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00828cfb",
      "instruction": "LEA ECX,[ESI + 0x8]"
    },
    {
      "address": "00828cfe",
      "instruction": "CALL 0x00542b80"
    },
    {
      "address": "00828d03",
      "instruction": "MOV ECX,dword ptr [ESP + 0x54]"
    },
  
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
  "body_end": "00828d3d",
  "body_span_bytes": 270,
  "body_start": "00828c30",
  "callees": [
    "FUN_0093db80",
    "FUN_00d01210",
    "FUN_00542b80",
    "FUN_00828b80"
  ],
  "callers": [
    "FUN_00e47520",
    "FUN_00bdde70",
    "FUN_00e2d6a0",
    "FUN_005e4560",
    "FUN_00677700",
    "FUN_005e6b40",
    "FUN_00e2c590"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00828c30",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "param_3",
      "storage": "Stack[0x8]:4",
      "type": "undefined4"
    },
    {
      "name": "param_2",
      "storage": "Stack[0x4]:4",
      "type": "uint"
    },
    {
      "name": "param_5",
      "storage": "Stack[0x10]:4",
      "type": "int *"
    },
    {
      "name": "param_4",
      "storage": "Stack[0xc]:4",
      "type": "uint"
    },
    {
      "name": "piVar2",
      "storage": "unique:00017200:4",
      "type": "int *"
    },
    {
      "name": "puVar1",
      "storage": "unique:00017200:4",
      "type": "uint *"
    },
    {
      "name": "puVar3",
      "storage": "register:00000000:4",
      "type": "uint *"
    },
    {
      "name": "local_28",
      "storage": "Stack[-0x28]:2",
      "type": "ushort"
    },
    {
      "name": "local_26",
      "storage": "Stack[-0x26]:2",
      "type": "undefined2"
    },
    {
      "name": "local_38",
      "storage": "",
      "type": "undefined1[16]"
    },
    {
      "name": "local_1c",
      "storage": "Stack[-0x1c]:4",
      "type": "int *"
    },
    {
      "name": "local_24",
      "storage": "Stack[-0x24]:4",
      "type": "undefined4"
    },
    {
      "name": "local_20",
      "storage": "Stack[-0x20]:4",
      "type": "uint"
    },
    {
      "name": "local_4",
      "storage": "Stack[-0x4]:4",
      "type": "undefined4"
    },
    {
      "name": "local_8",
      "storage": "Stack[-0x8]:2",
      "type": "ushort"
    },
    {
      "name": "local_6",
      "storage": "Stack[-0x6]:2",
      "type": "undefined2"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int"
    }
  ],
  "locals_count": 17,
  "mode": "live",
  "name": "FUN_00828c30",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x428c30",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00828c30(void)",
  "size_bytes": 270,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00828c30",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 31,
  "xrefs": [
    {
      "from": "005e4627"
    },
    {
      "from": "005e46d8"
    },
    {
      "from": "005e4738"
    },
    {
      "from": "005e47b3"
    },
    {
      "from": "005e4849"
    },
    {
      "from": "005e6b87"
    },
    {
      "from": "005e6d24"
    },
    {
      "from": "005e6dd5"
    },
    {
      "from": "005e6e3f"
    },
    {
      "from": "00677821"
    },
    {
      "from": "00bde014"
    },
    {
      "from": "00bde15e"
    },
    {
      "from": "00bde205"
    },
    {
      "from": "00bde297"
    },
    {
      "from": "00bde2dd"
    },
    {
      "from": "00bde3bb"
    },
    {
      "from": "00e2da92"
    },
    {
      "from": "00e2db93"
    },
    {
      "from": "00e2dc97"
    },
    {
      "from": "00e2dd9b"
    },
    {
      "from": "00e2dea9"
    },
    {
      "from": "00e2e06a"
    },
    {
      "from": "00e2e205"
    },
    {
      "from": "00e2c72b"
    },
    {
      "from": "00e475ef"
    },
    {
      "from": "005a75b6"
    },
    {
      "from": "005a75ed"
    },
    {
      "from": "005a7624"
    },
    {
      "from": "00ed0839"
    },
    {
      "from": "00ed0870"
    },
    {
      "from": "00ed08a4"
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
