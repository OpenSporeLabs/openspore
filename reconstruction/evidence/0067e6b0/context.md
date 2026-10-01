# Reconstruction context 0x0067e6b0

- Status: `partial`
- Content SHA-256: `5408de168604d77d154a6cf19e7f81042b322f124362da008bf5b41a7187b23b`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x0067e6b0",
  "phase": "reconstruction",
  "target": "0x0067e6b0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "App::cCheatManager::func3Ch",
  "package": null,
  "subsystem": "App",
  "va": "0x0067e6b0"
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
  "content_sha256": "d591fe6114dac04f7213080110838fdb675bdafdfd3343d4fedecb00e45c73b8",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x0067e6b0 failed: Decompilation did not complete. Reason: ",
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
  "ordinary_stack_arguments": [
    "{'entry_offset': 'entry_ESP+0x4', 'note': '0x0067e6b8 TEST byte ptr [ESP + 0x8],0x1 addresses entry_ESP+0x4 because PUSH ESI at 0x0067e6b0 is the only outstanding frame change and 0x0067e2b0 pushes nothing and ends in a plain RET at 0x0067e301. The test is on the low BYTE, so only bit 0 of the word is given meaning.', 'observed': True, 'ordinal': 1, 'read': True, 'width_bytes': 4, 'written': False}",
    "{'entry_offset': 'entry_ESP+0x4', 'note': '0x0067e6b8 TEST byte ptr [ESP + 0x8],0x1 addresses entry_ESP+0x4. The only outstanding frame change at that point is the PUSH ESI at 0x0067e6b0, because 0x0067e2b0 is stack-neutral across its own call: it pushes five words at 0x0067e2b0..0x0067e2c6 and drops exactly those five (POP ESI at 0x0067e2f6, ADD ESP,0x10 at 0x0067e2fe) before a bare RET at 0x0067e301. The test is on the low BYTE, so only bit 0 of the word is given meaning; the other 31 are read by the load and not consulted.', 'observed': True, 'ordinal': 1, 'read': True, 'width_bytes': 4, 'written': False}"
  ],
  "receiver": true,
  "receiver_register": "ECX",
  "ret_form": "RET 0x4",
  "return_note": "pointer to the receiver",
  "return_register": "EAX",
  "return_semantics": [
    "0x0067e6c8 MOV EAX,ESI puts the receiver in EAX on the single exit path, taken by both the gated and the ungated path. This CONTRADICTS the persisted SDK/Ghidra signature
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
      "callsite": "0x0067e6b3",
      "direction": "out",
      "other": "0x0067e2b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0067e6c0",
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
    "global:PASS",
    "global:g_cheat_func3ch_ports"
  ],
  "types": [
    "CheatManager* (the receiver), following 0x0067e6c8 MOV EAX,ESI rather than the SDK void",
    "pointer to the receiver",
    "pointer_to_the_receiver, an alias of void*. The alias is named from the persisted ABI record's own abi.return_type string, \"pointer to the receiver\", and no more"
  ],
  "vtables": [
    "vtable:0x014018b0"
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
      "The branch is inert unless the gate word has bit 0 set; a differential run that passes an even word will exercise only the teardown path.",
      "The function is only reachable through vtable slot 20, so observing it at all requires a live cCheatManager constructed by 0x0067e100 (which stores 0x014018b0) and a caller that dispatches that slot.",
      "The teardown path requires receiver+0x14 to be non-null before the indirect call at 0x0067e2e1 can happen at all."
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
      "callsite": "0x0067e6b3",
      "direction": "out",
      "other": "0x0067e2b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0067e6c0",
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
    "id": "scc-0188",
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__cCheatManager__func3Ch.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__cCheatManager__func3Ch.c",
    "reconstruction/staging/pkg-cheat-func3ch-0067e6b0/cheat_func3ch_0067e6b0.cpp",
    "reconstruction/staging/pkg-cheat-func3ch-0067e6b0/cheat_func3ch_0067e6b0.hpp",
    "reconstruction/staging/pkg-cheat-func3ch-0067e6b0/cheat_func3ch_0067e6b0_model_test.cpp",
    "reconstruction/staging/pkg-dfw-0067e6b0/dfw_0067e6b0.cpp",
    "reconstruction/staging/pkg-dfw-0067e6b0/dfw_0067e6b0_model_test.cpp",
    "reconstruction/staging/pkg-dfw-0067e6b0/dfw_0067e6b0_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-cheat-func3ch-0067e6b0/0067e6b0.json",
    "reconstruction/metadata/pkg-dfw-0067e6b0/0067e6b0.json"
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
    "Can the branch ever be taken as not-taken in the original process? runtime_metadata.gates says the branch is inert for an even gate word and that the function is only reachable through vtable slot 20. No trace exists in this repository, so this is unresolved rather than answered.",
    "Is 0x0067e2b0 a destructor? It calls vtable slot +0x10 of the object at +0x14 and then writes &PTR_purecall_0141b5ac into the receiver, which is the MSVC vptr-reset shape a base destructor performs, but the listing names nothing and the only inbound reference is this call site.",
    "Is 0x0067e2b0 a destructor? It calls vtable slot displacement 0x10 of the object at receiver+0x14 and its tail target writes &PTR_purecall_0141b5ac into the receiver, which is the MSVC vptr-reset shape a base destructor performs. Nothing in the listing names it and this package does not claim it.",
    "Is the returned EAX consumed by anyone? The only inbound reference is the vtable slot at 0x01401900 and no call site of that slot is known.",
    "Is the returned EAX consumed by anyone? The only inbound reference to the function is the vtable slot at 0x01401900, and no call site of that slot is known.",
    "The branch is inert unless the gate word has bit 0 set; a differential run that passes an even word will exercise only the teardown path.",
    "The function is only reachable through vtable slot 20, so observing it at all requires a live cCheatManager constructed by 0x0067e100 (which stores 0x014018b0) and a caller that dispatches that slot.",
    "The 
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/App__cCheatManager__func3Ch.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-cheat-func3ch-0067e6b0/0067e6b0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-dfw-0067e6b0/0067e6b0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-cheat-func3ch-0067e6b0/cheat_func3ch_0067e6b0.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-cheat-func3ch-0067e6b0/cheat_func3ch_0067e6b0.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-cheat-func3ch-0067e6b0/cheat_func3ch_0067e6b0_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-dfw-0067e6b0/dfw_0067e6b0.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-dfw-0067e6b0/dfw_0067e6b0_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-dfw-0067e6b0/dfw_0067e6b0_types.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/App__cCheatManager__func3Ch.c",
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
      "ref": "reconstruction/metadata/pkg-cheat-func3ch-0067e6b0/0067e6b0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg-dfw-0067e6b0/0067e6b0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-cheat-func3ch-0067e6b0/cheat_func3ch_0067e6b0.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "rec
[TRUNCATED]
```
