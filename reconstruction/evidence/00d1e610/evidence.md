# Evidence 0x00d1e610

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `cc560f8e02952ad983d0db59208f2fdbc2a2c44c22ab49059860647de1da7ddb`

## abi

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "abi": {
    "architecture": "x86-32",
    "receiver": false,
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
    "saved_registers": [
      "ESI"
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -8, so the listing is not one path",
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
  "content_sha256": "db5b821ddd500bd87e676d22bdb4d835630d3455186483d0bc1edb9740a7e0ac",
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
        "obs-0006"
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
        "obs-0015"
      ],
      "claim": "ECX is never read in any form, so there is no register receiver",
      "confidence": "OBSERVED",
      "id": "R2",
      "value": {
        "present": false
      }
    },
    {
      "based_on": [
        "obs-0015"
      ],
      "claim": "the function is byte-identical under all four conventions",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0006"
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
        "obs-0006",
        "obs-0015"
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
        "obs-0006"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0006"
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
      "at": "0x00d1e610",
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
      "at": "0x00d1e611",
      "definite": true,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "XOR ESI,ESI",
      "reg": "ESI",
      "write_kind": "zero"
    },
    {
      "at": "0x00d1e613",
      "id": "obs-0003",
      "index": 2,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00b5b800",
      "target": "0x00b5b800"
    },
    {
      "at": "0x00d1e618",
      "definite": true,
      "id": "obs-0004",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "SUB EAX,0x1654c01",
      "reg": "EAX",
      "write_kind": "arith"
    },
    {
      "at": "0x00d1e62b",
      "id": "obs-0005",
      "index": 10,
      "kind": "REG_RESTORE",
      "raw": "POP ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00d1e62c",
      "form": "RET",
      "id": "obs-0006",
      "imm": null,
      "index": 11,
      "kind": "RET",
      "raw": "RET"
    },
    {
      "at": "0x00d1e62d",
      "id": "obs-0007",
      "index": 12,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00b3d300",
      "target": "0x00b3d300"
    },
    {
      "at": "0x00d1e632",
      "count": 3,
      "first_use": 13,
      "first_write_index": 3,
      "id": "obs-0008",
      "index": 13,
      "kind": "REG_READ",
      "raw": "MOV ECX,EAX",
      "reg": "EAX"
    },
    {
      "at": "0x00d1e632",
      "definite": true,
      "id": "obs-0009",
      "index": 13,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,EAX",
      "reg": "ECX",
      "write_kind": "reg"
    },
    {
      "at": "0x00d1e634",
      "id": "obs-0010",
      "index": 14,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00bfc5f0",
      "target": "0x00bfc5f0"
    },
    {
      "at": "0x00d1e63f",
      "id": "obs-0011",
      "index": 18,
      "kind": "REG_RESTORE",
      "raw": "POP ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00d1e640",
      "id": "obs-0012",
      "index": 19,
      "kind": "UNCOND_TRANSFER_OUT",
      "raw": "JMP 0x00c00650",
      "target": "0x00c00650"
    },
    {
      "at": "0x00d1e645",
      "id": "obs-0013",
      "index": 20,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00b3d300",
      "target": "0x00b3d300"
    },
    {
      "at": "0x00d1e64c",
      "id": "obs-0014",
      "index": 22,
      "kind": "REG_RESTORE",
      "raw": "POP ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00d1e64d",
      "id": "obs-0015",
      "index": 23,
      "kind": "UNCOND_TRANSFER_OUT",
      "raw": "JMP 0x00b1fdb0",
      "target": "0x00b1fdb0"
    }
  ],
  "parse":
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
"\nundefined4 FUN_00d1e610(void)\n\n{\n  undefined *puVar1;\n  int iVar2;\n  undefined4 uVar3;\n  \n  puVar1 = (undefined *)FUN_00b5b800();\n  if (puVar1 != &DAT_01654c01) {\n    if (puVar1 == &DAT_01654c02) {\n      FUN_00b3d300();\n      iVar2 = FUN_00bfc5f0();\n      if (iVar2 != 0) {\n        uVar3 = FUN_00c00650();\n        return uVar3;\n      }\n    }\n    else if (puVar1 == &DAT_01654c10) goto LAB_00d1e645;\n    return 0;\n  }\nLAB_00d1e645:\n  FUN_00b3d300();\n  uVar3 = FUN_00b1fdb0();\n  return uVar3;\n}\n\n"
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
      "address": "00d1e610",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00d1e611",
      "instruction": "XOR ESI,ESI"
    },
    {
      "address": "00d1e613",
      "instruction": "CALL 0x00b5b800"
    },
    {
      "address": "00d1e618",
      "instruction": "SUB EAX,0x1654c01"
    },
    {
      "address": "00d1e61d",
      "instruction": "JZ 0x00d1e645"
    },
    {
      "address": "00d1e61f",
      "instruction": "SUB EAX,0x1"
    },
    {
      "address": "00d1e622",
      "instruction": "JZ 0x00d1e62d"
    },
    {
      "address": "00d1e624",
      "instruction": "SUB EAX,0xe"
    },
    {
      "address": "00d1e627",
      "instruction": "JZ 0x00d1e645"
    },
    {
      "address": "00d1e629",
      "instruction": "MOV EAX,ESI"
    },
    {
      "address": "00d1e62b",
      "instruction": "POP ESI"
    },
    {
      "address": "00d1e62c",
      "instruction": "RET"
    },
    {
      "address": "00d1e62d",
      "instruction": "CALL 0x00b3d300"
    },
    {
      "address": "00d1e632",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00d1e634",
      "instruction": "CALL 0x00bfc5f0"
    },
    {
      "address": "00d1e639",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00d1e63b",
      "instruction": "JZ 0x00d1e629"
    },
    {
      "address": "00d1e63d",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00d1e63f",
      "instruction": "POP ESI"
    },
    {
      "address": "00d1e640",
      "instruction": "JMP 0x00c00650"
    },
    {
      "address": "00d1e645",
      "instruction": "CALL 0x00b3d300"
    },
    {
      "address": "00d1e64a",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00d1e64c",
      "instruction": "POP ESI"
    },
    {
      "address": "00d1e64d",
      "instruction": "JMP 0x00b1fdb0"
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
  "body_end": "00d1e651",
  "body_span_bytes": 66,
  "body_start": "00d1e610",
  "callees": [
    "FUN_00b3d300",
    "FUN_00c00650",
    "FUN_00bfc5f0",
    "FUN_00b1fdb0",
    "FUN_00b5b800"
  ],
  "callers": [
    "FUN_00d49450",
    "FUN_00d48b00",
    "FUN_00d49270",
    "FUN_00d200a0",
    "FUN_00d4a5f0",
    "FUN_00d1e830",
    "FUN_00d49560"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00d1e610",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "uVar3",
      "storage": "register:00000000:4",
      "type": "undefined4"
    },
    {
      "name": "iVar2",
      "storage": "register:00000000:4",
      "type": "int"
    },
    {
      "name": "puVar1",
      "storage": "register:00000000:4",
      "type": "undefined *"
    }
  ],
  "locals_count": 3,
  "mode": "live",
  "name": "FUN_00d1e610",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x91e610",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00d1e610(void)",
  "size_bytes": 66,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00d1e610",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 8,
  "xrefs": [
    {
      "from": "00d49473"
    },
    {
      "from": "00d49273"
    },
    {
      "from": "00d49561"
    },
    {
      "from": "00d200c5"
    },
    {
      "from": "00d1e840"
    },
    {
      "from": "00d4a736"
    },
    {
      "from": "00d48b01"
    },
    {
      "from": "00d4ab0a"
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
