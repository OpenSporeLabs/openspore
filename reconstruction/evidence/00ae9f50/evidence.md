# Evidence 0x00ae9f50

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `ccb684b58d611003b5d20a529cac10bd64e3a479c8f6ac74891649fe29fdf8e9`

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
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
    "saved_registers": [
      "EBP",
      "EBX",
      "EDI",
      "ESI"
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +68, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "2a9d66fa2f581e93375f884c53094afd305f2916c8a294f713f2cd8f3e8db8d5",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall",
      "__fastcall"
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
    "indirect_calls": 3,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0073"
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
        "obs-0004",
        "obs-0005",
        "obs-0007",
        "obs-0008",
        "obs-0021",
        "obs-0032",
        "obs-0035",
        "obs-0036",
        "obs-0046",
        "obs-0047",
        "obs-0049",
        "obs-0070"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "SUPPORTED",
      "id": "R1",
      "value": {
        "offsets": [
          32,
          100,
          104,
          116
        ],
        "register": "ECX",
        "written_through": 2
      }
    },
    {
      "based_on": [
        "obs-0004",
        "obs-0005",
        "obs-0007",
        "obs-0008",
        "obs-0021",
        "obs-0032",
        "obs-0035",
        "obs-0036",
        "obs-0046",
        "obs-0047",
        "obs-0049",
        "obs-0070",
        "obs-0073"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0073"
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
        "obs-0073"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0073"
      ],
      "claim": "the last value written to EAX classifies as aggregate_unknown",
      "confidence": "INFERRED",
      "id": "RT2",
      "value": {
        "register_class": "aggregate_unknown"
      }
    }
  ],
  "observations": [
    {
      "and_esp": null,
      "at": "0x00ae9f50",
      "ebp_is_general_register": true,
      "fp": false,
      "id": "obs-0001",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": true,
      "push_ebp_at": 12,
      "raw": "SUB ESP,0x80",
      "sub": 128
    },
    {
      "at": "0x00ae9f50",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x80",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00ae9f56",
      "count": 13,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00ae9f57",
      "count": 15,
      "first_use": 2,
      "first_write_index": 4,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00ae9f57",
      "definite": true,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00ae9f59",
      "id": "obs-0006",
      "index": 3,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00dd1ca0",
      "target": "0x00dd1ca0"
    },
    {
      "at": "0x00ae9f5e",
      "count": 36,
      "first_use": 4,
      "first_write_index": 6,
      "id": "obs-0007",
      "index": 4,
      "kind": "REG_READ",
      "raw": "MOV ECX,EAX",
      "reg": "EAX"
    },
    {
      "at": "0x00ae9f5e",
      "definite": true,
      "id": "obs-0008",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,EAX",
      "reg": "ECX",
      "write_kind": "reg"
    },
    {
      "at": "0x00ae9f60",
      "id": "obs-0009",
      "index": 5,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00dd30d0",
      "target": "0x00dd30d0"
    },
    {
      "at": "0x00ae9f65",
      "definite": true,
      "id": "obs-001
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
"\n/* WARNING: Enum \"ObjectTYPE\": Some values do not have unique names */\n/* WARNING: Enum \"Names\": Some values do not have unique names */\n\nvoid __fastcall FUN_00ae9f50(int param_1)\n\n{\n  wchar16 *pwVar1;\n  void *pvVar2;\n  IAppSystem *pIVar3;\n  void *pvVar4;\n  int iVar5;\n  int *piVar6;\n  undefined4 uVar7;\n  cToolManager *pcVar8;\n  bool bVar9;\n  undefined4 uVar10;\n  undefined4 uVar11;\n  undefined4 uVar12;\n  undefined4 uVar13;\n  undefined1 local_80 [56];\n  undefined4 local_48;\n  void *pvStack_44;\n  IAppSystem *pIStack_1c;\n  undefined4 uStack_14;\n  \n  FUN_00dd1ca0();\n  FUN_00dd30d0();\n  iVar5 = *(int *)(param_1 + 0x20);\n  if (iVar5 != 0) {\n    bVar9 = *(int *)(iVar5 + 0xc) != 0;\n    if (bVar9) {\n      pvVar2 = (void *)0x0;\n    }\n    else {\n      uVar7 = *(undefined4 *)(iVar5 + 0x18);\n      FUN_00b3d2a0(uVar7);\n      pvVar2 = (void *)FUN_00ba9370(uVar7);\n    }\n    local_80._48_4_ = (IAppSystem *)0x3ac86b5;\n    LOCK();\n    local_80._4_4_ = (string16 *)0x0;\n    UNLOCK();\n    iVar5 = *(int *)(param_1 + 0x20);\n    local_80._0_4_ = &PTR_FUN_013eb844;\n    local_48 = 0;\n    local_80._8_4_ = *(undefined4 *)(iVar5 + 0xc);\n    local_80._16_4_ = pvVar2;\n    if (bVar9) {\n      uVar7 = *(undefined4 *)(iVar5 + 0x18);\n      FUN_00b3d300(uVar7);\n      FUN_00b20750(uVar7);\n      local_80._16_4_ = *(void **)(iVar5 + 0x28);\n      if (*(void **)(iVar5 + 0x28) == (void *)0x0) {\n        local_80._16_4_ = FUN_00bd9bf0();\n      }\n    }\n    pwVar1 = *(wchar16 **)(param_1 + 0x20);\n    if (bVar9) {\n      local_80._24_4_ = *(undefined4 *)(pwVar1 + 0x10);\n      local_80._32_4_ = *(undefined4 *)(pwVar1 + 0x12);\n    }\n    else {\n      local_80._32_4_ = (wchar16 *)0x0;\n      local_80._24_4_ = pwVar1;\n    }\n    pIVar3 = App__IAppSystem__Get();\n    (*pIVar3->_vftable0->Init)((IAppSystem *)local_80._48_4_,(CommandLine *)local_80);\n    if ((*(char *)(*(int *)(param_1 + 0x20) + 0x30) == '\\0') &&\n       (pvVar4 = (void *)FUN_01021300(), pvVar2 != pvVar4)) {\n      pIStack_1c = (IAppSystem *)0x43f2590;\n      LOCK();\n      local_48 = 0;\n      UNLOCK();\n      local_80._52_4_ = &PTR_FUN_013eb844;\n      uStack_14 = 0;\n      pvStack_44 = pvVar2;\n      pIVar3 = App__IAppSystem__Get();\n      (*pIVar3->_vftable0->Init)(pIStack_1c,(CommandLine *)(local_80 + 0x34));\n      FUN_00421cf0();\n    }\n    iVar5 = FUN_00b3d380();\n    if (iVar5 != 0) {\n      FUN_00b32250(0x4d02e35);\n    }\n    piVar6 = (int *)FUN_00a206f0();\n    if (piVar6 == (int *)0x0) {\n      uVar7 = 0;\n    }\n    else {\n      uVar7 = (**(code **)(*piVar6 + 0x20))();\n    }\n    FUN_00435ed0(0x1e5e7302,uVar7);\n    pcVar8 = Simulator__cToolManager__Get();\n    if (pcVar8 != (cToolManager *)0x0) {\n      Simulator__cToolManager__Get();\n      FUN_00ae8ea0();\n    }\n    uVar7 = 1;\n    Simulator__cGameNounManager__Get();\n    FUN_00e14c10(uVar7);\n    iVar5 = *(int *)(param_1 + 0x74);\n    if (iVar5 != -1) {\n      FUN_00b3d2a0(iVar5);\n      iVar5 = FUN_00ba6d80(iVar5);\n      if (iVar5 != 0) {\n        uVar7 = FUN_01021090();\n        FUN_00c35240(iVar5,uVar7);\n      }\n      *(undefined4 *)(param_1 + 0x74) = 0xffffffff;\n    }\n    iVar5 = *(int *)(param_1 + 100);\n    if (iVar5 != *(int *)(param_1 + 0x68)) {\n      uVar13 = 0;\n      uVar12 = 0;\n      uVar11 = 0;\n      uVar10 = 0;\n      uVar7 = 1;\n      Simulator__cSpaceTrading__Get();\n      FUN_00ae0930(iVar5,uVar7,uVar10,uVar11,uVar12,uVar13);\n      if (*(undefined1 **)(param_1 + 100) != *(undefined1 **)(param_1 + 0x68)) {\n        **(undefined1 **)(param_1 + 100) = 0;\n        *(undefined4 *)(param_1 + 0x68) = *(undefined4 *)(param_1 + 100);\n      }\n    }\n    FUN_00421cf0();\n  }\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "original_bytes": 14022,
  "preview": "{\n  \"count\": 169,\n  \"instructions\": [\n    {\n      \"address\": \"00ae9f50\",\n      \"instruction\": \"SUB ESP,0x80\"\n    },\n    {\n      \"address\": \"00ae9f56\",\n      \"instruction\": \"PUSH ESI\"\n    },\n    {\n      \"address\": \"00ae9f57\",\n      \"instruction\": \"MOV ESI,ECX\"\n    },\n    {\n      \"address\": \"00ae9f59\",\n      \"instruction\": \"CALL 0x00dd1ca0\"\n    },\n    {\n      \"address\": \"00ae9f5e\",\n      \"instruction\": \"MOV ECX,EAX\"\n    },\n    {\n      \"address\": \"00ae9f60\",\n      \"instruction\": \"CALL 0x00dd30d0\"\n    },\n    {\n      \"address\": \"00ae9f65\",\n      \"instruction\": \"MOV EAX,dword ptr [ESI + 0x20]\"\n    },\n    {\n      \"address\": \"00ae9f68\",\n      \"instruction\": \"TEST EAX,EAX\"\n    },\n    {\n      \"address\": \"00ae9f6a\",\n      \"instruction\": \"JZ 0x00aea15f\"\n    },\n    {\n      \"address\": \"00ae9f70\",\n      \"instruction\": \"CMP dword ptr [EAX + 0xc],0x0\"\n    },\n    {\n      \"address\": \"00ae9f74\",\n      \"instruction\": \"PUSH EBX\"\n    },\n    {\n      \"address\": \"00ae9f75\",\n      \"instruction\": \"SETZ BL\"\n    },\n    {\n      \"address\": \"00ae9f78\",\n      \"instruction\": \"PUSH EBP\"\n    },\n    {\n      \"address\": \"00ae9f79\",\n      \"instruction\": \"PUSH EDI\"\n    },\n    {\n      \"address\": \"00ae9f7a\",\n      \"instruction\": \"TEST BL,BL\"\n    },\n    {\n      \"address\": \"00ae9f7c\",\n      \"instruction\": \"JZ 0x00ae9f92\"\n    },\n    {\n      \"address\": \"00ae9f7e\",\n      \"instruction\": \"MOV EAX,dword ptr [EAX + 0x18]\"\n    },\n    {\n      \"address\": \"00ae9f81\",\n      \"instruction\": \"PUSH EAX\"\n    },\n    {\n      \"address\": \"00ae9f82\",\n      \"instruction\": \"CALL 0x00b3d2a0\"\n    },\n    {\n      \"address\": \"00ae9f87\",\n      \"instruction\": \"MOV ECX,EAX\"\n    },\n    {\n      \"address\": \"00ae9f89\",\n      \"instruction\": \"CALL 0x00ba9370\"\n    },\n    {\n      \"address\": \"00ae9f8e\",\n      \"instruction\": \"MOV EBP,EAX\"\n    },\n    {\n      \"address\": \"00ae9f90\",\n      \"instruction\": \"JMP 0x00ae9f94\"\n    },\n    {\n      \"address\": \"00ae9f92\",\n      \"instruction\": \"XOR EBP,EBP\"\n    },\n    {\n      \"address\": \"00ae9f94\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x40],0x3ac86b5\"\n    },\n    {\n      \"address\": \"00ae9f9c\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x10],0x13eb90c\"\n    },\n    {\n      \"address\": \"00ae9fa4\",\n      \"instruction\": \"XOR EAX,EAX\"\n    },\n    {\n      \"address\": \"00ae9fa6\",\n      \"instruction\": \"LEA ECX,[ESP + 0x14]\"\n    },\n    {\n      \"address\": \"00ae9faa\",\n      \"instruction\": \"XCHG dword ptr [ECX],EAX\"\n    },\n    {\n      \"address\": \"00ae9fac\",\n      \"instruction\": \"MOV EDI,dword ptr [ESI + 0x20]\"\n    },\n    {\n      \"address\": \"00ae9faf\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x10],0x13eb844\"\n    },\n    {\n      \"address\": \"00ae9fb7\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x48],0x0\"\n    },\n    {\n      \"address\": \"00ae9fbf\",\n      \"instruction\": \"MOV EDX,dword ptr [EDI + 0xc]\"\n    },\n    {\n      \"address\": \"00ae9fc2\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x18],EDX\"\n    },\n    {\n      \"address\": \"00ae9fc6\",\n      \"instruction\": \"TEST BL,BL\"\n    },\n    {\n      \"address\": \"00ae9fc8\",\n      \"instruction\": \"JZ 0x00ae9fce\"\n    },\n    {\n      \"address\": \"00ae9fca\",\n      \"instruction\": \"MOV EAX,EBP\"\n    },\n    {\n      \"address\": \"00ae9fcc\",\n      \"instruction\": \"JMP 0x00ae9fed\"\n    },\n    {\n      \"address\": \"00ae9fce\",\n      \"instruction\": \"MOV EAX,dword ptr [EDI + 0x18]\"\n    },\n    {\n      \"address\": \"00ae9fd1\",\n      \"instruction\": \"PUSH EAX\"\n    },\n    {\n      \"address\": \"00ae9fd2\",\n      \"instruction\": \"CALL 0x00b3d300\"\n    },\n    {\n      \"address\": \"00ae9fd7\",\n      \"instruction\": \"MOV ECX,EAX\"\n    },\n    {\n      \"address\": \"00ae9fd9\",\n      \"instruction\": \"CALL 0x00b20750\"\n    },\n    {\n      \"address\": \"00ae9fde\",\n      \"instruction\": \"MOV EAX,dword ptr [EDI + 0x28]\"\n    },\n    {\n      \"address\": \"00ae9fe1\",\n      \"instruction\": \"TEST EAX,EAX\"\n    },\n    {\n      \"address\": \"00ae9fe3\",\n      \"instruction\": \"JNZ 0x00ae9fed\"\n    },\n    {\n      \"address\": \"00ae9fe5\",\n      \"instruction\": \"MOV ECX,dword ptr [EDI + 0x20]\"\n    },\n    {\n      \"address\": \"00ae9fe8\",\n      \"instruction\": \"CALL 0x00bd9bf0\"\n    },\n    {\n      \"address\": \"00ae9fed\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x20],EAX\"\n    },\n    {\n      \"address\": \"00ae9ff1\",\n      \"instruction\": \"MOV EAX,dword ptr [ESI + 0x20]\"\n    },\n    {\n      \"address\": \"00ae9ff4\",\n      \"instruction\": \"MOV ECX,EAX\"\n    },\n    {\n      \"address\": \"00ae9ff6\",\n      \"instruction\": \"TEST BL,BL\"\n    },\n    {\n      \"address\": \"00ae9ff8\",\n      \"instruction\": \"JNZ 0x00ae9ffd\"\n    },\n    {\n      \"address\": \"00ae9ffa\",\n      \"instruction\": \"MOV ECX,dword ptr [EAX + 0x20]\"\n    },\n    {\n      \"address\": \"00ae9ffd\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x28],ECX\"\n    },\n    {\n      \"address\": \"00aea001\",\n      \"instruction\": \"TEST BL,BL\"\n    },\n    {\n      \"address\": \"00aea003\",\n      \"instruction\": \"JZ 0x00aea009\"\n    },\n    {\n      \"address\": \"00aea005\",\n      \"instruction\": \"XOR EAX,EAX\"\n    },\n    {\n      \"address\": \"00aea007\",\n      \"instruction\": \"JMP 0x00aea00c\"\n    },\n    {\n      \"address\": \"00aea009\",\n      \"instruction\": \"MOV EAX,dword ptr [EAX + 0x24]\"\n    },\n    {\n      \"address\": \"00aea00c\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x30],EAX\"\n    },\n    {\n      \"address\": \"00aea010\",\n      \"instruc
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
  "body_end": "00aea166",
  "body_span_bytes": 535,
  "body_start": "00ae9f50",
  "callees": [
    "FUN_00e14c10",
    "FUN_00dd30d0",
    "FUN_00a206f0",
    "FUN_00b20750",
    "FUN_00b32250",
    "FUN_00dd1ca0",
    "FUN_01021090",
    "FUN_00ba9370",
    "FUN_00b3d2a0",
    "FUN_00c35240",
    "FUN_00bd9bf0",
    "Simulator::cSpaceTrading::Get",
    "FUN_00b3d380",
    "Simulator::cToolManager::Get",
    "Simulator::cGameNounManager::Get",
    "FUN_01021300",
    "FUN_00ae8ea0",
    "FUN_00ba6d80",
    "FUN_00ae0930",
    "FUN_00435ed0",
    "App::IAppSystem::Get",
    "FUN_00421cf0",
    "FUN_00b3d300"
  ],
  "callers": [
    "FUN_00aeb7b0",
    "FUN_00aeb890",
    "FUN_00aea210",
    "FUN_00aeb090"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00ae9f50",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "uVar13",
      "storage": "Stack[-0x94]:4",
      "type": "undefined4"
    },
    {
      "name": "uVar11",
      "storage": "Stack[-0x9c]:4",
      "type": "undefined4"
    },
    {
      "name": "uVar12",
      "storage": "Stack[-0x98]:4",
      "type": "undefined4"
    },
    {
      "name": "bVar9",
      "storage": "register:00000206:1",
      "type": "bool"
    },
    {
      "name": "uVar10",
      "storage": "Stack[-0xa0]:4",
      "type": "undefined4"
    },
    {
      "name": "uStack_14",
      "storage": "Stack[-0x14]:4",
      "type": "undefined4"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int"
    },
    {
      "name": "pvStack_44",
      "storage": "Stack[-0x44]:4",
      "type": "void *"
    },
    {
      "name": "pIStack_1c",
      "storage": "Stack[-0x1c]:4",
      "type": "IAppSystem *"
    },
    {
      "name": "local_80",
      "storage": "Stack[-0x78]:4",
      "type": "undefined1[56]"
    },
    {
      "name": "uVar7",
      "storage": "register:00000000:4",
      "type": "undefined4"
    },
    {
      "name": "pcVar8",
      "storage": "register:00000000:4",
      "type": "cToolManager *"
    },
    {
      "name": "iVar5",
      "storage": "register:00000000:4",
      "type": "int"
    },
    {
      "name": "piVar6",
      "storage": "register:00000000:4",
      "type": "int *"
    },
    {
      "name": "pIVar3",
      "storage": "register:00000000:4",
      "type": "IAppSystem *"
    },
    {
      "name": "pvVar4",
      "storage": "register:00000000:4",
      "type": "void *"
    },
    {
      "name": "pwVar1",
      "storage": "unique:00017200:4",
      "type": "wchar16 *"
    },
    {
      "name": "local_48",
      "storage": "Stack[-0x48]:4",
      "type": "undefined4"
    },
    {
      "name": "pvVar2",
      "storage": "register:00000014:4",
      "type": "void *"
    }
  ],
  "locals_count": 19,
  "mode": "live",
  "name": "FUN_00ae9f50",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x6e9f50",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00ae9f50(void)",
  "size_bytes": 535,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00ae9f50",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 4,
  "xrefs": [
    {
      "from": "00aeb801"
    },
    {
      "from": "00aea210"
    },
    {
      "from": "00aeb906"
    },
    {
      "from": "00aeb099"
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
[
  {
    "anchors": [
      "0x00b3d2a0",
      "0x00b3d300",
      "0x00b5b800",
      "0x01021300",
      "0x01021300",
      "0x00ad23c0",
      "0x00adbca0",
      "0x00ae73e0",
      "0x00ae9590",
      "0x00ae9930",
      "0x00ae9c90",
      "0x00ae9f50",
      "0x00aeb3e0",
      "0x00aeb3e0",
      "0x00aebe90",
      "0x00b25fb0"
    ],
    "conflict_id": "global_root_identities",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
    "resolution_status": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x0067dcc0",
      "0x0067deb0",
      "0x00b3d330",
      "0x00b3d4e0",
      "0x015fd890",
      "0x0167eaf0",
      "0x0167eb60",
      "0x0067dcc0",
      "0x00ad23c0",
      "0x00adbca0",
      "0x00ae73e0",
      "0x00ae9590",
      "0x00ae9930",
      "0x00ae9c90",
      "0x00ae9f50",
      "0x00aeb3e0"
    ],
    "conflict_id": "global_service_publication",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  }
]
```
