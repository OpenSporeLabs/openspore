# Reconstruction context 0x01053be0

- Status: `complete`
- Content SHA-256: `7b0c8fe1036ff09e47d568fcb497adfa0f26f62ab0ee59acb589ff9e36c9494c`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x01053be0",
  "phase": "reconstruction",
  "target": "0x01053be0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_01053be0",
  "package": null,
  "subsystem": "Simulator",
  "va": "0x01053be0"
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
  "content_sha256": "509ecc2517bb9ed74934688a790a8aa3e1931371ba1bb98d3c1a8f2a98b292fa",
  "live_attempts": [],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `present`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json

/* WARNING: Enum "ObjectTYPE": Some values do not have unique names */
/* WARNING: Enum "Names": Some values do not have unique names */

Vector3 * __thiscall FUN_01053be0(int *param_1,Vector3 *param_2,undefined4 param_3)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  cGameInputManager *pcVar4;
  float *pfVar5;
  Vector3 *pVVar6;
  int iVar7;
  cPlanetModel *this;
  undefined1 *puVar8;
  Vector3 *position;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined1 local_c [12];
  
  FUN_00ffbe50();
  iVar2 = FUN_00a1ad60();
  param_2->x = 0.0;
  param_2->y = 0.0;
  param_2->z = 0.0;
  if (iVar2 == 0) {
    pcVar4 = Simulator__cGameInputManager__Get();
    if (pcVar4 != (cGameInputManager *)0x0) {
      puVar8 = local_c;
      Simulator__cGameInputManager__Get();
      pfVar5 = (float *)FUN_00b81720(puVar8);
      param_2->x = *pfVar5;
      param_2->y = pfVar5[1];
      param_2->z = pfVar5[2];
    }
  }
  else {
    puVar3 = (undefined4 *)(**(code **)(*(int *)(iVar2 + 0x34) + 0x2c))();
    uStack_18 = *puVar3;
    uStack_14 = puVar3[1];
    uStack_10 = puVar3[2];
    pcVar4 = Simulator__cGameInputManager__Get();
    if (pcVar4 != (cGameInputManager *)0x0) {
      puVar3 = &uStack_18;
      puVar8 = local_c;
      Simulator__cGameInputManager__Get();
      pfVar5 = (float *)FUN_00b815a0(puVar8,puVar3);
      param_2->x = *pfVar5;
      param_2->y = pfVar5[1];
      param_2->z = pfVar5[2];
    }
  }
  iVar2 = 0;
  do {
    iVar7 = iVar2;
    iVar2 = iVar7 + 1;
    cVar1 = (**(code **)(*param_1 + 0x24))(param_3,param_2,1);
    if (cVar1 != '\0
[TRUNCATED]
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
  "ordinary_stack_argument_slots": 1,
  "receiver": "ECX carries a receiver and the body reads it before any definite write to it (MOV EDI,ECX at 0x01053be7, then MOV ECX,EAX at 0x01053bee). Inference R1 records this at INFERRED confidence.",
  "return_observation": "The C entry declares void, which is the honest spelling of what the RECOVERED PREFIX does: it returns nothing, because it has no return instruction and neither of its two exits is a return. That is a statement about the 288 recovered bytes and NOT a claim that the function returns void: the real exit is outside the span and reads (from the image) MOV EAX,ESI ... ADD ESP,0x18; RET 0x8 at 0x01053d3b, which would put the caller's word in EAX. This package does not model that, does not claim it, and records the true return as an unresolved question. No canonical return_type is declared in this ...",
  "return_register": "ST0",
  "return_semantics": "float_or_x87_in_ST0 (machine record, confidence APPROXIMATION)",
  "return_width_bytes": null,
  "saved_registers": [
    "EBX",
    "EBP",
    "ESI",
    "EDI"
  ],
  "stack_cleanup_bytes": null,
  "stack_cleanup_owner": null
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "simulator_game_input_manager_get_00b3d350",
      "reconstructed": true,
      "va": "0x00b3d350"
    }
  ],
  "callers": [],
  "edge_rows": [
    {
      "callsite": "0x01053bf0",
      "direction": "out",
      "other": "0x00a1ad60",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x01053c3b",
      "direction": "out",
      "other": "0x00b3d350",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x01053c4e",
      "direction": "out",
      "other": "0x00b3d350",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x01053c6c",
      "direction": "out",
      "other": "0x00b3d350",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x01053c7a",
      "direction": "out",
      "other": "0x00b3d350",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x01053cce",
      "direction": "out",
      "other": "0x00b3d350",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x01053c55",
      "direction": "out",
      "other": "0x00b815a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x01053c81",
      "direction": "out",
      "other": "0x00b81720",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x01053cd5",
      "direction": "out",
      "other": "0x00b81780",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x01053be9",
      "direction": "out",
      "other": "0x00ffbe50",
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
  "globals": [],
  "types": [
    "float",
    "openspore::reconstruction::pkg_w2_01053be0::ModelWord",
    "openspore::reconstruction::pkg_w2_01053be0::Receiver",
    "std::uint32_t"
  ],
  "vtables": [
    "vtable:0x0149b2e0",
    "vtable:0x0149b4d8",
    "vtable:0x0149b810",
    "vtable:0x0149b8b4",
    "vtable:0x0149b900",
    "vtable:0x0149ba30",
    "vtable:0x0149bf20"
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
  "callees": [
    {
      "name": "simulator_game_input_manager_get_00b3d350",
      "reconstructed": true,
      "va": "0x00b3d350"
    }
  ],
  "callees_truncated": false,
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x01053bf0",
      "direction": "out",
      "other": "0x00a1ad60",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x01053c3b",
      "direction": "out",
      "other": "0x00b3d350",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x01053c4e",
      "direction": "out",
      "other": "0x00b3d350",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x01053c6c",
      "direction": "out",
      "other": "0x00b3d350",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x01053c7a",
      "direction": "out",
      "other": "0x00b3d350",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x01053cce",
      "direction": "out",
      "other": "0x00b3d350",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x01053c55",
      "direction": "out",
      "other": "0x00b815a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x01053c81",
      "direction": "out",
      "other": "0x00b81720",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x01053cd5",
      "direction": "out",
      "other": "0x00b81780",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x01053be9",
      "direction": "out",
      "other": "0x00ffbe50",
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
    "reconstruction/staging/pkg-w2-01053be0/sim_prefix_01053be0.cpp",
    "reconstruction/staging/pkg-w2-01053be0/sim_prefix_01053be0.hpp",
    "reconstruction/staging/pkg-w2-01053be0/sim_prefix_01053be0_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-w2-01053be0/01053be0.json"
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
    "RUNTIME. No original-process trace exists in this repository, none was attempted, and the runtime axis remains GATED at 0. Every claim here is from the disassembly listing, the machine-derived ABI sub-records, and bytes read back out of the image.",
    "THE CONVENTION. conventions.calling_convention is null with four candidates and confidence UNKNOWN, and cleanup is UNKNOWN with side null. __thiscall is the shape the receiver suggests and is NOT asserted; neither is any other candidate. Which side of each of the six direct callees restores ESP is likewise undetermined.",
    "THE DISPATCH SITE COUNT. The machine dispatch record counts indirect_calls 2; the 95-instruction listing shows one indirect transfer site (CALL EAX). Both computed transfers are present in the bytes (ff d0 and ff d2) and the model test checks both, so the disagreement is most likely the record counting the loop's CALL EDX separately -- but that is an explanation, not a determination, and it is not used to change any claim.",
    "THE EXIT AND THE RETURN. Both ways out of the recovered span leave it (the JLE at 0x01053cf9 to 0x01053d3b, and the fall-through at 0x01053d00) and neither is inside it, so the recovered 288 bytes cannot say what this function returns. Reading past the span shows MOV EAX,ESI ... ADD ESP,0x18; RET 0x8 at 0x01053d3b, which would return the caller's word and pop eight bytes of arguments -- but that is outside the recovered span, is not modelled, and is not claimed. The true return type, its width, and the callee-side cleanup 
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /decompile_function @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-w2-01053be0/01053be0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-w2-01053be0/sim_prefix_01053be0.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-w2-01053be0/sim_prefix_01053be0.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-w2-01053be0/sim_prefix_01053be0_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-w2-01053be0/01053be0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-w2-01053be0/sim_prefix_01053be0.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-w2-01053be0/sim_prefix_01053be0.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-w2-01053be0/sim_prefix_0105
[TRUNCATED]
```
