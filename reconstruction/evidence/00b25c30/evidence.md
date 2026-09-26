# Evidence 0x00b25c30

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `92ea5bb6dbe8c09fba8d836c5842f961c9d7dc2464cf4f4ff86b8c6957c06636`

## abi

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "abi": {
    "architecture": "x86-32",
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
    "flow_not_modelled: the linear ESP walk ends at +8, so the listing is not one path",
    "unparsed_lines_present: 1 line(s) matched no grammar rule",
    "receiver_not_determinable: ecx_read_without_deref",
    "no_discriminator: no stack-argument read and no positive receiver evidence"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "0d99ac3ac8a10625885ba12c2088535811e1be67c9e8100f4dd3a55ccd8b647f",
  "conventions": {
    "ambiguities": [],
    "calling_convention": null,
    "candidate_conventions": [
      "__cdecl",
      "__stdcall",
      "__thiscall",
      "__fastcall"
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
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0018",
        "obs-0023"
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
        "obs-0011",
        "obs-0019"
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
        "obs-0023"
      ],
      "claim": "the function is byte-identical under all four conventions",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0018",
        "obs-0023"
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
        "obs-0018",
        "obs-0023"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0018",
        "obs-0023"
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
      "at": "0x00b25c30",
      "count": 4,
      "first_use": 0,
      "first_write_index": 14,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00b25c31",
      "count": 5,
      "first_use": 1,
      "first_write_index": 9,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00b25c32",
      "count": 2,
      "first_use": 2,
      "first_write_index": 10,
      "id": "obs-0003",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00b25c4c",
      "id": "obs-0004",
      "index": 8,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00b21340",
      "target": "0x00b21340"
    },
    {
      "at": "0x00b25c51",
      "count": 6,
      "first_use": 9,
      "first_write_index": 17,
      "id": "obs-0005",
      "index": 9,
      "kind": "REG_READ",
      "raw": "MOV ESI,EAX",
      "reg": "EAX"
    },
    {
      "at": "0x00b25c51",
      "definite": true,
      "id": "obs-0006",
      "index": 9,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,EAX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00b25c53",
      "definite": true,
      "id": "obs-0007",
      "index": 10,
      "kind": "REG_WRITE",
      "raw": "MOV EDI,dword ptr [ESI + 0x8]",
      "reg": "EDI",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00b25c5f",
      "definite": true,
      "id": "obs-0008",
      "index": 14,
      "kind": "REG_WRITE",
      "raw": "XOR EBX,EBX",
      "reg": "EBX",
      "write_kind": "zero"
    },
    {
      "at": "0x00b25c65",
      "definite": true,
      "id": "obs-0009",
      "index": 17,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESI]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00b25c6a",
      "definite": true,
      "id": "obs-0010",
      "index": 19,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [EAX + 0x120]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00b25c70",
      "count": 2,
      "first_use": 20,
      "first_write_index": 33,
      "id": "obs-0011",
      "index": 20,
      "kind": "REG_READ",
      "raw": "LEA ECX,[EAX + 0x120]",
      "reg": "ECX"
    },
    {
      "at": "0x00b25c76",
      "count": 1,
      "first_use": 21,
      "first_write_index": 19,
      "id": "obs-0012",
      "index": 21,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [EDX + 0x58]",
      "reg": "EDX"
    },
    {
      "at": "0x00b25c79",
      "base": "EAX",
      "disp": null,
      "id": "obs-0013",
      "index": 22,
      "kind": "CALL_INDIRECT",
      "raw": "CALL EAX",
      "via": "re
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
"\nundefined4 FUN_00b25c30(void)\n\n{\n  char cVar1;\n  int iVar2;\n  uint uVar3;\n  uint uVar4;\n  \n  iVar2 = FUN_00b21340(&LAB_00cd7d10,&LAB_00d3d420,&LAB_00acdff0,&LAB_00b1e500,&DAT_018c43e8);\n  uVar4 = *(int *)(iVar2 + 8) - *(int *)(iVar2 + 4) >> 2;\n  uVar3 = 0;\n  if (uVar4 != 0) {\n    do {\n      cVar1 = (**(code **)(*(int *)(*(int *)(*(int *)(iVar2 + 4) + uVar3 * 4) + 0x120) + 0x58))();\n      if (cVar1 != '\\0') {\n        return *(undefined4 *)(*(int *)(iVar2 + 4) + uVar3 * 4);\n      }\n      uVar3 = uVar3 + 1;\n    } while (uVar3 < uVar4);\n  }\n  return 0;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 39,
  "instructions": [
    {
      "address": "00b25c30",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00b25c31",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00b25c32",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00b25c33",
      "instruction": "PUSH 0x18c43e8"
    },
    {
      "address": "00b25c38",
      "instruction": "PUSH 0xb1e500"
    },
    {
      "address": "00b25c3d",
      "instruction": "PUSH 0xacdff0"
    },
    {
      "address": "00b25c42",
      "instruction": "PUSH 0xd3d420"
    },
    {
      "address": "00b25c47",
      "instruction": "PUSH 0xcd7d10"
    },
    {
      "address": "00b25c4c",
      "instruction": "CALL 0x00b21340"
    },
    {
      "address": "00b25c51",
      "instruction": "MOV ESI,EAX"
    },
    {
      "address": "00b25c53",
      "instruction": "MOV EDI,dword ptr [ESI + 0x8]"
    },
    {
      "address": "00b25c56",
      "instruction": "SUB EDI,dword ptr [ESI + 0x4]"
    },
    {
      "address": "00b25c59",
      "instruction": "ADD ESI,0x4"
    },
    {
      "address": "00b25c5c",
      "instruction": "SAR EDI,0x2"
    },
    {
      "address": "00b25c5f",
      "instruction": "XOR EBX,EBX"
    },
    {
      "address": "00b25c61",
      "instruction": "TEST EDI,EDI"
    },
    {
      "address": "00b25c63",
      "instruction": "JBE 0x00b25c84"
    },
    {
      "address": "00b25c65",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "00b25c67",
      "instruction": "MOV EAX,dword ptr [EAX + EBX*0x4]"
    },
    {
      "address": "00b25c6a",
      "instruction": "MOV EDX,dword ptr [EAX + 0x120]"
    },
    {
      "address": "00b25c70",
      "instruction": "LEA ECX,[EAX + 0x120]"
    },
    {
      "address": "00b25c76",
      "instruction": "MOV EAX,dword ptr [EDX + 0x58]"
    },
    {
      "address": "00b25c79",
      "instruction": "CALL EAX"
    },
    {
      "address": "00b25c7b",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00b25c7d",
      "instruction": "JNZ 0x00b25c8a"
    },
    {
      "address": "00b25c7f",
      "instruction": "INC EBX"
    },
    {
      "address": "00b25c80",
      "instruction": "CMP EBX,EDI"
    },
    {
      "address": "00b25c82",
      "instruction": "JC 0x00b25c65"
    },
    {
      "address": "00b25c84",
      "instruction": "POP EDI"
    },
    {
      "address": "00b25c85",
      "instruction": "POP ESI"
    },
    {
      "address": "00b25c86",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "00b25c88",
      "instruction": "POP EBX"
    },
    {
      "address": "00b25c89",
      "instruction": "RET"
    },
    {
      "address": "00b25c8a",
      "instruction": "MOV ECX,dword ptr [ESI]"
    },
    {
      "address": "00b25c8c",
      "instruction": "MOV EAX,dword ptr [ECX + EBX*0x4]"
    },
    {
      "address": "00b25c8f",
      "instruction": "POP EDI"
    },
    {
      "address": "00b25c90",
      "instruction": "POP ESI"
    },
    {
      "address": "00b25c91",
      "instruction": "POP EBX"
    },
    {
      "address": "00b25c92",
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
  "body_end": "00b25c92",
  "body_span_bytes": 99,
  "body_start": "00b25c30",
  "callees": [
    "FUN_00b21340"
  ],
  "callers": [
    "FUN_00cfbc10",
    "FUN_00fdba50",
    "FUN_00cf9ba0",
    "FUN_01049040",
    "FUN_00cf1000",
    "FUN_00e352c0",
    "FUN_00cf7150",
    "FUN_00ff74f0",
    "FUN_00ff5ee0",
    "FUN_00c36030",
    "FUN_00ff60d0",
    "FUN_00cea1a0",
    "FUN_00bf4fc0",
    "FUN_00e35370",
    "FUN_00e07e70",
    "FUN_00cec7a0",
    "FUN_00bff2d0",
    "FUN_00cf8160"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00b25c30",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
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
      "storage": "register:0000000c:4",
      "type": "uint"
    },
    {
      "name": "uVar4",
      "storage": "register:0000001c:4",
      "type": "uint"
    }
  ],
  "locals_count": 4,
  "mode": "live",
  "name": "FUN_00b25c30",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x725c30",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00b25c30(void)",
  "size_bytes": 99,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00b25c30",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 26,
  "xrefs": [
    {
      "from": "00cf9eb6"
    },
    {
      "from": "00bff478"
    },
    {
      "from": "00bf4fe7"
    },
    {
      "from": "00c36097"
    },
    {
      "from": "00fdba7f"
    },
    {
      "from": "00ff5eee"
    },
    {
      "from": "00cea5c1"
    },
    {
      "from": "00cf101b"
    },
    {
      "from": "00e3530f"
    },
    {
      "from": "00e0826b"
    },
    {
      "from": "00e082aa"
    },
    {
      "from": "00e082de"
    },
    {
      "from": "00e3579a"
    },
    {
      "from": "00ff74fa"
    },
    {
      "from": "010496c7"
    },
    {
      "from": "00cfc163"
    },
    {
      "from": "00cfc1ab"
    },
    {
      "from": "00cecbb1"
    },
    {
      "from": "00cfcea1"
    },
    {
      "from": "00cf7159"
    },
    {
      "from": "00cee1f3"
    },
    {
      "from": "00cfd794"
    },
    {
      "from": "00cfd7b7"
    },
    {
      "from": "00cf83af"
    },
    {
      "from": "00ea72e1"
    },
    {
      "from": "00ff60f3"
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
