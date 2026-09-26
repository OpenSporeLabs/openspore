# Evidence 0x00bd9c00

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `70c30755011fb01ad9ff94438118ef54d318e75406a4de78e9788333555d6901`

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
    "return_semantics": "integral_in_EAX",
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
    "flow_not_modelled: the linear ESP walk ends at +4, so the listing is not one path"
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
  "content_sha256": "9e5986a02f695c8634ecb8be120e1c114b39611cca4ee1c50910089019417a0b",
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
        "obs-0008",
        "obs-0009"
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
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 1,
        "total_bytes": 4
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
          804
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0002",
        "obs-0008",
        "obs-0009"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0008",
        "obs-0009"
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
        "obs-0008",
        "obs-0009"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0008",
        "obs-0009"
      ],
      "claim": "the last value written to EAX classifies as integral",
      "confidence": "INFERRED",
      "id": "RT2",
      "value": {
        "register_class": "integral"
      }
    }
  ],
  "observations": [
    {
      "at": "0x00bd9c00",
      "count": 1,
      "first_use": 0,
      "first_write_index": 0,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV ECX,dword ptr [ECX + 0x324]",
      "reg": "ECX"
    },
    {
      "at": "0x00bd9c00",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [ECX + 0x324]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00bd9c0a",
      "count": 1,
      "first_use": 3,
      "first_write_index": null,
      "id": "obs-0003",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "ESP"
    },
    {
      "at": "0x00bd9c0a",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0004",
      "index": 3,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00bd9c0a",
      "definite": true,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00bd9c0e",
      "count": 1,
      "first_use": 4,
      "first_write_index": 3,
      "id": "obs-0006",
      "index": 4,
      "kind": "REG_READ",
      "raw": "PUSH EAX",
      "reg": "EAX"
    },
    {
      "at": "0x00bd9c0f",
      "id": "obs-0007",
      "index": 5,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00bec0f0",
      "target": "0x00bec0f0"
    },
    {
      "at": "0x00bd9c1a",
      "form": "RET 0x4",
      "id": "obs-0008",
      "imm": 4,
      "index": 9,
      "kind": "RET",
      "raw": "RET 0x4"
    },
    {
      "at": "0x00bd9c1f",
      "form": "RET 0x4",
      "id": "obs-0009",
      "imm": 4,
      "index": 11,
      "kind": "RET",
      "raw": "RET 0x4"
    }
  ],
  "parse": {
    "declared_count": 12,
    "degraded": false,
    "esp_unresolved": false,
    "flow_complete": false,
    
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
"\nundefined4 __thiscall FUN_00bd9c00(int param_1,undefined4 param_2)\n\n{\n  char cVar1;\n  \n  if (*(int *)(param_1 + 0x324) != 0) {\n    cVar1 = FUN_00bec0f0(param_2);\n    if (cVar1 != '\\0') {\n      return 1;\n    }\n  }\n  return 0;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 12,
  "instructions": [
    {
      "address": "00bd9c00",
      "instruction": "MOV ECX,dword ptr [ECX + 0x324]"
    },
    {
      "address": "00bd9c06",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00bd9c08",
      "instruction": "JZ 0x00bd9c1d"
    },
    {
      "address": "00bd9c0a",
      "instruction": "MOV EAX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "00bd9c0e",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00bd9c0f",
      "instruction": "CALL 0x00bec0f0"
    },
    {
      "address": "00bd9c14",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00bd9c16",
      "instruction": "JZ 0x00bd9c1d"
    },
    {
      "address": "00bd9c18",
      "instruction": "MOV AL,0x1"
    },
    {
      "address": "00bd9c1a",
      "instruction": "RET 0x4"
    },
    {
      "address": "00bd9c1d",
      "instruction": "XOR AL,AL"
    },
    {
      "address": "00bd9c1f",
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
  "body_end": "00bd9c21",
  "body_span_bytes": 34,
  "body_start": "00bd9c00",
  "callees": [
    "FUN_00bec0f0"
  ],
  "callers": [
    "FUN_01056d30",
    "FUN_00b262c0",
    "FUN_010593e0"
  ],
  "classification": "wrapper",
  "dispatch": null,
  "entry_point": "00bd9c00",
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
      "name": "cVar1",
      "storage": "register:00000000:1",
      "type": "char"
    },
    {
      "name": "param_2",
      "storage": "Stack[0x4]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 3,
  "mode": "live",
  "name": "FUN_00bd9c00",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x7d9c00",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00bd9c00(void)",
  "size_bytes": 34,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00bd9c00",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 4,
  "xrefs": [
    {
      "from": "00b26309"
    },
    {
      "from": "01056ea2"
    },
    {
      "from": "01059757"
    },
    {
      "from": "0105980b"
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
