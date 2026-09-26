# Evidence 0x00ba61b0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `ddb4efb71e400287032c52f0711a95de3acce2d04b0fb66732201cce45a0b6f3`

## abi

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "abi": {
    "architecture": "x86-32",
    "ordinary_stack_argument_slots": [
      "entry_ESP+0x4",
      "entry_ESP+0x8"
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
      },
      {
        "entry_offset": "entry_ESP+0x8",
        "observed": true,
        "ordinal": 2,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "ret_form": "RET",
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
      },
      {
        "entry_offset": "entry_ESP+0x8",
        "observed": true,
        "ordinal": 2,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +4, so the listing is not one path",
    "receiver_not_determinable: ecx_reassigned_before_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_reassigned_before_deref), and the convention rule that would apply discriminates on receiver absence"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate",
    "side": "caller"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "42fbea97fe8e16426d9bf2855b19961dc8aa63564fb041eb81d79bdf47f94c56",
  "conventions": {
    "ambiguities": [
      "receiver_undetermined"
    ],
    "calling_convention": null,
    "candidate_conventions": [
      "__cdecl",
      "__thiscall"
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
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0023"
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
        "obs-0009",
        "obs-0012"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 2,
        "total_bytes": 8
      }
    },
    {
      "based_on": [
        "obs-0003",
        "obs-0004",
        "obs-0015"
      ],
      "claim": "the register receiver is undetermined: ecx_reassigned_before_deref",
      "confidence": "UNKNOWN",
      "id": "R0",
      "value": {
        "reason": "ecx_reassigned_before_deref",
        "register": null
      }
    },
    {
      "based_on": [
        "obs-0003",
        "obs-0004",
        "obs-0015"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_reassigned_before_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0023"
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
        "obs-0023"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0023"
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
      "at": "0x00ba61c2",
      "id": "obs-0001",
      "index": 6,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00f473a0",
      "target": "0x00f473a0"
    },
    {
      "at": "0x00ba61c7",
      "definite": true,
      "id": "obs-0002",
      "index": 7,
      "kind": "REG_WRITE",
      "raw": "ADD ESP,0x18",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00ba61ce",
      "count": 9,
      "first_use": 10,
      "first_write_index": 13,
      "id": "obs-0003",
      "index": 10,
      "kind": "REG_READ",
      "raw": "MOV ECX,EAX",
      "reg": "EAX"
    },
    {
      "at": "0x00ba61ce",
      "definite": true,
      "id": "obs-0004",
      "index": 10,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,EAX",
      "reg": "ECX",
      "write_kind": "reg"
    },
    {
      "at": "0x00ba61d0",
      "id": "obs-0005",
      "index": 11,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00b8e180",
      "target": "0x00b8e180"
    },
    {
      "at": "0x00ba61d7",
      "definite": true,
      "id": "obs-0006",
      "index": 13,
      "kind": "REG_WRITE",
      "raw": "XOR EAX,EAX",
      "reg": "EAX",
      "write_kind": "zero"
    },
    {
      "at": "0x00ba61d9",
      "count": 6,
      "first_use": 14,
      "first_write_index": 15,
      "id": "obs-0007",
      "index": 14,
      "kind": "REG_READ",
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
"\nvoid FUN_00ba61b0(undefined4 param_1,int *param_2)\n\n{\n  int iVar1;\n  \n  iVar1 = FUN_00f473a0(0x1b0,\"Simulator/cPlanetRecord\",0,0,0,0);\n  if (iVar1 == 0) {\n    iVar1 = 0;\n  }\n  else {\n    iVar1 = FUN_00b8e180();\n  }\n  *param_2 = iVar1;\n  FUN_00b8da80(param_1);\n  iVar1 = *param_2;\n  *(undefined4 *)(iVar1 + 8) = param_1;\n  *(undefined4 *)(iVar1 + 0xc) = 0x5220cb8;\n  *(undefined4 *)(iVar1 + 0x10) = 1;\n  (*(code *)**(undefined4 **)*param_2)();\n  FUN_006ac040(1,*param_2);\n  FUN_006ad010(*param_2);\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 44,
  "instructions": [
    {
      "address": "00ba61b0",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00ba61b2",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00ba61b4",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00ba61b6",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00ba61b8",
      "instruction": "PUSH 0x1465ef0"
    },
    {
      "address": "00ba61bd",
      "instruction": "PUSH 0x1b0"
    },
    {
      "address": "00ba61c2",
      "instruction": "CALL 0x00f473a0"
    },
    {
      "address": "00ba61c7",
      "instruction": "ADD ESP,0x18"
    },
    {
      "address": "00ba61ca",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00ba61cc",
      "instruction": "JZ 0x00ba61d7"
    },
    {
      "address": "00ba61ce",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00ba61d0",
      "instruction": "CALL 0x00b8e180"
    },
    {
      "address": "00ba61d5",
      "instruction": "JMP 0x00ba61d9"
    },
    {
      "address": "00ba61d7",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "00ba61d9",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00ba61da",
      "instruction": "MOV ESI,dword ptr [ESP + 0xc]"
    },
    {
      "address": "00ba61de",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00ba61df",
      "instruction": "MOV EDI,dword ptr [ESP + 0xc]"
    },
    {
      "address": "00ba61e3",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00ba61e4",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00ba61e6",
      "instruction": "MOV dword ptr [ESI],EAX"
    },
    {
      "address": "00ba61e8",
      "instruction": "CALL 0x00b8da80"
    },
    {
      "address": "00ba61ed",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "00ba61ef",
      "instruction": "ADD EAX,0x8"
    },
    {
      "address": "00ba61f2",
      "instruction": "MOV dword ptr [EAX],EDI"
    },
    {
      "address": "00ba61f4",
      "instruction": "MOV ECX,0x5220cb8"
    },
    {
      "address": "00ba61f9",
      "instruction": "MOV dword ptr [EAX + 0x4],ECX"
    },
    {
      "address": "00ba61fc",
      "instruction": "MOV EDX,0x1"
    },
    {
      "address": "00ba6201",
      "instruction": "MOV dword ptr [EAX + 0x8],EDX"
    },
    {
      "address": "00ba6204",
      "instruction": "MOV ECX,dword ptr [ESI]"
    },
    {
      "address": "00ba6206",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "00ba6208",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00ba620a",
      "instruction": "CALL EDX"
    },
    {
      "address": "00ba620c",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "00ba620e",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00ba620f",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "00ba6211",
      "instruction": "CALL 0x006ac040"
    },
    {
      "address": "00ba6216",
      "instruction": "MOV ECX,dword ptr [ESI]"
    },
    {
      "address": "00ba6218",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00ba6219",
      "instruction": "CALL 0x006ad010"
    },
    {
      "address": "00ba621e",
      "instruction": "ADD ESP,0xc"
    },
    {
      "address": "00ba6221",
      "instruction": "POP EDI"
    },
    {
      "address": "00ba6222",
      "instruction": "POP ESI"
    },
    {
      "address": "00ba6223",
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
  "body_end": "00ba6223",
  "body_span_bytes": 116,
  "body_start": "00ba61b0",
  "callees": [
    "FUN_00f473a0",
    "FUN_00b8da80",
    "FUN_00b8e180",
    "FUN_006ac040",
    "FUN_006ad010"
  ],
  "callers": [
    "FUN_00bae9b0",
    "FUN_00bb2a50",
    "FUN_00bb28c0",
    "FUN_00bb4100",
    "FUN_00ba8830",
    "FUN_00bae6f0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00ba61b0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "param_1",
      "storage": "Stack[0x4]:4",
      "type": "undefined4"
    },
    {
      "name": "param_2",
      "storage": "Stack[0x8]:4",
      "type": "int *"
    },
    {
      "name": "iVar1",
      "storage": "register:00000000:4",
      "type": "int"
    }
  ],
  "locals_count": 3,
  "mode": "live",
  "name": "FUN_00ba61b0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x7a61b0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00ba61b0(void)",
  "size_bytes": 116,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00ba61b0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 24,
  "xrefs": [
    {
      "from": "00ba8899"
    },
    {
      "from": "00ba89b9"
    },
    {
      "from": "00ba8a5d"
    },
    {
      "from": "00ba8b0b"
    },
    {
      "from": "00ba8ba7"
    },
    {
      "from": "00baea55"
    },
    {
      "from": "00baeb21"
    },
    {
      "from": "00baebf9"
    },
    {
      "from": "00bae8c3"
    },
    {
      "from": "00bb29c2"
    },
    {
      "from": "00bb2bef"
    },
    {
      "from": "00bb2d18"
    },
    {
      "from": "00bb2e45"
    },
    {
      "from": "00bb2f67"
    },
    {
      "from": "00bb3087"
    },
    {
      "from": "00bb31a4"
    },
    {
      "from": "00bb3218"
    },
    {
      "from": "00bb32e2"
    },
    {
      "from": "00bb33ac"
    },
    {
      "from": "00bb3480"
    },
    {
      "from": "00bb354a"
    },
    {
      "from": "00bb3613"
    },
    {
      "from": "00bb44eb"
    },
    {
      "from": "00bb4893"
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
