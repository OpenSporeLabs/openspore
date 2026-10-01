# Reconstruction context 0x00ba9370

- Status: `partial`
- Content SHA-256: `d9a4c6e72c125c433a3c2de6bf908b957d2c5b4fd11d989b979f314e7379c35b`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00ba9370",
  "phase": "reconstruction",
  "target": "0x00ba9370"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueStarManager",
  "name": "FUN_00ba9370",
  "package": "PKG-11-SIM-CORE",
  "subsystem": "Simulator.EmpireRegistry",
  "va": "0x00ba9370"
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
  "content_sha256": "83d7bbaf683d3c0c6a6d00b7554dda6dd54c9bd2803ae89cac24cd2c29dda970",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00ba9370 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "__thiscall observed; ECX receiver and one caller-cleaned stack word",
  "receiver": {
    "register": "ECX",
    "type": "OpaqueStarManager*",
    "width_bytes": 4
  },
  "return_register": "EAX",
  "return_semantics": "Borrowed map payload pointer only when the guarded-hybrid dependent helper returns a non-anchor candidate whose final retained key exactly matches the request; zero on the anchor, invalid request, null payload, or a present key shadowed by a greater right-side candidate.",
  "return_width_bytes": 4,
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "observed_use": "Political ID request; 0xffffffff is rejected before receiver dereference.",
      "position": 1,
      "type": "TargetWord",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 4
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
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
      "va": "0x00ae9040"
    },
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
      "name": null,
      "reconstructed": false,
      "va": "0x00aecf90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aed2c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b20790"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b677e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b6baf0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b6cc50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b96d40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba0080"
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
      "callsite": "0x00
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [
    "global:0x0167eae4"
  ],
  "types": [
    "EmpireMapEntry",
    "OpaqueStarManager",
    "OpaqueStarManager*",
    "OrderedMapEntry",
    "TargetWord"
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
      "gate-star-manager-and-empire-map-lifecycle"
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
  "callees": [
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
      "va": "0x00ae9040"
    },
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
      "name": null,
      "reconstructed": false,
      "va": "0x00aecf90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aed2c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b20790"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b677e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b6baf0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b6cc50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b96d40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba0080"
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
      "name": 
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
      "shared_types:OpaqueStarManager,OpaqueStarManager*,TargetWord"
    ],
    "package": "PKG-14-A2-WORLD-LIFECYCLE-WAVE2",
    "score": 14,
    "symbol": "star_regenerate_00bb4af0",
    "va": "0x00bb4af0"
  },
  {
    "match_basis": [
      "same_package",
      "shared_types:OrderedMapEntry"
    ],
    "package": "PKG-11-SIM-CORE",
    "score": 11,
    "symbol": "pkg11_sim_core_00b21340",
    "va": "0x00b21340"
  },
  {
    "match_basis": [
      "same_class",
      "shared_types:OpaqueStarManager,OpaqueStarManager*"
    ],
    "package": "PKG-14-A2-WORLD-LIFECYCLE-WAVE2",
    "score": 11,
    "symbol": "star_manager_record_to_planet_00bb5b50",
    "va": "0x00bb5b50"
  },
  {
    "match_basis": [
      "shared_types:OrderedMapEntry,TargetWord",
      "direct_xref_neighbor"
    ],
    "package": "PKG-20-GAMEGLOBAL",
    "score": 9,
    "symbol": "map_int_whatever_find",
    "va": "0x00e5c780"
  },
  {
    "match_basis": [
      "same_class",
      "shared_types:OpaqueStarManager"
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
    "package": "PKG-11-SIM-CORE",
    "score": 8,
    "symbol": "Simulator_IsNotStarOrBinaryStar",
    "va": "0x00c8b6b0"
  },
  {
    "match_basis": [
      "shared_types:OrderedMapEntry,TargetWord"
    ],
    "package": "PKG-20-GAMEGLOBAL",
    "score": 6,
    "symbol": "pkg20_gameglobal_00ba83a0",
    "va": "0x00ba83a0"
  },
  {
    "match_basis": [
      "shared_types:Or
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg11_sim_core/empire_lookup.cpp",
  "files": [
    "reconstruction/staging/pkg11-sim-core/empire_lookup.cpp",
    "reconstruction/staging/pkg11-sim-core/empire_lookup.hpp",
    "reconstruction/staging/pkg11-sim-core/empire_lookup_model_test.cpp",
    "src/reconstruction/pkg11_sim_core/empire_lookup.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-source-wave2/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg11-sim-core/00ba9370.json"
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
        "0x00ba9370",
        "0x000000a0",
        "0x00000064",
        "0x00000084"
      ],
      "conflict_id": "TB-FL-004",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": {
        "merge_decision": "do_not_collapse",
        "preferred_claim": null,
        "preserved_alternatives": true,
        "scope_note": "The later matching offsets are not sufficient to validate the earlier alternatives.",
        "status": "preserved_alternatives",
        "taxonomy": "preserved_alternatives"
      },
      "resolution_status": "preserved_alternatives",
      "source": "knowledgegraph/research/conflicts/track-b-vtable-fields.json",
      "subject": "cStarManager selected field-offset maps",
      "unresolved_reason": "The cited static evidence leaves the competing owner, slot, layout, or lifecycle interpretation unresolved; no positive original runtime or MSVC RTTI evidence is available."
    }
  ],
  "unresolved_questions": [
    "Can the alternate manager be null while a non-invalid current-player ID is present?",
    "Does every map entry's key remain synchronized with the payload's cEmpire identity at +0x84?",
    "Is the alternate root value-equal to the canonical star-manager slot for the full lifecycle?",
    "The imported Ghidra cEmpire field label at +0x84 is not treated as authoritative for this wrapper.",
    "What are the ownership and teardown rules for the borrowed empire pointer?",
    "What code publishes, replaces, or clears the alternate star root at 0x0167eae4?",
    "alternate star root
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-source-wave2/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg11-sim-core/00ba9370.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg11-sim-core/empire_lookup.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg11-sim-core/empire_lookup.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg11-sim-core/empire_lookup_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg11_sim_core/empire_lookup.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg11-sim-core/00ba9370.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg11-sim-core/empire_lookup.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg11-sim-core/empire_lookup.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg11-sim-core/empi
[TRUNCATED]
```
