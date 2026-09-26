# Evidence 0x00baf630

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `8e7ede38b5a9e115f894b923a90267cff31cccd84e68acb7b0367f76f3c5dbca`

## abi

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "abi": {
    "architecture": "x86-32",
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
    "ret_form": "RET 0x8",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
    "saved_registers": [
      "EBP",
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
    "stack_cleanup_bytes": 8,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x8"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +16, so the listing is not one path",
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
  "content_sha256": "d6c8db4f084f54c8a4b2afa713d4f47a72f11edcedbffa472ef326d81af57854",
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
    "indirect_calls": 2,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0038",
        "obs-0045"
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
        "obs-0010",
        "obs-0011",
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
        "obs-0010",
        "obs-0011",
        "obs-0014",
        "obs-0015"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_read_without_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0038",
        "obs-0045"
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
        "obs-0038",
        "obs-0045"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0038",
        "obs-0045"
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
      "and_esp": null,
      "at": "0x00baf630",
      "ebp_is_general_register": false,
      "fp": false,
      "id": "obs-0001",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": true,
      "push_ebp_at": 2,
      "raw": "SUB ESP,0x8",
      "sub": 8
    },
    {
      "at": "0x00baf630",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x8",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00baf633",
      "count": 5,
      "first_use": 1,
      "first_write_index": 20,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00baf634",
      "count": 3,
      "first_use": 2,
      "first_write_index": 3,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH EBP",
      "reg": "EBP"
    },
    {
      "at": "0x00baf635",
      "count": 8,
      "first_use": 3,
      "first_write_index": 0,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV EBP,dword ptr [ESP + 0x14]",
      "reg": "ESP"
    },
    {
      "at": "0x00baf635",
      "base": "ESP",
      "disp": 20,
      "id": "obs-0006",
      "index": 3,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EBP,dword ptr [ESP + 0x14]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00baf635",
      "definite": true,
      "id": "obs-0007",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV EBP,dword ptr [ESP + 0x14]",
      "reg": "EBP",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00baf639",
      "count": 8,
      "first_use": 4,
      "first_write_index": 6,
      "id"
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
"\nvoid __thiscall FUN_00baf630(int param_1,undefined4 param_2,int *param_3)\n\n{\n  int *piVar1;\n  undefined4 uVar2;\n  int *piVar3;\n  undefined4 uVar4;\n  int *piVar5;\n  undefined4 local_8;\n  int local_4;\n  \n  uVar2 = param_2;\n  local_8 = param_2;\n  map_int_whatever_find(&local_4,&local_8);\n  piVar3 = param_3;\n  if ((local_4 != param_1 + 0x130) && (*(int *)(local_4 + 0x14) != 0)) {\n    FUN_00bb9b00(4,0);\n    if (piVar3 == (int *)0x0) goto LAB_00baf6db;\n    uVar4 = FUN_00bb9b80();\n    FUN_00bb9b90(uVar4);\n  }\n  if (piVar3 != (int *)0x0) {\n    FUN_00bb9b00(4,1);\n    FUN_00a16a90(uVar2);\n    piVar5 = (int *)FUN_00dd85c0(&param_2);\n    piVar1 = (int *)*piVar5;\n    if (piVar3 == piVar1) {\n      return;\n    }\n    (**(code **)*piVar3)();\n    *piVar5 = (int)piVar3;\n    if (piVar1 == (int *)0x0) {\n      return;\n    }\n    (**(code **)(*piVar1 + 4))();\n    return;\n  }\nLAB_00baf6db:\n  FUN_00baa110(&param_2);\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 78,
  "instructions": [
    {
      "address": "00baf630",
      "instruction": "SUB ESP,0x8"
    },
    {
      "address": "00baf633",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00baf634",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00baf635",
      "instruction": "MOV EBP,dword ptr [ESP + 0x14]"
    },
    {
      "address": "00baf639",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00baf63a",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00baf63b",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00baf63d",
      "instruction": "LEA EAX,[ESP + 0x10]"
    },
    {
      "address": "00baf641",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00baf642",
      "instruction": "LEA ECX,[ESP + 0x18]"
    },
    {
      "address": "00baf646",
      "instruction": "LEA EDI,[ESI + 0x12c]"
    },
    {
      "address": "00baf64c",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00baf64d",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00baf64f",
      "instruction": "MOV dword ptr [ESP + 0x18],EBP"
    },
    {
      "address": "00baf653",
      "instruction": "CALL 0x00e5c780"
    },
    {
      "address": "00baf658",
      "instruction": "MOV EAX,dword ptr [ESP + 0x14]"
    },
    {
      "address": "00baf65c",
      "instruction": "ADD ESI,0x130"
    },
    {
      "address": "00baf662",
      "instruction": "CMP EAX,ESI"
    },
    {
      "address": "00baf664",
      "instruction": "MOV ESI,dword ptr [ESP + 0x20]"
    },
    {
      "address": "00baf668",
      "instruction": "JZ 0x00baf68f"
    },
    {
      "address": "00baf66a",
      "instruction": "MOV EBX,dword ptr [EAX + 0x14]"
    },
    {
      "address": "00baf66d",
      "instruction": "TEST EBX,EBX"
    },
    {
      "address": "00baf66f",
      "instruction": "JZ 0x00baf68f"
    },
    {
      "address": "00baf671",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00baf673",
      "instruction": "PUSH 0x4"
    },
    {
      "address": "00baf675",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "00baf677",
      "instruction": "CALL 0x00bb9b00"
    },
    {
      "address": "00baf67c",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "00baf67e",
      "instruction": "JZ 0x00baf6db"
    },
    {
      "address": "00baf680",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "00baf682",
      "instruction": "CALL 0x00bb9b80"
    },
    {
      "address": "00baf687",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00baf688",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00baf68a",
      "instruction": "CALL 0x00bb9b90"
    },
    {
      "address": "00baf68f",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "00baf691",
      "instruction": "JZ 0x00baf6db"
    },
    {
      "address": "00baf693",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "00baf695",
      "instruction": "PUSH 0x4"
    },
    {
      "address": "00baf697",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00baf699",
      "instruction": "CALL 0x00bb9b00"
    },
    {
      "address": "00baf69e",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00baf69f",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00baf6a1",
      "instruction": "CALL 0x00a16a90"
    },
    {
      "address": "00baf6a6",
      "instruction": "LEA EDX,[ESP + 0x1c]"
    },
    {
      "address": "00baf6aa",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00baf6ab",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00baf6ad",
      "instruction": "CALL 0x00dd85c0"
    },
    {
      "address": "00baf6b2",
      "instruction": "MOV EBX,EAX"
    },
    {
      "address": "00baf6b4",
      "instruction": "MOV EDI,dword ptr [EBX]"
    },
    {
      "address": "00baf6b6",
      "instruction": "CMP ESI,EDI"
    },
    {
      "address": "00baf6b8",
      "instruction": "JZ 0x00baf6e7"
    },
    {
      "address": "00baf6ba",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "00baf6bc",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00baf6be",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00baf6c0",
      "instruction": "CALL EDX"
    },
    {
      "address": "00baf6c2",
      "instruction": "MOV dword ptr [EBX],ESI"
    },
    {
      "address": "00baf6c4",
      "instruction": "TEST EDI,EDI"
    },
    {
      "address": "00baf6c6",
      "instruction": "JZ 0x00baf6e7"
    },
    {
      "address": "00baf6c8",
      "instruction": "MOV EAX,dword ptr [EDI]"
    },
    {
      "address": "00baf6ca",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "00baf6cd",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00baf6cf",
      "instruction": "CALL EDX"
    },
    {
      "address": "00baf6d1",
      "instruction": "POP EDI"
    },
    {
      "address": "00baf6d2",
      "instruction": "POP ESI"
    },
    {
      "address": "00baf6d3",
      "instruction": "POP EBP"
    },
    {
      "address": "00baf6d4",
      "instruction": "POP EBX"
    },
    {
      "address": "00baf6d5",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "00baf6d8",
      "instruction": "RET 0x8"
    },
    {
      "address": "00baf6db",
      "instruction": "LEA EAX,[ESP + 0x1c]"
    },
    {
      "address": "00baf6df",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00baf6e0",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00baf6e2",
      "instruction": "CALL 0x00baa110"
    },
    {
      "address": "00baf6e7",
      "instruction": "POP EDI"
    },
    {
      "address": "00baf6e8",
      "instruction": "POP ESI"
    },
    {
      "address": "00baf6e9",
      "instruction": "POP EBP"
    },
[TRUNCATED]
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
  "body_end": "00baf6f0",
  "body_span_bytes": 193,
  "body_start": "00baf630",
  "callees": [
    "FUN_00dd85c0",
    "map_int_whatever_find",
    "FUN_00a16a90",
    "FUN_00baa110",
    "FUN_00bb9b90",
    "FUN_00bb9b00",
    "FUN_00bb9b80"
  ],
  "callers": [
    "FUN_00bb1340",
    "FUN_00c34ee0",
    "FUN_00c35810",
    "FUN_00bb2610",
    "FUN_00c30c10",
    "FUN_00c316c0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00baf630",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "piVar5",
      "storage": "register:00000000:4",
      "type": "int *"
    },
    {
      "name": "uVar4",
      "storage": "register:00000000:4",
      "type": "undefined4"
    },
    {
      "name": "local_8",
      "storage": "Stack[-0x8]:4",
      "type": "undefined4"
    },
    {
      "name": "piVar1",
      "storage": "unique:00017200:4",
      "type": "int *"
    },
    {
      "name": "param_3",
      "storage": "Stack[0x8]:4",
      "type": "int *"
    },
    {
      "name": "piVar3",
      "storage": "unique:100000bb:4",
      "type": "int *"
    },
    {
      "name": "uVar2",
      "storage": "unique:100000b7:4",
      "type": "undefined4"
    },
    {
      "name": "param_2",
      "storage": "Stack[0x4]:4",
      "type": "undefined4"
    },
    {
      "name": "local_4",
      "storage": "Stack[-0x4]:4",
      "type": "int"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int"
    }
  ],
  "locals_count": 10,
  "mode": "live",
  "name": "FUN_00baf630",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x7af630",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00baf630(void)",
  "size_bytes": 193,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00baf630",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 6,
  "xrefs": [
    {
      "from": "00bb13ee"
    },
    {
      "from": "00bb2752"
    },
    {
      "from": "00c30c35"
    },
    {
      "from": "00c3170c"
    },
    {
      "from": "00c358ff"
    },
    {
      "from": "00c351e5"
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
