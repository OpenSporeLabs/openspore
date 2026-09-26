# Evidence 0x00c0b780

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `65a4276c36f1a61617e2291666ba94f3756f44deaec51195d79a28632e72489e`

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
  "content_sha256": "9ae248f80816c527cdecbf45d509eb8f9797473b71c68966bfa0a07defab9f7d",
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
        "obs-0005"
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
        "obs-0002",
        "obs-0003",
        "obs-0004"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          2848,
          4392
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0002",
        "obs-0003",
        "obs-0004",
        "obs-0005"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0005"
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
        "obs-0005"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0005"
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
      "at": "0x00c0b780",
      "count": 2,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ECX + 0xb20]",
      "reg": "ECX"
    },
    {
      "at": "0x00c0b780",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ECX + 0xb20]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00c0b786",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "XOR ECX,ECX",
      "reg": "ECX",
      "write_kind": "zero"
    },
    {
      "at": "0x00c0b788",
      "count": 2,
      "first_use": 2,
      "first_write_index": 0,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "CMP ECX,dword ptr [EAX + 0x608]",
      "reg": "EAX"
    },
    {
      "at": "0x00c0b792",
      "form": "RET",
      "id": "obs-0005",
      "imm": null,
      "index": 5,
      "kind": "RET",
      "raw": "RET"
    }
  ],
  "parse": {
    "declared_count": 6,
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
    "max_offset": 4392,
    "offsets": [
      2848,
      4392
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
    "image_ba
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
"\nbool __fastcall FUN_00c0b780(int param_1)\n\n{\n  return *(int *)(*(int *)(param_1 + 0xb20) + 0x608) != 0;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 6,
  "instructions": [
    {
      "address": "00c0b780",
      "instruction": "MOV EAX,dword ptr [ECX + 0xb20]"
    },
    {
      "address": "00c0b786",
      "instruction": "XOR ECX,ECX"
    },
    {
      "address": "00c0b788",
      "instruction": "CMP ECX,dword ptr [EAX + 0x608]"
    },
    {
      "address": "00c0b78e",
      "instruction": "SBB EAX,EAX"
    },
    {
      "address": "00c0b790",
      "instruction": "NEG EAX"
    },
    {
      "address": "00c0b792",
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
  "body_end": "00c0b792",
  "body_span_bytes": 19,
  "body_start": "00c0b780",
  "callees": [],
  "callers": [
    "FUN_00d5f780",
    "FUN_00dbc7a0",
    "FUN_00d8dcc0",
    "FUN_00d8f560",
    "FUN_00c02eb0",
    "FUN_00ba27b0",
    "FUN_00d71060",
    "FUN_00da8a40",
    "FUN_00e8bf20",
    "FUN_00c042e0",
    "FUN_00d581b0",
    "FUN_00e8cd30",
    "FUN_00d74060",
    "FUN_00d3cdc0",
    "FUN_00d2c000",
    "FUN_00c24f40",
    "FUN_00d8cab0",
    "FUN_01030fd0"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "00c0b780",
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
  "name": "FUN_00c0b780",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x80b780",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00c0b780(void)",
  "size_bytes": 19,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00c0b780",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 27,
  "xrefs": [
    {
      "from": "00d5f85a"
    },
    {
      "from": "00d5fb1a"
    },
    {
      "from": "00d582cc"
    },
    {
      "from": "00c04426"
    },
    {
      "from": "00ba27fa"
    },
    {
      "from": "00ba2815"
    },
    {
      "from": "00ba2820"
    },
    {
      "from": "00ba284b"
    },
    {
      "from": "00ba2871"
    },
    {
      "from": "00c02eb3"
    },
    {
      "from": "00d3d073"
    },
    {
      "from": "00d3d0a2"
    },
    {
      "from": "00d2c144"
    },
    {
      "from": "00d8cb3e"
    },
    {
      "from": "00d8de7c"
    },
    {
      "from": "00d8f66a"
    },
    {
      "from": "00da8a76"
    },
    {
      "from": "00e8bfd3"
    },
    {
      "from": "00e8ce34"
    },
    {
      "from": "010315f7"
    },
    {
      "from": "00c2515b"
    },
    {
      "from": "00d71419"
    },
    {
      "from": "00d714ef"
    },
    {
      "from": "00d71590"
    },
    {
      "from": "00d74a40"
    },
    {
      "from": "00d752a1"
    },
    {
      "from": "00dbd315"
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
