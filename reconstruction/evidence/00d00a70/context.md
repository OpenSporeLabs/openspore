# Reconstruction context 0x00d00a70

- Status: `partial`
- Content SHA-256: `bb89f6bb8d778783e4dd3beaafb2393eb88e31dae41dfd460d564075bbfd2bd2`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00d00a70",
  "phase": "reconstruction",
  "target": "0x00d00a70"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00d00a70",
  "package": null,
  "subsystem": "Simulator",
  "va": "0x00d00a70"
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
  "content_sha256": "31b7dad7c244051b7cd22d740f3c33a360f33f344cfaad54d15495b9d29ce7f1",
  "live_attempts": [],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `present`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json

undefined4 __thiscall
FUN_00d00a70(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  float10 fVar1;
  float fVar2;
  
  fVar1 = (float10)FUN_00d05a20(param_2,param_3,param_4);
  fVar2 = (float)fVar1;
  if ((float)fVar1 <= -10.0) {
    fVar2 = -10.0;
  }
  if (10.0 <= fVar2) {
    fVar2 = 10.0;
  }
  if ((*(float *)(param_1 + 0x14) < fVar2) && (fVar2 < *(float *)(param_1 + 0x18))) {
    return 2;
  }
  if ((*(float *)(param_1 + 0x18) <= fVar2) && (fVar2 < *(float *)(param_1 + 0x1c))) {
    return 3;
  }
  if (*(float *)(param_1 + 0x1c) <= fVar2) {
    return 4;
  }
  if ((fVar2 <= *(float *)(param_1 + 0x14)) &&
     (*(float *)(param_1 + 0x10) <= fVar2 && fVar2 != *(float *)(param_1 + 0x10))) {
    return 1;
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
  "calling_convention": "__thiscall, receiver in ECX, three 4-byte callee-cleaned stack arguments",
  "ordinary_stack_arguments": [
    {
      "entry_offset": "entry_ESP+0x4",
      "meaning": "forwarded to 0x00d05a20 as its first argument, unmodified",
      "ordinal": 1,
      "read_at": "0x00d00a77",
      "width_bytes": 4
    },
    {
      "entry_offset": "entry_ESP+0x8",
      "meaning": "forwarded to 0x00d05a20 as its second argument, unmodified",
      "ordinal": 2,
      "read_at": "0x00d00a7e",
      "width_bytes": 4
    },
    {
      "entry_offset": "entry_ESP+0xc",
      "meaning": "forwarded to 0x00d05a20 as its third argument, unmodified",
      "ordinal": 3,
      "read_at": "0x00d00a73",
      "width_bytes": 4
    }
  ],
  "receiver": "ECX at entry, moved to ESI at 0x00d00a7c and read at +0x10/+0x14/+0x18/+0x1c; never written",
  "ret_form": "RET 0xc, at 0x00d00b03, 0x00d00b15, 0x00d00b2c and 0x00d00b35 -- one terminator per exit",
  "return_register": "EAX",
  "return_semantics": "one of the five immediates 0,1,2,3,4: `XOR EAX,EAX` at 0x00d00b2f, `MOV EAX,0x1` at 0x00d00b23, `MOV EAX,0x2` at 0x00d00ade, `MOV EAX,0x3` at 0x00d00afa, `MOV EAX,0x4` at 0x00d00b0c -- one per exit, all of them integers",
  "return_type": "std::int32_t",
  "saved_registers": [
    "ESI"
  ],
  "stack_cleanup_bytes": 12,
  "stack_cleanup_owner": "callee"
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
      "va": "0x00ae2e20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aea3d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aee830"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b68090"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba58f3"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba5a60"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba5bd3"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba5d30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be88d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bef620"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf5cb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf74a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf8440"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bfa660"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bfbbf0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c0e6a0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00ae2e2c",
      "direction": "in",
      "other": "0x00ae2e20",
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
    "std::int32_t"
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
      "establish whether the two clamp bounds at 0x01478d5c/0x01478d60 are constants for the whole subsystem or are shadowed per instance at run time",
      "observe a write to receiver+0x10..0x1c to establish what calibrates the four edges, and whether the calibration is per-receiver or shared",
      "read enough of the 42 call sites to find the index's consumer: a site that stores the result to a word and later compares that word against a small constant would identify what the five bands mean",
      "run the original under a trace with the four receiver edges set to distinct, recorded values and confirm the five band answers, which would turn the arithmetic partition from a transcription into an observation",
      "run the original with one of the four edges set to a NaN and confirm the band answer, which is the case this package can only trace from COMISS's documented flag behaviour"
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
      "va": "0x00ae2e20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aea3d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aee830"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b68090"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba58f3"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba5a60"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba5bd3"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba5d30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be88d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bef620"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf5cb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf74a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf8440"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bfa660"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bfbbf0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c0e6a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c238b0"
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
    "NO RUNTIME EVIDENCE EXISTS. Nothing in this repository has run the original process for this target, so the model test is a static model of the listing and not a differential test against the game.",
    "THE CALIBRATION OF THE FOUR EDGES IS NOT OBSERVED. Nothing shows what sets 0x10..0x1c, whether they can be re-tuned at runtime, and whether they are per-receiver or shared. The clamp bounds at 0x01478d5c/0x01478d60 ARE constants in the data section, but that says nothing about the four edges.",
    "THE DERIVED ABI RECORD'S RETURN_REGISTER IS WRONG AND THE PACK DOES NOT SAY SO. It says ST0. The listing says EAX, and this package's header documents the disagreement, but the persisted `conflicts` array in evidence.json is empty and `records/0x00d00a70` in reconstruction/knowledge/index.json still carries the ST0 claim. An integrator reading the index rather than the header would inherit it.",
    "THE UNORDERED CASES ARE TRACED, NOT MEASURED. The five band answers under an unordered receiver float are derived from COMISS's documented flag behaviour and are asserted against the reconstruction's helpers, not against the original process. A trace of the original under a NaN edge would settle them.",
    "WHAT THE FOUR RECEIVER FLOATS ARE IS UNKNOWN, AND IT IS THE QUESTION THAT WOULD NAME THE FUNCTION. They are four compared edges on a receiver this body shares with 42 call sites, and nothing in this package's evidence writes them or shows a caller reading the answer back into them. The band partition in `semantic_findings` i
[TRUNCATED]
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
