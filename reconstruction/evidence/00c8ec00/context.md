# Reconstruction context 0x00c8ec00

- Status: `partial`
- Content SHA-256: `f3e005988aa45beab44dcc28987db6c93029491954eb09c2bf118b8ccccd0cfe`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00c8ec00",
  "phase": "reconstruction",
  "target": "0x00c8ec00"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueTribeState",
  "name": "TribeState_test_purchased_tool_bit_00c8ec00",
  "package": "PKG-13-SIM-CREATURE-TRIBECIV",
  "subsystem": "Simulator.Tribe",
  "va": "0x00c8ec00"
}
```

## 03_current_status

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "blocked": false,
  "reconstructed": true,
  "runtime_gated": true,
  "runtime_validated": 0,
  "status": "reconstructed"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "109ea4499c450defc575ecaee3f332b7bd56471abaa6a7dbdd1b8dcb50f05d0f",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00c8ec00 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "thiscall",
  "hidden_this": "ECX receiver",
  "return_register": "EAX",
  "return_semantics": "Returns exactly 0 or 1. The imported cTribeArchetype* signature is not treated as a real object-pointer return because the direct caller immediately executes TEST AL,AL and the body contains no address load.",
  "return_width_bytes": 4,
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "observed_use": "Copied to ECX and used as the x86 shift count; x86 masks the count to five bits",
      "position": 1,
      "type": "std::uint32_t",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 4
}
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
      "va": "0x00d10f90"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00d115e5",
      "direction": "in",
      "other": "0x00d10f90",
      "reference_type": "direct-call"
    }
  ],
  "external_callees": []
}
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "OpaqueTribeState",
    "std::uint32_t"
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
      "tribe_purchased_tools_mask_observation"
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
  "callees": [],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d10f90"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00d115e5",
      "direction": "in",
      "other": "0x00d10f90",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 1,
  "fan_out": 0,
  "manifest_callees": [],
  "manifest_callers": [
    "0x00d10f90"
  ],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0481",
    "size": 1
  },
  "vtable_reference_count": 0
}
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "PKG-13-C3-TRIBE-CIV-WAVE2",
    "score": 8,
    "symbol": "tribe_constructor_00c982a0",
    "va": "0x00c982a0"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "PKG-13-SIM-CREATURE-TRIBECIV",
    "score": 8,
    "symbol": "Simulator_cCreatureGameData_GetEvolutionPoints",
    "va": "0x00d2e350"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "PKG-13-SIM-CREATURE-TRIBECIV",
    "score": 8,
    "symbol": "Simulator_cCreatureGameData_GetEvoPointsToNextBrainLevel",
    "va": "0x00d2e380"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "PKG-13-SIM-CREATURE-TRIBECIV",
    "score": 8,
    "symbol": "Simulator_cCreatureGameData_GetAbilityMode",
    "va": "0x00d2e490"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-EDITOR-RUNTIME-WAVE7",
    "score": 2,
    "symbol": "EditorCreatureController_SetTargetPosition_0059b0f0",
    "va": "0x0059b0f0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-EDITOR-RUNTIME-WAVE7",
    "score": 2,
    "symbol": "EditorCreatureController_Update_0059b4b0",
    "va": "0x0059b4b0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-EDITOR-RUNTIME-WAVE7",
    "score": 2,
    "symbol": "EditorAnimWorld_GetCreatureController_0059cac0",
    "va": "0x0059cac0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-EDITOR-RUNTIME-WAVE7
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg13_creature_state/creature_state.cpp",
  "files": [
    "reconstruction/staging/pkg13-b0-creature-state/creature_state.cpp",
    "reconstruction/staging/pkg13-b0-creature-state/creature_state.hpp",
    "reconstruction/staging/pkg13-b0-creature-state/creature_state_test.cpp",
    "src/reconstruction/pkg13_creature_state/creature_state.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg13-b0-creature-state/00c8ec00.json"
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
        "0x00a20670",
        "0x00571f80",
        "0x00572070",
        "0x00572020",
        "0x0067dd90",
        "0x00e66280",
        "0x00e66840",
        "0x00e63560",
        "0x00c8ec00"
      ],
      "conflict_id": "unresolved:knowledgegraph/research/state-machines/additional-domains.json:5",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
      "resolution_status": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
      "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
      "subject": null,
      "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
    }
  ],
  "unresolved_questions": [
    "No original-process mask value or caller outcome has been observed.",
    "The exact concrete state owner at ECX is not fully reconstructed, although the persisted layout and caller flow identify a tribe-state-shaped receiver.",
    "The semantic producer and complete meaning of all 32 purchased-tool bits remain unresolved.",
    "concrete state owner",
    "mask producer",
    "runtime mask value",
    "tool-index producer semantics",
    "tribe_purchased_tools_mask_observation"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg13-b0-creature-state/00c8ec00.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg13-b0-creature-state/creature_state.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg13-b0-creature-state/creature_state.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg13-b0-creature-state/creature_state_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg13_creature_state/creature_state.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/integrated/batch-2026-09-25/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg13-b0-creature-state/00c8ec00.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg13-b0-creature-state/creature_state.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg13-b0-creature-state/creature_state.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg
[TRUNCATED]
```
