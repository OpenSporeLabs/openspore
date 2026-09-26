# Evidence 0x00bbaa60

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `09ccbfec1fe747d192a3c05f6f2fad8f9fb83ebe04a8719107f0364e0d2c4485`

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
  "abstained_because": [],
  "cleanup": {
    "bytes": 4,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x4",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "26d99e91e03186fc7aeb892c84a2ec77afab94e49b27c61f6fcd7fd5223662ba",
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
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0011"
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
        "obs-0007"
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
        "obs-0002",
        "obs-0003",
        "obs-0006",
        "obs-0007",
        "obs-0008",
        "obs-0009"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          132
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0006",
        "obs-0007",
        "obs-0008",
        "obs-0009",
        "obs-0011"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0011"
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
        "obs-0011"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0011"
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
      "at": "0x00bbaa60",
      "count": 2,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00bbaa61",
      "count": 2,
      "first_use": 1,
      "first_write_index": 4,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00bbaa61",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00bbaa63",
      "id": "obs-0004",
      "index": 2,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00bba640",
      "target": "0x00bba640"
    },
    {
      "at": "0x00bbaa68",
      "definite": true,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESI + 0x84]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00bbaa6e",
      "count": 1,
      "first_use": 4,
      "first_write_index": null,
      "id": "obs-0006",
      "index": 4,
      "kind": "REG_READ",
      "raw": "MOV ECX,dword ptr [ESP + 0x8]",
      "reg": "ESP"
    },
    {
      "at": "0x00bbaa6e",
      "base": "ESP",
      "disp": 8,
      "id": "obs-0007",
      "index": 4,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV ECX,dword ptr [ESP + 0x8]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00bbaa6e",
      "definite": true,
      "id": "obs-0008",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [ESP + 0x8]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00bbaa72",
      "count": 1,
      "first_use": 5,
      "first_write_index": 3,
      "id": "obs-0009",
      "index": 5,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [EAX + ECX*0x4]",
      "reg": "EAX"
    },
    {
   
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
"\nundefined4 __thiscall FUN_00bbaa60(int param_1,int param_2)\n\n{\n  FUN_00bba640();\n  return *(undefined4 *)(*(int *)(param_1 + 0x84) + param_2 * 4);\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 8,
  "instructions": [
    {
      "address": "00bbaa60",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00bbaa61",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00bbaa63",
      "instruction": "CALL 0x00bba640"
    },
    {
      "address": "00bbaa68",
      "instruction": "MOV EAX,dword ptr [ESI + 0x84]"
    },
    {
      "address": "00bbaa6e",
      "instruction": "MOV ECX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "00bbaa72",
      "instruction": "MOV EAX,dword ptr [EAX + ECX*0x4]"
    },
    {
      "address": "00bbaa75",
      "instruction": "POP ESI"
    },
    {
      "address": "00bbaa76",
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
  "body_end": "00bbaa78",
  "body_span_bytes": 25,
  "body_start": "00bbaa60",
  "callees": [
    "FUN_00bba640"
  ],
  "callers": [
    "FUN_00bb5b70",
    "FUN_01004e50",
    "FUN_00bb6700",
    "FUN_00deb930",
    "FUN_00bafae0",
    "FUN_00bb23e0",
    "FUN_00ba6dc0",
    "FUN_00bb59b0",
    "FUN_00df6db0",
    "FUN_00bb8b20",
    "FUN_00bb2330",
    "FUN_00bad940",
    "FUN_0102d1b0",
    "FUN_00bb7620",
    "FUN_00bb7510",
    "FUN_00df6740",
    "FUN_00fdeac0",
    "FUN_00de6f20",
    "FUN_00bb57b0",
    "FUN_00ded7d0"
  ],
  "classification": "wrapper",
  "dispatch": null,
  "entry_point": "00bbaa60",
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
  "name": "FUN_00bbaa60",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x7baa60",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00bbaa60(void)",
  "size_bytes": 25,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00bbaa60",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 25,
  "xrefs": [
    {
      "from": "00bb23ba"
    },
    {
      "from": "00bb2466"
    },
    {
      "from": "00bb9808"
    },
    {
      "from": "00ba6df6"
    },
    {
      "from": "00bb5a4d"
    },
    {
      "from": "00bb57d9"
    },
    {
      "from": "00bb5833"
    },
    {
      "from": "00bb58b0"
    },
    {
      "from": "00bafbeb"
    },
    {
      "from": "00bb0b0e"
    },
    {
      "from": "0102d315"
    },
    {
      "from": "00bb767d"
    },
    {
      "from": "00bb7770"
    },
    {
      "from": "00bb5ba4"
    },
    {
      "from": "00bb671b"
    },
    {
      "from": "00bb753f"
    },
    {
      "from": "00de6f55"
    },
    {
      "from": "00debd1b"
    },
    {
      "from": "00debdb4"
    },
    {
      "from": "00df6775"
    },
    {
      "from": "00fded53"
    },
    {
      "from": "01004ebf"
    },
    {
      "from": "00df73b0"
    },
    {
      "from": "00bad9d2"
    },
    {
      "from": "00ded804"
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
