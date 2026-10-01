# Evidence 0x00c31890

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `02303968b753338452d01a35c0860255140ce3ee382262a46003dd83cd733290`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "thiscall",
  "hidden_this_register": "ECX",
  "hidden_this_type": "OpaqueEmpireMetricState*",
  "return_type": "float",
  "return_width_bytes": 4,
  "stack_arguments": [],
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
    "calling_convention": "__thiscall",
    "hidden_this": true,
    "hidden_this_register": "ECX",
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET",
    "return_register": "ST0",
    "return_semantics": "float_or_x87_in_ST0",
    "saved_registers": [
      "ESI"
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +4, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "c7c15c13fb952fdf7a7f51f738c7b1e79c5ce9338b090e068607c2d79fe93da1",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall",
      "__fastcall"
    ],
    "confidence": "SUPPORTED",
    "corroboration": "persisted_agrees"
  },
  "cross_validation": {
    "agreement": true,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 0,
    "persisted": "agrees",
    "persisted_calling_convention": "thiscall"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0012"
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
        "obs-0004",
        "obs-0005",
        "obs-0009"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          224
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0004",
        "obs-0005",
        "obs-0009",
        "obs-0012"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0012"
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
        "obs-0012"
      ],
      "claim": "the return value is carried in ST0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "ST0"
    }
  ],
  "observations": [
    {
      "at": "0x00c31890",
      "count": 2,
      "first_use": 0,
      "first_write_index": 0,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "XORPS XMM0,XMM0",
      "reg": "XMM0"
    },
    {
      "at": "0x00c31890",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "XORPS XMM0,XMM0",
      "reg": "XMM0",
      "write_kind": "unknown"
    },
    {
      "at": "0x00c31893",
      "count": 4,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00c31894",
      "count": 1,
      "first_use": 2,
      "first_write_index": 8,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00c31894",
      "definite": true,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00c3189f",
      "id": "obs-0006",
      "index": 5,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00c317a0",
      "target": "0x00c317a0"
    },
    {
      "at": "0x00c318a4",
      "count": 2,
      "first_use": 6,
      "first_write_index": null,
      "id": "obs-0007",
      "index": 6,
      "kind": "REG_READ",
      "raw": "PUSH EAX",
      "reg": "EAX"
    },
    {
      "at": "0x00c318a5",
      "id": "obs-0008",
      "index": 7,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x01029940",
      "target": "0x01029940"
    },
    {
      "at": "0x00c318aa",
      "definite": true,
      "id": "obs-0009",
      "index": 8,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,EAX",
      "reg": "ECX",
      "write_kind": "reg"
    },
    {
      "at": "0x00c318ac",
      "id": "obs-0010",
      "index": 9,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x01029cc0",
      "target": "0x01029cc0"
    },
    {
      "at": "0x00c318bd",
      "id": "obs-0011",
      "index": 12,
      "kind": "REG_RESTORE",
      "raw": "POP ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00c318be",
      "form": "RET",
      "id": "obs-0012",
      "imm": null,
      "index": 13,
      "kind": "RET",
      "raw": "RET"
    }
  ],
  "parse": {
    "declared_count": 14,
    "degraded": false,
    "esp_unresolved": false,
    "flow_complete": false,
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
    "confidence": "INFERRED",
    "distinct_offsets": 1,
    "max_offset": 224,
    "offsets": [
      224
    ],
    "present": true,
    "register": "ECX",
 
[TRUNCATED]
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
    "va": "0x00c5c860"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c774b0"
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
  "count": 14,
  "instructions": [
    {
      "address": "00c31890",
      "instruction": "XORPS XMM0,XMM0"
    },
    {
      "address": "00c31893",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00c31894",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00c31896",
      "instruction": "COMISS XMM0,dword ptr [ESI + 0xe0]"
    },
    {
      "address": "00c3189d",
      "instruction": "JC 0x00c318b7"
    },
    {
      "address": "00c3189f",
      "instruction": "CALL 0x00c317a0"
    },
    {
      "address": "00c318a4",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00c318a5",
      "instruction": "CALL 0x01029940"
    },
    {
      "address": "00c318aa",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00c318ac",
      "instruction": "CALL 0x01029cc0"
    },
    {
      "address": "00c318b1",
      "instruction": "FSTP float ptr [ESI + 0xe0]"
    },
    {
      "address": "00c318b7",
      "instruction": "FLD float ptr [ESI + 0xe0]"
    },
    {
      "address": "00c318bd",
      "instruction": "POP ESI"
    },
    {
      "address": "00c318be",
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
  "original_bytes": 6948,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"thiscall\",\n    \"hidden_this_register\": \"ECX\",\n    \"hidden_this_type\": \"OpaqueEmpireMetricState*\",\n    \"return_type\": \"float\",\n    \"return_width_bytes\": 4,\n    \"stack_arguments\": [],\n    \"stack_cleanup_bytes\": 0,\n    \"termination\": \"plain RET\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-13-E3-EMPIRE-STATE-WAVE2\",\n      \"score\": 10,\n      \"symbol\": \"ProfileSetter_00c33690\",\n      \"va\": \"0x00c33690\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-13-E3-EMPIRE-STATE-WAVE2\",\n      \"score\": 8,\n      \"symbol\": \"SpeciesProfileSelector_00c30cc0\",\n      \"va\": \"0x00c30cc0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-13-E3-EMPIRE-STATE-WAVE2\",\n      \"score\": 8,\n      \"symbol\": \"ArchetypeRelationshipsID_00c30e20\",\n      \"va\": \"0x00c30e20\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 2,\n      \"symbol\": \"EditorCreatureController_SetTargetPosition_0059b0f0\",\n      \"va\": \"0x0059b0f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 2,\n      \"symbol\": \"EditorCreatureController_Update_0059b4b0\",\n      \"va\": \"0x0059b4b0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 2,\n      \"symbol\": \"EditorAnimWorld_GetCreatureController_0059cac0\",\n      \"va\": \"0x0059cac0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 2,\n      \"symbol\": \"EditorAnimWorld_PlayAnimation_0059cb10\",\n      \"va\": \"0x0059cb10\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 2,\n      \"symbol\": \"EditorAnimWorld_SetTargetAngle_0059cea0\",\n      \"va\": \"0x0059cea0\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Reviewed static mechanics and ABI are canonical; runtime values, ownership, concrete types, and opaque port behavior remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueEmpireMetricState\",\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c5c860\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c774b0\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00c5c94d\",\n        \"direction\": \"in\",\n        \"other\": \"0x00c5c860\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c77537\",\n        \"direction\": \"in\",\n        \"other\": \"0x00c774b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c3189f\",\n        \"direction\": \"out\",\n        \"other\": \"0x00c317a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c318a5\",\n        \"direction\": \"out\",\n        \"other\": \"0x01029940\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c318ac\",\n        \"direction\": \"out\",\n        \"other\": \"0x01029cc0\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 2,\n    \"fan_out\": 0,\n    \"manifest_callees\": [\n      \"0x00c317a0\",\n      \"0x01029940\",\n      \"0x01029cc0\"\n    ],\n    \"manifest_callers\": [\n      \"0x00c5c860\",\n      \"0x00c774b0\"\n    ],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0453\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"SUPPORTED\",\n  \"globals\": [],\n  \"integration_status\": \"integrated\",\n  \"name\": \"HomeWorldMetricLazy_00c31890\",\n  \"normalized_symbol\": \"HomeWorldMetricLazy_00c31890\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"do_not_claim\",\n    \"handoff_packages\": [\n      \"PKG-13-E3-EMPIRE-STATE-WAVE2\"\n    ],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": \"PKG-13-E3-EMPIRE-STATE-WAVE2\",\n    \"queue_state\": null\n  },\n  \"package\": \"PKG-13-E3-EMPIRE-STATE-WAVE2\",\n  \"reconstructed\": true,\n  \"review_status\": \"approved\",\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"gate-home-world-metric-00c31890\",\n      \"runtime validation not run\"\n    ],\n    \"validated\": 0\n  },\n  \"runtime_gated\": true,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": \"static_reconstruction_metadata_exact_runtime_unresolved\",\n  \"services\": [],\n  \"source\": {\n    \"decomp\": null,\n    \"file\": \"src/reconstruction/pkg13_e3_empire_state_wave2/empire_state_wave2.cpp\",\n    \"files\": [\n      \"reconstruction/staging/pkg13-e3-empire-state-wave2/empire_state_boundary.S\",\n      \"reconstruction/staging/pkg13-e3-empire-state-wave2/empire_state_boundary_test.sh\",\n      \"reconstruction/staging/pkg13-e3-empire-state-wave2/empire_
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
  "body_end": "00c318be",
  "body_span_bytes": 47,
  "body_start": "00c31890",
  "callees": [
    "FUN_00c317a0",
    "FUN_01029940",
    "FUN_01029cc0"
  ],
  "callers": [
    "FUN_00c774b0",
    "FUN_00c5c860"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00c31890",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "cEmpire_RequireHomePlanet",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x831890",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined cEmpire_RequireHomePlanet(void)",
  "size_bytes": 47,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00c31890",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 2,
  "xrefs": [
    {
      "from": "00c5c94d"
    },
    {
      "from": "00c77537"
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
  "file": "src/reconstruction/pkg13_e3_empire_state_wave2/empire_state_wave2.cpp",
  "files": [
    "reconstruction/staging/pkg13-e3-empire-state-wave2/empire_state_boundary.S",
    "reconstruction/staging/pkg13-e3-empire-state-wave2/empire_state_boundary_test.sh",
    "reconstruction/staging/pkg13-e3-empire-state-wave2/empire_state_wave2.cpp",
    "reconstruction/staging/pkg13-e3-empire-state-wave2/empire_state_wave2.hpp",
    "reconstruction/staging/pkg13-e3-empire-state-wave2/empire_state_wave2_model_test.cpp",
    "src/reconstruction/pkg13_e3_empire_state_wave2/empire_state_boundary.S",
    "src/reconstruction/pkg13_e3_empire_state_wave2/empire_state_boundary_test.sh",
    "src/reconstruction/pkg13_e3_empire_state_wave2/empire_state_wave2.cpp",
    "src/reconstruction/pkg13_e3_empire_state_wave2/empire_state_wave2.hpp",
    "src/reconstruction/pkg13_e3_empire_state_wave2/empire_state_wave2_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-sim-social-world-wave2/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg13-e3-empire-state-wave2/00c31890.json"
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
    "gate-home-world-metric-00c31890",
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
  "OpaqueEmpireMetricState",
  "OpaqueEmpireMetricState*",
  "float"
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
