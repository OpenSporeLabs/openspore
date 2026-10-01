# Reconstruction context 0x00c471c0

- Status: `partial`
- Content SHA-256: `f03f6985b10e3eedc34410abdc6770cb652e8a2862801ecf61d7c8676cc19027`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00c471c0",
  "phase": "reconstruction",
  "target": "0x00c471c0"
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
  "va": "0x00c471c0"
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
  "content_sha256": "e0c8b1d2a08dd836a547ecbf95a73b61e8d00fe6a939c899a314218d80c8515c",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00c471c0 failed: Decompilation did not complete. Reason: ",
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
  "hidden_this_register": "ECX, read at 0x00c471c2 and reloaded at 0x00c471da, 0x00c47201 and 0x00c47222",
  "ordinary_stack_argument_slots": 1,
  "receiver": true,
  "ret_form": "JMP (tail transfer) on both exits; the function contains no RET of its own",
  "return_register": "none",
  "return_semantics": "no value; the terminal JMP hands control to a void callee and no register is written on the way out",
  "return_type": "void",
  "return_width_bytes": 0,
  "saved_registers": [
    {
      "pop": "0x00c4720c or 0x00c4722d",
      "push": "0x00c471c1",
      "register": "ESI"
    }
  ],
  "stack_arguments": [
    {
      "note": "holds the incoming receiver",
      "slot": "[ESP+4] at function entry",
      "written_by": "0x00c471c0 PUSH ECX"
    },
    {
      "note": "overwritten with the computed predicate before the +0x198 call; 0x00c47217 reads it back with MOV EAX,[ESP+0x4] and pushes it",
      "slot": "[ESP+4]",
      "written_by": "0x00c471ec MOV byte ptr [ESP+0x4],AL"
    }
  ],
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "callee, via the two explicit ADD ESP,0x4 instructions at 0x00c4720d and 0x00c4722e",
  "termination": "0x00c47210 JMP 0x01048ce0 and 0x00c47231 JMP 0x01048ce0"
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
      "name": null,
      "reconstructed": false,
      "va": "0x00c47240"
    },
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
      "name": null,
      "reconstructed": false,
      "va": "0x00c63130"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00c472ab",
      "direction": "in",
      "other": "0x00c47240",
      "reference_type": "direct-call"
    },

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
      "A runtime trace would be needed to see which of the two terminal slots is actually taken for a real mission transition, and to observe the seven counters the flush touches.",
      "Naming the four overrides requires a receiver whose vtable base is known at run time.",
      "No original-process trace exists for 0x00c471c0; every claim is static."
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
      "name": null,
      "reconstructed": false,
      "va": "0x00c47240"
    },
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
      "name": null,
      "reconstructed": false,
      "va": "0x00c63130"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c63170"
    },
    {
      "name": null,
      "reconst
[TRUNCATED]
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
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
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-APP-SAFE-WAVE11",
    "score": 2,
    "symbol": "pair_vector_construct_004b62a0",
    "va": "0x004b62a0"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/wave13-pilot-core-b01/c471c0_mission_settle.cpp",
    "reconstruction/staging/wave13-pilot-core-b01/wave13_pilot_core_b01_model_test.cpp",
    "reconstruction/staging/wave13-pilot-core-b01/wave13_pilot_core_b01_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-pilot-core-b01/00c471c0.json"
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
    "A runtime trace would be needed to see which of the two terminal slots is actually taken for a real mission transition, and to observe the seven counters the flush touches.",
    "Is the flush a no-op when the two virtuals did nothing? Both terminal slots have their results discarded, so if they are pure state changes with no dirty flag, the flush would be redundant - unresolvable statically.",
    "Naming the four overrides requires a receiver whose vtable base is known at run time.",
    "No original-process trace exists for 0x00c471c0; every claim is static.",
    "What are the seven counters the terminal flush walks, and what does 0x01021080 guard? The flush body is known; the domain is not. The flush is skipped entirely when 0x01021080 returns zero, so on some runs this function's last action would be nothing at all.",
    "What do the four dispatched virtuals do? Slot +0xf8 and +0xfc are boolean predicates, +0x19c is a no-argument action and +0x198 takes that one boolean. cMission.h places HasBeenFulfilled, HasFailed, func19Ch and func198h at exactly those offsets with exactly those arities, but no vtable was found to confirm it and two of the four header names are placeholders.",
    "What does the bit-1-of-+0x130 test mean in game terms? cMission.h names bit 1 kMissionFlagHideStarName, which would make the +0x19c exit a 'stop hiding the star name' action, but the SDK flag comments are themselves reverse-engineered and partly speculative.",
    "Which class owns this function? It is non-virtual and appears in no v
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-pilot-core-b01/00c471c0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-pilot-core-b01/c471c0_mission_settle.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-pilot-core-b01/wave13_pilot_core_b01_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-pilot-core-b01/wave13_pilot_core_b01_types.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave13-pilot-core-b01/00c471c0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-pilot-core-b01/c471c0_mission_settle.cpp",
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
    "recons
[TRUNCATED]
```
