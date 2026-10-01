# Reconstruction context 0x00b25fb0

- Status: `partial`
- Content SHA-256: `b773f9d421887c93a4f2353d20ca7f409c44430d42da57c110f2ed07b031f540`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00b25fb0",
  "phase": "reconstruction",
  "target": "0x00b25fb0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00b25fb0",
  "package": null,
  "subsystem": "Simulator",
  "va": "0x00b25fb0"
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
  "content_sha256": "e9dd71476cac84f3058f7b227c819b060b6358223b6b141279f3de050788546e",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00b25fb0 failed: Decompilation did not complete. Reason: ",
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
  "hidden_this_register": "ECX",
  "hidden_this_type": "NounProjection*",
  "ordinary_stack_arguments": [],
  "return_note": "opaque result word",
  "return_register": "EAX",
  "return_type": "NounObject*",
  "return_width_bytes": 4,
  "saved_registers": [
    "ESI",
    "ECX"
  ],
  "stack_cleanup_bytes": 0,
  "termination": "plain RET"
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "FUN_00b25f40",
      "reconstructed": false,
      "va": "0x00b25f40"
    },
    {
      "name": "pkg12_space_01021300",
      "reconstructed": true,
      "va": "0x01021300"
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae2f70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae37c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aeb240"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aebe90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aee830"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b5f670"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b998a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b99ed0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bcc860"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bd7ea0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bd80d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bdb3b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bdde70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bde4a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be1340"
    },
    {
      "name": null,
      "reconstr
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "NounObject* opaque result word",
    "NounProjection*"
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
      "The current-player provider must return a valid state window before +0x84 is read.",
      "The null-current receiver fallback must not be treated as a valid noun-object result by downstream callers without runtime evidence.",
      "The receiver must be a valid noun-projection-compatible object for 0x00b25f40.",
      "The resolver vector, object pointers, object vtables, and vtable+0x4c targets must be valid.",
      "The resolver's 0x00b21340 map/list callbacks and their ownership effects require original-process observation."
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
      "name": "FUN_00b25f40",
      "reconstructed": false,
      "va": "0x00b25f40"
    },
    {
      "name": "pkg12_space_01021300",
      "reconstructed": true,
      "va": "0x01021300"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae2f70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae37c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aeb240"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aebe90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aee830"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b5f670"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b998a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b99ed0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bcc860"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bd7ea0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bd80d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bdb3b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bdde70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bde4a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be1340"
    },
    {
     
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
  "files": [],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg13-c2-tribe-civilization/00b25fb0.json"
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
        "0x00b3d2a0",
        "0x00b3d300",
        "0x00b5b800",
        "0x01021300",
        "0x01021300",
        "0x00ad23c0",
        "0x00adbca0",
        "0x00ae73e0",
        "0x00ae9590",
        "0x00ae9930",
        "0x00ae9c90",
        "0x00ae9f50",
        "0x00aeb3e0",
        "0x00aeb3e0",
        "0x00aebe90",
        "0x00b25fb0"
      ],
      "conflict_id": "global_root_identities",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
      "resolution_status": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
      "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
      "subject": null,
      "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
    }
  ],
  "unresolved_questions": [
    "The current-player provider must return a valid state window before +0x84 is read.",
    "The null-current receiver fallback must not be treated as a valid noun-object result by downstream callers without runtime evidence.",
    "The receiver must be a valid noun-projection-compatible object for 0x00b25f40.",
    "The resolver vector, object pointers, object vtables, and vtable+0x4c targets must be valid.",
    "The resolver's 0x00b21340 map/list callbacks and their ownership effects require original-pro
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg13-c2-tribe-civilization/00b25fb0.json', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg13-c2-tribe-civilization/00b25fb0.json",
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
