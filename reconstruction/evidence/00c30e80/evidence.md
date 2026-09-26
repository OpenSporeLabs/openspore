# Evidence 0x00c30e80

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `5a5ddea29b70de01fcd8dcd740a4701782d5b9db8f0cf57965d2d26587371b6c`

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
    "return_semantics": "unclassified_in_EAX",
    "saved_registers": [
      "ESI"
    ],
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
  "content_sha256": "906d290d98d13d69ba64239392d0905854038ac723c985fdf60fc6d4d279f1c6",
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
        "obs-0013"
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
        "obs-0002",
        "obs-0003",
        "obs-0005",
        "obs-0006"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          88
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0005",
        "obs-0006",
        "obs-0013"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0013"
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
        "obs-0013"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0013"
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
      "at": "0x00c30e80",
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
      "at": "0x00c30e81",
      "count": 1,
      "first_use": 1,
      "first_write_index": 3,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00c30e81",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00c30e83",
      "id": "obs-0004",
      "index": 2,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00b3d300",
      "target": "0x00b3d300"
    },
    {
      "at": "0x00c30e88",
      "count": 4,
      "first_use": 3,
      "first_write_index": 6,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV ECX,EAX",
      "reg": "EAX"
    },
    {
      "at": "0x00c30e88",
      "definite": true,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,EAX",
      "reg": "ECX",
      "write_kind": "reg"
    },
    {
      "at": "0x00c30e8a",
      "id": "obs-0007",
      "index": 4,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00f67d90",
      "target": "0x00f67d90"
    },
    {
      "at": "0x00c30e91",
      "definite": true,
      "id": "obs-0008",
      "index": 6,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,0x1",
      "reg": "EAX",
      "write_kind": "imm"
    },
    {
      "at": "0x00c30e9a",
      "id": "obs-0009",
      "index": 9,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00c75420",
      "target": "0x00c75420"
    },
    {
      "at": "0x00c30ea4",
      "id": "obs-0010",
      "index": 13,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00c30cc0",
      "target": "0x00c30cc0"
    },
    {
      "at": "0x00c30ea9",
      "definite": true,
      "id": "obs-0011",
      "index": 14,
      "kind": "REG_WRITE",
      "raw": "ADD ESP,0x8",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00c30eac",
      "id": "obs-0012",
      "index": 15,
      "kind": "REG_RESTORE",
      "raw": "POP ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00c30ead",
      "form": "RET",
      "id": "obs-0013",
      "imm": null,
      "index": 16,
      "kind": "RET",
      "raw": "RET"
    }
  ],
  "parse": {
    "declared_count": 17,
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
      "sub
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
"\nvoid __fastcall FUN_00c30e80(int param_1)\n\n{\n  int iVar1;\n  undefined4 uVar2;\n  \n  FUN_00b3d300();\n  iVar1 = FUN_00f67d90();\n  uVar2 = 1;\n  if (iVar1 != 0) {\n    uVar2 = FUN_00c75420();\n  }\n  FUN_00c30cc0(*(undefined4 *)(param_1 + 0x58),uVar2);\n  return;\n}\n\n"
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
      "address": "00c30e80",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00c30e81",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00c30e83",
      "instruction": "CALL 0x00b3d300"
    },
    {
      "address": "00c30e88",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00c30e8a",
      "instruction": "CALL 0x00f67d90"
    },
    {
      "address": "00c30e8f",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00c30e91",
      "instruction": "MOV EAX,0x1"
    },
    {
      "address": "00c30e96",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00c30e98",
      "instruction": "JZ 0x00c30e9f"
    },
    {
      "address": "00c30e9a",
      "instruction": "CALL 0x00c75420"
    },
    {
      "address": "00c30e9f",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00c30ea0",
      "instruction": "MOV EAX,dword ptr [ESI + 0x58]"
    },
    {
      "address": "00c30ea3",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00c30ea4",
      "instruction": "CALL 0x00c30cc0"
    },
    {
      "address": "00c30ea9",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "00c30eac",
      "instruction": "POP ESI"
    },
    {
      "address": "00c30ead",
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
  "body_end": "00c30ead",
  "body_span_bytes": 46,
  "body_start": "00c30e80",
  "callees": [
    "FUN_00c75420",
    "FUN_00b3d300",
    "FUN_00f67d90",
    "FUN_00c30cc0"
  ],
  "callers": [
    "FUN_00baf700",
    "FUN_00d05a20",
    "FUN_00d06030",
    "FUN_00d05d90",
    "FUN_00d03d70"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00c30e80",
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
      "name": "uVar2",
      "storage": "register:00000000:4",
      "type": "undefined4"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int"
    }
  ],
  "locals_count": 3,
  "mode": "live",
  "name": "FUN_00c30e80",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x830e80",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00c30e80(void)",
  "size_bytes": 46,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00c30e80",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 5,
  "xrefs": [
    {
      "from": "00baf706"
    },
    {
      "from": "00d05c60"
    },
    {
      "from": "00d05e0a"
    },
    {
      "from": "00d03db2"
    },
    {
      "from": "00d06168"
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
