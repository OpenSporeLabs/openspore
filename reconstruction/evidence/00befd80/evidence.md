# Evidence 0x00befd80

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `cf7330a3711dbdd0d596581792de3d5bc7c2ca0ecd28899439e4ca1357178597`

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
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x8",
        "observed": true,
        "ordinal": 2,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x8",
    "return_register": "XMM0",
    "return_semantics": "float_or_x87_in_XMM0",
    "saved_registers": [
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
      },
      {
        "entry_offset": "entry_ESP+0x8",
        "observed": true,
        "ordinal": 2,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      }
    ],
    "stack_cleanup_bytes": 8,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x8"
  },
  "abstained_because": [],
  "cleanup": {
    "bytes": 8,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x8",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "813d07b0ba990abfcdc7ae220efbb1264c6c2e866800d2fec1eec03c5fdac818",
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
        "obs-0032"
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
        "obs-0002",
        "obs-0003",
        "obs-0017",
        "obs-0018",
        "obs-0022",
        "obs-0026",
        "obs-0027",
        "obs-0028"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "INFERRED",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 2,
        "total_bytes": 8
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007",
        "obs-0010",
        "obs-0011"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          137,
          138,
          152
        ],
        "register": "ECX",
        "written_through": 2
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007",
        "obs-0010",
        "obs-0011",
        "obs-0032"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0032"
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
        "obs-0032"
      ],
      "claim": "the return value is carried in XMM0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "XMM0"
    }
  ],
  "observations": [
    {
      "at": "0x00befd80",
      "count": 8,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "CMP byte ptr [ESP + 0x8],0x0",
      "reg": "ESP"
    },
    {
      "at": "0x00befd80",
      "base": "ESP",
      "disp": 8,
      "id": "obs-0002",
      "index": 0,
      "key": 8,
      "kind": "STACK_SLOT_READ",
      "raw": "CMP byte ptr [ESP + 0x8],0x0",
      "resolved": true,
      "size": 1
    },
    {
      "at": "0x00befd85",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0003",
      "index": 1,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOVSS XMM0,dword ptr [ESP + 0x4]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00befd85",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOVSS XMM0,dword ptr [ESP + 0x4]",
      "reg": "XMM0",
      "write_kind": "unknown"
    },
    {
      "at": "0x00befd8b",
      "count": 7,
      "first_use": 2,
      "first_write_index": 3,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00befd8c",
      "count": 1,
      "first_use": 3,
      "first_write_index": 10,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00befd8c",
      "definite": true,
      "id": "obs-0007",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00be
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
"\nvoid __thiscall FUN_00befd80(int param_1,float param_2,char param_3)\n\n{\n  int iVar1;\n  \n  if (((param_3 == '\\0') || (param_2 <= 0.0)) || (*(char *)(param_1 + 0x89) != '\\0'))\n  goto LAB_00befeaf;\n  FUN_00b3d300();\n  iVar1 = FUN_00b25fb0();\n  if (iVar1 == 0) goto LAB_00befeaf;\n  if (*(char *)(iVar1 + 0x8d) == '\\0') {\n    if (*(char *)(param_1 + 0x8a) == '\\0') goto LAB_00befdd8;\n    FUN_00b3d300();\n    FUN_00f67d90();\n    iVar1 = FUN_00c75420();\n    if (iVar1 == 0) {\n      param_2 = param_2 * 0.1;\n      goto LAB_00befeaf;\n    }\n    if (iVar1 != 1) {\n      if (iVar1 != 2) goto LAB_00befeaf;\n      goto LAB_00befe89;\n    }\nLAB_00befe15:\n    param_2 = param_2 * 0.2;\n  }\n  else {\n    if (*(char *)(param_1 + 0x8a) == '\\0') {\n      FUN_00b3d300();\n      FUN_00f67d90();\n      iVar1 = FUN_00c75420();\n      if (iVar1 == 0) {\nLAB_00befe89:\n        param_2 = param_2 * 0.4;\n        goto LAB_00befeaf;\n      }\n      if (iVar1 != 1) {\n        if (iVar1 == 2) {\n          param_2 = param_2 * 1.2;\n        }\n        goto LAB_00befeaf;\n      }\n    }\n    else {\nLAB_00befdd8:\n      FUN_00b3d300();\n      FUN_00f67d90();\n      iVar1 = FUN_00c75420();\n      if (iVar1 == 0) goto LAB_00befe15;\n      if (iVar1 == 1) goto LAB_00befe89;\n      if (iVar1 != 2) goto LAB_00befeaf;\n    }\n    param_2 = param_2 * 0.8;\n  }\nLAB_00befeaf:\n  param_2 = param_2 + *(float *)(param_1 + 0x98);\n  *(float *)(param_1 + 0x98) = param_2;\n  if (999999.0 < param_2) {\n    *(undefined4 *)(param_1 + 0x98) = 0x497423f0;\n  }\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 77,
  "instructions": [
    {
      "address": "00befd80",
      "instruction": "CMP byte ptr [ESP + 0x8],0x0"
    },
    {
      "address": "00befd85",
      "instruction": "MOVSS XMM0,dword ptr [ESP + 0x4]"
    },
    {
      "address": "00befd8b",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00befd8c",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00befd8e",
      "instruction": "JZ 0x00befeaf"
    },
    {
      "address": "00befd94",
      "instruction": "COMISS XMM0,dword ptr [0x01485378]"
    },
    {
      "address": "00befd9b",
      "instruction": "JBE 0x00befeaf"
    },
    {
      "address": "00befda1",
      "instruction": "CMP byte ptr [ESI + 0x89],0x0"
    },
    {
      "address": "00befda8",
      "instruction": "JNZ 0x00befeaf"
    },
    {
      "address": "00befdae",
      "instruction": "CALL 0x00b3d300"
    },
    {
      "address": "00befdb3",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00befdb5",
      "instruction": "CALL 0x00b25fb0"
    },
    {
      "address": "00befdba",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00befdbc",
      "instruction": "JZ 0x00befea9"
    },
    {
      "address": "00befdc2",
      "instruction": "CMP byte ptr [EAX + 0x8d],0x0"
    },
    {
      "address": "00befdc9",
      "instruction": "JZ 0x00befe5a"
    },
    {
      "address": "00befdcf",
      "instruction": "CMP byte ptr [ESI + 0x8a],0x0"
    },
    {
      "address": "00befdd6",
      "instruction": "JZ 0x00befe28"
    },
    {
      "address": "00befdd8",
      "instruction": "CALL 0x00b3d300"
    },
    {
      "address": "00befddd",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00befddf",
      "instruction": "CALL 0x00f67d90"
    },
    {
      "address": "00befde4",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00befde6",
      "instruction": "CALL 0x00c75420"
    },
    {
      "address": "00befdeb",
      "instruction": "SUB EAX,0x0"
    },
    {
      "address": "00befdee",
      "instruction": "JZ 0x00befe15"
    },
    {
      "address": "00befdf0",
      "instruction": "SUB EAX,0x1"
    },
    {
      "address": "00befdf3",
      "instruction": "JZ 0x00befe89"
    },
    {
      "address": "00befdf9",
      "instruction": "SUB EAX,0x1"
    },
    {
      "address": "00befdfc",
      "instruction": "JNZ 0x00befea9"
    },
    {
      "address": "00befe02",
      "instruction": "MOVSS XMM0,dword ptr [ESP + 0x8]"
    },
    {
      "address": "00befe08",
      "instruction": "MULSS XMM0,dword ptr [0x01486374]"
    },
    {
      "address": "00befe10",
      "instruction": "JMP 0x00befeaf"
    },
    {
      "address": "00befe15",
      "instruction": "MOVSS XMM0,dword ptr [ESP + 0x8]"
    },
    {
      "address": "00befe1b",
      "instruction": "MULSS XMM0,dword ptr [0x013ec480]"
    },
    {
      "address": "00befe23",
      "instruction": "JMP 0x00befeaf"
    },
    {
      "address": "00befe28",
      "instruction": "CALL 0x00b3d300"
    },
    {
      "address": "00befe2d",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00befe2f",
      "instruction": "CALL 0x00f67d90"
    },
    {
      "address": "00befe34",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00befe36",
      "instruction": "CALL 0x00c75420"
    },
    {
      "address": "00befe3b",
      "instruction": "SUB EAX,0x0"
    },
    {
      "address": "00befe3e",
      "instruction": "JZ 0x00befe89"
    },
    {
      "address": "00befe40",
      "instruction": "SUB EAX,0x1"
    },
    {
      "address": "00befe43",
      "instruction": "JZ 0x00befe02"
    },
    {
      "address": "00befe45",
      "instruction": "SUB EAX,0x1"
    },
    {
      "address": "00befe48",
      "instruction": "JNZ 0x00befea9"
    },
    {
      "address": "00befe4a",
      "instruction": "MOVSS XMM0,dword ptr [ESP + 0x8]"
    },
    {
      "address": "00befe50",
      "instruction": "MULSS XMM0,dword ptr [0x013eb1c0]"
    },
    {
      "address": "00befe58",
      "instruction": "JMP 0x00befeaf"
    },
    {
      "address": "00befe5a",
      "instruction": "CMP byte ptr [ESI + 0x8a],0x0"
    },
    {
      "address": "00befe61",
      "instruction": "JZ 0x00befdd8"
    },
    {
      "address": "00befe67",
      "instruction": "CALL 0x00b3d300"
    },
    {
      "address": "00befe6c",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00befe6e",
      "instruction": "CALL 0x00f67d90"
    },
    {
      "address": "00befe73",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00befe75",
      "instruction": "CALL 0x00c75420"
    },
    {
      "address": "00befe7a",
      "instruction": "SUB EAX,0x0"
    },
    {
      "address": "00befe7d",
      "instruction": "JZ 0x00befe99"
    },
    {
      "address": "00befe7f",
      "instruction": "SUB EAX,0x1"
    },
    {
      "address": "00befe82",
      "instruction": "JZ 0x00befe15"
    },
    {
      "address": "00befe84",
      "instruction": "SUB EAX,0x1"
    },
    {
      "address": "00befe87",
      "instruction": "JNZ 0x00befea9"
    },
    {
      "address": "00befe89",
      "instruction": "MOVSS XMM0,dword ptr [ESP + 0x8]"
    },
    {
      "address": "00befe8f",
      "instruction": "MULSS XMM0,dword ptr [0x013ec434]"
    },
    {
      "address": "00befe97",
      "instruction": "JMP 0x00befeaf"
    },
    {
      "address": "00befe99",
      "instruction": "MOVSS XMM0,dword ptr [ESP + 0x8]"
    },
    {
      "address": "00befe9f",
      "instruction": "MULSS XMM0,dword ptr [0x01488874]"
    },
    {
      "address": "00befea7",
      "instruction": "JMP 0x00befeaf"
    },
    {
      "address": "00befea9",
      "instruction": "MOVSS XMM0,dword ptr [ESP + 0x8]"
    },
    {
      "address": "00befeaf",
      "instruction": "ADDSS XMM0,dword ptr [ESI + 0x98]"
    },
    {
      "address": "00befeb7",
      "instruction": "MOVSS XMM1,dword ptr [0x0146935
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
  "body_end": "00befed7",
  "body_span_bytes": 344,
  "body_start": "00befd80",
  "callees": [
    "FUN_00b25fb0",
    "FUN_00f67d90",
    "FUN_00c75420",
    "FUN_00b3d300"
  ],
  "callers": [
    "FUN_00b998a0",
    "FUN_00caa610",
    "FUN_00cfeeb0",
    "FUN_00ff6a50",
    "FUN_00bf71d0",
    "FUN_00be8680",
    "FUN_00be1860",
    "FUN_00cf31f0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00befd80",
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
      "name": "iVar1",
      "storage": "register:00000000:4",
      "type": "int"
    },
    {
      "name": "param_2",
      "storage": "Stack[0x4]:4",
      "type": "float"
    },
    {
      "name": "param_3",
      "storage": "Stack[0x8]:1",
      "type": "char"
    }
  ],
  "locals_count": 4,
  "mode": "live",
  "name": "FUN_00befd80",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x7efd80",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00befd80(void)",
  "size_bytes": 344,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00befd80",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 15,
  "xrefs": [
    {
      "from": "00bf7221"
    },
    {
      "from": "00caa645"
    },
    {
      "from": "00cfefa3"
    },
    {
      "from": "00cff059"
    },
    {
      "from": "00cff3cb"
    },
    {
      "from": "00cff610"
    },
    {
      "from": "00cff97f"
    },
    {
      "from": "00be875e"
    },
    {
      "from": "00ff6b4e"
    },
    {
      "from": "00cf387f"
    },
    {
      "from": "00be18d1"
    },
    {
      "from": "00be1ad2"
    },
    {
      "from": "00b99e17"
    },
    {
      "from": "00b60bda"
    },
    {
      "from": "00d07cc8"
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
