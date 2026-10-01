# Reconstruction context 0x00c372b0

- Status: `partial`
- Content SHA-256: `163eae126a1c91ea7ec54d0bd9c478600e7c5fba8aba7ff7f5bd2d3d431bce2d`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00c372b0",
  "phase": "reconstruction",
  "target": "0x00c372b0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00c372b0",
  "package": "pkg-this-adjustor-fwd",
  "subsystem": "Unknown",
  "va": "0x00c372b0"
}
```

## 03_current_status

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "blocked": false,
  "reconstructed": true,
  "runtime_gated": false,
  "runtime_validated": 0,
  "status": "reconstructed"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "004c39062e5e8dd44fcb8ed6fa3e1d0bae1c0f9f4404e83bc4bf5bf2eae62cb9",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00c372b0 failed: Decompilation did not complete. Reason: ",
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
  "hidden_this": true,
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": 0,
  "receiver_register": "ECX",
  "ret_form": "RET",
  "return_register": "AL (one byte)",
  "return_semantics": "one byte in AL, forwarded from the tail target",
  "return_type": "std::uint8_t",
  "saved_registers": [],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "JMP 0x00feba90"
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
      "va": "0x00c5d640"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c5da10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ffa2c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ffabc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ffc5b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0102c0c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0102c1a0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00c5d6ec",
      "direction": "in",
      "other": "0x00c5d640",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c5da88",
      "direction": "in",
      "other": "0x00c5da10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00ffa455",
      "direction": "in",
      "other": "0x00ffa2c0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00ffacc1",
      "direction": "in",
      "other": "0x00ffabc0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00ffc5b7",
      "direction": "in",
      "other": "0x00ffc5b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0102c150",
      "direction": "in",
      "other": "0x0102c0c0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0102c2be",
      "direction": "in",
      "other": "0x0102c1a0",
      "referenc
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "std::uint8_t"
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
  "callees": [],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c5d640"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c5da10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ffa2c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ffabc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ffc5b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0102c0c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0102c1a0"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00c5d6ec",
      "direction": "in",
      "other": "0x00c5d640",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c5da88",
      "direction": "in",
      "other": "0x00c5da10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00ffa455",
      "direction": "in",
      "other": "0x00ffa2c0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00ffacc1",
      "direction": "in",
      "other": "0x00ffabc0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00ffc5b7",
      "direction": "in",
      "other": "0x00ffc5b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0102c150",
      "direction": "in",
      "other": "0x0102c0c0",
      "reference_type": "direct-call"
    },
    {
      "callsite"
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
    "reconstruction/staging/pkg-this-adjustor-fwd/this_adjustor_fwd.cpp",
    "reconstruction/staging/pkg-this-adjustor-fwd/this_adjustor_fwd.hpp",
    "reconstruction/staging/pkg-this-adjustor-fwd/this_adjustor_fwd_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-this-adjustor-fwd/00c372b0.json"
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
    "The class identity of the receiver is not established. The machine evidence shows a this-adjustor thunk reaching a sub-object 0x7b8 bytes above the incoming this, which is the shape of a secondary base in a multiple-inheritance layout, but no class name, no base-class list, and no layout is claimed. The tail target 0x00feba90 is a slot of four vptr-backed vftables, which establishes 'a virtual member of some class' and nothing more.",
    "The upper three bytes of the return register are undefined. The tail target writes AL only, so the thunk's return value is one byte wide and the upper bits are whatever the caller left there. The declared std::uint8_t promises only the low byte; no claim is made about the upper three."
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-this-adjustor-fwd/00c372b0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-this-adjustor-fwd/this_adjustor_fwd.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-this-adjustor-fwd/this_adjustor_fwd.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-this-adjustor-fwd/this_adjustor_fwd_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-this-adjustor-fwd/00c372b0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-this-adjustor-fwd/this_adjustor_fwd.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-this-adjustor-fwd/this_adjustor_fwd.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-this-adjustor-fwd/this_adjustor_fwd_model_test.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge
[TRUNCATED]
```
