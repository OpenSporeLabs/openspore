# Evidence 0x007c79e0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `4eb21ff01e3d00b7b0b9f755dd50bcab6a7e4faf521527b624d75b91fe0f5876`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86:LE:32",
  "calling_convention": "cdecl-compatible no-argument accessor",
  "hidden_receiver": null,
  "ordinary_stack_arguments": [],
  "return_note": "opaque 32-bit service pointer",
  "return_register": "EAX",
  "return_width_bytes": 4,
  "stack_cleanup_bytes": 0,
  "termination": "JMP 0x0067de20; target accessor terminates with plain RET"
}
```

## abi_derived

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function, tools/reconstruction_tooling/abi_infer.py#tail_target=0x0067de20`

```json
{
  "abi": {
    "architecture": "x86-32",
    "receiver": false,
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller"
  },
  "abstained_because": [
    "no_terminal_ret: the only exit observed is a tail jump"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "forwarded_from_tail_target",
    "evidence": "forwarded from the tail target 0x0067de20: ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "EMPTY",
  "conflicts": [],
  "content_sha256": "174989bbed49be4ea72feb9c0f59c4e8177546ecbea702df9c2cd1ddd79f8e76",
  "conventions": {
    "ambiguities": [
      "tail_call"
    ],
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
        "obs-0001"
      ],
      "claim": "no terminal return is present in the listing",
      "confidence": "UNKNOWN",
      "id": "C2"
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
      "claim": "this listing is a tail transfer: it inherits its caller's frame and never runs its own RET",
      "confidence": "UNKNOWN",
      "id": "T1",
      "value": {
        "form": "jmp"
      }
    },
    {
      "based_on": [
        "obs-0001"
      ],
      "claim": "the stack cleanup is caller with 0 byte(s), forwarded from the tail target 0x0067de20; the target's own calling convention is not decided, so none is forwarded (resolved from live listing for 0x0067de20)",
      "confidence": "INFERRED",
      "id": "T1-FWD",
      "value": {
        "target": "0x0067de20",
        "target_calling_convention": null,
        "target_cleanup_side": "caller",
        "target_source": "live listing for 0x0067de20",
        "target_stack_bytes": 0
      }
    }
  ],
  "observations": [
    {
      "at": "0x007c79e0",
      "id": "obs-0001",
      "index": 0,
      "kind": "UNCOND_TRANSFER_OUT",
      "raw": "JMP 0x0067de20",
      "target": "0x0067de20"
    }
  ],
  "parse": {
    "declared_count": 1,
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
    "confidence": "UNKNOWN",
    "register": null,
    "register_class": "unknown",
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
    "form": "jmp",
    "present": true,
    "target": "0x0067de20"
  },
  "target": {
    "address_available": true,
    "image_base": "0x00400000",
    "instructions": 1,
    "syntax": "intel",
    "va": "0x007c79e0"
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
    "va": "0x007e6470"
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
  "count": 1,
  "instructions": [
    {
      "address": "007c79e0",
      "instruction": "JMP 0x0067de20"
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
  "original_bytes": 6592,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86:LE:32\",\n    \"calling_convention\": \"cdecl-compatible no-argument accessor\",\n    \"hidden_receiver\": null,\n    \"ordinary_stack_arguments\": [],\n    \"return_note\": \"opaque 32-bit service pointer\",\n    \"return_register\": \"EAX\",\n    \"return_width_bytes\": 4,\n    \"stack_cleanup_bytes\": 0,\n    \"termination\": \"JMP 0x0067de20; target accessor terminates with plain RET\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueRuntimeService,opaque 32-bit service pointer\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-RUNTIME-SERVICES-WAVE7\",\n      \"score\": 27,\n      \"symbol\": \"app_cheat_manager_get_0067dde0\",\n      \"va\": \"0x0067dde0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueRuntimeService\"\n      ],\n      \"package\": \"PKG-RUNTIME-SERVICES-WAVE7\",\n      \"score\": 22,\n      \"symbol\": \"editor_anim_event_message_post_0059d840\",\n      \"va\": \"0x0059d840\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueRuntimeService\"\n      ],\n      \"package\": \"PKG-RUNTIME-SERVICES-WAVE7\",\n      \"score\": 22,\n      \"symbol\": \"editor_anim_event_message_send_0059d8b0\",\n      \"va\": \"0x0059d8b0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueRuntimeService\"\n      ],\n      \"package\": \"PKG-RUNTIME-SERVICES-WAVE7\",\n      \"score\": 22,\n      \"symbol\": \"app_prop_manager_get_global_property_list_006a3310\",\n      \"va\": \"0x006a3310\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueRuntimeService\"\n      ],\n      \"package\": \"PKG-RUNTIME-SERVICES-WAVE7\",\n      \"score\": 22,\n      \"symbol\": \"app_prop_manager_get_supported_types_006a3400\",\n      \"va\": \"0x006a3400\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueRuntimeService\"\n      ],\n      \"package\": \"PKG-RUNTIME-SERVICES-WAVE7\",\n      \"score\": 22,\n      \"symbol\": \"app_canvas_get_message_server_00c871d0\",\n      \"va\": \"0x00c871d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueRuntimeService\"\n      ],\n      \"package\": \"PKG-RUNTIME-SERVICES-WAVE8\",\n      \"score\": 14,\n      \"symbol\": \"ui_layer_manager_get_0067ca90\",\n      \"va\": \"0x0067ca90\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueRuntimeService\"\n      ],\n      \"package\": \"PKG-RUNTIME-SERVICES-WAVE8\",\n      \"score\": 14,\n      \"symbol\": \"anim_manager_get_0067cae0\",\n      \"va\": \"0x0067cae0\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Static mechanics and x86-32 ABI reviewed from live Ghidra; runtime values, concrete owners, and unresolved ports remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueRuntimeService\",\n  \"cluster\": null,\n  \"confidence\": 0.7,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007e6470\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x007e64fe\",\n        \"direction\": \"in\",\n        \"other\": \"0x007e6470\",\n        \"reference_type\": \"thunk\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 1,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0242\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"SUPPORTED\",\n  \"globals\": [\n    \"global:0x015fd8a4\",\n    \"global:read at 0x0067de20; write at 0x0067e034 in FUN_0067e030\"\n  ],\n  \"integration_status\": \"integrated\",\n  \"name\": \"app_id_generator_get_007c79e0\",\n  \"normalized_symbol\": \"app_id_generator_get_007c79e0\",\n  \"observed_mechanics\": [\n    \"{\\\"body_end_inclusive\\\": \\\"0x007c79e0\\\", \\\"entry\\\": \\\"0x007c79e0\\\", \\\"global_slot\\\": \\\"0x015fd8a4\\\", \\\"instruction_count\\\": 1, \\\"mechanics\\\": [\\\"tail-transfer to 0x0067de20\\\", \\\"the target accessor reads one four-byte global word at 0x015fd8a4\\\", \\\"return the 32-bit service pointer unchanged\\\"], \\\"raw_bytes_hex\\\": \\\"e93b64ebff\\\", \\\"tail_target\\\": \\\"0x0067de20\\\"}\"\n  ],\n  \"ownership\": {\n    \"claimability\": \"do_not_claim\",\n    \"handoff_packages\": [\n      \"PKG-RUNTIME-SERVICES-WAVE7\"\n    ],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": \"PKG-RUNTIME-SERVICES-WAVE7\",\n    \"queue_state\": null\n  },\n  \"package\": \"PKG-RUNTIME-SERVICES-WAVE7\",\n  \"reconstructed\": true,\n  \"review_status\": \"approved_after_parallel_review\",\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"required\"\n    ],\n    \"validated\": 0\n  },\n  \"runtime_gated\": true,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": \"static_reconstruction_runtime_gated\",\n  \"services\
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
  "body_end": "007c79e4",
  "body_span_bytes": 5,
  "body_start": "007c79e0",
  "callees": [],
  "callers": [
    "FUN_007e6470"
  ],
  "classification": "thunk",
  "dispatch": null,
  "entry_point": "007c79e0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "App::cIDGenerator::Get",
  "namespace": "App",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "cIDGenerator *",
  "return_type_resolved": true,
  "rva": "0x3c79e0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "cIDGenerator * App::cIDGenerator::Get(void)",
  "size_bytes": 5,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x007c79e0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 2,
  "xrefs": [
    {
      "from": "007e64fe"
    },
    {
      "from": "007e90df"
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
  "global:0x015fd8a4",
  "global:read at 0x0067de20; write at 0x0067e034 in FUN_0067e030"
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg_runtime_services_wave7/runtime_services_wave7.cpp",
  "files": [
    "src/reconstruction/pkg_runtime_services_wave7/runtime_services_wave7.cpp",
    "src/reconstruction/pkg_runtime_services_wave7/runtime_services_wave7.hpp",
    "src/reconstruction/pkg_runtime_services_wave7/runtime_services_wave7_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave7/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-runtime-services-wave7/007c79e0.json"
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
    "required"
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
  "OpaqueRuntimeService",
  "opaque 32-bit service pointer"
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
