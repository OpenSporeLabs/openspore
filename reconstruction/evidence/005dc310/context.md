# Reconstruction context 0x005dc310

- Status: `complete`
- Content SHA-256: `5bada0d10ed6c381925f51cdbca2bd30881b074e71cc8243ddcb79a1fee6a47f`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x005dc310",
  "phase": "reconstruction",
  "target": "0x005dc310"
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
  "va": "0x005dc310"
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
  "content_sha256": "c436e92480bc43932c531501e7c2d14b69b0627e5c247d789753af4180063c0c",
  "live_attempts": [],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `present`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json

void FUN_005dc310(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = FUN_008105b0(param_1,1);
  if (iVar1 == 0) {
    FUN_008105b0(param_1,1);
  }
  return;
}


```

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "__thiscall",
  "hidden_this_register": "ECX",
  "return_type": "void*",
  "stack_arguments": [
    {
      "entry_offset": "ESP+4",
      "name": "lookup_key",
      "type": "uint32_t",
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
      "name": "Editors::cEditor::Update",
      "reconstructed": false,
      "va": "0x0058be50"
    },
    {
      "name": "Editors::cEditor::HandleMessage",
      "reconstructed": false,
      "va": "0x00591fa0"
    },
    {
      "name": "FUN_005dda30",
      "reconstructed": true,
      "va": "0x005dda30"
    },
    {
      "name": "editor_query_dispatch_005dfd00",
      "reconstructed": true,
      "va": "0x005dfd00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00634e40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00634f20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00635010"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00635160"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00635390"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00635400"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006354c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00635520"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00635580"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00635600"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00635680"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00635790"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x0058c7e3",
      "direc
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "Opaque void* for the lookup result; no concrete target owner or ownership contract is asserted",
    "OpaqueEditorModeManager for ECX",
    "uint32_t",
    "uint32_t for the lookup key",
    "void*"
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
      "name": "Editors::cEditor::Update",
      "reconstructed": false,
      "va": "0x0058be50"
    },
    {
      "name": "Editors::cEditor::HandleMessage",
      "reconstructed": false,
      "va": "0x00591fa0"
    },
    {
      "name": "FUN_005dda30",
      "reconstructed": true,
      "va": "0x005dda30"
    },
    {
      "name": "editor_query_dispatch_005dfd00",
      "reconstructed": true,
      "va": "0x005dfd00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00634e40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00634f20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00635010"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00635160"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00635390"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00635400"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006354c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00635520"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00635580"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00635600"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00635680"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00635790"
    },
    {
      "name": null,
      "reconstr
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
      "shared_types:void*",
      "same_calling_convention"
    ],
    "package": "PKG-12-SIM-SPACE",
    "score": 5,
    "symbol": "FUN_00aea230",
    "va": "0x00aea230"
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
      "shared_types:void*"
    ],
    "package": "PKG-UTFWIN-CORE-W
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
    "reconstruction/metadata/pkg10-editor-dispatch/005dc310.json"
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
    "Are the two internal subobjects at this+0x14 and this+0x2c distinct registries or alternate lookup paths?",
    "What concrete type, if any, owns the opaque void* lookup result?"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'ref': 'ephemeral reconstruction_knowledge.build_index', 'mode': 'derived', 'source_class': 'generated_index'}, {'ref': 'tools/reconstruction_tooling/abi_infer.py', 'mode': 'derived', 'source_class': 'derived'}, {'ref': 'GhidraMCP /disassemble_function', 'mode': 'live', 'source_class': 'ghidra'}, {'ref': 'GhidraMCP REST /decompile_function @ http://127.0.0.1:8089', 'mode': 'live', 'source_class': 'ghidra'}, {'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'mode': 'live', 'source_class': 'ghidra'}, {'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'mode': 'persisted', 'source_class': 'committed_artifact'}, {'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'mode': 'persisted', 'source_class': 'committed_artifact'}, {'ref': 'reconstruction/metadata/pkg10-editor-dispatch/005dc310.json', 'mode': 'persisted', 'source_class': 'committed_artifact'}`

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
      "ref": "GhidraMCP REST /decompile_function @ http://127.0.0.1:8089",
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
      "ref": "reconstruction/metadata/pkg10-editor-dispatch/005dc310.json",
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
