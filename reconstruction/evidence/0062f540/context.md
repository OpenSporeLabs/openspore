# Reconstruction context 0x0062f540

- Status: `partial`
- Content SHA-256: `ec36bce0cb5716d9b03c2e3cdb0fdcead1a574288508ba7c1d9334023b4ff568`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x0062f540",
  "phase": "reconstruction",
  "target": "0x0062f540"
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
  "va": "0x0062f540"
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
  "content_sha256": "68f92195b740e1b4df79ddebc62b4bc08e0148df145cda9daf6c06158674ab2c",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x0062f540 failed: Decompilation did not complete. Reason: ",
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
  "hidden_this_register": "ECX is the receiver; 0x0062f544 MOV ESI,ECX and the body reads [ESI+0x34], [ESI+0x38] and [ESI+0x3c]",
  "ordinary_stack_argument_slots": 0,
  "receiver": true,
  "ret_form": "RET",
  "return_observation": "0x0062f5b8: RET with no preceding write to EAX that any caller consumes; 0x0062f88f is followed by MOV ECX,ESI and 0x0062fd06 by MOV ECX,ESI, so no result is used.",
  "return_register": null,
  "return_semantics": "void; the caller reads no register after either call site",
  "return_type": "void",
  "return_width_bytes": 0,
  "saved_registers": [
    "ESI",
    "EDI"
  ],
  "stack_arguments": [],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "RET"
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
      "va": "0x0062f7f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0062fc90"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x0062f88f",
      "direction": "in",
      "other": "0x0062f7f0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0062fd06",
      "direction": "in",
      "other": "0x0062fc90",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0062f558",
      "direction": "out",
      "other": "0x00634dc0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0062f54b",
      "direction": "out",
      "other": "0x006b5060",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0062f5ae",
      "direction": "out",
      "other": "0x006b5240",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0062f576",
      "direction": "out",
      "other": "0x006b54b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0062f59a",
      "direction": "out",
      "other": "0x006b55c0",
      "reference_type": "direct-call"
    }
  ],
  "external_callees": []
}
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
      "A runtime trace is required to confirm the runtime value of the global at 0x015F7CF4, the runtime resolution of localization id 0x7518573e, and that the window with control id 0x47ED688 actually exists in the PlayMode layout at the moment this function runs.",
      "No original-process trace has been captured for 0x0062f540. Every claim in this record is static.",
      "The Cell stage has never been entered in any recorded run, so the Editor/PlayMode path has no runtime oracle at all."
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
      "va": "0x0062f7f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0062fc90"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x0062f88f",
      "direction": "in",
      "other": "0x0062f7f0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0062fd06",
      "direction": "in",
      "other": "0x0062fc90",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0062f558",
      "direction": "out",
      "other": "0x00634dc0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0062f54b",
      "direction": "out",
      "other": "0x006b5060",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0062f5ae",
      "direction": "out",
      "other": "0x006b5240",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0062f576",
      "direction": "out",
      "other": "0x006b54b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0062f59a",
      "direction": "out",
      "other": "0x006b55c0",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 2,
  "fan_out": 0,
  "manifest_callees": [],
  "manifest_callers": [],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0147",
    "size": 1
  },
  "vtable_reference_count": 0
}
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
    "reconstruction/staging/wave13-w1-dispatch-b05/playmode_backgrounds_0062f540.cpp",
    "reconstruction/staging/wave13-w1-dispatch-b05/playmode_backgrounds_0062f540.hpp",
    "reconstruction/staging/wave13-w1-dispatch-b05/playmode_backgrounds_0062f540_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-dispatch-b05/0062f540.json"
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
    "A runtime trace is required to confirm the runtime value of the global at 0x015F7CF4, the runtime resolution of localization id 0x7518573e, and that the window with control id 0x47ED688 actually exists in the PlayMode layout at the moment this function runs.",
    "Is 0x0062f540 ever reached with the global at 0x015F7CF4 still null while a window is found? Statically impossible to exclude; a differential trace would be needed to confirm the invariant is upheld by the callers rather than by luck.",
    "No original-process trace has been captured for 0x0062f540. Every claim in this record is static.",
    "The Cell stage has never been entered in any recorded run, so the Editor/PlayMode path has no runtime oracle at all.",
    "What does 0x00634dc0 do when its slot +0xf0 fallback runs? The creation path is observed as a call with (id, 1) but its result and side effects were not analysed.",
    "What does vtable slot +0x80 concretely do? The argument is a resolved text pointer and the SDK declares SetCaption at exactly +0x80, but the implementing class was not located, so the call target is unidentified.",
    "What is the concrete class of the receiver? The SDK field layout at +0x34/+0x38/+0x3C matches Editors::PlayModeBackgrounds and the region matches, but the SDK's declared address for that class's UpdatePageNumbers matches neither 0x62F520 nor 0x62F570 to this entry, so the class assignment stays a candidate.",
    "What is the method name? No vtable entry, no imported symbol and no SDK address exist for 0x0062f540, s
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-w1-dispatch-b05/0062f540.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b05/playmode_backgrounds_0062f540.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b05/playmode_backgrounds_0062f540.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b05/playmode_backgrounds_0062f540_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave13-w1-dispatch-b05/0062f540.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b05/playmode_backgrounds_0062f540.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b05/playmode_backgrounds_0062f540.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b05/playmode_backgrounds_0062f540_model_test.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "read
[TRUNCATED]
```
