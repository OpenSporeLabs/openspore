# Reconstruction context 0x00b3d470

- Status: `partial`
- Content SHA-256: `ae8d68ded151425541afa1b32c81584800f9d58984f9d3e860d83af0bfb3c1fa`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00b3d470",
  "phase": "reconstruction",
  "target": "0x00b3d470"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00b3d470",
  "package": null,
  "subsystem": "Simulator",
  "va": "0x00b3d470"
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
  "content_sha256": "2b22aa9bc8004659cc7dfb9aef7a81b1ef62af980c43b8bd3d4d3ed8fe6caf24",
  "live_attempts": [],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `present`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json

undefined4 FUN_00b3d470(void)

{
  return DAT_0167eb18;
}


```

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "original_bytes": 5056,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"receiver\": false,\n    \"ret_form\": \"RET\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"pointer_like_in_EAX\",\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"RET\"\n  },\n  \"abstained_because\": [\n    \"no_discriminator: no stack-argument read and no positive receiver evidence\"\n  ],\n  \"cleanup\": {\n    \"bytes\": 0,\n    \"confidence\": \"INFERRED\",\n    \"corroboration\": \"not_available\",\n    \"evidence\": \"ret with no immediate, no stack reads\",\n    \"side\": \"caller\"\n  },\n  \"completeness\": \"PARTIAL\",\n  \"conflicts\": [],\n  \"content_sha256\": \"8294705252c6df7dea496b13af57b39e5897dc91d0a85d1cf30b78f5784686de\",\n  \"conventions\": {\n    \"ambiguities\": [],\n    \"calling_convention\": null,\n    \"candidate_conventions\": [\n      \"__cdecl\",\n      \"__stdcall\",\n      \"__thiscall\",\n      \"__fastcall\"\n    ],\n    \"confidence\": \"UNKNOWN\",\n    \"corroboration\": \"not_available\"\n  },\n  \"cross_validation\": {\n    \"agreement\": false,\n    \"ghidra\": \"no_information\",\n    \"ghidra_calling_convention\": null,\n    \"ghidra_parameter_count\": 0,\n    \"persisted\": \"no_information\",\n    \"persisted_calling_convention\": null\n  },\n  \"dispatch\": {\n    \"call_offsets\": [],\n    \"indirect_calls\": 0,\n    \"vtable_shaped_loads\": 0\n  },\n  \"inferences\": [\n    {\n      \"based_on\": [\n        \"obs-0002\"\n      ],\n      \"claim\": \"the caller 
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
      "va": "0x00b335d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b35300"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b35860"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b5e3f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bbcf00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c84620"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d3a830"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d3a960"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e978e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e97bf0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e98500"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fd9d90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fda390"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fdcee0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fdd4f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fdd5a0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00b33784",
      "direction": "in",
      "other": "0x00b335d0",
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
      "va": "0x00b335d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b35300"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b35860"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b5e3f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bbcf00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c84620"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d3a830"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d3a960"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e978e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e97bf0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e98500"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fd9d90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fda390"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fdcee0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fdd4f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fdd5a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fdf5f0"
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
    "no runtime validation exists: there is no Wine run, differential trace or runtime-gate result for 0x00b3d470, so nothing here is OBSERVED or VERIFIED",
    "what 0x0167eb18 denotes: the body returns it but never interprets it, so its type and semantic identity are unclaimed (STILL_UNKNOWN)",
    "whether 0x0167eb18 aliases any other Simulator root slot: not tested, and importing a sibling's identity would be a claim this listing does not carry",
    "whether the +0x60 dereference at caller 0x00d3a830 means the word is a pointer: consistent, not proven, and one caller is not enough to close a return type",
    "which calling convention applies: unrecoverable from a zero-parameter bare-RET body; the PKG_00B3D470_CALL macro is present and deliberately carries no convention token",
    "who publishes 0x0167eb18 and when: the datarefs export records only this body as a reader, so the writer must be a computed or otherwise unreferenced store, and the first-writer search was not performed here"
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
