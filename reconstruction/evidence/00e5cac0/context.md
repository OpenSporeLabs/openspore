# Reconstruction context 0x00e5cac0

- Status: `partial`
- Content SHA-256: `77950f605ec4f72ad5f1c11f405dd627ebed6df59a64714c2e4a8d67f42c596f`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00e5cac0",
  "phase": "reconstruction",
  "target": "0x00e5cac0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00e5cac0",
  "package": "pkg-w2-00e5cac0",
  "subsystem": "Editor",
  "va": "0x00e5cac0"
}
```

## 03_current_status

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "blocked": false,
  "reconstructed": true,
  "runtime_gated": false,
  "runtime_validated": 0,
  "status": "reconstructed"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "3121f03d4614eeb125cd7fe348584b2a8b246e88b3e7ac9406addd744b61f65d",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00e5cac0 failed: Decompilation did not complete. Reason: ",
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
  "hidden_this": true,
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": 1,
  "receiver": "ECX carries the receiver, and the body forwards it into EAX. What the machine record states, at INFERRED confidence: receiver {present true, register ECX, provenance vftable_slot_dispatch, bounds_only true, shape null, distinct_offsets 0, offsets [], written_through 0}. What the two instructions show: MOV EAX,ECX at 0x00e5cac0 copies all 32 bits of the incoming ECX into EAX, verbatim and unnarrowed, and the record returned by 0x007fbd90 is the very value that entered the CALL. ECX is NEVER DEREFERENCED in this body: the two instructions contain no load and no store through it in any registe...",
  "receiver_register": "ECX",
  "ret_form": "RET 0x4",
  "return_observation": "The record classifies the last write to EAX as aggregate_unknown (RT2) and the envelope as unclassified_in_EAX. The listing says more than that and this package reads only the listing: the single write to EAX is MOV EAX,ECX at 0x00e5cac0, a register-to-register move of the value ECX carried on entry, so the returned value is the incoming receiver verbatim and 32 bits wide, and the body never dereferences what it returns. The C spelling is Receiver *, chosen for the reason given in the sibling package at 0x00642210; the machine fixes the width, not the spelling.",
  "return_register": "EAX",
  "return_semantics": "unclassified_in_EAX",
  "return_width_bytes": 4,
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "callee",
  "term
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
      "va": "0x007fbd50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007fbf40"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x007fbd61",
      "direction": "in",
      "other": "0x007fbd50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x007fbd90",
      "direction": "in",
      "other": "0x007fbd50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x007fbfc8",
      "direction": "in",
      "other": "0x007fbf40",
      "reference_type": "direct-call"
    }
  ],
  "external_callees": []
}
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "openspore::reconstruction::pkg_w2_00e5cac0::Receiver",
    "openspore::reconstruction::pkg_w2_00e5cac0::Word"
  ],
  "vtables": [
    "vtable:0x013f57f8",
    "vtable:0x0140116c",
    "vtable:0x01485550"
  ]
}
```

## 09_state_event_relationships

- State: `missing`
- Provenance: `knowledgegraph/research/semantic-decomp.json, reconstruction/knowledge/index.json`

```json
{
  "runtime": {
    "blocking_reason": null,
    "gates": [],
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
      "va": "0x007fbd50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007fbf40"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x007fbd61",
      "direction": "in",
      "other": "0x007fbd50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x007fbd90",
      "direction": "in",
      "other": "0x007fbd50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x007fbfc8",
      "direction": "in",
      "other": "0x007fbf40",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 2,
  "fan_out": 0,
  "manifest_callees": [],
  "manifest_callers": [],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0530",
    "size": 1
  },
  "vtable_reference_count": 0
}
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013f57f8",
      "same_calling_convention"
    ],
    "package": "pkg-editor-w1-0057d6f0",
    "score": 12,
    "symbol": "re_0057d6f0",
    "va": "0x0057d6f0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013f57f8",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w2-00586700",
    "score": 12,
    "symbol": "re_00586700",
    "va": "0x00586700"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013f57f8",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-005b2490",
    "score": 12,
    "symbol": "re_005b2490",
    "va": "0x005b2490"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013f57f8",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-005ba0d0",
    "score": 12,
    "symbol": "re_005ba0d0",
    "va": "0x005ba0d0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013f57f8,vtable:0x0140116c",
      "same_calling_convention"
    ],
    "package": "pkg-shared-default-true-wave12",
    "score": 12,
    "symbol": "pkg_shared_default_true_00b1fbf0",
    "va": "0x00b1fbf0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013f57f8"
    ],
    "package": "pkg-editor-child-007f30d0",
    "score": 10,
    "symbol": "FUN_007f30d0",
    "va": "0x007f30d0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "pkg-vft-preinc-
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-w2-00e5cac0/ret_eax_from_ecx_00e5cac0.cpp",
    "reconstruction/staging/pkg-w2-00e5cac0/ret_eax_from_ecx_00e5cac0.hpp",
    "reconstruction/staging/pkg-w2-00e5cac0/ret_eax_from_ecx_00e5cac0_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-w2-00e5cac0/00e5cac0.json"
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
    "Is the receiver the head of its object or an interior sub-object? The two unadjusted call sites and the one +0xc-adjusted site reach the same body at different displacements, and the body neither adds nor subtracts anything of its own, so the base relationships between them are not recoverable from here.",
    "What does the popped 4-byte stack slot mean? It is established that the callee pops it and never reads it; whether it is a parameter at all, and if so of what type and meaning, is not established by this listing and is not guessed.",
    "What is the register_class of the returned value? The record classifies it aggregate_unknown (RT2) and the envelope as unclassified_in_EAX. The listing shows the value is the incoming receiver verbatim, so it is a pointer-shaped 4 bytes, but the machine's own classification is recorded as it stands and is not upgraded here.",
    "Which class, if any, does this address belong to? R1-VFT establishes that it is a virtual member of SOME class, because it is a slot of a vptr-backed table, and that is as far as the evidence goes. This binary carries no MSVC RTTI, the record names no owning class, and identical folding means one address can be a virtual member of several classes at once, so no class identity is claimed.",
    "Why does one address live in three vtables? ICF-folded shared stubs and vtable merging both produce that, and nothing in the five bytes distinguishes them."
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-w2-00e5cac0/00e5cac0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-w2-00e5cac0/ret_eax_from_ecx_00e5cac0.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-w2-00e5cac0/ret_eax_from_ecx_00e5cac0.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-w2-00e5cac0/ret_eax_from_ecx_00e5cac0_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-w2-00e5cac0/00e5cac0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-w2-00e5cac0/ret_eax_from_ecx_00e5cac0.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-w2-00e5cac0/ret_eax_from_ecx_00e5cac0.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-w2-00e5cac0/ret_eax_from_ecx_00e5cac0_model_test.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge
[TRUNCATED]
```
