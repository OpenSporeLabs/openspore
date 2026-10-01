# Reconstruction context 0x009804e0

- Status: `complete`
- Content SHA-256: `7f3cd0751654700457c217573be2e848489d7cf98cfb33bc4e675235f18cb3f3`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x009804e0",
  "phase": "reconstruction",
  "target": "0x009804e0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "UTFWin::PerspectiveEffect::func80h",
  "package": null,
  "subsystem": "UTFWin",
  "va": "0x009804e0"
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
  "content_sha256": "b5a0ae0ac2f97fdce5151fb122a17ad699263003c9349ad8bbcb81c0e20a6faf",
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
/* WARNING: Enum "ObjectTYPE": Some values do not have unique names */

void UTFWin__PerspectiveEffect__func80h(PerspectiveEffect *this,int param_2)

{
  int in_ECX;
  
  if (this != (PerspectiveEffect *)0xef2b293b) {
    FUN_00950eb0();
    return;
  }
  if (in_ECX != 0) {
    return;
  }
  return;
}


```

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "x86-32 thiscall, receiver in ECX, one 32-bit type word on the stack at [ESP+0x4]",
  "return_semantics": "EAX = sub-object pointer for the requested ObjectTYPE word, or 0",
  "return_type": "void*",
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
  "edge_rows": [
    {
      "callsite": "0x009804ef",
      "direction": "out",
      "other": "0x00950eb0",
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
    "openspore::reconstruction::pkg_utfwin_perspective_009804e0::ObjectTypeId",
    "openspore::reconstruction::pkg_utfwin_perspective_009804e0::PerspectiveEffect",
    "openspore::reconstruction::pkg_utfwin_perspective_009804e0::PerspectiveEffectVTable",
    "openspore::reconstruction::pkg_utfwin_perspective_009804e0::SubObjectVTable",
    "void*"
  ],
  "vtables": [
    "vtable:0x009806c0",
    "vtable:0x01444098",
    "vtable:0x014440b4",
    "vtable:0x014440d0"
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
      "callsite": "0x009804ef",
      "direction": "out",
      "other": "0x00950eb0",
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
    "id": "scc-0324",
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
      "shared_vtable:vtable:0x014440d0"
    ],
    "package": "pkg-dfw-00980510",
    "score": 10,
    "symbol": "dfw_get_proxy_id_00980510",
    "va": "0x00980510"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_types:void*"
    ],
    "package": "pkg-utfwin-hash-offset-009817c0",
    "score": 9,
    "symbol": "re_009817c0_UTFWin_HashOffsetResolver",
    "va": "0x009817c0"
  },
  {
    "match_basis": [
      "shared_types:void*",
      "shared_vtable:vtable:0x014440d0"
    ],
    "package": "PKG-UTFWIN-CORE-WAVE6",
    "score": 7,
    "symbol": "re_00951220",
    "va": "0x00951220"
  },
  {
    "match_basis": [
      "shared_types:void*",
      "shared_vtable:vtable:0x014440d0"
    ],
    "package": "PKG-UTFWIN-CORE-WAVE6",
    "score": 7,
    "symbol": "re_00951230",
    "va": "0x00951230"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "pkg-0095fa30-utfwin-isancestorof",
    "score": 6,
    "symbol": "is_ancestor_of_0095fa30",
    "va": "0x0095fa30"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "pkg-utfwin-func35-wave12",
    "score": 6,
    "symbol": "func35_0095fd60",
    "va": "0x0095fd60"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "pkg-dfw-0096ff70",
    "score": 6,
    "symbol": "dfw_func88h_0096ff70",
    "va": "0x0096ff70"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "pkg-dfw-00980480",
    "score": 6,
    "symbol": "handle_message_00980480",
    "va": "0x00980480"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__PerspectiveEffect__func80h.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__PerspectiveEffect__func80h.c",
    "reconstruction/staging/pkg-utfwin-perspective-009804e0/utfwin_perspective_009804e0.cpp",
    "reconstruction/staging/pkg-utfwin-perspective-009804e0/utfwin_perspective_009804e0.hpp",
    "reconstruction/staging/pkg-utfwin-perspective-009804e0/utfwin_perspective_009804e0_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-utfwin-perspective-009804e0/009804e0.json"
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
  "unresolved_questions": []
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /decompile_function @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__PerspectiveEffect__func80h.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-utfwin-perspective-009804e0/009804e0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-utfwin-perspective-009804e0/utfwin_perspective_009804e0.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-utfwin-perspective-009804e0/utfwin_perspective_009804e0.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-utfwin-perspective-009804e0/utfwin_perspective_009804e0_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__PerspectiveEffect__func80h.c",
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
      "ref": "reconstruction/metadata/pkg-utfwin-perspective-009804e0/009804e0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-utfwin-perspective-009804e0/utfwin_perspective_009804e0.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "r
[TRUNCATED]
```
