# Evidence 0x00c149c0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `eea60a38fcd819f926523c566143bca3fd433e5c21237f492017d0e59e0a6df4`

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
    "return_semantics": "pointer_like_in_EAX",
    "saved_registers": [
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
    "flow_not_modelled: the linear ESP walk ends at +16, so the listing is not one path",
    "slot_gaps_present: argument ordinal(s) below the highest read slot are never touched",
    "receiver_not_determinable: ecx_reassigned_before_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_reassigned_before_deref), and the convention rule that would apply discriminates on receiver absence"
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
  "content_sha256": "f4c061ad1bdf1aba8ee0018a72a0c644b47c6c0f491b274a5b4ec9c32ac3e4dd",
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
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0022"
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
        "obs-0002",
        "obs-0008"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 2,
        "observed_slots": 2,
        "total_bytes": 16
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007",
        "obs-0008",
        "obs-0009",
        "obs-0012",
        "obs-0014",
        "obs-0017"
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
        "obs-0008",
        "obs-0009",
        "obs-0012",
        "obs-0014",
        "obs-0017"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_reassigned_before_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0022"
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
        "obs-0022"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0022"
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
      "at": "0x00c149c0",
      "count": 4,
      "first_use": 0,
      "first_write_index": 26,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x10]",
      "reg": "ESP"
    },
    {
      "at": "0x00c149c0",
      "base": "ESP",
      "disp": 16,
      "id": "obs-0002",
      "index": 0,
      "key": 16,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x10]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00c149c0",
      "definite": true,
      "id": "obs-0003",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESP + 0x10]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00c149c4",
      "count": 3,
      "first_use": 1,
      "first_write_index": 11,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00c149c5",
      "count": 3,
      "first_use": 2,
      "first_write_index": 4,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00c149c8",
      "count"
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
"\nundefined4 __thiscall\nFUN_00c149c0(undefined4 param_1,undefined4 param_2,int *param_3,undefined4 param_4,\n            undefined4 param_5)\n\n{\n  undefined4 uVar1;\n  int iVar2;\n  \n  uVar1 = FUN_00c12310(param_2,param_5,0);\n  if ((param_3 != (int *)0x0) && (iVar2 = (**(code **)(*param_3 + 0xb8))(0xee3f516e), iVar2 != 0)) {\n    FUN_00c0b510(param_1,uVar1,iVar2,param_3);\n  }\n  return uVar1;\n}\n\n"
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
      "address": "00c149c0",
      "instruction": "MOV EAX,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00c149c4",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00c149c5",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00c149c6",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00c149c8",
      "instruction": "MOV EDI,ECX"
    },
    {
      "address": "00c149ca",
      "instruction": "MOV ECX,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00c149ce",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00c149cf",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00c149d0",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00c149d2",
      "instruction": "CALL 0x00c12310"
    },
    {
      "address": "00c149d7",
      "instruction": "MOV ECX,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00c149db",
      "instruction": "MOV ESI,EAX"
    },
    {
      "address": "00c149dd",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00c149df",
      "instruction": "JZ 0x00c14a06"
    },
    {
      "address": "00c149e1",
      "instruction": "MOV EDX,dword ptr [ECX]"
    },
    {
      "address": "00c149e3",
      "instruction": "MOV EAX,dword ptr [EDX + 0xb8]"
    },
    {
      "address": "00c149e9",
      "instruction": "PUSH 0xee3f516e"
    },
    {
      "address": "00c149ee",
      "instruction": "CALL EAX"
    },
    {
      "address": "00c149f0",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00c149f2",
      "instruction": "JZ 0x00c14a04"
    },
    {
      "address": "00c149f4",
      "instruction": "MOV ECX,dword ptr [ESP + 0x14]"
    },
    {
      "address": "00c149f8",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00c149f9",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00c149fa",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00c149fb",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00c149fc",
      "instruction": "CALL 0x00c0b510"
    },
    {
      "address": "00c14a01",
      "instruction": "ADD ESP,0x10"
    },
    {
      "address": "00c14a04",
      "instruction": "MOV EAX,ESI"
    },
    {
      "address": "00c14a06",
      "instruction": "POP EDI"
    },
    {
      "address": "00c14a07",
      "instruction": "POP ESI"
    },
    {
      "address": "00c14a08",
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
  "body_end": "00c14a0a",
  "body_span_bytes": 75,
  "body_start": "00c149c0",
  "callees": [
    "FUN_00c12310",
    "FUN_00c0b510"
  ],
  "callers": [
    "FUN_00d74060",
    "FUN_00dbc7a0",
    "FUN_00ec2130",
    "FUN_00c1e460",
    "FUN_00d6e3a0",
    "FUN_00dad390",
    "FUN_00d87620"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00c149c0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "iVar2",
      "storage": "register:00000000:4",
      "type": "int"
    },
    {
      "name": "uVar1",
      "storage": "register:00000000:4",
      "type": "undefined4"
    },
    {
      "name": "param_5",
      "storage": "Stack[0x10]:4",
      "type": "undefined4"
    },
    {
      "name": "param_4",
      "storage": "",
      "type": "undefined4"
    },
    {
      "name": "param_3",
      "storage": "Stack[0x8]:4",
      "type": "int *"
    },
    {
      "name": "param_2",
      "storage": "Stack[0x4]:4",
      "type": "undefined4"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 7,
  "mode": "live",
  "name": "FUN_00c149c0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x8149c0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00c149c0(void)",
  "size_bytes": 75,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00c149c0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 11,
  "xrefs": [
    {
      "from": "00c1e706"
    },
    {
      "from": "00d6e4c7"
    },
    {
      "from": "00d6e4f3"
    },
    {
      "from": "00ec2173"
    },
    {
      "from": "00d74f62"
    },
    {
      "from": "00d75193"
    },
    {
      "from": "00d87df1"
    },
    {
      "from": "00dad821"
    },
    {
      "from": "00dbcb84"
    },
    {
      "from": "00dbd98c"
    },
    {
      "from": "00dbdd35"
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
