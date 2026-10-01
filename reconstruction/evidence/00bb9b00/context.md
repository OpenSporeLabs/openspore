# Reconstruction context 0x00bb9b00

- Status: `partial`
- Content SHA-256: `912c23a076564566a765234330e7b2b7ac2d7eb103bf73e943775674c75f8238`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00bb9b00",
  "phase": "reconstruction",
  "target": "0x00bb9b00"
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
  "va": "0x00bb9b00"
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
  "content_sha256": "40670a2c1f497ad9bfad569304fdf3c06158f4d67e311a4c58e786e574d934a6",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00bb9b00 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "__thiscall with two callee-popped stack words",
  "hidden_this_register": "ECX, read at 0x00bb9b0b and 0x00bb9b17, never written",
  "ordinary_stack_argument_slots": 2,
  "receiver": true,
  "ret_form": "RET 0x8 on both paths",
  "return_register": "none",
  "return_semantics": "no value; the function's only effect is the read-modify-write of the receiver's +0x5c dword",
  "return_type": "void",
  "return_width_bytes": 0,
  "saved_registers": [],
  "stack_arguments": [
    {
      "slot": "[ESP+0x4]",
      "use": "the 32-bit mask, used whole in the OR path and after a NOT in the AND path"
    },
    {
      "slot": "[ESP+0x8]",
      "use": "the set/clear selector, read as a byte and compared against 0",
      "width": 1
    }
  ],
  "stack_cleanup_bytes": 8,
  "stack_cleanup_owner": "callee",
  "termination": "0x00bb9b0e and 0x00bb9b1a"
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
      "va": "0x00b294c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba6cf0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba7dc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba8830"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00baac30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bad940"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00baf630"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb21b0"
    },
    {
      "name": "star_regenerate_00bb4af0",
      "reconstructed": true,
      "va": "0x00bb4af0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb4ba0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb4f30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb5640"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb5d80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb6040"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb80f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c5b660"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00b296d3",
      "direction": "in",
      "other": "0x00b294c0",
      "reference_type": 
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
      "A runtime trace would be needed to observe the actual flag word of a real star record before and after a state transition, and to confirm that no other code path writes +0x5c outside this function and the two siblings that read it.",
      "No original-process trace exists for 0x00bb9b00; every claim is static.",
      "The undocumented bit meanings can only be resolved by correlating runtime flag values with game events, which no recorded run provides."
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
      "va": "0x00b294c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba6cf0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba7dc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba8830"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00baac30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bad940"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00baf630"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb21b0"
    },
    {
      "name": "star_regenerate_00bb4af0",
      "reconstructed": true,
      "va": "0x00bb4af0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb4ba0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb4f30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb5640"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb5d80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb6040"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb80f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c5b660"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c5c470"
    },
    {
      "name":
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
    "package": "PKG-14-A2-WORLD-LIFECYCLE-WAVE2",
    "score": 3,
    "symbol": "star_regenerate_00bb4af0",
    "va": "0x00bb4af0"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/wave13-pilot-core-b01/bb9b00_star_record_set_flags.cpp",
    "reconstruction/staging/wave13-pilot-core-b01/wave13_pilot_core_b01_model_test.cpp",
    "reconstruction/staging/wave13-pilot-core-b01/wave13_pilot_core_b01_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-pilot-core-b01/00bb9b00.json"
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
    "A runtime trace would be needed to observe the actual flag word of a real star record before and after a state transition, and to confirm that no other code path writes +0x5c outside this function and the two siblings that read it.",
    "Do all 24 callers use only single-bit masks? The three inspected windows pass 0x1, 0x2, 0x4, 0x8000 and 0x40000000, all single-bit, but 0x00bb4f30's loop passes the SAME mask for every entry while loading a different dword from the table into ECX's target field via the callee - so the per-entry value is read but not used as a mask. That inconsistency is unexplained and the remaining callers were not checked.",
    "Is the +0x5c word shared with any other structure? cStarRecord.h places mFlags there, and the SDK's own TODO comment at cStarRecord.h:105 reads 'TODO 1 << 4 (16) is visited? sub_BB8B50', which suggests the reverse engineer was themselves unsure about this field's flag discipline.",
    "Is the function ever called with a mask of 0? That would be a no-op in both directions, and no inspected caller does it, but nothing in the code forbids it.",
    "No original-process trace exists for 0x00bb9b00; every claim is static.",
    "The undocumented bit meanings can only be resolved by correlating runtime flag values with game events, which no recorded run provides.",
    "What do bits 2, 15 and 30 mean? They are set or cleared by shipping callers but are undocumented in cStarRecord.h, and their names cannot be recovered statically.",
    "What do bits 3, 6 and 9 mean? cStarRecord.h 
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-pilot-core-b01/00bb9b00.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-pilot-core-b01/bb9b00_star_record_set_flags.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-pilot-core-b01/wave13_pilot_core_b01_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-pilot-core-b01/wave13_pilot_core_b01_types.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave13-pilot-core-b01/00bb9b00.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-pilot-core-b01/bb9b00_star_record_set_flags.cpp",
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
    
[TRUNCATED]
```
