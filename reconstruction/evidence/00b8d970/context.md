# Reconstruction context 0x00b8d970

- Status: `partial`
- Content SHA-256: `916aa9fe9ed14a08e31e97a174131d5da9a47b00d133e7528b4be8e977ee7e66`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00b8d970",
  "phase": "reconstruction",
  "target": "0x00b8d970"
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
  "va": "0x00b8d970"
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
  "content_sha256": "cfc73a529f07e8ffef59993f029bc4a3dd21787e96a4362b041b9eed856385f1",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00b8d970 failed: Decompilation did not complete. Reason: ",
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
  "hidden_this_register": "ECX, read once and never modified",
  "ordinary_stack_argument_slots": 0,
  "receiver": true,
  "ret_form": "RET",
  "return_note": "(single flag bit, 0 or 1)",
  "return_observation": "0x00b8d973 SHR EAX,0x8 followed by 0x00b8d976 AND AL,0x1 leaves the full dword as 0 or 1. Consumers agree: 0x00c8b878 and 0x00c48534 and 0x00c44d0c all use TEST AL,AL, which is compatible with either width, but the reconstruction was written to the dword contract rather than the byte one and the model test pins it.",
  "return_register": "EAX",
  "return_semantics": "Bit 8 of the flag word at receiver+0x2c, materialised as a full dword that is exactly 0 or exactly 1. SHR EAX,8 first clears bits 0..7 and bit 31, then AND AL,1 clears bits 8..31, so the whole register ends up 0 or 1 and the upper three bytes are provably zero.",
  "return_type": "std::uint32_t",
  "return_width_bytes": 4,
  "saved_registers": [],
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
      "name": "FUN_00bba790",
      "reconstructed": false,
      "va": "0x00bba790"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bba990"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c38270"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c44d00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c484e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c8b820"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c8b920"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c8ba00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c8bb00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c8c420"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c8c5d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c8c7f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c8c9d0"
    },
    {
      "name": "PoliticalOwnershipScan_00c8d060",
      "reconstructed": true,
      "va": "0x00c8d060"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e97bf0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fdd210"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00bba811",
      "direction": "in",
      "other": "0x00bba790",
      "
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "dword bitfield",
    "dword state",
    "std::uint32_t (single flag bit, 0 or 1)"
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
      "A differential fixture is cheap but needs a receiver whose flag word is set by real game code, which static evidence does not supply.",
      "No original-process trace exists for this address, so the runtime value of the flag word at +0x2c is unverified.",
      "The Cell stage has never been entered in any recorded run, so nothing here is runtime observed."
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
      "name": "FUN_00bba790",
      "reconstructed": false,
      "va": "0x00bba790"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bba990"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c38270"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c44d00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c484e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c8b820"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c8b920"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c8ba00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c8bb00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c8c420"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c8c5d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c8c7f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c8c9d0"
    },
    {
      "name": "PoliticalOwnershipScan_00c8d060",
      "reconstructed": true,
      "va": "0x00c8d060"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e97bf0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fdd210"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fde3e0"
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
    "package": "PKG-13-E4-EMPIRE-WAVE3",
    "score": 3,
    "symbol": "PoliticalOwnershipScan_00c8d060",
    "va": "0x00c8d060"
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
    "reconstruction/staging/wave13-w1-core-b09/b09_abi.hpp",
    "reconstruction/staging/wave13-w1-core-b09/sim_flagbit_00b8d970.cpp",
    "reconstruction/staging/wave13-w1-core-b09/sim_flagbit_00b8d970.hpp",
    "reconstruction/staging/wave13-w1-core-b09/sim_flagbit_00b8d970_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-core-b09/00b8d970.json"
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
    "A differential fixture is cheap but needs a receiver whose flag word is set by real game code, which static evidence does not supply.",
    "No original-process trace exists for this address, so the runtime value of the flag word at +0x2c is unverified.",
    "No original-process trace exists, so the runtime flag values are unverified.",
    "The Cell stage has never been entered in any recorded run, so nothing here is runtime observed.",
    "What are the three unreported callsites at 0x00c56f3f, 0x00c56f95 and 0x01025ad7, which lie outside any Ghidra function body?",
    "What class owns this function? 31 live references, all UNCONDITIONAL_CALL, and no DATA reference, so it is not a vtable slot and no owner can be named.",
    "What does flag bit 8 mean? That it is a flag is established; its game meaning is not, and no SDK field, global name or string ties it to a concept.",
    "What is 0x00b8d9b0, the chain of five calls that runs only when both bit 8 and bit 0x800 are clear? It was not resolved in this batch.",
    "What is the state enum at +0x28, and what are all its values beyond the observed 0, 1 and 2-or-greater?",
    "Which other bits of the word at +0x2c are in use? Only bit 8 (here) and bit 11 (0x00b8da12) were observed; the other 30 bits are unaccounted for.",
    "Who writes the flag word at +0x2c? No writer was found in this batch."
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-w1-core-b09/00b8d970.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b09/b09_abi.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b09/sim_flagbit_00b8d970.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b09/sim_flagbit_00b8d970.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b09/sim_flagbit_00b8d970_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave13-w1-core-b09/00b8d970.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b09/b09_abi.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b09/sim_flagbit_00b8d970.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b09/sim_flagbit_00b8d970.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w
[TRUNCATED]
```
