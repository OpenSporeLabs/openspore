# Evidence 0x00d2e350

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `590bf687c76a01328508477beffa522ada247bff8b0235a8e4afbb8126f4680c`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "cdecl-compatible thisless static accessor from RET",
  "hidden_this": false,
  "return_register": "ST0",
  "return_semantics": "Exact four-byte float value loaded from the global slot 0x0169e398; no conversion, clamp, sentinel, or default occurs.",
  "return_width_bytes": 4,
  "stack_arguments": [],
  "stack_cleanup_bytes": 0
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
    "return_register": "ST0",
    "return_semantics": "float_or_x87_in_ST0",
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
  "content_sha256": "401732ed67eae07619ab11cd3c1fdf52b2fe3be59316effdb7e3bed2ed899bcb",
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
    "persisted_calling_convention": "cdecl-compatible thisless static accessor from RET"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0001"
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
        "obs-0001"
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
        "obs-0001"
      ],
      "claim": "the function is byte-identical under all four conventions",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0001"
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
        "obs-0001"
      ],
      "claim": "the return value is carried in ST0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "ST0"
    }
  ],
  "observations": [
    {
      "at": "0x00d2e356",
      "form": "RET",
      "id": "obs-0001",
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
    "instructions": 2,
    "syntax": "intel",
    "va": "0x00d2e356"
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
    "va": "0x00d2dd20"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d35190"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d39670"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d40230"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d45530"
  }
]
```

## contradictions

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "anchors": [
      "0x00fe52c0",
      "0x00fe52c0",
      "0x00d2e350",
      "0x00d2e350",
      "0x00d2e380",
      "0x00d2e380",
      "0x00d2e480",
      "0x00d2e480",
      "0x00d2e8a0",
      "0x00d2e8a0",
      "0x00d3fcf0",
      "0x00d3fcf0",
      "0x00fe52c0",
      "0x00fe52c0",
      "0x00fe52c0",
      "0x00fe52c0"
    ],
    "conflict_id": "badge_state_domain",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
    "resolution_status": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00594b10",
      "0x00594b10",
      "0x00596da0",
      "0x00596da0",
      "0x00597390",
      "0x00597390",
      "0x00597400",
      "0x00597400",
      "0x00598db0",
      "0x00598db0",
      "0x00598e90",
      "0x00598e90",
      "0x00599440",
      "0x00599440",
      "0x00d2e350",
      "0x00d2e350"
    ],
    "conflict_id": "cell_progression_semantics",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
    "resolution_status": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00001278",
      "0x0000127c",
      "0x000010fc",
      "0x0000110c",
      "0x00001278",
      "0x0000127c",
      "0x00d2e350",
      "0x00d2e350",
      "0x00d2e380",
      "0x00d2e380",
      "0x00d2e480",
      "0x00d2e480",
      "0x00d2e8a0",
      "0x00d2e8a0",
      "0x00d3fcf0",
      "0x00d3fcf0"
    ],
    "conflict_id": "consequence_trait_rules",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00d2e380",
      "0x00d2e8a0",
      "0x00d2e8a0",
      "0x00d2e350",
      "0x00d2e350",
      "0x00d2e380",
      "0x00d2e380",
      "0x00d2e380",
      "0x00d2e480",
      "0x00d2e480",
      "0x00d2e8a0",
      "0x00d2e8a0",
      "0x00d2e8a0",
      "0x00d3fcf0",
      "0x00d3fcf0",
      "0x00feb880"
    ],
    "conflict_id": "evolution_numeric_thresholds",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00598db0",
      "0x00598db0",
      "0x00cc8c90",
      "0x00cc8c90",
      "0x00d2e350",
      "0x00d2e350",
      "0x00d2e380",
      "0x00d2e380",
      "0x00d2e480",
      "0x00d2e480",
      "0x00d2e8a0",
      "0x00d2e8a0",
      "0x00d3fcf0",
      "0x00d3fcf0",
      "0x00d2e350",
      "0x00d2e380"
    ],
    "conflict_id": "live_ghidra_progression_access",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The cited stream or file boundary is retained, but the complete wire/transaction/round-trip contract is not reconstructed.",
    "resolution_status": "The cited stream or file boundary is retained, but the complete wire/transaction/round-trip contract is not reconstructed.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00d2e350",
      "0x00d2e350",
      "0x00d2e380",
      "0x00d2e380",
      "0x00d2e480",
      "0x00d2e480",
      "0x00d2e8a0",
      "0x00d2e8a0",
      "0x00d3fcf0",
      "0x00d3fcf0",
      "0x00fe52c0",
      "0x00fe52c0",
      "0x00feb880",
      "0x00feb880",
      "0x00febce0",
      "0x00febce0"
    ],
    "conflict_id": "mission_transition_implementation",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
    "resolution_status": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  }
]
```

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
      "address": "00d2e350",
      "instruction": "FLD float ptr [0x0169e398]"
    },
    {
      "address": "00d2e356",
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
  "original_bytes": 7593,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"cdecl-compatible thisless static accessor from RET\",\n    \"hidden_this\": false,\n    \"return_register\": \"ST0\",\n    \"return_semantics\": \"Exact four-byte float value loaded from the global slot 0x0169e398; no conversion, clamp, sentinel, or default occurs.\",\n    \"return_width_bytes\": 4,\n    \"stack_arguments\": [],\n    \"stack_cleanup_bytes\": 0\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:None\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-13-SIM-CREATURE-TRIBECIV\",\n      \"score\": 24,\n      \"symbol\": \"Simulator_cCreatureGameData_GetAbilityMode\",\n      \"va\": \"0x00d2e490\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-13-SIM-CREATURE-TRIBECIV\",\n      \"score\": 22,\n      \"symbol\": \"Simulator_cCreatureGameData_GetEvoPointsToNextBrainLevel\",\n      \"va\": \"0x00d2e380\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-13-C3-CREATURE-PROGRESSION-WAVE2\",\n      \"score\": 14,\n      \"symbol\": \"Simulator_cCreatureGameData_Get_00d2e340\",\n      \"va\": \"0x00d2e340\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-13-C3-CREATURE-PROGRESSION-WAVE2\",\n      \"score\": 14,\n      \"symbol\": \"Simulator_cCreatureGameData_AddEvolutionPoints_raw_00d2e8a0\",\n      \"va\": \"0x00d2e8a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-11-H2-ROOT-ACCESSORS\",\n      \"score\": 8,\n      \"symbol\": \"root_accessor_00b3d3b0\",\n      \"va\": \"0x00b3d3b0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-11-H2-ROOT-ACCESSORS\",\n      \"score\": 8,\n      \"symbol\": \"root_accessor_00b3d3e0\",\n      \"va\": \"0x00b3d3e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-11-H2-ROOT-ACCESSORS\",\n      \"score\": 8,\n      \"symbol\": \"root_accessor_00b3d3f0\",\n      \"va\": \"0x00b3d3f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-11-H2-ROOT-ACCESSORS\",\n      \"score\": 8,\n      \"symbol\": \"root_accessor_00b3d430\",\n      \"va\": \"0x00b3d430\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"The imported cCreatureGameData name is retained, but the body has no receiver and reads only global 0x0169e398; global owner and runtime value remain unresolved.\",\n  \"audit_findings\": [\n    \"PKG13-META-001\"\n  ],\n  \"audit_status\": \"clean_after_repair\",\n  \"blocked\": false,\n  \"blockers\": [\n    \"Runtime evolution-points values and global lifetime remain gated.\"\n  ],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"None\",\n  \"cluster\": null,\n  \"confidence\": 0.95,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d2dd20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d35190\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d39670\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d40230\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d45530\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00d2ddcc\",\n        \"direction\": \"in\",\n        \"other\": \"0x00d2dd20\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00d3551a\",\n        \"direction\": \"in\",\n        \"other\": \"0x00d35190\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00d3973d\",\n        \"direction\": \"in\",\n        \"other\": \"0x00d39670\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00d4030c\",\n        \"direction\": \"in\",\n        \"other\": \"0x00d40230\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00d45654\",\n        \"direction\": \"in\",\n        \"other\": \"0x00d45530\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 5,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [\n      \"0x00d2dd20\",\n      \"0x00d35190\",\n      \"0x00d39670\",\n      \"0x00d40230\",\n      \"0x00d45530\"\n    ],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0498\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"SUPPORTED\",\n  \"globals\": [\n    \"global:DAT_0169e398\",\n    \"global:float\",\n    \"global:unknown\"\n  ],\n  \"integration_status\": \"integrated\",\n  \"name\": \"Simulator_cCreatureGameData_GetEvolutionPoints\",\n  \"normalized_symbol\": \"Simulator_cCreatureGameData_GetEvolutionPoints\",\n  \"observed_mechanics\": [\n    \"FLD float ptr [0x0169e398]\",\n    \"RET\",\n    \"no receiver\",\n    \"no mutation\"\n  ],\n  \"ownership\": {\n    \"claimability\": \"do_not_claim\",\n    \"handoff_packages\": [\
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
  "body_end": "00d2e356",
  "body_span_bytes": 7,
  "body_start": "00d2e350",
  "callees": [],
  "callers": [
    "FUN_00d35190",
    "FUN_00d2dd20",
    "FUN_00d45530",
    "FUN_00d40230",
    "FUN_00d39670"
  ],
  "classification": "stub",
  "dispatch": null,
  "entry_point": "00d2e350",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "Simulator::cCreatureGameData::GetEvolutionPoints",
  "namespace": "Simulator",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "float",
  "return_type_resolved": true,
  "rva": "0x92e350",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "float Simulator::cCreatureGameData::GetEvolutionPoints(void)",
  "size_bytes": 7,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00d2e350",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 5,
  "xrefs": [
    {
      "from": "00d3973d"
    },
    {
      "from": "00d4030c"
    },
    {
      "from": "00d45654"
    },
    {
      "from": "00d3551a"
    },
    {
      "from": "00d2ddcc"
    }
  ]
}
```

## globals

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "global:DAT_0169e398",
  "global:float",
  "global:unknown"
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg13_creature_state/creature_state.cpp",
  "files": [
    "reconstruction/staging/pkg13-b0-creature-state/creature_state.cpp",
    "reconstruction/staging/pkg13-b0-creature-state/creature_state.hpp",
    "reconstruction/staging/pkg13-b0-creature-state/creature_state_test.cpp",
    "src/reconstruction/pkg13_creature_state/creature_state.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg13-b0-creature-state/00d2e350.json"
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
    "creature_evolution_points_global_observation"
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
  "None"
]
```

