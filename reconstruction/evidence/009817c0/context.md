# Reconstruction context 0x009817c0

- Status: `complete`
- Content SHA-256: `efbfbd044497b92fd3130166dd7a19073ecac220036ddefe38894d13d1e5a795`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x009817c0",
  "phase": "reconstruction",
  "target": "0x009817c0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "UTFWin::ScrollbarDrawable::SetImage",
  "package": null,
  "subsystem": "UTFWin",
  "va": "0x009817c0"
}
```

## 03_current_status

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "blocked": false,
  "reconstructed": false,
  "runtime_gated": true,
  "runtime_validated": 0,
  "status": "queued"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "dc9919649603e2784a0d4ac7f9803b427e11a44140ca286d605ee2919bbb6358",
  "live_attempts": [],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `present`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json

/* WARNING: Unknown calling convention */
/* WARNING: Enum "ObjectTYPE": Some values do not have unique names */

void UTFWin__ScrollbarDrawable__SetImage(IScrollbarDrawable *this,int index,Image *pImage)

{
  int in_ECX;
  
  if (this == (IScrollbarDrawable *)0xeec58382) {
    if (in_ECX != 0) {
      return;
    }
  }
  else {
    if (this != (IScrollbarDrawable *)0xeef3af8c) {
      FUN_00951240();
      return;
    }
    if (in_ECX != 0) {
      return;
    }
  }
  return;
}


```

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "convention": "__thiscall",
  "hidden_this": true,
  "ordinary_stack_argument_slots": [
    "entry_ESP+0x4"
  ],
  "ordinary_stack_arguments": [
    "{'entry_offset': 'entry_ESP+0x4', 'local_spelling': 'key', 'name': 'hash', 'observed': True, 'ordinal': 1, 'role': \"32-bit comparison key, tested against four CMP immediates across this body and its tail-call target, and never masked, widened or used as an index. The name and the type are the record's; this package adds nothing to them. Nothing establishes that the value is a hash of anything, and the model does not claim that.\", 'sizes': [4], 'type': 'uint32_t'}",
    "{'entry_offset': 'entry_ESP+0x4', 'name': 'hash', 'observed': True, 'ordinal': 1, 'role': '32-bit comparison key, tested against four CMP immediates and never masked, widened or used as an index', 'size_inferred': False, 'sizes': [4], 'type': 'uint32_t'}"
  ],
  "receiver": true,
  "receiver_register": "ECX",
  "ret_form": "RET 0x4",
  "return_observation": "EAX is written on every path. The three null exits materialise it with XOR EAX,EAX, the two local offset exits with LEA EAX,[ECX+0x4] and LEA EAX,[ECX+0xc], and the delegated paths by the tail-called 0x00951240, whose own exits are ADD EAX,0x4 and XOR EAX,EAX. So the returned value is always a deliberate pointer result, not a residual register.",
  "return_register": "EAX",
  "return_semantics": "Returns the address of the member selected by the hash argument relative to the receiver: receiver + 0x04 for hash 0xeec58382, receiver + 0x0c
