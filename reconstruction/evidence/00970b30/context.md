# Reconstruction context 0x00970b30

- Status: `partial`
- Content SHA-256: `2b8e3ed66f10da12c9bc262a4938022f27eacc7a7ceb4898bbf094c45710c289`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00970b30",
  "phase": "reconstruction",
  "target": "0x00970b30"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00970b30",
  "package": null,
  "subsystem": "Simulator",
  "va": "0x00970b30"
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
  "content_sha256": "f2b7edebf57e7ae385e4af838c8d16376d4593888cf9c900183c8bc54fc1b11e",
  "live_attempts": [],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `present`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json

undefined4 __fastcall FUN_00970b30(int param_1)

{
  return *(undefined4 *)(param_1 + 0x1e8);
}


```

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall (ECX carries the receiver and is dereferenced through the single memory operand before any definite write; bare RET with no imm16; no stack word read as an argument)",
  "ordinary_stack_argument_slots": 0,
  "ordinary_stack_arguments": [],
  "receiver": "ECX, read at 0x00970b30 as the base of the single memory operand `dword ptr [ECX + 0x1e8]`; never copied to another register and never written",
  "ret_form": "RET (0x00970b36, byte 0xc3, no imm16)",
  "return_register": "EAX",
  "return_semantics": "the 32-bit word STORED at receiver+0x1e8, copied bit for bit into EAX and re-typed as a pointer; the sampled callers dereference it",
  "return_type": "void*",
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
      "va": "0x00c4b250"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4b2b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4b7f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4c090"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4c130"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4c3f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4c690"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4c790"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4ccd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4e440"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4ea70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4f220"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4f4e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4fc00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4fe60"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c50940"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00c4b279",
      "direction": "in",
      "other": "0x00c4b250",
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
    "void*"
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
  "callees": [],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4b250"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4b2b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4b7f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4c090"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4c130"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4c3f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4c690"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4c790"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4ccd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4e440"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4ea70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4f220"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4f4e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4fc00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4fe60"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c50940"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c51010"
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
    "Do the 69 distinct callers share one receiver class, or is this slot reachable from more than one type? The fan-in is high and uniform but no witness names the receiver's origin.",
    "Is 0x00970b10 the only writer of the slot, and is the adjacent setter the only such accessor pair? The setter is adjacent in the image, which is an adjacency and not an enumeration of writers elsewhere in the binary.",
    "What does the pointer at receiver+0x1e8 point to, and what is at its displacement 0x13c? Three callers load there and one SDK-independent note names nothing; the pointee's type is UNKNOWN.",
    "Which class is the receiver? Nothing in the pack names it; the record has no namespace, no SDK association and no type. The 142 callers all supply their own ECX and the pack does not say from where.",
    "Why does the adjacent setter also write [ECX+0x9c] with the constant 1 in the same call? That coupling is observed but its meaning is not recoverable from this target's evidence."
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
