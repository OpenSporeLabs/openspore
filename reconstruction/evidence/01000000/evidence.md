# Evidence 0x01000000

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `2a929624cf25710f858c86583d2df9af730dba46c3d165b0c3c0ba6171fe47b7`

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
      "entry_ESP+0x30"
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
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x30",
        "observed": true,
        "ordinal": 12,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x4",
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
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x30",
        "observed": true,
        "ordinal": 12,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "termination": "RET 0x4"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -24, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
    "ret_imm_below_highest_slot: ret 0x4 pops less than the highest read slot 0x30; everything above it belongs to the caller's frame",
    "slot_gaps_present: argument ordinal(s) below the highest read slot are never touched",
    "no_discriminator: the callee pop of 0x4 is not a whole number of dword stack arguments, so no convention follows from it",
    "sret_vs_out_param: entry slot 0 is written through a pointer"
  ],
  "cleanup": {
    "bytes": 4,
    "confidence": "UNKNOWN",
    "corroboration": "not_available",
    "evidence": "ret 0x4 but entry slot 0x30 is read",
    "side": null
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "08c84419901ff7e97c465968702791541e915afe8a6eae92492446e453bced3f",
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
    "indirect_calls": 13,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0043",
        "obs-0135"
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
        "obs-0043",
        "obs-0135"
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
        "obs-0011",
        "obs-0067",
        "obs-0070",
        "obs-0073",
        "obs-0080"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 8,
        "observed_slots": 4,
        "total_bytes": 48
      }
    },
    {
      "based_on": [
        "obs-0007",
        "obs-0008",
        "obs-0014",
        "obs-0023",
        "obs-0036",
        "obs-0054",
        "obs-0059",
        "obs-0063",
        "obs-0070",
        "obs-0078",
        "obs-0083",
        "obs-0089",
        "obs-0095",
        "obs-0097",
        "obs-0101",
        "obs-0102",
        "obs-0103",
        "obs-0107",
        "obs-0110",
        "obs-0111",
        "obs-0116"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          64
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0135"
      ],
      "claim": "the calling convention is unknown: the terminal pop is not a whole number of dword arguments",
      "confidence": "UNKNOWN",
      "id": "C10"
    
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
"\n/* WARNING: Removing unreachable block (ram,0x01000288) */\n/* WARNING: Removing unreachable block (ram,0x01000164) */\n/* WARNING: Removing unreachable block (ram,0x0100026f) */\n/* WARNING: Removing unreachable block (ram,0x01000297) */\n/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */\n\nvoid __thiscall FUN_01000000(int param_1,int param_2)\n\n{\n  char cVar1;\n  int iVar2;\n  int iVar3;\n  int *piVar4;\n  int *piVar5;\n  int iVar6;\n  undefined4 *puVar7;\n  int iVar8;\n  int iVar9;\n  uint uVar10;\n  int *unaff_EDI;\n  undefined4 *puVar11;\n  int iVar12;\n  int iVar13;\n  float10 fVar14;\n  undefined4 uVar15;\n  undefined4 uVar16;\n  undefined4 uVar17;\n  undefined1 *puVar18;\n  undefined4 uVar19;\n  undefined1 *puVar20;\n  undefined4 uVar21;\n  undefined4 uVar22;\n  int iStack_94;\n  undefined1 auStack_8c [4];\n  undefined4 local_88;\n  int local_80;\n  int local_7c;\n  int local_78;\n  int aiStack_74 [3];\n  ushort uStack_68;\n  short sStack_66;\n  undefined4 uStack_64;\n  undefined4 uStack_60;\n  undefined4 uStack_5c;\n  float fStack_58;\n  undefined4 auStack_54 [9];\n  undefined1 auStack_30 [48];\n  \n  iVar2 = FUN_01021300();\n  local_88 = *(undefined4 *)(param_2 + 0x13c);\n  iVar3 = FUN_00c71e30();\n  if ((iVar2 == iVar3) && (cVar1 = FUN_0102adf0(param_2), cVar1 == '\\0')) {\n    FUN_01002bd0();\n    piVar4 = (int *)FUN_00a1ad60();\n    piVar5 = (int *)FUN_00b8dad0();\n    local_80 = *piVar5;\n    local_7c = piVar5[1];\n    local_78 = piVar5[2];\n    iVar2 = FUN_00c70fd0(0);\n    iVar3 = (**(code **)(*piVar4 + 100))(4,&local_80);\n    if (iVar3 == -1) {\n      iVar3 = (**(code **)(*piVar4 + 0x8c))();\n      if (iVar3 == 0) goto LAB_010000b6;\n    }\n    else {\n      iVar3 = (**(code **)(*piVar4 + 0x60))(iVar3);\n      FUN_0102f810();\n      iVar6 = FUN_0102ff00();\n      iVar6 = iVar6 - *(int *)(iVar3 + 0x10);\n      if ((iVar6 < 1) && (0 < iVar2)) {\nLAB_010000b6:\n        uVar22 = 0;\n        uVar21 = 1;\n        uVar19 = 0;\n        uVar17 = 0;\n        uVar16 = 0x131a9f54;\n        uVar15 = 0x2a84f6ca;\n        FUN_00b3d3e0(0x2a84f6ca,0x131a9f54,0,0,1,0);\n        FUN_00dd8640(uVar15,uVar16,uVar17,uVar19,uVar21,uVar22);\n        return;\n      }\n      if (iVar6 < iVar2) {\n        iVar2 = iVar6;\n      }\n    }\n    iVar2 = FUN_00c70fd0(iVar2);\n    if (0 < iVar2) {\n      FUN_00feb9f0();\n      cVar1 = FUN_00feba90();\n      if (cVar1 != '\\0') {\n        FUN_01041c50(\"SPG_FirstSpicePickup\",0x338e034e,1);\n      }\n      uVar22 = 0;\n      uVar21 = 1;\n      uVar19 = 0;\n      uVar17 = 0;\n      uVar16 = 0x131a9f54;\n      uVar15 = 0xe0439cfa;\n      FUN_00b3d3e0(0xe0439cfa,0x131a9f54,0,0,1,0);\n      FUN_00dd8640(uVar15,uVar16,uVar17,uVar19,uVar21,uVar22);\n      piVar4 = (int *)FUN_0067ddd0();\n      cVar1 = (**(code **)(*piVar4 + 0x2c))(0xbb1ceb80,0,&stack0xffffff60);\n      if (cVar1 != '\\0') {\n        FUN_00434040();\n        puVar7 = (undefined4 *)(**(code **)(*(int *)(*(int *)(param_1 + 0x40) + 0x34) + 0x2c))();\n        uStack_64 = *puVar7;\n        uStack_60 = puVar7[1];\n        uStack_5c = puVar7[2];\n        uStack_68 = uStack_68 | 4;\n        sStack_66 = sStack_66 + 1;\n        uVar15 = (**(code **)(*(int *)(*(int *)(param_1 + 0x40) + 0x34) + 0x30))();\n        puVar7 = (undefined4 *)QuaternionToMatrix(auStack_30,uVar15);\n        iVar3 = *(int *)(param_1 + 0x40);\n        puVar11 = auStack_54;\n        for (iVar6 = 9; iVar6 != 0; iVar6 = iVar6 + -1) {\n          *puVar11 = *puVar7;\n          puVar7 = puVar7 + 1;\n          puVar11 = puVar11 + 1;\n        }\n        uStack_68 = uStack_68 | 2;\n        sStack_66 = sStack_66 + 1;\n        fVar14 = (float10)(**(code **)(*(int *)(iVar3 + 0x34) + 0x34))();\n        sStack_66 = sStack_66 + 1;\n        fStack_58 = (float)fVar14;\n        (**(code **)(_DAT_00000000 + 0x14))(&uStack_68);\n        (**(code **)(*unaff_EDI + 8))(0);\n      }\n      FUN_00fffdd0(1,iVar2);\n      uVar15 = 0;\n      puVar20 = auStack_8c;\n      puVar18 = &stack0xffffff64;\n      iVar3 = iVar2;\n      FUN_00b3d3d0(puVar18,puVar20,iVar2,0);\n      FUN_0103a480(puVar18,puVar20,iVar3,uVar15);\n    }\n    piVar4 = (int *)FUN_00b8dad0();\n    iVar6 = *piVar4;\n    iVar3 = (*(int *)(iStack_94 + 0x138) - *(int *)(iStack_94 + 0x134)) / 0x2c + -1;\n    if (-1 < iVar3) {\n      iVar12 = iVar3 * 0x2c;\n      do {\n        piVar4 = (int *)(*(int *)(iStack_94 + 0x134) + iVar12);\n        if ((((*(byte *)(piVar4 + 10) & 8) != 0) && (*(char *)((int)piVar4 + 0x12) == '\\x04')) &&\n           (*piVar4 != iVar6)) {\n          iVar8 = FUN_00b3d3d0();\n          iVar8 = (*(int *)(iVar8 + 0x24) - *(int *)(iVar8 + 0x20)) / 0xc;\n          if (0 < iVar8) {\n            iVar13 = 0;\n            do {\n              iVar9 = FUN_00b3d3d0();\n              if (*piVar4 == *(int *)(iVar13 + *(int *)(iVar9 + 0x20))) {\n                uVar10 = (uint)*(ushort *)(piVar4 + 4);\n                piVar5 = aiStack_74;\n                aiStack_74[1] = 0;\n                aiStack_74[2] = 0;\n                aiStack_74[0] = *piVar4;\n                FUN_00b3d3d0(piVar5,uVar10);\n                FUN_0103fc10(piVar5,uVar10);\n                local_80 = *piVar4;\n                local_7c = 0;\n                local_78 = 0;\n                FUN_00c71160(iStack_94,&local_80,(short)piVar4[4]);\n              }\n              iVar13 = iVar13 + 0xc;\n              iVar8 = iVar8 + -1;\n            } while (iVar8 != 0);\n          }\n        }\n        iVar3 = iVar3 + -1;\n        iVar12 = iVar12 + -0x2c;\n      } while (-1 < iVar3);\n    }\n    uVar15 = 0x10;\n    FUN_01002bd0(0x10);\n    iVar3 = FUN_01005180(uVar15);\n    FUN_007eb820(8);\n    *(int *)(*(int *)(iVar3 + 0xc) + 0x1c) = iVar2;\n  }\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "original_bytes": 26440,
  "preview": "{\n  \"count\": 318,\n  \"instructions\": [\n    {\n      \"address\": \"01000000\",\n      \"instruction\": \"SUB ESP,0x94\"\n    },\n    {\n      \"address\": \"01000006\",\n      \"instruction\": \"PUSH EBX\"\n    },\n    {\n      \"address\": \"01000007\",\n      \"instruction\": \"PUSH EBP\"\n    },\n    {\n      \"address\": \"01000008\",\n      \"instruction\": \"PUSH ESI\"\n    },\n    {\n      \"address\": \"01000009\",\n      \"instruction\": \"PUSH EDI\"\n    },\n    {\n      \"address\": \"0100000a\",\n      \"instruction\": \"MOV EBP,ECX\"\n    },\n    {\n      \"address\": \"0100000c\",\n      \"instruction\": \"CALL 0x01021300\"\n    },\n    {\n      \"address\": \"01000011\",\n      \"instruction\": \"MOV EDI,dword ptr [ESP + 0xa8]\"\n    },\n    {\n      \"address\": \"01000018\",\n      \"instruction\": \"MOV ESI,dword ptr [EDI + 0x13c]\"\n    },\n    {\n      \"address\": \"0100001e\",\n      \"instruction\": \"MOV ECX,EDI\"\n    },\n    {\n      \"address\": \"01000020\",\n      \"instruction\": \"MOV EBX,EAX\"\n    },\n    {\n      \"address\": \"01000022\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x1c],ESI\"\n    },\n    {\n      \"address\": \"01000026\",\n      \"instruction\": \"CALL 0x00c71e30\"\n    },\n    {\n      \"address\": \"0100002b\",\n      \"instruction\": \"CMP EBX,EAX\"\n    },\n    {\n      \"address\": \"0100002d\",\n      \"instruction\": \"JNZ 0x010003d7\"\n    },\n    {\n      \"address\": \"01000033\",\n      \"instruction\": \"PUSH EDI\"\n    },\n    {\n      \"address\": \"01000034\",\n      \"instruction\": \"CALL 0x0102adf0\"\n    },\n    {\n      \"address\": \"01000039\",\n      \"instruction\": \"ADD ESP,0x4\"\n    },\n    {\n      \"address\": \"0100003c\",\n      \"instruction\": \"TEST AL,AL\"\n    },\n    {\n      \"address\": \"0100003e\",\n      \"instruction\": \"JNZ 0x010003d7\"\n    },\n    {\n      \"address\": \"01000044\",\n      \"instruction\": \"CALL 0x01002bd0\"\n    },\n    {\n      \"address\": \"01000049\",\n      \"instruction\": \"MOV ECX,EAX\"\n    },\n    {\n      \"address\": \"0100004b\",\n      \"instruction\": \"CALL 0x00a1ad60\"\n    },\n    {\n      \"address\": \"01000050\",\n      \"instruction\": \"MOV ECX,ESI\"\n    },\n    {\n      \"address\": \"01000052\",\n      \"instruction\": \"MOV EBX,EAX\"\n    },\n    {\n      \"address\": \"01000054\",\n      \"instruction\": \"CALL 0x00b8dad0\"\n    },\n    {\n      \"address\": \"01000059\",\n      \"instruction\": \"MOV ECX,dword ptr [EAX]\"\n    },\n    {\n      \"address\": \"0100005b\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x24],ECX\"\n    },\n    {\n      \"address\": \"0100005f\",\n      \"instruction\": \"MOV EDX,dword ptr [EAX + 0x4]\"\n    },\n    {\n      \"address\": \"01000062\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x28],EDX\"\n    },\n    {\n      \"address\": \"01000066\",\n      \"instruction\": \"MOV EAX,dword ptr [EAX + 0x8]\"\n    },\n    {\n      \"address\": \"01000069\",\n      \"instruction\": \"PUSH 0x0\"\n    },\n    {\n      \"address\": \"0100006b\",\n      \"instruction\": \"MOV ECX,EDI\"\n    },\n    {\n      \"address\": \"0100006d\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x30],EAX\"\n    },\n    {\n      \"address\": \"01000071\",\n      \"instruction\": \"CALL 0x00c70fd0\"\n    },\n    {\n      \"address\": \"01000076\",\n      \"instruction\": \"MOV EDX,dword ptr [EBX]\"\n    },\n    {\n      \"address\": \"01000078\",\n      \"instruction\": \"MOV EDX,dword ptr [EDX + 0x64]\"\n    },\n    {\n      \"address\": \"0100007b\",\n      \"instruction\": \"MOV ESI,EAX\"\n    },\n    {\n      \"address\": \"0100007d\",\n      \"instruction\": \"LEA EAX,[ESP + 0x24]\"\n    },\n    {\n      \"address\": \"01000081\",\n      \"instruction\": \"PUSH EAX\"\n    },\n    {\n      \"address\": \"01000082\",\n      \"instruction\": \"PUSH 0x4\"\n    },\n    {\n      \"address\": \"01000084\",\n      \"instruction\": \"MOV ECX,EBX\"\n    },\n    {\n      \"address\": \"01000086\",\n      \"instruction\": \"CALL EDX\"\n    },\n    {\n      \"address\": \"01000088\",\n      \"instruction\": \"MOV EDX,dword ptr [EBX]\"\n    },\n    {\n      \"address\": \"0100008a\",\n      \"instruction\": \"MOV ECX,EBX\"\n    },\n    {\n      \"address\": \"0100008c\",\n      \"instruction\": \"CMP EAX,-0x1\"\n    },\n    {\n      \"address\": \"0100008f\",\n      \"instruction\": \"JZ 0x010000e9\"\n    },\n    {\n      \"address\": \"01000091\",\n      \"instruction\": \"PUSH EAX\"\n    },\n    {\n      \"address\": \"01000092\",\n      \"instruction\": \"MOV EAX,dword ptr [EDX + 0x60]\"\n    },\n    {\n      \"address\": \"01000095\",\n      \"instruction\": \"CALL EAX\"\n    },\n    {\n      \"address\": \"01000097\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x18],EAX\"\n    },\n    {\n      \"address\": \"0100009b\",\n      \"instruction\": \"CALL 0x0102f810\"\n    },\n    {\n      \"address\": \"010000a0\",\n      \"instruction\": \"MOV ECX,EAX\"\n    },\n    {\n      \"address\": \"010000a2\",\n      \"instruction\": \"CALL 0x0102ff00\"\n    },\n    {\n      \"address\": \"010000a7\",\n      \"instruction\": \"MOV ECX,dword ptr [ESP + 0x18]\"\n    },\n    {\n      \"address\": \"010000ab\",\n      \"instruction\": \"SUB EAX,dword ptr [ECX + 0x10]\"\n    },\n    {\n      \"address\": \"010000ae\",\n      \"instruction\": \"TEST EAX,EAX\"\n    },\n    {\n      \"address\": \"010000b0\",\n      \"instruction\": \"JG 0x010000e1\"\n    },\n    {\n      \"address\": \"010000b2\",\n      \"instruction\": \"TEST ESI,ESI\"\n    },\n    {\n      \"address\": \"010000b4\",\n      \"instruction\": \"JLE 0x010000e1\"\n    },\n    {\n      \"address\": \"010000b6\",\n      \"instruction\": \"PUSH 0x0\"\n    },\n    {\n      \"address\": \"010000b8\",\n      \"instruction\": \"PUSH 0x1\"\n    },\n    {\n      \"address\": \"010000ba\",\n      \"instruction\": \"PUSH 0x0\"\n    },\n    
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
  "body_end": "010003e3",
  "body_span_bytes": 996,
  "body_start": "01000000",
  "callees": [
    "FUN_00fffdd0",
    "FUN_01005180",
    "FUN_0103fc10",
    "FUN_00434040",
    "FUN_01021300",
    "FUN_01041c50",
    "FUN_00a1ad60",
    "FUN_00b8dad0",
    "FUN_00feba90",
    "FUN_0067ddd0",
    "FUN_00c70fd0",
    "FUN_0102ff00",
    "QuaternionToMatrix",
    "FUN_01002bd0",
    "FUN_007eb820",
    "FUN_0103a480",
    "FUN_0102adf0",
    "FUN_00feb9f0",
    "FUN_00b3d3d0",
    "FUN_00c71e30",
    "FUN_00dd8640",
    "FUN_00c71160",
    "FUN_00b3d3e0",
    "FUN_0102f810"
  ],
  "callers": [
    "FUN_01000520",
    "FUN_0102caa0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "01000000",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "puVar18",
      "storage": "Stack[-0xc0]:4",
      "type": "undefined1 *"
    },
    {
      "name": "uVar17",
      "storage": "Stack[-0xc0]:4",
      "type": "undefined4"
    },
    {
      "name": "local_78",
      "storage": "Stack[-0x78]:4",
      "type": "int"
    },
    {
      "name": "puVar20",
      "storage": "Stack[-0xbc]:4",
      "type": "undefined1 *"
    },
    {
      "name": "local_7c",
      "storage": "Stack[-0x7c]:4",
      "type": "int"
    },
    {
      "name": "uVar19",
      "storage": "Stack[-0xbc]:4",
      "type": "undefined4"
    },
    {
      "name": "uVar22",
      "storage": "Stack[-0xb4]:4",
      "type": "undefined4"
    },
    {
      "name": "uVar21",
      "storage": "Stack[-0xb8]:4",
      "type": "undefined4"
    },
    {
      "name": "unaff_EDI",
      "storage": "register:0000001c:4",
      "type": "int *"
    },
    {
      "name": "uVar10",
      "storage": "register:00000000:4",
      "type": "uint"
    },
    {
      "name": "iVar12",
      "storage": "register:0000001c:4",
      "type": "int"
    },
    {
      "name": "puVar11",
      "storage": "register:0000001c:4",
      "type": "undefined4 *"
    },
    {
      "name": "fVar14",
      "storage": "register:00001100:10",
      "type": "float10"
    },
    {
      "name": "iVar13",
      "storage": "register:0000001c:4",
      "type": "int"
    },
    {
      "name": "uVar16",
      "storage": "Stack[-0xc4]:4",
      "type": "undefined4"
    },
    {
      "name": "uVar15",
      "storage": "Stack[-0xc8]:4",
      "type": "undefined4"
    },
    {
      "name": "aiStack_74",
      "storage": "Stack[-0x74]:4",
      "type": "int[3]"
    },
    {
      "name": "sStack_66",
      "storage": "Stack[-0x66]:2",
      "type": "short"
    },
    {
      "name": "uStack_68",
      "storage": "Stack[-0x68]:2",
      "type": "ushort"
    },
    {
      "name": "uStack_60",
      "storage": "Stack[-0x60]:4",
      "type": "undefined4"
    },
    {
      "name": "uStack_64",
      "storage": "Stack[-0x64]:4",
      "type": "undefined4"
    },
    {
      "name": "iStack_94",
      "storage": "Stack[-0x94]:4",
      "type": "int"
    },
    {
      "name": "auStack_8c",
      "storage": "",
      "type": "undefined1[4]"
    },
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
      "name": "piVar5",
      "storage": "Stack[-0xb8]:4",
      "type": "int *"
    },
    {
      "name": "piVar4",
      "storage": "register:00000000:4",
      "type": "int *"
    },
    {
      "name": "puVar7",
      "storage": "register:00000018:4",
      "type": "undefined4 *"
    },
    {
      "name": "iVar6",
      "storage": "register:00000000:4",
      "type": "int"
    },
    {
      "name": "iVar9",
      "storage": "register:00000000:4",
      "type": "int"
    },
    {
      "name": "iVar8",
      "storage": "register:00000000:4",
      "type": "int"
    },
    {
      "name": "fStack_58",
      "storage": "Stack[-0x58]:4",
      "type": "float"
    },
    {
      "name": "uStack_5c",
      "storage": "Stack[-0x5c]:4",
      "type": "undefined4"
    },
    {
      "name": "auStack_30",
      "storage": "",
      "type": "undefined1[48]"
    },
    {
      "name": "auStack_54",
      "storage": "",
      "type": "undefined4[9]"
    },
    {
      "name": "local_80",
      "storage": "Stack[-0x80]:4",
      "type": "int"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int"
    },
    {
      "name": "local_88",
      "storage": "Stack[-0x88]:4",
      "type": "undefined4"
    },
    {
      "name": "cVar1",
      "storage": "register:00000000:1",
      "type": "char"
    },
    {
      "name": "param_2",
      "storage": "Stack[0x4]:4",
      "type": "int"
    }
  ],
  "locals_count": 40,
  "mode": "live",
  "name": "FUN_01000000",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xc00000",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_01000000(void)",
  "size_bytes": 996,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x01000000",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 61,
  "xrefs": [
    {
      "from": "0102caad"
    },
    {
      "from": "01000555"
    },
    {
      "from": "00db21d2"
    },
    {
      "from": "00c6b2db"
    },
    {
      "from": "00c6b32b"
    },
   
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
