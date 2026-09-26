# Evidence 0x00c14990

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `f5ec06603bf499d9acf175885f0cd5bad15d4ca1213a636ff19741ff6e2bf347`

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
    "ret_form": "RET 0xc",
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
    "stack_cleanup_bytes": 12,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0xc"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +12, so the listing is not one path",
    "slot_gaps_present: argument ordinal(s) below the highest read slot are never touched",
    "receiver_not_determinable: ecx_read_without_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_read_without_deref), and the convention rule that would apply discriminates on receiver absence"
  ],
  "cleanup": {
    "bytes": 12,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0xc",
    "side": "callee"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "57f66ddd5c906ef23002be99737ce8434c5c3107883f3a274396577b4d42c038",
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
        "obs-0020"
      ],
      "claim": "the callee pops 12 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 12,
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
        "gaps": 1,
        "observed_slots": 2,
        "total_bytes": 12
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007",
        "obs-0008",
        "obs-0009"
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
        "obs-0006",
        "obs-0007",
        "obs-0008",
        "obs-0009"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_read_without_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0020"
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
        "obs-0020"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0020"
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
      "at": "0x00c14990",
      "count": 3,
      "first_use": 0,
      "first_write_index": 16,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0xc]",
      "reg": "ESP"
    },
    {
      "at": "0x00c14990",
      "base": "ESP",
      "disp": 12,
      "id": "obs-0002",
      "index": 0,
      "key": 12,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0xc]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00c14990",
      "definite": true,
      "id": "obs-0003",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESP + 0xc]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00c14994",
      "count": 3,
      "first_use": 1,
      "first_write_index": 4,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00c14995",
      "count": 3,
      "first_use": 2,
      "first_write_index": 12,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00c14998",
      "count": 2,
      "first_use": 4,
      "first_write_index": 5,
      "id": "obs-0006",
      "index": 4,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
 
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
"\nundefined4 __thiscall\nFUN_00c14990(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)\n\n{\n  undefined4 uVar1;\n  \n  uVar1 = FUN_00c12310(param_2,param_4,0);\n  FUN_00c0b570(param_1,uVar1,param_3);\n  return uVar1;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 21,
  "instructions": [
    {
      "address": "00c14990",
      "instruction": "MOV EAX,dword ptr [ESP + 0xc]"
    },
    {
      "address": "00c14994",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00c14995",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00c14996",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00c14998",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00c1499a",
      "instruction": "MOV ECX,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00c1499e",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00c1499f",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00c149a0",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00c149a2",
      "instruction": "CALL 0x00c12310"
    },
    {
      "address": "00c149a7",
      "instruction": "MOV EDX,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00c149ab",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00c149ac",
      "instruction": "MOV EDI,EAX"
    },
    {
      "address": "00c149ae",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00c149af",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00c149b0",
      "instruction": "CALL 0x00c0b570"
    },
    {
      "address": "00c149b5",
      "instruction": "ADD ESP,0xc"
    },
    {
      "address": "00c149b8",
      "instruction": "MOV EAX,EDI"
    },
    {
      "address": "00c149ba",
      "instruction": "POP EDI"
    },
    {
      "address": "00c149bb",
      "instruction": "POP ESI"
    },
    {
      "address": "00c149bc",
      "instruction": "RET 0xc"
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
  "body_end": "00c149be",
  "body_span_bytes": 47,
  "body_start": "00c14990",
  "callees": [
    "FUN_00c0b570",
    "FUN_00c12310"
  ],
  "callers": [
    "FUN_00d86a30",
    "FUN_00d81b60",
    "FUN_00db1790",
    "FUN_00d87620"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00c14990",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "uVar1",
      "storage": "register:00000000:4",
      "type": "undefined4"
    },
    {
      "name": "param_4",
      "storage": "Stack[0xc]:4",
      "type": "undefined4"
    },
    {
      "name": "param_3",
      "storage": "Stack[0x8]:4",
      "type": "undefined4"
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
  "locals_count": 5,
  "mode": "live",
  "name": "FUN_00c14990",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x814990",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00c14990(void)",
  "size_bytes": 47,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00c14990",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 10,
  "xrefs": [
    {
      "from": "00d86cfe"
    },
    {
      "from": "00d87e0a"
    },
    {
      "from": "00d87e4f"
    },
    {
      "from": "00d87ebc"
    },
    {
      "from": "00db19e0"
    },
    {
      "from": "00d81cd4"
    },
    {
      "from": "00ad46fe"
    },
    {
      "from": "00d64526"
    },
    {
      "from": "00d649b1"
    },
    {
      "from": "00dbda28"
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
