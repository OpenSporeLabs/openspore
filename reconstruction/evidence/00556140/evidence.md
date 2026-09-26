# Evidence 0x00556140

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `4f891b2f303a2fbfdb578501e5eddbc5e2140d3e854df61703a2e90c649ce44e`

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
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "pointer_like_in_EAX",
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
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
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
  "content_sha256": "2a05c0e854fd395d5ed45548b29e246f6f0f66e07108336b2b73eda4b45c32a8",
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
    "indirect_calls": 2,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0052"
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
        "obs-0007",
        "obs-0010",
        "obs-0013",
        "obs-0043"
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
        "obs-0010",
        "obs-0011",
        "obs-0012",
        "obs-0021",
        "obs-0028",
        "obs-0031",
        "obs-0032",
        "obs-0037",
        "obs-0038",
        "obs-0047"
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
        "obs-0010",
        "obs-0011",
        "obs-0012",
        "obs-0021",
        "obs-0028",
        "obs-0031",
        "obs-0032",
        "obs-0037",
        "obs-0038",
        "obs-0047"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_reassigned_before_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0052"
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
        "obs-0052"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0052"
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
      "at": "0x00556140",
      "count": 35,
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
      "at": "0x00556140",
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
      "sub": 32
    },
    {
      "at": "0x00556141",
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
      "at": "0x00556141",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EBP,ESP",
      "reg": "EBP",
      "write_kind": "reg"
    },
    {
      "at": "0x00556143
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
"\nundefined4 FUN_00556140(int param_1,int param_2)\n\n{\n  int *piVar1;\n  int iVar2;\n  undefined4 uVar3;\n  int iVar4;\n  int *piVar5;\n  int *piVar6;\n  undefined4 local_10;\n  undefined4 local_8;\n  \n  local_8 = 0;\n  if ((*(int *)(param_1 + 4) == 0x2b978c46) || (*(int *)(param_1 + 4) == 0x3d97a8e4)) {\n    piVar1 = (int *)FUN_00555cf0(param_1);\n    uVar3 = local_8;\n    if (piVar1 != (int *)0x0) {\n      (**(code **)*piVar1)();\n      local_10 = 0;\n      piVar6 = piVar1;\n      iVar2 = FUN_00550a30();\n      for (; uVar3 = local_8, local_10 < iVar2; local_10 = local_10 + 1) {\n        piVar5 = piVar1;\n        uVar3 = FUN_00550a60(local_10);\n        iVar4 = FUN_00555dd0(uVar3,piVar5,piVar6);\n        if (iVar4 == param_2) break;\n      }\n    }\n    local_8 = uVar3;\n    if (piVar1 != (int *)0x0) {\n      (**(code **)(*piVar1 + 4))();\n    }\n  }\n  return local_8;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 67,
  "instructions": [
    {
      "address": "00556140",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00556141",
      "instruction": "MOV EBP,ESP"
    },
    {
      "address": "00556143",
      "instruction": "SUB ESP,0x20"
    },
    {
      "address": "00556146",
      "instruction": "MOV dword ptr [EBP + -0x4],0x0"
    },
    {
      "address": "0055614d",
      "instruction": "MOV EAX,dword ptr [EBP + 0x8]"
    },
    {
      "address": "00556150",
      "instruction": "CMP dword ptr [EAX + 0x4],0x2b978c46"
    },
    {
      "address": "00556157",
      "instruction": "JZ 0x00556169"
    },
    {
      "address": "00556159",
      "instruction": "MOV ECX,dword ptr [EBP + 0x8]"
    },
    {
      "address": "0055615c",
      "instruction": "CMP dword ptr [ECX + 0x4],0x3d97a8e4"
    },
    {
      "address": "00556163",
      "instruction": "JNZ 0x00556204"
    },
    {
      "address": "00556169",
      "instruction": "MOV EDX,dword ptr [EBP + 0x8]"
    },
    {
      "address": "0055616c",
      "instruction": "PUSH EDX"
    },
    {
      "address": "0055616d",
      "instruction": "CALL 0x00555cf0"
    },
    {
      "address": "00556172",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "00556175",
      "instruction": "MOV dword ptr [EBP + -0x18],EAX"
    },
    {
      "address": "00556178",
      "instruction": "MOV EAX,dword ptr [EBP + -0x18]"
    },
    {
      "address": "0055617b",
      "instruction": "MOV dword ptr [EBP + -0x8],EAX"
    },
    {
      "address": "0055617e",
      "instruction": "CMP dword ptr [EBP + -0x8],0x0"
    },
    {
      "address": "00556182",
      "instruction": "JZ 0x00556190"
    },
    {
      "address": "00556184",
      "instruction": "MOV ECX,dword ptr [EBP + -0x8]"
    },
    {
      "address": "00556187",
      "instruction": "MOV EDX,dword ptr [EBP + -0x8]"
    },
    {
      "address": "0055618a",
      "instruction": "MOV EAX,dword ptr [EDX]"
    },
    {
      "address": "0055618c",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "0055618e",
      "instruction": "CALL EDX"
    },
    {
      "address": "00556190",
      "instruction": "CMP dword ptr [EBP + -0x8],0x0"
    },
    {
      "address": "00556194",
      "instruction": "JZ 0x005561f1"
    },
    {
      "address": "00556196",
      "instruction": "MOV dword ptr [EBP + -0xc],0x0"
    },
    {
      "address": "0055619d",
      "instruction": "MOV EAX,dword ptr [EBP + -0x8]"
    },
    {
      "address": "005561a0",
      "instruction": "MOV dword ptr [EBP + -0x1c],EAX"
    },
    {
      "address": "005561a3",
      "instruction": "MOV ECX,dword ptr [EBP + -0x1c]"
    },
    {
      "address": "005561a6",
      "instruction": "CALL 0x00550a30"
    },
    {
      "address": "005561ab",
      "instruction": "MOV dword ptr [EBP + -0x10],EAX"
    },
    {
      "address": "005561ae",
      "instruction": "JMP 0x005561b9"
    },
    {
      "address": "005561b0",
      "instruction": "MOV ECX,dword ptr [EBP + -0xc]"
    },
    {
      "address": "005561b3",
      "instruction": "ADD ECX,0x1"
    },
    {
      "address": "005561b6",
      "instruction": "MOV dword ptr [EBP + -0xc],ECX"
    },
    {
      "address": "005561b9",
      "instruction": "MOV EDX,dword ptr [EBP + -0xc]"
    },
    {
      "address": "005561bc",
      "instruction": "CMP EDX,dword ptr [EBP + -0x10]"
    },
    {
      "address": "005561bf",
      "instruction": "JGE 0x005561f1"
    },
    {
      "address": "005561c1",
      "instruction": "MOV EAX,dword ptr [EBP + -0x8]"
    },
    {
      "address": "005561c4",
      "instruction": "MOV dword ptr [EBP + -0x20],EAX"
    },
    {
      "address": "005561c7",
      "instruction": "MOV ECX,dword ptr [EBP + -0xc]"
    },
    {
      "address": "005561ca",
      "instruction": "PUSH ECX"
    },
    {
      "address": "005561cb",
      "instruction": "MOV ECX,dword ptr [EBP + -0x20]"
    },
    {
      "address": "005561ce",
      "instruction": "CALL 0x00550a60"
    },
    {
      "address": "005561d3",
      "instruction": "MOV dword ptr [EBP + -0x14],EAX"
    },
    {
      "address": "005561d6",
      "instruction": "MOV EDX,dword ptr [EBP + -0x14]"
    },
    {
      "address": "005561d9",
      "instruction": "PUSH EDX"
    },
    {
      "address": "005561da",
      "instruction": "CALL 0x00555dd0"
    },
    {
      "address": "005561df",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "005561e2",
      "instruction": "CMP EAX,dword ptr [EBP + 0xc]"
    },
    {
      "address": "005561e5",
      "instruction": "JNZ 0x005561ef"
    },
    {
      "address": "005561e7",
      "instruction": "MOV EAX,dword ptr [EBP + -0x14]"
    },
    {
      "address": "005561ea",
      "instruction": "MOV dword ptr [EBP + -0x4],EAX"
    },
    {
      "address": "005561ed",
      "instruction": "JMP 0x005561f1"
    },
    {
      "address": "005561ef",
      "instruction": "JMP 0x005561b0"
    },
    {
      "address": "005561f1",
      "instruction": "CMP dword ptr [EBP + -0x8],0x0"
    },
    {
      "address": "005561f5",
      "instruction": "JZ 0x00556204"
    },
    {
      "address": "005561f7",
      "instruction": "MOV ECX,dword ptr [EBP + -0x8]"
    },
    {
      "address": "005561fa",
      "instruction": "MOV EDX,dword ptr [EBP + -0x8]"
    },
    {
      "address": "005561fd",
      "instruction": "MOV EAX,dword ptr [EDX]"
    },
    {
      "address": "005561ff",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "00556202",
      "instruction": "CALL EDX"
    },
    {
      "address": "00556204",
      "instruction": "MOV EAX,dword ptr [EBP + -0x4]"
    },
    {
      "address": "00556207",
      "instruction": "MOV ESP,EBP"
    },
    {
      "address": "00556209",
      "instruction": "POP EBP"
    },
    {
      "address": "0055620a",
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
  "body_end": "0055620a",
  "body_span_bytes": 203,
  "body_start": "00556140",
  "callees": [
    "FUN_00555cf0",
    "FUN_00550a30",
    "FUN_00550a60",
    "FUN_00555dd0"
  ],
  "callers": [
    "FUN_00f17b00",
    "FUN_00646370",
    "FUN_00deb930",
    "Editor_Save",
    "FUN_00642700",
    "FUN_004d15c0",
    "FUN_00f392b0",
    "FUN_0066d430"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00556140",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_8",
      "storage": "Stack[-0x8]:4",
      "type": "undefined4"
    },
    {
      "name": "local_10",
      "storage": "Stack[-0x10]:4",
      "type": "undefined4"
    },
    {
      "name": "piVar1",
      "storage": "register:00000000:4",
      "type": "int *"
    },
    {
      "name": "iVar2",
      "storage": "register:00000000:4",
      "type": "int"
    },
    {
      "name": "param_1",
      "storage": "Stack[0x4]:4",
      "type": "int"
    },
    {
      "name": "param_2",
      "storage": "Stack[0x8]:4",
      "type": "int"
    },
    {
      "name": "piVar5",
      "storage": "Stack[-0x24]:4",
      "type": "int *"
    },
    {
      "name": "piVar6",
      "storage": "Stack[-0x20]:4",
      "type": "int *"
    },
    {
      "name": "uVar3",
      "storage": "register:00000000:4",
      "type": "undefined4"
    },
    {
      "name": "iVar4",
      "storage": "register:00000000:4",
      "type": "int"
    }
  ],
  "locals_count": 10,
  "mode": "live",
  "name": "FUN_00556140",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x156140",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00556140(void)",
  "size_bytes": 203,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00556140",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 48,
  "xrefs": [
    {
      "from": "004d1f64"
    },
    {
      "from": "00577a41"
    },
    {
      "from": "00577a53"
    },
    {
      "from": "00577a68"
    },
    {
      "from": "00577a7a"
    },
    {
      "from": "00577a8f"
    },
    {
      "from": "00577aa1"
    },
    {
      "from": "00577ab6"
    },
    {
      "from": "00577ac8"
    },
    {
      "from": "00577add"
    },
    {
      "from": "00577af3"
    },
    {
      "from": "00f17b85"
    },
    {
      "from": "00f17b97"
    },
    {
      "from": "00f17ba6"
    },
    {
      "from": "00f17bb5"
    },
    {
      "from": "00f17bc4"
    },
    {
      "from": "0064690d"
    },
    {
      "from": "00646926"
    },
    {
      "from": "00646946"
    },
    {
      "from": "0064695f"
    },
    {
      "from": "0064697f"
    },
    {
      "from": "00646998"
    },
    {
      "from": "006469b8"
    },
    {
      "from": "006469d1"
    },
    {
      "from": "006469f1"
    },
    {
      "from": "00646a0a"
    },
    {
      "from": "00f39327"
    },
    {
      "from": "00f39339"
    },
    {
      "from": "00f39348"
    },
    {
      "from": "00f39357"
    },
    {
      "from": "00f39366"
    },
    {
      "from": "0066d5b7"
    },
    {
      "from": "0066d600"
    },
    {
      "from": "0066d611"
    },
    {
      "from": "0066d622"
    },
    {
      "from": "0066d633"
    },
    {
      "from": "0066d6bb"
    },
    {
      "from": "0066d713"
    },
    {
      "from": "0066d76b"
    },
    {
      "from": "00deba22"
    },
    {
      "from": "00deba3c"
    },
    {
      "from": "00deba56"
    },
    {
      "from": "00deba70"
    },
    {
      "from": "00642719"
    },
    {
      "from": "00642752"
    },
    {
      "from": "00642787"
    },
    {
      "from": "006427bc"
    },
    {
      "from": "006427f1"
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
