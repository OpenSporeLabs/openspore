# Reconstruction context 0x0045ae10

- Status: `partial`
- Content SHA-256: `d312147d2943009ff44d45c60dc356f94677573ffd6fad7fbd8d2daa828ef4d2`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x0045ae10",
  "phase": "reconstruction",
  "target": "0x0045ae10"
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
  "va": "0x0045ae10"
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
  "content_sha256": "eb0a845a31fed89921d3b0005cd60c6b081ed2281962c36fa09e3a909c9f1ea9",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x0045ae10 failed: Decompilation did not complete. Reason: ",
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
  "hidden_receiver": "ECX, spilled to [EBP-0x6c] at 0x0045ae16 and reloaded at 0x0045ae2c",
  "ordinary_stack_argument_slots": 2,
  "receiver": true,
  "ret_form": "RET 0x8",
  "return_observation": "no MOV to EAX appears in the 17 instructions; the epilogue is MOV ESP,EBP / POP EBP / RET 0x8",
  "return_register": "none (EAX is clobbered by the two callees and never written by this body)",
  "return_semantics": "no value; the only result of the call is the side effect inside 0x0045ac20",
  "return_type": "void",
  "return_width_bytes": 0,
  "saved_registers": [],
  "stack_arguments": [
    {
      "offset_in_callee": "[EBP + 0x8]",
      "read_by": "0x0045ae28: MOV ECX,dword ptr [EBP + 0x8]",
      "role": "becomes the second stack argument of 0x0045ac20",
      "slot": 1,
      "width_bytes": 4
    },
    {
      "offset_in_callee": "[EBP + 0xc]",
      "read_by": "0x0045ae24: MOV EAX,dword ptr [EBP + 0xc]",
      "role": "becomes the third stack argument of 0x0045ac20",
      "slot": 2,
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 8,
  "stack_cleanup_owner": "callee",
  "termination": "RET 0x8"
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
      "va": "0x00573f20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005744b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00575f70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00585d40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00587270"
    },
    {
      "name": "editor_input_00588570",
      "reconstructed": true,
      "va": "0x00588570"
    },
    {
      "name": "Editors::cEditor::HandleMessage",
      "reconstructed": false,
      "va": "0x00591fa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005dec10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0062f5c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0062f610"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0062f920"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0063ef70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0064c0d0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00573f36",
      "direction": "in",
      "other": "0x00573f20",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0057450c",
      "direction": "in",
      "other": "0x005744b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0057454e",
      "direction": "in",
      "other": "0
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "Opaque45ae10Registry*",
    "opaque POD, written by 0x00434040",
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
      "A runtime differential test is required to (a) observe the real value of 0x015d0c14 and of 0x015d22f0/f4/f8, (b) resolve the four virtual slots, and (c) determine whether the fourth argument read by 0x0045ac20 is genuinely uninitialised in the shipping build.",
      "No original-process trace exists for 0x0045ae10; every claim is static. The Cell stage has never been entered in any recorded run.",
      "The identity of the 0x14-byte POD cannot be settled statically at all: every field it copies is zero in the image."
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
      "va": "0x00573f20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005744b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00575f70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00585d40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00587270"
    },
    {
      "name": "editor_input_00588570",
      "reconstructed": true,
      "va": "0x00588570"
    },
    {
      "name": "Editors::cEditor::HandleMessage",
      "reconstructed": false,
      "va": "0x00591fa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005dec10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0062f5c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0062f610"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0062f920"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0063ef70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0064c0d0"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00573f36",
      "direction": "in",
      "other": "0x00573f20",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0057450c",
      "direction": "in",
      "other": "0x005744b0",
      "reference_type": "direct-call"
  
[TRUNCATED]
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-EDITOR-INPUT-WAVE6",
    "score": 3,
    "symbol": "editor_input_00588570",
    "va": "0x00588570"
  },
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
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/wave13-w1-dispatch-b00/registry_0045ae10.cpp",
    "reconstruction/staging/wave13-w1-dispatch-b00/registry_0045ae10.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-dispatch-b00/0045ae10.json"
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
    "A runtime differential test is required to (a) observe the real value of 0x015d0c14 and of 0x015d22f0/f4/f8, (b) resolve the four virtual slots, and (c) determine whether the fourth argument read by 0x0045ac20 is genuinely uninitialised in the shipping build.",
    "Is 0x0045ae10 an inline expansion of a one-line source function, or a real out-of-line wrapper? Its 42-byte body and 13-call fan-in are consistent with either.",
    "No original-process trace exists for 0x0045ae10; every claim is static. The Cell stage has never been entered in any recorded run.",
    "The 13 callers are only 2 inspected. The other 11 pass their key and mode through registers whose provenance was not traced, so the argument distribution across the fan-in is not established.",
    "The identity of the 0x14-byte POD cannot be settled statically at all: every field it copies is zero in the image.",
    "What are the four virtual slots 0x0045ac20 uses (+0x2c on a manager, +0x18 and +0x08 on the created object, +0x00/+0x04 on the map-resident object)? Slot offsets are observed; names and owning interfaces are not.",
    "What do 0x015d22f0/f4/f8 hold at runtime, and what does 0x0041cb40(&0x015d2638) do with them?",
    "What is the 0x14-byte POD built by 0x00434040? Its bytes are known; its type, alignment intent and units are not. The 1.0f default suggests a scale but proves nothing.",
    "What is the type behind 0x015d0c14? The file image holds zero, no vtable was located, and the SDK has no matching global manager for this access pattern.",
 
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-w1-dispatch-b00/0045ae10.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b00/registry_0045ae10.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b00/registry_0045ae10.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave13-w1-dispatch-b00/0045ae10.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b00/registry_0045ae10.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b00/registry_0045ae10.hpp",
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
    "RE
[TRUNCATED]
```
