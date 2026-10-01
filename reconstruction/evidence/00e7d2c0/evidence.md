# Evidence 0x00e7d2c0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `06836bba98de9e29f0ac5f70b0cf038dbb60dbb3e30c9ceec2c8985d0c6fa3e2`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": null,
  "hidden_this": null,
  "receiver": "NOT CLAIMED, IN EITHER DIRECTION. The record declines to name one: receiver {present null, register null, reason ecx_reassigned_before_deref, confidence UNKNOWN, bounds_only true, offsets [], distinct_offsets 0, written_through 0}. Nothing in this package treats any register as `this`, and no receiver type, class, object size, vtable identity, field or layout is asserted anywhere.",
  "receiver_register": null,
  "ret_form": "RET",
  "return_register": "ST0",
  "return_semantics": "float_or_x87_in_ST0",
  "saved_registers": [
    "EBP",
    "EBX",
    "EDI",
    "ESI"
  ],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "RET"
}
```

## abi_derived

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
      "entry_ESP+0x10",
      "entry_ESP+0x14",
      "entry_ESP+0x18",
      "entry_ESP+0x1c",
      "entry_ESP+0x20",
      "entry_ESP+0x24",
      "entry_ESP+0x28",
      "entry_ESP+0x2c",
      "entry_ESP+0x30",
      "entry_ESP+0x34",
      "entry_ESP+0x3c"
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
        "confidence": "UNKNOWN",
        "entry_offset": "entry_ESP+0x8",
        "observed": true,
        "ordinal": 2,
        "read": false,
        "size_inferred": true,
        "sizes": [
          1,
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
        "entry_offset": "entry_ESP+0x10",
        "observed": true,
        "ordinal": 4,
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
        "size_inferred": true,
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
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x34",
        "observed": true,
        "ordinal": 13,
        "read": false,
        "size_inferred": false,
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
        "confidence": "UNKNOWN",
        "entry_offset": "entry_ESP+0x8",
        "observed": true,
        "ordinal": 2,
        "read": false,
        "size_inferred": true,
        "sizes": [
          1,
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
        "entry_offset": "entry_ESP+0x10",
        "observed": true,
        "ordinal": 4,
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
        "size_inferred": true,
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
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written":
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
"\n/* WARNING: Type propagation algorithm not settling */\n/* WARNING: Enum \"Names\": Some values do not have unique names */\n/* WARNING: Enum \"ObjectTYPE\": Some values do not have unique names */\n\nvoid FUN_00e7d070(int param_1,undefined4 param_2)\n\n{\n  int in_EAX;\n  cCellObjectData *cell;\n  int *piVar1;\n  int *piVar2;\n  int iVar3;\n  int iVar4;\n  undefined4 uVar5;\n  int local_30 [2];\n  int local_28 [10];\n  \n  if (*(int *)(Simulator__Cell__sCellGame + 0x411c) == 0) {\n    return;\n  }\n  cell = (cCellObjectData *)FUN_00b72210(*(int *)(Simulator__Cell__sCellGame + 0x411c));\n  FUN_00743b50();\n  iVar4 = 0;\n  if ((in_EAX != DAT_016b3c14) && (iVar4 = thunk_FUN_00e823a0(), iVar4 != 0)) {\n    if (*(char *)(iVar4 + 0x314) != '\\0') {\n      FUN_00e671c0(cell);\n    }\n    if (*(char *)(iVar4 + 0x315) != '\\0') {\n      FUN_00e77d50(param_2);\n    }\n  }\n  iVar3 = cell->mHealthPoints;\n  piVar2 = &cell->mHealthPoints;\n  if (iVar3 < 6) {\n    if (iVar4 == 0) {\n      if (*(int *)(Simulator__Cell__sCellGame + 0x411c) == cell->mObjectPoolIndex) {\n        Simulator__Cell__cCellUI__ShowHealthRollover(cell,iVar3);\n      }\n      *piVar2 = *piVar2 + 2;\n    }\n    else if (0 < *(int *)(iVar4 + 0x310)) {\n      if (*(int *)(Simulator__Cell__sCellGame + 0x411c) == cell->mObjectPoolIndex) {\n        Simulator__Cell__cCellUI__ShowHealthRollover(cell,iVar3);\n      }\n      if (*(int *)(*(int *)(Simulator__Cell__sCellGame + 0x5190) + 0x7c) == 0) {\n        *piVar2 = *piVar2 + *(int *)(iVar4 + 0x310) * 2;\n      }\n      else {\n        *piVar2 = *piVar2 + *(int *)(iVar4 + 0x310);\n      }\n    }\n  }\n  local_28[0] = 6;\n  piVar1 = piVar2;\n  if (5 < *piVar2) {\n    piVar1 = local_28;\n  }\n  *piVar2 = *piVar1;\n  if (iVar4 == 0) {\n    local_28[0] = 10;\n    iVar3 = local_28[0];\n  }\n  else {\n    iVar3 = *(int *)(iVar4 + 0x30c);\n    if (*(int *)(iVar4 + 0x30c) == 0) {\n      FUN_00e82130();\n      return;\n    }\n  }\n  local_28[0] = iVar3;\n  *(undefined1 *)(*(int *)(Simulator__Cell__sCellGame + 0x5190) + 0xe1) = 1;\n  FUN_00e51650();\n  iVar3 = *(int *)(Simulator__Cell__sCellGame + 0x5190);\n  if ((*(char *)(iVar3 + 0x69) == '\\0') && (0x95 < *(int *)(iVar3 + 0x1c))) {\n    *(undefined4 *)(Simulator__Cell__sCellGame + 0x51d0) = 0x40c00000;\n    *(undefined1 *)(iVar3 + 0x69) = 1;\n  }\n  iVar3 = *(int *)(Simulator__Cell__sCellGame + 0x5190);\n  if (*(int *)(iVar3 + 0x80) == 1) {\n    piVar2 = (int *)(iVar3 + 0x84);\n    local_30[0] = 5;\n    if (*(int *)(iVar3 + 0x84) != 5) {\n      iVar3 = *(int *)(iVar3 + 0x84) + 1;\n      *piVar2 = iVar3;\n      piVar1 = local_30;\n      if (iVar3 < 6) {\n        piVar1 = piVar2;\n      }\n      iVar3 = *piVar1;\n      *piVar2 = iVar3;\n      if (iVar3 == 5) {\n        FUN_00e53460();\n      }\n    }\n  }\n  if (iVar4 == 0) {\nLAB_00e7d248:\n    local_30[0] = CONCAT31(local_30[0]._1_3_,1);\n  }\n  else if ((*(byte *)(iVar4 + 0xb0) & 1) == 0) {\nLAB_00e7d26e:\n    local_30[0] = CONCAT31(local_30[0]._1_3_,*(int *)(iVar4 + 0xb4) == 3);\n  }\n  else {\n    if (param_1 != 2) {\n      if (param_1 == 3) goto LAB_00e7d248;\n      if (param_1 != 4) goto LAB_00e7d26e;\n    }\n    local_30[0] = (uint)local_30[0]._1_3_ << 8;\n  }\n  FUN_00e7ce10(local_28[0],local_30[0]);\n  if (iVar4 == 0) {\nLAB_00e7d2b7:\n    piVar2 = local_28 + 1;\n    iVar4 = *(int *)(Simulator__Cell__sCellGame + 0x5190);\n    piVar1 = local_28 + 7;\n    uVar5 = 0x9ef61113;\n  }\n  else {\n    if ((*(byte *)(iVar4 + 0xb0) & 1) == 0) {\nLAB_00e7d2aa:\n      if (*(int *)(iVar4 + 0xb4) == 3) goto LAB_00e7d2b7;\n    }\n    else if (param_1 != 2) {\n      if (param_1 == 3) goto LAB_00e7d2b7;\n      if (param_1 != 4) goto LAB_00e7d2aa;\n    }\n    piVar2 = local_28 + 7;\n    iVar4 = *(int *)(Simulator__Cell__sCellGame + 0x5190);\n    piVar1 = local_28 + 1;\n    uVar5 = 0xac7161b5;\n  }\n  local_28[9] = 0;\n  local_28[8] = 0;\n  local_28[7] = 0;\n  local_28[6] = 0;\n  local_28[5] = 0;\n  local_28[4] = 0;\n  local_28[3] = 0;\n  local_28[2] = 0;\n  local_28[1] = 0;\n  FUN_00e394f0(uVar5,iVar4 + 0x10,piVar1,local_28 + 4,piVar2);\n  FUN_00e82130();\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 224,
  "instructions": [
    {
      "address": "00e7d070",
      "instruction": "MOV ECX,dword ptr [0x016b3c04]"
    },
    {
      "address": "00e7d076",
      "instruction": "SUB ESP,0x30"
    },
    {
      "address": "00e7d079",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00e7d07a",
      "instruction": "MOV EDI,EAX"
    },
    {
      "address": "00e7d07c",
      "instruction": "MOV EAX,dword ptr [ECX + 0x411c]"
    },
    {
      "address": "00e7d082",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00e7d084",
      "instruction": "JZ 0x00e7d35c"
    },
    {
      "address": "00e7d08a",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00e7d08b",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00e7d08c",
      "instruction": "ADD ECX,0x1c"
    },
    {
      "address": "00e7d08f",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00e7d090",
      "instruction": "CALL 0x00b72210"
    },
    {
      "address": "00e7d095",
      "instruction": "LEA ECX,[ESP + 0x10]"
    },
    {
      "address": "00e7d099",
      "instruction": "MOV ESI,EAX"
    },
    {
      "address": "00e7d09b",
      "instruction": "CALL 0x00743b50"
    },
    {
      "address": "00e7d0a0",
      "instruction": "XOR EBP,EBP"
    },
    {
      "address": "00e7d0a2",
      "instruction": "CMP EDI,dword ptr [0x016b3c14]"
    },
    {
      "address": "00e7d0a8",
      "instruction": "JZ 0x00e7d0e9"
    },
    {
      "address": "00e7d0aa",
      "instruction": "LEA EAX,[ESP + 0x10]"
    },
    {
      "address": "00e7d0ae",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00e7d0af",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00e7d0b0",
      "instruction": "CALL 0x00e4cc40"
    },
    {
      "address": "00e7d0b5",
      "instruction": "MOV EBP,EAX"
    },
    {
      "address": "00e7d0b7",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "00e7d0ba",
      "instruction": "TEST EBP,EBP"
    },
    {
      "address": "00e7d0bc",
      "instruction": "JZ 0x00e7d0e9"
    },
    {
      "address": "00e7d0be",
      "instruction": "CMP byte ptr [EBP + 0x314],0x0"
    },
    {
      "address": "00e7d0c5",
      "instruction": "JZ 0x00e7d0d0"
    },
    {
      "address": "00e7d0c7",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00e7d0c8",
      "instruction": "CALL 0x00e671c0"
    },
    {
      "address": "00e7d0cd",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "00e7d0d0",
      "instruction": "CMP byte ptr [EBP + 0x315],0x0"
    },
    {
      "address": "00e7d0d7",
      "instruction": "JZ 0x00e7d0e9"
    },
    {
      "address": "00e7d0d9",
      "instruction": "FLD float ptr [ESP + 0x44]"
    },
    {
      "address": "00e7d0dd",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00e7d0de",
      "instruction": "FSTP float ptr [ESP]"
    },
    {
      "address": "00e7d0e1",
      "instruction": "CALL 0x00e77d50"
    },
    {
      "address": "00e7d0e6",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "00e7d0e9",
      "instruction": "MOV EAX,dword ptr [ESI + 0x244]"
    },
    {
      "address": "00e7d0ef",
      "instruction": "CMP EAX,0x6"
    },
    {
      "address": "00e7d0f2",
      "instruction": "LEA EDI,[ESI + 0x244]"
    },
    {
      "address": "00e7d0f8",
      "instruction": "JGE 0x00e7d165"
    },
    {
      "address": "00e7d0fa",
      "instruction": "TEST EBP,EBP"
    },
    {
      "address": "00e7d0fc",
      "instruction": "JZ 0x00e7d148"
    },
    {
      "address": "00e7d0fe",
      "instruction": "CMP dword ptr [EBP + 0x310],0x0"
    },
    {
      "address": "00e7d105",
      "instruction": "JLE 0x00e7d165"
    },
    {
      "address": "00e7d107",
      "instruction": "MOV ECX,dword ptr [0x016b3c04]"
    },
    {
      "address": "00e7d10d",
      "instruction": "MOV EDX,dword ptr [ECX + 0x411c]"
    },
    {
      "address": "00e7d113",
      "instruction": "CMP EDX,dword ptr [ESI]"
    },
    {
      "address": "00e7d115",
      "instruction": "JNZ 0x00e7d121"
    },
    {
      "address": "00e7d117",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00e7d118",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00e7d119",
      "instruction": "CALL 0x00e62340"
    },
    {
      "address": "00e7d11e",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "00e7d121",
      "instruction": "MOV EAX,[0x016b3c04]"
    },
    {
      "address": "00e7d126",
      "instruction": "MOV ECX,dword ptr [EAX + 0x5190]"
    },
    {
      "address": "00e7d12c",
      "instruction": "CMP dword ptr [ECX + 0x7c],0x0"
    },
    {
      "address": "00e7d130",
      "instruction": "JNZ 0x00e7d13e"
    },
    {
      "address": "00e7d132",
      "instruction": "MOV EDX,dword ptr [EBP + 0x310]"
    },
    {
      "address": "00e7d138",
      "instruction": "ADD EDX,EDX"
    },
    {
      "address": "00e7d13a",
      "instruction": "ADD dword ptr [EDI],EDX"
    },
    {
      "address": "00e7d13c",
      "instruction": "JMP 0x00e7d165"
    },
    {
      "address": "00e7d13e",
      "instruction": "MOV EAX,dword ptr [EBP + 0x310]"
    },
    {
      "address": "00e7d144",
      "instruction": "ADD dword ptr [EDI],EAX"
    },
    {
      "address": "00e7d146",
      "instruction": "JMP 0x00e7d165"
    },
    {
      "address": "00e7d148",
      "instruction": "MOV ECX,dword ptr [0x016b3c04]"
    },
    {
      "address": "00e7d14e",
      "instruction": "MOV EDX,dword ptr [ECX + 0x411c]"
    },
    {
      "address": "00e7d154",
      "instruction": "CMP EDX,dword ptr [ESI]"
    },
    {
      "address": "00e7d156",
      "instruction": "JNZ 0x00e7d162"
    },
    {
      "address": "00e7d158",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00e7d159",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00e7d15a",
      "instruction": "CALL 0
[TRUNCATED]
```

