# Evidence 0x00b21da0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `c216529ce5714277750d3f452d722d9c4a7867bdf27cf1faa4bf5706a6aa8033`

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
    "flow_not_modelled: the linear ESP walk ends at -24, so the listing is not one path",
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
  "content_sha256": "f97009dbc38fc04646589a83f8fe88e9e81137f8cb45718b9339ad8b7ce243ef",
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
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0018",
        "obs-0022",
        "obs-0026"
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
        "obs-0002"
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
        "obs-0004",
        "obs-0005",
        "obs-0013",
        "obs-0014"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          4,
          8,
          12,
          20
        ],
        "register": "ECX",
        "written_through": 6
      }
    },
    {
      "based_on": [
        "obs-0004",
        "obs-0005",
        "obs-0013",
        "obs-0014",
        "obs-0018",
        "obs-0022",
        "obs-0026"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0002"
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
        "obs-0018",
        "obs-0022",
        "obs-0026"
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
        "obs-0018",
        "obs-0022",
        "obs-0026"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0018",
        "obs-0022",
        "obs-0026"
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
      "at": "0x00b21da0",
      "count": 1,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "ESP"
    },
    {
      "at": "0x00b21da0",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0002",
      "index": 0,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00b21da0",
      "definite": true,
      "id": "obs-0003",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00b21da4",
      "count": 22,
      "first_use": 1,
      "first_write_index": 28,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EDX,dword ptr [ECX + 0x14]",
      "reg": "ECX"
    },
    {
      "at": "0x00b21da4",
      "definite": true,
      "id": "obs-0005",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [ECX + 0x14]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00b21da7",
      "count": 7,
      "first_use": 
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
"\nvoid __thiscall FUN_00b21da0(int param_1,int param_2)\n\n{\n  int iVar1;\n  undefined4 uVar2;\n  int iVar3;\n  \n  uVar2 = *(undefined4 *)(param_1 + 0x14);\n  *(undefined4 *)(param_1 + 0x14) = *(undefined4 *)(param_2 + 0x14);\n  *(undefined4 *)(param_2 + 0x14) = uVar2;\n  if (*(int *)(param_1 + 0xc) != 0) {\n    if (*(int *)(param_2 + 0xc) != 0) {\n      uVar2 = *(undefined4 *)(param_1 + 4);\n      *(undefined4 *)(param_1 + 4) = *(undefined4 *)(param_2 + 4);\n      *(undefined4 *)(param_2 + 4) = uVar2;\n      uVar2 = *(undefined4 *)(param_1 + 8);\n      *(undefined4 *)(param_1 + 8) = *(undefined4 *)(param_2 + 8);\n      *(undefined4 *)(param_2 + 8) = uVar2;\n      uVar2 = *(undefined4 *)(param_1 + 0xc);\n      *(undefined4 *)(param_1 + 0xc) = *(undefined4 *)(param_2 + 0xc);\n      *(undefined4 *)(param_2 + 0xc) = uVar2;\n      *(int *)(*(int *)(param_1 + 0xc) + 8) = param_1 + 4;\n      *(int *)(*(int *)(param_2 + 0xc) + 8) = param_2 + 4;\n      return;\n    }\n    if (*(int *)(param_1 + 0xc) != 0) {\n      *(undefined4 *)(param_2 + 4) = *(undefined4 *)(param_1 + 4);\n      iVar1 = param_1 + 4;\n      *(undefined4 *)(param_2 + 8) = *(undefined4 *)(param_1 + 8);\n      iVar3 = *(int *)(param_1 + 0xc);\n      *(int *)(param_2 + 0xc) = iVar3;\n      *(int *)(iVar3 + 8) = param_2 + 4;\n      *(undefined4 *)(param_1 + 0xc) = 0;\n      *(int *)iVar1 = iVar1;\n      *(int *)(param_1 + 8) = iVar1;\n      return;\n    }\n  }\n  if (*(int *)(param_2 + 0xc) != 0) {\n    iVar1 = param_2 + 4;\n    *(undefined4 *)(param_1 + 4) = *(undefined4 *)(param_2 + 4);\n    *(undefined4 *)(param_1 + 8) = *(undefined4 *)(param_2 + 8);\n    iVar3 = *(int *)(param_2 + 0xc);\n    *(int *)(param_1 + 0xc) = iVar3;\n    *(int *)(iVar3 + 8) = param_1 + 4;\n    *(int *)iVar1 = iVar1;\n    *(undefined4 *)(param_2 + 0xc) = 0;\n    *(int *)(param_2 + 8) = iVar1;\n  }\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 72,
  "instructions": [
    {
      "address": "00b21da0",
      "instruction": "MOV EAX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "00b21da4",
      "instruction": "MOV EDX,dword ptr [ECX + 0x14]"
    },
    {
      "address": "00b21da7",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00b21da8",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00b21da9",
      "instruction": "MOV ESI,dword ptr [EAX + 0x14]"
    },
    {
      "address": "00b21dac",
      "instruction": "MOV dword ptr [ECX + 0x14],ESI"
    },
    {
      "address": "00b21daf",
      "instruction": "MOV dword ptr [EAX + 0x14],EDX"
    },
    {
      "address": "00b21db2",
      "instruction": "MOV EDX,dword ptr [ECX + 0xc]"
    },
    {
      "address": "00b21db5",
      "instruction": "XOR EBX,EBX"
    },
    {
      "address": "00b21db7",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00b21db8",
      "instruction": "CMP EDX,EBX"
    },
    {
      "address": "00b21dba",
      "instruction": "JZ 0x00b21e2a"
    },
    {
      "address": "00b21dbc",
      "instruction": "CMP dword ptr [EAX + 0xc],EBX"
    },
    {
      "address": "00b21dbf",
      "instruction": "JZ 0x00b21dfd"
    },
    {
      "address": "00b21dc1",
      "instruction": "MOV EDI,dword ptr [ECX + 0x4]"
    },
    {
      "address": "00b21dc4",
      "instruction": "MOV EBX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "00b21dc7",
      "instruction": "MOV dword ptr [ECX + 0x4],EBX"
    },
    {
      "address": "00b21dca",
      "instruction": "MOV dword ptr [EAX + 0x4],EDI"
    },
    {
      "address": "00b21dcd",
      "instruction": "MOV EBX,dword ptr [EAX + 0x8]"
    },
    {
      "address": "00b21dd0",
      "instruction": "MOV EDI,dword ptr [ECX + 0x8]"
    },
    {
      "address": "00b21dd3",
      "instruction": "LEA EDX,[EAX + 0x4]"
    },
    {
      "address": "00b21dd6",
      "instruction": "LEA ESI,[ECX + 0x4]"
    },
    {
      "address": "00b21dd9",
      "instruction": "MOV dword ptr [ECX + 0x8],EBX"
    },
    {
      "address": "00b21ddc",
      "instruction": "MOV dword ptr [EAX + 0x8],EDI"
    },
    {
      "address": "00b21ddf",
      "instruction": "MOV EBX,dword ptr [EAX + 0xc]"
    },
    {
      "address": "00b21de2",
      "instruction": "MOV EDI,dword ptr [ECX + 0xc]"
    },
    {
      "address": "00b21de5",
      "instruction": "MOV dword ptr [ECX + 0xc],EBX"
    },
    {
      "address": "00b21de8",
      "instruction": "MOV dword ptr [EAX + 0xc],EDI"
    },
    {
      "address": "00b21deb",
      "instruction": "MOV ECX,dword ptr [ECX + 0xc]"
    },
    {
      "address": "00b21dee",
      "instruction": "MOV dword ptr [ECX + 0x8],ESI"
    },
    {
      "address": "00b21df1",
      "instruction": "MOV EAX,dword ptr [EAX + 0xc]"
    },
    {
      "address": "00b21df4",
      "instruction": "POP EDI"
    },
    {
      "address": "00b21df5",
      "instruction": "POP ESI"
    },
    {
      "address": "00b21df6",
      "instruction": "MOV dword ptr [EAX + 0x8],EDX"
    },
    {
      "address": "00b21df9",
      "instruction": "POP EBX"
    },
    {
      "address": "00b21dfa",
      "instruction": "RET 0x4"
    },
    {
      "address": "00b21dfd",
      "instruction": "CMP EDX,EBX"
    },
    {
      "address": "00b21dff",
      "instruction": "JZ 0x00b21e2a"
    },
    {
      "address": "00b21e01",
      "instruction": "MOV EDI,dword ptr [ECX + 0x4]"
    },
    {
      "address": "00b21e04",
      "instruction": "MOV dword ptr [EAX + 0x4],EDI"
    },
    {
      "address": "00b21e07",
      "instruction": "MOV EDI,dword ptr [ECX + 0x8]"
    },
    {
      "address": "00b21e0a",
      "instruction": "LEA EDX,[ECX + 0x4]"
    },
    {
      "address": "00b21e0d",
      "instruction": "LEA ESI,[EAX + 0x4]"
    },
    {
      "address": "00b21e10",
      "instruction": "MOV dword ptr [EAX + 0x8],EDI"
    },
    {
      "address": "00b21e13",
      "instruction": "MOV EDI,dword ptr [ECX + 0xc]"
    },
    {
      "address": "00b21e16",
      "instruction": "MOV dword ptr [EAX + 0xc],EDI"
    },
    {
      "address": "00b21e19",
      "instruction": "MOV dword ptr [EDI + 0x8],ESI"
    },
    {
      "address": "00b21e1c",
      "instruction": "POP EDI"
    },
    {
      "address": "00b21e1d",
      "instruction": "POP ESI"
    },
    {
      "address": "00b21e1e",
      "instruction": "MOV dword ptr [ECX + 0xc],EBX"
    },
    {
      "address": "00b21e21",
      "instruction": "MOV dword ptr [EDX],EDX"
    },
    {
      "address": "00b21e23",
      "instruction": "MOV dword ptr [ECX + 0x8],EDX"
    },
    {
      "address": "00b21e26",
      "instruction": "POP EBX"
    },
    {
      "address": "00b21e27",
      "instruction": "RET 0x4"
    },
    {
      "address": "00b21e2a",
      "instruction": "CMP dword ptr [EAX + 0xc],EBX"
    },
    {
      "address": "00b21e2d",
      "instruction": "JZ 0x00b21e52"
    },
    {
      "address": "00b21e2f",
      "instruction": "MOV EDI,dword ptr [EAX + 0x4]"
    },
    {
      "address": "00b21e32",
      "instruction": "LEA EDX,[EAX + 0x4]"
    },
    {
      "address": "00b21e35",
      "instruction": "MOV dword ptr [ECX + 0x4],EDI"
    },
    {
      "address": "00b21e38",
      "instruction": "MOV EDI,dword ptr [EAX + 0x8]"
    },
    {
      "address": "00b21e3b",
      "instruction": "LEA ESI,[ECX + 0x4]"
    },
    {
      "address": "00b21e3e",
      "instruction": "MOV dword ptr [ECX + 0x8],EDI"
    },
    {
      "address": "00b21e41",
      "instruction": "MOV EDI,dword ptr [EAX + 0xc]"
    },
    {
      "address": "00b21e44",
      "instruction": "MOV dword ptr [ECX + 0xc],EDI"
    },
    {
      "address": "00b21e47",
      "instruction": "MOV dword ptr [EDI + 0x8],ESI"
    },
    {
      "address": "00b21e4a",
      "instruction": "MOV dword ptr [EDX],EDX"
    },
    {
      "address": "00b21e4c",
      "instruction": "MOV dword ptr [EAX + 0xc],EBX"
    },
    {
      "address": 
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
  "body_end": "00b21e57",
  "body_span_bytes": 184,
  "body_start": "00b21da0",
  "callees": [],
  "callers": [
    "FUN_00bb8b20",
    "FUN_00b237d0",
    "FUN_00b26600",
    "FUN_00b22bc0",
    "FUN_00bb4ba0",
    "FUN_00b26320",
    "FUN_00b225b0"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "00b21da0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "iVar3",
      "storage": "unique:00017200:4",
      "type": "int"
    },
    {
      "name": "uVar2",
      "storage": "unique:00017200:4",
      "type": "undefined4"
    },
    {
      "name": "iVar1",
      "storage": "unique:00006600:4",
      "type": "int"
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
  "locals_count": 5,
  "mode": "live",
  "name": "FUN_00b21da0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x721da0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00b21da0(void)",
  "size_bytes": 184,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00b21da0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 13,
  "xrefs": [
    {
      "from": "00bb4e8c"
    },
    {
      "from": "00bb4ec9"
    },
    {
      "from": "00bb9018"
    },
    {
      "from": "00b225c5"
    },
    {
      "from": "00b22bdb"
    },
    {
      "from": "00b23905"
    },
    {
      "from": "00b2391e"
    },
    {
      "from": "00b26382"
    },
    {
      "from": "00b26576"
    },
    {
      "from": "00b26585"
    },
    {
      "from": "00b266b9"
    },
    {
      "from": "00b266c8"
    },
    {
      "from": "00b242b3"
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
