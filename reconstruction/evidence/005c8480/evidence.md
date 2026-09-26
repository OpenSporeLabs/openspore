# Evidence 0x005c8480

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `bb3a136369c04ae857bf1f1c3c9ec5ba01de0bc328d80aebab6a33ee3b7214c4`

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
      "entry_ESP+0x10",
      "entry_ESP+0x14",
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
        "size_inferred": false,
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
    "ret_form": "RET 0x8",
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
        "size_inferred": false,
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
    "termination": "RET 0x8"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -24, so the listing is not one path",
    "unparsed_lines_present: 2 line(s) matched no grammar rule",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
    "ret_imm_below_highest_slot: ret 0x8 pops less than the highest read slot 0x20; everything above it belongs to the caller's frame",
    "slot_gaps_present: argument ordinal(s) below the highest read slot are never touched",
    "no_discriminator: the callee pop of 0x8 is not a whole number of dword stack arguments, so no convention follows from it"
  ],
  "cleanup": {
    "bytes": 8,
    "confidence": "UNKNOWN",
    "corroboration": "not_available",
    "evidence": "ret 0x8 but entry slot 0x20 is read",
    "side": null
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "95f57489a8a2fe9eed4d4b3e68b1f99c4d55daf282250c7f29dc5512acb1c871",
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
    "indirect_calls": 4,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0032",
        "obs-0052"
      ],
      "claim": "the callee pops 8 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 8,
        "side": "callee"
      }
    },
    {
      "based_on": [
        "obs-0032",
        "obs-0052"
      ],
      "claim": "cleanup side is undetermined: a slot above the popped area is read",
      "confidence": "UNKNOWN",
      "id": "C4",
      "value": {
        "bytes": 8,
        "side": null
      }
    },
    {
      "based_on": [
        "obs-0011",
        "obs-0013",
        "obs-0033",
        "obs-0035",
        "obs-0036",
        "obs-0037",
        "obs-0038",
        "obs-0039",
        "obs-0040",
        "obs-0042",
        "obs-0046",
        "obs-0047"
      ],
      "claim": "entry-relative argument slots",
    
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
"\nvoid __thiscall FUN_005c8480(int *param_1,int *param_2,int *param_3)\n\n{\n  int *piVar1;\n  int *piVar2;\n  int iVar3;\n  int iVar4;\n  void *pvVar5;\n  size_t _Size;\n  void *local_8;\n  int local_4;\n  \n  piVar1 = (int *)param_1[1];\n  if (piVar1 != (int *)param_1[2]) {\n    if ((param_2 <= param_3) && (param_3 < piVar1)) {\n      param_3 = param_3 + 1;\n    }\n    if (piVar1 != (int *)0x0) {\n      piVar2 = (int *)piVar1[-1];\n      *piVar1 = (int)piVar2;\n      if (piVar2 != (int *)0x0) {\n        (**(code **)(*piVar2 + 4))();\n      }\n    }\n    FUN_005c1dc0(param_2,param_1[1] + -4,param_1[1]);\n    param_3 = (int *)*param_3;\n    piVar1 = (int *)*param_2;\n    if (param_3 != piVar1) {\n      if (param_3 != (int *)0x0) {\n        (**(code **)(*param_3 + 4))();\n      }\n      *param_2 = (int)param_3;\n      if (piVar1 != (int *)0x0) {\n        (**(code **)(*piVar1 + 8))();\n      }\n    }\n    param_1[1] = param_1[1] + 4;\n    return;\n  }\n  local_4 = (int)piVar1 - *param_1 >> 2;\n  if (local_4 == 0) {\n    local_4 = 1;\n  }\n  else {\n    local_4 = local_4 * 2;\n    if (local_4 == 0) {\n      local_8 = (void *)0x0;\n      goto LAB_005c854e;\n    }\n  }\n  local_8 = (void *)FUN_00f473a0(local_4 * 4,\"Editor\",0,0,\n                                 \"c:\\\\BuildAgent\\\\max-spore001-spore\\\\CMBuild\\\\SporeEP1_RL\\\\Core\\\\UTFKernel\\\\EASTL\\\\include\\\\EASTL/allocator.h\"\n                                 ,0xd1);\nLAB_005c854e:\n  _Size = (int)param_2 - *param_1;\n  pvVar5 = memcpy(local_8,(void *)*param_1,_Size);\n  piVar1 = (int *)((int)pvVar5 + ((int)_Size >> 2) * 4);\n  if (piVar1 != (int *)0x0) {\n    param_3 = (int *)*param_3;\n    *piVar1 = (int)param_3;\n    if (param_3 != (int *)0x0) {\n      (**(code **)(*param_3 + 4))();\n    }\n  }\n  iVar3 = param_1[1];\n  pvVar5 = memcpy(piVar1 + 1,param_2,iVar3 - (int)param_2);\n  iVar4 = *param_1;\n  if ((iVar4 != 0) && (*(int *)(iVar4 + -4) != 0)) {\n    FUN_00f47380(iVar4);\n  }\n  param_1[1] = (int)((int)pvVar5 + (iVar3 - (int)param_2 >> 2) * 4);\n  *param_1 = (int)local_8;\n  param_1[2] = (int)((int)local_8 + local_4 * 4);\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 133,
  "instructions": [
    {
      "address": "005c8480",
      "instruction": "SUB ESP,0x8"
    },
    {
      "address": "005c8483",
      "instruction": "PUSH EBX"
    },
    {
      "address": "005c8484",
      "instruction": "PUSH EBP"
    },
    {
      "address": "005c8485",
      "instruction": "PUSH ESI"
    },
    {
      "address": "005c8486",
      "instruction": "PUSH EDI"
    },
    {
      "address": "005c8487",
      "instruction": "MOV EDI,ECX"
    },
    {
      "address": "005c8489",
      "instruction": "MOV EAX,dword ptr [EDI + 0x4]"
    },
    {
      "address": "005c848c",
      "instruction": "CMP EAX,dword ptr [EDI + 0x8]"
    },
    {
      "address": "005c848f",
      "instruction": "JZ 0x005c84ff"
    },
    {
      "address": "005c8491",
      "instruction": "MOV ECX,dword ptr [ESP + 0x20]"
    },
    {
      "address": "005c8495",
      "instruction": "MOV EBP,dword ptr [ESP + 0x1c]"
    },
    {
      "address": "005c8499",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "005c849b",
      "instruction": "CMP ECX,EBP"
    },
    {
      "address": "005c849d",
      "instruction": "JC 0x005c84a6"
    },
    {
      "address": "005c849f",
      "instruction": "CMP ECX,EAX"
    },
    {
      "address": "005c84a1",
      "instruction": "JNC 0x005c84a6"
    },
    {
      "address": "005c84a3",
      "instruction": "LEA ESI,[ECX + 0x4]"
    },
    {
      "address": "005c84a6",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "005c84a8",
      "instruction": "JZ 0x005c84ba"
    },
    {
      "address": "005c84aa",
      "instruction": "MOV ECX,dword ptr [EAX + -0x4]"
    },
    {
      "address": "005c84ad",
      "instruction": "MOV dword ptr [EAX],ECX"
    },
    {
      "address": "005c84af",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "005c84b1",
      "instruction": "JZ 0x005c84ba"
    },
    {
      "address": "005c84b3",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "005c84b5",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "005c84b8",
      "instruction": "CALL EDX"
    },
    {
      "address": "005c84ba",
      "instruction": "MOV EAX,dword ptr [EDI + 0x4]"
    },
    {
      "address": "005c84bd",
      "instruction": "PUSH EAX"
    },
    {
      "address": "005c84be",
      "instruction": "ADD EAX,-0x4"
    },
    {
      "address": "005c84c1",
      "instruction": "PUSH EAX"
    },
    {
      "address": "005c84c2",
      "instruction": "PUSH EBP"
    },
    {
      "address": "005c84c3",
      "instruction": "CALL 0x005c1dc0"
    },
    {
      "address": "005c84c8",
      "instruction": "MOV ESI,dword ptr [ESI]"
    },
    {
      "address": "005c84ca",
      "instruction": "MOV EBX,dword ptr [EBP]"
    },
    {
      "address": "005c84cd",
      "instruction": "ADD ESP,0xc"
    },
    {
      "address": "005c84d0",
      "instruction": "CMP ESI,EBX"
    },
    {
      "address": "005c84d2",
      "instruction": "JZ 0x005c84f1"
    },
    {
      "address": "005c84d4",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "005c84d6",
      "instruction": "JZ 0x005c84e1"
    },
    {
      "address": "005c84d8",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "005c84da",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "005c84dd",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "005c84df",
      "instruction": "CALL EDX"
    },
    {
      "address": "005c84e1",
      "instruction": "MOV dword ptr [EBP],ESI"
    },
    {
      "address": "005c84e4",
      "instruction": "TEST EBX,EBX"
    },
    {
      "address": "005c84e6",
      "instruction": "JZ 0x005c84f1"
    },
    {
      "address": "005c84e8",
      "instruction": "MOV EAX,dword ptr [EBX]"
    },
    {
      "address": "005c84ea",
      "instruction": "MOV EDX,dword ptr [EAX + 0x8]"
    },
    {
      "address": "005c84ed",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "005c84ef",
      "instruction": "CALL EDX"
    },
    {
      "address": "005c84f1",
      "instruction": "ADD dword ptr [EDI + 0x4],0x4"
    },
    {
      "address": "005c84f5",
      "instruction": "POP EDI"
    },
    {
      "address": "005c84f6",
      "instruction": "POP ESI"
    },
    {
      "address": "005c84f7",
      "instruction": "POP EBP"
    },
    {
      "address": "005c84f8",
      "instruction": "POP EBX"
    },
    {
      "address": "005c84f9",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "005c84fc",
      "instruction": "RET 0x8"
    },
    {
      "address": "005c84ff",
      "instruction": "SUB EAX,dword ptr [EDI]"
    },
    {
      "address": "005c8501",
      "instruction": "SAR EAX,0x2"
    },
    {
      "address": "005c8504",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "005c8506",
      "instruction": "JBE 0x005c8538"
    },
    {
      "address": "005c8508",
      "instruction": "ADD EAX,EAX"
    },
    {
      "address": "005c850a",
      "instruction": "MOV dword ptr [ESP + 0x14],EAX"
    },
    {
      "address": "005c850e",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "005c8510",
      "instruction": "JZ 0x005c8546"
    },
    {
      "address": "005c8512",
      "instruction": "PUSH 0xd1"
    },
    {
      "address": "005c8517",
      "instruction": "PUSH 0x13ebb38"
    },
    {
      "address": "005c851c",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "005c851e",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "005c8520",
      "instruction": "ADD EAX,EAX"
    },
    {
      "address": "005c8522",
      "instruction": "ADD EAX,EAX"
    },
    {
      "address": "005c8524",
      "instruction": "PUSH 0x13eb430"
    },
    {
      "address": "005c8529",
      "instruction": "PUSH EAX"
    },
    {
      "address": "005c852a",
      "instruction": "
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
  "body_end": "005c85ce",
  "body_span_bytes": 335,
  "body_start": "005c8480",
  "callees": [
    "FUN_00f473a0",
    "FUN_00f47380",
    "memcpy",
    "FUN_005c1dc0"
  ],
  "callers": [
    "FUN_00631df0",
    "FUN_0062bb40",
    "FUN_01076540",
    "FUN_005c5f00",
    "FUN_006338a0",
    "FUN_005e04d0",
    "FUN_0066b050",
    "FUN_0062efb0",
    "FUN_0059cb80",
    "FUN_0062ce00",
    "FUN_005c85d0",
    "FUN_005c9230",
    "FUN_0062ec90",
    "FUN_0066b130",
    "FUN_00e0a680",
    "FUN_005c21d0",
    "FUN_005c2390",
    "FUN_0066b480",
    "Editors::cEditor::CommitEditHistory",
    "FUN_005c22b0",
    "FUN_0062f9f0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "005c8480",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "iVar4",
      "storage": "unique:00017200:4",
      "type": "int"
    },
    {
      "name": "pvVar5",
      "storage": "register:00000000:4",
      "type": "void *"
    },
    {
      "name": "_Size",
      "storage": "register:00000018:4",
      "type": "size_t"
    },
    {
      "name": "local_8",
      "storage": "Stack[-0x8]:4",
      "type": "void *"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int *"
    },
    {
      "name": "local_4",
      "storage": "Stack[-0x4]:4",
      "type": "int"
    },
    {
      "name": "param_2",
      "storage": "Stack[0x4]:4",
      "type": "int *"
    },
    {
      "name": "param_3",
      "storage": "Stack[0x8]:4",
      "type": "int *"
    },
    {
      "name": "piVar1",
      "storage": "unique:00017200:4",
      "type": "int *"
    },
    {
      "name": "piVar2",
      "storage": "unique:00017200:4",
      "type": "int *"
    },
    {
      "name": "iVar3",
      "storage": "unique:00017200:4",
      "type": "int"
    }
  ],
  "locals_count": 11,
  "mode": "live",
  "name": "FUN_005c8480",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x1c8480",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_005c8480(void)",
  "size_bytes": 335,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x005c8480",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 39,
  "xrefs": [
    {
      "from": "005c2372"
    },
    {
      "from": "005c221a"
    },
    {
      "from": "005c2455"
    },
    {
      "from": "005c5fbe"
    },
    {
      "from": "005c5feb"
    },
    {
      "from": "005c8a82"
    },
    {
      "from": "00586510"
    },
    {
      "from": "0062bd91"
    },
    {
      "from": "0062fb88"
    },
    {
      "from": "005c95ea"
    },
    {
      "from": "005e08ef"
    },
    {
      "from": "0062ceca"
    },
    {
      "from": "0062ef7b"
    },
    {
      "from": "0062f1af"
    },
    {
      "from": "0063399e"
    },
    {
      "from": "00631e35"
    },
    {
      "from": "0066b2c8"
    },
    {
      "from": "0066b3ba"
    },
    {
      "from": "0066b437"
    },
    {
      "from": "0066b4f3"
    },
    {
      "from": "0066b577"
    },
    {
      "from": "0066b5fb"
    },
    {
      "from": "0066b67f"
    },
    {
      "from": "0066b703"
    },
    {
      "from": "0066b787"
    },
    {
      "from": "0066b80b"
    },
    {
      "from": "0066b88f"
    },
    {
      "from": "0066b916"
    },
    {
      "from": "0066b9a1"
    },
    {
      "from": "0066ba2c"
    },
    {
      "from": "0066bab3"
    },
    {
      "from": "0066bb3e"
    },
    {
      "from": "0066bbc9"
    },
    {
      "from": "0066bc54"
    },
    {
      "from": "0066bcdf"
    },
    {
      "from": "010769de"
    },
    {
      "from": "0066b09f"
    },
    {
      "from": "00e0a716"
    },
    {
      "from": "0059cbb8"
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
