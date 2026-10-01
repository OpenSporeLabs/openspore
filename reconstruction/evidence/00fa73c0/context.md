# Reconstruction context 0x00fa73c0

- Status: `partial`
- Content SHA-256: `c7d388df96c337651345c996132eac4b4edf161984f0a166462ff1e77bb6d07a`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00fa73c0",
  "phase": "reconstruction",
  "target": "0x00fa73c0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00fa73c0",
  "package": "pkg-swarm-w1-00fa73c0",
  "subsystem": "Sporepedia",
  "va": "0x00fa73c0"
}
```

## 03_current_status

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "blocked": false,
  "reconstructed": true,
  "runtime_gated": false,
  "runtime_validated": 0,
  "status": "reconstructed"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "a192d5012ba262232cd756dda90fd6bb9a494179d71cb9828d3f77eff1a0ea34",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00fa73c0 failed: Decompilation did not complete. Reason: ",
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
  "ordinary_stack_argument_slots": 0,
  "receiver_register": "ECX",
  "ret_form": "RET",
  "return_register": "EAX",
  "return_type": "void",
  "saved_registers": [
    "EBX",
    "ESI",
    "EDI"
  ],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "RET"
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
      "callsite": "0x00fa73d4",
      "direction": "out",
      "other": "0x00f9f770",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00fa7430",
      "direction": "out",
      "other": "0x00fbaf10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00fa743d",
      "direction": "out",
      "other": "0x00fbaf50",
      "reference_type": "direct-call"
    }
  ],
  "external_callees": []
}
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [
    "global:PASS"
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
      "callsite": "0x00fa73d4",
      "direction": "out",
      "other": "0x00f9f770",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00fa7430",
      "direction": "out",
      "other": "0x00fbaf10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00fa743d",
      "direction": "out",
      "other": "0x00fbaf50",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 0,
  "fan_out": 0,
  "manifest_callees": [],
  "manifest_callers": [],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0581",
    "size": 1
  },
  "vtable_reference_count": 0
}
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
    "package": "pkg-swarm-w1-005c0dd0",
    "score": 8,
    "symbol": "re_005c0dd0",
    "va": "0x005c0dd0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-006413d0",
    "score": 8,
    "symbol": "re_006413d0",
    "va"
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-swarm-w1-00fa73c0/sw1_00fa73c0.cpp",
    "reconstruction/staging/pkg-swarm-w1-00fa73c0/sw1_00fa73c0_model_test.cpp",
    "reconstruction/staging/pkg-swarm-w1-00fa73c0/sw1_00fa73c0_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-swarm-w1-00fa73c0/00fa73c0.json"
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
    "Are the words at receiver+0x798 and +0x79c pointers, indices or counts? This body only ever forms their difference and hands them to 0x00f9f770 as opaque words, and 0x00f9f770 never dereferences them on the path this caller forces. 0xac appears both as that callee's stride and as this body's multiplier, which is suggestive of a 172-byte element size, but nothing here fixes what the words point AT. The model deliberately plants non-dereferenceable values so that any reconstruction which invents a dereference fails its own test.",
    "Is 0x00f9f770's degenerate call dead source, a debug leftover, or a call that was meant to be non-degenerate? This caller provably passes the same word as both range ends, so the callee's loop and its 0x00f9f620 call never run. Whether that is a bug, an intentional no-op, or the residue of a refactor is not determinable from the bytes, and the model reproduces the call exactly as the listing has it rather than deleting it.",
    "No record establishes who calls this body. ghidra_function.xref_count is 1 and that single xref is the vtable slot's storage at 0x01490c58; callers_dependencies is unavailable and dependencies.callers is empty. So the return value's fate and the expected receiver state are both unconstrained by anything in this repository, and the runtime gate below is written without assuming either.",
    "The three records disagree about the return type, and the disagreement is not fully resolvable from the bytes. abi.return_semantics is 'unclassified_in_EAX', abi_derived.return.
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-swarm-w1-00fa73c0/00fa73c0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w1-00fa73c0/sw1_00fa73c0.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w1-00fa73c0/sw1_00fa73c0_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w1-00fa73c0/sw1_00fa73c0_types.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-swarm-w1-00fa73c0/00fa73c0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w1-00fa73c0/sw1_00fa73c0.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w1-00fa73c0/sw1_00fa73c0_model_test.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w1-00fa73c0/sw1_00fa73c0_types.hpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.js
[TRUNCATED]
```
