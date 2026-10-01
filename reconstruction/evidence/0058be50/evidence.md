# Evidence 0x0058be50

- Evidence state: `PERSISTED`
- Live requested: `False`
- Content SHA-256: `0c05259336d481db5c21aacdd57e4f529945d8a0055d2b9c05a35d470c618e7a`

## abi

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## abi_derived

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: ``

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "FUN_0044ae00",
    "reconstructed": false,
    "va": "0x0044ae00"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0045b150"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0045b210"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x004c49e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0059d110"
  },
  {
    "name": "editor_row_publish_005a2010",
    "reconstructed": true,
    "va": "0x005a2010"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005dc310"
  },
  {
    "name": "anim_manager_get_0067cae0",
    "reconstructed": true,
    "va": "0x0067cae0"
  },
  {
    "name": "app_direct_property_list_get_direct_bool_006a25a0",
    "reconstructed": true,
    "va": "0x006a25a0"
  },
  {
    "name": "sporepedia_nop_slot_FUN_00c2e4e0",
    "reconstructed": true,
    "va": "0x00c2e4e0"
  },
  {
    "name": "map_int_whatever_find",
    "reconstructed": true,
    "va": "0x00e5c780"
  }
]
```

## callers_dependencies

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## contradictions

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "anchors": [
      "0x007d85b0",
      "0x007d8c80",
      "0x007d8cf0",
      "0x007d8d40",
      "0x01412598",
      "0x01412598",
      "0x007d8c80",
      "0x007d8c80",
      "0x007d85b0",
      "0x0212d3e7",
      "0x022d1adc",
      "0x00582fe0",
      "0x00582fe0",
      "0x00587270",
      "0x00587270",
      "0x0058be50"
    ],
    "conflict_id": "game_mode_transition_branches",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The cited producer, consumer, or registration surface is retained, but the complete event-to-message mapping, timing, and payload contract remain unresolved.",
    "resolution_status": "The cited producer, consumer, or registration surface is retained, but the complete event-to-message mapping, timing, and payload contract remain unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00574080",
      "0x00586410",
      "0x0058ac10",
      "0x0058ac10",
      "0x004af260",
      "0x00574080",
      "0x00576c50",
      "0x00576c50",
      "0x0057ce80",
      "0x0057ce80",
      "0x00584300",
      "0x00584300",
      "0x00586410",
      "0x00587a20",
      "0x00587a20",
      "0x0058be50"
    ],
    "conflict_id": "history_budget_semantics",
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
  "original_bytes": 10392,
  "preview": "{\n  \"abi\": {},\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x013f57f8\"\n      ],\n      \"package\": \"pkg-editor-w1-0057d6f0\",\n      \"score\": 10,\n      \"symbol\": \"re_0057d6f0\",\n      \"va\": \"0x0057d6f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x013f57f8\"\n      ],\n      \"package\": \"pkg-swarm-w2-00586700\",\n      \"score\": 10,\n      \"symbol\": \"re_00586700\",\n      \"va\": \"0x00586700\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x013f57f8\"\n      ],\n      \"package\": \"pkg-swarm-w1-005b2490\",\n      \"score\": 10,\n      \"symbol\": \"re_005b2490\",\n      \"va\": \"0x005b2490\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x013f57f8\"\n      ],\n      \"package\": \"pkg-swarm-w1-005ba0d0\",\n      \"score\": 10,\n      \"symbol\": \"re_005ba0d0\",\n      \"va\": \"0x005ba0d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x013f57f8\"\n      ],\n      \"package\": \"pkg-editor-child-007f30d0\",\n      \"score\": 10,\n      \"symbol\": \"FUN_007f30d0\",\n      \"va\": \"0x007f30d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x013f57f8\"\n      ],\n      \"package\": \"pkg-shared-default-true-wave12\",\n      \"score\": 10,\n      \"symbol\": \"pkg_shared_default_true_00b1fbf0\",\n      \"va\": \"0x00b1fbf0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x013f57f8\"\n      ],\n      \"package\": \"pkg-w2-00e5cac0\",\n      \"score\": 10,\n      \"symbol\": \"FUN_00e5cac0\",\n      \"va\": \"0x00e5cac0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"pkg-vft-preinc-0051e340\",\n      \"score\": 6,\n      \"symbol\": \"vft_preinc_0051e340\",\n      \"va\": \"0x0051e340\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"editor-core\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"FUN_0044ae00\",\n        \"reconstructed\": false,\n        \"va\": \"0x0044ae00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0045b150\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0045b210\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004c49e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0059d110\"\n      },\n      {\n        \"name\": \"editor_row_publish_005a2010\",\n        \"reconstructed\": true,\n        \"va\": \"0x005a2010\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005dc310\"\n      },\n      {\n        \"name\": \"anim_manager_get_0067cae0\",\n        \"reconstructed\": true,\n        \"va\": \"0x0067cae0\"\n      },\n      {\n        \"name\": \"app_direct_property_list_get_direct_bool_006a25a0\",\n        \"reconstructed\": true,\n        \"va\": \"0x006a25a0\"\n      },\n      {\n        \"name\": \"sporepedia_nop_slot_FUN_00c2e4e0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00c2e4e0\"\n      },\n      {\n        \"name\": \"map_int_whatever_find\",\n        \"reconstructed\": true,\n        \"va\": \"0x00e5c780\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x0058bf3e\",\n        \"direction\": \"out\",\n        \"other\": \"0x00401050\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0058bf6b\",\n        \"direction\": \"out\",\n        \"other\": \"0x00401050\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0058c3d3\",\n        \"direction\": \"out\",\n        \"other\": \"0x00401050\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0058c3e8\",\n        \"direction\": \"out\",\n        \"other\": \"0x00401050\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0058c404\",\n        \"direction\": \"out\",\n        \"other\": \"0x00401050\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0058cb24\",\n        \"direction\": \"out\",\n        \"other\": \"0x00401060\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0058bed4\",\n        \"direction\": \"out\",\n        \"other\": \"0x00410370\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0058c464\",\n        \"direction\": \"out\",\n        \"other\": \"0x0041cb40\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0058c9b2\",\n        \"direction\": \"out\",\n        \"other\": \"0x004333c0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0058ca2e\",\n        \"direction\": \"out\",\n        \"other\": \"0x00435f40\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0058ca4d\",\n        \"direction\": \"out\",\n        \"other\": \"0x00435f40\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0058cb17\",\n        \"direction\": \"out\",\n        \"other\": \"0x00435f40\",\n        \
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditor__Update.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditor__Update.c"
  ],
  "handoffs": [],
  "metadata": []
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
  "status": "queued"
}
```

