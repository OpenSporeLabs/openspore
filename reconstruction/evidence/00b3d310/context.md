# Reconstruction context 0x00b3d310

- Status: `partial`
- Content SHA-256: `322a181bd866b9c5329eb6258e49b46b0f76ba62573868a7119743e78c66b6dd`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00b3d310",
  "phase": "reconstruction",
  "target": "0x00b3d310"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00b3d310",
  "package": null,
  "subsystem": "Simulator",
  "va": "0x00b3d310"
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
  "content_sha256": "1e682f32bad14fe5faaa9ec9a6bd37e1a338f4ed3806a782ec30d7f780534adb",
  "live_attempts": [],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `present`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json

undefined4 FUN_00b3d310(void)

{
  return DAT_0167eae8;
}


```

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": null,
  "ordinary_stack_argument_slots": 0,
  "ordinary_stack_arguments": [],
  "receiver": "none. ECX is never read in any form (ABI observation R2, OBSERVED), so there is no register receiver and no hidden this-parameter.",
  "return_register": "EAX",
  "return_width_bytes": 4,
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "RET at 0x00b3d315, bare (no immediate)"
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
      "va": "0x00accf80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae0700"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b08670"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b08e90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b09830"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b32b20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b32ce0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b32dd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b32f60"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b330e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b33130"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b33350"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b334e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b335d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b34380"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b41ee0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00acd135",
      "direction": "in",
      "other": "0x00accf80",
      "reference_type": "direct-call"
    },

[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "OpaqueRootSlotTarget* (incomplete type; the machine fixes only the 4-byte width of EAX)"
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
      "no original-process trace exists for this target; nothing was attempted and nothing failed"
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
      "va": "0x00accf80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae0700"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b08670"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b08e90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b09830"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b32b20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b32ce0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b32dd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b32f60"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b330e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b33130"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b33350"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b334e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b335d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b34380"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b41ee0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b47ee0"
    },
    {
      "name": null,
      "reconst
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
  "files": [],
  "handoffs": [],
  "metadata": []
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
    "Does 0x0167eae8 ever alias any neighbouring slot (0x0167eae0, 0x0167eae4, 0x0167eaf0, 0x0167eaf8)? Adjacency in the .data tail proves nothing and no writer was located.",
    "Is the returned word a pointer, a handle, or an id? Three sampled callers dereference it at +0x20 or move it into ECX as a receiver, which is why it is modelled as a pointer -- but no callee through it has been resolved and no member is claimed.",
    "Runtime: no original-process trace exists in this repository for this target, so nothing here is a runtime claim.",
    "What class or object does 0x0167eae8 hold? No writer of the slot exists in the current analysis state, so its publication and teardown paths are unlocated. The raw-dword note in reconstruction/metadata/wave13-w1-core-b16/00b515e0.json (the address occurs once in the file, at 0x0073d311, as a decodable `A1 E8 EA 67 01 C3` in a region Ghidra has not split into a function) was NOT re-verified by this worker and is cited only as a lead.",
    "What is at displacement +0x20 of the pointee? Sampled callers read it; this body never does, so no member name is claimed.",
    "Which calling convention do the 90 direct callers actually use? The body cannot discriminate between the four, so the declared __cdecl is a source-side choice and the real answer needs a caller-side or import-side observation.",
    "no original-process trace exists for this target; nothing was attempted and nothing failed"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'derived'}, {'mode': 'derived', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'derived'}, {'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /decompile_function @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}`

```json
{
  "provenance": [
    {
      "mode": "derived",
      "ref": "GhidraMCP /disassemble_function",
      "source_class": "derived"
    },
    {
      "mode": "derived",
      "ref": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
      "source_class": "derived"
    },
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
      "ref": "GhidraMCP REST /decompile_function @ http://127.0.0.1:8089",
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
