# Reconstruction context 0x00a649a0

- Status: `partial`
- Content SHA-256: `c0c5f23f9c24216eef19bb111bfae8869851dc0bfbdfb6549ff7eb843ebd1b4d`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00a649a0",
  "phase": "reconstruction",
  "target": "0x00a649a0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00a649a0",
  "package": "pkg-swarm-w1-00a649a0",
  "subsystem": "Sporepedia",
  "va": "0x00a649a0"
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
  "content_sha256": "a7b42ecb593cd56ff7fe5374debd6d93d061b6ee46d94839df450da4cd9d8ae6",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00a649a0 failed: Decompilation did not complete. Reason: ",
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
  "ordinary_stack_argument_slots": 0,
  "receiver_register": "ECX",
  "ret_form": "RET (C3, bare)",
  "return_register": "EAX",
  "return_type": "Word",
  "saved_registers": [],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "callee owns nothing; nominally the caller, and 0 bytes either way",
  "termination": "RET (C3, bare)"
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
      "va": "0x00a53d20"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00a53da5",
      "direction": "in",
      "other": "0x00a53d20",
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
    "Word",
    "std::uint32_t (Word)"
  ],
  "vtables": [
    "vtable:0x013ff648",
    "vtable:0x013ff6ac",
    "vtable:0x01462764",
    "vtable:0x014627bc",
    "vtable:0x0147c9e8",
    "vtable:0x0147ca30",
    "vtable:0x0147ca70",
    "vtable:0x0147caf8",
    "vtable:0x0147cbbc",
    "vtable:0x0147cc14",
    "vtable:0x01489090",
    "vtable:0x014890f4"
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
      "va": "0x00a53d20"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00a53da5",
      "direction": "in",
      "other": "0x00a53d20",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 1,
  "fan_out": 0,
  "manifest_callees": [],
  "manifest_callers": [],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0332",
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
      "shared_types:Word",
      "shared_vtable:vtable:0x013ff648,vtable:0x01462764",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-006413d0",
    "score": 15,
    "symbol": "re_006413d0",
    "va": "0x006413d0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_types:Word",
      "shared_vtable:vtable:0x013ff648,vtable:0x01462764",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-00641780",
    "score": 15,
    "symbol": "re_00641780",
    "va": "0x00641780"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_types:Word",
      "shared_vtable:vtable:0x013ff648,vtable:0x013ff6ac",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w2-00642700",
    "score": 15,
    "symbol": "sporepedia_append_five_lookups_00642700",
    "va": "0x00642700"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_types:Word",
      "shared_vtable:vtable:0x0147ca30,vtable:0x0147ca70",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-00dd0550",
    "score": 15,
    "symbol": "re_00dd0550",
    "va": "0x00dd0550"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013ff648,vtable:0x013ff6ac",
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
    "packa
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-swarm-w1-00a649a0/sw1_00a649a0.cpp",
    "reconstruction/staging/pkg-swarm-w1-00a649a0/sw1_00a649a0_model_test.cpp",
    "reconstruction/staging/pkg-swarm-w1-00a649a0/sw1_00a649a0_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-swarm-w1-00a649a0/00a649a0.json"
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
    "The class hierarchy this accessor belongs to. 0x005c0dd0 sits in the same vtable run 0x00a5 bytes away and appears in the same residual-unknown row, but no reconstruction package for it exists yet, so the shared receiver layout is unconfirmed from the other side.",
    "The vtable slot number, and therefore what a caller of this slot is asking for. The entry sits 0x88 = 34 dwords past the head at 0x013ff648, but whether that head dword is slot 0 is the convention this target does not settle, so the package declares no slot. Resolving it needs the RTTI complete-object-locator question settled for the Sporepedia vtable family first.",
    "What the 4-byte word at receiver+0x6c is. The body, the seven verified vtable installations and the single caller give no name, no type and no nullability, and abi_derived's `pointer_like_in_EAX` is an INFERRED register class rather than a type -- recorded on its own in observed_original_abi.machine_return_class and deliberately kept out of observed_original_abi.return_type, since a register-class phrase is not a C or C++ type and no name in this package is derived from it. Whether the value really is pointer-like is itself open: nothing in these 4 bytes ever dereferences it, and the one caller stores it as an ordinary integer word. docs/analysis/residual-unknown-priority.md groups 0x00a649a0 with 0x005507a0, 0x005508c0, 0x005c0dd0 and 0x00ff3f00 as 'Local asset field projection' and says the open task is to bind one receiver field to a fixture-backed local metadata contract. Settling th
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-swarm-w1-00a649a0/00a649a0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w1-00a649a0/sw1_00a649a0.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w1-00a649a0/sw1_00a649a0_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w1-00a649a0/sw1_00a649a0_types.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-swarm-w1-00a649a0/00a649a0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w1-00a649a0/sw1_00a649a0.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w1-00a649a0/sw1_00a649a0_model_test.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w1-00a649a0/sw1_00a649a0_types.hpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.js
[TRUNCATED]
```
