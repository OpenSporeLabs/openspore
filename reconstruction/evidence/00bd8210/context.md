# Reconstruction context 0x00bd8210

- Status: `partial`
- Content SHA-256: `75f1d47736e9fb26ee5bb9aec93b7f6128b6ba9b6ffafb45986d20bbc80b4ab0`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00bd8210",
  "phase": "reconstruction",
  "target": "0x00bd8210"
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
  "va": "0x00bd8210"
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
  "content_sha256": "c4db125e3afea67a570123d9725d1bf5846db2ef625f82231d50ab34530ac69c",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00bd8210 failed: Decompilation did not complete. Reason: ",
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
  "hidden_this_register": "ECX is read at 0x00bd8210 and forwarded unchanged into the slot +0x58 call at 0x00bd821c",
  "ordinary_stack_argument_slots": 0,
  "receiver": true,
  "receiver_register": "ECX",
  "ret_form": "RET",
  "return_observation": "0x00b885a9..0x00b8875a computes a value and 0x00b8875a masks it with 0x3ff, so at most ten bits are significant. 0x00bd821f/0x00bd8226 do not touch EAX after the 0x00b88590 call, and 0x00bd822e is a bare RET, so the full EAX is forwarded.",
  "return_register": "EAX",
  "return_semantics": "the 10-bit payload that 0x00b88590 returns, forwarded unchanged in EAX",
  "return_type": "std::uint16_t",
  "return_width_bytes": 2,
  "saved_registers": [],
  "stack_arguments": [],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller for 0x00bd8210 itself; callee for 0x00bd821c and 0x00b88590",
  "termination": "RET"
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
      "va": "0x00bf00a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf0110"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf0130"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf5720"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf8440"
    },
    {
      "name": "culture_selection_00bf9820",
      "reconstructed": true,
      "va": "0x00bf9820"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf9e70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bfa660"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bfb020"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ca8340"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d04320"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00bf00cb",
      "direction": "in",
      "other": "0x00bf00a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00bf011c",
      "direction": "in",
      "other": "0x00bf0110",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00bf016d",
      "direction": "in",
      "other": "0x00bf0130",
      "reference_type": "direct-call"
    },
    {
      "ca
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "std::uint16_t"
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
      "A runtime check must confirm whether the table at receiver+0x4c is rebuilt (dirty byte +0x78) at the moments 0x00bd8210 runs, since that is the only side effect on the path.",
      "No original-process trace has been captured for 0x00bd8210, so the claim that equal directions always quantise to equal indices is static-only.",
      "The 12-byte out buffer written by the slot +0x58 callee must be observed in a live process before its role can be named."
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
      "va": "0x00bf00a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf0110"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf0130"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf5720"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf8440"
    },
    {
      "name": "culture_selection_00bf9820",
      "reconstructed": true,
      "va": "0x00bf9820"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf9e70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bfa660"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bfb020"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ca8340"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d04320"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00bf00cb",
      "direction": "in",
      "other": "0x00bf00a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00bf011c",
      "direction": "in",
      "other": "0x00bf0110",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00bf016d",
      "direction": "in",
    
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
      "direct_xref_neighbor"
    ],
    "package": "PKG-13-C4-CIV-WAVE3",
    "score": 3,
    "symbol": "culture_selection_00bf9820",
    "va": "0x00bf9820"
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
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/wave13-w1-core-b10/b10_observed_types.hpp",
    "reconstruction/staging/wave13-w1-core-b10/bd8210_packed_direction.cpp",
    "reconstruction/staging/wave13-w1-core-b10/bd8210_packed_direction.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-core-b10/00bd8210.json"
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
    "A runtime check must confirm whether the table at receiver+0x4c is rebuilt (dirty byte +0x78) at the moments 0x00bd8210 runs, since that is the only side effect on the path.",
    "Eleven of the fourteen observed call sites in region 0x00bf0000 were not disassembled, so their use of the return value is unverified.",
    "Is 0x00b87dc0 a full rebuild of the table or an incremental update? Only the call site was read.",
    "Is the object at 0x0167eaf8 really a cGameInputManager? The SDK import names 0x00b3d350 as Simulator::cGameInputManager::Get, but the ModAPI header for that class declares neither the +0x4c table nor the +0x78 dirty byte, so the name may be right while the layout is a different class reached through the same accessor.",
    "No original-process trace exists for any function in this batch. Every statement here is static.",
    "No original-process trace has been captured for 0x00bd8210, so the claim that equal directions always quantise to equal indices is static-only.",
    "The 12-byte out buffer written by the slot +0x58 callee must be observed in a live process before its role can be named.",
    "The binary carries no MSVC RTTI, so no class identity can be read from typeinfo; class claims in this record rest only on observed vtable data and SDK header text.",
    "What are the 10 bits at 0x00b8875a? They index a 6*128*128*2-byte table, so they are a packed face/u/v code or a precomputed lighting, navigation or animation index. No writer of that table was located.",
    "What class owns 0x00bd8210? 
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-w1-core-b10/00bd8210.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b10/b10_observed_types.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b10/bd8210_packed_direction.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b10/bd8210_packed_direction.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave13-w1-core-b10/00bd8210.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b10/b10_observed_types.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b10/bd8210_packed_direction.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b10/bd8210_packed_direction.hpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.jso
[TRUNCATED]
```
