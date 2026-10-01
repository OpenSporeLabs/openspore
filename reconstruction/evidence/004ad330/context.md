# Reconstruction context 0x004ad330

- Status: `partial`
- Content SHA-256: `0ac2d147bf41b04d4fcbfbc631ca41d4f5626a3ec40e130f2d2b375e2c1d7292`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x004ad330",
  "phase": "reconstruction",
  "target": "0x004ad330"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": null,
  "package": null,
  "subsystem": null,
  "va": "0x004ad330"
}
```

## 03_current_status

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "blocked": false,
  "reconstructed": false,
  "runtime_gated": true,
  "runtime_validated": 0,
  "status": "unresolved"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "43e63eefb29947cc370cc21b3824e6b66385e6a0e24312330d80191c70a18b5e",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x004ad330 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "__fastcall (register argument in ECX, no stack arguments)",
  "hidden_receiver": "ECX",
  "hidden_this_register": "ECX is spilled to [EBP - 0xc] at 0x004ad336 and reloaded twice, at 0x004ad339 for the 0x004ad280 call and at 0x004ad341 for the field_30 read; it is also pushed at 0x004ad35c as 0x004b9570's second argument",
  "ordinary_stack_argument_slots": 0,
  "receiver": true,
  "ret_form": "RET",
  "return_observation": "the last write to EAX is 0x004ad353 MOV EAX,dword ptr [EDX + 0x30], a reload of the member that is immediately stored to [EBP - 0x8]; nothing survives to the epilogue",
  "return_register": "none",
  "return_semantics": "no value; EAX is never written on any path",
  "return_type": "void",
  "return_width_bytes": 0,
  "saved_registers": [],
  "stack_arguments": [],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "callee",
  "termination": "two paths, both through 0x004ad365: the JZ at 0x004ad34e and the fall-through after 0x004b9570"
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
      "va": "0x0040d2d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0046d840"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004aba00"
    },
    {
      "name": "Editors::cEditor::Dispose",
      "reconstructed": false,
      "va": "0x00576c50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0057d710"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0057f6c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00585c10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00586b00"
    },
    {
      "name": "Editors::cEditor::OnExit",
      "reconstructed": false,
      "va": "0x00587a20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005f40b0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x0040d3b5",
      "direction": "in",
      "other": "0x0040d2d0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0040e58e",
      "direction": "in",
      "other": "0x0040d2d0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0046da80",
      "direction": "in",
      "other": "0x0046d840",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x004aba1f",
      "direction": "in",
      "other": "0x004aba00",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00576d38",
      "direction": "in",
      "ot
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "void"
  ],
  "vtables": []
}
```

## 09_state_event_relationships

- State: `present`
- Provenance: `knowledgegraph/research/semantic-decomp.json, reconstruction/knowledge/index.json`

```json
{
  "runtime": {
    "blocking_reason": null,
    "gates": [
      "A runtime trace is required to determine whether the double base pass in OnExit is benign in the shipping build.",
      "A runtime trace is required to observe the two virtual calls in 0x004ad280 and thereby resolve the receiver's class.",
      "No original-process trace has ever been captured for 0x004ad330; every claim here is static. The original Cell stage has never been entered in any recorded run."
    ],
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
      "va": "0x0040d2d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0046d840"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004aba00"
    },
    {
      "name": "Editors::cEditor::Dispose",
      "reconstructed": false,
      "va": "0x00576c50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0057d710"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0057f6c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00585c10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00586b00"
    },
    {
      "name": "Editors::cEditor::OnExit",
      "reconstructed": false,
      "va": "0x00587a20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005f40b0"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x0040d3b5",
      "direction": "in",
      "other": "0x0040d2d0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0040e58e",
      "direction": "in",
      "other": "0x0040d2d0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0046da80",
      "direction": "in",
      "other": "0x0046d840",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x004aba1f",
      "direction": "in",
      "other": "0x004aba00",
      "reference_type": "direct-
[TRUNCATED]
```

## 11_related_functions

- State: `missing`
- Provenance: `reconstruction/knowledge/index.json`

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/wave13-w1-dispatch-b02/b4ad330_teardown_004ad330.cpp",
    "reconstruction/staging/wave13-w1-dispatch-b02/b4ad330_teardown_004ad330.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-dispatch-b02/004ad330.json"
  ]
}
```

## 13_semantic_hypotheses

- State: `missing`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

## 14_conflicts_questions

- State: `conflicted`
- Provenance: `reconstruction/knowledge/index.json, knowledgegraph/research/semantic-decomp.json`

```json
{
  "conflicts": [
    {
      "derived": "__thiscall",
      "field": "calling_convention",
      "kind": "derived_vs_persisted",
      "persisted": "__fastcall (register argument in ECX, no stack arguments)",
      "resolution_status": "unresolved"
    }
  ],
  "unresolved_questions": [
    "A runtime trace is required to determine whether the double base pass in OnExit is benign in the shipping build.",
    "A runtime trace is required to observe the two virtual calls in 0x004ad280 and thereby resolve the receiver's class.",
    "Is the double 0x004ad280 pass in Editors::cEditor::OnExit intentional, or does it rely on the base pass being tolerant of an already-emptied vector?",
    "Nine of the thirteen callsites were not disassembled, so their null-guard and refcount context is unverified.",
    "No original-process trace has ever been captured for 0x004ad330; every claim here is static. The original Cell stage has never been entered in any recorded run.",
    "What are the two virtual callees at receiver vtable slots +0x00 and +0x08 that 0x004ad280 invokes with the float-table address?",
    "What class is the member at +0x30?",
    "What class owns this method? There is no data reference at this address, so no vtable can be derived, and the binary has no MSVC RTTI.",
    "What does 0x004b98b0 and 0x004b97e0 do to the sub-object at member+0x18?",
    "What is the pointer vector at receiver+0x18, and what does 0x00451400 do to each element?"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-w1-dispatch-b02/004ad330.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b02/b4ad330_teardown_004ad330.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b02/b4ad330_teardown_004ad330.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave13-w1-dispatch-b02/004ad330.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b02/b4ad330_teardown_004ad330.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b02/b4ad330_teardown_004ad330.hpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.json"
  ],
  "required_categories": [
    "ABI",
    "CALLS",
    "GLOBALS",
    "FIELDS/OFFSETS",
    "CONSTANTS",
    "CONTROL FLOW",
    "VIRTUAL DI
[TRUNCATED]
```
