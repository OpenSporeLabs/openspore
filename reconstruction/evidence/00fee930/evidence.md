# Evidence 0x00fee930

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `fc875c7a93541576300ee6ef6f7973e55154d36ba12329aa47cdc05031ebc0f7`

## abi

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "abi": {
    "architecture": "x86-32",
    "ordinary_stack_argument_slots": [
      "entry_ESP+0x4"
    ],
    "ordinary_stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "ret_form": "RET 0x4",
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
    "saved_registers": [
      "EDI",
      "ESI"
    ],
    "stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": true,
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
    "flow_not_modelled: the linear ESP walk ends at +28, so the listing is not one path",
    "receiver_not_determinable: ecx_read_without_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_read_without_deref), and the convention rule that would apply discriminates on receiver absence"
  ],
  "cleanup": {
    "bytes": 4,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x4",
    "side": "callee"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "1e43715e81a4c79f4c597fe57e2f12ba2cb19a4037120be851c0af6c86655dc5",
  "conventions": {
    "ambiguities": [
      "receiver_undetermined"
    ],
    "calling_convention": null,
    "candidate_conventions": [
      "__stdcall",
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
        "obs-0024",
        "obs-0037"
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
        "obs-0005",
        "obs-0009",
        "obs-0011"
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
        "obs-0010",
        "obs-0015",
        "obs-0023",
        "obs-0036"
      ],
      "claim": "the register receiver is undetermined: ecx_read_without_deref",
      "confidence": "UNKNOWN",
      "id": "R0",
      "value": {
        "reason": "ecx_read_without_deref",
        "register": null
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0007",
        "obs-0010",
        "obs-0015",
        "obs-0023",
        "obs-0036"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_read_without_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0024",
        "obs-0037"
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
        "obs-0024",
        "obs-0037"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0024",
        "obs-0037"
      ],
      "claim": "the last value written to EAX classifies as integral",
      "confidence": "INFERRED",
      "id": "RT2",
      "value": {
        "register_class": "integral"
      }
    }
  ],
  "observations": [
    {
      "at": "0x00fee930",
      "count": 5,
      "first_use": 0,
      "first_write_index": 29,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00fee931",
      "count": 7,
      "first_use": 1,
      "first_write_index": 4,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00fee932",
      "count": 4,
      "first_use": 2,
      "first_write_index": 3,
      "id": "obs-0003",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00fee933",
      "count": 4,
      "first_use": 3,
      "first_write_index": null,
      "id": "obs-0004",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV EDI,dword ptr [ESP + 0x10]",
      "reg": "ESP"
    },
    {
      "at": "0x00fee933",
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
      "at": "0x00fee933",
      "definite": true,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV EDI,dword ptr [ESP + 0x10]",
      "reg": "EDI",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00fee937",
      "definite": true,
      "id": "obs-0007",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00fee939",
      "count": 12,
      "first_use": 5,
      "first_write_index": 12,
      "id": "obs-0008",
      "index": 5,
      "kind": "REG_READ",
      
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
"\nundefined4 __thiscall FUN_00fee930(int param_1,int param_2)\n\n{\n  int iVar1;\n  char cVar2;\n  int *piVar3;\n  int iVar4;\n  undefined4 uVar5;\n  int local_4;\n  \n  iVar4 = param_2;\n  local_4 = param_1;\n  piVar3 = (int *)map_int_whatever_find(&local_4,&param_2);\n  if (*piVar3 != param_1 + 0x60) {\n    iVar1 = *(int *)(*piVar3 + 0x14);\n    if (iVar1 == 2) {\n      return 1;\n    }\n    if (iVar1 == 3) {\n      return 1;\n    }\n  }\n  if (iVar4 < -0x1c0a6b1e) {\n    if (iVar4 == -0x1c0a6b1f) {\n      iVar4 = FUN_00fee480(0xe3f594e1);\n      if ((iVar4 != 0) && (cVar2 = FUN_00c44c80(), cVar2 != '\\0')) {\n        return 0;\n      }\n      FUN_00b3d300();\n      FUN_00f67d90();\n      cVar2 = FUN_00c772c0(0x4ac8010);\n      goto LAB_00fee9ba;\n    }\n    if (iVar4 == -0x6951388c) {\n      iVar4 = FUN_00fee480(0x96aec774);\n      if ((iVar4 != 0) && (cVar2 = FUN_00c44c80(), cVar2 != '\\0')) {\n        return 0;\n      }\n      uVar5 = 0x3ae13c90;\n    }\n    else {\n      if (iVar4 != -0x69513889) {\n        return 0;\n      }\n      iVar4 = FUN_00fee480(0x96aec777);\n      if ((iVar4 != 0) && (cVar2 = FUN_00c44c80(), cVar2 != '\\0')) {\n        return 0;\n      }\n      uVar5 = 0x3ae13c93;\n    }\n  }\n  else {\n    if (iVar4 != 0x62613a1d) {\n      return 0;\n    }\n    iVar4 = FUN_00fee480(0x62613a1d);\n    if ((iVar4 != 0) && (cVar2 = FUN_00c44c80(), cVar2 != '\\0')) {\n      return 0;\n    }\n    uVar5 = 0x372e73ee;\n  }\n  FUN_01002bd0(uVar5);\n  FUN_00bfc5f0();\n  cVar2 = FUN_00fe4180(uVar5);\nLAB_00fee9ba:\n  if (cVar2 != '\\0') {\n    return 1;\n  }\n  return 0;\n}\n\n"
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
      "address": "00fee930",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00fee931",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00fee932",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00fee933",
      "instruction": "MOV EDI,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00fee937",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00fee939",
      "instruction": "LEA EAX,[ESP + 0x10]"
    },
    {
      "address": "00fee93d",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00fee93e",
      "instruction": "LEA ECX,[ESP + 0xc]"
    },
    {
      "address": "00fee942",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00fee943",
      "instruction": "LEA ECX,[ESI + 0x5c]"
    },
    {
      "address": "00fee946",
      "instruction": "MOV dword ptr [ESP + 0x18],EDI"
    },
    {
      "address": "00fee94a",
      "instruction": "CALL 0x00e5c780"
    },
    {
      "address": "00fee94f",
      "instruction": "MOV EAX,dword ptr [EAX]"
    },
    {
      "address": "00fee951",
      "instruction": "LEA EDX,[ESI + 0x60]"
    },
    {
      "address": "00fee954",
      "instruction": "CMP EAX,EDX"
    },
    {
      "address": "00fee956",
      "instruction": "JZ 0x00fee965"
    },
    {
      "address": "00fee958",
      "instruction": "MOV EAX,dword ptr [EAX + 0x14]"
    },
    {
      "address": "00fee95b",
      "instruction": "CMP EAX,0x2"
    },
    {
      "address": "00fee95e",
      "instruction": "JZ 0x00fee9c2"
    },
    {
      "address": "00fee960",
      "instruction": "CMP EAX,0x3"
    },
    {
      "address": "00fee963",
      "instruction": "JZ 0x00fee9c2"
    },
    {
      "address": "00fee965",
      "instruction": "CMP EDI,0xe3f594e1"
    },
    {
      "address": "00fee96b",
      "instruction": "JG 0x00feea21"
    },
    {
      "address": "00fee971",
      "instruction": "JZ 0x00fee9ec"
    },
    {
      "address": "00fee973",
      "instruction": "CMP EDI,0x96aec774"
    },
    {
      "address": "00fee979",
      "instruction": "JZ 0x00fee9ca"
    },
    {
      "address": "00fee97b",
      "instruction": "CMP EDI,0x96aec777"
    },
    {
      "address": "00fee981",
      "instruction": "JNZ 0x00feea4a"
    },
    {
      "address": "00fee987",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00fee988",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00fee98a",
      "instruction": "CALL 0x00fee480"
    },
    {
      "address": "00fee98f",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00fee991",
      "instruction": "JZ 0x00fee9a2"
    },
    {
      "address": "00fee993",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00fee995",
      "instruction": "CALL 0x00c44c80"
    },
    {
      "address": "00fee99a",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00fee99c",
      "instruction": "JNZ 0x00feea4a"
    },
    {
      "address": "00fee9a2",
      "instruction": "PUSH 0x3ae13c93"
    },
    {
      "address": "00fee9a7",
      "instruction": "CALL 0x01002bd0"
    },
    {
      "address": "00fee9ac",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00fee9ae",
      "instruction": "CALL 0x00bfc5f0"
    },
    {
      "address": "00fee9b3",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00fee9b5",
      "instruction": "CALL 0x00fe4180"
    },
    {
      "address": "00fee9ba",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00fee9bc",
      "instruction": "JZ 0x00feea4a"
    },
    {
      "address": "00fee9c2",
      "instruction": "POP EDI"
    },
    {
      "address": "00fee9c3",
      "instruction": "MOV AL,0x1"
    },
    {
      "address": "00fee9c5",
      "instruction": "POP ESI"
    },
    {
      "address": "00fee9c6",
      "instruction": "POP ECX"
    },
    {
      "address": "00fee9c7",
      "instruction": "RET 0x4"
    },
    {
      "address": "00fee9ca",
      "instruction": "PUSH 0x96aec774"
    },
    {
      "address": "00fee9cf",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00fee9d1",
      "instruction": "CALL 0x00fee480"
    },
    {
      "address": "00fee9d6",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00fee9d8",
      "instruction": "JZ 0x00fee9e5"
    },
    {
      "address": "00fee9da",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00fee9dc",
      "instruction": "CALL 0x00c44c80"
    },
    {
      "address": "00fee9e1",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00fee9e3",
      "instruction": "JNZ 0x00feea4a"
    },
    {
      "address": "00fee9e5",
      "instruction": "PUSH 0x3ae13c90"
    },
    {
      "address": "00fee9ea",
      "instruction": "JMP 0x00fee9a7"
    },
    {
      "address": "00fee9ec",
      "instruction": "PUSH 0xe3f594e1"
    },
    {
      "address": "00fee9f1",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00fee9f3",
      "instruction": "CALL 0x00fee480"
    },
    {
      "address": "00fee9f8",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00fee9fa",
      "instruction": "JZ 0x00feea07"
    },
    {
      "address": "00fee9fc",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00fee9fe",
      "instruction": "CALL 0x00c44c80"
    },
    {
      "address": "00feea03",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00feea05",
      "instruction": "JNZ 0x00feea4a"
    },
    {
      "address": "00feea07",
      "instruction": "CALL 0x00b3d300"
    },
    {
      "address": "00feea0c",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00feea0e",
      "instruction": "CALL 0x00f67d90"
    },
    {
      "address": "00feea13",
      "instruction": "PUSH 0x4ac8010"
    },
    {
      "address": "00feea18",
      "instruction": "MOV ECX,EAX"
    
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
  "body_end": "00feea51",
  "body_span_bytes": 290,
  "body_start": "00fee930",
  "callees": [
    "map_int_whatever_find",
    "FUN_00fe4180",
    "FUN_00fee480",
    "FUN_00bfc5f0",
    "FUN_00f67d90",
    "FUN_01002bd0",
    "FUN_00c772c0",
    "FUN_00c44c80",
    "FUN_00b3d300"
  ],
  "callers": [
    "FUN_00fef140",
    "FUN_00feebb0",
    "FUN_00aed580",
    "FUN_00feea60",
    "FUN_00feec30",
    "FUN_00feecb0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00fee930",
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
      "type": "int"
    },
    {
      "name": "param_2",
      "storage": "Stack[0x4]:4",
      "type": "int"
    },
    {
      "name": "iVar1",
      "storage": "unique:00017200:4",
      "type": "int"
    },
    {
      "name": "cVar2",
      "storage": "register:00000000:1",
      "type": "char"
    },
    {
      "name": "local_4",
      "storage": "Stack[-0x4]:4",
      "type": "int"
    },
    {
      "name": "piVar3",
      "storage": "register:00000000:4",
      "type": "int *"
    },
    {
      "name": "iVar4",
      "storage": "register:00000000:4",
      "type": "int"
    },
    {
      "name": "uVar5",
      "storage": "Stack[-0x10]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 8,
  "mode": "live",
  "name": "FUN_00fee930",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xbee930",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00fee930(void)",
  "size_bytes": 290,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00fee930",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 7,
  "xrefs": [
    {
      "from": "00feeb10"
    },
    {
      "from": "00aed6a1"
    },
    {
      "from": "00aed6d5"
    },
    {
      "from": "00feec0f"
    },
    {
      "from": "00feec8f"
    },
    {
      "from": "00feed0f"
    },
    {
      "from": "00fef22a"
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
