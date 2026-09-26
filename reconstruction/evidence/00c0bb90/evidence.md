# Evidence 0x00c0bb90

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `935d6deebec522045815a8e5d65b03660221feae59a8a70cdfd4222de41a08fd`

## abi

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "abi": {
    "architecture": "x86-32",
    "receiver": false,
    "ret_form": "RET",
    "return_register": "ST0",
    "return_semantics": "float_or_x87_in_ST0",
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "unparsed_lines_present: 1 line(s) matched no grammar rule",
    "no_discriminator: no stack-argument read and no positive receiver evidence"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "bbdab4d44948cdb13d5b1d1db17d9228470425e6723c77ef7a54156347f807da",
  "conventions": {
    "ambiguities": [],
    "calling_convention": null,
    "candidate_conventions": [
      "__cdecl",
      "__stdcall",
      "__thiscall",
      "__fastcall"
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
        "obs-0005",
        "obs-0007"
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
        "obs-0007"
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
        "obs-0007"
      ],
      "claim": "the function is byte-identical under all four conventions",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0005",
        "obs-0007"
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
        "obs-0007"
      ],
      "claim": "the return value is carried in ST0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "ST0"
    }
  ],
  "observations": [
    {
      "at": "0x00c0bb90",
      "definite": true,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "ADD ECX,0x5a8",
      "reg": "ECX",
      "write_kind": "arith"
    },
    {
      "at": "0x00c0bb96",
      "id": "obs-0002",
      "index": 1,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00bfc490",
      "target": "0x00bfc490"
    },
    {
      "at": "0x00c0bba7",
      "id": "obs-0003",
      "index": 4,
      "kind": "UNPARSED",
      "raw": "FCOMIP ST0,ST1",
      "reason": "unknown_mnemonic"
    },
    {
      "at": "0x00c0bbad",
      "definite": true,
      "id": "obs-0004",
      "index": 7,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,0x1",
      "reg": "EAX",
      "write_kind": "imm"
    },
    {
      "at": "0x00c0bbb2",
      "form": "RET",
      "id": "obs-0005",
      "imm": null,
      "index": 8,
      "kind": "RET",
      "raw": "RET"
    },
    {
      "at": "0x00c0bbb3",
      "count": 1,
      "first_use": 9,
      "first_write_index": 7,
      "id": "obs-0006",
      "index": 9,
      "kind": "REG_READ",
      "raw": "XOR EAX,EAX",
      "reg": "EAX"
    },
    {
      "at": "0x00c0bbb5",
      "form": "RET",
      "id": "obs-0007",
      "imm": null,
      "index": 10,
      "kind": "RET",
      "raw": "RET"
    }
  ],
  "parse": {
    "declared_count": 11,
    "degraded": true,
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
    "unparsed": 1
  },
  "receiver": {
    "bounds_only": true,
    "confidence": "OBSERVED",
    "distinct_offsets": 0,
    "max_offset": null,
    "offsets": [],
    "present": false,
    "register": null,
    "shape": null,
    "written_through": 0
  },
  "return": {
    "aggregate_evidence": {
      "bulk_write": false
    },
    "confidence": "APPROXIMATION",
    "register": "ST0",
    "register_class": "float_or_x87",
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
    "instructions": 10,
    "syntax": "intel",
    "va": "0x00c0bb90"
  },
  "variadic": "UNKNOWN",
  "verdict": "ABI_UNKNOWN"
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
"\nundefined4 FUN_00c0bb90(void)\n\n{\n  float10 fVar1;\n  \n  fVar1 = (float10)FUN_00bfc490();\n  if (fVar1 * (float10)DAT_01687a00 < (float10)DAT_01687a10) {\n    return 1;\n  }\n  return 0;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 11,
  "instructions": [
    {
      "address": "00c0bb90",
      "instruction": "ADD ECX,0x5a8"
    },
    {
      "address": "00c0bb96",
      "instruction": "CALL 0x00bfc490"
    },
    {
      "address": "00c0bb9b",
      "instruction": "FMUL float ptr [0x01687a00]"
    },
    {
      "address": "00c0bba1",
      "instruction": "FLD float ptr [0x01687a10]"
    },
    {
      "address": "00c0bba7",
      "instruction": "FCOMIP ST0,ST1"
    },
    {
      "address": "00c0bba9",
      "instruction": "FSTP ST0"
    },
    {
      "address": "00c0bbab",
      "instruction": "JBE 0x00c0bbb3"
    },
    {
      "address": "00c0bbad",
      "instruction": "MOV EAX,0x1"
    },
    {
      "address": "00c0bbb2",
      "instruction": "RET"
    },
    {
      "address": "00c0bbb3",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "00c0bbb5",
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
  "body_end": "00c0bbb5",
  "body_span_bytes": 38,
  "body_start": "00c0bb90",
  "callees": [
    "FUN_00bfc490"
  ],
  "callers": [
    "FUN_00c0acd0",
    "FUN_00e07e70",
    "FUN_00d8f250",
    "FUN_00c0c630",
    "FUN_00c02df0"
  ],
  "classification": "wrapper",
  "dispatch": null,
  "entry_point": "00c0bb90",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "fVar1",
      "storage": "register:00001100:10",
      "type": "float10"
    }
  ],
  "locals_count": 1,
  "mode": "live",
  "name": "FUN_00c0bb90",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x80bb90",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00c0bb90(void)",
  "size_bytes": 38,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00c0bb90",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 6,
  "xrefs": [
    {
      "from": "00c0c891"
    },
    {
      "from": "00c02df3"
    },
    {
      "from": "00c02e18"
    },
    {
      "from": "00c0ad5f"
    },
    {
      "from": "00d8f351"
    },
    {
      "from": "00e08aea"
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
