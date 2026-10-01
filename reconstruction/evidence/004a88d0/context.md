# Reconstruction context 0x004a88d0

- Status: `partial`
- Content SHA-256: `6f21dc201e91edd597fb6aaea73e848e75a80af3e7c079055253b03b64312f2d`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x004a88d0",
  "phase": "reconstruction",
  "target": "0x004a88d0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": null,
  "package": null,
  "subsystem": null,
  "va": "0x004a88d0"
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
  "status": "unresolved"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "7c339cda171bf81827e519d7a02dbc741acd9dc175394ae51cc8b29f91870e41",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x004a88d0 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "__cdecl",
  "hidden_receiver": "absent - the body never reads ECX and the callers never load one",
  "hidden_this_register": null,
  "ordinary_stack_argument_slots": 1,
  "receiver": false,
  "ret_form": "RET",
  "return_observation": "EAX is used only as the intermediate result of the first callee and as the pushed copy of the argument at 0x004a88db; it is dead on exit. No caller reads EAX after any of the recorded callsites.",
  "return_register": null,
  "return_semantics": "void",
  "return_type": "void",
  "return_width_bytes": 0,
  "saved_registers": [
    "EBP"
  ],
  "stack_arguments": [
    {
      "entry_offset": "EBP+0x8",
      "name": "event_tag",
      "role": "forwarded as the value of the record key 0x03475381; every inspected callsite pushes a 32-bit hash-like literal, e.g. 0x00A03E74B2, 0x00C355901A, 0x00D2C7F386, 0x002570AE6D, 0x00677F1FB8",
      "type": "std::uint32_t",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "0x004a88eb RET"
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
      "va": "0x0043c710"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0043cad0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00573c00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00577580"
    },
    {
      "name": "editor_input_00588570",
      "reconstructed": true,
      "va": "0x00588570"
    },
    {
      "name": "editor_input_0058b650",
      "reconstructed": true,
      "va": "0x0058b650"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00591690"
    },
    {
      "name": "Editors::cEditor::HandleMessage",
      "reconstructed": false,
      "va": "0x00591fa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005a63d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005b8fb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005bc0f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005bccc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005c3cb0"
    },
    {
      "name": "palette_select_category_005cb240",
      "reconstructed": true,
      "va": "0x005cb240"
    },
    {
      "name": "FUN_005dda30",
      "reconstructed": true,
      "va": "0x005dda30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005def30"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x0043c9f
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "std::uint32_t",
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
      "A runtime differential test is required to (a) observe the singleton being installed, (b) capture the concrete implementations behind slots +0x20, +0x38, +0x40 and +0x58, and (c) read the three key strings out of the sibling module once that module is available. Without (a) the static observation that the function is a no-op in the imported image says nothing about the shipping build.",
      "No original-process trace has ever been captured for this function; the original Cell stage has never been entered in any recorded run. Every claim here is static.",
      "The undo/redo inference additionally requires observing a listener that reacts to the emitted record."
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
      "va": "0x0043c710"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0043cad0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00573c00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00577580"
    },
    {
      "name": "editor_input_00588570",
      "reconstructed": true,
      "va": "0x00588570"
    },
    {
      "name": "editor_input_0058b650",
      "reconstructed": true,
      "va": "0x0058b650"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00591690"
    },
    {
      "name": "Editors::cEditor::HandleMessage",
      "reconstructed": false,
      "va": "0x00591fa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005a63d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005b8fb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005bc0f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005bccc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005c3cb0"
    },
    {
      "name": "palette_select_category_005cb240",
      "reconstructed": true,
      "va": "0x005cb240"
    },
    {
      "name": "FUN_005dda30",
      "reconstructed": true,
      "va": "0x005dda30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005def30"
    },
    {
      "name": null,
[TRUNCATED]
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-EDITOR-INPUT-WAVE6",
    "score": 3,
    "symbol": "editor_input_00588570",
    "va": "0x00588570"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-EDITOR-INPUT-WAVE6",
    "score": 3,
    "symbol": "editor_input_0058b650",
    "va": "0x0058b650"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-15-EDITOR-SUPPORT",
    "score": 3,
    "symbol": "palette_select_category_005cb240",
    "va": "0x005cb240"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-10-EDITOR-DISPATCH",
    "score": 3,
    "symbol": "FUN_005dda30",
    "va": "0x005dda30"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-10-EDITOR-DISPATCH",
    "score": 3,
    "symbol": "editor_query_dispatch_005dfd00",
    "va": "0x005dfd00"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-10-EDITOR-DISPATCH",
    "score": 3,
    "symbol": "Editors_EditorUI_HandleMessage_005e0000",
    "va": "0x005e0000"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-EDITOR-SAFE-WAVE11",
    "score": 2,
    "symbol": "editor_bake_probe_004bf770",
    "va": "0x004bf770"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-SIMULATOR-SAFE-WAVE11",
    "score": 2,
    "symbol": "dispatch_key_00628450",
    "va": "0x00628450"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/wave13-pilot-dispatch-b00/editor_004a88d0.cpp",
    "reconstruction/staging/wave13-pilot-dispatch-b00/editor_004a88d0.hpp",
    "reconstruction/staging/wave13-pilot-dispatch-b00/editor_004a88d0_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-pilot-dispatch-b00/004a88d0.json"
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
    "A runtime differential test is required to (a) observe the singleton being installed, (b) capture the concrete implementations behind slots +0x20, +0x38, +0x40 and +0x58, and (c) read the three key strings out of the sibling module once that module is available. Without (a) the static observation that the function is a no-op in the imported image says nothing about the shipping build.",
    "Does the tag have a stable public meaning, or is it a per-build hash of a source identifier? Every inspected argument is an opaque 32-bit value with no accompanying string, and no decoding table was found.",
    "Is the record an undo/redo transaction, a change notification, or a telemetry event? The call sites immediately preceding cEditor::Undo and cEditor::Redo make an undo/redo reading the most economical, but the +0x38 and +0x40 targets are unresolved, so this stays INFERRED.",
    "No original-process trace has ever been captured for this function; the original Cell stage has never been entered in any recorded run. Every claim here is static.",
    "The undo/redo inference additionally requires observing a listener that reacts to the emitted record.",
    "What class is behind DAT_0166D9F4? Its shape - slot +0x20 returning a context value, +0x38 taking a scope name, +0x3C/+0x40 taking key/value pairs, +0x58 closing, and +0xC4 as a no-argument update called from 0x00a228b0 - is observed, but no SDK header matches it and no vtable for it was located. Spore/App/IMessageManager.h was read and rejected: its +0x38 is ProcessQueue2() 
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-pilot-dispatch-b00/004a88d0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-pilot-dispatch-b00/editor_004a88d0.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-pilot-dispatch-b00/editor_004a88d0.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-pilot-dispatch-b00/editor_004a88d0_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave13-pilot-dispatch-b00/004a88d0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-pilot-dispatch-b00/editor_004a88d0.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-pilot-dispatch-b00/editor_004a88d0.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-pilot-dispatch-b00/editor_004a88d0_model_test.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction
[TRUNCATED]
```
