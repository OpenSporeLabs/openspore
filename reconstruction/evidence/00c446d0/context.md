# Reconstruction context 0x00c446d0

- Status: `partial`
- Content SHA-256: `9cbffd753f3ffd18dbc457575a9b6baee93a5162f8ab2a78a41b3db8d02c13ec`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00c446d0",
  "phase": "reconstruction",
  "target": "0x00c446d0"
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
  "va": "0x00c446d0"
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
  "content_sha256": "2c0274480a7857eb208216a152012b1ef8b66ce9526532ed01a2eb1d684b976e",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00c446d0 failed: Decompilation did not complete. Reason: ",
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
  "hidden_receiver": "read; ADD ECX,0xF0 then [ECX+0x00], [ECX+0x04] and [ECX+0x08] are the container's three cursors. A null receiver faults at 0x00c446f0's ADD is harmless but the first dereference at 0x00c4470f or 0x00c44721 is not.",
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": 2,
  "receiver": true,
  "ret_form": "RET 0x8 (at 0x00c4471e, 0x00c44749 and 0x00c44759)",
  "return_observation": "all three exits are RET 0x8 with no value contract; the two callees' returns are discarded at 0x00c4471b and 0x00c44756, and 0x00c43f20's iterator result is dropped even though the callee computes one.",
  "return_register": "none - EAX is used for the argument pointer, the grow-path position and the callee's discarded return; no exit value is consumed",
  "return_semantics": "none; the only effect is the growth of the vector member at receiver+0xF0 and the write of one 16-byte element into it",
  "return_type": "void",
  "return_width_bytes": 0,
  "saved_registers": [
    "ESI"
  ],
  "stack_arguments": [
    {
      "instruction": "0x00c446d3: MOV EAX,dword ptr [ESP + 0x14]",
      "offset": "ESP+0x4 at entry (read as [ESP+0x14] after the SUB)",
      "role": "pointer to three consecutive floats, the position to record",
      "width_bytes": 4
    },
    {
      "instruction": "0x00c446e5: MOV AL,byte ptr [ESP + 0x18]",
      "offset": "ESP+0x8 at entry (read as [ESP+0x18] after the SUB)",
      "role": "direction and stored tag: non-zero selects prepend and is normalised to the tag value 1"
[TRUNCATED]
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
      "va": "0x00b34380"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b452f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c0eec0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c13650"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c13a30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c18370"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c18740"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c18b40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c190e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c1a3c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c1b020"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c20230"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c2a190"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00f235e0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00b345dc",
      "direction": "in",
      "other": "0x00b34380",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00b45341",
      "direction": "in",
      "other": "0x00b452f0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c0f21e",
 
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
      "Confirming that the growth policy is reached with capacity exactly 1 on the first append requires a runtime allocation trace, since the arithmetic is only reached through the callee.",
      "No original-process trace has ever been captured for this function; the original Cell stage has never been entered in any recorded run. Every claim here is static.",
      "The container is empty in the shipping image and the owning subsystem was never started in any recorded run, so the grow path, the prepend path and the inlined append path have all never been observed executing.",
      "The null-cursor behaviour can only be exercised by a container whose insert cursor is null while its end cursor is not, i.e. a corrupt or deliberately initialised state. A runtime test must construct that state deliberately to confirm the original leaves the advanced cursor behind.",
      "The tag dword's meaning requires observing how the list is consumed after insertions from both ends. A differential trace that records the list contents after a prepend-then-append sequence would settle it; nothing static can."
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
      "va": "0x00b34380"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b452f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c0eec0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c13650"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c13a30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c18370"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c18740"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c18b40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c190e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c1a3c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c1b020"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c20230"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c2a190"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00f235e0"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00b345dc",
      "direction": "in",
      "other": "0x00b34380",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00b45341",
      "direction": "in",
      "other": "0x00b452f0",
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
    "reconstruction/staging/wave13-w1-core-b06/c446d0_tagged_vector3_push.cpp",
    "reconstruction/staging/wave13-w1-core-b06/sim_core_b06_model_test.cpp",
    "reconstruction/staging/wave13-w1-core-b06/sim_core_b06_opaque.hpp",
    "reconstruction/staging/wave13-w1-core-b06/sim_core_b06_ports_model.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-core-b06/00c446d0.json"
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
    "Confirming that the growth policy is reached with capacity exactly 1 on the first append requires a runtime allocation trace, since the arithmetic is only reached through the callee.",
    "Is the null-cursor advance a latent bug in the original? The function leaves receiver+0xF4 set to 0x10 when the cursor was null, so a subsequent call would write to address 0x10. Either the null case is unreachable in practice, or the original tolerates the corruption. Static evidence cannot decide, and the behaviour is preserved rather than defended against.",
    "No original-process trace has ever been captured for this function; the original Cell stage has never been entered in any recorded run. Every claim here is static.",
    "The briefing's canonical ledger recorded caller_count 14 and callee_count 2; both match the live xref query. The briefing's dependency list also omits the two indirect calls through vtable-loaded EDX at 0x00baf763-style sites, but this function has none, so there is no discrepancy to report here.",
    "The container is empty in the shipping image and the owning subsystem was never started in any recorded run, so the grow path, the prepend path and the inlined append path have all never been observed executing.",
    "The null-cursor behaviour can only be exercised by a container whose insert cursor is null while its end cursor is not, i.e. a corrupt or deliberately initialised state. A runtime test must construct that state deliberately to confirm the original leaves the advanced cursor behind.",
    "Th
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-w1-core-b06/00c446d0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b06/c446d0_tagged_vector3_push.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b06/sim_core_b06_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b06/sim_core_b06_opaque.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b06/sim_core_b06_ports_model.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave13-w1-core-b06/00c446d0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b06/c446d0_tagged_vector3_push.cpp",
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
      "ref": "reconstruc
[TRUNCATED]
```
