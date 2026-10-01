# Reconstruction context 0x00c485b0

- Status: `partial`
- Content SHA-256: `25bb5b593ac2ffa468c009bdced2f14a7054b019e6ae3ea94618a08419e1db48`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00c485b0",
  "phase": "reconstruction",
  "target": "0x00c485b0"
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
  "va": "0x00c485b0"
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
  "content_sha256": "2e13b78386b9988fa84051f38952907bc359288735896b09b4891672e2c85ecf",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00c485b0 failed: Decompilation did not complete. Reason: ",
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
  "hidden_receiver": "read (by the tail callee, on this function's behalf)",
  "hidden_this_register": "ECX is passed through 0x00c485b0 unmodified: there is no MOV ECX,... in the body",
  "ordinary_stack_argument_slots": 0,
  "receiver": true,
  "receiver_register": "ECX",
  "ret_form": "RET (tail return after a callee-cleaned call)",
  "return_observation": "0x00c47d6c: ADD ESP,0x40 ; 0x00c47d6f: RET 4 leaves EAX exactly as 0x00c47cc0 received it, and 0x00c485b0 adds nothing to it",
  "return_register": "none",
  "return_semantics": "none: EAX is not written by 0x00c485b0 and the tail callee 0x00c47cc0 ends in ADD ESP,0x40 ; RET 4 without touching EAX on either exit path",
  "return_type": "void",
  "return_width_bytes": 0,
  "saved_registers": [],
  "stack_arguments": [],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "the caller, for 0x00c485b0; 0x00c47cc0 cleans its own single 4-byte word",
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
      "name": null,
      "reconstructed": false,
      "va": "0x00c47cc0"
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c59eb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c5a790"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fe9580"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0100e780"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0101246a"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01012aa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01012b50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01014540"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01014870"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01023fc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x010251e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0102d0b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0102df20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x010593e0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00c59edf",
      "direction": "in",
      "other": "0x00c59eb0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c5a7bb",
      "direction": "in",
      "other": "0x00c5a
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
      "A runtime differential test must confirm that 0x00c47cc0's RET 4 still matches in the shipping build, since the whole tail-call reading depends on it.",
      "No original-process trace has been captured for 0x00c485b0, so the claim that the +0x84 write is the only persistent effect is static-only.",
      "The value stored at +0x84 before and after each of the 16 call sites must be observed to confirm the idempotence guard is exercised rather than always false."
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
      "name": null,
      "reconstructed": false,
      "va": "0x00c47cc0"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c59eb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c5a790"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fe9580"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0100e780"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0101246a"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01012aa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01012b50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01014540"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01014870"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01023fc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x010251e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0102d0b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0102df20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x010593e0"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00c59edf",
      "direction": "in",
      "other": "0x00c59eb0",
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
    "reconstruction/staging/wave13-w1-core-b10/b10_observed_types.hpp",
    "reconstruction/staging/wave13-w1-core-b10/c485b0_set_mode2.cpp",
    "reconstruction/staging/wave13-w1-core-b10/c485b0_set_mode2.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-core-b10/00c485b0.json"
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
    "A runtime differential test must confirm that 0x00c47cc0's RET 4 still matches in the shipping build, since the whole tail-call reading depends on it.",
    "Fifteen of the sixteen observed call sites were not disassembled, so the context in which mode 2 is selected is unverified.",
    "Is 0x00c47d80 the same operation without the mode guard? Its body clears both buffers and then always runs the Init transition, with no comparison against the incoming value, which suggests the pair is 'transition unconditionally' versus 'transition if the mode actually changes'.",
    "No original-process trace exists for any function in this batch. Every statement here is static.",
    "No original-process trace has been captured for 0x00c485b0, so the claim that the +0x84 write is the only persistent effect is static-only.",
    "The binary carries no MSVC RTTI, so no class identity can be read from typeinfo; class claims in this record rest only on observed vtable data and SDK header text.",
    "The value stored at +0x84 before and after each of the 16 call sites must be observed to confirm the idempotence guard is exercised rather than always false.",
    "What class owns 0x00c485b0? The offset signature (+0x84 mode, +0x14c/+0x150 and +0x15c/+0x160 wchar cursors, +0x194 kind) matches no ModAPI declaration, and no vtable for the receiver was located.",
    "What is the value 3 that unlocks the App::IAppSystem::Init(0x13eb844) transition, and which caller performs it? Only 0x00c485b0 (value 2) and 0x00c47d80 (unconditional variant) w
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-w1-core-b10/00c485b0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b10/b10_observed_types.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b10/c485b0_set_mode2.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b10/c485b0_set_mode2.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave13-w1-core-b10/00c485b0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b10/b10_observed_types.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b10/c485b0_set_mode2.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b10/c485b0_set_mode2.hpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.json"
  ],
  "req
[TRUNCATED]
```
