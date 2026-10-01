# Evidence 0x00b3d420

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `577ed9d40530eafb8feed2371d7204799089facdc4e085eb3d550eeda5b48d5b`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__cdecl",
  "ordinary_stack_argument_slots": 0,
  "return_note": "borrowed pointer word",
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
  "content_sha256": "cb9a86e1ec2b799635b8b8a4daee8eab47ce30504539ed43b5ab79df29bfa66c",
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
    "persisted_calling_convention": "__cdecl"
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
      "at": "0x00b3d420",
      "definite": true,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,[0x0167eb2c]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00b3d425",
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
    "va": "0x00b3d420"
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
    "va": "0x00b02b90"
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
    "va": "0x00b2b1e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b2b430"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b2bbe0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b2f350"
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
    "va": "0x00b32dd0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b32f60"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b330e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b33350"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b334e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b73f30"
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
      "address": "00b3d420",
      "instruction": "MOV EAX,[0x0167eb2c]"
    },
    {
      "address": "00b3d425",
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
  "original_bytes": 13450,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__cdecl\",\n    \"ordinary_stack_argument_slots\": 0,\n    \"return_note\": \"borrowed pointer word\",\n    \"return_register\": \"EAX\",\n    \"return_width_bytes\": 4,\n    \"stack_cleanup_bytes\": 0\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"shared_types:READ,undefined4\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-06-WAVE6-APP-MANAGERS\",\n      \"score\": 8,\n      \"symbol\": \"App_IStateManager_Get_0067dce0\",\n      \"va\": \"0x0067dce0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:READ,undefined4\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-06-WAVE6-APP-MANAGERS\",\n      \"score\": 8,\n      \"symbol\": \"App_IPropManager_Get_0067ddf0\",\n      \"va\": \"0x0067ddf0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:READ\"\n      ],\n      \"package\": \"PKG-RUNTIME-SERVICES-WAVE8\",\n      \"score\": 3,\n      \"symbol\": \"ui_layer_manager_get_0067ca90\",\n      \"va\": \"0x0067ca90\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:READ\"\n      ],\n      \"package\": \"PKG-RUNTIME-SERVICES-WAVE8\",\n      \"score\": 3,\n      \"symbol\": \"anim_manager_get_0067cae0\",\n      \"va\": \"0x0067cae0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:READ\"\n      ],\n      \"package\": \"PKG-RUNTIME-SERVICES-WAVE8\",\n      \"score\": 3,\n      \"symbol\": \"app_locale_manager_get_0067de00\",\n      \"va\": \"0x0067de00\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:READ\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE7\",\n      \"score\": 3,\n      \"symbol\": \"simulator_game_input_manager_get_00b3d350\",\n      \"va\": \"0x00b3d350\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:undefined4\"\n      ],\n      \"package\": \"PKG-11-H2-ROOT-ACCESSORS\",\n      \"score\": 3,\n      \"symbol\": \"root_accessor_00b3d3b0\",\n      \"va\": \"0x00b3d3b0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:undefined4\"\n      ],\n      \"package\": \"PKG-11-H2-ROOT-ACCESSORS\",\n      \"score\": 3,\n      \"symbol\": \"root_accessor_00b3d3e0\",\n      \"va\": \"0x00b3d3e0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b02b90\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b04aa0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b07980\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b07fa0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b2b1e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b2b430\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b2bbe0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b2f350\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b32b20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b32ce0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b32dd0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b32f60\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b330e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b33350\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b334e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b73f30\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b76f10\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b77db0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bac830\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bad080\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00badd10\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bbc540\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bbc870\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bbecc0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bc1b10\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c46e20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c53800\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c53bc0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c70c90\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va
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
  "body_end": "00b3d425",
  "body_span_bytes": 6,
  "body_start": "00b3d420",
  "callees": [],
  "callers": [
    "FUN_00b02b90",
    "FUN_00c809d0",
    "FUN_00bc1b10",
    "FUN_00c53800",
    "FUN_00c81ab0",
    "FUN_00bbc540",
    "FUN_00b07980",
    "FUN_00c810e0",
    "FUN_00b77db0",
    "FUN_00c53bc0",
    "FUN_01030fd0",
    "FUN_00d75740",
    "FUN_01071d70",
    "FUN_00bbecc0",
    "FUN_00b2b430",
    "FUN_010317d0",
    "FUN_00b07fa0",
    "FUN_00c81f40",
    "FUN_00b2bbe0",
    "FUN_00b32ce0",
    "FUN_00f35c80",
    "FUN_00b33350",
    "FUN_00b73f30",
    "FUN_00b330e0",
    "FUN_00c70c90",
    "FUN_00ee7cb0",
    "FUN_00c46e20",
    "FUN_00b32b20",
    "FUN_00b32f60",
    "FUN_00b04aa0",
    "FUN_00b32dd0",
    "FUN_01049040",
    "FUN_00c80680",
    "FUN_00bac830",
    "FUN_00b2b1e0",
    "FUN_00bbc870",
    "FUN_00b76f10",
    "FUN_00c81890",
    "FUN_00b2f350",
    "FUN_0105a110",
    "FUN_00badd10",
    "FUN_00b334e0",
    "FUN_010166c0",
    "FUN_00bad080",
    "FUN_00e9c9a0",
    "FUN_00fdeac0",
    "FUN_010534c0"
  ],
  "classification": "stub",
  "dispatch": null,
  "entry_point": "00b3d420",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "Simulator::cGameModeManager::Get",
  "namespace": "Simulator",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "cGameModeManager *",
  "return_type_resolved": true,
  "rva": "0x73d420",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "cGameModeManager * Simulator::cGameModeManager::Get(void)",
  "size_bytes": 6,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00b3d420",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 59,
  "xrefs": [
    {
      "from": "00badd16"
    },
    {
      "from": "00badd23"
    },
    {
      "from": "00bac84a"
    },
    {
      "from": "00bad143"
    },
    {
      "from": "00c46e5d"
    },
    {
      "from": "00c81f8a"
    },
    {
      "from": "00c818ae"
    },
    {
      "from": "00c80a2d"
    },
    {
      "from": "00b2bc8a"
    },
    {
      "from": "00b2bda1"
    },
    {
      "from": "00b02b9b"
    },
    {
      "from": "00b07fea"
    },
    {
      "from": "00b2b24b"
    },
    {
      "from": "00b2b537"
    },
    {
      "from": "00b2f4c3"
    },
    {
      "from": "00b32b7c"
    },
    {
      "from": "00b32d1c"
    },
    {
      "from": "00bbc5ae"
    },
    {
      "from": "00bbc88c"
    },
    {
      "from": "00bc1b30"
    },
    {
      "from": "00c806d9"
    },
    {
      "from": "00b32e3f"
    },
    {
      "from": "00b32fc1"
    },
    {
      "from": "00b33104"
    },
    {
      "from": "00b33509"
    },
    {
      "from": "00b73ffe"
    },
    {
      "from": "00b77e2d"
    },
    {
      "from": "00b76fda"
    },
    {
      "from": "00c53a1b"
    },
    {
      "from": "00c53f7b"
    },
    {
      "from": "00c70cfd"
    },
    {
      "from": "00c814be"
    },
    {
      "from": "00c81dff"
    },
    {
      "from": "00ee7cfe"
    },
    {
      "from": "00f35dc0"
    },
    {
      "from": "00fdeb8f"
    },
    {
      "from": "010725b8"
    },
    {
      "from": "01016749"
    },
    {
      "from": "010312da"
    },
    {
      "from": "00bbed67"
    },
    {
      "from": "0103181f"
    },
    {
      "from": "010490f9"
    },
    {
      "from": "010534cf"
    },
    {
      "from": "0105a6e3"
    },
    {
      "from": "00b333db"
    },
    {
      "from": "00b04b1e"
    },
    {
      "from": "00b079e1"
    },
    {
      "from": "00c53338"
    },
    {
      "from": "00c53412"
    },
    {
      "from": "00c535b8"
    },
    {
      "from": "00c541ad"
    },
    {
      "from": "00c54271"
    },
    {
      "from": "00e9ca50"
    },
    {
      "from": "010320a0"
    },
    {
      "from": "01032f96"
    },
    {
      "from": "01033404"
    },
    {
      "from": "010338b5"
    },
    {
      "from": "0102610e"
    },
    {
      "from": "00d75764"
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
  "global:0x0167eb2c",
  "global:g_wave6_app_manager_globals.simulator_game_mode_manager_0167eb2c"
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/wave6-app-managers/app_managers_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave6-app-managers/00b3d420.json"
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
  "status": "unresolved"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "OpaqueSimulatorGameModeManager*",
  "READ",
  "borrowed pointer word",
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
