# Evidence 0x00b3d3b0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `756cac695cf98c7c71a925576e8095a0403ec9ababd5338abbaf6e539d88bc9f`

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
  "content_sha256": "9975a81f828a37a9f77323cf921ef40a2e04d5b1d5aaf9bd05fab4b90757fb30",
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
      "at": "0x00b3d3b0",
      "definite": true,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,[0x0167eb10]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00b3d3b5",
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
    "va": "0x00b3d3b0"
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
    "va": "0x00b02fa0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b04aa0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b07980"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b07fa0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b2a110"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b2b090"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b32aa0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b32c60"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b32e80"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b33030"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b33130"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b33350"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b33540"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b335d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b57c40"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b5a750"
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
      "address": "00b3d3b0",
      "instruction": "MOV EAX,[0x0167eb10]"
    },
    {
      "address": "00b3d3b5",
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
  "original_bytes": 16981,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"cdecl-compatible no-argument accessor\",\n    \"hidden_receiver\": null,\n    \"ordinary_stack_argument_slots\": 0,\n    \"ret_form\": \"RET\",\n    \"return_note\": \"opaque 32-bit slot word\",\n    \"return_register\": \"EAX\",\n    \"return_width_bytes\": 4,\n    \"stack_cleanup_bytes\": 0\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:None,RootWord,opaque 32-bit slot word,undefined4\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-11-H2-ROOT-ACCESSORS\",\n      \"score\": 30,\n      \"symbol\": \"root_accessor_00b3d3e0\",\n      \"va\": \"0x00b3d3e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:None,RootWord,opaque 32-bit slot word,undefined4\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-11-H2-ROOT-ACCESSORS\",\n      \"score\": 30,\n      \"symbol\": \"root_accessor_00b3d3f0\",\n      \"va\": \"0x00b3d3f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:None,RootWord,opaque 32-bit slot word,undefined4\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-11-H2-ROOT-ACCESSORS\",\n      \"score\": 30,\n      \"symbol\": \"root_accessor_00b3d430\",\n      \"va\": \"0x00b3d430\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-13-E3-EMPIRE-STATE-WAVE2\",\n      \"score\": 8,\n      \"symbol\": \"SpeciesProfileSelector_00c30cc0\",\n      \"va\": \"0x00c30cc0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-13-E3-EMPIRE-STATE-WAVE2\",\n      \"score\": 8,\n      \"symbol\": \"ArchetypeRelationshipsID_00c30e20\",\n      \"va\": \"0x00c30e20\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-11-SIM-CORE\",\n      \"score\": 8,\n      \"symbol\": \"Simulator_IsNotStarOrBinaryStar\",\n      \"va\": \"0x00c8b6b0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-13-E2-DIPLOMACY-ALT\",\n      \"score\": 8,\n      \"symbol\": \"RelationshipScoreBand_00d00d00\",\n      \"va\": \"0x00d00d00\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-13-C3-CREATURE-PROGRESSION-WAVE2\",\n      \"score\": 8,\n      \"symbol\": \"Simulator_cCreatureGameData_Get_00d2e340\",\n      \"va\": \"0x00d2e340\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": \"clean\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"None\",\n  \"cluster\": \"unknown-fun-mass\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b02fa0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b04aa0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b07980\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b07fa0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b2a110\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b2b090\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b32aa0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b32c60\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b32e80\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b33030\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b33130\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b33350\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b33540\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b335d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b57c40\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b5a750\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b74f80\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b76f10\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b77db0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b783b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bbc400\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bbc540\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bbd6c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bbd730\"\n    
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
  "body_end": "00b3d3b5",
  "body_span_bytes": 6,
  "body_start": "00b3d3b0",
  "callees": [],
  "callers": [
    "FUN_00ee9690",
    "FUN_00b02fa0",
    "FUN_00c809d0",
    "FUN_00bbd6c0",
    "FUN_00c81ab0",
    "FUN_00bbc540",
    "FUN_00ee9840",
    "FUN_00b07980",
    "FUN_00c810e0",
    "FUN_00b77db0",
    "FUN_00b32e80",
    "FUN_00ee95a0",
    "FUN_01003690",
    "FUN_00b5a750",
    "FUN_00d87620",
    "FUN_00b07fa0",
    "FUN_00bbdbf0",
    "FUN_00cfa410",
    "FUN_00f35c80",
    "FUN_00b33350",
    "FUN_00b33030",
    "FUN_00b2a110",
    "FUN_00b335d0",
    "FUN_00b04aa0",
    "FUN_00b33130",
    "FUN_00b33540",
    "FUN_00b32c60",
    "FUN_00c80780",
    "FUN_01049040",
    "FUN_00c80680",
    "FUN_00b2b090",
    "FUN_00ff9800",
    "FUN_00b57c40",
    "FUN_00b783b0",
    "FUN_0100a960",
    "FUN_00b76f10",
    "FUN_00bbd730",
    "FUN_00b32aa0",
    "FUN_00d1cdf0",
    "FUN_0105a110",
    "FUN_00d7ee90",
    "FUN_00ff7530",
    "FUN_00bc08d0",
    "FUN_010166c0",
    "FUN_00b74f80",
    "FUN_00bbc400"
  ],
  "classification": "stub",
  "dispatch": null,
  "entry_point": "00b3d3b0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00b3d3b0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x73d3b0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00b3d3b0(void)",
  "size_bytes": 6,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00b3d3b0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 72,
  "xrefs": [
    {
      "from": "00bc08f6"
    },
    {
      "from": "00bc142c"
    },
    {
      "from": "00b2a14d"
    },
    {
      "from": "00c80a5d"
    },
    {
      "from": "00b07fd5"
    },
    {
      "from": "00b2b0d1"
    },
    {
      "from": "00b3384b"
    },
    {
      "from": "00b32edb"
    },
    {
      "from": "00b33050"
    },
    {
      "from": "00b33175"
    },
    {
      "from": "00b3359e"
    },
    {
      "from": "00bbc5a1"
    },
    {
      "from": "00bbc5e2"
    },
    {
      "from": "00bbc5f9"
    },
    {
      "from": "00bbc610"
    },
    {
      "from": "00c80711"
    },
    {
      "from": "00c8072c"
    },
    {
      "from": "00c80747"
    },
    {
      "from": "0100acbd"
    },
    {
      "from": "00b32ade"
    },
    {
      "from": "00b32cad"
    },
    {
      "from": "00b594ac"
    },
    {
      "from": "00b5a7f8"
    },
    {
      "from": "00b74fe2"
    },
    {
      "from": "00b77e18"
    },
    {
      "from": "00b77e5e"
    },
    {
      "from": "00b785a9"
    },
    {
      "from": "00b76fc3"
    },
    {
      "from": "00b770a5"
    },
    {
      "from": "00b77395"
    },
    {
      "from": "00bbdc0d"
    },
    {
      "from": "00bbdfd4"
    },
    {
      "from": "00ff9898"
    },
    {
      "from": "010037a3"
    },
    {
      "from": "00c80981"
    },
    {
      "from": "00c8098f"
    },
    {
      "from": "00c81781"
    },
    {
      "from": "00c81df2"
    },
    {
      "from": "00c81e41"
    },
    {
      "from": "00bbc402"
    },
    {
      "from": "00bbd764"
    },
    {
      "from": "00bbdbd7"
    },
    {
      "from": "00d1cff0"
    },
    {
      "from": "00d1d002"
    },
    {
      "from": "00d1d05f"
    },
    {
      "from": "00d1d06b"
    },
    {
      "from": "00bbd6c2"
    },
    {
      "from": "00bbd712"
    },
    {
      "from": "00ee966a"
    },
    {
      "from": "00ee9857"
    },
    {
      "from": "00ee97bd"
    },
    {
      "from": "00f35f5c"
    },
    {
      "from": "010167bd"
    },
    {
      "from": "010494ab"
    },
    {
      "from": "0105a819"
    },
    {
      "from": "00b333e7"
    },
    {
      "from": "00cfa57a"
    },
    {
      "from": "00d7f312"
    },
    {
      "from": "00d87d3a"
    },
    {
      "from": "00b04b0d"
    },
    {
      "from": "00b079cc"
    },
    {
      "from": "00b0ba33"
    },
    {
      "from": "00b02fc0"
    },
    {
      "from": "00b7bbd3"
    },
    {
      "from": "00c54785"
    },
    {
      "from": "00c7cf6e"
    },
    {
      "from": "00c7cff5"
    },
    {
      "from": "00ff8071"
    },
    {
      "from": "00ff807f"
    },
    {
      "from": "010339cf"
    },
    {
      "from": "0105aec8"
    },
    {
      "from": "0105af09"
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
  "global:MOV EAX,[0x0167eb10]",
  "global:READ from 0x00b3d3b0",
  "global:get_xrefs_to(0x0167eb10); one READ xref from this function"
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
    "reconstruction/metadata/pkg11-h2-root-accessors/00b3d3b0.json"
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
    "gate-root-slot-00b3d3b0",
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
