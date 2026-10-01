# Reconstruction context 0x00e57340

- Status: `partial`
- Content SHA-256: `f17231170caa98013034fa0905e76b08753fc3a534ead4d398c176f4c23477b5`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00e57340",
  "phase": "reconstruction",
  "target": "0x00e57340"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "Simulator::Cell::GetScaleDifferenceWithPlayer",
  "package": null,
  "subsystem": "Simulator",
  "va": "0x00e57340"
}
```

## 03_current_status

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "blocked": false,
  "reconstructed": false,
  "runtime_gated": false,
  "runtime_validated": 0,
  "status": "implemented"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "3b3b537bfc2b28dad5d76416de03d0b32e06dd3360d1e80ea4141021c90848f0",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00e57340 failed: Decompilation did not complete. Reason: ",
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
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "original_bytes": 11584,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"ordinary_stack_argument_slots\": [\n      \"entry_ESP+0x4\"\n    ],\n    \"ordinary_stack_arguments\": [\n      {\n        \"entry_offset\": \"entry_ESP+0x4\",\n        \"observed\": true,\n        \"ordinal\": 1,\n        \"read\": false,\n        \"size_inferred\": true,\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      }\n    ],\n    \"ret_form\": \"RET\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"pointer_like_in_EAX\",\n    \"saved_registers\": [\n      \"ESI\"\n    ],\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"entry_ESP+0x4\",\n        \"observed\": true,\n        \"ordinal\": 1,\n        \"read\": false,\n        \"size_inferred\": true,\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      }\n    ],\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"RET\"\n  },\n  \"abstained_because\": [\n    \"receiver_not_determinable: ecx_reassigned_before_deref\",\n    \"receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_reassigned_before_deref), and the convention rule that would apply discriminates on receiver absence\"\n  ],\n  \"cleanup\": {\n    \"bytes\": 0,\n    \"confidence\": \"INFERRED\",\n    \"corroboration\": \"not_available\",\n    \"evidence\": \"ret with no immediate\",\n    \"side\": \"caller\"\n  },\n  \"completeness\": \"PARTIAL\",\n  \"conflicts\": [],\n  \"content_sha256\": \"
[TRUNCATED]
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [],
  "callers": [
    {
      "name": "Simulator::Cell::ShouldNotAttack",
      "reconstructed": false,
      "va": "0x00e57460"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e57ce0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e57fd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e582c0"
    },
    {
      "name": "Simulator::Cell::GetDamageAmount",
      "reconstructed": false,
      "va": "0x00e58980"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e59e50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e5add0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e5c460"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e5d580"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e660e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e67890"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e68470"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e68630"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e6a250"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e6a3f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e6b370"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00e574d0",
      "direction": "in",
      "other":
[TRUNCATED]
```

## 08_types_fields_globals

- State: `missing`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [],
  "vtables": []
}
```

## 09_state_event_relationships

- State: `missing`
- Provenance: `knowledgegraph/research/semantic-decomp.json, reconstruction/knowledge/index.json`

```json
{
  "runtime": {
    "blocking_reason": null,
    "gates": [],
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
      "name": "Simulator::Cell::ShouldNotAttack",
      "reconstructed": false,
      "va": "0x00e57460"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e57ce0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e57fd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e582c0"
    },
    {
      "name": "Simulator::Cell::GetDamageAmount",
      "reconstructed": false,
      "va": "0x00e58980"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e59e50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e5add0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e5c460"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e5d580"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e660e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e67890"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e68470"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e68630"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e6a250"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e6a3f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e6b370"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": 
[TRUNCATED]
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-11-H4-HELPER-WAVE3",
    "score": 6,
    "symbol": "address_window_offset_005c65e0",
    "va": "0x005c65e0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-SIMULATOR-SAFE-WAVE11",
    "score": 6,
    "symbol": "dispatch_key_00628450",
    "va": "0x00628450"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-SIMULATOR-SAFE-WAVE11",
    "score": 6,
    "symbol": "cycle_key_006286a0",
    "va": "0x006286a0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-SIMULATOR-SAFE-WAVE11",
    "score": 6,
    "symbol": "release_child_0062c910",
    "va": "0x0062c910"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 6,
    "symbol": "FUN_00b3d2a0",
    "va": "0x00b3d2a0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 6,
    "symbol": "FUN_00b3d300",
    "va": "0x00b3d300"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 6,
    "symbol": "Simulator_GetUIMissionLogManager",
    "va": "0x00b3d4f0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-13-E4-EMPIRE-WAVE3",
    "score": 6,
    "symbol": "EmpirePoliticalColor_00c32cd0",
    "va": "0x00c32cd0"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__GetScaleDifferenceWithPlayer.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__GetScaleDifferenceWithPlayer.c"
  ],
  "handoffs": [],
  "metadata": []
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
        "0x00e74a20",
        "0x00e57460",
        "0x00e6d200",
        "0x00e57340",
        "0x00e780a0",
        "0x00000108",
        "0x00e74a20",
        "0x00000108"
      ],
      "conflict_id": "TB-FL-012",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": {
        "merge_decision": "separate_entities",
        "preferred_claim": "Use the original direct field/body evidence as the ABI anchor.",
        "preserved_alternatives": true,
        "scope_note": "The current padding is a replacement limitation and cannot define the original structure.",
        "status": "preferred_claim_with_limit",
        "taxonomy": "preferred_claim_with_limit"
      },
      "resolution_status": "preferred_claim_with_limit",
      "source": "knowledgegraph/research/conflicts/track-b-vtable-fields.json",
      "subject": "cCellObjectData original middle fields versus current opaque padding",
      "unresolved_reason": "The cited static evidence leaves the competing owner, slot, layout, or lifecycle interpretation unresolved; no positive original runtime or MSVC RTTI evidence is available."
    }
  ],
  "unresolved_questions": []
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'derived'}, {'mode': 'derived', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'derived'}, {'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__GetScaleDifferenceWithPlayer.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}`

```json
{
  "provenance": [
    {
      "mode": "derived",
      "ref": "GhidraMCP /disassemble_function",
      "source_class": "derived"
    },
    {
      "mode": "derived",
      "ref": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
      "source_class": "derived"
    },
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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__GetScaleDifferenceWithPlayer.c",
      "source_class": "committed_artifact"
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
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.json",
    ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__GetScaleDifferenceWithPlayer.c"
  ],
  "required_categories": [
    "ABI",
    "CALLS",
    "GLO
[TRUNCATED]
```
