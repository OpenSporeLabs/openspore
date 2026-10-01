# Evidence 0x01053be0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `509ecc2517bb9ed74934688a790a8aa3e1931371ba1bb98d3c1a8f2a98b292fa`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": null,
  "hidden_this": true,
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": 1,
  "receiver": "ECX carries a receiver and the body reads it before any definite write to it (MOV EDI,ECX at 0x01053be7, then MOV ECX,EAX at 0x01053bee). Inference R1 records this at INFERRED confidence.",
  "return_observation": "The C entry declares void, which is the honest spelling of what the RECOVERED PREFIX does: it returns nothing, because it has no return instruction and neither of its two exits is a return. That is a statement about the 288 recovered bytes and NOT a claim that the function returns void: the real exit is outside the span and reads (from the image) MOV EAX,ESI ... ADD ESP,0x18; RET 0x8 at 0x01053d3b, which would put the caller's word in EAX. This package does not model that, does not claim it, and records the true return as an unresolved question. No canonical return_type is declared in this ...",
  "return_register": "ST0",
  "return_semantics": "float_or_x87_in_ST0 (machine record, confidence APPROXIMATION)",
  "return_width_bytes": null,
  "saved_registers": [
    "EBX",
    "EBP",
    "ESI",
    "EDI"
  ],
  "stack_cleanup_bytes": null,
  "stack_cleanup_owner": null
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
    "hidden_this": true,
    "hidden_this_register": "ECX",
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
    "receiver": true,
    "receiver_register": "ECX",
    "return_register": "ST0",
    "return_semantics": "float_or_x87_in_ST0",
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
    ]
  },
  "abstained_because": [
    "no_terminal_ret: the listing is a prefix of a longer function",
    "sret_vs_out_param: entry slot 0 is written through a pointer",
    "truncated_listing: the last instruction is neither a return nor an out-of-listing transfer, so the listing stops mid-function"
  ],
  "cleanup": {
    "bytes": null,
    "confidence": "UNKNOWN",
    "corroboration": "not_available",
    "evidence": null,
    "side": null
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "af82ba2573ea2e578111b1de0cf06ce0aa7fcff253d0cce0d3f41cfbde6e064e",
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
        "obs-0043"
      ],
      "claim": "no terminal return is present in the listing",
      "confidence": "UNKNOWN",
      "id": "C2"
    },
    {
      "based_on": [
        "obs-0014"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "INFERRED",
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
        "obs-0008",
        "obs-0010",
        "obs-0011",
        "obs-0026",
        "obs-0031"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          0
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0014"
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
        "obs-0001"
      ],
      "claim": "the return value is carried in ST0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "ST0"
    }
  ],
  "observations": [
    {
      "and_esp": null,
      "at": "0x01053be0",
      "ebp_is_general_register": false,
      "fp": false,
      "id": "obs-0001",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": true,
      "push_ebp_at": 2,
      "raw": "SUB ESP,0x18",
      "sub": 24
    },
    {
      "at": "0x01053be0",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x18",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x01053be3",
      "count": 3,
      "first_use": 1,
      "first_write_index": 59,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x01053be4",
      "count": 2,
      "first_use": 2,
      "first_write_index": 58,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH EBP",
      "reg": "EBP"
    },
    {
      "at": "0x01053be5",
      "count": 15,
      "first_use": 3,
      "first_write_index": 9,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x01053be6",
      "count": 3,
      "first_use": 4,
      "first_write_index": 5,
      "id": "obs-0006",
      "index": 4,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x01053be7",
      "count": 10,
      "first_use": 5,
      "first_write_index": 7,
      "id": "obs-0007",
      "index": 5,
      "kind": "REG_READ",
      "raw": "MOV EDI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x01053be7",
      "definite": true,
      "id": "obs-0008",
      "index": 5,
      "kind": "REG_WRITE",
      "raw": "MOV EDI,ECX",
      "reg": "EDI",
      "write_kind": "reg"
    },
    {
      "at": "0x01053be9",
      "id": "obs-0009",
      "index": 6,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00ffbe50",
      "target": "0x00ffbe50"
    },
    {
      "at": "0x01053bee",
      "count": 24,
      "first_use": 7,
      "first_write_index": 17,
      "id": "obs-0010",
      "index": 7,
      "kind": "REG_READ",
      "raw": "MOV ECX,EAX",
      "reg": "EAX"
    },
    {
      "at": "0x01053bee",
      "definite": true,
      "id": "obs-0011",
      "index": 7,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,EAX",
      "reg": "ECX",
      "write_kind": "reg"
    },
    {
      "at": "0x01053bf0",
   
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "simulator_game_input_manager_get_00b3d350",
    "reconstructed": true,
    "va": "0x00b3d350"
  }
]
```

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
"\n/* WARNING: Enum \"ObjectTYPE\": Some values do not have unique names */\n/* WARNING: Enum \"Names\": Some values do not have unique names */\n\nVector3 * __thiscall FUN_01053be0(int *param_1,Vector3 *param_2,undefined4 param_3)\n\n{\n  char cVar1;\n  int iVar2;\n  undefined4 *puVar3;\n  cGameInputManager *pcVar4;\n  float *pfVar5;\n  Vector3 *pVVar6;\n  int iVar7;\n  cPlanetModel *this;\n  undefined1 *puVar8;\n  Vector3 *position;\n  undefined4 uStack_18;\n  undefined4 uStack_14;\n  undefined4 uStack_10;\n  undefined1 local_c [12];\n  \n  FUN_00ffbe50();\n  iVar2 = FUN_00a1ad60();\n  param_2->x = 0.0;\n  param_2->y = 0.0;\n  param_2->z = 0.0;\n  if (iVar2 == 0) {\n    pcVar4 = Simulator__cGameInputManager__Get();\n    if (pcVar4 != (cGameInputManager *)0x0) {\n      puVar8 = local_c;\n      Simulator__cGameInputManager__Get();\n      pfVar5 = (float *)FUN_00b81720(puVar8);\n      param_2->x = *pfVar5;\n      param_2->y = pfVar5[1];\n      param_2->z = pfVar5[2];\n    }\n  }\n  else {\n    puVar3 = (undefined4 *)(**(code **)(*(int *)(iVar2 + 0x34) + 0x2c))();\n    uStack_18 = *puVar3;\n    uStack_14 = puVar3[1];\n    uStack_10 = puVar3[2];\n    pcVar4 = Simulator__cGameInputManager__Get();\n    if (pcVar4 != (cGameInputManager *)0x0) {\n      puVar3 = &uStack_18;\n      puVar8 = local_c;\n      Simulator__cGameInputManager__Get();\n      pfVar5 = (float *)FUN_00b815a0(puVar8,puVar3);\n      param_2->x = *pfVar5;\n      param_2->y = pfVar5[1];\n      param_2->z = pfVar5[2];\n    }\n  }\n  iVar2 = 0;\n  do {\n    iVar7 = iVar2;\n    iVar2 = iVar7 + 1;\n    cVar1 = (**(code **)(*param_1 + 0x24))(param_3,param_2,1);\n    if (cVar1 != '\\0') goto LAB_01053cf3;\n    this = (cPlanetModel *)local_c;\n    position = (Vector3 *)0x42480000;\n    pVVar6 = param_2;\n    Simulator__cGameInputManager__Get();\n    pVVar6 = Simulator__cPlanetModel__ToSurface(this,pVVar6,position);\n    param_2->x = pVVar6->x;\n    param_2->y = pVVar6->y;\n    param_2->z = pVVar6->z;\n  } while (iVar2 < 1000);\n  iVar2 = iVar7 + 2;\nLAB_01053cf3:\n  if (1000 < iVar2) {\n    iVar2 = 0;\n    do {\n      iVar2 = iVar2 + 1;\n      cVar1 = (**(code **)(*param_1 + 0x24))(param_3,param_2,1);\n      if (cVar1 != '\\0') {\n        return param_2;\n      }\n      puVar8 = local_c;\n      Simulator__cGameInputManager__Get();\n      pfVar5 = (float *)FUN_00b81720(puVar8);\n      param_2->x = *pfVar5;\n      param_2->y = pfVar5[1];\n      param_2->z = pfVar5[2];\n    } while (iVar2 < 1000);\n  }\n  return param_2;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 95,
  "instructions": [
    {
      "address": "01053be0",
      "instruction": "SUB ESP,0x18"
    },
    {
      "address": "01053be3",
      "instruction": "PUSH EBX"
    },
    {
      "address": "01053be4",
      "instruction": "PUSH EBP"
    },
    {
      "address": "01053be5",
      "instruction": "PUSH ESI"
    },
    {
      "address": "01053be6",
      "instruction": "PUSH EDI"
    },
    {
      "address": "01053be7",
      "instruction": "MOV EDI,ECX"
    },
    {
      "address": "01053be9",
      "instruction": "CALL 0x00ffbe50"
    },
    {
      "address": "01053bee",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "01053bf0",
      "instruction": "CALL 0x00a1ad60"
    },
    {
      "address": "01053bf5",
      "instruction": "MOV ESI,dword ptr [ESP + 0x2c]"
    },
    {
      "address": "01053bf9",
      "instruction": "XORPS XMM0,XMM0"
    },
    {
      "address": "01053bfc",
      "instruction": "MOVSS dword ptr [ESI],XMM0"
    },
    {
      "address": "01053c00",
      "instruction": "MOVSS dword ptr [ESI + 0x4],XMM0"
    },
    {
      "address": "01053c05",
      "instruction": "MOVSS dword ptr [ESI + 0x8],XMM0"
    },
    {
      "address": "01053c0a",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "01053c0c",
      "instruction": "JZ 0x01053c6c"
    },
    {
      "address": "01053c0e",
      "instruction": "MOV EDX,dword ptr [EAX + 0x34]"
    },
    {
      "address": "01053c11",
      "instruction": "ADD EAX,0x34"
    },
    {
      "address": "01053c14",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "01053c16",
      "instruction": "MOV EAX,dword ptr [EDX + 0x2c]"
    },
    {
      "address": "01053c19",
      "instruction": "CALL EAX"
    },
    {
      "address": "01053c1b",
      "instruction": "MOVSS XMM0,dword ptr [EAX]"
    },
    {
      "address": "01053c1f",
      "instruction": "MOVSS dword ptr [ESP + 0x10],XMM0"
    },
    {
      "address": "01053c25",
      "instruction": "MOVSS XMM0,dword ptr [EAX + 0x4]"
    },
    {
      "address": "01053c2a",
      "instruction": "MOVSS dword ptr [ESP + 0x14],XMM0"
    },
    {
      "address": "01053c30",
      "instruction": "MOVSS XMM0,dword ptr [EAX + 0x8]"
    },
    {
      "address": "01053c35",
      "instruction": "MOVSS dword ptr [ESP + 0x18],XMM0"
    },
    {
      "address": "01053c3b",
      "instruction": "CALL 0x00b3d350"
    },
    {
      "address": "01053c40",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "01053c42",
      "instruction": "JZ 0x01053c96"
    },
    {
      "address": "01053c44",
      "instruction": "LEA ECX,[ESP + 0x10]"
    },
    {
      "address": "01053c48",
      "instruction": "PUSH ECX"
    },
    {
      "address": "01053c49",
      "instruction": "LEA EDX,[ESP + 0x20]"
    },
    {
      "address": "01053c4d",
      "instruction": "PUSH EDX"
    },
    {
      "address": "01053c4e",
      "instruction": "CALL 0x00b3d350"
    },
    {
      "address": "01053c53",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "01053c55",
      "instruction": "CALL 0x00b815a0"
    },
    {
      "address": "01053c5a",
      "instruction": "MOV ECX,dword ptr [EAX]"
    },
    {
      "address": "01053c5c",
      "instruction": "MOV dword ptr [ESI],ECX"
    },
    {
      "address": "01053c5e",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "01053c61",
      "instruction": "MOV dword ptr [ESI + 0x4],EDX"
    },
    {
      "address": "01053c64",
      "instruction": "MOV EAX,dword ptr [EAX + 0x8]"
    },
    {
      "address": "01053c67",
      "instruction": "MOV dword ptr [ESI + 0x8],EAX"
    },
    {
      "address": "01053c6a",
      "instruction": "JMP 0x01053c96"
    },
    {
      "address": "01053c6c",
      "instruction": "CALL 0x00b3d350"
    },
    {
      "address": "01053c71",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "01053c73",
      "instruction": "JZ 0x01053c96"
    },
    {
      "address": "01053c75",
      "instruction": "LEA ECX,[ESP + 0x1c]"
    },
    {
      "address": "01053c79",
      "instruction": "PUSH ECX"
    },
    {
      "address": "01053c7a",
      "instruction": "CALL 0x00b3d350"
    },
    {
      "address": "01053c7f",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "01053c81",
      "instruction": "CALL 0x00b81720"
    },
    {
      "address": "01053c86",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "01053c88",
      "instruction": "MOV dword ptr [ESI],EDX"
    },
    {
      "address": "01053c8a",
      "instruction": "MOV ECX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "01053c8d",
      "instruction": "MOV dword ptr [ESI + 0x4],ECX"
    },
    {
      "address": "01053c90",
      "instruction": "MOV EDX,dword ptr [EAX + 0x8]"
    },
    {
      "address": "01053c93",
      "instruction": "MOV dword ptr [ESI + 0x8],EDX"
    },
    {
      "address": "01053c96",
      "instruction": "MOV EBP,dword ptr [ESP + 0x30]"
    },
    {
      "address": "01053c9a",
      "instruction": "XOR EBX,EBX"
    },
    {
      "address": "01053c9c",
      "instruction": "LEA ESP,[ESP]"
    },
    {
      "address": "01053ca0",
      "instruction": "MOV EAX,dword ptr [EDI]"
    },
    {
      "address": "01053ca2",
      "instruction": "MOV EDX,dword ptr [EAX + 0x24]"
    },
    {
      "address": "01053ca5",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "01053ca7",
      "instruction": "PUSH ESI"
    },
    {
      "address": "01053ca8",
      "instruction": "PUSH EBP"
    },
    {
      "address": "01053ca9",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "01053cab",
      "instruction": "INC EBX"
    },
    {
      "address": "01053cac",
      "instruction": "CALL EDX"
    },
    {
      "address": "01053cae",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "01053cb0",
      "instruction": 
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
  "original_bytes": 13475,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": null,\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": 1,\n    \"receiver\": \"ECX carries a receiver and the body reads it before any definite write to it (MOV EDI,ECX at 0x01053be7, then MOV ECX,EAX at 0x01053bee). Inference R1 records this at INFERRED confidence.\",\n    \"return_observation\": \"The C entry declares void, which is the honest spelling of what the RECOVERED PREFIX does: it returns nothing, because it has no return instruction and neither of its two exits is a return. That is a statement about the 288 recovered bytes and NOT a claim that the function returns void: the real exit is outside the span and reads (from the image) MOV EAX,ESI ... ADD ESP,0x18; RET 0x8 at 0x01053d3b, which would put the caller's word in EAX. This package does not model that, does not claim it, and records the true return as an unresolved question. No canonical return_type is declared in this ...\",\n    \"return_register\": \"ST0\",\n    \"return_semantics\": \"float_or_x87_in_ST0 (machine record, confidence APPROXIMATION)\",\n    \"return_width_bytes\": null,\n    \"saved_registers\": [\n      \"EBX\",\n      \"EBP\",\n      \"ESI\",\n      \"EDI\"\n    ],\n    \"stack_cleanup_bytes\": null,\n    \"stack_cleanup_owner\": null\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x0149b810,vtable:0x0149b8b4\"\n      ],\n      \"package\": \"pkg-sim-toolevent-01053d50\",\n      \"score\": 10,\n      \"symbol\": \"sim_toolevent_slot8_fun_01053d50\",\n      \"va\": \"0x01053d50\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-11-H4-HELPER-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"address_window_offset_005c65e0\",\n      \"va\": \"0x005c65e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"dispatch_key_00628450\",\n      \"va\": \"0x00628450\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"cycle_key_006286a0\",\n      \"va\": \"0x006286a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"release_child_0062c910\",\n      \"va\": \"0x0062c910\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d2a0\",\n      \"va\": \"0x00b3d2a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d300\",\n      \"va\": \"0x00b3d300\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"Simulator_GetUIMissionLogManager\",\n      \"va\": \"0x00b3d4f0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"sim-core-systems\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"simulator_game_input_manager_get_00b3d350\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b3d350\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x01053bf0\",\n        \"direction\": \"out\",\n        \"other\": \"0x00a1ad60\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x01053c3b\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b3d350\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x01053c4e\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b3d350\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x01053c6c\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b3d350\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x01053c7a\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b3d350\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x01053cce\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b3d350\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x01053c55\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b815a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x01053c81\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b81720\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x01053cd5\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b81780\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x01053be9\",\n        \"direction\": \"out\",\n        \"other\": \"0x00ffbe50\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 1,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [\n      \"0x00b3d350\"\n    ],\n    \"scc\": {\n      \"id\": \"scc-0607\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 
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
  "body_end": "01053cff",
  "body_span_bytes": 288,
  "body_start": "01053be0",
  "callees": [
    "FUN_00ffbe50",
    "FUN_00b81720",
    "Simulator::cPlanetModel::ToSurface",
    "Simulator::cGameInputManager::Get",
    "FUN_00b815a0",
    "FUN_00a1ad60"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "01053be0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "param_2",
      "storage": "Stack[0x4]:4",
      "type": "Vector3 *"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int *"
    },
    {
      "name": "uStack_14",
      "storage": "Stack[-0x14]:4",
      "type": "undefined4"
    },
    {
      "name": "uStack_18",
      "storage": "Stack[-0x18]:4",
      "type": "undefined4"
    },
    {
      "name": "uStack_10",
      "storage": "Stack[-0x10]:4",
      "type": "undefined4"
    },
    {
      "name": "pfVar5",
      "storage": "register:00000000:4",
      "type": "float *"
    },
    {
      "name": "pcVar4",
      "storage": "register:00000000:4",
      "type": "cGameInputManager *"
    },
    {
      "name": "iVar7",
      "storage": "register:0000000c:4",
      "type": "int"
    },
    {
      "name": "pVVar6",
      "storage": "register:00000000:4",
      "type": "Vector3 *"
    },
    {
      "name": "cVar1",
      "storage": "register:00000000:1",
      "type": "char"
    },
    {
      "name": "param_3",
      "storage": "Stack[0x8]:4",
      "type": "undefined4"
    },
    {
      "name": "puVar3",
      "storage": "Stack[-0x2c]:4",
      "type": "undefined4 *"
    },
    {
      "name": "iVar2",
      "storage": "register:00000000:4",
      "type": "int"
    },
    {
      "name": "puVar8",
      "storage": "Stack[-0x30]:4",
      "type": "undefined1 *"
    },
    {
      "name": "this",
      "storage": "Stack[-0x38]:4",
      "type": "cPlanetModel *"
    },
    {
      "name": "local_c",
      "storage": "",
      "type": "undefined1[12]"
    },
    {
      "name": "position",
      "storage": "Stack[-0x30]:4",
      "type": "Vector3 *"
    }
  ],
  "locals_count": 17,
  "mode": "live",
  "name": "FUN_01053be0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xc53be0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_01053be0(void)",
  "size_bytes": 288,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x01053be0",
  "vtables": {
    "referenced_by_vtables": [
      "0x0149b4d8",
      "0x0149b8b4",
      "0x0149b900",
      "0x0149b810",
      "0x0149ba30",
      "0x0149b2e0",
      "0x0149bf20"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 24,
  "xrefs": [
    {
      "from": "0149bb28"
    },
    {
      "from": "0149bb70"
    },
    {
      "from": "0149b548"
    },
    {
      "from": "0149b590"
    },
    {
      "from": "0149b5d8"
    },
    {
      "from": "0149b620"
    },
    {
      "from": "0149b668"
    },
    {
      "from": "0149b6b0"
    },
    {
      "from": "0149b6f8"
    },
    {
      "from": "0149b740"
    },
    {
      "from": "0149b788"
    },
    {
      "from": "0149b7d0"
    },
    {
      "from": "0149b818"
    },
    {
      "from": "0149b868"
    },
    {
      "from": "0149b8b8"
    },
    {
      "from": "0149b908"
    },
    {
      "from": "0149b958"
    },
    {
      "from": "0149b9a8"
    },
    {
      "from": "0149b9f0"
    },
    {
      "from": "0149ba38"
    },
    {
      "from": "0149ba88"
    },
    {
      "from": "0149bad0"
    },
    {
      "from": "0149b320"
    },
    {
      "from": "0149bf60"
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
    "reconstruction/staging/pkg-w2-01053be0/sim_prefix_01053be0.cpp",
    "reconstruction/staging/pkg-w2-01053be0/sim_prefix_01053be0.hpp",
    "reconstruction/staging/pkg-w2-01053be0/sim_prefix_01053be0_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-w2-01053be0/01053be0.json"
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
  "float",
  "openspore::reconstruction::pkg_w2_01053be0::ModelWord",
  "openspore::reconstruction::pkg_w2_01053be0::Receiver",
  "std::uint32_t"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x0149b2e0",
  "vtable:0x0149b4d8",
  "vtable:0x0149b810",
  "vtable:0x0149b8b4",
  "vtable:0x0149b900",
  "vtable:0x0149ba30",
  "vtable:0x0149bf20"
]
```

## Conflicts

```json
[]
```
