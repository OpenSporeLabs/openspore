# Reconstruction context 0x00580cb0

- Status: `partial`
- Content SHA-256: `73d8e3424b2507e02559755ccf1cbb7f1fceedfbdc896bbbe1b0fe653a27d788`

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
  "content_sha256": "ba6c968b5a0c380ddb6d5a93eed23c3aefc26988f84e731936b302ab10ad00a4",
  "live_attempts": [],
  "live_requested": false,
  "overall": "PERSISTED"
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
    "global:NOT_AVAILABLE"
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
      "shared_types:OpaqueWord",
      "same_calling_convention"
    ],
    "package": "PKG-APP-SERVICES-SAFE-WAVE11",
    "score": 5,
    "symbol": "service_005f9230",
    "va": "0x005f9230"
  },
  {
    "match_basis": [
      "shared_types:OpaqueWord",
      "same_calling_convention"
    ],
    "package": "PKG-APP-SERVICES-SAFE-WAVE11",
    "score": 5,
    "symbol": "service_005f9310",
    "va": "0x005f9310"
  },
  {
    "match_basis": [
      "shared_types:OpaqueWord",
      "same_calling_convention"
    ],
    "package": "PKG-APP-SERVICES-SAFE-WAVE11",
    "score": 5,
    "symbol": "service_005fa8d0",
    "va": "0x005fa8d0"
  },
  {
    "match_basis": [
      "shared_types:OpaqueWord",
      "same_calling_convention"
    ],
    "package": "PKG-APP-SERVICES-SAFE-WAVE11",
    "score": 5,
    "symbol": "service_005fc330",
    "va": "0x005fc330"
  },
  {
    "match_basis": [
      "shared_types:OpaqueWord",
      "same_calling_convention"
    ],
    "package": "PKG-12-SIM-SPACE",
    "score": 5,
    "symbol": "FUN_00aeb160",
    "va": "0x00aeb160"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x013f57f8"
    ],
    "package": "PKG-EDITOR-INPUT-WAVE6",
    "score": 4,
    "symbol": "editor_input_005737d0",
    "va": "0x005737d0"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x013f57f8"
    ],
    "package": "PKG-EDITOR-INPUT-WAVE6",
    "score": 4,
    "symbol": "editor_input_00585890",
    "va": "0x00585890"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x013f57f8"
    ],
    "package": "PKG-EDITOR-INPUT-WAVE6",
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
    "The body is reached only through the table entry at 0x013f57f8 + 0x54, so its callers are indirect and cannot be enumerated from the binary. Whether it runs in a given play session, and with what receiver, is a runtime question.",
    "The frame-size reconciliation. 0x011e0700's nineteen instructions leave the stack pointer 0x1024 below entry, while the epilogue releases two pops plus 0x1024, four bytes more. The alternative reading balances the epilogue but shifts every local address by four and pushes the sink past the top of the block. The local geometry is self-consistent only under the adopted reading, so the byte accounting stays open and the model asserts only the return form. A runtime trace of the original would decide it.",
    "The narrow string \"Casual\" sits at 0x013f586c, immediately after the table's twenty-eight pointer slots. Is it a string constant the linker happened to place there, or is one of the slots a pointer that this analysis has misr
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'ref': 'ephemeral reconstruction_knowledge.build_index', 'mode': 'derived', 'source_class': 'generated_index'}, {'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'mode': 'persisted', 'source_class': 'committed_artifact'}, {'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'mode': 'persisted', 'source_class': 'committed_artifact'}, {'ref': 'reconstruction/metadata/pkg-dogfood-00580cb0-a1/00580cb0.json', 'mode': 'persisted', 'source_class': 'committed_artifact'}, {'ref': 'reconstruction/staging/pkg-dogfood-00580cb0-a1/.clang-format', 'mode': 'persisted', 'source_class': 'committed_artifact'}, {'ref': 'reconstruction/staging/pkg-dogfood-00580cb0-a1/dogfood_00580cb0_a1.cpp', 'mode': 'persisted', 'source_class': 'committed_artifact'}, {'ref': 'reconstruction/staging/pkg-dogfood-00580cb0-a1/dogfood_00580cb0_a1.hpp', 'mode': 'persisted', 'source_class': 'committed_artifact'}, {'ref': 'reconstruction/staging/pkg-dogfood-00580cb0-a1/dogfood_00580cb0_a1_boundary_test.sh', 'mode': 'persisted', 'source_class': 'committed_artifact'}, {'ref': 'reconstruction/staging/pkg-dogfood-00580cb0-a1/dogfood_00580cb0_a1_model_test.cpp', 'mode': 'persisted', 'source_class': 'committed_artifact'}, {'ref': 'reconstruction/staging/pkg-dogfood-00580cb0-a1/ownership.json', 'mode': 'persisted', 'source_class': 'committed_artifact'}`

```json
{
  "provenance": [
    {
      "mode": "derived",
      "ref": "ephemeral reconstruction_knowledge.build_index",
      "source_class": "generated_index"
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
      "ref": "reconstruction/staging/pkg-dogfood-00580cb0-a1/dogfood_00580cb0_a1_boundary_test.sh",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-dogfood-00580cb0-a1/dogfood_00580cb0_a1_model_test.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-dogfood-00580cb0-a1/ownership.json",

[TRUNCATED]
```
