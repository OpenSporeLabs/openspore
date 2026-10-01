# Reconstruction context 0x00c0c0e0

- Status: `partial`
- Content SHA-256: `7bd93107adc890e9903b56204c43beed5a80a69243a342c383a1fe3d05f136f1`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00c0c0e0",
  "phase": "reconstruction",
  "target": "0x00c0c0e0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00c0c0e0",
  "package": null,
  "subsystem": "Simulator",
  "va": "0x00c0c0e0"
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
  "content_sha256": "c66aa3531259351334162a3fe5fe079a5acf3b00f05705be1ec15950673aa8ea",
  "live_attempts": [],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `present`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json

undefined4 __fastcall FUN_00c0c0e0(int param_1)

{
  if ((*(int *)(param_1 + 0xe84) != 0) && (*(char *)(*(int *)(param_1 + 0xe84) + 0x388) != '\0')) {
    return 1;
  }
  return 0;
}


```

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "original_bytes": 6093,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"receiver\": true,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"integral_in_EAX\",\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"RET\"\n  },\n  \"abstained_because\": [],\n  \"cleanup\": {\n    \"bytes\": 0,\n    \"confidence\": \"INFERRED\",\n    \"corroboration\": \"not_available\",\n    \"evidence\": \"ret with no immediate, no stack reads\",\n    \"side\": \"caller\"\n  },\n  \"completeness\": \"CORE_RESOLVED\",\n  \"conflicts\": [],\n  \"content_sha256\": \"0af8314106fbafa8d3b56011bc54f657bf8e1ea2c797c4cf7f3abe80fc00996c\",\n  \"conventions\": {\n    \"ambiguities\": [],\n    \"calling_convention\": \"__thiscall\",\n    \"candidate_conventions\": [\n      \"__thiscall\",\n      \"__fastcall\"\n    ],\n    \"confidence\": \"INFERRED\",\n    \"corroboration\": \"not_available\"\n  },\n  \"cross_validation\": {\n    \"agreement\": false,\n    \"ghidra\": \"no_information\",\n    \"ghidra_calling_convention\": null,\n    \"ghidra_parameter_count\": 0,\n    \"persisted\": \"no_information\",\n    \"persisted_calling_convention\": null\n  },\n  \"dispatch\": {\n    \"call_offsets\": [],\n    \"indirect_calls\": 0,\n    \"vtable_shaped_loads\": 0\n  },\n  \"inferences\": [\n    {\n      \"based_on\": [\n        \"obs-0004\",\n       
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
      "va": "0x00ace5a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae4fd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae73e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b18760"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b6b4c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba48b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba5e10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c042e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c045f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c05a80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c06f70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c07480"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c099e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c09fa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c1d640"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00acc4cc",
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
      "va": "0x00ace5a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae4fd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae73e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b18760"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b6b4c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba48b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba5e10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c042e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c045f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c05a80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c06f70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c07480"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c099e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c09fa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c1d640"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c20230"
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
    "Are the 0x00c0c0e8 and 0x00c0c0f1 branches semantically two different questions (link absent vs flag clear) that happen to share one exit, or one question tested twice? The machine merges them into one block and gives no way to tell.",
    "No runtime validation exists for this target: zero differential traces, so the whole reconstruction is static-only and the runtime dimension reports GATED.",
    "What class is the ECX receiver? The evidence pack carries no class association, no namespace and no SDK name for FUN_00c0c0e0, so none is claimed and the receiver stays opaque.",
    "What do the 61 call sites ask this predicate? The high fan-in makes an IsX-shaped reading attractive, but what is being queried is not recoverable from the body and is not claimed.",
    "What does the 32-bit word at 0xe84 point at? The machine only tests it against zero and uses it as an address, so it is modelled as an opaque base; the pointee's identity is unrecoverable from these 28 bytes.",
    "Why does the derived receiver record enumerate 0x120c when the listing shows only 0xe84 (through ECX) and 0x388 (through EAX)? 0x120c is not an operand of this body. It is either a base offset from a different derivation pass or evidence that the record's bounds conflate the two objects. It was deliberately not modelled.",
    "Why is the subsystem tag 'Simulator' when no type, string or vtable in the pack corroborates it? The tag comes from the index projection and this package found no evidence for or against it."
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
