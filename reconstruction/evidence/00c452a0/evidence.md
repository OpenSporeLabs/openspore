# Evidence 0x00c452a0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `9ce27ceb8aac3ac85cdfe441d4e8bcd05e915c94d2141ce829d9afd3ec45c1da`

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
    "return_semantics": "pointer_like_in_EAX",
    "saved_registers": [
      "EBX",
      "EDI",
      "ESI"
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -24, so the listing is not one path"
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
  "content_sha256": "b586be1ef547eff7e1af987971eb825ff7b78495ce6db20a25f86f18a6eb7308",
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
    "indirect_calls": 2,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0020",
        "obs-0024",
        "obs-0028",
        "obs-0030"
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
        "obs-0009"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          148,
          152
        ],
        "register": "ECX",
        "written_through": 1
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0009",
        "obs-0020",
        "obs-0024",
        "obs-0028",
        "obs-0030"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0020",
        "obs-0024",
        "obs-0028",
        "obs-0030"
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
        "obs-0020",
        "obs-0024",
        "obs-0028",
        "obs-0030"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0020",
        "obs-0024",
        "obs-0028",
        "obs-0030"
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
      "at": "0x00c452a0",
      "count": 7,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00c452a1",
      "count": 1,
      "first_use": 1,
      "first_write_index": 11,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00c452a1",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00c452ac",
      "definite": true,
      "id": "obs-0004",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESI + 0x94]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00c452b7",
      "count": 4,
      "first_use": 7,
      "first_write_index": 13,
      "id": "obs-0005",
      "index": 7,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00c452b8",
      "count": 5,
      "first_use": 8,
      "first_write_index": 14,
      "id": "obs-0006",
      "index": 8,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00c452b9",
      "count": 5,
      "first_use": 9,
      "first_write_index": 4,
      "id": "obs-0007",
      "index": 9,
      "kind": "REG_READ",
      "raw": "PUSH EAX",
      "reg": "EAX"
    },
    {
      "at": "0x00c452ba",
      "id": "obs-0008",
      "index": 10,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00b3d2a0",
      "target": "0x00b3d2a0"
    },
    {
      "at": "0x00c452bf",
      "definite": true,
      "id": "obs-0009",
      "index": 11,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,EAX",
      "reg": "ECX",
      "write_kind": "reg"
    },
    {
      "at": "0x00c452c1",
      "id": "obs-0010",
      "index": 12,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00ba9370",
      "target": "0x00ba9370"
    },
    {
      "at": "0x00c452c6",
      "definite": true,
      "id": "obs-0011",
      "index": 13,
      "kind": "REG_WRITE",
      "raw": "MOV EBX,dword ptr [ESI + 0x98]",
      "reg": "EBX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00c452cc",
      "definite": true,
      "id": "obs-0012",
      "index": 14,
      "kind": "REG_WRITE",
      "raw": "MOV ED
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
"\nint * __fastcall FUN_00c452a0(int param_1)\n\n{\n  int *piVar1;\n  int *piVar2;\n  int iVar3;\n  \n  if ((*(int *)(param_1 + 0x98) != 0) || (iVar3 = *(int *)(param_1 + 0x94), iVar3 == -1)) {\n    return *(int **)(param_1 + 0x98);\n  }\n  FUN_00b3d2a0(iVar3);\n  piVar2 = (int *)FUN_00ba9370(iVar3);\n  piVar1 = *(int **)(param_1 + 0x98);\n  if (piVar2 == piVar1) {\n    return piVar1;\n  }\n  if (piVar2 != (int *)0x0) {\n    (**(code **)*piVar2)();\n  }\n  *(int **)(param_1 + 0x98) = piVar2;\n  if (piVar1 != (int *)0x0) {\n    (**(code **)(*piVar1 + 4))();\n    return *(int **)(param_1 + 0x98);\n  }\n  return piVar2;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 48,
  "instructions": [
    {
      "address": "00c452a0",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00c452a1",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00c452a3",
      "instruction": "CMP dword ptr [ESI + 0x98],0x0"
    },
    {
      "address": "00c452aa",
      "instruction": "JNZ 0x00c45307"
    },
    {
      "address": "00c452ac",
      "instruction": "MOV EAX,dword ptr [ESI + 0x94]"
    },
    {
      "address": "00c452b2",
      "instruction": "CMP EAX,-0x1"
    },
    {
      "address": "00c452b5",
      "instruction": "JZ 0x00c45307"
    },
    {
      "address": "00c452b7",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00c452b8",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00c452b9",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00c452ba",
      "instruction": "CALL 0x00b3d2a0"
    },
    {
      "address": "00c452bf",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00c452c1",
      "instruction": "CALL 0x00ba9370"
    },
    {
      "address": "00c452c6",
      "instruction": "MOV EBX,dword ptr [ESI + 0x98]"
    },
    {
      "address": "00c452cc",
      "instruction": "MOV EDI,EAX"
    },
    {
      "address": "00c452ce",
      "instruction": "CMP EDI,EBX"
    },
    {
      "address": "00c452d0",
      "instruction": "JZ 0x00c45301"
    },
    {
      "address": "00c452d2",
      "instruction": "TEST EDI,EDI"
    },
    {
      "address": "00c452d4",
      "instruction": "JZ 0x00c452de"
    },
    {
      "address": "00c452d6",
      "instruction": "MOV EAX,dword ptr [EDI]"
    },
    {
      "address": "00c452d8",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00c452da",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00c452dc",
      "instruction": "CALL EDX"
    },
    {
      "address": "00c452de",
      "instruction": "MOV dword ptr [ESI + 0x98],EDI"
    },
    {
      "address": "00c452e4",
      "instruction": "TEST EBX,EBX"
    },
    {
      "address": "00c452e6",
      "instruction": "JZ 0x00c452fb"
    },
    {
      "address": "00c452e8",
      "instruction": "MOV EAX,dword ptr [EBX]"
    },
    {
      "address": "00c452ea",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "00c452ed",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "00c452ef",
      "instruction": "CALL EDX"
    },
    {
      "address": "00c452f1",
      "instruction": "MOV EAX,dword ptr [ESI + 0x98]"
    },
    {
      "address": "00c452f7",
      "instruction": "POP EDI"
    },
    {
      "address": "00c452f8",
      "instruction": "POP EBX"
    },
    {
      "address": "00c452f9",
      "instruction": "POP ESI"
    },
    {
      "address": "00c452fa",
      "instruction": "RET"
    },
    {
      "address": "00c452fb",
      "instruction": "MOV EAX,EDI"
    },
    {
      "address": "00c452fd",
      "instruction": "POP EDI"
    },
    {
      "address": "00c452fe",
      "instruction": "POP EBX"
    },
    {
      "address": "00c452ff",
      "instruction": "POP ESI"
    },
    {
      "address": "00c45300",
      "instruction": "RET"
    },
    {
      "address": "00c45301",
      "instruction": "POP EDI"
    },
    {
      "address": "00c45302",
      "instruction": "MOV EAX,EBX"
    },
    {
      "address": "00c45304",
      "instruction": "POP EBX"
    },
    {
      "address": "00c45305",
      "instruction": "POP ESI"
    },
    {
      "address": "00c45306",
      "instruction": "RET"
    },
    {
      "address": "00c45307",
      "instruction": "MOV EAX,dword ptr [ESI + 0x98]"
    },
    {
      "address": "00c4530d",
      "instruction": "POP ESI"
    },
    {
      "address": "00c4530e",
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
  "body_end": "00c4530e",
  "body_span_bytes": 111,
  "body_start": "00c452a0",
  "callees": [
    "FUN_00ba9370",
    "FUN_00b3d2a0"
  ],
  "callers": [
    "FUN_00c487d0",
    "FUN_00c631f0",
    "FUN_00c486f0",
    "FUN_00c635c0",
    "FUN_00c637b0",
    "FUN_00c49140",
    "FUN_00c484e0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00c452a0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "piVar1",
      "storage": "unique:00017200:4",
      "type": "int *"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int"
    },
    {
      "name": "iVar3",
      "storage": "Stack[-0x10]:4",
      "type": "int"
    },
    {
      "name": "piVar2",
      "storage": "register:00000000:4",
      "type": "int *"
    }
  ],
  "locals_count": 4,
  "mode": "live",
  "name": "FUN_00c452a0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x8452a0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00c452a0(void)",
  "size_bytes": 111,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00c452a0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 7,
  "xrefs": [
    {
      "from": "00c48512"
    },
    {
      "from": "00c4881c"
    },
    {
      "from": "00c486f0"
    },
    {
      "from": "00c49141"
    },
    {
      "from": "00c632ea"
    },
    {
      "from": "00c635d1"
    },
    {
      "from": "00c638e6"
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
