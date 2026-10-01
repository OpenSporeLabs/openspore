# Reconstruction context 0x00bbaa60

- Status: `partial`
- Content SHA-256: `8a5a725fa39a0ec9446b6d33812c47d61fdbe27dda91ef537eb70c9e2e011350`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00bbaa60",
  "phase": "reconstruction",
  "target": "0x00bbaa60"
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
  "va": "0x00bbaa60"
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
  "content_sha256": "cdad127cda2844190154a67c4d4a00ba6d2ac27946d16d4236291b727efc5549",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00bbaa60 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "__thiscall with one callee-popped stack word",
  "hidden_this_register": "ECX, read at 0x00bbaa61 and never written",
  "ordinary_stack_argument_slots": 1,
  "receiver": true,
  "ret_form": "RET 0x4",
  "return_observation": "0x00bbaa72 MOV EAX,dword ptr [EAX + ECX*0x4] is the last write to EAX before the pops, so the returned register holds exactly the loaded element and no callee residue.",
  "return_register": "EAX",
  "return_semantics": "one element of the receiver's planet vector, as loaded at 0x00bbaa72; the callee's return value is discarded and never reaches EAX",
  "return_type": "void*",
  "return_width_bytes": 4,
  "saved_registers": [
    {
      "pop": "0x00bbaa75",
      "push": "0x00bbaa60",
      "register": "ESI"
    }
  ],
  "stack_arguments": [
    {
      "slot": "[ESP+0x8] at entry",
      "use": "element index, used as a raw scale-of-4 offset with no sign extension and no bounds check",
      "width": 4
    }
  ],
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "callee",
  "termination": "RET 0x4 at 0x00bbaa76"
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
      "va": "0x00ba6dc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bad940"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bafae0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb2330"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb23e0"
    },
    {
      "name": "FUN_00bb57b0",
      "reconstructed": false,
      "va": "0x00bb57b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb59b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb5b70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb6700"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb7510"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb7620"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb8b20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00de6f20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00deb930"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ded7d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00df6740"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00ba6df6",
      "direction": "in",
      "other": "0x00ba6dc0",
      "reference_type": "direct-cal
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
      "A runtime trace would be needed to observe the actual StarIDs the sync requests, to confirm that the vector is repopulated rather than merely reallocated on the second call, and to see whether any caller ever passes an out-of-range index.",
      "No original-process trace exists for 0x00bbaa60; every claim is static.",
      "The runtime value of mPlanetCount and of the vector's capacity for a real star is not recoverable statically."
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
      "va": "0x00ba6dc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bad940"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bafae0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb2330"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb23e0"
    },
    {
      "name": "FUN_00bb57b0",
      "reconstructed": false,
      "va": "0x00bb57b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb59b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb5b70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb6700"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb7510"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb7620"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb8b20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00de6f20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00deb930"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ded7d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00df6740"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00df6db0"
    },
    {
      "name": null,
    
[TRUNCATED]
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
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
  },
  {
    "match_basis": [
      "shared_types:void*"
    ],
    "package": "pkg-orchestrate-dogfood-008db310",
    "score": 3,
    "symbol": "pf_index_write_bounds_008db310",
    "va": "0x008db310"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/wave13-pilot-core-b01/bbaa60_star_record_planet.cpp",
    "reconstruction/staging/wave13-pilot-core-b01/wave13_pilot_core_b01_model_test.cpp",
    "reconstruction/staging/wave13-pilot-core-b01/wave13_pilot_core_b01_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-pilot-core-b01/00bbaa60.json"
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
    "A runtime trace would be needed to observe the actual StarIDs the sync requests, to confirm that the vector is repopulated rather than merely reallocated on the second call, and to see whether any caller ever passes an out-of-range index.",
    "Is 0x00bbaa60 ever called with the intent to trigger the load only, ignoring the result? The 20 canonical callers include several whose names suggest other subsystems, and none of the uninspected ones was checked for result use.",
    "No original-process trace exists for 0x00bbaa60; every claim is static.",
    "The runtime value of mPlanetCount and of the vector's capacity for a real star is not recoverable statically.",
    "What are the valid index bounds, and who guarantees them? Nothing here checks, so the contract is entirely on the callers; the 19 other canonical callers were not disassembled and might not all be well-behaved.",
    "What does the literal 0x5220cb8 in the per-iteration request mean? It has no SDK name and appears as a constant in the request word adjacent to the StarID.",
    "What is 0x00bba900 really? The SDK calls it GetPlanetRecords but the body is a boolean predicate over mPlanetCount and mFlags bit 12, and its JNZ leaves the function. Left unclassified; resolving it would sharpen the naming of this whole cluster.",
    "Which class and method is this, strictly? The evidence supports cStarRecord::GetPlanetRecord(size_t), but the SDK gives no address for that declaration and the function is in no vtable.",
    "Why does the sync advance the StarID by 
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-pilot-core-b01/00bbaa60.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-pilot-core-b01/bbaa60_star_record_planet.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-pilot-core-b01/wave13_pilot_core_b01_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-pilot-core-b01/wave13_pilot_core_b01_types.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave13-pilot-core-b01/00bbaa60.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-pilot-core-b01/bbaa60_star_record_planet.cpp",
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
    "re
[TRUNCATED]
```
