# Reconstruction context 0x007c3f70

- Status: `partial`
- Content SHA-256: `9e3e87a631386eb73509a86ae8af8d5c86a400eda421c565c496bae5860488a7`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x007c3f70",
  "phase": "reconstruction",
  "target": "0x007c3f70"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_007c3f70",
  "package": null,
  "subsystem": "Terrain",
  "va": "0x007c3f70"
}
```

## 03_current_status

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "blocked": false,
  "reconstructed": false,
  "runtime_gated": false,
  "runtime_validated": 0,
  "status": "candidate"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "65e3cf8d92f8f547df174e97ac20c851df2fff53b475b5699f46ef77d5419386",
  "live_attempts": [],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `present`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json

void __fastcall FUN_007c3f70(int param_1)

{
  *(undefined4 *)(param_1 + 0x140) = DAT_01635db8;
  *(undefined4 *)(param_1 + 0x144) = DAT_01635dbc;
  *(undefined4 *)(param_1 + 0x148) = DAT_01635dc0;
  *(undefined4 *)(param_1 + 0x14c) = DAT_01635dc4;
  *(undefined4 *)(param_1 + 0x150) = 0;
  *(undefined4 *)(param_1 + 0x154) = 0;
  *(undefined4 *)(param_1 + 0x158) = 0;
  *(undefined4 *)(param_1 + 0x15c) = 0x461c4000;
  *(undefined4 *)(param_1 + 0x160) = 0x461c4000;
  *(undefined4 *)(param_1 + 0x164) = 0x461c4000;
  *(undefined4 *)(param_1 + 0x168) = 0x461c4000;
  *(undefined1 *)(param_1 + 0x16c) = 1;
  *(undefined4 *)(param_1 + 0x170) = 0;
  return;
}


```

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "original_bytes": 6632,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"receiver\": true,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET\",\n    \"return_register\": \"XMM0\",\n    \"return_semantics\": \"float_or_x87_in_XMM0\",\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"RET\"\n  },\n  \"abstained_because\": [],\n  \"cleanup\": {\n    \"bytes\": 0,\n    \"confidence\": \"INFERRED\",\n    \"corroboration\": \"not_available\",\n    \"evidence\": \"ret with no immediate, no stack reads\",\n    \"side\": \"caller\"\n  },\n  \"completeness\": \"CORE_RESOLVED\",\n  \"conflicts\": [],\n  \"content_sha256\": \"63fd321d08aa03c16d29c06c7374111c435af7b1c705d704c9782cbd1cdca7cf\",\n  \"conventions\": {\n    \"ambiguities\": [],\n    \"calling_convention\": \"__thiscall\",\n    \"candidate_conventions\": [\n      \"__thiscall\",\n      \"__fastcall\"\n    ],\n    \"confidence\": \"INFERRED\",\n    \"corroboration\": \"not_available\"\n  },\n  \"cross_validation\": {\n    \"agreement\": false,\n    \"ghidra\": \"no_information\",\n    \"ghidra_calling_convention\": null,\n    \"ghidra_parameter_count\": 0,\n    \"persisted\": \"no_information\",\n    \"persisted_calling_convention\": null\n  },\n  \"dispatch\": {\n    \"call_offsets\": [],\n    \"indirect_calls\": 0,\n    \"vtable_shaped_loads\": 0\n  },\n  \"inferences\": [\n    {\n      \"based_on\": [\n        \"obs-0007\"\n  
[TRUNCATED]
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00430e70"
    },
    {
      "name": "Editors::cEditor::Initialize",
      "reconstructed": false,
      "va": "0x00584300"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006f5260"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006f69c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0076acd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0076b460"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0076b720"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0076d8e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00776f40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0077f040"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007b2ab0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007b2ca0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007b2f40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007b31f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007b3760"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007b91f0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x0043126a",
      "direction": "in",
      "other": "0x00430e70",
      "reference_ty
[TRUNCATED]
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
  "runtime": {
    "blocking_reason": null,
    "gates": [],
    "validated": 0
  },
  "semantic": {}
}
```

## 10_dependencies

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00430e70"
    },
    {
      "name": "Editors::cEditor::Initialize",
      "reconstructed": false,
      "va": "0x00584300"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006f5260"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006f69c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0076acd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0076b460"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0076b720"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0076d8e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00776f40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0077f040"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007b2ab0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007b2ca0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007b2f40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007b31f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007b3760"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007b91f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007b9420"
    },
    {
      "n
[TRUNCATED]
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "pkg-swarm-w1-00f9b7f0",
    "score": 6,
    "symbol": "re_00f9b7f0",
    "va": "0x00f9b7f0"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [],
  "handoffs": [],
  "metadata": []
}
```

## 13_semantic_hypotheses

- State: `missing`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

## 14_conflicts_questions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json, knowledgegraph/research/semantic-decomp.json`

```json
{
  "conflicts": [],
  "unresolved_questions": [
    "Class, vtable identity and SDK name are unknown: this binary carries no MSVC RTTI and the entry is not in any vtable slot per the record's dispatch counts (0 indirect calls, 0 vtable-shaped loads).",
    "No runtime value is claimed for the four writable .data globals 0x01635db8..0x01635dc4; /read_memory shows zeros in the static image, which is not a claim about the running program.",
    "The bytes below 0x140 are never touched by this body; no evidence here says which code initialises them.",
    "Whether any of the 65 call sites reads the residual XMM0 (which still holds the 0x013f0620 word at the RET) was not established; the entry is declared void on the grounds that no instruction produces a result.",
    "__thiscall vs __fastcall: the derived record keeps both open; every observed site loads ECX and pushes nothing, but nothing rules out __fastcall with a discarded EDX."
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'derived'}, {'mode': 'derived', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'derived'}, {'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /decompile_function @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}`

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
