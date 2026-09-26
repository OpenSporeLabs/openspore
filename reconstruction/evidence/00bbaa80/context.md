# Reconstruction context 0x00bbaa80

- Status: `partial`
- Content SHA-256: `c567f28501ab75ad61b05eae9769a1709c9f4bc1d5ae36cccd7e7e0040255739`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00bbaa80",
  "phase": "reconstruction",
  "target": "0x00bbaa80"
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
  "va": "0x00bbaa80"
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
  "content_sha256": "d25d1d6102bf54fc10bd6e48b0ef0d31c286b5ac169ae60a2388ac6ad301d797",
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

undefined1 __thiscall FUN_00bbaa80(int param_1,undefined4 param_2,int param_3)

{
  IGameModeManager__vftable *pIVar1;
  IGameModeManager *pIVar2;
  undefined4 uVar3;
  undefined1 **ppuVar4;
  uint32_t unaff_EBX;
  uint32_t unaff_EBP;
  char *unaff_ESI;
  char *unaff_EDI;
  int unaff_retaddr;
  int *piVar5;
  undefined4 uVar6;
  IGameModeManager local_68 [3];
  undefined4 uStack_5c;
  undefined4 uStack_58;
  IGameModeManager IStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  int aiStack_40 [2];
  int iStack_38;
  undefined1 *puStack_30;
  undefined1 *puStack_2c;
  IGameMode IStack_28;
  undefined1 *puStack_24;
  IGameMode local_20;
  undefined1 *local_1c;
  undefined1 *local_18;
  int iStack_10;
  int iStack_8;
  
  if (*(char *)(param_1 + 0xac) == '\0') {
    return 1;
  }
  FUN_00bba640();
  if ((**(int **)(param_1 + 0x84) != 0) && (*(char *)(**(int **)(param_1 + 0x84) + 0x130) != '\0'))
  {
    pIVar1 = (IGameModeManager__vftable *)FUN_00bb9e00(*(undefined4 *)(param_1 + 0x58));
    FUN_00b8dd60(local_68);
    if (pIVar1 != local_68[0]._vftable0) {
      local_20._vftable0 = (IGameMode__vftable *)&DAT_01667bac;
      local_1c = &DAT_01667bac;
      local_18 = &DAT_01667bae;
      pIVar2 = App__IGameModeManager__Get();
      (*pIVar2->_vftable0[1].AddGameMode)(local_68,&local_20,unaff_EBP,unaff_ESI);
      IStack_28._vftable0 = (IGameMode__vftable *)&DAT_01667bac;
      puStack_24 = &DAT_01667bac;
      local_20._vftable0 = (I
[TRUNCATED]
```

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "original_bytes": 12400,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": [\n      \"entry_ESP+0x4f\",\n      \"entry_ESP+0x68\"\n    ],\n    \"ordinary_stack_argument_slots_bounded\": {\n      \"kept\": 2,\n      \"omitted\": 19\n    },\n    \"ordinary_stack_arguments\": [\n      {\n        \"entry_offset\": \"entry_ESP+0x4f\",\n        \"observed\": true,\n        \"ordinal\": 19,\n        \"read\": false,\n        \"size_inferred\": false,\n        \"sizes\": [\n          1\n        ],\n        \"written\": false\n      },\n      {\n        \"entry_offset\": \"entry_ESP+0x68\",\n        \"observed\": true,\n        \"ordinal\": 26,\n        \"read\": false,\n        \"size_inferred\": false,\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      }\n    ],\n    \"ordinary_stack_arguments_bounded\": {\n      \"kept\": 2,\n      \"omitted\": 19\n    },\n    \"receiver\": true,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET 0x4\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"pointer_like_in_EAX\",\n    \"saved_registers\": [\n      \"EBP\",\n      \"EBX\",\n      \"EDI\",\n      \"ESI\"\n    ],\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"entry_ESP+0x4f\",\n        \"observed\": true,\n        \"ordinal\": 19,\n        \"read\": false,\n        \"size_inferred\": false,\n        \"sizes\": [\n          1\n        ],\n        \"written\": false\n      },\n      {\n     
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
