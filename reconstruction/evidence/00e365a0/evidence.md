# Evidence 0x00e365a0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `caae434bb70051d5ef1f7d6c46f4f33f4488bdc2f246bd760556c21b5dfc9ff2`

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
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -8, so the listing is not one path",
    "unparsed_lines_present: 1 line(s) matched no grammar rule"
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
  "content_sha256": "8425d96bdc2234ba8d18bb20884a9999632b4839c36dc16b610a1b2c031ca3c1",
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
        "obs-0021",
        "obs-0026"
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
        "obs-0006"
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
        "obs-0002",
        "obs-0003",
        "obs-0005",
        "obs-0006",
        "obs-0007"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          12,
          16,
          48,
          76
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
        "obs-0007",
        "obs-0021",
        "obs-0026"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0021",
        "obs-0026"
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
        "obs-0021",
        "obs-0026"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0021",
        "obs-0026"
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
      "at": "0x00e365a0",
      "count": 8,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00e365a1",
      "count": 4,
      "first_use": 1,
      "first_write_index": 5,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EDI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00e365a1",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EDI,ECX",
      "reg": "EDI",
      "write_kind": "reg"
    },
    {
      "at": "0x00e365a9",
      "definite": true,
      "id": "obs-0004",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [EDI + 0x10]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00e365ac",
      "count": 1,
      "first_use": 5,
      "first_write_index": 14,
      "id": "obs-0005",
      "index": 5,
      "kind": "REG_READ",
      "raw": "MOV ECX,dword ptr [ESP + 0x8]",
      "reg": "ESP"
    },
    {
      "at": "0x00e365ac",
      "base": "ESP",
      "disp": 8,
      "id": "obs-0006",
      "index": 5,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV ECX,dword ptr [ESP + 0x8]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00e365ac",
      "definite": true,
      "id": "obs-0007",
      "index": 5,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [ESP + 0x8]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00e365b0",
      "count": 1,
      "first_use": 6,
      "first_write_index": 19,
      "id": "obs-0008",
   
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
"\nvoid __thiscall FUN_00e365a0(int param_1,undefined4 param_2)\n\n{\n  undefined8 uVar1;\n  \n  if (*(int *)(param_1 + 0xc) != 0) {\n    FUN_00808b20(param_2,*(undefined4 *)(param_1 + 0x10),0);\n    if (*(int *)(param_1 + 0x30) != 0 || *(int *)(param_1 + 0x34) != 0) {\n      uVar1 = FUN_0093a5e0();\n      if (((int)((ulonglong)uVar1 >> 0x20) != 0) || (*(uint *)(param_1 + 0x4c) < (uint)uVar1)) {\n        FUN_00810590(1);\n        *(undefined4 *)(param_1 + 0x30) = 0;\n        *(undefined4 *)(param_1 + 0x34) = 0;\n        *(undefined4 *)(param_1 + 0x38) = 0;\n        *(undefined4 *)(param_1 + 0x3c) = 0;\n        return;\n      }\n    }\n    FUN_00571e80();\n  }\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 43,
  "instructions": [
    {
      "address": "00e365a0",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00e365a1",
      "instruction": "MOV EDI,ECX"
    },
    {
      "address": "00e365a3",
      "instruction": "CMP dword ptr [EDI + 0xc],0x0"
    },
    {
      "address": "00e365a7",
      "instruction": "JZ 0x00e36614"
    },
    {
      "address": "00e365a9",
      "instruction": "MOV EAX,dword ptr [EDI + 0x10]"
    },
    {
      "address": "00e365ac",
      "instruction": "MOV ECX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "00e365b0",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00e365b1",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00e365b2",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00e365b4",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00e365b5",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00e365b6",
      "instruction": "CALL 0x00808b20"
    },
    {
      "address": "00e365bb",
      "instruction": "MOV EDX,dword ptr [EDI + 0x30]"
    },
    {
      "address": "00e365be",
      "instruction": "LEA ESI,[EDI + 0x30]"
    },
    {
      "address": "00e365c1",
      "instruction": "ADD ESP,0xc"
    },
    {
      "address": "00e365c4",
      "instruction": "OR EDX,dword ptr [ESI + 0x4]"
    },
    {
      "address": "00e365c7",
      "instruction": "JZ 0x00e3660a"
    },
    {
      "address": "00e365c9",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00e365cb",
      "instruction": "CALL 0x0093a5e0"
    },
    {
      "address": "00e365d0",
      "instruction": "MOV EBX,dword ptr [EDI + 0x4c]"
    },
    {
      "address": "00e365d3",
      "instruction": "XOR ECX,ECX"
    },
    {
      "address": "00e365d5",
      "instruction": "CMP EDX,ECX"
    },
    {
      "address": "00e365d7",
      "instruction": "JC 0x00e3660a"
    },
    {
      "address": "00e365d9",
      "instruction": "JA 0x00e365df"
    },
    {
      "address": "00e365db",
      "instruction": "CMP EAX,EBX"
    },
    {
      "address": "00e365dd",
      "instruction": "JBE 0x00e3660a"
    },
    {
      "address": "00e365df",
      "instruction": "MOV ECX,dword ptr [EDI + 0xc]"
    },
    {
      "address": "00e365e2",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "00e365e4",
      "instruction": "CALL 0x00810590"
    },
    {
      "address": "00e365e9",
      "instruction": "MOV dword ptr [ESI],0x0"
    },
    {
      "address": "00e365ef",
      "instruction": "MOV dword ptr [ESI + 0x4],0x0"
    },
    {
      "address": "00e365f6",
      "instruction": "MOV dword ptr [ESI + 0x8],0x0"
    },
    {
      "address": "00e365fd",
      "instruction": "MOV dword ptr [ESI + 0xc],0x0"
    },
    {
      "address": "00e36604",
      "instruction": "POP ESI"
    },
    {
      "address": "00e36605",
      "instruction": "POP EBX"
    },
    {
      "address": "00e36606",
      "instruction": "POP EDI"
    },
    {
      "address": "00e36607",
      "instruction": "RET 0x4"
    },
    {
      "address": "00e3660a",
      "instruction": "LEA ECX,[EDI + 0x18]"
    },
    {
      "address": "00e3660d",
      "instruction": "CALL 0x00571e80"
    },
    {
      "address": "00e36612",
      "instruction": "POP ESI"
    },
    {
      "address": "00e36613",
      "instruction": "POP EBX"
    },
    {
      "address": "00e36614",
      "instruction": "POP EDI"
    },
    {
      "address": "00e36615",
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
  "body_end": "00e36617",
  "body_span_bytes": 120,
  "body_start": "00e365a0",
  "callees": [
    "FUN_0093a5e0",
    "FUN_00571e80",
    "FUN_00808b20",
    "FUN_00810590"
  ],
  "callers": [
    "FUN_01063a10",
    "FUN_0107b260",
    "FUN_01067c50",
    "FUN_010759c0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00e365a0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "param_2",
      "storage": "Stack[0x4]:4",
      "type": "undefined4"
    },
    {
      "name": "uVar1",
      "storage": "VARIABLE:00000000:8",
      "type": "undefined8"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int"
    }
  ],
  "locals_count": 3,
  "mode": "live",
  "name": "FUN_00e365a0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xa365a0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00e365a0(void)",
  "size_bytes": 120,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00e365a0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 4,
  "xrefs": [
    {
      "from": "01067e44"
    },
    {
      "from": "01063d86"
    },
    {
      "from": "01075d89"
    },
    {
      "from": "0107b68a"
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
