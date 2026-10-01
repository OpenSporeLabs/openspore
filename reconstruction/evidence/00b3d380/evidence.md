# Evidence 0x00b3d380

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `646fbe16cfc222ec58a43759478bc1c9b8dd011da0bfbf87ab67eabb99bb269c`

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
  "content_sha256": "8d855f079abfb4e752a3477f4aac037ff6f4749e6dc5e0fa80896e5abda06a60",
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
      "at": "0x00b3d380",
      "definite": true,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,[0x0167eb04]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00b3d385",
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
    "va": "0x00b3d380"
  },
  "variadic": "UNKNOWN",
  "verdict": "ABI_UNKNOWN"
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
  "content_sha256": "8d855f079abfb4e752a3477f4aac037ff6f4749e6dc5e0fa80896e5abda06a60",
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
      "at": "0x00b3d380",
      "definite": true,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,[0x0167eb04]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00b3d385",
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
    "va": "0x00b3d380"
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

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00adf840"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ae00d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ae37c0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ae6240"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ae9f50"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00aebe90"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b19290"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b1dee0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b26af0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b26c90"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b5cc80"
  },
  {
    "name": "simulator_strategy_transition_00b5f040",
    "reconstructed": true,
    "va": "0x00b5f040"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b71ee0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ba5270"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ba5650"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ba57f0"
  }
]
```

## contradictions

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## decompilation

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json
"\nundefined4 FUN_00b3d380(void)\n\n{\n  return DAT_0167eb04;\n}\n\n"
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
      "address": "00b3d380",
      "instruction": "MOV EAX,[0x0167eb04]"
    },
    {
      "address": "00b3d385",
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

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "original_bytes": 13368,
  "preview": "{\n  \"abi\": {},\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-11-H4-HELPER-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"address_window_offset_005c65e0\",\n      \"va\": \"0x005c65e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"dispatch_key_00628450\",\n      \"va\": \"0x00628450\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"cycle_key_006286a0\",\n      \"va\": \"0x006286a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"release_child_0062c910\",\n      \"va\": \"0x0062c910\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d2a0\",\n      \"va\": \"0x00b3d2a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d300\",\n      \"va\": \"0x00b3d300\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"Simulator_GetUIMissionLogManager\",\n      \"va\": \"0x00b3d4f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-13-E4-EMPIRE-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"EmpirePoliticalColor_00c32cd0\",\n      \"va\": \"0x00c32cd0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"unknown-fun-mass\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00adf840\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ae00d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ae37c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ae6240\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ae9f50\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00aebe90\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b19290\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b1dee0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b26af0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b26c90\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b5cc80\"\n      },\n      {\n        \"name\": \"simulator_strategy_transition_00b5f040\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b5f040\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b71ee0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ba5270\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ba5650\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ba57f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ba58f3\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ba5a60\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ba5bd3\"\n      },\n      {\n        \"name\": \"star_regenerate_00bb4af0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00bb4af0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bb4ba0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bb8b20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bd91e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00be06c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bea930\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c004c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c00b00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c03ec0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c09410\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c0d3a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c248d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c2a190\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c38510\"\n      },\n      {\n        \"nam
[TRUNCATED]
```

