# Reconstruction context 0x0041e8b0

- Status: `partial`
- Content SHA-256: `bb0f0c4b57c8ff33695765ebb56de7828fb16dd97685a4c0121c3b38f76ceb2a`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x0041e8b0",
  "phase": "reconstruction",
  "target": "0x0041e8b0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueCursorBuffer",
  "name": "cursor_buffer_emit_0041e8b0",
  "package": "PKG-APP-SAFE-WAVE10",
  "subsystem": "App.CursorBuffer",
  "va": "0x0041e8b0"
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
  "content_sha256": "5b9251a237bf07b467fa67e8e6edeed39154cef50cff2cb6e02fffb89b450ce4",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x0041e8b0 failed: Decompilation did not complete. Reason: ",
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
      "entry_offset": "EBP+0x08",
      "machine_type": "std::uint32_t",
      "native_reads": [
        "PUSH EAX at 0x0041e8ee for the copy port",
        "PUSH ECX at 0x0041e908 for the grow port"
      ],
      "normalized_name": "argument",
      "note": "the word is used as an opaque source pointer, not as a count",
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
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00407280"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0041aaa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0046aac0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00471000"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00471830"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00471b50"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00407b08",
      "direction": "in",
      "other": "0x00407280",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0041b1a4",
      "direction": "in",
      "other": "0x0041aaa0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0046adbd",
      "direction": "in",
      "other": "0x0046aac0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0047138a",
      "direction": "in",
      "other": "0x00471000",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00471a71",
      "direction": "in",
      "other": "0x00471830",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00471e13",
      "direction": "in",
      "other": "0x00471b50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0041e913",
      "direction": "out",
      "other": "0x00424010",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0041e8f2",
      "direction": 
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "CursorRuntime",
    "OpaqueCursorBuffer",
    "OpaqueCursorBuffer*",
    "OpaqueCursorElement",
    "unsigned int",
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
      "The 0x18 element stride comes from the ADD EAX,0x18 immediate; the element size is not independently confirmed.",
      "The argument is modelled as an opaque source pointer; its declared type is unresolved.",
      "The cursor buffer base word at +0x00 is never read or written by this body.",
      "The element copy port 0x00511140 and the grow port 0x00424010 are opaque seams and are not promoted.",
      "gate-cursor-buffer-emit-runtime-port-semantics",
      "runtime validation not performed; static decompilation and disassembly only",
      "the 0x18 element stride is a static constant read from the ADD EAX,0x18 immediate; the element size is not independently confirmed",
      "the argument is modelled as an opaque source pointer; its declared type is unresolved",
      "the cursor buffer base word at +0x00 is never read or written by this body",
      "the element copy port 0x00511140 and the grow port 0x00424010 are opaque seams and are not promoted"
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
      "va": "0x00407280"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0041aaa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0046aac0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00471000"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00471830"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00471b50"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00407b08",
      "direction": "in",
      "other": "0x00407280",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0041b1a4",
      "direction": "in",
      "other": "0x0041aaa0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0046adbd",
      "direction": "in",
      "other": "0x0046aac0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0047138a",
      "direction": "in",
      "other": "0x00471000",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00471a71",
      "direction": "in",
      "other": "0x00471830",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00471e13",
      "direction": "in",
      "other": "0x00471b50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0041e913",
      "direction": "out",
      "other": "0x00424010",
      "reference_
[TRUNCATED]
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "same_package"
    ],
    "package": "PKG-APP-SAFE-WAVE10",
    "score": 8,
    "symbol": "vector3_add_0041dc10",
    "va": "0x0041dc10"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "PKG-APP-SAFE-WAVE10",
    "score": 8,
    "symbol": "property_value_resolve_0041e920",
    "va": "0x0041e920"
  },
  {
    "match_basis": [
      "shared_types:unsigned int",
      "same_calling_convention"
    ],
    "package": "PKG-SKINNER-SAFE-WAVE10",
    "score": 5,
    "symbol": "skin_painter_state_setup_00506590",
    "va": "0x00506590"
  },
  {
    "match_basis": [
      "shared_types:unsigned int",
      "same_calling_convention"
    ],
    "package": "PKG-EDITOR-SAFE-WAVE10",
    "score": 5,
    "symbol": "editor_row_publish_005a2010",
    "va": "0x005a2010"
  },
  {
    "match_basis": [
      "shared_types:unsigned int",
      "same_calling_convention"
    ],
    "package": "PKG-PALETTE-SAFE-WAVE10",
    "score": 5,
    "symbol": "page_visible_slots_refresh_005c0a60",
    "va": "0x005c0a60"
  },
  {
    "match_basis": [
      "shared_types:unsigned int",
      "same_calling_convention"
    ],
    "package": "PKG-UI-SAFE-WAVE10",
    "score": 5,
    "symbol": "image_archive_scalar_deleting_destructor_00635700",
    "va": "0x00635700"
  },
  {
    "match_basis": [
      "shared_types:unsigned int"
    ],
    "package": "PKG-APP-SAFE-WAVE11",
    "score": 3,
    "symbol": "property_record_assign_pair_004279d0",
    "va": "0x004279d0"
  },
  {
    "match_basis": [
      "shared_types:unsigned int"
    ],
    "package": "PKG-APP
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg_app_safe_wave10/app_safe_wave10.cpp",
  "files": [
    "src/reconstruction/pkg_app_safe_wave10/app_safe_wave10.cpp",
    "src/reconstruction/pkg_app_safe_wave10/app_safe_wave10.hpp",
    "src/reconstruction/pkg_app_safe_wave10/app_safe_wave10_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave10-safe-core/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-app-safe-wave10/0041e8b0.json"
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
    "The 0x18 element stride comes from the ADD EAX,0x18 immediate; the element size is not independently confirmed.",
    "The argument is modelled as an opaque source pointer; its declared type is unresolved.",
    "The cursor buffer base word at +0x00 is never read or written by this body.",
    "The element copy port 0x00511140 and the grow port 0x00424010 are opaque seams and are not promoted.",
    "What 0x00424010 does with the unadvanced cursor and the limit when the buffer is full",
    "What 0x00511140 copies and whether it can fail",
    "What the argument word actually points to and who owns it",
    "Whether the base word at +0x00 is maintained by the grow port only",
    "Why a zero cursor skips the copy, since the cursor is advanced regardless",
    "gate-cursor-buffer-emit-runtime-port-semantics",
    "runtime validation not performed; static decompilation and disassembly only",
    "the 0x18 element stride is a static constant read from the ADD EAX,0x18 immediate; the element size is not independently confirmed",
    "the argument is modelled as an opaque source pointer; its declared type is unresolved",
    "the cursor buffer base word at +0x00 is never read or written by this body",
    "the element copy port 0x00511140 and the grow port 0x00424010 are opaque seams and are not promoted"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave10-safe-core/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-app-safe-wave10/0041e8b0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_app_safe_wave10/app_safe_wave10.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_app_safe_wave10/app_safe_wave10.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_app_safe_wave10/app_safe_wave10_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-app-safe-wave10/0041e8b0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_app_safe_wave10/app_safe_wave10.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_app_safe_wave10/app_safe_wave10.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_app_
[TRUNCATED]
```
