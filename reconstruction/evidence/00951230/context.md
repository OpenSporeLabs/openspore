# Reconstruction context 0x00951230

- Status: `partial`
- Content SHA-256: `77607a26339365deb568da3bd9c66725892bbcf030d9d89e51cee8b2ddae2723`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00951230",
  "phase": "reconstruction",
  "target": "0x00951230"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "UTFWin::UTFWinObject::new_",
  "package": "PKG-UTFWIN-CORE-WAVE6",
  "subsystem": "UTFWin.Core",
  "va": "0x00951230"
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
  "content_sha256": "ed9fe46fa1d8233073d38a397739d400711493c3122961cd13dfd31161db6576",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00951230 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "x86-32 stdcall with three caller arguments and callee cleanup",
  "return_semantics": "null pointer in EAX",
  "return_type": "void*",
  "stack_cleanup_bytes": 12,
  "stack_cleanup_owner": "callee"
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
    "openspore::reconstruction::pkg_utfwin_core_wave6::CursorManager",
    "openspore::reconstruction::pkg_utfwin_core_wave6::Drawable",
    "openspore::reconstruction::pkg_utfwin_core_wave6::DropIconObject",
    "openspore::reconstruction::pkg_utfwin_core_wave6::ResourceFactory",
    "openspore::reconstruction::pkg_utfwin_core_wave6::TooltipCore",
    "openspore::reconstruction::pkg_utfwin_core_wave6::WindowCore",
    "void*"
  ],
  "vtables": [
    "vtable:0x013fa72c",
    "vtable:0x013fa794",
    "vtable:0x013fa7d8",
    "vtable:0x013fa810",
    "vtable:0x013fa8b0",
    "vtable:0x013fa8f0",
    "vtable:0x013fa974",
    "vtable:0x013fb2b8",
    "vtable:0x013fb2f8",
    "vtable:0x013fb408",
    "vtable:0x013fb448",
    "vtable:0x013fcc08"
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
      "allocation/serialization boundary and runtime caller contract remain gated",
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
    "id": "scc-0292",
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
      "shared_types:openspore::reconstruction::pkg_utfwin_core_wave6::CursorManager,openspore::reconstruction::pkg_utfwin_core_wave6::Drawable,openspore::reconstruction::pkg_utfwin_core_wave6::DropIconObject,openspore::reconstruction::pkg_utfwin_core_wave6::ResourceFactory",
      "shared_vtable:vtable:0x013fa72c,vtable:0x013fa794"
    ],
    "package": "PKG-UTFWIN-CORE-WAVE6",
    "score": 27,
    "symbol": "re_00951220",
    "va": "0x00951220"
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
    "symbol": "re_0095f960",
    "va": "0x0095f960"
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
    "symbol": "re_0095f990",
    "va": "0x0095f990"
  },
  {
    "match_basis
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__UTFWinObject__new_.c",
  "file": "src/reconstruction/pkg_utfwin_core_wave6/utfwin_core_wave6.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__UTFWinObject__new_.c",
    "src/reconstruction/pkg_utfwin_core_wave6/utfwin_core_wave6.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-utfwin-core-wave6/00951230.json"
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
        "0x013fa974",
        "0x01419794",
        "0x013fa974",
        "0x01419794",
        "0x013fa974",
        "0x01419794",
        "0x013fa974",
        "0x01419794",
        "0x00951230",
        "0x006f2f20",
        "0x00dde980",
        "0x01419794",
        "0x013fa974",
        "0x013fef9c",
        "0x0141a024",
        "0x01442324"
      ],
      "conflict_id": "VT-003",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "CONFLICT_REMAINS",
      "resolution_status": "CONFLICT_REMAINS",
      "source": "knowledgegraph/research/conflicts/track-a-type-signature.json",
      "subject": "0x013FA974 and 0x01419794 UTFWin 21-slot base candidates",
      "unresolved_reason": "There is no constructor, destructor, complete-table boundary, RTTI, or independent owner evidence to choose between byte-identical arrays."
    }
  ],
  "unresolved_questions": [
    "allocation/serialization boundary and runtime caller contract remain gated",
    "runtime validation not run"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__UTFWinObject__new_.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-utfwin-core-wave6/00951230.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_utfwin_core_wave6/utfwin_core_wave6.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__UTFWinObject__new_.c",
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
      "ref": "reconstruction/metadata/pkg-utfwin-core-wave6/00951230.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_utfwin_core_wave6/utfwin_core_wave6.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/know
[TRUNCATED]
```
