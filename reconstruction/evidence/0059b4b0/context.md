# Reconstruction context 0x0059b4b0

- Status: `partial`
- Content SHA-256: `3b201638e9692cc904ca1b5ebae0286061f2a11a3af290028f7f0c08277af74c`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x0059b4b0",
  "phase": "reconstruction",
  "target": "0x0059b4b0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueEditorRuntime",
  "name": "EditorCreatureController_Update_0059b4b0",
  "package": "PKG-EDITOR-RUNTIME-WAVE7",
  "subsystem": "Editor.Runtime",
  "va": "0x0059b4b0"
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
  "content_sha256": "ee0812a68810d1a79a8985233a78463b6a156949e8a4266a900d125b2fe3f41a",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x0059b4b0 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "thiscall",
  "hidden_this": "OpaqueController * in ECX",
  "return_register": null,
  "return_type": "void",
  "return_width_bytes": 0,
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "dt",
      "position": 1,
      "type": "std::int32_t",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "caller"
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
      "va": "0x0059d610"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x0059d723",
      "direction": "in",
      "other": "0x0059d610",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0059bc9e",
      "direction": "out",
      "other": "0x00436ce0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0059ba99",
      "direction": "out",
      "other": "0x00576b00",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0059bd3c",
      "direction": "out",
      "other": "0x0059ab70",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0059ba1f",
      "direction": "out",
      "other": "0x0059ac00",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0059ba2f",
      "direction": "out",
      "other": "0x0059ac00",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0059ba3b",
      "direction": "out",
      "other": "0x0059ac00",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0059bd12",
      "direction": "out",
      "other": "0x0059aed0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0059b549",
      "direction": "out",
      "other": "0x0059b390",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0059b51c",
      "direction": "out",
      "other": "0x0067cb20",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0059befa",
      "direction": "out",
      "other":
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "OpaqueEditorRuntime",
    "std::int32_t",
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
      "Runtime values of the injected basis words 0x015e5a0c/0x10/0x14, 0x015e5a88/0x8c/0x90 and 0x015e590c/0x015e5910/0x015e5914, which read as zero in the file image",
      "Semantics of the 0x00699600, 0x0069b840 and 0x0069b760 helpers (lerp, angle lerp and projection are inferred from usage, not owned)",
      "Semantics of the 0x00699600, 0x0069b840 and 0x0069b760 helpers (lerp, angle lerp and projection are inferred from usage, not owned); Runtime values of the injected basis words 0x015e5a0c/0x10/0x14, 0x015e5a88/0x8c/0x90 and 0x015e590c/0x015e5910/0x015e5914, which read as zero in the file image; The four-argument contract of the creature bounds callback beyond the two output slots and two literal zeros; The AnimatedCreature vtable at controller+0x08 and its slots 0x58 and 0x5c; The eight-slot IShadowWorld raycast argument record; The picking helper 0x0067dd80 and its vtable slot 0x28 return value; The meaning of controller+0x1c and of the 0x0059b390 publication port; Whether a zero-length current offset is reachable; the binary produces 1.0f/0.0f = +inf and then 0.0f*inf = NaN, which this reconstruction reproduces but does not test numerically",
      "The AnimatedCreature vtable at controller+0x08 and its slots 0x58 and 0x5c",
      "The eight-slot IShadowWorld raycast argument record",
      "The four-argument contract of the creature bounds callback beyond the two output slots and two literal zeros",
      "The meaning of controller+0x1c and of the 0x0059b390 publication port",
      "The picking help
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
      "va": "0x0059d610"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x0059d723",
      "direction": "in",
      "other": "0x0059d610",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0059bc9e",
      "direction": "out",
      "other": "0x00436ce0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0059ba99",
      "direction": "out",
      "other": "0x00576b00",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0059bd3c",
      "direction": "out",
      "other": "0x0059ab70",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0059ba1f",
      "direction": "out",
      "other": "0x0059ac00",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0059ba2f",
      "direction": "out",
      "other": "0x0059ac00",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0059ba3b",
      "direction": "out",
      "other": "0x0059ac00",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0059bd12",
      "direction": "out",
      "other": "0x0059aed0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0059b549",
      "direction": "out",
      "other": "0x0059b390",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0059b51c",
      "direction": "out",
      "other": "0x0067cb20",
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
      "same_package",
      "same_subsystem",
      "same_class",
      "shared_types:OpaqueEditorRuntime",
      "same_calling_convention"
    ],
    "package": "PKG-EDITOR-RUNTIME-WAVE7",
    "score": 24,
    "symbol": "EditorCreatureController_SetTargetPosition_0059b0f0",
    "va": "0x0059b0f0"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "same_class",
      "shared_types:OpaqueEditorRuntime",
      "same_calling_convention"
    ],
    "package": "PKG-EDITOR-RUNTIME-WAVE7",
    "score": 24,
    "symbol": "EditorAnimWorld_GetCreatureController_0059cac0",
    "va": "0x0059cac0"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "same_class",
      "shared_types:OpaqueEditorRuntime",
      "same_calling_convention"
    ],
    "package": "PKG-EDITOR-RUNTIME-WAVE7",
    "score": 24,
    "symbol": "EditorAnimWorld_PlayAnimation_0059cb10",
    "va": "0x0059cb10"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "same_class",
      "shared_types:OpaqueEditorRuntime",
      "same_calling_convention"
    ],
    "package": "PKG-EDITOR-RUNTIME-WAVE7",
    "score": 24,
    "symbol": "EditorAnimWorld_SetTargetAngle_0059cea0",
    "va": "0x0059cea0"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "same_class",
      "shared_types:OpaqueEditorRuntime",
      "same_calling_convention"
    ],
    "package": "PKG-EDITOR-RUNTIME-WAVE7",
    "score": 24,
    "symbol": "EditorAnimWorld_SetTargetPosition_0059cf00",
    "va": "0x0059cf0
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg_editor_runtime_wave7/editor_runtime_wave7.cpp",
  "files": [
    "src/reconstruction/pkg_editor_runtime_wave7/editor_runtime_wave7.cpp",
    "src/reconstruction/pkg_editor_runtime_wave7/editor_runtime_wave7.hpp",
    "src/reconstruction/pkg_editor_runtime_wave7/editor_runtime_wave7_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave7/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-editor-runtime-wave7/0059b4b0.json"
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
    "Runtime values of the injected basis words 0x015e5a0c/0x10/0x14, 0x015e5a88/0x8c/0x90 and 0x015e590c/0x015e5910/0x015e5914, which read as zero in the file image",
    "Semantics of the 0x00699600, 0x0069b840 and 0x0069b760 helpers (lerp, angle lerp and projection are inferred from usage, not owned)",
    "Semantics of the 0x00699600, 0x0069b840 and 0x0069b760 helpers (lerp, angle lerp and projection are inferred from usage, not owned); Runtime values of the injected basis words 0x015e5a0c/0x10/0x14, 0x015e5a88/0x8c/0x90 and 0x015e590c/0x015e5910/0x015e5914, which read as zero in the file image; The four-argument contract of the creature bounds callback beyond the two output slots and two literal zeros; The AnimatedCreature vtable at controller+0x08 and its slots 0x58 and 0x5c; The eight-slot IShadowWorld raycast argument record; The picking helper 0x0067dd80 and its vtable slot 0x28 return value; The meaning of controller+0x1c and of the 0x0059b390 publication port; Whether a zero-length current offset is reachable; the binary produces 1.0f/0.0f = +inf and then 0.0f*inf = NaN, which this reconstruction reproduces but does not test numerically",
    "The AnimatedCreature vtable at controller+0x08 and its slots 0x58 and 0x5c",
    "The eight-slot IShadowWorld raycast argument record",
    "The four-argument contract of the creature bounds callback beyond the two output slots and two literal zeros",
    "The meaning of controller+0x1c and of the 0x0059b390 publication port",
    "The picking helper 0x0067dd80 and its vtable
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave7/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-editor-runtime-wave7/0059b4b0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_editor_runtime_wave7/editor_runtime_wave7.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_editor_runtime_wave7/editor_runtime_wave7.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_editor_runtime_wave7/editor_runtime_wave7_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/integrated/batch-2026-09-25-wave7/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg-editor-runtime-wave7/0059b4b0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_editor_runtime_wave7/editor_runtime_wave7.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_editor_runtime_wave7/editor_runtime_wave7.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstru
[TRUNCATED]
```
