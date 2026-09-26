# Evidence 0x00dd5dd0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `e1900300cc9f9629463652f1b672fa14474f693032ee457fa9ffd0d83ed4790d`

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
    "return_semantics": "pointer_like_in_EAX",
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
    "stack_cleanup_bytes": 4,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x4"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -16, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register"
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
  "content_sha256": "407f9452e0e81bdd1e5eea038b03d63af1b85c3d12afad1f904219dec9951e35",
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
        "obs-0023",
        "obs-0028"
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
        "obs-0009"
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
        "obs-0005",
        "obs-0006"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          48,
          68
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0005",
        "obs-0006",
        "obs-0023",
        "obs-0028"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0023",
        "obs-0028"
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
        "obs-0023",
        "obs-0028"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0023",
        "obs-0028"
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
      "at": "0x00dd5dd0",
      "count": 2,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00dd5dd1",
      "count": 2,
      "first_use": 1,
      "first_write_index": 8,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EBP",
      "reg": "EBP"
    },
    {
      "and_esp": null,
      "at": "0x00dd5dd1",
      "ebp_is_general_register": true,
      "fp": false,
      "id": "obs-0003",
      "index": 1,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": true,
      "push_ebp_at": 1,
      "raw": "PUSH EBP",
      "sub": null
    },
    {
      "at": "0x00dd5dd2",
      "count": 3,
      "first_use": 2,
      "first_write_index": 3,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00dd5dd3",
      "count": 4,
      "first_use": 3,
      "first_write_index": null,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV ESI,dword ptr [ECX + 0x30]",
      "reg": "ECX"
    },
    {
      "at": "0x00dd5dd3",
      "definite": true,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,dword ptr [ECX + 0x30]",
      "reg": "ESI",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00dd5dd9",
      "count": 4,
      "first_use": 5,
      "first_write_index": 9,
      "id": "obs-0007",
      "index": 5,
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
"\nint __thiscall FUN_00dd5dd0(int param_1,int param_2)\n\n{\n  int iVar1;\n  char cVar2;\n  int iVar3;\n  \n  iVar3 = *(int *)(param_1 + 0x30);\n  while( true ) {\n    if (iVar3 == param_1 + 0x2c) {\n      return 0;\n    }\n    iVar1 = *(int *)(iVar3 + 0x14);\n    if (((*(uint *)(iVar1 + 0xc) >> 9 & 1) != 0) &&\n       (cVar2 = FUN_0087d9a0(param_2 + 0x68,iVar1 + 0x68), cVar2 != '\\0')) break;\n    iVar3 = FUN_00921580(iVar3);\n  }\n  return iVar1;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 40,
  "instructions": [
    {
      "address": "00dd5dd0",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00dd5dd1",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00dd5dd2",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00dd5dd3",
      "instruction": "MOV ESI,dword ptr [ECX + 0x30]"
    },
    {
      "address": "00dd5dd6",
      "instruction": "LEA EBX,[ECX + 0x2c]"
    },
    {
      "address": "00dd5dd9",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00dd5dda",
      "instruction": "CMP ESI,EBX"
    },
    {
      "address": "00dd5ddc",
      "instruction": "JZ 0x00dd5e12"
    },
    {
      "address": "00dd5dde",
      "instruction": "MOV EBP,dword ptr [ESP + 0x14]"
    },
    {
      "address": "00dd5de2",
      "instruction": "MOV EDI,dword ptr [ESI + 0x14]"
    },
    {
      "address": "00dd5de5",
      "instruction": "MOV EAX,dword ptr [EDI + 0xc]"
    },
    {
      "address": "00dd5de8",
      "instruction": "SHR EAX,0x9"
    },
    {
      "address": "00dd5deb",
      "instruction": "TEST AL,0x1"
    },
    {
      "address": "00dd5ded",
      "instruction": "JZ 0x00dd5e03"
    },
    {
      "address": "00dd5def",
      "instruction": "LEA ECX,[EDI + 0x68]"
    },
    {
      "address": "00dd5df2",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00dd5df3",
      "instruction": "LEA EDX,[EBP + 0x68]"
    },
    {
      "address": "00dd5df6",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00dd5df7",
      "instruction": "CALL 0x0087d9a0"
    },
    {
      "address": "00dd5dfc",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "00dd5dff",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00dd5e01",
      "instruction": "JNZ 0x00dd5e1b"
    },
    {
      "address": "00dd5e03",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00dd5e04",
      "instruction": "CALL 0x00921580"
    },
    {
      "address": "00dd5e09",
      "instruction": "MOV ESI,EAX"
    },
    {
      "address": "00dd5e0b",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "00dd5e0e",
      "instruction": "CMP ESI,EBX"
    },
    {
      "address": "00dd5e10",
      "instruction": "JNZ 0x00dd5de2"
    },
    {
      "address": "00dd5e12",
      "instruction": "POP EDI"
    },
    {
      "address": "00dd5e13",
      "instruction": "POP ESI"
    },
    {
      "address": "00dd5e14",
      "instruction": "POP EBP"
    },
    {
      "address": "00dd5e15",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "00dd5e17",
      "instruction": "POP EBX"
    },
    {
      "address": "00dd5e18",
      "instruction": "RET 0x4"
    },
    {
      "address": "00dd5e1b",
      "instruction": "MOV EAX,EDI"
    },
    {
      "address": "00dd5e1d",
      "instruction": "POP EDI"
    },
    {
      "address": "00dd5e1e",
      "instruction": "POP ESI"
    },
    {
      "address": "00dd5e1f",
      "instruction": "POP EBP"
    },
    {
      "address": "00dd5e20",
      "instruction": "POP EBX"
    },
    {
      "address": "00dd5e21",
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
  "body_end": "00dd5e23",
  "body_span_bytes": 84,
  "body_start": "00dd5dd0",
  "callees": [
    "FUN_0087d9a0",
    "FUN_00921580"
  ],
  "callers": [
    "FUN_00dd6df0",
    "FUN_00dd8640",
    "FUN_00dd6ec0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00dd5dd0",
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
      "name": "cVar2",
      "storage": "register:00000000:1",
      "type": "char"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int"
    },
    {
      "name": "param_2",
      "storage": "Stack[0x4]:4",
      "type": "int"
    },
    {
      "name": "iVar3",
      "storage": "register:00000000:4",
      "type": "int"
    }
  ],
  "locals_count": 5,
  "mode": "live",
  "name": "FUN_00dd5dd0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x9d5dd0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00dd5dd0(void)",
  "size_bytes": 84,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00dd5dd0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 3,
  "xrefs": [
    {
      "from": "00dd8c93"
    },
    {
      "from": "00dd6e99"
    },
    {
      "from": "00dd6ed1"
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
