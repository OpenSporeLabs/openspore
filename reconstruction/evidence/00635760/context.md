# Reconstruction context 0x00635760

- Status: `partial`
- Content SHA-256: `cafff0eb6c85d1b71520314f82a434ed870f1a3e2a01efd58a2ad0cf0fb16e02`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00635760",
  "phase": "reconstruction",
  "target": "0x00635760"
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
  "va": "0x00635760"
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
  "content_sha256": "f3a323343a28a3cbcf4ddf99e3a344101a4874f62e783222be244d6873883c0f",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00635760 failed: Decompilation did not complete. Reason: ",
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
  "hidden_receiver": "ECX, forwarded unchanged to 0x00634dc0; overwritten at 0x0063577b with the resolved window before the tail transfer",
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": 2,
  "receiver": true,
  "ret_form": "RET 0x8",
  "return_observation": "EAX is a lookup result on entry to the dispatch path and is overwritten with the window pointer at 0x0063577b; on the null path EAX is 0 at 0x0063576a. No consumer reads EAX after any of the recorded call sites, so no return value is observable.",
  "return_register": null,
  "return_semantics": "void",
  "return_type": "void",
  "return_width_bytes": 0,
  "saved_registers": [],
  "stack_arguments": [
    {
      "entry_offset": "ESP+4",
      "name": "control_id",
      "role": "UTFWin control id, forwarded to the lookup and then replaced by the constant 1 before the tail transfer",
      "type": "std::uint32_t",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+8",
      "name": "visible",
      "role": "value written into kWinFlagVisible; forwarded verbatim as the second argument of the +0x7C dispatch",
      "type": "bool",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 8,
  "stack_cleanup_owner": "callee",
  "termination": "0x0063577f RET 8 on the null path; 0x0063577d JMP EDX (tail transfer) on the success path"
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
      "va": "0x0062ba10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0062bf10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0062c340"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0062c990"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0062e7a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0062e7e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0062ebe0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0062ec30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0062f340"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0062f480"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0062fc90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0062fda0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0062fe40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006301a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00630280"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00632ba0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x0062baef",
      "direction": "in",
      "other": "0x0062ba10",
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
    "bool",
    "std::uint32_t",
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
      "A runtime differential test would have to (a) confirm the lookup returns the same window for a given control id, (b) confirm the +0x7C dispatch reaches an IWindow::SetFlag implementation and not a patched one, and (c) confirm the callee really uses RET 8, which the tail transfer requires but which no in-binary observation of the concrete callee can prove.",
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
      "va": "0x0062ba10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0062bf10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0062c340"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0062c990"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0062e7a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0062e7e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0062ebe0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0062ec30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0062f340"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0062f480"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0062fc90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0062fda0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0062fe40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006301a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00630280"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00632ba0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00632c00"
    },
    {
      "name": null,
      "reconst
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
    "reconstruction/staging/wave13-pilot-dispatch-b00/utfwin_00635760.cpp",
    "reconstruction/staging/wave13-pilot-dispatch-b00/utfwin_00635760.hpp",
    "reconstruction/staging/wave13-pilot-dispatch-b00/utfwin_00635760_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-pilot-dispatch-b00/00635760.json"
  ]
}
```

## 13_semantic_hypotheses

- State: `missing`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

## 14_conflicts_questions

- State: `conflicted`
- Provenance: `reconstruction/knowledge/index.json, knowledgegraph/research/semantic-decomp.json`

```json
{
  "conflicts": [
    {
      "derived": "__stdcall",
      "field": "calling_convention",
      "kind": "derived_vs_persisted",
      "persisted": "__thiscall",
      "resolution_status": "unresolved"
    }
  ],
  "unresolved_questions": [
    "A runtime differential test would have to (a) confirm the lookup returns the same window for a given control id, (b) confirm the +0x7C dispatch reaches an IWindow::SetFlag implementation and not a patched one, and (c) confirm the callee really uses RET 8, which the tail transfer requires but which no in-binary observation of the concrete callee can prove.",
    "Is the vector at +0x14 a list of UTFWin service providers, a list of root windows, or a type registry? The observed protocol (query by type id, then treat the result as a window) fits all three.",
    "No original-process trace has ever been captured for this function; the original Cell stage has never been entered in any recorded run. Every claim here is static.",
    "Spore-ModAPI declares Editors::PlayModeUI::SetWindowVisible at 0x635450/0x635750, numerically adjacent to this target. Whether this target is that method could not be confirmed: 0x00635750 is not a function boundary in this image and 0x00634dc0 does not match PlayModeUI::FindWindowByID's described shape. Recorded as a candidate, not a claim.",
    "The control ids pushed by callers are addresses of string literals in .rdata (0x00406678, 0x004066b8, 0x0044 6a98 and so on). Their character contents were not read, so no caller-level purpose is claimed for any individual window.",
    "What is the dynamic IWindo
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-pilot-dispatch-b00/00635760.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-pilot-dispatch-b00/utfwin_00635760.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-pilot-dispatch-b00/utfwin_00635760.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-pilot-dispatch-b00/utfwin_00635760_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave13-pilot-dispatch-b00/00635760.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-pilot-dispatch-b00/utfwin_00635760.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-pilot-dispatch-b00/utfwin_00635760.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-pilot-dispatch-b00/utfwin_00635760_model_test.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction
[TRUNCATED]
```
