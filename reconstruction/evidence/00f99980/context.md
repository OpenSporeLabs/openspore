# Reconstruction context 0x00f99980

- Status: `partial`
- Content SHA-256: `b8c629c1dec733ca5ad4ae757ed8f373a776585ebb39c5308b756a2566c5da3e`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00f99980",
  "phase": "reconstruction",
  "target": "0x00f99980"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00f99980",
  "package": null,
  "subsystem": "Sporepedia",
  "va": "0x00f99980"
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
  "content_sha256": "94ad50daa3e7e61d863c2d6cfd6a099c0d4d4a7eccb197d090aad60eb46e0697",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00f99980 failed: Decompilation did not complete. Reason: ",
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
  "return_note": "(declared); the machine-derived record's own claim is the phrase 'unclassified_in_EAX' -- see implementation.return_type_note for why the two cannot be reconciled by any C++ spelling",
  "return_register": "EAX",
  "return_type": "void",
  "saved_registers": [
    "ESI"
  ],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "RET at 0x00f999d7, plus one unconditional transfer out of the body at 0x00f999d1 (JMP 0x00690120) that is a tail call"
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
      "callsite": "0x00f9998c",
      "direction": "out",
      "other": "0x0067dd50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f999d1",
      "direction": "out",
      "other": "0x00690120",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f999b7",
      "direction": "out",
      "other": "0x00692400",
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
    "void",
    "void (declared); the machine-derived record's own claim is the phrase 'unclassified_in_EAX' -- see implementation.return_type_note for why the two cannot be reconciled by any C++ spelling"
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
      "callsite": "0x00f9998c",
      "direction": "out",
      "other": "0x0067dd50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f999d1",
      "direction": "out",
      "other": "0x00690120",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f999b7",
      "direction": "out",
      "other": "0x00692400",
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
    "id": "scc-0572",
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
    "reconstruction/staging/pkg-swarm-w2-00f99980/sw2_00f99980.cpp",
    "reconstruction/staging/pkg-swarm-w2-00f99980/sw2_00f99980_model_test.cpp",
    "reconstruction/staging/pkg-swarm-w2-00f99980/sw2_00f99980_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-swarm-w2-00f99980/00f99980.json"
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
    "ABI is WARN, and it is fixed rather than fixable from this package: the derived record's verdict is ABI_UNKNOWN because the inference's linear ESP walk ended at +4 on a listing that is not one path, and the record states that reason itself. The model here supplies the per-path frame the walker could not (mechanics.frame_resolution), and the model test measures the frame with two ESP-sampling trampolines, but the verdict is read out of the committed record and no source edit can move it.",
    "The canonical ABI record cannot be reconciled with any C++ return type, and this package does not try. abi_derived.abi.return_semantics is the machine phrase 'unclassified_in_EAX' and the validator compares the declared return type against it as a string, so RETURN SEMANTICS is a WARN whatever is written. The choice made here is (b) of the wave-1 lesson -- declare void -- and the argument for it is in implementation.return_type_note: no instruction in the 25 has EAX as a destination and all three calls' return words are discarded. The alternative (a), a 32-bit integral return, would be a positive claim that this body produces a value, which the bytes refute. The record's void_possible false is not a counter-argument: abi_infer.py sets that flag only when EAX is never written AND the body contains no call, so it is unset for every body with a call in it, whatever the body returns. No typedef named after the phrase exists in this package.",
    "The model's emitted code for the transfer at 0x00f999d1 is call+ret rather than the machi
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-swarm-w2-00f99980/00f99980.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w2-00f99980/sw2_00f99980.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w2-00f99980/sw2_00f99980_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w2-00f99980/sw2_00f99980_types.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-swarm-w2-00f99980/00f99980.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w2-00f99980/sw2_00f99980.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w2-00f99980/sw2_00f99980_model_test.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w2-00f99980/sw2_00f99980_types.hpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.js
[TRUNCATED]
```
