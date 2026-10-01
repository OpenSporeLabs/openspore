# Reconstruction context 0x00e5c780

- Status: `partial`
- Content SHA-256: `8166f89dd47746394032174b7e3f691ce80adb0f345724f85130658636658fbd`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00e5c780",
  "phase": "reconstruction",
  "target": "0x00e5c780"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OrderedMap",
  "name": "map_int_whatever_find",
  "package": "PKG-20-GAMEGLOBAL",
  "subsystem": "GameGlobal.Collections",
  "va": "0x00e5c780"
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
  "content_sha256": "e4a7aaa5ce14ba7a8db8069f9188a30f5e4c5b4559b91687d6a658a19830c937",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00e5c780 failed: Decompilation did not complete. Reason: ",
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
  "return_observation": "The live function ends through void RET paths after writing the result pointer and cleans two stack words with RET 8.",
  "return_type": "void",
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "observed_use": "Receives the node pointer selected by the search.",
      "position": 1,
      "type": "OrderedMapEntry **",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x08",
      "observed_use": "The first stack word is dereferenced as the unsigned comparison key.",
      "position": 2,
      "type": "const std::uint32_t *",
      "width_bytes": 4
    }
  ]
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [],
  "callers": [
    {
      "name": "Editors::cEditor::Update",
      "reconstructed": false,
      "va": "0x0058be50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059c6e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059ca70"
    },
    {
      "name": "EditorAnimWorld_GetCreatureController_0059cac0",
      "reconstructed": true,
      "va": "0x0059cac0"
    },
    {
      "name": "EditorAnimWorld_PlayAnimation_0059cb10",
      "reconstructed": true,
      "va": "0x0059cb10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059cbd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059cc40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059cd20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059cdb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059ce30"
    },
    {
      "name": "EditorAnimWorld_SetTargetAngle_0059cea0",
      "reconstructed": true,
      "va": "0x0059cea0"
    },
    {
      "name": "EditorAnimWorld_SetTargetPosition_0059cf00",
      "reconstructed": true,
      "va": "0x0059cf00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059cf60"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059cfb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059d010"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "OrderedMap",
    "OrderedMapEntry",
    "OrderedMapEntry **",
    "OrderedMapNode",
    "OrderedMapNode *",
    "TargetWord",
    "const std::uint32_t *",
    "map<unsigned int, int>",
    "rbtree_node_base",
    "std::uint32_t",
    "void",
    "void *"
  ],
  "vtables": []
}
```

## 09_state_event_relationships

- State: `present`
- Provenance: `knowledgegraph/research/semantic-decomp.json, reconstruction/knowledge/index.json`

```json
{
  "original_bytes": 8595,
  "preview": "{\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"gate-map-root-publication-and-caller-fault-paths\"\n    ],\n    \"validated\": 0\n  },\n  \"semantic\": {\n    \"category\": \"GAMEPLAY_LOGIC\",\n    \"classification\": \"BOUNDED_SEMANTIC\",\n    \"confidence\": {\n      \"identity\": 0.86,\n      \"mechanics\": 0.99\n    },\n    \"contradictions\": [\n      {\n        \"path\": \"evidence.5\",\n        \"source\": \"knowledgegraph/research/semantic-decomp/worker-01-gameglobal.json\",\n        \"value\": {\n          \"kind\": \"repository_contradiction\",\n          \"source\": \"docs/analysis/architecture-resolution.md:50-86\",\n          \"statement\": \"The committed resolution claims lower_bound and rejects exact find; this conflicts with the target's final CMP/JC equality check and is retained as a contradiction.\"\n        }\n      },\n      {\n        \"path\": \"evidence.6\",\n        \"source\": \"knowledgegraph/research/semantic-decomp/worker-01-gameglobal.json\",\n        \"value\": {\n          \"kind\": \"repository_contradiction\",\n          \"source\": \"knowledgegraph/research/global-campaign-2026/conflicts/track-a-type-signature.json:602-779\",\n          \"statement\": \"The conflict artifact calls the target an ordered lower-bound helper, while the live target body and sibling 0x0059c740 enforce exact-key selection.\"\n        }\n      }\n    ],\n    \"downstream_unlock_count\": 239,\n    \"evidence\": [\n      {\n        \"kind\": \"disassembly\",\n        \"source\": \"ghidra://Spo
[TRUNCATED]
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
      "name": "Editors::cEditor::Update",
      "reconstructed": false,
      "va": "0x0058be50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059c6e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059ca70"
    },
    {
      "name": "EditorAnimWorld_GetCreatureController_0059cac0",
      "reconstructed": true,
      "va": "0x0059cac0"
    },
    {
      "name": "EditorAnimWorld_PlayAnimation_0059cb10",
      "reconstructed": true,
      "va": "0x0059cb10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059cbd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059cc40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059cd20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059cdb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059ce30"
    },
    {
      "name": "EditorAnimWorld_SetTargetAngle_0059cea0",
      "reconstructed": true,
      "va": "0x0059cea0"
    },
    {
      "name": "EditorAnimWorld_SetTargetPosition_0059cf00",
      "reconstructed": true,
      "va": "0x0059cf00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059cf60"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059cfb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059d010"
    },
    {
      "name": null,
      "reconstr
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
      "same_class",
      "shared_types:OrderedMap,OrderedMapEntry,TargetWord",
      "same_calling_convention"
    ],
    "package": "PKG-20-GAMEGLOBAL",
    "score": 24,
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
    "symbol": "pkg20_gameglobal_00ba8420",
    "va": "0x00ba8420"
  },
  {
    "match_basis": [
      "shared_types:OrderedMap,OrderedMapEntry,void *",
      "same_calling_convention",
      "direct_xref_neighbor"
    ],
    "package": "PKG-11-SIM-CORE",
    "score": 14,
    "symbol": "pkg11_sim_core_00b21340",
    "va": "0x00b21340"
  },
  {
    "match_basis": [
      "shared_types:OrderedMapEntry,TargetWord",
      "direct_xref_neighbor"
    ],
    "package": "PKG-11-SIM-CORE",
    "score": 9,
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
    "package": "PKG-SKINNER-SAFE-WAVE11",
    "score": 3,

[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg20_gameglobal/map_search.cpp",
  "files": [
    "reconstruction/staging/pkg20-gameglobal/map_search.cpp",
    "reconstruction/staging/pkg20-gameglobal/map_search.hpp",
    "reconstruction/staging/pkg20-gameglobal/map_search_model_test.cpp",
    "src/reconstruction/pkg20_gameglobal/map_search.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-source-wave2/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg20-gameglobal/00e5c780.json"
  ]
}
```

## 13_semantic_hypotheses

- State: `present`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

```json
{
  "original_bytes": 7924,
  "preview": "{\n  \"category\": \"GAMEPLAY_LOGIC\",\n  \"classification\": \"BOUNDED_SEMANTIC\",\n  \"confidence\": {\n    \"identity\": 0.86,\n    \"mechanics\": 0.99\n  },\n  \"contradictions\": [\n    {\n      \"path\": \"evidence.5\",\n      \"source\": \"knowledgegraph/research/semantic-decomp/worker-01-gameglobal.json\",\n      \"value\": {\n        \"kind\": \"repository_contradiction\",\n        \"source\": \"docs/analysis/architecture-resolution.md:50-86\",\n        \"statement\": \"The committed resolution claims lower_bound and rejects exact find; this conflicts with the target's final CMP/JC equality check and is retained as a contradiction.\"\n      }\n    },\n    {\n      \"path\": \"evidence.6\",\n      \"source\": \"knowledgegraph/research/semantic-decomp/worker-01-gameglobal.json\",\n      \"value\": {\n        \"kind\": \"repository_contradiction\",\n        \"source\": \"knowledgegraph/research/global-campaign-2026/conflicts/track-a-type-signature.json:602-779\",\n        \"statement\": \"The conflict artifact calls the target an ordered lower-bound helper, while the live target body and sibling 0x0059c740 enforce exact-key selection.\"\n      }\n    }\n  ],\n  \"downstream_unlock_count\": 239,\n  \"evidence\": [\n    {\n      \"kind\": \"disassembly\",\n      \"source\": \"ghidra://SporeApp.exe@0x00e5c780\",\n      \"statement\": \"The 31 instructions load map+0x0c, use map+0x04 as sentinel, compare node+0x10 unsigned against *key, reject a candidate whose key is greater than *key, write the exact candidate through the output
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
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-source-wave2/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg20-gameglobal/00e5c780.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg20-gameglobal/map_search.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg20-gameglobal/map_search.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg20-gameglobal/map_search_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg20_gameglobal/map_search.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg20-gameglobal/00e5c780.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg20-gameglobal/map_search.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg20-gameglobal/map_search.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg20-gameglobal/ma
[TRUNCATED]
```
