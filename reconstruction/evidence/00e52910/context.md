# Reconstruction context 0x00e52910

- Status: `partial`
- Content SHA-256: `58749b2d0dfdaea86970c5e6beda2e39e6e08379429e457f0ec1415a19a37f66`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00e52910",
  "phase": "reconstruction",
  "target": "0x00e52910"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "None",
  "name": "cell_ai_select_profile_00e52910",
  "package": "PKG-06A-CELL-AI-SELECTION",
  "subsystem": "Simulator.Cell",
  "va": "0x00e52910"
}
```

## 03_current_status

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "blocked": false,
  "reconstructed": true,
  "runtime_gated": true,
  "runtime_validated": 0,
  "status": "reconstructed"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "8b4b62e89e3f77b631f388ab51686195d9d54008d56edcf37157ee6da541a1b8",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00e52910 failed: Decompilation did not complete. Reason: ",
      "mode": "LIVE",
      "status": "unavailable"
    }
  ],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `missing`
- Provenance: ``

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "original_bytes": 8680,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"ordinary_stack_argument_slots\": [\n      \"entry_ESP+0x4\"\n    ],\n    \"ordinary_stack_arguments\": [\n      {\n        \"entry_offset\": \"entry_ESP+0x4\",\n        \"observed\": true,\n        \"ordinal\": 1,\n        \"read\": false,\n        \"size_inferred\": false,\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      }\n    ],\n    \"ret_form\": \"RET\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"unclassified_in_EAX\",\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"entry_ESP+0x4\",\n        \"observed\": true,\n        \"ordinal\": 1,\n        \"read\": false,\n        \"size_inferred\": false,\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      }\n    ],\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"RET\"\n  },\n  \"abstained_because\": [\n    \"receiver_not_determinable: ecx_reassigned_before_deref\",\n    \"receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_reassigned_before_deref), and the convention rule that would apply discriminates on receiver absence\"\n  ],\n  \"cleanup\": {\n    \"bytes\": 0,\n    \"confidence\": \"INFERRED\",\n    \"corroboration\": \"not_available\",\n    \"evidence\": \"ret with no immediate\",\n    \"side\": \"caller\"\n  },\n  \"completeness\": \"PARTIAL\",\n  \"conflicts\": [],\n  \"content_sha256\": \"89e2ffa779f5e77b68d15fb5e577730dabe37edf0d7e1da3bc
[TRUNCATED]
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e575f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e57890"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e67c40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e686c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e69480"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e695f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e6cbd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e6f990"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e6fbb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e6fce0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e6fd70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e70650"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e707d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e70cf0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e71300"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e71520"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00e57657",
      "direction": "in",
      "other": "0x00e575f0",
      "reference_type": "direct-call"
    },

[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [
    "global:std::byte* g_cell_game_016b3c04"
  ],
  "types": [
    "None",
    "ObservedCellAiData",
    "ObservedCellCellResource",
    "std::int32_t"
  ],
  "vtables": []
}
```

## 09_state_event_relationships

- State: `present`
- Provenance: `knowledgegraph/research/semantic-decomp.json, reconstruction/knowledge/index.json`

