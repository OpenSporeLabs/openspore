# Evidence 0x00feba90

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `b517097ec308eda5b630ca12159c499d57e95f82d7b2748f0f338226839ab330`

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
    "return_semantics": "pointer_like_in_EAX",
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
  "content_sha256": "4a29a5e5c80e891ef2491cbd40a48f0bfa3bfa6ab4e700dca7f2d6a97cf6eb44",
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
        "obs-0003"
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
          24
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0002",
        "obs-0003"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0003"
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
        "obs-0003"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0003"
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
      "at": "0x00feba90",
      "count": 1,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV AL,byte ptr [ECX + 0x18]",
      "reg": "ECX"
    },
    {
      "at": "0x00feba90",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV AL,byte ptr [ECX + 0x18]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00feba93",
      "form": "RET",
      "id": "obs-0003",
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
    "confidence": "INFERRED",
    "distinct_offsets": 1,
    "max_offset": 24,
    "offsets": [
      24
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
    "va": "0x00feba90"
  },
  "variadic": "UNKNOWN",
  "verdict": "ABI_INFERRED"
}
```

## abi_derived

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
    "return_semantics": "pointer_like_in_EAX",
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
  "content_sha256": "4a29a5e5c80e891ef2491cbd40a48f0bfa3bfa6ab4e700dca7f2d6a97cf6eb44",
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
        "obs-0003"
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
          24
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0002",
        "obs-0003"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0003"
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
        "obs-0003"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0003"
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
      "at": "0x00feba90",
      "count": 1,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV AL,byte ptr [ECX + 0x18]",
      "reg": "ECX"
    },
    {
      "at": "0x00feba90",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV AL,byte ptr [ECX + 0x18]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00feba93",
      "form": "RET",
      "id": "obs-0003",
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
    "confidence": "INFERRED",
    "distinct_offsets": 1,
    "max_offset": 24,
    "offsets": [
      24
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
    "va": "0x00feba90"
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

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: ``

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 2,
  "instructions": [
    {
      "address": "00feba90",
      "instruction": "MOV AL,byte ptr [ECX + 0x18]"
    },
    {
      "address": "00feba93",
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
  "body_end": "00feba93",
  "body_span_bytes": 4,
  "body_start": "00feba90",
  "callees": [],
  "callers": [
    "FUN_00fdabf0",
    "FUN_00c2e520",
    "FUN_00d32fd0",
    "FUN_00dc9430",
    "FUN_00bfcdd0",
    "FUN_00ca8120",
    "FUN_00c830f0",
    "FUN_00bfc600",
    "FUN_00d30ee0",
    "FUN_00ca96b0",
    "FUN_00d54940",
    "FUN_00bd8300",
    "FUN_00cc6910",
    "FUN_0104bd50",
    "FUN_01050070",
    "FUN_00bd82c0",
    "FUN_00c478b0",
    "FUN_00bcece0",
    "FUN_00cbbdc0",
    "FUN_00cba690",
    "FUN_00bcc800",
    "FUN_00c9b740",
    "FUN_00fec8a0",
    "FUN_00c2e9b0",
    "FUN_00bf1790",
    "FUN_00c9d1c0",
    "FUN_01039520",
    "FUN_00c07480",
    "FUN_00c389f0",
    "FUN_00e9cf30",
    "FUN_00c372b0",
    "FUN_00be3de0",
    "FUN_00c37e60",
    "FUN_0100a080",
    "FUN_00bcd250",
    "FUN_00c9afb0",
    "FUN_00c6d7c0",
    "FUN_00c9a960",
    "FUN_00cc1c30",
    "FUN_00ffc8d0",
    "FUN_00c9d160",
    "FUN_00c9ef60",
    "FUN_00bfc640",
    "FUN_00d5fb60",
    "FUN_0104ea80",
    "FUN_00c9a080",
    "FUN_010504a0",
    "FUN_00beabb0",
    "FUN_01060df0",
    "FUN_00bd8280",
    "FUN_0104ca20",
    "FUN_0104fc10",
    "FUN_00c9b6d0",
    "FUN_00db6130",
    "FUN_00c30b30",
    "FUN_00c05810",
    "FUN_00d32df0",
    "FUN_00c7ee50",
    "FUN_0105d200",
    "FUN_01050a60",
    "FUN_00b638d0",
    "FUN_00c0d440",
    "FUN_00d35190",
    "FUN_00c9ef20",
    "FUN_00d48010",
    "FUN_01051090",
    "FUN_00ae6240",
    "FUN_00c75650",
    "FUN_00d2bd00",
    "FUN_00ae2f70",
    "FUN_00fec4e0",
    "FUN_01016ad0",
    "FUN_01000000",
    "FUN_00fec900",
    "FUN_00bd8240",
    "FUN_0104ff10",
    "FUN_01003df0",
    "FUN_00ca0340",
    "FUN_00beb1c0"
  ],
  "classification": "stub",
  "dispatch": null,
  "entry_point": "00feba90",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00feba90",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xbeba90",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00feba90(void)",
  "size_bytes": 4,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00feba90",
  "vtables": {
    "referenced_by_vtables": [
      "0x01453998",
      "0x01459844",
      "0x014599e8",
      "0x01414918"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 100,
  "xrefs": [
    {
      "from": "00bfc60c"
    },
    {
      "from": "00c30b36"
    },
    {
      "from": "00c75673"
    },
    {
      "from": "00d6092f"
    },
    {
      "from": "00bd8249"
    },
    {
      "from": "00bd8289"
    },
    {
      "from": "00bd82cc"
    },
    {
      "from": "00ae315e"
    },
    {
      "from": "00ae6426"
    },
    {
      "from": "00bcc809"
    },
    {
      "from": "00bcd259"
    },
    {
      "from": "00be3ded"
    },
    {
      "from": "00be3dfc"
    },
    {
      "from": "00be3e8e"
    },
    {
      "from": "00be3e99"
    },
    {
      "from": "00be3ec3"
    },
    {
      "from": "00be3ece"
    },
    {
      "from": "00beb44a"
    },
    {
      "from": "00beabc2"
    },
    {
      "from": "00ca812c"
    },
    {
      "from": "00c37f49"
    },
    {
      "from": "00fec8dc"
    },
    {
      "from": "00fec93c"
    },
    {
      "from": "01000112"
    },
    {
      "from": "010395d9"
    },
    {
      "from": "0104bd5f"
    },
    {
      "from": "0104fc66"
    },
    {
      "from": "01050217"
    },
    {
      "from": "00c38a2f"
    },
    {
      "from": "010505c2"
    },
    {
      "from": "0104eaac"
    },
    {
      "from": "00c9a085"
    },
    {
      "from": "00ffc8de"
    },
    {
      "from": "00c2e9b6"
    },
    {
      "from": "00bd830e"
    },
    {
      "from": "00bf17a6"
    },
    {
      "from": "0104ff39"
    },
    {
      "from": "0104ff7d"
    },
    {
      "from": "00bfc64d"
    },
    {
      "from": "00bfce8c"
    },
    {
      "from": "00c0d487"
    },
    {
      "from": "00c0d4b7"
    },
    {
      "from": "00c0799b"
    },
    {
      "from": "00c0582a"
    },
    {
      "from": "00c2e529"
    },
    {
      "from": "00c4793d"
    },
    {
      "from": "00c47966"
    },
    {
      "from": "00c6d856"
    },
    {
      "from": "00c6dd08"
    },
    {
      "from": "00c6df35"
    },
    {
      "from": "00c6df6e"
    },
    {
      "from": "00c6e058"
    },
    {
      "from": "00c7ee6c"
    },
    {
      "from": "00c835e7"
    },
    {
      "from": "00c9a96c"
    },
    {
      "from": "00c9d16c"
    },
    {
      "from": "00c9ef2c"
    },
    {
      "from": "00c9ef6d"
    },
    {
      "from": "00ca034c"
    },
    {
      "from": "00cbbdd1"
    },
    {
      "from": "00cc6e80"
    },
    {
      "from": "00c9b6de"
    },
    {
      "from": "00c9b624"
    },
    {
      "from": "00c9d1cc"
    },
    {
      "from": "00c9b74f"
    },
    {
      "from": "00d30f0a"
    },
    {
      "from": "00d2bd23"
    },
    {
      "from": "00d2be2f"
    },
    {
      "from": "00d32e8c"
    },
    {
      "from": "00d484e6"
    },
    {
      "from": "00d5494f"
    },
    {
      "from": "00db6162"
    },
    {
      "from": "00dc9444"
    },
    {
      "from": "00ca973b"
    },
    {
      "from": "00fdac15"
    },
    {
      "from": "010510b5"
    },
    {
      "from": "00fec502"
    },
    {
      "from": "00fec554"
    },
    {
      "from":
[TRUNCATED]
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
