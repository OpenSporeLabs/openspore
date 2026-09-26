# Reconstruction context 0x00576c50

- Status: `partial`
- Content SHA-256: `4e1aafced223c8d31700542612b049de08628839f3403b5b04475dd1e69ef1f8`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00576c50",
  "phase": "reconstruction",
  "target": "0x00576c50"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "Editors::cEditor::Dispose",
  "package": null,
  "subsystem": "Editor",
  "va": "0x00576c50"
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
  "content_sha256": "a783cc48ebc5f48fdc73e205fffb16eee5a65971bb1d19f65229ad3a5d14b5e5",
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
      "name": null,
      "reconstructed": false,
      "va": "0x0067dcc0"
    },
    {
      "name": "FUN_007c3ba0",
      "reconstructed": false,
      "va": "0x007c3ba0"
    },
    {
      "name": "FUN_007c4000",
      "reconstructed": false,
      "va": "0x007c4000"
    }
  ],
  "callers": [],
  "edge_rows": [
    {
      "callsite": "0x00576d38",
      "direction": "out",
      "other": "0x004ad330",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00576d74",
      "direction": "out",
      "other": "0x004ad330",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00576f37",
      "direction": "out",
      "other": "0x004b9140",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00576d24",
      "direction": "out",
      "other": "0x00563de0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00576d29",
      "direction": "out",
      "other": "0x00563de0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00576cdb",
      "direction": "out",
      "other": "0x00571db0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00577101",
      "direction": "out",
      "other": "0x005a98f0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00576ca3",
      "direction": "out",
      "other": "0x0067dcc0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00576eab",
      "direction": "out",
      "other": "0x0067dd80",
      "reference_type": "direct-call"
    },
    {
      "callsi
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
    "vtable:0x013f57f8"
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
      "name": null,
      "reconstructed": false,
      "va": "0x0067dcc0"
    },
    {
      "name": "FUN_007c3ba0",
      "reconstructed": false,
      "va": "0x007c3ba0"
    },
    {
      "name": "FUN_007c4000",
      "reconstructed": false,
      "va": "0x007c4000"
    }
  ],
  "callees_truncated": false,
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00576d38",
      "direction": "out",
      "other": "0x004ad330",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00576d74",
      "direction": "out",
      "other": "0x004ad330",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00576f37",
      "direction": "out",
      "other": "0x004b9140",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00576d24",
      "direction": "out",
      "other": "0x00563de0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00576d29",
      "direction": "out",
      "other": "0x00563de0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00576cdb",
      "direction": "out",
      "other": "0x00571db0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00577101",
      "direction": "out",
      "other": "0x005a98f0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00576ca3",
      "direction": "out",
      "other": "0x0067dcc0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00576eab",
      "direction": "out",
      "o
[TRUNCATED]
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "shared_vtable:vtable:0x013f57f8"
    ],
    "package": "PKG-EDITOR-INPUT-WAVE6",
    "score": 4,
    "symbol": "editor_input_005737d0",
    "va": "0x005737d0"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x013f57f8"
    ],
    "package": "PKG-EDITOR-INPUT-WAVE6",
    "score": 4,
    "symbol": "editor_input_00585890",
    "va": "0x00585890"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x013f57f8"
    ],
    "package": "PKG-EDITOR-INPUT-WAVE6",
    "score": 4,
    "symbol": "editor_input_00585d10",
    "va": "0x00585d10"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x013f57f8"
    ],
    "package": "PKG-EDITOR-INPUT-WAVE6",
    "score": 4,
    "symbol": "editor_input_00588570",
    "va": "0x00588570"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x013f57f8"
    ],
    "package": "PKG-EDITOR-INPUT-WAVE6",
    "score": 4,
    "symbol": "editor_input_0058ac10",
    "va": "0x0058ac10"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x013f57f8"
    ],
    "package": "PKG-EDITOR-INPUT-WAVE6",
    "score": 4,
    "symbol": "editor_input_0058b650",
    "va": "0x0058b650"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditor__Dispose.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditor__Dispose.c"
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
  "conflicts": {
    "original_bytes": 10839,
    "preview": "[\n  {\n    \"anchors\": [\n      \"0x00584300\",\n      \"0x00584300\",\n      \"0x005737d0\",\n      \"0x005737d0\",\n      \"0x00576c50\",\n      \"0x00576c50\",\n      \"0x00584300\",\n      \"0x00584300\",\n      \"0x00585d10\",\n      \"0x00585d10\",\n      \"0x00586410\",\n      \"0x00586410\",\n      \"0x00586b00\",\n      \"0x00586b00\",\n      \"0x00587270\",\n      \"0x00587270\"\n    ],\n    \"conflict_id\": \"U-001-mission-transitions\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"Mission enum/field surface is known, but no complete direct writer and callback body establishes each transition. SDK contract is not promoted to native order.\",\n    \"resolution_status\": \"Mission enum/field surface is known, but no complete direct writer and callback body establishes each transition. SDK contract is not promoted to native order.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00582fe0\",\n      \"0x00587270\",\n      \"0x0059c830\",\n      \"0x0059c830\",\n      \"0x00576c50\",\n      \"0x00576c50\",\n      \"0x00582fe0\",\n      \"0x00582fe0\",\n      \"0x00582fe0\",\n      \"0x00584300\",\n      \"0x00584300\",\n      \"0x00586410\",\n      \"0x00586410\",\n      \"0x00586b00\",\n      \"0x00586b00\",\n      \"0x00587270\"\n    ],\n    \"confl
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'ref': 'ephemeral reconstruction_knowledge.build_index', 'mode': 'derived', 'source_class': 'generated_index'}, {'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditor__Dispose.c', 'mode': 'persisted', 'source_class': 'committed_artifact'}, {'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'mode': 'persisted', 'source_class': 'committed_artifact'}, {'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'mode': 'persisted', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditor__Dispose.c",
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
    ".spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditor__Dispose.c"
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
