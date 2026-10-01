# Evidence 0x0067dcf0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `7b993b63fd647d80a1cfdac85f216cf78bc16e54b93f7b2c2f6ab23de8711a4b`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "__cdecl",
  "ordinary_stack_arguments": [],
  "return_register": "EAX",
  "return_semantics": "borrowed 32-bit service pointer word returned unchanged",
  "return_width_bytes": 4,
  "stack_cleanup_bytes": 0,
  "termination": "plain RET"
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
  "content_sha256": "3b420a9be78c7b6805a5c3c59726efc474d040c8be5ed1c7fc682aad8fb53f4e",
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
      "at": "0x0067dcf0",
      "definite": true,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,[0x015fd89c]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x0067dcf5",
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
    "va": "0x0067dcf0"
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
    "va": "0x00601fd0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00603f10"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00609710"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0075df60"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0075e900"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0075f030"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x007e9db0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x007f4710"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x008013d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x008027e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00812c90"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00812f70"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00812ff0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x008131b0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00f47580"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00f47ed0"
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
      "address": "0067dcf0",
      "instruction": "MOV EAX,[0x015fd89c]"
    },
    {
      "address": "0067dcf5",
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
  "original_bytes": 10158,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"__cdecl\",\n    \"ordinary_stack_arguments\": [],\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"borrowed 32-bit service pointer word returned unchanged\",\n    \"return_width_bytes\": 4,\n    \"stack_cleanup_bytes\": 0,\n    \"termination\": \"plain RET\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-06-WAVE6-APP-MANAGERS\",\n      \"score\": 8,\n      \"symbol\": \"App_IStateManager_Get_0067dce0\",\n      \"va\": \"0x0067dce0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-06-WAVE6-APP-MANAGERS\",\n      \"score\": 8,\n      \"symbol\": \"App_IPropManager_Get_0067ddf0\",\n      \"va\": \"0x0067ddf0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"WAVE6-ENGINE-RUNTIME\",\n      \"score\": 8,\n      \"symbol\": \"app_system_service_gate_dispatch_007e5f30\",\n      \"va\": \"0x007e5f30\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"WAVE6-ENGINE-RUNTIME\",\n      \"score\": 8,\n      \"symbol\": \"app_system_initialize_plugins_007e93d0\",\n      \"va\": \"0x007e93d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-APP-SERVICES-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"service_005f9230\",\n      \"va\": \"0x005f9230\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-APP-SERVICES-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"service_005f9310\",\n      \"va\": \"0x005f9310\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-APP-SERVICES-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"service_005fa8d0\",\n      \"va\": \"0x005fa8d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-APP-SERVICES-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"service_005fc330\",\n      \"va\": \"0x005fc330\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"The static four-byte slot read and unchanged EAX return are exact; publisher, concrete manager, ownership, and runtime publication remain unresolved.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"pass_after_repair\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueWave6ConfigManager\",\n  \"cluster\": null,\n  \"confidence\": 0.96,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00601fd0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00603f10\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00609710\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0075df60\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0075e900\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0075f030\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007e9db0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007f4710\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x008013d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x008027e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00812c90\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00812f70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00812ff0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x008131b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00f47580\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00f47ed0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00f51680\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x0060211c\",\n        \"direction\": \"in\",\n        \"other\": \"0x00601fd0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0060216e\",\n        \"direction\": \"in\",\n        \"other\": \"0x00601fd0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00603f67\",\n        \"direction\": \"in\",\n        \"other\": \"0x00603f10\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00609716\",\n        \"direction\": \"in\",\n        \"other\": \"0x00609710\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0075df85\",\n        \"direction\": \"in\",\n        \"other\": \"0x0075df60\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0075ec0c\",\n        \"direction\": \"in\",\n        \"other\": \"0x0075e900\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0075f239\",\n        \"direction\": \"in\",\n        \"other\": \"0x0075f030\",\n        \"reference_typ
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
  "body_end": "0067dcf5",
  "body_span_bytes": 6,
  "body_start": "0067dcf0",
  "callees": [],
  "callers": [
    "FUN_00812f70",
    "FUN_0075e900",
    "FUN_00812ff0",
    "FUN_008027e0",
    "FUN_00603f10",
    "FUN_008013d0",
    "FUN_00812c90",
    "FUN_00f51680",
    "FUN_00f47580",
    "FUN_00601fd0",
    "FUN_0075f030",
    "FUN_007e9db0",
    "FUN_00609710",
    "FUN_008131b0",
    "FUN_00f47ed0",
    "FUN_0075df60",
    "FUN_007f4710"
  ],
  "classification": "stub",
  "dispatch": null,
  "entry_point": "0067dcf0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "App::IConfigManager::Get",
  "namespace": "App",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "IConfigManager *",
  "return_type_resolved": true,
  "rva": "0x27dcf0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "IConfigManager * App::IConfigManager::Get(void)",
  "size_bytes": 6,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x0067dcf0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 24,
  "xrefs": [
    {
      "from": "00f47590"
    },
    {
      "from": "00f481fe"
    },
    {
      "from": "00f4843c"
    },
    {
      "from": "00802837"
    },
    {
      "from": "008013df"
    },
    {
      "from": "00812f85"
    },
    {
      "from": "00812f9d"
    },
    {
      "from": "0060211c"
    },
    {
      "from": "0060216e"
    },
    {
      "from": "00609716"
    },
    {
      "from": "0075df85"
    },
    {
      "from": "0075ec0c"
    },
    {
      "from": "0075f239"
    },
    {
      "from": "007e9de3"
    },
    {
      "from": "00812c93"
    },
    {
      "from": "008131b6"
    },
    {
      "from": "00813207"
    },
    {
      "from": "007f474c"
    },
    {
      "from": "00813018"
    },
    {
      "from": "00f51eb7"
    },
    {
      "from": "00603f67"
    },
    {
      "from": "00760474"
    },
    {
      "from": "0076047d"
    },
    {
      "from": "007e5fe3"
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
  "global:0x015fd89c"
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/wave6_engine_runtime/engine_runtime.cpp",
  "files": [
    "reconstruction/staging/wave6-engine-runtime/engine_runtime.cpp",
    "reconstruction/staging/wave6-engine-runtime/engine_runtime.hpp",
    "reconstruction/staging/wave6-engine-runtime/engine_runtime_model_test.cpp",
    "src/reconstruction/wave6_engine_runtime/engine_runtime.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/wave6-engine-runtime/0067dcf0.json"
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
    "gate-config-manager-slot-publication"
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
  "OpaqueWave6ConfigManager"
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
