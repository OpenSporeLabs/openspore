# Evidence 0x00e66280

- Evidence state: `PERSISTED`
- Live requested: `False`
- Content SHA-256: `b9b34538b566df3e6feccf03864a7c69ae839b6502d5343e700f76f3029992d0`

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
    "name": "Simulator::Cell::cCellGFX::AddPreloadedModel2",
    "reconstructed": false,
    "va": "0x00e653a0"
  },
  {
    "name": "Simulator::Cell::cCellGFX::AddPreloadedModel",
    "reconstructed": false,
    "va": "0x00e65410"
  },
  {
    "name": "Simulator::Cell::cCellGFX::AddPreloadedTexture",
    "reconstructed": false,
    "va": "0x00e65970"
  },
  {
    "name": "Simulator::Cell::cCellGFX::AddPreloadedEffect",
    "reconstructed": false,
    "va": "0x00e66280"
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
    "name": "Simulator::Cell::cCellGFX::AddPreloadedEffect",
    "reconstructed": false,
    "va": "0x00e66280"
  },
  {
    "name": "Simulator::Cell::cCellGFX::PreloadCellResource",
    "reconstructed": false,
    "va": "0x00e663b0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e67610"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e67670"
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
  },
  {
    "anchors": [
      "0x00e63560",
      "0x00e63560",
      "0x00acd9a0",
      "0x00ace2c0",
      "0x00b25f40",
      "0x00ba0080",
      "0x00bf9820",
      "0x00e5c780",
      "0x00551240",
      "0x0067dd90",
      "0x00e66280",
      "0x00e66840",
      "0x00e63560",
      "0x00e5c780",
      "0x00e63560",
      "0x00571f80"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/additional-domains.json:4",
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
      "0x00a20670",
      "0x00571f80",
      "0x00572070",
      "0x00572020",
      "0x0067dd90",
      "0x00e66280",
      "0x00e66840",
      "0x00e63560",
      "0x00c8ec00"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/additional-domains.json:5",
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
      "0x00676e90",
      "0x00676e90",
      "0x00676e50",
      "0x00b31da0",
      "0x006766d0",
      "0x006766b0",
      "0x00676620",
      "0x00b321e0",
      "0x00676c40",
      "0x00b32330",
      "0x00676e90",
      "0x00b32560",
      "0x0067dd90",
      "0x00b63980",
      "0x00b32390",
      "0x00e66280"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/additional-domains.json:6",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The cited stream or file boundary is retained, but the complete wire/transaction/round-trip contract is not reconstructed.",
    "resolution_status": "The cited stream or file boundary is retained, but the complete wire/transaction/round-trip contract is not reconstructed.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00571f80",
      "0x00571f80",
      "0x0067cae0",
      "0x00a20670",
      "0x00571f80",
      "0x00572070",
      "0x00572020",
      "0x0059ca70",
      "0x0059cac0",
      "0x0059cea0",
      "0x0059cf00",
      "0x0067dd90",
      "0x00e66280",
      "0x00e66840",
      "0x00e63560",
      "0x0059c6e0"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/additional-domains.json:9",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The cited stream or file boundary is retained, but the complete wire/transaction/round-trip contract is not reconstructed.",
    "resolution_status": "The cited stream or file boundary is retained, but the complete wire/transaction/round-trip contract is not reconstructed.",
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
  "original_bytes": 9952,
  "preview": "{\n  \"abi\": {},\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-11-H4-HELPER-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"address_window_offset_005c65e0\",\n      \"va\": \"0x005c65e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"dispatch_key_00628450\",\n      \"va\": \"0x00628450\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"cycle_key_006286a0\",\n      \"va\": \"0x006286a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"release_child_0062c910\",\n      \"va\": \"0x0062c910\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d2a0\",\n      \"va\": \"0x00b3d2a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d300\",\n      \"va\": \"0x00b3d300\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"Simulator_GetUIMissionLogManager\",\n      \"va\": \"0x00b3d4f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-13-E4-EMPIRE-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"EmpirePoliticalColor_00c32cd0\",\n      \"va\": \"0x00c32cd0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"sim-cell\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"Simulator::Cell::cCellGFX::AddPreloadedModel2\",\n        \"reconstructed\": false,\n        \"va\": \"0x00e653a0\"\n      },\n      {\n        \"name\": \"Simulator::Cell::cCellGFX::AddPreloadedModel\",\n        \"reconstructed\": false,\n        \"va\": \"0x00e65410\"\n      },\n      {\n        \"name\": \"Simulator::Cell::cCellGFX::AddPreloadedTexture\",\n        \"reconstructed\": false,\n        \"va\": \"0x00e65970\"\n      },\n      {\n        \"name\": \"Simulator::Cell::cCellGFX::AddPreloadedEffect\",\n        \"reconstructed\": false,\n        \"va\": \"0x00e66280\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": \"Simulator::Cell::cCellGFX::AddPreloadedEffect\",\n        \"reconstructed\": false,\n        \"va\": \"0x00e66280\"\n      },\n      {\n        \"name\": \"Simulator::Cell::cCellGFX::PreloadCellResource\",\n        \"reconstructed\": false,\n        \"va\": \"0x00e663b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e67610\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e67670\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00e66326\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e66280\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e6646d\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e663b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e664e6\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e663b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e67649\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e67610\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e67684\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e67670\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e6769d\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e67670\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e676b6\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e67670\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e676d2\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e67670\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e676eb\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e67670\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e67704\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e67670\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e6771d\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e67670\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e67739\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e67670\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e67752\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e67670\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e6776b\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e67670\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e67787\",\n        \"direction\": \"in\",\n        \"other\": \"0
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__cCellGFX__AddPreloadedEffect.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__cCellGFX__AddPreloadedEffect.c"
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
  },
  {
    "anchors": [
      "0x00e63560",
      "0x00e63560",
      "0x00acd9a0",
      "0x00ace2c0",
      "0x00b25f40",
      "0x00ba0080",
      "0x00bf9820",
      "0x00e5c780",
      "0x00551240",
      "0x0067dd90",
      "0x00e66280",
      "0x00e66840",
      "0x00e63560",
      "0x00e5c780",
      "0x00e63560",
      "0x00571f80"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/additional-domains.json:4",
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
      "0x00a20670",
      "0x00571f80",
      "0x00572070",
      "0x00572020",
      "0x0067dd90",
      "0x00e66280",
      "0x00e66840",
      "0x00e63560",
      "0x00c8ec00"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/additional-domains.json:5",
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
      "0x00676e90",
      "0x00676e90",
      "0x00676e50",
      "0x00b31da0",
      "0x006766d0",
      "0x006766b0",
      "0x00676620",
      "0x00b321e0",
      "0x00676c40",
      "0x00b32330",
      "0x00676e90",
      "0x00b32560",
      "0x0067dd90",
      "0x00b63980",
      "0x00b32390",
      "0x00e66280"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/additional-domains.json:6",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The cited stream or file boundary is retained, but the complete wire/transaction/round-trip contract is not reconstructed.",
    "resolution_status": "The cited stream or file boundary is retained, but the complete wire/transaction/round-trip contract is not reconstructed.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00571f80",
      "0x00571f80",
      "0x0067cae0",
      "0x00a20670",
      "0x00571f80",
      "0x00572070",
      "0x00572020",
      "0x0059ca70",
      "0x0059cac0",
      "0x0059cea0",
      "0x0059cf00",
      "0x0067dd90",
      "0x00e66280",
      "0x00e66840",
      "0x00e63560",
      "0x0059c6e0"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/additional-domains.json:9",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The cited stream or file boundary is retained, but the complete wire/transaction/round-trip contract is not reconstructed.",
    "resolution_status": "The cited stream or file boundary is retained, but the complete wire/transaction/round-trip contract is not reconstructed.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  }
]
```
