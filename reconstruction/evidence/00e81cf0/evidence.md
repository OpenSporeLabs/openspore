# Evidence 0x00e81cf0

- Evidence state: `PERSISTED`
- Live requested: `False`
- Content SHA-256: `d128df7ee6084b3089caabd8e9dd7c89d69a957250181eac4e649bc4ef6e4cb0`

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
    "name": "property_value_resolve_0041e920",
    "reconstructed": true,
    "va": "0x0041e920"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0067dcc0"
  }
]
```

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
      "0x00e81cf0",
      "0x00e81cf0",
      "0x0067dcc0",
      "0x00b3d330",
      "0x00e552f0"
    ],
    "conflict_id": "U04",
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
      "0x00e81cf0",
      "0x00e81f30",
      "0x00e81cf0",
      "0x00e81cf0",
      "0x00e81f30",
      "0x00e81cf0",
      "0x00e81f30",
      "0x00e81cf0",
      "0x00e81f30",
      "0x00e81cf0",
      "0x00e81f30"
    ],
    "conflict_id": "U09",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
    "resolution_status": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00e80980",
      "0x00e818f0",
      "0x00e81cf0",
      "0x00e81f30",
      "0x00e552f0",
      "0x00e7fc00",
      "0x00e616c0",
      "0x00e80d8b",
      "0x01485550",
      "0x013f57f8",
      "0x01485550",
      "0x01485558",
      "0x01485550",
      "0x01485550",
      "0x01485558",
      "0x01485550"
    ],
    "conflict_id": "VT-002",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "RESOLVED_OBSERVED",
    "resolution_status": "RESOLVED_OBSERVED",
    "source": "knowledgegraph/research/conflicts/track-a-type-signature.json",
    "subject": "0x01485550/0x01485558 cCellModeStrategy vtable owner and base",
    "unresolved_reason": "The exact source-level name of the secondary subobject and the language-level interface declaration remain unproven, but the disputed table owner/base is resolved."
  },
  {
    "anchors": [
      "0x00aeb160",
      "0x00aebe90",
      "0x00aeb160",
      "0x00aebe90",
      "0x00f47b10",
      "0x00e552f0",
      "0x00e552f0",
      "0x00e7fc00",
      "0x00e7fc00",
      "0x00e80980",
      "0x00e80980",
      "0x00e81cf0",
      "0x00e81cf0",
      "0x00e81f30",
      "0x00e81f30",
      "0x00f47930"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/temporal-semantics.json:4",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "Deferred trigger and owner/order semantics are not recovered; no immediate dispatch equivalence is claimed.",
    "resolution_status": "Deferred trigger and owner/order semantics are not recovered; no immediate dispatch equivalence is claimed.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00e81cf0",
      "0x00e81cf0",
      "0x00e552f0",
      "0x00e552f0",
      "0x00e7fc00",
      "0x00e7fc00",
      "0x00e80980",
      "0x00e80980",
      "0x00e81cf0",
      "0x00e81cf0",
      "0x00e81f30",
      "0x00e81f30"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/temporal-semantics.json:6",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "A positive hash-pinned original-process trace is required; static naming or conceptual state names are not promoted to runtime behavior.",
    "resolution_status": "A positive hash-pinned original-process trace is required; static naming or conceptual state names are not promoted to runtime behavior.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "No positive original-process trace reaches this transition in the committed corpus."
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
  "original_bytes": 7930,
  "preview": "{\n  \"abi\": {},\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"pkg-app-imessage-manager-dtor\",\n      \"score\": 6,\n      \"symbol\": \"get_0067dc80\",\n      \"va\": \"0x0067dc80\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"pkg-cheat-func3ch-0067e6b0\",\n      \"score\": 6,\n      \"symbol\": \"func3_ch_0067e6b0\",\n      \"va\": \"0x0067e6b0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"pkg-cheat-dispatch-0067e6f0\",\n      \"score\": 6,\n      \"symbol\": \"cCheatManager_func40h_0067e6f0\",\n      \"va\": \"0x0067e6f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"cheat-func44h-0067e730\",\n      \"score\": 6,\n      \"symbol\": \"func44h_0067e730\",\n      \"va\": \"0x0067e730\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"pkg-app-proplist-copyall-wave16\",\n      \"score\": 6,\n      \"symbol\": \"all_copy_from_properties_006a14d0\",\n      \"va\": \"0x006a14d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"pkg-proplist-dispatch-wave14\",\n      \"score\": 6,\n      \"symbol\": \"app_property_list_add_all_properties_from_006a1510\",\n      \"va\": \"0x006a1510\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"pkg-dfw-006a1540\",\n      \"score\": 6,\n      \"symbol\": \"proplist_write_006a1540\",\n      \"va\": \"0x006a1540\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"pkg-property-clear-wave13\",\n      \"score\": 6,\n      \"symbol\": \"property_list_clear_006a2a80\",\n      \"va\": \"0x006a2a80\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"app-lifecycle\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"property_value_resolve_0041e920\",\n        \"reconstructed\": true,\n        \"va\": \"0x0041e920\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0067dcc0\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 1,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00e81f0c\",\n        \"direction\": \"out\",\n        \"other\": \"0x0041e920\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e81def\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067dcc0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e81e52\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067dcc0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e81e71\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067dcc0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e81e90\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067dcc0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e81eaf\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067dcc0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e81ece\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067dcc0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e81e0b\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067ddd0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e81d3d\",\n        \"direction\": \"out\",\n        \"other\": \"0x00692850\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e81d0e\",\n        \"direction\": \"out\",\n        \"other\": \"0x00692f60\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e81d2f\",\n        \"direction\": \"out\",\n        \"other\": \"0x00ab30c0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e81e3d\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e4c8c0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e81e42\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e4db10\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e81f16\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e4fe50\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e81dba\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e61aa0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e81d5e\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e646d0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e81d8c\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e647d0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e81e35\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e834d0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e81d50\",\n        \"direction\": \"out\",\n        \"other\": \"0x00f473a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e81d7e\",\n        \"direction\": \"out\",\n        \"o
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__cCellModeStrategy__Initialize.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__cCellModeStrategy__Initialize.c"
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

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x01485550"
]
```

