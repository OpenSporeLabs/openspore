# Reconstruction context 0x006417b0

- Status: `partial`
- Content SHA-256: `f04138a82a6b966fea458bdf54dc045297a67a4b2640a7db2208597710a13712`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x006417b0",
  "phase": "reconstruction",
  "target": "0x006417b0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "Sporepedia::cSPAssetDataOTDB::func3Ch",
  "package": "PKG-SPOREPEDIA-ACCESSORS-WAVE6",
  "subsystem": "Sporepedia.AssetAccessors",
  "va": "0x006417b0"
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
  "content_sha256": "e3b9955924550e33aa8226980ccf07a9dc7342bc84508221324da721274f9d0d",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x006417b0 failed: Decompilation did not complete. Reason: ",
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
  "return_semantics": "constant 0x80000001 in EAX",
  "return_type": "std::uint32_t",
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
  "edge_rows": [],
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
    "std::uint32_t"
  ],
  "vtables": [
    "vtable:0x013ff648",
    "vtable:0x01462764",
    "vtable:0x0147c9e8",
    "vtable:0x0147ca30",
    "vtable:0x0147ca70",
    "vtable:0x0147caf8",
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
      "constant meaning and caller interpretation remain gated",
      "runtime validation not run"
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
  "edges": [],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 0,
  "fan_out": 0,
  "manifest_callees": [],
  "manifest_callers": [],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0157",
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
    "symbol": "sporepedia_get_author_name_00641810",
    "va": "0x00641810"
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
    "symbol": "sporepedia_get_author_id_00641820",
    "va": "0x00641820"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "shared_types:pkg_sporepedia_accessors_wave6::Pkg16AssetData,pkg_sporepedia_acc
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Sporepedia__cSPAssetDataOTDB__func3Ch.c",
  "file": "src/reconstruction/pkg_sporepedia_accessors_wave6/sporepedia_accessors_wave6.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Sporepedia__cSPAssetDataOTDB__func3Ch.c",
    "src/reconstruction/pkg_sporepedia_accessors_wave6/sporepedia_accessors_wave6.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-sporepedia-accessors-wave6/006417b0.json"
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
    "constant meaning and caller interpretation remain gated",
    "runtime validation not run"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/Sporepedia__cSPAssetDataOTDB__func3Ch.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-sporepedia-accessors-wave6/006417b0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_sporepedia_accessors_wave6/sporepedia_accessors_wave6.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/Sporepedia__cSPAssetDataOTDB__func3Ch.c",
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
      "ref": "reconstruction/metadata/pkg-sporepedia-accessors-wave6/006417b0.json",
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
