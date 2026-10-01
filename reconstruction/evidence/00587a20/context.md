# Reconstruction context 0x00587a20

- Status: `partial`
- Content SHA-256: `5688b24a4416d05306712fc54cd2bc5ea04b93b51144c080923257a8c0b7d772`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00587a20",
  "phase": "reconstruction",
  "target": "0x00587a20"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "Editors::cEditor::OnExit",
  "package": null,
  "subsystem": "Editor",
  "va": "0x00587a20"
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
  "content_sha256": "0374bc8f05f05ad95dc661e7410508ec79daaeff1886114dd7489843dfffdbb0",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00587a20 failed: Decompilation did not complete. Reason: ",
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
  "hidden_this": true,
  "hidden_this_register": "ECX",
  "receiver": true,
  "receiver_register": "ECX",
  "ret_form": "RET",
  "return_observation": "Ghidra resolves return_type void (analyze_function_complete, ghidra_function.return_type_resolved true). The derived openspore-abi-inference-1 record for this target abstained (conventions.confidence UNKNOWN, calling_convention null, candidate_conventions __cdecl) and its return claim is contradicted by the balanced FLD/FSTP pair; see conflicts_and_disagreements.",
  "return_semantics": "void. The epilogue is POP ESI ; POP EBP ; POP EBX ; ADD ESP,0x44 ; RET: a bare RET with no immediate, and no instruction after the last call reads a return register. The x87 pair at 0x00587b10 (FLD float ptr [ESI+0x4d0]) and 0x00587b1b (FSTP float ptr [ESP]) is balanced -- FSTP pops what FLD pushed -- so nothing is left on the x87 stack, and the value is a 4-byte stack argument, not a result. This DISAGREES with the derived ABI record for this target, which reports return_register ST0 and return_semantics float_or_x87_in_ST0; that reading is a false positive of the linear-sweep inference, p...",
  "return_type": "void",
  "saved_registers": [
    "EBP",
    "EBX",
    "EDI",
    "ESI"
  ],
  "stack_arguments": [],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": [
    "RET at 0x0058856a, bare, no immediate",
    "RET"
  ]
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004ad330"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00573c00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00573d70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005772b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00587270"
    },
    {
      "name": "release_child_0062c910",
      "reconstructed": true,
      "va": "0x0062c910"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0067dcc0"
    }
  ],
  "callers": [],
  "edge_rows": [
    {
      "callsite": "0x00587ef6",
      "direction": "out",
      "other": "0x00401020",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00587f12",
      "direction": "out",
      "other": "0x00401020",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00587de0",
      "direction": "out",
      "other": "0x00401050",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0058855f",
      "direction": "out",
      "other": "0x00421cf0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00587d13",
      "direction": "out",
      "other": "0x0043a9a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00588028",
      "direction": "out",
      "other": "0x004581d0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00587de7",
      "direction": "out",
      "other": "0x
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "Byte",
    "Dword",
    "HIGH",
    "LocalAppState",
    "U64",
    "float",
    "void",
    "void*"
  ],
  "vtables": [
    "vtable:0x013f57f8"
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
      "runtime validation not run: no positive hash-pinned original-process trace reaches 0x00587a20 in the committed corpus"
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
  "callees": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004ad330"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00573c00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00573d70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005772b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00587270"
    },
    {
      "name": "release_child_0062c910",
      "reconstructed": true,
      "va": "0x0062c910"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0067dcc0"
    }
  ],
  "callees_truncated": false,
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00587ef6",
      "direction": "out",
      "other": "0x00401020",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00587f12",
      "direction": "out",
      "other": "0x00401020",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00587de0",
      "direction": "out",
      "other": "0x00401050",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0058855f",
      "direction": "out",
      "other": "0x00421cf0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00587d13",
      "direction": "out",
      "other": "0x0043a9a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00588028",
      "direction": "out",
      "other": "0x004581d0",
      "reference_type": "direct-call"
    
