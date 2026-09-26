# Evidence 0x00451e50

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `01f834d6cb26e50524623012fe8526b567eda3317cfb89fa51a0b9c3678354ed`

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
        "ebp_offset": "EBP+0x8",
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
      "EBP"
    ],
    "stack_arguments": [
      {
        "ebp_offset": "EBP+0x8",
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
  "content_sha256": "b48530c4b715445680681bbea049b0c139584d9830b3350b73a8fea75cf6fc6d",
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
        "obs-0017"
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
        "obs-0011",
        "obs-0012",
        "obs-0013",
        "obs-0017"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          396
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007",
        "obs-0011",
        "obs-0012",
        "obs-0013",
        "obs-0017",
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
      "at": "0x00451e50",
      "count": 8,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH EBP",
      "reg": "EBP"
    },
    {
      "and_esp": null,
      "at": "0x00451e50",
      "ebp_is_general_register": true,
      "fp": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": true,
      "mov_ebp_esp_at": 1,
      "push_ebp": true,
      "push_ebp_at": 0,
      "raw": "PUSH EBP",
      "sub": 8
    },
    {
      "at": "0x00451e51",
      "count": 1,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EBP,ESP",
      "reg": "ESP"
    },
    {
      "at": "0x00451e51",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EBP,ESP",
      "reg": "EBP",
      "write_kind": "reg"
    },
    {
      "at": "0x00451e53",
      "definite": true,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x8",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00451e56",
      "count": 3,
      "first_use": 3,
      "first_write_index": 7,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV dword ptr [EBP + -0x8],ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00451e56",
      "base": "EBP",
      "disp": -8,
      "id": "obs-0007",
      "index": 3,
      "key": null,
      "kind": "STACK_SLOT_WRITE",
      "raw": "MOV dword ptr [EBP + -0x8],ECX",
      "reason": "local",
      "resolved": false,
      "size": 4,
      "via": "direct"
    },
    {
      "at": "0x00451e59",
      "base": "EBP",
      "disp": -8,
      "id": "obs-0008",
      "index": 4,
      "key": null,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [EBP + -0x8]
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
"\nvoid __thiscall FUN_00451e50(int param_1,undefined4 param_2)\n\n{\n  if (*(int *)(param_1 + 0x18c) != 0) {\n    *(undefined4 *)(*(int *)(param_1 + 0x18c) + 0x38) = param_2;\n  }\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 17,
  "instructions": [
    {
      "address": "00451e50",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00451e51",
      "instruction": "MOV EBP,ESP"
    },
    {
      "address": "00451e53",
      "instruction": "SUB ESP,0x8"
    },
    {
      "address": "00451e56",
      "instruction": "MOV dword ptr [EBP + -0x8],ECX"
    },
    {
      "address": "00451e59",
      "instruction": "MOV EAX,dword ptr [EBP + -0x8]"
    },
    {
      "address": "00451e5c",
      "instruction": "CMP dword ptr [EAX + 0x18c],0x0"
    },
    {
      "address": "00451e63",
      "instruction": "JZ 0x00451e7d"
    },
    {
      "address": "00451e65",
      "instruction": "MOV ECX,dword ptr [EBP + -0x8]"
    },
    {
      "address": "00451e68",
      "instruction": "MOV EDX,dword ptr [ECX + 0x18c]"
    },
    {
      "address": "00451e6e",
      "instruction": "ADD EDX,0x1c"
    },
    {
      "address": "00451e71",
      "instruction": "MOV dword ptr [EBP + -0x4],EDX"
    },
    {
      "address": "00451e74",
      "instruction": "MOV EAX,dword ptr [EBP + -0x4]"
    },
    {
      "address": "00451e77",
      "instruction": "MOV ECX,dword ptr [EBP + 0x8]"
    },
    {
      "address": "00451e7a",
      "instruction": "MOV dword ptr [EAX + 0x1c],ECX"
    },
    {
      "address": "00451e7d",
      "instruction": "MOV ESP,EBP"
    },
    {
      "address": "00451e7f",
      "instruction": "POP EBP"
    },
    {
      "address": "00451e80",
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
  "body_end": "00451e82",
  "body_span_bytes": 51,
  "body_start": "00451e50",
  "callees": [],
  "callers": [
    "FUN_004ad4e0",
    "FUN_004ad470",
    "FUN_004a6690",
    "FUN_004956b0",
    "FUN_0048d010"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "00451e50",
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
    },
    {
      "name": "param_2",
      "storage": "Stack[0x4]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 2,
  "mode": "live",
  "name": "FUN_00451e50",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x51e50",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00451e50(void)",
  "size_bytes": 51,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00451e50",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 12,
  "xrefs": [
    {
      "from": "00495d7e"
    },
    {
      "from": "004ad4cb"
    },
    {
      "from": "004ad53e"
    },
    {
      "from": "0048d1e0"
    },
    {
      "from": "004a675b"
    },
    {
      "from": "004a67ba"
    },
    {
      "from": "004a683c"
    },
    {
      "from": "004a684d"
    },
    {
      "from": "004a6893"
    },
    {
      "from": "004a6947"
    },
    {
      "from": "004a69fd"
    },
    {
      "from": "004a6c15"
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
