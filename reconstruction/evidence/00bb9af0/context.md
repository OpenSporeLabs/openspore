# Reconstruction context 0x00bb9af0

- Status: `partial`
- Content SHA-256: `ba98e809b4a4ddc83594f76e1fa1a0690be70b3f58fd9d6bac34f6d447db8ad3`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00bb9af0",
  "phase": "reconstruction",
  "target": "0x00bb9af0"
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
  "va": "0x00bb9af0"
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
  "content_sha256": "9fa070f257b6fe2f09515e86de29e96a175ce1b8ae0af49c7fd025edc8246b7d",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00bb9af0 failed: Decompilation did not complete. Reason: ",
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
  "hidden_receiver": "unread by the mask itself; the receiver's +0x5C field IS read, so the receiver must be non-null",
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": 1,
  "receiver": true,
  "ret_form": "RET 0x4",
  "return_observation": "0x00bb9af7 NEG EAX sets CF from the operand's sign, 0x00bb9af9 SBB EAX,EAX yields 0 (CF clear) or 0xFFFFFFFF (CF set), and 0x00bb9afb NEG EAX maps those to 0 and 1. The full dword is therefore written and bits 8..31 are zero. Every consumer tests AL, never the full dword.",
  "return_register": "EAX",
  "return_semantics": "true iff at least one bit selected by `mask` is set in the receiver's +0x5C dword; the result is exactly 0 or 1, never a mask value",
  "return_type": "bool",
  "return_width_bytes": 4,
  "saved_registers": [],
  "stack_arguments": [
    {
      "instruction": "0x00bb9af3: AND EAX,dword ptr [ESP + 0x4]",
      "offset": "ESP+0x4",
      "role": "bit mask",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "callee",
  "termination": "RET 0x4 at 0x00bb9afd"
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
      "va": "0x00b93550"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b96d40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba6bb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba6f20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba8830"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00badd10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb2070"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb21b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb2330"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb4100"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb6040"
    },
    {
      "name": "FUN_00c47e20",
      "reconstructed": false,
      "va": "0x00c47e20"
    },
    {
      "name": "FUN_00c59240",
      "reconstructed": false,
      "va": "0x00c59240"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c59540"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c5f770"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c8b560"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00b93574",
      "direction": "in",
      "other": "0x00b93550",
      "reference_type": "
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
      "A runtime differential test would have to confirm the flag word's value for a known star system, which is the only way to attach a meaning to individual bits.",
      "Because the function dereferences ECX with no null check, a runtime test that passes a null receiver would fault; that is a property of the original and must be preserved, not defended against.",
      "No original-process trace has ever been captured for this function; the original Cell stage has never been entered in any recorded run. Every claim here is static."
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
      "va": "0x00b93550"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b96d40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba6bb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba6f20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba8830"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00badd10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb2070"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb21b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb2330"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb4100"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb6040"
    },
    {
      "name": "FUN_00c47e20",
      "reconstructed": false,
      "va": "0x00c47e20"
    },
    {
      "name": "FUN_00c59240",
      "reconstructed": false,
      "va": "0x00c59240"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c59540"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c5f770"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c8b560"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00df7f60"
    },
    {
      "name": 
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
    "reconstruction/staging/wave13-w1-core-b06/bb9af0_star_record_flag_test.cpp",
    "reconstruction/staging/wave13-w1-core-b06/sim_core_b06_model_test.cpp",
    "reconstruction/staging/wave13-w1-core-b06/sim_core_b06_opaque.hpp",
    "reconstruction/staging/wave13-w1-core-b06/sim_core_b06_ports_model.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-core-b06/00bb9af0.json"
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
    "A runtime differential test would have to confirm the flag word's value for a known star system, which is the only way to attach a meaning to individual bits.",
    "Because the function dereferences ECX with no null check, a runtime test that passes a null receiver would fault; that is a property of the original and must be preserved, not defended against.",
    "Does any caller pass a multi-bit mask? The AND would handle it as ANY, but all five inspected callsites pass a single bit, so multi-bit use is supported by the body and unconfirmed by any caller.",
    "Is this function reachable through a vtable? Every observed call is a direct CALL and no table slot was located for 0x00bb9af0, so its interface status, if any, is unestablished.",
    "No original-process trace has ever been captured for this function; the original Cell stage has never been entered in any recorded run. Every claim here is static.",
    "The briefing's canonical ledger recorded caller_count 20; the live query also returns 20 caller functions but 25 call sites, because 0x00ba6f20, 0x00b96d40 and 0x00bb2070/0x00bb21b0 call it more than once. The fan-in figure is not a contradiction, only a different counting convention.",
    "What does each individual bit of mFlags mean? Bits 0, 1, 2, 8, 13, 17 and 31 were observed at callsites, but no flag name was established for any of them. Spore-ModAPI's own comment on this field ('TODO 1 << 4 (16) is visited?') shows the upstream project has not settled the bit assignment either.",
    "Why is the return va
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-w1-core-b06/00bb9af0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b06/bb9af0_star_record_flag_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b06/sim_core_b06_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b06/sim_core_b06_opaque.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b06/sim_core_b06_ports_model.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave13-w1-core-b06/00bb9af0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b06/bb9af0_star_record_flag_test.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b06/sim_core_b06_model_test.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b06/sim_core_b06_opaque.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstr
[TRUNCATED]
```
