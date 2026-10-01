# Reconstruction context 0x00b72370

- Status: `partial`
- Content SHA-256: `9c9c444da56776ad33a8de93e2c1f70033a843b373261ee9e5f01f1acd1e2cc8`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00b72370",
  "phase": "reconstruction",
  "target": "0x00b72370"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "Simulator::cObjectPool_::DeleteObject",
  "package": null,
  "subsystem": "Simulator",
  "va": "0x00b72370"
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
  "status": "queued"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "cf82b7c6de125b8efdec09a23114e738439644ca170417e45d82ec4f2ddf43ee",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00b72370 failed: Decompilation did not complete. Reason: ",
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
  "hidden_receiver": "ECX is the cObjectPool_ receiver; 0x00b72373 MOV ESI,ECX",
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": 0,
  "receiver_register": "ECX",
  "ret_form": "plain RET",
  "return_register": "none",
  "return_semantics": "void; the value returned by the dispatched slot is discarded",
  "return_type": "void",
  "saved_registers": [
    "EBX",
    "ESI",
    "EDI"
  ],
  "stack_arguments": 0,
  "stack_cleanup_bytes": 0,
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
      "callsite": "0x00b72375",
      "direction": "out",
      "other": "0x00883860",
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
    "DATA",
    "openspore::reconstruction::pkg_orchestrate_dogfood_00b72370::DeleteObjectGlobals",
    "openspore::reconstruction::pkg_orchestrate_dogfood_00b72370::DeleteObjectPorts",
    "openspore::reconstruction::pkg_orchestrate_dogfood_00b72370::OpaqueDispatchTarget",
    "openspore::reconstruction::pkg_orchestrate_dogfood_00b72370::OpaqueDispatchTargetVtable",
    "openspore::reconstruction::pkg_orchestrate_dogfood_00b72370::OpaqueObjectPoolReceiver",
    "openspore::reconstruction::pkg_orchestrate_dogfood_00b72370::PublishedDeleteRecord",
    "void"
  ],
  "vtables": [
    "vtable:0x014650e8"
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
      "Observe a real dispatch through the vtable word at 0x014650f0 and record the receiver instance state before and after the five stores.",
      "Observe initialization and write ordering of the global word 0x016514cc through 0x00883870.",
      "Observe whether any later consumer reads the receiver words at +0x28 and +0x2c published here; 0x00b79a60 is the only such consumer found statically.",
      "Record the concrete target of the vtable slot at displacement 0x24 and observe its argument use and return-value handling.",
      "Record the live values of the eight words at 0x01465004 and the concrete class of the object returned by 0x00883860."
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
      "callsite": "0x00b72375",
      "direction": "out",
      "other": "0x00883860",
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
    "id": "scc-0401",
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
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "pkg-sim-toolevent-01053d50",
    "score": 8,
    "symbol": "sim_toolevent_slot8_fun_01053d50",
    "va": "0x01053d50"
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
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__cObjectPool___DeleteObject.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__cObjectPool___DeleteObject.c",
    "reconstruction/staging/pkg-orchestrate-dogfood-00b72370/dogfood_00b72370.cpp",
    "reconstruction/staging/pkg-orchestrate-dogfood-00b72370/dogfood_00b72370.hpp",
    "reconstruction/staging/pkg-orchestrate-dogfood-00b72370/dogfood_00b72370_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-orchestrate-dogfood-00b72370/00b72370.json"
  ]
}
```

## 13_semantic_hypotheses

- State: `missing`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

## 14_conflicts_questions

- State: `conflicted`
- Provenance: `reconstruction/knowledge/index.json, knowledgegraph/research/semantic-decomp.json`

```json
{
  "conflicts": [
    {
      "anchors": [
        "0x00eedd40",
        "0x00e7fd00",
        "0x00e74a20",
        "0x00e74a20",
        "0x00e5b790",
        "0x00e80ba0",
        "0x00b72370",
        "0x00b72320",
        "0x00e780a0",
        "0x00b72160",
        "0x00b72260",
        "0x00b72270",
        "0x00b72370",
        "0x00bb4100",
        "0x00bb42a0"
      ],
      "conflict_id": "U-008-scenario-respawner",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The cited direct body establishes a bounded state mutation or call anchor, but the full transition policy, consumer order, and runtime reachability remain unresolved.",
      "resolution_status": "The cited direct body establishes a bounded state mutation or call anchor, but the full transition policy, consumer order, and runtime reachability remain unresolved.",
      "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
      "subject": null,
      "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
    }
  ],
  "unresolved_questions": [
    "Is 0x014650e8 the true base of the containing vtable, or is it a word inside a larger class-registration table? The run is contiguous but sits next to class-name strings and a NULL separator, and the class owner is unknown.",
    "Is the receiver-minus-four word (LEA EBX,[ESI + -0x4]) a cObjectPoolIndex as the SDK decompilation names it, an adjusted this, or an unrelated token? The disassembly pushes no stack argument, so the SDK's second formal cannot be a par
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/Simulator__cObjectPool___DeleteObject.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-orchestrate-dogfood-00b72370/00b72370.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-orchestrate-dogfood-00b72370/dogfood_00b72370.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-orchestrate-dogfood-00b72370/dogfood_00b72370.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-orchestrate-dogfood-00b72370/dogfood_00b72370_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__cObjectPool___DeleteObject.c",
      "source_class": "committed_artifact"
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
      "ref": "reconstruction/metadata/pkg-orchestrate-dogfood-00b72370/00b72370.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-orchestrate-dogfood-00b72370/dogfood_00b72370.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-orchestrate-dogfood-00b72370/dogfood_00b72370.hpp",
      "source_class": "committed_artifact"
    },
    {
      
[TRUNCATED]
```
