# Reconstruction context 0x00b63980

- Status: `partial`
- Content SHA-256: `e6a003f47846d1df88340c0280a4e1b8f5b2c53f9d5186e0219f904b29315e8e`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00b63980",
  "phase": "reconstruction",
  "target": "0x00b63980"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueDestructible",
  "name": "destructible_lifecycle_thunk_00b63980",
  "package": "PKG-WAVE6-MISC-ENGINE",
  "subsystem": "Core.Lifecycle",
  "va": "0x00b63980"
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
  "content_sha256": "0b5eb717d5e43482f006c21d081e7db8c1d7065b06d0355137094ec9c7491d42",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00b63980 failed: Decompilation did not complete. Reason: ",
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
  "architecture": "x86-32",
  "calling_convention": "thiscall with one hidden ECX receiver and one ordinary stack word",
  "hidden_receiver": "ECX points to the destructible object",
  "ordinary_stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "role": "MSVC scalar deleting-destructor flag",
      "type": "uint32_t",
      "width_bytes": 4
    }
  ],
  "ret_form": "RET 0x4",
  "return_note": "opaque receiver pointer",
  "return_register": "EAX",
  "return_width_bytes": 4,
  "stack_cleanup_bytes": 4
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [],
  "callers": [],
  "edge_rows": [
    {
      "callsite": "0x00b63989",
      "direction": "out",
      "other": "0x005725a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00b63996",
      "direction": "out",
      "other": "0x00f47380",
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
    "DeletingDestructorPorts",
    "OpaqueDestructible",
    "opaque receiver pointer",
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
  "runtime": {
    "blocking_reason": null,
    "gates": [
      "gate-deleting-destructor-vtable-and-global-delete"
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
  "edges": [
    {
      "callsite": "0x00b63989",
      "direction": "out",
      "other": "0x005725a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00b63996",
      "direction": "out",
      "other": "0x00f47380",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 0,
  "fan_out": 0,
  "manifest_callees": [
    "0x005725a0",
    "0x00f47380"
  ],
  "manifest_callers": [
    "data_xref_01464450"
  ],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0400",
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
      "same_package"
    ],
    "package": "PKG-WAVE6-MISC-ENGINE",
    "score": 8,
    "symbol": "message_manager_get_queue_0098f4d0",
    "va": "0x0098f4d0"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "PKG-WAVE6-MISC-ENGINE",
    "score": 8,
    "symbol": "game_time_manager_get_00b3d480",
    "va": "0x00b3d480"
  },
  {
    "match_basis": [
      "shared_types:opaque receiver pointer"
    ],
    "package": "PKG-20-PERSISTENCE-BOUNDARY",
    "score": 3,
    "symbol": "ProfilePersistenceBoundary_run_candidate_00b28ec0",
    "va": "0x00b28ec0"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/wave6_misc_engine/misc_engine.cpp",
  "files": [
    "reconstruction/staging/wave6-misc-engine/misc_engine.cpp",
    "reconstruction/staging/wave6-misc-engine/misc_engine.hpp",
    "reconstruction/staging/wave6-misc-engine/misc_engine_model_test.cpp",
    "src/reconstruction/wave6_misc_engine/misc_engine.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/wave6-misc-engine/00b63980.json"
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
        "0x00b3d480",
        "0x00b3d480",
        "0x00b31da0",
        "0x00b321e0",
        "0x005c7d00",
        "0x005c7cb0",
        "0x005c7f10",
        "0x005c7f70",
        "0x00b32330",
        "0x00b32560",
        "0x00b63980",
        "0x00b32390",
        "0x00b32330",
        "0x00b32560",
        "0x00e63560",
        "0x005c7d00"
      ],
      "conflict_id": "unresolved:knowledgegraph/research/state-machines/additional-domains.json:2",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
      "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
      "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
      "subject": null,
      "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
    },
    {
      "anchors": [
        "0x00587270",
        "0x0059d840",
        "0x0059d8b0",
        "0x00587270",
        "0x0059d8b0",
        "0x0059d840",
        "0x0067cae0",
        "0x00b31da0",
        "0x0059ca70",
        "0x0059cac0",
        "0x00b321e0",
        "0x00b32330",
        "0x00b32560",
        "0x0059cea0",
        "0x0059cf00",
        "0x00b63980"
      ],
      "conflict_id": "unresolved:knowledgegraph/research/state-machines/additional-domains.j
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave6/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave6-misc-engine/00b63980.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave6-misc-engine/misc_engine.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave6-misc-engine/misc_engine.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave6-misc-engine/misc_engine_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/wave6_misc_engine/misc_engine.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/integrated/batch-2026-09-25-wave6/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/wave6-misc-engine/00b63980.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave6-misc-engine/misc_engine.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave6-misc-engine/misc_engine.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave6-misc-engine/mis
[TRUNCATED]
```
