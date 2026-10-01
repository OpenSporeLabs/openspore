# Reconstruction context 0x00d1dcd0

- Status: `partial`
- Content SHA-256: `eed7229ce24f0ba0b229e3bb5ba80458dfb986980f3a23679085abe8719695fe`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00d1dcd0",
  "phase": "reconstruction",
  "target": "0x00d1dcd0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "FormatParser",
  "name": "ArgScript::FormatParser::GetCurrentScope",
  "package": "PKG-ARGSCRIPT-WAVE9",
  "subsystem": "ArgScript",
  "va": "0x00d1dcd0"
}
```

## 03_current_status

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "blocked": false,
  "reconstructed": true,
  "runtime_gated": true,
  "runtime_validated": 0,
  "status": "reconstructed"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "3f303f89f9923f4abd8f43be7a7e780fdcf61024536bd6be2df03e201a286fed",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00d1dcd0 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "__thiscall (no stack arguments, no cleanup)",
  "hidden_this_register": "ECX",
  "ordinary_stack_arguments": [],
  "ret_form": "plain RET",
  "return_register": "EAX",
  "return_type": "char *",
  "stack_cleanup_bytes": 0
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
    "FormatParser",
    "char *"
  ],
  "vtables": [
    "vtable:0x0141c930",
    "vtable:0x0141c97c",
    "vtable:0x0147a200"
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
      "An empty scope returns a null begin word rather than a sentinel string; callers' null handling is unverified.",
      "No original-process invocation or indirect-caller trace was captured.",
      "Ownership and lifetime of the returned character pointer are unresolved; no reference count is taken or released.",
      "The +0x130 string header layout (begin, end, capacity, allocator) is inferred from adjacent fields and is unverified at runtime.",
      "gate-argscript-scope-string-header-layout"
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
    "id": "scc-0496",
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
      "same_subsystem"
    ],
    "package": "pkg-argscript-createdefsafe-00841440",
    "score": 6,
    "symbol": "argscript_formatparser_create_definition_safe_00841440",
    "va": "0x00841440"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x0147a200"
    ],
    "package": "pkg-00b1e4d0-shared-default-stub",
    "score": 4,
    "symbol": "shared_default_stub_00b1e4d0",
    "va": "0x00b1e4d0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-UTFWIN-DRAWABLE-WAVE9",
    "score": 2,
    "symbol": "re_00985ce0",
    "va": "0x00985ce0"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/ArgScript__FormatParser__GetCurrentScope.c",
  "file": "src/reconstruction/pkg_argscript_wave9/argscript_get_current_scope.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/ArgScript__FormatParser__GetCurrentScope.c",
    "src/reconstruction/pkg_argscript_wave9/argscript_get_current_scope.cpp",
    "src/reconstruction/pkg_argscript_wave9/argscript_get_current_scope.hpp",
    "src/reconstruction/pkg_argscript_wave9/argscript_get_current_scope_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave9-safe-core/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-argscript-wave9/00d1dcd0.json"
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
    "An empty scope returns a null begin word rather than a sentinel string; callers' null handling is unverified.",
    "Confirmed layout of the +0x130 string header and the +0x154 secondary string",
    "No original-process invocation or indirect-caller trace was captured.",
    "Ownership and lifetime of the returned character pointer are unresolved; no reference count is taken or released.",
    "Ownership of the returned scope pointer",
    "The +0x130 string header layout (begin, end, capacity, allocator) is inferred from adjacent fields and is unverified at runtime.",
    "Whether callers treat a null scope as valid",
    "Whether the +0x164/+0x168 state words gate scope validity",
    "gate-argscript-scope-string-header-layout"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/ArgScript__FormatParser__GetCurrentScope.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave9-safe-core/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-argscript-wave9/00d1dcd0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_argscript_wave9/argscript_get_current_scope.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_argscript_wave9/argscript_get_current_scope.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_argscript_wave9/argscript_get_current_scope_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/ArgScript__FormatParser__GetCurrentScope.c",
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
      "ref": "reconstruction/integrated/batch-2026-09-25-wave9-safe-core/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg-argscript-wave9/00d1dcd0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_argscript_wave9/argscript_get_current_scope.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",

[TRUNCATED]
```
