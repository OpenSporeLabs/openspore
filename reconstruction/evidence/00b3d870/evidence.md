# Evidence 0x00b3d870

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `9c30b6c6d843737dff3565228fbcdeeed1d158a624f7844b1578fddd826a8788`

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
    "receiver": true,
    "receiver_register": "ECX",
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
    "flow_not_modelled: the linear ESP walk ends at +4, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "387f432c780ee6f0c392ee159b4f9ff10f5eee598d28f5eb208652a6a21db2ce",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall",
      "__fastcall"
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
        "obs-0008"
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
        "obs-0003"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          0,
          4
        ],
        "register": "ECX",
        "written_through": 1
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0008"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0008"
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
        "obs-0008"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0008"
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
      "at": "0x00b3d870",
      "count": 6,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00b3d871",
      "count": 2,
      "first_use": 1,
      "first_write_index": null,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00b3d871",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00b3d876",
      "definite": true,
      "id": "obs-0004",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESI]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00b3d87d",
      "count": 2,
      "first_use": 6,
      "first_write_index": 3,
      "id": "obs-0005",
      "index": 6,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [EAX]",
      "reg": "EAX"
    },
    {
      "at": "0x00b3d883",
      "id": "obs-0006",
      "index": 9,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00c03520",
      "target": "0x00c03520"
    },
    {
      "at": "0x00b3d88e",
      "id": "obs-0007",
      "index": 13,
      "kind": "REG_RESTORE",
      "raw": "POP ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00b3d88f",
      "form": "RET",
      "id": "obs-0008",
      "imm": null,
      "index": 14,
      "kind": "RET",
      "raw": "RET"
    }
  ],
  "parse": {
    "declared_count": 15,
    "degraded": false,
    "esp_unresolved": false,
    "flow_complete": false,
    "frame": {
      "and_esp": null,
      "ebp_is_general_register": false,
      "fp": false,
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": false,
      "push_ebp_at": null,
      "sub": null
    },
    "layout": "json_instruction_list",
    "local_extent": 0,
    "unparsed": 0
  },
  "receiver": {
    "bounds_only": true,
    "confidence": "INFERRED",
    "distinct_offsets": 2,
    "max_offset": 4,
    "offsets": [
      0,
      4
    ],
    "present": true,
    "register": "ECX",
    "shape": "R-ALIAS",
    "written_through": 1
  },
  "return": {
    "aggregate_evidence": {
      "bulk_write": false
    },
    "confidence": "INFERRED",
    "register": "EAX",
    "register_class": "aggregate_unknown",
    "type": null,
    "void_possible": false
  },
  "schema": "openspore-abi-inference-1",
  "seh_or_cookie_frame": false,
  "sret": {
    "ambiguity": null,
    "basis": "entry slot 0 is not written through a pointer; DERIVED absence is weak, a struct filled through another alias would be missed",
    "candidates": null,
    "confidence": "A
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
"\nint * __fastcall FUN_00b3d870(int *param_1)\n\n{\n  char cVar1;\n  \n  do {\n    *param_1 = *param_1 + 4;\n    if ((undefined4 *)*param_1 == (undefined4 *)param_1[1]) {\n      return param_1;\n    }\n    cVar1 = FUN_00c03520(*(undefined4 *)*param_1);\n  } while (cVar1 == '\\0');\n  return param_1;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 15,
  "instructions": [
    {
      "address": "00b3d870",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00b3d871",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00b3d873",
      "instruction": "ADD dword ptr [ESI],0x4"
    },
    {
      "address": "00b3d876",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "00b3d878",
      "instruction": "CMP EAX,dword ptr [ESI + 0x4]"
    },
    {
      "address": "00b3d87b",
      "instruction": "JZ 0x00b3d88c"
    },
    {
      "address": "00b3d87d",
      "instruction": "MOV EAX,dword ptr [EAX]"
    },
    {
      "address": "00b3d87f",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00b3d880",
      "instruction": "LEA ECX,[ESI + 0x8]"
    },
    {
      "address": "00b3d883",
      "instruction": "CALL 0x00c03520"
    },
    {
      "address": "00b3d888",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00b3d88a",
      "instruction": "JZ 0x00b3d873"
    },
    {
      "address": "00b3d88c",
      "instruction": "MOV EAX,ESI"
    },
    {
      "address": "00b3d88e",
      "instruction": "POP ESI"
    },
    {
      "address": "00b3d88f",
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
  "body_end": "00b3d88f",
  "body_span_bytes": 32,
  "body_start": "00b3d870",
  "callees": [
    "FUN_00c03520"
  ],
  "callers": [
    "FUN_00d90640",
    "FUN_00d6f1c0",
    "FUN_00d90950",
    "FUN_00d6eeb0",
    "FUN_00d90320",
    "FUN_00b493e0"
  ],
  "classification": "wrapper",
  "dispatch": null,
  "entry_point": "00b3d870",
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
      "type": "int *"
    },
    {
      "name": "cVar1",
      "storage": "register:00000000:1",
      "type": "char"
    }
  ],
  "locals_count": 2,
  "mode": "live",
  "name": "FUN_00b3d870",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x73d870",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00b3d870(void)",
  "size_bytes": 32,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00b3d870",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 6,
  "xrefs": [
    {
      "from": "00b49614"
    },
    {
      "from": "00d6eeef"
    },
    {
      "from": "00d6f31a"
    },
    {
      "from": "00d903a7"
    },
    {
      "from": "00d90706"
    },
    {
      "from": "00d909c6"
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
