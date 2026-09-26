# Evidence 0x00c0ce80

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `32cfe60779d64db1bc8f74f745bca4780d45a26149394d5c530bcb5065ff002b`

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
          4
        ],
        "written": false
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x8",
    "return_register": "ST0",
    "return_semantics": "float_or_x87_in_ST0",
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
    "flow_not_modelled: the linear ESP walk ends at -4, so the listing is not one path",
    "unparsed_lines_present: 1 line(s) matched no grammar rule"
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
  "content_sha256": "9423c7631d377f848ddf90cfce84fa34e461cb7c6c55eece65fb5da6bd2e49fd",
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
        "obs-0033",
        "obs-0038",
        "obs-0042"
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
        "obs-0003",
        "obs-0010"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 2,
        "total_bytes": 8
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0008",
        "obs-0010",
        "obs-0011",
        "obs-0032",
        "obs-0037",
        "obs-0041"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          192
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0008",
        "obs-0010",
        "obs-0011",
        "obs-0032",
        "obs-0033",
        "obs-0037",
        "obs-0038",
        "obs-0041",
        "obs-0042"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0033",
        "obs-0038",
        "obs-0042"
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
        "obs-0042"
      ],
      "claim": "the return value is carried in ST0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "ST0"
    }
  ],
  "observations": [
    {
      "at": "0x00c0ce80",
      "count": 5,
      "first_use": 0,
      "first_write_index": 8,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00c0ce81",
      "count": 12,
      "first_use": 1,
      "first_write_index": null,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x8]",
      "reg": "ESP"
    },
    {
      "at": "0x00c0ce81",
      "base": "ESP",
      "disp": 8,
      "id": "obs-0003",
      "index": 1,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x8]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00c0ce81",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESP + 0x8]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00c0ce85",
      "count": 5,
      "first_use": 2,
      "first_write_index": 2,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_READ",
      "raw": "XORPS XMM0,XMM0",
      "reg": "XMM0"
    },
    {
      "at": "0x00c0ce85",
      "definite": true,
      "id": "obs-0006",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "XORPS XMM0,XMM0",
      "reg": "XMM0",
      "write_kind": "unknown"
    },
    {
   
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
"\nfloat10 __thiscall FUN_00c0ce80(int param_1,float param_2,undefined4 param_3)\n\n{\n  char cVar1;\n  int iVar2;\n  undefined *puVar3;\n  float10 fVar4;\n  int iVar5;\n  int iVar6;\n  float local_4;\n  \n  if (param_2 == 0.0) {\n    return (float10)0.0;\n  }\n  iVar2 = FUN_00c0ce30(param_2,param_3);\n  puVar3 = (undefined *)FUN_00b5b800();\n  if (puVar3 == &DAT_01654c10) {\n    iVar5 = param_1;\n    iVar6 = iVar2;\n    FUN_00c03260(param_1,iVar2);\n    fVar4 = (float10)FUN_00f31500(iVar5,iVar6);\n    local_4 = (float)fVar4;\n  }\n  else {\n    local_4 = *(float *)(&DAT_015d9650 + iVar2 * 4);\n  }\n  cVar1 = (**(code **)(*(int *)(param_1 + 0xc0) + 0x58))();\n  if (cVar1 != '\\0') {\n    param_2 = local_4;\n    if (iVar2 + 1U < 6) {\n      param_2 = *(float *)(&DAT_015d9654 + iVar2 * 4);\n    }\n    else if (iVar2 != 0) {\n      param_2 = *(float *)(&DAT_015d964c + iVar2 * 4);\n    }\n    return ABS((float10)local_4 - (float10)param_2) * (float10)0.5 + (float10)local_4;\n  }\n  return (float10)local_4;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 63,
  "instructions": [
    {
      "address": "00c0ce80",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00c0ce81",
      "instruction": "MOV EAX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "00c0ce85",
      "instruction": "XORPS XMM0,XMM0"
    },
    {
      "address": "00c0ce88",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00c0ce89",
      "instruction": "MOV EDI,ECX"
    },
    {
      "address": "00c0ce8b",
      "instruction": "MOVSS dword ptr [ESP + 0x4],XMM0"
    },
    {
      "address": "00c0ce91",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00c0ce93",
      "instruction": "JZ 0x00c0cf43"
    },
    {
      "address": "00c0ce99",
      "instruction": "MOV ECX,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00c0ce9d",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00c0ce9e",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00c0ce9f",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00c0cea0",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00c0cea2",
      "instruction": "CALL 0x00c0ce30"
    },
    {
      "address": "00c0cea7",
      "instruction": "MOV ESI,EAX"
    },
    {
      "address": "00c0cea9",
      "instruction": "CALL 0x00b5b800"
    },
    {
      "address": "00c0ceae",
      "instruction": "CMP EAX,0x1654c10"
    },
    {
      "address": "00c0ceb3",
      "instruction": "JNZ 0x00c0cec9"
    },
    {
      "address": "00c0ceb5",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00c0ceb6",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00c0ceb7",
      "instruction": "CALL 0x00c03260"
    },
    {
      "address": "00c0cebc",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00c0cebe",
      "instruction": "CALL 0x00f31500"
    },
    {
      "address": "00c0cec3",
      "instruction": "FSTP float ptr [ESP + 0x8]"
    },
    {
      "address": "00c0cec7",
      "instruction": "JMP 0x00c0ced8"
    },
    {
      "address": "00c0cec9",
      "instruction": "MOVSS XMM0,dword ptr [ESI*0x4 + 0x15d9650]"
    },
    {
      "address": "00c0ced2",
      "instruction": "MOVSS dword ptr [ESP + 0x8],XMM0"
    },
    {
      "address": "00c0ced8",
      "instruction": "MOV EDX,dword ptr [EDI + 0xc0]"
    },
    {
      "address": "00c0cede",
      "instruction": "MOV EAX,dword ptr [EDX + 0x58]"
    },
    {
      "address": "00c0cee1",
      "instruction": "LEA ECX,[EDI + 0xc0]"
    },
    {
      "address": "00c0cee7",
      "instruction": "CALL EAX"
    },
    {
      "address": "00c0cee9",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00c0ceeb",
      "instruction": "JZ 0x00c0cf39"
    },
    {
      "address": "00c0ceed",
      "instruction": "MOVSS XMM0,dword ptr [ESP + 0x8]"
    },
    {
      "address": "00c0cef3",
      "instruction": "LEA ECX,[ESI + 0x1]"
    },
    {
      "address": "00c0cef6",
      "instruction": "MOVSS dword ptr [ESP + 0x10],XMM0"
    },
    {
      "address": "00c0cefc",
      "instruction": "CMP ECX,0x6"
    },
    {
      "address": "00c0ceff",
      "instruction": "JNC 0x00c0cf0c"
    },
    {
      "address": "00c0cf01",
      "instruction": "MOVSS XMM0,dword ptr [ESI*0x4 + 0x15d9654]"
    },
    {
      "address": "00c0cf0a",
      "instruction": "JMP 0x00c0cf19"
    },
    {
      "address": "00c0cf0c",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "00c0cf0e",
      "instruction": "JBE 0x00c0cf1f"
    },
    {
      "address": "00c0cf10",
      "instruction": "MOVSS XMM0,dword ptr [ESI*0x4 + 0x15d964c]"
    },
    {
      "address": "00c0cf19",
      "instruction": "MOVSS dword ptr [ESP + 0x10],XMM0"
    },
    {
      "address": "00c0cf1f",
      "instruction": "FLD float ptr [ESP + 0x8]"
    },
    {
      "address": "00c0cf23",
      "instruction": "POP ESI"
    },
    {
      "address": "00c0cf24",
      "instruction": "FLD float ptr [ESP + 0xc]"
    },
    {
      "address": "00c0cf28",
      "instruction": "POP EDI"
    },
    {
      "address": "00c0cf29",
      "instruction": "FSUBR ST0,ST1"
    },
    {
      "address": "00c0cf2b",
      "instruction": "FABS"
    },
    {
      "address": "00c0cf2d",
      "instruction": "FMUL float ptr [0x01471064]"
    },
    {
      "address": "00c0cf33",
      "instruction": "FADDP"
    },
    {
      "address": "00c0cf35",
      "instruction": "POP ECX"
    },
    {
      "address": "00c0cf36",
      "instruction": "RET 0x8"
    },
    {
      "address": "00c0cf39",
      "instruction": "FLD float ptr [ESP + 0x8]"
    },
    {
      "address": "00c0cf3d",
      "instruction": "POP ESI"
    },
    {
      "address": "00c0cf3e",
      "instruction": "POP EDI"
    },
    {
      "address": "00c0cf3f",
      "instruction": "POP ECX"
    },
    {
      "address": "00c0cf40",
      "instruction": "RET 0x8"
    },
    {
      "address": "00c0cf43",
      "instruction": "FLD float ptr [ESP + 0x4]"
    },
    {
      "address": "00c0cf47",
      "instruction": "POP EDI"
    },
    {
      "address": "00c0cf48",
      "instruction": "POP ECX"
    },
    {
      "address": "00c0cf49",
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
  "body_end": "00c0cf4b",
  "body_span_bytes": 204,
  "body_start": "00c0ce80",
  "callees": [
    "FUN_00c03260",
    "FUN_00b5b800",
    "FUN_00c0ce30",
    "FUN_00f31500"
  ],
  "callers": [
    "FUN_00c1aad0",
    "FUN_00c1c080",
    "FUN_00c1f8d0",
    "FUN_00c1b020",
    "FUN_00c0d050",
    "FUN_00c0cfa0",
    "FUN_00c21bf0",
    "FUN_00c1c5c0",
    "FUN_00c1de20",
    "FUN_00c0cff0",
    "FUN_00c0d0c0",
    "FUN_00c190e0",
    "FUN_00c0cf50",
    "FUN_00c1c1d0",
    "FUN_00c1ad10"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00c0ce80",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "iVar2",
      "storage": "register:00000000:4",
      "type": "int"
    },
    {
      "name": "cVar1",
      "storage": "register:00000000:1",
      "type": "char"
    },
    {
      "name": "fVar4",
      "storage": "register:00001100:10",
      "type": "float10"
    },
    {
      "name": "puVar3",
      "storage": "register:00000000:4",
      "type": "undefined *"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int"
    },
    {
      "name": "param_3",
      "storage": "Stack[0x8]:4",
      "type": "undefined4"
    },
    {
      "name": "local_4",
      "storage": "Stack[-0x4]:4",
      "type": "float"
    },
    {
      "name": "param_2",
      "storage": "Stack[0x4]:4",
      "type": "float"
    },
    {
      "name": "iVar6",
      "storage": "Stack[-0x10]:4",
      "type": "int"
    },
    {
      "name": "iVar5",
      "storage": "Stack[-0x14]:4",
      "type": "int"
    }
  ],
  "locals_count": 10,
  "mode": "live",
  "name": "FUN_00c0ce80",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x80ce80",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00c0ce80(void)",
  "size_bytes": 204,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00c0ce80",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 33,
  "xrefs": [
    {
      "from": "00c0d00a"
    },
    {
      "from": "00c0d02e"
    },
    {
      "from": "00c0d186"
    },
    {
      "from": "00c0d196"
    },
    {
      "from": "00c1c2c2"
    },
    {
      "from": "00c1c2d1"
    },
    {
      "from": "00c21ebb"
    },
    {
      "from": "00c1c87d"
    },
    {
      "from": "00c1c88c"
    },
    {
      "from": "00c0cf62"
    },
    {
      "from": "00c0cf73"
    },
    {
      "from": "00c0cf84"
    },
    {
      "from": "00c1fdae"
    },
    {
      "from": "00c1fdbf"
    },
    {
      "from": "00c1fdd0"
    },
    {
      "from": "00c1adbc"
    },
    {
      "from": "00c1adcc"
    },
    {
      "from": "00c1ae85"
    },
    {
      "from": "00c1ae95"
    },
    {
      "from": "00c1abba"
    },
    {
      "from": "00c1abc9"
    },
    {
      "from": "00c1c165"
    },
    {
      "from": "00c1c174"
    },
    {
      "from": "00c1e1fc"
    },
    {
      "from": "00c1e20d"
    },
    {
      "from": "00c0cfad"
    },
    {
      "from": "00c193ab"
    },
    {
      "from": "00c193bc"
    },
    {
      "from": "00c0cfe4"
    },
    {
      "from": "00c1b43f"
    },
    {
      "from": "00c1b450"
    },
    {
      "from": "00c0d074"
    },
    {
      "from": "00c0d084"
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
