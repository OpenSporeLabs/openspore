# Reconstruction context 0x00642230

- Status: `partial`
- Content SHA-256: `3e4ed6eb93aef40157a291d8460db80c8e317dba4965ff3761870cf8ec99648e`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00642230",
  "phase": "reconstruction",
  "target": "0x00642230"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueSporepediaAsset",
  "name": "sporepedia_asset_load_00642230",
  "package": "PKG-SPOREPEDIA-SAFE-WAVE10",
  "subsystem": "Sporepedia.Asset",
  "va": "0x00642230"
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
  "content_sha256": "6876609c3230f877ec8566a8cf110624555e9f6068d64d6333da640d85a34561",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00642230 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "thiscall with callee stack cleanup",
  "receiver_register": "ECX",
  "ret_form": "RET 0x4",
  "return_register": "EAX",
  "return_width_bytes": 0,
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "machine_type": "OpaqueLookupSource*",
      "native_reads": [
        "MOV ESI,[ESP+0x48] at 0x00642263",
        "CMP ESI,EBP / JZ 0x00642375"
      ],
      "normalized_name": "source",
      "note": "a null source skips both lookup branches and still zeroes max_6c and runs the gate scan",
      "position": 1,
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 4
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
      "callsite": "0x00642395",
      "direction": "out",
      "other": "0x004babe0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006423e2",
      "direction": "out",
      "other": "0x004f3d60",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00642432",
      "direction": "out",
      "other": "0x004f3d60",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00642482",
      "direction": "out",
      "other": "0x004f3d60",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0064249c",
      "direction": "out",
      "other": "0x004f5720",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006422c1",
      "direction": "out",
      "other": "0x005507a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006422cc",
      "direction": "out",
      "other": "0x005507a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006424f3",
      "direction": "out",
      "other": "0x0060a600",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006424b6",
      "direction": "out",
      "other": "0x00642070",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00642301",
      "direction": "out",
      "other": "0x0067dea0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00642321",
      "direction": "out",
      "other": "0x0067dea0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "OpaqueAssetRef",
    "OpaqueGlobalRecord",
    "OpaqueGlobalRecordRange",
    "OpaqueInlineWordVector",
    "OpaqueKey16",
    "OpaqueKeyedSet",
    "OpaqueLookup",
    "OpaqueLookupEntry",
    "OpaqueLookupSource",
    "OpaqueLookupSource*",
    "OpaqueSporepediaAsset",
    "OpaqueSporepediaAsset*",
    "OpaqueWordVector",
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
      "Ten callees are modelled as opaque ports and none is promoted to a function record.",
      "The asset apply property vtable slot owner at +0xb4 is unattributed in the live database.",
      "The clear port count argument is computed as last minus last, which is statically zero; the runtime meaning of a zero count is unverified.",
      "The entry vector rewind arithmetic and the inline marker invariant are static only.",
      "The selectors 0x0670da17 and 0x03c609f8 and the three tag globals at 0x015da8e0, 0x015dab18 and 0x015da80c are undecoded.",
      "The signed maximum comparison depends on runtime supplied entry values.",
      "gate-sporepedia-asset-load-runtime-selectors-and-tag-globals",
      "runtime validation not performed; static decompilation and disassembly only",
      "ten callees are modelled as opaque ports and none is promoted to a function record",
      "the asset apply property vtable slot owner at +0xb4 is unattributed in the live database",
      "the clear port count argument is computed as last minus last, which is statically zero; the runtime meaning of a zero count is unverified",
      "the entry vector rewind arithmetic and the inline marker invariant are static only",
      "the selectors 0x0670da17 and 0x03c609f8 and the three tag globals are undecoded",
      "the signed maximum comparison against max_6c depends on the entry values, which are runtime supplied"
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
      "callsite": "0x00642395",
      "direction": "out",
      "other": "0x004babe0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006423e2",
      "direction": "out",
      "other": "0x004f3d60",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00642432",
      "direction": "out",
      "other": "0x004f3d60",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00642482",
      "direction": "out",
      "other": "0x004f3d60",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0064249c",
      "direction": "out",
      "other": "0x004f5720",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006422c1",
      "direction": "out",
      "other": "0x005507a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006422cc",
      "direction": "out",
      "other": "0x005507a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006424f3",
      "direction": "out",
      "other": "0x0060a600",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006424b6",
      "direction": "out",
      "other": "0x00642070",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00642301",
      "direction": "out",
      "other": "0x0067dea0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00642321",
      "direction": "out",
      "other": "0x
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
    "symbol": "sporepedia_asset_destroy_00642190",
    "va": "0x00642190"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-APP-SAFE-WAVE10",
    "score": 2,
    "symbol": "cursor_buffer_emit_0041e8b0",
    "va": "0x0041e8b0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-SKINNER-SAFE-WAVE10",
    "score": 2,
    "symbol": "skin_painter_state_setup_00506590",
    "va": "0x00506590"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-EDITOR-RUNTIME-WAVE8",
    "score": 2,
    "symbol": "editor_creature_walk_controller_set_target_angle_0059b2f0",
    "va": "0x0059b2f0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-EDITOR-SAFE-WAVE10",
    "score": 2,
    "symbol": "editor_row_publish_005a2010",
    "va": "0x005a2010"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-PALETTE-SAFE-WAVE10",
    "score": 2,
    "symbol": "page_visible_slots_refresh_005c0a60",
    "va": "0x005c0a60"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-UI-SAFE-WAVE10",
    "score": 2,
    "symbol": "image_archive_scalar_deleting_destructor_00635700",
    "va": "0x00635700"
  },
  {
    "match_basis": [
   
[TRUNCATED]
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
    "reconstruction/metadata/pkg-sporepedia-safe-wave10/00642230.json"
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
    "Ten callees are modelled as opaque ports and none is promoted to a function record.",
    "The asset apply property vtable slot owner at +0xb4 is unattributed in the live database.",
    "The clear port count argument is computed as last minus last, which is statically zero; the runtime meaning of a zero count is unverified.",
    "The entry vector rewind arithmetic and the inline marker invariant are static only.",
    "The selectors 0x0670da17 and 0x03c609f8 and the three tag globals at 0x015da8e0, 0x015dab18 and 0x015da80c are undecoded.",
    "The signed maximum comparison depends on runtime supplied entry values.",
    "What the byte-span rewind of the entry vector end is intended to discard",
    "What the selectors 0x0670da17 and 0x03c609f8 identify",
    "What the three tag globals at 0x015da8e0, 0x015dab18 and 0x015da80c encode",
    "What values the entry lookup returns and how the signed maximum is meant to be used",
    "Which class owns the asset apply property vtable slot +0xb4",
    "Why the clear port is called with a statically zero count and what the third argument means",
    "Why the gate lookup is called once per entry rather than once outside the loop",
    "gate-sporepedia-asset-load-runtime-selectors-and-tag-globals",
    "runtime validation not performed; static decompilation and disassembly only",
    "ten callees are modelled as opaque ports and none is promoted to a function record",
    "the asset apply property vtable slot owner at +0xb4 is unattributed in the live database",
    "the clear 
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave10-safe-core/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-sporepedia-safe-wave10/00642230.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_sporepedia_safe_wave10/sporepedia_safe_wave10.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_sporepedia_safe_wave10/sporepedia_safe_wave10.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_sporepedia_safe_wave10/sporepedia_safe_wave10_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-sporepedia-safe-wave10/00642230.json",
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
