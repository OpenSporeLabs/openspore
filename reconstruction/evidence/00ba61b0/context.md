# Reconstruction context 0x00ba61b0

- Status: `partial`
- Content SHA-256: `b7fb11b16eb4ff0987028027fea1758f7808d65c7ef565a805fad6671c40d22d`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00ba61b0",
  "phase": "reconstruction",
  "target": "0x00ba61b0"
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
  "va": "0x00ba61b0"
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
  "content_sha256": "c930089bb23ec2b3c144e6fdd418597b186b505a24c31f2fe5b14110aad26468",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00ba61b0 failed: Decompilation did not complete. Reason: ",
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
  "hidden_receiver": "none. This is a factory, not a member function. ECX is a scratch register reused as the receiver of three successive calls.",
  "hidden_this_register": "ECX is never read on entry. It is loaded at 0x00ba61ce with the allocated block for the constructor, at 0x00ba61e4 with the same block for the setter, and at 0x00ba6204 for the slot +0x00 virtual. No incoming register carries a receiver.",
  "ordinary_stack_argument_slots": 2,
  "receiver": false,
  "ret_form": "RET",
  "return_register": null,
  "return_semantics": "No return value. The constructed object is delivered through the second argument, an out-parameter.",
  "return_type": "void",
  "return_width_bytes": 0,
  "saved_registers": [
    "ESI",
    "EDI"
  ],
  "stack_arguments": [
    {
      "index": 0,
      "offset_at_entry": "[ESP + 0x4]",
      "read_at": "0x00ba61df MOV EDI,[ESP + 0xC] with ESP = entry-8",
      "use": "written to the object's +0x08, passed to 0x00B8DA80 which stores it at +0x184, and passed to the slot +0x00 virtual through the pushed register",
      "width_bytes": 4
    },
    {
      "index": 1,
      "offset_at_entry": "[ESP + 0x8]",
      "read_at": "0x00ba61da MOV ESI,[ESP + 0xC] with ESP = entry-4",
      "use": "the out-pointer. Stored to at 0x00ba61e6 and then RELOADED from at 0x00ba61ed, 0x00ba6204 and 0x00ba620c rather than kept in a register.",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "single bare RET at 0x00ba6223"
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
      "va": "0x00ba8830"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bae6f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bae9b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb28c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb2a50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb4100"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00ba8899",
      "direction": "in",
      "other": "0x00ba8830",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00ba89b9",
      "direction": "in",
      "other": "0x00ba8830",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00ba8a5d",
      "direction": "in",
      "other": "0x00ba8830",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00ba8b0b",
      "direction": "in",
      "other": "0x00ba8830",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00ba8ba7",
      "direction": "in",
      "other": "0x00ba8830",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00bae8c3",
      "direction": "in",
      "other": "0x00bae6f0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00baea55",
      "direction": "in",
      "other": "0x00bae9b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00baeb21",
      "direction": "
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
      "No original-process trace exists. A differential run must confirm the allocation size 0x1B0, the type name and the three header writes in the shipping build.",
      "The 0x5220CB8 constant can only be attributed by observing what reads +0x0C on a constructed record at runtime.",
      "The concrete callee behind vtable slot +0x00 can only be fixed by dumping the vtable pointer of a constructed record.",
      "The crash-on-allocation-failure path can only be confirmed as intentional or as a latent defect by forcing an allocation failure in a controlled run."
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
      "va": "0x00ba8830"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bae6f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bae9b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb28c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb2a50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb4100"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00ba8899",
      "direction": "in",
      "other": "0x00ba8830",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00ba89b9",
      "direction": "in",
      "other": "0x00ba8830",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00ba8a5d",
      "direction": "in",
      "other": "0x00ba8830",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00ba8b0b",
      "direction": "in",
      "other": "0x00ba8830",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00ba8ba7",
      "direction": "in",
      "other": "0x00ba8830",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00bae8c3",
      "direction": "in",
      "other": "0x00bae6f0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00baea55",
      "direction": "in",
      "other": "0x00bae9b0",
      "reference_t
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
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 2,
    "symbol": "FUN_00b3d400",
    "va": "0x00b3d400"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 2,
    "symbol": "Simulator_cSpaceTrading_Get",
    "va": "0x00b3d4d0"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/wave13-w1-core-b08/b8dad0_spice_gen_key_ptr.cpp",
    "reconstruction/staging/wave13-w1-core-b08/ba61b0_make_planet_record.cpp",
    "reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08.hpp",
    "reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_model_test.cpp",
    "reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_reconstructed.hpp",
    "reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_test_stubs.cpp",
    "reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_test_stubs.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-core-b08/00ba61b0.json"
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
    "No original-process trace exists. A differential run must confirm the allocation size 0x1B0, the type name and the three header writes in the shipping build.",
    "The 0x5220CB8 constant can only be attributed by observing what reads +0x0C on a constructed record at runtime.",
    "The concrete callee behind vtable slot +0x00 can only be fixed by dumping the vtable pointer of a constructed record.",
    "The crash-on-allocation-failure path can only be confirmed as intentional or as a latent defect by forcing an allocation failure in a controlled run.",
    "What do 0x006AC040(record, 1) and 0x006AD010(record) do? Both are engine-boundary calls, 82 and 28 instructions, neither characterised.",
    "What does the 459-byte constructor 0x00B8E180 initialise? It was located and its ret form read, but its body was not reconstructed, so no field claim is made beyond the first dword being the vtable pointer.",
    "What is 0x01465EF0? It is the type descriptor passed to the allocator. The decompiler renders the allocator's second argument as the literal \"Simulator/cPlanetRecord\" and the corresponding bytes are present in .rdata, but this worker did not follow the pointer 0x01465EF0 to its target, so the association is strong rather than byte-traced end to end.",
    "What is 0x5220CB8? It is read as an immediate at 0x00ba61f4 and stored at +0x0C. No name, type, key or hash is claimed for it.",
    "What is at +0x10, set to 1? A count, a flag, a reference count and a version are all consistent with the single observed write."
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-w1-core-b08/00ba61b0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b08/b8dad0_spice_gen_key_ptr.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b08/ba61b0_make_planet_record.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_reconstructed.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_test_stubs.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_test_stubs.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave13-w1-core-b08/00ba61b0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b08/b8dad0_spice_gen_key_ptr.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b08/ba61b0_make_planet_record.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruct
[TRUNCATED]
```
