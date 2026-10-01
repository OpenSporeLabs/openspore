# Reconstruction context 0x004b09b0

- Status: `partial`
- Content SHA-256: `54253bbe0d31e21c5df06fa3d1081332815f0c360be4933da4232ca8916293a3`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x004b09b0",
  "phase": "reconstruction",
  "target": "0x004b09b0"
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
  "va": "0x004b09b0"
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
  "content_sha256": "0034d4ded0add813607a7eef36549a4523a97c54848085110f10770de6f7faf1",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x004b09b0 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "__thiscall (receiver in ECX, one stack argument, callee pops it)",
  "hidden_receiver": "ECX",
  "hidden_this_register": "ECX is read only by the spill at 0x004b09b6 and then served from the frame",
  "ordinary_stack_argument_slots": 1,
  "receiver": true,
  "ret_form": "RET 0x4",
  "return_note": "(the receiver)",
  "return_observation": "0x004b09f9: MOV EAX,[EBP-8] where [EBP-8] was written from ECX at 0x004b09b6, so the result is always the receiver and is never derived from either pointer argument. The early exit at 0x004b09c1 jumps to the same 0x004b09f9, so the self-assignment case returns the holder too.",
  "return_register": "EAX",
  "return_semantics": "the holder itself, not the assigned pointer and not a status; 0x004b09f9 loads [EBP-8] into EAX, i.e. the address the caller passed in ECX",
  "return_type": "IntrusiveRefHolder*",
  "return_width_bytes": 4,
  "saved_registers": [
    "EBP"
  ],
  "stack_arguments": [
    {
      "offset": "[EBP+8]",
      "role": "the incoming pointer",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "callee",
  "termination": "single RET 0x4 at 0x004b09ff"
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
      "va": "0x004b0590"
    },
    {
      "name": "editor_input_005737d0",
      "reconstructed": true,
      "va": "0x005737d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00573c00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0057e790"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00582250"
    },
    {
      "name": "editor_input_00588570",
      "reconstructed": true,
      "va": "0x00588570"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x004b06c3",
      "direction": "in",
      "other": "0x004b0590",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005738e6",
      "direction": "in",
      "other": "0x005737d0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00573cd0",
      "direction": "in",
      "other": "0x00573c00",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0057e843",
      "direction": "in",
      "other": "0x0057e790",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005824ce",
      "direction": "in",
      "other": "0x00582250",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00588afb",
      "direction": "in",
      "other": "0x00588570",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00588b11",
      "direction": "in",
      "other": "0x00588570",
      "reference_type": "direct-call"
    },
    {
      "callsite"
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [
    "global:The body contains no absolute address, so it touches no global."
  ],
  "types": [
    "IntrusiveRefHolder* (the receiver)",
    "eastl::intrusive_ptr<Editors::EditorRigblock> (SDK candidate)"
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
      "No original-process trace exists for this function. The acquire/store/release order is proved statically but its purpose - which re-entrant write-back it defends against - has not been observed.",
      "The +0x04 and +0x08 callees have never been resolved on a concrete receiver, so the reference-count names remain inferred."
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
      "va": "0x004b0590"
    },
    {
      "name": "editor_input_005737d0",
      "reconstructed": true,
      "va": "0x005737d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00573c00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0057e790"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00582250"
    },
    {
      "name": "editor_input_00588570",
      "reconstructed": true,
      "va": "0x00588570"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x004b06c3",
      "direction": "in",
      "other": "0x004b0590",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005738e6",
      "direction": "in",
      "other": "0x005737d0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00573cd0",
      "direction": "in",
      "other": "0x00573c00",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0057e843",
      "direction": "in",
      "other": "0x0057e790",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005824ce",
      "direction": "in",
      "other": "0x00582250",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00588afb",
      "direction": "in",
      "other": "0x00588570",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00588b11",
      "direction": "in",
      "othe
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
    "package": "PKG-EDITOR-INPUT-WAVE6",
    "score": 3,
    "symbol": "editor_input_005737d0",
    "va": "0x005737d0"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-EDITOR-INPUT-WAVE6",
    "score": 3,
    "symbol": "editor_input_00588570",
    "va": "0x00588570"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/wave13-w1-dispatch-b04/004b09b0_intrusive_ref_assign.cpp",
    "reconstruction/staging/wave13-w1-dispatch-b04/004b09b0_intrusive_ref_assign.hpp",
    "reconstruction/staging/wave13-w1-dispatch-b04/wave13_w1_dispatch_b04_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-dispatch-b04/004b09b0.json"
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
    "Are the slot +0x04 and +0x08 callees really AddRef and Release, or two differently-named methods that happen to be called in these directions? Only the direction is proved by the binary; the names come from the SDK's DefaultRefCounted declaration.",
    "Is the argument always a raw pointer, or is there a second overload taking a pointer-to-pointer that was folded into this one? No such overload was found among the 11 code references.",
    "No original-process trace exists for this function. The acquire/store/release order is proved statically but its purpose - which re-entrant write-back it defends against - has not been observed.",
    "The +0x04 and +0x08 callees have never been resolved on a concrete receiver, so the reference-count names remain inferred.",
    "Which pointee type is the template argument? EditorRigblock is the best-supported candidate from the two cEditor field offsets, but the 9 undisassembled callsites were not checked and could name a different instantiation.",
    "Why does the erase loop at 0x004b06a0 walk the array assigning each cell its own value? Every iteration takes the early exit, so the loop is a no-op in the observed build. Its source-level intent is not recoverable from the code."
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-w1-dispatch-b04/004b09b0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b04/004b09b0_intrusive_ref_assign.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b04/004b09b0_intrusive_ref_assign.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b04/wave13_w1_dispatch_b04_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave13-w1-dispatch-b04/004b09b0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b04/004b09b0_intrusive_ref_assign.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b04/004b09b0_intrusive_ref_assign.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b04/wave13_w1_dispatch_b04_model_test.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first"
[TRUNCATED]
```
