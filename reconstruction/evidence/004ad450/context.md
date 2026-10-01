# Reconstruction context 0x004ad450

- Status: `partial`
- Content SHA-256: `044a591f573cac907094d4ea1c17ad6520b80b1f52fe4d92ba6950929925a037`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x004ad450",
  "phase": "reconstruction",
  "target": "0x004ad450"
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
  "va": "0x004ad450"
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
  "content_sha256": "cb5caafdc8e52e2c1c8f82c3eccf56cdf7ee54208caaac5877a333400d3d1ed2",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x004ad450 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "__thiscall (receiver in ECX), no stack arguments",
  "hidden_receiver": "ECX",
  "hidden_this_register": "ECX is read only by the spill at 0x004ad456",
  "ordinary_stack_argument_slots": 0,
  "receiver": true,
  "ret_form": "RET",
  "return_observation": "0x004ad45c loads the field into ECX, 0x004ad45f stores it to [EBP-4] and 0x004ad462 loads it straight back into EAX; the round trip through the frame slot is a register-allocation artefact with no effect. There is no null check and no LEA, so the value is the field itself and not &field.",
  "return_register": "EAX",
  "return_semantics": "the pointer stored at receiver+0x30, unmodified and untested",
  "return_type": "void*",
  "return_width_bytes": 4,
  "saved_registers": [
    "EBP"
  ],
  "stack_arguments": [],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "single RET at 0x004ad468"
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
      "va": "0x0048d010"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0048dcd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00491b40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004956b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004a6690"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0057d710"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005b9840"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005ba320"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005bb5a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005bc0f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005bccc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005d27e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005d36e0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x0048d56d",
      "direction": "in",
      "other": "0x0048d010",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0048dd3c",
      "direction": "in",
      "other": "0x0048dcd0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0048e231",
      "direction": "in",
      "other": "0x0048dcd0",
      "reference_type": "direct-cal
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "void*"
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
      "No original-process trace has been captured. Whether the +0x30 pointer is ever null at a callsite is a runtime fact; statically the getter propagates whatever is there.",
      "The 26 uninspected callsites need at least a sample disassembled before the uniform 'result is the next receiver' reading can be generalised."
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
      "va": "0x0048d010"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0048dcd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00491b40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004956b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004a6690"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0057d710"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005b9840"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005ba320"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005bb5a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005bc0f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005bccc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005d27e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005d36e0"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x0048d56d",
      "direction": "in",
      "other": "0x0048d010",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0048dd3c",
      "direction": "in",
      "other": "0x0048dcd0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0048e231",
    
[TRUNCATED]
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "shared_types:void*"
    ],
    "package": "PKG-APP-SAFE-WAVE11",
    "score": 3,
    "symbol": "property_record_assign_pair_004279d0",
    "va": "0x004279d0"
  },
  {
    "match_basis": [
      "shared_types:void*"
    ],
    "package": "PKG-PALETTE-SAFE-WAVE11",
    "score": 3,
    "symbol": "palette_safe_wave11_fill_node_array_005c7ff0",
    "va": "0x005c7ff0"
  },
  {
    "match_basis": [
      "shared_types:void*"
    ],
    "package": "PKG-APP-SERVICES-SAFE-WAVE11",
    "score": 3,
    "symbol": "service_005fa8d0",
    "va": "0x005fa8d0"
  },
  {
    "match_basis": [
      "shared_types:void*"
    ],
    "package": "PKG-APP-SERVICES-SAFE-WAVE11",
    "score": 3,
    "symbol": "service_0060ee90",
    "va": "0x0060ee90"
  },
  {
    "match_basis": [
      "shared_types:void*"
    ],
    "package": "pkg-swarm-w1-00641fd0",
    "score": 3,
    "symbol": "sporepedia_cached_handle_00641fd0",
    "va": "0x00641fd0"
  },
  {
    "match_basis": [
      "shared_types:void*"
    ],
    "package": "pkg-vft-slot-006e64f0",
    "score": 3,
    "symbol": "re_006e64f0",
    "va": "0x006e64f0"
  },
  {
    "match_basis": [
      "shared_types:void*"
    ],
    "package": "PKG-UTFWIN-CORE-WAVE6",
    "score": 3,
    "symbol": "re_00835380",
    "va": "0x00835380"
  },
  {
    "match_basis": [
      "shared_types:void*"
    ],
    "package": "pkg-orchestrate-dogfood-008db310",
    "score": 3,
    "symbol": "pf_index_write_bounds_008db310",
    "va": "0x008db310"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/wave13-w1-dispatch-b04/004ad450_related_pointer_getter.cpp",
    "reconstruction/staging/wave13-w1-dispatch-b04/004ad450_related_pointer_getter.hpp",
    "reconstruction/staging/wave13-w1-dispatch-b04/wave13_w1_dispatch_b04_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-dispatch-b04/004ad450.json"
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
    "Are the 26 uninspected callsites all shaped like the three inspected ones, i.e. moving the result into ECX? If some test the result, the null contract would differ per caller.",
    "No original-process trace has been captured. Whether the +0x30 pointer is ever null at a callsite is a runtime fact; statically the getter propagates whatever is there.",
    "The 26 uninspected callsites need at least a sample disassembled before the uniform 'result is the next receiver' reading can be generalised.",
    "The receiver's +0x00 vtable is dispatched by a sibling with the address of the global DAT_013ec468 as its argument. What that global holds, and what those two slots do, was not established.",
    "What class is the receiver? Nothing in the binary names it, and this binary has no RTTI, so the vtable at +0x00 that 0x004ad280 dispatches could not be tied to a declaration.",
    "What do 0x004b9440 and 0x004b9420 do? 0x004b9440's body writes its stack argument into [*(this+0xC)+0x1C], which is enough to prove the returned pointer has a +0xC sub-object and nothing more.",
    "What is the relationship between the receiver and the object at +0x30 - owner, child, observer? 0x004b9570 takes both, which shows the receiver matters to the callee, but the direction was not established.",
    "Why do five sites in FUN_005bb5a0 and four in FUN_005bccc0 call this getter? A one-word accessor with that much fan-in is either a hot shared sub-object or a vtable-like dispatch that Ghidra has not recognised. Neither was investigated."
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-w1-dispatch-b04/004ad450.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b04/004ad450_related_pointer_getter.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b04/004ad450_related_pointer_getter.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b04/wave13_w1_dispatch_b04_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave13-w1-dispatch-b04/004ad450.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b04/004ad450_related_pointer_getter.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b04/004ad450_related_pointer_getter.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b04/wave13_w1_dispatch_b04_model_test.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_fi
[TRUNCATED]
```
