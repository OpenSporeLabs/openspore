# Evidence 0x00695960

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `90d8ce36fbd03eed128bd7f1b176b34c7af9a13318be77ccebe266df07d4796d`

## abi

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
      "entry_ESP+0x64"
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
        "entry_offset": "entry_ESP+0x64",
        "observed": true,
        "ordinal": 25,
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
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x64",
        "observed": true,
        "ordinal": 25,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "termination": "RET 0x4"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -112, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
    "ret_imm_below_highest_slot: ret 0x4 pops less than the highest read slot 0x64; everything above it belongs to the caller's frame",
    "slot_gaps_present: argument ordinal(s) below the highest read slot are never touched",
    "no_discriminator: the callee pop of 0x4 is not a whole number of dword stack arguments, so no convention follows from it"
  ],
  "cleanup": {
    "bytes": 4,
    "confidence": "UNKNOWN",
    "corroboration": "not_available",
    "evidence": "ret 0x4 but entry slot 0x64 is read",
    "side": null
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "aff3b17c7b5f400a5ea10393410638b27b5f446d7841508cb776b8a5c690d221",
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
    "indirect_calls": 2,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0081",
        "obs-0086"
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
        "obs-0081",
        "obs-0086"
      ],
      "claim": "cleanup side is undetermined: a slot above the popped area is read",
      "confidence": "UNKNOWN",
      "id": "C4",
      "value": {
        "bytes": 4,
        "side": null
      }
    },
    {
      "based_on": [
        "obs-0012",
        "obs-0082"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 23,
        "observed_slots": 2,
        "total_bytes": 100
      }
    },
    {
      "based_on": [
        "obs-0010",
        "obs-0011",
        "obs-0012",
        "obs-0013",
        "obs-0020",
        "obs-0041",
        "obs-0044",
        "obs-0047",
        "obs-0049",
        "obs-0056",
        "obs-0058",
        "obs-0060",
        "obs-0061",
        "obs-0068",
        "obs-0079",
        "obs-0080",
        "obs-0082",
        "obs-0085"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          2560
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0004",
        "obs-0080",
        "obs-0085"
      ],
      "claim": "an FS:/GS: operand is an SEH or cookie frame, which is not variadic evidence",
      "confidence": "OBSERVED",
      "id": "V2",
      "value": {
        "seh_or_cookie_frame": true
      }
    },
    {
      "based_on": [
        "obs-0086"
      ],
      "claim": "the calling convention is unknown: the terminal pop is not a whole number of dword arguments",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0081",
        "obs-0086"
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
        "obs-0052"
      ],
      "claim": "a bulk string write reaches the return register, which is not a struct-return signature",
      "confidence": "INFERRED",
      "id": "RT4",
      "value": {
        "bulk_write": true
      }
    },
    {
      "based_on": [
        "obs-0081",
        "obs-0086"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0081",
        "obs-0086"
      ],
      "c
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
"\nundefined4 __fastcall FUN_00695960(int param_1)\n\n{\n  undefined4 *puVar1;\n  char *pcVar2;\n  char *pcVar3;\n  undefined4 uVar4;\n  int iVar5;\n  undefined4 *puVar6;\n  char **ppcVar7;\n  undefined4 *local_78;\n  int local_70;\n  char *local_6c [6];\n  undefined4 local_54;\n  undefined4 local_50;\n  code *local_4c;\n  undefined4 local_48;\n  undefined4 local_44;\n  undefined4 local_40;\n  undefined4 local_3c;\n  undefined4 local_38;\n  undefined4 local_34;\n  undefined4 local_30;\n  undefined1 *local_2c;\n  undefined1 *local_28;\n  undefined1 *local_24;\n  undefined1 *local_1c;\n  undefined1 *local_18;\n  undefined1 *local_14;\n  void *local_c;\n  undefined1 *puStack_8;\n  undefined4 local_4;\n  \n  local_4 = 0xffffffff;\n  puStack_8 = &LAB_0120d038;\n  local_c = ExceptionList;\n  ExceptionList = &local_c;\n  FUN_00695490(*(undefined4 *)(param_1 + 0xa00));\n  local_70 = 0;\n  if (*(int *)(param_1 + 0xa00) < 1) {\n    ExceptionList = local_c;\n    return *(undefined4 *)(param_1 + 0xa00);\n  }\n  local_78 = (undefined4 *)(param_1 + 0xc);\n  do {\n    puVar1 = (undefined4 *)local_78[1];\n    if (puVar1[6] == 0) {\n      puVar1[6] = *(undefined4 *)(param_1 + 0xa0c);\n    }\n    local_6c[0] = \"field_name\";\n    local_6c[1] = (char *)0xffffffff;\n    local_54 = 0;\n    local_50 = 0;\n    local_4c = FUN_011874d0;\n    local_48 = 0;\n    local_44 = 0;\n    local_40 = 0;\n    local_3c = 0;\n    local_38 = 0;\n    local_34 = 0;\n    local_6c[2] = (char *)0x0;\n    local_2c = &DAT_01667bac;\n    local_28 = &DAT_01667bac;\n    local_24 = &DAT_01667bad;\n    local_1c = &DAT_01667bac;\n    local_18 = &DAT_01667bac;\n    local_14 = &DAT_01667bad;\n    local_4 = 0;\n    pcVar2 = (char *)*puVar1;\n    do {\n      pcVar3 = pcVar2;\n      pcVar2 = pcVar3 + 1;\n    } while (*pcVar3 != '\\0');\n    FUN_00454cb0((char *)*puVar1,pcVar3);\n    local_30 = *(undefined4 *)(param_1 + 0xa0c);\n    puVar6 = puVar1;\n    ppcVar7 = local_6c;\n    for (iVar5 = 0xf; iVar5 != 0; iVar5 = iVar5 + -1) {\n      *ppcVar7 = (char *)*puVar6;\n      puVar6 = puVar6 + 1;\n      ppcVar7 = ppcVar7 + 1;\n    }\n    if ((puVar1[0xc] != 0) && ((code *)puVar1[8] != (code *)0x0)) {\n      uVar4 = (*(code *)puVar1[8])(puVar1);\n      (*(code *)puVar1[0xc])(&local_1c,uVar4);\n    }\n    puVar1[6] = *local_78;\n    FUN_006956f0(local_6c);\n    local_4 = 0xffffffff;\n    if ((1 < (int)local_14 - (int)local_1c) && (local_1c != (undefined1 *)0x0)) {\n      FUN_00f47380(local_1c);\n    }\n    if ((1 < (int)local_24 - (int)local_2c) && (local_2c != (undefined1 *)0x0)) {\n      FUN_00f47380(local_2c);\n    }\n    local_78 = local_78 + 5;\n    local_70 = local_70 + 1;\n  } while (local_70 < *(int *)(param_1 + 0xa00));\n  ExceptionList = local_c;\n  return *(undefined4 *)(param_1 + 0xa00);\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 136,
  "instructions": [
    {
      "address": "00695960",
      "instruction": "PUSH -0x1"
    },
    {
      "address": "00695962",
      "instruction": "PUSH 0x120d038"
    },
    {
      "address": "00695967",
      "instruction": "MOV EAX,FS:[0x0]"
    },
    {
      "address": "0069596d",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0069596e",
      "instruction": "MOV dword ptr FS:[0x0],ESP"
    },
    {
      "address": "00695975",
      "instruction": "SUB ESP,0x6c"
    },
    {
      "address": "00695978",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00695979",
      "instruction": "PUSH ESI"
    },
    {
      "address": "0069597a",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "0069597c",
      "instruction": "MOV EAX,dword ptr [ESI + 0xa00]"
    },
    {
      "address": "00695982",
      "instruction": "MOV ECX,dword ptr [ESP + 0x84]"
    },
    {
      "address": "00695989",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0069598a",
      "instruction": "MOV dword ptr [ESP + 0x10],ESI"
    },
    {
      "address": "0069598e",
      "instruction": "CALL 0x00695490"
    },
    {
      "address": "00695993",
      "instruction": "XOR EBX,EBX"
    },
    {
      "address": "00695995",
      "instruction": "CMP dword ptr [ESI + 0xa00],EBX"
    },
    {
      "address": "0069599b",
      "instruction": "MOV dword ptr [ESP + 0x10],EBX"
    },
    {
      "address": "0069599f",
      "instruction": "JLE 0x00695b1a"
    },
    {
      "address": "006959a5",
      "instruction": "PUSH EBP"
    },
    {
      "address": "006959a6",
      "instruction": "LEA ECX,[ESI + 0xc]"
    },
    {
      "address": "006959a9",
      "instruction": "PUSH EDI"
    },
    {
      "address": "006959aa",
      "instruction": "MOV dword ptr [ESP + 0x10],ECX"
    },
    {
      "address": "006959ae",
      "instruction": "JMP 0x006959b2"
    },
    {
      "address": "006959b0",
      "instruction": "MOV ESI,EDX"
    },
    {
      "address": "006959b2",
      "instruction": "MOV EDX,dword ptr [ESP + 0x10]"
    },
    {
      "address": "006959b6",
      "instruction": "MOV EBP,dword ptr [EDX + 0x4]"
    },
    {
      "address": "006959b9",
      "instruction": "CMP dword ptr [EBP + 0x18],EBX"
    },
    {
      "address": "006959bc",
      "instruction": "JNZ 0x006959c7"
    },
    {
      "address": "006959be",
      "instruction": "MOV EAX,dword ptr [ESI + 0xa0c]"
    },
    {
      "address": "006959c4",
      "instruction": "MOV dword ptr [EBP + 0x18],EAX"
    },
    {
      "address": "006959c7",
      "instruction": "MOV EAX,0x1667bac"
    },
    {
      "address": "006959cc",
      "instruction": "MOV ECX,0x1667bad"
    },
    {
      "address": "006959d1",
      "instruction": "MOV dword ptr [ESP + 0x1c],0x13f61cc"
    },
    {
      "address": "006959d9",
      "instruction": "MOV dword ptr [ESP + 0x20],0xffffffff"
    },
    {
      "address": "006959e1",
      "instruction": "MOV dword ptr [ESP + 0x34],EBX"
    },
    {
      "address": "006959e5",
      "instruction": "MOV dword ptr [ESP + 0x38],EBX"
    },
    {
      "address": "006959e9",
      "instruction": "MOV dword ptr [ESP + 0x3c],0x11874d0"
    },
    {
      "address": "006959f1",
      "instruction": "MOV dword ptr [ESP + 0x40],EBX"
    },
    {
      "address": "006959f5",
      "instruction": "MOV dword ptr [ESP + 0x44],EBX"
    },
    {
      "address": "006959f9",
      "instruction": "MOV dword ptr [ESP + 0x48],EBX"
    },
    {
      "address": "006959fd",
      "instruction": "MOV dword ptr [ESP + 0x4c],EBX"
    },
    {
      "address": "00695a01",
      "instruction": "MOV dword ptr [ESP + 0x50],EBX"
    },
    {
      "address": "00695a05",
      "instruction": "MOV dword ptr [ESP + 0x54],EBX"
    },
    {
      "address": "00695a09",
      "instruction": "MOV dword ptr [ESP + 0x24],EBX"
    },
    {
      "address": "00695a0d",
      "instruction": "MOV dword ptr [ESP + 0x5c],EAX"
    },
    {
      "address": "00695a11",
      "instruction": "MOV dword ptr [ESP + 0x60],EAX"
    },
    {
      "address": "00695a15",
      "instruction": "MOV dword ptr [ESP + 0x64],ECX"
    },
    {
      "address": "00695a19",
      "instruction": "MOV dword ptr [ESP + 0x6c],EAX"
    },
    {
      "address": "00695a1d",
      "instruction": "MOV dword ptr [ESP + 0x70],EAX"
    },
    {
      "address": "00695a21",
      "instruction": "MOV dword ptr [ESP + 0x74],ECX"
    },
    {
      "address": "00695a25",
      "instruction": "MOV ESI,dword ptr [EBP]"
    },
    {
      "address": "00695a28",
      "instruction": "MOV EAX,ESI"
    },
    {
      "address": "00695a2a",
      "instruction": "MOV dword ptr [ESP + 0x84],EBX"
    },
    {
      "address": "00695a31",
      "instruction": "LEA EDI,[EAX + 0x1]"
    },
    {
      "address": "00695a34",
      "instruction": "MOV CL,byte ptr [EAX]"
    },
    {
      "address": "00695a36",
      "instruction": "INC EAX"
    },
    {
      "address": "00695a37",
      "instruction": "CMP CL,BL"
    },
    {
      "address": "00695a39",
      "instruction": "JNZ 0x00695a34"
    },
    {
      "address": "00695a3b",
      "instruction": "SUB EAX,EDI"
    },
    {
      "address": "00695a3d",
      "instruction": "ADD EAX,ESI"
    },
    {
      "address": "00695a3f",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00695a40",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00695a41",
      "instruction": "LEA ECX,[ESP + 0x64]"
    },
    {
      "address": "00695a45",
      "instruction": "CALL 0x00454cb0"
    },
    {
      "address": "00695a4a",
      "instruction": "MOV ECX,dword ptr [ESP + 0x14]"
    },
    {
      "address": "00695a4e",
      "instruction": "MOV EDX,dword ptr [ECX + 0xa0c]"
    },
    {
      "address": "00695a54",
      "instruction": "MOV dword ptr [ESP + 0x58],EDX"
    },
    {
      "address": "00695a58",
      "instruction": "MOV ECX,0xf"
    },
    {

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
  "body_end": "00695b32",
  "body_span_bytes": 467,
  "body_start": "00695960",
  "callees": [
    "FUN_006956f0",
    "FUN_00454cb0",
    "FUN_00695490",
    "FUN_00f47380"
  ],
  "callers": [
    "FUN_00c35e70",
    "FUN_00c0bd70",
    "FUN_00c3bc80",
    "FUN_00bcd030",
    "FUN_00c0af90",
    "FUN_00c3f920",
    "FUN_00ff4090",
    "FUN_00b18420",
    "FUN_00c3e490",
    "FUN_00c69a70"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00695960",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "puStack_8",
      "storage": "Stack[-0x8]:4",
      "type": "undefined1 *"
    },
    {
      "name": "iVar5",
      "storage": "register:00000004:4",
      "type": "int"
    },
    {
      "name": "uVar4",
      "storage": "register:00000000:4",
      "type": "undefined4"
    },
    {
      "name": "ppcVar7",
      "storage": "register:0000001c:4",
      "type": "char * *"
    },
    {
      "name": "puVar6",
      "storage": "register:00000018:4",
      "type": "undefined4 *"
    },
    {
      "name": "puVar1",
      "storage": "unique:00017200:4",
      "type": "undefined4 *"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int"
    },
    {
      "name": "pcVar3",
      "storage": "register:00000000:4",
      "type": "char *"
    },
    {
      "name": "pcVar2",
      "storage": "unique:10000110:4",
      "type": "char *"
    },
    {
      "name": "local_78",
      "storage": "Stack[-0x78]:4",
      "type": "undefined4 *"
    },
    {
      "name": "local_70",
      "storage": "Stack[-0x70]:4",
      "type": "int"
    },
    {
      "name": "local_6c",
      "storage": "Stack[-0x6c]:4",
      "type": "char *[6]"
    },
    {
      "name": "local_4c",
      "storage": "Stack[-0x4c]:4",
      "type": "undefined *"
    },
    {
      "name": "local_48",
      "storage": "Stack[-0x48]:4",
      "type": "undefined4"
    },
    {
      "name": "local_54",
      "storage": "Stack[-0x54]:4",
      "type": "undefined4"
    },
    {
      "name": "local_50",
      "storage": "Stack[-0x50]:4",
      "type": "undefined4"
    },
    {
      "name": "local_3c",
      "storage": "Stack[-0x3c]:4",
      "type": "undefined4"
    },
    {
      "name": "local_38",
      "storage": "Stack[-0x38]:4",
      "type": "undefined4"
    },
    {
      "name": "local_44",
      "storage": "Stack[-0x44]:4",
      "type": "undefined4"
    },
    {
      "name": "local_40",
      "storage": "Stack[-0x40]:4",
      "type": "undefined4"
    },
    {
      "name": "local_2c",
      "storage": "Stack[-0x2c]:4",
      "type": "undefined1 *"
    },
    {
      "name": "local_28",
      "storage": "Stack[-0x28]:4",
      "type": "undefined1 *"
    },
    {
      "name": "local_34",
      "storage": "Stack[-0x34]:4",
      "type": "undefined4"
    },
    {
      "name": "local_30",
      "storage": "Stack[-0x30]:4",
      "type": "undefined4"
    },
    {
      "name": "local_18",
      "storage": "Stack[-0x18]:4",
      "type": "undefined1 *"
    },
    {
      "name": "local_14",
      "storage": "Stack[-0x14]:4",
      "type": "undefined1 *"
    },
    {
      "name": "local_24",
      "storage": "Stack[-0x24]:4",
      "type": "undefined1 *"
    },
    {
      "name": "local_1c",
      "storage": "Stack[-0x1c]:4",
      "type": "undefined1 *"
    },
    {
      "name": "local_c",
      "storage": "Stack[-0xc]:4",
      "type": "void *"
    },
    {
      "name": "local_4",
      "storage": "Stack[-0x4]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 30,
  "mode": "live",
  "name": "FUN_00695960",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x295960",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00695960(void)",
  "size_bytes": 467,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00695960",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 40,
  "xrefs": [
    {
      "from": "00bcd067"
    },
    {
      "from": "00bcd08b"
    },
    {
      "from": "00bcd0af"
    },
    {
      "from": "00b18446"
    },
    {
      "from": "00c0afbf"
    },
    {
      "from": "00c0afe5"
    },
    {
      "from": "00c0bdaa"
    },
    {
      "from": "00c0bdde"
    },
    {
      "from": "00c0be04"
    },
    {
      "from": "00c35eaa"
    },
    {
      "from": "00c35ed0"
    },
    {
      "from": "00c3bcc8"
    },
    {
      "from": "00c3bcee"
    },
    {
      "from": "00c3e4ca"
    },
    {
      "from": "00c3e4f0"
    },
    {
      "from": "00c3f952"
    },
    {
      "from": "00c3f982"
    },
    {
      "from": "00c69aaa"
    },
    {
      "from": "00c69ad0"
    },
    {
      "from": "00ff40c8"
    },
    {
      "from": "00ff40f0"
    },
    {
      "from": "00aff3e3"
    },
    {
      "from": "00aff5c3"
    },
    {
      "from": "00aff786"
    },
    {
      "from": "00ba2656"
    },
    {
      "from": "00bd6b46"
    },
    {
      "from": "00bf3a23"
    },
    {
      "from": "00c030f3"
    },
    {
      "from": "00c2e496"
    },
    {
      "from": "00c2e766"
    },
    {
      "from": "00c2e966"
    },
    {
      "from": "00c2eb46"
    },
    {
      "from": "00c3ebb3"
    },
    {
      "from": "00c401e3"
    },
    {
      "from": "00c44b66"
   
[TRUNCATED]
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
