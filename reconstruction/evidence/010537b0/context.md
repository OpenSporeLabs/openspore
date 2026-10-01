# Reconstruction context 0x010537b0

- Status: `partial`
- Content SHA-256: `852fbaf211762b4806e4e6b5827c888cee3e2b4b9ad5902bfad9009fb73fb700`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x010537b0",
  "phase": "reconstruction",
  "target": "0x010537b0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_010537b0",
  "package": null,
  "subsystem": "Simulator",
  "va": "0x010537b0"
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
  "status": "candidate"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "7f9be69214207112f8b9e95062e08df6c7b01618ade96d04a358d7eb7ea874d6",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x010537b0 failed: Decompilation did not complete. Reason: ",
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
  "ordinary_stack_arguments": [
    {
      "entry_offset": "entry_ESP+0x4",
      "evidence": "0x010537b0 `TEST byte ptr [ESP + 0x4],0x1` is the body's first instruction, executed before the prologue push, so ESP is still at its entry value; the operand width is BYTE, so only the low eight bits of the slot participate. abi_derived.ordinary_stack_arguments[0] agrees: entry_offset entry_ESP+0x4, sizes [1], observed true, read false, written false.",
      "ordinal": 1,
      "width": "1 byte, TESTed, not loaded"
    }
  ],
  "receiver_register": "ECX",
  "ret_form": "RET 0x4",
  "return_register": "EAX",
  "saved_registers": [
    "ESI"
  ],
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "callee"
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [],
  "callers": [],
  "edge_rows": [
    {
      "callsite": "0x010537c8",
      "direction": "out",
      "other": "0x00f47380",
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
    "TableWordPair",
    "TableWordPair* -- a four-byte pointer to the receiver"
  ],
  "vtables": [
    "vtable:0x013f6d6c",
    "vtable:0x013f7b54",
    "vtable:0x013f925c",
    "vtable:0x0140e360",
    "vtable:0x0145ab74",
    "vtable:0x0145ae10",
    "vtable:0x0145aeb4",
    "vtable:0x0145af64",
    "vtable:0x0145afdc",
    "vtable:0x0147dba8",
    "vtable:0x0148a7c8",
    "vtable:0x0148b040"
  ]
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
      "A trace captures the pointer 0x00f47380 receives and the pointer the body returns in EAX, so the two are shown to be the same address.",
      "A trace captures the two words before and after 0x010537b8 and 0x010537bf, confirming the immediates 0x013eb938 and 0x013ec458 and the order the two stores happen in.",
      "A trace enters through the adjustor 0x01053780, so the -4 bias is observed arriving already applied.",
      "A trace records the value in the entry stack word at 0x010537b0 and the ZF it produces, and which arm 0x010537c5 takes.",
      "The original process is driven to an object whose +0x00 and +0x04 words hold a most-derived table pair, once with the deleting-destructor flag clear and once with it set."
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
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x010537c8",
      "direction": "out",
      "other": "0x00f47380",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 0,
  "fan_out": 0,
  "manifest_callees": [],
  "manifest_callers": [],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0603",
    "size": 1
  },
  "vtable_reference_count": 2
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
      "shared_vtable:vtable:0x0149b810,vtable:0x0149b8b4"
    ],
    "package": "pkg-sim-toolevent-01053d50",
    "score": 10,
    "symbol": "sim_toolevent_slot8_fun_01053d50",
    "va": "0x01053d50"
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
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-swarm-w1-010537b0/sw1_010537b0.cpp",
    "reconstruction/staging/pkg-swarm-w1-010537b0/sw1_010537b0_model_test.cpp",
    "reconstruction/staging/pkg-swarm-w1-010537b0/sw1_010537b0_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-swarm-w1-010537b0/010537b0.json"
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
    "A trace captures the pointer 0x00f47380 receives and the pointer the body returns in EAX, so the two are shown to be the same address.",
    "A trace captures the two words before and after 0x010537b8 and 0x010537bf, confirming the immediates 0x013eb938 and 0x013ec458 and the order the two stores happen in.",
    "A trace enters through the adjustor 0x01053780, so the -4 bias is observed arriving already applied.",
    "A trace records the value in the entry stack word at 0x010537b0 and the ZF it produces, and which arm 0x010537c5 takes.",
    "Ghidra's decompilation of the ADJACENT creator at 0x01053740 shows `ret 0x8`, i.e. it believes it takes two stack arguments, while the creator's own bytes push six words and its caller-side cleanup is `ADD ESP,0x18` at 0x01053754. That is another function's decompilation error and it is recorded only because it was read while establishing the class name above; nothing in this reconstruction depends on it.",
    "Is the receiver's size 0x08? The body writes displacements 0x00 and 0x04 and the adjustor proves a sub-object at +0x04, so 0x08 is the smallest size consistent with this evidence and is what the model declares. The size of the BASE sub-object beyond the eight bytes the body touches is not established: 0x01053740 shows a MORE DERIVED object of 0x0c bytes, which says nothing about the base's own extent. No total size is claimed beyond the two words this body rewrites.",
    "The original process is driven to an object whose +0x00 and +0x04 words hold a most-derived table pai
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-swarm-w1-010537b0/010537b0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w1-010537b0/sw1_010537b0.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w1-010537b0/sw1_010537b0_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w1-010537b0/sw1_010537b0_types.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-swarm-w1-010537b0/010537b0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w1-010537b0/sw1_010537b0.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w1-010537b0/sw1_010537b0_model_test.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w1-010537b0/sw1_010537b0_types.hpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.js
[TRUNCATED]
```
