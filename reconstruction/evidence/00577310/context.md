# Reconstruction context 0x00577310

- Status: `partial`
- Content SHA-256: `2c506d431fd150bd92b2d08b4e399ea37ccb0641efd4325f43346998ded187c8`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00577310",
  "phase": "reconstruction",
  "target": "0x00577310"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00577310",
  "package": null,
  "subsystem": "Editor",
  "va": "0x00577310"
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
  "content_sha256": "8d5d44cf78322155e3cd9f7d19dcec7d0b1f639a947634ba924703871a26869c",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00577310 failed: Decompilation did not complete. Reason: ",
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
  "return_type": "void",
  "saved_registers": [
    "EBX",
    "EDI",
    "ESI"
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
      "callsite": "0x005773f7",
      "direction": "out",
      "other": "0x0067de30",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0057749d",
      "direction": "out",
      "other": "0x006a12a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00577344",
      "direction": "out",
      "other": "0x007b07e0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00577452",
      "direction": "out",
      "other": "0x007b07e0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0057739d",
      "direction": "out",
      "other": "0x007b1e90",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005773bd",
      "direction": "out",
      "other": "0x007b1e90",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005773dd",
      "direction": "out",
      "other": "0x007b1e90",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005774cc",
      "direction": "out",
      "other": "0x007b1e90",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00577334",
      "direction": "out",
      "other": "0x00f473a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00577442",
      "direction": "out",
      "other": "0x00f473a0",
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
    "global:WARN"
  ],
  "types": [
    "void"
  ],
  "vtables": [
    "vtable:0x013f57f8"
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
      "callsite": "0x005773f7",
      "direction": "out",
      "other": "0x0067de30",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0057749d",
      "direction": "out",
      "other": "0x006a12a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00577344",
      "direction": "out",
      "other": "0x007b07e0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00577452",
      "direction": "out",
      "other": "0x007b07e0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0057739d",
      "direction": "out",
      "other": "0x007b1e90",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005773bd",
      "direction": "out",
      "other": "0x007b1e90",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005773dd",
      "direction": "out",
      "other": "0x007b1e90",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005774cc",
      "direction": "out",
      "other": "0x007b1e90",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00577334",
      "direction": "out",
      "other": "0x00f473a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00577442",
      "direction": "out",
      "other": "0x00f473a0",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 0,
  "fan_ou
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
      "shared_vtable:vtable:0x013f57f8",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w2-00586700",
    "score": 12,
    "symbol": "re_00586700",
    "va": "0x00586700"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013f57f8",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-005b2490",
    "score": 12,
    "symbol": "re_005b2490",
    "va": "0x005b2490"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013f57f8",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-005ba0d0",
    "score": 12,
    "symbol": "re_005ba0d0",
    "va": "0x005ba0d0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013f57f8"
    ],
    "package": "pkg-editor-child-007f30d0",
    "score": 10,
    "symbol": "FUN_007f30d0",
    "va": "0x007f30d0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "pkg-vft-preinc-0051e340",
    "score": 8,
    "symbol": "vft_preinc_0051e340",
    "va": "0x0051e340"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "subobject-forward-0051e380",
    "score": 8,
    "symbol": "subobject_forward_0051e380",
    "va": "0x0051e380"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-00a85070",
    "score": 8,
    "symbol": "re_00a85070",
    "va": "0x00a85070"
  },
  {
    "match_basis"
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-swarm-w2-00577310/w2_00577310.cpp",
    "reconstruction/staging/pkg-swarm-w2-00577310/w2_00577310_model_test.cpp",
    "reconstruction/staging/pkg-swarm-w2-00577310/w2_00577310_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-swarm-w2-00577310/00577310.json"
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
    "No direct caller of this body is named anywhere. Its only reference in the binary is the data word at 0x013f5840, so the argument at entry_ESP+0x4 and the 0xffffffff sentinel are fixed by the body's own comparison and by nothing that calls it. What the sentinel means to the caller -- \"no subject\", \"destroy\", \"reset\" -- is not established.",
    "The block at 0x00577406..0x00577413 is dead in this body and this record explains why, but WHY the compiler emitted it is not settled. 0x007b1e90 contains the identical idiom in the identical order, which makes it a template artefact rather than a mistake; whether some sibling in the table at 0x013f57f8 reaches it is not known, because none of those bodies was read.",
    "What the receiver's two members ARE is not established. 0x308 is guarded for null and carries three registrations; 0x30c is unguarded and carries one, only on a yes answer. Nothing read here says what either points at, and the record is bounds_only so no member may be named. Whether they are the same kind of object that the factory happens to return, and whether the +0x308 guard is a deliberate one-shot initialisation or an accident of a template, is not settled.",
    "What the record's middle word, 0x510a95b, is for. It is written on all four registrations and 0x007b1e90 never reads it, so it is consumed by something further downstream (0x007b1e90's own follow-up call at 0x007b1f11 to 0x007b1de0 receives the same record pointer and is the obvious candidate) that was not read here. The model treats it as
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-swarm-w2-00577310/00577310.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w2-00577310/w2_00577310.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w2-00577310/w2_00577310_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w2-00577310/w2_00577310_types.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-swarm-w2-00577310/00577310.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w2-00577310/w2_00577310.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w2-00577310/w2_00577310_model_test.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w2-00577310/w2_00577310_types.hpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.json"
[TRUNCATED]
```
