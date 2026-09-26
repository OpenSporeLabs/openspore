# Evidence 0x00bd8210

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `17e1d533b54f56acb4e2e8649ee2692493c81b7421478d0d1d11eb4ae1d90843`

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
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +8, so the listing is not one path"
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
  "content_sha256": "d1949883f04d735060d92003a89f41df3c030bc6a7a14303f0ac5d17d9a73be3",
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
        "obs-0001",
        "obs-0002",
        "obs-0011"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          0,
          88
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0002",
        "obs-0011",
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
      "at": "0x00bd8210",
      "count": 1,
      "first_use": 0,
      "first_write_index": 8,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ECX]",
      "reg": "ECX"
    },
    {
      "at": "0x00bd8210",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ECX]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00bd8212",
      "count": 4,
      "first_use": 1,
      "first_write_index": 0,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [EAX + 0x58]",
      "reg": "EAX"
    },
    {
      "and_esp": null,
      "at": "0x00bd8215",
      "ebp_is_general_register": false,
      "fp": false,
      "id": "obs-0004",
      "index": 2,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": false,
      "push_ebp_at": null,
      "raw": "SUB ESP,0xc",
      "sub": 12
    },
    {
      "at": "0x00bd8215",
      "definite": true,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0xc",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00bd8218",
      "count": 2,
      "first_use": 3,
      "first_write_index": null,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_READ",
      "raw": "LEA EDX,[ESP]",
      "reg": "EDX"
    },
    {
      "at": "0x00bd8218",
      "count": 1,
      "first_use": 3,
      "first_write_index": 2,
      "id": "obs-0007",
      "index": 3,
      "kind": "REG_READ",
      "raw": "LEA EDX,[ESP]",
      "reg": "ESP"
    },
    {
      "at": "0x00bd8218",
      "base": "ESP",
      "disp": 0,
      "id": "obs-0008",
      "index": 3,
      "key": null,
      "kind": "STACK_SLOT_READ",
      "raw": "LEA EDX,[ESP]",
      "reason": "local",
      "resolved": false,
      "size": 4
    },
    {
      "at": "0x00bd821c",
      "base": "EAX",
      "disp": null,
      "id": "obs-0009",
      "index": 5,
      "kind": "CALL_INDIRECT",
      "raw": "CALL EAX",
      "via": "register"
    },
    {
      "at": "0x00bd821f",
      "id": "obs-0010",
      "index": 7,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00b3d350",
      "target": "0x00b3d350"
    },
    {
      "at": "0x00bd8224",
      "definite": true,
      "id": "obs-0011",
      "index": 8,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,EAX",
      "reg": "ECX",
      "write_kind": "reg"
    },
    {
      "at": "0x00bd8226",
      "id": "obs-0012",
      "index": 9,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00b88590",
      "target": "0x00b88590"
    },
    {
      "at": "0x00bd822e",
      "form": "RET",
      "id": "obs-0013",
      "imm": null
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
"\n/* WARNING: Enum \"ObjectTYPE\": Some values do not have unique names */\n/* WARNING: Enum \"Names\": Some values do not have unique names */\n\nvoid __fastcall FUN_00bd8210(int *param_1)\n\n{\n  undefined4 uVar1;\n  undefined1 local_c [12];\n  \n  uVar1 = (**(code **)(*param_1 + 0x58))(local_c);\n  Simulator__cGameInputManager__Get();\n  FUN_00b88590(uVar1);\n  return;\n}\n\n"
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
      "address": "00bd8210",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "00bd8212",
      "instruction": "MOV EAX,dword ptr [EAX + 0x58]"
    },
    {
      "address": "00bd8215",
      "instruction": "SUB ESP,0xc"
    },
    {
      "address": "00bd8218",
      "instruction": "LEA EDX,[ESP]"
    },
    {
      "address": "00bd821b",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00bd821c",
      "instruction": "CALL EAX"
    },
    {
      "address": "00bd821e",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00bd821f",
      "instruction": "CALL 0x00b3d350"
    },
    {
      "address": "00bd8224",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00bd8226",
      "instruction": "CALL 0x00b88590"
    },
    {
      "address": "00bd822b",
      "instruction": "ADD ESP,0xc"
    },
    {
      "address": "00bd822e",
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
  "body_end": "00bd822e",
  "body_span_bytes": 31,
  "body_start": "00bd8210",
  "callees": [
    "FUN_00b88590",
    "Simulator::cGameInputManager::Get"
  ],
  "callers": [
    "FUN_00bf00a0",
    "FUN_00bf0110",
    "FUN_00bf9e70",
    "FUN_00ca8340",
    "FUN_00bfb020",
    "FUN_00bf0130",
    "FUN_00bfa660",
    "FUN_00d04320",
    "FUN_00bf5720",
    "FUN_00bf8440",
    "FUN_00bf9820"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00bd8210",
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
      "name": "uVar1",
      "storage": "register:00000000:4",
      "type": "undefined4"
    },
    {
      "name": "local_c",
      "storage": "",
      "type": "undefined1[12]"
    }
  ],
  "locals_count": 3,
  "mode": "live",
  "name": "FUN_00bd8210",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x7d8210",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00bd8210(void)",
  "size_bytes": 31,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00bd8210",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 21,
  "xrefs": [
    {
      "from": "00d043c4"
    },
    {
      "from": "00d04415"
    },
    {
      "from": "00d0443a"
    },
    {
      "from": "00d044a0"
    },
    {
      "from": "00bf016d"
    },
    {
      "from": "00bf0199"
    },
    {
      "from": "00bf578b"
    },
    {
      "from": "00bf85f1"
    },
    {
      "from": "00bf00cb"
    },
    {
      "from": "00bf9b34"
    },
    {
      "from": "00bf9d16"
    },
    {
      "from": "00bfa338"
    },
    {
      "from": "00bfa51a"
    },
    {
      "from": "00bfad49"
    },
    {
      "from": "00bfad54"
    },
    {
      "from": "00bfaede"
    },
    {
      "from": "00bfaee7"
    },
    {
      "from": "00bf011c"
    },
    {
      "from": "00bfb31f"
    },
    {
      "from": "00bfb328"
    },
    {
      "from": "00ca8451"
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
