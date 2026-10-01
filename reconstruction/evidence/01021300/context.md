# Reconstruction context 0x01021300

- Status: `partial`
- Content SHA-256: `1077752b910b73be2a163d75e78a680a4fcf9873147372c0361eb3a6f210f572`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x01021300",
  "phase": "reconstruction",
  "target": "0x01021300"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "SpacePlayerCache",
  "name": "FUN_01021300",
  "package": "PKG-12-SIM-SPACE",
  "subsystem": "Simulator.SpacePlayerState",
  "va": "0x01021300"
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
  "content_sha256": "03cee8d99e5780867ab568da4ec294c147eb6f2c7382ffb6c8bca599bb5c7df4",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x01021300 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "cdecl-compatible no-argument accessor",
  "return_note": "cEmpire* as a borrowed 32-bit pointer word",
  "return_observation": "The return is the cached pointer at sSpacePlayerData+0x1c, or zero when the empire key is 0xffffffff. No return-path AddRef is present.",
  "return_register": "EAX",
  "stack_arguments": [],
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
      "name": "FUN_00b3d2a0",
      "reconstructed": true,
      "va": "0x00b3d2a0"
    },
    {
      "name": "Simulator_LookupEmpireByPoliticalId",
      "reconstructed": true,
      "va": "0x00ba9370"
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae9590"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae9930"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae9f50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aeb3e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aebe90"
    },
    {
      "name": "FUN_00b25fb0",
      "reconstructed": false,
      "va": "0x00b25fb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b262c0"
    },
    {
      "name": "ProfilePersistenceBoundary_run_candidate_00b28ec0",
      "reconstructed": true,
      "va": "0x00b28ec0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b6d3c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba0080"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba7080"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba7dc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bae130"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb4ba0"
    },
    {
      "name": null,
      "reconstructed": false,
   
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [
    "global:0x0167eae4",
    "global:0x016dda8c",
    "global:Simulator::sSpacePlayerData at 0x016DDA8C"
  ],
  "types": [
    "/Spore/Simulator/SpacePlayerData",
    "/Spore/Simulator/cEmpire",
    "Empire",
    "EmpireLookup",
    "EmpireTrait",
    "SpacePlayerCache",
    "StagedIdWord",
    "cEmpire* as a borrowed 32-bit pointer word",
    "intrusive_ptr<Simulator::cEmpire>",
    "uint32_t"
  ],
  "vtables": []
}
```

## 09_state_event_relationships

- State: `present`
- Provenance: `knowledgegraph/research/semantic-decomp.json, reconstruction/knowledge/index.json`

```json
{
  "original_bytes": 10582,
  "preview": "{\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"gate-space-player-data-and-empire-lookup\"\n    ],\n    \"validated\": 0\n  },\n  \"semantic\": {\n    \"category\": null,\n    \"classification\": \"STRONG_SEMANTIC\",\n    \"confidence\": {\n      \"mechanics\": 0.99\n    },\n    \"contradictions\": [],\n    \"downstream_unlock_count\": 184,\n    \"evidence\": [\n      {\n        \"independence\": \"same-binary disassembly corroborates decompilation\",\n        \"source\": \"Ghidra SporeApp.exe 0x01021300: 43 instructions; offsets +0x18/+0x1c/+0x84; vtable slots +0x00/+0x04\",\n        \"supports\": \"exact control flow and reference ordering\"\n      },\n      {\n        \"independence\": \"independent same-binary lookup helper\",\n        \"source\": \"Ghidra SporeApp.exe 0x00ba9370\",\n        \"supports\": \"mEmpires lower-bound lookup and end-only failure check\"\n      },\n      {\n        \"independence\": \"independent same-binary lifecycle paths\",\n        \"source\": \"Ghidra SporeApp.exe 0x01021d40, 0x01022460, 0x00bad7a0\",\n        \"supports\": \"cache initialization, player-field teardown, and independent empire-map erase\"\n      },\n      {\n        \"independence\": \"independent same-binary consumer\",\n        \"source\": \"Ghidra SporeApp.exe 0x00b25fb0\",\n        \"supports\": \"current-empire identity to kCivilization bridge\"\n      },\n      {\n        \"independence\": \"independent repository static adjudication\",\n        \"source\": \"knowledgegraph/research/root-closure
[TRUNCATED]
```

## 10_dependencies

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "FUN_00b3d2a0",
      "reconstructed": true,
      "va": "0x00b3d2a0"
    },
    {
      "name": "Simulator_LookupEmpireByPoliticalId",
      "reconstructed": true,
      "va": "0x00ba9370"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae9590"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae9930"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae9f50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aeb3e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aebe90"
    },
    {
      "name": "FUN_00b25fb0",
      "reconstructed": false,
      "va": "0x00b25fb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b262c0"
    },
    {
      "name": "ProfilePersistenceBoundary_run_candidate_00b28ec0",
      "reconstructed": true,
      "va": "0x00b28ec0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b6d3c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba0080"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba7080"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba7dc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bae130"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb4ba0"
    },
    {
      "name": null,
   
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
      "direct_xref_neighbor"
    ],
    "package": "PKG-12-SIM-SPACE",
    "score": 11,
    "symbol": "FUN_0102d1b0",
    "va": "0x0102d1b0"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "PKG-12-SIM-SPACE",
    "score": 8,
    "symbol": "FUN_00aea230",
    "va": "0x00aea230"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "PKG-12-SIM-SPACE",
    "score": 8,
    "symbol": "FUN_00aea250",
    "va": "0x00aea250"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "PKG-12-SIM-SPACE",
    "score": 8,
    "symbol": "FUN_00aea5d0",
    "va": "0x00aea5d0"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "PKG-12-SIM-SPACE",
    "score": 8,
    "symbol": "FUN_00aeb160",
    "va": "0x00aeb160"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "PKG-12-SIM-SPACE",
    "score": 8,
    "symbol": "Simulator_cCommManager_CreateAndDispatchEvent_00aeb720",
    "va": "0x00aeb720"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "PKG-12-SIM-SPACE",
    "score": 8,
    "symbol": "cSpaceInventoryItem_ctor_00c877f0",
    "va": "0x00c877f0"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "PKG-12-SIM-SPACE",
    "score": 8,
    "symbol": "pkg12_space_00de9fc0",
    "va": "0x00de9fc0"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg12_space/space_player_cache.cpp",
  "files": [
    "reconstruction/staging/pkg12-space/space_player_cache.cpp",
    "reconstruction/staging/pkg12-space/space_player_cache.hpp",
    "reconstruction/staging/pkg12-space/space_player_cache_model_test.cpp",
    "src/reconstruction/pkg12_space/space_player_cache.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-source-wave2/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg12-space/01021300.json"
  ]
}
```

## 13_semantic_hypotheses

- State: `present`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

```json
{
  "original_bytes": 9837,
  "preview": "{\n  \"category\": null,\n  \"classification\": \"STRONG_SEMANTIC\",\n  \"confidence\": {\n    \"mechanics\": 0.99\n  },\n  \"contradictions\": [],\n  \"downstream_unlock_count\": 184,\n  \"evidence\": [\n    {\n      \"independence\": \"same-binary disassembly corroborates decompilation\",\n      \"source\": \"Ghidra SporeApp.exe 0x01021300: 43 instructions; offsets +0x18/+0x1c/+0x84; vtable slots +0x00/+0x04\",\n      \"supports\": \"exact control flow and reference ordering\"\n    },\n    {\n      \"independence\": \"independent same-binary lookup helper\",\n      \"source\": \"Ghidra SporeApp.exe 0x00ba9370\",\n      \"supports\": \"mEmpires lower-bound lookup and end-only failure check\"\n    },\n    {\n      \"independence\": \"independent same-binary lifecycle paths\",\n      \"source\": \"Ghidra SporeApp.exe 0x01021d40, 0x01022460, 0x00bad7a0\",\n      \"supports\": \"cache initialization, player-field teardown, and independent empire-map erase\"\n    },\n    {\n      \"independence\": \"independent same-binary consumer\",\n      \"source\": \"Ghidra SporeApp.exe 0x00b25fb0\",\n      \"supports\": \"current-empire identity to kCivilization bridge\"\n    },\n    {\n      \"independence\": \"independent repository static adjudication\",\n      \"source\": \"knowledgegraph/research/root-closure/track-e-empire-chain.md:15-44,55-117,160-186\",\n      \"supports\": \"current-player cEmpire cache purpose, field map, successor behavior, ownership\"\n    },\n    {\n      \"independence\": \"independent repository lifecycle adjudicati
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
        "0x01021300",
        "0x0000001c",
        "0x0000001c",
        "0x01021300"
      ],
      "conflict_id": "TB-LC-005",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": {
        "merge_decision": "do_not_collapse",
        "preferred_claim": null,
        "preserved_alternatives": true,
        "scope_note": "The pointer transition is observed, but destruction versus reference release is not equivalent behavior.",
        "status": "preserved_alternatives",
        "taxonomy": "preserved_alternatives"
      },
      "resolution_status": "preserved_alternatives",
      "source": "knowledgegraph/research/conflicts/track-b-vtable-fields.json",
      "subject": "SpacePlayerData cached empire replacement lifecycle",
      "unresolved_reason": "The cited static evidence leaves the competing owner, slot, layout, or lifecycle interpretation unresolved; no positive original runtime or MSVC RTTI evidence is available."
    },
    {
      "anchors": [
        "0x00b3d2a0",
        "0x00b3d300",
        "0x00b5b800",
        "0x01021300",
        "0x01021300",
        "0x00ad23c0",
        "0x00adbca0",
        "0x00ae73e0",
        "0x00ae9590",
        "0x00ae9930",
        "0x00ae9c90",
        "0x00ae9f50",
        "0x00aeb3e0",
        "0x00aeb3e0",
        "0x00aebe90",
        "0x00b25fb0"
      ],
      "conflict_id": "global_root_identities",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The address/layout alternatives are preserved; no owner or exact binary identity 
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-source-wave2/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg12-space/01021300.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg12-space/space_player_cache.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg12-space/space_player_cache.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg12-space/space_player_cache_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg12_space/space_player_cache.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg12-space/01021300.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg12-space/space_player_cache.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg12-space/space_player_cache.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg12-space/space_
[TRUNCATED]
```
