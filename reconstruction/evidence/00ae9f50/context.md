# Reconstruction context 0x00ae9f50

- Status: `partial`
- Content SHA-256: `92a901996f3c68a4427b4a2d01695f2308a1f717ed9d0ca261f233aa311a1904`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00ae9f50",
  "phase": "reconstruction",
  "target": "0x00ae9f50"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": null,
  "package": null,
  "subsystem": null,
  "va": "0x00ae9f50"
}
```

## 03_current_status

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "blocked": false,
  "reconstructed": false,
  "runtime_gated": true,
  "runtime_validated": 0,
  "status": "unresolved"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "0006c655c9e638c8df883f8902001ab4d5ca0f4fa05972cfae7073c91f296299",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00ae9f50 failed: Decompilation did not complete. Reason: ",
      "mode": "LIVE",
      "status": "unavailable"
    }
  ],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `missing`
- Provenance: ``

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_receiver": "ECX, copied to ESI at 0x00ae9f57",
  "hidden_this_register": "ECX is consumed immediately; ESI carries the receiver for the rest of the body, which is what lets ECX be reused as the receiver for the many __thiscall ports.",
  "ordinary_stack_argument_slots": 0,
  "receiver": true,
  "ret_form": "RET",
  "return_register": null,
  "return_semantics": "No return value. EAX is a scratch register throughout.",
  "return_type": "void",
  "return_width_bytes": 0,
  "saved_registers": [
    "ESI",
    "EBX",
    "EBP",
    "EDI"
  ],
  "stack_arguments": [],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "two exits, both the same bare RET: 0x00aea166 reached by falling off the end, and 0x00aea15f reached by the null-sub-object jump and by the +0x64 / +0x68 skips."
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0067dcc0"
    },
    {
      "name": "FUN_00b3d2a0",
      "reconstructed": true,
      "va": "0x00b3d2a0"
    },
    {
      "name": "FUN_00b3d300",
      "reconstructed": true,
      "va": "0x00b3d300"
    },
    {
      "name": "FUN_00b3d380",
      "reconstructed": false,
      "va": "0x00b3d380"
    },
    {
      "name": "FUN_00b3d400",
      "reconstructed": true,
      "va": "0x00b3d400"
    },
    {
      "name": "Simulator_cSpaceTrading_Get",
      "reconstructed": true,
      "va": "0x00b3d4d0"
    },
    {
      "name": "Simulator_LookupEmpireByPoliticalId",
      "reconstructed": true,
      "va": "0x00ba9370"
    },
    {
      "name": "FUN_01021090",
      "reconstructed": false,
      "va": "0x01021090"
    },
    {
      "name": "pkg12_space_01021300",
      "reconstructed": true,
      "va": "0x01021300"
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aea210"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aeb090"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aeb7b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aeb890"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00aea210",
      "direction": "in",
      "other": "0x00aea210",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00aeb099",
      "direction": "in",
      "other": "0x00aeb090",
      "reference_type": "direct-call"
    },
    {
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "void"
  ],
  "vtables": []
}
```

## 09_state_event_relationships

- State: `present`
- Provenance: `knowledgegraph/research/semantic-decomp.json, reconstruction/knowledge/index.json`

