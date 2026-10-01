# Reconstruction context 0x0067dc80

- Status: `partial`
- Content SHA-256: `b3640b47527af5f496b7ab0e418d3d5e90155718f4c9a76cb495e35b4f5dcc3b`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x0067dc80",
  "phase": "reconstruction",
  "target": "0x0067dc80"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "App::IMessageManager::Get",
  "package": null,
  "subsystem": "App",
  "va": "0x0067dc80"
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
  "status": "queued"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "a012288f944a5e8a70fc87652bd088b6fda6709246cd863988fc9ea2a801216b",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x0067dc80 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "__thiscall, callee stack cleanup",
  "hidden_receiver": "ECX, dword pointer, callee object",
  "hidden_this": true,
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": 1,
  "ordinary_stack_arguments": [
    {
      "evidence": "RET 0x4 pops exactly one dword; the same slot is the one tested at 0x0067dc88.",
      "index": 0,
      "role": "deleting-destructor flag",
      "width_bytes": 4
    }
  ],
  "ret_form": "RET 0x4",
  "return_note": "MOV EAX,ESI at 0x0067dc98 materialises the receiver into the return register",
  "return_register": "EAX",
  "return_type": "void*",
  "saved_registers": [
    "ESI"
  ],
  "stack_arguments": [
    "{'evidence': 'RET 0x4 at 0x0067dc9b pops exactly one dword, and the same slot is the one tested at 0x0067dc88. The test is a BYTE test (encoding f6 44 24 08 01 = TEST r/m8, imm8), so only the low byte of the slot is read and only bit 0 of that byte is examined.', 'index': 0, 'role': 'deleting-destructor flag', 'width_bytes': 4}"
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
  "callees": [],
  "callers": [],
  "edge_rows": [
    {
      "callsite": "0x0067dc83",
      "direction": "out",
      "other": "0x0067db10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0067dc90",
      "direction": "out",
      "other": "0x00f47380",
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
  "globals": [
    "global:PASS"
  ],
  "types": [
    "DATA",
    "void*",
    "void* (dword receiver value) in EAX",
    "void* -- MOV EAX,ESI at 0x0067dc98 materialises the receiver into the return register"
  ],
  "vtables": [
    "vtable:0x013f3a68",
    "vtable:0x01401798"
  ]
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
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x0067dc83",
      "direction": "out",
      "other": "0x0067db10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0067dc90",
      "direction": "out",
      "other": "0x00f47380",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 0,
  "fan_out": 0,
  "manifest_callees": [],
  "manifest_callers": [],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0180",
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
      "same_subsystem"
    ],
    "package": "pkg-cheat-dispatch-0067e6f0",
    "score": 6,
    "symbol": "cCheatManager_func40h_0067e6f0",
    "va": "0x0067e6f0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "cheat-func44h-0067e730",
    "score": 6,
    "symbol": "func44h_0067e730",
    "va": "0x0067e730"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "pkg-app-proplist-copyall-wave16",
    "score": 6,
    "symbol": "all_copy_from_properties_006a14d0",
    "va": "0x006a14d0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "pkg-proplist-dispatch-wave14",
    "score": 6,
    "symbol": "app_property_list_add_all_properties_from_006a1510",
    "va": "0x006a1510"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "pkg-dfw-006a1540",
    "score": 6,
    "symbol": "proplist_write_006a1540",
    "va": "0x006a1540"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "pkg-property-clear-wave13",
    "score": 6,
    "symbol": "property_list_clear_006a2a80",
    "va": "0x006a2a80"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "pkg-direct-property-copyfrom-wave14",
    "score": 6,
    "symbol": "App_DirectPropertyList_CopyFrom_006a2ad0",
    "va": "0x006a2ad0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "pkg-direct-property-clear-wave14",
    "score": 6,
    "symbol": "direct_property_list_clear_006a2b20",
    "va": "0x006a2b20"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__IMessageManager__Get.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__IMessageManager__Get.c",
    "reconstruction/staging/pkg-app-imessage-manager-dtor/get_0067dc80.cpp",
    "reconstruction/staging/pkg-app-imessage-manager-dtor/get_0067dc80.hpp",
    "reconstruction/staging/pkg-app-imessage-manager-dtor/get_0067dc80_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-app-imessage-manager-dtor/0067dc80.json",
    "reconstruction/metadata/pkg-dfw-0067dc80/0067dc80.json"
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
        "0x000847f0",
        "0x00883a90",
        "0x00883ad0",
        "0x00883b20",
        "0x008841f0",
        "0x00883a90",
        "0x00883ad0",
        "0x00883b20",
        "0x008841f0",
        "0x000847f0",
        "0x0067dc80",
        "0x0067dc80",
        "0x000847f0",
        "0x000847f0",
        "0x0084bd70",
        "0x0084bd70"
      ],
      "conflict_id": "Q-DISPATCH-ORDER",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The cited producer, consumer, or registration surface is retained, but the complete event-to-message mapping, timing, and payload contract remain unresolved.",
      "resolution_status": "The cited producer, consumer, or registration surface is retained, but the complete event-to-message mapping, timing, and payload contract remain unresolved.",
      "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
      "subject": null,
      "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
    },
    {
      "anchors": [
        "0x000847f0",
        "0x00883a90",
        "0x00883ad0",
        "0x00883b20",
        "0x008841f0",
        "0x00883a90",
        "0x00883ad0",
        "0x00883b20",
        "0x008841f0",
        "0x000847f0",
        "0x0067dc80",
        "0x0067dc80",
        "0x000847f0",
        "0x000847f0",
        "0x0084bd70",
        "0x0084bd70"
      ],
      "conflict_id": "Q-QUEUE-LAYOUT",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The 0x
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/App__IMessageManager__Get.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-app-imessage-manager-dtor/0067dc80.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-dfw-0067dc80/0067dc80.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-app-imessage-manager-dtor/get_0067dc80.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-app-imessage-manager-dtor/get_0067dc80.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-app-imessage-manager-dtor/get_0067dc80_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/App__IMessageManager__Get.c",
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
      "ref": "reconstruction/metadata/pkg-app-imessage-manager-dtor/0067dc80.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg-dfw-0067dc80/0067dc80.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-app-imessage-manager-dtor/get_0067dc80.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstru
[TRUNCATED]
```
