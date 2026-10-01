# Reconstruction context 0x00d00a10

- Status: `partial`
- Content SHA-256: `bf542ba9df98ace2a73724f197d33eba5231d24073ef9d8157e913271fd51000`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00d00a10",
  "phase": "reconstruction",
  "target": "0x00d00a10"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00d00a10",
  "package": null,
  "subsystem": "Simulator",
  "va": "0x00d00a10"
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
  "content_sha256": "72205718477ce65c0b860e162b4f013f03c1c38d8bb36c7bddbb94037e7893ab",
  "live_attempts": [],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `present`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json

float10 FUN_00d00a10(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  float10 fVar1;
  float fVar2;
  
  fVar1 = (float10)FUN_00d05a20(param_1,param_2,param_3);
  fVar2 = (float)fVar1;
  if ((float)fVar1 <= -10.0) {
    fVar2 = -10.0;
  }
  if (10.0 <= fVar2) {
    fVar2 = 10.0;
  }
  return (float10)fVar2;
}


```

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__stdcall for the three stack arguments (OBSERVED from RET 0xc); the receiver rides in ECX and is forwarded without ever being touched (INFERRED from the call sites and from the callee's own prologue)",
  "ordinary_stack_argument_slots": 3,
  "ordinary_stack_arguments": [
    {
      "entry_offset": "entry_ESP+0x4",
      "observed": true,
      "ordinal": 1,
      "read": true,
      "size_inferred": false,
      "sizes": [
        4
      ],
      "written": false
    },
    {
      "entry_offset": "entry_ESP+0x8",
      "observed": true,
      "ordinal": 2,
      "read": true,
      "size_inferred": false,
      "sizes": [
        4
      ],
      "written": false
    },
    {
      "entry_offset": "entry_ESP+0xc",
      "observed": true,
      "ordinal": 3,
      "read": true,
      "size_inferred": false,
      "sizes": [
        4
      ],
      "written": false
    }
  ],
  "receiver": "ECX, read by nobody in this body and written by nobody in this body; it is handed to the callee unchanged",
  "ret_form": "RET 0xc (0x00d00a62 `c2 0c 00`)",
  "return_register": "ST0",
  "return_semantics": "the x87 top of stack, loaded by `FLD float ptr [ESP]` at 0x00d00a5c from the value the clamp step stored at [ESP] on 0x00d00a57",
  "return_type": "float",
  "saved_registers": [
    "EBX",
    "ESI",
    "EDI",
    "EBP"
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
      "va": "0x00bf9e70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bfa660"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c2f650"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c2fea0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c309e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c31640"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c468b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c469f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c46ab0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c46b80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c62ff0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c76800"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c94470"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ce1690"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ce1810"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ce5190"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00bfa191",
      "direction": "in",
      "other": "0x00bf9e70",
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
    "float"
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
      "confirm whether the two .rdata bounds are patched at run time, which would make the clamp range dynamic and would justify reading them per call rather than as constants",
      "execute the wrapper under a real evaluator (0x00d05a20) rather than the model test's stub, which is the only way to see the clamp engage on values the game actually produces",
      "observe one real caller long enough to record what the three forwarded words carry and what the clamped quantity represents, which would settle the undefined4 typing this package declines to guess"
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
      "va": "0x00bf9e70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bfa660"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c2f650"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c2fea0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c309e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c31640"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c468b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c469f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c46ab0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c46b80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c62ff0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c76800"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c94470"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ce1690"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ce1810"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ce5190"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ceee30"
    },
    {
      "name": "RelationshipScoreOb
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
    "NO RUNTIME EVIDENCE EXISTS. Nothing in this repository has run the original process for this target, so the model test is a static model of the listing and not a differential test against the game. The runtime gate is open and nothing was attempted.",
    "THE CALLEE IS A SEPARATE TARGET AND IS NOT RECONSTRUCTED. 0x00d05a20 is 279 instructions and this package models only its ABI. In particular the model test SUPPLIES the evaluated value rather than deriving it, so the clamp is measured against a controlled input and not against the real evaluator. Any claim about what the clamped quantity represents -- a distance, a ratio, a score -- would have to come from that target.",
    "THE GLOBAL CHECK IS WARN, NOT PASS, AND THAT IS CORRECT. validation.md reports GLOBALS at partial coverage because the data-reference artifact records 2 reference rows for this body against the 2 addresses the listing names, which is complete for the body; the residual WARN reflects that the artifact is read whole rather than sliced to this span. The CONSTANTS check is likewise WARN with degraded=True and unparsed=2, while the disassembly category itself lists all 20 instructions with no parse failure -- the two unparsed lines are counted against the ABI grammar, not against the listing, and the 85 bytes were re-read from memory to confirm the listing is complete.",
    "THE RECEIVER CONVENTION IS NOT SETTLED BY THE CALLEE UNDER RECONSTRUCTION. The derived ABI record's inference R2 says ECX is never read in any form, and abi_derived.receiver is nu
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
