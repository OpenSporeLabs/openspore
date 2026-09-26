# Evidence 0x00ff0870

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `f601687ea201b108c0e7bfa95a6ba7a7cba5dfa8e431315728e65cebff25f7f9`

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
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
    "saved_registers": [
      "ESI"
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
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "4075db74855eed95348293138c507527f44e0f1080182fb00be115c06e9f78db",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall",
      "__fastcall"
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
        "obs-0009"
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
        "obs-0001",
        "obs-0002"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          36,
          40
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0002",
        "obs-0009"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0009"
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
        "obs-0009"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0009"
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
      "at": "0x00ff0870",
      "count": 4,
      "first_use": 0,
      "first_write_index": 4,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOVZX EAX,byte ptr [ECX + 0x28]",
      "reg": "EAX"
    },
    {
      "at": "0x00ff0870",
      "count": 2,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOVZX EAX,byte ptr [ECX + 0x28]",
      "reg": "ECX"
    },
    {
      "at": "0x00ff0874",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,EAX",
      "reg": "EDX",
      "write_kind": "reg"
    },
    {
      "at": "0x00ff0876",
      "count": 5,
      "first_use": 2,
      "first_write_index": 1,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "SHR EDX,0x1",
      "reg": "EDX"
    },
    {
      "at": "0x00ff087e",
      "definite": true,
      "id": "obs-0005",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "SUB EAX,EDX",
      "reg": "EAX",
      "write_kind": "arith"
    },
    {
      "at": "0x00ff0882",
      "count": 5,
      "first_use": 6,
      "first_write_index": 12,
      "id": "obs-0006",
      "index": 6,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00ff0896",
      "definite": true,
      "id": "obs-0007",
      "index": 12,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,EDX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00ff08ae",
      "id": "obs-0008",
      "index": 19,
      "kind": "REG_RESTORE",
      "raw": "POP ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00ff08af",
      "form": "RET",
      "id": "obs-0009",
      "imm": null,
      "index": 20,
      "kind": "RET",
      "raw": "RET"
    }
  ],
  "parse": {
    "declared_count": 21,
    "degraded": false,
    "esp_unresolved": false,
    "flow_complete": true,
    "frame": {
      "and_esp": null,
      "ebp_is_general_register": false,
      "fp": false,
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": false,
      "push_ebp_at": null,
      "sub": null
    },
    "layout": "json_instruction_list",
    "local_extent": 0,
    "unparsed": 0
  },
  "receiver": {
    "bounds_only": true,
    "confidence": "INFERRED",
    "distinct_offsets": 2,
    "max_offset": 40,
    "offsets": [
      36,
      40
    ],
    "present": true,
    "register": "ECX",
    "shape": "R-DIRECT",
    "written_through": 0
  },
  "return": {
    "aggregate_evidence": {
      "bulk_write": false
    },
    "confidence": "INFERRED",
    "register": "EAX",
    "register_class": "integral",
    "type": null,
    "void_possible": false
  },
  "schema": "openspore-abi-inference-1",
  "seh_or_cookie_frame": false,
  "sret": {
    "ambiguity": null,
    "basis": "entry slot 0 is
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
"\nint __fastcall FUN_00ff0870(int param_1)\n\n{\n  uint uVar1;\n  \n  uVar1 = (uint)*(byte *)(param_1 + 0x28) - (*(byte *)(param_1 + 0x28) >> 1 & 0x55555555);\n  uVar1 = (uVar1 >> 2 & 0x33333333) + (uVar1 & 0x33333333);\n  return *(int *)(param_1 + 0x24) - (((uVar1 >> 4) + uVar1 & 0xf0f0f0f) * 0x1010101 >> 0x18);\n}\n\n"
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
      "address": "00ff0870",
      "instruction": "MOVZX EAX,byte ptr [ECX + 0x28]"
    },
    {
      "address": "00ff0874",
      "instruction": "MOV EDX,EAX"
    },
    {
      "address": "00ff0876",
      "instruction": "SHR EDX,0x1"
    },
    {
      "address": "00ff0878",
      "instruction": "AND EDX,0x55555555"
    },
    {
      "address": "00ff087e",
      "instruction": "SUB EAX,EDX"
    },
    {
      "address": "00ff0880",
      "instruction": "MOV EDX,EAX"
    },
    {
      "address": "00ff0882",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00ff0883",
      "instruction": "SHR EDX,0x2"
    },
    {
      "address": "00ff0886",
      "instruction": "AND EAX,0x33333333"
    },
    {
      "address": "00ff088b",
      "instruction": "AND EDX,0x33333333"
    },
    {
      "address": "00ff0891",
      "instruction": "ADD EDX,EAX"
    },
    {
      "address": "00ff0893",
      "instruction": "MOV EAX,dword ptr [ECX + 0x24]"
    },
    {
      "address": "00ff0896",
      "instruction": "MOV ESI,EDX"
    },
    {
      "address": "00ff0898",
      "instruction": "SHR ESI,0x4"
    },
    {
      "address": "00ff089b",
      "instruction": "ADD ESI,EDX"
    },
    {
      "address": "00ff089d",
      "instruction": "AND ESI,0xf0f0f0f"
    },
    {
      "address": "00ff08a3",
      "instruction": "IMUL ESI,ESI,0x1010101"
    },
    {
      "address": "00ff08a9",
      "instruction": "SHR ESI,0x18"
    },
    {
      "address": "00ff08ac",
      "instruction": "SUB EAX,ESI"
    },
    {
      "address": "00ff08ae",
      "instruction": "POP ESI"
    },
    {
      "address": "00ff08af",
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
  "body_end": "00ff08af",
  "body_span_bytes": 64,
  "body_start": "00ff0870",
  "callees": [],
  "callers": [
    "FUN_00bbe740",
    "FUN_00c70380",
    "FUN_00c70150",
    "FUN_00c702f0",
    "FUN_00c635c0",
    "FUN_00c5c860"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "00ff0870",
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
      "type": "uint"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int"
    }
  ],
  "locals_count": 2,
  "mode": "live",
  "name": "FUN_00ff0870",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xbf0870",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00ff0870(void)",
  "size_bytes": 64,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00ff0870",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 9,
  "xrefs": [
    {
      "from": "00c701e0"
    },
    {
      "from": "00c7034e"
    },
    {
      "from": "00c703e0"
    },
    {
      "from": "00bbe7c9"
    },
    {
      "from": "00c5cc01"
    },
    {
      "from": "00c636f4"
    },
    {
      "from": "00bbc639"
    },
    {
      "from": "00bbc650"
    },
    {
      "from": "00c61adb"
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
