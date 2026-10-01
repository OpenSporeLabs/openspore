# Reconstruction context 0x00e31100

- Status: `partial`
- Content SHA-256: `991475da2a94306baaab685a82cdb4bb8a0a9001a5290b27d9b5a2bb0e0ec923`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00e31100",
  "phase": "reconstruction",
  "target": "0x00e31100"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00e31100",
  "package": null,
  "subsystem": "Sporepedia",
  "va": "0x00e31100"
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
  "content_sha256": "44b88b09110fce16863ccd9b9db3dd232b6310417cb1eb6496b95d4fb7e4db83",
  "live_attempts": [],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `present`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json

undefined4 FUN_00e31100(void)

{
  return 0;
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
  "receiver": "ECX, never read: the complete two-instruction body contains no reference to ECX in any form",
  "ret_form": "RET (0x00e31102 `c3`), no immediate",
  "return_register": "EAX",
  "return_semantics": "EAX holds zero at the RET: XOR EAX,EAX at 0x00e31100 is the last and only write to EAX and nothing overwrites it before the terminator. The operand is the FULL 32-bit register, so all four bytes are written and none of them is indeterminate. The derived ABI record reports return_register EAX, return_semantics integral_in_EAX and register_class integral.",
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
      "va": "0x00a0f080"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b46d10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b4b4a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b4c270"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b68720"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b687d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b69890"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b6c280"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b6c710"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b6d1d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b6d3c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b6dbd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e4aa60"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e52ae0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e58730"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e59e80"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00a0f2c0",
      "direction": "in",
      "other": "0x00a0f080",
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
  "types": [],
  "vtables": [
    "vtable:0x013f6364",
    "vtable:0x013f63fc",
    "vtable:0x013f6ae0",
    "vtable:0x013f6bbc",
    "vtable:0x013f718c",
    "vtable:0x013f795c",
    "vtable:0x013f79f4",
    "vtable:0x013f7b54",
    "vtable:0x013f7bfc",
    "vtable:0x013f7c90",
    "vtable:0x013f7cc0",
    "vtable:0x013f7f30"
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
      "va": "0x00a0f080"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b46d10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b4b4a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b4c270"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b68720"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b687d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b69890"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b6c280"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b6c710"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b6d1d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b6d3c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b6dbd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e4aa60"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e52ae0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e58730"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e59e80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e5e2c0"
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
      "shared_vtable:vtable:0x013f7cc0,vtable:0x013ff648"
    ],
    "package": "pkg-swarm-w1-005c0dd0",
    "score": 10,
    "symbol": "re_005c0dd0",
    "va": "0x005c0dd0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013ff648,vtable:0x01462764"
    ],
    "package": "pkg-swarm-w1-006413d0",
    "score": 10,
    "symbol": "re_006413d0",
    "va": "0x006413d0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013ff648,vtable:0x01462764"
    ],
    "package": "pkg-swarm-w1-00641410",
    "score": 10,
    "symbol": "re_00641410",
    "va": "0x00641410"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013ff648,vtable:0x01462764"
    ],
    "package": "pkg-swarm-w1-00641780",
    "score": 10,
    "symbol": "re_00641780",
    "va": "0x00641780"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013ff648,vtable:0x01462764"
    ],
    "package": "pkg-swarm-w1-006417d0",
    "score": 10,
    "symbol": "re_006417d0",
    "va": "0x006417d0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01462764,vtable:0x0147ca70"
    ],
    "package": "pkg-sporepedia-slot-release",
    "score": 10,
    "symbol": "sporepedia_dispatch_owned_slot_FUN_00641e10",
    "va": "0x00641e10"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013ff648,vtable:0x01462764"
    ],
    "package": "pkg-swarm-w1-00641fa0",
    "score": 10,
    "symbol": "sporep
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
    "What a zero return means to the owning class: an absent-value answer, an empty-collection count, a default capability report or a placeholder. All four produce the same three bytes.",
    "Whether any of the 41 callers reads the returned EAX, and if so how. Nothing in this entry's scope answers that and no caller was decompiled for this package.",
    "Whether the original source declared the return int, unsigned, an iterator typedef, or something else one byte wide with a wider machine form. Several spellings compile to 33 c0 c3.",
    "Which class, if any single one, owns this slot. There is no MSVC RTTI in this binary and 508 tables hold the address."
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'derived'}, {'mode': 'derived', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'derived'}, {'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/vftables.py@25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /decompile_function @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}`

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
      "mode": "derived",
      "ref": "tools/reconstruction_tooling/vftables.py@25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e",
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
  "required_categori
[TRUNCATED]
```
