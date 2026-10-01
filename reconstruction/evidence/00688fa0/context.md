# Reconstruction context 0x00688fa0

- Status: `partial`
- Content SHA-256: `14ca5091ab5d2e0961a1e9750421813defc97b301c7027e1ca32342627539581`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00688fa0",
  "phase": "reconstruction",
  "target": "0x00688fa0"
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
  "va": "0x00688fa0"
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
  "content_sha256": "b5b2b0a7a5cf277b13ef05c2333f66d04a717704400e55b5973a9f149411112b",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00688fa0 failed: Decompilation did not complete. Reason: ",
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
  "hidden_this_register": "ECX is only ever an explicit thiscall argument, loaded at 0x006890d9, 0x0068912b, 0x00689141, 0x00689150 and 0x0068915c",
  "ordinary_stack_argument_slots": 1,
  "receiver": false,
  "ret_form": "RET",
  "return_observation": "0x006891d8: MOV EAX,EBX immediately before the register restores, so the return value is whatever EBX held; 0x00689132 MOV EBX,EAX takes the constructor's result and 0x00689136 XOR EBX,EBX covers the failed-allocation path",
  "return_register": "EAX",
  "return_semantics": "the 0x24-byte object, or null when the second registry allocation failed",
  "return_type": "void*",
  "return_width_bytes": 4,
  "saved_registers": [
    "EBX",
    "EBP",
    "ESI",
    "EDI"
  ],
  "stack_arguments": [
    {
      "frame_offset": "[ESP + 0x5c] at 0x00688fb8 with ESP = entry - 0x58",
      "index": 1,
      "meaning": "a const wchar_t* naming a file; the caller at 0x00de4850 passes the literal 0x0147e040, which ghidra_read_memory shows is the UTF-16LE string \"GGEUserData.dat.tmp\"",
      "width": 4
    }
  ],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "single exit at 0x006891e5; no early return exists in the 203-instruction body"
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
      "callsite": "0x00580d08",
      "direction": "in",
      "other": "0x00580cb0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00b2930b",
      "direction": "in",
      "other": "0x00b28ec0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00bb4cef",
      "direction": "in",
      "other": "0x00bb4ba0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00de485f",
      "direction": "in",
      "other": "0x00de4850",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00689081",
      "direction": "out",
      "other": "0x00423650",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0068902d",
      "direction": "out",
      "other": "0x00429760",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00688fd3",
      "direction": "out",
      "other": "0x00579a90",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00689003",
      "direction": "out",
      "other": "0x00579a90",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00689065",
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "void*"
  ],
  "vtables": [
    "vtable:0x01408698",
    "vtable:0x014086e8"
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
      "A runtime trace is required to confirm the delete actually targets a removable file, since the predicate that would guard it is discarded.",
      "A runtime trace is required to observe what the service locator returns for the key 0x04729a47 and therefore what base directory is actually used.",
      "A runtime trace is required to resolve the four unknown virtual callees and the identity of the Simulator class at runtime.",
      "No original-process trace has ever been captured for 0x00688fa0; every claim here is static. The original Cell stage has never been entered in any recorded run."
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
      "callsite": "0x00580d08",
      "direction": "in",
      "other": "0x00580cb0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00b2930b",
      "direction": "in",
      "other": "0x00b28ec0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00bb4cef",
      "direction": "in",
      "other": "0x00bb4ba0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00de485f",
      "direction": "in",
      "other": "0x00de4850",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00689081",
      "direction": "out",
      "other": "0x00423650",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0068902d",
      "direction": "out",
      "other": "0x00429760",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00688fd3",
      "direction": "out",
      "other": "0x00579a90",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00689003",
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
      "shared_vtable:vtable:0x014086e8"
    ],
    "package": "pkg-editor-child-007f30d0",
    "score": 4,
    "symbol": "FUN_007f30d0",
    "va": "0x007f30d0"
  },
  {
    "match_basis": [
      "shared_types:void*"
    ],
    "package": "PKG-APP-SAFE-WAVE11",
    "score": 3,
    "symbol": "property_record_assign_pair_004279d0",
    "va": "0x004279d0"
  },
  {
    "match_basis": [
      "shared_types:void*"
    ],
    "package": "PKG-PALETTE-SAFE-WAVE11",
    "score": 3,
    "symbol": "palette_safe_wave11_fill_node_array_005c7ff0",
    "va": "0x005c7ff0"
  },
  {
    "match_basis": [
      "shared_types:void*"
    ],
    "package": "PKG-APP-SERVICES-SAFE-WAVE11",
    "score": 3,
    "symbol": "service_005fa8d0",
    "va": "0x005fa8d0"
  },
  {
    "match_basis": [
      "shared_types:void*"
    ],
    "package": "PKG-APP-SERVICES-SAFE-WAVE11",
    "score": 3,
    "symbol": "service_0060ee90",
    "va": "0x0060ee90"
  },
  {
    "match_basis": [
      "shared_types:void*"
    ],
    "package": "pkg-swarm-w1-00641fd0",
    "score": 3,
    "symbol": "sporepedia_cached_handle_00641fd0",
    "va": "0x00641fd0"
  },
  {
    "match_basis": [
      "shared_types:void*"
    ],
    "package": "pkg-vft-slot-006e64f0",
    "score": 3,
    "symbol": "re_006e64f0",
    "va": "0x006e64f0"
  },
  {
    "match_basis": [
      "shared_types:void*"
    ],
    "package": "PKG-UTFWIN-CORE-WAVE6",
    "score": 3,
    "symbol": "re_00835380",
    "va": "0x00835380"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/wave13-w1-dispatch-b02/b688fa0_gge_user_data_reset.cpp",
    "reconstruction/staging/wave13-w1-dispatch-b02/b688fa0_gge_user_data_reset.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-dispatch-b02/00688fa0.json"
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
    "A runtime trace is required to confirm the delete actually targets a removable file, since the predicate that would guard it is discarded.",
    "A runtime trace is required to observe what the service locator returns for the key 0x04729a47 and therefore what base directory is actually used.",
    "A runtime trace is required to resolve the four unknown virtual callees and the identity of the Simulator class at runtime.",
    "No original-process trace has ever been captured for 0x00688fa0; every claim here is static. The original Cell stage has never been entered in any recorded run.",
    "Three of the four callers were not disassembled, so their argument provenance is unverified.",
    "What are the 0x68-byte App object and its derived 8-byte sub-object created inside 0x0069fa60, and what stores them at small+0x1c?",
    "What are the four unresolved virtual callees at 0x01408698 slots +0x04 and +0x2c, and at PTR_FUN_0143679c slots +0x00 and +0x04?",
    "What class is registered under the name Simulator? The registry is only reachable through 0x00926020 and no SDK type matches either object.",
    "What does 0x0069df20, the one resolved virtual callee at slot +0x3c, do with the arguments 0 and 1?",
    "What does the concatenated path (base ++ name) get used for? It is built, compared against the output header, freed, and never passed to a syscall at this level.",
    "What is 0x00932960, the fallback of the directory predicate?",
    "Which of the four intermediate string headers does each of the four length-guarded
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-w1-dispatch-b02/00688fa0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b02/b688fa0_gge_user_data_reset.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b02/b688fa0_gge_user_data_reset.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave13-w1-dispatch-b02/00688fa0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b02/b688fa0_gge_user_data_reset.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b02/b688fa0_gge_user_data_reset.hpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.json"
  ],
  "required_categories": [
    "ABI",
    "CALLS",
    "GLOBALS",
    "FIELDS/OFFSETS",
    "CONSTANTS",
    "CONTROL FLOW",
    "VIRTUA
[TRUNCATED]
```
