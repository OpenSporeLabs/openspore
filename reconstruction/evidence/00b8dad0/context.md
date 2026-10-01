# Reconstruction context 0x00b8dad0

- Status: `partial`
- Content SHA-256: `7cc0368b261cd4a3cb01341b574803460b81c2f6960e9715cdb07212376b8a75`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00b8dad0",
  "phase": "reconstruction",
  "target": "0x00b8dad0"
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
  "va": "0x00b8dad0"
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
  "content_sha256": "b34ca72bf45cbb741336d4af034d0d394ef8c36f89bbc984bcd09631e08588e7",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00b8dad0 failed: Decompilation did not complete. Reason: ",
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
  "hidden_receiver": "ECX, read at 0x00b8dad0",
  "hidden_this_register": "ECX is read exactly once, by the LEA displacement",
  "ordinary_stack_argument_slots": 0,
  "receiver": true,
  "ret_form": "RET",
  "return_register": "EAX",
  "return_semantics": "A pointer to receiver + 0x198. Formed with LEA, so it is the address of a member block inside the receiver, not a pointer the receiver stores. The result ALIASES the receiver: writing through it modifies the receiver's +0x198 block, which makes this a mutable-reference accessor rather than a const getter.",
  "return_type": "ResourceKey3*",
  "return_width_bytes": 4,
  "saved_registers": [],
  "stack_arguments": [],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "RET at 0x00b8dad6"
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
      "va": "0x00b6b1a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c53bc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c704a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c71750"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c71910"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c829e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e2abc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01000000"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0103af90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0103ca40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0103cd00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0103d9b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0103e6e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0103e8e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0103fe90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01068970"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00b6b39c",
      "direction": "in",
      "other": "0x00b6b1a0",
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
    "ResourceKey3*"
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
      "No original-process trace exists. A differential run must confirm the returned address is still receiver + 0x198 in the shipping build.",
      "The class attribution rests on a type-name literal read at 0x00ba61b0. A run that dumps the concrete vtable pointer of a constructed record would confirm or refute it."
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
      "va": "0x00b6b1a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c53bc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c704a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c71750"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c71910"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c829e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e2abc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01000000"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0103af90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0103ca40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0103cd00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0103d9b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0103e6e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0103e8e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0103fe90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01068970"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0106ba00"
    }
  ],
  "callers_truncated": false,
  "dat
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
    "reconstruction/metadata/wave13-w1-core-b08/00b8dad0.json"
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
    "Does any caller write through the returned pointer, or do all 17 only read? Comparison sites were confirmed; a writing site was not searched for exhaustively.",
    "Fifteen of the seventeen recorded callsites were not individually disassembled, so their receiver setup and result use come from the canonical xref list only.",
    "Is the block at +0x188, the second address-taken accessor at 0x00b8da60, the same kind of three-dword block? Its extent was not bounded; only its address was observed.",
    "Is the twelve-byte block at +0x198 a ResourceKey, three separate uint32, or a struct of three ids? The three-dword extent is observed; the field names are the SDK candidate's, not the binary's.",
    "No original-process trace exists. A differential run must confirm the returned address is still receiver + 0x198 in the shipping build.",
    "Spore-ModAPI's cPlanetRecord header is itself a third-party reconstruction, so the layout agreement is corroboration, not proof. The binary is the authority for the offsets; the header only supplies plausible names.",
    "The class attribution rests on a type-name literal read at 0x00ba61b0. A run that dumps the concrete vtable pointer of a constructed record would confirm or refute it.",
    "What is this accessor called in the original source? Spore-ModAPI declares mSpiceGen at +0x198 but no accessor for it, and declares GetGeneratedTerrainKey() for the +0x1A4 sibling instead. The names GetSpiceGenKey and SetSpiceGenKey used in this worker's reconstruction and filenames are this work
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-w1-core-b08/00b8dad0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b08/ae9f50_session_boot_register.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b08/b8dad0_spice_gen_key_ptr.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b08/ba61b0_make_planet_record.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b08/c0b780_sub_object_flag_608.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b08/c0ce80_tier_value_lookup.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b08/c47180_manager_slot_replace.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_model_test2.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_reconstructed.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_test_stubs.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_test_stubs.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave13-w1-core-b08/00b8dad0.json",
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
