# Reconstruction context 0x00c47180

- Status: `partial`
- Content SHA-256: `bd8746c6b7662840c558fcf9020d78e569ebadbb562ab1786aaa5e4a82200966`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00c47180",
  "phase": "reconstruction",
  "target": "0x00c47180"
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
  "va": "0x00c47180"
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
  "content_sha256": "42f908493213f4daa48ce3b4806271707a80f5a93da42a61f63a6fd3126966a7",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00c47180 failed: Decompilation did not complete. Reason: ",
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
  "hidden_receiver": "ECX, read at 0x00c47181",
  "hidden_this_register": "ECX is consumed once; the receiver is then reached only through the address held in ESI.",
  "ordinary_stack_argument_slots": 1,
  "receiver": true,
  "ret_form": "RET 0x4",
  "return_register": null,
  "return_semantics": "No return value. EAX is clobbered by 0x00c471a8 MOV ECX,EAX and is dead on exit.",
  "return_type": "void",
  "return_width_bytes": 0,
  "saved_registers": [
    "ESI"
  ],
  "stack_arguments": [
    {
      "actual_use": "NONE. 0x00B3D2A0 is exactly MOV EAX,dword ptr [0x0167EAE4] ; RET (two instructions, six bytes) and consumes no argument. The pushed word therefore survives 0x00c471a3 and becomes the SECOND stack argument of 0x00BB59B0, which ends in RET 0x8.",
      "declared_use": "PUSH EAX at 0x00c471a2, as an argument to 0x00B3D2A0",
      "index": 0,
      "note": "One dead word pushed and one live word pushed. The compiler folded the unused argument away without removing the push, because the push is what positions the two arguments 0x00BB59B0 needs.",
      "offset_at_entry": "[ESP + 0x4]",
      "read_at": "0x00c4719d MOV EAX,[ESP + 0x8]",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "callee",
  "termination": "single RET 0x4 at 0x00c471b0"
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "FUN_00b3d2a0",
      "reconstructed": true,
      "va": "0x00b3d2a0"
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4b440"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4b7f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4e440"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4f4e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c51010"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c54380"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c557c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c5ea60"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c5f770"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c60e90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c62b30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c63380"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fe9580"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0100e780"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0101246a"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01012aa0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00c4b520",

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
      "No original-process trace exists. A differential run must confirm the occupant's vtable slot +0xC0 does not re-read the receiver's +0x1E8 slot, which is the invariant the clear-before-detach ordering depends on.",
      "The concrete receiver type and the concrete occupant type can only be fixed by observing a vtable pointer in a running process.",
      "Whether the dead argument has any effect requires a run that varies it at a callsite and observes an unchanged result."
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
      "name": "FUN_00b3d2a0",
      "reconstructed": true,
      "va": "0x00b3d2a0"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4b440"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4b7f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4e440"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4f4e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c51010"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c54380"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c557c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c5ea60"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c5f770"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c60e90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c62b30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c63380"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fe9580"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0100e780"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0101246a"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01012aa0"
    },
    {
      "name": null,
   
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
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 3,
    "symbol": "FUN_00b3d2a0",
    "va": "0x00b3d2a0"
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
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-10-EDITOR-DISPATCH",
    "score": 2,
    "symbol": "Editors_EditorModel_SetColor_raw_004ae250",
    "va": "0x004ae250"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/wave13-w1-core-b08/c47180_manager_slot_replace.cpp",
    "reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08.hpp",
    "reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_model_test.cpp",
    "reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_reconstructed.hpp",
    "reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_test_stubs.cpp",
    "reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_test_stubs.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-core-b08/00c47180.json"
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
    "Does 0x00BB59B0 actually use the argument this function pushes? Its first parameter is the manager, so the dead word becomes its `key`, but the reconstruction does not assert what the key does, because 0x00bb59b0's contract was not fully established for that parameter.",
    "Is the write to +0x1E8 a release, a clear-for-replace, or a reset of an owning smart pointer? The body does no reference counting of its own.",
    "No original-process trace exists. A differential run must confirm the occupant's vtable slot +0xC0 does not re-read the receiver's +0x1E8 slot, which is the invariant the clear-before-detach ordering depends on.",
    "The concrete receiver type and the concrete occupant type can only be fixed by observing a vtable pointer in a running process.",
    "Twenty of the twenty-two recorded callsites were not individually disassembled.",
    "What are 0x00baf130, 0x00bbaa60, 0x00bb5930 and 0x00b8de30? They were located inside 0x00bb59b0's body and their ret forms read, but their bodies were not reconstructed.",
    "What class implements the occupant interface with slots +0xBC and +0xC0, and what are those two methods called? The detach/attach reading is inferred from call symmetry only.",
    "What is the object at 0x0167EAE4? 0x00B3D2A0 reads the pointer but this worker never read the dword or found a vtable for it.",
    "What is the owning type of the receiver? No vtable for it was located and the binary has no RTTI. All that is established is the single field at +0x1E8.",
    "Whether the dead argument h
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-w1-core-b08/00c47180.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b08/c47180_manager_slot_replace.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_reconstructed.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_test_stubs.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_test_stubs.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave13-w1-core-b08/00c47180.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b08/c47180_manager_slot_replace.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_model_test.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reco
[TRUNCATED]
```
