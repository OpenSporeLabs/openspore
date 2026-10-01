# Reconstruction context 0x00c472e0

- Status: `partial`
- Content SHA-256: `303d06b165086e83fc26adc307df1593ef8fe5bc125f684a0122aca6c60c51ef`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00c472e0",
  "phase": "reconstruction",
  "target": "0x00c472e0"
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
  "va": "0x00c472e0"
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
  "content_sha256": "a173a7f6d7cbbddbe01db669f230b9efd32ae038480148e46c8875b45312c255",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00c472e0 failed: Decompilation did not complete. Reason: ",
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
  "hidden_this_register": "ECX, read at 0x00c472e3 into ESI and never written afterwards",
  "ordinary_stack_argument_slots": 0,
  "receiver": true,
  "ret_form": "RET",
  "return_register": "none (EAX is scratch)",
  "return_semantics": "no value; EAX is clobbered by the four callees and never written back",
  "return_type": "void",
  "return_width_bytes": 0,
  "saved_registers": [
    {
      "pop": "0x00c47340",
      "push": "0x00c472e0",
      "register": "EBX"
    },
    {
      "pop": "0x00c4733f",
      "push": "0x00c472e1",
      "register": "EBP"
    },
    {
      "pop": "0x00c4733e",
      "push": "0x00c472e2",
      "register": "ESI"
    },
    {
      "pop": "0x00c4733d",
      "push": "0x00c472eb",
      "register": "EDI"
    }
  ],
  "stack_arguments": [],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "RET at 0x00c47341"
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "context_word_read_00ce6950",
      "reconstructed": true,
      "va": "0x00ce6950"
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4b760"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4db40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4e230"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4f160"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4fe60"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c50190"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c50460"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c51ac0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c51e40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c52e30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c52ea0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c55500"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c5f280"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c5f360"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c61570"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c62100"
    }
  ],
  "edge_rows": [
    {
      "callsite": 
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
      "A runtime differential test would be needed to confirm the runtime value of 0x0167eb44, the number of records the registry accumulates across a mission transition, and that no runtime patch retargets the two virtual slots.",
      "No original-process trace exists for 0x00c472e0. The classification rests entirely on static reads of SporeApp.exe 3.1.0.22.",
      "The concrete overrides reached through slots +0x10c and +0xa4 can only be named by observing a receiver whose vtable base is known at run time."
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
      "name": "context_word_read_00ce6950",
      "reconstructed": true,
      "va": "0x00ce6950"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4b760"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4db40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4e230"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4f160"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4fe60"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c50190"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c50460"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c51ac0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c51e40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c52e30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c52ea0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c55500"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c5f280"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c5f360"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c61570"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c62100"
    },
    {
      "na
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
    "package": "PKG-11-H4-HELPER-WAVE3",
    "score": 3,
    "symbol": "context_word_read_00ce6950",
    "va": "0x00ce6950"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-APP-SAFE-WAVE11",
    "score": 2,
    "symbol": "property_record_assign_pair_004279d0",
    "va": "0x004279d0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-APP-SAFE-WAVE11",
    "score": 2,
    "symbol": "property_record_assign_scalar_00428060",
    "va": "0x00428060"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-EDITOR-SAFE-WAVE11",
    "score": 2,
    "symbol": "editor_paint_commit_0043ac40",
    "va": "0x0043ac40"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-APP-SAFE-WAVE11",
    "score": 2,
    "symbol": "model_parts_apply_properties_00447150",
    "va": "0x00447150"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-APP-SAFE-WAVE11",
    "score": 2,
    "symbol": "pair_vector_insert_004786e0",
    "va": "0x004786e0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-EDITOR-SAFE-WAVE11",
    "score": 2,
    "symbol": "editor_entry_expand_004ad6f0",
    "va": "0x004ad6f0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-10-EDITOR-DISPATCH",
    "score": 2,
    "symbol": "Editors_EditorModel_SetColor_raw_004ae250",
    "va": "0x004ae250"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/wave13-pilot-core-b01/c472e0_mission_publish.cpp",
    "reconstruction/staging/wave13-pilot-core-b01/wave13_pilot_core_b01_model_test.cpp",
    "reconstruction/staging/wave13-pilot-core-b01/wave13_pilot_core_b01_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-pilot-core-b01/00c472e0.json"
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
    "A runtime differential test would be needed to confirm the runtime value of 0x0167eb44, the number of records the registry accumulates across a mission transition, and that no runtime patch retargets the two virtual slots.",
    "Is 0x0167eb44 guaranteed non-null at the point of use? This function dereferences the result of 0x00b3d4a0 into ECX without a null check, so a null registry would fault inside 0x00aeb160. No static evidence establishes that the global is initialised first.",
    "Is the +0x184 read on the +0x13c leaf a field or the start of a nested object? Only one dword is consumed and 0x00ce6950 exposes nothing further.",
    "No original-process trace exists for 0x00c472e0. The classification rests entirely on static reads of SporeApp.exe 3.1.0.22.",
    "The concrete overrides reached through slots +0x10c and +0xa4 can only be named by observing a receiver whose vtable base is known at run time.",
    "What class owns this function? It is non-virtual and appears in no vtable, so cMission remains a candidate. The 20 callers are SetState overrides of derived mission types, so the receiver is at least a cMission subclass, but which subclass varies per call site and is not determinable statically.",
    "What do the two dispatched virtuals do? Slot +0x10c is called with (mission, 0, 0) and slot +0xa4 with no arguments, and cMission.h suggests GetConversationID at +0xa4 and func10Ch at +0x10c, but the declared func10Ch arity contradicts the call and no vtable was found to confirm either.",
    "What does the dwo
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-pilot-core-b01/00c472e0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-pilot-core-b01/c472e0_mission_publish.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-pilot-core-b01/wave13_pilot_core_b01_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-pilot-core-b01/wave13_pilot_core_b01_types.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave13-pilot-core-b01/00c472e0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-pilot-core-b01/c472e0_mission_publish.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-pilot-core-b01/wave13_pilot_core_b01_model_test.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-pilot-core-b01/wave13_pilot_core_b01_types.hpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "recon
[TRUNCATED]
```
