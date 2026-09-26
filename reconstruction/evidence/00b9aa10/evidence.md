# Evidence 0x00b9aa10

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `89093bf5e9b6a4166e652703b1c9501552d5b1b10c1d7e1a6adc621e26231857`

## abi

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "abi": {
    "architecture": "x86-32",
    "ordinary_stack_argument_slots": [
      "entry_ESP+0x4",
      "entry_ESP+0x8",
      "entry_ESP+0xc",
      "entry_ESP+0x10"
    ],
    "ordinary_stack_arguments": [
      {
        "ebp_offset": "EBP+0x8",
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
        "ebp_offset": "EBP+0xc",
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
        "ebp_offset": "EBP+0x10",
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
        "ebp_offset": "EBP+0x14",
        "entry_offset": "entry_ESP+0x10",
        "observed": true,
        "ordinal": 4,
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
      "EBP",
      "EBX",
      "EDI",
      "ESI"
    ],
    "stack_arguments": [
      {
        "ebp_offset": "EBP+0x8",
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
        "ebp_offset": "EBP+0xc",
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
        "ebp_offset": "EBP+0x10",
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
        "ebp_offset": "EBP+0x14",
        "entry_offset": "entry_ESP+0x10",
        "observed": true,
        "ordinal": 4,
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
    "unparsed_lines_present: 5 line(s) matched no grammar rule",
    "receiver_not_determinable: ecx_address_taken_without_memory_access",
    "ecx_address_taken_without_memory_access: LEA takes ECX's address without any memory access through it",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_address_taken_without_memory_access), and the convention rule that would apply discriminates on receiver absence"
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
  "content_sha256": "0fc89861faf1dde3a368447776f18d91b06b5a29b98a5263b63347558b4ce705",
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
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0196"
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
        "obs-0035",
        "obs-0036",
        "obs-0112",
        "obs-0164",
        "obs-0188"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "INFERRED",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 4,
        "total_bytes": 16
      }
    },
    {
      "based_on": [
        "obs-0015",
        "obs-0022",
        "obs-0023",
        "obs-0026",
        "obs-0036",
        "obs-0060",
        "obs-0074",
        "obs-0081",
        "obs-0129",
        "obs-0139",
        "obs-0148",
        "obs-0151",
        "obs-0152",
        "obs-0166",
        "obs-0173"
      ],
      "claim": "the register receiver is undetermined: ecx_address_taken_without_memory_access",
      "confidence": "UNKNOWN",
      "id": "R0",
      "value": {
        "reason": "ecx_address_taken_without_memory_access",
        "register": null
      }
    },
    {
      "based_on": [
        "obs-0015",
        "obs-0022",
        "obs-0023",
        "obs-0026",
        "obs-0036",
        "obs-0060",
        "obs-0074",
        "obs-0081",
        "obs-0129",
        "obs-0139",
        "obs-0148",
        "obs-0151",
        "obs-0152",
        "obs-0166",
        "obs-0173"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_address_taken_without_memory_access) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0196"
      ],
      "claim": "entry slot 0 is not written through a pointer",
      "confiden
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
"\n/* WARNING: Enum \"ObjectTYPE\": Some values do not have unique names */\n/* WARNING: Enum \"Names\": Some values do not have unique names */\n\nvoid FUN_00b9aa10(undefined4 param_1,int param_2,uint param_3,undefined4 param_4)\n\n{\n  float fVar1;\n  char cVar2;\n  bool bVar3;\n  undefined *puVar4;\n  int iVar5;\n  int iVar6;\n  uint uVar7;\n  uint uVar8;\n  float10 fVar9;\n  float10 fVar10;\n  float10 fVar11;\n  undefined1 **ppuVar12;\n  undefined4 uVar13;\n  undefined4 uVar14;\n  undefined4 uVar15;\n  bool local_e0;\n  bool local_df;\n  bool local_de;\n  char local_dd;\n  float local_dc;\n  char local_d5;\n  float local_d4;\n  uint *local_d0;\n  size_t local_cc;\n  uint local_c8;\n  cSpeciesManager *local_c4;\n  undefined4 local_c0;\n  uint local_bc;\n  undefined4 local_b8;\n  double local_b4;\n  undefined4 local_ac;\n  undefined1 local_a8 [12];\n  float local_9c;\n  uint local_98;\n  undefined4 local_94;\n  undefined4 local_90;\n  undefined4 local_8c;\n  float local_88;\n  double local_84;\n  float local_7c;\n  float local_78;\n  uint local_74;\n  undefined4 local_70;\n  undefined4 local_6c;\n  undefined4 local_68;\n  undefined1 *local_64;\n  undefined1 *local_60;\n  int *local_5c;\n  undefined4 local_50;\n  undefined1 local_4c [20];\n  int local_38;\n  int local_34;\n  int local_30 [2];\n  float local_28 [6];\n  undefined1 local_10 [12];\n  \n  FUN_00b3d300();\n  Simulator__cGameInputManager__Get();\n  local_c4 = Editors__cSpeciesManager__Get();\n  FUN_004df420();\n  puVar4 = (undefined *)FUN_00b5b800();\n  local_dd = puVar4 == &DAT_01654c01;\n  iVar5 = FUN_0067cb40();\n  if (iVar5 != 0) {\n    local_64 = local_4c;\n    local_5c = &local_38;\n    local_50 = 0;\n    local_60 = local_64;\n    FUN_004cd3c0(1);\n    fVar9 = (float10)FUN_00b7e390();\n    local_78 = (float)fVar9;\n    local_bc = 0;\n    if (param_3 != 0) {\n      do {\n        local_b8 = *(undefined4 *)(param_2 + local_bc * 4);\n        iVar5 = FUN_004e0050(local_b8,0);\n        if (iVar5 != 0) {\n          iVar6 = FUN_004dfff0(&local_64,iVar5,1,0,0);\n          if (iVar6 < 1) {\n            uVar15 = 1;\n            uVar14 = 0;\n            uVar13 = 1;\n            ppuVar12 = &local_64;\n            iVar6 = iVar5;\n            Editors__cSpeciesManager__Get();\n            iVar6 = FUN_004dfff0(ppuVar12,iVar6,uVar13,uVar14,uVar15);\n            if (iVar6 < 1) goto LAB_00b9b056;\n          }\n          local_b4 = (double)*(float *)(iVar5 + 0x300);\n          local_84 = (double)*(float *)(iVar5 + 0x304);\n          fVar10 = (float10)FUN_009360d0();\n          fVar9 = (float10)local_84;\n          fVar11 = (float10)local_b4;\n          fVar10 = fVar10 * (fVar9 - fVar11) + fVar11;\n          if ((fVar10 < fVar9) && (fVar9 = fVar10, fVar10 < fVar11)) {\n            fVar9 = fVar11;\n          }\n          local_d4 = (float)fVar9;\n          fVar1 = ROUND(local_d4);\n          local_b4 = (double)CONCAT44(local_b4._4_4_,(int)fVar1);\n          fVar9 = (float10)FUN_004e1c70(*(undefined4 *)(iVar5 + 0x43c),0x4934caca,0x3f800000);\n          local_dc = (float)fVar9;\n          FUN_00b938d0(local_28,*(undefined4 *)(iVar5 + 0x43c),0x1ee4cafd,DAT_0156bfc4,DAT_0156bfc8,\n                       DAT_0156bfcc);\n          local_dc = local_28[DAT_0156c060] * local_dc;\n          fVar9 = (float10)FUN_009360d0();\n          local_d4 = (float)fVar9;\n          if ((0 < (int)fVar1) && (local_d4 <= local_dc)) {\n            uVar7 = DAT_016895a4 + 1;\n            DAT_016895a4 = uVar7;\n            local_c8 = uVar7;\n            FUN_00b938d0(local_28 + 3,*(undefined4 *)(iVar5 + 0x43c),0x6b152f47,DAT_01688890,\n                         DAT_01688894,DAT_01688898);\n            local_9c = local_28[DAT_0156c060 + 3];\n            if (0 < (int)local_9c) {\n              uVar7 = DAT_016895a4 % (uint)(int)local_9c + 1;\n              local_c8 = uVar7;\n            }\n            local_88 = *(float *)(iVar5 + 0x2e0) + local_78;\n            local_d5 = 1 < (uint)(*(int *)(iVar5 + 0x3a0) - *(int *)(iVar5 + 0x39c) >> 2);\n            local_7c = *(float *)(iVar5 + 0x2e4) + local_78;\n            local_de = true;\n            local_df = (bool)local_dd;\n            local_e0 = false;\n            App__Property__GetBool(*(PropertyList **)(iVar5 + 0x43c),0x80cd38c6,&local_de);\n            App__Property__GetBool(*(PropertyList **)(iVar5 + 0x43c),0x3a509d24,&local_df);\n            App__Property__GetBool(*(PropertyList **)(iVar5 + 0x43c),0x835025da,&local_e0);\n            local_dc = 0.0;\n            if (local_de != false) {\n              local_dc = 2.24208e-44;\n            }\n            if (local_df != false) {\n              local_dc = (float)((uint)local_dc | 0x20);\n            }\n            if (local_e0 != false) {\n              local_dc = (float)((uint)local_dc | 0x40);\n            }\n            if (0 < (int)local_b4._0_4_) {\n              local_d4 = local_b4._0_4_;\n              iVar6 = 0;\n              while( true ) {\n                if (local_d5 == '\\0') {\n                  local_c0 = 0x42c80000;\n                  local_ac = 0x447a0000;\n                }\n                else {\n                  local_c0 = *(undefined4 *)(*(int *)(iVar5 + 0x39c) + iVar6 * 4);\n                  local_ac = *(undefined4 *)(*(int *)(iVar5 + 0x39c) + iVar6 * 4 + 4);\n                }\n                local_b4 = (double)CONCAT44(local_b4._4_4_,\n                                            (iVar6 + 2U) %\n                                            (uint)(*(int *)(iVar5 + 0x3a0) - *(int *)(iVar5 + 0x39c)\n                                                  >> 2));\n                cVar2 = FUN_00b97720(local_a8,param_1,*(undefined1 *)(iVar5 + 0x334),local_c0,\n                                     local_ac,*(undefined4 *)(iVar5 + 0x2d4),\n                                     *(undefined4 *)(iVar5 + 0x2d8),*(undefined4 *)(iVar5 + 0x2dc),\n                                     local_88,local_7c,*(undefined4 *)(iVar5 + 0x2e8),\n                                     *(un
[TRUNCATED]
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "original_bytes": 36546,
  "preview": "{\n  \"count\": 430,\n  \"instructions\": [\n    {\n      \"address\": \"00b9aa10\",\n      \"instruction\": \"PUSH EBP\"\n    },\n    {\n      \"address\": \"00b9aa11\",\n      \"instruction\": \"MOV EBP,ESP\"\n    },\n    {\n      \"address\": \"00b9aa13\",\n      \"instruction\": \"AND ESP,0xfffffff8\"\n    },\n    {\n      \"address\": \"00b9aa16\",\n      \"instruction\": \"SUB ESP,0xdc\"\n    },\n    {\n      \"address\": \"00b9aa1c\",\n      \"instruction\": \"PUSH EBX\"\n    },\n    {\n      \"address\": \"00b9aa1d\",\n      \"instruction\": \"PUSH ESI\"\n    },\n    {\n      \"address\": \"00b9aa1e\",\n      \"instruction\": \"PUSH EDI\"\n    },\n    {\n      \"address\": \"00b9aa1f\",\n      \"instruction\": \"CALL 0x00b3d300\"\n    },\n    {\n      \"address\": \"00b9aa24\",\n      \"instruction\": \"CALL 0x00b3d350\"\n    },\n    {\n      \"address\": \"00b9aa29\",\n      \"instruction\": \"MOV ESI,EAX\"\n    },\n    {\n      \"address\": \"00b9aa2b\",\n      \"instruction\": \"CALL 0x00401090\"\n    },\n    {\n      \"address\": \"00b9aa30\",\n      \"instruction\": \"MOV EBX,EAX\"\n    },\n    {\n      \"address\": \"00b9aa32\",\n      \"instruction\": \"MOV ECX,EBX\"\n    },\n    {\n      \"address\": \"00b9aa34\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x2c],EBX\"\n    },\n    {\n      \"address\": \"00b9aa38\",\n      \"instruction\": \"CALL 0x004df420\"\n    },\n    {\n      \"address\": \"00b9aa3d\",\n      \"instruction\": \"CALL 0x00b5b800\"\n    },\n    {\n      \"address\": \"00b9aa42\",\n      \"instruction\": \"CMP EAX,0x1654c01\"\n    },\n    {\n      \"address\": \"00b9aa47\",\n      \"instruction\": \"SETZ byte ptr [ESP + 0x13]\"\n    },\n    {\n      \"address\": \"00b9aa4c\",\n      \"instruction\": \"CALL 0x0067cb40\"\n    },\n    {\n      \"address\": \"00b9aa51\",\n      \"instruction\": \"TEST EAX,EAX\"\n    },\n    {\n      \"address\": \"00b9aa53\",\n      \"instruction\": \"JZ 0x00b9b082\"\n    },\n    {\n      \"address\": \"00b9aa59\",\n      \"instruction\": \"LEA EAX,[ESP + 0xa4]\"\n    },\n    {\n      \"address\": \"00b9aa60\",\n      \"instruction\": \"MOV ECX,EAX\"\n    },\n    {\n      \"address\": \"00b9aa62\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x90],ECX\"\n    },\n    {\n      \"address\": \"00b9aa69\",\n      \"instruction\": \"LEA EDX,[ESP + 0xb8]\"\n    },\n    {\n      \"address\": \"00b9aa70\",\n      \"instruction\": \"PUSH 0x1\"\n    },\n    {\n      \"address\": \"00b9aa72\",\n      \"instruction\": \"LEA ECX,[ESP + 0x90]\"\n    },\n    {\n      \"address\": \"00b9aa79\",\n      \"instruction\": \"MOV dword ptr [ESP + 0xa4],0x0\"\n    },\n    {\n      \"address\": \"00b9aa84\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x90],EAX\"\n    },\n    {\n      \"address\": \"00b9aa8b\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x98],EDX\"\n    },\n    {\n      \"address\": \"00b9aa92\",\n      \"instruction\": \"CALL 0x004cd3c0\"\n    },\n    {\n      \"address\": \"00b9aa97\",\n      \"instruction\": \"MOV ECX,ESI\"\n    },\n    {\n      \"address\": \"00b9aa99\",\n      \"instruction\": \"CALL 0x00b7e390\"\n    },\n    {\n      \"address\": \"00b9aa9e\",\n      \"instruction\": \"FSTP float ptr [ESP + 0x78]\"\n    },\n    {\n      \"address\": \"00b9aaa2\",\n      \"instruction\": \"XOR EAX,EAX\"\n    },\n    {\n      \"address\": \"00b9aaa4\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x34],EAX\"\n    },\n    {\n      \"address\": \"00b9aaa8\",\n      \"instruction\": \"CMP dword ptr [EBP + 0x10],EAX\"\n    },\n    {\n      \"address\": \"00b9aaab\",\n      \"instruction\": \"JBE 0x00b9b068\"\n    },\n    {\n      \"address\": \"00b9aab1\",\n      \"instruction\": \"MOV ECX,dword ptr [EBP + 0xc]\"\n    },\n    {\n      \"address\": \"00b9aab4\",\n      \"instruction\": \"MOV EAX,dword ptr [ECX + EAX*0x4]\"\n    },\n    {\n      \"address\": \"00b9aab7\",\n      \"instruction\": \"PUSH 0x0\"\n    },\n    {\n      \"address\": \"00b9aab9\",\n      \"instruction\": \"PUSH EAX\"\n    },\n    {\n      \"address\": \"00b9aaba\",\n      \"instruction\": \"MOV ECX,EBX\"\n    },\n    {\n      \"address\": \"00b9aabc\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x40],EAX\"\n    },\n    {\n      \"address\": \"00b9aac0\",\n      \"instruction\": \"CALL 0x004e0050\"\n    },\n    {\n      \"address\": \"00b9aac5\",\n      \"instruction\": \"MOV ESI,EAX\"\n    },\n    {\n      \"address\": \"00b9aac7\",\n      \"instruction\": \"TEST ESI,ESI\"\n    },\n    {\n      \"address\": \"00b9aac9\",\n      \"instruction\": \"JZ 0x00b9b056\"\n    },\n    {\n      \"address\": \"00b9aacf\",\n      \"instruction\": \"PUSH 0x0\"\n    },\n    {\n      \"address\": \"00b9aad1\",\n      \"instruction\": \"PUSH 0x0\"\n    },\n    {\n      \"address\": \"00b9aad3\",\n      \"instruction\": \"PUSH 0x1\"\n    },\n    {\n      \"address\": \"00b9aad5\",\n      \"instruction\": \"PUSH ESI\"\n    },\n    {\n      \"address\": \"00b9aad6\",\n      \"instruction\": \"LEA EDX,[ESP + 0x9c]\"\n    },\n    {\n      \"address\": \"00b9aadd\",\n      \"instruction\": \"PUSH EDX\"\n    },\n    {\n      \"address\": \"00b9aade\",\n      \"instruction\": \"MOV ECX,EBX\"\n    },\n    {\n      \"address\": \"00b9aae0\",\n      \"instruction\": \"CALL 0x004dfff0\"\n    },\n    {\n      \"address\": \"00b9aae5\",\n      \"instruction\": \"TEST EAX,EAX\"\n    },\n    {\n      \"address\": \"00b9aae7\",\n      \"instruction\": \"JG 0x00b9ab0c\"\n    },\n    {\n      \"address\": \"00b9aae9\",\n      \"instruction\": \"PUSH 0x1\"\n    },\n    {\n      \"address\": \"00b9aaeb\",\n      \"instruction\": \"PUSH 0x0\"\n    },\n    {\n      \"address\": \"00b9aaed\",\n      \"instruction\": \"PUSH 0x1\"\n    },\n    {\n      \"address\": \"00b9aaef\",\n      \"instruction\": \"LEA EAX,[ESP + 0x98]\"\n    },\n    {\n      \"address\": \"00b9aaf6\",\n      \"instruction\": \"PUSH ESI\"\n    },\n    {\n      \"addr
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
  "body_end": "00b9b088",
  "body_span_bytes": 1657,
  "body_start": "00b9aa10",
  "callees": [
    "FUN_00b9aa10",
    "App::Property::GetBool",
    "FUN_00b90ea0",
    "Simulator::cGameInputManager::Get",
    "FUN_004dfff0",
    "FUN_009360d0",
    "FUN_00b906a0",
    "FUN_00a68fb0",
    "FUN_00b5b800",
    "FUN_004cd3c0",
    "FUN_00b98230",
    "FUN_00b97720",
    "FUN_00b93f40",
    "FUN_0067cb40",
    "FUN_00b938d0",
    "FUN_004e0050",
    "FUN_00f47380",
    "FUN_00b970c0",
    "FUN_00b7e390",
    "FUN_00b3d300",
    "App::Property::GetArrayUInt32",
    "FUN_00b96220",
    "FUN_00b965d0",
    "FUN_004df420",
    "FUN_004e1c70",
    "Editors::cSpeciesManager::Get",
    "FUN_00b9b090"
  ],
  "callers": [
    "FUN_00b9d6d0",
    "FUN_00b9aa10",
    "FUN_00b9caa0",
    "FUN_00b9c830",
    "FUN_00b9b090",
    "FUN_00b9d820",
    "FUN_00ba1590"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00b9aa10",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_df",
      "storage": "Stack[-0xdf]:1",
      "type": "bool"
    },
    {
      "name": "local_e0",
      "storage": "Stack[-0xe0]:1",
      "type": "bool"
    },
    {
      "name": "local_dd",
      "storage": "Stack[-0xdd]:1",
      "type": "char"
    },
    {
      "name": "local_de",
      "storage": "Stack[-0xde]:1",
      "type": "bool"
    },
    {
      "name": "local_d5",
      "storage": "Stack[-0xd5]:1",
      "type": "char"
    },
    {
      "name": "local_dc",
      "storage": "Stack[-0xdc]:4",
      "type": "float"
    },
    {
      "name": "local_d0",
      "storage": "Stack[-0xd0]:4",
      "type": "uint *"
    },
    {
      "name": "local_d4",
      "storage": "Stack[-0xd4]:4",
      "type": "float"
    },
    {
      "name": "local_c8",
      "storage": "Stack[-0xc8]:4",
      "type": "uint"
    },
    {
      "name": "local_cc",
      "storage": "Stack[-0xcc]:4",
      "type": "size_t"
    },
    {
      "name": "local_c0",
      "storage": "Stack[-0xc0]:4",
      "type": "undefined4"
    },
    {
      "name": "local_c4",
      "storage": "Stack[-0xc4]:4",
      "type": "cSpeciesManager *"
    },
    {
      "name": "local_b8",
      "storage": "Stack[-0xb8]:4",
      "type": "undefined4"
    },
    {
      "name": "local_bc",
      "storage": "Stack[-0xbc]:4",
      "type": "uint"
    },
    {
      "name": "local_ac",
      "storage": "Stack[-0xac]:4",
      "type": "undefined4"
    },
    {
      "name": "local_b4",
      "storage": "Stack[-0xb4]:8",
      "type": "double"
    },
    {
      "name": "local_9c",
      "storage": "Stack[-0x9c]:4",
      "type": "float"
    },
    {
      "name": "local_a8",
      "storage": "",
      "type": "undefined1[12]"
    },
    {
      "name": "local_94",
      "storage": "Stack[-0x94]:4",
      "type": "undefined4"
    },
    {
      "name": "local_98",
      "storage": "Stack[-0x98]:4",
      "type": "uint"
    },
    {
      "name": "local_8c",
      "storage": "Stack[-0x8c]:4",
      "type": "undefined4"
    },
    {
      "name": "local_90",
      "storage": "Stack[-0x90]:4",
      "type": "undefined4"
    },
    {
      "name": "local_84",
      "storage": "Stack[-0x84]:8",
      "type": "double"
    },
    {
      "name": "local_88",
      "storage": "Stack[-0x88]:4",
      "type": "float"
    },
    {
      "name": "local_78",
      "storage": "Stack[-0x78]:4",
      "type": "float"
    },
    {
      "name": "local_7c",
      "storage": "Stack[-0x7c]:4",
      "type": "float"
    },
    {
      "name": "local_70",
      "storage": "Stack[-0x70]:4",
      "type": "undefined4"
    },
    {
      "name": "local_74",
      "storage": "Stack[-0x74]:4",
      "type": "uint"
    },
    {
      "name": "local_68",
      "storage": "Stack[-0x68]:4",
      "type": "undefined4"
    },
    {
      "name": "local_6c",
      "storage": "Stack[-0x6c]:4",
      "type": "undefined4"
    },
    {
      "name": "local_60",
      "storage": "Stack[-0x60]:4",
      "type": "undefined1 *"
    },
    {
      "name": "local_64",
      "storage": "Stack[-0x64]:4",
      "type": "undefined1 *"
    },
    {
      "name": "local_50",
      "storage": "Stack[-0x50]:4",
      "type": "undefined4"
    },
    {
      "name": "local_5c",
      "storage": "Stack[-0x5c]:4",
      "type": "int *"
    },
    {
      "name": "local_38",
      "storage": "Stack[-0x38]:4",
      "type": "int"
    },
    {
      "name": "local_4c",
      "storage": "",
      "type": "undefined1[20]"
    },
    {
      "name": "local_30",
      "storage": "Stack[-0x30]:4",
      "type": "int[2]"
    },
    {
      "name": "local_34",
      "storage": "Stack[-0x34]:4",
      "type": "int"
    },
    {
      "name": "local_28",
      "storage": "",
      "type": "float[6]"
    },
    {
      "name": "local_10",
      "storage": "",
      "type": "undefined1[12]"
    },
    {
      "name": "ppuVar12",
      "storage": "Stack[-0x104]:4",
      "type": "undefined1 * *"
    },
    {
      "name": "fVar11",
      "storage": "register:00001100:10",
      "type": "float10"
    },
    {
      "name": "fVar10",
      "storage": "register:00001100:10",
      "type": "float10"
    },
    {
      "name": "fVar9",
      "storage": "register:00001100:10",
      "type": "float10"
    },
    {
      "name": "uVar15",
      "storage": "Stack[-0xf4]:4",
      "type": "undefined4"
    },
    {
      "name": "uVar14",
      "storage": "Stack[-0xf8]:4",
      "type": "undefined4"
    },
    {
      "name": "uVar13",
      "storage": "Stack[-0xfc]:4",
      "type": "undefined4"
    },
    {
      "name": "
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
