# Evidence 0x00bf3420

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `63789cf4c90743023dbb3432be1bae45d00b2b0523c3a2161db484e300738d7d`

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
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x4",
    "return_register": "EAX",
    "return_semantics": "pointer_like_in_EAX",
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
      }
    ],
    "stack_cleanup_bytes": 4,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x4"
  },
  "abstained_because": [
    "unparsed_lines_present: 1 line(s) matched no grammar rule"
  ],
  "cleanup": {
    "bytes": 4,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x4",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "fae466128f5ea3086c604bb731da033bba5d4a8c9c674a3dd8144a3679653716",
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
        "obs-0019"
      ],
      "claim": "the callee pops 4 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 4,
        "side": "callee"
      }
    },
    {
      "based_on": [
        "obs-0004"
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
        "obs-0006",
        "obs-0007",
        "obs-0008",
        "obs-0013"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          4
        ],
        "register": "ECX",
        "written_through": 1
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007",
        "obs-0008",
        "obs-0013",
        "obs-0019"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0019"
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
        "obs-0019"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0019"
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
      "at": "0x00bf3420",
      "count": 5,
      "first_use": 0,
      "first_write_index": 3,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00bf3421",
      "count": 4,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00bf3422",
      "count": 1,
      "first_use": 2,
      "first_write_index": 12,
      "id": "obs-0003",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV EDI,dword ptr [ESP + 0xc]",
      "reg": "ESP"
    },
    {
      "at": "0x00bf3422",
      "base": "ESP",
      "disp": 12,
      "id": "obs-0004",
      "index": 2,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EDI,dword ptr [ESP + 0xc]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00bf3422",
      "definite": true,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV EDI,dword ptr [ESP + 0xc]",
      "reg": "EDI",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00bf3426",
      "count": 3,
      "first_use": 3,
      "first_write_index": 4,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00bf3426",
      "definite": true,
      "id": "obs-0007",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00bf3428",
      "definite": true,
      "id": "obs-0008",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [ESI + 0x4]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00bf342b",
      "count": 3,
      "first_use": 5,
      "first_write_index": 18,
      "id": "obs-0009",
      "index": 5,
      "kind": "REG_READ",
      "raw": "LEA EAX,[EDI + 0x4]",
  
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
"\nint __thiscall FUN_00bf3420(int param_1,int param_2)\n\n{\n  if (param_2 + 4U < *(uint *)(param_1 + 4)) {\n    FUN_006782c0(param_2 + 4U,*(uint *)(param_1 + 4),param_2);\n  }\n  *(int *)(param_1 + 4) = *(int *)(param_1 + 4) + -4;\n  if ((int *)**(int **)(param_1 + 4) != (int *)0x0) {\n    (**(code **)(*(int *)**(int **)(param_1 + 4) + 4))();\n  }\n  return param_2;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 25,
  "instructions": [
    {
      "address": "00bf3420",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00bf3421",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00bf3422",
      "instruction": "MOV EDI,dword ptr [ESP + 0xc]"
    },
    {
      "address": "00bf3426",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00bf3428",
      "instruction": "MOV ECX,dword ptr [ESI + 0x4]"
    },
    {
      "address": "00bf342b",
      "instruction": "LEA EAX,[EDI + 0x4]"
    },
    {
      "address": "00bf342e",
      "instruction": "CMP EAX,ECX"
    },
    {
      "address": "00bf3430",
      "instruction": "JNC 0x00bf343d"
    },
    {
      "address": "00bf3432",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00bf3433",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00bf3434",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00bf3435",
      "instruction": "CALL 0x006782c0"
    },
    {
      "address": "00bf343a",
      "instruction": "ADD ESP,0xc"
    },
    {
      "address": "00bf343d",
      "instruction": "ADD dword ptr [ESI + 0x4],-0x4"
    },
    {
      "address": "00bf3441",
      "instruction": "MOV ESI,dword ptr [ESI + 0x4]"
    },
    {
      "address": "00bf3444",
      "instruction": "MOV ECX,dword ptr [ESI]"
    },
    {
      "address": "00bf3446",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00bf3448",
      "instruction": "JZ 0x00bf3451"
    },
    {
      "address": "00bf344a",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "00bf344c",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "00bf344f",
      "instruction": "CALL EDX"
    },
    {
      "address": "00bf3451",
      "instruction": "MOV EAX,EDI"
    },
    {
      "address": "00bf3453",
      "instruction": "POP EDI"
    },
    {
      "address": "00bf3454",
      "instruction": "POP ESI"
    },
    {
      "address": "00bf3455",
      "instruction": "RET 0x4"
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
  "body_end": "00bf3457",
  "body_span_bytes": 56,
  "body_start": "00bf3420",
  "callees": [
    "FUN_006782c0"
  ],
  "callers": [
    "FUN_00bb4ba0",
    "FUN_00d11730",
    "FUN_00e285a0",
    "FUN_00bb4af0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00bf3420",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "param_2",
      "storage": "Stack[0x4]:4",
      "type": "int"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int"
    }
  ],
  "locals_count": 2,
  "mode": "live",
  "name": "FUN_00bf3420",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x7f3420",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00bf3420(void)",
  "size_bytes": 56,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00bf3420",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 4,
  "xrefs": [
    {
      "from": "00bb4ce0"
    },
    {
      "from": "00bb4b60"
    },
    {
      "from": "00e28609"
    },
    {
      "from": "00d11900"
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
