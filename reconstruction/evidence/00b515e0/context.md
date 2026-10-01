# Reconstruction context 0x00b515e0

- Status: `partial`
- Content SHA-256: `91be62b01fa80c01378e64a95681731fa6d3b93a0186289dd1872cf8e0fc5e36`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00b515e0",
  "phase": "reconstruction",
  "target": "0x00b515e0"
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
  "va": "0x00b515e0"
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
  "content_sha256": "2dcc9fe5430d1d72c722a6278ede0087af718b56a0a09bcc15f8c770ea69584c",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00b515e0 failed: Decompilation did not complete. Reason: ",
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
  "hidden_this_register": "ECX, consumed by 0x00b515e8 MOV EDI,ECX and used only at 0x00b51638 to write the byte latch at EDI+0x30. ECX is clobbered by the virtual call at 0x00b51615 and reloaded at 0x00b51617.",
  "ordinary_stack_argument_slots": 0,
  "receiver": true,
  "ret_form": "RET",
  "return_observation": "The body never writes EAX outside the two SETNZ AL instructions at 0x00b51601 and 0x00b5161d, whose results feed TEST AL,AL immediately and are dead by 0x00b51606 / 0x00b51620. Every inspected callsite discards EAX: at 0x00fdc31c the next instruction is a fresh CALL, at 0x00b3d7a8 the next instruction reloads ECX from ESI, at 0x00fe105e the next instruction is CALL 0x00b3d350. The decompiler agrees: `void __fastcall FUN_00b515e0(int param_1)`.",
  "return_register": null,
  "return_semantics": "no value; side effects only",
  "return_type": "void",
  "return_width_bytes": 0,
  "saved_registers": [
    "EDI",
    "ESI"
  ],
  "stack_arguments": [],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "RET at 0x00b5163d"
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "simulator_game_input_manager_get_00b3d350",
      "reconstructed": true,
      "va": "0x00b3d350"
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b3d7a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ed4b70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00f44dd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fdc240"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fdc710"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fdc800"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fe0160"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fe0e10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fe0f40"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00b3d7a3",
      "direction": "in",
      "other": "0x00b3d7a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00ed4bd7",
      "direction": "in",
      "other": "0x00ed4b70",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f44f66",
      "direction": "in",
      "other": "0x00f44dd0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00fdc31c",
      "direction": "in",
      "other": "0x00fdc240",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00fdc74c",
      "direction": "in",
      "other":
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
      "A runtime differential must confirm that the cGameInputManager pointer stored at +0x34 is really compared by identity and not rewritten behind the cached object's back between calls, which would make the check vacuous.",
      "A runtime trace must show whether [this + 0x30] is ever read, and by which code, before the latch can be named.",
      "A runtime trace with a concrete receiver is required to resolve the slot +0x0c callee: the call must be sampled with ECX holding the sub-object and the callee address recorded.",
      "Every claim here is static. No original-process trace has been captured for 0x00b515e0, and the Cell stage has never been entered in any recorded run."
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
      "name": "simulator_game_input_manager_get_00b3d350",
      "reconstructed": true,
      "va": "0x00b3d350"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b3d7a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ed4b70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00f44dd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fdc240"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fdc710"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fdc800"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fe0160"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fe0e10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fe0f40"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00b3d7a3",
      "direction": "in",
      "other": "0x00b3d7a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00ed4bd7",
      "direction": "in",
      "other": "0x00ed4b70",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f44f66",
      "direction": "in",
      "other": "0x00f44dd0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00fdc31c",
      "direction": "in",
      "other": "0x00fdc240",
      "reference_type": "direct-call"
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
    "package": "PKG-GAME-INPUT-WAVE7",
    "score": 3,
    "symbol": "simulator_game_input_manager_get_00b3d350",
    "va": "0x00b3d350"
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
    "reconstruction/staging/wave13-w1-core-b16/b515e0_cached_object_validate.cpp",
    "reconstruction/staging/wave13-w1-core-b16/b515e0_cached_object_validate.hpp",
    "reconstruction/staging/wave13-w1-core-b16/b515e0_cached_object_validate_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-core-b16/00b515e0.json"
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
    "A runtime differential must confirm that the cGameInputManager pointer stored at +0x34 is really compared by identity and not rewritten behind the cached object's back between calls, which would make the check vacuous.",
    "A runtime trace must show whether [this + 0x30] is ever read, and by which code, before the latch can be named.",
    "A runtime trace with a concrete receiver is required to resolve the slot +0x0c callee: the call must be sampled with ECX holding the sub-object and the callee address recorded.",
    "Every claim here is static. No original-process trace has been captured for 0x00b515e0, and the Cell stage has never been entered in any recorded run.",
    "Is the +0x1c sub-object reference itself revalidated? No check on the +0x1c pointer itself was found, so a null there would fault at 0x00b515fe rather than invalidate. Whether the original can be reached in that state is unestablished.",
    "The SDK candidate set is empty by rejection rather than by absence of reading: GameInputManager.h and cStrategy.h were both read and both conflict with the observed offsets.",
    "What are the two guard globals semantically? 0x0167ecd0 gates the whole cluster and is written at 0x00b4d8c9 and 0x00b5a4ce, neither of which was analysed. 0x0167ecd4 is the cache. Which of them is 'the subsystem is running' and which is 'the object exists' is inferred from behaviour, not read.",
    "What class owns the receiver? All nine callers pass the single global 0x0167eae8 through accessor 0x00b3d310, so the receiver is one
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-w1-core-b16/00b515e0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b16/b515e0_cached_object_validate.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b16/b515e0_cached_object_validate.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b16/b515e0_cached_object_validate_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave13-w1-core-b16/00b515e0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b16/b515e0_cached_object_validate.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b16/b515e0_cached_object_validate.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b16/b515e0_cached_object_validate_model_test.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "
[TRUNCATED]
```
