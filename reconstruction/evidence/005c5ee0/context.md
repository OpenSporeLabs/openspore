# Reconstruction context 0x005c5ee0

- Status: `partial`
- Content SHA-256: `a954aa6cb4d39cdcd150f33d61f1a6725c078ea19f32df620082086be87862f5`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x005c5ee0",
  "phase": "reconstruction",
  "target": "0x005c5ee0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "Palettes::PaletteMain::GetCategory",
  "package": null,
  "subsystem": "Palettes",
  "va": "0x005c5ee0"
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
  "content_sha256": "a50c758fe8c544353e6ac7f6daad2b209c0e0a2ba806aa21923b0684ed18f565",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x005c5ee0 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "thiscall",
  "hidden_receiver": "ECX is the receiver word, copied to ESI at 0x005c5ee1 and returned in EAX at 0x005c5ef8",
  "ordinary_stack_argument_slots": 1,
  "ret_form": "RET 0x4",
  "return_register": "EAX",
  "return_semantics": "returns the receiver word itself; MOV EAX,ESI at 0x005c5ef8 runs on both the release and the skip path, and the EAX result of the 0x005c5e90 call is discarded",
  "return_type": "OpaquePaletteMain*",
  "return_width_bytes": 4,
  "saved_registers": [
    "ESI"
  ],
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04, read as ESP+0x08 after the PUSH ESI at 0x005c5ee0",
      "machine_type": "opaque_dword",
      "native_use": "only the low byte is read, by TEST byte ptr [ESP+0x8],0x1 at 0x005c5ee8",
      "normalized_name": "stack_word",
      "position": 1,
      "width_bytes": 4
    }
  ],
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
      "callsite": "0x005c5ee3",
      "direction": "out",
      "other": "0x005c5e90",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005c5ef0",
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
  "globals": [
    "global:high"
  ],
  "types": [
    "DATA",
    "OpaquePaletteMain*",
    "UNCONDITIONAL_CALL",
    "openspore::reconstruction::pkg_orchestrate_dogfood_005c5ee0::GetCategoryPorts",
    "openspore::reconstruction::pkg_orchestrate_dogfood_005c5ee0::OpaquePaletteMain",
    "openspore::reconstruction::pkg_orchestrate_dogfood_005c5ee0::OpaquePaletteMainGetCategory005c5ee0",
    "openspore::reconstruction::pkg_orchestrate_dogfood_005c5ee0::OpaquePaletteMainRelease00f47380",
    "openspore::reconstruction::pkg_orchestrate_dogfood_005c5ee0::OpaquePaletteMainSubobjectVtable",
    "openspore::reconstruction::pkg_orchestrate_dogfood_005c5ee0::OpaquePaletteMainTeardown005c5e90",
    "openspore::reconstruction::pkg_orchestrate_dogfood_005c5ee0::OpaquePaletteMainVtable"
  ],
  "vtables": [
    "vtable:0x013f7fc4",
    "vtable:0x013f7fd4"
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
      "Capture both stack-word polarities at a real call site and confirm that only bit 0 decides the release.",
      "Confirm the returned EAX is the receiver word on the release path, where the receiver has just been handed to the release wrapper.",
      "Determine the class and base-subobject binding of the vtables at 0x013f7fd4 and 0x013f7fc4, and the role of the word at 0x013f7fd8.",
      "Observe 0x005c5e90 live: its loop, the callees it invokes, and the values of the words it reads at receiver+0x04 and receiver+0x0c.",
      "Observe a real virtual dispatch through the word at 0x013f7fd4 and through the subobject slot at 0x013f7fcc, and record which of the two produced the entry call and with which receiver word.",
      "Record the receiver words at +0x00, +0x04 and +0x08 before and after the call and confirm that the entry itself leaves all three unchanged.",
      "Resolve whether the original source identifier, argument name, and return type match the imported SDK label or the destructor-shaped reading of the body."
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
      "callsite": "0x005c5ee3",
      "direction": "out",
      "other": "0x005c5e90",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005c5ef0",
      "direction": "out",
      "other": "0x00f47380",
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
    "id": "scc-0117",
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
      "shared_types:DATA,UNCONDITIONAL_CALL"
    ],
    "package": "PKG-18-UI-SCRIPTING",
    "score": 6,
    "symbol": "FUN_005bf9d0",
    "va": "0x005bf9d0"
  },
  {
    "match_basis": [
      "shared_types:DATA,UNCONDITIONAL_CALL"
    ],
    "package": "PKG-18-UI-SCRIPTING",
    "score": 6,
    "symbol": "FUN_005c0100",
    "va": "0x005c0100"
  },
  {
    "match_basis": [
      "shared_types:DATA,UNCONDITIONAL_CALL"
    ],
    "package": "PKG-18-UI-SCRIPTING",
    "score": 6,
    "symbol": "FUN_005c0380",
    "va": "0x005c0380"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-15-EDITOR-SUPPORT",
    "score": 6,
    "symbol": "palette_application_setup_005c53c0",
    "va": "0x005c53c0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-15-EDITOR-SUPPORT",
    "score": 6,
    "symbol": "palette_page_construct_005c9230",
    "va": "0x005c9230"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-15-EDITOR-SUPPORT",
    "score": 6,
    "symbol": "palette_select_category_005cb240",
    "va": "0x005cb240"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-15-EDITOR-SUPPORT",
    "score": 6,
    "symbol": "palette_editor_construct_loop_005cb5a0",
    "va": "0x005cb5a0"
  },
  {
    "match_basis": [
      "shared_types:DATA,UNCONDITIONAL_CALL"
    ],
    "package": "wave6-resources",
    "score": 6,
    "symbol": "property_list_has_property_006a2470",
    "va": "0x006a2470"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Palettes__PaletteMain__GetCategory.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Palettes__PaletteMain__GetCategory.c",
    "reconstruction/staging/pkg-orchestrate-dogfood-005c5ee0/dogfood_005c5ee0.cpp",
    "reconstruction/staging/pkg-orchestrate-dogfood-005c5ee0/dogfood_005c5ee0.hpp",
    "reconstruction/staging/pkg-orchestrate-dogfood-005c5ee0/dogfood_005c5ee0_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-orchestrate-dogfood-005c5ee0/005c5ee0.json"
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
    "Can the returned EAX be a released pointer in the original program, and does any caller use it after the release?",
    "Capture both stack-word polarities at a real call site and confirm that only bit 0 decides the release.",
    "Confirm the returned EAX is the receiver word on the release path, where the receiver has just been handed to the release wrapper.",
    "Determine the class and base-subobject binding of the vtables at 0x013f7fd4 and 0x013f7fc4, and the role of the word at 0x013f7fd8.",
    "Is the entry a deleting destructor, a hand-written release wrapper, or an accessor that the SDK symbol importer mislabeled? The machine mechanics are identical in all three cases, so the classification is unresolved.",
    "Observe 0x005c5e90 live: its loop, the callees it invokes, and the values of the words it reads at receiver+0x04 and receiver+0x0c.",
    "Observe a real virtual dispatch through the word at 0x013f7fd4 and through the subobject slot at 0x013f7fcc, and record which of the two produced the entry call and with which receiver word.",
    "Record the receiver words at +0x00, +0x04 and +0x08 before and after the call and confirm that the entry itself leaves all three unchanged.",
    "Resolve whether the original source identifier, argument name, and return type match the imported SDK label or the destructor-shaped reading of the body.",
    "The briefing carried no ABI section (evidence.missing_sections listed ABI), so the recorded ABI is derived from the eleven-instruction disassembly plus read-only live G
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/Palettes__PaletteMain__GetCategory.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-orchestrate-dogfood-005c5ee0/005c5ee0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-orchestrate-dogfood-005c5ee0/dogfood_005c5ee0.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-orchestrate-dogfood-005c5ee0/dogfood_005c5ee0.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-orchestrate-dogfood-005c5ee0/dogfood_005c5ee0_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/Palettes__PaletteMain__GetCategory.c",
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
      "ref": "reconstruction/metadata/pkg-orchestrate-dogfood-005c5ee0/005c5ee0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-orchestrate-dogfood-005c5ee0/dogfood_005c5ee0.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-orchestrate-dogfood-005c5ee0/dogfood_005c5ee0.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mo
[TRUNCATED]
```
