# Reconstruction context 0x00841540

- Status: `partial`
- Content SHA-256: `7b3a526abd680be9785953ce41050072483f0d1650236c3d6a2427477b89df92`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00841540",
  "phase": "reconstruction",
  "target": "0x00841540"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "ArgScript::FormatParser::SetFlag",
  "package": null,
  "subsystem": "ArgScript",
  "va": "0x00841540"
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
  "content_sha256": "be28a8aff2cf25e8584c27614b93700ea2dcef5049ea14781c2fc3d996da74bc",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00841540 failed: Decompilation did not complete. Reason: ",
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
  "convention": "__thiscall observed",
  "hidden_this_register": "ECX (ArgScript::FormatParser*)",
  "ordinary_stack_arguments": [
    {
      "index": 0,
      "note": "Two consecutive 32-bit words written at offsets +0 and +4 and returned in EAX; the caller at 0x0082fde0 reads exactly two dwords back from it.",
      "role": "out",
      "stack_offset_at_entry": "[ESP+4]",
      "type": "float *"
    },
    {
      "index": 1,
      "note": "The address of this word is taken three times and passed to both callees, which read the char pointer it holds and advance it.",
      "role": "cursor",
      "stack_offset_at_entry": "[ESP+8]",
      "type": "const char **"
    }
  ],
  "ret_form": "RET 0x8 (0x0084157c and 0x00841588)",
  "return_register": "EAX",
  "return_semantics": "EAX is loaded with the destination pointer by MOV EAX,EDI at 0x00841578 and 0x00841581, immediately before the register pops. The x87 stack is empty at both exits, so no part of the result travels in ST0. The caller confirms this by reading [EAX] and [EAX+0x4] as two MOVSS floats.",
  "return_type": "float *",
  "saved_registers": "ESI and EDI are pushed at 0x00841540..0x00841541 and popped at 0x0084157a..0x0084157b and 0x00841586..0x00841587",
  "stack_cleanup_bytes": 8,
  "stack_cleanup_owner": "callee",
  "termination": "two exits, both RET 0x8"
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
      "va": "0x0082f9a0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x0082fde0",
      "direction": "in",
      "other": "0x0082f9a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00841560",
      "direction": "out",
      "other": "0x0083d290",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0084154c",
      "direction": "out",
      "other": "0x0083e470",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00841570",
      "direction": "out",
      "other": "0x0083e470",
      "reference_type": "direct-call"
    }
  ],
  "external_callees": []
}
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "FormatParser",
    "const char **",
    "float *"
  ],
  "vtables": [
    "vtable:0x0141c97c",
    "vtable:0x0141c9d4"
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
      "No original-process invocation, no differential trace and no indirect-caller trace was captured, so runtime_validated remains 0.",
      "The exact numeric type of the destination pair is modelled as two floats on the strength of the x87 store/pop pair and of the caller packing the result as a two-element float array; the decompiler independently typed them float10.",
      "The identity, type and width of the FormatParser sub-object at this+0x4c are unresolved. Only its address is observable; the model holds a single opaque word and SetFlag never dereferences it.",
      "The x87 instruction forms are resolved and are no longer a gate: three independent decoders and a hand ModRM decode all give FSTP, FSTP, FLD. The remaining gates below are unchanged."
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
      "va": "0x0082f9a0"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x0082fde0",
      "direction": "in",
      "other": "0x0082f9a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00841560",
      "direction": "out",
      "other": "0x0083d290",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0084154c",
      "direction": "out",
      "other": "0x0083e470",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00841570",
      "direction": "out",
      "other": "0x0083e470",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 1,
  "fan_out": 0,
  "manifest_callees": [],
  "manifest_callers": [],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0263",
    "size": 1
  },
  "vtable_reference_count": 0
}
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "same_subsystem",
      "shared_types:FormatParser",
      "shared_vtable:vtable:0x0141c97c"
    ],
    "package": "PKG-ARGSCRIPT-WAVE9",
    "score": 13,
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
    "s
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/ArgScript__FormatParser__SetFlag.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/ArgScript__FormatParser__SetFlag.c",
    "reconstruction/staging/pkg-argscript-formatparser-setflag/argscript_formatparser_setflag.cpp",
    "reconstruction/staging/pkg-argscript-formatparser-setflag/argscript_formatparser_setflag.hpp",
    "reconstruction/staging/pkg-argscript-formatparser-setflag/argscript_formatparser_setflag_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-argscript-formatparser-setflag/00841540.json"
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
    "ABI CHECK STILL WARNS, AND THIS PACKAGE CANNOT CLEAR IT. The callsite_contract section now proves __thiscall from the call edge, but the machine ABI record still reads conventions.confidence = UNKNOWN with candidate_conventions [__stdcall, __thiscall], because the tooling deriver judges the target's own listing alone and its LEA ESI,[ECX+0x4c] performs no memory access through the receiver. The confidence field is produced by tools/reconstruction_tooling and mirrored into reconstruction/knowledge/index.json (where records[\"0x00841540\"][\"abi\"] is {}), neither of which this package may edit. The observation is recorded and the convention is stated as __thiscall, but the record is not relabelled to a confidence this package has not earned at the machine layer.",
    "Both vtables the briefing associates with this VA, 0x0141c97c and 0x0141c9d4, were not shown to contain 0x00841540. Reading the 88 bytes at 0x0141c97c yields 0x00841290, 0x00841300, 0x00841370, 0x008414c0, 0x008414d0, 0x00843240, 0x00843280, 0x008432d0, 0x00846b00, 0x00843320, 0x00846280, 0x00841500, 0x00845260, 0x00841c90, 0x00846420, 0x00d1dcd0, 0x008452e0 and 0x00835320 - 0x00841540 is absent. Whether SetFlag is virtual at all is unconfirmed, though it takes an ECX receiver like a virtual thunk would.",
    "EVIDENCE COVERAGE remains WARN and is not improvable from this package: static categories are unavailable because this function has no globals, no external callees, no recorded contradictions, no semantic hypotheses, and no original-process trace exi
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/ArgScript__FormatParser__SetFlag.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-argscript-formatparser-setflag/00841540.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-argscript-formatparser-setflag/argscript_formatparser_setflag.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-argscript-formatparser-setflag/argscript_formatparser_setflag.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-argscript-formatparser-setflag/argscript_formatparser_setflag_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/ArgScript__FormatParser__SetFlag.c",
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
      "ref": "reconstruction/metadata/pkg-argscript-formatparser-setflag/00841540.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-argscript-formatparser-setflag/argscript_formatparser_setflag.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-argscript-formatparser-setflag/argscript_formatparser_setflag.hpp",
      "source_class": "committed_
[TRUNCATED]
```
