# Reconstruction context 0x00c71e30

- Status: `complete`
- Content SHA-256: `1e83f1e5b2900b33c90a49f52d384b79739f5c461b25fbc0d679f8fb4bfa33b2`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00c71e30",
  "phase": "reconstruction",
  "target": "0x00c71e30"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00c71e30",
  "package": null,
  "subsystem": "Simulator",
  "va": "0x00c71e30"
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
  "content_sha256": "0ce5ec82a81cd77cf3d0d5c81aa204ac5f614f59ca5e74688f21388dc2b3f75f",
  "live_attempts": [],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `present`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json

undefined4 __fastcall FUN_00c71e30(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  if (*(int *)(param_1 + 0x13c) != 0) {
    iVar1 = FUN_00b8dab0();
    if (iVar1 == 5) {
      uVar2 = (**(code **)(*(int *)(param_1 + 0xd4) + 0x4c))();
      FUN_00b3d2a0(uVar2);
      uVar2 = FUN_00ba9370(uVar2);
      return uVar2;
    }
  }
  return 0;
}


```

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall (ECX carries the receiver and is dereferenced at 0x00c71e31 before any definite write to it; both exits are the bare 0xc3; no stack word is read as an argument). THE NAME IS NOT DISCRIMINATED BY THE BYTES - see calling_convention_caveat",
  "ordinary_stack_argument_slots": 0,
  "ordinary_stack_arguments": [],
  "receiver": "ECX, read at 0x00c71e31 (`8b f1`, MOV ESI,ECX) before any definite write; copied into ESI and then read back through ESI at 0x00c71e33, 0x00c71e47 and 0x00c71e50. The record's receiver.shape is R-ALIAS, which is exactly this: the body aliases its receiver into a scratch register rather than dereferencing ECX directly.",
  "ret_form": "RET (0x00c71e66 and 0x00c71e6a, both the bare 0xc3, no imm16)",
  "return_note": "32-bit dword",
  "return_register": "EAX",
  "return_semantics": "the passing arm returns 0x00ba9370's result verbatim - neither 0x00c71e65 (POP ESI) nor 0x00c71e66 (RET) touches EAX; the null arm returns a full 32-bit zero from `33 c0` at 0x00c71e67",
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller"
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "FUN_00b3d2a0",
      "reconstructed": true,
      "va": "0x00b3d2a0"
    },
    {
      "name": "FUN_00b8dab0",
      "reconstructed": false,
      "va": "0x00b8dab0"
    },
    {
      "name": "Simulator_LookupEmpireByPoliticalId",
      "reconstructed": true,
      "va": "0x00ba9370"
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ad4a10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba5270"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bbcf00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bdbf10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be7bf0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00becd70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c38270"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c54380"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c57ad0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c5b9c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c5c470"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c63380"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c82400"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c830f0"
    },
    {
      "name
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "32-bit dword"
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
  "callees": [
    {
      "name": "FUN_00b3d2a0",
      "reconstructed": true,
      "va": "0x00b3d2a0"
    },
    {
      "name": "FUN_00b8dab0",
      "reconstructed": false,
      "va": "0x00b8dab0"
    },
    {
      "name": "Simulator_LookupEmpireByPoliticalId",
      "reconstructed": true,
      "va": "0x00ba9370"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ad4a10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba5270"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bbcf00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bdbf10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be7bf0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00becd70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c38270"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c54380"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c57ad0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c5b9c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c5c470"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c63380"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c82400"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c8
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
      "direct_xref_neighbor"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 9,
    "symbol": "FUN_00b3d2a0",
    "va": "0x00b3d2a0"
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
    "reconstruction/staging/pkg-00c71e30-empire5/empire5_00c71e30.cpp",
    "reconstruction/staging/pkg-00c71e30-empire5/empire5_00c71e30.hpp",
    "reconstruction/staging/pkg-00c71e30-empire5/empire5_00c71e30_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-00c71e30-empire5/00c71e30.json"
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
    "Is the register argument a C++ `this`? The bytes eliminate __cdecl and eliminate nothing else; deciding __thiscall from __fastcall needs a class name, and no pack layer carries one.",
    "Is the return a pointer or a scalar? One sampled caller dereferences it at +0x84 and one null-tests it; both readings are consistent with everything observed.",
    "What class implements the table reached through receiver+0xd4? The shape is a two-level load and the classifier calls it VTABLE_SLOT, but the pack carries zero data references out of this VA and `vtable_at: []`.",
    "What does the constant 5 name, if anything? `CMP EAX,0x5` is an equality against an immediate and no evidence attaches a concept to it.",
    "What does the word at receiver+0x13c mean, and what class is the object it points at? Three sites read the displacement and none of them names a member.",
    "Why does the derived dispatch record count one indirect call and zero vtable-shaped loads for the same listing the repository's VIRTUAL DISPATCH dimension classifies as VTABLE_SLOT at 0x4c? Both numbers are pinned in the source and neither is reconciled here."
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /decompile_function @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-00c71e30-empire5/00c71e30.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-00c71e30-empire5/empire5_00c71e30.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-00c71e30-empire5/empire5_00c71e30.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-00c71e30-empire5/empire5_00c71e30_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-00c71e30-empire5/00c71e30.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-00c71e30-empire5/empire5_00c71e30.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-00c71e30-empire5/empire5_00c71e30.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-00c71e30-empire5/e
[TRUNCATED]
```
