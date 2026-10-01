# Reconstruction context 0x00c1d460

- Status: `partial`
- Content SHA-256: `19669a15ef2858c2a8c33aa79a2a4b137b3c071cccfbc44da899bdaffe28f7cb`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00c1d460",
  "phase": "reconstruction",
  "target": "0x00c1d460"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "Simulator_cCreatureBase_CreateAndStartPool2Effect_00c1d460",
  "package": "PKG-13-C4-CREATURE-WAVE3",
  "subsystem": null,
  "va": "0x00c1d460"
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
  "content_sha256": "1476e8b00e79aabac2001c7be6d3503affb827a19dc931c6ed6ad2f4b89ceead",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00c1d460 failed: Decompilation did not complete. Reason: ",
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
  "original_bytes": 23918,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": [\n      \"entry_ESP+0x4\"\n    ],\n    \"ordinary_stack_arguments\": [\n      {\n        \"entry_offset\": \"entry_ESP+0x4\",\n        \"observed\": true,\n        \"ordinal\": 1,\n        \"read\": false,\n        \"size_inferred\": false,\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      }\n    ],\n    \"receiver\": true,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET 0x8\",\n    \"return_register\": \"XMM0\",\n    \"return_semantics\": \"float_or_x87_in_XMM0\",\n    \"saved_registers\": [\n      \"EBP\",\n      \"EBX\",\n      \"EDI\",\n      \"ESI\"\n    ],\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"entry_ESP+0x4\",\n        \"observed\": true,\n        \"ordinal\": 1,\n        \"read\": false,\n        \"size_inferred\": false,\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      }\n    ],\n    \"stack_cleanup_bytes\": 8,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"RET 0x8\"\n  },\n  \"abstained_because\": [\n    \"flow_not_modelled: the linear ESP walk ends at +28, so the listing is not one path\",\n    \"untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated\",\n    \"frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memo
[TRUNCATED]
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "QuaternionToMatrix",
      "reconstructed": false,
      "va": "0x0059c190"
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c1d5e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d2d0b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d512f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e8bf20"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00c1d618",
      "direction": "in",
      "other": "0x00c1d5e0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d2d1f5",
      "direction": "in",
      "other": "0x00d2d0b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d5137a",
      "direction": "in",
      "other": "0x00d512f0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e8bf76",
      "direction": "in",
      "other": "0x00e8bf20",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e8bff5",
      "direction": "in",
      "other": "0x00e8bf20",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e8c016",
      "direction": "in",
      "other": "0x00e8bf20",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e8c023",
      "direction": "in",
      "other": "0x00e8bf20",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c1d52b",
      "direction": "out",
      "other": "0x0041cb40",
      "reference_type": "direct-cal
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "UNCONDITIONAL_CALL",
    "opaque 56-byte POD carrying a flag half-word, a count half-word, a three-real position, a real scale and a nine-real rotation",
    "uint32_t"
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
      "Confirm the handle reference-count pair on a live effect, including whether Start with argument 0 can clear the out slot that the cleanup reloads.",
      "Exercise the failure path with a service that returns false while writing a non-null handle, to confirm the Start and Release still run.",
      "No original-process trace, differential run under Wine, or runtime validation has been performed.",
      "Observe a real service create in an original process to confirm the instance id and group id contract and whether the group id is ever non-zero.",
      "Observe a real vtable slot +0x18 submission to learn the concrete property block layout and whether the pointer escapes.",
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
      "name": "QuaternionToMatrix",
      "reconstructed": false,
      "va": "0x0059c190"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c1d5e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d2d0b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d512f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e8bf20"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00c1d618",
      "direction": "in",
      "other": "0x00c1d5e0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d2d1f5",
      "direction": "in",
      "other": "0x00d2d0b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d5137a",
      "direction": "in",
      "other": "0x00d512f0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e8bf76",
      "direction": "in",
      "other": "0x00e8bf20",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e8bff5",
      "direction": "in",
      "other": "0x00e8bf20",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e8c016",
      "direction": "in",
      "other": "0x00e8bf20",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e8c023",
      "direction": "in",
      "other": "0x00e8bf20",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c1d52b",
     
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
    "symbol": "Simulator_cCreatureBase_LocomotionWalkToInterior_00c1c5c0",
    "va": "0x00c1c5c0"
  },
  {
    "match_basis": [
      "shared_types:UNCONDITIONAL_CALL"
    ],
    "package": "PKG-18-UI-SCRIPTING",
    "score": 3,
    "symbol": "FUN_005bf9d0",
    "va": "0x005bf9d0"
  },
  {
    "match_basis": [
      "shared_types:UNCONDITIONAL_CALL"
    ],
    "package": "PKG-18-UI-SCRIPTING",
    "score": 3,
    "symbol": "FUN_005c0100",
    "va": "0x005c0100"
  },
  {
    "match_basis": [
      "shared_types:UNCONDITIONAL_CALL"
    ],
    "package": "PKG-18-UI-SCRIPTING",
    "score": 3,
    "symbol": "FUN_005c0380",
    "va": "0x005c0380"
  },
  {
    "match_basis": [
      "shared_types:UNCONDITIONAL_CALL"
    ],
    "package": "wave6-resources",
    "score": 3,
    "symbol": "property_list_has_property_006a2470",
    "va": "0x006a2470"
  },
  {
    "match_basis": [
      "shared_types:UNCONDITIONAL_CALL"
    ],
    "package": "wave6-resources",
    "score": 3,
    "symbol": "property_list_get_property_object_006a24d0",
    "va": "0x006a24d0"
  },
  {
    "match_basis": [
      "shared_types:UNCONDITIONAL_CALL"
    ],
    "package": "PKG-13-C3-CREATURE-PROGRESSION-WAVE2",
    "score": 3,
    "symbol": "Simulator_cCreatureGameData_Get_00d2e340",
    "va": "0x00d2e340"
  },
  {
    "match_basis": [
      "shared_types:UNCONDITIONAL_CALL"
    ],
    "package": "PKG-13-C3-CREATURE-PROGRESSION-WAVE2",
    "score": 3,
    "symbol": "Simulator_cCreatureGameData_Add
[TRUNCATED]
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
    "reconstruction/metadata/pkg13-c4-creature-wave3/00c1d460.json"
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
    "Confirm the handle reference-count pair on a live effect, including whether Start with argument 0 can clear the out slot that the cleanup reloads.",
    "Exercise the failure path with a service that returns false while writing a non-null handle, to confirm the Start and Release still run.",
    "No original-process trace, differential run under Wine, or runtime validation has been performed.",
    "Observe a real service create in an original process to confirm the instance id and group id contract and whether the group id is ever non-zero.",
    "Observe a real vtable slot +0x18 submission to learn the concrete property block layout and whether the pointer escapes.",
    "runtime validation not run"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'derived'}, {'mode': 'derived', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'derived'}, {'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-sim-social-world-wave3/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg13-c4-creature-wave3/00c1d460.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg13-c4-creature-wave3/creature_wave3.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg13-c4-creature-wave3/creature_wave3.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg13-c4-creature-wave3/creature_wave3_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg13_c4_creature_wave3/creature_wave3.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg13_c4_creature_wave3/creature_wave3.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg13_c4_creature_wave3/creature_wave3_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg13_c4_creature_wave3/metadata_package_validation.py', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg13-c4-creature-wave3/00c1d460.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg13-c4-crea
[TRUNCATED]
```
