# Reconstruction context 0x008414d0

- Status: `partial`
- Content SHA-256: `1c8032deece0b27d04d227363000f12c5ff1a97bf037cf5426899e2e4c969ff3`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x008414d0",
  "phase": "reconstruction",
  "target": "0x008414d0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "ArgScript::FormatParser::ParseUInt",
  "package": null,
  "subsystem": "ArgScript",
  "va": "0x008414d0"
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
  "content_sha256": "2bc780fbf78f4409fe58d24fb238c807d3b66299ad4ac73932675eecbb5377be",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x008414d0 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "x86-32 thiscall with the receiver in ECX, no stack argument read by the body",
  "hidden_this_register": "ECX",
  "hidden_this_type": "FormatParser * (SporeApp.exe has no MSVC RTTI; the receiver is an opaque vtable-owning object reached only through the vtable slot)",
  "ordinary_stack_argument_slots": 0,
  "ordinary_stack_arguments": [],
  "ret_form": "plain RET",
  "return_register": "EAX",
  "return_type": "const char*",
  "saved_registers": "ESI is pushed at 0x008414d6 and popped at 0x008414f5 unmodified; no other callee-saved register is touched",
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "none for the receiver; the four words pushed for the callee are removed by ADD ESP,0x10 at 0x008414f2"
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [],
  "callers": [],
  "edge_rows": [
    {
      "callsite": "0x008414eb",
      "direction": "out",
      "other": "0x00840c20",
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
    "FormatParser * (SporeApp.exe has no MSVC RTTI; the receiver is an opaque vtable-owning object reached only through the vtable slot)",
    "const char*",
    "openspore::reconstruction::pkg_argscript_format_008414d0::CopyFormattedToString",
    "openspore::reconstruction::pkg_argscript_format_008414d0::FormatParserPorts",
    "openspore::reconstruction::pkg_argscript_format_008414d0::OpaqueFormatParser",
    "openspore::reconstruction::pkg_argscript_format_008414d0::OpaqueString"
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
  "edges": [
    {
      "callsite": "0x008414eb",
      "direction": "out",
      "other": "0x00840c20",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 0,
  "fan_out": 0,
  "manifest_callees": [],
  "manifest_callers": [],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0262",
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
  },
  {
    "match_basis": [
      "shared_types:const char*"
    ],
    "package": "PKG-APP-LIFECYCLE-WAVE7",
    "score": 3,
    "symbol": "app_capp_system_set_effect_collection_ids_007e6100",
    "va": "0x007e6100"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/ArgScript__FormatParser__ParseUInt.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/ArgScript__FormatParser__ParseUInt.c",
    "reconstruction/staging/pkg-argscript-format-008414d0/parse_uint_008414d0.cpp",
    "reconstruction/staging/pkg-argscript-format-008414d0/parse_uint_008414d0.hpp",
    "reconstruction/staging/pkg-argscript-format-008414d0/parse_uint_008414d0_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-argscript-format-008414d0/008414d0.json"
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
    "Are there writers of the words at +0xe0 and +0xf0 that would confirm their declared types (a script and a line/index respectively are guesses only)?",
    "Does any real caller push the declared pString stack argument, and if so who cleans it up given the plain RET?",
    "FIELDS/OFFSETS: is the machine-derived receiver record wrong, or is the model wrong? The record is narrower than the body: abi_derived.receiver is shape R-DIRECT with offsets [0xe0, 0xf0] and distinct_offsets 2, while the same pack's 13-instruction listing names 0xe0, 0xf0 and 0xf4 through ECX (0xf4 via LEA ESI,[ECX + 0xf4] at 0x008414d7). The record counts only direct [ECX+disp] dereferences, so a displacement carried in a LEA is invisible to it. This package holds that the record under-reports and the model is right, and did not shrink the model to fit the bounds; the disagreement is not settled because the fix belongs in the ABI inference, which is tooling-owned.",
    "GLOBALS: the body names the data address 0x0141bcb0 and nothing corroborates it -- the xref export carries no data-reference edge type and the pack's globals category is empty -- so its role as the \"%s:%d\" literal rests on the ghidra_read_memory byte read alone. That is sufficient for a format operand (the bytes are self-identifying) but it means no second machine witness confirms the address is a string and not a pointer to one.",
    "Is the native return type char* or uint32_t? Ghidra's prototype and the SDK import both say uint, yet the returned dword is the begin word of the s
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/ArgScript__FormatParser__ParseUInt.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-argscript-format-008414d0/008414d0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-argscript-format-008414d0/parse_uint_008414d0.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-argscript-format-008414d0/parse_uint_008414d0.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-argscript-format-008414d0/parse_uint_008414d0_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/ArgScript__FormatParser__ParseUInt.c",
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
      "ref": "reconstruction/metadata/pkg-argscript-format-008414d0/008414d0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-argscript-format-008414d0/parse_uint_008414d0.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-argscript-format-008414d0/parse_uint_008414d0.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode"
[TRUNCATED]
```
