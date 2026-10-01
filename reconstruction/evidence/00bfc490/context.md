# Reconstruction context 0x00bfc490

- Status: `partial`
- Content SHA-256: `e4c57c2b130549ab27f90ec15e56a85ce24364609e03007a8ec810f3c2d1f75b`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00bfc490",
  "phase": "reconstruction",
  "target": "0x00bfc490"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": null,
  "package": null,
  "subsystem": null,
  "va": "0x00bfc490"
}
```

## 03_current_status

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "blocked": false,
  "reconstructed": false,
  "runtime_gated": true,
  "runtime_validated": 0,
  "status": "unresolved"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "81920f55c0245202b74be2475b1e07884ec73aed5e10e3dacf6dfe6c909f0692",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00bfc490 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "__thiscall",
  "hidden_this_register": "ECX, read once at 0x00bfc491 and never written",
  "ordinary_stack_argument_slots": 0,
  "receiver": true,
  "ret_form": "RET",
  "return_observation": "0x00bfc49a is FDIVR float ptr [ESI + 0x38], an x87 divide whose only writer of the result is the x87 stack. No EAX or XMM0 write appears in the body, which is why the Ghidra decompilation declares a float10 return and casts it to float; the observed writer is the FPU, not a general-purpose register.",
  "return_register": "ST0",
  "return_semantics": "x87 extended-precision value in ST0",
  "return_type": "float",
  "return_width_bytes": 10,
  "saved_registers": [
    {
      "pop": "0x00bfc49d",
      "push": "0x00bfc490",
      "register": "ESI"
    }
  ],
  "stack_arguments": [],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "RET at 0x00bfc49e"
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
      "va": "0x00b188b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b685e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bd8660"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c02df0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c0ba30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c0ba70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c0bab0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c0bb90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c22ae0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c23e90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c26170"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c9cfd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c9e700"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ccc640"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ccefb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cd0830"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00b1891b",
      "direction": "in",
      "other": "0x00b188b0",
      "reference_type": "direct-call"
    },

[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "float"
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
      "A runtime trace would be needed to see which override of slot +0x58 is reached for a real creature, to observe the actual return values of the ratio in play, and to check whether the divisor is ever zero.",
      "No original-process trace exists for 0x00bfc490; every claim is static.",
      "The runtime values of the six threshold and scale globals cannot be recovered statically because they are zero in the file image."
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
      "va": "0x00b188b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b685e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bd8660"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c02df0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c0ba30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c0ba70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c0bab0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c0bb90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c22ae0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c23e90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c26170"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c9cfd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c9e700"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ccc640"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ccefb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cd0830"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ce8d00"
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
      "same_calling_convention"
    ],
    "package": "PKG-APP-SAFE-WAVE11",
    "score": 2,
    "symbol": "property_record_assign_pair_004279d0",
    "va": "0x004279d0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-APP-SAFE-WAVE11",
    "score": 2,
    "symbol": "property_record_assign_scalar_00428060",
    "va": "0x00428060"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-EDITOR-SAFE-WAVE11",
    "score": 2,
    "symbol": "editor_paint_commit_0043ac40",
    "va": "0x0043ac40"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-APP-SAFE-WAVE11",
    "score": 2,
    "symbol": "model_parts_apply_properties_00447150",
    "va": "0x00447150"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-APP-SAFE-WAVE11",
    "score": 2,
    "symbol": "pair_vector_insert_004786e0",
    "va": "0x004786e0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-EDITOR-SAFE-WAVE11",
    "score": 2,
    "symbol": "editor_entry_expand_004ad6f0",
    "va": "0x004ad6f0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-10-EDITOR-DISPATCH",
    "score": 2,
    "symbol": "Editors_EditorModel_SetColor_raw_004ae250",
    "va": "0x004ae250"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-APP-SAFE-WAVE11",
    "score": 2,
    "symbol": "pair_vector_construct_004b62a0",
    "va": "0x004b62a0"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/wave13-pilot-core-b01/bfc490_combatant_ratio.cpp",
    "reconstruction/staging/wave13-pilot-core-b01/wave13_pilot_core_b01_model_test.cpp",
    "reconstruction/staging/wave13-pilot-core-b01/wave13_pilot_core_b01_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-pilot-core-b01/00bfc490.json"
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
        "0x00e7a4a0",
        "0x00e7a7c0",
        "0x00e7a7c0",
        "0x00e7e6c0",
        "0x00e7a4a0",
        "0x00e7a4a0",
        "0x00e62340",
        "0x00e52910",
        "0x00e7a7c0",
        "0x00e7a7c0",
        "0x00bfc460",
        "0x00bfc460",
        "0x00bfc490",
        "0x00bfc490",
        "0x00bfc4a0",
        "0x00bfc4a0"
      ],
      "conflict_id": "cell_field_112_semantics",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The cited direct body establishes a bounded state mutation or call anchor, but the full transition policy, consumer order, and runtime reachability remain unresolved.",
      "resolution_status": "The cited direct body establishes a bounded state mutation or call anchor, but the full transition policy, consumer order, and runtime reachability remain unresolved.",
      "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
      "subject": null,
      "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
    },
    {
      "anchors": [
        "0x00bfc460",
        "0x00bfc540",
        "0x00bfc460",
        "0x00e7e6c0",
        "0x00e7a4a0",
        "0x00e52910",
        "0x00e7a7c0",
        "0x00bfc460",
        "0x00bfc460",
        "0x00bfc490",
        "0x00bfc490",
        "0x00bfc4a0",
        "0x00bfc4a0",
        "0x00bfc540",
        "0x00bfc540",
        "0x00bfc540"
      ],
      "conflict_id": "creature_death_publication",
      "kind": "conflict_ledger",
      "reje
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-pilot-core-b01/00bfc490.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-pilot-core-b01/bfc490_combatant_ratio.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-pilot-core-b01/wave13_pilot_core_b01_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-pilot-core-b01/wave13_pilot_core_b01_types.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave13-pilot-core-b01/00bfc490.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-pilot-core-b01/bfc490_combatant_ratio.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-pilot-core-b01/wave13_pilot_core_b01_model_test.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-pilot-core-b01/wave13_pilot_core_b01_types.hpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "recon
[TRUNCATED]
```
