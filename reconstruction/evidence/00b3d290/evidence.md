# Evidence 0x00b3d290

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `fc8f4f201205eaf26f028533de7786d5556e3bafb2791baf9a64262e7072155e`

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
    "return_semantics": "pointer_like_in_EAX",
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
  "content_sha256": "edb7a66fb88971b51bc7a5d11988dc9bca42f4908681ba9a43e1583d32524634",
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
        "obs-0002"
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
        "obs-0002"
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
        "obs-0002"
      ],
      "claim": "the function is byte-identical under all four conventions",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0002"
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
        "obs-0002"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0002"
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
      "at": "0x00b3d290",
      "definite": true,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,[0x0167ead4]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00b3d295",
      "form": "RET",
      "id": "obs-0002",
      "imm": null,
      "index": 1,
      "kind": "RET",
      "raw": "RET"
    }
  ],
  "parse": {
    "declared_count": 2,
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
    "register_class": "pointer_like",
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
    "instructions": 2,
    "syntax": "intel",
    "va": "0x00b3d290"
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
"\nundefined4 FUN_00b3d290(void)\n\n{\n  return DAT_0167ead4;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 2,
  "instructions": [
    {
      "address": "00b3d290",
      "instruction": "MOV EAX,[0x0167ead4]"
    },
    {
      "address": "00b3d295",
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
  "body_end": "00b3d295",
  "body_span_bytes": 6,
  "body_start": "00b3d290",
  "callees": [],
  "callers": [
    "FUN_00c43e40",
    "FUN_00ac5490",
    "FUN_00b5ce70",
    "FUN_00cad880",
    "FUN_00b32aa0",
    "FUN_00cf2520",
    "FUN_00b33350",
    "FUN_00bf5cb0",
    "FUN_00ca81d0",
    "FUN_00cacbe0",
    "FUN_00d1c400",
    "FUN_00b33540",
    "FUN_0100a960",
    "FUN_00b32e80",
    "FUN_00b8c330",
    "FUN_00db86a0",
    "FUN_00be7bf0",
    "FUN_00c1c310",
    "FUN_00cf3bf0",
    "FUN_00b32c60",
    "FUN_00dc7e00",
    "FUN_00c41ff0",
    "FUN_00c41f30",
    "FUN_00ac5330",
    "FUN_00dce970",
    "FUN_00ac5430",
    "FUN_00ac6960",
    "FUN_00ba1590",
    "FUN_00cf30b0",
    "FUN_00b33130",
    "FUN_00c41360",
    "FUN_00b9caa0"
  ],
  "classification": "stub",
  "dispatch": null,
  "entry_point": "00b3d290",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00b3d290",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x73d290",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00b3d290(void)",
  "size_bytes": 6,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00b3d290",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 38,
  "xrefs": [
    {
      "from": "00ac5333"
    },
    {
      "from": "00ac543f"
    },
    {
      "from": "00ac549f"
    },
    {
      "from": "00ac69e5"
    },
    {
      "from": "00bf67a5"
    },
    {
      "from": "00bf6a54"
    },
    {
      "from": "00b32e9b"
    },
    {
      "from": "00b3314e"
    },
    {
      "from": "00b3355a"
    },
    {
      "from": "0100ad6b"
    },
    {
      "from": "00b32aac"
    },
    {
      "from": "00b32ab8"
    },
    {
      "from": "00b32c7b"
    },
    {
      "from": "00b32c87"
    },
    {
      "from": "00b3335c"
    },
    {
      "from": "00db8936"
    },
    {
      "from": "00db897f"
    },
    {
      "from": "00b5cf3f"
    },
    {
      "from": "00b5cf94"
    },
    {
      "from": "00b8ca55"
    },
    {
      "from": "00be7c01"
    },
    {
      "from": "00c41508"
    },
    {
      "from": "00c43ead"
    },
    {
      "from": "00c1c5a1"
    },
    {
      "from": "00c41fd6"
    },
    {
      "from": "00c420b1"
    },
    {
      "from": "00ca830d"
    },
    {
      "from": "00cacc4e"
    },
    {
      "from": "00cadac9"
    },
    {
      "from": "00b9d140"
    },
    {
      "from": "00ba175d"
    },
    {
      "from": "00cf30db"
    },
    {
      "from": "00cf3d01"
    },
    {
      "from": "00d1c4fe"
    },
    {
      "from": "00dce983"
    },
    {
      "from": "00cf261b"
    },
    {
      "from": "00dc7de0"
    },
    {
      "from": "00dc7e13"
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
