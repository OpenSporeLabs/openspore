# Reconstruction context 0x00ba8830

- Status: `partial`
- Content SHA-256: `fe30b694608712a3c413e0a1e0392976101b1f66adbca5863812d3d9d95c9993`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00ba8830",
  "phase": "reconstruction",
  "target": "0x00ba8830"
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
  "va": "0x00ba8830"
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
  "content_sha256": "748b8db3d49084668acc0f843c96bebc94055065f48f758fd1b5112da504f0bb",
  "live_attempts": [],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `present`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json

void FUN_00ba8830(int *param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  char cVar4;
  undefined **ppuVar5;
  undefined4 uVar6;
  int *piVar7;
  bool bVar8;
  undefined4 uVar9;
  cSpaceNames *local_1c [2];
  int local_14;
  int iStack_10;
  int local_c;
  int *piStack_4;
  
  iVar2 = (int)param_1;
  local_1c[0] = (cSpaceNames *)0x0;
  cVar4 = FUN_00bb9af0(0x8000);
  if (cVar4 != '\0') {
    *(undefined1 *)(iVar2 + 0xac) = 0;
  }
  if (*(char *)(iVar2 + 0xac) == '\0') {
    FUN_00bb9b00(0x100,0);
    local_1c[0] = Simulator__cSpaceNames__Get();
    param_1 = (int *)0x0;
    FUN_00ba61b0((uint)*(byte *)(iVar2 + 0xac) * 0x1000000 + *(int *)(iVar2 + 0x70),&param_1);
    bVar8 = PTR_DAT_0156c63c != PTR_DAT_0156c640;
    if (bVar8) {
      ppuVar5 = &PTR_DAT_0156c63c;
    }
    else {
      ppuVar5 = (undefined **)FUN_005ecf80(&local_14,0x7e1310a);
    }
    piVar3 = param_1;
    if (ppuVar5 != (undefined **)(param_1 + 6)) {
      FUN_00423650(*ppuVar5,ppuVar5[1]);
    }
    if (((!bVar8) && (2 < (int)(local_c - local_14 & 0xfffffffeU))) && (local_14 != 0)) {
      FUN_00f47380(local_14);
    }
    piVar3[0xb] = 2;
    piVar3[10] = 5;
    uVar9 = 0;
    piVar3[0x65] = 1;
    uVar6 = FUN_00989360(0);
    uVar6 = FUN_00ba8010(&local_14,uVar6);
    FUN_00b8dde0(uVar6,uVar9);
    *(undefined1 *)(piVar3 + 0x4c) = 1;
    piVar7 = (int *)FUN_00f48a80();
    iVar1 = *piVar7;
    uVar6 = FUN_00b8d8e0(&local_14);
    (**(code **)(iVar1 + 8))(uVar6);
    piVar3[0x2c] = iStack_10;
    uVar6 = 1;
    piVar3[0x2d] = local_14;
    piVar7 = piVar3;
    FUN_00b3d3d0(piVar3,1);
    FUN_0103c
[TRUNCATED]
```

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "original_bytes": 10768,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"ordinary_stack_argument_slots\": [\n      \"entry_ESP+0x4\"\n    ],\n    \"ordinary_stack_arguments\": [\n      {\n        \"entry_offset\": \"entry_ESP+0x4\",\n        \"observed\": true,\n        \"ordinal\": 1,\n        \"read\": false,\n        \"size_inferred\": false,\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      }\n    ],\n    \"ret_form\": \"RET 0x4\",\n    \"return_register\": \"XMM0\",\n    \"return_semantics\": \"float_or_x87_in_XMM0\",\n    \"saved_registers\": [\n      \"EBP\",\n      \"EBX\",\n      \"EDI\",\n      \"ESI\"\n    ],\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"entry_ESP+0x4\",\n        \"observed\": true,\n        \"ordinal\": 1,\n        \"read\": false,\n        \"size_inferred\": false,\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      }\n    ],\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"RET 0x4\"\n  },\n  \"abstained_because\": [\n    \"flow_not_modelled: the linear ESP walk ends at +184, so the listing is not one path\",\n    \"untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated\",\n    \"frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register\",\n    \"receiver_not_determinable: ecx_read_without_deref\",\n    \"variadic_not_decidable
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
