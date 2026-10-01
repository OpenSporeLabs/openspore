# Reconstruction context 0x0096fec0

- Status: `partial`
- Content SHA-256: `cb6a478a08470b70bf82577f3455f705e19b8adac086567265ff6f8b2362fee2`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x0096fec0",
  "phase": "reconstruction",
  "target": "0x0096fec0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "UTFWin::GlideEffect::GetProxyID",
  "package": "PKG-UTFWIN-EFFECTS-WAVE6",
  "subsystem": "UTFWin.Effects",
  "va": "0x0096fec0"
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
  "content_sha256": "af95890264020fb8a9736d447a72b7a0c6d2106b5988a1346612a5beb18321bf",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x0096fec0 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "x86-32 thiscall with first explicit opaque word in ECX and caller cleanup",
  "return_semantics": "object pointer in EAX or null",
  "return_type": "Opaque*",
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
  "edge_rows": [
    {
      "callsite": "0x0096fec8",
      "direction": "out",
      "other": "0x009512c0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0096fed7",
      "direction": "out",
      "other": "0x009512d0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0096fee5",
      "direction": "out",
      "other": "0x0096fe30",
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
    "openspore::reconstruction::pkg_utfwin_effects_wave6::FloatRect",
    "openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueColorTarget",
    "openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueLayout",
    "openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueModulateEffect"
  ],
  "vtables": [
    "vtable:0x01442490"
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
      "allocator, type name, constructor, and returned object ownership remain gated",
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
  "edges": [
    {
      "callsite": "0x0096fec8",
      "direction": "out",
      "other": "0x009512c0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0096fed7",
      "direction": "out",
      "other": "0x009512d0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0096fee5",
      "direction": "out",
      "other": "0x0096fe30",
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
    "id": "scc-0311",
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
      "same_calling_convention"
    ],
    "package": "PKG-UTFWIN-EFFECTS-WAVE6",
    "score": 25,
    "symbol": "utfwin_0096ffc0",
    "va": "0x0096ffc0"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "shared_types:Opaque*,openspore::reconstruction::pkg_utfwin_effects_wave6::FloatRect,openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueColorTarget,openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueLayout",
      "same_calling_convention"
    ],
    "package": "PKG-UTFWIN-EFFECTS-WAVE6",
    "score": 25,
    "symbol": "utfwin_0097e440",
    "va": "0x0097e440"
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
    "symbol": "utfwin_0097e890",
    "va": "0x0097e890"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "share
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__GlideEffect__GetProxyID.c",
  "file": "src/reconstruction/pkg_utfwin_effects_wave6/utfwin_effects_wave6.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__GlideEffect__GetProxyID.c",
    "src/reconstruction/pkg_utfwin_effects_wave6/utfwin_effects_wave6.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-utfwin-effects-wave6/0096fec0.json"
  ]
}
```

## 13_semantic_hypotheses

- State: `missing`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

## 14_conflicts_questions

- State: `conflicted`
- Provenance: `reconstruction/knowledge/index.json, knowledgegraph/research/semantic-decomp.json`

```json
{
  "conflicts": [
    {
      "derived": "__stdcall",
      "field": "calling_convention",
      "kind": "derived_vs_persisted",
      "persisted": "x86-32 thiscall with first explicit opaque word in ECX and caller cleanup",
      "resolution_status": "unresolved"
    }
  ],
  "unresolved_questions": [
    "allocator, type name, constructor, and returned object ownership remain gated",
    "runtime validation not run"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__GlideEffect__GetProxyID.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-utfwin-effects-wave6/0096fec0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_utfwin_effects_wave6/utfwin_effects_wave6.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__GlideEffect__GetProxyID.c",
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
      "ref": "reconstruction/metadata/pkg-utfwin-effects-wave6/0096fec0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_utfwin_effects_wave6/utfwin_effects_wave6.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "recon
[TRUNCATED]
```
