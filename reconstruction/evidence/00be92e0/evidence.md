# Evidence 0x00be92e0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `94569fa4c110f5769f96179df2ce92642d79eebf8be32fc3e582245765f91b21`

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
      "entry_ESP+0x8",
      "entry_ESP+0xc",
      "entry_ESP+0x14",
      "entry_ESP+0x18",
      "entry_ESP+0x1c",
      "entry_ESP+0x24",
      "entry_ESP+0x2c",
      "entry_ESP+0x38",
      "entry_ESP+0x3c",
      "entry_ESP+0x84",
      "entry_ESP+0x8c"
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
        "entry_offset": "entry_ESP+0x14",
        "observed": true,
        "ordinal": 5,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x18",
        "observed": true,
        "ordinal": 6,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x1c",
        "observed": true,
        "ordinal": 7,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x24",
        "observed": true,
        "ordinal": 9,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x2c",
        "observed": true,
        "ordinal": 11,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x38",
        "observed": true,
        "ordinal": 14,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x3c",
        "observed": true,
        "ordinal": 15,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x84",
        "observed": true,
        "ordinal": 33,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x8c",
        "observed": true,
        "ordinal": 35,
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
    "ret_form": "RET 0x14",
    "return_register": "XMM0",
    "return_semantics": "float_or_x87_in_XMM0",
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
        "entry_offset": "entry_ESP+0x8",
        "observed": true,
        "ordinal": 2,
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
        "entry_offset": "entry_ESP+0x14",
        "observed": true,
        "ordinal": 5,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x18",
        "observed": true,
        "ordinal": 6,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x1c",
        "observed": true,
        "ordinal": 7,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x24",
        "observed": true,
        "ordinal": 9,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x2c",
        "observed": true,
        "ordinal": 11,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x38",
        "observed": true,
        "ordinal": 14,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x3c",
        "observed": true,
        "ordinal": 15,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x84",
        "observed": true,
        "ordinal": 33,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
   
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
"\n/* WARNING: Enum \"ObjectTYPE\": Some values do not have unique names */\n/* WARNING: Enum \"Names\": Some values do not have unique names */\n\nvoid __thiscall\nFUN_00be92e0(int param_1,int param_2,undefined4 param_3,undefined4 param_4,char param_5,\n            undefined4 param_6)\n\n{\n  int *piVar1;\n  bool bVar2;\n  char cVar3;\n  int iVar4;\n  int iVar5;\n  undefined4 uVar6;\n  cUIEventLog *pcVar7;\n  IAppSystem *pIVar8;\n  undefined *puVar9;\n  char *pcVar10;\n  undefined4 uVar11;\n  undefined1 *puVar12;\n  int *piVar13;\n  undefined4 uVar14;\n  undefined4 uVar15;\n  undefined4 uVar16;\n  undefined4 uStack_7c;\n  int iStack_78;\n  PropertyList *pPStack_74;\n  IWinProc__vftable *pIStack_70;\n  undefined1 auStack_6c [12];\n  undefined1 auStack_60 [32];\n  undefined4 uStack_40;\n  undefined1 auStack_30 [48];\n  \n  *(undefined4 *)(param_1 + 0x29c) = param_3;\n  iVar4 = (**(code **)(**(int **)(param_1 + 0x590) + 0x4c))();\n  if (param_2 == iVar4) {\n    return;\n  }\n  piVar1 = *(int **)(param_1 + 0x590);\n  if (piVar1 != (int *)0x0) {\n    (**(code **)*piVar1)();\n  }\n  iVar4 = param_2;\n  FUN_00b3d300(param_2);\n  iVar4 = FUN_00b25f40(iVar4);\n  if (iVar4 == 0) {\n    if (piVar1 == (int *)0x0) {\n      return;\n    }\n    (**(code **)(*piVar1 + 4))();\n    return;\n  }\n  (**(code **)(*(int *)(param_1 + 0x120) + 0x58))();\n  FUN_00b3d300();\n  iVar5 = FUN_00b25fb0();\n  *(int *)(iVar4 + 0x44c) = param_1;\n  uVar6 = FUN_00befab0();\n  *(undefined4 *)(iVar4 + 0x4bc) = uVar6;\n  *(undefined1 *)(param_1 + 0x2e0) = 1;\n  *(undefined1 *)(param_1 + 0x2e1) = 1;\n  *(undefined1 *)(param_1 + 0x2e2) = 1;\n  *(undefined1 *)(param_1 + 0x2e3) = 1;\n  *(undefined1 *)(param_1 + 0x2e4) = 1;\n  *(undefined1 *)(param_1 + 0x2e5) = 1;\n  *(undefined1 *)(param_1 + 0x2e6) = 1;\n  *(undefined4 *)(param_1 + 0x74c) = 0xffffffff;\n  *(undefined4 *)(param_1 + 0x748) = 0;\n  *(undefined4 *)(param_1 + 0x754) = 0xffffffff;\n  *(undefined4 *)(param_1 + 0x750) = 0;\n  *(undefined4 *)(param_1 + 0x75c) = 0xffffffff;\n  *(undefined4 *)(param_1 + 0x758) = 0;\n  iStack_78 = *(int *)(iVar4 + 0xc4);\n  pPStack_74 = *(PropertyList **)(iVar4 + 200);\n  pIStack_70 = *(IWinProc__vftable **)(iVar4 + 0xcc);\n  pcVar7 = Simulator__cUIEventLog__Get();\n  pcVar7->field_68 = iStack_78;\n  (pcVar7->mpPropList).ptr = pPStack_74;\n  pcVar7[1]._vftable0 = pIStack_70;\n  *(int *)(param_1 + 0x7d8) = piVar1[0x31];\n  *(int *)(param_1 + 0x7dc) = piVar1[0x32];\n  *(int *)(param_1 + 0x7e0) = piVar1[0x33];\n  *(undefined4 *)(param_1 + 0x7e4) = *(undefined4 *)(iVar4 + 0xc4);\n  *(undefined4 *)(param_1 + 0x7e8) = *(undefined4 *)(iVar4 + 200);\n  *(undefined4 *)(param_1 + 0x7ec) = *(undefined4 *)(iVar4 + 0xcc);\n  if ((*(int *)(param_1 + 0x29c) == 0) || (*(int *)(param_1 + 0x29c) == 1)) {\n    FUN_00be45b0(0,param_1);\n    pIVar8 = App__IAppSystem__Get();\n    (*pIVar8->_vftable0->InitPlugins)((IAppSystem *)0x66e0e11,(CommandLine *)0x0);\n  }\n  puVar9 = (undefined *)FUN_00b5b800();\n  if ((puVar9 != &DAT_01654c04) || (iVar4 != iVar5)) {\n    FUN_00be88d0(param_2,param_4,param_6);\n    goto LAB_00be9837;\n  }\n  if ((*(int **)(param_1 + 0x810) != (int *)0x0) &&\n     (cVar3 = (**(code **)(**(int **)(param_1 + 0x810) + 0x10))(), cVar3 != '\\0')) {\n    (**(code **)(**(int **)(param_1 + 0x810) + 0xc))(0);\n    FUN_00dc4c60();\n    FUN_00bc3110();\n    iVar4 = 0;\n    if (0 < (int)(*(int *)(param_1 + 0x344) - *(int *)(param_1 + 0x340) & 0xfffffffcU)) {\n      do {\n        FUN_00bfc6a0();\n        iVar4 = iVar4 + 1;\n      } while (iVar4 < *(int *)(param_1 + 0x344) - *(int *)(param_1 + 0x340) >> 2);\n    }\n    FUN_00be2440(param_1,0,0);\n  }\n  FUN_00b3d300();\n  FUN_00f67d90();\n  if (((char)param_4 != '\\0') || (*(char *)(param_1 + 0x762) != '\\0')) {\n    FUN_00be88d0(param_2,param_4,param_6);\n    FUN_00cf74c0();\n    cVar3 = FUN_00cf75d0();\n    if (cVar3 != '\\0') {\n      FUN_00cf74c0();\n      FUN_00cf8e00();\n      FUN_00cf74c0();\n      FUN_00cf7520();\n    }\n    goto LAB_00be9837;\n  }\n  if (*(int *)(param_1 + 800) == 0) {\n    iVar4 = 0;\n  }\n  else {\n    iVar4 = *(int *)(param_1 + 800) + 0x34;\n  }\n  FUN_00ad7a30(iVar4);\n  uVar15 = 0;\n  puVar12 = auStack_30;\n  uVar6 = 0x115fa309;\n  Simulator__cSpaceTrading__Get();\n  FUN_00ae09b0(uVar6,puVar12,uVar15);\n  FUN_00bd7f70(auStack_6c,&uStack_7c);\n  uVar6 = FUN_00ad7b70();\n  FUN_00ad79d0(auStack_6c,uVar6);\n  uVar15 = 0;\n  puVar12 = auStack_60;\n  uVar6 = 0x3f04cafe;\n  uStack_40 = uStack_7c;\n  Simulator__cSpaceTrading__Get();\n  FUN_00ae09b0(uVar6,puVar12,uVar15);\n  iVar4 = *(int *)(param_1 + 0x540);\n  bVar2 = false;\n  iStack_78 = 0;\n  pPStack_74 = (PropertyList *)0x0;\n  pIStack_70 = (IWinProc__vftable *)0x9969ac08;\n  if (iVar4 == 0) {\n    cVar3 = FUN_00c772c0(0x46bddaa);\n    if (cVar3 == '\\0') {\n      uVar6 = 0x46bddaa;\n      goto LAB_00be9686;\n    }\n  }\n  else if (iVar4 == 1) {\n    cVar3 = FUN_00c772c0(0x46bdddc);\n    if (cVar3 == '\\0') {\n      uVar6 = 0x46bdddc;\n      goto LAB_00be9686;\n    }\n  }\n  else {\n    bVar2 = false;\n    if ((iVar4 == 2) && (cVar3 = FUN_00c772c0(0x46bdde0), cVar3 == '\\0')) {\n      uVar6 = 0x46bdde0;\nLAB_00be9686:\n      FUN_00c77bf0(uVar6);\n      bVar2 = true;\n    }\n  }\n  iVar4 = *(int *)(param_1 + 0x29c);\n  if ((((iVar4 == 0) && (*(int *)(param_1 + 0x540) == 0)) ||\n      ((iVar4 == 1 && (*(int *)(param_1 + 0x540) == 1)))) ||\n     ((iVar4 == 2 && (*(int *)(param_1 + 0x540) == 2)))) {\n    if (iVar4 == 0) {\n      iStack_78 = 0x803;\n    }\n    else if (iVar4 == 1) {\n      iStack_78 = 0x804;\n    }\n    else if (iVar4 == 2) {\n      iStack_78 = 0x805;\n    }\n  }\n  else {\n    iVar5 = *(int *)(param_1 + 0x540);\n    if (iVar5 == 0) {\n      if (bVar2) {\n        iStack_78 = (uint)(iVar4 != 1) * 2 + 0x902;\n      }\n      else {\n        iStack_78 = (uint)(iVar4 != 1) * 8 + 0x908;\n      }\n    }\n    else if (iVar5 == 1) {\n      if (bVar2) {\n        iStack_78 = (-(uint)(iVar4 != 0) & 5) + 0x900;\n      }\n    
[TRUNCATED]
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "original_bytes": 32071,
  "preview": "{\n  \"count\": 386,\n  \"instructions\": [\n    {\n      \"address\": \"00be92e0\",\n      \"instruction\": \"MOV EAX,dword ptr [ESP + 0x8]\"\n    },\n    {\n      \"address\": \"00be92e4\",\n      \"instruction\": \"SUB ESP,0x80\"\n    },\n    {\n      \"address\": \"00be92ea\",\n      \"instruction\": \"PUSH EBP\"\n    },\n    {\n      \"address\": \"00be92eb\",\n      \"instruction\": \"PUSH ESI\"\n    },\n    {\n      \"address\": \"00be92ec\",\n      \"instruction\": \"MOV ESI,ECX\"\n    },\n    {\n      \"address\": \"00be92ee\",\n      \"instruction\": \"MOV ECX,dword ptr [ESI + 0x590]\"\n    },\n    {\n      \"address\": \"00be92f4\",\n      \"instruction\": \"MOV dword ptr [ESI + 0x29c],EAX\"\n    },\n    {\n      \"address\": \"00be92fa\",\n      \"instruction\": \"MOV EDX,dword ptr [ECX]\"\n    },\n    {\n      \"address\": \"00be92fc\",\n      \"instruction\": \"MOV EAX,dword ptr [EDX + 0x4c]\"\n    },\n    {\n      \"address\": \"00be92ff\",\n      \"instruction\": \"CALL EAX\"\n    },\n    {\n      \"address\": \"00be9301\",\n      \"instruction\": \"MOV EBP,dword ptr [ESP + 0x8c]\"\n    },\n    {\n      \"address\": \"00be9308\",\n      \"instruction\": \"CMP EBP,EAX\"\n    },\n    {\n      \"address\": \"00be930a\",\n      \"instruction\": \"JZ 0x00be9844\"\n    },\n    {\n      \"address\": \"00be9310\",\n      \"instruction\": \"PUSH EBX\"\n    },\n    {\n      \"address\": \"00be9311\",\n      \"instruction\": \"MOV EBX,dword ptr [ESI + 0x590]\"\n    },\n    {\n      \"address\": \"00be9317\",\n      \"instruction\": \"MOV dword ptr [ESP + 0xc],EBX\"\n    },\n    {\n      \"address\": \"00be931b\",\n      \"instruction\": \"TEST EBX,EBX\"\n    },\n    {\n      \"address\": \"00be931d\",\n      \"instruction\": \"JZ 0x00be9327\"\n    },\n    {\n      \"address\": \"00be931f\",\n      \"instruction\": \"MOV EDX,dword ptr [EBX]\"\n    },\n    {\n      \"address\": \"00be9321\",\n      \"instruction\": \"MOV EAX,dword ptr [EDX]\"\n    },\n    {\n      \"address\": \"00be9323\",\n      \"instruction\": \"MOV ECX,EBX\"\n    },\n    {\n      \"address\": \"00be9325\",\n      \"instruction\": \"CALL EAX\"\n    },\n    {\n      \"address\": \"00be9327\",\n      \"instruction\": \"PUSH EDI\"\n    },\n    {\n      \"address\": \"00be9328\",\n      \"instruction\": \"PUSH EBP\"\n    },\n    {\n      \"address\": \"00be9329\",\n      \"instruction\": \"CALL 0x00b3d300\"\n    },\n    {\n      \"address\": \"00be932e\",\n      \"instruction\": \"MOV ECX,EAX\"\n    },\n    {\n      \"address\": \"00be9330\",\n      \"instruction\": \"CALL 0x00b25f40\"\n    },\n    {\n      \"address\": \"00be9335\",\n      \"instruction\": \"MOV EDI,EAX\"\n    },\n    {\n      \"address\": \"00be9337\",\n      \"instruction\": \"TEST EDI,EDI\"\n    },\n    {\n      \"address\": \"00be9339\",\n      \"instruction\": \"JNZ 0x00be9359\"\n    },\n    {\n      \"address\": \"00be933b\",\n      \"instruction\": \"TEST EBX,EBX\"\n    },\n    {\n      \"address\": \"00be933d\",\n      \"instruction\": \"JZ 0x00be9842\"\n    },\n    {\n      \"address\": \"00be9343\",\n      \"instruction\": \"MOV EDX,dword ptr [EBX]\"\n    },\n    {\n      \"address\": \"00be9345\",\n      \"instruction\": \"MOV EAX,dword ptr [EDX + 0x4]\"\n    },\n    {\n      \"address\": \"00be9348\",\n      \"instruction\": \"MOV ECX,EBX\"\n    },\n    {\n      \"address\": \"00be934a\",\n      \"instruction\": \"CALL EAX\"\n    },\n    {\n      \"address\": \"00be934c\",\n      \"instruction\": \"POP EDI\"\n    },\n    {\n      \"address\": \"00be934d\",\n      \"instruction\": \"POP EBX\"\n    },\n    {\n      \"address\": \"00be934e\",\n      \"instruction\": \"POP ESI\"\n    },\n    {\n      \"address\": \"00be934f\",\n      \"instruction\": \"POP EBP\"\n    },\n    {\n      \"address\": \"00be9350\",\n      \"instruction\": \"ADD ESP,0x80\"\n    },\n    {\n      \"address\": \"00be9356\",\n      \"instruction\": \"RET 0x14\"\n    },\n    {\n      \"address\": \"00be9359\",\n      \"instruction\": \"MOV EDX,dword ptr [ESI + 0x120]\"\n    },\n    {\n      \"address\": \"00be935f\",\n      \"instruction\": \"MOV EAX,dword ptr [EDX + 0x58]\"\n    },\n    {\n      \"address\": \"00be9362\",\n      \"instruction\": \"LEA ECX,[ESI + 0x120]\"\n    },\n    {\n      \"address\": \"00be9368\",\n      \"instruction\": \"CALL EAX\"\n    },\n    {\n      \"address\": \"00be936a\",\n      \"instruction\": \"CALL 0x00b3d300\"\n    },\n    {\n      \"address\": \"00be936f\",\n      \"instruction\": \"MOV ECX,EAX\"\n    },\n    {\n      \"address\": \"00be9371\",\n      \"instruction\": \"CALL 0x00b25fb0\"\n    },\n    {\n      \"address\": \"00be9376\",\n      \"instruction\": \"CMP EDI,EAX\"\n    },\n    {\n      \"address\": \"00be9378\",\n      \"instruction\": \"MOV ECX,EDI\"\n    },\n    {\n      \"address\": \"00be937a\",\n      \"instruction\": \"SETZ BL\"\n    },\n    {\n      \"address\": \"00be937d\",\n      \"instruction\": \"MOV dword ptr [EDI + 0x44c],ESI\"\n    },\n    {\n      \"address\": \"00be9383\",\n      \"instruction\": \"CALL 0x00befab0\"\n    },\n    {\n      \"address\": \"00be9388\",\n      \"instruction\": \"XORPS XMM0,XMM0\"\n    },\n    {\n      \"address\": \"00be938b\",\n      \"instruction\": \"MOV dword ptr [EDI + 0x4bc],EAX\"\n    },\n    {\n      \"address\": \"00be9391\",\n      \"instruction\": \"OR EAX,0xffffffff\"\n    },\n    {\n      \"address\": \"00be9394\",\n      \"instruction\": \"MOV byte ptr [ESI + 0x2e0],0x1\"\n    },\n    {\n      \"address\": \"00be939b\",\n      \"instruction\": \"MOV byte ptr [ESI + 0x2e1],0x1\"\n    },\n    {\n      \"address\": \"00be93a2\",\n      \"instruction\": \"MOV byte ptr [ESI + 0x2e2],0x1\"\n    },\n    {\n      \"address\": \"00be93a9\",\n      \"instruction\": \"MOV byte ptr [ESI + 0x2e3],0x1\"\n    },\n    {\n      \"address\": \"00be93b0\",\n      \"instruction\": \"MOV byte ptr [ESI + 0x2e4],0x1\"\n    },\n    {\n      \"a
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
  "body_end": "00be984e",
  "body_span_bytes": 1391,
  "body_start": "00be92e0",
  "callees": [
    "App::IAppSystem::Get",
    "FUN_00adde90",
    "FUN_00be88d0",
    "FUN_00be45b0",
    "FUN_00ad7b70",
    "FUN_00c772c0",
    "FUN_00ae0930",
    "FUN_00dc4c60",
    "FUN_00ad7ad0",
    "FUN_00b3d300",
    "Simulator::cUIEventLog::Get",
    "FUN_00be2440",
    "FUN_00b5b800",
    "Simulator::cSpaceTrading::Get",
    "FUN_00bd7f70",
    "FUN_00cf8e00",
    "FUN_00befab0",
    "FUN_00f67d90",
    "FUN_00ad79d0",
    "FUN_00b25fb0",
    "FUN_00bc3110",
    "FUN_00cf7520",
    "FUN_00bfc6a0",
    "FUN_00bc3130",
    "FUN_00cf74c0",
    "FUN_00cf75d0",
    "FUN_00b25f40",
    "FUN_00c77bf0",
    "FUN_00ad7a30",
    "FUN_00ae09b0"
  ],
  "callers": [
    "FUN_00be9cb0",
    "FUN_00be9980",
    "FUN_00be9850",
    "FUN_00beaa30"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00be92e0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "iStack_78",
      "storage": "Stack[-0x78]:4",
      "type": "int"
    },
    {
      "name": "pPStack_74",
      "storage": "Stack[-0x74]:4",
      "type": "PropertyList *"
    },
    {
      "name": "uStack_7c",
      "storage": "Stack[-0x7c]:4",
      "type": "undefined4"
    },
    {
      "name": "param_5",
      "storage": "Stack[0x10]:1",
      "type": "char"
    },
    {
      "name": "param_6",
      "storage": "Stack[0x14]:4",
      "type": "undefined4"
    },
    {
      "name": "param_3",
      "storage": "Stack[0x8]:4",
      "type": "undefined4"
    },
    {
      "name": "param_4",
      "storage": "Stack[0xc]:4",
      "type": "undefined4"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int"
    },
    {
      "name": "param_2",
      "storage": "Stack[0x4]:4",
      "type": "int"
    },
    {
      "name": "auStack_30",
      "storage": "",
      "type": "undefined1[48]"
    },
    {
      "name": "auStack_60",
      "storage": "",
      "type": "undefined1[32]"
    },
    {
      "name": "uStack_40",
      "storage": "Stack[-0x40]:4",
      "type": "undefined4"
    },
    {
      "name": "pIStack_70",
      "storage": "Stack[-0x70]:4",
      "type": "IWinProc__vftable *"
    },
    {
      "name": "auStack_6c",
      "storage": "",
      "type": "undefined1[12]"
    },
    {
      "name": "uVar15",
      "storage": "Stack[-0x94]:4",
      "type": "undefined4"
    },
    {
      "name": "uVar16",
      "storage": "Stack[-0x94]:4",
      "type": "undefined4"
    },
    {
      "name": "piVar13",
      "storage": "Stack[-0x98]:4",
      "type": "int *"
    },
    {
      "name": "uVar14",
      "storage": "Stack[-0x98]:4",
      "type": "undefined4"
    },
    {
      "name": "uVar11",
      "storage": "Stack[-0x9c]:4",
      "type": "undefined4"
    },
    {
      "name": "puVar12",
      "storage": "Stack[-0x98]:4",
      "type": "undefined1 *"
    },
    {
      "name": "puVar9",
      "storage": "register:00000000:4",
      "type": "undefined *"
    },
    {
      "name": "pcVar10",
      "storage": "register:00000000:4",
      "type": "char *"
    },
    {
      "name": "pcVar7",
      "storage": "register:00000000:4",
      "type": "cUIEventLog *"
    },
    {
      "name": "pIVar8",
      "storage": "register:00000000:4",
      "type": "IAppSystem *"
    },
    {
      "name": "iVar5",
      "storage": "register:00000000:4",
      "type": "int"
    },
    {
      "name": "uVar6",
      "storage": "register:00000000:4",
      "type": "undefined4"
    },
    {
      "name": "cVar3",
      "storage": "register:00000000:1",
      "type": "char"
    },
    {
      "name": "iVar4",
      "storage": "register:00000000:4",
      "type": "int"
    },
    {
      "name": "piVar1",
      "storage": "unique:00017200:4",
      "type": "int *"
    },
    {
      "name": "bVar2",
      "storage": "unique:1000033b:1",
      "type": "bool"
    }
  ],
  "locals_count": 30,
  "mode": "live",
  "name": "FUN_00be92e0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x7e92e0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00be92e0(void)",
  "size_bytes": 1391,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00be92e0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 4,
  "xrefs": [
    {
      "from": "00beaba4"
    },
    {
      "from": "00be9d4c"
    },
    {
      "from": "00be995e"
    },
    {
      "from": "00be9af3"
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
