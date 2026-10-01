# Reconstruction context 0x0095fd60

- Status: `partial`
- Content SHA-256: `6b3574ade7736a635a39aa6e81d5a7e1b6752cf34dda62ab59586b76553a2dff`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x0095fd60",
  "phase": "reconstruction",
  "target": "0x0095fd60"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "UTFWin::Window::func35",
  "package": "pkg-utfwin-func35-wave12",
  "subsystem": "UTFWin",
  "va": "0x0095fd60"
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
  "content_sha256": "7518932e28a63ee615c86e2fcfc1cc6f4be9a3a82b5dcfd65717d022bd4835f0",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x0095fd60 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "thiscall; receiver in ECX (MOV ESI,ECX at 0x0095fd64)",
  "receiver": "ECX, saved to ESI at 0x0095fd64, used as the base for [ESI+0xa8], [ESI+0x1dc] and both vtable loads",
  "return_semantics": "void",
  "return_type": "void",
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
    "openspore::reconstruction::pkg_utfwin_func35_wave12::OpaquePendingQueue",
    "openspore::reconstruction::pkg_utfwin_func35_wave12::OpaqueStateMessage",
    "openspore::reconstruction::pkg_utfwin_func35_wave12::OpaqueWindow",
    "openspore::reconstruction::pkg_utfwin_func35_wave12::OpaqueWindowVTable",
    "void"
  ],
  "vtables": [
    "vtable:0x013fdb18",
    "vtable:0x013fdb6c",
    "vtable:0x01414bc0",
    "vtable:0x01414c14",
    "vtable:0x01414ed4",
    "vtable:0x01415178",
    "vtable:0x014151cc",
    "vtable:0x0141873c",
    "vtable:0x014190d4",
    "vtable:0x0141930c",
    "vtable:0x014195ac",
    "vtable:0x01419920"
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
      "ownership and lifetime of the word stored at +0xa8 unresolved",
      "producer of the +0x1dc gate unresolved",
      "record consumer semantics (vtable slot 0x114) unresolved"
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
    "id": "scc-0298",
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
      "shared_vtable:vtable:0x013fdb18,vtable:0x013fdb6c"
    ],
    "package": "pkg-0095fa30-utfwin-isancestorof",
    "score": 10,
    "symbol": "is_ancestor_of_0095fa30",
    "va": "0x0095fa30"
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
    "package": "pkg-dfw-00980510",
    "score": 6,
    "symbol": "dfw_get_proxy_id_00980510",
    "va": "0x00980510"
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
      "same_subsystem"
    ],
    "package": "pkg-utfwin-slot7-wave12",
    "score": 6,
    "symbol": "re_00fc7e10_UTFWin_ImageDrawable_GetTiling",
    "va": "0x00fc7e10"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "pkg-utfwin-settiling-wave13",
    "score": 6,
    "symbol": "set_tiling_00fd9460",
    "va": "0x00fd9460"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x013fdb18,vtable:0x01414bc0"
    ],
    "package": "PKG-UTFWIN-CORE-WAVE6",
    "score": 4,
    "symbol": "re_00575ea0",
    "va": "0x00575ea0"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x013fdb18,vtable:0x01414bc0"
    ],
    "package": "PKG-16-SPOREPEDIA-ONLINE",
    "score": 4,
    "symbol": "Sporepedia_cSPAssetDataOTDB_HasName_raw_00641770",
    "va": "0x00641770"
  
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__Window__func35.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__Window__func35.c",
    "reconstruction/staging/pkg-utfwin-func35-wave12/utfwin_func35_0095fd60.cpp",
    "reconstruction/staging/pkg-utfwin-func35-wave12/utfwin_func35_0095fd60.hpp",
    "reconstruction/staging/pkg-utfwin-func35-wave12/utfwin_func35_0095fd60_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-utfwin-func35-wave12/0095fd60.json"
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
    "The declaring class of func35 within UTFWin::Window: no MSVC RTTI exists in SporeApp.exe, so the owning class and its position in the hierarchy are not provable from this target alone.",
    "What the constant 0x13 in record +0x08 denotes: the SDK gives no name for func35, and the decompiler's 'Enum ObjectTYPE' warning is program-wide rather than tied to this literal, so no enum meaning is claimed.",
    "What vtable slot 0x114 does with the record. Its two observed implementations are an address with no defined function (0x00993200) and a stub returning 0 (0x006f2f20), so the consumer-side meaning of (0x13, new, previous) is unresolved.",
    "Whether the +0x1dc gate is a dirty/needs-invalidate flag. Only a zero test is observed here; the flag's producer and full field extent beyond 0x1df are unestablished (0x1e0 is only the arithmetic end of the last dword, not an observed object size).",
    "Whether the word at +0xa8 and the argument are object pointers or plain identifiers: this function only compares, stores and forwards the word, so nothing here distinguishes a pointer from an id; the value is kept as an opaque 32-bit word.",
    "ownership and lifetime of the word stored at +0xa8 unresolved",
    "producer of the +0x1dc gate unresolved",
    "record consumer semantics (vtable slot 0x114) unresolved"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__Window__func35.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-utfwin-func35-wave12/0095fd60.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-utfwin-func35-wave12/utfwin_func35_0095fd60.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-utfwin-func35-wave12/utfwin_func35_0095fd60.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-utfwin-func35-wave12/utfwin_func35_0095fd60_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__Window__func35.c",
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
      "ref": "reconstruction/metadata/pkg-utfwin-func35-wave12/0095fd60.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-utfwin-func35-wave12/utfwin_func35_0095fd60.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-utfwin-func35-wave12/utfwin_func35_0095fd60.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      
[TRUNCATED]
```
