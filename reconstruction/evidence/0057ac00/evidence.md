# Evidence 0x0057ac00

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `dfc0870c652cfe26aeff167af0dd692781317c8fb21e38732da2fbac441cdec3`

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
      "entry_ESP+0x1c",
      "entry_ESP+0x28",
      "entry_ESP+0x2c",
      "entry_ESP+0x30",
      "entry_ESP+0x34",
      "entry_ESP+0x38",
      "entry_ESP+0x40",
      "entry_ESP+0x54"
    ],
    "ordinary_stack_arguments": [
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
        "entry_offset": "entry_ESP+0x34",
        "observed": true,
        "ordinal": 13,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x38",
        "observed": true,
        "ordinal": 14,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x40",
        "observed": true,
        "ordinal": 16,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x54",
        "observed": true,
        "ordinal": 21,
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
    "ret_form": "RET 0x10",
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
        "entry_offset": "entry_ESP+0x34",
        "observed": true,
        "ordinal": 13,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x38",
        "observed": true,
        "ordinal": 14,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x40",
        "observed": true,
        "ordinal": 16,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x54",
        "observed": true,
        "ordinal": 21,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "termination": "RET 0x10"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -36, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
    "ret_imm_below_highest_slot: ret 0x10 pops less than the highest read slot 0x54; everything above it belongs to the caller's frame",
    "slot_gaps_present: argument ordinal(s) below the highest read slot are never touched",
    "no_discriminator: the callee pop of 0x10 is not a whole number of dword stack arguments, so no convention follows from it"
  ],
  "cleanup": {
    "bytes": 16,
    "confidence": "UNKNOWN",
    "corroboration": "not_available",
    "evidence": "ret 0x10 but entry slot 0x54 is read",
    "side": null
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "8f225ade223fd4e75fd946688ceae468e0505ea4935685809a39153086c3a726",
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
    "indirect_calls": 0,
    
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
"\n/* WARNING: Enum \"ObjectTYPE\": Some values do not have unique names */\n/* WARNING: Enum \"Names\": Some values do not have unique names */\n\nvoid __thiscall FUN_0057ac00(int param_1,uint *param_2,undefined4 param_3,undefined4 param_4)\n\n{\n  char cVar1;\n  bool bVar2;\n  uint *puVar3;\n  int iVar4;\n  int iVar5;\n  int iVar6;\n  undefined4 uVar7;\n  ResourceKey local_48;\n  ResourceKey local_3c;\n  uint local_30;\n  uint local_2c;\n  uint local_28;\n  uint local_24;\n  uint local_20;\n  uint local_1c;\n  uint local_18;\n  uint local_14;\n  undefined1 local_10 [16];\n  \n  cVar1 = Prop_GetPropValueBool(0x55d7ca1);\n  if (cVar1 != '\\0') {\n    *param_2 = 0;\n    param_2[1] = 0;\n    param_2[2] = 0;\n    param_2[3] = 0;\n    return;\n  }\n  FUN_0057a960(&local_20);\n  puVar3 = (uint *)FUN_0057a9e0(local_10);\n  FUN_004bac30(&local_30,local_20 | *puVar3,local_1c | puVar3[1],local_18 | puVar3[2],\n               local_14 | puVar3[3],0);\n  if ((*(int *)(param_1 + 0x2a8) == 0x2b978c46) || (*(int *)(param_1 + 0x2a8) == 0x3d97a8e4)) {\n    iVar6 = 0;\n    iVar4 = FUN_004accf0();\n    if (0 < iVar4) {\n      do {\n        uVar7 = 0xb00f0fec;\n        FUN_004accb0(iVar6);\n        iVar5 = FUN_00435b60(uVar7);\n        if (iVar5 != 0) {\nLAB_0057acfb:\n          local_30 = local_30 & 0xfffffbff;\n          goto LAB_0057ad03;\n        }\n        uVar7 = 0x11b79301;\n        FUN_004accb0(iVar6);\n        iVar5 = FUN_00435b60(uVar7);\n        if (iVar5 != 0) goto LAB_0057acfb;\n        iVar6 = iVar6 + 1;\n      } while (iVar6 < iVar4);\n    }\n    local_30 = local_30 | 0x400;\n  }\nLAB_0057ad03:\n  local_48.instanceID = 0;\n  local_48.typeID = 0;\n  local_48.groupID = Global;\n  if (*(PropertyList **)(param_1 + 0x24) == (PropertyList *)0x0) {\nLAB_0057ad4f:\n    local_30 = local_30 & 0xfffbffff;\n  }\n  else {\n    bVar2 = App__Property__GetKey(*(PropertyList **)(param_1 + 0x24),0x7a926123,&local_48);\n    if (!bVar2) goto LAB_0057ad4f;\n    cVar1 = FUN_004efb20(param_3,local_48.instanceID,param_1 + 0x48);\n    if (cVar1 != '\\0') goto LAB_0057ad4f;\n    local_30 = local_30 | 0x40000;\n  }\n  local_3c.instanceID = 0;\n  local_3c.typeID = 0;\n  local_3c.groupID = Global;\n  if (*(PropertyList **)(param_1 + 0x24) != (PropertyList *)0x0) {\n    bVar2 = App__Property__GetKey(*(PropertyList **)(param_1 + 0x24),0xf5cbe065,&local_3c);\n    if (bVar2) {\n      cVar1 = FUN_004ef880(param_3,local_3c.instanceID,param_1 + 0x48);\n      if (cVar1 == '\\0') {\n        local_30 = local_30 | 0x20;\n        goto LAB_0057ada5;\n      }\n    }\n  }\n  local_30 = local_30 & 0xffffffdf;\nLAB_0057ada5:\n  if ((*(char *)(param_1 + 0x4b1) == '\\0') || (*(char *)(param_1 + 0x4b2) != '\\0')) {\n    local_30 = local_30 & 0xfffff7ff;\n  }\n  else {\n    local_30 = local_30 | 0x800;\n  }\n  FUN_004edf40(param_4,&local_30);\n  *param_2 = local_30;\n  param_2[1] = local_2c;\n  param_2[2] = local_28;\n  param_2[3] = local_24;\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "original_bytes": 13926,
  "preview": "{\n  \"count\": 166,\n  \"instructions\": [\n    {\n      \"address\": \"0057ac00\",\n      \"instruction\": \"SUB ESP,0x48\"\n    },\n    {\n      \"address\": \"0057ac03\",\n      \"instruction\": \"PUSH EBX\"\n    },\n    {\n      \"address\": \"0057ac04\",\n      \"instruction\": \"PUSH EBP\"\n    },\n    {\n      \"address\": \"0057ac05\",\n      \"instruction\": \"PUSH ESI\"\n    },\n    {\n      \"address\": \"0057ac06\",\n      \"instruction\": \"PUSH EDI\"\n    },\n    {\n      \"address\": \"0057ac07\",\n      \"instruction\": \"MOV ESI,ECX\"\n    },\n    {\n      \"address\": \"0057ac09\",\n      \"instruction\": \"MOV ECX,dword ptr [0x015fd918]\"\n    },\n    {\n      \"address\": \"0057ac0f\",\n      \"instruction\": \"PUSH 0x55d7ca1\"\n    },\n    {\n      \"address\": \"0057ac14\",\n      \"instruction\": \"CALL 0x006a25a0\"\n    },\n    {\n      \"address\": \"0057ac19\",\n      \"instruction\": \"TEST AL,AL\"\n    },\n    {\n      \"address\": \"0057ac1b\",\n      \"instruction\": \"JZ 0x0057ac38\"\n    },\n    {\n      \"address\": \"0057ac1d\",\n      \"instruction\": \"MOV EAX,dword ptr [ESP + 0x5c]\"\n    },\n    {\n      \"address\": \"0057ac21\",\n      \"instruction\": \"XOR ECX,ECX\"\n    },\n    {\n      \"address\": \"0057ac23\",\n      \"instruction\": \"MOV dword ptr [EAX],ECX\"\n    },\n    {\n      \"address\": \"0057ac25\",\n      \"instruction\": \"MOV dword ptr [EAX + 0x4],ECX\"\n    },\n    {\n      \"address\": \"0057ac28\",\n      \"instruction\": \"MOV dword ptr [EAX + 0x8],ECX\"\n    },\n    {\n      \"address\": \"0057ac2b\",\n      \"instruction\": \"MOV dword ptr [EAX + 0xc],ECX\"\n    },\n    {\n      \"address\": \"0057ac2e\",\n      \"instruction\": \"POP EDI\"\n    },\n    {\n      \"address\": \"0057ac2f\",\n      \"instruction\": \"POP ESI\"\n    },\n    {\n      \"address\": \"0057ac30\",\n      \"instruction\": \"POP EBP\"\n    },\n    {\n      \"address\": \"0057ac31\",\n      \"instruction\": \"POP EBX\"\n    },\n    {\n      \"address\": \"0057ac32\",\n      \"instruction\": \"ADD ESP,0x48\"\n    },\n    {\n      \"address\": \"0057ac35\",\n      \"instruction\": \"RET 0x10\"\n    },\n    {\n      \"address\": \"0057ac38\",\n      \"instruction\": \"LEA EAX,[ESP + 0x38]\"\n    },\n    {\n      \"address\": \"0057ac3c\",\n      \"instruction\": \"PUSH EAX\"\n    },\n    {\n      \"address\": \"0057ac3d\",\n      \"instruction\": \"MOV ECX,ESI\"\n    },\n    {\n      \"address\": \"0057ac3f\",\n      \"instruction\": \"CALL 0x0057a960\"\n    },\n    {\n      \"address\": \"0057ac44\",\n      \"instruction\": \"LEA ECX,[ESP + 0x48]\"\n    },\n    {\n      \"address\": \"0057ac48\",\n      \"instruction\": \"PUSH ECX\"\n    },\n    {\n      \"address\": \"0057ac49\",\n      \"instruction\": \"MOV ECX,ESI\"\n    },\n    {\n      \"address\": \"0057ac4b\",\n      \"instruction\": \"CALL 0x0057a9e0\"\n    },\n    {\n      \"address\": \"0057ac50\",\n      \"instruction\": \"MOV ECX,dword ptr [ESP + 0x38]\"\n    },\n    {\n      \"address\": \"0057ac54\",\n      \"instruction\": \"OR ECX,dword ptr [EAX]\"\n    },\n    {\n      \"address\": \"0057ac56\",\n      \"instruction\": \"MOV EDX,dword ptr [ESP + 0x3c]\"\n    },\n    {\n      \"address\": \"0057ac5a\",\n      \"instruction\": \"OR EDX,dword ptr [EAX + 0x4]\"\n    },\n    {\n      \"address\": \"0057ac5d\",\n      \"instruction\": \"MOV EDI,dword ptr [ESP + 0x40]\"\n    },\n    {\n      \"address\": \"0057ac61\",\n      \"instruction\": \"OR EDI,dword ptr [EAX + 0x8]\"\n    },\n    {\n      \"address\": \"0057ac64\",\n      \"instruction\": \"MOV EBP,dword ptr [ESP + 0x44]\"\n    },\n    {\n      \"address\": \"0057ac68\",\n      \"instruction\": \"OR EBP,dword ptr [EAX + 0xc]\"\n    },\n    {\n      \"address\": \"0057ac6b\",\n      \"instruction\": \"MOV EBX,dword ptr [ESP + 0x60]\"\n    },\n    {\n      \"address\": \"0057ac6f\",\n      \"instruction\": \"PUSH 0x0\"\n    },\n    {\n      \"address\": \"0057ac71\",\n      \"instruction\": \"SUB ESP,0x10\"\n    },\n    {\n      \"address\": \"0057ac74\",\n      \"instruction\": \"MOV EAX,ESP\"\n    },\n    {\n      \"address\": \"0057ac76\",\n      \"instruction\": \"MOV dword ptr [EAX],ECX\"\n    },\n    {\n      \"address\": \"0057ac78\",\n      \"instruction\": \"MOV dword ptr [EAX + 0x4],EDX\"\n    },\n    {\n      \"address\": \"0057ac7b\",\n      \"instruction\": \"LEA EDX,[ESP + 0x3c]\"\n    },\n    {\n      \"address\": \"0057ac7f\",\n      \"instruction\": \"MOV dword ptr [EAX + 0x8],EDI\"\n    },\n    {\n      \"address\": \"0057ac82\",\n      \"instruction\": \"PUSH EDX\"\n    },\n    {\n      \"address\": \"0057ac83\",\n      \"instruction\": \"MOV ECX,EBX\"\n    },\n    {\n      \"address\": \"0057ac85\",\n      \"instruction\": \"MOV dword ptr [EAX + 0xc],EBP\"\n    },\n    {\n      \"address\": \"0057ac88\",\n      \"instruction\": \"CALL 0x004bac30\"\n    },\n    {\n      \"address\": \"0057ac8d\",\n      \"instruction\": \"MOV EAX,dword ptr [ESI + 0x2a8]\"\n    },\n    {\n      \"address\": \"0057ac93\",\n      \"instruction\": \"CMP EAX,0x2b978c46\"\n    },\n    {\n      \"address\": \"0057ac98\",\n      \"instruction\": \"JZ 0x0057aca1\"\n    },\n    {\n      \"address\": \"0057ac9a\",\n      \"instruction\": \"CMP EAX,0x3d97a8e4\"\n    },\n    {\n      \"address\": \"0057ac9f\",\n      \"instruction\": \"JNZ 0x0057ad03\"\n    },\n    {\n      \"address\": \"0057aca1\",\n      \"instruction\": \"MOV ECX,dword ptr [ESI + 0x98]\"\n    },\n    {\n      \"address\": \"0057aca7\",\n      \"instruction\": \"XOR EDI,EDI\"\n    },\n    {\n      \"address\": \"0057aca9\",\n      \"instruction\": \"CALL 0x004accf0\"\n    },\n    {\n      \"address\": \"0057acae\",\n      \"instruction\": \"MOV EBP,EAX\"\n    },\n    {\n      \"address\": \"0057acb0\",\n      \"instruction\": \"TEST EBP,EBP\"\n    },\n    {\n      \"address\": \"0057acb2\",\n      \"instruction\": \"JLE 0x0057acf1\"\n  
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
  "body_end": "0057ae03",
  "body_span_bytes": 516,
  "body_start": "0057ac00",
  "callees": [
    "FUN_0057a9e0",
    "FUN_004edf40",
    "FUN_004ef880",
    "FUN_00435b60",
    "FUN_004accf0",
    "App::Property::GetKey",
    "FUN_004efb20",
    "FUN_0057a960",
    "FUN_004accb0",
    "FUN_004bac30",
    "Prop_GetPropValueBool"
  ],
  "callers": [
    "FUN_0057ea30",
    "Editors::cEditor::Undo",
    "FUN_0058d1c0",
    "Editors::cEditor::Redo",
    "FUN_0057f6c0",
    "Editors::cEditor::CommitEditHistory"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "0057ac00",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_48",
      "storage": "Stack[-0x48]:4",
      "type": "ResourceKey"
    },
    {
      "name": "local_3c",
      "storage": "Stack[-0x3c]:4",
      "type": "ResourceKey"
    },
    {
      "name": "local_2c",
      "storage": "Stack[-0x2c]:4",
      "type": "uint"
    },
    {
      "name": "local_30",
      "storage": "Stack[-0x30]:4",
      "type": "uint"
    },
    {
      "name": "iVar5",
      "storage": "register:00000000:4",
      "type": "int"
    },
    {
      "name": "local_24",
      "storage": "Stack[-0x24]:4",
      "type": "uint"
    },
    {
      "name": "iVar6",
      "storage": "register:0000001c:4",
      "type": "int"
    },
    {
      "name": "local_28",
      "storage": "Stack[-0x28]:4",
      "type": "uint"
    },
    {
      "name": "local_1c",
      "storage": "Stack[-0x1c]:4",
      "type": "uint"
    },
    {
      "name": "uVar7",
      "storage": "Stack[-0x5c]:4",
      "type": "undefined4"
    },
    {
      "name": "local_20",
      "storage": "Stack[-0x20]:4",
      "type": "uint"
    },
    {
      "name": "cVar1",
      "storage": "register:00000000:1",
      "type": "char"
    },
    {
      "name": "local_14",
      "storage": "Stack[-0x14]:4",
      "type": "uint"
    },
    {
      "name": "bVar2",
      "storage": "register:00000000:1",
      "type": "bool"
    },
    {
      "name": "local_18",
      "storage": "Stack[-0x18]:4",
      "type": "uint"
    },
    {
      "name": "puVar3",
      "storage": "register:00000000:4",
      "type": "uint *"
    },
    {
      "name": "iVar4",
      "storage": "register:00000000:4",
      "type": "int"
    },
    {
      "name": "local_10",
      "storage": "",
      "type": "undefined1[16]"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int"
    },
    {
      "name": "param_2",
      "storage": "Stack[0x4]:4",
      "type": "uint *"
    },
    {
      "name": "param_3",
      "storage": "Stack[0x8]:4",
      "type": "undefined4"
    },
    {
      "name": "param_4",
      "storage": "Stack[0xc]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 22,
  "mode": "live",
  "name": "FUN_0057ac00",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x17ac00",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_0057ac00(void)",
  "size_bytes": 516,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x0057ac00",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 7,
  "xrefs": [
    {
      "from": "00586635"
    },
    {
      "from": "0057eb7c"
    },
    {
      "from": "0058a768"
    },
    {
      "from": "0058aaf3"
    },
    {
      "from": "0058d2fb"
    },
    {
      "from": "0057f79e"
    },
    {
      "from": "0057f7d9"
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
