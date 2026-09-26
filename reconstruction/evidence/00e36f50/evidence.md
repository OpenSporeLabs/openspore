# Evidence 0x00e36f50

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `9358c4411e348e3cedd36ef42b51372592170ba6d706c18b3fcf602a7a08f2aa`

## abi

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "abi": {
    "architecture": "x86-32",
    "calling_convention": "__cdecl",
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
    "receiver": false,
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
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
  "abstained_because": [],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate",
    "side": "caller"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "fcea72e0baa3a9fe296f91c907a1e2865d86329e2828f91299d22a324225a46e",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__cdecl",
    "candidate_conventions": [
      "__cdecl",
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
        "obs-0006",
        "obs-0007",
        "obs-0008",
        "obs-0009",
        "obs-0010"
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
        "obs-0002"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "INFERRED",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 1,
        "total_bytes": 4
      }
    },
    {
      "based_on": [
        "obs-0010"
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
        "obs-0002",
        "obs-0006",
        "obs-0007",
        "obs-0008",
        "obs-0009",
        "obs-0010"
      ],
      "claim": "calling convention is __cdecl: the caller cleans the stack and at least one entry slot is read",
      "confidence": "INFERRED",
      "id": "C9",
      "value": "__cdecl"
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007",
        "obs-0008",
        "obs-0009",
        "obs-0010"
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
        "obs-0007",
        "obs-0008",
        "obs-0009",
        "obs-0010"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007",
        "obs-0008",
        "obs-0009",
        "obs-0010"
      ],
      "claim": "the last value written to EAX classifies as integral",
      "confidence": "INFERRED",
      "id": "RT2",
      "value": {
        "register_class": "integral"
      }
    }
  ],
  "observations": [
    {
      "at": "0x00e36f50",
      "count": 1,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV ECX,dword ptr [ESP + 0x4]",
      "reg": "ESP"
    },
    {
      "at": "0x00e36f50",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0002",
      "index": 0,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV ECX,dword ptr [ESP + 0x4]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00e36f50",
      "definite": true,
      "id": "obs-0003",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [ESP + 0x4]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00e36f54",
      "count": 2,
      "first_use": 1,
      "first_write_index": 1,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_READ",
      "raw": "XOR EAX,EAX",
      "reg": "EAX"
    },
    {
      "at": "0x00e36f54",
      "definite": true,
      "id": "obs-0005",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "XOR EAX,EAX",
      "reg": "EAX",
      "write_kind": "zero"
    },
    {
      "at": "0x00e36f75",
      "form": "RET",
      "id": "obs-0006",
      "imm": null,
      "index": 10,
      "kind": "RET",
      "raw": "RET"
    },
    {
      "at": "0x00e36f78",
      "form": "RET",
      "id": "obs-0007",
      "imm": null,
      "index": 12,
      "kind": "RET",
      "raw": "RET"
    },
    {
      "at": "0x00e36f7e",
      "form": "RET",
      "id": "obs-0008",
      "imm": null,
      "index": 14,
      "kind": "RET",
      "raw": "RET"
    },
    {
      "at": "0x00e36f94",
      "form": "RET",
      "id": "obs-0009",
      "imm": null,
      "index": 20,
      "kind": "RET",
      "raw": "RET"
    },
    {
      "at": "0x00e36f9a",
      "form": "RET",
      "id": "obs-0010",
      "imm": null,
      "index": 22,
      "kind": "RET",
      "raw": "RET"
    }
  ],
  "parse": {
    "declare
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
"\nundefined4 FUN_00e36f50(int param_1)\n\n{\n  undefined4 uVar1;\n  \n  uVar1 = 0;\n  if (param_1 < -0x414ad734) {\n    if (param_1 == -0x414ad735) {\n      return 3;\n    }\n    if (param_1 == -0x5bd98cf5) {\n      return 0;\n    }\n    if (param_1 == -0x52a9f7f4) {\n      return 1;\n    }\n  }\n  else if (param_1 == -0x8e05cef) {\n    uVar1 = 2;\n  }\n  else if (param_1 == 0x2db6dad3) {\n    return 4;\n  }\n  return uVar1;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 23,
  "instructions": [
    {
      "address": "00e36f50",
      "instruction": "MOV ECX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "00e36f54",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "00e36f56",
      "instruction": "CMP ECX,0xbeb528cb"
    },
    {
      "address": "00e36f5c",
      "instruction": "JG 0x00e36f7f"
    },
    {
      "address": "00e36f5e",
      "instruction": "JZ 0x00e36f79"
    },
    {
      "address": "00e36f60",
      "instruction": "CMP ECX,0xa426730b"
    },
    {
      "address": "00e36f66",
      "instruction": "JZ 0x00e36f76"
    },
    {
      "address": "00e36f68",
      "instruction": "CMP ECX,0xad56080c"
    },
    {
      "address": "00e36f6e",
      "instruction": "JNZ 0x00e36f9a"
    },
    {
      "address": "00e36f70",
      "instruction": "MOV EAX,0x1"
    },
    {
      "address": "00e36f75",
      "instruction": "RET"
    },
    {
      "address": "00e36f76",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "00e36f78",
      "instruction": "RET"
    },
    {
      "address": "00e36f79",
      "instruction": "MOV EAX,0x3"
    },
    {
      "address": "00e36f7e",
      "instruction": "RET"
    },
    {
      "address": "00e36f7f",
      "instruction": "CMP ECX,0xf71fa311"
    },
    {
      "address": "00e36f85",
      "instruction": "JZ 0x00e36f95"
    },
    {
      "address": "00e36f87",
      "instruction": "CMP ECX,0x2db6dad3"
    },
    {
      "address": "00e36f8d",
      "instruction": "JNZ 0x00e36f9a"
    },
    {
      "address": "00e36f8f",
      "instruction": "MOV EAX,0x4"
    },
    {
      "address": "00e36f94",
      "instruction": "RET"
    },
    {
      "address": "00e36f95",
      "instruction": "MOV EAX,0x2"
    },
    {
      "address": "00e36f9a",
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
  "body_end": "00e36f9a",
  "body_span_bytes": 75,
  "body_start": "00e36f50",
  "callees": [],
  "callers": [
    "FUN_00e3c000",
    "FUN_00e3b9e0",
    "FUN_00e3a730"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "00e36f50",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "uVar1",
      "storage": "register:00000000:4",
      "type": "undefined4"
    },
    {
      "name": "param_1",
      "storage": "Stack[0x4]:4",
      "type": "int"
    }
  ],
  "locals_count": 2,
  "mode": "live",
  "name": "FUN_00e36f50",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xa36f50",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00e36f50(void)",
  "size_bytes": 75,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00e36f50",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 3,
  "xrefs": [
    {
      "from": "00e3a7b8"
    },
    {
      "from": "00e3c01d"
    },
    {
      "from": "00e3bd62"
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