## vtables

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## Conflicts

```json
[
  {
    "anchors": [
      "0x00fe52c0",
      "0x00fe52c0",
      "0x00d2e350",
      "0x00d2e350",
      "0x00d2e380",
      "0x00d2e380",
      "0x00d2e480",
      "0x00d2e480",
      "0x00d2e8a0",
      "0x00d2e8a0",
      "0x00d3fcf0",
      "0x00d3fcf0",
      "0x00fe52c0",
      "0x00fe52c0",
      "0x00fe52c0",
      "0x00fe52c0"
    ],
    "conflict_id": "badge_state_domain",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
    "resolution_status": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00594b10",
      "0x00594b10",
      "0x00596da0",
      "0x00596da0",
      "0x00597390",
      "0x00597390",
      "0x00597400",
      "0x00597400",
      "0x00598db0",
      "0x00598db0",
      "0x00598e90",
      "0x00598e90",
      "0x00599440",
      "0x00599440",
      "0x00d2e350",
      "0x00d2e350"
    ],
    "conflict_id": "cell_progression_semantics",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
    "resolution_status": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00001278",
      "0x0000127c",
      "0x000010fc",
      "0x0000110c",
      "0x00001278",
      "0x0000127c",
      "0x00d2e350",
      "0x00d2e350",
      "0x00d2e380",
      "0x00d2e380",
      "0x00d2e480",
      "0x00d2e480",
      "0x00d2e8a0",
      "0x00d2e8a0",
      "0x00d3fcf0",
      "0x00d3fcf0"
    ],
    "conflict_id": "consequence_trait_rules",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00d2e380",
      "0x00d2e8a0",
      "0x00d2e8a0",
      "0x00d2e350",
      "0x00d2e350",
      "0x00d2e380",
      "0x00d2e380",
      "0x00d2e380",
      "0x00d2e480",
      "0x00d2e480",
      "0x00d2e8a0",
      "0x00d2e8a0",
      "0x00d2e8a0",
      "0x00d3fcf0",
      "0x00d3fcf0",
      "0x00feb880"
    ],
    "conflict_id": "evolution_numeric_thresholds",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00598db0",
      "0x00598db0",
      "0x00cc8c90",
      "0x00cc8c90",
      "0x00d2e350",
      "0x00d2e350",
      "0x00d2e380",
      "0x00d2e380",
      "0x00d2e480",
      "0x00d2e480",
      "0x00d2e8a0",
      "0x00d2e8a0",
      "0x00d3fcf0",
      "0x00d3fcf0",
      "0x00d2e350",
      "0x00d2e380"
    ],
    "conflict_id": "live_ghidra_progression_access",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The cited stream or file boundary is retained, but the complete wire/transaction/round-trip contract is not reconstructed.",
    "resolution_status": "The cited stream or file boundary is retained, but the complete wire/transaction/round-trip contract is not reconstructed.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00d2e350",
      "0x00d2e350",
      "0x00d2e380",
      "0x00d2e380",
      "0x00
[TRUNCATED]
```
