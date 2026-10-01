# Reconstruction context 0x01053e00

- Status: `complete`
- Content SHA-256: `dd3bb4649c8edd4fae725792cf8be6ac729eadb1c04cd6cdd618530fd1907e15`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x01053e00",
  "phase": "reconstruction",
  "target": "0x01053e00"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_01053e00",
  "package": null,
  "subsystem": "Simulator",
  "va": "0x01053e00"
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
  "content_sha256": "b52c3ceda45e9fd3d9b0ebdd779161c4c18949cd88b8e3dc65b20ebf0f66fbe7",
  "live_attempts": [],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `present`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json

undefined4 FUN_01053e00(int param_1)

{
  char cVar1;
  int *piVar2;
  undefined4 unaff_retaddr;
  undefined1 auStack_c [12];
  
  if (*(int **)(param_1 + 0x124) != (int *)0x0) {
    cVar1 = (**(code **)(**(int **)(param_1 + 0x124) + 0x2c))();
    if ((cVar1 != '\0') && (piVar2 = *(int **)(param_1 + 0x124), piVar2 != (int *)0x0)) {
      *(undefined4 *)(param_1 + 0x124) = 0;
      (**(code **)(*piVar2 + 4))();
    }
  }
  if (*(int *)(param_1 + 0x124) == 0) {
    return 0;
  }
  if (*(int **)(param_1 + 0x114) != (int *)0x0) {
    piVar2 = (int *)(**(code **)(**(int **)(param_1 + 0x114) + 0xb8))(&PTR_LAB_013f94d4);
    if (piVar2 != (int *)0x0) {
      (**(code **)(*piVar2 + 0x30))(auStack_c);
      goto LAB_01053e7f;
    }
  }
  (**(code **)(**(int **)(param_1 + 0x114) + 0x2c))();
LAB_01053e7f:
  (**(code **)(*(int *)(*(int *)(param_1 + 0x124) + 0x34) + 0x38))(&stack0xffffffe4);
  FUN_00cb5930(unaff_retaddr);
  return 1;
}


