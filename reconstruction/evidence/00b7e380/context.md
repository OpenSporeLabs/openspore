# Reconstruction context 0x00b7e380

- Status: `partial`
- Content SHA-256: `bad6cef1fe01a177d4f1e7d374fbd81f863fe9dbb0e635fc091d3e2924d12c64`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00b7e380",
  "phase": "reconstruction",
  "target": "0x00b7e380"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00b7e380",
  "package": "pkg-00b7e380-member-ptr-0x2c",
  "subsystem": "Sporepedia",
  "va": "0x00b7e380"
}
```

## 03_current_status

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "blocked": false,
  "reconstructed": true,
  "runtime_gated": true,
  "runtime_validated": 0,
  "status": "reconstructed"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "9fb92e02083b9e7d48ca7374d98ceff66fc30353089a04bf59b5ce21d7915b21",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00b7e380 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "thiscall (V1-VFT: vptr-backed vftable slot 38, callee pops nothing, no stack word read as argument)",
  "ordinary_stack_argument_slots": 0,
  "ordinary_stack_arguments": [],
  "receiver": "ECX, used as the base of the single computation `LEA EAX,[ECX + 0x2c]` at 0x00b7e380; never saved to another register and never read from",
  "ret_form": "RET",
  "return_register": "EAX",
  "return_semantics": "pointer to a member at offset 0x2c of the receiver",
  "return_type": "void*",
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller"
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
      "va": "0x005c7500"
    },
    {
      "name": "ProfilePersistenceBoundary_run_candidate_00b28ec0",
      "reconstructed": true,
      "va": "0x00b28ec0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b5ba30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c82f00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d17250"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fdc710"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fdc800"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fdeac0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fe0160"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fe0e10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x010249f0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x005c7653",
      "direction": "in",
      "other": "0x005c7500",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00b291fc",
      "direction": "in",
      "other": "0x00b28ec0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00b5ba64",
      "direction": "in",
      "other": "0x00b5ba30",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c82f27",
      "direction": "in",
      "other": "0x00c82f00",
      "reference_type": "dir
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "medium (machine says void*; the member's type is unverifiable)",
    "openspore::reconstruction::pkg_00b7e380_member_ptr_0x2c::AbiMemberPtr00b7e380",
    "openspore::reconstruction::pkg_00b7e380_member_ptr_0x2c::Opaque",
    "openspore::reconstruction::pkg_00b7e380_member_ptr_0x2c::OpaqueReceiver",
    "openspore::reconstruction::pkg_00b7e380_member_ptr_0x2c::OpaqueReceiverVTable",
    "void*"
  ],
  "vtables": [
    "vtable:0x013ff648",
    "vtable:0x013ff6ac",
    "vtable:0x01462764",
    "vtable:0x014627bc",
    "vtable:0x0147ca30",
    "vtable:0x0147ca70",
    "vtable:0x0147caf8",
    "vtable:0x0147cbbc",
    "vtable:0x0147cc14",
    "vtable:0x01489090",
    "vtable:0x014890f4",
    "vtable:0x014893b0"
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
      "confirm the class identity behind the three vtable images; the binary has no MSVC RTTI",
      "observe one real virtual call through a slot +0x98 word and record whether the caller consumes EAX",
      "record the receiver allocation size at runtime; the 0x30 byte modelled extent is only the prefix through the reached slot",
      "record the value at receiver+0x2c and find its consumer, to establish the member's type"
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
      "va": "0x005c7500"
    },
    {
      "name": "ProfilePersistenceBoundary_run_candidate_00b28ec0",
      "reconstructed": true,
      "va": "0x00b28ec0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b5ba30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c82f00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d17250"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fdc710"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fdc800"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fdeac0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fe0160"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fe0e10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x010249f0"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x005c7653",
      "direction": "in",
      "other": "0x005c7500",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00b291fc",
      "direction": "in",
      "other": "0x00b28ec0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00b5ba64",
      "direction": "in",
      "other": "0x00b5ba30",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c82f27
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
      "shared_types:void*",
      "shared_vtable:vtable:0x013ff648,vtable:0x013ff6ac"
    ],
    "package": "pkg-swarm-w1-00641fd0",
    "score": 13,
    "symbol": "sporepedia_cached_handle_00641fd0",
    "va": "0x00641fd0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_types:void*",
      "shared_vtable:vtable:0x013ff648,vtable:0x01462764"
    ],
    "package": "pkg-vft-slot-006e64f0",
    "score": 13,
    "symbol": "re_006e64f0",
    "va": "0x006e64f0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013ff648,vtable:0x013ff6ac"
    ],
    "package": "pkg-swarm-w1-005c0dd0",
    "score": 10,
    "symbol": "re_005c0dd0",
    "va": "0x005c0dd0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013ff648,vtable:0x01462764"
    ],
    "package": "pkg-swarm-w1-006413d0",
    "score": 10,
    "symbol": "re_006413d0",
    "va": "0x006413d0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013ff648,vtable:0x01462764"
    ],
    "package": "pkg-swarm-w1-00641410",
    "score": 10,
    "symbol": "re_00641410",
    "va": "0x00641410"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013ff648,vtable:0x01462764"
    ],
    "package": "pkg-swarm-w1-00641780",
    "score": 10,
    "symbol": "re_00641780",
    "va": "0x00641780"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013ff648,vtable:0x013ff6ac"
    ],
    "package": "pkg-swarm-w1-006417d0"
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-00b7e380-member-ptr-0x2c/member_ptr_0x2c_00b7e380.cpp",
    "reconstruction/staging/pkg-00b7e380-member-ptr-0x2c/member_ptr_0x2c_00b7e380.hpp",
    "reconstruction/staging/pkg-00b7e380-member-ptr-0x2c/member_ptr_0x2c_00b7e380_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-00b7e380-member-ptr-0x2c/00b7e380.json"
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
    "The class identity behind the three vtable images; the binary has no MSVC RTTI.",
    "The real allocation size of the receiver object; 0x30 is only the modelled prefix through the reached slot.",
    "The type of the member at offset 0x2c: whether it is an int, a pointer, a char buffer or a sub-object. No instruction in this body reads or writes it, and no consumer is reachable from here.",
    "confirm the class identity behind the three vtable images; the binary has no MSVC RTTI",
    "observe one real virtual call through a slot +0x98 word and record whether the caller consumes EAX",
    "record the receiver allocation size at runtime; the 0x30 byte modelled extent is only the prefix through the reached slot",
    "record the value at receiver+0x2c and find its consumer, to establish the member's type"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-00b7e380-member-ptr-0x2c/00b7e380.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-00b7e380-member-ptr-0x2c/member_ptr_0x2c_00b7e380.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-00b7e380-member-ptr-0x2c/member_ptr_0x2c_00b7e380.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-00b7e380-member-ptr-0x2c/member_ptr_0x2c_00b7e380_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-00b7e380-member-ptr-0x2c/00b7e380.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-00b7e380-member-ptr-0x2c/member_ptr_0x2c_00b7e380.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-00b7e380-member-ptr-0x2c/member_ptr_0x2c_00b7e380.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-00b7e380-member-ptr-0x2c/member_ptr_0x2c_00b7e380_model_test.cpp",
      "source_class": "committed_artifact"
    }
  ]
[TRUNCATED]
```
