# Reconstruction context 0x00c77bf0

- Status: `partial`
- Content SHA-256: `76c7432ee828c8301e6dbb273c7302d0a8bf666e9b44631385e2a2b02c9be43f`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00c77bf0",
  "phase": "reconstruction",
  "target": "0x00c77bf0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00c77bf0",
  "package": null,
  "subsystem": "Simulator",
  "va": "0x00c77bf0"
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
  "content_sha256": "33129ca39c05c71b0ee68e0c19ab56f19cc1ed5ab9872ec289850908347655db",
  "live_attempts": [],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `present`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json

bool __thiscall FUN_00c77bf0(int param_1,uint param_2)

{
  uint *puVar1;
  int iVar2;
  uint local_10;
  undefined1 local_c [12];
  
  iVar2 = 0;
  for (puVar1 = *(uint **)(*(int *)(param_1 + 0x1120) + (param_2 % *(uint *)(param_1 + 0x1124)) * 4)
      ; puVar1 != (uint *)0x0; puVar1 = (uint *)puVar1[1]) {
    if (param_2 == *puVar1) {
      iVar2 = iVar2 + 1;
    }
  }
  if (iVar2 == 0) {
    local_10 = param_2;
    FUN_00de5df0(local_c,&local_10,0);
  }
  return iVar2 != 0;
}


```

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall (receiver in ECX), one ordinary stack argument, callee stack cleanup",
  "hidden_receiver": "ECX",
  "ordinary_stack_argument_slots": 1,
  "ordinary_stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "machine_type": "uint32",
      "normalized_name": "key",
      "position": 1,
      "read_at": "0x00c77bf6, MOV EDI,dword ptr [ESP+0x20] (the same slot after SUB ESP,0x10 and three pushes)",
      "width_bytes": 4
    }
  ],
  "receiver": true,
  "ret_form": "RET 0x4 (0x00c77c4c, bytes C2 04 00)",
  "return_register": "EAX",
  "return_semantics": "one byte. 0x00c77c21 is SETNZ BL over the match counter, 0x00c77c24/0x00c77c26 branch on it, and 0x00c77c46 is MOV AL,BL. Only AL is written, so the contract is 'AL is 0 or 1'. The upper three bytes of EAX are not part of it: at that point EAX still holds the array pointer the DIV sequence loaded at 0x00c77c07, and nothing in the body overwrites them. No caller in this package reads them.",
  "return_type": "bool",
  "return_width_bytes": 1,
  "saved_registers": [
    "EBX",
    "ESI",
    "EDI"
  ],
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "callee",
  "termination": "single RET at 0x00c77c4c; the body is 95 bytes and ends there"
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
      "va": "0x00ae9c90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aea8e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aea9e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aeaa80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aeab40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aeb240"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aeb3e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aebe90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aecf90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be92e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf4370"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c00b00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c389f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c7bd40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c81ab0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c82400"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00ae9cf0",
      "direction": "in",
      "other": "0x00ae9c90",
      "reference_type": "direct-call"
    },

[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [
    "global:PASS",
    "global:complete"
  ],
  "types": [
    "bool"
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
      "gate-simulator-callee-00de5df0-semantics",
      "gate-simulator-receiver-identity",
      "gate-simulator-table-purpose"
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
      "va": "0x00ae9c90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aea8e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aea9e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aeaa80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aeab40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aeb240"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aeb3e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aebe90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aecf90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be92e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf4370"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c00b00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c389f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c7bd40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c81ab0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c82400"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c830f0"
    },
    {
      "name": "PoliticalOwnershipS
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
    "Runtime behaviour. No original-process trace exists in this repository for this target; nothing was run and nothing failed.",
    "The original source expression behind the third argument. The value the callee observes is `key & 0xffffff00` and that is what is claimed and tested, but a flag argument sharing a reused stack slot is indistinguishable from a mask at this boundary.",
    "What the table is and what the key identifies. Sixteen callers are recorded, one carries a name, and none of that evidence licenses a purpose for the body.",
    "Whether 0x00de5df0's own semantics make it an insert, a notification, or a registration. The body discards its return value and only the miss path reaches it; the name used here ('insert') describes the ROLE this body gives it, not what it does.",
    "Whether the three words the callee removes are twelve bytes of arguments or a mix of arguments and something else. The body pushes three words and pops none, so the total is twelve; nothing here says what the callee does with them internally.",
    "Why the index record's callee_dependencies is MISSING while callers_dependencies is populated. The complete listing's single E8 is the callee oracle used here, and it agrees with the decompilation's FUN_00de5df0.",
    "gate-simulator-callee-00de5df0-semantics",
    "gate-simulator-receiver-identity",
    "gate-simulator-table-purpose"
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
