# Evidence 0x00bb9b00

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `07828b19533e84ba8151fa0342f8a7c227878a9efc6505ec4c84e27fd0953578`

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
      "entry_ESP+0x4",
      "entry_ESP+0x8"
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
      },
      {
        "entry_offset": "entry_ESP+0x8",
        "observed": true,
        "ordinal": 2,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x8",
    "return_register": "EAX",
    "return_semantics": "pointer_like_in_EAX",
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
      },
      {
        "entry_offset": "entry_ESP+0x8",
        "observed": true,
        "ordinal": 2,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      }
    ],
    "stack_cleanup_bytes": 8,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x8"
  },
  "abstained_because": [],
  "cleanup": {
    "bytes": 8,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x8",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "645fca4e416ce0a43911c6ce3ef6e7906bd75662941660797dec17abbd41afcb",
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
        "obs-0007",
        "obs-0011"
      ],
      "claim": "the callee pops 8 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 8,
        "side": "callee"
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0008"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "INFERRED",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 2,
        "total_bytes": 8
      }
    },
    {
      "based_on": [
        "obs-0005",
        "obs-0006",
        "obs-0010"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          92
        ],
        "register": "ECX",
        "written_through": 2
      }
    },
    {
      "based_on": [
        "obs-0005",
        "obs-0006",
        "obs-0007",
        "obs-0010",
        "obs-0011"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0007",
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
        "obs-0007",
        "obs-0011"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0007",
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
      "at": "0x00bb9b00",
      "count": 3,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "CMP byte ptr [ESP + 0x8],0x0",
      "reg": "ESP"
    },
    {
      "at": "0x00bb9b00",
      "base": "ESP",
      "disp": 8,
      "id": "obs-0002",
      "index": 0,
      "key": 8,
      "kind": "STACK_SLOT_READ",
      "raw": "CMP byte ptr [ESP + 0x8],0x0",
      "resolved": true,
      "size": 1
    },
    {
      "at": "0x00bb9b07",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0003",
      "index": 2,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00bb9b07",
      "definite": true,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00bb9b0b",
      "count": 2,
      "first_use": 3,
      "first_write_index": null,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "OR dword ptr [ECX + 0x5c],EAX",
      "reg": "ECX"
    },
    {
      "at": "0x00bb9b0b",
      "count": 1,
      "first_use": 3,
      "first_write_index": 2,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_READ",
      "raw": "OR dword ptr [ECX + 0x5c],EAX",
      "reg": "EAX"
    },
    {
      "at": "0x00bb9b0e",
      "form": "RET 0x8",
      "id": "obs-0007",
      "imm": 8,
      "index": 4,
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
"\nvoid __thiscall FUN_00bb9b00(int param_1,uint param_2,char param_3)\n\n{\n  if (param_3 != '\\0') {\n    *(uint *)(param_1 + 0x5c) = *(uint *)(param_1 + 0x5c) | param_2;\n    return;\n  }\n  *(uint *)(param_1 + 0x5c) = *(uint *)(param_1 + 0x5c) & ~param_2;\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 9,
  "instructions": [
    {
      "address": "00bb9b00",
      "instruction": "CMP byte ptr [ESP + 0x8],0x0"
    },
    {
      "address": "00bb9b05",
      "instruction": "JZ 0x00bb9b11"
    },
    {
      "address": "00bb9b07",
      "instruction": "MOV EAX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "00bb9b0b",
      "instruction": "OR dword ptr [ECX + 0x5c],EAX"
    },
    {
      "address": "00bb9b0e",
      "instruction": "RET 0x8"
    },
    {
      "address": "00bb9b11",
      "instruction": "MOV EDX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "00bb9b15",
      "instruction": "NOT EDX"
    },
    {
      "address": "00bb9b17",
      "instruction": "AND dword ptr [ECX + 0x5c],EDX"
    },
    {
      "address": "00bb9b1a",
      "instruction": "RET 0x8"
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
  "body_end": "00bb9b1c",
  "body_span_bytes": 29,
  "body_start": "00bb9b00",
  "callees": [],
  "callers": [
    "FUN_00ba6cf0",
    "FUN_00bb6040",
    "FUN_00bb5d80",
    "FUN_00bb80f0",
    "FUN_00bb5640",
    "FUN_00b294c0",
    "FUN_00ba7dc0",
    "FUN_00c5c470",
    "FUN_00fe9580",
    "FUN_00baac30",
    "FUN_00c5f5f0",
    "FUN_0100aec0",
    "FUN_00c7a160",
    "FUN_00ba8830",
    "FUN_00bb4af0",
    "FUN_00c5b660",
    "FUN_00c5f770",
    "FUN_00bad940",
    "FUN_00baf630",
    "FUN_00bb21b0",
    "FUN_00c8c2a0",
    "FUN_0100a160",
    "FUN_00bb4f30",
    "FUN_00bb4ba0"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "00bb9b00",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "param_3",
      "storage": "Stack[0x8]:1",
      "type": "char"
    },
    {
      "name": "param_2",
      "storage": "Stack[0x4]:4",
      "type": "uint"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int"
    }
  ],
  "locals_count": 3,
  "mode": "live",
  "name": "FUN_00bb9b00",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x7b9b00",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00bb9b00(void)",
  "size_bytes": 29,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00bb9b00",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 44,
  "xrefs": [
    {
      "from": "00b296de"
    },
    {
      "from": "00baf677"
    },
    {
      "from": "00baf699"
    },
    {
      "from": "00bb4c81"
    },
    {
      "from": "00bb6202"
    },
    {
      "from": "00ba8872"
    },
    {
      "from": "00bb2323"
    },
    {
      "from": "00ba6d5c"
    },
    {
      "from": "00baacb5"
    },
    {
      "from": "00baacce"
    },
    {
      "from": "00baacee"
    },
    {
      "from": "00bb86b1"
    },
    {
      "from": "00bb88ab"
    },
    {
      "from": "00bb4b7c"
    },
    {
      "from": "00fe973e"
    },
    {
      "from": "00fe9c8e"
    },
    {
      "from": "00c8c2c3"
    },
    {
      "from": "00bb5690"
    },
    {
      "from": "00bb569f"
    },
    {
      "from": "00bb56aa"
    },
    {
      "from": "00bb56b5"
    },
    {
      "from": "00bb56c3"
    },
    {
      "from": "00ba7fb0"
    },
    {
      "from": "00c7a1c2"
    },
    {
      "from": "00c7a1e1"
    },
    {
      "from": "00bb5eb8"
    },
    {
      "from": "00c5b67c"
    },
    {
      "from": "00c5c6f9"
    },
    {
      "from": "00c5f624"
    },
    {
      "from": "00c5fa12"
    },
    {
      "from": "00c5fb56"
    },
    {
      "from": "00c5fb6b"
    },
    {
      "from": "0100a5c9"
    },
    {
      "from": "0100b031"
    },
    {
      "from": "00b296d3"
    },
    {
      "from": "00bad9c9"
    },
    {
      "from": "00b29c25"
    },
    {
      "from": "00b29fca"
    },
    {
      "from": "00b29c1a"
    },
    {
      "from": "00b29fbf"
    },
    {
      "from": "00bb4fb0"
    },
    {
      "from": "00bb5086"
    },
    {
      "from": "00bb5149"
    },
    {
      "from": "00bb5562"
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
