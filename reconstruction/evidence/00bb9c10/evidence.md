# Evidence 0x00bb9c10

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `836a61a161c7bc7d035eeafd07103c8ae8d9e9a059c50d5bd9e86fe2d2aa7835`

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
          1
        ],
        "written": false
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x4",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX;void_possible",
    "stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1
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
  "content_sha256": "4546ed055a4c81c73624e21f212e6def263f4eeef0888f015a4f0fd9690dbe9b",
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
        "obs-0004",
        "obs-0005"
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
        "obs-0003"
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
        "obs-0003",
        "obs-0004",
        "obs-0005"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0004",
        "obs-0005"
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
        "obs-0004",
        "obs-0005"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0004",
        "obs-0005"
      ],
      "claim": "the last value written to EAX classifies as aggregate_unknown",
      "confidence": "INFERRED",
      "id": "RT2",
      "value": {
        "register_class": "aggregate_unknown"
      }
    },
    {
      "based_on": [
        "obs-0004",
        "obs-0005"
      ],
      "claim": "EAX is never written and no call can clobber it, so a void return is possible; this is a flag, never a type",
      "confidence": "APPROXIMATION",
      "id": "RT3",
      "value": {
        "void_possible": true
      }
    }
  ],
  "observations": [
    {
      "at": "0x00bb9c10",
      "count": 1,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "CMP byte ptr [ESP + 0x4],0x0",
      "reg": "ESP"
    },
    {
      "at": "0x00bb9c10",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0002",
      "index": 0,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "CMP byte ptr [ESP + 0x4],0x0",
      "resolved": true,
      "size": 1
    },
    {
      "at": "0x00bb9c17",
      "count": 2,
      "first_use": 2,
      "first_write_index": null,
      "id": "obs-0003",
      "index": 2,
      "kind": "REG_READ",
      "raw": "OR dword ptr [ECX + 0x5c],0x8",
      "reg": "ECX"
    },
    {
      "at": "0x00bb9c1b",
      "form": "RET 0x4",
      "id": "obs-0004",
      "imm": 4,
      "index": 3,
      "kind": "RET",
      "raw": "RET 0x4"
    },
    {
      "at": "0x00bb9c22",
      "form": "RET 0x4",
      "id": "obs-0005",
      "imm": 4,
      "index": 5,
      "kind": "RET",
      "raw": "RET 0x4"
    }
  ],
  "parse": {
    "declared_count": 6,
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
    "distinct_offsets": 1,
    "max_offset": 92,
    "offsets": [
      92
    ],
    "present": true,
    "register": "ECX",
    "shape": "R-DIRECT",
    "written_through": 2
  },
  "return": {
    "aggregate_evidence": {
      "bu
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
"\nvoid __thiscall FUN_00bb9c10(int param_1,char param_2)\n\n{\n  if (param_2 != '\\0') {\n    *(uint *)(param_1 + 0x5c) = *(uint *)(param_1 + 0x5c) | 8;\n    return;\n  }\n  *(uint *)(param_1 + 0x5c) = *(uint *)(param_1 + 0x5c) & 0xfffffff7;\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 6,
  "instructions": [
    {
      "address": "00bb9c10",
      "instruction": "CMP byte ptr [ESP + 0x4],0x0"
    },
    {
      "address": "00bb9c15",
      "instruction": "JZ 0x00bb9c1e"
    },
    {
      "address": "00bb9c17",
      "instruction": "OR dword ptr [ECX + 0x5c],0x8"
    },
    {
      "address": "00bb9c1b",
      "instruction": "RET 0x4"
    },
    {
      "address": "00bb9c1e",
      "instruction": "AND dword ptr [ECX + 0x5c],0xfffffff7"
    },
    {
      "address": "00bb9c22",
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
  "body_end": "00bb9c24",
  "body_span_bytes": 21,
  "body_start": "00bb9c10",
  "callees": [],
  "callers": [
    "FUN_00bb28c0",
    "FUN_00c46590",
    "FUN_00bb21b0",
    "FUN_00bb2610",
    "FUN_00c47a10",
    "FUN_00bae6f0",
    "FUN_00c34ee0",
    "FUN_00bb2a50"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "00bb9c10",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "param_2",
      "storage": "Stack[0x4]:1",
      "type": "char"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int"
    }
  ],
  "locals_count": 2,
  "mode": "live",
  "name": "FUN_00bb9c10",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x7b9c10",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00bb9c10(void)",
  "size_bytes": 21,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00bb9c10",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 9,
  "xrefs": [
    {
      "from": "00bb2315"
    },
    {
      "from": "00bae817"
    },
    {
      "from": "00bb29a6"
    },
    {
      "from": "00bb2bcd"
    },
    {
      "from": "00bb2770"
    },
    {
      "from": "00bb2845"
    },
    {
      "from": "00c35042"
    },
    {
      "from": "00c46650"
    },
    {
      "from": "00c47adf"
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
