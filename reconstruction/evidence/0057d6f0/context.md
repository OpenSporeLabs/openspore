# Reconstruction context 0x0057d6f0

- Status: `partial`
- Content SHA-256: `bc738f10de057d84d17f5ef933afeb0a8e0891b4143f5ea9e26cf9acc016100c`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x0057d6f0",
  "phase": "reconstruction",
  "target": "0x0057d6f0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_0057d6f0",
  "package": null,
  "subsystem": "Editor",
  "va": "0x0057d6f0"
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
  "content_sha256": "d517f88a7bd13c7441a255bfada0c7fdcfd1a971da67c4ee6d6aec42748a62c3",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x0057d6f0 failed: Decompilation did not complete. Reason: ",
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
  "receiver": "ECX carries the receiver. The record says so at INFERRED confidence: receiver {present true, register ECX, provenance vftable_slot_dispatch, bounds_only true, shape null, distinct_offsets 0, written_through 0}. In the body itself the receiver is read once, MOV ESI,ECX at 0x0057d6f1, and aliased into ESI so that it survives both calls; the SAME VALUE then goes to 0x00579e20 in ECX (unchanged) and to 0x00f47380 on the stack (unchanged), and what MOV EAX,ESI at 0x0057d708 writes into EAX is that value and nothing else. It is NOT dereferenced anywhere in the eleven instructions: there is no loa...",
  "receiver_register": "ECX",
  "ret_form": "RET 0x4",
  "return_observation": "The record classifies the last write to EAX as aggregate_unknown (RT2) and the envelope as unclassified_in_EAX. The listing says more than that and this package reads only the listing: the single write to EAX is MOV EAX,ESI at 0x0057d708, a register-to-register move of the value ESI has held since 0x0057d6f1, so the returned value is the incoming receiver verbatim and 32 bits wide. Both paths to the single reachable RET pass through 0x0057d708, so the must-analysis has no uninitialised path. The C type is Receiver *, which is the width-computable spelling of a 4-byte value that the machine ...",
  "return_register": "EAX",
  "return_semantics": "unclassified_in_EAX",
  "saved_registers": [
    "ESI"
  ],
  "stack_cleanup_bytes": 4
[TRUNCATED]
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
      "callsite": "0x0057d6f3",
      "direction": "out",
      "other": "0x00579e20",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0057d700",
      "direction": "out",
      "other": "0x00f47380",
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
    "global:0x013f57f8"
  ],
  "types": [
    "Receiver *",
    "openspore::reconstruction::pkg_editor_w1_0057d6f0::CleanupSide57d6f0",
    "openspore::reconstruction::pkg_editor_w1_0057d6f0::ConventionConfidence",
    "openspore::reconstruction::pkg_editor_w1_0057d6f0::ConventionVerdict57d6f0",
    "openspore::reconstruction::pkg_editor_w1_0057d6f0::OptionWord",
    "openspore::reconstruction::pkg_editor_w1_0057d6f0::Receiver",
    "openspore::reconstruction::pkg_editor_w1_0057d6f0::ReceiverProvenance57d6f0",
    "openspore::reconstruction::pkg_editor_w1_0057d6f0::ReceiverRegister57d6f0"
  ],
  "vtables": [
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
      "runtime validation not run: no original-process trace exists in this repository, so nothing about the original game has been observed for this VA"
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
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x0057d6f3",
      "direction": "out",
      "other": "0x00579e20",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0057d700",
      "direction": "out",
      "other": "0x00f47380",
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
    "id": "scc-0069",
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
    "reconstruction/staging/pkg-editor-w1-0057d6f0/editor_w1_0057d6f0.cpp",
    "reconstruction/staging/pkg-editor-w1-0057d6f0/editor_w1_0057d6f0_model_test.cpp",
    "reconstruction/staging/pkg-editor-w1-0057d6f0/editor_w1_0057d6f0_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-editor-w1-0057d6f0/0057d6f0.json"
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
    "Runtime. No original-process trace exists in this repository for this target, so nothing is claimed there. The gate is open, nothing was attempted, and nothing failed.",
    "The decompiler did not run for this target: the collector recorded ghidra_rest_error 'decompile 0x0057d6f0 failed: Decompilation did not complete', and 0x00579e20 and 0x00f47380 also fail to decompile through the bridge. Every claim above is therefore from the disassembly, the raw bytes and the xref export, never from pseudocode.",
    "The option word's meaning, and the 31 bits this body never reads. Bit 0 selects the dispose; nothing in these 11 instructions says what a set bit 0 means, and no caller is statically visible (all four references are a table slot and three stubs), so no call site supplies a value to read the meaning from.",
    "The receiver's identity. Whether the incoming ECX points at the head of an object or at one of at least three interior sub-objects is not determinable from this body: it neither dereferences the pointer nor adjusts it, and the stubs that reach it adjust by 0x10, 0x14 and 0x4, so at least three base-subobject displacements are in play for the same virtual. Which class, and whether the three stubs are one class's three bases or three classes' thunks, is not decided here and this binary carries no MSVC RTTI to decide it.",
    "Whether the INFERRED convention is the right one in an absolute sense. The derived record DETERMINES __thiscall (rule R1-VFT for the receiver, rule C6B for the convention) and this package
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-editor-w1-0057d6f0/0057d6f0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-editor-w1-0057d6f0/editor_w1_0057d6f0.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-editor-w1-0057d6f0/editor_w1_0057d6f0_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-editor-w1-0057d6f0/editor_w1_0057d6f0_types.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-editor-w1-0057d6f0/0057d6f0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-editor-w1-0057d6f0/editor_w1_0057d6f0.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-editor-w1-0057d6f0/editor_w1_0057d6f0_model_test.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-editor-w1-0057d6f0/editor_w1_0057d6f0_types.hpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruct
[TRUNCATED]
```
