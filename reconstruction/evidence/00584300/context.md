# Reconstruction context 0x00584300

- Status: `partial`
- Content SHA-256: `6b4d19cc7212b51df01a3a6ca8afb7d9e0d25475c1e0ae8e3bf890fb578f5582`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00584300",
  "phase": "reconstruction",
  "target": "0x00584300"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "Editors::cEditor::Initialize",
  "package": null,
  "subsystem": "Editor",
  "va": "0x00584300"
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
  "content_sha256": "4b1f0ee4f77fd3dc935cc8ed90039f5558be6f0c17cdd5190d4e6f194530af88",
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
      "va": "0x00643a40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0067dcc0"
    },
    {
      "name": "FUN_007c3f70",
      "reconstructed": false,
      "va": "0x007c3f70"
    }
  ],
  "callers": [],
  "edge_rows": [
    {
      "callsite": "0x005844ff",
      "direction": "out",
      "other": "0x004b8af0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00584543",
      "direction": "out",
      "other": "0x004b8c10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00585058",
      "direction": "out",
      "other": "0x00563de0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0058505d",
      "direction": "out",
      "other": "0x00563de0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00585163",
      "direction": "out",
      "other": "0x00584070",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005845dd",
      "direction": "out",
      "other": "0x0059e3c0",
      "reference_type": "computed-call"
    },
    {
      "callsite": "0x005845b6",
      "direction": "out",
      "other": "0x0059ec80",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00584410",
      "direction": "out",
      "other": "0x005a9b60",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005844b0",
      "direction": "out",
      "other": "0x005d5e40",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x
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
      "va": "0x00643a40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0067dcc0"
    },
    {
      "name": "FUN_007c3f70",
      "reconstructed": false,
      "va": "0x007c3f70"
    }
  ],
  "callees_truncated": false,
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x005844ff",
      "direction": "out",
      "other": "0x004b8af0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00584543",
      "direction": "out",
      "other": "0x004b8c10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00585058",
      "direction": "out",
      "other": "0x00563de0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0058505d",
      "direction": "out",
      "other": "0x00563de0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00585163",
      "direction": "out",
      "other": "0x00584070",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005845dd",
      "direction": "out",
      "other": "0x0059e3c0",
      "reference_type": "computed-call"
    },
    {
      "callsite": "0x005845b6",
      "direction": "out",
      "other": "0x0059ec80",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00584410",
      "direction": "out",
      "other": "0x005a9b60",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005844b0",
      "direction": "out",
      "other": "
[TRUNCATED]
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013f57f8"
    ],
    "package": "pkg-editor-w1-0057d6f0",
    "score": 10,
    "symbol": "re_0057d6f0",
    "va": "0x0057d6f0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013f57f8"
    ],
    "package": "pkg-swarm-w2-00586700",
    "score": 10,
    "symbol": "re_00586700",
    "va": "0x00586700"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013f57f8"
    ],
    "package": "pkg-swarm-w1-005b2490",
    "score": 10,
    "symbol": "re_005b2490",
    "va": "0x005b2490"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013f57f8"
    ],
    "package": "pkg-swarm-w1-005ba0d0",
    "score": 10,
    "symbol": "re_005ba0d0",
    "va": "0x005ba0d0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013f57f8"
    ],
    "package": "pkg-editor-child-007f30d0",
    "score": 10,
    "symbol": "FUN_007f30d0",
    "va": "0x007f30d0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013f57f8"
    ],
    "package": "pkg-shared-default-true-wave12",
    "score": 10,
    "symbol": "pkg_shared_default_true_00b1fbf0",
    "va": "0x00b1fbf0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013f57f8"
    ],
    "package": "pkg-w2-00e5cac0",
    "score": 10,
    "symbol": "FUN_00e5cac0",
    "va": "0x00e5cac0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "pkg-vft-preinc-0051e340",

[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditor__Initialize.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditor__Initialize.c"
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
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditor__Initialize.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditor__Initialize.c",
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
    ".spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditor__Initialize.c"
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
