# Reconstruction context 0x00c0bc00

- Status: `partial`
- Content SHA-256: `a40e06e48d5f4a2a59c528199c804ebcfd314c402fb239899cbf7fe564f32a36`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00c0bc00",
  "phase": "reconstruction",
  "target": "0x00c0bc00"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00c0bc00",
  "package": null,
  "subsystem": "Simulator",
  "va": "0x00c0bc00"
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
  "content_sha256": "1d61a9e0b6b48382b04299fb41a18fc6df54b51c8f55fb2803eb78b0a7f5df9b",
  "live_attempts": [],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `present`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json

int __fastcall FUN_00c0bc00(int param_1)

{
  if (*(int *)(param_1 + 0xb20) != 0) {
    return *(int *)(param_1 + 0xb20) + 0x504;
  }
  return param_1 + 0xb28;
}


```

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "original_bytes": 6127,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"receiver\": true,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"unclassified_in_EAX\",\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"RET\"\n  },\n  \"abstained_because\": [],\n  \"cleanup\": {\n    \"bytes\": 0,\n    \"confidence\": \"INFERRED\",\n    \"corroboration\": \"not_available\",\n    \"evidence\": \"ret with no immediate, no stack reads\",\n    \"side\": \"caller\"\n  },\n  \"completeness\": \"CORE_RESOLVED\",\n  \"conflicts\": [],\n  \"content_sha256\": \"3fd5a718dce8944f404c6ef645a35ad78716ea7f29df3ca6bf226234ad0b3fc0\",\n  \"conventions\": {\n    \"ambiguities\": [],\n    \"calling_convention\": \"__thiscall\",\n    \"candidate_conventions\": [\n      \"__thiscall\",\n      \"__fastcall\"\n    ],\n    \"confidence\": \"INFERRED\",\n    \"corroboration\": \"not_available\"\n  },\n  \"cross_validation\": {\n    \"agreement\": false,\n    \"ghidra\": \"no_information\",\n    \"ghidra_calling_convention\": null,\n    \"ghidra_parameter_count\": 0,\n    \"persisted\": \"no_information\",\n    \"persisted_calling_convention\": null\n  },\n  \"dispatch\": {\n    \"call_offsets\": [],\n    \"indirect_calls\": 0,\n    \"vtable_shaped_loads\": 0\n  },\n  \"inferences\": [\n    {\n      \"based_on\": [\n        \"obs-0003\",\n   
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
      "va": "0x00acc390"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba4600"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba4f30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba5e10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c07480"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c23e90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c267e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c2ed20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cd7320"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cf50e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d1e720"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d2ffd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d39360"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d3a5a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d3c6a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d3d4f0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00acc4ee",
      "direction": "in",
      "other": "0x00acc390",
      "reference_type": "direct-call"
    },

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
      "va": "0x00acc390"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba4600"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba4f30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba5e10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c07480"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c23e90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c267e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c2ed20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cd7320"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cf50e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d1e720"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d2ffd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d39360"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d3a5a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d3c6a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d3d4f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d3fcf0"
    },
    {
      "name": null,
      "reconst
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
    "package": "PKG-11-H4-HELPER-WAVE3",
    "score": 6,
    "symbol": "address_window_offset_005c65e0",
    "va": "0x005c65e0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-SIMULATOR-SAFE-WAVE11",
    "score": 6,
    "symbol": "dispatch_key_00628450",
    "va": "0x00628450"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-SIMULATOR-SAFE-WAVE11",
    "score": 6,
    "symbol": "cycle_key_006286a0",
    "va": "0x006286a0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-SIMULATOR-SAFE-WAVE11",
    "score": 6,
    "symbol": "release_child_0062c910",
    "va": "0x0062c910"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 6,
    "symbol": "FUN_00b3d2a0",
    "va": "0x00b3d2a0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 6,
    "symbol": "FUN_00b3d300",
    "va": "0x00b3d300"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 6,
    "symbol": "Simulator_GetUIMissionLogManager",
    "va": "0x00b3d4f0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-13-E4-EMPIRE-WAVE3",
    "score": 6,
    "symbol": "EmpirePoliticalColor_00c32cd0",
    "va": "0x00c32cd0"
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
    "All 68 callers are unnamed in the record and unreconstructed; their contracts would fix the pointee type and confirm the inline-or-indirect reading.",
    "Runtime is GATED with 0 original-process observations validated, so nothing here is differentially confirmed against the running game; the mutation test and the byte-level oracle are the only evidence.",
    "The owning class/type. No MSVC RTTI in this binary, no vtable reference, no SDK name; the package asserts no type and the receiver stays opaque.",
    "What the word at receiver+0xb20 is. ADD EAX,0x504 favours 'pointer to a separate block whose payload begins 0x504 bytes in', but no evidence in this pack establishes it; the interpretation is left unclaimed.",
    "Whether receiver+0xb28 is inline storage for the same payload, and what 0x504 counts (bytes from a block base, or a header offset)."
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
