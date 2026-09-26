# Evidence 0x0045b210

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `348671fcba05e10e2ef48a6a89bbdf9b33421797c18c09f87e91a737893ac8e6`

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
        "ebp_offset": "EBP+0x8",
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "ret_form": "RET 0x4",
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
        "size_inferred": true,
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
    "receiver_not_determinable: ecx_reassigned_before_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_reassigned_before_deref), and the convention rule that would apply discriminates on receiver absence"
  ],
  "cleanup": {
    "bytes": 4,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x4",
    "side": "callee"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "66f44bbc3f8b1831d63faa106590a4be4dada9f3cbe8604ac6d5f9d3bc07b823",
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
        "obs-0036"
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
        "obs-0006",
        "obs-0007",
        "obs-0010",
        "obs-0011",
        "obs-0012",
        "obs-0021",
        "obs-0024",
        "obs-0025",
        "obs-0032"
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
        "obs-0006",
        "obs-0007",
        "obs-0010",
        "obs-0011",
        "obs-0012",
        "obs-0021",
        "obs-0024",
        "obs-0025",
        "obs-0032"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_reassigned_before_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0036"
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
        "obs-0036"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0036"
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
      "at": "0x0045b210",
      "count": 24,
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
      "at": "0x0045b210",
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
      "sub": 96
    },
    {
      "at": "0x0045b211",
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
      "at": "0x0045b211",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EBP,ESP",
      "reg": "EBP",
      "write_kind": "reg"
    },
    {
      "at": "0x0045b213",
      "definite": true,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x60",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x0045b216",
      "count": 9,
      "first_use": 3,
      "first_write_index": 8,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV dword ptr [EBP + -0x60],ECX",
      "reg": "ECX"
    },
    {
      "at": "0x0045b216",
      "base": "EBP",
      "disp": -96,
      "id": "obs-0007",
      "index": 3,
      "key": null,
      "kind": "STACK_SLOT_WRITE",
      "raw": "MOV dword ptr [EBP + -0x60],ECX",
      "reason": "local",
      "resolved": false,
      "size": 4,
      "via": "direct"
    },
    {
      "a
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
"\nundefined4 __fastcall FUN_0045b210(int param_1)\n\n{\n  undefined4 uVar1;\n  int local_c [2];\n  \n  FUN_00421950(local_c,&stack0x00000004);\n  if (local_c[0] == *(int *)(*(int *)(param_1 + 0xc) + *(int *)(param_1 + 0x10) * 4)) {\n    uVar1 = 0;\n  }\n  else {\n    uVar1 = *(undefined4 *)(local_c[0] + 4);\n  }\n  return uVar1;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 45,
  "instructions": [
    {
      "address": "0045b210",
      "instruction": "PUSH EBP"
    },
    {
      "address": "0045b211",
      "instruction": "MOV EBP,ESP"
    },
    {
      "address": "0045b213",
      "instruction": "SUB ESP,0x60"
    },
    {
      "address": "0045b216",
      "instruction": "MOV dword ptr [EBP + -0x60],ECX"
    },
    {
      "address": "0045b219",
      "instruction": "LEA EAX,[EBP + 0x8]"
    },
    {
      "address": "0045b21c",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0045b21d",
      "instruction": "LEA ECX,[EBP + -0x8]"
    },
    {
      "address": "0045b220",
      "instruction": "PUSH ECX"
    },
    {
      "address": "0045b221",
      "instruction": "MOV ECX,dword ptr [EBP + -0x60]"
    },
    {
      "address": "0045b224",
      "instruction": "ADD ECX,0x8"
    },
    {
      "address": "0045b227",
      "instruction": "CALL 0x00421950"
    },
    {
      "address": "0045b22c",
      "instruction": "MOV EDX,dword ptr [EBP + -0x60]"
    },
    {
      "address": "0045b22f",
      "instruction": "ADD EDX,0x8"
    },
    {
      "address": "0045b232",
      "instruction": "MOV dword ptr [EBP + -0x54],EDX"
    },
    {
      "address": "0045b235",
      "instruction": "MOV EAX,dword ptr [EBP + -0x54]"
    },
    {
      "address": "0045b238",
      "instruction": "MOV ECX,dword ptr [EAX + 0x8]"
    },
    {
      "address": "0045b23b",
      "instruction": "MOV EDX,dword ptr [EBP + -0x54]"
    },
    {
      "address": "0045b23e",
      "instruction": "MOV EAX,dword ptr [EDX + 0x4]"
    },
    {
      "address": "0045b241",
      "instruction": "LEA ECX,[EAX + ECX*0x4]"
    },
    {
      "address": "0045b244",
      "instruction": "MOV dword ptr [EBP + -0x50],ECX"
    },
    {
      "address": "0045b247",
      "instruction": "MOV EDX,dword ptr [EBP + -0x50]"
    },
    {
      "address": "0045b24a",
      "instruction": "MOV EAX,dword ptr [EDX]"
    },
    {
      "address": "0045b24c",
      "instruction": "MOV dword ptr [EBP + -0x4c],EAX"
    },
    {
      "address": "0045b24f",
      "instruction": "MOV ECX,dword ptr [EBP + -0x4c]"
    },
    {
      "address": "0045b252",
      "instruction": "MOV dword ptr [EBP + -0x10],ECX"
    },
    {
      "address": "0045b255",
      "instruction": "MOV EDX,dword ptr [EBP + -0x50]"
    },
    {
      "address": "0045b258",
      "instruction": "MOV dword ptr [EBP + -0xc],EDX"
    },
    {
      "address": "0045b25b",
      "instruction": "MOV EAX,dword ptr [EBP + -0x8]"
    },
    {
      "address": "0045b25e",
      "instruction": "XOR ECX,ECX"
    },
    {
      "address": "0045b260",
      "instruction": "CMP EAX,dword ptr [EBP + -0x10]"
    },
    {
      "address": "0045b263",
      "instruction": "SETZ CL"
    },
    {
      "address": "0045b266",
      "instruction": "MOVZX EDX,CL"
    },
    {
      "address": "0045b269",
      "instruction": "TEST EDX,EDX"
    },
    {
      "address": "0045b26b",
      "instruction": "JZ 0x0045b271"
    },
    {
      "address": "0045b26d",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "0045b26f",
      "instruction": "JMP 0x0045b283"
    },
    {
      "address": "0045b271",
      "instruction": "MOV EAX,dword ptr [EBP + -0x8]"
    },
    {
      "address": "0045b274",
      "instruction": "MOV dword ptr [EBP + -0x58],EAX"
    },
    {
      "address": "0045b277",
      "instruction": "MOV ECX,dword ptr [EBP + -0x58]"
    },
    {
      "address": "0045b27a",
      "instruction": "MOV EDX,dword ptr [ECX + 0x4]"
    },
    {
      "address": "0045b27d",
      "instruction": "MOV dword ptr [EBP + -0x5c],EDX"
    },
    {
      "address": "0045b280",
      "instruction": "MOV EAX,dword ptr [EBP + -0x5c]"
    },
    {
      "address": "0045b283",
      "instruction": "MOV ESP,EBP"
    },
    {
      "address": "0045b285",
      "instruction": "POP EBP"
    },
    {
      "address": "0045b286",
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
  "body_end": "0045b288",
  "body_span_bytes": 121,
  "body_start": "0045b210",
  "callees": [
    "FUN_00421950"
  ],
  "callers": [
    "FUN_0045afc0",
    "FUN_0045b000",
    "Editors::cEditor::SetActiveMode",
    "FUN_0043f6b0",
    "FUN_0062f920",
    "Editors::cEditor::Update",
    "FUN_0045b110",
    "FUN_0045b040",
    "FUN_00575f70",
    "FUN_0062f2f0",
    "FUN_005744b0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "0045b210",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_c",
      "storage": "Stack[-0xc]:4",
      "type": "int[2]"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int"
    },
    {
      "name": "uVar1",
      "storage": "register:00000000:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 3,
  "mode": "live",
  "name": "FUN_0045b210",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x5b210",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_0045b210(void)",
  "size_bytes": 121,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x0045b210",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 26,
  "xrefs": [
    {
      "from": "0043f7ff"
    },
    {
      "from": "0043fa22"
    },
    {
      "from": "0043fa39"
    },
    {
      "from": "0045b050"
    },
    {
      "from": "0045afd0"
    },
    {
      "from": "0045b010"
    },
    {
      "from": "0045b120"
    },
    {
      "from": "0057600f"
    },
    {
      "from": "00576039"
    },
    {
      "from": "005760b2"
    },
    {
      "from": "005760dc"
    },
    {
      "from": "005872e4"
    },
    {
      "from": "005877d3"
    },
    {
      "from": "005744f5"
    },
    {
      "from": "00574537"
    },
    {
      "from": "0062f948"
    },
    {
      "from": "0062f96c"
    },
    {
      "from": "0062f980"
    },
    {
      "from": "0062f304"
    },
    {
      "from": "0062f31c"
    },
    {
      "from": "0058bf45"
    },
    {
      "from": "0058bf72"
    },
    {
      "from": "0058c3da"
    },
    {
      "from": "0058c3ef"
    },
    {
      "from": "005b3cc6"
    },
    {
      "from": "005b3dcb"
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
