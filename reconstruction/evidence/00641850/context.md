# Reconstruction context 0x00641850

- Status: `partial`
- Content SHA-256: `d30d4388bc3e0d0a3986025d41dcabe5b63df32359f7a12fa2d36ff141e97b43`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00641850",
  "phase": "reconstruction",
  "target": "0x00641850"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "Sporepedia::cSPAssetDataOTDB::GetTags",
  "package": "PKG-SPOREPEDIA-ACCESSORS-WAVE6",
  "subsystem": "Sporepedia.AssetAccessors",
  "va": "0x00641850"
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
  "content_sha256": "9d480da2f16f33d5be31179dc081cb86b17799af8e2845ff671aea8d7698ce20",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00641850 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "x86-32 thiscall with first explicit asset receiver in ECX and caller cleanup",
  "return_semantics": "pointer in EAX or null",
  "return_type": "Pkg16WideString*",
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
  "callers": [],
  "edge_rows": [
    {
      "callsite": "0x00641857",
      "direction": "out",
      "other": "0x005508c0",
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
    "Pkg16WideString*",
    "pkg_sporepedia_accessors_wave6::Pkg16AssetData",
    "pkg_sporepedia_accessors_wave6::Pkg16AssetMetadata",
    "pkg_sporepedia_accessors_wave6::Pkg16WideString"
  ],
  "vtables": [
    "vtable:0x013ff648",
    "vtable:0x01462764",
    "vtable:0x0147c9e8",
    "vtable:0x0147cbbc",
    "vtable:0x01489090",
    "vtable:0x014893b0"
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
      "runtime validation not run",
      "tags helper ownership and returned string lifetime remain gated"
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
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00641857",
      "direction": "out",
      "other": "0x005508c0",
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
    "id": "scc-0162",
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
      "same_package",
      "same_subsystem",
      "shared_types:pkg_sporepedia_accessors_wave6::Pkg16AssetData,pkg_sporepedia_accessors_wave6::Pkg16AssetMetadata,pkg_sporepedia_accessors_wave6::Pkg16WideString",
      "shared_vtable:vtable:0x013ff648,vtable:0x0147c9e8",
      "same_calling_convention"
    ],
    "package": "PKG-SPOREPEDIA-ACCESSORS-WAVE6",
    "score": 29,
    "symbol": "sporepedia_func7ch_00641460",
    "va": "0x00641460"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "shared_types:pkg_sporepedia_accessors_wave6::Pkg16AssetData,pkg_sporepedia_accessors_wave6::Pkg16AssetMetadata,pkg_sporepedia_accessors_wave6::Pkg16WideString",
      "shared_vtable:vtable:0x013ff648,vtable:0x01462764",
      "same_calling_convention"
    ],
    "package": "PKG-SPOREPEDIA-ACCESSORS-WAVE6",
    "score": 29,
    "symbol": "sporepedia_func3ch_006417b0",
    "va": "0x006417b0"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "shared_types:Pkg16WideString*,pkg_sporepedia_accessors_wave6::Pkg16AssetData,pkg_sporepedia_accessors_wave6::Pkg16AssetMetadata,pkg_sporepedia_accessors_wave6::Pkg16WideString",
      "shared_vtable:vtable:0x013ff648,vtable:0x01462764",
      "same_calling_convention"
    ],
    "package": "PKG-SPOREPEDIA-ACCESSORS-WAVE6",
    "score": 29,
    "symbol": "sporepedia_get_author_name_00641810",
    "va": "0x00641810"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "shared_types:pkg_sporepedia_accessors_wave6::Pkg16AssetData,pkg_spo
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Sporepedia__cSPAssetDataOTDB__GetTags.c",
  "file": "src/reconstruction/pkg_sporepedia_accessors_wave6/sporepedia_accessors_wave6.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Sporepedia__cSPAssetDataOTDB__GetTags.c",
    "src/reconstruction/pkg_sporepedia_accessors_wave6/sporepedia_accessors_wave6.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-sporepedia-accessors-wave6/00641850.json"
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
    "runtime validation not run",
    "tags helper ownership and returned string lifetime remain gated"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/Sporepedia__cSPAssetDataOTDB__GetTags.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-sporepedia-accessors-wave6/00641850.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_sporepedia_accessors_wave6/sporepedia_accessors_wave6.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/Sporepedia__cSPAssetDataOTDB__GetTags.c",
      "source_class": "committed_artifact"
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
      "ref": "reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg-sporepedia-accessors-wave6/00641850.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_sporepedia_accessors_wave6/sporepedia_accessors_wave6.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "r
[TRUNCATED]
```
