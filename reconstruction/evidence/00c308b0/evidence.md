# Evidence 0x00c308b0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `63d74b3d7a670ca05f42506a6b159a8fa05764fc0ca79be4a38a72127e54f9a3`

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
  "content_sha256": "52dbd1fa1f17f0c459f45722b2579808e4b2f80ba275e8d613b681a95cdaca51",
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
        "obs-0010"
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
          132
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
        "obs-0010"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0010"
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
        "obs-0010"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0010"
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
      "at": "0x00c308b0",
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
      "at": "0x00c308b1",
      "count": 2,
      "first_use": 1,
      "first_write_index": 3,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00c308b1",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00c308b3",
      "id": "obs-0004",
      "index": 2,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00b3d2a0",
      "target": "0x00b3d2a0"
    },
    {
      "at": "0x00c308b8",
      "count": 1,
      "first_use": 3,
      "first_write_index": 9,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV ECX,EAX",
      "reg": "EAX"
    },
    {
      "at": "0x00c308b8",
      "definite": true,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,EAX",
      "reg": "ECX",
      "write_kind": "reg"
    },
    {
      "at": "0x00c308ba",
      "id": "obs-0007",
      "index": 4,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00885c90",
      "target": "0x00885c90"
    },
    {
      "at": "0x00c308c7",
      "id": "obs-0008",
      "index": 7,
      "kind": "REG_RESTORE",
      "raw": "POP ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00c308cb",
      "definite": true,
      "id": "obs-0009",
      "index": 9,
      "kind": "REG_WRITE",
      "raw": "MOV AL,CL",
      "reg": "EAX",
      "write_kind": "reg"
    },
    {
      "at": "0x00c308cd",
      "form": "RET",
      "id": "obs-0010",
      "imm": null,
      "index": 10,
      "kind": "RET",
      "raw": "RET"
    }
  ],
  "parse": {
    "declared_count": 11,
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
    "max_offset": 132,
    "offsets": [
      132
    ],
    "present": true,
    "register": "ECX",
    "shape": "R-ALIAS",
    "written_through": 0
  },
  "return": {
    "aggregate_evidence": {
      "bulk_write": false
    },
    "confidence": "INFERRED",
    "register": "EAX",
    "register_class": "aggregate_unknown",
    "type": null,
    "void_po
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
"\nbool __fastcall FUN_00c308b0(int param_1)\n\n{\n  int iVar1;\n  \n  FUN_00b3d2a0();\n  iVar1 = FUN_00885c90();\n  return iVar1 == *(int *)(param_1 + 0x84);\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 11,
  "instructions": [
    {
      "address": "00c308b0",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00c308b1",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00c308b3",
      "instruction": "CALL 0x00b3d2a0"
    },
    {
      "address": "00c308b8",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00c308ba",
      "instruction": "CALL 0x00885c90"
    },
    {
      "address": "00c308bf",
      "instruction": "XOR ECX,ECX"
    },
    {
      "address": "00c308c1",
      "instruction": "CMP EAX,dword ptr [ESI + 0x84]"
    },
    {
      "address": "00c308c7",
      "instruction": "POP ESI"
    },
    {
      "address": "00c308c8",
      "instruction": "SETZ CL"
    },
    {
      "address": "00c308cb",
      "instruction": "MOV AL,CL"
    },
    {
      "address": "00c308cd",
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
  "body_end": "00c308cd",
  "body_span_bytes": 30,
  "body_start": "00c308b0",
  "callees": [
    "FUN_00885c90",
    "FUN_00b3d2a0"
  ],
  "callers": [
    "FUN_00fdfbc0",
    "FUN_00c555d0",
    "FUN_00bb1340",
    "FUN_0106cc70",
    "FUN_00be7bf0",
    "FUN_0106ba00",
    "FUN_00becd70",
    "FUN_00bbcf00",
    "FUN_00ba0080",
    "FUN_00bb4100"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00c308b0",
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
  "name": "FUN_00c308b0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x8308b0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00c308b0(void)",
  "size_bytes": 30,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00c308b0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 12,
  "xrefs": [
    {
      "from": "00bb1460"
    },
    {
      "from": "00bb42f5"
    },
    {
      "from": "00bbd020"
    },
    {
      "from": "0106bc84"
    },
    {
      "from": "0106d209"
    },
    {
      "from": "00be85fb"
    },
    {
      "from": "00beceaa"
    },
    {
      "from": "00ba0186"
    },
    {
      "from": "00fdfc50"
    },
    {
      "from": "00c55610"
    },
    {
      "from": "00fe337c"
    },
    {
      "from": "0100c2d4"
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
