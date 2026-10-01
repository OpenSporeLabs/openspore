# Reconstruction context 0x00641860

- Status: `partial`
- Content SHA-256: `07278861c471ee9e1029b4dba6f6ae98c8e26fb7022ea56a37009e11cdff092d`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00641860",
  "phase": "reconstruction",
  "target": "0x00641860"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "Sporepedia::cSPAssetDataOTDB::GetTimeCreated",
  "package": "PKG-SPOREPEDIA-ACCESSORS-WAVE6",
  "subsystem": "Sporepedia.AssetAccessors",
  "va": "0x00641860"
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
  "content_sha256": "9f2ffcb62848182133903558054504c1bd58cab5ce751edd3c66c5f4876cb7c9",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00641860 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "x86-32 thiscall with first explicit asset receiver in ECX and callee cleanup",
  "return_semantics": "void",
  "return_type": "void",
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "callee"
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
      "callsite": "0x00641867",
      "direction": "out",
      "other": "0x00550cf0",
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
    "pkg_sporepedia_accessors_wave6::Pkg16AssetData",
    "pkg_sporepedia_accessors_wave6::Pkg16AssetMetadata",
    "pkg_sporepedia_accessors_wave6::Pkg16WideString",
    "void"
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
      "time helper, destination lifetime, and null-output behavior remain gated"
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
      "callsite": "0x00641867",
      "direction": "out",
      "other": "0x00550cf0",
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
    "id": "scc-0163",
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
      "shared_vtable:vtable:0x013ff648,vtable:0x0147c9e8"
    ],
    "package": "PKG-SPOREPEDIA-ACCESSORS-WAVE6",
    "score": 27,
    "symbol": "sporepedia_func7ch_00641460",
    "va": "0x00641460"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "shared_types:pkg_sporepedia_accessors_wave6::Pkg16AssetData,pkg_sporepedia_accessors_wave6::Pkg16AssetMetadata,pkg_sporepedia_accessors_wave6::Pkg16WideString",
      "shared_vtable:vtable:0x013ff648,vtable:0x01462764"
    ],
    "package": "PKG-SPOREPEDIA-ACCESSORS-WAVE6",
    "score": 27,
    "symbol": "sporepedia_func3ch_006417b0",
    "va": "0x006417b0"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "shared_types:pkg_sporepedia_accessors_wave6::Pkg16AssetData,pkg_sporepedia_accessors_wave6::Pkg16AssetMetadata,pkg_sporepedia_accessors_wave6::Pkg16WideString",
      "shared_vtable:vtable:0x013ff648,vtable:0x01462764"
    ],
    "package": "PKG-SPOREPEDIA-ACCESSORS-WAVE6",
    "score": 27,
    "symbol": "sporepedia_get_author_name_00641810",
    "va": "0x00641810"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "shared_types:pkg_sporepedia_accessors_wave6::Pkg16AssetData,pkg_sporepedia_accessors_wave6::Pkg16AssetMetadata,pkg_sporepedia_accessors_wave6::Pkg16WideString",
      "shared_vtable:v
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Sporepedia__cSPAssetDataOTDB__GetTimeCreated.c",
  "file": "src/reconstruction/pkg_sporepedia_accessors_wave6/sporepedia_accessors_wave6.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Sporepedia__cSPAssetDataOTDB__GetTimeCreated.c",
    "src/reconstruction/pkg_sporepedia_accessors_wave6/sporepedia_accessors_wave6.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-sporepedia-accessors-wave6/00641860.json"
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
    "time helper, destination lifetime, and null-output behavior remain gated"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/Sporepedia__cSPAssetDataOTDB__GetTimeCreated.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-sporepedia-accessors-wave6/00641860.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_sporepedia_accessors_wave6/sporepedia_accessors_wave6.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/Sporepedia__cSPAssetDataOTDB__GetTimeCreated.c",
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
      "ref": "reconstruction/metadata/pkg-sporepedia-accessors-wave6/00641860.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_sporepedia_accessors_wave6/sporepedia_accessors_wave6.cpp",
      "source_class": "committed_artifact"
    }
  
[TRUNCATED]
```
