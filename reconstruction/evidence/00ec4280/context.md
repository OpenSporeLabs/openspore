# Reconstruction context 0x00ec4280

- Status: `partial`
- Content SHA-256: `8c984be35aed3c597c71b1eadced0d8367015e2a06cb03d004f8acc30b337e08`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00ec4280",
  "phase": "reconstruction",
  "target": "0x00ec4280"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00ec4280",
  "package": null,
  "subsystem": "Sporepedia",
  "va": "0x00ec4280"
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
  "content_sha256": "e5598c850d00187ad46fe7b5bcbed4f0ff710b7550e7798ca95cb5ce0e261fd4",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00ec4280 failed: Decompilation did not complete. Reason: ",
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
  "callees": [
    {
      "name": "sporepedia_asset_destroy_00642190",
      "reconstructed": true,
      "va": "0x00642190"
    }
  ],
  "callers": [],
  "edge_rows": [
    {
      "callsite": "0x00ec4297",
      "direction": "out",
      "other": "0x00642190",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00ec42a4",
      "direction": "out",
      "other": "0x00f47380",
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
  "globals": [],
  "types": [
    "SW1_00EC4280_CDECL",
    "SW1_00EC4280_THISCALL",
    "SporepediaOnlineAsset",
    "SporepediaOnlineAsset* (the receiver)"
  ],
  "vtables": [
    "vtable:0x00ec4280",
    "vtable:0x01489090"
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
      "name": "sporepedia_asset_destroy_00642190",
      "reconstructed": true,
      "va": "0x00642190"
    }
  ],
  "callees_truncated": false,
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00ec4297",
      "direction": "out",
      "other": "0x00642190",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00ec42a4",
      "direction": "out",
      "other": "0x00f47380",
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
    "0x00642190"
  ],
  "scc": {
    "id": "scc-0566",
    "size": 1
  },
  "vtable_reference_count": 3
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
      "shared_vtable:vtable:0x01489090",
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
      "shared_vtable:vtable:0x01489090",
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
      "shared_vtable:vtable:0x01489090",
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
      "shared_vtable:vtable:0x01489090",
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
      "shared_vtable:vtable:0x01489090",
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
      "shared_vtable:vtable:0x01489090",
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
      "shared_vtable:vtable:0x01489090",
      "sam
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-swarm-w1-00ec4280/sw1_00ec4280.cpp",
    "reconstruction/staging/pkg-swarm-w1-00ec4280/sw1_00ec4280_model_test.cpp",
    "reconstruction/staging/pkg-swarm-w1-00ec4280/sw1_00ec4280_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-swarm-w1-00ec4280/00ec4280.json"
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
    "The interior of 0x00642190 and of the 0x006412A0 chain. The five null-guarded indirect handle releases, the inline-vector comparison and the tail transfer are opaque seams here; this package asserts only the three vptr words, the terminator and the zero-argument convention, all of which were re-read from the image.",
    "What the class actually is. No MSVC RTTI survives in this binary (the repo's own AGENTS.md says so and the record's evidence_note repeats it), and no record names the class. The type name SporepediaOnlineAsset is for readability and is not a claim. The triage cluster says 'sporepedia-online' and the eight analogue records share this vftable, so the neighbourhood is Sporepedia, but the specific class and its bases are unknown.",
    "What the other seven bits of the delete-flag byte mean, and who sets them. Only bit 0 is examined here. An MSVC deleting destructor normally encodes more than one condition in that byte, and this body is the only place in this package that can see it, so the question is genuinely open from this VA alone.",
    "Whether the return value is ever consumed. No caller is recorded for this VA (Ghidra lists callers [] and the only xrefs are the vtable word and the two thunks), so the returning destructor's contract -- whether a caller uses EAX, or whether this is a hand-rolled destructor rather than a compiler-emitted one -- cannot be settled from the image at this address.",
    "Whether the three bytes at entry_ESP+0x5..0x7 of the argument slot are ever non-zero in real callers. 
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-swarm-w1-00ec4280/00ec4280.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w1-00ec4280/sw1_00ec4280.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w1-00ec4280/sw1_00ec4280_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w1-00ec4280/sw1_00ec4280_types.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-swarm-w1-00ec4280/00ec4280.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w1-00ec4280/sw1_00ec4280.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w1-00ec4280/sw1_00ec4280_model_test.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w1-00ec4280/sw1_00ec4280_types.hpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.js
[TRUNCATED]
```
