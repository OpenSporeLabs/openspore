# Reconstruction context 0x01053db0

- Status: `complete`
- Content SHA-256: `73d3523f318a8be15a74fd91f71a700657b0ec5890fbf7b30bbac4b387c34a53`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x01053db0",
  "phase": "reconstruction",
  "target": "0x01053db0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "Simulator::cDefaultBeamTool::func4Ch",
  "package": null,
  "subsystem": "Simulator",
  "va": "0x01053db0"
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
  "status": "queued"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "7873fecaed9f37ddc25e1a878eac1f4ab8c59045adcdc63af21b188c62947492",
  "live_attempts": [],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `present`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json

/* WARNING: Unknown calling convention */
/* WARNING: Enum "ObjectTYPE": Some values do not have unique names */
/* WARNING: Enum "Names": Some values do not have unique names */

bool Simulator__cDefaultBeamTool__func4Ch
               (cDefaultBeamTool *this,cSpaceToolData *pTool,Vector3 *param_3)

{
  DefaultRefCounted__vftable *pDVar1;
  char cVar2;
  
  if (this[0x18]._vftable1 != (DefaultRefCounted__vftable *)0x0) {
    FUN_00cb3c70();
    pDVar1 = this[0x18]._vftable1;
    if (pDVar1 != (DefaultRefCounted__vftable *)0x0) {
      this[0x18]._vftable1 = (DefaultRefCounted__vftable *)0x0;
      (**(code **)(pDVar1->_virtual_dtor + 4))();
    }
  }
  cVar2 = FUN_0104cd50();
  if (cVar2 != '\0') {
    Simulator__cRelationshipManager__Get();
    FUN_00b78860();
  }
  return true;
}


```

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": [
    "__stdcall",
    "MSVC x86 virtual-member convention observed: the receiver is passed as the first stack argument and the callee pops it"
  ],
  "hidden_this": false,
  "hidden_this_register": null,
  "ordinary_stack_argument_slots": 1,
  "receiver_register": null,
  "ret_form": "RET 0x4",
  "return_register": [
    "EAX",
    "AL"
  ],
  "return_semantics": "Unconditional success. The result is independent of the owned beam target presence, of the gate word at +0x174, and of the relationship manager global.",
  "return_type": "std::uint8_t",
  "return_width_bytes": 1,
  "saved_registers": [
    "ESI"
  ],
  "stack_arguments": [
    "{'entry_offset': 'ESP+0x08 at the post-prologue ESP+0x04 slot after PUSH ESI', 'observed_use': 'Copied into ESI at 0x01053db1 by `mov esi, dword ptr [esp+0x8]` immediately after `push esi` at 0x01053db0. The same register is the base for every field access and is reloaded into ECX at 0x01053ddf.', 'position': 1, 'type': 'OpaqueBeamToolState *', 'width_bytes': 4}"
  ],
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "callee",
  "termination": "RET 0x4"
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
      "callsite": "0x01053deb",
      "direction": "out",
      "other": "0x00b3d3c0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x01053df2",
      "direction": "out",
      "other": "0x00b78860",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x01053dbf",
      "direction": "out",
      "other": "0x00cb3c70",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x01053de1",
      "direction": "out",
      "other": "0x0104cd50",
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
    "OpaqueBeamTarget *",
    "OpaqueBeamToolState *",
    "const OpaqueBeamTargetVTable *",
    "std::uint32_t",
    "std::uint8_t",
    "void (__thiscall *)(OpaqueBeamTarget *)"
  ],
  "vtables": [
    "vtable:0x00b7d400",
    "vtable:0x01053dd8",
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
      "callsite": "0x01053deb",
      "direction": "out",
      "other": "0x00b3d3c0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x01053df2",
      "direction": "out",
      "other": "0x00b78860",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x01053dbf",
      "direction": "out",
      "other": "0x00cb3c70",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x01053de1",
      "direction": "out",
      "other": "0x0104cd50",
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
    "id": "scc-0609",
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__cDefaultBeamTool__func4Ch.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__cDefaultBeamTool__func4Ch.c",
    "reconstruction/staging/pkg-dfw-01053db0/dfw_01053db0.cpp",
    "reconstruction/staging/pkg-dfw-01053db0/dfw_01053db0_types.hpp",
    "reconstruction/staging/pkg-sim-beamtool-func4ch/beam_tool_func4ch.cpp",
    "reconstruction/staging/pkg-sim-beamtool-func4ch/beam_tool_func4ch.hpp",
    "reconstruction/staging/pkg-sim-beamtool-func4ch/beam_tool_func4ch_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-dfw-01053db0/01053db0.json",
    "reconstruction/metadata/pkg-sim-beamtool-func4ch/01053db0.json"
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
    "Can the callee at 0x00cb3c70 change the receiver's word at 0x124? The listing re-reads and re-tests the slot three instructions after the call, which tolerates it, and its own body is only `MOV byte ptr [ECX + 0x155],0x1 / RET` so there is no evidence either way. The second test is therefore modelled as a plain re-read guard, and the model test exercises both behaviours.",
    "FUN_00cb3c70 could in principle clear the +0x124 slot, which the defensive second null test would absorb; no evidence shows that it does, so the second test is staged as a plain re-read guard.",
    "No canonical Ghidra structure exists for OpaqueBeamToolState, OpaqueBeamTarget or OpaqueRelationshipState; the layouts are assembled from the observed offsets and corroborated by the pkg-sim-tool-wave9 staging package rather than promoted from a live type.",
    "The SDK export's two extra parameters, cSpaceToolData * and Vector3 *, are refuted by the listing and the ret 0x4, but the reason the SDK import attached them is not established; the interface this virtual actually overrides is not named.",
    "The behaviour of the 0x00b77aa0 drain, which is tail-called with the relationship manager as receiver, is outside this package.",
    "The concrete implementation behind the owned target's vtable word at +0x04 is not resolved, and calling it a refcount release is an inference from the null-then-release idiom rather than an observed decrement.",
    "The meaning of gate bit 4 in the word at +0x174 is not determined; only the bit selection is proven. Th
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /decompile_function @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/Simulator__cDefaultBeamTool__func4Ch.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-dfw-01053db0/01053db0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-sim-beamtool-func4ch/01053db0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-dfw-01053db0/dfw_01053db0.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-dfw-01053db0/dfw_01053db0_types.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-sim-beamtool-func4ch/beam_tool_func4ch.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-sim-beamtool-func4ch/beam_tool_func4ch.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-sim-beamtool-func4ch/beam_tool_func4ch_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__cDefaultBeamTool__func4Ch.c",
      "source_class": "committed_artifact"
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
      "ref": "reconstruction/metadata/pkg-dfw-01053db0/01053db0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg-sim-beamtool-func4ch/01053db0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-dfw-
[TRUNCATED]
```
