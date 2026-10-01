# Evidence 0x00e666f0

- Evidence state: `PERSISTED`
- Live requested: `False`
- Content SHA-256: `d30d5f3bf878ad17000f9f7334a21249a0aad379db40d8df5307ff69574fb7af`

## abi

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## abi_derived

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: ``

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "embedded_object_first_word_init_00743b50",
    "reconstructed": true,
    "va": "0x00743b50"
  },
  {
    "name": "Simulator::Cell::cCellGFX::PreloadCellResource",
    "reconstructed": false,
    "va": "0x00e663b0"
  },
  {
    "name": "Simulator::Cell::cCellGFX::PreloadPopulateResource",
    "reconstructed": false,
    "va": "0x00e665c0"
  }
]
```

## callers_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e819b0"
  }
]
```

## contradictions

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "anchors": [
      "0x00c932f0",
      "0x00b237c0",
      "0x00c983c0",
      "0x00e74a20",
      "0x00e4ce20",
      "0x00e665c0",
      "0x00e666f0",
      "0x00b237c0",
      "0x00c983c0",
      "0x00c932f0"
    ],
    "conflict_id": "U-006-herd-respawn-evolution",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
    "resolution_status": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00c932f0",
      "0x00c983c0",
      "0x00e74a20",
      "0x00e4ce20",
      "0x00e665c0",
      "0x00e666f0",
      "0x00be34a0",
      "0x00bddef0",
      "0x00bdde70",
      "0x00ca6630",
      "0x00ca6630"
    ],
    "conflict_id": "U-007-city-population-vehicle",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
    "resolution_status": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00e7fd00",
      "0x00e74a20",
      "0x00bb42a0",
      "0x00bb4c90",
      "0x00b237c0",
      "0x00e74a20",
      "0x00e74a20",
      "0x00e4ce20",
      "0x00e5b790",
      "0x00e665c0",
      "0x00e666f0",
      "0x00e80ba0",
      "0x00be34a0",
      "0x00bddef0",
      "0x00bdde70",
      "0x00bb5b50"
    ],
    "conflict_id": "U-009-runtime-validation",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "A positive hash-pinned original-process trace is required; static naming or conceptual state names are not promoted to runtime behavior.",
    "resolution_status": "A positive hash-pinned original-process trace is required; static naming or conceptual state names are not promoted to runtime behavior.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "No positive original-process trace reaches this transition in the committed corpus."
  },
  {
    "anchors": [
      "0x00e663b0",
      "0x00e663b0",
      "0x00e666f0"
    ],
    "conflict_id": "effect-failure",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "cCellGFX effect synchronization contains direct Stop/Release versus Create/Start branches. Whether each failure is optional or stage-fatal is unresolved.",
    "resolution_status": "cCellGFX effect synchronization contains direct Stop/Release versus Create/Start branches. Whether each failure is optional or stage-fatal is unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00e5dba0",
      "0x00e5dba0",
      "0x008df730",
      "0x00e666f0",
      "0x00e55120"
    ],
    "conflict_id": "preload-readiness",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "Preload traversal and display-start boundaries are concrete. Completion barrier, waitUntilLoaded behavior, and fatal-child behavior are unresolved.",
    "resolution_status": "Preload traversal and display-start boundaries are concrete. Completion barrier, waitUntilLoaded behavior, and fatal-child behavior are unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00e5dba0",
      "0x00e5dba0",
      "0x00e666f0"
    ],
    "conflict_id": "teardown-order",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The cited direct body establishes a bounded state mutation or call anchor, but the full transition policy, consumer order, and runtime reachability remain unresolved.",
    "resolution_status": "The cited direct body establishes a bounded state mutation or call anchor, but the full transition policy, consumer order, and runtime reachability remain unresolved.",
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
  "original_bytes": 8109,
  "preview": "{\n  \"abi\": {},\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-11-H4-HELPER-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"address_window_offset_005c65e0\",\n      \"va\": \"0x005c65e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"dispatch_key_00628450\",\n      \"va\": \"0x00628450\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"cycle_key_006286a0\",\n      \"va\": \"0x006286a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"release_child_0062c910\",\n      \"va\": \"0x0062c910\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d2a0\",\n      \"va\": \"0x00b3d2a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d300\",\n      \"va\": \"0x00b3d300\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"Simulator_GetUIMissionLogManager\",\n      \"va\": \"0x00b3d4f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-13-E4-EMPIRE-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"EmpirePoliticalColor_00c32cd0\",\n      \"va\": \"0x00c32cd0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"sim-cell\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"embedded_object_first_word_init_00743b50\",\n        \"reconstructed\": true,\n        \"va\": \"0x00743b50\"\n      },\n      {\n        \"name\": \"Simulator::Cell::cCellGFX::PreloadCellResource\",\n        \"reconstructed\": false,\n        \"va\": \"0x00e663b0\"\n      },\n      {\n        \"name\": \"Simulator::Cell::cCellGFX::PreloadPopulateResource\",\n        \"reconstructed\": false,\n        \"va\": \"0x00e665c0\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e819b0\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00e81acb\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e819b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e66727\",\n        \"direction\": \"out\",\n        \"other\": \"0x00743b50\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e66758\",\n        \"direction\": \"out\",\n        \"other\": \"0x00743b50\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e6681b\",\n        \"direction\": \"out\",\n        \"other\": \"0x009a9600\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e66765\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e4cc40\",\n        \"reference_type\": \"thunk\"\n      },\n      {\n        \"callsite\": \"0x00e667a8\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e4cce0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e667ba\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e4cce0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e667cc\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e4cce0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e667de\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e4cce0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e667f0\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e4cce0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e66731\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e4ce40\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e667fb\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e4fc20\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e66741\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e663b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e667b3\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e663b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e667c5\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e663b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e667d7\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e663b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e667e9\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e663b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e66783\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e665c0\",\n        \"reference_type\": \"direct-call\
[TRUNCATED]
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__cCellGFX__PreloadResources.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__cCellGFX__PreloadResources.c"
  ],
  "handoffs": [],
  "metadata": []
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
  "gates": [],
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
  "runtime_gated": false,
  "runtime_validated": 0,
  "status": "implemented"
}
```

## types

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## vtables

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## Conflicts

```json
[
  {
    "anchors": [
      "0x00c932f0",
      "0x00b237c0",
      "0x00c983c0",
      "0x00e74a20",
      "0x00e4ce20",
      "0x00e665c0",
      "0x00e666f0",
      "0x00b237c0",
      "0x00c983c0",
      "0x00c932f0"
    ],
    "conflict_id": "U-006-herd-respawn-evolution",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
    "resolution_status": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00c932f0",
      "0x00c983c0",
      "0x00e74a20",
      "0x00e4ce20",
      "0x00e665c0",
      "0x00e666f0",
      "0x00be34a0",
      "0x00bddef0",
      "0x00bdde70",
      "0x00ca6630",
      "0x00ca6630"
    ],
    "conflict_id": "U-007-city-population-vehicle",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
    "resolution_status": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00e7fd00",
      "0x00e74a20",
      "0x00bb42a0",
      "0x00bb4c90",
      "0x00b237c0",
      "0x00e74a20",
      "0x00e74a20",
      "0x00e4ce20",
      "0x00e5b790",
      "0x00e665c0",
      "0x00e666f0",
      "0x00e80ba0",
      "0x00be34a0",
      "0x00bddef0",
      "0x00bdde70",
      "0x00bb5b50"
    ],
    "conflict_id": "U-009-runtime-validation",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "A positive hash-pinned original-process trace is required; static naming or conceptual state names are not promoted to runtime behavior.",
    "resolution_status": "A positive hash-pinned original-process trace is required; static naming or conceptual state names are not promoted to runtime behavior.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "No positive original-process trace reaches this transition in the committed corpus."
  },
  {
    "anchors": [
      "0x00e663b0",
      "0x00e663b0",
      "0x00e666f0"
    ],
    "conflict_id": "effect-failure",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "cCellGFX effect synchronization contains direct Stop/Release versus Create/Start branches. Whether each failure is optional or stage-fatal is unresolved.",
    "resolution_status": "cCellGFX effect synchronization contains direct Stop/Release versus Create/Start branches. Whether each failure is optional or stage-fatal is unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00e5dba0",
      "0x00e5dba0",
      "0x008df730",
      "0x00e666f0",
      "0x00e55120"
    ],
    "conflict_id": "preload-readiness",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "Preload traversal and display-start boundaries are concrete. Completion barrier, waitUntilLoaded behavior, and fatal-child behavior are unresolved.",
    "resolution_status": "Preload traversal and display-start boundaries are concrete. Completion barrier, waitUntilLoaded behavior, and fatal-child behavior are unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00e5dba0",
      "0x00e5dba0",
      "0x00e666f0"
    ],
    "conflict_id": "teardown-order",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The cited direct body establishes a bounded state mutation or call anchor, but the full transition policy, consumer order, and runtime reachability remain unresolved.",
    "resolution_status": "The cited direct body establishes a bounded state mutation or call anchor, but the full transition policy, consumer order, and runtime reachability remain unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered.
[TRUNCATED]
```
