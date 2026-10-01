# Reconstruction context 0x007d9410

- Status: `complete`
- Content SHA-256: `04b4e76a6ae16f82e18268ae245c6d6d27b0321537d65114710a01df6f6b9f28`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x007d9410",
  "phase": "reconstruction",
  "target": "0x007d9410"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "App::cMouseCamera::OnKeyDown",
  "package": null,
  "subsystem": "App",
  "va": "0x007d9410"
}
```

## 03_current_status

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "blocked": false,
  "reconstructed": false,
  "runtime_gated": false,
  "runtime_validated": 0,
  "status": "queued"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "b1f792d20c11922aace3a8ba0b2bdf070d7d7df3b93efd01bfdf3aecc1492769",
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
/* WARNING: Enum "Names": Some values do not have unique names */

bool App__cMouseCamera__OnKeyDown(cMouseCamera *this,int virtualKey,KeyModifiers modifiers)

{
  bool bVar1;
  
  bVar1 = (bool)FUN_007d9bb0();
  return bVar1;
}


```

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_receiver": "ECX holds a pointer to the subobject that carries the OnKeyDown virtual; the entry rewinds it to the cMouseCamera start",
  "hidden_this": true,
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": 1,
  "receiver_register": "ECX",
  "ret_form": [
    "none in this body - the entry tail-jumps; the callee at 0x007d9bb0 ends with `POP ESI` / `RET 0x4`",
    "none in this body (tail transfer)"
  ],
  "return_note": "unclassified in this model; the persisted record and the SDK/Ghidra prototype both say bool at the declaration site",
  "return_register": [
    "EAX",
    "EAX per the persisted ABI record; the derived record names none (return.register null, register_class unknown, confidence UNKNOWN)"
  ],
  "return_type": "bool",
  "saved_registers": [],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "the tail target: the body pushes nothing and pops nothing, and the persisted record describes 0x007d9bb0 as ending in POP ESI / RET 0x4, which is what drops the caller's one word and returns to this body's caller",
  "termination": "JMP 0x007d9bb0 at 0x007d9413"
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
      "callsite": "0x007d9413",
      "direction": "out",
      "other": "0x007d9bb0",
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
    "global:PASS",
    "global:none: the complete two-instruction listing names no data-segment address"
  ],
  "types": [
    "DATA",
    "bool",
    "unclassified in this model; the persisted record and the SDK/Ghidra prototype both say bool at the declaration site",
    "unclassified_in_EAX (a std::uint32_t alias)"
  ],
  "vtables": [
    "vtable:0x007d93a0",
    "vtable:0x01412890",
    "vtable:0x01412894"
  ]
}
```

## 09_state_event_relationships

- State: `missing`
- Provenance: `knowledgegraph/research/semantic-decomp.json, reconstruction/knowledge/index.json`

```json
{
  "runtime": {
    "blocking_reason": null,
    "gates": [],
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
      "callsite": "0x007d9413",
      "direction": "out",
      "other": "0x007d9bb0",
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
    "id": "scc-0248",
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
      "shared_types:DATA"
    ],
    "package": "pkg-app-imessage-manager-dtor",
    "score": 9,
    "symbol": "get_0067dc80",
    "va": "0x0067dc80"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "pkg-cheat-func3ch-0067e6b0",
    "score": 8,
    "symbol": "func3_ch_0067e6b0",
    "va": "0x0067e6b0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "pkg-cheat-dispatch-0067e6f0",
    "score": 8,
    "symbol": "cCheatManager_func40h_0067e6f0",
    "va": "0x0067e6f0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "cheat-func44h-0067e730",
    "score": 8,
    "symbol": "func44h_0067e730",
    "va": "0x0067e730"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "pkg-app-proplist-copyall-wave16",
    "score": 8,
    "symbol": "all_copy_from_properties_006a14d0",
    "va": "0x006a14d0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "pkg-proplist-dispatch-wave14",
    "score": 8,
    "symbol": "app_property_list_add_all_properties_from_006a1510",
    "va": "0x006a1510"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "pkg-dfw-006a1540",
    "score": 8,
    "symbol": "proplist_write_006a1540",
    "va": "0x006a1540"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__cMouseCamera__OnKeyDown.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__cMouseCamera__OnKeyDown.c",
    "reconstruction/staging/pkg-app-mouse-camera-keydown/mouse_camera_on_key_down_007d9410.cpp",
    "reconstruction/staging/pkg-app-mouse-camera-keydown/mouse_camera_on_key_down_007d9410.hpp",
    "reconstruction/staging/pkg-app-mouse-camera-keydown/mouse_camera_on_key_down_007d9410_model_test.cpp",
    "reconstruction/staging/pkg-dfw-007d9410/dfw_007d9410.cpp",
    "reconstruction/staging/pkg-dfw-007d9410/dfw_007d9410_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-app-mouse-camera-keydown/007d9410.json",
    "reconstruction/metadata/pkg-dfw-007d9410/007d9410.json"
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
    "Ordinary-argument arity and identity. The SDK/Ghidra prototype stored on this symbol declares two four-byte stack slots, (int virtualKey, KeyModifiers modifiers), while the machine shows one word being dropped by the tail target's RET 0x4. The model implements the single machine-observed word and types it as an opaque Word. Whether a preceding virtualKey argument exists in the original source and is simply unconsumed, and which declared parameter this word is, is not established by anything in this pack.",
    "Ordinary-argument arity conflict: the SDK/Ghidra prototype stored on this symbol declares (int virtualKey, KeyModifiers modifiers) - two four-byte stack slots - but the callee reached through the tail jump ends in `RET 0x4` and reads only [ESP+0x4]. The model implements the machine-observed single argument and names it after the SDK parameter that bit 0 is tested against. Whether a preceding virtualKey argument exists in the original source and is simply unconsumed is unresolved.",
    "The class and interface identities behind the three associated vtable words 0x007d93a0, 0x01412890 and 0x01412894, and the meaning of the single data-segment xref at 0x01412894. The binary carries no MSVC RTTI and the word at 0x014128a8 is not a code address in this image.",
    "The class names and interface identities behind the three vtable pointers at +0x00, +0x04 and +0x08; the binary carries no MSVC RTTI and the word at 0x014128a8 is not a code address in this image.",
    "The concrete routines behind the IAT words 0x013cc2d
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /decompile_function @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/App__cMouseCamera__OnKeyDown.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-app-mouse-camera-keydown/007d9410.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-dfw-007d9410/007d9410.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-app-mouse-camera-keydown/mouse_camera_on_key_down_007d9410.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-app-mouse-camera-keydown/mouse_camera_on_key_down_007d9410.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-app-mouse-camera-keydown/mouse_camera_on_key_down_007d9410_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-dfw-007d9410/dfw_007d9410.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-dfw-007d9410/dfw_007d9410_types.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/App__cMouseCamera__OnKeyDown.c",
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
      "ref": "reconstruction/metadata/pkg-app-mouse-camera-keydown/007d9410.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg-dfw-007d9410/007d9410.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-app-mous
[TRUNCATED]
```