[TRUNCATED]
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
      "callsite": "0x009817d6",
      "direction": "out",
      "other": "0x00951240",
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
    "global:PASS"
  ],
  "types": [
    "uint32_t",
    "void*"
  ],
  "vtables": [
    "vtable:0x009838e0",
    "vtable:0x01441a2c",
    "vtable:0x014447f8"
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
      "No original-process invocation and no indirect-caller trace was captured, so no concrete caller and no real key value are known. The key-to-offset table is proven from the two bodies but the values a real caller passes, and therefore which members these offsets name, cannot be observed without a trace.",
      "The member names and declared types behind offsets +0x00, +0x04 and +0x0c are not established; only the offsets themselves are proven.",
      "The owning C++ class name and the interface identity of the target's vtable slot are not established, because SporeApp.exe carries no MSVC RTTI.",
      "The provenance of the four comparison constants is not established, so it cannot be checked whether another translation unit contributes further keys to the same table that are unreachable from this entry point."
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
      "callsite": "0x009817d6",
      "direction": "out",
      "other": "0x00951240",
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
    "id": "scc-0327",
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
      "same_calling_convention"
    ],
    "package": "pkg-dfw-00980510",
    "score": 8,
    "symbol": "dfw_get_proxy_id_00980510",
    "va": "0x00980510"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "pkg-utfwin-slot7-wave12",
    "score": 8,
    "symbol": "re_00fc7e10_UTFWin_ImageDrawable_GetTiling",
    "va": "0x00fc7e10"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "pkg-utfwin-settiling-wave13",
    "score": 8,
    "symbol": "set_tiling_00fd9460",
    "va": "0x00fd9460"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "pkg-0095fa30-utfwin-isancestorof",
    "score": 6,
    "symbol": "is_ancestor_of_0095fa30",
    "va": "0x0095fa30"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "pkg-utfwin-func35-wave12",
    "score": 6,
    "symbol": "func35_0095fd60",
    "va": "0x0095fd60"
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
    "package": "pkg-dfw-00980c50",
    "score": 6,
    "symbol": "dfw_00980c50_func88h",
    "va": "0x00980c50"
  },
  {
    "match_basis": [
      "shared_types:void*",
      "same_calling_convention"
    ],
    "package": "PKG-APP-SAFE-WAVE11",
    "score": 5,
    "symbol": "property_record_assign_pair_004279d0",
    "va": "0x004279d0"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__ScrollbarDrawable__SetImage.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__ScrollbarDrawable__SetImage.c",
    "reconstruction/staging/pkg-utfwin-hash-offset-009817c0/.clang-format",
    "reconstruction/staging/pkg-utfwin-hash-offset-009817c0/utfwin_hash_offset_009817c0.cpp",
    "reconstruction/staging/pkg-utfwin-hash-offset-009817c0/utfwin_hash_offset_009817c0.hpp",
    "reconstruction/staging/pkg-utfwin-hash-offset-009817c0/utfwin_hash_offset_009817c0_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-dfw-009817c0/009817c0.json",
    "reconstruction/metadata/pkg-utfwin-hash-offset-009817c0/009817c0.json"
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
    "Are the two this-adjusting thunks 0x00969b40 and 0x00969b50 members of the same interface as this slot, and is the base class boundary at 0x009817c0 or 0x009817b0? The thunks' SUB ECX displacements match this body's two LEA displacements exactly, which is suggestive, but no slot index is claimed for either thunk's own table.",
    "Is the MOV dword ptr [ESP + 0x4], EAX at 0x009817d2 an artefact of the original build's tail-call lowering, or an explicit argument write in the source? It is a semantic no-op on the argument either way, so the model does not depend on the answer.",
    "Is the MOV dword ptr [ESP + 0x4],EAX at 0x009817d2 an artefact of the original build's tail-call lowering, or an explicit argument write in the source? It is a no-op on the value either way, and the test cannot observe it -- mutation M10 confirms that removing it leaves the test green. The model states it rather than assuming it away, and that limit is stated in the test as well.",
    "Is the base of the vtable containing 0x00951240 at 0x01445c10 identifiable, and does that table share an interface with the two tables that contain this target? Only the single pointer occurrence is established; no slot index is claimed for it.",
    "Is the base of the vtable containing 0x00951240 identifiable, and does it share an interface with the tables that contain this target? Only the single pointer occurrence is established; no slot index is claimed for it.",
    "No original-process invocation and no indirect-caller trace was captured, so no concrete 
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /decompile_function @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__ScrollbarDrawable__SetImage.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-dfw-009817c0/009817c0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-utfwin-hash-offset-009817c0/009817c0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-utfwin-hash-offset-009817c0/.clang-format', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-utfwin-hash-offset-009817c0/utfwin_hash_offset_009817c0.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-utfwin-hash-offset-009817c0/utfwin_hash_offset_009817c0.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-utfwin-hash-offset-009817c0/utfwin_hash_offset_009817c0_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "GhidraMCP REST /decompile_function @ http://127.0.0.1:8089",
      "source_class": "ghidra"
    },
    {
      "mode": "live",
      "ref": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
      "source_class": "ghidra"
    },
    {
      "mode": "persisted",
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__ScrollbarDrawable__SetImage.c",
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
      "ref": "reconstruction/metadata/pkg-dfw-009817c0/009817c0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg-utfwin-hash-offset-009817c0/009817c0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pk
[TRUNCATED]
```
