# Reconstruction context 0x007c3c20

- Status: `partial`
- Content SHA-256: `a9aa03972d1b2ec7c49101590042f7c2271e769690f9abaa3b5749b2b58bc700`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x007c3c20",
  "phase": "reconstruction",
  "target": "0x007c3c20"
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
  "va": "0x007c3c20"
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
  "status": "unresolved"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "d96c2299c22f94e19e2b4161b27fedd6d668be4198305141faa93f1b025f731b",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x007c3c20 failed: Decompilation did not complete. Reason: ",
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
  "hidden_this_register": "ECX",
  "hidden_this_type": "OpaqueWorldViewer*",
  "return_register": null,
  "return_type": "void",
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "source",
      "position": 1,
      "type": "const std::uint32_t*",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 4,
  "termination": "RET 0x4"
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
      "va": "0x005812b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006e3100"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006e4210"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006efe90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006f3f20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006f41e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0076bc91"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0076c210"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0077f040"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007b3340"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007b7ac0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007b8cb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007bd750"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007bfee0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007c0780"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007c6200"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x005813aa",
      "direction": "in",
      "other": "0x005812b0",
      "reference_type": "direct-call"
    },

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
    "const std::uint32_t*",
    "void"
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
      "va": "0x005812b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006e3100"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006e4210"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006efe90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006f3f20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006f41e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0076bc91"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0076c210"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0077f040"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007b3340"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007b7ac0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007b8cb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007bd750"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007bfee0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007c0780"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007c6200"
    },
    {
      "name": "App::cCameraManager::SetActiveCameraByID",
      "reconstructed": false,
      "va": "0x007c6750"
    },
  
[TRUNCATED]
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "shared_types:const std::uint32_t*"
    ],
    "package": "PKG-PALETTE-SAFE-WAVE11",
    "score": 3,
    "symbol": "palette_safe_wave11_fill_node_array_005c7ff0",
    "va": "0x005c7ff0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-EDITOR-RUNTIME-WAVE7",
    "score": 2,
    "symbol": "EditorCreatureController_SetTargetPosition_0059b0f0",
    "va": "0x0059b0f0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-EDITOR-RUNTIME-WAVE7",
    "score": 2,
    "symbol": "EditorCreatureController_Update_0059b4b0",
    "va": "0x0059b4b0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-EDITOR-RUNTIME-WAVE7",
    "score": 2,
    "symbol": "EditorAnimWorld_GetCreatureController_0059cac0",
    "va": "0x0059cac0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-EDITOR-RUNTIME-WAVE7",
    "score": 2,
    "symbol": "EditorAnimWorld_PlayAnimation_0059cb10",
    "va": "0x0059cb10"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-EDITOR-RUNTIME-WAVE7",
    "score": 2,
    "symbol": "EditorAnimWorld_SetTargetAngle_0059cea0",
    "va": "0x0059cea0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-EDITOR-RUNTIME-WAVE7",
    "score": 2,
    "symbol": "EditorAnimWorld_SetTargetPosition_0059cf00",
    "va": "0x0059cf00"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-RUNTIME-SERVICES-WAVE7
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg14-a1-world-state/world_state.cpp",
    "reconstruction/staging/pkg14-a1-world-state/world_state.hpp",
    "reconstruction/staging/pkg14-a1-world-state/world_state_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg14-a1-world-state/007c3c20.json"
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
    "Caller receiver types are not assumed to be identical merely because they reach this common helper.",
    "The four-word block has no proven color, terrain, or renderer semantic identity from this function alone."
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg14-a1-world-state/007c3c20.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg14-a1-world-state/world_state.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg14-a1-world-state/world_state.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg14-a1-world-state/world_state_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg14-a1-world-state/007c3c20.json",
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
      "ref": "reconstruction/staging/pkg14-a1-world-state/world_state_model_test.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.json"
  ],
  "r
[TRUNCATED]
```
