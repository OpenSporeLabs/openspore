# Reconstruction context 0x00c982a0

- Status: `partial`
- Content SHA-256: `735b8c58a35dcb323a921cc6c6086313c9bf0f31d4a3638c0ebd4623efd58ad7`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00c982a0",
  "phase": "reconstruction",
  "target": "0x00c982a0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "Tribe",
  "name": "tribe_constructor_00c982a0",
  "package": "PKG-13-C3-TRIBE-CIV-WAVE2",
  "subsystem": "Simulator.Tribe",
  "va": "0x00c982a0"
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
  "content_sha256": "8ecd72a18ca092cdd177ed1da5e73e97d1fbc89eda76fe77e0c81146280b31ca",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00c982a0 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "thiscall",
  "hidden_this_register": "ECX",
  "hidden_this_type": "Tribe*",
  "ordinary_stack_arguments": [],
  "return_note": "incoming receiver returned unchanged",
  "return_register": "EAX",
  "return_type": "Tribe*",
  "return_width_bytes": 4,
  "saved_registers": [
    "EBX",
    "EBP",
    "ESI",
    "EDI"
  ],
  "stack_cleanup_bytes": 0,
  "termination": "plain RET"
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [],
  "callers": [],
  "edge_rows": [
    {
      "callsite": "0x00c9864a",
      "direction": "out",
      "other": "0x004548d0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c982c0",
      "direction": "out",
      "other": "0x00ac03d0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c984bc",
      "direction": "out",
      "other": "0x00afba10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c9833b",
      "direction": "out",
      "other": "0x00b63890",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c98528",
      "direction": "out",
      "other": "0x00b63890",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c98533",
      "direction": "out",
      "other": "0x00b63890",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c982d8",
      "direction": "out",
      "other": "0x00b6f280",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c9866c",
      "direction": "out",
      "other": "0x00bc3170",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c98673",
      "direction": "out",
      "other": "0x00bc3170",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c982a6",
      "direction": "out",
      "other": "0x00c011c0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c982b3",
      "direction": "out",
      "other": "0x00c89630",
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
  "globals": [
    "global:0x01485720"
  ],
  "types": [
    "Tribe",
    "Tribe*",
    "Tribe* incoming receiver returned unchanged"
  ],
  "vtables": [
    "vtable:0x01473e58"
  ]
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
      "gate-tribe-constructor-00c982a0",
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
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00c9864a",
      "direction": "out",
      "other": "0x004548d0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c982c0",
      "direction": "out",
      "other": "0x00ac03d0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c984bc",
      "direction": "out",
      "other": "0x00afba10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c9833b",
      "direction": "out",
      "other": "0x00b63890",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c98528",
      "direction": "out",
      "other": "0x00b63890",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c98533",
      "direction": "out",
      "other": "0x00b63890",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c982d8",
      "direction": "out",
      "other": "0x00b6f280",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c9866c",
      "direction": "out",
      "other": "0x00bc3170",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c98673",
      "direction": "out",
      "other": "0x00bc3170",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c982a6",
      "direction": "out",
      "other": "0x00c011c0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c982b3",
      "direction": "out",
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
      "same_package",
      "same_calling_convention"
    ],
    "package": "PKG-13-C3-TRIBE-CIV-WAVE2",
    "score": 10,
    "symbol": "city_add_building_00be1fb0",
    "va": "0x00be1fb0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "PKG-13-SIM-CREATURE-TRIBECIV",
    "score": 8,
    "symbol": "TribeState_test_purchased_tool_bit_00c8ec00",
    "va": "0x00c8ec00"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x01473e58"
    ],
    "package": "pkg-sporepedia-nop-slot",
    "score": 4,
    "symbol": "sporepedia_nop_slot_FUN_00c2e4e0",
    "va": "0x00c2e4e0"
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
    "package": "PKG-EDITOR-RUNTIME-WAVE7",
    "score": 2,
    "symbol": "EditorAnimWorld_PlayAnimation_0059cb10",
    "va": "0x0059cb10"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg13_c3_tribe_civ_wave2/tribe_civilization_wave2.cpp",
  "files": [
    "src/reconstruction/pkg13_c3_tribe_civ_wave2/tribe_civilization_wave2.cpp",
    "src/reconstruction/pkg13_c3_tribe_civ_wave2/tribe_civilization_wave2.hpp",
    "src/reconstruction/pkg13_c3_tribe_civ_wave2/tribe_civilization_wave2_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-sim-social-world-wave2/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg13-c3-tribe-civ-wave2/00c982a0.json"
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
    "No city, building, population, or persistence owner is inferred from this cTribe constructor.",
    "The concrete owner and runtime lifetime of the optional object at +0x368 remain unresolved.",
    "The delegated initializer layouts at +0x120, +0x1f4, +0x20c, +0x230, +0x270, +0x3b4, +0x510, +0x530, and +0x558 remain opaque.",
    "The vector element layout managed by 0x004548d0 at +0x1904 remains opaque beyond the observed pointer words and 14 reserve count.",
    "gate-tribe-constructor-00c982a0",
    "runtime validation not run"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-sim-social-world-wave2/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg13-c3-tribe-civ-wave2/00c982a0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg13_c3_tribe_civ_wave2/tribe_civilization_wave2.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg13_c3_tribe_civ_wave2/tribe_civilization_wave2.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg13_c3_tribe_civ_wave2/tribe_civilization_wave2_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg13-c3-tribe-civ-wave2/00c982a0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg13_c3_tribe_civ_wave2/tribe_civilization_wave2.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg13_c3_tribe_civ_wave2/tribe_civilization_wave2.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
  
[TRUNCATED]
```
