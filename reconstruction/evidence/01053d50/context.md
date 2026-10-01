# Reconstruction context 0x01053d50

- Status: `partial`
- Content SHA-256: `7eddbdfcb9b366649a7860557a36f41dca80f944e9085a2c80d25ba98cb06344`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x01053d50",
  "phase": "reconstruction",
  "target": "0x01053d50"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_01053d50",
  "package": "pkg-sim-toolevent-01053d50",
  "subsystem": "Simulator",
  "va": "0x01053d50"
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
  "content_sha256": "140324ead9bb2055fecd0cd5d702ebb89f5c23b5885c803ed9a0efac6caf3437",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x01053d50 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "thiscall",
  "hidden_this": true,
  "receiver_register": "ECX",
  "ret_form": "ret 0x8",
  "return_type": "void",
  "saved_registers": [
    "ESI",
    "EDI"
  ],
  "stack_arguments": [
    {
      "entry_slot": "ESP+0x04 at function entry",
      "observed_use": "Loaded by MOV EAX,dword ptr [ESP + 0x4c] at 0x01053d84, where ESP is already 0x48 below the entry ESP, so the slot is entry ESP+0x04. It is pushed as the first stack argument of the virtual call at 0x01053d8f and is used nowhere else in the body.",
      "position": 1,
      "type": "void * (opaque, forwarded only)",
      "width_bytes": 4
    },
    {
      "entry_slot": "ESP+0x08 at function entry",
      "observed_use": "Loaded by MOV EDI,dword ptr [ESP + 0x50] at 0x01053d55 into EDI, which is kept live across three calls. It is the first stack argument of the frame constructor at 0x01053d65, whose body copies 12 bytes from it, and the second stack argument of the virtual call at 0x01053d8f.",
      "position": 2,
      "type": "const OpaqueVector3 * (12-byte float triple)",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 8,
  "stack_cleanup_owner": "callee",
  "termination": "Unconditional fall-through to the epilogue. The body contains no conditional branch, no loop, and no early exit, so every call in the sequence executes on every invocation."
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "Simulator_cSpaceTrading_Get",
      "reconstructed": true,
      "va": "0x00b3d4d0"
    }
  ],
  "callers": [],
  "edge_rows": [
    {
      "callsite": "0x01053d65",
      "direction": "out",
      "other": "0x00ad79d0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x01053d95",
      "direction": "out",
      "other": "0x00ad7ad0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x01053d7d",
      "direction": "out",
      "other": "0x00ae09b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x01053d76",
      "direction": "out",
      "other": "0x00b3d4d0",
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
    "OpaqueQuaternion16 (4 floats)",
    "OpaqueVector3 (3 floats)",
    "Word (__thiscall *)(OpaqueToolEventReceiver *, void *, const OpaqueVector3 *)",
    "const OpaqueToolEventVTable *",
    "const OpaqueVector3 * (12-byte float triple)",
    "float[4]",
    "void",
    "void (__thiscall *)(void *)",
    "void *",
    "void * (opaque, forwarded only)",
    "void *[19]"
  ],
  "vtables": [
    "vtable:0x010537b0",
    "vtable:0x0149b810",
    "vtable:0x0149b8b4",
    "vtable:0x0149b900"
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
      "name": "Simulator_cSpaceTrading_Get",
      "reconstructed": true,
      "va": "0x00b3d4d0"
    }
  ],
  "callees_truncated": false,
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x01053d65",
      "direction": "out",
      "other": "0x00ad79d0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x01053d95",
      "direction": "out",
      "other": "0x00ad7ad0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x01053d7d",
      "direction": "out",
      "other": "0x00ae09b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x01053d76",
      "direction": "out",
      "other": "0x00b3d4d0",
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
    "0x00b3d4d0"
  ],
  "scc": {
    "id": "scc-0608",
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
      "same_calling_convention"
    ],
    "package": "PKG-13-E4-EMPIRE-WAVE3",
    "score": 8,
    "symbol": "EmpirePoliticalColor_00c32cd0",
    "va": "0x00c32cd0"
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
    "package": "PKG-SIMULATOR-SAFE-WAVE11",
    "score": 6,
    "symbol": "cycle_key_006286a0",
    "va": "0x006286a0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-SIMULATOR-SAFE-WAVE11",
    "score": 6,
    "symbol": "release_child_0062c910",
    "va": "0x0062c910"
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
    "reconstruction/staging/pkg-sim-toolevent-01053d50/sim_tool_event_01053d50.cpp",
    "reconstruction/staging/pkg-sim-toolevent-01053d50/sim_tool_event_01053d50.hpp",
    "reconstruction/staging/pkg-sim-toolevent-01053d50/sim_tool_event_01053d50_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-sim-toolevent-01053d50/01053d50.json"
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
    "No differential runtime corpus exists for this virtual, so the ordering and the dispatch are static-only evidence.",
    "The 16-byte rotation source is never written by this body, so the value the frame receives through that argument is indeterminate here. The original source most plausibly passed a default-constructed or dead value that the compiler proved irrelevant, but nothing in this VA's evidence shows which.",
    "The base of each pointer block, and therefore the index-8 reading and the resolution of the dispatched byte offset 0x4c to 0x007b86e0, rest on the repetition pattern alone. If the true base is four words later, this function is index 4 and the dispatched word is 0x010537e0 instead.",
    "The first stack argument is forwarded to the dispatched slot and used nowhere else. Its type is not determined; it is compatible with the cSpaceToolData * that the SDK attaches to the sibling virtual at 0x01053db0, but that is an SDK guess on a different function and is not adopted here.",
    "The image carries no name for 0x01053d50, so none is claimed. The class is not established either: the function is index 8 of six pointer blocks, but the repeated first word of those blocks is a constructor, so they are not plain MSVC vtables and no RTTI complete-object locator is available to name the class.",
    "The role of the dispatched slot is unresolved. The address the block reading resolves to decrements a refcount-like word and calls a callback when it reaches zero, but the two forwarded arguments are ignored by it, 
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-sim-toolevent-01053d50/01053d50.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-sim-toolevent-01053d50/sim_tool_event_01053d50.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-sim-toolevent-01053d50/sim_tool_event_01053d50.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-sim-toolevent-01053d50/sim_tool_event_01053d50_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-sim-toolevent-01053d50/01053d50.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-sim-toolevent-01053d50/sim_tool_event_01053d50.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-sim-toolevent-01053d50/sim_tool_event_01053d50.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-sim-toolevent-01053d50/sim_tool_event_01053d50_model_test.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_f
[TRUNCATED]
```
