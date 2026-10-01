# Reconstruction context 0x00641fd0

- Status: `partial`
- Content SHA-256: `856e21292295494e7f41aeb9d740d409d3f816a9722d53beda5c1ff66895c207`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00641fd0",
  "phase": "reconstruction",
  "target": "0x00641fd0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00641fd0",
  "package": "pkg-swarm-w1-00641fd0",
  "subsystem": "Sporepedia",
  "va": "0x00641fd0"
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
  "content_sha256": "af445398eff5c5adfde5079a89d326a38e81fa5fb4d934bd1aa4090ce1103373",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00641fd0 failed: Decompilation did not complete. Reason: ",
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
  "return_note": "a source-side choice: the machine fixes a 32-bit word in EAX and nothing fixes a C type. See return_semantics and unresolved_questions.",
  "return_register": "EAX",
  "return_type": "void*",
  "saved_registers": [
    "EDI",
    "ESI"
  ],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "callee",
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
      "callsite": "0x00642038",
      "direction": "out",
      "other": "0x00612f50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00642014",
      "direction": "out",
      "other": "0x00613860",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00642002",
      "direction": "out",
      "other": "0x0067cb30",
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
    "AcquireSlot04",
    "Acquired",
    "HandlePair",
    "ResolveSlot90",
    "Service",
    "ServiceRoot",
    "SporepediaAssetDataOtdb",
    "void*"
  ],
  "vtables": [
    "vtable:0x013ff648",
    "vtable:0x013ff6ac",
    "vtable:0x01462764",
    "vtable:0x014627bc",
    "vtable:0x0147ca30",
    "vtable:0x0147ca70",
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
      "callsite": "0x00642038",
      "direction": "out",
      "other": "0x00612f50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00642014",
      "direction": "out",
      "other": "0x00613860",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00642002",
      "direction": "out",
      "other": "0x0067cb30",
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
    "id": "scc-0168",
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
      "shared_types:void*",
      "shared_vtable:vtable:0x013ff648,vtable:0x01462764",
      "same_calling_convention"
    ],
    "package": "pkg-vft-slot-006e64f0",
    "score": 15,
    "symbol": "re_006e64f0",
    "va": "0x006e64f0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_types:void*",
      "shared_vtable:vtable:0x013ff648,vtable:0x013ff6ac"
    ],
    "package": "pkg-00b7e380-member-ptr-0x2c",
    "score": 13,
    "symbol": "member_ptr_0x2c_00b7e380",
    "va": "0x00b7e380"
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
    "va": "0x0064
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-swarm-w1-00641fd0/sw1_00641fd0.cpp",
    "reconstruction/staging/pkg-swarm-w1-00641fd0/sw1_00641fd0_model_test.cpp",
    "reconstruction/staging/pkg-swarm-w1-00641fd0/sw1_00641fd0_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-swarm-w1-00641fd0/00641fd0.json"
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
    "No ordinary caller is named. The record's callers list is empty and the xref export has no inbound call edge; the only inbound references are the seven vtable slots. So the contract of the return value -- whether a caller releases what it is handed, or only inspects it -- is unestablished, and the reconstruction asserts the reference is taken and never released, which is all the body shows.",
    "The 0x0067cb30 global's identity is not established. The callee returns the dword at 0x015fcc70 and the body reads the service out of that object's +0x5c; whether 0x015fcc70 holds a manager, a registry or a singleton pointer is not fixed by anything in this set, and the address is deliberately kept out of the reconstruction's function span.",
    "The RETURN SEMANTICS pass is partly self-referential and a reader should know it. The index record's abi was an empty object before this sidecar existed, so the only canonical return claim the validator could find is the one THIS SIDECAR contributes (observed_original_abi.return_type = \"void*\"), and the check compares that against the span's own declaration. The machine contributes the width and nothing more: abi_derived.return says register EAX, register_class \"integral\", type null. Before this sidecar existed the check would have compared the evidence pack's prose claim \"integral_in_EAX\" with the declaration and reported WARN. The integrator should treat the machine-fixed part (a 32-bit word in EAX, three exits, no sret) as the finding and the C spelling as a source-side choic
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-swarm-w1-00641fd0/00641fd0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w1-00641fd0/sw1_00641fd0.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w1-00641fd0/sw1_00641fd0_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w1-00641fd0/sw1_00641fd0_types.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-swarm-w1-00641fd0/00641fd0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w1-00641fd0/sw1_00641fd0.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w1-00641fd0/sw1_00641fd0_model_test.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w1-00641fd0/sw1_00641fd0_types.hpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.js
[TRUNCATED]
```
