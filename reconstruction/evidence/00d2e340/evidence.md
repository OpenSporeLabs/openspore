# Evidence 0x00d2e340

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `7c5bc4f83d208f93e4cee918dab39bc98eea9a6e54d5e821024136f72ef9d76a`

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
  "content_sha256": "08cdcf75fde5d0ce024a60d54c0abfdbbaedd3ab68a5b98d1d057167b61ee4b5",
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
      "at": "0x00d2e340",
      "definite": true,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,0x169e370",
      "reg": "EAX",
      "write_kind": "imm"
    },
    {
      "at": "0x00d2e345",
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
    "va": "0x00d2e340"
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
  "content_sha256": "08cdcf75fde5d0ce024a60d54c0abfdbbaedd3ab68a5b98d1d057167b61ee4b5",
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
      "at": "0x00d2e340",
      "definite": true,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,0x169e370",
      "reg": "EAX",
      "write_kind": "imm"
    },
    {
      "at": "0x00d2e345",
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
    "va": "0x00d2e340"
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
    "va": "0x00c0c630"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d1e930"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d1f650"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d239a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d24070"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e07e70"
  }
]
```

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
      "address": "00d2e340",
      "instruction": "MOV EAX,0x169e370"
    },
    {
      "address": "00d2e345",
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
  "original_bytes": 10711,
  "preview": "{\n  \"abi\": {},\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:None,UNCONDITIONAL_CALL\"\n      ],\n      \"package\": \"PKG-13-C3-CREATURE-PROGRESSION-WAVE2\",\n      \"score\": 25,\n      \"symbol\": \"Simulator_cCreatureGameData_AddEvolutionPoints_raw_00d2e8a0\",\n      \"va\": \"0x00d2e8a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-13-SIM-CREATURE-TRIBECIV\",\n      \"score\": 14,\n      \"symbol\": \"Simulator_cCreatureGameData_GetEvolutionPoints\",\n      \"va\": \"0x00d2e350\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-13-SIM-CREATURE-TRIBECIV\",\n      \"score\": 14,\n      \"symbol\": \"Simulator_cCreatureGameData_GetEvoPointsToNextBrainLevel\",\n      \"va\": \"0x00d2e380\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-13-SIM-CREATURE-TRIBECIV\",\n      \"score\": 14,\n      \"symbol\": \"Simulator_cCreatureGameData_GetAbilityMode\",\n      \"va\": \"0x00d2e490\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-11-H2-ROOT-ACCESSORS\",\n      \"score\": 8,\n      \"symbol\": \"root_accessor_00b3d3b0\",\n      \"va\": \"0x00b3d3b0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-11-H2-ROOT-ACCESSORS\",\n      \"score\": 8,\n      \"symbol\": \"root_accessor_00b3d3e0\",\n      \"va\": \"0x00b3d3e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-11-H2-ROOT-ACCESSORS\",\n      \"score\": 8,\n      \"symbol\": \"root_accessor_00b3d3f0\",\n      \"va\": \"0x00b3d3f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-11-H2-ROOT-ACCESSORS\",\n      \"score\": 8,\n      \"symbol\": \"root_accessor_00b3d430\",\n      \"va\": \"0x00b3d430\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Reviewed static mechanics and ABI are canonical; runtime values, ownership, concrete types, and opaque port behavior remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [\n    \"The concrete static object type, initialization, and caller-side lifetime contract remain runtime-gated.\"\n  ],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"None\",\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c0c630\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d1e930\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d1f650\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d239a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d24070\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e07e70\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00c0c983\",\n        \"direction\": \"in\",\n        \"other\": \"0x00c0c630\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00d1ec3a\",\n        \"direction\": \"in\",\n        \"other\": \"0x00d1e930\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00d1ec78\",\n        \"direction\": \"in\",\n        \"other\": \"0x00d1e930\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00d1f795\",\n        \"direction\": \"in\",\n        \"other\": \"0x00d1f650\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00d1f7e3\",\n        \"direction\": \"in\",\n        \"other\": \"0x00d1f650\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00d23cb6\",\n        \"direction\": \"in\",\n        \"other\": \"0x00d239a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00d23cd2\",\n        \"direction\": \"in\",\n        \"other\": \"0x00d239a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00d23e37\",\n        \"direction\": \"in\",\n        \"other\": \"0x00d239a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00d23ee5\",\n        \"direction\": \"in\",\n        \"other\": \"0x00d239a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00d23efa\",\n        \"direction\": \"in\",\n        \"other\": \"0x00d239a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00d23f12\",\n        \"direction\": \"in\",\n        \"other\": \"0x00d239a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00d23f30\",\n        \"direction\": \"in\",\n        \"other\": \"0x00d239a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00d23f40\",\n        \"direction\": \"in\",\n        \"other\": \"0x00d239a0\",\n        \"refere
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
  "body_end": "00d2e345",
  "body_span_bytes": 6,
  "body_start": "00d2e340",
  "callees": [],
  "callers": [
    "FUN_00d239a0",
    "FUN_00c0c630",
    "FUN_00d24070",
    "FUN_00e07e70",
    "FUN_00d1f650",
    "FUN_00d1e930"
  ],
  "classification": "stub",
  "dispatch": null,
  "entry_point": "00d2e340",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "Simulator::cCreatureGameData::Get",
  "namespace": "Simulator",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "cCreatureGameData *",
  "return_type_resolved": true,
  "rva": "0x92e340",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "cCreatureGameData * Simulator::cCreatureGameData::Get(void)",
  "size_bytes": 6,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00d2e340",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 28,
  "xrefs": [
    {
      "from": "00c0c983"
    },
    {
      "from": "00d23cb6"
    },
    {
      "from": "00d23cd2"
    },
    {
      "from": "00d23e37"
    },
    {
      "from": "00d23ee5"
    },
    {
      "from": "00d23efa"
    },
    {
      "from": "00d23f12"
    },
    {
      "from": "00d23f30"
    },
    {
      "from": "00d23f40"
    },
    {
      "from": "00d23f49"
    },
    {
      "from": "00d24245"
    },
    {
      "from": "00d2425d"
    },
    {
      "from": "00d2429a"
    },
    {
      "from": "00d244af"
    },
    {
      "from": "00d244c4"
    },
    {
      "from": "00d244dc"
    },
    {
      "from": "00d244fa"
    },
    {
      "from": "00d2450a"
    },
    {
      "from": "00d24513"
    },
    {
      "from": "00e081a8"
    },
    {
      "from": "00e081b3"
    },
    {
      "from": "00d1f795"
    },
    {
      "from": "00d1f7e3"
    },
    {
      "from": "00d1ec3a"
    },
    {
      "from": "00d1ec78"
    },
    {
      "from": "00d26c39"
    },
    {
      "from": "00d6410a"
    },
    {
      "from": "00d64dc7"
    }
  ]
}
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
  "file": "src/reconstruction/pkg13_c3_creature_progression_wave2/creature_progression_wave2.cpp",
  "files": [
    "reconstruction/staging/pkg13-c3-creature-progression-wave2/creature_progression_wave2.cpp",
    "reconstruction/staging/pkg13-c3-creature-progression-wave2/creature_progression_wave2.hpp",
    "reconstruction/staging/pkg13-c3-creature-progression-wave2/creature_progression_wave2_model_test.cpp",
    "src/reconstruction/pkg13_c3_creature_progression_wave2/creature_progression_wave2.cpp",
    "src/reconstruction/pkg13_c3_creature_progression_wave2/creature_progression_wave2.hpp",
    "src/reconstruction/pkg13_c3_creature_progression_wave2/creature_progression_wave2_model_test.cpp",
    "src/reconstruction/pkg13_c3_creature_progression_wave2/metadata_package_validation.py"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-sim-social-world-wave2/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg13-c3-creature-progression-wave2/00d2e340.json"
  ]
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
  "gates": [
    "No original-process accessor trace or runtime validation has been run.",
    "Observe the object at 0x0169e370 and its concrete initialization in an original process.",
    "Resolve the concrete caller-side type and lifetime contract before promoting the opaque object model.",
    "gate-creature-game-data-get-00d2e340",
    "runtime validation not run"
  ],
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
  "runtime_gated": true,
  "runtime_validated": 0,
  "status": "reconstructed"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "None",
  "UNCONDITIONAL_CALL",
  "static storage at 0x0169e370"
]
```

## vtables

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## Conflicts

```json
[]
```
