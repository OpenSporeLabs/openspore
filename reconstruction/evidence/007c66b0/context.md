# Reconstruction context 0x007c66b0

- Status: `partial`
- Content SHA-256: `a4c1e69f95cd8fd6f31afb67591582a16a0fe331ba54bfec99b22aef4fd6f234`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x007c66b0",
  "phase": "reconstruction",
  "target": "0x007c66b0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "App::cCameraManager::HandleMessage",
  "package": "pkg-camera-msg-007c66b0",
  "subsystem": "App",
  "va": "0x007c66b0"
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
  "content_sha256": "c85a94e93a4bcf8990a6a9010a31a49dcc0501dcba2b9031c5cec4ab49cdf321",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x007c66b0 failed: Decompilation did not complete. Reason: ",
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
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": 2,
  "ordinary_stack_arguments": [
    "dword message id at [ESP+4] after entry; address taken at 0x007c66b7 LEA EAX,[ESP+0x14] and passed as the hash key",
    "dword message payload at [ESP+8] after entry; never read by any instruction in 0x007c66b0..0x007c66f8"
  ],
  "ret_form": "RET 0x4",
  "return_semantics": "true when the message id resolved in the receiver's registry at +0x60 and the payload was forwarded to virtual slot 0x54; false when the lookup returned the miss sentinel and nothing was dispatched",
  "return_type": "bool",
  "stack_cleanup_bytes": 4
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
      "callsite": "0x007c66c6",
      "direction": "out",
      "other": "0x00645ed0",
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
    "bool"
  ],
  "vtables": [
    "vtable:0x014106a4"
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
      "No Wine/original trace was run for this target; no runtime promotion is claimed."
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
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x007c66c6",
      "direction": "out",
      "other": "0x00645ed0",
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
    "id": "scc-0239",
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
      "same_subsystem",
      "shared_vtable:vtable:0x014106a4",
      "same_calling_convention"
    ],
    "package": "pkg-app-camera-active-007c61a0",
    "score": 12,
    "symbol": "camera_manager_set_viewer_007c61a0",
    "va": "0x007c61a0"
  },
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
    "va"
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__cCameraManager__HandleMessage.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__cCameraManager__HandleMessage.c",
    "reconstruction/staging/pkg-camera-msg-007c66b0/camera_msg_007c66b0.cpp",
    "reconstruction/staging/pkg-camera-msg-007c66b0/camera_msg_007c66b0.hpp",
    "reconstruction/staging/pkg-camera-msg-007c66b0/camera_msg_007c66b0_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-camera-msg-007c66b0/007c66b0.json"
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
    "Does any caller pass a second message argument? The body never reads [ESP+8] and RET 0x4 pops one dword, so a second declared argument is possible but unconfirmed.",
    "Ghidra's function boundaries in this neighbourhood are unreliable: the SDK entry 0x007c64c0 sits inside the flow that starts at 0x007c6480, so slot identities that depend on Ghidra function extents (0x007c64c0 SetActiveCamera, 0x007c6e50 Dispose) are taken from the live listing rather than from Ghidra's function records.",
    "Is the receiver's dispatch vptr 0x014106a8 (ctor field +0x00) or 0x014106a4 (ctor field +0x04)? The byte offset 0x54 resolves to 0x007c6420 under the first and to 0x007c6480 under the second. No call site of HandleMessage was found to disambiguate, and the SDK label for 0x007c6420 is unknown.",
    "Is virtual slot 0x54 named SetActiveCameraByIndex, SetActiveView or something else in the SDK? 0x007c6420 is only an unnamed vtable entry; the name is not guessed here.",
    "No Wine/original trace was run for this target; no runtime promotion is claimed.",
    "What populates the registry at +0x60, i.e. which message ids map to which camera slots? No inserter for this map was located from this target."
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/App__cCameraManager__HandleMessage.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-camera-msg-007c66b0/007c66b0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-camera-msg-007c66b0/camera_msg_007c66b0.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-camera-msg-007c66b0/camera_msg_007c66b0.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-camera-msg-007c66b0/camera_msg_007c66b0_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/App__cCameraManager__HandleMessage.c",
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
      "ref": "reconstruction/metadata/pkg-camera-msg-007c66b0/007c66b0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-camera-msg-007c66b0/camera_msg_007c66b0.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-camera-msg-007c66b0/camera_msg_007c66b0.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
   
[TRUNCATED]
```
