# Evidence 0x00c37130

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `73be034ae3d66236ae5f1d769a0ee3b0fa195f0214b6b32e4615b885f17d5870`

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
    "return_semantics": "pointer_like_in_EAX",
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
  "content_sha256": "f7ab5395f69ef0ca3b45189f250a144aef44ff38ff747a00c7202abeecd59959",
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
        "obs-0004"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          1916,
          1917
        ],
        "register": "ECX",
        "written_through": 2
      }
    },
    {
      "based_on": [
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
        "obs-0005"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0005"
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
      "at": "0x00c37130",
      "count": 1,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV AL,byte ptr [ESP + 0x4]",
      "reg": "ESP"
    },
    {
      "at": "0x00c37130",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0002",
      "index": 0,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV AL,byte ptr [ESP + 0x4]",
      "resolved": true,
      "size": 1
    },
    {
      "at": "0x00c37130",
      "definite": true,
      "id": "obs-0003",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV AL,byte ptr [ESP + 0x4]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00c37134",
      "count": 3,
      "first_use": 1,
      "first_write_index": null,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_READ",
      "raw": "CMP byte ptr [ECX + 0x77c],AL",
      "reg": "ECX"
    },
    {
      "at": "0x00c37149",
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
    "distinct_offsets": 2,
    "max_offset": 1917,
    "offsets": [
      1916,
      1917
    ],
    "present": true,
    "register": "ECX",
    "shape": "R-DIRECT",
    "written_through": 2
  },
  "return": {
    "aggregate_evidence": {
      "bulk_write": false
    },
    "confidence": "INFERRED",
    "register": "EAX",
    "register_class": "pointer_like",
    "type": null,
    "void_possible": false
  },
  "schema": "openspore-abi-inference-1",
  "seh_or_cookie_frame": false,
  "sret": {
    "ambiguity": null,
    "basis": "entry slot 0 is not written through a pointer; DERIVED absence
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
"\nvoid __thiscall FUN_00c37130(int param_1,char param_2)\n\n{\n  if (*(char *)(param_1 + 0x77c) != param_2) {\n    *(char *)(param_1 + 0x77c) = param_2;\n    *(undefined1 *)(param_1 + 0x77d) = 1;\n  }\n  return;\n}\n\n"
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
      "address": "00c37130",
      "instruction": "MOV AL,byte ptr [ESP + 0x4]"
    },
    {
      "address": "00c37134",
      "instruction": "CMP byte ptr [ECX + 0x77c],AL"
    },
    {
      "address": "00c3713a",
      "instruction": "JZ 0x00c37149"
    },
    {
      "address": "00c3713c",
      "instruction": "MOV byte ptr [ECX + 0x77c],AL"
    },
    {
      "address": "00c37142",
      "instruction": "MOV byte ptr [ECX + 0x77d],0x1"
    },
    {
      "address": "00c37149",
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
  "body_end": "00c3714b",
  "body_span_bytes": 28,
  "body_start": "00c37130",
  "callees": [],
  "callers": [
    "FUN_01049040",
    "FUN_00ff62d0",
    "FUN_00fdba50",
    "FUN_00ff6200",
    "FUN_00ff60d0",
    "FUN_00ff6190",
    "FUN_00fdf5f0",
    "FUN_00fdf8e0",
    "FUN_00c5d140"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "00c37130",
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
      "storage": "Stack[0x4]:1",
      "type": "char"
    }
  ],
  "locals_count": 2,
  "mode": "live",
  "name": "FUN_00c37130",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x837130",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00c37130(void)",
  "size_bytes": 28,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00c37130",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 10,
  "xrefs": [
    {
      "from": "00ff6340"
    },
    {
      "from": "00fdf9c8"
    },
    {
      "from": "00fdba73"
    },
    {
      "from": "00fdbbac"
    },
    {
      "from": "00fdf787"
    },
    {
      "from": "00ff61d7"
    },
    {
      "from": "00ff6247"
    },
    {
      "from": "010497f5"
    },
    {
      "from": "00c5d589"
    },
    {
      "from": "00ff6167"
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
