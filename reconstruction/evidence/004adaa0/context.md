# Reconstruction context 0x004adaa0

- Status: `partial`
- Content SHA-256: `e65fd3603333cd290e03926f5295dfb4f6f71ad9f6cca826cc4a28bfd90a2844`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x004adaa0",
  "phase": "reconstruction",
  "target": "0x004adaa0"
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
  "va": "0x004adaa0"
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
  "content_sha256": "8e50c7ef8e42f11aa54b0ceb88d49da96515cd333c0a009a72792eb7732f51c2",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x004adaa0 failed: Decompilation did not complete. Reason: ",
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
  "hidden_receiver": "ECX, spilled to [EBP-0x4] at 0x004adaa4 and reloaded at 0x004adaa7",
  "ordinary_stack_argument_slots": 0,
  "receiver": true,
  "ret_form": "RET",
  "return_observation": "0x004adaaa: D9 40 38 (FLD float ptr [EAX + 0x38]) is the only value-producing instruction; the frame teardown at 0x004adaad..0x004adab0 (MOV ESP,EBP; POP EBP; RET) touches no FP register, so ST0 survives to the caller.",
  "return_register": "x87 ST0",
  "return_semantics": "the single-precision value stored at receiver + 0x38, unmodified",
  "return_type": "float",
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
      "va": "0x0043e3f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0043fc20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00448380"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00449ed0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00485110"
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
      "va": "0x0048e590"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0049a2a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0049b8b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004a06c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004a0bf0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004a3dc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004a4d60"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0057d710"
    },
    {
      "name": "editor_input_0058ac10",
      "reconstructed": true,
      "va": "0x0058ac10"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x0043e43a",
      "direction": "in",
      "other": "0x0043e3f0",
      "reference_type": "di
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "float",
    "float (single precision)"
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
      "A runtime differential test would be needed to confirm the receiver type and to confirm that no runtime patch retargets this address.",
      "No original-process trace exists for 0x004adaa0. The Cell stage has never been entered in any recorded run, so the claim that callers treat the result numerically is a static claim only.",
      "The meaning of the +0x38 field can only be settled by observing a write at runtime, which no recorded run does."
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
      "va": "0x0043e3f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0043fc20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00448380"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00449ed0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00485110"
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
      "va": "0x0048e590"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0049a2a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0049b8b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004a06c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004a0bf0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004a3dc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004a4d60"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0057d710"
    },
    {
      "name": "editor_input_0058ac10",
      "reconstructed": true,
      "va": "0x0058ac10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005b1870"
    },
    {
      "name": nu
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
    "reconstruction/staging/wave13-w1-dispatch-b00/field38_004adaa0.cpp",
    "reconstruction/staging/wave13-w1-dispatch-b00/field38_004adaa0.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-dispatch-b00/004adaa0.json"
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
    "A runtime differential test would be needed to confirm the receiver type and to confirm that no runtime patch retargets this address.",
    "Is 0x004adaa0 also a vtable entry? A pointer scan of the target's address was not performed, so only direct-call sites are recorded.",
    "No original-process trace exists for 0x004adaa0. The Cell stage has never been entered in any recorded run, so the claim that callers treat the result numerically is a static claim only.",
    "The 26 caller fan-in is dominated by four functions in the 0x0043xxxx-0x004axxxx range with no subsystem attribution. Their relationship to the owning type is not established.",
    "The meaning of the +0x38 field can only be settled by observing a write at runtime, which no recorded run does.",
    "What are the float constants at 0x013eb960 (0x3c23d70a) and 0x013eecd8 (0x41a00000 = 20.0f)? 20.0f is self-evident; the other is not, and neither is named in the SDK.",
    "What class owns the +0x38 float? No vtable was located for the receiver type and the binary has no RTTI, so the owner is unnamed.",
    "What does the float mean (scale, radius, alpha, weight, time)? Every inspected consumer only multiplies or divides it by a constant, which is compatible with all of those.",
    "Why is there no getter for +0x3c or +0x40 when both have setters? Either the getters were inlined at every use or they do not exist; the binary cannot distinguish these."
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-w1-dispatch-b00/004adaa0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b00/field38_004adaa0.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b00/field38_004adaa0.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave13-w1-dispatch-b00/004adaa0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b00/field38_004adaa0.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b00/field38_004adaa0.hpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.json"
  ],
  "required_categories": [
    "ABI",
    "CALLS",
    "GLOBALS",
    "FIELDS/OFFSETS",
    "CONSTANTS",
    "CONTROL FLOW",
    "VIRTUAL DISPATCH",
    "RETU
[TRUNCATED]
```
