# Reconstruction context 0x0095fa30

- Status: `partial`
- Content SHA-256: `a8b5f897ed227c7f9e5f9577798ad0ea572f97b13a4bb7a425ee2ce0846071cf`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x0095fa30",
  "phase": "reconstruction",
  "target": "0x0095fa30"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "UTFWin::Window::IsAncestorOf",
  "package": "pkg-0095fa30-utfwin-isancestorof",
  "subsystem": "UTFWin",
  "va": "0x0095fa30"
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
  "content_sha256": "f435e179d3d83770459b2de12b537146a60b60775f34e557eb085c73c5d14ccd",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x0095fa30 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": [
    "thiscall; the receiver is the ECX hidden argument (the decompiler renders it as `IWindow * this`, and Ghidra warns 'Unknown calling convention')",
    "thiscall"
  ],
  "hidden_receiver": "ECX is the window receiver, the decompiler renders it as IWindow * this",
  "ordinary_stack_argument_slots": 1,
  "ordinary_stack_arguments": [
    "{'address_at_entry': '[ESP+0x4]', 'ghidra_type': 'IWindow * pChildWindow', 'stack_slot': 0, 'use': 'copied verbatim into EAX and then into receiver+0x80; never dereferenced', 'width_bytes': 4}",
    "{'address_at_entry': '[ESP+0x4]', 'ghidra_type': 'IWindow * pChildWindow', 'use': 'copied verbatim into EAX at 0x0095fa30 and stored at receiver+0x80 at 0x0095fa34; never dereferenced, never compared, never tested', 'width_bytes': 4}"
  ],
  "receiver": "ECX, used as the base of the single store `MOV dword ptr [ECX + 0x80],EAX` at 0x0095fa34; never saved to another register and never read from",
  "ret_form": "RET 0x4",
  "return_register": "none; EAX still holds the copied stack word at the RET",
  "return_semantics": [
    "void",
    "void; the body stores the argument and falls through to RET 0x4. No instruction after 0x0095fa30 writes EAX, so the copied argument word survives in EAX at the RET, and no evidence claims that residue as a returned value."
  ],
  "return_type": "void",
  "saved_registers": [],
  "stack_cleanup_bytes": 4,
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
  "globals": [
    "global:high"
  ],
  "types": [
    "DATA",
    "IWindow * pChildWindow",
    "medium (machine says void, SDK label says bool; the machine reading is the one modelled)",
    "openspore::reconstruction::pkg_0095fa30_utfwin_isancestorof::AbiIsAncestorOf0095fa30",
    "openspore::reconstruction::pkg_0095fa30_utfwin_isancestorof::Opaque",
    "openspore::reconstruction::pkg_0095fa30_utfwin_isancestorof::OpaqueWindow",
    "openspore::reconstruction::pkg_0095fa30_utfwin_isancestorof::OpaqueWindowVTable",
    "openspore::reconstruction::pkg_orchestrate_dogfood_0095fa30::Abi0095fa30",
    "openspore::reconstruction::pkg_orchestrate_dogfood_0095fa30::OpaqueWindow",
    "openspore::reconstruction::pkg_orchestrate_dogfood_0095fa30::OpaqueWindowLayout",
    "openspore::reconstruction::pkg_orchestrate_dogfood_0095fa30::TargetPorts",
    "void"
  ],
  "vtables": [
    "vtable:0x013fdb18",
    "vtable:0x013fdb6c",
    "vtable:0x0140f854",
    "vtable:0x01414bc0",
    "vtable:0x01414c14",
    "vtable:0x01414ed4",
    "vtable:0x01415178",
    "vtable:0x014151cc",
    "vtable:0x0141873c",
    "vtable:0x014190d4",
    "vtable:0x0141930c",
    "vtable:0x014195ac"
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
      "Confirm the containing table base and slot displacement of at least one of the 33 references so the shared-vtable analogue chain can be grounded.",
      "Observe a real virtual call through one of the 33 function words and record the receiver instance state before and after the store at receiver+0x80.",
      "Observe whether any caller consumes AL after the RET 0x4, which would give the EAX residue a real contract the static body cannot prove.",
      "Record the real receiver allocation size, because the 0x84 byte modeled extent is only the prefix through the written slot.",
      "Record the runtime value stored at receiver+0x80 and whether the same word is later consumed as a window pointer, a vtable-adjacent field or a reference count carrier.",
      "confirm the class identity behind the 33 vtable images; the binary has no MSVC RTTI",
      "observe one real virtual call through a slot +0x00 word and record whether the caller consumes AL, which would settle the void-vs-bool return type",
      "record the receiver allocation size at runtime; the 0x84 byte modelled extent is only the prefix through the written slot",
      "record the value stored at receiver+0x80 and find its consumer, to establish whether the SDK name IsAncestorOf is misassigned"
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
    "id": "scc-0297",
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
    "package": "pkg-utfwin-func35-wave12",
    "score": 10,
    "symbol": "func35_0095fd60",
    "va": "0x0095fd60"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_types:DATA"
    ],
    "package": "pkg-dfw-0096ff70",
    "score": 9,
    "symbol": "dfw_func88h_0096ff70",
    "va": "0x0096ff70"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_types:DATA"
    ],
    "package": "pkg-dfw-00980c50",
    "score": 9,
    "symbol": "dfw_00980c50_func88h",
    "va": "0x00980c50"
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
    "symbol": "Sporepedia_cSPAssetDataOTDB_HasName_ra
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__Window__IsAncestorOf.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__Window__IsAncestorOf.c",
    "reconstruction/staging/pkg-0095fa30-utfwin-isancestorof/utfwin_is_ancestor_of_0095fa30.cpp",
    "reconstruction/staging/pkg-0095fa30-utfwin-isancestorof/utfwin_is_ancestor_of_0095fa30.hpp",
    "reconstruction/staging/pkg-0095fa30-utfwin-isancestorof/utfwin_is_ancestor_of_0095fa30_model_test.cpp",
    "reconstruction/staging/pkg-orchestrate-dogfood-0095fa30/dogfood_0095fa30.cpp",
    "reconstruction/staging/pkg-orchestrate-dogfood-0095fa30/dogfood_0095fa30.hpp",
    "reconstruction/staging/pkg-orchestrate-dogfood-0095fa30/dogfood_0095fa30_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-0095fa30-utfwin-isancestorof/0095fa30.json",
    "reconstruction/metadata/pkg-orchestrate-dogfood-0095fa30/0095fa30.json"
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
    "Confirm the containing table base and slot displacement of at least one of the 33 references so the shared-vtable analogue chain can be grounded.",
    "Is the EAX residue at the RET meaningful to any caller, and does any of the 33 virtual slots get its result from AL?",
    "Is the stored word a window pointer, a vtable-adjacent pointer, or a reference-counted handle? The decompiler types it as IWindow * but nothing here proves that.",
    "Observe a real virtual call through one of the 33 function words and record the receiver instance state before and after the store at receiver+0x80.",
    "Observe whether any caller consumes AL after the RET 0x4, which would give the EAX residue a real contract the static body cannot prove.",
    "Record the real receiver allocation size, because the 0x84 byte modeled extent is only the prefix through the written slot.",
    "Record the runtime value stored at receiver+0x80 and whether the same word is later consumed as a window pointer, a vtable-adjacent field or a reference count carrier.",
    "Return type: the SDK symbol table and the Ghidra signature say bool, but the machine writes no AL and no upper EAX bytes on any path, so the reconstruction models void. Settling this needs a runtime trace of one virtual call through slot +0x00, recording whether the caller reads AL.",
    "Semantics of the word stored at receiver+0x80: whether it is a window pointer, a registration record, a cached argument or a reference-count carrier. No instruction in this body dereferences or compares 
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__Window__IsAncestorOf.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-0095fa30-utfwin-isancestorof/0095fa30.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-orchestrate-dogfood-0095fa30/0095fa30.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-0095fa30-utfwin-isancestorof/utfwin_is_ancestor_of_0095fa30.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-0095fa30-utfwin-isancestorof/utfwin_is_ancestor_of_0095fa30.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-0095fa30-utfwin-isancestorof/utfwin_is_ancestor_of_0095fa30_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-orchestrate-dogfood-0095fa30/dogfood_0095fa30.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-orchestrate-dogfood-0095fa30/dogfood_0095fa30.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-orchestrate-dogfood-0095fa30/dogfood_0095fa30_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__Window__IsAncestorOf.c",
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
      "ref": "reconstruction/metadata/pkg-0095fa30-utfwin-isancestorof/0095fa30.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg-orchestrate-dogfood-0095fa30/0095fa30.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-0095fa30-utfwin-isancestorof/utfwin_is_ancestor_of_0095fa30.cpp",
      "source_class": "committed_artifact"
    },
    {
      "
[TRUNCATED]
```
