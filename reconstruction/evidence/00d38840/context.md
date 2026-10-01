# Reconstruction context 0x00d38840

- Status: `partial`
- Content SHA-256: `c13c75bd984da3cba053690daa0e84ecfedd2528b9ce9f42e1441f0d0f643028`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00d38840",
  "phase": "reconstruction",
  "target": "0x00d38840"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00d38840",
  "package": null,
  "subsystem": "Simulator",
  "va": "0x00d38840"
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
  "content_sha256": "82e9e391470ea513006896ee31d2ecc459ccb285f49c973d8e7cc74eede14e85",
  "live_attempts": [],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `present`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json

undefined4 FUN_00d38840(void)

{
  return App__sCreatureModeStrategy;
}


```

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "none asserted. Byte-identical under __cdecl, __stdcall, __thiscall and __fastcall: the body names no memory operand relative to ESP or to any register, so it has 0 ordinary stack arguments, and its bare RET pops nothing. The derived ABI record lists all four as candidates and abstains ('no_discriminator: no stack-argument read and no positive receiver evidence'). The entry is declared with no convention macro at all.",
  "ordinary_stack_argument_slots": 0,
  "ordinary_stack_arguments": [],
  "receiver": "none. Opcode 0xa1 takes a 32-bit absolute address as its only operand, with no ModRM byte and no base register. The derived record agrees: receiver.present false, distinct_offsets 0, register null, bounds_only true.",
  "ret_form": "RET (0x00d38845, byte 0xc3, no imm16)",
  "return_register": "EAX",
  "return_semantics": "the 32-bit word STORED at the absolute address 0x0169e294, copied bit for bit into EAX and re-typed as a pointer; no arithmetic, no masking, no sign extension, no comparison and no branch.",
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
      "va": "0x00b279e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b33130"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b5ba30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b5d540"
    },
    {
      "name": "simulator_strategy_transition_00b5dbb0",
      "reconstructed": true,
      "va": "0x00b5dbb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b5e9a0"
    },
    {
      "name": "simulator_strategy_transition_00b5f040",
      "reconstructed": true,
      "va": "0x00b5f040"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b60d80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba1590"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c03440"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c03d60"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c07480"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c13c60"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c6a030"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d20970"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d213b0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00b27c32",
      "direction": "in",
    
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
      "va": "0x00b279e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b33130"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b5ba30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b5d540"
    },
    {
      "name": "simulator_strategy_transition_00b5dbb0",
      "reconstructed": true,
      "va": "0x00b5dbb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b5e9a0"
    },
    {
      "name": "simulator_strategy_transition_00b5f040",
      "reconstructed": true,
      "va": "0x00b5f040"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b60d80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba1590"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c03440"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c03d60"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c07480"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c13c60"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c6a030"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d20970"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d213b0"
    },
    {
      "name": null,
      "reconstructed": false,
  
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
    "What TYPE the slot's pointee is. The evidence establishes that it is an object pointer - one writer publishes `this`, and callers use the result as a receiver and index through it - but not its class. The slot's Ghidra label is App::sCreatureModeStrategy while the callee names a TYPE App::cCreatureModeStrategy, and this binary has no MSVC RTTI, so nothing machine-derived ties the two together. Promoting cCreatureModeStrategy to the C type needs RTTI, a vtable-shape match, or an SDK-proven static-member declaration.",
    "Whether 0x00d3b9b0 is the ONLY writer across the whole program. The pinned sidecar and the live database each record one write row for the slot; neither covers unanalysed or dynamically-reached code.",
    "Whether all 39 recorded callers use the result the same way. Four were sampled (0x00d4c5e0, 0x00d395a4, 0x00d2b6e0, 0x00d2c280); the other 35 were not, so 'every caller treats it as a receiver' is not claimed.",
    "Whether the absolute slot address can ever be modelled as a real dereference rather than a stood-up object. That needs the original image mapped, which is outside what this package does.",
    "Whether the slot is ever null in the running process, and therefore whether any caller has a latent null dereference. The runtime axis is GATED and unattempted, so nothing here answers it."
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
