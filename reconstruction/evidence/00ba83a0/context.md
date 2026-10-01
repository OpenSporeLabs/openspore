# Reconstruction context 0x00ba83a0

- Status: `partial`
- Content SHA-256: `48a2014816667bd3dc8d3008a16df48549cb825cfb728109c8105594e6f63982`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00ba83a0",
  "phase": "reconstruction",
  "target": "0x00ba83a0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OrderedMap",
  "name": "pkg20_gameglobal_00ba83a0",
  "package": "PKG-20-GAMEGLOBAL",
  "subsystem": "GameGlobal.OrderedMap",
  "va": "0x00ba83a0"
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
  "content_sha256": "201c5b7661f9792a4b7eb490275fdb33e2091ae5bd8387d383debe63a5d5c5ac",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00ba83a0 failed: Decompilation did not complete. Reason: ",
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
  "hidden_this_register": "ECX",
  "hidden_this_type": "OrderedMap*",
  "return_type": "void",
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "output",
      "observed_use": "Receives the allocated entry pointer at offset zero.",
      "position": 1,
      "type": "MapInsertResult*",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x08",
      "name": "parent",
      "observed_use": "Forwarded to the red-black insertion helper.",
      "position": 2,
      "type": "OrderedMapEntry*",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x0C",
      "name": "pair",
      "observed_use": "When non-null, supplies the key at +0x00 and value at +0x04.",
      "position": 3,
      "type": "const MapInsertPair*",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x10",
      "name": "insertion_side",
      "observed_use": "Controls the automatic side decision; nonzero forces the helper side-zero path.",
      "position": 4,
      "type": "std::uint8_t",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 16
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
      "name": "pkg20_gameglobal_00ba8420",
      "reconstructed": true,
      "va": "0x00ba8420"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00baa660"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00ba847c",
      "direction": "in",
      "other": "0x00ba8420",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00baa6a6",
      "direction": "in",
      "other": "0x00baa660",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00baa6c0",
      "direction": "in",
      "other": "0x00baa660",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00baa6eb",
      "direction": "in",
      "other": "0x00baa660",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00ba8407",
      "direction": "out",
      "other": "0x009216a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00ba83e1",
      "direction": "out",
      "other": "0x00f473a0",
      "reference_type": "direct-call"
    }
  ],
  "external_callees": []
}
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "MapInsertPair",
    "MapInsertResult",
    "MapInsertResult*",
    "OrderedMap",
    "OrderedMap*",
    "OrderedMapEntry",
    "OrderedMapEntry*",
    "TargetWord",
    "const MapInsertPair*",
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
  "runtime": {
    "blocking_reason": null,
    "gates": [
      "gate-map-insertion"
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
      "name": "pkg20_gameglobal_00ba8420",
      "reconstructed": true,
      "va": "0x00ba8420"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00baa660"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00ba847c",
      "direction": "in",
      "other": "0x00ba8420",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00baa6a6",
      "direction": "in",
      "other": "0x00baa660",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00baa6c0",
      "direction": "in",
      "other": "0x00baa660",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00baa6eb",
      "direction": "in",
      "other": "0x00baa660",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00ba8407",
      "direction": "out",
      "other": "0x009216a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00ba83e1",
      "direction": "out",
      "other": "0x00f473a0",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 2,
  "fan_out": 0,
  "manifest_callees": [
    "0x00f473a0",
    "0x009216a0"
  ],
  "manifest_callers": [
    "0x00ba8420",
    "0x00baa660"
  ],
  "nearby_reconstructed": [
    "0x00ba8420"
  ],
  "scc": {
    "id": "scc-0414",
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
      "same_subsystem",
      "same_class",
      "shared_types:MapInsertPair,MapInsertResult,MapInsertResult*,OrderedMap",
      "same_calling_convention",
      "direct_xref_neighbor"
    ],
    "package": "PKG-20-GAMEGLOBAL",
    "score": 33,
    "symbol": "pkg20_gameglobal_00ba8420",
    "va": "0x00ba8420"
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
    "symbol": "map_int_whatever_find",
    "va": "0x00e5c780"
  },
  {
    "match_basis": [
      "shared_types:OrderedMap,OrderedMapEntry",
      "same_calling_convention"
    ],
    "package": "PKG-11-SIM-CORE",
    "score": 8,
    "symbol": "pkg11_sim_core_00b21340",
    "va": "0x00b21340"
  },
  {
    "match_basis": [
      "shared_types:OrderedMapEntry,TargetWord"
    ],
    "package": "PKG-11-SIM-CORE",
    "score": 6,
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
    "score": 3
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg20_gameglobal/map_insert.cpp",
  "files": [
    "reconstruction/staging/pkg20-gameglobal/map_insert.cpp",
    "reconstruction/staging/pkg20-gameglobal/map_insert.hpp",
    "reconstruction/staging/pkg20-gameglobal/map_insert_model_test.cpp",
    "src/reconstruction/pkg20_gameglobal/map_insert.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-source-wave3/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg20-gameglobal/00ba83a0.json"
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
    "Does insertion_side encode a caller-selected child side or a duplicate/rebalance mode?",
    "Does the red-black helper require any allocator state beyond the shared map allocator word?",
    "What concrete value type occupies the opaque word at node+0x14 across callers?",
    "What does the allocator boundary return on allocation failure, and does it abort before this body can continue?",
    "allocator failure behavior",
    "gate-map-insertion",
    "insertion-side semantics",
    "opaque value word",
    "red-black helper contract"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-source-wave3/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg20-gameglobal/00ba83a0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg20-gameglobal/map_insert.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg20-gameglobal/map_insert.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg20-gameglobal/map_insert_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg20_gameglobal/map_insert.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg20-gameglobal/00ba83a0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg20-gameglobal/map_insert.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg20-gameglobal/map_insert.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg20-gameglobal/ma
[TRUNCATED]
```
