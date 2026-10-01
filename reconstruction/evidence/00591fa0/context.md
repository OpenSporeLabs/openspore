# Reconstruction context 0x00591fa0

- Status: `partial`
- Content SHA-256: `3a51e447eeefb9ebd600abe804c0ca3dba49eaf4c2b60190e8579ec7b40f5b77`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00591fa0",
  "phase": "reconstruction",
  "target": "0x00591fa0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "Editors::cEditor::HandleMessage",
  "package": null,
  "subsystem": "Editor",
  "va": "0x00591fa0"
}
```

## 03_current_status

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "blocked": false,
  "reconstructed": false,
  "runtime_gated": false,
  "runtime_validated": 0,
  "status": "queued"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "61f0ce7b8657e232745364b7e3aa6c70ff46e5b1f11f098dc69e63008f6b919c",
  "live_attempts": [],
  "live_requested": false,
  "overall": "PERSISTED"
}
```

## 05_decompilation

- State: `missing`
- Provenance: ``

## 06_abi

- State: `missing`
- Provenance: `reconstruction/knowledge/index.json`

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
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
      "reconstructed": tru
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [],
  "vtables": [
    "vtable:0x013f57a4"
  ]
}
```

## 09_state_event_relationships

- State: `missing`
- Provenance: `knowledgegraph/research/semantic-decomp.json, reconstruction/knowledge/index.json`

```json
{
  "runtime": {
    "blocking_reason": null,
    "gates": [],
    "validated": 0
  },
  "semantic": {}
}
```

## 10_dependencies

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
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
      "reconstructed": tru
[TRUNCATED]
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "pkg-vft-preinc-0051e340",
    "score": 6,
    "symbol": "vft_preinc_0051e340",
    "va": "0x0051e340"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "subobject-forward-0051e380",
    "score": 6,
    "symbol": "subobject_forward_0051e380",
    "va": "0x0051e380"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "pkg-w2-0052e640",
    "score": 6,
    "symbol": "reconstruct_0052e640",
    "va": "0x0052e640"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "pkg-w2-0052e650",
    "score": 6,
    "symbol": "reconstruct_0052e650",
    "va": "0x0052e650"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "pkg-editor-w1-0057d6f0",
    "score": 6,
    "symbol": "re_0057d6f0",
    "va": "0x0057d6f0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "pkg-swarm-w2-00586700",
    "score": 6,
    "symbol": "re_00586700",
    "va": "0x00586700"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "pkg-swarm-w1-005b2490",
    "score": 6,
    "symbol": "re_005b2490",
    "va": "0x005b2490"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "pkg-swarm-w1-005ba0d0",
    "score": 6,
    "symbol": "re_005ba0d0",
    "va": "0x005ba0d0"
  }
]
```

## 12_existing_reconstruction

- State: `present`
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

## 13_semantic_hypotheses

- State: `missing`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

## 14_conflicts_questions

- State: `conflicted`
- Provenance: `reconstruction/knowledge/index.json, knowledgegraph/research/semantic-decomp.json`

```json
{
  "conflicts": [
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

[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditor__HandleMessage.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}`

```json
{
  "provenance": [
    {
      "mode": "derived",
      "ref": "ephemeral reconstruction_knowledge.build_index",
      "source_class": "generated_index"
    },
    {
      "mode": "persisted",
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditor__HandleMessage.c",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "knowledgegraph/research/source-reconstruction-manifest.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "knowledgegraph/triage/queue-f0e310e0-v6.json",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.json",
    ".spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditor__HandleMessage.c"
  ],
  "required_categories": [
    "ABI",
    "CALLS",
    "GLOBALS",
    "FIELDS/OFFSETS",
    "CONSTANTS",
    "CONTROL FLOW",
    "VIRTUAL DISPATCH",
    "RETURN SEMANTICS",
    "EVIDENCE COVERAGE"
  ]
}
```
