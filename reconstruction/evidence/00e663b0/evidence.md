# Evidence 0x00e663b0

- Evidence state: `PERSISTED`
- Live requested: `False`
- Content SHA-256: `598f57f23ec90dcf712ae32b866050662817e8b41ce7100ad530b0869e687014`

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
    "name": "map_int_whatever_find",
    "reconstructed": true,
    "va": "0x00e5c780"
  },
  {
    "name": "Simulator::Cell::cCellGFX::PreloadCreature",
    "reconstructed": false,
    "va": "0x00e64980"
  },
  {
    "name": "Simulator::Cell::cCellGFX::AddPreloadedModel2",
    "reconstructed": false,
    "va": "0x00e653a0"
  },
  {
    "name": "Simulator::Cell::cCellGFX::AddPreloadedEffect",
    "reconstructed": false,
    "va": "0x00e66280"
  },
  {
    "name": "Simulator::Cell::cCellGFX::PreloadCellResource",
    "reconstructed": false,
    "va": "0x00e663b0"
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
    "va": "0x00e4fc20"
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
  },
  {
    "name": "Simulator::Cell::cCellGFX::PreloadResources",
    "reconstructed": false,
    "va": "0x00e666f0"
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
      "0x00e663b0",
      "0x00e663b0",
      "0x008da6f0"
    ],
    "conflict_id": "resource-manager-error-taxonomy",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "resolution_status": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
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
  "original_bytes": 10290,
  "preview": "{\n  \"abi\": {},\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-11-H4-HELPER-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"address_window_offset_005c65e0\",\n      \"va\": \"0x005c65e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"dispatch_key_00628450\",\n      \"va\": \"0x00628450\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"cycle_key_006286a0\",\n      \"va\": \"0x006286a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"release_child_0062c910\",\n      \"va\": \"0x0062c910\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d2a0\",\n      \"va\": \"0x00b3d2a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d300\",\n      \"va\": \"0x00b3d300\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"Simulator_GetUIMissionLogManager\",\n      \"va\": \"0x00b3d4f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-13-E4-EMPIRE-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"EmpirePoliticalColor_00c32cd0\",\n      \"va\": \"0x00c32cd0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"sim-cell\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"embedded_object_first_word_init_00743b50\",\n        \"reconstructed\": true,\n        \"va\": \"0x00743b50\"\n      },\n      {\n        \"name\": \"map_int_whatever_find\",\n        \"reconstructed\": true,\n        \"va\": \"0x00e5c780\"\n      },\n      {\n        \"name\": \"Simulator::Cell::cCellGFX::PreloadCreature\",\n        \"reconstructed\": false,\n        \"va\": \"0x00e64980\"\n      },\n      {\n        \"name\": \"Simulator::Cell::cCellGFX::AddPreloadedModel2\",\n        \"reconstructed\": false,\n        \"va\": \"0x00e653a0\"\n      },\n      {\n        \"name\": \"Simulator::Cell::cCellGFX::AddPreloadedEffect\",\n        \"reconstructed\": false,\n        \"va\": \"0x00e66280\"\n      },\n      {\n        \"name\": \"Simulator::Cell::cCellGFX::PreloadCellResource\",\n        \"reconstructed\": false,\n        \"va\": \"0x00e663b0\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e4fc20\"\n      },\n      {\n        \"name\": \"Simulator::Cell::cCellGFX::PreloadCellResource\",\n        \"reconstructed\": false,\n        \"va\": \"0x00e663b0\"\n      },\n      {\n        \"name\": \"Simulator::Cell::cCellGFX::PreloadPopulateResource\",\n        \"reconstructed\": false,\n        \"va\": \"0x00e665c0\"\n      },\n      {\n        \"name\": \"Simulator::Cell::cCellGFX::PreloadResources\",\n        \"reconstructed\": false,\n        \"va\": \"0x00e666f0\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00e4fc74\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e4fc20\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e66500\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e663b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e6650d\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e663b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e6651a\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e663b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e66537\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e663b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e6654f\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e663b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e66567\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e663b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e66611\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e665c0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e66623\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e665c0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e6665d\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e665c0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e6666b\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e665c0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e6667d\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e665c0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e6668b\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e665c0\",\n
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__cCellGFX__PreloadCellResource.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__cCellGFX__PreloadCellResource.c"
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
      "0x00e663b0",
      "0x00e663b0",
      "0x008da6f0"
    ],
    "conflict_id": "resource-manager-error-taxonomy",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "resolution_status": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  }
]
```
