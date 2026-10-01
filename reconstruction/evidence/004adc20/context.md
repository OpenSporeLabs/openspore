# Reconstruction context 0x004adc20

- Status: `partial`
- Content SHA-256: `e5995d7e1b734ed6321c8d35ecf959171729602b2d044f4dc82f9a563753eba7`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x004adc20",
  "phase": "reconstruction",
  "target": "0x004adc20"
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
  "va": "0x004adc20"
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
  "content_sha256": "43c31d026ff92d7fa374cd6e167ba27f54844916b8b11810ab945093465c49d2",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x004adc20 failed: Decompilation did not complete. Reason: ",
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
  "architecture": "x86-32 (x86:LE:32:windows, image base 0x00400000)",
  "calling_convention": "__thiscall",
  "ordinary_stack_argument_slots": 1,
  "receiver_register": "ECX",
  "ret_form": "RET 0x4",
  "return_observation": "0x004adc30: MOV ESP,EBP / 0x004adc32: POP EBP / 0x004adc33: RET 0x4 with no meaningful EAX. No sampled caller reads a result.",
  "return_register": "none (void)",
  "return_semantics": "No value is returned. EAX is used only as scratch; on the only path through the function the last write to EAX is the reload of the spilled receiver at 0x004adc27.",
  "return_type": "void",
  "return_width_bytes": 0,
  "saved_registers": [
    "EBP"
  ],
  "stack_arguments": [
    {
      "entry_offset": "EBP+0x8",
      "name": "value",
      "narrowing_note": "The body reads only the low byte of the incoming word. Bits 8..31 of the caller's stack word are discarded, so a caller passing 0x00000101 stores 0x01. The reconstruction makes this explicit by typing the parameter std::uint8_t rather than relying on an implicit truncation.",
      "read_evidence": "0x004adc2a: MOV CL,byte ptr [EBP + 0x8]",
      "type": "std::uint8_t in a 4-byte ABI word",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "callee",
  "termination": "single exit at 0x004adc33"
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
      "va": "0x0043fc20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0048f790"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004934d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0049d6b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004a6ca0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004a6d20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004a6f10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00582250"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00586960"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00586b00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005b4bf0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005b74f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005b75e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005b8fb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005be500"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005d02d0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x0043fc88",
      "direction": "in",
      "other": "0x0043fc20",
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
    "std::uint8_t in a 4-byte ABI word",
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
      "A runtime pass would need to set the flag through a known call site and observe the paired 0x004adc40 read, to confirm the pairing and to see which values are stored.",
      "No original-process trace exists, so the claim that this flag is written and later read with a meaning is static only.",
      "The original Cell stage has never been entered in any recorded run, so no stage-level reachability claim is made."
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
      "va": "0x0043fc20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0048f790"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004934d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0049d6b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004a6ca0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004a6d20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004a6f10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00582250"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00586960"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00586b00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005b4bf0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005b74f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005b75e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005b8fb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005be500"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005d02d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005d07f0"
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
    "reconstruction/staging/wave13-w1-dispatch-b01/004adc20_set_flag4f.cpp",
    "reconstruction/staging/wave13-w1-dispatch-b01/004adc20_set_flag4f.hpp",
    "reconstruction/staging/wave13-w1-dispatch-b01/opaque_types.hpp",
    "reconstruction/staging/wave13-w1-dispatch-b01/wave13_b01_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-dispatch-b01/004adc20.json"
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
    "A runtime pass would need to set the flag through a known call site and observe the paired 0x004adc40 read, to confirm the pairing and to see which values are stored.",
    "Do all seventeen callers pass the same concrete receiver type? Their receiver provenances were not disassembled window-by-window in this batch, so only the fan-in of 17 is independently confirmed.",
    "Is the byte a bool, a small enum or a bitfield-style flag? Callers only ever store whole bytes and the paired getter is only ever tested for zero, so the evidence cannot separate these.",
    "Is the redundant spill in all ten family members an artefact of a specific build configuration? It affects no semantics and is not worth further investigation, but it is unexplained.",
    "No original-process trace exists, so the claim that this flag is written and later read with a meaning is static only.",
    "The original Cell stage has never been entered in any recorded run, so no stage-level reachability claim is made.",
    "What class owns this sub-object? Two proven provenances (cEditor+0x98 through the +0x44 getter's callers, and rigblock+0x28 through 0x00438700) do not converge on a named type, and no vtable was located.",
    "What does the byte at +0x4f mean, and what are the other three flags in the block for? Seventeen call sites were found and none of them was interpreted, so the value's role is unestablished.",
    "Why does +0x4e have a setter but no getter in this family, and why does +0x48 have a setter but no float getter? Either they are 
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-w1-dispatch-b01/004adc20.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b01/004adc20_set_flag4f.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b01/004adc20_set_flag4f.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b01/opaque_types.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b01/wave13_b01_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave13-w1-dispatch-b01/004adc20.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b01/004adc20_set_flag4f.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b01/004adc20_set_flag4f.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b01/opaque_types.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstructi
[TRUNCATED]
```
