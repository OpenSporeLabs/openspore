# Reconstruction context 0x00b3d430

- Status: `partial`
- Content SHA-256: `ba1bfad09bf40ef9164bfa09e1eede993af31c81e910ce8f6beb73b1b1e0f600`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00b3d430",
  "phase": "reconstruction",
  "target": "0x00b3d430"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "None",
  "name": "FUN_00b3d430",
  "package": "PKG-11-H2-ROOT-ACCESSORS",
  "subsystem": "Simulator.RootAccessors",
  "va": "0x00b3d430"
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
  "content_sha256": "dbec3e2bb094cdc46273e984b9410375e3405c62444e8806b6c1cfed3b9d4d47",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00b3d430 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "cdecl-compatible no-argument accessor",
  "hidden_receiver": null,
  "ordinary_stack_argument_slots": 0,
  "ret_form": "RET",
  "return_note": "opaque 32-bit slot word",
  "return_register": "EAX",
  "return_width_bytes": 4,
  "stack_cleanup_bytes": 0
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
      "va": "0x00ae3d70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae6240"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b32b20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b32ce0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b32e80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b33030"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b33130"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b33350"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b33540"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b335d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b93550"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b9d820"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba0080"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb2330"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb23e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bba990"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00ae3e8f",
      "direction": "in",
      "other": "0x00ae3d70",
      "reference_type": "direct-call"
    },

[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [
    "global:MOV EAX,[0x0167eb30]",
    "global:READ from 0x00b3d430",
    "global:get_xrefs_to(0x0167eb30); one READ xref from this function"
  ],
  "types": [
    "None",
    "RootWord",
    "opaque 32-bit slot word",
    "undefined4"
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
      "gate-root-slot-00b3d430",
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
      "va": "0x00ae3d70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae6240"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b32b20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b32ce0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b32e80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b33030"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b33130"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b33350"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b33540"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b335d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b93550"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b9d820"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba0080"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb2330"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb23e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bba990"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bbe740"
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
      "same_package",
      "same_subsystem",
      "same_class",
      "shared_types:None,RootWord,opaque 32-bit slot word,undefined4",
      "same_calling_convention"
    ],
    "package": "PKG-11-H2-ROOT-ACCESSORS",
    "score": 30,
    "symbol": "root_accessor_00b3d3b0",
    "va": "0x00b3d3b0"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "same_class",
      "shared_types:None,RootWord,opaque 32-bit slot word,undefined4",
      "same_calling_convention"
    ],
    "package": "PKG-11-H2-ROOT-ACCESSORS",
    "score": 30,
    "symbol": "root_accessor_00b3d3e0",
    "va": "0x00b3d3e0"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "same_class",
      "shared_types:None,RootWord,opaque 32-bit slot word,undefined4",
      "same_calling_convention"
    ],
    "package": "PKG-11-H2-ROOT-ACCESSORS",
    "score": 30,
    "symbol": "root_accessor_00b3d3f0",
    "va": "0x00b3d3f0"
  },
  {
    "match_basis": [
      "same_class",
      "shared_types:None"
    ],
    "package": "PKG-13-E3-EMPIRE-STATE-WAVE2",
    "score": 8,
    "symbol": "SpeciesProfileSelector_00c30cc0",
    "va": "0x00c30cc0"
  },
  {
    "match_basis": [
      "same_class",
      "shared_types:None"
    ],
    "package": "PKG-13-E3-EMPIRE-STATE-WAVE2",
    "score": 8,
    "symbol": "ArchetypeRelationshipsID_00c30e20",
    "va": "0x00c30e20"
  },
  {
    "match_basis": [
      "same_class",
      "shared_types:None"
    ],
    "package": "PKG-11-SIM-CORE",
    "score": 8,
    "symbol": "Simulator_IsNotStarOrBinarySta
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg11_h2_root_accessors/root_accessors.cpp",
  "files": [
    "reconstruction/staging/pkg11-h2-root-accessors/root_accessors.cpp",
    "reconstruction/staging/pkg11-h2-root-accessors/root_accessors.hpp",
    "reconstruction/staging/pkg11-h2-root-accessors/root_accessors_model_test.cpp",
    "src/reconstruction/pkg11_h2_root_accessors/root_accessors.cpp",
    "src/reconstruction/pkg11_h2_root_accessors/root_accessors.hpp",
    "src/reconstruction/pkg11_h2_root_accessors/root_accessors_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-sim-social-world-wave1/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg11-h2-root-accessors/00b3d430.json"
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
    "What concrete object and vtable can the slot contain?",
    "What lifetime guarantee, if any, applies to a nonzero returned word?",
    "Which callers interpret the returned word as a pointer, handle, or raw state value?",
    "Which code publishes, replaces, or clears 0x0167eb30?",
    "gate-root-slot-00b3d430",
    "runtime validation not run"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-sim-social-world-wave1/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg11-h2-root-accessors/00b3d430.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg11-h2-root-accessors/root_accessors.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg11-h2-root-accessors/root_accessors.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg11-h2-root-accessors/root_accessors_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg11_h2_root_accessors/root_accessors.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg11_h2_root_accessors/root_accessors.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg11_h2_root_accessors/root_accessors_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/integrated/batch-2026-09-25-sim-social-world-wave1/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg11-h2-root-accessors/00b3d430.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg11-h2-root-accessors/root_accessors.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg11-h2-root-accessors/root_accessors.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "rec
[TRUNCATED]
```
