# Reconstruction context 0x00b8d9b0

- Status: `partial`
- Content SHA-256: `b5db4e5af8be4f3e56d35aa21349fddfb36ee6c8c00b4cf82a3bb76ac62233a6`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00b8d9b0",
  "phase": "reconstruction",
  "target": "0x00b8d9b0"
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
  "va": "0x00b8d9b0"
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
  "content_sha256": "7d94b8f8507ed7f3c9adac6b97204d60b1e8bd4f4a33e561e94100e069f7e4be",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00b8d9b0 failed: Decompilation did not complete. Reason: ",
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
  "hidden_receiver": "read; ESI holds it for the whole body and is pushed as the argument to both callees",
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": 0,
  "receiver": true,
  "ret_form": "RET (with a tail JMP to 0x00c4b220 on the deepest path)",
  "return_observation": "Three exits write EAX: 0x00b8d9e1 MOV EAX,EDI (provably 0 on that path), 0x00b8d9e3 the preserved EDI from tier 1, and the tail transfer at 0x00b8d9dc which returns 0x00c4b220's EAX unchanged. The full dword is defined on every exit.",
  "return_register": "EAX",
  "return_semantics": "an opaque context handle: the non-null result of the tier-1 registry resolve, otherwise the tier-2 mission context's lazily resolved +0x1F4 slot, otherwise exactly 0",
  "return_type": "std::uint32_t",
  "return_width_bytes": 4,
  "saved_registers": [
    "ESI",
    "EDI"
  ],
  "stack_arguments": [],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "RET at 0x00b8d9e5, or JMP 0x00c4b220 at 0x00b8d9dc"
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
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b8d9f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bba870"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c44d00"
    },
    {
      "name": "FUN_00c59240",
      "reconstructed": false,
      "va": "0x00c59240"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c59540"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e2eba0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e98500"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fdf5b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fdf5f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fe7e60"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x010727e0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00b8da09",
      "direction": "in",
      "other": "0x00b8d9f0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00bba885",
      "direction": "in",
      "other": "0x00bba870",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c44d16",
      "direction": "in",
      "other": "0x00c44d00",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c593f3",
      "direction": 
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
      "A runtime write watchpoint on the singleton at 0x0167EAE4 and on the context field at +0x1F4 is required to confirm the lazy-resolution claim about 0x00c4b220, which this batch inferred from static structure only.",
      "No original-process trace has ever been captured for this function; the original Cell stage has never been entered in any recorded run. Every claim here is static.",
      "The concrete type of the returned handle can only be established by observing a receiver at a callsite and locating its vtable, neither of which is possible statically.",
      "The tier-1/tier-2 split is a runtime-behavioural claim about which registry is populated in a given game state. A differential test must exercise at least one planet that resolves through tier 1 and one that falls through to tier 2, and observe that tier 1's cross-context write is invisible to the caller."
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
      "name": "FUN_00b3d2a0",
      "reconstructed": true,
      "va": "0x00b3d2a0"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b8d9f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bba870"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c44d00"
    },
    {
      "name": "FUN_00c59240",
      "reconstructed": false,
      "va": "0x00c59240"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c59540"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e2eba0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e98500"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fdf5b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fdf5f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fe7e60"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x010727e0"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00b8da09",
      "direction": "in",
      "other": "0x00b8d9f0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00bba885",
      "direction": "in",
      "other": "0x00bba870",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c44d16",
      "direction": "in",
      "other": "0x00c44d00",
      "reference_
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
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 3,
    "symbol": "FUN_00b3d2a0",
    "va": "0x00b3d2a0"
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
    "reconstruction/staging/wave13-w1-core-b06/b8d9b0_planet_record_resolve_context.cpp",
    "reconstruction/staging/wave13-w1-core-b06/sim_core_b06_model_test.cpp",
    "reconstruction/staging/wave13-w1-core-b06/sim_core_b06_opaque.hpp",
    "reconstruction/staging/wave13-w1-core-b06/sim_core_b06_ports_model.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-core-b06/00b8d9b0.json"
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
    "A runtime write watchpoint on the singleton at 0x0167EAE4 and on the context field at +0x1F4 is required to confirm the lazy-resolution claim about 0x00c4b220, which this batch inferred from static structure only.",
    "Does tier 2 ever need to run in practice? Tier 1 covers records whose planet id is in the manager's registry, and 0x00bba870 already iterates a list calling this function per element, which suggests tier 1 usually succeeds. No static evidence establishes how often tier 2 is reached.",
    "No original-process trace has ever been captured for this function; the original Cell stage has never been entered in any recorded run. Every claim here is static.",
    "The briefing's canonical ledger recorded callee_count 5 and caller_count 11; both match the live xref query, with the note that 0x00bba870 calls it inside a loop rather than once.",
    "The concrete type of the returned handle can only be established by observing a receiver at a callsite and locating its vtable, neither of which is possible statically.",
    "The tier-1/tier-2 split is a runtime-behavioural claim about which registry is populated in a given game state. A differential test must exercise at least one planet that resolves through tier 1 and one that falls through to tier 2, and observe that tier 1's cross-context write is invisible to the caller.",
    "What class owns the singleton at 0x0167EAE4? It has a registry header at +0x184 and a lazily resolved pointer at +0x1F4, so it is at least 0x1F8 bytes. The SDK's attribution of the conta
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-w1-core-b06/00b8d9b0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b06/b8d9b0_planet_record_resolve_context.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b06/sim_core_b06_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b06/sim_core_b06_opaque.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b06/sim_core_b06_ports_model.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave13-w1-core-b06/00b8d9b0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b06/b8d9b0_planet_record_resolve_context.cpp",
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
