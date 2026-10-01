# Reconstruction context 0x00576650

- Status: `partial`
- Content SHA-256: `10fb2080a810f6829edec1395192e6dc2f3817472f04b3f19580b8a6c2cc3aa4`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00576650",
  "phase": "reconstruction",
  "target": "0x00576650"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "TexturePtr",
  "name": "TexturePtr_Set",
  "package": "PKG-20-RESOURCE-ADAPTER",
  "subsystem": "Resource.TexturePointer",
  "va": "0x00576650"
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
  "content_sha256": "9ffe937bafcd3cb4e2819500f3ce30325a8bb40ecfe20074c5c763f389b6c87a",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00576650 failed: Decompilation did not complete. Reason: ",
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
  "hidden_this_register": "ECX",
  "hidden_this_type": "TexturePtr*",
  "return_register": null,
  "return_type": "void",
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "rhs",
      "observed_use": "Compares against the current slot, increments rhs+0x08 when non-null, and publishes rhs to the slot.",
      "position": 1,
      "type": "OpaqueTexture*",
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
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00580700"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00585d40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005fdca0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00646370"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00659270"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006ebb80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006ef9e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006f0fb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006f44c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006f4500"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006fbed0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0070ec80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00713070"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007679f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0076e110"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0076edf0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00580858",
      "direction": "in",
      "other": "0x00580700",
      "reference_type": "direct-call"
    },

