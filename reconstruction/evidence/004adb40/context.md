# Reconstruction context 0x004adb40

- Status: `partial`
- Content SHA-256: `a2f193ebf9a6e7ba39628d60904ca4ec2481e5935e2589902803fe4e31b75b6b`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x004adb40",
  "phase": "reconstruction",
  "target": "0x004adb40"
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
  "va": "0x004adb40"
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
  "content_sha256": "6577999590d7c7e646f3dd83338a321fccb679711ed80e621897ef3f12f22b26",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x004adb40 failed: Decompilation did not complete. Reason: ",
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
  "ordinary_stack_argument_slots": 0,
  "receiver_register": "ECX",
  "ret_form": "RET",
  "return_note": "(IEEE-754 binary32)",
  "return_observation": "0x004adb4a FLD float ptr [EAX + 0x44] performs a 4-byte memory load and pushes exactly one x87 register. 0x004adb4d MOV ESP,EBP and 0x004adb4f POP EBP unwind the integer frame without touching the x87 stack, so the loaded value survives the epilogue in ST(0). Every sampled call site consumes it with an immediate FSTP or FCOMIP and none reads EAX afterwards.",
  "return_register": "ST(0) (the x87 register stack, not a GPR)",
  "return_semantics": "The exact 32-bit pattern stored at receiver+0x44, widened to a float and left in x87 register ST(0). No conversion, no normalisation, no scaling and no default.",
  "return_type": "float",
  "return_width_bytes": 4,
  "saved_registers": [
    "EBP"
  ],
  "stack_arguments": [],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "not applicable; there is no stack argument",
  "termination": "single exit at 0x004adb50"
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
      "va": "0x00486910"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0048dcd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0049a2a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00586b00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005addb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005ae300"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005b9840"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005be500"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005d36e0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x0043fd9d",
      "direction": "in",
      "other": "0x0043fc20",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x004869ed",
      "direction": "in",
      "other": "0x00486910",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0048ddeb",
      "direction": "in",
      "other": "0x0048dcd0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0049ad1e",
      "direction": "in",
      "other": "0x0049a2a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0049ae22",
      "direction": "in",
      "other": "0x0049a2a0",
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
    "float (IEEE-754 binary32)"
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
      "A runtime pass would need to sample the field at a known call site, for example around 0x00586f10, to see the value the original actually compares against.",
      "No original-process trace exists, so the claim that the field holds a live float in the shipping build is static only.",
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
      "va": "0x00486910"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0048dcd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0049a2a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00586b00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005addb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005ae300"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005b9840"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005be500"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005d36e0"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x0043fd9d",
      "direction": "in",
      "other": "0x0043fc20",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x004869ed",
      "direction": "in",
      "other": "0x00486910",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0048ddeb",
      "direction": "in",
      "other": "0x0048dcd0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0049ad1e",
      "direction": "in",
      "other": "0x0049a2a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0049a
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
    "reconstruction/staging/wave13-w1-dispatch-b01/004adb40_get_field44.cpp",
    "reconstruction/staging/wave13-w1-dispatch-b01/004adb40_get_field44.hpp",
    "reconstruction/staging/wave13-w1-dispatch-b01/opaque_types.hpp",
    "reconstruction/staging/wave13-w1-dispatch-b01/wave13_b01_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-dispatch-b01/004adb40.json"
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
    "A runtime pass would need to sample the field at a known call site, for example around 0x00586f10, to see the value the original actually compares against.",
    "Is +0x40 / +0x44 / +0x48 a vector, a bound or a centre? Three consecutive floats exist and are read together at 0x0049ad1e-0x0049ad3c, which is suggestive but does not fix the axes or the order.",
    "Is the PUSH ECX / spill / reload sequence in all ten family members an artefact of a debug build, a /Zi-style build, or a compiler that emits frames for trivially small functions? Nothing in the observed evidence distinguishes these, and it does not affect semantics.",
    "No original-process trace exists, so the claim that the field holds a live float in the shipping build is static only.",
    "Seven of the eleven reported call sites were not disassembled window-by-window in this batch; their receiver provenances come from the briefing's call graph.",
    "The original Cell stage has never been entered in any recorded run, so no stage-level reachability claim is made.",
    "What class owns this sub-object? Its proven parent contexts are cEditor+0x98 and rigblock+0x28, and no vtable was located for it.",
    "What does the float at +0x44 mean? The only site that gives it a role compares it against a computed float, which is consistent with a distance, a scale or a threshold. None of those is asserted.",
    "Why do +0x48 and +0x4e have setters but no getters in this family? Either they are read by inlined code elsewhere or the getters were never emitted out of
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-w1-dispatch-b01/004adb40.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b01/004adb40_get_field44.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b01/004adb40_get_field44.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b01/opaque_types.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b01/wave13_b01_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave13-w1-dispatch-b01/004adb40.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b01/004adb40_get_field44.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b01/004adb40_get_field44.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b01/opaque_types.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruc
[TRUNCATED]
```