## external_callees

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## function_identity

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "original_bytes": 6956,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": null,\n    \"hidden_this\": null,\n    \"receiver\": \"NOT CLAIMED, IN EITHER DIRECTION. The record declines to name one: receiver {present null, register null, reason ecx_reassigned_before_deref, confidence UNKNOWN, bounds_only true, offsets [], distinct_offsets 0, written_through 0}. Nothing in this package treats any register as `this`, and no receiver type, class, object size, vtable identity, field or layout is asserted anywhere.\",\n    \"receiver_register\": null,\n    \"ret_form\": \"RET\",\n    \"return_register\": \"ST0\",\n    \"return_semantics\": \"float_or_x87_in_ST0\",\n    \"saved_registers\": [\n      \"EBP\",\n      \"EBX\",\n      \"EDI\",\n      \"ESI\"\n    ],\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"RET\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-11-H4-HELPER-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"address_window_offset_005c65e0\",\n      \"va\": \"0x005c65e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"dispatch_key_00628450\",\n      \"va\": \"0x00628450\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"cycle_key_006286a0\",\n      \"va\": \"0x006286a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"release_child_0062c910\",\n      \"va\": \"0x0062c910\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d2a0\",\n      \"va\": \"0x00b3d2a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d300\",\n      \"va\": \"0x00b3d300\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"Simulator_GetUIMissionLogManager\",\n      \"va\": \"0x00b3d4f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-13-E4-EMPIRE-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"EmpirePoliticalColor_00c32cd0\",\n      \"va\": \"0x00c32cd0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"unknown-fun-mass\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0553\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"SUPPORTED\",\n  \"globals\": [],\n  \"integration_status\": null,\n  \"name\": null,\n  \"normalized_symbol\": null,\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"queue_candidate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"candidate\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [],\n    \"validated\": 0\n  },\n  \"runtime_gated\": false,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": null,\n  \"services\": [],\n  \"source\": {\n    \"decomp\": null,\n    \"file\": null,\n    \"files\": [\n      \"reconstruction/staging/pkg-w2-00e7d2c0/bounded_block_00e7d2c0.cpp\",\n      \"reconstruction/staging/pkg-w2-00e7d2c0/bounded_block_00e7d2c0.hpp\",\n      \"reconstruction/staging/pkg-w2-00e7d2c0/bounded_block_00e7d2c0_model_test.cpp\"\n    ],\n    \"handoffs\": [],\n    \"metadata\": [\n      \"reconstruction/metadata/pkg-w2-00e7d2c0/00e7d2c0.json\"\n    ],\n    \"provenance\": []\n  },\n  \"status\": \"candidate\",\n  \"subsystem\": \"Simulator\",\n  \"triage\": {\n    \"category\": \"GAMEPLAY_LOGIC\",\n    \"cluster\": \"unknown-fun-mass\",\n    \"db_triage_status\": \"candidate\",\n    \"decomp_path\": null,\n    \"dependencies\": [],\n    \"dossier\": null,\n    \"evidence\": \"SUPPORTED\",\n    \"in_degree\": 0,\n    \"kg_node_id\": null,\n    \"name\": null,\n    \"priority\": \"P1\",\n    \"provenance\": {\n      \"adjudicated\": true,\n      \"classifier\": \"triage-v6\",\n      \"replacement_candidate\": \"partial\",\n      \"snapshot\": \"f0e310e0\",\n      \"snapshot_sha256\": \"f0e310e0c83fc960ed38d490ff6d2a78d53925969206b4c4db7a012ddbf8b54b\"\n    }\n  },\n  \"types\": [\n    \"openspore::reconstruction::pkg_w2_00e7d2c0::BlockOutcome\",\n    \"openspore::reconstruction::pkg_w2_00e7d2c0::Byte\",\n    \"openspore::reconstruction::pkg_w2_00e7d2c0::StackWindow\",\n    \"openspore::reconstruction::pkg_w2_00e7d2c0::TailArguments\",\n    \"openspore::reconstruction::pkg_w2_00e7d2c0::Word\"\n  ],\n  \"unresolved_questions\": [\n    \"Is ESI provably zero on every path that reaches 0x00e7d2b7? The listing has exactly one definition of ESI, `XOR ESI,ESI` at 0x00e7d23d, and it dominates this block by inspection, but no dominator 
[TRUNCATED]
```

## ghidra_function

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089`

