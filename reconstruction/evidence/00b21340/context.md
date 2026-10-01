# Reconstruction context 0x00b21340

- Status: `partial`
- Content SHA-256: `dd881850ab3b9de1910bbb5fcfcefb91db113269a4cfec234f06ceded960d175`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00b21340",
  "phase": "reconstruction",
  "target": "0x00b21340"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "NounProjection",
  "name": "FUN_00b21340",
  "package": "PKG-11-SIM-CORE",
  "subsystem": "Simulator.NounProjection",
  "va": "0x00b21340"
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
  "content_sha256": "d67bbd35c1ac11c6e108b9b9a9ce8635c578dfc9b9cfde2e150015dd3e83c01e",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00b21340 failed: Decompilation did not complete. Reason: ",
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
  "hidden_this": true,
  "return_register": "EAX",
  "return_semantics": "The body returns the map value pointer without an AddRef, copy, or ownership transfer.",
  "return_width_bytes": 4,
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "observed_use": "Called with no source-level arguments on a map miss; its EAX result becomes the new value pointer.",
      "position": 1,
      "type": "NounCreateCallback",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x08",
      "observed_use": "Called with the selected value pointer when the value dirty byte is nonzero.",
      "position": 2,
      "type": "NounClearCallback",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x0C",
      "observed_use": "Called with value then list-node arguments when the filter callback returns nonzero.",
      "position": 3,
      "type": "NounAddCallback",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x10",
      "observed_use": "Called with list-node then noun-ID arguments; only a nonzero AL result invokes add.",
      "position": 4,
      "type": "NounFilterCallback",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x14",
      "observed_use": "Used as the map key and forwarded as the second filter argument.",
      "position": 5,
      "type": "std::uint32_t",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 0
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "pkg20_gameglobal_00ba8420",
      "reconstructed": true,
      "va": "0x00ba8420"
    },
    {
      "name": "map_int_whatever_find",
      "reconstructed": true,
      "va": "0x00e5c780"
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00acd9a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00acd9d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00acda00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ace2c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ace2f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ace4e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ace5a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ad12a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ad49b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ad49e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ad4a10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae0dd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae0e00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae6030"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae6240"
    },
    {
      "name": null,
  
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "ContainerCreateCallback_t/ContainerClearCallback_t/ContainerAddCallback_t/ContainerFilterCallback_t",
    "NounAddCallback",
    "NounClearCallback",
    "NounCreateCallback",
    "NounCreateMap",
    "NounFilterCallback",
    "NounListNode",
    "NounMapEntry",
    "NounProjection",
    "NounProjectionVector",
    "NounProjectionVector *",
    "OrderedMap",
    "OrderedMapEntry",
    "cGameNounManager",
    "std::int32_t",
    "std::uint32_t"
  ],
  "vtables": []
}
```

## 09_state_event_relationships

- State: `present`
- Provenance: `knowledgegraph/research/semantic-decomp.json, reconstruction/knowledge/index.json`

```json
{
  "original_bytes": 10105,
  "preview": "{\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"gate-noun-projection-callbacks-and-map-ownership\"\n    ],\n    \"validated\": 0\n  },\n  \"semantic\": {\n    \"category\": null,\n    \"classification\": \"STRONG_SEMANTIC\",\n    \"confidence\": {\n      \"mechanics\": 0.99\n    },\n    \"contradictions\": [],\n    \"downstream_unlock_count\": 256,\n    \"evidence\": [\n      {\n        \"independence\": \"same-binary disassembly corroborates decompilation\",\n        \"source\": \"Ghidra SporeApp.exe 0x00b21340: 80 instructions; RET 0x14; direct calls to 0x00e5c780 and 0x00ba8420\",\n        \"supports\": \"signature, calling convention, branches, direct callees\"\n      },\n      {\n        \"independence\": \"same-binary decompilation\",\n        \"source\": \"Ghidra SporeApp.exe FUN_00b21340\",\n        \"supports\": \"lower-bound selection, end-only insertion, dirty rebuild, borrowed return\"\n      },\n      {\n        \"independence\": \"independent same-binary consumer chain\",\n        \"source\": \"Ghidra SporeApp.exe 0x00bff2d0 and 0x00b25f40\",\n        \"supports\": \"receiver compatibility, callback ABI use, typed-vector consumer shape\"\n      },\n      {\n        \"independence\": \"same-binary helper decompilation\",\n        \"source\": \"Ghidra SporeApp.exe 0x00e5c780, 0x00ba8420, 0x00b201a0, 0x00b21410\",\n        \"supports\": \"lower_bound versus exact_find, insertion branch, invalidation and sibling erase boundary\"\n      },\n      {\n        \"independence\": \"independent rep
[TRUNCATED]
```

## 10_dependencies

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "pkg20_gameglobal_00ba8420",
      "reconstructed": true,
      "va": "0x00ba8420"
    },
    {
      "name": "map_int_whatever_find",
      "reconstructed": true,
      "va": "0x00e5c780"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00acd9a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00acd9d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00acda00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ace2c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ace2f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ace4e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ace5a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ad12a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ad49b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ad49e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ad4a10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae0dd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae0e00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae6030"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae6240"
    }
[TRUNCATED]
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "shared_types:OrderedMap,OrderedMapEntry,void *",
      "same_calling_convention",
      "direct_xref_neighbor"
    ],
    "package": "PKG-20-GAMEGLOBAL",
    "score": 14,
    "symbol": "map_int_whatever_find",
    "va": "0x00e5c780"
  },
  {
    "match_basis": [
      "shared_types:OrderedMap,OrderedMapEntry",
      "same_calling_convention",
      "direct_xref_neighbor"
    ],
    "package": "PKG-20-GAMEGLOBAL",
    "score": 11,
    "symbol": "pkg20_gameglobal_00ba8420",
    "va": "0x00ba8420"
  },
  {
    "match_basis": [
      "same_package",
      "shared_types:OrderedMapEntry"
    ],
    "package": "PKG-11-SIM-CORE",
    "score": 11,
    "symbol": "Simulator_LookupEmpireByPoliticalId",
    "va": "0x00ba9370"
  },
  {
    "match_basis": [
      "shared_types:OrderedMap,OrderedMapEntry",
      "same_calling_convention"
    ],
    "package": "PKG-20-GAMEGLOBAL",
    "score": 8,
    "symbol": "pkg20_gameglobal_00ba83a0",
    "va": "0x00ba83a0"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "PKG-11-SIM-CORE",
    "score": 8,
    "symbol": "Simulator_IsNotStarOrBinaryStar",
    "va": "0x00c8b6b0"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-13-C4-CIV-WAVE3",
    "score": 3,
    "symbol": "culture_selection_00bf9820",
    "va": "0x00bf9820"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-11-A2-PROGRESSION-ALTERNATIVE",
    "score": 3,
    "symbol": "mission_manager_operation_00fee310",
    "va": "0x00fee310"
  },
  {
    "match_basis": [
 
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg11_sim_core/noun_projection.cpp",
  "files": [
    "reconstruction/staging/pkg11-sim-core/noun_projection.cpp",
    "reconstruction/staging/pkg11-sim-core/noun_projection.hpp",
    "reconstruction/staging/pkg11-sim-core/noun_projection_model_test.cpp",
    "src/reconstruction/pkg11_sim_core/noun_projection.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-source-wave2/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg11-sim-core/00b21340.json"
  ]
}
```

## 13_semantic_hypotheses

- State: `present`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

```json
{
  "original_bytes": 9322,
  "preview": "{\n  \"category\": null,\n  \"classification\": \"STRONG_SEMANTIC\",\n  \"confidence\": {\n    \"mechanics\": 0.99\n  },\n  \"contradictions\": [],\n  \"downstream_unlock_count\": 256,\n  \"evidence\": [\n    {\n      \"independence\": \"same-binary disassembly corroborates decompilation\",\n      \"source\": \"Ghidra SporeApp.exe 0x00b21340: 80 instructions; RET 0x14; direct calls to 0x00e5c780 and 0x00ba8420\",\n      \"supports\": \"signature, calling convention, branches, direct callees\"\n    },\n    {\n      \"independence\": \"same-binary decompilation\",\n      \"source\": \"Ghidra SporeApp.exe FUN_00b21340\",\n      \"supports\": \"lower-bound selection, end-only insertion, dirty rebuild, borrowed return\"\n    },\n    {\n      \"independence\": \"independent same-binary consumer chain\",\n      \"source\": \"Ghidra SporeApp.exe 0x00bff2d0 and 0x00b25f40\",\n      \"supports\": \"receiver compatibility, callback ABI use, typed-vector consumer shape\"\n    },\n    {\n      \"independence\": \"same-binary helper decompilation\",\n      \"source\": \"Ghidra SporeApp.exe 0x00e5c780, 0x00ba8420, 0x00b201a0, 0x00b21410\",\n      \"supports\": \"lower_bound versus exact_find, insertion branch, invalidation and sibling erase boundary\"\n    },\n    {\n      \"independence\": \"independent repository static adjudication\",\n      \"source\": \"knowledgegraph/research/root-closure/followup-noun-boundary.md:7-13,38-80,84-103,176-183\",\n      \"supports\": \"actual GetData identity, callback roles, successor hazard, and preserved allo
[TRUNCATED]
```

## 14_conflicts_questions

- State: `conflicted`
- Provenance: `reconstruction/knowledge/index.json, knowledgegraph/research/semantic-decomp.json`

```json
{
  "conflicts": [
    {
      "anchors": [
        "0x00b21340",
        "0x00b21340"
      ],
      "conflict_id": "CF-006",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": null,
      "resolution_status": null,
      "source": "knowledgegraph/research/conflicts/track-f-cross-domain-impact.json",
      "subject": null,
      "unresolved_reason": {
        "missing_evidence": [
          "Concrete noun create, owner, erase, rekey, invalidation, and failure paths.",
          "Subtype-by-subtype factory and destruction evidence for cGameData, cCivilization, cCreatureBase, cTribe, cEmpire, cStarRecord, and cMission.",
          "A cross-mode identity and persistence handoff contract."
        ],
        "status": "blocked"
      }
    },
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
      "unresolved_reason": "The exact private source-level function name and complete parameter types are unknown; the noun-materializ
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-source-wave2/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg11-sim-core/00b21340.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg11-sim-core/noun_projection.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg11-sim-core/noun_projection.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg11-sim-core/noun_projection_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg11_sim_core/noun_projection.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/integrated/batch-2026-09-25-source-wave2/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg11-sim-core/00b21340.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg11-sim-core/noun_projection.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg11-sim-core/noun_projection.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg11-sim-core/
[TRUNCATED]
```
