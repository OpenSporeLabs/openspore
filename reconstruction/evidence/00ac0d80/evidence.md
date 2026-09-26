# Evidence 0x00ac0d80

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `d4fff3b937ff5fc80081ceda649d8170e9a6f51c7c25ed3acaeeb7bda291a37b`

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
      }
    ],
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
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
      }
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "receiver_not_determinable: ecx_reassigned_before_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_reassigned_before_deref), and the convention rule that would apply discriminates on receiver absence"
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
  "content_sha256": "40d7f803c65bf8f5227e341ea069a1c99ab103ed28687299af1dfa729a0159cc",
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
        "obs-0016"
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
        "obs-0002",
        "obs-0004",
        "obs-0006"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "INFERRED",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 3,
        "total_bytes": 12
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007",
        "obs-0009",
        "obs-0010"
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
        "obs-0009",
        "obs-0010"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_reassigned_before_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0016"
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
        "obs-0016"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0016"
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
      "at": "0x00ac0d80",
      "count": 3,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "ESP"
    },
    {
      "at": "0x00ac0d80",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0002",
      "index": 0,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00ac0d80",
      "definite": true,
      "id": "obs-0003",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00ac0d84",
      "base": "ESP",
      "disp": 8,
      "id": "obs-0004",
      "index": 1,
      "key": 8,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EDX,dword ptr
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
"\nvoid FUN_00ac0d80(int *param_1,int *param_2,int *param_3)\n\n{\n  if (param_1 != param_2) {\n    do {\n      if (((*param_1 == *param_3) && (param_1[1] == param_3[1])) && (param_1[2] == param_3[2])) {\n        return;\n      }\n      param_1 = param_1 + 3;\n    } while (param_1 != param_2);\n  }\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 22,
  "instructions": [
    {
      "address": "00ac0d80",
      "instruction": "MOV EAX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "00ac0d84",
      "instruction": "MOV EDX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "00ac0d88",
      "instruction": "CMP EAX,EDX"
    },
    {
      "address": "00ac0d8a",
      "instruction": "JZ 0x00ac0db1"
    },
    {
      "address": "00ac0d8c",
      "instruction": "MOV ECX,dword ptr [ESP + 0xc]"
    },
    {
      "address": "00ac0d90",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00ac0d91",
      "instruction": "MOV ESI,dword ptr [ECX]"
    },
    {
      "address": "00ac0d93",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00ac0d94",
      "instruction": "CMP dword ptr [EAX],ESI"
    },
    {
      "address": "00ac0d96",
      "instruction": "JNZ 0x00ac0da8"
    },
    {
      "address": "00ac0d98",
      "instruction": "MOV EDI,dword ptr [EAX + 0x4]"
    },
    {
      "address": "00ac0d9b",
      "instruction": "CMP EDI,dword ptr [ECX + 0x4]"
    },
    {
      "address": "00ac0d9e",
      "instruction": "JNZ 0x00ac0da8"
    },
    {
      "address": "00ac0da0",
      "instruction": "MOV EDI,dword ptr [EAX + 0x8]"
    },
    {
      "address": "00ac0da3",
      "instruction": "CMP EDI,dword ptr [ECX + 0x8]"
    },
    {
      "address": "00ac0da6",
      "instruction": "JZ 0x00ac0daf"
    },
    {
      "address": "00ac0da8",
      "instruction": "ADD EAX,0xc"
    },
    {
      "address": "00ac0dab",
      "instruction": "CMP EAX,EDX"
    },
    {
      "address": "00ac0dad",
      "instruction": "JNZ 0x00ac0d94"
    },
    {
      "address": "00ac0daf",
      "instruction": "POP EDI"
    },
    {
      "address": "00ac0db0",
      "instruction": "POP ESI"
    },
    {
      "address": "00ac0db1",
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
  "body_end": "00ac0db1",
  "body_span_bytes": 50,
  "body_start": "00ac0d80",
  "callees": [],
  "callers": [
    "FUN_00c821b0",
    "FUN_00c70d40",
    "FUN_00c70d10",
    "FUN_01043fd0",
    "FUN_00c745d0",
    "FUN_00ff3d10",
    "FUN_0069e5d0",
    "FUN_00c74730",
    "FUN_00eef330",
    "FUN_00ba9d60",
    "FUN_00fe0160",
    "FUN_01004fc0"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "00ac0d80",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "param_3",
      "storage": "Stack[0xc]:4",
      "type": "int *"
    },
    {
      "name": "param_2",
      "storage": "Stack[0x8]:4",
      "type": "int *"
    },
    {
      "name": "param_1",
      "storage": "Stack[0x4]:4",
      "type": "int *"
    }
  ],
  "locals_count": 3,
  "mode": "live",
  "name": "FUN_00ac0d80",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x6c0d80",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00ac0d80(void)",
  "size_bytes": 50,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00ac0d80",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 14,
  "xrefs": [
    {
      "from": "00ba9edb"
    },
    {
      "from": "0069e61d"
    },
    {
      "from": "00c821de"
    },
    {
      "from": "00c745ff"
    },
    {
      "from": "00c7476e"
    },
    {
      "from": "01043ff4"
    },
    {
      "from": "00eef3b9"
    },
    {
      "from": "00fe0259"
    },
    {
      "from": "01004fe8"
    },
    {
      "from": "00ff3d1e"
    },
    {
      "from": "00ac0ef8"
    },
    {
      "from": "00b8fb98"
    },
    {
      "from": "00c70d2a"
    },
    {
      "from": "00c70d5a"
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
