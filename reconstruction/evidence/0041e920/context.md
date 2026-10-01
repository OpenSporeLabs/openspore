# Reconstruction context 0x0041e920

- Status: `partial`
- Content SHA-256: `d3421a2907883d223b3c1943be062f65a948d6ca790d9eca3b3be42982d0ea3a`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x0041e920",
  "phase": "reconstruction",
  "target": "0x0041e920"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaquePropertySlot",
  "name": "property_value_resolve_0041e920",
  "package": "PKG-APP-SAFE-WAVE10",
  "subsystem": "App.PropertySlot",
  "va": "0x0041e920"
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
  "content_sha256": "4bc709a7b2b31d75598af5913b6c1e2be4bef6dbb07527a2b4f5a9bb0f3c8428",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x0041e920 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "thiscall, receiver only, no stack arguments",
  "receiver_register": "ECX",
  "ret_form": "RET",
  "return_register": "EAX",
  "return_width_bytes": 4,
  "stack_arguments": [],
  "stack_cleanup_bytes": 0
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
      "va": "0x00406570"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00406ef0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00407190"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00407280"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0040aeb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0040eb70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0040f4a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004147b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004360f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004410d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0044f240"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00452080"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0046c000"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00471000"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0047d950"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004ba150"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x004068b3",
      "direction": "in",
      "other": "0x00406570",
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
    "OpaquePropertySlot",
    "const OpaquePropertySlot*",
    "const unsigned char*"
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
      "The body is a leaf, so no dependency port was introduced.",
      "The meaning of the storage mask 0x0030 and of the kind values 0x0001 and 0x0010 is inferred from the compare immediates only.",
      "The opaque +0x04..+0x0f region of the slot is never read, so no field evidence exists for it.",
      "The sentinel address 0x015d115d is a .data address returned to the caller as a marker; its runtime identity is not established.",
      "gate-property-value-resolve-runtime-kind-and-storage-semantics",
      "no vtable or callee is involved, so no dependency port was introduced",
      "runtime validation not performed; static decompilation and disassembly only",
      "the meaning of the storage mask 0x0030 and of the kind values 0x0001 and 0x0010 is inferred from the compare immediates only",
      "the opaque +0x04..+0x0f region of the slot is never read, so no field evidence exists for it",
      "the sentinel address 0x015d115d is a .data address returned to the caller as a marker; its runtime identity is not established"
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
      "va": "0x00406570"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00406ef0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00407190"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00407280"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0040aeb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0040eb70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0040f4a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004147b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004360f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004410d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0044f240"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00452080"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0046c000"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00471000"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0047d950"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004ba150"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004d2450"
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
      "same_package"
    ],
    "package": "PKG-APP-SAFE-WAVE10",
    "score": 8,
    "symbol": "vector3_add_0041dc10",
    "va": "0x0041dc10"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "PKG-APP-SAFE-WAVE10",
    "score": 8,
    "symbol": "cursor_buffer_emit_0041e8b0",
    "va": "0x0041e8b0"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-PALETTE-SAFE-WAVE11",
    "score": 3,
    "symbol": "palette_safe_wave11_load_page_state_005c85d0",
    "va": "0x005c85d0"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-DIRECT-PROPERTY-WAVE6",
    "score": 3,
    "symbol": "opaque_list_set_property_006a30c0",
    "va": "0x006a30c0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-SKINNER-SAFE-WAVE10",
    "score": 2,
    "symbol": "skin_painter_job_brush_pass_005182f0",
    "va": "0x005182f0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-PALETTE-SAFE-WAVE10",
    "score": 2,
    "symbol": "palette_row_layout_005c3000",
    "va": "0x005c3000"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-SPOREPEDIA-SAFE-WAVE10",
    "score": 2,
    "symbol": "sporepedia_asset_destroy_00642190",
    "va": "0x00642190"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg_app_safe_wave10/app_safe_wave10.cpp",
  "files": [
    "src/reconstruction/pkg_app_safe_wave10/app_safe_wave10.cpp",
    "src/reconstruction/pkg_app_safe_wave10/app_safe_wave10.hpp",
    "src/reconstruction/pkg_app_safe_wave10/app_safe_wave10_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave10-safe-core/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-app-safe-wave10/0041e920.json"
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
    "The body is a leaf, so no dependency port was introduced.",
    "The meaning of the storage mask 0x0030 and of the kind values 0x0001 and 0x0010 is inferred from the compare immediates only.",
    "The opaque +0x04..+0x0f region of the slot is never read, so no field evidence exists for it.",
    "The sentinel address 0x015d115d is a .data address returned to the caller as a marker; its runtime identity is not established.",
    "What the 0x015d115d sentinel means to each consumer that receives it",
    "What the opaque +0x04..+0x0f region of the slot holds",
    "What the storage mask 0x0030 encodes and how many storage kinds exist",
    "Whether a direct slot returning its own address is a stable identity or an inlined value",
    "Why only kind 0x0001 and kind 0x0010 are modelled while the halfword allows 0..0xffff",
    "gate-property-value-resolve-runtime-kind-and-storage-semantics",
    "no vtable or callee is involved, so no dependency port was introduced",
    "runtime validation not performed; static decompilation and disassembly only",
    "the meaning of the storage mask 0x0030 and of the kind values 0x0001 and 0x0010 is inferred from the compare immediates only",
    "the opaque +0x04..+0x0f region of the slot is never read, so no field evidence exists for it",
    "the sentinel address 0x015d115d is a .data address returned to the caller as a marker; its runtime identity is not established"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave10-safe-core/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-app-safe-wave10/0041e920.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_app_safe_wave10/app_safe_wave10.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_app_safe_wave10/app_safe_wave10.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_app_safe_wave10/app_safe_wave10_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/integrated/batch-2026-09-25-wave10-safe-core/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg-app-safe-wave10/0041e920.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_app_safe_wave10/app_safe_wave10.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_app_safe_wave10/app_safe_wave10.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_app_
[TRUNCATED]
```
