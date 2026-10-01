# Reconstruction context 0x00b1fbf0

- Status: `partial`
- Content SHA-256: `1016a723f590ab23a869696de3c1e430aed117d1b56feba7e217115a6b10fd09`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00b1fbf0",
  "phase": "reconstruction",
  "target": "0x00b1fbf0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00b1fbf0",
  "package": null,
  "subsystem": "Editor",
  "va": "0x00b1fbf0"
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
  "content_sha256": "99f94b431be6bf704c07e192b4fe404261e565d8c3d59f325f7753407f95afce",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00b1fbf0 failed: Decompilation did not complete. Reason: ",
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
  "hidden_receiver": "unread",
  "hidden_this_register": "ECX is the register V1-VFT names as carrying the receiver, and 0x00b1fbf0 never reads it: the two instructions mention no register other than AL. The port therefore carries a receiver the body discards.",
  "ordinary_stack_argument_slots": 0,
  "receiver": false,
  "ret_form": "RET",
  "return_observation": "0x00b1fbf0: MOV AL,0x1 writes only the low byte of EAX, so bits 8..31 of EAX are left as the caller left them rather than zeroed. Every consumer inspected tests the AL byte and never the full dword, and 0x00e81139 goes further and compares it against the immediate 1 (CMP AL,0x1), which is what makes the one-byte width falsifiable rather than decorative. The derived return record names register EAX and register_class integral and names NO width and NO type; the one-byte width here is established from the opcode (B0 is MOV r8,imm8, whose register field is fixed at AL), not copied from a recor...",
  "return_register": "EAX",
  "return_semantics": "std::uint8_t",
  "return_type": "std::uint8_t",
  "return_width_bytes": 1,
  "saved_registers": [],
  "stack_arguments": [],
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
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007f53d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0082c210"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0096a670"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0096b3a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0097c6d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0098cc70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0098f3d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00993fa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00a43050"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00a51f40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ccefb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d73ca0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e0eab0"
    },
    {
      "name": "cell_mode_strategy_on_mouse_wheel_00e7d660",
      "reconstructed": true,
      "va": "0x00e7d660"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e81120"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ee8860"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x007f53fe",
      "direction": "in",
      "other": "0x007f53d0",
      
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "std::uint8_t"
  ],
  "vtables": [
    "vtable:0x013f57f8",
    "vtable:0x013f625c",
    "vtable:0x013f85a4",
    "vtable:0x013fc06c",
    "vtable:0x013fc1a4",
    "vtable:0x013fc474",
    "vtable:0x013fc6cc",
    "vtable:0x013fc6f4",
    "vtable:0x013fc744",
    "vtable:0x013fc854",
    "vtable:0x013fcc08",
    "vtable:0x013fcc48"
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
      "No original-process trace has been captured for 0x00b1fbf0, so every claim here is static. A runtime differential test must confirm that the answer is still 1 in the shipping build and that no runtime patch retargets the address.",
      "The 0x00ee8860 virtual dispatch site must be observed with a concrete receiver before the slot's owning class can be named."
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
      "va": "0x007f53d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0082c210"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0096a670"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0096b3a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0097c6d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0098cc70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0098f3d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00993fa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00a43050"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00a51f40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ccefb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d73ca0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e0eab0"
    },
    {
      "name": "cell_mode_strategy_on_mouse_wheel_00e7d660",
      "reconstructed": true,
      "va": "0x00e7d660"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e81120"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ee8860"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "
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
    "reconstruction/staging/pkg-shared-default-true-wave12/b1fbf0_default_true.cpp",
    "reconstruction/staging/pkg-shared-default-true-wave12/b1fbf0_default_true.hpp",
    "reconstruction/staging/pkg-shared-default-true-wave12/b1fbf0_default_true_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-shared-default-true-wave12/00b1fbf0.json"
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
    "Is the address a compiler-folded COMDAT shared by many unrelated 'return true' defaults, or a single default deliberately emitted once? Both fit every observation.",
    "Is the always-true body a shipped default, a build-configuration stub, or a patch target at runtime? No differential trace has been captured for this function, so runtime patching cannot be excluded.",
    "No original-process trace has been captured for 0x00b1fbf0, so every claim here is static. A runtime differential test must confirm that the answer is still 1 in the shipping build and that no runtime patch retargets the address.",
    "The 0x00ee8860 virtual dispatch site must be observed with a concrete receiver before the slot's owning class can be named.",
    "The 356 and 20 vtable-reference counts are raw pointer-scan totals, not proven distinct vtables. The true count is unmeasured. A scan of the image's own .rdata for the little-endian dword of this address finds 521 occurrences, and .data finds 17; those are also raw totals and are not a table count.",
    "The Spore-ModAPI correspondence to IGameMode::func0Ch is a CANDIDATE for the 0x01485550 table only, recorded in sdk_correspondence and deliberately not asserted. Four offsets across three tables are why.",
    "The six ECX receipt sites establish that a value is in ECX at the transfer. They do NOT establish that the body reads it, and the record's R2 says it does not. Whether the six sites pass the same object or six different ones is not determinable from the call sites alone.",
    "Wha
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-shared-default-true-wave12/00b1fbf0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-shared-default-true-wave12/b1fbf0_default_true.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-shared-default-true-wave12/b1fbf0_default_true.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-shared-default-true-wave12/b1fbf0_default_true_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-shared-default-true-wave12/00b1fbf0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-shared-default-true-wave12/b1fbf0_default_true.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-shared-default-true-wave12/b1fbf0_default_true.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-shared-default-true-wave12/b1fbf0_default_true_model_test.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "re
[TRUNCATED]
```
