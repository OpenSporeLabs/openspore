# Evidence 0x00587a20

- Evidence state: `PERSISTED`
- Live requested: `False`
- Content SHA-256: `97c7b54b901bc382e52a0e284c3c7508a50295049b85549ed535108c04d3f3d2`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_this": true,
  "hidden_this_register": "ECX",
  "receiver": true,
  "receiver_register": "ECX",
  "ret_form": "RET",
  "return_observation": "Ghidra resolves return_type void (analyze_function_complete, ghidra_function.return_type_resolved true). The derived openspore-abi-inference-1 record for this target abstained (conventions.confidence UNKNOWN, calling_convention null, candidate_conventions __cdecl) and its return claim is contradicted by the balanced FLD/FSTP pair; see conflicts_and_disagreements.",
  "return_semantics": "void. The epilogue is POP ESI ; POP EBP ; POP EBX ; ADD ESP,0x44 ; RET: a bare RET with no immediate, and no instruction after the last call reads a return register. The x87 pair at 0x00587b10 (FLD float ptr [ESI+0x4d0]) and 0x00587b1b (FSTP float ptr [ESP]) is balanced -- FSTP pops what FLD pushed -- so nothing is left on the x87 stack, and the value is a 4-byte stack argument, not a result. This DISAGREES with the derived ABI record for this target, which reports return_register ST0 and return_semantics float_or_x87_in_ST0; that reading is a false positive of the linear-sweep inference, p...",
  "return_type": "void",
  "saved_registers": [
    "EBP",
    "EBX",
    "EDI",
    "ESI"
  ],
  "stack_arguments": [],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": [
    "RET at 0x0058856a, bare, no immediate",
    "RET"
  ]
}
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": null,
    "reconstructed": false,
    "va": "0x004ad330"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00573c00"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00573d70"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005772b0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00587270"
  },
  {
    "name": "release_child_0062c910",
    "reconstructed": true,
    "va": "0x0062c910"
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
      "0x005737d0",
      "0x00588570",
      "0x0058ac10",
      "0x00b3d350",
      "0x00e818f0",
      "0x00b3d350",
      "0x00e818f0",
      "0x00b3d350",
      "0x005737d0",
      "0x00576c50",
      "0x00576c50",
      "0x0057ce80",
      "0x0057ce80",
      "0x00584300",
      "0x00584300",
      "0x00587a20"
    ],
    "conflict_id": "editor_input_routing",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "resolution_status": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x005737d0",
      "0x005737d0",
      "0x00576c50",
      "0x00576c50",
      "0x0057ce80",
      "0x0057ce80",
      "0x00584300",
      "0x00584300",
      "0x00587270",
      "0x00587270",
      "0x00587a20",
      "0x00587a20",
      "0x00588570",
      "0x00588570",
      "0x0058ac10",
      "0x0058ac10"
    ],
    "conflict_id": "editor_runtime_validation",
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
      "0x00574080",
      "0x00586410",
      "0x0058ac10",
      "0x0058ac10",
      "0x004af260",
      "0x00574080",
      "0x00576c50",
      "0x00576c50",
      "0x0057ce80",
      "0x0057ce80",
      "0x00584300",
      "0x00584300",
      "0x00586410",
      "0x00587a20",
      "0x00587a20",
      "0x0058be50"
    ],
    "conflict_id": "history_budget_semantics",
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
      "0x00586b00",
      "0x00587270",
      "0x00587a20",
      "0x00588570",
      "0x00588570",
      "0x005dda30",
      "0x005737d0",
      "0x005737d0",
      "0x005737d0",
      "0x005737d0",
      "0x00586b00",
      "0x00586b00",
      "0x00586b00",
      "0x00587270",
      "0x00587270",
      "0x00587270"
    ],
    "conflict_id": "manipulator_cancel",
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
      "0x005737d0",
      "0x00588570",
      "0x0058b650",
      "0x00588570",
      "0x0057f3e0",
      "0x005737d0",
      "0x005737d0",
      "0x005737d0",
      "0x00586b00",
      "0x00586b00",
      "0x00587270",
      "0x00587270",
      "0x00587a20",
      "0x00587a20",
      "0x00588570",
      "0x00588570"
    ],
    "conflict_id": "manipulator_types",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
    "resolution_status": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
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
  "original_bytes": 19612,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"receiver\": true,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET\",\n    \"return_observation\": \"Ghidra resolves return_type void (analyze_function_complete, ghidra_function.return_type_resolved true). The derived openspore-abi-inference-1 record for this target abstained (conventions.confidence UNKNOWN, calling_convention null, candidate_conventions __cdecl) and its return claim is contradicted by the balanced FLD/FSTP pair; see conflicts_and_disagreements.\",\n    \"return_semantics\": \"void. The epilogue is POP ESI ; POP EBP ; POP EBX ; ADD ESP,0x44 ; RET: a bare RET with no immediate, and no instruction after the last call reads a return register. The x87 pair at 0x00587b10 (FLD float ptr [ESI+0x4d0]) and 0x00587b1b (FSTP float ptr [ESP]) is balanced -- FSTP pops what FLD pushed -- so nothing is left on the x87 stack, and the value is a 4-byte stack argument, not a result. This DISAGREES with the derived ABI record for this target, which reports return_register ST0 and return_semantics float_or_x87_in_ST0; that reading is a false positive of the linear-sweep inference, p...\",\n    \"return_type\": \"void\",\n    \"saved_registers\": [\n      \"EBP\",\n      \"EBX\",\n      \"EDI\",\n      \"ESI\"\n    ],\n    \"stack_arguments\": [],\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": [\n      \"RET at 0x0058856a, bare, no immediate\",\n      \"RET\"\n    ]\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"shared_types:void*\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 5,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:Byte\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 5,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:Byte\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 5,\n      \"symbol\": \"editor_bake_select_004c4a30\",\n      \"va\": \"0x004c4a30\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:void*\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-PALETTE-SAFE-WAVE11\",\n      \"score\": 5,\n      \"symbol\": \"palette_safe_wave11_fill_node_array_005c7ff0\",\n      \"va\": \"0x005c7ff0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:void*\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SERVICES-SAFE-WAVE11\",\n      \"score\": 5,\n      \"symbol\": \"service_005fa8d0\",\n      \"va\": \"0x005fa8d0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:void*\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SERVICES-SAFE-WAVE11\",\n      \"score\": 5,\n      \"symbol\": \"service_0060ee90\",\n      \"va\": \"0x0060ee90\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 5,\n      \"symbol\": \"release_child_0062c910\",\n      \"va\": \"0x0062c910\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:void*\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 5,\n      \"symbol\": \"FUN_00aea230\",\n      \"va\": \"0x00aea230\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [\n    \"48 of the 54 direct callees have no name in the SDK and no recovered body in this repository. Their conventions and argument counts are fixed from their own epilogues, which is enough to call them correctly, but not enough to say what they do.\",\n    \"No original-process trace exists in this repository, so nothing about this function's runtime behaviour is established. The five conflict-ledger entries that name 0x00587a20 (editor_input_routing, editor_runtime_validation, history_budget_semantics, manipulator_cancel, manipulator_types) all record that their transition contract is not established, and all five remain open: knowledgegraph/research/conflicts/track-c-state-events.json.\",\n    \"The canonical record associates vtable:0x013f57f8 with this target while the xref export records vtable_reference_count 0 for it, so the two contradict each other and neither is independent of the other. No table is claimed as a dispatch target as a result.\",\n    \"The canonical record associates vtable:0x013f57f8 with this target while the xref export records vtable_reference_count 0, so the two contradict each other and neither is independent of the other. No table is claimed as a dispatch target.\",\n    \"The xref export's edge list for this target is truncated at 30 of 78 rows (MAX_DEPENDENCY_EDGES), so the validator's CALLS check can only WARN: the machine callee set is a lower bound and cannot bound the source. The 54-target parity reported above was measured against GhidraMCP directly instead.\"\n  ],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"editor-core\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004ad330\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00573c00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00573d70\
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditor__OnExit.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditor__OnExit.c",
    "reconstruction/staging/pkg-dogfood-00587a20-a1/editor_onexit_00587a20.cpp",
    "reconstruction/staging/pkg-dogfood-00587a20-a1/editor_onexit_00587a20.hpp",
    "reconstruction/staging/pkg-editor-onexit-smoke01/editor_onexit_00587a20.cpp",
    "reconstruction/staging/pkg-editor-onexit-smoke01/editor_onexit_00587a20.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-dogfood-00587a20-a1/00587a20.json",
    "reconstruction/metadata/pkg-editor-onexit-smoke01/00587a20.json"
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
    "runtime validation not run: no positive hash-pinned original-process trace reaches 0x00587a20 in the committed corpus"
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
  "status": "queued"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "Byte",
  "Dword",
  "HIGH",
  "LocalAppState",
  "U64",
  "float",
  "void",
  "void*"
]
```

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
[
  {
    "anchors": [
      "0x005737d0",
      "0x00588570",
      "0x0058ac10",
      "0x00b3d350",
      "0x00e818f0",
      "0x00b3d350",
      "0x00e818f0",
      "0x00b3d350",
      "0x005737d0",
      "0x00576c50",
      "0x00576c50",
      "0x0057ce80",
      "0x0057ce80",
      "0x00584300",
      "0x00584300",
      "0x00587a20"
    ],
    "conflict_id": "editor_input_routing",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "resolution_status": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x005737d0",
      "0x005737d0",
      "0x00576c50",
      "0x00576c50",
      "0x0057ce80",
      "0x0057ce80",
      "0x00584300",
      "0x00584300",
      "0x00587270",
      "0x00587270",
      "0x00587a20",
      "0x00587a20",
      "0x00588570",
      "0x00588570",
      "0x0058ac10",
      "0x0058ac10"
    ],
    "conflict_id": "editor_runtime_validation",
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
      "0x00574080",
      "0x00586410",
      "0x0058ac10",
      "0x0058ac10",
      "0x004af260",
      "0x00574080",
      "0x00576c50",
      "0x00576c50",
      "0x0057ce80",
      "0x0057ce80",
      "0x00584300",
      "0x00584300",
      "0x00586410",
      "0x00587a20",
      "0x00587a20",
      "0x0058be50"
    ],
    "conflict_id": "history_budget_semantics",
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
      "0x00586b00",
      "0x00587270",
      "0x00587a20",
      "0x00588570",
      "0x00588570",
      "0x005dda30",
      "0x005737d0",
      "0x005737d0",
      "0x005737d0",
      "0x005737d0",
      "0x00586b00",
      "0x00586b00",
      "0x00586b00",
      "0x00587270",
      "0x00587270",
      "0x00587270"
    ],
    "conflict_id": "manipulator_cancel",
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
      "0x005737d0",
      "0x00588570",
      "0x0058b650",
      "0x00588570",
      "0x0057f3e0",
      "0x005737d0",
      "0x005737d0",
      "0x005737d0",
      "0x00586b00",
      "0x00586b00",
      "0x00587270",
      "0x00587270",
      "0x00587a20",
      "0x00587a20",
      "0x00588570",
      "0x00588570"
    ],
    "conflict_id": "manipulator_types",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
    "resolution_status": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  }
]
```
