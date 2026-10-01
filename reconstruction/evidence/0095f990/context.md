# Reconstruction context 0x0095f990

- Status: `partial`
- Content SHA-256: `ee91d758d28a73c7b6223accfd3a74da66506ba4dae563a01feb6fd6bb46b6cb`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x0095f990",
  "phase": "reconstruction",
  "target": "0x0095f990"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "UTFWin::Window::SetCommandID",
  "package": "PKG-UTFWIN-CORE-WAVE6",
  "subsystem": "UTFWin.Core",
  "va": "0x0095f990"
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
  "content_sha256": "b2200349fb438eeaec75ad3c6e9e56e9324b541ad0b87753ebcf9882ccba03b2",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x0095f990 failed: Decompilation did not complete. Reason: ",
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
  "return_semantics": "new signed 32-bit reference count in EAX",
  "return_type": "std::int32_t",
  "stack_cleanup_bytes": 0,
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
      "va": "0x007f31d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00952860"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x009568c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00963f10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b1dc60"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d0a760"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e0eab0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x007f31d3",
      "direction": "in",
      "other": "0x007f31d0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x009528b4",
      "direction": "in",
      "other": "0x00952860",
      "reference_type": "computed-call"
    },
    {
      "callsite": "0x00956992",
      "direction": "in",
      "other": "0x009568c0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00963f10",
      "direction": "in",
      "other": "0x00963f10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00b1de02",
      "direction": "in",
      "other": "0x00b1dc60",
      "reference_type": "computed-call"
    },
    {
      "callsite": "0x00d0a8b9",
      "direction": "in",
      "other": "0x00d0a760",
      "reference_type": "computed-call"
    },
    {
      "callsite": "0x00e0ee4a",
      "direction": "in",
      "other": "0x00e0eab0",
      "re
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
    "std::int32_t"
  ],
  "vtables": [
    "vtable:0x01414b10",
    "vtable:0x01414ce0",
    "vtable:0x01440448",
    "vtable:0x0144064c",
    "vtable:0x01440b1c",
    "vtable:0x01441c18",
    "vtable:0x01443318",
    "vtable:0x01446078",
    "vtable:0x014462b0",
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
      "window lifetime and reference-count synchronization remain gated"
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
      "va": "0x007f31d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00952860"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x009568c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00963f10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b1dc60"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d0a760"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e0eab0"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x007f31d3",
      "direction": "in",
      "other": "0x007f31d0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x009528b4",
      "direction": "in",
      "other": "0x00952860",
      "reference_type": "computed-call"
    },
    {
      "callsite": "0x00956992",
      "direction": "in",
      "other": "0x009568c0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00963f10",
      "direction": "in",
      "other": "0x00963f10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00b1de02",
      "direction": "in",
      "other": "0x00b1dc60",
      "reference_type": "computed-call"
    },
    {
      "callsite": "0x00d0a8b9",
      "direction": "in",
      "other": "0x00d0a760",
      "reference_type": "computed-call"
    },
    {
      "cal
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
    "symbol": "re_0095f960",
    "va": "0x0095f960"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "shared_types:openspore::reconstruction::pkg_utfwin_core_wave6::CursorManager,openspore::reconstruction::pkg_utfwin_core_wave6::Drawable,openspore::reconstruction::pkg_utfwin_core_wave6::DropIconObject,openspore::reconstruction::pkg_utfwin_core_wave6::ResourceFactory",
      "shared_vtable:vtable:0x01414b10,vtable:0x01414ce0",
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
      "shared_vtable:vtable:0x01414b10,vtable:0x01414ce0"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__Window__SetCommandID.c",
  "file": "src/reconstruction/pkg_utfwin_core_wave6/utfwin_core_wave6.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__Window__SetCommandID.c",
    "src/reconstruction/pkg_utfwin_core_wave6/utfwin_core_wave6.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-utfwin-core-wave6/0095f990.json"
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
    "window lifetime and reference-count synchronization remain gated"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__Window__SetCommandID.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-utfwin-core-wave6/0095f990.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_utfwin_core_wave6/utfwin_core_wave6.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__Window__SetCommandID.c",
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
      "ref": "reconstruction/metadata/pkg-utfwin-core-wave6/0095f990.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_utfwin_core_wave6/utfwin_core_wave6.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/kn
[TRUNCATED]
```
