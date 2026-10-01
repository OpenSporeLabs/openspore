# Reconstruction context 0x006a3330

- Status: `partial`
- Content SHA-256: `9446fdcc9b6063b442b2a862405f9af626138c335ba0f3014ab4bb700e5a2ed6`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x006a3330",
  "phase": "reconstruction",
  "target": "0x006a3330"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "App::cPropManager::CreateResource",
  "package": null,
  "subsystem": "App",
  "va": "0x006a3330"
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
  "content_sha256": "3e8d3c8b17b69916169053518661a7a6cf604e7b0354b16fc9540828c4a0ee5d",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x006a3330 failed: Decompilation did not complete. Reason: ",
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
    "entry_ESP+0x8",
    "entry_ESP+0xc",
    "entry_ESP+0x10",
    "entry_ESP+0x14"
  ],
  "receiver_register": "ECX",
  "ret_form": "RET 0x10",
  "return_observation": "Only AL is written on either exit, so the upper three bytes of the returned word are whatever the last register-indirect transfer left in EAX. The reconstruction returns a bool, which is the only reading the two exits support; the decompiler's own prototype is bool App__cPropManager__CreateResource(...) and agrees.",
  "return_register": "EAX",
  "return_semantics": "integral_in_EAX, concretised to bool by the two exits: MOV AL,0x1 at 0x006a33c9 on the success path and XOR AL,AL at 0x006a33ec on the failure path. categories.abi.return is {register EAX, register_class integral, type null, void_possible false}, so the record supplies the register and the class and leaves the type open; the two explicit byte writes are what fix it at 1 or 0, and nothing else about the word is claimed.",
  "return_type": "bool",
  "return_width_bytes": 4,
  "saved_registers": [
    "EBX",
    "EDI",
    "ESI"
  ],
  "stack_cleanup_bytes": 16,
  "stack_cleanup_owner": "callee",
  "termination": "RET 0x10"
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
      "callsite": "0x006a3373",
      "direction": "out",
      "other": "0x006a1b90",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a3358",
      "direction": "out",
      "other": "0x00f473a0",
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
    "vtable:0x014091a0"
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
      "callsite": "0x006a3373",
      "direction": "out",
      "other": "0x006a1b90",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a3358",
      "direction": "out",
      "other": "0x00f473a0",
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
    "id": "scc-0224",
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__cPropManager__CreateResource.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__cPropManager__CreateResource.c",
    "reconstruction/staging/pkg-propmanager-create-wave15/prop_manager_create_resource_006a3330.cpp",
    "reconstruction/staging/pkg-propmanager-create-wave15/prop_manager_create_resource_006a3330.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-propmanager-create-wave15/006a3330.json"
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
    "Do the four slot callees clean up their own stack words? The frame is balanced across all four transfers with no ADD ESP after any of them, so callee cleanup is an inference, and the three slot function-pointer types are declared __thiscall on that basis. A resolved slot target would confirm or refute it.",
    "Is the entry_ESP+0x8 object the same thing the receiver's slot at 0x24 expects as its first stack word? The listing passes the same EDI/ESI/EDI word to both dispatches, and Ghidra names it both an IRecord and a source of the three copied words. No record establishes the relationship.",
    "What are the four dispatch slots? Byte displacement 0x10 of the entry_ESP+0x8 object's table (0x006a338d), 0x24 of the receiver's own table (0x006a33b3), 0 (0x006a33c5) and 0x8 (0x006a33e4) of the created object's table. No record in this repository names any of them, and the record's own vtable association (0x014091a0) comes with vtable_reference_count 0, so it is a classifier claim and not a slot identity.",
    "What are the two direct callees? 0x00f473a0 is a six-word caller-cleaned call whose second word is a data address and whose first is 0x38, and 0x006a1b90 takes one word and a receiver in ECX and returns the object the body works on. Neither is identified by any record in this repository, and the object they produce is known only by the fact that the body returns it.",
    "What do the two data-segment addresses hold, and are the byte reads enough to call them grounded? 0x1408b44 is pushed as the second word of the 0
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/App__cPropManager__CreateResource.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-propmanager-create-wave15/006a3330.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-propmanager-create-wave15/prop_manager_create_resource_006a3330.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-propmanager-create-wave15/prop_manager_create_resource_006a3330.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/App__cPropManager__CreateResource.c",
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
      "ref": "reconstruction/metadata/pkg-propmanager-create-wave15/006a3330.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-propmanager-create-wave15/prop_manager_create_resource_006a3330.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-propmanager-create-wave15/prop_manager_create_resource_006a3330.hpp",
      "source_class": "committed_
[TRUNCATED]
```
