# Evidence 0x004a88d0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `531450f8499568aa1ff3e2130876143a7fec55330e1464553685fc7dfc84a05a`

## abi

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "abi": {
    "architecture": "x86-32",
    "calling_convention": "__cdecl",
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
    "receiver": false,
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
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
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate",
    "side": "caller"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "798f735120d9907f0338840efdc151b9360017d509a5dd346633e339cbfda9ef",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__cdecl",
    "candidate_conventions": [
      "__cdecl",
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
        "obs-0012"
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
        "obs-0008"
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
        "obs-0012"
      ],
      "claim": "ECX is never read in any form, so there is no register receiver",
      "confidence": "OBSERVED",
      "id": "R2",
      "value": {
        "present": false
      }
    },
    {
      "based_on": [
        "obs-0008",
        "obs-0012"
      ],
      "claim": "calling convention is __cdecl: the caller cleans the stack and at least one entry slot is read",
      "confidence": "INFERRED",
      "id": "C9",
      "value": "__cdecl"
    },
    {
      "based_on": [
        "obs-0012"
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
        "obs-0012"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0012"
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
      "at": "0x004a88d0",
      "count": 3,
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
      "at": "0x004a88d0",
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
      "at": "0x004a88d1",
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
      "at": "0x004a88d1",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EBP,ESP",
      "reg": "EBP",
      "write_kind": "reg"
    },
    {
      "at": "0x004a88d3",
      "definite": true,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x8",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x004a88d6",
      "id": "obs-0006",
      "index": 3,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00435e90",
      "target": "0x00435e90"
    },
    {
      "at": "0x004a88db",
      "count": 2,
      "first_use": 4,
      "first_write_index": 5,
      "id": "obs-0007",
      "index": 4,
      "kind": "REG_READ",
      "raw": "PUSH EAX",
      "reg": "EAX"
    },
    {
      "at": "0x004a88dc",
      "base": "EBP",
      "disp": 8,
      "id": "obs-0008",
      "index": 5,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [EBP + 0x8]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x004a88dc",
      "definite": true,
      "id": "obs-0009",
      "index": 5,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [EBP + 0x8]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x004a88e0",
      "id": "obs-0010",
      "index": 7,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00435ed0",
      "target": "0x00435ed0"
    },
    {
      
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
"\nvoid FUN_004a88d0(undefined4 param_1)\n\n{\n  undefined4 uVar1;\n  \n  uVar1 = FUN_00435e90();\n  FUN_00435ed0(param_1,uVar1);\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 12,
  "instructions": [
    {
      "address": "004a88d0",
      "instruction": "PUSH EBP"
    },
    {
      "address": "004a88d1",
      "instruction": "MOV EBP,ESP"
    },
    {
      "address": "004a88d3",
      "instruction": "SUB ESP,0x8"
    },
    {
      "address": "004a88d6",
      "instruction": "CALL 0x00435e90"
    },
    {
      "address": "004a88db",
      "instruction": "PUSH EAX"
    },
    {
      "address": "004a88dc",
      "instruction": "MOV EAX,dword ptr [EBP + 0x8]"
    },
    {
      "address": "004a88df",
      "instruction": "PUSH EAX"
    },
    {
      "address": "004a88e0",
      "instruction": "CALL 0x00435ed0"
    },
    {
      "address": "004a88e5",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "004a88e8",
      "instruction": "MOV ESP,EBP"
    },
    {
      "address": "004a88ea",
      "instruction": "POP EBP"
    },
    {
      "address": "004a88eb",
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
  "body_end": "004a88eb",
  "body_span_bytes": 28,
  "body_start": "004a88d0",
  "callees": [
    "FUN_00435e90",
    "FUN_00435ed0"
  ],
  "callers": [
    "FUN_005b8fb0",
    "Editors::cEditor::HandleMessage",
    "FUN_00573c00",
    "FUN_005dfb40",
    "FUN_005dfd00",
    "FUN_0043c710",
    "FUN_005c3cb0",
    "FUN_00591690",
    "FUN_005a63d0",
    "FUN_005e0000",
    "Editors::cEditor::OnMouseUp",
    "FUN_005bccc0",
    "FUN_0043cad0",
    "FUN_005dda30",
    "FUN_005bc0f0",
    "FUN_005cb240",
    "FUN_005def30",
    "Editors::cEditor::OnMouseDown",
    "FUN_00577580"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "004a88d0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "param_1",
      "storage": "Stack[0x4]:4",
      "type": "undefined4"
    },
    {
      "name": "uVar1",
      "storage": "register:00000000:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 2,
  "mode": "live",
  "name": "FUN_004a88d0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xa88d0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_004a88d0(void)",
  "size_bytes": 28,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x004a88d0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 39,
  "xrefs": [
    {
      "from": "0043cdea"
    },
    {
      "from": "0043c9fe"
    },
    {
      "from": "00573d2d"
    },
    {
      "from": "005dda72"
    },
    {
      "from": "0058b7a9"
    },
    {
      "from": "005a694d"
    },
    {
      "from": "005b93af"
    },
    {
      "from": "005bc3e6"
    },
    {
      "from": "005bc404"
    },
    {
      "from": "005bd455"
    },
    {
      "from": "005bd46c"
    },
    {
      "from": "005c3d51"
    },
    {
      "from": "005cb2ea"
    },
    {
      "from": "005e00fa"
    },
    {
      "from": "005e011a"
    },
    {
      "from": "005e01d4"
    },
    {
      "from": "005dfb8b"
    },
    {
      "from": "005dfd83"
    },
    {
      "from": "005dfdeb"
    },
    {
      "from": "005dfe12"
    },
    {
      "from": "005dfe87"
    },
    {
      "from": "005dfeb4"
    },
    {
      "from": "005dff18"
    },
    {
      "from": "005dff7a"
    },
    {
      "from": "00588758"
    },
    {
      "from": "00588806"
    },
    {
      "from": "005775a2"
    },
    {
      "from": "005932d7"
    },
    {
      "from": "00591834"
    },
    {
      "from": "00591a4f"
    },
    {
      "from": "00591ab7"
    },
    {
      "from": "005b3981"
    },
    {
      "from": "005b399f"
    },
    {
      "from": "005c9e34"
    },
    {
      "from": "005df026"
    },
    {
      "from": "005df058"
    },
    {
      "from": "005af90d"
    },
    {
      "from": "005b07c7"
    },
    {
      "from": "005b0dd2"
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
