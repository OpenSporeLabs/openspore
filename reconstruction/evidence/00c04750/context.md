# Reconstruction context 0x00c04750

- Status: `partial`
- Content SHA-256: `b68e9be5eaab5ebbe9cec6c2af33de619f98025f215f7e1a70639429470dae2b`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00c04750",
  "phase": "reconstruction",
  "target": "0x00c04750"
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
  "va": "0x00c04750"
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
  "content_sha256": "082f87eeaa83fa92eee8c71d27b6a4d13c2889ac48d1fe7cc1570c359566a855",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00c04750 failed: Decompilation did not complete. Reason: ",
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
  "hidden_receiver": "owner of the id at +0x1c, forwarded as ECX to 0x00b18530",
  "hidden_this_register": "ECX, saved to ESI at 0x00c04751",
  "ordinary_stack_argument_slots": 0,
  "receiver": true,
  "ret_form": "RET",
  "return_observation": "0x00c04779 IMUL EAX,EAX,0x4e0 and 0x00c0477f ADD EAX,dword ptr [ESI + 0x70] build the value; the only other exit is 0x00c04784 XOR EAX,EAX.",
  "return_register": "EAX",
  "return_semantics": "a pointer computed as index * 0x4e0 + the word at subObject + 0x70, or 0 when either guard fails",
  "return_type": "std::uint32_t",
  "return_width_bytes": 4,
  "saved_registers": [
    "ESI"
  ],
  "stack_arguments": [],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller (nothing is pushed at entry)",
  "termination": "0x00c04783 RET and 0x00c04787 RET"
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "FUN_00b5b800",
      "reconstructed": false,
      "va": "0x00b5b800"
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b682a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c04790"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c0cdb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c0e4f0"
    },
    {
      "name": "FUN_00c14750",
      "reconstructed": false,
      "va": "0x00c14750"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c20230"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d2ffd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d85c00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ec0530"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ec2a70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ec2f30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ec3880"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00f07e10"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00b68304",
      "direction": "in",
      "other": "0x00b682a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c047ac",
      "direction": "in",
      "other": "0x00c04790",
      "reference_type": "direct-call"
    },
    {
      "call
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "std::uint32_t"
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
      "No original-process trace exists for this address.",
      "The record type, the index semantics and the mode guard's intent can only be settled with a runtime trace that exercises the accessor in its live mode."
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
      "name": "FUN_00b5b800",
      "reconstructed": false,
      "va": "0x00b5b800"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b682a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c04790"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c0cdb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c0e4f0"
    },
    {
      "name": "FUN_00c14750",
      "reconstructed": false,
      "va": "0x00c14750"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c20230"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d2ffd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d85c00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ec0530"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ec2a70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ec2f30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ec3880"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00f07e10"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00b68304",
      "direction": "in",
      "other": "0x00b682a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c047ac",
      "direction": "in",
      
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
    "reconstruction/staging/wave13-w1-core-b07/00c04750_record_pointer_by_index.cpp",
    "reconstruction/staging/wave13-w1-core-b07/b07_model_test.cpp",
    "reconstruction/staging/wave13-w1-core-b07/b07_opaque_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-core-b07/00c04750.json"
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
    "Is index * 0x4e0 + base ever used as an offset rather than an address? The one inspected caller dereferences the result, which favours the address reading, but 12 callers were not inspected.",
    "No original-process trace exists for this address.",
    "The record type, the index semantics and the mode guard's intent can only be settled with a runtime trace that exercises the accessor in its live mode.",
    "What does 0x00f3c0e0 compute? Its two branches (a field of App::sScenarioMode and 0x00efc520) were not followed, so the index semantics are unknown.",
    "What does the +0xb8 flag word in the adjacent caller gate, and why does it return the constant 2 rather than a pointer?",
    "What is the 0x4e0-stride record type? Three field offsets are read by neighbouring code (0x4a8, 0x4ec, 0x504) but no declaration matches.",
    "What is the receiver class, and what is the +0x1c id?"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-w1-core-b07/00c04750.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b07/00c04750_record_pointer_by_index.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b07/b07_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b07/b07_opaque_types.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave13-w1-core-b07/00c04750.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b07/00c04750_record_pointer_by_index.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b07/b07_model_test.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b07/b07_opaque_types.hpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.json"
[TRUNCATED]
```
