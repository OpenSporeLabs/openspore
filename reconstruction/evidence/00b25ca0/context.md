# Reconstruction context 0x00b25ca0

- Status: `partial`
- Content SHA-256: `abb1b7ca99478935430f7cc010c7899ba9b512378c6abb8d618201cab80b7582`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00b25ca0",
  "phase": "reconstruction",
  "target": "0x00b25ca0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00b25ca0",
  "package": null,
  "subsystem": "Simulator",
  "va": "0x00b25ca0"
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
  "content_sha256": "964f5c5ead5df3461c054f08cf974f09c32222cb16569bb6cdf2553ce049d4f1",
  "live_attempts": [],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `present`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json

int FUN_00b25ca0(void)

{
  int iVar1;
  
  iVar1 = FUN_00b21340(PTRREF_00B21080,PTRREF_00D3D420,PTRREF_00B236C0,PTRREF_00B1E500,&DAT_018c816a
                      );
  return iVar1 + 4;
}


```

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "original_bytes": 5321,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"receiver\": false,\n    \"ret_form\": \"RET\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"unclassified_in_EAX\",\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"RET\"\n  },\n  \"abstained_because\": [\n    \"flow_not_modelled: the linear ESP walk ends at +20, so the listing is not one path\",\n    \"no_discriminator: no stack-argument read and no positive receiver evidence\"\n  ],\n  \"cleanup\": {\n    \"bytes\": 0,\n    \"confidence\": \"INFERRED\",\n    \"corroboration\": \"not_available\",\n    \"evidence\": \"ret with no immediate, no stack reads\",\n    \"side\": \"caller\"\n  },\n  \"completeness\": \"PARTIAL\",\n  \"conflicts\": [],\n  \"content_sha256\": \"5d604b58fa6b4783c4d3ca48a4dbf2c4c87bc54dde5ddf6394b7e5eda4fcc2e4\",\n  \"conventions\": {\n    \"ambiguities\": [],\n    \"calling_convention\": null,\n    \"candidate_conventions\": [\n      \"__cdecl\",\n      \"__stdcall\",\n      \"__thiscall\",\n      \"__fastcall\"\n    ],\n    \"confidence\": \"UNKNOWN\",\n    \"corroboration\": \"not_available\"\n  },\n  \"cross_validation\": {\n    \"agreement\": false,\n    \"ghidra\": \"no_information\",\n    \"ghidra_calling_convention\": null,\n    \"ghidra_parameter_count\": 0,\n    \"persisted\": \"no_information\",\n    \"persisted_calling_convention\": null\n  },\n  \"dispatch\": {\n    \"call_offsets\": [],\n    \"indirect_calls\": 0,\n    \"vtable_shaped_loads\": 0\n  },\n  \"inferences\": [\
[TRUNCATED]
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "pkg11_sim_core_00b21340",
      "reconstructed": true,
      "va": "0x00b21340"
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae6240"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bd7160"
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
      "va": "0x00be4c00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be88d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf0b00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf0b70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf0be0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf1070"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf1170"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf1270"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf14b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf1e20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf3180"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf59d0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x
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
  "callees": [
    {
      "name": "pkg11_sim_core_00b21340",
      "reconstructed": true,
      "va": "0x00b21340"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae6240"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bd7160"
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
      "va": "0x00be4c00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be88d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf0b00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf0b70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf0be0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf1070"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf1170"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf1270"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf14b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf1e20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf3180"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf59d0"
    },
    {
      "name"
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
    "Ownership of the returned range is unclaimed beyond 'borrowed': the body adds a bias and hands the pointer on, with no AddRef, no store and no release, and the callee's own ownership contract for its returned vector remains that package's open question.",
    "The SDK name of 0x00b25ca0 is unknown. It sits in the same address neighbourhood as 0x00b25f40 (a kCivilization scan over the same callee) and 0x00b25fb0, and 0xbf9820's committed metadata describes it as a 'city ownership enumeration wrapper' - but that is a CALLER's reading, not a witness, and it is deliberately not adopted. No naming claim is made beyond the witnessed facts that the callee is the noun projection and the return is that projection's element range.",
    "The value and role of the key operand 0x018c816a are open. It reads as eight zero bytes on this snapshot; whether it is a live global, a zero-initialised slot or a BSS cell is not established.",
    "Which function in the unpromoted callee link 0x00b21340 should satisfy this package's callee declaration is an integration decision, not a semantic one: the model test substitutes a recording stub with the callee's own ABI, and promotion must bind it to the promoted pkg11_sim_core noun projection.",
    "Which of the five immediates is the create callback, the clear callback, the add callback and the filter callback is not established by this body's eight instructions; those are the callee's parameter roles and belong to the callee package's evidence. They are carried as opaque 32-bit constants with t
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
