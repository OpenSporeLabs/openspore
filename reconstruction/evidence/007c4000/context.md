# Reconstruction context 0x007c4000

- Status: `partial`
- Content SHA-256: `dd34cdcca6291d526b7e3c9cae42f923e9242b13e9d525eb79a2c2fccbb1cc4b`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x007c4000",
  "phase": "reconstruction",
  "target": "0x007c4000"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_007c4000",
  "package": null,
  "subsystem": "Terrain",
  "va": "0x007c4000"
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
  "content_sha256": "92f66c9ec29a298cdfa0327d51551ac0e355416f9050eee9dcdfc18a2c0ef0fc",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x007c4000 failed: Decompilation did not complete. Reason: ",
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
  "original_bytes": 6152,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"receiver\": true,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"unclassified_in_EAX;void_possible\",\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"RET\"\n  },\n  \"abstained_because\": [],\n  \"cleanup\": {\n    \"bytes\": 0,\n    \"confidence\": \"INFERRED\",\n    \"corroboration\": \"not_available\",\n    \"evidence\": \"ret with no immediate, no stack reads\",\n    \"side\": \"caller\"\n  },\n  \"completeness\": \"PARTIAL\",\n  \"conflicts\": [],\n  \"content_sha256\": \"045ad9bb66edabff49995068231a41498433ffeb6c7fe82ce50482bfc5a7d678\",\n  \"conventions\": {\n    \"ambiguities\": [],\n    \"calling_convention\": \"__thiscall\",\n    \"candidate_conventions\": [\n      \"__thiscall\",\n      \"__fastcall\"\n    ],\n    \"confidence\": \"INFERRED\",\n    \"corroboration\": \"not_available\"\n  },\n  \"cross_validation\": {\n    \"agreement\": false,\n    \"ghidra\": \"no_information\",\n    \"ghidra_calling_convention\": null,\n    \"ghidra_parameter_count\": 0,\n    \"persisted\": \"no_information\",\n    \"persisted_calling_convention\": null\n  },\n  \"dispatch\": {\n    \"call_offsets\": [],\n    \"indirect_calls\": 0,\n    \"vtable_shaped_loads\": 0\n  },\n  \"inferences\": [\n    {\n      \"based_on\": [\n        \"obs-0003
[TRUNCATED]
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "FUN_007c3ba0",
      "reconstructed": false,
      "va": "0x007c3ba0"
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00430e70"
    },
    {
      "name": "Editors::cEditor::Dispose",
      "reconstructed": false,
      "va": "0x00576c50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006f0890"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006f5260"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006f9cf0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0076b000"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0076b5d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0076b840"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00777060"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0077f210"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007b29a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007b77a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007b9620"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007b9e80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007bd540"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007bd640"
    }
  ],
  "edge_rows": [
    {
      "c
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
      "name": "FUN_007c3ba0",
      "reconstructed": false,
      "va": "0x007c3ba0"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00430e70"
    },
    {
      "name": "Editors::cEditor::Dispose",
      "reconstructed": false,
      "va": "0x00576c50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006f0890"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006f5260"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006f9cf0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0076b000"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0076b5d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0076b840"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00777060"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0077f210"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007b29a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007b77a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007b9620"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007b9e80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007bd540"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007bd640"
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
      "same_subsystem"
    ],
    "package": "pkg-swarm-w1-00f9b7f0",
    "score": 6,
    "symbol": "re_00f9b7f0",
    "va": "0x00f9b7f0"
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
  "unresolved_questions": []
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'derived'}, {'mode': 'derived', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'derived'}, {'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}`

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
