# Reconstruction context 0x00641e10

- Status: `partial`
- Content SHA-256: `46b48cc434316966202645325c15164e3b8e26c684e18b4d0823cd1904bb46f4`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00641e10",
  "phase": "reconstruction",
  "target": "0x00641e10"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00641e10",
  "package": "pkg-sporepedia-slot-release",
  "subsystem": "Sporepedia",
  "va": "0x00641e10"
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
  "content_sha256": "8ed82f9430e6582eb58f0e75e6c526eb4173a607d37f7817e87c1955c66d362a",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00641e10 failed: Decompilation did not complete. Reason: ",
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
  "return_type": "unclassified_in_EAX",
  "saved_registers": [
    "EDI",
    "ESI"
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
  "callers": [
    {
      "name": "sporepedia_owned_slot_notify_FUN_00ec3bc0",
      "reconstructed": true,
      "va": "0x00ec3bc0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00ec3bc3",
      "direction": "in",
      "other": "0x00ec3bc0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00641e30",
      "direction": "out",
      "other": "0x005bf0e0",
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
    "global:none: the complete 19-instruction listing names no data-segment address"
  ],
  "types": [
    "unclassified_in_EAX"
  ],
  "vtables": [
    "vtable:0x013ff6ac",
    "vtable:0x01462764",
    "vtable:0x014627bc",
    "vtable:0x0147ca30",
    "vtable:0x0147ca70",
    "vtable:0x0147caf8",
    "vtable:0x0147cbbc",
    "vtable:0x0147cc14"
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
      "name": "sporepedia_owned_slot_notify_FUN_00ec3bc0",
      "reconstructed": true,
      "va": "0x00ec3bc0"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00ec3bc3",
      "direction": "in",
      "other": "0x00ec3bc0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00641e30",
      "direction": "out",
      "other": "0x005bf0e0",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 1,
  "fan_out": 0,
  "manifest_callees": [],
  "manifest_callers": [],
  "nearby_reconstructed": [
    "0x00ec3bc0"
  ],
  "scc": {
    "id": "scc-0165",
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
      "shared_types:unclassified_in_EAX",
      "same_calling_convention",
      "direct_xref_neighbor"
    ],
    "package": "pkg-sporepedia-owned-slot-notify",
    "score": 14,
    "symbol": "sporepedia_owned_slot_notify_FUN_00ec3bc0",
    "va": "0x00ec3bc0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013ff6ac,vtable:0x0147ca30",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-005c0dd0",
    "score": 12,
    "symbol": "re_005c0dd0",
    "va": "0x005c0dd0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01462764,vtable:0x0147ca30",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-006413d0",
    "score": 12,
    "symbol": "re_006413d0",
    "va": "0x006413d0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01462764,vtable:0x0147ca30",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-00641410",
    "score": 12,
    "symbol": "re_00641410",
    "va": "0x00641410"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01462764,vtable:0x0147cbbc",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-00641780",
    "score": 12,
    "symbol": "re_00641780",
    "va": "0x00641780"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013ff6ac,vtable:0x01462764",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-006417d0",
    "score": 12,
    "symbol": "re_006417d0",
    "v
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-sporepedia-slot-release/sporepedia_slot_release.cpp",
    "reconstruction/staging/pkg-sporepedia-slot-release/sporepedia_slot_release.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-sporepedia-slot-release/00641e10.json"
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
    "Does the slot's return value or side effect matter to this body? EAX is overwritten by the direct call at 0x00641e30, so the body itself discards whatever the slot leaves there.",
    "Is 0x00641e10 the only implementation of this shape, or an override of a shared base helper? No RTTI and no vtable pass exist for this binary, and the record's association is transitive.",
    "Is the dispatch word at [pointee+0x0] a class vtable, and which class and vtable is it? The record associates eight vtables with this target transitively, which does not identify the one the body reads.",
    "The machine-derived receiver record is bounds_only and enumerates 0x20 and nothing else, so it states where the body was seen reaching and is not an enumeration of the receiver's words: it corroborates the 0x20 displacement and cannot refute any other receiver word. Displacement 0x4 is formed at 0x00641e2c but never dereferenced, so its absence from the record is consistent with a dereference-based observation rather than a disagreement -- but the record's own observation criteria are not documented, so it is not established here that a bounds_only record would have listed it.",
    "What contract does 0x005bf0e0 implement? It is a shared two-pointer helper that itself dispatches to a service slot at displacement 0x2c, but this body does not identify the service it reaches.",
    "What does the slot at displacement 4 of the pointee's dispatch word resolve to? No record for this target names the table, the slot or the callee, so the one indirec
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-sporepedia-slot-release/00641e10.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-sporepedia-slot-release/sporepedia_slot_release.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-sporepedia-slot-release/sporepedia_slot_release.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-sporepedia-slot-release/00641e10.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-sporepedia-slot-release/sporepedia_slot_release.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-sporepedia-slot-release/sporepedia_slot_release.hpp",
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
    
[TRUNCATED]
```
