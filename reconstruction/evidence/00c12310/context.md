# Reconstruction context 0x00c12310

- Status: `partial`
- Content SHA-256: `b852eaa3279f524b84762095eef2c17ebd824c8d318538fe591f6916f1c2e36e`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00c12310",
  "phase": "reconstruction",
  "target": "0x00c12310"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00c12310",
  "package": null,
  "subsystem": "Simulator",
  "va": "0x00c12310"
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
  "content_sha256": "a1c3ed1e2327c204b81bdbab8ad9248f9764cd6e3b62b41f12ada458efb098f6",
  "live_attempts": [],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `present`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json

undefined4 __thiscall FUN_00c12310(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  int *piVar2;
  int iVar3;
  char unaff_BP;
  undefined4 uVar4;
  undefined4 uVar5;
  
  uVar1 = param_2;
  uVar4 = 0;
  if (*(int *)(param_1 + 0xb54) != 0) {
    FUN_00c0c5b0(param_1,param_2,&param_2);
    piVar2 = (int *)FUN_0067cb20();
    uVar4 = param_2;
    iVar3 = (**(code **)(*piVar2 + 0x40))(param_2);
    if (iVar3 == 0) {
      return 0;
    }
    uVar4 = (**(code **)(**(int **)(param_1 + 0xb54) + 8))(uVar4,0);
    uVar5 = 1;
    (**(code **)(**(int **)(param_1 + 0xb54) + 0xc))(uVar4,1);
    if (unaff_BP != '\0') {
      (**(code **)(**(int **)(param_1 + 0xb54) + 0x14))(uVar4,0);
    }
    (**(code **)(**(int **)(param_1 + 0xb54) + 0x18))(uVar4);
    (**(code **)(**(int **)(param_1 + 0xb54) + 0x40))(uVar4,uVar1);
    (**(code **)(**(int **)(param_1 + 0xb54) + 0x3c))(uVar4,0);
    FUN_00c10250(param_1,uVar4,uVar5,iVar3);
    if (*(char *)(iVar3 + 0x1c) != '\x01') {
      *(undefined4 *)(param_1 + 0xe88) = uVar4;
    }
  }
  return uVar4;
}


```

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "original_bytes": 16139,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": [\n      \"entry_ESP+0x4\",\n      \"entry_ESP+0x8\"\n    ],\n    \"ordinary_stack_arguments\": [\n      {\n        \"entry_offset\": \"entry_ESP+0x4\",\n        \"observed\": true,\n        \"ordinal\": 1,\n        \"read\": false,\n        \"size_inferred\": true,\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      },\n      {\n        \"entry_offset\": \"entry_ESP+0x8\",\n        \"observed\": true,\n        \"ordinal\": 2,\n        \"read\": false,\n        \"size_inferred\": false,\n        \"sizes\": [\n          1\n        ],\n        \"written\": false\n      }\n    ],\n    \"receiver\": true,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET 0xc\",\n    \"return_register\": \"ST0\",\n    \"return_semantics\": \"float_or_x87_in_ST0\",\n    \"saved_registers\": [\n      \"EBP\",\n      \"EBX\",\n      \"EDI\",\n      \"ESI\"\n    ],\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"entry_ESP+0x4\",\n        \"observed\": true,\n        \"ordinal\": 1,\n        \"read\": false,\n        \"size_inferred\": true,\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      },\n      {\n        \"entry_offset\": \"entry_ESP+0x8\",\n        \"observed\": true,\n        \"ordinal\": 2,\n        \"read\": false,\n        \"size_inferred\": false,\n      
[TRUNCATED]
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
      "va": "0x00c06f70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c13650"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c13a30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c14590"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c14990"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c149c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c14cb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c18370"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c18740"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c18b40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c190e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c1b020"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c1c9f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c1e460"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c20230"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c21bf0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00c07067",
      "direction": "in",
      "other": "0x00c06f70",
      "reference_type": "direct-call"
    },

[TRUNCATED]
```

## 08_types_fields_globals

- State: `missing`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [],
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
      "va": "0x00c06f70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c13650"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c13a30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c14590"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c14990"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c149c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c14cb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c18370"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c18740"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c18b40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c190e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c1b020"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c1c9f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c1e460"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c20230"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c21bf0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c25480"
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
  "files": [],
  "handoffs": [],
  "metadata": []
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
    "A package-local .clang-format pins PointerAlignment: Left. With the LLVM default the formatter rewrites `OpaqueCreated* PKG_00C12310_THISCALL create_cached_object_00c12310(` into a form validate.RETURN_DECL cannot parse -- the convention token stops being a convention and the target span cannot be bound at all, so every dimension reports NOT_AVAILABLE for a correct source. The repository has no top-level .clang-format, so --style=file run from inside the package falls back to LLVM; the file is scoped to this directory and changes nothing else.",
    "Nothing has run the original process for this target: there is no trace, no differential capture and no runtime evidence anywhere in this repository, so the model test is a static model of the listing and not a comparison against the game.",
    "The concrete subtypes behind receiver+0xb54 and behind 0x0067cb20's return, and the sizes of either. No MSVC RTTI survives in this binary and no record names a class.",
    "The exact receiver size. 0xe88+4 is a floor from the store, not a measurement, and the model test only asserts that nothing past it is written.",
    "VALIDATION WIRING IS THE INTEGRATOR'S STEP: the metadata record is at reconstruction/staging/pkg-00c12310-create-cache-object/metadata/00c12310.json rather than in the shared reconstruction/metadata/, because I was told not to edit outside my own staging directory. Until it is moved, validate._source() finds no artifact for this VA and every dimension reports NOT_AVAILABLE. The source-side facts the checks read we
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'derived'}, {'mode': 'derived', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'derived'}, {'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /decompile_function @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}`

```json
{
  "provenance": [
    {
      "mode": "derived",
      "ref": "GhidraMCP /disassemble_function",
      "source_class": "derived"
    },
    {
      "mode": "derived",
      "ref": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
      "source_class": "derived"
    },
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
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.json"
  ],
  "required_categories": [
    "ABI",
    "CALLS",
    "GLOBALS",
    "FIELDS/OFFSETS",
    "CONSTANTS",
    "CONTROL FLOW",
    "VIRTUAL DISPATCH",
    "RETURN SEMANTICS",
    "EVIDENCE COVERAGE"
  ]
}
```
