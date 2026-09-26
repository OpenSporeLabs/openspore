# Evidence 0x00bf00a0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `c9372764bed5ae86ce524f4be62a5bf2b94f5afa825b27a04d7c8222fc8d128a`

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
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x8",
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
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
    "stack_cleanup_bytes": 8,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x8"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -16, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register"
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
  "content_sha256": "2ba27c1897fed6d37253c6e4eb4963fb88bcb95db8e2ce9d209eb39e8eedc485",
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
        "obs-0027",
        "obs-0032"
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
        "obs-0019",
        "obs-0020",
        "obs-0022"
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
        "obs-0005",
        "obs-0006",
        "obs-0016"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          156,
          160
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0005",
        "obs-0006",
        "obs-0016",
        "obs-0027",
        "obs-0032"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0027",
        "obs-0032"
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
        "obs-0027",
        "obs-0032"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0027",
        "obs-0032"
      ],
      "claim": "the last value written to EAX classifies as integral",
      "confidence": "INFERRED",
      "id": "RT2",
      "value": {
        "register_class": "integral"
      }
    }
  ],
  "observations": [
    {
      "at": "0x00bf00a0",
      "count": 3,
      "first_use": 0,
      "first_write_index": 13,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00bf00a1",
      "count": 4,
      "first_use": 1,
      "first_write_index": 3,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EBP",
      "reg": "EBP"
    },
    {
      "and_esp": null,
      "at": "0x00bf00a1",
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
      "at": "0x00bf00a2",
      "count": 2,
      "first_use": 2,
      "first_write_index": 4,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00bf00a3",
      "count": 1,
      "first_use": 3,
      "first_w
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
"\nundefined4 __thiscall FUN_00bf00a0(int param_1,int param_2,int param_3)\n\n{\n  int iVar1;\n  int iVar2;\n  int iVar3;\n  \n  iVar2 = *(int *)(param_1 + 0xa0) - *(int *)(param_1 + 0x9c) >> 2;\n  iVar3 = 0;\n  if (0 < iVar2) {\n    do {\n      iVar1 = FUN_00bd8210();\n      if ((iVar1 == param_2) && ((param_3 == -1 || (iVar1 = FUN_00bd81d0(), iVar1 == param_3)))) {\n        return 1;\n      }\n      iVar3 = iVar3 + 1;\n    } while (iVar3 < iVar2);\n  }\n  return 0;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 39,
  "instructions": [
    {
      "address": "00bf00a0",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00bf00a1",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00bf00a2",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00bf00a3",
      "instruction": "MOV EBP,ECX"
    },
    {
      "address": "00bf00a5",
      "instruction": "MOV ESI,dword ptr [EBP + 0xa0]"
    },
    {
      "address": "00bf00ab",
      "instruction": "SUB ESI,dword ptr [EBP + 0x9c]"
    },
    {
      "address": "00bf00b1",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00bf00b2",
      "instruction": "SAR ESI,0x2"
    },
    {
      "address": "00bf00b5",
      "instruction": "XOR EDI,EDI"
    },
    {
      "address": "00bf00b7",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "00bf00b9",
      "instruction": "JLE 0x00bf00ef"
    },
    {
      "address": "00bf00bb",
      "instruction": "JMP 0x00bf00c0"
    },
    {
      "address": "00bf00c0",
      "instruction": "MOV EAX,dword ptr [EBP + 0x9c]"
    },
    {
      "address": "00bf00c6",
      "instruction": "MOV EBX,dword ptr [EAX + EDI*0x4]"
    },
    {
      "address": "00bf00c9",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "00bf00cb",
      "instruction": "CALL 0x00bd8210"
    },
    {
      "address": "00bf00d0",
      "instruction": "CMP EAX,dword ptr [ESP + 0x14]"
    },
    {
      "address": "00bf00d4",
      "instruction": "JNZ 0x00bf00ea"
    },
    {
      "address": "00bf00d6",
      "instruction": "CMP dword ptr [ESP + 0x18],-0x1"
    },
    {
      "address": "00bf00db",
      "instruction": "JZ 0x00bf00f8"
    },
    {
      "address": "00bf00dd",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "00bf00df",
      "instruction": "CALL 0x00bd81d0"
    },
    {
      "address": "00bf00e4",
      "instruction": "CMP EAX,dword ptr [ESP + 0x18]"
    },
    {
      "address": "00bf00e8",
      "instruction": "JZ 0x00bf00f8"
    },
    {
      "address": "00bf00ea",
      "instruction": "INC EDI"
    },
    {
      "address": "00bf00eb",
      "instruction": "CMP EDI,ESI"
    },
    {
      "address": "00bf00ed",
      "instruction": "JL 0x00bf00c0"
    },
    {
      "address": "00bf00ef",
      "instruction": "POP EDI"
    },
    {
      "address": "00bf00f0",
      "instruction": "POP ESI"
    },
    {
      "address": "00bf00f1",
      "instruction": "POP EBP"
    },
    {
      "address": "00bf00f2",
      "instruction": "XOR AL,AL"
    },
    {
      "address": "00bf00f4",
      "instruction": "POP EBX"
    },
    {
      "address": "00bf00f5",
      "instruction": "RET 0x8"
    },
    {
      "address": "00bf00f8",
      "instruction": "POP EDI"
    },
    {
      "address": "00bf00f9",
      "instruction": "POP ESI"
    },
    {
      "address": "00bf00fa",
      "instruction": "POP EBP"
    },
    {
      "address": "00bf00fb",
      "instruction": "MOV AL,0x1"
    },
    {
      "address": "00bf00fd",
      "instruction": "POP EBX"
    },
    {
      "address": "00bf00fe",
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
  "body_end": "00bf0100",
  "body_span_bytes": 97,
  "body_start": "00bf00a0",
  "callees": [
    "FUN_00bd81d0",
    "FUN_00bd8210"
  ],
  "callers": [
    "FUN_00bf9e70",
    "FUN_00bf8710",
    "FUN_00bf9820",
    "FUN_00bf8440",
    "FUN_00bf0110"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00bf00a0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "iVar3",
      "storage": "register:0000001c:4",
      "type": "int"
    },
    {
      "name": "iVar1",
      "storage": "register:00000000:4",
      "type": "int"
    },
    {
      "name": "iVar2",
      "storage": "register:00000018:4",
      "type": "int"
    },
    {
      "name": "param_2",
      "storage": "Stack[0x4]:4",
      "type": "int"
    },
    {
      "name": "param_3",
      "storage": "Stack[0x8]:4",
      "type": "int"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int"
    }
  ],
  "locals_count": 6,
  "mode": "live",
  "name": "FUN_00bf00a0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x7f00a0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00bf00a0(void)",
  "size_bytes": 97,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00bf00a0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 5,
  "xrefs": [
    {
      "from": "00bf85f9"
    },
    {
      "from": "00bf87bc"
    },
    {
      "from": "00bf997f"
    },
    {
      "from": "00bfa10d"
    },
    {
      "from": "00bf0124"
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
