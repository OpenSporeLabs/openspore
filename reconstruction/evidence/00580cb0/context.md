# Reconstruction context 0x00580cb0

- Status: `partial`
- Content SHA-256: `34559b11e08150294c5801ad99591dbdad468c7d0be583daccd8df9908162314`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00580cb0",
  "phase": "reconstruction",
  "target": "0x00580cb0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00580cb0",
  "package": null,
  "subsystem": "Editor",
  "va": "0x00580cb0"
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
  "status": "candidate"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "9100b51750e334d3d546eee5e841fb77ff418148bb7d001b67efaa2ba32c7451",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00580cb0 failed: Decompilation did not complete. Reason: ",
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
  "convention": "__thiscall",
  "hidden_this": true,
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": [],
  "ordinary_stack_arguments": [],
  "receiver": true,
  "receiver_register": "ECX",
  "ret_form": "RET",
  "return_observation": "The last write to EAX before the epilogue is the CALL at 0x00580dd8, and the four instructions after it are POP EDI, POP ESI, ADD ESP,0x1024 and RET, none of which touches EAX. There is no direct call site to measure consumption against, because the body has zero incoming direct-call edges and is reached only through 0x013f57f8 + 0x54, so how the indirect callers treat the value is not measurable from this target.",
  "return_register": "EAX",
  "return_semantics": "a 4-byte opaque word in EAX, forwarded unmodified from the handle's table slot +0x04; the body writes no instruction to EAX between 0x00580dd8 and 0x00580de2",
  "return_type": "OpaqueWord",
  "return_width_bytes": 4,
  "saved_registers": "ESI and EDI, pushed at 0x00580cba/0x00580cbb and popped at 0x00580dda/0x00580ddb. No other callee-saved register is pushed or written.",
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
  "callees": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00688fa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006891f0"
    }
  ],
  "callers": [],
  "edge_rows": [
    {
      "callsite": "0x00580cc3",
      "direction": "out",
      "other": "0x00580c10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00580d08",
      "direction": "out",
      "other": "0x00688fa0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00580dc9",
      "direction": "out",
      "other": "0x006891f0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00580d95",
      "direction": "out",
      "other": "0x00692900",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00580d3f",
      "direction": "out",
      "other": "0x00692ea0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00580d84",
      "direction": "out",
      "other": "0x00692f90",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00580d9e",
      "direction": "out",
      "other": "0x00693900",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00580d36",
      "direction": "out",
      "other": "0x00693d60",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00580cdf",
      "direction": "out",
      "other": "0x00939a30",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00580cfb",
      "direction": "out",
      "other": "0x00939a30",
      "reference_type": "direct-ca
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
    "OpaqueWord"
  ],
  "vtables": [
    "vtable:0x00580df0",
    "vtable:0x013f57f8"
  ]
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
      "No original-process invocation was captured, so no live handle, no live path buffer contents and no live return value was observed. Every statement in this record is a static reading of the 3.1.0.22 image.",
      "The body is reached only through the table entry at 0x013f57f8 + 0x54, so its callers are indirect and cannot be enumerated from the binary. Whether it runs in a given play session, and with what receiver, is a runtime question.",
      "The null-handle path cannot be exercised without a filesystem that refuses the open, and the observable it would produce is a fault rather than a value.",
      "runtime validation not run"
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
  "callees": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00688fa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006891f0"
    }
  ],
  "callees_truncated": false,
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00580cc3",
      "direction": "out",
      "other": "0x00580c10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00580d08",
      "direction": "out",
      "other": "0x00688fa0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00580dc9",
      "direction": "out",
      "other": "0x006891f0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00580d95",
      "direction": "out",
      "other": "0x00692900",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00580d3f",
      "direction": "out",
      "other": "0x00692ea0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00580d84",
      "direction": "out",
      "other": "0x00692f90",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00580d9e",
      "direction": "out",
      "other": "0x00693900",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00580d36",
      "direction": "out",
      "other": "0x00693d60",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00580cdf",
      "direction": "out",
      "other": "0x00939a30",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00580cfb",
    
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
      "shared_vtable:vtable:0x013f57f8",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w2-00586700",
    "score": 12,
    "symbol": "re_00586700",
    "va": "0x00586700"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013f57f8",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-005b2490",
    "score": 12,
    "symbol": "re_005b2490",
    "va": "0x005b2490"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013f57f8",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-005ba0d0",
    "score": 12,
    "symbol": "re_005ba0d0",
    "va": "0x005ba0d0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013f57f8"
    ],
    "package": "pkg-editor-child-007f30d0",
    "score": 10,
    "symbol": "FUN_007f30d0",
    "va": "0x007f30d0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "pkg-vft-preinc-0051e340",
    "score": 8,
    "symbol": "vft_preinc_0051e340",
    "va": "0x0051e340"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "subobject-forward-0051e380",
    "score": 8,
    "symbol": "subobject_forward_0051e380",
    "va": "0x0051e380"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-00a85070",
    "score": 8,
    "symbol": "re_00a85070",
    "va": "0x00a85070"
  },
  {
    "match_basis"
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-dogfood-00580cb0-a1/.clang-format",
    "reconstruction/staging/pkg-dogfood-00580cb0-a1/dogfood_00580cb0_a1.cpp",
    "reconstruction/staging/pkg-dogfood-00580cb0-a1/dogfood_00580cb0_a1.hpp",
    "reconstruction/staging/pkg-dogfood-00580cb0-a1/dogfood_00580cb0_a1_boundary_test.sh",
    "reconstruction/staging/pkg-dogfood-00580cb0-a1/dogfood_00580cb0_a1_model_test.cpp",
    "reconstruction/staging/pkg-dogfood-00580cb0-a1/ownership.json"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-dogfood-00580cb0-a1/00580cb0.json"
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
    "Is the element width of the three path buffers really 16 bits? The two formats are written with the count 0x100 and the buffers are measured exactly 0x200 apart, so each holds at most 0x100 elements of some width. Sixteen-bit units agree with the UTF-16 literals and with 0x00580c10's own 0x100, but this body does not prove the width independently.",
    "No original-process invocation was captured, so no live handle, no live path buffer contents and no live return value was observed. Every statement in this record is a static reading of the 3.1.0.22 image.",
    "SETTLED in this attempt, removed from the open list: the frame reconciles exactly. See frame_geometry.unreconciled and frame_geometry.reconciliation. No runtime trace was needed; the prologue's two pushes had been left uncounted against the epilogue's two pops.",
    "The body is reached only through the table entry at 0x013f57f8 + 0x54, so its callers are indirect and cannot be enumerated from the binary. Whether it runs in a given play session, and with what receiver, is a runtime question.",
    "The narrow string \"Casual\" sits at 0x013f586c, immediately after the table's twenty-eight pointer slots. Is it a string constant the linker happened to place there, or is one of the slots a pointer that this analysis has misread? The four bytes at +0x74 are 43 61 73 75, which is \"Casu\" and not a plausible address, so the first reading is better supported, but the placement is unexplained.",
    "The null-handle path cannot be exercised without a filesystem that r
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-dogfood-00580cb0-a1/00580cb0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-dogfood-00580cb0-a1/.clang-format', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-dogfood-00580cb0-a1/dogfood_00580cb0_a1.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-dogfood-00580cb0-a1/dogfood_00580cb0_a1.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-dogfood-00580cb0-a1/dogfood_00580cb0_a1_boundary_test.sh', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-dogfood-00580cb0-a1/dogfood_00580cb0_a1_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-dogfood-00580cb0-a1/ownership.json', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-dogfood-00580cb0-a1/00580cb0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-dogfood-00580cb0-a1/.clang-format",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-dogfood-00580cb0-a1/dogfood_00580cb0_a1.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-dogfood-00580cb0-a1/dogfood_00580cb0_a1.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruct
[TRUNCATED]
```
