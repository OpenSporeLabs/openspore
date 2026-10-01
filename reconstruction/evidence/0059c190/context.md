# Reconstruction context 0x0059c190

- Status: `partial`
- Content SHA-256: `fb86024cd4b3a6512a4049b98ef63fadb5ee029b381b8135b5f399343785350c`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x0059c190",
  "phase": "reconstruction",
  "target": "0x0059c190"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "QuaternionToMatrix",
  "package": null,
  "subsystem": "GameGlobal",
  "va": "0x0059c190"
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
  "content_sha256": "5aef5a1d4232368733d3259b2c9306b7f343a22213fb876fd879e32fe79f882e",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x0059c190 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "__cdecl (no callee stack cleanup)",
  "hidden_receiver": "none",
  "hidden_this_register": "ECX is not read on entry; it is written at 0x0059c2c1 for the single callee",
  "ordinary_stack_argument_slots": 2,
  "receiver": false,
  "ret_form": "RET (bare, no immediate)",
  "return_note": "(the destination pointer, unchanged)",
  "return_observation": "0x0059c295 MOV ESI,dword ptr [ESP+0x38] loads stack argument 0 into ESI; 0x0059c2e0 MOV EAX,ESI returns it. XMM0 is not live on exit: its last write is the 2.0f constant load at 0x0059c217.",
  "return_register": "EAX",
  "return_semantics": "returns stack argument 0 unchanged, i.e. the buffer the 36-byte result was written into; nothing is returned by value in registers",
  "return_type": "Opaque59c190Float3x3*",
  "return_width_bytes": 4,
  "saved_registers": [
    "ESI (pushed 0x0059c193, popped 0x0059c2e2)"
  ],
  "stack_arguments": [
    {
      "address_at_entry": "[ESP_entry + 0x4]",
      "loaded_by": "0x0059c295 MOV ESI,dword ptr [ESP + 0x38]",
      "role": "destination of the 36-byte result; also passed as ECX to 0x0041cb40",
      "slot": 0
    },
    {
      "address_at_entry": "[ESP_entry + 0x8]",
      "loaded_by": "0x0059c194 MOV EAX,dword ptr [ESP + 0x3c]",
      "role": "const float[4] quaternion (x, y, z, w) read at +0x00, +0x04, +0x08, +0x0c",
      "slot": 1
    }
  ],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "0x0059c2e6 RET, unconditional, single exit"
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
      "va": "0x0059d610"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005b1e30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005d8f10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x009c6fc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ad12a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae46f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b02fa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b134a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b3f3a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b421b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b45ca0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b81780"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b81a40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b94150"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b998a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba0080"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x0059d791",
      "direction": "in",
      "other": "0x0059d610",
      "reference_type": "direct-call"
    },

[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "Opaque59c190Float3x3* (the destination pointer, unchanged)"
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
      "A differential test must also confirm that at least one caller supplies a unit quaternion, since the body has no normalisation and produces a non-orthonormal matrix otherwise.",
      "A differential test must confirm that the destination really receives the same 36 bytes at run time, i.e. that no runtime patch retargets 0x0041cb40 or the two float constants.",
      "No original-process trace exists for 0x0059c190. Every statement here is static."
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
      "va": "0x0059d610"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005b1e30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005d8f10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x009c6fc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ad12a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae46f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b02fa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b134a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b3f3a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b421b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b45ca0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b81780"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b81a40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b94150"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b998a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba0080"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bc2900"
    },
    {
      "name": null,
      "reconst
[TRUNCATED]
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 6,
    "symbol": "FUN_00ff3f00",
    "va": "0x00ff3f00"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-13-C4-CREATURE-WAVE3",
    "score": 3,
    "symbol": "Simulator_cCreatureBase_CreateAndStartPool2Effect_00c1d460",
    "va": "0x00c1d460"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/wave13-pilot-gameglobal-b03/59c190_quaternion_to_float3x3.cpp",
    "reconstruction/staging/wave13-pilot-gameglobal-b03/59c190_quaternion_to_float3x3.hpp",
    "reconstruction/staging/wave13-pilot-gameglobal-b03/59c190_quaternion_to_float3x3_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-pilot-gameglobal-b03/0059c190.json"
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
    "A differential test must also confirm that at least one caller supplies a unit quaternion, since the body has no normalisation and produces a non-orthonormal matrix otherwise.",
    "A differential test must confirm that the destination really receives the same 36 bytes at run time, i.e. that no runtime patch retargets 0x0041cb40 or the two float constants.",
    "Do all 113+ call sites pass a unit quaternion, or does the engine rely on this being a raw formula? Static analysis cannot answer that; it needs a runtime trace or a caller-by-caller normalisation audit.",
    "Is the quaternion actually stored as (x,y,z,w) in the caller's struct, or does some caller pass a (w,x,y,z) quaternion that the engine happens to treat correctly? The formula constrains the order, but not the caller's intent.",
    "Is this Quaternion::ToMatrix() itself, a free helper that Quaternion::ToMatrix() calls, or a static member? The argument shape rules out a thiscall member but not the first two.",
    "No original-process trace exists for 0x0059c190. Every statement here is static.",
    "What are the other two addresses labelled QuaternionToMatrix (0x0059bef0, 0x004a9a40) in this build, and are their bodies identical? 0x0059bef0 is not a function start in 3.1.0.22 and 0x004a9a40 was not inspected in this batch.",
    "What is the destination type? Only size 36 and a three-float3 layout are observed. 'Math::Matrix3' is a candidate from Spore ModAPI/Spore/MathUtils.h, not a proven identity.",
    "Why does the body spill q.x*q.z into its own i
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-pilot-gameglobal-b03/0059c190.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-pilot-gameglobal-b03/59c190_quaternion_to_float3x3.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-pilot-gameglobal-b03/59c190_quaternion_to_float3x3.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-pilot-gameglobal-b03/59c190_quaternion_to_float3x3_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave13-pilot-gameglobal-b03/0059c190.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-pilot-gameglobal-b03/59c190_quaternion_to_float3x3.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-pilot-gameglobal-b03/59c190_quaternion_to_float3x3.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-pilot-gameglobal-b03/59c190_quaternion_to_float3x3_model_test.cpp",
      "source_class": "committed_artifact
[TRUNCATED]
```
