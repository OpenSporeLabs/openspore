# Evidence 0x00b5b8c0

- Evidence state: `PERSISTED`
- Live requested: `True`
- Content SHA-256: `22e51dc2341c77f0d1fd133d19c40dc9ba195ac5b3e897fabd2ec51b66975135`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "ordinary_stack_arguments": [],
  "receiver": "strategy state in ECX",
  "ret_form": "plain RET",
  "return": "void"
}
```

## abi_derived

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: ``

## callees_dependencies

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## callers_dependencies

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## contradictions

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "anchors": [
      "0x00b5b8a0",
      "0x00b5b8c0",
      "0x00b5b8e0",
      "0x00b5b960",
      "0x00b5b960",
      "0x00b1d870",
      "0x00b1d870",
      "0x00b1db60",
      "0x00b1db60",
      "0x00b1dbd0",
      "0x00b1dbd0",
      "0x00b267f0",
      "0x00b267f0",
      "0x00b5b840",
      "0x00b5b840",
      "0x00b5b880"
    ],
    "conflict_id": "game_mode_identifier_domain",
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
      "0x00b1db60",
      "0x00b5b880",
      "0x00b5b8a0",
      "0x00b5b8c0",
      "0x00b5b8e0",
      "0x00b5b960",
      "0x00b1db60",
      "0x00c3ae70",
      "0x00c3dae0",
      "0x01001360",
      "0x01001360",
      "0x01021080",
      "0x01021080",
      "0x01021960",
      "0x01021960",
      "0x01021d40"
    ],
    "conflict_id": "simulator_mode_identifier_mapping",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  }
]
```

## decompilation

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: ``

## disassembly

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: ``

