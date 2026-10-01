# Reconstruction context 0x00b8de30

- Status: `partial`
- Content SHA-256: `22debb746cef6a353c0b464ace5afadbdf12ed6aefd94ac38dc79bba29aa7f6d`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00b8de30",
  "phase": "reconstruction",
  "target": "0x00b8de30"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00b8de30",
  "package": null,
  "subsystem": "Simulator",
  "va": "0x00b8de30"
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
  "content_sha256": "b158ca312389be20e5199d3bc8d1f7700077a4ad26197247d58adfa89865cb5d",
  "live_attempts": [],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `present`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json

void __fastcall FUN_00b8de30(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = *(undefined4 *)(param_1 + 0x184);
  FUN_00b3d2a0(uVar1);
  uVar1 = FUN_00ba6440(uVar1);
  FUN_00b3d2a0(uVar1);
  FUN_00ba6d80(uVar1);
  return;
}


```

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall (receiver in ECX), zero ordinary stack arguments, caller cleans the stack",
  "hidden_receiver": "ECX",
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": 0,
  "ordinary_stack_arguments": [],
  "receiver": true,
  "ret_form": "RET (0x00b8de50, byte 0xc3, no imm16)",
  "return_observation": "NOT a claim that the machine returns nothing. The validator's own must-analysis classes this shape UNCLASSIFIED (the last value-producing op is a CALL), so the machine offers no return verdict for this target whatever the source declares. No typedef of the record's register-class vocabulary was written to make a comparison succeed. READ THIS BEFORE TRUSTING THE VERDICT: the committed knowledge-index record for 0x00b8de30 carries abi {}, so before this sidecar existed RETURN SEMANTICS was NOT_AVAILABLE (no canonical return_type in any ABI layer). This sidecar's observed_original_abi.return_t...",
  "return_register": "EAX",
  "return_semantics": "no value produced by this body. The last value-producing operation in the complete listing is CALL 0x00ba6d80, and nothing in the body then writes EAX before the RET, so whatever that callee left in EAX is what a caller sees and this body makes no statement about it. The derived record is explicit that the width is not determinable here: return_semantics 'unclassified_in_EAX', and inference RT2 registers the last EAX write as register_class 'aggregate_unknown'.",
  "return_type": "void",
  "return_width_bytes": 0,
  "saved_registers": [],
  "stack_cleanup_bytes": 0
[TRUNCATED]
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "FUN_00b3d2a0",
      "reconstructed": true,
      "va": "0x00b3d2a0"
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b96d40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00baf130"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb59b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb9ff0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bbe470"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bbe5f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bc0180"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bd9a80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be9b20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c316c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c34e70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c35810"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c44d00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c46590"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c47a10"
    },
    {
      "name": "FUN_00c47e20",
      "reconstructed": false,
      "va": "0x00c47e20"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x0
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "void"
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
      "gate-simulator-callee-00ba6440-semantics",
      "gate-simulator-callee-00ba6d80-semantics",
      "gate-simulator-receiver-field-identity"
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
      "name": "FUN_00b3d2a0",
      "reconstructed": true,
      "va": "0x00b3d2a0"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b96d40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00baf130"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb59b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb9ff0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bbe470"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bbe5f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bc0180"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bd9a80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be9b20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c316c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c34e70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c35810"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c44d00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c46590"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c47a10"
    },
    {
      "name": "FUN_00c47e20",
      "reconstructed": false,
      "va": "0x00c47e20"
    },
    {
      "name":
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
      "direct_xref_neighbor"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 9,
    "symbol": "FUN_00b3d2a0",
    "va": "0x00b3d2a0"
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
    "Runtime behaviour. No original-process trace exists in this repository for this target; nothing was run and nothing failed.",
    "The C type of the return, and specifically whether the RETURN SEMANTICS PASS is worth anything. The machine's last value-producing op is a CALL, so the width is not determinable and the validator's must-analysis classes the state UNCLASSIFIED. A caller listing (0x00bbe608, `mov edi,eax` immediately after the call) shows at least one consumer reading EAX, so the body is not provably void at the ABI level. The declared void reflects that this body produces no value of its own, and the discrepancy is left open rather than resolved. Note also that the PASS is source-vs-THIS-SIDECAR agreement: the committed index record carries abi {}, so with no worker return_type on record the check is NOT_AVAILABLE.",
    "What the dword at receiver + 0x184 denotes. The receiver record is bounds_only and no evidence in this package names the member.",
    "Whether the two thiscall callees 0x00ba6440 and 0x00ba6d80 are members of one class, which would make this a two-step forward. 0x00ba6440 does not read ECX at all and 0x00ba6d80 reads two fields of it; that is a fact about those bodies and no claim is made about a shared class.",
    "Why the record's dependencies.edges projects zero outgoing callees for this target. The export records four outgoing rows over three addresses, and the projection's 30-row window is spent entirely on the 160 incoming ones. CALLS reads the export whole and PASSes; the projection 
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
