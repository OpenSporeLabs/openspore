# Reconstruction context 0x006891f0

- Status: `partial`
- Content SHA-256: `45838f3a4a9ea00935595c64b793fe28cfd115a91356077b2506d5117d4bd18d`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x006891f0",
  "phase": "reconstruction",
  "target": "0x006891f0"
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
  "va": "0x006891f0"
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
  "status": "unresolved"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "0745e7d192831a0c3046dfc5e45eab7ba3398bd12df86a4de0933e35753628ec",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x006891f0 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "__cdecl",
  "hidden_this_register": "ECX is not a receiver: 0x00689205 SUB ESP,0x60 is preceded by PUSH EDI at 0x0068920b, and ECX is only used as a scratch thiscall target for the string and allocator ports (0x00689225, 0x0068924a, 0x00689296, 0x006892ab, 0x0068930f, 0x00689385).",
  "ordinary_stack_argument_slots": 2,
  "receiver": false,
  "ret_form": "RET",
  "return_observation": "0x006894ca is C3 with no immediate and no preceding MOV EAX; the last value written to EAX is the return of 0x00931fd0 at 0x00689421, which is immediately followed by stack-pointer arithmetic and the epilogue.",
  "return_register": "EAX (clobbered, unused)",
  "return_semantics": "no value; EAX is clobbered by the last tail call and none of the 4 observed call sites reads it",
  "return_type": "void",
  "return_width_bytes": 0,
  "saved_registers": [
    "EBX",
    "EBP",
    "ESI",
    "EDI"
  ],
  "stack_arguments": [
    {
      "proof": "0x00de48e1 PUSH 0x145fb88 pushes L\"GGEUserData.dat\" first, so it is the second argument; 0x00de48e6 PUSH 0x147e040 pushes L\"GGEUserData.dat.tmp\" second, so it is the first argument, and the reconstruction's source_name is the .tmp name",
      "role": "source_name",
      "slot": "[ESP_entry+4]"
    },
    {
      "proof": "same callsite, the argument the reconstruction concatenates to form the destination path",
      "role": "dest_name",
      "slot": "[ESP_entry+8]"
    }
  ],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "single exit at 0x006894ca"
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
      "name": "FUN_00580cb0",
      "reconstructed": false,
      "va": "0x00580cb0"
    },
    {
      "name": "ProfilePersistenceBoundary_run_candidate_00b28ec0",
      "reconstructed": true,
      "va": "0x00b28ec0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb4ba0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00de4850"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00580dc9",
      "direction": "in",
      "other": "0x00580cb0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00b293d4",
      "direction": "in",
      "other": "0x00b28ec0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00bb4f0a",
      "direction": "in",
      "other": "0x00bb4ba0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00de48eb",
      "direction": "in",
      "other": "0x00de4850",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006892de",
      "direction": "out",
      "other": "0x00423650",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00689358",
      "direction": "out",
      "other": "0x00423650",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0068925e",
      "direction": "out",
      "other": "0x00429760",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00689235",
      "direction": "out",
      "other": "0x00579a90",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006892a6",
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
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
      "A trace must record the return value and the observable effect of 0x00932ae0 on the base path, which is the only way to resolve whether the leading delete is live behaviour or a no-op.",
      "A trace must record whether MoveFileExW at 0x00689406 succeeds in practice, because the body discards the result and static analysis cannot predict the filesystem state.",
      "No original-process trace exists for this function. A differential trace must record the string returned by the save-area virtual slot +0x28, since the whole path algebra depends on whether it is separator-terminated."
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
  "callers": [
    {
      "name": "FUN_00580cb0",
      "reconstructed": false,
      "va": "0x00580cb0"
    },
    {
      "name": "ProfilePersistenceBoundary_run_candidate_00b28ec0",
      "reconstructed": true,
      "va": "0x00b28ec0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb4ba0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00de4850"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00580dc9",
      "direction": "in",
      "other": "0x00580cb0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00b293d4",
      "direction": "in",
      "other": "0x00b28ec0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00bb4f0a",
      "direction": "in",
      "other": "0x00bb4ba0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00de48eb",
      "direction": "in",
      "other": "0x00de4850",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006892de",
      "direction": "out",
      "other": "0x00423650",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00689358",
      "direction": "out",
      "other": "0x00423650",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0068925e",
      "direction": "out",
      "other": "0x00429760",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00689235",
      "direction": "out",
      "other": "0x00579a90
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
    "package": "PKG-20-PERSISTENCE-BOUNDARY",
    "score": 3,
    "symbol": "ProfilePersistenceBoundary_run_candidate_00b28ec0",
    "va": "0x00b28ec0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-EDITOR-SAFE-WAVE11",
    "score": 2,
    "symbol": "editor_bake_probe_004bf770",
    "va": "0x004bf770"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-SIMULATOR-SAFE-WAVE11",
    "score": 2,
    "symbol": "dispatch_key_00628450",
    "va": "0x00628450"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-06-WAVE6-APP-MANAGERS",
    "score": 2,
    "symbol": "App_IStateManager_Get_0067dce0",
    "va": "0x0067dce0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "WAVE6-ENGINE-RUNTIME",
    "score": 2,
    "symbol": "app_config_manager_get_0067dcf0",
    "va": "0x0067dcf0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-06-WAVE6-APP-MANAGERS",
    "score": 2,
    "symbol": "App_IPropManager_Get_0067ddf0",
    "va": "0x0067ddf0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 2,
    "symbol": "FUN_00b3d3a0",
    "va": "0x00b3d3a0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 2,
    "symbol": "FUN_00b3d400",
    "va": "0x00b3d400"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/wave13-w1-dispatch-b03/editor_promote_save_file.cpp",
    "reconstruction/staging/wave13-w1-dispatch-b03/editor_promote_save_file.hpp",
    "reconstruction/staging/wave13-w1-dispatch-b03/editor_promote_save_file_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-dispatch-b03/006891f0.json"
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
    "A trace must record the return value and the observable effect of 0x00932ae0 on the base path, which is the only way to resolve whether the leading delete is live behaviour or a no-op.",
    "A trace must record whether MoveFileExW at 0x00689406 succeeds in practice, because the body discards the result and static analysis cannot predict the filesystem state.",
    "Do the callers at 0x00580dc9 and 0x00b293d4 pass names with an embedded separator, given that the concatenation inserts none? Their arguments are stack buffers whose contents were not read.",
    "Is the promote-and-delete sequence ever observed to run with a destination that does not exist, i.e. is the first-time-install path exercised? Static analysis cannot tell.",
    "No original-process trace exists for this function. A differential trace must record the string returned by the save-area virtual slot +0x28, since the whole path algebra depends on whether it is separator-terminated.",
    "What does virtual slot +0x28 on the save area return, and does it end with a path separator? The receiver is constructed at runtime so no string was read.",
    "What is 0x00932960, the routine 0x00932ae0 delegates to for a non-directory path? Not decompiled in this pass.",
    "What is the original function name and owning class? Nothing in the binary or the SDK names it.",
    "Why are the two exists/delete branches guarded while the promotion is not? The asymmetry may be deliberate (best-effort cleanup) or an oversight; the binary does not say.",
    "Why is a recurs
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-w1-dispatch-b03/006891f0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b03/editor_promote_save_file.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b03/editor_promote_save_file.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b03/editor_promote_save_file_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave13-w1-dispatch-b03/006891f0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b03/editor_promote_save_file.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b03/editor_promote_save_file.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b03/editor_promote_save_file_test.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "recon
[TRUNCATED]
```
