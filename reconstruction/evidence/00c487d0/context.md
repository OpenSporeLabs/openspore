# Reconstruction context 0x00c487d0

- Status: `partial`
- Content SHA-256: `aacab4b09b3b712a68239e9252fc75118aae2b3e7241858a665105590fd33082`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00c487d0",
  "phase": "reconstruction",
  "target": "0x00c487d0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00c487d0",
  "package": null,
  "subsystem": "Simulator",
  "va": "0x00c487d0"
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
  "content_sha256": "bd6af19adeb37cea21b0b9ab3dc3983507790b30fb78db418671ed33a7bc70dc",
  "live_attempts": [],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `present`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json

void __fastcall FUN_00c487d0(int *param_1)

{
  short sVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  int *piVar5;
  short *psVar6;
  short *psVar7;
  int unaff_EBP;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  undefined1 auStack_28 [20];
  undefined1 auStack_14 [4];
  undefined4 uStack_10;
  
  uVar2 = (**(code **)(*param_1 + 0xa4))();
  *(int **)(DAT_016e0d08 + 0x18) = param_1;
  *(undefined4 *)(DAT_016e0d08 + 0x48) = uVar2;
  iVar3 = FUN_01021260();
  if (iVar3 == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = *(undefined4 *)(iVar3 + 0x13c);
  }
  FUN_00c452a0();
  uVar4 = FUN_00c451e0();
  FUN_006b5060();
  if ((int *)param_1[0x5f] != (int *)0x0) {
    param_1 = (int *)param_1[0x5f];
  }
  piVar5 = (int *)FUN_00aed4d0();
  FUN_00aed4d0();
  iVar3 = *piVar5;
  uVar2 = FUN_01021300(uVar2,param_1);
  uVar2 = (**(code **)(iVar3 + 0x24))(auStack_14,uVar4,uVar2);
  (**(code **)(unaff_EBP + 0xc))(unaff_ESI,uStack_10,uVar2);
  psVar6 = (short *)FUN_006b55c0();
  sVar1 = *psVar6;
  psVar7 = psVar6;
  while (sVar1 != 0) {
    psVar7 = psVar7 + 1;
    sVar1 = *psVar7;
  }
  FUN_00423650(psVar6,psVar6 + ((int)psVar7 - (int)psVar6 >> 1));
  *(undefined1 **)(DAT_016e0d08 + 0x18) = auStack_28;
  *(undefined4 *)(DAT_016e0d08 + 0x48) = unaff_EDI;
  FUN_006b5240();
  return;
}


```

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_this": true,
  "receiver_register": "ECX",
  "ret_form": "RET 0x8",
  "return_note": "unresolved - artifact classes the last EAX write as aggregate_unknown and the body computes nothing after POP EBX; the reconstruction returns void and reports the type as open",
  "return_register": "EAX",
  "saved_registers": [
    "EBX",
    "EBP",
    "ESI",
    "EDI"
  ],
  "stack_cleanup_bytes": 8,
  "stack_cleanup_owner": "callee"
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "FUN_01021260",
      "reconstructed": true,
      "va": "0x01021260"
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
      "va": "0x00c48d40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c48db0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c48e00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4c4b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4ea70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4ef00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4ef90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4fa40"
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
      "va": "0x00c52160"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c521c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c53720"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c552d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c55330"
    },
    {
      "name": null,
      "reconstru
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "unresolved - artifact classes the last EAX write as aggregate_unknown and the body computes nothing after POP EBX; the reconstruction returns void and reports the type as open"
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
      "name": "FUN_01021260",
      "reconstructed": true,
      "va": "0x01021260"
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
      "va": "0x00c48d40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c48db0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c48e00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4c4b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4ea70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4ef00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4ef90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4fa40"
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
      "va": "0x00c52160"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c521c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c53720"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c552d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c55330"
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
    "package": "PKG-SIMULATOR-SAFE-WAVE11",
    "score": 8,
    "symbol": "cycle_key_006286a0",
    "va": "0x006286a0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "PKG-SIMULATOR-SAFE-WAVE11",
    "score": 8,
    "symbol": "release_child_0062c910",
    "va": "0x0062c910"
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
    "Are the two words of the descriptor at entry_ESP-0x08 initialised anywhere? The body never initialises them and never reads them before 0x006b55c0/dispatch calls that may write through the address at entry_ESP-0x14.",
    "Does this function really return void? The abi artifact classes the last EAX write as aggregate_unknown and the body computes nothing after POP EBX, so no return type is claimed.",
    "Is the 5/4 dispatch arity split correct, or is it 6/3? No arity is OBSERVED; only the sum is. This is the first claim to move if a differential run disagrees.",
    "The 0x01409b1c string constant the wrapper constructor stores at +0x08 and the wide-data source the wrapper accessor eventually yields are untraced.",
    "The 20+ callers (0x00c48d40, 0x00c48db0, 0x00c48e00, 0x00c4c4b0, 0x00c4ea70, 0x00c4ef00, 0x00c4ef90, 0x00c4fa40, 0x00c4fc00, 0x00c4fe60, 0x00c52160, 0x00c521c0, 0x00c53720, 0x00c552d0, 0x00c55330, ...) are unreconstructed; a caller's use of EAX is the cheapest way to settle the return type and could also cross-check the arity split.",
    "What are the two 0x00aed4d0 accessors? Each returns an object whose first word indexes a table, and each result is used exactly once as a dispatch receiver, but nothing identifies them. 0x00aed4d0 itself lazily builds a singleton from `FUN_00f473a0(4,\"Simulator\",0,0,0,0)` with vtable PTR_LAB_0145c0b4.",
    "What is 0x016e0d08, and what do ScopeState::field_18 and +0x48 mean? The save/publish/restore pattern is observed; the identity is not, and it is not Simulator::
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
