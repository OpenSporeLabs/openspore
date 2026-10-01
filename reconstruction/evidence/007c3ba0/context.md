# Reconstruction context 0x007c3ba0

- Status: `partial`
- Content SHA-256: `62ee46b0148e3e09ee36d915524ffa2e8e7e9725fa9688fefbe24731b7658f0e`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x007c3ba0",
  "phase": "reconstruction",
  "target": "0x007c3ba0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_007c3ba0",
  "package": null,
  "subsystem": "Terrain",
  "va": "0x007c3ba0"
}
```

## 03_current_status

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "blocked": false,
  "reconstructed": false,
  "runtime_gated": false,
  "runtime_validated": 0,
  "status": "candidate"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "1ee180d8d4b26e43002937796c85d8ce8cd50a1fc37daba032cc565be0c9e90d",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x007c3ba0 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": [
    "__thiscall",
    "thiscall"
  ],
  "hidden_this": true,
  "hidden_this_register": "ECX",
  "hidden_this_type": "OpaqueWorldViewer*",
  "receiver_register": "ECX",
  "ret_form": "RET",
  "return_register": "EAX",
  "return_semantics": "integral_in_EAX",
  "return_type": "std::uint8_t",
  "return_width_bytes": 1,
  "saved_registers": [
    "ESI"
  ],
  "stack_arguments": [],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "RET"
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
      "va": "0x00430e70"
    },
    {
      "name": "Editors::cEditor::Dispose",
      "reconstructed": false,
      "va": "0x00576c50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006f0890"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006f5260"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006f9cf0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0076b000"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0076b5d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0076b840"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00777060"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0077f210"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007b29a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007b77a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007b9620"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007b9e80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007bd540"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007bd640"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00432347",
      "direction": "in",
      "other": "0x00430e70",
      "reference_type"
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "OpaqueWorldViewer*",
    "cViewer",
    "std::uint8_t"
  ],
  "vtables": []
}
```

## 09_state_event_relationships

- State: `missing`
- Provenance: `knowledgegraph/research/semantic-decomp.json, reconstruction/knowledge/index.json`

```json
{
  "runtime": {
    "blocking_reason": null,
    "gates": [],
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
      "va": "0x00430e70"
    },
    {
      "name": "Editors::cEditor::Dispose",
      "reconstructed": false,
      "va": "0x00576c50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006f0890"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006f5260"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006f9cf0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0076b000"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0076b5d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0076b840"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00777060"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0077f210"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007b29a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007b77a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007b9620"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007b9e80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007bd540"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007bd640"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007bd6b0"
    },
    {
      "name
[TRUNCATED]
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "pkg-swarm-w1-00f9b7f0",
    "score": 6,
    "symbol": "re_00f9b7f0",
    "va": "0x00f9b7f0"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg14-a1-world-state/world_state.cpp",
    "reconstruction/staging/pkg14-a1-world-state/world_state.hpp",
    "reconstruction/staging/pkg14-a1-world-state/world_state_model_test.cpp",
    "reconstruction/staging/pkg_editor_007c3ba0/editor_007c3ba0.cpp",
    "reconstruction/staging/pkg_editor_007c3ba0/editor_007c3ba0.hpp",
    "reconstruction/staging/pkg_editor_007c3ba0/editor_007c3ba0_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-editor-007c3ba0/007c3ba0.json",
    "reconstruction/metadata/pkg14-a1-world-state/007c3ba0.json"
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
    "No runtime trace of the original exists (categories.runtime MISSING), so every behavioural claim here is static-evidence only.",
    "Subsystem attribution conflicts: the worker assignment says Editors (cEditor teardown neighbourhood, with Editors::cEditor::Dispose among the callers) while the persisted triage record and the briefing both say Terrain. The evidence does not settle it.",
    "The bodies of 0x00f47380 and 0x00f47410 are not in the evidence pack, so they remain declared cdecl ports with inert defaults rather than reconstructed routines. What they release, and whether the release is refcount-aware, is unknown.",
    "The concrete type and ownership of the 32-bit word at receiver+0x158 are not established. It is only ever loaded, compared, pushed to 0x00f47380 and zeroed; the decompiler types the call argument as undefined4, so the model keeps it an opaque std::uint32_t rather than asserting a pointer.",
    "The concrete type and ownership of the 32-bit word at receiver+0x170 are likewise not established; it is loaded, tested, pushed to 0x00f47410 and zeroed.",
    "The concrete type and ownership of the object at receiver+0x158 are not established by this body.",
    "The decompiler prints __fastcall with a single ECX-assigned parameter while the derived and persisted ABI both say thiscall; the listing is followed, but the decompiler's own convention for this function was never corrected in Ghidra, so any downstream tool reading Ghidra's signature for 0x007c3ba0 will still see __fastcall.",
    "The real nam
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-editor-007c3ba0/007c3ba0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg14-a1-world-state/007c3ba0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg14-a1-world-state/world_state.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg14-a1-world-state/world_state.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg14-a1-world-state/world_state_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg_editor_007c3ba0/editor_007c3ba0.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg_editor_007c3ba0/editor_007c3ba0.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg_editor_007c3ba0/editor_007c3ba0_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-editor-007c3ba0/007c3ba0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg14-a1-world-state/007c3ba0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg14-a1-world-state/world_state.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg14-a1-world-state/world_state.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg14-a1-world-s
[TRUNCATED]
```
