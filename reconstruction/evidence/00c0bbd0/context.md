# Reconstruction context 0x00c0bbd0

- Status: `partial`
- Content SHA-256: `8d61423e65ffbb55011bc2fd27050fb981f602e8e09190102be244843ef7ad9a`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00c0bbd0",
  "phase": "reconstruction",
  "target": "0x00c0bbd0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00c0bbd0",
  "package": null,
  "subsystem": "Simulator",
  "va": "0x00c0bbd0"
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
  "content_sha256": "d40fe2141273afe694f5e30017e5929e4194df30cdc90c145aa74590c82544d5",
  "live_attempts": [],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `present`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json

undefined4 __fastcall FUN_00c0bbd0(int param_1)

{
  return *(undefined4 *)(param_1 + 0xb20);
}


```

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_this": true,
  "receiver_register": "ECX",
  "return_register": "EAX",
  "stack_arguments": 0,
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller"
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
      "va": "0x00aca360"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b49a50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c02eb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c07480"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c08350"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4c690"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4c790"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4fc00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4fe60"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d38150"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d3cdc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d4b2f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d54330"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d58c50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d5bfa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d5ccf0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00aca469",
      "direction": "in",
      "other": "0x00aca360",
      "reference_type": "direct-call"
    },

[TRUNCATED]
```

## 08_types_fields_globals

- State: `missing`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [],
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
  "callees": [],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aca360"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b49a50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c02eb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c07480"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c08350"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4c690"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4c790"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4fc00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4fe60"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d38150"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d3cdc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d4b2f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d54330"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d58c50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d5bfa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d5ccf0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d679e0"
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
    "symbol": "FUN_00b3d2a0",
    "va": "0x00b3d2a0"
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
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-13-E4-EMPIRE-WAVE3",
    "score": 6,
    "symbol": "EmpirePoliticalColor_00c32cd0",
    "va": "0x00c32cd0"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [],
  "handoffs": [],
  "metadata": []
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
    "Is the receiver's true size recoverable? The same callers index it to at least +0x1350, but no evidence in this pack states an extent, so the model stops at the reached word.",
    "Is the true calling convention __thiscall or __fastcall? The ABI record lists both as candidates and the observed facts (receiver in ECX, 0 stack words, bare RET, caller cleanup) are consistent with either; no caller pushes an argument and no callee pops one, so nothing here separates them.",
    "No runtime/traced evidence exists in this repository for this target, so nothing is differentially validated against the original process.",
    "The 41 xrefs / 30 callers were sampled, not enumerated: 0x00c4fc00, 0x00aca360, 0x00c02eb0, 0x00c08350 only. A caller that dereferences the result would change the return-type argument, though not the load itself.",
    "What does the word at receiver+0xb20 mean — an id, a handle, an index or a pointer? The listing gives width and displacement only; the bounds_only receiver record cannot name the member. A hint exists but is not proof: the sibling 0x00c0bc00 loads the same word, tests it for null and then ADDs 0x504 to it (falling back to LEA EAX,[ECX+0xb28] when it is null), which is consistent with a pointer or table base. That sibling is owned by another worker and its interpretation is not claimed here."
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'derived'}, {'mode': 'derived', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'derived'}, {'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /decompile_function @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}`

```json
{
  "provenance": [
    {
      "mode": "derived",
      "ref": "GhidraMCP /disassemble_function",
      "source_class": "derived"
    },
    {
      "mode": "derived",
      "ref": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
      "source_class": "derived"
    },
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
      "ref": "GhidraMCP REST /decompile_function @ http://127.0.0.1:8089",
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
    "RETURN SEMANTICS",
    "EVIDENCE COVERAGE"
  ]
}
```
