# Reconstruction context 0x00506590

- Status: `partial`
- Content SHA-256: `6aa910c99fb891c0e1bdc6657afce9b406bd4dd15e67a6682d495a0a8f1423b0`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00506590",
  "phase": "reconstruction",
  "target": "0x00506590"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "Skinner::cSkinPainter",
  "name": "skin_painter_state_setup_00506590",
  "package": "PKG-SKINNER-SAFE-WAVE10",
  "subsystem": "Skinner",
  "va": "0x00506590"
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
  "content_sha256": "0ad8da6ece210aed1973a6e1e50afbb5e09a69c3ef138d7ad68be01d2095c52c",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00506590 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "thiscall with callee stack cleanup",
  "receiver_register": "ECX",
  "ret_form": "RET 0x4",
  "return_register": "EAX",
  "return_width_bytes": 0,
  "stack_arguments": [
    {
      "entry_offset": "EBP+0x08",
      "machine_type": "std::uint32_t",
      "native_reads": [
        "EBP+0x08 loaded twice per create call, PUSH EAX then PUSH EAX",
        "EBP+0x08 stored verbatim to receiver+0x1c"
      ],
      "normalized_name": "source",
      "position": 1,
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 4
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
      "va": "0x00521ba0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00521c08",
      "direction": "in",
      "other": "0x00521ba0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005065c4",
      "direction": "out",
      "other": "0x005288f0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00506609",
      "direction": "out",
      "other": "0x005288f0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0050664e",
      "direction": "out",
      "other": "0x005288f0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005065a8",
      "direction": "out",
      "other": "0x00f473a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005065ed",
      "direction": "out",
      "other": "0x00f473a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00506632",
      "direction": "out",
      "other": "0x00f473a0",
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
    "global:0x013eecd8",
    "global:0x01471064",
    "global:0x01485720"
  ],
  "types": [
    "OpaqueLayerFactory",
    "OpaqueSkinPainterState",
    "OpaqueSkinPainterState*",
    "OpaqueTexturePainter",
    "OpaqueTexturePainter*",
    "Skinner::cSkinPainter",
    "float",
    "std::uint32_t",
    "unsigned int",
    "void"
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
      "Receiver class identity is taken from the triage record /Spore/Skinner/cSkinPainter; offsets 0x00..0x0f and above 0x30 are not exercised.",
      "The 0x64 size class and the \"Skinner\" tag at 0x013f116c are inferred from the call shape, not from an SDK signature.",
      "The neighbouring 0x005171b0 label is repaired-contained inside this body and no symbol is claimed for it.",
      "The two unresolved callees at 0x00f473a0 and 0x005288f0 are owned elsewhere and remain runtime gated.",
      "gate-skin-painter-setup-runtime-acquire-and-scale-values"
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
      "va": "0x00521ba0"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00521c08",
      "direction": "in",
      "other": "0x00521ba0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005065c4",
      "direction": "out",
      "other": "0x005288f0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00506609",
      "direction": "out",
      "other": "0x005288f0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0050664e",
      "direction": "out",
      "other": "0x005288f0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005065a8",
      "direction": "out",
      "other": "0x00f473a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005065ed",
      "direction": "out",
      "other": "0x00f473a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00506632",
      "direction": "out",
      "other": "0x00f473a0",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 1,
  "fan_out": 0,
  "manifest_callees": [
    "0x00f473a0",
    "0x005288f0"
  ],
  "manifest_callers": [],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0039",
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
    "symbol": "skin_painter_job_brush_pass_005182f0",
    "va": "0x005182f0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_types:OpaqueTexturePainter"
    ],
    "package": "PKG-SKINNER-SAFE-WAVE11",
    "score": 9,
    "symbol": "skin_tex0_full_region_00518bf0",
    "va": "0x00518bf0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_types:OpaqueTexturePainter"
    ],
    "package": "PKG-SKINNER-SAFE-WAVE11",
    "score": 9,
    "symbol": "skin_rig_block_draw_00518f10",
    "va": "0x00518f10"
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
    "symbol": "skin_tex2_uv_region_00518cf0",
    "va": "0x00518cf0"
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
      "shared_types:unsigned int",
      "same_calling_convention"
    ],
    "package": "PKG-APP-SAFE-WAVE10",
  
[TRUNCATED]
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
    "reconstruction/metadata/pkg-skinner-safe-wave10/00506590.json"
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
    "Receiver class identity is taken from the triage record /Spore/Skinner/cSkinPainter; offsets 0x00..0x0f and above 0x30 are not exercised.",
    "The 0x64 size class and the \"Skinner\" tag at 0x013f116c are inferred from the call shape, not from an SDK signature.",
    "The neighbouring 0x005171b0 label is repaired-contained inside this body and no symbol is claimed for it.",
    "The two unresolved callees at 0x00f473a0 and 0x005288f0 are owned elsewhere and remain runtime gated.",
    "What reads the five scale floats written at +0x20 through +0x30",
    "What the 0x64 size class and the \"Skinner\" tag at 0x013f116c select in the allocator",
    "Whether the receiver offsets 0x00..0x0f and above 0x30 are initialised by the caller",
    "Whether the three texture painters are ever replaced or re-created later",
    "Who owns the allocator 0x00f473a0 and the constructor 0x005288f0",
    "gate-skin-painter-setup-runtime-acquire-and-scale-values"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave10-safe-core/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-skinner-safe-wave10/00506590.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_skinner_safe_wave10/skinner_safe_wave10.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_skinner_safe_wave10/skinner_safe_wave10.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_skinner_safe_wave10/skinner_safe_wave10_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-skinner-safe-wave10/00506590.json",
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
