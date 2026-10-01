# Reconstruction context 0x0102d1b0

- Status: `partial`
- Content SHA-256: `1a7cfe959fb7d1703709dd5d67992bef03c54768bedd43fc70ea8ec032dcb201`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x0102d1b0",
  "phase": "reconstruction",
  "target": "0x0102d1b0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "None",
  "name": "FUN_0102d1b0",
  "package": "PKG-12-SIM-SPACE",
  "subsystem": "Simulator.Space",
  "va": "0x0102d1b0"
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
  "content_sha256": "805fab7debe8838cde35010688fabd02ce94760054850db9aea736242563cde2",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x0102d1b0 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "cdecl observed; no implicit this parameter",
  "return_observation": "The live function ends through ordinary void RET paths; the staged implementation does not add an implicit this parameter.",
  "return_type": "void",
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "observed_use": "Loaded from the first stack slot and forwarded to helpers; no +0x70 or +0xAC access is attributed to this pointer.",
      "position": 1,
      "type": "Space *",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x08",
      "observed_use": "Loaded into EDI, used as the explicit ECX operand for FUN_00bba990, and accessed at +0x70 and +0xAC.",
      "position": 2,
      "type": "SpaceContext *",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x0C",
      "observed_use": "Loaded into EBP, compared with the result of FUN_0102fa30(4), and used in signed interval and branch selection.",
      "position": 3,
      "type": "std::uint32_t",
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
  "callees": [
    {
      "name": "achievement_progress_update_00676e90",
      "reconstructed": true,
      "va": "0x00676e90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0067dcc0"
    },
    {
      "name": "FUN_00aea230",
      "reconstructed": true,
      "va": "0x00aea230"
    },
    {
      "name": "Simulator_cCommManager_CreateAndDispatchEvent_00aeb720",
      "reconstructed": true,
      "va": "0x00aeb720"
    },
    {
      "name": "FUN_00b3d2a0",
      "reconstructed": true,
      "va": "0x00b3d2a0"
    },
    {
      "name": "FUN_00b3d2c0",
      "reconstructed": false,
      "va": "0x00b3d2c0"
    },
    {
      "name": "Simulator_cSpaceTrading_Get",
      "reconstructed": true,
      "va": "0x00b3d4d0"
    },
    {
      "name": "FUN_00b8dab0",
      "reconstructed": false,
      "va": "0x00b8dab0"
    },
    {
      "name": "Simulator_LookupEmpireByPoliticalId",
      "reconstructed": true,
      "va": "0x00ba9370"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bbaa60"
    },
    {
      "name": "FUN_00c70e00",
      "reconstructed": false,
      "va": "0x00c70e00"
    },
    {
      "name": "context_word_read_00ce6950",
      "reconstructed": true,
      "va": "0x00ce6950"
    },
    {
      "name": "FUN_00e39ab0",
      "reconstructed": false,
      "va": "0x00e39ab0"
    },
    {
      "name": "FUN_01021080",
      "reconstructed": true,
      "va": "0x01021080"
    },
    {
      "name": "FUN_01021090",
      "reconstructed": false,
      "va": "0x01021090"
    },
    {
      "name": "FU
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "None",
    "Opaque",
    "Space",
    "Space *",
    "SpaceContext",
    "SpaceContext *",
    "std::uint32_t",
    "std::uint8_t",
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
  "original_bytes": 10222,
  "preview": "{\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"space_communication_state_observation\"\n    ],\n    \"validated\": 0\n  },\n  \"semantic\": {\n    \"category\": null,\n    \"classification\": \"NEEDS_RUNTIME\",\n    \"confidence\": {\n      \"overall\": 0.87\n    },\n    \"contradictions\": [],\n    \"downstream_unlock_count\": 54,\n    \"evidence\": [\n      {\n        \"finding\": \"Surrender classification, local state updates, achievement call, temporary labels, and final cCommEvent wrapper.\",\n        \"kind\": \"target_decompilation\",\n        \"source\": \"Ghidra 0x0102d1b0\"\n      },\n      {\n        \"finding\": \"Numeric dispatcher calls the target on four selected branches and also creates other local surrender/communication events.\",\n        \"kind\": \"direct_caller_sibling\",\n        \"source\": \"Ghidra 0x0102df20\"\n      },\n      {\n        \"finding\": \"Independent raw key-0x0c/27-slot and key-0x06/24-slot entries under a common owner; no cCommEvent object flow.\",\n        \"kind\": \"anonymous_record_builder\",\n        \"source\": \"Ghidra 0x00e39ab0 and the focused space-pair resolution\"\n      },\n      {\n        \"finding\": \"0xa0 allocation, manager append, refcount-shaped object, and immediate application path.\",\n        \"kind\": \"communication_structure\",\n        \"source\": \"Ghidra 0x00aeb720, 0x00aeb160, 0x00aebe90, and structure:cCommEvent\"\n      },\n      {\n        \"finding\": \"The target is one member of a local surrender/space event family, not
[TRUNCATED]
```

## 10_dependencies

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "achievement_progress_update_00676e90",
      "reconstructed": true,
      "va": "0x00676e90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0067dcc0"
    },
    {
      "name": "FUN_00aea230",
      "reconstructed": true,
      "va": "0x00aea230"
    },
    {
      "name": "Simulator_cCommManager_CreateAndDispatchEvent_00aeb720",
      "reconstructed": true,
      "va": "0x00aeb720"
    },
    {
      "name": "FUN_00b3d2a0",
      "reconstructed": true,
      "va": "0x00b3d2a0"
    },
    {
      "name": "FUN_00b3d2c0",
      "reconstructed": false,
      "va": "0x00b3d2c0"
    },
    {
      "name": "Simulator_cSpaceTrading_Get",
      "reconstructed": true,
      "va": "0x00b3d4d0"
    },
    {
      "name": "FUN_00b8dab0",
      "reconstructed": false,
      "va": "0x00b8dab0"
    },
    {
      "name": "Simulator_LookupEmpireByPoliticalId",
      "reconstructed": true,
      "va": "0x00ba9370"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bbaa60"
    },
    {
      "name": "FUN_00c70e00",
      "reconstructed": false,
      "va": "0x00c70e00"
    },
    {
      "name": "context_word_read_00ce6950",
      "reconstructed": true,
      "va": "0x00ce6950"
    },
    {
      "name": "FUN_00e39ab0",
      "reconstructed": false,
      "va": "0x00e39ab0"
    },
    {
      "name": "FUN_01021080",
      "reconstructed": true,
      "va": "0x01021080"
    },
    {
      "name": "FUN_01021090",
      "reconstructed": false,
      "va": "0x01021090"
    },
    {
      "name": "FU
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
    "symbol": "FUN_00aea230",
    "va": "0x00aea230"
  },
  {
    "match_basis": [
      "same_package",
      "direct_xref_neighbor"
    ],
    "package": "PKG-12-SIM-SPACE",
    "score": 11,
    "symbol": "Simulator_cCommManager_CreateAndDispatchEvent_00aeb720",
    "va": "0x00aeb720"
  },
  {
    "match_basis": [
      "same_package",
      "direct_xref_neighbor"
    ],
    "package": "PKG-12-SIM-SPACE",
    "score": 11,
    "symbol": "pkg12_space_01021300",
    "va": "0x01021300"
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
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg12_space/space_functions.cpp",
  "files": [
    "reconstruction/staging/pkg12-space/space_functions.cpp",
    "reconstruction/staging/pkg12-space/space_functions.hpp",
    "src/reconstruction/pkg12_space/space_functions.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg12-space/0102d1b0.json"
  ]
}
```

## 13_semantic_hypotheses

- State: `present`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

```json
{
  "original_bytes": 9658,
  "preview": "{\n  \"category\": null,\n  \"classification\": \"NEEDS_RUNTIME\",\n  \"confidence\": {\n    \"overall\": 0.87\n  },\n  \"contradictions\": [],\n  \"downstream_unlock_count\": 54,\n  \"evidence\": [\n    {\n      \"finding\": \"Surrender classification, local state updates, achievement call, temporary labels, and final cCommEvent wrapper.\",\n      \"kind\": \"target_decompilation\",\n      \"source\": \"Ghidra 0x0102d1b0\"\n    },\n    {\n      \"finding\": \"Numeric dispatcher calls the target on four selected branches and also creates other local surrender/communication events.\",\n      \"kind\": \"direct_caller_sibling\",\n      \"source\": \"Ghidra 0x0102df20\"\n    },\n    {\n      \"finding\": \"Independent raw key-0x0c/27-slot and key-0x06/24-slot entries under a common owner; no cCommEvent object flow.\",\n      \"kind\": \"anonymous_record_builder\",\n      \"source\": \"Ghidra 0x00e39ab0 and the focused space-pair resolution\"\n    },\n    {\n      \"finding\": \"0xa0 allocation, manager append, refcount-shaped object, and immediate application path.\",\n      \"kind\": \"communication_structure\",\n      \"source\": \"Ghidra 0x00aeb720, 0x00aeb160, 0x00aebe90, and structure:cCommEvent\"\n    },\n    {\n      \"finding\": \"The target is one member of a local surrender/space event family, not a universal event ABI.\",\n      \"kind\": \"state_and_sibling_consumer\",\n      \"source\": \"Ghidra 0x0102df20 and committed event-family artifacts\"\n    },\n    {\n      \"finding\": \"Conditional App/Telemetry encoding is sepa
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
        "0x00aeb160",
        "0x00aebe90",
        "0x00aed2c0",
        "0x00c75520",
        "0x00dd5160",
        "0x0102c9e0",
        "0x0102caa0",
        "0x0102cae0",
        "0x0102cc30",
        "0x0102cd90",
        "0x0102ce30",
        "0x0102cf10",
        "0x0102d1b0",
        "0x0102df20",
        "0x01072d40",
        "0x00aeb730"
      ],
      "conflict_id": "LC-006",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "RESOLVED_SUPPORTED",
      "resolution_status": "RESOLVED_SUPPORTED",
      "source": "knowledgegraph/research/conflicts/track-a-type-signature.json",
      "subject": "0x00AEB720 communication wrapper",
      "unresolved_reason": "The exact private wrapper name and the full parameter types are not recoverable from static naming alone; the create-and-dispatch contract is resolved."
    }
  ],
  "unresolved_questions": [
    "Does any indirect path cross a network service in a mode not covered by the direct call graph?",
    "Does the achievement progress flag persist to a save or remain runtime-only?",
    "What are param_1, param_2, and param_3 semantically?",
    "What exact cCommEvent fields are populated for each surrender branch?",
    "What exact numeric/state values select diplomatic Planet versus Solar surrender?",
    "What is the runtime ordering between the keyed space entry, cCommEvent application, and visible UI changes?",
    "Which raw keyed entry is consumed by the local space state and what is the key-0x06 sidecar's consumer?",
    "achievement side effect
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg12-space/0102d1b0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg12-space/space_functions.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg12-space/space_functions.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg12_space/space_functions.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg12-space/0102d1b0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg12-space/space_functions.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg12-space/space_functions.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg12_space/space_functions.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.json",
    "src/reconstruction/pkg12_space/space_funct
[TRUNCATED]
```
