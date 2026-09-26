# Evidence 0x00bba500

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `d7184f80da9aeaaef86008b295cdc857a508ad9feff63c42b017c058c7cc8901`

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
    "return_semantics": "pointer_like_in_EAX",
    "saved_registers": [
      "ESI"
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -4, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "e8f868c37135fa0b0e614c3a39654935eb8e1ecf278ea4f53e72b154d9108702",
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
        "obs-0009",
        "obs-0016",
        "obs-0018"
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
        "obs-0004",
        "obs-0011"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "SUPPORTED",
      "id": "R1",
      "value": {
        "offsets": [
          76,
          116,
          128
        ],
        "register": "ECX",
        "written_through": 1
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0004",
        "obs-0009",
        "obs-0011",
        "obs-0016",
        "obs-0018"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0009",
        "obs-0016",
        "obs-0018"
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
        "obs-0009",
        "obs-0016",
        "obs-0018"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0009",
        "obs-0016",
        "obs-0018"
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
      "at": "0x00bba500",
      "count": 10,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00bba501",
      "count": 1,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00bba501",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00bba503",
      "definite": true,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [ESI + 0x74]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00bba506",
      "count": 4,
      "first_use": 3,
      "first_write_index": 7,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "LEA EAX,[ESI + 0x74]",
      "reg": "EAX"
    },
    {
      "at": "0x00bba511",
      "definite": true,
      "id": "obs-0006",
      "index": 7,
      "kind": "REG_WRITE",
      "raw": "SETG AL",
      "reg": "EAX",
      "write_kind": "unknown"
    },
    {
      "at": "0x00bba51a",
      "id": "obs-0007",
      "index": 11,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00bba2a0",
      "target": "0x00bba2a0"
    },
    {
      "at": "0x00bba525",
      "id": "obs-0008",
      "index": 13,
      "kind": "REG_RESTORE",
      "raw": "POP ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00bba526",
      "form": "RET",
      "id": "obs-0009",
      "imm": null,
      "index": 14,
      "kind": "RET",
      "raw": "RET"
    },
    {
      "at": "0x00bba527",
      "definite": true,
      "id": "obs-0010",
      "index": 15,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [ESI + 0x80]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00bba531",
      "count": 2,
      "first_use": 18,
      "first_write_index": 15,
      "id": "obs-0011",
      "index": 18,
      "kind": "REG_READ",
      "raw": "CMP dword ptr [EDX + 0x504],ECX",
      "reg": "EDX"
    },
    {
      "at": "0x00bba53a",
      "id": "obs-0012",
      "index": 21,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00401090",
      "target": "0x00401090"
    },
    {
      "at": "0x00bba541",
      "id": "obs-0013",
      "index": 23,
      "kind":
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
"\n/* WARNING: Enum \"Names\": Some values do not have unique names */\n\nint __fastcall FUN_00bba500(int param_1)\n\n{\n  int iVar1;\n  int iVar2;\n  \n  iVar2 = param_1 + 0x74;\n  if (*(int *)(param_1 + 0x74) == 0) {\n    if (1 < *(int *)(param_1 + 0x4c)) {\n      cStarRecord__ctor();\n    }\n    return *(int *)(param_1 + 0x80);\n  }\n  iVar1 = *(int *)(param_1 + 0x80);\n  if ((iVar1 == 0) || (*(int *)(iVar1 + 0x504) != *(int *)(param_1 + 0x74))) {\n    Editors__cSpeciesManager__Get();\n    iVar1 = FUN_004df550(iVar2);\n    *(int *)(param_1 + 0x80) = iVar1;\n    if (iVar1 == 0) {\n      cStarRecord__ctor();\n      return *(int *)(param_1 + 0x80);\n    }\n  }\n  return iVar1;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 35,
  "instructions": [
    {
      "address": "00bba500",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00bba501",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00bba503",
      "instruction": "MOV ECX,dword ptr [ESI + 0x74]"
    },
    {
      "address": "00bba506",
      "instruction": "LEA EAX,[ESI + 0x74]"
    },
    {
      "address": "00bba509",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00bba50b",
      "instruction": "JNZ 0x00bba527"
    },
    {
      "address": "00bba50d",
      "instruction": "CMP dword ptr [ESI + 0x4c],0x1"
    },
    {
      "address": "00bba511",
      "instruction": "SETG AL"
    },
    {
      "address": "00bba514",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00bba516",
      "instruction": "JZ 0x00bba51f"
    },
    {
      "address": "00bba518",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00bba51a",
      "instruction": "CALL 0x00bba2a0"
    },
    {
      "address": "00bba51f",
      "instruction": "MOV EAX,dword ptr [ESI + 0x80]"
    },
    {
      "address": "00bba525",
      "instruction": "POP ESI"
    },
    {
      "address": "00bba526",
      "instruction": "RET"
    },
    {
      "address": "00bba527",
      "instruction": "MOV EDX,dword ptr [ESI + 0x80]"
    },
    {
      "address": "00bba52d",
      "instruction": "TEST EDX,EDX"
    },
    {
      "address": "00bba52f",
      "instruction": "JZ 0x00bba539"
    },
    {
      "address": "00bba531",
      "instruction": "CMP dword ptr [EDX + 0x504],ECX"
    },
    {
      "address": "00bba537",
      "instruction": "JZ 0x00bba55f"
    },
    {
      "address": "00bba539",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00bba53a",
      "instruction": "CALL 0x00401090"
    },
    {
      "address": "00bba53f",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00bba541",
      "instruction": "CALL 0x004df550"
    },
    {
      "address": "00bba546",
      "instruction": "MOV dword ptr [ESI + 0x80],EAX"
    },
    {
      "address": "00bba54c",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00bba54e",
      "instruction": "JNZ 0x00bba561"
    },
    {
      "address": "00bba550",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00bba552",
      "instruction": "CALL 0x00bba2a0"
    },
    {
      "address": "00bba557",
      "instruction": "MOV EAX,dword ptr [ESI + 0x80]"
    },
    {
      "address": "00bba55d",
      "instruction": "POP ESI"
    },
    {
      "address": "00bba55e",
      "instruction": "RET"
    },
    {
      "address": "00bba55f",
      "instruction": "MOV EAX,EDX"
    },
    {
      "address": "00bba561",
      "instruction": "POP ESI"
    },
    {
      "address": "00bba562",
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
  "body_end": "00bba562",
  "body_span_bytes": 99,
  "body_start": "00bba500",
  "callees": [
    "FUN_004df550",
    "cStarRecord__ctor",
    "Editors::cSpeciesManager::Get"
  ],
  "callers": [
    "FUN_010221f0",
    "FUN_00cfbc10",
    "FUN_00bb1340",
    "FUN_00c30c80",
    "FUN_00c32cd0",
    "FUN_00bb4af0",
    "FUN_00c33580",
    "FUN_00c70860"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00bba500",
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
    },
    {
      "name": "iVar2",
      "storage": "Stack[-0x8]:4",
      "type": "int"
    }
  ],
  "locals_count": 3,
  "mode": "live",
  "name": "FUN_00bba500",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x7ba500",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00bba500(void)",
  "size_bytes": 99,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00bba500",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 9,
  "xrefs": [
    {
      "from": "00bb146b"
    },
    {
      "from": "00c32d57"
    },
    {
      "from": "00bb4b83"
    },
    {
      "from": "00c30c9e"
    },
    {
      "from": "00c335f0"
    },
    {
      "from": "010223e8"
    },
    {
      "from": "01022411"
    },
    {
      "from": "00c7086d"
    },
    {
      "from": "00cfc4b2"
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
