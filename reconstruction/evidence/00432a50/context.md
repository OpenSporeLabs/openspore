# Reconstruction context 0x00432a50

- Status: `partial`
- Content SHA-256: `82dc137869958a28826d49a207a7333336e5059569269af4dd686724713e1b47`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00432a50",
  "phase": "reconstruction",
  "target": "0x00432a50"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "Wave6ReferenceCounted",
  "name": "Reference",
  "package": "PKG-WAVE6-CONTAINERS-MEMORY",
  "subsystem": "Core.Memory",
  "va": "0x00432a50"
}
```

## 03_current_status

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "blocked": false,
  "reconstructed": true,
  "runtime_gated": true,
  "runtime_validated": 0,
  "status": "reconstructed"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "b4ae9b77e5d6d01418e9afe7494810c908ef45ca88cf1536954c4996f0617e15",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00432a50 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "__thiscall observed",
  "receiver_register": "ECX",
  "return_register": "EAX",
  "return_type": "std::uint32_t",
  "stack_arguments": [],
  "stack_cleanup_bytes": 0,
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
      "name": null,
      "reconstructed": false,
      "va": "0x00404660"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0040f4a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0040f820"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0040fc00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005598b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0057a710"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0057f6c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005a5960"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005a9200"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005dfbb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006145d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0061b9a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00628230"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00628340"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00633560"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00640ee0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00404c38",
      "direction": "in",
      "other": "0x00404660",
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
  "types": [
    "Wave6ReferenceCounted",
    "std::uint32_t"
  ],
  "vtables": [
    "vtable:0x013eb90c",
    "vtable:0x013ebca4",
    "vtable:0x013eff40",
    "vtable:0x013f3d44",
    "vtable:0x013f3d84",
    "vtable:0x013fc06c",
    "vtable:0x013fe50c",
    "vtable:0x013ff508",
    "vtable:0x0140944c",
    "vtable:0x014095cc",
    "vtable:0x01409bec",
    "vtable:0x0140a278"
  ]
}
```

## 09_state_event_relationships

- State: `present`
- Provenance: `knowledgegraph/research/semantic-decomp.json, reconstruction/knowledge/index.json`

```json
{
  "runtime": {
    "blocking_reason": null,
    "gates": [
      "gate-reference-count-concurrency-and-lifetime"
    ],
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
      "va": "0x00404660"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0040f4a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0040f820"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0040fc00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005598b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0057a710"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0057f6c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005a5960"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005a9200"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005dfbb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006145d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0061b9a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00628230"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00628340"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00633560"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00640ee0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006af260"
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
      "same_package",
      "same_subsystem"
    ],
    "package": "PKG-WAVE6-CONTAINERS-MEMORY",
    "score": 14,
    "symbol": "wave6_fixed_pool_allocator_alloc_00926100",
    "va": "0x00926100"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem"
    ],
    "package": "PKG-WAVE6-CONTAINERS-MEMORY",
    "score": 14,
    "symbol": "wave6_fixed_pool_allocator_free_00926140",
    "va": "0x00926140"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x014186c4"
    ],
    "package": "PKG-UTFWIN-CORE-WAVE6",
    "score": 4,
    "symbol": "re_00575ea0",
    "va": "0x00575ea0"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x01409bec,vtable:0x014186c4"
    ],
    "package": "PKG-16-SPOREPEDIA-ONLINE",
    "score": 4,
    "symbol": "Sporepedia_cSPAssetDataOTDB_HasName_raw_00641770",
    "va": "0x00641770"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x0140e09c"
    ],
    "package": "pkg-vft-slot-006e64f0",
    "score": 4,
    "symbol": "re_006e64f0",
    "va": "0x006e64f0"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x013ff508"
    ],
    "package": "PKG-UTFWIN-CORE-WAVE6",
    "score": 4,
    "symbol": "re_00951230",
    "va": "0x00951230"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x01452b00,vtable:0x0145c0b4"
    ],
    "package": "pkg-sporepedia-nop-slot",
    "score": 4,
    "symbol": "sporepedia_nop_slot_FUN_00c2e4e0",
    "va": "0x00c2e4e0"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-UTFWIN-CORE-WAVE6",
    "score": 3,
    
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/wave6_containers_memory/containers_memory.cpp",
  "files": [
    "reconstruction/staging/wave6-containers-memory/containers_memory.cpp",
    "reconstruction/staging/wave6-containers-memory/containers_memory.hpp",
    "reconstruction/staging/wave6-containers-memory/containers_memory_model_test.cpp",
    "src/reconstruction/wave6_containers_memory/containers_memory.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/wave6-containers-memory/00432a50.json"
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
    "The concrete ResourceManager subtype and complete receiver layout are not established by the local body.",
    "The exact synchronization guarantees of the original atomic primitive and the lifetime policy for count zero are outside this function.",
    "The imported function name Reference is retained as the Ghidra label; the source-level class ownership remains opaque.",
    "concrete receiver owner",
    "count-zero lifetime policy",
    "gate-reference-count-concurrency-and-lifetime",
    "synchronization guarantees"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave6/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave6-containers-memory/00432a50.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave6-containers-memory/containers_memory.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave6-containers-memory/containers_memory.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave6-containers-memory/containers_memory_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/wave6_containers_memory/containers_memory.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/integrated/batch-2026-09-25-wave6/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/wave6-containers-memory/00432a50.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave6-containers-memory/containers_memory.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave6-containers-memory/containers_memory.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction
[TRUNCATED]
```
