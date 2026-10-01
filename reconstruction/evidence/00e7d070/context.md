# Reconstruction context 0x00e7d070

- Status: `partial`
- Content SHA-256: `43db28b31980995eda84164149b39fea4a5df06439058912398c013ba8dac248`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00e7d070",
  "phase": "reconstruction",
  "target": "0x00e7d070"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00e7d070",
  "package": null,
  "subsystem": "Simulator",
  "va": "0x00e7d070"
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
  "status": "candidate"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "fb7ca69d50279cbf3720e24b0c0f0f7e1f6146dd76081852786e97bf57ebf503",
  "live_attempts": [],
  "live_requested": false,
  "overall": "PERSISTED"
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
  "calling_convention": null,
  "hidden_this": null,
  "receiver": "NOT CLAIMED, IN EITHER DIRECTION. The record declines to name one: receiver {present null, register null, reason ecx_reassigned_before_deref, confidence UNKNOWN, bounds_only true, offsets [], distinct_offsets 0, written_through 0}. Nothing in this package treats any register as `this`, and no receiver type, class, object size, vtable identity, field or layout is asserted anywhere.",
  "receiver_register": null,
  "ret_form": "RET",
  "return_register": "ST0",
  "return_semantics": "float_or_x87_in_ST0",
  "saved_registers": [
    "EBP",
    "EBX",
    "EDI",
    "ESI"
  ],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "RET"
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "embedded_object_first_word_init_00743b50",
      "reconstructed": true,
      "va": "0x00743b50"
    },
    {
      "name": "Simulator::Cell::cCellUI::ShowHealthRollover",
      "reconstructed": false,
      "va": "0x00e62340"
    }
  ],
  "callers": [
    {
      "name": "cell_mode_strategy_on_mouse_wheel_00e7d660",
      "reconstructed": true,
      "va": "0x00e7d660"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e7d760"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e81120"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00e7d6f8",
      "direction": "in",
      "other": "0x00e7d660",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7d77e",
      "direction": "in",
      "other": "0x00e7d760",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e816c2",
      "direction": "in",
      "other": "0x00e81120",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e816fd",
      "direction": "in",
      "other": "0x00e81120",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7d09b",
      "direction": "out",
      "other": "0x00743b50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7d090",
      "direction": "out",
      "other": "0x00b72210",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7d348",
      "direction": "out",
      "other": "0x00e394f0",
      "reference_type": "direct-call"
    },
    {
      "callsite":
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "openspore::reconstruction::pkg_w2_00e7d2c0::BlockOutcome",
    "openspore::reconstruction::pkg_w2_00e7d2c0::Byte",
    "openspore::reconstruction::pkg_w2_00e7d2c0::StackWindow",
    "openspore::reconstruction::pkg_w2_00e7d2c0::TailArguments",
    "openspore::reconstruction::pkg_w2_00e7d2c0::Word"
  ],
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
  "callees": [
    {
      "name": "embedded_object_first_word_init_00743b50",
      "reconstructed": true,
      "va": "0x00743b50"
    },
    {
      "name": "Simulator::Cell::cCellUI::ShowHealthRollover",
      "reconstructed": false,
      "va": "0x00e62340"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": "cell_mode_strategy_on_mouse_wheel_00e7d660",
      "reconstructed": true,
      "va": "0x00e7d660"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e7d760"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e81120"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00e7d6f8",
      "direction": "in",
      "other": "0x00e7d660",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7d77e",
      "direction": "in",
      "other": "0x00e7d760",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e816c2",
      "direction": "in",
      "other": "0x00e81120",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e816fd",
      "direction": "in",
      "other": "0x00e81120",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7d09b",
      "direction": "out",
      "other": "0x00743b50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7d090",
      "direction": "out",
      "other": "0x00b72210",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7d348",
      "direction": "out",
      "other
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
  "files": [
    "reconstruction/staging/pkg-w2-00e7d2c0/bounded_block_00e7d2c0.cpp",
    "reconstruction/staging/pkg-w2-00e7d2c0/bounded_block_00e7d2c0.hpp",
    "reconstruction/staging/pkg-w2-00e7d2c0/bounded_block_00e7d2c0_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-w2-00e7d2c0/00e7d2c0.json"
  ]
}
```

## 13_semantic_hypotheses

- State: `missing`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

## 14_conflicts_questions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json, knowledgegraph/research/semantic-decomp.json`

```json
{
  "conflicts": [],
  "unresolved_questions": [
    "Is ESI provably zero on every path that reaches 0x00e7d2b7? The listing has exactly one definition of ESI, `XOR ESI,ESI` at 0x00e7d23d, and it dominates this block by inspection, but no dominator computation was run and the model does not depend on it.",
    "Is the enclosing function variadic? The record lists variadic_suspected and variadic_not_decidable_from_listing and states that the suspicion removes any guarantee about the stack-argument extent. The block's own five words are accounted for; the function's are not.",
    "Is this body a virtual member of some class, and of which? The record declines to name a receiver and the body contains no indirect transfer, so nothing in this repository places it in a class or a slot.",
    "What do the two selector immediates 0x9ef61113 and 0xac7161b5 mean, and what does the callee at 0x00e394f0 do with them? The two-arm shape is established; the meaning of either arm is not.",
    "What is the enclosing function FUN_00e7d070 for? Its decompilation was never collected, eleven callees are unresolved, and 203 of its 224 instructions are untranscribed here.",
    "What is the word at the absolute address 0x016b3c04, and what object does it point at? The block reads it and then reads 0x5190 bytes into the result, but no type, size, class or lifetime for either is established here and none is guessed.",
    "Why does the CALLS oracle see no callee for this VA? The xref export keys rows on 0x00e7d070, the function's real entry, and carries no row for the interior address 0x00e7d2c0,
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-w2-00e7d2c0/00e7d2c0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-w2-00e7d2c0/bounded_block_00e7d2c0.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-w2-00e7d2c0/bounded_block_00e7d2c0.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-w2-00e7d2c0/bounded_block_00e7d2c0_model_test.cpp', 'source_class': 'committed_artifact'}`

```json
{
  "provenance": [
    {
      "mode": "derived",
      "ref": "ephemeral reconstruction_knowledge.build_index",
      "source_class": "generated_index"
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
      "ref": "reconstruction/metadata/pkg-w2-00e7d2c0/00e7d2c0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-w2-00e7d2c0/bounded_block_00e7d2c0.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-w2-00e7d2c0/bounded_block_00e7d2c0.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-w2-00e7d2c0/bounded_block_00e7d2c0_model_test.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.json"
  ],
  "required_categories": [
    "ABI",
    "CALLS",
    "GLOBALS",
    "FIELDS/OFFSETS",
    "CONSTANTS",
    "CONTROL FLOW",
    "VIRTUAL DISPATCH",
    "RETURN SEMANTICS",
    "EVIDENCE COVERAGE"
  ]
}
```
