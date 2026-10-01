# Reconstruction context 0x00c33580

- Status: `partial`
- Content SHA-256: `58d2d3f3c135b06f8d1ea4880eb90150d6b6a5c7e51293c5aca7f5bc0982e2f2`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00c33580",
  "phase": "reconstruction",
  "target": "0x00c33580"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00c33580",
  "package": null,
  "subsystem": "Simulator",
  "va": "0x00c33580"
}
```

## 03_current_status

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "blocked": false,
  "reconstructed": false,
  "runtime_gated": false,
  "runtime_validated": 0,
  "status": "candidate"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "28fc305fc27d0023a5b468d10ee75695b66a9199a111dfd2c6252b952acacf44",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00c33580 failed: Decompilation did not complete. Reason: ",
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
  "ordinary_stack_argument_slots": 0,
  "receiver_register": "ECX",
  "ret_form": "RET",
  "return_note": "DECLARED void, AND THE DISAGREEMENT WITH THE MACHINE RECORD IS RECORDED RATHER THAN PAPERED OVER. abi.return_semantics is the machine-vocabulary phrase unclassified_in_EAX and abi_derived.return reports register EAX, register_class aggregate_unknown, void_possible false -- so no C++ return type can agree with the canonical claim and the dimension is a WARN whatever is declared. Option (b) of the wave-1 guidance was taken because the bytes genuinely produce nothing: the single RET is reached with EAX holding, per exit, the lookup's null result, record word 2, the handle sentinel 0xffffffff, ...",
  "return_register": "EAX",
  "return_type": "void",
  "saved_registers": [
    "ESI",
    "EDI"
  ],
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
  "callees": [
    {
      "name": "FUN_00b3d2a0",
      "reconstructed": true,
      "va": "0x00b3d2a0"
    },
    {
      "name": "EmpirePoliticalColor_00c32cd0",
      "reconstructed": true,
      "va": "0x00c32cd0"
    },
    {
      "name": "map_int_whatever_find",
      "reconstructed": true,
      "va": "0x00e5c780"
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba7dc0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00ba7e23",
      "direction": "in",
      "other": "0x00ba7dc0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c33627",
      "direction": "out",
      "other": "0x004da330",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c3365c",
      "direction": "out",
      "other": "0x005c3d90",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c33596",
      "direction": "out",
      "other": "0x00b3d2a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c335d9",
      "direction": "out",
      "other": "0x00b3d2a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c33634",
      "direction": "out",
      "other": "0x00b6f380",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c3359d",
      "direction": "out",
      "other": "0x00ba6d80",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c335e0",
      "direction": "out",
      "other": "0x00ba6d80",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c335ac
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [
    "global:evidence ceiling, not a source defect (see unresolved_questions)."
  ],
  "types": [
    "void"
  ],
  "vtables": []
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
  "callees": [
    {
      "name": "FUN_00b3d2a0",
      "reconstructed": true,
      "va": "0x00b3d2a0"
    },
    {
      "name": "EmpirePoliticalColor_00c32cd0",
      "reconstructed": true,
      "va": "0x00c32cd0"
    },
    {
      "name": "map_int_whatever_find",
      "reconstructed": true,
      "va": "0x00e5c780"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba7dc0"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00ba7e23",
      "direction": "in",
      "other": "0x00ba7dc0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c33627",
      "direction": "out",
      "other": "0x004da330",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c3365c",
      "direction": "out",
      "other": "0x005c3d90",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c33596",
      "direction": "out",
      "other": "0x00b3d2a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c335d9",
      "direction": "out",
      "other": "0x00b3d2a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c33634",
      "direction": "out",
      "other": "0x00b6f380",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c3359d",
      "direction": "out",
      "other": "0x00ba6d80",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c335e0",
      "direction": "out",
      "other": "0x00ba6d
[TRUNCATED]
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "same_subsystem",
      "direct_xref_neighbor"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 9,
    "symbol": "FUN_00b3d2a0",
    "va": "0x00b3d2a0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "direct_xref_neighbor"
    ],
    "package": "PKG-13-E4-EMPIRE-WAVE3",
    "score": 9,
    "symbol": "EmpirePoliticalColor_00c32cd0",
    "va": "0x00c32cd0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "PKG-SIMULATOR-SAFE-WAVE11",
    "score": 8,
    "symbol": "cycle_key_006286a0",
    "va": "0x006286a0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "PKG-SIMULATOR-SAFE-WAVE11",
    "score": 8,
    "symbol": "release_child_0062c910",
    "va": "0x0062c910"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-11-H4-HELPER-WAVE3",
    "score": 6,
    "symbol": "address_window_offset_005c65e0",
    "va": "0x005c65e0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-SIMULATOR-SAFE-WAVE11",
    "score": 6,
    "symbol": "dispatch_key_00628450",
    "va": "0x00628450"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 6,
    "symbol": "FUN_00b3d300",
    "va": "0x00b3d300"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 6,
    "symbol": "Simulator_GetUIMissionLogManager",
    "va": "0x00b3d4f0"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-swarm-w2-00c33580/sw2_00c33580.cpp",
    "reconstruction/staging/pkg-swarm-w2-00c33580/sw2_00c33580_model_test.cpp",
    "reconstruction/staging/pkg-swarm-w2-00c33580/sw2_00c33580_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-swarm-w2-00c33580/00c33580.json"
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
    "RETURN SEMANTICS is a WARN by construction, and this is a choice rather than an oversight. abi.return_semantics is the machine phrase unclassified_in_EAX and abi_derived.return.void_possible is false, so no C++ return type can satisfy the canonical claim. The package declares void, because the listing produces nothing coherent in EAX on any of its eight exits and Ghidra's decompilation returns void throughout, and it records the disagreement here instead of declaring a typedef named after the phrase. If the integrator would rather see a non-void declaration, the only listing-true candidate is a 32-bit value, and no evidence in this repository picks which.",
    "The GLOBALS dimension cannot pass for this target and no source change can fix it: the body stores a .rdata address and the xref export carries no data-reference edge type to corroborate the mode. The store is kept because it is in the listing.",
    "The four-word block's element 0 and the release range interact in a way this listing cannot explain: the range is (element 2 - element 0) & 0xfffffffe, i.e. it starts at an element the body never wrote and ends two elements into a three-element initialisation. The guard reads as the standard 'more than one element' idiom for a two-byte element type, which does not match four-byte pointers. The reconstruction reproduces the arithmetic exactly and asserts nothing about what the range means.",
    "The identity of the .rdata words 0x1667bac and 0x1667bae is unknown. They are stored, in that order, into block elements 1
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-swarm-w2-00c33580/00c33580.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w2-00c33580/sw2_00c33580.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w2-00c33580/sw2_00c33580_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w2-00c33580/sw2_00c33580_types.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-swarm-w2-00c33580/00c33580.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w2-00c33580/sw2_00c33580.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w2-00c33580/sw2_00c33580_model_test.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w2-00c33580/sw2_00c33580_types.hpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.js
[TRUNCATED]
```
