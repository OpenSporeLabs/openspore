# Evidence 0x004b09b0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `206f76a33c4cf64eb463a7d520e6fb7087a9dc1277a89829a71738917a8ce2ee`

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
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
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
    "sret_vs_out_param: entry slot 0 is written through a pointer"
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
  "content_sha256": "edc7adba55fa064eb64e7d932b8c67edc4383eb4b55379b64c958337d84b6ae2",
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
    "indirect_calls": 2,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0029"
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
        "obs-0010",
        "obs-0017",
        "obs-0018",
        "obs-0019",
        "obs-0022"
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
        "obs-0006",
        "obs-0007",
        "obs-0010",
        "obs-0011",
        "obs-0012",
        "obs-0018",
        "obs-0019",
        "obs-0021",
        "obs-0025"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          0
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007",
        "obs-0010",
        "obs-0011",
        "obs-0012",
        "obs-0018",
        "obs-0019",
        "obs-0021",
        "obs-0025",
        "obs-0029"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0010",
        "obs-0018",
        "obs-0019",
        "obs-0022"
      ],
      "claim": "a hidden struct-return pointer is a hypothesis only: entry slot 0 is written through a pointer",
      "confidence": "INFERRED",
      "id": "S1",
      "value": {
        "ambiguity": "sret_vs_out_param",
        "present": null,
        "slot": 4
      }
    },
    {
      "based_on": [
        "obs-0029"
      ],
      "claim": "in MSVC x86 a hidden struct-return pointer is always stack slot 0 while this is in ECX, so the two never contend",
      "confidence": "APPROXIMATION",
      "id": "S3",
      "value": {
        "ordering": "not_applicable"
      }
    },
    {
      "based_on": [
        "obs-0029"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0029"
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
      "at": "0x004b09b0",
      "count": 16,
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
      "at": "0x004b09b0",
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
      "sub": 8
    },
    {
      "at": "0x004b09b1",
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
      "at": "0x004b09b1",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EBP,ESP",
      "reg": "EBP",
      "write_kind": "reg"
    },
    {
      "at": "0x004b09b3",
      "definite": true,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x8",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "
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
"\nint * __thiscall FUN_004b09b0(int *param_1,int *param_2)\n\n{\n  int *piVar1;\n  \n  if (param_2 != (int *)*param_1) {\n    piVar1 = (int *)*param_1;\n    if (param_2 != (int *)0x0) {\n      (**(code **)(*param_2 + 4))();\n    }\n    *param_1 = (int)param_2;\n    if (piVar1 != (int *)0x0) {\n      (**(code **)(*piVar1 + 8))();\n    }\n  }\n  return param_1;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 32,
  "instructions": [
    {
      "address": "004b09b0",
      "instruction": "PUSH EBP"
    },
    {
      "address": "004b09b1",
      "instruction": "MOV EBP,ESP"
    },
    {
      "address": "004b09b3",
      "instruction": "SUB ESP,0x8"
    },
    {
      "address": "004b09b6",
      "instruction": "MOV dword ptr [EBP + -0x8],ECX"
    },
    {
      "address": "004b09b9",
      "instruction": "MOV EAX,dword ptr [EBP + -0x8]"
    },
    {
      "address": "004b09bc",
      "instruction": "MOV ECX,dword ptr [EBP + 0x8]"
    },
    {
      "address": "004b09bf",
      "instruction": "CMP ECX,dword ptr [EAX]"
    },
    {
      "address": "004b09c1",
      "instruction": "JZ 0x004b09f9"
    },
    {
      "address": "004b09c3",
      "instruction": "MOV EDX,dword ptr [EBP + -0x8]"
    },
    {
      "address": "004b09c6",
      "instruction": "MOV EAX,dword ptr [EDX]"
    },
    {
      "address": "004b09c8",
      "instruction": "MOV dword ptr [EBP + -0x4],EAX"
    },
    {
      "address": "004b09cb",
      "instruction": "CMP dword ptr [EBP + 0x8],0x0"
    },
    {
      "address": "004b09cf",
      "instruction": "JZ 0x004b09de"
    },
    {
      "address": "004b09d1",
      "instruction": "MOV ECX,dword ptr [EBP + 0x8]"
    },
    {
      "address": "004b09d4",
      "instruction": "MOV EDX,dword ptr [ECX]"
    },
    {
      "address": "004b09d6",
      "instruction": "MOV ECX,dword ptr [EBP + 0x8]"
    },
    {
      "address": "004b09d9",
      "instruction": "MOV EAX,dword ptr [EDX + 0x4]"
    },
    {
      "address": "004b09dc",
      "instruction": "CALL EAX"
    },
    {
      "address": "004b09de",
      "instruction": "MOV ECX,dword ptr [EBP + -0x8]"
    },
    {
      "address": "004b09e1",
      "instruction": "MOV EDX,dword ptr [EBP + 0x8]"
    },
    {
      "address": "004b09e4",
      "instruction": "MOV dword ptr [ECX],EDX"
    },
    {
      "address": "004b09e6",
      "instruction": "CMP dword ptr [EBP + -0x4],0x0"
    },
    {
      "address": "004b09ea",
      "instruction": "JZ 0x004b09f9"
    },
    {
      "address": "004b09ec",
      "instruction": "MOV EAX,dword ptr [EBP + -0x4]"
    },
    {
      "address": "004b09ef",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "004b09f1",
      "instruction": "MOV ECX,dword ptr [EBP + -0x4]"
    },
    {
      "address": "004b09f4",
      "instruction": "MOV EAX,dword ptr [EDX + 0x8]"
    },
    {
      "address": "004b09f7",
      "instruction": "CALL EAX"
    },
    {
      "address": "004b09f9",
      "instruction": "MOV EAX,dword ptr [EBP + -0x8]"
    },
    {
      "address": "004b09fc",
      "instruction": "MOV ESP,EBP"
    },
    {
      "address": "004b09fe",
      "instruction": "POP EBP"
    },
    {
      "address": "004b09ff",
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
  "body_end": "004b0a01",
  "body_span_bytes": 82,
  "body_start": "004b09b0",
  "callees": [],
  "callers": [
    "FUN_0057e790",
    "FUN_00573c00",
    "Editors::cEditor::sub_581F70",
    "Editors::cEditor::OnMouseMove",
    "Editors::cEditor::OnMouseDown",
    "FUN_004b0590"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "004b09b0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "piVar1",
      "storage": "unique:00017200:4",
      "type": "int *"
    },
    {
      "name": "param_2",
      "storage": "Stack[0x4]:4",
      "type": "int *"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int *"
    }
  ],
  "locals_count": 3,
  "mode": "live",
  "name": "FUN_004b09b0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xb09b0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_004b09b0(void)",
  "size_bytes": 82,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x004b09b0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 11,
  "xrefs": [
    {
      "from": "004b06c3"
    },
    {
      "from": "005738e6"
    },
    {
      "from": "00573cd0"
    },
    {
      "from": "005824ce"
    },
    {
      "from": "0057e843"
    },
    {
      "from": "00588afb"
    },
    {
      "from": "00588b11"
    },
    {
      "from": "00588bf5"
    },
    {
      "from": "00589774"
    },
    {
      "from": "005ac70b"
    },
    {
      "from": "005b3b7e"
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
