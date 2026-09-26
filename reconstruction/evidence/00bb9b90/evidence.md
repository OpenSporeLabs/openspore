# Evidence 0x00bb9b90

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `7437403b80954db7a1258ebf886689194309251bcbfceafc7636cb38740d5a1c`

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
  "content_sha256": "b520e53c81aba02de995fa7dfc29d988c8b4fd1ac824f8e06ee6acc5667e818e",
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
        "obs-0008"
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
        "obs-0006",
        "obs-0007"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          116,
          120,
          124
        ],
        "register": "ECX",
        "written_through": 3
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007",
        "obs-0008"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
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
      "at": "0x00bb9b90",
      "count": 1,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "ESP"
    },
    {
      "at": "0x00bb9b90",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0002",
      "index": 0,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00bb9b90",
      "definite": true,
      "id": "obs-0003",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00bb9b94",
      "count": 4,
      "first_use": 1,
      "first_write_index": 0,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EDX,dword ptr [EAX]",
      "reg": "EAX"
    },
    {
      "at": "0x00bb9b94",
      "definite": true,
      "id": "obs-0005",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [EAX]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00bb9b96",
      "count": 3,
      "first_use": 2,
      "first_write_index": null,
      "id": "obs-0006",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV dword ptr [ECX + 0x74],EDX",
      "reg": "ECX"
    },
    {
      "at": "0x00bb9b96",
      "count": 2,
      "first_use": 2,
      "first_write_index": 1,
      "id": "obs-0007",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV dword ptr [ECX + 0x74],EDX",
      "reg": "EDX"
    },
    {
      "at": "0x00bb9ba5",
      "form": "RET 0x4",
      "id": "obs-0008",
      "imm": 4,
      "index": 7,
      "kind": "RET",
      "raw": "RET 0x4"
    }
  ],
  "parse": {
    "declared_count": 8,
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
      "sub": nul
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
"\nvoid __thiscall FUN_00bb9b90(int param_1,undefined4 *param_2)\n\n{\n  *(undefined4 *)(param_1 + 0x74) = *param_2;\n  *(undefined4 *)(param_1 + 0x78) = param_2[1];\n  *(undefined4 *)(param_1 + 0x7c) = param_2[2];\n  return;\n}\n\n"
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
      "address": "00bb9b90",
      "instruction": "MOV EAX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "00bb9b94",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00bb9b96",
      "instruction": "MOV dword ptr [ECX + 0x74],EDX"
    },
    {
      "address": "00bb9b99",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "00bb9b9c",
      "instruction": "MOV dword ptr [ECX + 0x78],EDX"
    },
    {
      "address": "00bb9b9f",
      "instruction": "MOV EAX,dword ptr [EAX + 0x8]"
    },
    {
      "address": "00bb9ba2",
      "instruction": "MOV dword ptr [ECX + 0x7c],EAX"
    },
    {
      "address": "00bb9ba5",
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
  "body_end": "00bb9ba7",
  "body_span_bytes": 24,
  "body_start": "00bb9b90",
  "callees": [],
  "callers": [
    "FUN_00ff9100",
    "FUN_00c341a0",
    "FUN_00bb2610",
    "FUN_00bad940",
    "FUN_00c8bc10",
    "FUN_00c706d0",
    "FUN_010221f0",
    "FUN_00baf630",
    "FUN_00deb930",
    "FUN_00bb2a50",
    "FUN_00c33690",
    "FUN_00bae6f0",
    "FUN_00bb28c0",
    "FUN_00c8b570"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "00bb9b90",
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
      "type": "undefined4 *"
    }
  ],
  "locals_count": 2,
  "mode": "live",
  "name": "FUN_00bb9b90",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x7b9b90",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00bb9b90(void)",
  "size_bytes": 24,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00bb9b90",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 16,
  "xrefs": [
    {
      "from": "00baf68a"
    },
    {
      "from": "00bae770"
    },
    {
      "from": "00bb293a"
    },
    {
      "from": "00bb2b19"
    },
    {
      "from": "00bb2767"
    },
    {
      "from": "00bb283c"
    },
    {
      "from": "00c33750"
    },
    {
      "from": "00c34259"
    },
    {
      "from": "00c707d0"
    },
    {
      "from": "00c8b580"
    },
    {
      "from": "010223e1"
    },
    {
      "from": "0102240a"
    },
    {
      "from": "00c8be42"
    },
    {
      "from": "00debc03"
    },
    {
      "from": "00ff9235"
    },
    {
      "from": "00bad9a0"
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
