# Reconstruction context 0x0060d860

- Status: `partial`
- Content SHA-256: `33d2d4290d5db0bc54d5c1b6b997ec6c8602d7b783e23f2cd29976d0f31c1a1b`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x0060d860",
  "phase": "reconstruction",
  "target": "0x0060d860"
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
  "va": "0x0060d860"
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
  "content_sha256": "8e9fbfa49bf9600b0b9446638fd9e20a11c34e907f2405637c5c2ddc835efec5",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x0060d860 failed: Decompilation did not complete. Reason: ",
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
  "hidden_receiver": "owner of the +0x58 gate",
  "hidden_this_register": "ECX, read at 0x0060d863",
  "ordinary_stack_argument_slots": 2,
  "receiver": true,
  "ret_form": "RET 0x8",
  "return_observation": "0x0060d915 ADD ESP,0x20 / 0x0060d918 RET 0x8 is the only exit and no EAX write is observable on any path.",
  "return_register": null,
  "return_semantics": "no value; the result of the work is observed through the resolved object, which is always released",
  "return_type": "void",
  "return_width_bytes": 0,
  "saved_registers": [
    "ESI"
  ],
  "stack_arguments": [
    {
      "read_at": "0x0060d8e2",
      "role": "argument forwarded to 0x0061fdb0",
      "slot": "entry ESP+4"
    },
    {
      "read_at": "0x0060d86d",
      "role": "mode descriptor pointer passed to 0x00552450",
      "slot": "entry ESP+8"
    }
  ],
  "stack_cleanup_bytes": 8,
  "stack_cleanup_owner": "callee",
  "termination": "0x0060d918 RET 0x8"
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "editor_query_clear_flags_0093db80",
      "reconstructed": true,
      "va": "0x0093db80"
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00acf3e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba4600"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c07480"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c099e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c2ed20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4f160"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cdbd20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cf44c0"
    },
    {
      "name": "DiplomacyTransition_00d065a0",
      "reconstructed": true,
      "va": "0x00d065a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d54330"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00db5e80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x010027b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0102ce30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0105b350"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00acf4a9",
      "direction": "in",
      "other": "0x00acf3e0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00ba
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "void"
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
      "The domain meaning of the keyed work, and whether the AND-based emptiness test ever misfires on real data, need runtime observation.",
      "The virtual release at vtable slot +0x4 can only be resolved with a receiver trace that captures the concrete object's vtable."
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
  "callees": [
    {
      "name": "editor_query_clear_flags_0093db80",
      "reconstructed": true,
      "va": "0x0093db80"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00acf3e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba4600"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c07480"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c099e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c2ed20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4f160"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cdbd20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cf44c0"
    },
    {
      "name": "DiplomacyTransition_00d065a0",
      "reconstructed": true,
      "va": "0x00d065a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d54330"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00db5e80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x010027b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0102ce30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0105b350"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00acf4a9",
      "direction": "in",
      "other": "0x00
[TRUNCATED]
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-10-EDITOR-DISPATCH",
    "score": 3,
    "symbol": "editor_query_clear_flags_0093db80",
    "va": "0x0093db80"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-13-SIM-DIPLOMACY-TRANSITIONS",
    "score": 3,
    "symbol": "DiplomacyTransition_00d065a0",
    "va": "0x00d065a0"
  },
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
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/wave13-w1-core-b07/0060d860_resolve_and_submit_keyed_work.cpp",
    "reconstruction/staging/wave13-w1-core-b07/b07_model_test.cpp",
    "reconstruction/staging/wave13-w1-core-b07/b07_opaque_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-core-b07/0060d860.json"
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
    "Is 0x00421f60 (inside 0x00552450) the step that actually produces the object, or is the virtual call at slot 0? Both appear in the decompilation and the distinction was not settled.",
    "No original-process trace exists for this address.",
    "The 0x30bdee3 constant copied by 0x00552450 is unexplained.",
    "The domain meaning of the keyed work, and whether the AND-based emptiness test ever misfires on real data, need runtime observation.",
    "The receiver passed to 0x0093db80 at 0x0060d8fc is computed as [ESP + 4] after PUSH 0, which static stack arithmetic puts on the PUSH ESI home slot, while 0x0093db80 dereferences receiver + 0x10 and + 0x12 - offsets that only make sense for the key descriptor at frame + 0x0c. Ghidra's decompilation names the receiver local_2. This contradiction is unresolved; the reconstruction passes the descriptor, which is the only reading consistent with the callee.",
    "The virtual release at vtable slot +0x4 can only be resolved with a receiver trace that captures the concrete object's vtable.",
    "What do the descriptor's kind and flags words mean beyond their use? The kind whitelist {0,2,3,4,0xf,0x10,0x11,0x14} and the flag bits 0x2, 0x4, 0x20 are observed, but their semantics are not.",
    "What is the 8-byte key pair at resolved object + 0x18? Nothing in the body or in the callees names it.",
    "Which class is the receiver, and what is the +0x58 gate? Only one of the 15 callers was disassembled and it supplies a global object as the mode descriptor, not the receiver.",
    "W
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-w1-core-b07/0060d860.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b07/0060d860_resolve_and_submit_keyed_work.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b07/b07_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b07/b07_opaque_types.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave13-w1-core-b07/0060d860.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b07/0060d860_resolve_and_submit_keyed_work.cpp",
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
    "reconstruction/knowledge/index
[TRUNCATED]
```