## Conflicts

```json
[
  {
    "anchors": [
      "0x00e81cf0",
      "0x00e81cf0",
      "0x0067dcc0",
      "0x00b3d330",
      "0x00e552f0"
    ],
    "conflict_id": "U04",
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
      "0x00e81cf0",
      "0x00e81f30",
      "0x00e81cf0",
      "0x00e81cf0",
      "0x00e81f30",
      "0x00e81cf0",
      "0x00e81f30",
      "0x00e81cf0",
      "0x00e81f30",
      "0x00e81cf0",
      "0x00e81f30"
    ],
    "conflict_id": "U09",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
    "resolution_status": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00e80980",
      "0x00e818f0",
      "0x00e81cf0",
      "0x00e81f30",
      "0x00e552f0",
      "0x00e7fc00",
      "0x00e616c0",
      "0x00e80d8b",
      "0x01485550",
      "0x013f57f8",
      "0x01485550",
      "0x01485558",
      "0x01485550",
      "0x01485550",
      "0x01485558",
      "0x01485550"
    ],
    "conflict_id": "VT-002",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "RESOLVED_OBSERVED",
    "resolution_status": "RESOLVED_OBSERVED",
    "source": "knowledgegraph/research/conflicts/track-a-type-signature.json",
    "subject": "0x01485550/0x01485558 cCellModeStrategy vtable owner and base",
    "unresolved_reason": "The exact source-level name of the secondary subobject and the language-level interface declaration remain unproven, but the disputed table owner/base is resolved."
  },
  {
    "anchors": [
      "0x00aeb160",
      "0x00aebe90",
      "0x00aeb160",
      "0x00aebe90",
      "0x00f47b10",
      "0x00e552f0",
      "0x00e552f0",
      "0x00e7fc00",
      "0x00e7fc00",
      "0x00e80980",
      "0x00e80980",
      "0x00e81cf0",
      "0x00e81cf0",
      "0x00e81f30",
      "0x00e81f30",
      "0x00f47930"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/temporal-semantics.json:4",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "Deferred trigger and owner/order semantics are not recovered; no immediate dispatch equivalence is claimed.",
    "resolution_status": "Deferred trigger and owner/order semantics are not recovered; no immediate dispatch equivalence is claimed.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00e81cf0",
      "0x00e81cf0",
      "0x00e552f0",
      "0x00e552f0",
      "0x00e7fc00",
      "0x00e7fc00",
      "0x00e80980",
      "0x00e80980",
      "0x00e81cf0",
      "0x00e81cf0",
      "0x00e81f30",
      "0x00e81f30"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/temporal-semantics.json:6",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "A positive hash-pinned original-process trace is required; static naming or conceptual state names are not promoted to runtime behavior.",
    "resolution_status": "A positive hash-pinned original-process trace is required; static naming or conceptual state names are not promoted to runtime behavior.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "No positive original-process trace reaches this transition in the committed corpus."
  }
]
```
