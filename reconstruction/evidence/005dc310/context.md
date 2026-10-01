# Reconstruction context 0x005dc310

- Status: `partial`
- Content SHA-256: `8cccc66c3c98c22d5227d0c58c137c48df22f82534c5d588677efce124f2f032`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x005dc310",
  "phase": "reconstruction",
  "target": "0x005dc310"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": null,
  "package": null,
  "subsystem": null,
  "va": "0x005dc310"
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
  "status": "unresolved"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "5969882cb396c3adae2aafd53ff855e315911d5fb2e53757202bf776b8edea3f",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x005dc310 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "__thiscall",
  "hidden_receiver": "ECX, copied to ESI at 0x005dc316 and never reloaded",
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": 1,
  "receiver": true,
  "ret_form": "RET 0x4",
  "return_note": "(a pointer, in EAX); Opaque5dc310Window*; void*",
  "return_observation": "0x005dc323 TEST EAX,EAX and 0x005dc325 JNZ read the first call's EAX; when the branch is not taken the second call at 0x005dc32d leaves its own answer in EAX. Neither POP EDI (0x005dc332) nor POP ESI (0x005dc333) touches EAX, and the epilogue is only those two pops plus RET. The Ghidra decompilation types this function 'void' and drops the result entirely; that typing is a decompiler miss, contradicted by every inspected caller.",
  "return_register": "EAX",
  "return_semantics": "the EAX produced by the last 0x008105b0 call that executed: the +0x14 sub-object's answer when it was non-null, otherwise the +0x2c sub-object's answer (which may itself be null)",
  "return_width_bytes": 4,
  "saved_registers": [
    "EDI",
    "ESI"
  ],
  "stack_arguments": [
    "{'entry_offset': 'ESP+4', 'name': 'lookup_key', 'type': 'uint32_t', 'width_bytes': 4}",
    "{'offset_in_callee': '[ESP + 0xc] before the two pushes', 'read_by': '0x005dc312: MOV EDI,dword ptr [ESP + 0xc]', 'role': 'the control id, forwarded to both 0x008105b0 calls', 'slot': 1, 'width_bytes': 4}"
  ],
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "callee",
  "termination": "RET 0x4"
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
      "name": "Editors::cEditor::Update",
      "reconstructed": false,
      "va": "0x0058be50"
    },
    {
      "name": "Editors::cEditor::HandleMessage",
      "reconstructed": false,
      "va": "0x00591fa0"
    },
    {
      "name": "FUN_005dda30",
      "reconstructed": true,
      "va": "0x005dda30"
    },
    {
      "name": "editor_query_dispatch_005dfd00",
      "reconstructed": true,
      "va": "0x005dfd00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00634e40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00634f20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00635010"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00635160"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00635390"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00635400"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006354c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00635520"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00635580"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00635600"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00635680"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00635790"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x0058c7e3",
      "direc
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "EditorUI*",
    "Opaque void* for the lookup result; no concrete target owner or ownership contract is asserted",
    "Opaque5dc310Window* (a pointer, in EAX)",
    "OpaqueEditorModeManager for ECX",
    "pointer (nullable)",
    "pointer one past the last array element",
    "pointer to the first array element",
    "sub-object address (opaque)",
    "uint32_t",
    "uint32_t for the lookup key",
    "void*"
  ],
  "vtables": []
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
      "A runtime differential test is required to resolve vtable slots +0x0c, +0x1c and +0xf0 on a live editor element, and to confirm that the +0x14 candidate really does shadow the +0x2c candidate in the shipping build.",
      "No original-process trace exists for 0x005dc310; every claim is static and the Cell stage has never been entered in any recorded run.",
      "The SDK's UILayoutObjects offsets must be re-derived before the +0x64/+0x68 scan bounds can be attributed to a named member.",
      "Whether the +0x2c fallback is ever load-bearing cannot be settled statically; only a run with the main layout empty would show it."
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
      "name": "Editors::cEditor::Update",
      "reconstructed": false,
      "va": "0x0058be50"
    },
    {
      "name": "Editors::cEditor::HandleMessage",
      "reconstructed": false,
      "va": "0x00591fa0"
    },
    {
      "name": "FUN_005dda30",
      "reconstructed": true,
      "va": "0x005dda30"
    },
    {
      "name": "editor_query_dispatch_005dfd00",
      "reconstructed": true,
      "va": "0x005dfd00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00634e40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00634f20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00635010"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00635160"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00635390"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00635400"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006354c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00635520"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00635580"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00635600"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00635680"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00635790"
    },
    {
      "name": null,
      "reconstr
[TRUNCATED]
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "shared_types:void*",
      "same_calling_convention"
    ],
    "package": "PKG-APP-SAFE-WAVE11",
    "score": 5,
    "symbol": "property_record_assign_pair_004279d0",
    "va": "0x004279d0"
  },
  {
    "match_basis": [
      "shared_types:void*",
      "same_calling_convention"
    ],
    "package": "PKG-PALETTE-SAFE-WAVE11",
    "score": 5,
    "symbol": "palette_safe_wave11_fill_node_array_005c7ff0",
    "va": "0x005c7ff0"
  },
  {
    "match_basis": [
      "same_calling_convention",
      "direct_xref_neighbor"
    ],
    "package": "PKG-10-EDITOR-DISPATCH",
    "score": 5,
    "symbol": "FUN_005dda30",
    "va": "0x005dda30"
  },
  {
    "match_basis": [
      "shared_types:void*",
      "same_calling_convention"
    ],
    "package": "PKG-APP-SERVICES-SAFE-WAVE11",
    "score": 5,
    "symbol": "service_005fa8d0",
    "va": "0x005fa8d0"
  },
  {
    "match_basis": [
      "shared_types:void*",
      "same_calling_convention"
    ],
    "package": "PKG-APP-SERVICES-SAFE-WAVE11",
    "score": 5,
    "symbol": "service_0060ee90",
    "va": "0x0060ee90"
  },
  {
    "match_basis": [
      "shared_types:void*",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-00641fd0",
    "score": 5,
    "symbol": "sporepedia_cached_handle_00641fd0",
    "va": "0x00641fd0"
  },
  {
    "match_basis": [
      "shared_types:void*",
      "same_calling_convention"
    ],
    "package": "pkg-vft-slot-006e64f0",
    "score": 5,
    "symbol": "re_006e64f0",
    "va": "0x006e64f0"
  },
  {
    "match_basis": [
      "shared_types:void*",
  
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/wave13-w1-dispatch-b00/editor_ui_005dc310.cpp",
    "reconstruction/staging/wave13-w1-dispatch-b00/editor_ui_005dc310.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg10-editor-dispatch/005dc310.json",
    "reconstruction/metadata/wave13-w1-dispatch-b00/005dc310.json"
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
    "A runtime differential test is required to resolve vtable slots +0x0c, +0x1c and +0xf0 on a live editor element, and to confirm that the +0x14 candidate really does shadow the +0x2c candidate in the shipping build.",
    "Are the two internal subobjects at this+0x14 and this+0x2c distinct registries or alternate lookup paths?",
    "Is 0x005dc310 itself an interface method or a vtable entry? No vtable was located for the EditorUI aggregate and no pointer scan for this address was performed.",
    "Is slot +0xf0 a recursive descent into children, or a lookup in a sibling container? Its (id, 1) shape is consistent with both.",
    "Is the flag argument ever 0 for this function? Both call sites here hard-code 1, and all 25 recorded callers route through those two sites, so the non-recursive path may be dead in this build. Not proven, because 0x008105b0 has other callers that were not enumerated.",
    "No original-process trace exists for 0x005dc310; every claim is static and the Cell stage has never been entered in any recorded run.",
    "The SDK's UILayoutObjects offsets must be re-derived before the +0x64/+0x68 scan bounds can be attributed to a named member.",
    "The element array scanned by 0x00810200 lives at +0x64..+0x68 of the layout-objects target, but the SDK declares UILayoutObjects::mRootComponents at +0x5c. Either the SDK offsets for that class are wrong, or the scanned array is a different member. Not reconciled.",
    "The other 14 of the 25 callers were not inspected, so the argument distribution across t
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg10-editor-dispatch/005dc310.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-w1-dispatch-b00/005dc310.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b00/editor_ui_005dc310.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b00/editor_ui_005dc310.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg10-editor-dispatch/005dc310.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/wave13-w1-dispatch-b00/005dc310.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b00/editor_ui_005dc310.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b00/editor_ui_005dc310.hpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.json"

[TRUNCATED]
```
