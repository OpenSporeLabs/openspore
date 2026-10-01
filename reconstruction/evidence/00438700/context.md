# Reconstruction context 0x00438700

- Status: `partial`
- Content SHA-256: `434f403f05c2b06f5bad9f5ec3d53e95f160f57d1c62d9eba1372295312cbba4`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00438700",
  "phase": "reconstruction",
  "target": "0x00438700"
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
  "va": "0x00438700"
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
  "content_sha256": "68e7bf31bd5558bb097516e722ebece9ae48e9870473bd5cbf962cd6805c1d6a",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00438700 failed: Decompilation did not complete. Reason: ",
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
  "return_observation": "0x004388a2: MOV ESP,EBP / 0x004388a4: POP EBP / 0x004388a5: RET 0x4 with no value in EAX that any caller could use; the sampled callers all discard the result.",
  "return_register": "none (void)",
  "return_semantics": "No value is returned. EAX is used only as scratch; the last write to EAX on any path is either the flag byte at 0x00438777 / 0x0043877c / 0x00438845 / 0x0043884a or the address 0x0043882c used to set up the bit mask.",
  "return_type": "void",
  "return_width_bytes": 0,
  "saved_registers": [
    "EBP"
  ],
  "stack_arguments": [
    {
      "entry_offset": "EBP+0x8",
      "name": "other",
      "observed_uses": [
        "0x0043874d: MOV ECX,dword ptr [EAX + EDX*0x4 + 0xdc8] -- bit 7 of the other object's attribute field",
        "0x004387a1 / 0x004387b3: MOV EDX / MOV ECX,dword ptr [ECX + 0x3e0] -- the other object's sub-object",
        "0x00438710: PUSH EAX then CALL 0x004388b0"
      ],
      "read_evidence": "0x00438709: MOV EAX,dword ptr [EBP + 0x8]",
      "type": "OpaqueEditorRigblock* (pointer-like)",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "callee",
  "termination": "single shared exit at 0x004388a2 reached by every path"
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "FUN_004adc40",
      "reconstructed": false,
      "va": "0x004adc40"
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00437b00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00487040"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0048f790"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0048fde0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0049a2a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0049cb90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0049cfd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0049d6b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004a0bf0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004a1070"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004a2350"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004a29a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004a6f10"
    },
    {
      "name": "editor_input_0058ac10",
      "reconstructed": true,
      "va": "0x0058ac10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005ad5d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005b7cf0"
    }
  ],
  "edge_rows": [
    {
      "callsi
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "OpaqueEditorRigblock* (pointer-like)",
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
      "A differential fixture would need to drive the editor with one rigblock whose bit 7 is set and one whose bit 11 is set, to see which branch actually fires.",
      "No original-process trace exists. Every flag value, every +0x1c0 value and every 0x004a7e60 result in the contract above is a static reading of the code path, not an observation.",
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
  "callees": [
    {
      "name": "FUN_004adc40",
      "reconstructed": false,
      "va": "0x004adc40"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00437b00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00487040"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0048f790"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0048fde0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0049a2a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0049cb90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0049cfd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0049d6b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004a0bf0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004a1070"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004a2350"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004a29a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004a6f10"
    },
    {
      "name": "editor_input_0058ac10",
      "reconstructed": true,
      "va": "0x0058ac10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005ad5d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005b7cf0"
    },
    {
    
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
    "symbol": "editor_input_0058ac10",
    "va": "0x0058ac10"
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
    "reconstruction/staging/wave13-w1-dispatch-b01/00438700_cascade.cpp",
    "reconstruction/staging/wave13-w1-dispatch-b01/00438700_cascade.hpp",
    "reconstruction/staging/wave13-w1-dispatch-b01/opaque_types.hpp",
    "reconstruction/staging/wave13-w1-dispatch-b01/wave13_b01_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-dispatch-b01/00438700.json"
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
    "A differential fixture would need to drive the editor with one rigblock whose bit 7 is set and one whose bit 11 is set, to see which branch actually fires.",
    "Are self and other guaranteed distinct? 0x00437b00's own guard suggests not, and this function has none.",
    "Is the receiver really Editors::EditorRigblock? Three independent observations support it -- the 0x3c-bit attribute field, the 0xe08 'Editor' allocation with bit 0x14 set, and the shared +0x28 / +0x4f / +0x3e0 guard triple -- but no vtable was resolved and the binary has no RTTI, so this stays a candidate.",
    "No original-process trace exists. Every flag value, every +0x1c0 value and every 0x004a7e60 result in the contract above is a static reading of the code path, not an observation.",
    "Only three of the twenty-one call sites were disassembled window-by-window in this batch; the remaining eighteen receiver provenances were taken from the briefing's call graph and were not independently re-verified at the instruction level.",
    "The original Cell stage has never been entered in any recorded run, so no stage-level reachability claim is made.",
    "What does the dword at +0x1c0 mean, and why does a zero there permit the cascade? The field is named only as an offset.",
    "What is 0x004a7e60 deciding? It is a two-level byte predicate with an unknown name, and its result gates the entire second half of this function.",
    "What is attribute bit 11? The SDK enum has no enumerator at 0x0B and duplicates 0x0A, so no name is asserted.",
    "What
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-w1-dispatch-b01/00438700.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b01/00438700_cascade.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b01/00438700_cascade.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b01/opaque_types.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b01/wave13_b01_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave13-w1-dispatch-b01/00438700.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b01/00438700_cascade.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b01/00438700_cascade.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b01/opaque_types.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/sta
[TRUNCATED]
```
