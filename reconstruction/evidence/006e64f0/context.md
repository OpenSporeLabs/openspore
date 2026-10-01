# Reconstruction context 0x006e64f0

- Status: `partial`
- Content SHA-256: `cf8d6c28192f4d67317cb54c0c2c77e3144b9453bc197846efac3eb06cbe75ee`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x006e64f0",
  "phase": "reconstruction",
  "target": "0x006e64f0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_006e64f0",
  "package": "pkg-vft-slot-006e64f0",
  "subsystem": "Sporepedia",
  "va": "0x006e64f0"
}
```

## 03_current_status

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "blocked": false,
  "reconstructed": true,
  "runtime_gated": false,
  "runtime_validated": 0,
  "status": "reconstructed"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "df3d1289e8d7353a1613d9f5bbdfbf4c032ce5dd9066ac9bc834005386fc4d14",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x006e64f0 failed: Decompilation did not complete. Reason: ",
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
  "ordinary_stack_argument_slots": 0,
  "receiver_register": "ECX",
  "ret_form": "RET (bare, no immediate)",
  "return_register": "EAX",
  "return_semantics": "one 32-bit word in EAX, value receiver + 0x4; the engine's own classification is unclassified_in_EAX with void_possible, and the width route of the return-evidence module measures WIDTH_4_IN_EAX over the complete listing",
  "saved_registers": [],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "RET"
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
      "va": "0x008edd50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x008edd80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x008ee740"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x008ee770"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x008ef900"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b94420"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b94670"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b9bed0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c932a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00f4c300"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x008edd50",
      "direction": "in",
      "other": "0x008edd50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x008edd80",
      "direction": "in",
      "other": "0x008edd80",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x008ee743",
      "direction": "in",
      "other": "0x008ee740",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x008ee773",
      "direction": "in",
      "other": "0x008ee770",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x008ef917",
      "direction": "in",
      "other": "0x008ef900",
      "reference_type": "
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "void*"
  ],
  "vtables": [
    "vtable:0x013fae9c",
    "vtable:0x013faea0",
    "vtable:0x013ff648",
    "vtable:0x0140e09c",
    "vtable:0x01419f80",
    "vtable:0x0143e7d8",
    "vtable:0x0144269c",
    "vtable:0x01444434",
    "vtable:0x0145a5d8",
    "vtable:0x0145c4f0",
    "vtable:0x0145eb60",
    "vtable:0x01462764"
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
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x008edd50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x008edd80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x008ee740"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x008ee770"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x008ef900"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b94420"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b94670"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b9bed0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c932a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00f4c300"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x008edd50",
      "direction": "in",
      "other": "0x008edd50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x008edd80",
      "direction": "in",
      "other": "0x008edd80",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x008ee743",
      "direction": "in",
      "other": "0x008ee740",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x008ee773",
      "direction": "in",
      "other": "0x008ee770",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x008ef
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
      "shared_types:void*",
      "shared_vtable:vtable:0x013ff648,vtable:0x01462764",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-00641fd0",
    "score": 15,
    "symbol": "sporepedia_cached_handle_00641fd0",
    "va": "0x00641fd0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_types:void*",
      "shared_vtable:vtable:0x013ff648,vtable:0x01462764"
    ],
    "package": "pkg-00b7e380-member-ptr-0x2c",
    "score": 13,
    "symbol": "member_ptr_0x2c_00b7e380",
    "va": "0x00b7e380"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013ff648,vtable:0x0147c9e8",
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
      "shared_vtable:vtable:0x013ff648,vtable:0x01462764",
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
      "shared_vtable:vtable:0x013ff648,vtable:0x01462764",
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
      "shared_vtable:vtable:0x013ff648,vtable:0x01462764",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-00641780",
    "score": 12,
    "symbol": "re_006417
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-vft-slot-006e64f0/pkg_vft_slot_006e64f0.cpp",
    "reconstruction/staging/pkg-vft-slot-006e64f0/pkg_vft_slot_006e64f0_model_test.cpp",
    "reconstruction/staging/pkg-vft-slot-006e64f0/pkg_vft_slot_006e64f0_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-vft-slot-006e64f0/006e64f0.json"
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
    "The extent of the vftable images. Only the first table's sixteen words were read; the other 65 memberships are counted, not transcribed.",
    "The receiver's class. V1-VFT proves the function is a virtual member of some class; with no MSVC RTTI in this binary and a bounds_only receiver record, no class name and no layout are claimed.",
    "What the returned address denotes. The body computes receiver + 0x4 and returns it; whether that address is a member, a byte past the vptr, or something else is not established by two instructions that never dereference it."
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-vft-slot-006e64f0/006e64f0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-vft-slot-006e64f0/pkg_vft_slot_006e64f0.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-vft-slot-006e64f0/pkg_vft_slot_006e64f0_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-vft-slot-006e64f0/pkg_vft_slot_006e64f0_types.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-vft-slot-006e64f0/006e64f0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-vft-slot-006e64f0/pkg_vft_slot_006e64f0.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-vft-slot-006e64f0/pkg_vft_slot_006e64f0_model_test.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-vft-slot-006e64f0/pkg_vft_slot_006e64f0_types.hpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "recons
[TRUNCATED]
```
