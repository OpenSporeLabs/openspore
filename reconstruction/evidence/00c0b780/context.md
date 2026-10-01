# Reconstruction context 0x00c0b780

- Status: `partial`
- Content SHA-256: `c8a3266776b3f593097c5641d3f8484c4dfb22ba9f18d934ae4426c15630c3b2`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00c0b780",
  "phase": "reconstruction",
  "target": "0x00c0b780"
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
  "va": "0x00c0b780"
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
  "content_sha256": "086e9462f43e6106d0e18de842b36aa537f283dabbc722939b3682b3b2f18d58",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00c0b780 failed: Decompilation did not complete. Reason: ",
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
  "hidden_receiver": "ECX, read at 0x00c0b780",
  "hidden_this_register": "ECX is read once and then zeroed at 0x00c0b786. The zeroing is part of the idiom, not evidence that ECX is unused.",
  "ordinary_stack_argument_slots": 0,
  "receiver": true,
  "ret_form": "RET",
  "return_register": "EAX",
  "return_semantics": "A full dword 0 or 1, never a byte. XOR ECX,ECX / CMP ECX,[EAX + 0x608] sets CF iff the memory dword is unsigned-greater than zero; SBB EAX,EAX yields 0 or 0xFFFFFFFF; NEG EAX maps 0xFFFFFFFF to 1. Both EAX writes are 32-bit, so bits 8..31 of the answer are written rather than left as the caller had them. Every inspected consumer tests AL, which is consistent but does not narrow the width.",
  "return_type": "std::uint32_t",
  "return_width_bytes": 4,
  "saved_registers": [],
  "stack_arguments": [],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "single RET at 0x00c0b792"
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
      "va": "0x00ba27b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c02eb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c042e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c24f40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d2c000"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d3cdc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d581b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d5f780"
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
      "va": "0x00d8cab0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d8dcc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d8f560"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00da8a40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00dbc7a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e8bf20"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00ba27fa",
      "direction": "in",
      "other": "0x00ba27b0",
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
      "No original-process trace exists for 0x00c0b780. A differential run must confirm the answer is still 0/1 in the shipping build and that no runtime patch retargets it.",
      "The non-null invariant on receiver+0xB20 must be observed at a concrete callsite before any caller-side guard can be claimed.",
      "The value of the dword at +0x608, and of the sibling at +0x60C, at the moment 0x00ba27b0 reads them, can only be established at runtime."
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
      "va": "0x00ba27b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c02eb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c042e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c24f40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d2c000"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d3cdc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d581b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d5f780"
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
      "va": "0x00d8cab0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d8dcc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d8f560"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00da8a40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00dbc7a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e8bf20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e8cd30"
    },
    {
      "name": null,
      "reconst
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
    "reconstruction/staging/wave13-w1-core-b08/c0b780_sub_object_flag_608.cpp",
    "reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08.hpp",
    "reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_model_test.cpp",
    "reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_reconstructed.hpp",
    "reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_test_stubs.cpp",
    "reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_test_stubs.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-core-b08/00c0b780.json"
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
    "Are +0x608 and +0x60C two independent dwords, a bitfield, or two slots of a small dispatch array? Only their offsets and non-zero-ness are observed.",
    "Is the sub-object at +0xB20 ever null in the shipping build? If it can be, this body faults and the caller-side invariant is unverified without a runtime trace.",
    "No original-process trace exists for 0x00c0b780. A differential run must confirm the answer is still 0/1 in the shipping build and that no runtime patch retargets it.",
    "The non-null invariant on receiver+0xB20 must be observed at a concrete callsite before any caller-side guard can be claimed.",
    "The value of the dword at +0x608, and of the sibling at +0x60C, at the moment 0x00ba27b0 reads them, can only be established at runtime.",
    "Twelve of the eighteen recorded callsites were not individually disassembled, so their receiver setup and result use are recorded from the canonical xref list only.",
    "What do the return codes 1, 2, 3, 4 and 6 of 0x00ba27b0 mean? Code 5 is never produced by the observed body, which suggests an enumeration this worker cannot name.",
    "What is the owning type of the receiver? No vtable for it was located and this binary has no RTTI, so nothing beyond the offsets +0xB20 and +0xB88 can be claimed.",
    "What is the owning type of the sub-object at receiver+0xB20? Only the offsets 0x544, 0x608 and 0x60C inside it are observed.",
    "What predicate does the dword at +0x608 express? The body proves it is a non-zero test and nothing more.",
    "Why does 0x00c
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-w1-core-b08/00c0b780.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b08/c0b780_sub_object_flag_608.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_reconstructed.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_test_stubs.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_test_stubs.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave13-w1-core-b08/00c0b780.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b08/c0b780_sub_object_flag_608.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_model_test.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "recon
[TRUNCATED]
```
