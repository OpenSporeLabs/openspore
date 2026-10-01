# Reconstruction context 0x00faad80

- Status: `partial`
- Content SHA-256: `6e64b9e7949fe5b0b57dadcfd61412d4c7d653ff367b5d046d725807fcd353f6`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00faad80",
  "phase": "reconstruction",
  "target": "0x00faad80"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00faad80",
  "package": null,
  "subsystem": "Sporepedia",
  "va": "0x00faad80"
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
  "content_sha256": "9a684e6c0a7668f853e8062d4f86dc1a9a6b3ce464a2531dc84e2ead586b33f3",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00faad80 failed: Decompilation did not complete. Reason: ",
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
  "ordinary_stack_argument_slots": 2,
  "receiver_register": "ECX",
  "ret_form": "RET 0x8",
  "return_register": "none -- EAX is dead and the x87 stack is empty at both returns",
  "return_semantics": "none. The committed record's phrase 'float_or_x87_in_ST0' is an APPROXIMATION derived by inference RT1 from the presence of an x87 instruction; the bytes do not support it. See implementation.return_type_note and unresolved_questions item 1.",
  "return_type": "void",
  "saved_registers": [
    "EBP",
    "EBX",
    "EDI",
    "ESI"
  ],
  "stack_cleanup_bytes": 8,
  "stack_cleanup_owner": "callee",
  "termination": "RET 0x8"
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
      "callsite": "0x00faae6b",
      "direction": "out",
      "other": "0x0067dd80",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00fab036",
      "direction": "out",
      "other": "0x00690120",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00fab047",
      "direction": "out",
      "other": "0x006909b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00faaf41",
      "direction": "out",
      "other": "0x00f96370",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00fab017",
      "direction": "out",
      "other": "0x00f96f90",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00faae2b",
      "direction": "out",
      "other": "0x00f977c0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00faadd6",
      "direction": "out",
      "other": "0x00f9b8c0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00fab05c",
      "direction": "out",
      "other": "0x00f9ba40",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00fab0b0",
      "direction": "out",
      "other": "0x00fa5610",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00fab03d",
      "direction": "out",
      "other": "0x00faacd0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00faaff3",
      "direction": "out",
      "other": "0x00faf140",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [
    "global:WARN"
  ],
  "types": [
    "void"
  ],
  "vtables": [
    "vtable:0x01490be8",
    "vtable:0x01490c7c"
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
      "callsite": "0x00faae6b",
      "direction": "out",
      "other": "0x0067dd80",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00fab036",
      "direction": "out",
      "other": "0x00690120",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00fab047",
      "direction": "out",
      "other": "0x006909b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00faaf41",
      "direction": "out",
      "other": "0x00f96370",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00fab017",
      "direction": "out",
      "other": "0x00f96f90",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00faae2b",
      "direction": "out",
      "other": "0x00f977c0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00faadd6",
      "direction": "out",
      "other": "0x00f9b8c0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00fab05c",
      "direction": "out",
      "other": "0x00f9ba40",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00fab0b0",
      "direction": "out",
      "other": "0x00fa5610",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00fab03d",
      "direction": "out",
      "other": "0x00faacd0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00faaff3",
      "direction": "out",
      "other": "0x
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
      "shared_vtable:vtable:0x01490be8",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w2-00f999e0",
    "score": 12,
    "symbol": "re_00f999e0",
    "va": "0x00f999e0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01490be8",
      "same_calling_convention"
    ],
    "package": "pkg-fa0d50-atomic-inc",
    "score": 12,
    "symbol": "FUN_00fa0d50",
    "va": "0x00fa0d50"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01490be8",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-00fa5580",
    "score": 12,
    "symbol": "re_00fa5580",
    "va": "0x00fa5580"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01490be8",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-00fa6ec0",
    "score": 12,
    "symbol": "re_00fa6ec0",
    "va": "0x00fa6ec0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01490be8",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-00fa73c0",
    "score": 12,
    "symbol": "sw1_snap_and_dispatch_00fa73c0",
    "va": "0x00fa73c0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01490be8",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-0104c110",
    "score": 12,
    "symbol": "re_0104c110",
    "va": "0x0104c110"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-005
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-swarm-w2-00faad80/sw2_00faad80.cpp",
    "reconstruction/staging/pkg-swarm-w2-00faad80/sw2_00faad80_model_test.cpp",
    "reconstruction/staging/pkg-swarm-w2-00faad80/sw2_00faad80_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-swarm-w2-00faad80/00faad80.json"
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
    "EVIDENCE COVERAGE is 10 of 17 static categories for this target and no source file, sidecar field or metadata edit can move it: the validator derives it purely from the pack's per-category availability, and this pack reports seven unavailable. It is reported, not chased.",
    "Nothing inside any of the fifteen direct callees was reconstructed, and no claim is made about any of them beyond the argument list, order and convention its call site fixes, plus the two callees whose own bodies were read out of the image (0x0067dd80 and 0x00f96370) because the body depends on what they do.",
    "The ECX receiver of 0x00fbf570 is NOT DETERMINED by this body, and this package does not guess it. 0x00faaf0b is the only call whose ECX the listing does not reload; the last write is MOV ECX,ESI at 0x00faaec4 for the slot+0x10 call, whose return type this listing does not fix either. The model passes a declared sentinel and the model test asserts the callee receives exactly it, so the non-claim is checkable. Settling it needs 0x00fbf570's own body.",
    "The committed ABI record's return_semantics is the phrase 'float_or_x87_in_ST0' and this package declares void. The record's own inference RT1 is an APPROXIMATION derived from a single observation -- 'an x87 or SSE instruction appears in the body' -- and the listing refutes it: the x87 stack is empty at 0x00faade0 and at 0x00fab0d1, because every x87 value the body produces is stored straight back or popped. The honest options were to declare a type true of the listing and record the 
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-swarm-w2-00faad80/00faad80.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w2-00faad80/sw2_00faad80.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w2-00faad80/sw2_00faad80_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w2-00faad80/sw2_00faad80_types.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-swarm-w2-00faad80/00faad80.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w2-00faad80/sw2_00faad80.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w2-00faad80/sw2_00faad80_model_test.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w2-00faad80/sw2_00faad80_types.hpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.js
[TRUNCATED]
```
