# Evidence 0x00576c50

- Evidence state: `PERSISTED`
- Live requested: `False`
- Content SHA-256: `a783cc48ebc5f48fdc73e205fffb16eee5a65971bb1d19f65229ad3a5d14b5e5`

## abi

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0067dcc0"
  },
  {
    "name": "FUN_007c3ba0",
    "reconstructed": false,
    "va": "0x007c3ba0"
  },
  {
    "name": "FUN_007c4000",
    "reconstructed": false,
    "va": "0x007c4000"
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
{
  "original_bytes": 10839,
  "preview": "[\n  {\n    \"anchors\": [\n      \"0x00584300\",\n      \"0x00584300\",\n      \"0x005737d0\",\n      \"0x005737d0\",\n      \"0x00576c50\",\n      \"0x00576c50\",\n      \"0x00584300\",\n      \"0x00584300\",\n      \"0x00585d10\",\n      \"0x00585d10\",\n      \"0x00586410\",\n      \"0x00586410\",\n      \"0x00586b00\",\n      \"0x00586b00\",\n      \"0x00587270\",\n      \"0x00587270\"\n    ],\n    \"conflict_id\": \"U-001-mission-transitions\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"Mission enum/field surface is known, but no complete direct writer and callback body establishes each transition. SDK contract is not promoted to native order.\",\n    \"resolution_status\": \"Mission enum/field surface is known, but no complete direct writer and callback body establishes each transition. SDK contract is not promoted to native order.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00582fe0\",\n      \"0x00587270\",\n      \"0x0059c830\",\n      \"0x0059c830\",\n      \"0x00576c50\",\n      \"0x00576c50\",\n      \"0x00582fe0\",\n      \"0x00582fe0\",\n      \"0x00582fe0\",\n      \"0x00584300\",\n      \"0x00584300\",\n      \"0x00586410\",\n      \"0x00586410\",\n      \"0x00586b00\",\n      \"0x00586b00\",\n      \"0x00587270\"\n    ],\n    \"conflict_id\": \"U-006-editor-world-slot-conflict\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The +0x360/+0x364 alternatives are preserved; no pointer-pair versus pointer-plus-ID choice is made without a typed body.\",\n    \"resolution_status\": \"The +0x360/+0x364 alternatives are preserved; no pointer-pair versus pointer-plus-ID choice is made without a typed body.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00aeb160\",\n      \"0x00aeb7b0\",\n      \"0x00aebe90\",\n      \"0x00aeb160\",\n      \"0x00aebe90\",\n      \"0x00aeb7b0\",\n      \"0x00aeb7b0\",\n      \"0x005737d0\",\n      \"0x005737d0\",\n      \"0x00576c50\",\n      \"0x00576c50\",\n      \"0x00582fe0\",\n      \"0x00582fe0\",\n      \"0x00584300\",\n      \"0x00584300\",\n      \"0x00585d10\"\n    ],\n    \"conflict_id\": \"U-007-communication-completion\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"Creation appends to cCommManager+0x20 and ShowCommEvent stores +0x1c before processing. Removal/clear and completion ordering are unresolved.\",\n    \"resolution_status\": \"Creation appends to cCommManager+0x20 and ShowCommEvent stores +0x1c before processing. Removal/clear and completion ordering are unresolved.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x005737d0\",\n      \"0x005737d0\",\n      \"0x00576c50\",\n      \"0x00576c50\",\n      \"0x00582fe0\",\n      \"0x00582fe0\",\n      \"0x00584300\",\n      \"0x00584300\",\n      \"0x00585d10\",\n      \"0x00585d10\",\n      \"0x00586410\",\n      \"0x00586410\",\n      \"0x00586b00\",\n      \"0x00586b00\",\n      \"0x00587270\",\n      \"0x00587270\"\n    ],\n    \"conflict_id\": \"U-008-runtime-validation\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.\",\n    \"resolution_status\": \"The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00587270\",\n      \"0x0058b650\",\n      \"0x013f57f8\",\n      \"0x0058b650\",\n      \"0x0057f3e0\",\n      \"0x013f57f8\",\n      \"0x005737d0\",\n      \"0x005737d0\",\n      \"0x00576c50\",\n      \"0x00576c50\",\n      \"0x0057ce80\",\n      \"0x0057ce80\",\n      \"0x00584300\",\n      \"0x00584300\",\n      \"0x00587270\",\n      \"0x00587270\"\n    ],\n    \"conflict_id\": \"ceditor_vtable_tail\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.\",\n    \"resolution_status\": \"The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x005737d0\",\n      \"0x00588570\",\n      \"0x0058ac10\",\n      \"0x00b3d350\",\n      \"0x00e818f0\",\n      \"0x00b3d350\",\n      \"0x00e818f0\",\n      \"0x00b3d350\",\n      \"0x005737d0\",\n      \"0x00576c50\",\n      \"0x00576c50\",\n      \"0x0057ce80\",\n      \"0x0057ce80\",\n      \"0x00584300\",\n      \"0x00584300\",\n      \"0x00587a20\"\n    ],\n    \"conflict_id\": \"editor_input_routing\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The input/UI surface is structurally p
[TRUNCATED]
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
  "original_bytes": 8827,
  "preview": "{\n  \"abi\": {},\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013f57f8\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"editor_input_005737d0\",\n      \"va\": \"0x005737d0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013f57f8\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"editor_input_00585890\",\n      \"va\": \"0x00585890\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013f57f8\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"editor_input_00585d10\",\n      \"va\": \"0x00585d10\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013f57f8\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"editor_input_00588570\",\n      \"va\": \"0x00588570\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013f57f8\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"editor_input_0058ac10\",\n      \"va\": \"0x0058ac10\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013f57f8\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"editor_input_0058b650\",\n      \"va\": \"0x0058b650\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"editor-core\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0067dcc0\"\n      },\n      {\n        \"name\": \"FUN_007c3ba0\",\n        \"reconstructed\": false,\n        \"va\": \"0x007c3ba0\"\n      },\n      {\n        \"name\": \"FUN_007c4000\",\n        \"reconstructed\": false,\n        \"va\": \"0x007c4000\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00576d38\",\n        \"direction\": \"out\",\n        \"other\": \"0x004ad330\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00576d74\",\n        \"direction\": \"out\",\n        \"other\": \"0x004ad330\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00576f37\",\n        \"direction\": \"out\",\n        \"other\": \"0x004b9140\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00576d24\",\n        \"direction\": \"out\",\n        \"other\": \"0x00563de0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00576d29\",\n        \"direction\": \"out\",\n        \"other\": \"0x00563de0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00576cdb\",\n        \"direction\": \"out\",\n        \"other\": \"0x00571db0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00577101\",\n        \"direction\": \"out\",\n        \"other\": \"0x005a98f0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00576ca3\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067dcc0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00576eab\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067dd80\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00576ebe\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067dd80\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00576ed1\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067dd80\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00576efb\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067ddd0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00576c67\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067de20\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00576c7a\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067de20\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00576c8d\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067de20\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0057709b\",\n        \"direction\": \"out\",\n        \"other\": \"0x006b1f90\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00576f70\",\n        \"direction\": \"out\",\n        \"other\": \"0x007c3ba0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00576f9f\",\n        \"direction\": \"out\",\n        \"other\": \"0x007c3ba0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00576fce\",\n        \"direction\": \"out\",\n        \"other\": \"0x007c3ba0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00576ffd\",\n        \"direction\": \"out\",\n        \"other\": \"0x007c3ba0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0057702c\",\n        \"direction\": \"out\",\n        \"other\": \"0x007c3ba0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00576f81\",\n        \"di
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditor__Dispose.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditor__Dispose.c"
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
  "status": "queued"
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
  "vtable:0x013f57f8"
]
```

## Conflicts

```json
{
  "original_bytes": 10839,
  "preview": "[\n  {\n    \"anchors\": [\n      \"0x00584300\",\n      \"0x00584300\",\n      \"0x005737d0\",\n      \"0x005737d0\",\n      \"0x00576c50\",\n      \"0x00576c50\",\n      \"0x00584300\",\n      \"0x00584300\",\n      \"0x00585d10\",\n      \"0x00585d10\",\n      \"0x00586410\",\n      \"0x00586410\",\n      \"0x00586b00\",\n      \"0x00586b00\",\n      \"0x00587270\",\n      \"0x00587270\"\n    ],\n    \"conflict_id\": \"U-001-mission-transitions\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"Mission enum/field surface is known, but no complete direct writer and callback body establishes each transition. SDK contract is not promoted to native order.\",\n    \"resolution_status\": \"Mission enum/field surface is known, but no complete direct writer and callback body establishes each transition. SDK contract is not promoted to native order.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00582fe0\",\n      \"0x00587270\",\n      \"0x0059c830\",\n      \"0x0059c830\",\n      \"0x00576c50\",\n      \"0x00576c50\",\n      \"0x00582fe0\",\n      \"0x00582fe0\",\n      \"0x00582fe0\",\n      \"0x00584300\",\n      \"0x00584300\",\n      \"0x00586410\",\n      \"0x00586410\",\n      \"0x00586b00\",\n      \"0x00586b00\",\n      \"0x00587270\"\n    ],\n    \"conflict_id\": \"U-006-editor-world-slot-conflict\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The +0x360/+0x364 alternatives are preserved; no pointer-pair versus pointer-plus-ID choice is made without a typed body.\",\n    \"resolution_status\": \"The +0x360/+0x364 alternatives are preserved; no pointer-pair versus pointer-plus-ID choice is made without a typed body.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00aeb160\",\n      \"0x00aeb7b0\",\n      \"0x00aebe90\",\n      \"0x00aeb160\",\n      \"0x00aebe90\",\n      \"0x00aeb7b0\",\n      \"0x00aeb7b0\",\n      \"0x005737d0\",\n      \"0x005737d0\",\n      \"0x00576c50\",\n      \"0x00576c50\",\n      \"0x00582fe0\",\n      \"0x00582fe0\",\n      \"0x00584300\",\n      \"0x00584300\",\n      \"0x00585d10\"\n    ],\n    \"conflict_id\": \"U-007-communication-completion\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"Creation appends to cCommManager+0x20 and ShowCommEvent stores +0x1c before processing. Removal/clear and completion ordering are unresolved.\",\n    \"resolution_status\": \"Creation appends to cCommManager+0x20 and ShowCommEvent stores +0x1c before processing. Removal/clear and completion ordering are unresolved.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x005737d0\",\n      \"0x005737d0\",\n      \"0x00576c50\",\n      \"0x00576c50\",\n      \"0x00582fe0\",\n      \"0x00582fe0\",\n      \"0x00584300\",\n      \"0x00584300\",\n      \"0x00585d10\",\n      \"0x00585d10\",\n      \"0x00586410\",\n      \"0x00586410\",\n      \"0x00586b00\",\n      \"0x00586b00\",\n      \"0x00587270\",\n      \"0x00587270\"\n    ],\n    \"conflict_id\": \"U-008-runtime-validation\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.\",\n    \"resolution_status\": \"The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00587270\",\n      \"0x0058b650\",\n      \"0x013f57f8\",\n      \"0x0058b650\",\n      \"0x0057f3e0\",\n      \"0x013f57f8\",\n      \"0x005737d0\",\n      \"0x005737d0\",\n      \"0x00576c50\",\n      \"0x00576c50\",\n      \"0x0057ce80\",\n      \"0x0057ce80\",\n      \"0x00584300\",\n      \"0x00584300\",\n      \"0x00587270\",\n      \"0x00587270\"\n    ],\n    \"conflict_id\": \"ceditor_vtable_tail\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The address/layout alternatives are preserved; no owner or exact binary identity is selected without a ty
[TRUNCATED]
```
