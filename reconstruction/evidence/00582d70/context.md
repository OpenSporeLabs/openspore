# Reconstruction context 0x00582d70

- Status: `partial`
- Content SHA-256: `700e067d805fdda3202ba32f359a81f73e1e791ab087b7ec371f2cde325a5f3a`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00582d70",
  "phase": "reconstruction",
  "target": "0x00582d70"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": null,
  "package": null,
  "subsystem": null,
  "va": "0x00582d70"
}
```

## 03_current_status

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "blocked": false,
  "reconstructed": false,
  "runtime_gated": true,
  "runtime_validated": 0,
  "status": "unresolved"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "c80e2c0326a5e625b8a626ee065852c25de312a311a990335db2a9dac5f2c5a1",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00582d70 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "__thiscall",
  "hidden_receiver": "ECX",
  "hidden_this_register": "ECX is copied to ESI at 0x00582d74 and read only as [ESI + disp]; the function passes it on to 0x0057ef50 and 0x009c69f0 as ECX after loading LEA EBP,[ESI + 0x36c] at 0x00582e5b and 0x00582ef6, so the vector helpers take the address of the begin field as their receiver",
  "ordinary_stack_argument_slots": 3,
  "receiver": true,
  "ret_form": "RET 0xc",
  "return_observation": "EAX is used only as scratch: the divide-by-0x30 sign correction at 0x00582db7 and the element-address computation at 0x00582df0 overwrite it before every call, and the last write before the epilogue is 0x00582ea1 LEA EDI,... / 0x00582ea8 SHL EDI,0x4",
  "return_register": "none",
  "return_semantics": "no value; the body never writes EAX on any exit path and all six exits share the same four-instruction epilogue",
  "return_type": "void",
  "return_width_bytes": 0,
  "saved_registers": [
    "ESI"
  ],
  "stack_arguments": [
    {
      "frame_offset": "[ESP + 0x18] at 0x00582d87",
      "index": 1,
      "meaning": "mode selector; compared against 1 at 0x00582d8b, against 0 at 0x00582f72 and against 2 at 0x00582fb3",
      "width": 4
    },
    {
      "frame_offset": "[ESP + 0x1c] at 0x00582d94",
      "index": 2,
      "meaning": "remove_last, read as a BYTE; any non-zero byte selects the remove-last path, so only bit 0 of the pushed dword matters",
      "width": 1
    },
    {
      "frame_offset": "[ESP + 0x28] at 0x00582e61 after PUSH EBX; PUSH EBP",
      "index": 3,
     
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
      "va": "0x0059d110"
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0062ba10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0062c340"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0062c990"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x0062ba5e",
      "direction": "in",
      "other": "0x0062ba10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0062ba7f",
      "direction": "in",
      "other": "0x0062ba10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0062c3de",
      "direction": "in",
      "other": "0x0062c340",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0062ca18",
      "direction": "in",
      "other": "0x0062c990",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00582e05",
      "direction": "out",
      "other": "0x00401050",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00582ec1",
      "direction": "out",
      "other": "0x00401050",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00582f33",
      "direction": "out",
      "other": "0x00401050",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00582e0c",
      "direction": "out",
      "other": "0x0045af60",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00582ec8",
      "direction": "out",
      "other": "0x0045af60"
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
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
      "A runtime trace is required to confirm modes 0 and 2 are never taken, since no static reference to them exists.",
      "A runtime trace is required to confirm no entry destructor is needed, i.e. that the removed 0x30-byte entries leak or are owned elsewhere by design.",
      "A runtime trace is required to observe the 0x03f1bf57 notification reaching a listener, which is the only way to learn what the detach protocol announces.",
      "No original-process trace has ever been captured for 0x00582d70; every claim here is static. The original Cell stage has never been entered in any recorded run."
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
      "va": "0x0059d110"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0062ba10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0062c340"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0062c990"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x0062ba5e",
      "direction": "in",
      "other": "0x0062ba10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0062ba7f",
      "direction": "in",
      "other": "0x0062ba10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0062c3de",
      "direction": "in",
      "other": "0x0062c340",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0062ca18",
      "direction": "in",
      "other": "0x0062c990",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00582e05",
      "direction": "out",
      "other": "0x00401050",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00582ec1",
      "direction": "out",
      "other": "0x00401050",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00582f33",
      "direction": "out",
      "other": "0x00401050",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00582e0c",
      "direction": "out",
      "other": "0x0045af60",
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
      "same_calling_convention"
    ],
    "package": "PKG-APP-SAFE-WAVE11",
    "score": 2,
    "symbol": "property_record_assign_pair_004279d0",
    "va": "0x004279d0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-APP-SAFE-WAVE11",
    "score": 2,
    "symbol": "property_record_assign_scalar_00428060",
    "va": "0x00428060"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-EDITOR-SAFE-WAVE11",
    "score": 2,
    "symbol": "editor_paint_commit_0043ac40",
    "va": "0x0043ac40"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-APP-SAFE-WAVE11",
    "score": 2,
    "symbol": "model_parts_apply_properties_00447150",
    "va": "0x00447150"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-APP-SAFE-WAVE11",
    "score": 2,
    "symbol": "pair_vector_insert_004786e0",
    "va": "0x004786e0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-EDITOR-SAFE-WAVE11",
    "score": 2,
    "symbol": "editor_entry_expand_004ad6f0",
    "va": "0x004ad6f0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-10-EDITOR-DISPATCH",
    "score": 2,
    "symbol": "Editors_EditorModel_SetColor_raw_004ae250",
    "va": "0x004ae250"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-APP-SAFE-WAVE11",
    "score": 2,
    "symbol": "pair_vector_construct_004b62a0",
    "va": "0x004b62a0"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/wave13-w1-dispatch-b02/b582d70_editor_remove_creature.cpp",
    "reconstruction/staging/wave13-w1-dispatch-b02/b582d70_editor_remove_creature.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-dispatch-b02/00582d70.json"
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
    "A runtime trace is required to confirm modes 0 and 2 are never taken, since no static reference to them exists.",
    "A runtime trace is required to confirm no entry destructor is needed, i.e. that the removed 0x30-byte entries leak or are owned elsewhere by design.",
    "A runtime trace is required to observe the 0x03f1bf57 notification reaching a listener, which is the only way to learn what the detach protocol announces.",
    "Are modes 0 and 2 reachable at runtime through a patch or a function pointer? No static reference exists, and no differential trace has been captured.",
    "Is the owning class really Editors::cEditor? The evidence is the SDK address table's neighbourhood plus the receiver being the pointer stored at caller+0x3614; no vtable was located and the binary has no RTTI.",
    "No original-process trace has ever been captured for 0x00582d70; every claim here is static. The original Cell stage has never been entered in any recorded run.",
    "What are the eleven unread dwords of the 0x30-byte entry? AddCreature writes them, but no SDK structure describes the element.",
    "What are the two EDX-side divisions at 0x00582e6b..0x00582e7d and 0x00582ef6..0x00582f06 for? They recompute the same count; the pseudocode's variable naming makes them look like distinct quantities.",
    "What is the SDK method name of the target? The cEditor address table jumps from sub_581F70 at 0x00582250 to AddCreature at 0x00582fe0, leaving the target unnamed.",
    "What is the attach flag at +0x385? Its setter 0x0057e34
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-w1-dispatch-b02/00582d70.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b02/b582d70_editor_remove_creature.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b02/b582d70_editor_remove_creature.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave13-w1-dispatch-b02/00582d70.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b02/b582d70_editor_remove_creature.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b02/b582d70_editor_remove_creature.hpp",
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
    "
[TRUNCATED]
```
