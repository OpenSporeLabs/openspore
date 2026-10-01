# Reconstruction context 0x00dd0e10

- Status: `partial`
- Content SHA-256: `e21d5c28d19a7635d85f2bc0b7dd093677a1372dded28607a4279764ca3fe7f1`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00dd0e10",
  "phase": "reconstruction",
  "target": "0x00dd0e10"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueGameObject",
  "name": "FUN_00dd0e10",
  "package": "PKG-20-GAMEGLOBAL",
  "subsystem": "GameGlobal",
  "va": "0x00dd0e10"
}
```

## 03_current_status

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "blocked": true,
  "reconstructed": false,
  "runtime_gated": true,
  "runtime_validated": 0,
  "status": "blocked"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "452016d4a4e0451400c5ac3d6eb9a92e23dcbe3fbed02cec82a793d420bb68f7",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00dd0e10 failed: Decompilation did not complete. Reason: ",
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
  "original_bytes": 13140,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": [\n      \"entry_ESP+0xb\",\n      \"entry_ESP+0x23\",\n      \"entry_ESP+0x34\",\n      \"entry_ESP+0x3c\",\n      \"entry_ESP+0x44\"\n    ],\n    \"ordinary_stack_arguments\": [\n      {\n        \"entry_offset\": \"entry_ESP+0xb\",\n        \"observed\": true,\n        \"ordinal\": 2,\n        \"read\": false,\n        \"size_inferred\": true,\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      },\n      {\n        \"entry_offset\": \"entry_ESP+0x23\",\n        \"observed\": true,\n        \"ordinal\": 8,\n        \"read\": false,\n        \"size_inferred\": true,\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      },\n      {\n        \"entry_offset\": \"entry_ESP+0x34\",\n        \"observed\": true,\n        \"ordinal\": 13,\n        \"read\": false,\n        \"size_inferred\": true,\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      },\n      {\n        \"entry_offset\": \"entry_ESP+0x3c\",\n        \"observed\": true,\n        \"ordinal\": 15,\n        \"read\": false,\n        \"size_inferred\": true,\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      },\n      {\n        \"entry_offset\": \"entry_ESP+0x44\",\n        \"observed\": true,\n        \"ordinal\": 17,\n        \"read\": false,\n        \"size
[TRUNCATED]
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "address_window_offset_005c65e0",
      "reconstructed": true,
      "va": "0x005c65e0"
    },
    {
      "name": "pkg13_creature_accessor_00b1fdb0",
      "reconstructed": true,
      "va": "0x00b1fdb0"
    },
    {
      "name": "FUN_00b3d2a0",
      "reconstructed": true,
      "va": "0x00b3d2a0"
    },
    {
      "name": "FUN_00b8de30",
      "reconstructed": false,
      "va": "0x00b8de30"
    },
    {
      "name": "Simulator_LookupEmpireByPoliticalId",
      "reconstructed": true,
      "va": "0x00ba9370"
    }
  ],
  "callers": [],
  "edge_rows": [
    {
      "callsite": "0x00dd0f08",
      "direction": "out",
      "other": "0x0041df50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00dd0f40",
      "direction": "out",
      "other": "0x0041df50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00dd0fa1",
      "direction": "out",
      "other": "0x0041df50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00dd0fd9",
      "direction": "out",
      "other": "0x0041df50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00dd0e71",
      "direction": "out",
      "other": "0x005c3d90",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00dd0e87",
      "direction": "out",
      "other": "0x005c3d90",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00dd104d",
      "direction": "out",
      "other": "0x005c65e0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00dd0
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "OpaqueGameObject"
  ],
  "vtables": [
    "vtable:0x0147cbbc"
  ]
}
```

## 09_state_event_relationships

- State: `present`
- Provenance: `knowledgegraph/research/semantic-decomp.json, reconstruction/knowledge/index.json`

```json
{
  "original_bytes": 9456,
  "preview": "{\n  \"runtime\": {\n    \"blocking_reason\": [\n      \"owner type\",\n      \"field meanings\",\n      \"vtable implementation\",\n      \"returned object identity\"\n    ],\n    \"gates\": [\n      \"indirect_dispatch_state_observation\"\n    ],\n    \"validated\": 0\n  },\n  \"semantic\": {\n    \"category\": null,\n    \"classification\": \"NEEDS_RUNTIME\",\n    \"confidence\": {\n      \"overall\": 0.83\n    },\n    \"contradictions\": [],\n    \"downstream_unlock_count\": 15,\n    \"evidence\": [\n      {\n        \"finding\": \"Null gate, +0x84/+0x88 switch, ~Epic/~MiniBoss strings, local record construction, and empire lookup branch.\",\n        \"kind\": \"target_decompilation\",\n        \"source\": \"Ghidra 0x00dd0e10\"\n      },\n      {\n        \"finding\": \"The method belongs to a concrete vtable installed on the timeline-event data object and is released by its destructor.\",\n        \"kind\": \"constructor_destructor\",\n        \"source\": \"Ghidra 0x00dd0ca0 and 0x00dd0cf0\"\n      },\n      {\n        \"finding\": \"Allocates UI/TimelineEventSporepediaData at 0xb0 or 0x9c and dispatches its vtable.\",\n        \"kind\": \"allocation_anchor\",\n        \"source\": \"Ghidra 0x00e2f6e0\"\n      },\n      {\n        \"finding\": \"Creates the same timeline-event data family and calls its virtual operations during local event setup.\",\n        \"kind\": \"representative_consumer\",\n        \"source\": \"Ghidra 0x00e47930\"\n      },\n      {\n        \"finding\": \"The candidate cSPAssetDataOTDB is 0x78 bytes; th
[TRUNCATED]
```

