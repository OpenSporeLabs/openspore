# Reconstruction context 0x0095f960

- Status: `partial`
- Content SHA-256: `e3238085498f8d74958705d99a45a76e9f69989c450f25cb323417da56410702`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x0095f960",
  "phase": "reconstruction",
  "target": "0x0095f960"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "UTFWin::Window::GetRealArea",
  "package": "PKG-UTFWIN-CORE-WAVE6",
  "subsystem": "UTFWin.Core",
  "va": "0x0095f960"
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
  "content_sha256": "80caa3bff81590ad5b6955e74a36d74060b82ab8ab35747b0257fbb84077ee01",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x0095f960 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "x86-32 thiscall with first explicit window receiver in ECX and caller cleanup",
  "return_semantics": "window+4 pointer or null in EAX",
  "return_type": "void*",
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
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007f31b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007f5410"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0081cf00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00963f30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00967a20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0096b3d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00970270"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00980fc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00983b40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00985cb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00988690"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00989210"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0098f370"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00991f40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x009925b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00992da0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x007f31b3",
      "direction": "in",
      "other": "0x007f31b0",
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
    "openspore::reconstruction::pkg_utfwin_core_wave6::CursorManager",
    "openspore::reconstruction::pkg_utfwin_core_wave6::Drawable",
    "openspore::reconstruction::pkg_utfwin_core_wave6::DropIconObject",
    "openspore::reconstruction::pkg_utfwin_core_wave6::ResourceFactory",
    "openspore::reconstruction::pkg_utfwin_core_wave6::TooltipCore",
    "openspore::reconstruction::pkg_utfwin_core_wave6::WindowCore",
    "void*"
  ],
  "vtables": [
    "vtable:0x01414b10",
    "vtable:0x01418838",
    "vtable:0x01440b1c",
    "vtable:0x01441c18",
    "vtable:0x01443318",
    "vtable:0x0145d758",
    "vtable:0x014793e0",
    "vtable:0x0147fa30"
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
      "runtime validation not run",
      "window subobject layout and type domain remain gated"
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
      "va": "0x007f31b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007f5410"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0081cf00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00963f30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00967a20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0096b3d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00970270"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00980fc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00983b40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00985cb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00988690"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00989210"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0098f370"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00991f40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x009925b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00992da0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e0ab20"
    }
  ],
  "callers_truncated": false,
  "dat
[TRUNCATED]
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
      "shared_types:openspore::reconstruction::pkg_utfwin_core_wave6::CursorManager,openspore::reconstruction::pkg_utfwin_core_wave6::Drawable,openspore::reconstruction::pkg_utfwin_core_wave6::DropIconObject,openspore::reconstruction::pkg_utfwin_core_wave6::ResourceFactory",
      "shared_vtable:vtable:0x01414b10,vtable:0x01440b1c",
      "same_calling_convention"
    ],
    "package": "PKG-UTFWIN-CORE-WAVE6",
    "score": 29,
    "symbol": "re_0095f990",
    "va": "0x0095f990"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "shared_types:openspore::reconstruction::pkg_utfwin_core_wave6::CursorManager,openspore::reconstruction::pkg_utfwin_core_wave6::Drawable,openspore::reconstruction::pkg_utfwin_core_wave6::DropIconObject,openspore::reconstruction::pkg_utfwin_core_wave6::ResourceFactory",
      "shared_vtable:vtable:0x01414b10,vtable:0x01440b1c",
      "same_calling_convention"
    ],
    "package": "PKG-UTFWIN-CORE-WAVE6",
    "score": 29,
    "symbol": "re_0095f9a0",
    "va": "0x0095f9a0"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "shared_types:openspore::reconstruction::pkg_utfwin_core_wave6::CursorManager,openspore::reconstruction::pkg_utfwin_core_wave6::Drawable,openspore::reconstruction::pkg_utfwin_core_wave6::DropIconObject,openspore::reconstruction::pkg_utfwin_core_wave6::ResourceFactory",
      "shared_vtable:vtable:0x01414b10,vtable:0x01418838"
    ],
    "package": "PKG-UTFWIN-CORE-WAVE6",
    "score": 27,
    "symbol
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__Window__GetRealArea.c",
  "file": "src/reconstruction/pkg_utfwin_core_wave6/utfwin_core_wave6.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__Window__GetRealArea.c",
    "src/reconstruction/pkg_utfwin_core_wave6/utfwin_core_wave6.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-utfwin-core-wave6/0095f960.json"
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
    "runtime validation not run",
    "window subobject layout and type domain remain gated"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__Window__GetRealArea.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-utfwin-core-wave6/0095f960.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_utfwin_core_wave6/utfwin_core_wave6.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__Window__GetRealArea.c",
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
      "ref": "reconstruction/metadata/pkg-utfwin-core-wave6/0095f960.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_utfwin_core_wave6/utfwin_core_wave6.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/kno
[TRUNCATED]
```
