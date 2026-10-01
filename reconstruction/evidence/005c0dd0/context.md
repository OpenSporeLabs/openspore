# Reconstruction context 0x005c0dd0

- Status: `partial`
- Content SHA-256: `14ce691684f75997a32c6f4486335c8b57b09be074df50974ec6d8f6b7e3e9e8`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x005c0dd0",
  "phase": "reconstruction",
  "target": "0x005c0dd0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_005c0dd0",
  "package": "pkg-swarm-w1-005c0dd0",
  "subsystem": "Sporepedia",
  "va": "0x005c0dd0"
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
  "content_sha256": "4a3bf26efc06859f4cd982d6cbcf446e1c4a2c7be82a213d5bd33fb764190641",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x005c0dd0 failed: Decompilation did not complete. Reason: ",
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
  "ret_form": "RET",
  "return_note": "1 byte, delivered in AL",
  "return_register": "EAX",
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
      "va": "0x00adfd60"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00de5260"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00adfeaa",
      "direction": "in",
      "other": "0x00adfd60",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00de5273",
      "direction": "in",
      "other": "0x00de5260",
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
    "global:none. Neither instruction has an absolute operand."
  ],
  "types": [
    "1 byte, delivered in AL",
    "std::uint8_t"
  ],
  "vtables": [
    "vtable:0x013f7cc0",
    "vtable:0x013f7de0",
    "vtable:0x013ff648",
    "vtable:0x013ff6ac",
    "vtable:0x0147c9e8",
    "vtable:0x0147ca30",
    "vtable:0x0147cbbc",
    "vtable:0x0147cc14",
    "vtable:0x01489090",
    "vtable:0x014890f4",
    "vtable:0x014893b0",
    "vtable:0x01489414"
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
      "va": "0x00adfd60"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00de5260"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00adfeaa",
      "direction": "in",
      "other": "0x00adfd60",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00de5273",
      "direction": "in",
      "other": "0x00de5260",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 2,
  "fan_out": 0,
  "manifest_callees": [],
  "manifest_callers": [],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0113",
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
      "shared_vtable:vtable:0x013ff648,vtable:0x0147c9e8",
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
      "shared_vtable:vtable:0x013ff648,vtable:0x0147c9e8",
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
      "shared_vtable:vtable:0x013ff648,vtable:0x0147c9e8",
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
      "shared_vtable:vtable:0x013ff648,vtable:0x013ff6ac",
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
      "shared_vtable:vtable:0x013ff6ac,vtable:0x0147ca30",
      "same_calling_convention"
    ],
    "package": "pkg-sporepedia-slot-release",
    "score": 12,
    "symbol": "sporepedia_dispatch_owned_slot_FUN_00641e10",
    "va": "0x00641e10"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013ff648,vtable:0x013ff6ac",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-00641fa0",
    "score": 12,
    "symbol": "sporepedia_predicate_00641fa0",
    
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-swarm-w1-005c0dd0/swarm_w1_005c0dd0.cpp",
    "reconstruction/staging/pkg-swarm-w1-005c0dd0/swarm_w1_005c0dd0_model_test.cpp",
    "reconstruction/staging/pkg-swarm-w1-005c0dd0/swarm_w1_005c0dd0_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-swarm-w1-005c0dd0/005c0dd0.json"
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
    "Is the value's domain {0, 1} or 0..255? Nothing in these two instructions masks anything, and both direct callers are domain-agnostic: 0x00adfeb2 stores the raw byte, and 0x00de5278's TEST AL,AL takes the same branch for 2, 0x80 and 0xff as for 1. The model therefore returns the byte verbatim and the model test REQUIRES 0x80 and 0xff to survive, which is the opposite of asserting a boolean. A bool declaration would be an invented domain.",
    "The persisted ABI record's calling convention lists __fastcall as a candidate alongside __thiscall and reports corroboration 'not_available'. __thiscall is the one both the persisted and derived records resolve to, and it is the one the listing supports (a base-register receiver, a bare RET, zero stack slots), but the corroboration field is empty and this package does not upgrade that to a claim beyond what the two records already say.",
    "What class is this receiver? The target record carries subsystem 'Sporepedia' and cluster 'sporepedia-online', and the tables this body sits in have SDK-named Sporepedia::cSPAssetDataOTDB neighbours -- but THIS entry is sdk=false and unnamed, so the class is not claimed and the type is spelled SporepediaByteRecord as a shape only.",
    "What do bits 8..31 of EAX hold at a real call site? The body does not set them (8A is a partial register write) and no value is claimed. Both known call sites read AL alone, so they are unobservable in this build; a third-party caller that read the full EAX would see whatever it had left there. Settling this 
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-swarm-w1-005c0dd0/005c0dd0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w1-005c0dd0/swarm_w1_005c0dd0.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w1-005c0dd0/swarm_w1_005c0dd0_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w1-005c0dd0/swarm_w1_005c0dd0_types.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-swarm-w1-005c0dd0/005c0dd0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w1-005c0dd0/swarm_w1_005c0dd0.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w1-005c0dd0/swarm_w1_005c0dd0_model_test.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w1-005c0dd0/swarm_w1_005c0dd0_types.hpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/kno
[TRUNCATED]
```
