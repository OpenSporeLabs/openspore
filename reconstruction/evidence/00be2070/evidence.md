# Evidence 0x00be2070

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `5c023527a728f5bc1ecfa5245daeb1b91e4b312eea57176dc524183205b97215`

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
    "ret_form": "RET 0x8",
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
    "stack_cleanup_bytes": 8,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x8"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +12, so the listing is not one path"
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
  "content_sha256": "0aa893032db7f1990cd1ca6eb7cf33c53e1723377051b06c9dbe988c9456470b",
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
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0029"
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
        "obs-0008"
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
        "obs-0002",
        "obs-0003",
        "obs-0010",
        "obs-0011",
        "obs-0012",
        "obs-0019"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          852,
          856
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0010",
        "obs-0011",
        "obs-0012",
        "obs-0019",
        "obs-0029"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0029"
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
        "obs-0029"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0029"
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
      "at": "0x00be2070",
      "count": 6,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00be2071",
      "count": 6,
      "first_use": 1,
      "first_write_index": 11,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EBX,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00be2071",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EBX,ECX",
      "reg": "EBX",
      "write_kind": "reg"
    },
    {
      "at": "0x00be2073",
      "definite": true,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [EBX + 0x354]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00be207f",
      "count": 3,
      "first_use": 4,
      "first_write_index": null,
      "id": "obs-0005",
      "index": 4,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00be2088",
      "count": 4,
      "first_use": 7,
      "first_write_index": 8,
      "id": "obs-0006",
      "index": 7,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00be2089",
      "count": 5,
      "first_use": 8,
      "first_write_index": 39,
      "id": "obs-0007",
      "index": 8,
      "kind": "REG_READ",
      "raw": "MOV ESI,dword ptr [ESP + 0x10]",
      "reg": "ESP"
    },
    {
      "at": "0x00be2089",
      "base": "ESP",
      "disp": 16,
      "id": "obs-0008",
      "index": 8,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV ESI,dword ptr [ESP + 0x10]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00be2089",
      "definite": true,
   
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
"\nvoid __thiscall FUN_00be2070(int param_1,int param_2,undefined4 param_3)\n\n{\n  int *piVar1;\n  undefined *puVar2;\n  int iVar3;\n  \n  if ((*(int **)(param_1 + 0x354) != *(int **)(param_1 + 0x358)) &&\n     ((param_2 != 0 ||\n      (((iVar3 = **(int **)(param_1 + 0x354), iVar3 != 0 &&\n        (piVar1 = (int *)(iVar3 + 0x588), piVar1 != (int *)0x0)) &&\n       (param_2 = (**(code **)(*piVar1 + 0x5c))(0x436f315), param_2 != 0)))))) {\n    iVar3 = param_2;\n    FUN_00afae50(param_2);\n    FUN_00b3d300(iVar3);\n    FUN_00b225d0(iVar3);\n    FUN_00d5aae0(param_1 + 0x354,&param_2,param_3);\n    if (((char)param_3 == '\\0') && (puVar2 = (undefined *)FUN_00b5b800(), puVar2 == &DAT_01654c05))\n    {\n      FUN_00bd9e50();\n    }\n  }\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 51,
  "instructions": [
    {
      "address": "00be2070",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00be2071",
      "instruction": "MOV EBX,ECX"
    },
    {
      "address": "00be2073",
      "instruction": "MOV EAX,dword ptr [EBX + 0x354]"
    },
    {
      "address": "00be2079",
      "instruction": "CMP EAX,dword ptr [EBX + 0x358]"
    },
    {
      "address": "00be207f",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00be2080",
      "instruction": "LEA EDI,[EBX + 0x354]"
    },
    {
      "address": "00be2086",
      "instruction": "JZ 0x00be2100"
    },
    {
      "address": "00be2088",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00be2089",
      "instruction": "MOV ESI,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00be208d",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "00be208f",
      "instruction": "JNZ 0x00be20b9"
    },
    {
      "address": "00be2091",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00be2093",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "00be2095",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00be2097",
      "instruction": "JZ 0x00be20ff"
    },
    {
      "address": "00be2099",
      "instruction": "LEA ECX,[EAX + 0x588]"
    },
    {
      "address": "00be209f",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00be20a1",
      "instruction": "JZ 0x00be20ff"
    },
    {
      "address": "00be20a3",
      "instruction": "MOV EDX,dword ptr [ECX]"
    },
    {
      "address": "00be20a5",
      "instruction": "MOV EAX,dword ptr [EDX + 0x5c]"
    },
    {
      "address": "00be20a8",
      "instruction": "PUSH 0x436f315"
    },
    {
      "address": "00be20ad",
      "instruction": "CALL EAX"
    },
    {
      "address": "00be20af",
      "instruction": "MOV ESI,EAX"
    },
    {
      "address": "00be20b1",
      "instruction": "MOV dword ptr [ESP + 0x10],ESI"
    },
    {
      "address": "00be20b5",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "00be20b7",
      "instruction": "JZ 0x00be20ff"
    },
    {
      "address": "00be20b9",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00be20ba",
      "instruction": "LEA ECX,[EBX + 0x4b4]"
    },
    {
      "address": "00be20c0",
      "instruction": "CALL 0x00afae50"
    },
    {
      "address": "00be20c5",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00be20c6",
      "instruction": "CALL 0x00b3d300"
    },
    {
      "address": "00be20cb",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00be20cd",
      "instruction": "CALL 0x00b225d0"
    },
    {
      "address": "00be20d2",
      "instruction": "MOV ECX,dword ptr [ESP + 0x14]"
    },
    {
      "address": "00be20d6",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00be20d7",
      "instruction": "LEA EDX,[ESP + 0x14]"
    },
    {
      "address": "00be20db",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00be20dc",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00be20dd",
      "instruction": "CALL 0x00d5aae0"
    },
    {
      "address": "00be20e2",
      "instruction": "ADD ESP,0xc"
    },
    {
      "address": "00be20e5",
      "instruction": "CMP byte ptr [ESP + 0x14],0x0"
    },
    {
      "address": "00be20ea",
      "instruction": "JNZ 0x00be20ff"
    },
    {
      "address": "00be20ec",
      "instruction": "CALL 0x00b5b800"
    },
    {
      "address": "00be20f1",
      "instruction": "CMP EAX,0x1654c05"
    },
    {
      "address": "00be20f6",
      "instruction": "JNZ 0x00be20ff"
    },
    {
      "address": "00be20f8",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "00be20fa",
      "instruction": "CALL 0x00bd9e50"
    },
    {
      "address": "00be20ff",
      "instruction": "POP ESI"
    },
    {
      "address": "00be2100",
      "instruction": "POP EDI"
    },
    {
      "address": "00be2101",
      "instruction": "POP EBX"
    },
    {
      "address": "00be2102",
      "instruction": "RET 0x8"
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
  "body_end": "00be2104",
  "body_span_bytes": 149,
  "body_start": "00be2070",
  "callees": [
    "FUN_00d5aae0",
    "FUN_00b5b800",
    "FUN_00afae50",
    "FUN_00b225d0",
    "FUN_00b3d300",
    "FUN_00bd9e50"
  ],
  "callers": [
    "FUN_00ff5720",
    "FUN_00d09d30",
    "FUN_00be5dd0",
    "FUN_00be3ad0",
    "FUN_00c8c0f0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00be2070",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "piVar1",
      "storage": "unique:00006800:4",
      "type": "int *"
    },
    {
      "name": "param_3",
      "storage": "Stack[0x8]:4",
      "type": "undefined4"
    },
    {
      "name": "iVar3",
      "storage": "Stack[-0x10]:4",
      "type": "int"
    },
    {
      "name": "puVar2",
      "storage": "register:00000000:4",
      "type": "undefined *"
    },
    {
      "name": "param_2",
      "storage": "Stack[0x4]:4",
      "type": "int"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int"
    }
  ],
  "locals_count": 6,
  "mode": "live",
  "name": "FUN_00be2070",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x7e2070",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00be2070(void)",
  "size_bytes": 149,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00be2070",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 7,
  "xrefs": [
    {
      "from": "00be3dcc"
    },
    {
      "from": "00be5e0e"
    },
    {
      "from": "00c8c1d6"
    },
    {
      "from": "00d09de1"
    },
    {
      "from": "00ff579e"
    },
    {
      "from": "00bd09bb"
    },
    {
      "from": "0100be63"
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
