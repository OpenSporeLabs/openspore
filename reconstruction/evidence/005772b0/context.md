# Reconstruction context 0x005772b0

- Status: `partial`
- Content SHA-256: `a3ede89cb7fa75e7579ed504a47eab210d022148132bac5610cc3beecd883627`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x005772b0",
  "phase": "reconstruction",
  "target": "0x005772b0"
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
  "va": "0x005772b0"
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
  "content_sha256": "36ccd9ab0bd9ab7b4fc92df00b5cc5d14f36dfcf41eb0ce970dc58bef8f2c055",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x005772b0 failed: Decompilation did not complete. Reason: ",
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
  "hidden_this_register": "ECX, moved to ESI at 0x005772b1 and held for the whole body",
  "ordinary_stack_argument_slots": 0,
  "receiver": true,
  "ret_form": "RET",
  "return_observation": "There is no MOV EAX/AL and no XOR EAX,EAX in the 36-instruction body. 0x005772ca and 0x00577307 are CALL EAX with the address loaded from a vtable, and the tested precondition is only that the object pointer is non-null.",
  "return_register": "EAX (clobbered, unused)",
  "return_semantics": "no meaningful return; EAX is clobbered by the two indirect calls and is never read by any of the 10 observed call sites",
  "return_type": "void",
  "return_width_bytes": 0,
  "saved_registers": [
    "ESI",
    "EBX"
  ],
  "stack_arguments": [],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "two exits, both a bare RET: 0x005772ed on the decrement path and 0x0057730b on the destroy/early-out path"
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
      "va": "0x0057a610"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0057e160"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0057e790"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0057f6c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00587270"
    },
    {
      "name": "Editors::cEditor::OnExit",
      "reconstructed": false,
      "va": "0x00587a20"
    },
    {
      "name": "editor_input_00588570",
      "reconstructed": true,
      "va": "0x00588570"
    },
    {
      "name": "editor_input_0058ac10",
      "reconstructed": true,
      "va": "0x0058ac10"
    },
    {
      "name": "editor_input_0058b650",
      "reconstructed": true,
      "va": "0x0058b650"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x0057a621",
      "direction": "in",
      "other": "0x0057a610",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0057e1bc",
      "direction": "in",
      "other": "0x0057e160",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0057e7b7",
      "direction": "in",
      "other": "0x0057e790",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00580225",
      "direction": "in",
      "other": "0x0057f6c0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005874da",
      "direction": "in",
      "other": "0x00587270",
      "reference_type": "direct-call"
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
      "A trace must confirm that IModelWorld slot +0x170 does not itself decrement the counter, since this body reaches it with the counter still at 1 (or 0).",
      "A trace with a concrete editor receiver is required before the +0xf0 member and the +0xe9 guard can be given semantic names.",
      "No original-process trace has ever been captured for 0x005772b0, so every claim here is static. A differential trace must confirm that mpWorld is non-null whenever the +0xf0 member is non-null, because both virtual calls dereference model->mpWorld twice with no null check."
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
      "va": "0x0057a610"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0057e160"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0057e790"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0057f6c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00587270"
    },
    {
      "name": "Editors::cEditor::OnExit",
      "reconstructed": false,
      "va": "0x00587a20"
    },
    {
      "name": "editor_input_00588570",
      "reconstructed": true,
      "va": "0x00588570"
    },
    {
      "name": "editor_input_0058ac10",
      "reconstructed": true,
      "va": "0x0058ac10"
    },
    {
      "name": "editor_input_0058b650",
      "reconstructed": true,
      "va": "0x0058b650"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x0057a621",
      "direction": "in",
      "other": "0x0057a610",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0057e1bc",
      "direction": "in",
      "other": "0x0057e160",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0057e7b7",
      "direction": "in",
      "other": "0x0057e790",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00580225",
      "direction": "in",
      "other": "0x0057f6c0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005874da",
      
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
    "symbol": "editor_input_00588570",
    "va": "0x00588570"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-EDITOR-INPUT-WAVE6",
    "score": 3,
    "symbol": "editor_input_0058ac10",
    "va": "0x0058ac10"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-EDITOR-INPUT-WAVE6",
    "score": 3,
    "symbol": "editor_input_0058b650",
    "va": "0x0058b650"
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
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/wave13-w1-dispatch-b03/editor_release_preview_model.cpp",
    "reconstruction/staging/wave13-w1-dispatch-b03/editor_release_preview_model.hpp",
    "reconstruction/staging/wave13-w1-dispatch-b03/editor_release_preview_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-dispatch-b03/005772b0.json"
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
    "A trace must confirm that IModelWorld slot +0x170 does not itself decrement the counter, since this body reaches it with the counter still at 1 (or 0).",
    "A trace with a concrete editor receiver is required before the +0xf0 member and the +0xe9 guard can be given semantic names.",
    "Is the +0xf0 model a 'preview', 'ghost' or 'highlight' model? The setup writes an all-ones mColor and a bitmask derived from an index-returning world call, which is consistent with several editor overlay uses, and nothing observed here decides between them.",
    "Is the counter at +0x40 really Model::mnRefCount in the original build, or a per-world counter that happens to share the offset? The five-way offset agreement makes this unlikely but nothing at runtime confirms it.",
    "No original-process trace has ever been captured for 0x005772b0, so every claim here is static. A differential trace must confirm that mpWorld is non-null whenever the +0xf0 member is non-null, because both virtual calls dereference model->mpWorld twice with no null check.",
    "What does bit 31 of Model::mFlags (0x80000000) mean? It is undocumented in the SDK Model.h flag enum and in cMWModelInternal::field_138, and no writer of that specific bit was located.",
    "What is this routine called in the original source? No string, symbol, PDB reference or vtable entry in the binary names it, and the +0xe9 guard is a bare byte with no SDK counterpart.",
    "Which concrete IModelWorld implementation receives the +0x16c and +0x170 calls? The vtable is a runtime
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-w1-dispatch-b03/005772b0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b03/editor_release_preview_model.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b03/editor_release_preview_model.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b03/editor_release_preview_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave13-w1-dispatch-b03/005772b0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b03/editor_release_preview_model.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b03/editor_release_preview_model.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b03/editor_release_preview_model_test.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": 
[TRUNCATED]
```
