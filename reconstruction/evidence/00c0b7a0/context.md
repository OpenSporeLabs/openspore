# Reconstruction context 0x00c0b7a0

- Status: `partial`
- Content SHA-256: `e0f5e50f4a86158fe362ec3a8c72482fa68265423f5658ae4a984cc182228656`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00c0b7a0",
  "phase": "reconstruction",
  "target": "0x00c0b7a0"
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
  "va": "0x00c0b7a0"
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
  "content_sha256": "ccc2a6035631088b994749a3b39a4d10b1d697d4568181237e1268974db61a82",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00c0b7a0 failed: Decompilation did not complete. Reason: ",
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
  "hidden_receiver": "read once, at the first instruction only",
  "ordinary_stack_argument_slots": 0,
  "receiver": true,
  "ret_form": "RET",
  "return_note": "(boolean, 0 or 1)",
  "return_observation": "0x00c0b7ae SBB EAX,EAX and 0x00c0b7b0 NEG EAX together overwrite all 32 bits of EAX. Consumers agree the width is meaningful: 0x00d2c164 uses MOVZX ESI,AL, 0x00ba2835 and 0x00d2c1e6 use TEST AL,AL, and 0x00d2c156 uses SETZ CL over the AL byte. Had only AL been meaningful the compiler would have emitted SETNE AL rather than the SBB/NEG pair, so the dword width is the real contract.",
  "return_register": "EAX",
  "return_semantics": "A full dword in EAX that is exactly 0 or exactly 1, never an arbitrary true value and never a leftover pointer. The chain is: XOR ECX,ECX zeroes the compare operand; CMP ECX,[EAX + 0x60c] sets CF when the dword is non-zero; SBB EAX,EAX with EAX holding the sub-object pointer computes EAX - EAX - CF, i.e. 0xFFFFFFFF or 0; NEG then yields 1 or 0.",
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
      "name": null,
      "reconstructed": false,
      "va": "0x00ba27b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c042e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d2c000"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d342d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d3cdc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d581b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d58ea0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d5f780"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d841a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d87620"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d8f560"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00dbc7a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e8bf20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00f0e380"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00ba2830",
      "direction": "in",
      "other": "0x00ba27b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00ba2856",
      "direction": "in",
      "other": "0x00ba27b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00ba2866",
 
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "dword",
    "pointer to sub-object",
    "std::uint32_t (boolean, 0 or 1)"
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
      "A differential fixture is cheap but needs a receiver whose +0xb20 sub-object is constructed, which static evidence does not supply.",
      "No original-process trace exists for this address, so the runtime values of the +0x608 and +0x60c flag cluster are unverified.",
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
      "name": null,
      "reconstructed": false,
      "va": "0x00ba27b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c042e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d2c000"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d342d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d3cdc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d581b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d58ea0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d5f780"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d841a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d87620"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d8f560"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00dbc7a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e8bf20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00f0e380"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00ba2830",
      "direction": "in",
      "other": "0x00ba27b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00ba2856",
      "direction": "in",
      "other": "0x00ba27b0",
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
    "reconstruction/staging/wave13-w1-core-b09/b09_abi.hpp",
    "reconstruction/staging/wave13-w1-core-b09/sim_subflag_00c0b7a0.cpp",
    "reconstruction/staging/wave13-w1-core-b09/sim_subflag_00c0b7a0.hpp",
    "reconstruction/staging/wave13-w1-core-b09/sim_subflag_00c0b7a0_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-core-b09/00c0b7a0.json"
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
    "A differential fixture is cheap but needs a receiver whose +0xb20 sub-object is constructed, which static evidence does not supply.",
    "Is the receiver's +0xb20 pointer guaranteed non-null at every one of the 20 callsites? The body does not check it, so a null there would fault; no caller's guarantee was established.",
    "No original-process trace exists for this address, so the runtime values of the +0x608 and +0x60c flag cluster are unverified.",
    "No original-process trace exists, so the runtime values of the flag cluster are unverified.",
    "The Cell stage has never been entered in any recorded run, so nothing here is runtime observed.",
    "What are the globals 0x0156c194 and 0x0156c198 that the sibling accessor 0x00c0b8e0 is compared against in 0x00ba27b0? They were not read in this batch, so no value is claimed.",
    "What class owns this function? 20 live references, all UNCONDITIONAL_CALL, and no DATA reference, so it is not a vtable slot and no owner can be named.",
    "What does the flag at sub-object+0x60c mean? Its use as a symmetric per-object decision predicate is established; its game meaning is not.",
    "What is the relationship between the flag at +0x608 (tested by 0x00c0b780) and the one at +0x60c? They are independent as far as the observed code shows, but whether they are meant to be mutually exclusive is unknown.",
    "Who writes sub-object+0x60c, and who writes the +0xb20 pointer itself? No writer was found in this batch."
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-w1-core-b09/00c0b7a0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b09/b09_abi.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b09/sim_subflag_00c0b7a0.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b09/sim_subflag_00c0b7a0.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b09/sim_subflag_00c0b7a0_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave13-w1-core-b09/00c0b7a0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b09/b09_abi.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b09/sim_subflag_00c0b7a0.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b09/sim_subflag_00c0b7a0.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w
[TRUNCATED]
```
