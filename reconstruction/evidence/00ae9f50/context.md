# Reconstruction context 0x00ae9f50

- Status: `partial`
- Content SHA-256: `3451d38db01e1a479c977ece4641978cc8ea6210c8cad44cb47e61176351e0fd`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00ae9f50",
  "phase": "reconstruction",
  "target": "0x00ae9f50"
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
  "va": "0x00ae9f50"
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
  "content_sha256": "ccb684b58d611003b5d20a529cac10bd64e3a479c8f6ac74891649fe29fdf8e9",
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

void __fastcall FUN_00ae9f50(int param_1)

{
  wchar16 *pwVar1;
  void *pvVar2;
  IAppSystem *pIVar3;
  void *pvVar4;
  int iVar5;
  int *piVar6;
  undefined4 uVar7;
  cToolManager *pcVar8;
  bool bVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  undefined4 uVar12;
  undefined4 uVar13;
  undefined1 local_80 [56];
  undefined4 local_48;
  void *pvStack_44;
  IAppSystem *pIStack_1c;
  undefined4 uStack_14;
  
  FUN_00dd1ca0();
  FUN_00dd30d0();
  iVar5 = *(int *)(param_1 + 0x20);
  if (iVar5 != 0) {
    bVar9 = *(int *)(iVar5 + 0xc) != 0;
    if (bVar9) {
      pvVar2 = (void *)0x0;
    }
    else {
      uVar7 = *(undefined4 *)(iVar5 + 0x18);
      FUN_00b3d2a0(uVar7);
      pvVar2 = (void *)FUN_00ba9370(uVar7);
    }
    local_80._48_4_ = (IAppSystem *)0x3ac86b5;
    LOCK();
    local_80._4_4_ = (string16 *)0x0;
    UNLOCK();
    iVar5 = *(int *)(param_1 + 0x20);
    local_80._0_4_ = &PTR_FUN_013eb844;
    local_48 = 0;
    local_80._8_4_ = *(undefined4 *)(iVar5 + 0xc);
    local_80._16_4_ = pvVar2;
    if (bVar9) {
      uVar7 = *(undefined4 *)(iVar5 + 0x18);
      FUN_00b3d300(uVar7);
      FUN_00b20750(uVar7);
      local_80._16_4_ = *(void **)(iVar5 + 0x28);
      if (*(void **)(iVar5 + 0x28) == (void *)0x0) {
        local_80._16_4_ = FUN_00bd9bf0();
      }
    }
    pwVar1 = *(wchar16 **)(param_1 + 0x20);
    if (bVar9) {
      local_80._24_4_ = *(undefined4 *)(pwVar1 + 0x10);
      local_80._32_4_ = *(undefined4 *)(pwVar1 + 0x12
[TRUNCATED]
```

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "original_bytes": 22881,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"receiver\": true,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"unclassified_in_EAX\",\n    \"saved_registers\": [\n      \"EBP\",\n      \"EBX\",\n      \"EDI\",\n      \"ESI\"\n    ],\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"RET\"\n  },\n  \"abstained_because\": [\n    \"flow_not_modelled: the linear ESP walk ends at +68, so the listing is not one path\",\n    \"untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated\",\n    \"frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register\"\n  ],\n  \"cleanup\": {\n    \"bytes\": 0,\n    \"confidence\": \"INFERRED\",\n    \"corroboration\": \"not_available\",\n    \"evidence\": \"ret with no immediate, no stack reads\",\n    \"side\": \"caller\"\n  },\n  \"completeness\": \"CORE_RESOLVED\",\n  \"conflicts\": [],\n  \"content_sha256\": \"2a9d66fa2f581e93375f884c53094afd305f2916c8a294f713f2cd8f3e8db8d5\",\n  \"conventions\": {\n    \"ambiguities\": [],\n    \"calling_convention\": \"__thiscall\",\n    \"candidate_conventions\": [\n      \"__thiscall\",\n      \"__fastcall\"\n    ],\n    \"confidence\": \"INFERRED\",\n    
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

- State: `conflicted`
- Provenance: `reconstruction/knowledge/index.json, knowledgegraph/research/semantic-decomp.json`

```json
{
  "conflicts": [
    {
      "anchors": [
        "0x00b3d2a0",
        "0x00b3d300",
        "0x00b5b800",
        "0x01021300",
        "0x01021300",
        "0x00ad23c0",
        "0x00adbca0",
        "0x00ae73e0",
        "0x00ae9590",
        "0x00ae9930",
        "0x00ae9c90",
        "0x00ae9f50",
        "0x00aeb3e0",
        "0x00aeb3e0",
        "0x00aebe90",
        "0x00b25fb0"
      ],
      "conflict_id": "global_root_identities",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
      "resolution_status": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
      "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
      "subject": null,
      "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
    },
    {
      "anchors": [
        "0x0067dcc0",
        "0x0067deb0",
        "0x00b3d330",
        "0x00b3d4e0",
        "0x015fd890",
        "0x0167eaf0",
        "0x0167eb60",
        "0x0067dcc0",
        "0x00ad23c0",
        "0x00adbca0",
        "0x00ae73e0",
        "0x00ae9590",
        "0x00ae9930",
        "0x00ae9c90",
        "0x00ae9f50",
        "0x00aeb3e0"
      ],
      "conflict_id": "global_service_publication",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The committed evidence does not es
[TRUNCATED]
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
