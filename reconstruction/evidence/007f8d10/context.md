# Reconstruction context 0x007f8d10

- Status: `complete`
- Content SHA-256: `1784a35e0e6ec095fd453b3daa9636b79ecbe773a2e2456830cb132f35834c67`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x007f8d10",
  "phase": "reconstruction",
  "target": "0x007f8d10"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_007f8d10",
  "package": null,
  "subsystem": "Simulator",
  "va": "0x007f8d10"
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
  "content_sha256": "e4f60f9a3a339509ef24bf7375e12b3339a0c855eaa2dcf52e11d5546f78d680",
  "live_attempts": [],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `present`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json

void __thiscall FUN_007f8d10(int param_1,int param_2,int *param_3,int param_4)

{
  int *piVar1;
  int *piVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  int *piVar8;
  int *local_88 [2];
  undefined **local_80;
  undefined **local_78;
  int *local_74;
  
  if (param_3 == (int *)0x0) {
    return;
  }
  if (*(int *)(param_2 + 4) == 0) {
    return;
  }
  piVar1 = (int *)(param_1 + 4);
  iVar5 = *(int *)(param_1 + 8) - *piVar1;
  uVar3 = (*(int *)(param_1 + 8) - *piVar1) / 0x88;
  iVar4 = iVar5 >> 0x1f;
  uVar6 = 0;
  uVar7 = uVar3;
  if (iVar5 / 0x88 + iVar4 != iVar4) {
    piVar8 = (int *)*piVar1;
    while (piVar2 = (int *)*piVar8, uVar7 = uVar6, piVar2 != (int *)0x0) {
      if ((piVar2 == param_3) && (piVar8[1] == param_4)) {
        if (piVar2 != (int *)0x0) {
          (*(code *)piVar8[3])(piVar8 + 2,0,0,1,0);
        }
        break;
      }
      uVar6 = uVar6 + 1;
      piVar8 = piVar8 + 0x22;
      uVar7 = uVar3;
      if ((uint)((*(int *)(param_1 + 8) - *piVar1) / 0x88) <= uVar6) break;
    }
  }
  if (uVar7 == (*(int *)(param_1 + 8) - *piVar1) / 0x88) {
    uVar3 = *(uint *)(param_1 + 8);
    local_88[0] = (int *)0x0;
    local_80 = &PTR_FUN_013f6400;
    local_78 = &PTR_FUN_013f63fc;
    local_74 = (int *)0x0;
    if (uVar3 < *(uint *)(param_1 + 0xc)) {
      *(uint *)(param_1 + 8) = uVar3 + 0x88;
      if (uVar3 == 0) goto LAB_007f8e83;
      FUN_007f6d90(local_88);
    }
    else {
      FUN_007f8820(uVar3,local_88);
    }
    if (local_74 != (int *)0x0) {
      (**(code **)(*local_74 + 4))();
    }
    if (local_88[0] != (int *)0
[TRUNCATED]
```

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall; receiver in ECX, three callee-cleaned 4-byte stack arguments",
  "ordinary_stack_argument_slots": 3,
  "receiver": "ECX, spilled to E0-0x8c at 0x007f8d1e and reloaded into EAX at 0x007f8edb to write [EAX+0x1c]; read through `LEA ESI,[ECX+0x4]` at 0x007f8d3f",
  "ret_form": "RET 0xc",
  "return_register": "none",
  "return_type": "void",
  "stack_cleanup_bytes": 12,
  "stack_cleanup_owner": "callee"
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
      "va": "0x0059a500"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006478c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0064ecc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00658440"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006589d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00658e80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0065fd30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00668070"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00832230"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00834730"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x008347f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00dd5a30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00dd5bb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00dd6570"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00dd7970"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00dd8640"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x0059a58b",
      "direction": "in",
      "other": "0x0059a500",
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
    "void"
  ],
  "vtables": []
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
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059a500"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006478c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0064ecc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00658440"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006589d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00658e80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0065fd30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00668070"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00832230"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00834730"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x008347f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00dd5a30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00dd5bb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00dd6570"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00dd7970"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00dd8640"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e133b0"
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
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-13-E4-EMPIRE-WAVE3",
    "score": 6,
    "symbol": "EmpirePoliticalColor_00c32cd0",
    "va": "0x00c32cd0"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-007f8d10-registry-ensure-entry/registry_ensure_entry_007f8d10.cpp",
    "reconstruction/staging/pkg-007f8d10-registry-ensure-entry/registry_ensure_entry_007f8d10.hpp",
    "reconstruction/staging/pkg-007f8d10-registry-ensure-entry/registry_ensure_entry_007f8d10_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-007f8d10-registry-ensure-entry/007f8d10.json"
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
    "0x007f8e0c (`CMP ECX,EBX` on the old end pointer) is only reachable when end is a null pointer with capacity still ahead. For a self-consistent container that cannot happen: end == 0 forces begin == 0, which forces capacity == 0, which routes to the grow branch instead. The branch is reproduced verbatim but no test can reach it.",
    "No caller was inspected. The seventeen-plus recorded callers pass the same three arguments, and one of them would settle what argument 1 and argument 3 mean, but that is outside this target's budget.",
    "On the grow route (0x007f8e58 -> 0x007f8820) the new element is initialised by 0x007f7c00 from the LAST live element, whereas on the in-place route (0x007f8e15 -> 0x007f6d90) it is initialised from the prototype, whose +0x00 is null. Whether 0x007f8ea7 releases a displaced handle therefore depends on a callee that was not resolved. Resolving 0x007f7c00 and 0x007f7920 would settle it.",
    "The two constants at element+0x08 and element+0x10 have the shape of a multiple-inheritance vptr pair, but the word the body dispatches through sits between them at element+0x0c and is a runtime value copied from argument 1, not a vtable. Whether +0x08 and +0x10 are vptrs of two bases or plain constants is not settled by this body."
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /decompile_function @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-007f8d10-registry-ensure-entry/007f8d10.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-007f8d10-registry-ensure-entry/registry_ensure_entry_007f8d10.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-007f8d10-registry-ensure-entry/registry_ensure_entry_007f8d10.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-007f8d10-registry-ensure-entry/registry_ensure_entry_007f8d10_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-007f8d10-registry-ensure-entry/007f8d10.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-007f8d10-registry-ensure-entry/registry_ensure_entry_007f8d10.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-007f8d10-registry-ensure-entry/registry_ensure_entry_007f8d10.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "p
[TRUNCATED]
```
