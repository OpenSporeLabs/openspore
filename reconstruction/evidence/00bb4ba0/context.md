# Reconstruction context 0x00bb4ba0

- Status: `partial`
- Content SHA-256: `f67497e7b3fe410e1b03808965d565b9eec725f1411fe162891af636593993bf`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00bb4ba0",
  "phase": "reconstruction",
  "target": "0x00bb4ba0"
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
  "va": "0x00bb4ba0"
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
  "content_sha256": "9d6eb9935d3fdf030dd18196d0d18967855a88cbb7d17d3558dbc116b0f1f926",
  "live_attempts": [],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `present`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json

/* WARNING: Function: __alloca_probe replaced with injection: alloca_probe */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_00bb4ba0(int param_1)

{
  int *piVar1;
  int iVar2;
  tm *ptVar3;
  undefined1 **ppuVar4;
  int *piVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  undefined4 uStack_14b0;
  undefined4 uStack_14ac;
  undefined4 uStack_14a8;
  undefined1 *puStack_14a4;
  undefined1 *puStack_14a0;
  undefined1 *puStack_149c;
  undefined1 *puStack_1494;
  undefined1 *puStack_1490;
  undefined1 *puStack_148c;
  undefined4 auStack_1484 [9];
  int aiStack_1460 [11];
  int iStack_1434;
  undefined4 uStack_4;
  
  uStack_4 = 0xbb4baa;
  if (*(char *)(param_1 + 0x21c) == '\0') {
    return;
  }
  FUN_00ba6e00(0);
  FUN_00bac3a0();
  FUN_00baf880();
  piVar1 = (int *)FUN_00f48a80();
  (**(code **)(*piVar1 + 0x20))(L"PlanetScripts");
  iVar2 = FUN_01021300();
  if (iVar2 != 0) {
    if (*(int *)(param_1 + 0x1dc) != 0) {
      _time64((__time64_t *)0x0);
      ptVar3 = _localtime64((__time64_t *)&stack0xffffeb40);
      if (ptVar3 == (tm *)0x0) {
        iVar2 = *(int *)(param_1 + 0x1dc);
        *(undefined4 *)(iVar2 + 0x18) = 0;
        *(undefined4 *)(iVar2 + 0x1c) = 0;
        *(undefined4 *)(iVar2 + 0x20) = 0;
        *(undefined4 *)(iVar2 + 0x24) = 0;
        *(undefined4 *)(iVar2 + 0x28) = 0;
        *(undefined4 *)(iVar2 + 0x2c) = 0;
        *(undefined4 *)(iVar2 + 0x30) = 0;
        *(undefined4 *)(iVar2 + 0x34) = 0;
        *(undefined4 *)(iVar2 + 0x38) = 0;
      }
      else {
        piVar1 = (int *)(*(i
[TRUNCATED]
```

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "original_bytes": 13370,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": [\n      \"entry_ESP+0x8\",\n      \"entry_ESP+0xc\"\n    ],\n    \"ordinary_stack_argument_slots_bounded\": {\n      \"kept\": 2,\n      \"omitted\": 16\n    },\n    \"ordinary_stack_arguments\": [\n      {\n        \"entry_offset\": \"entry_ESP+0x8\",\n        \"observed\": true,\n        \"ordinal\": 2,\n        \"read\": false,\n        \"size_inferred\": false,\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      },\n      {\n        \"entry_offset\": \"entry_ESP+0xc\",\n        \"observed\": true,\n        \"ordinal\": 3,\n        \"read\": false,\n        \"size_inferred\": false,\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      }\n    ],\n    \"ordinary_stack_arguments_bounded\": {\n      \"kept\": 2,\n      \"omitted\": 16\n    },\n    \"receiver\": true,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"unclassified_in_EAX\",\n    \"saved_registers\": [\n      \"EBP\",\n      \"EBX\",\n      \"EDI\",\n      \"ESI\"\n    ],\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"entry_ESP+0x8\",\n        \"observed\": true,\n        \"ordinal\": 2,\n        \"read\": false,\n        \"size_inferred\": false,\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      },\n      {\n        \"entry_o
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
        "0x00bb4100",
        "0x00bb42a0",
        "0x00bb4af0",
        "0x00bb4ba0",
        "0x00bb4c90",
        "0x00bb4af0",
        "0x00bb4100",
        "0x00bb42a0",
        "0x00bb4ba0",
        "0x00bb4c90",
        "0x00e7fd00",
        "0x00e74a20",
        "0x00bb42a0",
        "0x00bb4c90",
        "0x00e74a20",
        "0x00e74a20"
      ],
      "conflict_id": "U-004-star-generation-boundary",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "0x00bb4100 and 0x00bb4ba0 are coherent current bodies; SDK addresses 0x00bb42a0 and 0x00bb4c90 are retained as interior/alias candidates. mPlanetCount creation is visible, but append/materialization order is not.",
      "resolution_status": "0x00bb4100 and 0x00bb4ba0 are coherent current bodies; SDK addresses 0x00bb42a0 and 0x00bb4c90 are retained as interior/alias candidates. mPlanetCount creation is visible, but append/materialization order is not.",
      "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
      "subject": null,
      "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
    },
    {
      "anchors": [
        "0x00b28ec0",
        "0x00b294c0",
        "0x00bb4ba0",
        "0x00bb4ba0",
        "0x00693900",
        "0x00693900",
        "0x00693900",
        "0x00693900",
        "0x00693d60",
        "0x00693d60",
        "0x00693d60",
        "0x00693d60",
        "0x006a1540",
        "0x006a2f60",
        "0x006a1540",
        "0x006a2f60"
      
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
