# Reconstruction context 0x004c49e0

- Status: `partial`
- Content SHA-256: `9e69ebcc504ebc6a5b514ac7a8dc1d2a58e9872022a0a42be99f4e4db081b256`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x004c49e0",
  "phase": "reconstruction",
  "target": "0x004c49e0"
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
  "va": "0x004c49e0"
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
  "content_sha256": "b46bf621a9e87649967bcea8c7f381e4ce91a4d84c8672a825f2e6044ba5ad19",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x004c49e0 failed: Decompilation did not complete. Reason: ",
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
  "return_note": "(32-bit pointer-like dword)",
  "return_observation": "0x004c4a00 MOV EDX,dword ptr [ECX+0x18] and 0x004c4a10 MOV ECX,dword ptr [EAX+0x1c] are dword loads, and 0x004c4a06 / 0x004c4a16 copy the full 32 bits into EAX. 0x004c4a1b XOR EAX,EAX zeroes all 32 bits, so the default is a dword 0 and not a byte 0.",
  "return_register": "EAX",
  "return_semantics": "Either the dword stored at receiver+0x18, the dword stored at receiver+0x1c, or the literal 0, chosen by the index argument. Every observed consumer branches on the result being null and then dereferences it, so the value is an object pointer.",
  "return_type": "void*",
  "return_width_bytes": 4,
  "saved_registers": [
    "EBP"
  ],
  "stack_arguments": [
    {
      "entry_offset": "EBP+0x8",
      "name": "index",
      "observed_values": [
        "0x0 at 0x005ab6ff and 0x005ab710",
        "0x1 at seventeen inspected and reported sites including 0x0058757a, 0x0058bfeb, 0x005930b9, 0x00583126"
      ],
      "read_evidence": "0x004c49e9: MOV EAX,dword ptr [EBP + 0x8]",
      "type": "std::uint32_t",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "callee",
  "termination": "single exit at 0x004c4a20"
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
      "va": "0x00574a20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00577620"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00577dd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0057af00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0057c590"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0057e220"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0057e480"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0057f6c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00582fe0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00585330"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00587270"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0058a350"
    },
    {
      "name": "Editors::cEditor::Update",
      "reconstructed": false,
      "va": "0x0058be50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0058d1c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00591690"
    },
    {
      "name": "Editors::cEditor::HandleMessage",
      "reconstructed": false,
      "va": "0x00591fa0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00574a3c",
      "direction": "in",
      "other": "0x00574
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "std::uint32_t",
    "void* (32-bit pointer-like dword)"
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
      "A runtime differential test would have to record the two slot values at a few of the call sites to confirm which objects are returned in practice.",
      "No original-process trace exists for this function, so the claim that both arms return live object pointers is static only.",
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
  "callees": [],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00574a20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00577620"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00577dd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0057af00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0057c590"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0057e220"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0057e480"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0057f6c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00582fe0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00585330"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00587270"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0058a350"
    },
    {
      "name": "Editors::cEditor::Update",
      "reconstructed": false,
      "va": "0x0058be50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0058d1c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00591690"
    },
    {
      "name": "Editors::cEditor::HandleMessage",
      "reconstructed": false,
      "va": "0x00591fa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005aa7
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
    "reconstruction/staging/wave13-w1-dispatch-b01/004c49e0_pick.cpp",
    "reconstruction/staging/wave13-w1-dispatch-b01/004c49e0_pick.hpp",
    "reconstruction/staging/wave13-w1-dispatch-b01/opaque_types.hpp",
    "reconstruction/staging/wave13-w1-dispatch-b01/wave13_b01_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-dispatch-b01/004c49e0.json"
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
    "A runtime differential test would have to record the two slot values at a few of the call sites to confirm which objects are returned in practice.",
    "Fifteen of the thirty-three code xrefs were not disassembled window-by-window in this batch; their receiver provenances and result uses come from the briefing's call graph.",
    "Is the i>=2 -> 0 default a shipped guard or a compiler-generated default for an enum-like selector? No caller in this batch ever passes i >= 2, so the answer is not observable statically.",
    "No original-process trace exists for this function, so the claim that both arms return live object pointers is static only.",
    "The 0x00574a20 wrapper forces index 1 regardless of its own incoming argument; whether some caller relies on reaching the +0x18 arm through that wrapper was not established.",
    "The original Cell stage has never been entered in any recorded run, so no stage-level reachability claim is made for this Editor-subsystem function.",
    "What concrete type owns slots +0x18 and +0x1c? Three different receiver provenances (cEditor+0x150, cEditor+0x140, unrelated+0xe0) and no located vtable mean no single owner can be named.",
    "What do the two slots point at? 0x005ab717 shows the returned value is dereferenced at +0x34 and 0x0058c585 at +0x8, so it is an object pointer, but the object type is unresolved.",
    "Which writer maintains the two slots? No store to receiver+0x18 or receiver+0x1c was located in this batch, so the invariant that keeps them non-null at the observed c
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-w1-dispatch-b01/004c49e0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b01/004c49e0_pick.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b01/004c49e0_pick.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b01/opaque_types.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b01/wave13_b01_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave13-w1-dispatch-b01/004c49e0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b01/004c49e0_pick.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b01/004c49e0_pick.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b01/opaque_types.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/w
[TRUNCATED]
```
