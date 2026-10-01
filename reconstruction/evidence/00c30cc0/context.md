# Reconstruction context 0x00c30cc0

- Status: `partial`
- Content SHA-256: `33c311aa3f9ffe1f7bcabf176ecfbbf219f1d1963e9a7860264ce8414a1c55d0`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00c30cc0",
  "phase": "reconstruction",
  "target": "0x00c30cc0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "None",
  "name": "SpeciesProfileSelector_00c30cc0",
  "package": "PKG-13-E3-EMPIRE-STATE-WAVE2",
  "subsystem": "Simulator.SpeciesProfile",
  "va": "0x00c30cc0"
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
  "content_sha256": "9db3d64561a0adee719655765ca9f474d810a9b11849c9b2b42e2b741efda01f",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00c30cc0 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "cdecl",
  "hidden_this": null,
  "return_register": "EAX",
  "return_type": "std::uint32_t",
  "return_width_bytes": 4,
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "archetype",
      "position": 1,
      "type": "std::uint32_t",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x08",
      "name": "difficulty",
      "position": 2,
      "type": "std::uint32_t",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 8,
  "stack_cleanup_owner": "caller"
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
      "va": "0x00c30e80"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00c30ea4",
      "direction": "in",
      "other": "0x00c30e80",
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
    "None",
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
      "gate-species-profile-selector-00c30cc0",
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
      "va": "0x00c30e80"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00c30ea4",
      "direction": "in",
      "other": "0x00c30e80",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 1,
  "fan_out": 0,
  "manifest_callees": [],
  "manifest_callers": [
    "0x00c30e80"
  ],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0450",
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
      "same_package",
      "same_subsystem",
      "same_class",
      "shared_types:None",
      "same_calling_convention"
    ],
    "package": "PKG-13-E3-EMPIRE-STATE-WAVE2",
    "score": 24,
    "symbol": "ArchetypeRelationshipsID_00c30e20",
    "va": "0x00c30e20"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem"
    ],
    "package": "PKG-13-E3-EMPIRE-STATE-WAVE2",
    "score": 14,
    "symbol": "ProfileSetter_00c33690",
    "va": "0x00c33690"
  },
  {
    "match_basis": [
      "same_class",
      "shared_types:None",
      "same_calling_convention"
    ],
    "package": "PKG-13-E2-DIPLOMACY-ALT",
    "score": 10,
    "symbol": "RelationshipScoreBand_00d00d00",
    "va": "0x00d00d00"
  },
  {
    "match_basis": [
      "same_class",
      "shared_types:None"
    ],
    "package": "PKG-11-H2-ROOT-ACCESSORS",
    "score": 8,
    "symbol": "root_accessor_00b3d3b0",
    "va": "0x00b3d3b0"
  },
  {
    "match_basis": [
      "same_class",
      "shared_types:None"
    ],
    "package": "PKG-11-H2-ROOT-ACCESSORS",
    "score": 8,
    "symbol": "root_accessor_00b3d3e0",
    "va": "0x00b3d3e0"
  },
  {
    "match_basis": [
      "same_class",
      "shared_types:None"
    ],
    "package": "PKG-11-H2-ROOT-ACCESSORS",
    "score": 8,
    "symbol": "root_accessor_00b3d3f0",
    "va": "0x00b3d3f0"
  },
  {
    "match_basis": [
      "same_class",
      "shared_types:None"
    ],
    "package": "PKG-11-H2-ROOT-ACCESSORS",
    "score": 8,
    "symbol": "root_accessor_00b3d430",
    "va": "0x00b3d430"
  },
  {
    "match_basis": 
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg13_e3_empire_state_wave2/empire_state_wave2.cpp",
  "files": [
    "reconstruction/staging/pkg13-e3-empire-state-wave2/empire_state_boundary.S",
    "reconstruction/staging/pkg13-e3-empire-state-wave2/empire_state_boundary_test.sh",
    "reconstruction/staging/pkg13-e3-empire-state-wave2/empire_state_wave2.cpp",
    "reconstruction/staging/pkg13-e3-empire-state-wave2/empire_state_wave2.hpp",
    "reconstruction/staging/pkg13-e3-empire-state-wave2/empire_state_wave2_model_test.cpp",
    "src/reconstruction/pkg13_e3_empire_state_wave2/empire_state_boundary.S",
    "src/reconstruction/pkg13_e3_empire_state_wave2/empire_state_boundary_test.sh",
    "src/reconstruction/pkg13_e3_empire_state_wave2/empire_state_wave2.cpp",
    "src/reconstruction/pkg13_e3_empire_state_wave2/empire_state_wave2.hpp",
    "src/reconstruction/pkg13_e3_empire_state_wave2/empire_state_wave2_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-sim-social-world-wave2/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg13-e3-empire-state-wave2/00c30cc0.json"
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
    "gate-species-profile-selector-00c30cc0",
    "runtime validation not run"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-sim-social-world-wave2/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg13-e3-empire-state-wave2/00c30cc0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg13-e3-empire-state-wave2/empire_state_boundary.S', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg13-e3-empire-state-wave2/empire_state_boundary_test.sh', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg13-e3-empire-state-wave2/empire_state_wave2.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg13-e3-empire-state-wave2/empire_state_wave2.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg13-e3-empire-state-wave2/empire_state_wave2_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg13_e3_empire_state_wave2/empire_state_boundary.S', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg13_e3_empire_state_wave2/empire_state_boundary_test.sh', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg13_e3_empire_state_wave2/empire_state_wave2.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg13_e3_empire_state_wave2/empire_state_wave2.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg13_e3_empire_state_wave2/empire_state_wave2_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/integrated/batch-2026-09-25-sim-social-world-wave2/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg13-e3-empire-state-wave2/00c30cc0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg13-e3-empire-state-wave2/empire_state_boundary.S",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg13-e3-empire-state-wave2/empire_state_boundary_test.sh",
      "source_class": "committed_artifact"
    },
    {
      "mode": "p
[TRUNCATED]
```
