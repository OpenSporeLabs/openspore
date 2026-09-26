# Reconstruction context 0x00bba2a0

- Status: `partial`
- Content SHA-256: `c1afaa8d350d596f87a22b78865ecba6dd4beede9ee7aa6dabd57e5934df06a0`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00bba2a0",
  "phase": "reconstruction",
  "target": "0x00bba2a0"
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
  "va": "0x00bba2a0"
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
  "content_sha256": "c27ed8c2d47ecaf0292f9a9ddd10642402db9db4dc162b78f4f8ea0068504f07",
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

void __fastcall cStarRecord__ctor(int param_1)

{
  char cVar1;
  intrusive_ptr<Simulator::cPlanet> *unaff_EBX;
  int iVar2;
  cPlanetRecord *unaff_EBP;
  int iVar3;
  int iVar4;
  ISimulatorStrategy__vftable **ppIVar5;
  cStarManager *this;
  undefined4 uVar6;
  undefined4 local_2c;
  int local_24;
  int local_20;
  int local_14;
  ISimulatorStrategy__vftable *local_10;
  IVirtual__vftable *local_c;
  undefined1 *local_8;
  
  iVar2 = *(int *)(param_1 + 0x4c);
  iVar4 = 0;
  local_24 = 0;
  if (iVar2 == 2) {
    local_2c = 0x876201aa;
  }
  else if (iVar2 == 4) {
    local_2c = 0xefc33700;
  }
  else {
    if (iVar2 != 5) {
      *(undefined4 *)(param_1 + 0x78) = 0;
      *(undefined4 *)(param_1 + 0x7c) = 0;
      *(undefined4 *)(param_1 + 0x74) = 0;
      *(undefined4 *)(param_1 + 0x80) = 0;
      return;
    }
    uVar6 = *(undefined4 *)(param_1 + 0x54);
    local_2c = 0xfc5a17bc;
    FUN_00b3d2a0(uVar6);
    local_24 = FUN_00ba9370(uVar6);
  }
  local_20 = 100;
  iVar2 = 0;
  iVar3 = 0;
  local_14 = 0;
  Simulator__cPlanetModel__Get();
  while (((iVar2 == 0 ||
          (((iVar2 == *(int *)(param_1 + 0x74) && (iVar3 == *(int *)(param_1 + 0x78))) &&
           (local_14 == *(int *)(param_1 + 0x7c))))) && (local_20 = local_20 + -1, -1 < local_20)))
  {
    if (local_24 == 0) {
      iVar4 = FUN_00ac10a0(local_2c);
    }
    else {
      iVar4 = FUN_00ac1190(*(undefined4 *)(local_24 + 0x58));
    }
    if (iVar4 == 0) goto LAB_00bba410;
[TRUNCATED]
```

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "original_bytes": 15085,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": [\n      \"entry_ESP+0x4\",\n      \"entry_ESP+0x8\",\n      \"entry_ESP+0xc\",\n      \"entry_ESP+0x10\",\n      \"entry_ESP+0x14\",\n      \"entry_ESP+0x18\",\n      \"entry_ESP+0x1c\",\n      \"entry_ESP+0x20\"\n    ],\n    \"ordinary_stack_arguments\": [\n      {\n        \"entry_offset\": \"entry_ESP+0x4\",\n        \"observed\": true,\n        \"ordinal\": 1,\n        \"read\": false,\n        \"size_inferred\": false,\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      },\n      {\n        \"entry_offset\": \"entry_ESP+0x8\",\n        \"observed\": true,\n        \"ordinal\": 2,\n        \"read\": false,\n        \"size_inferred\": false,\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      },\n      {\n        \"entry_offset\": \"entry_ESP+0xc\",\n        \"observed\": true,\n        \"ordinal\": 3,\n        \"read\": false,\n        \"size_inferred\": false,\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      },\n      {\n        \"entry_offset\": \"entry_ESP+0x10\",\n        \"observed\": true,\n        \"ordinal\": 4,\n        \"read\": false,\n        \"size_inferred\": true,\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      },\n      {\n        \"entry_offset\": \"entry_ESP+0x14\",\n        \"observe
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
