# Reconstruction context 0x00c035f0

- Status: `partial`
- Content SHA-256: `99a445497f43e408bcc3a75a3067dab9e8cd88023807bcdaf5f6febcc3c8736c`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00c035f0",
  "phase": "reconstruction",
  "target": "0x00c035f0"
}
```

## 02_function_identity

- State: `missing`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": null,
  "package": null,
  "subsystem": null,
  "va": "0x00c035f0"
}
```

## 03_current_status

- State: `missing`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "blocked": null,
  "reconstructed": null,
  "runtime_gated": null,
  "runtime_validated": 0,
  "status": null
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "bc4dd019cc990e3f130be2432d7d93645ca1e3f5bdbd1f33475fab47964973f2",
  "live_attempts": [],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `present`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json

void FUN_00c035f0(int *param_1)

{
  int iVar1;
  int *piVar2;
  undefined4 *puVar3;
  float10 fVar4;
  float local_20;
  float local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined1 local_c [12];
  
  piVar2 = param_1;
  if ((param_1 != (int *)0x0) && (param_1[0x2d5] != 0)) {
    if ((((uint)param_1[0x2d6] >> 9 & 1) == 0) &&
       ((param_1[0x2cd] == 1 && ((param_1[0x2d6] & 1U) != 0)))) {
      iVar1 = DAT_01582f4c * 3 + 0x138;
      local_18 = *(undefined4 *)(param_1[0x2c8] + iVar1 * 4);
      iVar1 = param_1[0x2c8] + iVar1 * 4;
      local_14 = *(undefined4 *)(iVar1 + 4);
      local_10 = *(undefined4 *)(iVar1 + 8);
      FUN_0067ff30(local_18,local_14,local_10,&param_1,&local_20,&local_1c);
      param_1 = (int *)(DAT_01583338 * 360.0 + (float)param_1);
      if (360.0 < (float)param_1) {
        param_1 = (int *)((float)param_1 - 360.0);
      }
      if ((float)param_1 < 0.0) {
        param_1 = (int *)((float)param_1 + 360.0);
      }
      fVar4 = (float10)FUN_005a6e00(DAT_0158333c * local_20);
      local_20 = (float)fVar4;
      fVar4 = (float10)FUN_005a6e00(DAT_01583340 * local_1c);
      local_1c = (float)fVar4;
      puVar3 = (undefined4 *)FUN_0067fe30(local_c,param_1,local_20,(float)fVar4);
      local_18 = *puVar3;
      local_14 = puVar3[1];
      local_10 = puVar3[2];
      (**(code **)(*piVar2 + 0xe4))(&local_18);
      FUN_00c0d950(1);
      fVar4 = (float10)(**(code **)(*piVar2 + 0x80))(0);
      (**(code **)(piVar2[0x30] + 0x40))((float)fVar4);
      return;
    }
    (**(code **)(*param_1 + 0xe4))(&DAT_0157126c);

[TRUNCATED]
```

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "original_bytes": 21466,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"ordinary_stack_argument_slots\": [\n      \"entry_ESP+0x4\"\n    ],\n    \"ordinary_stack_arguments\": [\n      {\n        \"entry_offset\": \"entry_ESP+0x4\",\n        \"observed\": true,\n        \"ordinal\": 1,\n        \"read\": false,\n        \"size_inferred\": true,\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      }\n    ],\n    \"ret_form\": \"RET\",\n    \"return_register\": \"ST0\",\n    \"return_semantics\": \"float_or_x87_in_ST0\",\n    \"saved_registers\": [\n      \"ESI\"\n    ],\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"entry_ESP+0x4\",\n        \"observed\": true,\n        \"ordinal\": 1,\n        \"read\": false,\n        \"size_inferred\": true,\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      }\n    ],\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"RET\"\n  },\n  \"abstained_because\": [\n    \"flow_not_modelled: the linear ESP walk ends at -12, so the listing is not one path\",\n    \"receiver_not_determinable: ecx_read_without_deref\",\n    \"receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_read_without_deref), and the convention rule that would apply discriminates on receiver absence\"\n  ],\n  \"cleanup\": {\n    \"bytes\": 0,\n    \"confidence\": \"INFERRED\",\n    \"corroboration\": \"not_available\",\n    \"evidence\": \"ret with no immediate\",\n    \"side\": \"caller\"\n  }
[TRUNCATED]
```

## 07_callers_callees

- State: `missing`
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
  "runtime": {},
  "semantic": {}
}
```

## 10_dependencies

- State: `missing`
- Provenance: `reconstruction/knowledge/index.json`

## 11_related_functions

- State: `missing`
- Provenance: `reconstruction/knowledge/index.json`

## 12_existing_reconstruction

- State: `missing`
- Provenance: `reconstruction/knowledge/index.json`

## 13_semantic_hypotheses

- State: `missing`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

## 14_conflicts_questions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json, knowledgegraph/research/semantic-decomp.json`

```json
{
  "conflicts": [],
  "unresolved_questions": []
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'ref': 'GhidraMCP /disassemble_function', 'mode': 'derived', 'source_class': 'derived'}, {'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'mode': 'derived', 'source_class': 'derived'}, {'ref': 'ephemeral reconstruction_knowledge.build_index', 'mode': 'derived', 'source_class': 'generated_index'}, {'ref': 'tools/reconstruction_tooling/abi_infer.py', 'mode': 'derived', 'source_class': 'derived'}, {'ref': 'GhidraMCP /disassemble_function', 'mode': 'live', 'source_class': 'ghidra'}, {'ref': 'GhidraMCP REST /decompile_function @ http://127.0.0.1:8089', 'mode': 'live', 'source_class': 'ghidra'}, {'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'mode': 'live', 'source_class': 'ghidra'}, {'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'mode': 'persisted', 'source_class': 'committed_artifact'}, {'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'mode': 'persisted', 'source_class': 'committed_artifact'}`

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
