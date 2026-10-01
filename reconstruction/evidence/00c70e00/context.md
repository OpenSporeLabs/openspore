# Reconstruction context 0x00c70e00

- Status: `partial`
- Content SHA-256: `01483ac37de01e3118900396f5007a3e9c8dd6093e7780b13a29401434a97abd`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00c70e00",
  "phase": "reconstruction",
  "target": "0x00c70e00"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00c70e00",
  "package": null,
  "subsystem": "Simulator",
  "va": "0x00c70e00"
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
  "content_sha256": "319b654b6f1c0db4695c2de871ef38a5c8df48ba5e83e3e085c3a0b36660189e",
  "live_attempts": [],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `present`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json

undefined4 __fastcall FUN_00c70e00(int param_1)

{
  undefined4 uVar1;
  
  if (*(int *)(param_1 + 0x13c) != 0) {
    uVar1 = FUN_00b8dab0();
    return uVar1;
  }
  return 1;
}


```

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall (one register argument in ECX, read before any definite write and dereferenced; zero ordinary stack arguments; the callee pops nothing because 0x00c70e14 is the bare byte 0xc3, so the caller owns stack cleanup)",
  "ordinary_stack_argument_slots": 0,
  "ordinary_stack_arguments": [],
  "receiver": "ECX, read at 0x00c70e00 as the base of the body's only memory operand `dword ptr [ECX + 0x13c]` and never written before that read",
  "ret_form": "RET (0x00c70e14, byte 0xc3, no imm16)",
  "return_note": "32-bit dword",
  "return_register": "EAX",
  "return_semantics": "on the null arm the immediate 1 written by `MOV EAX,imm32` at 0x00c70e0f; on the non-null arm the 32-bit word the tail target reads at receiver+0x194",
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller"
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "FUN_00b8dab0",
      "reconstructed": false,
      "va": "0x00b8dab0"
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b6baf0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba0080"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba1ce0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bbe740"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bc0180"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bc1450"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bcece0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bd0140"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be2110"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf71d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bfb930"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bff2d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c51bb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c82d50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c830f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d56c30"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00b6c0c5",
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "32-bit dword"
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
      "name": "FUN_00b8dab0",
      "reconstructed": false,
      "va": "0x00b8dab0"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b6baf0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba0080"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba1ce0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bbe740"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bc0180"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bc1450"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bcece0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bd0140"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be2110"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf71d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bfb930"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bff2d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c51bb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c82d50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c830f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d56c30"
    },
    {
      "name": null,
  
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
    "Do the two paths' return values denote the same quantity? Nothing in the evidence settles it, and the two arms share one signature.",
    "Is the constant 1 a boolean, an enum member, a sentinel, or a count? The four sampled callers only order the result against 0x4 and 0x5, which is consistent with every one of those readings.",
    "Is the receiver argument a `this` or an ordinary first parameter? The bytes cannot say (see not_claimed), and the answer is what would settle __thiscall against __fastcall.",
    "What class is the TAIL receiver, and does it need an AddRef? The tail target's body is seven bytes with no room for a reference call, so ownership is undetermined; the promoted sibling pkg-00b8dab0-field194-getter carries the same open question for the same word.",
    "What does the word at receiver+0x13c name, and what class does the receiver belong to? Nothing in the pack names either; the receiver record is bounds_only and the types/globals/vtables categories are all MISSING.",
    "Why does the derived ABI record abstain with verdict ABI_UNKNOWN? Its own inference T2 gives the reason as the tail transfer - 'the function can reach a caller by transferring out of the listing, so the path that actually returns was never observed' - at confidence UNKNOWN. That observation is incomplete for this body: 0x00c70e0f/0x00c70e14 IS a returning path in the same listing, and the transfer's own target is a two-instruction body whose MOV EAX/RET was read live. See the tooling note in the report."
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
