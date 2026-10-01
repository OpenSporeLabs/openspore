# Reconstruction context 0x00f999e0

- Status: `partial`
- Content SHA-256: `576c21aad352d451a8843a4613773bfccc8c07a664786c9dcec9bbfbc158f718`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00f999e0",
  "phase": "reconstruction",
  "target": "0x00f999e0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00f999e0",
  "package": "pkg-swarm-w2-00f999e0",
  "subsystem": "Sporepedia",
  "va": "0x00f999e0"
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
  "content_sha256": "28680085b963bcd947bc5968062de1c305202bd3e1849a3a553a8d3715799404",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00f999e0 failed: Decompilation did not complete. Reason: ",
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
  "return_note": "REPAIR rp10. return_type now states the type the source span declares and the listing proves (std::uint8_t, one byte), and the machine record's register-CLASSIFICATION was moved out of that field into return_semantics, where the phrase is kept verbatim. The phrase is a register class, not a C type, and the listing refutes it: XMM0 is written only by MOVSS, read only by UCOMISS, and left holding nothing on every path, while all three exits write AL only. No typedef named after the phrase exists or may be added. See return_semantics.record_disagreement and unresolved_questions item 1.",
  "return_register": "AL (one byte), a machine fact and not a modelling choice: all three exits write AL only. The machine record's own claim is XMM0; it is kept in return_semantics and its refutation in return_note.",
  "return_semantics": "float_or_x87_in_XMM0",
  "return_type": "std::uint8_t",
  "saved_registers": [
    "ESI",
    "EDI"
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
      "callsite": "0x00f999e3",
      "direction": "out",
      "other": "0x00f48a70",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f999ea",
      "direction": "out",
      "other": "0x00f699b0",
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
    "global:0x016c8eb0",
    "global:PASS"
  ],
  "types": [
    "Real -- float, binary32, because MOVSS and UCOMISS each read four bytes",
    "Receiver -- an opaque byte run, one unnamed array, no member named anywhere in this package (the machine-derived receiver record is bounds_only)",
    "SlotFirst -- Word (__thiscall *)(Receiver*, std::uint8_t), the shape of the table word at slot +0x4c, the one word it takes being callee-popped",
    "SlotSecond -- Word (__thiscall *)(Receiver*), the shape of the table word at slot +0x30, taking no word",
    "Word -- std::uint32_t, a 32-bit table entry and a 32-bit receiver word",
    "std::uint8_t"
  ],
  "vtables": [
    "vtable:0x01490be8"
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
      "callsite": "0x00f999e3",
      "direction": "out",
      "other": "0x00f48a70",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f999ea",
      "direction": "out",
      "other": "0x00f699b0",
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
    "id": "scc-0573",
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
    "package": "pkg-swarm-w1-005c0dd0",
    "score": 8,
    "symbol": "re_005c0dd0",
    "va": "0x005c0dd0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-006413d0",
    "score": 8,
    "symbol": "re_
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-swarm-w2-00f999e0/sw2_00f999e0.cpp",
    "reconstruction/staging/pkg-swarm-w2-00f999e0/sw2_00f999e0_model_test.cpp",
    "reconstruction/staging/pkg-swarm-w2-00f999e0/sw2_00f999e0_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-swarm-w2-00f999e0/00f999e0.json"
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
    "DUPLICATE-OWNERSHIP CHECK NOT PERFORMED WITHIN BUDGET: I did not sweep reconstruction/metadata/ for another sidecar claiming 0x00f999e0. The existing_reconstruction block of my briefing reported files [], handoffs [] and metadata [], which is the pack's own view and is not the same as a directory sweep. The integrator should confirm this VA is singly owned before promotion, the way pkg-dfw-006a2e20 records for 0x006a2e20.",
    "RETURN SEMANTICS: the machine record and the listing still disagree, and this package cannot settle it -- it can only say which of the two is wrong. abi.return_register is \"XMM0\" with return_semantics \"float_or_x87_in_XMM0\" (APPROXIMATION, inference RT1: \"an x87 or SSE instruction appears in the body\"), and that is a REGISTER-CLASS CLASSIFICATION, not a C type. The listing refutes it on every count: XMM0 is written by the six MOVSS and read by the six UCOMISS and holds nothing on any exit; the three exits write AL only (XOR AL,AL at 0x00f999f3, MOV AL,0x1 at 0x00f99aab, XOR AL,AL at 0x00f99ab0); and no instruction in the 80 writes the other three bytes of the return register. So RT1 is a PRESENCE test over an SSE mnemonic firing on a body that uses SSE only to compare, and whether that rule should be narrowed is a question for the ABI layer, not for a reconstruction. This is why the machine-evidenced width route cannot arbitrate either: evidence_returns.classify over this body's own record returns state UNCLASSIFIED with the reason \"the ABI record names XMM0 as the return register; an SSE 
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-swarm-w2-00f999e0/00f999e0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w2-00f999e0/sw2_00f999e0.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w2-00f999e0/sw2_00f999e0_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w2-00f999e0/sw2_00f999e0_types.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-swarm-w2-00f999e0/00f999e0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w2-00f999e0/sw2_00f999e0.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w2-00f999e0/sw2_00f999e0_model_test.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w2-00f999e0/sw2_00f999e0_types.hpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.js
[TRUNCATED]
```
