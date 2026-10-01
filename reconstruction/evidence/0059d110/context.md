# Reconstruction context 0x0059d110

- Status: `partial`
- Content SHA-256: `8261c52593cf94b72ff06a6dbad03fc8178f0d90f76c4fcc4ad1c4f9577e272d`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x0059d110",
  "phase": "reconstruction",
  "target": "0x0059d110"
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
  "va": "0x0059d110"
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
  "content_sha256": "982c182765a23a1e698387cefd8edb34e95e21fedfc72cfd101debeea2b6e1d2",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x0059d110 failed: Decompilation did not complete. Reason: ",
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
  "hidden_this_register": "ECX, moved to EDI at 0x0059d117 and held for the whole body",
  "ordinary_stack_argument_slots": 2,
  "receiver": true,
  "ret_form": "RET 0x8",
  "return_observation": "0x0059d169 MOV AL,0x1 on the success path and 0x0059d171 XOR AL,AL on the failure path. Neither writes the upper bytes of EAX, so bits 8..31 are undefined on exit. Every inspected call site consumes the answer with TEST AL,AL followed by JZ, never as a dword.",
  "return_register": "AL",
  "return_semantics": "a byte-valued predicate: 1 when the position was written, 0 when any of the three guards rejected the query",
  "return_type": "bool",
  "return_width_bytes": 1,
  "saved_registers": [
    "ECX",
    "ESI",
    "EDI"
  ],
  "stack_arguments": [
    {
      "proof": "0x0059d111 MOV EAX,[ESP+0x8] reads it after the single PUSH ECX, i.e. the first stack slot; 0x0059d11d re-stores it locally and both map ports receive its address",
      "role": "creature_id",
      "slot": "[ESP_entry+4]"
    },
    {
      "proof": "0x0059d128 LEA EDX,[ESP+0xc] with ESP already lowered by 8 resolves to ESP_entry+8 and is pushed as the second argument to the find port; 0x0059d156 MOV ECX,[ESP+0x14] reloads the same slot on the copy path",
      "role": "out_position",
      "slot": "[ESP_entry+8]"
    }
  ],
  "stack_cleanup_bytes": 8,
  "stack_cleanup_owner": "callee",
  "termination": "two exits, 0x0059d16d and 0x0059d175, both RET 0x8 and both preceded by POP EDI / POP ESI / POP ECX"
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "map_int_EditorCreatureControllerPtr__get",
      "reconstructed": false,
      "va": "0x0059c740"
    },
    {
      "name": "map_int_whatever_find",
      "reconstructed": true,
      "va": "0x00e5c780"
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00577e10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00582d70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00582fe0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00583900"
    },
    {
      "name": "Editors::cEditor::Update",
      "reconstructed": false,
      "va": "0x0058be50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00628f10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00629590"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0062abd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00639350"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00577fce",
      "direction": "in",
      "other": "0x00577e10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00578b2d",
      "direction": "in",
      "other": "0x00577e10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00578d79",
      "direction": "in",
      "other": "0x00577e10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00578d9c",
      "direction": "in",
      "other": "0x00577
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "bool"
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
      "A trace must confirm the +0x0c sentinel identity, i.e. that the receiver's +0x0c really is the map's end node in a live instance. This is derived from the find port's source rather than observed at runtime.",
      "A trace with a concrete receiver is required before the creature id space can be characterised, and therefore before the 18 unchecked call sites can be assumed safe.",
      "No original-process trace exists for this function. Static analysis cannot show whether the mpAnimWorld gate is ever false in a live editor session, or how often the key-absent case occurs."
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
      "name": "map_int_EditorCreatureControllerPtr__get",
      "reconstructed": false,
      "va": "0x0059c740"
    },
    {
      "name": "map_int_whatever_find",
      "reconstructed": true,
      "va": "0x00e5c780"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00577e10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00582d70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00582fe0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00583900"
    },
    {
      "name": "Editors::cEditor::Update",
      "reconstructed": false,
      "va": "0x0058be50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00628f10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00629590"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0062abd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00639350"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00577fce",
      "direction": "in",
      "other": "0x00577e10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00578b2d",
      "direction": "in",
      "other": "0x00577e10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00578d79",
      "direction": "in",
      "other": "0x00577e10",
      "reference_type": "direct-call"
    },
 
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
    "package": "PKG-20-GAMEGLOBAL",
    "score": 3,
    "symbol": "map_int_whatever_find",
    "va": "0x00e5c780"
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
    "reconstruction/staging/wave13-w1-dispatch-b03/editor_anim_world_get_creature_position.cpp",
    "reconstruction/staging/wave13-w1-dispatch-b03/editor_anim_world_get_creature_position.hpp",
    "reconstruction/staging/wave13-w1-dispatch-b03/editor_anim_world_get_creature_position_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-dispatch-b03/0059d110.json"
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
    "A trace must confirm the +0x0c sentinel identity, i.e. that the receiver's +0x0c really is the map's end node in a live instance. This is derived from the find port's source rather than observed at runtime.",
    "A trace with a concrete receiver is required before the creature id space can be characterised, and therefore before the 18 unchecked call sites can be assumed safe.",
    "Is the coordinate space of AnimatedCreature::mPosition world or model-local? The SDK does not say, and nothing in this body resolves it.",
    "Is there a sibling writer (a SetTargetPosition-shaped method at 0x59CF00) that this reader is the inverse of? Plausible from the signature but unverified here.",
    "No original-process trace exists for this function. Static analysis cannot show whether the mpAnimWorld gate is ever false in a live editor session, or how often the key-absent case occurs.",
    "The original method name. cEditorAnimWorld declares five methods with address pairs and 0x0059d110 matches none of them, so the routine is either undeclared in the SDK or inlined out of a template. No name is claimed.",
    "What are the 13 undisassembled call sites doing with the result, in particular the one at 0x0063a9ec that Ghidra does not attribute to any function?",
    "Why are only some of the 18 call sites checking the return value, and what do the unchecked ones do with a stale out buffer? The body guarantees the buffer is untouched on failure, but the callers' pre-initialisation was not verified."
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-w1-dispatch-b03/0059d110.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b03/editor_anim_world_get_creature_position.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b03/editor_anim_world_get_creature_position.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b03/editor_anim_world_get_creature_position_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave13-w1-dispatch-b03/0059d110.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b03/editor_anim_world_get_creature_position.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b03/editor_anim_world_get_creature_position.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b03/editor_anim_world_get_creature_position_test.cpp",
      "source_class": "committed_arti
[TRUNCATED]
```