## ghidra_function

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089`

```json
{
  "binary_available": true,
  "binary_sha256": "25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e",
  "body_end": "00b3d385",
  "body_span_bytes": 6,
  "body_start": "00b3d380",
  "callees": [],
  "callers": [
    "FUN_00c2a190",
    "FUN_00e01620",
    "FUN_00aebe90",
    "FUN_00d4e4a0",
    "FUN_00fdeac0",
    "FUN_00fe0c60",
    "FUN_00ffa690",
    "FUN_01017ce0",
    "FUN_01017bb0",
    "FUN_00ef2e90",
    "FUN_00f1faa0",
    "FUN_00ce48f0",
    "FUN_00f19050",
    "FUN_00cf7920",
    "FUN_00cd6800",
    "FUN_00c248d0",
    "FUN_0101ec40",
    "FUN_00d1c010",
    "FUN_00f23cd0",
    "FUN_00e033d0",
    "FUN_00ae37c0",
    "FUN_00e3c7c0",
    "FUN_00e099d0",
    "FUN_00bb8b20",
    "FUN_00fe7e60",
    "FUN_00ffb270",
    "FUN_00dc6370",
    "FUN_00d32fd0",
    "FUN_00b5cc80",
    "FUN_00c45e10",
    "FUN_00ba5bd3",
    "FUN_00e03f80",
    "FUN_00d130d0",
    "FUN_00fe6490",
    "FUN_00c004c0",
    "FUN_00e39ab0",
    "FUN_010021a0",
    "FUN_00e0b990",
    "FUN_0106cc70",
    "FUN_00cc6910",
    "FUN_00cde660",
    "FUN_00ae6240",
    "FUN_00ba5270",
    "FUN_00e3e350",
    "FUN_00ba57f0",
    "FUN_00ef10c0",
    "FUN_00efa1b0",
    "FUN_00f0a440",
    "FUN_00e398e0",
    "FUN_00d58330",
    "FUN_0106b310",
    "FUN_01060df0",
    "FUN_00cf7ad0",
    "FUN_00ef73c0",
    "FUN_00ffe860",
    "FUN_00e1db60",
    "FUN_00e02580",
    "FUN_00dea200",
    "FUN_00dcedb0",
    "FUN_00e01d00",
    "FUN_00d74060",
    "FUN_010743a0",
    "FUN_00cd9da0",
    "FUN_00e90e00",
    "FUN_00ae00d0",
    "FUN_010727e0",
    "FUN_00c09410",
    "PTRREF_00B63880",
    "FUN_00d0e170",
    "FUN_00bb4af0",
    "FUN_010423d0",
    "FUN_01019090",
    "FUN_00f118e0",
    "FUN_00b5f040",
    "FUN_00cfe160",
    "FUN_00f1aae0",
    "FUN_00dd1840",
    "FUN_00fdbc20",
    "FUN_00ffc5b0",
    "FUN_01017b70",
    "FUN_00f18660",
    "FUN_00bb4ba0",
    "FUN_00e18dd0",
    "FUN_00fe0f40",
    "FUN_00ea6dd0",
    "FUN_00d45530",
    "FUN_00d39670",
    "FUN_00ef25a0",
    "FUN_00f0ea20",
    "FUN_00c69540",
    "FUN_00cd52e0",
    "FUN_00c9afb0",
    "FUN_00ba58f3",
    "FUN_01042450",
    "FUN_00ba5a60",
    "FUN_00c00b00",
    "FUN_00cf44c0",
    "FUN_00d5fb60",
    "FUN_00c8bc10",
    "FUN_00f05790",
    "FUN_00ef2c70",
    "FUN_00e394f0",
    "FUN_00fe7d70",
    "FUN_00b26af0",
    "FUN_00cf9ba0",
    "FUN_00c03ec0",
    "FUN_00cf84a0",
    "FUN_00cf7520",
    "FUN_00cdcb10",
    "FUN_010422e0",
    "FUN_00b1dee0",
    "FUN_00fda2e0",
    "FUN_00c0d3a0",
    "FUN_00d22300",
    "FUN_00e01270",
    "FUN_00bd91e0",
    "FUN_00ae9f50",
    "FUN_0102ba30",
    "FUN_00ce0a20",
    "FUN_00bea930",
    "FUN_01044920",
    "FUN_01009df0",
    "FUN_01056160",
    "FUN_00cfa3b0",
    "FUN_00d4fbf0",
    "PTRREF_00C00000",
    "FUN_01067b60",
    "FUN_00cfa990",
    "FUN_00ef2fe0",
    "FUN_010137b0",
    "FUN_00e09a50",
    "FUN_00cfab90",
    "FUN_00e02f00",
    "FUN_00e39710",
    "FUN_0106ba00",
    "FUN_0101d130",
    "FUN_00b71ee0",
    "FUN_00ff9800",
    "FUN_00b26c90",
    "FUN_00c38510",
    "FUN_00d43e30",
    "FUN_00ba5650",
    "FUN_00fdb330",
    "FUN_00d100b0",
    "FUN_01005180",
    "FUN_00cd6980",
    "FUN_00dd17f0",
    "FUN_00f044d0",
    "FUN_00b19290",
    "FUN_00f39f50",
    "FUN_01072d40",
    "FUN_00be06c0",
    "FUN_00f069a0",
    "FUN_00e19010",
    "FUN_00cfbc10",
    "FUN_010039c0",
    "FUN_00c478b0",
    "FUN_00e07e70",
    "FUN_01001cd0",
    "FUN_0100d0d0",
    "FUN_0101ad50",
    "FUN_00ef8a10",
    "FUN_00cf71d0",
    "FUN_00fe0570",
    "FUN_00f17870",
    "FUN_00adf840",
    "FUN_010053c0"
  ],
  "classification": "stub",
  "dispatch": null,
  "entry_point": "00b3d380",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00b3d380",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x73d380",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00b3d380(void)",
  "size_bytes": 6,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00b3d380",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 100,
  "xrefs": [
    {
      "from": "00bb4e66"
    },
    {
      "from": "00bb8fca"
    },
    {
      "from": "00c004c3"
    },
    {
      "from": "00bb4b19"
    },
    {
      "from": "00c0d3c4"
    },
    {
      "from": "00c0d3cd"
    },
    {
      "from": "00ba5c37"
    },
    {
      "from": "00e3e691"
    },
    {
      "from": "00e3e720"
    },
    {
      "from": "00d606cf"
    },
    {
      "from": "00d607b4"
    },
    {
      "from": "00d60ad5"
    },
    {
      "from": "00d583c4"
    },
    {
      "from": "00adf8ca"
    },
    {
      "from": "00adf8d6"
    },
    {
      "from": "00ae014f"
    },
    {
      "from": "00ae0164"
    },
    {
      "from": "00ae624f"
    },
    {
      "from": "00ae37ea"
    },
    {
      "from": "00bea937"
    },
    {
      "from": "00ba5ae1"
    },
    {
      "from": "00aec133"
    },
    {
      "from": "00aea094"
    },
    {
      "from": "00c00ba1"
    },
    {
      "from": "00c00da4"
    },
    {
      "from": "00cf7520"
    },
    {
      "from": "00cf79a6"
    },
    {
      "from": "00cf9c24"
    },
    {
      "from": "00cf9c78"
    },
    {
      "from": "00cf9ccb"
    },
    {
      "from": "00cf9d1e"
    },
    {
      "from": "00cf9e0d"
    },
    {
      "from": "00cf9ee2"
    },
    {
      "from": "00e3c9ae"
    },
    {
   
[TRUNCATED]
```

## globals

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [],
  "handoffs": [],
  "metadata": []
}
```

## runtime

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## runtime_metadata

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "blocking_reason": null,
  "gates": [],
  "validated": 0
}
```

## semantic_hypotheses

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

## status

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "runtime_gated": false,
  "runtime_validated": 0,
  "status": "candidate"
}
```

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
