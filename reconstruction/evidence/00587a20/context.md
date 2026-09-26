# Reconstruction context 0x00587a20

- Status: `partial`
- Content SHA-256: `3ae8ca8c57750802f4d7dd81b7b44dbc34f571b358682fe24e92835ebc47e410`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00587a20",
  "phase": "reconstruction",
  "target": "0x00587a20"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "Editors::cEditor::OnExit",
  "package": null,
  "subsystem": "Editor",
  "va": "0x00587a20"
}
```

## 03_current_status

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "blocked": false,
  "reconstructed": false,
  "runtime_gated": true,
  "runtime_validated": 0,
  "status": "queued"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "97c7b54b901bc382e52a0e284c3c7508a50295049b85549ed535108c04d3f3d2",
  "live_attempts": [],
  "live_requested": false,
  "overall": "PERSISTED"
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
  "receiver": true,
  "receiver_register": "ECX",
  "ret_form": "RET",
  "return_observation": "Ghidra resolves return_type void (analyze_function_complete, ghidra_function.return_type_resolved true). The derived openspore-abi-inference-1 record for this target abstained (conventions.confidence UNKNOWN, calling_convention null, candidate_conventions __cdecl) and its return claim is contradicted by the balanced FLD/FSTP pair; see conflicts_and_disagreements.",
  "return_semantics": "void. The epilogue is POP ESI ; POP EBP ; POP EBX ; ADD ESP,0x44 ; RET: a bare RET with no immediate, and no instruction after the last call reads a return register. The x87 pair at 0x00587b10 (FLD float ptr [ESI+0x4d0]) and 0x00587b1b (FSTP float ptr [ESP]) is balanced -- FSTP pops what FLD pushed -- so nothing is left on the x87 stack, and the value is a 4-byte stack argument, not a result. This DISAGREES with the derived ABI record for this target, which reports return_register ST0 and return_semantics float_or_x87_in_ST0; that reading is a false positive of the linear-sweep inference, p...",
  "return_type": "void",
  "saved_registers": [
    "EBP",
    "EBX",
    "EDI",
    "ESI"
  ],
  "stack_arguments": [],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": [
    "RET at 0x0058856a, bare, no immediate",
    "RET"
  ]
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004ad330"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00573c00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00573d70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005772b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00587270"
    },
    {
      "name": "release_child_0062c910",
      "reconstructed": true,
      "va": "0x0062c910"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0067dcc0"
    }
  ],
  "callers": [],
  "edge_rows": [
    {
      "callsite": "0x00587ef6",
      "direction": "out",
      "other": "0x00401020",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00587f12",
      "direction": "out",
      "other": "0x00401020",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00587de0",
      "direction": "out",
      "other": "0x00401050",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0058855f",
      "direction": "out",
      "other": "0x00421cf0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00587d13",
      "direction": "out",
      "other": "0x0043a9a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00588028",
      "direction": "out",
      "other": "0x004581d0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00587de7",
      "direction": "out",
      "other": "0x
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "Byte",
    "Dword",
    "HIGH",
    "LocalAppState",
    "U64",
    "float",
    "void",
    "void*"
  ],
  "vtables": [
    "vtable:0x013f57f8"
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
      "runtime validation not run: no positive hash-pinned original-process trace reaches 0x00587a20 in the committed corpus"
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
  "callees": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004ad330"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00573c00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00573d70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005772b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00587270"
    },
    {
      "name": "release_child_0062c910",
      "reconstructed": true,
      "va": "0x0062c910"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0067dcc0"
    }
  ],
  "callees_truncated": false,
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00587ef6",
      "direction": "out",
      "other": "0x00401020",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00587f12",
      "direction": "out",
      "other": "0x00401020",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00587de0",
      "direction": "out",
      "other": "0x00401050",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0058855f",
      "direction": "out",
      "other": "0x00421cf0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00587d13",
      "direction": "out",
      "other": "0x0043a9a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00588028",
      "direction": "out",
      "other": "0x004581d0",
      "reference_type": "direct-call"
    
[TRUNCATED]
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "shared_types:void*",
      "same_calling_convention"
    ],
    "package": "PKG-APP-SAFE-WAVE11",
    "score": 5,
    "symbol": "property_record_assign_pair_004279d0",
    "va": "0x004279d0"
  },
  {
    "match_basis": [
      "shared_types:Byte",
      "same_calling_convention"
    ],
    "package": "PKG-EDITOR-SAFE-WAVE11",
    "score": 5,
    "symbol": "editor_paint_commit_0043ac40",
    "va": "0x0043ac40"
  },
  {
    "match_basis": [
      "shared_types:Byte",
      "same_calling_convention"
    ],
    "package": "PKG-EDITOR-SAFE-WAVE11",
    "score": 5,
    "symbol": "editor_bake_select_004c4a30",
    "va": "0x004c4a30"
  },
  {
    "match_basis": [
      "shared_types:void*",
      "same_calling_convention"
    ],
    "package": "PKG-PALETTE-SAFE-WAVE11",
    "score": 5,
    "symbol": "palette_safe_wave11_fill_node_array_005c7ff0",
    "va": "0x005c7ff0"
  },
  {
    "match_basis": [
      "shared_types:void*",
      "same_calling_convention"
    ],
    "package": "PKG-APP-SERVICES-SAFE-WAVE11",
    "score": 5,
    "symbol": "service_005fa8d0",
    "va": "0x005fa8d0"
  },
  {
    "match_basis": [
      "shared_types:void*",
      "same_calling_convention"
    ],
    "package": "PKG-APP-SERVICES-SAFE-WAVE11",
    "score": 5,
    "symbol": "service_0060ee90",
    "va": "0x0060ee90"
  },
  {
    "match_basis": [
      "same_calling_convention",
      "direct_xref_neighbor"
    ],
    "package": "PKG-SIMULATOR-SAFE-WAVE11",
    "score": 5,
    "symbol": "release_child_0062c910",
    "va": "0x0062c910"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditor__OnExit.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditor__OnExit.c",
    "reconstruction/staging/pkg-dogfood-00587a20-a1/editor_onexit_00587a20.cpp",
    "reconstruction/staging/pkg-dogfood-00587a20-a1/editor_onexit_00587a20.hpp",
    "reconstruction/staging/pkg-editor-onexit-smoke01/editor_onexit_00587a20.cpp",
    "reconstruction/staging/pkg-editor-onexit-smoke01/editor_onexit_00587a20.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-dogfood-00587a20-a1/00587a20.json",
    "reconstruction/metadata/pkg-editor-onexit-smoke01/00587a20.json"
  ]
}
```