```json
{
  "runtime": {
    "blocking_reason": null,
    "gates": [
      "gate-cell-ai-selection"
    ],
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
  "callees": [],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e575f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e57890"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e67c40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e686c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e69480"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e695f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e6cbd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e6f990"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e6fbb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e6fce0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e6fd70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e70650"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e707d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e70cf0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e71300"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e71520"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e71f00"
    },
    {
      "name": null,
      "reconst
[TRUNCATED]
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "same_class",
      "shared_types:None,ObservedCellCellResource",
      "direct_xref_neighbor"
    ],
    "package": "PKG-06C-CELL-BEHAVIOR-DISPATCH",
    "score": 14,
    "symbol": "cell_behavior_dispatch_00e7a190",
    "va": "0x00e7a190"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_class",
      "shared_types:None"
    ],
    "package": "PKG-06-CELL-STATE",
    "score": 14,
    "symbol": "FUN_00e7fd00",
    "va": "0x00e7fd00"
  },
  {
    "match_basis": [
      "same_class",
      "shared_types:None"
    ],
    "package": "PKG-11-H2-ROOT-ACCESSORS",
    "score": 8,
    "symbol": "root_accessor_00b3d3b0",
    "va": "0x00b3d3b0"
  },
  {
    "match_basis": [
      "same_class",
      "shared_types:None"
    ],
    "package": "PKG-11-H2-ROOT-ACCESSORS",
    "score": 8,
    "symbol": "root_accessor_00b3d3e0",
    "va": "0x00b3d3e0"
  },
  {
    "match_basis": [
      "same_class",
      "shared_types:None"
    ],
    "package": "PKG-11-H2-ROOT-ACCESSORS",
    "score": 8,
    "symbol": "root_accessor_00b3d3f0",
    "va": "0x00b3d3f0"
  },
  {
    "match_basis": [
      "same_class",
      "shared_types:None"
    ],
    "package": "PKG-11-H2-ROOT-ACCESSORS",
    "score": 8,
    "symbol": "root_accessor_00b3d430",
    "va": "0x00b3d430"
  },
  {
    "match_basis": [
      "same_class",
      "shared_types:None"
    ],
    "package": "PKG-13-E3-EMPIRE-STATE-WAVE2",
    "score": 8,
    "symbol": "SpeciesProfileSelector_00c30cc0",
    "va": "0x00c30cc0"
  },
  {
    "match_basis": [
      "same_class",
      "shared_types:None"

[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg06a_cell_ai_selection/cell_ai_selection.cpp",
  "files": [
    "src/reconstruction/pkg06a_cell_ai_selection/cell_ai_selection.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-pkg06a-cell-ai-selection/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg06a-cell-ai-selection/00e52910.json"
  ]
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
        "0x00e7a4a0",
        "0x00e7a7c0",
        "0x00e7a7c0",
        "0x00e7e6c0",
        "0x00e7a4a0",
        "0x00e7a4a0",
        "0x00e62340",
        "0x00e52910",
        "0x00e7a7c0",
        "0x00e7a7c0",
        "0x00bfc460",
        "0x00bfc460",
        "0x00bfc490",
        "0x00bfc490",
        "0x00bfc4a0",
        "0x00bfc4a0"
      ],
      "conflict_id": "cell_field_112_semantics",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The cited direct body establishes a bounded state mutation or call anchor, but the full transition policy, consumer order, and runtime reachability remain unresolved.",
      "resolution_status": "The cited direct body establishes a bounded state mutation or call anchor, but the full transition policy, consumer order, and runtime reachability remain unresolved.",
      "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
      "subject": null,
      "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
    },
    {
      "anchors": [
        "0x00e52910",
        "0x00e575f0",
        "0x00e52910",
        "0x00e7e6c0",
        "0x00e7a7c0",
        "0x00e7a4a0",
        "0x00e52910",
        "0x00e7a7c0",
        "0x00e72060",
        "0x00e52910",
        "0x00e52910",
        "0x00e52910",
        "0x00e575f0",
        "0x00e575f0",
        "0x00e575f0",
        "0x00e7a4a0"
      ],
      "conflict_id": "cell_target_selector_domain",
      "kind": "conflict_ledger",
      "rej
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'derived'}, {'mode': 'derived', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'derived'}, {'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-pkg06a-cell-ai-selection/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg06a-cell-ai-selection/00e52910.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg06a_cell_ai_selection/cell_ai_selection.cpp', 'source_class': 'committed_artifact'}`

```json
{
  "provenance": [
    {
      "mode": "derived",
      "ref": "GhidraMCP /disassemble_function",
      "source_class": "derived"
    },
    {
      "mode": "derived",
      "ref": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
      "source_class": "derived"
    },
    {
      "mode": "derived",
      "ref": "ephemeral reconstruction_knowledge.build_index",
      "source_class": "generated_index"
    },
    {
      "mode": "derived",
      "ref": "tools/reconstruction_tooling/abi_infer.py",
      "source_class": "derived"
    },
    {
      "mode": "live",
      "ref": "GhidraMCP /disassemble_function",
      "source_class": "ghidra"
    },
    {
      "mode": "live",
      "ref": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
      "source_class": "ghidra"
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
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/integrated/batch-2026-09-25-pkg06a-cell-ai-selection/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg06a-cell-ai-selection/00e52910.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg06a_cell_ai
[TRUNCATED]
```
