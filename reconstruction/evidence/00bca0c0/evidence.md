# Evidence 0x00bca0c0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `aec1584481a9274bc7ed5668c0628984ac8a2ba89b45d0758f1f6d9ea9b9528c`

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
      "entry_ESP+0x8",
      "entry_ESP+0xc",
      "entry_ESP+0x10"
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
      },
      {
        "entry_offset": "entry_ESP+0xc",
        "observed": true,
        "ordinal": 3,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x10",
        "observed": true,
        "ordinal": 4,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "ret_form": "RET 0x10",
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
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
      },
      {
        "entry_offset": "entry_ESP+0xc",
        "observed": true,
        "ordinal": 3,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x10",
        "observed": true,
        "ordinal": 4,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "stack_cleanup_bytes": 16,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x10"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -12, so the listing is not one path",
    "unparsed_lines_present: 1 line(s) matched no grammar rule",
    "receiver_not_determinable: ecx_address_taken_without_memory_access",
    "ecx_address_taken_without_memory_access: LEA takes ECX's address without any memory access through it",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_address_taken_without_memory_access), and the convention rule that would apply discriminates on receiver absence"
  ],
  "cleanup": {
    "bytes": 16,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x10",
    "side": "callee"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "9be3fcd7354fb085e4661171860cbec2dfb04a4b300c323a5f66b6928f3e73d3",
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
        "obs-0022",
        "obs-0026"
      ],
      "claim": "the callee pops 16 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 16,
        "side": "callee"
      }
    },
    {
      "based_on": [
        "obs-0003",
        "obs-0006",
        "obs-0009",
        "obs-0013"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 4,
        "total_bytes": 16
      }
    },
    {
      "based_on": [
        "obs-0011",
        "obs-0012",
        "obs-0013",
        "obs-0014"
      ],
      "claim": "the register receiver is undetermined: ecx_address_taken_without_memory_access",
      "confidence": "UNKNOWN",
      "id": "R0",
      "value": {
        "reason": "ecx_address_taken_without_memory_access",
        "register": null
      }
    },
    {
      "based_on": [
        "obs-0011",
        "obs-0012",
        "obs-0013",
        "obs-0014"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_address_taken_without_memory_access) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0022",
        "obs-0026"
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
        "obs-0022",
        "obs-0026"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0022",
        "obs-0026"
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
      "at": "0x00bca0c0",
      "count": 1,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs
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
"\nuint __thiscall FUN_00bca0c0(int param_1,int param_2,int param_3,int param_4,int param_5)\n\n{\n  int *piVar1;\n  uint uVar2;\n  \n  piVar1 = (int *)(param_1 + 0x28);\n  uVar2 = 0;\n  while ((((piVar1[-1] != param_2 || (*piVar1 != param_3)) ||\n          ((param_4 != 0 && (piVar1[5] != param_4)))) || ((param_5 != 0 && (piVar1[6] != param_5))))\n        ) {\n    uVar2 = uVar2 + 1;\n    piVar1 = piVar1 + 0x11;\n    if (7 < uVar2) {\n      return 0xffffffff;\n    }\n  }\n  return (uint)*(ushort *)(piVar1 + -2) | uVar2 << 0x10;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 37,
  "instructions": [
    {
      "address": "00bca0c0",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00bca0c1",
      "instruction": "MOV EBX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "00bca0c5",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00bca0c6",
      "instruction": "MOV ESI,dword ptr [ESP + 0x14]"
    },
    {
      "address": "00bca0ca",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00bca0cb",
      "instruction": "MOV EDI,dword ptr [ESP + 0x14]"
    },
    {
      "address": "00bca0cf",
      "instruction": "LEA EAX,[ECX + 0x28]"
    },
    {
      "address": "00bca0d2",
      "instruction": "MOV ECX,dword ptr [ESP + 0x1c]"
    },
    {
      "address": "00bca0d6",
      "instruction": "XOR EDX,EDX"
    },
    {
      "address": "00bca0d8",
      "instruction": "CMP dword ptr [EAX + -0x4],EBX"
    },
    {
      "address": "00bca0db",
      "instruction": "JNZ 0x00bca0f3"
    },
    {
      "address": "00bca0dd",
      "instruction": "CMP dword ptr [EAX],EDI"
    },
    {
      "address": "00bca0df",
      "instruction": "JNZ 0x00bca0f3"
    },
    {
      "address": "00bca0e1",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "00bca0e3",
      "instruction": "JZ 0x00bca0ea"
    },
    {
      "address": "00bca0e5",
      "instruction": "CMP dword ptr [EAX + 0x14],ESI"
    },
    {
      "address": "00bca0e8",
      "instruction": "JNZ 0x00bca0f3"
    },
    {
      "address": "00bca0ea",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00bca0ec",
      "instruction": "JZ 0x00bca105"
    },
    {
      "address": "00bca0ee",
      "instruction": "CMP dword ptr [EAX + 0x18],ECX"
    },
    {
      "address": "00bca0f1",
      "instruction": "JZ 0x00bca105"
    },
    {
      "address": "00bca0f3",
      "instruction": "INC EDX"
    },
    {
      "address": "00bca0f4",
      "instruction": "ADD EAX,0x44"
    },
    {
      "address": "00bca0f7",
      "instruction": "CMP EDX,0x8"
    },
    {
      "address": "00bca0fa",
      "instruction": "JC 0x00bca0d8"
    },
    {
      "address": "00bca0fc",
      "instruction": "POP EDI"
    },
    {
      "address": "00bca0fd",
      "instruction": "POP ESI"
    },
    {
      "address": "00bca0fe",
      "instruction": "OR EAX,0xffffffff"
    },
    {
      "address": "00bca101",
      "instruction": "POP EBX"
    },
    {
      "address": "00bca102",
      "instruction": "RET 0x10"
    },
    {
      "address": "00bca105",
      "instruction": "MOVZX EAX,word ptr [EAX + -0x8]"
    },
    {
      "address": "00bca109",
      "instruction": "POP EDI"
    },
    {
      "address": "00bca10a",
      "instruction": "SHL EDX,0x10"
    },
    {
      "address": "00bca10d",
      "instruction": "POP ESI"
    },
    {
      "address": "00bca10e",
      "instruction": "OR EAX,EDX"
    },
    {
      "address": "00bca110",
      "instruction": "POP EBX"
    },
    {
      "address": "00bca111",
      "instruction": "RET 0x10"
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
  "body_end": "00bca113",
  "body_span_bytes": 84,
  "body_start": "00bca0c0",
  "callees": [],
  "callers": [
    "FUN_00d697a0",
    "FUN_00da6b10",
    "FUN_00d9b110",
    "FUN_00ba48b0",
    "FUN_00d2ffd0",
    "FUN_00c238b0",
    "FUN_00c0c630",
    "FUN_00c07480",
    "FUN_00c20230",
    "FUN_00cdcb10",
    "FUN_00c05a80",
    "FUN_00d1e720",
    "FUN_00d4b2f0",
    "FUN_00c09410",
    "FUN_00c0e6a0",
    "FUN_00d8e8d0"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "00bca0c0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "uVar2",
      "storage": "register:00000008:4",
      "type": "uint"
    },
    {
      "name": "piVar1",
      "storage": "register:00000000:4",
      "type": "int *"
    },
    {
      "name": "param_3",
      "storage": "Stack[0x8]:4",
      "type": "int"
    },
    {
      "name": "param_2",
      "storage": "Stack[0x4]:4",
      "type": "int"
    },
    {
      "name": "param_5",
      "storage": "Stack[0x10]:4",
      "type": "int"
    },
    {
      "name": "param_4",
      "storage": "Stack[0xc]:4",
      "type": "int"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int"
    }
  ],
  "locals_count": 7,
  "mode": "live",
  "name": "FUN_00bca0c0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x7ca0c0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00bca0c0(void)",
  "size_bytes": 84,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00bca0c0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 22,
  "xrefs": [
    {
      "from": "00c0c939"
    },
    {
      "from": "00c05bbb"
    },
    {
      "from": "00c07894"
    },
    {
      "from": "00c078b8"
    },
    {
      "from": "00d303db"
    },
    {
      "from": "00c0991a"
    },
    {
      "from": "00c09939"
    },
    {
      "from": "00cdcdd2"
    },
    {
      "from": "00d4b372"
    },
    {
      "from": "00d69894"
    },
    {
      "from": "00d8eb60"
    },
    {
      "from": "00d8ecfd"
    },
    {
      "from": "00da6b44"
    },
    {
      "from": "00da6b5c"
    },
    {
      "from": "00d1e75c"
    },
    {
      "from": "00ba49e9"
    },
    {
      "from": "00c0e893"
    },
    {
      "from": "00c23a79"
    },
    {
      "from": "00c23a95"
    },
    {
      "from": "00c20b89"
    },
    {
      "from": "00c92838"
    },
    {
      "from": "00d9b198"
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
