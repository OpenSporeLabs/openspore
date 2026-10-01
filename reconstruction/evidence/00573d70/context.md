# Reconstruction context 0x00573d70

- Status: `partial`
- Content SHA-256: `3afd43d4da551954baa64abc6e7e75d6263d66d433a9b0dfb817099edaf92d8d`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00573d70",
  "phase": "reconstruction",
  "target": "0x00573d70"
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
  "va": "0x00573d70"
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
  "content_sha256": "a357f92a3d4a9f6414791903d552f7386f5ee98c849ef49d24c8bda8386df9c7",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00573d70 failed: Decompilation did not complete. Reason: ",
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
  "ordinary_stack_argument_slots": 2,
  "receiver_register": "ECX, moved to ESI at 0x00573d77",
  "ret_form": "RET 0x8",
  "return_observation": "0x00573ef9..0x00573f04 and 0x00573f12..0x00573f16 are the two exits, both ending in RET 0x8 with no value contract. Every sampled caller discards the result.",
  "return_register": "none (void)",
  "return_semantics": "No value is returned. EAX and EBP are used as scratch; the two exits differ in whether EBP is restored before the pops, and neither leaves a meaningful EAX that any caller could use.",
  "return_type": "void",
  "return_width_bytes": 0,
  "saved_registers": [
    "EBX",
    "ESI",
    "EDI",
    "EBP"
  ],
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x4 at entry, loaded as [ESP+8] after the PUSH EBX at 0x00573d70",
      "name": "part",
      "observed_uses": [
        "null test at 0x00573d79",
        "primary comparison at 0x00573d98",
        "secondary comparison at 0x00573dbd",
        "attribute-bit-11 test at 0x00573de5..0x00573dfd",
        "publish at 0x00573e7a",
        "indirect slot +0x00 and slot +0x04 calls at 0x00573e78 and 0x00573e88"
      ],
      "read_evidence": "0x00573d71: MOV EBX,dword ptr [ESP + 0x8]; the same word is re-read at 0x00573e5d: MOV EBX,dword ptr [ESP + 0x14] after the PUSH EBP at 0x00573e06",
      "type": "void* (refcounted editor part pointer)",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x8 at entry, i.e. the second callee-cleaned wor
[TRUNCATED]
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
      "va": "0x00573c00"
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00577520"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0057e790"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0057f6c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00587270"
    },
    {
      "name": "Editors::cEditor::OnExit",
      "reconstructed": false,
      "va": "0x00587a20"
    },
    {
      "name": "editor_input_00588570",
      "reconstructed": true,
      "va": "0x00588570"
    },
    {
      "name": "editor_input_0058ac10",
      "reconstructed": true,
      "va": "0x0058ac10"
    },
    {
      "name": "editor_input_0058b650",
      "reconstructed": true,
      "va": "0x0058b650"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0058ba60"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00577573",
      "direction": "in",
      "other": "0x00577520",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0057e810",
      "direction": "in",
      "other": "0x0057e790",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0058025f",
      "direction": "in",
      "other": "0x0057f6c0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00587498",
      "direction": "in",
      "other": "0x00587270",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00587d06",
 
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "std::uint32_t, value not established",
    "void",
    "void* (refcounted editor part pointer)"
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
      "A differential fixture would need to drive the editor through at least four transitions -- null-to-part, part-to-part, part-to-null and a 0x50a993c part swap -- and record whether the +0x141 handshake fires and in what order.",
      "No original-process trace exists. Every flag value, every attribute bit, every list index and both 0x50a993c comparisons in the contract above are static readings of the code path, not observations.",
      "The original Cell stage has never been entered in any recorded run, so no stage-level reachability claim is made for this Editor-subsystem function."
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
      "va": "0x00573c00"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00577520"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0057e790"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0057f6c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00587270"
    },
    {
      "name": "Editors::cEditor::OnExit",
      "reconstructed": false,
      "va": "0x00587a20"
    },
    {
      "name": "editor_input_00588570",
      "reconstructed": true,
      "va": "0x00588570"
    },
    {
      "name": "editor_input_0058ac10",
      "reconstructed": true,
      "va": "0x0058ac10"
    },
    {
      "name": "editor_input_0058b650",
      "reconstructed": true,
      "va": "0x0058b650"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0058ba60"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00577573",
      "direction": "in",
      "other": "0x00577520",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0057e810",
      "direction": "in",
      "other": "0x0057e790",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0058025f",
      "direction": "in",
      "other": "0x0057f6c0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00587498",
      "direction": "in",
      "other": "0x00587270",
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
    "package": "PKG-EDITOR-INPUT-WAVE6",
    "score": 3,
    "symbol": "editor_input_00588570",
    "va": "0x00588570"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-EDITOR-INPUT-WAVE6",
    "score": 3,
    "symbol": "editor_input_0058ac10",
    "va": "0x0058ac10"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-EDITOR-INPUT-WAVE6",
    "score": 3,
    "symbol": "editor_input_0058b650",
    "va": "0x0058b650"
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
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/wave13-w1-dispatch-b01/00573d70_set_primary_part.cpp",
    "reconstruction/staging/wave13-w1-dispatch-b01/00573d70_set_primary_part.hpp",
    "reconstruction/staging/wave13-w1-dispatch-b01/opaque_types.hpp",
    "reconstruction/staging/wave13-w1-dispatch-b01/wave13_b01_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-dispatch-b01/00573d70.json"
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
    "A differential fixture would need to drive the editor through at least four transitions -- null-to-part, part-to-part, part-to-null and a 0x50a993c part swap -- and record whether the +0x141 handshake fires and in what order.",
    "Is 0x00572020 really Audio::StopAudio? The SDK lists its address and the argument shape matches, but the first argument passed here is the cEditor pointer rather than an AudioTrack and the callee tail-jumps into a service vtable.",
    "No original-process trace exists. Every flag value, every attribute bit, every list index and both 0x50a993c comparisons in the contract above are static readings of the code path, not observations.",
    "Six of the ten reported call sites were not disassembled window-by-window in this batch; their receiver provenances come from the briefing's call graph.",
    "The original Cell stage has never been entered in any recorded run, so no stage-level reachability claim is made for this Editor-subsystem function.",
    "What class implements the part's vtable? Six slot offsets were disassembled (+0x00, +0x04, +0x0c, +0x10, +0x30 and the two marker-service slots) but no table address was resolved, so the interface is unnamed.",
    "What do the flag bytes at +0x140 and +0x141 mean? Their complete read/write sets are established -- +0x140 is raised in three places, cleared in one and tested in one; +0x141 is set once, cleared once and tested once -- but nothing names either.",
    "What is editor+0xf4, and is it really unrefcounted? The body clears it with no Releas
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-w1-dispatch-b01/00573d70.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b01/00573d70_set_primary_part.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b01/00573d70_set_primary_part.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b01/opaque_types.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b01/wave13_b01_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave13-w1-dispatch-b01/00573d70.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b01/00573d70_set_primary_part.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b01/00573d70_set_primary_part.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b01/opaque_types.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "
[TRUNCATED]
```
