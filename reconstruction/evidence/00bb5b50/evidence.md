# Evidence 0x00bb5b50

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `987cef83092a2d38e8d1fa72714152d473ae949ea1e93e7bb1f6dd3aafb6b359`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "thiscall",
  "hidden_this_register": "ECX",
  "hidden_this_type": "OpaqueStarManager*",
  "receiver": "ECX",
  "return_register": "EAX",
  "return_type": "OpaqueRecordToPlanetOutput*",
  "stack_arguments": [
    "output",
    "pending_record"
  ],
  "stack_cleanup_bytes": 4,
  "termination": "RET 0x4"
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
    "calling_convention": "__stdcall",
    "ordinary_stack_argument_slots": [
      "entry_ESP+0x4"
    ],
    "ordinary_stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "receiver": false,
    "ret_form": "RET 0x4",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
    "stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "stack_cleanup_bytes": 4,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x4"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +8, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 4,
    "confidence": "SUPPORTED",
    "corroboration": "not_available",
    "evidence": "ret 0x4",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [
    {
      "field": "calling_convention",
      "inferred": "__stdcall",
      "kind": "inferred_vs_persisted",
      "persisted": "__thiscall",
      "resolution_status": "unresolved"
    }
  ],
  "content_sha256": "d62c23b3525e98b882a2378a145b35f045d36ab7a8ce60351482f908f9532268",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__stdcall",
    "candidate_conventions": [
      "__stdcall"
    ],
    "confidence": "INFERRED",
    "corroboration": "not_available"
  },
  "cross_validation": {
    "agreement": false,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 3,
    "persisted": "disagrees",
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
        "obs-0011"
      ],
      "claim": "the callee pops 4 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 4,
        "side": "callee"
      }
    },
    {
      "based_on": [
        "obs-0002"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 1,
        "total_bytes": 4
      }
    },
    {
      "based_on": [
        "obs-0011"
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
        "obs-0011"
      ],
      "claim": "calling convention is __stdcall: a callee that pops stack arguments with no register receiver",
      "confidence": "INFERRED",
      "id": "C6",
      "value": "__stdcall"
    },
    {
      "based_on": [
        "obs-0011"
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
        "obs-0011"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0011"
      ],
      "claim": "the last value written to EAX classifies as aggregate_unknown",
      "confidence": "INFERRED",
      "id": "RT2",
      "value": {
        "register_class": "aggregate_unknown"
      }
    }
  ],
  "observations": [
    {
      "at": "0x00bb5b50",
      "count": 2,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "ESP"
    },
    {
      "at": "0x00bb5b50",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0002",
      "index": 0,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00bb5b50",
      "definite": true,
      "id": "obs-0003",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "and_esp": null,
      "at": "0x00bb5b54",
      "ebp_is_general_register": false,
      "fp": false,
      "id": "obs-0004",
      "index": 1,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": false,
      "push_ebp_at": null,
      "raw": "SUB ESP,0x8",
      "sub": 8
    },
    {
      "at": "0x00bb5b54",
      "definite": true,
      "id": "obs-0005",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x8",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00bb5b57",
      "count": 1,
      "first_use": 2,
      "first_write_index": 0,
      "id": "obs-0006",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH EAX",
      "reg": "EAX"
    },
    {
      "at": "0x00bb5b58",
      "count": 2,
      "first_use": 3,
      "first_write_index": null,
      "id": "obs-0007",
      "index": 3,
      "kind": "REG_READ",
      "raw": "LEA EDX,[ESP + 0x4]",
      "reg": "EDX"
    },
    {
      "at": "0x00bb5b58",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0008",
      "index": 3,
      "key": null,
      "kind": "STACK_SLOT_READ",
      "raw": "LEA EDX,[ESP + 0x4]",
      "reason": "local",
      "resolved": false,
      "size": 4
    },
    {
      "at": "0x00bb5b5d",
      "definite": true,
      "id": "obs-0009",
      "index": 5,
      "kind": "REG_WRITE",
      "raw": "ADD ECX,0x16c",
      "reg": "ECX",
      "write_kind": "arith
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
    "va": "0x00bba2a0"
  },
  {
    "name": "ProfileSetter_00c33690",
    "reconstructed": true,
    "va": "0x00c33690"
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
      "0x00bb42a0",
      "0x00bb4c90",
      "0x00c932f0",
      "0x00c983c0",
      "0x00bb5b50",
      "0x00bba900",
      "0x00c983c0",
      "0x00c932f0"
    ],
    "conflict_id": "U-005-tribe-population",
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
      "0x00e7fd00",
      "0x00e74a20",
      "0x00bb42a0",
      "0x00bb4c90",
      "0x00b237c0",
      "0x00e74a20",
      "0x00e74a20",
      "0x00e4ce20",
      "0x00e5b790",
      "0x00e665c0",
      "0x00e666f0",
      "0x00e80ba0",
      "0x00be34a0",
      "0x00bddef0",
      "0x00bdde70",
      "0x00bb5b50"
    ],
    "conflict_id": "U-009-runtime-validation",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "A positive hash-pinned original-process trace is required; static naming or conceptual state names are not promoted to runtime behavior.",
    "resolution_status": "A positive hash-pinned original-process trace is required; static naming or conceptual state names are not promoted to runtime behavior.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "No positive original-process trace reaches this transition in the committed corpus."
  },
  {
    "anchors": [
      "0x01001360",
      "0x01021960",
      "0x01021960",
      "0x01001360",
      "0x01021960",
      "0x01021960",
      "0x01001360",
      "0x01021960",
      "0x01001360",
      "0x01001360",
      "0x01021960",
      "0x00bb5b50",
      "0x00c86390",
      "0x01001360"
    ],
    "conflict_id": "galaxy_followup_effects",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
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
  "count": 9,
  "instructions": [
    {
      "address": "00bb5b50",
      "instruction": "MOV EAX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "00bb5b54",
      "instruction": "SUB ESP,0x8"
    },
    {
      "address": "00bb5b57",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00bb5b58",
      "instruction": "LEA EDX,[ESP + 0x4]"
    },
    {
      "address": "00bb5b5c",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00bb5b5d",
      "instruction": "ADD ECX,0x16c"
    },
    {
      "address": "00bb5b63",
      "instruction": "CALL 0x00bb1560"
    },
    {
      "address": "00bb5b68",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "00bb5b6b",
      "instruction": "RET 0x4"
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
  "original_bytes": 7022,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"thiscall\",\n    \"hidden_this_register\": \"ECX\",\n    \"hidden_this_type\": \"OpaqueStarManager*\",\n    \"receiver\": \"ECX\",\n    \"return_register\": \"EAX\",\n    \"return_type\": \"OpaqueRecordToPlanetOutput*\",\n    \"stack_arguments\": [\n      \"output\",\n      \"pending_record\"\n    ],\n    \"stack_cleanup_bytes\": 4,\n    \"termination\": \"RET 0x4\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_class\",\n        \"shared_types:OpaqueStarManager,OpaqueStarManager*\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-14-A2-WORLD-LIFECYCLE-WAVE2\",\n      \"score\": 21,\n      \"symbol\": \"star_regenerate_00bb4af0\",\n      \"va\": \"0x00bb4af0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:OpaqueStarManager,OpaqueStarManager*\"\n      ],\n      \"package\": \"PKG-11-SIM-CORE\",\n      \"score\": 11,\n      \"symbol\": \"Simulator_LookupEmpireByPoliticalId\",\n      \"va\": \"0x00ba9370\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-14-A2-WORLD-LIFECYCLE-WAVE2\",\n      \"score\": 10,\n      \"symbol\": \"planet_record_copy_three_word_key_00b8da30\",\n      \"va\": \"0x00b8da30\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:OpaqueStarManager\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 8,\n      \"symbol\": \"FUN_00b3d2a0\",\n      \"va\": \"0x00b3d2a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-13-E3-EMPIRE-STATE-WAVE2\",\n      \"score\": 5,\n      \"symbol\": \"ProfileSetter_00c33690\",\n      \"va\": \"0x00c33690\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 2,\n      \"symbol\": \"EditorCreatureController_SetTargetPosition_0059b0f0\",\n      \"va\": \"0x0059b0f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 2,\n      \"symbol\": \"EditorCreatureController_Update_0059b4b0\",\n      \"va\": \"0x0059b4b0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 2,\n      \"symbol\": \"EditorAnimWorld_GetCreatureController_0059cac0\",\n      \"va\": \"0x0059cac0\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Reviewed static mechanics and ABI are canonical; runtime values, ownership, concrete types, and opaque port behavior remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [\n    \"The direct cache helper's opaque entry type and insertion allocator remain outside this worker boundary.\"\n  ],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueStarManager\",\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bba2a0\"\n      },\n      {\n        \"name\": \"ProfileSetter_00c33690\",\n        \"reconstructed\": true,\n        \"va\": \"0x00c33690\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00bba3be\",\n        \"direction\": \"in\",\n        \"other\": \"0x00bba2a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c336d9\",\n        \"direction\": \"in\",\n        \"other\": \"0x00c33690\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00bb5b63\",\n        \"direction\": \"out\",\n        \"other\": \"0x00bb1560\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 2,\n    \"fan_out\": 0,\n    \"manifest_callees\": [\n      \"0x00bb1560\"\n    ],\n    \"manifest_callers\": [\n      \"0x00c33690\",\n      \"0x00bba2a0 cStarRecord__ctor\"\n    ],\n    \"nearby_reconstructed\": [\n      \"0x00c33690\"\n    ],\n    \"scc\": {\n      \"id\": \"scc-0420\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"SUPPORTED\",\n  \"globals\": [],\n  \"integration_status\": \"integrated\",\n  \"name\": \"star_manager_record_to_planet_00bb5b50\",\n  \"normalized_symbol\": \"star_manager_record_to_planet_00bb5b50\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"do_not_claim\",\n    \"handoff_packages\": [\n      \"PKG-14-A2-WORLD-LIFECYCLE-WAVE2\"\n    ],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": \"PKG-14-A2-WORLD-LIFECYCLE-WAVE2\",\n    \"queue_state\": null\n  },\n  \"package\": \"PKG-14-A2-WORLD-LIFECYCLE-WAVE2\",\n  \"reconstructed\": true,\n  \"review_status\": \"approved\",\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"gate-star-record-cache-00bb5b50\",\n      \"runtime validation not run\"\n    ],\n    \"validated\": 0\n  },\n  \"runtime_gated\": true,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": \"static_reconstruction_metadata_exact_runtime_unresolved\",\n  \"services\": [],\n  \"source\": {\n    \"decomp\": null,\n    \"file\": \"src/reconstruction/pkg14_a2_world_lifecycle_wave2/world_lifecycle.cpp\",\n    \"files\": [\n      \"reconstruction/staging/pkg14-a2-world-lifecycle-wave2/world_lifecycle.cpp\",\n      \"reconstruc
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
  "body_end": "00bb5b6d",
  "body_span_bytes": 30,
  "body_start": "00bb5b50",
  "callees": [
    "FUN_00bb1560"
  ],
  "callers": [
    "FUN_00c33690",
    "cStarRecord__ctor"
  ],
  "classification": "wrapper",
  "dispatch": null,
  "entry_point": "00bb5b50",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_8",
      "storage": "Stack[-0x8]:1",
      "type": "undefined"
    }
  ],
  "locals_count": 1,
  "mode": "live",
  "name": "Simulator::cStarManager::RecordToPlanet",
  "namespace": "Simulator",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 3,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "cStarManager *"
    },
    {
      "name": "record",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "cPlanetRecord *"
    },
    {
      "name": "dst",
      "ordinal": 2,
      "storage": "Stack[0xc]:4",
      "type": "intrusive_ptr<Simulator::cPlanet> *"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "void",
  "return_type_resolved": true,
  "rva": "0x7b5b50",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "void Simulator::cStarManager::RecordToPlanet(cStarManager * this, cPlanetRecord * record, intrusive_ptr<Simulator::cPlanet> * dst)",
  "size_bytes": 30,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00bb5b50",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 2,
  "xrefs": [
    {
      "from": "00bba3be"
    },
    {
      "from": "00c336d9"
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
  "file": "src/reconstruction/pkg14_a2_world_lifecycle_wave2/world_lifecycle.cpp",
  "files": [
    "reconstruction/staging/pkg14-a2-world-lifecycle-wave2/world_lifecycle.cpp",
    "reconstruction/staging/pkg14-a2-world-lifecycle-wave2/world_lifecycle.hpp",
    "reconstruction/staging/pkg14-a2-world-lifecycle-wave2/world_lifecycle_model_test.cpp",
    "src/reconstruction/pkg14_a2_world_lifecycle_wave2/world_lifecycle.cpp",
    "src/reconstruction/pkg14_a2_world_lifecycle_wave2/world_lifecycle.hpp",
    "src/reconstruction/pkg14_a2_world_lifecycle_wave2/world_lifecycle_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-sim-social-world-wave2/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg14-a2-world-lifecycle-wave2/00bb5b50.json"
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
    "gate-star-record-cache-00bb5b50",
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
  "OpaqueRecordCache*",
  "OpaqueRecordToPlanetOutput*",
  "OpaqueStarManager",
  "OpaqueStarManager*",
  "OpaqueUninitializedRecordSlot"
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
      "0x00bb42a0",
      "0x00bb4c90",
      "0x00c932f0",
      "0x00c983c0",
      "0x00bb5b50",
      "0x00bba900",
      "0x00c983c0",
      "0x00c932f0"
    ],
    "conflict_id": "U-005-tribe-population",
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
      "0x00e7fd00",
      "0x00e74a20",
      "0x00bb42a0",
      "0x00bb4c90",
      "0x00b237c0",
      "0x00e74a20",
      "0x00e74a20",
      "0x00e4ce20",
      "0x00e5b790",
      "0x00e665c0",
      "0x00e666f0",
      "0x00e80ba0",
      "0x00be34a0",
      "0x00bddef0",
      "0x00bdde70",
      "0x00bb5b50"
    ],
    "conflict_id": "U-009-runtime-validation",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "A positive hash-pinned original-process trace is required; static naming or conceptual state names are not promoted to runtime behavior.",
    "resolution_status": "A positive hash-pinned original-process trace is required; static naming or conceptual state names are not promoted to runtime behavior.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "No positive original-process trace reaches this transition in the committed corpus."
  },
  {
    "anchors": [
      "0x01001360",
      "0x01021960",
      "0x01021960",
      "0x01001360",
      "0x01021960",
      "0x01021960",
      "0x01001360",
      "0x01021960",
      "0x01001360",
      "0x01001360",
      "0x01021960",
      "0x00bb5b50",
      "0x00c86390",
      "0x01001360"
    ],
    "conflict_id": "galaxy_followup_effects",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "derived": "__stdcall",
    "field": "calling_convention",
    "kind": "derived_vs_persisted",
    "persisted": "thiscall",
    "resolution_status": "unresolved"
  }
]
```
