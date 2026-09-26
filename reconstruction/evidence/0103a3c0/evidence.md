# Evidence 0x0103a3c0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `b3c11692863dbf7719518f54b714832ce0aab6b8160deaaa83cf41bd669a4874`

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
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
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
    "flow_not_modelled: the linear ESP walk ends at -8, so the listing is not one path",
    "receiver_not_determinable: ecx_reassigned_before_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_reassigned_before_deref), and the convention rule that would apply discriminates on receiver absence"
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
  "content_sha256": "ed6a4dc3545d7ce40e11d1509e73ccc5cdeb298a6cef712ff18afd0ed4bd2fef",
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
    "indirect_calls": 5,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0028",
        "obs-0042"
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
        "obs-0019",
        "obs-0033"
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
        "obs-0009",
        "obs-0010",
        "obs-0014",
        "obs-0015",
        "obs-0020",
        "obs-0022",
        "obs-0024",
        "obs-0035"
      ],
      "claim": "the register receiver is undetermined: ecx_reassigned_before_deref",
      "confidence": "UNKNOWN",
      "id": "R0",
      "value": {
        "reason": "ecx_reassigned_before_deref",
        "register": null
      }
    },
    {
      "based_on": [
        "obs-0009",
        "obs-0010",
        "obs-0014",
        "obs-0015",
        "obs-0020",
        "obs-0022",
        "obs-0024",
        "obs-0035"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_reassigned_before_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0028",
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
        "obs-0028",
        "obs-0042"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0028",
        "obs-0042"
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
      "and_esp": null,
      "at": "0x0103a3c0",
      "ebp_is_general_register": false,
      "fp": false,
      "id": "obs-0001",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": false,
      "push_ebp_at": null,
      "raw": "SUB ESP,0x10",
      "sub": 16
    },
    {
      "at": "0x0103a3c0",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x10",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x0103a3c3",
      "count": 7,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x0103a3c4",
      "definite": true,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "XOR ESI,ESI",
      "reg": "ESI",
      "write_kind": "zero"
    },
    {
      "at": "0x0103a3c6",
      "count": 3,
      "first_use": 3,
      "first_write_index": 7,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x0103a3c7",
      "count": 13,
      "first_use": 4,
      "first_write_index": 0,
      "id": "obs-0006",
      "index": 4,
      "kind": "REG_READ",
      "raw": "MOV dword ptr [ESP + 0x8],ESI",
      "reg": "ESP"
    },
    {
      "at": "0x0103a3c7",
      "base": "ESP",
      "disp": 8,
      "id": "obs-
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
"\n/* WARNING: Enum \"ObjectTYPE\": Some values do not have unique names */\n/* WARNING: Enum \"Names\": Some values do not have unique names */\n\nbool FUN_0103a3c0(undefined4 *param_1)\n\n{\n  int *piVar1;\n  char cVar2;\n  int *piVar3;\n  bool bVar4;\n  int **ppiStack_1c;\n  int *local_10 [4];\n  \n  local_10[0] = (int *)0x0;\n  ppiStack_1c = (int **)0x103a3d0;\n  piVar3 = (int *)FUN_0067de30();\n  piVar1 = local_10[0];\n  if (local_10[0] != (int *)0x0) {\n    local_10[0] = (int *)0x0;\n    ppiStack_1c = (int **)0x103a3e5;\n    (**(code **)(*piVar1 + 4))();\n  }\n  ppiStack_1c = local_10;\n  (**(code **)(*piVar3 + 0x2c))(*param_1);\n  if (ppiStack_1c != (int **)0x0) {\n    cVar2 = (*(code *)(*ppiStack_1c)[7])(0x34f1a4f);\n    if (cVar2 != '\\0') {\n      ppiStack_1c = (int **)0x0;\n      App__Property__GetKey((PropertyList *)0x34d97fa,0x34f1a4f,(ResourceKey *)&ppiStack_1c);\n      bVar4 = ppiStack_1c == (int **)0x7ecbe6f5;\n      (**(code **)(iRam034d97fa + 4))();\n      return bVar4;\n    }\n    (**(code **)(iRam034d97fa + 4))();\n  }\n  return false;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 68,
  "instructions": [
    {
      "address": "0103a3c0",
      "instruction": "SUB ESP,0x10"
    },
    {
      "address": "0103a3c3",
      "instruction": "PUSH ESI"
    },
    {
      "address": "0103a3c4",
      "instruction": "XOR ESI,ESI"
    },
    {
      "address": "0103a3c6",
      "instruction": "PUSH EDI"
    },
    {
      "address": "0103a3c7",
      "instruction": "MOV dword ptr [ESP + 0x8],ESI"
    },
    {
      "address": "0103a3cb",
      "instruction": "CALL 0x0067de30"
    },
    {
      "address": "0103a3d0",
      "instruction": "MOV ECX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "0103a3d4",
      "instruction": "MOV EDI,EAX"
    },
    {
      "address": "0103a3d6",
      "instruction": "CMP ECX,ESI"
    },
    {
      "address": "0103a3d8",
      "instruction": "JZ 0x0103a3e5"
    },
    {
      "address": "0103a3da",
      "instruction": "MOV dword ptr [ESP + 0x8],ESI"
    },
    {
      "address": "0103a3de",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "0103a3e0",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "0103a3e3",
      "instruction": "CALL EDX"
    },
    {
      "address": "0103a3e5",
      "instruction": "MOV EDX,dword ptr [ESP + 0x1c]"
    },
    {
      "address": "0103a3e9",
      "instruction": "MOV EAX,dword ptr [EDI]"
    },
    {
      "address": "0103a3eb",
      "instruction": "LEA ECX,[ESP + 0x8]"
    },
    {
      "address": "0103a3ef",
      "instruction": "PUSH ECX"
    },
    {
      "address": "0103a3f0",
      "instruction": "MOV ECX,dword ptr [EDX]"
    },
    {
      "address": "0103a3f2",
      "instruction": "MOV EDX,dword ptr [EAX + 0x2c]"
    },
    {
      "address": "0103a3f5",
      "instruction": "PUSH 0x34d97fa"
    },
    {
      "address": "0103a3fa",
      "instruction": "PUSH ECX"
    },
    {
      "address": "0103a3fb",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "0103a3fd",
      "instruction": "CALL EDX"
    },
    {
      "address": "0103a3ff",
      "instruction": "MOV ECX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "0103a403",
      "instruction": "CMP ECX,ESI"
    },
    {
      "address": "0103a405",
      "instruction": "JZ 0x0103a426"
    },
    {
      "address": "0103a407",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "0103a409",
      "instruction": "MOV EDX,dword ptr [EAX + 0x1c]"
    },
    {
      "address": "0103a40c",
      "instruction": "PUSH 0x34f1a4f"
    },
    {
      "address": "0103a411",
      "instruction": "CALL EDX"
    },
    {
      "address": "0103a413",
      "instruction": "MOV ECX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "0103a417",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "0103a419",
      "instruction": "JNZ 0x0103a42e"
    },
    {
      "address": "0103a41b",
      "instruction": "CMP ECX,ESI"
    },
    {
      "address": "0103a41d",
      "instruction": "JZ 0x0103a426"
    },
    {
      "address": "0103a41f",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "0103a421",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "0103a424",
      "instruction": "CALL EDX"
    },
    {
      "address": "0103a426",
      "instruction": "POP EDI"
    },
    {
      "address": "0103a427",
      "instruction": "XOR AL,AL"
    },
    {
      "address": "0103a429",
      "instruction": "POP ESI"
    },
    {
      "address": "0103a42a",
      "instruction": "ADD ESP,0x10"
    },
    {
      "address": "0103a42d",
      "instruction": "RET"
    },
    {
      "address": "0103a42e",
      "instruction": "PUSH EBX"
    },
    {
      "address": "0103a42f",
      "instruction": "LEA EAX,[ESP + 0x10]"
    },
    {
      "address": "0103a433",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0103a434",
      "instruction": "PUSH 0x34f1a4f"
    },
    {
      "address": "0103a439",
      "instruction": "PUSH ECX"
    },
    {
      "address": "0103a43a",
      "instruction": "MOV dword ptr [ESP + 0x1c],ESI"
    },
    {
      "address": "0103a43e",
      "instruction": "MOV dword ptr [ESP + 0x20],ESI"
    },
    {
      "address": "0103a442",
      "instruction": "MOV dword ptr [ESP + 0x24],ESI"
    },
    {
      "address": "0103a446",
      "instruction": "CALL 0x006a1250"
    },
    {
      "address": "0103a44b",
      "instruction": "MOV ECX,dword ptr [ESP + 0x18]"
    },
    {
      "address": "0103a44f",
      "instruction": "ADD ESP,0xc"
    },
    {
      "address": "0103a452",
      "instruction": "CMP dword ptr [ESP + 0x10],0x7ecbe6f5"
    },
    {
      "address": "0103a45a",
      "instruction": "SETZ BL"
    },
    {
      "address": "0103a45d",
      "instruction": "CMP ECX,ESI"
    },
    {
      "address": "0103a45f",
      "instruction": "JZ 0x0103a468"
    },
    {
      "address": "0103a461",
      "instruction": "MOV EDX,dword ptr [ECX]"
    },
    {
      "address": "0103a463",
      "instruction": "MOV EAX,dword ptr [EDX + 0x4]"
    },
    {
      "address": "0103a466",
      "instruction": "CALL EAX"
    },
    {
      "address": "0103a468",
      "instruction": "MOV AL,BL"
    },
    {
      "address": "0103a46a",
      "instruction": "POP EBX"
    },
    {
      "address": "0103a46b",
      "instruction": "POP EDI"
    },
    {
      "address": "0103a46c",
      "instruction": "POP ESI"
    },
    {
      "address": "0103a46d",
      "instruction": "ADD ESP,0x10"
    },
    {
      "address": "0103a470",
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
  "body_end": "0103a470",
  "body_span_bytes": 177,
  "body_start": "0103a3c0",
  "callees": [
    "App::Property::GetKey",
    "FUN_0067de30"
  ],
  "callers": [
    "FUN_00c52a70",
    "FUN_0103fc10"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "0103a3c0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "param_1",
      "storage": "Stack[0x4]:4",
      "type": "undefined4 *"
    },
    {
      "name": "ppiStack_1c",
      "storage": "Stack[-0x1c]:4",
      "type": "int * *"
    },
    {
      "name": "piVar3",
      "storage": "register:00000000:4",
      "type": "int *"
    },
    {
      "name": "bVar4",
      "storage": "register:00000206:1",
      "type": "bool"
    },
    {
      "name": "piVar1",
      "storage": "unique:100000ae:4",
      "type": "int *"
    },
    {
      "name": "cVar2",
      "storage": "register:00000000:1",
      "type": "char"
    },
    {
      "name": "local_10",
      "storage": "Stack[-0x10]:4",
      "type": "int *[4]"
    }
  ],
  "locals_count": 7,
  "mode": "live",
  "name": "FUN_0103a3c0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xc3a3c0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_0103a3c0(void)",
  "size_bytes": 177,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x0103a3c0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 4,
  "xrefs": [
    {
      "from": "0103fccd"
    },
    {
      "from": "00c5285a"
    },
    {
      "from": "00c52c38"
    },
    {
      "from": "00c54d67"
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
