# Reconstruction context 0x00ba8420

- Status: `partial`
- Content SHA-256: `4578d555cd88e27398b5afe206d77404630670e54cbfd21514102e39175d241d`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00ba8420",
  "phase": "reconstruction",
  "target": "0x00ba8420"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OrderedMap",
  "name": "pkg20_gameglobal_00ba8420",
  "package": "PKG-20-GAMEGLOBAL",
  "subsystem": "GameGlobal.OrderedMap",
  "va": "0x00ba8420"
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
  "content_sha256": "2126112eeefb7cc2fcf6a3fcd0803c174ffb39e8fe4c80ec990230af16a13d9c",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00ba8420 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "__thiscall observed",
  "hidden_this_register": "ECX",
  "hidden_this_type": "OrderedMap*",
  "return_register": "EAX",
  "return_type": "MapInsertResult*",
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "output",
      "observed_use": "Receives the existing or newly inserted entry and the one-byte insertion result.",
      "position": 1,
      "type": "MapInsertResult*",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x08",
      "name": "handoff",
      "observed_use": "No semantic use is established by the target body; preserved to retain the three-word caller boundary.",
      "position": 2,
      "type": "opaque 32-bit handoff word",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x0C",
      "name": "pair",
      "observed_use": "The first word is read as the unsigned query key and the pair is forwarded to node allocation.",
      "position": 3,
      "type": "const MapInsertPair*",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 12
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "pkg20_gameglobal_00ba83a0",
      "reconstructed": true,
      "va": "0x00ba83a0"
    }
  ],
  "callers": [
    {
      "name": "pkg11_sim_core_00b21340",
      "reconstructed": true,
      "va": "0x00b21340"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b2ede0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00baa660"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d02440"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d33c30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fe4d60"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00b21395",
      "direction": "in",
      "other": "0x00b21340",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00b2f0db",
      "direction": "in",
      "other": "0x00b2ede0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00baa70c",
      "direction": "in",
      "other": "0x00baa660",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d02526",
      "direction": "in",
      "other": "0x00d02440",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d33c81",
      "direction": "in",
      "other": "0x00d33c30",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d33cce",
      "direction": "in",
      "other": "0x00d33c30",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00fe4e42",
      "direction": "in",

[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "MapInsertPair",
    "MapInsertResult",
    "MapInsertResult*",
    "OrderedMap",
    "OrderedMap*",
    "OrderedMapEntry",
    "TargetWord",
    "const MapInsertPair*",
    "opaque 32-bit handoff word"
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
      "gate-map-insertion"
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
  "callees": [
    {
      "name": "pkg20_gameglobal_00ba83a0",
      "reconstructed": true,
      "va": "0x00ba83a0"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": "pkg11_sim_core_00b21340",
      "reconstructed": true,
      "va": "0x00b21340"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b2ede0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00baa660"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d02440"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d33c30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fe4d60"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00b21395",
      "direction": "in",
      "other": "0x00b21340",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00b2f0db",
      "direction": "in",
      "other": "0x00b2ede0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00baa70c",
      "direction": "in",
      "other": "0x00baa660",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d02526",
      "direction": "in",
      "other": "0x00d02440",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d33c81",
      "direction": "in",
      "other": "0x00d33c30",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d33cce",
      "direction": "in",
      "other": "0x00d33c30",
      "reference_type":
[TRUNCATED]
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
      "shared_types:MapInsertPair,MapInsertResult,MapInsertResult*,OrderedMap",
      "same_calling_convention",
      "direct_xref_neighbor"
    ],
    "package": "PKG-20-GAMEGLOBAL",
    "score": 33,
    "symbol": "pkg20_gameglobal_00ba83a0",
    "va": "0x00ba83a0"
  },
  {
    "match_basis": [
      "same_package",
      "same_class",
      "shared_types:OrderedMap,OrderedMapEntry,TargetWord",
      "same_calling_convention"
    ],
    "package": "PKG-20-GAMEGLOBAL",
    "score": 24,
    "symbol": "map_int_whatever_find",
    "va": "0x00e5c780"
  },
  {
    "match_basis": [
      "shared_types:OrderedMap,OrderedMapEntry",
      "same_calling_convention",
      "direct_xref_neighbor"
    ],
    "package": "PKG-11-SIM-CORE",
    "score": 11,
    "symbol": "pkg11_sim_core_00b21340",
    "va": "0x00b21340"
  },
  {
    "match_basis": [
      "shared_types:OrderedMapEntry,TargetWord"
    ],
    "package": "PKG-11-SIM-CORE",
    "score": 6,
    "symbol": "Simulator_LookupEmpireByPoliticalId",
    "va": "0x00ba9370"
  },
  {
    "match_basis": [
      "shared_types:TargetWord"
    ],
    "package": "PKG-APP-SAFE-WAVE11",
    "score": 3,
    "symbol": "pair_vector_insert_004786e0",
    "va": "0x004786e0"
  },
  {
    "match_basis": [
      "shared_types:TargetWord"
    ],
    "package": "PKG-APP-SAFE-WAVE11",
    "score": 3,
    "symbol": "stream_probe_dispatch_004bc540",
    "va": "0x004bc540"
  },
  {
    "match_basis": [
      "shared_types:TargetWord"
    ],
    "package": "PKG-SKINN
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg20_gameglobal/map_insert.cpp",
  "files": [
    "reconstruction/staging/pkg20-gameglobal/map_insert.cpp",
    "reconstruction/staging/pkg20-gameglobal/map_insert.hpp",
    "reconstruction/staging/pkg20-gameglobal/map_insert_model_test.cpp",
    "src/reconstruction/pkg20_gameglobal/map_insert.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-source-wave3/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg20-gameglobal/00ba8420.json"
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
        "0x00ba8420",
        "0x00e5c780",
        "0x00b212d0",
        "0x00b21340",
        "0x00b21340",
        "0x00b21340",
        "0x00e9c9a0",
        "0x00b21340",
        "0x00b212d0",
        "0x00b21340",
        "0x00b21340",
        "0x00ba8420",
        "0x00e9c9a0",
        "0x00b21340",
        "0x00e9c9a0",
        "0x00e5c780"
      ],
      "conflict_id": "LC-011",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "RESOLVED_SUPPORTED",
      "resolution_status": "RESOLVED_SUPPORTED",
      "source": "knowledgegraph/research/conflicts/track-a-type-signature.json",
      "subject": "0x00B21340 semantic identity",
      "unresolved_reason": "The exact private source-level function name and complete parameter types are unknown; the noun-materialization semantics and rejection of the message-registration label are resolved."
    },
    {
      "anchors": [
        "0x00e5c780",
        "0x00b21340",
        "0x00ba8420",
        "0x00000004",
        "0x00b21340",
        "0x00e5c780",
        "0x00b21340",
        "0x00b21340"
      ],
      "conflict_id": "TB-LC-011",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": {
        "merge_decision": "preferred_claim_with_limit",
        "preferred_claim": "Use map/list callback or noun-materialization mechanics as the preferred behavior label for 0x00B21340.",
        "preserved_alternatives": true,
        "scope_note": "The message-handler label remains withdrawn or contested because the owner and key/value domain 
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-source-wave3/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg20-gameglobal/00ba8420.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg20-gameglobal/map_insert.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg20-gameglobal/map_insert.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg20-gameglobal/map_insert_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg20_gameglobal/map_insert.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/integrated/batch-2026-09-25-source-wave3/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg20-gameglobal/00ba8420.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg20-gameglobal/map_insert.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg20-gameglobal/map_insert.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg20-gameglobal/ma
[TRUNCATED]
```
