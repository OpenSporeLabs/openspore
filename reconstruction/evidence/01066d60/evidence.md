# Evidence 0x01066d60

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `d9413cbc3f7896fccbe022556037e6896d74b9dbf79abf864d078b9f3dfd5456`

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
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
    "saved_registers": [
      "ESI"
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +16, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "adfda9aba594cededf88df2adb80851eb42fa3a5436129fa7d8f9b719ed9779b",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall",
      "__fastcall"
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
        "obs-0018"
      ],
      "claim": "the caller cleans up the stack: a bare RET is compatible with caller cleanup and, for a zero-parameter __stdcall, with zero bytes of callee cleanup",
      "confidence": "INFERRED",
      "id": "C5",
      "value": {
        "bytes": 0,
        "side": "caller"
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0004",
        "obs-0006"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          548,
          1476
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0004",
        "obs-0006",
        "obs-0018"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0018"
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
        "obs-0018"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0018"
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
      "at": "0x01066d60",
      "count": 4,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x01066d61",
      "count": 4,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x01066d61",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x01066d63",
      "definite": true,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [ESI + 0x224]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x01066d69",
      "id": "obs-0005",
      "index": 3,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00e01380",
      "target": "0x00e01380"
    },
    {
      "at": "0x01066d7c",
      "definite": true,
      "id": "obs-0006",
      "index": 9,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ECX]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x01066d7e",
      "count": 5,
      "first_use": 10,
      "first_write_index": 9,
      "id": "obs-0007",
      "index": 10,
      "kind": "REG_READ",
      "raw": "MOV EDX,dword ptr [EAX + 0x18]",
      "reg": "EAX"
    },
    {
      "at": "0x01066d7e",
      "definite": true,
      "id": "obs-0008",
      "index": 10,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [EAX + 0x18]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x01066d81",
      "count": 4,
      "first_use": 11,
      "first_write_index": 10,
      "id": "obs-0009",
      "index": 11,
      "kind": "REG_READ",
      "raw": "CALL EDX",
      "reg": "EDX"
    },
    {
      "at": "0x01066d81",
      "base": "EDX",
      "disp": null,
      "id": "obs-0010",
      "index": 11,
      "kind": "CALL_INDIRECT",
      "raw": "CALL EDX",
      "via": "register"
    },
    {
      "at": "0x01066d83",
      "id": "obs-0011",
      "index": 12,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00b3d230",
      "target": "0x00b3d230"
    },
    {
      "at": "0x01066d96",
      "base": "EDX",
      "disp": null,
      "id": "obs-0012",
      "index": 18,
      "kind": "CALL_INDIRECT",
      "raw": "CALL EDX",
      "via": "register"
    },
    {
      "at": "0x01066da0",
      "id": "obs-0013",
      "index": 21,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00e01350",
      "target": "0x00e01350"
    },
    {
      "at": "0x010
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
"\nvoid __fastcall FUN_01066d60(int param_1)\n\n{\n  char cVar1;\n  int *piVar2;\n  undefined4 uVar3;\n  \n  cVar1 = FUN_00e01380();\n  if (cVar1 != '\\0') {\n    if (DAT_016e2234 != (int *)0x0) {\n      (**(code **)(*DAT_016e2234 + 0x18))();\n    }\n    piVar2 = (int *)FUN_00b3d230();\n    (**(code **)(*piVar2 + 0x40))(DAT_016e2234);\n    FUN_00e01350(0);\n    uVar3 = 0;\n    FUN_00b3d3e0(0);\n    FUN_00dd8da0(uVar3);\n    if (*(int **)(param_1 + 0x5c4) != (int *)0x0) {\n      (**(code **)(**(int **)(param_1 + 0x5c4) + 0xc0))(0);\n    }\n  }\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 35,
  "instructions": [
    {
      "address": "01066d60",
      "instruction": "PUSH ESI"
    },
    {
      "address": "01066d61",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "01066d63",
      "instruction": "MOV ECX,dword ptr [ESI + 0x224]"
    },
    {
      "address": "01066d69",
      "instruction": "CALL 0x00e01380"
    },
    {
      "address": "01066d6e",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "01066d70",
      "instruction": "JZ 0x01066dc9"
    },
    {
      "address": "01066d72",
      "instruction": "MOV ECX,dword ptr [0x016e2234]"
    },
    {
      "address": "01066d78",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "01066d7a",
      "instruction": "JZ 0x01066d83"
    },
    {
      "address": "01066d7c",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "01066d7e",
      "instruction": "MOV EDX,dword ptr [EAX + 0x18]"
    },
    {
      "address": "01066d81",
      "instruction": "CALL EDX"
    },
    {
      "address": "01066d83",
      "instruction": "CALL 0x00b3d230"
    },
    {
      "address": "01066d88",
      "instruction": "MOV ECX,dword ptr [0x016e2234]"
    },
    {
      "address": "01066d8e",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "01066d90",
      "instruction": "MOV EDX,dword ptr [EDX + 0x40]"
    },
    {
      "address": "01066d93",
      "instruction": "PUSH ECX"
    },
    {
      "address": "01066d94",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "01066d96",
      "instruction": "CALL EDX"
    },
    {
      "address": "01066d98",
      "instruction": "MOV ECX,dword ptr [ESI + 0x224]"
    },
    {
      "address": "01066d9e",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "01066da0",
      "instruction": "CALL 0x00e01350"
    },
    {
      "address": "01066da5",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "01066da7",
      "instruction": "CALL 0x00b3d3e0"
    },
    {
      "address": "01066dac",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "01066dae",
      "instruction": "CALL 0x00dd8da0"
    },
    {
      "address": "01066db3",
      "instruction": "MOV ECX,dword ptr [ESI + 0x5c4]"
    },
    {
      "address": "01066db9",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "01066dbb",
      "instruction": "JZ 0x01066dc9"
    },
    {
      "address": "01066dbd",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "01066dbf",
      "instruction": "MOV EDX,dword ptr [EAX + 0xc0]"
    },
    {
      "address": "01066dc5",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "01066dc7",
      "instruction": "CALL EDX"
    },
    {
      "address": "01066dc9",
      "instruction": "POP ESI"
    },
    {
      "address": "01066dca",
      "instruction": "RET"
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
  "body_end": "01066dca",
  "body_span_bytes": 107,
  "body_start": "01066d60",
  "callees": [
    "FUN_00b3d230",
    "FUN_00b3d3e0",
    "FUN_00dd8da0",
    "FUN_00e01380",
    "FUN_00e01350"
  ],
  "callers": [
    "FUN_00ff74f0",
    "FUN_00c3c520",
    "FUN_00fe0160"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "01066d60",
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
      "name": "uVar3",
      "storage": "Stack[-0xc]:4",
      "type": "undefined4"
    },
    {
      "name": "cVar1",
      "storage": "register:00000000:1",
      "type": "char"
    },
    {
      "name": "piVar2",
      "storage": "register:00000000:4",
      "type": "int *"
    }
  ],
  "locals_count": 4,
  "mode": "live",
  "name": "FUN_01066d60",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xc66d60",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_01066d60(void)",
  "size_bytes": 107,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x01066d60",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 4,
  "xrefs": [
    {
      "from": "00c3c660"
    },
    {
      "from": "00fe0469"
    },
    {
      "from": "00ff751d"
    },
    {
      "from": "0100cd61"
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
