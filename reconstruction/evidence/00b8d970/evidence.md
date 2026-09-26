# Evidence 0x00b8d970

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `b15e21842fa23feb947dcdf100f82e4c7f3b5f6ddb7715562059e7288f6d8773`

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
    "return_semantics": "unclassified_in_EAX",
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
  "content_sha256": "b573a56757cf1233fd8d9311a03ca84af8aa63262cfb020059bd77363b0d926c",
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
        "obs-0004"
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
          44
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0002",
        "obs-0004"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0004"
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
        "obs-0004"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0004"
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
      "at": "0x00b8d970",
      "count": 1,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ECX + 0x2c]",
      "reg": "ECX"
    },
    {
      "at": "0x00b8d970",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ECX + 0x2c]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00b8d973",
      "count": 1,
      "first_use": 1,
      "first_write_index": 0,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "SHR EAX,0x8",
      "reg": "EAX"
    },
    {
      "at": "0x00b8d978",
      "form": "RET",
      "id": "obs-0004",
      "imm": null,
      "index": 3,
      "kind": "RET",
      "raw": "RET"
    }
  ],
  "parse": {
    "declared_count": 4,
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
    "distinct_offsets": 1,
    "max_offset": 44,
    "offsets": [
      44
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
    "register_class": "aggregate_unknown",
    "type": null,
    "void_possible": false
  },
  "schema": "openspore-abi-inference-1",
  "seh_or_cookie_frame": false,
  "sret": {
    "ambiguity": null,
    "basis": "entry slot 0 is not written through a pointer; DERIVED absence is weak, a struct filled through another alias would be missed",
    "candidates": null,
    "confidence": "APPROXIMATION",
    "eax_holds_slot0_at_ret": null,
    "hypothesis_confidence": null,
    "present": false,
    "slot": null,
    "this_interaction": null
  },
  "stack_arguments": {
    "confidence": "APPROXIMATION",
    "derived_slots": 0,
    "gaps": 0,
    "not_complete": false,
    "observed_slots": 0,
    "slots": [],
    "total_bytes": 0,
    "widths_ambiguous": false
  },
  "tail_call": {
    "after_frame_setup": false,
    "form": null,
    "present": false,
    "target": null
  },
  "target": {
    "address_available": true,
    "image_base": "0x00400000",
    "instructions": 4,
    "syntax": "intel",
    "va": "0x00b8d970"
  },
  "variadic": "UNKNOWN",
  "verdict": "ABI_INFERRED"
}
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
"\nuint __fastcall FUN_00b8d970(int param_1)\n\n{\n  return *(uint *)(param_1 + 0x2c) >> 8 & 0xffffff01;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 4,
  "instructions": [
    {
      "address": "00b8d970",
      "instruction": "MOV EAX,dword ptr [ECX + 0x2c]"
    },
    {
      "address": "00b8d973",
      "instruction": "SHR EAX,0x8"
    },
    {
      "address": "00b8d976",
      "instruction": "AND AL,0x1"
    },
    {
      "address": "00b8d978",
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
  "body_end": "00b8d978",
  "body_span_bytes": 9,
  "body_start": "00b8d970",
  "callees": [],
  "callers": [
    "FUN_01068970",
    "FUN_00bba990",
    "FUN_00e97bf0",
    "FUN_00c44d00",
    "FUN_00fde3e0",
    "FUN_00c8c5d0",
    "FUN_01072d40",
    "FUN_0103aa00",
    "FUN_00fdd210",
    "FUN_00c8b820",
    "FUN_010021a0",
    "FUN_00c38270",
    "FUN_0100a160",
    "FUN_00c8c420",
    "FUN_00c8c9d0",
    "FUN_00c8b920",
    "FUN_0106ba00",
    "FUN_01069aa0",
    "FUN_00bba790",
    "FUN_00c8bb00",
    "FUN_00c8ba00",
    "FUN_00c8c7f0",
    "FUN_010091d0",
    "FUN_00c8d060",
    "FUN_00c484e0"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "00b8d970",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int"
    }
  ],
  "locals_count": 1,
  "mode": "live",
  "name": "FUN_00b8d970",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x78d970",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00b8d970(void)",
  "size_bytes": 9,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00b8d970",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 31,
  "xrefs": [
    {
      "from": "00bba811"
    },
    {
      "from": "00c8b951"
    },
    {
      "from": "0103aa56"
    },
    {
      "from": "00c8bb57"
    },
    {
      "from": "00c8c656"
    },
    {
      "from": "00c8ca8e"
    },
    {
      "from": "00bba9d4"
    },
    {
      "from": "00fde8e5"
    },
    {
      "from": "0106bb77"
    },
    {
      "from": "00c8b873"
    },
    {
      "from": "00c8c844"
    },
    {
      "from": "0106898d"
    },
    {
      "from": "00c38295"
    },
    {
      "from": "00fdd293"
    },
    {
      "from": "00c4852f"
    },
    {
      "from": "00c48548"
    },
    {
      "from": "00c8d0d0"
    },
    {
      "from": "00c8c46d"
    },
    {
      "from": "00e97e50"
    },
    {
      "from": "01069d8f"
    },
    {
      "from": "010092cb"
    },
    {
      "from": "010092e5"
    },
    {
      "from": "0100a24a"
    },
    {
      "from": "010733c4"
    },
    {
      "from": "010734f4"
    },
    {
      "from": "00c44d07"
    },
    {
      "from": "00c56f3f"
    },
    {
      "from": "00c56f95"
    },
    {
      "from": "01002501"
    },
    {
      "from": "00c8ba31"
    },
    {
      "from": "01025ad7"
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
