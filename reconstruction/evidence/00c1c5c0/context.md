# Reconstruction context 0x00c1c5c0

- Status: `partial`
- Content SHA-256: `93ad6b3532095358989e37540434b63e3f6f967d58c81249db2496bce2e4d87e`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00c1c5c0",
  "phase": "reconstruction",
  "target": "0x00c1c5c0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "Simulator_cCreatureBase_LocomotionWalkToInterior_00c1c5c0",
  "package": "PKG-13-C4-CREATURE-WAVE3",
  "subsystem": null,
  "va": "0x00c1c5c0"
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
  "content_sha256": "deab567b6f14ae2ff407dde2b964b3ed0d931c3162dd291a0d09beea2bd3b7d7",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00c1c5c0 failed: Decompilation did not complete. Reason: ",
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
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "original_bytes": 12733,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": [\n      \"entry_ESP+0x8\",\n      \"entry_ESP+0xc\",\n      \"entry_ESP+0x10\",\n      \"entry_ESP+0x14\"\n    ],\n    \"ordinary_stack_arguments\": [\n      {\n        \"entry_offset\": \"entry_ESP+0x8\",\n        \"observed\": true,\n        \"ordinal\": 2,\n        \"read\": false,\n        \"size_inferred\": false,\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      },\n      {\n        \"entry_offset\": \"entry_ESP+0xc\",\n        \"observed\": true,\n        \"ordinal\": 3,\n        \"read\": false,\n        \"size_inferred\": false,\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      },\n      {\n        \"entry_offset\": \"entry_ESP+0x10\",\n        \"observed\": true,\n        \"ordinal\": 4,\n        \"read\": false,\n        \"size_inferred\": false,\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      },\n      {\n        \"entry_offset\": \"entry_ESP+0x14\",\n        \"observed\": true,\n        \"ordinal\": 5,\n        \"read\": false,\n        \"size_inferred\": false,\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      }\n    ],\n    \"receiver\": true,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET 0x14\",\n    \"return_register\": \"ST0\",\n    \"return_semantics\": \"float_or_x87_
[TRUNCATED]
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
      "va": "0x00c0ce80"
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bc4900"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c27dd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d31a70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d32fd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d62d90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d62f60"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d630c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d63560"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d64a90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d6ce10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d6e3a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d6e910"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d6f800"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d70c70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d71060"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d71780"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00bc4bcf",
      "di
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "const Vector3*",
    "float",
    "int32_t",
    "opaque 116-byte POD matching Simulator::cLocomotionRequest"
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
      "Exercise a NaN basis and a zero-length basis in the original to confirm the recorded NaN propagation and the absence of a length guard.",
      "No original-process trace, differential run under Wine, or runtime validation has been performed.",
      "Observe a real vtable+0xDC submission to learn whether the request pointer escapes and whether the handle header word at handle-0x04 is a reference count.",
      "Observe the 0x00ac4570 container at creature+0xBC0 to confirm the 60-byte element semantics.",
      "Observe the concrete creature+0x2B0, +0x2A0 and +0x330 field semantics in an original process.",
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
  "callees": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c0ce80"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bc4900"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c27dd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d31a70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d32fd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d62d90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d62f60"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d630c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d63560"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d64a90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d6ce10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d6e3a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d6e910"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d6f800"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d70c70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d71060"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d71780"
    },
    {
      "name": null,
      "recon
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
    "package": "PKG-13-C4-CREATURE-WAVE3",
    "score": 8,
    "symbol": "Simulator_cCreatureBase_CreateAndStartPool2Effect_00c1d460",
    "va": "0x00c1d460"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg13-c4-creature-wave3/creature_wave3.cpp",
    "reconstruction/staging/pkg13-c4-creature-wave3/creature_wave3.hpp",
    "reconstruction/staging/pkg13-c4-creature-wave3/creature_wave3_model_test.cpp",
    "src/reconstruction/pkg13_c4_creature_wave3/creature_wave3.cpp",
    "src/reconstruction/pkg13_c4_creature_wave3/creature_wave3.hpp",
    "src/reconstruction/pkg13_c4_creature_wave3/creature_wave3_model_test.cpp",
    "src/reconstruction/pkg13_c4_creature_wave3/metadata_package_validation.py"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-sim-social-world-wave3/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg13-c4-creature-wave3/00c1c5c0.json"
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
    "Exercise a NaN basis and a zero-length basis in the original to confirm the recorded NaN propagation and the absence of a length guard.",
    "No original-process trace, differential run under Wine, or runtime validation has been performed.",
    "Observe a real vtable+0xDC submission to learn whether the request pointer escapes and whether the handle header word at handle-0x04 is a reference count.",
    "Observe the 0x00ac4570 container at creature+0xBC0 to confirm the 60-byte element semantics.",
    "Observe the concrete creature+0x2B0, +0x2A0 and +0x330 field semantics in an original process.",
    "runtime validation not run"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'derived'}, {'mode': 'derived', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'derived'}, {'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-sim-social-world-wave3/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg13-c4-creature-wave3/00c1c5c0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg13-c4-creature-wave3/creature_wave3.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg13-c4-creature-wave3/creature_wave3.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg13-c4-creature-wave3/creature_wave3_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg13_c4_creature_wave3/creature_wave3.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg13_c4_creature_wave3/creature_wave3.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg13_c4_creature_wave3/creature_wave3_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg13_c4_creature_wave3/metadata_package_validation.py', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg13-c4-creature-wave3/00c1c5c0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg13-c4-crea
[TRUNCATED]
```
