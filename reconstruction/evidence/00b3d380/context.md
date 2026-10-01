# Reconstruction context 0x00b3d380

- Status: `partial`
- Content SHA-256: `1b68b652ac2135b24a01ef1c6f73a5691ad04db9bb1062fa7c780ace2361caf0`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00b3d380",
  "phase": "reconstruction",
  "target": "0x00b3d380"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00b3d380",
  "package": null,
  "subsystem": "Simulator",
  "va": "0x00b3d380"
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
  "content_sha256": "646fbe16cfc222ec58a43759478bc1c9b8dd011da0bfbf87ab67eabb99bb269c",
  "live_attempts": [],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `present`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json

undefined4 FUN_00b3d380(void)

{
  return DAT_0167eb04;
}


```

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "UNNAMED BY DESIGN: 0 ordinary stack arguments, no register receiver, bare RET. The derived ABI record abstains (`no_discriminator: no stack-argument read and no positive receiver evidence`) and reports cdecl/stdcall/thiscall/fastcall as byte-identical, which is correct for a zero-parameter entry. This package therefore models it as a plain zero-parameter entry and does not pick one.",
  "ordinary_stack_argument_slots": 0,
  "ordinary_stack_arguments": [],
  "receiver": "none. ECX is unreadable by construction: 0x00b3d380 is `a1 <disp32>` (MOV EAX, moffs32), which has no ModRM byte and therefore no r/m and no register operand at all.",
  "ret_form": "RET (0x00b3d385, byte 0xc3, no imm16)",
  "return_note": "opaque 32-bit object pointer; the pointee class is UNKNOWN",
  "return_register": "EAX",
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
      "va": "0x00adf840"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae00d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae37c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae6240"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae9f50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aebe90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b19290"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b1dee0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b26af0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b26c90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b5cc80"
    },
    {
      "name": "simulator_strategy_transition_00b5f040",
      "reconstructed": true,
      "va": "0x00b5f040"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b71ee0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba5270"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba5650"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba57f0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00adf8ca",
      "direction": "in",
      "other": "0x00adf840",
      "ref
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "opaque 32-bit object pointer; the pointee class is UNKNOWN"
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
      "va": "0x00adf840"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae00d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae37c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae6240"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae9f50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aebe90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b19290"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b1dee0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b26af0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b26c90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b5cc80"
    },
    {
      "name": "simulator_strategy_transition_00b5f040",
      "reconstructed": true,
      "va": "0x00b5f040"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b71ee0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba5270"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba5650"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba57f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba58f3"
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
    "Are the 0x0167eb00 and 0x0167eb08 slots (accessors 0x00b3d370 and 0x00b3d390, immediate neighbours in the same table) related to this one? Neither is named.",
    "Does the pointer the entry returns need an AddRef, and if so by whom? The body has no room for a reference call, and no writer is known, so ownership is undetermined.",
    "Is the byte at pointee+0x48 a flags word with more defined bits than bit 0? Three callers test only bit 0.",
    "What class does the word at 0x0167eb04 point to? No SDK import, committed research note or sampled caller names it.",
    "Who publishes 0x0167eb04, and when relative to the 240 callsites that read it? No direct writer exists; indirect or bulk publication is unexcluded."
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
