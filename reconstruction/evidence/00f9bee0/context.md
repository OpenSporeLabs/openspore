# Reconstruction context 0x00f9bee0

- Status: `partial`
- Content SHA-256: `b76965a8f09b274b0c1afd058279babc7946bd4816c5725e123e04152966f8ba`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00f9bee0",
  "phase": "reconstruction",
  "target": "0x00f9bee0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00f9bee0",
  "package": null,
  "subsystem": "Sporepedia",
  "va": "0x00f9bee0"
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
  "content_sha256": "891affcf2e7e48fa73ef13d6344277b6547221a56143bfee164a50d12382fe91",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00f9bee0 failed: Decompilation did not complete. Reason: ",
      "mode": "LIVE",
      "status": "unavailable"
    }
  ],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `missing`
- Provenance: ``

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_this": true,
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": 1,
  "receiver_register": "ECX",
  "ret_form": "RET 0x4",
  "return_register": "EAX",
  "saved_registers": [
    "EBX",
    "ESI",
    "EDI"
  ],
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "callee",
  "termination": "RET 0x4"
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [],
  "callers": [],
  "edge_rows": [
    {
      "callsite": "0x00f9bf4e",
      "direction": "out",
      "other": "0x0067dd80",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f9bf25",
      "direction": "out",
      "other": "0x0067ddd0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f9bf99",
      "direction": "out",
      "other": "0x00777ae0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f9bfa7",
      "direction": "out",
      "other": "0x00777ae0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f9bfb5",
      "direction": "out",
      "other": "0x00777ae0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f9bfc3",
      "direction": "out",
      "other": "0x00777ae0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f9bfd1",
      "direction": "out",
      "other": "0x00777ae0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f9bfdf",
      "direction": "out",
      "other": "0x00777ae0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f9bff0",
      "direction": "out",
      "other": "0x00777ae0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f9bffe",
      "direction": "out",
      "other": "0x00777ae0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f9bf10",
      "direction": "out",
      "other": "0x00f96c60",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [
    "global:WARN"
  ],
  "types": [
    "void"
  ],
  "vtables": [
    "vtable:0x01490be8"
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
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00f9bf4e",
      "direction": "out",
      "other": "0x0067dd80",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f9bf25",
      "direction": "out",
      "other": "0x0067ddd0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f9bf99",
      "direction": "out",
      "other": "0x00777ae0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f9bfa7",
      "direction": "out",
      "other": "0x00777ae0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f9bfb5",
      "direction": "out",
      "other": "0x00777ae0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f9bfc3",
      "direction": "out",
      "other": "0x00777ae0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f9bfd1",
      "direction": "out",
      "other": "0x00777ae0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f9bfdf",
      "direction": "out",
      "other": "0x00777ae0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f9bff0",
      "direction": "out",
      "other": "0x00777ae0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f9bffe",
      "direction": "out",
      "other": "0x00777ae0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f9bf10",
      "direction": "out",
      "other": "0x
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
      "shared_vtable:vtable:0x01490be8",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w2-00f999e0",
    "score": 12,
    "symbol": "re_00f999e0",
    "va": "0x00f999e0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01490be8",
      "same_calling_convention"
    ],
    "package": "pkg-fa0d50-atomic-inc",
    "score": 12,
    "symbol": "FUN_00fa0d50",
    "va": "0x00fa0d50"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01490be8",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-00fa5580",
    "score": 12,
    "symbol": "re_00fa5580",
    "va": "0x00fa5580"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01490be8",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-00fa6ec0",
    "score": 12,
    "symbol": "re_00fa6ec0",
    "va": "0x00fa6ec0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01490be8",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-00fa73c0",
    "score": 12,
    "symbol": "sw1_snap_and_dispatch_00fa73c0",
    "va": "0x00fa73c0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01490be8",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-0104c110",
    "score": 12,
    "symbol": "re_0104c110",
    "va": "0x0104c110"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-005
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-swarm-w2-00f9bee0/sw2_00f9bee0.cpp",
    "reconstruction/staging/pkg-swarm-w2-00f9bee0/sw2_00f9bee0_model_test.cpp",
    "reconstruction/staging/pkg-swarm-w2-00f9bee0/sw2_00f9bee0_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-swarm-w2-00f9bee0/00f9bee0.json"
  ]
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
    "DUPLICATE OWNERSHIP is not a risk on this VA at the time of writing: reconstruction/metadata carries no sidecar for 0x00f9bee0 other than this one, and reconstruction/evidence/00f9bee0/context.json lists no prior attempt. If a later package claims the same VA, note that reconstruction_knowledge.extract_metadata merges source_files per VA and sorts them, and validate._source() takes the first existing staging path, so two packages for one VA silently decide which source the validator judges. That is a property of the index and the integrator's call, not this worker's.",
    "GLOBALS is a WARN and it is a real evidence ceiling, not a defect. The xref export carries no data-reference edge type for this target (dependencies.data_reference_count is 0 and the pack's `globals` category is unavailable), so there is no second machine side to corroborate the one data address against, and validate's arm that reports agreement still WARNs because read/write mode needs per-access evidence. The mode WAS established independently, from GhidraMCP /get_xrefs_to, and is recorded under evidence.xref_modes_for_the_one_global; the check cannot read that source. Reported, not chased.",
    "RETURN SEMANTICS is a WARN and the disagreement is recorded rather than papered over. See validation.return_semantics_decision. No typedef named after the machine phrase was created to win the string comparison, and the sidecar states plainly which of the two honest options was taken and why.",
    "What the .data word at 0x016c9e68 is, beyond the read-the
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-swarm-w2-00f9bee0/00f9bee0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w2-00f9bee0/sw2_00f9bee0.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w2-00f9bee0/sw2_00f9bee0_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w2-00f9bee0/sw2_00f9bee0_types.hpp', 'source_class': 'committed_artifact'}`

```json
{
  "provenance": [
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
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg-swarm-w2-00f9bee0/00f9bee0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w2-00f9bee0/sw2_00f9bee0.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w2-00f9bee0/sw2_00f9bee0_model_test.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w2-00f9bee0/sw2_00f9bee0_types.hpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.js
[TRUNCATED]
```
