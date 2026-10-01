# Reconstruction context 0x009672d0

- Status: `complete`
- Content SHA-256: `dda463509c5a6833e355314e8a6c7b0f9d9e4ec646ade968070612af14fdf40c`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x009672d0",
  "phase": "reconstruction",
  "target": "0x009672d0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "UTFWin::CascadeEffect::HandleUIMessage",
  "package": null,
  "subsystem": "UTFWin",
  "va": "0x009672d0"
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
  "content_sha256": "a06e481ced06d5275afb85bfe7087ad7d90dba33b2cd4383567d72d6c2d3dda3",
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

bool UTFWin__CascadeEffect__HandleUIMessage(CascadeEffect *this,IWindow *pWindow,Message *message)

{
  undefined1 uVar1;
  int in_ECX;
  
  if (this != (CascadeEffect *)0x6f90a535) {
    uVar1 = FUN_00950eb0();
    return (bool)uVar1;
  }
  if (in_ECX != 0) {
    return (bool)((char)in_ECX + '\f');
  }
  return false;
}


```

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "x86-32 thiscall with the receiver in ECX and one 4-byte type word on the stack",
  "ordinary_stack_argument_slots": 1,
  "return_register": "EAX",
  "return_type": "Opaque*",
  "return_width_bytes": 4,
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "caller"
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
      "callsite": "0x009672df",
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
    "Opaque*",
    "openspore::reconstruction::pkg_utfwin_cascade_009672d0::CascadeEffectReceiver",
    "openspore::reconstruction::pkg_utfwin_cascade_009672d0::Opaque"
  ],
  "vtables": [
    "vtable:0x014414b8"
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
      "callsite": "0x009672df",
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
    "id": "scc-0306",
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
      "shared_types:Opaque*"
    ],
    "package": "pkg-dfw-00980480",
    "score": 9,
    "symbol": "handle_message_00980480",
    "va": "0x00980480"
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
    "package": "pkg-dfw-00980510",
    "score": 6,
    "symbol": "dfw_get_proxy_id_00980510",
    "va": "0x00980510"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "pkg-dfw-00980c50",
    "score": 6,
    "symbol": "dfw_00980c50_func88h",
    "va": "0x00980c50"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "pkg-utfwin-hash-offset-009817c0",
    "score": 6,
    "symbol": "re_009817c0_UTFWin_HashOffsetResolver",
    "va": "0x009817c0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "pkg-utfwin-slot7-wave12",
    "score": 6,
    "symbol": "re_00fc7e10_UTFWin_ImageDrawable_GetTiling",
    "va": "0x00fc7e10"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__CascadeEffect__HandleUIMessage.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__CascadeEffect__HandleUIMessage.c",
    "reconstruction/staging/pkg-utfwin-cascade-009672d0/utfwin_cascade_009672d0.cpp",
    "reconstruction/staging/pkg-utfwin-cascade-009672d0/utfwin_cascade_009672d0.hpp",
    "reconstruction/staging/pkg-utfwin-cascade-009672d0/utfwin_cascade_009672d0_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-utfwin-cascade-009672d0/009672d0.json"
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
    "Is 0x009672d0 a whole function or the tail of one whose head was folded into 0x00950eb0? The body is complete and self-consistent, but nothing in the listing proves no earlier block jumps into 0x009672d0.",
    "The SDK labels the slot HandleUIMessage with a bool return and two pointer parameters, but the body consumes one 4-byte stack word and returns a biased receiver word. Which of the two readings is the real source signature - an EA cross-cast helper that the SDK symbol table mislabels, or a HandleUIMessage whose message argument happens to hold an ObjectTYPE word?",
    "What produces the 0x6f90a535 word at the call site, given the slot has no direct caller and the only observable producer of these words elsewhere in the binary is a PUSH of 0xee3f516e at 0x00c149c0?"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /decompile_function @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__CascadeEffect__HandleUIMessage.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-utfwin-cascade-009672d0/009672d0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-utfwin-cascade-009672d0/utfwin_cascade_009672d0.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-utfwin-cascade-009672d0/utfwin_cascade_009672d0.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-utfwin-cascade-009672d0/utfwin_cascade_009672d0_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__CascadeEffect__HandleUIMessage.c",
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
      "ref": "reconstruction/metadata/pkg-utfwin-cascade-009672d0/009672d0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-utfwin-cascade-009672d0/utfwin_cascade_009672d0.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "re
[TRUNCATED]
```
