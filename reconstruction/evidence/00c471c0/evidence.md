# Evidence 0x00c471c0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `03f8a16085afde8f59f9d49c0569f01a9f1723da156e10cca6d22dea57c7803c`

## abi

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "abi": {
    "architecture": "x86-32",
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
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
    "saved_registers": [
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
    ]
  },
  "abstained_because": [
    "no_terminal_ret: the only exit observed is a tail jump"
  ],
  "cleanup": {
    "bytes": null,
    "confidence": "UNKNOWN",
    "corroboration": "not_available",
    "evidence": null,
    "side": null
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "157fc9ebbc985abe46df9ca297e338433271ee7e1259ebe481b952a0c86db9ee",
  "conventions": {
    "ambiguities": [
      "tail_call"
    ],
    "calling_convention": null,
    "candidate_conventions": [
      "__cdecl",
      "__stdcall",
      "__thiscall",
      "__fastcall"
    ],
    "confidence": "UNKNOWN",
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
    "indirect_calls": 4,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0022"
      ],
      "claim": "no terminal return is present in the listing",
      "confidence": "UNKNOWN",
      "id": "C2"
    },
    {
      "based_on": [
        "obs-0018"
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
        "obs-0001",
        "obs-0003",
        "obs-0009"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          0,
          304
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0022"
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
        "obs-0022"
      ],
      "claim": "this listing is a tail transfer: it inherits its caller's frame and never runs its own RET",
      "confidence": "UNKNOWN",
      "id": "T1",
      "value": {
        "form": "jmp"
      }
    }
  ],
  "observations": [
    {
      "at": "0x00c471c0",
      "count": 3,
      "first_use": 0,
      "first_write_index": 10,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00c471c1",
      "count": 9,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00c471c2",
      "definite": true,
      "id": "obs-0003",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00c471c4",
      "definite": true,
      "id": "obs-0004",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESI]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00c471c6",
      "count": 6,
      "first_use": 4,
      "first_write_index": 3,
      "id": "obs-0005",
      "index": 4,
      "kind": "REG_READ",
      "raw": "MOV EDX,dword ptr [EAX + 0xf8]",
      "reg": "EAX"
    },
    {
      "at": "0x00c471c6",
      "definite": true,
      "id": "obs-0006",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [EAX + 0xf8]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00c471cc",
      "count": 5,
      "first_use": 5,
      "first_write_index": 4,
      "id": "obs-0007",
      "index": 5,
      "kind": "REG_READ",
      "raw": "CALL EDX",
      "reg": "EDX"
    },
    {
      "at": "0x00c471cc",
      "base": "EDX",
      "disp": null,
      "id": "obs-0008",
      "index": 5,
      "kind": "CALL_INDIRECT",
      "raw": "CALL EDX",
      "via": "register"
    },
    {
      "at": "0x00c471da",
      "definite": true,
      "id": "obs-0009",
      "index": 10,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,ESI",
      "reg": "ECX",
      "write_kind": "reg"
    },
    {
      "at": "0x00c471dc",
      "base": "EDX",
      "disp": null,
      "id": "obs-0010",
      "index": 11,
      "kind": "CALL_INDIRECT",
      "raw": "CALL EDX",
      "via": "register"
    },
    {
      "at": "0x00c471ec",
      "count": 2,
      "first_use": 17,
      "first_write_index": 29,
      "id": "obs-0011",
      "index": 17,
      "kind": "REG_READ",
      "raw": "MOV byte ptr [ESP + 0x4],AL",
      "reg": "ESP"
    },
    {
      "at": "0x00c471ec",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0012",
      "index": 17,
      "key": null,
      "kind": "STACK_SLOT_WRITE",
      "raw": "MOV byte ptr [ESP + 0x4],AL",
      "reason": "local",
      "resolved": false,
      "size": 1,
      "via": "direct"
    },
    {
      "at": "0x00c47203",
      "base": "EAX",
      "
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
"\nvoid __fastcall FUN_00c471c0(int *param_1)\n\n{\n  char cVar1;\n  char cVar2;\n  \n  cVar1 = (**(code **)(*param_1 + 0xf8))();\n  if (cVar1 == '\\0') {\n    cVar2 = (**(code **)(*param_1 + 0xfc))();\n    cVar1 = '\\0';\n    if (cVar2 == '\\0') goto LAB_00c471e4;\n  }\n  cVar1 = '\\x01';\nLAB_00c471e4:\n  if ((((uint)param_1[0x4c] >> 1 & 1) != 0) && (cVar1 == '\\0')) {\n    (**(code **)(*param_1 + 0x19c))();\n    FUN_01046fc0();\n    FUN_01048ce0();\n    return;\n  }\n  (**(code **)(*param_1 + 0x198))(cVar1);\n  FUN_01046fc0();\n  FUN_01048ce0();\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 42,
  "instructions": [
    {
      "address": "00c471c0",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00c471c1",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00c471c2",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00c471c4",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "00c471c6",
      "instruction": "MOV EDX,dword ptr [EAX + 0xf8]"
    },
    {
      "address": "00c471cc",
      "instruction": "CALL EDX"
    },
    {
      "address": "00c471ce",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00c471d0",
      "instruction": "JNZ 0x00c471e2"
    },
    {
      "address": "00c471d2",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "00c471d4",
      "instruction": "MOV EDX,dword ptr [EAX + 0xfc]"
    },
    {
      "address": "00c471da",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00c471dc",
      "instruction": "CALL EDX"
    },
    {
      "address": "00c471de",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00c471e0",
      "instruction": "JZ 0x00c471e4"
    },
    {
      "address": "00c471e2",
      "instruction": "MOV AL,0x1"
    },
    {
      "address": "00c471e4",
      "instruction": "MOV ECX,dword ptr [ESI + 0x130]"
    },
    {
      "address": "00c471ea",
      "instruction": "SHR ECX,0x1"
    },
    {
      "address": "00c471ec",
      "instruction": "MOV byte ptr [ESP + 0x4],AL"
    },
    {
      "address": "00c471f0",
      "instruction": "TEST CL,0x1"
    },
    {
      "address": "00c471f3",
      "instruction": "JZ 0x00c47215"
    },
    {
      "address": "00c471f5",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00c471f7",
      "instruction": "JNZ 0x00c47215"
    },
    {
      "address": "00c471f9",
      "instruction": "MOV EDX,dword ptr [ESI]"
    },
    {
      "address": "00c471fb",
      "instruction": "MOV EAX,dword ptr [EDX + 0x19c]"
    },
    {
      "address": "00c47201",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00c47203",
      "instruction": "CALL EAX"
    },
    {
      "address": "00c47205",
      "instruction": "CALL 0x01046fc0"
    },
    {
      "address": "00c4720a",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00c4720c",
      "instruction": "POP ESI"
    },
    {
      "address": "00c4720d",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "00c47210",
      "instruction": "JMP 0x01048ce0"
    },
    {
      "address": "00c47215",
      "instruction": "MOV EDX,dword ptr [ESI]"
    },
    {
      "address": "00c47217",
      "instruction": "MOV EAX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "00c4721b",
      "instruction": "MOV EDX,dword ptr [EDX + 0x198]"
    },
    {
      "address": "00c47221",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00c47222",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00c47224",
      "instruction": "CALL EDX"
    },
    {
      "address": "00c47226",
      "instruction": "CALL 0x01046fc0"
    },
    {
      "address": "00c4722b",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00c4722d",
      "instruction": "POP ESI"
    },
    {
      "address": "00c4722e",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "00c47231",
      "instruction": "JMP 0x01048ce0"
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
  "body_end": "00c47235",
  "body_span_bytes": 118,
  "body_start": "00c471c0",
  "callees": [
    "FUN_01046fc0",
    "FUN_01048ce0"
  ],
  "callers": [
    "FUN_00c4f160",
    "FUN_00c5f360",
    "FUN_00c51ac0",
    "FUN_00c55500",
    "FUN_00c52ea0",
    "FUN_00c61570",
    "FUN_00c63330",
    "FUN_00c4b760",
    "FUN_00c63130",
    "FUN_00c62100",
    "FUN_00c4e230",
    "FUN_00c631b0",
    "FUN_00c4db40",
    "FUN_00c52e30",
    "FUN_00c51e40",
    "FUN_00c47240",
    "FUN_00c50460",
    "FUN_00c63170",
    "FUN_00c5f280"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00c471c0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "cVar1",
      "storage": "register:00000000:1",
      "type": "char"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int *"
    },
    {
      "name": "cVar2",
      "storage": "register:00000000:1",
      "type": "char"
    }
  ],
  "locals_count": 3,
  "mode": "live",
  "name": "FUN_00c471c0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x8471c0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00c471c0(void)",
  "size_bytes": 118,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00c471c0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 22,
  "xrefs": [
    {
      "from": "00c4f19a"
    },
    {
      "from": "00c51af6"
    },
    {
      "from": "00c51e7d"
    },
    {
      "from": "00c62136"
    },
    {
      "from": "00c4b797"
    },
    {
      "from": "00c472ab"
    },
    {
      "from": "00c4db7e"
    },
    {
      "from": "00c4e26e"
    },
    {
      "from": "00c50495"
    },
    {
      "from": "00c52e8d"
    },
    {
      "from": "00c52f0c"
    },
    {
      "from": "00c55537"
    },
    {
      "from": "00c5f2b7"
    },
    {
      "from": "00c5f3a5"
    },
    {
      "from": "00c615b9"
    },
    {
      "from": "00c63167"
    },
    {
      "from": "00c631a7"
    },
    {
      "from": "00c631e7"
    },
    {
      "from": "00c6336e"
    },
    {
      "from": "00c5326b"
    },
    {
      "from": "00c5ea11"
    },
    {
      "from": "00c62862"
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
