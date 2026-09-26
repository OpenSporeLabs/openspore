# Reconstruction context 0x00b25fe0

- Status: `partial`
- Content SHA-256: `5177543fd71c9d73795c728393f001a0698191b057d938fb3d688318edd5422f`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00b25fe0",
  "phase": "reconstruction",
  "target": "0x00b25fe0"
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
  "va": "0x00b25fe0"
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
  "content_sha256": "7ed0bd48b88f2da2e3c693a0a8f44ddec552f0f417f9d4cf8ffa946d5c38e786",
  "live_attempts": [],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `present`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json

void __fastcall FUN_00b25fe0(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int *piVar5;
  int *piStack_1c;
  int *piStack_18;
  int *piStack_14;
  
  FUN_00b22960();
  FUN_00b22650(0x18eb45e);
  FUN_00b22650(0x2c9cc91);
  FUN_00b22650(0x2e96892);
  FUN_00b22650(&DAT_018c84a9);
  FUN_00b22650(0x1be418e);
  piVar4 = *(int **)(param_1 + 0x58);
  if (piVar4 != (int *)0x0) {
    *(undefined4 *)(param_1 + 0x58) = 0;
    (**(code **)(*piVar4 + 4))();
  }
  FUN_00b22650(0x2a8fb3f);
  FUN_00b22650(0x2a034cd);
  FUN_00b22650(&DAT_018c6de8);
  FUN_00b22650(&DAT_018c88e4);
  FUN_00b22650(0x3a2511e);
  FUN_00b22650(0x403df5c);
  FUN_00b22650(0x61494be);
  FUN_00b22650(0x629bafe);
  FUN_00b3d2b0();
  uVar1 = FUN_00ac79d0();
  FUN_00b3d2b0(uVar1);
  FUN_00ac7a40(uVar1);
  iVar2 = FUN_00b21340(&LAB_00cd7d10,&LAB_00d3d420,&LAB_00ad48b0,&LAB_00b1e500,0x18ebadc);
  FUN_00b93c60(*(int *)(iVar2 + 8) - *(int *)(iVar2 + 4) >> 2,iVar2 + 0x10);
  piVar4 = piStack_14;
  FUN_00829110(&piStack_1c,*(undefined4 *)(iVar2 + 4),*(undefined4 *)(iVar2 + 8),piStack_14,
               piStack_18);
  piVar5 = piStack_1c;
  for (; piVar4 != piVar5; piVar4 = piVar4 + 1) {
    iVar2 = *(int *)(*piVar4 + 0x714);
    if (((iVar2 != 0) && (iVar2 != 8)) && (iVar2 != 3)) {
      FUN_0102c340(*piVar4,0);
    }
  }
  FUN_00b22650(0x2dd8c42);
  FUN_00b22650(0x4e3fab5);
  FUN_00b22650(&DAT_018c6d19);
  FUN_00b22650(0x24270c9);
  FUN_00b22650(&DAT_018c43e8);
  FUN_00b22650(0x18eb4b7);
  FUN_00b25ee0();
  iVar2 = FUN_00b21340(&LAB_00cd7d10,&LAB_00ae7060,&LAB_00ae7080,&LAB_00b1e520,&DAT_0142d
[TRUNCATED]
```

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "original_bytes": 21244,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"receiver\": true,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"unclassified_in_EAX\",\n    \"saved_registers\": [\n      \"EBP\",\n      \"EBX\",\n      \"EDI\",\n      \"ESI\"\n    ],\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"RET\"\n  },\n  \"abstained_because\": [\n    \"unparsed_lines_present: 4 line(s) matched no grammar rule\",\n    \"esp_alignment_unknown: the entry-relative ESP offset is unknown and there is no frame pointer to fall back on\"\n  ],\n  \"cleanup\": {\n    \"bytes\": 0,\n    \"confidence\": \"INFERRED\",\n    \"corroboration\": \"not_available\",\n    \"evidence\": \"ret with no immediate, no stack reads\",\n    \"side\": \"caller\"\n  },\n  \"completeness\": \"PARTIAL\",\n  \"conflicts\": [],\n  \"content_sha256\": \"9cd19b16808ec86ca3e5c28155a57d7d66c138c33c07fe7c5ad070e3131d9914\",\n  \"conventions\": {\n    \"ambiguities\": [\n      \"esp_alignment_unknown\"\n    ],\n    \"calling_convention\": null,\n    \"candidate_conventions\": [\n      \"__cdecl\",\n      \"__stdcall\",\n      \"__thiscall\",\n      \"__fastcall\"\n    ],\n    \"confidence\": \"UNKNOWN\",\n    \"corroboration\": \"not_available\"\n  },\n  \"cross_validation\": {\n    \"agreement\": false,\n    \"ghidra\": \"no_information\",\n    \"ghidra_calling_convention\": null,\n    \
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
