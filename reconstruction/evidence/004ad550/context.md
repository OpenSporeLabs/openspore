# Reconstruction context 0x004ad550

- Status: `partial`
- Content SHA-256: `dedb87cf5e95866e1ae7cb5fee761473f0f73e0fd824a937b51d9b442c2803e6`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x004ad550",
  "phase": "reconstruction",
  "target": "0x004ad550"
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
  "va": "0x004ad550"
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
  "content_sha256": "24817a1be9118b006a0c58fd7635ecdfaf6930c62561caa5ee34954eadd54264",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x004ad550 failed: Decompilation did not complete. Reason: ",
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
  "hidden_this_register": "ECX, spilled to [EBP-0xb0] at 0x004ad559 and reloaded at each use",
  "ordinary_stack_argument_slots": 2,
  "receiver": true,
  "ret_form": "RET 0x8",
  "return_observation": "the last write to EAX before the epilogue is 0x004ad6e4 MOV EAX,dword ptr [EBP+0x8]. The value is the out parameter, not a status code and not a pointer to the internal accumulator.",
  "return_register": "EAX",
  "return_semantics": "the function returns its own first stack argument unchanged; 0x004ad6e4 MOV EAX,[EBP+0x8] copies the out-parameter pointer into EAX after the copy at 0x004ad6df. The return value carries no information beyond what the caller already passed in.",
  "return_type": "BoundingBox*",
  "return_width_bytes": 4,
  "saved_registers": [
    "EBP"
  ],
  "stack_arguments": [
    {
      "proof": "0x004ad6db PUSH EDX pushes &accumulator and 0x004ad6dc MOV ECX,[EBP+0x8] makes the same slot the thiscall receiver of the final store, so it is the destination; 0x004ad6e4 then returns it",
      "role": "out_bounds",
      "slot": "[EBP+0x8]"
    },
    {
      "proof": "0x004ad653 MOVZX EDX,byte ptr [EBP+0xc] is read as a one-byte flag; the caller at 0x00586ed8/0x00586ee1 pushes a register and a stack address, and the byte slot is the one tested",
      "role": "filter_hidden",
      "slot": "[EBP+0xc]"
    }
  ],
  "stack_cleanup_bytes": 8,
  "stack_cleanup_owner": "callee",
  "termination": "single exit at 0x004ad6ea"
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00409c00"
    },
    {
      "name": "FUN_0044ae00",
      "reconstructed": false,
      "va": "0x0044ae00"
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00574b40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00580700"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00583c50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00586b00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005addb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005ae300"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00574bb4",
      "direction": "in",
      "other": "0x00574b40",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0058072b",
      "direction": "in",
      "other": "0x00580700",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00583e94",
      "direction": "in",
      "other": "0x00583c50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00586ee8",
      "direction": "in",
      "other": "0x00586b00",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005addc6",
      "direction": "in",
      "other": "0x005addb0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005ae348",
      "direction": "in",
      "other": "0x005ae300",
      "reference_type": "direct-call"
    },
    {
 
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "BoundingBox*"
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
      "A differential test must confirm the box is written even when the list is empty, since that is the invariant a caller is most likely to depend on incorrectly.",
      "A trace must confirm that the 100-level ceiling in 0x00435d40 is never reached, i.e. that no rigblock hierarchy in the shipping data is deeper than 100.",
      "A trace must record the actual filter-flag values passed by callers, which is the only way to learn whether the ancestor-chain test is ever active in the shipping build.",
      "No original-process trace exists for this function. Static analysis cannot show whether the rigblock vector is ever empty in a live editor session, which is the only path that produces the inverted sentinel in a caller's box."
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
      "name": null,
      "reconstructed": false,
      "va": "0x00409c00"
    },
    {
      "name": "FUN_0044ae00",
      "reconstructed": false,
      "va": "0x0044ae00"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00574b40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00580700"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00583c50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00586b00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005addb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005ae300"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00574bb4",
      "direction": "in",
      "other": "0x00574b40",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0058072b",
      "direction": "in",
      "other": "0x00580700",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00583e94",
      "direction": "in",
      "other": "0x00583c50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00586ee8",
      "direction": "in",
      "other": "0x00586b00",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005addc6",
      "direction": "in",
      "other": "0x005addb0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005ae348",
      "direction": "i
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
    "reconstruction/staging/wave13-w1-dispatch-b03/editor_model_union_bounds.cpp",
    "reconstruction/staging/wave13-w1-dispatch-b03/editor_model_union_bounds.hpp",
    "reconstruction/staging/wave13-w1-dispatch-b03/editor_model_union_bounds_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-dispatch-b03/004ad550.json"
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
    "A differential test must confirm the box is written even when the list is empty, since that is the invariant a caller is most likely to depend on incorrectly.",
    "A trace must confirm that the 100-level ceiling in 0x00435d40 is never reached, i.e. that no rigblock hierarchy in the shipping data is deeper than 100.",
    "A trace must record the actual filter-flag values passed by callers, which is the only way to learn whether the ancestor-chain test is ever active in the shipping build.",
    "No original-process trace exists for this function. Static analysis cannot show whether the rigblock vector is ever empty in a live editor session, which is the only path that produces the inverted sentinel in a caller's box.",
    "The five uninspected call sites at 0x00574bb4, 0x00583e94, 0x0058072b, 0x005addc6 and the pair at 0x005ae348/0x005ae35d.",
    "The method name. Nothing in the binary or the SDK names it; the reconstruction's name describes the operation, not a recovered identifier.",
    "The owning class. The +0x18 vector matches Spore/Editors/EditorModel.h's mRigblocks exactly and the code region matches, but no vtable was located and there is no RTTI, so the class is a candidate and not a claim.",
    "What the 24-byte box the caller at 0x00586ee8 receives is used for beyond the first float it reads at 0x00586eed; the rest of that caller's use was not followed.",
    "What the filter flag byte means to a caller. Observed only as 'non-zero enables the ancestor-chain test'; no caller's intent was established, and 
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-w1-dispatch-b03/004ad550.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b03/editor_model_union_bounds.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b03/editor_model_union_bounds.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b03/editor_model_union_bounds_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave13-w1-dispatch-b03/004ad550.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b03/editor_model_union_bounds.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b03/editor_model_union_bounds.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b03/editor_model_union_bounds_test.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "re
[TRUNCATED]
```
