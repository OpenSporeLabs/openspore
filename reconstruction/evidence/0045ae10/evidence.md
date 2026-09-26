# Evidence 0x0045ae10

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `b873c56eb929bf7356e6fdd50e27b382eeb2dd7f0bb237237ed7b346e4189141`

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
        "ebp_offset": "EBP+0x8",
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
        "ebp_offset": "EBP+0xc",
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
    "ret_form": "RET 0x8",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
    "saved_registers": [
      "EBP"
    ],
    "stack_arguments": [
      {
        "ebp_offset": "EBP+0x8",
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
        "ebp_offset": "EBP+0xc",
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
    "stack_cleanup_bytes": 8,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x8"
  },
  "abstained_because": [
    "receiver_not_determinable: ecx_read_without_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_read_without_deref), and the convention rule that would apply discriminates on receiver absence"
  ],
  "cleanup": {
    "bytes": 8,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x8",
    "side": "callee"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "b1fef8ef9cb42184ed2c4c49dfddf6699cf4e7c811a67e887b9d01112a0a075a",
  "conventions": {
    "ambiguities": [
      "receiver_undetermined"
    ],
    "calling_convention": null,
    "candidate_conventions": [
      "__stdcall",
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
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0018"
      ],
      "claim": "the callee pops 8 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 8,
        "side": "callee"
      }
    },
    {
      "based_on": [
        "obs-0011",
        "obs-0013"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "INFERRED",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 2,
        "total_bytes": 8
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007",
        "obs-0008",
        "obs-0013",
        "obs-0014",
        "obs-0015"
      ],
      "claim": "the register receiver is undetermined: ecx_read_without_deref",
      "confidence": "UNKNOWN",
      "id": "R0",
      "value": {
        "reason": "ecx_read_without_deref",
        "register": null
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007",
        "obs-0008",
        "obs-0013",
        "obs-0014",
        "obs-0015"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_read_without_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
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
      "at": "0x0045ae10",
      "count": 7,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH EBP",
      "reg": "EBP"
    },
    {
      "and_esp": null,
      "at": "0x0045ae10",
      "ebp_is_general_register": true,
      "fp": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": true,
      "mov_ebp_esp_at": 1,
      "push_ebp": true,
      "push_ebp_at": 0,
      "raw": "PUSH EBP",
      "sub": 108
    },
    {
      "at": "0x0045ae11",
      "count": 1,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EBP,ESP",
      "reg": "ESP"
    },
    {
      "at": "0x0045ae11",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EBP,ESP",
      "reg": "EBP",
      "write_kind": "reg"
    },
    {
      "at": "0x0045ae13",
      "definite": true,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x6c",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x0045ae16",
      "count": 3,
      "first_use": 3,
      "first_write_index": 10,
      "id": "obs-0006",
      "index": 
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
"\nvoid __thiscall FUN_0045ae10(undefined4 param_1,undefined4 param_2,undefined4 param_3)\n\n{\n  undefined4 uVar1;\n  undefined4 uVar2;\n  \n  uVar2 = 0;\n  uVar1 = FUN_00434040(0,param_1);\n  FUN_0045ac20(param_2,param_3,uVar1,uVar2);\n  return;\n}\n\n"
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
      "address": "0045ae10",
      "instruction": "PUSH EBP"
    },
    {
      "address": "0045ae11",
      "instruction": "MOV EBP,ESP"
    },
    {
      "address": "0045ae13",
      "instruction": "SUB ESP,0x6c"
    },
    {
      "address": "0045ae16",
      "instruction": "MOV dword ptr [EBP + -0x6c],ECX"
    },
    {
      "address": "0045ae19",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "0045ae1b",
      "instruction": "LEA ECX,[EBP + -0x38]"
    },
    {
      "address": "0045ae1e",
      "instruction": "CALL 0x00434040"
    },
    {
      "address": "0045ae23",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0045ae24",
      "instruction": "MOV EAX,dword ptr [EBP + 0xc]"
    },
    {
      "address": "0045ae27",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0045ae28",
      "instruction": "MOV ECX,dword ptr [EBP + 0x8]"
    },
    {
      "address": "0045ae2b",
      "instruction": "PUSH ECX"
    },
    {
      "address": "0045ae2c",
      "instruction": "MOV ECX,dword ptr [EBP + -0x6c]"
    },
    {
      "address": "0045ae2f",
      "instruction": "CALL 0x0045ac20"
    },
    {
      "address": "0045ae34",
      "instruction": "MOV ESP,EBP"
    },
    {
      "address": "0045ae36",
      "instruction": "POP EBP"
    },
    {
      "address": "0045ae37",
      "instruction": "RET 0x8"
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
  "body_end": "0045ae39",
  "body_span_bytes": 42,
  "body_start": "0045ae10",
  "callees": [
    "FUN_00434040",
    "FUN_0045ac20"
  ],
  "callers": [
    "FUN_0064c0d0",
    "Editors::cEditor::HandleMessage",
    "FUN_00585d40",
    "Editors::cEditor::SetActiveMode",
    "FUN_00575f70",
    "FUN_005744b0",
    "FUN_005dec10",
    "Editors::cEditor::OnMouseDown",
    "FUN_00573f20",
    "FUN_0062f610",
    "FUN_0062f920",
    "FUN_0063ef70",
    "FUN_0062f5c0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "0045ae10",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "param_3",
      "storage": "Stack[0x8]:4",
      "type": "undefined4"
    },
    {
      "name": "uVar1",
      "storage": "register:00000000:4",
      "type": "undefined4"
    },
    {
      "name": "uVar2",
      "storage": "Stack[-0x74]:4",
      "type": "undefined4"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "undefined4"
    },
    {
      "name": "param_2",
      "storage": "Stack[0x4]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 5,
  "mode": "live",
  "name": "FUN_0045ae10",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x5ae10",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_0045ae10(void)",
  "size_bytes": 42,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x0045ae10",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 16,
  "xrefs": [
    {
      "from": "0057610c"
    },
    {
      "from": "00576125"
    },
    {
      "from": "00587314"
    },
    {
      "from": "00587803"
    },
    {
      "from": "0057450c"
    },
    {
      "from": "0057454e"
    },
    {
      "from": "0062f996"
    },
    {
      "from": "005863f5"
    },
    {
      "from": "0064c24e"
    },
    {
      "from": "0062f6a7"
    },
    {
      "from": "0062f5f8"
    },
    {
      "from": "0063efb1"
    },
    {
      "from": "00573f36"
    },
    {
      "from": "005ded54"
    },
    {
      "from": "005888f5"
    },
    {
      "from": "005934d5"
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
