# Reconstruction context 0x00b28ec0

- Status: `partial`
- Content SHA-256: `dfcd53aa866a06847ac9cf571fdf446d7795312edb29e94c420aed756dcdd3ea`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00b28ec0",
  "phase": "reconstruction",
  "target": "0x00b28ec0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "ProfilePersistenceBoundary",
  "name": "ProfilePersistenceBoundary_run_candidate_00b28ec0",
  "package": "PKG-20-PERSISTENCE-BOUNDARY",
  "subsystem": "PersistenceBoundary.ProfileCandidate",
  "va": "0x00b28ec0"
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
  "content_sha256": "3369fb8027ec0ee8b4b154cd76d0eff0153d80a99e8e52ab503a6692f9252e7d",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00b28ec0 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "__thiscall",
  "hidden_this_register": "ECX",
  "hidden_this_type": "opaque receiver pointer",
  "return_type": "void",
  "stack_arguments": [
    {
      "entry_offset": "ESP+4",
      "name": "wide_path",
      "type": "const char16_t*",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+8",
      "name": "candidate_marker",
      "observed_access_at_gates": "ESP+0x120 after the 0x110-byte entry ESP adjustment",
      "observed_use": "nonzero value gates both the candidate-target and completion sequences",
      "type": "uint32_t",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 8
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "FUN_004df420",
      "reconstructed": false,
      "va": "0x004df420"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0067dcc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00688fa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006891f0"
    },
    {
      "name": "FUN_00b3d230",
      "reconstructed": false,
      "va": "0x00b3d230"
    },
    {
      "name": "FUN_00b3d2a0",
      "reconstructed": true,
      "va": "0x00b3d2a0"
    },
    {
      "name": "FUN_00b3d300",
      "reconstructed": true,
      "va": "0x00b3d300"
    },
    {
      "name": "simulator_game_input_manager_get_00b3d350",
      "reconstructed": true,
      "va": "0x00b3d350"
    },
    {
      "name": "FUN_00b5b800",
      "reconstructed": false,
      "va": "0x00b5b800"
    },
    {
      "name": "member_ptr_0x2c_00b7e380",
      "reconstructed": true,
      "va": "0x00b7e380"
    },
    {
      "name": "FUN_01021080",
      "reconstructed": true,
      "va": "0x01021080"
    },
    {
      "name": "FUN_01021230",
      "reconstructed": true,
      "va": "0x01021230"
    },
    {
      "name": "pkg12_space_01021300",
      "reconstructed": true,
      "va": "0x01021300"
    },
    {
      "name": "FUN_01021370",
      "reconstructed": false,
      "va": "0x01021370"
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b294c0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00b297b4",
      "direction": "in",
      "o
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "ProfilePersistenceBoundary",
    "ProfilePersistenceCandidateServices",
    "ProfilePersistenceRequest",
    "const char16_t*",
    "opaque receiver pointer",
    "uint32_t",
    "void"
  ],
  "vtables": []
}
```

## 09_state_event_relationships

- State: `present`
- Provenance: `knowledgegraph/research/semantic-decomp.json, reconstruction/knowledge/index.json`

```json
{
  "original_bytes": 9418,
  "preview": "{\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"gate-profile-persistence-candidate\"\n    ],\n    \"validated\": 0\n  },\n  \"semantic\": {\n    \"category\": null,\n    \"classification\": \"STRUCTURAL_ONLY\",\n    \"confidence\": {\n      \"events\": \"UNRESOLVED\",\n      \"identity\": \"INFERRED\",\n      \"mechanics\": \"CONFIRMED\",\n      \"overall\": \"high_for_static_mechanics_medium_for_operation_identity\",\n      \"ownership\": \"INFERRED_NOT_CONFIRMED\",\n      \"persistence\": \"SUPPORTED\",\n      \"runtime\": \"UNAVAILABLE\"\n    },\n    \"contradictions\": [],\n    \"downstream_unlock_count\": 43,\n    \"evidence\": [\n      {\n        \"claim\": \"path validation, header-shaped local record, temporary path, serializer/database calls, stream close, replacement, and conditional star database branch\",\n        \"class\": \"direct_body\",\n        \"source\": \"ghidra://SporeApp.exe@0x00b28ec0\"\n      },\n      {\n        \"claim\": \"profile/load wrapper calls the target after path/mode setup; it passes a second context argument\",\n        \"class\": \"direct_caller\",\n        \"source\": \"ghidra://SporeApp.exe@0x00b294c0 at 0x00b297b4\"\n      },\n      {\n        \"claim\": \"matching load path uses the same database/ClassSerializer architecture and closes the read context\",\n        \"class\": \"sibling_body\",\n        \"source\": \"ghidra://SporeApp.exe@0x00b279e0\"\n      },\n      {\n        \"claim\": \"header descriptor setup followed by the common write serializer\",\n   
[TRUNCATED]
```

## 10_dependencies

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "FUN_004df420",
      "reconstructed": false,
      "va": "0x004df420"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0067dcc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00688fa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006891f0"
    },
    {
      "name": "FUN_00b3d230",
      "reconstructed": false,
      "va": "0x00b3d230"
    },
    {
      "name": "FUN_00b3d2a0",
      "reconstructed": true,
      "va": "0x00b3d2a0"
    },
    {
      "name": "FUN_00b3d300",
      "reconstructed": true,
      "va": "0x00b3d300"
    },
    {
      "name": "simulator_game_input_manager_get_00b3d350",
      "reconstructed": true,
      "va": "0x00b3d350"
    },
    {
      "name": "FUN_00b5b800",
      "reconstructed": false,
      "va": "0x00b5b800"
    },
    {
      "name": "member_ptr_0x2c_00b7e380",
      "reconstructed": true,
      "va": "0x00b7e380"
    },
    {
      "name": "FUN_01021080",
      "reconstructed": true,
      "va": "0x01021080"
    },
    {
      "name": "FUN_01021230",
      "reconstructed": true,
      "va": "0x01021230"
    },
    {
      "name": "pkg12_space_01021300",
      "reconstructed": true,
      "va": "0x01021300"
    },
    {
      "name": "FUN_01021370",
      "reconstructed": false,
      "va": "0x01021370"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b294c0"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
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
      "same_calling_convention"
    ],
    "package": "PKG-20-PERSISTENCE-BOUNDARY",
    "score": 10,
    "symbol": "PaintPersistenceBoundary_submit_004c5200",
    "va": "0x004c5200"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 3,
    "symbol": "FUN_00b3d2a0",
    "va": "0x00b3d2a0"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 3,
    "symbol": "FUN_00b3d300",
    "va": "0x00b3d300"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-GAME-INPUT-WAVE7",
    "score": 3,
    "symbol": "simulator_game_input_manager_get_00b3d350",
    "va": "0x00b3d350"
  },
  {
    "match_basis": [
      "shared_types:opaque receiver pointer"
    ],
    "package": "PKG-WAVE6-MISC-ENGINE",
    "score": 3,
    "symbol": "destructible_lifecycle_thunk_00b63980",
    "va": "0x00b63980"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "pkg-00b7e380-member-ptr-0x2c",
    "score": 3,
    "symbol": "member_ptr_0x2c_00b7e380",
    "va": "0x00b7e380"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 3,
    "symbol": "FUN_01021080",
    "va": "0x01021080"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 3,
    "symbol": "FUN_01021230",
    "va": "0x01021230"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg20_persistence_boundary/persistence_boundary.cpp",
  "files": [
    "src/reconstruction/pkg20_persistence_boundary/persistence_boundary.cpp",
    "src/reconstruction/pkg20_persistence_boundary/persistence_boundary.hpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25/editor-ui/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg20-persistence-boundary/00b28ec0.json"
  ]
}
```

## 13_semantic_hypotheses

- State: `present`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

```json
{
  "original_bytes": 8797,
  "preview": "{\n  \"category\": null,\n  \"classification\": \"STRUCTURAL_ONLY\",\n  \"confidence\": {\n    \"events\": \"UNRESOLVED\",\n    \"identity\": \"INFERRED\",\n    \"mechanics\": \"CONFIRMED\",\n    \"overall\": \"high_for_static_mechanics_medium_for_operation_identity\",\n    \"ownership\": \"INFERRED_NOT_CONFIRMED\",\n    \"persistence\": \"SUPPORTED\",\n    \"runtime\": \"UNAVAILABLE\"\n  },\n  \"contradictions\": [],\n  \"downstream_unlock_count\": 43,\n  \"evidence\": [\n    {\n      \"claim\": \"path validation, header-shaped local record, temporary path, serializer/database calls, stream close, replacement, and conditional star database branch\",\n      \"class\": \"direct_body\",\n      \"source\": \"ghidra://SporeApp.exe@0x00b28ec0\"\n    },\n    {\n      \"claim\": \"profile/load wrapper calls the target after path/mode setup; it passes a second context argument\",\n      \"class\": \"direct_caller\",\n      \"source\": \"ghidra://SporeApp.exe@0x00b294c0 at 0x00b297b4\"\n    },\n    {\n      \"claim\": \"matching load path uses the same database/ClassSerializer architecture and closes the read context\",\n      \"class\": \"sibling_body\",\n      \"source\": \"ghidra://SporeApp.exe@0x00b279e0\"\n    },\n    {\n      \"claim\": \"header descriptor setup followed by the common write serializer\",\n      \"class\": \"serializer_wrapper\",\n      \"source\": \"ghidra://SporeApp.exe@0x00b268a0\"\n    },\n    {\n      \"claim\": \"old/temp path construction, move/copy, and removal behavior\",\n      \"class\": \"replacement_sibling
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
        "0x000051e0",
        "0x00e20860",
        "0x00e20860",
        "0x00ad23c0",
        "0x00adbca0",
        "0x00ae73e0",
        "0x00ae9c90",
        "0x00aeb3e0",
        "0x00b28ec0",
        "0x00b33130",
        "0x00b35300",
        "0x00b444c0",
        "0x00b4a720",
        "0x00de4c20",
        "0x00df5ac0",
        "0x01001360"
      ],
      "conflict_id": "cell_update_state_machine",
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
        "0x00b28ec0",
        "0x00b294c0",
        "0x00bb4ba0",
        "0x00bb4ba0",
        "0x00693900",
        "0x00693900",
        "0x00693900",
        "0x00693900",
        "0x00693d60",
        "0x00693d60",
        "0x00693d60",
        "0x00693d60",
        "0x006a1540",
        "0x006a2f60",
        "0x006a1540",
        "0x006a2f60"
      ],
      "conflict_id": "cross_file_atomicity",
      "kind": "conflict_ledger",
      "rejected"
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25/editor-ui/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg20-persistence-boundary/00b28ec0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg20_persistence_boundary/persistence_boundary.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg20_persistence_boundary/persistence_boundary.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/integrated/batch-2026-09-25/editor-ui/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg20-persistence-boundary/00b28ec0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg20_persistence_boundary/persistence_boundary.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg20_persistence_boundary/persistence_boundary.hpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledg
[TRUNCATED]
```
