# Evidence 0x00c0b1c0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `bbecb4ffca0634b50922643d19a7fbccbb3c2c6fc9c61ad7a9880e6c81c544dd`

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
      "entry_ESP+0xc"
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
        "entry_offset": "entry_ESP+0xc",
        "observed": true,
        "ordinal": 3,
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
    "return_semantics": "integral_in_EAX",
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
        "entry_offset": "entry_ESP+0xc",
        "observed": true,
        "ordinal": 3,
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
    "flow_not_modelled: the linear ESP walk ends at -4, so the listing is not one path",
    "slot_gaps_present: argument ordinal(s) below the highest read slot are never touched",
    "receiver_not_determinable: ecx_read_without_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_read_without_deref), and the convention rule that would apply discriminates on receiver absence",
    "sret_vs_out_param: entry slot 0 is written through a pointer"
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
  "content_sha256": "4c925e736db8b1394e400ca2d4b96fa9a1a853c6aeeaadc6cc63f26e7cc130c4",
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
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0021",
        "obs-0022"
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
        "obs-0004",
        "obs-0008",
        "obs-0020"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 1,
        "observed_slots": 2,
        "total_bytes": 12
      }
    },
    {
      "based_on": [
        "obs-0010",
        "obs-0011",
        "obs-0017",
        "obs-0019"
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
        "obs-0017",
        "obs-0019"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_read_without_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0004",
        "obs-0020"
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
        "obs-0021",
        "obs-0022"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0021",
        "obs-0022"
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
      "and_esp": null,
      "at": "0x00c0b1c0",
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
      "raw": "SUB ESP,0x8",
      "sub": 8
    },
    {
      "at": "0x00c0b1c0",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x8",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00c0b1c3",
      "count": 9,
      "first_use": 1,
      "first_write_index": 0,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EDX,dword ptr [ESP + 0xc]",
      "reg": "ESP"
    },
    {
      "at": "0x00c0b1c3",
      "base": "ESP",
      "disp": 12,
      "id": "obs-0004",
      "index": 1,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EDX,dword ptr [ESP + 0xc]",
      "resolved": true,
      "size": 4
    }
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
"\n/* WARNING: Enum \"ObjectTYPE\": Some values do not have unique names */\n/* WARNING: Enum \"Names\": Some values do not have unique names */\n\nundefined4 FUN_00c0b1c0(uint32_t param_1,uint *param_2,PropertyList *param_3)\n\n{\n  bool bVar1;\n  int iVar2;\n  size_t local_8;\n  uint *local_4;\n  \n  local_8 = 0;\n  local_4 = (uint *)0x0;\n  bVar1 = App__Property__GetArrayUInt32(param_3,param_1,&local_8,&local_4);\n  if ((bVar1) && (0 < (int)local_8)) {\n    iVar2 = FUN_00a68fb0(local_8);\n    *param_2 = local_4[iVar2];\n    return 1;\n  }\n  return 0;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 31,
  "instructions": [
    {
      "address": "00c0b1c0",
      "instruction": "SUB ESP,0x8"
    },
    {
      "address": "00c0b1c3",
      "instruction": "MOV EDX,dword ptr [ESP + 0xc]"
    },
    {
      "address": "00c0b1c7",
      "instruction": "LEA EAX,[ESP + 0x4]"
    },
    {
      "address": "00c0b1cb",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00c0b1cc",
      "instruction": "MOV EAX,dword ptr [ESP + 0x18]"
    },
    {
      "address": "00c0b1d0",
      "instruction": "LEA ECX,[ESP + 0x4]"
    },
    {
      "address": "00c0b1d4",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00c0b1d5",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00c0b1d6",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00c0b1d7",
      "instruction": "MOV dword ptr [ESP + 0x10],0x0"
    },
    {
      "address": "00c0b1df",
      "instruction": "MOV dword ptr [ESP + 0x14],0x0"
    },
    {
      "address": "00c0b1e7",
      "instruction": "CALL 0x006a0840"
    },
    {
      "address": "00c0b1ec",
      "instruction": "ADD ESP,0x10"
    },
    {
      "address": "00c0b1ef",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00c0b1f1",
      "instruction": "JZ 0x00c0b218"
    },
    {
      "address": "00c0b1f3",
      "instruction": "MOV EAX,dword ptr [ESP]"
    },
    {
      "address": "00c0b1f6",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00c0b1f8",
      "instruction": "JLE 0x00c0b218"
    },
    {
      "address": "00c0b1fa",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00c0b1fb",
      "instruction": "MOV ECX,0x1601760"
    },
    {
      "address": "00c0b200",
      "instruction": "CALL 0x00a68fb0"
    },
    {
      "address": "00c0b205",
      "instruction": "MOV ECX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "00c0b209",
      "instruction": "MOV EDX,dword ptr [ECX + EAX*0x4]"
    },
    {
      "address": "00c0b20c",
      "instruction": "MOV EAX,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00c0b210",
      "instruction": "MOV dword ptr [EAX],EDX"
    },
    {
      "address": "00c0b212",
      "instruction": "MOV AL,0x1"
    },
    {
      "address": "00c0b214",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "00c0b217",
      "instruction": "RET"
    },
    {
      "address": "00c0b218",
      "instruction": "XOR AL,AL"
    },
    {
      "address": "00c0b21a",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "00c0b21d",
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
  "body_end": "00c0b21d",
  "body_span_bytes": 94,
  "body_start": "00c0b1c0",
  "callees": [
    "App::Property::GetArrayUInt32",
    "FUN_00a68fb0"
  ],
  "callers": [
    "FUN_00c0c5b0",
    "FUN_00c0b220"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00c0b1c0",
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
      "type": "size_t"
    },
    {
      "name": "bVar1",
      "storage": "register:00000000:1",
      "type": "bool"
    },
    {
      "name": "param_3",
      "storage": "Stack[0xc]:4",
      "type": "PropertyList *"
    },
    {
      "name": "local_4",
      "storage": "Stack[-0x4]:4",
      "type": "uint *"
    },
    {
      "name": "iVar2",
      "storage": "register:00000000:4",
      "type": "int"
    },
    {
      "name": "param_2",
      "storage": "Stack[0x8]:4",
      "type": "uint *"
    },
    {
      "name": "param_1",
      "storage": "Stack[0x4]:4",
      "type": "uint32_t"
    }
  ],
  "locals_count": 7,
  "mode": "live",
  "name": "FUN_00c0b1c0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x80b1c0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00c0b1c0(void)",
  "size_bytes": 94,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00c0b1c0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 2,
  "xrefs": [
    {
      "from": "00c0c608"
    },
    {
      "from": "00c0b25f"
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
