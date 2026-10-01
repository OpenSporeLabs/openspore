# Reconstruction context 0x008414c0

- Status: `complete`
- Content SHA-256: `6ef0b8e4fb7d33ce23005f507ec5fd53dcb182b0ac45ceb764b2c2c21fc47e97`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x008414c0",
  "phase": "reconstruction",
  "target": "0x008414c0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_008414c0",
  "package": null,
  "subsystem": "ArgScript",
  "va": "0x008414c0"
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
  "status": "queued"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "d561bb827865d438869ce11774e07bcca4f11cc6cf3e1e707fd7d282931f2fff",
  "live_attempts": [],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `present`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json

/* WARNING: Unknown calling convention */

float ArgScript__FormatParser__ParseFloat(FormatParser *this,char *pString)

{
  float10 in_ST0;
  
  return (float)in_ST0;
}


```

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_this": true,
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": 0,
  "ordinary_stack_arguments": [],
  "receiver": true,
  "receiver_register": "ECX",
  "ret_form": "RET",
  "return_note": "(an opaque 32-bit word)",
  "return_register": [
    "EAX",
    "AL"
  ],
  "return_semantics": "EAX receives the 32-bit little-endian word at receiver+0x154 bit-for-bit. It is the only register the body writes.",
  "return_type": "uint32_t",
  "return_width_bytes": 4,
  "saved_registers": "none; the body touches only EAX and reads ECX",
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "RET at 0x008414c6, the bare single byte 0xC3 with no imm16 operand"
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
      "va": "0x00acf4c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b2a110"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b2bbe0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bbc340"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bbc3c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bbc540"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bbcb10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bbdbf0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bbdff0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bc1b10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4ccd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c53bc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c5b550"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cdd500"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ee95a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ee9690"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00acf7c3",
      "direction": "in",
      "other": "0x00acf4c0",
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
    "std::uint32_t",
    "uint32_t (an opaque 32-bit word)"
  ],
  "vtables": [
    "vtable:0x0141c930",
    "vtable:0x0141c97c"
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
      "Runtime validation against the original process is an open capability gate: nothing was attempted and nothing failed.",
      "The function is also reachable as a direct call from 34 sites across 30 caller functions, so a differential run can exercise it either through the vtable slot at 0x0141c97c slot 3 or through any of those direct callers."
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
      "va": "0x00acf4c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b2a110"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b2bbe0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bbc340"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bbc3c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bbc540"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bbcb10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bbdbf0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bbdff0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bc1b10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4ccd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c53bc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c5b550"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cdd500"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ee95a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ee9690"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ee9840"
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
      "same_subsystem",
      "shared_vtable:vtable:0x0141c930,vtable:0x0141c97c"
    ],
    "package": "PKG-ARGSCRIPT-WAVE9",
    "score": 10,
    "symbol": "pkg_argscript_get_current_scope_00d1dcd0",
    "va": "0x00d1dcd0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "pkg-argscript-createdefsafe-00841440",
    "score": 6,
    "symbol": "argscript_formatparser_create_definition_safe_00841440",
    "va": "0x00841440"
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
    "sy
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/ArgScript__FormatParser__ParseFloat.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/ArgScript__FormatParser__ParseFloat.c",
    "reconstruction/staging/pkg-argscript-parsefloat-008414c0/parsefloat_008414c0.cpp",
    "reconstruction/staging/pkg-argscript-parsefloat-008414c0/parsefloat_008414c0.hpp",
    "reconstruction/staging/pkg-argscript-parsefloat-008414c0/parsefloat_008414c0_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-argscript-parsefloat-008414c0/008414c0.json"
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
    "Are the two tables 0x0141c930 and 0x0141c97c one vftable seen at two scan offsets, or two related tables? The scan that found them reports 40 and 33 slots respectively; the 18-slot bound claimed here is the thunk argument and the two numbers are not reconciled.",
    "Does any of the 34 direct call sites pass a receiver of a different concrete type, and are all 30 caller functions reaching it through the same vtable as the slot at 0x0141c97c?",
    "Runtime validation against the original process is an open capability gate: nothing was attempted and nothing failed.",
    "The function is also reachable as a direct call from 34 sites across 30 caller functions, so a differential run can exercise it either through the vtable slot at 0x0141c97c slot 3 or through any of those direct callers.",
    "What class owns this slot? SporeApp.exe has no MSVC RTTI, the table's other slots carry FUN_ placeholders and four SDK-imported labels, and the exported decompilation is an artefact, so no owner is named here.",
    "What is the 32-bit word at receiver+0x154 semantically? The body fixes its offset, width and read-only access and nothing else; 851 other [reg+0x154] sites exist in the binary, so the displacement alone identifies no member.",
    "Why do four of the five inspected call sites consume the returned word as an address (move to ECX and call, or null-test then dereference at [EAX+0x1fd4] at 0x00bbc34d)? That is suggestive of a pointer, but no caller and no native rebuild fixes it here and no type is claimed."
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /decompile_function @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/ArgScript__FormatParser__ParseFloat.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-argscript-parsefloat-008414c0/008414c0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-argscript-parsefloat-008414c0/parsefloat_008414c0.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-argscript-parsefloat-008414c0/parsefloat_008414c0.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-argscript-parsefloat-008414c0/parsefloat_008414c0_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "GhidraMCP REST /decompile_function @ http://127.0.0.1:8089",
      "source_class": "ghidra"
    },
    {
      "mode": "live",
      "ref": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
      "source_class": "ghidra"
    },
    {
      "mode": "persisted",
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/ArgScript__FormatParser__ParseFloat.c",
      "source_class": "committed_artifact"
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
      "ref": "reconstruction/metadata/pkg-argscript-parsefloat-008414c0/008414c0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-argscript-parsefloat-008414c0/parsefloat_008414c0.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref"
[TRUNCATED]
```
