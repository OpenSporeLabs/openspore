# Reconstruction context 0x0067dcc0

- Status: `partial`
- Content SHA-256: `d5f16d615b350a901fb5ff64836b740a7e547d5b430e24ba6e53430ad3ffc251`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x0067dcc0",
  "phase": "reconstruction",
  "target": "0x0067dcc0"
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
  "va": "0x0067dcc0"
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
  "content_sha256": "9a1c92e69d129c73be81dbfc669608b761523646dc3ab870697d696c8fdc709e",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x0067dcc0 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "cdecl-compatible no-argument accessor",
  "hidden_receiver": null,
  "ordinary_stack_argument_slots": 0,
  "ret_form": "RET",
  "return_note": "opaque 32-bit application-system pointer",
  "return_register": "EAX",
  "return_width_bytes": 4,
  "stack_cleanup_bytes": 0
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
      "va": "0x00403af0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00404660"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0040a590"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0040e5b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0040eab0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0040eb70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0040f820"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0040fc00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0040fe00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00410d70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00410dd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004111e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00411890"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004157d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004165a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00416990"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00403efb",
      "direction": "in",
      "other": "0x00403af0",
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
    "global:MOV EAX,[0x015fd890]",
    "global:get_function_globals audit reports one undefined4 read at 0x015fd890"
  ],
  "types": [
    "opaque 32-bit application-system pointer"
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
      "va": "0x00403af0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00404660"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0040a590"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0040e5b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0040eab0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0040eb70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0040f820"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0040fc00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0040fe00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00410d70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00410dd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004111e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00411890"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004157d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004165a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00416990"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0041a0c0"
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
      "direct_xref_neighbor"
    ],
    "package": "PKG-EDITOR-INPUT-WAVE6",
    "score": 3,
    "symbol": "editor_input_0058ac10",
    "va": "0x0058ac10"
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
    "package": "PKG-RUNTIME-SERVICES-WAVE7",
    "score": 3,
    "symbol": "editor_anim_event_message_post_0059d840",
    "va": "0x0059d840"
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
      "direct_xref_neighbor"
    ],
    "package": "PKG-18-UI-SCRIPTING",
    "score": 3,
    "symbol": "FUN_005c0380",
    "va": "0x005c0380"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-15-EDITOR-SUPPORT",
    "score": 3,
    "symbol": "palette_application_setup_005c53c0",
    "va": "0x005c53c0"
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
    "symbol": "editor_query_dispatch_005dfd00",
    "va": "0x005dfd00"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/wave6-misc-engine/misc_engine.cpp",
    "reconstruction/staging/wave6-misc-engine/misc_engine.hpp",
    "reconstruction/staging/wave6-misc-engine/misc_engine_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave6-misc-engine/0067dcc0.json"
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
  "conflicts": [
    {
      "anchors": [
        "0x00e20860",
        "0x00e20860",
        "0x00e20860",
        "0x00e20860",
        "0x00e20860",
        "0x0067dcc0",
        "0x00b3d330",
        "0x00e7fc00",
        "0x00e20860"
      ],
      "conflict_id": "U01",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
      "resolution_status": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
      "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
      "subject": null,
      "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
    },
    {
      "anchors": [
        "0x00e81cf0",
        "0x00e81cf0",
        "0x0067dcc0",
        "0x00b3d330",
        "0x00e552f0"
      ],
      "conflict_id": "U04",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
      "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
      "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
      "subject": null,
      "unresolved_reason": "Runtime reachability is 
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave6-misc-engine/0067dcc0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave6-misc-engine/misc_engine.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave6-misc-engine/misc_engine.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave6-misc-engine/misc_engine_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave6-misc-engine/0067dcc0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave6-misc-engine/misc_engine.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave6-misc-engine/misc_engine.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave6-misc-engine/misc_engine_model_test.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.json"
  ],
  "required_cate
[TRUNCATED]
```
