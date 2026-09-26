# Evidence 0x00bb1340

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `5abfabd840ef0daa60531af540033c581acbbaa2143d29d70e35b776d63a39e7`

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
      }
    ],
    "stack_cleanup_bytes": 4,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x4"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +56, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
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
  "content_sha256": "4e15ec6a8fd6d624f92605007ba2ea4a74f4fbc2a0da5126ace4337131462561",
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
    "indirect_calls": 2,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0053"
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
        "obs-0004"
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
        "obs-0001",
        "obs-0007",
        "obs-0009",
        "obs-0052"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          468
        ],
        "register": "ECX",
        "written_through": 1
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0007",
        "obs-0009",
        "obs-0052",
        "obs-0053"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0004"
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
        "obs-0053"
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
        "obs-0053"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0053"
      ],
      "claim": "the last value written to EAX classifies as pointer_like",
      "confidence": "INFERRED",
      "id": "RT2",
      "value": {
        "register_class": "pointer_like"
      }
    }
  ],
  "observations": [
    {
      "at": "0x00bb1340",
      "count": 8,
      "first_use": 0,
      "first_write_index": 6,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00bb1341",
      "count": 9,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00bb1342",
      "count": 10,
      "first_use": 2,
      "first_write_index": null,
      "id": "obs-0003",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV EBX,dword ptr [ESP + 0xc]",
      "reg": "ESP"
    },
    {
      "at": "0x00bb1342",
      "base": "ESP",
      "disp": 12,
      "id": "obs-0004",
      "index": 2,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EBX,dword ptr [ESP + 0xc]",
      "resolved": true,
      "size": 4,
      "trust": "untrusted_frame"
    },
    {
      "at": "0x00bb1342",
      "definite": true,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV EBX,dword ptr [ESP + 0xc]",
      "reg": "EBX",
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
"\nint * __thiscall FUN_00bb1340(int param_1,int param_2)\n\n{\n  int *piVar1;\n  char cVar2;\n  int iVar3;\n  int iVar4;\n  int *piVar5;\n  uint uVar6;\n  undefined4 uVar7;\n  undefined4 *puVar8;\n  bool bVar9;\n  int iVar10;\n  int local_4;\n  \n  iVar10 = param_2;\n  local_4 = param_1;\n  iVar3 = FUN_00b1fdb0();\n  iVar4 = FUN_00b1fdb0();\n  if (iVar4 == -1) {\n    uVar6 = *(uint *)(param_1 + 0x1d4);\n    *(uint *)(param_1 + 0x1d4) = uVar6 + 1;\n    FUN_00a16a90(uVar6 | 0x80000000);\n    iVar3 = FUN_00b1fdb0();\n  }\n  if (iVar3 != -1) {\n    param_2 = iVar3;\n    piVar5 = (int *)map_int_whatever_find(&local_4,&param_2);\n    if ((*piVar5 != param_1 + 0x154) && (piVar5 = *(int **)(*piVar5 + 0x14), piVar5 != (int *)0x0))\n    {\n      return piVar5;\n    }\n  }\n  param_2 = iVar3;\n  map_int_whatever_find(&local_4,&param_2);\n  if ((local_4 == param_1 + 0x130) ||\n     (iVar4 = *(int *)(local_4 + 0x14), *(int *)(local_4 + 0x14) == 0)) {\n    FUN_00baf630(iVar3,iVar10);\n    iVar4 = iVar10;\n  }\n  uVar6 = FUN_00c87040();\n  bVar9 = (uVar6 & 3) != 0;\n  param_2 = CONCAT31(param_2._1_3_,bVar9);\n  iVar10 = iVar3;\n  FUN_00b3d2a0(iVar3);\n  piVar5 = (int *)FUN_00baf0b0(iVar10);\n  FUN_00c359a0(iVar3,param_2);\n  FUN_00c341a0(iVar4);\n  FUN_00c30c10(iVar4);\n  if (bVar9) {\n    piVar1 = *(int **)(Simulator__sSpacePlayerData + 0x1c);\n    puVar8 = (undefined4 *)(Simulator__sSpacePlayerData + 0x1c);\n    if (piVar5 != piVar1) {\n      if (piVar5 != (int *)0x0) {\n        (**(code **)*piVar5)();\n      }\n      *puVar8 = piVar5;\n      if (piVar1 != (int *)0x0) {\n        (**(code **)(*piVar1 + 4))();\n      }\n    }\n  }\n  cVar2 = FUN_00c308b0();\n  if (cVar2 != '\\0') {\n    uVar7 = FUN_00bba500();\n    FUN_00c33690(uVar7);\n  }\n  FUN_0102f810();\n  uVar7 = FUN_0102fcb0();\n  FUN_00c31a60(uVar7);\n  return piVar5;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 122,
  "instructions": [
    {
      "address": "00bb1340",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00bb1341",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00bb1342",
      "instruction": "MOV EBX,dword ptr [ESP + 0xc]"
    },
    {
      "address": "00bb1346",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00bb1347",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00bb1349",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00bb134a",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "00bb134c",
      "instruction": "CALL 0x00b1fdb0"
    },
    {
      "address": "00bb1351",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "00bb1353",
      "instruction": "MOV EDI,EAX"
    },
    {
      "address": "00bb1355",
      "instruction": "CALL 0x00b1fdb0"
    },
    {
      "address": "00bb135a",
      "instruction": "CMP EAX,-0x1"
    },
    {
      "address": "00bb135d",
      "instruction": "JNZ 0x00bb1384"
    },
    {
      "address": "00bb135f",
      "instruction": "MOV EAX,dword ptr [ESI + 0x1d4]"
    },
    {
      "address": "00bb1365",
      "instruction": "LEA ECX,[EAX + 0x1]"
    },
    {
      "address": "00bb1368",
      "instruction": "OR EAX,0x80000000"
    },
    {
      "address": "00bb136d",
      "instruction": "MOV dword ptr [ESI + 0x1d4],ECX"
    },
    {
      "address": "00bb1373",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00bb1374",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "00bb1376",
      "instruction": "CALL 0x00a16a90"
    },
    {
      "address": "00bb137b",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "00bb137d",
      "instruction": "CALL 0x00b1fdb0"
    },
    {
      "address": "00bb1382",
      "instruction": "MOV EDI,EAX"
    },
    {
      "address": "00bb1384",
      "instruction": "MOV dword ptr [ESP + 0x14],EDI"
    },
    {
      "address": "00bb1388",
      "instruction": "CMP EDI,-0x1"
    },
    {
      "address": "00bb138b",
      "instruction": "JZ 0x00bb13b9"
    },
    {
      "address": "00bb138d",
      "instruction": "LEA EDX,[ESP + 0x14]"
    },
    {
      "address": "00bb1391",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00bb1392",
      "instruction": "LEA EAX,[ESP + 0x10]"
    },
    {
      "address": "00bb1396",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00bb1397",
      "instruction": "LEA ECX,[ESI + 0x150]"
    },
    {
      "address": "00bb139d",
      "instruction": "CALL 0x00e5c780"
    },
    {
      "address": "00bb13a2",
      "instruction": "MOV EAX,dword ptr [EAX]"
    },
    {
      "address": "00bb13a4",
      "instruction": "LEA ECX,[ESI + 0x154]"
    },
    {
      "address": "00bb13aa",
      "instruction": "CMP EAX,ECX"
    },
    {
      "address": "00bb13ac",
      "instruction": "JZ 0x00bb13b9"
    },
    {
      "address": "00bb13ae",
      "instruction": "MOV EAX,dword ptr [EAX + 0x14]"
    },
    {
      "address": "00bb13b1",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00bb13b3",
      "instruction": "JNZ 0x00bb148f"
    },
    {
      "address": "00bb13b9",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00bb13ba",
      "instruction": "LEA EDX,[ESP + 0x18]"
    },
    {
      "address": "00bb13be",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00bb13bf",
      "instruction": "LEA EAX,[ESP + 0x14]"
    },
    {
      "address": "00bb13c3",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00bb13c4",
      "instruction": "LEA ECX,[ESI + 0x12c]"
    },
    {
      "address": "00bb13ca",
      "instruction": "MOV dword ptr [ESP + 0x20],EDI"
    },
    {
      "address": "00bb13ce",
      "instruction": "CALL 0x00e5c780"
    },
    {
      "address": "00bb13d3",
      "instruction": "MOV EAX,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00bb13d7",
      "instruction": "LEA ECX,[ESI + 0x130]"
    },
    {
      "address": "00bb13dd",
      "instruction": "CMP EAX,ECX"
    },
    {
      "address": "00bb13df",
      "instruction": "JZ 0x00bb13e8"
    },
    {
      "address": "00bb13e1",
      "instruction": "MOV EBP,dword ptr [EAX + 0x14]"
    },
    {
      "address": "00bb13e4",
      "instruction": "TEST EBP,EBP"
    },
    {
      "address": "00bb13e6",
      "instruction": "JNZ 0x00bb13f3"
    },
    {
      "address": "00bb13e8",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00bb13e9",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00bb13ea",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00bb13ec",
      "instruction": "MOV EBP,EBX"
    },
    {
      "address": "00bb13ee",
      "instruction": "CALL 0x00baf630"
    },
    {
      "address": "00bb13f3",
      "instruction": "MOV ECX,EBP"
    },
    {
      "address": "00bb13f5",
      "instruction": "CALL 0x00c87040"
    },
    {
      "address": "00bb13fa",
      "instruction": "TEST AL,0x3"
    },
    {
      "address": "00bb13fc",
      "instruction": "SETNZ BL"
    },
    {
      "address": "00bb13ff",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00bb1400",
      "instruction": "MOV byte ptr [ESP + 0x1c],BL"
    },
    {
      "address": "00bb1404",
      "instruction": "CALL 0x00b3d2a0"
    },
    {
      "address": "00bb1409",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00bb140b",
      "instruction": "CALL 0x00baf0b0"
    },
    {
      "address": "00bb1410",
      "instruction": "MOV EDX,dword ptr [ESP + 0x18]"
    },
    {
      "address": "00bb1414",
      "instruction": "MOV ESI,EAX"
    },
    {
      "address": "00bb1416",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00bb1417",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00bb1418",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00bb141a",
    
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
  "body_end": "00bb1495",
  "body_span_bytes": 342,
  "body_start": "00bb1340",
  "callees": [
    "FUN_00bba500",
    "FUN_0102fcb0",
    "FUN_00c87040",
    "FUN_0102f810",
    "FUN_00c308b0",
    "FUN_00c341a0",
    "FUN_00baf0b0",
    "FUN_00c30c10",
    "FUN_00baf630",
    "FUN_00c359a0",
    "FUN_00b1fdb0",
    "map_int_whatever_find",
    "FUN_00a16a90",
    "FUN_00b3d2a0",
    "FUN_00c33690",
    "FUN_00c31a60"
  ],
  "callers": [
    "FUN_010221f0",
    "FUN_00bb3750",
    "FUN_00bb2070",
    "FUN_00fdd5a0",
    "FUN_0100a160"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00bb1340",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_4",
      "storage": "Stack[-0x4]:4",
      "type": "int"
    },
    {
      "name": "iVar10",
      "storage": "Stack[-0x18]:4",
      "type": "int"
    },
    {
      "name": "uVar7",
      "storage": "register:00000000:4",
      "type": "undefined4"
    },
    {
      "name": "uVar6",
      "storage": "register:00000000:4",
      "type": "uint"
    },
    {
      "name": "bVar9",
      "storage": "register:00000206:1",
      "type": "bool"
    },
    {
      "name": "puVar8",
      "storage": "register:0000000c:4",
      "type": "undefined4 *"
    },
    {
      "name": "iVar3",
      "storage": "register:00000000:4",
      "type": "int"
    },
    {
      "name": "cVar2",
      "storage": "register:00000000:1",
      "type": "char"
    },
    {
      "name": "piVar5",
      "storage": "register:00000000:4",
      "type": "int *"
    },
    {
      "name": "iVar4",
      "storage": "register:00000000:4",
      "type": "int"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int"
    },
    {
      "name": "piVar1",
      "storage": "unique:00017200:4",
      "type": "int *"
    },
    {
      "name": "param_2",
      "storage": "Stack[0x4]:4",
      "type": "int"
    }
  ],
  "locals_count": 13,
  "mode": "live",
  "name": "FUN_00bb1340",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x7b1340",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00bb1340(void)",
  "size_bytes": 342,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00bb1340",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 6,
  "xrefs": [
    {
      "from": "00bb37ec"
    },
    {
      "from": "00bb20f8"
    },
    {
      "from": "00bb217e"
    },
    {
      "from": "010222fd"
    },
    {
      "from": "00fdd643"
    },
    {
      "from": "0100a352"
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
