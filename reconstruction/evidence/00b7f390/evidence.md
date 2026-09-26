# Evidence 0x00b7f390

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `e32f7f3920b801356ae9eee246be29abbf0573a490b8a0d670aad8e14fe0e982`

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
  "content_sha256": "36bf03acae89bc4c3780bd1bd4f438296c6558fef6a88603492eeaea2502bed0",
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
        "obs-0015"
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
        "obs-0008"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          32,
          236
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
        "obs-0015"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0015"
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
        "obs-0015"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0015"
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
      "at": "0x00b7f390",
      "count": 4,
      "first_use": 0,
      "first_write_index": 3,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00b7f391",
      "count": 3,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00b7f392",
      "count": 1,
      "first_use": 2,
      "first_write_index": 16,
      "id": "obs-0003",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV EDI,dword ptr [ESP + 0xc]",
      "reg": "ESP"
    },
    {
      "at": "0x00b7f392",
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
      "at": "0x00b7f392",
      "definite": true,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV EDI,dword ptr [ESP + 0xc]",
      "reg": "EDI",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00b7f396",
      "count": 2,
      "first_use": 3,
      "first_write_index": 6,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00b7f396",
      "definite": true,
      "id": "obs-0007",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00b7f3a0",
      "definite": true,
      "id": "obs-0008",
      "index": 6,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [ESI + 0x20]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00b7f3a7",
      "count": 4,
      "first_use": 9,
      "first_write_index": null,
      "id": "obs-0009",
      "index": 9,
      "kind": "REG_READ",
      "raw": "LEA EAX,[EDI + 0xfe9ab3ff]",
      "reg": "EAX"
    },
    {
      "at": "0x00b7f3b9",
      "base": n
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
"\nvoid __thiscall FUN_00b7f390(int param_1,int param_2)\n\n{\n  if (*(int *)(param_1 + 0xec) != param_2) {\n    if (*(int *)(param_1 + 0x20) != 0) {\n      switch(param_2) {\n      case 0x1654c01:\n      case 0x1654c02:\n      case 0x1654c04:\n      case 0x1654c05:\n      case 0x1654c06:\n      case 0x1654c10:\n        FUN_00b7e0b0(*(int *)(param_1 + 0x20));\n      }\n    }\n    *(int *)(param_1 + 0xec) = param_2;\n  }\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 21,
  "instructions": [
    {
      "address": "00b7f390",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00b7f391",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00b7f392",
      "instruction": "MOV EDI,dword ptr [ESP + 0xc]"
    },
    {
      "address": "00b7f396",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00b7f398",
      "instruction": "CMP dword ptr [ESI + 0xec],EDI"
    },
    {
      "address": "00b7f39e",
      "instruction": "JZ 0x00b7f3cf"
    },
    {
      "address": "00b7f3a0",
      "instruction": "MOV ECX,dword ptr [ESI + 0x20]"
    },
    {
      "address": "00b7f3a3",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00b7f3a5",
      "instruction": "JZ 0x00b7f3c9"
    },
    {
      "address": "00b7f3a7",
      "instruction": "LEA EAX,[EDI + 0xfe9ab3ff]"
    },
    {
      "address": "00b7f3ad",
      "instruction": "CMP EAX,0xf"
    },
    {
      "address": "00b7f3b0",
      "instruction": "JA 0x00b7f3c9"
    },
    {
      "address": "00b7f3b2",
      "instruction": "MOVZX EAX,byte ptr [EAX + 0xb7f3dc]"
    },
    {
      "address": "00b7f3b9",
      "instruction": "JMP dword ptr [EAX*0x4 + 0xb7f3d4]"
    },
    {
      "address": "00b7f3c0",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00b7f3c1",
      "instruction": "CALL 0x00b7e0b0"
    },
    {
      "address": "00b7f3c6",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "00b7f3c9",
      "instruction": "MOV dword ptr [ESI + 0xec],EDI"
    },
    {
      "address": "00b7f3cf",
      "instruction": "POP EDI"
    },
    {
      "address": "00b7f3d0",
      "instruction": "POP ESI"
    },
    {
      "address": "00b7f3d1",
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
  "body_end": "00b7f3d3",
  "body_span_bytes": 68,
  "body_start": "00b7f390",
  "callees": [
    "FUN_00b7e0b0"
  ],
  "callers": [
    "FUN_00b33030",
    "FUN_00b33130",
    "FUN_00b33540",
    "FUN_00b32e80"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00b7f390",
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
      "type": "int"
    }
  ],
  "locals_count": 2,
  "mode": "live",
  "name": "FUN_00b7f390",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x77f390",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00b7f390(void)",
  "size_bytes": 68,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00b7f390",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 4,
  "xrefs": [
    {
      "from": "00b32ec8"
    },
    {
      "from": "00b3303d"
    },
    {
      "from": "00b33189"
    },
    {
      "from": "00b33583"
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
