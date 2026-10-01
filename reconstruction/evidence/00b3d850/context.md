# Reconstruction context 0x00b3d850

- Status: `partial`
- Content SHA-256: `e07dfa2a6549e35d9cec8b9ac54ab5082c83e57c881edc06af1378c5db4368f6`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00b3d850",
  "phase": "reconstruction",
  "target": "0x00b3d850"
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
  "va": "0x00b3d850"
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
  "content_sha256": "2c8f51a803f69d4c2db519750b2898bc1efff9561b559a9e7039f8cc79e2d839",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00b3d850 failed: Decompilation did not complete. Reason: ",
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
  "hidden_this_register": "ECX, read at 0x00b3d851; ECX is then reloaded at 0x00b3d860 with self+0x8 for the port call",
  "ordinary_stack_argument_slots": 0,
  "receiver": true,
  "ret_form": "RET",
  "return_observation": "0x00b3d86c MOV EAX,ESI is the only write to EAX and it is reached by both exits - the exhaustion path via 0x00b3d85b JZ 0x00b3d86c and the accepted path by falling through - so the return is unconditionally the receiver and the callee's AL result is never propagated.",
  "return_register": "EAX",
  "return_semantics": "the receiver itself, on both exits",
  "return_type": "OpaqueCursor*",
  "return_width_bytes": 4,
  "saved_registers": [
    {
      "pop": "0x00b3d86e",
      "push": "0x00b3d850",
      "register": "ESI"
    }
  ],
  "stack_arguments": [],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "RET at 0x00b3d86f"
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
      "va": "0x00b41a40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c07480"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d35190"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d41a70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d4b860"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d522c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d66600"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d6ef50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d6f090"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d6f1c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d8b910"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d8bb70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d8c3e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d8c850"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d8c9c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d8cab0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00b41a66",
      "direction": "in",
      "other": "0x00b41a40",
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
    "OpaqueCursor*"
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
      "A runtime trace would be needed to observe the element type, to see which of the port's four conditions actually rejects elements in play, and to check whether any caller ever presents a cursor equal to its end.",
      "No original-process trace exists for 0x00b3d850; every claim is static.",
      "The identity of the ctx object and of its vtable slot +0x2c can only be resolved with a receiver whose vtable base is known at run time."
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
      "va": "0x00b41a40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c07480"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d35190"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d41a70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d4b860"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d522c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d66600"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d6ef50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d6f090"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d6f1c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d8b910"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d8bb70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d8c3e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d8c850"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d8c9c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d8cab0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d8d300"
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
    "reconstruction/staging/wave13-pilot-core-b01/b3d850_cursor_advance.cpp",
    "reconstruction/staging/wave13-pilot-core-b01/wave13_pilot_core_b01_model_test.cpp",
    "reconstruction/staging/wave13-pilot-core-b01/wave13_pilot_core_b01_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-pilot-core-b01/00b3d850.json"
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
    "A runtime trace would be needed to observe the element type, to see which of the port's four conditions actually rejects elements in play, and to check whether any caller ever presents a cursor equal to its end.",
    "Do all 18 callers maintain cursor < end on entry? Only the two inspected callers were checked, and both do. The other 16 were not, and the function has no guard.",
    "Is the range [cursor, end) guaranteed to be non-empty? If a caller presents cursor == end the function walks off the buffer. Whether that ever happens in the shipping game is not determinable statically.",
    "No original-process trace exists for 0x00b3d850; every claim is static.",
    "The identity of the ctx object and of its vtable slot +0x2c can only be resolved with a receiver whose vtable base is known at run time.",
    "What class does the ctx object belong to? The four field offsets (+0xb58, +0x135, +0x110) and a vtable slot at +0x2c describe a large Simulator object, but no vtable was located for it and the SDK offers no candidate, so the port's subject is unresolved.",
    "What do the port's four conditions mean? ctx->vslot_0x2c() must be zero, bit 9 of the dword at +0xb58 must be zero, the byte at +0x135 must be non-zero, and bit 4 of the byte at +0x110 must be zero. None of these is named in the SDK, and the four are read from an object this function never identifies.",
    "What is the element type? The handle's stride of four bytes and the unconditional dereference prove the elements are 4-byte values, but whether they are
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-pilot-core-b01/00b3d850.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-pilot-core-b01/b3d850_cursor_advance.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-pilot-core-b01/wave13_pilot_core_b01_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-pilot-core-b01/wave13_pilot_core_b01_types.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave13-pilot-core-b01/00b3d850.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-pilot-core-b01/b3d850_cursor_advance.cpp",
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
    "recons
[TRUNCATED]
```
