# Evidence 0x00b8d9b0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `812682e24959d2fc5a6e87e46543bc7b4ceec18bbcca430336f8d09fd7e6ebf9`

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
    "return_semantics": "unclassified_in_EAX",
    "saved_registers": [
      "EDI",
      "ESI"
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
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
  "content_sha256": "cf67bae81102ee0333a1b382dba38199bdb28a5b08d6427c753a94c3c11f6cfa",
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
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0018"
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
        "obs-0006",
        "obs-0007"
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
        "obs-0018"
      ],
      "claim": "the function is byte-identical under all four conventions",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0018"
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
        "obs-0014",
        "obs-0018"
      ],
      "claim": "the function can reach a caller by transferring out of the listing, so the path that actually returns was never observed",
      "confidence": "UNKNOWN",
      "id": "T2",
      "value": {
        "form": "epilogue_then_jmp"
      }
    },
    {
      "based_on": [
        "obs-0018"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0018"
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
      "at": "0x00b8d9b0",
      "count": 3,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00b8d9b1",
      "count": 1,
      "first_use": 1,
      "first_write_index": 5,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00b8d9b1",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00b8d9b3",
      "count": 2,
      "first_use": 2,
      "first_write_index": 7,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00b8d9b5",
      "id": "obs-0005",
      "index": 4,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00b3d2a0",
      "target": "0x00b3d2a0"
    },
    {
      "at": "0x00b8d9ba",
      "count": 4,
      "first_use": 5,
      "first_write_index": 20,
      "id": "obs-0006",
      "index": 5,
      "kind": "REG_READ",
      "raw": "MOV ECX,EAX",
      "reg": "EAX"
    },
    {
      "at": "0x00b8d9ba",
      "definite": true,
      "id": "obs-0007",
      "index": 5,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,EAX",
      "reg": "ECX",
      "write_kind": "reg"
    },
    {
      "at": "0x00b8d9bc",
      "id": "obs-0008",
      "index": 6,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00bb99e0",
      "target": "0x00bb99e0"
    },
    {
      "at": "0x00b8d9c1",
      "definite": true,
      "id": "obs-0009",
      "index": 7,
      "kind": "REG_WRITE",
      "raw": "MOV EDI,EAX",
      "reg": "EDI",
      "write_kind": "reg"
    },
    {
      "at": "0x00b8d9c8",
      "id": "obs-0010",
      "index": 11,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00feb9f0",
      "target": "0x00feb9f0"
    },
    {
      "at": "0x00b8d9cf",
      "id": "obs-0011",
      "index": 13,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00fee220",
      "target": "0x00fee220"
    },
    {
      "at": "0x00b8d9d8",
      "id": "obs-0012",
      "index": 16,
      "kind": "REG_RESTORE",
      "raw": "POP EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00b8d9db",
      "id": "obs-0013",
      "index": 18,
      "kind": "REG_RESTORE",
      "raw": "POP ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00b8d9dc",
      "id": "obs-0014",
      "index": 19,
      "kind": "UNCOND_TRANSFER_OUT",
      "raw": "JMP 0x00c4b220",
      "target": "0x00c4b220"
    },
    {
      "at":
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
"\nint __fastcall FUN_00b8d9b0(undefined4 param_1)\n\n{\n  int iVar1;\n  int iVar2;\n  undefined4 uVar3;\n  \n  uVar3 = param_1;\n  FUN_00b3d2a0(param_1);\n  iVar1 = FUN_00bb99e0(uVar3);\n  if (iVar1 == 0) {\n    FUN_00feb9f0(param_1);\n    iVar2 = FUN_00fee220(param_1);\n    if (iVar2 != 0) {\n      iVar1 = FUN_00c4b220();\n      return iVar1;\n    }\n  }\n  return iVar1;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 24,
  "instructions": [
    {
      "address": "00b8d9b0",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00b8d9b1",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00b8d9b3",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00b8d9b4",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00b8d9b5",
      "instruction": "CALL 0x00b3d2a0"
    },
    {
      "address": "00b8d9ba",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00b8d9bc",
      "instruction": "CALL 0x00bb99e0"
    },
    {
      "address": "00b8d9c1",
      "instruction": "MOV EDI,EAX"
    },
    {
      "address": "00b8d9c3",
      "instruction": "TEST EDI,EDI"
    },
    {
      "address": "00b8d9c5",
      "instruction": "JNZ 0x00b8d9e3"
    },
    {
      "address": "00b8d9c7",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00b8d9c8",
      "instruction": "CALL 0x00feb9f0"
    },
    {
      "address": "00b8d9cd",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00b8d9cf",
      "instruction": "CALL 0x00fee220"
    },
    {
      "address": "00b8d9d4",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00b8d9d6",
      "instruction": "JZ 0x00b8d9e1"
    },
    {
      "address": "00b8d9d8",
      "instruction": "POP EDI"
    },
    {
      "address": "00b8d9d9",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00b8d9db",
      "instruction": "POP ESI"
    },
    {
      "address": "00b8d9dc",
      "instruction": "JMP 0x00c4b220"
    },
    {
      "address": "00b8d9e1",
      "instruction": "MOV EAX,EDI"
    },
    {
      "address": "00b8d9e3",
      "instruction": "POP EDI"
    },
    {
      "address": "00b8d9e4",
      "instruction": "POP ESI"
    },
    {
      "address": "00b8d9e5",
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
  "body_end": "00b8d9e5",
  "body_span_bytes": 54,
  "body_start": "00b8d9b0",
  "callees": [
    "FUN_00feb9f0",
    "FUN_00c4b220",
    "FUN_00b3d2a0",
    "FUN_00bb99e0",
    "FUN_00fee220"
  ],
  "callers": [
    "FUN_00e98500",
    "FUN_00fdf5f0",
    "FUN_00c44d00",
    "FUN_00e2eba0",
    "FUN_00fe7e60",
    "FUN_00c59540",
    "FUN_00b8d9f0",
    "FUN_00fdf5b0",
    "FUN_00bba870",
    "FUN_00c59240",
    "FUN_010727e0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00b8d9b0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "uVar3",
      "storage": "Stack[-0xc]:4",
      "type": "undefined4"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "undefined4"
    },
    {
      "name": "iVar1",
      "storage": "register:00000000:4",
      "type": "int"
    },
    {
      "name": "iVar2",
      "storage": "register:00000000:4",
      "type": "int"
    }
  ],
  "locals_count": 4,
  "mode": "live",
  "name": "FUN_00b8d9b0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x78d9b0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00b8d9b0(void)",
  "size_bytes": 54,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00b8d9b0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 11,
  "xrefs": [
    {
      "from": "00b8da09"
    },
    {
      "from": "00bba885"
    },
    {
      "from": "00c593f3"
    },
    {
      "from": "00c596fc"
    },
    {
      "from": "00e98913"
    },
    {
      "from": "00fdf5bf"
    },
    {
      "from": "01072899"
    },
    {
      "from": "00fdf61f"
    },
    {
      "from": "00fe7ee2"
    },
    {
      "from": "00e2ebbb"
    },
    {
      "from": "00c44d16"
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
