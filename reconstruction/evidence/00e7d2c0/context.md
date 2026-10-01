# Reconstruction context 0x00e7d2c0

- Status: `complete`
- Content SHA-256: `fbdf886ce56dcb8aff1d853f8f8a4718168307fea7a64807267190c8da21fcc0`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00e7d2c0",
  "phase": "reconstruction",
  "target": "0x00e7d2c0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": null,
  "package": null,
  "subsystem": "Simulator",
  "va": "0x00e7d2c0"
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
  "content_sha256": "06836bba98de9e29f0ac5f70b0cf038dbb60dbb3e30c9ceec2c8985d0c6fa3e2",
  "live_attempts": [],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `present`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json

/* WARNING: Type propagation algorithm not settling */
/* WARNING: Enum "Names": Some values do not have unique names */
/* WARNING: Enum "ObjectTYPE": Some values do not have unique names */

void FUN_00e7d070(int param_1,undefined4 param_2)

{
  int in_EAX;
  cCellObjectData *cell;
  int *piVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  int local_30 [2];
  int local_28 [10];
  
  if (*(int *)(Simulator__Cell__sCellGame + 0x411c) == 0) {
    return;
  }
  cell = (cCellObjectData *)FUN_00b72210(*(int *)(Simulator__Cell__sCellGame + 0x411c));
  FUN_00743b50();
  iVar4 = 0;
  if ((in_EAX != DAT_016b3c14) && (iVar4 = thunk_FUN_00e823a0(), iVar4 != 0)) {
    if (*(char *)(iVar4 + 0x314) != '\0') {
      FUN_00e671c0(cell);
    }
    if (*(char *)(iVar4 + 0x315) != '\0') {
      FUN_00e77d50(param_2);
    }
  }
  iVar3 = cell->mHealthPoints;
  piVar2 = &cell->mHealthPoints;
  if (iVar3 < 6) {
    if (iVar4 == 0) {
      if (*(int *)(Simulator__Cell__sCellGame + 0x411c) == cell->mObjectPoolIndex) {
        Simulator__Cell__cCellUI__ShowHealthRollover(cell,iVar3);
      }
      *piVar2 = *piVar2 + 2;
    }
    else if (0 < *(int *)(iVar4 + 0x310)) {
      if (*(int *)(Simulator__Cell__sCellGame + 0x411c) == cell->mObjectPoolIndex) {
        Simulator__Cell__cCellUI__ShowHealthRollover(cell,iVar3);
      }
      if (*(int *)(*(int *)(Simulator__Cell__sCellGame + 0x5190) + 0x7c) == 0) {
        *piVar2 = *piVar2 + *(int *)(iVar4 + 0x310) * 2;
      }
      else {
        *piVar2 = *piVar2 + *(int *)(iVar4 + 0x310);
      }
    }
  }
  local_28[0] = 6;
  piVar1
[TRUNCATED]
```

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": null,
  "hidden_this": null,
  "receiver": "NOT CLAIMED, IN EITHER DIRECTION. The record declines to name one: receiver {present null, register null, reason ecx_reassigned_before_deref, confidence UNKNOWN, bounds_only true, offsets [], distinct_offsets 0, written_through 0}. Nothing in this package treats any register as `this`, and no receiver type, class, object size, vtable identity, field or layout is asserted anywhere.",
  "receiver_register": null,
  "ret_form": "RET",
  "return_register": "ST0",
  "return_semantics": "float_or_x87_in_ST0",
  "saved_registers": [
    "EBP",
    "EBX",
    "EDI",
    "ESI"
  ],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "RET"
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
    "openspore::reconstruction::pkg_w2_00e7d2c0::BlockOutcome",
    "openspore::reconstruction::pkg_w2_00e7d2c0::Byte",
    "openspore::reconstruction::pkg_w2_00e7d2c0::StackWindow",
    "openspore::reconstruction::pkg_w2_00e7d2c0::TailArguments",
    "openspore::reconstruction::pkg_w2_00e7d2c0::Word"
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
    "id": "scc-0553",
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
    "reconstruction/staging/pkg-w2-00e7d2c0/bounded_block_00e7d2c0.cpp",
    "reconstruction/staging/pkg-w2-00e7d2c0/bounded_block_00e7d2c0.hpp",
    "reconstruction/staging/pkg-w2-00e7d2c0/bounded_block_00e7d2c0_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-w2-00e7d2c0/00e7d2c0.json"
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
    "Is ESI provably zero on every path that reaches 0x00e7d2b7? The listing has exactly one definition of ESI, `XOR ESI,ESI` at 0x00e7d23d, and it dominates this block by inspection, but no dominator computation was run and the model does not depend on it.",
    "Is the enclosing function variadic? The record lists variadic_suspected and variadic_not_decidable_from_listing and states that the suspicion removes any guarantee about the stack-argument extent. The block's own five words are accounted for; the function's are not.",
    "Is this body a virtual member of some class, and of which? The record declines to name a receiver and the body contains no indirect transfer, so nothing in this repository places it in a class or a slot.",
    "What do the two selector immediates 0x9ef61113 and 0xac7161b5 mean, and what does the callee at 0x00e394f0 do with them? The two-arm shape is established; the meaning of either arm is not.",
    "What is the enclosing function FUN_00e7d070 for? Its decompilation was never collected, eleven callees are unresolved, and 203 of its 224 instructions are untranscribed here.",
    "What is the word at the absolute address 0x016b3c04, and what object does it point at? The block reads it and then reads 0x5190 bytes into the result, but no type, size, class or lifetime for either is established here and none is guessed.",
    "Why does the CALLS oracle see no callee for this VA? The xref export keys rows on 0x00e7d070, the function's real entry, and carries no row for the interior address 0x00e7d2c0,
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /decompile_function @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-w2-00e7d2c0/00e7d2c0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-w2-00e7d2c0/bounded_block_00e7d2c0.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-w2-00e7d2c0/bounded_block_00e7d2c0.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-w2-00e7d2c0/bounded_block_00e7d2c0_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-w2-00e7d2c0/00e7d2c0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-w2-00e7d2c0/bounded_block_00e7d2c0.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-w2-00e7d2c0/bounded_block_00e7d2c0.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-w2-00e7d2c0/bounded_b
[TRUNCATED]
```
