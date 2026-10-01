# Reconstruction context 0x00baf700

- Status: `partial`
- Content SHA-256: `e49b60c6be0ad6825fda692a9afb6fd845b30bc6ddab694c699a011c5637453c`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00baf700",
  "phase": "reconstruction",
  "target": "0x00baf700"
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
  "va": "0x00baf700"
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
  "content_sha256": "e96e497e24eb045efe28654cf90bbd01bd73d2a78b3f07bb4312a3418506f635",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00baf700 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "__stdcall encoding (one callee-cleaned stack dword); the incoming ECX is preserved and never read, so the function is best modelled as a static member taking one argument",
  "hidden_receiver": "unread: the incoming ECX is pushed at 0x00baf700 and popped at 0x00baf734/0x00baf789 without ever being dereferenced or tested",
  "hidden_this_register": "ECX, saved and restored but never read; the reconstruction therefore does not consume it",
  "ordinary_stack_argument_slots": 1,
  "receiver": "present but unread",
  "ret_form": "RET 0x4 (at both 0x00baf735 and 0x00baf78a)",
  "return_observation": "0x00baf730: MOV EAX,[EAX + 0x14] returns the mapped value on a hit; 0x00baf784: MOV EAX,[EAX] returns the RE-READ slot content on a miss, not the earlier pointer. Both exits write the full dword.",
  "return_register": "EAX",
  "return_semantics": "the interned object registered for the hashed name: node->value on a hit, or the value the factory's +0x2C slot stored into the node on a miss",
  "return_type": "std::uint32_t",
  "return_width_bytes": 4,
  "saved_registers": [
    "EBX",
    "ECX",
    "ESI",
    "EDI"
  ],
  "stack_arguments": [
    {
      "instruction": "0x00baf701: MOV ECX,dword ptr [ESP + 0x8] after the PUSH ECX, i.e. the entry stack argument",
      "offset": "ESP+0x4 at entry",
      "role": "selector token, passed as the ECX receiver of the callee 0x00c30e80 and stored as the map key",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "callee",
  "termination": "two exits,
[TRUNCATED]
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
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
      "va": "0x00bd9a80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c322f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c35320"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c75940"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c75d70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c76800"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c784c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fed640"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ff5930"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01030930"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x010309c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01030a30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01030aa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x010407d0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00bd9ad9",
      "direction": "in",
      "other": "0x00bd9a80",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c323f7",
      "direction": "in",
     
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "std::uint32_t"
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
      "No original-process trace has ever been captured for this function; the original Cell stage has never been entered in any recorded run. Every claim here is static.",
      "The create path cannot execute before the factory host at 0x015FD8A8 is installed, and that host is zero in the shipping image. A differential test must first establish the host is live, then observe the first miss and the exact object the factory stores.",
      "The low-byte keying collision risk in 0x00dd85c0 can only be settled by enumerating the runtime hashed names 0x00c30cc0 can produce and checking for shared top 24 bits.",
      "The re-fetch after the factory call is a correctness claim about tree rebalancing. Confirming it needs a case where the factory inserts enough nodes to force a rebalance, which cannot be provoked statically.",
      "The zero-before-release ordering is a re-entrancy and observability claim. Confirming it needs a concurrent reader of 0x0156C61C during the release, which only a runtime harness can arrange."
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
  "callees": [
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
      "va": "0x00bd9a80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c322f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c35320"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c75940"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c75d70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c76800"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c784c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fed640"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ff5930"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01030930"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x010309c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01030a30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01030aa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x010407d0"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00bd9ad9",
      "direction": "in",
      "other": "0x00bd9a80",
      "reference_type": "dir
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
    "package": "PKG-20-GAMEGLOBAL",
    "score": 3,
    "symbol": "map_int_whatever_find",
    "va": "0x00e5c780"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/wave13-w1-core-b06/baf700_interned_object_get_or_create.cpp",
    "reconstruction/staging/wave13-w1-core-b06/sim_core_b06_model_test.cpp",
    "reconstruction/staging/wave13-w1-core-b06/sim_core_b06_opaque.hpp",
    "reconstruction/staging/wave13-w1-core-b06/sim_core_b06_ports_model.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-core-b06/00baf700.json"
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
    "Does the low-byte-of-the-value keying in 0x00dd85c0 ever cause two distinct names to collide? The insertion path takes the key's top 24 bits and the queried value's low byte, so collision depends on runtime hash values. No static evidence establishes whether the hashed names produced by 0x00c30cc0 ever share their top 24 bits, and if they do the table would return the wrong object.",
    "Is 0x00c30e80's receiver the caller's stack argument or the preserved ECX? The body loads the stack argument into ECX at 0x00baf701 and then calls 0x00c30e80, so the callee receives the STACK ARGUMENT as its this pointer. If the original source intended a different receiver, the compiled code disagrees with the intent, and static evidence cannot say which is which.",
    "No original-process trace has ever been captured for this function; the original Cell stage has never been entered in any recorded run. Every claim here is static.",
    "The briefing's canonical ledger recorded caller_count 14 and callee_count 4; the live xref query confirms 15 call sites in 14 caller functions (0x00c784c0 contributing two) and 5 distinct callees (0x00c30e80, 0x00e5c780, 0x0067de30, 0x00dd85c0, and the two vtable slots counted as one entry in the briefing's static call graph because they are indirect). The difference is a counting convention, not a contradiction; the two vtable dispatches are the briefing's omission.",
    "The create path cannot execute before the factory host at 0x015FD8A8 is installed, and that host is zero in the shipping image. A
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-w1-core-b06/00baf700.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b06/baf700_interned_object_get_or_create.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b06/sim_core_b06_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b06/sim_core_b06_opaque.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b06/sim_core_b06_ports_model.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave13-w1-core-b06/00baf700.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b06/baf700_interned_object_get_or_create.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b06/sim_core_b06_model_test.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b06/sim_core_b06_opaque.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "
[TRUNCATED]
```
