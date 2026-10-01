# Reconstruction context 0x00451e50

- Status: `partial`
- Content SHA-256: `eca09c46b63b6f215e01dfbcdc38a9fb8c2e281d9cfbe17073805a2522f7ba0c`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00451e50",
  "phase": "reconstruction",
  "target": "0x00451e50"
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
  "va": "0x00451e50"
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
  "content_sha256": "7e877ab5c4073431fa21e3ead608d45c836bdd1f72230fba3126598e247e1c5d",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00451e50 failed: Decompilation did not complete. Reason: ",
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
  "hidden_receiver": "read",
  "hidden_this_register": "ECX; spilled to [EBP - 0x8] at 0x00451e56 and reloaded three times",
  "ordinary_stack_argument_slots": 1,
  "receiver": true,
  "ret_form": "RET 0x4",
  "return_observation": "There is no write to EAX anywhere in the 17 instructions. At 0x004a675b, 0x004a67ba, 0x004a683c, 0x004a684d, 0x004a6893, 0x004a6947, 0x004a69fd, 0x004a6c15, 0x00495d7e, 0x0048d1e0, 0x004ad4cb and 0x004ad53e the next instruction after the CALL either reloads a register or starts a new statement, and in the two loops at 0x004a6728 and 0x004ad50c the loop increment follows immediately.",
  "return_register": null,
  "return_semantics": "void; no call site reads EAX or AL after the call",
  "return_type": "void",
  "return_width_bytes": 0,
  "saved_registers": [
    "EBP"
  ],
  "stack_arguments": [
    {
      "offset_in_frame": "[EBP + 0x8]",
      "read_at": "0x00451e77",
      "role": "the value propagated into the nested object",
      "signedness": "not narrowed by the body; the value is stored and reloaded as a full dword",
      "slot": 1,
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "callee",
  "termination": "RET 0x4 (MOV ESP,EBP at 0x00451e7d, POP EBP at 0x00451e7f)"
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
      "va": "0x0048d010"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004956b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004a6690"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004ad470"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004ad4e0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x0048d1e0",
      "direction": "in",
      "other": "0x0048d010",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00495d7e",
      "direction": "in",
      "other": "0x004956b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x004a675b",
      "direction": "in",
      "other": "0x004a6690",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x004a67ba",
      "direction": "in",
      "other": "0x004a6690",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x004a683c",
      "direction": "in",
      "other": "0x004a6690",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x004a684d",
      "direction": "in",
      "other": "0x004a6690",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x004a6893",
      "direction": "in",
      "other": "0x004a6690",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x004a6947",
      "direction": "in",
      "other": "0x004a6690",
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
      "A runtime trace is required to determine the runtime value of receiver->[+0x18C] in each editor mode, the runtime class of the nested object, and the runtime content of the +0x38 dword.",
      "No original-process trace has been captured for 0x00451e50. Every claim in this record is static.",
      "The Cell stage has never been entered in any recorded run, so no editor path has a runtime oracle."
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
      "va": "0x0048d010"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004956b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004a6690"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004ad470"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004ad4e0"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x0048d1e0",
      "direction": "in",
      "other": "0x0048d010",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00495d7e",
      "direction": "in",
      "other": "0x004956b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x004a675b",
      "direction": "in",
      "other": "0x004a6690",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x004a67ba",
      "direction": "in",
      "other": "0x004a6690",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x004a683c",
      "direction": "in",
      "other": "0x004a6690",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x004a684d",
      "direction": "in",
      "other": "0x004a6690",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x004a6893",
      "direction": "in",
      "other": "0x004a6690",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x004a6947",
      "direction": "in"
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
    "reconstruction/staging/wave13-w1-dispatch-b05/editor_rigblock_00451e50.cpp",
    "reconstruction/staging/wave13-w1-dispatch-b05/editor_rigblock_00451e50.hpp",
    "reconstruction/staging/wave13-w1-dispatch-b05/editor_rigblock_00451e50_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-dispatch-b05/00451e50.json"
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
    "A runtime trace is required to determine the runtime value of receiver->[+0x18C] in each editor mode, the runtime class of the nested object, and the runtime content of the +0x38 dword.",
    "Do the two flag bits 7 and 11 of the dword array at rigblock + 0xdc8, read at 0x004a6aa7 and 0x004a6b15 by the caller, correlate with this value? The correlation was not analysed.",
    "Is the +0x18C slot a parent, a child, a detour or a sub-asset? The EditorRigblock.h comments around that offset mention 'remove parent?' and a detour helper, but nothing observed here settles it.",
    "Is the propagated value an ordinal, a level, a draw order or a state code? The 1..N assignment at 0x004ad4e0 is consistent with all four and proves only that it is a small non-negative integer in the observed callers.",
    "No original-process trace has been captured for 0x00451e50. Every claim in this record is static.",
    "The Cell stage has never been entered in any recorded run, so no editor path has a runtime oracle.",
    "What class does receiver->[+0x18C] point to? At 0x00495d5x the same pointer is used as `field_18C + 0x1c` for a transform-style call and at 0x0048d010 `*(field_18C + 0x1c)` is dereferenced as a vtable for a slot +0x0c call taking a static and two out-parameters, while `*(field_18C + 0x58)` is used as a further sub-object. None of that identifies the class.",
    "What does the +0x38 dword mean? The observed width rules out the SDK's two-bool layout, and nothing in the read evidence names it.",
    "What is the class of th
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-w1-dispatch-b05/00451e50.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b05/editor_rigblock_00451e50.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b05/editor_rigblock_00451e50.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b05/editor_rigblock_00451e50_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave13-w1-dispatch-b05/00451e50.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b05/editor_rigblock_00451e50.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b05/editor_rigblock_00451e50.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b05/editor_rigblock_00451e50_model_test.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    
[TRUNCATED]
```
