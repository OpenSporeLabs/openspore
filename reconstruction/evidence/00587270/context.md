# Reconstruction context 0x00587270

- Status: `partial`
- Content SHA-256: `ce7324b2165fdc3639eeb7c7a5fe3c66d878da84c249d5cea10fef73d1e3d582`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00587270",
  "phase": "reconstruction",
  "target": "0x00587270"
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
  "va": "0x00587270"
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
  "content_sha256": "4ddcd5b9682ff17c083266bb47526db5474491ed7104d8111c931e8352f23468",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00587270 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "__thiscall",
  "hidden_this_register": "ECX",
  "return_type": "bool",
  "stack_arguments": [
    {
      "abi_type": "std::uint32_t",
      "entry_offset": "ESP+4",
      "name": "mode",
      "type": "std::uint32_t",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+8",
      "name": "flag",
      "observed_values": [
        0,
        1
      ],
      "type": "uint32_t",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 8
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
      "va": "0x0045ae10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0045b150"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0045b210"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004c49e0"
    },
    {
      "name": "PaintPersistenceBoundary_submit_004c5200",
      "reconstructed": true,
      "va": "0x004c5200"
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
      "name": "EditorAnimWorld_GetCreatureController_0059cac0",
      "reconstructed": true,
      "va": "0x0059cac0"
    },
    {
      "name": "EditorAnimWorld_SetTargetAngle_0059cea0",
      "reconstructed": true,
      "va": "0x0059cea0"
    },
    {
      "name": "EditorAnimWorld_SetTargetPosition_0059cf00",
      "reconstructed": true,
      "va": "0x0059cf00"
    },
    {
      "name": "editor_anim_event_message_send_0059d8b0",
      "reconstructed": true,
      "va": "0x0059d8b0"
    },
    {
      "name": "cEditorAnimEvent__ctor",
      "reconstructed": false,
      "va": "0x0059d960"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0067dcc0"
    }
  ],
  "callers": [
    {
      "name": "Editors::cEditor::OnExit",
      "reconstructed": false,
      "va": "0x00587a20"
    },
    {
     
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "OpaqueEditor for ECX",
    "OpaqueEditorModeManager for the caller-owned this+0x5c relationship",
    "bool",
    "std::uint32_t",
    "std::uint32_t for the first stack argument",
    "uint32_t"
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
  "callees": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0045ae10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0045b150"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0045b210"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004c49e0"
    },
    {
      "name": "PaintPersistenceBoundary_submit_004c5200",
      "reconstructed": true,
      "va": "0x004c5200"
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
      "name": "EditorAnimWorld_GetCreatureController_0059cac0",
      "reconstructed": true,
      "va": "0x0059cac0"
    },
    {
      "name": "EditorAnimWorld_SetTargetAngle_0059cea0",
      "reconstructed": true,
      "va": "0x0059cea0"
    },
    {
      "name": "EditorAnimWorld_SetTargetPosition_0059cf00",
      "reconstructed": true,
      "va": "0x0059cf00"
    },
    {
      "name": "editor_anim_event_message_send_0059d8b0",
      "reconstructed": true,
      "va": "0x0059d8b0"
    },
    {
      "name": "cEditorAnimEvent__ctor",
      "reconstructed": false,
      "va": "0x0059d960"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0067dcc0"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": "Editors::cEditor::OnExit",
      "reconstructed": false,
      "va": "
[TRUNCATED]
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "same_calling_convention",
      "direct_xref_neighbor"
    ],
    "package": "PKG-20-PERSISTENCE-BOUNDARY",
    "score": 5,
    "symbol": "PaintPersistenceBoundary_submit_004c5200",
    "va": "0x004c5200"
  },
  {
    "match_basis": [
      "same_calling_convention",
      "direct_xref_neighbor"
    ],
    "package": "PKG-10-EDITOR-DISPATCH",
    "score": 5,
    "symbol": "FUN_005dda30",
    "va": "0x005dda30"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-EDITOR-RUNTIME-WAVE7",
    "score": 3,
    "symbol": "EditorAnimWorld_GetCreatureController_0059cac0",
    "va": "0x0059cac0"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-EDITOR-RUNTIME-WAVE7",
    "score": 3,
    "symbol": "EditorAnimWorld_SetTargetAngle_0059cea0",
    "va": "0x0059cea0"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-EDITOR-RUNTIME-WAVE7",
    "score": 3,
    "symbol": "EditorAnimWorld_SetTargetPosition_0059cf00",
    "va": "0x0059cf00"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-RUNTIME-SERVICES-WAVE7",
    "score": 3,
    "symbol": "editor_anim_event_message_send_0059d8b0",
    "va": "0x0059d8b0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-APP-SAFE-WAVE11",
    "score": 2,
    "symbol": "property_record_assign_pair_004279d0",
    "va": "0x004279d0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-APP-SAFE-WAVE11",
    "score": 
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg10-editor-dispatch/00587270.json"
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
  "original_bytes": 9131,
  "preview": "{\n  \"conflicts\": {\n    \"original_bytes\": 17652,\n    \"preview\": \"[\\n  {\\n    \\\"anchors\\\": [\\n      \\\"0x00587270\\\",\\n      \\\"0x0059d840\\\",\\n      \\\"0x0059d8b0\\\",\\n      \\\"0x00587270\\\",\\n      \\\"0x0059d8b0\\\",\\n      \\\"0x0059d840\\\",\\n      \\\"0x00573970\\\",\\n      \\\"0x00573970\\\",\\n      \\\"0x00586410\\\",\\n      \\\"0x00586410\\\",\\n      \\\"0x00587270\\\",\\n      \\\"0x00587270\\\",\\n      \\\"0x0059d840\\\",\\n      \\\"0x0059d840\\\",\\n      \\\"0x0059d8b0\\\",\\n      \\\"0x0059d8b0\\\"\\n    ],\\n    \\\"conflict_id\\\": \\\"Q-ANIMATION-DISPATCH\\\",\\n    \\\"kind\\\": \\\"conflict_ledger\\\",\\n    \\\"rejected\\\": [],\\n    \\\"resolution\\\": \\\"Editor animation Send/Post surfaces and the editor mode producer are concrete. The final AnimatedCreature/IAnimWorld consumer and pose ordering are unresolved.\\\",\\n    \\\"resolution_status\\\": \\\"Editor animation Send/Post surfaces and the editor mode producer are concrete. The final AnimatedCreature/IAnimWorld consumer and pose ordering are unresolved.\\\",\\n    \\\"source\\\": \\\"knowledgegraph/research/conflicts/track-c-state-events.json\\\",\\n    \\\"subject\\\": null,\\n    \\\"unresolved_reason\\\": \\\"Runtime reachability is absent or the required direct body/call path is not recovered.\\\"\\n  },\\n  {\\n    \\\"anchors\\\": [\\n      \\\"0x00591fa0\\\",\\n      \\\"0x00883a90\\\",\\n      \\\"0x00883ad0\\\",\\n      \\\"0x00883ad0\\\",\\n      \\\"0x00883a90\\\",\\n      \\\"0x00591fa0\\\",\\n      \\\"0x
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg10-editor-dispatch/00587270.json', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg10-editor-dispatch/00587270.json",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.json"
  ],
  "required_categories": [
    "ABI",
    "CALLS",
    "GLOBALS",
    "FIELDS/OFFSETS",
    "CONSTANTS",
    "CONTROL FLOW",
    "VIRTUAL DISPATCH",
    "RETURN SEMANTICS",
    "EVIDENCE COVERAGE"
  ]
}
```
