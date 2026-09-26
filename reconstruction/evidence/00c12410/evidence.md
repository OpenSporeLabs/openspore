# Evidence 0x00c12410

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `ac2012ffbbac2a335a52babefc2de021faf4a347252bf6b61dcd6470e588bd3f`

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
      "entry_ESP+0x10",
      "entry_ESP+0x14",
      "entry_ESP+0x18",
      "entry_ESP+0x1c",
      "entry_ESP+0x20",
      "entry_ESP+0x28",
      "entry_ESP+0x2c",
      "entry_ESP+0x30",
      "entry_ESP+0x34",
      "entry_ESP+0x3c",
      "entry_ESP+0x40"
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
        "confidence": "UNKNOWN",
        "entry_offset": "entry_ESP+0x10",
        "observed": true,
        "ordinal": 4,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1,
          4
        ],
        "written": false
      },
      {
        "confidence": "UNKNOWN",
        "entry_offset": "entry_ESP+0x14",
        "observed": true,
        "ordinal": 5,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1,
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x18",
        "observed": true,
        "ordinal": 6,
        "read": false,
        "size_inferred": true,
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
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x20",
        "observed": true,
        "ordinal": 8,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x28",
        "observed": true,
        "ordinal": 10,
        "read": false,
        "size_inferred": false,
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
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x30",
        "observed": true,
        "ordinal": 12,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "confidence": "UNKNOWN",
        "entry_offset": "entry_ESP+0x34",
        "observed": true,
        "ordinal": 13,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1,
          4
        ],
        "written": false
      },
      {
        "confidence": "UNKNOWN",
        "entry_offset": "entry_ESP+0x3c",
        "observed": true,
        "ordinal": 15,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1,
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x40",
        "observed": true,
        "ordinal": 16,
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
    "ret_form": "RET 0x1c",
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
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "confidence": "UNKNOWN",
        "entry_offset": "entry_ESP+0x10",
        "observed": true,
        "ordinal": 4,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1,
          4
        ],
        "written": false
      },
      {
        "confidence": "UNKNOWN",
        "entry_offset": "entry_ESP+0x14",
        "observed": true,
        "ordinal": 5,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1,
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x18",
        "observed": true,
        "ordinal": 6,
        "read": false,
        "size_inferred": true,
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
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x20",
        "observed": true,
        "ordinal": 8,
        "read": false,
        "s
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
"\n/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */\n\nuint __thiscall\nFUN_00c12410(int *param_1,int param_2,float param_3,char param_4,char param_5,char param_6,\n            char param_7,char param_8)\n\n{\n  float fVar1;\n  float fVar2;\n  int iVar3;\n  uint uVar4;\n  int iVar5;\n  float *pfVar6;\n  uint uVar7;\n  float10 fVar8;\n  float10 fVar9;\n  int iStack_24;\n  float fStack_1c;\n  uint uStack_18;\n  uint uStack_14;\n  float fStack_c;\n  float fStack_8;\n  uint uStack_4;\n  \n  if ((param_5 == '\\0') && (param_1[0x3a3] != -1)) {\n    return 0xffffffff;\n  }\n  uVar7 = 0;\n  fVar8 = (float10)FUN_00d38a30(0,param_1);\n  uStack_4 = (**(code **)(*param_1 + 0xb0))();\n  _param_5 = -1.0;\n  uStack_18 = 0xffffffff;\n  fStack_1c = 3.4028235e+38;\n  if (uStack_4 != 0) {\n    iStack_24 = 0;\n    do {\n      iVar3 = param_1[0x30a];\n      iVar5 = (**(code **)(*param_1 + 0xb4))(uVar7);\n      if ((((param_2 == 0) ||\n           ((uVar4 = *(uint *)(iVar5 + 8), uVar4 < 0x58 &&\n            ((*(uint *)(param_2 + (uVar4 >> 5) * 4) & 1 << ((byte)uVar4 & 0x1f)) != 0)))) &&\n          (*(int *)(iVar5 + 0xc) == 1)) &&\n         ((((*(char *)(iVar5 + 0x114) == '\\0' &&\n            ((*(float *)(iVar5 + 0x104) <= 0.0 ||\n             (*(float *)(iVar5 + 0x104) <= (float)param_1[0x396])))) &&\n           ((param_4 != '\\0' || (1.0 <= *(float *)(iVar3 + iStack_24 + 4))))) &&\n          ((param_7 != '\\0' ||\n           (param_3 <= (*(float *)(iVar5 + 0xf4) + *(float *)(iVar5 + 0xa8)) * (float)fVar8)))))) {\n        if (param_6 == '\\0') {\n          fVar1 = _DAT_01582efc + param_3;\n          uStack_14 = CONCAT31(uStack_14._1_3_,(char)((uint)param_1[0x2d6] >> 9)) & 0xffffff01;\n          fVar9 = (float10)FUN_004d3d70(uStack_14);\n          if ((float10)fVar1 < fVar9) goto LAB_00c12613;\n        }\n        fVar1 = *(float *)(iVar5 + 0x3c);\n        if ((0.0 < fVar1) || (*(int *)(iVar5 + 8) == 0x20)) {\n          fStack_8 = param_3 - (*(float *)(iVar5 + 0xf4) + *(float *)(iVar5 + 0xa8)) * (float)fVar8;\n          fStack_c = 0.0;\n          pfVar6 = &fStack_c;\n          if (0.0 <= fStack_8) {\n            pfVar6 = &fStack_8;\n          }\n          fVar2 = *pfVar6;\n          if (param_8 == '\\0') {\nLAB_00c125fc:\n            if (fVar1 <= _param_5) goto LAB_00c12613;\n          }\n          else if (fStack_1c <= fVar2) {\n            if (1.5258789e-05 <= fVar2 - fStack_1c) goto LAB_00c12613;\n            goto LAB_00c125fc;\n          }\n          _param_5 = fVar1;\n          fStack_1c = fVar2;\n          uStack_18 = uVar7;\n        }\n      }\nLAB_00c12613:\n      iStack_24 = iStack_24 + 0x10;\n      uVar7 = uVar7 + 1;\n    } while (uVar7 < uStack_4);\n  }\n  return uStack_18;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "original_bytes": 12215,
  "preview": "{\n  \"count\": 142,\n  \"instructions\": [\n    {\n      \"address\": \"00c12410\",\n      \"instruction\": \"SUB ESP,0x24\"\n    },\n    {\n      \"address\": \"00c12413\",\n      \"instruction\": \"PUSH ESI\"\n    },\n    {\n      \"address\": \"00c12414\",\n      \"instruction\": \"OR ESI,0xffffffff\"\n    },\n    {\n      \"address\": \"00c12417\",\n      \"instruction\": \"CMP byte ptr [ESP + 0x38],0x0\"\n    },\n    {\n      \"address\": \"00c1241c\",\n      \"instruction\": \"PUSH EDI\"\n    },\n    {\n      \"address\": \"00c1241d\",\n      \"instruction\": \"MOV EDI,ECX\"\n    },\n    {\n      \"address\": \"00c1241f\",\n      \"instruction\": \"JNZ 0x00c12433\"\n    },\n    {\n      \"address\": \"00c12421\",\n      \"instruction\": \"CMP dword ptr [EDI + 0xe8c],ESI\"\n    },\n    {\n      \"address\": \"00c12427\",\n      \"instruction\": \"JZ 0x00c12433\"\n    },\n    {\n      \"address\": \"00c12429\",\n      \"instruction\": \"POP EDI\"\n    },\n    {\n      \"address\": \"00c1242a\",\n      \"instruction\": \"MOV EAX,ESI\"\n    },\n    {\n      \"address\": \"00c1242c\",\n      \"instruction\": \"POP ESI\"\n    },\n    {\n      \"address\": \"00c1242d\",\n      \"instruction\": \"ADD ESP,0x24\"\n    },\n    {\n      \"address\": \"00c12430\",\n      \"instruction\": \"RET 0x1c\"\n    },\n    {\n      \"address\": \"00c12433\",\n      \"instruction\": \"PUSH EBX\"\n    },\n    {\n      \"address\": \"00c12434\",\n      \"instruction\": \"PUSH EDI\"\n    },\n    {\n      \"address\": \"00c12435\",\n      \"instruction\": \"XOR EBX,EBX\"\n    },\n    {\n      \"address\": \"00c12437\",\n      \"instruction\": \"PUSH EBX\"\n    },\n    {\n      \"address\": \"00c12438\",\n      \"instruction\": \"CALL 0x00d38a30\"\n    },\n    {\n      \"address\": \"00c1243d\",\n      \"instruction\": \"FSTP float ptr [ESP + 0x18]\"\n    },\n    {\n      \"address\": \"00c12441\",\n      \"instruction\": \"MOV EAX,dword ptr [EDI]\"\n    },\n    {\n      \"address\": \"00c12443\",\n      \"instruction\": \"MOV EDX,dword ptr [EAX + 0xb0]\"\n    },\n    {\n      \"address\": \"00c12449\",\n      \"instruction\": \"ADD ESP,0x8\"\n    },\n    {\n      \"address\": \"00c1244c\",\n      \"instruction\": \"MOV ECX,EDI\"\n    },\n    {\n      \"address\": \"00c1244e\",\n      \"instruction\": \"CALL EDX\"\n    },\n    {\n      \"address\": \"00c12450\",\n      \"instruction\": \"MOVSS XMM0,dword ptr [0x013eb1bc]\"\n    },\n    {\n      \"address\": \"00c12458\",\n      \"instruction\": \"MOVSS dword ptr [ESP + 0x40],XMM0\"\n    },\n    {\n      \"address\": \"00c1245e\",\n      \"instruction\": \"MOVSS XMM0,dword ptr [0x0146a32c]\"\n    },\n    {\n      \"address\": \"00c12466\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x2c],EAX\"\n    },\n    {\n      \"address\": \"00c1246a\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x18],ESI\"\n    },\n    {\n      \"address\": \"00c1246e\",\n      \"instruction\": \"MOVSS dword ptr [ESP + 0x14],XMM0\"\n    },\n    {\n      \"address\": \"00c12474\",\n      \"instruction\": \"CMP EAX,EBX\"\n    },\n    {\n      \"address\": \"00c12476\",\n      \"instruction\": \"JBE 0x00c12624\"\n    },\n    {\n      \"address\": \"00c1247c\",\n      \"instruction\": \"MOV dword ptr [ESP + 0xc],EBX\"\n    },\n    {\n      \"address\": \"00c12480\",\n      \"instruction\": \"PUSH EBP\"\n    },\n    {\n      \"address\": \"00c12481\",\n      \"instruction\": \"MOV EAX,dword ptr [EDI]\"\n    },\n    {\n      \"address\": \"00c12483\",\n      \"instruction\": \"MOV EBP,dword ptr [EDI + 0xc28]\"\n    },\n    {\n      \"address\": \"00c12489\",\n      \"instruction\": \"MOV EDX,dword ptr [EAX + 0xb4]\"\n    },\n    {\n      \"address\": \"00c1248f\",\n      \"instruction\": \"ADD EBP,dword ptr [ESP + 0x10]\"\n    },\n    {\n      \"address\": \"00c12493\",\n      \"instruction\": \"PUSH EBX\"\n    },\n    {\n      \"address\": \"00c12494\",\n      \"instruction\": \"MOV ECX,EDI\"\n    },\n    {\n      \"address\": \"00c12496\",\n      \"instruction\": \"CALL EDX\"\n    },\n    {\n      \"address\": \"00c12498\",\n      \"instruction\": \"CMP dword ptr [ESP + 0x38],0x0\"\n    },\n    {\n      \"address\": \"00c1249d\",\n      \"instruction\": \"MOV ESI,EAX\"\n    },\n    {\n      \"address\": \"00c1249f\",\n      \"instruction\": \"JZ 0x00c124ce\"\n    },\n    {\n      \"address\": \"00c124a1\",\n      \"instruction\": \"MOV EAX,dword ptr [ESI + 0x8]\"\n    },\n    {\n      \"address\": \"00c124a4\",\n      \"instruction\": \"CMP EAX,0x58\"\n    },\n    {\n      \"address\": \"00c124a7\",\n      \"instruction\": \"JNC 0x00c12613\"\n    },\n    {\n      \"address\": \"00c124ad\",\n      \"instruction\": \"MOV ECX,EAX\"\n    },\n    {\n      \"address\": \"00c124af\",\n      \"instruction\": \"AND ECX,0x1f\"\n    },\n    {\n      \"address\": \"00c124b2\",\n      \"instruction\": \"MOV EDX,0x1\"\n    },\n    {\n      \"address\": \"00c124b7\",\n      \"instruction\": \"SHL EDX,CL\"\n    },\n    {\n      \"address\": \"00c124b9\",\n      \"instruction\": \"MOV ECX,dword ptr [ESP + 0x38]\"\n    },\n    {\n      \"address\": \"00c124bd\",\n      \"instruction\": \"SHR EAX,0x5\"\n    },\n    {\n      \"address\": \"00c124c0\",\n      \"instruction\": \"TEST dword ptr [ECX + EAX*0x4],EDX\"\n    },\n    {\n      \"address\": \"00c124c3\",\n      \"instruction\": \"SETNZ AL\"\n    },\n    {\n      \"address\": \"00c124c6\",\n      \"instruction\": \"TEST AL,AL\"\n    },\n    {\n      \"address\": \"00c124c8\",\n      \"instruction\": \"JZ 0x00c12613\"\n    },\n    {\n      \"address\": \"00c124ce\",\n      \"instruction\": \"CMP dword ptr [ESI + 0xc],0x1\"\n    },\n    {\n      \"address\": \"00c124d2\",\n      \"instruction\": \"JNZ 0x00c12613\"\n    },\n    {\n      \"address\": \"00c124d8\",\n      \"instruction\": \"CMP byte ptr [ESI + 0x114],0x0\"\n    },\n    {\n      \"address\": \"00c124df\",\n      \"instruction\": \"JNZ 0x00c1261
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
  "body_end": "00c12630",
  "body_span_bytes": 545,
  "body_start": "00c12410",
  "callees": [
    "FUN_00d38a30",
    "FUN_004d3d70"
  ],
  "callers": [
    "FUN_00d669c0",
    "FUN_00d71780",
    "FUN_00d697a0",
    "FUN_00d8cde0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00c12410",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "fVar9",
      "storage": "register:00001100:10",
      "type": "float10"
    },
    {
      "name": "fVar8",
      "storage": "register:00001100:10",
      "type": "float10"
    },
    {
      "name": "uVar7",
      "storage": "register:0000000c:4",
      "type": "uint"
    },
    {
      "name": "pfVar6",
      "storage": "register:00000000:4",
      "type": "float *"
    },
    {
      "name": "iVar5",
      "storage": "register:00000000:4",
      "type": "int"
    },
    {
      "name": "uVar4",
      "storage": "unique:00017200:4",
      "type": "uint"
    },
    {
      "name": "iVar3",
      "storage": "unique:00017200:4",
      "type": "int"
    },
    {
      "name": "fVar2",
      "storage": "unique:0000a300:4",
      "type": "float"
    },
    {
      "name": "fVar1",
      "storage": "unique:0000a300:4",
      "type": "float"
    },
    {
      "name": "param_8",
      "storage": "Stack[0x1c]:1",
      "type": "char"
    },
    {
      "name": "param_7",
      "storage": "Stack[0x18]:1",
      "type": "char"
    },
    {
      "name": "param_6",
      "storage": "Stack[0x14]:1",
      "type": "char"
    },
    {
      "name": "param_5",
      "storage": "Stack[0x10]:4",
      "type": "char"
    },
    {
      "name": "param_4",
      "storage": "Stack[0xc]:1",
      "type": "char"
    },
    {
      "name": "param_3",
      "storage": "Stack[0x8]:4",
      "type": "float"
    },
    {
      "name": "param_2",
      "storage": "Stack[0x4]:4",
      "type": "int"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int *"
    },
    {
      "name": "uStack_4",
      "storage": "Stack[-0x4]:4",
      "type": "uint"
    },
    {
      "name": "fStack_8",
      "storage": "Stack[-0x8]:4",
      "type": "float"
    },
    {
      "name": "fStack_c",
      "storage": "Stack[-0xc]:4",
      "type": "float"
    },
    {
      "name": "uStack_14",
      "storage": "Stack[-0x14]:4",
      "type": "uint"
    },
    {
      "name": "uStack_18",
      "storage": "Stack[-0x18]:4",
      "type": "uint"
    },
    {
      "name": "fStack_1c",
      "storage": "Stack[-0x1c]:4",
      "type": "float"
    },
    {
      "name": "iStack_24",
      "storage": "Stack[-0x24]:4",
      "type": "int"
    }
  ],
  "locals_count": 24,
  "mode": "live",
  "name": "FUN_00c12410",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x812410",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00c12410(void)",
  "size_bytes": 545,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00c12410",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 6,
  "xrefs": [
    {
      "from": "00d66ab1"
    },
    {
      "from": "00d69efa"
    },
    {
      "from": "00d69f58"
    },
    {
      "from": "00d69f7d"
    },
    {
      "from": "00d8cf05"
    },
    {
      "from": "00d71bbe"
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
