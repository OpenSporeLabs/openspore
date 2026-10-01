# Evidence 0x00b3d3e0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `951d13488013b8e504ec40d02daf62aafb9222395200c5464c44d139f8303ab6`

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
  "content_sha256": "6c97b3ddf6128d29db766c6057d4f21bfe494a354c212831a4223a84128ed134",
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
      "at": "0x00b3d3e0",
      "definite": true,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,[0x0167eb24]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00b3d3e5",
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
    "va": "0x00b3d3e0"
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
    "va": "0x00adfd60"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ae9c90"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00aea720"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00aea8e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00aea9e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00aeaa80"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00aeab40"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00aeb3e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00aecf90"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00aed2c0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b328e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b32970"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b32aa0"
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
      "address": "00b3d3e0",
      "instruction": "MOV EAX,[0x0167eb24]"
    },
    {
      "address": "00b3d3e5",
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
  "original_bytes": 17377,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"cdecl-compatible no-argument accessor\",\n    \"hidden_receiver\": null,\n    \"ordinary_stack_argument_slots\": 0,\n    \"ret_form\": \"RET\",\n    \"return_note\": \"opaque 32-bit slot word\",\n    \"return_register\": \"EAX\",\n    \"return_width_bytes\": 4,\n    \"stack_cleanup_bytes\": 0\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:None,RootWord,opaque 32-bit slot word,undefined4\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-11-H2-ROOT-ACCESSORS\",\n      \"score\": 30,\n      \"symbol\": \"root_accessor_00b3d3b0\",\n      \"va\": \"0x00b3d3b0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:None,RootWord,opaque 32-bit slot word,undefined4\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-11-H2-ROOT-ACCESSORS\",\n      \"score\": 30,\n      \"symbol\": \"root_accessor_00b3d3f0\",\n      \"va\": \"0x00b3d3f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:None,RootWord,opaque 32-bit slot word,undefined4\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-11-H2-ROOT-ACCESSORS\",\n      \"score\": 30,\n      \"symbol\": \"root_accessor_00b3d430\",\n      \"va\": \"0x00b3d430\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-13-E3-EMPIRE-STATE-WAVE2\",\n      \"score\": 8,\n      \"symbol\": \"SpeciesProfileSelector_00c30cc0\",\n      \"va\": \"0x00c30cc0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-13-E3-EMPIRE-STATE-WAVE2\",\n      \"score\": 8,\n      \"symbol\": \"ArchetypeRelationshipsID_00c30e20\",\n      \"va\": \"0x00c30e20\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-11-SIM-CORE\",\n      \"score\": 8,\n      \"symbol\": \"Simulator_IsNotStarOrBinaryStar\",\n      \"va\": \"0x00c8b6b0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-13-E2-DIPLOMACY-ALT\",\n      \"score\": 8,\n      \"symbol\": \"RelationshipScoreBand_00d00d00\",\n      \"va\": \"0x00d00d00\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-13-C3-CREATURE-PROGRESSION-WAVE2\",\n      \"score\": 8,\n      \"symbol\": \"Simulator_cCreatureGameData_Get_00d2e340\",\n      \"va\": \"0x00d2e340\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": \"clean\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"None\",\n  \"cluster\": \"unknown-fun-mass\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00adf840\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00adfd60\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ae9c90\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00aea720\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00aea8e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00aea9e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00aeaa80\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00aeab40\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00aeb3e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00aecf90\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00aed2c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b328e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b32970\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b32aa0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b32b20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b32ce0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b33130\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b33350\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b335d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b5ce70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bbcf00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00be88d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00beb6d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bf45f0\"\n    
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
  "body_end": "00b3d3e5",
  "body_span_bytes": 6,
  "body_start": "00b3d3e0",
  "callees": [],
  "callers": [
    "FUN_00c505a0",
    "FUN_00ceb090",
    "FUN_01038410",
    "FUN_01014540",
    "FUN_00aed2c0",
    "FUN_00bf45f0",
    "FUN_00aeaa80",
    "FUN_00c4f9d0",
    "FUN_00adf840",
    "FUN_01012aa0",
    "FUN_01053980",
    "FUN_00cf9110",
    "FUN_00c5c470",
    "FUN_00cf3bf0",
    "FUN_00c44f20",
    "FUN_00cf90a0",
    "FUN_00bbcf00",
    "FUN_00b32970",
    "FUN_00feba10",
    "FUN_00c46590",
    "FUN_00b328e0",
    "FUN_00d2cb10",
    "FUN_00cfbc10",
    "FUN_00fdd5a0",
    "FUN_00ce8ee0",
    "FUN_00c81ab0",
    "FUN_01000000",
    "FUN_00c810e0",
    "FUN_00ff45e0",
    "FUN_00c562b0",
    "FUN_00c62100",
    "FUN_00c4f960",
    "FUN_00bff2d0",
    "FUN_00aeb3e0",
    "FUN_00c24760",
    "FUN_00aecf90",
    "FUN_00fdfbc0",
    "FUN_00b32ce0",
    "FUN_00b33350",
    "FUN_00cf9040",
    "FUN_010527f0",
    "FUN_00b335d0",
    "FUN_00fe5a20",
    "FUN_01030ef0",
    "FUN_00fe2ab0",
    "FUN_00c830f0",
    "FUN_01066dd0",
    "FUN_00be88d0",
    "FUN_00c82400",
    "FUN_00c4ec90",
    "FUN_00c4c4b0",
    "FUN_00c568d0",
    "FUN_00aeab40",
    "FUN_0106ada0",
    "FUN_00c4fe60",
    "FUN_00d2c200",
    "FUN_0107c1e0",
    "FUN_01030fd0",
    "FUN_00cccc50",
    "FUN_00adfd60",
    "FUN_00ce1690",
    "FUN_00c34320",
    "FUN_00e02f00",
    "FUN_00fdade0",
    "FUN_00b33130",
    "FUN_00d46c30",
    "FUN_0103fc10",
    "FUN_00dbb840",
    "FUN_01009df0",
    "FUN_00c484e0",
    "FUN_01066d60",
    "FUN_00b5ce70",
    "FUN_00ae9c90",
    "FUN_00aea9e0",
    "FUN_00d38930",
    "FUN_00c4ecc0",
    "FUN_00c4fc00",
    "FUN_00fdeac0",
    "FUN_00cd7100",
    "FUN_00d2c280",
    "FUN_00d4ee20",
    "FUN_010531b0",
    "FUN_00cc93b0",
    "FUN_00fef140",
    "FUN_00cd7320",
    "FUN_00aea720",
    "FUN_00caa360",
    "FUN_00c4ecf0",
    "FUN_01058c90",
    "FUN_010134d0",
    "FUN_00c56260",
    "FUN_010027b0",
    "FUN_00b32b20",
    "FUN_00c4fa40",
    "FUN_00ce1190",
    "FUN_00db5e80",
    "FUN_00aea8e0",
    "FUN_0100a160",
    "FUN_00b32aa0",
    "FUN_0103fe90",
    "FUN_00c4ed20",
    "FUN_00beb6d0"
  ],
  "classification": "stub",
  "dispatch": null,
  "entry_point": "00b3d3e0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00b3d3e0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x73d3e0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00b3d3e0(void)",
  "size_bytes": 6,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00b3d3e0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 100,
  "xrefs": [
    {
      "from": "00aeb4cd"
    },
    {
      "from": "00aeb562"
    },
    {
      "from": "00aeb577"
    },
    {
      "from": "00aea786"
    },
    {
      "from": "00aeab6b"
    },
    {
      "from": "00c34442"
    },
    {
      "from": "00feba17"
    },
    {
      "from": "00feba2a"
    },
    {
      "from": "00adfea3"
    },
    {
      "from": "00adfeb8"
    },
    {
      "from": "00adfc55"
    },
    {
      "from": "00be8a12"
    },
    {
      "from": "00beb86f"
    },
    {
      "from": "00bf46cf"
    },
    {
      "from": "00caa5db"
    },
    {
      "from": "00cf9075"
    },
    {
      "from": "00cf90e9"
    },
    {
      "from": "00cf9168"
    },
    {
      "from": "00c44f31"
    },
    {
      "from": "00ff4673"
    },
    {
      "from": "010028aa"
    },
    {
      "from": "0100294e"
    },
    {
      "from": "010000c8"
    },
    {
      "from": "01000141"
    },
    {
      "from": "0103fe4a"
    },
    {
      "from": "00aeaad8"
    },
    {
      "from": "00aed02d"
    },
    {
      "from": "01066e08"
    },
    {
      "from": "00b33716"
    },
    {
      "from": "00b3371f"
    },
    {
      "from": "00b3297e"
    },
    {
      "from": "00b32989"
    },
    {
      "from": "00b3299f"
    },
    {
      "from": "00b32b94"
    },
    {
      "from": "00b32d34"
    },
    {
      "from": "00b33131"
    },
    {
      "from": "00bbd060"
    },
    {
      "from": "00bff563"
    },
    {
      "from": "01066da7"
    },
    {
      "from": "00b3293c"
    },
    {
      "from": "00b32b02"
    },
    {
      "from": "00b32b0b"
    },
    {
      "from": "00b3338e"
    },
    {
      "from": "00b5cf28"
    },
    {
      "from": "00d3893d"
    },
    {
      "from": "00c24837"
    },
    {
      "from": "00cc9412"
    },
    {
      "from": "00c46663"
    },
    {
      "from": "00c466af"
    },
    {
      "from": "00c48585"
    },
    {
      "from": "00aeaa18"
    },
    {
      "from": "00c4c56e"
    },
    {
      "from": "00c4c582"
    },
    {
      "from": "00c4c591"
    },
    {
      "from": "00c4c5a8"
    },
    {
      "from": "00c4eca1"
    },
    {
      "from": "00c4ecd1"
    },
    {
      "from": "00c4ecff"
    },
    {
      "from": "00c4ed2f"
    },
    {
      "from": "00c4fcca"
    },
    {
      "from": "00c4fcde"
    },
    {
      "from": "00c4fdb9"
    },
    {
      "from": "00c4fdcd"
    },
    {
      "from": "00c4ff92"
    },
    {
      "from": "00c500b6"
    },
    {
      "from": "00c50113"
    },
    {
      "from": "00c5012b"
    },
    {
      "from": "00c4f9ef"
    },
    {
      "from": "00
[TRUNCATED]
```

## globals

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "global:MOV EAX,[0x0167eb24]",
  "global:READ from 0x00b3d3e0",
  "global:get_xrefs_to(0x0167eb24); one READ xref from this function"
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
    "reconstruction/metadata/pkg11-h2-root-accessors/00b3d3e0.json"
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
    "gate-root-slot-00b3d3e0",
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
