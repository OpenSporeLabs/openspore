# Reconstruction context 0x00b3d480

- Status: `partial`
- Content SHA-256: `7ce5f90bd49ff447283d99e6217cb9f58feabbbac580ddd134879c8993860339`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00b3d480",
  "phase": "reconstruction",
  "target": "0x00b3d480"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueGameTimeManager",
  "name": "game_time_manager_get_00b3d480",
  "package": "PKG-WAVE6-MISC-ENGINE",
  "subsystem": "Simulator.Time",
  "va": "0x00b3d480"
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
  "content_sha256": "684ee707f935d6d27ad04c1af7a40293c06383b617e54817f5df9a17d7efd86e",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00b3d480 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "cdecl-compatible no-argument accessor",
  "hidden_receiver": null,
  "ordinary_stack_argument_slots": 0,
  "ret_form": "RET",
  "return_note": "opaque 32-bit game-time-manager pointer",
  "return_register": "EAX",
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
      "va": "0x00b32b20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b32ce0"
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
      "va": "0x00b33130"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bcd690"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bd7e40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bd7ea0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bd7f30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bd9060"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bdff50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be1150"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be11f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be6f60"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be6f90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be88d0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00b32b56",
      "direction": "in",
      "other": "0x00b32b20",
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
    "global:MOV EAX,[0x0167eb3c]",
    "global:get_xrefs_to(0x0167eb3c); one read xref from this function"
  ],
  "types": [
    "OpaqueGameTimeManager",
    "opaque 32-bit game-time-manager pointer"
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
      "gate-game-time-manager-slot-publication"
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
      "va": "0x00b32b20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b32ce0"
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
      "va": "0x00b33130"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bcd690"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bd7e40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bd7ea0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bd7f30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bd9060"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bdff50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be1150"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be11f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be6f60"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be6f90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be88d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00beb090"
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
    "symbol": "destructible_lifecycle_thunk_00b63980",
    "va": "0x00b63980"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-RUNTIME-SERVICES-WAVE7",
    "score": 2,
    "symbol": "app_cheat_manager_get_0067dde0",
    "va": "0x0067dde0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-RUNTIME-SERVICES-WAVE7",
    "score": 2,
    "symbol": "app_id_generator_get_007c79e0",
    "va": "0x007c79e0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-11-H2-ROOT-ACCESSORS",
    "score": 2,
    "symbol": "root_accessor_00b3d3b0",
    "va": "0x00b3d3b0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-11-H2-ROOT-ACCESSORS",
    "score": 2,
    "symbol": "root_accessor_00b3d3e0",
    "va": "0x00b3d3e0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-11-H2-ROOT-ACCESSORS",
    "score": 2,
    "symbol": "root_accessor_00b3d3f0",
    "va": "0x00b3d3f0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-11-H2-ROOT-ACCESSORS",
    "score": 2,
    "symbol": "root_accessor_00b3d430",
    "va": "0x00b3d430"
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
    "reconstruction/metadata/wave6-misc-engine/00b3d480.json"
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
    }
  ],
  "unresolved_questions": [
    "Do all callers use the same pointer identity or can alternate roots exist?",
    "What clock epoch, units, and ownership guarantees apply to the returned pointer?",
    "What initializes and replaces the slot, and when is it valid?",
    "Which concrete time-manager object is published at 0x0167eb3c?",
    "alternate-root equality",
    "clock units and ownership",
    "concrete game-time manager",
    "gate-game-time-manager-slot-publi
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave6/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave6-misc-engine/00b3d480.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave6-misc-engine/misc_engine.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave6-misc-engine/misc_engine.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave6-misc-engine/misc_engine_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/wave6_misc_engine/misc_engine.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave6-misc-engine/00b3d480.json",
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
