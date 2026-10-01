# Reconstruction context 0x00b3d3a0

- Status: `partial`
- Content SHA-256: `7fe2faf1d3a3b742c04abeeaf00dec0cd0438d4ee9f844e6a295c0a0e36669b4`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00b3d3a0",
  "phase": "reconstruction",
  "target": "0x00b3d3a0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueCanonicalStarManager",
  "name": "FUN_00b3d3a0",
  "package": "PKG-01-SHARED-STATE-ROOTS",
  "subsystem": "Simulator.StarRoot",
  "va": "0x00b3d3a0"
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
  "content_sha256": "d99303ee74295799dfba477ab135ebe4c56d29eb2933e7eed721b4c69a36a77e",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00b3d3a0 failed: Decompilation did not complete. Reason: ",
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
  "return_type": "OpaqueCanonicalStarManager*",
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
  "callers": [],
  "edge_rows": [],
  "external_callees": []
}
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [
    "global:0x0167eb0c"
  ],
  "types": [
    "OpaqueCanonicalStarManager",
    "OpaqueCanonicalStarManager*"
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
      "No runtime trace establishes value equality with DAT_0167eae4 across the lifecycle; physical separation does not establish inequality of values.",
      "No runtime trace establishes when DAT_0167eb0c is published, replaced, invalidated, cleared, or unpublished.",
      "The borrowed return has no accessor-side generation, liveness, or teardown guarantee.",
      "gate-space-root-publication"
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
  "edges": [],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 0,
  "fan_out": 0,
  "manifest_callees": [],
  "manifest_callers": [
    "caller_xrefs_unrecorded"
  ],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0374",
    "size": 1
  },
  "vtable_reference_count": 0
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
      "same_calling_convention"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 10,
    "symbol": "FUN_00b3d400",
    "va": "0x00b3d400"
  },
  {
    "match_basis": [
      "same_package",
      "same_calling_convention"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 10,
    "symbol": "Simulator_cSpaceTrading_Get",
    "va": "0x00b3d4d0"
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
    "reconstruction/metadata/pkg01-roots/00b3d3a0.json"
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
        "0x00b3d300",
        "0x00b3d400",
        "0x00b3d2a0",
        "0x00b3d3a0",
        "0x00b5b800",
        "0xffffffff",
        "0x00b3d300",
        "0x00b3d2a0",
        "0x00b3d400",
        "0x00b3d3a0",
        "0x00b5b800"
      ],
      "conflict_id": "CF-002",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": null,
      "resolution_status": null,
      "source": "knowledgegraph/research/conflicts/track-f-cross-domain-impact.json",
      "subject": null,
      "unresolved_reason": {
        "missing_evidence": [
          "Direct or indirect publisher and teardown evidence for both alternate/canonical manager slot pairs.",
          "Pointer-equality checks across mode and service lifecycle boundaries.",
          "The concrete receiver class and physical storage type behind DAT_0167eaec and forwarded_object+0x20."
        ],
        "status": "blocked"
      }
    }
  ],
  "unresolved_questions": [
    "Are the canonical and alternate star slot values equal at every live lifecycle point?",
    "Can consumers observe a null or stale returned pointer during a mode transition?",
    "No runtime trace establishes value equality with DAT_0167eae4 across the lifecycle; physical separation does not establish inequality of values.",
    "No runtime trace establishes when DAT_0167eb0c is published, replaced, invalidated, cleared, or unpublished.",
    "The borrowed return has no accessor-side generation, liveness, or teardown guarantee.",
    "What code publishes, replaces, or clears DAT_0167eb
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-pkg01-roots/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg01-roots/00b3d3a0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg01_roots/canonical_roots.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg01_roots/canonical_roots.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg01_roots/canonical_roots_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg01-roots/00b3d3a0.json",
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
