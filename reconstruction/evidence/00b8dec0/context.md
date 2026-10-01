# Reconstruction context 0x00b8dec0

- Status: `partial`
- Content SHA-256: `7e8d4888dbeab03b86fe9945903b027932c24a5bfe86f24fa5e9761922c14e94`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00b8dec0",
  "phase": "reconstruction",
  "target": "0x00b8dec0"
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
  "va": "0x00b8dec0"
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
  "content_sha256": "d39399214c42e3dc282b008eb528b7335d500cf3f9d44c76470f31d06dcbaa50",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00b8dec0 failed: Decompilation did not complete. Reason: ",
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
  "hidden_receiver": "owner of the element block at +0x15c",
  "hidden_this_register": "ECX, read at 0x00b8dec0",
  "ordinary_stack_argument_slots": 1,
  "receiver": true,
  "ret_form": "RET 0x4",
  "return_observation": "0x00b8dedd MOV EAX,dword ptr [ECX + EAX*0x4] loads the element into EAX; 0x00b8dee3 XOR EAX,EAX is the only other write, so the return is never a pointer.",
  "return_register": "EAX",
  "return_semantics": "the 4-byte element itself (by value in EAX), or 0 when the index is at or past the element count",
  "return_type": "std::int32_t",
  "return_width_bytes": 4,
  "saved_registers": [],
  "stack_arguments": [
    {
      "read_at": "0x00b8decc",
      "role": "signed 32-bit element index",
      "slot": "entry ESP+4"
    }
  ],
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "callee",
  "termination": "0x00b8dee0 RET 0x4 and 0x00b8dee5 RET 0x4"
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
      "va": "0x00c5c860"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c70260"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c704a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c705c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c71030"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c71040"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c711e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c72030"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c72190"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c737a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c8b820"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c8b920"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c8ba00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c8bb00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c8c5d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c8c7f0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00c5cb9d",
      "direction": "in",
      "other": "0x00c5c860",
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
    "std::int32_t"
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
      "The element type and the owning class can only be settled with a receiver trace or by inspecting the 22 remaining call sites."
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
      "va": "0x00c5c860"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c70260"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c704a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c705c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c71030"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c71040"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c711e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c72030"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c72190"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c737a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c8b820"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c8b920"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c8ba00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c8bb00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c8c5d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c8c7f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c8c9d0"
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
    "reconstruction/staging/wave13-w1-core-b07/00b8dec0_indexed_element_accessor.cpp",
    "reconstruction/staging/wave13-w1-core-b07/b07_model_test.cpp",
    "reconstruction/staging/wave13-w1-core-b07/b07_opaque_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-core-b07/00b8dec0.json"
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
    "Do any of the 22 uninspected callers pass a negative index? The one caller that was disassembled does not; the others are unknown.",
    "Is the +0x164 word (a capacity pointer in a three-pointer vector layout) also maintained by the container? It is never read here, so the reconstruction does not model it.",
    "Is the zero out-of-range answer relied upon as a sentinel by the callers, or is it merely a discarded value? Not established.",
    "No original-process trace exists for this address.",
    "The element type and the owning class can only be settled with a receiver trace or by inspecting the 22 remaining call sites.",
    "What is the element type? A single caller dereferences it and reads +0x14; the other 22 callsites were not inspected and no common type was established.",
    "Which class owns the block? The one disassembled thunk shows owner+0x13c, but no vtable or SDK type was located for that owner."
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-w1-core-b07/00b8dec0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b07/00b8dec0_indexed_element_accessor.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b07/b07_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b07/b07_opaque_types.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave13-w1-core-b07/00b8dec0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b07/00b8dec0_indexed_element_accessor.cpp",
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
    "reconstruction/knowledge/index.json
[TRUNCATED]
```
