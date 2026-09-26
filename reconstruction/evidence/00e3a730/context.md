# Reconstruction context 0x00e3a730

- Status: `partial`
- Content SHA-256: `c2890522c1ae771e65ae3564d1a623b708f130a42d9fd37b8810d862f489587b`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00e3a730",
  "phase": "reconstruction",
  "target": "0x00e3a730"
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
  "va": "0x00e3a730"
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
  "content_sha256": "065b4e688c5af268cbc38f2ce84016801930e8549bd1d813a0809210da3ac919",
  "live_attempts": [],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `present`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json

int * __thiscall FUN_00e3a730(int param_1,int param_2,char param_3)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  undefined4 uVar4;
  int *piVar5;
  int iVar6;
  int iStack_c;
  undefined *puStack_8;
  undefined4 uStack_4;
  
  piVar5 = (int *)0x0;
  FUN_00b3d300();
  iVar1 = FUN_00f67d90();
  iVar6 = 0;
  if (*(int *)(param_1 + 0x1e0) == 0x2b978c46) {
    iVar6 = FUN_00c756e0(param_2);
  }
  else {
    iVar2 = *(int *)(*(int *)(param_1 + 0x188) + -4);
    if (iVar2 != 0) {
      iVar6 = *(int *)(iVar2 + 0xf0);
    }
  }
  if ((param_3 != '\0') && (*(int *)(iVar1 + 0x1108) != 0)) {
    iVar6 = FUN_00556440(*(undefined4 *)(iVar1 + 0x10fc),*(undefined4 *)(iVar1 + 0x1100),
                         *(undefined4 *)(iVar1 + 0x1104),*(int *)(iVar1 + 0x1108));
  }
  if (iVar6 != 0) {
    iVar1 = FUN_00e36f50(param_2);
    iVar2 = FUN_00f473a0(0xa0,&DAT_013f6b3c,0,0,0,0);
    if (iVar2 != 0) {
      piVar3 = (int *)FUN_006775f0();
      if (piVar3 != (int *)0x0) {
        (**(code **)*piVar3)();
        piVar5 = piVar3;
      }
    }
    uVar4 = FUN_008105b0(iVar1 + 0x6299720,1);
    iVar2 = param_1 + 0x29c + iVar1 * 0xc;
    if (*(int *)(param_1 + 0x29c + iVar1 * 0xc) == 0) {
      FUN_00677220(uVar4,1,1);
      puStack_8 = &DAT_00b1b104;
      uStack_4 = 0xf865c777;
      iStack_c = iVar6;
      FUN_00677700(1,&iStack_c,0);
    }
    else if (param_2 == -0x5bd98cf5) {
      FUN_00677df0(uVar4,iVar2,iVar6);
    }
    else {
      FUN_00677d90(uVar4,iVar2,param_2,iVar6);
    }
    if (param_3 != '\0') {
      puStack_8 = &DAT_00b1b104;
      uStack_4 = 0xf865c777;
      iStack_c = 
[TRUNCATED]
```

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "original_bytes": 21689,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": [\n      \"entry_ESP+0x4\"\n    ],\n    \"ordinary_stack_arguments\": [\n      {\n        \"confidence\": \"UNKNOWN\",\n        \"entry_offset\": \"entry_ESP+0x4\",\n        \"observed\": true,\n        \"ordinal\": 1,\n        \"read\": false,\n        \"size_inferred\": false,\n        \"sizes\": [\n          1,\n          4\n        ],\n        \"written\": false\n      }\n    ],\n    \"receiver\": true,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET 0x8\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"pointer_like_in_EAX\",\n    \"saved_registers\": [\n      \"EBP\",\n      \"EBX\",\n      \"EDI\",\n      \"ESI\"\n    ],\n    \"stack_arguments\": [\n      {\n        \"confidence\": \"UNKNOWN\",\n        \"entry_offset\": \"entry_ESP+0x4\",\n        \"observed\": true,\n        \"ordinal\": 1,\n        \"read\": false,\n        \"size_inferred\": false,\n        \"sizes\": [\n          1,\n          4\n        ],\n        \"written\": false\n      }\n    ],\n    \"stack_cleanup_bytes\": 8,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"RET 0x8\"\n  },\n  \"abstained_because\": [\n    \"flow_not_modelled: the linear ESP walk ends at +72, so the listing is not one path\",\n    \"untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-r
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
