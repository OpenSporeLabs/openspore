# Reconstruction context 0x00641fa0

- Status: `partial`
- Content SHA-256: `703b7826f0d3a0c25a45f4c0f4af1df2c53e4fe43d45eaf38938b61f721de3a9`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00641fa0",
  "phase": "reconstruction",
  "target": "0x00641fa0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00641fa0",
  "package": "pkg-swarm-w1-00641fa0",
  "subsystem": "Sporepedia",
  "va": "0x00641fa0"
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
  "content_sha256": "ddd80a7ac65579f7ff69ad624589f3ea13a9facb5070475cd17318ef7a89107b",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00641fa0 failed: Decompilation did not complete. Reason: ",
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
  "return_register": "EAX, and only AL: both terminators write AL explicitly (MOV AL,0x1 at 0x00641fc6, XOR AL,AL at 0x00641fca) and nothing in the 22 writes any other byte of it.",
  "return_type": "std::uint8_t",
  "return_width_bytes": 1,
  "saved_registers": [
    "ESI"
  ],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller (moot: there is no ordinary stack argument to clean, and both terminators are a bare RET with no immediate)",
  "termination": "RET"
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
      "callsite": "0x00641fad",
      "direction": "out",
      "other": "0x00641900",
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
    "global:PASS -- none; no instruction names a data-segment address and the record's globals list is empty."
  ],
  "types": [
    "openspore::reconstruction::pkg_swarm_w1_00641fa0::AssetDataSubObject04",
    "openspore::reconstruction::pkg_swarm_w1_00641fa0::DispatchSlot68",
    "openspore::reconstruction::pkg_swarm_w1_00641fa0::DispatchTable",
    "openspore::reconstruction::pkg_swarm_w1_00641fa0::SporepediaAssetDataOtdb",
    "openspore::reconstruction::pkg_swarm_w1_00641fa0::Word",
    "std::uint8_t"
  ],
  "vtables": [
    "vtable:0x013ff648",
    "vtable:0x013ff6ac",
    "vtable:0x01462764",
    "vtable:0x014627bc",
    "vtable:0x0147c9e8",
    "vtable:0x0147ca30",
    "vtable:0x0147caf8",
    "vtable:0x0147cbbc",
    "vtable:0x0147cc14",
    "vtable:0x01489090",
    "vtable:0x014890f4",
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
  "callees": [],
  "callees_truncated": false,
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00641fad",
      "direction": "out",
      "other": "0x00641900",
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
    "id": "scc-0167",
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
      "shared_vtable:vtable:0x013ff6ac,vtable:0x01462764",
      "same_calling_convention"
    ],
    "package": "pkg-sporepedia-slot-release",
    "score": 12,
    "symbol": "sporepedia_dispatch_owned_slot_FUN_00641e10",
    "va": "0x00641e10"
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-swarm-w1-00641fa0/sw1_00641fa0.cpp",
    "reconstruction/staging/pkg-swarm-w1-00641fa0/sw1_00641fa0_model_test.cpp",
    "reconstruction/staging/pkg-swarm-w1-00641fa0/sw1_00641fa0_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-swarm-w1-00641fa0/00641fa0.json"
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
    "The semantic name of the predicate. The shape -- three inputs, one direct callee, one virtual slot, a null-ness gate -- is fully reconstructed, but nothing in the evidence says what question the boolean answers. 'IsEditable' is the name the repository gives the neighbour at 0x00641400 and the shapes differ; it is deliberately NOT borrowed here.",
    "What the 0x0c sub-object at receiver+0x04 is, and what 0x00641900 decides. This package fixes only that the callee is handed its address, reads the dwords at +0x00 and +0x08 through it, and returns a byte. 0x00641900's own body is 88 instructions long, has one direct call of its own (0x0067dcd0) and two levels of virtual dispatch, and is not this worker's target; it is unowned here.",
    "What the dword at receiver+0x1c IS. The body compares it against zero and never dereferences it, so it is a null-ness gate on a word whose type, ownership and producer no record for this VA establishes. It is modelled as an opaque Word and nothing more. Naming it (a handle, a flag word, a version) would be a member story the listing does not carry.",
    "Whether a live receiver is ever dispatched through the four-slot table at 0x013ff6ac, in which this body is index 3. If it is, the index-0x68 word this body loads is data past that table rather than one of its slots. The two larger tables show real content at index 26, so the two-level load is not in doubt; what is open is which table a given receiver carries.",
    "Whether the class name Sporepedia::cSPAssetDataOTDB applies to THIS vir
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-swarm-w1-00641fa0/00641fa0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w1-00641fa0/sw1_00641fa0.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w1-00641fa0/sw1_00641fa0_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w1-00641fa0/sw1_00641fa0_types.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-swarm-w1-00641fa0/00641fa0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w1-00641fa0/sw1_00641fa0.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w1-00641fa0/sw1_00641fa0_model_test.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w1-00641fa0/sw1_00641fa0_types.hpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.js
[TRUNCATED]
```
