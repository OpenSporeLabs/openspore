# Reconstruction context 0x00be2440

- Status: `complete`
- Content SHA-256: `395bbbf0eea8089e2881ad0c179597c32d814882ce630b1d05b4c6278a15012f`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00be2440",
  "phase": "reconstruction",
  "target": "0x00be2440"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "city_building_economy_update_00be2440",
  "package": "PKG-13-C4-CIV-WAVE3",
  "subsystem": null,
  "va": "0x00be2440"
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
  "content_sha256": "0d3da0537dab6eae62e4856b48870ab54e410226a76bd9473d78016d30d3214f",
  "live_attempts": [],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `present`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json

void FUN_00be2440(int *param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  bool bVar4;
  char cVar5;
  int iVar6;
  int iVar7;
  int *piVar8;
  undefined1 *puVar9;
  uint uVar10;
  uint uVar11;
  uint uStack_210;
  int iStack_20c;
  int iStack_208;
  char local_204 [16];
  undefined4 uStack_1f4;
  undefined4 uStack_1f0;
  int local_1ec [14];
  float fStack_1b4;
  int local_1a4 [56];
  undefined1 local_c4 [196];
  
  local_1a4[0xe] = 0;
  local_1a4[0xf] = 0;
  local_1a4[0x10] = 0;
  local_1a4[0x11] = 0;
  local_1a4[0x12] = 0;
  local_1a4[0x13] = 0;
  local_1a4[0x14] = 0;
  local_1a4[0x15] = 0;
  local_1a4[0x16] = 0;
  local_1a4[0x17] = 0;
  local_1a4[0x18] = 0;
  local_1a4[0x19] = 0;
  local_1a4[0x1a] = 0;
  local_1a4[0x1b] = 0;
  local_1a4[0] = 0;
  local_1a4[1] = 0;
  local_1a4[2] = 0;
  local_1a4[3] = 0;
  local_1a4[4] = 0;
  local_1a4[5] = 0;
  local_1a4[6] = 0;
  local_1a4[7] = 0;
  local_1a4[8] = 0;
  local_1a4[9] = 0;
  local_1a4[10] = 0;
  local_1a4[0xb] = 0;
  local_1a4[0xc] = 0;
  local_1a4[0xd] = 0;
  local_1a4[0x1c] = 0;
  local_1a4[0x1d] = 0;
  local_1a4[0x1e] = 0;
  local_1a4[0x1f] = 0;
  local_1a4[0x20] = 0;
  local_1a4[0x21] = 0;
  local_1a4[0x22] = 0;
  local_1a4[0x23] = 0;
  local_1a4[0x24] = 0;
  local_1a4[0x25] = 0;
  local_1a4[0x26] = 0;
  local_1a4[0x27] = 0;
  local_1a4[0x28] = 0;
  local_1a4[0x29] = 0;
  local_1a4[0x2a] = 0;
  local_1a4[0x2b] = 0;
  local_1a4[0x2c] = 0;
  local_1a4[0x2d] = 0;
  local_1a4[0x2e] = 0;
  local_1a4[0x2f] = 0;
  local_1a4[0x30] = 0;
  local_1a4[0x31] = 0;
  local_1a4[0x32] = 0;
  local_1a4[0
[TRUNCATED]
```

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "cdecl",
  "hidden_this_register": null,
  "ordinary_stack_arguments": [
    {
      "name": "city",
      "offset": 4,
      "type": "OpaqueCity*",
      "width_bytes": 4
    },
    {
      "name": "live_state",
      "offset": 8,
      "type": "OpaqueLiveStateContext*",
      "width_bytes": 4
    },
    {
      "name": "update_word",
      "offset": 12,
      "type": "uint32_t",
      "width_bytes": 4
    }
  ],
  "return_register": "EAX",
  "return_type": "void",
  "saved_registers": [
    "EBX",
    "EBP",
    "ESI",
    "EDI"
  ],
  "termination": "plain RET"
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
      "va": "0x00bcc760"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bcece0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be3350"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be3500"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be3de0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be5180"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be5dd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be92e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d0e170"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d10840"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d10f90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ff1da0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00bcc7c4",
      "direction": "in",
      "other": "0x00bcc760",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00bced59",
      "direction": "in",
      "other": "0x00bcece0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00bcf465",
      "direction": "in",
      "other": "0x00bcece0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00be33c4",
      "direction": "in",
      "other": 
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "OpaqueCity*",
    "OpaqueLiveStateContext*",
    "uint32_t",
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
      "runtime validation not run"
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
      "va": "0x00bcc760"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bcece0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be3350"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be3500"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be3de0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be5180"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be5dd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be92e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d0e170"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d10840"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d10f90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ff1da0"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00bcc7c4",
      "direction": "in",
      "other": "0x00bcc760",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00bced59",
      "direction": "in",
      "other": "0x00bcece0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00bcf465",
      "direction": "in",
      "other": "0x00bcece0",
      "reference_type": "direct-call"

[TRUNCATED]
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "same_package"
    ],
    "package": "PKG-13-C4-CIV-WAVE3",
    "score": 8,
    "symbol": "culture_selection_00bf9820",
    "va": "0x00bf9820"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-GAME-INPUT-WAVE7",
    "score": 2,
    "symbol": "simulator_game_input_manager_get_00b3d350",
    "va": "0x00b3d350"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-14-A3-WORLD-WAVE3",
    "score": 2,
    "symbol": "sphere_draw_direction_00b7e560",
    "va": "0x00b7e560"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-13-E3-EMPIRE-STATE-WAVE2",
    "score": 2,
    "symbol": "SpeciesProfileSelector_00c30cc0",
    "va": "0x00c30cc0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-13-E3-EMPIRE-STATE-WAVE2",
    "score": 2,
    "symbol": "ArchetypeRelationshipsID_00c30e20",
    "va": "0x00c30e20"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-13-E4-EMPIRE-WAVE3",
    "score": 2,
    "symbol": "PoliticalOwnershipScan_00c8d060",
    "va": "0x00c8d060"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-13-E2-DIPLOMACY-ALT",
    "score": 2,
    "symbol": "RelationshipScoreBand_00d00d00",
    "va": "0x00d00d00"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-GAME-MODE-WAVE7",
    "score": 2,
    "symbol": "cell_mode_constructor_00e616c0",
    "va": "0x00e616c0"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "src/reconstruction/pkg13_c4_civ_wave3/civ_wave3.cpp",
    "src/reconstruction/pkg13_c4_civ_wave3/civ_wave3.hpp",
    "src/reconstruction/pkg13_c4_civ_wave3/civ_wave3_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-sim-social-world-wave3/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg13-c4-civ-wave3/00be2440.json"
  ]
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
    "runtime validation not run"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'ref': 'ephemeral reconstruction_knowledge.build_index', 'mode': 'derived', 'source_class': 'generated_index'}, {'ref': 'tools/reconstruction_tooling/abi_infer.py', 'mode': 'derived', 'source_class': 'derived'}, {'ref': 'GhidraMCP /disassemble_function', 'mode': 'live', 'source_class': 'ghidra'}, {'ref': 'GhidraMCP REST /decompile_function @ http://127.0.0.1:8089', 'mode': 'live', 'source_class': 'ghidra'}, {'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'mode': 'live', 'source_class': 'ghidra'}, {'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'mode': 'persisted', 'source_class': 'committed_artifact'}, {'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'mode': 'persisted', 'source_class': 'committed_artifact'}, {'ref': 'reconstruction/integrated/batch-2026-09-25-sim-social-world-wave3/handoff.json', 'mode': 'persisted', 'source_class': 'committed_artifact'}, {'ref': 'reconstruction/metadata/pkg13-c4-civ-wave3/00be2440.json', 'mode': 'persisted', 'source_class': 'committed_artifact'}, {'ref': 'src/reconstruction/pkg13_c4_civ_wave3/civ_wave3.cpp', 'mode': 'persisted', 'source_class': 'committed_artifact'}, {'ref': 'src/reconstruction/pkg13_c4_civ_wave3/civ_wave3.hpp', 'mode': 'persisted', 'source_class': 'committed_artifact'}, {'ref': 'src/reconstruction/pkg13_c4_civ_wave3/civ_wave3_model_test.cpp', 'mode': 'persisted', 'source_class': 'committed_artifact'}`

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
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/integrated/batch-2026-09-25-sim-social-world-wave3/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg13-c4-civ-wave3/00be2440.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg13_c4_civ_wave3/civ_wave3.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg13_c4_civ_wave3/civ_wave
[TRUNCATED]
```
