# Evidence 0x00be2440

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `0d3da0537dab6eae62e4856b48870ab54e410226a76bd9473d78016d30d3214f`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "cdecl",
  "hidden_this_register": null,
  "ordinary_stack_arguments": [
    {
      "name": "city",
      "offset": 4,
      "type": "OpaqueCity*",
      "width_bytes": 4
    },
    {
      "name": "live_state",
      "offset": 8,
      "type": "OpaqueLiveStateContext*",
      "width_bytes": 4
    },
    {
      "name": "update_word",
      "offset": 12,
      "type": "uint32_t",
      "width_bytes": 4
    }
  ],
  "return_register": "EAX",
  "return_type": "void",
  "saved_registers": [
    "EBX",
    "EBP",
    "ESI",
    "EDI"
  ],
  "termination": "plain RET"
}
```

## callees_dependencies

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## callers_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bcc760"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bcece0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00be3350"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00be3500"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00be3de0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00be5180"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00be5dd0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00be92e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d0e170"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d10840"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d10f90"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ff1da0"
  }
]
```

## contradictions

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## decompilation

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json
"\nvoid FUN_00be2440(int *param_1,int param_2,undefined4 param_3)\n\n{\n  int iVar1;\n  int iVar2;\n  int iVar3;\n  bool bVar4;\n  char cVar5;\n  int iVar6;\n  int iVar7;\n  int *piVar8;\n  undefined1 *puVar9;\n  uint uVar10;\n  uint uVar11;\n  uint uStack_210;\n  int iStack_20c;\n  int iStack_208;\n  char local_204 [16];\n  undefined4 uStack_1f4;\n  undefined4 uStack_1f0;\n  int local_1ec [14];\n  float fStack_1b4;\n  int local_1a4 [56];\n  undefined1 local_c4 [196];\n  \n  local_1a4[0xe] = 0;\n  local_1a4[0xf] = 0;\n  local_1a4[0x10] = 0;\n  local_1a4[0x11] = 0;\n  local_1a4[0x12] = 0;\n  local_1a4[0x13] = 0;\n  local_1a4[0x14] = 0;\n  local_1a4[0x15] = 0;\n  local_1a4[0x16] = 0;\n  local_1a4[0x17] = 0;\n  local_1a4[0x18] = 0;\n  local_1a4[0x19] = 0;\n  local_1a4[0x1a] = 0;\n  local_1a4[0x1b] = 0;\n  local_1a4[0] = 0;\n  local_1a4[1] = 0;\n  local_1a4[2] = 0;\n  local_1a4[3] = 0;\n  local_1a4[4] = 0;\n  local_1a4[5] = 0;\n  local_1a4[6] = 0;\n  local_1a4[7] = 0;\n  local_1a4[8] = 0;\n  local_1a4[9] = 0;\n  local_1a4[10] = 0;\n  local_1a4[0xb] = 0;\n  local_1a4[0xc] = 0;\n  local_1a4[0xd] = 0;\n  local_1a4[0x1c] = 0;\n  local_1a4[0x1d] = 0;\n  local_1a4[0x1e] = 0;\n  local_1a4[0x1f] = 0;\n  local_1a4[0x20] = 0;\n  local_1a4[0x21] = 0;\n  local_1a4[0x22] = 0;\n  local_1a4[0x23] = 0;\n  local_1a4[0x24] = 0;\n  local_1a4[0x25] = 0;\n  local_1a4[0x26] = 0;\n  local_1a4[0x27] = 0;\n  local_1a4[0x28] = 0;\n  local_1a4[0x29] = 0;\n  local_1a4[0x2a] = 0;\n  local_1a4[0x2b] = 0;\n  local_1a4[0x2c] = 0;\n  local_1a4[0x2d] = 0;\n  local_1a4[0x2e] = 0;\n  local_1a4[0x2f] = 0;\n  local_1a4[0x30] = 0;\n  local_1a4[0x31] = 0;\n  local_1a4[0x32] = 0;\n  local_1a4[0x33] = 0;\n  local_1a4[0x34] = 0;\n  local_1a4[0x35] = 0;\n  local_1a4[0x36] = 0;\n  local_1a4[0x37] = 0;\n  local_204[0] = '\\0';\n  local_204[1] = '\\0';\n  local_204[2] = '\\0';\n  local_204[3] = '\\0';\n  local_204[4] = '\\0';\n  local_204[5] = '\\0';\n  local_204[6] = '\\0';\n  local_204[7] = '\\0';\n  local_204[8] = '\\0';\n  local_204[9] = '\\0';\n  local_204[10] = '\\0';\n  local_204[0xb] = '\\0';\n  local_204[0xc] = '\\0';\n  local_204[0xd] = '\\0';\n  local_1ec[0] = 0;\n  local_1ec[1] = 0;\n  local_1ec[2] = 0;\n  local_1ec[3] = 0;\n  local_1ec[4] = 0;\n  local_1ec[5] = 0;\n  local_1ec[6] = 0;\n  local_1ec[7] = 0;\n  local_1ec[8] = 0;\n  local_1ec[9] = 0;\n  local_1ec[10] = 0;\n  local_1ec[0xb] = 0;\n  local_1ec[0xc] = 0;\n  local_1ec[0xd] = 0;\n  memset(local_c4,0,0xc4);\n  if (param_1 == (int *)0x0) {\n    if (param_2 == 0) {\n      return;\n    }\n    uVar11 = 0;\n    do {\n      iVar6 = FUN_00ff07a0(uVar11);\n      if (((iVar6 != 0) && (iVar7 = *(int *)(iVar6 + 0x30), *(int *)(iVar6 + 0x20) != 2)) &&\n         (0 < *(int *)(iVar6 + 0x2c))) {\n        local_1ec[iVar7] = *(int *)(iVar6 + 0x34);\n        uVar10 = 0;\n        do {\n          cVar5 = FUN_00ff0330(iVar7,uVar10);\n          if (cVar5 != '\\0') {\n            local_c4[uVar10 + iVar7 * 0xe] = 1;\n          }\n          uVar10 = uVar10 + 1;\n        } while (uVar10 < 0xe);\n      }\n      uVar11 = uVar11 + 1;\n    } while (uVar11 < 0xe);\n  }\n  else {\n    iVar6 = (**(code **)(*param_1 + 0x6c))();\n    if (iVar6 == 0) {\n      return;\n    }\n    iVar6 = 0;\n    uVar11 = 0;\n    do {\n      iVar7 = FUN_00af9ff0(iVar6);\n      if ((((iVar7 != 0) && (piVar8 = (int *)FUN_00fcc210(), piVar8 != (int *)0x0)) &&\n          ((piVar8 = (int *)(**(code **)(*piVar8 + 0xc))(0xe9cb8ba), piVar8 != (int *)0x0 &&\n           ((iVar7 = FUN_008e7f80(), iVar7 != 2 && (piVar8[0xa4] < 1)))))) &&\n         (cVar5 = FUN_00bfc600(), cVar5 == '\\0')) {\n        iVar7 = (**(code **)(*piVar8 + 0x20))();\n        local_1ec[iVar6] = iVar7;\n        uVar10 = 0;\n        do {\n          iVar7 = (**(code **)(*param_1 + 0x6c))();\n          if (*(char *)(uVar11 + iVar7 + 0x274 + uVar10) != '\\0') {\n            local_c4[uVar11 + uVar10] = 1;\n          }\n          uVar10 = uVar10 + 1;\n        } while (uVar10 < 0xe);\n      }\n      uVar11 = uVar11 + 0xe;\n      iVar6 = iVar6 + 1;\n    } while (uVar11 < 0xc4);\n  }\n  iVar6 = 0;\n  uVar11 = 0;\n  do {\n    if (local_1ec[uVar11] == 0x18ea1eb) {\n      local_204[uVar11] = '\\x01';\n    }\n    uVar11 = uVar11 + 1;\n  } while (uVar11 < 0xe);\n  do {\n    bVar4 = false;\n    uVar11 = 0;\n    puVar9 = local_c4 + 1;\n    do {\n      if ((local_1ec[uVar11] != 0) && (local_204[uVar11] == '\\0')) {\n        uVar10 = 0;\n        do {\n          if (((local_1ec[uVar10] != 0) && (local_204[uVar10] != '\\0')) &&\n             (puVar9[uVar10 - 1] != '\\0')) {\n            local_204[uVar11] = '\\x01';\n            bVar4 = true;\n          }\n          if (((local_1ec[uVar10 + 1] != 0) && (local_204[uVar10 + 1] != '\\0')) &&\n             (puVar9[uVar10] != '\\0')) {\n            local_204[uVar11] = '\\x01';\n            bVar4 = true;\n          }\n          uVar10 = uVar10 + 2;\n        } while (uVar10 < 0xe);\n      }\n      uVar11 = uVar11 + 1;\n      puVar9 = puVar9 + 0xe;\n    } while (uVar11 < 0xe);\n  } while (bVar4);\n  iStack_208 = 0;\n  iStack_20c = 0;\n  uStack_210 = 0;\n  uVar11 = 0;\n  puVar9 = local_c4 + 1;\n  do {\n    iVar7 = *(int *)((int)local_1ec + uVar11);\n    if ((iVar7 != 0) && (local_204[uStack_210] != '\\0')) {\n      if (iVar7 == 0x1a56aba) {\n        *(int *)((int)local_1a4 + uVar11) = *(int *)((int)local_1a4 + uVar11) + 1;\n        iStack_20c = iStack_20c + 1;\n      }\n      if (iVar7 == 0x18ea2cc) {\n        piVar8 = (int *)((int)local_1a4 + uVar11 + 0x38);\n        *piVar8 = *piVar8 + 1;\n        iVar6 = iVar6 + 1;\n      }\n      uVar10 = 0;\n      do {\n        if ((uStack_210 != uVar10) && (iVar7 = local_1ec[uVar10], iVar7 != 0)) {\n          iVar1 = *(int *)((int)local_1ec + uVar11);\n          if ((iVar1 == 0x18ea2cc) &&\n             (((iVar7 == 0x18ea1eb || (iVar7 == 0x18eb106)) && (puVar9[uVar10 - 1] != '\\0')))) {\n            piVar8 = (int *)((int)local_1a4 + uVar11 + 0x70);\n            *piVar8 = *piVar8 + 400;\n            iSta
[TRUNCATED]
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "original_bytes": 37197,
  "preview": "{\n  \"count\": 428,\n  \"instructions\": [\n    {\n      \"address\": \"00be2440\",\n      \"instruction\": \"SUB ESP,0x210\"\n    },\n    {\n      \"address\": \"00be2446\",\n      \"instruction\": \"XOR EAX,EAX\"\n    },\n    {\n      \"address\": \"00be2448\",\n      \"instruction\": \"PUSH EBX\"\n    },\n    {\n      \"address\": \"00be2449\",\n      \"instruction\": \"PUSH EBP\"\n    },\n    {\n      \"address\": \"00be244a\",\n      \"instruction\": \"PUSH ESI\"\n    },\n    {\n      \"address\": \"00be244b\",\n      \"instruction\": \"PUSH EDI\"\n    },\n    {\n      \"address\": \"00be244c\",\n      \"instruction\": \"PUSH 0xc4\"\n    },\n    {\n      \"address\": \"00be2451\",\n      \"instruction\": \"MOV dword ptr [ESP + 0xb8],EAX\"\n    },\n    {\n      \"address\": \"00be2458\",\n      \"instruction\": \"MOV dword ptr [ESP + 0xbc],EAX\"\n    },\n    {\n      \"address\": \"00be245f\",\n      \"instruction\": \"MOV dword ptr [ESP + 0xc0],EAX\"\n    },\n    {\n      \"address\": \"00be2466\",\n      \"instruction\": \"MOV dword ptr [ESP + 0xc4],EAX\"\n    },\n    {\n      \"address\": \"00be246d\",\n      \"instruction\": \"MOV dword ptr [ESP + 0xc8],EAX\"\n    },\n    {\n      \"address\": \"00be2474\",\n      \"instruction\": \"MOV dword ptr [ESP + 0xcc],EAX\"\n    },\n    {\n      \"address\": \"00be247b\",\n      \"instruction\": \"MOV dword ptr [ESP + 0xd0],EAX\"\n    },\n    {\n      \"address\": \"00be2482\",\n      \"instruction\": \"MOV dword ptr [ESP + 0xd4],EAX\"\n    },\n    {\n      \"address\": \"00be2489\",\n      \"instruction\": \"MOV dword ptr [ESP + 0xd8],EAX\"\n    },\n    {\n      \"address\": \"00be2490\",\n      \"instruction\": \"MOV dword ptr [ESP + 0xdc],EAX\"\n    },\n    {\n      \"address\": \"00be2497\",\n      \"instruction\": \"MOV dword ptr [ESP + 0xe0],EAX\"\n    },\n    {\n      \"address\": \"00be249e\",\n      \"instruction\": \"MOV dword ptr [ESP + 0xe4],EAX\"\n    },\n    {\n      \"address\": \"00be24a5\",\n      \"instruction\": \"MOV dword ptr [ESP + 0xe8],EAX\"\n    },\n    {\n      \"address\": \"00be24ac\",\n      \"instruction\": \"MOV dword ptr [ESP + 0xec],EAX\"\n    },\n    {\n      \"address\": \"00be24b3\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x80],EAX\"\n    },\n    {\n      \"address\": \"00be24ba\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x84],EAX\"\n    },\n    {\n      \"address\": \"00be24c1\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x88],EAX\"\n    },\n    {\n      \"address\": \"00be24c8\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x8c],EAX\"\n    },\n    {\n      \"address\": \"00be24cf\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x90],EAX\"\n    },\n    {\n      \"address\": \"00be24d6\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x94],EAX\"\n    },\n    {\n      \"address\": \"00be24dd\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x98],EAX\"\n    },\n    {\n      \"address\": \"00be24e4\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x9c],EAX\"\n    },\n    {\n      \"address\": \"00be24eb\",\n      \"instruction\": \"MOV dword ptr [ESP + 0xa0],EAX\"\n    },\n    {\n      \"address\": \"00be24f2\",\n      \"instruction\": \"MOV dword ptr [ESP + 0xa4],EAX\"\n    },\n    {\n      \"address\": \"00be24f9\",\n      \"instruction\": \"MOV dword ptr [ESP + 0xa8],EAX\"\n    },\n    {\n      \"address\": \"00be2500\",\n      \"instruction\": \"MOV dword ptr [ESP + 0xac],EAX\"\n    },\n    {\n      \"address\": \"00be2507\",\n      \"instruction\": \"MOV dword ptr [ESP + 0xb0],EAX\"\n    },\n    {\n      \"address\": \"00be250e\",\n      \"instruction\": \"MOV dword ptr [ESP + 0xb4],EAX\"\n    },\n    {\n      \"address\": \"00be2515\",\n      \"instruction\": \"MOV dword ptr [ESP + 0xf0],EAX\"\n    },\n    {\n      \"address\": \"00be251c\",\n      \"instruction\": \"MOV dword ptr [ESP + 0xf4],EAX\"\n    },\n    {\n      \"address\": \"00be2523\",\n      \"instruction\": \"MOV dword ptr [ESP + 0xf8],EAX\"\n    },\n    {\n      \"address\": \"00be252a\",\n      \"instruction\": \"MOV dword ptr [ESP + 0xfc],EAX\"\n    },\n    {\n      \"address\": \"00be2531\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x100],EAX\"\n    },\n    {\n      \"address\": \"00be2538\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x104],EAX\"\n    },\n    {\n      \"address\": \"00be253f\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x108],EAX\"\n    },\n    {\n      \"address\": \"00be2546\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x10c],EAX\"\n    },\n    {\n      \"address\": \"00be254d\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x110],EAX\"\n    },\n    {\n      \"address\": \"00be2554\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x114],EAX\"\n    },\n    {\n      \"address\": \"00be255b\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x118],EAX\"\n    },\n    {\n      \"address\": \"00be2562\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x11c],EAX\"\n    },\n    {\n      \"address\": \"00be2569\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x120],EAX\"\n    },\n    {\n      \"address\": \"00be2570\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x124],EAX\"\n    },\n    {\n      \"address\": \"00be2577\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x128],EAX\"\n    },\n    {\n      \"address\": \"00be257e\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x12c],EAX\"\n    },\n    {\n      \"address\": \"00be2585\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x130],EAX\"\n    },\n    {\n      \"address\": \"00be258c\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x134],EAX\"\n    },\n    {\n      \"address\": \"00be2593\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x138],EAX\"\n    },\n    {\n      \"address\": \"00be259a\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x13c],EAX\"\n    },\n    {\n      \"address\": \"00be25a1\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x140],EAX\"\n
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
  "original_bytes": 9963,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"cdecl\",\n    \"hidden_this_register\": null,\n    \"ordinary_stack_arguments\": [\n      {\n        \"name\": \"city\",\n        \"offset\": 4,\n        \"type\": \"OpaqueCity*\",\n        \"width_bytes\": 4\n      },\n      {\n        \"name\": \"live_state\",\n        \"offset\": 8,\n        \"type\": \"OpaqueLiveStateContext*\",\n        \"width_bytes\": 4\n      },\n      {\n        \"name\": \"update_word\",\n        \"offset\": 12,\n        \"type\": \"uint32_t\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"return_register\": \"EAX\",\n    \"return_type\": \"void\",\n    \"saved_registers\": [\n      \"EBX\",\n      \"EBP\",\n      \"ESI\",\n      \"EDI\"\n    ],\n    \"termination\": \"plain RET\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-13-C4-CIV-WAVE3\",\n      \"score\": 8,\n      \"symbol\": \"culture_selection_00bf9820\",\n      \"va\": \"0x00bf9820\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE7\",\n      \"score\": 2,\n      \"symbol\": \"simulator_game_input_manager_get_00b3d350\",\n      \"va\": \"0x00b3d350\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-14-A3-WORLD-WAVE3\",\n      \"score\": 2,\n      \"symbol\": \"sphere_draw_direction_00b7e560\",\n      \"va\": \"0x00b7e560\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-13-E3-EMPIRE-STATE-WAVE2\",\n      \"score\": 2,\n      \"symbol\": \"SpeciesProfileSelector_00c30cc0\",\n      \"va\": \"0x00c30cc0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-13-E3-EMPIRE-STATE-WAVE2\",\n      \"score\": 2,\n      \"symbol\": \"ArchetypeRelationshipsID_00c30e20\",\n      \"va\": \"0x00c30e20\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-13-E4-EMPIRE-WAVE3\",\n      \"score\": 2,\n      \"symbol\": \"PoliticalOwnershipScan_00c8d060\",\n      \"va\": \"0x00c8d060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-13-E2-DIPLOMACY-ALT\",\n      \"score\": 2,\n      \"symbol\": \"RelationshipScoreBand_00d00d00\",\n      \"va\": \"0x00d00d00\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-MODE-WAVE7\",\n      \"score\": 2,\n      \"symbol\": \"cell_mode_constructor_00e616c0\",\n      \"va\": \"0x00e616c0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bcc760\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bcece0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00be3350\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00be3500\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00be3de0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00be5180\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00be5dd0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00be92e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d0e170\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d10840\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d10f90\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ff1da0\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00bcc7c4\",\n        \"direction\": \"in\",\n        \"other\": \"0x00bcc760\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00bced59\",\n        \"direction\": \"in\",\n        \"other\": \"0x00bcece0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00bcf465\",\n        \"direction\": \"in\",\n        \"other\": \"0x00bcece0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00be33c4\",\n        \"direction\": \"in\",\n        \"other\": \"0x00be3350\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00be36ec\",\n        \"direction\": \"in\",\n        \"other\": \"0x00be3500\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00be3e7e\",\n        \"direction\": \"in\",\n        \"other\": \"0x00be3de0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00be526c\",\n        \"direction\": \"in\",\n        \"other\": \"0x00be5180\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00be605b\",\n        \"direction\": \"in\",\n        \"other\": \"0x00be5dd0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00be954d\",\n    
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
  "body_end": "00be2b0b",
  "body_span_bytes": 1740,
  "body_start": "00be2440",
  "callees": [
    "FUN_00ff08b0",
    "FUN_008e7f80",
    "FUN_00ff0330",
    "FUN_00af9ff0",
    "memset",
    "FUN_00bfc600",
    "FUN_00be0020",
    "FUN_00ff07a0",
    "FUN_00fcc210",
    "FUN_00bcc6e0"
  ],
  "callers": [
    "FUN_00bcece0",
    "FUN_00be3500",
    "FUN_00bcc760",
    "FUN_00be3de0",
    "FUN_00ff1da0",
    "FUN_00be3350",
    "FUN_00be5dd0",
    "FUN_00d10f90",
    "FUN_00be92e0",
    "FUN_00d10840",
    "FUN_00be5180",
    "FUN_00d0e170"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00be2440",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "param_2",
      "storage": "Stack[0x8]:4",
      "type": "int"
    },
    {
      "name": "param_1",
      "storage": "Stack[0x4]:4",
      "type": "int *"
    },
    {
      "name": "local_204",
      "storage": "Stack[-0x204]:4",
      "type": "char[16]"
    },
    {
      "name": "fStack_1b4",
      "storage": "Stack[-0x1b4]:4",
      "type": "float"
    },
    {
      "name": "local_1ec",
      "storage": "Stack[-0x1ec]:4",
      "type": "int[14]"
    },
    {
      "name": "uStack_1f4",
      "storage": "Stack[-0x1f4]:4",
      "type": "undefined4"
    },
    {
      "name": "uStack_1f0",
      "storage": "Stack[-0x1f0]:4",
      "type": "undefined4"
    },
    {
      "name": "uStack_210",
      "storage": "Stack[-0x210]:4",
      "type": "uint"
    },
    {
      "name": "iStack_208",
      "storage": "Stack[-0x208]:4",
      "type": "int"
    },
    {
      "name": "iStack_20c",
      "storage": "Stack[-0x20c]:4",
      "type": "int"
    },
    {
      "name": "local_c4",
      "storage": "",
      "type": "undefined1[196]"
    },
    {
      "name": "puVar9",
      "storage": "register:00000004:4",
      "type": "undefined1 *"
    },
    {
      "name": "piVar8",
      "storage": "register:00000000:4",
      "type": "int *"
    },
    {
      "name": "uVar11",
      "storage": "register:0000001c:4",
      "type": "uint"
    },
    {
      "name": "uVar10",
      "storage": "register:00000018:4",
      "type": "uint"
    },
    {
      "name": "cVar5",
      "storage": "register:00000000:1",
      "type": "char"
    },
    {
      "name": "bVar4",
      "storage": "unique:100001b3:1",
      "type": "bool"
    },
    {
      "name": "iVar7",
      "storage": "register:00000000:4",
      "type": "int"
    },
    {
      "name": "local_1a4",
      "storage": "Stack[-0x1a4]:4",
      "type": "int[56]"
    },
    {
      "name": "iVar6",
      "storage": "register:00000000:4",
      "type": "int"
    },
    {
      "name": "iVar1",
      "storage": "unique:00017200:4",
      "type": "int"
    },
    {
      "name": "param_3",
      "storage": "Stack[0xc]:4",
      "type": "undefined4"
    },
    {
      "name": "iVar3",
      "storage": "unique:00017200:4",
      "type": "int"
    },
    {
      "name": "iVar2",
      "storage": "unique:00017200:4",
      "type": "int"
    }
  ],
  "locals_count": 24,
  "mode": "live",
  "name": "FUN_00be2440",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x7e2440",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00be2440(void)",
  "size_bytes": 1740,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00be2440",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 14,
  "xrefs": [
    {
      "from": "00be33c4"
    },
    {
      "from": "00be3e7e"
    },
    {
      "from": "00be954d"
    },
    {
      "from": "00be526c"
    },
    {
      "from": "00be36ec"
    },
    {
      "from": "00be605b"
    },
    {
      "from": "00ff1f97"
    },
    {
      "from": "00bcc7c4"
    },
    {
      "from": "00d0e747"
    },
    {
      "from": "00d10d72"
    },
    {
      "from": "00d114ab"
    },
    {
      "from": "00bced59"
    },
    {
      "from": "00bcf465"
    },
    {
      "from": "00be791f"
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
    "src/reconstruction/pkg13_c4_civ_wave3/civ_wave3.cpp",
    "src/reconstruction/pkg13_c4_civ_wave3/civ_wave3.hpp",
    "src/reconstruction/pkg13_c4_civ_wave3/civ_wave3_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-sim-social-world-wave3/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg13-c4-civ-wave3/00be2440.json"
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
  "gates": [
    "runtime validation not run"
  ],
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
  "runtime_gated": true,
  "runtime_validated": 0,
  "status": "reconstructed"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "OpaqueCity*",
  "OpaqueLiveStateContext*",
  "uint32_t",
  "void"
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
