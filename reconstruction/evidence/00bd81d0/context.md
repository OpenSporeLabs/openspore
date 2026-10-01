# Reconstruction context 0x00bd81d0

- Status: `partial`
- Content SHA-256: `392376e2f3412415892fd5f4915b2723155efdd9a963809038956d38e4b56eec`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00bd81d0",
  "phase": "reconstruction",
  "target": "0x00bd81d0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00bd81d0",
  "package": null,
  "subsystem": "Simulator",
  "va": "0x00bd81d0"
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
  "content_sha256": "972825a9c6602f55949b80e2912850177708f7d35ef3aef1b063c8b400723055",
  "live_attempts": [],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `present`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json

undefined4 __fastcall FUN_00bd81d0(int param_1)

{
  return *(undefined4 *)(param_1 + 0x540);
}


```

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "original_bytes": 5577,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"receiver\": true,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"pointer_like_in_EAX\",\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"RET\"\n  },\n  \"abstained_because\": [],\n  \"cleanup\": {\n    \"bytes\": 0,\n    \"confidence\": \"INFERRED\",\n    \"corroboration\": \"not_available\",\n    \"evidence\": \"ret with no immediate, no stack reads\",\n    \"side\": \"caller\"\n  },\n  \"completeness\": \"CORE_RESOLVED\",\n  \"conflicts\": [],\n  \"content_sha256\": \"11274f2fd25902709b748a264f90ea7b912c8738fe1c2ec95ece113ceeef99fb\",\n  \"conventions\": {\n    \"ambiguities\": [],\n    \"calling_convention\": \"__thiscall\",\n    \"candidate_conventions\": [\n      \"__thiscall\",\n      \"__fastcall\"\n    ],\n    \"confidence\": \"INFERRED\",\n    \"corroboration\": \"not_available\"\n  },\n  \"cross_validation\": {\n    \"agreement\": false,\n    \"ghidra\": \"no_information\",\n    \"ghidra_calling_convention\": null,\n    \"ghidra_parameter_count\": 0,\n    \"persisted\": \"no_information\",\n    \"persisted_calling_convention\": null\n  },\n  \"dispatch\": {\n    \"call_offsets\": [],\n    \"indirect_calls\": 0,\n    \"vtable_shaped_loads\": 0\n  },\n  \"inferences\": [\n    {\n      \"based_on\": [\n        \"obs-0003\"\n    
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
      "va": "0x00bd0000"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bd7160"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00beeb70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00beff90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf00a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf01f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf0f40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf1e20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf1fd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf23d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf4370"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf4fc0"
    },
    {
      "name": "culture_selection_00bf9820",
      "reconstructed": true,
      "va": "0x00bf9820"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf9e70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bfa660"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bfb020"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00bd0067",
      "direction": "in",
      "other": "0x00bd0000",
      "reference_type"
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
      "va": "0x00bd0000"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bd7160"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00beeb70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00beff90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf00a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf01f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf0f40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf1e20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf1fd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf23d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf4370"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf4fc0"
    },
    {
      "name": "culture_selection_00bf9820",
      "reconstructed": true,
      "va": "0x00bf9820"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf9e70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bfa660"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bfb020"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bfbbf0"
    },
    {
      "name
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
    "Do any of the 24 unsampled caller functions dereference the returned word? If one does, a pointer reading also fits and contradiction C-RETTYPE would reopen.",
    "Is there a setter counterpart to this getter elsewhere in the image, as 0x00bd81e0 pairs with 0x00bd81f0 for +0x2f0? Not searched; this package is bounded to the target and its immediate block.",
    "The derived ABI record's convention resolution (__thiscall over __fastcall) is not observable from this function alone: for a body reading ECX with zero stack arguments the two encodings are identical.",
    "What are the enumerators of the 0/1/2/-1 domain? The observed comparands establish an enum-like shape and nothing more; the -1 at 0x00bd7160 hints at a signed domain but no name, count or ordering is evidenced.",
    "What class owns offset 0x540, and what is the field called? No SDK import, namespace or committed research note names either; Ghidra's SDK import left the entry FUN_00bd81d0.",
    "Who writes +0x540, and when relative to the 31 distinct caller functions that read it? No writer was located for this offset (sibling writers in the block cover +0x33c and +0x2f0 only); this is an unlocated writer, not an established absence."
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
