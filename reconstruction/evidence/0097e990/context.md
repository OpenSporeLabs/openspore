# Reconstruction context 0x0097e990

- Status: `partial`
- Content SHA-256: `c82bf5133f7558bf450dd156f3bce3005662766f7b650582c41a61d245d4b275`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x0097e990",
  "phase": "reconstruction",
  "target": "0x0097e990"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "UTFWin::SimpleLayout::SetSerializer",
  "package": "PKG-UTFWIN-EFFECTS-WAVE6",
  "subsystem": "UTFWin.Effects",
  "va": "0x0097e990"
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
  "content_sha256": "3dd39fbfbf0a6d1ff7881fbbfbfd9a827d939b349ec7c0bbeef742ae99bbc180",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x0097e990 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "x86-32 thiscall with first explicit layout receiver in ECX and caller cleanup",
  "return_semantics": "bool in AL; always true",
  "return_type": "bool",
  "stack_cleanup_bytes": 8,
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
    "bool",
    "openspore::reconstruction::pkg_utfwin_effects_wave6::FloatRect",
    "openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueColorTarget",
    "openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueLayout",
    "openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueModulateEffect"
  ],
  "vtables": [
    "vtable:0x014437b0"
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
      "layout flag semantics, pointer validity, and runtime rectangle ownership remain gated",
      "runtime validation not run"
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
    "id": "scc-0318",
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
      "shared_types:openspore::reconstruction::pkg_utfwin_effects_wave6::FloatRect,openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueColorTarget,openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueLayout,openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueModulateEffect",
      "shared_vtable:vtable:0x014437b0"
    ],
    "package": "PKG-UTFWIN-EFFECTS-WAVE6",
    "score": 27,
    "symbol": "utfwin_00980470",
    "va": "0x00980470"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "shared_types:openspore::reconstruction::pkg_utfwin_effects_wave6::FloatRect,openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueColorTarget,openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueLayout,openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueModulateEffect",
      "same_calling_convention"
    ],
    "package": "PKG-UTFWIN-EFFECTS-WAVE6",
    "score": 25,
    "symbol": "utfwin_0097ea50",
    "va": "0x0097ea50"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "shared_types:openspore::reconstruction::pkg_utfwin_effects_wave6::FloatRect,openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueColorTarget,openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueLayout,openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueModulateEffect"
    ],
    "package": "PKG-UTFWIN-EFFECTS-WAVE6",
    "score": 23,
    "symbol": "utfwin_0096fec0",
    "va": "0x0096fec0"
  },
  {
    "match_basis": [
      "same_packa
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__SimpleLayout__SetSerializer.c",
  "file": "src/reconstruction/pkg_utfwin_effects_wave6/utfwin_effects_wave6.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__SimpleLayout__SetSerializer.c",
    "src/reconstruction/pkg_utfwin_effects_wave6/utfwin_effects_wave6.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-utfwin-effects-wave6/0097e990.json"
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
    "layout flag semantics, pointer validity, and runtime rectangle ownership remain gated",
    "runtime validation not run"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__SimpleLayout__SetSerializer.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-utfwin-effects-wave6/0097e990.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_utfwin_effects_wave6/utfwin_effects_wave6.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__SimpleLayout__SetSerializer.c",
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
      "ref": "reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg-utfwin-effects-wave6/0097e990.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_utfwin_effects_wave6/utfwin_effects_wave6.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "r
[TRUNCATED]
```
