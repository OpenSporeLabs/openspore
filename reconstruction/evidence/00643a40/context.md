# Reconstruction context 0x00643a40

- Status: `partial`
- Content SHA-256: `2b203dc1e8530dfc973ba695e3e578aba617b1c7d617f2d309bf3799236b306c`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00643a40",
  "phase": "reconstruction",
  "target": "0x00643a40"
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
  "va": "0x00643a40"
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
  "content_sha256": "d6ed523f85d2764e60515a053d4f5648c6b6534ae0be40e702a671755a48fe79",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00643a40 failed: Decompilation did not complete. Reason: ",
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
  "hidden_receiver": "container",
  "hidden_this_register": "ECX, read at 0x00643a40 and 0x00643a48",
  "ordinary_stack_argument_slots": 1,
  "receiver": true,
  "ret_form": "RET 0x4",
  "return_observation": "0x00643ab3 LEA EAX,[EDX + 0x14] on the hit path and 0x00643aa1 MOV EAX,dword ptr [ESP + 0x18] + 0x00643aa5 ADD EAX,0x14 on the miss path. Callers dereference the result as a 4-byte value (0x00643df7 MOV EAX,dword ptr [EAX]; 0x00644521 MOV dword ptr [EAX],ECX).",
  "return_register": "EAX",
  "return_semantics": "address of the 4-byte mapped slot of the matching (or newly inserted) node",
  "return_type": "std::uint32_t",
  "return_width_bytes": 4,
  "saved_registers": [
    "EBP",
    "ESI",
    "EDI"
  ],
  "stack_arguments": [
    {
      "read_at": "0x00643a4c",
      "role": "pointer to the 4-byte key; the same word is reused as the out-slot the insert port publishes the created node into (0x00643a7b zeroes it, 0x00643aa1 reloads it)",
      "slot": "entry ESP+4"
    }
  ],
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "callee",
  "termination": "0x00643aae RET 0x4 and 0x00643aba RET 0x4"
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
      "name": "Editors::cEditor::Initialize",
      "reconstructed": false,
      "va": "0x00584300"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00643db0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00644510"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00644530"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0066b0c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00a18d90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b32190"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b32220"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b32250"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b32280"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b322c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00baf790"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be1150"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be11f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be2110"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be32b0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00584383",
      "direction": "in",
      "other": "0x00584300",
      "reference_ty
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
      "A runtime differential test would be needed to confirm that the reserved-key rejection in 0x00643db0 and the registration in cEditor::Initialize are reproduced, and that no runtime patch retargets the container.",
      "No original-process trace exists for this address; every claim is static.",
      "The identity of the owning class can only be settled with a receiver trace or a located vtable."
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
      "name": "Editors::cEditor::Initialize",
      "reconstructed": false,
      "va": "0x00584300"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00643db0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00644510"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00644530"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0066b0c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00a18d90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b32190"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b32220"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b32250"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b32280"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b322c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00baf790"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be1150"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be11f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be2110"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be32b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be32f0"
    },
    {
      "n
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
    "reconstruction/staging/wave13-w1-core-b07/00643a40_eastl_map_find_or_insert.cpp",
    "reconstruction/staging/wave13-w1-core-b07/b07_model_test.cpp",
    "reconstruction/staging/wave13-w1-core-b07/b07_opaque_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-core-b07/00643a40.json"
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
    "A runtime differential test would be needed to confirm that the reserved-key rejection in 0x00643db0 and the registration in cEditor::Initialize are reproduced, and that no runtime patch retargets the container.",
    "In the 0x006432d0 path that reaches 0x00579bd0 instead of 0x00579b50, the published node appears to be written into the value pair rather than the argument word, which would leave the 0x00643aa1 reload reading the zeroed word. Static stack arithmetic does not settle which write the compiler contracted for; the primary path is settled, this one is not.",
    "No original-process trace exists for this address; every claim is static.",
    "The container word at +0x00 and the node word at +0x0c are unobserved here, so their identity (comparator, allocator, colour) is inferred from the EASTL header rather than read.",
    "The identity of the owning class can only be settled with a receiver trace or a located vtable.",
    "What do the 4-byte keys and mapped values denote? The observed values look like class-name hashes but nothing in the binary names the registry.",
    "Whether the 0xffffff00 masking the decompiler shows on the argument pointer (an artefact of the byte-sized zeroing at 0x00643a7b) has any effect on keys whose address is not 256-byte aligned. Every inspected callsite passes a stack address, which is not 256-byte aligned in general, so the port keeps the observed behaviour of zeroing the low byte of the argument word.",
    "Which class owns each container? Four different sub-offsets (+0x10, +
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-w1-core-b07/00643a40.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b07/00643a40_eastl_map_find_or_insert.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b07/b07_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b07/b07_opaque_types.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave13-w1-core-b07/00643a40.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b07/00643a40_eastl_map_find_or_insert.cpp",
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