[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [
    "global:No direct global data reference is present in the target body."
  ],
  "types": [
    "OpaqueTexture",
    "OpaqueTexture*",
    "TexturePtr",
    "TexturePtr*",
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
      "gate-texture-ptr-refcount"
    ],
    "validated": 0
  },
  "semantic": {
    "category": "GAMEPLAY_LOGIC",
    "classification": "STRONG_SEMANTIC",
    "confidence": {
      "identity": 0.95,
      "mechanics": 0.99,
      "ownership": 0.9
    },
    "contradictions": [],
    "downstream_unlock_count": 67,
    "evidence": [
      {
        "kind": "disassembly",
        "source": "ghidra://SporeApp.exe@0x00576650",
        "statement": "The target compares old/rhs, uses LOCK XADD for rhs+8 and old+8, stores rhs into the slot, and restores a below-one old count to one."
      },
      {
        "kind": "decompilation",
        "source": "ghidra://SporeApp.exe@0x00576650",
        "statement": "Pseudocode independently shows the same add-new, publish, release-old sequence."
      },
      {
        "kind": "sibling",
        "source": "ghidra://SporeApp.exe@0x005766b0",
        "statement": "The adjacent clear/reset path also clears the slot and clamps the reference count without deletion."
      },
      {
        "kind": "SDK",
        "source": "/home/juanr/apps/Spore-ModAPI/Spore ModAPI/Spore/Graphics/Texture.h:26-30,45-75,84-97",
        "statement": "TexturePtr is eastl::intrusive_ptr<Graphics::Texture>; Texture stores mnRefCount at +0x08 and Release restores a below-one count to one without deleting itself."
      },
      {
        "kind": "repository",
        "source": "docs/analysis/reconstruction-research-queue.md:128",
        "statement": "The committed queue records TexturePtr_Set as a 67-fan-
[TRUNCATED]
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
      "va": "0x00580700"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00585d40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005fdca0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00646370"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00659270"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006ebb80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006ef9e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006f0fb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006f44c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006f4500"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006fbed0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0070ec80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00713070"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007679f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0076e110"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0076edf0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00777290"
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
      "same_calling_convention"
    ],
    "package": "WAVE6-PRESENTATION",
    "score": 2,
    "symbol": "transform_pre_transform_by_0040ccb0",
    "va": "0x0040ccb0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-WAVE6-CONTAINERS-MEMORY",
    "score": 2,
    "symbol": "wave6_reference_00432a50",
    "va": "0x00432a50"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-10-EDITOR-DISPATCH",
    "score": 2,
    "symbol": "editor_query_reset_005dd750",
    "va": "0x005dd750"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-10-EDITOR-DISPATCH",
    "score": 2,
    "symbol": "editor_query_dispatch_005dfd00",
    "va": "0x005dfd00"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "wave6-resources",
    "score": 2,
    "symbol": "property_list_has_property_006a2470",
    "va": "0x006a2470"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "wave6-resources",
    "score": 2,
    "symbol": "property_list_get_property_object_006a24d0",
    "va": "0x006a24d0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "pkg-resource-index-ref-008d86b0",
    "score": 2,
    "symbol": "destroy_index_008d86b0",
    "va": "0x008d86b0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-10-EDITOR-DISPATCH",
    "score": 2,
    "symbol": "editor_query_clear_flags_0093db80",
    "va": "0x0093db80"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg20_resource_adapter/texture_ptr.cpp",
  "files": [
    "reconstruction/staging/pkg20-resource-adapter/texture_ptr.cpp",
    "reconstruction/staging/pkg20-resource-adapter/texture_ptr.hpp",
    "reconstruction/staging/pkg20-resource-adapter/texture_ptr_model_test.cpp",
    "src/reconstruction/pkg20_resource_adapter/texture_ptr.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-source-wave4/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg20-resource-adapter/00576650.json"
  ]
}
```

## 13_semantic_hypotheses

- State: `present`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

```json
{
  "original_bytes": 6367,
  "preview": "{\n  \"category\": \"GAMEPLAY_LOGIC\",\n  \"classification\": \"STRONG_SEMANTIC\",\n  \"confidence\": {\n    \"identity\": 0.95,\n    \"mechanics\": 0.99,\n    \"ownership\": 0.9\n  },\n  \"contradictions\": [],\n  \"downstream_unlock_count\": 67,\n  \"evidence\": [\n    {\n      \"kind\": \"disassembly\",\n      \"source\": \"ghidra://SporeApp.exe@0x00576650\",\n      \"statement\": \"The target compares old/rhs, uses LOCK XADD for rhs+8 and old+8, stores rhs into the slot, and restores a below-one old count to one.\"\n    },\n    {\n      \"kind\": \"decompilation\",\n      \"source\": \"ghidra://SporeApp.exe@0x00576650\",\n      \"statement\": \"Pseudocode independently shows the same add-new, publish, release-old sequence.\"\n    },\n    {\n      \"kind\": \"sibling\",\n      \"source\": \"ghidra://SporeApp.exe@0x005766b0\",\n      \"statement\": \"The adjacent clear/reset path also clears the slot and clamps the reference count without deletion.\"\n    },\n    {\n      \"kind\": \"SDK\",\n      \"source\": \"/home/juanr/apps/Spore-ModAPI/Spore ModAPI/Spore/Graphics/Texture.h:26-30,45-75,84-97\",\n      \"statement\": \"TexturePtr is eastl::intrusive_ptr<Graphics::Texture>; Texture stores mnRefCount at +0x08 and Release restores a below-one count to one without deleting itself.\"\n    },\n    {\n      \"kind\": \"repository\",\n      \"source\": \"docs/analysis/reconstruction-research-queue.md:128\",\n      \"statement\": \"The committed queue records TexturePtr_Set as a 67-fan-in GameGlobal resource-content candidate with no ca
[TRUNCATED]
```

## 14_conflicts_questions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json, knowledgegraph/research/semantic-decomp.json`

```json
{
  "conflicts": [],
  "unresolved_questions": [
    "How are TexturePtr slots embedded and published by the 67 direct callers?",
    "What are the exact runtime synchronization guarantees around the locked refcount updates?",
    "What is the concrete Texture subtype and complete owner layout?",
    "What runtime paths exercise the below-one clamp and whether such objects are externally observable?",
    "concrete Texture owner",
    "gate-texture-ptr-refcount",
    "runtime concurrency guarantees",
    "runtime refcount values and external lifetime"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-source-wave4/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg20-resource-adapter/00576650.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg20-resource-adapter/texture_ptr.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg20-resource-adapter/texture_ptr.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg20-resource-adapter/texture_ptr_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg20_resource_adapter/texture_ptr.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/integrated/batch-2026-09-25-source-wave4/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg20-resource-adapter/00576650.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg20-resource-adapter/texture_ptr.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg20-resource-adapter/texture_ptr.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging
[TRUNCATED]
```
