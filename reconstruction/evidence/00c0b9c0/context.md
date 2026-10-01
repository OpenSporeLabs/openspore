# Reconstruction context 0x00c0b9c0

- Status: `partial`
- Content SHA-256: `192792ea581d7df912b844e0ea53ed24d4359074fb2502bbaa7b50d8d037af50`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00c0b9c0",
  "phase": "reconstruction",
  "target": "0x00c0b9c0"
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
  "va": "0x00c0b9c0"
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
  "content_sha256": "6234ccc80da3b8832a1bcb26d1264ce1e7b9f20d9ed061b9297864f4a5391738",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00c0b9c0 failed: Decompilation did not complete. Reason: ",
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
  "hidden_receiver": "read",
  "hidden_this_register": "ECX, read once and never modified",
  "ordinary_stack_argument_slots": 0,
  "receiver": true,
  "ret_form": "RET",
  "return_observation": "0x00c0b9c0 FLD float ptr [ECX + 0xbbc] pushes the value; 0x00c0b9c6 RET returns with it still on the x87 stack because no FSTP exists in the body. Callers confirm the convention: 0x00c02dfe is followed by FLD float ptr [0x01687a10] and FCOMIP ST0,ST1, 0x00c22b76 by FSUBR float ptr [0x01687a00], and the parallel shape in 0x00b3e3e0 FSTPs into a stack local.",
  "return_register": "ST(0) (x87)",
  "return_semantics": "The 32-bit IEEE-754 single at receiver+0xbbc, bit-for-bit unmodified, delivered on the x87 stack in ST(0). The body performs no arithmetic at all: it is a single 32-bit memory load.",
  "return_type": "float",
  "return_width_bytes": 4,
  "saved_registers": [],
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
  "callees": [],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c02df0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c08350"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c09fa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c22ae0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ccc640"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d2dd20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d35190"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d41a70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d71060"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d74060"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d85ad0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d85c00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00da9800"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00dabdf0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00daf820"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00dbc7a0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00c02dfe",
      "direction": "in",
      "other": "0x00c02df0",
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
    "float"
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
      "A differential fixture is cheap for this target - it is one load - but it still requires a constructed receiver to be meaningful.",
      "No original-process trace exists for this address, so the runtime value of +0xbbc and the real contents of the tuning globals are unverified.",
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
  "callees": [],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c02df0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c08350"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c09fa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c22ae0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ccc640"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d2dd20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d35190"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d41a70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d71060"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d74060"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d85ad0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d85c00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00da9800"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00dabdf0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00daf820"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00dbc7a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e07e70"
    }
  ],
  "callers_truncated": false,
  "dat
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
    "reconstruction/staging/wave13-w1-core-b09/b09_abi.hpp",
    "reconstruction/staging/wave13-w1-core-b09/sim_threshold_00c0b9c0.cpp",
    "reconstruction/staging/wave13-w1-core-b09/sim_threshold_00c0b9c0.hpp",
    "reconstruction/staging/wave13-w1-core-b09/sim_threshold_00c0b9c0_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-core-b09/00c0b9c0.json"
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
    "A differential fixture is cheap for this target - it is one load - but it still requires a constructed receiver to be meaningful.",
    "Is 0x00c0b9c0 ever reached through a vtable at runtime even though no static DATA reference exists? A runtime patch or a dynamically built table would not show up statically and cannot be excluded.",
    "No original-process trace exists for this address, so the runtime value of +0xbbc and the real contents of the tuning globals are unverified.",
    "The Cell stage has never been entered in any recorded run, so nothing here is runtime observed.",
    "What are the four tuning globals 0x01687a00, 0x01687a0c, 0x01687a10 and 0x01687a14 that the callers compare against? They were never read by a tool in this batch, so no value is claimed for any of them.",
    "What are the four unreported callsites at 0x00d760e7, 0x00d768eb, 0x00d77160 and 0x00d77234, which lie outside any Ghidra function body? Their surrounding code was not inspected.",
    "What class owns this function? 31 live references, all UNCONDITIONAL_CALL, and no DATA reference, so it is not a vtable slot and no owner can be named.",
    "What does the float at +0xbbc mean? The callers prove it is used as a threshold and as a bounded term in a weighted sum, but no SDK field, no global name and no string ties it to a game concept.",
    "What does the sibling accessor 0x00c0b8e0 read? It is called on the same receiver at 0x00ba27be and compared against 0x0156c198 and 0x0156c194, so it is a second parameter of the same kind, but i
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-w1-core-b09/00c0b9c0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b09/b09_abi.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b09/sim_threshold_00c0b9c0.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b09/sim_threshold_00c0b9c0.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b09/sim_threshold_00c0b9c0_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave13-w1-core-b09/00c0b9c0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b09/b09_abi.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b09/sim_threshold_00c0b9c0.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b09/sim_threshold_00c0b9c0.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave
[TRUNCATED]
```
