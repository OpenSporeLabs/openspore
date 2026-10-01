# Reconstruction context 0x00e616c0

- Status: `partial`
- Content SHA-256: `7bd2a3774865bcac92379819d287a64006bc94f2d1a6871f7c3f8a5bb4cbebfd`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00e616c0",
  "phase": "reconstruction",
  "target": "0x00e616c0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueGameModeState",
  "name": "cell_mode_constructor_00e616c0",
  "package": "PKG-GAME-MODE-WAVE7",
  "subsystem": "App.GameMode",
  "va": "0x00e616c0"
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
  "content_sha256": "9b7e24b7046f9d9cc79e816926d2954522e67bb2ee6308fff18b9513eba3de25",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00e616c0 failed: Decompilation did not complete. Reason: ",
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
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "cdecl",
  "ordinary_stack_arguments": [
    "CellModeOwner* owner"
  ],
  "receiver": "none; owner is loaded from [ESP+4]",
  "ret_form": "plain RET; caller removes the four-byte owner argument",
  "return": "void"
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [],
  "callers": [],
  "edge_rows": [
    {
      "callsite": "0x00e616cf",
      "direction": "out",
      "other": "0x00f473a0",
      "reference_type": "direct-call"
    }
  ],
  "external_callees": []
}
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "OpaqueGameModeState"
  ],
  "vtables": [
    "vtable:0x01485558"
  ]
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
      "Observe constructor reachability, allocator identity, object vtable publication, owner vtable +0x20 target, and null-allocation behavior; runtime validation is not run."
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
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00e616cf",
      "direction": "out",
      "other": "0x00f473a0",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 0,
  "fan_out": 0,
  "manifest_callees": [],
  "manifest_callers": [],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0532",
    "size": 1
  },
  "vtable_reference_count": 3
}
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "same_class",
      "shared_types:OpaqueGameModeState"
    ],
    "package": "PKG-GAME-MODE-WAVE7",
    "score": 22,
    "symbol": "app_mode_activate_by_name_007d8360",
    "va": "0x007d8360"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "same_class",
      "shared_types:OpaqueGameModeState"
    ],
    "package": "PKG-GAME-MODE-WAVE7",
    "score": 22,
    "symbol": "app_mode_activate_007d85b0",
    "va": "0x007d85b0"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "same_class",
      "shared_types:OpaqueGameModeState"
    ],
    "package": "PKG-GAME-MODE-WAVE7",
    "score": 22,
    "symbol": "app_mode_activate_index_007d8c80",
    "va": "0x007d8c80"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "same_class",
      "shared_types:OpaqueGameModeState"
    ],
    "package": "PKG-GAME-MODE-WAVE7",
    "score": 22,
    "symbol": "strategy_request_ready_00b5b840",
    "va": "0x00b5b840"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "same_class",
      "shared_types:OpaqueGameModeState"
    ],
    "package": "PKG-GAME-MODE-WAVE7",
    "score": 22,
    "symbol": "strategy_queue_primary_00b5b880",
    "va": "0x00b5b880"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "same_class",
      "shared_types:OpaqueGameModeState"
    ],
    "package": "PKG-GAME-MODE-WAVE7",
    "score": 22,
    "symbol": "strategy_queue_secondary_00b5b8a0",
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg_game_mode_wave7/game_mode_wave7.cpp",
  "files": [
    "src/reconstruction/pkg_game_mode_wave7/game_mode_wave7.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave7/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-game-mode-wave7/00e616c0.json"
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
        "0x00e61550",
        "0x00e616c0",
        "0x01485550",
        "0x01485550",
        "0x01485550"
      ],
      "conflict_id": "TB-INH-006",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": {
        "merge_decision": "structural_only",
        "preferred_claim": "Record interface implementation as structural interface evidence only.",
        "preserved_alternatives": true,
        "scope_note": "The current source is comparison-only and cannot backfill the original ABI.",
        "status": "preserved_alternatives",
        "taxonomy": "preserved_alternatives"
      },
      "resolution_status": "preserved_alternatives",
      "source": "knowledgegraph/research/conflicts/track-b-vtable-fields.json",
      "subject": "IGameMode implementation and cCellModeStrategy concrete table",
      "unresolved_reason": "The cited static evidence leaves the competing owner, slot, layout, or lifecycle interpretation unresolved; no positive original runtime or MSVC RTTI evidence is available."
    },
    {
      "anchors": [
        "0x01485550",
        "0x01485550",
        "0x01485550",
        "0x00e61550",
        "0x00e616c0",
        "0x01485550",
        "0x01485550",
        "0x00e61550",
        "0x01485550",
        "0x00e61550",
        "0x00e616c0",
        "0x0057ce80",
        "0x01485550",
        "0x01485550"
      ],
      "conflict_id": "TB-VT-002",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": {
        "merge_decision": "preferred_claim_with_limit",
        "
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave7/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-game-mode-wave7/00e616c0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_game_mode_wave7/game_mode_wave7.cpp', 'source_class': 'committed_artifact'}`

```json
{
  "provenance": [
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
      "ref": "reconstruction/integrated/batch-2026-09-25-wave7/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg-game-mode-wave7/00e616c0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_game_mode_wave7/game_mode_wave7.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.json",
    "src/reconstruction/pkg_game_mode_wave7/game_mode_wave7.cpp"
  ],
  "required_categories": [
    "ABI",
    "CALLS",
    "GLOBALS",
    "FIELDS/OFFSETS",
    "CONSTANTS",
   
[TRUNCATED]
```
