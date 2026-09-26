# Evidence 0x01021740

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `c40ce63b3f4dbcb2158a55002fe34116e383255a1eb151ddadc1a643b74a2ca3`

## abi

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "abi": {
    "architecture": "x86-32",
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
      }
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +24, so the listing is not one path",
    "receiver_not_determinable: ecx_used_as_counter",
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
  "content_sha256": "112612877f4af5a5e30d8f05543032ed4e8c6f5d991a17dac0486b00b08e1b29",
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
    "indirect_calls": 9,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0087"
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
        "obs-0006"
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
        "obs-0013",
        "obs-0014",
        "obs-0019",
        "obs-0026",
        "obs-0032",
        "obs-0041",
        "obs-0043",
        "obs-0067",
        "obs-0070",
        "obs-0082"
      ],
      "claim": "the register receiver is undetermined: ecx_used_as_counter",
      "confidence": "UNKNOWN",
      "id": "R0",
      "value": {
        "reason": "ecx_used_as_counter",
        "register": null
      }
    },
    {
      "based_on": [
        "obs-0037"
      ],
      "claim": "the calling convention is not decidable from the listing",
      "confidence": "UNKNOWN",
      "id": "C12"
    },
    {
      "based_on": [
        "obs-0087"
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
        "obs-0002"
      ],
      "claim": "the return value is carried in ST0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "ST0"
    }
  ],
  "observations": [
    {
      "id": "obs-0001"
    },
    {
      "id": "obs-0002"
    },
    {
      "id": "obs-0003"
    },
    {
      "id": "obs-0004"
    },
    {
      "id": "obs-0005"
    },
    {
      "id": "obs-0006"
    },
    {
      "id": "obs-0007"
    },
    {
      "id": "obs-0008"
    },
    {
      "id": "obs-0009"
    },
    {
      "id": "obs-0010"
    },
    {
      "id": "obs-0011"
    },
    {
      "id": "obs-0012"
    },
    {
      "id": "obs-0013"
    },
    {
      "id": "obs-0014"
    },
    {
      "id": "obs-0015"
    },
    {
      "id": "obs-0016"
    },
    {
      "id": "obs-0017"
    },
    {
      "id": "obs-0018"
    },
    {
      "id": "obs-0019"
    },
    {
      "id": "obs-0020"
    },
    {
      "id": "obs-0021"
    },
    {
      "id": "obs-0022"
    },
    {
      "id": "obs-0023"
    },
    {
      "id": "obs-0024"
    },
    {
      "id": "obs-0025"
    },
    {
      "id": "obs-0026"
    },
    {
      "id": "obs-0027"
    },
    {
      "id": "obs-0028"
    },
    {
      "id": "obs-0029"
    },
    {
      "id": "obs-0030"
    },
    {
      "id": "obs-0031"
    },
    {
      "id": "obs-0032"
    },
    {
      "id": "obs-0033"
    },
    {
      "id": "obs-0034"
    },
    {
      "id": "obs-0035"
    },
    {
      "id": "obs-0036"
    },
    {
      "id": "obs-0037"
    },
    {
      "id": "obs-0038"
    },
    {
      "id": "obs-0039"
    },
    {
      "id": "obs-0040"
    },
    {
      "id": "obs-0041"
    },
    {
      "id": "obs-0042"
    },
    {
      "id": "obs-0043"
    },
    {
      "id": "obs-0044"
    },
    {
      "id": "obs-0045"
    },
    {
      "id": "obs-0046"
    },
    {
      "id": "obs-0047"
    },
    {
      "id": "obs-0048"
    },
    {
      "id": "obs-0049"
    },
    {
      "id": "obs-0050"
    },
    {
      "id": "obs-0051"
    },
    {
      "id": "obs-0052"
    },
    {
      "id": "obs-0053"
    },
    {
      "id": "obs-0054"
    },
    {
      "id": "obs-0055"
    },
    {
      "id": "obs-0056"
    },
    {
      "id": "obs-0057"
    },
    {
      "id": "obs-0058"
    },
    {
    
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
"\n/* WARNING: Enum \"Names\": Some values do not have unique names */\n/* WARNING: Enum \"ObjectTYPE\": Some values do not have unique names */\n\nvoid FUN_01021740(int *param_1)\n\n{\n  float *pfVar1;\n  undefined4 uVar2;\n  undefined4 *puVar3;\n  cLocaleManager *pcVar4;\n  cGameInputManager *pcVar5;\n  undefined4 uVar6;\n  IShadowWorld *pIVar7;\n  int *piVar8;\n  int iVar9;\n  int unaff_EBX;\n  ILayer *unaff_ESI;\n  IShadowWorld *unaff_EDI;\n  undefined4 *puVar10;\n  cLocaleManager local_b0;\n  float local_a8;\n  float local_a4;\n  undefined4 local_a0;\n  undefined4 local_9c [9];\n  float fStack_78;\n  float fStack_74;\n  float fStack_70;\n  undefined1 auStack_6c [16];\n  ushort uStack_5c;\n  short sStack_5a;\n  undefined1 auStack_54 [12];\n  undefined4 auStack_48 [9];\n  undefined1 auStack_24 [36];\n  \n  if ((param_1 == *(int **)(Simulator__sSpacePlayerData + 4)) &&\n     (*(int *)(Simulator__sSpacePlayerData + 0x10) == 0)) {\n    local_b0.mnRefCount = DAT_016dda90;\n    local_a8 = (float)DAT_016dda94;\n    local_b0._vftable0._2_2_ = 0;\n    local_a4 = (float)DAT_016dda98;\n    local_b0._vftable0._0_2_ = 0;\n    local_a0 = 0x3f800000;\n    FUN_0041cb40(&DAT_016ddb10);\n    pfVar1 = (float *)(**(code **)(*param_1 + 0x2c))();\n    local_b0.mnRefCount = (int)*pfVar1;\n    local_a8 = pfVar1[1];\n    local_a4 = pfVar1[2];\n    local_b0._vftable0._0_2_ = (ushort)local_b0._vftable0 | 4;\n    local_b0._vftable0._2_2_ = local_b0._vftable0._2_2_ + 1;\n    uVar2 = (**(code **)(*param_1 + 0x30))();\n    puVar3 = (undefined4 *)QuaternionToMatrix(auStack_24,uVar2);\n    puVar10 = local_9c;\n    for (iVar9 = 9; iVar9 != 0; iVar9 = iVar9 + -1) {\n      *puVar10 = *puVar3;\n      puVar3 = puVar3 + 1;\n      puVar10 = puVar10 + 1;\n    }\n    local_b0._vftable0._0_2_ = (ushort)local_b0._vftable0 | 2;\n    local_b0._vftable0._2_2_ = local_b0._vftable0._2_2_ + 1;\n    pcVar4 = App__cLocaleManager__Get();\n    (*pcVar4->_vftable0[5].GetActiveLanguage)(&local_b0);\n    FUN_0040efa0();\n    fStack_70 = 1.0 / SQRT((float)local_b0.mnRefCount * (float)local_b0.mnRefCount +\n                           local_a8 * local_a8 + local_a4 * local_a4 + 1e-08);\n    fStack_78 = (float)local_b0.mnRefCount * fStack_70;\n    fStack_74 = local_a8 * fStack_70;\n    fStack_70 = local_a4 * fStack_70;\n    pcVar5 = Simulator__cGameInputManager__Get();\n    piVar8 = (int *)pcVar5->field_18;\n    if (piVar8 != (int *)0x0) {\n      uVar2 = (**(code **)(*param_1 + 0x30))();\n      uVar6 = (**(code **)(*param_1 + 0x2c))(uVar2);\n      (**(code **)(*piVar8 + 0x10))(uVar6);\n      FUN_00fbad70(uVar6,uVar2);\n      FUN_00409930();\n      FUN_00698180(auStack_6c,&DAT_015b7080,&fStack_78);\n      puVar3 = (undefined4 *)QuaternionToMatrix(auStack_24,auStack_6c);\n      puVar10 = auStack_48;\n      for (iVar9 = 9; iVar9 != 0; iVar9 = iVar9 + -1) {\n        *puVar10 = *puVar3;\n        puVar3 = puVar3 + 1;\n        puVar10 = puVar10 + 1;\n      }\n      uStack_5c = uStack_5c | 2;\n      sStack_5a = sStack_5a + 1;\n      pIVar7 = Graphics__IShadowWorld__Get();\n      if (((pIVar7 != (IShadowWorld *)0x0) &&\n          (piVar8 = (int *)(*pIVar7->_vftable0->AddLayer)(unaff_EDI,unaff_ESI,unaff_EBX),\n          piVar8 != (int *)0x0)) &&\n         (piVar8 = (int *)(**(code **)(*piVar8 + 0x144))(0), piVar8 != (int *)0x0)) {\n        (**(code **)(*piVar8 + 0x28))(auStack_54);\n      }\n    }\n  }\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "original_bytes": 12747,
  "preview": "{\n  \"count\": 151,\n  \"instructions\": [\n    {\n      \"address\": \"01021740\",\n      \"instruction\": \"MOV EAX,[0x016dda8c]\"\n    },\n    {\n      \"address\": \"01021745\",\n      \"instruction\": \"SUB ESP,0xb4\"\n    },\n    {\n      \"address\": \"0102174b\",\n      \"instruction\": \"PUSH EBX\"\n    },\n    {\n      \"address\": \"0102174c\",\n      \"instruction\": \"MOV EBX,dword ptr [ESP + 0xbc]\"\n    },\n    {\n      \"address\": \"01021753\",\n      \"instruction\": \"CMP EBX,dword ptr [EAX + 0x4]\"\n    },\n    {\n      \"address\": \"01021756\",\n      \"instruction\": \"JNZ 0x0102194a\"\n    },\n    {\n      \"address\": \"0102175c\",\n      \"instruction\": \"CMP dword ptr [EAX + 0x10],0x0\"\n    },\n    {\n      \"address\": \"01021760\",\n      \"instruction\": \"JNZ 0x0102194a\"\n    },\n    {\n      \"address\": \"01021766\",\n      \"instruction\": \"MOVSS XMM0,dword ptr [0x016dda90]\"\n    },\n    {\n      \"address\": \"0102176e\",\n      \"instruction\": \"MOVSS dword ptr [ESP + 0xc],XMM0\"\n    },\n    {\n      \"address\": \"01021774\",\n      \"instruction\": \"MOVSS XMM0,dword ptr [0x016dda94]\"\n    },\n    {\n      \"address\": \"0102177c\",\n      \"instruction\": \"PUSH ESI\"\n    },\n    {\n      \"address\": \"0102177d\",\n      \"instruction\": \"XOR ECX,ECX\"\n    },\n    {\n      \"address\": \"0102177f\",\n      \"instruction\": \"MOVSS dword ptr [ESP + 0x14],XMM0\"\n    },\n    {\n      \"address\": \"01021785\",\n      \"instruction\": \"MOVSS XMM0,dword ptr [0x016dda98]\"\n    },\n    {\n      \"address\": \"0102178d\",\n      \"instruction\": \"PUSH EDI\"\n    },\n    {\n      \"address\": \"0102178e\",\n      \"instruction\": \"XOR EAX,EAX\"\n    },\n    {\n      \"address\": \"01021790\",\n      \"instruction\": \"MOV word ptr [ESP + 0x12],CX\"\n    },\n    {\n      \"address\": \"01021795\",\n      \"instruction\": \"MOVSS dword ptr [ESP + 0x1c],XMM0\"\n    },\n    {\n      \"address\": \"0102179b\",\n      \"instruction\": \"MOVSS XMM0,dword ptr [0x01485720]\"\n    },\n    {\n      \"address\": \"010217a3\",\n      \"instruction\": \"PUSH 0x16ddb10\"\n    },\n    {\n      \"address\": \"010217a8\",\n      \"instruction\": \"LEA ECX,[ESP + 0x28]\"\n    },\n    {\n      \"address\": \"010217ac\",\n      \"instruction\": \"MOV word ptr [ESP + 0x14],AX\"\n    },\n    {\n      \"address\": \"010217b1\",\n      \"instruction\": \"MOVSS dword ptr [ESP + 0x24],XMM0\"\n    },\n    {\n      \"address\": \"010217b7\",\n      \"instruction\": \"CALL 0x0041cb40\"\n    },\n    {\n      \"address\": \"010217bc\",\n      \"instruction\": \"MOV EDX,dword ptr [EBX]\"\n    },\n    {\n      \"address\": \"010217be\",\n      \"instruction\": \"MOV EAX,dword ptr [EDX + 0x2c]\"\n    },\n    {\n      \"address\": \"010217c1\",\n      \"instruction\": \"MOV ECX,EBX\"\n    },\n    {\n      \"address\": \"010217c3\",\n      \"instruction\": \"CALL EAX\"\n    },\n    {\n      \"address\": \"010217c5\",\n      \"instruction\": \"MOV ECX,dword ptr [EAX]\"\n    },\n    {\n      \"address\": \"010217c7\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x14],ECX\"\n    },\n    {\n      \"address\": \"010217cb\",\n      \"instruction\": \"MOV EDX,dword ptr [EAX + 0x4]\"\n    },\n    {\n      \"address\": \"010217ce\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x18],EDX\"\n    },\n    {\n      \"address\": \"010217d2\",\n      \"instruction\": \"MOV EAX,dword ptr [EAX + 0x8]\"\n    },\n    {\n      \"address\": \"010217d5\",\n      \"instruction\": \"MOV EDX,dword ptr [EBX]\"\n    },\n    {\n      \"address\": \"010217d7\",\n      \"instruction\": \"OR word ptr [ESP + 0x10],0x4\"\n    },\n    {\n      \"address\": \"010217dd\",\n      \"instruction\": \"INC word ptr [ESP + 0x12]\"\n    },\n    {\n      \"address\": \"010217e2\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x1c],EAX\"\n    },\n    {\n      \"address\": \"010217e6\",\n      \"instruction\": \"MOV EAX,dword ptr [EDX + 0x30]\"\n    },\n    {\n      \"address\": \"010217e9\",\n      \"instruction\": \"MOV ECX,EBX\"\n    },\n    {\n      \"address\": \"010217eb\",\n      \"instruction\": \"CALL EAX\"\n    },\n    {\n      \"address\": \"010217ed\",\n      \"instruction\": \"PUSH EAX\"\n    },\n    {\n      \"address\": \"010217ee\",\n      \"instruction\": \"LEA ECX,[ESP + 0xa0]\"\n    },\n    {\n      \"address\": \"010217f5\",\n      \"instruction\": \"PUSH ECX\"\n    },\n    {\n      \"address\": \"010217f6\",\n      \"instruction\": \"CALL 0x0059c190\"\n    },\n    {\n      \"address\": \"010217fb\",\n      \"instruction\": \"MOV ESI,EAX\"\n    },\n    {\n      \"address\": \"010217fd\",\n      \"instruction\": \"MOV ECX,0x9\"\n    },\n    {\n      \"address\": \"01021802\",\n      \"instruction\": \"LEA EDI,[ESP + 0x2c]\"\n    },\n    {\n      \"address\": \"01021806\",\n      \"instruction\": \"MOVSD.REP ES:EDI,ESI\"\n    },\n    {\n      \"address\": \"01021808\",\n      \"instruction\": \"OR word ptr [ESP + 0x18],0x2\"\n    },\n    {\n      \"address\": \"0102180e\",\n      \"instruction\": \"INC word ptr [ESP + 0x1a]\"\n    },\n    {\n      \"address\": \"01021813\",\n      \"instruction\": \"ADD ESP,0x8\"\n    },\n    {\n      \"address\": \"01021816\",\n      \"instruction\": \"CALL 0x0067de00\"\n    },\n    {\n      \"address\": \"0102181b\",\n      \"instruction\": \"MOV EDX,dword ptr [EAX]\"\n    },\n    {\n      \"address\": \"0102181d\",\n      \"instruction\": \"MOV EDX,dword ptr [EDX + 0xdc]\"\n    },\n    {\n      \"address\": \"01021823\",\n      \"instruction\": \"LEA ECX,[ESP + 0x10]\"\n    },\n    {\n      \"address\": \"01021827\",\n      \"instruction\": \"PUSH ECX\"\n    },\n    {\n      \"address\": \"01021828\",\n      \"instruction\": \"MOV ECX,EAX\"\n    },\n    {\n      \"address\": \"0102182a\",\n      \"instruction\": \"CALL EDX\"\n    },\n    {\n      \"address\": \"0102182c\",\n      \"instruction\": \"LEA ECX,[ESP + 0x10]\
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
  "body_end": "01021951",
  "body_span_bytes": 530,
  "body_start": "01021740",
  "callees": [
    "FUN_00fbad70",
    "FUN_0041cb40",
    "Simulator::cGameInputManager::Get",
    "QuaternionToMatrix",
    "Graphics::IShadowWorld::Get",
    "FUN_00409930",
    "FUN_0040efa0",
    "App::cLocaleManager::Get",
    "FUN_00698180"
  ],
  "callers": [
    "FUN_00bc2c50",
    "FUN_00c84d60",
    "FUN_00fdf5f0",
    "FUN_01003690"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "01021740",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_a8",
      "storage": "Stack[-0xa8]:4",
      "type": "float"
    },
    {
      "name": "fStack_78",
      "storage": "Stack[-0x78]:4",
      "type": "float"
    },
    {
      "name": "local_b0",
      "storage": "Stack[-0xac]:4",
      "type": "cLocaleManager"
    },
    {
      "name": "local_9c",
      "storage": "",
      "type": "undefined4[9]"
    },
    {
      "name": "local_a0",
      "storage": "Stack[-0xa0]:4",
      "type": "undefined4"
    },
    {
      "name": "local_a4",
      "storage": "Stack[-0xa4]:4",
      "type": "float"
    },
    {
      "name": "param_1",
      "storage": "Stack[0x4]:4",
      "type": "int *"
    },
    {
      "name": "uVar2",
      "storage": "register:00000000:4",
      "type": "undefined4"
    },
    {
      "name": "pfVar1",
      "storage": "register:00000000:4",
      "type": "float *"
    },
    {
      "name": "pcVar4",
      "storage": "register:00000000:4",
      "type": "cLocaleManager *"
    },
    {
      "name": "puVar3",
      "storage": "register:00000018:4",
      "type": "undefined4 *"
    },
    {
      "name": "uVar6",
      "storage": "register:00000000:4",
      "type": "undefined4"
    },
    {
      "name": "pcVar5",
      "storage": "register:00000000:4",
      "type": "cGameInputManager *"
    },
    {
      "name": "fStack_70",
      "storage": "Stack[-0x70]:4",
      "type": "float"
    },
    {
      "name": "fStack_74",
      "storage": "Stack[-0x74]:4",
      "type": "float"
    },
    {
      "name": "uStack_5c",
      "storage": "Stack[-0x5c]:2",
      "type": "ushort"
    },
    {
      "name": "auStack_6c",
      "storage": "",
      "type": "undefined1[16]"
    },
    {
      "name": "auStack_54",
      "storage": "",
      "type": "undefined1[12]"
    },
    {
      "name": "sStack_5a",
      "storage": "Stack[-0x5a]:2",
      "type": "short"
    },
    {
      "name": "auStack_24",
      "storage": "",
      "type": "undefined1[36]"
    },
    {
      "name": "auStack_48",
      "storage": "",
      "type": "undefined4[9]"
    },
    {
      "name": "piVar8",
      "storage": "register:00000000:4",
      "type": "int *"
    },
    {
      "name": "pIVar7",
      "storage": "register:00000000:4",
      "type": "IShadowWorld *"
    },
    {
      "name": "unaff_EBX",
      "storage": "register:0000000c:4",
      "type": "int"
    },
    {
      "name": "iVar9",
      "storage": "register:00000004:4",
      "type": "int"
    },
    {
      "name": "unaff_EDI",
      "storage": "register:0000001c:4",
      "type": "IShadowWorld *"
    },
    {
      "name": "unaff_ESI",
      "storage": "register:00000018:4",
      "type": "ILayer *"
    },
    {
      "name": "puVar10",
      "storage": "register:0000001c:4",
      "type": "undefined4 *"
    }
  ],
  "locals_count": 28,
  "mode": "live",
  "name": "FUN_01021740",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xc21740",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_01021740(void)",
  "size_bytes": 530,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x01021740",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 4,
  "xrefs": [
    {
      "from": "00bc2e8e"
    },
    {
      "from": "00c850e3"
    },
    {
      "from": "01003824"
    },
    {
      "from": "00fdf89a"
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
