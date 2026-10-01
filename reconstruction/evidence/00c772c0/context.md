# Reconstruction context 0x00c772c0

- Status: `partial`
- Content SHA-256: `69282e5495e12ef961a4d0bc7e31f9847f16eb01ea7b4c50d2632dbb805c5541`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00c772c0",
  "phase": "reconstruction",
  "target": "0x00c772c0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00c772c0",
  "package": null,
  "subsystem": "Simulator",
  "va": "0x00c772c0"
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
  "content_sha256": "c55780d8f1c814391b6839ced54e9a51944825fd72fc18e10f7af53bc23e22e2",
  "live_attempts": [],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `present`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json

bool __thiscall FUN_00c772c0(int param_1,uint param_2)

{
  uint *puVar1;
  int iVar2;
  
  iVar2 = 0;
  for (puVar1 = *(uint **)(*(int *)(param_1 + 0x1120) + (param_2 % *(uint *)(param_1 + 0x1124)) * 4)
      ; puVar1 != (uint *)0x0; puVar1 = (uint *)puVar1[1]) {
    if (param_2 == *puVar1) {
      iVar2 = iVar2 + 1;
    }
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
  "calling_convention": "__thiscall, receiver in ECX, one 4-byte ordinary stack argument at entry_ESP+0x4, callee pops 4 bytes",
  "ordinary_stack_argument_slots": 1,
  "ordinary_stack_arguments": [
    {
      "entry_offset": "entry_ESP+0x4",
      "observed": true,
      "ordinal": 1,
      "read": true,
      "role": "the 32-bit key: it is the dividend of the DIV at 0x00c772ca and the value compared against every chain link at 0x00c772e0",
      "size_inferred": false,
      "sizes": [
        4
      ],
      "written": false
    }
  ],
  "receiver": "ECX, used as the base of exactly two reads, at +0x1120 and +0x1124",
  "ret_form": "RET 0x4 (0x00c772f5, bytes c2 04 00)",
  "return_register": "EAX",
  "return_semantics": "EAX provably holds 0 or 1 at the terminator, and the upper 24 bits are provably zero. 0x00c772ec XOR EAX,EAX is the last write to the whole register, and 0x00c772f1 SETNZ AL writes only AL. This is stronger than the ABI record's return_semantics=unclassified_in_EAX, which is a machine-derived label that does not model SETNZ. The match COUNT in ESI survives only as its own non-zeroness, so a chain holding the key twice answers 1, not 2.",
  "saved_registers": [
    "EDI",
    "ESI"
  ],
  "stack_cleanup_bytes": 4,
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
      "va": "0x00ae9930"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb9ff0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be92e0"
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
      "va": "0x00c5ff50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c79fa0"
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
      "name": "PoliticalOwnershipScan_00c8d060",
      "reconstructed": true,
      "va": "0x00c8d060"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cc99b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cd4460"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cd44a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cd6980"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cf7630"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00ae9a30",
      "direction": "in",
      "other": "0x00ae9930",
      "reference_
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
      "va": "0x00ae9930"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb9ff0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be92e0"
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
      "va": "0x00c5ff50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c79fa0"
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
      "name": "PoliticalOwnershipScan_00c8d060",
      "reconstructed": true,
      "va": "0x00c8d060"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cc99b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cd4460"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cd44a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cd6980"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cf7630"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cf93b0"
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
    "The class that owns the words at +0x1120 and +0x1124. No MSVC RTTI in this binary, and the evidence pack's types and vtables categories are both absent.",
    "The semantics of the sibling 0x00c77bf0, which two reconstructed callers invoke on this entry's false path with the same receiver and key. That is a separate target owned by another worker; it is the natural next question for this family but it is not answered here.",
    "What the 32-bit values are: a hashed token, a packed enum and a resource id all index and compare identically here. Caller analysis narrowed them to 31-bit immediate constants but did not identify a kind.",
    "Whether any real chain can be cyclic. The loop has no cap and no identity check, so a cycle would not terminate.",
    "Whether the count at +0x1124 is ever zero in a real instance. The body never tests it, so a zero would trap the machine with #DE, and nothing here shows whether the container can be constructed in that state."
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
