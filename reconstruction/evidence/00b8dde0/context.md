# Reconstruction context 0x00b8dde0

- Status: `partial`
- Content SHA-256: `94d9792cc80edf31ca58e7606803750b003e7c8731bb02c496e224b44487bc6d`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00b8dde0",
  "phase": "reconstruction",
  "target": "0x00b8dde0"
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
  "va": "0x00b8dde0"
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
  "content_sha256": "d7b2856e1c4e6ce1adf1185e9f13212579647aa1ab3cde22341e3cde189a0355",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00b8dde0 failed: Decompilation did not complete. Reason: ",
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
  "hidden_receiver": "read; the receiver's +0x1A4, +0x1A8 and +0x1AC fields are the comparison targets and the write destinations",
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": 1,
  "receiver": true,
  "ret_form": "RET 0x8",
  "return_observation": "0x00b8dde1e is a bare RET 0x8 with no value in EAX that any caller reads; the twelve inspected callsites all discard EAX or reload it immediately.",
  "return_register": "none - EAX is used as a scratch load at 0x00b8dde3 and 0x00b8dde15 and its exit value is never consumed",
  "return_semantics": "none; the function's only effect is the conditional write of three dwords into the receiver",
  "return_type": "void",
  "return_width_bytes": 0,
  "saved_registers": [],
  "stack_arguments": [
    {
      "instruction": "0x00b8dde0: MOV EAX,dword ptr [ESP + 0x4]",
      "offset": "ESP+0x4",
      "role": "pointer to a 12-byte ResourceKey {instanceID, typeID, groupID}",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 8,
  "stack_cleanup_owner": "callee",
  "termination": "single exit at 0x00b8dde1e"
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
      "va": "0x00ba5fd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba6120"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba6310"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba64a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba7c20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba8830"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb2a50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bbaa80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bbac80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c713c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00de6f20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00f37690"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00ba6073",
      "direction": "in",
      "other": "0x00ba5fd0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00ba6169",
      "direction": "in",
      "other": "0x00ba6120",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00ba6355",
      "direction": "in",
      "other": "0x00ba6310",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00ba6550",
      "direction": "in",
      "other": 
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
      "No original-process trace has ever been captured for this function; the original Cell stage has never been entered in any recorded run. Every claim here is static.",
      "No runtime evidence can distinguish 'write the same value' from 'skip the write' by observing memory alone, so any differential fixture for this function must observe side channels, not state.",
      "The change check is only observable through a watcher. A differential test must instrument the field or the paired getter to confirm that a redundant write really is suppressed, and to establish why the compiler emitted the check.",
      "The consume-once behaviour of the paired getter 0x00b8dd60 is a runtime claim about the materialisation service obtained from 0x00f48a80; a write watchpoint on record+0x1A4 across a full planet load is required to confirm it."
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
      "va": "0x00ba5fd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba6120"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba6310"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba64a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba7c20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba8830"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb2a50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bbaa80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bbac80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c713c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00de6f20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00f37690"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00ba6073",
      "direction": "in",
      "other": "0x00ba5fd0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00ba6169",
      "direction": "in",
      "other": "0x00ba6120",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00ba6355",
      "direction": "in",
      "other": "0x00ba6310",
      "reference_type": "direct-call"

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
    "reconstruction/staging/wave13-w1-core-b06/b8dde0_planet_record_store_terrain_key.cpp",
    "reconstruction/staging/wave13-w1-core-b06/sim_core_b06_model_test.cpp",
    "reconstruction/staging/wave13-w1-core-b06/sim_core_b06_opaque.hpp",
    "reconstruction/staging/wave13-w1-core-b06/sim_core_b06_ports_model.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-core-b06/00b8dde0.json"
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
    "Is 0xB0 or 0xAF the correct fifth IDGenerator argument? cPlanetRecord.h:342 records 0xAF while the observed callsites push 0xB0. The property id 0x00B1B104 and the offset 0x84 match exactly, so the discrepancy is isolated to one argument of a related SDK function and does not affect any claim made here.",
    "No original-process trace has ever been captured for this function; the original Cell stage has never been entered in any recorded run. Every claim here is static.",
    "No runtime evidence can distinguish 'write the same value' from 'skip the write' by observing memory alone, so any differential fixture for this function must observe side channels, not state.",
    "The briefing's canonical ledger recorded caller_count 12; the live xref query finds 16 call sites in 13 distinct caller functions. The four additional callers (0x00bbac80, 0x00c713c0, 0x00de6f20, 0x00f37690) are not a contradiction but a more complete count; 0x00bb2a50 alone accounts for five of the sixteen sites.",
    "The change check is only observable through a watcher. A differential test must instrument the field or the paired getter to confirm that a redundant write really is suppressed, and to establish why the compiler emitted the check.",
    "The consume-once behaviour of the paired getter 0x00b8dd60 is a runtime claim about the materialisation service obtained from 0x00f48a80; a write watchpoint on record+0x1A4 across a full planet load is required to confirm it.",
    "What does the +0x13C back-pointer at 0x00c713c0 point to, and why doe
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-w1-core-b06/00b8dde0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b06/b8dde0_planet_record_store_terrain_key.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b06/sim_core_b06_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b06/sim_core_b06_opaque.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b06/sim_core_b06_ports_model.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave13-w1-core-b06/00b8dde0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b06/b8dde0_planet_record_store_terrain_key.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b06/sim_core_b06_model_test.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b06/sim_core_b06_opaque.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref":
[TRUNCATED]
```
