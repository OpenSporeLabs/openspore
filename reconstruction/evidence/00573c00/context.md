# Reconstruction context 0x00573c00

- Status: `partial`
- Content SHA-256: `5071e8e41207c57b18297b8f19500d8bb68173a16bc943b1e10ba491f4be3d65`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00573c00",
  "phase": "reconstruction",
  "target": "0x00573c00"
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
  "va": "0x00573c00"
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
  "content_sha256": "e24f97e2807336f8f07f06e4058f94c070dd91a4d5800f39d996fce38e64d8c6",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00573c00 failed: Decompilation did not complete. Reason: ",
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
  "hidden_receiver": "ECX, copied to ESI at 0x00573c02; EBX is then set to the ADDRESS of the receiver's +0xcc field at 0x00573c0e (LEA EBX,[ESI + 0xcc]) and used as a first-class pointer for the rest of the body",
  "ordinary_stack_argument_slots": 2,
  "receiver": true,
  "ret_form": "RET 0x8",
  "return_observation": "the only store of a computed value is 0x00573d5a..0x00573d61: CMP dword ptr [EBX],0x0 / POP EDI / SETNZ CL / MOV byte ptr [ESI + 0x398],CL. Nothing is returned in a register.",
  "return_register": "none (EAX is scratch throughout; the last value in it is discarded at 0x00573d69)",
  "return_semantics": "no register result. The single observable outcome is the byte written to receiver + 0x398, which is the boolean 'the +0xcc slot is non-null' and is refreshed on every path including both early exits.",
  "return_type": "void",
  "return_width_bytes": 0,
  "saved_registers": [
    "EBX",
    "ESI",
    "EDI"
  ],
  "stack_arguments": [
    {
      "offset_in_callee": "[ESP + 0x10] with ESP lowered 12",
      "read_by": "0x00573c15: MOV EDI,dword ptr [ESP + 0x10]",
      "role": "the incoming rigblock pointer, stored in EDI and tested at 0x00573c19, 0x00573c80, 0x00573cc1",
      "slot": 1,
      "width_bytes": 4
    },
    {
      "offset_in_callee": "[ESP + 0x10] with ESP lowered 8",
      "read_by": "0x00573c0a: MOV ECX,dword ptr [ESP + 0x10]",
      "role": "the paint-region value, stored in ECX and latched into +0x3b0 and +0x3b4 at 0x00573c31/0x00573c37",
      "slot": 2,
      "width_by
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
      "va": "0x004a88d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004b09b0"
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00573d70"
    },
    {
      "name": "FUN_005774f0",
      "reconstructed": false,
      "va": "0x005774f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00577520"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0057f6c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005858f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00587270"
    },
    {
      "name": "Editors::cEditor::OnExit",
      "reconstructed": false,
      "va": "0x00587a20"
    },
    {
      "name": "editor_input_00588570",
      "reconstructed": true,
      "va": "0x00588570"
    },
    {
      "name": "editor_input_0058ac10",
      "reconstructed": true,
      "va": "0x0058ac10"
    },
    {
      "name": "editor_input_0058b650",
      "reconstructed": true,
      "va": "0x0058b650"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0058ba60"
    },
    {
      "name": "Editors::cEditor::HandleMessage",
      "reconstructed": false,
      "va": "0x00591fa0"
    },
    {
      "name": "Editors_EditorUI_HandleMessage_005e0000",
      "reconstructed": true,
      "va": "0x005e0000"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00573ea3",
      "direction": "in",
      "ot
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "bitflags",
    "bool",
    "handle pointer (nullable)",
    "int",
    "mode enumerator",
    "pointer (nullable)",
    "rigblock pointer (nullable)",
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
      "12 of the 13 recorded callsites were not disassembled. A full callsite sweep is static work and is listed in unresolved_questions rather than as a runtime gate.",
      "No original-process trace exists for 0x00573c00; every claim is static and the Cell stage has never been entered in any recorded run.",
      "The +0xdc8 bit semantics are the single largest gap and only a run can close it: each bit must be observed being set on a real rigblock together with the behaviour it gates.",
      "The vtable slot +0x8 callee, and the concrete types of the +0x498 and +0x3c4 receivers, require a run with a real editor session.",
      "Whether the discarded comparison at 0x00573c6f matters for its callee's side effects can only be settled by instrumenting 0x004a60a0 at runtime."
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
      "va": "0x004a88d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004b09b0"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00573d70"
    },
    {
      "name": "FUN_005774f0",
      "reconstructed": false,
      "va": "0x005774f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00577520"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0057f6c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005858f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00587270"
    },
    {
      "name": "Editors::cEditor::OnExit",
      "reconstructed": false,
      "va": "0x00587a20"
    },
    {
      "name": "editor_input_00588570",
      "reconstructed": true,
      "va": "0x00588570"
    },
    {
      "name": "editor_input_0058ac10",
      "reconstructed": true,
      "va": "0x0058ac10"
    },
    {
      "name": "editor_input_0058b650",
      "reconstructed": true,
      "va": "0x0058b650"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0058ba60"
    },
    {
      "name": "Editors::cEditor::HandleMessage",
      "reconstructed": false,
      "va": "0x00591fa0"
    },
    {
      "name": "Editors_EditorUI_HandleMessage_005e0000",
      "reconstructed": true,
      "va": "0x005e0000"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,

[TRUNCATED]
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "same_calling_convention",
      "direct_xref_neighbor"
    ],
    "package": "PKG-10-EDITOR-DISPATCH",
    "score": 5,
    "symbol": "Editors_EditorUI_HandleMessage_005e0000",
    "va": "0x005e0000"
  },
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
      "direct_xref_neighbor"
    ],
    "package": "PKG-EDITOR-INPUT-WAVE6",
    "score": 3,
    "symbol": "editor_input_0058ac10",
    "va": "0x0058ac10"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-EDITOR-INPUT-WAVE6",
    "score": 3,
    "symbol": "editor_input_0058b650",
    "va": "0x0058b650"
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
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/wave13-w1-dispatch-b00/editor_00573c00.cpp",
    "reconstruction/staging/wave13-w1-dispatch-b00/editor_00573c00.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-dispatch-b00/00573c00.json"
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
    "12 of the 13 recorded callsites were not disassembled. A full callsite sweep is static work and is listed in unresolved_questions rather than as a runtime gate.",
    "Is 0x00573c00 a vtable entry of the editor or of the mode classes? No vtable for the editor was located and no pointer scan for this address was performed.",
    "Is the discarded comparison at 0x00573c6f a source-level dead store, or does 0x004a60a0 have a side effect that matters? If the latter, the reimplementation must still call it even though the answer is unused. Static evidence cannot separate these.",
    "No original-process trace exists for 0x00573c00; every claim is static and the Cell stage has never been entered in any recorded run.",
    "Only 1 of the 13 recorded callsites was disassembled. The argument distribution across the fan-in, and in particular whether the 0xffffffff region sentinel seen at 0x00573e9d is common, is not established.",
    "The +0xdc8 bit semantics are the single largest gap and only a run can close it: each bit must be observed being set on a real rigblock together with the behaviour it gates.",
    "The vtable slot +0x8 callee, and the concrete types of the +0x498 and +0x3c4 receivers, require a run with a real editor session.",
    "What do 0x004b09b0 (which receives the ADDRESS of the field as its this), 0x0043a830 with its 0/1 phases, and 0x0043e2b0 actually do? Only their call shapes and gates are observed.",
    "What do the +0xdc8 flag bits mean? Bits 1, 3, 7, 10, 11 and 20 are read across this function, 0x004
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-w1-dispatch-b00/00573c00.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b00/editor_00573c00.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b00/editor_00573c00.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave13-w1-dispatch-b00/00573c00.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b00/editor_00573c00.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b00/editor_00573c00.hpp",
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
    "RETURN
[TRUNCATED]
```
