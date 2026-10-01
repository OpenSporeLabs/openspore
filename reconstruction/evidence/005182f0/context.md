# Reconstruction context 0x005182f0

- Status: `partial`
- Content SHA-256: `ea398f73a76edef5887c94ecc31b904c15b7a3aab6e7a67dbb4f416722f8b12b`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x005182f0",
  "phase": "reconstruction",
  "target": "0x005182f0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "Skinner::cSkinPainterJobApplyBrushes",
  "name": "skin_painter_job_brush_pass_005182f0",
  "package": "PKG-SKINNER-SAFE-WAVE10",
  "subsystem": "Skinner",
  "va": "0x005182f0"
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
  "content_sha256": "e8ae966b465768720d44196cfb884233909ab110164ed5381980150fd61343a8",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x005182f0 failed: Decompilation did not complete. Reason: ",
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
  "callers": [],
  "edge_rows": [
    {
      "callsite": "0x00518339",
      "direction": "out",
      "other": "0x00517430",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0051835d",
      "direction": "out",
      "other": "0x00517430",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00518379",
      "direction": "out",
      "other": "0x00517430",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00518395",
      "direction": "out",
      "other": "0x00517430",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005183a8",
      "direction": "out",
      "other": "0x00517430",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005182f9",
      "direction": "out",
      "other": "0x0067dd00",
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
    "DATA",
    "OpaqueGraphicsProbe",
    "OpaqueGraphicsProbeVTable",
    "OpaquePainterJob",
    "OpaquePainterJob*",
    "Skinner::cSkinPainterJobApplyBrushes",
    "std::int32_t",
    "unsigned int"
  ],
  "vtables": [
    "vtable:0x013f1a30"
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
      "Pass field semantics are inferred from 0x00517430, which increments and wraps the counter at 4; that body is owned elsewhere and is not reconstructed here.",
      "The 12 attempt limit is a static property; the runtime distribution of the pass field at the limit is not established.",
      "The vtable cluster at 0x013f1a30 is unattributed in docs/analysis/vtables.json, so slot 25 is bound to this body by the data pointer alone.",
      "The widened 0 and 1 on the short paths follow the repository convention rather than a literal 32 bit store in the original.",
      "gate-skin-painter-brush-pass-runtime-probe-and-step-semantics"
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
  "edges": [
    {
      "callsite": "0x00518339",
      "direction": "out",
      "other": "0x00517430",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0051835d",
      "direction": "out",
      "other": "0x00517430",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00518379",
      "direction": "out",
      "other": "0x00517430",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00518395",
      "direction": "out",
      "other": "0x00517430",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005183a8",
      "direction": "out",
      "other": "0x00517430",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005182f9",
      "direction": "out",
      "other": "0x0067dd00",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 0,
  "fan_out": 0,
  "manifest_callees": [
    "0x0067dd00",
    "0x00517430"
  ],
  "manifest_callers": [],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0040",
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
      "same_package",
      "same_subsystem",
      "shared_types:unsigned int"
    ],
    "package": "PKG-SKINNER-SAFE-WAVE10",
    "score": 17,
    "symbol": "skin_painter_state_setup_00506590",
    "va": "0x00506590"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-SKINNER-SAFE-WAVE11",
    "score": 6,
    "symbol": "skin_paint_slot_pass_005183c0",
    "va": "0x005183c0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-SKINNER-SAFE-WAVE11",
    "score": 6,
    "symbol": "skin_tex0_full_region_00518bf0",
    "va": "0x00518bf0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-SKINNER-SAFE-WAVE11",
    "score": 6,
    "symbol": "skin_tex2_uv_region_00518cf0",
    "va": "0x00518cf0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-SKINNER-SAFE-WAVE11",
    "score": 6,
    "symbol": "skin_rig_block_draw_00518f10",
    "va": "0x00518f10"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-SKINNER-SAFE-WAVE11",
    "score": 6,
    "symbol": "skin_rig_index_pass_0051a350",
    "va": "0x0051a350"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-SKINNER-SAFE-WAVE11",
    "score": 6,
    "symbol": "skin_job_setup_0051a9a0",
    "va": "0x0051a9a0"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x013f1a30"
    ],
    "package": "pkg-vft-preinc-0051e340",
    "score": 4,
    "symbol": "vft_preinc_0051e340",
    "va": "0x0051e340"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg_skinner_safe_wave10/skinner_safe_wave10.cpp",
  "files": [
    "src/reconstruction/pkg_skinner_safe_wave10/skinner_safe_wave10.cpp",
    "src/reconstruction/pkg_skinner_safe_wave10/skinner_safe_wave10.hpp",
    "src/reconstruction/pkg_skinner_safe_wave10/skinner_safe_wave10_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave10-safe-core/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-skinner-safe-wave10/005182f0.json"
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
    "Pass field semantics are inferred from 0x00517430, which increments and wraps the counter at 4; that body is owned elsewhere and is not reconstructed here.",
    "The 12 attempt limit is a static property; the runtime distribution of the pass field at the limit is not established.",
    "The vtable cluster at 0x013f1a30 is unattributed in docs/analysis/vtables.json, so slot 25 is bound to this body by the data pointer alone.",
    "The widened 0 and 1 on the short paths follow the repository convention rather than a literal 32 bit store in the original.",
    "What the graphics probe query at slot +0x44 actually asks",
    "What the pass field at +0x14 enumerates and which values other than 0, 2 and 3 occur",
    "What the step port 0x00517430 does per call and how it wraps the counter at 4",
    "Which class owns the vtable cluster at 0x013f1a30",
    "Why the attempt limit is 12 and what happens at the limit with a nonzero pass",
    "gate-skin-painter-brush-pass-runtime-probe-and-step-semantics"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave10-safe-core/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-skinner-safe-wave10/005182f0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_skinner_safe_wave10/skinner_safe_wave10.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_skinner_safe_wave10/skinner_safe_wave10.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_skinner_safe_wave10/skinner_safe_wave10_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-skinner-safe-wave10/005182f0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_skinner_safe_wave10/skinner_safe_wave10.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_skinner_safe_wave10/skinner_safe_wave10.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/rec
[TRUNCATED]
```
