# Reconstruction context 0x00b3d4d0

- Status: `partial`
- Content SHA-256: `0b1d32fe0351494c86a2e289890fb0b2d67080a9ab3020b49a99afb2fa0114ec`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00b3d4d0",
  "phase": "reconstruction",
  "target": "0x00b3d4d0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueSpaceTradingService",
  "name": "Simulator_cSpaceTrading_Get",
  "package": "PKG-01-SHARED-STATE-ROOTS",
  "subsystem": "Simulator.SpaceTrading",
  "va": "0x00b3d4d0"
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
  "content_sha256": "2c93b93ed5d0e0829c53f03f20d3affafec9f26000430ee61dea53e6e140504f",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00b3d4d0 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "__cdecl",
  "return_register": "EAX",
  "return_type": "OpaqueSpaceTradingService*",
  "return_width_bytes": 4,
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
      "va": "0x00ace5a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ad2650"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ad2ae0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ad6f40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae3b30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae6240"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae9f50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b19290"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b5e9a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b69990"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b69aa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b6dbd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b7b070"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b998a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bd7e40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bd9060"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00ace842",
      "direction": "in",
      "other": "0x00ace5a0",
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
    "global:0x0167eb50"
  ],
  "types": [
    "OpaqueSpaceTradingService",
    "OpaqueSpaceTradingService*"
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
      "No runtime trace establishes value equality with another root or service slot; physical separation does not establish inequality of values.",
      "No runtime trace establishes when DAT_0167eb50 is published, replaced, invalidated, cleared, or unpublished.",
      "The borrowed return has no accessor-side generation, liveness, or teardown guarantee.",
      "This getter does not validate or implement trading operations; trade requests, offers, acceptance, inventory, commodity, and economy boundaries remain unvalidated.",
      "gate-space-trading-lifecycle"
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
      "va": "0x00ace5a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ad2650"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ad2ae0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ad6f40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae3b30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae6240"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae9f50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b19290"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b5e9a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b69990"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b69aa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b6dbd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b7b070"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b998a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bd7e40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bd9060"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be88d0"
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
      "same_package",
      "same_calling_convention"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 10,
    "symbol": "FUN_00b3d3a0",
    "va": "0x00b3d3a0"
  },
  {
    "match_basis": [
      "same_package",
      "same_calling_convention"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 10,
    "symbol": "FUN_00b3d400",
    "va": "0x00b3d400"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 8,
    "symbol": "FUN_00b3d2a0",
    "va": "0x00b3d2a0"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 8,
    "symbol": "FUN_00b3d300",
    "va": "0x00b3d300"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 8,
    "symbol": "Simulator_GetUIMissionLogManager",
    "va": "0x00b3d4f0"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 8,
    "symbol": "FUN_00ff3f00",
    "va": "0x00ff3f00"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 8,
    "symbol": "FUN_01021080",
    "va": "0x01021080"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 8,
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
  "file": "src/reconstruction/pkg01_roots/canonical_roots.cpp",
  "files": [
    "src/reconstruction/pkg01_roots/canonical_roots.cpp",
    "src/reconstruction/pkg01_roots/canonical_roots.hpp",
    "src/reconstruction/pkg01_roots/canonical_roots_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-pkg01-roots/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg01-roots/00b3d4d0.json"
  ]
}
```

## 13_semantic_hypotheses

- State: `missing`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

## 14_conflicts_questions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json, knowledgegraph/research/semantic-decomp.json`

```json
{
  "conflicts": [],
  "unresolved_questions": [
    "Is this service pointer ever equal to another root or service slot during a lifecycle?",
    "No runtime trace establishes value equality with another root or service slot; physical separation does not establish inequality of values.",
    "No runtime trace establishes when DAT_0167eb50 is published, replaced, invalidated, cleared, or unpublished.",
    "The borrowed return has no accessor-side generation, liveness, or teardown guarantee.",
    "This getter does not validate or implement trading operations; trade requests, offers, acceptance, inventory, commodity, and economy boundaries remain unvalidated.",
    "What code publishes, replaces, or clears DAT_0167eb50?",
    "What concrete service object, vtable, owner, and lifetime does the returned pointer represent?",
    "Which trading operations, state transitions, failure paths, and atomicity boundaries belong to cSpaceTrading?",
    "concrete vtable",
    "gate-space-trading-lifecycle",
    "publisher",
    "replacement order",
    "service owner",
    "trade operation boundaries"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-pkg01-roots/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg01-roots/00b3d4d0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg01_roots/canonical_roots.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg01_roots/canonical_roots.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg01_roots/canonical_roots_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/integrated/batch-2026-09-25-pkg01-roots/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg01-roots/00b3d4d0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg01_roots/canonical_roots.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg01_roots/canonical_roots.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg01_roots/canonical_roots_model_tes
[TRUNCATED]
```
