# Reconstruction context 0x00ecc620

- Status: `partial`
- Content SHA-256: `16d6d47237009cb34757232c6bc21f19ee829cbbf104a36bf5fcb97d19dca284`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00ecc620",
  "phase": "reconstruction",
  "target": "0x00ecc620"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00ecc620",
  "package": null,
  "subsystem": "Sporepedia",
  "va": "0x00ecc620"
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
  "status": "candidate"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "800580ad1c52a0e028a45e3d8116d6cd501de0b1231e4d760dfe3ae4741eda05",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00ecc620 failed: Decompilation did not complete. Reason: ",
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
  "ordinary_stack_argument_slots": 1,
  "receiver_register": "ECX",
  "ret_form": "RET 0x4",
  "return_note": "(the receiver)",
  "return_register": "EAX",
  "return_type": "OpaqueSporepediaAssetData*",
  "saved_registers": [
    "ESI"
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
  "callees": [
    {
      "name": "sporepedia_asset_destroy_00642190",
      "reconstructed": true,
      "va": "0x00642190"
    }
  ],
  "callers": [],
  "edge_rows": [
    {
      "callsite": "0x00ecc65c",
      "direction": "out",
      "other": "0x00642190",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00ecc652",
      "direction": "out",
      "other": "0x00f47380",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00ecc669",
      "direction": "out",
      "other": "0x00f47380",
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
    "OpaqueSporepediaAssetData* (the receiver)",
    "OpaqueSporepediaAssetData* (the receiver). Machine fact, not convention: 0x00ecc671 MOV EAX,ESI executes on BOTH arms -- it sits after the 0x00ecc666 join, reached by falling through the 0x00f47380 call or by the branch -- and ESI is the receiver alias from 0x00ecc621 which is never reassigned. The derived ABI record classifies that EAX as unclassified_in_EAX with type null, which is a statement about its classifier and not about the listing."
  ],
  "vtables": [
    "vtable:0x014893b0"
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
  "callees": [
    {
      "name": "sporepedia_asset_destroy_00642190",
      "reconstructed": true,
      "va": "0x00642190"
    }
  ],
  "callees_truncated": false,
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00ecc65c",
      "direction": "out",
      "other": "0x00642190",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00ecc652",
      "direction": "out",
      "other": "0x00f47380",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00ecc669",
      "direction": "out",
      "other": "0x00f47380",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 0,
  "fan_out": 1,
  "manifest_callees": [],
  "manifest_callers": [],
  "nearby_reconstructed": [
    "0x00642190"
  ],
  "scc": {
    "id": "scc-0567",
    "size": 1
  },
  "vtable_reference_count": 3
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
      "shared_vtable:vtable:0x014893b0",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-005c0dd0",
    "score": 12,
    "symbol": "re_005c0dd0",
    "va": "0x005c0dd0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x014893b0",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-006413d0",
    "score": 12,
    "symbol": "re_006413d0",
    "va": "0x006413d0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x014893b0",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-00641410",
    "score": 12,
    "symbol": "re_00641410",
    "va": "0x00641410"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x014893b0",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-00641780",
    "score": 12,
    "symbol": "re_00641780",
    "va": "0x00641780"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x014893b0",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-006417d0",
    "score": 12,
    "symbol": "re_006417d0",
    "va": "0x006417d0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x014893b0",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-00641fa0",
    "score": 12,
    "symbol": "sporepedia_predicate_00641fa0",
    "va": "0x00641fa0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x014893b0",
      "same_calling_convention"

[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-swarm-w1-00ecc620/sw1_00ecc620.cpp",
    "reconstruction/staging/pkg-swarm-w1-00ecc620/sw1_00ecc620_model_test.cpp",
    "reconstruction/staging/pkg-swarm-w1-00ecc620/sw1_00ecc620_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-swarm-w1-00ecc620/00ecc620.json"
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
    "RUNTIME is GATED at 0. No original-process trace exists in this repository for this VA, nothing was attempted, and nothing failed.",
    "The class name is CORROBORATED but one indirection away: the string 'Sporepedia/AssetData/cSPScenarioCaptainAssetData' at 0x01489468 is passed to the allocator by the factory 0x00ecc7d0, which constructs with 0x00ecc780, which installs the three dispatch constants this body also installs. This VA's own records carry ghidra_name FUN_00ecc620 and sdk_name null, and the SDK-to-Ghidra import named nothing at this address, so the name is recorded here and deliberately not used in the signature.",
    "The two adjust-and-jump thunks adjust ECX by 0x10 and 0x14 DOWNWARDS, which fixes that the subobjects owning those vftables sit 0x10 and 0x14 bytes below the complete-object pointer that reached the thunk. The bases those two subobjects belong to are not identified here, and nothing in this body depends on them.",
    "There are no callers recorded for this VA (briefing.callers is empty and ghidra_function.callers is empty), so the frequencies with which the deleting form and the non-deleting form are actually used are unknown. The body handles both, and the model test drives both, but no evidence says which is the common case.",
    "What the two words at receiver+0x80 and +0x88 actually are. The body only subtracts and masks them, and this package therefore claims nothing about their type beyond being 32-bit words at those two displacements. Three facts constrain but do not settle it: the co
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-swarm-w1-00ecc620/00ecc620.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w1-00ecc620/sw1_00ecc620.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w1-00ecc620/sw1_00ecc620_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w1-00ecc620/sw1_00ecc620_types.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-swarm-w1-00ecc620/00ecc620.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w1-00ecc620/sw1_00ecc620.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w1-00ecc620/sw1_00ecc620_model_test.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w1-00ecc620/sw1_00ecc620_types.hpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.js
[TRUNCATED]
```
