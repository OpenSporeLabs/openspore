# Reconstruction context 0x00c6a960

- Status: `partial`
- Content SHA-256: `3abe8ccaab0e7bc0bd7c14693675ca3b0cf297f2b53a7cd9d2d23c384838e826`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00c6a960",
  "phase": "reconstruction",
  "target": "0x00c6a960"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00c6a960",
  "package": null,
  "subsystem": "Editor",
  "va": "0x00c6a960"
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
  "content_sha256": "f7e9e0cd3e725b2910ea3300e7dccfc2110f377c0de5b2d14bafdaf6677c2a3e",
  "live_attempts": [],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `present`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json

void __fastcall FUN_00c6a960(int param_1)

{
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 1;
  return;
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
  "receiver": "ECX, used as the base of the read at +0x8 and the write at +0x8, and of nothing else",
  "ret_form": "RET (0x00c6a967 `c3`), no immediate",
  "return_register": "EAX",
  "return_semantics": "EAX holds the post-increment value at the RET: INC EAX at 0x00c6a963 is the last write to EAX and the store at 0x00c6a964 goes through ECX, so the value survives to the terminator. This is a statement about machine state, not about the source-level signature.",
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
      "va": "0x005bfd40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00650190"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00658c70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0065dd30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0065e110"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0068af10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0068b5b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00714260"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0076dee0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00782660"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007bb670"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007bbf80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007bced0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007be430"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007bea00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007bedb0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x005bffac",
      "direction": "in",
      "other": "0x005bfd40",
      "reference_type": "computed-call"
    }
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [],
  "vtables": [
    "vtable:0x013f56a8",
    "vtable:0x013f57f8",
    "vtable:0x013f625c",
    "vtable:0x013f6364",
    "vtable:0x013f68c4",
    "vtable:0x013f6ae0",
    "vtable:0x013f6cec",
    "vtable:0x013f6d6c",
    "vtable:0x013f6de4",
    "vtable:0x013f6f14",
    "vtable:0x013f6fc0",
    "vtable:0x013f7b54"
  ]
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
      "va": "0x005bfd40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00650190"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00658c70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0065dd30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0065e110"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0068af10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0068b5b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00714260"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0076dee0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00782660"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007bb670"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007bbf80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007bced0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007be430"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007bea00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007bedb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007c1c10"
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
      "same_subsystem",
      "shared_vtable:vtable:0x0140da74,vtable:0x014123b4"
    ],
    "package": "pkg-vft-preinc-0051e340",
    "score": 10,
    "symbol": "vft_preinc_0051e340",
    "va": "0x0051e340"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x0140da74,vtable:0x014123b4"
    ],
    "package": "subobject-forward-0051e380",
    "score": 10,
    "symbol": "subobject_forward_0051e380",
    "va": "0x0051e380"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013f8be0,vtable:0x014123b4"
    ],
    "package": "pkg-w2-0052e650",
    "score": 10,
    "symbol": "reconstruct_0052e650",
    "va": "0x0052e650"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013f57f8"
    ],
    "package": "pkg-editor-w1-0057d6f0",
    "score": 10,
    "symbol": "re_0057d6f0",
    "va": "0x0057d6f0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013f57f8"
    ],
    "package": "pkg-swarm-w2-00586700",
    "score": 10,
    "symbol": "re_00586700",
    "va": "0x00586700"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013f57f8"
    ],
    "package": "pkg-swarm-w1-005b2490",
    "score": 10,
    "symbol": "re_005b2490",
    "va": "0x005b2490"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013f57f8"
    ],
    "package": "pkg-swarm-w1-005ba0d0",
    "score": 10,
    "symbol": "re_005ba0d0",
    "va": "0x005ba0d0"
  },
  {
    "match_basis": [
      "same_sub
[TRUNCATED]
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
    "What the 32-bit word at receiver+0x8 means. The retain/release reading rests on the partner body at 0x007b86e0, not on this entry's own instructions.",
    "Whether any caller can present a receiver whose +0x8 word is already at the top of the range, i.e. whether the observed wrap is reachable in practice.",
    "Whether the original source declared this entry void or returning the incremented value. Both compile to the same eight bytes.",
    "Which class owns the virtual slot. No MSVC RTTI in this binary, and the slot index varies per table (0..36 across 342 HIGH-confidence tables)."
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
