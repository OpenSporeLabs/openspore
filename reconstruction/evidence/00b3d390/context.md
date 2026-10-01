# Reconstruction context 0x00b3d390

- Status: `partial`
- Content SHA-256: `25572b7ddc9bfe3c2f33b97288442f8a4043088fd97c1d7a7e170d81cd030ada`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00b3d390",
  "phase": "reconstruction",
  "target": "0x00b3d390"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00b3d390",
  "package": null,
  "subsystem": "Simulator",
  "va": "0x00b3d390"
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
  "content_sha256": "284ebe1c1e349d559b2fd5d67e79ee9a3008b74858f0389ce198e522dae430a5",
  "live_attempts": [],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `present`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json

undefined4 FUN_00b3d390(void)

{
  return DAT_0167eb08;
}


```

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "original_bytes": 5056,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"receiver\": false,\n    \"ret_form\": \"RET\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"pointer_like_in_EAX\",\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"RET\"\n  },\n  \"abstained_because\": [\n    \"no_discriminator: no stack-argument read and no positive receiver evidence\"\n  ],\n  \"cleanup\": {\n    \"bytes\": 0,\n    \"confidence\": \"INFERRED\",\n    \"corroboration\": \"not_available\",\n    \"evidence\": \"ret with no immediate, no stack reads\",\n    \"side\": \"caller\"\n  },\n  \"completeness\": \"PARTIAL\",\n  \"conflicts\": [],\n  \"content_sha256\": \"1994e434d9213ce389cf7a2a4d8c6effe93abba6d316e0ab3ba2c9ad805510a2\",\n  \"conventions\": {\n    \"ambiguities\": [],\n    \"calling_convention\": null,\n    \"candidate_conventions\": [\n      \"__cdecl\",\n      \"__stdcall\",\n      \"__thiscall\",\n      \"__fastcall\"\n    ],\n    \"confidence\": \"UNKNOWN\",\n    \"corroboration\": \"not_available\"\n  },\n  \"cross_validation\": {\n    \"agreement\": false,\n    \"ghidra\": \"no_information\",\n    \"ghidra_calling_convention\": null,\n    \"ghidra_parameter_count\": 0,\n    \"persisted\": \"no_information\",\n    \"persisted_calling_convention\": null\n  },\n  \"dispatch\": {\n    \"call_offsets\": [],\n    \"indirect_calls\": 0,\n    \"vtable_shaped_loads\": 0\n  },\n  \"inferences\": [\n    {\n      \"based_on\": [\n        \"obs-0002\"\n      ],\n      \"claim\": \"the caller 
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
      "va": "0x00ae73e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b5fde0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bc1450"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bce1e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bd0000"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bd0140"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bdc1a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be41b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be4400"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf6ee0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c3a220"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c3a2b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c3a5a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c3a930"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c3b5c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c3c520"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00ae748a",
      "direction": "in",
      "other": "0x00ae73e0",
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
      "va": "0x00ae73e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b5fde0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bc1450"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bce1e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bd0000"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bd0140"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bdc1a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be41b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be4400"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf6ee0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c3a220"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c3a2b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c3a5a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c3a930"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c3b5c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c3c520"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c3dba0"
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
    "Does the returned pointer need an AddRef, and if so by whom? The body has no room for a reference call and no writer is known, so ownership is undetermined.",
    "Is 0x0167eb08 related to the SDK-named neighbours 0x0167eb0c (cStarManager::Get) and 0x0167eb60 (cGameNounManager::Get), and to the alternate slots 0x0167eae0 and 0x0167eae4 Phase 0 already closed? Adjacency in one table is not evidence of aliasing, and nothing here claims or denies it. The root closure's open alternate-vs-canonical question does not currently list this slot.",
    "Is the returned pointer ever null at a real callsite, and what do callers do then? None of the sampled sites null-tests the result, so no null contract is claimed in either direction - only that a stored zero is returned as a stored zero, which is what the body does.",
    "Of the 63 distinct callers, only 0x00b5fde0 and 0x00bdc1a0's neighbourhoods were read by disassembly; the remaining 61 were counted from the edge sidecar and not classified by hand, because fan-in is not semantic evidence.",
    "Promotion is blocked by a validator limitation rather than a package defect (FIELDS/OFFSETS cannot score a global-slot load). An integrator must either promote by review or add a global-slot arm to that check; tools/** was not modified.",
    "What class does the word at 0x0167eb08 point to? The SDK import leaves this slot, and 0x0167eb00 and 0x0167eb04, unnamed, and no committed research note names it. This is the single biggest gap and the reason the pointee type is opaque with no mod
[TRUNCATED]
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
