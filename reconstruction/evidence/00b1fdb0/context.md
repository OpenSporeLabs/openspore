# Reconstruction context 0x00b1fdb0

- Status: `partial`
- Content SHA-256: `d731202af7966d32b3a2621866cacef024f0753bee637a1fc3e724d982eca0f7`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00b1fdb0",
  "phase": "reconstruction",
  "target": "0x00b1fdb0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueNounManager",
  "name": "FUN_00b1fdb0",
  "package": "PKG-13-CREATURE-ACCESSOR",
  "subsystem": "Simulator.Creature",
  "va": "0x00b1fdb0"
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
  "content_sha256": "c13d6b2575bf20c09cfea510639b667725cda5212497ffce02944139d698c930",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00b1fdb0 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "thiscall-compatible ECX-only machine ABI",
  "hidden_this": "OpaqueNounManager* receiver in ECX",
  "return_register": "EAX",
  "return_semantics": "Returns the opaque 32-bit receiver field word unchanged; no pointer cast, sign extension, truncation, or ownership operation occurs.",
  "return_width_bytes": 4,
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
      "va": "0x00b0a6f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b19290"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b2dac0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b2e940"
    },
    {
      "name": "timing_update_body_00b31cc0",
      "reconstructed": true,
      "va": "0x00b31cc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b7a880"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b96d40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba1590"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba9f80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb1340"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb2330"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb23e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb24d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb3750"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb4100"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb5640"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00b0a7dd",
      "direction": "in",
      "other": "0x00b0a6f0",
      "reference_type
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "OpaqueNounManager",
    "OpaqueNounManagerField"
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
      "gate-creature-accessor-field"
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
      "va": "0x00b0a6f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b19290"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b2dac0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b2e940"
    },
    {
      "name": "timing_update_body_00b31cc0",
      "reconstructed": true,
      "va": "0x00b31cc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b7a880"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b96d40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba1590"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba9f80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb1340"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb2330"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb23e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb24d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb3750"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb4100"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb5640"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb80f0"
    },
    {
      "nam
[TRUNCATED]
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "same_class",
      "shared_types:OpaqueNounManager"
    ],
    "package": "PKG-11-H3-HELPER-WAVE2",
    "score": 8,
    "symbol": "noun_manager_logical_destroy_00b225d0",
    "va": "0x00b225d0"
  },
  {
    "match_basis": [
      "same_class",
      "shared_types:OpaqueNounManager"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 8,
    "symbol": "FUN_00b3d300",
    "va": "0x00b3d300"
  },
  {
    "match_basis": [
      "shared_types:OpaqueNounManager",
      "direct_xref_neighbor"
    ],
    "package": "PKG-13-SIM-CREATURE-TRIBECIV",
    "score": 6,
    "symbol": "Simulator_cCreatureGameData_GetEvoPointsToNextBrainLevel",
    "va": "0x00d2e380"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-FRAME-RUNTIME-WAVE8",
    "score": 3,
    "symbol": "timing_update_body_00b31cc0",
    "va": "0x00b31cc0"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-13-E4-EMPIRE-WAVE3",
    "score": 3,
    "symbol": "EmpirePoliticalColor_00c32cd0",
    "va": "0x00c32cd0"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-13-E4-EMPIRE-WAVE3",
    "score": 3,
    "symbol": "PoliticalOwnershipScan_00c8d060",
    "va": "0x00c8d060"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-13-C3-CREATURE-PROGRESSION-WAVE2",
    "score": 3,
    "symbol": "Simulator_cCreatureGameData_AddEvolutionPoints_raw_00d2e8a0",
    "va": "0x00d2e8a0"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg13_creature_accessor/b1fdb0_accessor.cpp",
  "files": [
    "reconstruction/staging/pkg13-creature-accessor/b1fdb0_accessor.cpp",
    "reconstruction/staging/pkg13-creature-accessor/b1fdb0_accessor.hpp",
    "reconstruction/staging/pkg13-creature-accessor/b1fdb0_accessor_model_test.cpp",
    "src/reconstruction/pkg13_creature_accessor/b1fdb0_accessor.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-source-wave5/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg13-creature-accessor/00b1fdb0.json"
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
        "0x00845310",
        "0x00b1fdb0",
        "0x00845310",
        "0x00b1fdb0",
        "0x00844f70",
        "0x00841440",
        "0x00846e60",
        "0x00841d40",
        "0x00845790",
        "0x00842d10",
        "0x00844180",
        "0x00843000",
        "0x00845310",
        "0x0067dd90",
        "0x00e66280",
        "0x00e66840"
      ],
      "conflict_id": "unresolved:knowledgegraph/research/state-machines/additional-domains.json:1",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
      "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
      "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
      "subject": null,
      "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
    }
  ],
  "unresolved_questions": [
    "Does every one of the 303 direct callers pass the same concrete noun-manager receiver type?",
    "What concrete object, if any, the opaque +0x54 word represents across all callers.",
    "What values are observed at +0x54 in the original process.",
    "Which owner publishes, replaces, and tears down noun-manager receivers.",
    "concrete noun-manager owner",
    "gate-creature-accessor-field",
    "meaning and ownership of receiver+0
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-source-wave5/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg13-creature-accessor/00b1fdb0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg13-creature-accessor/b1fdb0_accessor.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg13-creature-accessor/b1fdb0_accessor.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg13-creature-accessor/b1fdb0_accessor_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg13_creature_accessor/b1fdb0_accessor.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/integrated/batch-2026-09-25-source-wave5/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg13-creature-accessor/00b1fdb0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg13-creature-accessor/b1fdb0_accessor.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg13-creature-accessor/b1fdb0_accessor.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruct
[TRUNCATED]
```
