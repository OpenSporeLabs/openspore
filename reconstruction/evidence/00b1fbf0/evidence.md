# Evidence 0x00b1fbf0

- Evidence state: `PERSISTED`
- Live requested: `False`
- Content SHA-256: `78f01b2af698ca5c3c324c6b26960b2b29ce9eff248df6083e013f9520a2609b`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": null,
  "hidden_receiver": "unread",
  "hidden_this_register": "ECX is never read; 0x00b1fbf0 has no instruction that mentions any register other than AL",
  "ordinary_stack_argument_slots": 0,
  "receiver": false,
  "ret_form": "RET",
  "return_observation": "0x00b1fbf0: MOV AL,0x1 writes only the low byte of EAX, so bits 8..31 of EAX are undefined on exit rather than zero. Every consumer inspected tests the AL byte, never the full dword.",
  "return_register": "EAX",
  "return_semantics": "std::uint8_t",
  "return_type": "std::uint8_t",
  "return_width_bytes": 1,
  "saved_registers": [],
  "stack_arguments": [],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "RET"
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
    "va": "0x007f53d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0082c210"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0096a670"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0096b3a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0097c6d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0098cc70"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0098f3d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00993fa0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00a43050"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00a51f40"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ccefb0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d73ca0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e0eab0"
  },
  {
    "name": "cell_mode_strategy_on_mouse_wheel_00e7d660",
    "reconstructed": true,
    "va": "0x00e7d660"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e81120"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ee8860"
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
  "original_bytes": 20490,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": null,\n    \"hidden_receiver\": \"unread\",\n    \"hidden_this_register\": \"ECX is never read; 0x00b1fbf0 has no instruction that mentions any register other than AL\",\n    \"ordinary_stack_argument_slots\": 0,\n    \"receiver\": false,\n    \"ret_form\": \"RET\",\n    \"return_observation\": \"0x00b1fbf0: MOV AL,0x1 writes only the low byte of EAX, so bits 8..31 of EAX are undefined on exit rather than zero. Every consumer inspected tests the AL byte, never the full dword.\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"std::uint8_t\",\n    \"return_type\": \"std::uint8_t\",\n    \"return_width_bytes\": 1,\n    \"saved_registers\": [],\n    \"stack_arguments\": [],\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"RET\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01485550\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE8\",\n      \"score\": 7,\n      \"symbol\": \"cell_mode_strategy_on_mouse_wheel_00e7d660\",\n      \"va\": \"0x00e7d660\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013fc06c,vtable:0x01409bec\"\n      ],\n      \"package\": \"PKG-WAVE6-CONTAINERS-MEMORY\",\n      \"score\": 4,\n      \"symbol\": \"wave6_reference_00432a50\",\n      \"va\": \"0x00432a50\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013f57f8\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"editor_input_005737d0\",\n      \"va\": \"0x005737d0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x014186c4\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"re_00575ea0\",\n      \"va\": \"0x00575ea0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013f57f8\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"editor_input_00585890\",\n      \"va\": \"0x00585890\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013f57f8\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"editor_input_00585d10\",\n      \"va\": \"0x00585d10\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013f57f8\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"editor_input_00588570\",\n      \"va\": \"0x00588570\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013f57f8\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"editor_input_0058ac10\",\n      \"va\": \"0x0058ac10\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"editor-core\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007f53d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0082c210\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0096a670\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0096b3a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0097c6d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0098cc70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0098f3d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00993fa0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00a43050\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00a51f40\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ccefb0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d73ca0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e0eab0\"\n      },\n      {\n        \"name\": \"cell_mode_strategy_on_mouse_wheel_00e7d660\",\n        \"reconstructed\": true,\n        \"va\": \"0x00e7d660\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e81120\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ee8860\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x007f53fe\",\n        \"direction\": \"in\",\n        \"other\": \"0x007f53d0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0082c27a\",\n        \"direction\": \"in\",\n        \"other\": \"0x0082c210\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0096a673\",\n        \"direction\": \"in\",\n        \"other\": \"0x0096a670\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0096b3a3\",\n        \"direction\": \"in\",\n        \"other\": \"0x0096b3a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0097c6d3\",\n        \"direction\": \"in\",\n        \"other\": \"0x0097
[TRUNCATED]
```

## ghidra_function

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: ``

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
  "files": [
    "reconstruction/staging/pkg-shared-default-true-wave12/b1fbf0_default_true.cpp",
    "reconstruction/staging/pkg-shared-default-true-wave12/b1fbf0_default_true.hpp",
    "reconstruction/staging/pkg-shared-default-true-wave12/b1fbf0_default_true_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-shared-default-true-wave12/00b1fbf0.json"
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
    "No original-process trace has been captured for 0x00b1fbf0, so every claim here is static. A runtime differential test must confirm that the answer is still 1 in the shipping build and that no runtime patch retargets the address.",
    "The 0x00ee8860 virtual dispatch site must be observed with a concrete receiver before the slot's owning class can be named."
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
  "status": "candidate"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "std::uint8_t"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x013f57f8",
  "vtable:0x013f625c",
  "vtable:0x013f85a4",
  "vtable:0x013fc06c",
  "vtable:0x013fc1a4",
  "vtable:0x013fc474",
  "vtable:0x013fc6cc",
  "vtable:0x013fc6f4",
  "vtable:0x013fc744",
  "vtable:0x013fc854",
  "vtable:0x013fcc08",
  "vtable:0x013fcc48",
  "vtable:0x013fec40",
  "vtable:0x013fec78",
  "vtable:0x013fedb4",
  "vtable:0x013ff064"
]
```

## Conflicts

```json
[]
```