## external_callees

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## function_identity

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "abi": {
    "architecture": "x86-32",
    "calling_convention": "__thiscall",
    "ordinary_stack_arguments": [],
    "receiver": "strategy state in ECX",
    "ret_form": "plain RET",
    "return": "void"
  },
  "analogues": [
    {
      "match_basis": [
        "same_package",
        "same_subsystem",
        "same_class",
        "shared_types:OpaqueGameModeState",
        "same_calling_convention"
      ],
      "package": "PKG-GAME-MODE-WAVE7",
      "score": 24,
      "symbol": "app_mode_activate_by_name_007d8360",
      "va": "0x007d8360"
    },
    {
      "match_basis": [
        "same_package",
        "same_subsystem",
        "same_class",
        "shared_types:OpaqueGameModeState",
        "same_calling_convention"
      ],
      "package": "PKG-GAME-MODE-WAVE7",
      "score": 24,
      "symbol": "app_mode_activate_007d85b0",
      "va": "0x007d85b0"
    },
    {
      "match_basis": [
        "same_package",
        "same_subsystem",
        "same_class",
        "shared_types:OpaqueGameModeState",
        "same_calling_convention"
      ],
      "package": "PKG-GAME-MODE-WAVE7",
      "score": 24,
      "symbol": "app_mode_activate_index_007d8c80",
      "va": "0x007d8c80"
    },
    {
      "match_basis": [
        "same_package",
        "same_subsystem",
        "same_class",
        "shared_types:OpaqueGameModeState",
        "same_calling_convention"
      ],
      "package": "PKG-GAME-MODE-WAVE7",
      "score": 24,
      "symbol": "strategy_request_ready_00b5b840",
      "va": "0x00b5b840"
    },
    {
      "match_basis": [
        "same_package",
        "same_subsystem",
        "same_class",
        "shared_types:OpaqueGameModeState",
        "same_calling_convention"
      ],
      "package": "PKG-GAME-MODE-WAVE7",
      "score": 24,
      "symbol": "strategy_queue_primary_00b5b880",
      "va": "0x00b5b880"
    },
    {
      "match_basis": [
        "same_package",
        "same_subsystem",
        "same_class",
        "shared_types:OpaqueGameModeState",
        "same_calling_convention"
      ],
      "package": "PKG-GAME-MODE-WAVE7",
      "score": 24,
      "symbol": "strategy_queue_secondary_00b5b8a0",
      "va": "0x00b5b8a0"
    },
    {
      "match_basis": [
        "same_package",
        "same_subsystem",
        "same_class",
        "shared_types:OpaqueGameModeState",
        "same_calling_convention"
      ],
      "package": "PKG-GAME-MODE-WAVE7",
      "score": 24,
      "symbol": "strategy_commit_secondary_00b5b8e0",
      "va": "0x00b5b8e0"
    },
    {
      "match_basis": [
        "same_package",
        "same_subsystem",
        "same_class",
        "shared_types:OpaqueGameModeState",
        "same_calling_convention"
      ],
      "package": "PKG-GAME-MODE-WAVE7",
      "score": 24,
      "symbol": "app_simulator_mode_bridge_00b63510",
      "va": "0x00b63510"
    }
  ],
  "audit_evidence_boundary": "Static mechanics and x86-32 ABI reviewed from live Ghidra; runtime values, concrete owners, and unresolved ports remain gated.",
  "audit_findings": [],
  "audit_status": "clean_after_reviewed_repairs",
  "blocked": false,
  "blockers": [],
  "body_status": "integrated",
  "class_type": "OpaqueGameModeState",
  "cluster": null,
  "confidence": 0.7,
  "dependencies": {
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
    "manifest_callers": [],
    "nearby_reconstructed": [],
    "scc": {
      "id": "scc-0394",
      "size": 1
    },
    "vtable_reference_count": 0
  },
  "evidence_level": "SUPPORTED",
  "globals": [],
  "integration_status": "integrated",
  "name": "strategy_commit_primary_00b5b8c0",
  "normalized_symbol": "strategy_commit_primary_00b5b8c0",
  "observed_mechanics": [
    "{}"
  ],
  "ownership": {
    "claimability": "do_not_claim",
    "handoff_packages": [
      "PKG-GAME-MODE-WAVE7"
    ],
    "manifest": {
      "record": null,
      "worker_ownership": null
    },
    "package": "PKG-GAME-MODE-WAVE7",
    "queue_state": null
  },
  "package": "PKG-GAME-MODE-WAVE7",
  "reconstructed": true,
  "review_status": "approved_after_parallel_review",
  "runtime": {
    "blocking_reason": null,
    "gates": [
      "Observe concrete strategy commit reachability and whether sentinel commits occur in the original process; runtime validation is not run."
    ],
    "validated": 0
  },
  "runtime_gated": true,
  "runtime_validated": 0,
  "semantic": null,
  "semantic_status": "static_reconstruction_runtime_gated",
  "services": [],
  "source": {
    "decomp": null,
    "file": "src/reconstruction/pkg_game_mode_wave7/game_mode_wave7.cpp",
    "files": [
      "src/reconstruction/pkg_game_mode_wave7/game_mode_wave7.cpp"
    ],
    "handoffs": [
      "reconstruction/integrated/batch-2026-09-25-wave7/handoff.json"
    ],
    "metadata": [
      "reconstruction/metadata/pkg-game-mode-wave7/00b5b8c0.json"
    ],
    "provenance": [
      "ghidra:decompile_function",
      "ghidra:disassemble_function",
      "ghidra:get_function_callees",
      "ghidra:get_function_callers",
      "reconstruction/metadata/pkg-game-mode-wave7/00b5b8c0.json"
    ]
  },
  "status": "reconstructed",
  "subsystem": "App.GameMode",
  "triage": null,
  "types": [
    "OpaqueGameModeState"
  ],
  "unresolved_questions": [
    "concrete runtime owners and values remain unresolved"
  ],
  "va": "0x00b5b8c0",
  "vtables": [
    "vtable:0x00b5b8c0"
  ]
}
```

## ghidra_function

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: ``

## globals

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg_game_mode_wave7/game_mode_wave7.cpp",
  "files": [
    "src/reconstruction/pkg_game_mode_wave7/game_mode_wave7.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave7/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-game-mode-wave7/00b5b8c0.json"
  ]
}
```

## runtime

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## runtime_metadata

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "blocking_reason": null,
  "gates": [
    "Observe concrete strategy commit reachability and whether sentinel commits occur in the original process; runtime validation is not run."
  ],
  "validated": 0
}
```

## semantic_hypotheses

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

## status

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "runtime_gated": true,
  "runtime_validated": 0,
  "status": "reconstructed"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "OpaqueGameModeState"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x00b5b8c0"
]
```

## Conflicts

```json
[
  {
    "anchors": [
      "0x00b5b8a0",
      "0x00b5b8c0",
      "0x00b5b8e0",
      "0x00b5b960",
      "0x00b5b960",
      "0x00b1d870",
      "0x00b1d870",
      "0x00b1db60",
      "0x00b1db60",
      "0x00b1dbd0",
      "0x00b1dbd0",
      "0x00b267f0",
      "0x00b267f0",
      "0x00b5b840",
      "0x00b5b840",
      "0x00b5b880"
    ],
    "conflict_id": "game_mode_identifier_domain",
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
      "0x00b1db60",
      "0x00b5b880",
      "0x00b5b8a0",
      "0x00b5b8c0",
      "0x00b5b8e0",
      "0x00b5b960",
      "0x00b1db60",
      "0x00c3ae70",
      "0x00c3dae0",
      "0x01001360",
      "0x01001360",
      "0x01021080",
      "0x01021080",
      "0x01021960",
      "0x01021960",
      "0x01021d40"
    ],
    "conflict_id": "simulator_mode_identifier_mapping",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  }
]
```
