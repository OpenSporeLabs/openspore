# Evidence 0x00c487d0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `bd6af19adeb37cea21b0b9ab3dc3983507790b30fb78db418671ed33a7bc70dc`

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
      "entry_ESP+0x8"
    ],
    "ordinary_stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x4",
        "observed": false,
        "ordinal": 1,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "source": "ret_immediate",
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x8",
        "observed": false,
        "ordinal": 2,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "source": "ret_immediate",
        "written": false
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x8",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
    "saved_registers": [
      "EBP",
      "EBX",
      "EDI",
      "ESI"
    ],
    "stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x4",
        "observed": false,
        "ordinal": 1,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "source": "ret_immediate",
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x8",
        "observed": false,
        "ordinal": 2,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "source": "ret_immediate",
        "written": false
      }
    ],
    "stack_cleanup_bytes": 8,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x8"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +44, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 8,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x8",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "bd587089966527f720ea038713f5f29a753a83bcff0800e4bf1b4f7c26af5ce7",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall"
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
        "obs-0054"
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
        "obs-0054"
      ],
      "claim": "argument slots derived from the terminal immediate alone; no argument read was observed, so this is the popped area and not a parameter count",
      "confidence": "APPROXIMATION",
      "id": "A1-IMM",
      "value": {
        "derived_slots": 2,
        "total_bytes": 8
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007",
        "obs-0014",
        "obs-0023",
        "obs-0029",
        "obs-0032",
        "obs-0038",
        "obs-0042",
        "obs-0048",
        "obs-0052"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          0,
          380
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007",
        "obs-0014",
        "obs-0023",
        "obs-0029",
        "obs-0032",
        "obs-0038",
        "obs-0042",
        "obs-0048",
        "obs-0052",
        "obs-0054"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0054"
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
        "obs-0054"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0054"
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
      "at": "0x00c487d0",
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
      "raw": "SUB ESP,0x40",
      "sub": 64
    },
    {
      "at": "0x00c487d0",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x40",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00c487d3",
      "count": 3,
      "first_use": 1,
      "first_write_index": 41,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00c487d4",
      "count": 3,
      "first_use": 2,
      "first_write_index": 21,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH EBP",
      "reg
[TRUNCATED]
```

## abi_derived

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
      "entry_ESP+0x8"
    ],
    "ordinary_stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x4",
        "observed": false,
        "ordinal": 1,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "source": "ret_immediate",
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x8",
        "observed": false,
        "ordinal": 2,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "source": "ret_immediate",
        "written": false
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x8",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
    "saved_registers": [
      "EBP",
      "EBX",
      "EDI",
      "ESI"
    ],
    "stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x4",
        "observed": false,
        "ordinal": 1,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "source": "ret_immediate",
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x8",
        "observed": false,
        "ordinal": 2,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "source": "ret_immediate",
        "written": false
      }
    ],
    "stack_cleanup_bytes": 8,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x8"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +44, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 8,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x8",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "bd587089966527f720ea038713f5f29a753a83bcff0800e4bf1b4f7c26af5ce7",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall"
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
        "obs-0054"
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
        "obs-0054"
      ],
      "claim": "argument slots derived from the terminal immediate alone; no argument read was observed, so this is the popped area and not a parameter count",
      "confidence": "APPROXIMATION",
      "id": "A1-IMM",
      "value": {
        "derived_slots": 2,
        "total_bytes": 8
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007",
        "obs-0014",
        "obs-0023",
        "obs-0029",
        "obs-0032",
        "obs-0038",
        "obs-0042",
        "obs-0048",
        "obs-0052"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          0,
          380
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007",
        "obs-0014",
        "obs-0023",
        "obs-0029",
        "obs-0032",
        "obs-0038",
        "obs-0042",
        "obs-0048",
        "obs-0052",
        "obs-0054"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0054"
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
        "obs-0054"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0054"
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
      "at": "0x00c487d0",
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
      "raw": "SUB ESP,0x40",
      "sub": 64
    },
    {
      "at": "0x00c487d0",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x40",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00c487d3",
      "count": 3,
      "first_use": 1,
      "first_write_index": 41,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00c487d4",
      "count": 3,
      "first_use": 2,
      "first_write_index": 21,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH EBP",
      "reg
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "FUN_01021260",
    "reconstructed": true,
    "va": "0x01021260"
  },
  {
    "name": "pkg12_space_01021300",
    "reconstructed": true,
    "va": "0x01021300"
  }
]
```

## callers_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c48d40"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c48db0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c48e00"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c4c4b0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c4ea70"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c4ef00"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c4ef90"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c4fa40"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c4fc00"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c4fe60"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c52160"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c521c0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c53720"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c552d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c55330"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c55de0"
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
"\nvoid __fastcall FUN_00c487d0(int *param_1)\n\n{\n  short sVar1;\n  undefined4 uVar2;\n  int iVar3;\n  undefined4 uVar4;\n  int *piVar5;\n  short *psVar6;\n  short *psVar7;\n  int unaff_EBP;\n  undefined4 unaff_ESI;\n  undefined4 unaff_EDI;\n  undefined1 auStack_28 [20];\n  undefined1 auStack_14 [4];\n  undefined4 uStack_10;\n  \n  uVar2 = (**(code **)(*param_1 + 0xa4))();\n  *(int **)(DAT_016e0d08 + 0x18) = param_1;\n  *(undefined4 *)(DAT_016e0d08 + 0x48) = uVar2;\n  iVar3 = FUN_01021260();\n  if (iVar3 == 0) {\n    uVar2 = 0;\n  }\n  else {\n    uVar2 = *(undefined4 *)(iVar3 + 0x13c);\n  }\n  FUN_00c452a0();\n  uVar4 = FUN_00c451e0();\n  FUN_006b5060();\n  if ((int *)param_1[0x5f] != (int *)0x0) {\n    param_1 = (int *)param_1[0x5f];\n  }\n  piVar5 = (int *)FUN_00aed4d0();\n  FUN_00aed4d0();\n  iVar3 = *piVar5;\n  uVar2 = FUN_01021300(uVar2,param_1);\n  uVar2 = (**(code **)(iVar3 + 0x24))(auStack_14,uVar4,uVar2);\n  (**(code **)(unaff_EBP + 0xc))(unaff_ESI,uStack_10,uVar2);\n  psVar6 = (short *)FUN_006b55c0();\n  sVar1 = *psVar6;\n  psVar7 = psVar6;\n  while (sVar1 != 0) {\n    psVar7 = psVar7 + 1;\n    sVar1 = *psVar7;\n  }\n  FUN_00423650(psVar6,psVar6 + ((int)psVar7 - (int)psVar6 >> 1));\n  *(undefined1 **)(DAT_016e0d08 + 0x18) = auStack_28;\n  *(undefined4 *)(DAT_016e0d08 + 0x48) = unaff_EDI;\n  FUN_006b5240();\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 96,
  "instructions": [
    {
      "address": "00c487d0",
      "instruction": "SUB ESP,0x40"
    },
    {
      "address": "00c487d3",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00c487d4",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00c487d5",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00c487d6",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00c487d8",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "00c487da",
      "instruction": "MOV EDX,dword ptr [EAX + 0xa4]"
    },
    {
      "address": "00c487e0",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00c487e1",
      "instruction": "CALL EDX"
    },
    {
      "address": "00c487e3",
      "instruction": "MOV ECX,dword ptr [0x016e0d08]"
    },
    {
      "address": "00c487e9",
      "instruction": "MOV EDX,dword ptr [ECX + 0x18]"
    },
    {
      "address": "00c487ec",
      "instruction": "MOV dword ptr [ECX + 0x18],ESI"
    },
    {
      "address": "00c487ef",
      "instruction": "MOV ECX,dword ptr [0x016e0d08]"
    },
    {
      "address": "00c487f5",
      "instruction": "MOV dword ptr [ESP + 0x20],EDX"
    },
    {
      "address": "00c487f9",
      "instruction": "MOV EDX,dword ptr [ECX + 0x48]"
    },
    {
      "address": "00c487fc",
      "instruction": "MOV dword ptr [ESP + 0x18],EAX"
    },
    {
      "address": "00c48800",
      "instruction": "MOV dword ptr [ESP + 0x24],EDX"
    },
    {
      "address": "00c48804",
      "instruction": "MOV dword ptr [ECX + 0x48],EAX"
    },
    {
      "address": "00c48807",
      "instruction": "CALL 0x01021260"
    },
    {
      "address": "00c4880c",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00c4880e",
      "instruction": "JZ 0x00c48818"
    },
    {
      "address": "00c48810",
      "instruction": "MOV EBP,dword ptr [EAX + 0x13c]"
    },
    {
      "address": "00c48816",
      "instruction": "JMP 0x00c4881a"
    },
    {
      "address": "00c48818",
      "instruction": "XOR EBP,EBP"
    },
    {
      "address": "00c4881a",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00c4881c",
      "instruction": "CALL 0x00c452a0"
    },
    {
      "address": "00c48821",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00c48823",
      "instruction": "CALL 0x00c451e0"
    },
    {
      "address": "00c48828",
      "instruction": "LEA ECX,[ESP + 0x28]"
    },
    {
      "address": "00c4882c",
      "instruction": "MOV dword ptr [ESP + 0x10],EAX"
    },
    {
      "address": "00c48830",
      "instruction": "CALL 0x006b5060"
    },
    {
      "address": "00c48835",
      "instruction": "MOV EAX,dword ptr [ESI + 0x17c]"
    },
    {
      "address": "00c4883b",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00c4883d",
      "instruction": "JZ 0x00c48841"
    },
    {
      "address": "00c4883f",
      "instruction": "MOV ESI,EAX"
    },
    {
      "address": "00c48841",
      "instruction": "CALL 0x00aed4d0"
    },
    {
      "address": "00c48846",
      "instruction": "MOV EDI,EAX"
    },
    {
      "address": "00c48848",
      "instruction": "CALL 0x00aed4d0"
    },
    {
      "address": "00c4884d",
      "instruction": "LEA ECX,[ESP + 0x28]"
    },
    {
      "address": "00c48851",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00c48852",
      "instruction": "MOV ECX,dword ptr [EDI]"
    },
    {
      "address": "00c48854",
      "instruction": "MOV EBX,EAX"
    },
    {
      "address": "00c48856",
      "instruction": "MOV EAX,dword ptr [EBX]"
    },
    {
      "address": "00c48858",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00c48859",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00c4885a",
      "instruction": "MOV dword ptr [ESP + 0x28],EAX"
    },
    {
      "address": "00c4885e",
      "instruction": "MOV dword ptr [ESP + 0x20],ECX"
    },
    {
      "address": "00c48862",
      "instruction": "CALL 0x01021300"
    },
    {
      "address": "00c48867",
      "instruction": "MOV EDX,dword ptr [ESP + 0x1c]"
    },
    {
      "address": "00c4886b",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00c4886c",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00c4886d",
      "instruction": "LEA EAX,[ESP + 0x50]"
    },
    {
      "address": "00c48871",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00c48872",
      "instruction": "MOV EAX,dword ptr [ESP + 0x2c]"
    },
    {
      "address": "00c48876",
      "instruction": "MOV EDX,dword ptr [EAX + 0x24]"
    },
    {
      "address": "00c48879",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00c4887b",
      "instruction": "CALL EDX"
    },
    {
      "address": "00c4887d",
      "instruction": "MOV ECX,dword ptr [ESP + 0x1c]"
    },
    {
      "address": "00c48881",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00c48882",
      "instruction": "MOV EAX,dword ptr [ESP + 0x5c]"
    },
    {
      "address": "00c48886",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00c48887",
      "instruction": "MOV EAX,dword ptr [ESP + 0x28]"
    },
    {
      "address": "00c4888b",
      "instruction": "MOV EDX,dword ptr [EAX + 0xc]"
    },
    {
      "address": "00c4888e",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00c4888f",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "00c48891",
      "instruction": "CALL EDX"
    },
    {
      "address": "00c48893",
      "instruction": "LEA ECX,[ESP + 0x28]"
    },
    {
      "address": "00c48897",
      "instruction": "CALL 0x006b55c0"
    },
    {
      "address": "00c4889c",
      "instruction": "CMP word ptr [EAX],0x0"
    },
    {
      "address": "00c488a0",
      "instruction": "POP EDI"
    },
    {
      "address": "00c488a1",
      "instruction": "POP ESI"
    },
    {
  
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
  "original_bytes": 11707,
  "preview": "{\n  \"abi\": {},\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-11-H4-HELPER-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"address_window_offset_005c65e0\",\n      \"va\": \"0x005c65e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"dispatch_key_00628450\",\n      \"va\": \"0x00628450\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"cycle_key_006286a0\",\n      \"va\": \"0x006286a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"release_child_0062c910\",\n      \"va\": \"0x0062c910\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d2a0\",\n      \"va\": \"0x00b3d2a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d300\",\n      \"va\": \"0x00b3d300\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"Simulator_GetUIMissionLogManager\",\n      \"va\": \"0x00b3d4f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-13-E4-EMPIRE-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"EmpirePoliticalColor_00c32cd0\",\n      \"va\": \"0x00c32cd0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"unknown-fun-mass\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"FUN_01021260\",\n        \"reconstructed\": true,\n        \"va\": \"0x01021260\"\n      },\n      {\n        \"name\": \"pkg12_space_01021300\",\n        \"reconstructed\": true,\n        \"va\": \"0x01021300\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c48d40\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c48db0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c48e00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c4c4b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c4ea70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c4ef00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c4ef90\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c4fa40\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c4fc00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c4fe60\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c52160\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c521c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c53720\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c552d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c55330\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c55de0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c55e50\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c562b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c568d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c56bd0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c58920\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c5a180\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c5a280\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c5a3b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c5c470\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c5eed0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c5efb0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c5f690\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c61070\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c62ed0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c62f60\"\n      },\n      {\n        \"name\": null,\n        \"rec
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
  "body_end": "00c488f3",
  "body_span_bytes": 292,
  "body_start": "00c487d0",
  "callees": [
    "FUN_00c452a0",
    "FUN_01021260",
    "FUN_006b5060",
    "FUN_00aed4d0",
    "FUN_00423650",
    "FUN_01021300",
    "FUN_006b55c0",
    "FUN_006b5240",
    "FUN_00c451e0"
  ],
  "callers": [
    "FUN_00c5f690",
    "FUN_00c48e00",
    "FUN_00c568d0",
    "FUN_00c61070",
    "FUN_00c48db0",
    "FUN_00c4fa40",
    "FUN_00c5a180",
    "FUN_00c4c4b0",
    "FUN_00c5efb0",
    "FUN_00c55e50",
    "FUN_00c521c0",
    "FUN_00c53720",
    "FUN_00c62ed0",
    "FUN_00c5eed0",
    "FUN_00c4ef90",
    "FUN_00c5c470",
    "FUN_00c58920",
    "FUN_00c48d40",
    "FUN_00c4fe60",
    "FUN_00c5a280",
    "FUN_00c4fc00",
    "FUN_00c562b0",
    "FUN_00c4ea70",
    "FUN_00c52160",
    "FUN_00c62f60",
    "FUN_00c4ef00",
    "FUN_00c55de0",
    "FUN_00c5a3b0",
    "FUN_00c552d0",
    "FUN_00c56bd0",
    "FUN_00c55330",
    "FUN_00c634a0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00c487d0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "auStack_14",
      "storage": "",
      "type": "undefined1[4]"
    },
    {
      "name": "auStack_28",
      "storage": "",
      "type": "undefined1[20]"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int *"
    },
    {
      "name": "uStack_10",
      "storage": "Stack[-0x10]:4",
      "type": "undefined4"
    },
    {
      "name": "uVar2",
      "storage": "register:00000000:4",
      "type": "undefined4"
    },
    {
      "name": "sVar1",
      "storage": "unique:00017100:2",
      "type": "short"
    },
    {
      "name": "uVar4",
      "storage": "register:00000000:4",
      "type": "undefined4"
    },
    {
      "name": "iVar3",
      "storage": "register:00000000:4",
      "type": "int"
    },
    {
      "name": "psVar6",
      "storage": "register:00000000:4",
      "type": "short *"
    },
    {
      "name": "piVar5",
      "storage": "register:00000000:4",
      "type": "int *"
    },
    {
      "name": "unaff_EBP",
      "storage": "register:00000014:4",
      "type": "int"
    },
    {
      "name": "psVar7",
      "storage": "register:00000004:4",
      "type": "short *"
    },
    {
      "name": "unaff_EDI",
      "storage": "register:0000001c:4",
      "type": "undefined4"
    },
    {
      "name": "unaff_ESI",
      "storage": "register:00000018:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 14,
  "mode": "live",
  "name": "FUN_00c487d0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x8487d0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00c487d0(void)",
  "size_bytes": 292,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00c487d0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 95,
  "xrefs": [
    {
      "from": "00c48d7a"
    },
    {
      "from": "00c48dd6"
    },
    {
      "from": "00c48deb"
    },
    {
      "from": "00c48e26"
    },
    {
      "from": "00c48e3b"
    },
    {
      "from": "00c4c50c"
    },
    {
      "from": "00c4eae9"
    },
    {
      "from": "00c4eb38"
    },
    {
      "from": "00c4eb8b"
    },
    {
      "from": "00c4fcb3"
    },
    {
      "from": "00c4fda2"
    },
    {
      "from": "00c4ff81"
    },
    {
      "from": "00c500fc"
    },
    {
      "from": "00c5218d"
    },
    {
      "from": "00c521a2"
    },
    {
      "from": "00c521b7"
    },
    {
      "from": "00c521ed"
    },
    {
      "from": "00c52202"
    },
    {
      "from": "00c52217"
    },
    {
      "from": "00c537c2"
    },
    {
      "from": "00c552fd"
    },
    {
      "from": "00c55312"
    },
    {
      "from": "00c55327"
    },
    {
      "from": "00c5535d"
    },
    {
      "from": "00c55372"
    },
    {
      "from": "00c55387"
    },
    {
      "from": "00c55e1b"
    },
    {
      "from": "00c55e31"
    },
    {
      "from": "00c5a20f"
    },
    {
      "from": "00c5a238"
    },
    {
      "from": "00c5a251"
    },
    {
      "from": "00c55e8b"
    },
    {
      "from": "00c55ea1"
    },
    {
      "from": "00c5a332"
    },
    {
      "from": "00c5a35b"
    },
    {
      "from": "00c5a374"
    },
    {
      "from": "00c562f6"
    },
    {
      "from": "00c568f5"
    },
    {
      "from": "00c56c19"
    },
    {
      "from": "00c58946"
    },
    {
      "from": "00c5a462"
    },
    {
      "from": "00c5a48b"
    },
    {
      "from": "00c5a4a4"
    },
    {
      "from": "00c5c4d4"
    },
    {
      "from": "00c4fab5"
    },
    {
      "from": "00c4fb3e"
    },
    {
      "from": "00c4fb96"
    },
    {
      "from": "00c63523"
    },
    {
      "from": "00c610c0"
    },
    {
      "from": "00c61118"
    },
    {
      "from": "00c6116f"
    },
    {
      "from": "00c611ce"
    },
    {
      "from": "00c6122d"
    },
    {
      "from": "00c61284"
    },
    {
      "from": "00c612aa"
    },
    {
      "from": "00c612c2"
    },
    {
      "from": "00c62efa"
    },
    {
      "from": "00c62f0f"
    },
    {
      "from": "00c62f24"
    },
    {
      "from": "00c62f39"
    },
    {
      "from": "00c5ef02"
    },
    {
      "from": "00c5ef17"
    },
    {
      "from": "00c5ef4f"
    },
    {
      "from": "00
[TRUNCATED]
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
  "files": [],
  "handoffs": [],
  "metadata": []
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
