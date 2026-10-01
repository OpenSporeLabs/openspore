# Reconstruction context 0x00b3d260

- Status: `partial`
- Content SHA-256: `b05360e5a5b4ed9d20d3a1b4aad103ae53aa2a6df04781826f6592b4841d8e21`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00b3d260",
  "phase": "reconstruction",
  "target": "0x00b3d260"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00b3d260",
  "package": null,
  "subsystem": "Simulator",
  "va": "0x00b3d260"
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
  "content_sha256": "b0085aa93c947e6d94ccacb32ab175cf20214672339c36ed82a5e06e14ecd4da",
  "live_attempts": [],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `present`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json

undefined4 FUN_00b3d260(void)

{
  return DAT_0167ead8;
}


```

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "original_bytes": 5056,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"receiver\": false,\n    \"ret_form\": \"RET\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"pointer_like_in_EAX\",\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"RET\"\n  },\n  \"abstained_because\": [\n    \"no_discriminator: no stack-argument read and no positive receiver evidence\"\n  ],\n  \"cleanup\": {\n    \"bytes\": 0,\n    \"confidence\": \"INFERRED\",\n    \"corroboration\": \"not_available\",\n    \"evidence\": \"ret with no immediate, no stack reads\",\n    \"side\": \"caller\"\n  },\n  \"completeness\": \"PARTIAL\",\n  \"conflicts\": [],\n  \"content_sha256\": \"ecc268d64d9c755da6997d180dcafe0e909d48ddf04aea89912b92f0e81fdd82\",\n  \"conventions\": {\n    \"ambiguities\": [],\n    \"calling_convention\": null,\n    \"candidate_conventions\": [\n      \"__cdecl\",\n      \"__stdcall\",\n      \"__thiscall\",\n      \"__fastcall\"\n    ],\n    \"confidence\": \"UNKNOWN\",\n    \"corroboration\": \"not_available\"\n  },\n  \"cross_validation\": {\n    \"agreement\": false,\n    \"ghidra\": \"no_information\",\n    \"ghidra_calling_convention\": null,\n    \"ghidra_parameter_count\": 0,\n    \"persisted\": \"no_information\",\n    \"persisted_calling_convention\": null\n  },\n  \"dispatch\": {\n    \"call_offsets\": [],\n    \"indirect_calls\": 0,\n    \"vtable_shaped_loads\": 0\n  },\n  \"inferences\": [\n    {\n      \"based_on\": [\n        \"obs-0002\"\n      ],\n      \"claim\": \"the caller 
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
      "va": "0x00abf710"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00abf760"
    },
    {
      "name": "opaque_service_forward_00abf790",
      "reconstructed": true,
      "va": "0x00abf790"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ac8a80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00accf80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ad8b10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00adf840"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b0eae0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b32aa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b32c60"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bd2310"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf3c50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf45f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf57b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf7d80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c02ba0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00abf71a",
      "direction": "in",
      "other": "0x00abf710",
      "reference_
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
      "va": "0x00abf710"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00abf760"
    },
    {
      "name": "opaque_service_forward_00abf790",
      "reconstructed": true,
      "va": "0x00abf790"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ac8a80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00accf80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ad8b10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00adf840"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b0eae0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b32aa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b32c60"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bd2310"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf3c50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf45f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf57b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf7d80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c02ba0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c099e0"
    },
    {
      
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
    "Do any of the 16 other slots in the table (0x0167eac0,0x0167eac4,0x0167eac8,0x0167eacc,0x0167ead0,0x0167ead4,0x0167eadc,0x0167eae8,0x0167eaf0,0x0167eaf4,0x0167eafc and the three closed ones) alias each other at a lifecycle point? Nothing here says they do or do not.",
    "Is 0x00b3d260 the accessor a canonical SDK-named getter would sit on? The 17-slot table at 0x0167eac0..0x0167eafc has one accessor per slot and the SDK import pass named none of them; no SDK identity is claimed.",
    "Is the returned word ever null at a real callsite, and what do callers do then? None of the eight caller listings read here null-tests the result, so no null contract is claimed in either direction.",
    "The remaining 29 of the 37 distinct callers (58 callsites total) were not classified by hand. Only 0x00abf710/0x00abf760/0x00abf790/0x00b32ac4/0x00b32c60/0x00bf45f0/0x00bf57b0/0x00bf7d80 were read; fan-in was deliberately not used as semantic evidence.",
    "What object does 0x0167ead8 point to? Consumers treat it as an object base with a function table at [result+0] and dispatch through slots +0x24, +0x30 and +0x38, but no class, vtable identity, field name, slot owner or object size is established by this body or by any caller read here.",
    "Who publishes 0x0167ead8, when, and how is it torn down and reset? The project's own promoted metadata for 0x00abf790 already carries this as an open question and this package keeps it open; no first-writer scan was attempted."
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