```

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": [
    "__stdcall by machine shape; the record's own derived conventions block abstains",
    "Observed MSVC x86 virtual-member convention already established for this table by the sibling reconstruction of 0x01053db0: the receiver is NOT in ECX but is the first callee-popped stack argument, read as MOV ESI,[ESP+0x20] at 0x01053e04 after SUB ESP,0x18 / PUSH ESI. ECX is used only to carry the receiver of each inner virtual."
  ],
  "hidden_this": false,
  "receiver_register": "none. The machine record's receiver sub-record names no register and enumerates no offsets, with reason ecx_reassigned_before_deref. That is accurate about the DERIVATION (ECX is reassigned at 0x01053e08 before it is ever dereferenced) and it says nothing about the body reaching no fields, which it plainly does. See `contradictions`.",
  "ret_form": "RET 0x8",
  "return_register": "AL",
  "return_type": "bool",
  "return_width_bytes": 1,
  "saved_registers": [
    "ESI"
  ],
  "stack_arguments": [
    "{'evidence': 'MOV ESI,[ESP+0x20] at 0x01053e04 with the prologue already applied, and MOV ECX,[ESP+0x24] at 0x01053eb4 reloading the same word', 'index': 0, 'offset_hex': '0x04', 'role': 'receiver; the object whose fields at +0x114 and +0x124 are read'}",
    "{'evidence': 'no instruction in the 65-instruction body reads [ESP+0x08] relative to the entry stack pointer, yet RET 0x8 at 0x01053eca and 0x01053ed3 clean eight bytes', 'index': 1, 'offset_hex': '0x08', 'role': 'second callee-popped stack word; never read by this body'}"
  ],
  "stack_cleanup_b
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
      "callsite": "0x01053ebf",
      "direction": "out",
      "other": "0x00cb5930",
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
    "global:0x013f94d4",
    "global:WARN"
  ],
  "types": [
    "OpaqueBeamTarget",
    "OpaqueBeamToolState",
    "bool"
  ],
  "vtables": [
    "vtable:0x00c6a960",
    "vtable:0x0149b810",
    "vtable:0x0149b8b4",
    "vtable:0x0149b900",
    "vtable:0x0149ba30"
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
      "callsite": "0x01053ebf",
      "direction": "out",
      "other": "0x00cb5930",
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
    "id": "scc-0610",
    "size": 1
  },
  "vtable_reference_count": 1
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
      "shared_vtable:vtable:0x0149b810,vtable:0x0149b8b4"
    ],
    "package": "pkg-sim-toolevent-01053d50",
    "score": 10,
    "symbol": "sim_toolevent_slot8_fun_01053d50",
    "va": "0x01053d50"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-11-H4-HELPER-WAVE3",
    "score": 6,
    "symbol": "address_window_offset_005c65e0",
    "va": "0x005c65e0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-SIMULATOR-SAFE-WAVE11",
    "score": 6,
    "symbol": "dispatch_key_00628450",
    "va": "0x00628450"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-SIMULATOR-SAFE-WAVE11",
    "score": 6,
    "symbol": "cycle_key_006286a0",
    "va": "0x006286a0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-SIMULATOR-SAFE-WAVE11",
    "score": 6,
    "symbol": "release_child_0062c910",
    "va": "0x0062c910"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 6,
    "symbol": "FUN_00b3d2a0",
    "va": "0x00b3d2a0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 6,
    "symbol": "FUN_00b3d300",
    "va": "0x00b3d300"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 6,
    "symbol": "Simulator_GetUIMissionLogManager",
    "va": "0x00b3d4f0"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-dfw-01053e00/dfw_01053e00.cpp",
    "reconstruction/staging/pkg-dfw-01053e00/dfw_01053e00_model_test.cpp",
    "reconstruction/staging/pkg-dfw-01053e00/dfw_01053e00_types.hpp",
    "reconstruction/staging/pkg-sim-beamtool-func5/beam_tool_func5_01053e00.cpp",
    "reconstruction/staging/pkg-sim-beamtool-func5/beam_tool_func5_01053e00.hpp",
    "reconstruction/staging/pkg-sim-beamtool-func5/beam_tool_func5_01053e00_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-dfw-01053e00/01053e00.json",
    "reconstruction/metadata/pkg-sim-beamtool-func5/01053e00.json"
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
    "Is the 0x01053e27 store before 0x01053e36 an ownership transfer or a bug? The store zeroes the receiver's word while ECX still holds the pointer, so the release-shaped transfer at 0x01053e36 is reached through a receiver that no longer names the object. That is what the listing does and the model reproduces it. Whether it is intended cannot be settled from this body, and the sibling at 0x01053db0 was not consulted for intent -- only for the frame shape.",
    "Is the 0x01053e4d path -- a null word at 0x114 falling into a block that dereferences it with no test -- reachable in the original? The model reproduces the absence of the test and the model test does not enter that path. Whether any real caller can reach it needs a runtime observation, and this body has no recorded caller.",
    "The 12-byte buffer passed to the found object's vtable word at +0x30 is written by the callee but never read back by this body, which consumes the returned pointer instead. Whether that buffer is a genuine second output or a compiler artifact of the callee's prototype is not resolvable from this function alone.",
    "The commit helper 0x00cb5930 uses this function's own receiver word as a fallback pointer to three floats, which reads the first twelve bytes of the receiver object. That is what the listing does and it is staged verbatim, but it looks like an argument mix-up in the original; whether the caller ever reaches that fallback is unknown.",
    "The eight code pointers stored at 0x013f94d4 are recorded as observed bytes but are de
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /decompile_function @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-dfw-01053e00/01053e00.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-sim-beamtool-func5/01053e00.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-dfw-01053e00/dfw_01053e00.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-dfw-01053e00/dfw_01053e00_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-dfw-01053e00/dfw_01053e00_types.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-sim-beamtool-func5/beam_tool_func5_01053e00.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-sim-beamtool-func5/beam_tool_func5_01053e00.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-sim-beamtool-func5/beam_tool_func5_01053e00_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-dfw-01053e00/01053e00.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg-sim-beamtool-func5/01053e00.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-dfw-01053e00/dfw_01053e00.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-dfw-01053e00/dfw_01053e00_model_te
[TRUNCATED]
```
