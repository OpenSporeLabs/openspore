# Evidence 0x00ff5270

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `0648f1e3db53de13c12d3808faa555f2e00a435bf3548cd1abeccf710127de55`

## abi

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "abi": {
    "architecture": "x86-32",
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
    "ret_form": "RET",
    "return_register": "ST0",
    "return_semantics": "float_or_x87_in_ST0",
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
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +12, so the listing is not one path",
    "receiver_not_determinable: ecx_read_without_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_read_without_deref), and the convention rule that would apply discriminates on receiver absence"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate",
    "side": "caller"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "befc7d24be5e52303008c094d7f9e52c34ad778bcd13f8a24f3ccc0e473b2a9a",
  "conventions": {
    "ambiguities": [
      "receiver_undetermined"
    ],
    "calling_convention": null,
    "candidate_conventions": [
      "__cdecl",
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
    "indirect_calls": 4,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0036"
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
        "obs-0004",
        "obs-0005",
        "obs-0020"
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
        "obs-0004",
        "obs-0005",
        "obs-0020"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_read_without_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0036"
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
        "obs-0036"
      ],
      "claim": "the return value is carried in ST0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "ST0"
    }
  ],
  "observations": [
    {
      "at": "0x00ff5270",
      "count": 10,
      "first_use": 0,
      "first_write_index": 5,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00ff5271",
      "count": 2,
      "first_use": 1,
      "first_write_index": 6,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00ff5272",
      "id": "obs-0003",
      "index": 2,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00b3d300",
      "target": "0x00b3d300"
    },
    {
      "at": "0x00ff5277",
      "count": 14,
      "first_use": 3,
      "first_write_index": 7,
      "id": "obs-0004",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV ECX,EAX",
      "reg": "EAX"
    },
    {
      "at": "0x00ff5277",
      "definite": true,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,EAX",
      "reg": "ECX",
      "write_kind": "reg"
    },
    {
      "at": "0x00ff5279",
      "id": "obs-0006",
      "index": 4,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00b1f9d0",
      "target": "0x00b1f9d0"
    },
    {
      "at": "0x00ff527e",
      "count": 5,
      "first_use": 5,
      "first_write_index": 63,
      "id": "obs-0007",
      "index": 5,
      "kind": "REG_READ",
      "raw": "MOV ESI,dword ptr [ESP + 0xc]",
      "reg": "ESP"
    },
    {
      "at": "0x00ff527e",
      "base": "ESP",
      "disp": 12,
      "id": "obs-0008",
      "index": 5,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV ESI,dword ptr [ESP + 0xc]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00ff527e",
      "definite": true,
      "id": "obs-0009",
      "index": 5,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,dword ptr [ESP + 0xc]",
      "reg": "ESI",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00ff5282",
      "definite": true,
      "id": "obs-0010",
      "index": 6,
      "kind": "REG_WRITE",
      "raw": "MOV E
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
"\nvoid FUN_00ff5270(int *param_1)\n\n{\n  int iVar1;\n  int iVar2;\n  int iVar3;\n  undefined4 uVar4;\n  float unaff_ESI;\n  undefined4 unaff_retaddr;\n  \n  FUN_00b3d300();\n  iVar1 = FUN_00b1f9d0();\n  iVar2 = (**(code **)(*param_1 + 0x4c))();\n  if (iVar2 != iVar1) {\n    iVar1 = (**(code **)(*param_1 + 0xc))(0x901f1362);\n    iVar2 = (**(code **)(*param_1 + 0xc))(0x4f396a66);\n    iVar3 = (**(code **)(*param_1 + 0xc))(0xee9b2232);\n    uVar4 = 0;\n    if (iVar1 != 0) {\n      uVar4 = FUN_00bef8e0();\n    }\n    if (iVar2 != 0) {\n      uVar4 = FUN_00c8e7e0();\n    }\n    if (iVar3 != 0) {\n      FUN_00bd9bf0();\n      uVar4 = FUN_00bef8e0();\n    }\n    if (unaff_ESI != 0.0) {\n      FUN_00ff51f0(uVar4,unaff_ESI,unaff_retaddr);\n    }\n  }\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 67,
  "instructions": [
    {
      "address": "00ff5270",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00ff5271",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00ff5272",
      "instruction": "CALL 0x00b3d300"
    },
    {
      "address": "00ff5277",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00ff5279",
      "instruction": "CALL 0x00b1f9d0"
    },
    {
      "address": "00ff527e",
      "instruction": "MOV ESI,dword ptr [ESP + 0xc]"
    },
    {
      "address": "00ff5282",
      "instruction": "MOV EDI,EAX"
    },
    {
      "address": "00ff5284",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "00ff5286",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4c]"
    },
    {
      "address": "00ff5289",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00ff528b",
      "instruction": "CALL EDX"
    },
    {
      "address": "00ff528d",
      "instruction": "CMP EAX,EDI"
    },
    {
      "address": "00ff528f",
      "instruction": "JZ 0x00ff5320"
    },
    {
      "address": "00ff5295",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "00ff5297",
      "instruction": "MOV EDX,dword ptr [EAX + 0xc]"
    },
    {
      "address": "00ff529a",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00ff529b",
      "instruction": "PUSH 0x901f1362"
    },
    {
      "address": "00ff52a0",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00ff52a2",
      "instruction": "CALL EDX"
    },
    {
      "address": "00ff52a4",
      "instruction": "MOV EDI,EAX"
    },
    {
      "address": "00ff52a6",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "00ff52a8",
      "instruction": "MOV EDX,dword ptr [EAX + 0xc]"
    },
    {
      "address": "00ff52ab",
      "instruction": "PUSH 0x4f396a66"
    },
    {
      "address": "00ff52b0",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00ff52b2",
      "instruction": "CALL EDX"
    },
    {
      "address": "00ff52b4",
      "instruction": "MOV EBX,EAX"
    },
    {
      "address": "00ff52b6",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "00ff52b8",
      "instruction": "MOV EDX,dword ptr [EAX + 0xc]"
    },
    {
      "address": "00ff52bb",
      "instruction": "PUSH 0xee9b2232"
    },
    {
      "address": "00ff52c0",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00ff52c2",
      "instruction": "CALL EDX"
    },
    {
      "address": "00ff52c4",
      "instruction": "XOR ECX,ECX"
    },
    {
      "address": "00ff52c6",
      "instruction": "MOV ESI,EAX"
    },
    {
      "address": "00ff52c8",
      "instruction": "TEST EDI,EDI"
    },
    {
      "address": "00ff52ca",
      "instruction": "JZ 0x00ff52d5"
    },
    {
      "address": "00ff52cc",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00ff52ce",
      "instruction": "CALL 0x00bef8e0"
    },
    {
      "address": "00ff52d3",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00ff52d5",
      "instruction": "TEST EBX,EBX"
    },
    {
      "address": "00ff52d7",
      "instruction": "JZ 0x00ff52e2"
    },
    {
      "address": "00ff52d9",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "00ff52db",
      "instruction": "CALL 0x00c8e7e0"
    },
    {
      "address": "00ff52e0",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00ff52e2",
      "instruction": "POP EBX"
    },
    {
      "address": "00ff52e3",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "00ff52e5",
      "instruction": "JZ 0x00ff52f7"
    },
    {
      "address": "00ff52e7",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00ff52e9",
      "instruction": "CALL 0x00bd9bf0"
    },
    {
      "address": "00ff52ee",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00ff52f0",
      "instruction": "CALL 0x00bef8e0"
    },
    {
      "address": "00ff52f5",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00ff52f7",
      "instruction": "MOVSS XMM0,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00ff52fd",
      "instruction": "UCOMISS XMM0,dword ptr [0x01485378]"
    },
    {
      "address": "00ff5304",
      "instruction": "LAHF"
    },
    {
      "address": "00ff5305",
      "instruction": "TEST AH,0x44"
    },
    {
      "address": "00ff5308",
      "instruction": "JNP 0x00ff5320"
    },
    {
      "address": "00ff530a",
      "instruction": "MOV EAX,dword ptr [ESP + 0x14]"
    },
    {
      "address": "00ff530e",
      "instruction": "FLD float ptr [ESP + 0x10]"
    },
    {
      "address": "00ff5312",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00ff5313",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00ff5314",
      "instruction": "FSTP float ptr [ESP]"
    },
    {
      "address": "00ff5317",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00ff5318",
      "instruction": "CALL 0x00ff51f0"
    },
    {
      "address": "00ff531d",
      "instruction": "ADD ESP,0xc"
    },
    {
      "address": "00ff5320",
      "instruction": "POP EDI"
    },
    {
      "address": "00ff5321",
      "instruction": "POP ESI"
    },
    {
      "address": "00ff5322",
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
  "body_end": "00ff5322",
  "body_span_bytes": 179,
  "body_start": "00ff5270",
  "callees": [
    "FUN_00b1f9d0",
    "FUN_00c8e7e0",
    "FUN_00bd9bf0",
    "FUN_00bef8e0",
    "FUN_00b3d300",
    "FUN_00ff51f0"
  ],
  "callers": [
    "FUN_00bdc8a0",
    "FUN_0103fe90",
    "FUN_010593e0",
    "FUN_01030ef0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00ff5270",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "iVar1",
      "storage": "register:00000000:4",
      "type": "int"
    },
    {
      "name": "iVar2",
      "storage": "register:00000000:4",
      "type": "int"
    },
    {
      "name": "iVar3",
      "storage": "register:00000000:4",
      "type": "int"
    },
    {
      "name": "uVar4",
      "storage": "register:00000004:4",
      "type": "undefined4"
    },
    {
      "name": "unaff_ESI",
      "storage": "register:00000018:4",
      "type": "float"
    },
    {
      "name": "unaff_retaddr",
      "storage": "Stack[0x0]:4",
      "type": "undefined4"
    },
    {
      "name": "param_1",
      "storage": "Stack[0x4]:4",
      "type": "int *"
    }
  ],
  "locals_count": 7,
  "mode": "live",
  "name": "FUN_00ff5270",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xbf5270",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00ff5270(void)",
  "size_bytes": 179,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00ff5270",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 6,
  "xrefs": [
    {
      "from": "00bdc934"
    },
    {
      "from": "0103ffa8"
    },
    {
      "from": "0105994b"
    },
    {
      "from": "01059a14"
    },
    {
      "from": "00fe30ac"
    },
    {
      "from": "01030f9f"
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
