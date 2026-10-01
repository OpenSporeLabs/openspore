# Reconstruction context 0x00b9aa10

- Status: `partial`
- Content SHA-256: `ac8a76b751f646201338cbfec25b0dd8d1c6bf08eb76c99ca3430c0f83eedc2b`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00b9aa10",
  "phase": "reconstruction",
  "target": "0x00b9aa10"
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
  "va": "0x00b9aa10"
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
  "content_sha256": "0648ffee46aa32eb3b733a086e14e919ed24ad8a8b2866242ab81234b77bfac4",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00b9aa10 failed: Decompilation did not complete. Reason: ",
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
  "hidden_receiver": "none; ECX is only ever an explicit argument to the __thiscall callees",
  "hidden_this_register": "ECX is loaded with the species manager, the record's property list or an immediate state pointer before each thiscall; it is never read as an implicit receiver",
  "ordinary_stack_argument_slots": 4,
  "receiver": false,
  "ret_form": "RET",
  "return_observation": "the only RET is 0x00b9b088, a bare C3 with no immediate, and the four POPs restore the saved registers immediately before it",
  "return_register": "none",
  "return_semantics": "no value; the body has no write to EAX on any exit path and every path ends at the single epilogue",
  "return_type": "void",
  "return_width_bytes": 0,
  "saved_registers": [
    "EBX",
    "ESI",
    "EDI"
  ],
  "stack_arguments": [
    {
      "ebp_offset": "+0x08",
      "index": 1,
      "meaning": "Vector3*; loaded at 0x00b9addf MOV EDX,dword ptr [EBP + 0x8] and pushed at 0x00b9ae41 as the second argument of the free-cell search. The same pointer is the search's output, so it is an in/out up-direction-then-position slot.",
      "width": 4
    },
    {
      "ebp_offset": "+0x0c",
      "index": 2,
      "meaning": "base of a std::uint32_t array; 0x00b9aab1 MOV ECX,dword ptr [EBP + 0xc] then 0x00b9aab4 MOV EAX,dword ptr [ECX + EAX*0x4]",
      "width": 4
    },
    {
      "ebp_offset": "+0x10",
      "index": 3,
      "meaning": "element count; 0x00b9aaa8 CMP dword ptr [EBP + 0x10],EAX with JBE to skip the loop, and 0x00b9b05f CMP EAX,dword ptr [
[TRUNCATED]
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "FUN_004df420",
      "reconstructed": false,
      "va": "0x004df420"
    },
    {
      "name": "FUN_00b3d300",
      "reconstructed": true,
      "va": "0x00b3d300"
    },
    {
      "name": "simulator_game_input_manager_get_00b3d350",
      "reconstructed": true,
      "va": "0x00b3d350"
    },
    {
      "name": "FUN_00b5b800",
      "reconstructed": false,
      "va": "0x00b5b800"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b9aa10"
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b9aa10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b9b090"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b9c830"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b9caa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b9d6d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b9d820"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba1590"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00b9b03f",
      "direction": "in",
      "other": "0x00b9aa10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00b9baf6",
      "direction": "in",
      "other": "0x00b9b090",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00b9ca5f",
      "direction": "in",
      "other": "0x00b9c830",
      "reference_type": "direct-call"
    },
    {
   
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
      "A runtime trace is required to confirm the discarded draw at 0x00b9af7b really is dead in the shipping build and not consumed by a patched 0x00b906a0.",
      "A runtime trace is required to determine the maximum recursion depth, since neither the self-recursion nor the mutual recursion with 0x00b9b090 has a bound in the body.",
      "A runtime trace is required to observe whether the sorted table at 0x0168890c ever becomes non-empty, which is the only way to learn its element layout.",
      "A runtime trace is required to read the record floats at +0x300/+0x304 and the component selector at 0x0156c060, which together decide the placement count and the acceptance threshold.",
      "No original-process trace has ever been captured for 0x00b9aa10; every claim here is static. The original Cell stage has never been entered in any recorded run."
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
      "name": "FUN_004df420",
      "reconstructed": false,
      "va": "0x004df420"
    },
    {
      "name": "FUN_00b3d300",
      "reconstructed": true,
      "va": "0x00b3d300"
    },
    {
      "name": "simulator_game_input_manager_get_00b3d350",
      "reconstructed": true,
      "va": "0x00b3d350"
    },
    {
      "name": "FUN_00b5b800",
      "reconstructed": false,
      "va": "0x00b5b800"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b9aa10"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b9aa10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b9b090"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b9c830"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b9caa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b9d6d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b9d820"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba1590"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00b9b03f",
      "direction": "in",
      "other": "0x00b9aa10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00b9baf6",
      "direction": "in",
      "other": "0x00b9b090",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00b9ca5f",
      "direction": "in"
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
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 3,
    "symbol": "FUN_00b3d300",
    "va": "0x00b3d300"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-GAME-INPUT-WAVE7",
    "score": 3,
    "symbol": "simulator_game_input_manager_get_00b3d350",
    "va": "0x00b3d350"
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
    "reconstruction/staging/wave13-w1-dispatch-b02/b9aa10_place_species_on_cube_map.cpp",
    "reconstruction/staging/wave13-w1-dispatch-b02/b9aa10_place_species_on_cube_map.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-dispatch-b02/00b9aa10.json"
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
    "A runtime trace is required to confirm the discarded draw at 0x00b9af7b really is dead in the shipping build and not consumed by a patched 0x00b906a0.",
    "A runtime trace is required to determine the maximum recursion depth, since neither the self-recursion nor the mutual recursion with 0x00b9b090 has a bound in the body.",
    "A runtime trace is required to observe whether the sorted table at 0x0168890c ever becomes non-empty, which is the only way to learn its element layout.",
    "A runtime trace is required to read the record floats at +0x300/+0x304 and the component selector at 0x0156c060, which together decide the placement count and the acceptance threshold.",
    "Five of the eight recorded callsites (0x00b9cc2c, 0x00b9d327, 0x00b9d806, 0x00b9f84e, 0x00ba1b01, 0x00ba1bad) were not disassembled.",
    "No original-process trace has ever been captured for 0x00b9aa10; every claim here is static. The original Cell stage has never been entered in any recorded run.",
    "The values of 0x016895a4, 0x0156c060, 0x01688890/94/98, 0x0168890c/10/20 and 0x0167eaec are all runtime state and are zero in the file image, so the component selector, the bucket default and the table contents are not statically predictable.",
    "What class owns the per-id record read at +0x10, +0x14, +0x2d4..+0x310, +0x334, +0x39c/+0x3a0, +0x3b0/+0x3b4 and +0x43c? No SDK structure matches these offsets, and the 0x19a8-byte stride at the caller 0x00b9c830 matches no known type.",
    "What do the seven property keys 0x4934caca, 0x1ee4cafd, 0x6
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-w1-dispatch-b02/00b9aa10.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b02/b9aa10_place_species_on_cube_map.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b02/b9aa10_place_species_on_cube_map.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave13-w1-dispatch-b02/00b9aa10.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b02/b9aa10_place_species_on_cube_map.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b02/b9aa10_place_species_on_cube_map.hpp",
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
 
[TRUNCATED]
```
