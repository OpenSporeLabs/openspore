# Reconstruction context 0x00bca0c0

- Status: `partial`
- Content SHA-256: `608cd59ef8d74bf102a09a1d810e4d29ebb49c4137574de97941b328496b130b`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00bca0c0",
  "phase": "reconstruction",
  "target": "0x00bca0c0"
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
  "va": "0x00bca0c0"
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
  "content_sha256": "7e1063a25438f0ddf4a033b1507f5f79626e8414d96703f1e369ce33e59ede8a",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00bca0c0 failed: Decompilation did not complete. Reason: ",
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
  "hidden_receiver": "owner of the eight-slot record table at +0x20",
  "hidden_this_register": "ECX, read at 0x00bca0cf",
  "ordinary_stack_argument_slots": 4,
  "receiver": true,
  "ret_form": "RET 0x10",
  "return_observation": "0x00bca105 MOVZX EAX,word ptr [EAX + -0x8] loads 16 bits only, 0x00bca10a SHL EDX,0x10 and 0x00bca10e OR EAX,EDX assemble the packed value, and 0x00bca0fe OR EAX,0xffffffff is the not-found answer.",
  "return_register": "EAX",
  "return_semantics": "the matched record's 16-bit identifier in bits 0..15 with the slot index in bits 16..31, or 0xffffffff when no record matches",
  "return_type": "std::uint32_t",
  "return_width_bytes": 4,
  "saved_registers": [
    "EBX",
    "ESI",
    "EDI"
  ],
  "stack_arguments": [
    {
      "read_at": "0x00bca0c1",
      "role": "key1, compared at 0x00bca0d8 against record+0x04",
      "slot": "entry ESP+4"
    },
    {
      "read_at": "0x00bca0cb",
      "role": "key2, compared at 0x00bca0dd against record+0x08",
      "slot": "entry ESP+8"
    },
    {
      "read_at": "0x00bca0c6",
      "role": "key3, compared at 0x00bca0e5 against record+0x1c only when non-zero",
      "slot": "entry ESP+0xc"
    },
    {
      "read_at": "0x00bca0d2",
      "role": "key4, compared at 0x00bca0ee against record+0x20 only when non-zero",
      "slot": "entry ESP+0x10"
    }
  ],
  "stack_cleanup_bytes": 16,
  "stack_cleanup_owner": "callee",
  "termination": "0x00bca102 RET 0x10 and 0x00bca111 RET 0x10"
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
      "va": "0x00ba48b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c05a80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c07480"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c09410"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c0c630"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c0e6a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c20230"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c238b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cdcb10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d1e720"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d2ffd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d4b2f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d697a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d8e8d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d9b110"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00da6b10"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00ba49e9",
      "direction": "in",
      "other": "0x00ba48b0",
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
    "std::uint32_t"
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
      "No original-process trace exists for this address.",
      "The record semantics and the owning class can only be settled with a receiver trace or by locating a writer of the eight records."
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
      "va": "0x00ba48b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c05a80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c07480"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c09410"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c0c630"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c0e6a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c20230"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c238b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cdcb10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d1e720"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d2ffd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d4b2f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d697a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d8e8d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d9b110"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00da6b10"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00ba49e9",
      "directi
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
    "reconstruction/staging/wave13-w1-core-b07/00bca0c0_fixed_table_lookup.cpp",
    "reconstruction/staging/wave13-w1-core-b07/b07_model_test.cpp",
    "reconstruction/staging/wave13-w1-core-b07/b07_opaque_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-core-b07/00bca0c0.json"
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
    "Do the remaining 15 callers use the identifier and slot index, or only the found/not-found bit like 0x00ba48b0? Not established.",
    "Is the table ever mutated after construction (so that the linear search and the fixed count stay valid)? No writer was located in this batch.",
    "No original-process trace exists for this address.",
    "The record semantics and the owning class can only be settled with a receiver trace or by locating a writer of the eight records.",
    "What are the four key fields and the 16-bit identifier? Nothing in the body or in the one inspected caller names them.",
    "What lives in the unobserved 0x10 bytes at record+0x0c..+0x1b and the 0x20 bytes at record+0x24..+0x43? The body never reads them.",
    "Which class owns the table? The one caller passes a sub-object pointer found at its own +0xb48; no vtable was located."
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-w1-core-b07/00bca0c0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b07/00bca0c0_fixed_table_lookup.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b07/b07_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b07/b07_opaque_types.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave13-w1-core-b07/00bca0c0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b07/00bca0c0_fixed_table_lookup.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b07/b07_model_test.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b07/b07_opaque_types.hpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.json"
  ],
[TRUNCATED]
```
