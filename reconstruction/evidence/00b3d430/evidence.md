# Evidence 0x00b3d430

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `dbec3e2bb094cdc46273e984b9410375e3405c62444e8806b6c1cfed3b9d4d47`

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
  "content_sha256": "7c14cbb07c3ce9aa99dfbdf7c66adb3dd0483280f08a47c0f07b2ec095d09d3a",
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
      "at": "0x00b3d430",
      "definite": true,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,[0x0167eb30]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00b3d435",
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
    "va": "0x00b3d430"
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
    "va": "0x00ae3d70"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ae6240"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b32b20"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b32ce0"
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
    "va": "0x00b93550"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b9d820"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ba0080"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bb2330"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bb23e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bba990"
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
      "address": "00b3d430",
      "instruction": "MOV EAX,[0x0167eb30]"
    },
    {
      "address": "00b3d435",
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
  "original_bytes": 17368,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"cdecl-compatible no-argument accessor\",\n    \"hidden_receiver\": null,\n    \"ordinary_stack_argument_slots\": 0,\n    \"ret_form\": \"RET\",\n    \"return_note\": \"opaque 32-bit slot word\",\n    \"return_register\": \"EAX\",\n    \"return_width_bytes\": 4,\n    \"stack_cleanup_bytes\": 0\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:None,RootWord,opaque 32-bit slot word,undefined4\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-11-H2-ROOT-ACCESSORS\",\n      \"score\": 30,\n      \"symbol\": \"root_accessor_00b3d3b0\",\n      \"va\": \"0x00b3d3b0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:None,RootWord,opaque 32-bit slot word,undefined4\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-11-H2-ROOT-ACCESSORS\",\n      \"score\": 30,\n      \"symbol\": \"root_accessor_00b3d3e0\",\n      \"va\": \"0x00b3d3e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:None,RootWord,opaque 32-bit slot word,undefined4\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-11-H2-ROOT-ACCESSORS\",\n      \"score\": 30,\n      \"symbol\": \"root_accessor_00b3d3f0\",\n      \"va\": \"0x00b3d3f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-13-E3-EMPIRE-STATE-WAVE2\",\n      \"score\": 8,\n      \"symbol\": \"SpeciesProfileSelector_00c30cc0\",\n      \"va\": \"0x00c30cc0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-13-E3-EMPIRE-STATE-WAVE2\",\n      \"score\": 8,\n      \"symbol\": \"ArchetypeRelationshipsID_00c30e20\",\n      \"va\": \"0x00c30e20\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-11-SIM-CORE\",\n      \"score\": 8,\n      \"symbol\": \"Simulator_IsNotStarOrBinaryStar\",\n      \"va\": \"0x00c8b6b0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-13-E2-DIPLOMACY-ALT\",\n      \"score\": 8,\n      \"symbol\": \"RelationshipScoreBand_00d00d00\",\n      \"va\": \"0x00d00d00\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-13-C3-CREATURE-PROGRESSION-WAVE2\",\n      \"score\": 8,\n      \"symbol\": \"Simulator_cCreatureGameData_Get_00d2e340\",\n      \"va\": \"0x00d2e340\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": \"clean\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"None\",\n  \"cluster\": \"unknown-fun-mass\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ae3d70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ae6240\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b32b20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b32ce0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b32e80\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b33030\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b33130\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b33350\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b33540\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b335d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b93550\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b9d820\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ba0080\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bb2330\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bb23e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bba990\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bbe740\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bd8110\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bd8a00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bd8b10\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bd9a80\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00becd70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c466d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c4b8f0\"\n    
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
  "body_end": "00b3d435",
  "body_span_bytes": 6,
  "body_start": "00b3d430",
  "callees": [],
  "callers": [
    "FUN_00e07e70",
    "FUN_00ebb8b0",
    "FUN_00c60af0",
    "FUN_00c62ff0",
    "FUN_00bd9a80",
    "FUN_01030fd0",
    "FUN_00bb2330",
    "FUN_00b32e80",
    "FUN_01073044",
    "FUN_00d41560",
    "FUN_00c70fb0",
    "FUN_00d1c610",
    "FUN_00cfa410",
    "FUN_00e98d30",
    "FUN_00ff6450",
    "FUN_00c932a0",
    "FUN_00f355b0",
    "FUN_00c466d0",
    "FUN_00bd8b10",
    "FUN_00ebcc80",
    "FUN_010593e0",
    "FUN_00b33130",
    "FUN_01049040",
    "FUN_00bba990",
    "FUN_00c7f5b0",
    "FUN_00b9d820",
    "FUN_00bd8a00",
    "FUN_00c4ccd0",
    "FUN_00c82d50",
    "FUN_0105a050",
    "FUN_00cfbc10",
    "FUN_00bd8110",
    "FUN_00e9c9a0",
    "FUN_00e2eba0",
    "FUN_01066f20",
    "FUN_00cdd9c0",
    "FUN_00d07470",
    "FUN_00ba0080",
    "FUN_00c810e0",
    "FUN_01056160",
    "FUN_00c99dc0",
    "FUN_0100d230",
    "FUN_01003690",
    "FUN_01071d70",
    "FUN_00c93160",
    "FUN_00becd70",
    "FUN_00c4b8f0",
    "FUN_01072d40",
    "FUN_00ff63e0",
    "FUN_00ae3d70",
    "FUN_00c7ee50",
    "FUN_00b32ce0",
    "FUN_00b33350",
    "FUN_00c6ab90",
    "FUN_00b33030",
    "FUN_00f37690",
    "FUN_0106fc90",
    "FUN_00c60cc0",
    "FUN_00b335d0",
    "FUN_00f347e0",
    "FUN_00ff5930",
    "FUN_00b32b20",
    "FUN_00b33540",
    "FUN_00bb23e0",
    "FUN_0105b350",
    "FUN_00b93550",
    "FUN_00ae6240",
    "FUN_0100a960",
    "FUN_00c830f0",
    "FUN_00ff7530",
    "FUN_00fdf9f0",
    "FUN_00bbe740",
    "FUN_00c54380",
    "FUN_00cbbdc0",
    "FUN_01065ba0",
    "FUN_01068970"
  ],
  "classification": "stub",
  "dispatch": null,
  "entry_point": "00b3d430",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00b3d430",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x73d430",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00b3d430(void)",
  "size_bytes": 6,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00b3d430",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 100,
  "xrefs": [
    {
      "from": "00bb23c0"
    },
    {
      "from": "00bb246c"
    },
    {
      "from": "00ae64e5"
    },
    {
      "from": "00bd8b41"
    },
    {
      "from": "00bd8112"
    },
    {
      "from": "00bba99d"
    },
    {
      "from": "00bba9de"
    },
    {
      "from": "00b3383e"
    },
    {
      "from": "00b32b4a"
    },
    {
      "from": "00b32cea"
    },
    {
      "from": "00b32ece"
    },
    {
      "from": "00b33043"
    },
    {
      "from": "00b33168"
    },
    {
      "from": "00b3358d"
    },
    {
      "from": "0100acb1"
    },
    {
      "from": "00c9324a"
    },
    {
      "from": "00bd8a51"
    },
    {
      "from": "00b935b2"
    },
    {
      "from": "00bbe7e0"
    },
    {
      "from": "00becec3"
    },
    {
      "from": "00ebcc9b"
    },
    {
      "from": "00c70fb7"
    },
    {
      "from": "00fdfa7c"
    },
    {
      "from": "00fdfa89"
    },
    {
      "from": "00ba012c"
    },
    {
      "from": "00c935fd"
    },
    {
      "from": "00ff59c2"
    },
    {
      "from": "01003796"
    },
    {
      "from": "010038ac"
    },
    {
      "from": "00c46764"
    },
    {
      "from": "00c4b8f9"
    },
    {
      "from": "00c4ce35"
    },
    {
      "from": "00c4ce49"
    },
    {
      "from": "00c4ce5d"
    },
    {
      "from": "00c54516"
    },
    {
      "from": "00bd9aee"
    },
    {
      "from": "00c60b4e"
    },
    {
      "from": "00c60b91"
    },
    {
      "from": "00c60bd4"
    },
    {
      "from": "00c6abdb"
    },
    {
      "from": "00c7ef03"
    },
    {
      "from": "00c7ef87"
    },
    {
      "from": "00c7f5c7"
    },
    {
      "from": "00c7f6cf"
    },
    {
      "from": "00c81699"
    },
    {
      "from": "00c82e1a"
    },
    {
      "from": "00c83106"
    },
    {
      "from": "00c83780"
    },
    {
      "from": "00c83790"
    },
    {
      "from": "00cbc1a3"
    },
    {
      "from": "00d1c9b6"
    },
    {
      "from": "00cdda4d"
    },
    {
      "from": "00b9f596"
    },
    {
      "from": "00c99ec0"
    },
    {
      "from": "00d074e9"
    },
    {
      "from": "00d0755e"
    },
    {
      "from": "00d415fd"
    },
    {
      "from": "00e092f4"
    },
    {
      "from": "00c60d1b"
    },
    {
      "from": "00c60d59"
    },
    {
      "from": "00c60da9"
    },
    {
      "from": "00e98d38"
    },
    {
      "from": "00ebb964"
    },
    {
      "from": "00f34c8e"
    },
    {
      "from": "00f377ff"
    },
    {
      "from": "01066f42"
    },
    {
      "from": "01065ba6"
    },
    {
      "from": "01065bc8"
    },
    {
      "from": "01065be6"
    },
    {
      "from": "01065c0a"
    },
    {
      "from": "01071e03"
    },
    {
      "from": "010725b3"
    },
    {
      "from": "0100d284"
    },
    {
      "from": "010310a1"
    },
    {
      "from": "01031245"
    },
    {
      "from": "01031301"
    },
    {
      "from": "010494eb"
    },
    {
      "from": "010498ce"
    },
    {
      "from": "010566b2"
    },
    {
      "from": "0105a0de"
    },
    {
      "from": "0105959c"
    },
    {
      "from": "0105b48f"
    },
    {
     
[TRUNCATED]
```

## globals

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "global:MOV EAX,[0x0167eb30]",
  "global:READ from 0x00b3d430",
  "global:get_xrefs_to(0x0167eb30); one READ xref from this function"
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
    "reconstruction/metadata/pkg11-h2-root-accessors/00b3d430.json"
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
    "gate-root-slot-00b3d430",
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
