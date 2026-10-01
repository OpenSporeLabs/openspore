# Reconstruction context 0x00f96840

- Status: `complete`
- Content SHA-256: `05754f84544a7c3433d84d7b9b5650e63c16084ba42f35212f0ff5e01d2db872`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00f96840",
  "phase": "reconstruction",
  "target": "0x00f96840"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00f96840",
  "package": null,
  "subsystem": "Sporepedia",
  "va": "0x00f96840"
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
  "content_sha256": "22f645cff2fb04be49872c285007442e190e21591aa48add35db52ddda8815ea",
  "live_attempts": [],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `present`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json

void __fastcall FUN_00f96840(int *param_1)

{
  code *UNRECOVERED_JUMPTABLE;
  
  (**(code **)(*param_1 + 0x70))();
  (**(code **)(*param_1 + 0x60))();
  UNRECOVERED_JUMPTABLE = *(code **)(*param_1 + 0x84);
  param_1[0x205] = 0;
                    /* WARNING: Could not recover jumptable at 0x00f96868. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)();
  return;
}


```

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": null,
  "hidden_this": true,
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": 0,
  "receiver": "ECX carries the receiver, and this is an INFERRED determination with a real dereference history rather than a guess. The record states receiver {present true, register ECX, confidence INFERRED, shape R-ALIAS, bounds_only true, distinct_offsets 2, offsets [0, 2068], max_offset 2068, written_through 1} on inference R1, from observations obs-0002, obs-0003 and obs-0009: ECX is copied into ESI at 0x00f96841 and is dereferenced through that alias before any definite write to it. The listing corroborates it instruction by instruction: 0x00f96841 is the only read of ECX, and ECX is not written aga...",
  "ret_form": null,
  "return_register": "EAX",
  "return_semantics": "pointer_like_in_EAX",
  "return_width_bytes": null,
  "saved_registers": [
    "ESI"
  ],
  "stack_arguments": "none. stack_arguments {observed_slots 0, derived_slots 0, total_bytes 0, gaps 0, not_complete false, widths_ambiguous false, confidence APPROXIMATION}, and the fifteen instructions contain no memory operand on ESP at all: nothing is pushed for a callee and no stack word is read.",
  "stack_cleanup_bytes": null,
  "stack_cleanup_owner": null,
  "termination": "JMP EDX at 0x00f96868 (ff e2) -- a tail transfer, not a return"
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [],
  "callers": [],
  "edge_rows": [],
  "external_callees": []
}
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "openspore::reconstruction::pkg_w2_00f96840::CandidateConvention00f96840",
    "openspore::reconstruction::pkg_w2_00f96840::CleanupSide00f96840",
    "openspore::reconstruction::pkg_w2_00f96840::ConventionVerdict00f96840",
    "openspore::reconstruction::pkg_w2_00f96840::Receiver",
    "openspore::reconstruction::pkg_w2_00f96840::ReceiverRegister00f96840",
    "openspore::reconstruction::pkg_w2_00f96840::ReceiverShape00f96840",
    "openspore::reconstruction::pkg_w2_00f96840::ReturnRegisterClass00f96840"
  ],
  "vtables": [
    "vtable:0x01490be8"
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
      "no original-process trace exists in this repository; the runtime gate is open, nothing was attempted, and nothing failed"
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
  "edges": [],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 0,
  "fan_out": 0,
  "manifest_callees": [],
  "manifest_callers": [],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0570",
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
      "shared_vtable:vtable:0x01490be8"
    ],
    "package": "pkg-swarm-w2-00f999e0",
    "score": 10,
    "symbol": "re_00f999e0",
    "va": "0x00f999e0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01490be8"
    ],
    "package": "pkg-fa0d50-atomic-inc",
    "score": 10,
    "symbol": "FUN_00fa0d50",
    "va": "0x00fa0d50"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01490be8"
    ],
    "package": "pkg-swarm-w1-00fa5580",
    "score": 10,
    "symbol": "re_00fa5580",
    "va": "0x00fa5580"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01490be8"
    ],
    "package": "pkg-swarm-w1-00fa6ec0",
    "score": 10,
    "symbol": "re_00fa6ec0",
    "va": "0x00fa6ec0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01490be8"
    ],
    "package": "pkg-swarm-w1-00fa73c0",
    "score": 10,
    "symbol": "sw1_snap_and_dispatch_00fa73c0",
    "va": "0x00fa73c0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01490be8"
    ],
    "package": "pkg-swarm-w1-0104c110",
    "score": 10,
    "symbol": "re_0104c110",
    "va": "0x0104c110"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "pkg-swarm-w1-005c0dd0",
    "score": 6,
    "symbol": "re_005c0dd0",
    "va": "0x005c0dd0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "pkg-swarm-w1-006413d0",
    "score": 6,
    "symbol": "re_006413d0",
    "va": 
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-w2-00f96840/w2_00f96840.cpp",
    "reconstruction/staging/pkg-w2-00f96840/w2_00f96840_model_test.cpp",
    "reconstruction/staging/pkg-w2-00f96840/w2_00f96840_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-w2-00f96840/00f96840.json"
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
    "No original-process trace exists in this repository, so nothing here is runtime-validated. Every statement in this record is a static reading of the image and of the machine's own derived ABI record.",
    "No return type is determinable. The only exit belongs to the routine at table slot 0x84, which is outside this body, so what the caller receives in EAX is that routine's return. The record says the same: return.type null, void_possible false, and a machine return state of UNCLASSIFIED on a body with a tail exit.",
    "The calling convention is undetermined and the machine record says so. All four candidates (__cdecl, __stdcall, __thiscall, __fastcall) remain open because the body has no terminator to read a cleanup from, and nothing in these 42 bytes separates a COM/__stdcall object from a __thiscall method. A caller-side observation, a this-adjusting entry stub, or a terminator in a neighbouring function would settle it; none of those is in this record.",
    "The cleanup side and size are undetermined (cleanup.side null, cleanup.bytes null, confidence UNKNOWN). There is no RET immediate to be either, and the body pushes nothing and reads nothing on the stack, so there is no argument to account for either.",
    "The meaning of the word the body loads at 0x00f96843 beyond \"it is the base of the next displacement\" is unknown. The model treats it as a table pointer because that is the only use the fifteen instructions make of it, and it does not claim the object's own vtable identity from that.",
    "The receiver's
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /decompile_function @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-w2-00f96840/00f96840.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-w2-00f96840/w2_00f96840.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-w2-00f96840/w2_00f96840_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-w2-00f96840/w2_00f96840_types.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "GhidraMCP REST /decompile_function @ http://127.0.0.1:8089",
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
      "ref": "reconstruction/metadata/pkg-w2-00f96840/00f96840.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-w2-00f96840/w2_00f96840.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-w2-00f96840/w2_00f96840_model_test.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-w2-00f96840/w2_00f96840_types.hp
[TRUNCATED]
```