[TRUNCATED]
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013f57f8",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w2-00586700",
    "score": 12,
    "symbol": "re_00586700",
    "va": "0x00586700"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013f57f8",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-005b2490",
    "score": 12,
    "symbol": "re_005b2490",
    "va": "0x005b2490"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013f57f8",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-005ba0d0",
    "score": 12,
    "symbol": "re_005ba0d0",
    "va": "0x005ba0d0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013f57f8"
    ],
    "package": "pkg-editor-child-007f30d0",
    "score": 10,
    "symbol": "FUN_007f30d0",
    "va": "0x007f30d0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "pkg-vft-preinc-0051e340",
    "score": 8,
    "symbol": "vft_preinc_0051e340",
    "va": "0x0051e340"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "subobject-forward-0051e380",
    "score": 8,
    "symbol": "subobject_forward_0051e380",
    "va": "0x0051e380"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-00a85070",
    "score": 8,
    "symbol": "re_00a85070",
    "va": "0x00a85070"
  },
  {
    "match_basis"
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditor__OnExit.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditor__OnExit.c",
    "reconstruction/staging/pkg-dogfood-00587a20-a1/editor_onexit_00587a20.cpp",
    "reconstruction/staging/pkg-dogfood-00587a20-a1/editor_onexit_00587a20.hpp",
    "reconstruction/staging/pkg-editor-onexit-smoke01/editor_onexit_00587a20.cpp",
    "reconstruction/staging/pkg-editor-onexit-smoke01/editor_onexit_00587a20.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-dogfood-00587a20-a1/00587a20.json",
    "reconstruction/metadata/pkg-editor-onexit-smoke01/00587a20.json"
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
  "original_bytes": 10568,
  "preview": "{\n  \"conflicts\": [\n    {\n      \"anchors\": [\n        \"0x005737d0\",\n        \"0x00588570\",\n        \"0x0058ac10\",\n        \"0x00b3d350\",\n        \"0x00e818f0\",\n        \"0x00b3d350\",\n        \"0x00e818f0\",\n        \"0x00b3d350\",\n        \"0x005737d0\",\n        \"0x00576c50\",\n        \"0x00576c50\",\n        \"0x0057ce80\",\n        \"0x0057ce80\",\n        \"0x00584300\",\n        \"0x00584300\",\n        \"0x00587a20\"\n      ],\n      \"conflict_id\": \"editor_input_routing\",\n      \"kind\": \"conflict_ledger\",\n      \"rejected\": [],\n      \"resolution\": \"The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.\",\n      \"resolution_status\": \"The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.\",\n      \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n      \"subject\": null,\n      \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n    },\n    {\n      \"anchors\": [\n        \"0x005737d0\",\n        \"0x005737d0\",\n        \"0x00576c50\",\n        \"0x00576c50\",\n        \"0x0057ce80\",\n        \"0x0057ce80\",\n        \"0x00584300\",\n        \"0x00584300\",\n        \"0x00587270\",\n        \"0x00587270\",\n        \"0x00587a20\",\n        \"0x00587a20\",\n        \"0x00588570\",\n        \"0x00588570\",\n        \"0x0058ac10\",\n        \"0x0058ac10\"\n      ],\n      \"confl
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditor__OnExit.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-dogfood-00587a20-a1/00587a20.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-editor-onexit-smoke01/00587a20.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-dogfood-00587a20-a1/editor_onexit_00587a20.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-dogfood-00587a20-a1/editor_onexit_00587a20.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-editor-onexit-smoke01/editor_onexit_00587a20.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-editor-onexit-smoke01/editor_onexit_00587a20.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditor__OnExit.c",
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
      "ref": "reconstruction/metadata/pkg-dogfood-00587a20-a1/00587a20.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg-editor-onexit-smoke01/00587a20.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-dogfood-00587a20-a1/editor_onexit_00587a20.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "rec
[TRUNCATED]
```
