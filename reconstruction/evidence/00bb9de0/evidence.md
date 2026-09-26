# Evidence 0x00bb9de0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `db249183c3c10cc2ec2bc5a43412d6c025352ca9ff5bcc78f0abfb35f24799ff`

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
  "abstained_because": [],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "9c4f07eed8794e0ac65641a5e4f5d3c4c64f4f61196d3d090d2191f073f629df",
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
        "obs-0007"
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
        "obs-0001",
        "obs-0002"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          96,
          100
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0002",
        "obs-0007"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0007"
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
        "obs-0007"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0007"
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
      "at": "0x00bb9de0",
      "count": 4,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ECX + 0x60]",
      "reg": "ECX"
    },
    {
      "at": "0x00bb9de0",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ECX + 0x60]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00bb9de6",
      "count": 3,
      "first_use": 2,
      "first_write_index": null,
      "id": "obs-0003",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00bb9ded",
      "id": "obs-0004",
      "index": 6,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00c8bff0",
      "target": "0x00c8bff0"
    },
    {
      "at": "0x00bb9df2",
      "definite": true,
      "id": "obs-0005",
      "index": 7,
      "kind": "REG_WRITE",
      "raw": "ADD ESP,0x4",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00bb9df7",
      "id": "obs-0006",
      "index": 9,
      "kind": "REG_RESTORE",
      "raw": "POP ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00bb9df8",
      "form": "RET",
      "id": "obs-0007",
      "imm": null,
      "index": 10,
      "kind": "RET",
      "raw": "RET"
    }
  ],
  "parse": {
    "declared_count": 11,
    "degraded": false,
    "esp_unresolved": false,
    "flow_complete": true,
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
    "max_offset": 100,
    "offsets": [
      96,
      100
    ],
    "present": true,
    "register": "ECX",
    "shape": "R-DIRECT",
    "written_through": 0
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
    "confidence": "APPROXIMATION",
    "eax_holds_slot0_at_ret": null,
    "hypothesis_confidence": null,
    "present": false,
    "slot": null,
    "this_interaction": null
  },
  "stack_arguments": {
    "confidence": "APPROXIMATION",
    "derived_slots": 0,
    "gaps": 0,
    "not_complete": false,
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
"\nint __fastcall FUN_00bb9de0(int param_1)\n\n{\n  if (*(int *)(param_1 + 0x60) == *(int *)(param_1 + 100)) {\n    FUN_00c8bff0(param_1);\n  }\n  return param_1 + 0x60;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 11,
  "instructions": [
    {
      "address": "00bb9de0",
      "instruction": "MOV EAX,dword ptr [ECX + 0x60]"
    },
    {
      "address": "00bb9de3",
      "instruction": "CMP EAX,dword ptr [ECX + 0x64]"
    },
    {
      "address": "00bb9de6",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00bb9de7",
      "instruction": "LEA ESI,[ECX + 0x60]"
    },
    {
      "address": "00bb9dea",
      "instruction": "JNZ 0x00bb9df5"
    },
    {
      "address": "00bb9dec",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00bb9ded",
      "instruction": "CALL 0x00c8bff0"
    },
    {
      "address": "00bb9df2",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "00bb9df5",
      "instruction": "MOV EAX,ESI"
    },
    {
      "address": "00bb9df7",
      "instruction": "POP ESI"
    },
    {
      "address": "00bb9df8",
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
  "body_end": "00bb9df8",
  "body_span_bytes": 25,
  "body_start": "00bb9de0",
  "callees": [
    "FUN_00c8bff0"
  ],
  "callers": [
    "FUN_00c48740",
    "FUN_0106cc70",
    "FUN_00c486f0",
    "FUN_00c8b540",
    "FUN_00ba81b0",
    "FUN_00c58920",
    "FUN_00c48900",
    "FUN_00c491c0",
    "FUN_00df7ce0"
  ],
  "classification": "wrapper",
  "dispatch": null,
  "entry_point": "00bb9de0",
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
    }
  ],
  "locals_count": 1,
  "mode": "live",
  "name": "FUN_00bb9de0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x7b9de0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00bb9de0(void)",
  "size_bytes": 25,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00bb9de0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 18,
  "xrefs": [
    {
      "from": "00c8b543"
    },
    {
      "from": "0106d6f9"
    },
    {
      "from": "00c58a04"
    },
    {
      "from": "00c491f4"
    },
    {
      "from": "00c48706"
    },
    {
      "from": "00c48756"
    },
    {
      "from": "00c4891b"
    },
    {
      "from": "00df7ddd"
    },
    {
      "from": "00dd097e"
    },
    {
      "from": "0104afee"
    },
    {
      "from": "0104b317"
    },
    {
      "from": "0104b376"
    },
    {
      "from": "0104b3b2"
    },
    {
      "from": "0104b3ee"
    },
    {
      "from": "01027223"
    },
    {
      "from": "010285c3"
    },
    {
      "from": "010294e8"
    },
    {
      "from": "00ba81dc"
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
