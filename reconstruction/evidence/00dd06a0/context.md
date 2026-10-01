# Reconstruction context 0x00dd06a0

- Status: `partial`
- Content SHA-256: `796c12cd19f67cf878f36bfa9b5d3159e38df1b25e8ec3b033980c66c2457533`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00dd06a0",
  "phase": "reconstruction",
  "target": "0x00dd06a0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00dd06a0",
  "package": "pkg-swarm-w1-00dd06a0",
  "subsystem": "Sporepedia",
  "va": "0x00dd06a0"
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
  "content_sha256": "f9a92b01b4f0d89fcd63875cde9c303417b8851d63890598606dea94bed7a514",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00dd06a0 failed: Decompilation did not complete. Reason: ",
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
  "return_register": "EAX",
  "return_type": "std::int32_t",
  "saved_registers": [
    "ESI"
  ],
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
  "callers": [],
  "edge_rows": [
    {
      "callsite": "0x00dd06d1",
      "direction": "out",
      "other": "0x00b6e250",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00dd06e1",
      "direction": "out",
      "other": "0x00b6f0d0",
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
    "std::int32_t"
  ],
  "vtables": [
    "vtable:0x0147cbbc"
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
      "callsite": "0x00dd06d1",
      "direction": "out",
      "other": "0x00b6e250",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00dd06e1",
      "direction": "out",
      "other": "0x00b6f0d0",
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
    "id": "scc-0507",
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
      "shared_vtable:vtable:0x0147cbbc",
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
      "shared_vtable:vtable:0x0147cbbc",
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
      "shared_vtable:vtable:0x0147cbbc",
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
      "shared_vtable:vtable:0x0147cbbc",
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
      "shared_vtable:vtable:0x0147cbbc",
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
      "shared_vtable:vtable:0x0147cbbc",
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
      "shared_vtable:vtable:0x0147cbbc",
      "same_
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-swarm-w1-00dd06a0/sw1_00dd06a0.cpp",
    "reconstruction/staging/pkg-swarm-w1-00dd06a0/sw1_00dd06a0_model_test.cpp",
    "reconstruction/staging/pkg-swarm-w1-00dd06a0/sw1_00dd06a0_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-swarm-w1-00dd06a0/00dd06a0.json"
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
    "Is 0x00dd06d1's call really argument-free, as a behavioural matter? As a STATIC matter it is: the instruction before the call is 0x00dd06cf's JZ, no instruction pushes for it, and 0x00b6e250's own body reads no stack slot. It is NOT observable through a compiled model, which balances its own pushes, and the model test says so rather than pretending to check it. Two instruments that tried were withdrawn and the reasons are recorded in the model test's own file: a stack-depth difference measured 48 bytes of the compiler's -O0 frame where the listing's prologue accounts for 4, and a read of the word above the callee's return address read the compiler's 12 bytes of call-alignment padding rather than the argument slot. What is asserted instead is the observable content: the model's frame is balanced across the call and the caller's own stack word is untouched when it returns (C1, C3).",
    "Is 0x00dd06e6's ADD ESP,0x4 the callee's or the caller's? The callee's own terminator is a bare C3 with no immediate, so it is the caller's -- that is established by real evidence. But for a cdecl leaf callee that does not touch the caller's stack, a callee-pops and a caller-pops return are the same machine behaviour, and no black-box observer can tell them apart. Reported as a known limit of the test, not as an open question about the reconstruction.",
    "Is 0x0147cbbc really the start of a function table? The word at 0x0147cbbc + 0x2c is 0xf0ff0300, which is below the image base and therefore not a code address, in a run where every o
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-swarm-w1-00dd06a0/00dd06a0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w1-00dd06a0/sw1_00dd06a0.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w1-00dd06a0/sw1_00dd06a0_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w1-00dd06a0/sw1_00dd06a0_types.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-swarm-w1-00dd06a0/00dd06a0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w1-00dd06a0/sw1_00dd06a0.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w1-00dd06a0/sw1_00dd06a0_model_test.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w1-00dd06a0/sw1_00dd06a0_types.hpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.js
[TRUNCATED]
```