## 13_semantic_hypotheses

- State: `missing`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

## 14_conflicts_questions

- State: `conflicted`
- Provenance: `reconstruction/knowledge/index.json, knowledgegraph/research/semantic-decomp.json`

```json
{
  "original_bytes": 10568,
  "preview": "{\n  \"conflicts\": [\n    {\n      \"anchors\": [\n        \"0x005737d0\",\n        \"0x00588570\",\n        \"0x0058ac10\",\n        \"0x00b3d350\",\n        \"0x00e818f0\",\n        \"0x00b3d350\",\n        \"0x00e818f0\",\n        \"0x00b3d350\",\n        \"0x005737d0\",\n        \"0x00576c50\",\n        \"0x00576c50\",\n        \"0x0057ce80\",\n        \"0x0057ce80\",\n        \"0x00584300\",\n        \"0x00584300\",\n        \"0x00587a20\"\n      ],\n      \"conflict_id\": \"editor_input_routing\",\n      \"kind\": \"conflict_ledger\",\n      \"rejected\": [],\n      \"resolution\": \"The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.\",\n      \"resolution_status\": \"The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.\",\n      \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n      \"subject\": null,\n      \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n    },\n    {\n      \"anchors\": [\n        \"0x005737d0\",\n        \"0x005737d0\",\n        \"0x00576c50\",\n        \"0x00576c50\",\n        \"0x0057ce80\",\n        \"0x0057ce80\",\n        \"0x00584300\",\n        \"0x00584300\",\n        \"0x00587270\",\n        \"0x00587270\",\n        \"0x00587a20\",\n        \"0x00587a20\",\n        \"0x00588570\",\n        \"0x00588570\",\n        \"0x0058ac10\",\n        \"0x0058ac10\"\n      ],\n      \"confl
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'ref': 'ephemeral reconstruction_knowledge.build_index', 'mode': 'derived', 'source_class': 'generated_index'}, {'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditor__OnExit.c', 'mode': 'persisted', 'source_class': 'committed_artifact'}, {'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'mode': 'persisted', 'source_class': 'committed_artifact'}, {'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'mode': 'persisted', 'source_class': 'committed_artifact'}, {'ref': 'reconstruction/metadata/pkg-dogfood-00587a20-a1/00587a20.json', 'mode': 'persisted', 'source_class': 'committed_artifact'}, {'ref': 'reconstruction/metadata/pkg-editor-onexit-smoke01/00587a20.json', 'mode': 'persisted', 'source_class': 'committed_artifact'}, {'ref': 'reconstruction/staging/pkg-dogfood-00587a20-a1/editor_onexit_00587a20.cpp', 'mode': 'persisted', 'source_class': 'committed_artifact'}, {'ref': 'reconstruction/staging/pkg-dogfood-00587a20-a1/editor_onexit_00587a20.hpp', 'mode': 'persisted', 'source_class': 'committed_artifact'}, {'ref': 'reconstruction/staging/pkg-editor-onexit-smoke01/editor_onexit_00587a20.cpp', 'mode': 'persisted', 'source_class': 'committed_artifact'}, {'ref': 'reconstruction/staging/pkg-editor-onexit-smoke01/editor_onexit_00587a20.hpp', 'mode': 'persisted', 'source_class': 'committed_artifact'}`

```json
{
  "provenance": [
    {
      "mode": "derived",
      "ref": "ephemeral reconstruction_knowledge.build_index",
      "source_class": "generated_index"
    },
    {
      "mode": "persisted",
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditor__OnExit.c",
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
      "ref": "reconstruction/metadata/pkg-dogfood-00587a20-a1/00587a20.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg-editor-onexit-smoke01/00587a20.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-dogfood-00587a20-a1/editor_onexit_00587a20.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-dogfood-00587a20-a1/editor_onexit_00587a20.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-editor-onexit-smoke01/editor_onexit_00587a20.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-editor-onexit-smoke01/editor_onexit_00587a20.
[TRUNCATED]
```
