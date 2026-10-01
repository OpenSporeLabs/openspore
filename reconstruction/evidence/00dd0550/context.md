# Reconstruction context 0x00dd0550

- Status: `partial`
- Content SHA-256: `d455a43ba21a41d4eba2bcce064da60ff91948e1f2c5d7695dc5fd040307c450`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00dd0550",
  "phase": "reconstruction",
  "target": "0x00dd0550"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00dd0550",
  "package": "pkg-swarm-w1-00dd0550",
  "subsystem": "Sporepedia",
  "va": "0x00dd0550"
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
  "content_sha256": "da5e43ff75385b9e013559e771306ccadbb9c28fb36d046520cc00696d037658",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00dd0550 failed: Decompilation did not complete. Reason: ",
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
  "hidden_this_type": "SporepediaOnlineReceiver",
  "ordinary_stack_argument_slots": 0,
  "receiver_register": "ECX",
  "ret_form": "RET",
  "return_note": "The published claim is the type the source span declares, and the two are now the same string. What the machine fixes is the TRANSFER REGISTER, its WIDTH and its CLASS, and nothing finer: abi_derived.value.abi names EAX as the return register and states return_semantics 'integral_in_EAX' (kept verbatim in the sibling field machine_return_semantics, because that is a register-class label and not a C or C++ type), abi_derived.return adds register_class 'integral' with void_possible false, and its own return.type is null, so no record supplies a C type for this VA at all. The width is fixed by...",
  "return_register": "EAX",
  "return_type": "Word",
  "saved_registers": [
    "ESI"
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
    }
  ],
  "callers": [],
  "edge_rows": [
    {
      "callsite": "0x00dd0553",
      "direction": "out",
      "other": "0x00b3d2a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00dd0569",
      "direction": "out",
      "other": "0x00ba6dc0",
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
  "globals": [
    "global:0x0167eae4"
  ],
  "types": [
    "OpaqueStarTable",
    "SporepediaOnlineReceiver",
    "Word",
    "lookup_00ba6dc0",
    "re_00dd0550",
    "root_slot_00b3d2a0"
  ],
  "vtables": [
    "vtable:0x0147ca30",
    "vtable:0x0147ca70",
    "vtable:0x0147caf8",
    "vtable:0x0147cc14"
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
  "callees": [
    {
      "name": "FUN_00b3d2a0",
      "reconstructed": true,
      "va": "0x00b3d2a0"
    }
  ],
  "callees_truncated": false,
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00dd0553",
      "direction": "out",
      "other": "0x00b3d2a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00dd0569",
      "direction": "out",
      "other": "0x00ba6dc0",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 0,
  "fan_out": 1,
  "manifest_callees": [],
  "manifest_callers": [],
  "nearby_reconstructed": [
    "0x00b3d2a0"
  ],
  "scc": {
    "id": "scc-0506",
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
      "shared_types:Word",
      "shared_vtable:vtable:0x0147ca30,vtable:0x0147caf8",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-006413d0",
    "score": 15,
    "symbol": "re_006413d0",
    "va": "0x006413d0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_types:Word",
      "shared_vtable:vtable:0x0147ca30,vtable:0x0147ca70",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w2-00642700",
    "score": 15,
    "symbol": "sporepedia_append_five_lookups_00642700",
    "va": "0x00642700"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_types:Word",
      "shared_vtable:vtable:0x0147ca30,vtable:0x0147ca70",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-00a649a0",
    "score": 15,
    "symbol": "re_00a649a0",
    "va": "0x00a649a0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x0147ca30,vtable:0x0147cc14",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-005c0dd0",
    "score": 12,
    "symbol": "re_005c0dd0",
    "va": "0x005c0dd0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x0147ca30,vtable:0x0147caf8",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-00641410",
    "score": 12,
    "symbol": "re_00641410",
    "va": "0x00641410"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x0147ca30,vtable:0x0147ca70",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-006417d0
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-swarm-w1-00dd0550/swarmw1_00dd0550.cpp",
    "reconstruction/staging/pkg-swarm-w1-00dd0550/swarmw1_00dd0550_model_test.cpp",
    "reconstruction/staging/pkg-swarm-w1-00dd0550/swarmw1_00dd0550_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-swarm-w1-00dd0550/00dd0550.json"
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
    "Is the -1 sentinel at 0x00ba6dc5 reachable from this body? It is not, because this body's own guard diverts a null key and 0xffffffff is not null -- so a -1 key DOES reach 0x00ba6dc0 and gets its 0 back. Whether 0xffffffff is a meaningful value at +0x80 is unresolved.",
    "RETURN SEMANTICS: the canonical claim is the string 'Word' and the source span declares 'Word', so the arm agrees -- but the agreement is between a SOURCE-SIDE SPELLING and a MACHINE-FIXED WIDTH, not between two machine observations. abi_derived.value.abi.return_semantics is the register-class phrase `integral_in_EAX` and abi_derived.return.type is null, so no record for this VA supplies a C type, and a width-based oracle could not adjudicate this body in any case: the last value-producing instruction before both terminators is 0x00dd0569 CALL 0x00ba6dc0, and a CALL inside the body defeats evidence_returns' WIDTH state by design, because whether a caller may read EAX after a call is the CALLEE's signature and this listing cannot show it. So the residual question is exactly the one the record leaves open: which of the integral types of that four-byte word the original was written as. `Word` is one honest spelling and not a recovery -- a 32-bit pointer, a handle and a count are all 4 bytes and all `integral` in EAX, and the callee's own return is INFERRED (see return_semantics.value_meaning) to be a planet-record-shaped pointer without this body establishing that. Nothing here distinguishes them, and the declaration does not claim to.",
    "The ghidra
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-swarm-w1-00dd0550/00dd0550.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w1-00dd0550/swarmw1_00dd0550.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w1-00dd0550/swarmw1_00dd0550_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w1-00dd0550/swarmw1_00dd0550_types.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-swarm-w1-00dd0550/00dd0550.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w1-00dd0550/swarmw1_00dd0550.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w1-00dd0550/swarmw1_00dd0550_model_test.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w1-00dd0550/swarmw1_00dd0550_types.hpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowle
[TRUNCATED]
```
