# Reconstruction context 0x00596e10

- Status: `partial`
- Content SHA-256: `04ce20d3a945b767089bcff7781ba51c48ef6b543d660ab984949eeec125804c`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00596e10",
  "phase": "reconstruction",
  "target": "0x00596e10"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "collectable_lock_00596e10",
  "package": "PKG-11-A4-PROGRESSION-WAVE3",
  "subsystem": null,
  "va": "0x00596e10"
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
  "content_sha256": "aecc6a5fc29a5ec5abf1f9120451ff595e14ea8414330e03276989f2e2fb0814",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00596e10 failed: Decompilation did not complete. Reason: ",
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
  "original_bytes": 8649,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"ordinary_stack_argument_slots\": [\n      \"entry_ESP+0x4\"\n    ],\n    \"ordinary_stack_arguments\": [\n      {\n        \"entry_offset\": \"entry_ESP+0x4\",\n        \"observed\": true,\n        \"ordinal\": 1,\n        \"read\": false,\n        \"size_inferred\": true,\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      }\n    ],\n    \"ret_form\": \"RET 0x8\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"integral_in_EAX\",\n    \"saved_registers\": [\n      \"ESI\"\n    ],\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"entry_ESP+0x4\",\n        \"observed\": true,\n        \"ordinal\": 1,\n        \"read\": false,\n        \"size_inferred\": true,\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      }\n    ],\n    \"stack_cleanup_bytes\": 8,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"RET 0x8\"\n  },\n  \"abstained_because\": [\n    \"flow_not_modelled: the linear ESP walk ends at +8, so the listing is not one path\",\n    \"receiver_not_determinable: ecx_read_without_deref\",\n    \"receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_read_without_deref), and the convention rule that would apply discriminates on receiver absence\"\n  ],\n  \"cleanup\": {\n    \"bytes\": 8,\n    \"confidence\": \"OBSERVED\",\n    \"corroboration\": \"not_available\",\n    \"evidence\": \"ret 0x8\",\n    \"side\": \"callee\"\n  },\n  \"compl
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
      "va": "0x005ef470"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d0e170"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e4fac0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00f12fc0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x005ef4f8",
      "direction": "in",
      "other": "0x005ef470",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d0ec2c",
      "direction": "in",
      "other": "0x00d0e170",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d0edca",
      "direction": "in",
      "other": "0x00d0e170",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d0ef2a",
      "direction": "in",
      "other": "0x00d0e170",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d0f1db",
      "direction": "in",
      "other": "0x00d0e170",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e4fb4a",
      "direction": "in",
      "other": "0x00e4fac0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f13046",
      "direction": "in",
      "other": "0x00f12fc0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00596e31",
      "direction": "out",
      "other": "0x005945b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00596e1e",
      "direction": "out",
      "other": "0x00595eb0",
   
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
      "va": "0x005ef470"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d0e170"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e4fac0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00f12fc0"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x005ef4f8",
      "direction": "in",
      "other": "0x005ef470",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d0ec2c",
      "direction": "in",
      "other": "0x00d0e170",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d0edca",
      "direction": "in",
      "other": "0x00d0e170",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d0ef2a",
      "direction": "in",
      "other": "0x00d0e170",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d0f1db",
      "direction": "in",
      "other": "0x00d0e170",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e4fb4a",
      "direction": "in",
      "other": "0x00e4fac0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f13046",
      "direction": "in",
      "other": "0x00f12fc0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00596e31",
      "direction": "out",
      "other": "0x005945b0",
      "reference_type": "direct-call"
    },
    {
     
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
    "symbol": "collectable_unlock_00596da0",
    "va": "0x00596da0"
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
    "reconstruction/metadata/pkg11-a4-progression-wave3/00596e10.json"
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
        "0x010535e0",
        "0x010535e0",
        "0x005942e0",
        "0x005942e0",
        "0x00596da0",
        "0x00596da0",
        "0x00596e10",
        "0x00596e10",
        "0x005973a0",
        "0x005973a0",
        "0x00598db0",
        "0x00598db0",
        "0x00598e90",
        "0x00598e90",
        "0x00be2590",
        "0x00be2590"
      ],
      "conflict_id": "U-E007",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The resource seam and cited call boundary are retained, but original ownership, priority, cache, failure, and load-order semantics are unresolved.",
      "resolution_status": "The resource seam and cited call boundary are retained, but original ownership, priority, cache, failure, and load-order semantics are unresolved.",
      "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
      "subject": null,
      "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
    },
    {
      "anchors": [
        "0x010535e0",
        "0x010535e0",
        "0x005942e0",
        "0x005942e0",
        "0x00596da0",
        "0x00596da0",
        "0x00596e10",
        "0x00596e10",
        "0x005973a0",
        "0x005973a0",
        "0x00598db0",
        "0x00598db0",
        "0x00598e90",
        "0x00598e90",
        "0x00be2590",
        "0x00be2590"
      ],
      "conflict_id": "U-E008",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The declared state surface is retained, but th
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'derived'}, {'mode': 'derived', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'derived'}, {'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-sim-social-world-wave3/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg11-a4-progression-wave3/00596e10.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg11-a4-progression-wave3/progression_wave3.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg11-a4-progression-wave3/progression_wave3.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg11_a4_progression_wave3/progression_wave3.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg11_a4_progression_wave3/progression_wave3.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg11_a4_progression_wave3/progression_wave3_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg11-a4-progression-wave3/00596e10.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg11-a4-p
[TRUNCATED]
```