## 10_dependencies

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "address_window_offset_005c65e0",
      "reconstructed": true,
      "va": "0x005c65e0"
    },
    {
      "name": "pkg13_creature_accessor_00b1fdb0",
      "reconstructed": true,
      "va": "0x00b1fdb0"
    },
    {
      "name": "FUN_00b3d2a0",
      "reconstructed": true,
      "va": "0x00b3d2a0"
    },
    {
      "name": "FUN_00b8de30",
      "reconstructed": false,
      "va": "0x00b8de30"
    },
    {
      "name": "Simulator_LookupEmpireByPoliticalId",
      "reconstructed": true,
      "va": "0x00ba9370"
    }
  ],
  "callees_truncated": false,
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00dd0f08",
      "direction": "out",
      "other": "0x0041df50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00dd0f40",
      "direction": "out",
      "other": "0x0041df50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00dd0fa1",
      "direction": "out",
      "other": "0x0041df50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00dd0fd9",
      "direction": "out",
      "other": "0x0041df50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00dd0e71",
      "direction": "out",
      "other": "0x005c3d90",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00dd0e87",
      "direction": "out",
      "other": "0x005c3d90",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00dd104d",
      "direction": "out",
      "other": "0x005
[TRUNCATED]
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x0147cbbc",
      "same_semantic_family"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 15,
    "symbol": "FUN_00ff3f00",
    "va": "0x00ff3f00"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "PKG-20-GAMEGLOBAL",
    "score": 8,
    "symbol": "pkg20_gameglobal_00ba83a0",
    "va": "0x00ba83a0"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "PKG-20-GAMEGLOBAL",
    "score": 8,
    "symbol": "pkg20_gameglobal_00ba8420",
    "va": "0x00ba8420"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "PKG-20-GAMEGLOBAL",
    "score": 8,
    "symbol": "map_int_whatever_find",
    "va": "0x00e5c780"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x0147cbbc"
    ],
    "package": "pkg-swarm-w1-005c0dd0",
    "score": 4,
    "symbol": "re_005c0dd0",
    "va": "0x005c0dd0"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x0147cbbc"
    ],
    "package": "pkg-swarm-w1-006413d0",
    "score": 4,
    "symbol": "re_006413d0",
    "va": "0x006413d0"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x0147cbbc"
    ],
    "package": "PKG-16-SPOREPEDIA-ONLINE",
    "score": 4,
    "symbol": "Sporepedia_cSPAssetDataOTDB_IsEditable_00641400",
    "va": "0x00641400"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x0147cbbc"
    ],
    "package": "pkg-swarm-w1-00641410",
    "score": 4,
    "symbol": "re_00641410",
    "va": "0x00641410"
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

- State: `present`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

```json
{
  "original_bytes": 8765,
  "preview": "{\n  \"category\": null,\n  \"classification\": \"NEEDS_RUNTIME\",\n  \"confidence\": {\n    \"overall\": 0.83\n  },\n  \"contradictions\": [],\n  \"downstream_unlock_count\": 15,\n  \"evidence\": [\n    {\n      \"finding\": \"Null gate, +0x84/+0x88 switch, ~Epic/~MiniBoss strings, local record construction, and empire lookup branch.\",\n      \"kind\": \"target_decompilation\",\n      \"source\": \"Ghidra 0x00dd0e10\"\n    },\n    {\n      \"finding\": \"The method belongs to a concrete vtable installed on the timeline-event data object and is released by its destructor.\",\n      \"kind\": \"constructor_destructor\",\n      \"source\": \"Ghidra 0x00dd0ca0 and 0x00dd0cf0\"\n    },\n    {\n      \"finding\": \"Allocates UI/TimelineEventSporepediaData at 0xb0 or 0x9c and dispatches its vtable.\",\n      \"kind\": \"allocation_anchor\",\n      \"source\": \"Ghidra 0x00e2f6e0\"\n    },\n    {\n      \"finding\": \"Creates the same timeline-event data family and calls its virtual operations during local event setup.\",\n      \"kind\": \"representative_consumer\",\n      \"source\": \"Ghidra 0x00e47930\"\n    },\n    {\n      \"finding\": \"The candidate cSPAssetDataOTDB is 0x78 bytes; the target accesses fields beyond its end and the observed allocation is 0xb0/0x9c.\",\n      \"kind\": \"structure_separator\",\n      \"source\": \"Ghidra cSPAssetDataOTDB layout\"\n    },\n    {\n      \"finding\": \"No cSPAssetDataOTDB constructor, network call, cCommEvent constructor, or universal event queue is attached to this method.\",\n      \"
[TRUNCATED]
```

## 14_conflicts_questions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json, knowledgegraph/research/semantic-decomp.json`

```json
{
  "conflicts": [],
  "unresolved_questions": [
    "Are the Epic and MiniBoss labels presentation-only or part of a broader communication state transition?",
    "Does receiver+0x9c hold a local event payload, a property list, or an opaque service record?",
    "What are the exact semantic names and allowed values of receiver+0x84 and +0x88?",
    "What do the empire lookup values mean in the subtype-5 path?",
    "What type and ownership does the vtable+0x0c result have?",
    "Which virtual consumer invokes this method in each timeline-event variant?",
    "field meanings",
    "indirect_dispatch_state_observation",
    "owner type",
    "returned object identity",
    "vtable implementation"
  ]
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
