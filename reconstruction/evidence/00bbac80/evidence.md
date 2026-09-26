# Evidence 0x00bbac80

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `c68511930727af24a754930d00dd72423078b1c2947a8cb30aed35722fe734d3`

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
    "ret_form": "RET 0x8",
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
    "stack_cleanup_bytes": 8,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x8"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +16, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 8,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x8",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "5acaf70cc02975eaf31956453d47cc56ec25f0e809d7164af4e01cd2d505859c",
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
        "obs-0024"
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
        "obs-0005"
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
        "obs-0008",
        "obs-0009",
        "obs-0014",
        "obs-0015"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          88,
          92,
          132,
          172
        ],
        "register": "ECX",
        "written_through": 1
      }
    },
    {
      "based_on": [
        "obs-0008",
        "obs-0009",
        "obs-0014",
        "obs-0015",
        "obs-0024"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0024"
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
        "obs-0024"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0024"
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
      "at": "0x00bbac80",
      "ebp_is_general_register": false,
      "fp": false,
      "id": "obs-0001",
      "index": 0,
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
      "at": "0x00bbac80",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0xc",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00bbac83",
      "count": 3,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00bbac84",
      "count": 2,
      "first_use": 2,
      "first_write_index": 0,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV EBX,dword ptr [ESP + 0x14]",
      "reg": "ESP"
    },
    {
      "at": "0x00bbac84",
      "base": "ESP",
      "disp": 20,
      "id": "obs-0005",
      "index": 2,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EBX,dword ptr [ESP + 0x14]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00bbac84",
      "definite": true,
      "id": "obs-0006",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV EBX,dword ptr [ESP + 0x14]",
      "reg": "EBX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00bbac88",
      "count": 6,
      "first_use": 3,
      "first_write_index": 4,
      "id": "obs-0007",
      "index": 3,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00bbac89",
      "count": 2,
      "first_use": 4,
      "first_write_index": 15,
      "id": "obs-0008",
      "index": 4,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX"
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
"\nvoid __thiscall FUN_00bbac80(int param_1,int param_2)\n\n{\n  undefined4 uVar1;\n  undefined1 *puVar2;\n  int iVar3;\n  undefined4 uVar4;\n  undefined1 local_c [12];\n  \n  if (param_2 != *(int *)(param_1 + 0x58)) {\n    if ((*(char *)(param_1 + 0xac) != '\\0') && ((*(uint *)(param_1 + 0x5c) >> 0xf & 1) == 0)) {\n      FUN_00bba640();\n      uVar4 = 1;\n      puVar2 = local_c;\n      iVar3 = param_2;\n      FUN_00b3d2a0(puVar2,param_2,1);\n      uVar1 = FUN_00ba8010(puVar2,iVar3);\n      FUN_00b8dde0(uVar1,uVar4);\n    }\n    *(int *)(param_1 + 0x58) = param_2;\n  }\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 33,
  "instructions": [
    {
      "address": "00bbac80",
      "instruction": "SUB ESP,0xc"
    },
    {
      "address": "00bbac83",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00bbac84",
      "instruction": "MOV EBX,dword ptr [ESP + 0x14]"
    },
    {
      "address": "00bbac88",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00bbac89",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00bbac8b",
      "instruction": "CMP EBX,dword ptr [ESI + 0x58]"
    },
    {
      "address": "00bbac8e",
      "instruction": "JZ 0x00bbacd1"
    },
    {
      "address": "00bbac90",
      "instruction": "CMP byte ptr [ESI + 0xac],0x0"
    },
    {
      "address": "00bbac97",
      "instruction": "JZ 0x00bbacce"
    },
    {
      "address": "00bbac99",
      "instruction": "MOV EAX,dword ptr [ESI + 0x5c]"
    },
    {
      "address": "00bbac9c",
      "instruction": "SHR EAX,0xf"
    },
    {
      "address": "00bbac9f",
      "instruction": "TEST AL,0x1"
    },
    {
      "address": "00bbaca1",
      "instruction": "JNZ 0x00bbacce"
    },
    {
      "address": "00bbaca3",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00bbaca4",
      "instruction": "CALL 0x00bba640"
    },
    {
      "address": "00bbaca9",
      "instruction": "MOV ECX,dword ptr [ESI + 0x84]"
    },
    {
      "address": "00bbacaf",
      "instruction": "MOV EDI,dword ptr [ECX]"
    },
    {
      "address": "00bbacb1",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "00bbacb3",
      "instruction": "LEA EDX,[ESP + 0x10]"
    },
    {
      "address": "00bbacb7",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00bbacb8",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00bbacb9",
      "instruction": "CALL 0x00b3d2a0"
    },
    {
      "address": "00bbacbe",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00bbacc0",
      "instruction": "CALL 0x00ba8010"
    },
    {
      "address": "00bbacc5",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00bbacc6",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00bbacc8",
      "instruction": "CALL 0x00b8dde0"
    },
    {
      "address": "00bbaccd",
      "instruction": "POP EDI"
    },
    {
      "address": "00bbacce",
      "instruction": "MOV dword ptr [ESI + 0x58],EBX"
    },
    {
      "address": "00bbacd1",
      "instruction": "POP ESI"
    },
    {
      "address": "00bbacd2",
      "instruction": "POP EBX"
    },
    {
      "address": "00bbacd3",
      "instruction": "ADD ESP,0xc"
    },
    {
      "address": "00bbacd6",
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
  "body_end": "00bbacd8",
  "body_span_bytes": 89,
  "body_start": "00bbac80",
  "callees": [
    "FUN_00b8dde0",
    "FUN_00bba640",
    "FUN_00b3d2a0",
    "FUN_00ba8010"
  ],
  "callers": [
    "FUN_00bae6f0",
    "FUN_00bb28c0",
    "FUN_00bb6040",
    "FUN_00bb2a50"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00bbac80",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "uVar4",
      "storage": "Stack[-0x1c]:4",
      "type": "undefined4"
    },
    {
      "name": "uVar1",
      "storage": "register:00000000:4",
      "type": "undefined4"
    },
    {
      "name": "param_2",
      "storage": "Stack[0x4]:4",
      "type": "int"
    },
    {
      "name": "iVar3",
      "storage": "Stack[-0x20]:4",
      "type": "int"
    },
    {
      "name": "local_c",
      "storage": "",
      "type": "undefined1[12]"
    },
    {
      "name": "puVar2",
      "storage": "Stack[-0x24]:4",
      "type": "undefined1 *"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int"
    }
  ],
  "locals_count": 7,
  "mode": "live",
  "name": "FUN_00bbac80",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x7bac80",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00bbac80(void)",
  "size_bytes": 89,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00bbac80",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 6,
  "xrefs": [
    {
      "from": "00bb625f"
    },
    {
      "from": "00bae7fe"
    },
    {
      "from": "00bb298e"
    },
    {
      "from": "00bb2ba7"
    },
    {
      "from": "00df456e"
    },
    {
      "from": "00df789b"
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
