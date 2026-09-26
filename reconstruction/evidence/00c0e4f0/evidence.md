# Evidence 0x00c0e4f0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `2fb7ca8e2e088c4412cc206c24cb92e89fa89f47b7ffbb9b9c657764b4961b97`

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
    "return_register": "ST0",
    "return_semantics": "float_or_x87_in_ST0",
    "saved_registers": [
      "ESI"
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -12, so the listing is not one path",
    "unparsed_lines_present: 1 line(s) matched no grammar rule"
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
  "content_sha256": "5fa35973e4e8881402b437e828dcf259b5a8cb88ebb5a434fa7eac4fa7a31911",
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
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0014",
        "obs-0023",
        "obs-0026"
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
        "obs-0001",
        "obs-0003",
        "obs-0009",
        "obs-0013",
        "obs-0022",
        "obs-0025"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          0,
          2904,
          3716
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0003",
        "obs-0009",
        "obs-0013",
        "obs-0014",
        "obs-0022",
        "obs-0023",
        "obs-0025",
        "obs-0026"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0014",
        "obs-0023",
        "obs-0026"
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
        "obs-0026"
      ],
      "claim": "the return value is carried in ST0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "ST0"
    }
  ],
  "observations": [
    {
      "at": "0x00c0e4f0",
      "count": 3,
      "first_use": 0,
      "first_write_index": 14,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00c0e4f1",
      "count": 6,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00c0e4f2",
      "definite": true,
      "id": "obs-0003",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00c0e4f4",
      "id": "obs-0004",
      "index": 3,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00b5b800",
      "target": "0x00b5b800"
    },
    {
      "at": "0x00c0e500",
      "definite": true,
      "id": "obs-0005",
      "index": 6,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,[0x016c7aa4]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00c0e505",
      "count": 4,
      "first_use": 7,
      "first_write_index": 6,
      "id": "obs-0006",
      "index": 7,
      "kind": "REG_READ",
      "raw": "CMP dword ptr [EAX + 0xcc],0x2",
      "reg": "EAX"
    },
    {
      "at": "0x00c0e512",
      "definite": true,
      "id": "obs-0007",
      "index": 11,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [ESI]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00c0e514",
      "count": 1,
      "first_use": 12,
      "first_write_index": 11,
      "id": "obs-0008",
      "index": 12,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [EDX + 0xc]",
      "reg": "EDX"
    },
    {
      "at": "0x00c0e51c",
      "definite": true,
      "id": "obs-0009",
      "index": 14,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,ESI",
      "reg": "ECX",
      "write_kind": "reg"
    },
    {
      "at": "0x00c0e51e",
      "base": "EAX",
      "disp": null,
      "id": "obs-0010",
      "index": 15,
      "kind": "CALL_INDIRECT",
      "raw": "CALL EAX",
      "via": "register"
    },
    {
      "at": "0x00c0e534",
      "id": "obs-0011",
      "index": 23,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00c04750",
      "target": "0x00c04750"
    },
    {
      "at": "0x00c0e543",
      "id": "obs-0012",
      "index": 27,
      "kind": "REG_RESTORE",
      "raw": "POP ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00c0e544",
      "id": "obs-0013",
      "index": 28,
      "kind": "REG_RESTORE",
      "raw": "POP ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00c0e545",
      "f
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
"\n/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */\n\nfloat10 __fastcall FUN_00c0e4f0(int *param_1)\n\n{\n  float fVar1;\n  undefined *puVar2;\n  int iVar3;\n  \n  puVar2 = (undefined *)FUN_00b5b800();\n  if (((puVar2 == &DAT_01654c10) && (*(int *)(App__sScenarioMode + 0xcc) == 2)) &&\n     (param_1 != (int *)0x0)) {\n    iVar3 = (**(code **)(*param_1 + 0xc))(0xd0036e08);\n    if ((iVar3 != 0) && (((uint)param_1[0x2d6] >> 9 & 1) == 0)) {\n      iVar3 = FUN_00c04750();\n      if (iVar3 != 0) {\n        return (float10)*(float *)(iVar3 + 0x484);\n      }\n    }\n  }\n  if ((param_1[0x3a1] != 0) && (fVar1 = *(float *)(param_1[0x3a1] + 0x34c), 0.0 <= fVar1)) {\n    return (float10)fVar1;\n  }\n  return (float10)_DAT_0150c8bc;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 45,
  "instructions": [
    {
      "address": "00c0e4f0",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00c0e4f1",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00c0e4f2",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00c0e4f4",
      "instruction": "CALL 0x00b5b800"
    },
    {
      "address": "00c0e4f9",
      "instruction": "CMP EAX,0x1654c10"
    },
    {
      "address": "00c0e4fe",
      "instruction": "JNZ 0x00c0e546"
    },
    {
      "address": "00c0e500",
      "instruction": "MOV EAX,[0x016c7aa4]"
    },
    {
      "address": "00c0e505",
      "instruction": "CMP dword ptr [EAX + 0xcc],0x2"
    },
    {
      "address": "00c0e50c",
      "instruction": "JNZ 0x00c0e546"
    },
    {
      "address": "00c0e50e",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "00c0e510",
      "instruction": "JZ 0x00c0e546"
    },
    {
      "address": "00c0e512",
      "instruction": "MOV EDX,dword ptr [ESI]"
    },
    {
      "address": "00c0e514",
      "instruction": "MOV EAX,dword ptr [EDX + 0xc]"
    },
    {
      "address": "00c0e517",
      "instruction": "PUSH 0xd0036e08"
    },
    {
      "address": "00c0e51c",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00c0e51e",
      "instruction": "CALL EAX"
    },
    {
      "address": "00c0e520",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00c0e522",
      "instruction": "JZ 0x00c0e546"
    },
    {
      "address": "00c0e524",
      "instruction": "MOV ECX,dword ptr [ESI + 0xb58]"
    },
    {
      "address": "00c0e52a",
      "instruction": "SHR ECX,0x9"
    },
    {
      "address": "00c0e52d",
      "instruction": "TEST CL,0x1"
    },
    {
      "address": "00c0e530",
      "instruction": "JNZ 0x00c0e546"
    },
    {
      "address": "00c0e532",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00c0e534",
      "instruction": "CALL 0x00c04750"
    },
    {
      "address": "00c0e539",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00c0e53b",
      "instruction": "JZ 0x00c0e546"
    },
    {
      "address": "00c0e53d",
      "instruction": "FLD float ptr [EAX + 0x484]"
    },
    {
      "address": "00c0e543",
      "instruction": "POP ESI"
    },
    {
      "address": "00c0e544",
      "instruction": "POP ECX"
    },
    {
      "address": "00c0e545",
      "instruction": "RET"
    },
    {
      "address": "00c0e546",
      "instruction": "MOV ESI,dword ptr [ESI + 0xe84]"
    },
    {
      "address": "00c0e54c",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "00c0e54e",
      "instruction": "JZ 0x00c0e56e"
    },
    {
      "address": "00c0e550",
      "instruction": "MOVSS XMM0,dword ptr [ESI + 0x34c]"
    },
    {
      "address": "00c0e558",
      "instruction": "COMISS XMM0,dword ptr [0x01485378]"
    },
    {
      "address": "00c0e55f",
      "instruction": "MOVSS dword ptr [ESP + 0x4],XMM0"
    },
    {
      "address": "00c0e565",
      "instruction": "JC 0x00c0e56e"
    },
    {
      "address": "00c0e567",
      "instruction": "FLD float ptr [ESP + 0x4]"
    },
    {
      "address": "00c0e56b",
      "instruction": "POP ESI"
    },
    {
      "address": "00c0e56c",
      "instruction": "POP ECX"
    },
    {
      "address": "00c0e56d",
      "instruction": "RET"
    },
    {
      "address": "00c0e56e",
      "instruction": "FLD float ptr [0x0150c8bc]"
    },
    {
      "address": "00c0e574",
      "instruction": "POP ESI"
    },
    {
      "address": "00c0e575",
      "instruction": "POP ECX"
    },
    {
      "address": "00c0e576",
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
  "body_end": "00c0e576",
  "body_span_bytes": 135,
  "body_start": "00c0e4f0",
  "callees": [
    "FUN_00c04750",
    "FUN_00b5b800"
  ],
  "callers": [
    "FUN_00c11480",
    "FUN_00c09410",
    "FUN_00c03950",
    "FUN_00c08350"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00c0e4f0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "iVar3",
      "storage": "register:00000000:4",
      "type": "int"
    },
    {
      "name": "puVar2",
      "storage": "register:00000000:4",
      "type": "undefined *"
    },
    {
      "name": "fVar1",
      "storage": "unique:0000a300:4",
      "type": "float"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int *"
    }
  ],
  "locals_count": 4,
  "mode": "live",
  "name": "FUN_00c0e4f0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x80e4f0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00c0e4f0(void)",
  "size_bytes": 135,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00c0e4f0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 6,
  "xrefs": [
    {
      "from": "00c03ae3"
    },
    {
      "from": "00c086bc"
    },
    {
      "from": "00c090de"
    },
    {
      "from": "00c09475"
    },
    {
      "from": "00c114ea"
    },
    {
      "from": "00c03ba7"
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
