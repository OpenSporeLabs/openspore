# Evidence 0x00b515e0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `82c146af8ad236b701443f8e60d43ed62f7b1272bc65e303b68a725f1027a3e7`

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
      "EDI",
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
  "content_sha256": "11f9e095f1cbf58452c4df54cce245cec4318ffab11e7326bb0fb22720d89855",
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
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
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
        "obs-0010"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          48
        ],
        "register": "ECX",
        "written_through": 1
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0010",
        "obs-0018"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
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
        "obs-0018"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0018"
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
      "at": "0x00b515e7",
      "count": 2,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0001",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00b515e8",
      "count": 2,
      "first_use": 2,
      "first_write_index": 15,
      "id": "obs-0002",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV EDI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00b515e8",
      "definite": true,
      "id": "obs-0003",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV EDI,ECX",
      "reg": "EDI",
      "write_kind": "reg"
    },
    {
      "at": "0x00b515ec",
      "definite": true,
      "id": "obs-0004",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,[0x0167ecd4]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00b515f5",
      "count": 3,
      "first_use": 7,
      "first_write_index": 8,
      "id": "obs-0005",
      "index": 7,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00b515f6",
      "count": 4,
      "first_use": 8,
      "first_write_index": 4,
      "id": "obs-0006",
      "index": 8,
      "kind": "REG_READ",
      "raw": "MOV ESI,dword ptr [EAX + 0x1c]",
      "reg": "EAX"
    },
    {
      "at": "0x00b515f6",
      "definite": true,
      "id": "obs-0007",
      "index": 8,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,dword ptr [EAX + 0x1c]",
      "reg": "ESI",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00b515f9",
      "id": "obs-0008",
      "index": 9,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00b3d350",
      "target": "0x00b3d350"
    },
    {
      "at": "0x00b51608",
      "id": "obs-0009",
      "index": 14,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00b3d350",
      "target": "0x00b3d350"
    },
    {
      "at": "0x00b5160d",
      "definite": true,
      "id": "obs-0010",
      "index": 15,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [EAX + 0x24]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00b51612",
      "definite": true,
      "id": "obs-0011",
      "index": 17,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [EAX + 0xc]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00b51615",
      "count": 1,
      "first_use": 18,
      "first_write_index": 17,
      "id": "obs-0012",
      "index": 18,
      "kind": "REG_READ",
      "raw": "CALL EDX",
      "reg": "EDX"
    },
    {
      "at": "0x00b51615",
      "base": "EDX",
      "disp": null,
      "id": "obs-0013",
      "index": 18,
      "kind": "CALL_INDIRECT",
      "raw": "CALL EDX",
      "via": "register"
    },
    {
      "at": "0x00b51624",
      "id": "obs-0014",
      "index": 24,
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
"\n/* WARNING: Enum \"ObjectTYPE\": Some values do not have unique names */\n/* WARNING: Enum \"Names\": Some values do not have unique names */\n\nvoid __fastcall FUN_00b515e0(int param_1)\n\n{\n  int iVar1;\n  cGameInputManager *pcVar2;\n  int iVar3;\n  \n  if (DAT_0167ecd0 == 0) {\n    return;\n  }\n  if (DAT_0167ecd4 == 0) goto LAB_00b51633;\n  iVar1 = *(int *)(DAT_0167ecd4 + 0x1c);\n  pcVar2 = Simulator__cGameInputManager__Get();\n  if (*(cGameInputManager **)(iVar1 + 0x34) == pcVar2) {\n    pcVar2 = Simulator__cGameInputManager__Get();\n    iVar3 = (**(code **)(*(int *)pcVar2->field_18 + 0xc))();\n    if (*(int *)(iVar1 + 0x3c) != *(int *)(iVar3 + 8)) goto LAB_00b51624;\n  }\n  else {\nLAB_00b51624:\n    FUN_00b4f7f0();\n  }\n  if (DAT_0167ecd4 != 0) {\n    return;\n  }\nLAB_00b51633:\n  FUN_00b512f0();\n  *(undefined1 *)(param_1 + 0x30) = 1;\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 32,
  "instructions": [
    {
      "address": "00b515e0",
      "instruction": "CMP dword ptr [0x0167ecd0],0x0"
    },
    {
      "address": "00b515e7",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00b515e8",
      "instruction": "MOV EDI,ECX"
    },
    {
      "address": "00b515ea",
      "instruction": "JZ 0x00b5163c"
    },
    {
      "address": "00b515ec",
      "instruction": "MOV EAX,[0x0167ecd4]"
    },
    {
      "address": "00b515f1",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00b515f3",
      "instruction": "JZ 0x00b51633"
    },
    {
      "address": "00b515f5",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00b515f6",
      "instruction": "MOV ESI,dword ptr [EAX + 0x1c]"
    },
    {
      "address": "00b515f9",
      "instruction": "CALL 0x00b3d350"
    },
    {
      "address": "00b515fe",
      "instruction": "CMP dword ptr [ESI + 0x34],EAX"
    },
    {
      "address": "00b51601",
      "instruction": "SETNZ AL"
    },
    {
      "address": "00b51604",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00b51606",
      "instruction": "JNZ 0x00b51624"
    },
    {
      "address": "00b51608",
      "instruction": "CALL 0x00b3d350"
    },
    {
      "address": "00b5160d",
      "instruction": "MOV ECX,dword ptr [EAX + 0x24]"
    },
    {
      "address": "00b51610",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "00b51612",
      "instruction": "MOV EDX,dword ptr [EAX + 0xc]"
    },
    {
      "address": "00b51615",
      "instruction": "CALL EDX"
    },
    {
      "address": "00b51617",
      "instruction": "MOV ECX,dword ptr [ESI + 0x3c]"
    },
    {
      "address": "00b5161a",
      "instruction": "CMP ECX,dword ptr [EAX + 0x8]"
    },
    {
      "address": "00b5161d",
      "instruction": "SETNZ AL"
    },
    {
      "address": "00b51620",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00b51622",
      "instruction": "JZ 0x00b51629"
    },
    {
      "address": "00b51624",
      "instruction": "CALL 0x00b4f7f0"
    },
    {
      "address": "00b51629",
      "instruction": "CMP dword ptr [0x0167ecd4],0x0"
    },
    {
      "address": "00b51630",
      "instruction": "POP ESI"
    },
    {
      "address": "00b51631",
      "instruction": "JNZ 0x00b5163c"
    },
    {
      "address": "00b51633",
      "instruction": "CALL 0x00b512f0"
    },
    {
      "address": "00b51638",
      "instruction": "MOV byte ptr [EDI + 0x30],0x1"
    },
    {
      "address": "00b5163c",
      "instruction": "POP EDI"
    },
    {
      "address": "00b5163d",
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
  "body_end": "00b5163d",
  "body_span_bytes": 94,
  "body_start": "00b515e0",
  "callees": [
    "FUN_00b4f7f0",
    "Simulator::cGameInputManager::Get",
    "FUN_00b512f0"
  ],
  "callers": [
    "FUN_00fe0e10",
    "FUN_00fdc800",
    "FUN_00ed4b70",
    "FUN_00b3d7a0",
    "FUN_00fdc710",
    "FUN_00fe0160",
    "FUN_00fe0f40",
    "FUN_00f44dd0",
    "FUN_00fdc240"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00b515e0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "iVar1",
      "storage": "unique:00017200:4",
      "type": "int"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int"
    },
    {
      "name": "iVar3",
      "storage": "register:00000000:4",
      "type": "int"
    },
    {
      "name": "pcVar2",
      "storage": "register:00000000:4",
      "type": "cGameInputManager *"
    }
  ],
  "locals_count": 4,
  "mode": "live",
  "name": "FUN_00b515e0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x7515e0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00b515e0(void)",
  "size_bytes": 94,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00b515e0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 10,
  "xrefs": [
    {
      "from": "00b3d7a3"
    },
    {
      "from": "00fe0e66"
    },
    {
      "from": "00f44f66"
    },
    {
      "from": "00fdc31c"
    },
    {
      "from": "00fdc74c"
    },
    {
      "from": "00fdc864"
    },
    {
      "from": "00fe03b4"
    },
    {
      "from": "00fe105e"
    },
    {
      "from": "00b4cfa2"
    },
    {
      "from": "00ed4bd7"
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
