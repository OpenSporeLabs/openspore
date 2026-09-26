# Evidence 0x00b3dcd0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `e17a54eb30382daba5dc4a730abdc258e51662033dfca0555bf74c55789df559`

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
    "ret_form": "RET",
    "return_register": "ST0",
    "return_semantics": "float_or_x87_in_ST0",
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
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -12, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate",
    "side": "caller"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "ced1d4708bdfd9246ef84ee388ffaa1235b17b4596b15f9f8032702311624832",
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
        "obs-0005",
        "obs-0011",
        "obs-0018",
        "obs-0021"
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
        "obs-0015",
        "obs-0016"
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
        "obs-0002",
        "obs-0004",
        "obs-0006",
        "obs-0007",
        "obs-0010",
        "obs-0017",
        "obs-0020"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          4,
          64,
          177
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0002",
        "obs-0004",
        "obs-0005",
        "obs-0006",
        "obs-0007",
        "obs-0010",
        "obs-0011",
        "obs-0017",
        "obs-0018",
        "obs-0020",
        "obs-0021"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0005",
        "obs-0011",
        "obs-0018",
        "obs-0021"
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
        "obs-0021"
      ],
      "claim": "the return value is carried in ST0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "ST0"
    }
  ],
  "observations": [
    {
      "at": "0x00b3dcd0",
      "count": 6,
      "first_use": 0,
      "first_write_index": 12,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00b3dcd1",
      "definite": true,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ECX + 0x4]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00b3dce1",
      "count": 10,
      "first_use": 7,
      "first_write_index": 1,
      "id": "obs-0003",
      "index": 7,
      "kind": "REG_READ",
      "raw": "CMP byte ptr [EAX + 0x71],0x0",
      "reg": "EAX"
    },
    {
      "at": "0x00b3dce9",
      "id": "obs-0004",
      "index": 10,
      "kind": "REG_RESTORE",
      "raw": "POP ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00b3dcea",
      "form": "RET",
      "id": "obs-0005",
      "imm": null,
      "index": 11,
      "kind": "RET",
      "raw": "RET"
    },
    {
      "at": "0x00b3dceb",
      "definite": true,
      "id": "obs-0006",
      "index": 12,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,EAX",
      "reg": "ECX",
      "write_kind": "reg"
    },
    {
      "at": "0x00b3dced",
      "definite": true,
      "id": "obs-0007",
      "index": 13,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [ECX]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00b3dcef",
      "count": 4,
      "first_use": 14,
      "first_write_index": 13,
      "id": "obs-0008",
      "index": 14,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [EDX + 0x68]",
      "reg": "EDX"
    },
    {
      "at": "0x00b3dcf2",
      "base": "EAX",
      "disp": null,
      "id": "obs-0009",
      "in
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
"\n/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */\n\nfloat10 __fastcall FUN_00b3dcd0(int param_1)\n\n{\n  float *pfVar1;\n  float10 fVar2;\n  \n  if (*(int *)(param_1 + 4) == 0) {\n    if (*(char *)((int)*(int **)(param_1 + 0x40) + 0x71) != '\\0') {\n      return (float10)0.0;\n    }\n    fVar2 = (float10)(**(code **)(**(int **)(param_1 + 0x40) + 0xd8))(param_1);\n    return (float10)1 / fVar2;\n  }\n  if ((*(int *)(param_1 + 4) == 1) && (*(char *)((int)*(int **)(param_1 + 0x40) + 0x71) == '\\0')) {\n    pfVar1 = (float *)(**(code **)(**(int **)(param_1 + 0x40) + 0x68))();\n    return (float10)1 /\n           (((float10)pfVar1[3] - (float10)*pfVar1) * ((float10)pfVar1[4] - (float10)pfVar1[1]) *\n            ((float10)pfVar1[5] - (float10)pfVar1[2]) * (float10)_DAT_015695fc);\n  }\n  return (float10)0;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 46,
  "instructions": [
    {
      "address": "00b3dcd0",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00b3dcd1",
      "instruction": "MOV EAX,dword ptr [ECX + 0x4]"
    },
    {
      "address": "00b3dcd4",
      "instruction": "SUB EAX,0x0"
    },
    {
      "address": "00b3dcd7",
      "instruction": "JZ 0x00b3dd17"
    },
    {
      "address": "00b3dcd9",
      "instruction": "SUB EAX,0x1"
    },
    {
      "address": "00b3dcdc",
      "instruction": "JNZ 0x00b3dce7"
    },
    {
      "address": "00b3dcde",
      "instruction": "MOV EAX,dword ptr [ECX + 0x40]"
    },
    {
      "address": "00b3dce1",
      "instruction": "CMP byte ptr [EAX + 0x71],0x0"
    },
    {
      "address": "00b3dce5",
      "instruction": "JZ 0x00b3dceb"
    },
    {
      "address": "00b3dce7",
      "instruction": "FLDZ"
    },
    {
      "address": "00b3dce9",
      "instruction": "POP ECX"
    },
    {
      "address": "00b3dcea",
      "instruction": "RET"
    },
    {
      "address": "00b3dceb",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00b3dced",
      "instruction": "MOV EDX,dword ptr [ECX]"
    },
    {
      "address": "00b3dcef",
      "instruction": "MOV EAX,dword ptr [EDX + 0x68]"
    },
    {
      "address": "00b3dcf2",
      "instruction": "CALL EAX"
    },
    {
      "address": "00b3dcf4",
      "instruction": "FLD float ptr [EAX + 0xc]"
    },
    {
      "address": "00b3dcf7",
      "instruction": "FSUB float ptr [EAX]"
    },
    {
      "address": "00b3dcf9",
      "instruction": "FLD float ptr [EAX + 0x10]"
    },
    {
      "address": "00b3dcfc",
      "instruction": "FSUB float ptr [EAX + 0x4]"
    },
    {
      "address": "00b3dcff",
      "instruction": "FLD float ptr [EAX + 0x14]"
    },
    {
      "address": "00b3dd02",
      "instruction": "FSUB float ptr [EAX + 0x8]"
    },
    {
      "address": "00b3dd05",
      "instruction": "FXCH ST2"
    },
    {
      "address": "00b3dd07",
      "instruction": "FMULP"
    },
    {
      "address": "00b3dd09",
      "instruction": "FMULP"
    },
    {
      "address": "00b3dd0b",
      "instruction": "FMUL float ptr [0x015695fc]"
    },
    {
      "address": "00b3dd11",
      "instruction": "FLD1"
    },
    {
      "address": "00b3dd13",
      "instruction": "FDIVRP"
    },
    {
      "address": "00b3dd15",
      "instruction": "POP ECX"
    },
    {
      "address": "00b3dd16",
      "instruction": "RET"
    },
    {
      "address": "00b3dd17",
      "instruction": "MOV EDX,dword ptr [ECX + 0x40]"
    },
    {
      "address": "00b3dd1a",
      "instruction": "CMP byte ptr [EDX + 0x71],0x0"
    },
    {
      "address": "00b3dd1e",
      "instruction": "JZ 0x00b3dd2d"
    },
    {
      "address": "00b3dd20",
      "instruction": "XORPS XMM0,XMM0"
    },
    {
      "address": "00b3dd23",
      "instruction": "MOVSS dword ptr [ESP],XMM0"
    },
    {
      "address": "00b3dd28",
      "instruction": "FLD float ptr [ESP]"
    },
    {
      "address": "00b3dd2b",
      "instruction": "POP ECX"
    },
    {
      "address": "00b3dd2c",
      "instruction": "RET"
    },
    {
      "address": "00b3dd2d",
      "instruction": "MOV ECX,EDX"
    },
    {
      "address": "00b3dd2f",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "00b3dd31",
      "instruction": "MOV EDX,dword ptr [EAX + 0xd8]"
    },
    {
      "address": "00b3dd37",
      "instruction": "CALL EDX"
    },
    {
      "address": "00b3dd39",
      "instruction": "FLD1"
    },
    {
      "address": "00b3dd3b",
      "instruction": "FDIVRP"
    },
    {
      "address": "00b3dd3d",
      "instruction": "POP ECX"
    },
    {
      "address": "00b3dd3e",
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
  "body_end": "00b3dd3e",
  "body_span_bytes": 111,
  "body_start": "00b3dcd0",
  "callees": [],
  "callers": [
    "FUN_00b43290",
    "FUN_00b46660",
    "FUN_00b3faa0",
    "FUN_00b45ca0",
    "FUN_00b3dec0",
    "FUN_00b4bc20",
    "FUN_00b3f940"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "00b3dcd0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "pfVar1",
      "storage": "register:00000000:4",
      "type": "float *"
    },
    {
      "name": "fVar2",
      "storage": "register:00001100:10",
      "type": "float10"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int"
    }
  ],
  "locals_count": 3,
  "mode": "live",
  "name": "FUN_00b3dcd0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x73dcd0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00b3dcd0(void)",
  "size_bytes": 111,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00b3dcd0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 8,
  "xrefs": [
    {
      "from": "00b43654"
    },
    {
      "from": "00b3faa6"
    },
    {
      "from": "00b3dec4"
    },
    {
      "from": "00b45ca6"
    },
    {
      "from": "00b3f944"
    },
    {
      "from": "00b46669"
    },
    {
      "from": "00b4bc8e"
    },
    {
      "from": "00b4bc99"
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
