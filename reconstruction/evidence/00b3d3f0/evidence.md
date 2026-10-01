# Evidence 0x00b3d3f0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `9b246b1791d889086e23915d456d91c0a047dbe6f180dece7fbb468f03462d9e`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "cdecl-compatible no-argument accessor",
  "hidden_receiver": null,
  "ordinary_stack_argument_slots": 0,
  "ret_form": "RET",
  "return_note": "opaque 32-bit slot word",
  "return_register": "EAX",
  "return_width_bytes": 4,
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
  "content_sha256": "0036e381359064e4a7067b08386ea06da2a2b56ff2ebff38352a7ab3b0a331d8",
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
    "persisted_calling_convention": "cdecl-compatible no-argument accessor"
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
      "at": "0x00b3d3f0",
      "definite": true,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,[0x0167eb5c]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00b3d3f5",
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
    "va": "0x00b3d3f0"
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
    "va": "0x00b5e9a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b6dbd0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00cd9660"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00cd98e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d0e170"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d35190"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d3d4f0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e02f00"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e130b0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e14360"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e14a30"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e18a30"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e1ef90"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e1fb20"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e510f0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e53860"
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
      "address": "00b3d3f0",
      "instruction": "MOV EAX,[0x0167eb5c]"
    },
    {
      "address": "00b3d3f5",
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
  "original_bytes": 16234,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"cdecl-compatible no-argument accessor\",\n    \"hidden_receiver\": null,\n    \"ordinary_stack_argument_slots\": 0,\n    \"ret_form\": \"RET\",\n    \"return_note\": \"opaque 32-bit slot word\",\n    \"return_register\": \"EAX\",\n    \"return_width_bytes\": 4,\n    \"stack_cleanup_bytes\": 0\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:None,RootWord,opaque 32-bit slot word,undefined4\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-11-H2-ROOT-ACCESSORS\",\n      \"score\": 30,\n      \"symbol\": \"root_accessor_00b3d3b0\",\n      \"va\": \"0x00b3d3b0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:None,RootWord,opaque 32-bit slot word,undefined4\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-11-H2-ROOT-ACCESSORS\",\n      \"score\": 30,\n      \"symbol\": \"root_accessor_00b3d3e0\",\n      \"va\": \"0x00b3d3e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:None,RootWord,opaque 32-bit slot word,undefined4\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-11-H2-ROOT-ACCESSORS\",\n      \"score\": 30,\n      \"symbol\": \"root_accessor_00b3d430\",\n      \"va\": \"0x00b3d430\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-13-E3-EMPIRE-STATE-WAVE2\",\n      \"score\": 8,\n      \"symbol\": \"SpeciesProfileSelector_00c30cc0\",\n      \"va\": \"0x00c30cc0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-13-E3-EMPIRE-STATE-WAVE2\",\n      \"score\": 8,\n      \"symbol\": \"ArchetypeRelationshipsID_00c30e20\",\n      \"va\": \"0x00c30e20\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-11-SIM-CORE\",\n      \"score\": 8,\n      \"symbol\": \"Simulator_IsNotStarOrBinaryStar\",\n      \"va\": \"0x00c8b6b0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-13-E2-DIPLOMACY-ALT\",\n      \"score\": 8,\n      \"symbol\": \"RelationshipScoreBand_00d00d00\",\n      \"va\": \"0x00d00d00\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-13-C3-CREATURE-PROGRESSION-WAVE2\",\n      \"score\": 8,\n      \"symbol\": \"Simulator_cCreatureGameData_Get_00d2e340\",\n      \"va\": \"0x00d2e340\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": \"clean\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"None\",\n  \"cluster\": \"unknown-fun-mass\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b5e9a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b6dbd0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00cd9660\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00cd98e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d0e170\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d35190\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d3d4f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e02f00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e130b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e14360\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e14a30\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e18a30\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e1ef90\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e1fb20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e510f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e53860\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e53950\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e539c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e5d7b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e64a00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e7f630\"\n      },\n      {\n        \"name\": \"cell_update_body_00e806b0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00e806b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00feb770\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va
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
  "body_end": "00b3d3f5",
  "body_span_bytes": 6,
  "body_start": "00b3d3f0",
  "callees": [],
  "callers": [
    "FUN_00b5e9a0",
    "FUN_00d3d4f0",
    "FUN_00e7f630",
    "FUN_00feb770",
    "FUN_00e18a30",
    "FUN_0106cc70",
    "FUN_00cd9660",
    "FUN_00cd98e0",
    "FUN_0106ada0",
    "FUN_010743a0",
    "FUN_00e806b0",
    "FUN_01072d40",
    "FUN_010691e0",
    "FUN_00d0e170",
    "FUN_00e5d7b0",
    "FUN_00e53860",
    "FUN_0106ba00",
    "FUN_00e130b0",
    "FUN_00e02f00",
    "FUN_00e510f0",
    "FUN_00e1ef90",
    "FUN_01064080",
    "FUN_00b6dbd0",
    "FUN_00e14a30",
    "FUN_01064f00",
    "FUN_00d35190",
    "FUN_00e1fb20",
    "FUN_0107afa0",
    "FUN_00e14360",
    "FUN_00ffe860",
    "FUN_01023fc0",
    "FUN_01067b60",
    "FUN_00e539c0",
    "FUN_010655a0",
    "FUN_00e64a00",
    "FUN_010635d0",
    "FUN_01063dc0",
    "FUN_00e53950"
  ],
  "classification": "stub",
  "dispatch": null,
  "entry_point": "00b3d3f0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00b3d3f0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x73d3f0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00b3d3f0(void)",
  "size_bytes": 6,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00b3d3f0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 61,
  "xrefs": [
    {
      "from": "0106ba27"
    },
    {
      "from": "0106cc93"
    },
    {
      "from": "00b5ecf8"
    },
    {
      "from": "00b6dc59"
    },
    {
      "from": "00cd9729"
    },
    {
      "from": "00cd99ad"
    },
    {
      "from": "00d0e74f"
    },
    {
      "from": "00d3d6a6"
    },
    {
      "from": "00e03310"
    },
    {
      "from": "00e14492"
    },
    {
      "from": "00e14b14"
    },
    {
      "from": "00e18a35"
    },
    {
      "from": "00e18a46"
    },
    {
      "from": "00e1f042"
    },
    {
      "from": "00e200e7"
    },
    {
      "from": "00e64bc6"
    },
    {
      "from": "00e5d9cc"
    },
    {
      "from": "00e807d9"
    },
    {
      "from": "00e8091a"
    },
    {
      "from": "00e51165"
    },
    {
      "from": "00ffe8f8"
    },
    {
      "from": "00ffe90e"
    },
    {
      "from": "010743f5"
    },
    {
      "from": "010748f7"
    },
    {
      "from": "01074b2b"
    },
    {
      "from": "01074b5f"
    },
    {
      "from": "010691fe"
    },
    {
      "from": "0106adb2"
    },
    {
      "from": "0106b1a1"
    },
    {
      "from": "00feb98a"
    },
    {
      "from": "010245c6"
    },
    {
      "from": "01063679"
    },
    {
      "from": "01063f42"
    },
    {
      "from": "01064295"
    },
    {
      "from": "010644ea"
    },
    {
      "from": "01065670"
    },
    {
      "from": "010656ee"
    },
    {
      "from": "01067bdd"
    },
    {
      "from": "0107360c"
    },
    {
      "from": "0107361e"
    },
    {
      "from": "0107b04e"
    },
    {
      "from": "0107b0d5"
    },
    {
      "from": "00d361c5"
    },
    {
      "from": "00cf66bb"
    },
    {
      "from": "00e06b8d"
    },
    {
      "from": "00e13102"
    },
    {
      "from": "00e19232"
    },
    {
      "from": "00e20501"
    },
    {
      "from": "00fd9f21"
    },
    {
      "from": "00fd9f2f"
    },
    {
      "from": "0100cd66"
    },
    {
      "from": "0100cd6f"
    },
    {
      "from": "01064fb1"
    },
    {
      "from": "010753cd"
    },
    {
      "from": "0107b728"
    },
    {
      "from": "01062f6e"
    },
    {
      "from": "00e7f66c"
    },
    {
      "from": "00e7f698"
    },
    {
      "from": "00e538a3"
    },
    {
      "from": "00e5399a"
    },
    {
      "from": "00e53a03"
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
  "global:MOV EAX,[0x0167eb5c]",
  "global:READ from 0x00b3d3f0",
  "global:get_xrefs_to(0x0167eb5c); one READ xref from this function"
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg11_h2_root_accessors/root_accessors.cpp",
  "files": [
    "reconstruction/staging/pkg11-h2-root-accessors/root_accessors.cpp",
    "reconstruction/staging/pkg11-h2-root-accessors/root_accessors.hpp",
    "reconstruction/staging/pkg11-h2-root-accessors/root_accessors_model_test.cpp",
    "src/reconstruction/pkg11_h2_root_accessors/root_accessors.cpp",
    "src/reconstruction/pkg11_h2_root_accessors/root_accessors.hpp",
    "src/reconstruction/pkg11_h2_root_accessors/root_accessors_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-sim-social-world-wave1/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg11-h2-root-accessors/00b3d3f0.json"
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
    "gate-root-slot-00b3d3f0",
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
  "RootWord",
  "opaque 32-bit slot word",
  "undefined4"
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
