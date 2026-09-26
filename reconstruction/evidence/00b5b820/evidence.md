# Evidence 0x00b5b820

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `0639a1c2956670c0999a14308473cadfdfd443eb4d52600ae8e20f1f7ed88509`

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
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
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
  "content_sha256": "82cd93492a3a0bbfcfa70a61db0cf258b95f29dfc9c4cc5867cce13f0ce4f8bc",
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
        "obs-0006"
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
        "obs-0006"
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
        "obs-0006"
      ],
      "claim": "the function is byte-identical under all four conventions",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0006"
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
        "obs-0004",
        "obs-0006"
      ],
      "claim": "the function can reach a caller by transferring out of the listing, so the path that actually returns was never observed",
      "confidence": "UNKNOWN",
      "id": "T2",
      "value": {
        "form": "epilogue_then_jmp"
      }
    },
    {
      "based_on": [
        "obs-0006"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0006"
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
      "at": "0x00b5b820",
      "id": "obs-0001",
      "index": 0,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00b3d320",
      "target": "0x00b3d320"
    },
    {
      "at": "0x00b5b829",
      "count": 1,
      "first_use": 3,
      "first_write_index": 5,
      "id": "obs-0002",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV ECX,EAX",
      "reg": "EAX"
    },
    {
      "at": "0x00b5b829",
      "definite": true,
      "id": "obs-0003",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,EAX",
      "reg": "ECX",
      "write_kind": "reg"
    },
    {
      "at": "0x00b5b82b",
      "id": "obs-0004",
      "index": 4,
      "kind": "UNCOND_TRANSFER_OUT",
      "raw": "JMP 0x00ff35d0",
      "target": "0x00ff35d0"
    },
    {
      "at": "0x00b5b830",
      "definite": true,
      "id": "obs-0005",
      "index": 5,
      "kind": "REG_WRITE",
      "raw": "OR EAX,0xffffffff",
      "reg": "EAX",
      "write_kind": "arith"
    },
    {
      "at": "0x00b5b833",
      "form": "RET",
      "id": "obs-0006",
      "imm": null,
      "index": 6,
      "kind": "RET",
      "raw": "RET"
    }
  ],
  "parse": {
    "declared_count": 7,
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
    "form": "epilogue_then_jmp",
    "present": true,
    "target": "0x00ff35d0"
  },
  "target
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
"\nundefined4 FUN_00b5b820(void)\n\n{\n  int iVar1;\n  undefined4 uVar2;\n  \n  iVar1 = FUN_00b3d320();\n  if (iVar1 != 0) {\n    uVar2 = FUN_00ff35d0();\n    return uVar2;\n  }\n  return 0xffffffff;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 7,
  "instructions": [
    {
      "address": "00b5b820",
      "instruction": "CALL 0x00b3d320"
    },
    {
      "address": "00b5b825",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00b5b827",
      "instruction": "JZ 0x00b5b830"
    },
    {
      "address": "00b5b829",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00b5b82b",
      "instruction": "JMP 0x00ff35d0"
    },
    {
      "address": "00b5b830",
      "instruction": "OR EAX,0xffffffff"
    },
    {
      "address": "00b5b833",
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
  "body_end": "00b5b833",
  "body_span_bytes": 20,
  "body_start": "00b5b820",
  "callees": [
    "FUN_00b3d320",
    "FUN_00ff35d0"
  ],
  "callers": [
    "FUN_00d1cdf0",
    "FUN_00ad2200",
    "FUN_00e03f80",
    "FUN_00b2f350",
    "FUN_00ad25e0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00b5b820",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "uVar2",
      "storage": "register:00000000:4",
      "type": "undefined4"
    },
    {
      "name": "iVar1",
      "storage": "register:00000000:4",
      "type": "int"
    }
  ],
  "locals_count": 2,
  "mode": "live",
  "name": "FUN_00b5b820",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x75b820",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00b5b820(void)",
  "size_bytes": 20,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00b5b820",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 7,
  "xrefs": [
    {
      "from": "00ad25fb"
    },
    {
      "from": "00b2f370"
    },
    {
      "from": "00ad22b3"
    },
    {
      "from": "00d1cffc"
    },
    {
      "from": "00d1d043"
    },
    {
      "from": "00d19e31"
    },
    {
      "from": "00e04085"
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
