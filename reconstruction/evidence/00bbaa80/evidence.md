# Evidence 0x00bbaa80

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `d25d1d6102bf54fc10bd6e48b0ef0d31c286b5ac169ae60a2388ac6ad301d797`

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
      "entry_ESP+0x4f",
      "entry_ESP+0x68"
    ],
    "ordinary_stack_argument_slots_bounded": {
      "kept": 2,
      "omitted": 19
    },
    "ordinary_stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x4f",
        "observed": true,
        "ordinal": 19,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x68",
        "observed": true,
        "ordinal": 26,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "ordinary_stack_arguments_bounded": {
      "kept": 2,
      "omitted": 19
    },
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x4",
    "return_register": "EAX",
    "return_semantics": "pointer_like_in_EAX",
    "saved_registers": [
      "EBP",
      "EBX",
      "EDI",
      "ESI"
    ],
    "stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x4f",
        "observed": true,
        "ordinal": 19,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x68",
        "observed": true,
        "ordinal": 26,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "stack_arguments_bounded": {
      "kept": 2,
      "omitted": 19
    },
    "termination": "RET 0x4"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -184, so the listing is not one path",
    "ret_imm_below_highest_slot: ret 0x4 pops less than the highest read slot 0xc8; everything above it belongs to the caller's frame",
    "slot_gaps_present: argument ordinal(s) below the highest read slot are never touched",
    "no_discriminator: the callee pop of 0x4 is not a whole number of dword stack arguments, so no convention follows from it"
  ],
  "cleanup": {
    "bytes": 4,
    "confidence": "UNKNOWN",
    "corroboration": "not_available",
    "evidence": "ret 0x4 but entry slot 0xc8 is read",
    "side": null
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "af9ecebc5a71b0eb37bec1e7a78bc8bcc156aa5457b945bce95856169d7903ae",
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
        "obs-0008",
        "obs-0015",
        "obs-0087"
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
        "obs-0008",
        "obs-0015",
        "obs-0087"
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
        "obs-0019",
        "obs-0023",
        "obs-0024",
        "obs-0027",
        "obs-0028",
        "obs-0029",
        "obs-0033",
        "obs-0034",
        "obs-0036",
        "obs-0037",
        "obs-0038",
        "obs-0039",
        "obs-0040",
        "obs-0041",
        "obs-0042",
        "obs-0043",
        "obs-0044",
        "obs-0045",
        "obs-0047",
        "obs-0048",
        "obs-0050",
        "obs-0051",
        "obs-0052",
        "obs-0053",
        "obs-0054",
        "obs-0056",
        "obs-0057",
        "obs-0059",
        "obs-0061",
        "obs-0064",
        "obs-0065",
        "obs-0067",
        "obs-0068",
        "obs-0070",
        "obs-0074",
        "obs-0075",
        "obs-0077",
        "obs-0078",
        "obs-0080",
        "obs-0081",
        "obs-0083"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 29,
        "observed_slots": 21,
        "total_bytes": 200
      }
    },
    {
      "based_on": [
        "obs-0004",
        "obs-0005",
        "obs-0018",
        "obs-0019",
        "obs-0020",
        "obs-0033",
        "obs-0034",
        "obs-0037",
        "obs-0043",
        "obs-0047",
        "obs-0048",
        "obs-0051",
        "obs-0057",
        "obs-0061",
        "obs-0064",
        "obs-0074",
        "obs-0080"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          88,
          132,
          172
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0087"
      ],
      "claim": "the calling convention is unknown: the terminal pop is not a whole number of dword arguments",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0008",
        "obs-0015",
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
        "obs-0008",
        "obs-0015",
 
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
"\n/* WARNING: Enum \"ObjectTYPE\": Some values do not have unique names */\n/* WARNING: Enum \"Names\": Some values do not have unique names */\n\nundefined1 __thiscall FUN_00bbaa80(int param_1,undefined4 param_2,int param_3)\n\n{\n  IGameModeManager__vftable *pIVar1;\n  IGameModeManager *pIVar2;\n  undefined4 uVar3;\n  undefined1 **ppuVar4;\n  uint32_t unaff_EBX;\n  uint32_t unaff_EBP;\n  char *unaff_ESI;\n  char *unaff_EDI;\n  int unaff_retaddr;\n  int *piVar5;\n  undefined4 uVar6;\n  IGameModeManager local_68 [3];\n  undefined4 uStack_5c;\n  undefined4 uStack_58;\n  IGameModeManager IStack_54;\n  undefined4 uStack_50;\n  undefined4 uStack_4c;\n  int aiStack_40 [2];\n  int iStack_38;\n  undefined1 *puStack_30;\n  undefined1 *puStack_2c;\n  IGameMode IStack_28;\n  undefined1 *puStack_24;\n  IGameMode local_20;\n  undefined1 *local_1c;\n  undefined1 *local_18;\n  int iStack_10;\n  int iStack_8;\n  \n  if (*(char *)(param_1 + 0xac) == '\\0') {\n    return 1;\n  }\n  FUN_00bba640();\n  if ((**(int **)(param_1 + 0x84) != 0) && (*(char *)(**(int **)(param_1 + 0x84) + 0x130) != '\\0'))\n  {\n    pIVar1 = (IGameModeManager__vftable *)FUN_00bb9e00(*(undefined4 *)(param_1 + 0x58));\n    FUN_00b8dd60(local_68);\n    if (pIVar1 != local_68[0]._vftable0) {\n      local_20._vftable0 = (IGameMode__vftable *)&DAT_01667bac;\n      local_1c = &DAT_01667bac;\n      local_18 = &DAT_01667bae;\n      pIVar2 = App__IGameModeManager__Get();\n      (*pIVar2->_vftable0[1].AddGameMode)(local_68,&local_20,unaff_EBP,unaff_ESI);\n      IStack_28._vftable0 = (IGameMode__vftable *)&DAT_01667bac;\n      puStack_24 = &DAT_01667bac;\n      local_20._vftable0 = (IGameMode__vftable *)&DAT_01667bae;\n      uStack_50 = uStack_5c;\n      uStack_4c = uStack_58;\n      IStack_54._vftable0 = pIVar1;\n      pIVar2 = App__IGameModeManager__Get();\n      (*pIVar2->_vftable0[1].AddGameMode)(&IStack_54,&IStack_28,unaff_EBX,unaff_EDI);\n      puStack_30 = &DAT_01667bac;\n      puStack_2c = &DAT_01667bac;\n      IStack_28._vftable0 = (IGameMode__vftable *)&DAT_01667bad;\n      FUN_00472fe0(&puStack_30,\" failed consistency check (0x%08x - 0x%08x)!\\n\",pIVar1,uStack_58);\n      uVar3 = FUN_0093c570(&stack0x00000000,param_1 + 0x60,&puStack_30);\n      ppuVar4 = (undefined1 **)FUN_00618890(aiStack_40,uVar3);\n      if (ppuVar4 != &puStack_30) {\n        FUN_00454cb0(*ppuVar4,ppuVar4[1]);\n      }\n      if ((1 < iStack_38 - aiStack_40[0]) && (aiStack_40[0] != 0)) {\n        FUN_00f47380(aiStack_40[0]);\n      }\n      if ((1 < param_3 - unaff_retaddr) && (unaff_retaddr != 0)) {\n        FUN_00f47380(unaff_retaddr);\n      }\n      uVar3 = *(undefined4 *)(param_1 + 0x58);\n      uVar6 = 1;\n      piVar5 = aiStack_40;\n      FUN_00b3d2a0(piVar5,uVar3,1);\n      uVar3 = FUN_00ba8010(piVar5,uVar3);\n      FUN_00b8dde0(uVar3,uVar6);\n      if ((1 < (int)IStack_28._vftable0 - (int)puStack_30) && (puStack_30 != (undefined1 *)0x0)) {\n        FUN_00f47380(puStack_30);\n      }\n      if ((2 < (int)((int)local_18 - (int)local_20._vftable0 & 0xfffffffeU)) &&\n         (local_20._vftable0 != (IGameMode__vftable *)0x0)) {\n        FUN_00f47380(local_20._vftable0);\n      }\n      if ((2 < (int)(iStack_8 - iStack_10 & 0xfffffffeU)) && (iStack_10 != 0)) {\n        FUN_00f47380(iStack_10);\n      }\n    }\n    return uStack_5c._3_1_;\n  }\n  return 1;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "original_bytes": 14175,
  "preview": "{\n  \"count\": 172,\n  \"instructions\": [\n    {\n      \"address\": \"00bbaa80\",\n      \"instruction\": \"SUB ESP,0x6c\"\n    },\n    {\n      \"address\": \"00bbaa83\",\n      \"instruction\": \"PUSH EDI\"\n    },\n    {\n      \"address\": \"00bbaa84\",\n      \"instruction\": \"MOV EDI,ECX\"\n    },\n    {\n      \"address\": \"00bbaa86\",\n      \"instruction\": \"CMP byte ptr [EDI + 0xac],0x0\"\n    },\n    {\n      \"address\": \"00bbaa8d\",\n      \"instruction\": \"JNZ 0x00bbaa98\"\n    },\n    {\n      \"address\": \"00bbaa8f\",\n      \"instruction\": \"MOV AL,0x1\"\n    },\n    {\n      \"address\": \"00bbaa91\",\n      \"instruction\": \"POP EDI\"\n    },\n    {\n      \"address\": \"00bbaa92\",\n      \"instruction\": \"ADD ESP,0x6c\"\n    },\n    {\n      \"address\": \"00bbaa95\",\n      \"instruction\": \"RET 0x4\"\n    },\n    {\n      \"address\": \"00bbaa98\",\n      \"instruction\": \"PUSH EBX\"\n    },\n    {\n      \"address\": \"00bbaa99\",\n      \"instruction\": \"CALL 0x00bba640\"\n    },\n    {\n      \"address\": \"00bbaa9e\",\n      \"instruction\": \"MOV EAX,dword ptr [EDI + 0x84]\"\n    },\n    {\n      \"address\": \"00bbaaa4\",\n      \"instruction\": \"MOV EBX,dword ptr [EAX]\"\n    },\n    {\n      \"address\": \"00bbaaa6\",\n      \"instruction\": \"TEST EBX,EBX\"\n    },\n    {\n      \"address\": \"00bbaaa8\",\n      \"instruction\": \"JZ 0x00bbaab3\"\n    },\n    {\n      \"address\": \"00bbaaaa\",\n      \"instruction\": \"CMP byte ptr [EBX + 0x130],0x0\"\n    },\n    {\n      \"address\": \"00bbaab1\",\n      \"instruction\": \"JNZ 0x00bbaabd\"\n    },\n    {\n      \"address\": \"00bbaab3\",\n      \"instruction\": \"POP EBX\"\n    },\n    {\n      \"address\": \"00bbaab4\",\n      \"instruction\": \"MOV AL,0x1\"\n    },\n    {\n      \"address\": \"00bbaab6\",\n      \"instruction\": \"POP EDI\"\n    },\n    {\n      \"address\": \"00bbaab7\",\n      \"instruction\": \"ADD ESP,0x6c\"\n    },\n    {\n      \"address\": \"00bbaaba\",\n      \"instruction\": \"RET 0x4\"\n    },\n    {\n      \"address\": \"00bbaabd\",\n      \"instruction\": \"MOV EAX,dword ptr [EDI + 0x58]\"\n    },\n    {\n      \"address\": \"00bbaac0\",\n      \"instruction\": \"PUSH ESI\"\n    },\n    {\n      \"address\": \"00bbaac1\",\n      \"instruction\": \"PUSH EAX\"\n    },\n    {\n      \"address\": \"00bbaac2\",\n      \"instruction\": \"CALL 0x00bb9e00\"\n    },\n    {\n      \"address\": \"00bbaac7\",\n      \"instruction\": \"ADD ESP,0x4\"\n    },\n    {\n      \"address\": \"00bbaaca\",\n      \"instruction\": \"LEA ECX,[ESP + 0x10]\"\n    },\n    {\n      \"address\": \"00bbaace\",\n      \"instruction\": \"PUSH ECX\"\n    },\n    {\n      \"address\": \"00bbaacf\",\n      \"instruction\": \"MOV ECX,EBX\"\n    },\n    {\n      \"address\": \"00bbaad1\",\n      \"instruction\": \"MOV ESI,EAX\"\n    },\n    {\n      \"address\": \"00bbaad3\",\n      \"instruction\": \"CALL 0x00b8dd60\"\n    },\n    {\n      \"address\": \"00bbaad8\",\n      \"instruction\": \"CMP ESI,dword ptr [ESP + 0x10]\"\n    },\n    {\n      \"address\": \"00bbaadc\",\n      \"instruction\": \"SETZ AL\"\n    },\n    {\n      \"address\": \"00bbaadf\",\n      \"instruction\": \"MOV byte ptr [ESP + 0xf],AL\"\n    },\n    {\n      \"address\": \"00bbaae3\",\n      \"instruction\": \"TEST AL,AL\"\n    },\n    {\n      \"address\": \"00bbaae5\",\n      \"instruction\": \"JNZ 0x00bbac6f\"\n    },\n    {\n      \"address\": \"00bbaaeb\",\n      \"instruction\": \"PUSH EBP\"\n    },\n    {\n      \"address\": \"00bbaaec\",\n      \"instruction\": \"MOV EBP,0x1667bac\"\n    },\n    {\n      \"address\": \"00bbaaf1\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x5c],EBP\"\n    },\n    {\n      \"address\": \"00bbaaf5\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x60],EBP\"\n    },\n    {\n      \"address\": \"00bbaaf9\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x64],0x1667bae\"\n    },\n    {\n      \"address\": \"00bbab01\",\n      \"instruction\": \"CALL 0x0067dcd0\"\n    },\n    {\n      \"address\": \"00bbab06\",\n      \"instruction\": \"MOV EDX,dword ptr [EAX]\"\n    },\n    {\n      \"address\": \"00bbab08\",\n      \"instruction\": \"MOV EDX,dword ptr [EDX + 0x7c]\"\n    },\n    {\n      \"address\": \"00bbab0b\",\n      \"instruction\": \"LEA ECX,[ESP + 0x5c]\"\n    },\n    {\n      \"address\": \"00bbab0f\",\n      \"instruction\": \"PUSH ECX\"\n    },\n    {\n      \"address\": \"00bbab10\",\n      \"instruction\": \"LEA ECX,[ESP + 0x18]\"\n    },\n    {\n      \"address\": \"00bbab14\",\n      \"instruction\": \"PUSH ECX\"\n    },\n    {\n      \"address\": \"00bbab15\",\n      \"instruction\": \"MOV ECX,EAX\"\n    },\n    {\n      \"address\": \"00bbab17\",\n      \"instruction\": \"CALL EDX\"\n    },\n    {\n      \"address\": \"00bbab19\",\n      \"instruction\": \"MOV EAX,dword ptr [ESP + 0x14]\"\n    },\n    {\n      \"address\": \"00bbab1d\",\n      \"instruction\": \"MOV ECX,dword ptr [ESP + 0x18]\"\n    },\n    {\n      \"address\": \"00bbab21\",\n      \"instruction\": \"MOV EDX,dword ptr [ESP + 0x1c]\"\n    },\n    {\n      \"address\": \"00bbab25\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x20],EAX\"\n    },\n    {\n      \"address\": \"00bbab29\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x4c],EBP\"\n    },\n    {\n      \"address\": \"00bbab2d\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x50],EBP\"\n    },\n    {\n      \"address\": \"00bbab31\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x54],0x1667bae\"\n    },\n    {\n      \"address\": \"00bbab39\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x24],ECX\"\n    },\n    {\n      \"address\": \"00bbab3d\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x28],EDX\"\n    },\n    {\n      \"address\": \"00bbab41\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x20],ESI\"\n    },\n    {\n      \"address\": \"00bbab45\",\n      \"instruction\
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
  "body_end": "00bbac7b",
  "body_span_bytes": 508,
  "body_start": "00bbaa80",
  "callees": [
    "FUN_00b3d2a0",
    "FUN_00454cb0",
    "FUN_00bb9e00",
    "FUN_00f47380",
    "FUN_00ba8010",
    "FUN_00bba640",
    "FUN_00b8dde0",
    "FUN_00b8dd60",
    "App::IGameModeManager::Get",
    "FUN_00618890",
    "FUN_00472fe0",
    "FUN_0093c570"
  ],
  "callers": [
    "FUN_00deb930",
    "FUN_00df47b0",
    "FUN_00ba6e00"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00bbaa80",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "unaff_retaddr",
      "storage": "Stack[0x0]:4",
      "type": "int"
    },
    {
      "name": "unaff_EDI",
      "storage": "register:0000001c:4",
      "type": "char *"
    },
    {
      "name": "uVar6",
      "storage": "Stack[-0x6c]:4",
      "type": "undefined4"
    },
    {
      "name": "piVar5",
      "storage": "Stack[-0x74]:4",
      "type": "int *"
    },
    {
      "name": "unaff_EBX",
      "storage": "register:0000000c:4",
      "type": "uint32_t"
    },
    {
      "name": "ppuVar4",
      "storage": "register:00000000:4",
      "type": "undefined1 * *"
    },
    {
      "name": "unaff_ESI",
      "storage": "register:00000018:4",
      "type": "char *"
    },
    {
      "name": "unaff_EBP",
      "storage": "register:00000014:4",
      "type": "uint32_t"
    },
    {
      "name": "pIVar1",
      "storage": "register:00000000:4",
      "type": "IGameModeManager__vftable *"
    },
    {
      "name": "param_3",
      "storage": "Stack[0x8]:4",
      "type": "int"
    },
    {
      "name": "uVar3",
      "storage": "register:00000000:4",
      "type": "undefined4"
    },
    {
      "name": "pIVar2",
      "storage": "register:00000000:4",
      "type": "IGameModeManager *"
    },
    {
      "name": "uStack_5c",
      "storage": "Stack[-0x5c]:4",
      "type": "undefined4"
    },
    {
      "name": "IStack_54",
      "storage": "Stack[-0x54]:4",
      "type": "IGameModeManager"
    },
    {
      "name": "uStack_58",
      "storage": "Stack[-0x58]:4",
      "type": "undefined4"
    },
    {
      "name": "iStack_8",
      "storage": "Stack[-0x8]:4",
      "type": "int"
    },
    {
      "name": "param_2",
      "storage": "",
      "type": "undefined4"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int"
    },
    {
      "name": "local_68",
      "storage": "Stack[-0x68]:4",
      "type": "IGameModeManager[3]"
    },
    {
      "name": "iStack_10",
      "storage": "Stack[-0x10]:4",
      "type": "int"
    },
    {
      "name": "local_1c",
      "storage": "Stack[-0x1c]:4",
      "type": "undefined1 *"
    },
    {
      "name": "local_20",
      "storage": "Stack[-0x20]:4",
      "type": "IGameMode"
    },
    {
      "name": "puStack_2c",
      "storage": "Stack[-0x2c]:4",
      "type": "undefined1 *"
    },
    {
      "name": "local_18",
      "storage": "Stack[-0x18]:4",
      "type": "undefined1 *"
    },
    {
      "name": "puStack_30",
      "storage": "Stack[-0x30]:4",
      "type": "undefined1 *"
    },
    {
      "name": "puStack_24",
      "storage": "Stack[-0x24]:4",
      "type": "undefined1 *"
    },
    {
      "name": "IStack_28",
      "storage": "Stack[-0x28]:4",
      "type": "IGameMode"
    },
    {
      "name": "uStack_4c",
      "storage": "Stack[-0x4c]:4",
      "type": "undefined4"
    },
    {
      "name": "uStack_50",
      "storage": "Stack[-0x50]:4",
      "type": "undefined4"
    },
    {
      "name": "iStack_38",
      "storage": "Stack[-0x38]:4",
      "type": "int"
    },
    {
      "name": "aiStack_40",
      "storage": "Stack[-0x40]:4",
      "type": "int[2]"
    }
  ],
  "locals_count": 31,
  "mode": "live",
  "name": "FUN_00bbaa80",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x7baa80",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00bbaa80(void)",
  "size_bytes": 508,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00bbaa80",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 3,
  "xrefs": [
    {
      "from": "00ba6e4e"
    },
    {
      "from": "00debbc4"
    },
    {
      "from": "00df4fba"
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
