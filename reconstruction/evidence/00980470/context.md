# Reconstruction context 0x00980470

- Status: `partial`
- Content SHA-256: `4af3de34dd800898ae78def2d6abfd88be166b0efb2a300f1123d9bc46f6a61b`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00980470",
  "phase": "reconstruction",
  "target": "0x00980470"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "UTFWin::PerspectiveEffect::GetEventFlags",
  "package": "PKG-UTFWIN-EFFECTS-WAVE6",
  "subsystem": "UTFWin.Effects",
  "va": "0x00980470"
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
  "content_sha256": "9af448b204707992a2627c115121b43280d726093f61304e1db04935bb2913b4",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00980470 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "x86-32 thiscall with first explicit object word in ECX and caller cleanup",
  "return_semantics": "delegated result in EAX",
  "return_type": "Opaque",
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
      "callsite": "0x00980473",
      "direction": "out",
      "other": "0x00980490",
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
    "Opaque",
    "openspore::reconstruction::pkg_utfwin_effects_wave6::FloatRect",
    "openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueColorTarget",
    "openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueLayout",
    "openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueModulateEffect"
  ],
  "vtables": [
    "vtable:0x014184e4",
    "vtable:0x01440d24",
    "vtable:0x01441478",
    "vtable:0x014436c0",
    "vtable:0x014437b0",
    "vtable:0x01443f2c",
    "vtable:0x01444098"
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
      "adjusted object layout and delegated result ownership remain gated",
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
      "callsite": "0x00980473",
      "direction": "out",
      "other": "0x00980490",
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
    "id": "scc-0322",
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
    "symbol": "utfwin_0097e990",
    "va": "0x0097e990"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "shared_types:Opaque,openspore::reconstruction::pkg_utfwin_effects_wave6::FloatRect,openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueColorTarget,openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueLayout",
      "same_calling_convention"
    ],
    "package": "PKG-UTFWIN-EFFECTS-WAVE6",
    "score": 25,
    "symbol": "utfwin_0097e550",
    "va": "0x0097e550"
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
      "same_package",
      "same_subsystem",
      "shared_types:Opaque,openspore::
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__PerspectiveEffect__GetEventFlags.c",
  "file": "src/reconstruction/pkg_utfwin_effects_wave6/utfwin_effects_wave6.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__PerspectiveEffect__GetEventFlags.c",
    "src/reconstruction/pkg_utfwin_effects_wave6/utfwin_effects_wave6.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-utfwin-effects-wave6/00980470.json"
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
      "anchors": [
        "0x00960250",
        "0x00960250",
        "0x0095fcc0",
        "0x0095fcc0",
        "0x00960250",
        "0x00960250",
        "0x00960370",
        "0x00960370",
        "0x00961300",
        "0x00961300",
        "0x00980470",
        "0x00980470",
        "0x00aeb0e0",
        "0x00aeb0e0",
        "0x00aeb1c0",
        "0x00aeb1c0"
      ],
      "conflict_id": "Q-UTFWIN-ORDER",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
      "resolution_status": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
      "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
      "subject": null,
      "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
    }
  ],
  "unresolved_questions": [
    "adjusted object layout and delegated result ownership remain gated",
    "runtime validation not run"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__PerspectiveEffect__GetEventFlags.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-utfwin-effects-wave6/00980470.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_utfwin_effects_wave6/utfwin_effects_wave6.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__PerspectiveEffect__GetEventFlags.c",
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
      "ref": "reconstruction/metadata/pkg-utfwin-effects-wave6/00980470.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_utfwin_effects_wave6/utfwin_effects_wave6.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
 
[TRUNCATED]
```
