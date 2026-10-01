# Reconstruction context 0x005a9200

- Status: `partial`
- Content SHA-256: `8147071f880fc73b966fbf1f295ccf7c4b7fafb4b809f37d925ef80138a11888`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x005a9200",
  "phase": "reconstruction",
  "target": "0x005a9200"
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
  "va": "0x005a9200"
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
  "content_sha256": "7181801f73ac2b07547d06236952d3a9a39f7586ab9987ac7408e7e15fe80bdb",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x005a9200 failed: Decompilation did not complete. Reason: ",
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
  "hidden_receiver": "none",
  "hidden_this_register": "ECX is never read before the first call and is only ever loaded as an explicit argument (0x005a92be, 0x005a92e1, 0x005a9276, 0x005a945c) or used as scratch (0x005a92a6 XOR ECX,ECX, 0x005a92f9 XOR ECX,ECX, 0x005a9450 MOV ECX,EAX, 0x005a92ef MOV ECX,EAX). There is no callee-side this.",
  "ordinary_stack_argument_slots": 1,
  "receiver": false,
  "ret_form": "RET",
  "return_observation": "0x005a9462: MOV AL,0x1 writes only the low byte. The body contains no other write to EAX after the last callee return, so nothing else is defined in the return register.",
  "return_register": "AL",
  "return_semantics": "unconditional true; the only write to the return register is MOV AL,0x1 at 0x005a9462, so bits 8..31 of EAX are undefined on exit. All three inspected callers discard the value.",
  "return_type": "std::uint8_t",
  "return_width_bytes": 1,
  "saved_registers": [
    "EBX",
    "ESI",
    "EDI"
  ],
  "stack_arguments": [],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "single exit at 0x005a9465; no early return exists in the 199-instruction body"
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "wave6_reference_00432a50",
      "reconstructed": true,
      "va": "0x00432a50"
    },
    {
      "name": "achievement_progress_flag_transition_00676ed0",
      "reconstructed": true,
      "va": "0x00676ed0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0067dcc0"
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005a94d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0064acd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b1dee0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d3c6a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d43e30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e84600"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x005a95ea",
      "direction": "in",
      "other": "0x005a94d0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0064b417",
      "direction": "in",
      "other": "0x0064acd0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00b1df94",
      "direction": "in",
      "other": "0x00b1dee0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d3c8ca",
      "direction": "in",
      "other": "0x00d3c6a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d45002",
      "direction": "in",
      "other": "0x00d43e30",
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
    "std::uint8_t"
  ],
  "vtables": [
    "vtable:0x013eb844"
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
      "A runtime trace is required to confirm 0x00676ed0's dead first argument is genuinely dead in the shipping build rather than read by an inlined or patched variant.",
      "A runtime trace is required to observe the actual value of [[0x015fd918]+0x3c]+0x118 at editor entry and therefore whether the mask write ever fires in the shipping configuration.",
      "A runtime trace is required to read the runtime-initialised 16 bytes at 0x015da7c4 and confirm the seeded ContentValidation matches the shipped illegal-character set.",
      "A runtime trace with a resolved IAppSystem vtable pointer is required to name the two notification consumers.",
      "No original-process trace has ever been captured for 0x005a9200; every claim here is static. The original Cell stage has never been entered in any recorded run."
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
      "name": "wave6_reference_00432a50",
      "reconstructed": true,
      "va": "0x00432a50"
    },
    {
      "name": "achievement_progress_flag_transition_00676ed0",
      "reconstructed": true,
      "va": "0x00676ed0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0067dcc0"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005a94d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0064acd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b1dee0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d3c6a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d43e30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e84600"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x005a95ea",
      "direction": "in",
      "other": "0x005a94d0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0064b417",
      "direction": "in",
      "other": "0x0064acd0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00b1df94",
      "direction": "in",
      "other": "0x00b1dee0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d3c8ca",
      "direction": "in",
      "other": "0x00d3c6a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d45002",
      "direction"
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
    "package": "PKG-WAVE6-CONTAINERS-MEMORY",
    "score": 3,
    "symbol": "wave6_reference_00432a50",
    "va": "0x00432a50"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-11-A3-ACHIEVEMENT-MISSION-WAVE2",
    "score": 3,
    "symbol": "achievement_progress_flag_transition_00676ed0",
    "va": "0x00676ed0"
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
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/wave13-w1-dispatch-b02/a9200_editor_request_submit.cpp",
    "reconstruction/staging/wave13-w1-dispatch-b02/a9200_editor_request_submit.hpp",
    "reconstruction/staging/wave13-w1-dispatch-b02/a9200_editor_request_submit_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-dispatch-b02/005a9200.json"
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
    "A runtime trace is required to confirm 0x00676ed0's dead first argument is genuinely dead in the shipping build rather than read by an inlined or patched variant.",
    "A runtime trace is required to observe the actual value of [[0x015fd918]+0x3c]+0x118 at editor entry and therefore whether the mask write ever fires in the shipping configuration.",
    "A runtime trace is required to read the runtime-initialised 16 bytes at 0x015da7c4 and confirm the seeded ContentValidation matches the shipped illegal-character set.",
    "A runtime trace with a resolved IAppSystem vtable pointer is required to name the two notification consumers.",
    "Is 0x00676ed0 really SetProgressFlags? Its class attribution is solid; the method attribution within the class is a body-shape inference and the SDK's own address for SetProgressFlags resolves to a sibling function.",
    "No original-process trace has ever been captured for 0x005a9200; every claim here is static. The original Cell stage has never been entered in any recorded run.",
    "The three remaining callers (0x00b1dee0, 0x00d3c6a0, 0x00d43e30) and the second site in 0x00e84600 were not disassembled.",
    "The values of 0x015da7c4..0x015da7d0 and of 0x015fd918 are runtime state; the file image is zero, so the seeded ContentValidation and the gate outcome cannot be predicted statically.",
    "What are the ids 0xb03bc30c and 0x00e11332? 0x00e11332 sits one below the SDK's kMsgSetGameModeByName = 0x00E11333, which is a family resemblance in the same message-id space and is not cl
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-w1-dispatch-b02/005a9200.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b02/a9200_editor_request_submit.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b02/a9200_editor_request_submit.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b02/a9200_editor_request_submit_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave13-w1-dispatch-b02/005a9200.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b02/a9200_editor_request_submit.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b02/a9200_editor_request_submit.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b02/a9200_editor_request_submit_model_test.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first
[TRUNCATED]
```
