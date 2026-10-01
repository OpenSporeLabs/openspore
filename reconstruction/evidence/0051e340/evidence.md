# Evidence 0x0051e340

- Evidence state: `PERSISTED`
- Live requested: `False`
- Content SHA-256: `eff915c311abbc1cc79c5dcf03b5993fe777cbaf6e50a05e163b14952c365a6c`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_this": true,
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": 0,
  "ordinary_stack_arguments": [],
  "ret_form": "RET (bare, no immediate)",
  "return_register": "EAX",
  "return_semantics": "integral_in_EAX at 32-bit width; the engine's own classifier says pointer_like because the last EAX write is a load from memory, which is the conservative reading of the same fact",
  "return_type": "std::uint32_t",
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller"
}
```

## abi_derived

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: ``

## callees_dependencies

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## callers_dependencies

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## contradictions

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## decompilation

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: ``

## disassembly

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: ``

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
  "original_bytes": 7559,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": 0,\n    \"ordinary_stack_arguments\": [],\n    \"ret_form\": \"RET (bare, no immediate)\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"integral_in_EAX at 32-bit width; the engine's own classifier says pointer_like because the last EAX write is a load from memory, which is the conservative reading of the same fact\",\n    \"return_type\": \"std::uint32_t\",\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ef110,vtable:0x013f2194\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 6,\n      \"symbol\": \"Editors_EditorModel_SetColor_raw_004ae250\",\n      \"va\": \"0x004ae250\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013f1a30\"\n      ],\n      \"package\": \"PKG-SKINNER-SAFE-WAVE10\",\n      \"score\": 4,\n      \"symbol\": \"skin_painter_job_brush_pass_005182f0\",\n      \"va\": \"0x005182f0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x014582e0\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"re_00951220\",\n      \"va\": \"0x00951220\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01414614,vtable:0x01458024\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"re_00951230\",\n      \"va\": \"0x00951230\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"model_parts_apply_properties_00447150\",\n      \"va\": \"0x00447150\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"editor-core\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0047\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"INFERRED\",\n  \"globals\": [\n    \"global:PASS\"\n  ],\n  \"integration_status\": null,\n  \"name\": \"FUN_0051e340\",\n  \"normalized_symbol\": \"FUN_0051e340\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"queue_candidate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"candidate\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [],\n    \"validated\": 0\n  },\n  \"runtime_gated\": false,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": null,\n  \"services\": [],\n  \"source\": {\n    \"decomp\": null,\n    \"file\": null,\n    \"files\": [\n      \"reconstruction/staging/pkg-vft-preinc-0051e340/vft_preinc_0051e340.cpp\",\n      \"reconstruction/staging/pkg-vft-preinc-0051e340/vft_preinc_0051e340.hpp\",\n      \"reconstruction/staging/pkg-vft-preinc-0051e340/vft_preinc_0051e340_model_test.cpp\"\n    ],\n    \"handoffs\": [],\n    \"metadata\": [\n      \"reconstruction/metadata/pkg-vft-preinc-0051e340/0051e340.json\"\n    ],\n    \"provenance\": []\n  },\n  \"status\": \"candidate\",\n  \"subsystem\": \"Editor\",\n  \"triage\": {\n    \"category\": \"GAMEPLAY_LOGIC\",\n    \"cluster\": \"editor-core\",\n    \"db_triage_status\": \"candidate\",\n    \"decomp_path\": null,\n    \"dependencies\": [],\n    \"evidence\": \"INFERRED\",\n    \"kg_node_id\": \"fun:0051e340\",\n    \"name\": \"FUN_0051e340\",\n    \"priority\": \"P1\",\n    \"provenance\": {\n      \"classifier\": \"triage-v5\",\n      \"sdk_name\": null,\n      \"snapshot\": \"f0e310e0\",\n      \"snapshot_sha256\": \"f0e310e0c83fc960ed38d490ff6d2a78d53925969206b4c4db7a012ddbf8b54b\",\n      \"vtable_addrs\": [\n        \"013ef110\",\n        \"013ef1c0\",\n        \"013ef270\",\n        \"013ef320\",\n        \"013ef3c0\",\n        \"013ef6a4\",\n        \"013f031c\",\n        \"013f1a30\",\n        \"013f1c6c\",\n        \"013f2194\",\n        \"013f21d8\",\n        \"013f2698\"\n      ]\n    },\n    \"queue_state\": \"candidate\",\n    \"rank\": 260\n  },\n  \"types\": [\n    \"std::uint32_t\"\n  ],\n  \"unresolved_questions\": [\n    \"The class is unknown and unknowable from this evidence: 42 vptr-backed tables hold the body, which is ICF collapse, so 'virtual member of some c
[TRUNCATED]
```

## ghidra_function

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: ``

## globals

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "global:PASS"
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-vft-preinc-0051e340/vft_preinc_0051e340.cpp",
    "reconstruction/staging/pkg-vft-preinc-0051e340/vft_preinc_0051e340.hpp",
    "reconstruction/staging/pkg-vft-preinc-0051e340/vft_preinc_0051e340_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-vft-preinc-0051e340/0051e340.json"
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
  "status": "candidate"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "std::uint32_t"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x0051e380",
  "vtable:0x013ef110",
  "vtable:0x013ef1c0",
  "vtable:0x013ef270",
  "vtable:0x013ef320",
  "vtable:0x013ef3c0",
  "vtable:0x013ef6a4",
  "vtable:0x013f031c",
  "vtable:0x013f1a30",
  "vtable:0x013f1c6c",
  "vtable:0x013f2194",
  "vtable:0x013f21d8",
  "vtable:0x013f2698",
  "vtable:0x013f276c",
  "vtable:0x013f2d68",
  "vtable:0x013f6e78"
]
```

## Conflicts

```json
[]
```