## types

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x013f57f8"
]
```

## Conflicts

```json
[
  {
    "anchors": [
      "0x007d85b0",
      "0x007d8c80",
      "0x007d8cf0",
      "0x007d8d40",
      "0x01412598",
      "0x01412598",
      "0x007d8c80",
      "0x007d8c80",
      "0x007d85b0",
      "0x0212d3e7",
      "0x022d1adc",
      "0x00582fe0",
      "0x00582fe0",
      "0x00587270",
      "0x00587270",
      "0x0058be50"
    ],
    "conflict_id": "game_mode_transition_branches",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The cited producer, consumer, or registration surface is retained, but the complete event-to-message mapping, timing, and payload contract remain unresolved.",
    "resolution_status": "The cited producer, consumer, or registration surface is retained, but the complete event-to-message mapping, timing, and payload contract remain unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00574080",
      "0x00586410",
      "0x0058ac10",
      "0x0058ac10",
      "0x004af260",
      "0x00574080",
      "0x00576c50",
      "0x00576c50",
      "0x0057ce80",
      "0x0057ce80",
      "0x00584300",
      "0x00584300",
      "0x00586410",
      "0x00587a20",
      "0x00587a20",
      "0x0058be50"
    ],
    "conflict_id": "history_budget_semantics",
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
