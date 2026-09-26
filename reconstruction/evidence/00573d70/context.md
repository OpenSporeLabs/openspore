# Reconstruction context 0x00573d70

- Status: `partial`
- Content SHA-256: `bd420d7d4c37c3cc7cb845a9d43128e1c47793ee180d1b73373b4f8af6c9395e`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00573d70",
  "phase": "reconstruction",
  "target": "0x00573d70"
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
  "va": "0x00573d70"
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
  "content_sha256": "2690a0b5850683b8a42ce17b7eb3c9492692b570939379efbb5c1a2a89be5c02",
  "live_attempts": [],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `present`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json

void __thiscall FUN_00573d70(int param_1,int *param_2)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  
  if ((param_2 == (int *)0x0) && (*(char *)(param_1 + 0x140) == '\0')) {
    *(undefined1 *)(param_1 + 0x140) = 1;
  }
  piVar1 = (int *)(param_1 + 0xe4);
  if ((param_2 != *(int **)(param_1 + 0xe4)) ||
     ((*(int **)(param_1 + 0xe4) != (int *)0x0 && (iVar3 = FUN_0047ec20(), iVar3 != 0)))) {
    if ((*(int **)(param_1 + 0xf4) != (int *)0x0) && (*(int **)(param_1 + 0xf4) != param_2)) {
      if (*(char *)(param_1 + 0x140) == '\0') {
        *(undefined1 *)(param_1 + 0x140) = 1;
      }
      *(undefined4 *)(param_1 + 0xf4) = 0;
    }
    if ((int *)*piVar1 != param_2) {
      if (((param_2 != (int *)0x0) && (iVar3 = FUN_0047e6c0(), iVar3 != 0)) &&
         ((*(uint *)(iVar3 + 0xdc8) >> 0xb & 1) != 0)) {
        *(undefined1 *)(param_1 + 0x140) = 0;
      }
      if (((int *)*piVar1 != (int *)0x0) &&
         ((**(code **)(*(int *)*piVar1 + 0x30))(3,1), *(char *)(param_1 + 0x141) != '\0')) {
        if (((int *)*piVar1 != (int *)0x0) &&
           ((iVar3 = (**(code **)(*(int *)*piVar1 + 0xc))(0x50a993c), iVar3 != 0 &&
            (iVar4 = FUN_0047e6c0(), iVar4 != 0)))) {
          FUN_0047e6c0();
          uVar6 = 1;
          uVar5 = FUN_0043c3d0(iVar3);
          FUN_0043e7e0(uVar5,uVar6);
        }
        *(undefined1 *)(param_1 + 0x141) = 0;
      }
      piVar2 = (int *)*piVar1;
      if (param_2 != piVar2) {
        if (param_2 != (int *)0x0) {
          (**(code **)*param_2)();
        }
        *piVar1 = (int
[TRUNCATED]
```

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "original_bytes": 16778,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": [\n      \"entry_ESP+0x4\"\n    ],\n    \"ordinary_stack_arguments\": [\n      {\n        \"entry_offset\": \"entry_ESP+0x4\",\n        \"observed\": true,\n        \"ordinal\": 1,\n        \"read\": false,\n        \"size_inferred\": false,\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      }\n    ],\n    \"receiver\": true,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET 0x8\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"unclassified_in_EAX\",\n    \"saved_registers\": [\n      \"EBP\",\n      \"EBX\",\n      \"EDI\",\n      \"ESI\"\n    ],\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"entry_ESP+0x4\",\n        \"observed\": true,\n        \"ordinal\": 1,\n        \"read\": false,\n        \"size_inferred\": false,\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      }\n    ],\n    \"stack_cleanup_bytes\": 8,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"RET 0x8\"\n  },\n  \"abstained_because\": [\n    \"flow_not_modelled: the linear ESP walk ends at +32, so the listing is not one path\",\n    \"untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated\",\n    \"frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP 
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
