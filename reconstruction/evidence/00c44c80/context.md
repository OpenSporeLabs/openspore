# Reconstruction context 0x00c44c80

- Status: `partial`
- Content SHA-256: `bdfdd88252816b0074a6a4baf768df8ae793c8bdab875e5c0ada296cdd3d34fb`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00c44c80",
  "phase": "reconstruction",
  "target": "0x00c44c80"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00c44c80",
  "package": null,
  "subsystem": "Simulator",
  "va": "0x00c44c80"
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
  "content_sha256": "032ad12628111b0896fe50274ec885500398a5d8cfffe7507ee4bbb0678ac2f8",
  "live_attempts": [],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `present`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json

bool __fastcall FUN_00c44c80(int param_1)

{
  return *(int *)(param_1 + 0x84) == 3;
}


```

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "original_bytes": 5748,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"receiver\": true,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"unclassified_in_EAX\",\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"RET\"\n  },\n  \"abstained_because\": [],\n  \"cleanup\": {\n    \"bytes\": 0,\n    \"confidence\": \"INFERRED\",\n    \"corroboration\": \"not_available\",\n    \"evidence\": \"ret with no immediate, no stack reads\",\n    \"side\": \"caller\"\n  },\n  \"completeness\": \"CORE_RESOLVED\",\n  \"conflicts\": [],\n  \"content_sha256\": \"2085c360d0815a1223dfd27835e9582b92b51ff7ee866e92dda1dd4102d5df09\",\n  \"conventions\": {\n    \"ambiguities\": [],\n    \"calling_convention\": \"__thiscall\",\n    \"candidate_conventions\": [\n      \"__thiscall\",\n      \"__fastcall\"\n    ],\n    \"confidence\": \"INFERRED\",\n    \"corroboration\": \"not_available\"\n  },\n  \"cross_validation\": {\n    \"agreement\": false,\n    \"ghidra\": \"no_information\",\n    \"ghidra_calling_convention\": null,\n    \"ghidra_parameter_count\": 0,\n    \"persisted\": \"no_information\",\n    \"persisted_calling_convention\": null\n  },\n  \"dispatch\": {\n    \"call_offsets\": [],\n    \"indirect_calls\": 0,\n    \"vtable_shaped_loads\": 0\n  },\n  \"inferences\": [\n    {\n      \"based_on\": [\n        \"obs-0004\"\n    
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
      "va": "0x00ae9930"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4ef00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4ef90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c52160"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c521c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c552d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c55330"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c5a580"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c5ac60"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c5eed0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c5efb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c5ff50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c62ed0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c62f60"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e07e70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e17570"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00ae9b00",
      "direction": "in",
      "other": "0x00ae9930",
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
      "va": "0x00ae9930"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4ef00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4ef90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c52160"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c521c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c552d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c55330"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c5a580"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c5ac60"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c5eed0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c5efb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c5ff50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c62ed0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c62f60"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e07e70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e17570"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e1d020"
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
    "No class, vtable slot or SDK name is claimed: the body contains no indirect transfer and the binary has no MSVC RTTI.",
    "Running `python3 -m tools.reconstruction_tooling context <va>` re-collects the evidence pack non-live and drops the disassembly category; `recover --live` restores it. The pack for this target was restored that way.",
    "The 43 callers are listed in the pack but none was reconstructed here, so what the predicate means to its consumers is uncharacterised.",
    "The identity of the word at 0x84 is not recoverable from this body: the derived receiver record is bounds_only, so no member name is claimed. Resolving it needs a writer of that word, which this package did not reconstruct.",
    "The return value is read as AL in the model test because a one-byte declared return only promises AL; the machine additionally clears all of EAX, but that extra guarantee is a property of this body and not of the declared type.",
    "Whether 0x3 is a member of a meaningful enumeration is not established; the CMP immediate is the whole of the evidence, so it is spelled as a constant."
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
