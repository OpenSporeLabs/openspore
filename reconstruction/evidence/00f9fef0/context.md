# Reconstruction context 0x00f9fef0

- Status: `complete`
- Content SHA-256: `d6992d76a41f970751811d2c3147c9b4e67255fa3de569990229e27105e13012`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00f9fef0",
  "phase": "reconstruction",
  "target": "0x00f9fef0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00f9fef0",
  "package": null,
  "subsystem": "Sporepedia",
  "va": "0x00f9fef0"
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
  "content_sha256": "67c16fa0e3ae44c198af45465cde4dbed1dd7a78d91c46943b2ee3c3dde0de70",
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

void __thiscall FUN_00f9fef0(int param_1,int *param_2)

{
  char cVar1;
  char cVar2;
  int iVar3;
  void *pEffectsRenderer;
  IShadowWorld *pIVar4;
  int *piVar5;
  undefined4 uVar6;
  int iVar7;
  
  if (param_1 == 0) {
    iVar7 = 0;
  }
  else {
    iVar7 = param_1 + 4;
  }
  iVar3 = (**(code **)(*param_2 + 0x58))(8);
  if (iVar3 != iVar7) {
    cVar1 = Prop_GetPropValueBool(0x201a4e50);
    cVar2 = Prop_GetPropValueBool(0xe13ce337);
    if (cVar1 != '\0') {
      FUN_00f96b40();
      if (cVar2 != '\0') {
        FUN_00f9e3a0();
      }
    }
    if (param_1 == 0) {
      iVar7 = 0;
    }
    else {
      iVar7 = param_1 + 4;
    }
    (**(code **)(*param_2 + 0x4c))(iVar7,7,0);
    if (param_1 == 0) {
      iVar7 = 0;
    }
    else {
      iVar7 = param_1 + 4;
    }
    (**(code **)(*param_2 + 0x4c))(iVar7,8,0);
    if (param_1 == 0) {
      pEffectsRenderer = (void *)0x0;
    }
    else {
      pEffectsRenderer = (void *)(param_1 + 4);
    }
    iVar7 = 0x21;
    (**(code **)(*param_2 + 0x4c))(pEffectsRenderer,0x21,0);
    pIVar4 = Graphics__IShadowWorld__Get();
    piVar5 = (int *)(*pIVar4->_vftable0->AddEffects)
                              ((IShadowWorld *)0x3fbae24,pEffectsRenderer,iVar7);
    iVar7 = *param_2;
    uVar6 = (**(code **)(*piVar5 + 0x13c))(10,0);
    (**(code **)(iVar7 + 0x4c))(uVar6);
    (**(code **)(*piVar5 + 0x134))(1);
    piVar5 = (int *)FUN_0067ddd0();
    piVar5 = (int *)(**(code **)(*piVar5 + 0x54))(0x3
[TRUNCATED]
```

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
  "receiver": "ECX carries the receiver, and the witness is the strongest in this campaign. 0x00f9fef3 MOV EDI,ECX copies the incoming register into EDI before anything else touches it; 0x00f9fef5 TEST EDI,EDI and 0x00f9fef7 JZ 0x00f9fefe NULL-TEST it; 0x00f9fef9 LEA EBX,[EDI+0x4] forms an interior address from it. What the machine record states, at INFERRED confidence: receiver {present true, register ECX, provenance vftable_slot_dispatch, bounds_only true, shape null, distinct_offsets 0, offsets [], written_through 0}. What the listing shows: the register is read by eleven instructions and every one of ...",
  "receiver_register": "ECX",
  "ret_form": "RET 0x4",
  "return_observation": "The record classifies the return as pointer_like in EAX with aggregate_evidence bulk_write false, and the listing agrees on the width and the shape. The listing says more, and only the listing is read here: the early out returns the interior pointer, and the main path does not return at all. The C spelling is Word *, chosen because the value is a plain four-byte interior address; a pointer-to-Receiver spelling would additionally imply a type this package declines to name.",
  "return_register": "EAX",
  "return_semantics": "pointer_like_in_EAX",
  "return_width_bytes": 4,
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
  "callees": [
    {
      "name": "app_direct_property_list_get_direct_bool_006a25a0",
      "reconstructed": true,
      "va": "0x006a25a0"
    }
  ],
  "callers": [],
  "edge_rows": [
    {
      "callsite": "0x00f9ff9f",
      "direction": "out",
      "other": "0x0067dd80",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f9ffdc",
      "direction": "out",
      "other": "0x0067ddd0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f9ff25",
      "direction": "out",
      "other": "0x006a25a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f9ff33",
      "direction": "out",
      "other": "0x006a25a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f9ff41",
      "direction": "out",
      "other": "0x00f96b40",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f9ff4f",
      "direction": "out",
      "other": "0x00f9e3a0",
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
    "openspore::reconstruction::pkg_w2_00f9fef0::Argument",
    "openspore::reconstruction::pkg_w2_00f9fef0::Receiver",
    "openspore::reconstruction::pkg_w2_00f9fef0::Word"
  ],
  "vtables": [
    "vtable:0x01490be8"
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
      "name": "app_direct_property_list_get_direct_bool_006a25a0",
      "reconstructed": true,
      "va": "0x006a25a0"
    }
  ],
  "callees_truncated": false,
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00f9ff9f",
      "direction": "out",
      "other": "0x0067dd80",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f9ffdc",
      "direction": "out",
      "other": "0x0067ddd0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f9ff25",
      "direction": "out",
      "other": "0x006a25a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f9ff33",
      "direction": "out",
      "other": "0x006a25a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f9ff41",
      "direction": "out",
      "other": "0x00f96b40",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f9ff4f",
      "direction": "out",
      "other": "0x00f9e3a0",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 0,
  "fan_out": 1,
  "manifest_callees": [],
  "manifest_callers": [],
  "nearby_reconstructed": [
    "0x006a25a0"
  ],
  "scc": {
    "id": "scc-0576",
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
      "shared_vtable:vtable:0x01490be8",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w2-00f999e0",
    "score": 12,
    "symbol": "re_00f999e0",
    "va": "0x00f999e0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01490be8",
      "same_calling_convention"
    ],
    "package": "pkg-fa0d50-atomic-inc",
    "score": 12,
    "symbol": "FUN_00fa0d50",
    "va": "0x00fa0d50"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01490be8",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-00fa5580",
    "score": 12,
    "symbol": "re_00fa5580",
    "va": "0x00fa5580"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01490be8",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-00fa6ec0",
    "score": 12,
    "symbol": "re_00fa6ec0",
    "va": "0x00fa6ec0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01490be8",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-00fa73c0",
    "score": 12,
    "symbol": "sw1_snap_and_dispatch_00fa73c0",
    "va": "0x00fa73c0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01490be8",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-0104c110",
    "score": 12,
    "symbol": "re_0104c110",
    "va": "0x0104c110"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-005
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-w2-00f9fef0/w2_00f9fef0.cpp",
    "reconstruction/staging/pkg-w2-00f9fef0/w2_00f9fef0_model_test.cpp",
    "reconstruction/staging/pkg-w2-00f9fef0/w2_00f9fef0_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-w2-00f9fef0/00f9fef0.json"
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
    "Is the first callee-popped stack word a parameter at all? It is established that the body reads it, dereferences it five times, spills a byte into it, tests that byte, and zeroes it before a tail transfer. Whether it is a declared parameter, and of what type and meaning, is not established by this listing and is not guessed.",
    "The machine record and the listing DISAGREE about the first callee-popped stack word: the record says read: false and written: false, and the listing reads it at 0x00f9ff00 and writes it at 0x00f9ff38 and 0x00f9fff4. The record's own abstention (\"flow_not_modelled: the linear ESP walk ends at +60, so the listing is not one path\") explains why, and the record was deliberately not edited, but the disagreement is real and is not resolved here. Which reading the game's own callers would confirm is an open question.",
    "What are the stack effects of the seven virtual callees? Their terminators are resolved at run time and are not in this image at this address, so the frame balance constrains only their sum. Many assignments close both epilogues and the tail transfer, so no per-callee figure is derivable here.",
    "What do the immediates mean? 0x201a4e50 and 0xe13ce337 are passed as one 32-bit word each to 0x006a25a0, whose low byte return is the only part the body consumes; 0x7, 0x8 and 0x21 select the three consecutive slot-0x4c calls; 0x3fbae24 is passed to both the slot-0x1c and the slot-0x54 call; 0xa and 0x1 are passed to the slot-0x13c and slot-0x134 calls. The listing says which bytes
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /decompile_function @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-w2-00f9fef0/00f9fef0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-w2-00f9fef0/w2_00f9fef0.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-w2-00f9fef0/w2_00f9fef0_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-w2-00f9fef0/w2_00f9fef0_types.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-w2-00f9fef0/00f9fef0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-w2-00f9fef0/w2_00f9fef0.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-w2-00f9fef0/w2_00f9fef0_model_test.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-w2-00f9fef0/w2_00f9fef0_types.hp
[TRUNCATED]
```
