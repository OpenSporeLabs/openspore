# Reconstruction context 0x00d20610

- Status: `partial`
- Content SHA-256: `a658705906bc19573f405338690f88cc973d978eeb521d5911f4e07313969668`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00d20610",
  "phase": "reconstruction",
  "target": "0x00d20610"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00d20610",
  "package": null,
  "subsystem": "Simulator",
  "va": "0x00d20610"
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
  "content_sha256": "e9362a5ce81d4c5ebf52eb3919b097ead1ee71c1f67b1c0271de4c3e788f6110",
  "live_attempts": [],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `present`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json

int __fastcall FUN_00d20610(int param_1)

{
  return param_1 + 0x1c8;
}


```

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall, receiver in ECX, zero stack arguments, callee pops nothing",
  "ordinary_stack_argument_slots": 0,
  "ordinary_stack_arguments": [],
  "receiver": "ECX, used only as the base register of the LEA's address computation and never dereferenced",
  "ret_form": "RET (0x00d20616 `c3`), no immediate",
  "return_note": "opaque 32-bit object pointer",
  "return_register": "EAX",
  "return_semantics": "the address receiver+0x1c8, computed by LEA and therefore never dereferenced by this function",
  "saved_registers": [],
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
      "va": "0x00ae73e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b3dbb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b444c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b48f20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b493e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b49a50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b4a720"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b4c850"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b537f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b56090"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b57c40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c05810"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c0c630"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c0eec0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c133d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c13650"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00ae78ab",
      "direction": "in",
      "other": "0x00ae73e0",
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
    "opaque 32-bit object pointer"
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
      "identify the class or classes whose accessors were merged or shared at this address, which the 95-site fan-in with six distinct ECX sources leaves open",
      "observe one real caller long enough to record what lives at receiver+0x1c8 and whether its element type is the float triple that some sites read at +0/+4/+8 or the pointer triple that others read",
      "separate __thiscall from __fastcall on a caller that also passes a second argument, which is the only shape where the two conventions differ observably"
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
      "va": "0x00ae73e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b3dbb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b444c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b48f20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b493e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b49a50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b4a720"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b4c850"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b537f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b56090"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b57c40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c05810"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c0c630"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c0eec0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c133d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c13650"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c13a30"
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
    "THE CALLER-SIDE EAX USE IS A MEASUREMENT OVER A WINDOW, NOT A WHOLE-BODY PROOF. The 71-of-95 pointer-consumption figure comes from a bounded scan of the 8 instructions following each call site, so it is a lower bound on pointer consumption, not an exhaustive classification of all 95 sites. The sampled remainder were read individually and all consume the result as a pointer or an argument.",
    "THE DERIVED ABI RECORD ABSTAINS AND THIS PACKAGE DOES NOT OVERRIDE IT. abi_derived.receiver is bounds_only with reason `ecx_address_taken_without_memory_access`, and inference R0 records the receiver register as null with UNKNOWN confidence. The consequence for the validator is stated plainly: FIELDS/OFFSETS cannot ground a declared offset, because there is no machine-derived receiver register to ground it against. The package therefore declares NO field offset, and the LEA displacement is carried as a computed constant instead.",
    "WHICH CLASS OWNS THE 0x1c8 SUB-OBJECT IS UNKNOWN, AND THE FAN-IN IS THE EVIDENCE AGAINST A SINGLE OWNER. 95 call sites in 88 functions load ECX from at least six distinct sources ([ESI+0x40], [ESI+0x80], [ESI+0x14], EDI, EAX, and LEA-computed values) and every one of them receives the same displacement. Either one class hierarchy supplies all of them, or the compiler/linker shared the accessor acr
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
