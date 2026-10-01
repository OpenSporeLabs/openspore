# Reconstruction context 0x00c0ce80

- Status: `partial`
- Content SHA-256: `71aa5cbcad3fbe27642bd14292c402ef36252addf64ec2b0555affdcc8952f2c`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00c0ce80",
  "phase": "reconstruction",
  "target": "0x00c0ce80"
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
  "va": "0x00c0ce80"
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
  "content_sha256": "ad70ad7a0275ed2bb94be05ec967c0deba7cce623c513c70e2a90bb439322e80",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00c0ce80 failed: Decompilation did not complete. Reason: ",
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
  "hidden_receiver": "ECX, copied to EDI at 0x00c0ce89",
  "hidden_this_register": "ECX is live until 0x00c0cea0 where MOV ECX,EDI re-establishes it for 0x00C0CE30; after 0x00c0ce89 it is never read again, and 0x00c0cee1 overwrites it with receiver+0xC0 for the virtual call.",
  "ordinary_stack_argument_slots": 2,
  "receiver": true,
  "ret_form": "RET 0x8",
  "return_register": "ST0",
  "return_semantics": "ST0 on return, consumed by FSTP. Two shapes. Gate false: the base value, unchanged. Gate true: v + 0.5f * |first_arg_reinterpreted_as_float - v|. The second shape is asymmetric: when the float operand is at or below v the result is the midpoint (v + a) / 2, but when a is above v the result is (3v - a) / 2, which overshoots.",
  "return_type": "float",
  "return_width_bytes": 4,
  "saved_registers": [
    "EDI",
    "ESI (only on the 0x00c0cf1f path)"
  ],
  "stack_arguments": [
    {
      "index": 0,
      "note": "Ghidra's `param_2 == 0.0` test and its `ABS(local_4 - param_2)` are the same single stack word read two ways. The decompiler additionally aliases the zero-initialised local at [E0-4] onto this parameter, which is wrong: 0x00c0ce8b writes 0.0f into the saved-ECX slot, not into the parameter slot. Recorded as a correction.",
      "offset_at_entry": "[ESP + 0x4]",
      "use_1": "TEST EAX,EAX at 0x00c0ce91: zero returns 0.0f immediately, with no callee invoked",
      "use_2": "FLD float ptr [ESP + 0xC] at 0x00c0cf24, reached after the POP ESI and POP EDI, so the same word is the float operand
[TRUNCATED]
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "FUN_00b5b800",
      "reconstructed": false,
      "va": "0x00b5b800"
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c0cf50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c0cfa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c0cff0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c0d050"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c0d0c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c190e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c1aad0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c1ad10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c1b020"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c1c080"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c1c1d0"
    },
    {
      "name": "Simulator_cCreatureBase_LocomotionWalkToInterior_00c1c5c0",
      "reconstructed": true,
      "va": "0x00c1c5c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c1de20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c1f8d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c21bf0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00c0cf62",
      "direction": "in",
      "o
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "float"
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
      "No original-process trace exists. A differential run must confirm the six table values at 0x015D9650 and the boolean behind slot +0x58 at the moment this function runs.",
      "The concrete receiver behind the slot +0x58 dispatch must be observed before the owning class can be named.",
      "The sentinel branch is only reachable once 0x01654C10 has been populated at runtime; in the file image it holds 0, so the branch cannot be exercised statically.",
      "The value of the singleton's float vector at singleton+0x10 can only be observed at runtime, which also determines whether 0x00F31500 returns a real element or FLD1."
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
      "name": "FUN_00b5b800",
      "reconstructed": false,
      "va": "0x00b5b800"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c0cf50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c0cfa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c0cff0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c0d050"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c0d0c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c190e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c1aad0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c1ad10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c1b020"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c1c080"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c1c1d0"
    },
    {
      "name": "Simulator_cCreatureBase_LocomotionWalkToInterior_00c1c5c0",
      "reconstructed": true,
      "va": "0x00c1c5c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c1de20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c1f8d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c21bf0"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
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
    "package": "PKG-13-C4-CREATURE-WAVE3",
    "score": 3,
    "symbol": "Simulator_cCreatureBase_LocomotionWalkToInterior_00c1c5c0",
    "va": "0x00c1c5c0"
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
    "va": "
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/wave13-w1-core-b08/ae9f50_session_boot_register.cpp",
    "reconstruction/staging/wave13-w1-core-b08/b8dad0_spice_gen_key_ptr.cpp",
    "reconstruction/staging/wave13-w1-core-b08/ba61b0_make_planet_record.cpp",
    "reconstruction/staging/wave13-w1-core-b08/c0b780_sub_object_flag_608.cpp",
    "reconstruction/staging/wave13-w1-core-b08/c0ce80_tier_value_lookup.cpp",
    "reconstruction/staging/wave13-w1-core-b08/c47180_manager_slot_replace.cpp",
    "reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08.hpp",
    "reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_model_test.cpp",
    "reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_model_test2.cpp",
    "reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_reconstructed.hpp",
    "reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_test_stubs.cpp",
    "reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_test_stubs.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-core-b08/00c0ce80.json"
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
    "Is the sentinel test 0x00B5B800() == 0x01654C10 a type check or an instance check? The same constant is pushed to 0x00B3D320 inside 0x00F31500, which is consistent with either reading.",
    "No original-process trace exists. A differential run must confirm the six table values at 0x015D9650 and the boolean behind slot +0x58 at the moment this function runs.",
    "Ten of the fifteen recorded callsites were not individually disassembled.",
    "The concrete receiver behind the slot +0x58 dispatch must be observed before the owning class can be named.",
    "The sentinel branch is only reachable once 0x01654C10 has been populated at runtime; in the file image it holds 0, so the branch cannot be exercised statically.",
    "The value of the singleton's float vector at singleton+0x10 can only be observed at runtime, which also determines whether 0x00F31500 returns a real element or FLD1.",
    "What are the six runtime values of the float table at 0x015D9650? The shipped image carries zeros, so on the file image every path through this table returns 0.",
    "What is 0x0145F924, the type descriptor 0x00C03260 passes to the allocator? It is read as an immediate only.",
    "What is the boolean at slot +0x58? It is only ever consumed as a gate on whether the neighbour-averaged formula is applied.",
    "What is the name of the float at _DAT_0150C900 that 0x00C0CFA0 adds to this result? It was not read.",
    "What populates the singleton at 0x0168D824 and its float vector at +0x10? Only the lazy-allocation path of 0x00C03260 
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-w1-core-b08/00c0ce80.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b08/ae9f50_session_boot_register.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b08/b8dad0_spice_gen_key_ptr.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b08/ba61b0_make_planet_record.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b08/c0b780_sub_object_flag_608.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b08/c0ce80_tier_value_lookup.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b08/c47180_manager_slot_replace.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_model_test2.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_reconstructed.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_test_stubs.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_test_stubs.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave13-w1-core-b08/00c0ce80.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b08/ae9f50_session_boot_register.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b08/b8dad0_spice_gen_key_ptr.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b08/ba61b0_make_planet_record.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "r
[TRUNCATED]
```
