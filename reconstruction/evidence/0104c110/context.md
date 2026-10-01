# Reconstruction context 0x0104c110

- Status: `partial`
- Content SHA-256: `6d5ce0f35c8d82f0f6aac909989325f9f74375e0ebc416d8e993216da28b6a71`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x0104c110",
  "phase": "reconstruction",
  "target": "0x0104c110"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_0104c110",
  "package": "pkg-swarm-w1-0104c110",
  "subsystem": "Sporepedia",
  "va": "0x0104c110"
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
  "content_sha256": "78feaadbbf890738fd85d60b67ebbd6eaac5ea3fd18277701dcb5b0ff10f57bd",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x0104c110 failed: Decompilation did not complete. Reason: ",
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
  "receiver": true,
  "receiver_register": "ECX",
  "ret_form": "RET",
  "return_register": "EAX",
  "return_type": "FieldWord",
  "return_width_bytes": 4,
  "saved_registers": [],
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
      "va": "0x00ff3df0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00ff3e26",
      "direction": "in",
      "other": "0x00ff3df0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00ff3e3c",
      "direction": "in",
      "other": "0x00ff3df0",
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
    "FieldWord",
    "FieldWord, an opaque 4-byte alias (std::uint32_t as the width carrier)"
  ],
  "vtables": [
    "vtable:0x01490be8"
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
      "va": "0x00ff3df0"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00ff3e26",
      "direction": "in",
      "other": "0x00ff3df0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00ff3e3c",
      "direction": "in",
      "other": "0x00ff3df0",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 1,
  "fan_out": 0,
  "manifest_callees": [],
  "manifest_callers": [],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0600",
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
      "shared_vtable:vtable:0x01490be8",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w2-00f999e0",
    "score": 12,
    "symbol": "re_00f999e0",
    "va": "0x00f999e0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01490be8",
      "same_calling_convention"
    ],
    "package": "pkg-fa0d50-atomic-inc",
    "score": 12,
    "symbol": "FUN_00fa0d50",
    "va": "0x00fa0d50"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01490be8",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-00fa5580",
    "score": 12,
    "symbol": "re_00fa5580",
    "va": "0x00fa5580"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01490be8",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-00fa6ec0",
    "score": 12,
    "symbol": "re_00fa6ec0",
    "va": "0x00fa6ec0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01490be8",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-00fa73c0",
    "score": 12,
    "symbol": "sw1_snap_and_dispatch_00fa73c0",
    "va": "0x00fa73c0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-005c0dd0",
    "score": 8,
    "symbol": "re_005c0dd0",
    "va": "0x005c0dd0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-006413d0",
    "score": 8,
    "symbol": "re_
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-swarm-w1-0104c110/sw1_0104c110.cpp",
    "reconstruction/staging/pkg-swarm-w1-0104c110/sw1_0104c110_model_test.cpp",
    "reconstruction/staging/pkg-swarm-w1-0104c110/sw1_0104c110_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-swarm-w1-0104c110/0104c110.json"
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
    "How large is the receiver really? Only that it is at least 0x214 bytes is established. The one caller touches +0x60, +0x64 and +0x7c, all inside that, so the true extent is larger and is not modelled.",
    "Is +0x210 a field of its own or part of a larger sub-object (a refcount, a size, a capacity, an index, a version)? A two-instruction accessor cannot see this. Other bodies in the same class would have to establish it, and none was re-read for this package.",
    "Is 0x00ff3df0 the only direct caller? The xref export records exactly one, but it is a projection and this package did not re-derive the whole image's call sites independently. A vtable slot is also reachable indirectly, so the set of call sites reaching this body through the table at 0x01490be8 is not enumerated here.",
    "What is the ELEMENT TYPE of the returned 32 bits? The machine fixes the width (4 bytes) and nothing else: abi_derived.return.type is null and its register_class is the inference string 'pointer_like' at INFERRED confidence, while the one direct caller tests the result with a signed JLE and stores it into a 4-byte member. A signed integer, an unsigned handle and a pointer all survive every fact in the evidence set. Settling it needs either a second direct caller that uses the value as an address, or a record of what the caller at 0x00ff3df0 was doing with the object it got from the 0x00ff3e13 virtual call.",
    "What is the class? The triage record carries sdk_name = null, the Sporepedia cluster label is a classifier output rather than 
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-swarm-w1-0104c110/0104c110.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w1-0104c110/sw1_0104c110.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w1-0104c110/sw1_0104c110_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w1-0104c110/sw1_0104c110_types.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-swarm-w1-0104c110/0104c110.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w1-0104c110/sw1_0104c110.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w1-0104c110/sw1_0104c110_model_test.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w1-0104c110/sw1_0104c110_types.hpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.js
[TRUNCATED]
```