```json
{
  "binary_available": true,
  "binary_sha256": "25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e",
  "body_end": "00e7d360",
  "body_span_bytes": 753,
  "body_start": "00e7d070",
  "callees": [
    "FUN_00e77d50",
    "FUN_00e51650",
    "thunk_FUN_00e823a0",
    "FUN_00e671c0",
    "FUN_00e394f0",
    "FUN_00e53460",
    "FUN_00b72210",
    "FUN_00743b50",
    "Simulator::Cell::cCellUI::ShowHealthRollover",
    "FUN_00e82130",
    "FUN_00e7ce10"
  ],
  "callers": [
    "FUN_00e7d760",
    "FUN_00e81120",
    "App::cCellModeStrategy::OnMouseWheel"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00e7d070",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_30",
      "storage": "Stack[-0x30]:4",
      "type": "int[2]"
    },
    {
      "name": "local_28",
      "storage": "Stack[-0x28]:4",
      "type": "int[10]"
    },
    {
      "name": "param_1",
      "storage": "Stack[0x4]:4",
      "type": "int"
    },
    {
      "name": "piVar1",
      "storage": "register:00000000:4",
      "type": "int *"
    },
    {
      "name": "cell",
      "storage": "register:00000000:4",
      "type": "cCellObjectData *"
    },
    {
      "name": "in_EAX",
      "storage": "register:00000000:4",
      "type": "int"
    },
    {
      "name": "param_2",
      "storage": "Stack[0x8]:4",
      "type": "undefined4"
    },
    {
      "name": "uVar5",
      "storage": "Stack[-0x54]:4",
      "type": "undefined4"
    },
    {
      "name": "iVar4",
      "storage": "register:00000014:4",
      "type": "int"
    },
    {
      "name": "iVar3",
      "storage": "register:00000004:4",
      "type": "int"
    },
    {
      "name": "piVar2",
      "storage": "Stack[-0x44]:4",
      "type": "int *"
    }
  ],
  "locals_count": 11,
  "mode": "live",
  "name": "FUN_00e7d070",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xa7d2c0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00e7d070(void)",
  "size_bytes": 753,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00e7d2c0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 4,
  "xrefs": [
    {
      "from": "00e7d77e"
    },
    {
      "from": "00e816c2"
    },
    {
      "from": "00e816fd"
    },
    {
      "from": "00e7d6f8"
    }
  ]
}
```

## globals

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-w2-00e7d2c0/bounded_block_00e7d2c0.cpp",
    "reconstruction/staging/pkg-w2-00e7d2c0/bounded_block_00e7d2c0.hpp",
    "reconstruction/staging/pkg-w2-00e7d2c0/bounded_block_00e7d2c0_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-w2-00e7d2c0/00e7d2c0.json"
  ]
}
```

## runtime

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## runtime_metadata

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "blocking_reason": null,
  "gates": [],
  "validated": 0
}
```

## semantic_hypotheses

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

## status

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "runtime_gated": false,
  "runtime_validated": 0,
  "status": "candidate"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "openspore::reconstruction::pkg_w2_00e7d2c0::BlockOutcome",
  "openspore::reconstruction::pkg_w2_00e7d2c0::Byte",
  "openspore::reconstruction::pkg_w2_00e7d2c0::StackWindow",
  "openspore::reconstruction::pkg_w2_00e7d2c0::TailArguments",
  "openspore::reconstruction::pkg_w2_00e7d2c0::Word"
]
```

## vtables

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## Conflicts

```json
[]
```
