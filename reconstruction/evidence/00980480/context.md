# Reconstruction context 0x00980480

- Status: `complete`
- Content SHA-256: `f10f9792a4938c4f8f789c000a08f8deb53f252b61dae06c7b7db42e41a8cf09`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00980480",
  "phase": "reconstruction",
  "target": "0x00980480"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "UTFWin::PerspectiveEffect::HandleUIMessage",
  "package": null,
  "subsystem": "UTFWin",
  "va": "0x00980480"
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
  "content_sha256": "ee7894d03ba772093098709cade4c4c954cb4ec4b28a2663e3d728157cf5d52f",
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

bool UTFWin__PerspectiveEffect__HandleUIMessage
               (PerspectiveEffect *this,IWindow *pWindow,Message *message)

{
  bool bVar1;
  
  bVar1 = (bool)FUN_00980330();
  return bVar1;
}


```

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": [
    "__thiscall",
    "x86-32 thiscall with the receiver in ECX and one 4-byte stack word, popped by the tail callee"
  ],
  "hidden_this": true,
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": 1,
  "receiver_register": "ECX",
  "ret_form": "none in this body; the callee of the tail transfer ends in RET 0x4 at 0x0098034b and 0x00980350",
  "return_register": "EAX",
  "return_semantics": "delegated result in EAX, forwarded verbatim from 0x00980330",
  "return_type": "Opaque*",
  "saved_registers": [],
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "callee",
  "termination": [
    "tail transfer (JMP) to 0x00980330",
    "the body does not return; control leaves through the tail transfer at 0x00980483"
  ]
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
      "callsite": "0x00980483",
      "direction": "out",
      "other": "0x00980330",
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
  "globals": [
    "global:PASS",
    "global:PASS (expected)",
    "global:PASS / complete"
  ],
  "types": [
    "ILayoutElement__vftable*",
    "IPerspectiveEffect__vftable*",
    "Opaque*",
    "PerspectiveEffect__vftable*",
    "float",
    "int",
    "openspore::reconstruction::pkg_utfwin_perspective_wave12::MessageSlot",
    "openspore::reconstruction::pkg_utfwin_perspective_wave12::Opaque"
  ],
  "vtables": [
    "vtable:0x01443f2c"
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
      "callsite": "0x00980483",
      "direction": "out",
      "other": "0x00980330",
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
    "id": "scc-0323",
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
    "package": "pkg-utfwin-slot7-wave12",
    "score": 6,
    "symbol": "re_00fc7e10_UTFWin_ImageDrawable_GetTiling",
    "va": "0x00fc7e10"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "pkg-utfwin-settiling-wave13",
    "score": 6,
    "symbol": "set_tiling_00fd9460",
    "va": "0x00fd9460"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x01443f2c"
    ],
    "package": "PKG-UTFWIN-EFFECTS-WAVE6",
    "score": 4,
    "symbol": "utfwin_00980470",
    "va": "0x00980470"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__PerspectiveEffect__HandleUIMessage.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__PerspectiveEffect__HandleUIMessage.c",
    "reconstruction/staging/pkg-dfw-00980480/dfw_00980480.cpp",
    "reconstruction/staging/pkg-dfw-00980480/dfw_00980480_types.hpp",
    "reconstruction/staging/pkg-utfwin-perspective-wave12/utfwin_perspective_wave12.cpp",
    "reconstruction/staging/pkg-utfwin-perspective-wave12/utfwin_perspective_wave12.hpp",
    "reconstruction/staging/pkg-utfwin-perspective-wave12/utfwin_perspective_wave12_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-dfw-00980480/00980480.json",
    "reconstruction/metadata/pkg-utfwin-perspective-wave12/00980480.json"
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
    "0x00950eb0 returns receiver+0x04 for the class ids of Object and ILayoutElement but null for IWinProc, which is the primary base of PerspectiveEffect at +0x00. That ordering is unexplained by the observed instructions alone and is the strongest single reason the type-id reading above stays a hypothesis.",
    "Duplicate coverage: reconstruction/staging/pkg-utfwin-perspective-wave12/ still reconstructs this same VA and is RETAINED, deliberately. The earlier version of this question also claimed the validator 'can only see the one the index record names' and therefore could not see this package; that consequence was wrong and is withdrawn. The index record lists this package's .cpp before the wave12 one, so the validator grades this package, as the 2026-09-29 run confirms. What remains open is an integrator decision only: two staging candidates for one VA cannot both be the source of truth, and which one is promoted to src/ is not a worker's call. Neither package was modified to resolve it.",
    "The SDK and Ghidra both type this symbol as `bool HandleUIMessage(IWindow *pWindow, Message *message)`, but the tail callee pops exactly one stack word (RET 0x4 at 0x0098034b and 0x00980350) and answers with a pointer or with null rather than a normalised byte. Either the SDK signature is a documentation-only entry or the Ghidra symbol at 0x00980480 is attached to the wrong body; the machine cannot distinguish a two-word caller that also reclaims the second word from a one-word signature. The machine cannot distinguish these, so 
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /decompile_function @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__PerspectiveEffect__HandleUIMessage.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-dfw-00980480/00980480.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-utfwin-perspective-wave12/00980480.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-dfw-00980480/dfw_00980480.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-dfw-00980480/dfw_00980480_types.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-utfwin-perspective-wave12/utfwin_perspective_wave12.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-utfwin-perspective-wave12/utfwin_perspective_wave12.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-utfwin-perspective-wave12/utfwin_perspective_wave12_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__PerspectiveEffect__HandleUIMessage.c",
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
      "ref": "reconstruction/metadata/pkg-dfw-00980480/00980480.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg-utfwin-perspective-wave12/00980480.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/stagi
[TRUNCATED]
```
