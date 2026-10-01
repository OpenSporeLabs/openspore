# Reconstruction context 0x00641400

- Status: `partial`
- Content SHA-256: `6ab54bbd9932b8d0238025c1bc1be59700caf5b004060cf457e85baa58014cee`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00641400",
  "phase": "reconstruction",
  "target": "0x00641400"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "Pkg16AssetData",
  "name": "Sporepedia::cSPAssetDataOTDB::IsEditable",
  "package": "PKG-16-SPOREPEDIA-ONLINE",
  "subsystem": "Sporepedia.AssetData",
  "va": "0x00641400"
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
  "content_sha256": "6392649869cdf4e6c6f20a97316b802b8f44f3b4e59a2cf06d94be7cd806e136",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00641400 failed: Decompilation did not complete. Reason: ",
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
  "receiver": {
    "register": "ECX",
    "type": "Pkg16AssetData *",
    "width_bytes": 4
  },
  "return_observation": "The wrapper performs no return-value transformation; the target selected from vtable +0x60 supplies AL.",
  "return_register": "AL through the tail target",
  "stack_arguments": [],
  "stack_cleanup_bytes": 0,
  "termination": "JMP EDX"
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
    "Pkg16AssetData",
    "Pkg16AssetData *",
    "Pkg16EditableSlot",
    "cSPAssetDataOTDB"
  ],
  "vtables": [
    "vtable:0x00000060",
    "vtable:0x013ff648",
    "vtable:0x013ff6ac",
    "vtable:0x01462764",
    "vtable:0x014627bc",
    "vtable:0x0147c9e8",
    "vtable:0x0147ca30",
    "vtable:0x0147caf8",
    "vtable:0x0147cbbc",
    "vtable:0x0147cc14",
    "vtable:0x01489090",
    "vtable:0x014890f4"
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
      "gate-sporepedia-editable-vtable"
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
  "manifest_callees": [
    "vtable+0x60"
  ],
  "manifest_callers": [
    "data_pointer_xrefs_7"
  ],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0151",
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
      "same_class",
      "shared_types:Pkg16AssetData,Pkg16AssetData *,cSPAssetDataOTDB",
      "shared_vtable:vtable:0x013ff648,vtable:0x01462764"
    ],
    "package": "PKG-16-SPOREPEDIA-ONLINE",
    "score": 32,
    "symbol": "Sporepedia_cSPAssetDataOTDB_HasName_raw_00641770",
    "va": "0x00641770"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "same_class",
      "shared_types:Pkg16AssetData,Pkg16AssetData *",
      "shared_vtable:vtable:0x013ff648,vtable:0x01462764"
    ],
    "package": "PKG-16-SPOREPEDIA-ONLINE",
    "score": 29,
    "symbol": "Sporepedia_cSPAssetDataOTDB_GetAssetID_address_006417c0",
    "va": "0x006417c0"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x013ff648,vtable:0x013ff6ac"
    ],
    "package": "pkg-swarm-w1-005c0dd0",
    "score": 4,
    "symbol": "re_005c0dd0",
    "va": "0x005c0dd0"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x013ff648,vtable:0x01462764"
    ],
    "package": "pkg-swarm-w1-006413d0",
    "score": 4,
    "symbol": "re_006413d0",
    "va": "0x006413d0"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x013ff648,vtable:0x01462764"
    ],
    "package": "pkg-swarm-w1-00641410",
    "score": 4,
    "symbol": "re_00641410",
    "va": "0x00641410"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x013ff648,vtable:0x013ff6ac"
    ],
    "package": "PKG-SPOREPEDIA-ACCESSORS-WAVE6",
    "score": 4,
    "symbol": "sporepedia_func7ch_00641460",
    "va": "0x00641460"
  },
  {
    "
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Sporepedia__cSPAssetDataOTDB__IsEditable.c",
  "file": "src/reconstruction/pkg16_sporepedia/sporepedia_access.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Sporepedia__cSPAssetDataOTDB__IsEditable.c",
    "src/reconstruction/pkg16_sporepedia/sporepedia_access.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-source-wave2/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg16-sporepedia/00641400.json"
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
    "Can the selected target legally return a non-canonical byte even though the SDK declaration is bool?",
    "Which concrete vtable owner and callback signature populate slot +0x60 at runtime?",
    "gate-sporepedia-editable-vtable",
    "noncanonical return normalization",
    "runtime subtype",
    "slot owner"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/Sporepedia__cSPAssetDataOTDB__IsEditable.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-source-wave2/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg16-sporepedia/00641400.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg16_sporepedia/sporepedia_access.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/Sporepedia__cSPAssetDataOTDB__IsEditable.c",
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
      "ref": "reconstruction/integrated/batch-2026-09-25-source-wave2/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg16-sporepedia/00641400.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg16_sporepedia/sporepedia_access.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/
[TRUNCATED]
```
