# Reconstruction context 0x005a2ed0

- Status: `partial`
- Content SHA-256: `62e100b82f9eb3dd476bb5eec68b278932bbe80b1c5d91b849e250c179555e55`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x005a2ed0",
  "phase": "reconstruction",
  "target": "0x005a2ed0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_005a2ed0",
  "package": null,
  "subsystem": "Editor",
  "va": "0x005a2ed0"
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
  "content_sha256": "ae7b18925be93d0121c00719d869992e4ea0f0df21c10797b1b63cfb21afa8b9",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x005a2ed0 failed: Decompilation did not complete. Reason: ",
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
  "receiver_register": "ECX",
  "ret_form": "RET 0x4",
  "return_note": "HONEST DISCLOSURE, because this field is a worker claim and not a machine token. The machine ABI envelope for this VA records return_semantics \"unclassified_in_EAX\" with return {register EAX, register_class \"aggregate_unknown\", type null, void_possible false} -- machine-vocabulary phrases that name no C++ type. Independently of that envelope the complete listing fixes the value: MOV EAX,ESI at 0x005a2f19 is the last write to EAX before the body's sole RET at 0x005a2f1c, it is unconditional on both paths, and ESI has held the receiver since 0x005a2ed1, so the returned value is the receiver p...",
  "return_register": "EAX",
  "return_type": "SwarmW2005a2ed0Receiver*",
  "saved_registers": [
    "ESI"
  ],
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "callee",
  "termination": "RET 0x4"
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
      "name": "editor_camera_func54h_005a2320",
      "reconstructed": true,
      "va": "0x005a2320"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x005a2323",
      "direction": "in",
      "other": "0x005a2320",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005a2f11",
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
    "SwarmW2005a2ed0Receiver*"
  ],
  "vtables": [
    "vtable:0x013f69b4"
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
      "RUNTIME is GATED: the OpenSpore original has never been executed in this repository, so no runtime claim of any kind is made for 0x005a2ed0. A differential test would need a driver, and the single recorded caller (0x005a2320) is a two-instruction receiver-adjustor thunk that tail-jumps here rather than calling it."
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
      "name": "editor_camera_func54h_005a2320",
      "reconstructed": true,
      "va": "0x005a2320"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x005a2323",
      "direction": "in",
      "other": "0x005a2320",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005a2f11",
      "direction": "out",
      "other": "0x00f47380",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 1,
  "fan_out": 0,
  "manifest_callees": [],
  "manifest_callers": [],
  "nearby_reconstructed": [
    "0x005a2320"
  ],
  "scc": {
    "id": "scc-0103",
    "size": 1
  },
  "vtable_reference_count": 6
}
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "shared_vtable:vtable:0x013f69b4",
      "same_calling_convention",
      "direct_xref_neighbor"
    ],
    "package": "PKG-CAMERA-WAVE8",
    "score": 9,
    "symbol": "editor_camera_func54h_005a2320",
    "va": "0x005a2320"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "pkg-vft-preinc-0051e340",
    "score": 8,
    "symbol": "vft_preinc_0051e340",
    "va": "0x0051e340"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "subobject-forward-0051e380",
    "score": 8,
    "symbol": "subobject_forward_0051e380",
    "va": "0x0051e380"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w2-00586700",
    "score": 8,
    "symbol": "re_00586700",
    "va": "0x00586700"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-005b2490",
    "score": 8,
    "symbol": "re_005b2490",
    "va": "0x005b2490"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-005ba0d0",
    "score": 8,
    "symbol": "re_005ba0d0",
    "va": "0x005ba0d0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-00a85070",
    "score": 8,
    "symbol": "re_00a85070",
    "va": "0x00a85070"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-swarm-w2-005a2ed0/sw2_005a2ed0.cpp",
    "reconstruction/staging/pkg-swarm-w2-005a2ed0/sw2_005a2ed0_model_test.cpp",
    "reconstruction/staging/pkg-swarm-w2-005a2ed0/sw2_005a2ed0_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-swarm-w2-005a2ed0/005a2ed0.json"
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
    "RETURN SEMANTICS: the machine ABI envelope's own return token is the machine phrase `unclassified_in_EAX` with register_class `aggregate_unknown`, and no C++ type can equal it. The listing independently fixes the returned value as the receiver pointer (MOV EAX,ESI at 0x005a2f19, unconditional, the last write to EAX before the sole RET 0x4 at 0x005a2f1c, with ESI the entry ECX since 0x005a2ed1), and the sidecar publishes that as observed_original_abi.return_type. So the canonical record and the source agree, but that agreement is between a LISTING-DERIVED claim and a source declaration, not between two machine observations: the machine envelope classifies nothing here. The claim to review is the envelope's, and this package did not override it -- it published its own reading beside it.",
    "RUNTIME is GATED: the OpenSpore original has never been executed in this repository, so no runtime claim of any kind is made for 0x005a2ed0. A differential test would need a driver, and the single recorded caller (0x005a2320) is a two-instruction receiver-adjustor thunk that tail-jumps here rather than calling it.",
    "The class of the object the word at receiver+0x10 points to is not established, and neither is the class of the table its +0x00 names. The single recorded caller, 0x005a2320, is a two-instruction receiver-adjustor thunk (SUB ECX,0x4 / JMP 0x005a2ed0), so the receiver here is a subobject pointer rather than a complete-object pointer, but the subobject's own layout past its +0x00 word is not observable from these twent
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-swarm-w2-005a2ed0/005a2ed0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w2-005a2ed0/sw2_005a2ed0.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w2-005a2ed0/sw2_005a2ed0_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w2-005a2ed0/sw2_005a2ed0_types.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-swarm-w2-005a2ed0/005a2ed0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w2-005a2ed0/sw2_005a2ed0.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w2-005a2ed0/sw2_005a2ed0_model_test.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w2-005a2ed0/sw2_005a2ed0_types.hpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.js
[TRUNCATED]
```
