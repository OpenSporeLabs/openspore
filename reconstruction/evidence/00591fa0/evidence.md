# Evidence 0x00591fa0

- Evidence state: `PERSISTED`
- Live requested: `False`
- Content SHA-256: `61f0ce7b8657e232745364b7e3aa6c70ff46e5b1f11f098dc69e63008f6b919c`

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
    "va": "0x0045ae10"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x004a88d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x004c49e0"
  },
  {
    "name": "PaintPersistenceBoundary_submit_004c5200",
    "reconstructed": true,
    "va": "0x004c5200"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00573c00"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00587270"
  },
  {
    "name": "editor_anim_event_message_send_0059d8b0",
    "reconstructed": true,
    "va": "0x0059d8b0"
  },
  {
    "name": "cEditorAnimEvent__ctor",
    "reconstructed": false,
    "va": "0x0059d960"
  },
  {
    "name": "palette_select_category_005cb240",
    "reconstructed": true,
    "va": "0x005cb240"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005dc310"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005dd7a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0067dcc0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0067dcd0"
  },
  {
    "name": "app_direct_property_list_get_direct_bool_006a25a0",
    "reconstructed": true,
    "va": "0x006a25a0"
  },
  {
    "name": "camera_light_origin_helper_007c4900",
    "reconstructed": true,
    "va": "0x007c4900"
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
      "0x00591fa0",
      "0x00883a90",
      "0x00883ad0",
      "0x00883ad0",
      "0x00883a90",
      "0x00591fa0",
      "0x00573970",
      "0x00573970",
      "0x00586410",
      "0x00586410",
      "0x00587270",
      "0x00587270",
      "0x0059d840",
      "0x0059d840",
      "0x0059d8b0",
      "0x0059d8b0"
    ],
    "conflict_id": "Q-EDITOR-MESSAGE-CATALOG",
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
      "0x00591fa0",
      "0x005dec10",
      "0x00883a90",
      "0x00883ad0",
      "0x051cc0b8",
      "0xb2e18705",
      "0x00883ad0",
      "0x00883a90",
      "0x00591fa0",
      "0x004af260",
      "0x005dda30",
      "0x00591690",
      "0x051cc0b8",
      "0x00591fa0",
      "0x005dec10",
      "0xb2e18705"
    ],
    "conflict_id": "editor_message_names_and_payloads",
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
      "0x005cb240",
      "0x005cb2a0",
      "0x005cb5a0",
      "0x005cb5a0",
      "0x00591fa0",
      "0x00591fa0",
      "0x005cb240",
      "0x005cb240",
      "0x005cb240",
      "0x005cb2a0",
      "0x005cb5a0",
      "0x005cb5a0",
      "0x005cb2a0",
      "0x005cb240",
      "0x005cb240",
      "0x005cb2a0"
    ],
    "conflict_id": "palette_selected_paint",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
    "resolution_status": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
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
  "original_bytes": 10680,
  "preview": "{\n  \"abi\": {},\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"pkg-vft-preinc-0051e340\",\n      \"score\": 6,\n      \"symbol\": \"vft_preinc_0051e340\",\n      \"va\": \"0x0051e340\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"subobject-forward-0051e380\",\n      \"score\": 6,\n      \"symbol\": \"subobject_forward_0051e380\",\n      \"va\": \"0x0051e380\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"pkg-w2-0052e640\",\n      \"score\": 6,\n      \"symbol\": \"reconstruct_0052e640\",\n      \"va\": \"0x0052e640\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"pkg-w2-0052e650\",\n      \"score\": 6,\n      \"symbol\": \"reconstruct_0052e650\",\n      \"va\": \"0x0052e650\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"pkg-editor-w1-0057d6f0\",\n      \"score\": 6,\n      \"symbol\": \"re_0057d6f0\",\n      \"va\": \"0x0057d6f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"pkg-swarm-w2-00586700\",\n      \"score\": 6,\n      \"symbol\": \"re_00586700\",\n      \"va\": \"0x00586700\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"pkg-swarm-w1-005b2490\",\n      \"score\": 6,\n      \"symbol\": \"re_005b2490\",\n      \"va\": \"0x005b2490\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"pkg-swarm-w1-005ba0d0\",\n      \"score\": 6,\n      \"symbol\": \"re_005ba0d0\",\n      \"va\": \"0x005ba0d0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"editor-core\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"FUN_0044ae00\",\n        \"reconstructed\": false,\n        \"va\": \"0x0044ae00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0045ae10\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004a88d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004c49e0\"\n      },\n      {\n        \"name\": \"PaintPersistenceBoundary_submit_004c5200\",\n        \"reconstructed\": true,\n        \"va\": \"0x004c5200\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00573c00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00587270\"\n      },\n      {\n        \"name\": \"editor_anim_event_message_send_0059d8b0\",\n        \"reconstructed\": true,\n        \"va\": \"0x0059d8b0\"\n      },\n      {\n        \"name\": \"cEditorAnimEvent__ctor\",\n        \"reconstructed\": false,\n        \"va\": \"0x0059d960\"\n      },\n      {\n        \"name\": \"palette_select_category_005cb240\",\n        \"reconstructed\": true,\n        \"va\": \"0x005cb240\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005dc310\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005dd7a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0067dcc0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0067dcd0\"\n      },\n      {\n        \"name\": \"app_direct_property_list_get_direct_bool_006a25a0\",\n        \"reconstructed\": true,\n        \"va\": \"0x006a25a0\"\n      },\n      {\n        \"name\": \"camera_light_origin_helper_007c4900\",\n        \"reconstructed\": true,\n        \"va\": \"0x007c4900\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00592667\",\n        \"direction\": \"out\",\n        \"other\": \"0x00401030\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00592670\",\n        \"direction\": \"out\",\n        \"other\": \"0x00401030\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00592e89\",\n        \"direction\": \"out\",\n        \"other\": \"0x00401050\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005934ce\",\n        \"direction\": \"out\",\n        \"other\": \"0x00401050\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0059349a\",\n        \"direction\": \"out\",\n        \"other\": \"0x0040cf10\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00592116\",\n        \"direction\": \"out\",\n        \"other\": \"0x0041e050\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00592199\",\n        \"direction\": \"out\",\n        \"other\": \"0x0041e050\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00593762\",\n        \"direction\": \"out\",\n        \"other\": \"0x0041e050\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00592741\",\n        \"direction\": \"out\",\n        \"other\": \"0x00421eb0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0059283e\",\n        \"direction\": \"out\",\n        \"other\": \"0x00432f10\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n    
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditor__HandleMessage.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditor__HandleMessage.c"
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
  "vtable:0x013f57a4"
]
```

## Conflicts

```json
[
  {
    "anchors": [
      "0x00591fa0",
      "0x00883a90",
      "0x00883ad0",
      "0x00883ad0",
      "0x00883a90",
      "0x00591fa0",
      "0x00573970",
      "0x00573970",
      "0x00586410",
      "0x00586410",
      "0x00587270",
      "0x00587270",
      "0x0059d840",
      "0x0059d840",
      "0x0059d8b0",
      "0x0059d8b0"
    ],
    "conflict_id": "Q-EDITOR-MESSAGE-CATALOG",
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
      "0x00591fa0",
      "0x005dec10",
      "0x00883a90",
      "0x00883ad0",
      "0x051cc0b8",
      "0xb2e18705",
      "0x00883ad0",
      "0x00883a90",
      "0x00591fa0",
      "0x004af260",
      "0x005dda30",
      "0x00591690",
      "0x051cc0b8",
      "0x00591fa0",
      "0x005dec10",
      "0xb2e18705"
    ],
    "conflict_id": "editor_message_names_and_payloads",
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
      "0x005cb240",
      "0x005cb2a0",
      "0x005cb5a0",
      "0x005cb5a0",
      "0x00591fa0",
      "0x00591fa0",
      "0x005cb240",
      "0x005cb240",
      "0x005cb240",
      "0x005cb2a0",
      "0x005cb5a0",
      "0x005cb5a0",
      "0x005cb2a0",
      "0x005cb240",
      "0x005cb240",
      "0x005cb2a0"
    ],
    "conflict_id": "palette_selected_paint",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
    "resolution_status": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  }
]
```
