# Reconstruction context 0x00c12410

- Status: `partial`
- Content SHA-256: `ea7f0e69c2cc6da41a82d7ca37d384c06659d6aee5681c8617e65750755f7a84`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00c12410",
  "phase": "reconstruction",
  "target": "0x00c12410"
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
  "va": "0x00c12410"
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
  "content_sha256": "ac2012ffbbac2a335a52babefc2de021faf4a347252bf6b61dcd6470e588bd3f",
  "live_attempts": [],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `present`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint __thiscall
FUN_00c12410(int *param_1,int param_2,float param_3,char param_4,char param_5,char param_6,
            char param_7,char param_8)

{
  float fVar1;
  float fVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  float *pfVar6;
  uint uVar7;
  float10 fVar8;
  float10 fVar9;
  int iStack_24;
  float fStack_1c;
  uint uStack_18;
  uint uStack_14;
  float fStack_c;
  float fStack_8;
  uint uStack_4;
  
  if ((param_5 == '\0') && (param_1[0x3a3] != -1)) {
    return 0xffffffff;
  }
  uVar7 = 0;
  fVar8 = (float10)FUN_00d38a30(0,param_1);
  uStack_4 = (**(code **)(*param_1 + 0xb0))();
  _param_5 = -1.0;
  uStack_18 = 0xffffffff;
  fStack_1c = 3.4028235e+38;
  if (uStack_4 != 0) {
    iStack_24 = 0;
    do {
      iVar3 = param_1[0x30a];
      iVar5 = (**(code **)(*param_1 + 0xb4))(uVar7);
      if ((((param_2 == 0) ||
           ((uVar4 = *(uint *)(iVar5 + 8), uVar4 < 0x58 &&
            ((*(uint *)(param_2 + (uVar4 >> 5) * 4) & 1 << ((byte)uVar4 & 0x1f)) != 0)))) &&
          (*(int *)(iVar5 + 0xc) == 1)) &&
         ((((*(char *)(iVar5 + 0x114) == '\0' &&
            ((*(float *)(iVar5 + 0x104) <= 0.0 ||
             (*(float *)(iVar5 + 0x104) <= (float)param_1[0x396])))) &&
           ((param_4 != '\0' || (1.0 <= *(float *)(iVar3 + iStack_24 + 4))))) &&
          ((param_7 != '\0' ||
           (param_3 <= (*(float *)(iVar5 + 0xf4) + *(float *)(iVar5 + 0xa8)) * (float)fVar8)))))) {
        if (param_6 == '\0') {
          fVar1 = _DAT_01582efc + param_3;
          uStack_14 = CONC
[TRUNCATED]
```

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "original_bytes": 21493,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": [\n      \"entry_ESP+0x4\",\n      \"entry_ESP+0x8\",\n      \"entry_ESP+0xc\",\n      \"entry_ESP+0x10\",\n      \"entry_ESP+0x14\",\n      \"entry_ESP+0x18\",\n      \"entry_ESP+0x1c\",\n      \"entry_ESP+0x20\",\n      \"entry_ESP+0x28\",\n      \"entry_ESP+0x2c\",\n      \"entry_ESP+0x30\",\n      \"entry_ESP+0x34\",\n      \"entry_ESP+0x3c\",\n      \"entry_ESP+0x40\"\n    ],\n    \"ordinary_stack_arguments\": [\n      {\n        \"entry_offset\": \"entry_ESP+0x4\",\n        \"observed\": true,\n        \"ordinal\": 1,\n        \"read\": false,\n        \"size_inferred\": false,\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      },\n      {\n        \"entry_offset\": \"entry_ESP+0x8\",\n        \"observed\": true,\n        \"ordinal\": 2,\n        \"read\": false,\n        \"size_inferred\": false,\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      },\n      {\n        \"entry_offset\": \"entry_ESP+0xc\",\n        \"observed\": true,\n        \"ordinal\": 3,\n        \"read\": false,\n        \"size_inferred\": false,\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      },\n      {\n        \"confidence\": \"UNKNOWN\",\n        \"entry_offset\": \"entry_ESP+0x10\",\n        \"observed\": true,\n        \"ordinal\": 4,\n        \"read\": false,\n        \"size_inferred\": false,\n  
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
