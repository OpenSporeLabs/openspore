# Reconstruction context 0x00574a20

- Status: `partial`
- Content SHA-256: `ba0555f1d4f4f4d3861aa676fa03d7b84b0b11464d574e8dcbe05e82800ac956`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00574a20",
  "phase": "reconstruction",
  "target": "0x00574a20"
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
  "va": "0x00574a20"
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
  "content_sha256": "c0f12f1d04f76297825b4a268052d01fdb6c8da65e73e6db96483bd5339a7d9f",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00574a20 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "__thiscall-like",
  "hidden_this_register": "ECX",
  "hidden_this_type": "OpaqueEditor *",
  "return_note": "opaque pointer-like value",
  "stack_arguments": [
    {
      "abi_type": "unclassified 32-bit value",
      "entry_offset": "ESP+4",
      "name": "receiver_candidate_word",
      "nonzero_behavior": "use the incoming value directly as the tail-call ECX receiver candidate; no uint32 selector semantics are established",
      "type": "unclassified 32-bit value",
      "width_bytes": 4,
      "zero_behavior": "load [ECX+0x150] and use that value as the tail-call ECX receiver candidate"
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
  "callees": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004c49e0"
    }
  ],
  "callers": [
    {
      "name": "Editor_Save",
      "reconstructed": false,
      "va": "0x00577650"
    },
    {
      "name": "FUN_005dda30",
      "reconstructed": true,
      "va": "0x005dda30"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x0057775a",
      "direction": "in",
      "other": "0x00577650",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005dda42",
      "direction": "in",
      "other": "0x005dda30",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00574a3c",
      "direction": "out",
      "other": "0x004c49e0",
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
  "globals": [],
  "types": [
    "A nonzero incoming stack word becomes the tail-call ECX receiver candidate directly; no uint32 selector semantics are established",
    "A zero incoming stack word instead loads [ECX+0x150], whose opaque value becomes the tail-call ECX receiver candidate",
    "OpaqueEditor *",
    "OpaqueEditor for ECX; the mode-manager caller passes this+0x5c, while Editor_Save passes its own this",
    "The result retains pointer-like status and is used only through a null/nonzero guard by 0x005dda30; no boolean return is inferred",
    "opaque pointer-like value",
    "unclassified 32-bit value"
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
      "va": "0x004c49e0"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": "Editor_Save",
      "reconstructed": false,
      "va": "0x00577650"
    },
    {
      "name": "FUN_005dda30",
      "reconstructed": true,
      "va": "0x005dda30"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x0057775a",
      "direction": "in",
      "other": "0x00577650",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005dda42",
      "direction": "in",
      "other": "0x005dda30",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00574a3c",
      "direction": "out",
      "other": "0x004c49e0",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 2,
  "fan_out": 1,
  "manifest_callees": [],
  "manifest_callers": [],
  "nearby_reconstructed": [
    "0x005dda30"
  ],
  "scc": {
    "id": "scc-0058",
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
      "direct_xref_neighbor"
    ],
    "package": "PKG-10-EDITOR-DISPATCH",
    "score": 3,
    "symbol": "FUN_005dda30",
    "va": "0x005dda30"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg10-editor-dispatch/00574a20.json"
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
    "Can the receiver candidate at [ECX+0x150] be classified without RTTI?",
    "What concrete pointer-like owner or return semantics, if any, can be recovered for the mode2_guard result?",
    "What concrete type is established for the direct and +0x150-derived tail-call ECX receiver candidates?"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg10-editor-dispatch/00574a20.json', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg10-editor-dispatch/00574a20.json",
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
