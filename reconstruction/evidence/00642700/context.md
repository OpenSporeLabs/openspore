# Reconstruction context 0x00642700

- Status: `partial`
- Content SHA-256: `108582d4eaa68471df73009e7b392c92948bbe80ce31d7df5f565dc006947f7a`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00642700",
  "phase": "reconstruction",
  "target": "0x00642700"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00642700",
  "package": "pkg-swarm-w2-00642700",
  "subsystem": "Sporepedia",
  "va": "0x00642700"
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
  "content_sha256": "d1c819729714e0d6ce4b877b59e960b75d60dcb74a9262cc5e107096cbab8fcc",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00642700 failed: Decompilation did not complete. Reason: ",
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
  "return_register": "EAX",
  "return_type": "bool",
  "saved_registers": [
    "ESI",
    "EDI"
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
  "callers": [],
  "edge_rows": [
    {
      "callsite": "0x00642747",
      "direction": "out",
      "other": "0x004558a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0064277c",
      "direction": "out",
      "other": "0x004558a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006427b1",
      "direction": "out",
      "other": "0x004558a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006427e6",
      "direction": "out",
      "other": "0x004558a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00642821",
      "direction": "out",
      "other": "0x004558a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00642719",
      "direction": "out",
      "other": "0x00556140",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00642752",
      "direction": "out",
      "other": "0x00556140",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00642787",
      "direction": "out",
      "other": "0x00556140",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006427bc",
      "direction": "out",
      "other": "0x00556140",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006427f1",
      "direction": "out",
      "other": "0x00556140",
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
    "SporepediaTypeDescriptor",
    "SporepediaTypeKeySource",
    "SporepediaTypeKeyVector",
    "Word",
    "bool"
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
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00642747",
      "direction": "out",
      "other": "0x004558a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0064277c",
      "direction": "out",
      "other": "0x004558a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006427b1",
      "direction": "out",
      "other": "0x004558a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006427e6",
      "direction": "out",
      "other": "0x004558a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00642821",
      "direction": "out",
      "other": "0x004558a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00642719",
      "direction": "out",
      "other": "0x00556140",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00642752",
      "direction": "out",
      "other": "0x00556140",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00642787",
      "direction": "out",
      "other": "0x00556140",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006427bc",
      "direction": "out",
      "other": "0x00556140",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006427f1",
      "direction": "out",
      "other": "0x00556140",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 0,
  "fan_ou
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
    "package": "pkg-swarm-w1-00a649a0",
    "score": 15,
    "symbol": "re_00a649a0",
    "va": "0x00a649a0"
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
    "package": "pkg-swarm-w1-00641410"
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-swarm-w2-00642700/sw2_00642700.cpp",
    "reconstruction/staging/pkg-swarm-w2-00642700/sw2_00642700_model_test.cpp",
    "reconstruction/staging/pkg-swarm-w2-00642700/sw2_00642700_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-swarm-w2-00642700/00642700.json"
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
    "Is 0x00642700 a virtual function with any DIRECT caller at all? The record carries seven data-side xrefs, all of which are this body's own address inside twelve tables, so the entry is a virtual function; no direct-call xref is recorded in either direction. Whether some other image, a mod, or a vtable reached only at run time calls it directly is not established here.",
    "Is the caller-visible destruction of the argument slot load-bearing? On any path that reaches 0x0064275d this body overwrites the caller's own argument word (entry+4) with a lookup result -- the vector pointer the caller pushed is destroyed. The argument is dead to the body, but a caller that read its own argument slot back would see a lookup result. No record establishes whether any caller does, and the model does not assert the machine's slot aliasing at all (see mechanics.frame_resolution.value_slot_is_not_constant).",
    "The canonical ABI record's return claim is the machine-vocabulary string 'integral_in_EAX' (abi.return_semantics; abi_derived inference RT2 register_class 'integral'), and the ghidra_function record says return_type 'undefined' with return_type_resolved false. The listing writes only AL, so this package declares bool -- the width the machine fixes -- which is option (a) of the wave-1 guidance. The consequence is that RETURN SEMANTICS compares the strings 'bool' and 'integral_in_EAX' and WARNs, and no honest declaration can make that comparison succeed. Declaring void is not available (three instructions produce a value) and inv
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-swarm-w2-00642700/00642700.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w2-00642700/sw2_00642700.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w2-00642700/sw2_00642700_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w2-00642700/sw2_00642700_types.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-swarm-w2-00642700/00642700.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w2-00642700/sw2_00642700.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w2-00642700/sw2_00642700_model_test.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w2-00642700/sw2_00642700_types.hpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.js
[TRUNCATED]
```
