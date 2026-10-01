# Reconstruction context 0x00b3d400

- Status: `partial`
- Content SHA-256: `2a614739944f26c1605f5d6f48c7ee1a1d9acbcb6578bee37fbf23b3a5a5d863`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00b3d400",
  "phase": "reconstruction",
  "target": "0x00b3d400"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueCanonicalNounManager",
  "name": "FUN_00b3d400",
  "package": "PKG-01-SHARED-STATE-ROOTS",
  "subsystem": "Simulator.NounRoot",
  "va": "0x00b3d400"
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
  "content_sha256": "8fcbcd4fa56c90c48c3e70960f6179c42e73e323f66306bb4b97487eb1a1405a",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00b3d400 failed: Decompilation did not complete. Reason: ",
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
  "return_type": "OpaqueCanonicalNounManager*",
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
      "va": "0x00ae9f50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aebe90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b32aa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b32c60"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b32dd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b32f60"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b330e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b33350"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b335d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b33970"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b6f650"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b6f760"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b6f820"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ccec20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cd3610"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cd3bf0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00aea0e4",
      "direction": "in",
      "other": "0x00ae9f50",
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
    "global:0x0167eb60"
  ],
  "types": [
    "OpaqueCanonicalNounManager",
    "OpaqueCanonicalNounManager*"
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
      "No runtime trace establishes value equality with DAT_0167eae0 across the lifecycle; physical separation does not establish inequality of values.",
      "No runtime trace establishes when DAT_0167eb60 is published, replaced, invalidated, cleared, or unpublished.",
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
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae9f50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aebe90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b32aa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b32c60"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b32dd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b32f60"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b330e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b33350"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b335d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b33970"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b6f650"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b6f760"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b6f820"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ccec20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cd3610"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cd3bf0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ce8ee0"
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
    "reconstruction/metadata/pkg01-roots/00b3d400.json"
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
    },
    {
      "anchors": [
        "0x00b3d350",
        "0x00b3d400",
        "0x00b3d350",
        "0x00b3d350",
        "0x01485550"
      ],
      "conflict_id": "TB-VT-008",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": {
        "merge_decision": "separate_entities",
        "preferred_claim": null,
        "preserved_alternatives": true,
        "scope_note": "The interface and object layout are supported; the concrete vtable address is unresolved.",
        "status": "unresolved",
        "taxonomy": "unresolved"
      },
      "resolution_status": "unresolved",
      "source": "knowledge
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-pkg01-roots/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg01-roots/00b3d400.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg01_roots/canonical_roots.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg01_roots/canonical_roots.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg01_roots/canonical_roots_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg01-roots/00b3d400.json",
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