```json
{
  "runtime": {
    "blocking_reason": null,
    "gates": [
      "No original-process trace exists. A differential run must confirm the two AppSystem submissions, the two publishes and the three memory writes actually occur in the observed order in the shipping build.",
      "The claim that 0x00421CF0 destroys the stack records must be observed: a run that keeps the record alive after return would refute it.",
      "The sentinel-free runtime values behind the six-entry table at 0x015D9650 used by the sibling 0x00C0CE80 are irrelevant here, but the two record ids 0x3AC86B5 and 0x43F2590 can only be resolved by observing what the AppSystem slot +0x14 does with them.",
      "Whether receiver+0x74 can be non-(-1) at entry, and what 0x00BA6D80 returns for it, can only be established at runtime."
    ],
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
      "name": null,
      "reconstructed": false,
      "va": "0x0067dcc0"
    },
    {
      "name": "FUN_00b3d2a0",
      "reconstructed": true,
      "va": "0x00b3d2a0"
    },
    {
      "name": "FUN_00b3d300",
      "reconstructed": true,
      "va": "0x00b3d300"
    },
    {
      "name": "FUN_00b3d380",
      "reconstructed": false,
      "va": "0x00b3d380"
    },
    {
      "name": "FUN_00b3d400",
      "reconstructed": true,
      "va": "0x00b3d400"
    },
    {
      "name": "Simulator_cSpaceTrading_Get",
      "reconstructed": true,
      "va": "0x00b3d4d0"
    },
    {
      "name": "Simulator_LookupEmpireByPoliticalId",
      "reconstructed": true,
      "va": "0x00ba9370"
    },
    {
      "name": "FUN_01021090",
      "reconstructed": false,
      "va": "0x01021090"
    },
    {
      "name": "pkg12_space_01021300",
      "reconstructed": true,
      "va": "0x01021300"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aea210"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aeb090"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aeb7b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aeb890"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00aea210",
      "direction": "in",
      "other": "0x00aea210",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00aeb099",
      "direction": 
[TRUNCATED]
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 3,
    "symbol": "FUN_00b3d2a0",
    "va": "0x00b3d2a0"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 3,
    "symbol": "FUN_00b3d300",
    "va": "0x00b3d300"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 3,
    "symbol": "FUN_00b3d400",
    "va": "0x00b3d400"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 3,
    "symbol": "Simulator_cSpaceTrading_Get",
    "va": "0x00b3d4d0"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-11-SIM-CORE",
    "score": 3,
    "symbol": "Simulator_LookupEmpireByPoliticalId",
    "va": "0x00ba9370"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-12-SIM-SPACE",
    "score": 3,
    "symbol": "pkg12_space_01021300",
    "va": "0x01021300"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-APP-SAFE-WAVE11",
    "score": 2,
    "symbol": "property_record_assign_pair_004279d0",
    "va": "0x004279d0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-APP-SAFE-WAVE11",
    "score": 2,
    "symbol": "property_record_assign_scalar_00428060",
    "va": "0x00428060"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/wave13-w1-core-b08/ae9f50_session_boot_register.cpp",
    "reconstruction/staging/wave13-w1-core-b08/b8dad0_spice_gen_key_ptr.cpp",
    "reconstruction/staging/wave13-w1-core-b08/ba61b0_make_planet_record.cpp",
    "reconstruction/staging/wave13-w1-core-b08/c0b780_sub_object_flag_608.cpp",
    "reconstruction/staging/wave13-w1-core-b08/c0ce80_tier_value_lookup.cpp",
    "reconstruction/staging/wave13-w1-core-b08/c47180_manager_slot_replace.cpp",
    "reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08.hpp",
    "reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_model_test.cpp",
    "reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_model_test2.cpp",
    "reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_reconstructed.hpp",
    "reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_test_stubs.cpp",
    "reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_test_stubs.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-core-b08/00ae9f50.json"
  ]
}
```

## 13_semantic_hypotheses

- State: `missing`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

## 14_conflicts_questions

- State: `conflicted`
- Provenance: `reconstruction/knowledge/index.json, knowledgegraph/research/semantic-decomp.json`

```json
{
  "conflicts": [
    {
      "anchors": [
        "0x00b3d2a0",
        "0x00b3d300",
        "0x00b5b800",
        "0x01021300",
        "0x01021300",
        "0x00ad23c0",
        "0x00adbca0",
        "0x00ae73e0",
        "0x00ae9590",
        "0x00ae9930",
        "0x00ae9c90",
        "0x00ae9f50",
        "0x00aeb3e0",
        "0x00aeb3e0",
        "0x00aebe90",
        "0x00b25fb0"
      ],
      "conflict_id": "global_root_identities",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
      "resolution_status": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
      "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
      "subject": null,
      "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
    },
    {
      "anchors": [
        "0x0067dcc0",
        "0x0067deb0",
        "0x00b3d330",
        "0x00b3d4e0",
        "0x015fd890",
        "0x0167eaf0",
        "0x0167eb60",
        "0x0067dcc0",
        "0x00ad23c0",
        "0x00adbca0",
        "0x00ae73e0",
        "0x00ae9590",
        "0x00ae9930",
        "0x00ae9c90",
        "0x00ae9f50",
        "0x00aeb3e0"
      ],
      "conflict_id": "global_service_publication",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The committed evidence does not es
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-w1-core-b08/00ae9f50.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b08/ae9f50_session_boot_register.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b08/b8dad0_spice_gen_key_ptr.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b08/ba61b0_make_planet_record.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b08/c0b780_sub_object_flag_608.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b08/c0ce80_tier_value_lookup.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b08/c47180_manager_slot_replace.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_model_test2.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_reconstructed.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_test_stubs.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_test_stubs.hpp', 'source_class': 'committed_artifact'}`

```json
{
  "provenance": [
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
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/wave13-w1-core-b08/00ae9f50.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b08/ae9f50_session_boot_register.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b08/b8dad0_spice_gen_key_ptr.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b08/ba61b0_make_planet_record.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "r
[TRUNCATED]
```
