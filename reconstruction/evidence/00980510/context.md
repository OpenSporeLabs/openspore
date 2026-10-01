# Reconstruction context 0x00980510

- Status: `partial`
- Content SHA-256: `42fb355686169dc18e92f2d118fcb5041c6873734d348930cbc5ad030d85ca97`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00980510",
  "phase": "reconstruction",
  "target": "0x00980510"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "UTFWin::PerspectiveEffect::GetProxyID",
  "package": "pkg-dfw-00980510",
  "subsystem": "UTFWin",
  "va": "0x00980510"
}
```

## 03_current_status

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "blocked": false,
  "reconstructed": true,
  "runtime_gated": false,
  "runtime_validated": 0,
  "status": "reconstructed"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "379f2db0db0f8490ce1f95188058cc30574cc7a11d7cbaaedeb77f51bae73a5a",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00980510 failed: Decompilation did not complete. Reason: ",
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
  "hidden_this": true,
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": 0,
  "ordinary_stack_arguments": [],
  "receiver_register": "ECX",
  "ret_form": "RET (bare, no immediate)",
  "return_register": "EAX",
  "return_semantics": "integral_in_EAX",
  "return_type": "std::uint32_t",
  "saved_registers": [],
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
  "globals": [
    "global:PASS",
    "global:none. The listing names no data-segment address, and the body reaches memory nowhere."
  ],
  "types": [
    "std::uint32_t"
  ],
  "vtables": [
    "vtable:0x014440cc",
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
  "edges": [],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 0,
  "fan_out": 0,
  "manifest_callees": [],
  "manifest_callers": [],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0325",
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
      "same_calling_convention"
    ],
    "package": "pkg-utfwin-slot7-wave12",
    "score": 8,
    "symbol": "re_00fc7e10_UTFWin_ImageDrawable_GetTiling",
    "va": "0x00fc7e10"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "pkg-utfwin-settiling-wave13",
    "score": 8,
    "symbol": "set_tiling_00fd9460",
    "va": "0x00fd9460"
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
    "package": "pkg-dfw-00980c50",
    "score": 6,
    "symbol": "dfw_00980c50_func88h",
    "va": "0x00980c50"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x014440d0"
    ],
    "package": "PKG-UTFWIN-CORE-WAVE6",
    "score": 4,
    "symbol": "re_00951220",
    "va": "0x00951220"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x014440d0"
    ],
    "package": "PKG-UTFWIN-CORE-WAVE6",
    "score": 4,
    "symbol": "re_00951230",
    "va": "0x00951230"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__PerspectiveEffect__GetProxyID.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__PerspectiveEffect__GetProxyID.c",
    "reconstruction/staging/pkg-dfw-00980510/dfw_00980510.cpp",
    "reconstruction/staging/pkg-dfw-00980510/dfw_00980510_model_test.cpp",
    "reconstruction/staging/pkg-dfw-00980510/dfw_00980510_types.hpp",
    "reconstruction/staging/pkg-utfwin-perspective-proxyid-00980510/get_proxy_id_00980510.cpp",
    "reconstruction/staging/pkg-utfwin-perspective-proxyid-00980510/get_proxy_id_00980510.hpp",
    "reconstruction/staging/pkg-utfwin-perspective-proxyid-00980510/get_proxy_id_00980510_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-dfw-00980510/00980510.json",
    "reconstruction/metadata/pkg-utfwin-perspective-proxyid-00980510/00980510.json"
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
    "Slot +0x18 (0x00980520) has no function record in Ghidra, so the slot immediately after GetProxyID is uncharacterised. It is the most likely place a related per-class override would sit, which makes it the obvious next target for this class.",
    "Slot +0x18 (0x00980520) has no function record in Ghidra, so the slot immediately after this one is uncharacterised. It is the most likely place a related per-class override would sit.",
    "The decompiler's `ILayoutElement *` parameter type is not independently confirmed. The binary carries no MSVC RTTI (per the project evidence note), so the base type comes from the imported Spore-ModAPI symbols. This record keeps the receiver opaque (struct PerspectiveEffect) rather than adopting the decompiler's base-class spelling, and flags the disagreement rather than resolving it.",
    "The exact vtable extent. Slots +0x00..+0x5c are recorded and mutually consistent, but no null terminator appears in that window, and words observed at +0x60..+0x7c (0x010829f0, 0x00951230, 0x006f2f20) may belong to this image or to the next one. Nothing in this target's body depends on the answer.",
    "The extent of the dispatch-table image. Only the eight words actually read are recorded. Whether the image continues past +0x1c, and where it ends, is unresolved; nothing in this body depends on the answer.",
    "The receiver convention is inferred, not observed. See observed_original_abi.convention_basis. Nothing in the body can corroborate it, which is why the derived ABI record abstained (verdict 
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__PerspectiveEffect__GetProxyID.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-dfw-00980510/00980510.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-utfwin-perspective-proxyid-00980510/00980510.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-dfw-00980510/dfw_00980510.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-dfw-00980510/dfw_00980510_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-dfw-00980510/dfw_00980510_types.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-utfwin-perspective-proxyid-00980510/get_proxy_id_00980510.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-utfwin-perspective-proxyid-00980510/get_proxy_id_00980510.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-utfwin-perspective-proxyid-00980510/get_proxy_id_00980510_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__PerspectiveEffect__GetProxyID.c",
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
      "ref": "reconstruction/metadata/pkg-dfw-00980510/00980510.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg-utfwin-perspective-proxyid-00980510/00980510.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-dfw-00980510/dfw_00980510.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "
[TRUNCATED]
```
