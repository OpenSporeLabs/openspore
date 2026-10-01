# Reconstruction context 0x00596da0

- Status: `partial`
- Content SHA-256: `1d669e290aa72e48994193150299e755933cad31c58d2a40d02a959b754fbfaf`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00596da0",
  "phase": "reconstruction",
  "target": "0x00596da0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "collectable_unlock_00596da0",
  "package": "PKG-11-A4-PROGRESSION-WAVE3",
  "subsystem": null,
  "va": "0x00596da0"
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
  "content_sha256": "dde1cf71171b76e28a50bda34b88c949677e35ef2d3bfe2bfb13efc458e49971",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00596da0 failed: Decompilation did not complete. Reason: ",
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
  "original_bytes": 11308,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": [\n      \"entry_ESP+0x4\",\n      \"entry_ESP+0x8\"\n    ],\n    \"ordinary_stack_arguments\": [\n      {\n        \"entry_offset\": \"entry_ESP+0x4\",\n        \"observed\": true,\n        \"ordinal\": 1,\n        \"read\": false,\n        \"size_inferred\": false,\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      },\n      {\n        \"entry_offset\": \"entry_ESP+0x8\",\n        \"observed\": true,\n        \"ordinal\": 2,\n        \"read\": false,\n        \"size_inferred\": false,\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      }\n    ],\n    \"receiver\": true,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET 0xc\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"integral_in_EAX\",\n    \"saved_registers\": [\n      \"ESI\"\n    ],\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"entry_ESP+0x4\",\n        \"observed\": true,\n        \"ordinal\": 1,\n        \"read\": false,\n        \"size_inferred\": false,\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      },\n      {\n        \"entry_offset\": \"entry_ESP+0x8\",\n        \"observed\": true,\n        \"ordinal\": 2,\n        \"read\": false,\n        \"size_inferred\": false,\n        \"sizes\": [\n          4\n        ],\n        \
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
      "va": "0x005973a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005bf1e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005ef470"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb8b20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c7a1f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00de4f50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e4fac0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e83430"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e83910"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00f12fc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01058460"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x005973f0",
      "direction": "in",
      "other": "0x005973a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005bf2be",
      "direction": "in",
      "other": "0x005bf1e0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005bf2fa",
      "direction": "in",
      "other": "0x005bf1e0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005ef574",
      "direction": "in",
      "other": "0x005ef470",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "std::int32_t",
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
      "va": "0x005973a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005bf1e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005ef470"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb8b20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c7a1f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00de4f50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e4fac0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e83430"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e83910"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00f12fc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01058460"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x005973f0",
      "direction": "in",
      "other": "0x005973a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005bf2be",
      "direction": "in",
      "other": "0x005bf1e0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005bf2fa",
      "direction": "in",
      "other": "0x005bf1e0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005ef574",
      "direction": "in",
      "other": "0x
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
    "package": "PKG-11-A4-PROGRESSION-WAVE3",
    "score": 8,
    "symbol": "collectable_lock_00596e10",
    "va": "0x00596e10"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg11-a4-progression-wave3/progression_wave3.cpp",
    "reconstruction/staging/pkg11-a4-progression-wave3/progression_wave3.hpp",
    "src/reconstruction/pkg11_a4_progression_wave3/progression_wave3.cpp",
    "src/reconstruction/pkg11_a4_progression_wave3/progression_wave3.hpp",
    "src/reconstruction/pkg11_a4_progression_wave3/progression_wave3_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-sim-social-world-wave3/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg11-a4-progression-wave3/00596da0.json"
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
  "conflicts": {
    "original_bytes": 11277,
    "preview": "[\n  {\n    \"anchors\": [\n      \"0x00d01e30\",\n      \"0x00d01e30\",\n      \"0x00d038e0\",\n      \"0x00d038e0\",\n      \"0x00d05830\",\n      \"0x00d05830\",\n      \"0x00d06270\",\n      \"0x00d06270\",\n      \"0x00d065a0\",\n      \"0x00d065a0\",\n      \"0x00d06920\",\n      \"0x00d06920\",\n      \"0x00596da0\"\n    ],\n    \"conflict_id\": \"U-E001\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.\",\n    \"resolution_status\": \"The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x01037d30\",\n      \"0x01037d30\",\n      \"0x01037d30\",\n      \"0x01037d30\",\n      \"0x0103a480\",\n      \"0x0103a480\",\n      \"0x0103e8e0\",\n      \"0x0103e8e0\",\n      \"0x0103fc10\",\n      \"0x0103fc10\",\n      \"0x00c877f0\",\n      \"0x00c877f0\",\n      \"0x00596da0\",\n      \"0x01037d30\",\n      \"0x00d2e8a0\",\n      \"0x0103e8e0\"\n    ],\n    \"conflict_id\": \"U-E004\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The committed evidence does not establish the requ
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'derived'}, {'mode': 'derived', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'derived'}, {'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-sim-social-world-wave3/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg11-a4-progression-wave3/00596da0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg11-a4-progression-wave3/progression_wave3.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg11-a4-progression-wave3/progression_wave3.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg11_a4_progression_wave3/progression_wave3.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg11_a4_progression_wave3/progression_wave3.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg11_a4_progression_wave3/progression_wave3_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg11-a4-progression-wave3/00596da0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg11-a4-p
[TRUNCATED]
```
