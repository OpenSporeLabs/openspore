# Evidence 0x00bf0f40

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `1971bee2fc12caca89a4d50c55e2c97958f52fbbed8b7b0d0ba389cb69696ad2`

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
    "return_semantics": "integral_in_EAX",
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
  "content_sha256": "7f3c967f2f3d8eed6912a9c1e5bf5308265ad824e8cb71ad81f5d8fcf2172da1",
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
        "obs-0005",
        "obs-0006",
        "obs-0007",
        "obs-0009"
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
        "obs-0002",
        "obs-0003"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          156,
          160
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0002",
        "obs-0003",
        "obs-0005",
        "obs-0006",
        "obs-0007",
        "obs-0009"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0005",
        "obs-0006",
        "obs-0007",
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
        "obs-0005",
        "obs-0006",
        "obs-0007",
        "obs-0009"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0005",
        "obs-0006",
        "obs-0007",
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
      "at": "0x00bf0f40",
      "count": 4,
      "first_use": 0,
      "first_write_index": 4,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ECX + 0xa0]",
      "reg": "ECX"
    },
    {
      "at": "0x00bf0f40",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ECX + 0xa0]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00bf0f53",
      "definite": true,
      "id": "obs-0003",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [ECX + 0x9c]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00bf0f5f",
      "id": "obs-0004",
      "index": 8,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00bd81d0",
      "target": "0x00bd81d0"
    },
    {
      "at": "0x00bf0f76",
      "form": "RET",
      "id": "obs-0005",
      "imm": null,
      "index": 16,
      "kind": "RET",
      "raw": "RET"
    },
    {
      "at": "0x00bf0f7c",
      "form": "RET",
      "id": "obs-0006",
      "imm": null,
      "index": 18,
      "kind": "RET",
      "raw": "RET"
    },
    {
      "at": "0x00bf0f82",
      "form": "RET",
      "id": "obs-0007",
      "imm": null,
      "index": 20,
      "kind": "RET",
      "raw": "RET"
    },
    {
      "at": "0x00bf0f83",
      "count": 1,
      "first_use": 21,
      "first_write_index": 0,
      "id": "obs-0008",
      "index": 21,
      "kind": "REG_READ",
      "raw": "XOR EAX,EAX",
      "reg": "EAX"
    },
    {
      "at": "0x00bf0f85",
      "form": "RET",
      "id": "obs-0009",
      "imm": null,
      "index": 22,
      "kind": "RET",
      "raw": "RET"
    }
  ],
  "parse": {
    "declared_count": 23,
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
    "max_offset": 160,
    "offsets": [
      156,
      160
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
    "register_class": "integral",
    "type": 
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
"\nundefined4 __fastcall FUN_00bf0f40(int param_1)\n\n{\n  int iVar1;\n  \n  if (((*(int *)(param_1 + 0xa0) - *(int *)(param_1 + 0x9c) & 0xfffffffcU) != 0) &&\n     (**(int **)(param_1 + 0x9c) != 0)) {\n    iVar1 = FUN_00bd81d0();\n    if (iVar1 != 0) {\n      if (iVar1 == 1) {\n        return 2;\n      }\n      if (iVar1 != 2) {\n        return 0xffffffff;\n      }\n      return 1;\n    }\n  }\n  return 0;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 23,
  "instructions": [
    {
      "address": "00bf0f40",
      "instruction": "MOV EAX,dword ptr [ECX + 0xa0]"
    },
    {
      "address": "00bf0f46",
      "instruction": "SUB EAX,dword ptr [ECX + 0x9c]"
    },
    {
      "address": "00bf0f4c",
      "instruction": "TEST EAX,0xfffffffc"
    },
    {
      "address": "00bf0f51",
      "instruction": "JZ 0x00bf0f83"
    },
    {
      "address": "00bf0f53",
      "instruction": "MOV ECX,dword ptr [ECX + 0x9c]"
    },
    {
      "address": "00bf0f59",
      "instruction": "MOV ECX,dword ptr [ECX]"
    },
    {
      "address": "00bf0f5b",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00bf0f5d",
      "instruction": "JZ 0x00bf0f83"
    },
    {
      "address": "00bf0f5f",
      "instruction": "CALL 0x00bd81d0"
    },
    {
      "address": "00bf0f64",
      "instruction": "SUB EAX,0x0"
    },
    {
      "address": "00bf0f67",
      "instruction": "JZ 0x00bf0f83"
    },
    {
      "address": "00bf0f69",
      "instruction": "SUB EAX,0x1"
    },
    {
      "address": "00bf0f6c",
      "instruction": "JZ 0x00bf0f7d"
    },
    {
      "address": "00bf0f6e",
      "instruction": "SUB EAX,0x1"
    },
    {
      "address": "00bf0f71",
      "instruction": "JZ 0x00bf0f77"
    },
    {
      "address": "00bf0f73",
      "instruction": "OR EAX,0xffffffff"
    },
    {
      "address": "00bf0f76",
      "instruction": "RET"
    },
    {
      "address": "00bf0f77",
      "instruction": "MOV EAX,0x1"
    },
    {
      "address": "00bf0f7c",
      "instruction": "RET"
    },
    {
      "address": "00bf0f7d",
      "instruction": "MOV EAX,0x2"
    },
    {
      "address": "00bf0f82",
      "instruction": "RET"
    },
    {
      "address": "00bf0f83",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "00bf0f85",
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
  "body_end": "00bf0f85",
  "body_span_bytes": 70,
  "body_start": "00bf0f40",
  "callees": [
    "FUN_00bd81d0"
  ],
  "callers": [
    "FUN_00bf74a0",
    "FUN_00d04320",
    "FUN_00dd35c0",
    "FUN_00e053c0",
    "FUN_00d02050",
    "FUN_00be88d0",
    "FUN_00cf9ba0",
    "FUN_00ae7ce0",
    "FUN_00bf7230",
    "FUN_00dd3810",
    "FUN_00bf1fd0",
    "FUN_00e2d6a0",
    "FUN_00dd1f70",
    "FUN_00d00b40",
    "FUN_00cfe820",
    "FUN_00e04770",
    "FUN_00bf8440",
    "FUN_00dd2320",
    "FUN_00dd1e30",
    "FUN_00aee830"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00bf0f40",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "iVar1",
      "storage": "register:00000000:4",
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
  "name": "FUN_00bf0f40",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x7f0f40",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00bf0f40(void)",
  "size_bytes": 70,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00bf0f40",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 33,
  "xrefs": [
    {
      "from": "00d00b5d"
    },
    {
      "from": "00d02115"
    },
    {
      "from": "00d0212f"
    },
    {
      "from": "00d02154"
    },
    {
      "from": "00d02188"
    },
    {
      "from": "00d021f0"
    },
    {
      "from": "00d045ab"
    },
    {
      "from": "00be8aab"
    },
    {
      "from": "00be8acb"
    },
    {
      "from": "00ae7d6b"
    },
    {
      "from": "00bf1ffc"
    },
    {
      "from": "00bf727e"
    },
    {
      "from": "00bf766b"
    },
    {
      "from": "00bf860d"
    },
    {
      "from": "00bf8643"
    },
    {
      "from": "00cfa005"
    },
    {
      "from": "00cfe8b5"
    },
    {
      "from": "00cfe8cb"
    },
    {
      "from": "00cfe8ed"
    },
    {
      "from": "00cfe8f9"
    },
    {
      "from": "00dd1e9e"
    },
    {
      "from": "00dd20a1"
    },
    {
      "from": "00dd3682"
    },
    {
      "from": "00dd375e"
    },
    {
      "from": "00dd3877"
    },
    {
      "from": "00dd25d8"
    },
    {
      "from": "00e048e1"
    },
    {
      "from": "00aee9be"
    },
    {
      "from": "00e053f2"
    },
    {
      "from": "00e2da22"
    },
    {
      "from": "00b5f7f5"
    },
    {
      "from": "00b5f852"
    },
    {
      "from": "00b5f8af"
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
