# Evidence 0x00ff4540

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `782c8bad742a467ff47e2b4665f46fa219a64f9673f7165e785d22231b9f7517`

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
    "ret_form": "RET 0x4",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
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
    "stack_cleanup_bytes": 4,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x4"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +16, so the listing is not one path",
    "sret_vs_out_param: entry slot 0 is written through a pointer"
  ],
  "cleanup": {
    "bytes": 4,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x4",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "b97535777883cdf091319e1b980c84c133cac82745b182cf1b0d74e2efe48744",
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
    "indirect_calls": 5,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0023",
        "obs-0031"
      ],
      "claim": "the callee pops 4 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 4,
        "side": "callee"
      }
    },
    {
      "based_on": [
        "obs-0005"
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
        "obs-0010",
        "obs-0011",
        "obs-0013"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          0,
          52,
          136,
          140
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0010",
        "obs-0011",
        "obs-0013",
        "obs-0023",
        "obs-0031"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0005"
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
        "obs-0023",
        "obs-0031"
      ],
      "claim": "in MSVC x86 a hidden struct-return pointer is always stack slot 0 while this is in ECX, so the two never contend",
      "confidence": "APPROXIMATION",
      "id": "S3",
      "value": {
        "ordering": "not_applicable"
      }
    },
    {
      "based_on": [
        "obs-0023",
        "obs-0031"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0023",
        "obs-0031"
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
      "at": "0x00ff4540",
      "count": 2,
      "first_use": 0,
      "first_write_index": 7,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00ff4541",
      "count": 7,
      "first_use": 1,
      "first_write_index": 6,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00ff4542",
      "count": 11,
      "first_use": 2,
      "first_write_index": 3,
      "id": "obs-0003",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00ff4543",
      "count": 1,
      "first_use": 3,
      "first_write_index": null,
      "id": "obs-0004",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV EDI,dword ptr [ESP + 0x10]",
      "reg": "ESP"
    },
    {
      "at": "0x00ff4543",
      "base": "ESP",
      "disp": 16,
      "id": "obs-0005",
      "index": 3,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EDI,dword ptr [ESP + 0x10]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00ff4543",
      "definite": true,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV EDI,dword ptr [ESP + 0x10]",
      "reg": "EDI",
      "write_kind": "mem_load"
    },
   
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
"\nvoid __thiscall FUN_00ff4540(int *param_1,int *param_2)\n\n{\n  int *piVar1;\n  char cVar2;\n  undefined4 uVar3;\n  int iVar4;\n  CommandLine *commandLine;\n  IAppSystem *pIVar5;\n  CommandLine *pCVar6;\n  \n  iVar4 = *param_1;\n  uVar3 = (**(code **)(*param_2 + 0x18))();\n  iVar4 = (**(code **)(iVar4 + 100))(param_2[5],uVar3);\n  if (-1 < iVar4) {\n    piVar1 = *(int **)(param_1[0xd] + iVar4 * 4);\n    cVar2 = (**(code **)(*piVar1 + 0x20))();\n    if (cVar2 == '\\0') {\n      commandLine = (CommandLine *)(**(code **)(piVar1[3] + 0xc))(0x707459f0);\n    }\n    else {\n      commandLine = (CommandLine *)param_1[0x22];\n    }\n    if (commandLine != (CommandLine *)0x0) {\n      if (commandLine == (CommandLine *)param_1[0x23]) {\n        FUN_00ff3e80();\n        return;\n      }\n      pIVar5 = App__IAppSystem__Get();\n      (*pIVar5->_vftable0->Init)((IAppSystem *)0x61dae65,commandLine);\n      pCVar6 = commandLine;\n      FUN_00b3d390(commandLine);\n      FUN_0104fc10(pCVar6);\n      *(undefined1 *)&(commandLine->field_28).mpBegin = 0;\n    }\n  }\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 61,
  "instructions": [
    {
      "address": "00ff4540",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00ff4541",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00ff4542",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00ff4543",
      "instruction": "MOV EDI,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00ff4547",
      "instruction": "MOV EAX,dword ptr [EDI]"
    },
    {
      "address": "00ff4549",
      "instruction": "MOV EDX,dword ptr [EAX + 0x18]"
    },
    {
      "address": "00ff454c",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00ff454e",
      "instruction": "MOV EBX,dword ptr [ESI]"
    },
    {
      "address": "00ff4550",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00ff4552",
      "instruction": "CALL EDX"
    },
    {
      "address": "00ff4554",
      "instruction": "MOV EDX,dword ptr [EBX + 0x64]"
    },
    {
      "address": "00ff4557",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00ff4558",
      "instruction": "MOV EAX,dword ptr [EDI + 0x14]"
    },
    {
      "address": "00ff455b",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00ff455c",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00ff455e",
      "instruction": "CALL EDX"
    },
    {
      "address": "00ff4560",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00ff4562",
      "instruction": "JL 0x00ff45d1"
    },
    {
      "address": "00ff4564",
      "instruction": "MOV ECX,dword ptr [ESI + 0x34]"
    },
    {
      "address": "00ff4567",
      "instruction": "MOV EDI,dword ptr [ECX + EAX*0x4]"
    },
    {
      "address": "00ff456a",
      "instruction": "MOV EDX,dword ptr [EDI]"
    },
    {
      "address": "00ff456c",
      "instruction": "MOV EAX,dword ptr [EDX + 0x20]"
    },
    {
      "address": "00ff456f",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00ff4571",
      "instruction": "CALL EAX"
    },
    {
      "address": "00ff4573",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00ff4575",
      "instruction": "JZ 0x00ff457f"
    },
    {
      "address": "00ff4577",
      "instruction": "MOV EDI,dword ptr [ESI + 0x88]"
    },
    {
      "address": "00ff457d",
      "instruction": "JMP 0x00ff4591"
    },
    {
      "address": "00ff457f",
      "instruction": "MOV EDX,dword ptr [EDI + 0xc]"
    },
    {
      "address": "00ff4582",
      "instruction": "MOV EAX,dword ptr [EDX + 0xc]"
    },
    {
      "address": "00ff4585",
      "instruction": "LEA ECX,[EDI + 0xc]"
    },
    {
      "address": "00ff4588",
      "instruction": "PUSH 0x707459f0"
    },
    {
      "address": "00ff458d",
      "instruction": "CALL EAX"
    },
    {
      "address": "00ff458f",
      "instruction": "MOV EDI,EAX"
    },
    {
      "address": "00ff4591",
      "instruction": "TEST EDI,EDI"
    },
    {
      "address": "00ff4593",
      "instruction": "JZ 0x00ff45d1"
    },
    {
      "address": "00ff4595",
      "instruction": "CMP EDI,dword ptr [ESI + 0x8c]"
    },
    {
      "address": "00ff459b",
      "instruction": "JNZ 0x00ff45aa"
    },
    {
      "address": "00ff459d",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00ff459f",
      "instruction": "CALL 0x00ff3e80"
    },
    {
      "address": "00ff45a4",
      "instruction": "POP EDI"
    },
    {
      "address": "00ff45a5",
      "instruction": "POP ESI"
    },
    {
      "address": "00ff45a6",
      "instruction": "POP EBX"
    },
    {
      "address": "00ff45a7",
      "instruction": "RET 0x4"
    },
    {
      "address": "00ff45aa",
      "instruction": "CALL 0x0067dcc0"
    },
    {
      "address": "00ff45af",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00ff45b1",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00ff45b3",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00ff45b4",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00ff45b6",
      "instruction": "MOV EAX,dword ptr [EDX + 0x14]"
    },
    {
      "address": "00ff45b9",
      "instruction": "PUSH 0x61dae65"
    },
    {
      "address": "00ff45be",
      "instruction": "CALL EAX"
    },
    {
      "address": "00ff45c0",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00ff45c1",
      "instruction": "CALL 0x00b3d390"
    },
    {
      "address": "00ff45c6",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00ff45c8",
      "instruction": "CALL 0x0104fc10"
    },
    {
      "address": "00ff45cd",
      "instruction": "MOV byte ptr [EDI + 0x28],0x0"
    },
    {
      "address": "00ff45d1",
      "instruction": "POP EDI"
    },
    {
      "address": "00ff45d2",
      "instruction": "POP ESI"
    },
    {
      "address": "00ff45d3",
      "instruction": "POP EBX"
    },
    {
      "address": "00ff45d4",
      "instruction": "RET 0x4"
    }
  ]
}
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
  "body_end": "00ff45d6",
  "body_span_bytes": 151,
  "body_start": "00ff4540",
  "callees": [
    "FUN_00ff3e80",
    "FUN_0104fc10",
    "FUN_00b3d390",
    "App::IAppSystem::Get"
  ],
  "callers": [
    "FUN_0104fa90",
    "FUN_0100a960",
    "FUN_0104e260",
    "FUN_01077900",
    "FUN_01050070"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00ff4540",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int *"
    },
    {
      "name": "param_2",
      "storage": "Stack[0x4]:4",
      "type": "int *"
    },
    {
      "name": "piVar1",
      "storage": "unique:00017200:4",
      "type": "int *"
    },
    {
      "name": "cVar2",
      "storage": "register:00000000:1",
      "type": "char"
    },
    {
      "name": "uVar3",
      "storage": "register:00000000:4",
      "type": "undefined4"
    },
    {
      "name": "iVar4",
      "storage": "register:00000000:4",
      "type": "int"
    },
    {
      "name": "commandLine",
      "storage": "register:0000001c:4",
      "type": "CommandLine *"
    },
    {
      "name": "pIVar5",
      "storage": "register:00000000:4",
      "type": "IAppSystem *"
    },
    {
      "name": "pCVar6",
      "storage": "Stack[-0x24]:4",
      "type": "CommandLine *"
    }
  ],
  "locals_count": 9,
  "mode": "live",
  "name": "FUN_00ff4540",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xbf4540",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00ff4540(void)",
  "size_bytes": 151,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00ff4540",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 5,
  "xrefs": [
    {
      "from": "0104fb03"
    },
    {
      "from": "010503c4"
    },
    {
      "from": "0100aa05"
    },
    {
      "from": "0104e283"
    },
    {
      "from": "0107792e"
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
