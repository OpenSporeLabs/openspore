# Reconstruction context 0x00ec3be0

- Status: `partial`
- Content SHA-256: `11dc9229230db906457939ce5064ad460ae7e4f099f76527d5cd76bc9c530c7f`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00ec3be0",
  "phase": "reconstruction",
  "target": "0x00ec3be0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00ec3be0",
  "package": "pkg-swarm-w1-00ec3be0",
  "subsystem": "Sporepedia",
  "va": "0x00ec3be0"
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
  "content_sha256": "bcc8383bcf8c83b980d9d12f12245f2962c3ff322cbee4a2dbd9c399efde207d",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00ec3be0 failed: Decompilation did not complete. Reason: ",
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
  "return_note": "the machine ABI envelope (abi_derived.return) names EAX as the return register, classifies its register_class as aggregate_unknown and sets void_possible false, and evidence_returns therefore reports UNCLASSIFIED for this body rather than a void; the declared void here rests on the listing instead -- no path writes EAX immediately before a terminator for the purpose of returning it, and Ghidra's decompilation is `void __thiscall FUN_00ec3be0(int,uint *)` with five bare `return;` statements. What the machine does leave in EAX is incidental and path-dependent: the callee's return where no arm...",
  "return_register": "EAX",
  "return_type": "void",
  "saved_registers": [
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
      "callsite": "0x00ec3be9",
      "direction": "out",
      "other": "0x00642530",
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
  "callees": [],
  "callees_truncated": false,
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00ec3be9",
      "direction": "out",
      "other": "0x00642530",
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
    "id": "scc-0565",
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
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x014890f4",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-00a649a0",
    "score": 12,
    "symbol": "re_00a649a0",
    "va": "0x00a649a0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vt
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-swarm-w1-00ec3be0/sw1_00ec3be0.cpp",
    "reconstruction/staging/pkg-swarm-w1-00ec3be0/sw1_00ec3be0_model_test.cpp",
    "reconstruction/staging/pkg-swarm-w1-00ec3be0/sw1_00ec3be0_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-swarm-w1-00ec3be0/00ec3be0.json"
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
    "EVIDENCE COVERAGE is expected to stay WARN at 14 of 17 static categories. This pack reports availability unavailable/MISSING for callees_dependencies, callers_dependencies, contradictions, external_callees, globals, runtime and types, and validate derives the check purely from that field. Nothing in a source file or a sidecar can move it.",
    "RETURN SEMANTICS is expected to stay WARN and no source edit can move it. The machine ABI envelope names EAX, classifies it aggregate_unknown, sets void_possible false, and the body contains a CALL at 0x00ec3be9 -- which evidence_returns treats as defeating a width claim on its own. So the dimension reports UNCLASSIFIED, which never passes, whatever the reconstructed return type says. The declared void is the honest reading of the listing and the decompilation; it just cannot be corroborated by this pack's evidence.",
    "The ABI envelope's stack_arguments entry for entry_ESP+0x4 carries read: false while obs-0003 in the same envelope is a STACK_SLOT_READ at 0x00ec3be1 with resolved true and size 4. The bytes plainly read that slot (8B 74 24 08) and push it again at 0x00ec3be6, and the model follows the bytes. The two fields of one record disagree and I could not determine which the inference meant; it does not affect the reconstruction, only the record's self-consistency.",
    "What 0x00642530 does to the receiver when this body has already stored its flag. The two bodies are siblings over the same record and the same type hash, and the call precedes the flag write on every pa
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-swarm-w1-00ec3be0/00ec3be0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w1-00ec3be0/sw1_00ec3be0.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w1-00ec3be0/sw1_00ec3be0_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w1-00ec3be0/sw1_00ec3be0_types.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-swarm-w1-00ec3be0/00ec3be0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w1-00ec3be0/sw1_00ec3be0.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w1-00ec3be0/sw1_00ec3be0_model_test.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w1-00ec3be0/sw1_00ec3be0_types.hpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.js
[TRUNCATED]
```
