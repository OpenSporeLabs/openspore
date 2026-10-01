# Reconstruction context 0x00bba790

- Status: `partial`
- Content SHA-256: `3a1d9333c8ff6a19bc302249e094e4b878035bff9036b3c74a0c15dc09f739da`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00bba790",
  "phase": "reconstruction",
  "target": "0x00bba790"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00bba790",
  "package": null,
  "subsystem": "Simulator",
  "va": "0x00bba790"
}
```

## 03_current_status

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "blocked": false,
  "reconstructed": false,
  "runtime_gated": false,
  "runtime_validated": 0,
  "status": "candidate"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "d1f62b7d0c1fc0e21b509e88e837d90d12fb0ab30ab2f2b4f6412564b7abf248",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00bba790 failed: Decompilation did not complete. Reason: ",
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
  "hidden_this": true,
  "hidden_this_register": "ECX",
  "receiver": true,
  "receiver_register": "ECX",
  "ret_form": "RET",
  "return_register": "EAX",
  "return_semantics": "unclassified_in_EAX",
  "saved_registers": [
    "EBP",
    "EBX",
    "EDI",
    "ESI"
  ],
  "stack_arguments": {
    "confidence": "APPROXIMATION",
    "derived_slots": 0,
    "gaps": 0,
    "not_complete": false,
    "observed_slots": 0,
    "slots": [],
    "total_bytes": 0,
    "widths_ambiguous": false
  },
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
      "name": "FUN_00aea5d0",
      "reconstructed": true,
      "va": "0x00aea5d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b8d970"
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb2330"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb23e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb4100"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb5ae0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bba870"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bba8c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bba913"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bba990"
    },
    {
      "name": "FUN_00c31730",
      "reconstructed": false,
      "va": "0x00c31730"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c341a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c344f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c34ee0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c35240"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c35810"
    },
    {
      "name": "FUN_00c47e20",
      "reconstructed": false,
      "va": "0x00c47e20"
    },
    {
      "name": null,
      "recons
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "NodeKeepPending",
    "OpaqueSimState*",
    "OpaqueWordVector*",
    "StateRefresh",
    "VectorGrowInsert",
    "VectorReserve",
    "VectorResize"
  ],
  "vtables": []
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
      "name": "FUN_00aea5d0",
      "reconstructed": true,
      "va": "0x00aea5d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b8d970"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb2330"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb23e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb4100"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb5ae0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bba870"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bba8c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bba913"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bba990"
    },
    {
      "name": "FUN_00c31730",
      "reconstructed": false,
      "va": "0x00c31730"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c341a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c344f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c34ee0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c35240"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c35810"
    },
    {
      "name": "FUN_00c47e20",
      "reconstructed": false,
      "va": "0x00c47e20"
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
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-13-E4-EMPIRE-WAVE3",
    "score": 6,
    "symbol": "EmpirePoliticalColor_00c32cd0",
    "va": "0x00c32cd0"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg_sim_f00bba790/sim_f00bba790.cpp",
    "reconstruction/staging/pkg_sim_f00bba790/sim_f00bba790.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-sim-f00bba790/00bba790.json"
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
    "0x00e25bd0 and 0x00d01790 are inferred to clean their own 8 and 4 bytes because the stack is not adjusted after either call; their actual ret forms are not observed from this listing.",
    "The bodies of 0x00bba640, 0x00e25bd0, 0x00d01790, 0x00b8d970 and 0x00aea5d0 are unresolved; each is declared as a port carrying only its observed call shape and is never given a fabricated body.",
    "The class identity of the receiver and the concrete type behind the vector words are unresolved; only element+0x00 and its first table word are observed, so the node and its dispatch table stay opaque.",
    "The element dispatch is only observed as MOV EAX,[ECX]; MOV EDX,[EAX]; CALL EDX. Reading element+0x00 as a table pointer is an inference from that shape, not a confirmed vtable.",
    "The exact element stride beyond the 4-byte word implied by SAR 2 is fixed by the listing, but the semantic width of a pending element is not stated by the evidence.",
    "The meaning of the two words 0x00e25bd0 receives (the active vector's own begin and end at the call) is not observable here; the port carries both verbatim.",
    "The pending vector at +0x84 is read-only here, so the transferred elements are still listed after a flush; whether another function clears it is not observable from this listing.",
    "The predicate implemented by 0x00b8d970 is unknown; only its effect is observed, that a non-zero AL leaves the element in the pending vector.",
    "The receiver fields below +0x5c, the range +0x60..+0x83, the word at +0x8c and the range
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-sim-f00bba790/00bba790.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg_sim_f00bba790/sim_f00bba790.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg_sim_f00bba790/sim_f00bba790.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-sim-f00bba790/00bba790.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg_sim_f00bba790/sim_f00bba790.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg_sim_f00bba790/sim_f00bba790.hpp",
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
    "E
[TRUNCATED]
```
