# Evidence 0x005a9200

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `2054a62ea8ddc318edf467f47b85815dd85e049ecb1272de4dfe37ae859bb4d3`

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
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +48, so the listing is not one path",
    "unparsed_lines_present: 1 line(s) matched no grammar rule",
    "receiver_not_determinable: ecx_reassigned_before_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_reassigned_before_deref), and the convention rule that would apply discriminates on receiver absence",
    "sret_vs_out_param: entry slot 0 is written through a pointer"
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
  "content_sha256": "c0c923b55965f971edf9d78b8222f36f6dab0611bfefbcf5486ac439ebed0198",
  "conventions": {
    "ambiguities": [
      "receiver_undetermined"
    ],
    "calling_convention": null,
    "candidate_conventions": [
      "__cdecl",
      "__thiscall"
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
    "indirect_calls": 5,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0033"
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
        "obs-0012"
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
        "obs-0007",
        "obs-0014"
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
        "obs-0007",
        "obs-0014"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_reassigned_before_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0012"
      ],
      "claim": "a hidden struct-return pointer is a hypothesis only: entry slot 0 is written through a pointer",
      "confidence": "INFERRED",
      "id": "S1",
      "value": {
        "ambiguity": "sret_vs_out_param",
        "present": null,
        "slot": 4
      }
    },
    {
      "based_on": [
        "obs-0033"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0033"
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
      "at": "0x005a9200",
      "count": 8,
      "first_use": 0,
      "first_write_index": 61,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x005a9201",
      "count": 5,
      "first_use": 1,
      "first_write_index": 35,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x005a9202",
      "count": 8,
      "first_use": 2,
      "first_write_index": 8,
      "id": "obs-0003",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x005a9203",
      "id": "obs-0004",
      "index": 3,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x0067dd10",
      "target": "0x0067dd10"
    },
    {
      "at": "0x005a9208",
      "count": 27,
      "first_use": 4,
      "first_write_index": 6,
      "id": "obs-0005",
      "index": 4,
      "kind": "REG_READ",
      "raw": "MOV EDX,dword ptr [EAX]",
      "reg": "EAX"
    },
    {
      "at": "0x005a9208",
      "definite": true,
      "id": "obs-0006",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [EAX]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x005a920a",
      "definite": true,
      "id": "obs-0007",
      "index": 5,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,EAX",
      "reg": "ECX",
      "write_kind": "reg"
    },
    {
      "at": "0x005a920c",
      "count": 15,
      "first_use": 6,
      "first_write_index": 4,
      "id": "obs-0008",
      "index": 6,
      "kind": "REG_READ",
   
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
"\nundefined4 FUN_005a9200(undefined4 param_1,undefined4 param_2,CommandLine *param_3)\n\n{\n  int *piVar1;\n  IRenderer *pIVar2;\n  wchar16 *pwVar3;\n  uint uVar4;\n  string16 *psVar5;\n  IAppSystem *pIVar6;\n  CommandLine *commandLine;\n  int iVar7;\n  sbyte sVar8;\n  int *piVar9;\n  undefined1 unaff_SI;\n  IRenderer *unaff_EDI;\n  undefined4 uVar10;\n  undefined4 uVar11;\n  CommandLine *pCVar12;\n  int iVar13;\n  \n  pIVar2 = Graphics__IRenderer__Get();\n  pwVar3 = (wchar16 *)(*pIVar2->_vftable0->func38h)(unaff_EDI,(bool)unaff_SI);\n  piVar1 = &(param_3->field_18).mAllocator;\n  (param_3->field_18).mpEnd = pwVar3;\n  uVar4 = 0;\n  piVar9 = piVar1;\n  do {\n    if (*piVar9 != 0) goto LAB_005a924f;\n    uVar4 = uVar4 + 1;\n    piVar9 = piVar9 + 1;\n  } while (uVar4 < 4);\n  *piVar1 = Editors__ContentValidation__sIllegalCharacters;\n  (param_3->field_28).mpBegin = DAT_015da7c8;\n  (param_3->field_28).mpEnd = DAT_015da7cc;\n  (param_3->field_28).mpCapacity = DAT_015da7d0;\nLAB_005a924f:\n  if ((param_3->mSplits).mpCapacity == (string16 *)0xffffffff) {\n    psVar5 = (string16 *)FUN_005a8f80();\n    (param_3->mSplits).mpCapacity = psVar5;\n  }\n  pIVar6 = App__IAppSystem__Get();\n  iVar13 = 0;\n  pCVar12 = (CommandLine *)0x0;\n  (*pIVar6->_vftable0->InitPlugins)((IAppSystem *)0xb03bc30c,param_3);\n  commandLine = (CommandLine *)FUN_00f473a0(0x40,&DAT_013ebc58,0,0,0,0);\n  if (commandLine == (CommandLine *)0x0) {\n    commandLine = (CommandLine *)0x0;\n  }\n  else {\n    (commandLine->field_28).mpCapacity = (wchar16 *)0x0;\n    commandLine->_vftable0 = (CommandLine__vftable *)&PTR_FUN_013eb90c;\n    LOCK();\n    (commandLine->mSplits).mpBegin = (string16 *)0x0;\n    UNLOCK();\n    commandLine->_vftable0 = (CommandLine__vftable *)&PTR_FUN_013eb844;\n    commandLine[1]._vftable0 = (CommandLine__vftable *)0x0;\n    (*commandLine->_vftable0[1]._virtual_dtor)(pCVar12,iVar13);\n  }\n  iVar13 = 0;\n  (commandLine->field_28).mpCapacity =\n       L\"\\xe851뭨\\xffff䓙⠤죜࿳吐Ⱔ䓙〤࿳尐〤죜ᚋ芋È\";\n  pCVar12 = (CommandLine *)0x0;\n  (commandLine->mSplits).mpEnd = (string16 *)&DAT_00dbdba1;\n  (*pIVar6->_vftable0->InitPlugins)((IAppSystem *)(commandLine->field_28).mpCapacity,commandLine);\n  uVar10 = 0x1003;\n  FUN_0067cab0(0x1003);\n  FUN_00801bb0(uVar10);\n  psVar5 = (param_3->mSplits).mpCapacity;\n  sVar8 = 0;\n  if ((int)psVar5 < 0x1d2ec0a8) {\n    if ((int)psVar5 < 0x1d2ec0a4) {\n      if ((int)psVar5 < -0x48507007) {\n        if (psVar5 == (string16 *)0xb7af8ff8) goto LAB_005a9422;\n        if ((int)psVar5 < -0x6616d0fa) {\n          if ((psVar5 != (string16 *)0x99e92f05) && (psVar5 != (string16 *)0x8707be7d)) {\n            if (psVar5 != (string16 *)0x8f963dcb) {\n              if (psVar5 == (string16 *)0x96b24187) {\n                sVar8 = 0xf;\n              }\n              goto LAB_005a9427;\n            }\n            goto LAB_005a9466;\n          }\n          goto LAB_005a94b7;\n        }\n        if (psVar5 != (string16 *)0x9ad7d4aa) {\n          if (psVar5 == (string16 *)0x9adf00a9) {\n            sVar8 = 8;\n            goto LAB_005a9427;\n          }\n          if (psVar5 != (string16 *)0xa56567f7) goto LAB_005a9427;\n          goto LAB_005a937a;\n        }\n      }\n      else {\n        if (-0x98f55bd < (int)psVar5) {\n          if (psVar5 == (string16 *)0x156276d1) {\nLAB_005a9406:\n            sVar8 = 7;\n            goto LAB_005a9427;\n          }\n          if (psVar5 == (string16 *)0x1a4e0708) goto LAB_005a948d;\n          if (psVar5 != (string16 *)0x1d2ec0a0) goto LAB_005a9427;\n          goto LAB_005a93d4;\n        }\n        if (psVar5 != (string16 *)0xf670aa43) {\n          if (psVar5 != (string16 *)0xbc1041e6) {\n            if (psVar5 == (string16 *)0xbdd15f3d) goto LAB_005a94b7;\n            if (psVar5 != (string16 *)0xc15695da) goto LAB_005a9427;\n          }\nLAB_005a93b4:\n          sVar8 = 0xd;\n          goto LAB_005a9427;\n        }\n      }\nLAB_005a94ad:\n      sVar8 = 10;\n    }\n    else {\nLAB_005a93d4:\n      sVar8 = 5;\n    }\n    goto LAB_005a9427;\n  }\n  if ((int)psVar5 < 0x37e82da2) {\n    if (psVar5 == (string16 *)0x37e82da1) {\nLAB_005a937a:\n      sVar8 = 0xe;\n      goto LAB_005a9427;\n    }\n    if ((int)psVar5 < 0x281f5961) {\n      if (psVar5 != (string16 *)0x281f5960) {\n        if (psVar5 != (string16 *)0x1f2a25b6) {\n          if (psVar5 == (string16 *)0x2090a11b) goto LAB_005a93b4;\n          if (psVar5 != (string16 *)0x247e2615) goto LAB_005a9427;\n          goto LAB_005a9406;\n        }\nLAB_005a9466:\n        sVar8 = 0xb;\n        goto LAB_005a9427;\n      }\n    }\n    else if (psVar5 != (string16 *)0x290adace) {\n      if (psVar5 == (string16 *)0x2a5147a9) goto LAB_005a9466;\n      if (psVar5 != (string16 *)0x312e9d6a) goto LAB_005a9427;\n    }\n  }\n  else if ((int)psVar5 < 0x4e3f7778) {\n    if (psVar5 == (string16 *)0x4e3f7777) {\nLAB_005a94b7:\n      sVar8 = 9;\n      goto LAB_005a9427;\n    }\n    if ((psVar5 == (string16 *)0x441cd3e6) || (psVar5 == (string16 *)0x449c040f)) {\nLAB_005a948d:\n      sVar8 = 0xc;\n      goto LAB_005a9427;\n    }\n    if (psVar5 != (string16 *)0x465c50ba) goto LAB_005a9427;\n  }\n  else if (psVar5 != (string16 *)0x5bf8f774) {\n    if (psVar5 != (string16 *)0x72c49181) {\n      if (psVar5 != (string16 *)0x7d433fad) goto LAB_005a9427;\n      goto LAB_005a94ad;\n    }\n    goto LAB_005a94b7;\n  }\nLAB_005a9422:\n  sVar8 = 6;\nLAB_005a9427:\n  if ((*(int *)(*(int *)(App__sAppProperties + 0x3c) + 0x118) == 0) && (sVar8 != 0)) {\n    iVar7 = 1 << sVar8;\n    uVar11 = 1;\n    uVar10 = 0xd082675a;\n    FUN_00675250(0xd082675a,iVar7,1);\n    FUN_00676ed0(uVar10,iVar7,uVar11);\n  }\n  (*commandLine->_vftable0[2]._virtual_dtor)(pCVar12,iVar13);\n  return 1;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "original_bytes": 16279,
  "preview": "{\n  \"count\": 199,\n  \"instructions\": [\n    {\n      \"address\": \"005a9200\",\n      \"instruction\": \"PUSH EBX\"\n    },\n    {\n      \"address\": \"005a9201\",\n      \"instruction\": \"PUSH ESI\"\n    },\n    {\n      \"address\": \"005a9202\",\n      \"instruction\": \"PUSH EDI\"\n    },\n    {\n      \"address\": \"005a9203\",\n      \"instruction\": \"CALL 0x0067dd10\"\n    },\n    {\n      \"address\": \"005a9208\",\n      \"instruction\": \"MOV EDX,dword ptr [EAX]\"\n    },\n    {\n      \"address\": \"005a920a\",\n      \"instruction\": \"MOV ECX,EAX\"\n    },\n    {\n      \"address\": \"005a920c\",\n      \"instruction\": \"MOV EAX,dword ptr [EDX + 0x38]\"\n    },\n    {\n      \"address\": \"005a920f\",\n      \"instruction\": \"CALL EAX\"\n    },\n    {\n      \"address\": \"005a9211\",\n      \"instruction\": \"MOV EDI,dword ptr [ESP + 0x10]\"\n    },\n    {\n      \"address\": \"005a9215\",\n      \"instruction\": \"LEA EDX,[EDI + 0x24]\"\n    },\n    {\n      \"address\": \"005a9218\",\n      \"instruction\": \"MOV dword ptr [EDI + 0x1c],EAX\"\n    },\n    {\n      \"address\": \"005a921b\",\n      \"instruction\": \"XOR EAX,EAX\"\n    },\n    {\n      \"address\": \"005a921d\",\n      \"instruction\": \"MOV ECX,EDX\"\n    },\n    {\n      \"address\": \"005a921f\",\n      \"instruction\": \"NOP\"\n    },\n    {\n      \"address\": \"005a9220\",\n      \"instruction\": \"CMP dword ptr [ECX],0x0\"\n    },\n    {\n      \"address\": \"005a9223\",\n      \"instruction\": \"JNZ 0x005a924f\"\n    },\n    {\n      \"address\": \"005a9225\",\n      \"instruction\": \"INC EAX\"\n    },\n    {\n      \"address\": \"005a9226\",\n      \"instruction\": \"ADD ECX,0x4\"\n    },\n    {\n      \"address\": \"005a9229\",\n      \"instruction\": \"CMP EAX,0x4\"\n    },\n    {\n      \"address\": \"005a922c\",\n      \"instruction\": \"JC 0x005a9220\"\n    },\n    {\n      \"address\": \"005a922e\",\n      \"instruction\": \"MOV ECX,dword ptr [0x015da7c4]\"\n    },\n    {\n      \"address\": \"005a9234\",\n      \"instruction\": \"MOV dword ptr [EDX],ECX\"\n    },\n    {\n      \"address\": \"005a9236\",\n      \"instruction\": \"MOV EAX,[0x015da7c8]\"\n    },\n    {\n      \"address\": \"005a923b\",\n      \"instruction\": \"MOV dword ptr [EDX + 0x4],EAX\"\n    },\n    {\n      \"address\": \"005a923e\",\n      \"instruction\": \"MOV ECX,dword ptr [0x015da7cc]\"\n    },\n    {\n      \"address\": \"005a9244\",\n      \"instruction\": \"MOV dword ptr [EDX + 0x8],ECX\"\n    },\n    {\n      \"address\": \"005a9247\",\n      \"instruction\": \"MOV EAX,[0x015da7d0]\"\n    },\n    {\n      \"address\": \"005a924c\",\n      \"instruction\": \"MOV dword ptr [EDX + 0xc],EAX\"\n    },\n    {\n      \"address\": \"005a924f\",\n      \"instruction\": \"CMP dword ptr [EDI + 0xc],-0x1\"\n    },\n    {\n      \"address\": \"005a9253\",\n      \"instruction\": \"JNZ 0x005a9260\"\n    },\n    {\n      \"address\": \"005a9255\",\n      \"instruction\": \"LEA EAX,[EDI + 0x10]\"\n    },\n    {\n      \"address\": \"005a9258\",\n      \"instruction\": \"CALL 0x005a8f80\"\n    },\n    {\n      \"address\": \"005a925d\",\n      \"instruction\": \"MOV dword ptr [EDI + 0xc],EAX\"\n    },\n    {\n      \"address\": \"005a9260\",\n      \"instruction\": \"CALL 0x0067dcc0\"\n    },\n    {\n      \"address\": \"005a9265\",\n      \"instruction\": \"PUSH 0x0\"\n    },\n    {\n      \"address\": \"005a9267\",\n      \"instruction\": \"MOV ESI,EAX\"\n    },\n    {\n      \"address\": \"005a9269\",\n      \"instruction\": \"MOV EDX,dword ptr [ESI]\"\n    },\n    {\n      \"address\": \"005a926b\",\n      \"instruction\": \"MOV EAX,dword ptr [EDX + 0x18]\"\n    },\n    {\n      \"address\": \"005a926e\",\n      \"instruction\": \"PUSH 0x0\"\n    },\n    {\n      \"address\": \"005a9270\",\n      \"instruction\": \"PUSH EDI\"\n    },\n    {\n      \"address\": \"005a9271\",\n      \"instruction\": \"PUSH 0xb03bc30c\"\n    },\n    {\n      \"address\": \"005a9276\",\n      \"instruction\": \"MOV ECX,ESI\"\n    },\n    {\n      \"address\": \"005a9278\",\n      \"instruction\": \"CALL EAX\"\n    },\n    {\n      \"address\": \"005a927a\",\n      \"instruction\": \"PUSH 0x0\"\n    },\n    {\n      \"address\": \"005a927c\",\n      \"instruction\": \"PUSH 0x0\"\n    },\n    {\n      \"address\": \"005a927e\",\n      \"instruction\": \"PUSH 0x0\"\n    },\n    {\n      \"address\": \"005a9280\",\n      \"instruction\": \"PUSH 0x0\"\n    },\n    {\n      \"address\": \"005a9282\",\n      \"instruction\": \"PUSH 0x13ebc58\"\n    },\n    {\n      \"address\": \"005a9287\",\n      \"instruction\": \"PUSH 0x40\"\n    },\n    {\n      \"address\": \"005a9289\",\n      \"instruction\": \"CALL 0x00f473a0\"\n    },\n    {\n      \"address\": \"005a928e\",\n      \"instruction\": \"ADD ESP,0x18\"\n    },\n    {\n      \"address\": \"005a9291\",\n      \"instruction\": \"TEST EAX,EAX\"\n    },\n    {\n      \"address\": \"005a9293\",\n      \"instruction\": \"JZ 0x005a9356\"\n    },\n    {\n      \"address\": \"005a9299\",\n      \"instruction\": \"MOV dword ptr [EAX + 0x30],0x0\"\n    },\n    {\n      \"address\": \"005a92a0\",\n      \"instruction\": \"MOV dword ptr [EAX],0x13eb90c\"\n    },\n    {\n      \"address\": \"005a92a6\",\n      \"instruction\": \"XOR ECX,ECX\"\n    },\n    {\n      \"address\": \"005a92a8\",\n      \"instruction\": \"LEA EDX,[EAX + 0x4]\"\n    },\n    {\n      \"address\": \"005a92ab\",\n      \"instruction\": \"XCHG dword ptr [EDX],ECX\"\n    },\n    {\n      \"address\": \"005a92ad\",\n      \"instruction\": \"MOV dword ptr [EAX],0x13eb844\"\n    },\n    {\n      \"address\": \"005a92b3\",\n      \"instruction\": \"MOV dword ptr [EAX + 0x38],0x0\"\n    },\n    {\n      \"address\": \"005a92ba\",\n      \"instruction\": \"MOV EDX,dword ptr [EAX]\"\n    },\n    {\n      \"address\": \"005a92bc\",\n      \"instruction\": \"MOV EBX,EAX\"\n    },\n    {\n      
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
  "body_end": "005a94c0",
  "body_span_bytes": 705,
  "body_start": "005a9200",
  "callees": [
    "Reference",
    "Graphics::IRenderer::Get",
    "FUN_005a8f80",
    "FUN_00f473a0",
    "FUN_00676ed0",
    "FUN_0067cab0",
    "FUN_00404f90",
    "App::IAppSystem::Get",
    "FUN_00801bb0",
    "FUN_00675250"
  ],
  "callers": [
    "FUN_005a94d0",
    "FUN_00d43e30",
    "FUN_00b1dee0",
    "FUN_0064acd0",
    "FUN_00d3c6a0",
    "FUN_00e84600"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "005a9200",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "iVar13",
      "storage": "Stack[-0x8]:4",
      "type": "int"
    },
    {
      "name": "uVar10",
      "storage": "Stack[-0x18]:4",
      "type": "undefined4"
    },
    {
      "name": "unaff_EDI",
      "storage": "register:0000001c:4",
      "type": "IRenderer *"
    },
    {
      "name": "pCVar12",
      "storage": "Stack[-0xc]:4",
      "type": "CommandLine *"
    },
    {
      "name": "uVar11",
      "storage": "Stack[-0x18]:4",
      "type": "undefined4"
    },
    {
      "name": "sVar8",
      "storage": "register:00000004:1",
      "type": "sbyte"
    },
    {
      "name": "iVar7",
      "storage": "register:00000000:4",
      "type": "int"
    },
    {
      "name": "unaff_SI",
      "storage": "register:00000018:1",
      "type": "undefined1"
    },
    {
      "name": "piVar9",
      "storage": "register:00000004:4",
      "type": "int *"
    },
    {
      "name": "psVar5",
      "storage": "register:00000000:4",
      "type": "string16 *"
    },
    {
      "name": "uVar4",
      "storage": "register:00000000:4",
      "type": "uint"
    },
    {
      "name": "commandLine",
      "storage": "register:0000000c:4",
      "type": "CommandLine *"
    },
    {
      "name": "pIVar6",
      "storage": "register:00000000:4",
      "type": "IAppSystem *"
    },
    {
      "name": "piVar1",
      "storage": "unique:00006600:4",
      "type": "int *"
    },
    {
      "name": "param_3",
      "storage": "Stack[0xc]:4",
      "type": "CommandLine *"
    },
    {
      "name": "pwVar3",
      "storage": "register:00000000:4",
      "type": "wchar16 *"
    },
    {
      "name": "pIVar2",
      "storage": "register:00000000:4",
      "type": "IRenderer *"
    },
    {
      "name": "param_2",
      "storage": "",
      "type": "undefined4"
    },
    {
      "name": "param_1",
      "storage": "",
      "type": "undefined4"
    }
  ],
  "locals_count": 19,
  "mode": "live",
  "name": "FUN_005a9200",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x1a9200",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_005a9200(void)",
  "size_bytes": 705,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x005a9200",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 10,
  "xrefs": [
    {
      "from": "0064b417"
    },
    {
      "from": "005a95ea"
    },
    {
      "from": "00b1df94"
    },
    {
      "from": "00d3c8ca"
    },
    {
      "from": "00e8467b"
    },
    {
      "from": "00e8475c"
    },
    {
      "from": "00d45002"
    },
    {
      "from": "00cf5955"
    },
    {
      "from": "00d43044"
    },
    {
      "from": "00dee6d7"
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
