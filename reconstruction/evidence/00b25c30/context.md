# Reconstruction context 0x00b25c30

- Status: `partial`
- Content SHA-256: `5bf3140ebb7f878e929953fefcbf779256009e5c35c8c5b1e32defb319950f23`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00b25c30",
  "phase": "reconstruction",
  "target": "0x00b25c30"
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
  "va": "0x00b25c30"
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
  "content_sha256": "ff0c271096d29e34d933615302582880f358a6937560ee799f9f70045d080790",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00b25c30 failed: Decompilation did not complete. Reason: ",
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
  "hidden_receiver": "read once, forwarded to the callee in ECX",
  "hidden_this_register": "ECX, never written by this body",
  "ordinary_stack_argument_slots": 0,
  "receiver": true,
  "ret_form": "RET",
  "return_note": "pointer to a registry element, or null",
  "return_observation": "0x00b25c86 XOR EAX,EAX is the failure return; 0x00b25c8a MOV ECX,[ESI] followed by 0x00b25c8c MOV EAX,[ECX + EBX*0x4] is the success return, re-loading elements[i]. No caller-visible transformation is applied.",
  "return_register": "EAX",
  "return_semantics": "The address of the first array element whose embedded interface at byte offset +0x120 answers true through vtable slot +0x58. If the element count is not positive, or if no element matches, the return is 0. The success path explicitly re-reads the element pointer from the array after restoring the saved registers, so the returned value is the element pointer itself and not the interface sub-object.",
  "return_width_bytes": 4,
  "saved_registers": [
    "EBX",
    "ESI",
    "EDI"
  ],
  "stack_arguments": [],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "RET"
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "pkg11_sim_core_00b21340",
      "reconstructed": true,
      "va": "0x00b21340"
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf4fc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bff2d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c36030"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cea1a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cec7a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cf1000"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cf7150"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cf8160"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cf9ba0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cfbc10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e07e70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e352c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e35370"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fdba50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ff5ee0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ff60d0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "dword",
    "pointer to a registry element, or null",
    "pointer, element array begin",
    "pointer, element array end",
    "vtable pointer of an embedded interface"
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
      "A differential fixture would need a real registry populated through the get-or-create helper, which static evidence alone cannot supply.",
      "No original-process trace exists for this address, so the runtime contents of the registry container, the runtime value of the .bss key 0x018c43e8 and the real distribution of predicate answers are all unverified.",
      "The Cell stage has never been entered in any recorded run, so nothing here is runtime observed."
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
      "name": "pkg11_sim_core_00b21340",
      "reconstructed": true,
      "va": "0x00b21340"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf4fc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bff2d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c36030"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cea1a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cec7a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cf1000"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cf7150"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cf8160"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cf9ba0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cfbc10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e07e70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e352c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e35370"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fdba50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ff5ee0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ff60d0"
    },
    {
      "name"
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
    "package": "PKG-11-SIM-CORE",
    "score": 3,
    "symbol": "pkg11_sim_core_00b21340",
    "va": "0x00b21340"
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
    "reconstruction/staging/wave13-w1-core-b09/b09_abi.hpp",
    "reconstruction/staging/wave13-w1-core-b09/b09_opaque_ports.hpp",
    "reconstruction/staging/wave13-w1-core-b09/sim_findfirst_00b25c30.cpp",
    "reconstruction/staging/wave13-w1-core-b09/sim_findfirst_00b25c30.hpp",
    "reconstruction/staging/wave13-w1-core-b09/sim_findfirst_00b25c30_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-core-b09/00b25c30.json"
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
    "A differential fixture would need a real registry populated through the get-or-create helper, which static evidence alone cannot supply.",
    "Is the container returned by the helper ever null? The body dereferences it immediately at 0x00b25c53, so a null return would fault; the reconstruction preserves that rather than adding a guard.",
    "No original-process trace exists for this address, so the runtime contents of the registry container, the runtime value of the .bss key 0x018c43e8 and the real distribution of predicate answers are all unverified.",
    "No original-process trace exists, so the runtime contents of the registry and the real distribution of predicate answers are unverified.",
    "The Cell stage has never been entered in any recorded run, so nothing here is runtime observed.",
    "What are the four unreported callsites at 0x00cee1f3, 0x00cfd794, 0x00cfd7b7 and 0x00ea72e1, which lie outside any Ghidra function body?",
    "What class owns this function? 26 live references, all UNCONDITIONAL_CALL, and no DATA reference, so it is not a vtable slot and no owner can be named.",
    "What does the get-or-create helper 0x00b21340 actually do, and what is its element type? Its map at this+0x98 and list at this+0x78 and its five callbacks are observed, but no element type was established, so it is kept as an opaque port rather than guessed.",
    "What is the concrete callee at vtable slot +0x58 of the element's +0x120 interface? No element instance and therefore no table address was ever observed statically
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-w1-core-b09/00b25c30.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b09/b09_abi.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b09/b09_opaque_ports.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b09/sim_findfirst_00b25c30.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b09/sim_findfirst_00b25c30.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b09/sim_findfirst_00b25c30_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave13-w1-core-b09/00b25c30.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b09/b09_abi.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b09/b09_opaque_ports.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b09/sim_findfirst_00b25c30.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-
[TRUNCATED]
```
