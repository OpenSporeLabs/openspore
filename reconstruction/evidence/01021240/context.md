# Reconstruction context 0x01021240

- Status: `partial`
- Content SHA-256: `bb517eba42876df3dd17b8fe20d639969aa1e0204e5cdbf7d5cbd352583b351c`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x01021240",
  "phase": "reconstruction",
  "target": "0x01021240"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_01021240",
  "package": null,
  "subsystem": "Simulator",
  "va": "0x01021240"
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
  "content_sha256": "7a20f4293c65ba011a1b9942276e9273c15fd53587f219dc7c746c2ecfe1af18",
  "live_attempts": [],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `present`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json

undefined4 FUN_01021240(void)

{
  if (*(int *)(Simulator__sSpacePlayerData + 8) != 0) {
    return *(undefined4 *)(*(int *)(Simulator__sSpacePlayerData + 8) + 0x48);
  }
  return 0;
}


```

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__cdecl",
  "ordinary_stack_arguments": [],
  "receiver": null,
  "ret_form": "RET",
  "return": "uint32 in EAX",
  "return_semantics": "integral_in_EAX",
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller"
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
      "va": "0x00bb4ba0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bba4b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c314a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c31550"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c341a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c382e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c3a2b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c3ae70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c3dba0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4ea70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4f160"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c53720"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c5eed0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c5efb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c5f690"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c61070"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00bb4caf",
      "direction": "in",
      "other": "0x00bb4ba0",
      "reference_type": "direct-call"
    },

[TRUNCATED]
```

## 08_types_fields_globals

- State: `missing`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [],
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
  "callees": [],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb4ba0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bba4b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c314a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c31550"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c341a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c382e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c3a2b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c3ae70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c3dba0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4ea70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4f160"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c53720"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c5eed0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c5efb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c5f690"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c61070"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c7bd40"
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
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "PKG-SIMULATOR-SAFE-WAVE11",
    "score": 8,
    "symbol": "dispatch_key_00628450",
    "va": "0x00628450"
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
    "Simulator__sSpacePlayerData is defined by both this package and src/reconstruction/pkg01_roots/space_player_data_accessors.cpp. If the integrator merges them into one target, exactly one definition must survive; that reconciliation was left to the integrator.",
    "The caller's domain is not established. 74 caller functions and 100 xref sites are consistent with a widely-used identity accessor, but fan-in alone does not show what any of them do with the value, and no caller was decompiled under this run's bounded budget.",
    "The calling convention is undetermined by the body. __cdecl is declared because it is the least committal zero-parameter leaf shape and agrees with the caller-owned cleanup the ABI record states as INFERRED, but __stdcall with zero callee cleanup is byte-identical here and nothing in this body distinguishes them.",
    "Whether the returned word is genuinely an intrusive_ptr<Simulator::cStarRecord> payload, as the SDK offset column suggests, or a differently-typed 32-bit word that merely occupies 0x48, is not settled by this body's own listing. The reconstruction claims the displacement and the zero-guard and deliberately says nothing about what the word addresses."
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
