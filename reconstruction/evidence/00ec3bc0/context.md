# Reconstruction context 0x00ec3bc0

- Status: `partial`
- Content SHA-256: `21fa3907f1f80f4738510ca84eec09b481e32a4adbfc9607f2aacfc6fe70bf51`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00ec3bc0",
  "phase": "reconstruction",
  "target": "0x00ec3bc0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00ec3bc0",
  "package": "pkg-sporepedia-owned-slot-notify",
  "subsystem": "Sporepedia",
  "va": "0x00ec3bc0"
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
  "content_sha256": "e90c24836ac398e1c336b4cf492fb5145c561fd084d61c6dfe7b749da1295733",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00ec3bc0 failed: Decompilation did not complete. Reason: ",
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
  "callees": [
    {
      "name": "sporepedia_dispatch_owned_slot_FUN_00641e10",
      "reconstructed": true,
      "va": "0x00641e10"
    }
  ],
  "callers": [],
  "edge_rows": [
    {
      "callsite": "0x00ec3bc3",
      "direction": "out",
      "other": "0x00641e10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00ec3bd4",
      "direction": "out",
      "other": "0x00eec760",
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
    "global:PASS",
    "global:none: the complete 13-instruction listing names no data-segment address"
  ],
  "types": [
    "unclassified_in_EAX"
  ],
  "vtables": [
    "vtable:0x014890f4"
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
  "callees": [
    {
      "name": "sporepedia_dispatch_owned_slot_FUN_00641e10",
      "reconstructed": true,
      "va": "0x00641e10"
    }
  ],
  "callees_truncated": false,
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00ec3bc3",
      "direction": "out",
      "other": "0x00641e10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00ec3bd4",
      "direction": "out",
      "other": "0x00eec760",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 0,
  "fan_out": 1,
  "manifest_callees": [],
  "manifest_callers": [],
  "nearby_reconstructed": [
    "0x00641e10"
  ],
  "scc": {
    "id": "scc-0564",
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
    "package": "pkg-sporepedia-slot-release",
    "score": 14,
    "symbol": "sporepedia_dispatch_owned_slot_FUN_00641e10",
    "va": "0x00641e10"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x014890f4",
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
      "shared_vtable:vtable:0x014890f4",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-006417d0",
    "score": 12,
    "symbol": "re_006417d0",
    "va": "0x006417d0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x014890f4",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-00641fa0",
    "score": 12,
    "symbol": "sporepedia_predicate_00641fa0",
    "va": "0x00641fa0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x014890f4",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-00641fd0",
    "score": 12,
    "symbol": "sporepedia_cached_handle_00641fd0",
    "va": "0x00641fd0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x014890f4",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w2-00642700",
    "score": 12,
    "symbol": "sporepedia_append_five_lookups_00642700",
    "va": "0x00642700"
  },
  {
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-sporepedia-owned-slot-notify/sporepedia_owned_slot_notify.cpp",
    "reconstruction/staging/pkg-sporepedia-owned-slot-notify/sporepedia_owned_slot_notify_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-sporepedia-owned-slot-notify/00ec3bc0.json"
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
    "Is the branch at 0x00ec3bcd ever taken as not-taken? The re-verified sibling record reconstruction/metadata/pkg-sporepedia-slot-release/00641e10.json writes zero into the same displacement 0x20 of its receiver at 0x00641e1e, before its own dispatch. If both bodies share a receiver, the word this body tests at 0x00ec3bcb is already zero and the block at 0x00ec3bcf..0x00ec3bd9 is dead on the non-null entry path. This is a cross-target inference, not a fact about this body: no record for 0x00ec3bc0 shows the two share a receiver (its own fan_in is 0, callers empty), and 0x00641e10 closed as WARN, so its candidate is unconfirmed. Settling it needs a trace that captures the value at receiver+0x20 both before and after 0x00ec3bc3.",
    "Is the return word meaningful? The record classifies it as unclassified_in_EAX with register_class aggregate_unknown and void_possible false, and the live decompilation of this body ends in a bare return, so the model neither names nor interprets it.",
    "What do the three hashed ids 0x1f0372ed, 0xd6a4ff43 and 0xb55857d7 that 0x00eec760 passes to its slot at displacement 0x24 mean, and why does the callee read a short at offset 0x12 of the first argument? None of that is visible in this body.",
    "What is the 0x80 area that 0x00eec760 writes three words into? The body only forms the address; the live decompilation of that callee stores 0xffffffff and two words of 0x7fffffff there under its own guards, which suggests an initialised bounds or range block, but no record for this target names 
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-sporepedia-owned-slot-notify/00ec3bc0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-sporepedia-owned-slot-notify/sporepedia_owned_slot_notify.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-sporepedia-owned-slot-notify/sporepedia_owned_slot_notify_types.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-sporepedia-owned-slot-notify/00ec3bc0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-sporepedia-owned-slot-notify/sporepedia_owned_slot_notify.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-sporepedia-owned-slot-notify/sporepedia_owned_slot_notify_types.hpp",
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
    "CONST
[TRUNCATED]
```
