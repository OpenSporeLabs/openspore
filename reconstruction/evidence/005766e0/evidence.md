# Evidence 0x005766e0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `22ee9977ff270daee6138265af8582d01af558ae77bae0af48856e14188b7084`

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
    "return_semantics": "unclassified_in_EAX",
    "saved_registers": [
      "EBX",
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
  "content_sha256": "0e16b47d3906cbefe29e10cf513e428607f5aa8f32ce5dbe88c546f259e60e66",
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
    "indirect_calls": 2,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0020"
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
        "obs-0009",
        "obs-0010",
        "obs-0014"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          0
        ],
        "register": "ECX",
        "written_through": 1
      }
    },
    {
      "based_on": [
        "obs-0009",
        "obs-0010",
        "obs-0014",
        "obs-0020"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0020"
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
        "obs-0020"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0020"
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
      "at": "0x005766e0",
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
      "at": "0x005766e0",
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
      "at": "0x005766e0",
      "definite": true,
      "id": "obs-0003",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x005766e4",
      "count": 3,
      "first_use": 1,
      "first_write_index": 6,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x005766e5",
      "count": 4,
      "first_use": 2,
      "first_write_index": 3,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x005766e6",
      "count": 3,
      "first_use": 3,
      "first_write_index": 0,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV ESI,dword ptr [EAX]",
      "reg": "EAX"
    },
    {
      "at": "0x005766e6",
      "definite": true,
      "id": "obs-0007",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,dword ptr [EAX]",
      "reg": "ESI",
      "write_kind": "mem_load"
    },
    {
      "at": "0x005766e8",
      "count": 4,
      "first_use": 4,
      "first_write_index": 5,
      "id": "obs-0008",
      "index": 4,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x005766e9",
      "count": 1,
      "first_use": 5,
      "first_write_index": 13,
      "id": "obs-0009",
      "index": 5,
      "kind": "REG_READ",
      "raw": "MOV EDI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x005766e9",
      "definit
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
"\nint * __thiscall FUN_005766e0(int *param_1,int *param_2)\n\n{\n  int *piVar1;\n  \n  param_2 = (int *)*param_2;\n  piVar1 = (int *)*param_1;\n  if (param_2 != piVar1) {\n    if (param_2 != (int *)0x0) {\n      (**(code **)(*param_2 + 4))();\n    }\n    *param_1 = (int)param_2;\n    if (piVar1 != (int *)0x0) {\n      (**(code **)(*piVar1 + 8))();\n    }\n  }\n  return param_1;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 27,
  "instructions": [
    {
      "address": "005766e0",
      "instruction": "MOV EAX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "005766e4",
      "instruction": "PUSH EBX"
    },
    {
      "address": "005766e5",
      "instruction": "PUSH ESI"
    },
    {
      "address": "005766e6",
      "instruction": "MOV ESI,dword ptr [EAX]"
    },
    {
      "address": "005766e8",
      "instruction": "PUSH EDI"
    },
    {
      "address": "005766e9",
      "instruction": "MOV EDI,ECX"
    },
    {
      "address": "005766eb",
      "instruction": "MOV EBX,dword ptr [EDI]"
    },
    {
      "address": "005766ed",
      "instruction": "CMP ESI,EBX"
    },
    {
      "address": "005766ef",
      "instruction": "JZ 0x0057670d"
    },
    {
      "address": "005766f1",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "005766f3",
      "instruction": "JZ 0x005766fe"
    },
    {
      "address": "005766f5",
      "instruction": "MOV EDX,dword ptr [ESI]"
    },
    {
      "address": "005766f7",
      "instruction": "MOV EAX,dword ptr [EDX + 0x4]"
    },
    {
      "address": "005766fa",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "005766fc",
      "instruction": "CALL EAX"
    },
    {
      "address": "005766fe",
      "instruction": "MOV dword ptr [EDI],ESI"
    },
    {
      "address": "00576700",
      "instruction": "TEST EBX,EBX"
    },
    {
      "address": "00576702",
      "instruction": "JZ 0x0057670d"
    },
    {
      "address": "00576704",
      "instruction": "MOV EDX,dword ptr [EBX]"
    },
    {
      "address": "00576706",
      "instruction": "MOV EAX,dword ptr [EDX + 0x8]"
    },
    {
      "address": "00576709",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "0057670b",
      "instruction": "CALL EAX"
    },
    {
      "address": "0057670d",
      "instruction": "MOV EAX,EDI"
    },
    {
      "address": "0057670f",
      "instruction": "POP EDI"
    },
    {
      "address": "00576710",
      "instruction": "POP ESI"
    },
    {
      "address": "00576711",
      "instruction": "POP EBX"
    },
    {
      "address": "00576712",
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
  "body_end": "00576714",
  "body_span_bytes": 53,
  "body_start": "005766e0",
  "callees": [],
  "callers": [
    "FUN_0069e090",
    "Editors::cEditor::OnMouseDown",
    "FUN_007bf720",
    "FUN_005c7ff0",
    "FUN_00661d10",
    "FUN_00c3a930",
    "FUN_0057c0e0",
    "FUN_0064acd0",
    "FUN_0069e260"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "005766e0",
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
      "name": "param_2",
      "storage": "Stack[0x4]:4",
      "type": "int *"
    },
    {
      "name": "piVar1",
      "storage": "unique:00017200:4",
      "type": "int *"
    }
  ],
  "locals_count": 3,
  "mode": "live",
  "name": "FUN_005766e0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x1766e0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_005766e0(void)",
  "size_bytes": 53,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x005766e0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 13,
  "xrefs": [
    {
      "from": "0069e308"
    },
    {
      "from": "005c8342"
    },
    {
      "from": "0064af7a"
    },
    {
      "from": "0064b39a"
    },
    {
      "from": "00661f59"
    },
    {
      "from": "00661fd5"
    },
    {
      "from": "0069e131"
    },
    {
      "from": "00c3a9aa"
    },
    {
      "from": "0057c160"
    },
    {
      "from": "00588ea8"
    },
    {
      "from": "007bf944"
    },
    {
      "from": "00c3a8a4"
    },
    {
      "from": "00c3a8cc"
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
