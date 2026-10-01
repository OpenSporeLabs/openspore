# Reconstruction context 0x00642190

- Status: `partial`
- Content SHA-256: `6402e24372a93d0afb5116d818c2dc91e8362ff25dd7475a2f858f01f8b247db`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00642190",
  "phase": "reconstruction",
  "target": "0x00642190"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueSporepediaAsset",
  "name": "sporepedia_asset_destroy_00642190",
  "package": "PKG-SPOREPEDIA-SAFE-WAVE10",
  "subsystem": "Sporepedia.Asset",
  "va": "0x00642190"
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
  "content_sha256": "11c0aab85dc03f4b2388c159d2a8ff612814412a1b452233b1e5bd86e6c1b9ea",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00642190 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "thiscall, receiver only, no stack arguments",
  "receiver_register": "ECX",
  "ret_form": "RET",
  "return_register": "EAX",
  "return_width_bytes": 0,
  "stack_arguments": [],
  "stack_cleanup_bytes": 0
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
      "name": "FUN_00642210",
      "reconstructed": false,
      "va": "0x00642210"
    },
    {
      "name": "FUN_00dd0bc0",
      "reconstructed": false,
      "va": "0x00dd0bc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00dd0cf0"
    },
    {
      "name": "FUN_00ec4280",
      "reconstructed": false,
      "va": "0x00ec4280"
    },
    {
      "name": "FUN_00ecc620",
      "reconstructed": false,
      "va": "0x00ecc620"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00642213",
      "direction": "in",
      "other": "0x00642210",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00dd0bd7",
      "direction": "in",
      "other": "0x00dd0bc0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00dd0d28",
      "direction": "in",
      "other": "0x00dd0cf0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00ec4297",
      "direction": "in",
      "other": "0x00ec4280",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00ecc65c",
      "direction": "in",
      "other": "0x00ecc620",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00642205",
      "direction": "out",
      "other": "0x006412a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006421d0",
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
    "OpaqueAssetRef",
    "OpaqueAssetRefVtable",
    "OpaqueInlineWordVector",
    "OpaqueSporepediaAsset",
    "OpaqueSporepediaAsset*",
    "SporepediaSafeBindings",
    "void"
  ],
  "vtables": []
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
      "The base destructor 0x006412a0 is a tail-transfer target and is not promoted; only its three vtable stores are modelled.",
      "The free port 0x00f47380 is shared across the campaign and is not promoted here.",
      "The handle release slots at asset-ref vtable +0x04 are opaque seams and are not promoted.",
      "The invariant that keeps an inline vector from being freed is unverified at runtime.",
      "The six vtable words are literal image addresses with no class attribution in the live database.",
      "gate-sporepedia-asset-destroy-runtime-vtable-owners",
      "runtime validation not performed; static decompilation and disassembly only",
      "the base destructor 0x006412a0 is a tail-transfer target and is not promoted; only its three vtable stores are modelled in the default port",
      "the free port 0x00f47380 is shared across the campaign and is not promoted here",
      "the handle release slots at asset-ref vtable +0x04 are opaque seams and are not promoted",
      "the inline marker comparison uses the word at +0x50 against the vector first word at +0x40; the invariant that keeps an inline vector from being freed is unverified at runtime",
      "the six vtable words are literal image addresses with no class attribution in the live database"
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
      "name": "FUN_00642210",
      "reconstructed": false,
      "va": "0x00642210"
    },
    {
      "name": "FUN_00dd0bc0",
      "reconstructed": false,
      "va": "0x00dd0bc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00dd0cf0"
    },
    {
      "name": "FUN_00ec4280",
      "reconstructed": false,
      "va": "0x00ec4280"
    },
    {
      "name": "FUN_00ecc620",
      "reconstructed": false,
      "va": "0x00ecc620"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00642213",
      "direction": "in",
      "other": "0x00642210",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00dd0bd7",
      "direction": "in",
      "other": "0x00dd0bc0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00dd0d28",
      "direction": "in",
      "other": "0x00dd0cf0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00ec4297",
      "direction": "in",
      "other": "0x00ec4280",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00ecc65c",
      "direction": "in",
      "other": "0x00ecc620",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00642205",
      "direction": "out",
      "other": "0x006412a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006421d0",
      "direction": "out",
      "other": "0x00f47380",
      "reference_type": "direct-call"
    }
  ],
  "edges_trunca
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
      "same_subsystem",
      "same_class",
      "shared_types:OpaqueAssetRef,OpaqueInlineWordVector,OpaqueSporepediaAsset,OpaqueSporepediaAsset*"
    ],
    "package": "PKG-SPOREPEDIA-SAFE-WAVE10",
    "score": 28,
    "symbol": "sporepedia_asset_load_00642230",
    "va": "0x00642230"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-APP-SAFE-WAVE10",
    "score": 2,
    "symbol": "property_value_resolve_0041e920",
    "va": "0x0041e920"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-SKINNER-SAFE-WAVE10",
    "score": 2,
    "symbol": "skin_painter_job_brush_pass_005182f0",
    "va": "0x005182f0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-PALETTE-SAFE-WAVE10",
    "score": 2,
    "symbol": "palette_row_layout_005c3000",
    "va": "0x005c3000"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg_sporepedia_safe_wave10/sporepedia_safe_wave10.cpp",
  "files": [
    "src/reconstruction/pkg_sporepedia_safe_wave10/sporepedia_safe_wave10.cpp",
    "src/reconstruction/pkg_sporepedia_safe_wave10/sporepedia_safe_wave10.hpp",
    "src/reconstruction/pkg_sporepedia_safe_wave10/sporepedia_safe_wave10_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave10-safe-core/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-sporepedia-safe-wave10/00642190.json"
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
    "The base destructor 0x006412a0 is a tail-transfer target and is not promoted; only its three vtable stores are modelled.",
    "The free port 0x00f47380 is shared across the campaign and is not promoted here.",
    "The handle release slots at asset-ref vtable +0x04 are opaque seams and are not promoted.",
    "The invariant that keeps an inline vector from being freed is unverified at runtime.",
    "The six vtable words are literal image addresses with no class attribution in the live database.",
    "What the base destructor 0x006412a0 does beyond its three vtable stores",
    "What the five handles at +0x1c, +0x20, +0x3c, +0x70 and +0x74 reference",
    "What the inline marker invariant at +0x50 is and who maintains it",
    "Whether the free at 0x00f47380 matches the allocator that produced the entry vector",
    "Which classes the six vtable words belong to",
    "gate-sporepedia-asset-destroy-runtime-vtable-owners",
    "runtime validation not performed; static decompilation and disassembly only",
    "the base destructor 0x006412a0 is a tail-transfer target and is not promoted; only its three vtable stores are modelled in the default port",
    "the free port 0x00f47380 is shared across the campaign and is not promoted here",
    "the handle release slots at asset-ref vtable +0x04 are opaque seams and are not promoted",
    "the inline marker comparison uses the word at +0x50 against the vector first word at +0x40; the invariant that keeps an inline vector from being freed is unverified at runtime",
    "the six 
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave10-safe-core/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-sporepedia-safe-wave10/00642190.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_sporepedia_safe_wave10/sporepedia_safe_wave10.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_sporepedia_safe_wave10/sporepedia_safe_wave10.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_sporepedia_safe_wave10/sporepedia_safe_wave10_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/integrated/batch-2026-09-25-wave10-safe-core/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg-sporepedia-safe-wave10/00642190.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_sporepedia_safe_wave10/sporepedia_safe_wave10.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_sporepedia_safe_wave10/sporepedia_safe_wave10.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      
[TRUNCATED]
```
