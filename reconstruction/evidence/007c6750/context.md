# Reconstruction context 0x007c6750

- Status: `partial`
- Content SHA-256: `1f86a852907d0d10ea121b7d2abbfeeaaaced56478b483311137d7008b69ae66`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x007c6750",
  "phase": "reconstruction",
  "target": "0x007c6750"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "App::cCameraManager::SetActiveCameraByID",
  "package": null,
  "subsystem": "App",
  "va": "0x007c6750"
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
  "content_sha256": "98ece8d181aa8775f956d7a2efd6149cd696765b09ef1f40ee2c141845f6100f",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x007c6750 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "__thiscall",
  "hidden_this": true,
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": [
    "entry_ESP+0x4"
  ],
  "ordinary_stack_arguments": 1,
  "receiver_register": "ECX",
  "ret_form": "RET 0x4",
  "return_register": "EAX",
  "return_type": "bool",
  "saved_registers": [
    "EBX",
    "ESI",
    "EBP",
    "EDI"
  ],
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "callee",
  "termination": "RET 0x4"
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
      "va": "0x007c3c20"
    }
  ],
  "callers": [],
  "edge_rows": [
    {
      "callsite": "0x007c68e5",
      "direction": "out",
      "other": "0x0052df30",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x007c6b12",
      "direction": "out",
      "other": "0x0067dd10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x007c6b52",
      "direction": "out",
      "other": "0x0067dd10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x007c6b27",
      "direction": "out",
      "other": "0x007c3c20",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x007c6b65",
      "direction": "out",
      "other": "0x007c3ce0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x007c6a3d",
      "direction": "out",
      "other": "0x007c65a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x007c6772",
      "direction": "out",
      "other": "0x00837f30",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x007c67ec",
      "direction": "out",
      "other": "0x00838020",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x007c696d",
      "direction": "out",
      "other": "0x008380b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x007c6807",
      "direction": "out",
      "other": "0x00838330",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x007c6ac9",
      "direction": "out",
      "other"
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "bool"
  ],
  "vtables": [
    "vtable:0x014104a4"
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
      "no original-process trace exists in this repository; the static reconstruction of 0x007c6750 is unvalidated at runtime",
      "the committed evidence pack's disassembly is a truncated envelope, so no listing-dependent check could be adjudicated from committed evidence"
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
  "callees": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007c3c20"
    }
  ],
  "callees_truncated": false,
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x007c68e5",
      "direction": "out",
      "other": "0x0052df30",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x007c6b12",
      "direction": "out",
      "other": "0x0067dd10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x007c6b52",
      "direction": "out",
      "other": "0x0067dd10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x007c6b27",
      "direction": "out",
      "other": "0x007c3c20",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x007c6b65",
      "direction": "out",
      "other": "0x007c3ce0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x007c6a3d",
      "direction": "out",
      "other": "0x007c65a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x007c6772",
      "direction": "out",
      "other": "0x00837f30",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x007c67ec",
      "direction": "out",
      "other": "0x00838020",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x007c696d",
      "direction": "out",
      "other": "0x008380b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x007c6807",
      "direction": "out",
      "other": "0x00838330",
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
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "pkg-cheat-dispatch-0067e6f0",
    "score": 8,
    "symbol": "cCheatManager_func40h_0067e6f0",
    "va": "0x0067e6f0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "cheat-func44h-0067e730",
    "score": 8,
    "symbol": "func44h_0067e730",
    "va": "0x0067e730"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "pkg-app-proplist-copyall-wave16",
    "score": 8,
    "symbol": "all_copy_from_properties_006a14d0",
    "va": "0x006a14d0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "pkg-proplist-dispatch-wave14",
    "score": 8,
    "symbol": "app_property_list_add_all_properties_from_006a1510",
    "va": "0x006a1510"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "pkg-dfw-006a1540",
    "score": 8,
    "symbol": "proplist_write_006a1540",
    "va": "0x006a1540"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "pkg-property-clear-wave13",
    "score": 8,
    "symbol": "property_list_clear_006a2a80",
    "va": "0x006a2a80"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "pkg-direct-property-copyfrom-wave14",
    "score": 8,
    "symbol": "App_DirectPropertyList_CopyFrom_006a2ad0",
    "va": "0x006a2ad0"
  },
  {
    "ma
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__cCameraManager__SetActiveCameraByID.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__cCameraManager__SetActiveCameraByID.c",
    "reconstruction/staging/df2-live-listing/camera_active_by_id_007c6750.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/df2-live-listing/007c6750.json"
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
        "0x007d85b0",
        "0x007d8d40",
        "0x01412598",
        "0x01412598",
        "0x007d8c80",
        "0x007d8d40",
        "0x007d85b0",
        "0x007d8d40",
        "0x01412598",
        "0x007d8c80",
        "0x007c61a0",
        "0x007c61a0",
        "0x007c64c0",
        "0x007c64c0",
        "0x007c6750",
        "0x007c6750"
      ],
      "conflict_id": "app_mode_setter_boundary",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
      "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
      "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
      "subject": null,
      "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
    },
    {
      "anchors": [
        "0x007c61a0",
        "0x007c64c0",
        "0x007c6750",
        "0x007c6eb0",
        "0x007c61a0",
        "0x007c61a0",
        "0x007c61a0",
        "0x007c61a0",
        "0x007c64c0",
        "0x007c64c0",
        "0x007c64c0",
        "0x007c6750",
        "0x007c6750",
        "0x007c6750",
        "0x007c6eb0",
        "0x007c6eb0"
      ],
      "conflict_id": "camera_address_conflicts",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The committed evid
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/App__cCameraManager__SetActiveCameraByID.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/df2-live-listing/007c6750.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/df2-live-listing/camera_active_by_id_007c6750.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/App__cCameraManager__SetActiveCameraByID.c",
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
      "ref": "reconstruction/metadata/df2-live-listing/007c6750.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/df2-live-listing/camera_active_by_id_007c6750.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.json",
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__cCameraManager__SetActiveCameraByID.c"
  ],
  "required_categories": [
    "ABI",
  
[TRUNCATED]
```
