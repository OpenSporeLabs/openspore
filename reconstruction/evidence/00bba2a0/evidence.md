# Evidence 0x00bba2a0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `c27ed8c2d47ecaf0292f9a9ddd10642402db9db4dc162b78f4f8ea0068504f07`

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
      "entry_ESP+0x4",
      "entry_ESP+0x8",
      "entry_ESP+0xc",
      "entry_ESP+0x10",
      "entry_ESP+0x14",
      "entry_ESP+0x18",
      "entry_ESP+0x1c",
      "entry_ESP+0x20"
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
        "entry_offset": "entry_ESP+0x10",
        "observed": true,
        "ordinal": 4,
        "read": false,
        "size_inferred": true,
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
        "size_inferred": true,
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
        "size_inferred": false,
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
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
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
        "entry_offset": "entry_ESP+0x10",
        "observed": true,
        "ordinal": 4,
        "read": false,
        "size_inferred": true,
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
        "size_inferred": true,
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
        "size_inferred": false,
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
      }
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -76, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate",
    "side": "caller"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "59cd60af6991d18d9d552f046cc2d062be07baee3b0b5d821daf651f82abcc4a",
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
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0013",
        "obs-0068",
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
        "obs-0015",
        "obs-0019",
        "obs-0020",
        "obs-0021",
        "obs-0024",
        "obs-0027",
        "obs-0029",
        "
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
"\n/* WARNING: Enum \"ObjectTYPE\": Some values do not have unique names */\n/* WARNING: Enum \"Names\": Some values do not have unique names */\n\nvoid __fastcall cStarRecord__ctor(int param_1)\n\n{\n  char cVar1;\n  intrusive_ptr<Simulator::cPlanet> *unaff_EBX;\n  int iVar2;\n  cPlanetRecord *unaff_EBP;\n  int iVar3;\n  int iVar4;\n  ISimulatorStrategy__vftable **ppIVar5;\n  cStarManager *this;\n  undefined4 uVar6;\n  undefined4 local_2c;\n  int local_24;\n  int local_20;\n  int local_14;\n  ISimulatorStrategy__vftable *local_10;\n  IVirtual__vftable *local_c;\n  undefined1 *local_8;\n  \n  iVar2 = *(int *)(param_1 + 0x4c);\n  iVar4 = 0;\n  local_24 = 0;\n  if (iVar2 == 2) {\n    local_2c = 0x876201aa;\n  }\n  else if (iVar2 == 4) {\n    local_2c = 0xefc33700;\n  }\n  else {\n    if (iVar2 != 5) {\n      *(undefined4 *)(param_1 + 0x78) = 0;\n      *(undefined4 *)(param_1 + 0x7c) = 0;\n      *(undefined4 *)(param_1 + 0x74) = 0;\n      *(undefined4 *)(param_1 + 0x80) = 0;\n      return;\n    }\n    uVar6 = *(undefined4 *)(param_1 + 0x54);\n    local_2c = 0xfc5a17bc;\n    FUN_00b3d2a0(uVar6);\n    local_24 = FUN_00ba9370(uVar6);\n  }\n  local_20 = 100;\n  iVar2 = 0;\n  iVar3 = 0;\n  local_14 = 0;\n  Simulator__cPlanetModel__Get();\n  while (((iVar2 == 0 ||\n          (((iVar2 == *(int *)(param_1 + 0x74) && (iVar3 == *(int *)(param_1 + 0x78))) &&\n           (local_14 == *(int *)(param_1 + 0x7c))))) && (local_20 = local_20 + -1, -1 < local_20)))\n  {\n    if (local_24 == 0) {\n      iVar4 = FUN_00ac10a0(local_2c);\n    }\n    else {\n      iVar4 = FUN_00ac1190(*(undefined4 *)(local_24 + 0x58));\n    }\n    if (iVar4 == 0) goto LAB_00bba410;\n    local_10 = (ISimulatorStrategy__vftable *)&DAT_01667bac;\n    local_c = (IVirtual__vftable *)&DAT_01667bac;\n    local_8 = &DAT_01667bae;\n    FUN_004da330(&local_10);\n    ppIVar5 = &local_10;\n    FUN_00b3d2a0(ppIVar5);\n    cVar1 = FUN_00baf5d0(ppIVar5);\n    if (cVar1 == '\\0') {\n      this = (cStarManager *)&local_10;\n      FUN_00b3d2a0();\n      Simulator__cStarManager__RecordToPlanet(this,unaff_EBP,unaff_EBX);\n      local_14 = *(int *)(iVar4 + 0x50c);\n      iVar2 = *(int *)(iVar4 + 0x504);\n      iVar3 = *(int *)(iVar4 + 0x508);\n    }\n    if ((2 < (int)((int)local_8 - (int)local_10 & 0xfffffffeU)) &&\n       (local_10 != (ISimulatorStrategy__vftable *)0x0)) {\n      FUN_00f47380(local_10);\n    }\n  }\n  if (iVar4 != 0) goto LAB_00bba466;\nLAB_00bba410:\n  do {\n    if ((iVar2 != 0) &&\n       (((iVar2 != *(int *)(param_1 + 0x74) || (iVar3 != *(int *)(param_1 + 0x78))) ||\n        (local_14 != *(int *)(param_1 + 0x7c))))) {\n      if (iVar4 != 0) {\nLAB_00bba466:\n        *(int *)(param_1 + 0x74) = iVar2;\n        *(int *)(param_1 + 0x78) = iVar3;\n        *(int *)(param_1 + 0x80) = iVar4;\n        *(int *)(param_1 + 0x7c) = local_14;\n        if (*(int *)(param_1 + 0x4c) != 5) {\n          return;\n        }\n        if (local_24 == 0) {\n          return;\n        }\n        FUN_00c33690(iVar4);\n        return;\n      }\nLAB_00bba495:\n      *(undefined4 *)(param_1 + 0x78) = 0;\n      *(undefined4 *)(param_1 + 0x7c) = 0;\n      *(undefined4 *)(param_1 + 0x74) = 0;\n      *(undefined4 *)(param_1 + 0x80) = 0;\n      return;\n    }\n    if (local_24 == 0) {\n      iVar4 = FUN_00ac10a0(local_2c);\n    }\n    else {\n      iVar4 = FUN_00ac1190(*(undefined4 *)(local_24 + 0x58));\n    }\n    if (iVar4 == 0) goto LAB_00bba495;\n    local_14 = *(int *)(iVar4 + 0x50c);\n    iVar2 = *(int *)(iVar4 + 0x504);\n    iVar3 = *(int *)(iVar4 + 0x508);\n  } while( true );\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "original_bytes": 13976,
  "preview": "{\n  \"count\": 166,\n  \"instructions\": [\n    {\n      \"address\": \"00bba2a0\",\n      \"instruction\": \"SUB ESP,0x2c\"\n    },\n    {\n      \"address\": \"00bba2a3\",\n      \"instruction\": \"PUSH ESI\"\n    },\n    {\n      \"address\": \"00bba2a4\",\n      \"instruction\": \"PUSH EDI\"\n    },\n    {\n      \"address\": \"00bba2a5\",\n      \"instruction\": \"MOV EDI,ECX\"\n    },\n    {\n      \"address\": \"00bba2a7\",\n      \"instruction\": \"MOV EAX,dword ptr [EDI + 0x4c]\"\n    },\n    {\n      \"address\": \"00bba2aa\",\n      \"instruction\": \"XOR ESI,ESI\"\n    },\n    {\n      \"address\": \"00bba2ac\",\n      \"instruction\": \"SUB EAX,0x2\"\n    },\n    {\n      \"address\": \"00bba2af\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x10],ESI\"\n    },\n    {\n      \"address\": \"00bba2b3\",\n      \"instruction\": \"JZ 0x00bba2fc\"\n    },\n    {\n      \"address\": \"00bba2b5\",\n      \"instruction\": \"SUB EAX,0x2\"\n    },\n    {\n      \"address\": \"00bba2b8\",\n      \"instruction\": \"JZ 0x00bba2f2\"\n    },\n    {\n      \"address\": \"00bba2ba\",\n      \"instruction\": \"SUB EAX,0x1\"\n    },\n    {\n      \"address\": \"00bba2bd\",\n      \"instruction\": \"JZ 0x00bba2d4\"\n    },\n    {\n      \"address\": \"00bba2bf\",\n      \"instruction\": \"MOV dword ptr [EDI + 0x78],ESI\"\n    },\n    {\n      \"address\": \"00bba2c2\",\n      \"instruction\": \"MOV dword ptr [EDI + 0x7c],ESI\"\n    },\n    {\n      \"address\": \"00bba2c5\",\n      \"instruction\": \"MOV dword ptr [EDI + 0x74],ESI\"\n    },\n    {\n      \"address\": \"00bba2c8\",\n      \"instruction\": \"MOV dword ptr [EDI + 0x80],ESI\"\n    },\n    {\n      \"address\": \"00bba2ce\",\n      \"instruction\": \"POP EDI\"\n    },\n    {\n      \"address\": \"00bba2cf\",\n      \"instruction\": \"POP ESI\"\n    },\n    {\n      \"address\": \"00bba2d0\",\n      \"instruction\": \"ADD ESP,0x2c\"\n    },\n    {\n      \"address\": \"00bba2d3\",\n      \"instruction\": \"RET\"\n    },\n    {\n      \"address\": \"00bba2d4\",\n      \"instruction\": \"MOV EAX,dword ptr [EDI + 0x54]\"\n    },\n    {\n      \"address\": \"00bba2d7\",\n      \"instruction\": \"PUSH EAX\"\n    },\n    {\n      \"address\": \"00bba2d8\",\n      \"instruction\": \"MOV dword ptr [ESP + 0xc],0xfc5a17bc\"\n    },\n    {\n      \"address\": \"00bba2e0\",\n      \"instruction\": \"CALL 0x00b3d2a0\"\n    },\n    {\n      \"address\": \"00bba2e5\",\n      \"instruction\": \"MOV ECX,EAX\"\n    },\n    {\n      \"address\": \"00bba2e7\",\n      \"instruction\": \"CALL 0x00ba9370\"\n    },\n    {\n      \"address\": \"00bba2ec\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x10],EAX\"\n    },\n    {\n      \"address\": \"00bba2f0\",\n      \"instruction\": \"JMP 0x00bba304\"\n    },\n    {\n      \"address\": \"00bba2f2\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x8],0xefc33700\"\n    },\n    {\n      \"address\": \"00bba2fa\",\n      \"instruction\": \"JMP 0x00bba304\"\n    },\n    {\n      \"address\": \"00bba2fc\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x8],0x876201aa\"\n    },\n    {\n      \"address\": \"00bba304\",\n      \"instruction\": \"PUSH EBX\"\n    },\n    {\n      \"address\": \"00bba305\",\n      \"instruction\": \"PUSH EBP\"\n    },\n    {\n      \"address\": \"00bba306\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x1c],0x64\"\n    },\n    {\n      \"address\": \"00bba30e\",\n      \"instruction\": \"XOR EBX,EBX\"\n    },\n    {\n      \"address\": \"00bba310\",\n      \"instruction\": \"XOR EBP,EBP\"\n    },\n    {\n      \"address\": \"00bba312\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x28],ESI\"\n    },\n    {\n      \"address\": \"00bba316\",\n      \"instruction\": \"CALL 0x00b3d450\"\n    },\n    {\n      \"address\": \"00bba31b\",\n      \"instruction\": \"MOV ECX,EAX\"\n    },\n    {\n      \"address\": \"00bba31d\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x14],ECX\"\n    },\n    {\n      \"address\": \"00bba321\",\n      \"instruction\": \"JMP 0x00bba327\"\n    },\n    {\n      \"address\": \"00bba323\",\n      \"instruction\": \"MOV ECX,dword ptr [ESP + 0x14]\"\n    },\n    {\n      \"address\": \"00bba327\",\n      \"instruction\": \"TEST EBX,EBX\"\n    },\n    {\n      \"address\": \"00bba329\",\n      \"instruction\": \"JZ 0x00bba34a\"\n    },\n    {\n      \"address\": \"00bba32b\",\n      \"instruction\": \"CMP EBX,dword ptr [EDI + 0x74]\"\n    },\n    {\n      \"address\": \"00bba32e\",\n      \"instruction\": \"JNZ 0x00bba405\"\n    },\n    {\n      \"address\": \"00bba334\",\n      \"instruction\": \"CMP EBP,dword ptr [EDI + 0x78]\"\n    },\n    {\n      \"address\": \"00bba337\",\n      \"instruction\": \"JNZ 0x00bba405\"\n    },\n    {\n      \"address\": \"00bba33d\",\n      \"instruction\": \"MOV EDX,dword ptr [ESP + 0x28]\"\n    },\n    {\n      \"address\": \"00bba341\",\n      \"instruction\": \"CMP EDX,dword ptr [EDI + 0x7c]\"\n    },\n    {\n      \"address\": \"00bba344\",\n      \"instruction\": \"JNZ 0x00bba405\"\n    },\n    {\n      \"address\": \"00bba34a\",\n      \"instruction\": \"SUB dword ptr [ESP + 0x1c],0x1\"\n    },\n    {\n      \"address\": \"00bba34f\",\n      \"instruction\": \"JS 0x00bba405\"\n    },\n    {\n      \"address\": \"00bba355\",\n      \"instruction\": \"MOV EAX,dword ptr [ESP + 0x18]\"\n    },\n    {\n      \"address\": \"00bba359\",\n      \"instruction\": \"TEST EAX,EAX\"\n    },\n    {\n      \"address\": \"00bba35b\",\n      \"instruction\": \"JZ 0x00bba368\"\n    },\n    {\n      \"address\": \"00bba35d\",\n      \"instruction\": \"MOV EAX,dword ptr [EAX + 0x58]\"\n    },\n    {\n      \"address\": \"00bba360\",\n      \"instruction\": \"PUSH EAX\"\n    },\n    {\n      \"address\": \"00bba361\",\n      \"instruction\": \"CALL 0x00ac1190\"\n    },\n    {\n      \"address\": \"00bba366\",\n      \"instruction\": \"JMP 0x00bba372\"\n    },\n    {\n      \"address\": \
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
  "body_end": "00bba4ad",
  "body_span_bytes": 526,
  "body_start": "00bba2a0",
  "callees": [
    "Simulator::cPlanetModel::Get",
    "FUN_00ba9370",
    "FUN_00ac1190",
    "Simulator::cStarManager::RecordToPlanet",
    "FUN_00ac10a0",
    "FUN_004da330",
    "FUN_00baf5d0",
    "FUN_00f47380",
    "FUN_00b3d2a0",
    "FUN_00c33690"
  ],
  "callers": [
    "FUN_00bba500",
    "FUN_00ba7220"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00bba2a0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "iVar4",
      "storage": "register:00000018:4",
      "type": "int"
    },
    {
      "name": "iVar3",
      "storage": "register:00000014:4",
      "type": "int"
    },
    {
      "name": "this",
      "storage": "Stack[-0x40]:4",
      "type": "cStarManager *"
    },
    {
      "name": "ppIVar5",
      "storage": "Stack[-0x40]:4",
      "type": "ISimulatorStrategy__vftable * *"
    },
    {
      "name": "unaff_EBX",
      "storage": "register:0000000c:4",
      "type": "intrusive_ptr<Simulator::cPlanet> *"
    },
    {
      "name": "cVar1",
      "storage": "register:00000000:1",
      "type": "char"
    },
    {
      "name": "unaff_EBP",
      "storage": "register:00000014:4",
      "type": "cPlanetRecord *"
    },
    {
      "name": "iVar2",
      "storage": "register:0000000c:4",
      "type": "int"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int"
    },
    {
      "name": "local_2c",
      "storage": "Stack[-0x2c]:4",
      "type": "undefined4"
    },
    {
      "name": "local_20",
      "storage": "Stack[-0x20]:4",
      "type": "int"
    },
    {
      "name": "local_24",
      "storage": "Stack[-0x24]:4",
      "type": "int"
    },
    {
      "name": "local_10",
      "storage": "Stack[-0x10]:4",
      "type": "ISimulatorStrategy__vftable *"
    },
    {
      "name": "local_14",
      "storage": "Stack[-0x14]:4",
      "type": "int"
    },
    {
      "name": "uVar6",
      "storage": "Stack[-0x38]:4",
      "type": "undefined4"
    },
    {
      "name": "local_8",
      "storage": "Stack[-0x8]:4",
      "type": "undefined1 *"
    },
    {
      "name": "local_c",
      "storage": "Stack[-0xc]:4",
      "type": "IVirtual__vftable *"
    }
  ],
  "locals_count": 17,
  "mode": "live",
  "name": "cStarRecord__ctor",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x7ba2a0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined cStarRecord__ctor(void)",
  "size_bytes": 526,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00bba2a0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 3,
  "xrefs": [
    {
      "from": "00bba51a"
    },
    {
      "from": "00bba552"
    },
    {
      "from": "00ba7259"
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
