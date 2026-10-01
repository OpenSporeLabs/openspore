# Reconstruction context 0x00de9fc0

- Status: `partial`
- Content SHA-256: `7633b3ad8dfc8a5e7158e50e292eb486e2cd38d2a41fd46cd26fde371173326e`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00de9fc0",
  "phase": "reconstruction",
  "target": "0x00de9fc0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "InventoryEntryContext",
  "name": "pkg12_space_00de9fc0",
  "package": "PKG-12-SIM-SPACE",
  "subsystem": "Simulator.SpaceInventory",
  "va": "0x00de9fc0"
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
  "content_sha256": "7098e37377db20f239f9f8ab5c7a985bd6965006c312db180014dd4657a138b9",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00de9fc0 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "fastcall-style method; Ghidra reports unknown convention",
  "return_observation": "The function returns after the final guarded cleanup/free sequence and has no value return.",
  "return_type": "void",
  "stack_arguments": [],
  "stack_cleanup_bytes": 0
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
      "name": null,
      "reconstructed": false,
      "va": "0x00dea200"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00dea27f",
      "direction": "in",
      "other": "0x00dea200",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00dea026",
      "direction": "out",
      "other": "0x004e39a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00dea08d",
      "direction": "out",
      "other": "0x004e39a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00dea0f1",
      "direction": "out",
      "other": "0x004e39a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00dea1da",
      "direction": "out",
      "other": "0x004e39a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00dea013",
      "direction": "out",
      "other": "0x004e39d0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00dea07a",
      "direction": "out",
      "other": "0x004e39d0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00dea0de",
      "direction": "out",
      "other": "0x004e39d0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00de9fe9",
      "direction": "out",
      "other": "0x00558960",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00dea050",
      "direction": "out",
      "other": "0x00558960",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00dea0b4",
      "direction": "out",
      "other":
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [
    "global:0x015fcc74"
  ],
  "types": [
    "/Spore/App/IGameModeManager",
    "/Spore/GalaxyGameEntry/GlobalGGEUI",
    "/Spore/Simulator/cGameBehaviorManager",
    "/Spore/Simulator/cGameModeManager",
    "AllocationService",
    "BehaviorCleanupService",
    "EntryIndex",
    "GameEntryDescriptor",
    "GameEntryRange",
    "GameModeService",
    "InventoryEntryContext",
    "InventoryEntryServices",
    "PropertyRecord",
    "PropertyRecordBuffer",
    "PropertyRecordService",
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
  "original_bytes": 7081,
  "preview": "{\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"gate-space-inventory-entry\"\n    ],\n    \"validated\": 0\n  },\n  \"semantic\": {\n    \"category\": \"GAMEPLAY_LOGIC\",\n    \"classification\": \"STRUCTURAL_ONLY\",\n    \"confidence\": {\n      \"mechanics\": 0.98\n    },\n    \"contradictions\": [],\n    \"downstream_unlock_count\": 10,\n    \"evidence\": [\n      {\n        \"kind\": \"targeted_decompilation_and_disassembly\",\n        \"observation\": \"Three constant-backed 0x24 temporaries, 0x0c descriptor stride, receiver+0x38/+0x3c comparison, FUN_00de9600, FUN_00de7010, cleanup.\",\n        \"source\": \"ghidra://SporeApp.exe@0x00de9fc0\"\n      },\n      {\n        \"kind\": \"callee_decompilation\",\n        \"observation\": \"Allocates Simulator/GGE state, sets a property parent, and invokes IGameModeManager Initialize.\",\n        \"source\": \"ghidra://SporeApp.exe@0x00de9600\"\n      },\n      {\n        \"kind\": \"callee_decompilation\",\n        \"observation\": \"Traverses game behavior manager state and conditionally performs a bounded post-pass.\",\n        \"source\": \"ghidra://SporeApp.exe@0x00de7010\"\n      },\n      {\n        \"kind\": \"caller_comparison\",\n        \"observation\": \"Calls 00de9fc0 before a sequence of InitGraphics calls and later receiver virtual operations.\",\n        \"source\": \"ghidra://SporeApp.exe@0x00dea200\"\n      },\n      {\n        \"kind\": \"structure_layout\",\n        \"observation\": \"The imported type supplies +0x38 and +0x3c fields 
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
      "name": null,
      "reconstructed": false,
      "va": "0x00dea200"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00dea27f",
      "direction": "in",
      "other": "0x00dea200",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00dea026",
      "direction": "out",
      "other": "0x004e39a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00dea08d",
      "direction": "out",
      "other": "0x004e39a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00dea0f1",
      "direction": "out",
      "other": "0x004e39a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00dea1da",
      "direction": "out",
      "other": "0x004e39a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00dea013",
      "direction": "out",
      "other": "0x004e39d0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00dea07a",
      "direction": "out",
      "other": "0x004e39d0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00dea0de",
      "direction": "out",
      "other": "0x004e39d0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00de9fe9",
      "direction": "out",
      "other": "0x00558960",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00dea050",
      "direction": "out",
      "other": "0x00558960",
      "reference_type": "direct-call"

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
      "same_subsystem"
    ],
    "package": "PKG-12-SIM-SPACE",
    "score": 14,
    "symbol": "cSpaceInventoryItem_ctor_00c877f0",
    "va": "0x00c877f0"
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
    "symbol": "pkg12_space_01021300",
    "va": "0x01021300"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "PKG-12-SIM-SPACE",
    "score": 8,
    "symbol": "FUN_0102d1b0",
    "va": "0x0102d1b0"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg12_space/space_inventory_entry.cpp",
  "files": [
    "reconstruction/staging/pkg12-space/space_inventory_entry.cpp",
    "reconstruction/staging/pkg12-space/space_inventory_entry.hpp",
    "reconstruction/staging/pkg12-space/space_inventory_entry_model_test.cpp",
    "src/reconstruction/pkg12_space/space_inventory_entry.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-source-wave3/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg12-space/00de9fc0.json"
  ]
}
```

## 13_semantic_hypotheses

- State: `present`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

```json
{
  "original_bytes": 6636,
  "preview": "{\n  \"category\": \"GAMEPLAY_LOGIC\",\n  \"classification\": \"STRUCTURAL_ONLY\",\n  \"confidence\": {\n    \"mechanics\": 0.98\n  },\n  \"contradictions\": [],\n  \"downstream_unlock_count\": 10,\n  \"evidence\": [\n    {\n      \"kind\": \"targeted_decompilation_and_disassembly\",\n      \"observation\": \"Three constant-backed 0x24 temporaries, 0x0c descriptor stride, receiver+0x38/+0x3c comparison, FUN_00de9600, FUN_00de7010, cleanup.\",\n      \"source\": \"ghidra://SporeApp.exe@0x00de9fc0\"\n    },\n    {\n      \"kind\": \"callee_decompilation\",\n      \"observation\": \"Allocates Simulator/GGE state, sets a property parent, and invokes IGameModeManager Initialize.\",\n      \"source\": \"ghidra://SporeApp.exe@0x00de9600\"\n    },\n    {\n      \"kind\": \"callee_decompilation\",\n      \"observation\": \"Traverses game behavior manager state and conditionally performs a bounded post-pass.\",\n      \"source\": \"ghidra://SporeApp.exe@0x00de7010\"\n    },\n    {\n      \"kind\": \"caller_comparison\",\n      \"observation\": \"Calls 00de9fc0 before a sequence of InitGraphics calls and later receiver virtual operations.\",\n      \"source\": \"ghidra://SporeApp.exe@0x00dea200\"\n    },\n    {\n      \"kind\": \"structure_layout\",\n      \"observation\": \"The imported type supplies +0x38 and +0x3c fields but not enough type identity to prove the SDK entry.\",\n      \"source\": \"ghidra://SporeApp.exe@structure:GlobalGGEUI\"\n    }\n  ],\n  \"family\": \"galaxy_game_entry_ui_bootstrap\",\n  \"interfaces\": {\n    \"boundari
[TRUNCATED]
```

## 14_conflicts_questions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json, knowledgegraph/research/semantic-decomp.json`

```json
{
  "conflicts": [],
  "unresolved_questions": [
    "Galaxy/game-entry service owner",
    "The behavior/cache list at context+0x40 and the secondary record range ownership remain opaque.",
    "The concrete Galaxy/game-entry service owner type and the vtable +0x38 return contract are not named by Ghidra.",
    "The game-mode initialization and behavior cleanup services are separate dependencies; no event lifecycle is inferred here.",
    "The live body has no explicit null or reversed-range guard; the staging descriptor_count guard is a model safety boundary and not a recovered source branch.",
    "The three descriptor words and their relationship to Galaxy coordinates, game IDs, and game-mode selection remain unknown.",
    "The three property records' opaque words and the exact ownership of their allocated buffers are not closed by this body.",
    "What concrete 0x0c descriptor type is returned by the service, and what do its three dwords mean?",
    "What concrete ordered-map/container type occupies receiver+0x38, and why is only the receiver+0x3c result acted upon?",
    "What state does FUN_00de7010 observe after the matching game-mode initialization?",
    "Which UI/game-mode side effects are required for a replacement, and which are SDK-only compatibility behavior?",
    "Which service is returned by FUN_0067cb40, and what is the true GlobalGGEUI::Initialize entry?",
    "behavior/cache ownership",
    "descriptor word semantics",
    "gate-space-inventory-entry",
    "property record allocator ownership"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-source-wave3/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg12-space/00de9fc0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg12-space/space_inventory_entry.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg12-space/space_inventory_entry.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg12-space/space_inventory_entry_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg12_space/space_inventory_entry.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg12-space/00de9fc0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg12-space/space_inventory_entry.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg12-space/space_inventory_entry.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg12-space/
[TRUNCATED]
```
