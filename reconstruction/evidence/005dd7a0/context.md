# Reconstruction context 0x005dd7a0

- Status: `partial`
- Content SHA-256: `60bd7b386943133491b3ea5df84946bb6a9ca9a57eb6addc22b65106f27a4d1e`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x005dd7a0",
  "phase": "reconstruction",
  "target": "0x005dd7a0"
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
  "va": "0x005dd7a0"
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
  "content_sha256": "a47fcfc66207c1c5460d0d6b692fce2a581e320c370b69e94c7c98cfa403df9f",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x005dd7a0 failed: Decompilation did not complete. Reason: ",
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
  "hidden_this_register": "ECX, moved to ESI at 0x005dd7a5 and reloaded into ECX at 0x005dd833 for the tail call",
  "ordinary_stack_argument_slots": 0,
  "receiver": true,
  "ret_form": "JMP (tail transfer)",
  "return_observation": "0x005dd83a is JMP 0x005dc800, not RET. The three POPs and the ADD ESP,0x8 run first, so the callee-clean convention and the frame are already resolved when control leaves.",
  "return_register": "none",
  "return_semantics": "no value. The body ends with a tail transfer, so there is no return address to unwind to this function's caller and no result is produced.",
  "return_type": "void",
  "return_width_bytes": 0,
  "saved_registers": [
    "EBX",
    "ESI",
    "EDI"
  ],
  "stack_arguments": [],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "single exit, a tail jump to 0x005dc800 with ECX reloaded to the receiver at 0x005dd833"
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
      "va": "0x0057ea30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0057ed00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0057f6c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00586410"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00586690"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0058a1e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0058a5a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0058a950"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0058d1c0"
    },
    {
      "name": "Editors::cEditor::HandleMessage",
      "reconstructed": false,
      "va": "0x00591fa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005de690"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x0057eb9b",
      "direction": "in",
      "other": "0x0057ea30",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0057ed3c",
      "direction": "in",
      "other": "0x0057ed00",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0057f7bd",
      "direction": "in",
      "other": "0x0057f6c0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00586654",
      "direction": "in",
      "other": "0x00586410",
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
    "void"
  ],
  "vtables": [
    "vtable:0x005dd840"
  ]
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
      "A differential test must confirm that the two layouts at +0x14 and +0x2c really are alternatives rather than complementary, i.e. that the fallback path is ever taken.",
      "A trace must record the live value of the +0x102 enable byte and the +0xd1 inhibit byte, since either can suppress the whole publish step.",
      "A trace must resolve the provider that virtual slot +0x7c belongs to, which is the only way to turn 'two named toggle states' into a semantic claim.",
      "No original-process trace exists for this function. Static analysis cannot show which of the five classification values actually occurs in a live editor session, so the frequency of each published state is unknown."
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
      "va": "0x0057ea30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0057ed00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0057f6c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00586410"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00586690"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0058a1e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0058a5a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0058a950"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0058d1c0"
    },
    {
      "name": "Editors::cEditor::HandleMessage",
      "reconstructed": false,
      "va": "0x00591fa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005de690"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x0057eb9b",
      "direction": "in",
      "other": "0x0057ea30",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0057ed3c",
      "direction": "in",
      "other": "0x0057ed00",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0057f7bd",
      "direction": "in",
      "other": "0x0057f6c0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00586654",
      "directi
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
    "reconstruction/staging/wave13-w1-dispatch-b03/editor_ui_paint_toggle_publish.cpp",
    "reconstruction/staging/wave13-w1-dispatch-b03/editor_ui_paint_toggle_publish.hpp",
    "reconstruction/staging/wave13-w1-dispatch-b03/editor_ui_paint_toggle_publish_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-dispatch-b03/005dd7a0.json"
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
    "A differential test must confirm that the two layouts at +0x14 and +0x2c really are alternatives rather than complementary, i.e. that the fallback path is ever taken.",
    "A trace must record the live value of the +0x102 enable byte and the +0xd1 inhibit byte, since either can suppress the whole publish step.",
    "A trace must resolve the provider that virtual slot +0x7c belongs to, which is the only way to turn 'two named toggle states' into a semantic claim.",
    "No original-process trace exists for this function. Static analysis cannot show which of the five classification values actually occurs in a live editor session, so the frequency of each published state is unknown.",
    "The method name; nothing in the binary or the SDK names it.",
    "The owning class. Six offsets match Spore/Editors/EditorUI.h uniquely and the receiver's provenance is cEditor+0x78 = mpEditorUI, but no vtable exists in the typed program and there is no RTTI, so the class is a candidate and not a claim.",
    "The twelve uninspected call sites and the flag values their contexts imply, in particular the pair inside cEditor::HandleMessage and the two inside FUN_0058d1c0.",
    "What element id 0x5b6e484 denotes. It is absent from every SDK header read, and the sibling ids 0x612efea and 0x612efeb used by the tail target are equally unlabelled.",
    "What object virtual slot +0x7c belongs to, and what that method is called. This is the largest gap: it bounds what the function publishes to 'two named toggle states' without naming either.",
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-w1-dispatch-b03/005dd7a0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b03/editor_ui_paint_toggle_publish.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b03/editor_ui_paint_toggle_publish.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b03/editor_ui_paint_toggle_publish_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave13-w1-dispatch-b03/005dd7a0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b03/editor_ui_paint_toggle_publish.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b03/editor_ui_paint_toggle_publish.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b03/editor_ui_paint_toggle_publish_test.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_fi
[TRUNCATED]
```
