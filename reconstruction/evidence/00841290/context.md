# Reconstruction context 0x00841290

- Status: `partial`
- Content SHA-256: `ee1dde21ff4651364e1daa3c03c3cbae10eab7f665bcd70776d52b01a83b0543`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00841290",
  "phase": "reconstruction",
  "target": "0x00841290"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "ArgScript::FormatParser::Release",
  "package": null,
  "subsystem": "ArgScript",
  "va": "0x00841290"
}
```

## 03_current_status

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "blocked": false,
  "reconstructed": false,
  "runtime_gated": false,
  "runtime_validated": 0,
  "status": "queued"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "f303c15630ec295d75d1d414c35d3a074df4c5ec143e4e0986d353ae9188d9a9",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00841290 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "x86-32 thiscall with the receiver in ECX and one caller-pushed four-byte stack word",
  "hidden_this_register": "ECX",
  "hidden_this_type": "FormatParser * (SporeApp.exe has no MSVC RTTI; the receiver type is an opaque vtable-owning object)",
  "ordinary_stack_argument_slots": 1,
  "ordinary_stack_arguments": [
    {
      "entry_offset": "EBP+0x08",
      "load_instruction": "0x008412ab: MOV EDX,dword ptr [EBP + 0x8]",
      "name": "argument_08",
      "semantic_type": "unresolved; passed straight through to the +0x3c slot as a raw 32-bit word",
      "type": "uint32_t",
      "width_bytes": 4
    }
  ],
  "ret_form": "RET 0x4",
  "return_note": "(modeled)",
  "return_register": "EAX",
  "return_type": "bool",
  "saved_registers": "EBX, ESI and EDI are pushed and popped unmodified; the fourth push (ECX at 0x008412a8) is dropped by MOV ESP,EBP",
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "callee"
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [],
  "callers": [],
  "edge_rows": [],
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
    "FormatParser * (SporeApp.exe has no MSVC RTTI; the receiver type is an opaque vtable-owning object)",
    "bool (modeled)",
    "openspore::reconstruction::pkg_orchestrate_dogfood_00841290::FormatParserReleaseSlot3c",
    "openspore::reconstruction::pkg_orchestrate_dogfood_00841290::OpaqueFormatParser",
    "openspore::reconstruction::pkg_orchestrate_dogfood_00841290::OpaqueFormatParserVtable",
    "openspore::reconstruction::pkg_orchestrate_dogfood_00841290::OpaqueReleasePorts",
    "uint32_t"
  ],
  "vtables": [
    "vtable:0x0141c930",
    "vtable:0x0141c97c"
  ]
}
```

## 09_state_event_relationships

- State: `missing`
- Provenance: `knowledgegraph/research/semantic-decomp.json, reconstruction/knowledge/index.json`

```json
{
  "runtime": {
    "blocking_reason": null,
    "gates": [],
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
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 0,
  "fan_out": 0,
  "manifest_callees": [],
  "manifest_callers": [],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0259",
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
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/ArgScript__FormatParser__Release.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/ArgScript__FormatParser__Release.c",
    "reconstruction/staging/pkg-orchestrate-dogfood-00841290/dogfood_00841290.cpp",
    "reconstruction/staging/pkg-orchestrate-dogfood-00841290/dogfood_00841290.hpp",
    "reconstruction/staging/pkg-orchestrate-dogfood-00841290/dogfood_00841290_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-orchestrate-dogfood-00841290/00841290.json"
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
    "Is the native return type bool or int, given that only AL is written?",
    "The briefing carried no ABI projection (evidence.missing_sections: ABI); the whole observed_original_abi block above was derived by hand from the disassembly and must be reviewed against a native build.",
    "What does the funclet at 0x01217640 do if the +0x3c callee raises an exception, and is the state word at [EBP-4] ever set by a path not present in this body?",
    "What is the full extent of the vtable beginning at 0x0141c930, and which slots below index 15 belong to base classes?",
    "What is the single stack argument at [EBP+0x8] (type, producer, and meaning)?",
    "Which concrete callee does vtable index 15 resolve to for a live FormatParser receiver, and does the base class at 0x0141c930 or the secondary vtable at 0x0141c97c own that slot?"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/ArgScript__FormatParser__Release.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-orchestrate-dogfood-00841290/00841290.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-orchestrate-dogfood-00841290/dogfood_00841290.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-orchestrate-dogfood-00841290/dogfood_00841290.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-orchestrate-dogfood-00841290/dogfood_00841290_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/ArgScript__FormatParser__Release.c",
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
      "ref": "reconstruction/metadata/pkg-orchestrate-dogfood-00841290/00841290.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-orchestrate-dogfood-00841290/dogfood_00841290.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-orchestrate-dogfood-00841290/dogfood_00841290.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode
[TRUNCATED]
```
