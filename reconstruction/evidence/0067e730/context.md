# Reconstruction context 0x0067e730

- Status: `partial`
- Content SHA-256: `18ea52a32e8ef4499e0e8ceec044f2692d943d6b7972cf32041b3feac7c831f7`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x0067e730",
  "phase": "reconstruction",
  "target": "0x0067e730"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "App::cCheatManager::func44h",
  "package": "cheat-func44h-0067e730",
  "subsystem": "App",
  "va": "0x0067e730"
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
  "content_sha256": "cbbf502298789e89dce51bbadf02210388735877617df66d2a892cb9a7b31b75",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x0067e730 failed: Decompilation did not complete. Reason: ",
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
  "convention": "__thiscall with two callee-cleaned stack words",
  "hidden_this": true,
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": [
    "entry_ESP+0x4"
  ],
  "ordinary_stack_arguments": [
    "{'entry_offset': 'entry_ESP+0x4', 'note': '0x0067e73d MOV EBX,dword ptr [ESP + 0x10] addresses entry_ESP+0x4 because PUSH ESI (0x0067e730), PUSH EDI (0x0067e734) and PUSH EBX (0x0067e73c) have moved ESP from entry_ESP to entry_ESP-0xC. It is read exactly once, before the loop head at 0x0067e741, and the back edge at 0x0067e75b targets the head, so the word is hoisted out of the loop.', 'observed': True, 'ordinal': 1, 'read': True, 'width_bytes': 4, 'written': False}",
    "{'entry_offset': 'entry_ESP+0x4', 'note': 'Read once, hoisted out of the loop. After PUSH ESI/EDI/EBX the frame is entry_ESP-0xC, so 0x0067e73d MOV EBX,[ESP+0x10] addresses entry_ESP+0x4.', 'observed': True, 'ordinal': 1, 'read': True, 'width_bytes': 4, 'written': False}"
  ],
  "receiver": true,
  "receiver_register": "ECX",
  "ret_form": "RET 0x4",
  "return_register": "EAX",
  "return_semantics": [
    "EAX carries no defined value on any exit path; the only writes to EAX are the vtable load at 0x0067e744 and the 0x00921580 result consumed into ESI at 0x0067e754. The function is a procedure, not a value producer.",
    "EAX carries no defined value on any exit path; the only writes to EAX are the vtable load and the 0x00921580 result, and both are consumed by the loop. The function is a procedure, not a value producer.
[TRUNCATED]
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
      "callsite": "0x0067e74f",
      "direction": "out",
      "other": "0x00921580",
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
    "global:g_cheat_func44h_ports",
    "global:g_dispatch_ports"
  ],
  "types": [
    "void"
  ],
  "vtables": [
    "vtable:0x01401b74"
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
      "A live cCheatManager with a populated observer chain is required to observe the dispatch at all; the chain head at +0x50 must differ from the embedded terminator at +0x4c, or the body exits at 0x0067e73a without making any call.",
      "A live cCheatManager with a populated observer chain is required to observe the dispatch at all; the chain head at +0x50 must differ from the embedded terminator at +0x4c.",
      "The concrete receiver type must be identified before the +0x1c entry can be attributed a meaning, and before a stub with the right stack discipline can be confirmed.",
      "The concrete receiver type must be identified before the +0x1c entry can be attributed a meaning.",
      "The function is reachable only through vtable 0x01401b74 slot 17, so a differential run must construct that exact table and dispatch the slot."
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
      "callsite": "0x0067e74f",
      "direction": "out",
      "other": "0x00921580",
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
    "id": "scc-0190",
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
      "shared_vtable:vtable:0x01401b74",
      "same_calling_convention"
    ],
    "package": "pkg-cheat-dispatch-0067e6f0",
    "score": 12,
    "symbol": "cCheatManager_func40h_0067e6f0",
    "va": "0x0067e6f0"
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
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "pkg-direct-property-clear-wave14",
    "score": 8,
    "symbol": "direct
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__cCheatManager__func44h.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__cCheatManager__func44h.c",
    "reconstruction/staging/cheat-func44h-0067e730/cheat_dispatch_func44h_0067e730.cpp",
    "reconstruction/staging/cheat-func44h-0067e730/cheat_dispatch_func44h_0067e730.hpp",
    "reconstruction/staging/cheat-func44h-0067e730/cheat_dispatch_func44h_0067e730_model_test.cpp",
    "reconstruction/staging/dogfood-after-02-0067e730/cheat_dispatch_0067e730.cpp",
    "reconstruction/staging/dogfood-after-02-0067e730/cheat_dispatch_0067e730.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/cheat-func44h-0067e730/0067e730.json",
    "reconstruction/metadata/dogfood-after-02-0067e730/0067e730.json"
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
    "A live cCheatManager with a populated observer chain is required to observe the dispatch at all; the chain head at +0x50 must differ from the embedded terminator at +0x4c, or the body exits at 0x0067e73a without making any call.",
    "A live cCheatManager with a populated observer chain is required to observe the dispatch at all; the chain head at +0x50 must differ from the embedded terminator at +0x4c.",
    "Does the dispatch observe the chain as it is being mutated, since a successor is fetched after each call?",
    "Does the manager's own word at +0x4c ever hold a value another function uses, given that this body only address-takes it?",
    "Is the callee-cleaned eight-byte stack of the +0x1c entry confirmed anywhere, or is it only forced by the requirement that ESP stay constant across iterations?",
    "The concrete receiver type must be identified before the +0x1c entry can be attributed a meaning, and before a stub with the right stack discipline can be confirmed.",
    "The concrete receiver type must be identified before the +0x1c entry can be attributed a meaning.",
    "The function is reachable only through vtable 0x01401b74 slot 17, so a differential run must construct that exact table and dispatch the slot.",
    "What does the +0x64 byte mean, and is the sibling pair an enable/disable or a register/unregister traversal?",
    "What does the +0x64 byte that the sibling gates on mean, and is the pair an enable/disable or a register/unregister traversal?",
    "What is 0x00921580 semantically, beyond taki
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/App__cCheatManager__func44h.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/cheat-func44h-0067e730/0067e730.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/dogfood-after-02-0067e730/0067e730.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/cheat-func44h-0067e730/cheat_dispatch_func44h_0067e730.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/cheat-func44h-0067e730/cheat_dispatch_func44h_0067e730.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/cheat-func44h-0067e730/cheat_dispatch_func44h_0067e730_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/dogfood-after-02-0067e730/cheat_dispatch_0067e730.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/dogfood-after-02-0067e730/cheat_dispatch_0067e730.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/App__cCheatManager__func44h.c",
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
      "ref": "reconstruction/metadata/cheat-func44h-0067e730/0067e730.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/dogfood-after-02-0067e730/0067e730.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/cheat-func44h-0067e730/cheat_dispatch_func44h_0067e730.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "
[TRUNCATED]
```
