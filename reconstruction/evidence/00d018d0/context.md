# Reconstruction context 0x00d018d0

- Status: `partial`
- Content SHA-256: `b113f30fdedd2fa70f51cc14c06dee0fcc5f2ea93923475e39c323653be8fc46`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00d018d0",
  "phase": "reconstruction",
  "target": "0x00d018d0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00d018d0",
  "package": null,
  "subsystem": "Simulator",
  "va": "0x00d018d0"
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
  "content_sha256": "88f645fb86cf31781b7afbe75d928e33f13a0d3dd349fdf9fbea2f226d65d0c5",
  "live_attempts": [],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `present`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json

void __thiscall FUN_00d018d0(int param_1,undefined4 *param_2,undefined4 *param_3)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  puVar1 = *(undefined4 **)(param_1 + 4);
  puVar3 = param_2;
  for (puVar2 = param_3; puVar2 != puVar1; puVar2 = puVar2 + 2) {
    *puVar3 = *puVar2;
    puVar3[1] = puVar2[1];
    puVar3 = puVar3 + 2;
  }
  *(int *)(param_1 + 4) = *(int *)(param_1 + 4) + ((int)param_3 - (int)param_2 >> 3) * -8;
  return;
}


```

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "original_bytes": 11535,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": [\n      \"entry_ESP+0x4\",\n      \"entry_ESP+0x8\"\n    ],\n    \"ordinary_stack_arguments\": [\n      {\n        \"entry_offset\": \"entry_ESP+0x4\",\n        \"observed\": true,\n        \"ordinal\": 1,\n        \"read\": false,\n        \"size_inferred\": false,\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      },\n      {\n        \"entry_offset\": \"entry_ESP+0x8\",\n        \"observed\": true,\n        \"ordinal\": 2,\n        \"read\": false,\n        \"size_inferred\": false,\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      }\n    ],\n    \"receiver\": true,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET 0x8\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"pointer_like_in_EAX\",\n    \"saved_registers\": [\n      \"EBP\",\n      \"EBX\",\n      \"EDI\",\n      \"ESI\"\n    ],\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"entry_ESP+0x4\",\n        \"observed\": true,\n        \"ordinal\": 1,\n        \"read\": false,\n        \"size_inferred\": false,\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      },\n      {\n        \"entry_offset\": \"entry_ESP+0x8\",\n        \"observed\": true,\n        \"ordinal\": 2,\n        \"read\": false,\n        \"size_inferred\": false,\n    
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
      "va": "0x00603650"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00708d90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00723cf0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0074e2b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007507e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00755da0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00769310"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00774b50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007b9420"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007b9510"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007b9620"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007cf630"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007f2600"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00846db0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00846f10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0089b080"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x006036d7",
      "direction": "in",
      "other": "0x00603650",
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
      "va": "0x00603650"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00708d90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00723cf0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0074e2b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007507e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00755da0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00769310"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00774b50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007b9420"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007b9510"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007b9620"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007cf630"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007f2600"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00846db0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00846f10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0089b080"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0089bd50"
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
    "argument names first/last describe what the body does with the two stack words (observable) and the order is corroborated by 16 call sites, but the original author's names are not observable",
    "no runtime evidence: the model test is a static model of the listing, not a differential test against the game",
    "only 1 of the 16 call sites (0x007f2600) was individually decompiled; the other 15 rest on the xref export rather than on separate body reads",
    "the counter-intuitive trip count: erasing one element copies every element after it, so the cost is O(remaining) rather than O(1). It follows from the machine and is asserted by the model test, but it is the claim most worth a second witness",
    "the element type: only its 8-byte width is fixed, by three machine facts plus one call site",
    "which member the receiver word at 0x4 is: `tail` is this package's own name, inferred from the loop bound and the ADD that shrinks it, and a bounds_only record cannot corroborate a name"
  ]
}
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
