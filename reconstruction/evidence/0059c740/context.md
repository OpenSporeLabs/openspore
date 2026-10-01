# Reconstruction context 0x0059c740

- Status: `partial`
- Content SHA-256: `cc69eacf2da1e1f6aa7f08e46b9b20b7e568e45b8b2d40350989831a09fa5241`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x0059c740",
  "phase": "reconstruction",
  "target": "0x0059c740"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "map_int_EditorCreatureControllerPtr__get",
  "package": null,
  "subsystem": "GameGlobal",
  "va": "0x0059c740"
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
  "status": "candidate"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "c2b4ff5bdacde3a6cd95fb020a191c681022f52186ea7319d4ed1f7d3df6ce98",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x0059c740 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "__thiscall (receiver in ECX, callee pops the one stack word)",
  "hidden_receiver": "explicit",
  "hidden_this_register": "ECX, read at 0x0059c740 and 0x0059c748 before anything else; never written",
  "ordinary_stack_argument_slots": 1,
  "receiver": true,
  "ret_form": "RET 0x4",
  "return_note": "(pointer to the mapped 4-byte value)",
  "return_observation": "0x0059c7b3 LEA EAX,[EDX + 0x14] on the hit path and 0x0059c7a1 MOV EAX,dword ptr [ESP + 0x18] / 0x0059c7a5 ADD EAX,0x14 on the insert path. Three call sites dereference the result exactly once (0x0059caf2 MOV EAX,dword ptr [EAX], 0x0059cb4a MOV ESI,dword ptr [EAX]) and one passes it as ECX to another method (0x0059c986), which is the behaviour of a pointer to a pointer.",
  "return_register": "EAX",
  "return_semantics": "the address of the mapped value inside the tree node, i.e. node + 0x14, on both the hit and the insert path; never the value itself",
  "return_type": "std::uint32_t*",
  "return_width_bytes": 4,
  "saved_registers": [
    "EBP, ESI, EDI (pushed 0x0059c746/0x0059c747/0x0059c74b, popped 0x0059c7a8/0x0059c7a9/0x0059c7aa and 0x0059c7b1/0x0059c7b2/0x0059c7b6)"
  ],
  "stack_arguments": [
    {
      "address_at_entry": "[ESP_entry + 0x4]",
      "loaded_by": "0x0059c74c MOV EDI,dword ptr [ESP + 0x18] (ESP is 0x14 below entry)",
      "note": "0x0059c77b MOV byte ptr [ESP + 0x18],0x0 overwrites the low byte of this argument slot itself; the slot is dead after 0x0059c74c, and the body then reuses it as the out-parameter cell for the insert port.",
  
[TRUNCATED]
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
      "va": "0x0059c830"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059c9c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059ca70"
    },
    {
      "name": "EditorAnimWorld_GetCreatureController_0059cac0",
      "reconstructed": true,
      "va": "0x0059cac0"
    },
    {
      "name": "EditorAnimWorld_PlayAnimation_0059cb10",
      "reconstructed": true,
      "va": "0x0059cb10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059cbd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059cc40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059cd20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059cdb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059ce30"
    },
    {
      "name": "EditorAnimWorld_SetTargetAngle_0059cea0",
      "reconstructed": true,
      "va": "0x0059cea0"
    },
    {
      "name": "EditorAnimWorld_SetTargetPosition_0059cf00",
      "reconstructed": true,
      "va": "0x0059cf00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059cf60"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059cfb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059d010"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059d060"
    }
  ],
 
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "std::uint32_t* (pointer to the mapped 4-byte value)"
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
      "A differential test must confirm the mapped handle the insert path produces, which no static evidence in this batch pins down.",
      "A differential test must establish whether the key pointer is ever null in practice, because the miss path dereferences it at 0x0059c775.",
      "A differential test must exercise the miss path and observe what 0x0059c520 writes into the caller's argument slot, since that value becomes the return value; a wrong node there would be an immediate fault in every caller.",
      "No original-process trace exists for 0x0059c740. Every statement here is static."
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
      "va": "0x0059c830"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059c9c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059ca70"
    },
    {
      "name": "EditorAnimWorld_GetCreatureController_0059cac0",
      "reconstructed": true,
      "va": "0x0059cac0"
    },
    {
      "name": "EditorAnimWorld_PlayAnimation_0059cb10",
      "reconstructed": true,
      "va": "0x0059cb10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059cbd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059cc40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059cd20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059cdb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059ce30"
    },
    {
      "name": "EditorAnimWorld_SetTargetAngle_0059cea0",
      "reconstructed": true,
      "va": "0x0059cea0"
    },
    {
      "name": "EditorAnimWorld_SetTargetPosition_0059cf00",
      "reconstructed": true,
      "va": "0x0059cf00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059cf60"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059cfb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059d010"
    },
    {
      "name": null,
      "reconstructed": false,
      "
[TRUNCATED]
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
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 6,
    "symbol": "FUN_00ff3f00",
    "va": "0x00ff3f00"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-EDITOR-RUNTIME-WAVE7",
    "score": 3,
    "symbol": "EditorAnimWorld_GetCreatureController_0059cac0",
    "va": "0x0059cac0"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-EDITOR-RUNTIME-WAVE7",
    "score": 3,
    "symbol": "EditorAnimWorld_PlayAnimation_0059cb10",
    "va": "0x0059cb10"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-EDITOR-RUNTIME-WAVE7",
    "score": 3,
    "symbol": "EditorAnimWorld_SetTargetAngle_0059cea0",
    "va": "0x0059cea0"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-EDITOR-RUNTIME-WAVE7",
    "score": 3,
    "symbol": "EditorAnimWorld_SetTargetPosition_0059cf00",
    "va": "0x0059cf00"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/wave13-pilot-gameglobal-b03/59c740_map_get_or_create.cpp",
    "reconstruction/staging/wave13-pilot-gameglobal-b03/59c740_map_get_or_create.hpp",
    "reconstruction/staging/wave13-pilot-gameglobal-b03/59c740_map_get_or_create_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-pilot-gameglobal-b03/0059c740.json"
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
        "0x0059c740"
      ],
      "kind": "semantic_decomp_contradiction",
      "path": "evidence.6",
      "source": "knowledgegraph/research/semantic-decomp/worker-01-gameglobal.json",
      "statement": {
        "kind": "repository_contradiction",
        "source": "knowledgegraph/research/global-campaign-2026/conflicts/track-a-type-signature.json:602-779",
        "statement": "The conflict artifact calls the target an ordered lower-bound helper, while the live target body and sibling 0x0059c740 enforce exact-key selection."
      },
      "va": "0x00e5c780"
    }
  ],
  "unresolved_questions": [
    "A differential test must confirm the mapped handle the insert path produces, which no static evidence in this batch pins down.",
    "A differential test must establish whether the key pointer is ever null in practice, because the miss path dereferences it at 0x0059c775.",
    "A differential test must exercise the miss path and observe what 0x0059c520 writes into the caller's argument slot, since that value becomes the return value; a wrong node there would be an immediate fault in every caller.",
    "Are the 22 callers all operating on the same container instance, or does 0x0059c740 serve several containers of this instantiation? Only the four named editor callers were traced to cEditorAnimWorld+0x08.",
    "Call site 0x0059c981 can pass a null key pointer (0x0059c972 XOR EDI,EDI). On the miss path this body dereferences it unconditionally (0x0059c775), so that path would fault. Whether the container is guaranteed empty th
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-pilot-gameglobal-b03/0059c740.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-pilot-gameglobal-b03/59c740_map_get_or_create.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-pilot-gameglobal-b03/59c740_map_get_or_create.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-pilot-gameglobal-b03/59c740_map_get_or_create_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave13-pilot-gameglobal-b03/0059c740.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-pilot-gameglobal-b03/59c740_map_get_or_create.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-pilot-gameglobal-b03/59c740_map_get_or_create.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-pilot-gameglobal-b03/59c740_map_get_or_create_model_test.cpp",
      "source_class": "committed_artifact"
    }
  ],
  
[TRUNCATED]
```
