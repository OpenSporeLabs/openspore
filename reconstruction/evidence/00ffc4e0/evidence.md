# Evidence 0x00ffc4e0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `b9a3d52b710e992ba160eb88e28a8e899b3ad9810eba1742619cf9c7f13d487f`

## abi

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "abi": {
    "architecture": "x86-32",
    "ordinary_stack_argument_slots": [
      "entry_ESP+0x8"
    ],
    "ordinary_stack_arguments": [
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
    "ret_form": "RET 0x8",
    "return_register": "ST0",
    "return_semantics": "float_or_x87_in_ST0",
    "saved_registers": [
      "EDI",
      "ESI"
    ],
    "stack_arguments": [
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
    "flow_not_modelled: the linear ESP walk ends at +8, so the listing is not one path",
    "unparsed_lines_present: 1 line(s) matched no grammar rule",
    "receiver_not_determinable: ecx_read_without_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_read_without_deref), and the convention rule that would apply discriminates on receiver absence"
  ],
  "cleanup": {
    "bytes": 8,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x8",
    "side": "callee"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "18a36ac2de8062df6cf08051afda6202d08ded78a34b0adb0722d076a594541e",
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
        "obs-0041"
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
        "obs-0006"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 1,
        "observed_slots": 1,
        "total_bytes": 8
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0010",
        "obs-0025",
        "obs-0040"
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
        "obs-0010",
        "obs-0025",
        "obs-0040"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_read_without_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0041"
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
        "obs-0041"
      ],
      "claim": "the return value is carried in ST0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "ST0"
    }
  ],
  "observations": [
    {
      "at": "0x00ffc4e0",
      "count": 1,
      "first_use": 0,
      "first_write_index": 9,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00ffc4e1",
      "count": 6,
      "first_use": 1,
      "first_write_index": 5,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00ffc4e2",
      "count": 5,
      "first_use": 2,
      "first_write_index": 4,
      "id": "obs-0003",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00ffc4e3",
      "id": "obs-0004",
      "index": 3,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x01021300",
      "target": "0x01021300"
    },
    {
      "at": "0x00ffc4e8",
      "count": 10,
      "first_use": 4,
      "first_write_index": 47,
      "id": "obs-0005",
      "index": 4,
      "kind": "REG_READ",
      "raw": "MOV EDI,dword ptr [ESP + 0x14]",
      "reg": "ESP"
    },
    {
      "at": "0x00ffc4e8",
      "base": "ESP",
      "disp": 20,
      "id": "obs-0006",
      "index": 4,
      "key": 8,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EDI,dword ptr [ESP + 0x14]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00ffc4e8",
      "definite": true,
      "id": "obs-0007",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV EDI,dword ptr [ESP + 0x14]",
      "reg": "EDI",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00ffc4ec",
      "count": 7,
      "first_use": 5,
      "first_write_index": null,
      "id": "obs-0008",
      "index": 5,
      "kind": "REG_READ",
      "raw": "MOV ESI,EAX",
      "reg": "EAX"
    },
    {
      "at": "0x00ffc4ec",
      "definite": true,
      "id": "obs-0009",
      "index": 5,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,EAX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00ffc4f3",
      "definite": true,
      "id": "obs-0010",
      "index": 9,
      "
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
"\nvoid FUN_00ffc4e0(undefined4 param_1,undefined4 param_2)\n\n{\n  char cVar1;\n  int iVar2;\n  undefined4 uVar3;\n  \n  iVar2 = FUN_01021300();\n  if (iVar2 != 0) {\n    cVar1 = FUN_00c31470(param_2);\n    if (cVar1 == '\\0') {\n      iVar2 = FUN_00bb9ae0();\n      if (iVar2 == 5) {\n        uVar3 = FUN_00b1fdb0();\n        cVar1 = FUN_00c31bf0(uVar3);\n        if (cVar1 != '\\0') {\n          FUN_0102f810();\n          FUN_0102fd90();\n        }\n      }\n    }\n    else {\n      FUN_0102f810();\n      FUN_0102fd40();\n    }\n  }\n  uVar3 = FUN_005c65e0();\n  uVar3 = FUN_005c65e0(uVar3);\n  FUN_010434e0(uVar3);\n  FUN_0102f810();\n  FUN_0102fcf0();\n  FUN_011e0810();\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 64,
  "instructions": [
    {
      "address": "00ffc4e0",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00ffc4e1",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00ffc4e2",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00ffc4e3",
      "instruction": "CALL 0x01021300"
    },
    {
      "address": "00ffc4e8",
      "instruction": "MOV EDI,dword ptr [ESP + 0x14]"
    },
    {
      "address": "00ffc4ec",
      "instruction": "MOV ESI,EAX"
    },
    {
      "address": "00ffc4ee",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "00ffc4f0",
      "instruction": "JZ 0x00ffc541"
    },
    {
      "address": "00ffc4f2",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00ffc4f3",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00ffc4f5",
      "instruction": "CALL 0x00c31470"
    },
    {
      "address": "00ffc4fa",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00ffc4fc",
      "instruction": "JNZ 0x00ffc52f"
    },
    {
      "address": "00ffc4fe",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00ffc500",
      "instruction": "CALL 0x00bb9ae0"
    },
    {
      "address": "00ffc505",
      "instruction": "CMP EAX,0x5"
    },
    {
      "address": "00ffc508",
      "instruction": "JNZ 0x00ffc541"
    },
    {
      "address": "00ffc50a",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00ffc50c",
      "instruction": "CALL 0x00b1fdb0"
    },
    {
      "address": "00ffc511",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00ffc512",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00ffc514",
      "instruction": "CALL 0x00c31bf0"
    },
    {
      "address": "00ffc519",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00ffc51b",
      "instruction": "JZ 0x00ffc541"
    },
    {
      "address": "00ffc51d",
      "instruction": "CALL 0x0102f810"
    },
    {
      "address": "00ffc522",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00ffc524",
      "instruction": "CALL 0x0102fd90"
    },
    {
      "address": "00ffc529",
      "instruction": "FSTP float ptr [ESP + 0x14]"
    },
    {
      "address": "00ffc52d",
      "instruction": "JMP 0x00ffc54f"
    },
    {
      "address": "00ffc52f",
      "instruction": "CALL 0x0102f810"
    },
    {
      "address": "00ffc534",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00ffc536",
      "instruction": "CALL 0x0102fd40"
    },
    {
      "address": "00ffc53b",
      "instruction": "FSTP float ptr [ESP + 0x14]"
    },
    {
      "address": "00ffc53f",
      "instruction": "JMP 0x00ffc54f"
    },
    {
      "address": "00ffc541",
      "instruction": "MOVSS XMM0,dword ptr [0x01485720]"
    },
    {
      "address": "00ffc549",
      "instruction": "MOVSS dword ptr [ESP + 0x14],XMM0"
    },
    {
      "address": "00ffc54f",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00ffc551",
      "instruction": "CALL 0x005c65e0"
    },
    {
      "address": "00ffc556",
      "instruction": "MOV ECX,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00ffc55a",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00ffc55b",
      "instruction": "CALL 0x005c65e0"
    },
    {
      "address": "00ffc560",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00ffc561",
      "instruction": "CALL 0x010434e0"
    },
    {
      "address": "00ffc566",
      "instruction": "FST float ptr [ESP + 0x18]"
    },
    {
      "address": "00ffc56a",
      "instruction": "FLD1"
    },
    {
      "address": "00ffc56c",
      "instruction": "MOVSS XMM0,dword ptr [0x01485720]"
    },
    {
      "address": "00ffc574",
      "instruction": "FXCH"
    },
    {
      "address": "00ffc576",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "00ffc579",
      "instruction": "MOVSS dword ptr [ESP + 0x8],XMM0"
    },
    {
      "address": "00ffc57f",
      "instruction": "FCOMIP ST0,ST1"
    },
    {
      "address": "00ffc581",
      "instruction": "FSTP ST0"
    },
    {
      "address": "00ffc583",
      "instruction": "LEA ESI,[ESP + 0x10]"
    },
    {
      "address": "00ffc587",
      "instruction": "JA 0x00ffc58d"
    },
    {
      "address": "00ffc589",
      "instruction": "LEA ESI,[ESP + 0x8]"
    },
    {
      "address": "00ffc58d",
      "instruction": "CALL 0x0102f810"
    },
    {
      "address": "00ffc592",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00ffc594",
      "instruction": "CALL 0x0102fcf0"
    },
    {
      "address": "00ffc599",
      "instruction": "FMUL float ptr [ESP + 0x14]"
    },
    {
      "address": "00ffc59d",
      "instruction": "FMUL float ptr [ESI]"
    },
    {
      "address": "00ffc59f",
      "instruction": "CALL 0x011e0810"
    },
    {
      "address": "00ffc5a4",
      "instruction": "POP EDI"
    },
    {
      "address": "00ffc5a5",
      "instruction": "POP ESI"
    },
    {
      "address": "00ffc5a6",
      "instruction": "POP ECX"
    },
    {
      "address": "00ffc5a7",
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
  "body_end": "00ffc5a9",
  "body_span_bytes": 202,
  "body_start": "00ffc4e0",
  "callees": [
    "FUN_0102f810",
    "FUN_0102fcf0",
    "FUN_0102fd90",
    "FUN_011e0810",
    "FUN_005c65e0",
    "FUN_010434e0",
    "FUN_00bb9ae0",
    "FUN_00c31470",
    "FUN_00c31bf0",
    "FUN_0102fd40",
    "FUN_01021300",
    "FUN_00b1fdb0"
  ],
  "callers": [
    "FUN_0106cc70",
    "FUN_010021a0",
    "FUN_010697b0",
    "FUN_010229d0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00ffc4e0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "param_1",
      "storage": "",
      "type": "undefined4"
    },
    {
      "name": "param_2",
      "storage": "Stack[0x8]:4",
      "type": "undefined4"
    },
    {
      "name": "cVar1",
      "storage": "register:00000000:1",
      "type": "char"
    },
    {
      "name": "iVar2",
      "storage": "register:00000000:4",
      "type": "int"
    },
    {
      "name": "uVar3",
      "storage": "register:00000000:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 5,
  "mode": "live",
  "name": "FUN_00ffc4e0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xbfc4e0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00ffc4e0(void)",
  "size_bytes": 202,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00ffc4e0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 8,
  "xrefs": [
    {
      "from": "0106cfd3"
    },
    {
      "from": "010698b6"
    },
    {
      "from": "00c45548"
    },
    {
      "from": "00c57399"
    },
    {
      "from": "00c573f9"
    },
    {
      "from": "010021f0"
    },
    {
      "from": "0104b1e6"
    },
    {
      "from": "010229f2"
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
